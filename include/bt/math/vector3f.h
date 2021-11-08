/*
 * vector3f.h
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef VECTOR3F_H_
#define VECTOR3F_H_

#include <bt/functions.h>

namespace bt {

WARNING_DISABLE;
OPTIMIZE_ON;

class vector2f;
class vector4f;
class vector3d;

/**
 * @class vector3f
 *
 * @ingroup math
 * @brief vector3f - three-dimensional vector with single precision.
 *
 * @see vector3d, vector2f, vector2d, vector4f, vector4d, math
 */

class vector3f {
public:
	/// Параметр оси X
	float x;
	/// Параметр оси Y
	float y;
	/// Параметр оси Z
	float z;

	/// The constructor does not set the initial values to the fields.
	_FORCEINLINE vector3f() {}
	/// Constructor, sets all parameters equal to one value.
	_FORCEINLINE vector3f(float a) {x=y=z=a;}
	/// @param _x - vector x
	/// @param _y - vector y
	/// @param _z - vector z
	_FORCEINLINE vector3f(float _x,float _y,float _z) {x=_x;y=_y;z=_z;}
	_FORCEINLINE vector3f(float* _a) {vecFunctions.V3R32Copy((void*)_a,(void*)this);}
	_FORCEINLINE vector3f(vector2f& _a) {float *c=(float*)&_a;x=c[0];y=c[1];z=0;}
	_FORCEINLINE vector3f(vector2f* _a) {float *c=(float*)&_a;x=c[0];y=c[1];z=0;}
	_FORCEINLINE vector3f(const vector3f& _a) {vecFunctions.V3R32Copy((void*)&_a,(void*)this);}
	_FORCEINLINE vector3f(vector3f& _a) {vecFunctions.V3R32Copy((void*)&_a,(void*)this);}
	_FORCEINLINE vector3f(vector3f* _a) {vecFunctions.V3R32Copy((void*)_a,(void*)this);}
	_FORCEINLINE vector3f(const vector4f& _a) {float *c=(float*)&_a;x=c[0];y=c[1];z=c[2];}
	/// Converting the integer vector in floating-point format
	_FORCEINLINE vector3f(vector3i &_a) {vecFunctions.V3ITo3F((void*)&_a,(void*)this);}
	_FORCEINLINE vector3f(const vector3d &_a) {vecFunctions.V3DTo3F((void*)&_a,(void*)this);}
	_FORCEINLINE vector3f(vector3d &_a) {vecFunctions.V3DTo3F((void*)&_a,(void*)this);}
	_FORCEINLINE vector3f(vector3d *_a) {vecFunctions.V3DTo3F((void*)_a,(void*)this);}
	_FORCEINLINE ~vector3f() {}

	/// The appeal of the sign of the vector.
	_FORCEINLINE void neg() {vecFunctions.V3FInv(this,this);}
	/// Transforms itself in the absolute value of the vector.
	_FORCEINLINE void abs() {vecFunctions.V3FAbs(this,this);}
	/// Addition of vectors
	_FORCEINLINE void add(vector3f &a,vector3f &b) {vecFunctions.V3FAdd((void*)&a,(void*)&b,(void*)this);}
	/// Subtraction of vectors
	_FORCEINLINE void sub(vector3f &a,vector3f &b) {vecFunctions.V3FSub((void*)&a,(void*)&b,(void*)this);}
	/// Vector length squared.
	_FORCEINLINE float sqrLen() {return vecFunctions.V3FLength2(this);}
	/// Converts the vector to a unit length.
	_FORCEINLINE const vector3f norm() {vector3f c; vecFunctions.V3FNormal(this,&c); return c;}
	/// Scales the vector.
	_FORCEINLINE void scale(float a) {vecFunctions.V3FScale(this,this,a);}
	/// Scales the vector to a unit length.
	_FORCEINLINE void normalize() {vecFunctions.V3FNormal(this,this);}
	/// The vector interpolation between a and b, с[0.0 .. 1.0].
	_FORCEINLINE void lerp(vector3f &a,vector3f &b,float c) {vecFunctions.V3FLerp(&a,&b,this,c);}
	/// Scaling and addition of vectors by the formula a * c + b * d
	_FORCEINLINE void combine(vector3f &a,vector3f &b,float c,float d) {vecFunctions.V3FCombine(&a,&b,this,c,d);}
	/// The reflection vector.
	_FORCEINLINE void reflect(vector3f &a) {vecFunctions.V3FReflect(this,&a,this);}
//	_FORCEINLINE void min() {}
//	_FORCEINLINE void max() {}
	/// Sets the value of the fields to zero.
	_FORCEINLINE void zero() {x=y=z=0;}
	/// Dot product.
	_FORCEINLINE float dot(vector3f &a) {return vecFunctions.V3FDot(this,&a);}
	/// Cross product.
	_FORCEINLINE vector3f cross(vector3f &a) {vector3f c; vecFunctions.V3FCross(this,&a,&c); return c;}
	/// Cross product.
	_FORCEINLINE void cross(vector3f &a,vector3f &b) {vecFunctions.V3FCross(&a,&b,this);}
	/// The angle between the vectors.
	_FORCEINLINE float angle(vector3d &b) {return vecFunctions.V3FAngle((void*)this,&b);}

	/// Addition of vectors
	_FORCEINLINE const vector3f operator+(const vector3f &a) {vector3f c; vecFunctions.V3FAdd((void*)&x,(void*)&a,&c); return c;}
	/// Addition of vectors
	_FORCEINLINE friend vector3f operator+(const vector3f &a, const vector3f &b) {vector3f c; vecFunctions.V3FAdd((void*)&a,(void*)&b,&c); return c;}
	/// Addition of vectors
	_FORCEINLINE friend vector3f operator+(vector3f &a, vector3f &b) {vector3f c; vecFunctions.V3FAdd(&a,&b,&c); return c;}
	/// Addition of vectors
	_FORCEINLINE const vector3f &operator+=(const vector3f &a) {vecFunctions.V3FAdd((void*)this,(void*)&a,(void*)this); return *this;}
	/// Addition of vectors
	_FORCEINLINE friend vector3f &operator+=(vector3f &a,vector3f &b) {vecFunctions.V3FAdd(&a,&b,&a); return a;}
	/// Subtraction of vectors
	_FORCEINLINE const vector3f operator-(const vector3f &a) {vector3f c; vecFunctions.V3FSub((void*)this,(void*)&a,&c); return c;}
	/// Subtraction of vectors
	_FORCEINLINE friend vector3f operator-(const vector3f &a, const vector3f &b) {vector3f c; vecFunctions.V3FSub((void*)&a,(void*)&b,&c); return c;}
	/// Subtraction of vectors
	_FORCEINLINE friend vector3f operator-(vector3f &a, vector3f &b) {vector3f c; vecFunctions.V3FSub(&a,&b,&c); return c;}
	/// Subtraction of vectors
	_FORCEINLINE const vector3f &operator-=(const vector3f &a) {vecFunctions.V3FSub((void*)this,(void*)&a,(void*)this); return *this;}
	/// Subtraction of vectors
	_FORCEINLINE friend vector3f &operator-=(vector3f &a,vector3f &b) {vecFunctions.V3FSub(&a,&b,&a); return a;}
	/// Scaling vector
	_FORCEINLINE const vector3f operator*(const float &b) {vector3f c; vecFunctions.V3FScale((void*)this,(void*)&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE friend vector3f operator*(const vector3f &a, const float &b) {vector3f c; vecFunctions.V3FScale((void*)&a,&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE friend vector3f operator*(const float &b,const vector3f &a) {vector3f c; vecFunctions.V3FScale((void*)&a,&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE friend vector3f operator*(vector3f &a, float &b) {vector3f c; vecFunctions.V3FScale(&a,&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE friend vector3f operator*(float &b, vector3f &a) {vector3f c; vecFunctions.V3FScale(&a,&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE const vector3f operator*=(const float &b) {vecFunctions.V3FScale((void*)this,(void*)this,b); return (*this);}
	/// Scaling vector
	_FORCEINLINE const vector3f operator*=(float &b) {vecFunctions.V3FScale((void*)this,(void*)this,b); return (*this);}
	/// Transforming a vector by a quaternion.
	_FORCEINLINE const vector3f operator*(const quaternionf &b) {vector2f c; vecFunctions.Q3FInvTransform((void *)&b,this,&c); return c;}
	/// Transforming a vector by a quaternion.
	_FORCEINLINE friend vector3f operator*(const vector3f &a,const quaternionf &b) {vector3f c; vecFunctions.Q3FInvTransform((void *)&b,(void *)&a,&c); return c;}
	/// Element-by-element multiplication of vectors.
	_FORCEINLINE const vector3f operator*(const vector3f &a) {vector3f c; vecFunctions.V3FMul((void*)this,(void*)&a,&c); return c;}
	/// Element-by-element multiplication of vectors.
	_FORCEINLINE friend vector3f operator*(vector3f &a, vector3f &b) {vector3f c; vecFunctions.V3FMul(&a,&b,&c); return c;}
	/// Element-by-element division of vectors.
	_FORCEINLINE const vector3f operator/(const vector3f &a) {vector3f c; vecFunctions.V3FDiv((void*)this,(void*)&a,&c); return c;}
	/// Element-by-element division of vectors.
	_FORCEINLINE friend vector3f operator/(vector3f &a, vector3f &b) {vector3f c; vecFunctions.V3FDiv(&a,&b,&c); return c;}
	/// Dot product of the vectors.
	_FORCEINLINE const float operator|(vector3f &a) {return vecFunctions.V3FDot((void*)this,(void*)&a);}
	/// Dot product of the vectors.
	_FORCEINLINE friend float operator|(vector3f &a, vector3f &b) {return vecFunctions.V3FDot(&a,&b);}
	/// Cross product of the vectors.
	_FORCEINLINE friend vector3f operator&(const vector3f &a, const vector3f &b) {vector3f c; vecFunctions.V3FCross((void *)&a,(void *)&b,(void *)&c); return c;}
	_FORCEINLINE vector3f &operator=(const vector3f &b) {vecFunctions.V3R32Copy((void*)&b,(void*)this); return *this;}
	//_FORCEINLINE vector3f &operator=(_vector3d &b) {x=(float)b.x;y=(float)b.y;z=(float)b.z; return *this;}

	_FORCEINLINE bool operator==(vector3f b) {if (x!=b.x) return false; if (y!=b.y) return false; return z==b.z;}
	_FORCEINLINE bool operator!=(vector3f b) {if (x!=b.x) return true; if (y!=b.y) return true; return z!=b.z;}

	/// Field reference as to the elements of the array.
	_FORCEINLINE float &operator[](unsigned int id) const {
		return ((float*)this)[id];
	}

	/// Static identifier type vector3f::t()
	BT_API TYPEINFO_H;

};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* VECTOR3F_H_ */
