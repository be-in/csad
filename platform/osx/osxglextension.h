/*
 * osxglextension.h
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr
 */

#ifndef OSXGLEXTENTION_H_
#define OSXGLEXTENTION_H_

#include <bt/os.h>

#if defined (OS_OSX)

#include <OpenGL/gl.h>
#include <bt/typesproc.h>

namespace csad {

// *********************************** OpenGL *****************************************
#ifndef GL_BGRA
#define GL_BGRA                                    0x080E1
#endif
#ifndef GL_BGR
#define GL_BGR                                     0x080E0
#endif
//#define GL_TEXTURE_MIN_LOD                         0x0813A
//#define GL_TEXTURE_MAX_LOD                         0x0813B
#define GL_DOUBLE                                  0x140A

#ifndef GL_TEXTURE_MAX_LOD
#define GL_TEXTURE_MAX_LOD 0x813B
#endif
#ifndef GL_TEXTURE_MIN_LOD
#define GL_TEXTURE_MIN_LOD 0x813A
#endif

typedef unsigned int GlIndex;

// *********************************** GL_TEXTURE_3D **********************************
#define GL_TEXTURE_3D                               0x806F
#define GL_TEXTURE_BINDING_3D                       0x806A

// extentions

// *********************************** EXT_stencil_wrap *******************************
#define GL_STENCIL_TEST_TWO_SIDE_EXT                0x8910

#ifndef GL_INCR_WRAP_EXT
#define GL_INCR_WRAP_EXT                            0x8507
#endif

#ifndef GL_DECR_WRAP_EXT
#define GL_DECR_WRAP_EXT                            0x8508
#endif

#define GL_PROGRAM_ERROR_POSITION_ARB               0x864B
#define GL_PROGRAM_BINDING_ARB                      0x8677
#define GL_SHADER_TYPE                              0x8B4F
#define GL_FRAGMENT_SHADER                          0x8B30
#define GL_VERTEX_SHADER                            0x8B31
#define GL_PROGRAM_ERROR_STRING_ARB                 0x8874
#define GL_CURRENT_PROGRAM                          0x8B8D
#define GL_INFO_LOG_LENGTH                          0x8B84

#define GL_BUFFER_SIZE_ARB							0x8764
#define GL_BUFFER_USAGE_ARB							0x8765
#define GL_ARRAY_BUFFER_ARB                         0x8892
#define GL_ELEMENT_ARRAY_BUFFER_ARB                 0x8893
#define GL_ARRAY_BUFFER_BINDING_ARB                 0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING_ARB         0x8895
#define GL_VERTEX_ARRAY_BUFFER_BINDING_ARB          0x8896
#define GL_NORMAL_ARRAY_BUFFER_BINDING_ARB          0x8897
#define GL_COLOR_ARRAY_BUFFER_BINDING_ARB           0x8898
#define GL_INDEX_ARRAY_BUFFER_BINDING_ARB           0x8899
#define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING_ARB   0x889A
#define GL_EDGE_FLAG_ARRAY_BUFFER_BINDING_ARB       0x889B
#define GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING_ARB 0x889C
#define GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB  0x889D
#define GL_WEIGHT_ARRAY_BUFFER_BINDING_ARB          0x889E
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING_ARB   0x889F
#define GL_READ_ONLY_ARB                            0x88B8
#define GL_WRITE_ONLY_ARB                           0x88B9
#define GL_READ_WRITE_ARB                           0x88BA
#define GL_BUFFER_ACCESS_ARB                        0x88BB
#define GL_BUFFER_MAPPED_ARB                        0x88BC
#define GL_BUFFER_MAP_POINTER_ARB                   0x88BD
#define GL_STREAM_DRAW_ARB                          0x88E0
#define GL_STREAM_READ_ARB                          0x88E1
#define GL_STREAM_COPY_ARB                          0x88E2
#define GL_STATIC_DRAW_ARB                          0x88E4
#define GL_STATIC_READ_ARB                          0x88E5
#define GL_STATIC_COPY_ARB                          0x88E6
#define GL_DYNAMIC_DRAW_ARB                         0x88E8
#define GL_DYNAMIC_READ_ARB                         0x88E9
#define GL_DYNAMIC_COPY_ARB                         0x88EA

// subclass

struct Display_P {

	Window surface;
	::Display *display;
	XVisualInfo *vi;
	int posx;
	int posy;
	int xres;
	int yres;
	int colorres;
	int scrnum;
};

struct Context_P {

	GLXContext context;
	bool initialize;
	bool _GL_EXT_stencil_two_side;
	bool _GL_EXT_stencil_wrap;
	bool _GL_ARB_vertex_buffer_object;
	bool _GL_ARB_shader;

	void (_APICALL *glActiveStencilFaceEXT)(GLuint _face);
	GLboolean (_APICALL *glAreTexturesResidentEXT)(GLsizei _n, GLuint *_textures, GLboolean *_residences);
	void (_APICALL *glArrayElementArrayEXT)(GLenum _mode, GLsizei _count, void *pi);
	void (_APICALL *glBeginSceneEXT)();
	void (_APICALL *glBindTextureEXT)(GLenum target, GLuint texture);
	void (_APICALL *glColorTableEXT)(GLenum target, GLenum internalFormat, GLsizei width, GLenum format, GLenum atype, void * data);
//  glColorSubTableExt: procedure(target: GLenum; start, count: GLsizei; format, atype: GLenum; data: Pointer); stdcall;
//  glCopyTexImage1DEXT: procedure(target: GLenum; level: TGLint; internalFormat: GLenum; x, y: TGLint; width: GLsizei; border: TGLint); stdcall;
//  glCopyTexSubImage1DEXT: procedure(target: GLenum; level, xoffset, x, y: TGLint; width: GLsizei); stdcall;
//  glCopyTexImage2DEXT: procedure(target: GLenum; level: TGLint; internalFormat: GLenum; x, y: TGLint; width,  height: GLsizei; border: TGLint); stdcall;
//  glCopyTexSubImage2DEXT: procedure(target: GLenum; level, xoffset, yoffset, x, y: TGLint; width,  height: GLsizei); stdcall;
//  glCopyTexSubImage3DEXT: procedure(target: GLenum; level, xoffset, yoffset, zoffset, x, y: TGLint; width,height: GLsizei); stdcall;
	void (_APICALL *glDeleteTexturesEXT)(GLsizei n, GLuint *textures);
	void (_APICALL *glEndSceneEXT)();
	void (_APICALL *glGenTexturesEXT)(GLsizei n, GLuint *textures);
//  glGenTexturesEXT: procedure(n: GLsizei; textures: PGLuint); stdcall;
//  glGetColorTableEXT: procedure(target, format, atype: GLenum; data: Pointer); stdcall;
//  glGetColorTablePameterfvEXT: procedure(target, pname: GLenum; params: Pointer); stdcall;
//  glGetColorTablePameterivEXT: procedure(target, pname: GLenum; params: Pointer); stdcall;
//  glIndexFuncEXT: procedure(func: GLenum; ref: GLfloat); stdcall;
//  glIndexMaterialEXT: procedure(face: GLenum; mode: GLenum); stdcall;
	GLboolean (_APICALL *glIsTextureEXT)(GLuint texture);
	void (_APICALL *glLockArraysEXT)(GLint first,GLsizei count);
//  glPolygonOffsetEXT: procedure(factor, bias: GLfloat); stdcall;
//  glPrioritizeTexturesEXT: procedure(n: GLsizei; textures: PGLuint; priorities: PGLclampf); stdcall;
//  glTexSubImage1DEXT: procedure(target: GLenum; level, xoffset: TGLint; width: GLsizei; format, Atype: GLenum; pixels: Pointer); stdcall;
//  glTexSubImage2DEXT: procedure(target: GLenum; level, xoffset, yoffset: TGLint; width, height: GLsizei; format,Atype: GLenum; pixels: Pointer); stdcall;
//  glTexSubImage3DEXT: procedure(target: GLenum; level, xoffset, yoffset, zoffset: GLint; width, height, depth: GLsizei; format, Atype: GLenum; pixels: Pointer); stdcall;
	void (_APICALL *glUnlockArraysEXT)();

	void (_APICALL *glArrayElementEXT)(GLint);
	void (_APICALL *glColorPointerEXT)(GLint, GLenum, GLsizei, GLsizei, const GLvoid *);
	void (_APICALL *glDrawArraysEXT)(GLenum, GLint, GLsizei);
	void (_APICALL *glEdgeFlagPointerEXT)(GLsizei, GLsizei, const GLboolean *);
	void (_APICALL *glGetPointervEXT)(GLenum, GLvoid* *);
	void (_APICALL *glIndexPointerEXT)(GLenum, GLsizei, GLsizei, const GLvoid *);
	void (_APICALL *glNormalPointerEXT)(GLenum, GLsizei, GLsizei, const GLvoid *);
	void (_APICALL *glTexCoordPointerEXT)(GLint, GLenum, GLsizei, GLsizei, const GLvoid *);
	void (_APICALL *glVertexPointerEXT)(GLint, GLenum, GLsizei, GLsizei, const GLvoid *);
	void (_APICALL *glTangentPointerEXT)(GLenum,GLsizei, const GLvoid *);
	void (_APICALL *glBinormalPointerEXT)(GLenum,GLsizei, const GLvoid *);
	GLboolean (_APICALL *glSwapIntervalEXT)(GLint);

	void (_APICALL *glGenBuffers)(GLsizei, GLuint *);
	void (_APICALL *glDeleteBuffers)(GLsizei, const GLuint *);
	void (_APICALL *glBindBuffer)(GLenum, GLuint);
	GLboolean (_APICALL *glIsBuffer)(GLuint);
	void (_APICALL *glBufferData)(GLenum, GLsizei, const GLvoid *, GLenum);
	void (_APICALL *glBufferSubData)(GLenum, GLint, GLsizei, const GLvoid *);
	//void (_STDCALL *glGetBufferSubData)(GLenum, GLintptrARB, GLsizeiptrARB, GLvoid *);
	GLvoid* (_APICALL *glMapBuffer)(GLenum, GLenum);
	GLboolean (_APICALL *glUnmapBuffer)(GLenum);
	void (_APICALL *glGetBufferParameteriv)(GLenum, GLenum, GLint *);
	void (_APICALL *glGetBufferPointerv)(GLenum, GLenum, GLvoid* *);

	void (_APICALL *glCompileShader)(GLuint);
	GLuint (_APICALL *glCreateProgram)(void);
	GLuint (_APICALL *glCreateShader)(GLenum);
	void (_APICALL *glDeleteProgram)(GLuint);
	void (_APICALL *glDeleteShader)(GLuint);
	void (_APICALL *glUseProgram)(GLuint);
	void (_APICALL *glGetProgramInfoLog) (GLuint, GLsizei, GLsizei *, char *);
	void (_APICALL *glAttachShader) (GLuint, GLuint);
	void (_APICALL *glLinkProgram) (GLuint);
	void (_APICALL *glShaderSource) (GLuint, GLsizei, const char**, const GLint *);
	void (_APICALL *glGetProgramiv) (GLuint, GLenum, GLint *);
	void (_APICALL *glGetShaderiv) (GLuint, GLenum, GLint *);
	GLuint (_APICALL *glGetUniformLocation) (GLuint, const char *);
	void (_APICALL *glUniform1f) (GLint, GLfloat);
	void (_APICALL *glUniform2f) (GLint, GLfloat, GLfloat);
	void (_APICALL *glUniform3f) (GLint, GLfloat, GLfloat, GLfloat);
	void (_APICALL *glUniform4f) (GLint, GLfloat, GLfloat, GLfloat, GLfloat);
	void (_APICALL *glUniform1i) (GLint, GLint);
	void (_APICALL *glUniform2i) (GLint, GLint, GLint);
	void (_APICALL *glUniform3i) (GLint, GLint, GLint, GLint);
	void (_APICALL *glUniform4i) (GLint, GLint, GLint, GLint, GLint);
	void (_APICALL *glUniform1fv) (GLint, GLsizei, const GLfloat *);
	void (_APICALL *glUniform2fv) (GLint, GLsizei, const GLfloat *);
	void (_APICALL *glUniform3fv) (GLint, GLsizei, const GLfloat *);
	void (_APICALL *glUniform4fv) (GLint, GLsizei, const GLfloat *);
	void (_APICALL *glUniform1iv) (GLint, GLsizei, const GLint *);
	void (_APICALL *glUniform2iv) (GLint, GLsizei, const GLint *);
	void (_APICALL *glUniform3iv) (GLint, GLsizei, const GLint *);
	void (_APICALL *glUniform4iv) (GLint, GLsizei, const GLint *);
	void (_APICALL *glUniformMatrix2fv) (GLint, GLsizei, GLboolean, const GLfloat *);
	void (_APICALL *glUniformMatrix3fv) (GLint, GLsizei, GLboolean, const GLfloat *);
	void (_APICALL *glUniformMatrix4fv) (GLint, GLsizei, GLboolean, const GLfloat *);

	bt::tfFASTCALL_bool_FUNC_p_p BindModel;
	bt::tfFASTCALL_bool_FUNC_p_p DrawBindModel;
	bt::tfFASTCALL_PROC UnBindModel;
	bt::tfFASTCALL_PROC_p_p_int_int UpdateModelElement;
	bt::tfFASTCALL_PROC_p_p_int_int UpdateModelIndex;
};

// extention methods

void glReadExtention(Context_P *_context);

}

#endif

#endif /* OSXGLEXTENTION_H_ */
