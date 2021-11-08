/*
 * display.h
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <platform/platformapi.h>
#include <core/objectmanager.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

class GlContext;

/**
 * @class Display
 *
 * @ingroup scene
 * @brief Display - the class of the output device.
 *
 * In different ways this can be separately selected output device or the output window.
 * When using operating systems support window organization applications, you can specify the mode display full screen or windowed.
 * To specify the mode of displaying the image indicated ...
 *
 @verbatim
   <Scene name="the name of the scene">
   <Display name="" dev="the logical number of the controller" id="logical device number" mode="fullscreen/windowed" render="soft/gl/gles">
       ...
   </Display>
 @endverbatim
 *
 * @see scene
 */

class Display: public BaseObject {  
public:
	MEMNULL

	enum Mode {
		RM_SOFT = 0x0,
		RM_GL = 0x1,
		RM_GLES = 0x2,
	};

	enum Flag {
		FM_VSYNC = 0x00000001,
		FM_HARDWAREMOUSE = 0x00000002,
		FM_WINDOWED = 0x00000004,
		FM_TRANSPARENT = 0x00000008
	};

	virtual GlContext* createContext(char *)=0;
	/// create new context.
	_FORCEINLINE GlContext* createContext(const char *name="") { return createContext((char*)name); }
	/// Returns the context by name
	virtual GlContext * getContext(char *)=0;
	_FORCEINLINE GlContext* getContext(const char *name="") { return getContext((char*)name); }

	virtual void addContext(GlContext *,char *)=0;
	_FORCEINLINE void addContext(GlContext * context,const char *name="") { addContext(context,(char*)name); }

	/// return handle of device
	virtual void *getHandle()=0;
	virtual void *getBase()=0;

	virtual unsigned _int32 mode()=0;
	virtual void setMode(unsigned _int32 mode)=0;
	virtual unsigned _int32 flag()=0;
	virtual void setFlag(unsigned _int32 mask,unsigned _int32 val)=0;
	_FORCEINLINE void setFlag(unsigned _int32 val) { setFlag(val,val); }

	/// Setting of a mode vertical sync
	_FORCEINLINE void SetVSync(bool val) { setFlag(FM_VSYNC,FM_VSYNC*val); }
	/// Checking mode vertical sync
	_FORCEINLINE bool isVSync() { return (flag() & FM_VSYNC)!=0; }
	/// Setting of a mode window/fullscreen
	_FORCEINLINE void SetWindowed(bool val) { setFlag(FM_WINDOWED,FM_WINDOWED*val); }
	_FORCEINLINE bool isWindowed() { return (flag() & FM_WINDOWED)!=0; }
	_FORCEINLINE void SetTransparent(bool val) { setFlag(FM_TRANSPARENT,FM_TRANSPARENT*val); }
	_FORCEINLINE bool isTransparent() { return (flag() & FM_TRANSPARENT)!=0; }
	_FORCEINLINE void SetHM(bool val) { setFlag(FM_HARDWAREMOUSE,FM_HARDWAREMOUSE*val); }

	/// Crossing checking the global coordinates of the screen with display
	virtual bool isGlobalPoint(vector2i*pos)=0;

	/// the width of the screen
	virtual _int32 width()=0;
	/// the height of the screen
	virtual _int32 height()=0;
	/// The top position of the screen in desktop coordinate system
	virtual _int32 top()=0;
	/// The left position of the screen in desktop coordinate system
	virtual _int32 left()=0;

	virtual void toLocal(vector2f*,vector2f*)=0;
	virtual void toLocal(vector2i*,vector2i*)=0;

	virtual void swapBuffers()=0;

	CSAD_API TYPEINFO_H

	CSAD_API static unsigned _int32 mode(char*);
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* DISPLAY_H_ */
