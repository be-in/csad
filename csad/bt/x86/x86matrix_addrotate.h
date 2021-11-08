//=============================================================================
///**
// *  @file   matrix_addrotate.h
// *
// *  $Id: matrix_addrotate.h 16.10.2011  $
// *
// *  @brief generator 3, assembler matrix double/float addrotate, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_MATRIX_ADDROTATE_H_
#define GEN3_MATRIX_ADDROTATE_H_

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

/// ѕоворот матрици одинарной точности, команды SSE
/// @brief for CPUTYPE3
#define MATRIXP4DADDROTATESSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8]  */ \
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
_LINE4( 0x8B,0x54,0x24,0x0C )                               /* mov         edx,dword ptr [esp+C]  */ \
_LINE3( 0x0F,0x5C,0xFC )                                    /* subps       xmm7,xmm4 (2 1 0) */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x0F,0x12,0x40,0x20 )                               /* movlps      xmm0,qword ptr [eax+20h]  */ \
_LINE3( 0x0F,0x28,0xF7 )                                    /* movaps      xmm6,xmm7  */ \
_LINE3( 0x0F,0x12,0x20 )                                    /* movlps      xmm4,qword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xEA )                                    /* movaps      xmm5,xmm2  */ \
_LINE4( 0x0F,0x12,0x58,0x10 )                               /* movlps      xmm3,qword ptr [eax+10h]  */ \
_LINE4( 0x0F,0xC6,0xF6,0xAA )                               /* shufps      xmm6,xmm6,AAh  */ \
_LINE4( 0x0F,0x16,0x40,0x28 )                               /* movhps      xmm0,qword ptr [eax+28h]  */ \
_LINE4( 0x0F,0xC6,0xED,0x00 )                               /* shufps      xmm5,xmm5,00h  */ \
_LINE4( 0x0F,0x16,0x60,0x08 )                               /* movhps      xmm4,qword ptr [eax+8]  */ \
_LINE4( 0x0F,0x16,0x58,0x18 )                               /* movhps      xmm3,qword ptr [eax+18h]  */ \
_LINE3( 0x0F,0x59,0xF4 )                                    /* mulps       xmm6,xmm4  */ \
_LINE3( 0x0F,0x59,0xEB )                                    /* mulps       xmm5,xmm3  */ \
_LINE3( 0x0F,0x58,0xF5 )                                    /* addps       xmm6,xmm5  */ \
_LINE3( 0x0F,0x28,0xE9 )                                    /* movaps      xmm5,xmm1  */ \
_LINE4( 0x0F,0xC6,0xED,0x55 )                               /* shufps      xmm5,xmm5,55h  */ \
_LINE3( 0x0F,0x59,0xE8 )                                    /* mulps       xmm5,xmm0  */ \
_LINE3( 0x0F,0x58,0xF5 )                                    /* addps       xmm6,xmm5  */ \
_LINE3( 0x0F,0x13,0x32 )                                    /* movlps      qword ptr [edx],xmm6  */ \
_LINE4( 0x0F,0x17,0x72,0x08 )                               /* movhps      qword ptr [edx+8],xmm6  */ \
_LINE3( 0x0F,0x28,0xEF )                                    /* movaps      xmm5,xmm7  */ \
_LINE3( 0x0F,0x28,0xF1 )                                    /* movaps      xmm6,xmm1  */ \
_LINE4( 0x0F,0xC6,0xED,0x55 )                               /* shufps      xmm5,xmm5,55h  */ \
_LINE4( 0x0F,0xC6,0xF6,0x00 )                               /* shufps      xmm6,xmm6,00h  */ \
_LINE3( 0x0F,0x59,0xEB )                                    /* mulps       xmm5,xmm3  */ \
_LINE3( 0x0F,0x59,0xF4 )                                    /* mulps       xmm6,xmm4  */ \
_LINE4( 0x0F,0xC6,0xC9,0xAA )                               /* shufps      xmm1,xmm1,AAh  */ \
_LINE3( 0x0F,0x58,0xF5 )                                    /* addps       xmm6,xmm5  */ \
_LINE4( 0x0F,0xC6,0xFF,0x00 )                               /* shufps      xmm7,xmm7,00h  */ \
_LINE3( 0x0F,0x28,0xEA )                                    /* movaps      xmm5,xmm2  */ \
_LINE3( 0x0F,0x59,0xF8 )                                    /* mulps       xmm7,xmm0  */ \
_LINE4( 0x0F,0xC6,0xED,0xAA )                               /* shufps      xmm5,xmm5,AAh  */ \
_LINE4( 0x0F,0xC6,0xD2,0x55 )                               /* shufps      xmm2,xmm2,55h  */ \
_LINE3( 0x0F,0x59,0xE8 )                                    /* mulps       xmm5,xmm0  */ \
_LINE3( 0x0F,0x59,0xCB )                                    /* mulps       xmm1,xmm3  */ \
_LINE3( 0x0F,0x58,0xF5 )                                    /* addps       xmm6,xmm5  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE4( 0x0F,0x13,0x72,0x10 )                               /* movlps      qword ptr [edx+10h],xmm6  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE4( 0x0F,0x12,0x40,0x30 )                               /* movlps      xmm0,qword ptr [eax+30h]  */ \
_LINE4( 0x0F,0x17,0x72,0x18 )                               /* movhps      qword ptr [edx+18h],xmm6  */ \
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
_LINE4( 0x0F,0x16,0x40,0x38 )                               /* movhps      xmm0,qword ptr [eax+38h]  */ \
_LINE4( 0x0F,0x13,0x52,0x20 )                               /* movlps      qword ptr [edx+20h],xmm2  */ \
_LINE4( 0x0F,0x13,0x42,0x30 )                               /* movlps      qword ptr [edx+30h],xmm0  */ \
_LINE4( 0x0F,0x17,0x52,0x28 )                               /* movhps      qword ptr [edx+28h],xmm2  */ \
_LINE4( 0x0F,0x17,0x42,0x38 )                               /* movhps      qword ptr [edx+38h],xmm0  */ \
_END_ASM

/// ѕоворот матрици одинарной точности, команды SSE2
/// @brief for CPUTYPE3
#define MATRIXP4DADDROTATESSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8]  */ \
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
_LINE4( 0x8B,0x54,0x24,0x0C )                               /* mov         edx,dword ptr [esp+C]  */ \
_LINE3( 0x0F,0x5C,0xFC )                                    /* subps       xmm7,xmm4 (2 1 0) */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x0F,0x12,0x40,0x20 )                               /* movlps      xmm0,qword ptr [eax+20h]  */ \
_LINE3( 0x0F,0x28,0xF7 )                                    /* movaps      xmm6,xmm7  */ \
_LINE3( 0x0F,0x12,0x20 )                                    /* movlps      xmm4,qword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xEA )                                    /* movaps      xmm5,xmm2  */ \
_LINE4( 0x0F,0x12,0x58,0x10 )                               /* movlps      xmm3,qword ptr [eax+10h]  */ \
_LINE4( 0x0F,0xC6,0xF6,0xAA )                               /* shufps      xmm6,xmm6,AAh  */ \
_LINE4( 0x0F,0x16,0x40,0x28 )                               /* movhps      xmm0,qword ptr [eax+28h]  */ \
_LINE4( 0x0F,0xC6,0xED,0x00 )                               /* shufps      xmm5,xmm5,00h  */ \
_LINE4( 0x0F,0x16,0x60,0x08 )                               /* movhps      xmm4,qword ptr [eax+8]  */ \
_LINE4( 0x0F,0x16,0x58,0x18 )                               /* movhps      xmm3,qword ptr [eax+18h]  */ \
_LINE3( 0x0F,0x59,0xF4 )                                    /* mulps       xmm6,xmm4  */ \
_LINE3( 0x0F,0x59,0xEB )                                    /* mulps       xmm5,xmm3  */ \
_LINE3( 0x0F,0x58,0xF5 )                                    /* addps       xmm6,xmm5  */ \
_LINE3( 0x0F,0x28,0xE9 )                                    /* movaps      xmm5,xmm1  */ \
_LINE4( 0x0F,0xC6,0xED,0x55 )                               /* shufps      xmm5,xmm5,55h  */ \
_LINE3( 0x0F,0x59,0xE8 )                                    /* mulps       xmm5,xmm0  */ \
_LINE3( 0x0F,0x58,0xF5 )                                    /* addps       xmm6,xmm5  */ \
_LINE3( 0x0F,0x13,0x32 )                                    /* movlps      qword ptr [edx],xmm6  */ \
_LINE4( 0x0F,0x17,0x72,0x08 )                               /* movhps      qword ptr [edx+8],xmm6  */ \
_LINE3( 0x0F,0x28,0xEF )                                    /* movaps      xmm5,xmm7  */ \
_LINE3( 0x0F,0x28,0xF1 )                                    /* movaps      xmm6,xmm1  */ \
_LINE4( 0x0F,0xC6,0xED,0x55 )                               /* shufps      xmm5,xmm5,55h  */ \
_LINE4( 0x0F,0xC6,0xF6,0x00 )                               /* shufps      xmm6,xmm6,00h  */ \
_LINE3( 0x0F,0x59,0xEB )                                    /* mulps       xmm5,xmm3  */ \
_LINE3( 0x0F,0x59,0xF4 )                                    /* mulps       xmm6,xmm4  */ \
_LINE4( 0x0F,0xC6,0xC9,0xAA )                               /* shufps      xmm1,xmm1,AAh  */ \
_LINE3( 0x0F,0x58,0xF5 )                                    /* addps       xmm6,xmm5  */ \
_LINE4( 0x0F,0xC6,0xFF,0x00 )                               /* shufps      xmm7,xmm7,00h  */ \
_LINE3( 0x0F,0x28,0xEA )                                    /* movaps      xmm5,xmm2  */ \
_LINE3( 0x0F,0x59,0xF8 )                                    /* mulps       xmm7,xmm0  */ \
_LINE4( 0x0F,0xC6,0xED,0xAA )                               /* shufps      xmm5,xmm5,AAh  */ \
_LINE4( 0x0F,0xC6,0xD2,0x55 )                               /* shufps      xmm2,xmm2,55h  */ \
_LINE3( 0x0F,0x59,0xE8 )                                    /* mulps       xmm5,xmm0  */ \
_LINE3( 0x0F,0x59,0xCB )                                    /* mulps       xmm1,xmm3  */ \
_LINE3( 0x0F,0x58,0xF5 )                                    /* addps       xmm6,xmm5  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE4( 0x0F,0x13,0x72,0x10 )                               /* movlps      qword ptr [edx+10h],xmm6  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE4( 0x0F,0x12,0x40,0x30 )                               /* movlps      xmm0,qword ptr [eax+30h]  */ \
_LINE4( 0x0F,0x17,0x72,0x18 )                               /* movhps      qword ptr [edx+18h],xmm6  */ \
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
_LINE4( 0x0F,0x16,0x40,0x38 )                               /* movhps      xmm0,qword ptr [eax+38h]  */ \
_LINE4( 0x0F,0x13,0x52,0x20 )                               /* movlps      qword ptr [edx+20h],xmm2  */ \
_LINE4( 0x0F,0x13,0x42,0x30 )                               /* movlps      qword ptr [edx+30h],xmm0  */ \
_LINE4( 0x0F,0x17,0x52,0x28 )                               /* movhps      qword ptr [edx+28h],xmm2  */ \
_LINE4( 0x0F,0x17,0x42,0x38 )                               /* movhps      qword ptr [edx+38h],xmm0  */ \
_END_ASM

/// ѕоворот матрици одинарной точности, команды SSE3
/// @brief for CPUTYPE4
#define MATRIXP4DADDROTATESSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8]  */ \
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
_LINE4( 0x8B,0x54,0x24,0x0C )                               /* mov         edx,dword ptr [esp+C]  */ \
_LINE3( 0x0F,0x5C,0xFC )                                    /* subps       xmm7,xmm4 (2 1 0) */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x40,0x20 )                          /* lddqu       xmm0,[eax+20h]  */ \
_LINE3( 0x0F,0x28,0xF7 )                                    /* movaps      xmm6,xmm7  */ \
_LINE4( 0xF2,0x0F,0xF0,0x20 )                               /* lddqu       xmm4,[eax]  */ \
_LINE3( 0x0F,0x28,0xEA )                                    /* movaps      xmm5,xmm2  */ \
_LINE5( 0xF2,0x0F,0xF0,0x58,0x10 )                          /* lddqu       xmm3,[eax+10h]  */ \
_LINE4( 0x0F,0xC6,0xF6,0xAA )                               /* shufps      xmm6,xmm6,AAh  */ \
_LINE4( 0x0F,0xC6,0xED,0x00 )                               /* shufps      xmm5,xmm5,00h  */ \
_LINE3( 0x0F,0x59,0xF4 )                                    /* mulps       xmm6,xmm4  */ \
_LINE3( 0x0F,0x59,0xEB )                                    /* mulps       xmm5,xmm3  */ \
_LINE3( 0x0F,0x58,0xF5 )                                    /* addps       xmm6,xmm5  */ \
_LINE3( 0x0F,0x28,0xE9 )                                    /* movaps      xmm5,xmm1  */ \
_LINE4( 0x0F,0xC6,0xED,0x55 )                               /* shufps      xmm5,xmm5,55h  */ \
_LINE3( 0x0F,0x59,0xE8 )                                    /* mulps       xmm5,xmm0  */ \
_LINE3( 0x0F,0x58,0xF5 )                                    /* addps       xmm6,xmm5  */ \
_LINE3( 0x0F,0x13,0x32 )                                    /* movlps      qword ptr [edx],xmm6  */ \
_LINE4( 0x0F,0x17,0x72,0x08 )                               /* movhps      qword ptr [edx+8],xmm6  */ \
_LINE3( 0x0F,0x28,0xEF )                                    /* movaps      xmm5,xmm7  */ \
_LINE3( 0x0F,0x28,0xF1 )                                    /* movaps      xmm6,xmm1  */ \
_LINE4( 0x0F,0xC6,0xED,0x55 )                               /* shufps      xmm5,xmm5,55h  */ \
_LINE4( 0x0F,0xC6,0xF6,0x00 )                               /* shufps      xmm6,xmm6,00h  */ \
_LINE3( 0x0F,0x59,0xEB )                                    /* mulps       xmm5,xmm3  */ \
_LINE3( 0x0F,0x59,0xF4 )                                    /* mulps       xmm6,xmm4  */ \
_LINE4( 0x0F,0xC6,0xC9,0xAA )                               /* shufps      xmm1,xmm1,AAh  */ \
_LINE3( 0x0F,0x58,0xF5 )                                    /* addps       xmm6,xmm5  */ \
_LINE4( 0x0F,0xC6,0xFF,0x00 )                               /* shufps      xmm7,xmm7,00h  */ \
_LINE3( 0x0F,0x28,0xEA )                                    /* movaps      xmm5,xmm2  */ \
_LINE3( 0x0F,0x59,0xF8 )                                    /* mulps       xmm7,xmm0  */ \
_LINE4( 0x0F,0xC6,0xED,0xAA )                               /* shufps      xmm5,xmm5,AAh  */ \
_LINE4( 0x0F,0xC6,0xD2,0x55 )                               /* shufps      xmm2,xmm2,55h  */ \
_LINE3( 0x0F,0x59,0xE8 )                                    /* mulps       xmm5,xmm0  */ \
_LINE3( 0x0F,0x59,0xCB )                                    /* mulps       xmm1,xmm3  */ \
_LINE3( 0x0F,0x58,0xF5 )                                    /* addps       xmm6,xmm5  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE4( 0x0F,0x13,0x72,0x10 )                               /* movlps      qword ptr [edx+10h],xmm6  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF2,0x0F,0xF0,0x40,0x30 )                          /* lddqu       xmm0,[eax+30h]  */ \
_LINE4( 0x0F,0x17,0x72,0x18 )                               /* movhps      qword ptr [edx+18h],xmm6  */ \
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
_LINE4( 0x0F,0x13,0x52,0x20 )                               /* movlps      qword ptr [edx+20h],xmm2  */ \
_LINE4( 0x0F,0x13,0x42,0x30 )                               /* movlps      qword ptr [edx+30h],xmm0  */ \
_LINE4( 0x0F,0x17,0x52,0x28 )                               /* movhps      qword ptr [edx+28h],xmm2  */ \
_LINE4( 0x0F,0x17,0x42,0x38 )                               /* movhps      qword ptr [edx+38h],xmm0  */ \
_END_ASM

/// ѕоворот матрици одинарной точности, команды SSE4
/// @brief for CPUTYPE4
#define MATRIXP4DADDROTATESSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,[eax]  */ \
_LINE3( 0x0F,0x28,0xD0 )                                    /* movaps      xmm2,xmm0  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xD2,0xF1 )                     /* dpps        xmm2,xmm2,0F1h  */ \
_LINE5( 0xB8,0x02,0x00,0x00,0x00 )                          /* mov         eax,2  */ \
_LINE3( 0x0F,0x57,0xFF )                                    /* xorps       xmm7,xmm7  */ \
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
_LINE4( 0x8B,0x54,0x24,0x0C )                               /* mov         edx,dword ptr [esp+C]  */ \
_LINE3( 0x0F,0x5C,0xFC )                                    /* subps       xmm7,xmm4 (2 1 0) */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x40,0x20 )                          /* lddqu       xmm0,[eax+20h]  */ \
_LINE3( 0x0F,0x28,0xF7 )                                    /* movaps      xmm6,xmm7  */ \
_LINE4( 0xF2,0x0F,0xF0,0x20 )                               /* lddqu       xmm4,[eax]  */ \
_LINE3( 0x0F,0x28,0xEA )                                    /* movaps      xmm5,xmm2  */ \
_LINE5( 0xF2,0x0F,0xF0,0x58,0x10 )                          /* lddqu       xmm3,[eax+10h]  */ \
_LINE4( 0x0F,0xC6,0xF6,0xAA )                               /* shufps      xmm6,xmm6,AAh  */ \
_LINE4( 0x0F,0xC6,0xED,0x00 )                               /* shufps      xmm5,xmm5,00h  */ \
_LINE3( 0x0F,0x59,0xF4 )                                    /* mulps       xmm6,xmm4  */ \
_LINE3( 0x0F,0x59,0xEB )                                    /* mulps       xmm5,xmm3  */ \
_LINE3( 0x0F,0x58,0xF5 )                                    /* addps       xmm6,xmm5  */ \
_LINE3( 0x0F,0x28,0xE9 )                                    /* movaps      xmm5,xmm1  */ \
_LINE4( 0x0F,0xC6,0xED,0x55 )                               /* shufps      xmm5,xmm5,55h  */ \
_LINE3( 0x0F,0x59,0xE8 )                                    /* mulps       xmm5,xmm0  */ \
_LINE3( 0x0F,0x58,0xF5 )                                    /* addps       xmm6,xmm5  */ \
_LINE3( 0x0F,0x11,0x32 )                                    /* movups      xmmword ptr [edx],xmm6  */ \
_LINE3( 0x0F,0x28,0xEF )                                    /* movaps      xmm5,xmm7  */ \
_LINE3( 0x0F,0x28,0xF1 )                                    /* movaps      xmm6,xmm1  */ \
_LINE4( 0x0F,0xC6,0xED,0x55 )                               /* shufps      xmm5,xmm5,55h  */ \
_LINE4( 0x0F,0xC6,0xF6,0x00 )                               /* shufps      xmm6,xmm6,00h  */ \
_LINE3( 0x0F,0x59,0xEB )                                    /* mulps       xmm5,xmm3  */ \
_LINE3( 0x0F,0x59,0xF4 )                                    /* mulps       xmm6,xmm4  */ \
_LINE4( 0x0F,0xC6,0xC9,0xAA )                               /* shufps      xmm1,xmm1,AAh  */ \
_LINE3( 0x0F,0x58,0xF5 )                                    /* addps       xmm6,xmm5  */ \
_LINE4( 0x0F,0xC6,0xFF,0x00 )                               /* shufps      xmm7,xmm7,00h  */ \
_LINE3( 0x0F,0x28,0xEA )                                    /* movaps      xmm5,xmm2  */ \
_LINE3( 0x0F,0x59,0xF8 )                                    /* mulps       xmm7,xmm0  */ \
_LINE4( 0x0F,0xC6,0xED,0xAA )                               /* shufps      xmm5,xmm5,AAh  */ \
_LINE4( 0x0F,0xC6,0xD2,0x55 )                               /* shufps      xmm2,xmm2,55h  */ \
_LINE3( 0x0F,0x59,0xE8 )                                    /* mulps       xmm5,xmm0  */ \
_LINE3( 0x0F,0x59,0xCB )                                    /* mulps       xmm1,xmm3  */ \
_LINE3( 0x0F,0x58,0xF5 )                                    /* addps       xmm6,xmm5  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE4( 0x0F,0x11,0x72,0x10 )                               /* movups      xmmword ptr [edx+10h],xmm6  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF2,0x0F,0xF0,0x40,0x30 )                          /* lddqu       xmm0,[eax+30h]  */ \
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
_LINE4( 0x0F,0x11,0x52,0x20 )                               /* movups      xmmword ptr [edx+20h],xmm2  */ \
_LINE4( 0x0F,0x11,0x42,0x30 )                               /* movups      xmmword ptr [edx+30h],xmm0  */ \
_END_ASM

/// ѕоворот матрици двойной точности, команды SSE4 ???
/// @brief for CPUTYPE4
#define MATRIXP4DDADDROTATESSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x0C )                               /* mov         edx,dword ptr [esp+C]  */ \
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
_LINE4( 0x66,0x0F,0x59,0xF4 )                               /* mulpd       xmm6,xmm4  */ \
_LINE3( 0x0F,0x16,0xCA )                                    /* movlhps     xmm1,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xFC )                               /* mulpd       xmm7,xmm4  */ \
_LINE3( 0x0F,0x12,0xDE )                                    /* movhlps     xmm3,xmm6  */ \
_LINE3( 0x0F,0x28,0xE0 )                                    /* movaps      xmm4,xmm0  */ \
_LINE5( 0xB8,0x01,0x00,0x00,0x00 )                          /* mov         eax,1  */ \
_LINE3( 0x0F,0x16,0xDF )                                    /* movlhps     xmm3,xmm7  */ \
_LINE4( 0xF2,0x0F,0x59,0xE6 )                               /* mulsd       xmm4,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xD9 )                               /* mulpd       xmm3,xmm1  */ \
_LINE4( 0xF2,0x0F,0x2A,0xE8 )                               /* cvtsi2sd    xmm5,eax  */ \
_LINE3( 0x0F,0x16,0xE4 )                                    /* movlhps     xmm4,xmm4  */ \
_LINE3( 0x0F,0x16,0xED )                                    /* movlhps     xmm5,xmm5  */ \
_LINE4( 0x66,0x0F,0x58,0xE3 )                               /* addpd       xmm4,xmm3  */ \
_LINE3( 0x0F,0x28,0xC5 )                                    /* movaps      xmm0,xmm5  */ \
_LINE4( 0x66,0x0F,0x5C,0xEC )                               /* subpd       xmm5,xmm4  */ \
_LINE3( 0x0F,0x12,0xFF )                                    /* movhlps     xmm7,xmm7  */ \
_LINE3( 0x0F,0x16,0xE6 )                                    /* movlhps     xmm4,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xF9 )                               /* mulpd       xmm7,xmm1  */ \
_LINE3( 0x0F,0x12,0xE6 )                                    /* movhlps     xmm4,xmm6  */ \
_LINE6( 0xF2,0x0F,0x11,0x6C,0x24,0x90 )                     /* movsd       mmword ptr [esp-70h],xmm5  */ \
_LINE4( 0x66,0x0F,0x59,0xE2 )                               /* mulpd       xmm4,xmm2  */ \
_LINE3( 0x0F,0x16,0xF6 )                                    /* movlhps     xmm6,xmm6  */ \
_LINE4( 0x66,0x0F,0x7C,0xDC )                               /* haddpd      xmm3,xmm4  */ \
_LINE5( 0x0F,0x17,0x6C,0x24,0xB8 )                          /* movhps      qword ptr [esp-48h],xmm5  */ \
_LINE4( 0x66,0x0F,0x7D,0xE4 )                               /* hsubpd      xmm4,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xF1 )                               /* mulpd       xmm6,xmm1  */ \
_LINE4( 0xF2,0x0F,0x5C,0xC3 )                               /* subsd       xmm0,xmm3  */ \
_LINE3( 0x0F,0x16,0xD6 )                                    /* movlhps     xmm2,xmm6  */ \
_LINE6( 0xF2,0x0F,0x11,0x44,0x24,0xE0 )                     /* movsd       mmword ptr [esp-20h],xmm0 */ \
_LINE3( 0x0F,0x12,0xD6 )                                    /* movhlps     xmm2,xmm6  */ \
_LINE5( 0x0F,0x17,0x5C,0x24,0x98 )                          /* movhps      qword ptr [esp-68h],xmm3  */ \
_LINE3( 0x0F,0x28,0xF2 )                                    /* movaps      xmm6,xmm2  */ \
_LINE6( 0xF2,0x0F,0x11,0x64,0x24,0xB0 )                     /* movsd       mmword ptr [esp-50h],xmm4 */ \
_LINE4( 0x66,0x0F,0x5C,0xD7 )                               /* subpd       xmm2,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xF7 )                               /* addpd       xmm6,xmm7  */ \
_LINE6( 0xF2,0x0F,0x11,0x54,0x24,0xA0 )                     /* movsd       mmword ptr [esp-60h],xmm2 */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0x0F,0x17,0x54,0x24,0xD8 )                          /* movhps      qword ptr [esp-28h],xmm2  */ \
_LINE5( 0x0F,0x17,0x74,0x24,0xC0 )                          /* movhps      qword ptr [esp-40h],xmm6  */ \
_LINE3( 0x0F,0x16,0xC0 )                                    /* movlhps     xmm0,xmm0  */ \
_LINE3( 0x0F,0x12,0xD2 )                                    /* movhlps     xmm2,xmm2  */ \
_LINE3( 0x0F,0x12,0xDB )                                    /* movhlps     xmm3,xmm3  */ \
_LINE3( 0x0F,0x16,0xE4 )                                    /* movlhps     xmm4,xmm4  */ \
_LINE3( 0x0F,0x16,0xED )                                    /* movlhps     xmm5,xmm5  */ \
_LINE3( 0x0F,0x16,0xF6 )                                    /* movlhps     xmm6,xmm6  */ \
_LINE5( 0xF2,0x0F,0xF0,0x48,0x20 )                          /* lddqu       xmm1,[eax+20h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x78,0x40 )                          /* lddqu       xmm7,[eax+40h]  */ \
_LINE4( 0x66,0x0F,0x59,0xD1 )                               /* mulpd       xmm2,xmm1  */ \
_LINE4( 0x66,0x0F,0x59,0xD9 )                               /* mulpd       xmm3,xmm1  */ \
_LINE4( 0x66,0x0F,0x59,0xEF )                               /* mulpd       xmm5,xmm7  */ \
_LINE4( 0x66,0x0F,0x59,0xE7 )                               /* mulpd       xmm4,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xDD )                               /* addpd       xmm3,xmm5  */ \
_LINE4( 0x66,0x0F,0x59,0xFE )                               /* mulpd       xmm7,xmm6  */ \
_LINE4( 0xF2,0x0F,0xF0,0x28 )                               /* lddqu       xmm5,[eax]  */ \
_LINE4( 0x66,0x0F,0x58,0xFA )                               /* addpd       xmm7,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xC5 )                               /* mulpd       xmm0,xmm5  */ \
_LINE6( 0xF2,0x0F,0x12,0x54,0x24,0xA0 )                     /* movddup     xmm2,mmword ptr [esp-60h]  */ \
_LINE4( 0x66,0x0F,0x58,0xF8 )                               /* addpd       xmm7,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xD5 )                               /* mulpd       xmm2,xmm5  */ \
_LINE4( 0x66,0x0F,0x11,0x3A )                               /* movupd      xmmword ptr [edx],xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xDA )                               /* addpd       xmm3,xmm2  */ \
_LINE6( 0xF2,0x0F,0x12,0x7C,0x24,0xB8 )                     /* movddup     xmm7,mmword ptr [esp-48h] */ \
_LINE5( 0x66,0x0F,0x11,0x5A,0x40 )                          /* movupd      xmmword ptr [edx+40h],xmm3  */ \
_LINE4( 0x66,0x0F,0x59,0xCF )                               /* mulpd       xmm1,xmm7  */ \
_LINE6( 0xF2,0x0F,0x12,0x5C,0x24,0xC0 )                     /* movddup     xmm3,mmword ptr [esp-40h]  */ \
_LINE4( 0x66,0x0F,0x58,0xE1 )                               /* addpd       xmm4,xmm1  */ \
_LINE5( 0xF2,0x0F,0xF0,0x40,0x10 )                          /* lddqu       xmm0,[eax+10h]  */ \
_LINE4( 0x66,0x0F,0x59,0xEB )                               /* mulpd       xmm5,xmm3  */ \
_LINE5( 0xF2,0x0F,0xF0,0x48,0x30 )                          /* lddqu       xmm1,[eax+30h]  */ \
_LINE4( 0x66,0x0F,0x58,0xE5 )                               /* addpd       xmm4,xmm5  */ \
_LINE4( 0x66,0x0F,0x59,0xD8 )                               /* mulpd       xmm3,xmm0  */ \
_LINE5( 0x66,0x0F,0x11,0x62,0x20 )                          /* movupd      xmmword ptr [edx+20h],xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xF9 )                               /* mulpd       xmm7,xmm1  */ \
_LINE5( 0xF2,0x0F,0xF0,0x50,0x50 )                          /* lddqu       xmm2,[eax+50h]  */ \
_LINE6( 0xF2,0x0F,0x12,0x64,0x24,0xB0 )                     /* movddup     xmm4,mmword ptr [esp-50h]  */ \
_LINE4( 0x66,0x0F,0x58,0xFB )                               /* addpd       xmm7,xmm3  */ \
_LINE6( 0xF2,0x0F,0x12,0x6C,0x24,0xE0 )                     /* movddup     xmm5,mmword ptr [esp-20h]  */ \
_LINE4( 0x66,0x0F,0x59,0xE2 )                               /* mulpd       xmm4,xmm2  */ \
_LINE6( 0xF2,0x0F,0x12,0x5C,0x24,0xA0 )                     /* movddup     xmm3,mmword ptr [esp-60h] */ \
_LINE4( 0x66,0x0F,0x59,0xF2 )                               /* mulpd       xmm6,xmm2  */ \
_LINE4( 0x66,0x0F,0x58,0xFC )                               /* addpd       xmm7,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xE8 )                               /* mulpd       xmm5,xmm0  */ \
_LINE5( 0x66,0x0F,0x11,0x7A,0x30 )                          /* movupd      xmmword ptr [edx+30h],xmm7  */ \
_LINE6( 0xF2,0x0F,0x12,0x64,0x24,0xD8 )                     /* movddup     xmm4,mmword ptr [esp-28h]  */ \
_LINE4( 0x66,0x0F,0x59,0xD8 )                               /* mulpd       xmm3,xmm0  */ \
_LINE4( 0x66,0x0F,0x58,0xEE )                               /* addpd       xmm5,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xE1 )                               /* mulpd       xmm4,xmm1  */ \
_LINE6( 0xF2,0x0F,0x12,0x7C,0x24,0x90 )                     /* movddup     xmm7,mmword ptr [esp-70h]  */ \
_LINE6( 0xF2,0x0F,0x12,0x74,0x24,0x98 )                     /* movddup     xmm6,mmword ptr [esp-68h]  */ \
_LINE4( 0x66,0x0F,0x59,0xFA )                               /* mulpd       xmm7,xmm2  */ \
_LINE4( 0x66,0x0F,0x58,0xEC )                               /* addpd       xmm5,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xF1 )                               /* mulpd       xmm6,xmm1  */ \
_LINE4( 0x66,0x0F,0x58,0xDF )                               /* addpd       xmm3,xmm7  */ \
_LINE5( 0x66,0x0F,0x11,0x6A,0x10 )                          /* movupd      xmmword ptr [edx+10h],xmm5  */ \
_LINE5( 0xF2,0x0F,0xF0,0x60,0x60 )                          /* lddqu       xmm4,[eax+60h]  */ \
_LINE4( 0x66,0x0F,0x58,0xDE )                               /* addpd       xmm3,xmm6  */ \
_LINE5( 0xF2,0x0F,0xF0,0x48,0x70 )                          /* lddqu       xmm1,[eax+70h]  */ \
_LINE5( 0x66,0x0F,0x11,0x5A,0x50 )                          /* movupd      xmmword ptr [edx+50h],xmm3  */ \
_LINE5( 0x66,0x0F,0x11,0x62,0x60 )                          /* movupd      xmmword ptr [edx+60h],xmm4  */ \
_LINE5( 0x66,0x0F,0x11,0x4A,0x70 )                          /* movupd      xmmword ptr [edx+70h],xmm1  */ \
_END_ASM

#endif /* X86MATRIX_ADDROTATE_H_ */
