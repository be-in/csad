/*
 * quaternionf.h
 *
 *  Created on: 13.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef QUATERNIONF_H_
#define QUATERNIONF_H_

#include <bt/functions.h>

namespace bt {

using namespace bt;

WARNING_DISABLE;
OPTIMIZE_ON;

class vector3f;
class vector4f;
class quaterniond;
class matrix4f;

/**
 * @class quaternionf
 *
 * @ingroup math
 * @brief quaternionf - the rotation around the vector
 *
 * Quaternions are used in the system of Hypercomplex numbers, form a vector space of dimension four over the field of real numbers.
 * Vector quaternions form a three-dimensional real vector space, which can be used to describe any rotation of this space
 * as the object is rotated around the center of the starting position in the final, at the expense derived
 * from the rotation of the fixed points lying on the straight line and the angle of rotation around it.
 *
 * @see quaternionf, math
 */

class quaternionf {
public:
	/// Factor.
	float x;
	/// Factor.
	float y;
	/// Factor.
	float z;
	/// Factor.
	float w;

	/// not initialised quaternion
	_FORCEINLINE quaternionf() {}
	/// @param _x - vector x
	/// @param _y - vector y
	/// @param _z - vector z
	/// @param _rad - rotation in radian
	_FORCEINLINE quaternionf(float _x,float _y,float _z,float _rad) {float c[4]; c[0]=_x; c[1]=_y; c[2]=_z;c[3]=_rad; vecFunctions.V4FQuaternion(c,this);}
	/// @param vec - vector
	/// @param rad - rotation in radian
	_FORCEINLINE quaternionf(vector3f vec,double rad) {float c[4];c[0]=vec.x;c[1]=vec.y;c[2]=vec.z;c[3]=rad; vecFunctions.V4FQuaternion(c,this);}
	/// @param vec - vector
	_FORCEINLINE quaternionf(vector4f &vec) {vecFunctions.V4FQuaternion(&vec,this);}
	_FORCEINLINE quaternionf(quaterniond &_a) {vecFunctions.V4DTo4F(&_a,this);}
	_FORCEINLINE quaternionf(quaterniond *_a) {vecFunctions.V4DTo4F(_a,this);}
	_FORCEINLINE ~quaternionf() {}

	//quaterniond(vector3d _vec,double _rad) {vector4d c(_vec.x,_vec.y,_vec.z,_rad); vecFunctions.V4DQuaternion(&c,this);}

	/// Set to identity
	_FORCEINLINE void reset() {x=0;y=0;z=0;w=1;}
	/// Reverse rotation
	_FORCEINLINE quaternionf invert() {quaternionf _c; vecFunctions.QFInv(this,&_c);return _c;}
	/// Create rotation matrix
	_FORCEINLINE void toMatrix(matrix4f &_c) {vecFunctions.Q4FMatrix(this,&_c); }
	/// Set Rotation form euler angles
	_FORCEINLINE void euler(double a,double b,double c) {vector3d lc(a,b,c); vecFunctions.QDEuler(&lc,this); }

	/// Reverse rotation
	_FORCEINLINE const quaternionf operator!() {quaternionf _c; vecFunctions.QFInv((void*)this,&_c); return _c;}
	/// Reverse rotation
	_FORCEINLINE friend quaternionf operator!(quaternionf &_a) {quaternionf _c; vecFunctions.QFInv(&_a,&_c); return _c;}
	_FORCEINLINE const quaternionf operator*(const quaternionf &_a) {quaternionf _c; vecFunctions.QFMul((void*)this,(void*)&_a,&_c); return _c;}
	_FORCEINLINE friend quaternionf operator*(quaternionf &_a, quaternionf &_b) {quaternionf _c; vecFunctions.QFMul(&_a,&_b,&_c); return _c;}
	_FORCEINLINE const vector2f operator*(const vector2f &_b) {vector2f _c; vecFunctions.Q2FInvTransform(this,(void *)&_b,&_c); return _c;}
	_FORCEINLINE friend vector2f operator*(vector2f &_b,quaternionf &_a) {vector2f _c; vecFunctions.Q2FInvTransform(&_a,&_b,&_c); return _c;}
	_FORCEINLINE const vector3f operator*(const vector3f &_b) {vector3f _c; vecFunctions.Q3FInvTransform(this,(void *)&_b,&_c); return _c;}
	_FORCEINLINE friend vector3f operator*(vector3f &_b,quaternionf &_a) {vector3f _c; vecFunctions.Q3FInvTransform(&_a,&_b,&_c); return _c;}

	_FORCEINLINE quaternionf &operator=(const quaternionf &b) {vecFunctions.V4R32Copy((void*)&b,(void*)this); return *this;}

	/// Field reference as to the elements of the array.
	_FORCEINLINE float &operator[](unsigned int id) const {
		return ((float*)this)[id];
	}

	/// Статический индентификатор типа quaternionf::t()
	BT_API TYPEINFO_H;

};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* QUATERNIONF_H_ */
