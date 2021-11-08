//=============================================================================
///**
// *  @file vector_mul.h
// *
// *  $Id: vector_mul.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float mul, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

//**************************** MUL STDCALL *********************************
// mul vectors eax=[esp+4]-a void *, edx=[esp+8]-b void *, ecx=[esp+12]-rez void *

/// Поэлементное умножение двухмерных векторов одинарной точности, команды FPU.
#define VECTORP2DMULFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_STR(_DB(0xD9) _DB(0x00)) \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_STR(_DB(0xD8) _DB(0x0A)) \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_STR(_DB(0xD9) _DB(0x19)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
_STR(_DB(0xD8) _DB(0x4A) _DB(0x04)) \
_STR(_DB(0xD9) _DB(0x59) _DB(0x04)) \
_END_ASM

/// Поэлементное умножение трехмерных векторов одинарной точности, команды SSE.
#define VECTORP2DMULSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
ASM( xorps xmm0,xmm0 ) \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
ASM( xorps xmm1,xmm1 ) \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x16,0x00 )                                    /* movhps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x16,0x0A )                                    /* movhps      xmm1,qword ptr [edx]  */ \
_LINE3( 0x0F,0x59,0xC1 )                                    /* mulps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x17,0x01 )                                    /* movhps      qword ptr [ecx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x41,0x08 )                          /* movss       dword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Поэлементное умножение трехмерных векторов одинарной точности, команды FPU.
#define VECTORP3DMULFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_STR(_DB(0xD9) _DB(0x00)) \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_STR(_DB(0xD8) _DB(0x0A)) \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_STR(_DB(0xD9) _DB(0x19)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
_STR(_DB(0xD8) _DB(0x4A) _DB(0x04)) \
_STR(_DB(0xD9) _DB(0x59) _DB(0x04)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x08)) \
_STR(_DB(0xD8) _DB(0x4A) _DB(0x08)) \
_STR(_DB(0xD9) _DB(0x59) _DB(0x08)) \
_END_ASM

/// Поэлементное умножение трехмерных векторов одинарной точности, команды SSE.
#define VECTORP3DMULSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE3( 0x0F,0x16,0x00 )                                    /* movhps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x16,0x0A )                                    /* movhps      xmm1,qword ptr [edx]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x59,0xC1 )                                    /* mulps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x17,0x00 )                                    /* movhps      qword ptr [eax],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x40,0x08 )                          /* movss       dword ptr [eax+8],xmm0  */ \
_END_ASM

/// Поэлементное умножение четырехмерных векторов одинарной точности, команды FPU.
#define VECTORP4DMULFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_STR(_DB(0xD9) _DB(0x00)) \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_STR(_DB(0xD8) _DB(0x0A)) \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_STR(_DB(0xD9) _DB(0x19)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
_STR(_DB(0xD8) _DB(0x4A) _DB(0x04)) \
_STR(_DB(0xD9) _DB(0x59) _DB(0x04)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x08)) \
_STR(_DB(0xD8) _DB(0x4A) _DB(0x08)) \
_STR(_DB(0xD9) _DB(0x59) _DB(0x08)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x0C)) \
_STR(_DB(0xD8) _DB(0x4A) _DB(0x0C)) \
_STR(_DB(0xD9) _DB(0x59) _DB(0x0C)) \
_END_ASM

/// Поэлементное умножение четырехмерных векторов одинарной точности, команды SSE.
#define VECTORP4DMULSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE3( 0x0F,0x10,0x00 )                                    /* movups      xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x10,0x0A )                                    /* movups      xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x59,0xC1 )                                    /* mulps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x11,0x01 )                                    /* movups      xmmword ptr [ecx],xmm0  */ \
_END_ASM

/// Поэлементное умножение двухмерных векторов двойной точности, команды FPU.
#define VECTORP2DDMULFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_STR(_DB(0xDD) _DB(0x00)) \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_STR(_DB(0xDC) _DB(0x0A)) \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_STR(_DB(0xDD) _DB(0x19)) \
_STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
_STR(_DB(0xDC) _DB(0x4A) _DB(0x08)) \
_STR(_DB(0xDD) _DB(0x59) _DB(0x08)) \
_END_ASM

/// Поэлементное умножение двухмерных векторов двойной точности, команды SSE2.
#define VECTORP2DDMULSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE3(0x0F,0x10,0x00) \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3(0x0F,0x10,0x0A) \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE4(0x66,0x0F,0x59,0xC1) \
_LINE3(0x0F,0x11,0x01) \
_END_ASM

/// Поэлементное умножение трехмерных векторов двойной точности, команды FPU.
#define VECTORP3DDMULFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_STR(_DB(0xDD) _DB(0x00)) \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_STR(_DB(0xDC) _DB(0x0A)) \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_STR(_DB(0xDD) _DB(0x19)) \
_STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
_STR(_DB(0xDC) _DB(0x4A) _DB(0x08)) \
_STR(_DB(0xDD) _DB(0x59) _DB(0x08)) \
_STR(_DB(0xDD) _DB(0x40) _DB(0x10)) \
_STR(_DB(0xDC) _DB(0x4A) _DB(0x10)) \
_STR(_DB(0xDD) _DB(0x59) _DB(0x10)) \
_END_ASM

/// Поэлементное умножение трехмерных векторов двойной точности, команды SSE2.
#define VECTORP3DDMULSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x08 )                          /* movsd       xmm1,mmword ptr [eax+8]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE4( 0xF2,0x0F,0x10,0x22 )                               /* movsd       xmm4,mmword ptr [edx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x6A,0x08 )                          /* movsd       xmm5,mmword ptr [edx+8]  */ \
_LINE4( 0x66,0x0F,0x14,0xC1 )                               /* unpcklpd    xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x14,0xE5 )                               /* unpcklpd    xmm4,xmm5  */ \
_LINE4( 0x66,0x0F,0x59,0xC4 )                               /* mulpd       xmm0,xmm4  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x59,0x52,0x10 )                          /* mulsd       xmm2,mmword ptr [edx+10h]  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Поэлементное умножение трехмерных векторов двойной точности, команды SSE3.
#define VECTORP3DDMULSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x22 )                               /* lddqu       xmm4,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE4( 0x66,0x0F,0x59,0xC4 )                               /* mulpd       xmm0,xmm4  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x59,0x52,0x10 )                          /* mulsd       xmm2,mmword ptr [edx+10h]  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Поэлементное умножение четырехмерных векторов двойной точности, команды FPU.
#define VECTORP4DDMULFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_STR(_DB(0xDD) _DB(0x00)) \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_STR(_DB(0xDC) _DB(0x0A)) \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_STR(_DB(0xDD) _DB(0x19)) \
_STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
_STR(_DB(0xDC) _DB(0x4A) _DB(0x08)) \
_STR(_DB(0xDD) _DB(0x59) _DB(0x08)) \
_STR(_DB(0xDD) _DB(0x40) _DB(0x10)) \
_STR(_DB(0xDC) _DB(0x4A) _DB(0x10)) \
_STR(_DB(0xDD) _DB(0x59) _DB(0x10)) \
_STR(_DB(0xDD) _DB(0x40) _DB(0x18)) \
_STR(_DB(0xDC) _DB(0x4A) _DB(0x18)) \
_STR(_DB(0xDD) _DB(0x59) _DB(0x18)) \
_END_ASM

/// Поэлементное умножение четырехмерных векторов двойной точности, команды SSE2.
#define VECTORP4DDMULSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x08 )                          /* movsd       xmm1,mmword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE5( 0xF2,0x0F,0x10,0x58,0x18 )                          /* movsd       xmm3,mmword ptr [eax+18h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE4( 0x66,0x0F,0x14,0xC1 )                               /* unpcklpd    xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x14,0xD3 )                               /* unpcklpd    xmm2,xmm3  */ \
_LINE5( 0xF2,0x0F,0x10,0x6A,0x08 )                          /* movsd       xmm5,mmword ptr [edx+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x22 )                               /* movsd       xmm4,mmword ptr [edx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x7A,0x18 )                          /* movsd       xmm7,mmword ptr [edx+18h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x72,0x10 )                          /* movsd       xmm6,mmword ptr [edx+10h]  */ \
_LINE4( 0x66,0x0F,0x14,0xE5 )                               /* unpcklpd    xmm4,xmm5  */ \
_LINE4( 0x66,0x0F,0x14,0xF7 )                               /* unpcklpd    xmm6,xmm7  */ \
_LINE4( 0x66,0x0F,0x59,0xC4 )                               /* mulpd       xmm0,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xD6 )                               /* mulpd       xmm2,xmm6  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xD2 )                               /* unpckhpd    xmm2,xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x18 )                          /* movsd       mmword ptr [ecx+18h],xmm2  */ \
_END_ASM

/// Поэлементное умножение четырехмерных векторов двойной точности, команды SSE4.
/// @brief for CPUTYPE4
#define VECTORP4DDMULSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )          /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )          /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )          /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )          /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )          /* mov         ecx,dword ptr [esp+12]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x50,0x10 )     /* lddqu       xmm2,xmmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x5A,0x10 )     /* lddqu       xmm3,xmmword ptr [edx+10h]  */ \
_LINE4( 0x66,0x0F,0x59,0xC1 )          /* mulpd       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x59,0xD3 )          /* mulpd       xmm2,xmm3  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )          /* movupd      xmmword ptr [ecx],xmm0  */ \
_LINE5( 0x66,0x0F,0x11,0x51,0x10 )     /* movupd      xmmword ptr [ecx+10h],xmm2  */ \
_END_ASM

/// Поэлементное умножение четырехмерных векторов двойной точности, команды AVX
#define VECTORP4DDMULAVX_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )         /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xC5,0xFD,0x10,0x00 )         /* vmovupd     ymm0,ymmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )         /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xC5,0xFD,0x10,0x0A )         /* vmovupd     ymm1,ymmword ptr [edx]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )         /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE4( 0xC5,0xFD,0x59,0xD9 )         /* vmulpd      ymm3,ymm0,ymm1  */ \
_LINE4( 0xC5,0xFD,0x11,0x18 )         /* vmovupd     ymmword ptr [eax],ymm3  */ \
_LINE3( 0xC5,0xF8,0x77 )               /* vzeroupper  */ \
_END_ASM

//**************************** MUL REGISTER FASTCALL *********************************
// addition vectors eax-a void *, edx-b void *, ecx-rez void *

/// Поэлементное умножение двухмерных векторов одинарной точности, команды FPU.
#define VECTORP2DMULFPU \
_BEGIN_ASM \
_STR(_DB(0xD9) _DB(0x00)) \
_STR(_DB(0xD8) _DB(0x0A)) \
_STR(_DB(0xD9) _DB(0x19)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
_STR(_DB(0xD8) _DB(0x4A) _DB(0x04)) \
_STR(_DB(0xD9) _DB(0x59) _DB(0x04)) \
_END_ASM

/// Поэлементное умножение трехмерных векторов одинарной точности, команды FPU.
#define VECTORP3DMULFPU \
_BEGIN_ASM \
_STR(_DB(0xD9) _DB(0x00)) \
_STR(_DB(0xD8) _DB(0x0A)) \
_STR(_DB(0xD9) _DB(0x19)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
_STR(_DB(0xD8) _DB(0x4A) _DB(0x04)) \
_STR(_DB(0xD9) _DB(0x59) _DB(0x04)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x08)) \
_STR(_DB(0xD8) _DB(0x4A) _DB(0x08)) \
_STR(_DB(0xD9) _DB(0x59) _DB(0x08)) \
_END_ASM

/// Поэлементное умножение трехмерных векторов одинарной точности, команды SSE.
#define VECTORP3DMULSSE \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE3( 0x0F,0x16,0x00 )                                    /* movhps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x16,0x0A )                                    /* movhps      xmm1,qword ptr [edx]  */ \
_LINE3( 0x0F,0x59,0xC1 )                                    /* mulps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x17,0x01 )                                    /* movhps      qword ptr [ecx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x41,0x08 )                          /* movss       dword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Поэлементное умножение четырехмерных векторов одинарной точности, команды FPU.
#define VECTORP4DMULFPU \
_BEGIN_ASM \
_STR(_DB(0xD9) _DB(0x00)) \
_STR(_DB(0xD8) _DB(0x0A)) \
_STR(_DB(0xD9) _DB(0x19)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
_STR(_DB(0xD8) _DB(0x4A) _DB(0x04)) \
_STR(_DB(0xD9) _DB(0x59) _DB(0x04)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x08)) \
_STR(_DB(0xD8) _DB(0x4A) _DB(0x08)) \
_STR(_DB(0xD9) _DB(0x59) _DB(0x08)) \
_STR(_DB(0xD9) _DB(0x40) _DB(0x0C)) \
_STR(_DB(0xD8) _DB(0x4A) _DB(0x0C)) \
_STR(_DB(0xD9) _DB(0x59) _DB(0x0C)) \
_END_ASM

/// Поэлементное умножение четырехмерных векторов одинарной точности, команды SSE.
#define VECTORP4DMULSSE \
_BEGIN_ASM \
_STR(_DB(0x0F) _DB(0x10) _DB(0x00)) \
_STR(_DB(0x0F) _DB(0x10) _DB(0x0A)) \
_STR(_DB(0x0F) _DB(0x59) _DB(0xC1)) \
_STR(_DB(0x0F) _DB(0x11) _DB(0x01)) \
_END_ASM

/// Поэлементное умножение двухмерных векторов двойной точности, команды FPU.
#define VECTORP2DDMULFPU \
_BEGIN_ASM \
_STR(_DB(0xDD) _DB(0x00)) \
_STR(_DB(0xDC) _DB(0x0A)) \
_STR(_DB(0xDD) _DB(0x19)) \
_STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
_STR(_DB(0xDC) _DB(0x4A) _DB(0x08)) \
_STR(_DB(0xDD) _DB(0x59) _DB(0x08)) \
_END_ASM

/// Поэлементное умножение двухмерных векторов двойной точности, команды SSE2.
#define VECTORP2DDMULSSE2 \
_BEGIN_ASM \
_LINE3(0x0F,0x10,0x00) \
_LINE3(0x0F,0x10,0x0A) \
_LINE4(0x66,0x0F,0x59,0xC1) \
_LINE3(0x0F,0x11,0x01) \
_END_ASM

/// Поэлементное умножение трехмерных векторов двойной точности, команды FPU.
#define VECTORP3DDMULFPU \
_BEGIN_ASM \
_STR(_DB(0xDD) _DB(0x00)) \
_STR(_DB(0xDC) _DB(0x0A)) \
_STR(_DB(0xDD) _DB(0x19)) \
_STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
_STR(_DB(0xDC) _DB(0x4A) _DB(0x08)) \
_STR(_DB(0xDD) _DB(0x59) _DB(0x08)) \
_STR(_DB(0xDD) _DB(0x40) _DB(0x10)) \
_STR(_DB(0xDC) _DB(0x4A) _DB(0x10)) \
_STR(_DB(0xDD) _DB(0x59) _DB(0x10)) \
_END_ASM

/// Поэлементное умножение трехмерных векторов двойной точности, команды SSE2.
#define VECTORP3DDMULSSE2 \
BEGIN_ASM \
_ASM movsd xmm0,[eax] \
_ASM movsd xmm1,[eax+8] \
_ASM movsd xmm4,[edx] \
_ASM movsd xmm5,[edx+8] \
_ASM unpcklpd xmm0,xmm1 \
_ASM unpcklpd xmm4,xmm5 \
_ASM mulpd xmm0,xmm4 \
_ASM movsd xmm2,[eax+16] \
_ASM movsd [ecx],xmm0 \
_ASM mulsd xmm2,[edx+16] \
_ASM unpckhpd xmm0,xmm0 \
_ASM movsd [ecx+16],xmm2 \
_ASM movsd [ecx+8],xmm0 \
END_ASM

/// Поэлементное умножение трехмерных векторов двойной точности, команды SSE3.
#define VECTORP3DDMULSSE3 \
BEGIN_ASM \
_ASM lddqu xmm0,[eax] \
_ASM lddqu xmm4,[edx] \
_ASM mulpd xmm0,xmm4 \
_ASM movsd xmm2,[eax+16] \
_ASM movsd [ecx],xmm0 \
_ASM mulsd xmm2,[edx+16] \
_ASM unpckhpd xmm0,xmm0 \
_ASM movsd [ecx+16],xmm2 \
_ASM movsd [ecx+8],xmm0 \
END_ASM

/// Поэлементное умножение четырехмерных векторов двойной точности, команды FPU.
#define VECTORP4DDMULFPU \
_BEGIN_ASM \
_STR(_DB(0xDD) _DB(0x00)) \
_STR(_DB(0xDC) _DB(0x0A)) \
_STR(_DB(0xDD) _DB(0x19)) \
_STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
_STR(_DB(0xDC) _DB(0x4A) _DB(0x08)) \
_STR(_DB(0xDD) _DB(0x59) _DB(0x08)) \
_STR(_DB(0xDD) _DB(0x40) _DB(0x10)) \
_STR(_DB(0xDC) _DB(0x4A) _DB(0x10)) \
_STR(_DB(0xDD) _DB(0x59) _DB(0x10)) \
_STR(_DB(0xDD) _DB(0x40) _DB(0x18)) \
_STR(_DB(0xDC) _DB(0x4A) _DB(0x18)) \
_STR(_DB(0xDD) _DB(0x59) _DB(0x18)) \
_END_ASM

/// Поэлементное умножение четырехмерных векторов двойной точности, команды SSE2.
#define VECTORP4DDMULSSE2 \
BEGIN_ASM \
_ASM movsd xmm1,[eax+8] \
_ASM movsd xmm0,[eax] \
_ASM movsd xmm3,[eax+24] \
_ASM movsd xmm2,[eax+16] \
_ASM unpcklpd xmm0,xmm1 \
_ASM unpcklpd xmm2,xmm3 \
_ASM movsd xmm5,[edx+8] \
_ASM movsd xmm4,[edx] \
_ASM movsd xmm7,[edx+24] \
_ASM movsd xmm6,[edx+16] \
_ASM unpcklpd xmm4,xmm5 \
_ASM unpcklpd xmm6,xmm7 \
_ASM mulpd xmm0,xmm4 \
_ASM mulpd xmm2,xmm6 \
_ASM movsd [ecx],xmm0 \
_ASM movsd [ecx+16],xmm2 \
_ASM unpckhpd xmm0,xmm0 \
_ASM unpckhpd xmm2,xmm2 \
_ASM movsd [ecx+8],xmm0 \
_ASM movsd [ecx+24],xmm2 \
END_ASM
