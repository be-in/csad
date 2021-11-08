//=============================================================================
///**
// *  @file   x86_64vector.h
// *
// *  $Id: x86_64vector.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector operations, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_X86_64_VECTOR_H_
#define GEN3_X86_64_VECTOR_H_

#include <bt.h>

#ifdef CPU_X86_64

namespace bt {

	void _APICALL _V2FAddSSE(float *a,float *b,float *c);
	void _APICALL _V3FAddSSE(float *a,float *b,float *c);
	void _APICALL _V4FAddSSE(float *a,float *b,float *c);

	void _APICALL _V2FSubSSE(float *a,float *b,float *c);
	void _APICALL _V3FSubSSE(float *a,float *b,float *c);

	void _APICALL _V2FScaleSSE(float *a, float *b, float c);
	void _APICALL _V3FScaleSSE(float *a, float *b, float c);
	void _APICALL _V4FScaleSSE(float *a, float *b, float c);

	void _APICALL _V2FMulSSE(float *a,float *b,float *c);
	void _APICALL _V3FMulSSE(float *a,float *b,float *c);

	void _APICALL _V2FDivSSE(float *a,float *b,float *c);
	void _APICALL _V3FDivSSE(float *a,float *b,float *c);

	void _APICALL _V3FCrossSSE(float *a,float *b,float *c);

	void _APICALL _V2FNormalSSE(float *a, float *b);
	void _APICALL _V3FNormalSSE(float *a, float *b);
	void _APICALL _V4FNormalSSE(float *a, float *b);

	void _APICALL _V2FFastNormalSSE(float *a, float *b);
	void _APICALL _V3FFastNormalSSE(float *a, float *b);
	void _APICALL _V4FFastNormalSSE(float *a, float *b);
	//void _STDCALL _V2DNormalSSE2(double *a, double *b);

	void _APICALL _V2FLerpSSE(float *a, float *b,float *c, float d);
	void _APICALL _V3FLerpSSE(float *a, float *b,float *c, float d);
	void _APICALL _V4FLerpSSE(float *a, float *b,float *c, float d);

	float _APICALL _V3FAngleSSE(float * _a,float * _b);

	void _APICALL _V2FTransformSSE(float *,void *,float *);
	void _APICALL _V3FTransformSSE(float *,void *,float *);
	void _APICALL _V4FTransformSSE(float *,void *,float *);

	void _APICALL _V2FMMulSSE(float *,void *,float *);
	void _APICALL _V3FMMulSSE(float *,void *,float *);

	void _APICALL _V2FAddSSE2(float *a,float *b,float *c);
	void _APICALL _V4FAddSSE2(float *a,float *b,float *c);
	void _APICALL _V2DAddSSE2(double *a,double *b,double *c);
	void _APICALL _V3DAddSSE2(double *a,double *b,double *c);
	void _APICALL _V4DAddSSE2(double *a,double *b,double *c);

	void _APICALL _V2FSubSSE2(float *a,float *b,float *c);
	void _APICALL _V4FSubSSE2(float *a,float *b,float *c);
	void _APICALL _V2DSubSSE2(double *a,double *b,double *c);
	void _APICALL _V3DSubSSE2(double *a,double *b,double *c);
	void _APICALL _V4DSubSSE2(double *a,double *b,double *c);

	void _APICALL _V2DScaleSSE2(double *a, double *b, double c);
	void _APICALL _V3DScaleSSE2(double *a, double *b, double c);
	void _APICALL _V4DScaleSSE2(double *a, double *b, double c);

	void _APICALL _V2FMulSSE2(float *a,float *b,float *c);
	void _APICALL _V4FMulSSE2(float *a,float *b,float *c);
	void _APICALL _V2DMulSSE2(double *a,double *b,double *c);
	void _APICALL _V3DMulSSE2(double *a,double *b,double *c);
	void _APICALL _V4DMulSSE2(double *a,double *b,double *c);

	void _APICALL _V2FDivSSE2(float *a,float *b,float *c);
	void _APICALL _V4FDivSSE2(float *a,float *b,float *c);
	void _APICALL _V2DDivSSE2(double *a,double *b,double *c);
	void _APICALL _V3DDivSSE2(double *a,double *b,double *c);
	void _APICALL _V4DDivSSE2(double *a,double *b,double *c);

	void _APICALL _V2DNormalSSE2(double *a, double *b);
	void _APICALL _V3DNormalSSE2(double *a, double *b);
	void _APICALL _V4DNormalSSE2(double *a, double *b);
	
	void _APICALL _V2DFastNormalSSE2(double *a, double *b);
	void _APICALL _V3DFastNormalSSE2(double *a, double *b);
	void _APICALL _V4DFastNormalSSE2(double *a, double *b);

	void _APICALL _V2DLerpSSE2(double *a, double *b,double *c, double d);
	void _APICALL _V3DLerpSSE2(double *a, double *b,double *c, double d);
	void _APICALL _V4DLerpSSE2(double *a, double *b,double *c, double d);

	void _APICALL _V2DReflectSSE2(double * _a,double * _b,double * _c);
	void _APICALL _V3DReflectSSE2(double * _a,double * _b,double * _c);

	void _APICALL _V2FTransformSSE2(float *,void *,float *);
	void _APICALL _V2DTransformSSE2(double *a,void *b,double *c);

	void _APICALL _V4R32SSE3(int *a,int *b);
	void _APICALL _V4R64SSE3(_int64 *a,_int64 *b);

	void _APICALL _V4FAddSSE3(float *a,float *b,float *c);

	float _APICALL _V3FAngleSSE3(float * _a,float * _b);

	void _APICALL _V4FAddSSE4(float *a,float *b,float *c);

	void _APICALL _V4FScaleSSE4(float *a,float *b,float c);
	void _APICALL _V2DScaleSSE4(double *a,double *b,double c);
	void _APICALL _V4DScaleSSE4(double *a,double *b,double c);

	void _APICALL _V2Fmul2NRoundSSE4(float *,int *,int);
	void _APICALL _V3Fmul2NRoundSSE4(float *,int *,int);
	void _APICALL _V4Fmul2NRoundSSE4(float *,int *,int);

	float _APICALL _V2FDotSSE4(float *a,float *b);
	float _APICALL _V3FDotSSE4(float *a,float *b);
	float _APICALL _V4FDotSSE4(float *a,float *b);
	double _APICALL _V2DDotSSE4(double *a,double *b);
	double _APICALL _V3DDotSSE4(double *a,double *b);
	double _APICALL _V4DDotSSE4(double *a,double *b);

	float _APICALL _V2FLength2SSE4(float *a);
	float _APICALL _V3FLength2SSE4(float *a);
	float _APICALL _V4FLength2SSE4(float *a);
	double _APICALL _V2DLength2SSE4(double *a);
	double _APICALL _V3DLength2SSE4(double *a);
	double _APICALL _V4DLength2SSE4(double *a);

	void _APICALL _V2FLerpSSE4(float *,float *,float *,float);
	void _APICALL _V3FLerpSSE4(float *,float *,float *,float);
	void _APICALL _V4FLerpSSE4(float *,float *,float *,float);
	void _APICALL _V2DLerpSSE4(double *,double *,double *,double);
	void _APICALL _V3DLerpSSE4(double *,double *,double *,double);
	void _APICALL _V4DLerpSSE4(double *,double *,double *,double);

	void _APICALL _V2FCombineSSE4(float *,float *,float *,float,float);
	void _APICALL _V3FCombineSSE4(float *,float *,float *,float,float);
	void _APICALL _V4FCombineSSE4(float *,float *,float *,float,float);
	void _APICALL _V2DCombineSSE4(double *,double *,double *,double,double);
	void _APICALL _V3DCombineSSE4(double *,double *,double *,double,double);
	void _APICALL _V4DCombineSSE4(double *,double *,double *,double,double);

	void _APICALL _V4FTransformSSE4(float *,void *,float *);
	void _APICALL _V2DTransformSSE4(double *,void *,double *);
	void _APICALL _V3DTransformSSE4(double *,void *,double *);
	void _APICALL _V4DTransformSSE4(double *,void *,double *);

	void _APICALL _V4DAddAVX(double *a,double *b,double *c);
	void _APICALL _V4DSubAVX(double *a,double *b,double *c);
	void _APICALL _V4DScaleAVX(double *a,double *b,double c);
	void _APICALL _V4DMulAVX(double *a,double *b,double *c);
	void _APICALL _V4DDivAVX(double *a,double *b,double *c);
	void _APICALL _V4DLerpAVX(double *a,double *b,double *c,double d);
	void _APICALL _V4DCombineAVX(double *a,double *b,double *c,double d,double e);
	void _APICALL _V4DTransformAVX(double *,void *,double *);
}

#endif

#endif /* GEN3_X86_64_VECTOR_H_ */
