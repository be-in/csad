/*
 * osxdisplay.cpp
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr
 */

#include <platform/platformapi.h>

#if defined (OS_OSX)

#include "csad/platform/localdisplay.h"
#include <platform.h>
#include <bt.h>
#include <core/graph.h>

OPTIMIZE_ON;

namespace csad {

using namespace bt;

LocalDisplay::LocalDisplay(int dev,int id,char *name)
{
	Graph::graph().p_display->addObject(this,name);
	p_display.flag=VSYNC;
}

LocalDisplay::LocalDisplay(int dev,int id,const char *name)
{
	Graph::graph().p_display->addObject(this,name);
	p_display.flag=VSYNC;
}

LocalDisplay::~LocalDisplay()
{
	Graph::graph().p_display->detachObject(this);
	p_context.destroyObjects<GlContext>();
}

GlContext* LocalDisplay::createContext(char *name)
{
	if (name[0]!=0) {
		GlContext *context=(GlContext*)p_context.getObject(name);
		if (context) return context;
	}
	GlContext *context=new GlContext(this,name);
	if (!Render::createContext(this,context)) {
		delete context;
		return 0;
	}
	return context;
}

GlContext * LocalDisplay::getContext(const char *name)
{
	return (GlContext*)p_context.getObject(name);
}

void *LocalDisplay::getHandle()
{
	return (void *)p_display.surface;
}

void *LocalDisplay::getBase()
{
	return (void *)p_display.display;
}

void LocalDisplay::SetVSync(bool val)
{
	if (val!=(p_display.flag&VSYNC)) {
		p_display.flag^=VSYNC;
	}
}

void LocalDisplay::SetHM(bool val)
{
	if (val!=(p_display.flag&HARDWAREMOUSE)) {
		p_display.flag^=HARDWAREMOUSE;
		//SetFocus(p_display.surface);
		//ShowCursor(val);
	}
}

void LocalDisplay::SetTitle(char *title)
{
	//SetWindowTitle();
}

bool LocalDisplay::isVSync()
{
	return ((p_display.flag&VSYNC)!=0);
}

/*void Display::offGlContexts()
{
	Render::MakeCurrent(this,0);
	GlContext::p_current=0;
}*/

bool LocalDisplay::isGlobalPoint(vector2i*pos)
{
	if (p_display.posx>pos->x) return false;
	if (p_display.posx+p_display.xres<=pos->x) return false;
	if (p_display.posy>pos->y) return false;
	if (p_display.posy+p_display.yres<=pos->y) return false;
	return true;
}

int LocalDisplay::width()
{
	return p_display.xres;
}

int LocalDisplay::height()
{
	return p_display.yres;
}

int LocalDisplay::left()
{
	return p_display.posx;
}

int LocalDisplay::top() 
{
	return p_display.posy;
}

void LocalDisplay::toLocal(vector2f*global,vector2f*local)
{
	local->x=global->x-p_display.posx;//-p_display->xres*0.5f;
	local->y=global->y-p_display.posy;//p_display->yres*0.5f-global->y+p_display->posy;
}

void LocalDisplay::toLocal(vector2i*global,vector2i*local)
{
	local->x=global->x-p_display.posx;//-p_display->xres*0.5f;
	local->y=global->y-p_display.posy;//p_display->yres*0.5f-global->y+p_display->posy;
}

void LocalDisplay::swapBuffers()
{
	/*ObjectsList::iterator it = p_context.getObjects().begin();
	ObjectsList::iterator end = p_context.getObjects().end();

	while (it!=end) {
		GlContext* context=(GlContext*)it.value();
		if (context->makeCurrent())	Render::Finish();
		it++;
	}*/
	//Render::MakeCurrent(this,0);
	//GlContext::p_current=0;

	Render::Buffers(this);
}

void *LocalDisplay::set(unsigned int id,void *param)
{
	if (id==BaseObject::TYPE) return Display::t();
	if (id==BaseObject::WRITE) {
		ParametersList *list=(ParametersList *)param;
		if (list->contains("vsync")) SetVSync((*list)["vsync"].getBool());
		if (list->contains("hardwarecursor")) SetHM((*list)["hardwarecursor"].getBool());
		if (list->contains("title")) SetTitle((*list)["title"].getString());
	}
	if (id==BaseObject::MANAGER) {
		return &p_context;
	}
	return 0;
}

TYPEINFO(Display)

}

OPTIMIZE_OFF;

#endif
