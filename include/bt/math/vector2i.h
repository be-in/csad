/*
 * vector2i.h
 *
 *  Created on: 28.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef VECTOR2I_H_
#define VECTOR2I_H_

#include <bt/functions.h>

namespace bt {

WARNING_DISABLE;
OPTIMIZE_ON;

class vector2l;
class vector2f;
class vector3f;
class vector2d;

/**
 * @class vector2i
 *
 * @ingroup math
 * @brief vector2i - two-dimensional integer vector.
 *
 * @see vector4i, vector3i math
 */

class vector2i {
public:
	/// Параметр оси X
	_int32 x;
	/// Параметр оси Y
	_int32 y;

	/// The constructor does not set the initial values to the fields.
	_FORCEINLINE vector2i() {}
	/// Конструктор, задает все параметры равными одному значению.
	_FORCEINLINE vector2i(_int32 _a) {x=y=_a;}
	/// Конструктор.
	/// @param _x - vector x
	/// @param _y - vector y
	_FORCEINLINE vector2i(_int32 _x,_int32 _y) {x=_x;y=_y;}
	/// Преобразование вектора в формате с плавающей точкой в целочисленный
	_FORCEINLINE vector2i(vector2f*_a) {vecFunctions.V2FTo2I((void*)_a,(void*)this);}
	_FORCEINLINE vector2i(vector3f*_a) {vecFunctions.V2FTo2I((void*)_a,(void*)this);}
	_FORCEINLINE vector2i(vector2d*_a) {vecFunctions.V2DTo2I((void*)_a,(void*)this);}
	_FORCEINLINE ~vector2i() {}

	_FORCEINLINE bool less(const vector2i &b) {if (y!=b.y) return y<b.y; return x<b.x;}
	/// The position of a point on a straight line passing through a b.
	_FORCEINLINE bool leftOfLine(const vector2i &a,const vector2i &b) {return vecFunctions.V2IQDFL(this,(void*)&a,(void*)&b)<0;}
	/// The square of the distance from a point to a straight line passing through a b.
	_FORCEINLINE _int32 quadDistanceFromLine(const vector2i &a,const vector2i &b) {return vecFunctions.V2IQDFL(this,(void*)&a,(void*)&b);}
	/// Vector length squared.
	_FORCEINLINE _int32 sqrLen() {return vecFunctions.V2ILength2(this);}
	/// Sets the value of the fields to zero.
	_FORCEINLINE void zero() {x=y=0;}
	
	/// Addition of vectors
	_FORCEINLINE const vector2i operator+(const vector2i &a) const {vector2i c; vecFunctions.V2IAdd((void*)this,(void*)&a,&c); return c;}
	/// Addition of vectors
	_FORCEINLINE friend vector2i operator+(const vector2i &a, const vector2i &b) {vector2i c; vecFunctions.V2IAdd((void *)&a,(void *)&b,&c); return c;}
	/// Addition of vectors
	_FORCEINLINE friend vector2i operator+(vector2i &a, vector2i &b) {vector2i c; vecFunctions.V2IAdd((void *)&a,(void *)&b,(void *)&c); return c;}
	/// Addition of vectors
	_FORCEINLINE const vector2i &operator+=(const vector2i &a) {vecFunctions.V2IAdd((void*)this,(void*)&a,(void*)this); return *this;}
	/// Addition of vectors
	_FORCEINLINE friend vector2i &operator+=(vector2i &a,vector2i &b) {vecFunctions.V2IAdd(&a,&b,&a); return a;}
	/// Subtraction of vectors
	_FORCEINLINE const vector2i operator-(const vector2i &a) const {vector2i c; vecFunctions.V2ISub((void*)this,(void*)&a,&c); return c;}
	/// Subtraction of vectors
	_FORCEINLINE friend vector2i operator-(vector2i &a, vector2i &b) {vector2i c; vecFunctions.V2ISub(&a,&b,&c); return c;}
	/// Subtraction of vectors
	_FORCEINLINE const vector2i &operator-=(const vector2i &a) {vecFunctions.V2ISub((void*)this,(void*)&a,(void*)this); return *this;}
	/// Subtraction of vectors
	_FORCEINLINE friend vector2i &operator-=(vector2i &a,vector2i &b) {vecFunctions.V2ISub(&a,&b,&a); return a;}
	/// Scaling vector
	_FORCEINLINE const vector2i operator*(const float &b) {vector2i c; vecFunctions.V2IScale((void*)this,&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE const vector2i operator*(const _int32 &b) {vector2i c; vecFunctions.V2IScale((void*)this,&c,(float)b); return c;}
	/// Scaling vector
	_FORCEINLINE friend vector2i operator*(vector2i &a, _int32 &b) {vector2i c; vecFunctions.V2IScale(&a,&c,(float)b); return c;}
	/// Scaling vector
	_FORCEINLINE friend vector2i operator*(_int32 &b, vector2i &a) {vector2i c; vecFunctions.V2IScale(&a,&c,(float)b); return c;}
	//_FORCEINLINE vector2i operator=(const vector2d &b) {return vector2i(&b);}
	_FORCEINLINE bool operator==(vector2i b) {if (x!=b.x) return false; return y==b.y;}
	_FORCEINLINE bool operator!=(vector2i b) {if (x!=b.x) return true; return y!=b.y;}

	/// Accessing parameters as array elements
	_FORCEINLINE _int32 &operator[](unsigned int id) const {
		return ((_int32*)this)[id];
	}

	BT_API TYPEINFO_H;
};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* VECTOR2I_H_ */
