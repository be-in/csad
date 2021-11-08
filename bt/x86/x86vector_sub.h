//=============================================================================
///**
// *  @file vector_sub.h
// *
// *  $Id: vector_sub.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float substract, MS Visual C++ 2003-2008
// *
// *  @author Pan_teleymonov Ale_ksandr Kon_stantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_VECTOR_SUB_H
#define GEN3_VECTOR_SUB_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** SUB STDCALL **********************************************
// subtract vectors eax=[esp+4]-a void *, edx=[esp+8]-b void *, ecx=[esp+12]-rez void *

/// Вычитание четырехмерных байтовых векторов, команды CPU.
/// @brief for CPUTYPE3
#define VECTORP2BSUBCPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
ASM( sub al,dl ) \
ASM( cmovb al,0x00 ) \
ASM( sub ah,dh ) \
ASM( cmovb ah,0x00 ) \
ASM( ror edx,16 ) \
ASM( ror eax,16 ) \
ASM( sub al,dl ) \
ASM( cmovb al,0x00 ) \
ASM( sub ah,dh ) \
ASM( cmovb ah,0x00 ) \
ASM( rol eax,16 ) \
_END_ASM

/// Вычитание двухмерных векторов одинарной точности, команды FPU.
#define VECTORP2DSUBFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xD8,0x22 )                                         /* fsub        dword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE2( 0xD9,0x19 )                                         /* fstp        dword ptr [ecx]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x62,0x04 )                                    /* fsub        dword ptr [edx+4]  */ \
_LINE3( 0xD9,0x59,0x04 )                                    /* fstp        dword ptr [ecx+4]  */ \
_END_ASM

/// Вычитание двухмерных векторов одинарной точности, команды 3DNOW.
#define VECTORP2DSUB3DNOW_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE3( 0x0F,0x6F,0x00 )                                    /* movq        mm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x0F,0x02,0x9A )                               /* pfsub       mm0,mmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x7F,0x01 )                                    /* movq        mmword ptr [ecx],mm0  */ \
_LINE2( 0x0F,0x0E )                                         /* femms  */ \
_END_ASM

/// Вычитание двухмерных векторов одинарной точности, команды SSE.
// не верно заполняется старшая часть!
#define VECTORP2DSUBSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF3,0x0F,0x10,0x00 )                               /* movss       xmm0,dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
ASM( subss xmm0,dword ptr [edx] ) \
ASM( subss xmm1,dword ptr [edx+4] ) \
_LINE4( 0xF3,0x0F,0x11,0x01 )                               /* movss       dword ptr [ecx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x49,0x04 )                          /* movss       dword ptr [ecx+4],xmm1  */ \
_END_ASM

/// Вычитание двухмерных векторов одинарной точности, команды SSE.
// не верно заполняется старшая часть!
#define VECTORP2DSUBSSE_STD1 \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF3,0x0F,0x10,0x00 )                               /* movss       xmm0,dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE4( 0xF3,0x0F,0x10,0x12 )                               /* movss       xmm2,dword ptr [edx]  */ \
_LINE5( 0xF3,0x0F,0x10,0x5A,0x04 )                          /* movss       xmm3,dword ptr [edx+4]  */ \
_LINE4( 0xF3,0x0F,0x5C,0xC2 )                               /* subss       xmm0,xmm2  */ \
_LINE4( 0xF3,0x0F,0x5C,0xCB )                               /* subss       xmm1,xmm3  */ \
_LINE4( 0xF3,0x0F,0x11,0x01 )                               /* movss       dword ptr [ecx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x49,0x04 )                          /* movss       dword ptr [ecx+4],xmm1  */ \
_END_ASM

/// Вычитание двухмерных векторов одинарной точности, команды SSE2.
#define VECTORP2DSUBSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,mmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE3( 0x0F,0x5C,0xC1 )                                    /* subps       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_END_ASM

/// Вычитание трехмерных векторов одинарной точности, команды FPU.
#define VECTORP3DSUBFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xD8,0x22 )                                         /* fsub        dword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE2( 0xD9,0x19 )                                         /* fstp        dword ptr [ecx]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x62,0x04 )                                    /* fsub        dword ptr [edx+4]  */ \
_LINE3( 0xD9,0x59,0x04 )                                    /* fstp        dword ptr [ecx+4]  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD8,0x62,0x08 )                                    /* fsub        dword ptr [edx+8]  */ \
_LINE3( 0xD9,0x59,0x08 )                                    /* fstp        dword ptr [ecx+8]  */ \
_END_ASM

/// Вычитание трехмерных векторов одинарной точности, команды 3DNOW.
#define VECTORP3DSUB3DNOW_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE3( 0x0F,0x6F,0x00 )                                    /* movq        mm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x0F,0x02,0x9A )                               /* pfsub       mm0,mmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x7F,0x01 )                                    /* movq        mmword ptr [ecx],mm0  */ \
_LINE4( 0x0F,0x6E,0x48,0x08 )                               /* movd        mm1,dword ptr [eax+8]  */ \
_LINE5( 0x0F,0x0F,0x4A,0x08,0x9A )                          /* pfsub       mm1,mmword ptr [edx+8]  */ \
_LINE4( 0x0F,0x7E,0x49,0x08 )                               /* movd        dword ptr [ecx+8],mm1  */ \
_LINE2( 0x0F,0x0E )                                         /* femms  */ \
_END_ASM

/// Вычитание трехмерных векторов одинарной точности, команды SSE.
#define VECTORP3DSUBSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE3( 0x0F,0x16,0x00 )                                    /* movhps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x16,0x0A )                                    /* movhps      xmm1,qword ptr [edx]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x5C,0xC1 )                                    /* subps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x17,0x00 )                                    /* movhps      qword ptr [eax],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x40,0x08 )                          /* movss       dword ptr [eax+8],xmm0  */ \
_END_ASM

/// Вычитание четырехмерных векторов одинарной точности, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP4DSUBFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE3( 0xD9,0x40,0x0C )                                    /* fld         dword ptr [eax+0Ch]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0xD8,0x62,0x0C )                                    /* fsub        dword ptr [edx+0Ch]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE3( 0xD9,0x59,0x0C )                                    /* fstp        dword ptr [ecx+0Ch]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0x22 )                                         /* fsub        dword ptr [edx]  */ \
_LINE2( 0xD9,0x19 )                                         /* fstp        dword ptr [ecx]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x62,0x04 )                                    /* fsub        dword ptr [edx+4]  */ \
_LINE3( 0xD9,0x59,0x04 )                                    /* fstp        dword ptr [ecx+4]  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD8,0x62,0x08 )                                    /* fsub        dword ptr [edx+8]  */ \
_LINE3( 0xD9,0x59,0x08 )                                    /* fstp        dword ptr [ecx+8]  */ \
_END_ASM

/// Вычитание четырехмерных векторов одинарной точности, команды 3DNOW.
/// @brief for CPUTYPE2
#define VECTORP4DSUB3DNOW_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE3( 0x0F,0x6F,0x00 )                                    /* movq        mm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x0F,0x02,0x9A )                               /* pfsub       mm0,mmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x7F,0x01 )                                    /* movq        mmword ptr [ecx],mm0  */ \
_LINE4( 0x0F,0x6F,0x48,0x08 )                               /* movq        mm1,mmword ptr [eax+8]  */ \
_LINE5( 0x0F,0x0F,0x4A,0x08,0x9A )                          /* pfsub       mm1,mmword ptr [edx+8]  */ \
_LINE4( 0x0F,0x7F,0x49,0x08 )                               /* movq        mmword ptr [ecx+8],mm1  */ \
_LINE2( 0x0F,0x0E )                                         /* femms */ \
_END_ASM

/// Вычитание четырехмерных векторов одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP4DSUBSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF3,0x0F,0x10,0x00 )                               /* movss       xmm0,dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE5( 0xF3,0x0F,0x10,0x50,0x08 )                          /* movss       xmm2,dword ptr [eax+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x0C )                          /* movss       xmm3,dword ptr [eax+12]  */ \
ASM( subss xmm0,dword ptr [edx] ) \
ASM( subss xmm1,dword ptr [edx+4] ) \
ASM( subss xmm2,dword ptr [edx+8] ) \
ASM( subss xmm3,dword ptr [edx+12] ) \
_LINE4( 0xF3,0x0F,0x11,0x01 )                               /* movss       dword ptr [ecx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x49,0x04 )                          /* movss       dword ptr [ecx+4],xmm1  */ \
_LINE5( 0xF3,0x0F,0x11,0x51,0x08 )                          /* movss       dword ptr [ecx+8],xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x59,0x0C )                          /* movss       dword ptr [ecx+12],xmm3  */ \
_END_ASM

/// Вычитание четырехмерных векторов одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP4DSUBSSE_STD1 \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE3( 0x0F,0x12,0x00 )                                    /* movlps      xmm0,qword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x12,0x0A )                                    /* movlps      xmm1,qword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )                               /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE4( 0x0F,0x16,0x4A,0x08 )                               /* movhps      xmm1,qword ptr [edx+8]  */ \
_LINE3( 0x0F,0x5C,0xC1 )                                    /* subps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x01 )                                    /* movlps      qword ptr [ecx],xmm0  */ \
_LINE4( 0x0F,0x17,0x41,0x08 )                               /* movhps      qword ptr [ecx+8],xmm0 */ \
_END_ASM

/// Вычитание четырехмерных векторов одинарной точности, команды SSE2.
#define VECTORP4DSUBSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,mmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x08 )                          /* movsd       xmm2,mmword ptr [eax+8]  */ \
_LINE5( 0xF2,0x0F,0x10,0x5A,0x08 )                          /* movsd       xmm3,mmword ptr [edx+8]  */ \
_LINE3( 0x0F,0x5C,0xC1 )                                    /* subps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x5C,0xD3 )                                    /* subps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x13,0x01 )                                    /* movlps      qword ptr [ecx],xmm0  */ \
_LINE4( 0x0F,0x13,0x51,0x08 )                               /* movlps      qword ptr [ecx+8],xmm2  */ \
_END_ASM

/// Вычитание четырехмерных векторов одинарной точности, команды SSE2.
#define VECTORP4DSUBSSE2_STD1 \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )                               /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x16,0x4A,0x08 )                               /* movhps      xmm1,qword ptr [edx+8]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x12,0x00 )                                    /* movlps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x12,0x0A )                                    /* movlps      xmm1,qword ptr [edx]  */ \
_LINE3( 0x0F,0x5C,0xC1 )                                    /* subps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x01 )                                    /* movlps      qword ptr [ecx],xmm0  */ \
_LINE4( 0x0F,0x17,0x41,0x08 )                               /* movhps      qword ptr [ecx+8],xmm0 */ \
_END_ASM

/// Вычитание четырехмерных векторов одинарной точности, команды SSE3.
#define VECTORP4DSUBSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x5C,0xC1 )                                    /* subps       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0x66,0x0F,0x17,0x41,0x08 )                          /* movhpd      qword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Вычитание двухмерных векторов двойной точности, команды FPU.
#define VECTORP2DDSUBFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xDD,0x00 )                                         /* fld         qword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xDC,0x22 )                                         /* fsub        qword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE2( 0xDD,0x19 )                                         /* fstp        qword ptr [ecx]  */ \
_LINE3( 0xDD,0x40,0x08 )                                    /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDC,0x62,0x08 )                                    /* fsub        qword ptr [edx+8]  */ \
_LINE3( 0xDD,0x59,0x08 )                                    /* fstp        qword ptr [ecx+8]  */ \
_END_ASM

/// Вычитание двухмерных векторов двойной точности, команды SSE2.
#define VECTORP2DDSUBSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x08 )                          /* movsd       xmm1,mmword ptr [eax+8]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE4( 0xF2,0x0F,0x10,0x22 )                               /* movsd       xmm4,mmword ptr [edx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x6A,0x08 )                          /* movsd       xmm5,mmword ptr [edx+8]  */ \
_LINE4( 0x66,0x0F,0x14,0xC1 )                               /* unpcklpd    xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x14,0xE5 )                               /* unpcklpd    xmm4,xmm5  */ \
_LINE4( 0x66,0x0F,0x5C,0xC4 )                               /* subpd       xmm0,xmm4  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Вычитание двухмерных векторов двойной точности, команды SSE3.
#define VECTORP2DDSUBSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE4( 0x66,0x0F,0x5C,0xC1 )                               /* subpd       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Вычитание трехмерных векторов двойной точности, команды FPU.
#define VECTORP3DDSUBFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xDD,0x00 )                                         /* fld         qword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xDC,0x22 )                                         /* fsub        qword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE2( 0xDD,0x19 )                                         /* fstp        qword ptr [ecx]  */ \
_LINE3( 0xDD,0x40,0x08 )                                    /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDC,0x62,0x08 )                                    /* fsub        qword ptr [edx+8]  */ \
_LINE3( 0xDD,0x59,0x08 )                                    /* fstp        qword ptr [ecx+8]  */ \
_LINE3( 0xDD,0x40,0x10 )                                    /* fld         qword ptr [eax+10h]  */ \
_LINE3( 0xDC,0x62,0x10 )                                    /* fsub        qword ptr [edx+10h]  */ \
_LINE3( 0xDD,0x59,0x10 )                                    /* fstp        qword ptr [ecx+10h]  */ \
_END_ASM

/// Вычитание трехмерных векторов двойной точности, команды SSE2.
#define VECTORP3DDSUBSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x08 )                          /* movsd       xmm1,mmword ptr [eax+8]  */ \
_LINE5( 0xF2,0x0F,0x5C,0x52,0x10 )                          /* subsd       xmm2,mmword ptr [edx+10h]  */ \
_LINE4( 0xF2,0x0F,0x10,0x22 )                               /* movsd       xmm4,mmword ptr [edx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x6A,0x08 )                          /* movsd       xmm5,mmword ptr [edx+8]  */ \
_LINE4( 0x66,0x0F,0x14,0xC1 )                               /* unpcklpd    xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x14,0xE5 )                               /* unpcklpd    xmm4,xmm5  */ \
_LINE4( 0x66,0x0F,0x5C,0xC4 )                               /* subpd       xmm0,xmm4  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Вычитание трехмерных векторов двойной точности, команды SSE3.
/// @brief for CPUTYPE3
#define VECTORP3DDSUBSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x22 )                               /* lddqu       xmm4,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE4( 0x66,0x0F,0x5C,0xC4 )                               /* subpd       xmm0,xmm4  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x5C,0x52,0x10 )                          /* subsd       xmm2,mmword ptr [edx+10h]  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Вычитание трехмерных векторов двойной точности, команды SSE4.
/// @brief for CPUTYPE4
#define VECTORP3DDSUBSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x22 )                               /* lddqu       xmm4,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE4( 0x66,0x0F,0x5C,0xC4 )                               /* subpd       xmm0,xmm4  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x5C,0x52,0x10 )                          /* subsd       xmm2,mmword ptr [edx+10h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_END_ASM

/// Вычитание четырехмерных векторов двойной точности, команды FPU.
/// @brief for CPUTYPE4
#define VECTORP4DDSUBFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE3( 0xDD,0x40,0x18 )                                    /* fld         qword ptr [eax+18h]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0xDC,0x62,0x18 )                                    /* fsub        qword ptr [edx+18h]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE3( 0xDD,0x59,0x18 )                                    /* fstp        qword ptr [ecx+18h]  */ \
_LINE2( 0xDD,0x00 )                                         /* fld         qword ptr [eax]  */ \
_LINE2( 0xDC,0x22 )                                         /* fsub        qword ptr [edx]  */ \
_LINE2( 0xDD,0x19 )                                         /* fstp        qword ptr [ecx]  */ \
_LINE3( 0xDD,0x40,0x08 )                                    /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDC,0x62,0x08 )                                    /* fsub        qword ptr [edx+8]  */ \
_LINE3( 0xDD,0x59,0x08 )                                    /* fstp        qword ptr [ecx+8]  */ \
_LINE3( 0xDD,0x40,0x10 )                                    /* fld         qword ptr [eax+10h]  */ \
_LINE3( 0xDC,0x62,0x10 )                                    /* fsub        qword ptr [edx+10h]  */ \
_LINE3( 0xDD,0x59,0x10 )                                    /* fstp        qword ptr [ecx+10h]  */ \
_END_ASM

/// Вычитание четырехмерных векторов двойной точности, команды SSE2.
#define VECTORP4DDSUBSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x5C,0x02 )                               /* subsd       xmm0,mmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x08 )                          /* movsd       xmm2,mmword ptr [eax+8]  */ \
_LINE5( 0xF2,0x0F,0x5C,0x52,0x08 )                          /* subsd       xmm2,mmword ptr [edx+8]  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm2  */ \
_LINE5( 0xF2,0x0F,0x10,0x60,0x10 )                          /* movsd       xmm4,mmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0x5C,0x62,0x10 )                          /* subsd       xmm4,mmword ptr [edx+10h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x61,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm4  */ \
_LINE5( 0xF2,0x0F,0x10,0x70,0x18 )                          /* movsd       xmm6,mmword ptr [eax+18h]  */ \
_LINE5( 0xF2,0x0F,0x5C,0x72,0x18 )                          /* subsd       xmm6,mmword ptr [edx+18h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x71,0x18 )                          /* movsd       mmword ptr [ecx+18h],xmm6  */ \
_END_ASM

/// Вычитание четырехмерных векторов двойной точности, команды SSE3.
#define VECTORP4DDSUBSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x50,0x10 )                          /* lddqu       xmm2,xmmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x5A,0x10 )                          /* lddqu       xmm3,xmmword ptr [edx+10h]  */ \
_LINE4( 0x66,0x0F,0x5C,0xC1 )                               /* subpd       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x5C,0xD3 )                               /* subpd       xmm2,xmm3  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xD2 )                               /* unpckhpd    xmm2,xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x18 )                          /* movsd       mmword ptr [ecx+18h],xmm2  */ \
_END_ASM

/// Вычитание четырехмерных векторов двойной точности, команды SSE4.
#define VECTORP4DDSUBSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x50,0x10 )                          /* lddqu       xmm2,xmmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x5A,0x10 )                          /* lddqu       xmm3,xmmword ptr [edx+10h]  */ \
_LINE4( 0x66,0x0F,0x5C,0xC1 )                               /* subpd       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x5C,0xD3 )                               /* subpd       xmm2,xmm3  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_LINE5( 0x66,0x0F,0x11,0x51,0x10 )                          /* movupd      xmmword ptr [ecx+10h],xmm2  */ \
_END_ASM

/// Вычитание четырехмерных векторов двойной точности, команды AVX
#define VECTORP4DDSUBAVX_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )         /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xC5,0xFD,0x10,0x00 )         /* vmovupd     ymm0,ymmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )         /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xC5,0xFD,0x10,0x0A )         /* vmovupd     ymm1,ymmword ptr [edx]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )         /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE4( 0xC5,0xFD,0x5C,0xD9 )         /* vsubpd      ymm3,ymm0,ymm1  */ \
_LINE4( 0xC5,0xFD,0x11,0x18 )         /* vmovupd     ymmword ptr [eax],ymm3  */ \
_LINE3( 0xC5,0xF8,0x77 )              /* vzeroupper  */ \
_END_ASM

//**************************** ADD REGISTER FASTCALL *********************************
// subtract vectors eax-a void *, edx-b void *, ecx-rez void *

/// Вычитание двухмерных векторов одинарной точности, команды FPU.
#define VECTORP2DSUBFPU \
_BEGIN_ASM \
_LINE2(0xD9,0x00) \
_LINE2(0xD8,0x22) \
_LINE2(0xD9,0x19) \
_LINE3(0xD9,0x40,0x04) \
_LINE3(0xD8,0x62,0x04) \
_LINE3(0xD9,0x59,0x04) \
_END_ASM

/// Вычитание двухмерных векторов одинарной точности, команды 3DNOW.
#define VECTORP2DSUB3DNOW \
_BEGIN_ASM \
 _STR(_DB(0x0F) _DB(0x6F) _DB(0x00)) \
 _STR(_DB(0x0F) _DB(0x0F) _DB(0x02) _DB(0x9A)) \
 _STR(_DB(0x0F) _DB(0x7F) _DB(0x01)) \
 _STR(_DB(0x0F) _DB(0x0E)) \
_END_ASM

/// Вычитание двухмерных векторов одинарной точности, команды SSE.
// не верно заполняется старшая часть!
#define VECTORP2DSUBSSE \
BEGIN_ASM \
ASM( movss xmm0,[eax]) \
ASM( movss xmm1,[eax+4]) \
ASM( movss xmm2,[edx]) \
ASM( movss xmm3,[edx+4]) \
ASM( subss xmm0,xmm2) \
ASM( subss xmm1,xmm3) \
ASM( movss [ecx],xmm0) \
ASM( movss [ecx+4],xmm1) \
END_ASM

/// Вычитание двухмерных векторов одинарной точности, команды SSE2.
#define VECTORP2DSUBSSE2 \
BEGIN_ASM \
ASM( movsd xmm0,[eax]) \
ASM( movsd xmm1,[edx]) \
ASM( subps xmm0,xmm1) \
ASM( movsd [ecx],xmm0) \
END_ASM

/// Вычитание трехмерных векторов одинарной точности, команды FPU.
#define VECTORP3DSUBFPU \
_BEGIN_ASM \
 _STR(_DB(0xD9) _DB(0x00)) \
 _STR(_DB(0xD8) _DB(0x22)) \
 _STR(_DB(0xD9) _DB(0x19)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
 _STR(_DB(0xD8) _DB(0x62) _DB(0x04)) \
 _STR(_DB(0xD9) _DB(0x59) _DB(0x04)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xD8) _DB(0x62) _DB(0x08)) \
 _STR(_DB(0xD9) _DB(0x59) _DB(0x08)) \
_END_ASM

/// Вычитание трехмерных векторов одинарной точности, команды 3DNOW.
#define VECTORP3DSUB3DNOW \
_BEGIN_ASM \
 _STR(_DB(0x0F) _DB(0x6F) _DB(0x00)) \
 _STR(_DB(0x0F) _DB(0x0F) _DB(0x02) _DB(0x9A)) \
 _STR(_DB(0x0F) _DB(0x7F) _DB(0x01)) \
 _STR(_DB(0x0F) _DB(0x6E) _DB(0x48) _DB(0x08)) \
 _STR(_DB(0x0F) _DB(0x0F) _DB(0x4A) _DB(0x08) _DB(0x9A)) \
 _STR(_DB(0x0F) _DB(0x7E) _DB(0x49) _DB(0x08)) \
 _STR(_DB(0x0F) _DB(0x0E)) \
_END_ASM

/// Вычитание трехмерных векторов одинарной точности, команды SSE.
#define VECTORP3DSUBSSE \
BEGIN_ASM \
ASM( movss xmm0,[eax+8]) \
ASM( movss xmm1,[edx+8]) \
ASM( movhps xmm0,[eax]) \
ASM( movhps xmm1,[edx]) \
ASM( subps xmm0,xmm1) \
ASM( movhps [ecx],xmm0) \
ASM( movss [ecx+8],xmm0) \
END_ASM

/// Вычитание четырехмерных векторов одинарной точности, команды FPU.
#define VECTORP4DSUBFPU \
_BEGIN_ASM \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x0C)) \
 _STR(_DB(0xD8) _DB(0x62) _DB(0x0C)) \
 _STR(_DB(0xD9) _DB(0x59) _DB(0x0C)) \
 _STR(_DB(0xD9) _DB(0x00)) \
 _STR(_DB(0xD8) _DB(0x22)) \
 _STR(_DB(0xD9) _DB(0x19)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
 _STR(_DB(0xD8) _DB(0x62) _DB(0x04)) \
 _STR(_DB(0xD9) _DB(0x59) _DB(0x04)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xD8) _DB(0x62) _DB(0x08)) \
 _STR(_DB(0xD9) _DB(0x59) _DB(0x08)) \
_END_ASM

/// Вычитание четырехмерных векторов одинарной точности, команды 3DNOW.
#define VECTORP4DSUB3DNOW \
_BEGIN_ASM \
 _STR(_DB(0x0F) _DB(0x6F) _DB(0x00)) \
 _STR(_DB(0x0F) _DB(0x0F) _DB(0x02) _DB(0x9A)) \
 _STR(_DB(0x0F) _DB(0x7F) _DB(0x01)) \
 _STR(_DB(0x0F) _DB(0x6F) _DB(0x48) _DB(0x08)) \
 _STR(_DB(0x0F) _DB(0x0F) _DB(0x4A) _DB(0x08) _DB(0x9A)) \
 _STR(_DB(0x0F) _DB(0x7F) _DB(0x49) _DB(0x08)) \
 _STR(_DB(0x0F) _DB(0x0E)) \
_END_ASM

/// Вычитание четырехмерных векторов одинарной точности, команды SSE.
#define VECTORP4DSUBSSE \
BEGIN_ASM \
ASM( movhps xmm0,[eax+8]) \
ASM( movhps xmm1,[edx+8]) \
ASM( movlps xmm0,[eax]) \
ASM( movlps xmm1,[edx]) \
ASM( subps xmm0,xmm1) \
ASM( movlps [ecx],xmm0) \
ASM( movhps [ecx+8],xmm0) \
END_ASM

/// Вычитание четырехмерных векторов одинарной точности, команды SSE3.
#define VECTORP4DSUBSSE3 \
BEGIN_ASM \
ASM( lddqu xmm0,[eax]) \
ASM( lddqu xmm1,[edx]) \
ASM( subps xmm0,xmm1) \
ASM( movlps [ecx],xmm0) \
ASM( movhps [ecx+8],xmm0) \
END_ASM

/// Вычитание двухмерных векторов двойной точности, команды FPU.
#define VECTORP2DDSUBFPU \
_BEGIN_ASM \
 _STR(_DB(0xDD) _DB(0x00)) \
 _STR(_DB(0xDC) _DB(0x22)) \
 _STR(_DB(0xDD) _DB(0x19)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x62) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x59) _DB(0x08)) \
_END_ASM

/// Вычитание двухмерных векторов двойной точности, команды SSE2.
#define VECTORP2DDSUBSSE2 \
BEGIN_ASM \
ASM( movsd xmm0,[eax]) \
ASM( movsd xmm1,[eax+8]) \
ASM( movsd xmm4,[edx]) \
ASM( movsd xmm5,[edx+8]) \
ASM( unpcklpd xmm0,xmm1) \
ASM( unpcklpd xmm4,xmm5) \
ASM( subpd xmm0,xmm4) \
ASM( movsd [ecx],xmm0) \
ASM( unpckhpd xmm0,xmm0) \
ASM( movsd [ecx+8],xmm0) \
END_ASM

/// Вычитание двухмерных векторов двойной точности, команды SSE3.
#define VECTORP2DDSUBSSE3 \
BEGIN_ASM \
ASM( lddqu xmm0,[eax]) \
ASM( lddqu xmm1,[edx]) \
ASM( subpd xmm0,xmm1) \
ASM( movsd [ecx],xmm0) \
ASM( unpckhpd xmm0,xmm0) \
ASM( movsd [ecx+8],xmm0) \
END_ASM

/// Вычитание трехмерных векторов двойной точности, команды FPU.
#define VECTORP3DDSUBFPU \
_BEGIN_ASM \
 _STR(_DB(0xDD) _DB(0x00)) \
 _STR(_DB(0xDC) _DB(0x22)) \
 _STR(_DB(0xDD) _DB(0x19)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x62) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x59) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x10)) \
 _STR(_DB(0xDC) _DB(0x62) _DB(0x10)) \
 _STR(_DB(0xDD) _DB(0x59) _DB(0x10)) \
_END_ASM

/// Вычитание трехмерных векторов двойной точности, команды SSE2.
#define VECTORP3DDSUBSSE2 \
BEGIN_ASM \
ASM( movsd xmm2,[eax+16]) \
ASM( movsd xmm0,[eax]) \
ASM( movsd xmm1,[eax+8]) \
ASM( subsd xmm2,[edx+16]) \
ASM( movsd xmm4,[edx]) \
ASM( movsd xmm5,[edx+8]) \
ASM( unpcklpd xmm0,xmm1) \
ASM( unpcklpd xmm4,xmm5) \
ASM( subpd xmm0,xmm4) \
ASM( movsd [ecx],xmm0) \
ASM( unpckhpd xmm0,xmm0) \
ASM( movsd [ecx+16],xmm2) \
ASM( movsd [ecx+8],xmm0) \
END_ASM

/* _STR(_DB(0x0F) _DB(0x10) _DB(0x00)) \
 _STR(_DB(0x0F) _DB(0x10) _DB(0x0A)) \
 _STR(_DB(0x66) _DB(0x0F) _DB(0x5C) _DB(0xC1)) \
 _STR(_DB(0x0F) _DB(0x11) _DB(0x01)) \
 _STR(_DB(0x0F) _DB(0x12) _DB(0x40) _DB(0x10)) \
 _STR(_DB(0x0F) _DB(0x12) _DB(0x4A) _DB(0x10)) \
 _STR(_DB(0x66) _DB(0x0F) _DB(0x5C) _DB(0xC1)) \
 _STR(_DB(0x0F) _DB(0x13) _DB(0x41) _DB(0x10)) \
*/

/// Вычитание трехмерных векторов двойной точности, команды SSE3.
#define VECTORP3DDSUBSSE3 \
BEGIN_ASM \
ASM( lddqu xmm0,[eax]) \
ASM( lddqu xmm4,[edx]) \
ASM( movsd xmm2,[eax+16]) \
ASM( subpd xmm0,xmm4) \
ASM( movsd [ecx],xmm0) \
ASM( subsd xmm2,[edx+16]) \
ASM( unpckhpd xmm0,xmm0) \
ASM( movsd [ecx+16],xmm2) \
ASM( movsd [ecx+8],xmm0) \
END_ASM

/// Вычитание четырехмерных векторов двойной точности, команды FPU.
#define VECTORP4DDSUBFPU \
_BEGIN_ASM \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x18)) \
 _STR(_DB(0xDC) _DB(0x62) _DB(0x18)) \
 _STR(_DB(0xDD) _DB(0x59) _DB(0x18)) \
 _STR(_DB(0xDD) _DB(0x00)) \
 _STR(_DB(0xDC) _DB(0x22)) \
 _STR(_DB(0xDD) _DB(0x19)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x62) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x59) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x10)) \
 _STR(_DB(0xDC) _DB(0x62) _DB(0x10)) \
 _STR(_DB(0xDD) _DB(0x59) _DB(0x10)) \
_END_ASM

/// Вычитание четырехмерных векторов двойной точности, команды SSE2.
#define VECTORP4DDSUBSSE2 \
BEGIN_ASM \
ASM( movsd xmm0,[eax]) \
ASM( subsd xmm0,[edx]) \
ASM( movsd [ecx],xmm0) \
ASM( movsd xmm2,[eax+8]) \
ASM( subsd xmm2,[edx+8]) \
ASM( movsd [ecx+8],xmm2) \
ASM( movsd xmm4,[eax+0x10]) \
ASM( subsd xmm4,[edx+0x10]) \
ASM( movsd [ecx+0x10],xmm4) \
ASM( movsd xmm6,[eax+0x18]) \
ASM( subsd xmm6,[edx+0x18]) \
ASM( movsd [ecx+0x18],xmm6) \
END_ASM

/// Вычитание четырехмерных векторов двойной точности, команды SSE3.
#define VECTORP4DDSUBSSE3 \
BEGIN_ASM \
ASM( lddqu xmm0,[eax]) \
ASM( lddqu xmm1,[edx]) \
ASM( lddqu xmm2,[eax+16]) \
ASM( lddqu xmm3,[edx+16]) \
ASM( subpd xmm0,xmm1) \
ASM( subpd xmm2,xmm3) \
ASM( movsd [ecx],xmm0) \
ASM( movsd [ecx+16],xmm2) \
ASM( unpckhpd xmm0,xmm0) \
ASM( unpckhpd xmm2,xmm2) \
ASM( movsd [ecx+8],xmm0) \
ASM( movsd [ecx+24],xmm2) \
END_ASM

//**************************** ADD C++ FASTCALL *********************************
// subtract vectors ecx-a void *, edx-b void *, eax-rez void *

/// Вычитание двухмерных векторов одинарной точности, команды FPU.
#define VECTORP2DSUBFPU_CPP \
_BEGIN_ASM \
_LINE2(0xD9,0x01) \
_LINE2(0xD8,0x22) \
_LINE2(0xD9,0x18) \
_LINE3(0xD9,0x41,0x04) \
_LINE3(0xD8,0x62,0x04) \
_LINE3(0xD9,0x58,0x04) \
_END_ASM

/// Вычитание двухмерных векторов одинарной точности, команды SSE.
#define VECTORP2DSUBSSE_CPP \
_BEGIN_ASM \
_LINE4( 0xF3,0x0F,0x10,0x01 )                               /* movss       xmm0,dword ptr [ecx]  */ \
_LINE5( 0xF3,0x0F,0x10,0x49,0x04 )                          /* movss       xmm1,dword ptr [ecx+4]  */ \
_LINE4( 0xF3,0x0F,0x10,0x12 )                               /* movss       xmm2,dword ptr [edx]  */ \
_LINE5( 0xF3,0x0F,0x10,0x5A,0x04 )                          /* movss       xmm3,dword ptr [edx+4]  */ \
_LINE4( 0xF3,0x0F,0x5C,0xC2 )                               /* subss       xmm0,xmm2  */ \
_LINE4( 0xF3,0x0F,0x5C,0xCB )                               /* subss       xmm1,xmm3  */ \
_LINE4( 0xF3,0x0F,0x11,0x00 )                               /* movss       dword ptr [eax],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x48,0x04 )                          /* movss       dword ptr [eax+4],xmm1 */ \
_END_ASM

/// Вычитание двухмерных векторов одинарной точности, команды SSE2.
#define VECTORP2DSUBSSE2_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x01 )                               /* movsd       xmm0,mmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,mmword ptr [edx]  */ \
_LINE3( 0x0F,0x5C,0xC1 )                                    /* subps       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x00 )                               /* movsd       mmword ptr [eax],xmm0  */ \
_END_ASM

/// Вычитание трехмерных векторов одинарной точности, команды FPU.
#define VECTORP3DSUBFPU_CPP \
_BEGIN_ASM \
 _STR(_DB(0xD9) _DB(0x01)) \
 _STR(_DB(0xD8) _DB(0x22)) \
 _STR(_DB(0xD9) _DB(0x18)) \
 _STR(_DB(0xD9) _DB(0x41) _DB(0x04)) \
 _STR(_DB(0xD8) _DB(0x62) _DB(0x04)) \
 _STR(_DB(0xD9) _DB(0x58) _DB(0x04)) \
 _STR(_DB(0xD9) _DB(0x41) _DB(0x08)) \
 _STR(_DB(0xD8) _DB(0x62) _DB(0x08)) \
 _STR(_DB(0xD9) _DB(0x58) _DB(0x08)) \
_END_ASM

/// Вычитание трехмерных векторов одинарной точности, команды SSE.
#define VECTORP3DSUBSSE_CPP \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x41,0x08 )                          /* movss       xmm0,dword ptr [ecx+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE3( 0x0F,0x16,0x01 )                                    /* movhps      xmm0,qword ptr [ecx]  */ \
_LINE3( 0x0F,0x16,0x0A )                                    /* movhps      xmm1,qword ptr [edx]  */ \
_LINE3( 0x0F,0x5C,0xC1 )                                    /* subps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x17,0x00 )                                    /* movhps      qword ptr [eax],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x40,0x08 )                          /* movss       dword ptr [eax+8],xmm0  */ \
_END_ASM

/// Вычитание четырехмерных векторов одинарной точности, команды FPU.
#define VECTORP4DSUBFPU_CPP \
_BEGIN_ASM \
_LINE3( 0xD9,0x41,0x0C )                                    /* fld         dword ptr [ecx+0Ch]  */ \
_LINE3( 0xD8,0x62,0x0C )                                    /* fsub        dword ptr [edx+0Ch]  */ \
_LINE3( 0xD9,0x58,0x0C )                                    /* fstp        dword ptr [eax+0Ch]  */ \
_LINE2( 0xD9,0x01 )                                         /* fld         dword ptr [ecx]  */ \
_LINE2( 0xD8,0x22 )                                         /* fsub        dword ptr [edx]  */ \
_LINE2( 0xD9,0x18 )                                         /* fstp        dword ptr [eax]  */ \
_LINE3( 0xD9,0x41,0x04 )                                    /* fld         dword ptr [ecx+4]  */ \
_LINE3( 0xD8,0x62,0x04 )                                    /* fsub        dword ptr [edx+4]  */ \
_LINE3( 0xD9,0x58,0x04 )                                    /* fstp        dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x41,0x08 )                                    /* fld         dword ptr [ecx+8]  */ \
_LINE3( 0xD8,0x62,0x08 )                                    /* fsub        dword ptr [edx+8]  */ \
_LINE3( 0xD9,0x58,0x08 )                                    /* fstp        dword ptr [eax+8]  */ \
_END_ASM

/// Вычитание четырехмерных векторов одинарной точности, команды SSE.
#define VECTORP4DSUBSSE_CPP \
_BEGIN_ASM \
_LINE3( 0x0F,0x12,0x01 )                                    /* movlps      xmm0,qword ptr [ecx]  */ \
_LINE3( 0x0F,0x12,0x0A )                                    /* movlps      xmm1,qword ptr [edx]  */ \
_LINE4( 0x0F,0x16,0x41,0x08 )                               /* movhps      xmm0,qword ptr [ecx+8]  */ \
_LINE4( 0x0F,0x16,0x4A,0x08 )                               /* movhps      xmm1,qword ptr [edx+8]  */ \
_LINE3( 0x0F,0x5C,0xC1 )                                    /* subps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x00 )                                    /* movlps      qword ptr [eax],xmm0  */ \
_LINE4( 0x0F,0x17,0x40,0x08 )                               /* movhps      qword ptr [eax+8],xmm0  */ \
_END_ASM

/// Вычитание четырехмерных векторов одинарной точности, команды SSE3.
#define VECTORP4DSUBSSE3_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE3( 0x0F,0x5C,0xC1 )                                    /* subps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x00 )                                    /* movlps      qword ptr [eax],xmm0  */ \
_LINE4( 0x0F,0x17,0x40,0x08 )                               /* movhps      qword ptr [eax+8],xmm0  */ \
_END_ASM

/// Вычитание двухмерных векторов двойной точности, команды SSE2.
#define VECTORP2DDSUBSSE2_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x01 )                               /* movsd       xmm0,mmword ptr [ecx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x49,0x08 )                          /* movsd       xmm1,mmword ptr [ecx+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x22 )                               /* movsd       xmm4,mmword ptr [edx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x6A,0x08 )                          /* movsd       xmm5,mmword ptr [edx+8]  */ \
_LINE4( 0x66,0x0F,0x14,0xC1 )                               /* unpcklpd    xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x14,0xE5 )                               /* unpcklpd    xmm4,xmm5  */ \
_LINE4( 0x66,0x0F,0x5C,0xC4 )                               /* subpd       xmm0,xmm4  */ \
_LINE4( 0xF2,0x0F,0x11,0x00 )                               /* movsd       mmword ptr [eax],xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x40,0x08 )                          /* movsd       mmword ptr [eax+8],xmm0  */ \
_END_ASM

/// Вычитание трехмерных векторов двойной точности, команды SSE2.
#define VECTORP3DDSUBSSE2_CPP \
_BEGIN_ASM \
_LINE5( 0xF2,0x0F,0x10,0x51,0x10 )                          /* movsd       xmm2,mmword ptr [ecx+10h]  */ \
_LINE4( 0xF2,0x0F,0x10,0x01 )                               /* movsd       xmm0,mmword ptr [ecx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x49,0x08 )                          /* movsd       xmm1,mmword ptr [ecx+8]  */ \
_LINE5( 0xF2,0x0F,0x5C,0x52,0x10 )                          /* subsd       xmm2,mmword ptr [edx+10h]  */ \
_LINE4( 0xF2,0x0F,0x10,0x22 )                               /* movsd       xmm4,mmword ptr [edx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x6A,0x08 )                          /* movsd       xmm5,mmword ptr [edx+8]  */ \
_LINE4( 0x66,0x0F,0x14,0xC1 )                               /* unpcklpd    xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x14,0xE5 )                               /* unpcklpd    xmm4,xmm5  */ \
_LINE4( 0x66,0x0F,0x5C,0xC4 )                               /* subpd       xmm0,xmm4  */ \
_LINE4( 0xF2,0x0F,0x11,0x00 )                               /* movsd       mmword ptr [eax],xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x50,0x10 )                          /* movsd       mmword ptr [eax+10h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x40,0x08 )                          /* movsd       mmword ptr [eax+8],xmm0  */ \
_END_ASM

/// Вычитание трехмерных векторов двойной точности, команды SSE3.
#define VECTORP3DDSUBSSE3_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x51,0x10 )                          /* movsd       xmm2,mmword ptr [ecx+10h]  */ \
_LINE5( 0xF2,0x0F,0x5C,0x52,0x10 )                          /* subsd       xmm2,mmword ptr [edx+10h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x50,0x10 )                          /* movsd       mmword ptr [eax+10h],xmm2  */ \
_LINE4( 0xF2,0x0F,0xF0,0x22 )                               /* lddqu       xmm4,xmmword ptr [edx]  */ \
_LINE4( 0x66,0x0F,0x5C,0xC4 )                               /* subpd       xmm0,xmm4  */ \
_LINE4( 0xF2,0x0F,0x11,0x00 )                               /* movsd       mmword ptr [eax],xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x40,0x08 )                          /* movsd       mmword ptr [eax+8],xmm0  */ \
_END_ASM

/// Вычитание четырехмерных векторов двойной точности, команды SSE2.
#define VECTORP4DDSUBSSE2_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x01 )                               /* movsd       xmm0,mmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0x5C,0x02 )                               /* subsd       xmm0,mmword ptr [edx]  */ \
_LINE4( 0xF2,0x0F,0x11,0x00 )                               /* movsd       mmword ptr [eax],xmm0  */ \
_LINE5( 0xF2,0x0F,0x10,0x51,0x08 )                          /* movsd       xmm2,mmword ptr [ecx+8]  */ \
_LINE5( 0xF2,0x0F,0x5C,0x52,0x08 )                          /* subsd       xmm2,mmword ptr [edx+8]  */ \
_LINE5( 0xF2,0x0F,0x11,0x50,0x08 )                          /* movsd       mmword ptr [eax+8],xmm2  */ \
_LINE5( 0xF2,0x0F,0x10,0x61,0x10 )                          /* movsd       xmm4,mmword ptr [ecx+10h]  */ \
_LINE5( 0xF2,0x0F,0x5C,0x62,0x10 )                          /* subsd       xmm4,mmword ptr [edx+10h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x60,0x10 )                          /* movsd       mmword ptr [eax+10h],xmm4  */ \
_LINE5( 0xF2,0x0F,0x10,0x71,0x18 )                          /* movsd       xmm6,mmword ptr [ecx+18h]  */ \
_LINE5( 0xF2,0x0F,0x5C,0x72,0x18 )                          /* subsd       xmm6,mmword ptr [edx+18h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x70,0x18 )                          /* movsd       mmword ptr [eax+18h],xmm6  */ \
_END_ASM

/// Вычитание четырехмерных векторов двойной точности, команды SSE3.
#define VECTORP4DDSUBSSE3_CPP \
_BEGIN_ASM \
_LINE5( 0xF2,0x0F,0xF0,0x51,0x10 )                          /* lddqu       xmm2,xmmword ptr [ecx+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x5A,0x10 )                          /* lddqu       xmm3,xmmword ptr [edx+10h]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x66,0x0F,0x5C,0xD3 )                               /* subpd       xmm2,xmm3  */ \
_LINE4( 0x66,0x0F,0x5C,0xC1 )                               /* subpd       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x00 )                               /* movsd       mmword ptr [eax],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x50,0x10 )                          /* movsd       mmword ptr [eax+10h],xmm2  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xD2 )                               /* unpckhpd    xmm2,xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x40,0x08 )                          /* movsd       mmword ptr [eax+8],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x50,0x18 )                          /* movsd       mmword ptr [eax+18h],xmm2  */ \
_END_ASM

#endif