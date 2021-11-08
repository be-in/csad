/*
 * x86vector.h
 *
 *  Created on: 18.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef X86VECTOR_H_
#define X86VECTOR_H_

#include <bt.h>

#ifdef CPU_X86_32

namespace bt {

	void _APICALL _V2FTo2IFPU(float *,int *);
	void _APICALL _V3FTo3IFPU(float *,int *);
	void _APICALL _V4FTo4IFPU(float *,int *);
	void _APICALL _V2DTo2IFPU(double *,int *);
	void _APICALL _V3DTo3IFPU(double *,int *);
	void _APICALL _V4DTo4IFPU(double *,int *);

	void _APICALL _V2FAbsFPU(float * _a,float * _b);
	void _APICALL _V3FAbsFPU(float * _a,float * _b);
	void _APICALL _V4FAbsFPU(float * _a,float * _b);
	void _APICALL _V2DAbsFPU(double * _a,double * _b);
	void _APICALL _V3DAbsFPU(double * _a,double * _b);
	void _APICALL _V4DAbsFPU(double * _a,double * _b);

	void _APICALL _V2FAddFPU(float *,float *,float *);
	void _APICALL _V3FAddFPU(float *,float *,float *);
	void _APICALL _V4FAddFPU(float *,float *,float *);
	void _APICALL _V2DAddFPU(double *,double *,double *);
	void _APICALL _V3DAddFPU(double *,double *,double *);
	void _APICALL _V4DAddFPU(double *,double *,double *);

	void _APICALL _V2FSubFPU(float *,float *,float *);
	void _APICALL _V3FSubFPU(float *,float *,float *);
	void _APICALL _V4FSubFPU(float *,float *,float *);
	void _APICALL _V2DSubFPU(double *,double *,double *);
	void _APICALL _V3DSubFPU(double *,double *,double *);
	void _APICALL _V4DSubFPU(double *,double *,double *);

	void _APICALL _V2FScaleFPU(float *,float *,float);
	void _APICALL _V3FScaleFPU(float *,float *,float);
	void _APICALL _V4FScaleFPU(float *,float *,float);
	void _APICALL _V2DScaleFPU(double *,double *,double);
	void _APICALL _V3DScaleFPU(double *,double *,double);
	void _APICALL _V4DScaleFPU(double *,double *,double);

	void _APICALL _V2FMulFPU(float *,float *,float*);
	void _APICALL _V3FMulFPU(float *,float *,float*);
	void _APICALL _V4FMulFPU(float *,float *,float*);
	void _APICALL _V2DMulFPU(double *,double *,double *);
	void _APICALL _V3DMulFPU(double *,double *,double *);
	void _APICALL _V4DMulFPU(double *,double *,double *);

	void _APICALL _V2Fmul2NTruncFPU(float *,int *,int);
	void _APICALL _V3Fmul2NTruncFPU(float *,int *,int);
	void _APICALL _V4Fmul2NTruncFPU(float *,int *,int);
	void _APICALL _V2Dmul2NTruncFPU(double *,int *,int);
	void _APICALL _V3Dmul2NTruncFPU(double *,int *,int);
	void _APICALL _V4Dmul2NTruncFPU(double *,int *,int);

	void _APICALL _V2Fmul2NRoundFPU(float *,int *,int);
	void _APICALL _V3Fmul2NRoundFPU(float *,int *,int);
	void _APICALL _V4Fmul2NRoundFPU(float *,int *,int);
	void _APICALL _V2Dmul2NRoundFPU(double *,int *,int);
	void _APICALL _V3Dmul2NRoundFPU(double *,int *,int);
	void _APICALL _V4Dmul2NRoundFPU(double *,int *,int);

	void _APICALL _V2Fmul2NFPU(float *,float *,int);
	void _APICALL _V3Fmul2NFPU(float *,float *,int);
	void _APICALL _V4Fmul2NFPU(float *,float *,int);
	void _APICALL _V2Dmul2NFPU(double *,double *,int);
	void _APICALL _V3Dmul2NFPU(double *,double *,int);
	void _APICALL _V4Dmul2NFPU(double *,double *,int);

	float _APICALL _V2FDotFPU(float *,float *);
	float _APICALL _V3FDotFPU(float *,float *);
	float _APICALL _V4FDotFPU(float *,float *);
	double _APICALL _V2DDotFPU(double *,double *);
	double _APICALL _V3DDotFPU(double *,double *);
	double _APICALL _V4DDotFPU(double *,double *);

	float _APICALL _V2FLength2FPU(float *);
	float _APICALL _V3FLength2FPU(float *);
	float _APICALL _V4FLength2FPU(float *);
	double _APICALL _V2DLength2FPU(double *);
	double _APICALL _V3DLength2FPU(double *);

	void _APICALL _V3FCrossFPU(float *,float *,float *);
	void _APICALL _V3DCrossFPU(double *,double *,double *);

	void _APICALL _V2FNormalFPU(float *,float *);
	void _APICALL _V3FNormalFPU(float *,float *);
	void _APICALL _V4FNormalFPU(float *,float *);
	void _APICALL _V2DNormalFPU(double *,double *);
	void _APICALL _V3DNormalFPU(double *,double *);
	void _APICALL _V4DNormalFPU(double *,double *);

	void _APICALL _V2FLerpFPU(float * _a,float * _b,float * _c,float _d);
	void _APICALL _V3FLerpFPU(float * _a,float * _b,float * _c,float _d);
	void _APICALL _V4FLerpFPU(float * _a,float * _b,float * _c,float _d);
	void _APICALL _V2DLerpFPU(double * _a,double * _b,double * _c,double _d);
	void _APICALL _V3DLerpFPU(double * _a,double * _b,double * _c,double _d);
	void _APICALL _V4DLerpFPU(double * _a,double * _b,double * _c,double _d);

	void _APICALL _V2FCombineFPU(float *a,float *b,float *c,float d,float e);
	void _APICALL _V3FCombineFPU(float *a,float *b,float *c,float d,float e);
	void _APICALL _V4FCombineFPU(float *a,float *b,float *c,float d,float e);
	void _APICALL _V2DCombineFPU(double *,double *,double *,double ,double );
	void _APICALL _V3DCombineFPU(double *,double *,double *,double ,double );
	void _APICALL _V4DCombineFPU(double *,double *,double *,double ,double );

	float _APICALL _V2FAngleFPU(float * _a,float * _b);
	float _APICALL _V3FAngleFPU(float * _a,float * _b);
	double _APICALL _V2DAngleFPU(double * _a,double * _b);
	double _APICALL _V3DAngleFPU(double * _a,double * _b);

	void _APICALL _V3FAddTriNormFPU(float *a,float *b,float *c,int off);
	void _APICALL _V3FAdd3DTriNormFPU(double *a,double *b,double *c,int off);
	void _APICALL _V3DAddTriNormFPU(double *a,double *b,double *c,int off);

	void _APICALL _V4FQuaternionFPU(float *,float *);
	void _APICALL _V4DQuaternionFPU(double *,double *);

	void _APICALL _V2FTransformFPU(float *,void *,float *);
	void _APICALL _V3FTransformFPU(float *,void *,float *);
	void _APICALL _V4FTransformFPU(float *,void *,float *);

	void _APICALL _V2FMMulFPU(float *,void *,float *);

	int _APICALL _V3FProjFPU(float *_a,void *_b,float *_c,float *_d,float *_e);

	void _APICALL _Q4FMatrixFPU(float *,float *);
	void _APICALL _Q4DMatrixFPU(double *,double *);

	void _APICALL _V2BTo2FSSE(char *,float *);
	void _APICALL _V3BTo3FSSE(char *,float *);
	void _APICALL _V4BTo4FSSE(char *,float *);
	void _APICALL _V2ITo2FSSE(int *,float *);
	void _APICALL _V3ITo3FSSE(int *,float *);
	void _APICALL _V4ITo4FSSE(int *,float *);
	void _APICALL _V2FTo2BSSE(float *,char *);
	void _APICALL _V3FTo3BSSE(float *,char *);
	void _APICALL _V4FTo4BSSE(float *,char *);
	void _APICALL _V2FTo2ISSE(float *,int *);
	void _APICALL _V3FTo3ISSE(float *,int *);
	void _APICALL _V4FTo4ISSE(float *,int *);
	void _APICALL _V2FTTo2ISSE(float *,int *);
	void _APICALL _V3FTTo3ISSE(float *,int *);
	void _APICALL _V4FTTo4ISSE(float *,int *);

	void _APICALL _V2FInvSSE(float * _a,float * _b);
	void _APICALL _V3FInvSSE(float * _a,float * _b);
	void _APICALL _V4FInvSSE(float * _a,float * _b);
	void _APICALL _V2DInvSSE(double * _a,double * _b);
	void _APICALL _V3DInvSSE(double * _a,double * _b);
	void _APICALL _V4DInvSSE(double * _a,double * _b);

	void _APICALL _V3DAbsSSE(double * _a,double * _b);
	void _APICALL _V4DAbsSSE(double * _a,double * _b);

	void _APICALL _V2FAddSSE(float *,float *,float *);
	void _APICALL _V3FAddSSE(float *,float *,float *);
	void _APICALL _V4FAddSSE(float *,float *,float *);

	void _APICALL _V2FSubSSE(float *,float *,float *);
	void _APICALL _V3FSubSSE(float *,float *,float *);
	void _APICALL _V4FSubSSE(float *,float *,float *);

	void _APICALL _V2FScaleSSE(float *,float *,float);
	void _APICALL _V3FScaleSSE(float *,float *,float);
	void _APICALL _V4FScaleSSE(float *,float *,float);

	void _APICALL _V2FMulSSE(float *,float *,float *);
	void _APICALL _V3FMulSSE(float *,float *,float *);
	void _APICALL _V4FMulSSE(float *,float *,float *);

	void _APICALL _V2FDivSSE(float *,float *,float *);
	void _APICALL _V3FDivSSE(float *,float *,float *);
	void _APICALL _V4FDivSSE(float *,float *,float *);

	float _APICALL _V4FDotSSE(float *,float *);

	float _APICALL _V4FLength2SSE(float *);

	void _APICALL _V3FCrossSSE(float *,float *,float *);

	void _APICALL _V2FNormalSSE(float *,float *);
	void _APICALL _V3FNormalSSE(float *,float *);
	void _APICALL _V4FNormalSSE(float *,float *);

	void _APICALL _V2FFastNormalSSE(float *,float *);
	void _APICALL _V3FFastNormalSSE(float *,float *);
	void _APICALL _V4FFastNormalSSE(float *,float *);

	void _APICALL _V2FLerpSSE(float * _a,float * _b,float * _c,float _d);
	void _APICALL _V3FLerpSSE(float * _a,float * _b,float * _c,float _d);
	void _APICALL _V4FLerpSSE(float * _a,float * _b,float * _c,float _d);

	void _APICALL _V2FCombineSSE(float *,float *,float *,float ,float );
	void _APICALL _V3FCombineSSE(float *,float *,float *,float ,float );
	void _APICALL _V4FCombineSSE(float *,float *,float *,float ,float );

	float _APICALL _V3FAngleSSE(float * _a,float * _b);

	void _APICALL _V3FAddTriNormSSE(float *a,float *b,float *c,int off);

	void _APICALL _V4FQuaternionSSE(float *,float *);
	void _APICALL _V4FFastQuaternionSSE(float *,float *);

	void _APICALL _V2FTransformSSE(float *,void *,float *);
	void _APICALL _V3FTransformSSE(float *,void *,float *);
	void _APICALL _V4FTransformSSE(float *,void *,float *);

	void _APICALL _V2FMMulSSE(float *,void *,float *);
	void _APICALL _V3FMMulSSE(float *,void *,float *);

	int _APICALL _V3FProjSSE(float *_a,void *_b,float *_c,float *_d,float *_e);

	void _APICALL _V2BTo2DSSE2(char *,double *);
	void _APICALL _V3BTo3DSSE2(char *,double *);
	void _APICALL _V4BTo4DSSE2(char *,double *);
	void _APICALL _V2FTo2ISSE2(float *,_int32 *);
	void _APICALL _V3FTo3ISSE2(float *,_int32 *);
	void _APICALL _V4FTo4ISSE2(float *,_int32 *);
	void _APICALL _V2FTTo2ISSE2(float *,_int32 *);
	void _APICALL _V3FTTo3ISSE2(float *,_int32 *);
	void _APICALL _V4FTTo4ISSE2(float *,_int32 *);
	void _APICALL _V2FTo2DSSE2(float *,double *);
	void _APICALL _V3FTo3DSSE2(float *,double *);
	void _APICALL _V4FTo4DSSE2(float *,double *);
	void _APICALL _V2DTo2ISSE2(double *,_int32 *);
	void _APICALL _V3DTo3ISSE2(double *,_int32 *);
	void _APICALL _V4DTo4ISSE2(double *,_int32 *);
	void _APICALL _V2DTTo2ISSE2(double *,_int32 *);
	void _APICALL _V3DTTo3ISSE2(double *,_int32 *);
	void _APICALL _V4DTTo4ISSE2(double *,_int32 *);
	void _APICALL _V2DTo2FSSE2(double *,float *);
	void _APICALL _V3DTo3FSSE2(double *,float *);
	void _APICALL _V4DTo4FSSE2(double *,float *);

	void _APICALL _V2FAbsSSE2(float *_a,float *_b);
	void _APICALL _V3FAbsSSE2(float *_a,float *_b);
	void _APICALL _V4FAbsSSE2(float *_a,float *_b);
	void _APICALL _V2DAbsSSE2(double *_a,double *_b);
	void _APICALL _V3DAbsSSE2(double *_a,double *_b);
	void _APICALL _V4DAbsSSE2(double *_a,double *_b);

	void _APICALL _V2FMinMaxSSE2(float *,float *,float *);
	void _APICALL _V3FMinMaxSSE2(float *,float *,float *);
	void _APICALL _V4FMinMaxSSE2(float *,float *,float *);
	void _APICALL _V2DMinMaxSSE2(double *,double *,double *);

	void _APICALL _V2IAddSSE2(int *,int *,int *);
	void _APICALL _V3IAddSSE2(int *,int *,int *);
	void _APICALL _V4IAddSSE2(int *,int *,int *);

	void _APICALL _V2FAddSSE2(float *,float *,float *);
	void _APICALL _V3FAddSSE2(float *,float *,float *);

	void _APICALL _V2FSubSSE2(float *,float *,float *);
	void _APICALL _V4FSubSSE2(float *,float *,float *);
	void _APICALL _V3DSubSSE2(double *,double *,double *);
	void _APICALL _V4DSubSSE2(double *,double *,double *);

	void _APICALL _V2DMulSSE2(double *,double *,double *);
	void _APICALL _V3DMulSSE2(double *,double *,double *);
	void _APICALL _V4DMulSSE2(double *,double *,double *);

	void _APICALL _V2DDivSSE2(double *,double *,double *);
	void _APICALL _V3DDivSSE2(double *,double *,double *);
	void _APICALL _V4DDivSSE2(double *,double *,double *);

	void _APICALL _V2Fmul2NTruncSSE2(float *,int *,int);
	void _APICALL _V3Fmul2NTruncSSE2(float *,int *,int);
	void _APICALL _V4Fmul2NTruncSSE2(float *,int *,int);
	void _APICALL _V2Dmul2NTruncSSE2(double *,int *,int);
	void _APICALL _V3Dmul2NTruncSSE2(double *,int *,int);
	void _APICALL _V4Dmul2NTruncSSE2(double *,int *,int);

	void _APICALL _V2Fmul2NRoundSSE2(float *,int *,int);
	void _APICALL _V3Fmul2NRoundSSE2(float *,int *,int);
	void _APICALL _V4Fmul2NRoundSSE2(float *,int *,int);
	void _APICALL _V2Dmul2NRoundSSE2(double *,int *,int);
	void _APICALL _V3Dmul2NRoundSSE2(double *,int *,int);
	void _APICALL _V4Dmul2NRoundSSE2(double *,int *,int);

	void _APICALL _V2Fmul2NSSE2(float *,float *,int);
	void _APICALL _V3Fmul2NSSE2(float *,float *,int);
	void _APICALL _V4Fmul2NSSE2(float *,float *,int);
	void _APICALL _V2Dmul2NSSE2(double *,double *,int);
	void _APICALL _V3Dmul2NSSE2(double *,double *,int);
	void _APICALL _V4Dmul2NSSE2(double *,double *,int);

	double _APICALL _V4DLength2SSE2(double *);

	void _APICALL _V3DCrossSSE2(double *,double *,double *);

	//void _STDCALL _V2DNormalSSE2(double *,double *);

	void _APICALL _V2DFastNormalSSE2(double *,double *);
	void _APICALL _V3DFastNormalSSE2(double *,double *);
	void _APICALL _V4DFastNormalSSE2(double *,double *);

	void _APICALL _V2DLerpSSE2(double * _a,double * _b,double * _c,double _d);
	void _APICALL _V3DLerpSSE2(double * _a,double * _b,double * _c,double _d);
	void _APICALL _V4DLerpSSE2(double * _a,double * _b,double * _c,double _d);
	
	void _APICALL _V2FCombineSSE2(float *,float *,float *,float ,float );
	void _APICALL _V4DCombineSSE2(double *,double *,double *,double ,double );

	void _APICALL _V3DAddTriNormSSE2(double *a,double *b,double *c,int off);

	void _APICALL _V4DQuaternionSSE2(double *,double *);
	void _APICALL _V4DFastQuaternionSSE2(double *,double *);

	void _APICALL _V2FTransformSSE2(float *,void *,float *);
	void _APICALL _V3DTransformSSE2(double *,void *,double *);

	void _APICALL _V3R64CopySSE3(void *a, void *b);
	void _APICALL _V4R64CopySSE3(void *a, void *b);

	void _APICALL _V4R32SSE3(_int32 *,_int32 *);
	void _APICALL _V4R64SSE3(_int64 *,_int64 *);

	void _APICALL _V4BTo4FSSE3(char *,float *);
	//void _STDCALL _V4FTo4BSSE3(float *,char *);
	void _APICALL _V2DTo2FSSE3(double *,float *);
	void _APICALL _V3DTo3FSSE3(double *,float *);
	void _APICALL _V4DTo4FSSE3(double *,float *);

	void _APICALL _V4FAddSSE3(float *,float *,float *);
	void _APICALL _V2DAddSSE3(double *,double *,double *);
	void _APICALL _V3DAddSSE3(double *,double *,double *);
	void _APICALL _V4DAddSSE3(double *,double *,double *);

	void _APICALL _V4FSubSSE3(float *,float *,float *);
	void _APICALL _V2DSubSSE3(double *,double *,double *);
	void _APICALL _V3DSubSSE3(double *,double *,double *);
	void _APICALL _V4DSubSSE3(double *,double *,double *);

	void _APICALL _V4IScaleSSE3(_int32 *,_int32 *,float);
	void _APICALL _V4FScaleSSE3(float *,float *,float);
	void _APICALL _V2DScaleSSE3(double *,double *,double);

	void _APICALL _V4FLerpSSE3(float * ,float * ,float * ,float );
	void _APICALL _V2DLerpSSE3(double * ,double * ,double * ,double );
	void _APICALL _V3DLerpSSE3(double * ,double * ,double * ,double );
	void _APICALL _V4DLerpSSE3(double * ,double * ,double * ,double );

	void _APICALL _V4FCombineSSE3(float *,float *,float *,float ,float );

	float _APICALL _V2FQDFLSSE3(float * _a,float * _b,float * _c);
	double _APICALL _V2DQDFLSSE3(double * _a,double * _b,double * _c);

	void _APICALL _V3FTransformSSE3(float *,void *,float *);
	void _APICALL _V4FTransformSSE3(float *,void *,float *);

	void _APICALL _V3FMMulSSE3(float *,void *,float *);

	int _APICALL _V2FProjSSE3(float *_a,void *_b,float *_c,float *_d,float *_e);
	int _APICALL _V3FProjSSE3(float *_a,void *_b,float *_c,float *_d,float *_e);
	int _APICALL _V4FProjSSE3(float *_a,void *_b,float *_c,float *_d,float *_e);

	void _APICALL _V4ITo4FSSE4(int *,float *);
	void _APICALL _V4FTo4BSSE4(float *,char *);
	void _APICALL _V4FTo4ISSE4(float *,int *);
	void _APICALL _V4FTTo4ISSE4(float *,int *);
	void _APICALL _V3FTo3DSSE4(float *,double *);

	void _APICALL _V4FAbsSSE4(float * _a,float * _b);
	void _APICALL _V2DAbsSSE4(double * _a,double * _b);
	void _APICALL _V3DAbsSSE4(double * _a,double * _b);
	void _APICALL _V4DAbsSSE4(double * _a,double * _b);

	void _APICALL _V4FMinMaxSSE4(float *,float *,float *);
	void _APICALL _V2DMinMaxSSE4(double *,double *,double *);
	void _APICALL _V3DMinMaxSSE4(double *,double *,double *);
	void _APICALL _V4DMinMaxSSE4(double *,double *,double *);

	void _APICALL _V4IAddSSE4(int *,int *,int *);
	void _APICALL _V3DAddSSE4(double *,double *,double *);
	void _APICALL _V4DAddSSE4(double *,double *,double *);

	void _APICALL _V4DSubSSE4(double *,double *,double *);

	void _APICALL _V2DScaleSSE4(double *,double *,double);
	void _APICALL _V3DScaleSSE4(double *,double *,double);
	void _APICALL _V4DScaleSSE4(double *,double *,double);

	void _APICALL _V4DMulSSE4(double *,double *,double *);

	void _APICALL _V4DDivSSE4(double *,double *,double *);

	void _APICALL _V4Fmul2NRoundSSE4(float *,int *,int);

	float _APICALL _V2FDotSSE4(float *,float *);
	float _APICALL _V3FDotSSE4(float *,float *);
	float _APICALL _V4FDotSSE4(float *,float *);
	double _APICALL _V2DDotSSE4(double *,double *);
	double _APICALL _V3DDotSSE4(double *,double *);
	double _APICALL _V4DDotSSE4(double *,double *);

	float _APICALL _V2FLength2SSE4(float *);
	float _APICALL _V3FLength2SSE4(float *);
	float _APICALL _V4FLength2SSE4(float *);
	double _APICALL _V2DLength2SSE4(double *);
	double _APICALL _V3DLength2SSE4(double *);
	double _APICALL _V4DLength2SSE4(double *);

	void _APICALL _V2FNormalSSE4(float *,float *);
	void _APICALL _V3FNormalSSE4(float *,float *);
	void _APICALL _V4FNormalSSE4(float *,float *);
	void _APICALL _V2DNormalSSE4(double *,double *);
	void _APICALL _V3DNormalSSE4(double *,double *);
	void _APICALL _V4DNormalSSE4(double *,double *);

	void _APICALL _V2FFastNormalSSE4(float *,float *);
	void _APICALL _V3FFastNormalSSE4(float *,float *);
	void _APICALL _V4FFastNormalSSE4(float *,float *);
	void _APICALL _V2DFastNormalSSE4(double *,double *);
	void _APICALL _V3DFastNormalSSE4(double *,double *);
	void _APICALL _V4DFastNormalSSE4(double *,double *);

	void _APICALL _V4FLerpSSE4(float * ,float * ,float * ,float );
	void _APICALL _V2DLerpSSE4(double * ,double * ,double * ,double );
	void _APICALL _V4DLerpSSE4(double * ,double * ,double * ,double );

	void _APICALL _V4FCombineSSE4(float *,float *,float *,float ,float );
	void _APICALL _V2DCombineSSE4(double *,double *,double *,double ,double );
	void _APICALL _V3DCombineSSE4(double *,double *,double *,double ,double );
	void _APICALL _V4DCombineSSE4(double *,double *,double *,double ,double );

	void _APICALL _V4FQuaternionSSE4(float *,float *);
	void _APICALL _V4DQuaternionSSE4(double *,double *);

	void _APICALL _V4FFastQuaternionSSE4(float *,float *);

	void _APICALL _V2DTransformSSE4(double *a,void *b,double *c);
	void _APICALL _V3DTransformSSE4(double *a,void *b,double *c);
	void _APICALL _V4DTransformSSE4(double *a,void *b,double *c);

	void _APICALL _V4DMinMaxAVX(double * ,double * ,double *);
	void _APICALL _V3DAddAVX(double * ,double * ,double *);
	void _APICALL _V4DAddAVX(double * ,double * ,double *);
	void _APICALL _V4DSubAVX(double * ,double * ,double *);
	void _APICALL _V4DScaleAVX(double *,double *,double);
	void _APICALL _V4DMulAVX(double * ,double * ,double *);
	void _APICALL _V4DDivAVX(double * ,double * ,double *);
	double _APICALL _V4DDotAVX(double * ,double * );
	void _APICALL _V4DNormalAVX(double * ,double *);
	void _APICALL _V4DLerpAVX(double * ,double * ,double * ,double );
	void _APICALL _V3DTransformAVX(double *,void *,double *);
	void _APICALL _V4DTransformAVX(double *,void *,double *);
	void _APICALL _V4DProjAVX(double * ,void *,double * ,double * ,double *);

}

#endif

#endif /* X86VECTOR_H_ */
