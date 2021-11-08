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
 * @brief vector2b - ���������� ������������� ����������� ������ ����.
 *
 * @see math
 */

	class vector3b {
	public:
		/// �������� ��� X
		unsigned char x;
		/// �������� ��� Y
		unsigned char y;
		/// �������� ��� Z
		unsigned char z;

		/// ����������� �� ������ �������������� �������� �����.
		_FORCEINLINE vector3b() {}
		/// �����������, ������ ��� ��������� ������� ������ ��������.
		_FORCEINLINE vector3b(unsigned char _a) {x=y=z=_a;}
		///
		_FORCEINLINE vector3b(vector3f *_a) {vecFunctions.V3FTo3B((void*)_a,(void*)this);}
		_FORCEINLINE ~vector3b() {}

		/// set value
		_FORCEINLINE void setInt(unsigned short val) {*((unsigned short*)this)=val;}
		/// return value
		_FORCEINLINE unsigned short getInt() {return *((unsigned short*)this);}

		/// ��������� � ���������� ��� � ��������� �������
		_FORCEINLINE unsigned char &operator[](unsigned int id) const {
			return ((unsigned char*)this)[id];
		}

		/// ����������� �������������� ���� vector3b::t()
		BT_API TYPEINFO_H;
	};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* VECTOR3B_H_ */
