//=============================================================================
///**
// *  @file   matrix_transpose.h
// *
// *  $Id: matrix_transpose.h 16.10.2011  $
// *
// *  @brief generator 3, assembler matrix double/float transpose, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_MATRIX_TRANSPOSE_H_
#define GEN3_MATRIX_TRANSPOSE_H_

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

/// Транспонирование матрицы одинарной точности, команды SSE4
#define MATRIXP4DTRANSPOSESSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                               /* mov         edx,dword ptr [esp+4] */ \
_LINE4( 0xF2,0x0F,0xF0,0x22 )                               /* lddqu       xmm4,[edx]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x6A,0x10 )                          /* lddqu       xmm5,[edx+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x7A,0x20 )                          /* lddqu       xmm7,[edx+20h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x72,0x30 )                          /* lddqu       xmm6,[edx+30h]  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8] */ \
_LINE4( 0xF2,0x0F,0x10,0xC4 )                               /* movsd       xmm0,xmm4  */ \
_LINE3( 0x0F,0x14,0xC5 )                                    /* unpcklps    xmm0,xmm5  */ \
_LINE3( 0x0F,0x15,0xE5 )                                    /* unpckhps    xmm4,xmm5  */ \
_LINE4( 0xF2,0x0F,0x10,0xEF )                               /* movsd       xmm5,xmm7  */ \
_LINE3( 0x0F,0x14,0xEE )                                    /* unpcklps    xmm5,xmm6  */ \
_LINE3( 0x0F,0x15,0xFE )                                    /* unpckhps    xmm7,xmm6  */ \
_LINE4( 0xF2,0x0F,0x10,0xF4 )                               /* movsd       xmm6,xmm4  */ \
_LINE3( 0x0F,0x16,0xF7 )                                    /* movlhps     xmm6,xmm7  */ \
_LINE3( 0x0F,0x12,0xFC )                                    /* movhlps     xmm7,xmm4  */ \
_LINE4( 0xF2,0x0F,0x10,0xE0 )                               /* movsd       xmm4,xmm0  */ \
_LINE3( 0x0F,0x16,0xE5 )                                    /* movlhps     xmm4,xmm5  */ \
_LINE3( 0x0F,0x12,0xE8 )                                    /* movhlps     xmm5,xmm0  */ \
_LINE3( 0x0F,0x11,0x20 )                                    /* movups      xmmword ptr [eax],xmm4  */ \
_LINE4( 0x0F,0x11,0x68,0x10 )                               /* movups      xmmword ptr [eax+10h],xmm5  */ \
_LINE4( 0x0F,0x11,0x70,0x20 )                               /* movups      xmmword ptr [eax+20h],xmm6  */ \
_LINE4( 0x0F,0x11,0x78,0x30 )                               /* movups      xmmword ptr [eax+30h],xmm7  */ \
_END_ASM

#endif /* X86MATRIX_TRANSPOSE_H_ */
