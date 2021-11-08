/*
 * x86matrix.cpp
 *
 *  Created on: 03.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifdef CPU_BT

#include "x86matrix.h"

#ifdef CPU_X86_32

#include "x86vector_to.h"
#include "x86math.h"
#include "x86matrix_transpose.h"
#include "x86matrix_mul.h"
#include "x86matrix_trs.h"
#include "x86matrix_addtranslate.h"
#include "x86matrix_addscale.h"
#include "x86matrix_addrotate.h"
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

void _NAKED _APICALL _M4DTranslateCPU(void *,double *)
{
	BEGIN_ASM \
	_LINE2( 0x33,0xC0 )                    /* xor         eax,eax  */ \
	_LINE2( 0x8B,0xD7 )                    /* mov         edx,edi  */ \
	_LINE4( 0x8B,0x7C,0x24,0x04 )          /* mov         edi,dword ptr [esp+4]  */ \
	_LINE5( 0xB9,0x20,0x00,0x00,0x00 )     /* mov         ecx,20h  */ \
	_LINE2( 0xF3,0xAB )                    /* rep stos    dword ptr es:[edi]  */ \
	_LINE4( 0x8B,0x7C,0x24,0x04 )          /* mov         edi,dword ptr [esp+4]  */ \
	_LINE5( 0xB8,0x00,0x00,0xF0,0x3F )     /* mov         eax,3FF00000h  */ \
	_LINE3( 0x89,0x47,0x04 )               /* mov         dword ptr [edi+4],eax  */ \
	_LINE3( 0x89,0x47,0x2C )               /* mov         dword ptr [edi+2Ch],eax  */ \
	_LINE3( 0x89,0x47,0x54 )               /* mov         dword ptr [edi+54h],eax  */ \
	_LINE3( 0x89,0x47,0x7C )               /* mov         dword ptr [edi+7Ch],eax  */ \
	_LINE2( 0x8B,0xC6 )                    /* mov         eax,esi  */ \
	_LINE4( 0x8B,0x74,0x24,0x08 )          /* mov         esi,dword ptr [esp+8]  */ \
	_LINE3( 0x83,0xC7,0x60 )               /* add         edi,60h  */ \
	_LINE5( 0xB9,0x06,0x00,0x00,0x00 )     /* mov         ecx,6  */ \
	_LINE2( 0xF3,0xA5 )                    /* rep movs    dword ptr es:[edi],dword ptr [esi]  */ \
	_LINE2( 0x8B,0xFA )                    /* mov         edi,edx  */ \
	_LINE2( 0x8B,0xF0 )                    /* mov         esi,eax  */ \
	END_ASM
	RET_2;
}

void _NAKED _APICALL _M4DScaleCPU(void *,double *)
{
	BEGIN_ASM \
	_LINE2( 0x33,0xC0 )                    /* xor         eax,eax  */ \
	_LINE2( 0x8B,0xD7 )                    /* mov         edx,edi  */ \
	_LINE4( 0x8B,0x7C,0x24,0x04 )          /* mov         edi,dword ptr [esp+4]  */ \
	_LINE5( 0xB9,0x20,0x00,0x00,0x00 )     /* mov         ecx,20h  */ \
	_LINE2( 0xF3,0xAB )                    /* rep stos    dword ptr es:[edi]  */ \
	_LINE4( 0x8B,0x7C,0x24,0x04 )          /* mov         edi,dword ptr [esp+4]  */ \
	_LINE5( 0xB8,0x00,0x00,0xF0,0x3F )     /* mov         eax,3FF00000h  */ \
	_LINE3( 0x89,0x47,0x7C )               /* mov         dword ptr [edi+7Ch],eax  */ \
	_LINE2( 0x8B,0xC6 )                    /* mov         eax,esi  */ \
	_LINE4( 0x8B,0x74,0x24,0x08 )          /* mov         esi,dword ptr [esp+8]  */ \
	_LINE5( 0xB9,0x02,0x00,0x00,0x00 )     /* mov         ecx,2  */ \
	_LINE2( 0xF3,0xA5 )                    /* rep movs    dword ptr es:[edi],dword ptr [esi]  */ \
	_LINE3( 0x83,0xC7,0x20 )               /* add         edi,20h  */ \
	_LINE5( 0xB9,0x02,0x00,0x00,0x00 )     /* mov         ecx,2  */ \
	_LINE2( 0xF3,0xA5 )                    /* rep movs    dword ptr es:[edi],dword ptr [esi]  */ \
	_LINE3( 0x83,0xC7,0x20 )               /* add         edi,20h  */ \
	_LINE5( 0xB9,0x02,0x00,0x00,0x00 )     /* mov         ecx,2  */ \
	_LINE2( 0xF3,0xA5 )                    /* rep movs    dword ptr es:[edi],dword ptr [esi]  */ \
	_LINE2( 0x8B,0xFA )                    /* mov         edi,edx  */ \
	_LINE2( 0x8B,0xF0 )                    /* mov         esi,eax  */ \
	END_ASM
	RET_2;
}

void _NAKED _APICALL _M4DTRSFPU(void *,double *,double *,double*)
{
	MATRIXP4DDTRSFPU_STD;
	RET_4;
}

void _NAKED _APICALL _M4FMulSSE(void *,void *,void *)
{
	MATRIXP4DMULSSE_STD;
	RET_3;
}

void _APICALL _M4FPerspectiveSSE(void *_m,int _w,int _h,float _aend,float _astart,float _fov)
{
	float tbrl[2];

	float f=(float)(_fov*PI360);
	_FSinCosSSE(f,&tbrl[0],&tbrl[1]);
	f=tbrl[1]/tbrl[0];
	if (_h>0) { tbrl[1]=(float)(_w*1.0/_h); } else tbrl[1]=(float)(_w);

	float *_matrix=(float *)_m;
	__m128 v0 = _mm_setzero_ps();
	__m128 v1 = _mm_set_ps(-(_aend+_astart),-2.0*_aend*_astart,1.0,1.0);
	__m128 v2 = _mm_set_ps((_aend-_astart),(_aend-_astart),f,f);
	v2 = _mm_mul_ss(v2,_mm_set_ss(tbrl[1]));
	v1 = _mm_div_ps(v1,v2);
	_mm_storel_pi((__m64*)_matrix,v0);
	_mm_storeh_pi((__m64*)(_matrix+2),v0);
	_mm_storel_pi((__m64*)(_matrix+4),v0);
	_mm_storeh_pi((__m64*)(_matrix+6),v0);
	_mm_storel_pi((__m64*)(_matrix+8),v0);
	_mm_storeh_pi((__m64*)(_matrix+10),v0);
	_mm_storel_pi((__m64*)(_matrix+12),v0);
	_mm_storeh_pi((__m64*)(_matrix+14),v0);
	_mm_store_ss(_matrix,v1);
	v2 = _mm_movehl_ps(v2,v1);
	v1 = _mm_shuffle_ps(v1,v1,0x01);
	_mm_store_ss(_matrix+14,v2);
	_mm_store_ss(_matrix+5,v1);
	v2 = _mm_shuffle_ps(v2,v2,0x01);
	_mm_store_ss(_matrix+10,v2);
	_matrix[11]=-1.0f;
}

void _APICALL _M4FOrtographicSSE(void *_m,int _w,int _h,float _aend,float _astart,float _scale)
{
	float tbrl;

	if (_h>0) { tbrl=(float)(_w*1.0/_h); } else tbrl=(float)(_w);

	float *_matrix=(float *)_m;
	__m128 v0 = _mm_setzero_ps();
	__m128 v1 = _mm_set_ps(-(_aend+_astart),-2.0,2.0,2.0);
	__m128 v2 = _mm_set_ps((_aend-_astart),(_aend-_astart),_scale,_scale);
	v2 = _mm_mul_ss(v2,_mm_set_ss(tbrl));
	v1 = _mm_div_ps(v1,v2);
	_mm_storel_pi((__m64*)_matrix,v0);
	_mm_storeh_pi((__m64*)(_matrix+2),v0);
	_mm_storel_pi((__m64*)(_matrix+4),v0);
	_mm_storeh_pi((__m64*)(_matrix+6),v0);
	_mm_storel_pi((__m64*)(_matrix+8),v0);
	_mm_storeh_pi((__m64*)(_matrix+10),v0);
	_mm_storel_pi((__m64*)(_matrix+12),v0);
	_mm_storeh_pi((__m64*)(_matrix+14),v0);
	_mm_store_ss(_matrix,v1);
	v2 = _mm_movehl_ps(v2,v1);
	v1 = _mm_shuffle_ps(v1,v1,0x01);
	_mm_store_ss(_matrix+10,v2);
	_mm_store_ss(_matrix+5,v1);
	v2 = _mm_shuffle_ps(v2,v2,0x01);
	_mm_store_ss(_matrix+14,v2);
	_matrix[15]=1.0f;
}

void _NAKED _APICALL _M4FIdentitySSE(void *)
{
	BEGIN_ASM \
	_LINE3( 0x0F,0x57,0xC0 )               /* xorps       xmm0,xmm0  */ \
	_LINE5( 0xB8,0x00,0x00,0x80,0x3F )     /* mov         eax,3F800000h  */ \
	_LINE4( 0x8B,0x54,0x24,0x04 )          /* mov         edx,dword ptr [esp+4]  */ \
	_LINE3( 0x0F,0x13,0x02 )               /* movlps      qword ptr [edx],xmm0  */ \
	_LINE4( 0x0F,0x17,0x42,0x08 )          /* movhps      qword ptr [edx+08h],xmm0  */ \
	_LINE4( 0x0F,0x13,0x42,0x10 )          /* movlps      qword ptr [edx+10h],xmm0  */ \
	_LINE4( 0x0F,0x17,0x42,0x18 )          /* movhps      qword ptr [edx+18h],xmm0  */ \
	_LINE4( 0x0F,0x13,0x42,0x20 )          /* movlps      qword ptr [edx+20h],xmm0  */ \
	_LINE4( 0x0F,0x17,0x42,0x28 )          /* movhps      qword ptr [edx+28h],xmm0  */ \
	_LINE4( 0x0F,0x13,0x42,0x30 )          /* movlps      qword ptr [edx+30h],xmm0  */ \
	_LINE4( 0x0F,0x17,0x42,0x38 )          /* movhps      qword ptr [edx+38h],xmm0  */ \
	_LINE2( 0x89,0x02 )                    /* mov         dword ptr [edx],eax  */ \
	_LINE3( 0x89,0x42,0x14 )               /* mov         dword ptr [edx+14h],eax  */ \
	_LINE3( 0x89,0x42,0x28 )               /* mov         dword ptr [edx+28h],eax  */ \
	_LINE3( 0x89,0x42,0x3C )               /* mov         dword ptr [edx+3Ch],eax  */ \
	END_ASM
	RET_1;
}

void _NAKED _APICALL _M4DIdentitySSE(void *)
{
	BEGIN_ASM \
	_LINE3( 0x0F,0x57,0xC0 )               /* xorps       xmm0,xmm0  */ \
	_LINE5( 0xB8,0x00,0x00,0xF0,0x3F )     /* mov         eax,3FF00000h  */ \
	_LINE4( 0x8B,0x54,0x24,0x04 )          /* mov         edx,dword ptr [esp+4]  */ \
	_LINE3( 0x0F,0x13,0x02 )               /* movlps      qword ptr [edx],xmm0  */ \
	_LINE4( 0x0F,0x17,0x42,0x08 )          /* movhps      qword ptr [edx+08h],xmm0  */ \
	_LINE4( 0x0F,0x13,0x42,0x10 )          /* movlps      qword ptr [edx+10h],xmm0  */ \
	_LINE4( 0x0F,0x17,0x42,0x18 )          /* movhps      qword ptr [edx+18h],xmm0  */ \
	_LINE4( 0x0F,0x13,0x42,0x20 )          /* movlps      qword ptr [edx+20h],xmm0  */ \
	_LINE4( 0x0F,0x17,0x42,0x28 )          /* movhps      qword ptr [edx+28h],xmm0  */ \
	_LINE4( 0x0F,0x13,0x42,0x30 )          /* movlps      qword ptr [edx+30h],xmm0  */ \
	_LINE4( 0x0F,0x17,0x42,0x38 )          /* movhps      qword ptr [edx+38h],xmm0  */ \
	_LINE4( 0x0F,0x13,0x42,0x40 )          /* movlps      qword ptr [edx+40h],xmm0  */ \
	_LINE4( 0x0F,0x17,0x42,0x48 )          /* movhps      qword ptr [edx+48h],xmm0  */ \
	_LINE4( 0x0F,0x13,0x42,0x50 )          /* movlps      qword ptr [edx+50h],xmm0  */ \
	_LINE4( 0x0F,0x17,0x42,0x58 )          /* movhps      qword ptr [edx+58h],xmm0  */ \
	_LINE4( 0x0F,0x13,0x42,0x60 )          /* movlps      qword ptr [edx+60h],xmm0  */ \
	_LINE4( 0x0F,0x17,0x42,0x68 )          /* movhps      qword ptr [edx+68h],xmm0  */ \
	_LINE4( 0x0F,0x13,0x42,0x70 )          /* movlps      qword ptr [edx+70h],xmm0  */ \
	_LINE4( 0x0F,0x17,0x42,0x78 )          /* movhps      qword ptr [edx+78h],xmm0  */ \
	_LINE3( 0x89,0x42,0x04 )               /* mov         dword ptr [edx+04h],eax  */ \
	_LINE3( 0x89,0x42,0x2C )               /* mov         dword ptr [edx+2Ch],eax  */ \
	_LINE3( 0x89,0x42,0x54 )               /* mov         dword ptr [edx+54h],eax  */ \
	_LINE3( 0x89,0x42,0x7C )               /* mov         dword ptr [edx+7Ch],eax  */ \
	END_ASM
	RET_1;
}

void _NAKED _APICALL _M4FTranslateSSE(void *,float *)
{
	BEGIN_ASM \
	_LINE3( 0x0F,0x57,0xC0 )               /* xorps       xmm0,xmm0  */ \
	_LINE5( 0xB8,0x00,0x00,0x80,0x3F )     /* mov         eax,3F800000h  */ \
	_LINE4( 0x8B,0x54,0x24,0x04 )          /* mov         edx,dword ptr [esp+4]  */ \
	_LINE4( 0x66,0x0F,0x11,0x02 )          /* movupd      xmmword ptr [edx],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x10 )     /* movupd      xmmword ptr [edx+10h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x20 )     /* movupd      xmmword ptr [edx+20h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x30 )     /* movupd      xmmword ptr [edx+30h],xmm0  */ \
	_LINE2( 0x89,0x02 )                    /* mov         dword ptr [edx],eax  */ \
	_LINE3( 0x89,0x42,0x14 )               /* mov         dword ptr [edx+14h],eax  */ \
	_LINE3( 0x89,0x42,0x28 )               /* mov         dword ptr [edx+28h],eax  */ \
	_LINE3( 0x89,0x42,0x3C )               /* mov         dword ptr [edx+3Ch],eax  */ \
	_LINE4( 0x8B,0x44,0x24,0x08 )          /* mov         eax,dword ptr [esp+8]  */ \
	_LINE5( 0xF3,0x0F,0x10,0x58,0x08 )     /* movss       xmm3,dword ptr [eax+8]  */ \
	_LINE3( 0x0F,0x12,0x08 )               /* movlps      xmm1,qword ptr [eax]  */ \
	_LINE4( 0x0F,0x13,0x4A,0x30 )          /* movlps      qword ptr [edx+30h],xmm1  */ \
	_LINE5( 0xF3,0x0F,0x11,0x5A,0x38 )     /* movss       dword ptr [edx+38h],xmm3  */ \
	END_ASM
	RET_2;
}

void _NAKED _APICALL _M4FScaleSSE(void *,float *)
{
	BEGIN_ASM \
	_LINE3( 0x0F,0x57,0xC0 )               /* xorps       xmm0,xmm0  */ \
	_LINE5( 0xB8,0x00,0x00,0x80,0x3F )     /* mov         eax,3F800000h  */ \
	_LINE4( 0x8B,0x54,0x24,0x04 )          /* mov         edx,dword ptr [esp+4]  */ \
	_LINE4( 0x66,0x0F,0x11,0x02 )          /* movupd      xmmword ptr [edx],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x10 )     /* movupd      xmmword ptr [edx+10h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x20 )     /* movupd      xmmword ptr [edx+20h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x30 )     /* movupd      xmmword ptr [edx+30h],xmm0  */ \
	_LINE3( 0x89,0x42,0x3C )               /* mov         dword ptr [edx+3Ch],eax  */ \
	_LINE4( 0x8B,0x44,0x24,0x08 )          /* mov         eax,dword ptr [esp+8]  */ \
	_LINE5( 0xF3,0x0F,0x10,0x58,0x08 )     /* movss       xmm3,dword ptr [eax+8]  */ \
	_LINE5( 0xF3,0x0F,0x10,0x50,0x04 )     /* movss       xmm2,dword ptr [eax+4]  */ \
	_LINE4( 0xF3,0x0F,0x10,0x08 )          /* movss       xmm1,dword ptr [eax]  */ \
	_LINE4( 0xF3,0x0F,0x11,0x0A )          /* movss       dword ptr [edx],xmm1  */ \
	_LINE5( 0xF3,0x0F,0x11,0x52,0x14 )     /* movss       dword ptr [edx+14h],xmm2  */ \
	_LINE5( 0xF3,0x0F,0x11,0x5A,0x28 )     /* movss       dword ptr [edx+28h],xmm3  */ \
	END_ASM
	RET_2;
}

void _NAKED _APICALL _M4FAddTranslateSSE(void *,float *,void *)
{
	MATRIXP4DADDTRANSLATESSE_STD;
	RET_3;
}

void _NAKED _APICALL _M4FAddScaleSSE(void *,float *,void *)
{
	MATRIXP4DADDSCALESSE_STD;
	RET_3;
}

void _NAKED _APICALL _M4FAddRotateSSE(void *,float *,void *)
{
	MATRIXP4DADDROTATESSE_STD;
	RET_3;
}

void _NAKED _APICALL _M4FTRSSSE(void *,float *,float *,float *)
{
	MATRIXP4DTRSSSE_STD;
	RET_4;
}

void _NAKED _APICALL _M4DMulSSE2(void *,void *,void *)
{
	MATRIXP4DDMULSSE2_STD;
	RET_3;
}

void _NAKED _APICALL _M4DScaleSSE2(void *,double *)
{
	BEGIN_ASM \
	_LINE3( 0x0F,0x57,0xC0 )               /* xorps       xmm0,xmm0  */ \
	_LINE5( 0xB8,0x00,0x00,0xF0,0x3F )     /* mov         eax,3FF00000h  */ \
	_LINE4( 0x8B,0x54,0x24,0x04 )          /* mov         edx,dword ptr [esp+4]  */ \
	_LINE4( 0x66,0x0F,0x11,0x02 )          /* movupd      xmmword ptr [edx],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x10 )     /* movupd      xmmword ptr [edx+10h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x20 )     /* movupd      xmmword ptr [edx+20h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x30 )     /* movupd      xmmword ptr [edx+30h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x40 )     /* movupd      xmmword ptr [edx+40h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x50 )     /* movupd      xmmword ptr [edx+50h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x60 )     /* movupd      xmmword ptr [edx+60h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x70 )     /* movupd      xmmword ptr [edx+70h],xmm0  */ \
	_LINE3( 0x89,0x42,0x7C )               /* mov         dword ptr [edx+7Ch],eax  */ \
	_LINE4( 0x8B,0x44,0x24,0x08 )          /* mov         eax,dword ptr [esp+8] */ \
	ASM( movsd xmm1,[eax] ) \
	ASM( movsd xmm2,[eax+0x8] ) \
	ASM( movsd xmm3,[eax+0x10] ) \
	ASM( movsd [edx],xmm1 ) \
	ASM( movsd [edx+0x28],xmm2 ) \
	ASM( movsd [edx+0x50],xmm3 ) \
	END_ASM
	RET_2;
}

void _APICALL _M4DPerspectiveSSE2(void *_m,int _w,int _h,double _aend,double _astart,double _fov)
{
	double tbrl[2];

	double f=_fov*PI360;
	_DSinCosSSE2(f,&tbrl[0],&tbrl[1]);
	f=tbrl[1]/tbrl[0];
	if (_h>0) { tbrl[1]=_w*1.0/_h; } else tbrl[1]=_w;
	tbrl[0]=f;
	tbrl[1]=f*tbrl[1];

	double *_matrix=(double *)_m;
	__m128 v0 = _mm_setzero_ps();
	_mm_storeh_pi((__m64*)(_matrix+1),v0);
	_mm_storel_pi((__m64*)(_matrix+2),v0);
	_mm_storeh_pi((__m64*)(_matrix+3),v0);
	_mm_storel_pi((__m64*)(_matrix+4),v0);
	_mm_storel_pi((__m64*)(_matrix+6),v0);
	_mm_storeh_pi((__m64*)(_matrix+7),v0);
	_mm_storel_pi((__m64*)(_matrix+8),v0);
	_mm_storeh_pi((__m64*)(_matrix+9),v0);
	_mm_storel_pi((__m64*)(_matrix+12),v0);
	_mm_storeh_pi((__m64*)(_matrix+13),v0);
	_mm_storeh_pi((__m64*)(_matrix+15),v0);
	_matrix[0]=1.0/tbrl[1];
	_matrix[5]=1.0/tbrl[0];
	_matrix[10]=-(_aend+_astart)/(_aend-_astart);
	_matrix[11]=-1.0;
	_matrix[14]=-2.0*_aend*_astart/(_aend-_astart);
}

void _APICALL _M4DOrtographicSSE2(void *_m,int _w,int _h,double _aend,double _astart,double _scale)
{
	double tbrl[2];

	if (_h>0) { tbrl[1]=(float)(_w*1.0/_h); } else tbrl[1]=(float)(_w);
	tbrl[0]=_scale;
	tbrl[1]=_scale*tbrl[1];

	double *_matrix=(double *)_m;
	__m128 v0 = _mm_setzero_ps();
	_mm_storeh_pi((__m64*)(_matrix+1),v0);
	_mm_storel_pi((__m64*)(_matrix+2),v0);
	_mm_storeh_pi((__m64*)(_matrix+3),v0);
	_mm_storel_pi((__m64*)(_matrix+4),v0);
	_mm_storel_pi((__m64*)(_matrix+6),v0);
	_mm_storeh_pi((__m64*)(_matrix+7),v0);
	_mm_storel_pi((__m64*)(_matrix+8),v0);
	_mm_storeh_pi((__m64*)(_matrix+9),v0);
	_mm_storel_pi((__m64*)(_matrix+11),v0);
	_mm_storel_pi((__m64*)(_matrix+12),v0);
	_mm_storeh_pi((__m64*)(_matrix+13),v0);
	_matrix[0]=2.0/tbrl[1];
	_matrix[5]=2.0/tbrl[0];
	_matrix[10]=-2.0/(_aend-_astart);
	_matrix[14]=-(_aend+_astart)/(_aend-_astart);
	_matrix[15]=1.0;
}

void _NAKED _APICALL _M4DToM4FSSE2(void *,void *)
{
	MATRIXP4DDTO4DSSE2_STD;
	RET_2;
}

void _NAKED _APICALL _M4FAddRotateSSE2(void *,float *,void *)
{
	MATRIXP4DADDROTATESSE2_STD;
	RET_3;
}

void _NAKED _APICALL _M4FMulSSE3(void *,void *,void *)
{
	MATRIXP4DMULSSE3_STD;
	RET_3;
}

void _NAKED _APICALL _M4FAddRotateSSE3(void *,float *,void *)
{
	MATRIXP4DADDROTATESSE3_STD;
	RET_3;
}

void _NAKED _APICALL _M4FTransposeSSE4(void *,void *)
{
	MATRIXP4DTRANSPOSESSE4_STD;
	RET_2;
}

void _NAKED _APICALL _M4FMulSSE4(void *,void *,void *)
{
	MATRIXP4DMULSSE4_STD;
	RET_3;
}

void _NAKED _APICALL _M4DMulSSE4(void *,void *,void *)
{
	MATRIXP4DDMULSSE4_STD;
	RET_3;
}

void _APICALL _M4FPerspectiveSSE4(void *_m,int _w,int _h,float _aend,float _astart,float _fov)
{
	float tbrl[2];

	float f=(float)(_fov*PI360);
	_FSinCosSSE(f,&tbrl[0],&tbrl[1]);
	f=tbrl[1]/tbrl[0];
	if (_h>0) { tbrl[1]=(float)(_w*1.0/_h); } else tbrl[1]=(float)(_w);

	float *_matrix=(float *)_m;
	__m128 v0 = _mm_setzero_ps();
	__m128 v1 = _mm_set_ps(-(_aend+_astart),-2.0*_aend*_astart,1.0,1.0);
	__m128 v2 = _mm_set_ps((_aend-_astart),(_aend-_astart),f,f);
	v2 = _mm_mul_ss(v2,_mm_set_ss(tbrl[1]));
	v1 = _mm_div_ps(v1,v2);
	_mm_storeu_ps(_matrix,v0);
	_mm_storeu_ps(_matrix+4,v0);
	_mm_storeu_ps(_matrix+8,v0);
	_mm_storeu_ps(_matrix+12,v0);
	_mm_store_ss(_matrix,v1);
	v2 = _mm_movehl_ps(v2,v1);
	v1 = _mm_shuffle_ps(v1,v1,0x01);
	_mm_store_ss(_matrix+14,v2);
	_mm_store_ss(_matrix+5,v1);
	v2 = _mm_shuffle_ps(v2,v2,0x01);
	_mm_store_ss(_matrix+10,v2);
	_matrix[11]=-1.0f;
}

void _APICALL _M4DPerspectiveSSE4(void *_m,int _w,int _h,double _aend,double _astart,double _fov)
{
	double tbrl[2];

	double f=_fov*PI360;
	_DSinCosSSE2(f,&tbrl[0],&tbrl[1]);
	f=tbrl[1]/tbrl[0];
	if (_h>0) { tbrl[1]=_w*1.0/_h; } else tbrl[1]=_w;
	tbrl[0]=f;
	tbrl[1]=f*tbrl[1];

	double *_matrix=(double *)_m;
	__m128d v0 = _mm_setzero_pd();
	_mm_storeu_pd(_matrix,v0);
	_mm_storeu_pd(_matrix+2,v0);
	_mm_storeu_pd(_matrix+4,v0);
	_mm_storeu_pd(_matrix+6,v0);
	_mm_storeu_pd(_matrix+8,v0);
	_mm_storeu_pd(_matrix+12,v0);
	_mm_storeu_pd(_matrix+14,v0);
	_matrix[0]=1.0/tbrl[1];
	_matrix[5]=1.0/tbrl[0];
	_matrix[10]=-(_aend+_astart)/(_aend-_astart);
	_matrix[11]=-1.0;
	_matrix[14]=-2.0*_aend*_astart/(_aend-_astart);
}

void _APICALL _M4FOrtographicSSE4(void *_m,int _w,int _h,float _aend,float _astart,float _scale)
{
	float tbrl;

	if (_h>0) { tbrl=(float)(_w*1.0/_h); } else tbrl=(float)(_w);

	float *_matrix=(float *)_m;
	__m128 v0 = _mm_setzero_ps();
	__m128 v1 = _mm_set_ps(-(_aend+_astart),-2.0,2.0,2.0);
	__m128 v2 = _mm_set_ps((_aend-_astart),(_aend-_astart),_scale,_scale);
	v2 = _mm_mul_ss(v2,_mm_set_ss(tbrl));
	v1 = _mm_div_ps(v1,v2);
	_mm_storeu_ps(_matrix,v0);
	_mm_storeu_ps(_matrix+4,v0);
	_mm_storeu_ps(_matrix+8,v0);
	_mm_storeu_ps(_matrix+12,v0);
	_mm_store_ss(_matrix,v1);
	v2 = _mm_movehl_ps(v2,v1);
	v1 = _mm_shuffle_ps(v1,v1,0x01);
	_mm_store_ss(_matrix+10,v2);
	_mm_store_ss(_matrix+5,v1);
	v2 = _mm_shuffle_ps(v2,v2,0x01);
	_mm_store_ss(_matrix+14,v2);
	_matrix[15]=1.0f;
}

void _APICALL _M4DOrtographicSSE4(void *_m,int _w,int _h,double _aend,double _astart,double _scale)
{
	double tbrl;

	if (_h>0) { tbrl=(float)(_w*1.0/_h); } else tbrl=(float)(_w);

	double *_matrix=(double *)_m;
	__m128d v0 = _mm_setzero_pd();
	__m128d v1 = _mm_set_sd(2.0);
	__m128d v2 = _mm_set_sd(_scale);
	v2 = _mm_mul_sd(_mm_shuffle_pd(v2,v2,0),_mm_set_sd(tbrl));
	v1 = _mm_div_pd(_mm_shuffle_pd(v1,v1,0),v2);
	_mm_storeu_pd(_matrix,v0);
	_mm_storeu_pd(_matrix+2,v0);
	_mm_storeu_pd(_matrix+4,v0);
	_mm_storeu_pd(_matrix+6,v0);
	_mm_storeu_pd(_matrix+8,v0);
	_mm_storeu_pd(_matrix+12,v0);
	_mm_storeu_pd(_matrix+14,v0);
	_mm_store_sd(_matrix,v1);
	_mm_storeh_pi((__m64*)(_matrix+5),*(__m128*)&v1);
	_matrix[10]=-2.0/(_aend-_astart);
	_matrix[14]=-(_aend+_astart)/(_aend-_astart);
	_matrix[15]=1.0;
}

void _NAKED _APICALL _M4FIdentitySSE4(void *)
{
	BEGIN_ASM \
	_LINE3( 0x0F,0x57,0xC0 )               /* xorps       xmm0,xmm0  */ \
	_LINE5( 0xB8,0x00,0x00,0x80,0x3F )     /* mov         eax,3F800000h  */ \
	_LINE4( 0x8B,0x54,0x24,0x04 )          /* mov         edx,dword ptr [esp+4]  */ \
	_LINE4( 0x66,0x0F,0x11,0x02 )          /* movupd      xmmword ptr [edx],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x10 )     /* movupd      xmmword ptr [edx+10h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x20 )     /* movupd      xmmword ptr [edx+20h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x30 )     /* movupd      xmmword ptr [edx+30h],xmm0  */ \
	_LINE2( 0x89,0x02 )                    /* mov         dword ptr [edx],eax  */ \
	_LINE3( 0x89,0x42,0x14 )               /* mov         dword ptr [edx+14h],eax  */ \
	_LINE3( 0x89,0x42,0x28 )               /* mov         dword ptr [edx+28h],eax  */ \
	_LINE3( 0x89,0x42,0x3C )               /* mov         dword ptr [edx+3Ch],eax  */ \
	END_ASM
	RET_1;
}

void _NAKED _APICALL _M4DIdentitySSE4(void *)
{
	BEGIN_ASM \
	_LINE3( 0x0F,0x57,0xC0 )               /* xorps       xmm0,xmm0  */ \
	_LINE5( 0xB8,0x00,0x00,0xF0,0x3F )     /* mov         eax,3FF00000h  */ \
	_LINE4( 0x8B,0x54,0x24,0x04 )          /* mov         edx,dword ptr [esp+4]  */ \
	_LINE4( 0x66,0x0F,0x11,0x02 )          /* movupd      xmmword ptr [edx],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x10 )     /* movupd      xmmword ptr [edx+10h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x20 )     /* movupd      xmmword ptr [edx+20h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x30 )     /* movupd      xmmword ptr [edx+30h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x40 )     /* movupd      xmmword ptr [edx+40h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x50 )     /* movupd      xmmword ptr [edx+50h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x60 )     /* movupd      xmmword ptr [edx+60h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x70 )     /* movupd      xmmword ptr [edx+70h],xmm0  */ \
	_LINE3( 0x89,0x42,0x04 )               /* mov         dword ptr [edx+04h],eax  */ \
	_LINE3( 0x89,0x42,0x2C )               /* mov         dword ptr [edx+2Ch],eax  */ \
	_LINE3( 0x89,0x42,0x54 )               /* mov         dword ptr [edx+54h],eax  */ \
	_LINE3( 0x89,0x42,0x7C )               /* mov         dword ptr [edx+7Ch],eax  */ \
	END_ASM
	RET_1;
}

void _NAKED _APICALL _M4DTranslateSSE4(void *,double *)
{
	BEGIN_ASM \
	_LINE3( 0x0F,0x57,0xC0 )               /* xorps       xmm0,xmm0  */ \
	_LINE5( 0xB8,0x00,0x00,0xF0,0x3F )     /* mov         eax,3FF00000h  */ \
	_LINE4( 0x8B,0x54,0x24,0x04 )          /* mov         edx,dword ptr [esp+4]  */ \
	_LINE4( 0x66,0x0F,0x11,0x02 )          /* movupd      xmmword ptr [edx],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x10 )     /* movupd      xmmword ptr [edx+10h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x20 )     /* movupd      xmmword ptr [edx+20h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x30 )     /* movupd      xmmword ptr [edx+30h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x40 )     /* movupd      xmmword ptr [edx+40h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x50 )     /* movupd      xmmword ptr [edx+50h],xmm0  */ \
	_LINE5( 0x66,0x0F,0x11,0x42,0x70 )     /* movupd      xmmword ptr [edx+70h],xmm0  */ \
	_LINE3( 0x89,0x42,0x04 )               /* mov         dword ptr [edx+04h],eax  */ \
	_LINE3( 0x89,0x42,0x2C )               /* mov         dword ptr [edx+2Ch],eax  */ \
	_LINE3( 0x89,0x42,0x54 )               /* mov         dword ptr [edx+54h],eax  */ \
	_LINE3( 0x89,0x42,0x7C )               /* mov         dword ptr [edx+7Ch],eax  */ \
	_LINE4( 0x8B,0x44,0x24,0x08 )          /* mov         eax,dword ptr [esp+8] */ \
	ASM( lddqu xmm1,[eax] ) \
	ASM( movsd xmm3,[eax+0x10] ) \
	ASM( movupd [edx+0x60],xmm1 ) \
	ASM( movsd [edx+0x70],xmm3 ) \
	END_ASM
	RET_2;
}

void _NAKED _APICALL _M4FAddTranslateSSE4(void *,float *,void *)
{
	MATRIXP4DADDTRANSLATESSE4_STD;
	RET_3;
}

void _NAKED _APICALL _M4DAddTranslateSSE4(void *,double *,void *)
{
	MATRIXP4DDADDTRANSLATESSE4_STD;
	RET_3;
}

void _NAKED _APICALL _M4FAddScaleSSE4(void *,float *,void *)
{
	MATRIXP4DADDSCALESSE4_STD
	RET_3;
}

void _NAKED _APICALL _M4FAddRotateSSE4(void *,float *,void *)
{
	MATRIXP4DADDROTATESSE4_STD;
	RET_3;
}

void _NAKED _APICALL _M4DAddRotateSSE4(void *,double *,void *)
{
	MATRIXP4DDADDROTATESSE4_STD;
	RET_3;
}

void _NAKED _APICALL _M4FTRSSSE4(void *,float *,float *,float *)
{
	MATRIXP4DTRSSSE4_STD;
	RET_4;
}

void _NAKED _APICALL _M4DTRSSSE4(void *,double *,double *,double *)
{
	MATRIXP4DDTRSSSE4_STD;
	RET_4;
}

#define _mm_shufd(v, i) _mm_shuffle_ps((v), (v), _MM_SHUFFLE((i), (i), (i), (i)))
#define fma(a,b,c) _mm_add_ps(_mm_mul_ps(a, b), c)

void _APICALL _M4FMulAVX(void * a,void * b,void * c)
{
	__m128 *mm=(__m128 *)c;
	__m128 *ma=(__m128 *)a;
	__m128 *mb=(__m128 *)b;
	mm[0] = fma(_mm_shufd(ma[0], 0), mb[0], fma(_mm_shufd(ma[0], 1), mb[1], _mm_add_ps(_mm_mul_ps(_mm_shufd(ma[0], 2), mb[2]), _mm_mul_ps(_mm_shufd(ma[0], 3), mb[3]))));
	mm[1] = fma(_mm_shufd(ma[1], 0), mb[0], fma(_mm_shufd(ma[1], 1), mb[1], _mm_add_ps(_mm_mul_ps(_mm_shufd(ma[1], 2), mb[2]), _mm_mul_ps(_mm_shufd(ma[1], 3), mb[3]))));
	mm[2] = fma(_mm_shufd(ma[2], 0), mb[0], fma(_mm_shufd(ma[2], 1), mb[1], _mm_add_ps(_mm_mul_ps(_mm_shufd(ma[2], 2), mb[2]), _mm_mul_ps(_mm_shufd(ma[2], 3), mb[3]))));
	mm[3] = fma(_mm_shufd(ma[3], 0), mb[0], fma(_mm_shufd(ma[3], 1), mb[1], _mm_add_ps(_mm_mul_ps(_mm_shufd(ma[3], 2), mb[2]), _mm_mul_ps(_mm_shufd(ma[3], 3), mb[3]))));

}

void _NAKED _APICALL _M4DMulAVX(void *,void *,void *)
{
	MATRIXP4DDMULAVX_STD;
	RET_3;
}

void _NAKED _APICALL _M4DTRSAVX(void *, double *, double *, double *)
{
	MATRIXP4DDTRSAVX_STD;
	RET_4;
}

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif
#endif

