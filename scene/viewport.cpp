/*
 * viewport.cpp
 *
 *  Created on: 16.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/viewport.h>
#include <platform.h>
#include "csad/platform/localdisplay.h"

OPTIMIZE_ON;

namespace csad {

ViewPort::ViewPort()
{
	setFull();
}

ViewPort::~ViewPort()
{
}

vector4f &ViewPort::getRect()
{
	return p_view;
}

vector4i ViewPort::getRect(GlContext *context)
{
	if (!context) return vector4i(0,0,0,0);
	float aw=matFunctions.IToF(context->width());
	float ah=matFunctions.IToF(context->height());
	vector4f rect(p_view.x*aw,p_view.y*ah,p_view.z*aw,p_view.w*ah);
	rect.y=(ah-rect.w-rect.y);
	bt::vector4i vporti;
	vecFunctions.V4FTo4I(&rect,&vporti);
	return vporti;
}

vector4i ViewPort::getRect(Display *display)
{
	if (!display) return vector4i(0,0,0,0);
	float aw=matFunctions.IToF(display->width());
	float ah=matFunctions.IToF(display->height());
	vector4f rect(p_view.x*aw,p_view.y*ah,p_view.z*aw,p_view.w*ah);
	rect.y=(ah-rect.w-rect.y);
	bt::vector4i vporti;
	vecFunctions.V4FTo4I(&rect,&vporti);
	return vporti;
}

void ViewPort::setFull()
{
	p_view.x=0.0f;
	p_view.y=0.0f;
	p_view.z=1.0f;
	p_view.w=1.0f;
}

bool ViewPort::makeCurrent(unsigned int toTextureId)
{
	GlContext *mcontext=GlContext::getCurrent();
	if (!mcontext) return false;
	if (toTextureId) {
	//!!! bind texture;
/*		Render::BindTexture2D(toTextureId);
		Texture2D text(toTextureId);
		Render::setViewPort(0,0,text.getWidth(0),text.getHeight(0));*/
	} else {
		sFunctionsDisplayRender &dfunctions=((LocalDisplay*)mcontext->getDisplay())->functions();
		bt::vector4i vporti=getRect(mcontext);
		dfunctions.SetViewPort(vporti.x,vporti.y,vporti.z,vporti.w);
	}
	return true;
}

TYPEINFO(ViewPort)

}

OPTIMIZE_OFF;

