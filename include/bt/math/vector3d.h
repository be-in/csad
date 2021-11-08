/*
 * vector3d.h
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef VECTOR3D_H_
#define VECTOR3D_H_

#include <bt/functions.h>

namespace bt {

WARNING_DISABLE;
OPTIMIZE_ON;

class quaterniond;
class vector3f;

/**
 * @class vector3d
 *
 * @ingroup math
 * @brief vector3d - three-dimensional vector with double precision.
 *
 * @see vector3f, vector2f, vector2d, vector4f, vector4d, math
 */

class vector3d {
public:
	/// Параметр оси X
	double x;
	/// Параметр оси Y
	double y;
	/// Параметр оси Z
	double z;

	/// The constructor does not set the initial values to the fields.
	_FORCEINLINE vector3d() {}
	/// Конструктор, задает все параметры равными одному значению.
	_FORCEINLINE vector3d(double a) {x=y=z=a;}
	/// Конструктор.
	/// @param _x - vector x
	/// @param _y - vector y
	/// @param _z - vector z
	_FORCEINLINE vector3d(double _x,double _y,double _z) {x=_x;y=_y;z=_z;}
	_FORCEINLINE vector3d(double* _a) {vecFunctions.V3R64Copy(_a,(void*)this);}
	_FORCEINLINE vector3d(vector2d& _a) {double *c=(double*)&_a;x=c[0];y=c[1];z=0;}
	_FORCEINLINE vector3d(vector2d* _a) {double *c=(double*)&_a;x=c[0];y=c[1];z=0;}
	_FORCEINLINE vector3d(const vector3d& _a) {vecFunctions.V3R64Copy((void*)&_a,(void*)this);}
	_FORCEINLINE vector3d(vector3d& _a) {vecFunctions.V3R64Copy(&_a,(void*)this);}
	_FORCEINLINE vector3d(vector3d* _a) {vecFunctions.V3R64Copy(_a,(void*)this);}
	_FORCEINLINE vector3d(vector3i &_a) {vecFunctions.V3ITo3D((void*)&_a,(void*)this);}
	_FORCEINLINE vector3d(const vector3f& _a) {vecFunctions.V3FTo3D((void*)&_a,(void*)this);}
	_FORCEINLINE vector3d(vector3f &_a) {vecFunctions.V3FTo3D((void*)&_a,(void*)this);}
	_FORCEINLINE vector3d(vector3f *_a) {vecFunctions.V3FTo3D((void*)_a,(void*)this);}
	_FORCEINLINE ~vector3d() {}

	/// The appeal of the sign of the vector.
	_FORCEINLINE void neg() {vecFunctions.V3DInv((void*)this,(void*)this);}
	/// Addition of vectors
	_FORCEINLINE void add(vector3d &a,vector3d &b) {vecFunctions.V3DAdd((void*)&a,(void*)&b,(void*)this);}
	/// Subtraction of vectors
	_FORCEINLINE void sub(vector3d &a,vector3d &b) {vecFunctions.V3DSub((void*)&a,(void*)&b,(void*)this);}
	/// Vector length squared.
	_FORCEINLINE double sqrLen() {return vecFunctions.V3DLength2((void*)this);}
	/// Converts the vector to a unit length.
	_FORCEINLINE const vector3d norm() {vector3d c; vecFunctions.V3DNormal((void*)this,&c); return c;}
	/// Scales the vector.
	_FORCEINLINE void scale(double a) {vecFunctions.V3DScale((void*)this,(void*)this,a);}
	/// Converts the vector to a unit length.
	_FORCEINLINE void normalize() {vecFunctions.V3DNormal((void*)this,(void*)this);}
	/// The vector interpolation between a and b, с[0.0 .. 1.0].
	_FORCEINLINE void lerp(vector3d &a,vector3d &b,double c) {return vecFunctions.V3DLerp(&a,&b,(void*)this,c);}
	/// Scaling and addition of vectors by the formula a * c + b * d
	_FORCEINLINE void combine(vector3d &a,vector3d &b,double c,double d) {vecFunctions.V3DCombine(&a,&b,(void*)this,c,d);}
	/// The reflection vector.
	_FORCEINLINE vector3d reflect(vector3d &a) {vector3d c; vecFunctions.V3DReflect((void*)this,&a,&c); return c;}
	/// Sets the value of the fields to zero.
	_FORCEINLINE void zero() {x=0;y=0;z=0;}
	/// Dot product.
	_FORCEINLINE double dot(vector3d &a) {return vecFunctions.V3DDot((void*)this,&a);}
	/// Cross product.
	_FORCEINLINE vector3d cross(vector3d &a) {vector3d c; vecFunctions.V3DCross((void*)this,&a,&c); return c;}
	/// Cross product.
	_FORCEINLINE void cross(vector3d &a,vector3d &b) {vecFunctions.V3DCross(&a,&b,this);}
	/// The angle between the vectors.
	_FORCEINLINE double angle(vector3d &b) {return vecFunctions.V3DAngle((void*)this,&b);}

	/// Addition of vectors
	_FORCEINLINE const vector3d operator+(const vector3d &a) const {vector3d c; vecFunctions.V3DAdd((void*)this,(void*)&a,&c); return c;}
	/// Addition of vectors
	_FORCEINLINE friend vector3d operator+(vector3d &a, vector3d &b) {vector3d c; vecFunctions.V3DAdd(&a,&b,&c); return c;}
	/// Addition of vectors
	_FORCEINLINE const vector3d &operator+=(const vector3d &a) {vecFunctions.V3DAdd((void*)this,(void*)&a,(void*)this); return *this;}
	/// Addition of vectors
	_FORCEINLINE friend vector3d operator+=(vector3d &a,vector3d &b) {vecFunctions.V3DAdd(&a,&b,&a); return a;}
	/// Subtraction of vectors
	_FORCEINLINE const vector3d operator-(const vector3d &a) const {vector3d c; vecFunctions.V3DSub((void*)this,(void*)&a,&c); return c;}
	/// Subtraction of vectors
	_FORCEINLINE friend vector3d operator-(vector3d &a, vector3d &b) {vector3d c; vecFunctions.V3DSub(&a,&b,&c); return c;}
	/// Subtraction of vectors
	_FORCEINLINE const vector3d &operator-=(const vector3d &a) {vecFunctions.V3DSub((void*)this,(void*)&a,(void*)this); return (*this);}
	/// Subtraction of vectors
	_FORCEINLINE friend vector3d operator-=(vector3d &a,vector3d &b) {vecFunctions.V3DSub(&a,&b,&a); return a;}
	/// Scaling vector
	_FORCEINLINE friend vector3d operator*(vector3d &a, double &b) {vector3d c; vecFunctions.V3DScale(&a,&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE friend vector3d operator*(double &b, vector3d &a) {vector3d c; vecFunctions.V3DScale(&a,&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE friend vector3d operator*(vector3d &a, const double &b) {vector3d c; vecFunctions.V3DScale(&a,&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE friend vector3d operator*(const double &b, vector3d &a) {vector3d c; vecFunctions.V3DScale(&a,&c,b); return c;}
	/// Scaling vector
	_FORCEINLINE const vector3d operator*=(const double &b) {vecFunctions.V3DScale((void*)this,(void*)this,b); return (*this);}
	/// Scaling vector
	_FORCEINLINE const vector3d operator*=(double &b) {vecFunctions.V3DScale((void*)this,(void*)this,b); return (*this);}
	//_FORCEINLINE const vector3d operator*(const double b) {vector3d c; vecFunctions.V3DScale(this,&c,b); return c;}
	//_FORCEINLINE const vector3d operator*=(const double b) {vecFunctions.V3DScale(this,this,b); return *this;}
	/*_FORCEINLINE friend const vector3d operator*(const vector3d &a, double &b) {vector3d c; vecFunctions.V3DScale((void*)&a,&c,b); return c;}
	_FORCEINLINE friend const vector3d operator*(double &b, const vector3d &a) {vector3d c; vecFunctions.V3DScale((void*)&a,&c,b); return c;}
	_FORCEINLINE friend const vector3d operator*(const vector3d &a, const double &b) {vector3d c; vecFunctions.V3DScale((void*)&a,&c,b); return c;}
	_FORCEINLINE friend const vector3d operator*(const double &b, const vector3d &a) {vector3d c; vecFunctions.V3DScale((void*)&a,&c,b); return c;}*/
	/// Transforming a vector by a quaternion
	_FORCEINLINE const vector3d operator*(const quaterniond &_b) {vector3d _c; vecFunctions.Q3DInvTransform((void *)&_b,(void*)this,&_c); return _c;}
	/// Element-by-element multiplication of vectors.
	_FORCEINLINE const vector3d operator*(const vector3d &a) {vector3d c; vecFunctions.V3DMul((void*)this,(void*)&a,&c); return c;}
	/// Element-by-element multiplication of vectors.
	_FORCEINLINE friend vector3d operator*(vector3d &a, vector3d &b) {vector3d c; vecFunctions.V3DMul(&a,&b,&c); return c;}
	/// Element-by-element multiplication of vectors.
	_FORCEINLINE friend vector3d operator*(const vector3d &a, const vector3d &b) {vector3d c; vecFunctions.V3DMul((void*)&a,(void*)&b,&c); return c;}
	/// Element-by-element division of vectors.
	_FORCEINLINE friend vector3d operator/(vector3d &a, vector3d &b) {vector3d c; vecFunctions.V3DDiv((void*)&a,(void*)&b,&c); return c;}
	/// Element-by-element division of vectors.
	_FORCEINLINE friend vector3d operator/(const vector3d &a, const vector3d &b) {vector3d c; vecFunctions.V3DDiv((void*)&a,(void*)&b,&c); return c;}
	/// Dot product of the vectors.
	_FORCEINLINE const double operator|(vector3d &a) {return vecFunctions.V3DDot((void*)this,(void*)&a);}
	/// Dot product of the vectors.
	_FORCEINLINE friend double operator|(vector3d &a, vector3d &b) {return vecFunctions.V3DDot(&a,&b);}
	/// Cross product of the vectors.
	_FORCEINLINE const vector3d operator&(const vector3d &a) {vector3d c; vecFunctions.V3DCross((void*)this,(void*)&a,&c); return c;}
	/// Cross product of the vectors.
	_FORCEINLINE friend vector3d operator&(const vector3d &a, const vector3d &b) {vector3d c; vecFunctions.V3DCross((void*)&a,(void*)&b,&c); return c;}
	_FORCEINLINE vector3d &operator=(const vector3d &b) {vecFunctions.V3R64Copy((void*)&b,(void*)this); return *this;}
	//_FORCEINLINE vector3d &operator=(const _vector3f &b) {x=b.x;y=b.y;z=b.z; return *this;}

	_FORCEINLINE bool operator==(vector3d b) {if (x!=b.x) return false; if (y!=b.y) return false; return z==b.z;}
	_FORCEINLINE bool operator!=(vector3d b) {if (x!=b.x) return true; if (y!=b.y) return false; return z!=b.z;}

	/// Accessing parameters as array elements.
	_FORCEINLINE double &operator[](unsigned int id) const {
		return ((double*)this)[id];
	}

	/// Статический индентификатор типа vector3d::t()
	BT_API TYPEINFO_H;
};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* VECTOR3D_H_ */
