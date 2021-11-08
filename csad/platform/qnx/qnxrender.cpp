/*
 * qnxrender.cpp
 *
 *  Created on: 13.08.2013
 *      Author: Пантелеймонов Александр
 */

#include <platform/platformapi.h>

#if defined (OS_QNX)

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
#include "qnxglextention.h"
#include "csad/platform/localdisplay.h"

OPTIMIZE_ON;

namespace csad {

unsigned int Render::p_isVal;
unsigned char * Render::p_lastelements;

char *gfstrings[]={
		"no error",
		"memory allocation error",
		"error accessing io-display",
		"error accessing device",
		"error accessing shared memory",
		"error accessing dll/entrypoints",
		"thread registration failure",
		"invalid parameter",
		"resource in use",
		"unsupported operation",
		"bad configuration",
		"h/w not locked",
		"h/w level I/O error",
		"h/w locked; deadlock avoided",
		"target surface destroyed, due to modeswitch or power management",
		"Requested operation exceeded internal limits",
};

Render::Render()
{
	//vertex_buffer_object=false;
}

void Render::initialize(void *c)
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

void Render::Info()
{
	char *str=(char*)glGetString(GL_RENDERER);
	Log::console("GL_RENDERER: %s",str);
	str=(char*)glGetString(GL_EXTENSIONS);
	Log::console("GL_EXTENSIONS: %s",str);
}

void Render::setViewPort(int x,int y,int width,int height)
{
	glEnable(GL_SCISSOR_TEST);
	glViewport(x,y,width,height);
	glScissor(x,y,width,height);
}

void Render::setClearColor(vector4f *color)
{
	glClearColor(color->x,color->y,color->z,color->w);
}

unsigned int  Render::GenTextures(int count,void* data)
{
	glGenTextures(count,(GLuint *)data);
	return glGetError();
}

int Render::GetTexure2DWidth()
{
	int val=0;
	//glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_WIDTH,&val);
	//glGetTexLevelParameteriv(GL_TEXTURE_2D,_level,GL_TEXTURE_WIDTH,&val);
	return val;
}

int Render::GetTexure2DHeight()
{
	int val=0;
	//glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_HEIGHT,&val);
	return val;
}

int Render::formatFromBPP(int bpp,int format)
{
	if (bpp==4) if (format!=GL_RGBA) format=GL_RGBA;
	if (bpp==3)	if (format!=GL_RGB) format=GL_RGB;
	return format;
}

void Render::TexImage2D(int level,int format,int width,int height,void * data)
{
	glTexImage2D(GL_TEXTURE_2D,level,format,width,height,0,format,GL_UNSIGNED_BYTE,data);
}

bool Render::createContext(Display *display, GlContext * context)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;
	Context_P * mcontext=(Context_P *)context->p_context;
	mcontext->context=eglCreateContext(mdisplay->display, mdisplay->config, EGL_NO_CONTEXT, 0);
	mcontext->initialize=false;
	mcontext->_GL_ARB_shader=false;
	mcontext->_GL_EXT_stencil_wrap=false;
	mcontext->_GL_ARB_vertex_buffer_object=false;
	mcontext->_GL_EXT_stencil_two_side=false;
	if (mcontext->context==EGL_NO_CONTEXT)
	{
		Log::console("Create context failed: 0x%x\n", eglGetError());
		return false;
	}

	return true;
}

bool Render::destroyContext(Display *display, GlContext * context)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;
	Context_P * mcontext=(Context_P *)context->p_context;
	if (eglDestroyContext(mdisplay->display, mcontext->context))
	{
		Log::console("Destroy context failed: 0x%x\n", eglGetError());
		return false;
	}
	mcontext->context=0;
	return true;
}

void * Render::getCurrentContex()
{
	return (void*)eglGetCurrentContext();
}

bool Render::MakeCurrent(Display * display,GlContext * context)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;
	bool ret=true;
	if (context==0) {
		eglMakeCurrent(mdisplay->display, mdisplay->surface, mdisplay->surface, 0);
		GlContext::p_current=0;
		return ret;
	}
	Context_P * mcontext = (Context_P *)context->p_context;
	if (mcontext->context!=(void*)eglGetCurrentContext())
		ret=eglMakeCurrent(mdisplay->display, mdisplay->surface, mdisplay->surface, mcontext->context)!=EGL_FALSE;
	if (ret) Render::initialize(mcontext);
	return ret;
}

void Render::setMipMap(int _min,int _max)
{
	//GL_GENERATE_MIPMAP
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, _max);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD, _min);
}

void Render::setFilterMode(int mag,int min)
{
	glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
	glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
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

	//gluPickMatrix(rect.x+_rect.z*0.5,rectV.w-_rect.y-_rect.w*0.5,_rect.z,_rect.w,(int*)&ViewPort);
	int x=rect.x+rect.z*0.5;
	int y=rectV.w-rect.y-rect.w*0.5;
    if ((rect.z > 0) && (rect.w > 0)) {
    	glTranslatef((rectV.z - 2 * (x - rectV.x)) / rect.z,(rectV.w - 2 * (y - rectV.y)) / rect.w, 0);
    	glScalef(rectV.z *1.0f / rect.z, rectV.w *1.0f / rect.w, 1.0);
    }

	glMultMatrixf((GLfloat*)camera->projMatrix());
	glMatrixMode(GL_MODELVIEW);
}

void Render::DrawMesh(MeshFilter *mesh)
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
	if (!GlContext::p_current) return;
	//GLboolean isEnable;
	//glGetBooleanv(GL_TEXTURE_2D,&isEnable);
	//if (!isEnable) glEnable(GL_TEXTURE_2D);
	//unsigned int bind;
	//glGetIntegerv(GL_TEXTURE_BINDING_2D,(int*)&bind);
	if (GlContext::p_current->p_lasttexture2d!=text) glBindTexture(GL_TEXTURE_2D,text);
	GlContext::p_current->p_lasttexture2d=text;
}

void Render::BindTexture2D(Texture2D* text)
{
	if (!GlContext::p_current) return;
	//GLboolean isEnable;
	//glGetBooleanv(GL_TEXTURE_2D,&isEnable);
	//if (!isEnable) glEnable(GL_TEXTURE_2D);
	unsigned int id=text->texture();
	if (text->p_context!=GlContext::p_current) id=text->setContext(GlContext::p_current);
	//unsigned int bind;
	//glGetIntegerv(GL_TEXTURE_BINDING_2D,(int*)&bind);
	if (GlContext::p_current->p_lasttexture2d!=id) glBindTexture(GL_TEXTURE_2D,id);
	GlContext::p_current->p_lasttexture2d=id;
}

void _FASTCALL Render::Finish()
{
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	if (mcontext)
		if (!GlContext::p_current->p_parent->isVSync()) {
			if (eglSwapInterval(((LocalDisplay*)GlContext::p_current->p_parent)->p_display.display,0));
		} else {
			if (eglSwapInterval(((LocalDisplay*)GlContext::p_current->p_parent)->p_display.display,1));
		}
	//glFlush();
	//glFinish();
}

void _FASTCALL Render::Buffers(Display *display)
{
    eglWaitGL();
    eglSwapBuffers(((LocalDisplay*)display)->p_display.display,((LocalDisplay*)display)->p_display.surface);
}

void _FASTCALL Render::UnBindAll()
{
	if (!GlContext::p_current) return;
	GlContext::p_current->p_lasttexture2d=-1;
	Context_P * mcontext=(Context_P *)(GlContext::p_current->p_context);
	mcontext->UnBindModel();
}

void Render::_InterleavedArrays(unsigned int format,unsigned int item,unsigned char *pointer)
{
	int s=Mesh::_elementSize(format);
	pointer+=item*s;
	int c=0;
	for (int i=0;i<6;i++) {
		c=Mesh::_elementSize(format,i);
		if (c>0) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(Mesh::_elementSubCount(format,i),GL_FLOAT, s, (GLvoid *)(pointer));
			pointer+=c;
		}
	}

	c=Mesh::_elementSize(format,6);
	if (c>0) {
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(Mesh::_elementSubCount(format,6), GL_FLOAT, s, (GLvoid *)(pointer));
		pointer+=c;
	}

	c=Mesh::_elementSize(format,7);
	if (c>0) {
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, s, (GLvoid *)(pointer));
		pointer+=c;
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
	}
}

bool Render::_BindModel(Mesh *model,VBOMesh *)
{
	if (!model) return false;
	if ((p_lastelements!=model->p_elements) || (p_lastelements==0)) {
		if (model->p_elementCount == 0) return false;

		_InterleavedArrays(model->p_elementFormat,0,model->p_elements);
		p_lastelements=model->p_elements;
	}
	return true;
}

bool Render::_BindModelVBO(Mesh *model,VBOMesh *vbo)
{
	if ((!model) || (!vbo)) return false;
	if (vbo->elements==0) {
		int s=Mesh::_elementSize(model->p_elementFormat);
		if (model->p_elementCount <= 0) return false;
		glGenBuffers(1,&vbo->elements);
		glBindBuffer(GL_ARRAY_BUFFER,vbo->elements);
		glBufferData(GL_ARRAY_BUFFER,s*model->p_elementCount,(GLvoid *)model->p_elements,GL_STATIC_DRAW);
	}
	if ((p_lastelements!=model->p_elements) || (p_lastelements==0)) {
		glBindBuffer(GL_ARRAY_BUFFER,vbo->elements);
		_InterleavedArrays(model->p_elementFormat,0,0);
		p_lastelements=model->p_elements;
	}
	return true;
}

bool Render::_DrawBindModel(Mesh *model,VBOMesh *)
{
	if (!model) return false;
	if ((model->p_indexCount==0) || (model->p_index == NULL)) return false;
	glDrawElements(model->p_drawFormat & Mesh::_GL_MASK,model->p_indexCount,GL_UNSIGNED_SHORT,model->p_index);
	return true;
}

bool Render::_DrawBindModelVBO(Mesh *model,VBOMesh *vbo)
{
	if ((!model) || (!vbo)) return false;
	if ((model->p_indexCount == 0) || (model->p_index == NULL)) return false;
	if (vbo->index == 0) {
		glGenBuffers(1,&vbo->index);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbo->index);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,(sizeof(GlIndex))*model->p_indexCount,(GLvoid *)model->p_index,GL_STATIC_DRAW);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbo->index);
	glDrawElements(model->p_drawFormat & Mesh::_GL_MASK,model->p_indexCount,GL_UNSIGNED_SHORT,0);
	return true;
}

void Render::_UnBindModel()
{
	p_lastelements=0;
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
void Render::_UnBindModelVBO()
{
	p_lastelements=0;
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
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
		glGenBuffers(1,&vbo->elements);
		glBindBuffer(GL_ARRAY_BUFFER,vbo->elements);
		glBufferData(GL_ARRAY_BUFFER,s*model->p_elementCount,(GLvoid *)model->p_elements,GL_DYNAMIC_DRAW_ARB);
	} else {
		unsigned char *p=model->p_elements;
		_id=_id*s;
		p+=_id;
		glBindBuffer(GL_ARRAY_BUFFER_ARB,vbo->elements);
		glBufferSubData(GL_ARRAY_BUFFER_ARB,_id,s*_count,(GLvoid *)p);
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
		glGenBuffers(1,&vbo->index);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,vbo->index);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER_ARB,(sizeof(GlIndex))*model->p_indexCount,(GLvoid *)model->p_index,GL_DYNAMIC_DRAW_ARB);
	} else {
		unsigned int *p=(unsigned int *)model->p_index;
		p+=_id;
		_id=_id*4;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,vbo->index);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER_ARB,_id,_count*(sizeof(GlIndex)),(GLvoid *)p);
	}
}

bool Render::_choosePixelFormat(Display * display,bool format,bool gl,int r,int g,int b,int a,int depth,int stencil,int sample)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;

	int size=1;
	if (format) size+=2;
	if (gl) size+=2;
	if (r>0) size+=2;
	if (g>0) size+=2;
	if (b>0) size+=2;
	if (a>0) size+=2;
	if (depth>0) size+=2;
	if (stencil>0) size+=2;
	if (sample>0) size+=2;
#if _NTO_VERSION < 660
#else
	size+=2;
#endif

	EGLint *attribute_list = new EGLint[size];
	int index=0;
	if (format) {
		attribute_list[index]=EGL_NATIVE_VISUAL_ID;
		index+=2;
	}
	if (gl) {
		attribute_list[index]=EGL_NATIVE_RENDERABLE;
		attribute_list[index+1]=EGL_TRUE;
		index+=2;
	}
	if (r>0) {
		attribute_list[index]=EGL_RED_SIZE;
		attribute_list[index+1]=r;
		index+=2;
	}
	if (g>0) {
		attribute_list[index]=EGL_GREEN_SIZE;
		attribute_list[index+1]=g;
		index+=2;
	}
	if (b>0) {
		attribute_list[index]=EGL_BLUE_SIZE;
		attribute_list[index+1]=b;
		index+=2;
	}
	if (a>0) {
		attribute_list[index]=EGL_ALPHA_SIZE;
		attribute_list[index+1]=a;
		index+=2;
	}
	if (depth>0) {
		attribute_list[index]=EGL_DEPTH_SIZE;
		attribute_list[index+1]=depth;
		index+=2;
	}
	if (stencil>0) {
		attribute_list[index]=EGL_STENCIL_SIZE;
		attribute_list[index+1]=stencil;
		index+=2;
	}
	if (sample>0) {
		attribute_list[index]=EGL_SURFACE_TYPE;
		attribute_list[index+1]=EGL_WINDOW_BIT;
		index+=2;
	}

#if _NTO_VERSION < 660
#else
	attribute_list[index]=EGL_SAMPLE_BUFFERS;
	attribute_list[index+1]=sample;
	index+=2;
#endif
	attribute_list[index]=EGL_NONE;

	EGLint num_config;

	bool ret=false;
#if _NTO_VERSION < 660
	for (int it=0;; it++)
	{
		// Walk through all possible pixel formats for this layer
		int idt=gf_layer_query(mdisplay->layer, it, &mdisplay->linfo);
		if (idt==-1)
		{
			Log::console("Couldn't find a compatible frame buffer configuration on layer %d", mdisplay->disp_info.main_layer_index);
			return false;
		}

		if (format) attribute_list[1]=mdisplay->linfo.format;

		// Look for a compatible EGL frame buffer configuration
		if (eglChooseConfig(mdisplay->display, attribute_list, &mdisplay->config, 1, &num_config)==EGL_TRUE)
		{
			if (num_config>0)
			{
				ret=true;
				break;
			} else {
				ret=false;
				break;
			}
		} else {
			ret=false;
			break;
		}
	}
#else
    if(!eglChooseConfig(mdisplay->display, attribute_list, &mdisplay->config, 1, &num_config)) {
		ret=false;
	} else {
		ret=true;
	}
#endif

	delete[] attribute_list;
	return ret;
}

bool Render::_createDisplay(Display * display,int devid,int dispid)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;

#if _NTO_VERSION < 660
	// initialize the graphics device
	int err=gf_dev_attach(&mdisplay->gfdev, GF_DEVICE_INDEX(devid), &mdisplay->info);
	if (err!=GF_ERR_OK)
	{
		if (err<16) {
			Log::console("gf_dev_attach() failed: %s",gfstrings[err]);
		} else {
			Log::console("gf_dev_attach() failed: %i",err);
		}
		return false;
	}

	// Setup the layer we will use
	err=gf_display_attach(&mdisplay->gf_disp, mdisplay->gfdev, dispid, &mdisplay->disp_info);
	if (err!=GF_ERR_OK)
	{
		if (err<16) {
			Log::console("gf_display_attach() failed: %s",gfstrings[err]);
		} else {
			Log::console("gf_display_attach() failed: %i",err);
		}
		return false;
	}

	// get an EGL display connection
	mdisplay->display=eglGetDisplay(mdisplay->gfdev);
	if (mdisplay->display==EGL_NO_DISPLAY)
	{
		Log::console("eglGetDisplay() failed");
		return false;
	}

	err=gf_layer_attach(&mdisplay->layer, mdisplay->gf_disp, mdisplay->disp_info.main_layer_index, GF_LAYER_ATTACH_PASSIVE);

	if (err!=GF_ERR_OK)
	{
		if (err<16) {
			Log::console("gf_layer_attach() failed: %s",gfstrings[err]);
		} else {
			Log::console("gf_layer_attach() failed: %i",err);
		}
	   return false;
	}

	// initialize the EGL display connection
	if (eglInitialize(mdisplay->display, NULL, NULL)!=EGL_TRUE)
	{
		Log::console("eglInitialize: error 0x%x", eglGetError());
		return false;
	}

	int num_config;
	if (eglChooseConfig(mdisplay->display, 0, 0, 0, &num_config)==EGL_TRUE)
	{
		if (num_config==0) {
			Log::console("OpenGL ES: have not pixel format");
			return false;
		} else {
			Log::console("OpenGL ES: have %i configuration",num_config);
		}
	} else {
		return false;
	}

	if (_choosePixelFormat(display,true,true,8,8,8,8,16,0,1)) {
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

	// create a 3D rendering target
	if (gf_3d_target_create(&mdisplay->target, mdisplay->layer, 0, 0, mdisplay->disp_info.xres, mdisplay->disp_info.yres, mdisplay->linfo.format)!=GF_ERR_OK)
	{
		Log::console("Unable to create rendering target");
		return false;
	}

	gf_layer_set_src_viewport(mdisplay->layer, 0, 0, mdisplay->disp_info.xres-1, mdisplay->disp_info.yres-1);
	gf_layer_set_dst_viewport(mdisplay->layer, 0, 0, mdisplay->disp_info.xres-1, mdisplay->disp_info.yres-1);
	gf_layer_enable(mdisplay->layer);

	/* create an EGL window surface */
	mdisplay->surface=eglCreateWindowSurface(mdisplay->display, mdisplay->config, mdisplay->target, NULL);
	if (mdisplay->surface==EGL_NO_SURFACE)
	{
		Log::console("Create surface failed: 0x%x\n", eglGetError());
		return false;
	}
	mdisplay->posx=0;
	mdisplay->posy=0;

#else

	screen_create_context(&mdisplay->scene,0); //SCREEN_DISPLAY_MANAGER_CONTEXT

	int ndisplays;
	if (screen_get_context_property_iv(mdisplay->scene,SCREEN_PROPERTY_DISPLAY_COUNT,&ndisplays)) {
		Log::console("screen_get_context_property_iv(SCREEN_PROPERTY_DISPLAY_COUNT)");
		return false;
	}
	if (dispid>=ndisplays) {
		Log::console("Too big display id");
		return false;
	}

	screen_display_t *screen_dlist = (screen_display_t *)new void*[ndisplays];
	if (screen_get_context_property_pv(mdisplay->scene, SCREEN_PROPERTY_DISPLAYS,(void **)screen_dlist)) {
		delete screen_dlist;
		return false;
	}
	mdisplay->posx=0;
	mdisplay->posy=0;
	int d[2];
	for (int i=0;i<dispid;i++) {
		screen_get_display_property_iv(screen_dlist[i], SCREEN_PROPERTY_SIZE, d);
		mdisplay->posx+=d[0];
	}
	mdisplay->posx=0;
	mdisplay->sdisplay=screen_dlist[dispid];
	delete screen_dlist;
	screen_get_display_property_iv(mdisplay->sdisplay, SCREEN_PROPERTY_SIZE, &mdisplay->width);

	// get an EGL display connection
	mdisplay->display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if (mdisplay->display==EGL_NO_DISPLAY)
	{
		Log::console("eglGetDisplay() failed");
		return false;
	}

	if (eglInitialize(mdisplay->display, NULL, NULL)!=EGL_TRUE)
	{
		Log::console("eglInitialize: error 0x%x", eglGetError());
		return false;
	}

	int num_config;
	if (eglChooseConfig(mdisplay->display, 0, 0, 0, &num_config)==EGL_TRUE)
	{
		if (num_config==0) {
			Log::console("OpenGL ES: have not pixel format");
			return false;
		} else {
			Log::console("OpenGL ES: have %i configuration",num_config);
		}
	} else {
		return false;
	}

	if (_choosePixelFormat(display,true,true,8,8,8,8,16,0,1)) {
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

	mdisplay->surface=eglCreateWindowSurface(mdisplay->display, mdisplay->config, mdisplay->screen_win, NULL);
	if (mdisplay->surface==EGL_NO_SURFACE)
	{
		Log::console("Create surface failed: 0x%x\n", eglGetError());
		return false;
	}

#endif

	return true;
}

bool Render::_destroyDisplay(Display * display)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;

#if _NTO_VERSION < 660

#else

	screen_destroy_context(mdisplay->scene);

#endif

	return true;
}

}

OPTIMIZE_OFF;

#endif
