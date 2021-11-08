/*
 * basesoftrender.cpp
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#if defined(CSAD_SOFT_RENDER) || defined(SOFT_RENDER_CSAD)

#include "basesoftrender.h"
#include <platform/glcontext.h>
#include <platform/platformfunctions.h>
#include <scene/meshfilter.h>
#include <scene/mesh.h>
#include "csad/platform/glextension.h"
#include "csad/platform/localdisplay.h"

OPTIMIZE_ON;

namespace csad {

union conv4b {
	float valfloat;
	_int32 valint;
	unsigned _int32 valuint;
	char valarray[4];
};

softGlContext *currentContext=0;

void softBasefunctions(Context_P * context)
{
	if (context->initialize) return;
	extFunctions.CleanMem(context,sizeof(Context_P));
	context->initialize=true;
}

void softReadExtention(Context_P *_context)
{
	if ((!_context) || (_context->initialize)) return;
	_context->initialize=true;
}

#define INITGLPROCS(module,name) void *local; \
	bt::tfSTDCALL_p_FUNC_p lGetProcAddress=(bt::tfSTDCALL_p_FUNC_p)module->getProc(name);
#define WGLProc(name,set,type) local=(void*)(lGetProcAddress((char*)name)); if (local) {set=(type)local;}// else {Log::console("WGLProc null %s",name);}
#define GLProc(name,set,type) local=(void*)(module->getProc(name)); if (local) {set=(type)local;}// else {Log::console("getProc null %s",name);}

void softInitGLFunctions(void *_conteiner)
{
	bt::sFunctionsGLContext *as=(bt::sFunctionsGLContext *)_conteiner;
	as->version=0;

	extFunctions.CleanMem(as,sizeof(bt::sFunctionsGLContext));

	as->AlphaFunc=(bt::tfSTDCALL_PROC_uint_float)glAlphaFunc;
	//GLProc("glBindBuffer",as->BindBuffer,bt::tfSTDCALL_PROC_uint_uint);
	as->BindTexture=(bt::tfSTDCALL_PROC_uint_uint)glBindTexture;
	as->BlendFunc=(bt::tfSTDCALL_PROC_uint_uint)glBlendFunc;
	//GLProc("glBufferData",as->BufferData,bt::tfSTDCALL_PROC_uint_int_p_uint);
	//GLProc("glBufferSubData",as->BufferSubData,bt::tfSTDCALL_PROC_uint_int_int_p);
	as->Color4f=(bt::tfSTDCALL_PROC_float_float_float_float)glColor4f;
	as->Color4fv=(bt::tfSTDCALL_PROC_p)glColor4fv;
	as->ColorPointer=(bt::tfSTDCALL_PROC_int_uint_int_p)glColorPointer;
	as->Clear=(bt::tfSTDCALL_PROC_uint)glClear;
	//GLProc("glClearAccum",as->ClearAccum,bt::tfSTDCALL_PROC_float_float_float_float);
	as->ClearColor=(bt::tfSTDCALL_PROC_float_float_float_float)glClearColor;
	as->ClearDepth=(bt::tfSTDCALL_PROC_double)glClearDepth;
	as->CullFace=(bt::tfSTDCALL_PROC_uint)glCullFace;
	//GLProc("glDeleteBuffers",as->DeleteBuffers,bt::tfSTDCALL_PROC_int_p);
	as->DeleteTextures=(bt::tfSTDCALL_PROC_int_p)glDeleteTextures;
	as->DepthFunc=(bt::tfSTDCALL_PROC_uint)glDepthFunc;
	as->Disable=(bt::tfSTDCALL_PROC_uint)glDisable;
	as->DisableClientState=(bt::tfSTDCALL_PROC_uint)glDisableClientState;
	as->DrawElements=(bt::tfSTDCALL_PROC_uint_int_uint_p)glDrawElements;
	as->Enable=(bt::tfSTDCALL_PROC_uint)glEnable;
	as->EnableClientState=(bt::tfSTDCALL_PROC_uint)glEnableClientState;
	as->Finish=(bt::tfSTDCALL_PROC)glFinish;
	as->Flush=(bt::tfSTDCALL_PROC)glFlush;
	//GLProc("glGenBuffers",as->GenBuffers,bt::tfSTDCALL_PROC_int_p);
	as->GenTextures=(bt::tfSTDCALL_PROC_int_p)glGenTextures;
	as->GetBooleanv=(bt::tfSTDCALL_PROC_uint_p)glGetBooleanv;
	//GLProc("glGetBufferParameteriv",as->GetBufferParameteriv,bt::tfSTDCALL_PROC_uint_uint_p);
	//GLProc("glGetBufferPointerv",as->GetBufferPointerv,bt::tfSTDCALL_PROC_uint_uint_p);
	as->GetError=(bt::tfSTDCALL_uint_FUNC)glGetError;
	as->GetFloatv=(bt::tfSTDCALL_PROC_uint_p)glGetFloatv;
	as->GetIntegerv=(bt::tfSTDCALL_PROC_uint_p)glGetIntegerv;
	//GLProc("glGetProgramiv",as->GetProgramiv,bt::tfSTDCALL_PROC_uint_uint_p);
	as->GetString=(bt::tfSTDCALL_p_FUNC_uint)glGetString;
	as->GetTexParameteriv=(bt::tfSTDCALL_PROC_uint_uint_p)glGetTexParameteriv;
	//GLProc("glGetUniformLocation",as->GetUniformLocation,bt::tfSTDCALL_uint_FUNC_uint_p);
	as->Hint=(bt::tfSTDCALL_PROC_uint_uint)glHint;
	//GLProc("glInitNames",as->InitNames,bt::tfSTDCALL_PROC);
	//GLProc("glIsBuffer",as->IsBuffer,bt::tfSTDCALL_bool_FUNC_uint);
	as->IsEnabled=(bt::tfSTDCALL_bool_FUNC_uint)glIsEnabled;
	as->LightModelfv=(bt::tfSTDCALL_PROC_uint_uint_p)glLightModelfv;
	as->Lightfv=(bt::tfSTDCALL_PROC_uint_uint_p)glLightfv;
	as->LineWidth=(bt::tfSTDCALL_PROC_float)glLineWidth;
	as->LoadIdentity=(bt::tfSTDCALL_PROC)glLoadIdentity;
	//GLProc("glLoadMatrixd",as->LoadMatrixd,bt::tfSTDCALL_PROC_p);
	as->LoadMatrixf=(bt::tfSTDCALL_PROC_p)glLoadMatrixf;
	//GLProc("glLoadName",as->LoadName,bt::tfSTDCALL_PROC_uint);
	//GLProc("glMapBuffer",as->MapBuffer,bt::tfSTDCALL_p_FUNC_uint_uint);
	as->Materialfv=(bt::tfSTDCALL_PROC_uint_uint_p)glMaterialfv;
	as->MatrixMode=(bt::tfSTDCALL_PROC_uint)glMatrixMode;
	//GLProc("glMultMatrixd",as->MultMatrixd,bt::tfSTDCALL_PROC_p);
	as->MultMatrixf=(bt::tfSTDCALL_PROC_p)glMultMatrixf;
	as->NormalPointer=(bt::tfSTDCALL_PROC_uint_int_p)glNormalPointer;
	as->PointSize=(bt::tfSTDCALL_PROC_float)glPointSize;
	//GLProc("glPopAttrib",as->PopAttrib,bt::tfSTDCALL_PROC);
	as->PopMatrix=(bt::tfSTDCALL_PROC)glPopMatrix;
	//GLProc("glPopName",as->PopName,bt::tfSTDCALL_PROC);
	//GLProc("glPushAttrib",as->PushAttrib,bt::tfSTDCALL_PROC_uint);
	as->PushMatrix=(bt::tfSTDCALL_PROC)glPushMatrix;
	//GLProc("glPushName",as->PushName,bt::tfSTDCALL_PROC_uint);
	as->RenderMode=(bt::tfSTDCALL_int_FUNC_uint)glRenderMode;
	as->Scalef=(bt::tfSTDCALL_PROC_float_float_float)glScalef;
	as->Scissor=(bt::tfSTDCALL_PROC_int_int_int_int)glScissor;
	//GLProc("glSelectBuffer",as->SelectBuffer,bt::tfSTDCALL_PROC_int_p);
	//GLProc("glSwapInterval",as->SwapInterval,bt::tfSTDCALL_bool_FUNC_int);
	as->TexCoordPointer=(bt::tfSTDCALL_PROC_int_uint_int_p)glTexCoordPointer;
	as->TexImage2D=(bt::tfSTDCALL_PROC_uint_int_int_int_int_int_uint_uint_p)glTexImage2D;
	as->TexParameteri=(bt::tfSTDCALL_PROC_uint_uint_int)glTexParameteri;
	as->TexSubImage2D=(bt::tfSTDCALL_PROC_uint_int_int_int_int_int_uint_uint_p)glTexSubImage2D;
	as->Translatef=(bt::tfSTDCALL_PROC_float_float_float)glTranslatef;
	//GLProc("glUnmapBuffer",as->UnmapBuffer,bt::tfSTDCALL_bool_FUNC_uint);
	as->VertexPointer=(bt::tfSTDCALL_PROC_int_uint_int_p)glVertexPointer;
	as->Viewport=(bt::tfSTDCALL_PROC_int_int_int_int)glViewport;
}

SoftRender::SoftRender()
{
}

void _APICALL SoftRender::initialize(GlContext * context)
{
	Context_P * mcontext=(Context_P *)context->handle();
	if ((!mcontext) || (mcontext->initialize)) return;
	sFunctionsGLContext &functions=context->functions();
	softInitGLFunctions(&functions);
	int err=functions.GetError();
	if (err) Log::console("Render::initialize failed: 0x%x\n", err);
	softReadExtention(mcontext);
	
	err=functions.GetError();
	if (err) Log::console("Render::initialize failed: 0x%x\n", err);

	char *info=(char*)functions.GetString(GL_VERSION);
	if (!info) Log::console("Render::initialize GL_VERSION failed: 0x%x\n", functions.GetError());
	Log::console("GL_VERSION: %s",info);
	info=(char*)functions.GetString(GL_VENDOR);
	if (!info) Log::console("Render::initialize GL_VENDOR failed: 0x%x\n", functions.GetError());
	Log::console("GL_VENDOR: %s",info);
	info=(char*)functions.GetString(GL_RENDERER);
	if (!info) Log::console("Render::initialize GL_RENDERER failed: 0x%x\n", functions.GetError());
	Log::console("GL_RENDERER: %s",info);
	info=(char*)functions.GetString(GL_EXTENSIONS);
	if (!info) Log::console("Render::initialize GL_EXTENSIONS failed: 0x%x\n", functions.GetError());
	Log::console("GL_EXTENSIONS: %s",info);

	//DrawModel=&_DrawModelVBO;
	//DrawLodModel=&_DrawLodModelVBO;
	functions.DrawMesh=(tfSTDCALL_PROC_p)&csad::Render::_DrawMesh;
	/*mcontext->BindModel=(tfFASTCALL_bool_FUNC_p_p)&_BindModel;
	mcontext->DrawBindModel=(tfFASTCALL_bool_FUNC_p_p)&_DrawBindModel;
	//DrawBindLodModel=&_DrawBindLodModelVBO;
	mcontext->UpdateModelElement=(tfFASTCALL_PROC_p_p_int_int)&_UpdateModelElement;
	mcontext->UpdateModelIndex=(tfFASTCALL_PROC_p_p_int_int)&_UpdateModelIndex;*/
	mcontext->UnBindModel=(tfFASTCALL_PROC)&csad::Render::_UnBindModel;

	mcontext->_GL_ARB_vertex_buffer_object=(
		functions.GenBuffers && functions.BindBuffer && functions.BufferData && 
		functions.BufferSubData && functions.MapBuffer && functions.UnmapBuffer && 
		functions.DeleteBuffers && functions.GetBufferParameteriv);

	/*if (mcontext->_GL_ARB_vertex_buffer_object) {
		functions.DrawMesh=(tfSTDCALL_PROC_p)&_DrawMeshVBO;
		mcontext->BindModel=(tfFASTCALL_bool_FUNC_p_p)&_BindModelVBO;
		mcontext->DrawBindModel=(tfFASTCALL_bool_FUNC_p_p)&_DrawBindModelVBO;
		mcontext->UpdateModelElement=(tfFASTCALL_PROC_p_p_int_int)&_UpdateModelElementVBO;
		mcontext->UpdateModelIndex=(tfFASTCALL_PROC_p_p_int_int)&_UpdateModelIndexVBO;
		mcontext->UnBindModel=(tfFASTCALL_PROC)&_UnBindModelVBO;
	}*/
	//p_isVal=VALIDED;
}

void _APICALL SoftRender::setViewPort(int x,int y,int width,int height)
{
	sFunctionsGLContext &functions=GlContext::current()->functions();
	functions.Enable(GL_SCISSOR_TEST);
	functions.Viewport(x,y,width,height);
	functions.Scissor(x,y,width,height);
}

bool _APICALL SoftRender::createContext(Display* display,GlContext * context)
{
	((LocalDisplay*)display)->check();
	sFunctionsDisplayRender &functions=((LocalDisplay*)display)->functions();
	if ((functions.mode&0xFF)!=0) return false;
	Context_P * mcontext=(Context_P *)context->handle();
	softBasefunctions(mcontext);
	softGlContext *cont=new softGlContext();
	extFunctions.CleanMem(cont,sizeof(softGlContext));
	cont->display=functions.soft;
	cont->depthMax=1.0f;
	mcontext->context=(void*)cont;
	mcontext->initialize=0;
	mcontext->_GL_ARB_shader=false;
	mcontext->_GL_EXT_stencil_wrap=false;
	mcontext->_GL_ARB_vertex_buffer_object=false;
	mcontext->_GL_EXT_stencil_two_side=false;
	if (mcontext->context==0)
	{
		Log::console("Create context failed");
		return false;
	}
	if (!MakeCurrent(display,context))
		Log::console("Render::createContext MakeCurrent error");
	initialize(context);

	return true;
}

bool _APICALL SoftRender::destroyContext(Display *display, GlContext *context)
{
	sFunctionsDisplayRender &functions=((LocalDisplay*)display)->functions();
	if ((functions.mode&0xFF)!=0) return false;
	Context_P * mcontext=(Context_P *)context->handle();
	delete (softGlContext*)mcontext->context;
	return true;
}

void * _APICALL SoftRender::getCurrentContext()
{
	if (!GlContext::current()) return 0;
	return currentContext;
}

bool _APICALL SoftRender::MakeCurrent(Display*display,GlContext*context)
{
	sFunctionsDisplayRender &functions=((LocalDisplay*)display)->functions();
	if ((functions.mode&0xFF)!=0) return false;
	((LocalDisplay*)display)->check();
	Context_P * mcontext=(Context_P *)(context->handle());
	bool ret=true;
	if (context==0) {
		if (currentContext!=0)
			currentContext=0;
		GlContext::current()=0;
		return ret;
	}
	if (mcontext->context!=(void*)currentContext) {
		softGlContext *sc=(softGlContext *)mcontext->context;
		sc->display=functions.soft;
		currentContext=(softGlContext*)sc;
	}
	if (ret) initialize(context);
	return ret;
}

void SoftRender::Buffers(Display * display)
{
	sFunctionsDisplayRender &function=((LocalDisplay*)display)->functions();
	if ((function.mode & 0xFF)!=csad::Display::RM_SOFT) return;
	((LocalDisplay*)display)->softDraw();
}

TYPEINFO(SoftRender)

void _APICALL glAlphaFunc(unsigned int,float)
{
}

void _APICALL glBindTexture(unsigned int,unsigned int)
{
}

void _APICALL glBlendFunc(unsigned int src,unsigned int dst)
{
	currentContext->blendSrcFactor=src;
	currentContext->blendDstFactor=dst;
}

void _APICALL glColor4f(float,float,float,float)
{
}

void _APICALL glColor4fv(float*)
{
}

void _APICALL glColorPointer(int count,unsigned int type,int step,void* data)
{
	currentContext->colorArray.count=count;
	currentContext->colorArray.type=type;
	currentContext->colorArray.step=step;
	currentContext->colorArray.data=data;
}

void _APICALL glClear(unsigned int mask)
{
	bool scissor=extFunctions.GetBit(softGlContext::SCISSOR_TEST,currentContext->enable)!=0;
	softDisplay *sd=(softDisplay *)currentContext->display;
	_int32 loop=sd->maxy;
	_int32 len=sd->maxx;
	if (scissor) {
		loop=currentContext->scissor.w;
		len=currentContext->scissor.z;
		if (loop>sd->maxy-currentContext->scissor.y) loop=sd->maxy-currentContext->scissor.y;
		if (len>sd->maxx-currentContext->scissor.x) len=sd->maxx-currentContext->scissor.x;
	}
	if (mask & GL_COLOR_BUFFER_BIT) {
		_int32 *buff=(_int32 *)sd->colorOffset;
		if (scissor) {
			buff+=(currentContext->scissor.x+currentContext->scissor.y*sd->maxx);
		}
		unsigned _int32 stride=sd->maxx;
		unsigned _int32 val=currentContext->clearColor.getInt();
		_int32 i=loop;

		while (i>0) {
			extFunctions.StocIMem(buff,len,val);
			buff+=stride;
			i--;
		}
	}
	if (mask & GL_DEPTH_BUFFER_BIT) {
		softDisplay *sd=(softDisplay *)currentContext->display;
		_int32 *depth=(_int32 *)sd->depthOffset;
		if (scissor) {
			depth+=(currentContext->scissor.x+currentContext->scissor.y*sd->maxx);
		}
		conv4b val;
		val.valfloat=currentContext->clearDepth;
		unsigned _int32 stride=sd->maxx;
		_int32 i=loop;

		while (i>0) {
			extFunctions.StocIMem(depth,len,val.valuint);
			depth+=stride;
			i--;
		}
	}
}

void _APICALL glClearColor(float a,float b,float c,float d)
{
	bt::vector4f vr(a,b,c,d);
	vecFunctions.V4FScale(&vr,&vr,255.0f);
	vecFunctions.V4FTo4B(&vr,&currentContext->clearColor);
}

void _APICALL glClearDepth(double val)
{
	currentContext->clearDepth=(float)val;
}

void _APICALL glCullFace(unsigned int id)
{
	currentContext->cullface=id;
}

void _APICALL glDeleteTextures(int,void*)
{
}

void _APICALL glDepthFunc(unsigned int fun)
{
	currentContext->depthFunc=fun;
}

void _APICALL glDisable(unsigned int id)
{
	int lid=-1;
	if (id==GL_ALPHA_TEST) lid=softGlContext::ALPHA_TEST;
	if (id==GL_BLEND) lid=softGlContext::BLEND;
	if (id==GL_LINE_SMOOTH) lid=softGlContext::LINE_SMOOTH;
	if (id==GL_POINT_SMOOTH) lid=softGlContext::POINT_SMOOTH;
	if (id==GL_DEPTH_TEST) lid=softGlContext::DEPTH_TEST;
	if (id==GL_CULL_FACE) lid=softGlContext::CULL_FACE;
	if (id==GL_NORMALIZE) lid=softGlContext::NORMALIZE;
	if (id==GL_SCISSOR_TEST) lid=softGlContext::SCISSOR_TEST;
	if (id==GL_TEXTURE_1D) lid=softGlContext::TEXTURE_1D;
	if (id==GL_TEXTURE_2D) lid=softGlContext::TEXTURE_2D;
	if (id==GL_TEXTURE_3D) lid=softGlContext::TEXTURE_3D;
	if (lid<0) return;
	extFunctions.SetBit(lid,0,currentContext->enable);
}

void _APICALL glDisableClientState(unsigned int id)
{
	if (id==GL_TEXTURE_COORD_ARRAY) extFunctions.SetBit(softGlContext::CLIENT_TEXTURE_COORD_ARRAY,0,currentContext->enable);
	if (id==GL_COLOR_ARRAY) extFunctions.SetBit(softGlContext::CLIENT_COLOR_ARRAY,0,currentContext->enable);
	if (id==GL_NORMAL_ARRAY) extFunctions.SetBit(softGlContext::CLIENT_NORMAL_ARRAY,0,currentContext->enable);
	if (id==GL_VERTEX_ARRAY) extFunctions.SetBit(softGlContext::CLIENT_VERTEX_ARRAY,0,currentContext->enable);
}

V4AFdata TempTri[256*3];

void _prepareVertexTrianglesFloatInt(char *data,char *index,int mode,int step,int count)
{
	V4AFdata* vt=TempTri;
	char *pvertex=data;
	char *pindex=index;
	char *idc=pindex+(count<<2);
	int svertex=step;
	if (mode==2) while(pindex<idc) {float *vr=(float*)&pvertex[*((int*)pindex)*svertex]; float *vw=vt->v; vw[0]=vr[0]; vw[1]=vr[1]; vw[2]=0.0f;vw[3]=1.0f; pindex+=4; vt++;}
	if (mode==3) while(pindex<idc) {float *vr=(float*)&pvertex[*((int*)pindex)*svertex]; float *vw=vt->v; vw[0]=vr[0]; vw[1]=vr[1]; vw[2]=vr[2];vw[3]=1.0f; pindex+=4; vt++;}
	if (mode==4) while(pindex<idc) {float *vr=(float*)&pvertex[*((int*)pindex)*svertex]; float *vw=vt->v; vw[0]=vr[0]; vw[1]=vr[1]; vw[2]=vr[2];vw[3]=vr[3]; pindex+=4; vt++;}
}

void _prepareColorTrianglesFloatInt(char *data,char *index,int mode,int step,int count)
{
	V4AFdata* vt=TempTri;
	char *pcolor=data;
	char *pindex=index;
	char *idc=pindex+(count<<2);
	int scolor=step;
	if (mode==1) while(pindex<idc) {float *vr=(float*)&pcolor[*((int*)pindex)*scolor]; float *vw=vt->c; vw[0]=vr[0]; vw[1]=0.0; vw[2]=0.0f;vw[3]=0.0f; pindex+=4; vt++;}
	if (mode==2) while(pindex<idc) {float *vr=(float*)&pcolor[*((int*)pindex)*scolor]; float *vw=vt->c; vw[0]=vr[0]; vw[1]=vr[1]; vw[2]=0.0f;vw[3]=0.0f; pindex+=4; vt++;}
	if (mode==3) while(pindex<idc) {float *vr=(float*)&pcolor[*((int*)pindex)*scolor]; float *vw=vt->c; vw[0]=vr[2]; vw[1]=vr[1]; vw[2]=vr[0];vw[3]=0.0f; pindex+=4; vt++;}
	if (mode==4) while(pindex<idc) {float *vr=(float*)&pcolor[*((int*)pindex)*scolor]; float *vw=vt->c; vw[0]=vr[2]; vw[1]=vr[1]; vw[2]=vr[0];vw[3]=vr[3]; pindex+=4; vt++;}
}

void _APICALL _FV3T4C4VertexTruncXDEF(V4AFdata *v,V4AFdata *vbase,float limit)
{
	float k=(vbase->v[0]-limit)/(vbase->v[0]-v->v[0]);
	v->v[2]=(v->v[2]-vbase->v[2])*k+vbase->v[2];
	v->v[0]=limit;
	v->v[1]=(v->v[1]-vbase->v[1])*k+vbase->v[1];
	v->c[0]=(v->c[0]-vbase->c[0])*k+vbase->c[0];
	v->c[1]=(v->c[1]-vbase->c[1])*k+vbase->c[1];
	v->c[2]=(v->c[2]-vbase->c[2])*k+vbase->c[2];
	v->c[3]=(v->c[3]-vbase->c[3])*k+vbase->c[3];
	v->text[0][0]=(v->text[0][0]-vbase->text[0][0])*k+vbase->text[0][0];
	v->text[0][1]=(v->text[0][1]-vbase->text[0][1])*k+vbase->text[0][1];
	v->text[1][0]=(v->text[1][0]-vbase->text[1][0])*k+vbase->text[1][0];
	v->text[1][1]=(v->text[1][1]-vbase->text[1][1])*k+vbase->text[1][1];
	v->text[2][0]=(v->text[2][0]-vbase->text[2][0])*k+vbase->text[2][0];
	v->text[2][1]=(v->text[2][1]-vbase->text[2][1])*k+vbase->text[2][1];
	v->text[3][0]=(v->text[3][0]-vbase->text[3][0])*k+vbase->text[3][0];
	v->text[3][1]=(v->text[3][1]-vbase->text[3][1])*k+vbase->text[3][1];
}

void _APICALL _FV3T4C4VertexTruncYDEF(V4AFdata *v,V4AFdata *vbase,float limit)
{
	float k=(vbase->v[1]-limit)/(vbase->v[1]-v->v[1]);
	v->v[2]=(v->v[2]-vbase->v[2])*k+vbase->v[2];
	v->v[0]=(v->v[0]-vbase->v[0])*k+vbase->v[0];
	v->v[1]=limit;
	v->c[0]=(v->c[0]-vbase->c[0])*k+vbase->c[0];
	v->c[1]=(v->c[1]-vbase->c[1])*k+vbase->c[1];
	v->c[2]=(v->c[2]-vbase->c[2])*k+vbase->c[2];
	v->c[3]=(v->c[3]-vbase->c[3])*k+vbase->c[3];
	v->text[0][0]=(v->text[0][0]-vbase->text[0][0])*k+vbase->text[0][0];
	v->text[0][1]=(v->text[0][1]-vbase->text[0][1])*k+vbase->text[0][1];
	v->text[1][0]=(v->text[1][0]-vbase->text[1][0])*k+vbase->text[1][0];
	v->text[1][1]=(v->text[1][1]-vbase->text[1][1])*k+vbase->text[1][1];
	v->text[2][0]=(v->text[2][0]-vbase->text[2][0])*k+vbase->text[2][0];
	v->text[2][1]=(v->text[2][1]-vbase->text[2][1])*k+vbase->text[2][1];
	v->text[3][0]=(v->text[3][0]-vbase->text[3][0])*k+vbase->text[3][0];
	v->text[3][1]=(v->text[3][1]-vbase->text[3][1])*k+vbase->text[3][1];
}

void _APICALL _FV3T4C4VertexTruncZDEF(V4AFdata *v,V4AFdata *vbase,float limit)
{
	float k=(vbase->v[2]-limit)/(vbase->v[2]-v->v[2]);
	v->v[1]=(v->v[1]-vbase->v[1])*k+vbase->v[1];
	v->v[0]=(v->v[0]-vbase->v[0])*k+vbase->v[0];
	v->v[2]=limit;
	v->c[0]=(v->c[0]-vbase->c[0])*k+vbase->c[0];
	v->c[1]=(v->c[1]-vbase->c[1])*k+vbase->c[1];
	v->c[2]=(v->c[2]-vbase->c[2])*k+vbase->c[2];
	v->c[3]=(v->c[3]-vbase->c[3])*k+vbase->c[3];
	v->text[0][0]=(v->text[0][0]-vbase->text[0][0])*k+vbase->text[0][0];
	v->text[0][1]=(v->text[0][1]-vbase->text[0][1])*k+vbase->text[0][1];
	v->text[1][0]=(v->text[1][0]-vbase->text[1][0])*k+vbase->text[1][0];
	v->text[1][1]=(v->text[1][1]-vbase->text[1][1])*k+vbase->text[1][1];
	v->text[2][0]=(v->text[2][0]-vbase->text[2][0])*k+vbase->text[2][0];
	v->text[2][1]=(v->text[2][1]-vbase->text[2][1])*k+vbase->text[2][1];
	v->text[3][0]=(v->text[3][0]-vbase->text[3][0])*k+vbase->text[3][0];
	v->text[3][1]=(v->text[3][1]-vbase->text[3][1])*k+vbase->text[3][1];
}

void _APICALL glDrawElements(unsigned int draw,int indexcount,unsigned int type,void* index)
{
	if (extFunctions.GetBit(softGlContext::CLIENT_VERTEX_ARRAY,currentContext->enable)==0) {
		return;
	}
	int tvertex=currentContext->vertexArray.type;
	int cvertex=currentContext->vertexArray.count;
	char *pvertex=(char *)currentContext->vertexArray.data;
	int svertex=currentContext->vertexArray.step;
	int tcolor=currentContext->colorArray.type;
	int ccolor=currentContext->colorArray.count;
	char *pcolor=(char *)currentContext->colorArray.data;
	int scolor=currentContext->colorArray.step;
	bt::matrix4f matrix;
	vecFunctions.M4FMul(currentContext->proj_matrix[currentContext->projMatrixStackPos].m,currentContext->model_matrix[currentContext->modelMatrixStackPos].m,matrix.m);
	bt::vector4i vp=currentContext->viewPort;
	softDisplay *display=(softDisplay*)currentContext->display;

	if (vp[0]<0) vp[0]=0;
	if (vp[1]<0) vp[1]=0;
	if (vp[0]>=display->maxx) vp[0]=display->maxx-1;
	if (vp[1]>=display->maxy) vp[1]=display->maxy-1;
	if (vp[2]<0) vp[2]=0;
	if (vp[3]<0) vp[3]=0;
	if (vp[2]>=display->maxx-vp[0]) vp[2]=display->maxx-vp[0];
	if (vp[3]>=display->maxy-vp[1]) vp[3]=display->maxy-vp[1];

	float vportScale[3]={0.5f*vp[2],0.5f*vp[3],(currentContext->depthMax-currentContext->depthMin)*0.5f};
	float vportAdd[3]={vp[0]+vp[2]*0.5f,vp[1]+vp[3]*0.5f,currentContext->depthMin};

	T4AFdata fsdata;
	fsdata.mem=(char*)display->colorOffset;
	fsdata.depth=(char*)display->depthOffset;
	fsdata.stride=display->bufferStride;
	fsdata.size=display->bufferStride*vp[3];
	fsdata.width=display->maxx;
	fsdata.height=display->maxy;
	fsdata.left=vp[0]<<2;
	fsdata.right=(vp[0]+vp[2])<<2;
	float vportFull[4];
	vportFull[0]=(float)vp[0];
	vportFull[1]=(float)vp[1];
	vportFull[2]=(float)(vp[0]+vp[2]);
	vportFull[3]=(float)(vp[1]+vp[3]);
	bool isface=extFunctions.GetBit(softGlContext::CULL_FACE,currentContext->enable)==0;

	char *pindex=(char*)index;
	if (draw==GL_TRIANGLES && (type==GL_INT || type==GL_UNSIGNED_INT)) while (indexcount>0) {
		int tris=256*3;
		if (indexcount<tris) tris=indexcount;

		V4AFdata* vt=TempTri;
		// prepare vertex pos
		if (tvertex==GL_FLOAT) _prepareVertexTrianglesFloatInt(pvertex,pindex,cvertex,svertex,tris);
		arvFunctions.A3FProj(&TempTri[0].v,matrix.m,vportScale,vportAdd,&TempTri[0].v,sizeof(V4AFdata),sizeof(V4AFdata),(unsigned int)((char*)&TempTri[0].flag-(char*)&TempTri[0]),tris);
		// prepare color
		if (extFunctions.GetBit(softGlContext::CLIENT_COLOR_ARRAY,currentContext->enable)!=0) {
			if (tcolor==GL_FLOAT) _prepareColorTrianglesFloatInt(pcolor,pindex,ccolor,scolor,tris);
			arvFunctions.A4FScale(&TempTri[0].c,&TempTri[0].c,255.0f,sizeof(V4AFdata),sizeof(V4AFdata),tris);
		} else {
			bt::vector4f colorm(currentContext->materialFrontDiffuse.z,currentContext->materialFrontDiffuse.y,currentContext->materialFrontDiffuse.x,currentContext->materialFrontDiffuse.w); //BGR TO RGB
			arvFunctions.A4FScale(&colorm,&TempTri[0].c,255.0f,0,sizeof(V4AFdata),tris);
			/*for (int i=0;i<tris;i++) {
				TempTri[i].c[0]=(i*20)%256;
				TempTri[i].c[1]=(i*10)%256;
			}*/
		}
		// prepare color and texture coordinate
		// ...
		// pvertex+=tris*svertex;
		pindex+=tris<<2;
		indexcount-=tris;

		int indexTr=0;
		vt=TempTri;
		while (indexTr<tris) {
			if ((vt[0].flag & vt[1].flag & vt[2].flag & 0x33)==0) {
				bool fase=true;
				if (currentContext->cullface==GL_BACK) {
					fase=vecFunctions.V2FQDFL(vt[0].v,vt[1].v,vt[2].v)<=0;
				} else {
					fase=vecFunctions.V2FQDFL(vt[0].v,vt[1].v,vt[2].v)>=0;
				}

				if (fase || isface) {
					int i1=0;
					V4AFdata* vt0[3];
					if (vt[0].flag & 0x20) {
						vt0[0]=&vt[0];
						i1++;
					} else vt0[2]=&vt[0];
					if (vt[1].flag & 0x20) {
						vt0[i1]=&vt[1];
						i1++;
					} else vt0[2]=&vt[1];
					if (vt[2].flag & 0x20) {
						vt0[i1]=&vt[2];
						i1++;
					} else vt0[2]=&vt[2];
					if (i1==2) {
						_FV3T4C4VertexTruncYDEF(vt0[0],vt0[2],vportFull[1]);
						_FV3T4C4VertexTruncYDEF(vt0[1],vt0[2],vportFull[1]);
					}
					int i2=0;
					if (vt[0].flag & 0x02) {
						vt0[0]=&vt[0];
						i2++;
					} else vt0[2]=&vt[0];
					if (vt[1].flag & 0x02) {
						vt0[i2]=&vt[1];
						i2++;
					} else vt0[2]=&vt[1];
					if (vt[2].flag & 0x02) {
						vt0[i2]=&vt[2];
						i2++;
					} else vt0[2]=&vt[2];
					if (i2==2) {
						_FV3T4C4VertexTruncYDEF(vt0[0],vt0[2],vportFull[3]);
						_FV3T4C4VertexTruncYDEF(vt0[1],vt0[2],vportFull[3]);
					}
					if (i1==2 || i2==2) {
						if (vt0[0]->v[0]<vportFull[0]) vt0[0]->flag|=0x10;
						if (vt0[1]->v[0]<vportFull[0]) vt0[1]->flag|=0x10;
						if (vt0[0]->v[0]>vportFull[2]) vt0[0]->flag|=0x01;
						if (vt0[1]->v[0]>vportFull[2]) vt0[1]->flag|=0x01;
					}
					if ((vt[0].flag & vt[1].flag & vt[2].flag & 0x33)==0) {
						i1=0;
						if (vt[0].flag & 0x10) {
							vt0[0]=&vt[0];
							i1++;
						} else vt0[2]=&vt[0];
						if (vt[1].flag & 0x10) {
							vt0[i1]=&vt[1];
							i1++;
						} else vt0[2]=&vt[1];
						if (vt[2].flag & 0x10) {
							vt0[i1]=&vt[2];
							i1++;
						} else vt0[2]=&vt[2];
						if (i1==2) {
							_FV3T4C4VertexTruncXDEF(vt0[0],vt0[2],vportFull[0]);
							_FV3T4C4VertexTruncXDEF(vt0[1],vt0[2],vportFull[0]);
						}
						i2=0;
						if (vt[0].flag & 0x01) {
							vt0[0]=&vt[0];
							i2++;
						} else vt0[2]=&vt[0];
						if (vt[1].flag & 0x01) {
							vt0[i2]=&vt[1];
							i2++;
						} else vt0[2]=&vt[1];
						if (vt[2].flag & 0x01) {
							vt0[i2]=&vt[2];
							i2++;
						} else vt0[2]=&vt[2];
						if (i2==2) {
							_FV3T4C4VertexTruncXDEF(vt0[0],vt0[2],vportFull[2]);
							_FV3T4C4VertexTruncXDEF(vt0[1],vt0[2],vportFull[2]);
						}
						if (i1==2 || i2==2) {
							if (vt0[0]->v[1]<vportFull[1]) vt0[0]->flag|=0x20;
							if (vt0[1]->v[1]<vportFull[1]) vt0[1]->flag|=0x20;
							if (vt0[0]->v[1]>vportFull[3]) vt0[0]->flag|=0x02;
							if (vt0[1]->v[1]>vportFull[3]) vt0[1]->flag|=0x02;
						}
						/*i1=0;
						if (vt[0].flag & 0x40) {
							vt0[0]=&vt[0];
							i1++;
						} else vt0[2]=&vt[0];
						if (vt[1].flag & 0x40) {
							vt0[i1]=&vt[1];
							i1++;
						} else vt0[2]=&vt[1];
						if (vt[2].flag & 0x40) {
							vt0[i1]=&vt[2];
							i1++;
						} else vt0[2]=&vt[2];
						if (i1==2) {
							_FV3T4C4VertexTruncZDEF(vt0[0],vt0[2],currentContext->depthMin);
							_FV3T4C4VertexTruncZDEF(vt0[1],vt0[2],currentContext->depthMin);
						}*/

						if ((vt[0].flag & vt[1].flag & vt[2].flag & 0x33)==0) {
							int c1;
							int c2;
							int c3;
							vecFunctions.V4FTo4B(vt[0].c,&c1);
							vecFunctions.V4FTo4B(vt[1].c,&c2);
							vecFunctions.V4FTo4B(vt[2].c,&c3);
							if (c1==c2 && c2==c3) {
								renFunctions.T4AFDraw(vt,&fsdata);
							} else {
								renFunctions.T4AFSDraw(vt,&fsdata);
							}
						}
					}
				}
			}
			vt+=3;
			indexTr+=3;
		}
	}

	bool pointsm=extFunctions.GetBit(softGlContext::POINT_SMOOTH,currentContext->enable)!=0;
	tfSTDCALL_PROC_p_p_float pf=renFunctions.P4AFDraw;
	if (pointsm) {
		pf=renFunctions.P4AFDrawAA;
		if (extFunctions.GetBit(softGlContext::BLEND,currentContext->enable)!=0) {
			if ((currentContext->blendSrcFactor==GL_SRC_ALPHA) && (currentContext->blendDstFactor==GL_ONE_MINUS_SRC_ALPHA)) pf=renFunctions.P4AFADrawAA;
		}
	}
	
	if (draw==GL_POINTS && (type==GL_INT || type==GL_UNSIGNED_INT)) while (indexcount>0) {
		int tris=256;
		if (indexcount<tris) tris=indexcount;

		V4AFdata* vt=TempTri;
		// prepare vertex pos
		if (tvertex==GL_FLOAT) _prepareVertexTrianglesFloatInt(pvertex,pindex,cvertex,svertex,tris);
		arvFunctions.A3FProj(TempTri,matrix.m,vportScale,vportAdd,TempTri,sizeof(V4AFdata),sizeof(V4AFdata),(unsigned int)((char*)&TempTri[0].flag-(char*)&TempTri[0]),tris);
		// prepare color
		if (extFunctions.GetBit(softGlContext::CLIENT_COLOR_ARRAY,currentContext->enable)!=0) {
			if (tcolor==GL_FLOAT) _prepareColorTrianglesFloatInt(pcolor,pindex,ccolor,scolor,tris);
			arvFunctions.A4FScale(&TempTri[0].c,&TempTri[0].c,255.0f,sizeof(V4AFdata),sizeof(V4AFdata),tris);
		} else {
			bt::vector4f colorm(currentContext->materialFrontDiffuse.z,currentContext->materialFrontDiffuse.y,currentContext->materialFrontDiffuse.x,currentContext->materialFrontDiffuse.w); //BGR TO RGB
			arvFunctions.A4FScale(&colorm,&TempTri[0].c,255.0f,0,sizeof(V4AFdata),tris);
		}
		// prepare color and texture coordinate
		// ...
		// pvertex+=tris*svertex;
		pindex+=tris<<2;
		indexcount-=tris;

		int indexTr=0;
		vt=TempTri;
		while (indexTr<tris) {
			if ((vt[0].flag & 0x33)==0 || ((vt[0].v[0]>vportFull[0]-currentContext->pointSize)
				&& (vt[0].v[0]<vportFull[2]+currentContext->pointSize)
				&& (vt[0].v[1]>vportFull[1]-currentContext->pointSize)
				&& (vt[0].v[1]<vportFull[3]+currentContext->pointSize))) {
				pf(vt,&fsdata,currentContext->pointSize*0.5f);
			}
			vt++;
			indexTr++;
		}
	}

	if (draw==GL_LINES && (type==GL_INT || type==GL_UNSIGNED_INT)) while (indexcount>0) {
		int tris=256*2;
		if (indexcount<tris) tris=indexcount;

		V4AFdata* vt=TempTri;
		// prepare vertex pos
		if (tvertex==GL_FLOAT) _prepareVertexTrianglesFloatInt(pvertex,pindex,cvertex,svertex,tris);
		arvFunctions.A4FProj(TempTri,matrix.m,vportScale,vportAdd,TempTri,sizeof(V4AFdata),sizeof(V4AFdata),(unsigned int)((char*)&TempTri[0].flag-(char*)&TempTri[0]),tris);
		// prepare color
		if (extFunctions.GetBit(softGlContext::CLIENT_COLOR_ARRAY,currentContext->enable)!=0) {
			if (tcolor==GL_FLOAT) _prepareColorTrianglesFloatInt(pcolor,pindex,ccolor,scolor,tris);
			arvFunctions.A4FScale(&TempTri[0].c,&TempTri[0].c,255.0f,sizeof(V4AFdata),sizeof(V4AFdata),tris);
		} else {
			bt::vector4f colorm(currentContext->materialFrontDiffuse.z,currentContext->materialFrontDiffuse.y,currentContext->materialFrontDiffuse.x,currentContext->materialFrontDiffuse.w); //BGR TO RGB
			arvFunctions.A4FScale(&colorm,&TempTri[0].c,255.0f,0,sizeof(V4AFdata),tris);
		}
		// prepare color and texture coordinate
		// ...
		// pvertex+=tris*svertex;
		pindex+=tris<<2;
		indexcount-=tris;

		int indexTr=0;
		vt=TempTri;
		while (indexTr<tris) {
			if ((vt[0].flag & vt[1].flag & 0x33)==0) {
				if (vt[0].flag & 0x40) _FV3T4C4VertexTruncZDEF(&vt[0],&vt[1],currentContext->depthMin);
				if (vt[1].flag & 0x40) _FV3T4C4VertexTruncZDEF(&vt[1],&vt[0],currentContext->depthMin);
				if (vt[0].flag & 0x20) _FV3T4C4VertexTruncYDEF(&vt[0],&vt[1],vportFull[1]);
				if (vt[1].flag & 0x20) _FV3T4C4VertexTruncYDEF(&vt[1],&vt[0],vportFull[1]);
				if (vt[0].flag & 0x02) _FV3T4C4VertexTruncYDEF(&vt[0],&vt[1],vportFull[3]);
				if (vt[1].flag & 0x02) _FV3T4C4VertexTruncYDEF(&vt[1],&vt[0],vportFull[3]);
				if (vt[0].flag & 0x10) _FV3T4C4VertexTruncXDEF(&vt[0],&vt[1],vportFull[0]);
				if (vt[1].flag & 0x10) _FV3T4C4VertexTruncXDEF(&vt[1],&vt[0],vportFull[0]);
				if (vt[0].flag & 0x01) _FV3T4C4VertexTruncXDEF(&vt[0],&vt[1],vportFull[2]);
				if (vt[1].flag & 0x01) _FV3T4C4VertexTruncXDEF(&vt[1],&vt[0],vportFull[2]);
				/*if (vt0[0]->v[1]<vportFull[1]) vt0[0]->flag|=0x20;
				if (vt0[1]->v[1]<vportFull[1]) vt0[1]->flag|=0x20;
				if (vt0[0]->v[1]>vportFull[3]) vt0[0]->flag|=0x02;
				if (vt0[1]->v[1]>vportFull[3]) vt0[1]->flag|=0x02;*/
				renFunctions.L4AFDraw(vt,&fsdata,currentContext->lineSize);
			}
			vt+=2;
			indexTr+=2;
		}
	}
}

void _APICALL glEnable(unsigned int id)
{
	int lid=-1;
	if (id==GL_ALPHA_TEST) lid=softGlContext::ALPHA_TEST;
	if (id==GL_BLEND) lid=softGlContext::BLEND;
	if (id==GL_LINE_SMOOTH) lid=softGlContext::LINE_SMOOTH;
	if (id==GL_POINT_SMOOTH) lid=softGlContext::POINT_SMOOTH;
	if (id==GL_DEPTH_TEST) lid=softGlContext::DEPTH_TEST;
	if (id==GL_CULL_FACE) lid=softGlContext::CULL_FACE;
	if (id==GL_NORMALIZE) lid=softGlContext::NORMALIZE;
	if (id==GL_SCISSOR_TEST) lid=softGlContext::SCISSOR_TEST;
	if (id==GL_TEXTURE_1D) lid=softGlContext::TEXTURE_1D;
	if (id==GL_TEXTURE_2D) lid=softGlContext::TEXTURE_2D;
	if (id==GL_TEXTURE_3D) lid=softGlContext::TEXTURE_3D;
	if (lid<0) return;
	extFunctions.SetBit(lid,1,currentContext->enable);
}

void _APICALL glEnableClientState(unsigned int id)
{
	if (id==GL_TEXTURE_COORD_ARRAY) extFunctions.SetBit(softGlContext::CLIENT_TEXTURE_COORD_ARRAY,1,currentContext->enable);
	if (id==GL_COLOR_ARRAY) extFunctions.SetBit(softGlContext::CLIENT_COLOR_ARRAY,1,currentContext->enable);
	if (id==GL_NORMAL_ARRAY) extFunctions.SetBit(softGlContext::CLIENT_NORMAL_ARRAY,1,currentContext->enable);
	if (id==GL_VERTEX_ARRAY) extFunctions.SetBit(softGlContext::CLIENT_VERTEX_ARRAY,1,currentContext->enable);
}

void _APICALL glFinish()
{
}

void _APICALL glFlush()
{
}

void _APICALL glGenTextures(int count,unsigned int *data)
{
	while (count>0) {
		*data=0;
		data++;
		count--;
	}
}

void _APICALL glGetBooleanv(unsigned int id,void* val)
{
	int lid=-1;
	if (id==GL_ALPHA_TEST) lid=softGlContext::ALPHA_TEST;
	if (id==GL_BLEND) lid=softGlContext::BLEND;
	if (id==GL_LINE_SMOOTH) lid=softGlContext::LINE_SMOOTH;
	if (id==GL_POINT_SMOOTH) lid=softGlContext::POINT_SMOOTH;
	if (id==GL_DEPTH_TEST) lid=softGlContext::DEPTH_TEST;
	if (id==GL_NORMALIZE) lid=softGlContext::NORMALIZE;
	if (id==GL_SCISSOR_TEST) lid=softGlContext::SCISSOR_TEST;
	if (id==GL_TEXTURE_1D) lid=softGlContext::TEXTURE_1D;
	if (id==GL_TEXTURE_2D) lid=softGlContext::TEXTURE_2D;
	if (id==GL_TEXTURE_3D) lid=softGlContext::TEXTURE_3D;
	if (lid<0) 	return;
	unsigned char *sval=(unsigned char *)val;
	*sval=GL_FALSE;
	if (extFunctions.GetBit(lid,currentContext->enable)!=0) {
		*sval=GL_TRUE;
	}
}

unsigned int _APICALL glGetError()
{
	return currentContext->error;
}

void _APICALL glGetFloatv(unsigned int id,void*to)
{
	int count=0;
	float *from=0;
	if (id==GL_PROJECTION_MATRIX) {
		count=4*4;
		from=currentContext->proj_matrix[currentContext->projMatrixStackPos].m;
	}
	if (!from) return;
	extFunctions.MoveMem(from,to,count*4);
}

void _APICALL glGetIntegerv(unsigned int,void*)
{
}

char *_APICALL glGetString(unsigned int id)
{
	if (id==GL_VERSION) return (char*)"0.0.1";
	if (id==GL_VENDOR) return (char*)"CSAD";
	if (id==GL_RENDERER) return (char*)"SOFT";
	if (id==GL_EXTENSIONS) return (char*)"";
	return 0;
}

void _APICALL glGetTexParameteriv(unsigned int,unsigned int,int *)
{
}

void _APICALL glHint(unsigned int,unsigned int)
{
}

bool _APICALL glIsEnabled(unsigned int id)
{
	int lid=-1;
	if (id==GL_ALPHA_TEST) lid=softGlContext::ALPHA_TEST;
	if (id==GL_BLEND) lid=softGlContext::BLEND;
	if (id==GL_LINE_SMOOTH) lid=softGlContext::LINE_SMOOTH;
	if (id==GL_POINT_SMOOTH) lid=softGlContext::POINT_SMOOTH;
	if (id==GL_DEPTH_TEST) lid=softGlContext::DEPTH_TEST;
	if (id==GL_COLOR_MATERIAL) lid=softGlContext::COLOR_MATERIAL;
	if (id==GL_NORMALIZE) lid=softGlContext::NORMALIZE;
	if (id==GL_SCISSOR_TEST) lid=softGlContext::SCISSOR_TEST;
	if (id==GL_TEXTURE_1D) lid=softGlContext::TEXTURE_1D;
	if (id==GL_TEXTURE_2D) lid=softGlContext::TEXTURE_2D;
	if (id==GL_TEXTURE_3D) lid=softGlContext::TEXTURE_3D;
	if (lid<0) 	return false;
	return extFunctions.GetBit(lid,currentContext->enable)!=0;
}

void _APICALL glLightModelfv(unsigned int,unsigned int,float*)
{
}

void _APICALL glLightfv(unsigned int,unsigned int,float*)
{
}

void _APICALL glLineWidth(float val)
{
	currentContext->lineSize=val;
}

void _APICALL glLoadIdentity()
{
	float *matrixload=0;
	if (currentContext->matrixMode==GL_PROJECTION) matrixload=currentContext->proj_matrix[currentContext->projMatrixStackPos].m;
	if (currentContext->matrixMode==GL_MODELVIEW) matrixload=currentContext->model_matrix[currentContext->modelMatrixStackPos].m;
	if (currentContext->matrixMode==GL_TEXTURE) {
		int id=currentContext->multyTextId;
		matrixload=currentContext->text_matrix[id][currentContext->textMatrixStackPos[id]].m;
	}
	if (matrixload) vecFunctions.M4FIdentity(matrixload);
}

void _APICALL glLoadMatrixf(float*matrix)
{
	float *matrixload=0;
	if (currentContext->matrixMode==GL_PROJECTION) matrixload=currentContext->proj_matrix[currentContext->projMatrixStackPos].m;
	if (currentContext->matrixMode==GL_MODELVIEW) matrixload=currentContext->model_matrix[currentContext->modelMatrixStackPos].m;
	if (currentContext->matrixMode==GL_TEXTURE) {
		int id=currentContext->multyTextId;
		matrixload=currentContext->text_matrix[id][currentContext->textMatrixStackPos[id]].m;
	}
	if (matrixload) extFunctions.MoveMem(matrix,matrixload,4*4*4);
}

void _APICALL glMaterialfv(unsigned int face,unsigned int id,float* val)
{
	if (face==GL_FRONT_AND_BACK || face==GL_FRONT) {
		if (id==GL_AMBIENT) currentContext->materialFrontAmbient=bt::vector4f(val);
		if (id==GL_DIFFUSE) currentContext->materialFrontDiffuse=bt::vector4f(val);
		if (id==GL_EMISSION) currentContext->materialFrontEmission=bt::vector4f(val);
		if (id==GL_SPECULAR) currentContext->materialFrontSpecular=bt::vector4f(val);
	}
	if (face==GL_FRONT_AND_BACK || face==GL_BACK) {
		if (id==GL_AMBIENT) currentContext->materialBackAmbient=bt::vector4f(val);
		if (id==GL_DIFFUSE) currentContext->materialBackDiffuse=bt::vector4f(val);
		if (id==GL_EMISSION) currentContext->materialBackEmission=bt::vector4f(val);
		if (id==GL_SPECULAR) currentContext->materialBackSpecular=bt::vector4f(val);
	}
}

void _APICALL glMatrixMode(unsigned int mode)
{
	currentContext->matrixMode=mode;
}

void _APICALL glMultMatrixf(float*matrix)
{
	float *matrixload=0;
	if (currentContext->matrixMode==GL_PROJECTION) matrixload=currentContext->proj_matrix[currentContext->projMatrixStackPos].m;
	if (currentContext->matrixMode==GL_MODELVIEW) matrixload=currentContext->model_matrix[currentContext->modelMatrixStackPos].m;
	if (currentContext->matrixMode==GL_TEXTURE) {
		int id=currentContext->multyTextId;
		matrixload=currentContext->text_matrix[id][currentContext->textMatrixStackPos[id]].m;
	}
	if (matrixload) vecFunctions.M4FMul(matrixload,matrix,matrixload);
}

void _APICALL glNormalPointer(unsigned int type,int step,void* data)
{
	currentContext->normalArray.count=3;
	currentContext->normalArray.type=type;
	currentContext->normalArray.step=step;
	currentContext->normalArray.data=data;
}

void _APICALL glPointSize(float size)
{
	currentContext->pointSize=size;
}

void _APICALL glPopMatrix()
{
	if (currentContext->matrixMode==GL_PROJECTION) if (currentContext->projMatrixStackPos>0) currentContext->projMatrixStackPos--;
	if (currentContext->matrixMode==GL_MODELVIEW) if (currentContext->modelMatrixStackPos>0) currentContext->modelMatrixStackPos--;
	if (currentContext->matrixMode==GL_TEXTURE) if (currentContext->textMatrixStackPos[currentContext->multyTextId]>0) currentContext->textMatrixStackPos[currentContext->multyTextId]--;
}

void _APICALL glPushMatrix()
{
	if (currentContext->matrixMode==GL_PROJECTION) if (currentContext->projMatrixStackPos<1) currentContext->projMatrixStackPos++;
	if (currentContext->matrixMode==GL_MODELVIEW) if (currentContext->modelMatrixStackPos<15) currentContext->modelMatrixStackPos++;
	if (currentContext->matrixMode==GL_TEXTURE) if (currentContext->textMatrixStackPos[currentContext->multyTextId]<1) currentContext->textMatrixStackPos[currentContext->multyTextId]++;
}

int _APICALL glRenderMode(unsigned int)
{
	return 0;
}

void _APICALL glScalef(float a,float b,float c)
{
	bt::vector3f scale(a,b,c);
	float *matrixload=0;
	if (currentContext->matrixMode==GL_PROJECTION) matrixload=currentContext->proj_matrix[currentContext->projMatrixStackPos].m;
	if (currentContext->matrixMode==GL_MODELVIEW) matrixload=currentContext->model_matrix[currentContext->modelMatrixStackPos].m;
	if (currentContext->matrixMode==GL_TEXTURE) {
		int id=currentContext->multyTextId;
		matrixload=currentContext->text_matrix[id][currentContext->textMatrixStackPos[id]].m;
	}
	if (matrixload) vecFunctions.M4FAddScale(matrixload,&scale,matrixload);
}

void _APICALL glScissor(int a,int b,int c,int d)
{
	currentContext->scissor=bt::vector4i(a,b,c,d);
}

void _APICALL glTexCoordPointer(int count,unsigned int type,int step,void*data)
{
	int id=currentContext->multyTextId;
	currentContext->textArray[id].count=count;
	currentContext->textArray[id].type=type;
	currentContext->textArray[id].step=step;
	currentContext->textArray[id].data=data;
}

void _APICALL glTexImage2D(unsigned int,int,int,int,int,int,unsigned int,unsigned int,void*)
{
}

void _APICALL glTexParameteri(unsigned int,unsigned int,unsigned int)
{
}

void _APICALL glTexSubImage2D(unsigned int,int,int,int,int,int,unsigned int,unsigned int,void*)
{
}

void _APICALL glTranslatef(float a,float b,float c)
{
	bt::vector3f translate(a,b,c);
	float *matrixload=0;
	if (currentContext->matrixMode==GL_PROJECTION) matrixload=currentContext->proj_matrix[currentContext->projMatrixStackPos].m;
	if (currentContext->matrixMode==GL_MODELVIEW) matrixload=currentContext->model_matrix[currentContext->modelMatrixStackPos].m;
	if (currentContext->matrixMode==GL_TEXTURE) {
		int id=currentContext->multyTextId;
		matrixload=currentContext->text_matrix[id][currentContext->textMatrixStackPos[id]].m;
	}
	if (matrixload) vecFunctions.M4FAddTranslate(matrixload,&translate,matrixload);
}

void _APICALL glVertexPointer(int count,int type,int step,void* data)
{
	currentContext->vertexArray.count=count;
	currentContext->vertexArray.type=type;
	currentContext->vertexArray.step=step;
	currentContext->vertexArray.data=data;
}

void _APICALL glViewport(int a,int b,int c,int d)
{
	currentContext->viewPort=bt::vector4i(a,b,c,d);
}

}

OPTIMIZE_OFF;

#endif