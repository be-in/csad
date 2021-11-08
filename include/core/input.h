/*
 * input.h
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef INPUT_H_
#define INPUT_H_

#include <bt.h>
#include <core/objectmanager.h>
#include <platform.h>

namespace csad {

class Mouse;
class Keyboard;
class Display;

/**
 * @class Input
 *
 * @ingroup input
 * @brief Input - Manager device input.
 *
 * @see input
 */

class Input:public BaseObject {
public:
	MEMDEFAULT(Input)

	CSAD_API Input();
	CSAD_API ~Input();

	enum Button {
		MOUSELEFT = 0x0001,
		MOUSERIGHT = 0x0002,
		MOUSEMIDDLE = 0x0004,
	};

	/// creates an event handler for an input device type mouse
	CSAD_API Mouse* createMouse(char * driver,char * name);
	_FORCEINLINE Mouse* createMouse(const char * driver="",const char * name="") {return createMouse((char*)driver,(char*)name);}
	/// creates an event handler for an input device type keyboard
	CSAD_API Keyboard* createKeyboard(char * driver,char * name);
	_FORCEINLINE Keyboard* createKeyboard(const char * driver="",const char * name="") {return createKeyboard((char*)driver,(char*)name);}

	/// Returns an object of a mouse
	CSAD_API Mouse* getMouse(char * name);
	_FORCEINLINE Mouse* getMouse(const char * name) { return getMouse((char*)name);}
	/// Returns an object keyboard
	CSAD_API Keyboard* getKeyboard(char * name);
	_FORCEINLINE Keyboard* getKeyboard(const char * name) { return getKeyboard((char*)name);}

	/// The screen on which the mouse is
	_FORCEINLINE Display *getDisplay() {return p_display;}

	_FORCEINLINE bool isKeyboardUpdata() {return (mState & 0x2)!=0;}
	_FORCEINLINE bool isCursorUpdata() {return (mState & 0x1)!=0;}
	//CSAD_API void setCursorPos();
	/// The General position of the cursor all manipulators
	_FORCEINLINE vector3f& getCursorPos() { return p_cursorPos; }
	/// The offset of the General provisions of the cursor all manipulators
	_FORCEINLINE vector3f& getCursorDelta() { return p_cursorDelta; }
	_FORCEINLINE void setButton(unsigned int id,bool bit) { extFunctions.SetBit(id & 0xff,bit,p_buttonsBuff); }
	/// Returns the status of the specified key
	_FORCEINLINE bool getButton(unsigned int id) { return extFunctions.GetBit(id & 0xff,p_buttonsBuff)!=0; }
	CSAD_API bool getAnyKey();

	CSAD_API char readKey();

	CSAD_API BaseObject *finder(char *path);

	CSAD_API void *set(unsigned _int32 ,void *);

	/// Provides access to the active input Manager
	CSAD_API static Input & input();

	CSAD_API TYPEINFO_H

	/// the event handler
	CSAD_API void init();
	/// the event handler
	CSAD_API void update();
	/// the event handler
	CSAD_API void updateReset();
	/// the event handler
	CSAD_API void close();

private:
	unsigned int mState;
	//bool p_isCursorUpdata;
	vector3f p_cursorPos;
	vector3f p_cursorDelta;
	char p_buttonsBuff[32];
	char p_keyBuff[32];

	ObjectManager *p_mouse;
	ObjectManager *p_keyboard;
	Display *p_display;

	void _write32(char c);

friend class Mouse;
friend class Keyboard;
};

}

#endif /* INPUT_H_ */
