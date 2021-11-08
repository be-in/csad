/*
 * x86vector.cpp
 *
 *  Created on: 18.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifdef CPU_BT

#include "x86vector.h"
//#include "csad/platform/internalfunctions.h"
#include "x86service.h"

#ifdef CPU_X86_32

#include "x86vector_to.h"
#include "x86vector_abs.h"
#include "x86vector_minmax.h"
#include "x86vector_add.h"
#include "x86vector_sub.h"
#include "x86vector_scale.h"
#include "x86vector_mul.h"
#include "x86vector_div.h"
#include "x86vector_mul2n.h"
#include "x86vector_dotproduct.h"
#include "x86vector_length2.h"
#include "x86vector_normal.h"
#include "x86vector_cross.h"
#include "x86vector_lerp.h"
#include "x86vector_combine.h"
#include "x86vector_qdfl.h"
#include "x86vector_angle.h"
#include "x86triangle_normal.h"
#include "x86vector_quaternion.h"
#include "x86vector_transform.h"
#include "x86vector_mmul.h"
#include "x86vector_proj.h"
#include "../base/basemath.h"
#include "x86math.h"
#include "macrosasm.h"

#if defined(GCC) || defined(MINGW)
#include <x86intrin.h>
#endif

#if defined(MSVC)
#include <intrin.h>
#endif

WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

	void _FASTCALL SUB_FSinCosSSE(float *s,float *c,float *table,float a);
	void _FASTCALL SUB_DSinCosSSE2(double *s,double *c,double *table,double a);
	void _FASTCALL SUB_FFastSinCosSSE(float *s,float *c,float *table,float a);

// ************** vector To FPU function *******************

	void _NAKED _APICALL _V2FTo2IFPU(float *,int *)
	{
		VECTORP2DTO2IFPU_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3FTo3IFPU(float *,int *)
	{
		VECTORP3DTO3IFPU_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4FTo4IFPU(float *,int *)
	{
		VECTORP4DTO4IFPU_STD;
		RET_2;
	}

	void _NAKED _APICALL _V2DTo2IFPU(double *,int *)
	{
		VECTORP2DDTO2IFPU_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3DTo3IFPU(double *,int *)
	{
		VECTORP3DDTO3IFPU_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4DTo4IFPU(double *,int *)
	{
		VECTORP4DDTO4IFPU_STD;
		RET_2;
	}

// ************** vector Abs FPU function *******************

	void _NAKED _APICALL _V2FAbsFPU(float *,float *)
	{
		VECTORP2DABSFPU_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3FAbsFPU(float *,float *)
	{
		VECTORP3DABSFPU_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4FAbsFPU(float *,float *)
	{
		VECTORP4DABSFPU_STD;
		RET_2;
	}

	void _NAKED _APICALL _V2DAbsFPU(double *,double *)
	{
		VECTORP2DDABSFPU_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3DAbsFPU(double *,double *)
	{
		VECTORP3DDABSFPU_STD;
		RET_2;
	}
	
	void _NAKED _APICALL _V4DAbsFPU(double *,double *)
	{
		VECTORP4DDABSFPU_STD;
		RET_2;
	}

// ************** vector Add FPU function *******************

	void _NAKED _APICALL _V2FAddFPU(float *,float *,float *)
	{
		VECTORP2DADDFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3FAddFPU(float *,float *,float *)
	{
		VECTORP3DADDFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4FAddFPU(float *,float *,float *)
	{
		VECTORP4DADDFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V2DAddFPU(double *,double *,double *)
	{
		VECTORP2DDADDFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3DAddFPU(double *,double *,double *)
	{
		VECTORP3DDADDFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4DAddFPU(double *,double *,double *)
	{
		VECTORP4DDADDFPU_STD;
		RET_3;
	}

// ************** vector Sub FPU function *******************

	void _NAKED _APICALL _V2FSubFPU(float *,float *,float *)
	{
		VECTORP2DSUBFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3FSubFPU(float *,float *,float *)
	{
		VECTORP3DSUBFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4FSubFPU(float *,float *,float *)
	{
		VECTORP4DSUBFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V2DSubFPU(double *,double *,double *)
	{
		VECTORP2DDSUBFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3DSubFPU(double *,double *,double *)
	{
		VECTORP3DDSUBFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4DSubFPU(double *,double *,double *)
	{
		VECTORP4DDSUBFPU_STD;
		RET_3;
	}

// ************** vector Scale FPU function *******************

	void _NAKED _APICALL _V2FScaleFPU(float *,float *,float)
	{
		VECTORP2DSCALEFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3FScaleFPU(float *,float *,float)
	{
		VECTORP3DSCALEFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4FScaleFPU(float *,float *,float)
	{
		VECTORP4DSCALEFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V2DScaleFPU(double *,double *,double)
	{
		VECTORP2DDSCALEFPU_STD;
		RET_4;
	}

	void _NAKED _APICALL _V3DScaleFPU(double *,double *,double)
	{
		VECTORP3DDSCALEFPU_STD;
		RET_4;
	}

	void _NAKED _APICALL _V4DScaleFPU(double *,double *,double)
	{
		VECTORP4DDSCALEFPU_STD;
		RET_4;
	}

// ************** vector Mul FPU function *******************

	void _NAKED _APICALL _V2FMulFPU(float *,float *,float*)
	{
		VECTORP2DMULFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3FMulFPU(float *,float *,float*)
	{
		VECTORP3DMULFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4FMulFPU(float *,float *,float*)
	{
		VECTORP4DMULFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V2DMulFPU(double *,double *,double*)
	{
		VECTORP2DDMULFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3DMulFPU(double *,double *,double*)
	{
		VECTORP3DDMULFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4DMulFPU(double *,double *,double*)
	{
		VECTORP4DDMULFPU_STD;
		RET_3;
	}

// ************** vector mul2n trunc FPU function *******************

	void _NAKED _APICALL _V2Fmul2NTruncFPU(float *,int *,int)
	{
		VECTORP2DMUL2NTRUNCFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3Fmul2NTruncFPU(float *,int *,int)
	{
		VECTORP3DMUL2NTRUNCFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4Fmul2NTruncFPU(float *,int *,int)
	{
		VECTORP4DMUL2NTRUNCFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V2Dmul2NTruncFPU(double *,int *,int)
	{
		VECTORP2DDMUL2NTRUNCFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3Dmul2NTruncFPU(double *,int *,int)
	{
		VECTORP3DDMUL2NTRUNCFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4Dmul2NTruncFPU(double *,int *,int)
	{
		VECTORP4DDMUL2NTRUNCFPU_STD;
		RET_3;
	}

// ************** vector mul2n round FPU function *******************

	void _NAKED _APICALL _V2Fmul2NRoundFPU(float *,int *,int)
	{
		VECTORP2DMUL2NROUNDFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3Fmul2NRoundFPU(float *,int *,int)
	{
		VECTORP3DMUL2NROUNDFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4Fmul2NRoundFPU(float *,int *,int)
	{
		VECTORP4DMUL2NROUNDFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V2Dmul2NRoundFPU(double *,int *,int)
	{
		VECTORP2DDMUL2NROUNDFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3Dmul2NRoundFPU(double *,int *,int)
	{
		VECTORP3DDMUL2NROUNDFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4Dmul2NRoundFPU(double *,int *,int)
	{
		VECTORP4DDMUL2NROUNDFPU_STD;
		RET_3;
	}

// ************** vector mul2n FPU function *******************

	void _NAKED _APICALL _V2Fmul2NFPU(float *,float *,int)
	{
		VECTORP2DMUL2NFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3Fmul2NFPU(float *,float *,int)
	{
		VECTORP3DMUL2NFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4Fmul2NFPU(float *,float *,int)
	{
		VECTORP4DMUL2NFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V2Dmul2NFPU(double *,double *,int)
	{
		VECTORP2DDMUL2NFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3Dmul2NFPU(double *,double *,int)
	{
		VECTORP3DDMUL2NFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4Dmul2NFPU(double *,double *,int)
	{
		VECTORP4DDMUL2NFPU_STD;
		RET_3;
	}

// ************** vector Dotproduct FPU function *******************

	float _NAKED _APICALL _V2FDotFPU(float *,float *)
	{
		VECTORP2DDOTPRODUCTFPU_STD;
		RET_2;
	}

	float _NAKED _APICALL _V3FDotFPU(float *,float *)
	{
		VECTORP3DDOTPRODUCTFPU_STD;
		RET_2;
	}

	float _NAKED _APICALL _V4FDotFPU(float *,float *)
	{
		VECTORP4DDOTPRODUCTFPU_STD;
		RET_2;
	}

	double _NAKED _APICALL _V2DDotFPU(double *,double *)
	{
		VECTORP2DDDOTPRODUCTFPU_STD;
		RET_2;
	}

	double _NAKED _APICALL _V3DDotFPU(double *,double *)
	{
		VECTORP3DDDOTPRODUCTFPU_STD;
		RET_2;
	}

	double _NAKED _APICALL _V4DDotFPU(double *,double *)
	{
		VECTORP4DDDOTPRODUCTFPU_STD;
		RET_2;
	}

// ************** vector Length2 FPU function *******************

	float _NAKED _APICALL _V2FLength2FPU(float *)
	{
		VECTORP2DLENGTH2FPU_STD;
		RET_1;
	}

	float _NAKED _APICALL _V3FLength2FPU(float *)
	{
		VECTORP3DLENGTH2FPU_STD
		RET_1
	}

	float _NAKED _APICALL _V4FLength2FPU(float *)
	{
		VECTORP4DLENGTH2FPU_STD
		RET_1
	}

	double _NAKED _APICALL _V2DLength2FPU(double *)
	{
		VECTORP2DDLENGTH2FPU_STD;
		RET_1;
	}

	double _NAKED _APICALL _V3DLength2FPU(double *)
	{
		VECTORP3DDLENGTH2FPU_STD;
		RET_1;
	}


// ************** vector CrossProduct FPU function *******************

	void _NAKED _APICALL _V3FCrossFPU(float *,float *,float *) {
		VECTORP3DCROSSPRODUCTFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3DCrossFPU(double *,double *,double *) {
		VECTORP3DDCROSSPRODUCTFPU_STD;
		RET_3;
	}

// ************** normal FPU function *******************

	void _NAKED _APICALL _V2FNormalFPU(float *,float * ) {
		VECTORP2DNORMALFPU_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3FNormalFPU(float * ,float * ) {
		VECTORP3DNORMALFPU_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4FNormalFPU(float * ,float * ) {
		VECTORP4DNORMALFPU_STD;
		RET_2;
	}

	void _NAKED _APICALL _V2DNormalFPU(double * ,double * ) {
		VECTORP2DDNORMALFPU_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3DNormalFPU(double * ,double * ) {
		PARAMETERS_ESP_VOID_VOID;
		VECTORP3DDNORMALFPU;
		RET_2;
	}

	void _NAKED _APICALL _V4DNormalFPU(double * ,double * ) {
		VECTORP4DDNORMALFPU_STD;
		RET_2;
	}

// ************** vector Lerp FPU function *******************

	void _NAKED _APICALL _V2FLerpFPU(float * ,float * ,float * ,float )
	{
		VECTORP2DLERPFPU_STD;
		RET_4;
	}

	void _NAKED _APICALL _V3FLerpFPU(float * ,float * ,float * ,float )
	{
		VECTORP3DLERPFPU_STD
		RET_4
	}

	void _NAKED _APICALL _V4FLerpFPU(float * ,float * ,float * ,float )
	{
		VECTORP4DLERPFPU_STD
		RET_4
	}

	void _NAKED _APICALL _V2DLerpFPU(double * ,double * ,double * ,double )
	{
		VECTORP2DDLERPFPU_STD;
		RET_5;
	}

	void _NAKED _APICALL _V3DLerpFPU(double * ,double * ,double * ,double )
	{
		VECTORP3DDLERPFPU_STD;
		RET_5;
	}

	void _NAKED _APICALL _V4DLerpFPU(double * ,double * ,double * ,double )
	{
		VECTORP4DDLERPFPU_STD;
		RET_5;
	}

// ************** vector Combine FPU function *******************

	void _NAKED _APICALL _V2FCombineFPU(float *,float *,float *,float ,float )
	{
		VECTORP2DCOMBINEFPU_STD;
		RET_5;
	}

	void _NAKED _APICALL _V3FCombineFPU(float *,float *,float *,float ,float )
	{
		VECTORP3DCOMBINEFPU_STD;
		RET_5;
	}

	void _NAKED _APICALL _V4FCombineFPU(float *,float *,float *,float ,float )
	{
		VECTORP4DCOMBINEFPU_STD;
		RET_5;
	}

	void _NAKED _APICALL _V2DCombineFPU(double *,double *,double *,double ,double )
	{
		VECTORP2DDCOMBINEFPU_STD;
		RET_7;
	}

	void _NAKED _APICALL _V3DCombineFPU(double *,double *,double *,double ,double )
	{
		VECTORP3DDCOMBINEFPU_STD;
		RET_7;
	}

	void _NAKED _APICALL _V4DCombineFPU(double *,double *,double *,double ,double )
	{
		VECTORP4DDCOMBINEFPU_STD;
		RET_7;
	}

// ************** angle FPU function *******************

	float _NAKED _APICALL _V2FAngleFPU(float *,float *)
	{
		VECTORP2DANGLEFPU_STD;
		RET_2;
	}

	float _NAKED _APICALL _V3FAngleFPU(float *,float *)
	{
		VECTORP3DANGLEFPU_STD;
		RET_2;
	}

	double _NAKED _APICALL _V2DAngleFPU(double *,double *)
	{
		VECTORP2DDANGLEFPU_STD;
		RET_2;
	}

	double _NAKED _APICALL _V3DAngleFPU(double *,double *)
	{
		VECTORP3DDANGLEFPU_STD;
		RET_2;
	}

// ************** add triangle normal FPU function *******************

	void _NAKED _APICALL _V3FAddTriNormFPU(float *,float *,float *,int )
	{
		TRIANGLEP3DADDNORMALFPU_STD;
		RET_4;
	}

	void _NAKED _APICALL _V3FAdd3DTriNormFPU(double *,double *,double *,int )
	{
		TRIANGLEP3DADD3DDNORMALFPU_STD;
		RET_4;
	}

	void _NAKED _APICALL _V3DAddTriNormFPU(double *,double *,double *,int )
	{
		TRIANGLEP3DDADDNORMALFPU_STD;
		RET_4;
	}

// ************** vector Quaternion FPU function *******************

	void _NAKED _APICALL _V4FQuaternionFPU(float *,float *)
	{
		VECTORP4DQUATERNIONFPU_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4DQuaternionFPU(double *,double *)
	{
		VECTORP4DDQUATERNIONFPU_STD;
		RET_2;
	}

// ************** vector Transform FPU function *******************

	void _NAKED _APICALL _V2FTransformFPU(float *,void *,float *)
	{
		VECTORP2DTRANSFORMFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3FTransformFPU(float *,void *,float *)
	{
		VECTORP3DTRANSFORMFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4FTransformFPU(float *,void *,float *)
	{
		VECTORP4DTRANSFORMFPU_STD;
		RET_3;
	}

// ************** vector MMul FPU function *******************

	void _NAKED _APICALL _V2FMMulFPU(float *,void *,float *)
	{
		VECTORP2DMMULFPU_STD;
		RET_3;
	}

/*	void _NAKED _STDCALL _V3FMMulFPU(float *,void *,float *)
	{
		VECTORP3DTRANSFORMFPU_STD;
		RET_3;
	}*/

// ************** vector Projection FPU function *******************

	int _NAKED _APICALL _V3FProjFPU(float *,void *,float *,float *,float *)
	{
		VECTORP3DPROJECTFPU_STD;
		RET_5;
	}

// ************** vector Quaternion To Matrix FPU function *******************

	void _NAKED _APICALL _Q4FMatrixFPU(float *,float *)
	{
//		return
	}

	void _NAKED _APICALL _Q4DMatrixFPU(double *,double *)
	{

	}

	// ************** vector To SSE function *******************

	void _NAKED _APICALL _V2BTo2FSSE(char *,float *)
	{
		VECTORP2BTO2DSSE_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3BTo3FSSE(char *,float *)
	{
		VECTORP3BTO3DSSE_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4BTo4FSSE(char *,float *)
	{
		VECTORP4BTO4DSSE_STD;
		RET_2;
	}

	void _NAKED _APICALL _V2ITo2FSSE(int *,float *)
	{
		VECTORP2ITO2DSSE_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3ITo3FSSE(int *,float *)
	{
		VECTORP3ITO3DSSE_STD;
		RET_2;
	}
	void _NAKED _APICALL _V4ITo4FSSE(int *,float *)
	{
		VECTORP4ITO4DSSE_STD;
		RET_2;
	}

	void _NAKED _APICALL _V2FTo2BSSE(float *,char *)
	{
		VECTORP2DTO2BSSE_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3FTo3BSSE(float *,char *)
	{
		VECTORP3DTO3BSSE_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4FTo4BSSE(float *,char *)
	{
		VECTORP4DTO4BSSE_STD;
		RET_2;
	}

	void _NAKED _APICALL _V2FTo2ISSE(float *,int *)
	{
		VECTORP2DTO2ISSE_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3FTo3ISSE(float *,int *)
	{
		VECTORP3DTO3ISSE_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4FTo4ISSE(float *,int *)
	{
		VECTORP4DTO4ISSE_STD;
		RET_2;
	}

	void _NAKED _APICALL _V2FTTo2ISSE(float *,int *)
	{
		VECTORP2DTTO2ISSE_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3FTTo3ISSE(float *,int *)
	{
		VECTORP3DTTO3ISSE_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4FTTo4ISSE(float *,int *)
	{
		VECTORP4DTTO4ISSE_STD;
		RET_2;
	}

	// ************** vector Inv SSE function *******************

	void _APICALL _V2FInvSSE(float *_a,float *_b)
	{
		__m128 v0 =_mm_castsi128_ps(_mm_set_epi32(0x80000000,0x80000000,0x80000000,0x80000000));
		__m128 v1 = _mm_setzero_ps();
		v0 = _mm_xor_ps(_mm_loadl_pi(v1,(__m64*)_a),v0);
		_mm_storel_pi((__m64*)_b,v0);
	}

	void _APICALL _V3FInvSSE(float *_a,float *_b)
	{
		__m128 v0 =_mm_castsi128_ps(_mm_set_epi32(0x80000000,0x80000000,0x80000000,0x80000000));
		v0 = _mm_xor_ps(_mm_loadh_pi(_mm_load_ss(_a+2),(__m64*)_a),v0);
		_mm_store_ss(_b+2,v0);
		_mm_storeh_pi((__m64*)_b,v0);
	}

	void _APICALL _V4FInvSSE(float *_a,float *_b)
	{
		__m128 v0 =_mm_castsi128_ps(_mm_set_epi32(0x80000000,0x80000000,0x80000000,0x80000000));
		v0 = _mm_xor_ps(_mm_loadu_ps(_a),v0);
		_mm_storeu_ps(_b,v0);
	}

	void _APICALL _V2DInvSSE(double *_a,double *_b)
	{
		__m128 v0 =_mm_castsi128_ps(_mm_set_epi32(0x80000000,0x00000000,0x80000000,0x00000000));
		v0 = _mm_xor_ps(_mm_loadu_ps((float*)_a),v0);
		_mm_storeu_ps((float*)_b,v0);
	}

	void _APICALL _V3DInvSSE(double *_a,double *_b)
	{
		__m128 v0 =_mm_castsi128_ps(_mm_set_epi32(0x80000000,0x00000000,0x80000000,0x00000000));
		__m128 v1 = _mm_xor_ps(_mm_loadu_ps((float*)_a),v0);
		_mm_storeu_ps((float*)_b,v1);
		__m128 v2 = _mm_xor_ps(v1,v1);
		v0 = _mm_xor_ps(_mm_loadl_pi(v2,(__m64*)(_a+2)),v0);
		_mm_storel_pi((__m64*)(_b+2),v0);
	}

	void _APICALL _V4DInvSSE(double *_a,double *_b)
	{
		__m128 v0 =_mm_castsi128_ps(_mm_set_epi32(0x80000000,0x00000000,0x80000000,0x00000000));
		__m128 v1 = _mm_xor_ps(_mm_loadu_ps((float*)_a),v0);
		v0 = _mm_xor_ps(_mm_loadu_ps((float*)(_a+2)),v0);
		_mm_storeu_ps((float*)_b,v1);
		_mm_storeu_ps((float*)(_b+2),v0);
	}

	// ************** vector Add SSE function *******************

	void _NAKED _APICALL _V2FAddSSE(float *,float *,float *)
	{
		VECTORP2DADDSSE_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3FAddSSE(float *,float *,float *)
	{
		VECTORP3DADDSSE_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4FAddSSE(float *,float *,float *)
	{
		VECTORP4DADDSSE_STD;
		RET_3;
	}

	// ************** vector Sub SSE function *******************

	void _NAKED _APICALL _V2FSubSSE(float *,float *,float *)
	{
		VECTORP2DSUBSSE_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3FSubSSE(float *,float *,float *)
	{
		VECTORP3DSUBSSE_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4FSubSSE(float *,float *,float *)
	{
		VECTORP4DSUBSSE_STD;
		RET_3;
	}

// ************** vector Scale SSE function *******************

	void _NAKED _APICALL _V2FScaleSSE(float *,float *,float)
	{
		VECTORP2DSCALESSE_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3FScaleSSE(float *,float *,float)
	{
		VECTORP3DSCALESSE_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4FScaleSSE(float *,float *,float)
	{
		VECTORP4DSCALESSE_STD;
		RET_3;
	}

// ************** vector Mul SSE function *******************

	void _NAKED _APICALL _V2FMulSSE(float *,float *,float*)
	{
		VECTORP2DMULSSE_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3FMulSSE(float *,float *,float*)
	{
		VECTORP3DMULSSE_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4FMulSSE(float *,float *,float*)
	{
		VECTORP4DMULSSE_STD;
		RET_3;
	}

// ************** vector Div SSE function *******************

	void _NAKED _APICALL _V2FDivSSE(float *,float *,float*)
	{
		VECTORP2DDIVSSE_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3FDivSSE(float *,float *,float*)
	{
		VECTORP3DDIVSSE_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4FDivSSE(float *,float *,float*)
	{
		VECTORP4DDIVSSE_STD;
		RET_3;
	}

// ************** vector Dot Product SSE function *******************

	float _NAKED _APICALL _V4FDotSSE(float *,float *)
	{
		VECTORP4DDOTPRODUCTSSE_STD;
		RET_2;
	}

// ************** vector Length2 SSE function *******************

	float _NAKED _APICALL _V4FLength2SSE(float *)
	{
		VECTORP4DLENGTH2SSE_STD;
		RET_1;
	}

// ************** vector CrossProduct SSE function *******************

	void _NAKED _APICALL _V3FCrossSSE(float *,float *,float *) {
		VECTORP3DCROSSPRODUCTSSE_STD;
		RET_3;
	}

// ************** vector Normal SSE function *******************

	void _NAKED _APICALL _V2FNormalSSE(float *,float *) {
		VECTORP2DNORMALSSE_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3FNormalSSE(float *,float *) {
		VECTORP3DNORMALSSE_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4FNormalSSE(float *,float *) {
		VECTORP4DNORMALSSE_STD;
		RET_2;
	}

// ************** vector Fast Normal SSE function *******************

	void _NAKED _APICALL _V2FFastNormalSSE(float *,float *) {
		VECTORP2DFASTNORMALSSE_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3FFastNormalSSE(float *,float *) {
		VECTORP3DFASTNORMALSSE_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4FFastNormalSSE(float *,float *) {
		VECTORP4DFASTNORMALSSE_STD;
		RET_2;
	}

// ************** vector Lerp SSE function *******************

	void _NAKED _APICALL _V2FLerpSSE(float * ,float * ,float * ,float )
	{
		VECTORP2DLERPSSE_STD;
		RET_4;
	}

	void _NAKED _APICALL _V3FLerpSSE(float * ,float * ,float * ,float )
	{
		VECTORP3DLERPSSE_STD;
		RET_4;
	}

	void _NAKED _APICALL _V4FLerpSSE(float * ,float * ,float * ,float )
	{
		VECTORP4DLERPSSE_STD;
		RET_4;
	}

// ************** vector Combine SSE function *******************

	void _NAKED _APICALL _V2FCombineSSE(float *,float *,float *,float ,float )
	{
		VECTORP2DCOMBINESSE_STD;
		RET_5;
	}

	void _NAKED _APICALL _V3FCombineSSE(float *,float *,float *,float ,float )
	{
		VECTORP3DCOMBINESSE_STD;
		RET_5;
	}

	void _NAKED _APICALL _V4FCombineSSE(float *,float *,float *,float ,float )
	{
		VECTORP4DCOMBINESSE_STD;
		RET_5;
	}

// ************** angle SSE function *******************

	float _APICALL _V3FAngleSSE(float * _a,float * _b)
	{
		__m128 v0 = _mm_load_ss(_a+2);
		__m128 v1 = _mm_load_ss(_b+2);
		v0 = _mm_loadh_pi(v0,(const __m64 *)_a);
		v1 = _mm_loadh_pi(v1,(const __m64 *)_b);
		__m128 v2 = v0;
		__m128 v3 = v1;
		__m128 v4 = v0;
		__m128 v5 = v1;
		v0 = _mm_shuffle_ps(v0, v0, 0x32);
		v1 = _mm_shuffle_ps(v1, v1, 0x83);
		v2 = _mm_shuffle_ps(v2, v2, 0x83);
		v3 = _mm_shuffle_ps(v3, v3, 0x32);
		v0 = _mm_mul_ps(v0, v1);
		v2 = _mm_mul_ps(v2, v3);
		v0 = _mm_sub_ps(v0, v2);
		v4 = _mm_mul_ps(v4, v5);
		v0 = _mm_mul_ps(v0, v0);

		v2 = _mm_movehl_ps(v2, v4);
		v1 = _mm_movehl_ps(v1, v0);
		v4 = _mm_add_ss(v4, v2);
		v0 = _mm_add_ss(v0, v1);
		v2 = v4;
		v1 = v0;
		v2 = _mm_shuffle_ps(v2, v2, 0x01);
		v1 = _mm_shuffle_ps(v1, v1, 0x01);
		v4 = _mm_add_ss(v4, v2);
		v0 = _mm_add_ss(v0, v1);

		v0 = _mm_sqrt_ss(v0);

		float _x;
		float _y;

		_mm_store_ss(&_x,v4);
		_mm_store_ss(&_y,v0);

		return _FArcTgSSE(_x,_y);
//		return _FArcTgSSE(_a[0],_a[1]);
	}

// ************** add triangle normal SSE function *******************

	void _NAKED _APICALL _V3FAddTriNormSSE(float *,float *,float *,int )
	{
		TRIANGLEP3DADDNORMALSSE_STD;
		RET_4;
	}

// ************** vector to Quaternion SSE function *******************

	void _APICALL _V4FQuaternionSSE(float * _a,float * _b) {
		float sc[2];
		__m128 v1=_mm_loadu_ps(_a);
		SUB_FSinCosSSE(sc,&sc[1],fastsindividef,(float)(_a[3]*0.5));
		//_FSinCosSSE((float)(_a[3]*0.5),sc,&sc[1]);
		float alen=_a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2];
		__m128 v0=_mm_set_ss(sc[1]);
		if ((alen!=1) && (alen!=0)) {
			v0=_mm_div_ss(v0,_mm_sqrt_ss(_mm_set_ss(alen)));
		}
		v0 = _mm_shuffle_ps(v0,v0,0xC0);
		v0 = _mm_mul_ps(v1,v0);
		_mm_storel_pi((__m64*)_b,v0);
		v0 = _mm_movehl_ps(v0,v0);
		_mm_store_ss(&_b[2],v0);
		_b[3]=sc[0];

		//VECTORP4DQUATERNIONSSE_STD;
		//RET_2;
	}

// ************** vector fast to Quaternion SSE function *******************

	void _APICALL _V4FFastQuaternionSSE(float * _a,float * _b) {
		float sc[2];
		__m128 v1=_mm_loadu_ps(_a);
		SUB_FFastSinCosSSE(sc,&sc[1],fastsindividef,(float)(_a[3]*0.5));
		//_FFastSinCosSSE((float)(_a[3]*0.5),sc,&sc[1]);
		float alen=_a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2];
		__m128 v0=_mm_set_ss(sc[1]);
		if ((alen!=1) && (alen!=0)) {
			v0=_mm_mul_ss(v0,_mm_rsqrt_ss(_mm_set_ss(alen)));
		}
		v0 = _mm_shuffle_ps(v0,v0,0xC0);
		v0 = _mm_mul_ps(v1,v0);
		_mm_storel_pi((__m64*)_b,v0);
		v0 = _mm_movehl_ps(v0,v0);
		_mm_store_ss(&_b[2],v0);
		_b[3]=sc[0];

		//VECTORP4DQUATERNIONSSE_STD;
		//RET_2;
	}

// ************** vector Transform SSE function *******************

	void _NAKED _APICALL _V2FTransformSSE(float *,void *,float *)
	{
		VECTORP2DTRANSFORMSSE_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3FTransformSSE(float *,void *,float *)
	{
		VECTORP3DTRANSFORMSSE_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4FTransformSSE(float *,void *,float *)
	{
		VECTORP4DTRANSFORMSSE_STD;
		RET_3;
	}

// ************** vector MMul SSE function *******************

	void _NAKED _APICALL _V2FMMulSSE(float *,void *,float *)
	{
		VECTORP2DMMULSSE_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3FMMulSSE(float *,void *,float *)
	{
		VECTORP3DMMULSSE_STD;
		RET_3;
	}

// ************** vector Projection SSE function *******************

	int _NAKED _APICALL _V3FProjSSE(float *,void *,float *,float *,float *)
	{
		VECTORP3DPROJECTSSE_STD;
		RET_5;
	}

// ************** vector To SSE2 function *******************

	void _NAKED _APICALL _V2BTo2DSSE2(char *,double *)
	{
		VECTORP2BTO2DDSSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3BTo3DSSE2(char *,double *)
	{
		VECTORP3BTO3DDSSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4BTo4DSSE2(char *,double *)
	{
		VECTORP4BTO4DDSSE2_STD;
		RET_2;
	}

/*	void _NAKED _STDCALL _V4FTo4BSSE2(float *,char *)
	{
		VECTORP4DTO4BSSE2_STD;
		RET_2;
	}*/

	void _NAKED _APICALL _V2FTo2ISSE2(float *,_int32 *)
	{
		VECTORP2DTO2ISSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3FTo3ISSE2(float *,_int32 *)
	{
		VECTORP3DTO3ISSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4FTo4ISSE2(float *,_int32 *)
	{
		VECTORP4DTO4ISSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V2FTTo2ISSE2(float *,_int32 *)
	{
		VECTORP2DTTO2ISSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3FTTo3ISSE2(float *,_int32 *)
	{
		VECTORP3DTTO3ISSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4FTTo4ISSE2(float *,_int32 *)
	{
		VECTORP4DTTO4ISSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V2FTo2DSSE2(float *,double *)
	{
		VECTORP2DTO2DDSSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3FTo3DSSE2(float *,double *)
	{
		VECTORP3DTO3DDSSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4FTo4DSSE2(float *,double *)
	{
		VECTORP4DTO4DDSSE2_STD
		RET_2;
	}

	void _NAKED _APICALL _V2DTo2ISSE2(double *,_int32 *)
	{
		VECTORP2DDTO2ISSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3DTo3ISSE2(double *,_int32 *)
	{
		VECTORP3DDTO3ISSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4DTo4ISSE2(double *,_int32 *)
	{
		VECTORP4DDTO4ISSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V2DTTo2ISSE2(double *,_int32 *)
	{
		VECTORP2DDTTO2ISSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3DTTo3ISSE2(double *,_int32 *)
	{
		VECTORP3DDTTO3ISSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4DTTo4ISSE2(double *,_int32 *)
	{
		VECTORP4DDTTO4ISSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V2DTo2FSSE2(double *,float *)
	{
		VECTORP2DDTO2DSSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3DTo3FSSE2(double *,float *)
	{
		VECTORP3DDTO3DSSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4DTo4FSSE2(double *,float *)
	{
		VECTORP4DDTO4DSSE2_STD;
		RET_2;
	}

	// ************** vector Abs SSE2 function *******************

	void _NAKED _APICALL _V2FAbsSSE2(float *,float *)
	{
		VECTORP2DABSSSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3FAbsSSE2(float *,float *)
	{
		VECTORP3DABSSSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4FAbsSSE2(float *,float *)
	{
		VECTORP4DABSSSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V2DAbsSSE2(double *,double *)
	{
		VECTORP2DDABSSSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3DAbsSSE2(double *,double *)
	{
		VECTORP3DDABSSSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4DAbsSSE2(double *,double *)
	{
		VECTORP4DDABSSSE2_STD;
		RET_2;
	}

// ************** vector Min Max SSE2 function *******************

	void _NAKED _APICALL _V2FMinMaxSSE2(float *,float *,float *)
	{
		VECTORP2DMINMAXSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3FMinMaxSSE2(float *,float *,float *)
	{
		VECTORP3DMINMAXSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4FMinMaxSSE2(float *,float *,float *)
	{
		VECTORP4DMINMAXSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V2DMinMaxSSE2(double *,double *,double *)
	{
		VECTORP2DDMINMAXSSE2_STD;
		RET_3;
	}


// ************** vector Add SSE2 function *******************

	void _NAKED _APICALL _V2IAddSSE2(int *,int *,int *)
	{
		VECTORP2IADDSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3IAddSSE2(int *,int *,int *)
	{
		VECTORP3IADDSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4IAddSSE2(int *,int *,int *)
	{
		VECTORP4IADDSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V2FAddSSE2(float *,float *,float *)
	{
		VECTORP2DADDSSE2_STD;
		RET_3;
	}

	//void _STDCALL _V2FAddSSE2(float *a,float *b,float *c) { __writeAddr(&WriteMe,&__V2FAddSSE2); }

	void _NAKED _APICALL _V3FAddSSE2(float *,float *,float *)
	{
		VECTORP3DADDSSE2_STD;
		RET_3;
	}

	//void _STDCALL _V3FAddSSE2(float *a,float *b,float *c) { __writeAddr(&WriteMe,&__V3FAddSSE2); }

// ************** vector Sub SSE2 function *******************

	void _NAKED _APICALL _V2FSubSSE2(float *,float *,float *)
	{
		VECTORP2DSUBSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4FSubSSE2(float *,float *,float *)
	{
		VECTORP4DSUBSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3DSubSSE2(double *,double *,double *)
	{
		VECTORP3DDSUBSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4DSubSSE2(double *,double *,double *)
	{
		VECTORP4DDSUBSSE2_STD;
		RET_3;
	}

// ************** vector Mul SSE2 function *******************

	void _NAKED _APICALL _V2DMulSSE2(double *,double *,double *)
	{
		VECTORP2DDMULSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3DMulSSE2(double *,double *,double *)
	{
		VECTORP3DDMULSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4DMulSSE2(double *,double *,double *)
	{
		VECTORP4DDMULSSE2_STD;
		RET_3;
	}

// ************** vector Div SSE2 function *******************

	void _NAKED _APICALL _V2DDivSSE2(double *,double *,double *)
	{
		VECTORP2DDDIVSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3DDivSSE2(double *,double *,double *)
	{
		VECTORP3DDDIVSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4DDivSSE2(double *,double *,double *)
	{
		VECTORP4DDDIVSSE2_STD;
		RET_3;
	}

// ************** vector mul2nTrunc SSE function *******************

	void _NAKED _APICALL _V2Fmul2NTruncSSE2(float *,int *,int)
	{
		VECTORP2DMUL2NTRUNCSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3Fmul2NTruncSSE2(float *,int *,int)
	{
		VECTORP3DMUL2NTRUNCSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4Fmul2NTruncSSE2(float *,int *,int)
	{
		VECTORP4DMUL2NTRUNCSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V2Dmul2NTruncSSE2(double *,int *,int)
	{
		VECTORP2DDMUL2NTRUNCSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3Dmul2NTruncSSE2(double *,int *,int)
	{
		VECTORP3DDMUL2NTRUNCSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4Dmul2NTruncSSE2(double *,int *,int)
	{
		VECTORP4DDMUL2NTRUNCSSE2_STD;
		RET_3;
	}

// ************** vector mul2nRound SSE function *******************

	void _NAKED _APICALL _V2Fmul2NRoundSSE2(float *,int *,int)
	{
		VECTORP2DMUL2NROUNDSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3Fmul2NRoundSSE2(float *,int *,int)
	{
		VECTORP3DMUL2NROUNDSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4Fmul2NRoundSSE2(float *,int *,int)
	{
		VECTORP4DMUL2NROUNDSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V2Dmul2NRoundSSE2(double *,int *,int)
	{
		VECTORP2DDMUL2NROUNDSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3Dmul2NRoundSSE2(double *,int *,int)
	{
		VECTORP3DDMUL2NROUNDSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4Dmul2NRoundSSE2(double *,int *,int)
	{
		VECTORP4DDMUL2NROUNDSSE2_STD;
		RET_3;
	}

// ************** vector mul2n SSE function *******************

	void _NAKED _APICALL _V2Fmul2NSSE2(float *,float *,int)
	{
		VECTORP2DMUL2NSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3Fmul2NSSE2(float *,float *,int)
	{
		VECTORP3DMUL2NSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4Fmul2NSSE2(float *,float *,int)
	{
		VECTORP4DMUL2NSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V2Dmul2NSSE2(double *,double *,int)
	{
		VECTORP2DDMUL2NSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3Dmul2NSSE2(double *,double *,int)
	{
		VECTORP3DDMUL2NSSE2_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4Dmul2NSSE2(double *,double *,int)
	{
		VECTORP4DDMUL2NSSE2_STD;
		RET_3;
	}

// ************** vector Length2 SSE2 function *******************

	double _NAKED _APICALL _V4DLength2SSE2(double *)
	{
		VECTORP4DDLENGTH2SSE2_STD;
		RET_1;
	}

// ************** vector CrossProduct SSE2 function *******************

	void _NAKED _APICALL _V3DCrossSSE2(double *,double *,double *) {
		VECTORP3DDCROSSPRODUCTSSE2_STD;
		RET_3;
	}

// ************** vector Normal SSE2 function *******************

	/*void _NAKED _STDCALL _V2DNormalSSE2(double *,double *) {
		VECTORP2DDNORMALSSE2_STD;
		RET_2;
	}*/

// ************** vector Fast Normal SSE2 function *******************

	void _NAKED _APICALL _V2DFastNormalSSE2(double *,double *) {
		VECTORP2DDFASTNORMALSSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3DFastNormalSSE2(double *,double *) {
		VECTORP3DDFASTNORMALSSE2_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4DFastNormalSSE2(double *,double *) {
		VECTORP4DDFASTNORMALSSE2_STD;
		RET_2;
	}

// ************** vector Lerp SSE2 function *******************

	void _NAKED _APICALL _V2DLerpSSE2(double * ,double * ,double * ,double )
	{
		VECTORP2DDLERPSSE2_STD;
		RET_5;
	}

	void _NAKED _APICALL _V3DLerpSSE2(double * ,double * ,double * ,double )
	{
		VECTORP3DDLERPSSE2_STD
		RET_5;
	}

	void _NAKED _APICALL _V4DLerpSSE2(double * ,double * ,double * ,double )
	{
		VECTORP4DDLERPSSE2_STD
		RET_5;
	}

// ************** vector Combine SSE2 function *******************

	void _NAKED _APICALL _V2FCombineSSE2(float *,float *,float *,float ,float )
	{
		VECTORP2DCOMBINESSE2_STD;
		RET_5;
	}

	void _NAKED _APICALL _V4DCombineSSE2(double *,double *,double *,double ,double )
	{
		VECTORP4DDCOMBINESSE2_STD;
		RET_7;
	}

// ************** add triangle normal SSE2 function *******************

	void _NAKED _APICALL _V3DAddTriNormSSE2(double *,double *,double *,int )
	{
		TRIANGLEP3DDADDNORMALSSE2_STD;
		RET_4;
	}

// ************** vector to Quaternion SSE2 function *******************

	void _APICALL _V4DQuaternionSSE2(double * _a,double * _b) {
		double sc[2];
		__m128d v2=_mm_loadu_pd(_a);
		__m128d v3=_mm_load_sd(&_a[2]);
		SUB_DSinCosSSE2(sc,&sc[1],fastsindivided,(double)(_a[3]*0.5));
		//_DSinCosSSE2((double)(_a[3]*0.5),sc,&sc[1]);
		double alen=_a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2];
		__m128d v0=_mm_set_sd(sc[1]);
		if ((alen!=1) && (alen!=0)) {
			__m128d vs=_mm_set_sd(alen);
			v0 = _mm_div_sd(v0,_mm_sqrt_sd(vs,vs));
		}
		v0 = _mm_shuffle_pd(v0,v0,0x00);
		_mm_store_sd(&_b[2],_mm_mul_sd(v3,v0));
		v0 = _mm_mul_pd(v2,v0);
		_b[3]=sc[0];
		_mm_store_sd(_b,v0);
		_mm_storeh_pi((__m64*)&_b[1],*(__m128*)&v0);
	}

// ************** vector fast to Quaternion SSE2 function *******************

	void _APICALL _V4DFastQuaternionSSE2(double * _a,double * _b) {
		double sc[2];
		__m128d v2=_mm_loadu_pd(_a);
		__m128d v3=_mm_load_sd(&_a[2]);
		_DFastSinCosSSE2((double)(_a[3]*0.5),sc,&sc[1]);
		double alen=_a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2];
		__m128d v0=_mm_set_sd(sc[1]);
		if ((alen!=1) && (alen!=0)) {
			__m128 vs=_mm_cvtsd_ss(_mm_setzero_ps(),_mm_set_sd(alen));
			__m128d v4=_mm_cvtss_sd(_mm_setzero_pd(),_mm_rsqrt_ss(vs));
			v0 = _mm_mul_sd(v0,v4);
		}
		v0 = _mm_shuffle_pd(v0,v0,0x00);
		_mm_store_sd(&_b[2],_mm_mul_sd(v3,v0));
		v2 = _mm_mul_pd(v2,v0);
		_b[3]=sc[0];
		_mm_store_sd(_b,v2);
		_mm_storeh_pi((__m64*)&_b[1],*(__m128*)&v2);
	}

// ************** vector Transform SSE2 function *******************

	void _NAKED _APICALL _V2FTransformSSE2(float *,void *,float *)
	{
		VECTORP2DTRANSFORMSSE2_STD;
		RET_3;
	}

	/*void _NAKED _STDCALL _V2DTransformSSE2(double *,void *,double *)
	{
		VECTORP2DDTRANSFORMSSE2_STD;
		RET_3;
	}*/

	void _NAKED _APICALL _V3DTransformSSE2(double *,void *,double *)
	{
		VECTORP3DDTRANSFORMSSE2_STD;
		RET_3;
	}

	/*void _NAKED _STDCALL _V4DTransformSSE2(double *,void *,double *)
	{
		VECTORP4DDTRANSFORMSSE2_STD;
		RET_3;
	}*/

// ************** vector revers SSE3 function *******************

	void _NAKED _APICALL _V4R32SSE3(_int32 *,_int32 *) {
		_BEGIN_ASM \
		_LINE4( 0x8B,0x44,0x24,0x04 )                        /* mov         eax,dword ptr [esp+4]  */ \
		_LINE4( 0x8B,0x54,0x24,0x08 )                        /* mov         edx,dword ptr [esp+8]  */ \
		ASM( lddqu xmm0,[eax] ) \
		ASM( shufps xmm0,xmm0,0x1B ) \
		ASM( movups [edx],xmm0 ) \
		_END_ASM
		RET_2;
	}

	void _NAKED _APICALL _V4R64SSE3(_int64 *,_int64 *) {
		_BEGIN_ASM \
		_LINE4( 0x8B,0x44,0x24,0x04 )                        /* mov         eax,dword ptr [esp+4]  */ \
		_LINE4( 0x8B,0x54,0x24,0x08 )                        /* mov         edx,dword ptr [esp+8]  */ \
		ASM( lddqu xmm0,[eax] ) \
		ASM( lddqu xmm1,[eax+0x10] ) \
		ASM( shufpd xmm0,xmm0,0x1 ) \
		ASM( shufpd xmm1,xmm1,0x1 ) \
		ASM( movups [edx],xmm1 ) \
		ASM( movups [edx+0x10],xmm0 ) \
		_END_ASM
		RET_2;
	}

// ************** vector copy SSE3 function *******************

	void _NAKED _APICALL _V3R64CopySSE3(void *, void *)
	{
		VECTORP3DDCOPYSSE3_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4R64CopySSE3(void *, void *)
	{
		VECTORP4DDCOPYSSE3_STD;
		RET_2;
	}

// ************** vector To SSE3 function *******************

	void _NAKED _APICALL _V4BTo4FSSE3(char *,float *)
	{
		VECTORP4BTO4DSSE3_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4FTo4BSSE3(float *,char *)
	{
		//VECTORP4DTO4BSSE3_STD;
		RET_2;
	}

	void _NAKED _APICALL _V2DTo2FSSE3(double *,float *)
	{
		VECTORP2DDTO2DSSE3_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3DTo3FSSE3(double *,float *)
	{
		VECTORP3DDTO3DSSE3_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4DTo4FSSE3(double *,float *)
	{
		VECTORP4DDTO4DSSE3_STD;
		RET_2;
	}

// ************** vector Add SSE3 function *******************

	void _NAKED _APICALL _V4FAddSSE3(float *,float *,float *)
	{
		VECTORP4DADDSSE3_STD;
		RET_3;
	}

	//void _STDCALL _V4FAddSSE3(float *a,float *b,float *c) { __writeAddr(&WriteMe,&__V4FAddSSE3); }

	void _NAKED _APICALL _V2DAddSSE3(double *,double *,double *)
	{
		VECTORP2DDADDSSE3_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3DAddSSE3(double *,double *,double *)
	{
		VECTORP3DDADDSSE3_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4DAddSSE3(double *,double *,double *)
	{
		VECTORP4DDADDSSE3_STD;
		RET_3;
	}

// ************** vector Sub SSE3 function *******************

	void _NAKED _APICALL _V4FSubSSE3(float *,float *,float *)
	{
		VECTORP4DSUBSSE3_STD;
		RET_3;
	}

	void _NAKED _APICALL _V2DSubSSE3(double *,double *,double *)
	{
		VECTORP2DDSUBSSE3_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3DSubSSE3(double *,double *,double *)
	{
		VECTORP3DDSUBSSE3_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4DSubSSE3(double *,double *,double *)
	{
		VECTORP4DDSUBSSE3_STD;
		RET_3;
	}

// ************** vector Scale SSE3 function *******************

	void _NAKED _APICALL _V4IScaleSSE3(_int32 *,_int32 *,float)
	{
		VECTORP4ISCALESSE3_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4FScaleSSE3(float *,float *,float)
	{
		VECTORP4DSCALESSE3_STD;
		RET_3;
	}

	void _NAKED _APICALL _V2DScaleSSE3(double *,double *,double)
	{
		VECTORP2DDSCALESSE3_STD;
		RET_4;
	}

// ************** vector Lerp SSE3 function *******************

	void _NAKED _APICALL _V4FLerpSSE3(float * ,float * ,float * ,float )
	{
		VECTORP4DLERPSSE3_STD;
		RET_4;
	}

	void _NAKED _APICALL _V2DLerpSSE3(double * ,double * ,double * ,double )
	{
		VECTORP2DDLERPSSE3_STD;
		RET_5;
	}

	void _NAKED _APICALL _V3DLerpSSE3(double * ,double * ,double * ,double )
	{
		VECTORP3DDLERPSSE3_STD;
		RET_5;
	}

	void _NAKED _APICALL _V4DLerpSSE3(double * ,double * ,double * ,double )
	{
		VECTORP4DDLERPSSE3_STD;
		RET_5;
	}

// ************** vector Combine SSE3 function *******************

	void _NAKED _APICALL _V4FCombineSSE3(float *,float *,float *,float ,float )
	{
		VECTORP4DCOMBINESSE3_STD;
		RET_5;
	}

// ************** vector quad distance from line SSE3 function *******************

	float _NAKED _APICALL _V2FQDFLSSE3(float * ,float * ,float * )
	{
		VECTORP2DQDFLSSE3_STD;
		RET_3;
	}

	double _NAKED _APICALL _V2DQDFLSSE3(double * ,double * ,double * )
	{
		VECTORP2DDQDFLSSE3_STD;
		RET_3;
	}

// ************** vector Transform SSE3 function *******************

	void _NAKED _APICALL _V3FTransformSSE3(float *,void *,float *)
	{
		VECTORP3DTRANSFORMSSE3_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4FTransformSSE3(float *,void *,float *)
	{
		VECTORP4DTRANSFORMSSE3_STD;
		RET_3;
	}

// ************** vector Mul matrix SSE3 function *******************

	void _NAKED _APICALL _V3FMMulSSE3(float *,void *,float *)
	{
		VECTORP3DMMULSSE3_STD;
		RET_3;
	}

// ************** vector Projection SSE3 function *******************

	int _NAKED _APICALL _V2FProjSSE3(float *,void *,float *,float *,float *)
	{
		VECTORP2DPROJECTSSE3_STD;
		RET_5;
	}

	int _NAKED _APICALL _V3FProjSSE3(float *,void *,float *,float *,float *)
	{
		VECTORP3DPROJECTSSE3_STD;
		RET_5;
	}

	int _NAKED _APICALL _V4FProjSSE3(float *,void *,float *,float *,float *)
	{
		VECTORP4DPROJECTSSE3_STD;
		RET_5;
	}

// ************** vector To SSE4 function *******************

	void _NAKED _APICALL _V4ITo4FSSE4(int *,float *)
	{
		VECTORP4ITO4DSSE4_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4FTo4BSSE4(float *,char *)
	{
		VECTORP4DTO4BSSE4_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4FTo4ISSE4(float *,int *)
	{
		VECTORP4DTO4ISSE4_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4FTTo4ISSE4(float *,int *)
	{
		VECTORP4DTTO4ISSE4_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3FTo3DSSE4(float *,double *)
	{
		VECTORP3DTO3DDSSE4_STD;
		RET_2;
	}

// ************** vector Abs SSE4 function *******************

	void _NAKED _APICALL _V4FAbsSSE4(float *,float *)
	{
		VECTORP4DABSSSE4_STD;
		RET_2;
	}

	void _NAKED _APICALL _V2DAbsSSE4(double *,double *)
	{
		VECTORP2DDABSSSE4_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3DAbsSSE4(double *,double *)
	{
		VECTORP3DDABSSSE4_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4DAbsSSE4(double *,double *)
	{
		VECTORP4DDABSSSE4_STD;
		RET_2;
	}

// ************** vector Min Max SSE4 function *******************

	void _NAKED _APICALL _V4FMinMaxSSE4(float *,float *,float *)
	{
		VECTORP4DMINMAXSSE4_STD;
		RET_3;
	}

	void _NAKED _APICALL _V2DMinMaxSSE4(double *,double *,double *)
	{
		VECTORP2DDMINMAXSSE4_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3DMinMaxSSE4(double *,double *,double *)
	{
		VECTORP3DDMINMAXSSE4_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4DMinMaxSSE4(double *,double *,double *)
	{
		VECTORP4DDMINMAXSSE4_STD;
		RET_3;
	}

// ************** vector Add SSE4 function *******************

	void _NAKED _APICALL _V4IAddSSE4(int *,int *,int *)
	{
		VECTORP4IADDSSE4_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3DAddSSE4(double *,double *,double *)
	{
		VECTORP3DDADDSSE4_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4DAddSSE4(double *,double *,double *)
	{
		VECTORP4DDADDSSE4_STD;
		RET_3;
	}

// ************** vector Sub SSE4 function *******************

	void _NAKED _APICALL _V4DSubSSE4(double *,double *,double *)
	{
		VECTORP4DDSUBSSE4_STD;
		RET_3;
	}

// ************** array Scale SSE4 function *******************

	void _NAKED _APICALL _V2DScaleSSE4(double *,double *,double)
	{
		VECTORP2DDSCALESSE4_STD;
		RET_4;
	}

	void _NAKED _APICALL _V3DScaleSSE4(double *,double *,double)
	{
		VECTORP3DDSCALESSE4_STD;
		RET_4;
	}

	void _NAKED _APICALL _V4DScaleSSE4(double *,double *,double)
	{
		VECTORP4DDSCALESSE4_STD;
		RET_4;
	}

// ************** vector Mul SSE4 function *******************

	void _NAKED _APICALL _V4DMulSSE4(double *,double *,double *)
	{
		VECTORP4DDMULSSE4_STD;
		RET_3;
	}

// ************** vector Div SSE4 function *******************

	void _NAKED _APICALL _V4DDivSSE4(double *,double *,double *)
	{
		VECTORP4DDDIVSSE4_STD;
		RET_3;
	}

// ************** vector mul2nRound SSE4 function *******************

	void _NAKED _APICALL _V4Fmul2NRoundSSE4(float *,int *,int)
	{
		VECTORP4DMUL2NROUNDSSE4_STD;
		RET_3;
	}

// ************** vector Dotproduct SSE4 function *******************

	float _NAKED _APICALL _V2FDotSSE4(float *,float *)
	{
		VECTORP2DDOTPRODUCTSSE4_STD;
		RET_2;
	}

	float _NAKED _APICALL _V3FDotSSE4(float *,float *)
	{
		VECTORP3DDOTPRODUCTSSE4_STD;
		RET_2;
	}

	float _NAKED _APICALL _V4FDotSSE4(float *,float *)
	{
		VECTORP4DDOTPRODUCTSSE4_STD;
		RET_2;
	}

	double _NAKED _APICALL _V2DDotSSE4(double *,double *)
	{
		VECTORP2DDDOTPRODUCTSSE4_STD;
		RET_2;
	}

	double _NAKED _APICALL _V3DDotSSE4(double *,double *)
	{
		VECTORP3DDDOTPRODUCTSSE4_STD;
		RET_2;
	}

	double _NAKED _APICALL _V4DDotSSE4(double *,double *)
	{
		VECTORP4DDDOTPRODUCTSSE4_STD;
		RET_2;
	}

// ************** vector Length2 SSE4 function *******************

	float _NAKED _APICALL _V2FLength2SSE4(float *)
	{
		VECTORP2DLENGTH2SSE4_STD;
		RET_1;
	}

	float _NAKED _APICALL _V3FLength2SSE4(float *)
	{
		VECTORP3DLENGTH2SSE4_STD
		RET_1
	}

	float _NAKED _APICALL _V4FLength2SSE4(float *)
	{
		VECTORP4DLENGTH2SSE4_STD
		RET_1
	}

	double _NAKED _APICALL _V2DLength2SSE4(double *)
	{
		VECTORP2DDLENGTH2SSE4_STD;
		RET_1;
	}

	double _NAKED _APICALL _V3DLength2SSE4(double *)
	{
		VECTORP3DDLENGTH2SSE4_STD;
		RET_1;
	}

	double _NAKED _APICALL _V4DLength2SSE4(double *)
	{
		VECTORP4DDLENGTH2SSE4_STD;
		RET_1;
	}

// ************** vector Normal SSE4 function *******************

	void _NAKED _APICALL _V2FNormalSSE4(float *,float *) {
		VECTORP2DNORMALSSE4_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3FNormalSSE4(float *,float *) {
		VECTORP3DNORMALSSE4_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4FNormalSSE4(float *,float *) {
		VECTORP4DNORMALSSE4_STD;
		RET_2;
	}

	void _NAKED _APICALL _V2DNormalSSE4(double *,double *) {
		VECTORP2DDNORMALSSE4_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3DNormalSSE4(double *,double *) {
		VECTORP3DDNORMALSSE4_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4DNormalSSE4(double *,double *) {
		VECTORP4DDNORMALSSE4_STD;
		RET_2;
	}

// ************** vector Fast Normal SSE4 function *******************

	void _NAKED _APICALL _V2FFastNormalSSE4(float *,float *) {
		VECTORP2DFASTNORMALSSE4_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3FFastNormalSSE4(float *,float *) {
		VECTORP3DFASTNORMALSSE4_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4FFastNormalSSE4(float *,float *) {
		VECTORP4DFASTNORMALSSE4_STD;
		RET_2;
	}

	void _NAKED _APICALL _V2DFastNormalSSE4(double *,double *) {
		VECTORP2DDFASTNORMALSSE4_STD;
		RET_2;
	}

	void _NAKED _APICALL _V3DFastNormalSSE4(double *,double *) {
		VECTORP3DDFASTNORMALSSE4_STD;
		RET_2;
	}

	void _NAKED _APICALL _V4DFastNormalSSE4(double *,double *) {
		VECTORP4DDFASTNORMALSSE4_STD;
		RET_2;
	}

// ************** vector Lerp SSE4 function *******************

	void _NAKED _APICALL _V4FLerpSSE4(float * ,float * ,float * ,float )
	{
		VECTORP4DLERPSSE4_STD;
		RET_4;
	}

	void _NAKED _APICALL _V2DLerpSSE4(double * ,double * ,double * ,double )
	{
		VECTORP2DDLERPSSE4_STD;
		RET_5;
	}

	void _NAKED _APICALL _V4DLerpSSE4(double * ,double * ,double * ,double )
	{
		VECTORP4DDLERPSSE4_STD;
		RET_5;
	}

// ************** vector Combine SSE4 function *******************

	void _NAKED _APICALL _V4FCombineSSE4(float *,float *,float *,float ,float )
	{
		VECTORP4DCOMBINESSE4_STD;
		RET_5;
	}

	void _NAKED _APICALL _V2DCombineSSE4(double *,double *,double *,double ,double )
	{
		VECTORP2DDCOMBINESSE4_STD;
		RET_7;
	}

	void _NAKED _APICALL _V3DCombineSSE4(double *,double *,double *,double ,double )
	{
		VECTORP3DDCOMBINESSE4_STD;
		RET_7;
	}

	void _NAKED _APICALL _V4DCombineSSE4(double *,double *,double *,double ,double )
	{
		VECTORP4DDCOMBINESSE4_STD;
		RET_7;
	}

// ************** vector to Quaternion SSE4 function *******************

	void _APICALL _V4FQuaternionSSE4(float * _a,float * _b) {
		float sc[2];
		__m128 v1;
		*(__m128i*)&v1=_mm_lddqu_si128((__m128i*)_a);
		SUB_FSinCosSSE(sc,&sc[1],fastsindividef,(float)(_a[3]*0.5));
		__m128 vs=_mm_dp_ps(v1,v1,0x71);
		float alen;
		__m128 v0=_mm_set_ss(sc[1]);
		_mm_store_ss(&alen,vs);
		if ((alen!=1) && (alen!=0)) {
			v0=_mm_div_ss(v0,_mm_sqrt_ss(vs));
		}
		v0 = _mm_shuffle_ps(v0,v0,0xC0);
		v0 = _mm_mul_ps(v1,v0);
		_mm_storel_pi((__m64*)_b,v0);
		v0 = _mm_movehl_ps(v0,v0);
		_mm_store_ss(&_b[2],v0);
		_b[3]=sc[0];
	}

	void _APICALL _V4DQuaternionSSE4(double * _a,double * _b) {
		double sc[2];
		__m128d v2;
		*(__m128i*)&v2=_mm_lddqu_si128((__m128i*)_a);
		__m128d v3=_mm_load_sd(&_a[2]);
		SUB_DSinCosSSE2(sc,&sc[1],fastsindivided,(double)(_a[3]*0.5));
		//_DSinCosSSE2((double)(_a[3]*0.5),sc,&sc[1]);
		__m128d vs=_mm_add_sd(_mm_dp_pd(v2,v2,0x31),_mm_mul_sd(v3,v3));
		double alen;
		__m128d v0=_mm_set_sd(sc[1]);
		_mm_store_sd(&alen,vs);
		if ((alen!=1) && (alen!=0)) {
			v0 = _mm_div_sd(v0,_mm_sqrt_sd(vs,vs));
		}
		v0 = _mm_shuffle_pd(v0,v0,0x00);
		_mm_store_sd(&_b[2],_mm_mul_sd(v3,v0));
		v0 = _mm_mul_pd(v2,v0);
		_b[3]=sc[0];
		_mm_store_sd(_b,v0);
		_mm_storeh_pi((__m64*)&_b[1],*(__m128*)&v0);
	}

// ************** fast vector to Quaternion SSE4 function *******************

	void _NAKED _APICALL _V4FFastQuaternionSSE4(float *,float *)
	{
		//VECTORP4DFASTQUATERNIONSSE4_STD;
		RET_2;
	}

// ************** vector Transform SSE4 function *******************

void _APICALL _V2DTransformSSE4(double *,void *,double *)
{
	VECTORP2DDTRANSFORMSSE4_STD;
	RET_3;
}

void _NAKED _APICALL _V3DTransformSSE4(double *,void *,double *)
{
	VECTORP3DDTRANSFORMSSE4_STD;
	RET_3;
}

void _NAKED _APICALL _V4DTransformSSE4(double *,void *,double *)
{
	VECTORP4DDTRANSFORMSSE4_STD;
	RET_3;
}

// ************** vector Min Max AVX function *******************

	void _NAKED _APICALL _V4DMinMaxAVX(double *,double *,double *)
	{
		VECTORP4DDMINMAXAVX_STD;
		RET_3;
	}

// ************** vector Add AVX function *******************

	void _NAKED _APICALL _V3DAddAVX(double * ,double * ,double *)
	{
		VECTORP3DDADDAVX_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4DAddAVX(double * ,double * ,double *)
	{
		VECTORP4DDADDAVX_STD;
		RET_3;
	}

// ************** vector Sub AVX function *******************

	void _NAKED _APICALL _V4DSubAVX(double * ,double * ,double *)
	{
		VECTORP4DDSUBAVX_STD;
		RET_3;
	}

// ************** vector Scale AVX function *******************

	void _NAKED _APICALL _V4DScaleAVX(double *,double *,double)
	{
		VECTORP4DDSCALEAVX_STD;
		RET_4;
	}

// ************** vector Mul AVX function *******************

	void _NAKED _APICALL _V4DMulAVX(double * ,double * ,double *)
	{
		VECTORP4DDMULAVX_STD;
		RET_3;
	}

// ************** vector Div AVX function *******************

	void _NAKED _APICALL _V4DDivAVX(double * ,double * ,double *)
	{
		VECTORP4DDDIVAVX_STD;
		RET_3;
	}

// ************** vector Div AVX function *******************

	double _NAKED _APICALL _V4DDotAVX(double * ,double * )
	{
		VECTORP4DDDOTPRODUCTAVX_STD;
		RET_2;
	}

// ************** vector Lerp AVX function *******************

	void _NAKED _APICALL _V4DNormalAVX(double * ,double *)
	{
		VECTORP4DDNORMALAVX_STD;
		RET_2;
	}

// ************** vector Lerp AVX function *******************

	void _NAKED _APICALL _V4DLerpAVX(double * ,double * ,double * ,double )
	{
		VECTORP4DDLERPAVX_STD;
		RET_5;
	}

// ************** vector Lerp AVX function *******************

void _NAKED _APICALL _V3DTransformAVX(double *,void *,double *)
{
	VECTORP3DDTRANSFORMAVX_STD;
	RET_3;
}

void _NAKED _APICALL _V4DTransformAVX(double *,void *,double *)
{
	VECTORP4DDTRANSFORMAVX_STD;
	RET_3;
}

// ************** vector Proj AVX function *******************

	void _NAKED _APICALL _V4DProjAVX(double * ,void *,double * ,double * ,double *)
	{
		VECTORP4DDPROJECTAVX_STD;
		RET_5;
	}

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif

#endif

