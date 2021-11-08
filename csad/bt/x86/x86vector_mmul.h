//=============================================================================
///**
// *  @file vector_mmul.h
// *
// *  $Id: vector_mmul.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float mmul, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef X86VECTOR_MMUL_H_
#define X86VECTOR_MMUL_H_

//**************************** MMUL STDCALL *********************************
// vector mul matrix eax=[esp+4]-a void *, edx=[esp+8]-b void *, ecx=[esp+12]-rez void *

/// Умножение двухмерного вектора на матрицу одинарной точности, команды FPU
#define VECTORP2DMMULFPU_STD \
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
 _STR(_DB(0xD9) _DB(0x1A))                                   /* fstp        dword ptr [edx] */ \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x04))                         /* fld         dword ptr [eax+4] */ \
 _STR(_DB(0xDE) _DB(0xC9))                                   /* fmulp       st(1), st */ \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x14))                         /* fld         dword ptr [eax+14h] */ \
 _STR(_DB(0xDE) _DB(0xCA))                                   /* fmulp       st(2), st */ \
 _STR(_DB(0xDE) _DB(0xC1))                                   /* faddp       st(1), st */ \
 _STR(_DB(0xD9) _DB(0x5A) _DB(0x04))                         /* fstp        dword ptr [edx+4] */ \
_END_ASM

/// Умножение двухмерного вектора на матрицу одинарной точности, команды SSE
#define VECTORP2DMMULSSE_STD \
_BEGIN_ASM \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x08))               /* mov         eax,dword ptr [esp+8] */ \
ASM( xorps xmm4,xmm4 ) \
ASM( xorps xmm5,xmm5 ) \
ASM( xorps xmm7,xmm7 ) \
_LINE3( 0x0F,0x12,0x20 )                                    /* movlps      xmm4,qword ptr [eax]  */ \
_LINE4( 0x0F,0x12,0x68,0x10 )                               /* movlps      xmm5,qword ptr [eax+10h]  */ \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x04))               /* mov         eax,dword ptr [esp+04h] */ \
_LINE4( 0xF3,0x0F,0x10,0x10 )                               /* movss       xmm2,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x50 )                               /* shufps      xmm2,xmm2,0x50  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x50 )                               /* shufps      xmm1,xmm1,0x50  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x0C))               /* mov         eax,dword ptr [esp+0Ch] */ \
_LINE3( 0x0F,0x13,0x10 )                                    /* movlps      qword ptr [eax],xmm2  */ \
_END_ASM

/// Умножение трехмерного вектора на матрицу одинарной точности, команды SSE
#define VECTORP3DMMULSSE_STD \
_BEGIN_ASM \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x08))               /* mov         eax,dword ptr [esp+8] */ \
_LINE3( 0x0F,0x12,0x20 )                                    /* movlps      xmm4,qword ptr [eax]  */ \
_LINE4( 0x0F,0x16,0x60,0x08 )                               /* movhps      xmm4,qword ptr [eax+8]  */ \
_LINE4( 0x0F,0x12,0x68,0x10 )                               /* movlps      xmm5,qword ptr [eax+10h]  */ \
_LINE4( 0x0F,0x16,0x68,0x18 )                               /* movhps      xmm5,qword ptr [eax+18h]  */ \
_LINE4( 0x0F,0x12,0x70,0x20 )                               /* movlps      xmm6,qword ptr [eax+20h]  */ \
_LINE4( 0x0F,0x16,0x70,0x28 )                               /* movhps      xmm6,qword ptr [eax+28h]  */ \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x04))               /* mov         eax,dword ptr [esp+04h] */ \
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
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x0C))               /* mov         eax,dword ptr [esp+0Ch] */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x13,0x10 )                                    /* movlps      qword ptr [eax],xmm2  */ \
_LINE3( 0x0F,0x15,0xD2 )                                    /* unpckhps    xmm2,xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x50,0x08 )                          /* movss       dword ptr [eax+8],xmm2 */ \
_END_ASM

/// Умножение трехмерного вектора на матрицу одинарной точности, команды SSE3
#define VECTORP3DMMULSSE3_STD \
_BEGIN_ASM \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x08))               /* mov         eax,dword ptr [esp+8] */ \
_LINE4( 0xF2,0x0F,0xF0,0x20 )                               /* lddqu       xmm4,[eax]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x68,0x10 )                          /* lddqu       xmm5,[eax+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x70,0x20 )                          /* lddqu       xmm6,[eax+20h]  */ \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x04))               /* mov         eax,dword ptr [esp+04h] */ \
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
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x0C))               /* mov         eax,dword ptr [esp+0Ch] */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x13,0x10 )                                    /* movlps      qword ptr [eax],xmm2  */ \
_LINE3( 0x0F,0x15,0xD2 )                                    /* unpckhps    xmm2,xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x50,0x08 )                          /* movss       dword ptr [eax+8],xmm2  */ \
_END_ASM

#endif /* X86VECTOR_MMUL_H_ */