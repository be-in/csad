/*
 * qnxkeyboard.cpp
 *
 *  Created on: 14.08.2013
 *      Author: Пантелеймонов Александр
 */

#include <platform/platformapi.h>

#if defined (OS_QNX)

#include <core/system.h>
#include <core/input.h>
#include <bt.h>
#include <platform.h>
//#include <photon/PkKeyDef.h>
//#include <photon/keycodes.h>
//#include <unicode.h>

#define	CAP_KEY_DOWN				0x00000001
#define	CAP_KEY_REPEAT				0x00000002
#define CAP_SCAN_VALID				0x00000020
#define CAP_SYM_VALID				0x00000040

namespace csad {

Keyboard::Keyboard(char* driver,char* name):
		BaseKeyboard(driver,name)
{
	p_driver=driver;
	p_handle=-1;
	Input::input().p_keyboard->addObject(this,name);
	extFunctions.CleanMem(p_map,32);
}

Keyboard::Keyboard(const char* driver,const char* name):
		BaseKeyboard(driver,name)
{
	p_driver=driver;
	p_handle=-1;
	Input::input().p_keyboard->addObject(this,name);
	extFunctions.CleanMem(p_map,32);
}

bool Keyboard::getKey(int id)
{
	return extFunctions.GetBit(id & 0xff,p_map)!=0;
}

char* Keyboard::getMap()
{
	return p_map;
}

bool Keyboard::init()
{
	p_handle = ::open(p_driver.str(),O_RDONLY);
	if (p_handle == -1) {
		Log::console("Keyboard::init() keyboard not found. driver %s",p_driver.str());
		return false;
	}
	System::system().getIES().registerEvent(p_handle,this);
	return true;
}

bool Keyboard::close()
{
	if (p_handle!=-1) {
		bool ret=System::system().getIES().unregisterEvent(p_handle);
		::close(p_handle);
		p_handle=-1;
		return ret;
	}
	Log::console("Keyboard::close() keyboard not initialized.");
	return false;
}

void Keyboard::read()
{
	struct _keyboard_packet pkt;
	int ret = ::read(p_handle,&pkt,sizeof(struct _keyboard_packet));
	if (ret==sizeof(struct _keyboard_packet)) {
		unsigned long int key_scan=0;
		unsigned long int key_sym=0;
		if (pkt.data.key_cap & CAP_SCAN_VALID) key_scan=pkt.data.key_scan;
		if (pkt.data.key_cap & CAP_SYM_VALID) key_sym=pkt.data.key_sym;
		if (pkt.data.key_cap & CAP_KEY_DOWN) {
			extFunctions.SetBit(key_scan & 0xff,1,p_map);
		} else {
			extFunctions.SetBit(key_scan & 0xff,0,p_map);
		}
	}
}

void *Keyboard::set(unsigned int id,void * data)
{
	if (id==BaseObject::TYPE) return Keyboard::t();
	if (id==BaseObject::EVENT) read();
	return 0;
}

TYPEINFO(Keyboard)

}

#endif
