/*
 * vector3l.h
 *
 *  Created on: 30.08.2013
 *      Author: Пантелеймонов Александр
 */

#ifndef VECTOR3L_H_
#define VECTOR3L_H_

#include <bt/functions.h>

namespace bt {

class vector3i;

class vector3l {
	long long x;
	long long y;
	long long z;

	_FORCEINLINE vector3l() {}
	_FORCEINLINE ~vector3l() {}
};

}

#endif /* VECTOR3L_H_ */
