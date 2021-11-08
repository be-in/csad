//=============================================================================
///**
// *  @file   defmath.h
// *
// *  $Id: defmath.h 23.05.2012  $
// *
// *  @brief generator 3, MS Visual C++ 2003-2008
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#pragma once
#ifndef GEN3TOOL_DEFMATH_H
#define GEN3TOOL_DEFMATH_H

#include <bt.h>

namespace bt {

	_ALIGN extern float fastsindividef[];
	_ALIGN extern double fastsindivided[];
	_ALIGN extern float fasttgdividef[];
	_ALIGN extern double fasttgdivided[];
	_ALIGN extern float rotateArcTgf[];
	_ALIGN extern double rotateArcTgd[];
	_ALIGN extern float fcmsplinef[];
	_ALIGN extern double fcmsplined[];

	/// ¬ычисление квадратного корн€
	float _APICALL _FsqrtDEF(float);

	/// ¬ычисление квадратного корн€
	double _APICALL _DsqrtDEF(double);

	/// Ѕыстрое вычисление обратного квадратного корн€
	float _APICALL _FFastInvSqrtDEF(float);

	/// Ѕыстрое вычисление обратного квадратного корн€
	double _APICALL _DFastInvSqrtDEF(double);

	/// ¬ычисление косинуса синуса в формте одинарной точности, 8 итераций.
	void _APICALL _FSinCosDEF(float ,float *,float *);

	/// ¬ычисление косинуса синуса в формате двойной точности, 8 итераций.
	void _APICALL _DSinCosDEF(double ,double *,double *);

	/// ¬ычисление косинуса синуса в формте одинарной точности, 5 итераций.
	void _APICALL _FSinCosFASTDEF(float _a,float *_cos,float *_sin);

	/// ¬ычисление косинуса синуса в формате двойной точности, 5 итераций.
	void _APICALL _DSinCosFASTDEF(double _a,double *_cos,double *_sin);

	float _APICALL _FSinDEF(float _a);
	float _APICALL _FCosDEF(float _a);
	double _APICALL _DSinDEF(double _a);
	double _APICALL _DCosDEF(double _a);

	/// ¬ычисление арктангенса в формте одинарной точности.
	float _APICALL _FArcTgDEF(float _x,float _y);

	/// ¬ычисление арктангенса в формате двойной точности.
	double _APICALL _DArcTgDEF(double _x,double _y);

	/// ”множение числа на 2 в степени N в формте одинарной точности.
	float _APICALL _Fmul2NDEF(float,_int32);

	/// ”множение числа на 2 в степени N в формате двойной точности.
	double _APICALL _Dmul2NDEF(double,_int32);

	/// »нтерпол€ци€ между двум€ значени€ми в формте одинарной точности.
	float _APICALL _FLerpDEF(float,float,float);

	/// »нтерпол€ци€ между двум€ значени€ми в формате двойной точности.
	double _APICALL _DLerpDEF(double,double,double);

	///
	_int32 _APICALL _FTruncDEF(float);

	///
	_int32 _APICALL _DTruncDEF(double);

	///
	_int64 _APICALL _DTruncLDEF(double);

	///
	_int32 _APICALL _FRoundDEF(float _a);

	///
	_int32 _APICALL _DRoundDEF(double _a);

	///
	_int64 _APICALL _DRoundLDEF(double _a);

	///
	float _APICALL _IToFDEF(_int32 _a);

	///
	double _APICALL _IToDDEF(_int32 _a);

	///
	double _APICALL _LToDDEF(_int64 _a);

	///
	_int32 _APICALL _Fmul2NTruncDEF(float _a,_int32 _b);

	_int32 _APICALL _Dmul2NTruncDEF(double _a,_int32 _b);

	///
	_int32 _APICALL _Fmul2NRoundDEF(float _a,_int32 _b);

	///
	_int32 _APICALL _Dmul2NRoundDEF(double _a,_int32 _b);

	float _APICALL _FScaleModDEF(float  _a, float _c);
	double _APICALL _DScaleModDEF(double  _a, double _c);

	void _APICALL _FCRCCDEF(float,float,float,float,float *);
	void _APICALL _DCRCCDEF(double,double,double,double,double *);
	void _APICALL _FPCRCCDEF(float **,float *);
	void _APICALL _DPCRCCDEF(double **,double *);

	void _APICALL _FSplineCRDEF(float *,float *,float ,float);
	void _APICALL _DSplineCRDEF(double *,double *,double ,double);

	float _APICALL _FExpDEF(float);
	double _APICALL _DExpDEF(double);
	float _APICALL _FLnDEF(float);
	double _APICALL _DLnDEF(double);

	float _APICALL _FLog2DEF(float _a);
	double _APICALL _DLog2DEF(double _a);
	_int32 _APICALL _ILog2DEF(_int32 _a);
	_int32 _APICALL _LLog2DEF(_int64 _a);

	float _APICALL _FPoly1DEF(void*,unsigned _int32,float);
	double _APICALL _DPoly1DEF(void*,unsigned _int32,double);
	float _APICALL _FPoly2DEF(void*,unsigned _int32,unsigned _int32,float,float);
	double _APICALL _DPoly2DEF(void*,unsigned _int32,unsigned _int32,double,double);
	float _APICALL _FPolyMDEF(void*,unsigned _int32*,float*,unsigned _int32);
	double _APICALL _DPolyMDEF(void*,unsigned _int32*,double*,unsigned _int32);

	void _APICALL _FMinMaxDEF(float *,float *,float *);
	void _APICALL _DMinMaxDEF(double *,double *,double *);

}

#endif //GEN3TOOL_DEFMATH_H
