//=============================================================================
///**
// *  @file matrix_trs.h
// *
// *  $Id: matrix_trs.h 16.10.2011  $
// *
// *  @brief generator 3, assembler matrix double/float trs, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_MATRIX_TRS_H_
#define GEN3_MATRIX_TRS_H_

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

/// Создание матрици трансформации одинарной точности, команды SSE ???
/// @brief for CPUTYPE3
#define MATRIXP4DTRSSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x12,0x00 )                                    /* movlps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x57,0xFF )                                    /* xorps       xmm7,xmm7  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )                               /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x59,0xC9 )                                    /* mulps       xmm1,xmm1  */ \
_LINE3( 0x0F,0x12,0xD1 )                                    /* movhlps     xmm2,xmm1  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x28,0xCA )                                    /* movaps      xmm1,xmm2  */ \
_LINE4( 0x0F,0xC6,0xC9,0x01 )                               /* shufps      xmm1,xmm1,1  */ \
_LINE4( 0xF3,0x0F,0x58,0xD1 )                               /* addss       xmm2,xmm1  */ \
_LINE5( 0xB8,0x02,0x00,0x00,0x00 )                          /* mov         eax,2  */ \
_LINE4( 0xF3,0x0F,0x2A,0xC8 )                               /* cvtsi2ss    xmm1,eax  */ \
_LINE5( 0xB8,0x01,0x00,0x00,0x00 )                          /* mov         eax,1  */ \
_LINE4( 0xF3,0x0F,0x2A,0xF8 )                               /* cvtsi2ss    xmm7,eax  */ \
_LINE4( 0xF3,0x0F,0x5E,0xCA )                               /* divss       xmm1,xmm2  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x28,0xD8 )                                    /* movaps      xmm3,xmm0  */ \
_LINE3( 0x0F,0x59,0xD9 )                                    /* mulps       xmm3,xmm1 (f 0-2) */ \
_LINE3( 0x0F,0x28,0xD0 )                                    /* movaps      xmm2,xmm0  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x28,0xCB )                                    /* movaps      xmm1,xmm3  */ \
_LINE3( 0x0F,0x59,0xCA )                                    /* mulps       xmm1,xmm2 (f 3-5) */ \
_LINE3( 0x0F,0x28,0xE3 )                                    /* movaps      xmm4,xmm3  */ \
_LINE4( 0x0F,0xC6,0xE4,0xE9 )                               /* shufps      xmm4,xmm4,0E9h  */ \
_LINE4( 0x0F,0xC6,0xC0,0xE5 )                               /* shufps      xmm0,xmm0,0E5h  */ \
_LINE3( 0x0F,0x59,0xE0 )                                    /* mulps       xmm4,xmm0 (f 6-8) */ \
_LINE4( 0x0F,0xC6,0xC0,0xFF )                               /* shufps      xmm0,xmm0,0FFh  */ \
_LINE3( 0x0F,0x59,0xC3 )                                    /* mulps       xmm0,xmm3 (f 9-11) */ \
_LINE3( 0x0F,0x28,0xD9 )                                    /* movaps      xmm3,xmm1  */ \
_LINE4( 0x0F,0xC6,0xDC,0x00 )                               /* shufps      xmm3,xmm4,0x0 (f 3 3 6 6) */ \
_LINE4( 0x0F,0xC6,0xCC,0x59 )                               /* shufps      xmm1,xmm4,59h (f 4 5 7 7) */ \
_LINE4( 0x0F,0xC6,0xC0,0x06 )                               /* shufps      xmm0,xmm0,6 (f 11 10 9 9) */ \
_LINE4( 0x0F,0xC6,0xE4,0xA8 )                               /* shufps      xmm4,xmm4,0A8h (f 6 8 8 8) */ \
_LINE3( 0x0F,0x28,0xD1 )                                    /* movaps      xmm2,xmm1  */ \
_LINE3( 0x0F,0x58,0xC8 )                                    /* addps       xmm1,xmm0 (3 5 7) */ \
_LINE3( 0x0F,0x5C,0xD0 )                                    /* subps       xmm2,xmm0 (4 6 8) */ \
_LINE3( 0x0F,0x58,0xE3 )                                    /* addps       xmm4,xmm3  */ \
_LINE4( 0x0F,0xC6,0xFF,0x40 )                               /* shufps      xmm7,xmm7,40h  */ \
_LINE4( 0x8B,0x54,0x24,0x04 )                               /* mov         edx,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x11,0x7A,0x3C )                          /* movss       dword ptr [edx+3Ch],xmm7  */ \
_LINE3( 0x0F,0x5C,0xFC )                                    /* subps       xmm7,xmm4 (2 1 0) */ \
_LINE4( 0x8B,0x44,0x24,0x10 )                               /* mov         eax,dword ptr [esp+16]  */ \
_LINE3( 0x0F,0x28,0xC1 )                                    /* movaps      xmm0,xmm1 (3 5 7) */ \
_LINE3( 0x0F,0x28,0xDA )                                    /* movaps      xmm3,xmm2 (4 6 8) */ \
_LINE3( 0x0F,0x28,0xE7 )                                    /* movaps      xmm4,xmm7 (2 1 0) */ \
_LINE4( 0xF3,0x0F,0x10,0x28 )                               /* movss       xmm5,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xC0,0xDC )                               /* shufps      xmm0,xmm0,0DCh (3 x 5 x) */ \
_LINE4( 0x0F,0xC6,0xDB,0xDE )                               /* shufps      xmm3,xmm3,0DEh (8 x 6 x) */ \
_LINE4( 0x0F,0xC6,0xE4,0xCE )                               /* shufps      xmm4,xmm4,0CEh (0 x 2 x) */ \
_LINE4( 0x0F,0xC6,0xED,0x40 )                               /* shufps      xmm5,xmm5,40h  */ \
_LINE3( 0x0F,0x12,0xCB )                                    /* movhlps     xmm1,xmm3 (6 x 7 x) */ \
_LINE3( 0x0F,0x16,0xD4 )                                    /* movlhps     xmm2,xmm4 () */ \
_LINE3( 0x0F,0x16,0xF8 )                                    /* movlhps     xmm7,xmm0 (2 1 3 x) */ \
_LINE5( 0xF3,0x0F,0x10,0x70,0x04 )                          /* movss       xmm6,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xCC,0xE8 )                               /* shufps      xmm1,xmm4,0E8h  */ \
_LINE4( 0x0F,0xC6,0xD0,0xE2 )                               /* shufps      xmm2,xmm0,0E2h  */ \
_LINE4( 0x0F,0xC6,0xFB,0xC6 )                               /* shufps      xmm7,xmm3,0C6h (3 1 8 x) */ \
_LINE5( 0xF3,0x0F,0x10,0x60,0x08 )                          /* movss       xmm4,dword ptr [eax+8]  */ \
_LINE4( 0x0F,0xC6,0xF6,0x40 )                               /* shufps      xmm6,xmm6,40h  */ \
_LINE3( 0x0F,0x59,0xD5 )                                    /* mulps       xmm2,xmm5  */ \
_LINE4( 0x0F,0xC6,0xE4,0x40 )                               /* shufps      xmm4,xmm4,40h  */ \
_LINE3( 0x0F,0x59,0xFE )                                    /* mulps       xmm7,xmm6  */ \
_LINE3( 0x0F,0x13,0x12 )                                    /* movlps      qword ptr [edx],xmm2  */ \
_LINE3( 0x0F,0x59,0xCC )                                    /* mulps       xmm1,xmm4  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x17,0x52,0x08 )                               /* movhps      qword ptr [edx+8],xmm2  */ \
_LINE4( 0x0F,0x13,0x7A,0x10 )                               /* movlps      qword ptr [edx+10h],xmm7  */ \
_LINE4( 0x0F,0x13,0x4A,0x20 )                               /* movlps      qword ptr [edx+20h],xmm1  */ \
_LINE4( 0x0F,0x17,0x7A,0x18 )                               /* movhps      qword ptr [edx+18h],xmm7  */ \
_LINE4( 0x0F,0x17,0x4A,0x28 )                               /* movhps      qword ptr [edx+28h],xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x08 )                          /* movss       xmm3,dword ptr [eax+8]  */ \
_LINE5( 0xF3,0x0F,0x11,0x5A,0x38 )                          /* movss       dword ptr [edx+38h],xmm3  */ \
_LINE3( 0x0F,0x16,0x28 )                                    /* movhps      xmm5,qword ptr [eax]  */ \
_LINE4( 0x0F,0x17,0x6A,0x30 )                               /* movhps      qword ptr [edx+30h],xmm5  */ \
_END_ASM

/// Поворот матрици одинарной точности, команды SSE2
/// @brief for CPUTYPE3
#define MATRIXP4DTRSSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x12,0x00 )                                    /* movlps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x57,0xFF )                                    /* xorps       xmm7,xmm7  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )                               /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x59,0xC9 )                                    /* mulps       xmm1,xmm1  */ \
_LINE3( 0x0F,0x12,0xD1 )                                    /* movhlps     xmm2,xmm1  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x28,0xCA )                                    /* movaps      xmm1,xmm2  */ \
_LINE4( 0x0F,0xC6,0xC9,0x01 )                               /* shufps      xmm1,xmm1,1  */ \
_LINE4( 0xF3,0x0F,0x58,0xD1 )                               /* addss       xmm2,xmm1  */ \
_LINE5( 0xB8,0x02,0x00,0x00,0x00 )                          /* mov         eax,2  */ \
_LINE4( 0xF3,0x0F,0x2A,0xC8 )                               /* cvtsi2ss    xmm1,eax  */ \
_LINE5( 0xB8,0x01,0x00,0x00,0x00 )                          /* mov         eax,1  */ \
_LINE4( 0xF3,0x0F,0x2A,0xF8 )                               /* cvtsi2ss    xmm7,eax  */ \
_LINE4( 0xF3,0x0F,0x5E,0xCA )                               /* divss       xmm1,xmm2  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x28,0xD8 )                                    /* movaps      xmm3,xmm0  */ \
_LINE3( 0x0F,0x59,0xD9 )                                    /* mulps       xmm3,xmm1 (f 0-2) */ \
_LINE3( 0x0F,0x28,0xD0 )                                    /* movaps      xmm2,xmm0  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x28,0xCB )                                    /* movaps      xmm1,xmm3  */ \
_LINE3( 0x0F,0x59,0xCA )                                    /* mulps       xmm1,xmm2 (f 3-5) */ \
_LINE3( 0x0F,0x28,0xE3 )                                    /* movaps      xmm4,xmm3  */ \
_LINE4( 0x0F,0xC6,0xE4,0xE9 )                               /* shufps      xmm4,xmm4,0E9h  */ \
_LINE4( 0x0F,0xC6,0xC0,0xE5 )                               /* shufps      xmm0,xmm0,0E5h  */ \
_LINE3( 0x0F,0x59,0xE0 )                                    /* mulps       xmm4,xmm0 (f 6-8) */ \
_LINE4( 0x0F,0xC6,0xC0,0xFF )                               /* shufps      xmm0,xmm0,0FFh  */ \
_LINE3( 0x0F,0x59,0xC3 )                                    /* mulps       xmm0,xmm3 (f 9-11) */ \
_LINE3( 0x0F,0x28,0xD9 )                                    /* movaps      xmm3,xmm1  */ \
_LINE4( 0x0F,0xC6,0xDC,0x00 )                               /* shufps      xmm3,xmm4,0x0 (f 3 3 6 6) */ \
_LINE4( 0x0F,0xC6,0xCC,0x59 )                               /* shufps      xmm1,xmm4,59h (f 4 5 7 7) */ \
_LINE4( 0x0F,0xC6,0xC0,0x06 )                               /* shufps      xmm0,xmm0,6 (f 11 10 9 9) */ \
_LINE4( 0x0F,0xC6,0xE4,0xA8 )                               /* shufps      xmm4,xmm4,0A8h (f 6 8 8 8) */ \
_LINE3( 0x0F,0x28,0xD1 )                                    /* movaps      xmm2,xmm1  */ \
_LINE3( 0x0F,0x58,0xC8 )                                    /* addps       xmm1,xmm0 (3 5 7) */ \
_LINE3( 0x0F,0x5C,0xD0 )                                    /* subps       xmm2,xmm0 (4 6 8) */ \
_LINE3( 0x0F,0x58,0xE3 )                                    /* addps       xmm4,xmm3  */ \
_LINE4( 0x0F,0xC6,0xFF,0x40 )                               /* shufps      xmm7,xmm7,40h  */ \
_LINE4( 0x8B,0x54,0x24,0x04 )                               /* mov         edx,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x11,0x7A,0x3C )                          /* movss       dword ptr [edx+3Ch],xmm7  */ \
_LINE3( 0x0F,0x5C,0xFC )                                    /* subps       xmm7,xmm4 (2 1 0) */ \
_LINE4( 0x8B,0x44,0x24,0x10 )                               /* mov         eax,dword ptr [esp+16]  */ \
_LINE3( 0x0F,0x28,0xC1 )                                    /* movaps      xmm0,xmm1 (3 5 7) */ \
_LINE3( 0x0F,0x28,0xDA )                                    /* movaps      xmm3,xmm2 (4 6 8) */ \
_LINE3( 0x0F,0x28,0xE7 )                                    /* movaps      xmm4,xmm7 (2 1 0) */ \
_LINE4( 0xF3,0x0F,0x10,0x28 )                               /* movss       xmm5,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xC0,0xDC )                               /* shufps      xmm0,xmm0,0DCh (3 x 5 x) */ \
_LINE4( 0x0F,0xC6,0xDB,0xDE )                               /* shufps      xmm3,xmm3,0DEh (8 x 6 x) */ \
_LINE4( 0x0F,0xC6,0xE4,0xCE )                               /* shufps      xmm4,xmm4,0CEh (0 x 2 x) */ \
_LINE4( 0x0F,0xC6,0xED,0x40 )                               /* shufps      xmm5,xmm5,40h  */ \
_LINE3( 0x0F,0x12,0xCB )                                    /* movhlps     xmm1,xmm3 (6 x 7 x) */ \
_LINE3( 0x0F,0x16,0xD4 )                                    /* movlhps     xmm2,xmm4 () */ \
_LINE3( 0x0F,0x16,0xF8 )                                    /* movlhps     xmm7,xmm0 (2 1 3 x) */ \
_LINE5( 0xF3,0x0F,0x10,0x70,0x04 )                          /* movss       xmm6,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xCC,0xE8 )                               /* shufps      xmm1,xmm4,0E8h  */ \
_LINE4( 0x0F,0xC6,0xD0,0xE2 )                               /* shufps      xmm2,xmm0,0E2h  */ \
_LINE4( 0x0F,0xC6,0xFB,0xC6 )                               /* shufps      xmm7,xmm3,0C6h (3 1 8 x) */ \
_LINE5( 0xF3,0x0F,0x10,0x60,0x08 )                          /* movss       xmm4,dword ptr [eax+8]  */ \
_LINE4( 0x0F,0xC6,0xF6,0x40 )                               /* shufps      xmm6,xmm6,40h  */ \
_LINE3( 0x0F,0x59,0xD5 )                                    /* mulps       xmm2,xmm5  */ \
_LINE4( 0x0F,0xC6,0xE4,0x40 )                               /* shufps      xmm4,xmm4,40h  */ \
_LINE3( 0x0F,0x59,0xFE )                                    /* mulps       xmm7,xmm6  */ \
_LINE3( 0x0F,0x13,0x12 )                                    /* movlps      qword ptr [edx],xmm2  */ \
_LINE3( 0x0F,0x59,0xCC )                                    /* mulps       xmm1,xmm4  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x17,0x52,0x08 )                               /* movhps      qword ptr [edx+8],xmm2  */ \
_LINE4( 0x0F,0x13,0x7A,0x10 )                               /* movlps      qword ptr [edx+10h],xmm7  */ \
_LINE4( 0x0F,0x13,0x4A,0x20 )                               /* movlps      qword ptr [edx+20h],xmm1  */ \
_LINE4( 0x0F,0x17,0x7A,0x18 )                               /* movhps      qword ptr [edx+18h],xmm7  */ \
_LINE4( 0x0F,0x17,0x4A,0x28 )                               /* movhps      qword ptr [edx+28h],xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x08 )                          /* movss       xmm3,dword ptr [eax+8]  */ \
_LINE5( 0xF3,0x0F,0x11,0x5A,0x38 )                          /* movss       dword ptr [edx+38h],xmm3  */ \
_LINE3( 0x0F,0x16,0x28 )                                    /* movhps      xmm5,qword ptr [eax]  */ \
_LINE4( 0x0F,0x17,0x6A,0x30 )                               /* movhps      qword ptr [edx+30h],xmm5  */ \
_END_ASM

/// Создание матрици трансформации одинарной точности, команды SSE3
/// @brief for CPUTYPE4
#define MATRIXP4DTRSSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+12]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,[eax]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x59,0xC9 )                                    /* mulps       xmm1,xmm1  */ \
_LINE3( 0x0F,0x12,0xD1 )                                    /* movhlps     xmm2,xmm1  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x28,0xCA )                                    /* movaps      xmm1,xmm2  */ \
_LINE3( 0x0F,0x57,0xFF )                                    /* xorps       xmm7,xmm7  */ \
_LINE4( 0x0F,0xC6,0xC9,0x01 )                               /* shufps      xmm1,xmm1,1  */ \
_LINE4( 0xF3,0x0F,0x58,0xD1 )                               /* addss       xmm2,xmm1  */ \
_LINE5( 0xB8,0x02,0x00,0x00,0x00 )                          /* mov         eax,2  */ \
_LINE4( 0xF3,0x0F,0x2A,0xC8 )                               /* cvtsi2ss    xmm1,eax  */ \
_LINE5( 0xB8,0x01,0x00,0x00,0x00 )                          /* mov         eax,1  */ \
_LINE4( 0xF3,0x0F,0x2A,0xF8 )                               /* cvtsi2ss    xmm7,eax  */ \
_LINE4( 0xF3,0x0F,0x5E,0xCA )                               /* divss       xmm1,xmm2  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x28,0xD8 )                                    /* movaps      xmm3,xmm0  */ \
_LINE3( 0x0F,0x59,0xD9 )                                    /* mulps       xmm3,xmm1 (f 0-2) */ \
_LINE3( 0x0F,0x28,0xD0 )                                    /* movaps      xmm2,xmm0  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x28,0xCB )                                    /* movaps      xmm1,xmm3  */ \
_LINE3( 0x0F,0x59,0xCA )                                    /* mulps       xmm1,xmm2 (f 3-5) */ \
_LINE3( 0x0F,0x28,0xE3 )                                    /* movaps      xmm4,xmm3  */ \
_LINE4( 0x0F,0xC6,0xE4,0xE9 )                               /* shufps      xmm4,xmm4,0E9h  */ \
_LINE4( 0x0F,0xC6,0xC0,0xE5 )                               /* shufps      xmm0,xmm0,0E5h  */ \
_LINE3( 0x0F,0x59,0xE0 )                                    /* mulps       xmm4,xmm0 (f 6-8) */ \
_LINE4( 0x0F,0xC6,0xC0,0xFF )                               /* shufps      xmm0,xmm0,0FFh  */ \
_LINE3( 0x0F,0x59,0xC3 )                                    /* mulps       xmm0,xmm3 (f 9-11) */ \
_LINE3( 0x0F,0x28,0xD9 )                                    /* movaps      xmm3,xmm1  */ \
_LINE4( 0x0F,0xC6,0xDC,0x00 )                               /* shufps      xmm3,xmm4,0x0 (f 3 3 6 6) */ \
_LINE4( 0x0F,0xC6,0xCC,0x59 )                               /* shufps      xmm1,xmm4,59h (f 4 5 7 7) */ \
_LINE4( 0x0F,0xC6,0xC0,0x06 )                               /* shufps      xmm0,xmm0,6 (f 11 10 9 9) */ \
_LINE4( 0x0F,0xC6,0xE4,0xA8 )                               /* shufps      xmm4,xmm4,0A8h (f 6 8 8 8) */ \
_LINE3( 0x0F,0x28,0xD1 )                                    /* movaps      xmm2,xmm1  */ \
_LINE3( 0x0F,0x58,0xC8 )                                    /* addps       xmm1,xmm0 (3 5 7) */ \
_LINE3( 0x0F,0x5C,0xD0 )                                    /* subps       xmm2,xmm0 (4 6 8) */ \
_LINE3( 0x0F,0x58,0xE3 )                                    /* addps       xmm4,xmm3  */ \
_LINE4( 0x0F,0xC6,0xFF,0x40 )                               /* shufps      xmm7,xmm7,40h  */ \
_LINE4( 0x8B,0x54,0x24,0x04 )                               /* mov         edx,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x11,0x7A,0x3C )                          /* movss       dword ptr [edx+3Ch],xmm7  */ \
_LINE3( 0x0F,0x5C,0xFC )                                    /* subps       xmm7,xmm4 (2 1 0) */ \
_LINE4( 0x8B,0x44,0x24,0x10 )                               /* mov         eax,dword ptr [esp+16]  */ \
_LINE3( 0x0F,0x28,0xC1 )                                    /* movaps      xmm0,xmm1 (3 5 7) */ \
_LINE3( 0x0F,0x28,0xDA )                                    /* movaps      xmm3,xmm2 (4 6 8) */ \
_LINE3( 0x0F,0x28,0xE7 )                                    /* movaps      xmm4,xmm7 (2 1 0) */ \
_LINE4( 0xF3,0x0F,0x10,0x28 )                               /* movss       xmm5,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xC0,0xDC )                               /* shufps      xmm0,xmm0,0DCh (3 x 5 x) */ \
_LINE4( 0x0F,0xC6,0xDB,0xDE )                               /* shufps      xmm3,xmm3,0DEh (8 x 6 x) */ \
_LINE4( 0x0F,0xC6,0xE4,0xCE )                               /* shufps      xmm4,xmm4,0CEh (0 x 2 x) */ \
_LINE4( 0x0F,0xC6,0xED,0x40 )                               /* shufps      xmm5,xmm5,40h  */ \
_LINE3( 0x0F,0x12,0xCB )                                    /* movhlps     xmm1,xmm3 (6 x 7 x) */ \
_LINE3( 0x0F,0x16,0xD4 )                                    /* movlhps     xmm2,xmm4 () */ \
_LINE3( 0x0F,0x16,0xF8 )                                    /* movlhps     xmm7,xmm0 (2 1 3 x) */ \
_LINE5( 0xF3,0x0F,0x10,0x70,0x04 )                          /* movss       xmm6,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xCC,0xE8 )                               /* shufps      xmm1,xmm4,0E8h  */ \
_LINE4( 0x0F,0xC6,0xD0,0xE2 )                               /* shufps      xmm2,xmm0,0E2h  */ \
_LINE4( 0x0F,0xC6,0xFB,0xC6 )                               /* shufps      xmm7,xmm3,0C6h (3 1 8 x) */ \
_LINE5( 0xF3,0x0F,0x10,0x60,0x08 )                          /* movss       xmm4,dword ptr [eax+8]  */ \
_LINE4( 0x0F,0xC6,0xF6,0x40 )                               /* shufps      xmm6,xmm6,40h  */ \
_LINE3( 0x0F,0x59,0xD5 )                                    /* mulps       xmm2,xmm5  */ \
_LINE4( 0x0F,0xC6,0xE4,0x40 )                               /* shufps      xmm4,xmm4,40h  */ \
_LINE3( 0x0F,0x59,0xFE )                                    /* mulps       xmm7,xmm6  */ \
_LINE3( 0x0F,0x13,0x12 )                                    /* movlps      qword ptr [edx],xmm2  */ \
_LINE3( 0x0F,0x59,0xCC )                                    /* mulps       xmm1,xmm4  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x17,0x52,0x08 )                               /* movhps      qword ptr [edx+8],xmm2  */ \
_LINE4( 0x0F,0x13,0x7A,0x10 )                               /* movlps      qword ptr [edx+10h],xmm7  */ \
_LINE4( 0x0F,0x13,0x4A,0x20 )                               /* movlps      qword ptr [edx+20h],xmm1  */ \
_LINE4( 0x0F,0x17,0x7A,0x18 )                               /* movhps      qword ptr [edx+18h],xmm7  */ \
_LINE4( 0x0F,0x17,0x4A,0x28 )                               /* movhps      qword ptr [edx+28h],xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x08 )                          /* movss       xmm3,dword ptr [eax+8]  */ \
_LINE5( 0xF3,0x0F,0x11,0x5A,0x38 )                          /* movss       dword ptr [edx+38h],xmm3  */ \
_LINE3( 0x0F,0x16,0x28 )                                    /* movhps      xmm5,qword ptr [eax]  */ \
_LINE4( 0x0F,0x17,0x6A,0x30 )                               /* movhps      qword ptr [edx+30h],xmm5  */ \
_END_ASM

/// Создание матрици трансформации одинарной точности, команды SSE4
/// @brief for CPUTYPE4
#define MATRIXP4DTRSSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+12]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,[eax]  */ \
_LINE3( 0x0F,0x28,0xD0 )                                    /* movaps      xmm2,xmm0  */ \
_LINE5( 0xB8,0x02,0x00,0x00,0x00 )                          /* mov         eax,2  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xD2,0xF1 )                     /* dpps        xmm2,xmm2,0F1h  */ \
_LINE3( 0x0F,0x57,0xFF )                                    /* xorps       xmm7,xmm7  */ \
_LINE4( 0xF3,0x0F,0x2A,0xC8 )                               /* cvtsi2ss    xmm1,eax  */ \
_LINE5( 0xB8,0x01,0x00,0x00,0x00 )                          /* mov         eax,1  */ \
_LINE4( 0xF3,0x0F,0x5E,0xCA )                               /* divss       xmm1,xmm2  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x28,0xD8 )                                    /* movaps      xmm3,xmm0  */ \
_LINE3( 0x0F,0x59,0xD9 )                                    /* mulps       xmm3,xmm1 (f 0-2) */ \
_LINE3( 0x0F,0x28,0xD0 )                                    /* movaps      xmm2,xmm0  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x28,0xCB )                                    /* movaps      xmm1,xmm3  */ \
_LINE3( 0x0F,0x59,0xCA )                                    /* mulps       xmm1,xmm2 (f 3-5) */ \
_LINE3( 0x0F,0x28,0xE3 )                                    /* movaps      xmm4,xmm3  */ \
_LINE4( 0x0F,0xC6,0xE4,0xE9 )                               /* shufps      xmm4,xmm4,0E9h  */ \
_LINE4( 0x0F,0xC6,0xC0,0xE5 )                               /* shufps      xmm0,xmm0,0E5h  */ \
_LINE3( 0x0F,0x59,0xE0 )                                    /* mulps       xmm4,xmm0 (f 6-8) */ \
_LINE4( 0x0F,0xC6,0xC0,0xFF )                               /* shufps      xmm0,xmm0,0FFh  */ \
_LINE3( 0x0F,0x59,0xC3 )                                    /* mulps       xmm0,xmm3 (f 9-11) */ \
_LINE3( 0x0F,0x28,0xD9 )                                    /* movaps      xmm3,xmm1  */ \
_LINE4( 0xF3,0x0F,0x2A,0xF8 )                               /* cvtsi2ss    xmm7,eax  */ \
_LINE4( 0x0F,0xC6,0xDC,0x00 )                               /* shufps      xmm3,xmm4,0x0 (f 3 3 6 6) */ \
_LINE4( 0x0F,0xC6,0xCC,0x59 )                               /* shufps      xmm1,xmm4,59h (f 4 5 7 7) */ \
_LINE4( 0x0F,0xC6,0xC0,0x06 )                               /* shufps      xmm0,xmm0,6 (f 11 10 9 9) */ \
_LINE4( 0x0F,0xC6,0xE4,0xA8 )                               /* shufps      xmm4,xmm4,0A8h (f 6 8 8 8) */ \
_LINE3( 0x0F,0x28,0xD1 )                                    /* movaps      xmm2,xmm1  */ \
_LINE3( 0x0F,0x58,0xC8 )                                    /* addps       xmm1,xmm0 (3 5 7) */ \
_LINE3( 0x0F,0x5C,0xD0 )                                    /* subps       xmm2,xmm0 (4 6 8) */ \
_LINE3( 0x0F,0x58,0xE3 )                                    /* addps       xmm4,xmm3  */ \
_LINE4( 0x0F,0xC6,0xFF,0x40 )                               /* shufps      xmm7,xmm7,40h  */ \
_LINE4( 0x8B,0x54,0x24,0x04 )                               /* mov         edx,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x11,0x7A,0x3C )                          /* movss       dword ptr [edx+3Ch],xmm7  */ \
_LINE3( 0x0F,0x5C,0xFC )                                    /* subps       xmm7,xmm4 (2 1 0) */ \
_LINE4( 0x8B,0x44,0x24,0x10 )                               /* mov         eax,dword ptr [esp+16]  */ \
_LINE3( 0x0F,0x28,0xC1 )                                    /* movaps      xmm0,xmm1 (3 5 7) */ \
_LINE3( 0x0F,0x28,0xDA )                                    /* movaps      xmm3,xmm2 (4 6 8) */ \
_LINE3( 0x0F,0x28,0xE7 )                                    /* movaps      xmm4,xmm7 (2 1 0) */ \
_LINE4( 0xF3,0x0F,0x10,0x28 )                               /* movss       xmm5,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xC0,0xDC )                               /* shufps      xmm0,xmm0,0DCh (3 x 5 x) */ \
_LINE4( 0x0F,0xC6,0xDB,0xDE )                               /* shufps      xmm3,xmm3,0DEh (8 x 6 x) */ \
_LINE4( 0x0F,0xC6,0xE4,0xCE )                               /* shufps      xmm4,xmm4,0CEh (0 x 2 x) */ \
_LINE4( 0x0F,0xC6,0xED,0x40 )                               /* shufps      xmm5,xmm5,40h  */ \
_LINE3( 0x0F,0x12,0xCB )                                    /* movhlps     xmm1,xmm3 (6 x 7 x) */ \
_LINE3( 0x0F,0x16,0xD4 )                                    /* movlhps     xmm2,xmm4 () */ \
_LINE3( 0x0F,0x16,0xF8 )                                    /* movlhps     xmm7,xmm0 (2 1 3 x) */ \
_LINE5( 0xF3,0x0F,0x10,0x70,0x04 )                          /* movss       xmm6,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xCC,0xE8 )                               /* shufps      xmm1,xmm4,0E8h  */ \
_LINE4( 0x0F,0xC6,0xD0,0xE2 )                               /* shufps      xmm2,xmm0,0E2h  */ \
_LINE4( 0x0F,0xC6,0xFB,0xC6 )                               /* shufps      xmm7,xmm3,0C6h (3 1 8 x) */ \
_LINE5( 0xF3,0x0F,0x10,0x60,0x08 )                          /* movss       xmm4,dword ptr [eax+8]  */ \
_LINE4( 0x0F,0xC6,0xF6,0x40 )                               /* shufps      xmm6,xmm6,40h  */ \
_LINE3( 0x0F,0x59,0xD5 )                                    /* mulps       xmm2,xmm5  */ \
_LINE4( 0x0F,0xC6,0xE4,0x40 )                               /* shufps      xmm4,xmm4,40h  */ \
_LINE3( 0x0F,0x59,0xFE )                                    /* mulps       xmm7,xmm6  */ \
_LINE3( 0x0F,0x11,0x12 )                                    /* movups      xmmword ptr [edx],xmm2  */ \
_LINE3( 0x0F,0x59,0xCC )                                    /* mulps       xmm1,xmm4  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x11,0x7A,0x10 )                               /* movups      xmmword ptr [edx+10h],xmm7  */ \
_LINE4( 0x0F,0x11,0x4A,0x20 )                               /* movups      xmmword ptr [edx+20h],xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x08 )                          /* movss       xmm3,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x28 )                                    /* movhps      xmm5,qword ptr [eax]  */ \
_LINE5( 0xF3,0x0F,0x11,0x5A,0x38 )                          /* movss       dword ptr [edx+38h],xmm3  */ \
_LINE4( 0x0F,0x17,0x6A,0x30 )                               /* movhps      qword ptr [edx+30h],xmm5  */ \
_END_ASM

/// Создание матрици трансформации двойной точности, команды FPU // low
/// @brief for CPUTYPE1
#define MATRIXP4DDTRSFPU_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+12] ) \
ASM( mov edx,[esp+16] ) \
ASM( mov ecx,[esp+4] ) \
_LINE6( 0x81,0xEC,0xB0,0x00,0x00,0x00 )  /* sub         esp,0B0h  */ \
_LINE3( 0xDD,0x40,0x08 )           /* fld         qword ptr [eax+8]  */ \
_LINE7( 0xC7,0x04,0x24,0x00,0x00,0x00,0x00 ) /* mov         dword ptr [esp],0  */ \
_LINE2( 0xDD,0x00 )              /* fld         qword ptr [eax]  */ \
_LINE8( 0xC7,0x44,0x24,0x04,0x00,0x00,0x00,0x40 ) /* mov         dword ptr [esp+4],40000000h  */ \
_LINE3( 0xDD,0x40,0x10 )           /* fld         qword ptr [eax+10h]  */ \
_LINE3( 0xDD,0x40,0x18 )           /* fld         qword ptr [eax+18h]  */ \
_LINE2( 0xD9,0xC2 )              /* fld         st(2)  */ \
_LINE2( 0xDE,0xCB )              /* fmulp       st(3),st  */ \
_LINE2( 0xD9,0xC3 )              /* fld         st(3)  */ \
_LINE2( 0xDE,0xCC )              /* fmulp       st(4),st  */ \
_LINE2( 0xD9,0xCA )              /* fxch        st(2)  */ \
_LINE2( 0xDE,0xC3 )              /* faddp       st(3),st  */ \
_LINE2( 0xDC,0xC8 )              /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC2 )              /* faddp       st(2),st  */ \
_LINE2( 0xDC,0xC8 )              /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )              /* faddp       st(1),st  */ \
_LINE3( 0xDC,0x3C,0x24 )           /* fdivr       qword ptr [esp]  */ \
_LINE2( 0xDD,0x00 )              /* fld         qword ptr [eax]  */ \
_LINE2( 0xD8,0xC9 )              /* fmul        st,st(1)  */ \
_LINE2( 0xD9,0xC1 )              /* fld         st(1)  */ \
_LINE3( 0xDC,0x48,0x08 )           /* fmul        qword ptr [eax+8]  */ \
_LINE2( 0xD9,0xCA )              /* fxch        st(2)  */ \
_LINE3( 0xDC,0x48,0x10 )           /* fmul        qword ptr [eax+10h]  */ \
_LINE2( 0xDD,0x00 )              /* fld         qword ptr [eax]  */ \
_LINE2( 0xD8,0xCA )              /* fmul        st,st(2)  */ \
_LINE2( 0xDD,0x00 )              /* fld         qword ptr [eax]  */ \
_LINE2( 0xD8,0xCC )              /* fmul        st,st(4)  */ \
_LINE2( 0xDD,0x00 )              /* fld         qword ptr [eax]  */ \
_LINE2( 0xD8,0xCB )              /* fmul        st,st(3)  */ \
_LINE2( 0xD9,0xC5 )              /* fld         st(5)  */ \
_LINE3( 0xDC,0x48,0x08 )           /* fmul        qword ptr [eax+8]  */ \
_LINE2( 0xD9,0xC4 )              /* fld         st(4)  */ \
_LINE3( 0xDC,0x48,0x08 )           /* fmul        qword ptr [eax+8]  */ \
_LINE7( 0xDD,0x9C,0x24,0x88,0x00,0x00,0x00 ) /* fstp        qword ptr [esp+88h]  */ \
_LINE2( 0xD9,0xC4 )              /* fld         st(4)  */ \
_LINE3( 0xDC,0x48,0x10 )             /* fmul        qword ptr [eax+10h]  */ \
_LINE7( 0xDD,0x9C,0x24,0x90,0x00,0x00,0x00 ) /* fstp        qword ptr [esp+90h]  */ \
_LINE3( 0xDD,0x40,0x18 )           /* fld         qword ptr [eax+18h]  */ \
_LINE2( 0xDE,0xCE )              /* fmulp       st(6),st  */ \
_LINE3( 0xDD,0x40,0x18 )           /* fld         qword ptr [eax+18h]  */ \
_LINE2( 0xDE,0xCF )              /* fmulp       st(7),st  */ \
_LINE2( 0xD9,0xCE )              /* fxch        st(6)  */ \
_LINE7( 0xDD,0x9C,0x24,0xA0,0x00,0x00,0x00 ) /* fstp        qword ptr [esp+0A0h]  */ \
_LINE3( 0xDD,0x40,0x18 )           /* fld         qword ptr [eax+18h]  */ \
_LINE2( 0xDE,0xCC )              /* fmulp       st(4),st  */ \
_LINE2( 0xD9,0xCB )              /* fxch        st(3)  */ \
_LINE7( 0xDD,0x9C,0x24,0xA8,0x00,0x00,0x00 ) /* fstp        qword ptr [esp+0A8h]  */ \
_LINE7( 0xDD,0x84,0x24,0x90,0x00,0x00,0x00 ) /* fld         qword ptr [esp+90h]  */ \
_LINE2( 0xD8,0xC5 )              /* fadd        st,st(5)  */ \
_LINE2( 0xD9,0xE8 )              /* fld1  */ \
_LINE2( 0xD9,0xC0 )              /* fld         st(0)  */ \
_LINE2( 0xDE,0xE2 )              /* fsubrp      st(2),st  */ \
_LINE2( 0xD9,0xC9 )              /* fxch        st(1)  */ \
_LINE4( 0xDD,0x5C,0x24,0x08 )        /* fstp        qword ptr [esp+8]  */ \
_LINE7( 0xDD,0x84,0x24,0x90,0x00,0x00,0x00 ) /* fld         qword ptr [esp+90h]  */ \
_LINE2( 0xD8,0xC3 )              /* fadd        st,st(3)  */ \
_LINE2( 0xD8,0xE9 )              /* fsubr       st,st(1)  */ \
_LINE4( 0xDD,0x5C,0x24,0x10 )        /* fstp        qword ptr [esp+10h]  */ \
_LINE2( 0xD9,0xCD )              /* fxch        st(5)  */ \
_LINE2( 0xDE,0xC2 )              /* faddp       st(2),st  */ \
_LINE2( 0xD9,0xC4 )              /* fld         st(4)  */ \
_LINE2( 0xDE,0xE2 )              /* fsubrp      st(2),st  */ \
_LINE2( 0xD9,0xC9 )              /* fxch        st(1)  */ \
_LINE4( 0xDD,0x5C,0x24,0x18 )        /* fstp        qword ptr [esp+18h]  */ \
_LINE7( 0xDD,0x84,0x24,0xA8,0x00,0x00,0x00 ) /* fld         qword ptr [esp+0A8h]  */ \
_LINE2( 0xD9,0xC0 )              /* fld         st(0)  */ \
_LINE2( 0xD8,0xC2 )              /* fadd        st,st(2)  */ \
_LINE4( 0xDD,0x5C,0x24,0x20 )        /* fstp        qword ptr [esp+20h]  */ \
_LINE7( 0xDD,0x84,0x24,0xA0,0x00,0x00,0x00 ) /* fld         qword ptr [esp+0A0h]  */ \
_LINE2( 0xD9,0xC0 )              /* fld         st(0)  */ \
_LINE2( 0xD8,0xC4 )              /* fadd        st,st(4)  */ \
_LINE4( 0xDD,0x5C,0x24,0x30 )        /* fstp        qword ptr [esp+30h]  */ \
_LINE2( 0xD9,0xC4 )              /* fld         st(4)  */ \
_LINE7( 0xDD,0x84,0x24,0x88,0x00,0x00,0x00 ) /* fld         qword ptr [esp+88h]  */ \
_LINE2( 0xDC,0xC1 )              /* fadd        st(1),st  */ \
_LINE2( 0xD9,0xCC )              /* fxch        st(4)  */ \
_LINE2( 0xDE,0xE3 )              /* fsubrp      st(3),st  */ \
_LINE2( 0xD9,0xCC )              /* fxch        st(4)  */ \
_LINE2( 0xDE,0xE1 )              /* fsubrp      st(1),st  */ \
ASM( mov eax,[esp+0xB8] ) \
_LINE2( 0xD9,0xCA )              /* fxch        st(2)  */ \
_LINE2( 0xDE,0xE4 )              /* fsubrp      st(4),st  */ \
_LINE2( 0xDD,0x02 )              /* fld         qword ptr [edx]  */ \
_LINE4( 0xDC,0x4C,0x24,0x08 )        /* fmul        qword ptr [esp+8]  */ \
_LINE2( 0xDD,0x19 )              /* fstp        qword ptr [ecx]  */ \
_LINE2( 0xDC,0x0A )              /* fmul        qword ptr [edx]  */ \
_LINE3( 0xDD,0x59,0x08 )           /* fstp        qword ptr [ecx+8]  */ \
_LINE2( 0xDD,0x02 )              /* fld         qword ptr [edx]  */ \
_LINE4( 0xDC,0x4C,0x24,0x30 )        /* fmul        qword ptr [esp+30h]  */ \
_LINE3( 0xDD,0x59,0x10 )           /* fstp        qword ptr [ecx+10h]  */ \
_LINE2( 0xD9,0xEE )              /* fldz  */ \
_LINE3( 0xDD,0x51,0x18 )           /* fst         qword ptr [ecx+18h]  */ \
_LINE3( 0xDD,0x42,0x08 )           /* fld         qword ptr [edx+8]  */ \
_LINE4( 0xDC,0x4C,0x24,0x20 )        /* fmul        qword ptr [esp+20h]  */ \
_LINE3( 0xDD,0x59,0x20 )           /* fstp        qword ptr [ecx+20h]  */ \
_LINE3( 0xDD,0x42,0x08 )           /* fld         qword ptr [edx+8]  */ \
_LINE4( 0xDC,0x4C,0x24,0x10 )        /* fmul        qword ptr [esp+10h]  */ \
_LINE3( 0xDD,0x59,0x28 )           /* fstp        qword ptr [ecx+28h]  */ \
_LINE3( 0xDD,0x42,0x08 )           /* fld         qword ptr [edx+8]  */ \
_LINE2( 0xDE,0xCC )              /* fmulp       st(4),st  */ \
_LINE2( 0xD9,0xCB )              /* fxch        st(3)  */ \
_LINE3( 0xDD,0x59,0x30 )           /* fstp        qword ptr [ecx+30h]  */ \
_LINE2( 0xD9,0xCA )              /* fxch        st(2)  */ \
_LINE3( 0xDD,0x51,0x38 )           /* fst         qword ptr [ecx+38h]  */ \
_LINE3( 0xDD,0x42,0x10 )           /* fld         qword ptr [edx+10h]  */ \
_LINE2( 0xDE,0xCB )              /* fmulp       st(3),st  */ \
_LINE2( 0xD9,0xCA )              /* fxch        st(2)  */ \
_LINE3( 0xDD,0x59,0x40 )           /* fstp        qword ptr [ecx+40h]  */ \
_LINE3( 0xDC,0x4A,0x10 )           /* fmul        qword ptr [edx+10h]  */ \
_LINE3( 0xDD,0x59,0x48 )           /* fstp        qword ptr [ecx+48h]  */ \
_LINE3( 0xDD,0x42,0x10 )           /* fld         qword ptr [edx+10h]  */ \
_LINE4( 0xDC,0x4C,0x24,0x18 )        /* fmul        qword ptr [esp+18h]  */ \
_LINE3( 0xDD,0x59,0x50 )           /* fstp        qword ptr [ecx+50h]  */ \
_LINE3( 0xDD,0x59,0x58 )           /* fstp        qword ptr [ecx+58h]  */ \
_LINE2( 0xDD,0x00 )              /* fld         qword ptr [eax]  */ \
_LINE3( 0xDD,0x59,0x60 )           /* fstp        qword ptr [ecx+60h]  */ \
_LINE3( 0xDD,0x40,0x08 )           /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDD,0x59,0x68 )           /* fstp        qword ptr [ecx+68h]  */ \
_LINE3( 0xDD,0x40,0x10 )           /* fld         qword ptr [eax+10h]  */ \
_LINE3( 0xDD,0x59,0x70 )           /* fstp        qword ptr [ecx+70h]  */ \
_LINE3( 0xDD,0x59,0x78 )           /* fstp        qword ptr [ecx+78h]  */ \
_LINE6( 0x81,0xC4,0xB0,0x00,0x00,0x00 )  /* add         esp,0B0h  */ \
_END_ASM

/// Создание матрици трансформации двойной точности, команды SSE4
/// @brief for CPUTYPE4
#define MATRIXP4DDTRSSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+C]  */ \
_LINE4( 0x8B,0x54,0x24,0x10 )                               /* mov         edx,dword ptr [esp+0x10]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE5( 0xF2,0x0F,0xF0,0x50,0x10 )                          /* lddqu       xmm2,xmmword ptr [eax+10h]  */ \
_LINE3( 0x0F,0x28,0xDA )                                    /* movaps      xmm3,xmm2  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC9,0x31 )                     /* dppd        xmm1,xmm1,31h  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xDB,0x31 )                     /* dppd        xmm3,xmm3,31h  */ \
_LINE4( 0xF2,0x0F,0x58,0xCB )                               /* addsd       xmm1,xmm3  */ \
_LINE5( 0xB8,0x02,0x00,0x00,0x00 )                          /* mov         eax,2  */ \
_LINE4( 0xF2,0x0F,0x2A,0xE0 )                               /* cvtsi2sd    xmm4,eax  */ \
_LINE3( 0x0F,0x28,0xF0 )                                    /* movaps      xmm6,xmm0  */ \
_LINE4( 0xF2,0x0F,0x5E,0xE1 )                               /* divsd       xmm4,xmm1  */ \
_LINE3( 0x0F,0x28,0xFA )                                    /* movaps      xmm7,xmm2  */ \
_LINE3( 0x0F,0x16,0xE4 )                                    /* movlhps     xmm4,xmm4  */ \
_LINE3( 0x0F,0x12,0xC8 )                                    /* movhlps     xmm1,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xF4 )                               /* mulpd       xmm6,xmm4 b[0]*s b[1]*s */ \
_LINE3( 0x0F,0x16,0xCA )                                    /* movlhps     xmm1,xmm2 b[1] b[2] */ \
_LINE4( 0x66,0x0F,0x59,0xFC )                               /* mulpd       xmm7,xmm4 b[2]*s b[3]*s */ \
_LINE3( 0x0F,0x12,0xDE )                                    /* movhlps     xmm3,xmm6 b[1]*s */ \
_LINE3( 0x0F,0x28,0xE0 )                                    /* movaps      xmm4,xmm0 b[0] b[1] */ \
_LINE5( 0xB8,0x01,0x00,0x00,0x00 )                          /* mov         eax,1  */ \
_LINE3( 0x0F,0x16,0xDF )                                    /* movlhps     xmm3,xmm7 b[1]*s b[2]*s */ \
_LINE4( 0xF2,0x0F,0x59,0xE6 )                               /* mulsd       xmm4,xmm6 b[0]*f[0] */ \
_LINE4( 0x66,0x0F,0x59,0xD9 )                               /* mulpd       xmm3,xmm1 f[6] f[8] */ \
_LINE4( 0xF2,0x0F,0x2A,0xE8 )                               /* cvtsi2sd    xmm5,eax  */ \
_LINE3( 0x0F,0x16,0xE4 )                                    /* movlhps     xmm4,xmm4 f[3] f[3] */ \
_LINE3( 0x0F,0x16,0xED )                                    /* movlhps     xmm5,xmm5 1 1 */ \
_LINE4( 0x66,0x0F,0x58,0xE3 )                               /* addpd       xmm4,xmm3 f[3]+f[6] f[3]+f[8] */ \
_LINE3( 0x0F,0x28,0xC5 )                                    /* movaps      xmm0,xmm5 1 1 */ \
_LINE4( 0x66,0x0F,0x5C,0xEC )                               /* subpd       xmm5,xmm4 1-(f[3]+f[6]) 1-(f[3]+f[8]) */ \
_LINE3( 0x0F,0x12,0xFF )                                    /* movhlps     xmm7,xmm7 b[3]*s b[3]*s */ \
_LINE3( 0x0F,0x16,0xE6 )                                    /* movlhps     xmm4,xmm6 f[3]+f[6] b[0]*s */ \
_LINE4( 0x66,0x0F,0x59,0xF9 )                               /* mulpd       xmm7,xmm1 f[10] f[11] */ \
_LINE3( 0x0F,0x12,0xE6 )                                    /* movhlps     xmm4,xmm6 b[1]*s b[0]*s */ \
_LINE5( 0x66,0x0F,0xC6,0xFF,0x01 )                          /* shufpd      xmm7, xmm7, 1 f[11] f[10] */ \
_LINE4( 0x66,0x0F,0x59,0xE2 )                               /* mulpd       xmm4,xmm2 f[7] f[9] */ \
_LINE3( 0x0F,0x16,0xF6 )                                    /* movlhps     xmm6,xmm6 b[0]*s b[0]*s */ \
_LINE4( 0x66,0x0F,0x7C,0xDC )                               /* haddpd      xmm3,xmm4 f[6]+f[8] f[7]+f[9] */ \
_LINE4( 0x66,0x0F,0x7D,0xE4 )                               /* hsubpd      xmm4,xmm4 f[7]-f[9] f[7]-f[9] */ \
_LINE4( 0x66,0x0F,0x59,0xF1 )                               /* mulpd       xmm6,xmm1 f[4] f[5] */ \
_LINE4( 0xF2,0x0F,0x5C,0xC3 )                               /* subsd       xmm0,xmm3 1-(f[6]+f[8]) */ \
_LINE3( 0x0F,0x28,0xD6 )                                    /* movaps      xmm2,xmm6 f[4] f[5] */ \
_LINE4( 0x66,0x0F,0x5C,0xD7 )                               /* subpd       xmm2,xmm7 f[4]-f[11] f[5]-f[10] */ \
_LINE4( 0x66,0x0F,0x58,0xF7 )                               /* addpd       xmm6,xmm7 f[4]+f[11] f[5]+f[10] */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x0F,0x17,0x40,0x78 )                               /* movhps      qword ptr[eax + 78h], xmm0  */ \
_LINE3( 0x0F,0x12,0xE6 )                                    /* movhlps     xmm4,xmm6 f[5]+f[10] f[7]-f[9] */ \
_LINE3( 0x0F,0x12,0xDA )                                    /* movhlps     xmm3,xmm2 f[5]-f[10] f[7]+f[9] */ \
_LINE3( 0x0F,0x16,0xC2 )                                    /* movlhps     xmm0,xmm2 1-(f[6]+f[8]) f[4]-f[11] */ \
_LINE4( 0xF2,0x0F,0x10,0xD6 )                               /* movsd       xmm2, xmm6 f[4]+f[11] */ \
_LINE5( 0x66,0x0F,0xC6,0xD5,0x04 )                          /* shufpd      xmm2, xmm5, 4 f[4]+f[11] 1-(f[3]+f[8]) */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x66,0x0F,0x59,0xE1 )                               /* mulpd       xmm4,xmm1  */ \
_LINE4( 0xF2,0x0F,0x12,0xF9 )                               /* movddup     xmm7, xmm1  */ \
_LINE3( 0x0F,0x12,0xC9 )                                    /* movhlps     xmm1,xmm1  */ \
_LINE4( 0x66,0x0F,0x59,0xC7 )                               /* mulpd       xmm0,xmm7  */ \
_LINE4( 0x66,0x0F,0x59,0xD1 )                               /* mulpd       xmm2,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x00 )                               /* movupd      xmmword ptr [eax],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x60,0x10 )                          /* movsd       mmword ptr[eax+10h],xmm4  */ \
_LINE5( 0x66,0x0F,0x11,0x50,0x20 )                          /* movupd      xmmword ptr [eax+20h],xmm2  */ \
_LINE4(0x0F, 0x17, 0x60, 0x30 )                             /* movhps      qword ptr[eax+30h],xmm4  */ \
_LINE5(0xF2, 0x0F, 0x12, 0x7A, 0x10 )                       /* movddup     xmm7, mmword ptr[edx+10h]  */ \
_LINE4(0x66, 0x0F, 0x59, 0xDF)                              /* mulpd       xmm3,xmm7  */ \
_LINE4(0xF2, 0x0F, 0x59, 0xEF)                              /* mulsd       xmm5,xmm7 */ \
_LINE5(0x66, 0x0F, 0x11, 0x58, 0x40)                        /* movupd      xmmword ptr [eax+40h],xmm3  */ \
_LINE5(0xF2, 0x0F, 0x11, 0x68, 0x50 )                       /* movsd       mmword ptr[eax+50h],xmm5  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+0x8]  */ \
_LINE5( 0xF2,0x0F,0x10,0x72,0x10 )                          /* movsd       xmm6, mmword ptr[edx + 10h]  */ \
_LINE4(0xF2, 0x0F, 0xF0, 0x0A)                              /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE5(0x66, 0x0F, 0x11, 0x48, 0x60)                        /* movupd      xmmword ptr [eax+60h],xmm1  */ \
_LINE5(0xF2, 0x0F, 0x11, 0x70, 0x70)                        /* movsd       mmword ptr[eax + 70h], xmm6  */ \
_LINE4(0x0F, 0x17, 0x70, 0x18)                              /* movhps      qword ptr[eax + 18h], xmm6  */ \
_LINE4(0x0F, 0x17, 0x70, 0x38)                              /* movhps      qword ptr[eax + 38h], xmm6  */ \
_LINE4(0x0F, 0x17, 0x70, 0x58 )                             /* movhps      qword ptr[eax + 58h], xmm6  */ \
_END_ASM

/// Создание матрици трансформации одинарной точности, команды AVX ???
/// @brief for CPUTYPE4
#define MATRIXP4DDTRSAVX_STD \
_BEGIN_ASM \
_LINE4(0x8B, 0x44, 0x24, 0x0C)                               /* mov         eax,dword ptr [esp+12]  */ \
_LINE4(0xC5, 0xFD, 0x10, 0x00)                              /* vmovupd     ymm0,ymmword ptr [edx]  */ \
ASM( vmovaps ymm2,ymm0 )                                    /* movaps      xmm2,xmm0  */ \
	ASM(vdpps ymm2,ymm2, ymm2, 0xF1)                     /* dpps        xmm2,xmm2,0F1h  */ \
_LINE5(0xB8, 0x02, 0x00, 0x00, 0x00)                          /* mov         eax,2  */ \
ASM(vxorps       ymm7,ymm7, ymm7)                                    /* xorps       xmm7,xmm7  */ \
_LINE4(0xF3, 0x0F, 0x2A, 0xC8)                               /* cvtsi2ss    xmm1,eax  */ \
_LINE5(0xB8, 0x01, 0x00, 0x00, 0x00)                          /* mov         eax,1  */ \
_LINE4(0xF3, 0x0F, 0x2A, 0xF8)                               /* cvtsi2ss    xmm7,eax  */ \
_LINE4(0xF3, 0x0F, 0x5E, 0xCA)                               /* divss       xmm1,xmm2  */ \
ASM(vshufps      ymm1,ymm1, ymm1, 0)                               /* shufps      xmm1,xmm1,0  */ \
ASM(vmovaps ymm3, ymm0)                                    /* movaps      xmm3,xmm0  */ \
ASM(vmulps ymm3,ymm3, ymm1)                                    /* mulps       xmm3,xmm1 (f 0-2) */ \
ASM(vmovaps ymm2, ymm0)                                    /* movaps      xmm2,xmm0  */ \
ASM(vshufps      ymm2,ymm2, ymm2, 0)                               /* shufps      xmm2,xmm2,0  */ \
ASM(vmovaps ymm1, ymm3)                                    /* movaps      xmm1,xmm3  */ \
	_LINE3(0x0F, 0x59, 0xCA)                                    /* mulps       xmm1,xmm2 (f 3-5) */ \
	_LINE3(0x0F, 0x28, 0xE3)                                    /* movaps      xmm4,xmm3  */ \
	_LINE4(0x0F, 0xC6, 0xE4, 0xE9)                               /* shufps      xmm4,xmm4,0E9h  */ \
	_LINE4(0x0F, 0xC6, 0xC0, 0xE5)                               /* shufps      xmm0,xmm0,0E5h  */ \
	_LINE3(0x0F, 0x59, 0xE0)                                    /* mulps       xmm4,xmm0 (f 6-8) */ \
	_LINE4(0x0F, 0xC6, 0xC0, 0xFF)                               /* shufps      xmm0,xmm0,0FFh  */ \
	_LINE3(0x0F, 0x59, 0xC3)                                    /* mulps       xmm0,xmm3 (f 9-11) */ \
	_LINE3(0x0F, 0x28, 0xD9)                                    /* movaps      xmm3,xmm1  */ \
	_LINE4(0x0F, 0xC6, 0xDC, 0x00)                               /* shufps      xmm3,xmm4,0x0 (f 3 3 6 6) */ \
	_LINE4(0x0F, 0xC6, 0xCC, 0x59)                               /* shufps      xmm1,xmm4,59h (f 4 5 7 7) */ \
	_LINE4(0x0F, 0xC6, 0xC0, 0x06)                               /* shufps      xmm0,xmm0,6 (f 11 10 9 9) */ \
	_LINE4(0x0F, 0xC6, 0xE4, 0xA8)                               /* shufps      xmm4,xmm4,0A8h (f 6 8 8 8) */ \
	_LINE3(0x0F, 0x28, 0xD1)                                    /* movaps      xmm2,xmm1  */ \
	_LINE3(0x0F, 0x58, 0xC8)                                    /* addps       xmm1,xmm0 (3 5 7) */ \
	_LINE3(0x0F, 0x5C, 0xD0)                                    /* subps       xmm2,xmm0 (4 6 8) */ \
	_LINE3(0x0F, 0x58, 0xE3)                                    /* addps       xmm4,xmm3  */ \
	_LINE4(0x0F, 0xC6, 0xFF, 0x40)                               /* shufps      xmm7,xmm7,40h  */ \
	_LINE4(0x8B, 0x54, 0x24, 0x04)                               /* mov         edx,dword ptr [esp+4]  */ \
	_LINE5(0xF3, 0x0F, 0x11, 0x7A, 0x3C)                          /* movss       dword ptr [edx+3Ch],xmm7  */ \
	_LINE3(0x0F, 0x5C, 0xFC)                                    /* subps       xmm7,xmm4 (2 1 0) */ \
	_LINE4(0x8B, 0x44, 0x24, 0x10)                               /* mov         eax,dword ptr [esp+16]  */ \
	_LINE3(0x0F, 0x28, 0xC1)                                    /* movaps      xmm0,xmm1 (3 5 7) */ \
	_LINE3(0x0F, 0x28, 0xDA)                                    /* movaps      xmm3,xmm2 (4 6 8) */ \
	_LINE3(0x0F, 0x28, 0xE7)                                    /* movaps      xmm4,xmm7 (2 1 0) */ \
	_LINE4(0xF3, 0x0F, 0x10, 0x28)                               /* movss       xmm5,dword ptr [eax]  */ \
	_LINE4(0x0F, 0xC6, 0xC0, 0xDC)                               /* shufps      xmm0,xmm0,0DCh (3 x 5 x) */ \
	_LINE4(0x0F, 0xC6, 0xDB, 0xDE)                               /* shufps      xmm3,xmm3,0DEh (8 x 6 x) */ \
	_LINE4(0x0F, 0xC6, 0xE4, 0xCE)                               /* shufps      xmm4,xmm4,0CEh (0 x 2 x) */ \
	_LINE4(0x0F, 0xC6, 0xED, 0x40)                               /* shufps      xmm5,xmm5,40h  */ \
	_LINE3(0x0F, 0x12, 0xCB)                                    /* movhlps     xmm1,xmm3 (6 x 7 x) */ \
	_LINE3(0x0F, 0x16, 0xD4)                                    /* movlhps     xmm2,xmm4 () */ \
	_LINE3(0x0F, 0x16, 0xF8)                                    /* movlhps     xmm7,xmm0 (2 1 3 x) */ \
	_LINE5(0xF3, 0x0F, 0x10, 0x70, 0x04)                          /* movss       xmm6,dword ptr [eax+4]  */ \
	_LINE4(0x0F, 0xC6, 0xCC, 0xE8)                               /* shufps      xmm1,xmm4,0E8h  */ \
	_LINE4(0x0F, 0xC6, 0xD0, 0xE2)                               /* shufps      xmm2,xmm0,0E2h  */ \
	_LINE4(0x0F, 0xC6, 0xFB, 0xC6)                               /* shufps      xmm7,xmm3,0C6h (3 1 8 x) */ \
	_LINE5(0xF3, 0x0F, 0x10, 0x60, 0x08)                          /* movss       xmm4,dword ptr [eax+8]  */ \
	_LINE4(0x0F, 0xC6, 0xF6, 0x40)                               /* shufps      xmm6,xmm6,40h  */ \
	_LINE3(0x0F, 0x59, 0xD5)                                    /* mulps       xmm2,xmm5  */ \
	_LINE4(0x0F, 0xC6, 0xE4, 0x40)                               /* shufps      xmm4,xmm4,40h  */ \
	_LINE3(0x0F, 0x59, 0xFE)                                    /* mulps       xmm7,xmm6  */ \
	_LINE3(0x0F, 0x11, 0x12)                                    /* movups      xmmword ptr [edx],xmm2  */ \
	_LINE3(0x0F, 0x59, 0xCC)                                    /* mulps       xmm1,xmm4  */ \
	_LINE4(0x8B, 0x44, 0x24, 0x08)                               /* mov         eax,dword ptr [esp+8]  */ \
	_LINE4(0x0F, 0x11, 0x7A, 0x10)                               /* movups      xmmword ptr [edx+10h],xmm7  */ \
	_LINE4(0x0F, 0x11, 0x4A, 0x20)                               /* movups      xmmword ptr [edx+20h],xmm1  */ \
	_LINE5(0xF3, 0x0F, 0x10, 0x58, 0x08)                          /* movss       xmm3,dword ptr [eax+8]  */ \
	_LINE3(0x0F, 0x16, 0x28)                                    /* movhps      xmm5,qword ptr [eax]  */ \
	_LINE5(0xF3, 0x0F, 0x11, 0x5A, 0x38)                          /* movss       dword ptr [edx+38h],xmm3  */ \
	_LINE4(0x0F, 0x17, 0x6A, 0x30)                               /* movhps      qword ptr [edx+30h],xmm5  */ \
_END_ASM

#endif /* X86MATRIX_TRS_H_ */
