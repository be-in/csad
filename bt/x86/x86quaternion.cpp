/*
 * x86quaternion.cpp
 *
 *  Created on: 24.10.2013
 *      Author: Пантелеймонов А
 */

#ifdef CPU_BT

#include "x86quaternion.h"

#ifdef CPU_X86_32

#include "x86quaternion_vector.h"
#include "x86quaternion_inv.h"
#include "x86quaternion_mul.h"
#include "x86quaternion_matrix.h"
#include "x86quaternion_transform.h"
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

// ************** quaternion Inv FPU function *******************

	void _APICALL _Q4FVectorFPU(float *,float *)
	{
		QUATERNIONPDVECTORFPU_STD;
		RET_2;
	}

	void _APICALL _Q4DVectorFPU(double *,double *)
	{
		QUATERNIONPDDVECTORFPU_STD;
		RET_2;
	}

	void _NAKED _APICALL _QFInvFPU(float *,float *)
	{
		QUATERNIONPDINVFPU_STD;
		RET_2;
	}

	void _NAKED _APICALL _QDInvFPU(double *,double *)
	{
		QUATERNIONPDDINVFPU_STD;
		RET_2;
	}

// ************** quaternion transform FPU function *******************

	void _NAKED _APICALL _Q3FInvTransformFPU(float * ,float * ,float * ) {
		QUATERNIONP3DTRANSFORMFPU_STD;
		RET_3;
	}

	void _NAKED _APICALL _Q3DInvTransformFPU(double * ,double * ,double * ) {
		QUATERNIONP3DDTRANSFORMFPU_STD;
		RET_3;
	}

// ************** quaternion Mul SSE function *******************

	void _NAKED _APICALL _QFMulSSE(float * ,float * ,float * )
	{
		QUATERNIONPDMULSSE_STD;
		RET_3;
	}

// ************** quaternion Euler SSE function *******************

	void _APICALL _QFEulerSSE(float * _a,float * _b) {
		float lsin[3];
		float lcos[3];
		_FSinCosSSE(_a[0]*0.5f,&lsin[0],&lcos[0]);
		_FSinCosSSE(_a[1]*0.5f,&lsin[1],&lcos[1]);
		_FSinCosSSE(_a[2]*0.5f,&lsin[2],&lcos[2]);

		__m128 v0=_mm_shuffle_ps(_mm_set_ss(1.0f),_mm_set_ss(-1.0f),0);
		__m128 v1=_mm_shuffle_ps(_mm_load_ss(&lsin[0]),_mm_load_ss(&lcos[0]),0x00);
		__m128 v2=_mm_shuffle_ps(_mm_load_ss(&lsin[1]),_mm_load_ss(&lcos[1]),0x00);
		__m128 v3=_mm_load_ss(&lsin[2]);
		__m128 v4=_mm_load_ss(&lcos[2]);
		v3 = _mm_shuffle_ps(v3,v3,0);
		v4 = _mm_shuffle_ps(v4,v4,0);
		__m128 v5 = _mm_shuffle_ps(v1,v1,0x0A);
		__m128 v6 = _mm_shuffle_ps(v2,v2,0x0A);
		//_b[0]=lcos[0]*lsin[1]*lsin[2]+lsin[0]*lcos[1]*lcos[2];
		//_b[2]=lcos[0]*lcos[1]*lsin[2]+lsin[0]*lsin[1]*lcos[2];
		//_b[1]=lsin[0]*lcos[1]*lsin[2]-lcos[0]*lsin[1]*lcos[2];
		//_b[3]=lsin[0]*lsin[1]*lsin[2]-lcos[0]*lcos[1]*lcos[2];
	}

// ************** quaternion matrix SSE function *******************

	void _NAKED _APICALL _Q4FMatrixSSE(float * ,float * )
	{
		QUATERNIONP4DMATRIXSSE_STD;
		RET_2;
	}

// ************** quaternion Inv Transform SSE function *******************

	void _APICALL _Q3FInvTransformSSE(float *,float *,float *)
	{
		QUATERNIONP3DTRANSFORMSSE_STD;
		RET_3;
	}

// ************** quaternion Mul SSE2 function *******************

	void _NAKED _APICALL _QDMulSSE2(double * ,double * ,double * )
	{
		QUATERNIONPDDMULSSE2_STD;
		RET_3;
	}

// ************** quaternion Inv Transform SSE2 function *******************

	void _NAKED _APICALL _Q3DInvTransformSSE2(double * ,double * ,double * ) {
		QUATERNIONP3DDTRANSFORMSSE2_STD;
		RET_3;
	}

// ************** quaternion Mul SSE3 function *******************

	void _NAKED _APICALL _QFMulSSE3(float * ,float * ,float * )
	{
		QUATERNIONPDMULSSE3_STD;
		RET_3;
	}

	void _NAKED _APICALL _QDMulSSE3(double * ,double * ,double * )
	{
		QUATERNIONPDDMULSSE3_STD;
		RET_3;
	}

// ************** quaternion matrix SSE3 function *******************

	void _NAKED _APICALL _Q3FInvTransformSSE3(float *,float *,float *)
	{
		QUATERNIONP3DTRANSFORMSSE3_STD;
		RET_3;
	}

// ************** quaternion Inv SSE4 function *******************

	void _NAKED _APICALL _QFInvSSE4(float *,float *)
	{
		QUATERNIONPDINVSSE4_STD;
		RET_2;
	}

	/*void _NAKED _STDCALL _QDInvSSE4(double *,double *)
	{
		QUATERNIONPDDINVSSE4_STD;
		RET_2;
	}*/

// ************** quaternion Mul SSE4 function *******************

	void _NAKED _APICALL _QFMulSSE4(float * ,float * ,float * )
	{
		QUATERNIONPDMULSSE4_STD;
		RET_3;
	}

	void _NAKED _APICALL _QDMulSSE4(double * ,double * ,double * )
	{
		QUATERNIONPDDMULSSE4_STD;
		RET_3;
	}

// ************** quaternion Matrix SSE4 function *******************

	void _NAKED _APICALL _Q4FMatrixSSE4(float * ,float * )
	{
		QUATERNIONP4DMATRIXSSE4_STD;
		RET_2;
	}

	void _NAKED _APICALL _Q4DMatrixSSE4(double * ,double * )
	{
		QUATERNIONP4DDMATRIXSSE4_STD;
		RET_2;
	}

// ************** quaternion Inv Transform SSE4 function *******************

	void _NAKED _APICALL _Q3FInvTransformSSE4(float * ,float * ,float * ) {
		QUATERNIONP3DTRANSFORMSSE4_STD;
		RET_3;
	}

	void _NAKED _APICALL _Q3DInvTransformSSE4(double * ,double * ,double * ) {
		QUATERNIONP3DDTRANSFORMSSE4_STD;
		RET_3;
	}

}

#endif

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif