/*
 * localdisplay.h
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include "csad/platform/localdisplay.h"
#include <core/graph.h>
#include "csad/platform/base/basesoftrender.h"

OPTIMIZE_ON;

namespace csad {

LocalDisplay::LocalDisplay(char *name)
{
	Graph::graph().p_display->addObject(this,name);
	extFunctions.CleanMem(&p_display,sizeof(p_display));
	//ffunctions.flag=FM_VSYNC;
	fdev=0;
	fid=0;
	ffunctions.soft=0;
	initDisplayRender(&ffunctions,FM_VSYNC<<8);
}

LocalDisplay::LocalDisplay(const char *name)
{
	Graph::graph().p_display->addObject(this,name);
	extFunctions.CleanMem(&p_display,sizeof(p_display));
	//p_display.flag=FM_VSYNC;
	fdev=0;
	fid=0;
	ffunctions.soft=0;
	initDisplayRender(&ffunctions,FM_VSYNC<<8);
}

LocalDisplay::~LocalDisplay()
{
	Graph::graph().p_display->detachObject(this);
	p_context.destroyObjects<GlContext>();
	_destroyDisplay(this);
}

GlContext* LocalDisplay::createContext(char *name)
{
	check();
	if (name[0]!=0) {
		GlContext *context=(GlContext*)p_context.getObject(name);
		if (context) return context;
	}
	GlContext *context=new GlContext(this,name);
	if (!ffunctions.CreateContext(this,context)) {
		delete context;
		return 0;
	}
	return context;
}

unsigned _int32 LocalDisplay::mode()
{
	return ffunctions.mode;
}

void LocalDisplay::setMode(unsigned _int32 mode)
{
	if (((ffunctions.mode ^ mode) & 0xFF)==0) return;
	ffunctions.mode &=0xFFFFFF00;
	initDisplayRender(&ffunctions,mode | ffunctions.mode);
}

void LocalDisplay::check()
{
	if (!p_display.display) {
		_createDisplay(this,fdev,fid);
	}
}

void *LocalDisplay::set(unsigned _int32 id,void *param)
{
	if (id==BaseObject::TYPE) return Display::t();
	if (id==BaseObject::WRITE) {
		bt::Variant *p;
		ParametersList *list=(ParametersList *)param;
		if ((p=list->find("vsync"))!=0) SetVSync(p->getBool());
		if ((p=list->find("hardwarecursor"))!=0) SetHM(p->getBool());
		if ((p=list->find("title"))!=0) SetTitle(p->getString());
		if ((p=list->find("device"))!=0) fdev=p->getInt();
		if ((p=list->find("display"))!=0) fid=p->getInt();
		if ((p=list->find("size"))!=0) setSize(p->getVector4i());
		if ((p=list->find("render"))!=0) setMode(Display::mode(p->getString()));
		if ((p=list->find("fullscreen"))!=0) SetWindowed(!p->getBool());
		if ((p=list->find("transparent"))!=0) SetTransparent(p->getBool());
	}
	if (id==BaseObject::MANAGER) {
		return &p_context;
	}
	return 0;
}

/*void LocalDisplay::createSoft()
{
	Display_P * mdisplay=&p_display;
	if (ffunctions.soft==0) {
		ffunctions.soft=new softDisplay();
	}
	softDisplay *sd=(softDisplay*)ffunctions.soft;
	sd->bufferStride=mdisplay->xres<<2;
	int size=mdisplay->xres*sd->bufferStride;
	sd->buffer=(void*)new char[size*2+16];
	sd->colorOffset=(void*)(((_voidint)sd->buffer)&(_voidintmax-15));
	sd->depthOffset=((char*)sd->colorOffset)+size;
	sd->maxx=mdisplay->xres;
	sd->maxy=mdisplay->yres;
}*/

unsigned _int32 Display::mode(char* name)
{
	if (extFunctions.SubMem(name,(void*)"GL",3)==0) return Display::RM_GL;
	if (extFunctions.SubMem(name,(void*)"GLES",5)==0) return Display::RM_GLES;
	return 0;
}

TYPEINFO(Display)

}

OPTIMIZE_OFF;
