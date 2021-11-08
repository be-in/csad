/*
 * qnxglextention.cpp
 *
 *  Created on: 05.02.2014
 *      Author: Пантелеймонов А
 */

#include <platform/platformapi.h>

#if defined (OS_QNX)

#include "qnxglextention.h"

namespace csad {

void glReadExtention(Context_P *_context)
{
	if ((!_context) || (_context->initialize)) return;
	_context->initialize=true;

	char *glex=(char *)glGetString(GL_EXTENSIONS);
	_context->_GL_EXT_stencil_two_side=(strstr(glex,"GL_EXT_stencil_two_side")!=0);
	_context->_GL_EXT_stencil_wrap=(strstr(glex,"GL_EXT_stencil_wrap")!=0);
	_context->_GL_ARB_shader=(strstr(glex,"GL_ARB_fragment_program")!=0) || (strstr(glex,"GL_ARB_vertex_program")!=0);
	//_GL_ARB_shader=false;

	_context->glActiveStencilFaceEXT=(void (_APICALL *)(GLuint _face))eglGetProcAddress("glActiveStencilFaceEXT");
	_context->glAreTexturesResidentEXT=(GLboolean (_APICALL *)(GLsizei _n, GLuint *_textures, GLboolean *_residences))eglGetProcAddress("glActiveStencilFaceEXT");
	_context->glArrayElementArrayEXT=(void (_APICALL *)(GLenum _mode, GLsizei _count, void *pi))eglGetProcAddress("glArrayElementArrayEXT");
	_context->glBeginSceneEXT=(void (_APICALL *)())eglGetProcAddress("glBeginSceneEXT");
	_context->glBindTextureEXT=(void (_APICALL *)(GLenum target, GLuint texture))eglGetProcAddress("glBindTextureEXT");
	_context->glColorTableEXT=(void (_APICALL *)(GLenum target, GLenum internalFormat, GLsizei width, GLenum format, GLenum atype, void * data))eglGetProcAddress("glColorTableEXT");

	_context->glDeleteTexturesEXT=(void (_APICALL *)(GLsizei n, GLuint *textures))eglGetProcAddress("glDeleteTexturesEXT");
	_context->glEndSceneEXT=(void (_APICALL *)())eglGetProcAddress("glEndSceneEXT");
	_context->glGenTexturesEXT=(void (_APICALL *)(GLsizei n, GLuint *textures))eglGetProcAddress("glGenTexturesEXT");
	_context->glIsTextureEXT=(GLboolean (_APICALL *)(GLuint ))eglGetProcAddress("glIsTextureEXT");
	_context->glLockArraysEXT=(void (_APICALL *)(GLint ,GLsizei ))eglGetProcAddress("glLockArraysEXT");
	_context->glUnlockArraysEXT=(void (_APICALL *)())eglGetProcAddress("glUnlockArraysEXT");

	_context->glArrayElementEXT=(void (_APICALL *)(GLint))eglGetProcAddress("glArrayElementEXT");
	_context->glColorPointerEXT=(void (_APICALL *)(GLint, GLenum, GLsizei, GLsizei, const GLvoid *))eglGetProcAddress("glColorPointerEXT");
	_context->glDrawArraysEXT=(void (_APICALL *)(GLenum, GLint, GLsizei))eglGetProcAddress("glDrawArraysEXT");
	_context->glEdgeFlagPointerEXT=(void (_APICALL *)(GLsizei, GLsizei, const GLboolean *))eglGetProcAddress("glEdgeFlagPointerEXT");
	_context->glGetPointervEXT=(void (_APICALL *)(GLenum, GLvoid* *))eglGetProcAddress("glGetPointervEXT");
	_context->glIndexPointerEXT=(void (_APICALL *)(GLenum, GLsizei, GLsizei, const GLvoid *))eglGetProcAddress("glIndexPointerEXT");
	_context->glNormalPointerEXT=(void (_APICALL *)(GLenum, GLsizei, GLsizei, const GLvoid *))eglGetProcAddress("glNormalPointerEXT");
	_context->glTexCoordPointerEXT=(void (_APICALL *)(GLint, GLenum, GLsizei, GLsizei, const GLvoid *))eglGetProcAddress("glTexCoordPointerEXT");
	_context->glVertexPointerEXT=(void (_APICALL *)(GLint, GLenum, GLsizei, GLsizei, const GLvoid *))eglGetProcAddress("glVertexPointerEXT");
	_context->glTangentPointerEXT=(void (_APICALL *)(GLenum,GLsizei, const GLvoid *))eglGetProcAddress("glTangentPointerEXT");
	_context->glBinormalPointerEXT=(void (_APICALL *)(GLenum,GLsizei, const GLvoid *))eglGetProcAddress("glBinormalPointerEXT");
	_context->glSwapIntervalEXT=(GLboolean (_APICALL *)(GLint))eglGetProcAddress("wglSwapIntervalEXT");

	_context->glGenBuffers=(void (_APICALL *)(GLsizei, GLuint *))eglGetProcAddress("glGenBuffersARB");
	_context->glDeleteBuffers=(void (_APICALL *)(GLsizei, const GLuint *))eglGetProcAddress("glDeleteBuffersARB");
	_context->glBindBuffer=(void (_APICALL *)(GLenum, GLuint))eglGetProcAddress("glBindBufferARB");
	_context->glIsBuffer=(GLboolean (_APICALL *)(GLuint))eglGetProcAddress("glIsBufferARB");
	_context->glMapBuffer=(GLvoid* (_APICALL *)(GLenum, GLenum))eglGetProcAddress("glMapBufferARB");
	_context->glUnmapBuffer=(GLboolean (_APICALL *)(GLenum))eglGetProcAddress("glUnmapBufferARB");
	_context->glGetBufferParameteriv=(void (_APICALL *)(GLenum, GLenum, GLint *))eglGetProcAddress("glGetBufferParameterivARB");
	_context->glGetBufferPointerv=(void (_APICALL *)(GLenum, GLenum, GLvoid* *))eglGetProcAddress("glGetBufferPointervARB");
	_context->glBufferData=(void (_APICALL *)(GLenum, GLsizei, const GLvoid *, GLenum))eglGetProcAddress("glBufferDataARB");
	_context->glBufferSubData=(void (_APICALL *)(GLenum, GLint , GLsizei, const GLvoid *))eglGetProcAddress("glBufferSubDataARB");

	_context->glCompileShader=(void (_APICALL *)(GLuint))eglGetProcAddress("glCompileShader");
	_context->glCreateProgram=(GLuint (_APICALL *)(void))eglGetProcAddress("glCreateProgram");
	_context->glCreateShader=(GLuint (_APICALL *)(GLenum))eglGetProcAddress("glCreateShader");
	_context->glDeleteProgram=(void (_APICALL *)(GLuint))eglGetProcAddress("glDeleteProgram");
	_context->glDeleteShader=(void (_APICALL *)(GLuint))eglGetProcAddress("glDeleteShader");
	_context->glUseProgram=(void (_APICALL *)(GLuint))eglGetProcAddress("glUseProgram");
	_context->glGetProgramInfoLog=(void (_APICALL *) (GLuint, GLsizei, GLsizei *, char *))eglGetProcAddress("glGetProgramInfoLog");
	_context->glAttachShader=(void (_APICALL *) (GLuint, GLuint))eglGetProcAddress("glAttachShader");
	_context->glLinkProgram=(void (_APICALL *) (GLuint))eglGetProcAddress("glLinkProgram");
	_context->glShaderSource=(void (_APICALL *) (GLuint, GLsizei, const char**, const GLint *))eglGetProcAddress("glShaderSource");
	_context->glGetProgramiv=(void (_APICALL *) (GLuint, GLenum, GLint *))eglGetProcAddress("glGetProgramiv");
	_context->glGetShaderiv=(void (_APICALL *) (GLuint, GLenum, GLint *))eglGetProcAddress("glGetShaderiv");
	_context->glGetUniformLocation=(GLuint (_APICALL *) (GLuint, const char *))eglGetProcAddress("glGetUniformLocation");
	_context->glUniform1f=(void (_APICALL *) (GLint, GLfloat))eglGetProcAddress("glUniform1f");
	_context->glUniform2f=(void (_APICALL *) (GLint, GLfloat, GLfloat))eglGetProcAddress("glUniform2f");
	_context->glUniform3f=(void (_APICALL *) (GLint, GLfloat, GLfloat, GLfloat))eglGetProcAddress("glUniform3f");
	_context->glUniform4f=(void (_APICALL *) (GLint, GLfloat, GLfloat, GLfloat, GLfloat))eglGetProcAddress("glUniform4f");
	_context->glUniform1i=(void (_APICALL *) (GLint, GLint))eglGetProcAddress("glUniform1i");
	_context->glUniform2i=(void (_APICALL *) (GLint, GLint, GLint))eglGetProcAddress("glUniform2i");
	_context->glUniform3i=(void (_APICALL *) (GLint, GLint, GLint, GLint))eglGetProcAddress("glUniform3i");
	_context->glUniform4i=(void (_APICALL *) (GLint, GLint, GLint, GLint, GLint))eglGetProcAddress("glUniform4i");
	_context->glUniform1fv=(void (_APICALL *) (GLint, GLsizei, const GLfloat *))eglGetProcAddress("glUniform1fv");
	_context->glUniform2fv=(void (_APICALL *) (GLint, GLsizei, const GLfloat *))eglGetProcAddress("glUniform2fv");
	_context->glUniform3fv=(void (_APICALL *) (GLint, GLsizei, const GLfloat *))eglGetProcAddress("glUniform3fv");
	_context->glUniform4fv=(void (_APICALL *) (GLint, GLsizei, const GLfloat *))eglGetProcAddress("glUniform4fv");
	_context->glUniform1iv=(void (_APICALL *) (GLint, GLsizei, const GLint *))eglGetProcAddress("glUniform1iv");
	_context->glUniform2iv=(void (_APICALL *) (GLint, GLsizei, const GLint *))eglGetProcAddress("glUniform2iv");
	_context->glUniform3iv=(void (_APICALL *) (GLint, GLsizei, const GLint *))eglGetProcAddress("glUniform3iv");
	_context->glUniform4iv=(void (_APICALL *) (GLint, GLsizei, const GLint *))eglGetProcAddress("glUniform4iv");
	_context->glUniformMatrix2fv=(void (_APICALL *) (GLint, GLsizei, GLboolean, const GLfloat *))eglGetProcAddress("glUniformMatrix2fv");
	_context->glUniformMatrix3fv=(void (_APICALL *) (GLint, GLsizei, GLboolean, const GLfloat *))eglGetProcAddress("glUniformMatrix3fv");
	_context->glUniformMatrix4fv=(void (_APICALL *) (GLint, GLsizei, GLboolean, const GLfloat *))eglGetProcAddress("glUniformMatrix4fv");

	_context->_GL_ARB_vertex_buffer_object=(
		_context->glGenBuffers && _context->glBindBuffer && _context->glBufferData &&
		_context->glBufferSubData && _context->glMapBuffer && _context->glUnmapBuffer &&
		_context->glDeleteBuffers && _context->glGetBufferParameteriv);
}

}

#endif