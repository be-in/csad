/*
 *  osxrender.cpp
 *
 *  Created on: 13.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>

#if defined (OS_OSX)

#include <platform.h>
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

void Render::initialize(void * c)
{
	if ((!c) || ((Context_P*)c)->initialize) return;
	Info();
	glReadExtention((Context_P*)c);
	//DrawModel=&_DrawModelVBO;
	//DrawLodModel=&_DrawLodModelVBO;
	((Context_P*)c)->BindModel=(tfFASTCALL_bool_FUNC_p_p)&_BindModel;
	((Context_P*)c)->DrawBindModel=(tfFASTCALL_bool_FUNC_p_p)&_DrawBindModel;
	//DrawBindLodModel=&_DrawBindLodModelVBO;
	((Context_P*)c)->UpdateModelElement=(tfFASTCALL_PROC_p_p_int_int)&_UpdateModelElement;
	((Context_P*)c)->UpdateModelIndex=(tfFASTCALL_PROC_p_p_int_int)&_UpdateModelIndex;
	((Context_P*)c)->UnBindModel=(tfFASTCALL_PROC)&_UnBindModel;

	if (((Context_P*)c)->_GL_ARB_vertex_buffer_object) {
		((Context_P*)c)->BindModel=(tfFASTCALL_bool_FUNC_p_p)&_BindModelVBO;
		((Context_P*)c)->DrawBindModel=(tfFASTCALL_bool_FUNC_p_p)&_DrawBindModelVBO;
		((Context_P*)c)->UpdateModelElement=(tfFASTCALL_PROC_p_p_int_int)&_UpdateModelElementVBO;
		((Context_P*)c)->UpdateModelIndex=(tfFASTCALL_PROC_p_p_int_int)&_UpdateModelIndexVBO;
		((Context_P*)c)->UnBindModel=(tfFASTCALL_PROC)&_UnBindModelVBO;
	}
	p_isVal=VALIDED;
}

void _FASTCALL Render::Info()
{
	char *str=(char*)glGetString(GL_RENDERER);
	Log::console("GL_RENDERER: %s",str);
	str=(char*)glGetString(GL_EXTENSIONS);
	//vertex_buffer_object=strstr(str,"vertex_array_object")!=0;
	Log::console("GL_EXTENSIONS: %s",str);
}

void _FASTCALL Render::setViewPort(int x,int y,int width,int height)
{
	glEnable(GL_SCISSOR_TEST);
	glViewport(x,y,width,height);
	glScissor(x,y,width,height);
}

void _FASTCALL Render::setClearColor(vector4f *color)
{
	glClearColor(color->x,color->y,color->z,color->w);
}

unsigned int _FASTCALL Render::GenTextures(int count,void* data)
{
	glGenTextures(count,(GLuint *)data);
	return glGetError();
}

int Render::GetTexure2DWidth()
{
	int val=0;
	glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_WIDTH,&val);
	//glGetTexLevelParameteriv(GL_TEXTURE_2D,_level,GL_TEXTURE_WIDTH,&val);
	return val;
}

int Render::GetTexure2DHeight()
{
	int val=0;
	glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_HEIGHT,&val);
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
	int internalformat=format;
	if (internalformat==GL_BGRA) internalformat=GL_RGBA;
	if (internalformat==GL_BGR) internalformat=GL_RGB;
	glTexImage2D(GL_TEXTURE_2D,level,internalformat,width,height,0,format,GL_UNSIGNED_BYTE,data);
}

bool Render::createContext(Display *display, GlContext * context)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;
	Context_P * mcontext=(Context_P *)(context->p_context);
	mcontext->context=glXCreateContext(mdisplay->display,mdisplay->vi,NULL,1);
	mcontext->initialize=0;
	mcontext->_GL_ARB_shader=false;
	mcontext->_GL_EXT_stencil_wrap=false;
	mcontext->_GL_ARB_vertex_buffer_object=false;
	mcontext->_GL_EXT_stencil_two_side=false;

	if (mcontext->context==0)
	{
		Log::console("Create context failed: 0x%x\n", glGetError());
		return false;
	}

	return true;
}

bool Render::destroyContext(Display *display, GlContext * context)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;
	Context_P * mcontext=(Context_P *)(context->p_context);
	glXDestroyContext(mdisplay->display,mcontext->context);
	/*if ()
	{
		Log::console("Destroy context failed: 0x%x\n", glGetError());
		return false;
	}*/
	mcontext->context=0;
	return true;
}

void * Render::getCurrentContex()
{
	return (void*)glXGetCurrentContext();
}

bool Render::MakeCurrent(Display * display,GlContext * context)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;
	bool ret=true;
	if (context==0) {
		if ((void*)glXGetCurrentContext()!=0)
			ret=glXMakeCurrent(mdisplay->display,mdisplay->surface, 0)!=0;
		GlContext::p_current=0;
		return ret;
	}
	Context_P * mcontext=(Context_P *)(context->p_context);
	if (mcontext->context!=(void*)glXGetCurrentContext())
		ret=glXMakeCurrent(mdisplay->display,mdisplay->surface, mcontext->context)!=0;
	if (ret) Render::initialize(mcontext);
	return ret;
}

void Render::setMipMap(int _min,int _max)
{
	//GL_GENERATE_MIPMAP
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, _max);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD, _min);
}

void Render::setFilterMode(int mag,int min)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
}

void Render::setMatrix(Camera* camera)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf((GLfloat*)camera->projMatrix());
	glMatrixMode(GL_MODELVIEW);
}

void Render::setMatrix(Camera* camera,vector4i &rect)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	vector4i rectV=camera->getViewPort(GlContext::getCurrent());
	//gluPickMatrix(rect.x+_rect.z*0.5,m_viewPort->getHeight()-_rect.y-_rect.w*0.5,_rect.z,_rect.w,(int*)&ViewPort);
	int x=rect.x+(int)(rect.z*0.5f);
	int y=rectV.w-rect.y-(int)(rect.w*0.5f);
    if ((rect.z > 0) && (rect.w > 0)) {
    	glTranslatef((float)(rectV.z - 2 * (x - rectV.x)) / rect.z,(float)(rectV.w - 2 * (y - rectV.y)) / rect.w, 0);
    	glScalef(rectV.z *1.0f/ rect.z, rectV.w *1.0f/ rect.w, 1.0);
    }

	glMultMatrixf((GLfloat*)camera->projMatrix());
	glMatrixMode(GL_MODELVIEW);
}

void _FASTCALL Render::DrawMesh(MeshFilter *mesh)
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
	if (mcontext->_GL_ARB_vertex_buffer_object) {
		if ((mmesh->p_drawFormat & Mesh::_GL_NEED_INDEX_UPDATE)!=0) {
			mcontext->UpdateModelIndex(mmesh,vbo,0,mmesh->p_indexCount);
			mmesh->p_drawFormat^=Mesh::_GL_NEED_INDEX_UPDATE;
		}
		if ((mmesh->p_drawFormat & Mesh::_GL_NEED_ELEMENT_UPDATE)!=0) {
			mcontext->UpdateModelElement(mmesh,vbo,0,mmesh->p_elementCount);
			mmesh->p_drawFormat^=Mesh::_GL_NEED_ELEMENT_UPDATE;
		}
	}
	mcontext->DrawBindModel(mmesh,vbo);
}

void _FASTCALL Render::FreeVBO(VBOMesh *mesh)
{
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	if (mcontext->_GL_ARB_vertex_buffer_object) {
		if (mesh->index) mcontext->glDeleteBuffers(1,&mesh->index);
		if (mesh->elements) mcontext->glDeleteBuffers(1,&mesh->elements);
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
	GLboolean isEnable;
	glGetBooleanv(GL_TEXTURE_2D,&isEnable);
	if (!isEnable) glEnable(GL_TEXTURE_2D);
	if (GlContext::p_current->p_lasttexture2d!=text) glBindTexture(GL_TEXTURE_2D,text);
	GlContext::p_current->p_lasttexture2d=text;
}

void Render::BindTexture2D(Texture2D* text)
{
	GLboolean isEnable;
	glGetBooleanv(GL_TEXTURE_2D,&isEnable);
	if (!isEnable) glEnable(GL_TEXTURE_2D);
	unsigned int id=text->texture();
	if (text->p_context!=GlContext::p_current) id=text->setContext(GlContext::p_current);
	if (GlContext::p_current->p_lasttexture2d!=id) glBindTexture(GL_TEXTURE_2D,id);
	GlContext::p_current->p_lasttexture2d=id;
}

bool Render::CompileSourceFile(GLuint _id,char *_filename)
{
	Context_P * mcontext=(Context_P *)(GlContext::getCurrent()->p_context);
	if (!mcontext->_GL_ARB_shader) return false;
	File file(_filename,File::READ);
	if (!file.open()) {
		GLint type;
		mcontext->glGetShaderiv(_id,GL_SHADER_TYPE,&type);
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
	if (!mcontext->_GL_ARB_shader) return false;
	GLint len=extFunctions.FindCMem(_src,0,65535);
	mcontext->glShaderSource (_id, 1, (const char **)&_src, &len);
	mcontext->glCompileShader (_id);
	if ( glGetError () == GL_INVALID_OPERATION )
	{
		GLint     errorPos;
		GLubyte * errorStr=0;

		glGetIntegerv ( GL_PROGRAM_ERROR_POSITION_ARB, &errorPos );

		//errorString = glGetString ( GL_PROGRAM_ERROR_STRING_ARB );

		Log::console("Error at position %i Line: \"%s\"",errorPos, errorStr);
		//printf ( "Error at position %d.\Line: \"%s\"\n", errorPos, errorStr );
	}
	return true;
}

void Render::UseProgram(GLuint _id)
{
	Context_P * mcontext=(Context_P *)(GlContext::getCurrent()->p_context);
	if (!mcontext->_GL_ARB_shader) return;
	GLuint cp;
	glGetIntegerv(GL_CURRENT_PROGRAM,(GLint*)&cp);
	if (cp==_id) return;
	mcontext->glUseProgram(_id);
}

void Render::LogProgram(GLuint _id)
{
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	if (!mcontext->_GL_ARB_shader) return;
	//value = 0;
	//mcontext->glGetProgramiv(_id, GL_LINK_STATUS, &value);
	GLint mvalue = 0;
	mcontext->glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &mvalue);
	if (mvalue > 1) {
		char *logbuf = new char [mvalue];
		GLint len;
		mcontext->glGetProgramInfoLog(_id, mvalue, &len, logbuf);		
		Log::console("%s",logbuf);
		delete [] logbuf;
	}
}

void Render::DeleteProgram(GLuint _id)
{
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	if (!mcontext->_GL_ARB_shader) return;
	if (!_id) return;
	GLint vs;
	mcontext->glGetProgramiv(_id,GL_VERTEX_SHADER,&vs);
	if (vs) mcontext->glDeleteShader(vs);
	GLint fs;
	mcontext->glGetProgramiv(_id,GL_FRAGMENT_SHADER,&fs);
	if (fs) mcontext->glDeleteShader(fs);
	mcontext->glDeleteProgram(_id);
}

void Render::Uniform1f(char *_name,float _x)
{
	GLuint cp;
	glGetIntegerv(GL_CURRENT_PROGRAM,(GLint*)&cp);
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	mcontext->glUniform1f(mcontext->glGetUniformLocation(cp,_name),_x);
}

void Render::Uniform2f(char *_name,float _x,float _y)
{
	GLuint cp;
	glGetIntegerv(GL_CURRENT_PROGRAM,(GLint*)&cp);
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	mcontext->glUniform2f(mcontext->glGetUniformLocation(cp,_name),_x,_y);
}

void Render::Uniform3f(char *_name,float _x,float _y,float _z)
{
	GLuint cp;
	glGetIntegerv(GL_CURRENT_PROGRAM,(GLint*)&cp);
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	mcontext->glUniform3f(mcontext->glGetUniformLocation(cp,_name),_x,_y,_z);
}

void Render::Uniform4f(char *_name,float _x,float _y,float _z,float _w)
{
	GLuint cp;
	glGetIntegerv(GL_CURRENT_PROGRAM,(GLint*)&cp);
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	mcontext->glUniform4f(mcontext->glGetUniformLocation(cp,_name),_x,_y,_z,_w);
}

void _FASTCALL Render::Finish()
{
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	if (mcontext) if (mcontext->glSwapIntervalEXT) {
		if (!GlContext::p_current->p_parent->isVSync()) {
			if (mcontext->glSwapIntervalEXT(0));
		} else {
			if (mcontext->glSwapIntervalEXT(1));
		}
	}
	glFlush();
	glFinish();
}

void _FASTCALL Render::Buffers(Display *display)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;
	if (GlContext::p_current) glXSwapBuffers(mdisplay->display,mdisplay->surface);
}

void _FASTCALL Render::UnBindAll()
{
	GlContext::p_current->p_lasttexture2d=-1;
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	mcontext->UnBindModel();
}

void Render::_InterleavedArrays(unsigned int format,unsigned int item,unsigned char *pointer)
{
	int s=Mesh::_elementSize(format);
	pointer+=item*s;
	int c=0;
	bool textenable=false;
	for (int i=0;i<6;i++) {
		c=Mesh::_elementSize(format,i);
		if (c>0) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(Mesh::_elementSubCount(format,i),GL_FLOAT, s, (GLvoid *)(pointer));
			pointer+=c;
			textenable=true;
		}
	}
	if (!textenable) {
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	c=Mesh::_elementSize(format,6);
	if (c>0) {
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(Mesh::_elementSubCount(format,6), GL_FLOAT, s, (GLvoid *)(pointer));
		pointer+=c;
	} else {
		glDisableClientState(GL_COLOR_ARRAY);
	}

	c=Mesh::_elementSize(format,7);
	if (c>0) {
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, s, (GLvoid *)(pointer));
		pointer+=c;
	} else {
		glDisableClientState(GL_NORMAL_ARRAY);
	}

	c=Mesh::_elementSize(format,8);
	if (c>0) {
		glEnableClientState(GL_VERTEX_ARRAY);
		int cc=Mesh::_elementSubCount(format,8);
		if (cc*4<c) {
			glVertexPointer(cc, GL_DOUBLE, s, (GLvoid *)(pointer));
		} else {
			glVertexPointer(cc, GL_FLOAT, s, (GLvoid *)(pointer));
		}
		pointer+=c;
	} else {
		glDisableClientState(GL_VERTEX_ARRAY);
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
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	if ((!model) || (!vbo)) return false;
	if (vbo->elements==0) {
		int s=Mesh::_elementSize(model->p_elementFormat);
		if (model->p_elementCount <= 0) return false;
		mcontext->glGenBuffers(1,&vbo->elements);
		mcontext->glBindBuffer(GL_ARRAY_BUFFER_ARB,vbo->elements);
		mcontext->glBufferData(GL_ARRAY_BUFFER_ARB,s*model->p_elementCount,(GLvoid *)model->p_elements,GL_STATIC_DRAW_ARB);
	}
	if ((p_lastelements!=model->p_elements) || (p_lastelements==0)) {
		mcontext->glBindBuffer(GL_ARRAY_BUFFER_ARB,vbo->elements);
		_InterleavedArrays(model->p_elementFormat,0,0);
		p_lastelements=model->p_elements;
	}
	return true;
}

bool _FASTCALL Render::_DrawBindModel(Mesh *model,VBOMesh *)
{
	if (!model) return false;
	if ((model->p_indexCount==0) || (model->p_index == NULL)) return false;
	glDrawElements(model->p_drawFormat & Mesh::_GL_MASK,model->p_indexCount,GL_UNSIGNED_INT,model->p_index);
	return true;
}

bool _FASTCALL Render::_DrawBindModelVBO(Mesh *model,VBOMesh *vbo)
{
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	if ((!model) || (!vbo)) return false;
	if ((model->p_indexCount == 0) || (model->p_index == NULL)) return false;
	if (vbo->index == 0) {
		mcontext->glGenBuffers(1,&vbo->index);
		mcontext->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,vbo->index);
		mcontext->glBufferData(GL_ELEMENT_ARRAY_BUFFER_ARB,(sizeof(GlIndex))*model->p_indexCount,(GLvoid *)model->p_index,GL_STATIC_DRAW_ARB);
	} else mcontext->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,vbo->index);
	glDrawElements(model->p_drawFormat & Mesh::_GL_MASK,model->p_indexCount,GL_UNSIGNED_INT,0);
	return true;
}

void _FASTCALL Render::_UnBindModel()
{
	p_lastelements=0;
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void _FASTCALL Render::_UnBindModelVBO()
{
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	p_lastelements=0;
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	mcontext->glBindBuffer(GL_ARRAY_BUFFER_ARB,0);
	mcontext->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,0);
}

void _FASTCALL Render::_UpdateModelElement(Mesh *,VBOMesh *,int ,int )
{
	//lastelements=_model->p_elements;
}

void _FASTCALL Render::_UpdateModelElementVBO(Mesh *model,VBOMesh *vbo,int _id,int _count)
{	
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	int s=Mesh::_elementSize(model->p_elementFormat);
	if (!vbo->elements) {
		mcontext->glGenBuffers(1,&vbo->elements);
		mcontext->glBindBuffer(GL_ARRAY_BUFFER_ARB,vbo->elements);
		mcontext->glBufferData(GL_ARRAY_BUFFER_ARB,s*model->p_elementCount,(GLvoid *)model->p_elements,GL_DYNAMIC_DRAW_ARB);
	} else {
		unsigned char *p=model->p_elements;
		_id=_id*s;
		p+=_id;
		mcontext->glBindBuffer(GL_ARRAY_BUFFER_ARB,vbo->elements);
		mcontext->glBufferSubData(GL_ARRAY_BUFFER_ARB,_id,s*_count,(GLvoid *)p);
	}
	//lastelements=_model->Elements;
}

void _FASTCALL Render::_UpdateModelIndex(Mesh *,VBOMesh *,int ,int )
{
}

void _FASTCALL Render::_UpdateModelIndexVBO(Mesh *model,VBOMesh *vbo,int _id,int _count)
{	
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	if (!vbo->index) {
		mcontext->glGenBuffers(1,&vbo->index);
		mcontext->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,vbo->index);
		mcontext->glBufferData(GL_ELEMENT_ARRAY_BUFFER_ARB,(sizeof(GlIndex))*model->p_indexCount,(GLvoid *)model->p_index,GL_DYNAMIC_DRAW_ARB);
	} else {
		unsigned int *p=(unsigned int *)model->p_index;
		p+=_id;
		_id=_id*4;
		mcontext->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,vbo->index);
		mcontext->glBufferSubData(GL_ELEMENT_ARRAY_BUFFER_ARB,_id,_count*(sizeof(GlIndex)),(GLvoid *)p);
	}
}

bool Render::_choosePixelFormat(Display * display,bool format,bool gl,int r,int g,int b,int a,int depth,int stencil,int sample)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;

	int size=3;
	if (gl) size+=2;
	if (r>0) size+=2;
	if (g>0) size+=2;
	if (b>0) size+=2;
	if (a>0) size+=2;
	if (depth>0) size+=2;
	if (stencil>0) size+=2;

	int *attribute_list = new int[size];
	int index=0;
	attribute_list[index]=GLX_RGBA;
	index++;
	attribute_list[index]=GLX_DOUBLEBUFFER;
	index++;
	if (gl) {
		attribute_list[index]=GLX_USE_GL;
		attribute_list[index+1]=1;
		index+=2;
	}
	if (r>0) {
		attribute_list[index]=GLX_RED_SIZE;
		attribute_list[index+1]=r;
		index+=2;
	}
	if (g>0) {
		attribute_list[index]=GLX_GREEN_SIZE;
		attribute_list[index+1]=g;
		index+=2;
	}
	if (b>0) {
		attribute_list[index]=GLX_BLUE_SIZE;
		attribute_list[index+1]=b;
		index+=2;
	}
	if (a>0) {
		attribute_list[index]=GLX_ALPHA_SIZE;
		attribute_list[index+1]=a;
		index+=2;
	}
	if (depth>0) {
		attribute_list[index]=GLX_DEPTH_SIZE;
		attribute_list[index+1]=depth;
		index+=2;
	}
	if (stencil>0) {
		attribute_list[index]=GLX_STENCIL_SIZE;
		attribute_list[index+1]=stencil;
		index+=2;
	}
	attribute_list[index]=None;

	mdisplay->vi = glXChooseVisual( mdisplay->display, mdisplay->scrnum, attribute_list );

	delete[] attribute_list;

	if (!mdisplay->vi) return false;

	return true;
}

/*
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
	case WM_NCPAINT:
	case WM_ERASEBKGND:
	case WM_SETREDRAW:
	case WM_PAINTICON:
	case WM_SYSCOLORCHANGE:
	case WM_ICONERASEBKGND:
		break;
	default:
		return DefWindowProc(hWnd,message,wParam,lParam);
	}
	return 0;
}*/

//HWND lastSurface=0;

bool Render::_createDisplay(Display * display,int devid,int dispid)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;

	Atom wmDelete;
	bt::BaseShortString str=":";
	char buff[16];
	csad::Log::tocahr(buff,15,"%i",devid);
	str+=buff;
	str+='.';
	csad::Log::tocahr(buff,15,"%i",dispid);
	str+=buff;

	mdisplay->display = XOpenDisplay(str.str());

	if (!mdisplay->display) {
		Log::console("Error: couldn't open display %s\n", str.str());
		return false;
	}
	mdisplay->vi=0;

	mdisplay->scrnum = DefaultScreen( mdisplay->display );

	if (_choosePixelFormat(display,true,true,8,8,8,8,32,0,1)) {
		Log::console("PixelFormat: 32 bit Depth 32 bit Antialiasing GL enable");
	} else if (_choosePixelFormat(display,true,true,8,8,8,8,24,0,1)) {
		Log::console("PixelFormat: 32 bit Depth 24 bit Antialiasing GL enable");
	} else if (_choosePixelFormat(display,true,true,8,8,8,8,16,0,1)) {
		Log::console("PixelFormat: 32 bit Depth 16 bit Antialiasing GL enable");
	} else if (_choosePixelFormat(display,true,true,8,8,8,8,16,0,0)) {
		Log::console("PixelFormat: 32 bit Depth 16 bit GL enable");
	} else if (_choosePixelFormat(display,true,true,8,8,8,0,16,0,0)) {
		Log::console("PixelFormat: 24 bit Depth 16 bit GL enable");
	} else if (_choosePixelFormat(display,true,true,4,4,4,4,16,0,0)) {
		Log::console("PixelFormat: 16 bit Depth 16 bit GL enable");
	} else if (_choosePixelFormat(display,true,true,4,4,4,0,16,0,0)) {
		Log::console("PixelFormat: 16 bit Depth 16 bit GL enable");
	} else if (_choosePixelFormat(display,true,true,5,5,5,1,0,0,0)) {
		Log::console("PixelFormat: 16 bit GL enable");
	} else if (_choosePixelFormat(display,true,true,4,4,4,4,0,0,0)) {
		Log::console("PixelFormat: 16 bit GL enable");
	} else if (_choosePixelFormat(display,true,true,4,4,4,0,0,0,0)) {
		Log::console("PixelFormat: 16 bit GL enable");
	} else if (_choosePixelFormat(display,true,false,8,8,8,8,0,0,0)) {
		Log::console("PixelFormat: 32 bit Depth 16 bit");
	} else if (_choosePixelFormat(display,true,false,5,5,5,1,0,0,0)) {
		Log::console("PixelFormat: 16 bit");
	} else if (_choosePixelFormat(display,true,false,4,4,4,4,0,0,0)) {
		Log::console("PixelFormat: 16 bit");
	} else if (_choosePixelFormat(display,true,true,0,0,0,0,0,0,0)) {
		Log::console("PixelFormat: Low GL enable");
	} else if (_choosePixelFormat(display,true,false,0,0,0,0,0,0,0)) {
		Log::console("PixelFormat: Low");
	} else if (_choosePixelFormat(display,false,false,0,0,0,0,0,0,0)) {
		Log::console("PixelFormat: Low");
	} else {
		Log::console("Unable to choose pixel format");
		return false;
	}

	XSetWindowAttributes attr;
	Window root = RootWindow( mdisplay->display, mdisplay->vi->screen );
	XWindowAttributes getWinAttr;
	XGetWindowAttributes(mdisplay->display, root, &getWinAttr);
	mdisplay->posx=getWinAttr.x;
	mdisplay->posy=getWinAttr.y;
	mdisplay->xres=getWinAttr.width;
	mdisplay->yres=getWinAttr.height;
	mdisplay->colorres=4;

	attr.background_pixel = 0;
	attr.border_pixel = 0;
	attr.colormap = XCreateColormap( mdisplay->display, root, mdisplay->vi->visual, AllocNone);
	attr.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask;
	int mask = CWBorderPixel | CWColormap | CWEventMask;

	mdisplay->surface=XCreateWindow(mdisplay->display,root,0, 0,mdisplay->xres,mdisplay->yres,0,mdisplay->vi->depth,InputOutput,mdisplay->vi->visual,mask,&attr);

	if (!mdisplay->surface) {
		Log::console("XCreateWindow: couldn't create window \n");
		return false;
	}
/*
 X Error of failed request:  BadValue (integer parameter out of range for operation)
  Major opcode of failed request:  1 (X_CreateWindow)
  Value in failed request:  0xd8
  Serial number of failed request:  25
  Current serial number in output stream:  26
 */
	XSizeHints sizehints;
	sizehints.x = 0;
	sizehints.y = 0;
	sizehints.width  = mdisplay->xres;
	sizehints.height = mdisplay->yres;
	sizehints.flags = USSize | USPosition;
	wmDelete = XInternAtom(mdisplay->display, "WM_DELETE_WINDOW", True);
	XSetWMProtocols(mdisplay->display, mdisplay->surface, &wmDelete, 1);
	XSetNormalHints(mdisplay->display, mdisplay->surface, &sizehints);
	XSetStandardProperties(mdisplay->display, mdisplay->surface, "unname", "unname",None, (char **)NULL, 0, &sizehints);

	XMapRaised(mdisplay->display, mdisplay->surface);
	//XMapWindow(mdisplay->display,mdisplay->surface);

	XAllowEvents(mdisplay->display,AsyncBoth,CurrentTime);
	XGrabPointer(mdisplay->display,mdisplay->surface,1,PointerMotionMask | ButtonPressMask | ButtonReleaseMask,GrabModeAsync,GrabModeAsync,None,None,CurrentTime);

	return true;
}

/*bool Render::_destroyDisplay(Display * display)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;

	XFree(mdisplay->vi);
	XCloseDisplay(mdisplay->display);
	return true;
}*/

TYPEINFO(Render)

}

OPTIMIZE_OFF;

#endif
