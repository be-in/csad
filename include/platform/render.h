/*
 * render.h
 *
 *  Created on: 13.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef RENDER_H_
#define RENDER_H_

#include <platform/platformapi.h>
#include <bt.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

class Display;
class GlContext;
class Material;
class LightingModel;
class Camera;
class MeshFilter;
class Mesh;
class VBOMesh;
class Texture2D;

/*typedef void (_FASTCALL *tfUpdateModelElement)(void *,void *,int _id,int);
typedef void (_FASTCALL *tfUpdateModelIndex)(void *,void *,int _id,int);*/

/**
 * @class Render
 *
 * @ingroup scene
 * @brief Render - the basic methods of drawing.
 *
 * @see scene
 */

class Render {
public:
	MEMDEFAULT(Render)

	PLATFORM_API Render();

	PLATFORM_API static void _APICALL initialize(GlContext * context);

	/// установка массивов gen::gen::tglmodel.
/*	static tfBindModel BindModel;
	/// отрисовка установленный массивов.
	static tfDrawBindModel DrawBindModel;
	static tfUnBindModel UnBindModel;
	static tfUpdateModelElement UpdateModelElement;
	static tfUpdateModelIndex UpdateModelIndex;*/

	static void _FASTCALL Info();
	static void _APICALL setViewPort(int x,int y,int width,int height);
	static void _APICALL setClearColor(vector4f *color);
	static unsigned int _APICALL GenTextures(int count,void* data);
	static void _APICALL TexImage2D(int level,int format,int width,int height,void * data);
	static void _APICALL TexSubImage2D(int level,int format,int x,int y,int width,int height,void * data);
	static int _FASTCALL GetTexure2DWidth();
	static int _FASTCALL GetTexure2DHeight();
	static int _FASTCALL formatFromBPP(int bpp,int format);
	static bool _APICALL createContext(Display*,GlContext *);
	static bool _APICALL destroyContext(Display *, GlContext *);
	static void * _APICALL getCurrentContext();
	static bool _APICALL MakeCurrent(Display*,GlContext*);
	static void _APICALL setMipMap(int _min,int _max);
	static void _APICALL setFilterMode(int mag,int min);
	static void _APICALL setMatrix(Camera*);
	static void _APICALL setMatrixRect(Camera*,vector4i&);
	static void _APICALL BindMaterial(Material*);
	static void _APICALL BindLightingModel(LightingModel*);
	//static void _STDCALL DrawMesh(MeshFilter *mesh);
	static void _APICALL FreeVBO(VBOMesh *mesh);
	static void _APICALL UnBindModel();
	static void _FASTCALL BindTexture2D(unsigned int text);
	static void _FASTCALL BindTexture2D(Texture2D* text);
	static void _FASTCALL Uniform1f(char *_name,float _x);
	static void _FASTCALL Uniform2f(char *_name,float _x,float _y);
	static void _FASTCALL Uniform3f(char *_name,float _x,float _y,float _z);
	static void _FASTCALL Uniform4f(char *_name,float _x,float _y,float _z,float _w);
	static void _APICALL Finish();
	static void _APICALL Buffers(Display *display);
	static void _APICALL TransparentBuffers(Display *display);
	static void _APICALL UnBindAll();

	PLATFORM_API static void* hInst;

	static void _APICALL _DrawMesh(MeshFilter *mesh);
	static void _FASTCALL _UnBindModel();

	TYPEINFO_H

private:
	enum States {
		VALIDED = 0x011F1C01,
		FREE = 0
	};

	static unsigned int p_isVal;
	static unsigned int vertexvbo;
	static unsigned int indexvbo;
	static unsigned char *p_lastelements;
	static unsigned int p_deffProg;

//	static GLExtentionFunction *m_extfunc;

	static void _APICALL _DrawMeshVBO(MeshFilter *mesh);

	static bool _FASTCALL _BindModel(Mesh *model,VBOMesh *_vbo);
	static bool _FASTCALL _BindModelVBO(Mesh *model,VBOMesh *_vbo);
	static bool _FASTCALL _DrawBindModel(Mesh *model,VBOMesh *vbo);
	static bool _FASTCALL _DrawBindModelVBO(Mesh *model,VBOMesh *_vbo);
	static void _FASTCALL _UpdateModelElement(Mesh *model,VBOMesh *vbo,int _id,int _count);
	static void _FASTCALL _UpdateModelElementVBO(Mesh *model,VBOMesh *vbo,int _id,int _count);
	static void _FASTCALL _UpdateModelIndex(Mesh *model,VBOMesh *vbo,int ,int );
	static void _FASTCALL _UpdateModelIndexVBO(Mesh *model,VBOMesh *vbo,int _id,int _count);
	static void _FASTCALL _UnBindModelVBO();

	static void _FASTCALL _InterleavedArrays(unsigned int _format,unsigned int _item,unsigned char *_pointer);

	//static bool _choosePixelFormat(Display *,bool format,bool gl,int r,int g,int b,int a,int depth,int stencil,int sample);
	//static bool _createDisplay(Display * display, int devid, int dispid);
	//static bool _destroyDisplay(Display * display);
	static bool _createContext(Display *,GlContext *);

friend class Display;
friend class Graph;
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* RENDER_H_ */
