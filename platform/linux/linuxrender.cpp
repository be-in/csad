/*
 * linuxrender.cpp
 *
 *  Created on: 13.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>

#if defined (OS_LINUX)

#include <platform.h>
#include <core/module.h>
#include <scene/scene.h>
#include <scene/camera.h>
#include <scene/transform.h>
#include <scene/viewport.h>
#include <scene/meshfilter.h>
#include <scene/mesh.h>
#include <scene/material.h>
#include <scene/texture2d.h>
#include <bt.h>
#include "linuxglextention.h"
#include "csad/platform/localdisplay.h"

OPTIMIZE_ON;

namespace csad {

unsigned int Render::p_isVal;
void* Render::hInst;
unsigned char * Render::p_lastelements;

Render::Render()
{
}

void Render::initialize(GlContext * context)
{
	Context_P * mcontext=(Context_P *)(context->p_context);
	if ((!mcontext) || (mcontext->initialize)) return;
	sFunctionsGLContext &functions=context->ffunctions;
	glInitGLFunctions(&functions);
	int err=functions.GetError();
	if (err) Log::console("Render::initialize failed: 0x%x\n", err);
	glReadExtention(mcontext);

	err=functions.GetError();
	if (err) Log::console("Render::initialize failed: 0x%x\n", err);

	char *info=(char*)mcontext->GetString(GL_VERSION);
	if (!info) Log::console("Render::initialize GL_VERSION failed: 0x%x\n", functions.GetError());
	Log::console("GL_VERSION: %s",info);
	info=(char*)mcontext->GetString(GL_VENDOR);
	if (!info) Log::console("Render::initialize GL_VENDOR failed: 0x%x\n", functions.GetError());
	Log::console("GL_VENDOR: %s",info);
	info=(char*)mcontext->GetString(GL_RENDERER);
	if (!info) Log::console("Render::initialize GL_RENDERER failed: 0x%x\n", functions.GetError());
	Log::console("GL_RENDERER: %s",info);
	info=(char*)mcontext->GetString(GL_EXTENSIONS);
	if (!info) Log::console("Render::initialize GL_EXTENSIONS failed: 0x%x\n", functions.GetError());
	Log::console("GL_EXTENSIONS: %s",info);

	//DrawModel=&_DrawModelVBO;
	//DrawLodModel=&_DrawLodModelVBO;
	functions.DrawMesh=(tfSTDCALL_PROC_p)&_DrawMesh;
	mcontext->BindModel=(tfFASTCALL_bool_FUNC_p_p)&_BindModel;
	mcontext->DrawBindModel=(tfFASTCALL_bool_FUNC_p_p)&_DrawBindModel;
	//DrawBindLodModel=&_DrawBindLodModelVBO;
	mcontext->UpdateModelElement=(tfFASTCALL_PROC_p_p_int_int)&_UpdateModelElement;
	mcontext->UpdateModelIndex=(tfFASTCALL_PROC_p_p_int_int)&_UpdateModelIndex;
	mcontext->UnBindModel=(tfFASTCALL_PROC)&_UnBindModel;

	if ((functions.extensionsFlag & GlContext::EXT_VB)!=0) {
		mcontext->_GL_ARB_vertex_buffer_object=(
			functions.GenBuffers && functions.BindBuffer && functions.BufferData && 
			functions.BufferSubData && functions.MapBuffer && functions.UnmapBuffer && 
			functions.DeleteBuffers && functions.GetBufferParameteriv);
	} else mcontext->_GL_ARB_vertex_buffer_object=false;

	if (mcontext->_GL_ARB_vertex_buffer_object) {
		functions.DrawMesh=(tfSTDCALL_PROC_p)&_DrawMeshVBO;
		mcontext->BindModel=(tfFASTCALL_bool_FUNC_p_p)&_BindModelVBO;
		mcontext->DrawBindModel=(tfFASTCALL_bool_FUNC_p_p)&_DrawBindModelVBO;
		mcontext->UpdateModelElement=(tfFASTCALL_PROC_p_p_int_int)&_UpdateModelElementVBO;
		mcontext->UpdateModelIndex=(tfFASTCALL_PROC_p_p_int_int)&_UpdateModelIndexVBO;
		mcontext->UnBindModel=(tfFASTCALL_PROC)&_UnBindModelVBO;
	}
	p_isVal=VALIDED;
}

void _FASTCALL Render::Info()
{
	/*char *str=(char*)glGetString(GL_RENDERER);
	Log::console("GL_RENDERER: %s",str);
	str=(char*)glGetString(GL_EXTENSIONS);
	//vertex_buffer_object=strstr(str,"vertex_array_object")!=0;
	Log::console("GL_EXTENSIONS: %s",str);*/
}

void _APICALL Render::setViewPort(int x,int y,int width,int height)
{
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	functions.Enable(GL_SCISSOR_TEST);
	functions.Viewport(x,y,width,height);
	functions.Scissor(x,y,width,height);
}

void _FASTCALL Render::setClearColor(vector4f *color)
{
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	functions.ClearColor(color->x,color->y,color->z,color->w);
}

unsigned int _FASTCALL Render::GenTextures(int count,void* data)
{
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	functions.GenTextures(count,(GLuint *)data);
	return functions.GetError();
}

int Render::GetTexure2DWidth()
{
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	int val=0;
	functions.GetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_WIDTH,&val);
	return val;
}

int Render::GetTexure2DHeight()
{
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	int val=0;
	functions.GetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_HEIGHT,&val);
	return val;
}

int Render::formatFromBPP(int bpp,int format)
{
	if (bpp==4) if (format!=GL_RGBA) format=GL_RGBA;
	if (bpp==3)	if (format!=GL_RGB) format=GL_RGB;
//	if (bpp==4) if (format!=GL_BGRA || format==GL_BGR) format=GL_BGRA;
//	if (bpp==3)	if (format!=GL_BGR || format==GL_BGRA) format=GL_BGR;
	if (bpp==1)	if (format!=GL_RED && format!=GL_GREEN && format!=GL_BLUE && format!=GL_ALPHA && format!=GL_LUMINANCE) format=GL_LUMINANCE;
	return format;
}

void Render::TexImage2D(int level,int format,int width,int height,void * data)
{
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	int internalformat=format;
	if (internalformat==GL_BGRA) internalformat=GL_RGBA;
	if (internalformat==GL_BGR) internalformat=GL_RGB;
	functions.TexImage2D(GL_TEXTURE_2D,level,internalformat,width,height,0,format,GL_UNSIGNED_BYTE,data);
}

bool Render::createContext(Display *display, GlContext * context)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;
	Context_P * mcontext=(Context_P *)(context->p_context);
	glBasefunctions(mcontext);
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	mcontext->context=(GLXContext)mcontext->CreateContext((void*)mdisplay->display,(void*)mdisplay->vi,NULL,1);
	mcontext->initialize=0;
	mcontext->_GL_ARB_shader=false;
	mcontext->_GL_EXT_stencil_wrap=false;
	mcontext->_GL_ARB_vertex_buffer_object=false;
	mcontext->_GL_EXT_stencil_two_side=false;

	if (mcontext->context==0)
	{
		Log::console("Create context failed: 0x%x\n", functions.GetError());
		return false;
	}

	return true;
}

bool Render::destroyContext(Display *display, GlContext * context)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;
	Context_P * mcontext=(Context_P *)(context->p_context);
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	mcontext->DestroyContext(mdisplay->display,mcontext->context);
	/*if (mcontext->wglDeleteContext(mcontext->context))
	{
		Log::console("Destroy context failed: 0x%x\n", functions.GetError());
		return false;
	}*/
	mcontext->context=0;
	return true;
}

void * Render::getCurrentContext()
{
	if (!GlContext::p_current) return 0;
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	return (void*)mcontext->GetCurrentContext();
}

bool Render::MakeCurrent(Display * display,GlContext * context)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;
	Context_P * mcontext=(Context_P *)(context->p_context);
	bool ret=true;
	if (context==0) {
		if ((void*)mcontext->GetCurrentContext()!=0)
			ret=mcontext->MakeCurrent((void*)mdisplay->display,(void*)mdisplay->surface, 0)!=0;
		GlContext::p_current=0;
		return ret;
	}
	if (mcontext->context!=(void*)mcontext->GetCurrentContext())
		ret=mcontext->MakeCurrent((void*)mdisplay->display,(void*)mdisplay->surface, mcontext->context)!=0;
	if (ret) Render::initialize(context);
	return ret;
}

void Render::setMipMap(int _min,int _max)
{
	//GL_GENERATE_MIPMAP
	sFunctionsGLContext &functions=GlContext::p_current->functions();
	functions.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, _max);
	functions.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD, _min);
}

void Render::setFilterMode(int mag,int min)
{
	sFunctionsGLContext &functions=GlContext::p_current->functions();
	functions.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
	functions.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
}

/*void _FASTCALL Render::DrawMesh(MeshFilter *mesh)
{
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	VBOMesh *vbo=mesh->getVBOMesh();
	Mesh *mmesh=mesh->getMesh();
	if (!mmesh) return;

	if (mcontext->_GL_ARB_vertex_buffer_object) {
		if (vbo==0) {
			vbo=(VBOMesh *)GlContext::p_current->createVBOMesh(mmesh);
			mesh->setMesh((Mesh*)vbo);
		} else if (vbo->context!=GlContext::p_current) {
			vbo=(VBOMesh *)GlContext::p_current->createVBOMesh(mmesh);
			mesh->setMesh((Mesh*)vbo);
		}
	}

	mcontext->BindModel(mmesh,vbo);
	mcontext->DrawBindModel(mmesh,vbo);
}*/

void _FASTCALL Render::FreeVBO(VBOMesh *mesh)
{
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	if (mcontext->_GL_ARB_vertex_buffer_object) {
		if (mesh->index) functions.DeleteBuffers(1,&mesh->index);
		if (mesh->elements) functions.DeleteBuffers(1,&mesh->elements);
		mesh->index=0;
		mesh->elements=0;
	}
}

void _FASTCALL Render::UnBindModel()
{
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	mcontext->UnBindModel();
}

void Render::BindTexture2D(unsigned int text)
{
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	GLboolean isEnable;
	functions.GetBooleanv(GL_TEXTURE_2D,&isEnable);
	if (!isEnable) functions.Enable(GL_TEXTURE_2D);
	if (GlContext::p_current->p_lasttexture2d!=text) functions.BindTexture(GL_TEXTURE_2D,text);
	GlContext::p_current->p_lasttexture2d=text;
}

void Render::BindTexture2D(Texture2D* text)
{
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	GLboolean isEnable;
	functions.GetBooleanv(GL_TEXTURE_2D,&isEnable);
	if (!isEnable) functions.Enable(GL_TEXTURE_2D);
	unsigned int id=text->texture();
	if (text->p_context!=GlContext::p_current) id=text->setContext(GlContext::p_current);
	if (GlContext::p_current->p_lasttexture2d!=id) functions.BindTexture(GL_TEXTURE_2D,id);
	GlContext::p_current->p_lasttexture2d=id;
}

bool Render::CompileSourceFile(GLuint _id,char *_filename)
{
	Context_P * mcontext=(Context_P *)(GlContext::getCurrent()->p_context);
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	if (!mcontext->_GL_ARB_shader) return false;
	File file(_filename,File::READ);
	if (!file.open()) {
		GLint type;
		functions.GetShaderiv(_id,GL_SHADER_TYPE,&type);
		return false;
	}
	char* contents = file.readAll();
	bool ret=CompileSource(_id,contents);
	delete contents;
	return ret;  
}

bool Render::CompileSource(GLuint _id,char *_src)
{
	Context_P * mcontext=(Context_P *)(GlContext::getCurrent()->p_context);
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	if (!mcontext->_GL_ARB_shader) return false;
	GLint len=extFunctions.FindCMem(_src,0,65535);
	functions.ShaderSource (_id, 1, (const char **)&_src, &len);
	functions.CompileShader (_id);
	if ( functions.GetError () == GL_INVALID_OPERATION )
	{
		GLint     errorPos;
		GLubyte * errorStr=0;

		functions.GetIntegerv ( GL_PROGRAM_ERROR_POSITION_ARB, &errorPos );

		//errorString = glGetString ( GL_PROGRAM_ERROR_STRING_ARB );

		Log::console("Error at position %d.\\Line: \"%s\"",errorPos, errorStr);
		//printf ( "Error at position %d.\\Line: \"%s\"\n", errorPos, errorStr );
	}
	return true;
}

void Render::UseProgram(GLuint _id)
{
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	Context_P * mcontext=(Context_P *)(GlContext::getCurrent()->p_context);
	if (!mcontext->_GL_ARB_shader) return;
	GLuint cp;
	functions.GetIntegerv(GL_CURRENT_PROGRAM,(GLint*)&cp);
	if (cp==_id) return;
	functions.UseProgram(_id);
}

void Render::LogProgram(GLuint _id)
{
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	if (!mcontext->_GL_ARB_shader) return;
	//value = 0;
	//mcontext->glGetProgramiv(_id, GL_LINK_STATUS, &value);
	GLint mvalue = 0;
	functions.GetProgramiv(_id, GL_INFO_LOG_LENGTH, &mvalue);
	if (mvalue > 1) {
		char *logbuf = new char [mvalue];
		GLint len;
		functions.GetProgramInfoLog(_id, mvalue, &len, logbuf);
		Log::console("%s",logbuf);
		delete [] logbuf;
	}
}

void Render::DeleteProgram(GLuint _id)
{
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	if (!mcontext->_GL_ARB_shader) return;
	if (!_id) return;
	GLint vs;
	functions.GetProgramiv(_id,GL_VERTEX_SHADER,&vs);
	if (vs) functions.DeleteShader(vs);
	GLint fs;
	functions.GetProgramiv(_id,GL_FRAGMENT_SHADER,&fs);
	if (fs) functions.DeleteShader(fs);
	functions.DeleteProgram(_id);
}

void Render::Uniform1f(char *_name,float _x)
{
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	GLuint cp;
	functions.GetIntegerv(GL_CURRENT_PROGRAM,(GLint*)&cp);
	functions.Uniform1f(functions.GetUniformLocation(cp,_name),_x);
}

void Render::Uniform2f(char *_name,float _x,float _y)
{
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	GLuint cp;
	functions.GetIntegerv(GL_CURRENT_PROGRAM,(GLint*)&cp);
	functions.Uniform2f(functions.GetUniformLocation(cp,_name),_x,_y);
}

void Render::Uniform3f(char *_name,float _x,float _y,float _z)
{
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	GLuint cp;
	functions.GetIntegerv(GL_CURRENT_PROGRAM,(GLint*)&cp);
	functions.Uniform3f(functions.GetUniformLocation(cp,_name),_x,_y,_z);
}

void Render::Uniform4f(char *_name,float _x,float _y,float _z,float _w)
{
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	GLuint cp;
	functions.GetIntegerv(GL_CURRENT_PROGRAM,(GLint*)&cp);
	functions.Uniform4f(functions.GetUniformLocation(cp,_name),_x,_y,_z,_w);
}

void _FASTCALL Render::Finish()
{
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	if (mcontext && functions.SwapInterval) {
		if (!GlContext::p_current->p_parent->isVSync()) {
			functions.SwapInterval(0);
		} else {
			functions.SwapInterval(1);
		}
	}
	functions.Flush();
	functions.Finish();
}

void _FASTCALL Render::Buffers(Display *display)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	if (GlContext::p_current) mcontext->SwapBuffers((void*)mdisplay->display,(void*)mdisplay->surface);
}

void _FASTCALL Render::UnBindAll()
{
	GlContext::p_current->p_lasttexture2d=-1;
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	mcontext->UnBindModel();
}

unsigned int indexSize[8]={GL_UNSIGNED_INT,GL_UNSIGNED_BYTE,GL_UNSIGNED_SHORT,GL_UNSIGNED_INT,GL_UNSIGNED_INT,GL_UNSIGNED_INT,GL_UNSIGNED_INT,GL_UNSIGNED_INT};

void _APICALL Render::_DrawMesh(MeshFilter *mesh)
{
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	Mesh *mmesh=mesh->getMesh();
	if (!mmesh) return;

	if (!mmesh) return;
	if ((p_lastelements!=mmesh->p_elements) || (p_lastelements==0)) {
		if (mmesh->p_elementCount == 0) return;

		_InterleavedArrays(mmesh->p_elementFormat,0,mmesh->p_elements);
	}
	p_lastelements=mmesh->p_elements;
	if (!mmesh) return;
	if ((mmesh->p_indexCount==0) || (mmesh->p_index == NULL)) return;
	int idIndexSize=(mmesh->p_drawFormat>>24)&7;
	functions.DrawElements(mmesh->p_drawFormat & Mesh::_GL_MASK,mmesh->p_indexCount,indexSize[idIndexSize],mmesh->p_index);
}

void _APICALL Render::_DrawMeshVBO(MeshFilter *mesh)
{
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	VBOMesh *vbo=mesh->getVBOMesh();
	Mesh *mmesh=mesh->getMesh();
	if (!mmesh) return;

	if (vbo==0) {
		vbo=(VBOMesh *)GlContext::p_current->createVBOMesh(mmesh);
		mesh->setMesh((Mesh*)vbo);
	} else if (vbo->context!=GlContext::p_current) {
		vbo=(VBOMesh *)GlContext::p_current->createVBOMesh(mmesh);
		mesh->setMesh((Mesh*)vbo);
	}

	if ((!mmesh) || (!vbo)) return;
	if ((mmesh->p_drawFormat & Mesh::_GL_NEED_INDEX_UPDATE)!=0) {
		_UpdateModelIndexVBO(mmesh,vbo,0,mmesh->p_indexCount);
		mmesh->p_drawFormat^=Mesh::_GL_NEED_INDEX_UPDATE;
	}
	if ((mmesh->p_drawFormat & Mesh::_GL_NEED_ELEMENT_UPDATE)!=0) {
		_UpdateModelElementVBO(mmesh,vbo,0,mmesh->p_elementCount);
		mmesh->p_drawFormat^=Mesh::_GL_NEED_ELEMENT_UPDATE;
	}
	if (vbo->elements==0) {
		int s=Mesh::_elementSize(mmesh->p_elementFormat);
		if (mmesh->p_elementCount <= 0) return;
		functions.GenBuffers(1,&vbo->elements);
		functions.BindBuffer(GL_ARRAY_BUFFER_ARB,vbo->elements);
		functions.BufferData(GL_ARRAY_BUFFER_ARB,s*mmesh->p_elementCount,(GLvoid *)mmesh->p_elements,GL_STATIC_DRAW_ARB);
	}
	if ((p_lastelements!=mmesh->p_elements) || (p_lastelements==0)) {
		functions.BindBuffer(GL_ARRAY_BUFFER_ARB,vbo->elements);
		_InterleavedArrays(mmesh->p_elementFormat,0,0);
		p_lastelements=mmesh->p_elements;
	}
	if ((mmesh->p_indexCount == 0) || (mmesh->p_index == NULL)) return;
	if (vbo->index == 0) {
		functions.GenBuffers(1,&vbo->index);
		functions.BindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,vbo->index);
		functions.BufferData(GL_ELEMENT_ARRAY_BUFFER_ARB,(sizeof(GlIndex))*mmesh->p_indexCount,(GLvoid *)mmesh->p_index,GL_STATIC_DRAW_ARB);
	} else functions.BindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,vbo->index);
	int idIndexSize=(mmesh->p_drawFormat>>24)&7;
	functions.DrawElements(mmesh->p_drawFormat & Mesh::_GL_MASK,mmesh->p_indexCount,indexSize[idIndexSize],0);
}

void Render::_InterleavedArrays(unsigned int format,unsigned int item,unsigned char *pointer)
{
	sFunctionsGLContext &functions=GlContext::p_current->functions();
	int s=Mesh::_elementSize(format);
	pointer+=item*s;
	int c=0;
	bool textenable=false;
	for (int i=0;i<6;i++) {
		c=Mesh::_elementSize(format,i);
		if (c>0) {
			functions.EnableClientState(GL_TEXTURE_COORD_ARRAY);
			functions.TexCoordPointer(Mesh::_elementSubCount(format,i),GL_FLOAT, s, (GLvoid *)(pointer));
			//mcontext->glTexCoordPointer(Mesh::_elementSubCount(format,i),GL_FLOAT, s, (GLvoid *)(pointer));
			pointer+=c;
			textenable=true;
		}
	}
	if (!textenable) {
		functions.DisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	c=Mesh::_elementSize(format,6);
	if (c>0) {
		functions.EnableClientState(GL_COLOR_ARRAY);
		functions.ColorPointer(Mesh::_elementSubCount(format,6), GL_FLOAT, s, (GLvoid *)(pointer));
		//mcontext->glColorPointer(Mesh::_elementSubCount(format,6), GL_FLOAT, s, (GLvoid *)(pointer));
		pointer+=c;
	} else {
		functions.DisableClientState(GL_COLOR_ARRAY);
	}

	c=Mesh::_elementSize(format,7);
	if (c>0) {
		functions.EnableClientState(GL_NORMAL_ARRAY);
		functions.NormalPointer(GL_FLOAT, s, (GLvoid *)(pointer));
		pointer+=c;
	} else {
		functions.DisableClientState(GL_NORMAL_ARRAY);
	}

	c=Mesh::_elementSize(format,8);
	if (c>0) {
		functions.EnableClientState(GL_VERTEX_ARRAY);
		int cc=Mesh::_elementSubCount(format,8);
		if (cc*4<c) {
			functions.VertexPointer(cc, GL_DOUBLE, s, (GLvoid *)(pointer));
		} else {
			functions.VertexPointer(cc, GL_FLOAT, s, (GLvoid *)(pointer));
		}
		pointer+=c;
	} else {
		functions.DisableClientState(GL_VERTEX_ARRAY);
	}
}

bool _FASTCALL Render::_BindModel(Mesh *model,VBOMesh *)
{
	if (!model) return false;
	if ((p_lastelements!=model->p_elements) || (p_lastelements==0)) {
		if (model->p_elementCount == 0) return false;

		_InterleavedArrays(model->p_elementFormat,0,model->p_elements);
	}
	p_lastelements=model->p_elements;
	return true;
}

bool _FASTCALL Render::_BindModelVBO(Mesh *model,VBOMesh *vbo)
{
	sFunctionsGLContext &functions=GlContext::p_current->functions();
	if ((!model) || (!vbo)) return false;
	if (vbo->elements==0) {
		int s=Mesh::_elementSize(model->p_elementFormat);
		if (model->p_elementCount <= 0) return false;
		functions.GenBuffers(1,&vbo->elements);
		functions.BindBuffer(GL_ARRAY_BUFFER_ARB,vbo->elements);
		functions.BufferData(GL_ARRAY_BUFFER_ARB,s*model->p_elementCount,(GLvoid *)model->p_elements,GL_STATIC_DRAW_ARB);
	}
	if ((p_lastelements!=model->p_elements) || (p_lastelements==0)) {
		functions.BindBuffer(GL_ARRAY_BUFFER_ARB,vbo->elements);
		_InterleavedArrays(model->p_elementFormat,0,0);
		p_lastelements=model->p_elements;
	}

	if ((model->p_drawFormat & Mesh::_GL_NEED_INDEX_UPDATE)!=0) {
		_UpdateModelIndexVBO(model,vbo,0,model->p_indexCount);
		model->p_drawFormat^=Mesh::_GL_NEED_INDEX_UPDATE;
	}
	if ((model->p_drawFormat & Mesh::_GL_NEED_ELEMENT_UPDATE)!=0) {
		_UpdateModelElementVBO(model,vbo,0,model->p_elementCount);
		model->p_drawFormat^=Mesh::_GL_NEED_ELEMENT_UPDATE;
	}
	return true;
}

bool _FASTCALL Render::_DrawBindModel(Mesh *model,VBOMesh *)
{
	sFunctionsGLContext &functions=GlContext::p_current->functions();
	if (!model) return false;
	if ((model->p_indexCount==0) || (model->p_index == NULL)) return false;
	functions.DrawElements(model->p_drawFormat & Mesh::_GL_MASK,model->p_indexCount,GL_UNSIGNED_INT,model->p_index);
	return true;
}

bool _FASTCALL Render::_DrawBindModelVBO(Mesh *model,VBOMesh *vbo)
{
	sFunctionsGLContext &functions=GlContext::p_current->functions();
	if ((!model) || (!vbo)) return false;
	if ((model->p_indexCount == 0) || (model->p_index == NULL)) return false;
	if (vbo->index == 0) {
		functions.GenBuffers(1,&vbo->index);
		functions.BindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,vbo->index);
		functions.BufferData(GL_ELEMENT_ARRAY_BUFFER_ARB,(sizeof(GlIndex))*model->p_indexCount,(GLvoid *)model->p_index,GL_STATIC_DRAW_ARB);
	} else functions.BindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,vbo->index);
	functions.DrawElements(model->p_drawFormat & Mesh::_GL_MASK,model->p_indexCount,GL_UNSIGNED_INT,0);
	return true;
}

void _FASTCALL Render::_UnBindModel()
{
	sFunctionsGLContext &functions=GlContext::p_current->functions();
	p_lastelements=0;
	functions.DisableClientState(GL_VERTEX_ARRAY);
	functions.DisableClientState(GL_NORMAL_ARRAY);
	functions.DisableClientState(GL_COLOR_ARRAY);
	functions.DisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void _FASTCALL Render::_UnBindModelVBO()
{
	sFunctionsGLContext &functions=GlContext::p_current->functions();
	p_lastelements=0;
	functions.DisableClientState(GL_VERTEX_ARRAY);
	functions.DisableClientState(GL_NORMAL_ARRAY);
	functions.DisableClientState(GL_COLOR_ARRAY);
	functions.DisableClientState(GL_TEXTURE_COORD_ARRAY);
	functions.BindBuffer(GL_ARRAY_BUFFER_ARB,0);
	functions.BindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,0);
}

void _FASTCALL Render::_UpdateModelElement(Mesh *,VBOMesh *,int ,int )
{
	//lastelements=_model->p_elements;
}

void _FASTCALL Render::_UpdateModelElementVBO(Mesh *model,VBOMesh *vbo,int _id,int _count)
{	
	sFunctionsGLContext &functions=GlContext::p_current->functions();
	int s=Mesh::_elementSize(model->p_elementFormat);
	if (!vbo->elements) {
		functions.GenBuffers(1,&vbo->elements);
		functions.BindBuffer(GL_ARRAY_BUFFER_ARB,vbo->elements);
		functions.BufferData(GL_ARRAY_BUFFER_ARB,s*model->p_elementCount,(GLvoid *)model->p_elements,GL_DYNAMIC_DRAW_ARB);
	} else {
		unsigned char *p=model->p_elements;
		_id=_id*s;
		p+=_id;
		functions.BindBuffer(GL_ARRAY_BUFFER_ARB,vbo->elements);
		functions.BufferSubData(GL_ARRAY_BUFFER_ARB,_id,s*_count,(GLvoid *)p);
	}
	//lastelements=_model->Elements;
}

void _FASTCALL Render::_UpdateModelIndex(Mesh *,VBOMesh *,int ,int )
{
}

void _FASTCALL Render::_UpdateModelIndexVBO(Mesh *model,VBOMesh *vbo,int _id,int _count)
{	
	sFunctionsGLContext &functions=GlContext::p_current->functions();
	if (!vbo->index) {
		functions.GenBuffers(1,&vbo->index);
		functions.BindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,vbo->index);
		functions.BufferData(GL_ELEMENT_ARRAY_BUFFER_ARB,(sizeof(GlIndex))*model->p_indexCount,(GLvoid *)model->p_index,GL_DYNAMIC_DRAW_ARB);
	} else {
		unsigned int *p=(unsigned int *)model->p_index;
		p+=_id;
		_id=_id*4;
		functions.BindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,vbo->index);
		functions.BufferSubData(GL_ELEMENT_ARRAY_BUFFER_ARB,_id,_count*(sizeof(GlIndex)),(GLvoid *)p);
	}
}

}

OPTIMIZE_OFF;

#endif
