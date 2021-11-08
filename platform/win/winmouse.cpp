/*
 * winmouse.cpp
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>

#if defined (OS_WIN)

#include <platform/mouse.h>
#include <platform/win/winlog.h>
#include <core/system.h>
#include <core/input.h>

OPTIMIZE_ON;

namespace csad {

Mouse::Mouse(char* driver,char* name):
		BaseMouse(driver,name)
{
	p_isinit=false;
	p_driver=driver;
	p_handle=-1;
	init();
	Input::input().p_mouse->addObject(this,name);
}

Mouse::Mouse(const char* driver,const char* name):
		BaseMouse(driver,name)
{
	p_isinit = false;
	p_driver=driver;
	p_handle = -1;
	init();
	Input::input().p_mouse->addObject(this,name);
}

bool Mouse::init()
{
	if (p_isinit) return true;
	p_isinit=true;
	p_buttons=0;
	p_sufrace=0;
	p_updata=false;
	p_delta=vector3f(0.0f);
	p_pos=vector3f(0.0f);
	p_handle=System::system().getIES().newid();
	if (p_handle == -1) {
#ifdef LOG_CSAD
		Log::console("Mouse::init() mouse");
#endif
		return false;
	}
	System::system().getIES().registerEvent(p_handle,this);
	return true;
}

bool Mouse::close()
{
	p_isinit=false;
	if (p_handle!=-1) {
		bool ret=System::system().getIES().unregisterEvent(p_handle);
		p_handle=-1;
		return ret;
	}
#ifdef LOG_CSAD
	Log::console("Mouse::close() mouse not initialized.");
#endif
	return false;
}

void Mouse::read(void *msg)
{
	BaseInterfaceEventSystem::Event *_msg=(BaseInterfaceEventSystem::Event *)msg;
	//p_updata=false;
	p_sufrace=(void*)_msg->id;
	
	if (_msg->message==WM_MBUTTONDOWN || _msg->message==WM_LBUTTONDOWN || _msg->message==WM_RBUTTONDOWN) {
		p_updata=true;
		p_buttons=_msg->wparam & 0xFFFF;
	}
	if (_msg->message==WM_MBUTTONUP || _msg->message==WM_LBUTTONUP || _msg->message==WM_RBUTTONUP) {
		p_updata=true;
		p_buttons=_msg->wparam & 0xFFFF;
	}
	if (_msg->message==WM_MOUSEWHEEL) {
		p_updata=true;
		int p=_msg->wparam & 0xFFF80000;
		if ((signed int)(_msg->wparam & 0xFFF80000)<0) {
			p_delta.z=0.01f*((-(signed int)_msg->wparam)>>16);
		} else {
			p_delta.z=-0.01f*(_msg->wparam>>16);
		}//GET_WHEEL_DELTA_WPARAM
		p_pos.z+=p_delta.z;
	} else p_delta.z=0;
 	/*if (_msg->message==WM_MOUSELEAVE) {
		p_sufrace=0;
		p_buttons=0;
		//p_updata=true;
	}*/
	if (_msg->message!=WM_MOUSEMOVE) return;
	p_updata=true;

	p_buttons=_msg->wparam & 0xFFFF;

	//RECT lpRect;
	//GetWindowRect((HWND)_msg->id,&lpRect);
	//POINTS *p=(POINTS *)&_msg->lparam;
	//p_delta.x = lpRect.left+p->x - p_pos.x;//((p->x-(lpRect.right-lpRect.left)*0.5f) - p_pos.x);
	//p_delta.y = lpRect.top+p->y - p_pos.y;//(-(p->y-(lpRect.bottom-lpRect.top)*0.5f) - p_pos.y);

	POINTS *p=(POINTS *)&_msg->lparam;
	POINT point;
	point.x=p->x;
	point.y=p->y;
	ClientToScreen((HWND)_msg->id,&point);

	p_delta.x = point.x - p_pos.x;//((p->x-(lpRect.right-lpRect.left)*0.5f) - p_pos.x);
	p_delta.y = point.y - p_pos.y;//(-(p->y-(lpRect.bottom-lpRect.top)*0.5f) - p_pos.y);

	p_pos+=p_delta;
//	p_buttons = pkt.hdr.buttons;
}

void Mouse::setDriver(char *param)
{
	p_driver=param;
}

void *Mouse::set(unsigned _int32 id,void * param)
{
	if (id==BaseObject::EVENT) read(param);
	if (id==BaseObject::TYPE) return Mouse::t();
	if (id==BaseObject::WRITE) {
		ParametersList *list=(ParametersList *)param;
		if (list->contains("driver")) setDriver((*list)["driver"].getString());
		return 0;
	}
	if (id==BaseObject::READ) {
		Variant *p;
		ParametersList *list=(ParametersList *)param;
		p=&(*list)["driver"];
		p->setString(p_driver.str());
		return param;
	}
	return 0;
}

void Mouse::setCursorPos(float x,float y)
{
	SetCursorPos(matFunctions.FTrunc(x),matFunctions.FTrunc(y));
}

TYPEINFO(Mouse)

}

OPTIMIZE_OFF;

#endif
