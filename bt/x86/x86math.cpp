/*
 * @file x86math.cpp
 *
 *  Created on: 18.10.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifdef CPU_BT

#include "x86math.h"
#include "macrosasm.h"
#include "../base/basemath.h"
#include "x86math_sincos.h"

#ifdef CPU_X86_32

#if defined(GCC) || defined(MINGW)
#include <x86intrin.h>
#endif

#if defined(MSVC)
#include <intrin.h>
#endif

WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

int _NAKED _APICALL _ILog2CPU(unsigned int)
{
_BEGIN_ASM
_LINE2( 0x33,0xC0 )                         /* xor         eax,eax  */ \
_LINE5( 0x83,0x7C,0x24,0x04,0x00 )          /* cmp         dword ptr [esp+4],0  */ \
_LINE2( 0x7F,0x03 )                         /* jg          eee (1722ADh)  */ \
_LINE3( 0xC2,0x04,0x00 )                    /* ret         4  */ \
_LINE5( 0x0F,0xBD,0x44,0x24,0x04 )          /* bsr         eax,dword ptr [esp+4]  */ \
_END_ASM
RET_1;
}

float _NAKED _APICALL _FsqrtFPU(float)
{
_BEGIN_ASM
_LINE4(0xD9,0x44,0x24,0x04) //esp
_LINE2(0xD9,0xFA)
_END_ASM
RET_1;
}

double _NAKED _APICALL _DsqrtFPU(double)
{
_BEGIN_ASM
_LINE4(0xDD,0x44,0x24,0x04) //esp
_LINE2(0xD9,0xFA)
_END_ASM
RET_2;
}

float _NAKED _APICALL _FFastInvSqrtFPU(float )
{
_BEGIN_ASM
_LINE4( 0x8B,0x54,0x24,0x04 )                      /* mov         edx,dword ptr [esp+4]  */ \
_LINE2( 0xD1,0xEA )                                /* shr         edx,1  */ \
_LINE5( 0xB8,0xF3,0x04,0x35,0x5F )                 /* mov         eax,0x5F3504F3h  */ \
_LINE2( 0x2B,0xC2 )                                /* sub         eax,edx  */ \
_LINE4( 0xD9,0x44,0x24,0x04 )                      /* fld         dword ptr [esp+4]  */ \
_LINE4( 0x89,0x44,0x24,0x04 )                      /* mov         dword ptr [esp+4],eax  */ \
_LINE4( 0xD9,0x44,0x24,0x04 )                      /* fld         dword ptr [esp+4]  */ \
_LINE8( 0xC7,0x44,0x24,0x04,0x00,0x00,0x00,0x3F )  /* mov         dword ptr [esp+4],0x3F000000h  */ \
_LINE4( 0xD9,0x44,0x24,0x04 )                      /* fld         dword ptr [esp+4]  */ \
_LINE2( 0xD9,0xC1 )                                /* fld         st(1)  */ \
_LINE2( 0xDC,0xC8 )                                /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xCB )                                /* fmulp       st(3),st  */ \
_LINE2( 0xDC,0xCA )                                /* fmul        st(2),st  */ \
_LINE2( 0xD9,0xE8 )                                /* fld1  */ \
_LINE2( 0xDE,0xC1 )                                /* faddp       st(1),st  */ \
_LINE2( 0xDE,0xE2 )                                /* fsubrp      st(2),st  */ \
_LINE2( 0xDE,0xC9 )                                /* fmulp       st(1),st  */ \
_END_ASM
RET_1;
}

void _NAKED _APICALL _FSinCosFPU(float, float*, float*)
{
_BEGIN_ASM
 _STR(_DB(0xD9) _DB(0x44) _DB(0x24) _DB(0x04)) /* fld         dword ptr [esp+4]  */ \
 _STR(_DB(0xD9) _DB(0xFB))                     /* fsincos  */ \
 _STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x08)) /* mov         eax,dword ptr [esp+8]  */ \
 _STR(_DB(0xD9) _DB(0x18))                     /* fstp        dword ptr [eax]  */ \
 _STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x0C)) /* mov         eax,dword ptr [esp+0Ch]  */ \
 _STR(_DB(0xD9) _DB(0x18))                     /* fstp        dword ptr [eax]  */ \
_END_ASM
RET_3;
}

void _NAKED _APICALL _DSinCosFPU(double,double*,double*)
{
_BEGIN_ASM
 _STR(_DB(0xDD) _DB(0x44) _DB(0x24) _DB(0x04)) //esp
 _STR(_DB(0xD9) _DB(0xFB))
 _STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x0C)) //esp
 _STR(_DB(0xDD) _DB(0x18))
 _STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x10)) //esp
 _STR(_DB(0xDD) _DB(0x18))
_END_ASM
RET_4
}

float _NAKED _APICALL _FArcTgFPU(float,float)
{
_BEGIN_ASM
_LINE4(0xD9,0x44,0x24,0x08)
_LINE4(0xD9,0x44,0x24,0x04)
_LINE2(0xD9,0xF3)                      /* farctg */ 
_END_ASM
RET_2;
}

double _NAKED _APICALL _DArcTgFPU(double,double)
{
_BEGIN_ASM
_LINE4(0xDD,0x44,0x24,0x0C) //esp
_LINE4(0xDD,0x44,0x24,0x04) //esp
_LINE2(0xD9,0xF3)
_END_ASM
RET_4;
}

float _NAKED _APICALL _Fmul2NFPU(float,int)
{
_BEGIN_ASM
_LINE4( 0xDB,0x44,0x24,0x08 )            /* fild        dword ptr [esp+0Ch] */ \
_LINE4( 0xD9,0x44,0x24,0x04 )            /* fld         dword ptr [esp+4] */ \
_LINE2( 0xD9,0xFD )                      /* fscale */ \
_LINE2( 0xDD,0xD9 )                      /* fstp        st(1) */ \
_END_ASM
RET_2;
}

double _NAKED _APICALL _Dmul2NFPU(double,int)
{
_BEGIN_ASM \
_LINE4( 0xDB,0x44,0x24,0x0C )            /* fild        dword ptr [esp+0Ch] */ \
_LINE4( 0xDD,0x44,0x24,0x04 )            /* fld         qword ptr [esp+4] */ \
_LINE2( 0xD9,0xFD )                      /* fscale */ \
_LINE2( 0xDD,0xD9 )                      /* fstp        st(1) */ \
_END_ASM
RET_3;
}

int _NAKED _APICALL _FTruncFPU(float)
{
_BEGIN_ASM
_LINE4( 0xD9,0x44,0x24,0x04 )        /* fld         dword ptr [esp+4]  */ \
_LINE4( 0xD9,0x7C,0x24,0x04 )        /* fnstcw      word ptr [esp+4]  */ \
_LINE5( 0x66,0x8B,0x44,0x24,0x04 )   /* mov         ax,word ptr [esp+4]  */ \
_LINE3( 0x66,0x8B,0xD0 )             /* mov         dx,ax  */ \
_LINE4( 0x66,0x25,0xFF,0xF3 )        /* and         ax,0F3FFh  */ \
_LINE4( 0x66,0x0D,0x00,0x0C )        /* or          ax,C00h  */ \
_LINE5( 0x66,0x89,0x44,0x24,0x04 )   /* mov         word ptr [esp+4],ax  */ \
_LINE4( 0xD9,0x6C,0x24,0x04 )        /* fldcw       word ptr [esp+4]  */ \
_LINE5( 0x66,0x89,0x54,0x24,0x04 )   /* mov         word ptr [esp+4],dx  */ \
_LINE4( 0xDB,0x5C,0x24,0xFC )        /* fistp       dword ptr [esp-4]  */ \
_LINE4( 0xD9,0x6C,0x24,0x04 )        /* fldcw       word ptr [esp+4]  */ \
_LINE4( 0x8B,0x44,0x24,0xFC )        /* mov         eax,dword ptr [esp-4]  */ \
_END_ASM
RET_1;
}

int _NAKED _APICALL _DTruncFPU(double)
{
_BEGIN_ASM
_LINE4( 0xDD,0x44,0x24,0x04 )        /* fld         qword ptr [esp+4]  */ \
_LINE4( 0xD9,0x7C,0x24,0x04 )        /* fnstcw      word ptr [esp+4]  */ \
_LINE5( 0x66,0x8B,0x44,0x24,0x04 )   /* mov         ax,word ptr [esp+4]  */ \
_LINE3( 0x66,0x8B,0xD0 )             /* mov         dx,ax  */ \
_LINE4( 0x66,0x25,0xFF,0xF3 )        /* and         ax,0F3FFh  */ \
_LINE4( 0x66,0x0D,0x00,0x0C )        /* or          ax,C00h  */ \
_LINE5( 0x66,0x89,0x44,0x24,0x04 )   /* mov         word ptr [esp+4],ax  */ \
_LINE4( 0xD9,0x6C,0x24,0x04 )        /* fldcw       word ptr [esp+4]  */ \
_LINE5( 0x66,0x89,0x54,0x24,0x04 )   /* mov         word ptr [esp+4],dx  */ \
_LINE4( 0xDB,0x5C,0x24,0xFC )        /* fistp       dword ptr [esp-4]  */ \
_LINE4( 0xD9,0x6C,0x24,0x04 )        /* fldcw       word ptr [esp+4]  */ \
_LINE4( 0x8B,0x44,0x24,0xFC )        /* mov         eax,dword ptr [esp-4]  */ \
_END_ASM
RET_2;
}

int _NAKED _APICALL _FRoundFPU(float)
{
_BEGIN_ASM
_LINE4( 0xD9,0x44,0x24,0x04 )        /* fld         dword ptr [esp+4]  */ \
_LINE4( 0xDB,0x5C,0x24,0xFC )        /* fistp       dword ptr [esp-4]  */ \
_LINE4( 0x8B,0x44,0x24,0xFC )        /* mov         eax,dword ptr [esp-4]  */ \
_END_ASM
RET_1;
}

int _NAKED _APICALL _DRoundFPU(double)
{
_BEGIN_ASM
_LINE4( 0xDD,0x44,0x24,0x04 )        /* fld         qword ptr [esp+4]  */ \
_LINE4( 0xDB,0x5C,0x24,0xFC )        /* fistp       dword ptr [esp-4]  */ \
_LINE4( 0x8B,0x44,0x24,0xFC )        /* mov         eax,dword ptr [esp-4]  */ \
_END_ASM
RET_2;
}

int _NAKED _APICALL _Fmul2NTruncFPU(float,int)
{
_BEGIN_ASM
ASM( mov dword ptr [esp-8],0x3f000000 ) \
_LINE4( 0xDB,0x44,0x24,0x08 )                               /* fild        dword ptr [esp+8]  */ \
_LINE4( 0xD9,0x44,0x24,0x04 )                               /* fld         dword ptr [esp+4]  */ \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
ASM( fsub dword ptr [esp-8] ) \
_LINE4( 0xDB,0x5C,0x24,0x08 )                               /* fistp       dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8]  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM
RET_2;
}

int _NAKED _APICALL _Dmul2NTruncFPU(double,int)
{
_BEGIN_ASM
ASM( mov dword ptr [esp-8],0x3f000000 ) \
_LINE4( 0xDB,0x44,0x24,0x0C )                               /* fild        dword ptr [esp+12]  */ \
_LINE4( 0xDD,0x44,0x24,0x04 )                               /* fld         qword ptr [esp+4]  */ \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
ASM( fsub dword ptr [esp-8] ) \
_LINE4( 0xDB,0x5C,0x24,0x0C )                               /* fistp       dword ptr [esp+12]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+12]  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM
RET_3;
}

int _NAKED _APICALL _Fmul2NRoundFPU(float,int)
{
_BEGIN_ASM
_LINE4( 0xDB,0x44,0x24,0x08 )                               /* fild        dword ptr [esp+8]  */ \
_LINE4( 0xD9,0x44,0x24,0x04 )                               /* fld         dword ptr [esp+4]  */ \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
_LINE4( 0xDB,0x5C,0x24,0x08 )                               /* fistp       dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8]  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM
RET_2;
}

int _NAKED _APICALL _Dmul2NRoundFPU(double,int)
{
_BEGIN_ASM
_LINE4( 0xDB,0x44,0x24,0x0C )                               /* fild        dword ptr [esp+12]  */ \
_LINE4( 0xDD,0x44,0x24,0x04 )                               /* fld         qword ptr [esp+4]  */ \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
_LINE4( 0xDB,0x5C,0x24,0x0C )                               /* fistp       dword ptr [esp+12]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+12]  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM
RET_3;
}

void _NOINLINE _APICALL setRoundMode(int)
{
PUSH_EAX;
_BEGIN_ASM
_LINE3(0xD9,0x3C,0x24)
_LINE6(0x66,0x81,0x24,0x24,0xFF,0xF3)
_LINE4(0x8B,0x44,0x24,0x08)
_LINE2(0x24,0x03)
_LINE3(0xC0,0xE0,0x02)
_LINE4(0x08,0x44,0x24,0x01)
_LINE3(0xD9,0x2C,0x24)
_END_ASM
POP_EAX;
}

float _NAKED _APICALL _FLog2FPU(float)
{
_BEGIN_ASM
ASM( FLD1 ) \
ASM( fld dword ptr [esp+4] ) \
ASM( FYL2X ) \
_END_ASM
RET_1;
}

double _NAKED _APICALL _DLog2FPU(double)
{
_BEGIN_ASM
ASM( FLD1 ) \
ASM( fld qword ptr [esp+4] ) \
ASM( FYL2X ) \
_END_ASM
RET_2;
}

_int32 _NAKED _APICALL _ILog2FPU(unsigned _int32)
{
_BEGIN_ASM
_LINE2( 0x33,0xC0 )                         /* xor         eax,eax  */ \
_LINE5( 0x83,0x7C,0x24,0x04,0x00 )          /* cmp         dword ptr [esp+4],0  */ \
_LINE2( 0x7F,0x03 )                         /* jg          eee (1722ADh)  */ \
_LINE3( 0xC2,0x04,0x00 )                    /* ret         4  */ \
_LINE4( 0xDB,0x44,0x24,0x04 )               /* fild        dword ptr [esp+4]  */ \
_LINE4( 0xDD,0x5C,0x24,0xF4 )               /* fstp        qword ptr [esp-0Ch]  */ \
_LINE5( 0x0F,0xB7,0x44,0x24,0xFA )          /* movzx       eax,word ptr [esp-6]  */ \
_LINE3( 0xC1,0xE8,0x04 )                    /* shr         eax,4  */ \
_LINE5( 0x25,0xFF,0x07,0x00,0x00 )          /* and         eax,7FFh  */ \
_LINE5( 0x2D,0xFF,0x03,0x00,0x00 )          /* sub         eax,3FFh  */ \
_END_ASM
RET_1;
}

_int32 _NAKED _APICALL _LLog2FPU(_int64)
{
_BEGIN_ASM
_LINE2( 0x33,0xC0 )                         /* xor         eax,eax  */ \
_LINE5( 0x83,0x7C,0x24,0x04,0x00 )          /* cmp         dword ptr [esp+4],0  */ \
_LINE2( 0x7F,0x0A )                         /* jg          eee (1722ADh)  */ \
_LINE5( 0x83,0x7C,0x24,0x08,0x00 )          /* cmp         dword ptr [esp+8],0  */ \
_LINE2( 0x7F,0x03 )                         /* jg          eee (1722ADh)  */ \
_LINE3( 0xC2,0x04,0x00 )                    /* ret         4  */ \
_LINE4( 0xDF,0x6C,0x24,0x04 )               /* fild        qword ptr [esp+4]  */ \
_LINE4( 0xDD,0x5C,0x24,0xF4 )               /* fstp        qword ptr [esp-0Ch]  */ \
_LINE5( 0x0F,0xB7,0x44,0x24,0xFA )          /* movzx       eax,word ptr [esp-6]  */ \
_LINE3( 0xC1,0xE8,0x04 )                    /* shr         eax,4  */ \
_LINE5( 0x25,0xFF,0x07,0x00,0x00 )          /* and         eax,7FFh  */ \
_LINE5( 0x2D,0xFF,0x03,0x00,0x00 )          /* sub         eax,3FFh  */ \
_END_ASM
RET_2;
}

// ******************************* SSE ********************************

float _NAKED _APICALL _FsqrtSSE(float)
{
	_BEGIN_ASM
	_LINE6( 0xF3,0x0F,0x10,0x44,0x24,0x04 )    /* movss       xmm0,dword ptr [esp+4]  */ \
	_LINE4( 0xF3,0x0F,0x51,0xC8 )              /* sqrtss      xmm1,xmm0  */ \
	_LINE6( 0xF3,0x0F,0x11,0x4C,0x24,0x04 )    /* movss       dword ptr [esp+4],xmm1  */ \
	_LINE4( 0xD9,0x44,0x24,0x04 )              /* fld         dword ptr [esp+4]  */ \
	_END_ASM
	RET_1;
}

float _NAKED _APICALL _FFastInvSqrtSSE(float )
{
	_BEGIN_ASM
	ASM( movss xmm0,[esp+4] ) \
	_LINE4( 0xF3,0x0F,0x52,0xC0 )              /* rsqrtss     xmm0,xmm0  */ \
	_LINE6( 0xF3,0x0F,0x11,0x44,0x24,0xDC )    /* movss       dword ptr [esp-24h],xmm0  */ \
	_LINE4( 0xD9,0x44,0x24,0xDC )              /* fld         dword ptr [esp-24h]  */ \
	_END_ASM
	RET_1;
	}

// ************** SinCos SSE function *******************

void _NAKED _FASTCALL SUB_FSinCosSSE(float *,float *,float *,float )
{
	MATHPDSINCOSTABLESSE_FAST;
	//MATHPDSINCOSTABLESSE_STD;
	RET_2;
}

void _APICALL _FSinCosSSE(float a,float *s,float *c)
{
	SUB_FSinCosSSE(s,c,fastsindividef,a);
}

void _NAKED _FASTCALL SUB_FFastSinCosSSE(float *,float *,float *,float )
{
	MATHPDFASTSINCOSTABLESSE_FAST;
	RET_2;
}

void _APICALL _FFastSinCosSSE(float a,float *s,float *c)
{
	SUB_FFastSinCosSSE(s,c,fastsindividef,a);
}

// ************** ArcTg SSE function *******************

	/*float _STDCALL _FArcTgSSE(float _x,float _y)
	{
		float _b;
		if (_x==0) _b=1;
		if (_y==0) _b=0;
		float b=0;
		float bs=0;
		float abs[2]={_x,_y};
		if (abs[0]<0) abs[0]=-abs[0];
		if (abs[1]<0) abs[1]=-abs[1];
		if (abs[1]==abs[0]) {
			_b=0.78539816339744830961566084581988f;
		} else {
			if (abs[1]>abs[0]) bs=abs[0]/abs[1];
			if (abs[1]<abs[0]) bs=abs[1]/abs[0];
			if (bs<0) bs=-bs;
			if (bs>0.4142135623730950488016887242097f) {
				__m128 v3 = _mm_loadl_pi(v3,(const __m64 *)abs);
				__m128 v1 = _mm_setzero_ps();
				__m128 v2 = _mm_load_ps(bt::rotateArcTgf);
				v3 = _mm_shuffle_ps(v3, v3, 0x14);
				if (abs[1]>abs[0]) {
					v3 = _mm_mul_ps(v3, v2);
					v1 = _mm_movehl_ps(v1, v3);
					v1 = _mm_sub_ps(v1, v3);
					_mm_storel_pi((__m64*)abs,v1);
					b=abs[0]/abs[1];
				}
				if (abs[1]<abs[0]) {
					v3 = _mm_mul_ps(v3, v2);
					v1 = _mm_movehl_ps(v1, v3);
					v3 = _mm_add_ps(v3, v1);
					_mm_storel_pi((__m64*)abs,v3);
					b=abs[1]/abs[0];
				}
			} else b=bs;

			float a3=1.0f;
			float a4=-1.0f;

			__m128 v5 = _mm_load_ss(&b);
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
			__m128 v8 = _mm_load_ss(&a3);
			v6 = _mm_load_ss(&a4);
			v6 = _mm_shuffle_ps(v6, v8, 0x00);
			v5 = _mm_mul_ps(_mm_mul_ps(v5, v7),_mm_shuffle_ps(v6, v6, 0x88));
			v7 = _mm_shuffle_ps(v7, v7, 0xFF);//FF
			v6 = v5;

			__m128 v1 = _mm_load_ps(bt::fasttgdividef);
			__m128 v2 = _mm_load_ps(bt::fasttgdividef + 4);
			v6 = _mm_mul_ps(v6, v7);
			v7 = _mm_mul_ps(v7, v7);
			v1 = _mm_add_ps(_mm_mul_ps(v1, v5), _mm_mul_ps(v2, v6));
			v5 = _mm_mul_ps(v5, v7);
			__m128 v4 = _mm_setzero_ps();
			v6 = _mm_mul_ps(v6, v7);
			__m128 v3 = _mm_add_ps(_mm_mul_ps(_mm_load_ps(bt::fasttgdividef + 8), v5), _mm_mul_ps(_mm_load_ps(bt::fasttgdividef + 12), v6));
			v1 = _mm_add_ps(v1, v3);
			v1 = _mm_add_ps(v1, _mm_movehl_ps(v4,v1));
			v2 = v1;
			v2 = _mm_shuffle_ps(v2, v2, 0x01);
			v1 = _mm_add_ss(v1, v9);
			v1 = _mm_add_ss(v1, v2);
			_mm_store_ss(&_b,v1);

			if (bs>0.4142135623730950488016887242097f) _b+=0.39269908169872415480783042290994f;
		}
		if (_y*_x<0) _b=-_b;
		//if (abs[1]>abs[0]) _b=-_b;
		float fs=0;
		if (abs[1]>abs[0]) {
			_b=-_b;
			fs=3.1415926535897932384626433832795f*0.5f;
		} else if (_x<0) {
			fs=3.1415926535897932384626433832795f;
		}
		if (_y<0) _b-=fs;
		if (_y>=0) _b+=fs;
		return _b;
	}*/

	float _APICALL _FArcTgSSE(float _x,float )
	{
		__m128 vB;
		__m128 vZero = _mm_setzero_ps();
		__m128 vABS = vZero;
		vABS = _mm_loadl_pi(vABS,(__m64*)&_x);
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

/*
 push        ebp  
 mov         ebp,esp  
 and         esp,0FFFFFFF0h  
 sub         esp,20h  
 xorps       xmm5,xmm5  
 movaps      xmm0,xmm5  
 movlps      xmm0,qword ptr [_x]  
 movaps      xmm2,xmm0  
 cmpltps     xmm2,xmm5  
 movaps      xmm1,xmm5  
 subps       xmm1,xmm0  
 andps       xmm1,xmm2  
 andnps      xmm2,xmm0  
 orps        xmm1,xmm2  
 movaps      xmm6,xmm1  
 shufps      xmm6,xmm5,1  
 comiss      xmm1,xmm6  
 movaps      xmm7,xmm0  
 movaps      xmmword ptr [esp+10h],xmm7  
 movaps      xmm3,xmm5  
 movaps      xmm4,xmm5  
 jne         bt::_FArcTgSSE+50h (5E1E03E0h)  
 movss       xmm0,dword ptr [bt::rotateArcTgf+10h (5E23E9B0h)]  
 jmp         bt::_FArcTgSSE+195h (5E1E0525h)  
 comiss      xmm6,xmm1  
 mov         ecx,0  
 mov         eax,1  
 cmovbe      ecx,eax  
 test        ecx,ecx  
 jne         bt::_FArcTgSSE+6Bh (5E1E03FBh)  
 movaps      xmm4,xmm1  
 divss       xmm4,xmm6  
 comiss      xmm6,xmm1  
 jae         bt::_FArcTgSSE+77h (5E1E0407h)  
 movaps      xmm4,xmm6  
 divss       xmm4,xmm1  
 comiss      xmm4,xmm5  
 jae         bt::_FArcTgSSE+86h (5E1E0416h)  
 movaps      xmm0,xmm5  
 subss       xmm0,xmm4  
 movaps      xmm4,xmm0  
 movss       xmm0,dword ptr [bt::rotateArcTgf+14h (5E23E9B4h)]  
 comiss      xmm4,xmm0  
 mov         eax,0  
 mov         edx,1  
 cmovbe      eax,edx  
 test        eax,eax  
 jne         bt::_FArcTgSSE+0F8h (5E1E0488h)  
 movaps      xmm4,xmmword ptr [bt::rotateArcTgf (5E23E9A0h)]  
 movaps      xmm2,xmm1  
 shufps      xmm2,xmm1,14h  
 movaps      xmm0,xmm5  
 test        ecx,ecx  
 jne         bt::_FArcTgSSE+0D7h (5E1E0467h)  
 movaps      xmm0,xmm4  
 mulps       xmm2,xmm0  
 movaps      xmm0,xmm5  
 movhlps     xmm0,xmm2  
 movaps      xmm1,xmm0  
 addps       xmm1,xmm2  
 movaps      xmm6,xmm1  
 shufps      xmm6,xmm1,1  
 movaps      xmm3,xmm1  
 divss       xmm3,xmm6  
 comiss      xmm6,xmm1  
 jae         bt::_FArcTgSSE+0FBh (5E1E048Bh)  
 mulps       xmm4,xmm2  
 movaps      xmm1,xmm4  
 movhlps     xmm0,xmm1  
 subps       xmm1,xmm0  
 movaps      xmm6,xmm1  
 shufps      xmm6,xmm1,1  
 movaps      xmm3,xmm6  
 divss       xmm3,xmm1  
 jmp         bt::_FArcTgSSE+0FBh (5E1E048Bh)  
 movaps      xmm3,xmm4  
 movaps      xmm0,xmmword ptr [esp+10h]  
 movaps      xmm7,xmmword ptr [esp+10h]  
 movss       xmm2,xmm3  
 movss       xmm0,xmm2  
 mulss       xmm0,xmm0  
 shufps      xmm0,xmm0,50h  
 mulss       xmm0,xmm0  
 shufps      xmm0,xmm0,51h  
 movaps      xmm4,xmm0  
 shufps      xmm4,xmm0,0A5h  
 mulps       xmm4,xmm0  
 movaps      xmm2,xmm0  
 movss       xmm0,dword ptr [__real@bf800000 (5E2270B4h)]  
 movlhps     xmm2,xmm4  
 movss       xmm4,dword ptr [__real@3f800000 (5E22678Ch)]  
 shufps      xmm0,xmm4,0  
 shufps      xmm0,xmm0,88h  
 movaps      xmm4,xmm3  
 shufps      xmm4,xmm3,0  
 mulps       xmm4,xmm2  
 mulps       xmm4,xmm0  
 movaps      xmm0,xmmword ptr [bt::fasttgdividef (5E23E190h)]  
 shufps      xmm2,xmm2,0FFh  
 mulps       xmm0,xmm4  
 mulps       xmm2,xmm4  
 mulps       xmm2,xmmword ptr [bt::fasttgdividef+10h (5E23E1A0h)]  
 addps       xmm2,xmm0  
 movaps      xmm0,xmm5  
 movhlps     xmm0,xmm2  
 addps       xmm0,xmm2  
 movaps      xmm2,xmm0  
 shufps      xmm2,xmm0,1  
 addss       xmm0,xmm3  
 addss       xmm0,xmm2  
 test        eax,eax  
 jne         bt::_FArcTgSSE+195h (5E1E0525h)  
 movss       xmm2,dword ptr [bt::rotateArcTgf+18h (5E23E9B8h)]  
 addss       xmm0,xmm2  
 movaps      xmm3,xmm7  
 shufps      xmm3,xmm7,1  
 movaps      xmm2,xmm3  
 mulss       xmm2,xmm7  
 comiss      xmm2,xmm5  
 jae         bt::_FArcTgSSE+1B2h (5E1E0542h)  
 movaps      xmm2,xmm5  
 subss       xmm2,xmm0  
 movaps      xmm0,xmm2  
 comiss      xmm6,xmm1  
 movaps      xmm2,xmm5  
 jbe         bt::_FArcTgSSE+1CEh (5E1E055Eh)  
 movss       xmm2,dword ptr [bt::rotateArcTgf+20h (5E23E9C0h)]  
 movaps      xmm1,xmm5  
 subss       xmm1,xmm0  
 movaps      xmm0,xmm1  
 jmp         bt::_FArcTgSSE+1DBh (5E1E056Bh)  
 comiss      xmm7,xmm5  
 jae         bt::_FArcTgSSE+1DBh (5E1E056Bh)  
 movss       xmm2,dword ptr [bt::rotateArcTgf+1Ch (5E23E9BCh)]  
 comiss      xmm3,xmm5  
 jae         bt::_FArcTgSSE+1F4h (5E1E0584h)  
 subss       xmm0,xmm2  
 movss       dword ptr [esp+0Ch],xmm0  
 fld         dword ptr [esp+0Ch]  
 mov         esp,ebp  
 pop         ebp  
 ret         8  
 addss       xmm0,xmm2  
 movss       dword ptr [esp+0Ch],xmm0  
 fld         dword ptr [esp+0Ch]  
 mov         esp,ebp  
 pop         ebp  
 ret         8   
*/

float _NAKED _APICALL _Fmul2NSSE(float,int)
{
	_BEGIN_ASM
	ASM( mov eax,1 ) \
	ASM( mov ecx,[esp+8] ) \
	ASM( movss xmm1,[esp+4] ) \
	ASM( cmp ecx,0 ) \
	ASM( jl _Fmul2NSSE01 ) \
	ASM( je _Fmul2NSSE02 ) \
	ASM( shl eax,cl ) \
	ASM( cvtsi2ss    xmm0,eax )              /* cvtsi2ss    xmm0,eax */ \
	ASM( mulss xmm1,xmm0 ) \
	_LINE6( 0xF3,0x0F,0x11,0x4C,0x24,0x04 )    /* movss       dword ptr [esp+4],xmm1  */ \
	ASM( _Fmul2NSSE02: ) \
	_LINE4( 0xD9,0x44,0x24,0x04 )              /* fld         dword ptr [esp+4]  */ \
	_LINE3( 0xC2,0x08,0x00 )
	ASM( _Fmul2NSSE01: ) \
	ASM( neg ecx ) \
	ASM( shl eax,cl ) \
	ASM( cvtsi2ss    xmm0,eax )              /* cvtsi2ss    xmm0,eax */ \
	ASM( divss xmm1,xmm0 ) \
	_LINE6( 0xF3,0x0F,0x11,0x4C,0x24,0x04 )    /* movss       dword ptr [esp+4],xmm1  */ \
	_LINE4( 0xD9,0x44,0x24,0x04 )              /* fld         dword ptr [esp+4]  */ \
	_LINE3( 0xC2,0x08,0x00 )
	_END_ASM
}

int _NAKED _APICALL _FTruncSSE(float)
{
	_BEGIN_ASM \
	_LINE6( 0xF3,0x0F,0x2C,0x44,0x24,0x04 )              /*cvttss2si   eax,dword ptr [esp+4] */ \
	_END_ASM
	RET_1;
}

int _NAKED _APICALL _FRoundSSE(float)
{
_BEGIN_ASM
_LINE6( 0xF3,0x0F,0x2D,0x44,0x24,0x04 )              /* cvtss2si   eax,dword ptr [esp+4] */ \
_END_ASM
RET_1;
}

// ******************************* Exp SSE *******************************

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

// ******************************* SSE2 *******************************

double _NAKED _APICALL _DsqrtSSE2(double)
{
	_BEGIN_ASM
	_LINE6( 0xF2,0x0F,0x10,0x44,0x24,0x04 )    /* movsd       xmm0,mmword ptr [esp+4]  */ \
	_LINE4( 0xF2,0x0F,0x51,0xC8 )              /* sqrtsd      xmm1,xmm0  */ \
	_LINE6( 0xF2,0x0F,0x11,0x4C,0x24,0x04 )    /* movsd       mmword ptr [esp+4],xmm1  */ \
	_LINE4( 0xDD,0x44,0x24,0x04 )              /* fld         qword ptr [esp+4]  */ \
	_END_ASM
	RET_2;
}

double _NAKED _APICALL _DFastInvSqrtSSE2(double )
{
	_BEGIN_ASM
	_LINE6( 0xF2,0x0F,0x10,0x44,0x24,0x04 )    /* movsd       xmm0,mmword ptr [esp+4]  */ \
	_LINE4( 0xF2,0x0F,0x5A,0xC0 )              /* cvtsd2ss    xmm0,xmm0  */ \
	_LINE4( 0xF3,0x0F,0x52,0xC0 )              /* rsqrtss     xmm0,xmm0  */ \
	_LINE6( 0xF3,0x0F,0x11,0x44,0x24,0x04 )    /* movss       dword ptr [esp+4],xmm0  */ \
	_LINE4( 0xD9,0x44,0x24,0x04 )              /* fld         dword ptr [esp+4]  */ \
	_END_ASM
	RET_2;
}

void _NAKED _APICALL _FSinCosSSE2(float ,float *,float *)
{
	//MATHPDSINCOSSSE2_STD;
	RET_3;
}

void _NAKED _FASTCALL SUB_DSinCosSSE2(double *,double *,double *,double )
{
	MATHPDDSINCOSTABLESSE2_FAST;
	RET_3;
}

void _APICALL _DSinCosSSE2(double a,double *s,double *c)
{
	SUB_DSinCosSSE2(s,c,fastsindivided,a);
}

void _NAKED _FASTCALL SUB_DFastSinCosSSE2(double *,double *,double *,double )
{
	MATHPDDFASTSINCOSTABLESSE2_FAST;
	RET_3;
}

void _APICALL _DFastSinCosSSE2(double a,double *s,double *c)
{
	SUB_DFastSinCosSSE2(s,c,fastsindivided,a);
}

float _NAKED _APICALL _Fmul2NSSE2(float,int)
{
	_BEGIN_ASM \
	_LINE4( 0x8B,0x44,0x24,0x08 )           /* mov         eax,dword ptr [esp+8]  */ \
	_LINE3( 0x83,0xC0,0x7F )                /* add         eax,7Fh  */ \
	_LINE5( 0x25,0xFF,0x00,0x00,0x00 )      /* and         eax,0FFh  */ \
	_LINE3( 0xC1,0xE0,0x17 )                /* shl         eax,17h  */ \
	_LINE4( 0x66,0x0F,0x6E,0xC0 )           /* movd        xmm0,eax  */ \
	_LINE6( 0xF3,0x0F,0x10,0x4C,0x24,0x04 ) /* movss       xmm1,dword ptr [esp+4]  */ \
	_LINE4( 0xF3,0x0F,0x59,0xC8 )           /* mulss       xmm1,xmm0  */ \
	_LINE6( 0xF3,0x0F,0x11,0x4C,0x24,0x04 ) /* movss       dword ptr [esp+4],xmm1  */ \
	_LINE4( 0xD9,0x44,0x24,0x04 )           /* fld         dword ptr [esp+4]  */ \
	_LINE3( 0xC2,0x08,0x00 ) \
	_END_ASM
}

double _NAKED _APICALL _Dmul2NSSE2(double,int)
{
	_BEGIN_ASM \
	_LINE4( 0x8B,0x44,0x24,0x0C )           /* mov         eax,dword ptr [esp+12]  */ \
	ASM( add eax,0x3FF ) \
	_LINE5( 0x25,0xFF,0x07,0x00,0x00 )      /* and         eax,0FFh  */ \
	_LINE3( 0xC1,0xE0,0x14 )                /* shl         eax,14h  */ \
	_LINE4( 0x66,0x0F,0x6E,0xC0 )           /* movd        xmm0,eax  */ \
	ASM( shufps xmm0,xmm0,1 ) \
	ASM( movsd xmm1,[esp+4] ) \
	ASM( mulsd xmm1,xmm0 ) \
	ASM( movsd [esp+4],xmm1 ) \
	_LINE4( 0xDD,0x44,0x24,0x04 )              /* fld         qword ptr [esp+4]  */ \
	_LINE3( 0xC2,0x0C,0x00 ) \
	_END_ASM
}

int _NAKED _APICALL _DTruncSSE2(double)
{
_BEGIN_ASM
_LINE6( 0xF2,0x0F,0x2C,0x44,0x24,0x04 )              /* cvttsd2si    eax,mmword ptr [esp+4] */ \
_END_ASM
RET_2;
}

int _NAKED _APICALL _DRoundSSE2(double)
{
_BEGIN_ASM
_LINE6( 0xF2,0x0F,0x2D,0x44,0x24,0x04 )              /* cvtsd2si    eax,mmword ptr [esp+4] */ \
_END_ASM
RET_2;
}

int _NAKED _APICALL _Fmul2NTruncSSE2(float ,int )
{
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x08 )           /* mov         eax,dword ptr [esp+8]  */ \
_LINE3( 0x83,0xC0,0x7F )                /* add         eax,7Fh  */ \
_LINE5( 0x25,0xFF,0x00,0x00,0x00 )      /* and         eax,0FFh  */ \
_LINE3( 0xC1,0xE0,0x17 )                /* shl         eax,17h  */ \
_LINE4( 0x66,0x0F,0x6E,0xC0 )           /* movd        xmm0,eax  */ \
ASM( movss xmm1,[esp+4] ) \
ASM( mulss xmm1,xmm0 ) \
ASM( cvttss2si    eax,xmm1 ) \
_END_ASM
RET_2;
}

int _NAKED _APICALL _Dmul2NTruncSSE2(double ,int )
{
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x0C )           /* mov         eax,dword ptr [esp+12]  */ \
ASM( add eax,0x3FF ) \
_LINE5( 0x25,0xFF,0x07,0x00,0x00 )      /* and         eax,0FFh  */ \
_LINE3( 0xC1,0xE0,0x14 )                /* shl         eax,14h  */ \
_LINE4( 0x66,0x0F,0x6E,0xC0 )           /* movd        xmm0,eax  */ \
ASM( shufps xmm0,xmm0,1 ) \
ASM( movsd xmm1,[esp+4] ) \
ASM( mulsd xmm1,xmm0 ) \
ASM( cvttsd2si    eax,xmm1 ) \
_END_ASM
RET_3;
}

int _NAKED _APICALL _Fmul2NRoundSSE2(float ,int )
{
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x08 )           /* mov         eax,dword ptr [esp+8]  */ \
_LINE3( 0x83,0xC0,0x7F )                /* add         eax,7Fh  */ \
_LINE5( 0x25,0xFF,0x00,0x00,0x00 )      /* and         eax,0FFh  */ \
_LINE3( 0xC1,0xE0,0x17 )                /* shl         eax,17h  */ \
_LINE4( 0x66,0x0F,0x6E,0xC0 )           /* movd        xmm0,eax  */ \
ASM( movss xmm1,[esp+4] ) \
ASM( mulss xmm1,xmm0 ) \
ASM( cvtss2si    eax,xmm1 ) \
_END_ASM
RET_2;
}

int _NAKED _APICALL _Dmul2NRoundSSE2(double ,int )
{
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x0C )            /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE5( 0x05,0xFF,0x03,0x00,0x00 )       /* add         eax,3FFh  */ \
_LINE5( 0x25,0xFF,0x07,0x00,0x00 )       /* and         eax,7FFh  */ \
_LINE3( 0xC1,0xE0,0x14 )                 /* shl         eax,14h  */ \
_LINE4( 0x66,0x0F,0x6E,0xC0 )            /* movd        xmm0,eax  */ \
_LINE4( 0x0F,0xC6,0xC0,0x01 )            /* shufps      xmm0,xmm0,1  */ \
_LINE6( 0xF2,0x0F,0x10,0x4C,0x24,0x04 )  /* movsd       xmm1,mmword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x59,0xC8 )            /* mulsd       xmm1,xmm0  */ \
_LINE4( 0xF2,0x0F,0x2D,0xC1 )            /* cvtsd2si    eax,xmm1  */ \
_END_ASM
RET_3;
}

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

// ******************************* ilog2 SSE2 *******************************

int _NAKED _APICALL _ILog2SSE2(unsigned int)
{
_BEGIN_ASM
_LINE2( 0x33,0xC0 )                         /* xor         eax,eax  */ \
_LINE5( 0x83,0x7C,0x24,0x04,0x00 )          /* cmp         dword ptr [esp+4],0  */ \
_LINE2( 0x7F,0x03 )                         /* jg          eee (1722ADh)  */ \
_LINE3( 0xC2,0x04,0x00 )                    /* ret         4  */ \
_LINE6( 0xF2,0x0F,0x2A,0x44,0x24,0x04 )     /* cvtsi2sd    xmm0,dword ptr [esp+4]  */ \
_LINE5( 0x66,0x0F,0x73,0xF0,0x01 )          /* psllq       xmm0,1  */ \
_LINE5( 0x66,0x0F,0x73,0xD0,0x35 )          /* psrlq       xmm0,35h  */ \
_LINE4( 0x66,0x0F,0x7E,0xC0 )               /* movd        eax,xmm0  */ \
_LINE5( 0x2D,0xFF,0x03,0x00,0x00 )          /* sub         eax,3FFh  */ \
_END_ASM
RET_1;
}

// ******************************* SSE3 *******************************

void _NAKED _APICALL _FSinCosSSE3(float ,float *,float *)
{
	//MATHPDSINCOSSSE3_STD;
	RET_3;
}

/*float _NAKED _STDCALL _FArcTgSSE3(float,float)
{
_BEGIN_ASM
ASM( movss xmm0,[esp+4] ) \
ASM( movss xmm1,[esp+8] ) \
ASM( xorps xmm2,xmm2 ) \
ASM( movaps xmm4,xmm0 ) \
ASM( ucomiss xmm2,xmm0 ) \
ASM( ja 0x433d90 ) \
ASM( ucomiss xmm2,xmm1 ) \
ASM( movaps xmm5,xmm1 ) \
ASM( ja 0x433d78 ) \
ASM( ucomiss xmm4,xmm5 ) \
ASM( jp 0x433c28 ) \
ASM( movss xmm3,0.78539816339744830961566084581988f ) \
ASM( jne 0x433c28 ) \
ASM( movps xmm6,xmm0 ) \
ASM( mulss xmm6,xmm1 ) \
ASM( ucomiss xmm2,xmm6 ) \
ASM( ja 0x433d37 ) \
ASM( ucomiss xmm5,xmm4 ) \
ASM( jbe 0x433d4d ) \
ASM( ucomiss %xmm1,%xmm2 ) \
ASM( movss xmm0,0x48cf0(%rip),xmm0        # 0x47c8f0 ) \
ASM( xorps xmm3,xmm0 ) \
ASM( movss 0x4c788(%rip),%xmm0        # 0x480394 ) \
ASM( ja 0x433d68 ) \
ASM( 0x433c12: ucomiss xmm1,xmm2 ) \
ASM( jb 0x433c1c ) \
ASM( addss xmm3,xmm0 ) \
ASM( 0x433c1c:   movaps xmm0,%xmm3 ) \
ASM( retq  ) \
ASM( nopl 0x0(%rax) ) \
ASM( 0x433c28:   vucomiss %xmm4,%xmm5 ) \
ASM( movaps xmm6,xmm2 ) \
ASM( jbe 0x433c36 ) \
ASM( movaps xmm6,xmm4 ) \
ASM( 0000000000433c32:   divss xmm6,xmm5 ) \
ASM( 0x433c36:   ucomiss xmm4,xmm5 ) \
ASM( jbe 0x433c40 ) \
ASM( movaps xmm6,xmm5 ) \
ASM( 0000000000433c3c:   vdivss xmm6áxmm4 ) \
ASM( 0x433c40:   ucomiss xmm2,xmm6 ) \
ASM( 0000000000433c44:   ja 0x433e40 ) \
ASM( 0000000000433c4a:   vucomiss 0x4c74a(%rip),%xmm6        # 0x48039c ) \
ASM( 0000000000433c52:   ja 0x433db0 <bt::_FArcTgSSE3(float, float)+528> ) \
ASM( 0x433c58:   vmovaps %xmm6,%xmm8 ) \
ASM( 0000000000433c5c:   vmovss -0x14(%rsp),%xmm5 ) \
ASM( 0000000000433c62:   vmovss -0x18(%rsp),%xmm4 ) \
ASM( 0x433c68:   vinsertps $0xe,%xmm8,%xmm8,%xmm8 ) \
ASM( 0000000000433c6e:   vxorps %xmm3,%xmm3,%xmm3 ) \
ASM( 0000000000433c72:   vucomiss 0x4c722(%rip),%xmm6        # 0x48039c ) \
ASM( 0000000000433c7a:   vshufps $0x0,%xmm8,%xmm8,%xmm9 ) \
ASM( 0000000000433c80:   vmovss %xmm8,%xmm3,%xmm3 ) \
ASM( 0000000000433c84:   vmulss %xmm3,%xmm3,%xmm3 ) \
ASM( 0000000000433c88:   vshufps $0x50,%xmm3,%xmm3,%xmm3 ) \
ASM( 0000000000433c8d:   vmulss %xmm3,%xmm3,%xmm3 ) \
ASM( 0000000000433c91:   vshufps $0xf1,%xmm3,%xmm3,%xmm3 ) \
ASM( 0000000000433c96:   vshufps $0xa5,%xmm3,%xmm3,%xmm7 ) \
ASM( 0000000000433c9b:   vmulps %xmm3,%xmm7,%xmm7 ) \
ASM( 0000000000433c9f:   vmovlhps %xmm7,%xmm3,%xmm3 ) \
ASM( 0000000000433ca3:   vmovss 0x4c6b5(%rip),%xmm7        # 0x480360 ) \
ASM( 0000000000433cab:   vshufps $0x0,0x4c6bc(%rip),%xmm7,%xmm7        # 0x480370 ) \
ASM( 0000000000433cb4:   vmulps %xmm3,%xmm9,%xmm9 ) \
ASM( 0000000000433cb8:   vshufps $0xff,%xmm3,%xmm3,%xmm3 ) \
ASM( 0000000000433cbd:   vshufps $0x88,%xmm7,%xmm7,%xmm7 ) \
ASM( 0000000000433cc2:   vmulps %xmm7,%xmm9,%xmm9 ) \
ASM( 0000000000433cc6:   vmulps %xmm3,%xmm9,%xmm10 ) \
ASM( 0000000000433cca:   vmulps %xmm3,%xmm3,%xmm3 ) \
ASM( 0000000000433cce:   vmulps 0x270d7a(%rip),%xmm9,%xmm7        # 0x6a4a50 <_ZN2bt13fasttgdividefE> ) \
ASM( 0000000000433cd6:   vmulps 0x270d82(%rip),%xmm10,%xmm11        # 0x6a4a60 <_ZN2bt13fasttgdividefE+16> ) \
ASM( 0000000000433cde:   vmulps %xmm3,%xmm9,%xmm3 ) \
ASM( 0000000000433ce2:   vmulps 0x270d96(%rip),%xmm10,%xmm10        # 0x6a4a80 <_ZN2bt13fasttgdividefE+48> ) \
ASM( 0000000000433cea:   vmulps 0x270d7e(%rip),%xmm3,%xmm3        # 0x6a4a70 <_ZN2bt13fasttgdividefE+32> ) \
ASM( 0000000000433cf2:   vaddps %xmm11,%xmm7,%xmm9 ) \
ASM( 0000000000433cf7:   vaddps %xmm10,%xmm3,%xmm3 ) \
ASM( 0000000000433cfc:   vaddps %xmm3,%xmm9,%xmm9 ) \
ASM( 0000000000433d00:   vmovhlps %xmm9,%xmm10,%xmm7 ) \
ASM( 0000000000433d05:   vaddps %xmm7,%xmm9,%xmm7 ) \
ASM( 0000000000433d09:   vshufps $0x1,%xmm7,%xmm7,%xmm3 ) \
ASM( 0000000000433d0e:   vaddss %xmm8,%xmm7,%xmm7 ) \
ASM( 0000000000433d13:   vaddss %xmm3,%xmm7,%xmm7 ) \
ASM( 0000000000433d17:   vmovaps %xmm7,%xmm3 ) \
ASM( 0000000000433d1b:   jbe 0x433bdc <bt::_FArcTgSSE3(float, float)+60> ) \
ASM( 0000000000433d21:   vmulss %xmm0,%xmm1,%xmm6 ) \
ASM( 0000000000433d25:   vaddss 0x4c673(%rip),%xmm3,%xmm3        # 0x4803a0 ) \
ASM( 0000000000433d2d:   vucomiss %xmm6,%xmm2 ) \
ASM( 0000000000433d31:   jbe 0x433bea <bt::_FArcTgSSE3(float, float)+74> ) \
ASM( 0x433d37:   vucomiss %xmm4,%xmm5 ) \
ASM( 0000000000433d3b:   vmovss 0x48bad(%rip),%xmm6        # 0x47c8f0 ) \
ASM( 0000000000433d43:   vxorps %xmm6,%xmm3,%xmm3 ) \
ASM( 0000000000433d47:   ja 0x433bf4 <bt::_FArcTgSSE3(float, float)+84> ) \
ASM( 0000000000433d4d:   vucomiss %xmm1,%xmm2 ) \
ASM( 0000000000433d51:   vcmpltss %xmm2,%xmm0,%xmm0 ) \
ASM( 0000000000433d56:   vmovss 0x4c63a(%rip),%xmm4        # 0x480398 ) \
ASM( 0000000000433d5e:   vandps %xmm0,%xmm4,%xmm0 ) \
ASM( 0000000000433d62:   jbe 0x433c12 <bt::_FArcTgSSE3(float, float)+114> ) \
ASM( 0x433d68:   vsubss %xmm0,%xmm3,%xmm3 ) \
ASM( 0000000000433d6c:   jmpq 0x433c12 <bt::_FArcTgSSE3(float, float)+114> ) \
ASM( 0000000000433d71:   nopl 0x0(%rax) ) \
ASM( 0x433d78:   vmovss 0x48b70(%rip),%xmm5        # 0x47c8f0 ) \
ASM( 0000000000433d80:   vxorps %xmm1,%xmm5,%xmm5 ) \
ASM( 0000000000433d84:   vmovss %xmm5,-0x14(%rsp) ) \
ASM( 0000000000433d8a:   jmpq 0x433bcc <bt::_FArcTgSSE3(float, float)+44> ) \
ASM( 0000000000433d8f:   nop  ) \
ASM( 0x433d90: movss xmm4,[%rip] ) \
ASM( 0000000000433d98:   vxorps %xmm0,%xmm4,%xmm4 ) \
ASM( 0000000000433d9c:   vmovss %xmm4,-0x18(%rsp) ) \
ASM( 0000000000433da2:   jmpq 0x433bbe <bt::_FArcTgSSE3(float, float)+30> ) \
ASM( 0000000000433da7:   nopw 0x0(%rax,%rax,1) ) \
ASM( 0x433db0:   vxorps %xmm3,%xmm3,%xmm3 ) \
ASM( 0000000000433db4:   vmovss -0x14(%rsp),%xmm5 ) \
ASM( 0000000000433dba:   vmovss -0x18(%rsp),%xmm4 ) \
ASM( 0000000000433dc0:   vucomiss %xmm4,%xmm5 ) \
ASM( 0000000000433dc4:   vmovlps -0x18(%rsp),%xmm3,%xmm3 ) \
ASM( 0000000000433dca:   vmovaps 0x2706fe(%rip),%xmm7        # 0x6a44d0 <_ZN2bt12rotateArcTgfE> ) \
ASM( 0000000000433dd2:   vshufps $0x14,%xmm3,%xmm3,%xmm3 ) \
ASM( 0000000000433dd7:   jbe 0x433e60 <bt::_FArcTgSSE3(float, float)+704> ) \
ASM( 0000000000433ddd:   vmulps %xmm7,%xmm3,%xmm3 ) \
ASM( 0000000000433de1:   vxorps %xmm9,%xmm9,%xmm9 ) \
ASM( 0000000000433de6:   vmovhlps %xmm3,%xmm9,%xmm9 ) \
ASM( 0000000000433dea:   vsubps %xmm3,%xmm9,%xmm9 ) \
ASM( 0000000000433dee:   vmovlps %xmm9,-0x18(%rsp) ) \
ASM( 0000000000433df4:   vmovss -0x18(%rsp),%xmm4 ) \
ASM( 0000000000433dfa:   vmovss -0x14(%rsp),%xmm5 ) \
ASM( 0000000000433e00:   vdivss %xmm5,%xmm4,%xmm8 ) \
ASM( 0x433e04:   vucomiss %xmm5,%xmm4 ) \
ASM( 0000000000433e08:   jbe 0x433c68 <bt::_FArcTgSSE3(float, float)+200> ) \
ASM( 0000000000433e0e:   vmulps %xmm7,%xmm3,%xmm3 ) \
ASM( 0000000000433e12:   vmovhlps %xmm3,%xmm9,%xmm9 ) \
ASM( 0000000000433e16:   vaddps %xmm9,%xmm3,%xmm3 ) \
ASM( 0000000000433e1b:   vmovlps %xmm3,-0x18(%rsp) ) \
ASM( 0000000000433e21:   vmovss -0x14(%rsp),%xmm5 ) \
ASM( 0000000000433e27:   vdivss -0x18(%rsp),%xmm5,%xmm8 ) \
ASM( 0000000000433e2d:   vmovss -0x18(%rsp),%xmm4 ) \
ASM( jmpq 0x433c68 ) \
ASM( 0000000000433e38:   nopl 0x0(%rax,%rax,1) ) \
ASM( 0x433e40:   vmovss 0x48aa8(%rip),%xmm3        # 0x47c8f0 ) \
ASM( 0000000000433e48:   xorps xmm6,xmm3 ) \
ASM( 0000000000433e4c:   vucomiss 0x4c548(%rip),%xmm6        # 0x48039c ) \
ASM( jbe 0x433c58 ) \
ASM( jmpq 0x433db0 ) \
ASM( nop  ) \
ASM( 0x433e60:   movaps xmm8,xmm2 ) \
ASM( xorps xmm9,xmm9 ) \
ASM( jmp 0x433e04 ) \
ASM( 0000000000433e6b:   nopl 0x0(%rax,%rax,1) ) \
_END_ASM
RET_2;
}*/


// ******************************* Spline Catmule Rome SSE4 *******************************

	void _APICALL _FPCRCCSSE4(float **a,float *cof)
	{
		__m128 v0=_mm_load_ss(a[0]);
		__m128 v1=_mm_load_ss(a[1]);
		__m128 v2=_mm_load_ss(a[2]);
		__m128 v3=_mm_load_ss(a[3]);
		__m128 v4=_mm_shuffle_ps(_mm_shuffle_ps(v0,v1,0x44),_mm_shuffle_ps(v2,v3,0x44),0x88);
		__m128 v6;
		__m128 v7=_mm_load_ps((fcmsplinef+4));
		_mm_store_ss(cof,_mm_dp_ps(v4,_mm_load_ps(fcmsplinef),0xF1));
		_mm_store_ss(cof+1,_mm_dp_ps(v4,v7,0xF1));
		_mm_store_ss(cof+2,_mm_sub_ss(v2,v0));
		_mm_store_ss(cof+3,_mm_mul_ss(v1,v7));
	}

	void _APICALL _DPCRCCSSE4(double **a,double *cof)
	{
		__m128d v0=_mm_load_sd(a[0]);
		__m128d v1=_mm_load_sd(a[1]);
		__m128d v2=_mm_load_sd(a[2]);
		__m128d v3=_mm_load_sd(a[3]);
		__m128d v4=_mm_shuffle_pd(v0,v1,0x0);
		__m128d v5=_mm_shuffle_pd(v2,v3,0x0);
		_mm_store_sd(cof,_mm_add_sd(_mm_dp_pd(v4,_mm_load_pd(fcmsplined),0x31),_mm_dp_pd(v5,_mm_load_pd(fcmsplined+2),0x31)));
		__m128d v6=_mm_load_pd(fcmsplined+4);
		_mm_store_sd(cof+1,_mm_add_sd(_mm_dp_pd(v4,v6,0x31),_mm_dp_pd(v5,_mm_load_pd(fcmsplined+6),0x31)));
		_mm_store_sd(cof+2,_mm_sub_sd(v2,v0));
		_mm_store_sd(cof+3,_mm_mul_sd(v1,v6));
	}

	void _APICALL _FSplineCRSSE4(float *a,float *b,float c,float d)
	{
		__m128 v1=_mm_set_ss(c);
		__m128 v4=_mm_shuffle_ps(v1,_mm_set_ss(1.0f),0x44);
		v1=_mm_mul_ps(v1,v1);
		v1=_mm_shuffle_ps(_mm_mul_ss(v1,v4),v1,0x44);
		v1=_mm_shuffle_ps(v1,v4,0x88);
		__m128 v2;
		*(__m128i*)&v2=_mm_lddqu_si128((const __m128i *)a);
		v1=_mm_dp_ps(v1,v2,0xF1);
		v1=_mm_mul_ss(v1,_mm_set_ss(d));
		_mm_store_ss(b,v1);
	}

	void _APICALL _DSplineCRSSE4(double *a,double *b,double c,double d)
	{
		__m128d v1=_mm_set_sd(c);
		__m128d v4=_mm_shuffle_pd(v1,_mm_set_sd(1.0),0);
		v1=_mm_mul_sd(v1,v1);
		v1=_mm_shuffle_pd(v1,v1,0);
		__m128d v2;
		__m128d v3;
		v1=_mm_mul_sd(v1,v4);
		*(__m128i*)&v2=_mm_lddqu_si128((const __m128i *)a);
		*(__m128i*)&v3=_mm_lddqu_si128((const __m128i *)(a+2));
		v1=_mm_add_sd(_mm_dp_pd(v1,v2,0x31),_mm_dp_pd(v4,v3,0x31));
		v1=_mm_mul_sd(v1,_mm_set_sd(d));
		_mm_store_sd(b,v1);
	}

// ******************************* Exp SSE4 (dpps is low perfomance) *******************************

/*float _STDCALL _FExpSSE4(float _a)
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
	v1=_mm_add_ss(v1,_mm_dp_ps(v2,_mm_load_ps(fastsindividef),0xF1));
	v1=_mm_add_ss(v1,_mm_dp_ps(v4,_mm_load_ps(fastsindividef+4),0xF1));
	v2=_mm_mul_ps(v2,v3);
	v4=_mm_mul_ps(v4,v3);
	v1=_mm_add_ss(v1,_mm_dp_ps(v2,_mm_load_ps(fastsindividef+8),0xF1));
	v1=_mm_add_ss(v1,_mm_dp_ps(v4,_mm_load_ps(fastsindividef+12),0xF1));
	return v1.m128_f32[0];
}

double _STDCALL _DExpSSE4(double _a)
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
	v1=_mm_add_sd(v1,_mm_dp_pd(v2,_mm_load_pd(fastsindivided),0x31));
	v1=_mm_add_sd(v1,_mm_dp_pd(v4,_mm_load_pd(fastsindivided+2),0x31));
	v2=_mm_mul_pd(v2,v3);
	v4=_mm_mul_pd(v4,v3);
	v1=_mm_add_sd(v1,_mm_dp_pd(v2,_mm_load_pd(fastsindivided+4),0x31));
	v1=_mm_add_sd(v1,_mm_dp_pd(v4,_mm_load_pd(fastsindivided+6),0x31));
	v2=_mm_mul_pd(v2,v3);
	v4=_mm_mul_pd(v4,v3);
	v1=_mm_add_sd(v1,_mm_dp_pd(v2,_mm_load_pd(fastsindivided+8),0x31));
	v1=_mm_add_sd(v1,_mm_dp_pd(v4,_mm_load_pd(fastsindivided+10),0x31));
	v2=_mm_mul_pd(v2,v3);
	v4=_mm_mul_pd(v4,v3);
	v1=_mm_add_sd(v1,_mm_dp_pd(v2,_mm_load_pd(fastsindivided+12),0x31));
	v1=_mm_add_sd(v1,_mm_dp_pd(v4,_mm_load_pd(fastsindivided+14),0x31));
	return v1.m128d_f64[0];
}*/

// ******************************* Log2 SSE4 *******************************

_ALIGN _int64 logt[30]={0x000FFFFFFFFFFFFF,0,0x3F60000000000000,0,0x0010000000000000,0,0x7fefffffffffffff,0,0x3ff7100000000000,0,0xfffffffffc000000,0,0xbfb563d0fce18810,0,0x3fc48dead300e7bf,0,0xbf9b743ca0b38eeb,0,0x3fa7be52039fb7ce,0,0xbfd6386b9b9b5d42,0,0x3f4d4c6d2bc5aea6,0,0xC08FF48046FEE800,0,0xBD23FABE48CF933C};

double _NAKED _FASTCALL _DsLog2SSE4(double *,double )
{
_BEGIN_ASM
ASM( movsd       xmm0,xmmword ptr [esp+4]  )
ASM( movsd       xmm7,xmmword ptr [ecx]  )
ASM( andpd      xmm7,xmm0  )
ASM( orpd       xmm7,xmmword ptr [ecx+0x10]  )   // unsigned _int64 a1=((*(unsigned _int64*)&_a) & 0x000FFFFFFFFFFFFF) | 0x3F60000000000000
ASM( CVTSD2SS   xmm1,xmm7  )                     // double s2=(*(double*)&a1);
ASM( rcpss      xmm6,xmm1  )
ASM( CVTSS2SD   xmm1,xmm6  )                      // double s1=(double)(1.0f/(float)s2);
ASM( movsd     xmm4,xmmword ptr [ecx+0x40]  )
ASM( mulsd      xmm1,xmm4  )                      // s1=s1*1.44140625;
ASM( movsd      xmm2,xmmword ptr [ecx+0x50]  )
ASM( andpd      xmm2,xmm7  )                      // unsigned _int64 a2=(a1 & 0xfffffffffc000000);
ASM( movsd      xmm6,xmm0  )                      // double s3=(*(double*)&a2);
ASM( psrlq      xmm6,52  )
ASM( roundsd    xmm1,xmm1,0  )
ASM( subsd      xmm7,xmm2  )                    // s2-=s3;
ASM( mulsd      xmm2,xmm1  )                    // s1=round(s1);
ASM( mulsd      xmm7,xmm1  )                    // s2=s2*s1;
ASM( subsd      xmm2,xmm4  )                    // s3=s3*s1-1.44140625;
ASM( cvtdq2pd   xmm5,xmm6  )                    // double s4=(*(unsigned _int64*)&_a) >> 52;
ASM( addsd      xmm2,xmm7  )                    // s3=s3+s2;                                                  //-6.1211352864417321E-004
ASM( psrlq      xmm1,27h  )                     // int tableId=((*(unsigned _int64*)&s1) >> 39)-0x0080ee20;
//ASM( movd       edx,xmm1  )
ASM( movsd      xmm7,xmmword ptr [ecx+0x60]  )
ASM( mulsd      xmm7,xmm2  )
ASM( addsd      xmm7,xmmword ptr [ecx+0x70]  )   // s2=s3*(-0.0835543267617)+0.160580971746;           //+1.6063211647934578E-001
ASM( movsd      xmm6,xmmword ptr [ecx+0xC0]  )  // table low
ASM( addsd      xmm6,xmm5  )  
ASM( movsd      xmm5,xmmword ptr [ecx+0x80]  )                     // s4=s4+table[tableId*2];
ASM( mulsd      xmm5,xmm2  )                  // double s5=s3*(-0.0268105958065)+0.0463739041733;
ASM( movsd      xmm3,xmm2  )
ASM( mulsd      xmm3,xmm2  )
ASM( addsd      xmm5,xmmword ptr [ecx+0x90]  )
ASM( movsd      xmm0,xmmword ptr [ecx+0xA0]  )
ASM( mulsd      xmm0,xmm2  )
ASM( mulsd      xmm5,xmm3  )
ASM( addsd      xmm5,xmm7  )                    
ASM( mulsd      xmm3,xmm5  )                     // s5=(s5*(s3*s3)+s2)*s3*s3;            //+6.0186125305587197E-008
ASM( movsd      xmm5,xmmword ptr [ecx+0xD0]  ) // table hi
ASM( addsd      xmm0,xmmword ptr [ecx+0xB0]  )  // double s6=s3*(-0.347193624458)+0.000894120508332;
ASM( movsd      xmm4,xmm6  )
ASM( addsd      xmm4,xmm2  )                    // sdouble s7=s4+s3;              //+4.3675247286749869E-001
ASM( addsd      xmm0,xmm3  )                    // s6=s6+s5;                      //+1.1067026090474958E-003
ASM( movsd      xmm3,xmm2  )
ASM( mulsd      xmm0,xmm2  )                    // s6=s6*s3;                      //-6.7742763918377551E-007
ASM( addsd      xmm4,xmm5  )                    // s7=s7+table[tableId*2+1];      //+4.3675247286746322E-001
ASM( addsd      xmm0,xmm4  )                    // rez=s6+s7+s3;
_LINE6( 0xF2,0x0F,0x11,0x44,0x24,0x04 )    /* movsd       mmword ptr [esp+4],xmm0  */ \
_LINE4( 0xDD,0x44,0x24,0x04 )              /* fld         qword ptr [esp+4]  */ \
_END_ASM
RET_2;
}

double _APICALL _DLog2SSE4(double _a)
{
	return _DsLog2SSE4((double*)logt,_a);
}

/*double _STDCALL _DLog2SSE4(double _a)
{
    double y,z,x=_a;
    y=(((((((
        +0.09008290449235264)*x
        -0.8232520933634452)*x
        +3.268347597049261)*x
        -7.395442213971012)*x
        +10.54199156531427)*x
        -9.979689072844229)*x
        +6.882403741291307)*x
        -2.584443170188027;
    z=_DExpDEF(-y);
    y-=1.0-x*z;
    z=_DExpDEF(-y);
    y-=1.0-x*z;
    return y*1.4426950408889634073599246810019;
}*/

};

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif
#endif
