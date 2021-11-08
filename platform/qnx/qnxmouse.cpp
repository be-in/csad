/*
 * qnxmouse.cpp
 *
 *  Created on: 09.08.2013
 *      Author: Пантелеймонов Александр
 */

#include <platform/platformapi.h>

#if defined (OS_QNX)

#include <bt.h>
#include <platform.h>
#include <core/system.h>
#include <core/input.h>

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
	p_handle=-1;
	Input::input().p_mouse->addObject(this,name);
}

bool Mouse::init()
{
	p_isinit=true;
	p_handle = ::open(p_driver.str(),O_RDONLY);
	if (p_handle == -1) {
		p_isinit=false;
		Log::console("Mouse::init() mouse not found. driver %s",p_driver.str());
		return false;
	}
	p_isinit=true;
	System::system().getIES().registerEvent(p_handle,this);
	return true;
}

bool Mouse::close()
{
	p_isinit=false;
	if (p_handle!=-1) {
		bool ret=System::system().getIES().unregisterEvent(p_handle);
		::close(p_handle);
		p_handle=-1;
		return ret;
	}
	Log::console("Mouse::close() mouse not initialized.");
	return false;
}

void Mouse::read()
{
	struct _mouse_packet pkt;
	int ret = ::read(p_handle,&pkt,sizeof(struct _mouse_packet));
	if (ret==sizeof(struct _mouse_packet)) {
		p_updata=true;
		p_delta.x = pkt.dx;
		p_delta.y = -pkt.dy;
		p_delta.z = pkt.dz;
		p_buttons=0;
		if ((pkt.hdr.buttons & 4)!=0) p_buttons|=LEFT;
		if ((pkt.hdr.buttons & 2)!=0) p_buttons|=MIDDLE;
		if ((pkt.hdr.buttons & 1)!=0) p_buttons|=RIGHT;
		p_pos+=p_delta;
	}
}

void Mouse::setDriver(char *param)
{
	if (p_handle!=-1) {
		close();
		p_driver=param;
		init();
	} else {
		p_driver=param;
	}
}

void *Mouse::set(unsigned int id,void * data)
{
	if (id==BaseObject::EVENT) read();
	if (id==BaseObject::TYPE) return Mouse::t();
	if (id==BaseObject::WRITE) {
		ParametersList *list=(ParametersList *)data;
		if (list->contains("driver")) setDriver((*list)["driver"].getString());
		return 0;
	}
	if (id==BaseObject::READ) {
		Variant *p;
		ParametersList *list=(ParametersList *)data;
		p=&(*list)["driver"];
		p->setString(p_driver.str());
		return data;
	}
	return 0;
}

TYPEINFO(Mouse)

}

#endif