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

#ifndef CPU_X86_64
#define GEN3_VECTOR_ADD_H
#endif

#ifndef GEN3_VECTOR_ADD_H
#define GEN3_VECTOR_ADD_H

//**************************** ADD Microsoft x64 *********************************
// addition vectors rcx=a void *, rdx=b void *, r8=rez void *

/// Сложение двухмерных целочисленных векторов, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP2IADDSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,mmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
ASM( paddd xmm0,xmm1 )                                      /* paddd       xmm0,xmm1  */ \
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
ASM( paddd xmm0,xmm1 )                                      /* paddd       xmm0,xmm1  */ \
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
ASM( paddd xmm0,xmm1 )                                      /* paddd       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x01 )                                    /* movlps      qword ptr [ecx],xmm0  */ \
_LINE4( 0x0F,0x17,0x41,0x08 )                               /* movhps      qword ptr [ecx+8],xmm0 */ \
_END_ASM

/// Сложение двухмерных векторов одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP2DADDSSE_MC \
_BEGIN_ASM \
_LINE3( 0x0F,0x57,0xC0 )           /* xorps       xmm0,xmm0  */ \
_LINE3( 0x0F,0x28,0xC8 )           /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x12,0x09 )           /* movlps      xmm1,qword ptr [rcx]  */ \
_LINE3( 0x0F,0x12,0x02 )           /* movlps      xmm0,qword ptr [rdx]  */ \
_LINE3( 0x0F,0x58,0xC8 )           /* addps       xmm1,xmm0  */ \
_LINE4( 0x41,0x0F,0x13,0x08 )      /* movlps      qword ptr [r8],xmm1  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Сложение двухмерных векторов одинарной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP2DADDSSE2_MC \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x01 )                               /* movsd       xmm0,mmword ptr [rcx]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,mmword ptr [rdx]  */ \
_LINE3( 0x0F,0x58,0xC8 )                                    /* addps       xmm1,xmm0  */ \
_LINE4( 0x41,0x0F,0x13,0x08 )                               /* movlps      qword ptr [r8],xmm1  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Сложение трехмерных векторов одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP3DADDSSE_MC \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x49,0x08 )      /* movss       xmm1,dword ptr [rcx+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x42,0x08 )      /* movss       xmm0,dword ptr [rdx+8]  */ \
_LINE3( 0x0F,0x16,0x09 )                /* movhps      xmm1,qword ptr [rcx]  */ \
_LINE3( 0x0F,0x16,0x02 )                /* movhps      xmm0,qword ptr [rdx]  */ \
_LINE3( 0x0F,0x58,0xC8 )                /* addps       xmm1,xmm0  */ \
_LINE4( 0x41,0x0F,0x17,0x08 )           /* movhps      qword ptr [r8],xmm1  */ \
_LINE6( 0xF3,0x41,0x0F,0x11,0x48,0x08 ) /* movlps      qword ptr [r8+8],xmm1  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Сложение трехмерных векторов одинарной точности, команды SSE2. ???
/// @brief for CPUTYPE3
#define VECTORP3DADDSSE2_STD \
_BEGIN_ASM \
_LINE5( 0xF2,0x0F,0x10,0x42,0x10 )                          /* mmovsd       xmm0,mmword ptr [rdx+10h]  */ \
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

/// Сложение четырехмерных векторов одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP4DADDSSE_MC \
_BEGIN_ASM \
_LINE3( 0x0F,0x12,0x01 )                                    /* movlps      xmm0,qword ptr [rcx]  */ \
_LINE3( 0x0F,0x12,0x0A )                                    /* movlps      xmm1,qword ptr [rdx]  */ \
_LINE4( 0x0F,0x16,0x4A,0x08 )                               /* movhps      xmm1,qword ptr [rdx+8]  */ \
_LINE4( 0x0F,0x16,0x41,0x08 )                               /* movhps      xmm0,qword ptr [rcx+8]  */ \
_LINE3( 0x0F,0x58,0xC8 )                                    /* addps       xmm1,xmm0  */ \
_LINE4( 0x41,0x0F,0x13,0x08 )                               /* movlps      mmword ptr [r8],xmm1  */ \
_LINE5( 0x41,0x0F,0x17,0x48,0x08 )                          /* movhps      qword ptr [r8+8],xmm1  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Сложение четырехмерных векторов одинарной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP4DADDSSE2_MC \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x01 )                               /* movsd       xmm0,mmword ptr [rcx]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,mmword ptr [rdx]  */ \
_LINE4( 0x0F,0x16,0x4A,0x08 )                               /* movhps      xmm1,qword ptr [rdx+8]  */ \
_LINE4( 0x0F,0x16,0x41,0x08 )                               /* movhps      xmm0,qword ptr [rcx+8]  */ \
_LINE3( 0x0F,0x58,0xC8 )                                    /* addps       xmm1,xmm0  */ \
_LINE5( 0xF2,0x41,0x0F,0x11,0x08 )                          /* movsd       mmword ptr [r8],xmm1  */ \
_LINE5( 0x41,0x0F,0x17,0x48,0x08 )                          /* movhps      qword ptr [r8+8],xmm1  */ \
_LINE1( 0xC3 ) \
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

/// Сложение двухмерных векторов двойной точности, команды SSE2.
#define VECTORP2DDADDSSE2_MC \
_BEGIN_ASM \
_LINE4( 0x66,0x0F,0x10,0x09 )        /* movupd      xmm1,xmmword ptr [rcx]  */ \
_LINE4( 0x66,0x0F,0x10,0x02 )        /* movupd      xmm0,xmmword ptr [rdx]  */ \
_LINE4( 0x66,0x0F,0x58,0xC8 )        /* addpd       xmm1,xmm0  */ \
_LINE5( 0x66,0x41,0x0F,0x11,0x08 )   /* movupd      xmmword ptr [r8],xmm1  */ \
_LINE1( 0xC3 ) \
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

/// Сложение трехмерных векторов двойной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP3DDADDSSE2_MC \
_BEGIN_ASM \
_LINE5( 0xF2,0x0F,0x10,0x42,0x10 )                          /* movsd       xmm0,mmword ptr [rdx+10h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x51,0x10 )                          /* movsd       xmm2,mmword ptr [rcx+10h]  */ \
_LINE4( 0x66,0x0F,0x10,0x09 )                               /* movupd      xmm1,xmmword ptr [rcx]  */ \
_LINE4( 0xF2,0x0F,0x58,0xD0 )                               /* addsd       xmm2,xmm0  */ \
_LINE4( 0x66,0x0F,0x10,0x02 )                               /* movupd      xmm0,xmmword ptr [rdx]  */ \
_LINE4( 0x66,0x0F,0x58,0xC8 )                               /* addpd       xmm1,xmm0  */ \
_LINE5( 0x66,0x41,0x0F,0x11,0x08 )                          /* movupd      xmmword ptr [r8],xmm1  */ \
_LINE6( 0xF2,0x41,0x0F,0x11,0x50,0x10 )                     /* movsd       mmword ptr [r8+10h],xmm2  */ \
_LINE1( 0xC3 ) \
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

/// Сложение четырехмерных векторов двойной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP4DDADDSSE2_MC \
_BEGIN_ASM \
_LINE5( 0x66,0x0F,0x10,0x42,0x10 )       /* movupd      xmm0,xmmword ptr [rdx+0x10]  */ \
_LINE5( 0x66,0x0F,0x10,0x51,0x10 )       /* movupd      xmm2,xmmword ptr [rcx+0x10]  */ \
_LINE4( 0x66,0x0F,0x10,0x09 )            /* movupd      xmm1,xmmword ptr [rcx]  */ \
_LINE4( 0x66,0x0F,0x58,0xD0 )            /* addpd       xmm2,xmm0  */ \
_LINE4( 0x66,0x0F,0x10,0x02 )            /* movupd      xmm0,xmmword ptr [rdx]  */ \
_LINE4( 0x66,0x0F,0x58,0xC8 )            /* addpd       xmm1,xmm0  */ \
_LINE5( 0x66,0x41,0x0F,0x11,0x08 )       /* movupd      xmmword ptr [r8],xmm1  */ \
_LINE6( 0x66,0x41,0x0F,0x11,0x50,0x10 )  /* movupd      xmmword ptr [r8+0x10],xmm2  */ \
_LINE1( 0xC3 ) \
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
#define VECTORP4DDADDAVX_MC \
_BEGIN_ASM \
_LINE4 ( 0xC5,0xFD,0x10,0x02 )         /* vmovupd     ymm0,ymmword ptr [edx]  */ \
_LINE4 ( 0xC5,0xFD,0x10,0x09 )         /* vmovupd     ymm1,ymmword ptr [ecx]  */ \
_LINE4 ( 0xC5,0xFD,0x58,0xD8 )         /* vaddpd      ymm1,ymm0,ymm1  */ \
_LINE5 ( 0xC4,0xC1,0x7D,0x11,0x08 )    /* vmovupd     ymmword ptr [r8],ymm1  */ \
_END_ASM

//**************************** ADD System V x64 *********************************
// addition vectors rdi-a void *, rsi-b void *, rdx-rez void *

/// Сложение двухмерных векторов одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP2DADDSSE_SV \
_BEGIN_ASM \
_LINE3( 0x0F,0x57,0xC0 )           /* xorps       xmm0,xmm0  */ \
_LINE3( 0x0F,0x28,0xC8 )           /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x12,0x0E )           /* movlps      xmm1,qword ptr [rsi]  */ \
_LINE3( 0x0F,0x12,0x07 )           /* movlps      xmm0,qword ptr [rdi]  */ \
_LINE3( 0x0F,0x58,0xC8 )           /* addps       xmm1,xmm0  */ \
_LINE3( 0x0F,0x13,0x0A )           /* movlps      qword ptr [rdx],xmm1  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Сложение двухмерных векторов одинарной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP2DADDSSE2_SV \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x07 )                               /* movsd       xmm0,mmword ptr [rdi]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0E )                               /* movsd       xmm1,mmword ptr [rsi]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x02 )                               /* movsd       mmword ptr [rdx],xmm0  */ \
_END_ASM

/// Сложение трехмерных векторов одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP3DADDSSE_SV \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x4E,0x08 )      /* movss       xmm1,dword ptr [rsi+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x47,0x08 )      /* movss       xmm0,dword ptr [rdi+8]  */ \
_LINE3( 0x0F,0x16,0x0E )                /* movhps      xmm1,qword ptr [rsi]  */ \
_LINE3( 0x0F,0x16,0x07 )                /* movhps      xmm0,qword ptr [rdi]  */ \
_LINE3( 0x0F,0x58,0xC8 )                /* addps       xmm1,xmm0  */ \
_LINE3( 0x0F,0x17,0x0A )                /* movhps      qword ptr [rdx],xmm1  */ \
_LINE5( 0xF3,0x0F,0x11,0x4A,0x08 )      /* movlps      qword ptr [rdx+8],xmm1  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Сложение трехмерных векторов одинарной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP3DADDSSE2__ \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE4( 0x66,0x0F,0x16,0x00 )                               /* movhpd      xmm0,qword ptr [eax]  */ \
_LINE4( 0x66,0x0F,0x16,0x0A )                               /* movhpd      xmm1,qword ptr [edx]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x17,0x01 )                               /* movhpd      qword ptr [ecx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x41,0x08 )                          /* movss       dword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Сложение четырехмерных векторов одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP4DADDSSE_SV \
_BEGIN_ASM \
_LINE3( 0x0F,0x12,0x06 )                                    /* movlps      xmm0,qword ptr [rsi]  */ \
_LINE3( 0x0F,0x12,0x0F )                                    /* movlps      xmm1,qword ptr [rdi]  */ \
_LINE4( 0x0F,0x16,0x4F,0x08 )                               /* movhps      xmm1,qword ptr [rdi+8]  */ \
_LINE4( 0x0F,0x16,0x46,0x08 )                               /* movhps      xmm0,qword ptr [rsi+8]  */ \
_LINE3( 0x0F,0x58,0xC8 )                                    /* addps       xmm1,xmm0  */ \
_LINE3( 0x0F,0x13,0x0A )                                    /* movlps      mmword ptr [rdx],xmm1  */ \
_LINE4( 0x0F,0x17,0x4A,0x08 )                               /* movhps      qword ptr [rdx+8],xmm1  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Сложение четырехмерных векторов одинарной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP4DADDSSE2_SV \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x06 )                               /* movsd       xmm0,mmword ptr [rsi]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0F )                               /* movsd       xmm1,mmword ptr [rdi]  */ \
_LINE4( 0x0F,0x16,0x4F,0x08 )                               /* movhps      xmm1,qword ptr [rdi+8]  */ \
_LINE4( 0x0F,0x16,0x46,0x08 )                               /* movhps      xmm0,qword ptr [rsi+8]  */ \
_LINE3( 0x0F,0x58,0xC8 )                                    /* addps       xmm1,xmm0  */ \
_LINE4( 0xF2,0x0F,0x11,0x0A )                               /* movsd       mmword ptr [rdx],xmm1  */ \
_LINE4( 0x0F,0x17,0x4A,0x08 )                               /* movhps      qword ptr [rdx+8],xmm1  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Сложение четырехмерных векторов одинарной точности, команды SSE3.
/// @brief for CPUTYPE3
#define VECTORP4DADDSSE3__ \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0x66,0x0F,0x17,0x41,0x08 )                          /* movhpd      qword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Сложение четырехмерных векторов одинарной точности, команды SSE4.
/// @brief for CPUTYPE4
#define VECTORP4DADDSSE4__ \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_END_ASM

/// Сложение двухмерных векторов двойной точности, команды SSE2.
#define VECTORP2DDADDSSE2_SV \
_BEGIN_ASM \
_LINE4( 0x66,0x0F,0x10,0x0E )        /* movupd      xmm1,xmmword ptr [rsi]  */ \
_LINE4( 0x66,0x0F,0x10,0x07 )        /* movupd      xmm0,xmmword ptr [rdi]  */ \
_LINE4( 0x66,0x0F,0x58,0xC8 )        /* addpd       xmm1,xmm0  */ \
_LINE4( 0x66,0x0F,0x11,0x0A )        /* movupd      xmmword ptr [rdx],xmm1  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Сложение двухмерных векторов двойной точности, команды SSE3.
#define VECTORP2DDADDSSE3__ \
_BEGIN_ASM \
_LINE5( 0xF2,0x0F,0x10,0x48,0x08 )                          /* movsd       xmm1,mmword ptr [eax+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0x58,0x4A,0x08 )                          /* addsd       xmm1,mmword ptr [edx+8]  */ \
_LINE4( 0xF2,0x0F,0x58,0x02 )                               /* addsd       xmm0,mmword ptr [edx]  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x49,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm1 */ \
_END_ASM

/// Сложение двухмерных векторов двойной точности, команды SSE4.
#define VECTORP2DDADDSSE4__ \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x66,0x0F,0x58,0xC1 )                               /* addpd       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_END_ASM

/// Сложение трехмерных векторов двойной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP3DDADDSSE2_SV \
_BEGIN_ASM \
_LINE5( 0xF2,0x0F,0x10,0x47,0x10 )                          /* movsd       xmm0,mmword ptr [rdi+10h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x56,0x10 )                          /* movsd       xmm2,mmword ptr [rsi+10h]  */ \
_LINE4( 0x66,0x0F,0x10,0x0E )                               /* movupd      xmm1,xmmword ptr [rsi]  */ \
_LINE4( 0xF2,0x0F,0x58,0xD0 )                               /* addsd       xmm2,xmm0  */ \
_LINE4( 0x66,0x0F,0x10,0x07 )                               /* movupd      xmm0,xmmword ptr [rdi]  */ \
_LINE4( 0x66,0x0F,0x58,0xC8 )                               /* addpd       xmm1,xmm0  */ \
_LINE4( 0x66,0x0F,0x11,0x0A )                               /* movupd      xmmword ptr [edx],xmm1  */ \
_LINE5( 0xF2,0x0F,0x11,0x52,0x10 )                          /* movsd       mmword ptr [edx+10h],xmm2  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Сложение трехмерных векторов двойной точности, команды SSE3. ???
/// @brief for CPUTYPE3
#define VECTORP3DDADDSSE3__ \
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
#define VECTORP3DDADDARRAYSSE3__ \
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
#define VECTORP3DDADDSSE4__ \
BEGIN_ASM \
ASM(lddqu xmm0,[eax]) \
ASM(lddqu xmm4,[edx]) \
ASM(addpd xmm0,xmm4) \
ASM(movsd xmm2,[eax+16]) \
ASM(movupd [ecx],xmm0) \
ASM(addsd xmm2,[edx+16]) \
ASM(movsd [ecx+16],xmm2) \
END_ASM

/// Сложение четырехмерных векторов двойной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP4DDADDSSE2_SV \
_BEGIN_ASM \
_LINE5( 0x66,0x0F,0x10,0x47,0x10 )       /* movupd      xmm0,xmmword ptr [rdi+0x10]  */ \
_LINE5( 0x66,0x0F,0x10,0x56,0x10 )       /* movupd      xmm2,xmmword ptr [rsi+0x10]  */ \
_LINE4( 0x66,0x0F,0x10,0x0E )            /* movupd      xmm1,xmmword ptr [rsi]  */ \
_LINE4( 0x66,0x0F,0x58,0xD0 )            /* addpd       xmm2,xmm0  */ \
_LINE4( 0x66,0x0F,0x10,0x07 )            /* movupd      xmm0,xmmword ptr [rdi]  */ \
_LINE4( 0x66,0x0F,0x58,0xC8 )            /* addpd       xmm1,xmm0  */ \
_LINE4( 0x66,0x0F,0x11,0x0A )            /* movupd      xmmword ptr [rdx],xmm1  */ \
_LINE5( 0x66,0x0F,0x11,0x52,0x10 )       /* movupd      xmmword ptr [rdx+0x10],xmm2  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Сложение четырехмерных векторов двойной точности, команды AVX
#define VECTORP4DDADDAVX_SV \
_BEGIN_ASM \
_LINE4 ( 0xC5,0xFD,0x10,0x06 )         /* vmovupd     ymm0,ymmword ptr [esi]  */ \
_LINE4 ( 0xC5,0xFD,0x10,0x0F )         /* vmovupd     ymm1,ymmword ptr [edi]  */ \
_LINE4 ( 0xC5,0xFD,0x58,0xD8 )         /* vaddpd      ymm1,ymm0,ymm1  */ \
_LINE4 ( 0xC5,0xFD,0x11,0x0A )         /* vmovupd     ymmword ptr [rdx],ymm1  */ \
_END_ASM

//**************************** ADD all caling conventions *********************************

#ifdef OS_WIN
/// Microsoft Calling Convention
#ifndef CALLMC
#define CALLMC
#endif
#else
/// System V Calling Convention
#ifndef CALLSV
#define CALLSV
#endif
#endif

#ifdef CALLMC
#define VECTORP2DADDSSE VECTORP2DADDSSE_MC
#define VECTORP3DADDSSE VECTORP3DADDSSE_MC
#define VECTORP4DADDSSE VECTORP4DADDSSE_MC
#define VECTORP2DADDSSE2 VECTORP2DADDSSE2_MC
#define VECTORP4DADDSSE2 VECTORP4DADDSSE2_MC
#define VECTORP2DDADDSSE2 VECTORP2DDADDSSE2_MC
#define VECTORP3DDADDSSE2 VECTORP3DDADDSSE2_MC
#define VECTORP4DDADDSSE2 VECTORP4DDADDSSE2_MC
#define VECTORP4DDADDAVX VECTORP4DDADDAVX_MC
#endif

#ifdef CALLSV
#define VECTORP2DADDSSE VECTORP2DADDSSE_SV
#define VECTORP3DADDSSE VECTORP3DADDSSE_SV
#define VECTORP4DADDSSE VECTORP4DADDSSE_SV
#define VECTORP2DADDSSE2 VECTORP2DADDSSE2_SV
#define VECTORP4DADDSSE2 VECTORP4DADDSSE2_SV
#define VECTORP2DDADDSSE2 VECTORP2DDADDSSE2_SV
#define VECTORP3DDADDSSE2 VECTORP3DDADDSSE2_SV
#define VECTORP4DDADDSSE2 VECTORP4DDADDSSE2_SV
#define VECTORP4DDADDAVX VECTORP4DDADDAVX_SV
#endif

#endif
