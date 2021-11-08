/*
 * localdisplay.h
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef LOCALDISPLAY_H_
#define LOCALDISPLAY_H_

#include <platform.h>
#include <core/objectmanager.h>
#include "glextension.h"

OPTIMIZE_ON;

namespace csad {

class LocalDisplay: public Display {  
public:
	MEMDEFAULT(LocalDisplay)

	LocalDisplay(char *name);
	LocalDisplay(const char *name="");
	~LocalDisplay();

	GlContext* createContext(char *name);
	_FORCEINLINE GlContext* createContext(const char *name="") {return createContext((char*)name);}
	GlContext * getContext(char *name);
	_FORCEINLINE GlContext* getContext(const char *name="") {return getContext((char*)name);}

	void addContext(GlContext *,char *);
	_FORCEINLINE void addContext(GlContext * context,const char *name="") {addContext(context,(char*)name);}

	void *getHandle();
	void *getBase();

	unsigned _int32 mode();
	void setMode(unsigned _int32 mode);
	unsigned _int32 flag();
	void setFlag(unsigned _int32 mask,unsigned _int32 val);

	void SetTitle(char *title);

	bool isGlobalPoint(vector2i*pos);

	_int32 width();
	_int32 height();
	_int32 top();
	_int32 left();

	void setSize(bt::vector4i &size);

	void toLocal(vector2f*global,vector2f*local);
	void toLocal(vector2i*global,vector2i*local);

	_FORCEINLINE sFunctionsDisplayRender &functions() { return ffunctions; }
	_FORCEINLINE Display_P *localDisplay() { return &p_display; }

	_FORCEINLINE void swapBuffers() { ffunctions.Buffers(this); }

	void check();
	void softDraw();

	void *set(unsigned _int32 id,void *param);

private:
	/*enum Flag {
		VSYNC = 0x00000001,
		HARDWAREMOUSE = 0x00000002,
		WINDOWED = 0x00000004,
	};*/

	Display_P p_display;
	ObjectManager p_context;
	sFunctionsDisplayRender ffunctions;
	unsigned int fdev,fid;

	//void createSoft();
	static bool _choosePixelFormat(Display * display,bool ,bool gl,int r,int g,int b,int a,int depth,int stencil,int sample);
	static bool _createDisplay(Display * display,_int32 ,_int32 dispid);
	static bool _destroyDisplay(Display * display);

friend class Render;
friend class GlContext;
};

}

OPTIMIZE_OFF;

#endif
