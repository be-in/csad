/*
 * depvector4f.h
 *
 *  Created on: 19.08.2013
 *      Author: Пантелеймонов Александр
 */

#ifndef DEPVECTOR4F_H_
#define DEPVECTOR4F_H_

#include <bt/functions.h>

namespace bt {

class vector2f;
class vector4d;

/**
 * @class depVector4f
 *
 * @ingroup math
 * @brief depVector4f - четырехмерный вектор одинарной точности c плавающей точкой, архитектурно зависим.
 *
 * @see math
 */

class depVector4f {
public:
	float x;
	float y;
	float z;
	float w;

	_FORCEINLINE depVector4f() {}
	_FORCEINLINE depVector4f(float _a) {x=y=z=w=_a;}
	_FORCEINLINE depVector4f(float *_a) {x=_a[0];y=_a[1];z=_a[2];w=_a[3];}
	_FORCEINLINE depVector4f(float _x,float _y,float _z,float _w) {x=_x;y=_y;z=_z;w=_w;}

	_FORCEINLINE ~depVector4f() {}

	_FORCEINLINE float sqrLen() {return x*x+y*y+z*z+w*w;}
/*	_FORCEINLINE const vector4f norm() {vector4f c; vecFunctions.V4FNormal(this,&c); return c;}
	/// Интерполяция вектора между a и b, с[0.0 .. 1.0].
	_FORCEINLINE void lerp(vector4f &a,vector4f &b,float c) {vecFunctions.V4FLerp(&a,&b,this,c);}
	/// Обнуляет вектор
	_FORCEINLINE void zero() {x=y=z=w=0;}
	/// Скалярное произведение
	_FORCEINLINE float dot(vector4f &a) {return vecFunctions.V4FDot(this,&a);}

	_FORCEINLINE const vector4f operator+(const vector4f &a) {vector4f c; vecFunctions.V4FAdd((void*)this,(void*)&a,&c); return c;}
	_FORCEINLINE friend const vector4f operator+(const vector4f &a, const vector4f &b) {vector4f c; vecFunctions.V4FAdd((void*)&a,(void*)&b,&c); return c;}
	_FORCEINLINE friend const vector4f operator+(vector4f &a, vector4f &b) {vector4f c; vecFunctions.V4FAdd(&a,&b,&c); return c;}
	_FORCEINLINE const vector4f operator+=(const vector4f &a) {vecFunctions.V4FAdd((void*)this,(void*)&a,(void*)this); return *this;}
	_FORCEINLINE friend const vector4f operator+=(vector4f &a,vector4f &b) {vecFunctions.V4FAdd(&a,&b,&a); return a;}
	_FORCEINLINE const vector4f operator-(const vector4f &a) {vector4f c; vecFunctions.V4FSub((void*)this,(void*)&a,&c); return c;}
	_FORCEINLINE friend const vector4f operator-(vector4f &a, vector4f &b) {vector4f c; vecFunctions.V4FSub(&a,&b,&c); return c;}
	_FORCEINLINE friend const vector4f operator*(vector4f &a, float &b) {vector4f c; vecFunctions.V4FScale(&a,&c,b); return c;}
	_FORCEINLINE friend const vector4f operator*(float &b, vector4f &a) {vector4f c; vecFunctions.V4FScale(&a,&c,b); return c;}
	_FORCEINLINE const vector4f operator*(const vector4f &a) {vector4f c; vecFunctions.V4FMul((void*)this,(void*)&a,&c); return c;}
	_FORCEINLINE friend const vector4f operator*(vector4f &a, vector4f &b) {vector4f c; vecFunctions.V4FMul(&a,&b,&c); return c;}
	_FORCEINLINE friend const vector4f operator/(vector4f &a, vector4f &b) {vector4f c; c.x=a.x/b.x;c.y=a.y/b.y;c.z=a.z/b.z;c.z=a.w/b.w; return c;}
	_FORCEINLINE friend const double operator|(vector4f &a, vector4f &b) {return vecFunctions.V4FDot(&a,&b);}
	_FORCEINLINE friend vector4f operator&(const vector4f &a, const vector4f &b) {vector4f c; vecFunctions.V3FCross((void *)&a,(void *)&b,(void *)&c); return c;}
	_FORCEINLINE const vector4f &operator=(const vector4f &b) {x=b.x;y=b.y;z=b.z;w=b.w; return *this;}

	_FORCEINLINE float &operator[](unsigned int id) const {
		return ((float*)this)[id];
	}*/
};

}

#endif /* DEPVECTOR4F_H_ */
