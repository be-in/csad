//=============================================================================
///**
// *  @file defarrayvector.h
// *
// *  $Id: defarrayvector.h 23.05.2012  $
// *
// *  @brief generator 3 tool, MS Visual C++ 2003-2008
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#pragma once
#ifndef GEN3TOOL_DEFARRAYVECTOR_H
#define GEN3TOOL_DEFARRAYVECTOR_H

#include <bt.h>

namespace bt {

///**
// *
// * Methods of calculation of massifs of the grouped values of unary and double accuracy.
// * In case of work of calculations over big massifs fast transfer of input parameters doesn't offer advantage.
// * Therefore the call of methods of processing of massifs is made on the stdcall standard.
// *
// *
// *
// *
// */

	template <typename T>

	/// Класс QGLArray представляет из себя контейнер неопределенного массива данных
	/// состоящий из упорядоченых елементов одного размера, находящихся друг за ругом.

	class GLArray // ???
	{
	public:
		_FORCEINLINE GLArray(void *_from,unsigned _int32 _offset,unsigned _int32 _step,unsigned _int32 *_max)
		{
			m_array=(char*)_from;
			m_array+=_offset;
			m_step=_step;
			m_count=_max;
		}

		/// Возвращает количество елементов реального массива
		_FORCEINLINE unsigned int getCount() {return *m_count;}

		/// Возвращает значение массива
		_FORCEINLINE T value(unsigned int _id) {char *p=m_array+_id*m_step; return *((T*)p);}

		/// Устанавливает значение массива
		_FORCEINLINE void setValue(unsigned int _id,T &_val) {char *p=m_array+_id*m_step; *((T*)p)=_val;}

		_FORCEINLINE T &operator[](unsigned int _id) const {char *p=m_array+_id*m_step; return *((T*)p);}

	private:
		/// Указатель на реальный массив
		char *m_array;
		/// Расстояние в байтах между элементами массива
		unsigned int m_step;
		/// Указатель на счетчик элементов реального массива
		unsigned int *m_count;
	};

	void _APICALL _AConvertDEF(void *_a,void *_b,int _stepa,int _stepb,void *_at,void *_bt,unsigned int _count);

	void _APICALL _A2BMoveDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A3BMoveDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A4BMoveDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A2FMoveDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A3FMoveDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A4FMoveDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A2DMoveDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A3DMoveDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A4DMoveDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);

	void _APICALL _A2ITo2FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A2ITo2DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A3ITo3FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A3ITo3DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A4ITo4WDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A4ITo4FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A4ITo4DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A2FTo2IDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A3FTo3IDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A4FTo4IDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A2FTo2DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A3FTo3DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A4FTo4DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A2DTo2FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A3DTo3FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A4DTo4FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);

	void _APICALL _A2FGrow3FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A2FGrow4FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A3FGrow4FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A2DGrow3DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A2DGrow4DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A3DGrow4DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);

	void _APICALL _A2IGrowTo3FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A2IGrowTo4FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A3IGrowTo4FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A2IGrowTo3DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A2IGrowTo4DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A3IGrowTo4DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);

	void _APICALL _A2FSumDEF(void *_a,float *_b,int _step,unsigned int _count);
	void _APICALL _A3FSumDEF(void *_a,float *_b,int _step,unsigned int _count);
	void _APICALL _A4FSumDEF(void *_a,float *_b,int _step,unsigned int _count);
	void _APICALL _A2DSumDEF(void *_a,double *_b,int _step,unsigned int _count);
	void _APICALL _A3DSumDEF(void *_a,double *_b,int _step,unsigned int _count);
	void _APICALL _A4DSumDEF(void *_a,double *_b,int _step,unsigned int _count);

	void _APICALL _A2FAddVectorDEF(void *_a,float *_b,void *_c,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A3FAddVectorDEF(void *_a,float *_b,void *_c,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A4FAddVectorDEF(void *_a,float *_b,void *_c,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A2DAddVectorDEF(void *_a,double *_b,void *_c,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A3DAddVectorDEF(void *_a,double *_b,void *_c,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A4DAddVectorDEF(void *_a,double *_b,void *_c,int _stepa,int _stepc,unsigned int _count);

	void _APICALL _A2IAddDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A3IAddDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A4IAddDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A2FAddDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A3FAddDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A4FAddDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A2DAddDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A3DAddDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A4DAddDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);

	void _APICALL _A2FSubVectorDEF(void *_a,float *_b,void *_c,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A3FSubVectorDEF(void *_a,float *_b,void *_c,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A4FSubVectorDEF(void *_a,float *_b,void *_c,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A2DSubVectorDEF(void *_a,double *_b,void *_c,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A3DSubVectorDEF(void *_a,double *_b,void *_c,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A4DSubVectorDEF(void *_a,double *_b,void *_c,int _stepa,int _stepc,unsigned int _count);

	void _APICALL _A2ISubDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A3ISubDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A4ISubDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A2FSubDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A3FSubDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A4FSubDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A2DSubDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A3DSubDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A4DSubDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);

	void _APICALL _A2FScaleDEF(void *_a,void *_c,float _b,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A3FScaleDEF(void *_a,void *_c,float _b,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A4FScaleDEF(void *_a,void *_c,float _b,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A2DScaleDEF(void *_a,void *_c,double _b,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A3DScaleDEF(void *_a,void *_c,double _b,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A4DScaleDEF(void *_a,void *_c,double _b,int _stepa,int _stepc,unsigned int _count);

	void _APICALL _A2FMulVectorDEF(void *_a,float *_b,void *_c,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A3FMulVectorDEF(void *_a,float *_b,void *_c,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A4FMulVectorDEF(void *_a,float *_b,void *_c,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A2DMulVectorDEF(void *_a,double *_b,void *_c,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A3DMulVectorDEF(void *_a,double *_b,void *_c,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A4DMulVectorDEF(void *_a,double *_b,void *_c,int _stepa,int _stepc,unsigned int _count);

	void _APICALL _A2FMulDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A3FMulDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A4FMulDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A2DMulDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A3DMulDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A4DMulDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);

	void _APICALL _A2FNormalDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A3FNormalDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A4FNormalDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A2DNormalDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A3DNormalDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A4DNormalDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count);

	void _APICALL _A2FLerpDEF(void *_a,void *_b,void *_c,float _d,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A3FLerpDEF(void *_a,void *_b,void *_c,float _d,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A4FLerpDEF(void *_a,void *_b,void *_c,float _d,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A2DLerpDEF(void *_a,void *_b,void *_c,double _d,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A3DLerpDEF(void *_a,void *_b,void *_c,double _d,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _APICALL _A4DLerpDEF(void *_a,void *_b,void *_c,double _d,int _stepa,int _stepb,int _stepc,unsigned int _count);

	void _APICALL _A2FMatrixTransformDEF(void *_a,void *_matrix,void *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A3FMatrixTransformDEF(float *_a,void *_matrix,float *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A4FMatrixTransformDEF(float *_a,void *_matrix,float *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A2DMatrixTransformDEF(double *_a,void *_matrix,double *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A3DMatrixTransformDEF(double *_a,void *_matrix,double *_b,int _stepa,int _stepb,unsigned int _count);
	void _APICALL _A4DMatrixTransformDEF(double *_a,void *_matrix,double *_b,int _stepa,int _stepb,unsigned int _count);

/*	void _STDCALL _A3FQuaternionTransformDEF(void *_a,float *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);
	void _STDCALL _A3DQuaternionTransformDEF(void *_a,double *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count);*/

	void _APICALL _A2FProjDEF(float *_a,void *_b,float *_c,float *_d,float *_e,int _stepa,int _stepe,int _flagoff,unsigned int _count);
	void _APICALL _A3FProjDEF(float *_a,void *_b,float *_c,float *_d,float *_e,int _stepa,int _stepe,int _flagoff,unsigned int _count);
	void _APICALL _A4FProjDEF(float *_a,void *_b,float *_c,float *_d,float *_e,int _stepa,int _stepe,int _flagoff,unsigned int _count);
	void _APICALL _A2DProjDEF(double *_a,void *_b,double *_c,double *_d,double *_e,int _stepa,int _stepe,int _flagoff,unsigned int _count);
	void _APICALL _A3DProjDEF(double *_a,void *_b,double *_c,double *_d,double *_e,int _stepa,int _stepe,int _flagoff,unsigned int _count);
	void _APICALL _A4DProjDEF(double *_a,void *_b,double *_c,double *_d,double *_e,int _stepa,int _stepe,int _flagoff,unsigned int _count);

	void _APICALL _AFZoomSplineCRDEF(float *_a,float *_b,int _stepa,int _stepb,double spstart,float spStep,unsigned int flag,unsigned int _counta,unsigned int _count);
	void _APICALL _A2FZoomSplineCRDEF(float *_a,float *_b,int _stepa,int _stepb,double spstart,float spStep,unsigned int flag,unsigned int _counta,unsigned int _count);
	void _APICALL _A3FZoomSplineCRDEF(float *_a,float *_b,int _stepa,int _stepb,double spstart,float spStep,unsigned int flag,unsigned int _counta,unsigned int _count);
	void _APICALL _A4FZoomSplineCRDEF(float *_a,float *_b,int _stepa,int _stepb,double spstart,float spStep,unsigned int flag,unsigned int _counta,unsigned int _count);
	void _APICALL _ADZoomSplineCRDEF(double *_a,double *_b,int _stepa,int _stepb,double spstart,float spStep,unsigned int flag,unsigned int _counta,unsigned int _count);
	void _APICALL _A2DZoomSplineCRDEF(double *_a,double *_b,int _stepa,int _stepb,double spstart,float spStep,unsigned int flag,unsigned int _counta,unsigned int _count);
	void _APICALL _A3DZoomSplineCRDEF(double *_a,double *_b,int _stepa,int _stepb,double spstart,float spStep,unsigned int flag,unsigned int _counta,unsigned int _count);
	void _APICALL _A4DZoomSplineCRDEF(double *_a,double *_b,int _stepa,int _stepb,double spstart,float spStep,unsigned int flag,unsigned int _counta,unsigned int _count);
};

#endif
