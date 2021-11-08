//=============================================================================
///**
// *  @file vector_lerp.h
// *
// *  $Id: vector_lerp.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float lerp, MS Visual C++ 2003-2008
// *
// *  @author Pant_eleymonov Alek_sandr Kons_tantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifdef CPU_BT
#ifndef CPU_X86_64
#define GEN3_VECTOR_LERP_H
#endif

#ifndef GEN3_VECTOR_LERP_H
#define GEN3_VECTOR_LERP_H

//**************************** LERP Microsoft x64 *********************************
// vector dot product ecx=[esp+4]-a void * edx=[esp+8]-b void *

/// »нтерпол€ци€ между двухмерными векторами одинарной точности, команды SSE4
#define VECTORP2DLERPSSE4_MC \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x09 )    /* movsd       xmm1,mmword ptr [rcx]  */ \
_LINE4( 0xF2,0x0F,0x10,0x02 )    /* movsd       xmm0,mmword ptr [rdx]  */ \
_LINE3( 0x0F,0x5C,0xC1 )         /* subps       xmm0,xmm1  */ \
_LINE4( 0x0F,0xC6,0xDB,0x50 )    /* shufps      xmm3,xmm3,50h  */ \
_LINE3( 0x0F,0x59,0xD8 )         /* mulps       xmm3,xmm0  */ \
_LINE3( 0x0F,0x58,0xD9 )         /* addps       xmm3,xmm1  */ \
_LINE4( 0x41,0x0F,0x13,0x18 )    /* movlps      qword ptr [r8],xmm3  */ \
_LINE1( 0xC3 )                   /* ret  */ \
_END_ASM

/// »нтерпол€ци€ между трехмерными векторами одинарной точности, команды SSE4
#define VECTORP3DLERPSSE4_MC \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x51,0x08 )       /* movss       xmm2,dword ptr [rcx+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x42,0x08 )       /* movss       xmm0,dword ptr [rdx+8]  */ \
_LINE3( 0x0F,0x16,0x11 )                 /* movhps      xmm2,qword ptr [rcx]  */ \
_LINE3( 0x0F,0x16,0x02 )                 /* movhps      xmm0,qword ptr [rdx]  */ \
_LINE3( 0x0F,0x5C,0xC2 )                 /* subps       xmm0,xmm2  */ \
_LINE4( 0x0F,0xC6,0xDB,0x04 )            /* shufps      xmm3,xmm3,4  */ \
_LINE3( 0x0F,0x59,0xC3 )                 /* mulps       xmm0,xmm3  */ \
_LINE3( 0x0F,0x58,0xD0 )                 /* addps       xmm2,xmm0  */ \
_LINE4( 0x41,0x0F,0x17,0x10 )            /* movhps      qword ptr [r8],xmm2  */ \
_LINE6( 0xF3,0x41,0x0F,0x11,0x50,0x08 )  /* movss       dword ptr [r8+8],xmm2  */ \
_LINE1( 0xC3 )                           /* ret  */ \
_END_ASM

/// »нтерпол€ци€ между четырехмерными векторами одинарной точности, команды SSE4
#define VECTORP4DLERPSSE4_MC \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x09 )  /* lddqu       xmm1,xmmword ptr [rcx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x02 )  /* lddqu       xmm0,xmmword ptr [rdx]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )  /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x5C,0xC1 )       /* subps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x59,0xC3 )       /* mulps       xmm0,xmm3  */ \
_LINE3( 0x0F,0x58,0xC1 )       /* addps       xmm0,xmm1  */ \
_LINE4( 0x41,0x0F,0x11,0x00 )  /* movups      xmmword ptr [r8],xmm0  */ \
_LINE1( 0xC3 )                 /* ret  */ \
_END_ASM

/// »нтерпол€ци€ между двухмерными векторами двойной точности, команды SSE4
#define VECTORP2DDLERPSSE4_MC \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x21 )       /* lddqu       xmm4,xmmword ptr [rcx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )       /* lddqu       xmm1,xmmword ptr [rdx]  */ \
_LINE4( 0xF2,0x0F,0x12,0xD3 )       /* movddup     xmm2,xmm3  */ \
_LINE4( 0xF2,0x0F,0x10,0xC3 )       /* movsd       xmm0,xmm3  */ \
_LINE4( 0x66,0x0F,0x5C,0xCC )       /* subpd       xmm1,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xD1 )       /* mulpd       xmm2,xmm1  */ \
_LINE4( 0x66,0x0F,0x58,0xD4 )       /* addpd       xmm2,xmm4  */ \
_LINE5( 0x66,0x41,0x0F,0x11,0x10 )  /* movupd      xmmword ptr [r8],xmm2  */ \
_LINE1( 0xC3 )                      /* ret  */ \
_END_ASM

/// »нтерпол€ци€ между трехмерными векторами двойной точности, команды SSE4
#define VECTORP3DDLERPSSE4_MC \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x11 )           /* lddqu       xmm2,xmmword ptr [rcx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x22 )           /* lddqu       xmm4,xmmword ptr [rdx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x6A,0x10 )      /* movsd       xmm5,mmword ptr [rdx+10h]  */ \
_LINE4( 0x66,0x0F,0x5C,0xE2 )           /* subpd       xmm4,xmm2  */ \
_LINE4( 0xF2,0x0F,0x12,0xDB )           /* movddup     xmm3,xmm3  */ \
_LINE5( 0xF2,0x0F,0x10,0x41,0x10 )      /* movsd       xmm0,mmword ptr [rcx+10h]  */ \
_LINE4( 0xF2,0x0F,0x5C,0xE8 )           /* subsd       xmm5,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xE3 )           /* mulpd       xmm4,xmm3  */ \
_LINE4( 0xF2,0x0F,0x59,0xEB )           /* mulsd       xmm5,xmm3  */ \
_LINE4( 0x66,0x0F,0x58,0xE2 )           /* addpd       xmm4,xmm2  */ \
_LINE4( 0xF2,0x0F,0x58,0xE8 )           /* addsd       xmm5,xmm0  */ \
_LINE5( 0x66,0x41,0x0F,0x11,0x20 )      /* movupd      xmmword ptr [r8],xmm4  */ \
_LINE6( 0xF2,0x41,0x0F,0x11,0x68,0x10 ) /* movsd       mmword ptr [r8+10h],xmm5  */ \
_LINE1( 0xC3 )                          /* ret  */ \
_END_ASM

/// »нтерпол€ци€ между четырехмерными векторами двойной точности, команды SSE4
#define VECTORP4DDLERPSSE4_MC \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x11 )           /* lddqu       xmm2,xmmword ptr [rcx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x22 )           /* lddqu       xmm4,xmmword ptr [rdx]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x6A,0x10 )      /* lddqu       xmm5,xmmword ptr [rdx+10h]  */ \
_LINE4( 0x66,0x0F,0x5C,0xE2 )           /* subpd       xmm4,xmm2  */ \
_LINE5( 0xF2,0x0F,0xF0,0x71,0x10 )      /* lddqu       xmm0,xmmword ptr [rcx+10h]  */ \
_LINE4( 0xF2,0x0F,0x12,0xDB )           /* movddup     xmm1,xmm3  */ \
_LINE4( 0x66,0x0F,0x59,0xE1 )           /* mulpd       xmm4,xmm1  */ \
_LINE4( 0x66,0x0F,0x5C,0xEE )           /* subpd       xmm5,xmm0  */ \
_LINE4( 0x66,0x0F,0x58,0xE2 )           /* addpd       xmm4,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xE9 )           /* mulpd       xmm5,xmm1  */ \
_LINE4( 0x66,0x0F,0x58,0xEE )           /* addpd       xmm5,xmm0  */ \
_LINE5( 0x66,0x41,0x0F,0x11,0x20 )      /* movupd      xmmword ptr [r8],xmm4  */ \
_LINE6( 0x66,0x41,0x0F,0x11,0x68,0x10 ) /* movupd      xmmword ptr [r8+10h],xmm5  */ \
_LINE1( 0xC3 )                          /* ret  */ \
_END_ASM

//**************************** LERP System V x64 *********************************
// addition vectors rdi-a void *, rsi-b void *

/// »нтерпол€ци€ между двухмерными векторами одинарной точности, команды SSE4
#define VECTORP2DLERPSSE4_SV \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x0F )    /* movsd       xmm1,mmword ptr [rdi]  */ \
_LINE4( 0xF2,0x0F,0x10,0x16 )    /* movsd       xmm2,mmword ptr [rsi]  */ \
_LINE3( 0x0F,0x5C,0xD1 )         /* subps       xmm2,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC0,0x50 )    /* shufps      xmm0,xmm0,50h  */ \
_LINE3( 0x0F,0x59,0xC2 )         /* mulps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x58,0xC1 )         /* addps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x02 )         /* movlps      qword ptr [rdx],xmm0  */ \
_LINE1( 0xC3 )                   /* ret  */ \
_END_ASM

/// »нтерпол€ци€ между трехмерными векторами одинарной точности, команды SSE4
#define VECTORP3DLERPSSE4_SV \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x57,0x08 )       /* movss       xmm2,dword ptr [rdi+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4E,0x08 )       /* movss       xmm1,dword ptr [rsi+8]  */ \
_LINE3( 0x0F,0x16,0x17 )                 /* movhps      xmm2,qword ptr [rdi]  */ \
_LINE3( 0x0F,0x16,0x0E )                 /* movhps      xmm1,qword ptr [rsi]  */ \
_LINE3( 0x0F,0x5C,0xCA )                 /* subps       xmm1,xmm2  */ \
_LINE4( 0x0F,0xC6,0xC0,0x04 )            /* shufps      xmm0,xmm0,4  */ \
_LINE3( 0x0F,0x59,0xC8 )                 /* mulps       xmm1,xmm0  */ \
_LINE3( 0x0F,0x58,0xD1 )                 /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x17,0x12 )                 /* movhps      qword ptr [rdx],xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x52,0x08 )       /* movss       dword ptr [rdx+8],xmm2  */ \
_LINE1( 0xC3 )                           /* ret  */ \
_END_ASM

/// »нтерпол€ци€ между четырехмерными векторами одинарной точности, команды SSE4
#define VECTORP4DLERPSSE4_SV \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x0F )  /* lddqu       xmm1,xmmword ptr [rdi]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x16 )  /* lddqu       xmm2,xmmword ptr [rsi]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )  /* shufps      xmm0,xmm0,0  */ \
_LINE3( 0x0F,0x5C,0xD1 )       /* subps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x59,0xC2 )       /* mulps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x58,0xC1 )       /* addps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x11,0x02 )       /* movups      xmmword ptr [rdx],xmm0  */ \
_LINE1( 0xC3 )                 /* ret  */ \
_END_ASM

/// »нтерпол€ци€ между двухмерными векторами двойной точности, команды SSE4
#define VECTORP2DDLERPSSE4_SV \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x27 )       /* lddqu       xmm4,xmmword ptr [rdi]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0E )       /* lddqu       xmm1,xmmword ptr [rsi]  */ \
_LINE4( 0xF2,0x0F,0x12,0xC0 )       /* movddup     xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x5C,0xCC )       /* subpd       xmm1,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xC1 )       /* mulpd       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x58,0xC4 )       /* addpd       xmm0,xmm4  */ \
_LINE4( 0x66,0x0F,0x11,0x02 )       /* movupd      xmmword ptr [rdx],xmm0  */ \
_LINE1( 0xC3 )                      /* ret  */ \
_END_ASM

/// »нтерпол€ци€ между трехмерными векторами двойной точности, команды SSE4
#define VECTORP3DDLERPSSE4_SV \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x17 )           /* lddqu       xmm2,xmmword ptr [rdi]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x26 )           /* lddqu       xmm4,xmmword ptr [rsi]  */ \
_LINE5( 0xF2,0x0F,0x10,0x6E,0x10 )      /* movsd       xmm5,mmword ptr [rsi+10h]  */ \
_LINE4( 0x66,0x0F,0x5C,0xE2 )           /* subpd       xmm4,xmm2  */ \
_LINE4( 0xF2,0x0F,0x12,0xC0 )           /* movddup     xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x10,0x4F,0x10 )      /* movsd       xmm1,mmword ptr [rdi+10h]  */ \
_LINE4( 0xF2,0x0F,0x5C,0xE9 )           /* subsd       xmm5,xmm1  */ \
_LINE4( 0x66,0x0F,0x59,0xE0 )           /* mulpd       xmm4,xmm0  */ \
_LINE4( 0xF2,0x0F,0x59,0xE8 )           /* mulsd       xmm5,xmm0  */ \
_LINE4( 0x66,0x0F,0x58,0xE2 )           /* addpd       xmm4,xmm2  */ \
_LINE4( 0xF2,0x0F,0x58,0xE9 )           /* addsd       xmm5,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x22 )           /* movupd      xmmword ptr [rdx],xmm4  */ \
_LINE5( 0xF2,0x0F,0x11,0x6A,0x10 )      /* movsd       mmword ptr [rdx+10h],xmm5  */ \
_LINE1( 0xC3 )                          /* ret  */ \
_END_ASM

/// »нтерпол€ци€ между четырехмерными векторами двойной точности, команды SSE4
#define VECTORP4DDLERPSSE4_SV \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x17 )           /* lddqu       xmm2,xmmword ptr [rdi]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x26 )           /* lddqu       xmm4,xmmword ptr [rsi]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x6E,0x10 )      /* lddqu       xmm5,xmmword ptr [rsi+10h]  */ \
_LINE4( 0x66,0x0F,0x5C,0xE2 )           /* subpd       xmm4,xmm2  */ \
_LINE5( 0xF2,0x0F,0xF0,0x4F,0x10 )      /* lddqu       xmm1,xmmword ptr [rdi+10h]  */ \
_LINE4( 0xF2,0x0F,0x12,0xC0 )           /* movddup     xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xE0 )           /* mulpd       xmm4,xmm0  */ \
_LINE4( 0x66,0x0F,0x5C,0xE9 )           /* subpd       xmm5,xmm1  */ \
_LINE4( 0x66,0x0F,0x58,0xE2 )           /* addpd       xmm4,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xE8 )           /* mulpd       xmm5,xmm0  */ \
_LINE4( 0x66,0x0F,0x58,0xE9 )           /* addpd       xmm5,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x22 )           /* movupd      xmmword ptr [rdx],xmm4  */ \
_LINE5( 0x66,0x0F,0x11,0x6A,0x10 )      /* movupd      xmmword ptr [rdx+10h],xmm5  */ \
_LINE1( 0xC3 )                          /* ret  */ \
_END_ASM

//**************************** LERP all caling conventions *********************************

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
#define VECTORP2DLERPSSE4 VECTORP2DLERPSSE4_MC
#define VECTORP3DLERPSSE4 VECTORP3DLERPSSE4_MC
#define VECTORP4DLERPSSE4 VECTORP4DLERPSSE4_MC
#define VECTORP2DDLERPSSE4 VECTORP2DDLERPSSE4_MC
#define VECTORP3DDLERPSSE4 VECTORP3DDLERPSSE4_MC
#define VECTORP4DDLERPSSE4 VECTORP4DDLERPSSE4_MC
#endif

#ifdef CALLSV
#define VECTORP2DLERPSSE4 VECTORP2DLERPSSE4_SV
#define VECTORP3DLERPSSE4 VECTORP3DLERPSSE4_SV
#define VECTORP4DLERPSSE4 VECTORP4DLERPSSE4_SV
#define VECTORP2DDLERPSSE4 VECTORP2DDLERPSSE4_SV
#define VECTORP3DDLERPSSE4 VECTORP3DDLERPSSE4_SV
#define VECTORP4DDLERPSSE4 VECTORP4DDLERPSSE4_SV
#endif

#endif // GEN3_VECTOR_NORMAL_H
#endif