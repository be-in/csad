//=============================================================================
///**
// *  @file vector_add.h
// *
// *  $Id: vector_add.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float addition, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_VECTOR_ADD_H
#define GEN3_VECTOR_ADD_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** ADD STDCALL *********************************
// addition vectors eax=[esp+4]-a void *, edx=[esp+8]-b void *, ecx=[esp+12]-rez void *

/// Сложение четырехмерных байтовых векторов, команды CPU.
/// @brief for CPUTYPE3
#define VECTORP4BADDCPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
ASM( add al,dl ) \
ASM( cmovc al,0xFF ) \
ASM( add ah,dh ) \
ASM( cmovc ah,0xFF ) \
ASM( ror edx,16 ) \
ASM( ror eax,16 ) \
ASM( add al,dl ) \
ASM( cmovc al,0xFF ) \
ASM( add ah,dh ) \
ASM( cmovc ah,0xFF ) \
ASM( rol eax,16 ) \
_END_ASM

/// Сложение двухмерных целочисленных векторов, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP2IADDSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,mmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE4( 0x66,0x0F,0xFE,0xC1 )                               /* paddd       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_END_ASM

/// Сложение трехмерных целочисленных векторов, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP3IADDSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE4( 0x66,0x0F,0x16,0x00 )                               /* movhpd      xmm0,qword ptr [eax]  */ \
_LINE4( 0x66,0x0F,0x16,0x0A )                               /* movhpd      xmm1,qword ptr [edx]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+12]  */ \
_LINE4( 0x66,0x0F,0xFE,0xC1 )                               /* paddd       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x17,0x00 )                               /* movhpd      qword ptr [eax],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x40,0x08 )                          /* movss       dword ptr [eax+8],xmm0  */ \
_END_ASM

/// Сложение четырехмерных целочисленных векторов, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP4IADDSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )                               /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x16,0x4A,0x08 )                               /* movhps      xmm1,qword ptr [edx+8]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x12,0x00 )                                    /* movlps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x12,0x0A )                                    /* movlps      xmm1,qword ptr [edx]  */ \
_LINE4( 0x66,0x0F,0xFE,0xC1 )                               /* paddd       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x01 )                                    /* movlps      qword ptr [ecx],xmm0  */ \
_LINE4( 0x0F,0x17,0x41,0x08 )                               /* movhps      qword ptr [ecx+8],xmm0 */ \
_END_ASM

/// Сложение четырехмерных целочисленных векторов, команды SSE4.
/// @brief for CPUTYPE3
#define VECTORP4IADDSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE4( 0x66,0x0F,0xFE,0xC1 )                               /* paddd       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_END_ASM

/// Сложение двухмерных векторов одинарной точности, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP2DADDFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 ) \
_LINE2( 0xD9,0x00 ) \
_LINE4( 0x8B,0x54,0x24,0x08 ) \
_LINE2( 0xD8,0x02 ) \
_LINE4( 0x8B,0x4C,0x24,0x0C ) \
_LINE2( 0xD9,0x19 ) \
_LINE3( 0xD9,0x40,0x04 ) \
_LINE3( 0xD8,0x42,0x04 ) \
_LINE3( 0xD9,0x59,0x04 ) \
_END_ASM

/// Сложение двухмерных векторов одинарной точности, команды 3DNOW.
/// @brief for CPUTYPE2
#define VECTORP2DADD3DNOW_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 ) \
_LINE3( 0x0F,0x6F,0x00 ) \
_LINE4( 0x8B,0x54,0x24,0x08 ) \
_LINE4( 0x0F,0x0F,0x02,0x9E ) \
_LINE4( 0x8B,0x4C,0x24,0x0C ) \
_LINE3( 0x0F,0x7F,0x01 ) \
_LINE2( 0x0F,0x0E ) \
_END_ASM

/// Сложение двухмерных векторов одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP2DADDSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF3,0x0F,0x10,0x00 )                               /* movss       xmm0,dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
ASM( addss xmm0,dword ptr [edx] ) \
ASM( addss xmm1,dword ptr [edx+4] ) \
_LINE4( 0xF3,0x0F,0x11,0x01 )                               /* movss       dword ptr [ecx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x49,0x04 )                          /* movss       dword ptr [ecx+4],xmm1  */ \
_END_ASM

/// Сложение двухмерных векторов одинарной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP2DADDSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,mmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_END_ASM

/// Сложение трехмерных векторов одинарной точности, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP3DADDFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xD8,0x02 )                                         /* fadd        dword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE2( 0xD9,0x19 )                                         /* fstp        dword ptr [ecx]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x42,0x04 )                                    /* fadd        dword ptr [edx+4]  */ \
_LINE3( 0xD9,0x59,0x04 )                                    /* fstp        dword ptr [ecx+4]  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD8,0x42,0x08 )                                    /* fadd        dword ptr [edx+8]  */ \
_LINE3( 0xD9,0x59,0x08 )                                    /* fstp        dword ptr [ecx+8]  */ \
_END_ASM

/// Сложение трехмерных векторов одинарной точности, команды 3DNOW.
/// @brief for CPUTYPE2
#define VECTORP3DADD3DNOW_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE3( 0x0F,0x6F,0x00 )                                    /* movq        mm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x0F,0x02,0x9E )                               /* pfadd       mm0,mmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x7F,0x01 )                                    /* movq        mmword ptr [ecx],mm0  */ \
_LINE4( 0x0F,0x6E,0x48,0x08 )                               /* movd        mm1,dword ptr [eax+8]  */ \
_LINE5( 0x0F,0x0F,0x4A,0x08,0x9E )                          /* pfadd       mm1,mmword ptr [edx+8]  */ \
_LINE4( 0x0F,0x7E,0x49,0x08 )                               /* movd        dword ptr [ecx+8],mm1  */ \
_LINE2( 0x0F,0x0E )                                         /* femms  */ \
_END_ASM

/// Сложение трехмерных векторов одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP3DADDSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE3( 0x0F,0x16,0x00 )                                    /* movhps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x16,0x0A )                                    /* movhps      xmm1,qword ptr [edx]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x17,0x00 )                                    /* movhps      qword ptr [eax],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x40,0x08 )                          /* movss       dword ptr [eax+8],xmm0  */ \
_END_ASM

/// Сложение трехмерных векторов одинарной точности, команды SSE2. - не эфективно по сравнению с SSE
/// @brief for CPUTYPE3
#define VECTORP3DADDSSE2_STD \
_BEGIN_ASM \
ASM( xorps xmm0,xmm0 ) \
ASM( xorps xmm1,xmm1 ) \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x12,0x00 )                                    /* movlps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x12,0x0A )                                    /* movlps      xmm1,qword ptr [edx]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x00 )                                    /* movlps      qword ptr [eax],xmm0  */ \
_LINE3( 0xD8,0x42,0x08 )                                    /* fadd        dword ptr [edx+8]  */ \
_LINE3( 0xD9,0x58,0x08 )                                    /* fstp        dword ptr [eax+8]  */ \
_END_ASM

/// Сложение трехмерных векторов одинарной точности, команды SSE2. - не эфективно по сравнению с SSE
/// @brief for CPUTYPE3
#define VECTORP3DADDSSE2_STD1 \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE4( 0x66,0x0F,0x16,0x00 )                               /* movhpd      xmm0,qword ptr [eax]  */ \
_LINE4( 0x66,0x0F,0x16,0x0A )                               /* movhpd      xmm1,qword ptr [edx]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x17,0x00 )                               /* movhpd      qword ptr [eax],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x40,0x08 )                          /* movss       dword ptr [eax+8],xmm0  */ \
_END_ASM

/// Сложение четырехмерных векторов одинарной точности, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP4DADDFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x0C)) \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
 _STR(_DB(0xD8) _DB(0x42) _DB(0x0C)) \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
 _STR(_DB(0xD9) _DB(0x59) _DB(0x0C)) \
 _STR(_DB(0xD9) _DB(0x00)) \
 _STR(_DB(0xD8) _DB(0x02)) \
 _STR(_DB(0xD9) _DB(0x19)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
 _STR(_DB(0xD8) _DB(0x42) _DB(0x04)) \
 _STR(_DB(0xD9) _DB(0x59) _DB(0x04)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xD8) _DB(0x42) _DB(0x08)) \
 _STR(_DB(0xD9) _DB(0x59) _DB(0x08)) \
_END_ASM \

/// Сложение четырехмерных векторов одинарной точности, команды 3DNOW.
/// @brief for CPUTYPE2
#define VECTORP4DADD3DNOW_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
 _STR(_DB(0x0F) _DB(0x6F) _DB(0x00)) \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
 _STR(_DB(0x0F) _DB(0x0F) _DB(0x02) _DB(0x9E)) \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
 _STR(_DB(0x0F) _DB(0x7F) _DB(0x01)) \
 _STR(_DB(0x0F) _DB(0x6F) _DB(0x48) _DB(0x08)) \
 _STR(_DB(0x0F) _DB(0x0F) _DB(0x4A) _DB(0x08) _DB(0x9E)) \
 _STR(_DB(0x0F) _DB(0x7F) _DB(0x49) _DB(0x08)) \
 _STR(_DB(0x0F) _DB(0x0E)) \
_END_ASM

/// Сложение четырехмерных векторов одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP4DADDSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF3,0x0F,0x10,0x00 )                               /* movss       xmm0,dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE5( 0xF3,0x0F,0x10,0x50,0x08 )                          /* movss       xmm2,dword ptr [eax+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x0C )                          /* movss       xmm3,dword ptr [eax+12]  */ \
ASM( addss xmm0,dword ptr [edx] ) \
ASM( addss xmm1,dword ptr [edx+4] ) \
ASM( addss xmm2,dword ptr [edx+8] ) \
ASM( addss xmm3,dword ptr [edx+12] ) \
_LINE4( 0xF3,0x0F,0x11,0x01 )                               /* movss       dword ptr [ecx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x49,0x04 )                          /* movss       dword ptr [ecx+4],xmm1  */ \
_LINE5( 0xF3,0x0F,0x11,0x51,0x08 )                          /* movss       dword ptr [ecx+8],xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x59,0x0C )                          /* movss       dword ptr [ecx+12],xmm3  */ \
_END_ASM

/// Сложение четырехмерных векторов одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP4DADDSSE_STD1 \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )                               /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x16,0x4A,0x08 )                               /* movhps      xmm1,qword ptr [edx+8]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x12,0x00 )                                    /* movlps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x12,0x0A )                                    /* movlps      xmm1,qword ptr [edx]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x01 )                                    /* movlps      qword ptr [ecx],xmm0  */ \
_LINE4( 0x0F,0x17,0x41,0x08 )                               /* movhps      qword ptr [ecx+8],xmm0 */ \
_END_ASM

/// Сложение четырехмерных векторов одинарной точности, команды SSE3.
/// @brief for CPUTYPE3
#define VECTORP4DADDSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0x66,0x0F,0x17,0x41,0x08 )                          /* movhpd      qword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Сложение четырехмерных векторов одинарной точности, команды SSE4.
/// @brief for CPUTYPE4
#define VECTORP4DADDSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_END_ASM

/// Сложение двухмерных векторов двойной точности, команды FPU.
#define VECTORP2DDADDFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xDD,0x00 )                                         /* fld         qword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xDC,0x02 )                                         /* fadd        qword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE2( 0xDD,0x19 )                                         /* fstp        qword ptr [ecx]  */ \
_LINE3( 0xDD,0x40,0x08 )                                    /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDC,0x42,0x08 )                                    /* fadd        qword ptr [edx+8]  */ \
_LINE3( 0xDD,0x59,0x08 )                                    /* fstp        qword ptr [ecx+8]  */ \
_END_ASM

/// Сложение двухмерных векторов двойной точности, команды SSE2.
#define VECTORP2DDADDSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x08 )                          /* movsd       xmm1,mmword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE5( 0xF2,0x0F,0x58,0x4A,0x08 )                          /* addsd       xmm1,mmword ptr [edx+8]  */ \
_LINE4( 0xF2,0x0F,0x58,0x02 )                               /* addsd       xmm0,mmword ptr [edx]  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x49,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm1 */ \
_END_ASM

/// Сложение двухмерных векторов двойной точности, команды SSE3.
#define VECTORP2DDADDSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE4( 0x66,0x0F,0x58,0xC1 )                               /* addpd       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Сложение двухмерных векторов двойной точности, команды SSE4.
#define VECTORP2DDADDSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE4( 0x66,0x0F,0x58,0xC1 )                               /* addpd       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_END_ASM

/// Сложение трехмерных векторов двойной точности, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP3DDADDFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
 _STR(_DB(0xDD) _DB(0x00)) \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
 _STR(_DB(0xDC) _DB(0x02)) \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
 _STR(_DB(0xDD) _DB(0x19)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x42) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x59) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x10)) \
 _STR(_DB(0xDC) _DB(0x42) _DB(0x10)) \
 _STR(_DB(0xDD) _DB(0x59) _DB(0x10)) \
_END_ASM

/// Сложение трехмерных векторов двойной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP3DDADDSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x08 )                          /* movsd       xmm1,mmword ptr [eax+8]  */ \
_LINE5( 0xF2,0x0F,0x58,0x52,0x10 )                          /* addsd       xmm2,mmword ptr [edx+10h]  */ \
_LINE4( 0xF2,0x0F,0x10,0x22 )                               /* movsd       xmm4,mmword ptr [edx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x6A,0x08 )                          /* movsd       xmm5,mmword ptr [edx+8]  */ \
_LINE4( 0x66,0x0F,0x14,0xC1 )                               /* unpcklpd    xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x14,0xE5 )                               /* unpcklpd    xmm4,xmm5  */ \
_LINE4( 0x66,0x0F,0x58,0xC4 )                               /* addpd       xmm0,xmm4  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xC1 )                               /* unpckhpd    xmm0,xmm1  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Сложение трехмерных векторов двойной точности, команды SSE3.
/// @brief for CPUTYPE3
#define VECTORP3DDADDSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x22 )                               /* lddqu       xmm4,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE4( 0x66,0x0F,0x58,0xC4 )                               /* addpd       xmm0,xmm4  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x58,0x52,0x10 )                          /* addsd       xmm2,mmword ptr [edx+10h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_LINE4( 0x66,0x0F,0x15,0xC1 )                               /* unpckhpd    xmm0,xmm1  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Сложение трехмерных векторов двойной точности, команды SSE4.
/// @brief for CPUTYPE4
#define VECTORP3DDADDSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x22 )                               /* lddqu       xmm4,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE4( 0x66,0x0F,0x58,0xC4 )                               /* addpd       xmm0,xmm4  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x58,0x52,0x10 )                          /* addsd       xmm2,mmword ptr [edx+10h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_END_ASM

/// Сложение трехмерных векторов двойной точности, команды AVX
#define VECTORP3DDADDAVX_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )           /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xC5,0xFB,0x10,0x40,0x10 )      /* vmovsd      xmm0,qword ptr [eax+10h]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )           /* mov         edx,dword ptr [esp+8]  */ \
_LINE5( 0xC5,0xFB,0x10,0x4A,0x10 )      /* vmovsd      xmm1,qword ptr [edx+10h]  */ \
_LINE6( 0xC4,0xE3,0x7D,0x18,0x00,0x01 ) /* vinsertf128 ymm0,ymm0,xmmword ptr [eax],1  */ \
_LINE6( 0xC4,0xE3,0x75,0x18,0x0A,0x01 ) /* vinsertf128 ymm1,ymm1,xmmword ptr [edx],1  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )           /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE4( 0xC5,0xF5,0x58,0xD8 )           /* vaddpd      ymm3,ymm1,ymm0  */ \
_LINE6( 0xC4,0xE3,0x7D,0x19,0xDA,0x01 ) /* vextractf128 xmm2,ymm3,1  */ \
_LINE4( 0xC5,0xF9,0x11,0x10 )           /* vmovupd     xmmword ptr [eax],xmm2  */ \
_LINE5( 0xC5,0xFB,0x11,0x58,0x10 )      /* vmovsd      qword ptr [eax+10h],xmm3  */ \
_LINE3( 0xC5,0xF8,0x77 )                /* vzeroupper  */ \
_END_ASM

/// Сложение четырехмерных векторов двойной точности, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP4DDADDFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE3( 0xDD,0x40,0x18 )                                    /* fld         qword ptr [eax+18h]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0xDC,0x42,0x18 )                                    /* fadd        qword ptr [edx+18h]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE3( 0xDD,0x59,0x18 )                                    /* fstp        qword ptr [ecx+18h]  */ \
_LINE2( 0xDD,0x00 )                                         /* fld         qword ptr [eax]  */ \
_LINE2( 0xDC,0x02 )                                         /* fadd        qword ptr [edx]  */ \
_LINE2( 0xDD,0x19 )                                         /* fstp        qword ptr [ecx]  */ \
_LINE3( 0xDD,0x40,0x08 )                                    /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDC,0x42,0x08 )                                    /* fadd        qword ptr [edx+8]  */ \
_LINE3( 0xDD,0x59,0x08 )                                    /* fstp        qword ptr [ecx+8]  */ \
_LINE3( 0xDD,0x40,0x10 )                                    /* fld         qword ptr [eax+10h]  */ \
_LINE3( 0xDC,0x42,0x10 )                                    /* fadd        qword ptr [edx+10h]  */ \
_LINE3( 0xDD,0x59,0x10 )                                    /* fstp        qword ptr [ecx+10h]  */ \
_END_ASM

/// Сложение четырехмерных векторов двойной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP4DDADDSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x58,0x02 )                               /* addsd       xmm0,mmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x08 )                          /* movsd       xmm2,mmword ptr [eax+8]  */ \
_LINE5( 0xF2,0x0F,0x58,0x52,0x08 )                          /* addsd       xmm2,mmword ptr [edx+8]  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm2  */ \
_LINE5( 0xF2,0x0F,0x10,0x60,0x10 )                          /* movsd       xmm4,mmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0x58,0x62,0x10 )                          /* addsd       xmm4,mmword ptr [edx+10h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x61,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm4  */ \
_LINE5( 0xF2,0x0F,0x10,0x70,0x18 )                          /* movsd       xmm6,mmword ptr [eax+18h]  */ \
_LINE5( 0xF2,0x0F,0x58,0x72,0x18 )                          /* addsd       xmm6,mmword ptr [edx+18h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x71,0x18 )                          /* movsd       mmword ptr [ecx+18h],xmm6  */ \
_END_ASM

/// Сложение четырехмерных векторов двойной точности, команды SSE3.
/// @brief for CPUTYPE3
#define VECTORP4DDADDSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x50,0x10 )                          /* lddqu       xmm2,xmmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x5A,0x10 )                          /* lddqu       xmm3,xmmword ptr [edx+10h]  */ \
_LINE4( 0x66,0x0F,0x58,0xC1 )                               /* addpd       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x58,0xD3 )                               /* addpd       xmm2,xmm3  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xD2 )                               /* unpckhpd    xmm2,xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x18 )                          /* movsd       mmword ptr [ecx+18h],xmm2  */ \
_END_ASM

/// Сложение четырехмерных векторов двойной точности, команды SSE4.
/// @brief for CPUTYPE4
#define VECTORP4DDADDSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x50,0x10 )                          /* lddqu       xmm2,xmmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x5A,0x10 )                          /* lddqu       xmm3,xmmword ptr [edx+10h]  */ \
_LINE4( 0x66,0x0F,0x58,0xC1 )                               /* addpd       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x58,0xD3 )                               /* addpd       xmm2,xmm3  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_LINE5( 0x66,0x0F,0x11,0x51,0x10 )                          /* movupd      xmmword ptr [ecx+10h],xmm2  */ \
_END_ASM

/// Сложение четырехмерных векторов двойной точности, команды AVX
#define VECTORP4DDADDAVX_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )         /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xC5,0xFD,0x10,0x00 )         /* vmovupd     ymm0,ymmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )         /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xC5,0xFD,0x10,0x0A )         /* vmovupd     ymm1,ymmword ptr [edx]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )         /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE4( 0xC5,0xF5,0x58,0xD8 )         /* vaddpd      ymm3,ymm1,ymm0  */ \
_LINE4( 0xC5,0xFD,0x11,0x18 )         /* vmovupd     ymmword ptr [eax],ymm3  */ \
_LINE3( 0xC5,0xF8,0x77 )              /* vzeroupper  */ \
_END_ASM

//**************************** ADD REGISTER FASTCALL *********************************
// addition vectors eax-a void *, edx-b void *, ecx-rez void *

/// Сложение двухмерных векторов одинарной точности, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP2DADDFPU \
_BEGIN_ASM \
 _STR(_DB(0xD9) _DB(0x00)) \
 _STR(_DB(0xD8) _DB(0x02)) \
 _STR(_DB(0xD9) _DB(0x19)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
 _STR(_DB(0xD8) _DB(0x42) _DB(0x04)) \
 _STR(_DB(0xD9) _DB(0x59) _DB(0x04)) \
_END_ASM

/// Сложение двухмерных векторов одинарной точности, команды 3DNOW.
/// @brief for CPUTYPE2
#define VECTORP2DADD3DNOW \
_BEGIN_ASM \
_LINE3(0x0F,0x6F,0x00)        /* movq        mm0,mmword ptr [eax] */  \
_LINE4(0x0F,0x0F,0x02,0x9E)   /* pfadd       mm0,mmword ptr [edx] */  \
_LINE3(0x0F,0x7F,0x01)        /* movq        mmword ptr [ecx],mm0 */  \
_LINE2(0x0F,0x0E)             /* femms */  \
_END_ASM

/// Сложение двухмерных векторов одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP2DADDSSE \
_BEGIN_ASM \
_LINE4( 0xF3,0x0F,0x10,0x00 )                               /* movss       xmm0,dword ptr [eax]  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0xF3,0x0F,0x10,0x12 )                               /* movss       xmm2,dword ptr [edx]  */ \
_LINE5( 0xF3,0x0F,0x10,0x5A,0x04 )                          /* movss       xmm3,dword ptr [edx+4]  */ \
_LINE4( 0xF3,0x0F,0x58,0xC2 )                               /* addss       xmm0,xmm2  */ \
_LINE4( 0xF3,0x0F,0x58,0xCB )                               /* addss       xmm1,xmm3  */ \
_LINE4( 0xF3,0x0F,0x11,0x01 )                               /* movss       dword ptr [ecx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x49,0x04 )                          /* movss       dword ptr [ecx+4],xmm1  */ \
_END_ASM

/// Сложение двухмерных векторов одинарной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP2DADDSSE2 \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,mmword ptr [edx]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_END_ASM

/// Сложение трехмерных векторов одинарной точности, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP3DADDFPU \
_BEGIN_ASM \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0x02 )                                         /* fadd        dword ptr [edx]  */ \
_LINE2( 0xD9,0x19 )                                         /* fstp        dword ptr [ecx]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x42,0x04 )                                    /* fadd        dword ptr [edx+4]  */ \
_LINE3( 0xD9,0x59,0x04 )                                    /* fstp        dword ptr [ecx+4]  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD8,0x42,0x08 )                                    /* fadd        dword ptr [edx+8]  */ \
_LINE3( 0xD9,0x59,0x08 )                                    /* fstp        dword ptr [ecx+8]  */ \
_END_ASM

/// Сложение трехмерных векторов одинарной точности, команды 3DNOW.
/// @brief for CPUTYPE2
#define VECTORP3DADD3DNOW \
_BEGIN_ASM \
_LINE3( 0x0F,0x6F,0x00 )                                    /* movq        mm0,mmword ptr [eax]  */ \
_LINE4( 0x0F,0x0F,0x02,0x9E )                               /* pfadd       mm0,mmword ptr [edx]  */ \
_LINE3( 0x0F,0x7F,0x01 )                                    /* movq        mmword ptr [ecx],mm0  */ \
_LINE4( 0x0F,0x6E,0x48,0x08 )                               /* movd        mm1,dword ptr [eax+8]  */ \
_LINE5( 0x0F,0x0F,0x4A,0x08,0x9E )                          /* pfadd       mm1,mmword ptr [edx+8]  */ \
_LINE4( 0x0F,0x7E,0x49,0x08 )                               /* movd        dword ptr [ecx+8],mm1  */ \
_LINE2( 0x0F,0x0E )                                         /* femms  */ \
_END_ASM

/// Сложение трехмерных векторов одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP3DADDSSE \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE3( 0x0F,0x16,0x00 )                                    /* movhps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x16,0x0A )                                    /* movhps      xmm1,qword ptr [edx]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x17,0x01 )                                    /* movhps      qword ptr [ecx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x41,0x08 )                          /* movss       dword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Сложение трехмерных векторов одинарной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP3DADDSSE2 \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE4( 0x66,0x0F,0x16,0x00 )                               /* movhpd      xmm0,qword ptr [eax]  */ \
_LINE4( 0x66,0x0F,0x16,0x0A )                               /* movhpd      xmm1,qword ptr [edx]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x17,0x01 )                               /* movhpd      qword ptr [ecx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x41,0x08 )                          /* movss       dword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Сложение четырехмерных векторов одинарной точности, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP4DADDFPU \
_BEGIN_ASM \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x0C)) \
 _STR(_DB(0xD8) _DB(0x42) _DB(0x0C)) \
 _STR(_DB(0xD9) _DB(0x59) _DB(0x0C)) \
 _STR(_DB(0xD9) _DB(0x00)) \
 _STR(_DB(0xD8) _DB(0x02)) \
 _STR(_DB(0xD9) _DB(0x19)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
 _STR(_DB(0xD8) _DB(0x42) _DB(0x04)) \
 _STR(_DB(0xD9) _DB(0x59) _DB(0x04)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xD8) _DB(0x42) _DB(0x08)) \
 _STR(_DB(0xD9) _DB(0x59) _DB(0x08)) \
_END_ASM \

/// Сложение четырехмерных векторов одинарной точности, команды 3DNOW.
/// @brief for CPUTYPE2
#define VECTORP4DADD3DNOW \
_BEGIN_ASM \
 _STR(_DB(0x0F) _DB(0x6F) _DB(0x00)) \
 _STR(_DB(0x0F) _DB(0x0F) _DB(0x02) _DB(0x9E)) \
 _STR(_DB(0x0F) _DB(0x7F) _DB(0x01)) \
 _STR(_DB(0x0F) _DB(0x6F) _DB(0x48) _DB(0x08)) \
 _STR(_DB(0x0F) _DB(0x0F) _DB(0x4A) _DB(0x08) _DB(0x9E)) \
 _STR(_DB(0x0F) _DB(0x7F) _DB(0x49) _DB(0x08)) \
 _STR(_DB(0x0F) _DB(0x0E)) \
_END_ASM

/// Сложение четырехмерных векторов одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP4DADDSSE \
_BEGIN_ASM \
_LINE4( 0x0F,0x16,0x40,0x08 )                               /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE4( 0x0F,0x16,0x4A,0x08 )                               /* movhps      xmm1,qword ptr [edx+8]  */ \
_LINE3( 0x0F,0x12,0x00 )                                    /* movlps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x12,0x0A )                                    /* movlps      xmm1,qword ptr [edx]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x01 )                                    /* movlps      qword ptr [ecx],xmm0  */ \
_LINE4( 0x0F,0x17,0x41,0x08 )                               /* movhps      qword ptr [ecx+8],xmm0 */ \
_END_ASM

/// Сложение четырехмерных векторов одинарной точности, команды SSE3.
/// @brief for CPUTYPE3
#define VECTORP4DADDSSE3 \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0x66,0x0F,0x17,0x41,0x08 )                          /* movhpd      qword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Сложение четырехмерных векторов одинарной точности, команды SSE4.
/// @brief for CPUTYPE4
#define VECTORP4DADDSSE4 \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_END_ASM

/// Сложение двухмерных векторов двойной точности, команды FPU.
#define VECTORP2DDADDFPU \
_BEGIN_ASM \
_LINE2( 0xDD,0x00 )                                         /* fld         qword ptr [eax]  */ \
_LINE2( 0xDC,0x02 )                                         /* fadd        qword ptr [edx]  */ \
_LINE2( 0xDD,0x19 )                                         /* fstp        qword ptr [ecx]  */ \
_LINE3( 0xDD,0x40,0x08 )                                    /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDC,0x42,0x08 )                                    /* fadd        qword ptr [edx+8]  */ \
_LINE3( 0xDD,0x59,0x08 )                                    /* fstp        qword ptr [ecx+8]  */ \
_END_ASM

/// Сложение двухмерных векторов двойной точности, команды SSE2.
#define VECTORP2DDADDSSE2 \
_BEGIN_ASM \
_LINE5( 0xF2,0x0F,0x10,0x48,0x08 )                          /* movsd       xmm1,mmword ptr [eax+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0x58,0x4A,0x08 )                          /* addsd       xmm1,mmword ptr [edx+8]  */ \
_LINE4( 0xF2,0x0F,0x58,0x02 )                               /* addsd       xmm0,mmword ptr [edx]  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x49,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm1 */ \
_END_ASM

/// Сложение двухмерных векторов двойной точности, команды SSE3.
#define VECTORP2DDADDSSE3 \
_BEGIN_ASM \
_LINE5( 0xF2,0x0F,0x10,0x48,0x08 )                          /* movsd       xmm1,mmword ptr [eax+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0x58,0x4A,0x08 )                          /* addsd       xmm1,mmword ptr [edx+8]  */ \
_LINE4( 0xF2,0x0F,0x58,0x02 )                               /* addsd       xmm0,mmword ptr [edx]  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x49,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm1 */ \
_END_ASM

/*
_ASM lddqu xmm0,[eax] \
_ASM lddqu xmm1,[edx] \
_ASM addpd xmm0,xmm1 \
_ASM movsd [ecx],xmm0 \
_ASM movhpd [ecx+8],xmm0 \
*/

/// Сложение двухмерных векторов двойной точности, команды SSE4.
#define VECTORP2DDADDSSE4 \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x66,0x0F,0x58,0xC1 )                               /* addpd       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_END_ASM

/// Сложение трехмерных векторов двойной точности, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP3DDADDFPU \
_BEGIN_ASM \
 _STR(_DB(0xDD) _DB(0x00)) \
 _STR(_DB(0xDC) _DB(0x02)) \
 _STR(_DB(0xDD) _DB(0x19)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x42) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x59) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x10)) \
 _STR(_DB(0xDC) _DB(0x42) _DB(0x10)) \
 _STR(_DB(0xDD) _DB(0x59) _DB(0x10)) \
_END_ASM

/// Сложение трехмерных векторов двойной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP3DDADDSSE2 \
_BEGIN_ASM \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x08 )                          /* movsd       xmm1,mmword ptr [eax+8]  */ \
_LINE5( 0xF2,0x0F,0x58,0x52,0x10 )                          /* addsd       xmm2,mmword ptr [edx+10h]  */ \
_LINE4( 0xF2,0x0F,0x10,0x22 )                               /* movsd       xmm4,mmword ptr [edx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x6A,0x08 )                          /* movsd       xmm5,mmword ptr [edx+8]  */ \
_LINE4( 0x66,0x0F,0x14,0xC1 )                               /* unpcklpd    xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x14,0xE5 )                               /* unpcklpd    xmm4,xmm5  */ \
_LINE4( 0x66,0x0F,0x58,0xC4 )                               /* addpd       xmm0,xmm4  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xC1 )                               /* unpckhpd    xmm0,xmm1  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Сложение трехмерных векторов двойной точности, команды SSE3. ???
/// @brief for CPUTYPE3
#define VECTORP3DDADDSSE3 \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x22 )                               /* lddqu       xmm4,xmmword ptr [edx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE4( 0x66,0x0F,0x58,0xC4 )                               /* addpd       xmm0,xmm4  */ \
_LINE5( 0xF2,0x0F,0x58,0x52,0x10 )                          /* addsd       xmm2,mmword ptr [edx+10h]  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xC1 )                               /* unpckhpd    xmm0,xmm1  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Сложение трехмерных векторов двойной точности, команды SSE3.
/// @brief for CPUTYPE3
#define VECTORP3DDADDARRAYSSE3 \
BEGIN_ASM \
ASM(lddqu xmm0,[eax]) \
ASM(lddqu xmm4,[edx]) \
ASM(movsd xmm2,[eax+16]) \
ASM(addpd xmm0,xmm4) \
ASM(movsd [ecx],xmm0) \
ASM(unpckhpd xmm0,xmm1) \
ASM(addsd xmm2,[edx+16]) \
ASM(movsd [ecx+16],xmm2) \
ASM(movsd [ecx+8],xmm0) \
END_ASM

/// Сложение трехмерных векторов двойной точности, команды SSE4.
/// @brief for CPUTYPE4
#define VECTORP3DDADDSSE4 \
BEGIN_ASM \
ASM(lddqu xmm0,[eax]) \
ASM(lddqu xmm4,[edx]) \
ASM(addpd xmm0,xmm4) \
ASM(movsd xmm2,[eax+16]) \
ASM(movupd [ecx],xmm0) \
ASM(addsd xmm2,[edx+16]) \
ASM(movsd [ecx+16],xmm2) \
END_ASM

/// Сложение четырехмерных векторов двойной точности, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP4DDADDFPU \
_BEGIN_ASM \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x18)) \
 _STR(_DB(0xDC) _DB(0x42) _DB(0x18)) \
 _STR(_DB(0xDD) _DB(0x59) _DB(0x18)) \
 _STR(_DB(0xDD) _DB(0x00)) \
 _STR(_DB(0xDC) _DB(0x02)) \
 _STR(_DB(0xDD) _DB(0x19)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x42) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x59) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x10)) \
 _STR(_DB(0xDC) _DB(0x42) _DB(0x10)) \
 _STR(_DB(0xDD) _DB(0x59) _DB(0x10)) \
_END_ASM

/// Сложение четырехмерных векторов двойной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP4DDADDSSE2 \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0xF2,0x0F,0x58,0x02 )                               /* addsd       xmm0,mmword ptr [edx]  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x08 )                          /* movsd       xmm2,mmword ptr [eax+8]  */ \
_LINE5( 0xF2,0x0F,0x58,0x52,0x08 )                          /* addsd       xmm2,mmword ptr [edx+8]  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm2  */ \
_LINE5( 0xF2,0x0F,0x10,0x60,0x10 )                          /* movsd       xmm4,mmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0x58,0x62,0x10 )                          /* addsd       xmm4,mmword ptr [edx+10h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x61,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm4  */ \
_LINE5( 0xF2,0x0F,0x10,0x70,0x18 )                          /* movsd       xmm6,mmword ptr [eax+18h]  */ \
_LINE5( 0xF2,0x0F,0x58,0x72,0x18 )                          /* addsd       xmm6,mmword ptr [edx+18h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x71,0x18 )                          /* movsd       mmword ptr [ecx+18h],xmm6  */ \
_END_ASM

/// Сложение двухмерных векторов двойной точности, команды SSE3.
/// @brief for CPUTYPE3
#define VECTORP4DDADDSSE3 \
BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0xF2,0x0F,0x58,0x02 )                               /* addsd       xmm0,mmword ptr [edx]  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x08 )                          /* movsd       xmm2,mmword ptr [eax+8]  */ \
_LINE5( 0xF2,0x0F,0x58,0x52,0x08 )                          /* addsd       xmm2,mmword ptr [edx+8]  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm2  */ \
_LINE5( 0xF2,0x0F,0x10,0x60,0x10 )                          /* movsd       xmm4,mmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0x58,0x62,0x10 )                          /* addsd       xmm4,mmword ptr [edx+10h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x61,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm4  */ \
_LINE5( 0xF2,0x0F,0x10,0x70,0x18 )                          /* movsd       xmm6,mmword ptr [eax+18h]  */ \
_LINE5( 0xF2,0x0F,0x58,0x72,0x18 )                          /* addsd       xmm6,mmword ptr [edx+18h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x71,0x18 )                          /* movsd       mmword ptr [ecx+18h],xmm6  */ \
END_ASM

/// Сложение двухмерных векторов двойной точности, команды SSE4.
/// @brief for CPUTYPE4
#define VECTORP4DDADDSSE4 \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x66,0x0F,0x58,0xC1 )                               /* addpd       xmm0,xmm1  */ \
_LINE5( 0xF2,0x0F,0xF0,0x50,0x10 )                          /* lddqu       xmm2,xmmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x5A,0x10 )                          /* lddqu       xmm3,xmmword ptr [edx+10h]  */ \
_LINE4( 0x66,0x0F,0x58,0xD3 )                               /* addpd       xmm2,xmm3  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_LINE5( 0x66,0x0F,0x11,0x51,0x10 )                          /* movupd      xmmword ptr [ecx+10h],xmm2  */ \
_END_ASM

//**************************** ADD C++ FASTCALL *********************************
// addition vectors ecx-a void *, edx-b void *, eax-rez void *

/// Сложение двухмерных векторов одинарной точности, команды FPU.
#define VECTORP2DADDFPU_CPP \
_BEGIN_ASM \
_STR(_DB(0xD9) _DB(0x01)) \
_STR(_DB(0xD8) _DB(0x02)) \
_STR(_DB(0xD9) _DB(0x18)) \
_STR(_DB(0xD9) _DB(0x41) _DB(0x04)) \
_STR(_DB(0xD8) _DB(0x42) _DB(0x04)) \
_STR(_DB(0xD9) _DB(0x58) _DB(0x04)) \
_END_ASM

/// Сложение двухмерных векторов одинарной точности, команды 3DNOW.
#define VECTORP2DADD3DNOW_CPP \
_BEGIN_ASM \
_LINE3( 0x0F,0x6F,0x01 )                                    /* movq        mm0,mmword ptr [ecx]  */ \
_LINE4( 0x0F,0x0F,0x02,0x9E )                               /* pfadd       mm0,mmword ptr [edx]  */ \
_LINE3( 0x0F,0x7F,0x00 )                                    /* movq        mmword ptr [eax],mm0  */ \
_LINE2( 0x0F,0x0E )                                         /* femms   */ \
_END_ASM

/// Сложение двухмерных векторов одинарной точности, команды SSE.
#define VECTORP2DADDSSE_CPP \
_BEGIN_ASM \
_LINE4( 0xF3,0x0F,0x10,0x01 )                               /* movss       xmm0,dword ptr [ecx]  */ \
_LINE5( 0xF3,0x0F,0x10,0x49,0x04 )                          /* movss       xmm1,dword ptr [ecx+4]  */ \
_LINE4( 0xF3,0x0F,0x10,0x12 )                               /* movss       xmm2,dword ptr [edx]  */ \
_LINE5( 0xF3,0x0F,0x10,0x5A,0x04 )                          /* movss       xmm3,dword ptr [edx+4]  */ \
_LINE4( 0xF3,0x0F,0x58,0xC2 )                               /* addss       xmm0,xmm2  */ \
_LINE4( 0xF3,0x0F,0x58,0xCB )                               /* addss       xmm1,xmm3  */ \
_LINE4( 0xF3,0x0F,0x11,0x00 )                               /* movss       dword ptr [eax],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x48,0x04 )                          /* movss       dword ptr [eax+4],xmm1  */ \
_END_ASM

/// Сложение двухмерных векторов одинарной точности, команды SSE2.
#define VECTORP2DADDSSE2_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x01 )                               /* movsd       xmm0,mmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,mmword ptr [edx]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x00 )                               /* movsd       mmword ptr [eax],xmm0  */ \
_END_ASM

/// Сложение трехмерных векторов одинарной точности, команды FPU.
#define VECTORP3DADDFPU_CPP \
_BEGIN_ASM \
 _STR(_DB(0xD9) _DB(0x01)) \
 _STR(_DB(0xD8) _DB(0x02)) \
 _STR(_DB(0xD9) _DB(0x18)) \
 _STR(_DB(0xD9) _DB(0x41) _DB(0x04)) \
 _STR(_DB(0xD8) _DB(0x42) _DB(0x04)) \
 _STR(_DB(0xD9) _DB(0x58) _DB(0x04)) \
 _STR(_DB(0xD9) _DB(0x41) _DB(0x08)) \
 _STR(_DB(0xD8) _DB(0x42) _DB(0x08)) \
 _STR(_DB(0xD9) _DB(0x58) _DB(0x08)) \
_END_ASM

/// Сложение трехмерных векторов одинарной точности, команды 3DNOW.
#define VECTORP3DADD3DNOW_CPP \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE3( 0x0F,0x6F,0x01 )                                    /* movq        mm0,mmword ptr [ecx]  */ \
_LINE4( 0x0F,0x0F,0x02,0x9E )                               /* pfadd       mm0,mmword ptr [edx]  */ \
_LINE3( 0x0F,0x7F,0x00 )                                    /* movq        mmword ptr [eax],mm0  */ \
_LINE4( 0x0F,0x6E,0x49,0x08 )                               /* movd        mm1,dword ptr [ecx+8]  */ \
_LINE5( 0x0F,0x0F,0x4A,0x08,0x9E )                          /* pfadd       mm1,mmword ptr [edx+8]  */ \
_LINE4( 0x0F,0x7E,0x48,0x08 )                               /* movd        dword ptr [eax+8],mm1  */ \
_LINE2( 0x0F,0x0E )                                         /* femms   */ \
_END_ASM

/// Сложение трехмерных векторов одинарной точности, команды SSE.
#define VECTORP3DADDSSE_CPP \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x41,0x08 )                          /* movss       xmm0,dword ptr [ecx+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE3( 0x0F,0x16,0x01 )                                    /* movhps      xmm0,qword ptr [ecx]  */ \
_LINE3( 0x0F,0x16,0x0A )                                    /* movhps      xmm1,qword ptr [edx]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x17,0x00 )                                    /* movhps      qword ptr [eax],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x40,0x08 )                          /* movss       dword ptr [eax+8],xmm0  */ \
_END_ASM

/// Сложение трехмерных векторов одинарной точности, команды SSE2.
#define VECTORP3DADDSSE2_CPP \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x41,0x08 )                          /* movss       xmm0,dword ptr [ecx+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE4( 0x66,0x0F,0x16,0x01 )                               /* movhpd      xmm0,qword ptr [ecx]  */ \
_LINE4( 0x66,0x0F,0x16,0x0A )                               /* movhpd      xmm1,qword ptr [edx]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x17,0x00 )                               /* movhpd      qword ptr [eax],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x40,0x08 )                          /* movss       dword ptr [eax+8],xmm0  */ \
_END_ASM

/// Сложение четырехмерных векторов одинарной точности, команды FPU.
#define VECTORP4DADDFPU_CPP \
_BEGIN_ASM \
_STR(_DB(0xD9) _DB(0x41) _DB(0x0C)) \
_STR(_DB(0xD8) _DB(0x42) _DB(0x0C)) \
_STR(_DB(0xD9) _DB(0x58) _DB(0x0C)) \
_STR(_DB(0xD9) _DB(0x01)) \
_STR(_DB(0xD8) _DB(0x02)) \
_STR(_DB(0xD9) _DB(0x18)) \
_STR(_DB(0xD9) _DB(0x41) _DB(0x04)) \
_STR(_DB(0xD8) _DB(0x42) _DB(0x04)) \
_STR(_DB(0xD9) _DB(0x58) _DB(0x04)) \
_STR(_DB(0xD9) _DB(0x41) _DB(0x08)) \
_STR(_DB(0xD8) _DB(0x42) _DB(0x08)) \
_STR(_DB(0xD9) _DB(0x58) _DB(0x08)) \
_END_ASM \

/// Сложение четырехмерных векторов одинарной точности, команды SSE.
#define VECTORP4DADDSSE_CPP \
_BEGIN_ASM \
_LINE3( 0x0F,0x12,0x01 )                                    /* movlps      xmm0,qword ptr [ecx]  */ \
_LINE3( 0x0F,0x12,0x0A )                                    /* movlps      xmm1,qword ptr [edx]  */ \
_LINE4( 0x0F,0x16,0x41,0x08 )                               /* movhps      xmm0,qword ptr [ecx+8]  */ \
_LINE4( 0x0F,0x16,0x4A,0x08 )                               /* movhps      xmm1,qword ptr [edx+8]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x00 )                                    /* movlps      qword ptr [eax],xmm0  */ \
_LINE4( 0x0F,0x17,0x40,0x08 )                               /* movhps      qword ptr [eax+8],xmm0  */ \
_END_ASM

/// Сложение четырехмерных векторов одинарной точности, команды SSE3.
#define VECTORP4DADDSSE3_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x00 )                                    /* movlps      qword ptr [eax],xmm0  */ \
_LINE4( 0x0F,0x17,0x40,0x08 )                               /* movhps      qword ptr [eax+8],xmm0  */ \
_END_ASM

/// Сложение четырехмерных векторов одинарной точности, команды SSE4.
#define VECTORP4DADDSSE4_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x00 )                               /* movupd      xmmword ptr [eax],xmm0  */ \
_END_ASM

/// Сложение двухмерных векторов двойной точности, команды FPU.
#define VECTORP2DDADDFPU_CPP \
_BEGIN_ASM \
_LINE2( 0xDD,0x01 )                                         /* fld         qword ptr [ecx]  */ \
_LINE2( 0xDC,0x02 )                                         /* fadd        qword ptr [edx]  */ \
_LINE2( 0xDD,0x18 )                                         /* fstp        qword ptr [eax]  */ \
_LINE3( 0xDD,0x41,0x08 )                                    /* fld         qword ptr [ecx+8]  */ \
_LINE3( 0xDC,0x42,0x08 )                                    /* fadd        qword ptr [edx+8]  */ \
_LINE3( 0xDD,0x58,0x08 )                                    /* fstp        qword ptr [eax+8]  */ \
_END_ASM

/// Сложение двухмерных векторов двойной точности, команды SSE2.
#define VECTORP2DDADDSSE2_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x01 )                               /* movsd       xmm0,mmword ptr [ecx]  */ \
_LINE5( 0x66,0x0F,0x16,0x41,0x08 )                          /* movhpd      xmm0,qword ptr [ecx+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x22 )                               /* movsd       xmm4,mmword ptr [edx]  */ \
_LINE5( 0x66,0x0F,0x16,0x62,0x08 )                          /* movhpd      xmm4,qword ptr [edx+8]  */ \
_LINE4( 0x66,0x0F,0x58,0xC4 )                               /* addpd       xmm0,xmm4  */ \
_LINE4( 0xF2,0x0F,0x11,0x00 )                               /* movsd       mmword ptr [eax],xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xC1 )                               /* unpckhpd    xmm0,xmm1  */ \
_LINE5( 0xF2,0x0F,0x11,0x40,0x08 )                          /* movsd       mmword ptr [eax+8],xmm0  */ \
_END_ASM

/// Сложение двухмерных векторов двойной точности, команды SSE3.
#define VECTORP2DDADDSSE3_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x66,0x0F,0x58,0xC1 )                               /* addpd       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x00 )                               /* movsd       mmword ptr [eax],xmm0  */ \
_LINE5( 0x66,0x0F,0x17,0x40,0x08 )                          /* movhpd      qword ptr [eax+8],xmm0  */ \
_END_ASM

/// Сложение двухмерных векторов двойной точности, команды SSE4.
#define VECTORP2DDADDSSE4_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x66,0x0F,0x58,0xC1 )                               /* addpd       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x00 )                               /* movupd      xmmword ptr [eax],xmm0  */ \
_END_ASM

/// Сложение трехмерных векторов двойной точности, команды FPU.
#define VECTORP3DDADDFPU_CPP \
_BEGIN_ASM \
_LINE2( 0xDD,0x01 )                                         /* fld         qword ptr [ecx]  */ \
_LINE2( 0xDC,0x02 )                                         /* fadd        qword ptr [edx]  */ \
_LINE2( 0xDD,0x18 )                                         /* fstp        qword ptr [eax]  */ \
_LINE3( 0xDD,0x41,0x08 )                                    /* fld         qword ptr [ecx+8]  */ \
_LINE3( 0xDC,0x42,0x08 )                                    /* fadd        qword ptr [edx+8]  */ \
_LINE3( 0xDD,0x58,0x08 )                                    /* fstp        qword ptr [eax+8]  */ \
_LINE3( 0xDD,0x41,0x10 )                                    /* fld         qword ptr [ecx+10h]  */ \
_LINE3( 0xDC,0x42,0x10 )                                    /* fadd        qword ptr [edx+10h]  */ \
_LINE3( 0xDD,0x58,0x10 )                                    /* fstp        qword ptr [eax+10h]  */ \
_END_ASM

/// Сложение трехмерных векторов двойной точности, команды SSE2.
#define VECTORP3DDADDSSE2_CPP \
_BEGIN_ASM \
_LINE5( 0xF2,0x0F,0x10,0x51,0x10 )                          /* movsd       xmm2,mmword ptr [ecx+10h]  */ \
_LINE4( 0xF2,0x0F,0x10,0x01 )                               /* movsd       xmm0,mmword ptr [ecx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x49,0x08 )                          /* movsd       xmm1,mmword ptr [ecx+8]  */ \
_LINE5( 0xF2,0x0F,0x58,0x52,0x10 )                          /* addsd       xmm2,mmword ptr [edx+10h]  */ \
_LINE4( 0xF2,0x0F,0x10,0x22 )                               /* movsd       xmm4,mmword ptr [edx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x6A,0x08 )                          /* movsd       xmm5,mmword ptr [edx+8]  */ \
_LINE4( 0x66,0x0F,0x14,0xC1 )                               /* unpcklpd    xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x14,0xE5 )                               /* unpcklpd    xmm4,xmm5  */ \
_LINE4( 0x66,0x0F,0x58,0xC4 )                               /* addpd       xmm0,xmm4  */ \
_LINE4( 0xF2,0x0F,0x11,0x00 )                               /* movsd       mmword ptr [eax],xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xC1 )                               /* unpckhpd    xmm0,xmm1  */ \
_LINE5( 0xF2,0x0F,0x11,0x50,0x10 )                          /* movsd       mmword ptr [eax+10h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x40,0x08 )                          /* movsd       mmword ptr [eax+8],xmm0  */ \
_END_ASM

/// Сложение трехмерных векторов двойной точности, команды SSE3.
#define VECTORP3DDADDSSE3_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x51,0x10 )                          /* movsd       xmm2,mmword ptr [ecx+10h]  */ \
_LINE5( 0xF2,0x0F,0x58,0x52,0x10 )                          /* addsd       xmm2,mmword ptr [edx+10h]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x22 )                               /* lddqu       xmm4,xmmword ptr [edx]  */ \
_LINE5( 0xF2,0x0F,0x11,0x50,0x10 )                          /* movsd       mmword ptr [eax+10h],xmm2  */ \
_LINE4( 0x66,0x0F,0x58,0xC4 )                               /* addpd       xmm0,xmm4  */ \
_LINE4( 0xF2,0x0F,0x11,0x00 )                               /* movsd       mmword ptr [eax],xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xC1 )                               /* unpckhpd    xmm0,xmm1  */ \
_LINE5( 0xF2,0x0F,0x11,0x40,0x08 )                          /* movsd       mmword ptr [eax+8],xmm0  */ \
_END_ASM

/// Сложение трехмерных векторов двойной точности, команды SSE4.
#define VECTORP3DDADDSSE4_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x22 )                               /* lddqu       xmm4,xmmword ptr [edx]  */ \
_LINE4( 0x66,0x0F,0x58,0xC4 )                               /* addpd       xmm0,xmm4  */ \
_LINE5( 0xF2,0x0F,0x10,0x51,0x10 )                          /* movsd       xmm2,mmword ptr [ecx+10h]  */ \
_LINE4( 0x66,0x0F,0x11,0x00 )                               /* movupd      xmmword ptr [eax],xmm0  */ \
_LINE5( 0xF2,0x0F,0x58,0x52,0x10 )                          /* addsd       xmm2,mmword ptr [edx+10h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x50,0x10 )                          /* movsd       mmword ptr [eax+10h],xmm2  */ \
_END_ASM

/// Сложение четырехмерных векторов двойной точности, команды FPU.
#define VECTORP4DDADDFPU_CPP \
_BEGIN_ASM \
 _STR(_DB(0xDD) _DB(0x41) _DB(0x18)) \
 _STR(_DB(0xDC) _DB(0x42) _DB(0x18)) \
 _STR(_DB(0xDD) _DB(0x58) _DB(0x18)) \
 _STR(_DB(0xDD) _DB(0x01)) \
 _STR(_DB(0xDC) _DB(0x02)) \
 _STR(_DB(0xDD) _DB(0x18)) \
 _STR(_DB(0xDD) _DB(0x41) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x42) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x58) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x41) _DB(0x10)) \
 _STR(_DB(0xDC) _DB(0x42) _DB(0x10)) \
 _STR(_DB(0xDD) _DB(0x58) _DB(0x10)) \
_END_ASM

/// Сложение четырехмерных векторов двойной точности, команды SSE2.
#define VECTORP4DDADDSSE2_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x01 )                               /* movsd       xmm0,mmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0x58,0x02 )                               /* addsd       xmm0,mmword ptr [edx]  */ \
_LINE4( 0xF2,0x0F,0x11,0x00 )                               /* movsd       mmword ptr [eax],xmm0  */ \
_LINE5( 0xF2,0x0F,0x10,0x51,0x08 )                          /* movsd       xmm2,mmword ptr [ecx+8]  */ \
_LINE5( 0xF2,0x0F,0x58,0x52,0x08 )                          /* addsd       xmm2,mmword ptr [edx+8]  */ \
_LINE5( 0xF2,0x0F,0x11,0x50,0x08 )                          /* movsd       mmword ptr [eax+8],xmm2  */ \
_LINE5( 0xF2,0x0F,0x10,0x61,0x10 )                          /* movsd       xmm4,mmword ptr [ecx+10h]  */ \
_LINE5( 0xF2,0x0F,0x58,0x62,0x10 )                          /* addsd       xmm4,mmword ptr [edx+10h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x60,0x10 )                          /* movsd       mmword ptr [eax+10h],xmm4  */ \
_LINE5( 0xF2,0x0F,0x10,0x71,0x18 )                          /* movsd       xmm6,mmword ptr [ecx+18h]  */ \
_LINE5( 0xF2,0x0F,0x58,0x72,0x18 )                          /* addsd       xmm6,mmword ptr [edx+18h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x70,0x18 )                          /* movsd       mmword ptr [eax+18h],xmm6  */ \
_END_ASM

/// Сложение двухмерных векторов двойной точности, команды SSE3.
#define VECTORP4DDADDSSE3_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x01 )                               /* movsd       xmm0,mmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0x58,0x02 )                               /* addsd       xmm0,mmword ptr [edx]  */ \
_LINE4( 0xF2,0x0F,0x11,0x00 )                               /* movsd       mmword ptr [eax],xmm0  */ \
_LINE5( 0xF2,0x0F,0x10,0x51,0x08 )                          /* movsd       xmm2,mmword ptr [ecx+8]  */ \
_LINE5( 0xF2,0x0F,0x58,0x52,0x08 )                          /* addsd       xmm2,mmword ptr [edx+8]  */ \
_LINE5( 0xF2,0x0F,0x11,0x50,0x08 )                          /* movsd       mmword ptr [eax+8],xmm2  */ \
_LINE5( 0xF2,0x0F,0x10,0x61,0x10 )                          /* movsd       xmm4,mmword ptr [ecx+10h]  */ \
_LINE5( 0xF2,0x0F,0x58,0x62,0x10 )                          /* addsd       xmm4,mmword ptr [edx+10h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x60,0x10 )                          /* movsd       mmword ptr [eax+10h],xmm4  */ \
_LINE5( 0xF2,0x0F,0x10,0x71,0x18 )                          /* movsd       xmm6,mmword ptr [ecx+18h]  */ \
_LINE5( 0xF2,0x0F,0x58,0x72,0x18 )                          /* addsd       xmm6,mmword ptr [edx+18h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x70,0x18 )                          /* movsd       mmword ptr [eax+18h],xmm6  */ \
_END_ASM

/// Сложение двухмерных векторов двойной точности, команды SSE4.
#define VECTORP4DDADDSSE4_CPP \
_BEGIN_ASM \
_LINE5( 0xF2,0x0F,0xF0,0x51,0x10 )                          /* lddqu       xmm2,xmmword ptr [ecx+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x5A,0x10 )                          /* lddqu       xmm3,xmmword ptr [edx+10h]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x66,0x0F,0x58,0xD3 )                               /* addpd       xmm2,xmm3  */ \
_LINE4( 0x66,0x0F,0x58,0xC1 )                               /* addpd       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x00 )                               /* movupd      xmmword ptr [eax],xmm0  */ \
_LINE5( 0x66,0x0F,0x11,0x50,0x10 )                          /* movupd      xmmword ptr [eax+10h],xmm2  */ \
_END_ASM

// *************************************** TEST RESULTS **********************************************

#endif
