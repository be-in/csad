/*
 * input.cpp
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <core/input.h>
#include "csadcore.h"
#include <platform.h>
#include <scene/camera.h>

OPTIMIZE_ON;

namespace csad {

Input::Input():
	p_cursorPos(0.0f),
	p_cursorDelta(0.0f)
{
	p_mouse = new ObjectManager("mouse");
	p_keyboard = new ObjectManager("keyboard");
	p_display = 0;
	extFunctions.CleanMem(p_buttonsBuff,32);
	extFunctions.CleanMem(p_keyBuff,32);
	mState=0;
}

Input::~Input()
{
	if (p_mouse) p_mouse->destroyObjects<Mouse>();
	if (p_keyboard) p_keyboard->destroyObjects<Keyboard>();
	delete p_mouse;
	delete p_keyboard;
	p_mouse=0;
	p_keyboard=0;
}

Mouse* Input::createMouse(char * driver,char * name)
{
	if (name[0]!=0) {
		Mouse* r=(Mouse*)p_mouse->getObject(name);
		if (r) return r;
	}
	return new Mouse(driver,name);
}

Keyboard* Input::createKeyboard(char * driver,char * name)
{
	if ((name!=0) && (name[0]!=0)) {
		Keyboard* r=(Keyboard*)p_keyboard->getObject(name);
		if (r) return r;
	}
	return new Keyboard(driver,name);
}

Mouse* Input::getMouse(char * name)
{
	return (Mouse*)p_mouse->getObject(name);
}

Keyboard* Input::getKeyboard(char * name)
{
	return (Keyboard*)p_keyboard->getObject(name);
}

bool Input::getAnyKey()
{
	_int32 *buff=(_int32 *)p_buttonsBuff;
	for (int i=0;i<8;i++) if (buff[i]) return true;
	return false;
}

char Input::readKey()
{
	int id=p_keyBuff[30];
	int idr=p_keyBuff[31];
	if (idr==id) return 0;
	char r=p_keyBuff[idr];
	idr++;
	if (idr>29) idr=0;
	p_keyBuff[31]=idr;
	return r;
}

BaseObject *Input::finder(char *path)
{
	ObjectManager::Finder find(path);
	ObjectManager *inputmanager=(ObjectManager*)ObjectManager::manager().getObject(find.getNext());
	if (inputmanager) {
		find.next();
		if (find.getNext()){
			BaseObject* obj=(BaseObject *)inputmanager->getObject(find.getNext());
			if (obj) {
				return obj;
			} else {
#ifdef LOG_CSAD
				Log::console("Can`t find input: %s",find.getNext());
#endif
			}
		}
	} else {
#ifdef LOG_CSAD
		Log::console("Can`t find input manager: %s",find.getNext());
#endif
	}
	return inputmanager;
}

void *Input::set(unsigned _int32 id,void *)
{
	if (id==BaseObject::TYPE) return Input::t();
	return 0;
}

Input & Input::input()
{
	return *core->input();
}

void Input::init()
{
	ObjectsList::iterator it= p_mouse->getObjects().begin();
	ObjectsList::iterator end= p_mouse->getObjects().end();
	while (it!=end) {
		BaseMouse * mouse = (BaseMouse*)it.value();
		mouse->init();
		it++;
	}
	it= p_keyboard->getObjects().begin();
	end= p_keyboard->getObjects().end();
	while (it!=end) {
		BaseKeyboard * keyboard = (BaseKeyboard*)it.value();
		keyboard->init();
		it++;
	}
}

void Input::updateReset()
{
	while (readKey()!=0);
	ObjectsList::iterator it= p_mouse->getObjects().begin();
	ObjectsList::iterator end= p_mouse->getObjects().end();
	while (it!=end) {
		BaseMouse * mouse = (BaseMouse*)it.value();
		mouse->p_updata=false;
		it++;
	}
	it= p_keyboard->getObjects().begin();
	end= p_keyboard->getObjects().end();
	while (it!=end) {
		BaseKeyboard * keyboard = (BaseKeyboard*)it.value();
		keyboard->p_updata=false;
		it++;
	}
}

void Input::_write32(char c)
{
	int id=p_keyBuff[30];
	int idr=p_keyBuff[31];
	p_keyBuff[id]=c;
	id++;
	if (id>29) id=0;
	if (idr==id) idr++;
	if (idr>29) idr=0;
	p_keyBuff[30]=id;
	p_keyBuff[31]=idr;
}

void Input::update()
{
	mState=0;
	ObjectsList::iterator it= p_mouse->getObjects().begin();
	ObjectsList::iterator end= p_mouse->getObjects().end();
	vector3f pos(0.0f,0.0f,0.0f);
	unsigned int button=0;
	void *surface=0;
	bool needfind=false;
	float c=0;
	while (it!=end) {
		BaseMouse * mouse = (BaseMouse*)it.value();
		if (mouse->getUpdata()) {
			if ((surface) && (surface!=mouse->getSurface())) needfind=true;
			surface=mouse->getSurface();
			pos+=mouse->p_pos;
			c+=1.0f;
		}
		button|=mouse->p_buttons;
		it++;
	}
	if (c>0) mState|=0x1;
	if ((mState&0x1)!=0) {
		c=1.0f/c;
		pos=pos*c;
		p_cursorDelta=pos-p_cursorPos;
		p_cursorPos=pos;
		/*if ((needfind) || (!surface)) {
			p_display=Graph::graph().getDisplayIntersect(&p_cursorPos);
		}*/
		p_display=0;
		if ((surface) && (!needfind)) p_display=Graph::graph().getDisplayByHandle(surface);
		int b=0;
		if (button & BaseMouse::LEFT) b=1;
		extFunctions.SetBit(MOUSELEFT,b,p_buttonsBuff);
		b=0;
		if (button & BaseMouse::RIGHT) b=1;
		extFunctions.SetBit(MOUSERIGHT,b,p_buttonsBuff);
		b=0;
		if (button & BaseMouse::MIDDLE) b=1;
		extFunctions.SetBit(MOUSEMIDDLE,b,p_buttonsBuff);
	} else {
		p_cursorDelta.zero();
	}

	it= p_keyboard->getObjects().begin();
	end= p_keyboard->getObjects().end();

	bool KeyUpdata=false;
	while (it!=end) {
		BaseKeyboard * keyboard = (BaseKeyboard*)it.value();
		if (keyboard->getUpdata()) KeyUpdata=true;
		it++;
	}

	if (KeyUpdata) {
		it= p_keyboard->getObjects().begin();
		mState|=0x2;
		for (int i=1;i<32;i++) p_buttonsBuff[i]=0;
		while (it!=end) {
			BaseKeyboard * keyboard = (BaseKeyboard*)it.value();
			char *mapc=keyboard->getMap();
			for (int i=0;i<32;i++) {
				p_buttonsBuff[i]|=mapc[i];
			}
			it++;
		}
	}
}

void Input::close()
{
	ObjectsList::iterator it= p_mouse->getObjects().begin();
	ObjectsList::iterator end= p_mouse->getObjects().end();
	while (it!=end) {
		BaseMouse * mouse = (BaseMouse*)it.value();
		mouse->close();
		it++;
	}
	it= p_keyboard->getObjects().begin();
	end= p_keyboard->getObjects().end();
	while (it!=end) {
		BaseKeyboard * keyboard = (BaseKeyboard*)it.value();
		keyboard->close();
		it++;
	}
}

TYPEINFO(Input)

}

OPTIMIZE_OFF;
