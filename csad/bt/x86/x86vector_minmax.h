//=============================================================================
///**
// *  @file vector_minmax.h
// *
// *  $Id: vector_add.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float min max, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_VECTOR_MIN_MAX_H
#define GEN3_VECTOR_MIN_MAX_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** MIN MAX STDCALL *********************************
// absolute vectors eax=[esp+4]-a void *, edx=[esp+8]-b void *

/// ћинимум и мачимум между 3 векторами, команды SSE2
#define VECTORP2DMINMAXSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,mmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE4( 0xF2,0x0F,0x10,0x11 )                               /* movsd       xmm2,mmword ptr [ecx]  */ \
ASM( minps xmm1,xmm0 ) \
ASM( maxps xmm2,xmm0 ) \
_LINE4( 0xF2,0x0F,0x11,0x0A )                               /* movsd       mmword ptr [edx],xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x11 )                               /* movsd       mmword ptr [ecx],xmm2  */ \
_END_ASM

/// ћинимум и мачимум между 3 векторами, команды SSE2
#define VECTORP3DMINMAXSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE4( 0x66,0x0F,0x16,0x00 )                               /* movhpd      xmm0,qword ptr [eax]  */ \
_LINE4( 0x66,0x0F,0x16,0x0A )                               /* movhpd      xmm1,qword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE5( 0xF3,0x0F,0x10,0x51,0x08 )                          /* movss       xmm2,dword ptr [ecx+8]  */ \
_LINE4( 0x66,0x0F,0x16,0x11 )                               /* movhpd      xmm2,qword ptr [ecx]  */ \
ASM( minps xmm1,xmm0 ) \
ASM( maxps xmm2,xmm0 ) \
_LINE4( 0x66,0x0F,0x17,0x0A )                               /* movhpd      qword ptr [edx],xmm1  */ \
_LINE5( 0xF3,0x0F,0x11,0x5A,0x08 )                          /* movss       dword ptr [edx+8],xmm1  */ \
_LINE4( 0x66,0x0F,0x17,0x11 )                               /* movhpd      qword ptr [ecx],xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x51,0x08 )                          /* movss       dword ptr [ecx+8],xmm2  */ \
_END_ASM

/// ћинимум и мачимум между 3 векторами, команды SSE2
#define VECTORP4DMINMAXSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )                               /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x16,0x4A,0x08 )                               /* movhps      xmm1,qword ptr [edx+8]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x12,0x00 )                                    /* movlps      xmm0,qword ptr [eax]  */ \
_LINE4( 0x0F,0x16,0x51,0x08 )                               /* movhps      xmm2,qword ptr [ecx+8]  */ \
_LINE3( 0x0F,0x12,0x0A )                                    /* movlps      xmm1,qword ptr [edx]  */ \
_LINE3( 0x0F,0x12,0x11 )                                    /* movlps      xmm2,qword ptr [ecx]  */ \
ASM( minps xmm1,xmm0 ) \
ASM( maxps xmm2,xmm0 ) \
_LINE3( 0x0F,0x13,0x0A )                                    /* movlps      qword ptr [edx],xmm1  */ \
_LINE4( 0x0F,0x17,0x4A,0x08 )                               /* movhps      qword ptr [edx+8],xmm1 */ \
_LINE3( 0x0F,0x13,0x11 )                                    /* movlps      qword ptr [ecx],xmm2  */ \
_LINE4( 0x0F,0x17,0x51,0x08 )                               /* movhps      qword ptr [ecx+8],xmm2 */ \
_END_ASM

/// ћинимум и мачимум между 3 векторами, команды SSE4
#define VECTORP4DMINMAXSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x11 )                               /* lddqu       xmm2,xmmword ptr [ecx]  */ \
ASM( minps xmm1,xmm0 ) \
ASM( maxps xmm2,xmm0 ) \
_LINE4( 0x66,0x0F,0x11,0x0A )                               /* movupd      xmmword ptr [edx],xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x11 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_END_ASM

/// ћинимум и мачимум между 3 векторами, команды SSE2
#define VECTORP2DDMINMAXSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x08 )                          /* movsd       xmm1,mmword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE4( 0xF2,0x0F,0x10,0x12 )                               /* movsd       xmm2,mmword ptr [edx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x5A,0x08 )                          /* movsd       xmm3,mmword ptr [edx+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x21 )                               /* movsd       xmm4,mmword ptr [ecx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x69,0x08 )                          /* movsd       xmm5,mmword ptr [ecx+8]  */ \
ASM( minsd xmm2,xmm0 ) \
ASM( minsd xmm3,xmm1 ) \
ASM( maxsd xmm4,xmm0 ) \
ASM( maxsd xmm5,xmm1 ) \
_LINE4( 0xF2,0x0F,0x11,0x12 )                               /* movsd       mmword ptr [ecx],xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x5A,0x08 )                          /* movsd       mmword ptr [edx+8h],xmm3  */ \
_LINE4( 0xF2,0x0F,0x11,0x21 )                               /* movsd       mmword ptr [ecx],xmm4  */ \
_LINE5( 0xF2,0x0F,0x11,0x69,0x08 )                          /* movsd       mmword ptr [ecx+8h],xmm5  */ \
_END_ASM

/// ћинимум и мачимум между 3 векторами, команды SSE4
#define VECTORP2DDMINMAXSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x21 )                               /* lddqu       xmm4,xmmword ptr [ecx]  */ \
ASM( minpd xmm1,xmm0 ) \
ASM( maxpd xmm4,xmm0 ) \
_LINE4( 0x66,0x0F,0x11,0x0A )                               /* movupd      xmmword ptr [edx],xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x21 )                               /* movupd      xmmword ptr [ecx],xmm4  */ \
_END_ASM

/// ћинимум и мачимум между 3 векторами, команды SSE2
#define VECTORP3DDMINMAXSSE2_STD \
_BEGIN_ASM \
_END_ASM

/// ћинимум и мачимум между 3 векторами, команды SSE4
#define VECTORP3DDMINMAXSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x21 )                               /* lddqu       xmm4,xmmword ptr [ecx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x5A,0x10 )                          /* movsd       xmm3,mmword ptr [edx+10h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x69,0x10 )                          /* movsd       xmm5,mmword ptr [ecx+10h]  */ \
ASM( minpd xmm1,xmm0 ) \
ASM( minsd xmm3,xmm2 ) \
ASM( maxpd xmm4,xmm0 ) \
ASM( maxsd xmm5,xmm2 ) \
_LINE4( 0x66,0x0F,0x11,0x0A )                               /* movupd      xmmword ptr [edx],xmm1  */ \
_LINE5( 0xF2,0x0F,0x11,0x5A,0x10 )                          /* movsd       mmword ptr [edx+10h],xmm3  */ \
_LINE4( 0x66,0x0F,0x11,0x21 )                               /* movupd      xmmword ptr [ecx],xmm4  */ \
_LINE5( 0xF2,0x0F,0x11,0x69,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm5  */ \
_END_ASM

/// ћинимум и мачимум между 3 векторами, команды SSE2
#define VECTORP4DDMINMAXSSE2_STD \
_BEGIN_ASM \
_END_ASM

/// ћинимум и мачимум между 3 векторами, команды SSE4
#define VECTORP4DDMINMAXSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x50,0x10 )                          /* lddqu       xmm2,xmmword ptr [eax+10h]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x21 )                               /* lddqu       xmm4,xmmword ptr [ecx]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x5A,0x10 )                          /* lddqu       xmm3,xmmword ptr [edx+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x69,0x10 )                          /* lddqu       xmm5,xmmword ptr [ecx+10h]  */ \
ASM( minpd xmm1,xmm0 ) \
ASM( minpd xmm3,xmm2 ) \
ASM( maxpd xmm4,xmm0 ) \
ASM( maxpd xmm5,xmm2 ) \
_LINE4( 0x66,0x0F,0x11,0x0A )                               /* movupd      xmmword ptr [edx],xmm1  */ \
_LINE5( 0x66,0x0F,0x11,0x5A,0x10 )                          /* movupd      xmmword ptr [edx+10h],xmm3  */ \
_LINE4( 0x66,0x0F,0x11,0x21 )                               /* movupd      xmmword ptr [ecx],xmm4  */ \
_LINE5( 0x66,0x0F,0x11,0x69,0x10 )                          /* movupd      xmmword ptr [ecx+10h],xmm5  */ \
_END_ASM

/// ћинимум и мачимум между 3 векторами, команды AVX
#define VECTORP4DDMINMAXAVX_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )         /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xC5,0xFD,0x10,0x00 )         /* vmovupd     ymm0,ymmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )         /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xC5,0xFD,0x10,0x0A )         /* vmovupd     ymm1,ymmword ptr [edx]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )         /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE4( 0xC5,0xFD,0x10,0x10 )         /* vmovupd     ymm2,ymmword ptr [eax]  */ \
ASM( vminpd ymm1,ymm1,ymm0 ) \
ASM( vmaxpd ymm2,ymm2,ymm0 ) \
_LINE4( 0xC5,0xFD,0x11,0x0A )         /* vmovupd     ymmword ptr [edx],ymm1  */ \
_LINE4( 0xC5,0xFD,0x11,0x10 )         /* vmovupd     ymmword ptr [eax],ymm2  */ \
_LINE3( 0xC5,0xF8,0x77 )              /* vzeroupper  */ \
_END_ASM

#endif
