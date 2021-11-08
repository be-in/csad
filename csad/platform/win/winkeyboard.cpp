/*
 * winkeyboard.cpp
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>

#if defined (OS_WIN)

#include <platform.h>
#include <core/system.h>
#include <core/input.h>
#include <bt.h>
//#include <photon/PkKeyDef.h>
//#include <photon/keycodes.h>
//#include <unicode.h>

#define	CAP_KEY_DOWN				0x00000001
#define	CAP_KEY_REPEAT				0x00000002
#define CAP_SCAN_VALID				0x00000020
#define CAP_SYM_VALID				0x00000040

OPTIMIZE_ON;

namespace csad {

using namespace bt;

Keyboard::Keyboard(char* driver,char* name):
		BaseKeyboard(driver,name)
{
	p_driver=driver;
	p_handle = -1;
	init();
	Input::input().p_keyboard->addObject(this,name);
	extFunctions.CleanMem(p_map,32);
}

Keyboard::Keyboard(const char* driver,const char* name):
		BaseKeyboard(driver,name)
{
	p_driver=driver;
	p_handle = -1;
	init();
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
	if (p_handle >= 0) return true;
	p_handle=System::system().getIES().newid();
	if (p_handle == -1) {
#ifdef LOG_CSAD
		Log::console("Keyboard::init() keyboard not found. driver %s",p_driver.str());
#endif
		return false;
	}
	System::system().getIES().registerEvent(p_handle,this);
	return true;
}

bool Keyboard::close()
{
	if (p_handle!=-1) {
		bool ret=System::system().getIES().unregisterEvent(p_handle);
		p_handle=-1;
		return ret;
	}
#ifdef LOG_CSAD
	Log::console("Keyboard::close() keyboard not initialized.");
#endif
	return false;
}

void Keyboard::read(void *msg)
{
	BaseInterfaceEventSystem::Event *_msg=(BaseInterfaceEventSystem::Event *)msg;
	//p_updata=false;
	if (_msg->message == WM_KEYDOWN) {
		int scancode=_msg->wparam & 0xFF;
		extFunctions.SetBit(scancode,1,p_map);
		int flag=0;
		if (extFunctions.GetBit(KEY_SHIFT,p_map)!=0) {
			flag^=1;
			flag|=2;
		}
		char key=(char)extFunctions.KeyToUniChar(scancode,flag);
		csad::Input::input()._write32(key);
		p_updata=true;
	}
	if (_msg->message==WM_KEYUP) {
		int scancode=_msg->wparam & 0xFF;
		extFunctions.SetBit(scancode,0,p_map);
		p_updata=true;
	}
}

}

OPTIMIZE_OFF;

#endif