/*
 * vector4d.h
 *
 *  Created on: 13.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef VECTOR4D_H_
#define VECTOR4D_H_

#include <bt/functions.h>

namespace bt {

WARNING_DISABLE;
OPTIMIZE_ON;

	class vector3f;
	class vector4f;
	class vector3d;
	class quaterniond;

/**
 * @class vector4d
 *
 * @ingroup math
 * @brief vector4d - four-dimensional double precision vector.
 *
 * @see vector4f, vector2f, vector2d, vector3f, vector3d, math
 */

	class vector4d {
	public:
		/// Параметр оси X
		double x;
		/// Параметр оси Y
		double y;
		/// Параметр оси Z
		double z;
		/// Параметр оси W
		double w;

		/// The constructor does not set the initial values to the fields.
		_FORCEINLINE vector4d() {}
		/// Конструктор, задает все параметры равными одному значению.
		_FORCEINLINE vector4d(double _a) {x=y=z=w=_a;}
		/// Конструктор.
		/// @param _x - vector x
		/// @param _y - vector y
		/// @param _z - vector z
		/// @param _w - vector w
		_FORCEINLINE vector4d(double _x,double _y,double _z,double _w) {x=_x;y=_y;z=_z;w=_w;}
		_FORCEINLINE vector4d(double* _a) {vecFunctions.V4R64Copy((void*)_a,(void*)this);}
		_FORCEINLINE vector4d(vector3f* _a) {vecFunctions.V3FTo3D((void*)_a,(void*)this);}
		///
		_FORCEINLINE vector4d(vector4f* _a) {vecFunctions.V4FTo4D((void*)_a,(void*)this);}
		_FORCEINLINE vector4d(vector3d* _a) {vecFunctions.V3R64Copy((void*)_a,(void*)this);}
		_FORCEINLINE vector4d(quaterniond* _a) {vecFunctions.Q4DVector((void*)_a,(void*)this);}
		_FORCEINLINE ~vector4d() {}

		/// The appeal of the sign of the vector.
		_FORCEINLINE void neg() {vecFunctions.V4DInv(this,this);}
		/// Vector length squared.
		_FORCEINLINE double sqrLen() {return vecFunctions.V4DLength2(this);}
		/// Converts the vector to a unit length.
		_FORCEINLINE const vector4d norm() {vector4d c; vecFunctions.V4DNormal(this,&c); return c;}
		/// Scales the vector.
		_FORCEINLINE void scale(double a) {vecFunctions.V4DScale(this,this,a);}
		/// Converts the vector to a unit length.
		_FORCEINLINE void normalize() {vecFunctions.V4DNormal(this,this);}
		/// The vector interpolation between a and b, с[0.0 .. 1.0].
		_FORCEINLINE void lerp(vector4d &a,vector4d &b,double c) {return vecFunctions.V4DLerp(&a,&b,this,c);}
		/// Scaling and addition of vectors by the formula a * c + b * d
		_FORCEINLINE void combine(vector4d &a,vector4d &b,double c,double d) {vecFunctions.V4DCombine(&a,&b,this,c,d);}
		/// Clears the vector.
		_FORCEINLINE void zero() {x=y=z=w=0;}
		/// Dot product.
		_FORCEINLINE double dot(vector4d &a) {return vecFunctions.V4DDot(this,&a);}

		/// Addition of vectors
		_FORCEINLINE const vector4d operator+(const vector4d &a) {vector4d c; vecFunctions.V4DAdd((void *)this,(void *)&a,&c); return c;}
		/// Addition of vectors
		_FORCEINLINE friend vector4d operator+(vector4d &a, vector4d &b) {vector4d c; vecFunctions.V4DAdd(&a,&b,&c); return c;}
		/// Addition of vectors
		_FORCEINLINE const vector4d &operator+=(const vector4d &a) {vecFunctions.V4DAdd((void*)this,(void*)&a,(void*)this); return *this;}
		/// Addition of vectors
		_FORCEINLINE friend vector4d operator+=(vector4d &a,vector4d &b) {vecFunctions.V4DAdd(&a,&b,&a); return a;}
		/// Subtraction of vectors
		_FORCEINLINE const vector4d operator-(const vector4d &a) {vector4d c; vecFunctions.V4DSub((void *)this,(void *)&a,&c); return c;}
		/// Subtraction of vectors
		_FORCEINLINE friend vector4d operator-(vector4d &a, vector4d &b) {vector4d c; vecFunctions.V4DSub(&a,&b,&c); return c;}
		/// Subtraction of vectors
		_FORCEINLINE const vector4d &operator-=(const vector4d &a) {vecFunctions.V4DSub((void*)this,(void*)&a,(void*)this); return *this;}
		/// Subtraction of vectors
		_FORCEINLINE friend vector4d operator-=(vector4d &a,vector4d &b) {vecFunctions.V4DSub(&a,&b,&a); return a;}
		/// Scaling vector.
		_FORCEINLINE friend vector4d operator*(vector4d &a, double &b) {vector4d c; vecFunctions.V4DScale(&a,&c,b); return c;}
		/// Scaling vector.
		_FORCEINLINE friend vector4d operator*(double &b, vector4d &a) {vector4d c; vecFunctions.V4DScale(&a,&c,b); return c;}
		/// Element-by-element multiplication of vectors.
		_FORCEINLINE friend vector4d operator*(vector4d &a, vector4d &b) {vector4d c; vecFunctions.V4DMul(&a,&b,&c); return c;}
		/// Element-by-element division of vectors.
		_FORCEINLINE friend vector4d operator/(vector4d &a, vector4d &b) {vector4d c; vecFunctions.V4DDiv(&a,&b,&c); return c;}
		/// Dot product of the vectors.
		_FORCEINLINE friend double operator|(vector4d &a, vector4d &b) {return (const double)vecFunctions.V4DDot(&a,&b);}
		/// Cross product of the vectors, the vector is represented as 3D.
		_FORCEINLINE friend vector4d operator&(vector4d &a, vector4d &b) {vector4d c; c.w=a.w*b.w; vecFunctions.V3DCross(&a,&b,&c); return c;}
		_FORCEINLINE vector4d &operator=(const vector4d &b) {vecFunctions.V4R64Copy((void*)&b,(void*)this); return *this;}
		//_FORCEINLINE vector4d &operator=(const _vector4f &b) {x=b.x;y=b.y;z=b.z;w=b.w; return *this;}

		/// Accessing parameters as array elements.
		_FORCEINLINE double &operator[](unsigned int id) const {
			return ((double*)this)[id];
		}

		/// Статический индентификатор типа vector4d::t()
		BT_API TYPEINFO_H;
	};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* VECTOR4D_H_ */
