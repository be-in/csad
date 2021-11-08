//=============================================================================
///**
// *  @file vector_abs.h
// *
// *  $Id: vector_add.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float absolute, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_VECTOR_ABS_H
#define GEN3_VECTOR_ABS_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** ABS STDCALL *********************************
// absolute vectors eax=[esp+4]-a void *, edx=[esp+8]-b void *

/// Абсолютное значение вектора, команды FPU
#define VECTORP2DABSFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )      /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )      /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xD9,0x00 )                /* fld         dword ptr [eax]  */ \
_LINE3( 0xD9,0x40,0x04 )           /* fld         dword ptr [eax+4]  */ \
_LINE2( 0xD9,0xE1 )                /* fabs  */ \
_LINE3( 0xD9,0x5A,0x04 )           /* fstp        dword ptr [edx+4h]  */ \
_LINE2( 0xD9,0xE1 )                /* fabs  */ \
_LINE2( 0xD9,0x1A )                /* fstp        dword ptr [edx]  */ \
_END_ASM

/// Абсолютное значение вектора, команды SSE2
#define VECTORP2DABSSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,0x7FFFFFFF ) \
ASM( movd xmm0,eax ) \
_LINE4( 0x8B,0x44,0x24,0x04 )      /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )      /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x50 )      /* shufps      xmm0,xmm0,0x50  */ \
_LINE3( 0x0F,0x12,0x20 )           /* movlps      xmm4,qword ptr [eax]  */ \
ASM( andps xmm0,xmm4 ) \
_LINE3( 0x0F,0x13,0x02 )           /* movlps      qword ptr [edx],xmm0  */ \
_END_ASM

/// Абсолютное значение вектора, команды FPU
#define VECTORP3DABSFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )      /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )      /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xD9,0x00 )                /* fld         dword ptr [eax]  */ \
_LINE3( 0xD9,0x40,0x04 )           /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x40,0x08 )           /* fld         dword ptr [eax+8]  */ \
_LINE2( 0xD9,0xE1 )                /* fabs  */ \
_LINE3( 0xD9,0x5A,0x08 )           /* fstp        dword ptr [edx+8h]  */ \
_LINE2( 0xD9,0xE1 )                /* fabs  */ \
_LINE3( 0xD9,0x5A,0x04 )           /* fstp        dword ptr [edx+4h]  */ \
_LINE2( 0xD9,0xE1 )                /* fabs  */ \
_LINE2( 0xD9,0x1A )                /* fstp        dword ptr [edx]  */ \
_END_ASM

/// Абсолютное значение вектора, команды SSE2
#define VECTORP3DABSSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,0x7FFFFFFF ) \
ASM( movd xmm4,eax ) \
_LINE4( 0x8B,0x44,0x24,0x04 )      /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )      /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0xC6,0xE4,0x04 )      /* shufps      xmm4,xmm4,0x04  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 ) /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x00 )           /* movhps      xmm0,qword ptr [eax]  */ \
ASM( andps xmm0,xmm4 ) \
_LINE3( 0x0F,0x17,0x02 )           /* movhps      qword ptr [edx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x42,0x08 ) /* movss       dword ptr [edx+8],xmm0  */ \
_END_ASM

/// Абсолютное значение вектора, команды FPU
#define VECTORP4DABSFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )      /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )      /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xD9,0x00 )                /* fld         dword ptr [eax]  */ \
_LINE3( 0xD9,0x40,0x04 )           /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x40,0x08 )           /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD9,0x40,0x0C )           /* fld         dword ptr [eax+Ch]  */ \
_LINE2( 0xD9,0xE1 )                /* fabs  */ \
_LINE3( 0xD9,0x5A,0x0C )           /* fstp        dword ptr [edx+Ch]  */ \
_LINE2( 0xD9,0xE1 )                /* fabs  */ \
_LINE3( 0xD9,0x5A,0x08 )           /* fstp        dword ptr [edx+8h]  */ \
_LINE2( 0xD9,0xE1 )                /* fabs  */ \
_LINE3( 0xD9,0x5A,0x04 )           /* fstp        dword ptr [edx+4h]  */ \
_LINE2( 0xD9,0xE1 )                /* fabs  */ \
_LINE2( 0xD9,0x1A )                /* fstp        dword ptr [edx]  */ \
_END_ASM

/// Абсолютное значение вектора, команды SSE2
#define VECTORP4DABSSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,0x7FFFFFFF ) \
ASM( movd xmm4,eax ) \
_LINE4( 0x8B,0x44,0x24,0x04 )      /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )      /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0xC6,0xE4,0x00 )      /* shufps      xmm4,xmm4,0x00  */ \
_LINE3( 0x0F,0x12,0x00 )           /* movlps      xmm0,qword ptr [eax]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )      /* movhps      xmm0,qword ptr [eax+8]  */ \
ASM( andps xmm0,xmm4 ) \
_LINE3( 0x0F,0x13,0x02 )           /* movlps      qword ptr [edx],xmm0  */ \
_LINE4( 0x0F,0x17,0x42,0x08 )      /* movhps      qword ptr [edx+8],xmm0 */ \
_END_ASM

/// Абсолютное значение вектора, команды SSE4
#define VECTORP4DABSSSE4_STD \
_BEGIN_ASM \
ASM( mov eax,0x7FFFFFFF ) \
ASM( movd xmm4,eax ) \
_LINE4( 0x8B,0x44,0x24,0x04 )      /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )      /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0xC6,0xE4,0x00 )      /* shufps      xmm4,xmm4,0x00  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )      /* lddqu       xmm0,xmmword ptr [eax]  */ \
ASM( andps xmm0,xmm4 ) \
_LINE4( 0x66,0x0F,0x11,0x02 )      /* movupd      xmmword ptr [edx],xmm0  */ \
_END_ASM

/// Абсолютное значение вектора, команды FPU
#define VECTORP2DDABSFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )      /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )      /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xDD,0x00 )                /* fld         qword ptr [eax]  */ \
_LINE3( 0xDD,0x40,0x08 )           /* fld         qword ptr [eax+8]  */ \
_LINE2( 0xD9,0xE1 )                /* fabs  */ \
_LINE3( 0xDD,0x5A,0x08 )           /* fstp        qword ptr [edx+8h]  */ \
_LINE2( 0xD9,0xE1 )                /* fabs  */ \
_LINE2( 0xDD,0x1A )                /* fstp        qword ptr [edx]  */ \
_END_ASM

/// Абсолютное значение вектора, команды SSE2
#define VECTORP2DDABSSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,0x80000000 ) \
ASM( movd xmm4,eax ) \
_LINE4( 0x8B,0x44,0x24,0x04 )      /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )      /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0xC6,0xE4,0x11 )      /* shufps      xmm4,xmm4,0x11  */ \
_LINE3( 0x0F,0x12,0x00 )           /* movlps      xmm0,qword ptr [eax]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )      /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE3( 0x0F,0x55,0xE0 )           /* andnps      xmm4,xmm0  */ \
_LINE3( 0x0F,0x13,0x22 )           /* movlps      qword ptr [edx],xmm4  */ \
_LINE4( 0x0F,0x17,0x62,0x08 )      /* movhps      qword ptr [edx+8],xmm4 */ \
_END_ASM

/// Абсолютное значение вектора, команды SSE4
#define VECTORP2DDABSSSE4_STD \
_BEGIN_ASM \
ASM( mov edx,0x80000000 ) \
ASM( movd xmm4,edx ) \
_LINE4( 0x8B,0x44,0x24,0x04 )      /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )      /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0xC6,0xE4,0x11 )      /* shufps      xmm4,xmm4,0x11  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )      /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE3( 0x0F,0x55,0xE0 )           /* andnps      xmm4,xmm0  */ \
_LINE4( 0x66,0x0F,0x11,0x22 )      /* movupd      xmmword ptr [edx],xmm4  */ \
_END_ASM

/// Абсолютное значение вектора, команды FPU
#define VECTORP3DDABSFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )      /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )      /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xDD,0x00 )                /* fld         qword ptr [eax]  */ \
_LINE3( 0xDD,0x40,0x08 )           /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDD,0x40,0x10 )           /* fld         qword ptr [eax+10h]  */ \
_LINE2( 0xD9,0xE1 )                /* fabs  */ \
_LINE3( 0xDD,0x5A,0x10 )           /* fstp        qword ptr [edx+10h]  */ \
_LINE2( 0xD9,0xE1 )                /* fabs  */ \
_LINE3( 0xDD,0x5A,0x08 )           /* fstp        qword ptr [edx+8h]  */ \
_LINE2( 0xD9,0xE1 )                /* fabs  */ \
_LINE2( 0xDD,0x1A )                /* fstp        qword ptr [edx]  */ \
_END_ASM

/// Абсолютное значение вектора, команды SSE2
#define VECTORP3DDABSSSE2_STD \
_BEGIN_ASM \
_LINE5( 0xB8,0x00,0x00,0x00,0x80 ) /* mov         eax,80000000h  */ \
_LINE4( 0x66,0x0F,0x6E,0xE0 )      /* movd        xmm4,eax  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )      /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )      /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0xC6,0xE4,0x11 )      /* shufps      xmm4,xmm4,0x11  */ \
_LINE3( 0x0F,0x12,0x00 )           /* movlps      xmm0,qword ptr [eax]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )      /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE3( 0x0F,0x28,0xEC )           /* movaps      xmm5,xmm4  */ \
_LINE4( 0x0F,0x12,0x48,0x10 )      /* movlps      xmm1,qword ptr [eax+16]  */ \
_LINE3( 0x0F,0x55,0xE0 )           /* andnps      xmm4,xmm0  */ \
_LINE3( 0x0F,0x55,0xE9 )           /* andnps      xmm5,xmm1  */ \
_LINE3( 0x0F,0x13,0x22 )           /* movlps      qword ptr [edx],xmm4  */ \
_LINE4( 0x0F,0x17,0x62,0x08 )      /* movhps      qword ptr [edx+8],xmm4 */ \
_LINE4( 0x0F,0x13,0x6A,0x10 )      /* movlps      qword ptr [edx+16],xmm5  */ \
_END_ASM

/// Абсолютное значение вектора, команды SSE4
#define VECTORP3DDABSSSE4_STD \
_BEGIN_ASM \
_LINE5( 0xB8,0x00,0x00,0x00,0x80 ) /* mov         eax,80000000h  */ \
_LINE4( 0x66,0x0F,0x6E,0xE0 )      /* movd        xmm4,eax  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )      /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )      /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0xC6,0xE4,0x11 )      /* shufps      xmm4,xmm4,0x11  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )      /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xEC )           /* movaps      xmm5,xmm4  */ \
_LINE4( 0x0F,0x12,0x48,0x10 )      /* movlps      xmm1,qword ptr [eax+16]  */ \
_LINE3( 0x0F,0x55,0xE0 )           /* andnps      xmm4,xmm0  */ \
_LINE3( 0x0F,0x55,0xE9 )           /* andnps      xmm5,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x22 )      /* movupd      xmmword ptr [edx],xmm4  */ \
_LINE4( 0x0F,0x13,0x6A,0x10 )      /* movlps      qword ptr [edx+16],xmm5  */ \
_END_ASM

/// Абсолютное значение вектора, команды FPU
#define VECTORP4DDABSFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )      /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )      /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xDD,0x00 )                /* fld         qword ptr [eax]  */ \
_LINE3( 0xDD,0x40,0x08 )           /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDD,0x40,0x10 )           /* fld         qword ptr [eax+10h]  */ \
_LINE3( 0xDD,0x40,0x18 )           /* fld         qword ptr [eax+18h]  */ \
_LINE2( 0xD9,0xE1 )                /* fabs  */ \
_LINE3( 0xDD,0x5A,0x18 )           /* fstp        qword ptr [edx+18h]  */ \
_LINE2( 0xD9,0xE1 )                /* fabs  */ \
_LINE3( 0xDD,0x5A,0x10 )           /* fstp        qword ptr [edx+10h]  */ \
_LINE2( 0xD9,0xE1 )                /* fabs  */ \
_LINE3( 0xDD,0x5A,0x08 )           /* fstp        qword ptr [edx+8h]  */ \
_LINE2( 0xD9,0xE1 )                /* fabs  */ \
_LINE2( 0xDD,0x1A )                /* fstp        qword ptr [edx]  */ \
_END_ASM

/// Абсолютное значение вектора, команды SSE2
#define VECTORP4DDABSSSE2_STD \
_BEGIN_ASM \
ASM( mov edx,0x80000000 ) \
ASM( movd xmm4,edx ) \
_LINE4( 0x8B,0x44,0x24,0x04 )      /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )      /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0xC6,0xE4,0x11 )      /* shufps      xmm4,xmm4,0x11  */ \
_LINE3( 0x0F,0x12,0x00 )           /* movlps      xmm0,qword ptr [eax]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )      /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE3( 0x0F,0x28,0xEC )           /* movaps      xmm5,xmm4  */ \
_LINE4( 0x0F,0x12,0x48,0x10 )      /* movlps      xmm1,qword ptr [eax+16]  */ \
_LINE4( 0x0F,0x16,0x48,0x18 )      /* movhps      xmm1,qword ptr [eax+24]  */ \
_LINE3( 0x0F,0x55,0xE0 )           /* andnps      xmm4,xmm0  */ \
_LINE3( 0x0F,0x55,0xE9 )           /* andnps      xmm5,xmm1  */ \
_LINE3( 0x0F,0x13,0x22 )           /* movlps      qword ptr [edx],xmm4  */ \
_LINE4( 0x0F,0x17,0x62,0x08 )      /* movhps      qword ptr [edx+8],xmm4 */ \
_LINE4( 0x0F,0x13,0x6A,0x10 )      /* movlps      qword ptr [edx+16],xmm5  */ \
_LINE4( 0x0F,0x17,0x6A,0x18 )      /* movhps      qword ptr [edx+24],xmm5 */ \
_END_ASM

/// Абсолютное значение вектора, команды SSE4
#define VECTORP4DDABSSSE4_STD \
_BEGIN_ASM \
ASM( mov edx,0x80000000 ) \
ASM( movd xmm4,edx ) \
_LINE4( 0x8B,0x44,0x24,0x04 )      /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )      /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0xC6,0xE4,0x11 )      /* shufps      xmm4,xmm4,0x11  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )      /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xEC )           /* movaps      xmm5,xmm4  */ \
_LINE5( 0xF2,0x0F,0xF0,0x48,0x10 ) /* lddqu       xmm1,xmmword ptr [eax+10h]  */ \
_LINE3( 0x0F,0x55,0xE0 )           /* andnps      xmm4,xmm0  */ \
_LINE3( 0x0F,0x55,0xE9 )           /* andnps      xmm5,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x22 )      /* movupd      xmmword ptr [edx],xmm4  */ \
_LINE5( 0x66,0x0F,0x11,0x6A,0x10 ) /* movupd      xmmword ptr [edx+10h],xmm5  */ \
_END_ASM

#endif
