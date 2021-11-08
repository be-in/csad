/*
 * linuxkeyboard.cpp
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>

#if defined (OS_LINUX)

#include <platform.h>
#include <core/system.h>
#include <core/input.h>
#include <bt.h>
#include <X11/Xlib.h>

OPTIMIZE_ON;

namespace csad {

using namespace bt;

Keyboard::Keyboard(char* driver,char* name):
		BaseKeyboard(driver,name)
{
	p_driver=driver;
	Input::input().p_keyboard->addObject(this,name);
	extFunctions.CleanMem(p_map,32);
}

Keyboard::Keyboard(const char* driver,const char* name):
		BaseKeyboard(driver,name)
{
	p_driver=driver;
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
	p_handle=-1;
	p_handle=System::system().getIES().newid();
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
		p_handle=-1;
		return ret;
	}
	Log::console("Keyboard::close() keyboard not initialized.");
	return false;
}

int convertToKey(int val)
{
	int key=val;
	if (val==36) key=36;
	if (val==37) key=37;
	if (val==38) key=38;
	if (val==39) key=39;
	if (val==40) key=40;
	if (val==41) key=33;
	if (val==42) key=34;
	if (val==43) key=35;
	if (val==44) key=188;
	if (val==46) key=190;
	if (val==47) key=191;
	if (val==55) key=46;
	//if (val==59) key=186s;
	if (val==83) key=144;
	if (val==91) key=219;
	if (val==92) key=220;
	if (val==93) key=221;
	if (val==96) key=192;
	if (val==181) key=16;
	if (val==182) key=16;
	if (val==183) key=17;
	if (val==184) key=17;
	if (val==185) key=20;
	//if (val==190) key=ALT;
	if (val==192) key=92;
	if (val==211) key=45;
	if (val==220) key=8;
	if (val==221) key=9;
	//if (val==225) key=27;
	if (val==232) key=145;
	if (val==239) key=27;
	if ((val>=146) && (val<=157)) key=val-34;
	if ((val>=97) && (val<=122)) key=val-32;
	//Log::console("key %i val %i",key,val);
	return key;
}

void Keyboard::read(void *msg)
{
	BaseInterfaceEventSystem::Event *_msg=(BaseInterfaceEventSystem::Event *)msg;
	if (_msg->message==KeyPress) {
		int scancode=convertToKey(_msg->wparam & 0xFF);
		extFunctions.SetBit(scancode,1,p_map);
		int flag=0;
		if (extFunctions.GetBit(KEY_SHIFT,p_map)!=0) {
			flag^=1;
			flag|=2;
		}
		char key=extFunctions.KeyToUniChar(scancode,flag);
		csad::Input::input()._write32(key);
		p_updata=true;
	}
	if (_msg->message==KeyRelease) {
		int scancode=convertToKey(_msg->wparam & 0xFF);
		extFunctions.SetBit(scancode,0,p_map);
		p_updata=true;
	}
}

}

OPTIMIZE_OFF;

#endif
