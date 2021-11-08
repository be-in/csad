/*
 * x86_64quaternion.cpp
 *
 *  Created on: 18.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifdef CPU_BT
#include "x86_64quaternion.h"

#ifdef CPU_X86_64

#include "macrosasm.h"
ARCH_ALL;

#if defined(GCC) || defined(MINGW)
#include <x86intrin.h>
#endif

#if defined(MSVC)
#include <intrin.h>
#endif

WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

// ************************* SSE ****************************
ARCH_SSE;

// ************************* SSE3 ***************************
ARCH_SSE3;

void _APICALL _QFMulSSE3(float * a,float * b,float * c)
{
	__m128 v0;
	__m128 v7;
	*(__m128i*)&v0=_mm_lddqu_si128((const __m128i *)b);
	*(__m128i*)&v7=_mm_lddqu_si128((const __m128i *)a);
	__m128 v1=_mm_xor_ps(v1,v1);
	__m128 v2=_mm_movehl_ps(v2,v0);
	__m128 v6=_mm_moveldup_ps(v7);
	v1 = _mm_sub_ps(v1,v0);
	v7=_mm_movehdup_ps(v7);
	v0 = _mm_shuffle_ps(v0,v1,0x44);
	v2=_mm_movelh_ps(v2,v2);
	__m128 v3=v0;
	v1 = _mm_shuffle_ps(v1,v2,0x5A);
	v3 = _mm_shuffle_ps(v3,v3,0x93);
	v1 = _mm_shuffle_ps(v1,v1,0x22);
	v2 = _mm_mul_ps(v2,v7);
	v1 = _mm_mul_ps(v1,v6);
	v7 = _mm_shuffle_ps(v7,v7,0x4E);
	v6 = _mm_shuffle_ps(v6,v6,0x4E);
	v1 = _mm_add_ps(_mm_add_ps(v2,_mm_mul_ps(v0,v7)),_mm_add_ps(v1,_mm_mul_ps(v3,v6)));
	_mm_storel_pi((__m64 *)c, v1);
	_mm_storeh_pi((__m64 *)(c + 2),v1);
}

void _APICALL _QDMulSSE3(double * a,double * b,double * c)
{
	__m128d v0;
	__m128d v1;
	__m128d v4;
	__m128d v5;
	__m128d v6=_mm_loaddup_pd(a);
	__m128d v2=_mm_xor_pd(v2,v2);
	__m128d v7=_mm_loaddup_pd(a+1);
	*(__m128i*)&v0=_mm_lddqu_si128((const __m128i *)b);
	*(__m128i*)&v1=_mm_lddqu_si128((const __m128i *)(b+2));
	__m128d v3=_mm_xor_pd(v3,v3);
	v2 = _mm_sub_pd(v2,v0);
	v3 = _mm_sub_pd(v3,v1);
	*(__m128*)&v3 = _mm_movelh_ps(*(__m128*)&v3,*(__m128*)&v3);
	*(__m128*)&v4 = _mm_movehl_ps(*(__m128*)&v4,*(__m128*)&v0);
	*(__m128*)&v3 = _mm_movehl_ps(*(__m128*)&v3,*(__m128*)&v1);
	*(__m128*)&v5 = _mm_movelh_ps(*(__m128*)&v5,*(__m128*)&v0);
	*(__m128*)&v4 = _mm_movelh_ps(*(__m128*)&v4,*(__m128*)&v2);
	*(__m128*)&v5 = _mm_movehl_ps(*(__m128*)&v5,*(__m128*)&v2);
	v4 = _mm_mul_pd(v4,v6);
	v2 = _mm_mul_pd(v2,v7);
	v6 = _mm_mul_pd(v6,v3);
	v7 = _mm_mul_pd(v7,v1);
	v2 = _mm_add_pd(v2,v4);
	v6 = _mm_add_pd(v6,v7);
	v4 = _mm_loaddup_pd(a+2);
	v7 = _mm_loaddup_pd(a+3);
	v5 = _mm_mul_pd(v5,v4);
	v0 = _mm_mul_pd(v0,v7);
	v4 = _mm_mul_pd(v4,v3);
	v7 = _mm_mul_pd(v7,v1);
	v0 = _mm_add_pd(v0,v5);
	v7 = _mm_add_pd(v7,v4);
	v6 = _mm_add_pd(v6,v0);
	v2 = _mm_add_pd(v2,v7);
	_mm_store_sd(c, v6);
	_mm_store_sd(c+2, v2);
	_mm_storeh_pi((__m64 *)(c + 1),*(__m128*)&v6);
	_mm_storeh_pi((__m64 *)(c + 3),*(__m128*)&v2);
}

}

OPTIMIZE_OFF;
WARNING_ENABLE;

ARCH_DEFAULT;

#endif
#endif