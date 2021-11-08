/*
 * vector4b.h
 *
 *  Created on: 12.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef VECTOR4B_H_
#define VECTOR4B_H_

#include <bt/functions.h>

namespace bt {

WARNING_DISABLE;
OPTIMIZE_ON;

class vector4f;

/**
 * @class vector4b
 *
 * @ingroup math
 * @brief vector4b - ������������� ������������� ����������� ������ ����.
 *
 * @see math
 */

	class vector4b {
	public:
		/// �������� ��� X
		unsigned char x;
		/// �������� ��� Y
		unsigned char y;
		/// �������� ��� Z
		unsigned char z;
		/// �������� ��� W
		unsigned char w;

		/// ����������� �� ������ �������������� �������� �����.
		_FORCEINLINE vector4b() {}
		/// �����������, ������ ��� ��������� ������� ������ ��������.
		_FORCEINLINE vector4b(unsigned char _a) {x=y=z=w=_a;}
		///
		_FORCEINLINE vector4b(vector4f *_a) {vecFunctions.V4FTo4B((void*)_a,(void*)this);}
		_FORCEINLINE ~vector4b() {}

		/// set value
		_FORCEINLINE void setInt(unsigned _int32 val) {*((unsigned _int32*)this)=val;}
		/// return value
		_FORCEINLINE unsigned _int32 getInt() {return *((unsigned _int32*)this);}

		/// ��������� � ���������� ��� � ��������� �������
		_FORCEINLINE unsigned char &operator[](unsigned int id) const {
			return ((unsigned char*)this)[id];
		}

		/// ����������� �������������� ���� vector4b::t()
		BT_API TYPEINFO_H;
	};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* VECTOR4B_H_ */
