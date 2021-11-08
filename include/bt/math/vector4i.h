/*
 * vector4i.h
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef VECTOR4I_H_
#define VECTOR4I_H_

#include <bt/functions.h>

namespace bt {

WARNING_DISABLE;
OPTIMIZE_ON;

/**
 * @class vector4i
 *
 * @ingroup math
 * @brief vector4i - four-dimensional integer vector.
 *
 * @see vector3i, vector2i math
 */

class vector4i {
public:
	_int32 x;
	_int32 y;
	_int32 z;
	_int32 w;

	/// The constructor does not set the initial values to the fields.
	_FORCEINLINE vector4i() {}
	/// Constructor, sets all parameters equal to one value.
	_FORCEINLINE vector4i(_int32 a) {x=y=z=w=a;}
	/// Constructor.
	/// @param _x - vector x
	/// @param _y - vector y
	/// @param _z - vector z
	/// @param _w - vector w
	_FORCEINLINE vector4i(_int32 _x,_int32 _y,_int32 _z,_int32 _w) {x=_x;y=_y;z=_z;w=_w;}
	/// The transformation vector in floating-point format to integer.
	_FORCEINLINE vector4i(vector4f*_a) {vecFunctions.V4FTo4I((void*)_a,(void*)this);}
	_FORCEINLINE ~vector4i() {}

	/// Sets the value of the fields to zero.
	_FORCEINLINE void zero() {x=y=z=w=0;}

	/// Addition of integer vectors
	_FORCEINLINE friend vector4i operator+(const vector4i &a, const vector4i &b) {vector4i c; vecFunctions.V4IAdd((void *)&a,(void *)&b,&c); return c;}
	/// Addition of integer vectors
	_FORCEINLINE friend vector4i operator+(vector4i &a, vector4i &b) {vector4i c; vecFunctions.V4IAdd(&a,&b,&c); return c;}
	/// Subtraction of integer vectors
	_FORCEINLINE friend vector4i operator-(vector4i &a, vector4i &b) {vector4i c; vecFunctions.V4ISub(&a,&b,&c); return c;}
	/// Scaling integer vector
	_FORCEINLINE const vector4i operator*(const float &b) {vector4i c; vecFunctions.V4IScale((void*)this,(void*)&c,b); return c;}
	/// Scaling integer vector
	_FORCEINLINE friend vector4i operator*(const vector4i &a, const float &b) {vector4i c; vecFunctions.V4IScale((void*)&a,&c,b); return c;}
	/// Scaling integer vector
	_FORCEINLINE friend vector4i operator*(const float &b,const vector4i &a) {vector4i c; vecFunctions.V4IScale((void*)&a,&c,b); return c;}
	/// Scaling integer vector
	_FORCEINLINE friend vector4i operator*(vector4i &a, float &b) {vector4i c; vecFunctions.V4IScale(&a,&c,b); return c;}
	/// Scaling integer vector
	_FORCEINLINE friend vector4i operator*(float &b, vector4i &a) {vector4i c; vecFunctions.V4IScale(&a,&c,b); return c;}

	_FORCEINLINE friend vector4i operator*(vector4i &a, vector4i &b) {vector4i c; vecFunctions.V4IMul(&a,&b,&c); return c;}

	_FORCEINLINE const vector4i &operator=(const vector4i& b) {vecFunctions.V4R32Copy((void*)&b,(void*)this); return *this;}

	/// Field reference as to the elements of the array.
	_FORCEINLINE _int32 &operator[](unsigned int id) const {
		return ((_int32*)this)[id];
	}

	BT_API TYPEINFO_H;
};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* VECTOR4I_H_ */
