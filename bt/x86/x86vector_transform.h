//=============================================================================
///**
// *  @file vector_transform.h
// *
// *  $Id: vector_transform.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float transform, MS Visual C++ 2003-2008
// *
// *  @author Pant_eleymonov Alek_sandr Kons_tantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_VECTOR_TRANSFORM_H
#define GEN3_VECTOR_TRANSFORM_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** TRANSFORM STDCALL *********************************
// transform vectors eax=[esp+4]-a void *, [esp+8]-b void *  [esp+12]-c void *

/// Умножение двухмерного вектора на матрицу трансформации одинарной точности, команды FPU
#define VECTORP2DTRANSFORMFPU_STD \
_BEGIN_ASM \
 _STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x04))               /* mov         eax,dword ptr [esp+04h] */ \
 _STR(_DB(0x8B) _DB(0x54) _DB(0x24) _DB(0x0C))               /* mov         edx,dword ptr [esp+0Ch] */ \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x04))                         /* fld         dword ptr [eax+04h] */ \
 _STR(_DB(0xD9) _DB(0x00))                                   /* fld         dword ptr [eax] */ \
 _STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x08))               /* mov         eax,dword ptr [esp+8] */ \
 _STR(_DB(0xD9) _DB(0x00))                                   /* fld         dword ptr [eax] */ \
 _STR(_DB(0xD8) _DB(0xC9))                                   /* fmul        st, st(1) */ \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x10))                         /* fld         dword ptr [eax+10h] */ \
 _STR(_DB(0xD8) _DB(0xCB))                                   /* fmul        st, st(3) */ \
 _STR(_DB(0xDE) _DB(0xC1))                                   /* faddp       st(1), st */ \
 _STR(_DB(0xD8) _DB(0x40) _DB(0x30))                         /* fadd        dword ptr [eax+30h] */ \
 _STR(_DB(0xD9) _DB(0x1A))                                   /* fstp        dword ptr [edx] */ \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x04))                         /* fld         dword ptr [eax+4] */ \
 _STR(_DB(0xDE) _DB(0xC9))                                   /* fmulp       st(1), st */ \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x14))                         /* fld         dword ptr [eax+14h] */ \
 _STR(_DB(0xDE) _DB(0xCA))                                   /* fmulp       st(2), st */ \
 _STR(_DB(0xDE) _DB(0xC1))                                   /* faddp       st(1), st */ \
 _STR(_DB(0xD8) _DB(0x40) _DB(0x34))                         /* fadd        dword ptr [eax+34h] */ \
 _STR(_DB(0xD9) _DB(0x5A) _DB(0x04))                         /* fstp        dword ptr [edx+4] */ \
_END_ASM

/// Умножение двухмерного вектора на матрицу трансформации одинарной точности, команды SSE
#define VECTORP2DTRANSFORMSSE_STD \
_BEGIN_ASM \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x08))               /* mov         eax,dword ptr [esp+8] */ \
ASM( xorps xmm4,xmm4 ) \
ASM( xorps xmm5,xmm5 ) \
ASM( xorps xmm7,xmm7 ) \
_LINE3( 0x0F,0x12,0x20 )                                    /* movlps      xmm4,qword ptr [eax]  */ \
_LINE4( 0x0F,0x12,0x68,0x10 )                               /* movlps      xmm5,qword ptr [eax+10h]  */ \
_LINE4( 0x0F,0x12,0x78,0x30 )                               /* movlps      xmm7,qword ptr [eax+30h]  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+04h] */ \
_LINE4( 0xF3,0x0F,0x10,0x10 )                               /* movss       xmm2,dword ptr [eax]  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x50 )                               /* shufps      xmm2,xmm2,0x50  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE4( 0x0F,0xC6,0xC9,0x50 )                               /* shufps      xmm1,xmm1,0x50  */ \
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+0Ch] */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x13,0x10 )                                    /* movlps      qword ptr [eax],xmm2  */ \
_END_ASM

/// Умножение двухмерного вектора на матрицу трансформации одинарной точности, команды SSE2
#define VECTORP2DTRANSFORMSSE2_STD \
_BEGIN_ASM \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x08))               /* mov         eax,dword ptr [esp+8] */ \
ASM( movsd xmm4,qword ptr [eax] ) \
ASM( movsd xmm5,qword ptr [eax+0x10] ) \
ASM( movsd xmm7,qword ptr [eax+0x30] ) \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+04h] */ \
_LINE4( 0xF3,0x0F,0x10,0x10 )                               /* movss       xmm2,dword ptr [eax]  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x50 )                               /* shufps      xmm2,xmm2,0x50  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE4( 0x0F,0xC6,0xC9,0x50 )                               /* shufps      xmm1,xmm1,0x50  */ \
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+0Ch] */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x13,0x10 )                                    /* movlps      qword ptr [eax],xmm2  */ \
_END_ASM

/// Умножение трехмерного вектора на матрицу трансформации одинарной точности, команды FPU
#define VECTORP3DTRANSFORMFPU_STD \
_BEGIN_ASM \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x04))               /* mov         eax,dword ptr [esp+04h] */ \
_STR(_DB(0x8B) _DB(0x54) _DB(0x24) _DB(0x0C))               /* mov         edx,dword ptr [esp+0Ch] */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x08))               /* mov         eax,dword ptr [esp+8] */ \
_STR(_DB(0xD9) _DB(0x00)) \
_STR(_DB(0xD8) _DB(0xC9)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x10)) \
_STR(_DB(0xD8) _DB(0xCB)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x20)) \
_STR(_DB(0xD8) _DB(0xCC)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xD8) _DB(0x40) _DB(0x30)) \
_STR(_DB(0xD9) _DB(0x1A)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
_STR(_DB(0xD8) _DB(0xC9)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x14)) \
_STR(_DB(0xD8) _DB(0xCB)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x24)) \
_STR(_DB(0xD8) _DB(0xCC)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xD8) _DB(0x40) _DB(0x34)) \
_LINE3( 0xD9,0x5A,0x04 )                                    /* fstp        dword ptr [edx+4] */ \
_STR(_DB(0xD9) _DB(0x40) _DB(0x08)) \
_STR(_DB(0xDE) _DB(0xC9)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x18)) \
_STR(_DB(0xDE) _DB(0xCA)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x28)) \
_STR(_DB(0xDE) _DB(0xCB)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xD8) _DB(0x40) _DB(0x38)) \
_LINE3( 0xD9,0x5A,0x08 )                                    /* fstp        dword ptr [edx+8] */ \
_END_ASM

/// Умножение трехмерного вектора на матрицу трансформации одинарной точности, команды SSE
#define VECTORP3DTRANSFORMSSE_STD \
_BEGIN_ASM \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x08))               /* mov         eax,dword ptr [esp+8] */ \
_LINE3( 0x0F,0x12,0x20 )                                    /* movlps      xmm4,qword ptr [eax]  */ \
_LINE4( 0x0F,0x16,0x60,0x08 )                               /* movhps      xmm4,qword ptr [eax+8]  */ \
_LINE4( 0x0F,0x12,0x68,0x10 )                               /* movlps      xmm5,qword ptr [eax+10h]  */ \
_LINE4( 0x0F,0x16,0x68,0x18 )                               /* movhps      xmm5,qword ptr [eax+18h]  */ \
_LINE4( 0x0F,0x12,0x70,0x20 )                               /* movlps      xmm6,qword ptr [eax+20h]  */ \
_LINE4( 0x0F,0x16,0x70,0x28 )                               /* movhps      xmm6,qword ptr [eax+28h]  */ \
_LINE4( 0x0F,0x12,0x78,0x30 )                               /* movlps      xmm7,qword ptr [eax+30h]  */ \
_LINE4( 0x0F,0x16,0x78,0x38 )                               /* movhps      xmm7,qword ptr [eax+38h]  */ \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x04))               /* mov         eax,dword ptr [esp+04h] */ \
_LINE4( 0xF3,0x0F,0x10,0x10 )                               /* movss       xmm2,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x40 )                               /* shufps      xmm2,xmm2,0x40  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x40 )                               /* shufps      xmm1,xmm1,0x40  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x08 )                          /* movss       xmm3,dword ptr [eax+8]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x40 )                               /* shufps      xmm3,xmm3,0x40  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x0C))               /* mov         eax,dword ptr [esp+0Ch] */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
_LINE3( 0x0F,0x13,0x10 )                                    /* movlps      qword ptr [eax],xmm2  */ \
_LINE3( 0x0F,0x15,0xD2 )                                    /* unpckhps    xmm2,xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x50,0x08 )                          /* movss       dword ptr [eax+8],xmm2 */ \
_END_ASM

/// Умножение трехмерного вектора на матрицу трансформации одинарной точности, команды SSE3
#define VECTORP3DTRANSFORMSSE3_STD \
_BEGIN_ASM \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x08))               /* mov         eax,dword ptr [esp+8] */ \
_LINE4( 0xF2,0x0F,0xF0,0x20 )                               /* lddqu       xmm4,[eax]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x68,0x10 )                          /* lddqu       xmm5,[eax+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x70,0x20 )                          /* lddqu       xmm6,[eax+20h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x78,0x30 )                          /* lddqu       xmm7,[eax+30h]  */ \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x04))               /* mov         eax,dword ptr [esp+04h] */ \
_LINE4( 0xF3,0x0F,0x10,0x10 )                               /* movss       xmm2,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x40 )                               /* shufps      xmm2,xmm2,0x40  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x40 )                               /* shufps      xmm1,xmm1,0x40  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x08 )                          /* movss       xmm3,dword ptr [eax+8]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x40 )                               /* shufps      xmm3,xmm3,0x40  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x0C))               /* mov         eax,dword ptr [esp+0Ch] */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
_LINE3( 0x0F,0x13,0x10 )                                    /* movlps      qword ptr [eax],xmm2  */ \
_LINE3( 0x0F,0x15,0xD2 )                                    /* unpckhps    xmm2,xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x50,0x08 )                          /* movss       dword ptr [eax+8],xmm2  */ \
_END_ASM

/// Умножение четырехмерного вектора на матрицу трансформации одинарной точности, команды FPU
#define VECTORP4DTRANSFORMFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+04h] */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+08h] */ \
_LINE3( 0xD9,0x40,0x0C )                                    /* fld         dword ptr [eax+0Ch]  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+0Ch] */ \
_LINE3( 0xD9,0x42,0x0C )                                    /* fld         dword ptr [edx+0Ch]  */ \
_LINE2( 0xD8,0xC9 )                                         /* fmul        st,st(1)  */ \
_LINE3( 0xD9,0x42,0x1C )                                    /* fld         dword ptr [edx+1Ch]  */ \
_LINE2( 0xD8,0xCB )                                         /* fmul        st,st(3)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x42,0x2C )                                    /* fld         dword ptr [edx+2Ch]  */ \
_LINE2( 0xD8,0xCC )                                         /* fmul        st,st(4)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x42,0x3C )                                    /* fld         dword ptr [edx+3Ch]  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x58,0x0C )                                    /* fstp        dword ptr [eax+0Ch]  */ \
_LINE2( 0xD9,0x02 )                                         /* fld         dword ptr [edx]  */ \
_LINE2( 0xD8,0xC9 )                                         /* fmul        st,st(1)  */ \
_LINE3( 0xD9,0x42,0x10 )                                    /* fld         dword ptr [edx+10h]  */ \
_LINE2( 0xD8,0xCB )                                         /* fmul        st,st(3)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x42,0x20 )                                    /* fld         dword ptr [edx+20h]  */ \
_LINE2( 0xD8,0xCC )                                         /* fmul        st,st(4)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x42,0x30 )                                    /* fld         dword ptr [edx+30h]  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xD9,0x18 )                                         /* fstp        dword ptr [eax]  */ \
_LINE3( 0xD9,0x42,0x04 )                                    /* fld         dword ptr [edx+4]  */ \
_LINE2( 0xD8,0xC9 )                                         /* fmul        st,st(1)  */ \
_LINE3( 0xD9,0x42,0x14 )                                    /* fld         dword ptr [edx+14h]  */ \
_LINE2( 0xD8,0xCB )                                         /* fmul        st,st(3)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x42,0x24 )                                    /* fld         dword ptr [edx+24h]  */ \
_LINE2( 0xD8,0xCC )                                         /* fmul        st,st(4)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x42,0x34 )                                    /* fld         dword ptr [edx+34h]  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x58,0x04 )                                    /* fstp        dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x42,0x08 )                                    /* fld         dword ptr [edx+8]  */ \
_LINE2( 0xDE,0xC9 )                                         /* fmulp       st(1),st  */ \
_LINE3( 0xD9,0x42,0x18 )                                    /* fld         dword ptr [edx+18h]  */ \
_LINE2( 0xDE,0xCA )                                         /* fmulp       st(2),st  */ \
_LINE3( 0xD9,0x42,0x28 )                                    /* fld         dword ptr [edx+28h]  */ \
_LINE2( 0xDE,0xCB )                                         /* fmulp       st(3),st  */ \
_LINE3( 0xD9,0x42,0x38 )                                    /* fld         dword ptr [edx+38h]  */ \
_LINE2( 0xDE,0xCC )                                         /* fmulp       st(4),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x58,0x08 )                                    /* fstp        dword ptr [eax+8] */ \
_END_ASM

/// Умножение четырехмерного вектора на матрицу трансформации одинарной точности, команды SSE
#define VECTORP4DTRANSFORMSSE_STD \
_BEGIN_ASM \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x08))               /* mov         eax,dword ptr [esp+8] */ \
_LINE3( 0x0F,0x12,0x20 )                                    /* movlps      xmm4,qword ptr [eax]  */ \
_LINE4( 0x0F,0x16,0x60,0x08 )                               /* movhps      xmm4,qword ptr [eax+8]  */ \
_LINE4( 0x0F,0x12,0x68,0x10 )                               /* movlps      xmm5,qword ptr [eax+10h]  */ \
_LINE4( 0x0F,0x16,0x68,0x18 )                               /* movhps      xmm5,qword ptr [eax+18h]  */ \
_LINE4( 0x0F,0x12,0x70,0x20 )                               /* movlps      xmm6,qword ptr [eax+20h]  */ \
_LINE4( 0x0F,0x16,0x70,0x28 )                               /* movhps      xmm6,qword ptr [eax+28h]  */ \
_LINE4( 0x0F,0x12,0x78,0x30 )                               /* movlps      xmm7,qword ptr [eax+30h]  */ \
_LINE4( 0x0F,0x16,0x78,0x38 )                               /* movhps      xmm7,qword ptr [eax+38h]  */ \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x04))               /* mov         eax,dword ptr [esp+04h] */ \
_LINE4( 0xF3,0x0F,0x10,0x10 )                               /* movss       xmm2,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x08 )                          /* movss       xmm3,dword ptr [eax+8]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x0C )                          /* movss       xmm0,dword ptr [eax+12]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )                               /* shufps      xmm0,xmm0,0  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x59,0xC7 )                                    /* mulps       xmm0,xmm7  */ \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x0C))               /* mov         eax,dword ptr [esp+0Ch] */ \
_LINE3( 0x0F,0x58,0xD0 )                                    /* addps       xmm2,xmm0  */ \
_LINE3( 0x0F,0x13,0x10 )                                    /* movlps      qword ptr [eax],xmm2  */ \
_LINE4( 0x0F,0x17,0x50,0x08 )                               /* movhps      qword ptr [eax+8],xmm2 */ \
_END_ASM

/// Умножение четырехмерного вектора на матрицу трансформации одинарной точности, команды SSE3
#define VECTORP4DTRANSFORMSSE3_STD \
_BEGIN_ASM \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x08))               /* mov         eax,dword ptr [esp+8] */ \
_LINE4( 0xF2,0x0F,0xF0,0x20 )                               /* lddqu       xmm4,[eax]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x68,0x10 )                          /* lddqu       xmm5,[eax+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x70,0x20 )                          /* lddqu       xmm6,[eax+20h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x78,0x30 )                          /* lddqu       xmm7,[eax+30h]  */ \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x04))               /* mov         eax,dword ptr [esp+04h] */ \
_LINE4( 0xF3,0x0F,0x10,0x10 )                               /* movss       xmm2,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x08 )                          /* movss       xmm3,dword ptr [eax+8]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x0C )                          /* movss       xmm0,dword ptr [eax+12]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )                               /* shufps      xmm0,xmm0,0  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x59,0xC7 )                                    /* mulps       xmm0,xmm7  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+0Ch] */ \
_LINE3( 0x0F,0x58,0xD0 )                                    /* addps       xmm2,xmm0  */ \
_LINE3( 0x0F,0x13,0x10 )                                    /* movlps      qword ptr [eax],xmm2  */ \
_LINE4( 0x0F,0x17,0x50,0x08 )                               /* movhps      qword ptr [eax+8],xmm2 */ \
_END_ASM

/// Умножение двухмерного вектора на матрицу трансформации двойной точности, команды SSE4
#define VECTORP2DDTRANSFORMSSE4_STD \
_LINE4( 0x8B,0x44,0x24,0x08 )        /* mov         eax,dword ptr [b]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x48,0x20 )   /* lddqu       xmm1,xmmword ptr [eax+20h]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )        /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x50,0x60 )   /* lddqu       xmm2,xmmword ptr [eax+60h]  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )        /* mov         eax,dword ptr [a]  */ \
_LINE5( 0xF2,0x0F,0x12,0x58,0x08 )   /* movddup     xmm3,mmword ptr [eax+8]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )        /* mov         ecx,dword ptr [c]  */ \
_LINE4( 0x66,0x0F,0x59,0xD9 )        /* mulpd       xmm3,xmm1  */ \
_LINE4( 0xF2,0x0F,0x12,0x08 )        /* movddup     xmm1,mmword ptr [eax]  */ \
_LINE4( 0x66,0x0F,0x59,0xC8 )        /* mulpd       xmm1,xmm0  */ \
_LINE4( 0x66,0x0F,0x58,0xD9 )        /* addpd       xmm3,xmm1  */ \
_LINE4( 0x66,0x0F,0x58,0xDA )        /* addpd       xmm3,xmm2  */ \
_LINE4( 0x66,0x0F,0x11,0x19 )        /* movupd      xmmword ptr [ecx],xmm3  */ \
_END_ASM

/// Умножение трехмерного вектора на матрицу трансформации двойной точности, команды SSE2
#define VECTORP3DDTRANSFORMSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8] */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0xF2,0x0F,0x10,0x1A )                               /* movsd       xmm3,mmword ptr [edx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x62,0x08 )                          /* movsd       xmm4,mmword ptr [edx+8]  */ \
_LINE4( 0x66,0x0F,0x14,0xC0 )                               /* unpcklpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x08 )                          /* movsd       xmm1,mmword ptr [eax+8]  */ \
_LINE4( 0x66,0x0F,0x14,0xDC )                               /* unpcklpd    xmm3,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xD8 )                               /* mulpd       xmm3,xmm0  */ \
_LINE5( 0xF2,0x0F,0x59,0x42,0x10 )                          /* mulsd       xmm0,mmword ptr [edx+10h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE4( 0x66,0x0F,0x14,0xC9 )                               /* unpcklpd    xmm1,xmm1  */ \
_LINE5( 0x66,0x0F,0x10,0x6A,0x20 )                          /* movupd      xmm5,[edx+20h]  */ \
_LINE4( 0x66,0x0F,0x59,0xE9 )                               /* mulpd       xmm5,xmm1  */ \
_LINE4( 0x66,0x0F,0x14,0xD2 )                               /* unpcklpd    xmm2,xmm2  */ \
_LINE5( 0x66,0x0F,0x10,0x72,0x40 )                          /* movupd      xmm6,[edx+40h]  */ \
_LINE4( 0x66,0x0F,0x59,0xF2 )                               /* mulpd       xmm6,xmm2  */ \
_LINE4( 0x66,0x0F,0x58,0xF5 )                               /* addpd       xmm6,xmm5  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+0Ch] */ \
_LINE5( 0x66,0x0F,0x10,0x7A,0x60 )                          /* movupd      xmm7,[edx+60h]  */ \
_LINE4( 0x66,0x0F,0x58,0xDF )                               /* addpd       xmm3,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xDE )                               /* addpd       xmm3,xmm6  */ \
_LINE5( 0xF2,0x0F,0x59,0x4A,0x30 )                          /* mulsd       xmm1,mmword ptr [edx+30h]  */ \
_LINE4( 0xF2,0x0F,0x11,0x18 )                               /* movsd       mmword ptr [eax],xmm3  */ \
_LINE4( 0xF2,0x0F,0x58,0xC1 )                               /* addsd       xmm0,xmm1  */ \
_LINE5( 0xF2,0x0F,0x59,0x52,0x50 )                          /* mulsd       xmm2,mmword ptr [edx+50h]  */ \
_LINE4( 0x66,0x0F,0x15,0xDB )                               /* unpckhpd    xmm3,xmm3  */ \
_LINE4( 0xF2,0x0F,0x58,0xC2 )                               /* addsd       xmm0,xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x58,0x08 )                          /* movsd       mmword ptr [eax+8],xmm3  */ \
_LINE5( 0xF2,0x0F,0x58,0x42,0x70 )                          /* addsd       xmm0,mmword ptr [edx+70h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x40,0x10 )                          /* movsd       mmword ptr [eax+10h],xmm0  */ \
_END_ASM

/// Умножение трехмерного вектора на матрицу трансформации двойной точности, команды SSE4
#define VECTORP3DDTRANSFORMSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x08 )        /* mov         eax,dword ptr [b]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x50 )     /* movsd       xmm1,mmword ptr [eax+50h]  */ \
_LINE4( 0x8B,0x4C,0x24,0x04 )        /* mov         ecx,dword ptr [a]  */ \
_LINE5( 0xF2,0x0F,0x12,0x51,0x10 )     /* movddup     xmm2,mmword ptr [ecx+10h]  */ \
_LINE5( 0xF2,0x0F,0x12,0x41,0x08 )     /* movddup     xmm0,mmword ptr [ecx+8]  */ \
_LINE4( 0xF2,0x0F,0x12,0x19 )        /* movddup     xmm3,mmword ptr [ecx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x78,0x10 )     /* movsd       xmm7,mmword ptr [eax+10h]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x30 )        /* lddqu       xmm6,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )        /* mov         ecx,dword ptr [c]  */ \
_LINE4( 0x66,0x0F,0x28,0xE2 )        /* movapd      xmm4,xmm2  */ \
_LINE4( 0xF2,0x0F,0x59,0xE1 )        /* mulsd       xmm4,xmm1  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x70 )     /* movsd       xmm1,mmword ptr [eax+70h]  */ \
_LINE4( 0xF2,0x0F,0x58,0xE1 )        /* addsd       xmm4,xmm1  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x30 )     /* movsd       xmm1,mmword ptr [eax+30h]  */ \
_LINE4( 0x66,0x0F,0x28,0xE8 )        /* movapd      xmm5,xmm0  */ \
_LINE4( 0xF2,0x0F,0x59,0xE9 )        /* mulsd       xmm5,xmm1  */ \
_LINE4( 0x66,0x0F,0x28,0xCB )        /* movapd      xmm1,xmm3  */ \
_LINE4( 0xF2,0x0F,0x59,0xCF )        /* mulsd       xmm1,xmm7  */ \
_LINE5( 0xF2,0x0F,0xF0,0x78,0x20 )     /* lddqu       xmm7,xmmword ptr [eax+20h]  */ \
_LINE4( 0x66,0x0F,0x59,0xDE )        /* mulpd       xmm3,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xC7 )        /* mulpd       xmm0,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xC3 )        /* addpd       xmm0,xmm3  */ \
_LINE5( 0xF2,0x0F,0xF0,0x58,0x40 )     /* lddqu       xmm3,xmmword ptr [eax+40h]  */ \
_LINE4( 0x66,0x0F,0x59,0xD3 )        /* mulpd       xmm2,xmm3  */ \
_LINE5( 0xF2,0x0F,0xF0,0x58,0x60 )     /* lddqu       xmm3,xmmword ptr [eax+60h]  */ \
_LINE4( 0x66,0x0F,0x58,0xD3 )        /* addpd       xmm2,xmm3  */ \
_LINE4( 0x66,0x0F,0x58,0xC2 )        /* addpd       xmm0,xmm2  */ \
_LINE4( 0xF2,0x0F,0x58,0xCD )        /* addsd       xmm1,xmm5  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )        /* movupd      xmmword ptr [ecx],xmm0  */ \
_LINE4( 0xF2,0x0F,0x58,0xCC )        /* addsd       xmm1,xmm4  */ \
_LINE5( 0xF2,0x0F,0x11,0x49,0x10 )     /* movsd       mmword ptr [ecx+10h],xmm1 */ \
_END_ASM

/// Умножение трехмерного вектора на матрицу трансформации двойной точности, команды AVX
#define VECTORP3DDTRANSFORMAVX_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )           /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xC4,0xE2,0x7D,0x19,0x00 )      /* vbroadcastsd ymm0,qword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )           /* mov         edx,dword ptr [esp+8]  */ \
_LINE6( 0xC4,0xE2,0x7D,0x19,0x48,0x08 ) /* vbroadcastsd ymm1,qword ptr [eax+8]  */ \
_LINE6( 0xC4,0xE2,0x7D,0x19,0x50,0x10 ) /* vbroadcastsd ymm2,qword ptr [eax+10h]  */ \
_LINE4( 0xC5,0xFD,0x10,0x22 )           /* vmovupd     ymm4,ymmword ptr [edx]  */ \
_LINE5( 0xC5,0xFD,0x10,0x6A,0x20 )      /* vmovupd     ymm5,ymmword ptr [edx+20h]  */ \
_LINE5( 0xC5,0xFD,0x10,0x72,0x40 )      /* vmovupd     ymm6,ymmword ptr [edx+40h]  */ \
_LINE5( 0xC5,0xFD,0x10,0x7A,0x60 )      /* vmovupd     ymm7,ymmword ptr [edx+60h]  */ \
_LINE4( 0xC5,0xFD,0x59,0xC4 )           /* vmulpd      ymm0,ymm0,ymm4  */ \
_LINE4( 0xC5,0xF5,0x59,0xCD )           /* vmulpd      ymm1,ymm1,ymm5  */ \
_LINE4( 0xC5,0xED,0x59,0xD6 )           /* vmulpd      ymm2,ymm2,ymm6  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )           /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE4( 0xC5,0xFD,0x58,0xC7 )           /* vaddpd      ymm0,ymm0,ymm7  */ \
_LINE4( 0xC5,0xF5,0x58,0xCA )           /* vaddpd      ymm1,ymm1,ymm2  */ \
_LINE4( 0xC5,0xFD,0x58,0xC1 )           /* vaddpd      ymm0,ymm0,ymm1  */ \
_LINE6( 0xC4,0xE3,0x7D,0x19,0xC2,0x01 ) /* vextractf128 xmm2,ymm0,1  */ \
_LINE4( 0xC5,0xF9,0x11,0x00 )           /* vmovupd     xmmword ptr [eax],xmm0  */ \
_LINE5( 0xC5,0xFB,0x11,0x50,0x10 )      /* vmovsd      qword ptr [eax+10h],xmm2  */ \
_LINE3( 0xC5,0xF8,0x77 )                /* vzeroupper  */ \
_END_ASM

/// Умножение четырехмерного вектора на матрицу трансформации двойной точности, команды SSE4
#define VECTORP4DDTRANSFORMSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x08 )        /* mov         eax,dword ptr [b]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )        /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x04 )        /* mov         ecx,dword ptr [a]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x58,0x60 )   /* lddqu       xmm3,xmmword ptr [eax+0x60]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x78,0x20 )   /* lddqu       xmm7,xmmword ptr [eax+0x20]  */ \
_LINE4( 0xF2,0x0F,0x12,0x21 )        /* movddup     xmm4,mmword ptr [ecx]  */ \
_LINE5( 0xF2,0x0F,0x12,0x69,0x10 )   /* movddup     xmm5,mmword ptr [ecx+0x10]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x48,0x40 )   /* lddqu       xmm1,xmmword ptr [eax+0x40]  */ \
_LINE5( 0xF2,0x0F,0x12,0x51,0x08 )   /* movddup     xmm2,mmword ptr [ecx+8]  */ \
_LINE5( 0xF2,0x0F,0x12,0x71,0x18 )   /* movddup     xmm6,mmword ptr [ecx+0x18]  */ \
_LINE4( 0x66,0x0F,0x59,0xC4 )        /* mulpd       xmm0,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xFA )        /* mulpd       xmm7,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xCD )        /* mulpd       xmm1,xmm5  */ \
_LINE4( 0x66,0x0F,0x59,0xDE )        /* mulpd       xmm3,xmm6  */ \
_LINE4( 0x66,0x0F,0x58,0xC7 )        /* addpd       xmm0,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xD9 )        /* addpd       xmm3,xmm1  */ \
_LINE5( 0xF2,0x0F,0xF0,0x78,0x10 )   /* lddqu       xmm7,xmmword ptr [eax+0x10]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x48,0x30 )   /* lddqu       xmm1,xmmword ptr [eax+0x30]  */ \
_LINE4( 0x66,0x0F,0x58,0xC3 )        /* addpd       xmm0,xmm3  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )        /* mov         ecx,dword ptr [c]  */ \
_LINE4( 0x66,0x0F,0x59,0xFC )        /* mulpd       xmm7,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xCA )        /* mulpd       xmm1,xmm2  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )        /* movupd      xmmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0xF0,0x58,0x50 )   /* lddqu       xmm3,xmmword ptr [eax+0x50]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x40,0x70 )   /* lddqu       xmm0,xmmword ptr [eax+0x70]  */ \
_LINE4( 0x66,0x0F,0x59,0xDD )        /* mulpd       xmm3,xmm5  */ \
_LINE4( 0x66,0x0F,0x58,0xCF )        /* addpd       xmm1,xmm7  */ \
_LINE4( 0x66,0x0F,0x59,0xC6 )        /* mulpd       xmm0,xmm6  */ \
_LINE4( 0x66,0x0F,0x58,0xCB )        /* addpd       xmm1,xmm3  */ \
_LINE4( 0x66,0x0F,0x58,0xC8 )        /* addpd       xmm1,xmm0  */ \
_LINE5( 0x66,0x0F,0x11,0x49,0x10 )   /* movupd      xmmword ptr [ecx+10h],xmm1  */ \
_END_ASM

/// Умножение четырехмерного вектора на матрицу трансформации двойной точности, команды AVX
#define VECTORP4DDTRANSFORMAVX_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )           /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xC4,0xE2,0x7D,0x19,0x00 )      /* vbroadcastsd ymm0,qword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )           /* mov         edx,dword ptr [esp+8]  */ \
_LINE6( 0xC4,0xE2,0x7D,0x19,0x48,0x08 ) /* vbroadcastsd ymm1,qword ptr [eax+8]  */ \
_LINE6( 0xC4,0xE2,0x7D,0x19,0x50,0x10 ) /* vbroadcastsd ymm2,qword ptr [eax+10h]  */ \
ASM( vbroadcastsd ymm3,qword ptr [eax+24] ) \
_LINE4( 0xC5,0xFD,0x10,0x22 )           /* vmovupd     ymm4,ymmword ptr [edx]  */ \
_LINE5( 0xC5,0xFD,0x10,0x6A,0x20 )      /* vmovupd     ymm5,ymmword ptr [edx+20h]  */ \
_LINE5( 0xC5,0xFD,0x10,0x72,0x40 )      /* vmovupd     ymm6,ymmword ptr [edx+40h]  */ \
_LINE5( 0xC5,0xFD,0x10,0x7A,0x60 )      /* vmovupd     ymm7,ymmword ptr [edx+60h]  */ \
_LINE4( 0xC5,0xFD,0x59,0xC4 )           /* vmulpd      ymm0,ymm0,ymm4  */ \
_LINE4( 0xC5,0xF5,0x59,0xCD )           /* vmulpd      ymm1,ymm1,ymm5  */ \
_LINE4( 0xC5,0xED,0x59,0xD6 )           /* vmulpd      ymm2,ymm2,ymm6  */ \
ASM( vmulpd ymm3,ymm3,ymm7 ) \
_LINE4( 0x8B,0x44,0x24,0x0C )           /* mov         eax,dword ptr [esp+0Ch]  */ \
ASM( vaddpd ymm0,ymm0,ymm3 ) \
_LINE4( 0xC5,0xF5,0x58,0xCA )           /* vaddpd      ymm1,ymm1,ymm2  */ \
_LINE4( 0xC5,0xFD,0x58,0xC1 )           /* vaddpd      ymm0,ymm0,ymm1  */ \
ASM( vmovupd [eax],ymm0 ) \
_LINE3( 0xC5,0xF8,0x77 )                /* vzeroupper  */ \
_END_ASM

// *********************************** TRANSFORM REGISTER FASTCALL **************************************
// vector transform eax-a void * edx-matrix void * ecx-b void *

/// Умножение двухмерного вектора на матрицу трансформации одинарной точности, команды FPU
#define VECTORP2DTRANSFORMFPU \
_BEGIN_ASM \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
 _STR(_DB(0xD9) _DB(0x00)) \
 _STR(_DB(0xD9) _DB(0x02)) \
 _STR(_DB(0xD8) _DB(0xC9)) \
 _STR(_DB(0xD9) _DB(0x42) _DB(0x10)) \
 _STR(_DB(0xD8) _DB(0xCB)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xD8) _DB(0x42) _DB(0x30)) \
 _STR(_DB(0xD9) _DB(0x19)) \
 _STR(_DB(0xD9) _DB(0x42) _DB(0x04)) \
 _STR(_DB(0xDE) _DB(0xC9)) \
 _STR(_DB(0xD9) _DB(0x42) _DB(0x14)) \
 _STR(_DB(0xDE) _DB(0xCA)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xD8) _DB(0x42) _DB(0x34)) \
 _STR(_DB(0xD9) _DB(0x59) _DB(0x04)) \
_END_ASM

/// Умножение трехмерного вектора на матрицу трансформации одинарной точности, команды FPU
#define VECTORP3DTRANSFORMFPU \
_BEGIN_ASM \
_STR(_DB(0xD9) _DB(0x40) _DB(0x08)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
_STR(_DB(0xD9) _DB(0x00)) \
_STR(_DB(0xD9) _DB(0x02)) \
_STR(_DB(0xD8) _DB(0xC9)) \
_STR(_DB(0xD9) _DB(0x42) _DB(0x10)) \
_STR(_DB(0xD8) _DB(0xCB)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xD9) _DB(0x42) _DB(0x20)) \
_STR(_DB(0xD8) _DB(0xCC)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xD8) _DB(0x42) _DB(0x30)) \
_STR(_DB(0xD9) _DB(0x19)) \
_STR(_DB(0xD9) _DB(0x42) _DB(0x04)) \
_STR(_DB(0xD8) _DB(0xC9)) \
_STR(_DB(0xD9) _DB(0x42) _DB(0x14)) \
_STR(_DB(0xD8) _DB(0xCB)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xD9) _DB(0x42) _DB(0x24)) \
_STR(_DB(0xD8) _DB(0xCC)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xD8) _DB(0x42) _DB(0x34)) \
_STR(_DB(0xD9) _DB(0x59) _DB(0x04)) \
_STR(_DB(0xD9) _DB(0x42) _DB(0x08)) \
_STR(_DB(0xDE) _DB(0xC9)) \
_STR(_DB(0xD9) _DB(0x42) _DB(0x18)) \
_STR(_DB(0xDE) _DB(0xCA)) \
_STR(_DB(0xD9) _DB(0x42) _DB(0x28)) \
_STR(_DB(0xDE) _DB(0xCB)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xD8) _DB(0x42) _DB(0x38)) \
_STR(_DB(0xD9) _DB(0x59) _DB(0x08)) \
_END_ASM

/// Умножение трехмерного вектора на матрицу трансформации одинарной точности, команды SSE
#define VECTORP3DTRANSFORMSSE \
_BEGIN_ASM \
_LINE3( 0x0F,0x12,0x22 )                                    /* movlps      xmm4,qword ptr [edx]  */ \
_LINE4( 0x0F,0x16,0x62,0x08 )                               /* movhps      xmm4,qword ptr [edx+8]  */ \
_LINE4( 0x0F,0x12,0x6A,0x10 )                               /* movlps      xmm5,qword ptr [edx+10h]  */ \
_LINE4( 0x0F,0x16,0x6A,0x18 )                               /* movhps      xmm5,qword ptr [edx+18h]  */ \
_LINE4( 0x0F,0x12,0x72,0x20 )                               /* movlps      xmm6,qword ptr [edx+20h]  */ \
_LINE4( 0x0F,0x16,0x72,0x28 )                               /* movhps      xmm6,qword ptr [edx+28h]  */ \
_LINE4( 0x0F,0x12,0x7A,0x30 )                               /* movlps      xmm7,qword ptr [edx+30h]  */ \
_LINE4( 0x0F,0x16,0x7A,0x38 )                               /* movhps      xmm7,qword ptr [edx+38h]  */ \
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
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
_LINE3( 0x0F,0x13,0x11 )                                    /* movlps      qword ptr [ecx],xmm2  */ \
_LINE3( 0x0F,0x15,0xD2 )                                    /* unpckhps    xmm2,xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x51,0x08 )                          /* movss       dword ptr [ecx+8],xmm2 */ \
_END_ASM

/// Умножение трехмерного вектора на матрицу трансформации одинарной точности, команды SSE3
#define VECTORP3DTRANSFORMSSE3 \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x22 )                               /* lddqu       xmm4,[edx]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x6A,0x10 )                          /* lddqu       xmm5,[edx+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x72,0x20 )                          /* lddqu       xmm6,[edx+20h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x7A,0x30 )                          /* lddqu       xmm7,[edx+30h]  */ \
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
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
_LINE3( 0x0F,0x13,0x11 )                                    /* movlps      qword ptr [ecx],xmm2  */ \
_LINE3( 0x0F,0x15,0xD2 )                                    /* unpckhps    xmm2,xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x51,0x08 )                          /* movss       dword ptr [ecx+8],xmm2  */ \
_END_ASM

/// Умножение четырехмерного вектора на матрицу трансформации одинарной точности, команды FPU
#define VECTORP4DTRANSFORMFPU \
_BEGIN_ASM \
_LINE3( 0xD9,0x40,0x0C )                                    /* fld         dword ptr [eax+0Ch]  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE3( 0xD9,0x42,0x0C )                                    /* fld         dword ptr [edx+0Ch]  */ \
_LINE2( 0xD8,0xC9 )                                         /* fmul        st,st(1)  */ \
_LINE3( 0xD9,0x42,0x1C )                                    /* fld         dword ptr [edx+1Ch]  */ \
_LINE2( 0xD8,0xCB )                                         /* fmul        st,st(3)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x42,0x2C )                                    /* fld         dword ptr [edx+2Ch]  */ \
_LINE2( 0xD8,0xCC )                                         /* fmul        st,st(4)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x42,0x3C )                                    /* fld         dword ptr [edx+3Ch]  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x59,0x0C )                                    /* fstp        dword ptr [ecx+0Ch]  */ \
_LINE2( 0xD9,0x02 )                                         /* fld         dword ptr [edx]  */ \
_LINE2( 0xD8,0xC9 )                                         /* fmul        st,st(1)  */ \
_LINE3( 0xD9,0x42,0x10 )                                    /* fld         dword ptr [edx+10h]  */ \
_LINE2( 0xD8,0xCB )                                         /* fmul        st,st(3)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x42,0x20 )                                    /* fld         dword ptr [edx+20h]  */ \
_LINE2( 0xD8,0xCC )                                         /* fmul        st,st(4)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x42,0x30 )                                    /* fld         dword ptr [edx+30h]  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xD9,0x19 )                                         /* fstp        dword ptr [ecx]  */ \
_LINE3( 0xD9,0x42,0x04 )                                    /* fld         dword ptr [edx+4]  */ \
_LINE2( 0xD8,0xC9 )                                         /* fmul        st,st(1)  */ \
_LINE3( 0xD9,0x42,0x14 )                                    /* fld         dword ptr [edx+14h]  */ \
_LINE2( 0xD8,0xCB )                                         /* fmul        st,st(3)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x42,0x24 )                                    /* fld         dword ptr [edx+24h]  */ \
_LINE2( 0xD8,0xCC )                                         /* fmul        st,st(4)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x42,0x34 )                                    /* fld         dword ptr [edx+34h]  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x59,0x04 )                                    /* fstp        dword ptr [ecx+4]  */ \
_LINE3( 0xD9,0x42,0x08 )                                    /* fld         dword ptr [edx+8]  */ \
_LINE2( 0xDE,0xC9 )                                         /* fmulp       st(1),st  */ \
_LINE3( 0xD9,0x42,0x18 )                                    /* fld         dword ptr [edx+18h]  */ \
_LINE2( 0xDE,0xCA )                                         /* fmulp       st(2),st  */ \
_LINE3( 0xD9,0x42,0x28 )                                    /* fld         dword ptr [edx+28h]  */ \
_LINE2( 0xDE,0xCB )                                         /* fmulp       st(3),st  */ \
_LINE3( 0xD9,0x42,0x38 )                                    /* fld         dword ptr [edx+38h]  */ \
_LINE2( 0xDE,0xCC )                                         /* fmulp       st(4),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x59,0x08 )                                    /* fstp        dword ptr [ecx+8] */ \
_END_ASM

/// Умножение четырехмерного вектора на матрицу трансформации одинарной точности, команды 3DNOW
#define VECTORP4DTRANSFORM3DNOW \
_BEGIN_ASM \
_LINE3( 0x0F,0x6F,0x00 )                                    /* movq        mm0,mmword ptr [eax]  */ \
_LINE4( 0x0F,0x6F,0x48,0x08 )                               /* movq        mm1,mmword ptr [eax+8]  */ \
_LINE3( 0x0F,0x6F,0x22 )                                    /* movq        mm4,mmword ptr [edx]  */ \
_LINE3( 0x0F,0x6A,0xD0 )                                    /* punpckhdq   mm2,mm0  */ \
_LINE4( 0x0F,0x6F,0x6A,0x10 )                               /* movq        mm5,mmword ptr [edx+10h]  */ \
_LINE3( 0x0F,0x62,0xC0 )                                    /* punpckldq   mm0,mm0  */ \
_LINE4( 0x0F,0x6F,0x72,0x20 )                               /* movq        mm6,mmword ptr [edx+20h]  */ \
_LINE4( 0x0F,0x0F,0xE0,0xB4 )                               /* pfmul       mm4,mm0  */ \
_LINE4( 0x0F,0x6F,0x7A,0x30 )                               /* movq        mm7,mmword ptr [edx+30h]  */ \
_LINE3( 0x0F,0x6A,0xD2 )                                    /* punpckhdq   mm2,mm2  */ \
_LINE3( 0x0F,0x6A,0xD9 )                                    /* punpckhdq   mm3,mm1  */ \
_LINE4( 0x0F,0x0F,0xEA,0xB4 )                               /* pfmul       mm5,mm2  */ \
_LINE3( 0x0F,0x62,0xC9 )                                    /* punpckldq   mm1,mm1  */ \
_LINE5( 0x0F,0x0F,0x42,0x08,0xB4 )                          /* pfmul       mm0,mmword ptr [edx+8]  */ \
_LINE3( 0x0F,0x6A,0xDB )                                    /* punpckhdq   mm3,mm3  */ \
_LINE5( 0x0F,0x0F,0x52,0x18,0xB4 )                          /* pfmul       mm2,mmword ptr [edx+18h]  */ \
_LINE4( 0x0F,0x0F,0xF1,0xB4 )                               /* pfmul       mm6,mm1  */ \
_LINE4( 0x0F,0x0F,0xEC,0x9E )                               /* pfadd       mm5,mm4  */ \
_LINE5( 0x0F,0x0F,0x4A,0x28,0xB4 )                          /* pfmul       mm1,mmword ptr [edx+28h]  */ \
_LINE4( 0x0F,0x0F,0xD0,0x9E )                               /* pfadd       mm2,mm0  */ \
_LINE4( 0x0F,0x0F,0xFB,0xB4 )                               /* pfmul       mm7,mm3  */ \
_LINE4( 0x0F,0x0F,0xF5,0x9E )                               /* pfadd       mm6,mm5  */ \
_LINE5( 0x0F,0x0F,0x5A,0x38,0xB4 )                          /* pfmul       mm3,mmword ptr [edx+38h]  */ \
_LINE4( 0x0F,0x0F,0xD1,0x9E )                               /* pfadd       mm2,mm1  */ \
_LINE4( 0x0F,0x0F,0xFE,0x9E )                               /* pfadd       mm7,mm6  */ \
_LINE4( 0x0F,0x0F,0xDA,0x9E )                               /* pfadd       mm3,mm2  */ \
_LINE3( 0x0F,0x7F,0x39 )                                    /* movq        mmword ptr [ecx],mm7  */ \
_LINE4( 0x0F,0x7F,0x59,0x08 )                               /* movq        mmword ptr [ecx+8],mm3  */ \
_LINE2( 0x0F,0x0E )                                         /* femms   */ \
_END_ASM

/// Умножение четырехмерного вектора на матрицу трансформации одинарной точности, команды SSE
#define VECTORP4DTRANSFORMSSE \
_BEGIN_ASM \
_LINE3( 0x0F,0x10,0x22 )                                    /* movups      xmm4,[edx]  */ \
_LINE4( 0x0F,0x10,0x6A,0x10 )                               /* movups      xmm5,[edx+10h]  */ \
_LINE4( 0x0F,0x10,0x72,0x20 )                               /* movups      xmm6,[edx+20h]  */ \
_LINE4( 0x0F,0x10,0x7A,0x30 )                               /* movups      xmm7,[edx+30h]  */ \
_LINE3( 0x0F,0x10,0x00 )                                    /* movups      xmm0,[eax]  */ \
_LINE3( 0x0F,0x10,0xD0 )                                    /* movups      xmm2,xmm0  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE3( 0x0F,0x10,0xC8 )                                    /* movups      xmm1,xmm0  */ \
_LINE4( 0x0F,0xC6,0xC9,0x55 )                               /* shufps      xmm1,xmm1,55h  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x10,0xC8 )                                    /* movups      xmm1,xmm0  */ \
_LINE4( 0x0F,0xC6,0xC9,0xAA )                               /* shufps      xmm1,xmm1,0AAh  */ \
_LINE3( 0x0F,0x59,0xCE )                                    /* mulps       xmm1,xmm6  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x10,0xC8 )                                    /* movups      xmm1,xmm0  */ \
_LINE4( 0x0F,0xC6,0xC9,0xFF )                               /* shufps      xmm1,xmm1,0FFh  */ \
_LINE3( 0x0F,0x59,0xCF )                                    /* mulps       xmm1,xmm7  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x11,0x11 )                                    /* movups      [ecx],xmm2  */ \
_END_ASM

/// Умножение трехмерного вектора на матрицу трансформации одинарной точности, команды SSE3
#define VECTORP4DTRANSFORMSSE3 \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x22 )                               /* lddqu       xmm4,[edx]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x6A,0x10 )                          /* lddqu       xmm5,[edx+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x72,0x20 )                          /* lddqu       xmm6,[edx+20h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x7A,0x30 )                          /* lddqu       xmm7,[edx+30h]  */ \
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
_LINE5( 0xF3,0x0F,0x10,0x60,0x0C )                          /* movss       xmm4,dword ptr [eax+0Ch]  */ \
_LINE4( 0x0F,0xC6,0xE4,0x00 )                               /* shufps      xmm4,xmm4,0  */ \
_LINE3( 0x0F,0x59,0xE7 )                                    /* mulps       xmm4,xmm7  */ \
_LINE3( 0x0F,0x58,0xD4 )                                    /* addps       xmm2,xmm4  */ \
_LINE3( 0x0F,0x13,0x11 )                                    /* movlps      qword ptr [ecx],xmm2  */ \
_LINE4( 0x0F,0x17,0x51,0x08 )                               /* movhps      qword ptr [ecx+8],xmm2 */ \
_END_ASM

/// Умножение двухмкрного вектора на матрицу трансформации двойной точности, команды FPU
#define VECTORP2DDTRANSFORMFPU \
_BEGIN_ASM \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x00)) \
 _STR(_DB(0xDD) _DB(0x02)) \
 _STR(_DB(0xD8) _DB(0xC9)) \
 _STR(_DB(0xDD) _DB(0x42) _DB(0x20)) \
 _STR(_DB(0xD8) _DB(0xCB)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xDC) _DB(0x42) _DB(0x60)) \
 _STR(_DB(0xDD) _DB(0x19)) \
 _STR(_DB(0xDD) _DB(0x42) _DB(0x08)) \
 _STR(_DB(0xDE) _DB(0xC9)) \
 _STR(_DB(0xDD) _DB(0x42) _DB(0x28)) \
 _STR(_DB(0xDE) _DB(0xCA)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xDC) _DB(0x42) _DB(0x68)) \
 _STR(_DB(0xDD) _DB(0x59) _DB(0x08)) \
_END_ASM

/// Умножение трехмерного вектора на матрицу трансформации двойной точности, команды FPU
#define VECTORP3DDTRANSFORMFPU \
_BEGIN_ASM \
_STR(_DB(0xDD) _DB(0x40) _DB(0x10)) \
_STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
_STR(_DB(0xDD) _DB(0x00)) \
_STR(_DB(0xDD) _DB(0x02)) \
_STR(_DB(0xD8) _DB(0xC9)) \
_STR(_DB(0xDD) _DB(0x42) _DB(0x20)) \
_STR(_DB(0xD8) _DB(0xCB)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xDD) _DB(0x42) _DB(0x40)) \
_STR(_DB(0xD8) _DB(0xCC)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xDC) _DB(0x42) _DB(0x60)) \
_STR(_DB(0xDD) _DB(0x19)) \
_STR(_DB(0xDD) _DB(0x42) _DB(0x08)) \
_STR(_DB(0xD8) _DB(0xC9)) \
_STR(_DB(0xDD) _DB(0x42) _DB(0x28)) \
_STR(_DB(0xD8) _DB(0xCB)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xDD) _DB(0x42) _DB(0x48)) \
_STR(_DB(0xD8) _DB(0xCC)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xDC) _DB(0x42) _DB(0x68)) \
_STR(_DB(0xDD) _DB(0x59) _DB(0x08)) \
_STR(_DB(0xDD) _DB(0x42) _DB(0x10)) \
_STR(_DB(0xDE) _DB(0xC9)) \
_STR(_DB(0xDD) _DB(0x42) _DB(0x30)) \
_STR(_DB(0xDE) _DB(0xCA)) \
_STR(_DB(0xDD) _DB(0x42) _DB(0x50)) \
_STR(_DB(0xDE) _DB(0xCB)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xDC) _DB(0x42) _DB(0x70)) \
_STR(_DB(0xDD) _DB(0x59) _DB(0x10)) \
_END_ASM

/// Умножение трехмерного вектора на матрицу трансформации двойной точности, команды SSE2
#define VECTORP3DDTRANSFORMSSE2 \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0xF2,0x0F,0x10,0x1A )                               /* movsd       xmm3,mmword ptr [edx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x62,0x08 )                          /* movsd       xmm4,mmword ptr [edx+8]  */ \
_LINE4( 0x66,0x0F,0x14,0xC0 )                               /* unpcklpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x08 )                          /* movsd       xmm1,mmword ptr [eax+8]  */ \
_LINE4( 0x66,0x0F,0x14,0xDC )                               /* unpcklpd    xmm3,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xD8 )                               /* mulpd       xmm3,xmm0  */ \
_LINE5( 0xF2,0x0F,0x59,0x42,0x10 )                          /* mulsd       xmm0,mmword ptr [edx+10h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE4( 0x66,0x0F,0x14,0xC9 )                               /* unpcklpd    xmm1,xmm1  */ \
_LINE5( 0x66,0x0F,0x10,0x6A,0x20 )                          /* movupd      xmm5,[edx+20h]  */ \
_LINE4( 0x66,0x0F,0x59,0xE9 )                               /* mulpd       xmm5,xmm1  */ \
_LINE4( 0x66,0x0F,0x14,0xD2 )                               /* unpcklpd    xmm2,xmm2  */ \
_LINE5( 0x66,0x0F,0x10,0x72,0x40 )                          /* movupd      xmm6,[edx+40h]  */ \
_LINE4( 0x66,0x0F,0x59,0xF2 )                               /* mulpd       xmm6,xmm2  */ \
_LINE4( 0x66,0x0F,0x58,0xF5 )                               /* addpd       xmm6,xmm5  */ \
_LINE5( 0x66,0x0F,0x10,0x7A,0x60 )                          /* movupd      xmm7,[edx+60h]  */ \
_LINE4( 0x66,0x0F,0x58,0xDF )                               /* addpd       xmm3,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xDE )                               /* addpd       xmm3,xmm6  */ \
_LINE5( 0xF2,0x0F,0x59,0x4A,0x30 )                          /* mulsd       xmm1,mmword ptr [edx+30h]  */ \
_LINE4( 0xF2,0x0F,0x11,0x19 )                               /* movsd       mmword ptr [ecx],xmm3  */ \
_LINE4( 0xF2,0x0F,0x58,0xC1 )                               /* addsd       xmm0,xmm1  */ \
_LINE5( 0xF2,0x0F,0x59,0x52,0x50 )                          /* mulsd       xmm2,mmword ptr [edx+50h]  */ \
_LINE4( 0x66,0x0F,0x15,0xDB )                               /* unpckhpd    xmm3,xmm3  */ \
_LINE4( 0xF2,0x0F,0x58,0xC2 )                               /* addsd       xmm0,xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x59,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm3  */ \
_LINE5( 0xF2,0x0F,0x58,0x42,0x70 )                          /* addsd       xmm0,mmword ptr [edx+70h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm0  */ \
_END_ASM

/*_ASM movsd xmm0,[eax] \
_ASM movsd xmm1,[eax+8] \
_ASM movsd xmm2,[eax+0x10] \
_ASM unpcklpd xmm0,xmm0 \
_ASM movupd xmm3,[edx] \
_ASM unpcklpd xmm1,xmm1 \
_ASM movupd xmm5,[edx+0x20] \
_ASM unpcklpd xmm2,xmm2 \
_ASM movupd xmm6,[edx+0x40] \
_ASM mulpd xmm3,xmm0 \
_ASM mulpd xmm5,xmm1 \
_ASM mulpd xmm6,xmm2 \
_ASM movupd xmm7,[edx+0x60] \
_ASM addpd xmm6,xmm5 \
_ASM addpd xmm3,xmm7 \
_ASM movsd xmm4,[edx+0x10] \
_ASM addpd xmm3,xmm6 \
_ASM movsd xmm5,[edx+0x30] \
_ASM movsd [ecx],xmm3 \
_ASM mulsd xmm4,xmm0 \
_ASM movsd xmm6,[edx+0x50] \
_ASM mulsd xmm5,xmm1 \
_ASM unpckhpd xmm3,xmm3 \
_ASM mulsd xmm6,xmm2 \
_ASM movsd xmm7,[edx+0x70] \
_ASM addsd xmm6,xmm5 \
_ASM addsd xmm4,xmm7 \
_ASM movsd [ecx+8],xmm3 \
_ASM addsd xmm4,xmm6 \
_ASM movsd [ecx+0x10],xmm4 \*/

/// Умножение трехмерного вектора на матрицу трансформации двойной точности, команды SSE3
#define VECTORP3DDTRANSFORMSSE3 \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x12,0x00 )                               /* movddup     xmm0,mmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0x12,0x48,0x08 )                          /* movddup     xmm1,mmword ptr [eax+8]  */ \
_LINE5( 0xF2,0x0F,0x12,0x50,0x10 )                          /* movddup     xmm2,mmword ptr [eax+10h]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x22 )                               /* lddqu       xmm4,[edx]  */ \
_LINE4( 0x66,0x0F,0x59,0xE0 )                               /* mulpd       xmm4,xmm0  */ \
_LINE5( 0xF2,0x0F,0x59,0x42,0x10 )                          /* mulsd       xmm0,mmword ptr [edx+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x6A,0x20 )                          /* lddqu       xmm5,[edx+20h]  */ \
_LINE4( 0x66,0x0F,0x59,0xE9 )                               /* mulpd       xmm5,xmm1  */ \
_LINE5( 0xF2,0x0F,0x59,0x4A,0x30 )                          /* mulsd       xmm1,mmword ptr [edx+30h]  */ \
_LINE4( 0x66,0x0F,0x58,0xE5 )                               /* addpd       xmm4,xmm5  */ \
_LINE4( 0xF2,0x0F,0x58,0xC1 )                               /* addsd       xmm0,xmm1  */ \
_LINE5( 0xF2,0x0F,0xF0,0x72,0x40 )                          /* lddqu       xmm6,[edx+40h]  */ \
_LINE4( 0x66,0x0F,0x59,0xF2 )                               /* mulpd       xmm6,xmm2  */ \
_LINE5( 0xF2,0x0F,0x59,0x52,0x50 )                          /* mulsd       xmm2,mmword ptr [edx+50h]  */ \
_LINE4( 0x66,0x0F,0x58,0xE6 )                               /* addpd       xmm4,xmm6  */ \
_LINE4( 0xF2,0x0F,0x58,0xC2 )                               /* addsd       xmm0,xmm2  */ \
_LINE5( 0xF2,0x0F,0xF0,0x7A,0x60 )                          /* lddqu       xmm7,[edx+60h]  */ \
_LINE5( 0xF2,0x0F,0x58,0x42,0x70 )                          /* addsd       xmm0,mmword ptr [edx+70h]  */ \
_LINE4( 0x66,0x0F,0x58,0xE7 )                               /* addpd       xmm4,xmm7  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm0  */ \
_LINE4( 0xF2,0x0F,0x11,0x21 )                               /* movsd       mmword ptr [ecx],xmm4  */ \
_LINE4( 0x66,0x0F,0x15,0xE4 )                               /* unpckhpd    xmm4,xmm4  */ \
_LINE5( 0xF2,0x0F,0x11,0x61,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm4  */ \
_END_ASM

/*
_ASM movddup xmm0,[eax] \
_ASM movddup xmm1,[eax+8] \
_ASM movddup xmm2,[eax+0x10] \
_ASM lddqu xmm3,[edx] \
_ASM lddqu xmm5,[edx+0x20] \
_ASM lddqu xmm6,[edx+0x40] \
_ASM mulpd xmm3,xmm0 \
_ASM mulpd xmm5,xmm1 \
_ASM mulpd xmm6,xmm2 \
_ASM lddqu xmm7,[edx+0x60] \
_ASM addpd xmm6,xmm5 \
_ASM addpd xmm3,xmm7 \
_ASM movsd xmm4,[edx+0x10] \
_ASM addpd xmm3,xmm6 \
_ASM movsd xmm5,[edx+0x30] \
_ASM movsd [ecx],xmm3 \
_ASM mulsd xmm4,xmm0 \
_ASM movsd xmm6,[edx+0x50] \
_ASM mulsd xmm5,xmm1 \
_ASM unpckhpd xmm3,xmm3 \
_ASM mulsd xmm6,xmm2 \
_ASM movsd xmm7,[edx+0x70] \
_ASM addsd xmm6,xmm5 \
_ASM addsd xmm4,xmm7 \
_ASM movsd [ecx+8],xmm3 \
_ASM addsd xmm4,xmm6 \
_ASM movsd [ecx+0x10],xmm4 \
*/

/*_ASM movddup xmm0,[eax] \
_ASM movddup xmm1,[eax+8] \
_ASM movddup xmm2,[eax+0x10] \
_ASM movsd xmm4,[edx+0x30] \
_ASM lddqu xmm3,[edx] \
_ASM mulsd xmm4,xmm1 \
_ASM movsd xmm6,[edx+0x50] \
_ASM mulpd xmm3,xmm0 \
_ASM lddqu xmm5,[edx+0x20] \
_ASM mulsd xmm6,xmm2 \
_ASM mulpd xmm5,xmm1 \
_ASM addsd xmm4,xmm6 \
_ASM addpd xmm3,xmm5 \
_ASM movsd xmm6,[edx+0x10] \
_ASM lddqu xmm5,[edx+0x40] \
_ASM mulsd xmm6,xmm0 \
_ASM mulpd xmm5,xmm2 \
_ASM addsd xmm4,xmm6 \
_ASM addpd xmm3,xmm5 \
_ASM addsd xmm4,[edx+0x70] \
_ASM lddqu xmm5,[edx+0x60] \
_ASM movsd [ecx+0x10],xmm4 \
_ASM addpd xmm3,xmm5 \
_ASM movsd [ecx],xmm3 \
_ASM unpckhpd xmm3,xmm3 \
_ASM movsd [ecx+8],xmm3 \*/

/// Умножение четырехмерного вектора на матрицу трансформации двойной точности, команды FPU
#define VECTORP4DDTRANSFORMFPU \
_BEGIN_ASM \
_LINE3( 0xDD,0x40,0x18 )                                    /* fld         qword ptr [eax+18h]  */ \
_LINE3( 0xDD,0x40,0x10 )                                    /* fld         qword ptr [eax+10h]  */ \
_LINE3( 0xDD,0x40,0x08 )                                    /* fld         qword ptr [eax+8]  */ \
_LINE2( 0xDD,0x00 )                                         /* fld         qword ptr [eax]  */ \
_LINE3( 0xDD,0x42,0x18 )                                    /* fld         qword ptr [edx+18h]  */ \
_LINE2( 0xD8,0xC9 )                                         /* fmul        st,st(1)  */ \
_LINE3( 0xDD,0x42,0x38 )                                    /* fld         qword ptr [edx+38h]  */ \
_LINE2( 0xD8,0xCB )                                         /* fmul        st,st(3)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x42,0x58 )                                    /* fld         qword ptr [edx+58h]  */ \
_LINE2( 0xD8,0xCC )                                         /* fmul        st,st(4)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x42,0x78 )                                    /* fld         qword ptr [edx+78h]  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x59,0x18 )                                    /* fstp        qword ptr [ecx+18h]  */ \
_LINE2( 0xDD,0x02 )                                         /* fld         qword ptr [edx]  */ \
_LINE2( 0xD8,0xC9 )                                         /* fmul        st,st(1)  */ \
_LINE3( 0xDD,0x42,0x20 )                                    /* fld         qword ptr [edx+20h]  */ \
_LINE2( 0xD8,0xCB )                                         /* fmul        st,st(3)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x42,0x40 )                                    /* fld         qword ptr [edx+40h]  */ \
_LINE2( 0xD8,0xCC )                                         /* fmul        st,st(4)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x42,0x60 )                                    /* fld         qword ptr [edx+60h]  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xDD,0x19 )                                         /* fstp        qword ptr [ecx]  */ \
_LINE3( 0xDD,0x42,0x08 )                                    /* fld         qword ptr [edx+8]  */ \
_LINE2( 0xD8,0xC9 )                                         /* fmul        st,st(1)  */ \
_LINE3( 0xDD,0x42,0x28 )                                    /* fld         qword ptr [edx+28h]  */ \
_LINE2( 0xD8,0xCB )                                         /* fmul        st,st(3)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x42,0x48 )                                    /* fld         qword ptr [edx+48h]  */ \
_LINE2( 0xD8,0xCC )                                         /* fmul        st,st(4)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x42,0x68 )                                    /* fld         qword ptr [edx+68h]  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x59,0x08 )                                    /* fstp        qword ptr [ecx+8]  */ \
_LINE3( 0xDD,0x42,0x10 )                                    /* fld         qword ptr [edx+10h]  */ \
_LINE2( 0xDE,0xC9 )                                         /* fmulp       st(1),st  */ \
_LINE3( 0xDD,0x42,0x30 )                                    /* fld         qword ptr [edx+30h]  */ \
_LINE2( 0xDE,0xCA )                                         /* fmulp       st(2),st  */ \
_LINE3( 0xDD,0x42,0x50 )                                    /* fld         qword ptr [edx+50h]  */ \
_LINE2( 0xDE,0xCB )                                         /* fmulp       st(3),st  */ \
_LINE3( 0xDD,0x42,0x70 )                                    /* fld         qword ptr [edx+70h]  */ \
_LINE2( 0xDE,0xCC )                                         /* fmulp       st(4),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x59,0x10 )                                    /* fstp        qword ptr [ecx+10h]  */ \
_END_ASM

/// Умножение четырехмерного вектора на матрицу трансформации двойной точности, команды SSE2
#define VECTORP4DDTRANSFORMSSE2 \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x08 )                          /* movsd       xmm1,mmword ptr [eax+8]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x58,0x18 )                          /* movsd       xmm3,mmword ptr [eax+18h]  */ \
_LINE4( 0x66,0x0F,0x14,0xC0 )                               /* unpcklpd    xmm0,xmm0  */ \
_LINE3( 0x0F,0x10,0x22 )                                    /* movups      xmm4,[edx]  */ \
_LINE4( 0x66,0x0F,0x14,0xC9 )                               /* unpcklpd    xmm1,xmm1  */ \
_LINE4( 0x66,0x0F,0x14,0xD2 )                               /* unpcklpd    xmm2,xmm2  */ \
_LINE4( 0x66,0x0F,0x14,0xDB )                               /* unpcklpd    xmm3,xmm3  */ \
_LINE4( 0x0F,0x10,0x6A,0x20 )                               /* movups      xmm5,[edx+20h]  */ \
_LINE4( 0x66,0x0F,0x59,0xE0 )                               /* mulpd       xmm4,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xE9 )                               /* mulpd       xmm5,xmm1  */ \
_LINE4( 0x0F,0x10,0x72,0x40 )                               /* movups      xmm6,[edx+40h]  */ \
_LINE4( 0x66,0x0F,0x58,0xE5 )                               /* addpd       xmm4,xmm5  */ \
_LINE4( 0x66,0x0F,0x59,0xF2 )                               /* mulpd       xmm6,xmm2  */ \
_LINE4( 0x0F,0x10,0x7A,0x60 )                               /* movups      xmm7,[edx+60h]  */ \
_LINE4( 0x66,0x0F,0x58,0xE6 )                               /* addpd       xmm4,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xFB )                               /* mulpd       xmm7,xmm3  */ \
_LINE4( 0x66,0x0F,0x58,0xE7 )                               /* addpd       xmm4,xmm7  */ \
_LINE4( 0xF2,0x0F,0x11,0x21 )                               /* movsd       mmword ptr [ecx],xmm4  */ \
_LINE4( 0x0F,0x10,0x72,0x10 )                               /* movups      xmm6,[edx+10h]  */ \
_LINE4( 0x66,0x0F,0x15,0xE4 )                               /* unpckhpd    xmm4,xmm4  */ \
_LINE4( 0x0F,0x10,0x7A,0x30 )                               /* movups      xmm7,[edx+30h]  */ \
_LINE5( 0xF2,0x0F,0x11,0x61,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xF0 )                               /* mulpd       xmm6,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xF9 )                               /* mulpd       xmm7,xmm1  */ \
_LINE4( 0x0F,0x10,0x62,0x50 )                               /* movups      xmm4,[edx+50h]  */ \
_LINE4( 0x66,0x0F,0x58,0xF7 )                               /* addpd       xmm6,xmm7  */ \
_LINE4( 0x66,0x0F,0x59,0xE2 )                               /* mulpd       xmm4,xmm2  */ \
_LINE4( 0x0F,0x10,0x6A,0x70 )                               /* movups      xmm5,[edx+70h]  */ \
_LINE4( 0x66,0x0F,0x58,0xF4 )                               /* addpd       xmm6,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xEB )                               /* mulpd       xmm5,xmm3  */ \
_LINE4( 0x66,0x0F,0x58,0xF5 )                               /* addpd       xmm6,xmm5  */ \
_LINE4( 0x0F,0x11,0x71,0x10 )                               /* movups      [ecx+10h],xmm6  */ \
_END_ASM

/*_ASM movsd xmm0,[eax] \
_ASM movsd xmm1,[eax+8] \
_ASM movsd xmm2,[eax+0x10] \
_ASM movsd xmm3,[eax+0x18] \
_ASM unpcklpd xmm0,xmm0 \
_ASM unpcklpd xmm1,xmm1 \
_ASM unpcklpd xmm2,xmm2 \
_ASM unpcklpd xmm3,xmm3 \
_ASM movups xmm4,[edx] \
_ASM movups xmm5,[edx+20h] \
_ASM movups xmm6,[edx+40h] \
_ASM movups xmm7,[edx+60h] \
_ASM mulpd xmm4,xmm0 \
_ASM mulpd xmm5,xmm1 \
_ASM mulpd xmm6,xmm2 \
_ASM mulpd xmm7,xmm3 \
_ASM addpd xmm6,xmm5 \
_ASM addpd xmm4,xmm7 \
_ASM addpd xmm4,xmm6 \
_ASM movups [ecx],xmm4 \
_ASM movups xmm4,[edx+10h] \
_ASM movups xmm5,[edx+30h] \
_ASM mulpd xmm4,xmm0 \
_ASM mulpd xmm5,xmm1 \
_ASM movups xmm6,[edx+50h] \
_ASM addpd xmm4,xmm5 \
_ASM mulpd xmm6,xmm2 \
_ASM movups xmm7,[edx+70h] \
_ASM addpd xmm4,xmm6 \
_ASM mulpd xmm7,xmm3 \
_ASM addpd xmm4,xmm7 \
_ASM movups [ecx+10h],xmm4 \*/

/// Умножение четырехмерного вектора на матрицу трансформации двойной точности, команды SSE3
#define VECTORP4DDTRANSFORMSSE3 \
BEGIN_ASM \
ASM( movddup xmm0,[eax]) \
ASM( movddup xmm1,[eax+8]) \
ASM( movddup xmm2,[eax+0x10]) \
ASM( movddup xmm3,[eax+0x18]) \
ASM( movsd xmm4,[edx]) \
ASM( movhpd xmm4,[edx+8]) \
ASM( movsd xmm5,[edx+0x20]) \
ASM( movhpd xmm5,[edx+0x28]) \
ASM( mulpd xmm4,xmm0) \
ASM( mulpd xmm5,xmm1) \
ASM( movsd xmm6,[edx+0x40]) \
ASM( movhpd xmm6,[edx+0x48]) \
ASM( addpd xmm4,xmm5) \
ASM( mulpd xmm6,xmm2) \
ASM( movsd xmm7,[edx+0x60]) \
ASM( movhpd xmm7,[edx+0x68]) \
ASM( addpd xmm4,xmm6) \
ASM( mulpd xmm7,xmm3) \
ASM( addpd xmm4,xmm7) \
ASM( movsd [ecx+00],xmm4) \
ASM( movhpd [ecx+0x08],xmm4) \
ASM( movsd xmm4,[edx+0x10]) \
ASM( movhpd xmm4,[edx+0x18]) \
ASM( movsd xmm5,[edx+0x30]) \
ASM( movhpd xmm5,[edx+0x38]) \
ASM( mulpd xmm4,xmm0) \
ASM( mulpd xmm5,xmm1) \
ASM( movsd xmm6,[edx+0x50]) \
ASM( movhpd xmm6,[edx+0x58]) \
ASM( addpd xmm4,xmm5) \
ASM( mulpd xmm6,xmm2) \
ASM( movsd xmm7,[edx+0x70]) \
ASM( movhpd xmm7,[edx+0x78]) \
ASM( addpd xmm4,xmm6) \
ASM( mulpd xmm7,xmm3) \
ASM( addpd xmm4,xmm7) \
ASM( movsd [ecx+0x10],xmm4) \
ASM( movhpd [ecx+0x18],xmm4) \
END_ASM

/*
_ASM movddup xmm0,[eax] \
_ASM movddup xmm1,[eax+8] \
_ASM movddup xmm2,[eax+0x10] \
_ASM movddup xmm3,[eax+0x18] \
_ASM lddqu xmm4,[edx] \
_ASM lddqu xmm5,[edx+20h] \
_ASM mulpd xmm4,xmm0 \
_ASM mulpd xmm5,xmm1 \
_ASM lddqu xmm6,[edx+40h] \
_ASM addpd xmm4,xmm5 \
_ASM mulpd xmm6,xmm2 \
_ASM lddqu xmm7,[edx+60h] \
_ASM addpd xmm4,xmm6 \
_ASM mulpd xmm7,xmm3 \
_ASM addpd xmm4,xmm7 \
_ASM movupd [ecx],xmm4 \
_ASM lddqu xmm4,[edx+10h] \
_ASM lddqu xmm5,[edx+30h] \
_ASM mulpd xmm4,xmm0 \
_ASM mulpd xmm5,xmm1 \
_ASM lddqu xmm6,[edx+50h] \
_ASM addpd xmm4,xmm5 \
_ASM mulpd xmm6,xmm2 \
_ASM lddqu xmm7,[edx+70h] \
_ASM addpd xmm4,xmm6 \
_ASM mulpd xmm7,xmm3 \
_ASM addpd xmm4,xmm7 \
_ASM movupd [ecx+10h],xmm4 \
*/

// *********************************** TRANSFORM CPP FASTCALL **************************************
// vector transform ecx-a void * edx-matrix void * eax-b void *

/*/// Умножение двухмерного вектора на матрицу трансформации одинарной точности, команды FPU
#define VECTORP2DTRANSFORMFPU \
_BEGIN_ASM \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
 _STR(_DB(0xD9) _DB(0x00)) \
 _STR(_DB(0xD9) _DB(0x02)) \
 _STR(_DB(0xD8) _DB(0xC9)) \
 _STR(_DB(0xD9) _DB(0x42) _DB(0x10)) \
 _STR(_DB(0xD8) _DB(0xCB)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xD8) _DB(0x42) _DB(0x30)) \
 _STR(_DB(0xD9) _DB(0x19)) \
 _STR(_DB(0xD9) _DB(0x42) _DB(0x04)) \
 _STR(_DB(0xDE) _DB(0xC9)) \
 _STR(_DB(0xD9) _DB(0x42) _DB(0x14)) \
 _STR(_DB(0xDE) _DB(0xCA)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xD8) _DB(0x42) _DB(0x34)) \
 _STR(_DB(0xD9) _DB(0x59) _DB(0x04)) \
_END_ASM

/// Умножение трехмерного вектора на матрицу трансформации одинарной точности, команды FPU
#define VECTORP3DTRANSFORMFPU \
_BEGIN_ASM \
_STR(_DB(0xD9) _DB(0x40) _DB(0x08)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
_STR(_DB(0xD9) _DB(0x00)) \
_STR(_DB(0xD9) _DB(0x02)) \
_STR(_DB(0xD8) _DB(0xC9)) \
_STR(_DB(0xD9) _DB(0x42) _DB(0x10)) \
_STR(_DB(0xD8) _DB(0xCB)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xD9) _DB(0x42) _DB(0x20)) \
_STR(_DB(0xD8) _DB(0xCC)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xD8) _DB(0x42) _DB(0x30)) \
_STR(_DB(0xD9) _DB(0x19)) \
_STR(_DB(0xD9) _DB(0x42) _DB(0x04)) \
_STR(_DB(0xD8) _DB(0xC9)) \
_STR(_DB(0xD9) _DB(0x42) _DB(0x14)) \
_STR(_DB(0xD8) _DB(0xCB)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xD9) _DB(0x42) _DB(0x24)) \
_STR(_DB(0xD8) _DB(0xCC)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xD8) _DB(0x42) _DB(0x34)) \
_STR(_DB(0xD9) _DB(0x59) _DB(0x04)) \
_STR(_DB(0xD9) _DB(0x42) _DB(0x08)) \
_STR(_DB(0xDE) _DB(0xC9)) \
_STR(_DB(0xD9) _DB(0x42) _DB(0x18)) \
_STR(_DB(0xDE) _DB(0xCA)) \
_STR(_DB(0xD9) _DB(0x42) _DB(0x28)) \
_STR(_DB(0xDE) _DB(0xCB)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xD8) _DB(0x42) _DB(0x38)) \
_STR(_DB(0xD9) _DB(0x59) _DB(0x08)) \
_END_ASM

/// Умножение трехмерного вектора на матрицу трансформации одинарной точности, команды SSE
#define VECTORP3DTRANSFORMSSE \
BEGIN_ASM \
_ASM movlps xmm4,[edx] \
_ASM movhps xmm4,[edx+08h] \
_ASM movlps xmm5,[edx+10h] \
_ASM movhps xmm5,[edx+18h] \
_ASM movlps xmm6,[edx+20h] \
_ASM movhps xmm6,[edx+28h] \
_ASM movlps xmm7,[edx+30h] \
_ASM movhps xmm7,[edx+38h] \
_ASM movss xmm2,[eax] \
_ASM shufps xmm2,xmm2,0 \
_ASM mulps xmm2,xmm4 \
_ASM movss xmm1,[eax+4] \
_ASM shufps xmm1,xmm1,0 \
_ASM mulps xmm1,xmm5 \
_ASM addps xmm2,xmm1 \
_ASM movss xmm3,[eax+8] \
_ASM shufps xmm3,xmm3,0 \
_ASM mulps xmm3,xmm6 \
_ASM addps xmm2,xmm3 \
_ASM addps xmm2,xmm7 \
_ASM movlps [ecx],xmm2 \
_ASM unpckhps xmm2,xmm2 \
_ASM movss [ecx+8],xmm2 \
END_ASM

/// Умножение трехмерного вектора на матрицу трансформации одинарной точности, команды SSE3
#define VECTORP3DTRANSFORMSSE3 \
BEGIN_ASM \
_ASM lddqu xmm4,[edx] \
_ASM lddqu xmm5,[edx+10h] \
_ASM lddqu xmm6,[edx+20h] \
_ASM lddqu xmm7,[edx+30h] \
_ASM movss xmm2,[eax] \
_ASM shufps xmm2,xmm2,0 \
_ASM mulps xmm2,xmm4 \
_ASM movss xmm1,[eax+4] \
_ASM shufps xmm1,xmm1,0 \
_ASM mulps xmm1,xmm5 \
_ASM addps xmm2,xmm1 \
_ASM movss xmm3,[eax+8] \
_ASM shufps xmm3,xmm3,0 \
_ASM mulps xmm3,xmm6 \
_ASM addps xmm2,xmm3 \
_ASM addps xmm2,xmm7 \
_ASM movlps [ecx],xmm2 \
_ASM unpckhps xmm2,xmm2 \
_ASM movss [ecx+8],xmm2 \
END_ASM*/

/// Умножение четырехмерного вектора на матрицу трансформации одинарной точности, команды FPU
#define VECTORP4DTRANSFORMFPU_CPP \
BEGIN_ASM \
ASM( fld dword ptr [ecx+0x0C]) \
ASM( fld dword ptr [ecx+8]) \
ASM( fld dword ptr [ecx+4]) \
ASM( fld dword ptr [ecx]) \
ASM( fld dword ptr [edx+0x0C]) \
ASM( fmul st,st(1)) \
ASM( fld dword ptr [edx+0x1C]) \
ASM( fmul st,st(3)) \
ASM( faddp st(1),st) \
ASM( fld dword ptr [edx+0x2C]) \
ASM( fmul st,st(4)) \
ASM( faddp st(1),st) \
ASM( fld dword ptr [edx+0x3C]) \
ASM( fmul st,st(5)) \
ASM( faddp st(1),st) \
ASM( fstp dword ptr [eax+0x0C]) \
ASM( fld dword ptr [edx]) \
ASM( fmul st,st(1)) \
ASM( fld dword ptr [edx+0x10]) \
ASM( fmul st,st(3)) \
ASM( faddp st(1),st) \
ASM( fld dword ptr [edx+0x20]) \
ASM( fmul st,st(4)) \
ASM( faddp st(1),st) \
ASM( fld dword ptr [edx+0x30]) \
ASM( fmul st,st(5)) \
ASM( faddp st(1),st) \
ASM( fstp dword ptr [eax]) \
ASM( fld dword ptr [edx+4]) \
ASM( fmul st,st(1)) \
ASM( fld dword ptr [edx+0x14]) \
ASM( fmul st,st(3)) \
ASM( faddp st(1),st) \
ASM( fld dword ptr [edx+0x24]) \
ASM( fmul st,st(4)) \
ASM( faddp st(1),st) \
ASM( fld dword ptr [edx+0x34]) \
ASM( fmul st,st(5)) \
ASM( faddp st(1),st) \
ASM( fstp dword ptr [eax+4]) \
ASM( fld dword ptr [edx+8]) \
ASM( fmulp st(1),st) \
ASM( fld dword ptr [edx+0x18]) \
ASM( fmulp st(2),st) \
ASM( fld dword ptr [edx+0x28]) \
ASM( fmulp st(3),st) \
ASM( fld dword ptr [edx+0x38]) \
ASM( fmulp st(4),st) \
ASM( faddp st(1),st) \
ASM( faddp st(1),st) \
ASM( faddp st(1),st) \
ASM( fstp dword ptr [eax+8]) \
END_ASM

/*/// Умножение четырехмерного вектора на матрицу трансформации одинарной точности, команды 3DNOW
#define VECTORP4DTRANSFORM3DNOW \
BEGIN_ASM \
_ASM movq mm0,[eax] \
_ASM movq mm1,[eax+8] \
_ASM movq mm4,[edx] \
_ASM punpckhdq mm2,mm0 \
_ASM movq mm5,[edx+16] \
_ASM punpckldq mm0,mm0 \
_ASM movq mm6,[edx+32] \
_ASM pfmul mm4,mm0 \
_ASM movq mm7,[edx+48] \
_ASM punpckhdq mm2,mm2 \
_ASM punpckhdq mm3,mm1 \
_ASM pfmul mm5,mm2 \
_ASM punpckldq mm1,mm1 \
_ASM pfmul mm0,[edx+8] \
_ASM punpckhdq mm3,mm3 \
_ASM pfmul mm2,[edx+24] \
_ASM pfmul mm6,mm1 \
_ASM pfadd mm5,mm4 \
_ASM pfmul mm1,[edx+40] \
_ASM pfadd mm2,mm0 \
_ASM pfmul mm7,mm3 \
_ASM pfadd mm6,mm5 \
_ASM pfmul mm3,[edx+56] \
_ASM pfadd mm2,mm1 \
_ASM pfadd mm7,mm6 \
_ASM pfadd mm3,mm2 \
_ASM movq [ecx],mm7 \
_ASM movq [ecx+8],mm3 \
_ASM femms \
END_ASM

/// Умножение четырехмерного вектора на матрицу трансформации одинарной точности, команды SSE
#define VECTORP4DTRANSFORMSSE \
_BEGIN_ASM \
_STR(_DB(0x0F) _DB(0x10) _DB(0x22)) \
_STR(_DB(0x0F) _DB(0x10) _DB(0x6A) _DB(0x10)) \
_STR(_DB(0x0F) _DB(0x10) _DB(0x72) _DB(0x20)) \
_STR(_DB(0x0F) _DB(0x10) _DB(0x7A) _DB(0x30)) \
_STR(_DB(0x0F) _DB(0x10) _DB(0x00)) \
_STR(_DB(0x0F) _DB(0x10) _DB(0xD0)) \
_STR(_DB(0x0F) _DB(0xC6) _DB(0xD2) _DB(0x00)) \
_STR(_DB(0x0F) _DB(0x59) _DB(0xD4)) \
_STR(_DB(0x0F) _DB(0x10) _DB(0xC8)) \
_STR(_DB(0x0F) _DB(0xC6) _DB(0xC9) _DB(0x55)) \
_STR(_DB(0x0F) _DB(0x59) _DB(0xCD)) \
_STR(_DB(0x0F) _DB(0x58) _DB(0xD1)) \
_STR(_DB(0x0F) _DB(0x10) _DB(0xC8)) \
_STR(_DB(0x0F) _DB(0xC6) _DB(0xC9) _DB(0xAA)) \
_STR(_DB(0x0F) _DB(0x59) _DB(0xCE)) \
_STR(_DB(0x0F) _DB(0x58) _DB(0xD1)) \
_STR(_DB(0x0F) _DB(0x10) _DB(0xC8)) \
_STR(_DB(0x0F) _DB(0xC6) _DB(0xC9) _DB(0xFF)) \
_STR(_DB(0x0F) _DB(0x59) _DB(0xCF)) \
_STR(_DB(0x0F) _DB(0x58) _DB(0xD1)) \
_STR(_DB(0x0F) _DB(0x11) _DB(0x11)) \
_END_ASM

/// Умножение трехмерного вектора на матрицу трансформации одинарной точности, команды SSE3
#define VECTORP4DTRANSFORMSSE3 \
BEGIN_ASM \
_ASM lddqu xmm4,[edx] \
_ASM lddqu xmm5,[edx+10h] \
_ASM lddqu xmm6,[edx+20h] \
_ASM lddqu xmm7,[edx+30h] \
_ASM movss xmm2,[eax] \
_ASM shufps xmm2,xmm2,0 \
_ASM mulps xmm2,xmm4 \
_ASM movss xmm1,[eax+4] \
_ASM shufps xmm1,xmm1,0 \
_ASM mulps xmm1,xmm5 \
_ASM addps xmm2,xmm1 \
_ASM movss xmm3,[eax+8] \
_ASM shufps xmm3,xmm3,0 \
_ASM mulps xmm3,xmm6 \
_ASM addps xmm2,xmm3 \
_ASM movss xmm4,[eax+12] \
_ASM shufps xmm4,xmm4,0 \
_ASM mulps xmm4,xmm7 \
_ASM addps xmm2,xmm4 \
_ASM movlps [ecx],xmm2 \
_ASM movhps [ecx+8],xmm2 \
END_ASM

/// Умножение двухмкрного вектора на матрицу трансформации двойной точности, команды FPU
#define VECTORP2DDTRANSFORMFPU \
_BEGIN_ASM \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x00)) \
 _STR(_DB(0xDD) _DB(0x02)) \
 _STR(_DB(0xD8) _DB(0xC9)) \
 _STR(_DB(0xDD) _DB(0x42) _DB(0x20)) \
 _STR(_DB(0xD8) _DB(0xCB)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xDC) _DB(0x42) _DB(0x60)) \
 _STR(_DB(0xDD) _DB(0x19)) \
 _STR(_DB(0xDD) _DB(0x42) _DB(0x08)) \
 _STR(_DB(0xDE) _DB(0xC9)) \
 _STR(_DB(0xDD) _DB(0x42) _DB(0x28)) \
 _STR(_DB(0xDE) _DB(0xCA)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xDC) _DB(0x42) _DB(0x68)) \
 _STR(_DB(0xDD) _DB(0x59) _DB(0x08)) \
_END_ASM

/// Умножение трехмерного вектора на матрицу трансформации двойной точности, команды FPU
#define VECTORP3DDTRANSFORMFPU \
_BEGIN_ASM \
_STR(_DB(0xDD) _DB(0x40) _DB(0x10)) \
_STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
_STR(_DB(0xDD) _DB(0x00)) \
_STR(_DB(0xDD) _DB(0x02)) \
_STR(_DB(0xD8) _DB(0xC9)) \
_STR(_DB(0xDD) _DB(0x42) _DB(0x20)) \
_STR(_DB(0xD8) _DB(0xCB)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xDD) _DB(0x42) _DB(0x40)) \
_STR(_DB(0xD8) _DB(0xCC)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xDC) _DB(0x42) _DB(0x60)) \
_STR(_DB(0xDD) _DB(0x19)) \
_STR(_DB(0xDD) _DB(0x42) _DB(0x08)) \
_STR(_DB(0xD8) _DB(0xC9)) \
_STR(_DB(0xDD) _DB(0x42) _DB(0x28)) \
_STR(_DB(0xD8) _DB(0xCB)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xDD) _DB(0x42) _DB(0x48)) \
_STR(_DB(0xD8) _DB(0xCC)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xDC) _DB(0x42) _DB(0x68)) \
_STR(_DB(0xDD) _DB(0x59) _DB(0x08)) \
_STR(_DB(0xDD) _DB(0x42) _DB(0x10)) \
_STR(_DB(0xDE) _DB(0xC9)) \
_STR(_DB(0xDD) _DB(0x42) _DB(0x30)) \
_STR(_DB(0xDE) _DB(0xCA)) \
_STR(_DB(0xDD) _DB(0x42) _DB(0x50)) \
_STR(_DB(0xDE) _DB(0xCB)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xDC) _DB(0x42) _DB(0x70)) \
_STR(_DB(0xDD) _DB(0x59) _DB(0x10)) \
_END_ASM

/// Умножение трехмерного вектора на матрицу трансформации двойной точности, команды SSE2
#define VECTORP3DDTRANSFORMSSE2 \
BEGIN_ASM \
_ASM movsd xmm0,[eax] \
_ASM movsd xmm3,[edx] \
_ASM movsd xmm4,[edx+8] \
_ASM unpcklpd xmm0,xmm0 \
_ASM movsd xmm1,[eax+8] \
_ASM unpcklpd xmm3,xmm4 \
_ASM mulpd xmm3,xmm0 \
_ASM mulsd xmm0,[edx+0x10] \
_ASM movsd xmm2,[eax+0x10] \
_ASM unpcklpd xmm1,xmm1 \
_ASM movupd xmm5,[edx+0x20] \
_ASM mulpd xmm5,xmm1 \
_ASM unpcklpd xmm2,xmm2 \
_ASM movupd xmm6,[edx+0x40] \
_ASM mulpd xmm6,xmm2 \
_ASM addpd xmm6,xmm5 \
_ASM movupd xmm7,[edx+0x60] \
_ASM addpd xmm3,xmm7 \
_ASM addpd xmm3,xmm6 \
_ASM mulsd xmm1,[edx+0x30] \
_ASM movsd [ecx],xmm3 \
_ASM addsd xmm0,xmm1 \
_ASM mulsd xmm2,[edx+0x50] \
_ASM unpckhpd xmm3,xmm3 \
_ASM addsd xmm0,xmm2 \
_ASM movsd [ecx+8],xmm3 \
_ASM addsd xmm0,[edx+0x70] \
_ASM movsd [ecx+0x10],xmm0 \
END_ASM

/// Умножение трехмерного вектора на матрицу трансформации двойной точности, команды SSE3
#define VECTORP3DDTRANSFORMSSE3 \
BEGIN_ASM \
_ASM movddup xmm0,[eax] \
_ASM movddup xmm1,[eax+8] \
_ASM movddup xmm2,[eax+0x10] \
_ASM lddqu xmm4,[edx] \
_ASM mulpd xmm4,xmm0 \
_ASM mulsd xmm0,[edx+0x10] \
_ASM lddqu xmm5,[edx+0x20] \
_ASM mulpd xmm5,xmm1 \
_ASM mulsd xmm1,[edx+0x30] \
_ASM addpd xmm4,xmm5 \
_ASM addsd xmm0,xmm1 \
_ASM lddqu xmm6,[edx+0x40] \
_ASM mulpd xmm6,xmm2 \
_ASM mulsd xmm2,[edx+0x50] \
_ASM addpd xmm4,xmm6 \
_ASM addsd xmm0,xmm2 \
_ASM lddqu xmm7,[edx+0x60] \
_ASM addsd xmm0,[edx+0x70] \
_ASM addpd xmm4,xmm7 \
_ASM movsd [ecx+0x10],xmm0 \
_ASM movsd [ecx],xmm4 \
_ASM unpckhpd xmm4,xmm4 \
_ASM movsd [ecx+0x08],xmm4 \
END_ASM*/

/// Умножение четырехмерного вектора на матрицу трансформации двойной точности, команды FPU
#define VECTORP4DDTRANSFORMFPU_CPP \
BEGIN_ASM \
ASM( fld qword ptr [eax+0x18]) \
ASM( fld qword ptr [eax+0x10]) \
ASM( fld qword ptr [eax+8]) \
ASM( fld qword ptr [eax]) \
ASM( fld qword ptr [edx+0x18]) \
ASM( fmul st,st(1)) \
ASM( fld qword ptr [edx+0x38]) \
ASM( fmul st,st(3)) \
ASM( faddp st(1),st) \
ASM( fld qword ptr [edx+0x58]) \
ASM( fmul st,st(4)) \
ASM( faddp st(1),st) \
ASM( fld qword ptr [edx+0x78]) \
ASM( fmul st,st(5)) \
ASM( faddp st(1),st) \
ASM( fstp qword ptr [ecx+0x18]) \
ASM( fld qword ptr [edx]) \
ASM( fmul st,st(1)) \
ASM( fld qword ptr [edx+0x20]) \
ASM( fmul st,st(3)) \
ASM( faddp st(1),st) \
ASM( fld qword ptr [edx+0x40]) \
ASM( fmul st,st(4)) \
ASM( faddp st(1),st) \
ASM( fld qword ptr [edx+0x60]) \
ASM( fmul st,st(5)) \
ASM( faddp st(1),st) \
ASM( fstp qword ptr [ecx]) \
ASM( fld qword ptr [edx+8]) \
ASM( fmul st,st(1)) \
ASM( fld qword ptr [edx+0x28]) \
ASM( fmul st,st(3)) \
ASM( faddp st(1),st) \
ASM( fld qword ptr [edx+0x48]) \
ASM( fmul st,st(4)) \
ASM( faddp st(1),st) \
ASM( fld qword ptr [edx+0x68]) \
ASM( fmul st,st(5)) \
ASM( faddp st(1),st) \
ASM( fstp qword ptr [ecx+8]) \
ASM( fld qword ptr [edx+0x10]) \
ASM( fmulp st(1),st) \
ASM( fld qword ptr [edx+0x30]) \
ASM( fmulp st(2),st) \
ASM( fld qword ptr [edx+0x50]) \
ASM( fmulp st(3),st) \
ASM( fld qword ptr [edx+0x70]) \
ASM( fmulp st(4),st) \
ASM( faddp st(1),st) \
ASM( faddp st(1),st) \
ASM( faddp st(1),st) \
ASM( fstp qword ptr [ecx+0x10]) \
END_ASM

/*/// Умножение четырехмерного вектора на матрицу трансформации двойной точности, команды SSE2
#define VECTORP4DDTRANSFORMSSE2 \
BEGIN_ASM \
_ASM movsd xmm0,[eax] \
_ASM movsd xmm1,[eax+8] \
_ASM movsd xmm2,[eax+0x10] \
_ASM movsd xmm3,[eax+0x18] \
_ASM unpcklpd xmm0,xmm0 \
_ASM movups xmm4,[edx] \
_ASM unpcklpd xmm1,xmm1 \
_ASM unpcklpd xmm2,xmm2 \
_ASM unpcklpd xmm3,xmm3 \
_ASM movups xmm5,[edx+20h] \
_ASM mulpd xmm4,xmm0 \
_ASM mulpd xmm5,xmm1 \
_ASM movups xmm6,[edx+40h] \
_ASM addpd xmm4,xmm5 \
_ASM mulpd xmm6,xmm2 \
_ASM movups xmm7,[edx+60h] \
_ASM addpd xmm4,xmm6 \
_ASM mulpd xmm7,xmm3 \
_ASM addpd xmm4,xmm7 \
_ASM movsd [ecx],xmm4 \
_ASM movups xmm6,[edx+10h] \
_ASM unpckhpd xmm4,xmm4 \
_ASM movups xmm7,[edx+30h] \
_ASM movsd [ecx+8],xmm4 \
_ASM mulpd xmm6,xmm0 \
_ASM mulpd xmm7,xmm1 \
_ASM movups xmm4,[edx+50h] \
_ASM addpd xmm6,xmm7 \
_ASM mulpd xmm4,xmm2 \
_ASM movups xmm5,[edx+70h] \
_ASM addpd xmm6,xmm4 \
_ASM mulpd xmm5,xmm3 \
_ASM addpd xmm6,xmm5 \
_ASM movups [ecx+10h],xmm6 \
END_ASM

/// Умножение четырехмерного вектора на матрицу трансформации двойной точности, команды SSE3
#define VECTORP4DDTRANSFORMSSE3 \
BEGIN_ASM \
_ASM movddup xmm0,[eax] \
_ASM movddup xmm1,[eax+8] \
_ASM movddup xmm2,[eax+0x10] \
_ASM movddup xmm3,[eax+0x18] \
_ASM movlpd xmm4,[edx] \
_ASM movhpd xmm4,[edx+8] \
_ASM movlpd xmm5,[edx+20h] \
_ASM movhpd xmm5,[edx+28h] \
_ASM mulpd xmm4,xmm0 \
_ASM mulpd xmm5,xmm1 \
_ASM movlpd xmm6,[edx+40h] \
_ASM movhpd xmm6,[edx+48h] \
_ASM addpd xmm4,xmm5 \
_ASM mulpd xmm6,xmm2 \
_ASM movlpd xmm7,[edx+60h] \
_ASM movhpd xmm7,[edx+68h] \
_ASM addpd xmm4,xmm6 \
_ASM mulpd xmm7,xmm3 \
_ASM addpd xmm4,xmm7 \
_ASM movlpd [ecx+00],xmm4 \
_ASM movhpd [ecx+0x08],xmm4 \
_ASM movlpd xmm4,[edx+10h] \
_ASM movhpd xmm4,[edx+18h] \
_ASM movlpd xmm5,[edx+30h] \
_ASM movhpd xmm5,[edx+38h] \
_ASM mulpd xmm4,xmm0 \
_ASM mulpd xmm5,xmm1 \
_ASM movlpd xmm6,[edx+50h] \
_ASM movhpd xmm6,[edx+58h] \
_ASM addpd xmm4,xmm5 \
_ASM mulpd xmm6,xmm2 \
_ASM movlpd xmm7,[edx+70h] \
_ASM movhpd xmm7,[edx+78h] \
_ASM addpd xmm4,xmm6 \
_ASM mulpd xmm7,xmm3 \
_ASM addpd xmm4,xmm7 \
_ASM movlpd [ecx+10h],xmm4 \
_ASM movhpd [ecx+18h],xmm4 \
END_ASM
*/

#endif