/*
 * matrix4f.h
 *
 *  Created on: 13.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef MATRIX4F_H_
#define MATRIX4F_H_

#include <bt/functions.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

class matrix4d;
class quaternionf;

/**
 * @class matrix4f
 *
 * @ingroup math
 * @brief matrix4f - The matrix in the format of floating point single precision.
 *
 * @see matrix4d, math
 */

	class matrix4f {
	public:
		float m[16];

		/// The constructor does not set the initial values to the fields.
		_FORCEINLINE matrix4f() {}
		_FORCEINLINE matrix4f(const float m00,const float m01,const float m02,const float m03,const float m10,const float m11,const float m12,const float m13,const float m20,const float m21,const float m22,const float m23,const float m30,const float m31,const float m32,const float m33) {m[0]=m00;m[1]=m01;m[2]=m02;m[3]=m03;m[4]=m10;m[5]=m11;m[6]=m12;m[7]=m13;m[8]=m20;m[9]=m21;m[10]=m22;m[11]=m23;m[12]=m30;m[13]=m31;m[14]=m32;m[15]=m33;}
		_FORCEINLINE matrix4f(const matrix4d &_a) {vecFunctions.M4DToM4F((void*)&_a,this);}
		_FORCEINLINE matrix4f(quaternionf &_a) {vecFunctions.Q4FMatrix((void *)&_a,this);}
		_FORCEINLINE matrix4f(quaterniond _a) {vecFunctions.Q4FMatrix((void *)&_a,this);}
		_FORCEINLINE matrix4f(quaternionf *_a) {vecFunctions.Q4FMatrix(_a,this);}
		_FORCEINLINE ~matrix4f() {}

		/// The multiplication of a vector by a matrix
		_FORCEINLINE vector2f &transform(const vector2f &_a) {vector2f c;vecFunctions.V2FTransform((void*)&_a,this,&c);return c;}
		/// The multiplication of a vector by a matrix
		_FORCEINLINE vector3f &transform(const vector3f &_a) {vector3f c;vecFunctions.V3FTransform((void*)&_a,this,&c);return c;}
		/// The multiplication of a vector by a matrix
		_FORCEINLINE vector4f &transform(const vector4f &_a) {vector4f c;vecFunctions.V4FTransform((void*)&_a,this,&c);return c;}

		/// Setting identity matrix
		_FORCEINLINE void identity() {vecFunctions.M4FIdentity(m);}
		/// The calculation of the inverse matrix
		_FORCEINLINE void invert(matrix4f*_a) {vecFunctions.M4FInv(m,_a);}
		/// The calculation of the inverse matrix
		_FORCEINLINE const matrix4f &invert() {matrix4f c;vecFunctions.M4FInv(m,&c);return c;}
		/// Умножение на матрицу смещения
		_FORCEINLINE void addTranslateSelf(float x,float y,float z) {float a[3]={x,y,z}; vecFunctions.M4FAddTranslate(this,a,this);}
		/// Умножение на матрицу смещения
		_FORCEINLINE void addTranslateSelf(vector3f *_a) {vecFunctions.M4FAddTranslate(this,_a,this);}
		/// Умножение на матрицу смещения
		_FORCEINLINE void addTranslateSelf(vector3f &_a) {vecFunctions.M4FAddTranslate(this,&_a,this);}

		/// Умножение на матрицу смещения
		_FORCEINLINE const matrix4f &addTranslate(float x,float y,float z) {matrix4f c;float a[3]={x,y,z}; vecFunctions.M4FAddTranslate(this,a,&c); return c;}
		/// Умножение на матрицу смещения
		_FORCEINLINE const matrix4f &addTranslate(vector3f *_a) {matrix4f c; vecFunctions.M4FAddTranslate(this,_a,&c); return c;}
		/// Умножение на матрицу смещения
		_FORCEINLINE const matrix4f &addTranslate(vector3f &_a) {matrix4f c; vecFunctions.M4FAddTranslate(this,&_a,&c); return c;}
		/// Умножение на матрицу масштаба
		_FORCEINLINE void addScaleSelf(vector3f &_a) {vecFunctions.M4FAddScale(this,&_a,this);}
		/// Умножение на матрицу масштаба
		_FORCEINLINE void addScaleSelf(float x,float y,float z) {float a[3]={x,y,z};vecFunctions.M4FAddScale(this,&a,this);}
		/// Умножение на матрицу масштаба
		_FORCEINLINE const matrix4f &addScale(vector3f &_a) {matrix4f c;vecFunctions.M4FAddScale(this,&_a,&c); return c;}
		/// Умножение на матрицу поворота
		_FORCEINLINE void addRotateSelf(quaternionf &_a) {vecFunctions.M4FAddRotate(this,&_a,this);}
		/// Умножение на матрицу поворота
		_FORCEINLINE const matrix4f &addRotate(quaternionf &_a) {matrix4f c;vecFunctions.M4FAddRotate(this,&_a,&c); return c;}

		/// Установка значений матрицы смещения
		_FORCEINLINE void translate(float x,float y,float z) {float c[3]={x,y,z}; vecFunctions.M4FTranslate(this,c);}
		/// Установка значений матрицы смещения
		_FORCEINLINE void translate(vector3f *_a) {vecFunctions.M4FTranslate(this,_a);}
		/// Установка значений матрицы смещения
		_FORCEINLINE void translate(vector3f &_a) {vecFunctions.M4FTranslate(this,&_a);}
		/// Set the scale matrix
		_FORCEINLINE void scale(vector3f &_a) {vecFunctions.M4FScale(this,&_a);}
		/// Set perspective projection
		/// @param _w - width in pixels
		/// @param _h - height in pixels
		/// @param _aend - the far plane
		/// @param _astart - the near plane
		/// @param _fov - viewing angle vertical
		_FORCEINLINE void perspective(int _w,int _h,float _aend,float _astart,float _fov) {vecFunctions.M4FPerspective(m,_w,_h,_aend,_astart,_fov);}
		/// Set the values of the orthogonal projection
		/// @param _w - width in pixels
		/// @param _h - height in pixels
		/// @param _aend - the far plane
		/// @param _astart - the near plane
		/// @param _scale - image scale
		_FORCEINLINE void ortographic(int _w,int _h,float _aend,float _astart,float _scale) {vecFunctions.M4FOrtographic(m,_w,_h,_aend,_astart,_scale);}

		_FORCEINLINE const matrix4f &operator*(const matrix4f &a) {matrix4f c; vecFunctions.M4FMul(m,(void*)&a,&c); return c;}
		_FORCEINLINE friend matrix4f &operator*(matrix4f &a, matrix4f &b) {matrix4f c; vecFunctions.M4FMul(&a,&b,&c); return c;}

		/// Field reference as to the elements of the array.
		_FORCEINLINE float &operator[](unsigned int id) const {
			return ((float*)this)[id];
		}

		BT_API TYPEINFO_H;

	};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* MATRIX4F_H_ */
