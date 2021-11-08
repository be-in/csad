/*
 * quaterniond.h
 *
 *  Created on: 13.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef QUATERNIOND_H_
#define QUATERNIOND_H_

#include <bt/functions.h>

namespace bt {

WARNING_DISABLE;
OPTIMIZE_ON;

class matrix4d;
class vector3d;
class vector4d;
class quaternionf;

/**
 * @class quaterniond
 *
 * @ingroup math
 * @brief quaterniond - the rotation around the vector
 *
 * Quaternions are used in the system of Hypercomplex numbers, form a vector space of dimension four over the field of real numbers.
 * Vector quaternions form a three-dimensional real vector space, which can be used to describe any rotation of this space
 * as the object is rotated around the center of the starting position in the final, at the expense derived
 * from the rotation of the fixed points lying on the straight line and the angle of rotation around it.
 *
 * @see quaternionf, math
 */

class quaterniond {
public:
	/// Factor.
	double x;
	/// Factor.
	double y;
	/// Factor.
	double z;
	/// Factor.
	double w;

	/// not initialised quaternion
	_FORCEINLINE quaterniond() {}
	/// @param _x - vector x
	/// @param _y - vector y
	/// @param _z - vector z
	/// @param _rad - rotation in radian
	_FORCEINLINE quaterniond(double _x,double _y,double _z,double _rad) {double c[4]; c[0]=_x; c[1]=_y; c[2]=_z;c[3]=_rad; vecFunctions.V4DQuaternion(c,this);}
	/// @param vec - vector
	/// @param rad - rotation in radian
	_FORCEINLINE quaterniond(vector3d vec,double rad) {double c[4];c[0]=vec.x;c[1]=vec.y;c[2]=vec.z;c[3]=rad; vecFunctions.V4DQuaternion(c,this);}
	/// @param vec - vector
	_FORCEINLINE quaterniond(vector4d &vec) {vecFunctions.V4DQuaternion(&vec,this);}
	_FORCEINLINE quaterniond(quaternionf *_a) {vecFunctions.V4FTo4D(_a,this);}
	_FORCEINLINE ~quaterniond() {}

	/// Set to identity
	_FORCEINLINE void reset() {x=y=z=0;w=1;}
	/// Reverse rotation
	_FORCEINLINE quaterniond invert() {quaterniond _c; vecFunctions.QDInv(this,&_c);return _c;}
	/// Create rotation matrix
	_FORCEINLINE void toMatrix(matrix4d &_c) {vecFunctions.Q4DMatrix(this,&_c); }
	/// Set Rotation form euler angles
	_FORCEINLINE void euler(double a,double b,double c) {vector3d lc(a,b,c); vecFunctions.QDEuler(&lc,this); }

	//_FORCEINLINE matrix4d matrix() {double _c[16]; vecFunctions.Q4DMatrix(this,_c); return *((matrix4d*)_c);}
//		_FORCEINLINE friend matrix4d operator=(quaterniond &_a) {matrix4d _c; gen3tool::vecFunctions.Q4DMatrix(&_a,&_c); return _c;}
	_FORCEINLINE friend quaterniond operator+(quaterniond &_a, quaterniond &_b) {quaterniond _c; vecFunctions.QDAdd(&_a,&_b,&_c); return _c;}
	/// Reverse rotation
	_FORCEINLINE const quaterniond operator!() {quaterniond _c; vecFunctions.QDInv((void*)this,&_c); return _c;}
	/// Reverse rotation
	_FORCEINLINE friend quaterniond operator!(quaterniond &_a) {quaterniond _c; vecFunctions.QDInv(&_a,&_c); return _c;}
	//_FORCEINLINE friend quaterniond operator-(quaterniond &_a) {quaterniond _c; gen3tool::vecFunctions.QDInv(&_a,&_c); return _c;}
	//_FORCEINLINE friend quaterniond operator-(quaterniond &_a,quaterniond &_b) {quaterniond _c; gen3tool::vecFunctions.QDInv(&_b,&_c); gen3tool::vecFunctions.QDAdd(&_a,&_c,&_c); return _c;}
	_FORCEINLINE const quaterniond operator*(const quaterniond &_a) {quaterniond _c; vecFunctions.QDMul((void*)this,(void*)&_a,&_c); return _c;}
	_FORCEINLINE friend quaterniond operator*(quaterniond &_a, quaterniond &_b) {quaterniond _c; vecFunctions.QDMul(&_a,&_b,&_c); return _c;}
	_FORCEINLINE const vector3d operator*(const vector3d &_b) {vector3d _c; vecFunctions.Q3DInvTransform(this,(void *)&_b,&_c); return _c;}
	_FORCEINLINE friend vector3d operator*(vector3d &_b,quaterniond &_a) {vector3d _c; vecFunctions.Q3DInvTransform(&_a,&_b,&_c); return _c;}
	_FORCEINLINE friend vector3d operator*(const vector3d &_b,const quaterniond &_a) {vector3d _c; vecFunctions.Q3DInvTransform((void*)&_a,(void*)&_b,&_c); return _c;}
	_FORCEINLINE const vector2d operator*(const vector2d &_b) {vector2d _c; vecFunctions.Q2DInvTransform(this,(void *)&_b,&_c); return _c;}
	_FORCEINLINE friend vector2d operator*(vector2d &_b,quaterniond &_a) {vector2d _c; vecFunctions.Q2DInvTransform(&_a,&_b,&_c); return _c;}

	_FORCEINLINE quaterniond &operator=(const quaterniond &b) {vecFunctions.V4R64Copy((void*)&b,(void*)this); return *this;}

	/// Field reference as to the elements of the array.
	_FORCEINLINE double &operator[](unsigned int id) const {
		return ((double*)this)[id];
	}

	/// Статический индентификатор типа quaterniond::t()
	BT_API TYPEINFO_H;
};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* QUATERNIOND_H_ */
