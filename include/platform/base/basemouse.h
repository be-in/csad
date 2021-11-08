/*
 * basemouse.h
 *
 *  Created on: 09.08.2013
 *      Author: Пантелеймонов Александр
 */

#ifndef BASE_MOUSE_H_
#define BASE_MOUSE_H_

#include <bt.h>
#include <core/baseobject.h>

namespace csad {

using namespace bt;

class BaseMouse : public BaseObject {
public:
	MEMDEFAULT(BaseMouse)

	enum Button {
		LEFT = 0x0001,
		RIGHT = 0x0002,
		MIDDLE = 0x0010,
	};

	_FORCEINLINE BaseMouse(char* ,char* ):p_delta(0.0f),p_pos(0.0f) {}
	_FORCEINLINE BaseMouse(const char* ,const char* ):p_delta(0.0f),p_pos(0.0f) {}

	/// Возвращает положение мыши и колеса прокрутки
	_FORCEINLINE vector3f& getPos() {return p_pos;}
	_FORCEINLINE void setPos(vector3f& pos) {p_pos=pos;}

	/// Возвращает изменения произошедшие за прошедшее время
	_FORCEINLINE vector3f& getDelta() {return p_delta;}
	_FORCEINLINE void setDelta(vector3f& delta) {p_delta=delta;}

	/// Возвращает состояние указанной клавиши мыши
	_FORCEINLINE bool getButton(unsigned _int32 b) {return (p_buttons & b)!=0;}

	/// Возвращает индификатор поверхности изображения к которой принадлежит указатель
	_FORCEINLINE void *getSurface() {return p_sufrace;}

	/// Овзвращает true если произошли изменения монипулятором
	_FORCEINLINE bool getUpdata() {return p_updata;}

private:

	bool p_isinit;
	bool p_updata;
	vector3f p_delta;
	vector3f p_pos;
	unsigned _int32  p_buttons;
	void *p_sufrace;

	virtual bool init() {p_isinit=false; return p_isinit;}
	virtual bool close() {return false;}

	friend class Mouse;
	friend class Input;
};

}

#endif /* BASE_MOUSE_H_ */
