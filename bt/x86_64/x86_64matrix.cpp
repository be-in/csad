/*
 * x86_64matrix.cpp
 *
 *  Created on: 17.10.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifdef CPU_BT
#include "x86_64matrix.h"

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

void _APICALL _M4FTranslateSSE(void *a,float *b)
{
	unsigned int *sb=(unsigned int *)b;
	unsigned int *sd=(unsigned int *)a;
	__m128 v1 = _mm_xor_ps(v1,v1);
	_mm_storeu_ps((float*)a,v1);
	_mm_storeu_ps(((float*)a)+4,v1);
	_mm_storeu_ps(((float*)a)+8,v1);
	_mm_storeu_ps(((float*)a)+12,v1);
	unsigned int ed=0x3F800000;
	sd[0]=ed;
	sd[5]=ed;
	sd[10]=ed;
	sd[15]=ed;
	__m128 v2=_mm_loadl_pi(v2,(__m64*)b);
	_mm_storel_pi((__m64*)&sd[12],v2);
	sd[14]=sb[2];
}

void _APICALL _M4FScaleSSE(void *a,float *b)
{
	unsigned int *sb=(unsigned int *)b;
	unsigned int *sd=(unsigned int *)a;
	__m128 v1 = _mm_xor_ps(v1,v1);
	_mm_storeu_ps((float*)a,v1);
	_mm_storeu_ps(((float*)a)+4,v1);
	_mm_storeu_ps(((float*)a)+8,v1);
	_mm_storeu_ps(((float*)a)+12,v1);
	unsigned int ed=0x3F800000;
	sd[0]=sb[0];
	sd[5]=sb[1];
	sd[10]=sb[2];
	sd[15]=ed;
}

void _APICALL _M4FAddTranslateSSE(void *, float *, void *)
{

}

void _APICALL _M4FTRSSSE(void *,float *,float *,float *)
{
}

// ************************* SSE2 ****************************

void _APICALL _M4DTranslateSSE2(void *a,double *b)
{
	unsigned int *sb=(unsigned int *)b;
	unsigned int *sd=(unsigned int *)a;
	__m128d v1 = _mm_xor_pd(v1,v1);
	_mm_storeu_pd((double*)a,v1);
	_mm_storeu_pd(((double*)a)+2,v1);
	_mm_storeu_pd(((double*)a)+4,v1);
	_mm_storeu_pd(((double*)a)+6,v1);
	_mm_storeu_pd(((double*)a)+8,v1);
	_mm_storeu_pd(((double*)a)+10,v1);
	_mm_storeu_pd(((double*)a)+12,v1);
	_mm_storeu_pd(((double*)a)+14,v1);
	unsigned int ed=0x3FF00000;
	sd[1]=ed;
	sd[11]=ed;
	sd[21]=ed;
	sd[31]=ed;
	__m128d v2=_mm_load_sd(b+2);
	__m128d v3=_mm_loadu_pd(b);
	_mm_storeu_pd((double*)&sd[24],v3);
	_mm_store_sd((double*)&sd[28],v2);
}

void _APICALL _M4DScaleSSE2(void *a,double *b)
{
	unsigned int *sb=(unsigned int *)b;
	unsigned int *sd=(unsigned int *)a;
	__m128d v1 = _mm_xor_pd(v1,v1);
	_mm_storeu_pd((double*)a,v1);
	_mm_storeu_pd(((double*)a)+2,v1);
	_mm_storeu_pd(((double*)a)+4,v1);
	_mm_storeu_pd(((double*)a)+6,v1);
	_mm_storeu_pd(((double*)a)+8,v1);
	_mm_storeu_pd(((double*)a)+10,v1);
	_mm_storeu_pd(((double*)a)+12,v1);
	_mm_storeu_pd(((double*)a)+14,v1);
	unsigned int ed=0x3FF00000;
	__m128d v2=_mm_load_sd(b);
	_mm_store_sd((double*)&sd[0],v2);
	__m128d v3=_mm_load_sd(b+1);
	_mm_store_sd((double*)&sd[10],v3);
	__m128d v4=_mm_load_sd(b+2);
	_mm_store_sd((double*)&sd[20],v4);
	sd[31]=ed;
}

// ************************* SSE3 ****************************
ARCH_SSE3;

void _APICALL _M4FMulSSE3(void *_a, void *_b, void *_c)
{
  __m128 v3; // xmm4@1
  __m128 v4; // xmm5@1
  __m128 v5; // xmm6@1
  __m128 v6; // xmm7@1
  void *v7; // eax@1
  __m128 v8; // xmm2@1
  __m128 v9; // xmm2@1
  __m128 v10; // xmm2@1
  __m128 v11; // xmm2@1

  *(__m128i*)&v3 = _mm_lddqu_si128((const __m128i *)_a);
  *(__m128i*)&v4 = _mm_lddqu_si128((const __m128i *)_a + 1);
  *(__m128i*)&v5 = _mm_lddqu_si128((const __m128i *)_a + 2);
  *(__m128i*)&v6 = _mm_lddqu_si128((const __m128i *)_a + 3);
  v7 = _b;
  v8 = _mm_add_ps(
         _mm_add_ps(
           _mm_add_ps(
             _mm_mul_ps(_mm_shuffle_ps(_mm_load_ss((float *)_b), _mm_load_ss((float *)_b), 0), v3),
             _mm_mul_ps(_mm_shuffle_ps(_mm_load_ss((float *)_b + 1), _mm_load_ss((float *)_b + 1), 0), v4)),
           _mm_mul_ps(_mm_shuffle_ps(_mm_load_ss((float *)_b + 2), _mm_load_ss((float *)_b + 2), 0), v5)),
         _mm_mul_ps(_mm_shuffle_ps(_mm_load_ss((float *)_b + 3), _mm_load_ss((float *)_b + 3), 0), v6));
  _mm_storel_pi((__m64 *)_c, v8);
  _mm_storeh_pi((__m64 *)_c + 1, v8);
  v9 = _mm_add_ps(
         _mm_add_ps(
           _mm_add_ps(
             _mm_mul_ps(_mm_shuffle_ps(_mm_load_ss((float *)v7 + 4), _mm_load_ss((float *)v7 + 4), 0), v3),
             _mm_mul_ps(_mm_shuffle_ps(_mm_load_ss((float *)v7 + 5), _mm_load_ss((float *)v7 + 5), 0), v4)),
           _mm_mul_ps(_mm_shuffle_ps(_mm_load_ss((float *)v7 + 6), _mm_load_ss((float *)v7 + 6), 0), v5)),
         _mm_mul_ps(_mm_shuffle_ps(_mm_load_ss((float *)v7 + 7), _mm_load_ss((float *)v7 + 7), 0), v6));
  _mm_storel_pi((__m64 *)_c + 2, v9);
  _mm_storeh_pi((__m64 *)_c + 3, v9);
  v10 = _mm_add_ps(
          _mm_add_ps(
            _mm_add_ps(
              _mm_mul_ps(_mm_shuffle_ps(_mm_load_ss((float *)v7 + 8), _mm_load_ss((float *)v7 + 8), 0), v3),
              _mm_mul_ps(_mm_shuffle_ps(_mm_load_ss((float *)v7 + 9), _mm_load_ss((float *)v7 + 9), 0), v4)),
            _mm_mul_ps(_mm_shuffle_ps(_mm_load_ss((float *)v7 + 10), _mm_load_ss((float *)v7 + 10), 0), v5)),
          _mm_mul_ps(_mm_shuffle_ps(_mm_load_ss((float *)v7 + 11), _mm_load_ss((float *)v7 + 11), 0), v6));
  _mm_storel_pi((__m64 *)_c + 4, v10);
  _mm_storeh_pi((__m64 *)_c + 5, v10);
  v11 = _mm_add_ps(
          _mm_add_ps(
            _mm_add_ps(
              _mm_mul_ps(_mm_shuffle_ps(_mm_load_ss((float *)v7 + 12), _mm_load_ss((float *)v7 + 12), 0), v3),
              _mm_mul_ps(_mm_shuffle_ps(_mm_load_ss((float *)v7 + 13), _mm_load_ss((float *)v7 + 13), 0), v4)),
            _mm_mul_ps(_mm_shuffle_ps(_mm_load_ss((float *)v7 + 14), _mm_load_ss((float *)v7 + 14), 0), v5)),
          _mm_mul_ps(_mm_shuffle_ps(_mm_load_ss((float *)v7 + 15), _mm_load_ss((float *)v7 + 15), 0), v6));
  _mm_storel_pi((__m64 *)_c + 6, v11);
  _mm_storeh_pi((__m64 *)_c + 7, v11);
}

// ************************* SSE4 ****************************
ARCH_SSE4;

void _APICALL _M4DMulSSE4(void *_a, void *_b, void *_c)
{
  __m128d v3; // xmm4@1
  __m128d v4; // xmm5@1
  __m128d v5; // xmm6@1
  __m128d v6; // xmm7@1
  __m128d v7; // xmm4@1
  __m128d v8; // xmm5@1
  __m128d v9; // xmm6@1
  __m128d v10; // xmm7@1

  *(__m128i*)&v3 = _mm_lddqu_si128((const __m128i *)_a);
  *(__m128i*)&v4 = _mm_lddqu_si128((const __m128i *)_a + 2);
  *(__m128i*)&v5 = _mm_lddqu_si128((const __m128i *)_a + 4);
  *(__m128i*)&v6 = _mm_lddqu_si128((const __m128i *)_a + 6);
  *(__m128d *)_c = _mm_add_pd(
                    _mm_add_pd(
                      _mm_add_pd(
                        _mm_mul_pd(_mm_loaddup_pd((const double *)_b), v3),
                        _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 1), v4)),
                      _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 2), v5)),
                    _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 3), v6));
  *((__m128d *)_c + 2) = _mm_add_pd(
                          _mm_add_pd(
                            _mm_add_pd(
                              _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 4), v3),
                              _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 5), v4)),
                            _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 6), v5)),
                          _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 7), v6));
  *((__m128d *)_c + 4) = _mm_add_pd(
                          _mm_add_pd(
                            _mm_add_pd(
                              _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 8), v3),
                              _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 9), v4)),
                            _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 10), v5)),
                          _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 11), v6));
  *((__m128d *)_c + 6) = _mm_add_pd(
                          _mm_add_pd(
                            _mm_add_pd(
                              _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 12), v3),
                              _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 13), v4)),
                            _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 14), v5)),
                          _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 15), v6));
  *(__m128i*)&v7 = _mm_lddqu_si128((const __m128i *)_a + 1);
  *(__m128i*)&v8 = _mm_lddqu_si128((const __m128i *)_a + 3);
  *(__m128i*)&v9 = _mm_lddqu_si128((const __m128i *)_a + 5);
  *(__m128i*)&v10 = _mm_lddqu_si128((const __m128i *)_a + 7);
  *((__m128d *)_c + 1) = _mm_add_pd(
                          _mm_add_pd(
                            _mm_add_pd(
                              _mm_mul_pd(_mm_loaddup_pd((const double *)_b), v7),
                              _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 1), v8)),
                            _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 2), v9)),
                          _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 3), v10));
  *((__m128d *)_c + 3) = _mm_add_pd(
                          _mm_add_pd(
                            _mm_add_pd(
                              _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 4), v7),
                              _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 5), v8)),
                            _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 6), v9)),
                          _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 7), v10));
  *((__m128d *)_c + 5) = _mm_add_pd(
                          _mm_add_pd(
                            _mm_add_pd(
                              _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 8), v7),
                              _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 9), v8)),
                            _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 10), v9)),
                          _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 11), v10));
  *((__m128d *)_c + 7) = _mm_add_pd(
                          _mm_add_pd(
                            _mm_add_pd(
                              _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 12), v7),
                              _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 13), v8)),
                            _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 14), v9)),
                          _mm_mul_pd(_mm_loaddup_pd((const double *)_b + 15), v10));
}

void _APICALL _M4FAddTranslateSSE4(void *__formal, float *__formala, void *a3)
{
  __m128 v3; // xmm4@1
  __m128 v4; // xmm5@1
  __m128 v5; // xmm6@1
  __m128 v6; // xmm7@1
  __m128 v7; // xmm0@1

  *(__m128i*)&v3 = _mm_lddqu_si128((const __m128i *)__formal);
  *(__m128i*)&v4 = _mm_lddqu_si128((const __m128i *)__formal + 1);
  *(__m128i*)&v5 = _mm_lddqu_si128((const __m128i *)__formal + 2);
  *(__m128i*)&v6 = _mm_lddqu_si128((const __m128i *)__formal + 3);
  v7 = _mm_movelh_ps(_mm_loadl_pi(v7,(const __m64 *)__formala), _mm_load_ss((float *)__formala + 2));
  __m128 v1 =_mm_add_ps(v3, _mm_mul_ps(_mm_shuffle_ps(v3, v3, 255), v7));
  _mm_storeu_ps((float*)a3,v1);
  __m128 v2 = _mm_add_ps(v4, _mm_mul_ps(_mm_shuffle_ps(v4, v4, 255), v7));
  _mm_storeu_ps(((float*)a3)+4,v2);
  __m128 v8 = _mm_add_ps(v5, _mm_mul_ps(_mm_shuffle_ps(v5, v5, 255), v7));
  _mm_storeu_ps(((float*)a3)+8,v8);
  __m128 v9 = _mm_add_ps(v6, _mm_mul_ps(_mm_shuffle_ps(v6, v6, 255), v7));
  _mm_storeu_ps(((float*)a3)+12,v9);
}

void _APICALL _M4FAddScaleSSE4(void *__formal, float *__formala, void *a3)
{
  __m128 v3; // xmm7@1
  __m128 v4; // xmm5@1
  __m128 v5; // xmm6@1
  __m128 v7;
  __m128 v8;
  __m128 v9;

  *(__m128i*)&v3 = _mm_lddqu_si128((const __m128i *)__formal + 3);
  *(__m128i*)&v7=_mm_lddqu_si128((const __m128i *)__formal + 1);
  v4 = _mm_mul_ps(
         v7,
         _mm_shuffle_ps(_mm_load_ss((float *)__formala + 1), _mm_load_ss((float *)__formala + 1), 0));
  *(__m128i*)&v8=_mm_lddqu_si128((const __m128i *)__formal + 2);
  v5 = _mm_mul_ps(
         v8,
         _mm_shuffle_ps(_mm_load_ss((float *)__formala + 2), _mm_load_ss((float *)__formala + 2), 0));
  *(__m128i*)&v9=_mm_lddqu_si128((const __m128i *)__formal);
  _mm_storeu_ps(((float*)a3),_mm_mul_ps(
                    v9,
                    _mm_shuffle_ps(_mm_load_ss((float *)__formala), _mm_load_ss((float *)__formala), 0)));
  _mm_storeu_ps(((float*)a3)+4,v4);
  _mm_storeu_ps(((float*)a3)+8,v5);
  _mm_storeu_ps(((float*)a3)+12,v3);
}

}

OPTIMIZE_OFF;
WARNING_ENABLE;

ARCH_DEFAULT;

#endif
#endif
