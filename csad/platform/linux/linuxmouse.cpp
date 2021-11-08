/*
 *  linuxmouse.cpp
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr
 */

#include <platform/platformapi.h>

#if defined (OS_LINUX)

#include <platform.h>
#include <platform/log.h>
#include <core/system.h>
#include <core/input.h>
#include <X11/Xlib.h>

OPTIMIZE_ON;

namespace csad {

Mouse::Mouse(char* driver,char* name):
		BaseMouse(driver,name)
{
	p_isinit=false;
	p_driver=driver;
	p_handle=-1;
	Input::input().p_mouse->addObject(this,name);
}

Mouse::Mouse(const char* driver,const char* name):
		BaseMouse(driver,name)
{
	p_driver=driver;
	Input::input().p_mouse->addObject(this,name);
}

bool Mouse::init()
{
	p_isinit=true;
	p_buttons=0;
	p_sufrace=0;
	p_updata=false;
	p_delta=vector3f(0.0f);
	p_pos=vector3f(0.0f);
	p_handle=System::system().getIES().newid();
	if (p_handle == -1) {
		Log::console("Mouse::init() mouse");
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
	Log::console("Mouse::close() mouse not initialized.");
	return false;
}

struct POINTS {
	short int x;
	short int y;
};

int convertToButton(int val)
{
	int key=val;
	if (val==1) key=0;
	if (val==2) key=2;
	if (val==3) key=1;
	if (val==4) key=31;
	if (val==5) key=31;
	if (val>31) key=31;
	return key;
}

void Mouse::read(void *msg)
{
	BaseInterfaceEventSystem::Event *_msg=(BaseInterfaceEventSystem::Event *)msg;
	p_updata=false;
	p_sufrace=(void*)_msg->id;

	p_delta.z=0;
	if (_msg->message==ButtonPress) {
		p_updata=true;
		extFunctions.SetBit(convertToButton(_msg->wparam & 0xFF),1,&p_buttons);
		if ((_msg->wparam & 0xFF)==4) {
			p_delta.z=-1.9f;
		} else if ((_msg->wparam & 0xFF)==5) {
			p_delta.z=1.9f;
		}
	}
	if (_msg->message==ButtonRelease) {
		p_updata=true;
		extFunctions.SetBit(convertToButton(_msg->wparam & 0xFF),0,&p_buttons);
/*		if (((_msg->wparam & 0xFF)==4) && ((_msg->wparam & 0xFF)==5)) {
			p_delta.z=0;
		}*/
	}
	if (_msg->message==MotionNotify || _msg->message==ButtonRelease || _msg->message==ButtonPress) {
		p_updata=true;

		//lpRect

		//p_delta.x = lpRect.left+p->x - p_pos.x;
		//p_delta.y = lpRect.top+p->y - p_pos.y;
		POINTS *p=(POINTS *)&_msg->lparam;
		p_delta.x = p->x - p_pos.x;
		p_delta.y = p->y - p_pos.y;
		p_pos+=p_delta;
	}
}

void Mouse::setDriver(char *param)
{
	p_driver=param;
}

void *Mouse::set(unsigned int id,void * param)
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

TYPEINFO(Mouse)

}

OPTIMIZE_OFF;

#endif
