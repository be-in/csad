/*
 * winglextension.h
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef WINGLEXTENTION_H_
#define WINGLEXTENTION_H_

#include <bt/os.h>
#include <bt/memmanager.h>
#include <bt/functions.h>

#if defined (OS_WIN)

#include <GL/gl.h>
#include <bt/typesproc.h>

OPTIMIZE_ON;

namespace csad {

class Module;

// *********************************** OpenGL *****************************************

typedef unsigned int GlIndex;

// extentions

// *********************************** EXT_stencil_wrap *******************************
#define GL_STENCIL_TEST_TWO_SIDE_EXT                0x8910

#ifndef GL_INCR_WRAP_EXT
#define GL_INCR_WRAP_EXT                            0x8507
#endif

#ifndef GL_DECR_WRAP_EXT
#define GL_DECR_WRAP_EXT                            0x8508
#endif

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
	MEMDEFAULT(Display_P)

	HWND surface;
	HDC display;
	unsigned int config;
	int posx;
	int posy;
	int xres;
	int yres;
	int colorres;
};

struct Context_P {
	MEMDEFAULT(Context_P)

	_FORCEINLINE Context_P() {};

	void* context;
	bool initialize;
	bool _GL_EXT_stencil_two_side;
	bool _GL_EXT_stencil_wrap;
	bool _GL_ARB_vertex_buffer_object;
	bool _GL_ARB_shader;

	bt::tfSTDCALL_p_FUNC_p GetProcAddress; //??
	bt::tfSTDCALL_p_FUNC_p CreateContext; //??
	bt::tfSTDCALL_bool_FUNC_p DeleteContext; //??
	bt::tfSTDCALL_p_FUNC GetCurrentContext; //??
	bt::tfSTDCALL_bool_FUNC_p_p MakeCurrent; //??

	bt::tfFASTCALL_bool_FUNC_p_p BindModel;
	bt::tfFASTCALL_bool_FUNC_p_p DrawBindModel;
	bt::tfFASTCALL_PROC UnBindModel;
	bt::tfFASTCALL_PROC_p_p_int_int UpdateModelElement;
	bt::tfFASTCALL_PROC_p_p_int_int UpdateModelIndex;
};

// extention methods

void glBasefunctions(Context_P *_context);
void glReadExtention(Context_P *_context);
void glInitGLFunctions(void *content);

}

OPTIMIZE_OFF;

#endif

#endif /* WINGLEXTENTION_H_ */
