//=============================================================================
///**
// *  @file   matrix_mul.h
// *
// *  $Id: matrix_mul.h 16.10.2011  $
// *
// *  @brief generator 3, assembler matrix double/float mul, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_MATRIX_MUL_H
#define GEN3_MATRIX_MUL_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** MUL STDCALL *********************************
// matrix mul eax=[esp+4]-a void *, [esp+8]-b void *  [esp+12]-c void *

/// ”множение матриц одинарной точности, команды SSE ???
#define MATRIXP4DMULSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                               /* mov         edx,dword ptr [esp+4] */ \
_LINE3( 0x0F,0x12,0x22 )                                    /* movlps      xmm4,qword ptr [edx]  */ \
_LINE4( 0x0F,0x12,0x6A,0x10 )                               /* movlps      xmm5,qword ptr [edx+10h]  */ \
_LINE4( 0x0F,0x16,0x62,0x08 )                               /* movhps      xmm4,qword ptr [edx+8]  */ \
_LINE4( 0x0F,0x16,0x6A,0x18 )                               /* movhps      xmm5,qword ptr [edx+18h]  */ \
_LINE4( 0x0F,0x12,0x72,0x20 )                               /* movlps      xmm6,qword ptr [edx+20h]  */ \
_LINE4( 0x0F,0x12,0x7A,0x30 )                               /* movlps      xmm7,qword ptr [edx+30h]  */ \
_LINE4( 0x0F,0x16,0x72,0x28 )                               /* movhps      xmm6,qword ptr [edx+28h]  */ \
_LINE4( 0x0F,0x16,0x7A,0x38 )                               /* movhps      xmm7,qword ptr [edx+38h]  */ \
_LINE4( 0x8B,0x54,0x24,0x0C )                               /* mov         edx,dword ptr [esp+12] */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8] */ \
_LINE4( 0xF3,0x0F,0x10,0x10 )                               /* movss       xmm2,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x08 )                          /* movss       xmm3,dword ptr [eax+8]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x0C )                          /* movss       xmm0,dword ptr [eax+12]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )                               /* shufps      xmm0,xmm0,0  */ \
_LINE3( 0x0F,0x59,0xC7 )                                    /* mulps       xmm0,xmm7  */ \
_LINE3( 0x0F,0x58,0xD0 )                                    /* addps       xmm2,xmm0  */ \
_LINE3( 0x0F,0x13,0x12 )                                    /* movlps      qword ptr [edx],xmm2  */ \
_LINE4( 0x0F,0x17,0x52,0x08 )                               /* movhps      qword ptr [edx+8],xmm2 */ \
_LINE5( 0xF3,0x0F,0x10,0x50,0x10 )                          /* movss       xmm2,dword ptr [eax+16]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x14 )                          /* movss       xmm1,dword ptr [eax+20]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x18 )                          /* movss       xmm3,dword ptr [eax+24]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x1C )                          /* movss       xmm0,dword ptr [eax+28]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )                               /* shufps      xmm0,xmm0,0  */ \
_LINE3( 0x0F,0x59,0xC7 )                                    /* mulps       xmm0,xmm7  */ \
_LINE3( 0x0F,0x58,0xD0 )                                    /* addps       xmm2,xmm0  */ \
_LINE4( 0x0F,0x13,0x52,0x10 )                               /* movlps      qword ptr [edx+16],xmm2  */ \
_LINE4( 0x0F,0x17,0x52,0x18 )                               /* movhps      qword ptr [edx+24],xmm2 */ \
_LINE5( 0xF3,0x0F,0x10,0x50,0x20 )                          /* movss       xmm2,dword ptr [eax+32]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x24 )                          /* movss       xmm1,dword ptr [eax+36]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x28 )                          /* movss       xmm3,dword ptr [eax+40]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x2C )                          /* movss       xmm0,dword ptr [eax+44]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )                               /* shufps      xmm0,xmm0,0  */ \
_LINE3( 0x0F,0x59,0xC7 )                                    /* mulps       xmm0,xmm7  */ \
_LINE3( 0x0F,0x58,0xD0 )                                    /* addps       xmm2,xmm0  */ \
_LINE4( 0x0F,0x13,0x52,0x20 )                               /* movlps      qword ptr [edx+32],xmm2  */ \
_LINE4( 0x0F,0x17,0x52,0x28 )                               /* movhps      qword ptr [edx+40],xmm2 */ \
_LINE5( 0xF3,0x0F,0x10,0x50,0x30 )                          /* movss       xmm2,dword ptr [eax+48]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x34 )                          /* movss       xmm1,dword ptr [eax+52]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x38 )                          /* movss       xmm3,dword ptr [eax+56]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x3C )                          /* movss       xmm0,dword ptr [eax+60]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )                               /* shufps      xmm0,xmm0,0  */ \
_LINE3( 0x0F,0x59,0xC7 )                                    /* mulps       xmm0,xmm7  */ \
_LINE3( 0x0F,0x58,0xD0 )                                    /* addps       xmm2,xmm0  */ \
_LINE4( 0x0F,0x13,0x52,0x30 )                               /* movlps      qword ptr [edx+48],xmm2  */ \
_LINE4( 0x0F,0x17,0x52,0x38 )                               /* movhps      qword ptr [edx+56],xmm2  */ \
_END_ASM

/// ”множение матриц одинарной точности, команды SSE3 ???
#define MATRIXP4DMULSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                               /* mov         edx,dword ptr [esp+4] */ \
_LINE4( 0xF2,0x0F,0xF0,0x22 )                               /* lddqu       xmm4,[edx]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x6A,0x10 )                          /* lddqu       xmm5,[edx+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x72,0x20 )                          /* lddqu       xmm6,[edx+20h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x7A,0x30 )                          /* lddqu       xmm7,[edx+30h]  */ \
_LINE4( 0x8B,0x54,0x24,0x0C )                               /* mov         edx,dword ptr [esp+12] */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8] */ \
_LINE4( 0xF3,0x0F,0x10,0x10 )                               /* movss       xmm2,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x08 )                          /* movss       xmm3,dword ptr [eax+8]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x0C )                          /* movss       xmm0,dword ptr [eax+12]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )                               /* shufps      xmm0,xmm0,0  */ \
_LINE3( 0x0F,0x59,0xC7 )                                    /* mulps       xmm0,xmm7  */ \
_LINE3( 0x0F,0x58,0xD0 )                                    /* addps       xmm2,xmm0  */ \
_LINE3( 0x0F,0x13,0x12 )                                    /* movlps      qword ptr [edx],xmm2  */ \
_LINE4( 0x0F,0x17,0x52,0x08 )                               /* movhps      qword ptr [edx+8],xmm2 */ \
_LINE5( 0xF3,0x0F,0x10,0x50,0x10 )                          /* movss       xmm2,dword ptr [eax+16]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x14 )                          /* movss       xmm1,dword ptr [eax+20]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x18 )                          /* movss       xmm3,dword ptr [eax+24]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x1C )                          /* movss       xmm0,dword ptr [eax+28]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )                               /* shufps      xmm0,xmm0,0  */ \
_LINE3( 0x0F,0x59,0xC7 )                                    /* mulps       xmm0,xmm7  */ \
_LINE3( 0x0F,0x58,0xD0 )                                    /* addps       xmm2,xmm0  */ \
_LINE4( 0x0F,0x13,0x52,0x10 )                               /* movlps      qword ptr [edx+16],xmm2  */ \
_LINE4( 0x0F,0x17,0x52,0x18 )                               /* movhps      qword ptr [edx+24],xmm2 */ \
_LINE5( 0xF3,0x0F,0x10,0x50,0x20 )                          /* movss       xmm2,dword ptr [eax+32]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x24 )                          /* movss       xmm1,dword ptr [eax+36]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x28 )                          /* movss       xmm3,dword ptr [eax+40]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x2C )                          /* movss       xmm0,dword ptr [eax+44]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )                               /* shufps      xmm0,xmm0,0  */ \
_LINE3( 0x0F,0x59,0xC7 )                                    /* mulps       xmm0,xmm7  */ \
_LINE3( 0x0F,0x58,0xD0 )                                    /* addps       xmm2,xmm0  */ \
_LINE4( 0x0F,0x13,0x52,0x20 )                               /* movlps      qword ptr [edx+32],xmm2  */ \
_LINE4( 0x0F,0x17,0x52,0x28 )                               /* movhps      qword ptr [edx+40],xmm2 */ \
_LINE5( 0xF3,0x0F,0x10,0x50,0x30 )                          /* movss       xmm2,dword ptr [eax+48]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x34 )                          /* movss       xmm1,dword ptr [eax+52]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x38 )                          /* movss       xmm3,dword ptr [eax+56]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x3C )                          /* movss       xmm0,dword ptr [eax+60]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )                               /* shufps      xmm0,xmm0,0  */ \
_LINE3( 0x0F,0x59,0xC7 )                                    /* mulps       xmm0,xmm7  */ \
_LINE3( 0x0F,0x58,0xD0 )                                    /* addps       xmm2,xmm0  */ \
_LINE4( 0x0F,0x13,0x52,0x30 )                               /* movlps      qword ptr [edx+48],xmm2  */ \
_LINE4( 0x0F,0x17,0x52,0x38 )                               /* movhps      qword ptr [edx+56],xmm2  */ \
_END_ASM

/// ”множение матриц одинарной точности, команды SSE4
/// @brief for CPUTYPE4
#define MATRIXP4DMULSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                               /* mov         edx,dword ptr [esp+4] */ \
_LINE4( 0xF2,0x0F,0xF0,0x22 )                               /* lddqu       xmm4,[edx]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x6A,0x10 )                          /* lddqu       xmm5,[edx+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x72,0x20 )                          /* lddqu       xmm6,[edx+20h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x7A,0x30 )                          /* lddqu       xmm7,[edx+30h]  */ \
_LINE4( 0x8B,0x54,0x24,0x0C )                               /* mov         edx,dword ptr [esp+12] */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8] */ \
_LINE4( 0xF3,0x0F,0x10,0x10 )                               /* movss       xmm2,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x08 )                          /* movss       xmm3,dword ptr [eax+8]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x0C )                          /* movss       xmm0,dword ptr [eax+12]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )                               /* shufps      xmm0,xmm0,0  */ \
_LINE3( 0x0F,0x59,0xC7 )                                    /* mulps       xmm0,xmm7  */ \
_LINE3( 0x0F,0x58,0xD0 )                                    /* addps       xmm2,xmm0  */ \
_LINE3( 0x0F,0x11,0x12 )                                    /* movups      xmmword ptr [edx],xmm2  */ \
_LINE5( 0xF3,0x0F,0x10,0x50,0x10 )                          /* movss       xmm2,dword ptr [eax+16]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x14 )                          /* movss       xmm1,dword ptr [eax+20]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x18 )                          /* movss       xmm3,dword ptr [eax+24]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x1C )                          /* movss       xmm0,dword ptr [eax+28]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )                               /* shufps      xmm0,xmm0,0  */ \
_LINE3( 0x0F,0x59,0xC7 )                                    /* mulps       xmm0,xmm7  */ \
_LINE3( 0x0F,0x58,0xD0 )                                    /* addps       xmm2,xmm0  */ \
_LINE4( 0x0F,0x11,0x52,0x10 )                               /* movups      xmmword ptr [edx+10h],xmm2  */ \
_LINE5( 0xF3,0x0F,0x10,0x50,0x20 )                          /* movss       xmm2,dword ptr [eax+32]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x24 )                          /* movss       xmm1,dword ptr [eax+36]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x28 )                          /* movss       xmm3,dword ptr [eax+40]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x2C )                          /* movss       xmm0,dword ptr [eax+44]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )                               /* shufps      xmm0,xmm0,0  */ \
_LINE3( 0x0F,0x59,0xC7 )                                    /* mulps       xmm0,xmm7  */ \
_LINE3( 0x0F,0x58,0xD0 )                                    /* addps       xmm2,xmm0  */ \
_LINE4( 0x0F,0x11,0x52,0x20 )                               /* movups      xmmword ptr [edx+20h],xmm2  */ \
_LINE5( 0xF3,0x0F,0x10,0x50,0x30 )                          /* movss       xmm2,dword ptr [eax+48]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x34 )                          /* movss       xmm1,dword ptr [eax+52]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x38 )                          /* movss       xmm3,dword ptr [eax+56]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x3C )                          /* movss       xmm0,dword ptr [eax+60]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )                               /* shufps      xmm0,xmm0,0  */ \
_LINE3( 0x0F,0x59,0xC7 )                                    /* mulps       xmm0,xmm7  */ \
_LINE3( 0x0F,0x58,0xD0 )                                    /* addps       xmm2,xmm0  */ \
_LINE4( 0x0F,0x11,0x52,0x30 )                               /* movups      xmmword ptr [edx+30h],xmm2  */ \
_END_ASM

/// ”множение матриц одинарной точности, команды AVX
#define MATRIXP4DMULAVX_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                               /* mov         edx,dword ptr [esp+4] */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8] */ \
ASM( mov         ecx,dword ptr [esp+12] ) \
ASM( movaps xmm2, xmmword ptr [eax] ) \
ASM( movaps xmm1, xmm2 ) \
ASM( movaps xmm0, xmm2 ) \
ASM( shufps xmm1, xmm2, 0xff ) \
ASM( mulps xmm1, xmmword ptr [edx+0x30] ) \
ASM( shufps xmm0, xmm2, 0xaa ) \
ASM( vfmadd231ps xmm1, xmm0, xmmword ptr [edx+0x20] ) \
ASM( VFMADD132PS xmm4, xmm3, [48+eax] ) \
ASM( vmovups   XMMWORD PTR [ecx], xmm4 ) \
ASM( vbroadcastss xmm5, DWORD PTR [20+edx] ) \
ASM( vbroadcastss xmm7, DWORD PTR [16+edx] ) \
ASM( vbroadcastss xmm8, DWORD PTR [24+edx] ) \
ASM( vbroadcastss xmm9, DWORD PTR [28+edx] ) \
ASM( vmulps    xmm6, xmm5, XMMWORD PTR [16+eax] ) \
ASM( vfmadd132ps xmm7, xmm6, XMMWORD PTR [eax] ) \
ASM( vfmadd132ps xmm8, xmm7, XMMWORD PTR [32+eax] ) \
ASM( vfmadd132ps xmm9, xmm8, XMMWORD PTR [48+eax] ) \
ASM( vmovups   XMMWORD PTR [16+ecx], xmm9 ) \
ASM( vbroadcastss xmm10, DWORD PTR [36+edx] ) \
ASM( vbroadcastss xmm12, DWORD PTR [32+edx] ) \
ASM( vbroadcastss xmm13, DWORD PTR [40+edx] ) \
ASM( vbroadcastss xmm14, DWORD PTR [44+edx] ) \
ASM( vmulps    xmm11, xmm10, XMMWORD PTR [16+eax] ) \
ASM( vfmadd132ps xmm12, xmm11, XMMWORD PTR [eax] ) \
ASM( vfmadd132ps xmm13, xmm12, XMMWORD PTR [32+eax] ) \
ASM( vfmadd132ps xmm14, xmm13, XMMWORD PTR [48+eax] ) \
ASM( vmovups   XMMWORD PTR [32+ecx], xmm14 ) \
ASM( vbroadcastss xmm15, DWORD PTR [52+edx] ) \
ASM( vbroadcastss xmm0, DWORD PTR [48+edx] ) \
ASM( vbroadcastss xmm1, DWORD PTR [56+edx] ) \
ASM( vbroadcastss xmm2, DWORD PTR [60+edx] ) \
ASM( vmulps    xmm15, xmm15, XMMWORD PTR [16+eax] ) \
ASM( vfmadd132ps xmm0, xmm15, XMMWORD PTR [eax] ) \
ASM( vfmadd132ps xmm1, xmm0, XMMWORD PTR [32+eax] ) \
ASM( vfmadd132ps xmm2, xmm1, XMMWORD PTR [48+eax] ) \
ASM( vmovups   XMMWORD PTR [48+ecx], xmm2 ) \
_END_ASM


/*#define MATRIXP4DMULAVX_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 ) \
_LINE4( 0x8B,0x44,0x24,0x08 ) \
ASM( mov         ecx,dword ptr [esp+12] ) \
ASM( vbroadcastss xmm0, [4+edx] ) \
ASM( vbroadcastss xmm2, [edx] ) \
ASM( vbroadcastss xmm3, [8+edx] ) \
ASM( vbroadcastss xmm4, [12+edx] ) \
ASM( vmulps    xmm1, xmm0, xmmword ptr [16+eax] ) \
ASM( VFMADD132PS xmm2, xmm1, [eax] ) \
ASM( vfmadd132ps xmm3, xmm2, [32+eax] ) \
ASM( VFMADD132PS xmm4, xmm3, [48+eax] ) \
ASM( vmovups   XMMWORD PTR [ecx], xmm4 ) \
ASM( vbroadcastss xmm5, DWORD PTR [20+edx] ) \
ASM( vbroadcastss xmm7, DWORD PTR [16+edx] ) \
ASM( vbroadcastss xmm8, DWORD PTR [24+edx] ) \
ASM( vbroadcastss xmm9, DWORD PTR [28+edx] ) \
ASM( vmulps    xmm6, xmm5, XMMWORD PTR [16+eax] ) \
ASM( vfmadd132ps xmm7, xmm6, XMMWORD PTR [eax] ) \
ASM( vfmadd132ps xmm8, xmm7, XMMWORD PTR [32+eax] ) \
ASM( vfmadd132ps xmm9, xmm8, XMMWORD PTR [48+eax] ) \
ASM( vmovups   XMMWORD PTR [16+ecx], xmm9 ) \
ASM( vbroadcastss xmm10, DWORD PTR [36+edx] ) \
ASM( vbroadcastss xmm12, DWORD PTR [32+edx] ) \
ASM( vbroadcastss xmm13, DWORD PTR [40+edx] ) \
ASM( vbroadcastss xmm14, DWORD PTR [44+edx] ) \
ASM( vmulps    xmm11, xmm10, XMMWORD PTR [16+eax] ) \
ASM( vfmadd132ps xmm12, xmm11, XMMWORD PTR [eax] ) \
ASM( vfmadd132ps xmm13, xmm12, XMMWORD PTR [32+eax] ) \
ASM( vfmadd132ps xmm14, xmm13, XMMWORD PTR [48+eax] ) \
ASM( vmovups   XMMWORD PTR [32+ecx], xmm14 ) \
ASM( vbroadcastss xmm15, DWORD PTR [52+edx] ) \
ASM( vbroadcastss xmm0, DWORD PTR [48+edx] ) \
ASM( vbroadcastss xmm1, DWORD PTR [56+edx] ) \
ASM( vbroadcastss xmm2, DWORD PTR [60+edx] ) \
ASM( vmulps    xmm15, xmm15, XMMWORD PTR [16+eax] ) \
ASM( vfmadd132ps xmm0, xmm15, XMMWORD PTR [eax] ) \
ASM( vfmadd132ps xmm1, xmm0, XMMWORD PTR [32+eax] ) \
ASM( vfmadd132ps xmm2, xmm1, XMMWORD PTR [48+eax] ) \
ASM( vmovups   XMMWORD PTR [48+ecx], xmm2 ) \
_END_ASM*/

/// ”множение матриц двойной точности, команды SSE2
#define MATRIXP4DDMULSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                               /* mov         edx,dword ptr [esp+4] */ \
_LINE3( 0x0F,0x12,0x22 )                                    /* movlps      xmm4,qword ptr [edx]  */ \
_LINE4( 0x0F,0x12,0x6A,0x20 )                               /* movlps      xmm5,qword ptr [edx+20h]  */ \
_LINE4( 0x0F,0x16,0x62,0x08 )                               /* movhps      xmm4,qword ptr [edx+8]  */ \
_LINE4( 0x0F,0x16,0x6A,0x28 )                               /* movhps      xmm5,qword ptr [edx+28h]  */ \
_LINE4( 0x0F,0x12,0x72,0x40 )                               /* movlps      xmm6,qword ptr [edx+40h]  */ \
_LINE4( 0x0F,0x12,0x7A,0x60 )                               /* movlps      xmm7,qword ptr [edx+60h]  */ \
_LINE4( 0x0F,0x16,0x72,0x48 )                               /* movhps      xmm6,qword ptr [edx+48h]  */ \
_LINE4( 0x0F,0x16,0x7A,0x68 )                               /* movhps      xmm7,qword ptr [edx+68h]  */ \
_LINE4( 0x8B,0x54,0x24,0x0C )                               /* mov         edx,dword ptr [esp+12] */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8] */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x08 )                          /* movsd       xmm1,mmword ptr [eax+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x10 )                               /* movsd       xmm2,mmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0x10,0x58,0x10 )                          /* movsd       xmm3,mmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x40,0x18 )                          /* movsd       xmm0,mmword ptr [eax+18h]  */ \
_LINE3( 0x0F,0x16,0xC9 )                                    /* movlhps     xmm1,xmm1  */ \
_LINE3( 0x0F,0x16,0xD2 )                                    /* movlhps     xmm2,xmm2  */ \
_LINE3( 0x0F,0x16,0xDB )                                    /* movlhps     xmm3,xmm3  */ \
_LINE3( 0x0F,0x16,0xC0 )                                    /* movlhps     xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xCD )                               /* mulpd       xmm1,xmm5  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xDE )                               /* mulpd       xmm3,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xC7 )                               /* mulpd       xmm0,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xD1 )                               /* addpd       xmm2,xmm1  */ \
_LINE4( 0x66,0x0F,0x58,0xC3 )                               /* addpd       xmm0,xmm3  */ \
_LINE4( 0x66,0x0F,0x58,0xD0 )                               /* addpd       xmm2,xmm0  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x28 )                          /* movsd       xmm1,mmword ptr [eax+28h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x58,0x30 )                          /* movsd       xmm3,mmword ptr [eax+30h]  */ \
_LINE4( 0xF2,0x0F,0x11,0x12 )                               /* movsd       mmword ptr [edx],xmm2  */ \
_LINE4( 0x0F,0x17,0x52,0x08 )                               /* movhps      qword ptr [edx+8],xmm2  */ \
_LINE5( 0xF2,0x0F,0x10,0x40,0x38 )                          /* movsd       xmm0,mmword ptr [eax+38h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x20 )                          /* movsd       xmm2,mmword ptr [eax+20h]  */ \
_LINE3( 0x0F,0x16,0xDB )                                    /* movlhps     xmm3,xmm3  */ \
_LINE3( 0x0F,0x16,0xC9 )                                    /* movlhps     xmm1,xmm1  */ \
_LINE3( 0x0F,0x16,0xC0 )                                    /* movlhps     xmm0,xmm0  */ \
_LINE3( 0x0F,0x16,0xD2 )                                    /* movlhps     xmm2,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xDE )                               /* mulpd       xmm3,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xCD )                               /* mulpd       xmm1,xmm5  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xC7 )                               /* mulpd       xmm0,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xD1 )                               /* addpd       xmm2,xmm1  */ \
_LINE4( 0x66,0x0F,0x58,0xC3 )                               /* addpd       xmm0,xmm3  */ \
_LINE4( 0x66,0x0F,0x58,0xD0 )                               /* addpd       xmm2,xmm0  */ \
_LINE5( 0xF2,0x0F,0x10,0x58,0x50 )                          /* movsd       xmm3,mmword ptr [eax+50h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x48 )                          /* movsd       xmm1,mmword ptr [eax+48h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x52,0x20 )                          /* movsd       mmword ptr [edx+20h],xmm2  */ \
_LINE4( 0x0F,0x17,0x52,0x28 )                               /* movhps      qword ptr [edx+28h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x10,0x40,0x58 )                          /* movsd       xmm0,mmword ptr [eax+58h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x40 )                          /* movsd       xmm2,mmword ptr [eax+40h]  */ \
_LINE3( 0x0F,0x16,0xC9 )                                    /* movlhps     xmm1,xmm1  */ \
_LINE3( 0x0F,0x16,0xDB )                                    /* movlhps     xmm3,xmm3  */ \
_LINE3( 0x0F,0x16,0xD2 )                                    /* movlhps     xmm2,xmm2  */ \
_LINE3( 0x0F,0x16,0xC0 )                                    /* movlhps     xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xCD )                               /* mulpd       xmm1,xmm5  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xDE )                               /* mulpd       xmm3,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xC7 )                               /* mulpd       xmm0,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xD1 )                               /* addpd       xmm2,xmm1  */ \
_LINE4( 0x66,0x0F,0x58,0xC3 )                               /* addpd       xmm0,xmm3  */ \
_LINE4( 0x66,0x0F,0x58,0xD0 )                               /* addpd       xmm2,xmm0  */ \
_LINE5( 0xF2,0x0F,0x10,0x58,0x70 )                          /* movsd       xmm3,mmword ptr [eax+70h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x68 )                          /* movsd       xmm1,mmword ptr [eax+68h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x52,0x40 )                          /* movsd       mmword ptr [edx+40h],xmm2  */ \
_LINE4( 0x0F,0x17,0x52,0x48 )                               /* movhps      qword ptr [edx+48h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x10,0x40,0x78 )                          /* movsd       xmm0,mmword ptr [eax+78h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x60 )                          /* movsd       xmm2,mmword ptr [eax+60h]  */ \
_LINE3( 0x0F,0x16,0xC9 )                                    /* movlhps     xmm1,xmm1  */ \
_LINE3( 0x0F,0x16,0xDB )                                    /* movlhps     xmm3,xmm3  */ \
_LINE3( 0x0F,0x16,0xD2 )                                    /* movlhps     xmm2,xmm2  */ \
_LINE3( 0x0F,0x16,0xC0 )                                    /* movlhps     xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xCD )                               /* mulpd       xmm1,xmm5  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xDE )                               /* mulpd       xmm3,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xC7 )                               /* mulpd       xmm0,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xD1 )                               /* addpd       xmm2,xmm1  */ \
_LINE4( 0x66,0x0F,0x58,0xC3 )                               /* addpd       xmm0,xmm3  */ \
_LINE4( 0x66,0x0F,0x58,0xD0 )                               /* addpd       xmm2,xmm0  */ \
_LINE4( 0x8B,0x54,0x24,0x04 )                               /* mov         edx,dword ptr [esp+4] */ \
_LINE4( 0x0F,0x12,0x62,0x10 )                               /* movlps      xmm4,qword ptr [edx+10h]  */ \
_LINE4( 0x0F,0x12,0x6A,0x30 )                               /* movlps      xmm5,qword ptr [edx+30h]  */ \
_LINE4( 0x0F,0x16,0x62,0x18 )                               /* movhps      xmm4,qword ptr [edx+18]  */ \
_LINE4( 0x0F,0x16,0x6A,0x38 )                               /* movhps      xmm5,qword ptr [edx+38h]  */ \
_LINE4( 0x0F,0x12,0x72,0x50 )                               /* movlps      xmm6,qword ptr [edx+50h]  */ \
_LINE4( 0x0F,0x12,0x7A,0x70 )                               /* movlps      xmm7,qword ptr [edx+70h]  */ \
_LINE4( 0x0F,0x16,0x72,0x58 )                               /* movhps      xmm6,qword ptr [edx+58h]  */ \
_LINE4( 0x0F,0x16,0x7A,0x78 )                               /* movhps      xmm7,qword ptr [edx+78h]  */ \
_LINE4( 0x8B,0x54,0x24,0x0C )                               /* mov         edx,dword ptr [esp+12] */ \
_LINE5( 0xF2,0x0F,0x10,0x58,0x10 )                          /* movsd       xmm3,mmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x52,0x60 )                          /* movsd       mmword ptr [edx+60h],xmm2  */ \
_LINE4( 0x0F,0x17,0x52,0x68 )                               /* movhps      qword ptr [edx+68h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x10,0x40,0x18 )                          /* movsd       xmm0,mmword ptr [eax+18h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x08 )                          /* movsd       xmm1,mmword ptr [eax+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x10 )                               /* movsd       xmm2,mmword ptr [eax]  */ \
_LINE3( 0x0F,0x16,0xDB )                                    /* movlhps     xmm3,xmm3  */ \
_LINE3( 0x0F,0x16,0xC0 )                                    /* movlhps     xmm0,xmm0  */ \
_LINE3( 0x0F,0x16,0xC9 )                                    /* movlhps     xmm1,xmm1  */ \
_LINE3( 0x0F,0x16,0xD2 )                                    /* movlhps     xmm2,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xDE )                               /* mulpd       xmm3,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xC7 )                               /* mulpd       xmm0,xmm7  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xCD )                               /* mulpd       xmm1,xmm5  */ \
_LINE4( 0x66,0x0F,0x58,0xC3 )                               /* addpd       xmm0,xmm3  */ \
_LINE4( 0x66,0x0F,0x58,0xD1 )                               /* addpd       xmm2,xmm1  */ \
_LINE4( 0x66,0x0F,0x58,0xD0 )                               /* addpd       xmm2,xmm0  */ \
_LINE5( 0xF2,0x0F,0x10,0x58,0x30 )                          /* movsd       xmm3,mmword ptr [eax+30h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x28 )                          /* movsd       xmm1,mmword ptr [eax+28h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x52,0x10 )                          /* movsd       mmword ptr [edx+10h],xmm2  */ \
_LINE4( 0x0F,0x17,0x52,0x18 )                               /* movhps      qword ptr [edx+18h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x10,0x40,0x38 )                          /* movsd       xmm0,mmword ptr [eax+38h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x20 )                          /* movsd       xmm2,mmword ptr [eax+20h]  */ \
_LINE3( 0x0F,0x16,0xDB )                                    /* movlhps     xmm3,xmm3  */ \
_LINE3( 0x0F,0x16,0xC9 )                                    /* movlhps     xmm1,xmm1  */ \
_LINE3( 0x0F,0x16,0xD2 )                                    /* movlhps     xmm2,xmm2  */ \
_LINE3( 0x0F,0x16,0xC0 )                                    /* movlhps     xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xCD )                               /* mulpd       xmm1,xmm5  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xDE )                               /* mulpd       xmm3,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xC7 )                               /* mulpd       xmm0,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xD1 )                               /* addpd       xmm2,xmm1  */ \
_LINE4( 0x66,0x0F,0x58,0xC3 )                               /* addpd       xmm0,xmm3  */ \
_LINE4( 0x66,0x0F,0x58,0xD0 )                               /* addpd       xmm2,xmm0  */ \
_LINE5( 0xF2,0x0F,0x10,0x58,0x50 )                          /* movsd       xmm3,mmword ptr [eax+50h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x48 )                          /* movsd       xmm1,mmword ptr [eax+48h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x52,0x30 )                          /* movsd       mmword ptr [edx+30h],xmm2  */ \
_LINE4( 0x0F,0x17,0x52,0x38 )                               /* movhps      qword ptr [edx+38h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x10,0x40,0x58 )                          /* movsd       xmm0,mmword ptr [eax+58h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x40 )                          /* movsd       xmm2,mmword ptr [eax+40h]  */ \
_LINE3( 0x0F,0x16,0xDB )                                    /* movlhps     xmm3,xmm3  */ \
_LINE3( 0x0F,0x16,0xC9 )                                    /* movlhps     xmm1,xmm1  */ \
_LINE3( 0x0F,0x16,0xD2 )                                    /* movlhps     xmm2,xmm2  */ \
_LINE3( 0x0F,0x16,0xC0 )                                    /* movlhps     xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xCD )                               /* mulpd       xmm1,xmm5  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xDE )                               /* mulpd       xmm3,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xC7 )                               /* mulpd       xmm0,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xD1 )                               /* addpd       xmm2,xmm1  */ \
_LINE4( 0x66,0x0F,0x58,0xC3 )                               /* addpd       xmm0,xmm3  */ \
_LINE4( 0x66,0x0F,0x58,0xD0 )                               /* addpd       xmm2,xmm0  */ \
_LINE5( 0xF2,0x0F,0x10,0x58,0x70 )                          /* movsd       xmm3,mmword ptr [eax+70h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x68 )                          /* movsd       xmm1,mmword ptr [eax+68h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x52,0x50 )                          /* movsd       mmword ptr [edx+50h],xmm2  */ \
_LINE4( 0x0F,0x17,0x52,0x58 )                               /* movhps      qword ptr [edx+58h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x10,0x40,0x78 )                          /* movsd       xmm0,mmword ptr [eax+78h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x60 )                          /* movsd       xmm2,mmword ptr [eax+60h]  */ \
_LINE3( 0x0F,0x16,0xDB )                                    /* movlhps     xmm3,xmm3  */ \
_LINE3( 0x0F,0x16,0xC9 )                                    /* movlhps     xmm1,xmm1  */ \
_LINE3( 0x0F,0x16,0xD2 )                                    /* movlhps     xmm2,xmm2  */ \
_LINE3( 0x0F,0x16,0xC0 )                                    /* movlhps     xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xCD )                               /* mulpd       xmm1,xmm5  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xDE )                               /* mulpd       xmm3,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xC7 )                               /* mulpd       xmm0,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xD1 )                               /* addpd       xmm2,xmm1  */ \
_LINE4( 0x66,0x0F,0x58,0xC3 )                               /* addpd       xmm0,xmm3  */ \
_LINE4( 0x66,0x0F,0x58,0xD0 )                               /* addpd       xmm2,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x52,0x70 )                          /* movsd       mmword ptr [edx+70h],xmm2  */ \
_LINE4( 0x0F,0x17,0x52,0x78 )                               /* movhps      qword ptr [edx+78h],xmm2  */ \
_END_ASM

/// ”множение матриц двойной точности, команды SSE4
/// @brief for CPUTYPE4
#define MATRIXP4DDMULSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                               /* mov         edx,dword ptr [esp+4] */ \
_LINE4( 0xF2,0x0F,0xF0,0x22 )                               /* lddqu       xmm4,[edx]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x6A,0x20 )                          /* lddqu       xmm5,[edx+20h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x72,0x40 )                          /* lddqu       xmm6,[edx+40h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x7A,0x60 )                          /* lddqu       xmm7,[edx+60h]  */ \
_LINE4( 0x8B,0x54,0x24,0x0C )                               /* mov         edx,dword ptr [esp+12] */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8] */ \
_LINE4( 0xF2,0x0F,0x12,0x10 )                               /* movddup     xmm2,mmword ptr [eax]  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE5( 0xF2,0x0F,0x12,0x48,0x08 )                          /* movddup     xmm1,mmword ptr [eax+8]  */ \
_LINE4( 0x66,0x0F,0x59,0xCD )                               /* mulpd       xmm1,xmm5  */ \
_LINE4( 0x66,0x0F,0x58,0xD1 )                               /* addpd       xmm2,xmm1  */ \
_LINE5( 0xF2,0x0F,0x12,0x58,0x10 )                          /* movddup     xmm3,mmword ptr [eax+10h]  */ \
_LINE4( 0x66,0x0F,0x59,0xDE )                               /* mulps       xmm3,xmm6  */ \
_LINE4( 0x66,0x0F,0x58,0xD3 )                               /* addps       xmm2,xmm3  */ \
_LINE5( 0xF2,0x0F,0x12,0x40,0x18 )                          /* movddup     xmm0,mmword ptr [eax+18h]  */ \
_LINE4( 0x66,0x0F,0x59,0xC7 )                               /* mulps       xmm0,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xD0 )                               /* addps       xmm2,xmm0  */ \
_LINE4( 0x66,0x0F,0x11,0x12 )                               /* movupd      xmmword ptr [edx],xmm2  */ \
_LINE5( 0xF2,0x0F,0x12,0x50,0x20 )                          /* movddup     xmm2,mmword ptr [eax+20h]  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE5( 0xF2,0x0F,0x12,0x48,0x28 )                          /* movddup     xmm1,mmword ptr [eax+28h]  */ \
_LINE4( 0x66,0x0F,0x59,0xCD )                               /* mulpd       xmm1,xmm5  */ \
_LINE4( 0x66,0x0F,0x58,0xD1 )                               /* addpd       xmm2,xmm1  */ \
_LINE5( 0xF2,0x0F,0x12,0x58,0x30 )                          /* movddup     xmm3,mmword ptr [eax+30h]  */ \
_LINE4( 0x66,0x0F,0x59,0xDE )                               /* mulps       xmm3,xmm6  */ \
_LINE4( 0x66,0x0F,0x58,0xD3 )                               /* addps       xmm2,xmm3  */ \
_LINE5( 0xF2,0x0F,0x12,0x40,0x38 )                          /* movddup     xmm0,mmword ptr [eax+38h]  */ \
_LINE4( 0x66,0x0F,0x59,0xC7 )                               /* mulps       xmm0,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xD0 )                               /* addps       xmm2,xmm0  */ \
_LINE5( 0x66,0x0F,0x11,0x52,0x20 )                          /* movupd      xmmword ptr [edx+20h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x12,0x50,0x40 )                          /* movddup     xmm2,mmword ptr [eax+40h]  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE5( 0xF2,0x0F,0x12,0x48,0x48 )                          /* movddup     xmm1,mmword ptr [eax+48h]  */ \
_LINE4( 0x66,0x0F,0x59,0xCD )                               /* mulpd       xmm1,xmm5  */ \
_LINE4( 0x66,0x0F,0x58,0xD1 )                               /* addpd       xmm2,xmm1  */ \
_LINE5( 0xF2,0x0F,0x12,0x58,0x50 )                          /* movddup     xmm3,mmword ptr [eax+50h]  */ \
_LINE4( 0x66,0x0F,0x59,0xDE )                               /* mulps       xmm3,xmm6  */ \
_LINE4( 0x66,0x0F,0x58,0xD3 )                               /* addps       xmm2,xmm3  */ \
_LINE5( 0xF2,0x0F,0x12,0x40,0x58 )                          /* movddup     xmm0,mmword ptr [eax+58h]  */ \
_LINE4( 0x66,0x0F,0x59,0xC7 )                               /* mulps       xmm0,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xD0 )                               /* addps       xmm2,xmm0  */ \
_LINE5( 0x66,0x0F,0x11,0x52,0x40 )                          /* movupd      xmmword ptr [edx+40h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x12,0x50,0x60 )                          /* movddup     xmm2,mmword ptr [eax+60h]  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE5( 0xF2,0x0F,0x12,0x48,0x68 )                          /* movddup     xmm1,mmword ptr [eax+68h]  */ \
_LINE4( 0x66,0x0F,0x59,0xCD )                               /* mulpd       xmm1,xmm5  */ \
_LINE4( 0x66,0x0F,0x58,0xD1 )                               /* addpd       xmm2,xmm1  */ \
_LINE5( 0xF2,0x0F,0x12,0x58,0x70 )                          /* movddup     xmm3,mmword ptr [eax+70h]  */ \
_LINE4( 0x66,0x0F,0x59,0xDE )                               /* mulps       xmm3,xmm6  */ \
_LINE4( 0x66,0x0F,0x58,0xD3 )                               /* addps       xmm2,xmm3  */ \
_LINE5( 0xF2,0x0F,0x12,0x40,0x78 )                          /* movddup     xmm0,mmword ptr [eax+78h]  */ \
_LINE4( 0x66,0x0F,0x59,0xC7 )                               /* mulps       xmm0,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xD0 )                               /* addps       xmm2,xmm0  */ \
_LINE5( 0x66,0x0F,0x11,0x52,0x60 )                          /* movupd      xmmword ptr [edx+60h],xmm2  */ \
_LINE4( 0x8B,0x54,0x24,0x04 )                               /* mov         edx,dword ptr [esp+4] */ \
_LINE5( 0xF2,0x0F,0xF0,0x62,0x10 )                          /* lddqu       xmm4,[edx+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x6A,0x30 )                          /* lddqu       xmm5,[edx+30h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x72,0x50 )                          /* lddqu       xmm6,[edx+50h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x7A,0x70 )                          /* lddqu       xmm7,[edx+70h]  */ \
_LINE4( 0x8B,0x54,0x24,0x0C )                               /* mov         edx,dword ptr [esp+12] */ \
_LINE4( 0xF2,0x0F,0x12,0x10 )                               /* movddup     xmm2,mmword ptr [eax]  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE5( 0xF2,0x0F,0x12,0x48,0x08 )                          /* movddup     xmm1,mmword ptr [eax+8]  */ \
_LINE4( 0x66,0x0F,0x59,0xCD )                               /* mulpd       xmm1,xmm5  */ \
_LINE4( 0x66,0x0F,0x58,0xD1 )                               /* addpd       xmm2,xmm1  */ \
_LINE5( 0xF2,0x0F,0x12,0x58,0x10 )                          /* movddup     xmm3,mmword ptr [eax+10h]  */ \
_LINE4( 0x66,0x0F,0x59,0xDE )                               /* mulps       xmm3,xmm6  */ \
_LINE4( 0x66,0x0F,0x58,0xD3 )                               /* addps       xmm2,xmm3  */ \
_LINE5( 0xF2,0x0F,0x12,0x40,0x18 )                          /* movddup     xmm0,mmword ptr [eax+18h]  */ \
_LINE4( 0x66,0x0F,0x59,0xC7 )                               /* mulps       xmm0,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xD0 )                               /* addps       xmm2,xmm0  */ \
_LINE5( 0x66,0x0F,0x11,0x52,0x10 )                          /* movupd      xmmword ptr [edx+10h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x12,0x50,0x20 )                          /* movddup     xmm2,mmword ptr [eax+20h]  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE5( 0xF2,0x0F,0x12,0x48,0x28 )                          /* movddup     xmm1,mmword ptr [eax+28h]  */ \
_LINE4( 0x66,0x0F,0x59,0xCD )                               /* mulpd       xmm1,xmm5  */ \
_LINE4( 0x66,0x0F,0x58,0xD1 )                               /* addpd       xmm2,xmm1  */ \
_LINE5( 0xF2,0x0F,0x12,0x58,0x30 )                          /* movddup     xmm3,mmword ptr [eax+30h]  */ \
_LINE4( 0x66,0x0F,0x59,0xDE )                               /* mulps       xmm3,xmm6  */ \
_LINE4( 0x66,0x0F,0x58,0xD3 )                               /* addps       xmm2,xmm3  */ \
_LINE5( 0xF2,0x0F,0x12,0x40,0x38 )                          /* movddup     xmm0,mmword ptr [eax+38h]  */ \
_LINE4( 0x66,0x0F,0x59,0xC7 )                               /* mulps       xmm0,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xD0 )                               /* addps       xmm2,xmm0  */ \
_LINE5( 0x66,0x0F,0x11,0x52,0x30 )                          /* movupd      xmmword ptr [edx+30h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x12,0x50,0x40 )                          /* movddup     xmm2,mmword ptr [eax+40h]  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE5( 0xF2,0x0F,0x12,0x48,0x48 )                          /* movddup     xmm1,mmword ptr [eax+48h]  */ \
_LINE4( 0x66,0x0F,0x59,0xCD )                               /* mulpd       xmm1,xmm5  */ \
_LINE4( 0x66,0x0F,0x58,0xD1 )                               /* addpd       xmm2,xmm1  */ \
_LINE5( 0xF2,0x0F,0x12,0x58,0x50 )                          /* movddup     xmm3,mmword ptr [eax+50h]  */ \
_LINE4( 0x66,0x0F,0x59,0xDE )                               /* mulps       xmm3,xmm6  */ \
_LINE4( 0x66,0x0F,0x58,0xD3 )                               /* addps       xmm2,xmm3  */ \
_LINE5( 0xF2,0x0F,0x12,0x40,0x58 )                          /* movddup     xmm0,mmword ptr [eax+58h]  */ \
_LINE4( 0x66,0x0F,0x59,0xC7 )                               /* mulps       xmm0,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xD0 )                               /* addps       xmm2,xmm0  */ \
_LINE5( 0x66,0x0F,0x11,0x52,0x50 )                          /* movupd      xmmword ptr [edx+50h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x12,0x50,0x60 )                          /* movddup     xmm2,mmword ptr [eax+60h]  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE5( 0xF2,0x0F,0x12,0x48,0x68 )                          /* movddup     xmm1,mmword ptr [eax+68h]  */ \
_LINE4( 0x66,0x0F,0x59,0xCD )                               /* mulpd       xmm1,xmm5  */ \
_LINE4( 0x66,0x0F,0x58,0xD1 )                               /* addpd       xmm2,xmm1  */ \
_LINE5( 0xF2,0x0F,0x12,0x58,0x70 )                          /* movddup     xmm3,mmword ptr [eax+70h]  */ \
_LINE4( 0x66,0x0F,0x59,0xDE )                               /* mulps       xmm3,xmm6  */ \
_LINE4( 0x66,0x0F,0x58,0xD3 )                               /* addps       xmm2,xmm3  */ \
_LINE5( 0xF2,0x0F,0x12,0x40,0x78 )                          /* movddup     xmm0,mmword ptr [eax+78h]  */ \
_LINE4( 0x66,0x0F,0x59,0xC7 )                               /* mulps       xmm0,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xD0 )                               /* addps       xmm2,xmm0  */ \
_LINE5( 0x66,0x0F,0x11,0x52,0x70 )                          /* movupd      xmmword ptr [edx+70h],xmm2  */ \
_END_ASM

/// ”множение матриц двойной точности, команды AVX
#define MATRIXP4DDMULAVX_STD \
_BEGIN_ASM \
_LINE4 ( 0x8B,0x54,0x24,0x04 )                              /* mov         edx,dword ptr [esp+4]  */ \
_LINE4 ( 0xC5,0xFD,0x10,0x22 )                              /* vmovupd     ymm4,ymmword ptr [edx]  */ \
_LINE5 ( 0xC5,0xFD,0x10,0x6A,0x20 )                         /* vmovupd     ymm5,ymmword ptr [edx+20]  */ \
_LINE5 ( 0xC5,0xFD,0x10,0x72,0x40 )                         /* vmovupd     ymm6,ymmword ptr [edx+40]  */ \
_LINE5 ( 0xC5,0xFD,0x10,0x7A,0x60 )                         /* vmovupd     ymm7,ymmword ptr [edx+60]  */ \
_LINE4 ( 0x8B,0x54,0x24,0x0C )                              /* mov         edx,dword ptr [esp+12] */ \
_LINE4 ( 0x8B,0x44,0x24,0x08 )                              /* mov         eax,dword ptr [esp+8] */ \
_LINE6 ( 0xC4,0xE2,0x7D,0x19,0x58,0x18 )                    /* vbroadcastsd ymm3,qword ptr [eax+18h]  */ \
_LINE6 ( 0xC4,0xE2,0x7D,0x19,0x50,0x10 )                    /* vbroadcastsd ymm2,qword ptr [eax+10h]  */ \
_LINE6 ( 0xC4,0xE2,0x7D,0x19,0x48,0x08 )                    /* vbroadcastsd ymm1,qword ptr [eax+8h]  */ \
_LINE5 ( 0xC4,0xE2,0x7D,0x19,0x00 )                         /* vbroadcastsd ymm0,qword ptr [eax]  */ \
_LINE4 ( 0xC5,0xC5,0x59,0xDB )                              /* vmulpd      ymm3,ymm7,ymm3  */ \
_LINE4 ( 0xC5,0xCD,0x59,0xD2 )                              /* vmulpd      ymm2,ymm6,ymm2  */ \
_LINE4 ( 0xC5,0xD5,0x59,0xC9 )                              /* vmulpd      ymm1,ymm5,ymm1  */ \
_LINE4 ( 0xC5,0xDD,0x59,0xC0 )                              /* vmulpd      ymm0,ymm4,ymm0  */ \
_LINE4 ( 0xC5,0xE5,0x58,0xD2 )                              /* vaddpd      ymm2,ymm3,ymm2  */ \
_LINE4 ( 0xC5,0xFD,0x58,0xC9 )                              /* vaddpd      ymm1,ymm0,ymm1  */ \
_LINE4 ( 0xC5,0xED,0x58,0xC1 )                              /* vaddpd      ymm0,ymm2,ymm1  */ \
_LINE6 ( 0xC4,0xE2,0x7D,0x19,0x58,0x38 )                    /* vbroadcastsd ymm3,qword ptr [eax+38h]  */ \
_LINE4 ( 0xC5,0xFD,0x11,0x02 )                              /* vmovupd     ymmword ptr [edx],ymm0  */ \
_LINE6 ( 0xC4,0xE2,0x7D,0x19,0x50,0x30 )                    /* vbroadcastsd ymm2,qword ptr [eax+30h]  */ \
_LINE6 ( 0xC4,0xE2,0x7D,0x19,0x48,0x28 )                    /* vbroadcastsd ymm1,qword ptr [eax+28h]  */ \
_LINE6 ( 0xC4,0xE2,0x7D,0x19,0x40,0x20 )                    /* vbroadcastsd ymm0,qword ptr [eax+20h]  */ \
_LINE4 ( 0xC5,0xC5,0x59,0xDB )                              /* vmulpd      ymm3,ymm7,ymm3  */ \
_LINE4 ( 0xC5,0xCD,0x59,0xD2 )                              /* vmulpd      ymm2,ymm6,ymm2  */ \
_LINE4 ( 0xC5,0xD5,0x59,0xC9 )                              /* vmulpd      ymm1,ymm5,ymm1  */ \
_LINE4 ( 0xC5,0xDD,0x59,0xC0 )                              /* vmulpd      ymm0,ymm4,ymm0  */ \
_LINE4 ( 0xC5,0xE5,0x58,0xD2 )                              /* vaddpd      ymm2,ymm3,ymm2  */ \
_LINE4 ( 0xC5,0xFD,0x58,0xC9 )                              /* vaddpd      ymm1,ymm0,ymm1  */ \
_LINE4 ( 0xC5,0xED,0x58,0xC1 )                              /* vaddpd      ymm0,ymm2,ymm1  */ \
_LINE6 ( 0xC4,0xE2,0x7D,0x19,0x58,0x58 )                    /* vbroadcastsd ymm3,qword ptr [eax+58h]  */ \
_LINE5 ( 0xC5,0xFD,0x11,0x42,0x20 )                         /* vmovupd     ymmword ptr [edx+20],ymm0  */ \
_LINE6 ( 0xC4,0xE2,0x7D,0x19,0x50,0x50 )                    /* vbroadcastsd ymm2,qword ptr [eax+50h]  */ \
_LINE6 ( 0xC4,0xE2,0x7D,0x19,0x48,0x48 )                    /* vbroadcastsd ymm1,qword ptr [eax+48h]  */ \
_LINE6 ( 0xC4,0xE2,0x7D,0x19,0x40,0x40 )                    /* vbroadcastsd ymm0,qword ptr [eax+40h]  */ \
_LINE4 ( 0xC5,0xC5,0x59,0xDB )                              /* vmulpd      ymm3,ymm7,ymm3  */ \
_LINE4 ( 0xC5,0xCD,0x59,0xD2 )                              /* vmulpd      ymm2,ymm6,ymm2  */ \
_LINE4 ( 0xC5,0xD5,0x59,0xC9 )                              /* vmulpd      ymm1,ymm5,ymm1  */ \
_LINE4 ( 0xC5,0xDD,0x59,0xC0 )                              /* vmulpd      ymm0,ymm4,ymm0  */ \
_LINE4 ( 0xC5,0xE5,0x58,0xD2 )                              /* vaddpd      ymm2,ymm3,ymm2  */ \
_LINE4 ( 0xC5,0xFD,0x58,0xC9 )                              /* vaddpd      ymm1,ymm0,ymm1  */ \
_LINE4 ( 0xC5,0xED,0x58,0xC1 )                              /* vaddpd      ymm0,ymm2,ymm1  */ \
_LINE6 ( 0xC4,0xE2,0x7D,0x19,0x58,0x78 )                    /* vbroadcastsd ymm3,qword ptr [eax+78h]  */ \
_LINE5 ( 0xC5,0xFD,0x11,0x42,0x40 )                         /* vmovupd     ymmword ptr [edx+40],ymm0  */ \
_LINE6 ( 0xC4,0xE2,0x7D,0x19,0x50,0x70 )                    /* vbroadcastsd ymm2,qword ptr [eax+70h]  */ \
_LINE6 ( 0xC4,0xE2,0x7D,0x19,0x48,0x68 )                    /* vbroadcastsd ymm1,qword ptr [eax+68h]  */ \
_LINE6 ( 0xC4,0xE2,0x7D,0x19,0x40,0x60 )                    /* vbroadcastsd ymm0,qword ptr [eax+60h]  */ \
_LINE4 ( 0xC5,0xC5,0x59,0xDB )                              /* vmulpd      ymm3,ymm7,ymm3  */ \
_LINE4 ( 0xC5,0xCD,0x59,0xD2 )                              /* vmulpd      ymm2,ymm6,ymm2  */ \
_LINE4 ( 0xC5,0xD5,0x59,0xC9 )                              /* vmulpd      ymm1,ymm5,ymm1  */ \
_LINE4 ( 0xC5,0xDD,0x59,0xC0 )                              /* vmulpd      ymm0,ymm4,ymm0  */ \
_LINE4 ( 0xC5,0xE5,0x58,0xD2 )                              /* vaddpd      ymm2,ymm3,ymm2  */ \
_LINE4 ( 0xC5,0xFD,0x58,0xC9 )                              /* vaddpd      ymm1,ymm0,ymm1  */ \
_LINE4 ( 0xC5,0xED,0x58,0xC1 )                              /* vaddpd      ymm0,ymm2,ymm1  */ \
_LINE5 ( 0xC5,0xFD,0x11,0x42,0x60 )                         /* vmovupd     ymmword ptr [edx+60],ymm0  */ \
ASM( vzeroupper ) \
_END_ASM

#endif


