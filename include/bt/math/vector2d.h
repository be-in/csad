/*
 * vector2d.h
 *
 *  Created on: 29.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <bt/functions.h>

namespace bt {

WARNING_DISABLE;
OPTIMIZE_ON;

class vector2f;
class vector3f;

/**
 * @class vector2d
 *
 * @ingroup math
 * @brief vector2d - двухмерный вектор двойной точности
 *
 * @see vector2f, vector3f, vector3d, vector4f, vector4d, math
 */

class vector2d {
public:
	/// Параметр оси X
	double x;
	/// Параметр оси Y
	double y;

	/// The constructor does not set the initial values to the fields.
	_FORCEINLINE vector2d() {}
	/// Конструктор, задает все параметры равными одному значению.
	_FORCEINLINE vector2d(double _x) {x=y=_x;}
	/// Конструктор.
	/// @param _x - vector x
	/// @param _y - vector y
	_FORCEINLINE vector2d(double _x,double _y) {x=_x;y=_y;}
	_FORCEINLINE vector2d(vector2f &_a) {vecFunctions.V2FTo2D((void*)&_a,(void*)this);}
	_FORCEINLINE vector2d(vector2f *_a) {vecFunctions.V2FTo2D((void*)_a,(void*)this);}
	_FORCEINLINE vector2d(vector3f &_a) {vecFunctions.V2FTo2D((void*)&_a,(void*)this);}
	_FORCEINLINE ~vector2d() {}

	/// The appeal of the sign of the vector.
	_FORCEINLINE void neg() {vecFunctions.V2DInv(this,this);}

	_FORCEINLINE bool less(const vector2d &b) {if (y!=b.y) return y<b.y; return x<b.x;}
	/// The position of a point on a straight line passing through a b.
	_FORCEINLINE bool leftOfLine(const vector2d &a,const vector2d &b) {return vecFunctions.V2DQDFL(this,(void*)&a,(void*)&b)<0;}
	/// The square of the distance from a point to a straight line passing through a b.
	_FORCEINLINE double quadDistanceFromLine(const vector2d &a,const vector2d &b) {return vecFunctions.V2DQDFL(this,(void*)&a,(void*)&b);}
	/// Vector length squared.
	_FORCEINLINE double sqrLen() {return vecFunctions.V2DLength2(&x);}
	/// Converts the vector to a unit length.
	_FORCEINLINE const vector2d norm() {vector2d c; vecFunctions.V2DNormal(&x,&c); return c;}
	/// Scales the vector.
	_FORCEINLINE void scale(double a) {vecFunctions.V2DScale(this,this,a);}
	/// Scales the vector to a unit length.
	_FORCEINLINE void normalize() {vecFunctions.V2DNormal(this,this);}
	/// The vector interpolation between a and b, с[0.0 .. 1.0].
	_FORCEINLINE void lerp(vector2d &a,vector2d &b,double c) {vecFunctions.V2DLerp(&a,&b,this,c);}
	/// Масштобирование и сложение векторов по формуле a * c + b * d
	_FORCEINLINE void combine(vector2d &a,vector2d &b,double c,double d) {vecFunctions.V2DCombine(&a,&b,this,c,d);}
	/// The reflection vector.
	_FORCEINLINE vector2d reflect(vector2d &a) {vector2d c; vecFunctions.V2DReflect(this,&a,&c); return c;}
	/// Sets the value of the fields to zero.
	_FORCEINLINE void zero() {x=0;y=0;}
	/// Скалярное произведение
	_FORCEINLINE double dot(vector2d &a) {return vecFunctions.V2DDot(this,&a);}
	/// The angle between the vectors.
	_FORCEINLINE double angle(vector2d &b) {return vecFunctions.V2DAngle((void*)this,&b);}

	/// Addition of vectors
	_FORCEINLINE const vector2d operator+(const vector2d &a) {vector2d c; vecFunctions.V2DAdd((void*)&x,(void*)&a,&c); return c;}
	/// Addition of vectors
	_FORCEINLINE friend vector2d operator+(const vector2f &a, const vector2d &b) {vector2d c; vecFunctions.V2DAdd((void*)&a,(void*)&b,&c); return c;}
	/// Addition of vectors
	_FORCEINLINE friend vector2d operator+(vector2d &a, vector2d &b) {vector2d c; vecFunctions.V2DAdd(&a,&b,&c); return c;}
	/// Addition of vectors
	_FORCEINLINE const vector2d &operator+=(const vector2d &a) {vecFunctions.V2DAdd((void*)this,(void*)&a,(void*)this); return *this;}
	/// Addition of vectors
	_FORCEINLINE friend vector2d operator+=(vector2d &a,vector2d &b) {vecFunctions.V2DAdd(&a,&b,&a); return a;}
	/// Subtraction of vectors
	_FORCEINLINE const vector2d operator-(const vector2d &a) {vector2d c; vecFunctions.V2DSub((void*)&x,(void*)&a,&c); return c;}
	/// Subtraction of vectors
	_FORCEINLINE friend vector2d operator-(const vector2d &a, const vector2d &b) {vector2d c; vecFunctions.V2DSub((void*)&a,(void*)&b,&c); return c;}
	/// Subtraction of vectors
	_FORCEINLINE friend vector2d operator-(vector2d &a, vector2d &b) {vector2d c; vecFunctions.V2DSub(&a,&b,&c); return c;}
	/// Subtraction of vectors
	_FORCEINLINE const vector2d &operator-=(const vector2d &a) {vecFunctions.V2DSub((void*)this,(void*)&a,(void*)this); return *this;}
	/// Subtraction of vectors
	_FORCEINLINE friend vector2d operator-=(vector2d &a,vector2d &b) {vecFunctions.V2DSub(&a,&b,&a); return a;}
	/// Scaling vector
	_FORCEINLINE const vector2d operator*(const double &b) {vector2d c; vecFunctions.V2DScale((void*)this,&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE friend vector2d operator*(const vector2d &a, const double &b) {vector2d c; vecFunctions.V2DScale((void*)&a,&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE friend vector2d operator*(const double &b, const vector2d &a) {vector2d c; vecFunctions.V2DScale((void*)&a,&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE friend vector2d operator*(vector2d &a, double &b) {vector2d c; vecFunctions.V2DScale(&a,&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE friend vector2d operator*(double &b, vector2d &a) {vector2d c; vecFunctions.V2DScale(&a,&c,b); return c;}
	/// Element-by-element multiplication of vectors.
	_FORCEINLINE friend vector2d operator*(const vector2d &a, const vector2d &b) {vector2d c; vecFunctions.V2DMul((void*)&a,(void*)&b,&c); return c;}
	/// Element-by-element multiplication of vectors.
	_FORCEINLINE const vector2d operator*(const vector2d &a) {vector2d c; vecFunctions.V2DMul((void*)this,(void*)&a,&c); return c;}

	/// Accessing parameters as array elements.
	_FORCEINLINE double &operator[](unsigned int id) const {
		return ((double*)this)[id];
	}

	BT_API TYPEINFO_H;

};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* VECTOR2D_H_ */
