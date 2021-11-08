/*
 * vector2f.h
 *
 *  Created on: 29.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef VECTOR2F_H_
#define VECTOR2F_H_

#include <bt/functions.h>

namespace bt {

WARNING_DISABLE;
OPTIMIZE_ON;

class vector2i;
class vector3f;
class vector4f;
class vector2d;
class vector3d;
class quaternionf;

/**
 * @class vector2f
 *
 * @ingroup math
 * @brief vector2f - two-dimensional single precision vector
 *
 * @see vector2d, vector3f, vector3d, vector4f, vector4d, math
 */

class vector2f {
public:
	/// Параметр оси X
	float x;
	/// Параметр оси Y
	float y;

	/// The constructor does not set the initial values to the fields.
	_FORCEINLINE vector2f() {}
	/// Конструктор, задает все параметры равными одному значению.
	_FORCEINLINE vector2f(float _a) {x=y=_a;}
	/// Конструктор.
	/// @param _x - vector x
	/// @param _y - vector y
	_FORCEINLINE vector2f(float _x,float _y): x(_x), y(_y) {}
	_FORCEINLINE vector2f(const vector2i& _a) {vecFunctions.V2ITo2F((void*)&_a,(void*)this);}
	_FORCEINLINE vector2f(const vector3f& _a) {float *c=(float*)&_a;x=c[0];y=c[1];}
	_FORCEINLINE vector2f(const vector4f& _a) {float *c=(float*)&_a;x=c[0];y=c[1];}
	_FORCEINLINE vector2f(vector2i &_a) {vecFunctions.V2ITo2F((void*)&_a,(void*)this);}
	_FORCEINLINE vector2f(const vector2d &_a) {vecFunctions.V2DTo2F((void*)&_a,(void*)this);}
	_FORCEINLINE vector2f(const vector3d &_a) {vecFunctions.V2DTo2F((void*)&_a,(void*)this);}
	_FORCEINLINE vector2f(vector2d &_a) {vecFunctions.V2DTo2F((void*)&_a,(void*)this);}
	_FORCEINLINE vector2f(vector2d *_a) {vecFunctions.V2DTo2F((void*)_a,(void*)this);}
	_FORCEINLINE vector2f(vector3d *_a) {vecFunctions.V2DTo2F((void*)_a,(void*)this);}
	_FORCEINLINE ~vector2f() {}

	/// The appeal of the sign of the vector.
	_FORCEINLINE void neg() {vecFunctions.V2FInv(this,this);}

	_FORCEINLINE bool less(const vector2f &b) {if (y!=b.y) return y<b.y; return x<b.x;}
	/// The position of a point on a straight line passing through a b.
	_FORCEINLINE bool leftOfLine(const vector2f &a,const vector2f &b) {return vecFunctions.V2FQDFL(this,(void*)&a,(void*)&b)<0;}
	/// The square of the distance from a point to a straight line passing through a b.
	_FORCEINLINE float quadDistanceFromLine(const vector2f &a,const vector2f &b) {return vecFunctions.V2FQDFL(this,(void*)&a,(void*)&b);}
	/// Vector length squared.
	_FORCEINLINE float sqrLen() {return vecFunctions.V2FLength2(&x);}
	/// Converts the vector to a unit length.
	_FORCEINLINE const vector2f norm() {vector2f c; vecFunctions.V2FNormal(&x,&c); return c;}
	/// Scales the vector.
	_FORCEINLINE void scale(float a) {vecFunctions.V2FScale(this,this,a);}
	/// Scales the vector to a unit length.
	_FORCEINLINE void normalize() {vecFunctions.V2FNormal(this,this);}
	/// The vector interpolation between a and b, с[0.0 .. 1.0].
	_FORCEINLINE void lerp(vector2f &a,vector2f &b,float c) {vecFunctions.V2FLerp(&a,&b,this,c);}
	/// Масштобирование и сложение векторов по формуле a * c + b * d
	_FORCEINLINE void combine(vector2f &a,vector2f &b,float c,float d) {vecFunctions.V2FCombine(&a,&b,this,c,d);}
	/// The reflection vector.
	_FORCEINLINE vector2f reflect(vector2f &a) {vector2f c; vecFunctions.V2FReflect(this,&a,&c); return c;}
	/// Sets the value of the fields to zero.
	_FORCEINLINE void zero() {x=0;y=0;}
	/// Dot product.
	_FORCEINLINE float dot(vector2f &a) {return vecFunctions.V2FDot(&x,&a);}
	/// The angle between the vectors.
	_FORCEINLINE float angle(vector2f &b) {return vecFunctions.V2FAngle((void*)this,&b);}

	/// Addition of vectors
	_FORCEINLINE const vector2f operator+(const vector2f &a) {vector2f c; vecFunctions.V2FAdd(this,(void*)&a,&c); return c;}
	/// Addition of vectors
	_FORCEINLINE friend vector2f operator+(const vector2f &a, const vector2f &b) {vector2f c; vecFunctions.V2FAdd((void*)&a,(void*)&b,&c); return c;}
	/// Addition of vectors
	_FORCEINLINE friend vector2f operator+(vector2f &a, vector2f &b) {vector2f c; vecFunctions.V2FAdd(&a,&b,&c); return c;}
	/// Addition of vectors
	_FORCEINLINE const vector2f &operator+=(const vector2f &a) {vecFunctions.V2FAdd((void*)this,(void*)&a,(void*)this); return *this;}
	/// Addition of vectors
	_FORCEINLINE friend vector2f operator+=(vector2f &a,vector2f &b) {vecFunctions.V2FAdd(&a,&b,&a); return a;}
	/// Subtraction of vectors
	_FORCEINLINE const vector2f operator-(const vector2f &a) {vector2f c; vecFunctions.V2FSub(this,(void*)&a,&c); return c;}
	/// Subtraction of vectors
	_FORCEINLINE friend vector2f operator-(const vector2f &a, const vector2f &b) {vector2f c; vecFunctions.V2FSub((void*)&a,(void*)&b,&c); return c;}
	/// Subtraction of vectors
	_FORCEINLINE friend vector2f operator-(vector2f &a, vector2f &b) {vector2f c; vecFunctions.V2FSub(&a,&b,&c); return c;}
	/// Subtraction of vectors
	_FORCEINLINE const vector2f &operator-=(const vector2f &a) {vecFunctions.V2FSub((void*)this,(void*)&a,(void*)this); return *this;}
	/// Subtraction of vectors
	_FORCEINLINE friend vector2f operator-=(vector2f &a,vector2f &b) {vecFunctions.V2FSub(&a,&b,&a); return a;}
	/// Transforming a vector by a quaternion.
	_FORCEINLINE const vector2f operator*(const quaternionf &b) {vector2f c; vecFunctions.Q2FInvTransform((void *)&b,this,&c); return c;}
	/// Transforming a vector by a quaternion.
	_FORCEINLINE friend vector2f operator*(const vector2f &a,const quaternionf &b) {vector2f c; vecFunctions.Q2FInvTransform((void *)&b,(void *)&a,&c); return c;}
	/// Scaling vector
	_FORCEINLINE const vector2f operator*(const float &b) {vector2f c; vecFunctions.V2FScale((void*)this,&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE friend vector2f operator*(const vector2f &a, const float &b) {vector2f c; vecFunctions.V2FScale((void*)&a,&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE friend vector2f operator*(const float &b, const vector2f &a) {vector2f c; vecFunctions.V2FScale((void*)&a,&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE friend vector2f operator*(vector2f &a, float &b) {vector2f c; vecFunctions.V2FScale(&a,&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE friend vector2f operator*(float &b, vector2f &a) {vector2f c; vecFunctions.V2FScale(&a,&c,b); return c;}

	_FORCEINLINE bool operator==(vector2f b) {if (x!=b.x) return false; return y==b.y;}
	_FORCEINLINE bool operator!=(vector2f b) {if (x!=b.x) return true; return y!=b.y;}

	/// Accessing parameters as array elements.
	_FORCEINLINE float &operator[](unsigned int id) const {
		return ((float*)this)[id];
	}

	BT_API TYPEINFO_H;
};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* VECTOR2F_H_ */
