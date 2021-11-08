/*
 * osxglextention.cpp
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>

#if defined (OS_OSX)

#include "osxglextention.h"

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

	_context->glActiveStencilFaceEXT=(void (_APICALL *)(GLuint _face))glXGetProcAddress((const unsigned char *)"glActiveStencilFaceEXT");
	_context->glAreTexturesResidentEXT=(GLboolean (_APICALL *)(GLsizei _n, GLuint *_textures, GLboolean *_residences))glXGetProcAddress((const unsigned char *)"glActiveStencilFaceEXT");
	_context->glArrayElementArrayEXT=(void (_APICALL *)(GLenum _mode, GLsizei _count, void *pi))glXGetProcAddress((const unsigned char *)"glArrayElementArrayEXT");
	_context->glBeginSceneEXT=(void (_APICALL *)())glXGetProcAddress((const unsigned char *)"glBeginSceneEXT");
	_context->glBindTextureEXT=(void (_APICALL *)(GLenum target, GLuint texture))glXGetProcAddress((const unsigned char *)"glBindTextureEXT");
	_context->glColorTableEXT=(void (_APICALL *)(GLenum target, GLenum internalFormat, GLsizei width, GLenum format, GLenum atype, void * data))glXGetProcAddress((const unsigned char *)"glColorTableEXT");

	_context->glDeleteTexturesEXT=(void (_APICALL *)(GLsizei n, GLuint *textures))glXGetProcAddress((const unsigned char *)"glDeleteTexturesEXT");
	_context->glEndSceneEXT=(void (_APICALL *)())glXGetProcAddress((const unsigned char *)"glEndSceneEXT");
	_context->glGenTexturesEXT=(void (_APICALL *)(GLsizei n, GLuint *textures))glXGetProcAddress((const unsigned char *)"glGenTexturesEXT");
	_context->glIsTextureEXT=(GLboolean (_APICALL *)(GLuint ))glXGetProcAddress((const unsigned char *)"glIsTextureEXT");
	_context->glLockArraysEXT=(void (_APICALL *)(GLint ,GLsizei ))glXGetProcAddress((const unsigned char *)"glLockArraysEXT");
	_context->glUnlockArraysEXT=(void (_APICALL *)())glXGetProcAddress((const unsigned char *)"glUnlockArraysEXT");

	_context->glArrayElementEXT=(void (_APICALL *)(GLint))glXGetProcAddress((const unsigned char *)"glArrayElementEXT");
	_context->glColorPointerEXT=(void (_APICALL *)(GLint, GLenum, GLsizei, GLsizei, const GLvoid *))glXGetProcAddress((const unsigned char *)"glColorPointerEXT");
	_context->glDrawArraysEXT=(void (_APICALL *)(GLenum, GLint, GLsizei))glXGetProcAddress((const unsigned char *)"glDrawArraysEXT");
	_context->glEdgeFlagPointerEXT=(void (_APICALL *)(GLsizei, GLsizei, const GLboolean *))glXGetProcAddress((const unsigned char *)"glEdgeFlagPointerEXT");
	_context->glGetPointervEXT=(void (_APICALL *)(GLenum, GLvoid* *))glXGetProcAddress((const unsigned char *)"glGetPointervEXT");
	_context->glIndexPointerEXT=(void (_APICALL *)(GLenum, GLsizei, GLsizei, const GLvoid *))glXGetProcAddress((const unsigned char *)"glIndexPointerEXT");
	_context->glNormalPointerEXT=(void (_APICALL *)(GLenum, GLsizei, GLsizei, const GLvoid *))glXGetProcAddress((const unsigned char *)"glNormalPointerEXT");
	_context->glTexCoordPointerEXT=(void (_APICALL *)(GLint, GLenum, GLsizei, GLsizei, const GLvoid *))glXGetProcAddress((const unsigned char *)"glTexCoordPointerEXT");
	_context->glVertexPointerEXT=(void (_APICALL *)(GLint, GLenum, GLsizei, GLsizei, const GLvoid *))glXGetProcAddress((const unsigned char *)"glVertexPointerEXT");
	_context->glTangentPointerEXT=(void (_APICALL *)(GLenum,GLsizei, const GLvoid *))glXGetProcAddress((const unsigned char *)"glTangentPointerEXT");
	_context->glBinormalPointerEXT=(void (_APICALL *)(GLenum,GLsizei, const GLvoid *))glXGetProcAddress((const unsigned char *)"glBinormalPointerEXT");
	_context->glSwapIntervalEXT=(GLboolean (_APICALL *)(GLint))glXGetProcAddress((const unsigned char *)"wglSwapIntervalEXT");

	_context->glGenBuffers=(void (_APICALL *)(GLsizei, GLuint *))glXGetProcAddress((const unsigned char *)"glGenBuffersARB");
	_context->glDeleteBuffers=(void (_APICALL *)(GLsizei, const GLuint *))glXGetProcAddress((const unsigned char *)"glDeleteBuffersARB");
	_context->glBindBuffer=(void (_APICALL *)(GLenum, GLuint))glXGetProcAddress((const unsigned char *)"glBindBufferARB");
	_context->glIsBuffer=(GLboolean (_APICALL *)(GLuint))glXGetProcAddress((const unsigned char *)"glIsBufferARB");
	_context->glMapBuffer=(GLvoid* (_APICALL *)(GLenum, GLenum))glXGetProcAddress((const unsigned char *)"glMapBufferARB");
	_context->glUnmapBuffer=(GLboolean (_APICALL *)(GLenum))glXGetProcAddress((const unsigned char *)"glUnmapBufferARB");
	_context->glGetBufferParameteriv=(void (_APICALL *)(GLenum, GLenum, GLint *))glXGetProcAddress((const unsigned char *)"glGetBufferParameterivARB");
	_context->glGetBufferPointerv=(void (_APICALL *)(GLenum, GLenum, GLvoid* *))glXGetProcAddress((const unsigned char *)"glGetBufferPointervARB");
	_context->glBufferData=(void (_APICALL *)(GLenum, GLsizei, const GLvoid *, GLenum))glXGetProcAddress((const unsigned char *)"glBufferDataARB");
	_context->glBufferSubData=(void (_APICALL *)(GLenum, GLint , GLsizei, const GLvoid *))glXGetProcAddress((const unsigned char *)"glBufferSubDataARB");
	
	_context->glCompileShader=(void (_APICALL *)(GLuint))glXGetProcAddress((const unsigned char *)"glCompileShader");
	_context->glCreateProgram=(GLuint (_APICALL *)(void))glXGetProcAddress((const unsigned char *)"glCreateProgram");
	_context->glCreateShader=(GLuint (_APICALL *)(GLenum))glXGetProcAddress((const unsigned char *)"glCreateShader");
	_context->glDeleteProgram=(void (_APICALL *)(GLuint))glXGetProcAddress((const unsigned char *)"glDeleteProgram");
	_context->glDeleteShader=(void (_APICALL *)(GLuint))glXGetProcAddress((const unsigned char *)"glDeleteShader");
	_context->glUseProgram=(void (_APICALL *)(GLuint))glXGetProcAddress((const unsigned char *)"glUseProgram");
	_context->glGetProgramInfoLog=(void (_APICALL *) (GLuint, GLsizei, GLsizei *, char *))glXGetProcAddress((const unsigned char *)"glGetProgramInfoLog");
	_context->glAttachShader=(void (_APICALL *) (GLuint, GLuint))glXGetProcAddress((const unsigned char *)"glAttachShader");
	_context->glLinkProgram=(void (_APICALL *) (GLuint))glXGetProcAddress((const unsigned char *)"glLinkProgram");
	_context->glShaderSource=(void (_APICALL *) (GLuint, GLsizei, const char**, const GLint *))glXGetProcAddress((const unsigned char *)"glShaderSource");
	_context->glGetProgramiv=(void (_APICALL *) (GLuint, GLenum, GLint *))glXGetProcAddress((const unsigned char *)"glGetProgramiv");
	_context->glGetShaderiv=(void (_APICALL *) (GLuint, GLenum, GLint *))glXGetProcAddress((const unsigned char *)"glGetShaderiv");
	_context->glGetUniformLocation=(GLuint (_APICALL *) (GLuint, const char *))glXGetProcAddress((const unsigned char *)"glGetUniformLocation");
	_context->glUniform1f=(void (_APICALL *) (GLint, GLfloat))glXGetProcAddress((const unsigned char *)"glUniform1f");
	_context->glUniform2f=(void (_APICALL *) (GLint, GLfloat, GLfloat))glXGetProcAddress((const unsigned char *)"glUniform2f");
	_context->glUniform3f=(void (_APICALL *) (GLint, GLfloat, GLfloat, GLfloat))glXGetProcAddress((const unsigned char *)"glUniform3f");
	_context->glUniform4f=(void (_APICALL *) (GLint, GLfloat, GLfloat, GLfloat, GLfloat))glXGetProcAddress((const unsigned char *)"glUniform4f");
	_context->glUniform1i=(void (_APICALL *) (GLint, GLint))glXGetProcAddress((const unsigned char *)"glUniform1i");
	_context->glUniform2i=(void (_APICALL *) (GLint, GLint, GLint))glXGetProcAddress((const unsigned char *)"glUniform2i");
	_context->glUniform3i=(void (_APICALL *) (GLint, GLint, GLint, GLint))glXGetProcAddress((const unsigned char *)"glUniform3i");
	_context->glUniform4i=(void (_APICALL *) (GLint, GLint, GLint, GLint, GLint))glXGetProcAddress((const unsigned char *)"glUniform4i");
	_context->glUniform1fv=(void (_APICALL *) (GLint, GLsizei, const GLfloat *))glXGetProcAddress((const unsigned char *)"glUniform1fv");
	_context->glUniform2fv=(void (_APICALL *) (GLint, GLsizei, const GLfloat *))glXGetProcAddress((const unsigned char *)"glUniform2fv");
	_context->glUniform3fv=(void (_APICALL *) (GLint, GLsizei, const GLfloat *))glXGetProcAddress((const unsigned char *)"glUniform3fv");
	_context->glUniform4fv=(void (_APICALL *) (GLint, GLsizei, const GLfloat *))glXGetProcAddress((const unsigned char *)"glUniform4fv");
	_context->glUniform1iv=(void (_APICALL *) (GLint, GLsizei, const GLint *))glXGetProcAddress((const unsigned char *)"glUniform1iv");
	_context->glUniform2iv=(void (_APICALL *) (GLint, GLsizei, const GLint *))glXGetProcAddress((const unsigned char *)"glUniform2iv");
	_context->glUniform3iv=(void (_APICALL *) (GLint, GLsizei, const GLint *))glXGetProcAddress((const unsigned char *)"glUniform3iv");
	_context->glUniform4iv=(void (_APICALL *) (GLint, GLsizei, const GLint *))glXGetProcAddress((const unsigned char *)"glUniform4iv");
	_context->glUniformMatrix2fv=(void (_APICALL *) (GLint, GLsizei, GLboolean, const GLfloat *))glXGetProcAddress((const unsigned char *)"glUniformMatrix2fv");
	_context->glUniformMatrix3fv=(void (_APICALL *) (GLint, GLsizei, GLboolean, const GLfloat *))glXGetProcAddress((const unsigned char *)"glUniformMatrix3fv");
	_context->glUniformMatrix4fv=(void (_APICALL *) (GLint, GLsizei, GLboolean, const GLfloat *))glXGetProcAddress((const unsigned char *)"glUniformMatrix4fv");

	_context->_GL_ARB_vertex_buffer_object=(
		_context->glGenBuffers && _context->glBindBuffer && _context->glBufferData && 
		_context->glBufferSubData && _context->glMapBuffer && _context->glUnmapBuffer && 
		_context->glDeleteBuffers && _context->glGetBufferParameteriv);
}

}

#endif
