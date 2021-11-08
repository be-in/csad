/*
 * vector3b.h
 *
 *  Created on: 12.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef VECTOR3B_H_
#define VECTOR3B_H_

#include <bt/functions.h>

namespace bt {

WARNING_DISABLE;
OPTIMIZE_ON;

class vector3f;

/**
 * @class vector2b
 *
 * @ingroup math
 * @brief vector2b - трехмерный целочисленный беззнаковый вектор байт.
 *
 * @see math
 */

	class vector3b {
	public:
		/// Параметр оси X
		unsigned char x;
		/// Параметр оси Y
		unsigned char y;
		/// Параметр оси Z
		unsigned char z;

		/// Конструктор не задает первоначальные значения полям.
		_FORCEINLINE vector3b() {}
		/// Конструктор, задает все параметры равными одному значению.
		_FORCEINLINE vector3b(unsigned char _a) {x=y=z=_a;}
		///
		_FORCEINLINE vector3b(vector3f *_a) {vecFunctions.V3FTo3B((void*)_a,(void*)this);}
		_FORCEINLINE ~vector3b() {}

		/// set value
		_FORCEINLINE void setInt(unsigned short val) {*((unsigned short*)this)=val;}
		/// return value
		_FORCEINLINE unsigned short getInt() {return *((unsigned short*)this);}

		/// Обращение к параметрам как к элементам массива
		_FORCEINLINE unsigned char &operator[](unsigned int id) const {
			return ((unsigned char*)this)[id];
		}

		/// Статический индентификатор типа vector3b::t()
		BT_API TYPEINFO_H;
	};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* VECTOR3B_H_ */
