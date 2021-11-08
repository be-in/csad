/*
 * linuxglextention.cpp
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>
#include <core/system.h>
#include <core/module.h>
#include <platform/library.h>
#include <bt/types.h>

#if defined (OS_LINUX)

#include "linuxglextention.h"

OPTIMIZE_ON;

namespace csad {

char* openglmodulename=(char*)"opengl";

Module * glLib()
{
	Module *module=System::system().getModule(openglmodulename);
	if (!module) {
		BaseString cpath;
		Library::findLib(&cpath,"","GL");
		module=System::system().createModule(cpath.str(),openglmodulename);
	}
	if (!module->isInit() || !module) {
		Log::console("glReadExtention: Can't use opengl library!");
		return 0;
	}
	return module;
}

void glBasefunctions(Context_P *_context)
{
	if ((!_context) || (_context->initialize)) return;

	Module *module=glLib();

	_context->GetProcAddress=(bt::tfSTDCALL_p_FUNC_p)module->getProc("glXGetProcAddress");
	_context->CreateContext=(bt::tfSTDCALL_p_FUNC_p_p_p_int)module->getProc("glXCreateContext");
	_context->DestroyContext=(bt::tfSTDCALL_PROC_p_p)module->getProc("glXDestroyContext");
	_context->GetCurrentContext=(bt::tfSTDCALL_p_FUNC)module->getProc("glXGetCurrentContext");
	_context->MakeCurrent=(bt::tfSTDCALL_int_FUNC_p_p_p)module->getProc("glXMakeCurrent");
	_context->SwapBuffers=(bt::tfSTDCALL_PROC_p_p)module->getProc("glXSwapBuffers");
	_context->GetString=(bt::tfSTDCALL_p_FUNC_uint)module->getProc("glGetString");
}

void glReadExtention(Context_P *_context)
{
	if ((!_context) || (_context->initialize)) return;
	_context->initialize=true;

	/*char *glex=(char *)glGetString(GL_EXTENSIONS);
	_context->_GL_EXT_stencil_two_side=(strstr(glex,"GL_EXT_stencil_two_side")!=0);
	_context->_GL_EXT_stencil_wrap=(strstr(glex,"GL_EXT_stencil_wrap")!=0);
	_context->_GL_ARB_shader=(strstr(glex,"GL_ARB_fragment_program")!=0) || (strstr(glex,"GL_ARB_vertex_program")!=0);
	//_GL_ARB_shader=false;

	_context->glActiveStencilFaceEXT=(void (_STDCALL *)(GLuint _face))glXGetProcAddress((const unsigned char *)"glActiveStencilFaceEXT");
	_context->glAreTexturesResidentEXT=(GLboolean (_STDCALL *)(GLsizei _n, GLuint *_textures, GLboolean *_residences))glXGetProcAddress((const unsigned char *)"glActiveStencilFaceEXT");
	_context->glArrayElementArrayEXT=(void (_STDCALL *)(GLenum _mode, GLsizei _count, void *pi))glXGetProcAddress((const unsigned char *)"glArrayElementArrayEXT");
	_context->glBeginSceneEXT=(void (_STDCALL *)())glXGetProcAddress((const unsigned char *)"glBeginSceneEXT");
	_context->glBindTextureEXT=(void (_STDCALL *)(GLenum target, GLuint texture))glXGetProcAddress((const unsigned char *)"glBindTextureEXT");
	_context->glColorTableEXT=(void (_STDCALL *)(GLenum target, GLenum internalFormat, GLsizei width, GLenum format, GLenum atype, void * data))glXGetProcAddress((const unsigned char *)"glColorTableEXT");

	_context->glDeleteTexturesEXT=(void (_STDCALL *)(GLsizei n, GLuint *textures))glXGetProcAddress((const unsigned char *)"glDeleteTexturesEXT");
	_context->glEndSceneEXT=(void (_STDCALL *)())glXGetProcAddress((const unsigned char *)"glEndSceneEXT");
	_context->glGenTexturesEXT=(void (_STDCALL *)(GLsizei n, GLuint *textures))glXGetProcAddress((const unsigned char *)"glGenTexturesEXT");
	_context->glIsTextureEXT=(GLboolean (_STDCALL *)(GLuint ))glXGetProcAddress((const unsigned char *)"glIsTextureEXT");
	_context->glLockArraysEXT=(void (_STDCALL *)(GLint ,GLsizei ))glXGetProcAddress((const unsigned char *)"glLockArraysEXT");
	_context->glUnlockArraysEXT=(void (_STDCALL *)())glXGetProcAddress((const unsigned char *)"glUnlockArraysEXT");

	_context->glArrayElementEXT=(void (_STDCALL *)(GLint))glXGetProcAddress((const unsigned char *)"glArrayElementEXT");
	_context->glColorPointerEXT=(void (_STDCALL *)(GLint, GLenum, GLsizei, GLsizei, const GLvoid *))glXGetProcAddress((const unsigned char *)"glColorPointerEXT");
	_context->glDrawArraysEXT=(void (_STDCALL *)(GLenum, GLint, GLsizei))glXGetProcAddress((const unsigned char *)"glDrawArraysEXT");
	_context->glEdgeFlagPointerEXT=(void (_STDCALL *)(GLsizei, GLsizei, const GLboolean *))glXGetProcAddress((const unsigned char *)"glEdgeFlagPointerEXT");
	_context->glGetPointervEXT=(void (_STDCALL *)(GLenum, GLvoid* *))glXGetProcAddress((const unsigned char *)"glGetPointervEXT");
	_context->glIndexPointerEXT=(void (_STDCALL *)(GLenum, GLsizei, GLsizei, const GLvoid *))glXGetProcAddress((const unsigned char *)"glIndexPointerEXT");
	_context->glNormalPointerEXT=(void (_STDCALL *)(GLenum, GLsizei, GLsizei, const GLvoid *))glXGetProcAddress((const unsigned char *)"glNormalPointerEXT");
	_context->glTexCoordPointerEXT=(void (_STDCALL *)(GLint, GLenum, GLsizei, GLsizei, const GLvoid *))glXGetProcAddress((const unsigned char *)"glTexCoordPointerEXT");
	_context->glVertexPointerEXT=(void (_STDCALL *)(GLint, GLenum, GLsizei, GLsizei, const GLvoid *))glXGetProcAddress((const unsigned char *)"glVertexPointerEXT");
	_context->glTangentPointerEXT=(void (_STDCALL *)(GLenum,GLsizei, const GLvoid *))glXGetProcAddress((const unsigned char *)"glTangentPointerEXT");
	_context->glBinormalPointerEXT=(void (_STDCALL *)(GLenum,GLsizei, const GLvoid *))glXGetProcAddress((const unsigned char *)"glBinormalPointerEXT");
	_context->glSwapIntervalEXT=(GLboolean (_STDCALL *)(GLint))glXGetProcAddress((const unsigned char *)"wglSwapIntervalEXT");

	_context->glGenBuffers=(void (_STDCALL *)(GLsizei, GLuint *))glXGetProcAddress((const unsigned char *)"glGenBuffersARB");
	_context->glDeleteBuffers=(void (_STDCALL *)(GLsizei, const GLuint *))glXGetProcAddress((const unsigned char *)"glDeleteBuffersARB");
	_context->glBindBuffer=(void (_STDCALL *)(GLenum, GLuint))glXGetProcAddress((const unsigned char *)"glBindBufferARB");
	_context->glIsBuffer=(GLboolean (_STDCALL *)(GLuint))glXGetProcAddress((const unsigned char *)"glIsBufferARB");
	_context->glMapBuffer=(GLvoid* (_STDCALL *)(GLenum, GLenum))glXGetProcAddress((const unsigned char *)"glMapBufferARB");
	_context->glUnmapBuffer=(GLboolean (_STDCALL *)(GLenum))glXGetProcAddress((const unsigned char *)"glUnmapBufferARB");
	_context->glGetBufferParameteriv=(void (_STDCALL *)(GLenum, GLenum, GLint *))glXGetProcAddress((const unsigned char *)"glGetBufferParameterivARB");
	_context->glGetBufferPointerv=(void (_STDCALL *)(GLenum, GLenum, GLvoid* *))glXGetProcAddress((const unsigned char *)"glGetBufferPointervARB");
	_context->glBufferData=(void (_STDCALL *)(GLenum, GLsizei, const GLvoid *, GLenum))glXGetProcAddress((const unsigned char *)"glBufferDataARB");
	_context->glBufferSubData=(void (_STDCALL *)(GLenum, GLint , GLsizei, const GLvoid *))glXGetProcAddress((const unsigned char *)"glBufferSubDataARB");
	
	_context->glCompileShader=(void (_STDCALL *)(GLuint))glXGetProcAddress((const unsigned char *)"glCompileShader");
	_context->glCreateProgram=(GLuint (_STDCALL *)(void))glXGetProcAddress((const unsigned char *)"glCreateProgram");
	_context->glCreateShader=(GLuint (_STDCALL *)(GLenum))glXGetProcAddress((const unsigned char *)"glCreateShader");
	_context->glDeleteProgram=(void (_STDCALL *)(GLuint))glXGetProcAddress((const unsigned char *)"glDeleteProgram");
	_context->glDeleteShader=(void (_STDCALL *)(GLuint))glXGetProcAddress((const unsigned char *)"glDeleteShader");
	_context->glUseProgram=(void (_STDCALL *)(GLuint))glXGetProcAddress((const unsigned char *)"glUseProgram");
	_context->glGetProgramInfoLog=(void (_STDCALL *) (GLuint, GLsizei, GLsizei *, char *))glXGetProcAddress((const unsigned char *)"glGetProgramInfoLog");
	_context->glAttachShader=(void (_STDCALL *) (GLuint, GLuint))glXGetProcAddress((const unsigned char *)"glAttachShader");
	_context->glLinkProgram=(void (_STDCALL *) (GLuint))glXGetProcAddress((const unsigned char *)"glLinkProgram");
	_context->glShaderSource=(void (_STDCALL *) (GLuint, GLsizei, const char**, const GLint *))glXGetProcAddress((const unsigned char *)"glShaderSource");
	_context->glGetProgramiv=(void (_STDCALL *) (GLuint, GLenum, GLint *))glXGetProcAddress((const unsigned char *)"glGetProgramiv");
	_context->glGetShaderiv=(void (_STDCALL *) (GLuint, GLenum, GLint *))glXGetProcAddress((const unsigned char *)"glGetShaderiv");
	_context->glGetUniformLocation=(GLuint (_STDCALL *) (GLuint, const char *))glXGetProcAddress((const unsigned char *)"glGetUniformLocation");
	_context->glUniform1f=(void (_STDCALL *) (GLint, GLfloat))glXGetProcAddress((const unsigned char *)"glUniform1f");
	_context->glUniform2f=(void (_STDCALL *) (GLint, GLfloat, GLfloat))glXGetProcAddress((const unsigned char *)"glUniform2f");
	_context->glUniform3f=(void (_STDCALL *) (GLint, GLfloat, GLfloat, GLfloat))glXGetProcAddress((const unsigned char *)"glUniform3f");
	_context->glUniform4f=(void (_STDCALL *) (GLint, GLfloat, GLfloat, GLfloat, GLfloat))glXGetProcAddress((const unsigned char *)"glUniform4f");
	_context->glUniform1i=(void (_STDCALL *) (GLint, GLint))glXGetProcAddress((const unsigned char *)"glUniform1i");
	_context->glUniform2i=(void (_STDCALL *) (GLint, GLint, GLint))glXGetProcAddress((const unsigned char *)"glUniform2i");
	_context->glUniform3i=(void (_STDCALL *) (GLint, GLint, GLint, GLint))glXGetProcAddress((const unsigned char *)"glUniform3i");
	_context->glUniform4i=(void (_STDCALL *) (GLint, GLint, GLint, GLint, GLint))glXGetProcAddress((const unsigned char *)"glUniform4i");
	_context->glUniform1fv=(void (_STDCALL *) (GLint, GLsizei, const GLfloat *))glXGetProcAddress((const unsigned char *)"glUniform1fv");
	_context->glUniform2fv=(void (_STDCALL *) (GLint, GLsizei, const GLfloat *))glXGetProcAddress((const unsigned char *)"glUniform2fv");
	_context->glUniform3fv=(void (_STDCALL *) (GLint, GLsizei, const GLfloat *))glXGetProcAddress((const unsigned char *)"glUniform3fv");
	_context->glUniform4fv=(void (_STDCALL *) (GLint, GLsizei, const GLfloat *))glXGetProcAddress((const unsigned char *)"glUniform4fv");
	_context->glUniform1iv=(void (_STDCALL *) (GLint, GLsizei, const GLint *))glXGetProcAddress((const unsigned char *)"glUniform1iv");
	_context->glUniform2iv=(void (_STDCALL *) (GLint, GLsizei, const GLint *))glXGetProcAddress((const unsigned char *)"glUniform2iv");
	_context->glUniform3iv=(void (_STDCALL *) (GLint, GLsizei, const GLint *))glXGetProcAddress((const unsigned char *)"glUniform3iv");
	_context->glUniform4iv=(void (_STDCALL *) (GLint, GLsizei, const GLint *))glXGetProcAddress((const unsigned char *)"glUniform4iv");
	_context->glUniformMatrix2fv=(void (_STDCALL *) (GLint, GLsizei, GLboolean, const GLfloat *))glXGetProcAddress((const unsigned char *)"glUniformMatrix2fv");
	_context->glUniformMatrix3fv=(void (_STDCALL *) (GLint, GLsizei, GLboolean, const GLfloat *))glXGetProcAddress((const unsigned char *)"glUniformMatrix3fv");
	_context->glUniformMatrix4fv=(void (_STDCALL *) (GLint, GLsizei, GLboolean, const GLfloat *))glXGetProcAddress((const unsigned char *)"glUniformMatrix4fv");

	_context->_GL_ARB_vertex_buffer_object=(
		_context->glGenBuffers && _context->glBindBuffer && _context->glBufferData && 
		_context->glBufferSubData && _context->glMapBuffer && _context->glUnmapBuffer && 
		_context->glDeleteBuffers && _context->glGetBufferParameteriv);*/
}

#define INITGLPROCS(module,name) void *local; \
	bt::tfSTDCALL_p_FUNC_p lGetProcAddress=(bt::tfSTDCALL_p_FUNC_p)module->getProc(name);
#define OSGLProc(local,name,set,type) local=(void*)lGetProcAddress((void*)name); if (local) {set=(type)local;}// else {Log::console("WGLProc null %s",name);}
#define GLProc(name,set,type) local=(void*)module->getProc(name); if (local) {set=(type)local;}// else {Log::console("getProc null %s",name);}

void glInitGLFunctions(void *_conteiner)
{
	bt::sFunctionsGLContext *as=(bt::sFunctionsGLContext *)_conteiner;
	as->version=0;

	Module *module=glLib();

	INITGLPROCS(module,"glXGetProcAddress");

	extFunctions.CleanMem(as,sizeof(bt::sFunctionsGLContext));

	GLProc("glAlphaFunc",as->AlphaFunc,bt::tfSTDCALL_PROC_uint_float);
	GLProc("glBindBuffer",as->BindBuffer,bt::tfSTDCALL_PROC_uint_uint);
	GLProc("glBindTexture",as->BindTexture,bt::tfSTDCALL_PROC_uint_uint);
	GLProc("glBlendFunc",as->BlendFunc,bt::tfSTDCALL_PROC_uint_uint);
	GLProc("glBufferData",as->BufferData,bt::tfSTDCALL_PROC_uint_int_p_uint);
	GLProc("glBufferSubData",as->BufferSubData,bt::tfSTDCALL_PROC_uint_int_int_p);
	GLProc("glColor4f",as->Color4f,bt::tfSTDCALL_PROC_float_float_float_float);
	GLProc("glColor4fv",as->Color4fv,bt::tfSTDCALL_PROC_p);
	GLProc("glColorPointer",as->ColorPointer,bt::tfSTDCALL_PROC_int_uint_int_p);
	GLProc("glClear",as->Clear,bt::tfSTDCALL_PROC_uint);
	GLProc("glClearAccum",as->ClearAccum,bt::tfSTDCALL_PROC_float_float_float_float);
	GLProc("glClearColor",as->ClearColor,bt::tfSTDCALL_PROC_float_float_float_float);
	GLProc("glClearDepth",as->ClearDepth,bt::tfSTDCALL_PROC_double);
	GLProc("glCullFace",as->CullFace,bt::tfSTDCALL_PROC_uint);
	GLProc("glDeleteBuffers",as->DeleteBuffers,bt::tfSTDCALL_PROC_int_p);
	GLProc("glDeleteTextures",as->DeleteTextures,bt::tfSTDCALL_PROC_int_p);
	GLProc("glDepthFunc",as->DepthFunc,bt::tfSTDCALL_PROC_uint);
	GLProc("glDepthMask",as->DepthMask,bt::tfSTDCALL_PROC_bool);
	GLProc("glDisable",as->Disable,bt::tfSTDCALL_PROC_uint);
	GLProc("glDisableClientState",as->DisableClientState,bt::tfSTDCALL_PROC_uint);
	GLProc("glDrawElements",as->DrawElements,bt::tfSTDCALL_PROC_uint_int_uint_p);
	GLProc("glEnable",as->Enable,bt::tfSTDCALL_PROC_uint);
	GLProc("glEnableClientState",as->EnableClientState,bt::tfSTDCALL_PROC_uint);
	GLProc("glFinish",as->Finish,bt::tfSTDCALL_PROC);
	GLProc("glFlush",as->Flush,bt::tfSTDCALL_PROC);
	GLProc("glGenBuffers",as->GenBuffers,bt::tfSTDCALL_PROC_int_p);
	GLProc("glGenTextures",as->GenTextures,bt::tfSTDCALL_PROC_int_p);
	GLProc("glGetBooleanv",as->GetBooleanv,bt::tfSTDCALL_PROC_uint_p);
	GLProc("glGetBufferParameteriv",as->GetBufferParameteriv,bt::tfSTDCALL_PROC_uint_uint_p);
	GLProc("glGetBufferPointerv",as->GetBufferPointerv,bt::tfSTDCALL_PROC_uint_uint_p);
	GLProc("glGetDoublev",as->GetDoublev,bt::tfSTDCALL_PROC_uint_p);
	GLProc("glGetError",as->GetError,bt::tfSTDCALL_uint_FUNC);
	GLProc("glGetFloatv",as->GetFloatv,bt::tfSTDCALL_PROC_uint_p);
	GLProc("glGetIntegerv",as->GetIntegerv,bt::tfSTDCALL_PROC_uint_p);
	GLProc("glGetProgramiv",as->GetProgramiv,bt::tfSTDCALL_PROC_uint_uint_p);
	GLProc("glGetString",as->GetString,bt::tfSTDCALL_p_FUNC_uint);
	GLProc("glGetTexParameteriv",as->GetTexParameteriv,bt::tfSTDCALL_PROC_uint_uint_p);
	GLProc("glGetUniformLocation",as->GetUniformLocation,bt::tfSTDCALL_uint_FUNC_uint_p);
	GLProc("glHint",as->Hint,bt::tfSTDCALL_PROC_uint_uint);
	GLProc("glInitNames",as->InitNames,bt::tfSTDCALL_PROC);
	GLProc("glIsBuffer",as->IsBuffer,bt::tfSTDCALL_bool_FUNC_uint);
	GLProc("glIsEnabled",as->IsEnabled,bt::tfSTDCALL_bool_FUNC_uint);
	GLProc("glLightModelfv",as->LightModelfv,bt::tfSTDCALL_PROC_uint_uint_p);
	GLProc("glLightfv",as->Lightfv,bt::tfSTDCALL_PROC_uint_uint_p);
	GLProc("glLineWidth",as->LineWidth,bt::tfSTDCALL_PROC_float);
	GLProc("glLoadIdentity",as->LoadIdentity,bt::tfSTDCALL_PROC);
	GLProc("glLoadMatrixd",as->LoadMatrixd,bt::tfSTDCALL_PROC_p);
	GLProc("glLoadMatrixf",as->LoadMatrixf,bt::tfSTDCALL_PROC_p);
	GLProc("glLoadName",as->LoadName,bt::tfSTDCALL_PROC_uint);
	GLProc("glMapBuffer",as->MapBuffer,bt::tfSTDCALL_p_FUNC_uint_uint);
	GLProc("glMaterialfv",as->Materialfv,bt::tfSTDCALL_PROC_uint_uint_p);
	GLProc("glMatrixMode",as->MatrixMode,bt::tfSTDCALL_PROC_uint);
	GLProc("glMultMatrixd",as->MultMatrixd,bt::tfSTDCALL_PROC_p);
	GLProc("glMultMatrixf",as->MultMatrixf,bt::tfSTDCALL_PROC_p);
	GLProc("glNormalPointer",as->NormalPointer,bt::tfSTDCALL_PROC_uint_int_p);
	GLProc("glPointSize",as->PointSize,bt::tfSTDCALL_PROC_float);
	GLProc("glPopAttrib",as->PopAttrib,bt::tfSTDCALL_PROC);
	GLProc("glPopMatrix",as->PopMatrix,bt::tfSTDCALL_PROC);
	GLProc("glPopName",as->PopName,bt::tfSTDCALL_PROC);
	GLProc("glPushAttrib",as->PushAttrib,bt::tfSTDCALL_PROC_uint);
	GLProc("glPushMatrix",as->PushMatrix,bt::tfSTDCALL_PROC);
	GLProc("glPushName",as->PushName,bt::tfSTDCALL_PROC_uint);
	GLProc("glRenderMode",as->RenderMode,bt::tfSTDCALL_int_FUNC_uint);
	GLProc("glScalef",as->Scalef,bt::tfSTDCALL_PROC_float_float_float);
	GLProc("glScissor",as->Scissor,bt::tfSTDCALL_PROC_int_int_int_int);
	GLProc("glSelectBuffer",as->SelectBuffer,bt::tfSTDCALL_PROC_int_p);
	GLProc("glSwapInterval",as->SwapInterval,bt::tfSTDCALL_bool_FUNC_int);
	GLProc("glTexCoordPointer",as->TexCoordPointer,bt::tfSTDCALL_PROC_int_uint_int_p);
	GLProc("glTexImage2D",as->TexImage2D,bt::tfSTDCALL_PROC_uint_int_int_int_int_int_uint_uint_p);
	GLProc("glTexParameteri",as->TexParameteri,bt::tfSTDCALL_PROC_uint_uint_int);
	GLProc("glTexSubImage2D",as->TexSubImage2D,bt::tfSTDCALL_PROC_uint_int_int_int_int_int_uint_uint_p);
	GLProc("glTranslatef",as->Translatef,bt::tfSTDCALL_PROC_float_float_float);
	GLProc("glUnmapBuffer",as->UnmapBuffer,bt::tfSTDCALL_bool_FUNC_uint);
	GLProc("glVertexPointer",as->VertexPointer,bt::tfSTDCALL_PROC_int_uint_int_p);
	GLProc("glViewport",as->Viewport,bt::tfSTDCALL_PROC_int_int_int_int);

	OSGLProc(local,"glBindTexture",as->BindTexture,bt::tfSTDCALL_PROC_uint_uint);
	OSGLProc(local,"glBindBufferARB",as->BindBuffer,bt::tfSTDCALL_PROC_uint_uint);
	OSGLProc(local,"glBufferDataARB",as->BufferData,bt::tfSTDCALL_PROC_uint_int_p_uint);
	OSGLProc(local,"glBufferSubDataARB",as->BufferSubData,bt::tfSTDCALL_PROC_uint_int_int_p);
	OSGLProc(local,"glCompileShader",as->CompileShader,bt::tfSTDCALL_PROC_uint);
	OSGLProc(local,"glCreateProgram",as->CreateProgram,bt::tfSTDCALL_uint_FUNC);
	OSGLProc(local,"glDeleteBuffersARB",as->DeleteBuffers,bt::tfSTDCALL_PROC_int_p);
	OSGLProc(local,"glDisable",as->Disable,bt::tfSTDCALL_PROC_uint);
	OSGLProc(local,"glDisableClientState",as->DisableClientState,bt::tfSTDCALL_PROC_uint);
	OSGLProc(local,"glDrawElements",as->DrawElements,bt::tfSTDCALL_PROC_uint_int_uint_p);
	OSGLProc(local,"glEnable",as->Enable,bt::tfSTDCALL_PROC_uint);
	OSGLProc(local,"glEnableClientState",as->EnableClientState,bt::tfSTDCALL_PROC_uint);
	OSGLProc(local,"glGenBuffersARB",as->GenBuffers,bt::tfSTDCALL_PROC_int_p);
	OSGLProc(local,"glGetBufferParameterivARB",as->GetBufferParameteriv,bt::tfSTDCALL_PROC_uint_uint_p);
	OSGLProc(local,"glGetBufferPointervARB",as->GetBufferPointerv,bt::tfSTDCALL_PROC_uint_uint_p);
	OSGLProc(local,"glGetProgramInfoLogARB",as->GetProgramInfoLog,bt::tfSTDCALL_PROC_uint_int_p_p);
	OSGLProc(local,"glIsBufferARB",as->IsBuffer,bt::tfSTDCALL_bool_FUNC_uint);
	OSGLProc(local,"glLoadIdentity",as->LoadIdentity,bt::tfSTDCALL_PROC);
	OSGLProc(local,"glLoadMatrixd",as->LoadMatrixd,bt::tfSTDCALL_PROC_p);
	OSGLProc(local,"glLoadMatrixf",as->LoadMatrixf,bt::tfSTDCALL_PROC_p);
	OSGLProc(local,"glMapBufferARB",as->MapBuffer,bt::tfSTDCALL_p_FUNC_uint_uint);
	OSGLProc(local,"glMaterialfv",as->Materialfv,bt::tfSTDCALL_PROC_uint_uint_p);
	OSGLProc(local,"glMatrixMode",as->MatrixMode,bt::tfSTDCALL_PROC_uint);
	OSGLProc(local,"glNormalPointer",as->NormalPointer,bt::tfSTDCALL_PROC_uint_int_p);
	OSGLProc(local,"glPopMatrix",as->PopMatrix,bt::tfSTDCALL_PROC);
	OSGLProc(local,"glPushMatrix",as->PushMatrix,bt::tfSTDCALL_PROC);
	OSGLProc(local,"glRenderMode",as->RenderMode,bt::tfSTDCALL_int_FUNC_uint);
	OSGLProc(local,"glShaderSource",as->ShaderSource,bt::tfSTDCALL_PROC_uint_int_p_p);
	OSGLProc(local,"glXSwapInterval",as->SwapInterval,bt::tfSTDCALL_bool_FUNC_int);
	OSGLProc(local,"glTexCoordPointer",as->TexCoordPointer,bt::tfSTDCALL_PROC_int_uint_int_p);
	OSGLProc(local,"glTexImage2D",as->TexImage2D,bt::tfSTDCALL_PROC_uint_int_int_int_int_int_uint_uint_p);
	OSGLProc(local,"glTexSubImage2D",as->TexSubImage2D,bt::tfSTDCALL_PROC_uint_int_int_int_int_int_uint_uint_p);
	OSGLProc(local,"glTranslatef",as->Translatef,bt::tfSTDCALL_PROC_float_float_float);
	OSGLProc(local,"glUnmapBufferARB",as->UnmapBuffer,bt::tfSTDCALL_bool_FUNC_uint);
	OSGLProc(local,"glUseProgramARB",as->UseProgram,bt::tfSTDCALL_PROC_uint);
	OSGLProc(local,"glVertexPointer",as->VertexPointer,bt::tfSTDCALL_PROC_int_uint_int_p);
	OSGLProc(local,"glViewport",as->Viewport,bt::tfSTDCALL_PROC_int_int_int_int);
}

}

OPTIMIZE_OFF;

#endif
