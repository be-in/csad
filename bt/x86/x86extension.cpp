/*
 * x86extension.cpp
 *
 *  Created on: 18.09.2013
 *      Author: Пантелеймонов Александр
 */

#ifdef CPU_BT

#include "x86extension.h"
#include "macrosasm.h"
#include "x86vector_bl.h"
#include "../base/baseext.h"

WARNING_DISABLE;
OPTIMIZE_ON;

#ifdef CPU_X86_32

namespace bt {

int _NAKED _APICALL _ILogSizeCPU(unsigned int)
{
_BEGIN_ASM
ASM( mov eax,1 ) \
_LINE4( 0x29,0x44,0x24,0x04 )          /* sub         dword ptr [esp+4],eax  */ \
_LINE2( 0x7F,0x03 )                    /* jg          eee1 (12F2406h)  */ \
_LINE3( 0xC2,0x04,0x00 )               /* ret         4  */ \
ASM( bsr ecx,[esp+4] ) \
_LINE5( 0xB8,0x02,0x00,0x00,0x00 )     /* mov         eax,2  */ \
_LINE2( 0xD3,0xE0 )                    /* shl         eax,cl  */ \
_END_ASM
RET_1;
}

int _NAKED _APICALL _ILogSizeFPU(unsigned int)
{
_BEGIN_ASM
_LINE5( 0xB8,0x01,0x00,0x00,0x00 )     /* mov         eax,1  */ \
_LINE4( 0x29,0x44,0x24,0x04 )          /* sub         dword ptr [esp+4],eax  */ \
_LINE2( 0x7F,0x03 )                    /* jg          eee1 (12F2406h)  */ \
_LINE3( 0xC2,0x04,0x00 )               /* ret         4  */ \
_LINE4( 0xDB,0x44,0x24,0x04 )          /* fild        dword ptr [esp+4]  */ \
_LINE4( 0xDD,0x5C,0x24,0xF4 )          /* fstp        qword ptr [esp-0Ch]  */ \
_LINE5( 0x66,0x8B,0x4C,0x24,0xFA )     /* mov         cx,word ptr [esp-6]  */ \
_LINE4( 0x66,0xC1,0xE9,0x04 )          /* shr         cx,4  */ \
_LINE5( 0xB8,0x02,0x00,0x00,0x00 )     /* mov         eax,2  */ \
_LINE5( 0x66,0x81,0xE1,0xFF,0x07 )     /* and         cx,7FFh  */ \
_LINE5( 0x66,0x81,0xE9,0xFF,0x03 )     /* sub         cx,3FFh  */ \
_LINE2( 0xD3,0xE0 )                    /* shl         eax,cl  */ \
_END_ASM
RET_1;
}

void _NAKED _APICALL _V3FToBLHFPU(float *,float *)
{
	VECTORP3DTOBLHFPU_STD;
	RET_2;
}

void _NAKED _APICALL _V3DToBLHFPU(double *,double *)
{
	VECTORP3DDTOBLHFPU_STD;
	RET_2;
}

void _NAKED _APICALL _V3FToBLFPU(float *,float *,float *)
{
	VECTORP3DTOBLFPU_STD;
	RET_3;
}

void _NAKED _APICALL _V3DToBLFPU(double *,double *,double *)
{
	VECTORP3DDTOBLFPU_STD;
	RET_3;
}

int _NAKED _APICALL _ILogSizeSSE2(unsigned int)
{
_BEGIN_ASM
_LINE5( 0xB8,0x01,0x00,0x00,0x00 )     /* mov         eax,1  */ \
_LINE4( 0x29,0x44,0x24,0x04 )          /* sub         dword ptr [esp+4],eax  */ \
_LINE2( 0x7F,0x03 )                    /* jg          eee1 (12F2406h)  */ \
_LINE3( 0xC2,0x04,0x00 )               /* ret         4  */ \
ASM( cvtsi2sd    xmm0,dword ptr [esp+4] ) \
ASM( psllq    xmm0,1 ) \
_LINE5( 0xB8,0x02,0x00,0x00,0x00 )     /* mov         eax,2  */ \
ASM( psrlq    xmm0,53 ) \
ASM( movd    ecx,xmm0 ) \
_LINE5( 0x66,0x81,0xE9,0xFF,0x03 )     /* sub         cx,3FFh  */ \
_LINE2( 0xD3,0xE0 )                    /* shl         eax,cl  */ \
_END_ASM
RET_1;
}

// ************** Noise SSE2 *******************

double NoiseGetVals[]={0.33333333333333333333333333333333,4.656612875245796924105750827168e-10};

_int32 _NAKED _FASTCALL SUB_NoiseGetSSE2(unsigned _int32 *,double *) //???
{
	//NOISEGETSSE_FAST
	_BEGIN_ASM \
	ASM( movsd xmm2,[edx+8] ) \
	ASM( mov eax,[ecx+0x44] ) \
	ASM( movsd xmm1,[edx] ) \
	ASM( mov edx,eax ) \
	ASM( and eax,0xF ) \
	ASM( cvtsi2sd xmm5,eax ) \
	ASM( mov eax,[ecx+eax*4] ) \
	ASM( mov [ecx+0x44],eax ) \
	ASM( cvtsi2sd xmm4,eax ) \
	ASM( shr edx,6 ) \
	ASM( cvtsi2sd xmm0,edx ) \
	ASM( mulsd xmm1,xmm0 ) \
	ASM( cvttsd2si eax,xmm1 ) \
	ASM( lea eax,[eax+eax*2] ) \
	ASM( sub edx,eax ) \
	ASM( add edx,18 ) \
	ASM( cvtsi2sd xmm3,dword ptr [ecx+edx*4] ) \
	ASM( cvtsi2sd xmm0,dword ptr [ecx+0x40] ) \
	ASM( mulsd xmm3,xmm4 ) \
	ASM( addsd xmm0,xmm3 ) \
	ASM( cvttsd2si eax,xmm0 ) \
	ASM( cvtsi2sd xmm0,eax ) \
	ASM( mulsd xmm2,xmm0 ) \
	ASM( cvttsd2si eax,xmm2 ) \
	ASM( mov edx,eax ) \
	ASM( shl eax,31 ) \
	ASM( sub eax,edx ) \
	ASM( cvttsd2si edx,xmm0 ) \
	ASM( sub edx,eax ) \
	ASM( cvttsd2si eax,xmm5 ) \
	ASM( and eax,0xF ) \
	ASM( mov [ecx+eax*4],edx ) \
	ASM( mov eax,[ecx+0x44] ) \
	_END_ASM
	RET;
}

_int32 _APICALL _NoiseGetSSE2()
{
	return SUB_NoiseGetSSE2(Noigen,NoiseGetVals);
}

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif
#endif