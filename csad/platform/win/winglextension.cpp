/*
 * winglextention.cpp
 *
 *  Created on: 14.08.2013
 *      Author: Пантелеймонов Александр
 */

#include <platform/platformapi.h>
#include <core/system.h>
#include <core/module.h>
#include <platform/library.h>
#include <bt/types.h>

#if defined (OS_WIN)

#include "winglextension.h"

OPTIMIZE_ON;

namespace csad {

char* openglmodulename=(char*)"opengl";

Module * glLib()
{
	Module *module=System::system().getModule(openglmodulename);
	if (!module) {
		ShortString cpath;
//#ifdef CPU_X86_32
		Library::findLib(&cpath,"","opengl32");
//#else
//		Library::findLib(&cpath,"","opengl");
//#endif
		module=System::system().createModule(cpath.str(),openglmodulename);
	}
	if (!module->isInit() || !module) {
#ifdef LOG_CSAD
		Log::console("glReadExtention: Can't use opengl library!");
#endif
		return 0;
	}
	return module;
}

//#define GLProc(set,name,type) set=(type)module->wglGetProcAddress(name)

void glBasefunctions(Context_P *_context)
{
	if ((!_context) || (_context->initialize)) return;

	Module *module=glLib();

	_context->GetProcAddress=(bt::tfSTDCALL_p_FUNC_p)module->getProc("wglGetProcAddress");
	_context->CreateContext=(bt::tfSTDCALL_p_FUNC_p)module->getProc("wglCreateContext");
	_context->DeleteContext=(bt::tfSTDCALL_bool_FUNC_p)module->getProc("wglDeleteContext");
	_context->GetCurrentContext=(bt::tfSTDCALL_p_FUNC)module->getProc("wglGetCurrentContext");
	_context->MakeCurrent=(bt::tfSTDCALL_bool_FUNC_p_p)module->getProc("wglMakeCurrent");
}

void glReadExtention(Context_P *_context)
{
	if ((!_context) || (_context->initialize)) return;
	_context->initialize=true;
}

#define INITGLPROCS(module,name) void *local; \
	bt::tfSTDCALL_p_FUNC_p lGetProcAddress=(bt::tfSTDCALL_p_FUNC_p)module->getProc(name);
#define WGLProc(name,set,type) local=(void*)(lGetProcAddress((char*)name)); if (local) {set=(type)local;}// else {Log::console("WGLProc null %s",name);}
#define GLProc(name,set,type) local=(void*)(module->getProc(name)); if (local) {set=(type)local;}// else {Log::console("getProc null %s",name);}

char localGLname[]="gl************************************";

char *tmpGLNames[]={"AlphaFunc","AttachShader","BindBuffer","BindTexture",
	"BlendFunc","BufferData","BufferSubData","Color4f","Color4fv","ColorMaterial","ColorPointer",
	"CompileShader","Clear","ClearAccum","ClearColor","ClearDepth","CreateProgram","CreateShader",
	"CullFace","DeleteBuffers","DeleteProgram","DeleteShader","DeleteTextures","DepthFunc","DepthMask",
	"Disable","DisableClientState","DrawElements","Enable","EnableClientState","Finish","Flush","GenBuffers",
	"GenTextures","GetAttachedShaders","GetBooleanv","GetBufferParameteriv","GetBufferPointerv",
	"GetBufferSubData","GetDoublev","GetError","GetFloatv","GetIntegerv","GetProgramiv",
	"GetProgramInfoLog","GetShaderiv","GetString","GetTexParameteriv","GetUniformLocation","Hint",
	"InitNames","IsBuffer","IsEnabled","LightModelfv","Lightfv","LineWidth","LinkProgram",
	"LoadIdentity","LoadMatrixf","LoadMatrixd","LoadName","MapBuffer","Materialfv","MatrixMode",
	"MultMatrixd","MultMatrixf","NormalPointer","PointSize","PopAttrib","PopMatrix","PopName",
	"PushAttrib","PushMatrix","PushName","ReadPixels","RenderMode","Scalef","Scissor","SelectBuffer","ShaderSource",
	"SwapInterval","TexCoordPointer","TexImage2D","TexParameteri","TexSubImage2D","Translatef",
	"Uniform1f","Uniform2f","Uniform3f","Uniform4f","Uniform1iv","Uniform1fv","Uniform2iv","Uniform2fv",
	"Uniform3iv","Uniform3fv","Uniform4iv","Uniform4fv","UnmapBuffer","UseProgram","VertexPointer","Viewport",
	0};

void glInitGLFunctions(void *_conteiner)
{
	bt::sFunctionsGLContext *as=(bt::sFunctionsGLContext *)_conteiner;
	as->version=0;

	Module *module=glLib();

	INITGLPROCS(module,"wglGetProcAddress");

	extFunctions.CleanMem(as,sizeof(bt::sFunctionsGLContext));

	void **funcs=(void**)&as->AlphaFunc;
	char **names=tmpGLNames;
	while (*names) {
		int ss=extFunctions.FindCMem(*names,0,256)+1;
		extFunctions.MoveMem(*names,localGLname+2,ss);
		local=(void*)(module->getProc(localGLname));
		if (local) {*funcs=(void*)local;}
		funcs++;
		names++;
	}

	funcs=(void**)&as->AlphaFunc;
	names=tmpGLNames;
	while (*names) {
		int ss=extFunctions.FindCMem(*names,0,256)+1;
		extFunctions.MoveMem(*names,localGLname+2,ss);
		local=(void*)(lGetProcAddress((char*)localGLname));
		if (local) {*funcs=(void*)local;}
		funcs++;
		names++;
	}

	/*WGLProc("glAttachShader",as->AttachShader,bt::tfSTDCALL_PROC_uint_uint);
	WGLProc("glBindTexture",as->BindTexture,bt::tfSTDCALL_PROC_uint_uint);
	WGLProc("glBindBufferARB",as->BindBuffer,bt::tfSTDCALL_PROC_uint_uint);
	WGLProc("glBufferDataARB",as->BufferData,bt::tfSTDCALL_PROC_uint_int_p_uint);
	WGLProc("glBufferSubDataARB",as->BufferSubData,bt::tfSTDCALL_PROC_uint_int_int_p);
	WGLProc("glCompileShader",as->CompileShader,bt::tfSTDCALL_PROC_uint);
	WGLProc("glCreateProgram",as->CreateProgram,bt::tfSTDCALL_uint_FUNC);
	WGLProc("glCreateShader",as->CreateShader,bt::tfSTDCALL_uint_FUNC_uint);
	WGLProc("glDeleteBuffersARB",as->DeleteBuffers,bt::tfSTDCALL_PROC_int_p);
	WGLProc("glDeleteProgram",as->DeleteProgram,bt::tfSTDCALL_PROC_uint);
	WGLProc("glDisable",as->Disable,bt::tfSTDCALL_PROC_uint);
	WGLProc("glDisableClientState",as->DisableClientState,bt::tfSTDCALL_PROC_uint);
	WGLProc("glDrawElements",as->DrawElements,bt::tfSTDCALL_PROC_uint_int_uint_p);
	WGLProc("glEnable",as->Enable,bt::tfSTDCALL_PROC_uint);
	WGLProc("glEnableClientState",as->EnableClientState,bt::tfSTDCALL_PROC_uint);
	WGLProc("glGetAttachedShaders",as->GetAttachedShaders,bt::tfSTDCALL_PROC_uint_int_p_p);
	WGLProc("glGenBuffersARB",as->GenBuffers,bt::tfSTDCALL_PROC_int_p);
	WGLProc("glGetBufferParameterivARB",as->GetBufferParameteriv,bt::tfSTDCALL_PROC_uint_uint_p);
	WGLProc("glGetBufferPointervARB",as->GetBufferPointerv,bt::tfSTDCALL_PROC_uint_uint_p);
	WGLProc("glGetProgramInfoLog",as->GetProgramInfoLog,bt::tfSTDCALL_PROC_uint_int_p_p);
	WGLProc("glGetProgramiv",as->GetProgramiv,bt::tfSTDCALL_PROC_uint_uint_p);
	WGLProc("glGetShaderiv",as->GetShaderiv,bt::tfSTDCALL_PROC_uint_uint_p);
	WGLProc("glGetUniformLocation",as->GetUniformLocation,bt::tfSTDCALL_uint_FUNC_uint_p);
	WGLProc("glIsBufferARB",as->IsBuffer,bt::tfSTDCALL_bool_FUNC_uint);
	WGLProc("glLinkProgram",as->LinkProgram,bt::tfSTDCALL_PROC_uint);
	WGLProc("glLoadIdentity",as->LoadIdentity,bt::tfSTDCALL_PROC);
	WGLProc("glLoadMatrixd",as->LoadMatrixd,bt::tfSTDCALL_PROC_p);
	WGLProc("glLoadMatrixf",as->LoadMatrixf,bt::tfSTDCALL_PROC_p);
	WGLProc("glMapBufferARB",as->MapBuffer,bt::tfSTDCALL_p_FUNC_uint_uint);
	WGLProc("glMaterialfv",as->Materialfv,bt::tfSTDCALL_PROC_uint_uint_p);
	WGLProc("glMatrixMode",as->MatrixMode,bt::tfSTDCALL_PROC_uint);
	WGLProc("glNormalPointer",as->NormalPointer,bt::tfSTDCALL_PROC_uint_int_p);
	WGLProc("glPopMatrix",as->PopMatrix,bt::tfSTDCALL_PROC);
	WGLProc("glPushMatrix",as->PushMatrix,bt::tfSTDCALL_PROC);
	WGLProc("glRenderMode",as->RenderMode,bt::tfSTDCALL_int_FUNC_uint);
	WGLProc("glShaderSource",as->ShaderSource,bt::tfSTDCALL_PROC_uint_int_p_p);*/
	WGLProc("wglSwapIntervalEXT",as->SwapInterval,bt::tfSTDCALL_bool_FUNC_int);
	/*WGLProc("glTexCoordPointer",as->TexCoordPointer,bt::tfSTDCALL_PROC_int_uint_int_p);
	WGLProc("glTexImage2D",as->TexImage2D,bt::tfSTDCALL_PROC_uint_int_int_int_int_int_uint_uint_p);
	WGLProc("glTexSubImage2D",as->TexSubImage2D,bt::tfSTDCALL_PROC_uint_int_int_int_int_int_uint_uint_p);
	WGLProc("glTranslatef",as->Translatef,bt::tfSTDCALL_PROC_float_float_float);
	WGLProc("glUniform1fv",as->Uniformfv,bt::tfSTDCALL_PROC_uint_int_p);
	WGLProc("glUniform2fv",as->Uniform2fv,bt::tfSTDCALL_PROC_uint_int_p);
	WGLProc("glUniform3fv",as->Uniform3fv,bt::tfSTDCALL_PROC_uint_int_p);
	WGLProc("glUniform4fv",as->Uniform4fv,bt::tfSTDCALL_PROC_uint_int_p);
	WGLProc("glUnmapBufferARB",as->UnmapBuffer,bt::tfSTDCALL_bool_FUNC_uint);
	WGLProc("glUseProgram",as->UseProgram,bt::tfSTDCALL_PROC_uint);
	WGLProc("glVertexPointer",as->VertexPointer,bt::tfSTDCALL_PROC_int_uint_int_p);
	WGLProc("glViewport",as->Viewport,bt::tfSTDCALL_PROC_int_int_int_int);*/
}

}

OPTIMIZE_OFF;

#endif
