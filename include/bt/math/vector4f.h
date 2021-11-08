/*
 * vector4f.h
 *
 *  Created on: 19.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef VECTOR4F_H_
#define VECTOR4F_H_

#include <bt/functions.h>

namespace bt {

WARNING_DISABLE;
OPTIMIZE_ON;

class vector2f;
class vector3f;
class vector3d;
class vector4i;
class vector4d;

/**
 * @class vector4f
 *
 * @ingroup math
 * @brief vector4f - four-dimensional single precision vector
 *
 * При обьявлении переменной типа vector4f, значения полей не определены:
 * vector4f vec1;
 *
 * Можно обращатся к параметрам как к полям структуры:
 * vec1.x=300.0f;
 * vec1.y=123.0f;
 * vec1.z=0.01f;
 * vec1.w=1.0f;
 *
 * Можно обращатся к параметрам как к массиву:
 * vec1[0]=300.0f;
 * vec1[1]=123.0f;
 * vec1[2]=0.01f;
 * vec1[3]=1.0f;
 *
 * @see vector4d, vector2f, vector2d, vector3f, vector3d, math
 */

class vector4f {
public:
	/// Параметр оси X
	float x;
	/// Параметр оси Y
	float y;
	/// Параметр оси Z
	float z;
	/// Параметр оси W
	float w;

	/// The constructor does not set the initial values to the fields.
	_FORCEINLINE vector4f() {}
	/// Конструктор, задает все параметры равными одному значению.
	_FORCEINLINE vector4f(float _a) {x=y=z=w=_a;}
	_FORCEINLINE vector4f(float *_a) {x=_a[0];y=_a[1];z=_a[2];w=_a[3];}
	/// Конструктор.
	/// @param _x - vector x
	/// @param _y - vector y
	/// @param _z - vector z
	/// @param _w - vector w
	_FORCEINLINE vector4f(float _x,float _y,float _z,float _w) {x=_x;y=_y;z=_z;w=_w;}
	_FORCEINLINE vector4f(vector2f &_a) {float *c=(float*)&_a;x=c[0];y=c[1];}
	_FORCEINLINE vector4f(const vector2f &_a) {float *c=(float*)&_a;x=c[0];y=c[1];}
	_FORCEINLINE vector4f(vector4i &_a) {vecFunctions.V4ITo4F((void*)&_a,(void*)this);}
	_FORCEINLINE vector4f(vector3f &_a) {vecFunctions.V3R32Copy((void*)&_a,(void*)this);}
	_FORCEINLINE vector4f(vector3f *_a) {vecFunctions.V3R32Copy((void*)_a,(void*)this);}
	_FORCEINLINE vector4f(vector3d *_a) {vecFunctions.V3DTo3F((void*)_a,(void*)this);}
	_FORCEINLINE vector4f(vector4d &_a) {vecFunctions.V4DTo4F((void*)&_a,(void*)this);}
	_FORCEINLINE vector4f(vector4d *_a) {vecFunctions.V4DTo4F((void*)_a,(void*)this);}
	_FORCEINLINE vector4f(quaternionf* _a) {vecFunctions.Q4FVector((void*)_a,(void*)this);}
	_FORCEINLINE ~vector4f() {}

	/// The appeal of the sign of the vector.
	_FORCEINLINE void neg() {vecFunctions.V4FInv(this,this);}
	/// Vector length squared.
	_FORCEINLINE float sqrLen() {return vecFunctions.V4FLength2(this);}
	/// Scales the vector to a unit length.
	_FORCEINLINE const vector4f norm() {vector4f c; vecFunctions.V4FNormal(this,&c); return c;}
	/// Scales the vector.
	_FORCEINLINE void scale(float a) {vecFunctions.V4FScale(this,this,a);}
	/// Scales the vector to a unit length.
	_FORCEINLINE void normalize() {vecFunctions.V4FNormal(this,this);}
	/// The vector interpolation between a and b, с[0.0 .. 1.0].
	_FORCEINLINE void lerp(vector4f &a,vector4f &b,float c) {vecFunctions.V4FLerp(&a,&b,this,c);}
	/// Scaling and addition of vectors by the formula a * c + b * d
	_FORCEINLINE void combine(vector4f &a,vector4f &b,float c,float d) {vecFunctions.V4FCombine(&a,&b,this,c,d);}
	/// Sets the value of the fields to zero.
	_FORCEINLINE void zero() {x=y=z=w=0;}
	/// Dot product.
	_FORCEINLINE float dot(vector4f &a) {return vecFunctions.V4FDot(this,&a);}

	/// Addition of vectors
	_FORCEINLINE const vector4f operator+(const vector4f &a) {vector4f c; vecFunctions.V4FAdd((void*)this,(void*)&a,&c); return c;}
	/// Addition of vectors
	_FORCEINLINE friend vector4f operator+(const vector4f &a, const vector4f &b) {vector4f c; vecFunctions.V4FAdd((void*)&a,(void*)&b,&c); return c;}
	/// Addition of vectors
	_FORCEINLINE friend vector4f operator+(vector4f &a, vector4f &b) {vector4f c; vecFunctions.V4FAdd(&a,&b,&c); return c;}
	/// Addition of vectors
	_FORCEINLINE const vector4f &operator+=(const vector4f &a) {vecFunctions.V4FAdd((void*)this,(void*)&a,(void*)this); return *this;}
	/// Addition of vectors
	_FORCEINLINE friend vector4f &operator+=(vector4f &a,vector4f &b) {vecFunctions.V4FAdd(&a,&b,&a); return a;}
	/// Subtraction of vectors
	_FORCEINLINE const vector4f operator-(const vector4f &a) {vector4f c; vecFunctions.V4FSub((void*)this,(void*)&a,&c); return c;}
	/// Subtraction of vectors
	_FORCEINLINE friend vector4f operator-(vector4f &a, vector4f &b) {vector4f c; vecFunctions.V4FSub(&a,&b,&c); return c;}
	/// Subtraction of vectors
	_FORCEINLINE const vector4f &operator-=(const vector4f &a) {vecFunctions.V4FSub((void*)this,(void*)&a,(void*)this); return *this;}
	/// Subtraction of vectors
	_FORCEINLINE friend vector4f &operator-=(vector4f &a,vector4f &b) {vecFunctions.V4FSub(&a,&b,&a); return a;}
	/// Scaling vector.
	_FORCEINLINE friend vector4f operator*(vector4f &a, float &b) {vector4f c; vecFunctions.V4FScale(&a,&c,b); return c;}
	/// Scaling vector.
	_FORCEINLINE friend vector4f operator*(float &b, vector4f &a) {vector4f c; vecFunctions.V4FScale(&a,&c,b); return c;}
	/// Element-by-element multiplication of vectors.
	_FORCEINLINE const vector4f operator*(const vector4f &a) {vector4f c; vecFunctions.V4FMul((void*)this,(void*)&a,&c); return c;}
	/// Element-by-element multiplication of vectors.
	_FORCEINLINE friend vector4f operator*(vector4f &a, vector4f &b) {vector4f c; vecFunctions.V4FMul(&a,&b,&c); return c;}
	/// Element-by-element division of vectors.
	_FORCEINLINE friend vector4f operator/(vector4f &a, vector4f &b) {vector4f c; vecFunctions.V4FDiv(&a,&b,&c); return c;}
	/// Dot product of the vectors.
	_FORCEINLINE const double operator|(vector4f& a) {return vecFunctions.V4FDot((void*)this,(void*)&a);}
	/// Dot product of the vectors.
	_FORCEINLINE friend double operator|(vector4f& a, vector4f& b) {return vecFunctions.V4FDot(&a,&b);}
	_FORCEINLINE friend vector4f operator&(const vector4f& a, const vector4f& b) {vector4f c; vecFunctions.V3FCross((void *)&a,(void *)&b,(void *)&c); return c;}
	_FORCEINLINE const vector4f &operator=(const vector4f& b) {vecFunctions.V4R32Copy((void*)&b,(void*)this); return *this;}

	_FORCEINLINE bool operator==(vector4f b) {if (x!=b.x) return false; if (y!=b.y) return false; if (z!=b.z) return false; return w==b.w;}

	/// Accessing parameters as array elements.
	_FORCEINLINE float &operator[](unsigned int id) const {
		return ((float*)this)[id];
	}

	/// Статический индентификатор типа vector4f::t()
	BT_API TYPEINFO_H;

};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* VECTOR4F_H_ */
