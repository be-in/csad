/*
 *  osxmouse.cpp
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr
 */

#include <platform/platformapi.h>

#if defined (OS_OSX)

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

void Mouse::read(void *msg)
{
	BaseInterfaceEventSystem::Event *_msg=(BaseInterfaceEventSystem::Event *)msg;
	p_updata=false;
	p_sufrace=(void*)_msg->id;

	if (_msg->message==ButtonPress) {
		p_updata=true;
		p_buttons=_msg->wparam & 0xFFFF;
	}
	if (_msg->message==ButtonRelease) {
		p_updata=true;
		p_buttons=_msg->wparam & 0xFFFF;
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
