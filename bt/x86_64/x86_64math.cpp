/*
 * x86_64math.cpp
 *
 *  Created on: 18.10.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifdef CPU_BT
#include "x86_64math.h"
#include "../base/basemath.h"

#ifdef CPU_X86_64

#include "macrosasm.h"

#if defined(GCC) || defined(MINGW)
#include "x86_64intrin.h"
#include <x86intrin.h>
#include "../x86/macrosasm.h"
#endif

#if defined(MSVC)
#include <intrin.h>
#endif

#include "x86_64log2.h"
#include "x86_64sqrt.h"

WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

// ************** Sqrt FPU function *******************

// ************** Log2 FPU function *******************

	double _APICALL _DLog2FPU(double)
	{
		return 0;
		//__libm_sse2_exp();

/*	_BEGIN_ASM
	ASM( FLD1 ) \
	ASM( fld qword ptr [esp+4] ) \
	ASM( FYL2X ) \
	_END_ASM
	RET_2;*/
	}
	
// ************************* SSE ****************************

// ************** Sqrt SSE function *******************

#ifdef MSVC
	float _APICALL _FsqrtSSE(float _a)
	{
		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(_a)));
	}
#else
_NORETURN float _APICALL _FsqrtSSE(float)
{
	SQRTDSSE;
}
#endif

#ifdef MSVC
	float _APICALL _FFastInvSqrtSSE(float _a)
	{
		return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(_a)));
	}
#else
_NORETURN float _APICALL _FFastInvSqrtSSE(float)
{
	FASTINVERTSQRTDSSE;
}
#endif

// ************** SinCos SSE function *******************

	void _APICALL _FSinCosSSE(float a, float *__formala, float *a3)
	{
		float a1=-1;
		float a2=1;

		__m128 v5 = _mm_load_ss(&a1);
		__m128 v3 = _mm_load_ss(&a2);
		__m128 v21 = _mm_load_ss(&a);
		__m128 v6 = v21;
		v6 = _mm_mul_ss(v6,v6);
		__m128 v7 = _mm_shuffle_ps(v21, v6, 0);
		__m128 v4 = _mm_move_ss(v4,v6);
		v6 = _mm_mul_ss(v6,v6);
		__m128 v8 = _mm_shuffle_ps(_mm_shuffle_ps(v4, v6, 0), v7, 8);
		__m128 v9 = _mm_shuffle_ps(v8, v8, 66);
		__m128 v10 = _mm_shuffle_ps(v5, v3, 0);
		__m128 v11 = _mm_shuffle_ps(v6, v6, 0);
		__m128 v12 = _mm_movelh_ps(v3, v9);
		__m128 v13 = _mm_mul_ps(_mm_mul_ps(_mm_shuffle_ps(v7, v7, 32), v9), v10);
		v21 = _mm_load_ps(fastsindividef);
		__m128 v14 = _mm_mul_ps(v21, v13);
		__m128 v15 = _mm_mul_ps(v13, v11);
		//*(__m128i *)&v21 = _mm_lddqu_si128(((const __m128i *)fastsindividef) + 1);
		v21 = _mm_load_ps(fastsindividef + 4);
		__m128 v16 = _mm_add_ps(v14, _mm_mul_ps(v21, v15));
		__m128 v17 = _mm_mul_ps(v15, v11);
		v21 = _mm_load_ps(fastsindividef + 8);
		__m128 v18 = _mm_mul_ps(v21, v17);
		__m128 v19 = _mm_mul_ps(v17, v11);
		v6 = _mm_load_ps(fastsindividef + 12);
		__m128 v20 = _mm_add_ps(
				_mm_add_ps(v16, v18),
				_mm_mul_ps(v6, v19));
		v21 = _mm_add_ps(_mm_add_ps(v20, _mm_movehl_ps(v19, v20)), _mm_shuffle_ps(v12, v12, -120));
		_mm_store_ss(__formala,v21);
		v21 = _mm_shuffle_ps(v21, v21, 1);
		_mm_store_ss(a3,v21);
	}

// ************** ArcTg SSE function *******************

	float _APICALL _FArcTgSSE(float _x,float _y)
	{
		__m128 vABS = _mm_set_ps(0,0,_y,_x);
		__m128 vB;
		__m128 vZero = _mm_setzero_ps();
		__m128 vpABS = vABS;
		__m128 vBb = vZero;
		if (_mm_comieq_ss(vABS,vBb)!=0) vB=_mm_set_ss(1.0f);
		__m128 vABS1 = _mm_shuffle_ps(vABS,vABS,0x1);
		if (_mm_comieq_ss(vABS1,vBb)!=0) vB=vZero;
		__m128 vBs = vZero;
		__m128 mask=_mm_cmplt_ps(vABS,vZero);
		vABS = _mm_or_ps(_mm_andnot_ps(mask,vABS),_mm_and_ps(_mm_sub_ps(vZero,vABS),mask));
		vABS1 = _mm_shuffle_ps(vABS,vZero,0x1);
		if (_mm_comieq_ss(vABS,vABS1)!=0) {
			vB=_mm_load_ss(rotateArcTgf+4);
		} else {
			if (_mm_comile_ss(vABS1,vABS)==0) vBs=_mm_div_ss(vABS,vABS1);
			if (_mm_comilt_ss(vABS1,vABS)!=0) vBs=_mm_div_ss(vABS1,vABS);
			if (_mm_comilt_ss(vBs,vZero)!=0) vBs=_mm_sub_ss(vZero,vBs);
			if (_mm_comile_ss(vBs,_mm_load_ss(rotateArcTgf+5))==0) {
				__m128 v3 = _mm_shuffle_ps(vABS, vABS, 0x14);
				__m128 v1 = vZero;
				__m128 v2 = _mm_load_ps(rotateArcTgf);
				if (_mm_comile_ss(vABS1,vABS)==0) {
					v3 = _mm_mul_ps(v3, v2);
					v1 = _mm_movehl_ps(v1, v3);
					vABS = _mm_add_ps(v1, v3);
					vABS1 = _mm_shuffle_ps(vABS,vABS,0x1);
					vBb=_mm_div_ss(vABS,vABS1);
				}
				if (_mm_comilt_ss(vABS1,vABS)!=0) {
					v3 = _mm_mul_ps(v3, v2);
					v1 = _mm_movehl_ps(v1, v3);
					vABS = _mm_sub_ps(v3, v1);
					vABS1 = _mm_shuffle_ps(vABS,vABS,0x1);
					vBb=_mm_div_ss(vABS1,vABS);
				}
			} else vBb=vBs;

			__m128 v5 = vBb;
			__m128 v9 = v5;
			__m128 v21 = _mm_move_ss(v21,v5);
			v5 = _mm_shuffle_ps(v5, v5, 0x00);

			v21 = _mm_mul_ss(v21,v21);
			v21 = _mm_shuffle_ps(v21, v21, 0x50);
			__m128 v6 = v21;
			v6 = _mm_mul_ss(v6,v6);
			v6 = _mm_shuffle_ps(v6, v6, 0x51);
			__m128 v7 = v6;
			v6 = _mm_shuffle_ps(v6, v6, 0xA5);
			v6 = _mm_mul_ps(v6,v7);
			v7 = _mm_movelh_ps(v7,v6);
			__m128 v8 = _mm_set_ss(1.0f);
			v6 = _mm_set_ss(-1.0f);
			v6 = _mm_shuffle_ps(v6, v8, 0x00);
			v5 = _mm_mul_ps(_mm_mul_ps(v5, v7),_mm_shuffle_ps(v6, v6, 0x88));
			v7 = _mm_shuffle_ps(v7, v7, 0xFF);
			v6 = v5;

			__m128 v1 = _mm_load_ps(fasttgdividef);
			v6 = _mm_mul_ps(v6, v7);
			__m128 v2 = _mm_load_ps(fasttgdividef + 4);
			v1 = _mm_add_ps(_mm_mul_ps(v1, v5), _mm_mul_ps(v2, v6));
			__m128 v4 = vZero;
			v1 = _mm_add_ps(v1, _mm_movehl_ps(v4,v1));
			v2 = v1;
			v2 = _mm_shuffle_ps(v2, v2, 0x01);
			v1 = _mm_add_ss(v1, v9);
			vB = _mm_add_ss(v1, v2);

			if (_mm_comile_ss(vBs,_mm_load_ss(rotateArcTgf+5))==0) vB=_mm_add_ss(vB,_mm_load_ss(rotateArcTgf+6));
		}
		__m128 vpABS1 = _mm_shuffle_ps(vpABS,vpABS,0x1);
		if (_mm_comilt_ss(_mm_mul_ss(vpABS1,vpABS),vZero)!=0) vB=_mm_sub_ss(vZero,vB);
		__m128 vfs=vZero;
		if (_mm_comile_ss(vABS1,vABS)==0) {
			vB=_mm_sub_ss(vZero,vB);
			vfs=_mm_load_ss(rotateArcTgf+8);
		} else if (_mm_comilt_ss(vpABS,vZero)!=0) {
			vfs=_mm_load_ss(rotateArcTgf+7);
		}
		if (_mm_comilt_ss(vpABS1,vZero)!=0) { vB=_mm_sub_ss(vB,vfs); } else { vB=_mm_add_ss(vB,vfs); }
		return _mm_cvtss_f32(vB);
	}

// ************** Exp SSE function *******************

float _APICALL _FExpSSE(float _a)
{
	__m128 v1=_mm_set_ss(_a);
	__m128 v4=_mm_set_ss(1.0);
	__m128 v2=_mm_mul_ss(v1,v1);
	__m128 v3=_mm_mul_ss(v2,v2);
	v4=_mm_shuffle_ps(v4,v1,0);
	v2=_mm_shuffle_ps(v2,v3,0);
	v4=_mm_shuffle_ps(v4,v4,0x88);
	v3=_mm_shuffle_ps(v3,v3,0);
	v2=_mm_mul_ps(v2,v4);
	v1=_mm_add_ss(v1,v4);

	v4=_mm_mul_ps(v2,v3);
	v3=_mm_mul_ps(v3,v3);
	v1=_mm_add_ps(v1,_mm_mul_ps(v2,_mm_load_ps(fastsindividef)));
	v1=_mm_add_ps(v1,_mm_mul_ps(v4,_mm_load_ps(fastsindividef+4)));
	v2=_mm_mul_ps(v2,v3);
	v4=_mm_mul_ps(v4,v3);
	v1=_mm_add_ps(v1,_mm_mul_ps(v2,_mm_load_ps(fastsindividef+8)));
	v1=_mm_add_ps(v1,_mm_mul_ps(v4,_mm_load_ps(fastsindividef+12)));
	v4=_mm_movehl_ps(v4,v1);
	v1=_mm_add_ps(v1,v4);
	v4=_mm_shuffle_ps(v4,v1,1);
	v1=_mm_add_ss(v1,v4);
	return _mm_cvtss_f32(v1);
}

// ************************* SSE2 ****************************

// ************** Sqrt SSE2 function *******************

#ifdef MSVC
	double _APICALL _DsqrtSSE2(double _a)
	{
		double ret;
		__m128d v0=_mm_set_sd(_a);
		return _mm_cvtsd_f64(_mm_sqrt_sd(v0,v0));
	}
#else
_NORETURN double _APICALL _DsqrtSSE2(double)
{
	SQRTDDSSE2;
}
#endif

#ifdef MSVC
	double _APICALL _DFastInvSqrtSSE2(double _a)
	{
		__m128 v0=_mm_rsqrt_ss(_mm_set_ss(_a));
		__m128d v3=_mm_cvtss_sd(v3,v0);
		return _mm_cvtsd_f64(v3);
	}
#else
_NORETURN double _APICALL _DFastInvSqrtSSE2(double)
{
	FASTINVERTSQRTDDSSE2;
}
#endif

// ******************************* exp SSE2 *******************************

double _APICALL _DExpSSE2(double _a)
{
	__m128d v1=_mm_set_sd(_a);
	__m128d v4=_mm_set_sd(1.0);
	__m128d v2=_mm_mul_sd(v1,v1);
	v4=_mm_shuffle_pd(v4,v1,0);
	v2=_mm_shuffle_pd(v2,v2,0);
	__m128d v3=v2;
	v2=_mm_mul_pd(v2,v4);
	v1=_mm_add_sd(v1,v4);

	v4=_mm_mul_pd(v2,v3);
	v3=_mm_mul_pd(v3,v3);
	v1=_mm_add_pd(v1,_mm_mul_pd(v2,_mm_load_pd(fastsindivided)));
	v1=_mm_add_pd(v1,_mm_mul_pd(v4,_mm_load_pd(fastsindivided+2)));
	v2=_mm_mul_pd(v2,v3);
	v4=_mm_mul_pd(v4,v3);
	v1=_mm_add_pd(v1,_mm_mul_pd(v2,_mm_load_pd(fastsindivided)));
	v1=_mm_add_pd(v1,_mm_mul_pd(v4,_mm_load_pd(fastsindivided+2)));
	v2=_mm_mul_pd(v2,v3);
	v4=_mm_mul_pd(v4,v3);
	v1=_mm_add_pd(v1,_mm_mul_pd(v2,_mm_load_pd(fastsindivided)));
	v1=_mm_add_pd(v1,_mm_mul_pd(v4,_mm_load_pd(fastsindivided+2)));
	v2=_mm_mul_pd(v2,v3);
	v4=_mm_mul_pd(v4,v3);
	v1=_mm_add_pd(v1,_mm_mul_pd(v2,_mm_load_pd(fastsindivided)));
	v1=_mm_add_pd(v1,_mm_mul_pd(v4,_mm_load_pd(fastsindivided+2)));
	v4=_mm_shuffle_pd(v4,v1,01);
	v1=_mm_add_sd(v1,v4);
	return _mm_cvtsd_f64(v1);
}

// ************** log2 int SSE2 function *******************

#ifdef MSVC
	int _APICALL _ILog2SSE2(unsigned int _a)
	{
		int val=0;
		if (_a>0) {
			__m128i v1;
			*(__m128d*)&v1 = _mm_cvtsi32_sd(*(__m128d*)&v1,_a);
			v1 = _mm_slli_epi64(v1,1);
			v1 = _mm_srli_epi64(v1,53);
			val = _mm_cvtsi128_si32(v1);
			val-=0x3FF;
		}
		return val;
	}
#else
_NORETURN int _APICALL _ILog2SSE2(unsigned int)
{
	MATHLOG2ISS2;
}
#endif

// ************************* SSE3 ****************************

// ************** SinCos SSE3 function *******************

	void _APICALL _FSinCosSSE3(float a, float *__formala, float *a3)
	{
		float a1=-1;
		float a2=1;

		__m128 v5 = _mm_load_ss(&a1);
		__m128 v3 = _mm_load_ss(&a2);
		__m128 v21 = _mm_load_ss(&a);
		__m128 v6 = v21;
		v6 = _mm_mul_ss(v6,v6);
		__m128 v7 = _mm_shuffle_ps(v21, v6, 0);
		__m128 v4 = _mm_move_ss(v4,v6);
		v6 = _mm_mul_ss(v6,v6);
		__m128 v8 = _mm_shuffle_ps(_mm_shuffle_ps(v4, v6, 0), v7, 8);
		__m128 v9 = _mm_shuffle_ps(v8, v8, 66);
		__m128 v10 = _mm_shuffle_ps(v5, v3, 0);
		__m128 v11 = _mm_shuffle_ps(v6, v6, 0);
		__m128 v12 = _mm_movelh_ps(v3, v9);
		__m128 v13 = _mm_mul_ps(_mm_mul_ps(_mm_shuffle_ps(v7, v7, 32), v9), v10);
		v21 = _mm_load_ps(fastsindividef);
		__m128 v14 = _mm_mul_ps(v21, v13);
		__m128 v15 = _mm_mul_ps(v13, v11);
		//*(__m128i *)&v21 = _mm_lddqu_si128(((const __m128i *)fastsindividef) + 1);
		v21 = _mm_load_ps(fastsindividef + 4);
		__m128 v16 = _mm_add_ps(v14, _mm_mul_ps(v21, v15));
		__m128 v17 = _mm_mul_ps(v15, v11);
		v21 = _mm_load_ps(fastsindividef + 8);
		__m128 v18 = _mm_mul_ps(v21, v17);
		__m128 v19 = _mm_mul_ps(v17, v11);
		v6 = _mm_load_ps(fastsindividef + 12);
		__m128 v20 = _mm_add_ps(
				_mm_add_ps(v16, v18),
				_mm_mul_ps(v6, v19));
		v21 = _mm_add_ps(_mm_add_ps(v20, _mm_movehl_ps(v19, v20)), _mm_shuffle_ps(v12, v12, -120));
		_mm_store_ss(__formala,v21);
		v21 = _mm_shuffle_ps(v21, v21, 1);
		_mm_store_ss(a3,v21);
	}

// ************** ArcTg SSE3 function *******************

	//__attribute__ ((__target__("sse3")))

	float _APICALL _FArcTgSSE3(float _x,float _y)
	{
		__m128 vABS = _mm_set_ps(0,0,_y,_x);
		__m128 vB;
		__m128 vZero = _mm_setzero_ps();
		__m128 vpABS = vABS;
		__m128 vBb = vZero;
		if (_mm_comieq_ss(vABS,vBb)!=0) vB=_mm_set_ss(1.0f);
		__m128 vABS1 = _mm_shuffle_ps(vABS,vABS,0x1);
		if (_mm_comieq_ss(vABS1,vBb)!=0) vB=vZero;
		__m128 vBs = vZero;
		__m128 mask=_mm_cmplt_ps(vABS,vZero);
		vABS = _mm_or_ps(_mm_andnot_ps(mask,vABS),_mm_and_ps(_mm_sub_ps(vZero,vABS),mask));
		vABS1 = _mm_shuffle_ps(vABS,vZero,0x1);
		if (_mm_comieq_ss(vABS,vABS1)!=0) {
			vB=_mm_load_ss(rotateArcTgf+4);
		} else {
			if (_mm_comile_ss(vABS1,vABS)==0) vBs=_mm_div_ss(vABS,vABS1);
			if (_mm_comilt_ss(vABS1,vABS)!=0) vBs=_mm_div_ss(vABS1,vABS);
			if (_mm_comilt_ss(vBs,vZero)!=0) vBs=_mm_sub_ss(vZero,vBs);
			if (_mm_comile_ss(vBs,_mm_load_ss(rotateArcTgf+5))==0) {
				__m128 v3 = _mm_shuffle_ps(vABS, vABS, 0x14);
				__m128 v1 = vZero;
				__m128 v2 = _mm_load_ps(rotateArcTgf);
				if (_mm_comile_ss(vABS1,vABS)==0) {
					v3 = _mm_mul_ps(v3, v2);
					v1 = _mm_movehl_ps(v1, v3);
					vABS = _mm_add_ps(v1, v3);
					vABS1 = _mm_shuffle_ps(vABS,vABS,0x1);
					vBb=_mm_div_ss(vABS,vABS1);
				}
				if (_mm_comilt_ss(vABS1,vABS)!=0) {
					v3 = _mm_mul_ps(v3, v2);
					v1 = _mm_movehl_ps(v1, v3);
					vABS = _mm_sub_ps(v3, v1);
					vABS1 = _mm_shuffle_ps(vABS,vABS,0x1);
					vBb=_mm_div_ss(vABS1,vABS);
				}
			} else vBb=vBs;

			__m128 v5 = vBb;
			__m128 v9 = v5;
			__m128 v21 = _mm_move_ss(v21,v5);
			v5 = _mm_shuffle_ps(v5, v5, 0x00);

			v21 = _mm_mul_ss(v21,v21);
			v21 = _mm_shuffle_ps(v21, v21, 0x50);
			__m128 v6 = v21;
			v6 = _mm_mul_ss(v6,v6);
			v6 = _mm_shuffle_ps(v6, v6, 0x51);
			__m128 v7 = v6;
			v6 = _mm_shuffle_ps(v6, v6, 0xA5);
			v6 = _mm_mul_ps(v6,v7);
			v7 = _mm_movelh_ps(v7,v6);
			__m128 v8 = _mm_set_ss(1.0f);
			v6 = _mm_set_ss(-1.0f);
			v6 = _mm_shuffle_ps(v6, v8, 0x00);
			v5 = _mm_mul_ps(_mm_mul_ps(v5, v7),_mm_shuffle_ps(v6, v6, 0x88));
			v7 = _mm_shuffle_ps(v7, v7, 0xFF);
			v6 = v5;

			__m128 v1 = _mm_load_ps(fasttgdividef);
			v6 = _mm_mul_ps(v6, v7);
			__m128 v2 = _mm_load_ps(fasttgdividef + 4);
			v1 = _mm_add_ps(_mm_mul_ps(v1, v5), _mm_mul_ps(v2, v6));
			__m128 v4 = vZero;
			v1 = _mm_add_ps(v1, _mm_movehl_ps(v4,v1));
			v2 = v1;
			v2 = _mm_shuffle_ps(v2, v2, 0x01);
			v1 = _mm_add_ss(v1, v9);
			vB = _mm_add_ss(v1, v2);

			if (_mm_comile_ss(vBs,_mm_load_ss(rotateArcTgf+5))==0) vB=_mm_add_ss(vB,_mm_load_ss(rotateArcTgf+6));
		}
		__m128 vpABS1 = _mm_shuffle_ps(vpABS,vpABS,0x1);
		if (_mm_comilt_ss(_mm_mul_ss(vpABS1,vpABS),vZero)!=0) vB=_mm_sub_ss(vZero,vB);
		__m128 vfs=vZero;
		if (_mm_comile_ss(vABS1,vABS)==0) {
			vB=_mm_sub_ss(vZero,vB);
			vfs=_mm_load_ss(rotateArcTgf+8);
		} else if (_mm_comilt_ss(vpABS,vZero)!=0) {
			vfs=_mm_load_ss(rotateArcTgf+7);
		}
		if (_mm_comilt_ss(vpABS1,vZero)!=0) { vB=_mm_sub_ss(vB,vfs); } else { vB=_mm_add_ss(vB,vfs); }
		return _mm_cvtss_f32(vB);
	}

	double _APICALL _DArcTgSSE3(double _x,double _y)
	{
		double _b;
		if (_x==0) _b=1;
		if (_y==0) _b=0;
		double b;
		double bs;
		double absx=_x;
		if (absx<0) absx=-absx;
		double absy=_y;
		if (absy<0) absy=-absy;
		if (absy==absx) {
			_b=0.78539816339744830961566084581988;
		} else {
			if (absy>absx) bs=absx/absy;
			if (absy<absx) bs=absy/absx;
			if (bs<0) bs=-bs;
			if (bs>0.4142135623730950488016887242097) {
				if (absy>absx) {
					double bsx=absx*0.92387953251128675612818318939679-absy*0.3826834323650897717284599840304;
					absy=absy*0.92387953251128675612818318939679+absx*0.3826834323650897717284599840304;
					absx=bsx;
					b=absx/absy;
				}
				if (absy<absx) {
					double bsx=absx*0.92387953251128675612818318939679+absy*0.3826834323650897717284599840304;
					absy=absy*0.92387953251128675612818318939679-absx*0.3826834323650897717284599840304;
					absx=bsx;
					b=absy/absx;
				}
			} else b=bs;

			double a3[2]={1.0,-1.0};

			__m128d v1 = _mm_load_pd(bt::fasttgdivided);
			__m128d v2 = _mm_load_pd(bt::fasttgdivided + 2);
			__m128d v3 = _mm_load_pd(bt::fasttgdivided + 4);
			__m128d v4 = _mm_load_pd(bt::fasttgdivided + 6);
			__m128d v5 = _mm_load_pd(bt::fasttgdivided + 8);
			__m128d v6 = _mm_load_pd(bt::fasttgdivided + 10);
			__m128d v7 = _mm_load_pd(bt::fasttgdivided + 12);
			__m128d v8 = _mm_load_pd(bt::fasttgdivided + 14);

			__m128d v10 = _mm_loaddup_pd(&b);
			__m128d v21 = v10;
			v21 = _mm_mul_sd(v21,v21);
			v21 = _mm_shuffle_pd(v21, v21, 0x00);
			v10 = _mm_mul_pd(v10,_mm_load_pd(a3));
			v21 = _mm_mul_sd(v21,v21);
			v21 = _mm_shuffle_pd(v21, v21, 0x04);
			v10 = _mm_mul_pd(v10,v21);
			__m128d v11 = v10;
			v21 = _mm_shuffle_pd(v21, v21, 0x05);
			v11 = _mm_mul_pd(v11,v21);
			v1 = _mm_mul_pd(v1,v10);
			v21 = _mm_mul_pd(v21,v21);
			v2 = _mm_mul_pd(v2,v11);
			v10 = _mm_mul_pd(v10,v21);
			v1 = _mm_add_pd(v1,v2);
			v3 = _mm_mul_pd(v3,v10);
			v10 = _mm_mul_pd(v11,v21);
			v1 = _mm_add_pd(v1,v3);
			v4 = _mm_mul_pd(v4,v11);
			v10 = _mm_mul_pd(v10,v21);
			v1 = _mm_add_pd(v1,v4);
			v5 = _mm_mul_pd(v5,v10);
			v10 = _mm_mul_pd(v11,v21);
			v1 = _mm_add_pd(v1,v5);
			v6 = _mm_mul_pd(v6,v11);
			v10 = _mm_mul_pd(v10,v21);
			v1 = _mm_add_pd(v1,v6);
			v7 = _mm_mul_pd(v7,v10);
			v10 = _mm_mul_pd(v11,v21);
			v1 = _mm_add_pd(v1,v7);
			v8 = _mm_mul_pd(v8,v11);
			v1 = _mm_add_pd(v1,v8);
			v2 = v1;
			v1 = _mm_shuffle_pd(v1, v1, 0x01);
			v2 = _mm_add_sd(v2,v1);
			_b=_mm_cvtsd_f64(v2);

			/*double a=b*b;
			_b=b;
			for (int i=0;i<MAX_SINE_ITER;i++) {
				b=b*a;
				_b-=b*fasttgdivide[i<<1];            // arctg
				b=b*a;
				_b+=b*fasttgdivide[(i<<1)+1];            // arctg
			}*/
			if (bs>0.4142135623730950488016887242097) _b+=0.39269908169872415480783042290994;
		}
		if (_y*_x<0) _b=-_b;
		if (absy>absx) _b=-_b;
		double fs=0;
		if (absy>absx) {
			fs=3.1415926535897932384626433832795*0.5;
		} else if (_x<0) {
			fs=3.1415926535897932384626433832795;
		}
		if (_y<0) _b-=fs;
		if (_y>=0) _b+=fs;
		return _b;
	}

}

OPTIMIZE_OFF;
WARNING_ENABLE;

ARCH_DEFAULT;

#endif
#endif
