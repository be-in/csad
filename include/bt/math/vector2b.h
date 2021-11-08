/*
 * vector2b.h
 *
 *  Created on: 12.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef VECTOR2B_H_
#define VECTOR2B_H_

#include <bt/functions.h>

namespace bt {

WARNING_DISABLE;
OPTIMIZE_ON;

class vector2f;

/**
 * @class vector2b
 *
 * @ingroup math
 * @brief vector2b - ���������� ������������� ����������� ������ ����.
 *
 * @see math
 */

	class vector2b {
	public:
		/// �������� ��� X
		unsigned char x;
		/// �������� ��� Y
		unsigned char y;

		/// ����������� �� ������ �������������� �������� �����.
		_FORCEINLINE vector2b() {}
		/// �����������, ������ ��� ��������� ������� ������ ��������.
		_FORCEINLINE vector2b(unsigned char _a) {x=y=_a;}
		///
		_FORCEINLINE vector2b(vector2f *_a) {vecFunctions.V2FTo2B((void*)_a,(void*)this);}
		_FORCEINLINE ~vector2b() {}

		/// set value
		_FORCEINLINE void setInt(unsigned short val) {*((unsigned short*)this)=val;}
		/// return value
		_FORCEINLINE unsigned short getInt() {return *((unsigned short*)this);}

		/// ��������� � ���������� ��� � ��������� �������
		_FORCEINLINE unsigned char &operator[](unsigned int id) const {
			return ((unsigned char*)this)[id];
		}

		/// ����������� �������������� ���� vector2b::t()
		BT_API TYPEINFO_H;
	};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* VECTOR2B_H_ */
