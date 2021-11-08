//=============================================================================
///**
// *  @file   vector_normal.h
// *
// *  $Id: vector_normal.h 17.08.2011  $
// *
// *  @brief generator 3, MS Visual C++ 2003-2008
// *
// *  @author Panteleym_onov Aleks_andr Konstantino_vich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_VECTOR_NORMAL_H
#define GEN3_VECTOR_NORMAL_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** NORMAL STDCALL *********************************
// vector Normal [eax]-a void * [edx]-b void * rez

/// Нормализация двухмерного вектора одинарной точности, команды FPU
#define VECTORP2DNORMALFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xFA )                                         /* fsqrt             */ \
_LINE2( 0xD9,0xE8 )                                         /* fld1              */ \
_LINE2( 0xDE,0xF1 )                                         /* fdivrp      st(1),st  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE2( 0xD9,0x1A )                                         /* fstp        dword ptr [edx]  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x5A,0x04 )                                    /* fstp        dword ptr [edx+4]  */ \
_END_ASM

/// Нормализация двухмерного вектора одинарной точности, команды SSE
#define VECTORP2DNORMALSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
ASM( xorps xmm0,xmm0 ) \
_LINE3( 0x0F,0x12,0x00 )                                    /* movlps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x59,0xC9 )                                    /* mulps       xmm1,xmm1  */ \
_LINE3( 0x0F,0x28,0xD1 )                                    /* movaps      xmm2,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC9,0x01 )                               /* shufps      xmm1,xmm1,1  */ \
_LINE4( 0xF3,0x0F,0x58,0xD1 )                               /* addss       xmm2,xmm1  */ \
_LINE4( 0xF3,0x0F,0x51,0xD2 )                               /* sqrtss      xmm2,xmm2  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x5E,0xC2 )                                    /* divps       xmm0,xmm2  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8] */ \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
_END_ASM

/// Нормализация двухмерного вектора одинарной точности, команды SSE2
#define VECTORP2DNORMALSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
ASM( movsd xmm0,qword ptr [eax] ) \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x59,0xC9 )                                    /* mulps       xmm1,xmm1  */ \
_LINE3( 0x0F,0x28,0xD1 )                                    /* movaps      xmm2,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC9,0x01 )                               /* shufps      xmm1,xmm1,1  */ \
_LINE4( 0xF3,0x0F,0x58,0xD1 )                               /* addss       xmm2,xmm1  */ \
_LINE4( 0xF3,0x0F,0x51,0xD2 )                               /* sqrtss      xmm2,xmm2  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x5E,0xC2 )                                    /* divps       xmm0,xmm2  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8] */ \
ASM( movsd qword ptr [edx],xmm0 ) \
_END_ASM

/// Нормализация двухмерного вектора одинарной точности, команды SSE4
#define VECTORP2DNORMALSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
ASM( movsd xmm0,qword ptr [eax] ) \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC9,0x31 )                     /* dpps        xmm1,xmm1,31h  */ \
_LINE4( 0xF3,0x0F,0x51,0xC9 )                               /* sqrtss      xmm1,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x5E,0xC1 )                                    /* divps       xmm0,xmm1  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
ASM( movsd qword ptr [edx],xmm0 ) \
_END_ASM

/// Нормализация трехмерного вектора одинарной точности, команды FPU
#define VECTORP3DNORMALFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD8,0x48,0x08 )                                    /* fmul        dword ptr [eax+8]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xFA )                                         /* fsqrt             */ \
_LINE2( 0xD9,0xE8 )                                         /* fld1              */ \
_LINE2( 0xDE,0xF1 )                                         /* fdivrp      st(1),st  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE2( 0xD9,0x1A )                                         /* fstp        dword ptr [edx]  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x5A,0x04 )                                    /* fstp        dword ptr [edx+4]  */ \
_LINE3( 0xD8,0x48,0x08 )                                    /* fmul        dword ptr [eax+8]  */ \
_LINE3( 0xD9,0x5A,0x08 )                                    /* fstp        dword ptr [edx+8]  */ \
_END_ASM

/// Нормализация трехмерного вектора одинарной точности, команды SSE
#define VECTORP3DNORMALSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x00 )                                    /* movhps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x59,0xC9 )                                    /* mulps       xmm1,xmm1  */ \
_LINE3( 0x0F,0x28,0xD1 )                                    /* movaps      xmm2,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC9,0x0E )                               /* shufps      xmm1,xmm1,0Eh  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC9,0x01 )                               /* shufps      xmm1,xmm1,1  */ \
_LINE4( 0xF3,0x0F,0x58,0xD1 )                               /* addss       xmm2,xmm1  */ \
_LINE4( 0xF3,0x0F,0x51,0xD2 )                               /* sqrtss      xmm2,xmm2  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x5E,0xC2 )                                    /* divps       xmm0,xmm2  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8] */ \
_LINE3( 0x0F,0x17,0x02 )                                    /* movhps      qword ptr [edx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x42,0x08 )                          /* movss       dword ptr [edx+8],xmm0  */ \
_END_ASM

/// Нормализация трехмерного вектора одинарной точности, команды SSE4
#define VECTORP3DNORMALSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x00 )                                    /* movhps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC9,0xD1 )                     /* dpps        xmm1,xmm1,0D1h  */ \
_LINE4( 0xF3,0x0F,0x51,0xC9 )                               /* sqrtss      xmm1,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x5E,0xC1 )                                    /* divps       xmm0,xmm1  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8] */ \
_LINE3( 0x0F,0x17,0x02 )                                    /* movhps      qword ptr [edx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x42,0x08 )                          /* movss       dword ptr [edx+8],xmm0  */ \
_END_ASM

/// Нормализация четырехмерного вектора одинарной точности, команды FPU
#define VECTORP4DNORMALFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD8,0x48,0x08 )                                    /* fmul        dword ptr [eax+8]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x40,0x0C )                                    /* fld         dword ptr [eax+12]  */ \
_LINE3( 0xD8,0x48,0x0C )                                    /* fmul        dword ptr [eax+12]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xFA )                                         /* fsqrt             */ \
_LINE2( 0xD9,0xE8 )                                         /* fld1              */ \
_LINE2( 0xDE,0xF1 )                                         /* fdivrp      st(1),st  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE2( 0xD9,0x1A )                                         /* fstp        dword ptr [edx]  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x5A,0x04 )                                    /* fstp        dword ptr [edx+4]  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE3( 0xD8,0x48,0x08 )                                    /* fmul        dword ptr [eax+8]  */ \
_LINE3( 0xD9,0x5A,0x08 )                                    /* fstp        dword ptr [edx+8]  */ \
_LINE3( 0xD8,0x48,0x0C )                                    /* fmul        dword ptr [eax+12]  */ \
_LINE3( 0xD9,0x5A,0x0C )                                    /* fstp        dword ptr [edx+12]  */ \
_END_ASM

/// Нормализация четырехмерного вектора одинарной точности, команды SSE
#define VECTORP4DNORMALSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
ASM( xorps xmm0,xmm0 ) \
ASM( xorps xmm3,xmm3 ) \
_LINE4( 0x0F,0x12,0x58,0x08 )                               /* movlps      xmm3,qword ptr [eax+8]  */ \
_LINE3( 0x0F,0x12,0x00 )                                    /* movlps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x28,0xD3 )                                    /* movaps      xmm2,xmm3  */ \
_LINE3( 0x0F,0x59,0xC9 )                                    /* mulps       xmm1,xmm1  */ \
_LINE3( 0x0F,0x59,0xD2 )                                    /* mulps       xmm2,xmm2  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x28,0xCA )                                    /* movaps      xmm1,xmm2  */ \
_LINE4( 0x0F,0xC6,0xD2,0x01 )                               /* shufps      xmm1,xmm1,1  */ \
_LINE4( 0xF3,0x0F,0x58,0xD1 )                               /* addss       xmm2,xmm1  */ \
ASM( movlhps xmm0,xmm3 ) \
_LINE4( 0xF3,0x0F,0x51,0xD2 )                               /* sqrtss      xmm2,xmm2  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8] */ \
_LINE3( 0x0F,0x5E,0xC2 )                                    /* divps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
_LINE4( 0x0F,0x17,0x42,0x08 )                               /* movhps      qword ptr [edx+8],xmm0 */ \
_END_ASM

/// Нормализация четырехмерного вектора одинарной точности, команды SSE4
#define VECTORP4DNORMALSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC9,0xF1 )                     /* dpps        xmm1,xmm1,0F1h  */ \
_LINE4( 0xF3,0x0F,0x51,0xC9 )                               /* sqrtss      xmm1,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8] */ \
_LINE3( 0x0F,0x5E,0xC1 )                                    /* divps       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x02 )                               /* movupd      xmmword ptr [edx],xmm0  */ \
_END_ASM

/// Нормализация двухмерного вектора двойной точности, команды FPU
#define VECTORP2DDNORMALFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
 _STR(_DB(0xDD) _DB(0x00)) \
 _STR(_DB(0xDC) _DB(0x08)) \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8] */ \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x48) _DB(0x08)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xD9) _DB(0xFA)) \
 _STR(_DB(0xD9) _DB(0xE8)) \
 _STR(_DB(0xDE) _DB(0xF1)) \
 _STR(_DB(0xD9) _DB(0xC0)) \
 _STR(_DB(0xDC) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x1A)) \
 _STR(_DB(0xDC) _DB(0x48) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x5A) _DB(0x08)) \
_END_ASM

/// Нормализация двухмерного вектора двойной точности, команды SSE2
#define VECTORP2DDNORMALSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )                               /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xC9 )                               /* mulpd       xmm1,xmm1  */ \
_LINE3( 0x0F,0x12,0xD1 )                                    /* movhlps     xmm2,xmm1  */ \
_LINE4( 0xF2,0x0F,0x58,0xD1 )                               /* addsd       xmm2,xmm1  */ \
_LINE4( 0xF2,0x0F,0x51,0xD2 )                               /* sqrtsd      xmm2,xmm2  */ \
_LINE3( 0x0F,0x16,0xD2 )                                    /* movlhps     xmm2,xmm2  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x66,0x0F,0x5E,0xC2 )                               /* divpd       xmm0,xmm2  */ \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
_LINE4( 0x0F,0x17,0x42,0x08 )                               /* movhps      qword ptr [edx+8],xmm0  */ \
_END_ASM

/// Нормализация двухмерного вектора двойной точности, команды SSE4
#define VECTORP2DDNORMALSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
ASM( lddqu       xmm0,[eax] ) \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC9,0x31 )                     /* dppd        xmm1,xmm1,31h  */ \
_LINE4( 0xF2,0x0F,0x51,0xC9 )                               /* sqrtsd      xmm1,xmm1  */ \
_LINE5( 0xB8,0x01,0x00,0x00,0x00 )                          /* mov         eax,1  */ \
_LINE4( 0xF2,0x0F,0x2A,0xD0 )                               /* cvtsi2sd    xmm2,eax  */ \
_LINE4( 0xF2,0x0F,0x5E,0xD1 )                               /* divsd       xmm2,xmm1  */ \
_LINE3( 0x0F,0x16,0xD2 )                                    /* movlhps     xmm2,xmm2  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x66,0x0F,0x59,0xC2 )                               /* mulpd       xmm0,xmm2  */ \
ASM( movupd [edx],xmm0 ) \
_END_ASM

/// Нормализация трехмерного вектора двойной точности, команды SSE4
#define VECTORP3DDNORMALSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
ASM( lddqu xmm0,[eax] ) \
_LINE5( 0xF2,0x0F,0x10,0x68,0x10 )                          /* movsd       xmm5,qword ptr [eax+16]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x28,0xF5 )                                    /* movaps      xmm6,xmm5  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC9,0x31 )                     /* dppd        xmm1,xmm1,31h  */ \
_LINE4( 0xF2,0x0F,0x59,0xF6 )                               /* mulsd       xmm6,xmm6  */ \
_LINE4( 0xF2,0x0F,0x58,0xCE )                               /* addsd       xmm1,xmm6  */ \
_LINE4( 0xF2,0x0F,0x51,0xC9 )                               /* sqrtsd      xmm1,xmm1  */ \
_LINE5( 0xB8,0x01,0x00,0x00,0x00 )                          /* mov         eax,1  */ \
_LINE4( 0xF2,0x0F,0x2A,0xD0 )                               /* cvtsi2sd    xmm2,eax  */ \
_LINE4( 0xF2,0x0F,0x5E,0xD1 )                               /* divsd       xmm2,xmm1  */ \
_LINE3( 0x0F,0x16,0xD2 )                                    /* movlhps     xmm2,xmm2  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x66,0x0F,0x59,0xC2 )                               /* mulpd       xmm0,xmm2  */ \
_LINE4( 0xF2,0x0F,0x59,0xEA )                               /* mulsd       xmm5,xmm2  */ \
ASM( movupd [edx],xmm0 ) \
_LINE4( 0x0F,0x13,0x6A,0x10 )                               /* movlps      qword ptr [edx+16],xmm5  */ \
_END_ASM

/// Нормализация четырехмерного вектора двойной точности, команды FPU
#define VECTORP4DDNORMALFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
_LINE2( 0xDD,0x00 ) \
_LINE2( 0xDC,0x08 ) \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8] */ \
_LINE3( 0xDD,0x40,0x08 ) \
_STR(_DB(0xDC) _DB(0x48) _DB(0x08)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xDD) _DB(0x40) _DB(0x10)) \
_STR(_DB(0xDC) _DB(0x48) _DB(0x10)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xDD) _DB(0x40) _DB(0x18)) \
_STR(_DB(0xDC) _DB(0x48) _DB(0x18)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xD9) _DB(0xFA)) \
_STR(_DB(0xD9) _DB(0xE8)) \
_STR(_DB(0xDE) _DB(0xF1)) \
_STR(_DB(0xD9) _DB(0xC0)) \
_STR(_DB(0xDC) _DB(0x08)) \
_STR(_DB(0xDD) _DB(0x1A)) \
_STR(_DB(0xD9) _DB(0xC0)) \
_STR(_DB(0xDC) _DB(0x48) _DB(0x08)) \
_STR(_DB(0xDD) _DB(0x5A) _DB(0x08)) \
_STR(_DB(0xD9) _DB(0xC0)) \
_STR(_DB(0xDC) _DB(0x48) _DB(0x10)) \
_STR(_DB(0xDD) _DB(0x5A) _DB(0x10)) \
_STR(_DB(0xDC) _DB(0x48) _DB(0x18)) \
_STR(_DB(0xDD) _DB(0x5A) _DB(0x18)) \
_END_ASM

/// Нормализация четырехмерного вектора двойной точности, команды SSE4
#define VECTORP4DDNORMALSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
ASM( lddqu xmm0,[eax] ) \
ASM( lddqu xmm5,[eax+16] ) \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x28,0xF5 )                                    /* movaps      xmm6,xmm5  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC9,0x31 )                     /* dppd        xmm1,xmm1,31h  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xF6,0x31 )                     /* dppd        xmm6,xmm6,31h  */ \
_LINE4( 0xF2,0x0F,0x58,0xCE )                               /* addsd       xmm1,xmm6  */ \
_LINE4( 0xF2,0x0F,0x51,0xC9 )                               /* sqrtsd      xmm1,xmm1  */ \
_LINE5( 0xB8,0x01,0x00,0x00,0x00 )                          /* mov         eax,1  */ \
_LINE4( 0xF2,0x0F,0x2A,0xD0 )                               /* cvtsi2sd    xmm2,eax  */ \
_LINE4( 0xF2,0x0F,0x5E,0xD1 )                               /* divsd       xmm2,xmm1  */ \
_LINE3( 0x0F,0x16,0xD2 )                                    /* movlhps     xmm2,xmm2  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x66,0x0F,0x59,0xC2 )                               /* mulpd       xmm0,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xEA )                               /* mulpd       xmm5,xmm2  */ \
ASM( movupd [edx],xmm0 ) \
ASM( movupd [edx+16],xmm5 ) \
_END_ASM

/// Нормализация четырехмерного вектора двойной точности, команды AVX ???
#define VECTORP4DDNORMALAVX_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xC5,0xFD,0x10,0x00 )                /* vmovupd     ymm0,ymmword ptr [eax]  */ \
_LINE6( 0xC4,0xE3,0x79,0x41,0xD0,0xF1 )      /* vdppd       xmm2,xmm0,xmm0,31h  */ \
ASM( vsqrtsd xmm2,xmm2,xmm2 ) \
_LINE5( 0xB8,0x01,0x00,0x00,0x00 )           /* mov         eax,1  */ \
ASM( vcvtsi2sd xmm3,xmm3,eax )                /* cvtsi2sd    xmm4,eax  */ \
ASM( vdivsd xmm3,xmm3,xmm2 )                /* divsd       xmm4,xmm1  */ \
ASM( VSHUFPD ymm4,ymm3,ymm3,0x00 ) /* vbroadcastsd ymm4,qword ptr [esp-0Ch]  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0xC5,0xDD,0x59,0xC0 )                /* vmulpd      ymm0,ymm4,ymm0  */ \
_LINE4( 0xC5,0xFD,0x11,0x00 )                /* vmovupd     ymmword ptr [eax],ymm0  */ \
_LINE3( 0xC5,0xF8,0x77 )                /* vzeroupper  */ \
_END_ASM

//**************************** FAST NORMAL STDCALL *********************************

/// Нормализация двухмерного вектора одинарной точности, команды SSE
#define VECTORP2DFASTNORMALSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
ASM( xorps xmm0,xmm0 ) \
_LINE3( 0x0F,0x12,0x00 )                                    /* movlps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x59,0xC9 )                                    /* mulps       xmm1,xmm1  */ \
_LINE3( 0x0F,0x28,0xD1 )                                    /* movaps      xmm2,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC9,0x01 )                               /* shufps      xmm1,xmm1,01h  */ \
_LINE4( 0xF3,0x0F,0x58,0xD1 )                               /* addss       xmm2,xmm1  */ \
_LINE4( 0xF3,0x0F,0x52,0xD2 )                               /* rsqrtss     xmm2,xmm2  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x59,0xC2 )                                    /* mulps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
_END_ASM

/// Нормализация двухмерного вектора одинарной точности, команды SSE4
#define VECTORP2DFASTNORMALSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
ASM( xorps xmm0,xmm0 ) \
_LINE3( 0x0F,0x12,0x00 )                                    /* movlps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC9,0x31 )                     /* dpps        xmm1,xmm1,31h  */ \
_LINE4( 0xF3,0x0F,0x52,0xC9 )                               /* rsqrtss     xmm1,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x59,0xC1 )                                    /* mulps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
_END_ASM

/// Нормализация двухмерного вектора одинарной точности, команды SSE
#define VECTORP3DFASTNORMALSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
ASM( xorps xmm0,xmm0 ) \
_LINE3( 0x0F,0x12,0x00 )                                    /* movlps      xmm0,qword ptr [eax]  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x08 )                          /* movss       xmm3,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
ASM( movss xmm4,xmm3 ) \
_LINE3( 0x0F,0x59,0xC9 )                                    /* mulps       xmm1,xmm1  */ \
ASM( mulss xmm4,xmm4 ) \
_LINE3( 0x0F,0x28,0xD1 )                                    /* movaps      xmm2,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC9,0x01 )                               /* shufps      xmm1,xmm1,01h  */ \
_LINE4( 0xF3,0x0F,0x58,0xCC )                               /* addss       xmm1,xmm4  */ \
_LINE4( 0xF3,0x0F,0x58,0xD1 )                               /* addss       xmm2,xmm1  */ \
_LINE4( 0xF3,0x0F,0x52,0xD2 )                               /* rsqrtss     xmm2,xmm2  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x59,0xC2 )                                    /* mulps       xmm0,xmm2  */ \
ASM( mulss xmm3,xmm2 ) \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x5A,0x08 )                          /* movss       dword ptr [edx+8],xmm3  */ \
_END_ASM

/// Нормализация трехмерного вектора одинарной точности, команды SSE4
#define VECTORP3DFASTNORMALSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x00 )                                    /* movhps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC9,0xD1 )                     /* dpps        xmm1,xmm1,0D1h  */ \
_LINE4( 0xF3,0x0F,0x52,0xC9 )                               /* rsqrtss     xmm1,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8] */ \
_LINE3( 0x0F,0x59,0xC1 )                                    /* mulps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x17,0x02 )                                    /* movhps      qword ptr [edx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x42,0x08 )                          /* movss       dword ptr [edx+8],xmm0  */ \
_END_ASM

/// Нормализация четырехмерного вектора одинарной точности, команды SSE
#define VECTORP4DFASTNORMALSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
ASM( xorps xmm0,xmm0 ) \
ASM( xorps xmm3,xmm3 ) \
_LINE4( 0x0F,0x12,0x40,0x08 )                               /* movlps      xmm0,qword ptr [eax+8]  */ \
_LINE3( 0x0F,0x12,0x18 )                                    /* movlps      xmm3,qword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x28,0xD3 )                                    /* movaps      xmm2,xmm3  */ \
_LINE3( 0x0F,0x59,0xC9 )                                    /* mulps       xmm1,xmm1  */ \
_LINE3( 0x0F,0x59,0xD2 )                                    /* mulps       xmm2,xmm2  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x28,0xCA )                                    /* movaps      xmm1,xmm2  */ \
_LINE4( 0x0F,0xC6,0xD2,0x01 )                               /* shufps      xmm1,xmm1,1  */ \
_LINE4( 0xF3,0x0F,0x58,0xD1 )                               /* addss       xmm2,xmm1  */ \
_LINE4( 0xF3,0x0F,0x52,0xD2 )                               /* rsqrtss     xmm2,xmm2  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8] */ \
_LINE3( 0x0F,0x59,0xC2 )                                    /* mulps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x59,0xDA )                                    /* mulps       xmm3,xmm2  */ \
_LINE4( 0x0F,0x13,0x42,0x08 )                               /* movlps      qword ptr [edx+8],xmm0 */ \
_LINE3( 0x0F,0x13,0x1A )                                    /* movlps      qword ptr [edx],xmm3  */ \
_END_ASM

/// Нормализация четырехмерного вектора одинарной точности, команды SSE4
#define VECTORP4DFASTNORMALSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC9,0xF1 )                     /* dpps        xmm1,xmm1,0F1h  */ \
_LINE4( 0xF3,0x0F,0x52,0xC9 )                               /* rsqrtss     xmm1,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8] */ \
_LINE3( 0x0F,0x59,0xC1 )                                    /* mulps       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x02 )                               /* movupd      xmmword ptr [edx],xmm0  */ \
_END_ASM

/// Нормализация двухмерного вектора двойной точности, команды SSE2
#define VECTORP2DDFASTNORMALSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )                               /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xC9 )                               /* mulpd       xmm1,xmm1  */ \
_LINE3( 0x0F,0x12,0xD1 )                                    /* movhlps     xmm2,xmm1  */ \
_LINE4( 0xF2,0x0F,0x58,0xD1 )                               /* addsd       xmm2,xmm1  */ \
_LINE4( 0xF2,0x0F,0x5A,0xDA )                               /* cvtsd2ss    xmm3,xmm2  */ \
_LINE4( 0xF3,0x0F,0x52,0xE3 )                               /* rsqrtss     xmm4,xmm3  */ \
_LINE4( 0xF3,0x0F,0x5A,0xCC )                               /* cvtss2sd    xmm1,xmm4  */ \
_LINE3( 0x0F,0x16,0xC9 )                                    /* movlhps     xmm1,xmm1  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x66,0x0F,0x59,0xC1 )                               /* mulpd       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
_LINE4( 0x0F,0x17,0x42,0x08 )                               /* movhps      qword ptr [edx+8],xmm0  */ \
_END_ASM

/// Нормализация двухмерного вектора двойной точности, команды SSE4
#define VECTORP2DDFASTNORMALSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
ASM( lddqu xmm0,[eax] ) \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC9,0x31 )                     /* dppd        xmm1,xmm1,31h  */ \
_LINE4( 0xF2,0x0F,0x5A,0xD9 )                               /* cvtsd2ss    xmm3,xmm1  */ \
_LINE4( 0xF3,0x0F,0x52,0xE3 )                               /* rsqrtss     xmm4,xmm3  */ \
_LINE4( 0xF3,0x0F,0x5A,0xCC )                               /* cvtss2sd    xmm1,xmm4  */ \
_LINE3( 0x0F,0x16,0xC9 )                                    /* movlhps     xmm1,xmm1  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x66,0x0F,0x59,0xC1 )                               /* mulpd       xmm0,xmm1  */ \
ASM( movupd [edx],xmm0 ) \
_END_ASM

/// Нормализация трехмерного вектора двойной точности, команды SSE2
#define VECTORP3DDFASTNORMALSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,qword ptr [eax]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )                               /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE5( 0xF2,0x0F,0x10,0x68,0x10 )                          /* movsd       xmm5,qword ptr [eax+16]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x28,0xF5 )                                    /* movaps      xmm6,xmm5  */ \
_LINE4( 0x66,0x0F,0x59,0xC9 )                               /* mulpd       xmm1,xmm1  */ \
_LINE4( 0xF2,0x0F,0x59,0xF6 )                               /* mulsd       xmm6,xmm6  */ \
_LINE4( 0xF2,0x0F,0x58,0xCE )                               /* addsd       xmm1,xmm6  */ \
_LINE3( 0x0F,0x12,0xD1 )                                    /* movhlps     xmm2,xmm1  */ \
_LINE4( 0xF2,0x0F,0x58,0xD1 )                               /* addsd       xmm2,xmm1  */ \
_LINE4( 0xF2,0x0F,0x5A,0xDA )                               /* cvtsd2ss    xmm3,xmm2  */ \
_LINE4( 0xF3,0x0F,0x52,0xE3 )                               /* rsqrtss     xmm4,xmm3  */ \
_LINE4( 0xF3,0x0F,0x5A,0xCC )                               /* cvtss2sd    xmm1,xmm4  */ \
_LINE3( 0x0F,0x16,0xC9 )                                    /* movlhps     xmm1,xmm1  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x66,0x0F,0x59,0xC1 )                               /* mulpd       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x59,0xE9 )                               /* mulsd       xmm5,xmm1  */ \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
_LINE4( 0x0F,0x17,0x42,0x08 )                               /* movhps      qword ptr [edx+8],xmm0  */ \
_LINE4( 0x0F,0x13,0x6A,0x10 )                               /* movlps      qword ptr [edx+16],xmm5  */ \
_END_ASM

/// Нормализация трехмерного вектора двойной точности, команды SSE4
#define VECTORP3DDFASTNORMALSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
ASM( lddqu xmm0,[eax] ) \
_LINE5( 0xF2,0x0F,0x10,0x68,0x10 )                          /* movsd       xmm5,qword ptr [eax+16]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x28,0xF5 )                                    /* movaps      xmm6,xmm5  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC9,0x31 )                     /* dppd        xmm1,xmm1,31h  */ \
_LINE4( 0xF2,0x0F,0x59,0xF6 )                               /* mulsd       xmm6,xmm6  */ \
_LINE4( 0xF2,0x0F,0x58,0xCE )                               /* addsd       xmm1,xmm6  */ \
_LINE4( 0xF2,0x0F,0x5A,0xD9 )                               /* cvtsd2ss    xmm3,xmm1  */ \
_LINE4( 0xF3,0x0F,0x52,0xE3 )                               /* rsqrtss     xmm4,xmm3  */ \
_LINE4( 0xF3,0x0F,0x5A,0xCC )                               /* cvtss2sd    xmm1,xmm4  */ \
_LINE3( 0x0F,0x16,0xC9 )                                    /* movlhps     xmm1,xmm1  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x66,0x0F,0x59,0xC1 )                               /* mulpd       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x59,0xE9 )                               /* mulsd       xmm5,xmm1  */ \
ASM( movupd [edx],xmm0 ) \
_LINE4( 0x0F,0x13,0x6A,0x10 )                               /* movlps      qword ptr [edx+16],xmm5  */ \
_END_ASM

/// Нормализация четырехмерного вектора двойной точности, команды SSE2
#define VECTORP4DDFASTNORMALSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,qword ptr [eax]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )                               /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE5( 0xF2,0x0F,0x10,0x68,0x10 )                          /* movsd       xmm5,qword ptr [eax+16]  */ \
_LINE4( 0x0F,0x16,0x68,0x18 )                               /* movhps      xmm5,qword ptr [eax+24]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x28,0xF5 )                                    /* movaps      xmm6,xmm5  */ \
_LINE4( 0x66,0x0F,0x59,0xC9 )                               /* mulpd       xmm1,xmm1  */ \
_LINE4( 0x66,0x0F,0x59,0xF6 )                               /* mulpd       xmm6,xmm6  */ \
_LINE4( 0x66,0x0F,0x58,0xCE )                               /* addpd       xmm1,xmm6  */ \
_LINE3( 0x0F,0x12,0xD1 )                                    /* movhlps     xmm2,xmm1  */ \
_LINE4( 0xF2,0x0F,0x58,0xD1 )                               /* addsd       xmm2,xmm1  */ \
_LINE4( 0xF2,0x0F,0x5A,0xDA )                               /* cvtsd2ss    xmm3,xmm2  */ \
_LINE4( 0xF3,0x0F,0x52,0xE3 )                               /* rsqrtss     xmm4,xmm3  */ \
_LINE4( 0xF3,0x0F,0x5A,0xCC )                               /* cvtss2sd    xmm1,xmm4  */ \
_LINE3( 0x0F,0x16,0xC9 )                                    /* movlhps     xmm1,xmm1  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x66,0x0F,0x59,0xC1 )                               /* mulpd       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x59,0xE9 )                               /* mulpd       xmm5,xmm1  */ \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
_LINE4( 0x0F,0x17,0x42,0x08 )                               /* movhps      qword ptr [edx+8],xmm0  */ \
_LINE4( 0x0F,0x13,0x6A,0x10 )                               /* movlps      qword ptr [edx+16],xmm5  */ \
_LINE4( 0x0F,0x17,0x6A,0x18 )                               /* movhps      qword ptr [edx+24],xmm5  */ \
_END_ASM

/// Нормализация четырехмерного вектора двойной точности, команды SSE4
#define VECTORP4DDFASTNORMALSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
ASM( lddqu xmm0,[eax] ) \
ASM( lddqu xmm5,[eax+16] ) \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x28,0xF5 )                                    /* movaps      xmm6,xmm5  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC9,0x31 )                     /* dppd        xmm1,xmm1,31h  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xF6,0x31 )                     /* dppd        xmm6,xmm6,31h  */ \
_LINE4( 0x66,0x0F,0x58,0xCE )                               /* addpd       xmm1,xmm6  */ \
_LINE4( 0xF2,0x0F,0x5A,0xD9 )                               /* cvtsd2ss    xmm3,xmm1  */ \
_LINE4( 0xF3,0x0F,0x52,0xE3 )                               /* rsqrtss     xmm4,xmm3  */ \
_LINE4( 0xF3,0x0F,0x5A,0xCC )                               /* cvtss2sd    xmm1,xmm4  */ \
_LINE3( 0x0F,0x16,0xC9 )                                    /* movlhps     xmm1,xmm1  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x66,0x0F,0x59,0xC1 )                               /* mulpd       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x59,0xE9 )                               /* mulpd       xmm5,xmm1  */ \
ASM( movupd [edx],xmm0 ) \
ASM( movupd [edx+16],xmm5 ) \
_END_ASM

//**************************** NORMAL REGCALL *********************************

// vector Normal eax-a void * edx-b void *

/// Нормализация двухмерного вектора одинарной точности, команды FPU
#define VECTORP2DNORMALFPU \
_BEGIN_ASM \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xFA )                                         /* fsqrt             */ \
_LINE2( 0xD9,0xE8 )                                         /* fld1              */ \
_LINE2( 0xDE,0xF1 )                                         /* fdivrp      st(1),st  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE2( 0xD9,0x1A )                                         /* fstp        dword ptr [edx]  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x5A,0x04 )                                    /* fstp        dword ptr [edx+4]  */ \
_END_ASM

/// Нормализация трехмерного вектора одинарной точности, команды FPU
#define VECTORP3DNORMALFPU \
_BEGIN_ASM \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD8,0x48,0x08 )                                    /* fmul        dword ptr [eax+8]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xFA )                                         /* fsqrt             */ \
_LINE2( 0xD9,0xE8 )                                         /* fld1              */ \
_LINE2( 0xDE,0xF1 )                                         /* fdivrp      st(1),st  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE2( 0xD9,0x1A )                                         /* fstp        dword ptr [edx]  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x5A,0x04 )                                    /* fstp        dword ptr [edx+4]  */ \
_LINE3( 0xD8,0x48,0x08 )                                    /* fmul        dword ptr [eax+8]  */ \
_LINE3( 0xD9,0x5A,0x08 )                                    /* fstp        dword ptr [edx+8]  */ \
_END_ASM

/// Нормализация трехмерного вектора одинарной точности, команды SSE // не точно
#define VECTORP3DNORMALSSE \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x00 )                                    /* movhps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x59,0xC9 )                                    /* mulps       xmm1,xmm1  */ \
_LINE3( 0x0F,0x28,0xD1 )                                    /* movaps      xmm2,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC9,0x0E )                               /* shufps      xmm1,xmm1,0Eh  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC9,0x01 )                               /* shufps      xmm1,xmm1,1  */ \
_LINE4( 0xF3,0x0F,0x58,0xD1 )                               /* addss       xmm2,xmm1  */ \
_LINE4( 0xF3,0x0F,0x51,0xD2 )                               /* sqrtss      xmm2,xmm2  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x5E,0xC2 )                                    /* divps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x17,0x02 )                                    /* movhps      qword ptr [edx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x42,0x08 )                          /* movss       dword ptr [edx+8],xmm0  */ \
_END_ASM

/// Нормализация двухмерного вектора двойной точности, команды FPU
#define VECTORP2DDNORMALFPU \
_BEGIN_ASM \
 _STR(_DB(0xDD) _DB(0x00)) \
 _STR(_DB(0xDC) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x48) _DB(0x08)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xD9) _DB(0xFA)) \
 _STR(_DB(0xD9) _DB(0xE8)) \
 _STR(_DB(0xDE) _DB(0xF1)) \
 _STR(_DB(0xD9) _DB(0xC0)) \
 _STR(_DB(0xDC) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x1A)) \
 _STR(_DB(0xDC) _DB(0x48) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x5A) _DB(0x08)) \
_END_ASM

/// Нормализация двухмерного вектора одинарной точности, команды SSE2
#define VECTORP2DDNORMALSSE2 \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0x10,0x60,0x08 )                          /* movsd       xmm4,mmword ptr [eax+8]  */ \
_LINE4( 0x66,0x0F,0x14,0xC4 )                               /* unpcklpd    xmm0,xmm4  */ \
_LINE4( 0x66,0x0F,0x28,0xD0 )                               /* movapd      xmm2,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xD2 )                               /* mulpd       xmm2,xmm2  */ \
_LINE4( 0x66,0x0F,0x28,0xDA )                               /* movapd      xmm3,xmm2  */ \
_LINE4( 0x66,0x0F,0x15,0xD2 )                               /* unpckhpd    xmm2,xmm2  */ \
_LINE4( 0xF2,0x0F,0x58,0xDA )                               /* addsd       xmm3,xmm2  */ \
_LINE4( 0xF2,0x0F,0x51,0xDB )                               /* sqrtsd      xmm3,xmm3  */ \
_LINE2( 0xD9,0xE8 )                                         /* fld1              */ \
_LINE4( 0xDD,0x5C,0x24,0xDC )                               /* fstp        qword ptr [esp-24h]  */ \
_LINE6( 0xF2,0x0F,0x10,0x54,0x24,0xDC )                     /* movsd       xmm2,mmword ptr [esp-24h]  */ \
_LINE4( 0xF2,0x0F,0x5E,0xD3 )                               /* divsd       xmm2,xmm3  */ \
_LINE4( 0x66,0x0F,0x14,0xD2 )                               /* unpcklpd    xmm2,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xC2 )                               /* mulpd       xmm0,xmm2  */ \
_LINE4( 0xF2,0x0F,0x11,0x02 )                               /* movsd       mmword ptr [edx],xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x42,0x08 )                          /* movsd       mmword ptr [edx+8],xmm0  */ \
_END_ASM

/// Нормализация трехмерного вектора двойной точности, команды FPU
#define VECTORP3DDNORMALFPU \
_BEGIN_ASM \
 _STR(_DB(0xDD) _DB(0x00)) \
 _STR(_DB(0xDC) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x48) _DB(0x08)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x10)) \
 _STR(_DB(0xDC) _DB(0x48) _DB(0x10)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xD9) _DB(0xFA)) \
 _STR(_DB(0xD9) _DB(0xE8)) \
 _STR(_DB(0xDE) _DB(0xF1)) \
 _STR(_DB(0xD9) _DB(0xC0)) \
 _STR(_DB(0xDC) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x1A)) \
 _STR(_DB(0xD9) _DB(0xC0)) \
 _STR(_DB(0xDC) _DB(0x48) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x5A) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x48) _DB(0x10)) \
 _STR(_DB(0xDD) _DB(0x5A) _DB(0x10)) \
_END_ASM

/// Нормализация трехмерного вектора одинарной точности, команды SSE2
#define VECTORP3DDNORMALSSE2 \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0x10,0x60,0x08 )                          /* movsd       xmm4,mmword ptr [eax+8]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x10 )                          /* movsd       xmm1,mmword ptr [eax+10h]  */ \
_LINE4( 0x66,0x0F,0x14,0xC4 )                               /* unpcklpd    xmm0,xmm4  */ \
_LINE4( 0x66,0x0F,0x28,0xD0 )                               /* movapd      xmm2,xmm0  */ \
_LINE4( 0x66,0x0F,0x28,0xD9 )                               /* movapd      xmm3,xmm1  */ \
_LINE4( 0x66,0x0F,0x59,0xD2 )                               /* mulpd       xmm2,xmm2  */ \
_LINE4( 0xF2,0x0F,0x59,0xDB )                               /* mulsd       xmm3,xmm3  */ \
_LINE4( 0xF2,0x0F,0x58,0xDA )                               /* addsd       xmm3,xmm2  */ \
_LINE4( 0x66,0x0F,0x15,0xD2 )                               /* unpckhpd    xmm2,xmm2  */ \
_LINE4( 0xF2,0x0F,0x58,0xDA )                               /* addsd       xmm3,xmm2  */ \
_LINE4( 0xF2,0x0F,0x51,0xDB )                               /* sqrtsd      xmm3,xmm3  */ \
_LINE2( 0xD9,0xE8 )                                         /* fld1              */ \
_LINE4( 0xDD,0x5C,0x24,0xDC )                               /* fstp        qword ptr [esp-24h]  */ \
_LINE6( 0xF2,0x0F,0x10,0x54,0x24,0xDC )                     /* movsd       xmm2,mmword ptr [esp-24h]  */ \
_LINE4( 0xF2,0x0F,0x5E,0xD3 )                               /* divsd       xmm2,xmm3  */ \
_LINE4( 0x66,0x0F,0x14,0xD2 )                               /* unpcklpd    xmm2,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xC2 )                               /* mulpd       xmm0,xmm2  */ \
_LINE4( 0xF2,0x0F,0x11,0x02 )                               /* movsd       mmword ptr [edx],xmm0  */ \
_LINE4( 0xF2,0x0F,0x59,0xCA )                               /* mulsd       xmm1,xmm2  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x4A,0x10 )                          /* movsd       mmword ptr [edx+10h],xmm1  */ \
_LINE5( 0xF2,0x0F,0x11,0x42,0x08 )                          /* movsd       mmword ptr [edx+8],xmm0  */ \
_END_ASM

#endif