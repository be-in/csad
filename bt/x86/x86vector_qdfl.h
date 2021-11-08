//=============================================================================
///**
// *  @file   vector_qdfl.h
// *
// *  $Id: vector_qdfl.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float quad distance from line, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_VECTOR_QDFL_H_
#define GEN3_VECTOR_QDFL_H_

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** QDFL STDCALL *********************************
// quad distance from line vectors eax=[esp+4]-a void *, edx=[esp+8]-b void *, ecx=[esp+12]-c void *, rez fpu

/// Квадрат расстояния от точки до прямой одинарной точности, команды SSE3
#define VECTORP2DQDFLSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,mmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE4( 0xF2,0x0F,0x10,0x11 )                               /* movsd       xmm2,xmmword ptr [ecx]  */ \
_LINE3( 0x0F,0x5C,0xD1 )                                    /* subps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x5C,0xC1 )                                    /* subps       xmm0,xmm1  */ \
_LINE4( 0x0F,0xC6,0xD2,0xF1 )                               /* shufps      xmm2,xmm2,0F1h  */ \
_LINE3( 0x0F,0x59,0xC2 )                                    /* mulps       xmm0,xmm2  */ \
_LINE4( 0xF2,0x0F,0x7D,0xC0 )                               /* hsubps      xmm0,xmm0  */ \
_LINE6( 0xF3,0x0F,0x11,0x44,0x24,0xDC )                     /* movss       dword ptr [esp-24h],xmm0  */ \
_LINE4( 0xD9,0x44,0x24,0xDC )                               /* fld         dword ptr [esp-24h]  */ \
_END_ASM

/// Квадрат расстояния от точки до прямой двойной точности, команды SSE3
#define VECTORP2DDQDFLSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x11 )                               /* lddqu       xmm2,xmmword ptr [ecx]  */ \
_LINE4( 0x66,0x0F,0x5C,0xD1 )                               /* subpd       xmm2,xmm1  */ \
_LINE4( 0x66,0x0F,0x5C,0xC1 )                               /* subpd       xmm0,xmm1  */ \
_LINE5( 0x66,0x0F,0xC6,0xD2,0x01 )                          /* shufpd      xmm2,xmm2,1  */ \
_LINE4( 0x66,0x0F,0x59,0xC2 )                               /* mulpd       xmm0,xmm2  */ \
_LINE4( 0x66,0x0F,0x7D,0xC0 )                               /* hsubpd      xmm0,xmm0  */ \
_LINE6( 0xF2,0x0F,0x11,0x44,0x24,0xDC )                     /* movsd       mmword ptr [esp-24h],xmm0  */ \
_LINE4( 0xDD,0x44,0x24,0xDC )                               /* fld         qword ptr [esp-24h]  */ \
_END_ASM

#endif /* X86VECTOR_QDFL_H_ */
