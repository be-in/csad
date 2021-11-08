/*
 * qnxdisplay.cpp
 *
 *  Created on: 14.08.2013
 *      Author: Пантелеймонов Александр
 */

#include <platform/platformapi.h>

#if defined (OS_QNX)

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

GlContext * LocalDisplay::getContext(const char *name)
{
	return (GlContext*)p_context.getObject(name);
}

void LocalDisplay::SetVSync(bool val)
{
	if (val!=(p_display.flag&VSYNC)) {
		p_display.flag^=VSYNC;
	}
}

bool LocalDisplay::isVSync()
{
	return ((p_display.flag&VSYNC)!=0);
}

void LocalDisplay::SetHM(bool val)
{

}

void LocalDisplay::SetTitle(char *title)
{

}

void *LocalDisplay::getHandle()
{
	return (void *)p_display.surface;
}

bool LocalDisplay::isGlobalPoint(vector2i*pos)
{
#if _NTO_VERSION < 660
	if (p_display.posx>pos->x) return false;
	if (p_display.posx+p_display.disp_info.xres<=pos->x) return false;
	if (p_display.posy>pos->y) return false;
	if (p_display.posy+p_display.disp_info.yres<=pos->y) return false;
#else
	if (p_display.posx>pos->x) return false;
	if (p_display.posx+p_display.width<=pos->x) return false;
	if (p_display.posy>pos->y) return false;
	if (p_display.posy+p_display.height<=pos->y) return false;
#endif
	return true;
}

int LocalDisplay::width()
{
#if _NTO_VERSION < 660
	return p_display.disp_info.xres;
#else
	return p_display.width;
#endif
}

int LocalDisplay::height()
{
#if _NTO_VERSION < 660
	return p_display.disp_info.yres;
#else
	return p_display.height;
#endif
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
	local->x=global->x-p_display.posx;
	local->y=global->y-p_display.posy;
}

void LocalDisplay::toLocal(vector2i*global,vector2i*local)
{
	local->x=global->x-p_display.posx;
	local->y=global->y-p_display.posy;
}

void LocalDisplay::swapBuffers()
{
	ObjectsList::iterator it = p_context.getObjects().begin();
	ObjectsList::iterator end = p_context.getObjects().end();
	while (it!=end) {
		GlContext *context=(GlContext*)it.value();
		context->makeCurrent();
		Render::Buffers(this);
		it++;
	}
	//Render::MakeCurrent(display,0);
	//Render::Buffers(this);
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
	if (id==BaseObject::READ) {
		//ParametersList *list=(ParametersList *)param;
		//list->
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
