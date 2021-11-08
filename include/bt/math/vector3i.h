/*
 * vector3i.h
 *
 *  Created on: 30.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef VECTOR3I_H_
#define VECTOR3I_H_

#include <bt/functions.h>

namespace bt {

WARNING_DISABLE;
OPTIMIZE_ON;

class vector3l;
class vector3f;
class vector3d;
class vector4f;

/**
 * @class vector3i
 *
 * @ingroup math
 * @brief vector3i - three-dimensional integer vector.
 *
 * @see vector4i, vector2i math
 */

class vector3i {
public:
	_int32 x;
	_int32 y;
	_int32 z;

	/// The constructor does not set the initial values to the fields.
	_FORCEINLINE vector3i() {}
	///  онструктор, задает все параметры равными одному значению.
	_FORCEINLINE vector3i(_int32 a) {x=y=z=a;}
	///  онструктор.
	/// @param _x - vector x
	/// @param _y - vector y
	/// @param _z - vector z
	_FORCEINLINE vector3i(_int32 _x,_int32 _y,_int32 _z) {x=_x;y=_y;z=_z;}
	/// ѕреобразование вектора в формате с плавающей точкой в целочисленный
	_FORCEINLINE vector3i(vector3f*_a) {vecFunctions.V3FTo3I((void*)_a,(void*)this);}
	_FORCEINLINE vector3i(vector3d*_a) {vecFunctions.V3DTo3I((void*)_a,(void*)this);}
	_FORCEINLINE vector3i(vector4f*_a) {vecFunctions.V3FTo3I((void*)_a,(void*)this);}
	_FORCEINLINE ~vector3i() {}

	/// Sets the value of the fields to zero.
	_FORCEINLINE void zero() {x=y=z=0;}

	/// Addition of vectors
	_FORCEINLINE const vector3i operator+(const vector3i &a) const {vector3i c; vecFunctions.V3IAdd((void*)this,(void*)&a,&c); return c;}
	/// Addition of vectors
	_FORCEINLINE friend vector3i operator+(vector3i &a, vector3i &b) {vector3i c; vecFunctions.V3IAdd(&a,&b,&c); return c;}
	/// Addition of vectors
	_FORCEINLINE const vector3i &operator+=(const vector3i &a) {vecFunctions.V3IAdd((void*)this,(void*)&a,(void*)this); return *this;}
	/// Addition of vectors
	_FORCEINLINE friend vector3i &operator+=(vector3i &a,vector3i &b) {vecFunctions.V3IAdd(&a,&b,&a); return a;}
	/// Subtraction of vectors
	_FORCEINLINE const vector3i operator-(const vector3i &a) const {vector3i c; vecFunctions.V3ISub((void*)this,(void*)&a,&c); return c;}
	/// Subtraction of vectors
	_FORCEINLINE friend vector3i operator-(vector3i &a, vector3i &b) {vector3i c; vecFunctions.V3ISub(&a,&b,&c); return c;}
	/// Subtraction of vectors
	_FORCEINLINE const vector3i &operator-=(const vector3i &a) {vecFunctions.V3ISub((void*)this,(void*)&a,(void*)this); return *this;}
	/// Subtraction of vectors
	_FORCEINLINE friend vector3i &operator-=(vector3i &a,vector3i &b) {vecFunctions.V3ISub(&a,&b,&a); return a;}
	/// Scaling vector
	_FORCEINLINE friend vector3i operator*(vector3i &a, double &b) {vector3i c; vecFunctions.V3IScale(&a,&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE friend vector3i operator*(double &b, vector3i &a) {vector3i c; vecFunctions.V3IScale(&a,&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE friend vector3i operator*(vector3i &a, const double &b) {vector3i c; vecFunctions.V3IScale(&a,&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE friend vector3i operator*(const double &b, vector3i &a) {vector3i c; vecFunctions.V3IScale(&a,&c,b); return c;}
	/// Element-by-element multiplication of vectors.
	_FORCEINLINE friend vector3i operator*(vector3i &a, vector3i &b) {vector3i c; vecFunctions.V3IMul(&a,&b,&c); return c;}

	_FORCEINLINE const vector3i &operator=(const vector3i& b) {vecFunctions.V3R32Copy((void*)&b,(void*)this); return *this;}

	_FORCEINLINE bool operator==(vector3i b) {if (x!=b.x) return false; if (y!=b.y) return false; return z==b.z;}
	_FORCEINLINE bool operator!=(vector3i b) {if (x!=b.x) return true; if (y!=b.y) return false; return z!=b.z;}

	/// Accessing parameters as array elements
	_FORCEINLINE _int32 &operator[](unsigned int id) const {
		return ((_int32*)this)[id];
	}

	BT_API TYPEINFO_H;
};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* VECTOR3I_H_ */
