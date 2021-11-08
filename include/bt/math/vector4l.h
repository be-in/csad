/*
 * vector4l.h
 *
 *  Created on: 30.08.2013
 *      Author: Пантелеймонов Александр
 */

#ifndef VECTOR4L_H_
#define VECTOR4L_H_

#include <bt/functions.h>

namespace bt {

class vector4l {
	long long x;
	long long y;
	long long z;
	long long w;

	_FORCEINLINE vector4l() {}
	_FORCEINLINE ~vector4l() {}
};

}

#endif /* VECTOR4L_H_ */
