/*
 * x86_64vector.cpp
 *
 *  Created on: 17.10.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifdef CPU_BT
#include "x86_64vector.h"

#ifdef CPU_X86_64

#include <bt/os.h>
#include "macrosasm.h"

#if defined(GCC) || defined(MINGW)
#include "x86_64intrin.h"
#include <x86intrin.h>
#include "../x86/macrosasm.h"
#endif

#if defined(MSVC)
#include <intrin.h>
#endif

#include "x86_64vector_add.h"
#include "x86_64vector_normal.h"
#include "x86_64vector_dotproduct.h"
#include "x86_64vector_length2.h"
#include "x86_64vector_lerp.h"
#include "../base/basemath.h"
#include "x86_64math.h"

WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

// ************************* SSE ****************************

// ************** vector Add SSE function *******************

#ifdef MSVC
void _APICALL _V2FAddSSE(float *a,float *b,float *c)
{
	__m128 v2;
	__m128 v3;
	v2 = _mm_setzero_ps();
	v3 = _mm_setzero_ps();
	v2 = _mm_loadl_pi(v2,(const __m64 *)a);
	v3 = _mm_loadl_pi(v3,(const __m64 *)b);
	__m128 v1 = _mm_add_ps(v2, v3);
	_mm_storel_pi((__m64 *)c, v1);
}
#else
void _APICALL _V2FAddSSE(float *,float *,float *)
{
	VECTORP2DADDSSE;
}
#endif

#ifdef MSVC
void _APICALL _V3FAddSSE(float *a,float *b,float *c)
{
	__m128 v2 = _mm_load_ss(a+2);
	__m128 v3 = _mm_load_ss(b+2);
	v2 = _mm_loadh_pi(v2,(const __m64 *)a);
	v3 = _mm_loadh_pi(v3,(const __m64 *)b);
	__m128 v1 = _mm_add_ps(v2, v3);
	_mm_storeh_pi((__m64 *)c, v1);
	_mm_store_ss(((float *)c + 2),v1);
}
#else
void _APICALL _V3FAddSSE(float *,float *,float *)
{
	VECTORP3DADDSSE;
}
#endif

#ifdef MSVC
void _APICALL _V4FAddSSE(float *a,float *b,float *c)
{
	__m128 v2 = _mm_loadl_pi(v2,(const __m64 *)(a+2));
	__m128 v3 = _mm_loadl_pi(v2,(const __m64 *)(b+2));
	v2 = _mm_loadh_pi(v2,(const __m64 *)a);
	v3 = _mm_loadh_pi(v3,(const __m64 *)b);
	__m128 v1 = _mm_add_ps(v2, v3);
	_mm_storeh_pi((__m64 *)c, v1);
	_mm_storel_pi((__m64 *)(c + 2),v1);
}
#else
void _APICALL _V4FAddSSE(float *,float *,float *)
{
	VECTORP4DADDSSE;
}
#endif

// ************** vector Sub SSE function *******************

void _APICALL _V2FSubSSE(float *a,float *b,float *c)
{
	__m128 v2;
	__m128 v3;
	v2 = _mm_setzero_ps();
	v3 = v2;
	v2 = _mm_loadl_pi(v2,(const __m64 *)a);
	v3 = _mm_loadl_pi(v3,(const __m64 *)b);
	__m128 v1 = _mm_sub_ps(v2, v3);
	_mm_storel_pi((__m64 *)c, v1);
}

void _APICALL _V3FSubSSE(float *a,float *b,float *c)
{
	__m128 v2 = _mm_load_ss(a+2);
	__m128 v3 = _mm_load_ss(b+2);
	v2 = _mm_loadh_pi(v2,(const __m64 *)a);
	v3 = _mm_loadh_pi(v3,(const __m64 *)b);
	__m128 v1 = _mm_sub_ps(v2, v3);
	_mm_storeh_pi((__m64 *)c, v1);
	_mm_store_ss(((float *)c + 2),v1);
}

// ************** vector Scale SSE function *******************

void _APICALL _V2FScaleSSE(float *a, float *b, float c)
{
	__m128 v2;
	__m128 v3;
	v2 = _mm_setzero_ps();
	v3 = _mm_set_ss(c);
	v2 = _mm_loadl_pi(v2,(const __m64 *)a);
	v3 = _mm_shuffle_ps(v3,v3,0);
	__m128 v1 = _mm_mul_ps(v2, v3);
	_mm_storel_pi((__m64 *)b, v1);
}

void _APICALL _V3FScaleSSE(float *a, float *b, float c)
{
	__m128 v2 = _mm_load_ss(a+2);
	__m128 v3 = _mm_set_ss(c);
	v2 = _mm_loadh_pi(v2,(const __m64 *)a);
	v3 = _mm_shuffle_ps(v3,v3,0);
	__m128 v1 = _mm_mul_ps(v2, v3);
	_mm_storeh_pi((__m64 *)b, v1);
	_mm_store_ss((float *)(b + 2),v1);
}

void _APICALL _V4FScaleSSE(float *a, float *b, float c)
{
	__m128 v2;
	__m128 v3 = _mm_set_ss(c);
	v2 = _mm_loadl_pi(v2,(const __m64 *)(a+2));
	v2 = _mm_loadh_pi(v2,(const __m64 *)a);
	v3 = _mm_shuffle_ps(v3,v3,0);
	__m128 v1 = _mm_mul_ps(v2, v3);
	_mm_storeh_pi((__m64 *)b, v1);
	_mm_storel_pi((__m64 *)(b + 2),v1);
}

// ************** vector Mul SSE function *******************

void _APICALL _V2FMulSSE(float *a,float *b,float *c)
{
	__m128 v2;
	__m128 v3;
	v2 = _mm_setzero_ps();
	v3 = _mm_setzero_ps();
	v2 = _mm_loadl_pi(v2,(const __m64 *)a);
	v3 = _mm_loadl_pi(v3,(const __m64 *)b);
	__m128 v1 = _mm_mul_ps(v2, v3);
	_mm_storel_pi((__m64 *)c, v1);
}

void _APICALL _V3FMulSSE(float *a,float *b,float *c)
{
	__m128 v2 = _mm_load_ss(a+2);
	__m128 v3 = _mm_load_ss(b+2);
	v2 = _mm_loadh_pi(v2,(const __m64 *)a);
	v3 = _mm_loadh_pi(v3,(const __m64 *)b);
	__m128 v1 = _mm_mul_ps(v2, v3);
	_mm_storeh_pi((__m64 *)c, v1);
	_mm_store_ss(((float *)c + 2),v1);
}

// ************** vector Div SSE function *******************

void _APICALL _V2FDivSSE(float *a,float *b,float *c)
{
	__m128 v2;
	__m128 v3;
	v2 = _mm_setzero_ps();
	v3 = _mm_setzero_ps();
	v2 = _mm_loadl_pi(v2,(const __m64 *)a);
	v3 = _mm_loadl_pi(v3,(const __m64 *)b);
	__m128 v1 = _mm_div_ps(v2, v3);
	_mm_storel_pi((__m64 *)c, v1);
}

void _APICALL _V3FDivSSE(float *a,float *b,float *c)
{
	__m128 v2 = _mm_load_ss(a+2);
	__m128 v3 = _mm_load_ss(b+2);
	v2 = _mm_loadh_pi(v2,(const __m64 *)a);
	v3 = _mm_loadh_pi(v3,(const __m64 *)b);
	__m128 v1 = _mm_div_ps(v2, v3);
	_mm_storeh_pi((__m64 *)c, v1);
	_mm_store_ss(((float *)c + 2),v1);
}

// ************** vector Cross SSE function *******************

void _APICALL _V3FCrossSSE(float *a,float *b,float *c)
{
	__m128 v0 = _mm_load_ss(a+2);
	__m128 v1 = _mm_load_ss(b+2);
	v0 = _mm_loadh_pi(v0,(const __m64 *)a);
	v1 = _mm_loadh_pi(v1,(const __m64 *)b);
	__m128 v2 = v0;
	__m128 v3 = v1;
	v0 = _mm_shuffle_ps(v0, v0, 0x32);
	v1 = _mm_shuffle_ps(v1, v1, 0x83);
	v2 = _mm_shuffle_ps(v2, v2, 0x83);
	v3 = _mm_shuffle_ps(v3, v3, 0x32);
	v0 = _mm_mul_ps(v0, v1);
	v2 = _mm_mul_ps(v2, v3);
	v0 = _mm_sub_ps(v0, v2);
	_mm_storeh_pi((__m64 *)c, v0);
	_mm_store_ss(((float *)c + 2),v0);
}

// ************** vector Normal SSE function *******************

#ifdef MSVC
void _APICALL _V2FNormalSSE(float *__formal, float *__formala)
{
	__m128 v2; // xmm0@1
	__m128 v3; // xmm2@1

	v2 = _mm_setzero_ps();
	v2 = _mm_loadl_pi(v2,(const __m64 *)__formal);
	v3 = _mm_mul_ps(v2, v2);
	v3 = _mm_sqrt_ss(_mm_add_ss(v3,_mm_shuffle_ps(v3, v3, 1)));
	_mm_storel_pi((__m64 *)__formala, _mm_div_ps(v2, _mm_shuffle_ps(v3, v3, 0)));
}
#else
void _APICALL _V2FNormalSSE(float *, float *)
{
	VECTORP2DNORMALSSE
}
#endif

#ifdef MSVC
void _APICALL _V3FNormalSSE(float *__formal, float *__formala)
{
	__m128 v2; // xmm0@1
	__m128 v3; // xmm1@1
	__m128 v4; // xmm2@1
	__m128 v5; // xmm1@1
	__m128 v6; // xmm2@1
	__m128 v7; // xmm0@1

	v2 = _mm_load_ss(__formal+2);
	v2 = _mm_loadh_pi(v2,(const __m64 *)__formal);
	v3 = _mm_mul_ps(v2, v2);
	v4 = v3;
	v5 = _mm_shuffle_ps(v3, v3, 14);
	v6 = _mm_add_ps(v4, v5);
	v6 = _mm_sqrt_ss(_mm_add_ss(v6,_mm_shuffle_ps(v5, v5, 1)));
	v7 = _mm_div_ps(v2, _mm_shuffle_ps(v6, v6, 0));
	_mm_storeh_pi((__m64 *)__formala, v7);
	_mm_store_ss(((float *)__formala + 2),v7);
	//*((float *)__formala + 2) = (float)v7.m128_f32[0];
}
#else
void _APICALL _V3FNormalSSE(float *, float *)
{
	VECTORP3DNORMALSSE
}
#endif

#ifdef MSVC
void _APICALL _V4FNormalSSE(float *__formal, float *__formala)
{
	__m128 v2; // xmm0@1
	__m128 v3; // xmm1@1
	__m128 v4; // xmm2@1

	v2 = _mm_loadl_pi(v2,(const __m64 *)(__formal+2));
	v2 = _mm_loadh_pi(v2,(const __m64 *)__formal);
	v3 = _mm_mul_ps(v2, v2);
	v4 = v3;
	v3 = _mm_movehl_ps(v3, v3);
	v4 = _mm_add_ps(v4, v3);
	v4 = _mm_sqrt_ss(_mm_add_ss(v4,_mm_shuffle_ps(v3, v3, 1)));
	v2 = _mm_div_ps(v2, _mm_shuffle_ps(v4, v4, 0));
	_mm_storeh_pi((__m64 *)__formala, v2);
	_mm_storel_pi((__m64 *)(__formala+2), v2);
}
#else
void _APICALL _V4FNormalSSE(float *, float *)
{
	VECTORP4DNORMALSSE
}
#endif

// ************** vector Fast Normal SSE function *******************

void _APICALL _V2FFastNormalSSE(float *__formal, float *__formala)
{
	__m128 v2; // xmm0@1
	__m128 v3; // xmm2@1

	v2 = _mm_setzero_ps();
	v2 = _mm_loadl_pi(v2,(const __m64 *)__formal);
	v3 = _mm_mul_ps(v2, v2);
	v3 = _mm_rsqrt_ss(_mm_add_ss(v3,_mm_shuffle_ps(v3, v3, 1)));
	_mm_storel_pi((__m64 *)__formala, _mm_mul_ps(v2, _mm_shuffle_ps(v3, v3, 0)));
}

void _APICALL _V3FFastNormalSSE(float *__formal, float *__formala)
{
	__m128 v2; // xmm0@1
	__m128 v3; // xmm1@1
	__m128 v4; // xmm2@1
	__m128 v5; // xmm1@1
	__m128 v6; // xmm2@1
	__m128 v7; // xmm0@1

	v2 = _mm_load_ss(__formal+2);
	v2 = _mm_loadh_pi(v2,(const __m64 *)__formal);
	v3 = _mm_mul_ps(v2, v2);
	v4 = v3;
	v5 = _mm_shuffle_ps(v3, v3, 14);
	v6 = _mm_add_ps(v4, v5);
	v6 = _mm_rsqrt_ss(_mm_add_ss(v6,_mm_shuffle_ps(v5, v5, 1)));
	v7 = _mm_mul_ps(v2, _mm_shuffle_ps(v6, v6, 0));
	_mm_storeh_pi((__m64 *)__formala, v7);
	_mm_store_ss(((float *)__formala + 2),v7);
	//*((float *)__formala + 2) = (float)v7.m128_f32[0];
}

void _APICALL _V4FFastNormalSSE(float *a, float *b)
{
	__m128 v2; // xmm0@1
	__m128 v3; // xmm1@1
	__m128 v4; // xmm2@1

	v2 = _mm_loadl_pi(v2,(const __m64 *)(a+2));
	v2 = _mm_loadh_pi(v2,(const __m64 *)a);
	v3 = _mm_mul_ps(v2, v2);
	v4 = v3;
	v3 = _mm_movehl_ps(v3, v3);
	v4 = _mm_add_ps(v4, v3);
	v4 = _mm_rsqrt_ss(_mm_add_ss(v4,_mm_shuffle_ps(v3, v3, 1)));
	v2 = _mm_mul_ps(v2, _mm_shuffle_ps(v4, v4, 0));
	_mm_storeh_pi((__m64 *)b, v2);
	_mm_storel_pi((__m64 *)(b+2), v2);
}

// ************** vector Lerp SSE function *******************

void _APICALL _V2FLerpSSE(float *a, float *b,float *c, float d)
{
	__m128 v1 = _mm_setzero_ps();
	__m128 v2 = v1;
	__m128 v3 =  _mm_load_ss(&d);
	v1 = _mm_loadl_pi(v1,(const __m64 *)a);
	v2 = _mm_loadl_pi(v2,(const __m64 *)b);
	v3 = _mm_shuffle_ps(v3,v3,0x50);
	v1 = _mm_add_ps(_mm_mul_ps(_mm_sub_ps(v2,v1), v3),v1);
	_mm_storel_pi((__m64 *)c, v1);
}

void _APICALL _V3FLerpSSE(float *a, float *b,float *c, float d)
{
	__m128 v1 = _mm_load_ss(a+2);
	__m128 v2 = _mm_load_ss(b+2);
	__m128 v3 = _mm_load_ss(&d);
	v1 = _mm_loadh_pi(v1,(const __m64 *)a);
	v2 = _mm_loadh_pi(v2,(const __m64 *)b);
	v3 = _mm_shuffle_ps(v3,v3,0);
	v1 = _mm_add_ps(_mm_mul_ps(_mm_sub_ps(v2,v1), v3),v1);
	_mm_storeh_pi((__m64 *)c, v1);
	_mm_store_ss((float *)(c + 2),v1);
}

void _APICALL _V4FLerpSSE(float *a, float *b,float *c, float d)
{
	__m128 v3 = _mm_load_ss(&d);
	__m128 v1 = _mm_loadl_pi(v1,(const __m64 *)(a+2));
	__m128 v2 = _mm_loadl_pi(v2,(const __m64 *)(b+2));
	v1 = _mm_loadh_pi(v1,(const __m64 *)a);
	v2 = _mm_loadh_pi(v2,(const __m64 *)b);
	v3 = _mm_shuffle_ps(v3,v3,0);
	v1 = _mm_add_ps(_mm_mul_ps(_mm_sub_ps(v2,v1), v3),v1);
	_mm_storeh_pi((__m64 *)c, v1);
	_mm_storel_pi((__m64 *)(c + 2),v1);
}

// ************** vector Angle SSE function *******************

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
}

// ************** vector Transform SSE function *******************

void _APICALL _V2FTransformSSE(float *a,void *b,float *c)
{
	__m128 v1 = _mm_setzero_ps();
	__m128 v2 = _mm_setzero_ps();
	__m128 v4 = _mm_setzero_ps();
	v1 = _mm_loadl_pi(v1,(const __m64 *)b);
	v2 = _mm_loadl_pi(v2,((const __m64 *)b)+2);
	v4 = _mm_loadl_pi(v4,((const __m64 *)b)+6);
	__m128 v5 = _mm_load_ss(a);
	__m128 v6 = _mm_load_ss(a+1);
	v2=_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v5,v5,0x50),v1),_mm_mul_ps(_mm_shuffle_ps(v6,v6,0x50),v2)),v4);
	_mm_storel_pi((__m64 *)c, v2);
}

void _APICALL _V3FTransformSSE(float *a,void *b,float *c)
{
	__m128 v1 = _mm_load_ss(((const float*)b)+2);
	__m128 v2 = _mm_load_ss(((const float*)b)+6);
	v1 = _mm_loadh_pi(v1,((const __m64 *)b));
	v2 = _mm_loadh_pi(v2,((const __m64 *)b)+2);
	__m128 v3 = _mm_load_ss(((const float*)b)+10);
	__m128 v4 = _mm_load_ss(((const float*)b)+14);
	v3 = _mm_loadh_pi(v3,((const __m64 *)b)+4);
	v4 = _mm_loadh_pi(v4,((const __m64 *)b)+6);
	__m128 v5 = _mm_load_ss(a);
	__m128 v6 = _mm_load_ss(a+1);
	v2=_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v5,v5,0x04),v1),_mm_mul_ps(_mm_shuffle_ps(v6,v6,0x04),v2)),v4);
	v5 = _mm_load_ss(a+2);
	v4=_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v5,v5,0x04),v3),v2);
	_mm_storeh_pi((__m64 *)c, v4);
	_mm_store_ss(c+2, v4);
}

void _APICALL _V4FTransformSSE(float *a,void *b,float *c)
{
	__m128 v1 = _mm_loadl_pi(v1,(const __m64 *)b);
	__m128 v2 = _mm_loadl_pi(v2,((const __m64 *)b)+2);
	v1 = _mm_loadh_pi(v1,((const __m64 *)b)+1);
	v2 = _mm_loadh_pi(v2,((const __m64 *)b)+3);
	__m128 v3 = _mm_loadl_pi(v3,((const __m64 *)b)+4);
	__m128 v4 = _mm_loadl_pi(v4,((const __m64 *)b)+6);
	v3 = _mm_loadh_pi(v3,((const __m64 *)b)+5);
	v4 = _mm_loadh_pi(v4,((const __m64 *)b)+7);
	__m128 v5 = _mm_load_ss(a);
	__m128 v6 = _mm_load_ss(a+1);
	v2=_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v5,v5,0),v1),_mm_mul_ps(_mm_shuffle_ps(v6,v6,0),v2));
	v5 = _mm_load_ss(a+2);
	v6 = _mm_load_ss(a+3);
	v4=_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v5,v5,0),v3),_mm_mul_ps(_mm_shuffle_ps(v6,v6,0),v4)),v2);
	_mm_storel_pi((__m64 *)c, v4);
	_mm_storeh_pi((__m64 *)(c + 2),v4);
}

// ************** vector MMul SSE function *******************

void _APICALL _V2FMMulSSE(float *a,void *b,float *c)
{
	__m128 v1 = _mm_setzero_ps();
	__m128 v2 = _mm_setzero_ps();
	v1 = _mm_loadl_pi(v1,(const __m64 *)b);
	v2 = _mm_loadl_pi(v2,((const __m64 *)b)+2);
	__m128 v5 = _mm_load_ss(a);
	__m128 v6 = _mm_load_ss(a+1);
	v2=_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v5,v5,0x50),v1),_mm_mul_ps(_mm_shuffle_ps(v6,v6,0x50),v2));
	_mm_storel_pi((__m64 *)c, v2);
}

void _APICALL _V3FMMulSSE(float *a,void *b,float *c)
{
	__m128 v1 = _mm_load_ss(((const float*)b)+2);
	__m128 v2 = _mm_load_ss(((const float*)b)+6);
	v1 = _mm_loadh_pi(v1,((const __m64 *)b));
	v2 = _mm_loadh_pi(v2,((const __m64 *)b)+2);
	__m128 v3 = _mm_load_ss(((const float*)b)+10);
	v3 = _mm_loadh_pi(v3,((const __m64 *)b)+4);
	__m128 v5 = _mm_load_ss(a);
	__m128 v6 = _mm_load_ss(a+1);
	v2=_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v5,v5,0x04),v1),_mm_mul_ps(_mm_shuffle_ps(v6,v6,0x04),v2));
	v5 = _mm_load_ss(a+2);
	v2=_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v5,v5,0x04),v3),v2);
	_mm_storeh_pi((__m64 *)c, v2);
	_mm_store_ss(c+2, v2);
}

// ************************* SSE2 ****************************

// ************** vector Add SSE2 function *******************

#ifdef MSVC
void _APICALL _V2FAddSSE2(float *a,float *b,float *c)
{
	__m128 v1;
	__m128 v2;
	__m128 v3;

	*(__m128d*)&v2=_mm_load_sd((const double *)a);
	*(__m128d*)&v3=_mm_load_sd((const double *)b);
	v1 = _mm_add_ps(v2, v3);
	_mm_storel_pi((__m64 *)c, v1);
}
#else
void _APICALL _V2FAddSSE2(float *,float *,float *)
{
	VECTORP2DADDSSE2
}
#endif

#ifdef MSVC
void _APICALL _V4FAddSSE2(float *a,float *b,float *c)
{
	__m128 v1;
	__m128 v2;
	__m128 v3;

	*(__m128d*)&v2=_mm_load_sd((const double *)a);
	v2=_mm_loadh_pi(v2,(const __m64 *)(a+2));
	*(__m128d*)&v3=_mm_load_sd((const double *)b);
	v3=_mm_loadh_pi(v3,(const __m64 *)(b+2));
	v1 = _mm_add_ps(v2, v3);
	_mm_store_sd((double *)c, *(__m128d*)&v1);
	_mm_storeh_pi((__m64 *)(c+2), v1);
}
#else
void _APICALL _V4FAddSSE2(float *,float *,float *)
{
	VECTORP4DADDSSE2
}
#endif

#ifdef MSVC
void _APICALL _V2DAddSSE2(double *a,double *b,double *c)
{
	__m128d v2=_mm_loadu_pd((const double *)a);
	__m128d v3=_mm_loadu_pd((const double *)b);
	__m128d v1 = _mm_add_pd(v2, v3);
	_mm_storeu_pd(c, v1);
}
#else
void _APICALL _V2DAddSSE2(double *,double *,double *)
{
	VECTORP2DDADDSSE2
}
#endif

#ifdef MSVC
void _APICALL _V3DAddSSE2(double *a,double *b,double *c)
{
	__m128d v2=_mm_loadu_pd((const double *)a);
	__m128d v3=_mm_loadu_pd((const double *)b);
	__m128d v5=_mm_load_sd((const double *)(a+2));
	__m128d v4=_mm_load_sd((const double *)(b+2));
	__m128d v1 = _mm_add_pd(v2, v3);
	__m128d v0 = _mm_add_sd(v5, v4);
	_mm_storeu_pd(c, v1);
	_mm_store_sd(c+2, v0);
}
#else
void _APICALL _V3DAddSSE2(double *,double *,double *)
{
	VECTORP3DDADDSSE2
}
#endif

#ifdef MSVC
void _APICALL _V4DAddSSE2(double *a,double *b,double *c)
{
	__m128d v2=_mm_loadu_pd((const double *)a);
	__m128d v3=_mm_loadu_pd((const double *)b);
	__m128d v5=_mm_loadu_pd((const double *)(a+2));
	__m128d v4=_mm_loadu_pd((const double *)(b+2));
	__m128d v1 = _mm_add_pd(v2, v3);
	__m128d v0 = _mm_add_pd(v5, v4);
	_mm_storeu_pd(c, v1);
	_mm_storeu_pd(c+2, v0);
}
#else
void _APICALL _V4DAddSSE2(double *,double *,double *)
{
	VECTORP4DDADDSSE2
}
#endif

// ************** vector Sub SSE2 function *******************

void _APICALL _V2FSubSSE2(float *a,float *b,float *c)
{
	__m128 v1;
	__m128 v2;
	__m128 v3;

	*(__m128d*)&v2=_mm_load_sd((const double *)a);
	*(__m128d*)&v3=_mm_load_sd((const double *)b);
	v1 = _mm_sub_ps(v2, v3);
	_mm_storel_pi((__m64 *)c, v1);
}

void _APICALL _V4FSubSSE2(float *a,float *b,float *c)
{
	__m128 v1;
	__m128 v2;
	__m128 v3;

	*(__m128d*)&v2=_mm_load_sd((const double *)a);
	v2=_mm_loadh_pi(v2,(const __m64 *)(a+2));
	*(__m128d*)&v3=_mm_load_sd((const double *)b);
	v3=_mm_loadh_pi(v3,(const __m64 *)(b+2));
	v1 = _mm_sub_ps(v2, v3);
	_mm_store_sd((double *)c, *(__m128d*)&v1);
	_mm_storeh_pi((__m64 *)(c+2), v1);
}

void _APICALL _V2DSubSSE2(double *a,double *b,double *c)
{
	__m128d v2=_mm_loadu_pd((const double *)a);
	__m128d v3=_mm_loadu_pd((const double *)b);
	__m128d v1 = _mm_sub_pd(v2, v3);
	_mm_storeu_pd(c, v1);
}

void _APICALL _V3DSubSSE2(double *a,double *b,double *c)
{
	__m128d v2=_mm_loadu_pd((const double *)a);
	__m128d v3=_mm_loadu_pd((const double *)b);
	__m128d v5=_mm_load_sd((const double *)(a+2));
	__m128d v4=_mm_load_sd((const double *)(b+2));
	__m128d v1 = _mm_sub_pd(v2, v3);
	__m128d v0 = _mm_sub_sd(v5, v4);
	_mm_storeu_pd(c, v1);
	_mm_store_sd(c+2, v0);
}

void _APICALL _V4DSubSSE2(double *a,double *b,double *c)
{
	__m128d v2=_mm_loadu_pd((const double *)a);
	__m128d v3=_mm_loadu_pd((const double *)b);
	__m128d v5=_mm_loadu_pd((const double *)(a+2));
	__m128d v4=_mm_loadu_pd((const double *)(b+2));
	__m128d v1 = _mm_sub_pd(v2, v3);
	__m128d v0 = _mm_sub_pd(v5, v4);
	_mm_storeu_pd(c, v1);
	_mm_storeu_pd(c+2, v0);
}

// ************** vector Scale SSE2 function *******************

void _APICALL _V2DScaleSSE2(double *a, double *b, double c)
{
	__m128d v3=_mm_set_sd(c);
	__m128d v2=_mm_loadu_pd((const double *)a);
	v3 = _mm_shuffle_pd(v3,v3,0);
	__m128d v1 = _mm_mul_pd(v2, v3);
	_mm_storeu_pd(b, v1);
}

void _APICALL _V3DScaleSSE2(double *a, double *b, double c)
{
	__m128d v3=_mm_set_sd(c);
	__m128d v2=_mm_loadu_pd((const double *)a);
	__m128d v4=_mm_load_sd((const double *)(a+2));
	v3 = _mm_shuffle_pd(v3,v3,0);
	__m128d v1 = _mm_mul_pd(v2, v3);
	__m128d v5 = _mm_mul_sd(v4, v3);
	_mm_storeu_pd(b, v1);
	_mm_store_sd(b+2, v5);
}

void _APICALL _V4DScaleSSE2(double *a, double *b, double c)
{
	__m128d v3=_mm_set_sd(c);
	__m128d v2=_mm_loadu_pd((const double *)a);
	__m128d v4=_mm_loadu_pd((const double *)(a+2));
	v3 = _mm_shuffle_pd(v3,v3,0);
	__m128d v1 = _mm_mul_pd(v2, v3);
	__m128d v5 = _mm_mul_pd(v4, v3);
	_mm_storeu_pd(b, v1);
	_mm_storeu_pd(b+2, v5);
}

// ************** vector Mul SSE2 function *******************

void _APICALL _V2FMulSSE2(float *a,float *b,float *c)
{
	__m128 v1;
	__m128 v2;
	__m128 v3;

	*(__m128d*)&v2=_mm_load_sd((const double *)a);
	*(__m128d*)&v3=_mm_load_sd((const double *)b);
	v1 = _mm_mul_ps(v2, v3);
	_mm_storel_pi((__m64 *)c, v1);
}

void _APICALL _V4FMulSSE2(float *a,float *b,float *c)
{
	__m128 v1;
	__m128 v2;
	__m128 v3;

	*(__m128d*)&v2=_mm_load_sd((const double *)a);
	v2=_mm_loadh_pi(v2,(const __m64 *)(a+2));
	*(__m128d*)&v3=_mm_load_sd((const double *)b);
	v3=_mm_loadh_pi(v3,(const __m64 *)(b+2));
	v1 = _mm_mul_ps(v2, v3);
	_mm_storel_pi((__m64 *)c, v1);
	_mm_storeh_pi(((__m64 *)c)+1, v1);
}

void _APICALL _V2DMulSSE2(double *a,double *b,double *c)
{
	__m128d v2=_mm_loadu_pd((const double *)a);
	__m128d v3=_mm_loadu_pd((const double *)b);
	__m128d v1 = _mm_mul_pd(v2, v3);
	_mm_storeu_pd(c, v1);
}

void _APICALL _V3DMulSSE2(double *a,double *b,double *c)
{
	__m128d v2=_mm_loadu_pd((const double *)a);
	__m128d v3=_mm_loadu_pd((const double *)b);
	__m128d v5=_mm_load_sd((const double *)(a+2));
	__m128d v4=_mm_load_sd((const double *)(b+2));
	__m128d v1 = _mm_mul_pd(v2, v3);
	__m128d v0 = _mm_mul_sd(v5, v4);
	_mm_storeu_pd(c, v1);
	_mm_store_sd(c+2, v0);
}

void _APICALL _V4DMulSSE2(double *a,double *b,double *c)
{
	__m128d v2=_mm_loadu_pd((const double *)a);
	__m128d v3=_mm_loadu_pd((const double *)b);
	__m128d v5=_mm_loadu_pd((const double *)a+2);
	__m128d v4=_mm_loadu_pd((const double *)b+2);
	__m128d v1 = _mm_mul_pd(v2, v3);
	__m128d v0 = _mm_mul_pd(v5, v4);
	_mm_storeu_pd(c, v1);
	_mm_storeu_pd(c+2, v0);
}

// ************** vector Div SSE2 function *******************

void _APICALL _V2FDivSSE2(float *a,float *b,float *c)
{
	__m128 v1;
	__m128 v2;
	__m128 v3;

	*(__m128d*)&v2=_mm_load_sd((const double *)a);
	*(__m128d*)&v3=_mm_load_sd((const double *)b);
	v1 = _mm_div_ps(v2, v3);
	_mm_storel_pi((__m64 *)c, v1);
}

void _APICALL _V4FDivSSE2(float *a,float *b,float *c)
{
	__m128 v1;
	__m128 v2;
	__m128 v3;

	*(__m128d*)&v2=_mm_load_sd((const double *)a);
	v2=_mm_loadh_pi(v2,(const __m64 *)(a+2));
	*(__m128d*)&v3=_mm_load_sd((const double *)b);
	v3=_mm_loadh_pi(v3,(const __m64 *)(b+2));
	v1 = _mm_div_ps(v2, v3);
	_mm_storel_pi((__m64 *)c, v1);
	_mm_storeh_pi(((__m64 *)c)+1, v1);
}

void _APICALL _V2DDivSSE2(double *a,double *b,double *c)
{
	__m128d v2=_mm_loadu_pd((const double *)a);
	__m128d v3=_mm_loadu_pd((const double *)b);
	__m128d v1 = _mm_div_pd(v2, v3);
	_mm_storeu_pd(c, v1);
}

void _APICALL _V3DDivSSE2(double *a,double *b,double *c)
{
	__m128d v2=_mm_loadu_pd((const double *)a);
	__m128d v3=_mm_loadu_pd((const double *)b);
	__m128d v5=_mm_load_sd((const double *)(a+2));
	__m128d v4=_mm_load_sd((const double *)(b+2));
	__m128d v1 = _mm_div_pd(v2, v3);
	__m128d v0 = _mm_div_sd(v5, v4);
	_mm_storeu_pd(c, v1);
	_mm_store_sd(c+2, v0);
}

void _APICALL _V4DDivSSE2(double *a,double *b,double *c)
{
	__m128d v2=_mm_loadu_pd((const double *)a);
	__m128d v3=_mm_loadu_pd((const double *)b);
	__m128d v5=_mm_loadu_pd((const double *)a+2);
	__m128d v4=_mm_loadu_pd((const double *)b+2);
	__m128d v1 = _mm_div_pd(v2, v3);
	__m128d v0 = _mm_div_pd(v5, v4);
	_mm_storeu_pd(c, v1);
	_mm_storeu_pd(c+2, v0);
}

// ************** vector Normal SSE2 function *******************

void _APICALL _V2DNormalSSE2(double *a, double *b)
{
	__m128d v2=_mm_loadu_pd((const double *)a);
	__m128d v0 = _mm_mul_pd(v2, v2);
	__m128d v1;
	*(__m128*)&v1 = _mm_movehl_ps(*(__m128*)&v1, *(__m128*)&v0);
	v1 = _mm_sqrt_sd(v1,_mm_add_sd(v1,v0));
	*(__m128*)&v1 = _mm_movelh_ps(*(__m128*)&v1, *(__m128*)&v1);
	v2 = _mm_div_pd(v2, v1);
	_mm_storeu_pd(b, v2);
}

void _APICALL _V3DNormalSSE2(double *a, double *b)
{
	__m128d v2 = _mm_load_sd(a+2);
	__m128d v3=_mm_loadu_pd((const double *)a);
	__m128d v0 = _mm_mul_sd(v2, v2);
	__m128d v1 = _mm_mul_pd(v3, v3);
	v0 = _mm_add_sd(v0,v1);
	*(__m128*)&v1 = _mm_movehl_ps(*(__m128*)&v1, *(__m128*)&v1);
	v1 = _mm_sqrt_sd(v1,_mm_add_sd(v1,v0));
	*(__m128*)&v1 = _mm_movelh_ps(*(__m128*)&v1, *(__m128*)&v1);
	v2 = _mm_div_sd(v2, v1);
	v3 = _mm_div_pd(v3, v1);
	_mm_store_sd(b+2, v2);
	_mm_storeu_pd(b, v3);
}

void _APICALL _V4DNormalSSE2(double *a, double *b)
{
	__m128d v2 = _mm_loadu_pd((const double *)(a+2));
	__m128d v3 = _mm_loadu_pd((const double *)a);
	__m128d v0 = _mm_mul_pd(v2, v2);
	__m128d v1 = _mm_mul_pd(v3, v3);
	v1 = _mm_add_pd(v1,v0);
	*(__m128*)&v1 = _mm_movehl_ps(*(__m128*)&v1, *(__m128*)&v1);
	v1 = _mm_sqrt_sd(v1,_mm_add_sd(v1,v0));
	*(__m128*)&v1 = _mm_movelh_ps(*(__m128*)&v1, *(__m128*)&v1);
	v2 = _mm_div_pd(v2, v1);
	v3 = _mm_div_pd(v3, v1);
	_mm_storeu_pd(b+2, v2);
	_mm_storeu_pd(b, v3);
}

// ************** vector Fast Normal SSE2 function *******************

void _APICALL _V2DFastNormalSSE2(double *a, double *b)
{
	__m128d v2=_mm_loadu_pd((const double *)a);
	__m128d v0 = _mm_mul_pd(v2, v2);
	__m128d v1;
	*(__m128*)&v1 = _mm_movehl_ps(*(__m128*)&v1, *(__m128*)&v0);
	v1 = _mm_cvtps_pd(_mm_rsqrt_ss(_mm_cvtpd_ps(_mm_add_sd(v1,v0))));
	*(__m128*)&v1 = _mm_movelh_ps(*(__m128*)&v1, *(__m128*)&v1);
	v2 = _mm_mul_pd(v2, v1);
	_mm_storeu_pd(b, v2);
}

void _APICALL _V3DFastNormalSSE2(double *a, double *b)
{
	__m128d v2 = _mm_load_sd(a+2);
	__m128d v3 = _mm_loadu_pd((const double *)a);
	__m128d v0 = _mm_mul_sd(v2, v2);
	__m128d v1 = _mm_mul_pd(v3, v3);
	v0 = _mm_add_sd(v0,v1);
	*(__m128*)&v1 = _mm_movehl_ps(*(__m128*)&v1, *(__m128*)&v1);
	v1 = _mm_cvtps_pd(_mm_rsqrt_ss(_mm_cvtpd_ps(_mm_add_sd(v1,v0))));
	*(__m128*)&v1 = _mm_movelh_ps(*(__m128*)&v1, *(__m128*)&v1);
	v2 = _mm_mul_sd(v2, v1);
	v3 = _mm_mul_pd(v3, v1);
	_mm_store_sd(b+2, v2);
	_mm_storeu_pd(b, v3);
}

void _APICALL _V4DFastNormalSSE2(double *a, double *b)
{
	__m128d v2 = _mm_loadu_pd((const double *)(a+2));
	__m128d v3 = _mm_loadu_pd((const double *)a);
	__m128d v0 = _mm_mul_pd(v2, v2);
	__m128d v1 = _mm_mul_pd(v3, v3);
	v1 = _mm_add_pd(v1,v0);
	*(__m128*)&v1 = _mm_movehl_ps(*(__m128*)&v1, *(__m128*)&v1);
	v1 = _mm_cvtps_pd(_mm_rsqrt_ss(_mm_cvtpd_ps(_mm_add_sd(v1,v0))));
	*(__m128*)&v1 = _mm_movelh_ps(*(__m128*)&v1, *(__m128*)&v1);
	v2 = _mm_mul_pd(v2, v1);
	v3 = _mm_mul_pd(v3, v1);
	_mm_storeu_pd(b+2, v2);
	_mm_storeu_pd(b, v3);
}

// ************** vector Lerp SSE2 function *******************

void _APICALL _V2DLerpSSE2(double *a, double *b,double *c, double d)
{
	__m128d v1 = _mm_loadu_pd((const double *)a);
	__m128d v2 = _mm_loadu_pd((const double *)b);
	__m128d v3 =  _mm_load_sd(&d);
	v3 = _mm_shuffle_pd(v3,v3,0x00);
	v1 = _mm_add_pd(_mm_mul_pd(_mm_sub_pd(v2,v1), v3),v1);
	_mm_storeu_pd(c, v1);
}

void _APICALL _V3DLerpSSE2(double *a, double *b,double *c, double d)
{
	__m128d v1 = _mm_loadu_pd((const double *)a);
	__m128d v2 = _mm_loadu_pd((const double *)b);
	__m128d v3 =  _mm_load_sd(&d);
	__m128d v4 = _mm_load_sd((const double *)(a+2));
	__m128d v5 = _mm_load_sd((const double *)(b+2));
	v3 = _mm_shuffle_pd(v3,v3,0x00);
	v1 = _mm_add_pd(_mm_mul_pd(_mm_sub_pd(v2,v1), v3),v1);
	v4 = _mm_add_sd(_mm_mul_sd(_mm_sub_sd(v5,v4), v3),v4);
	_mm_storeu_pd(c, v1);
	_mm_store_sd(c+2, v4);
}

void _APICALL _V4DLerpSSE2(double *a, double *b,double *c, double d)
{
	__m128d v1 = _mm_loadu_pd((const double *)a);
	__m128d v2 = _mm_loadu_pd((const double *)b);
	__m128d v3 =  _mm_load_sd(&d);
	__m128d v4 = _mm_loadu_pd((const double *)(a+2));
	__m128d v5 = _mm_loadu_pd((const double *)(b+2));
	v3 = _mm_shuffle_pd(v3,v3,0x00);
	v1 = _mm_add_pd(_mm_mul_pd(_mm_sub_pd(v2,v1), v3),v1);
	v4 = _mm_add_pd(_mm_mul_pd(_mm_sub_pd(v5,v4), v3),v4);
	_mm_storeu_pd(c, v1);
	_mm_storeu_pd(c+2, v4);
}

// ************** vector Reflect SSE2 function *******************

void _APICALL _V2DReflectSSE2(double * _a,double * _b,double * _c)
{
	__m128d v3 = _mm_loadu_pd((const double *)_a);
	__m128d v1 = _mm_loadu_pd((const double *)_b);
	__m128d v5 = _mm_mul_pd(v1, v3);
	__m128d v4;
	*(__m128*)&v4 = _mm_movehl_ps(*(__m128*)&v4, *(__m128*)&v5);
	v5 = _mm_add_sd(v5,v4);
	*(__m128*)&v5 = _mm_movelh_ps(*(__m128*)&v5, *(__m128*)&v5);
	v1 = _mm_mul_pd(v1, v5);
	v3 = _mm_sub_pd(v3, v1);
	_mm_storeu_pd(_c, v3);
}

void _APICALL _V3DReflectSSE2(double * _a,double * _b,double * _c)
{
	__m128d v2 = _mm_load_sd(_a+2);
	__m128d v3 = _mm_loadu_pd((const double *)_a);
	__m128d v0 = _mm_load_sd(_b+2);
	__m128d v1 = _mm_loadu_pd((const double *)_b);
	__m128d v4 = _mm_mul_sd(v0, v2);
	__m128d v5 = _mm_mul_pd(v1, v3);
	v4 = _mm_add_sd(v4,v5);
	*(__m128*)&v5 = _mm_movehl_ps(*(__m128*)&v5, *(__m128*)&v5);
	v5 = _mm_add_sd(v5,v4);
	*(__m128*)&v5 = _mm_movelh_ps(*(__m128*)&v5, *(__m128*)&v5);
	v0 = _mm_mul_sd(v0, v5);
	v1 = _mm_mul_pd(v1, v5);
	v2 = _mm_sub_sd(v2, v0);
	v3 = _mm_sub_pd(v3, v1);
	_mm_store_sd(_c+2, v2);
	_mm_storeu_pd(_c, v3);
}

// ************** vector Transform SSE2 function *******************

void _APICALL _V2FTransformSSE2(float *a,void *b,float *c)
{
	__m128 v1;
	__m128 v2;
	__m128 v4;
	*(__m128d*)&v1 = _mm_load_sd((const double *)b);
	*(__m128d*)&v2 = _mm_load_sd(((const double *)b)+2);
	*(__m128d*)&v4 = _mm_load_sd(((const double *)b)+6);
	__m128 v5 = _mm_load_ss(a);
	__m128 v6 = _mm_load_ss(a+1);
	v2=_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v5,v5,0x50),v1),_mm_mul_ps(_mm_shuffle_ps(v6,v6,0x50),v2)),v4);
	_mm_storel_pi((__m64 *)c, v2);
}

void _APICALL _V2DTransformSSE2(double *a,void *b,double *c)
{
	__m128d v1 = _mm_load_sd((const double *)b);
	__m128d v2 = _mm_load_sd(((const double *)b)+4);
	__m128d v4 = _mm_load_sd(((const double *)b)+12);
	*(__m128 *)&v1 = _mm_loadh_pi(*(__m128 *)&v1,((const __m64 *)b)+1);
	*(__m128 *)&v2 = _mm_loadh_pi(*(__m128 *)&v2,((const __m64 *)b)+5);
	*(__m128 *)&v4 = _mm_loadh_pi(*(__m128 *)&v4,((const __m64 *)b)+13);
	__m128d v5 = _mm_load_sd(a);
	__m128d v6 = _mm_load_sd(a+1);
	v2=_mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_shuffle_pd(v5,v5,0x50),v1),_mm_mul_pd(_mm_shuffle_pd(v6,v6,0x50),v2)),v4);
	_mm_store_sd(c, v2);
	_mm_storeh_pi((__m64 *)(c+1), *(__m128 *)&v2);
}

// ************************* SSE3 ***************************

// ************** vector revers SSE3 function *******************

	void _APICALL _V4R32SSE3(int *a,int *b) {
		__m128 v1;
		*(__m128i*)&v1=_mm_lddqu_si128((const __m128i *)a);
		v1=_mm_shuffle_ps(v1,v1,0x1B);
		_mm_storeu_ps((float*)b, v1);
	}

	void _APICALL _V4R64SSE3(_int64 *a,_int64 *b) {
		__m128d v1;
		__m128d v2;
		*(__m128i*)&v1=_mm_lddqu_si128((const __m128i *)(a));
		*(__m128i*)&v2=_mm_lddqu_si128((const __m128i *)(a+2));
		v1=_mm_shuffle_pd(v1,v1,0x1);
		v2=_mm_shuffle_pd(v2,v2,0x1);
		_mm_storeu_pd((double*)(b), v2);
		_mm_storeu_pd((double*)(b+2), v1);
	}

// ************** vector Add SSE3 function *******************

void _APICALL _V4FAddSSE3(float *a,float *b,float *c)
{
	__m128 v1;
	__m128 v2;
	__m128 v3;

	*(__m128i*)&v2=_mm_lddqu_si128((const __m128i *)a);
	*(__m128i*)&v3=_mm_lddqu_si128((const __m128i *)b);
	v1 = _mm_add_ps(v2, v3);
	_mm_storel_pi((__m64 *)c, v1);
	_mm_storeh_pi(((__m64 *)c)+1, v1);
}

void _APICALL _V2DAddSSE3(double *a,double *b,double *c)
{
	__m128d v1;
	__m128d v2;
	__m128d v3;

	*(__m128i*)&v2=_mm_lddqu_si128((const __m128i *)a);
	*(__m128i*)&v3=_mm_lddqu_si128((const __m128i *)b);
	v1 = _mm_add_pd(v2, v3);
	_mm_storeu_pd(c, v1);
}

void _APICALL _V4DAddSSE3(double *a,double *b,double *c)
{
	__m128d v1;
	__m128d v2;
	__m128d v3;
	__m128d v4;
	__m128d v5;
	__m128d v6;

	*(__m128i*)&v2=_mm_lddqu_si128((const __m128i *)a);
	*(__m128i*)&v3=_mm_lddqu_si128((const __m128i *)b);
	*(__m128i*)&v4=_mm_lddqu_si128((const __m128i *)(a+2));
	*(__m128i*)&v5=_mm_lddqu_si128((const __m128i *)(b+2));
	v1 = _mm_add_pd(v2, v3);
	v6 = _mm_add_pd(v4, v5);
	_mm_storeu_pd(c, v1);
	_mm_storeu_pd(c+2, v6);
}

// ************** vector Angle SSE3 function *******************

float _APICALL _V3FAngleSSE3(float * _a,float * _b)
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

	return _FArcTgSSE3(_x,_y);
}

// ************************* SSE4 ****************************

// ************** vector Add SSE4 function *******************

void _APICALL _V4FAddSSE4(float *a,float *b,float *c)
{
	__m128 v1;
	__m128 v2;
	__m128 v3;

	*(__m128i*)&v2=_mm_lddqu_si128((const __m128i *)a);
	*(__m128i*)&v3=_mm_lddqu_si128((const __m128i *)b);
	v1 = _mm_add_ps(v2, v3);
	_mm_storeu_ps(c, v1);
}

// ************** vector Scale SSE4 function *******************

void _APICALL _V4FScaleSSE4(float *a,float *b,float c)
{
	__m128 v1;
	*(__m128i*)&v1 = _mm_lddqu_si128((const __m128i *)a);
	__m128 v2 = _mm_set_ss(c);
	_mm_storeu_ps(b, _mm_mul_ps(v1,_mm_shuffle_ps(v2, v2, 0x0)));
}

void _APICALL _V2DScaleSSE4(double *a,double *b,double c)
{
	__m128d v1;
	*(__m128i*)&v1 = _mm_lddqu_si128((const __m128i *)a);
	_mm_storeu_pd(b, _mm_mul_pd(v1,_mm_movedup_pd(_mm_set_sd(c))));
}

void _APICALL _V4DScaleSSE4(double *a,double *b,double c)
{
	__m128d v1;
	__m128d v2;
	*(__m128i*)&v1 = _mm_lddqu_si128((const __m128i *)a);
	*(__m128i*)&v2 = _mm_lddqu_si128((const __m128i *)(a+2));
	__m128d v3 = _mm_movedup_pd(_mm_set_sd(c));
	_mm_storeu_pd(b, _mm_mul_pd(v1,v3));
	_mm_storeu_pd(b+2, _mm_mul_pd(v2,v3));
}

// ************** vector mul2n Round SSE4 function *******************

void _APICALL _V2Fmul2NRoundSSE4(float *a,int *b,int c)
{
	__m128 v1;
	*(__m128i*)&v1=_mm_cvtsi32_si128(((c+0x7F)&0xFF)<<23);
	__m128 v2 = _mm_load_ss(a);
	__m128 v3 = _mm_load_ss(a+1);
	b[0] =_mm_cvt_ss2si(_mm_mul_ps(v2,v1));
	b[1] =_mm_cvt_ss2si(_mm_mul_ps(v3,v1));
}

void _APICALL _V3Fmul2NRoundSSE4(float *a,int *b,int c)
{
	__m128 v1;
	__m128 v2 = _mm_load_ss(a+2);
	__m128 v3;
	*(__m128i*)&v1=_mm_cvtsi32_si128(((c+0x7F)&0xFF)<<23);
	v1=_mm_shuffle_ps(v1,v1,0x04);
	v2 = _mm_loadh_pi(v2,(__m64*)a);
	*(__m128i*)&v3 =_mm_cvtps_epi32(_mm_mul_ps(v2,v1));
	_mm_storeh_pi((__m64 *)b, v3);
	_mm_store_ss((float*)b+2, v3);
}

void _APICALL _V4Fmul2NRoundSSE4(float *a,int *b,int c)
{
	__m128 v1;
	__m128 v2;
	__m128 v3;
	*(__m128i*)&v1=_mm_cvtsi32_si128(((c+0x7F)&0xFF)<<23);
	v1=_mm_shuffle_ps(v1,v1,0);
	*(__m128i*)&v2 = _mm_lddqu_si128((const __m128i *)a);
	*(__m128i*)&v3 =_mm_cvtps_epi32(_mm_mul_ps(v2,v1));
	_mm_storeu_ps((float*)b,v3);
}

// ************** vector Dot SSE4 function *******************

#ifdef MSVC
float _APICALL _V2FDotSSE4(float *a,float *b)
{
	__m128 v1;
	__m128 v2;

	*(__m128d*)&v1 = _mm_load_sd((const double *)a);
	*(__m128d*)&v2 = _mm_load_sd((const double *)b);
	v1 = _mm_dp_ps(v1, v2, 0x31);
	return _mm_cvtss_f32(v1);
}
#else
_NORETURN float _APICALL _V2FDotSSE4(float *,float *)
{
	VECTORP2DDOTPRODUCTSSE4;
}
#endif

#ifdef MSVC
float _APICALL _V3FDotSSE4(float *a,float *b)
{
	__m128 v1 = _mm_load_ss(a+2);
	__m128 v2 = _mm_load_ss(b+2);
	v1 = _mm_loadh_pi(v1,(const __m64 *)a);
	v2 = _mm_loadh_pi(v2,(const __m64 *)b);
	v1 = _mm_dp_ps(v1, v2, 0xD1);
	return _mm_cvtss_f32(v1);
}
#else
_NORETURN float _APICALL _V3FDotSSE4(float *,float *)
{
	VECTORP3DDOTPRODUCTSSE4;
}
#endif

#ifdef MSVC
float _APICALL _V4FDotSSE4(float *a,float *b)
{
	__m128 v1;
	__m128 v2;

	*(__m128i*)&v1=_mm_lddqu_si128((const __m128i *)a);
	*(__m128i*)&v2=_mm_lddqu_si128((const __m128i *)b);
	v1 = _mm_dp_ps(v1, v2, 0xF1);
	return _mm_cvtss_f32(v1);
}
#else
_NORETURN float _APICALL _V4FDotSSE4(float *,float *)
{
	VECTORP4DDOTPRODUCTSSE4;
}
#endif

#ifdef MSVC
double _APICALL _V2DDotSSE4(double *a,double *b)
{
	__m128d v1;
	__m128d v2;

	*(__m128i*)&v1=_mm_lddqu_si128((const __m128i *)a);
	*(__m128i*)&v2=_mm_lddqu_si128((const __m128i *)b);
	return _mm_cvtsd_f64(_mm_dp_pd(v1, v2, 0x31));
}
#else
_NORETURN double _APICALL _V2DDotSSE4(double *,double *)
{
	VECTORP2DDDOTPRODUCTSSE4;
}
#endif

#ifdef MSVC
double _APICALL _V3DDotSSE4(double *a,double *b)
{
	__m128d v1;
	__m128d v3;

	__m128d v2 = _mm_load_sd(a+2);
	__m128d v4 = _mm_load_sd(b+2);
	*(__m128i*)&v1=_mm_lddqu_si128((const __m128i *)a);
	*(__m128i*)&v3=_mm_lddqu_si128((const __m128i *)b);
	return _mm_cvtsd_f64(_mm_add_sd(_mm_dp_pd(v1, v3, 0x31),_mm_mul_sd(v2,v4)));
}
#else
_NORETURN double _APICALL _V3DDotSSE4(double *,double *)
{
	VECTORP3DDDOTPRODUCTSSE4;
}
#endif

#ifdef MSVC
double _APICALL _V4DDotSSE4(double *a,double *b)
{
	__m128d v1;
	__m128d v2;
	__m128d v3;
	__m128d v4;
	__m128d v5;

	*(__m128i*)&v2=_mm_lddqu_si128((const __m128i *)a);
	*(__m128i*)&v3=_mm_lddqu_si128((const __m128i *)(a+2));
	*(__m128i*)&v4=_mm_lddqu_si128((const __m128i *)b);
	*(__m128i*)&v5=_mm_lddqu_si128((const __m128i *)(b+2));
	return _mm_cvtsd_f64(_mm_add_sd(_mm_dp_pd(v2, v4, 0x31),_mm_dp_pd(v3, v5, 0x31)));
}
#else
_NORETURN double _APICALL _V4DDotSSE4(double *,double *)
{
	VECTORP4DDDOTPRODUCTSSE4;
}
#endif

// ************** vector Length2 SSE4 function *******************

#ifdef MSVC
float _APICALL _V2FLength2SSE4(float *__formal)
{
	__m128 v1; // xmm0@1
	float ret;

	*(__m128d*)&v1 = _mm_load_sd((const double *)__formal);
	v1 = _mm_dp_ps(v1, v1, 0x31);
	return _mm_cvtss_f32(v1);
}
#else
_NORETURN float _APICALL _V2FLength2SSE4(float *)
{
	VECTORP2DLENGTH2SSE4;
}
#endif

#ifdef MSVC
float _APICALL _V3FLength2SSE4(float *__formal)
{
	__m128 v1; // xmm0@1
	float ret;

	v1 = _mm_load_ss(__formal+2);
	v1 = _mm_loadh_pi(v1,(const __m64 *)__formal);
	v1 = _mm_dp_ps(v1, v1, 0xD1);
	return _mm_cvtss_f32(v1);
}
#else
_NORETURN float _APICALL _V3FLength2SSE4(float *)
{
	VECTORP3DLENGTH2SSE4;
}
#endif

#ifdef MSVC
float _APICALL _V4FLength2SSE4(float *__formal)
{
	__m128 v1; // xmm0@1
	float ret;

	*(__m128d*)&v1 = _mm_load_sd((const double *)(__formal+2));
	v1 = _mm_loadh_pi(v1,(const __m64 *)__formal);
	v1 = _mm_dp_ps(v1, v1, 0xF1);
	return _mm_cvtss_f32(v1);
}
#else
_NORETURN float _APICALL _V4FLength2SSE4(float *)
{
	VECTORP4DLENGTH2SSE4;
}
#endif

#ifdef MSVC
double _APICALL _V2DLength2SSE4(double *a)
{
	__m128d v1; // xmm0@1
	double ret;

	*(__m128i*)&v1=_mm_lddqu_si128((const __m128i *)a);
	return _mm_cvtsd_f64(_mm_dp_pd(v1, v1, 0x31));
}
#else
_NORETURN double _APICALL _V2DLength2SSE4(double *)
{
	VECTORP2DDLENGTH2SSE4;
}
#endif

#ifdef MSVC
double _APICALL _V3DLength2SSE4(double *a)
{
	__m128d v1;
	__m128d v2;
	double ret;

	v2 = _mm_load_sd(a+2);
	*(__m128i*)&v1=_mm_lddqu_si128((const __m128i *)a);
	return _mm_cvtsd_f64(_mm_add_sd(_mm_dp_pd(v1, v1, 0x31),_mm_mul_sd(v2,v2)));
}
#else
_NORETURN double _APICALL _V3DLength2SSE4(double *)
{
	VECTORP3DDLENGTH2SSE4;
}
#endif

#ifdef MSVC
double _APICALL _V4DLength2SSE4(double *a)
{
	__m128d v1;
	__m128d v2;
	__m128d v3;
	double ret;

	*(__m128i*)&v2=_mm_lddqu_si128((const __m128i *)a);
	*(__m128i*)&v3=_mm_lddqu_si128((const __m128i *)(a+2));
	return _mm_cvtsd_f64(_mm_add_sd(_mm_dp_pd(v2, v2, 0x31),_mm_dp_pd(v3, v3, 0x31)));
}
#else
_NORETURN double _APICALL _V4DLength2SSE4(double *)
{
	VECTORP4DDLENGTH2SSE4;
}
#endif

// ************** vector Lerp SSE4 function *******************

#ifdef MSVC
void _APICALL _V2FLerpSSE4(float *a,float *b,float *c,float d)
{
	__m128 v1;
	__m128 v2;
	__m128 v3 = _mm_set_ss(d);
	*(__m128d*)&v1=_mm_load_sd((double *)a);
	*(__m128d*)&v2=_mm_load_sd((double *)b);
	v3 = _mm_shuffle_ps(v3,v3,0x50);
	v1 = _mm_add_ps(_mm_mul_ps(_mm_sub_ps(v2,v1), v3),v1);
	_mm_storel_pi((__m64 *)c, v1);
}
#else
void _APICALL _V2FLerpSSE4(float *,float *,float *,float )
{
	VECTORP2DLERPSSE4;
}
#endif

#ifdef MSVC
void _APICALL _V3FLerpSSE4(float *a,float *b,float *c,float d)
{
	__m128 v1;
	__m128 v2;
	__m128 v3 = _mm_set_ss(d);

	v1=_mm_load_ss(a+2);
	v2=_mm_load_ss(b+2);
	v1=_mm_loadh_pi(v1,(__m64*)a);
	v2=_mm_loadh_pi(v2,(__m64*)b);
	v3 = _mm_shuffle_ps(v3,v3,0x04);
	v1 = _mm_add_ps(_mm_mul_ps(_mm_sub_ps(v2,v1), v3),v1);
	_mm_storeh_pi((__m64*)c, v1);
	_mm_store_ss(c+2, v1);
}
#else
void _APICALL _V3FLerpSSE4(float *,float *,float *,float )
{
	VECTORP3DLERPSSE4;
}
#endif

#ifdef MSVC
void _APICALL _V4FLerpSSE4(float *a,float *b,float *c,float d)
{
	__m128 v1;
	__m128 v2;
	__m128 v3 = _mm_set_ss(d);

	*(__m128i*)&v1=_mm_lddqu_si128((const __m128i *)a);
	*(__m128i*)&v2=_mm_lddqu_si128((const __m128i *)b);
	v3 = _mm_shuffle_ps(v3,v3,0x00);
	_mm_storeu_ps(c, _mm_add_ps(_mm_mul_ps(_mm_sub_ps(v2,v1), v3),v1));
}
#else
void _APICALL _V4FLerpSSE4(float *,float *,float *,float )
{
	VECTORP4DLERPSSE4;
}
#endif

#ifdef MSVC
void _APICALL _V2DLerpSSE4(double *a,double *b,double *c,double d)
{
	__m128d v1;
	__m128d v2;

	*(__m128i*)&v1=_mm_lddqu_si128((const __m128i *)a);
	*(__m128i*)&v2=_mm_lddqu_si128((const __m128i *)b);
	__m128d v3 = _mm_movedup_pd(_mm_set_sd(d));
	_mm_storeu_pd(c, _mm_add_pd(_mm_mul_pd(_mm_sub_pd(v2,v1), v3),v1));
}
#else
void _APICALL _V2DLerpSSE4(double *,double *,double *,double )
{
	VECTORP2DDLERPSSE4;
}
#endif

#ifdef MSVC
void _APICALL _V3DLerpSSE4(double *a,double *b,double *c,double d)
{
	__m128d v1;
	__m128d v2;
	__m128d v4;
	__m128d v5;

	*(__m128i*)&v1=_mm_lddqu_si128((const __m128i *)a);
	*(__m128i*)&v2=_mm_lddqu_si128((const __m128i *)b);
	v4=_mm_load_sd(a+2);
	v5=_mm_load_sd(b+2);
	__m128d v3 = _mm_movedup_pd(_mm_set_sd(d));
	_mm_storeu_pd(c, _mm_add_pd(_mm_mul_pd(_mm_sub_pd(v2,v1), v3),v1));
	_mm_store_sd(c+2, _mm_add_sd(_mm_mul_sd(_mm_sub_sd(v5,v4), v3),v4));
}
#else
void _APICALL _V3DLerpSSE4(double *,double *,double *,double )
{
	VECTORP3DDLERPSSE4;
}
#endif

#ifdef MSVC
void _APICALL _V4DLerpSSE4(double *a,double *b,double *c,double d)
{
	__m128d v1;
	__m128d v2;
	__m128d v4;
	__m128d v5;

	*(__m128i*)&v1=_mm_lddqu_si128((const __m128i *)a);
	*(__m128i*)&v2=_mm_lddqu_si128((const __m128i *)b);
	*(__m128i*)&v4=_mm_lddqu_si128((const __m128i *)(a+2));
	*(__m128i*)&v5=_mm_lddqu_si128((const __m128i *)(b+2));
	__m128d v3 = _mm_movedup_pd(_mm_set_sd(d));
	_mm_storeu_pd(c, _mm_add_pd(_mm_mul_pd(_mm_sub_pd(v2,v1), v3),v1));
	_mm_storeu_pd(c+2, _mm_add_pd(_mm_mul_pd(_mm_sub_pd(v5,v4), v3),v4));
}
#else
void _APICALL _V4DLerpSSE4(double *,double *,double *,double )
{
	VECTORP4DDLERPSSE4;
}
#endif

// ************** vector Combine SSE4 function *******************

void _APICALL _V2FCombineSSE4(float *a,float *b,float *c,float d,float e)
{
	__m128 v2;
	__m128 v4;
	__m128d v5;

	*(__m128d*)&v2=_mm_load_sd((double *)a);
	*(__m128d*)&v4=_mm_load_sd((double *)b);
	__m128 v0 = _mm_set_ss(d);
	__m128 v1 = _mm_set_ss(e);
	v0 = _mm_shuffle_ps(v0,v0,0x50);
	v1 = _mm_shuffle_ps(v1,v1,0x50);
	*(__m128*)&v5 = _mm_add_ps(_mm_mul_ps(v2, v0),_mm_mul_ps(v4, v1));
	_mm_store_sd((double*)c, v5);
}

void _APICALL _V3FCombineSSE4(float *a,float *b,float *c,float d,float e)
{
	__m128 v2;
	__m128 v4;
	__m128 v5;

	v2=_mm_load_ss(a+2);
	v4=_mm_load_ss(b+2);
	v2=_mm_loadh_pi(v2,(__m64*)a);
	v4=_mm_loadh_pi(v4,(__m64*)b);
	__m128 v0 = _mm_set_ss(d);
	__m128 v1 = _mm_set_ss(e);
	v0 = _mm_shuffle_ps(v0,v0,0x04);
	v1 = _mm_shuffle_ps(v1,v1,0x04);
	v5 = _mm_add_ps(_mm_mul_ps(v2, v0),_mm_mul_ps(v4, v1));
	_mm_storeh_pi((__m64*)c, v5);
	_mm_store_ss(c+2, v5);
}

void _APICALL _V4FCombineSSE4(float *a,float *b,float *c,float d,float e)
{
	__m128 v2;
	__m128 v4;

	*(__m128i*)&v2=_mm_lddqu_si128((const __m128i *)a);
	*(__m128i*)&v4=_mm_lddqu_si128((const __m128i *)b);
	__m128 v0 = _mm_set_ps1(d);
	__m128 v1 = _mm_set_ps1(e);
	_mm_storeu_ps(c, _mm_add_ps(_mm_mul_ps(v2, v0),_mm_mul_ps(v4, v1)));
}

void _APICALL _V2DCombineSSE4(double *a,double *b,double *c,double d,double e)
{
	__m128d v2;
	__m128d v4;

	*(__m128i*)&v2=_mm_lddqu_si128((const __m128i *)a);
	*(__m128i*)&v4=_mm_lddqu_si128((const __m128i *)b);
	__m128d v0 = _mm_movedup_pd(_mm_set_sd(d));
	__m128d v1 = _mm_movedup_pd(_mm_set_sd(e));
	_mm_storeu_pd(c, _mm_add_pd(_mm_mul_pd(v2, v0),_mm_mul_pd(v4, v1)));
}

void _APICALL _V3DCombineSSE4(double *a,double *b,double *c,double d,double e)
{
	__m128d v2;
	__m128d v3;
	__m128d v4;
	__m128d v5;

	*(__m128i*)&v2=_mm_lddqu_si128((const __m128i *)a);
	*(__m128i*)&v4=_mm_lddqu_si128((const __m128i *)b);
	v3=_mm_load_sd(a+2);
	v5=_mm_load_sd(b+2);
	__m128d v0 = _mm_movedup_pd(_mm_set_sd(d));
	__m128d v1 = _mm_movedup_pd(_mm_set_sd(e));
	_mm_storeu_pd(c, _mm_add_pd(_mm_mul_pd(v2, v0),_mm_mul_pd(v4, v1)));
	_mm_store_sd(c+2, _mm_add_sd(_mm_mul_sd(v3, v0),_mm_mul_sd(v5, v1)));
}

void _APICALL _V4DCombineSSE4(double *a,double *b,double *c,double d,double e)
{
	__m128d v2;
	__m128d v3;
	__m128d v4;
	__m128d v5;

	*(__m128i*)&v2=_mm_lddqu_si128((const __m128i *)a);
	*(__m128i*)&v3=_mm_lddqu_si128((const __m128i *)(a+2));
	*(__m128i*)&v4=_mm_lddqu_si128((const __m128i *)b);
	*(__m128i*)&v5=_mm_lddqu_si128((const __m128i *)(b+2));
	__m128d v0 = _mm_movedup_pd(_mm_set_sd(d));
	__m128d v1 = _mm_movedup_pd(_mm_set_sd(e));
	_mm_storeu_pd(c, _mm_add_pd(_mm_mul_pd(v2, v0),_mm_mul_pd(v4, v1)));
	_mm_storeu_pd(c+2, _mm_add_pd(_mm_mul_pd(v3, v0),_mm_mul_pd(v5, v1)));
}

// ************** vector Transform SSE4 function *******************

void _APICALL _V4FTransformSSE4(float *a,void *b,float *c)
{
	__m128 v1;
	__m128 v2;
	__m128 v3;
	__m128 v4;
	*(__m128i*)&v1 = _mm_lddqu_si128((const __m128i *)b);
	*(__m128i*)&v2 = _mm_lddqu_si128(((const __m128i *)b)+1);
	*(__m128i*)&v3 = _mm_lddqu_si128(((const __m128i *)b)+2);
	*(__m128i*)&v4 = _mm_lddqu_si128(((const __m128i *)b)+3);
	__m128 v5 = _mm_load_ss(a);
	__m128 v6 = _mm_load_ss(a+1);
	v2=_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v5,v5,0),v1),_mm_mul_ps(_mm_shuffle_ps(v6,v6,0),v2));
	v5 = _mm_load_ss(a+2);
	v6 = _mm_load_ss(a+3);
	v4=_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v5,v5,0),v3),_mm_mul_ps(_mm_shuffle_ps(v6,v6,0),v4)),v2);
	_mm_storeu_ps(c, v4);
}

void _APICALL _V2DTransformSSE4(double *a,void *b,double *c)
{
	__m128d v1;
	__m128d v2;
	__m128d v4;
	*(__m128i*)&v1 = _mm_lddqu_si128((const __m128i *)b);
	*(__m128i*)&v2 = _mm_lddqu_si128(((const __m128i *)b)+2);
	*(__m128i*)&v4 = _mm_lddqu_si128(((const __m128i *)b)+6);
	__m128d v5 = _mm_loaddup_pd(a);
	__m128d v6 = _mm_loaddup_pd(a+1);
	v2=_mm_add_pd(_mm_add_pd(_mm_mul_pd(v5,v1),_mm_mul_pd(v6,v2)),v4);
	_mm_storeu_pd(c, v2);
}

void _APICALL _V3DTransformSSE4(double *a,void *b,double *c)
{
	__m128d v1;
	__m128d v3;
	__m128d v5;
	__m128d v7;
	*(__m128i*)&v1 = _mm_lddqu_si128((const __m128i *)b);
	__m128d v2 = _mm_load_sd((const double *)b+2);
	*(__m128i*)&v3 = _mm_lddqu_si128(((const __m128i *)b)+2);
	__m128d v4 = _mm_load_sd((const double *)b+6);
	*(__m128i*)&v5 = _mm_lddqu_si128(((const __m128i *)b)+4);
	__m128d v6 = _mm_load_sd((const double *)b+10);
	*(__m128i*)&v7 = _mm_lddqu_si128(((const __m128i *)b)+6);
	__m128d v8 = _mm_load_sd((const double *)b+14);
	__m128d v9 = _mm_loaddup_pd(a);
	__m128d v10 = _mm_loaddup_pd(a+1);
	__m128d v11 = _mm_loaddup_pd(a+2);
	__m128d v13=_mm_add_pd(_mm_add_pd(_mm_mul_pd(v9,v1),_mm_mul_pd(v10,v3)),_mm_add_pd(_mm_mul_pd(v11,v5),v7));
	__m128d v14=_mm_add_sd(_mm_add_sd(_mm_mul_sd(v9,v2),_mm_mul_sd(v10,v4)),_mm_add_sd(_mm_mul_sd(v11,v6),v8));
	_mm_storeu_pd(c, v13);
	_mm_store_sd(c+2, v14);
}

void _APICALL _V4DTransformSSE4(double *a,void *b,double *c)
{
	__m128d v1;
	__m128d v2;
	__m128d v3;
	__m128d v4;
	__m128d v5;
	__m128d v6;
	__m128d v7;
	__m128d v8;
	*(__m128i*)&v1 = _mm_lddqu_si128((const __m128i *)b);
	*(__m128i*)&v2 = _mm_lddqu_si128(((const __m128i *)b)+1);
	*(__m128i*)&v3 = _mm_lddqu_si128(((const __m128i *)b)+2);
	*(__m128i*)&v4 = _mm_lddqu_si128(((const __m128i *)b)+3);
	*(__m128i*)&v5 = _mm_lddqu_si128(((const __m128i *)b)+4);
	*(__m128i*)&v6 = _mm_lddqu_si128(((const __m128i *)b)+5);
	*(__m128i*)&v7 = _mm_lddqu_si128(((const __m128i *)b)+6);
	*(__m128i*)&v8 = _mm_lddqu_si128(((const __m128i *)b)+7);
	__m128d v9 = _mm_loaddup_pd(a);
	__m128d v10 = _mm_loaddup_pd(a+1);
	__m128d v11 = _mm_loaddup_pd(a+2);
	__m128d v12 = _mm_loaddup_pd(a+3);
	__m128d v13=_mm_add_pd(_mm_add_pd(_mm_mul_pd(v9,v1),_mm_mul_pd(v10,v3)),_mm_add_pd(_mm_mul_pd(v11,v5),_mm_mul_pd(v12,v7)));
	__m128d v14=_mm_add_pd(_mm_add_pd(_mm_mul_pd(v9,v2),_mm_mul_pd(v10,v4)),_mm_add_pd(_mm_mul_pd(v11,v6),_mm_mul_pd(v12,v8)));
	_mm_storeu_pd(c, v13);
	_mm_storeu_pd(c+2, v14);
}

// ************************* AVX ****************************

// ************** vector Add AVX function *******************

void _APICALL _V3DAddAVX(double *a,double *b,double *c)
{
	_mm256_storeu_pd(c,_mm256_add_pd(_mm256_set_pd(0,a[0],a[1],a[2]), _mm256_set_pd(0,b[0],b[1],b[2])));
}

#ifdef MSVC
void _APICALL _V4DAddAVX(double *a,double *b,double *c)
{
	_mm256_storeu_pd(c,_mm256_add_pd(_mm256_loadu_pd(a), _mm256_loadu_pd(b)));
}
#else
void _APICALL _V4DAddAVX(double *,double *,double *)
{
	VECTORP4DDADDAVX;
}
#endif

// ************** vector Sub AVX function *******************

void _APICALL _V4DSubAVX(double *a,double *b,double *c)
{
	_mm256_storeu_pd(c,_mm256_sub_pd(_mm256_loadu_pd(a), _mm256_loadu_pd(b)));
}

// ************** vector Scale AVX function *******************

void _APICALL _V4DScaleAVX(double *a,double *b,double c)
{
	_mm256_storeu_pd(b,_mm256_mul_pd(_mm256_loadu_pd(a), _mm256_set_pd(c,c,c,c)));
}

// ************** vector Mul AVX function *******************

void _APICALL _V4DMulAVX(double *a,double *b,double *c)
{
	_mm256_storeu_pd(c,_mm256_mul_pd(_mm256_loadu_pd(a), _mm256_loadu_pd(b)));
}

// ************** vector Div AVX function *******************

void _APICALL _V4DDivAVX(double *a,double *b,double *c)
{
	_mm256_storeu_pd(c,_mm256_div_pd(_mm256_loadu_pd(a), _mm256_loadu_pd(b)));
}

// ************** vector Lerp AVX function *******************

void _APICALL _V4DLerpAVX(double *a,double *b,double *c,double d)
{
	//_mm256_storeu_pd(c,_mm256_mul_pd(_mm256_loadu_pd(a), _mm256_loadu_pd(b)));
	/*__m128d v1 = _mm_loadu_pd((const double *)a);
	__m128d v2 = _mm_loadu_pd((const double *)b);
	__m128d v3 =  _mm_load_sd(&d);
	__m128d v4 = _mm_loadu_pd((const double *)(a+2));
	__m128d v5 = _mm_loadu_pd((const double *)(b+2));
	v3 = _mm_shuffle_pd(v3,v3,0x00);
	v1 = _mm_add_pd(_mm_mul_pd(_mm_sub_pd(v2,v1), v3),v1);
	v4 = _mm_add_pd(_mm_mul_pd(_mm_sub_pd(v5,v4), v3),v4);
	_mm_storeu_pd(c, v1);
	_mm_storeu_pd(c+2, v4);*/

	//_mm256_storeu_pd(c,_mm256_mul_pd(_mm256_loadu_pd(a), _mm256_loadu_pd(b)));
	__m256d v3 = _mm256_loadu_pd(a);
	__m256d v2 = _mm256_loadu_pd(b);
	__m256d v1 = _mm256_add_pd(_mm256_mul_pd(_mm256_sub_pd(v2,v3), v2),v3);
	_mm256_storeu_pd(c,v2);
}

// ************** vector Combine AVX function *******************

void _APICALL _V4DCombineAVX(double *a,double *b,double *c,double d,double e)
{
	__m256d v1 = _mm256_add_pd(_mm256_mul_pd(_mm256_loadu_pd(a), _mm256_broadcast_sd(&d)),_mm256_mul_pd(_mm256_loadu_pd(b), _mm256_broadcast_sd(&e)));
	_mm256_storeu_pd(c,v1);
}

// ************** vector Transform AVX function *******************

void _APICALL _V4DTransformAVX(double *,void *,double *)
{
	//__m256d v1 = _mm256_add_pd(_mm256_mul_pd(_mm256_loadu_pd(a), _mm256_broadcast_sd(&d)),_mm256_mul_pd(_mm256_loadu_pd(b), _mm256_broadcast_sd(&e)));
	//_mm256_storeu_pd(c,v1);
}

}

OPTIMIZE_OFF;
WARNING_ENABLE;

ARCH_DEFAULT;

#endif
#endif
