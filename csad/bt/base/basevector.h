//=============================================================================
///**
// *  @file   defvector.h
// *
// *  $Id: defvector.h 23.05.2012  $
// *
// *  @brief generator 3, MS Visual C++ 2003-2008
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#pragma once
#ifndef GEN3TOOL_DEFVECTOR_H
#define GEN3TOOL_DEFVECTOR_H

#include <bt.h>

namespace bt {

OPTIMIZE_ON;

	void _APICALL _V4R8DEF(char *,char *);
	void _APICALL _V4R16DEF(short *,short *);
	void _APICALL _V4R32DEF(_int32 *,_int32 *);
	void _APICALL _V4R64DEF(_int64 *,_int64 *);

	void _APICALL _V2R32CopyDEF(void *,void *);
	void _APICALL _V3R32CopyDEF(void *,void *);
	void _APICALL _V4R32CopyDEF(void *,void *);
	void _APICALL _V2R64CopyDEF(void *,void *);
	void _APICALL _V3R64CopyDEF(void *,void *);
	void _APICALL _V4R64CopyDEF(void *,void *);

	void _APICALL _V2BTo2FDEF(char *,float *);
	void _APICALL _V2BTo2DDEF(char *,double *);
	void _APICALL _V3BTo3FDEF(char *,float *);
	void _APICALL _V3BTo3DDEF(char *,double *);
	void _APICALL _V4BTo4FDEF(char *,float *);
	void _APICALL _V4BTo4DDEF(char *,double *);
	void _APICALL _V2ITo2FDEF(_int32 *,float *);
	void _APICALL _V2ITo2DDEF(_int32 *,double *);
	void _APICALL _V3ITo3FDEF(_int32 *,float *);
	void _APICALL _V3ITo3DDEF(_int32 *,double *);
	void _APICALL _V4ITo4BDEF(_int32 *,char *);
	void _APICALL _V4ITo4FDEF(_int32 *,float *);
	void _APICALL _V4ITo4DDEF(_int32 *,double *);
	void _APICALL _V2FTo2BDEF(float *,char *);
	void _APICALL _V2FTo2IDEF(float *,_int32 *);
	void _APICALL _V2FTTo2IDEF(float *,_int32 *);
	void _APICALL _V2FTo2DDEF(float *,double *);
	void _APICALL _V3FTo3BDEF(float *,char *);
	void _APICALL _V3FTo3IDEF(float *,_int32 *);
	void _APICALL _V3FTTo3IDEF(float *,_int32 *);
	void _APICALL _V3FTo3DDEF(float *,double *);
	void _APICALL _V4FTo4BDEF(float *,char *);
	void _APICALL _V4FTo4IDEF(float *,_int32 *);
	void _APICALL _V4FTTo4IDEF(float *,_int32 *);
	void _APICALL _V4FTo4DDEF(float *,double *);
	void _APICALL _V2DTo2BDEF(double *,char *);
	void _APICALL _V2DTo2IDEF(double *,_int32 *);
	void _APICALL _V2DTTo2IDEF(double *,_int32 *);
	void _APICALL _V2DTo2LDEF(double *,_int64 *);
	void _APICALL _V2DTTo2LDEF(double *,_int64 *);
	void _APICALL _V2DTo2FDEF(double *,float *);
	void _APICALL _V3DTo3BDEF(double *,char *);
	void _APICALL _V3DTo3IDEF(double *,_int32 *);
	void _APICALL _V3DTTo3IDEF(double *,_int32 *);
	void _APICALL _V3DTo3FDEF(double *,float *);
	void _APICALL _V4DTo4BDEF(double *,char *);
	void _APICALL _V4DTo4IDEF(double *,_int32 *);
	void _APICALL _V4DTTo4IDEF(double *,_int32 *);
	void _APICALL _V4DTo4FDEF(double *,float *);

	void _APICALL _V2FInvDEF(float *,float *);
	void _APICALL _V3FInvDEF(float *,float *);
	void _APICALL _V4FInvDEF(float *,float *);
	void _APICALL _V2DInvDEF(double *,double *);
	void _APICALL _V3DInvDEF(double *,double *);
	void _APICALL _V4DInvDEF(double *,double *);

	void _FASTCALL _V2FInvDEF_CPP(float *,float *);
	void _FASTCALL _V3FInvDEF_CPP(float *,float *);
	void _FASTCALL _V4FInvDEF_CPP(float *,float *);
	void _FASTCALL _V2DInvDEF_CPP(double *,double *);
	void _FASTCALL _V3DInvDEF_CPP(double *,double *);
	void _FASTCALL _V4DInvDEF_CPP(double *,double *);

	void _APICALL _V2FAbsDEF(float *,float *);
	void _APICALL _V3FAbsDEF(float *,float *);
	void _APICALL _V4FAbsDEF(float *,float *);
	void _APICALL _V2DAbsDEF(double *,double *);
	void _APICALL _V3DAbsDEF(double *,double *);
	void _APICALL _V4DAbsDEF(double *,double *);

	void _FASTCALL _V2FAbsDEF_CPP(float *,float *);
	void _FASTCALL _V3FAbsDEF_CPP(float *,float *);
	void _FASTCALL _V4FAbsDEF_CPP(float *,float *);
	void _FASTCALL _V2DAbsDEF_CPP(double *,double *);
	void _FASTCALL _V3DAbsDEF_CPP(double *,double *);
	void _FASTCALL _V4DAbsDEF_CPP(double *,double *);

	void _APICALL _V2FMinMaxDEF(float *,float *,float *);
	void _APICALL _V3FMinMaxDEF(float *,float *,float *);
	void _APICALL _V4FMinMaxDEF(float *,float *,float *);
	void _APICALL _V2DMinMaxDEF(double *,double *,double *);
	void _APICALL _V3DMinMaxDEF(double *,double *,double *);
	void _APICALL _V4DMinMaxDEF(double *,double *,double *);

	void _APICALL _V2IAddDEF(_int32 *,_int32 *,_int32 *);
	void _APICALL _V3IAddDEF(_int32 *,_int32 *,_int32 *);
	void _APICALL _V4IAddDEF(_int32 *,_int32 *,_int32 *);
	void _APICALL _V2FAddDEF(float *,float *,float *);
	void _APICALL _V3FAddDEF(float *,float *,float *);
	void _APICALL _V4FAddDEF(float *,float *,float *);
	void _APICALL _V2LAddDEF(_int64 *,_int64 *,_int64 *);
	void _APICALL _V2DAddDEF(double *,double *,double *);
	void _APICALL _V3DAddDEF(double *,double *,double *);
	void _APICALL _V4DAddDEF(double *,double *,double *);

	void _FASTCALL _V2IAddDEF_CPP(_int32 *, _int32 *, _int32 *);
	void _FASTCALL _V3IAddDEF_CPP(_int32 *, _int32 *, _int32 *);
	void _FASTCALL _V4IAddDEF_CPP(_int32 *, _int32 *, _int32 *);
	void _FASTCALL _V2FAddDEF_CPP(float *,float *,float *);
	void _FASTCALL _V3FAddDEF_CPP(float *,float *,float *);
	void _FASTCALL _V4FAddDEF_CPP(float *,float *,float *);
	void _FASTCALL _V2LAddDEF_CPP(_int64 *,_int64 *,_int64 *);
	void _FASTCALL _V2DAddDEF_CPP(double *,double *,double *);
	void _FASTCALL _V3DAddDEF_CPP(double *,double *,double *);
	void _FASTCALL _V4DAddDEF_CPP(double *,double *,double *);

	void _APICALL _V2ISubDEF(_int32 *,_int32 *,_int32 *);
	void _APICALL _V3ISubDEF(_int32 *,_int32 *,_int32 *);
	void _APICALL _V4ISubDEF(_int32 *,_int32 *,_int32 *);
	void _APICALL _V2FSubDEF(float *,float *,float *);
	void _APICALL _V3FSubDEF(float *,float *,float *);
	void _APICALL _V4FSubDEF(float *,float *,float *);
	void _APICALL _V2LSubDEF(_int64 *,_int64 *,_int64 *);
	void _APICALL _V2DSubDEF(double *,double *,double *);
	void _APICALL _V3DSubDEF(double *,double *,double *);
	void _APICALL _V4DSubDEF(double *,double *,double *);

	void _FASTCALL _V2FSubDEF_CPP(float *,float *,float *);
	void _FASTCALL _V3FSubDEF_CPP(float *,float *,float *);
	void _FASTCALL _V4FSubDEF_CPP(float *,float *,float *);
	void _FASTCALL _V2DSubDEF_CPP(double *,double *,double *);
	void _FASTCALL _V3DSubDEF_CPP(double *,double *,double *);
	void _FASTCALL _V4DSubDEF_CPP(double *,double *,double *);

	void _APICALL _V2IScaleDEF(_int32 *,_int32 *,float);
	void _APICALL _V3IScaleDEF(_int32 *,_int32 *,float);
	void _APICALL _V4IScaleDEF(_int32 *,_int32 *,float);
	void _APICALL _V2FScaleDEF(float *,float *,float);
	void _APICALL _V3FScaleDEF(float *,float *,float);
	void _APICALL _V4FScaleDEF(float *,float *,float);
	void _APICALL _V2LScaleDEF(_int64 *,_int64 *,double);
	void _APICALL _V2DScaleDEF(double *,double *,double);
	void _APICALL _V3DScaleDEF(double *,double *,double);
	void _APICALL _V4DScaleDEF(double *,double *,double);

	void _FASTCALL _V2FScaleDEF_CPP(float *,float *,float);
	void _FASTCALL _V3FScaleDEF_CPP(float *,float *,float);
	void _FASTCALL _V4FScaleDEF_CPP(float *,float *,float);
	void _FASTCALL _V2DScaleDEF_CPP(double *,double *,double);
	void _FASTCALL _V3DScaleDEF_CPP(double *,double *,double);
	void _FASTCALL _V4DScaleDEF_CPP(double *,double *,double);

	void _APICALL _V2IMulDEF(_int32 *,_int32 *,_int32 *);
	void _APICALL _V3IMulDEF(_int32 *,_int32 *,_int32 *);
	void _APICALL _V4IMulDEF(_int32 *,_int32 *,_int32 *);
	void _APICALL _V2FMulDEF(float *,float *,float *);
	void _APICALL _V3FMulDEF(float *,float *,float *);
	void _APICALL _V4FMulDEF(float *,float *,float *);
	void _APICALL _V2DMulDEF(double *,double *,double *);
	void _APICALL _V3DMulDEF(double *,double *,double *);
	void _APICALL _V4DMulDEF(double *,double *,double *);

	void _FASTCALL _V2FMulDEF_CPP(float *,float *,float *);
	void _FASTCALL _V3FMulDEF_CPP(float *,float *,float *);
	void _FASTCALL _V4FMulDEF_CPP(float *,float *,float *);
	void _FASTCALL _V2DMulDEF_CPP(double *,double *,double *);
	void _FASTCALL _V3DMulDEF_CPP(double *,double *,double *);
	void _FASTCALL _V4DMulDEF_CPP(double *,double *,double *);

	void _APICALL _V2FDivDEF(float *,float *,float *);
	void _APICALL _V3FDivDEF(float *,float *,float *);
	void _APICALL _V4FDivDEF(float *,float *,float *);
	void _APICALL _V2DDivDEF(double *,double *,double *);
	void _APICALL _V3DDivDEF(double *,double *,double *);
	void _APICALL _V4DDivDEF(double *,double *,double *);

	void _APICALL _V2Fmul2NTruncDEF(float * _a,_int32 * _b,_int32 _c);
	void _APICALL _V3Fmul2NTruncDEF(float * _a,_int32 * _b,_int32 _c);
	void _APICALL _V4Fmul2NTruncDEF(float * _a,_int32 * _b,_int32 _c);
	void _APICALL _V2Dmul2NTruncDEF(double * _a,_int32 * _b,_int32 _c);
	void _APICALL _V3Dmul2NTruncDEF(double * _a,_int32 * _b,_int32 _c);
	void _APICALL _V4Dmul2NTruncDEF(double * _a,_int32 * _b,_int32 _c);

	void _APICALL _V2Fmul2NRoundDEF(float * _a,_int32 * _b,_int32 _c);
	void _APICALL _V3Fmul2NRoundDEF(float * _a,_int32 * _b,_int32 _c);
	void _APICALL _V4Fmul2NRoundDEF(float * _a,_int32 * _b,_int32 _c);
	void _APICALL _V2Dmul2NRoundDEF(double * _a,_int32 * _b,_int32 _c);
	void _APICALL _V3Dmul2NRoundDEF(double * _a,_int32 * _b,_int32 _c);
	void _APICALL _V4Dmul2NRoundDEF(double * _a,_int32 * _b,_int32 _c);

	void _APICALL _V2Imul2NDEF(_int32 * _a,_int32 * _b,_int32 _c);
	void _APICALL _V3Imul2NDEF(_int32 * _a,_int32 * _b,_int32 _c);
	void _APICALL _V4Imul2NDEF(_int32 * _a,_int32 * _b,_int32 _c);
	void _APICALL _V2Fmul2NDEF(float * _a,float * _b,_int32 _c);
	void _APICALL _V3Fmul2NDEF(float * _a,float * _b,_int32 _c);
	void _APICALL _V4Fmul2NDEF(float * _a,float * _b,_int32 _c);
	void _APICALL _V2Dmul2NDEF(double * _a,double * _b,_int32 _c);
	void _APICALL _V3Dmul2NDEF(double * _a,double * _b,_int32 _c);
	void _APICALL _V4Dmul2NDEF(double * _a,double * _b,_int32 _c);

	void _APICALL _V2FScaleModDEF(float * _a,float * _b,float _c);
	void _APICALL _V3FScaleModDEF(float * _a,float * _b,float _c);
	void _APICALL _V4FScaleModDEF(float * _a,float * _b,float _c);
	void _APICALL _V3DScaleModDEF(double * _a,double * _b,double _c);
	void _APICALL _V4DScaleModDEF(double * _a,double * _b,double _c);

	float _APICALL _V2FDotDEF(float *,float *);
	float _APICALL _V3FDotDEF(float *,float *);
	float _APICALL _V4FDotDEF(float *,float *);
	double _APICALL _V2DDotDEF(double *,double *);
	double _APICALL _V3DDotDEF(double *,double *);
	double _APICALL _V4DDotDEF(double *,double *);

	float _FASTCALL _V2FDotDEF_CPP(float *,float *);
	float _FASTCALL _V3FDotDEF_CPP(float *,float *);
	float _FASTCALL _V4FDotDEF_CPP(float *,float *);
	double _FASTCALL _V2DDotDEF_CPP(double *,double *);
	double _FASTCALL _V3DDotDEF_CPP(double *,double *);
	double _FASTCALL _V4DDotDEF_CPP(double *,double *);

	_int32 _APICALL _V2ILength2DEF(_int32 *);
	float _APICALL _V2FLength2DEF(float *);
	float _APICALL _V3FLength2DEF(float *);
	float _APICALL _V4FLength2DEF(float *);
	_int64 _APICALL _V2LLength2DEF(_int64 *_a);
	double _APICALL _V2DLength2DEF(double *);
	double _APICALL _V3DLength2DEF(double *);
	double _APICALL _V4DLength2DEF(double *);

	float _FASTCALL _V2FLength2DEF_CPP(float *);
	float _FASTCALL _V3FLength2DEF_CPP(float *);
	float _FASTCALL _V4FLength2DEF_CPP(float *);
	double _FASTCALL _V2DLength2DEF_CPP(double *);
	double _FASTCALL _V3DLength2DEF_CPP(double *);
	double _FASTCALL _V4DLength2DEF_CPP(double *);

	_int32 _APICALL _V2ICrossDEF(_int32 * _a,_int32 * _b);
	float _APICALL _V2FCrossDEF(float * _a,float * _b);
	void _APICALL _V3FCrossDEF(float * _a,float * _b,float * _c);
	_int64 _APICALL _V2LCrossDEF(_int64 * _a,_int64 * _b);
	double _APICALL _V2DCrossDEF(double * _a,double * _b);
	void _APICALL _V3DCrossDEF(double * _a,double * _b,double * _c);

	_int32 _FASTCALL _V2ICrossDEF_CPP(_int32 * _a,_int32 * _b);
	float _FASTCALL _V2FCrossDEF_CPP(float * _a,float * _b);
	void _FASTCALL _V3FCrossDEF_CPP(float * _a,float * _b,float * _c);
	_int64 _FASTCALL _V2LCrossDEF_CPP(_int64 * _a,_int64 * _b);
	double _FASTCALL _V2DCrossDEF_CPP(double * _a,double * _b);
	void _FASTCALL _V3DCrossDEF_CPP(double * _a,double * _b,double * _c);

	void _APICALL _V2INormalMul2NDEF(_int32 *,_int32 *,_int32);
	void _APICALL _V3INormalMul2NDEF(_int32 *,_int32 *,_int32);
	void _APICALL _V4INormalMul2NDEF(_int32 *,_int32 *,_int32);

	void _APICALL _V2FNormalDEF(float *,float *);
	void _APICALL _V3FNormalDEF(float *,float *);
	void _APICALL _V4FNormalDEF(float *,float *);
	void _APICALL _V2DNormalDEF(double *,double *);
	void _APICALL _V3DNormalDEF(double *,double *);
	void _APICALL _V4DNormalDEF(double *,double *);

	void _FASTCALL _V2FNormDEF_CPP(float *,float *);
	void _FASTCALL _V3FNormDEF_CPP(float *,float *);
	void _FASTCALL _V4FNormDEF_CPP(float *,float *);
	void _FASTCALL _V2DNormDEF_CPP(double *,double *);
	void _FASTCALL _V3DNormDEF_CPP(double *,double *);
	void _FASTCALL _V4DNormDEF_CPP(double *,double *);

	void _APICALL _V2FFastNormalDEF(float * _a,float * _b);
	void _APICALL _V3FFastNormalDEF(float * _a,float * _b);
	void _APICALL _V4FFastNormalDEF(float * _a,float * _b);
	void _APICALL _V2DFastNormalDEF(double * _a,double * _b);
	void _APICALL _V3DFastNormalDEF(double * _a,double * _b);
	void _APICALL _V4DFastNormalDEF(double * _a,double * _b);

	void _APICALL _V2FLerpDEF(float *,float *,float *,float);
	void _APICALL _V3FLerpDEF(float *,float *,float *,float);
	void _APICALL _V4FLerpDEF(float *,float *,float *,float);
	void _APICALL _V2DLerpDEF(double *,double *,double *,double);
	void _APICALL _V3DLerpDEF(double *,double *,double *,double);
	void _APICALL _V4DLerpDEF(double *,double *,double *,double);

	void _APICALL _V2FCombineDEF(float *,float *,float *,float ,float);
	void _APICALL _V3FCombineDEF(float *,float *,float *,float ,float);
	void _APICALL _V4FCombineDEF(float *,float *,float *,float ,float);
	void _APICALL _V2DCombineDEF(double *,double *,double *,double ,double);
	void _APICALL _V3DCombineDEF(double *,double *,double *,double ,double);
	void _APICALL _V4DCombineDEF(double *,double *,double *,double ,double);

	_int32 _APICALL _V2IQDFLDEF(_int32 *,_int32 *,_int32 *);
	float _APICALL _V2FQDFLDEF(float *,float *,float *);
	_int64 _APICALL _V2LQDFLDEF(_int64 *,_int64 *,_int64 *);
	double _APICALL _V2DQDFLDEF(double *,double *,double *);

	void _APICALL _V2FReflectDEF(float *,float *,float *);
	void _APICALL _V2DReflectDEF(double *,double *,double *);
	void _APICALL _V3FReflectDEF(float *,float *,float *);
	void _APICALL _V3DReflectDEF(double *,double *,double *);

	float _APICALL _V2FAngleDEF(float * _a,float * _b);
	float _APICALL _V3FAngleDEF(float * _a,float * _b);
	double _APICALL _V2DAngleDEF(double * _a,double * _b);
	double _APICALL _V3DAngleDEF(double * _a,double * _b);

	float _APICALL _V3FDPFRDEF(float * _a,float * _b,float * _c,float * _d);
	double _APICALL _V3DDPFRDEF(double * _a,double * _b,double * _c,double * _d);

	void _APICALL _V3FTriNormDEF(float * _a,float * _b,float * _c,float * _d);
	void _APICALL _V3DTriNormDEF(double * _a,double * _b,double * _c,double * _d);

	void _APICALL _V3FAddTriNormDEF(float * _a,float * _b,float * _c,_int32 off);
	void _APICALL _V3FAdd3DTriNormDEF(double * _a,double * _b,double * _c,_int32 off);
	void _APICALL _V3DAddTriNormDEF(double * _a,double * _b,double * _c,_int32 off);

	void _APICALL _V4FQuaternionDEF(float *,float *);
	void _APICALL _V4DQuaternionDEF(double *,double *);
	
	void _APICALL _V4FFastQuaternionDEF(float *,float *);
	void _APICALL _V4DFastQuaternionDEF(double *,double *);

	void _APICALL _V2ITransformDEF(_int32 *,void *,_int32 *);
	void _APICALL _V2FTransformDEF(float *,void *,float *);
	void _APICALL _V3FTransformDEF(float *,void *,float *);
	void _APICALL _V4FTransformDEF(float *,void *,float *);
	void _APICALL _V2DTransformDEF(double *,void *,double *);
	void _APICALL _V3DTransformDEF(double *,void *,double *);
	void _APICALL _V4DTransformDEF(double *,void *,double *);

	void _APICALL _V2FMMulDEF(float *,void *,float *);
	void _APICALL _V3FMMulDEF(float *,void *,float *);
	void _APICALL _V2DMMulDEF(double *,void *,double *);
	void _APICALL _V3DMMulDEF(double *,void *,double *);

	_int32 _APICALL _V2FProjDEF(float *_a,void *_b,float *_c,float *_d,float *_e);
	_int32 _APICALL _V3FProjDEF(float *_a,void *_b,float *_c,float *_d,float *_e);
	_int32 _APICALL _V4FProjDEF(float *_a,void *_b,float *_c,float *_d,float *_e);
	_int32 _APICALL _V2DProjDEF(double *_a,void *_b,double *_c,double *_d,double *_e);
	_int32 _APICALL _V3DProjDEF(double *_a,void *_b,double *_c,double *_d,double *_e);
	_int32 _APICALL _V4DProjDEF(double *_a,void *_b,double *_c,double *_d,double *_e);

	void _APICALL _Q4FVectorDEF(float * _a,float * _b);
	void _APICALL _Q4DVectorDEF(double * _a,double * _b);

	void _APICALL _QFInvDEF(float *,float *);
	void _APICALL _QDInvDEF(double *,double *);
	void _FASTCALL _QFInvDEF_CPP(float *,float *);
	void _FASTCALL _QDInvDEF_CPP(double *,double *);

	void _APICALL _QFMulDEF(float *,float *,float *);
	void _APICALL _QDMulDEF(double *,double *,double *);
	void _FASTCALL _QFMulDEF_CPP(float *,float *,float *);
	void _FASTCALL _QDMulDEF_CPP(double *,double *,double *);

	void _APICALL _QFEulerDEF(float * _a,float * _b);
	void _APICALL _QDEulerDEF(double * _a,double * _b);

	void _APICALL _Q4FMatrixDEF(float *,float *);
	void _APICALL _Q4DMatrixDEF(double *,double *);
	void _FASTCALL _Q4FMatrixDEF_CPP(float *,float *);
	void _FASTCALL _Q4DMatrixDEF_CPP(double *,double *);

	void _APICALL _V2FAfineTransformDEF(float *,float *,float *);
	void _APICALL _V2DAfineTransformDEF(double *,double *,double *);

	void _APICALL _Q2FInvTransformDEF(float *,float *,float *);
	void _APICALL _Q2DInvTransformDEF(double *,double *,double *);
	void _APICALL _Q3FInvTransformDEF(float *,float *,float *);
	void _APICALL _Q3DInvTransformDEF(double *,double *,double *);
	void _FASTCALL _Q3FInvTransformDEF_CPP(float *,float *,float *);
	void _FASTCALL _Q3DInvTransformDEF_CPP(double *,double *,double *);

	void _APICALL _M4FTransposeDEF(void *,void *);
	void _APICALL _M4DTransposeDEF(void *,void *);

	void _APICALL _M4FMulDEF(void *,void *,void *);
	void _APICALL _M4DMulDEF(void *,void *,void *);

	_int32 _APICALL _M4FInvDEF(void *_a,void *_b);
	_int32 _APICALL _M4DInvDEF(void *_a,void *_b);

	void _APICALL _M4FPerspectiveDEF(void *,_int32,_int32,float,float,float);
	void _APICALL _M4DPerspectiveDEF(void *,_int32,_int32,double,double,double);
	void _APICALL _M4FOrtographicDEF(void *,_int32,_int32,float,float,float);
	void _APICALL _M4DOrtographicDEF(void *,_int32,_int32,double,double,double);

	void _APICALL _M4FIdentityDEF(void *_m);
	void _APICALL _M4DIdentityDEF(void *_m);

	void _APICALL _M4FQuaternionDEF(float * _a,float * _b);
	void _APICALL _M4DQuaternionDEF(double * _a,double * _b);

	void _APICALL _M4FTranslateDEF(void *_m,float *v);
	void _APICALL _M4DTranslateDEF(void *_m,double *v);

	void _APICALL _M4FScaleDEF(void *_m,float *v);
	void _APICALL _M4DScaleDEF(void *_m,double *v);

	void _APICALL _M4FTRSDEF(void * _m,float * _a,float * _b,float * _c);
	void _APICALL _M4DTRSDEF(void * _m,double * _a,double * _b,double * _c);

	void _APICALL _M4FTo4DDEF(void *_mf,void *_md);
	void _APICALL _M4DTo4FDEF(void *_md,void *_mf);

	void _APICALL _M4FAddTranslateDEF(void *_ma,float *v,void *_mb);
	void _APICALL _M4DAddTranslateDEF(void *_ma,double *v,void *_mb);

	void _APICALL _M4FAddScaleDEF(void *_ma,float *v,void *_mb);
	void _APICALL _M4DAddScaleDEF(void *_ma,double *v,void *_mb);

	void _APICALL _M4FAddRotateDEF(void * _a,float * _b,void * _c);
	void _APICALL _M4DAddRotateDEF(void * _a,double * _b,void * _c);

OPTIMIZE_OFF;
}

#endif
