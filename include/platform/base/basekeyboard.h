/*
 * keyboard.h
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef BASE_KEYBOARD_H_
#define BASE_KEYBOARD_H_

#include <core/baseobject.h>

namespace csad {

class BaseKeyboard : public BaseObject {
public:
	MEMDEFAULT(BaseKeyboard)

	_FORCEINLINE BaseKeyboard(char* ,char* ) {}
	_FORCEINLINE BaseKeyboard(const char* ,const char* ) {}

	enum Keys {
		KEY_ANY = -1,
		KEY_MOUSELEFT = 1,
		KEY_MOUSERIGHT = 2,
		KEY_CANCEL = 3,
		KEY_MOUSEMIDDLE = 4,
		KEY_BAKCSPACE = 8,
		KEY_TAB = 9,
		KEY_ENTER = 13,
		KEY_SHIFT = 16,
		KEY_CTRL = 17,
		KEY_PAUSE = 19,
		KEY_CAPSLOCK = 20,
		KEY_ESC = 27,
		KEY_SPACE = 32,
		KEY_PAGEUP = 33,
		KEY_PAGEDOWN = 34,
		KEY_END = 35,
		KEY_HOME = 36,
		KEY_LEFT = 37,
		KEY_UP = 38,
		KEY_RIGHT = 39,
		KEY_DOWN = 40,
		KEY_INS = 45,
		KEY_DEL = 46,
		KEY_0 = 48,
		KEY_1 = 49,
		KEY_2 = 50,
		KEY_3 = 51,
		KEY_4 = 52,
		KEY_5 = 53,
		KEY_6 = 54,
		KEY_7 = 55,
		KEY_8 = 56,
		KEY_9 = 57,
		KEY_A = 65,
		KEY_B = 66,
		KEY_C = 67,
		KEY_D = 68,
		KEY_E = 69, //101
		KEY_F = 70,
		KEY_G = 71,
		KEY_H = 72,
		KEY_I = 73,
		KEY_J = 74,
		KEY_K = 75,
		KEY_L = 76,
		KEY_M = 77,
		KEY_N = 78,
		KEY_O = 79,
		KEY_P = 80,
		KEY_Q = 81,
		KEY_R = 82,
		KEY_S = 83,
		KEY_T = 84,
		KEY_U = 85,
		KEY_V = 86,
		KEY_W = 87,
		KEY_X = 88, //120
		KEY_Y = 89,
		KEY_Z = 90,
		KEY_WIN = 92,
		KEY_CONTEXTMENU = 93,
		KEY_NUM_PLUS = 107,
		KEY_NUM_MINUS = 109,
		KEY_F1 = 112,
		KEY_F2 = 113,
		KEY_F3 = 114,
		KEY_F4 = 115,
		KEY_F5 = 116,
		KEY_F6 = 117,
		KEY_F7 = 118,
		KEY_F8 = 119,
		KEY_F9 = 120,
		KEY_F10 = 121,
		KEY_F11 = 122,
		KEY_F12 = 123,
		KEY_NUMLOCK = 144,
		KEY_SCROLL = 145,
		KEY_COLON = 186,
		KEY_PLUS = 187,
		KEY_COMMA = 188,
		KEY_MINUS = 189,
		KEY_PERIOD = 190,
		KEY_SLASH = 191,
		KEY_TILDE = 192,
		KEY_SQUARELEFT = 219,
		KEY_BACKSLASH = 220,
		KEY_SQUARERIGHT = 221,
		KEY_COMMAS = 222,
	};

	enum ScanCode {
		SC_ESC = 1,
		SC_1 = 2,
		SC_2 = 3,
		SC_3 = 4,
		SC_4 = 5,
		SC_5 = 6,
		SC_6 = 7,
		SC_7 = 8,
		SC_8 = 9,
		SC_9 = 10,
		SC_0 = 11,
		SC_12 = 12,
		SC_EQUAL = 13,
		SC_BAKCSPACE = 14,
		SC_TAB = 15,
		SC_16 = 16,
		SC_17 = 17,
		SC_E = 18,
		SC_R = 19,
		SC_T = 20,
		SC_Y = 21,
		SC_U = 22,
		SC_I = 23,
		SC_O = 24,
		SC_P = 25,
		SC_ENTER = 28,
		SC_CTRL = 29,
		SC_A = 30,
		SC_S = 31,
		SC_D = 32,
		SC_F = 33,
		SC_G = 34,
		SC_H = 35,
		SC_J = 36,
		SC_K = 37,
		SC_L = 38,
		SC_39 = 39,
		SC_40 = 40,
		SC_TILDE = 41,
		SC_LEFTSHIFT = 42,
		SC_43 = 43,
		SC_Z = 44,
		SC_X = 45,
		SC_C = 46,
		SC_V = 47,
		SC_B = 48,
		SC_N = 49,
		SC_M = 50,
		SC_51 = 51,
		SC_52 = 52,
		SC_DIV = 53,
		SC_RIGHTSHIFT = 54,
		SC_MUL = 55,
		SC_56 = 56,
		SC_57 = 57,
		SC_CAPSLOCK = 58,
		SC_F1 = 59,
		SC_F2 = 60,
		SC_F3 = 61,
		SC_F4 = 62,
		SC_F5 = 63,
		SC_F6 = 64,
		SC_F7 = 65,
		SC_F8 = 66,
		SC_F9 = 67,
		SC_68 = 68,
		SC_NUMLOCK = 69,
		SC_SCROLL = 70,
		SC_71 = 71,
		SC_UP = 72,
		SC_SUB = 74,
		SC_LEFT = 75,
		SC_76 = 76,
		SC_RIGHT = 77,
		SC_ADD = 78,
		SC_79 = 79,
		SC_DOWN = 80,
		SC_81 = 81,
		SC_INS = 82,
		SC_DEL = 83,
		SC_84 = 84,
		SC_85 = 85,
		SC_86 = 86,
		SC_F11 = 87,
		SC_F12 = 88,
	};

	enum Flags {
		UPCHAR = 0x00000001,
		ENCODE = 0x00000000,
		RUCODE = 0x00010000,
	};

	virtual bool getKey(int ) {return false;}
	virtual char *getMap()  {return 0;}

	/// Овзвращает true если произошли изменения монипулятором
	_FORCEINLINE bool getUpdata() {return p_updata;}

private:
	bool p_isinit;
	bool p_updata;

	virtual bool init() {p_isinit=false; return p_isinit;}
	virtual bool close() {return false;}

	friend class Keyboard;
	friend class Input;
};

}
#endif /* BASE_KEYBOARD_H_ */
