/*
 * glcontext.h
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef GLCONTEXT_H_
#define GLCONTEXT_H_

#include <platform/platformapi.h>
#include <bt/types.h>
#include <core/baseobject.h>
#include <core/objectmanager.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

/**
 * @class GlContext
 *
 * @ingroup core
 * @brief GlContext - the context interface OpenGL/OpenGLES.
 *
 *
 @verbatim
   <Display name="display name">
      <GlContext name="context name" />
   </Display>
 @endverbatim
 *
 * @see core
 */

class Display;
class ViewPort;
class Texture2D;
class BaseMesh;
class Material;
class LightingModel;

class GlContext: public BaseObject {
public:
	MEMDEFAULT(GlContext)

	enum Flag {
		EXT_VB = 0x00001,
	};

	PLATFORM_API GlContext(Display *parent,char *name);
	PLATFORM_API GlContext(Display *parent,const char *name="");
	PLATFORM_API ~GlContext();

	/// Creates a new texture devices
	PLATFORM_API unsigned int createTexture2D();
	PLATFORM_API void bindTexture2D(unsigned _int32);
	PLATFORM_API unsigned int createShaderProg();
	PLATFORM_API void bindShaderProg(unsigned _int32);

	PLATFORM_API BaseMesh * createVBOMesh(BaseMesh *mesh);
	PLATFORM_API BaseMesh * getVBOMesh(BaseMesh *mesh);

	PLATFORM_API void freeVBOMesh(BaseMesh *mesh);

	PLATFORM_API void setExtentions(bool val);

	/// Returns the parent device
	_FORCEINLINE Display *getDisplay() { return p_parent; }

	/// Returns the width of the screen
	PLATFORM_API int width();
	/// Returns the height of the screen
	PLATFORM_API int height();

	PLATFORM_API void setColor(vector4f &color);

	_FORCEINLINE void *handle() { return p_context; }

	/// Activates the context
	PLATFORM_API bool makeCurrent();
	/// Returns the active context
	PLATFORM_API static GlContext *getCurrent();
	_FORCEINLINE static GlContext *&current() {return p_current;}

	PLATFORM_API void *set(unsigned _int32 ,void *);

	PLATFORM_API static GlContext *finder(char *path);

	PLATFORM_API TYPEINFO_H

	_FORCEINLINE bt::sFunctionsGLContext& functions() {return ffunctions;}

private:
	Display *p_parent;
	void * p_context;
	bt::MapVoid<void> p_vboMesh;
	Material *p_lastmaterial;
	LightingModel *p_lastlightings;
	unsigned int p_lasttexture2d;
	unsigned int p_lastshaderprog;

	bt::sFunctionsGLContext ffunctions;

	static GlContext *p_current;

friend class Render;
friend class Display;
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* GLCONTEXT_H_ */
