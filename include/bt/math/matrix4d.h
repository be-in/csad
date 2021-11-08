/*
 * matrix4d.h
 *
 *  Created on: 13.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef MATRIX4D_H_
#define MATRIX4D_H_

#include <bt/functions.h>

namespace bt {

WARNING_DISABLE;
OPTIMIZE_ON;

	class  vector3d;
	class  quaterniond;

	/**
	 * @class matrix4d
	 *
	 * @ingroup math
	 * @brief matrix4d - The matrix in the format of floating point numbers double precision
	 *
	 * @see matrix4f, math
	 */

	class matrix4d {
	public:
		double m[16];

		/// The constructor does not set the initial values to the fields.
		_FORCEINLINE matrix4d() {}
		_FORCEINLINE matrix4d(const matrix4f &_a) {vecFunctions.M4FToM4D((void*)&_a,this);}
		_FORCEINLINE matrix4d(quaterniond &_a) {vecFunctions.Q4DMatrix((void *)&_a,this);}
		_FORCEINLINE matrix4d(quaterniond _a) {vecFunctions.Q4DMatrix((void *)&_a,this);}
		_FORCEINLINE matrix4d(quaterniond *_a) {vecFunctions.Q4DMatrix(_a,this);}
		_FORCEINLINE ~matrix4d() {}

		/// Умножение вектора на матрицу
		_FORCEINLINE vector2d transform(const vector2d &_a) {vector2d c;vecFunctions.V2DTransform((void*)&_a,m,&c);return c;}
		/// Умножение вектора на матрицу
		_FORCEINLINE vector3d transform(const vector3d &_a) {vector3d c;vecFunctions.V3DTransform((void*)&_a,m,&c);return c;}
		/// Умножение вектора на матрицу
		_FORCEINLINE vector4d transform(const vector4d &_a) {vector4d c;vecFunctions.V4DTransform((void*)&_a,m,&c);return c;}

		/// Установка значений единичной матрицы
		_FORCEINLINE void identity() {vecFunctions.M4DIdentity(m);}
		/// Вычисление обратной матрицы
		_FORCEINLINE void invert(matrix4d*_a) {vecFunctions.M4DInv(m,_a);}
		/// Вычисление обратной матрицы
		_FORCEINLINE const matrix4d &invert() {matrix4d c;vecFunctions.M4DInv(m,&c);return c;}
		/// Умножение на матрицу смещения
		_FORCEINLINE void addTranslateSelf(double x,double y,double z) {double a[3]={x,y,z}; vecFunctions.M4DAddTranslate(this,a,this);}
		/// Умножение на матрицу смещения
		_FORCEINLINE void addTranslateSelf(vector3d *_a) {vecFunctions.M4DAddTranslate(this,_a,this);}
		/// Умножение на матрицу смещения
		_FORCEINLINE void addTranslateSelf(vector3d &_a) {vecFunctions.M4DAddTranslate(this,&_a,this);}
		/// Умножение на матрицу смещения
		_FORCEINLINE const matrix4d addTranslate(double x,double y,double z) {matrix4d c;double a[3]={x,y,z}; vecFunctions.M4DAddTranslate(this,a,&c); return c;}
		/// Умножение на матрицу смещения
		_FORCEINLINE const matrix4d addTranslate(vector3d *_a) {matrix4d c; vecFunctions.M4DAddTranslate(this,_a,&c); return c;}
		/// Умножение на матрицу смещения
		_FORCEINLINE const matrix4d addTranslate(vector3d &_a) {matrix4d c; vecFunctions.M4DAddTranslate(this,&_a,&c); return c;}
		/// Умножение на матрицу масштаба
		_FORCEINLINE void addScaleSelf(vector3d &_a) {vecFunctions.M4DAddScale(this,&_a,this);}
		/// Умножение на матрицу масштаба
		_FORCEINLINE const matrix4d addScale(vector3d &_a) {matrix4d c; vecFunctions.M4DAddScale(this,&_a,&c); return c;}
		/// Умножение на матрицу поворота
		_FORCEINLINE void addRotateSelf(quaterniond &_a) {vecFunctions.M4DAddRotate(this,&_a,this);}
		/// Умножение на матрицу поворота
		_FORCEINLINE const matrix4d addRotate(quaterniond &_a) {matrix4d c;vecFunctions.M4DAddRotate(this,&_a,&c); return c;}

		/// Установка значений матрицы смещения
		_FORCEINLINE void translate(double x,double y,double z) {double c[3]={x,y,z}; vecFunctions.M4DTranslate(this,c);}
		/// Установка значений матрицы смещения
		_FORCEINLINE void translate(vector3d *_a) {vecFunctions.M4DTranslate(this,_a);}
		/// Установка значений матрицы смещения
		_FORCEINLINE void translate(vector3d &_a) {vecFunctions.M4DTranslate(this,&_a);}
		/// Set the scale matrix
		_FORCEINLINE void scale(vector3d &_a) {vecFunctions.M4DScale(this,&_a);}
		/// Set perspective projection
		/// @param _w - width in pixels
		/// @param _h - height in pixels
		/// @param _aend - the far plane
		/// @param _astart - the near plane
		/// @param _fov - viewing angle vertical
		_FORCEINLINE void perspective(int _w,int _h,float _aend,float _astart,float _fov) {vecFunctions.M4DPerspective(m,_w,_h,_aend,_astart,_fov);}
		/// Set the values of the orthogonal projection
		/// @param _w - width in pixels
		/// @param _h - height in pixels
		/// @param _aend - the far plane
		/// @param _astart - the near plane
		/// @param _scale - image scale
		_FORCEINLINE void ortographic(int _w,int _h,float _aend,float _astart,float _scale) {vecFunctions.M4DOrtographic(m,_w,_h,_aend,_astart,_scale);}

		_FORCEINLINE const matrix4d operator*(const matrix4d &a) {matrix4d c; vecFunctions.M4DMul(m,(void*)&a,&c); return c;}
		_FORCEINLINE friend matrix4d operator*(matrix4d &a, matrix4d &b) {matrix4d c; vecFunctions.M4DMul(&a,&b,&c); return c;}

		/// Field reference as to the elements of the array.
		_FORCEINLINE double &operator[](unsigned int id) const {
			return ((double*)this)[id];
		}

		BT_API TYPEINFO_H;
	};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* MATRIX4D_H_ */
