//=============================================================================
///**
// *  @file vector_normal.h
// *
// *  $Id: vector_normal.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float normal, MS Visual C++ 2003-2008
// *
// *  @author Pant_eleymonov Alek_sandr Kons_tantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifdef CPU_BT
#ifndef CPU_X86_64
#define GEN3_VECTOR_NORMAL_H
#endif

#ifndef GEN3_VECTOR_NORMAL_H
#define GEN3_VECTOR_NORMAL_H

//**************************** NORMAL Microsoft x64 *********************************
// vector dot product ecx=[esp+4]-a void * edx=[esp+8]-b void *

/// Нормализация двухмерного вектора одинарной точности, команды SSE
#define VECTORP2DNORMALSSE_MC \
_BEGIN_ASM \
_LINE3( 0x0F,0x57,0xD2 )           /* xorps       xmm2,xmm2  */ \
_LINE3( 0x0F,0x12,0x11 )           /* movlps      xmm2,qword ptr [rcx]  */ \
_LINE3( 0x0F,0x28,0xCA )           /* movaps      xmm1,xmm2  */ \
_LINE3( 0x0F,0x59,0xCA )           /* mulps       xmm1,xmm2  */ \
_LINE3( 0x0F,0x28,0xC1 )           /* movaps      xmm0,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC1,0x01 )      /* shufps      xmm0,xmm1,1  */ \
_LINE4( 0xF3,0x0F,0x58,0xC8 )      /* addss       xmm1,xmm0  */ \
_LINE4( 0xF3,0x0F,0x51,0xC9 )      /* sqrtss      xmm1,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )      /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x5E,0xD1 )           /* divps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x13,0x12 )           /* movlps      qword ptr [rdx],xmm2  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Нормализация трехмерного вектора одинарной точности, команды SSE
#define VECTORP3DNORMALSSE_MC \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x59,0x08 ) /* movss       xmm3,dword ptr [rcx+8]  */ \
_LINE3( 0x0F,0x16,0x19 )           /* movhps      xmm3,qword ptr [rcx]  */ \
_LINE3( 0x0F,0x28,0xCB )           /* movaps      xmm1,xmm3  */ \
_LINE3( 0x0F,0x59,0xCB )           /* mulps       xmm1,xmm3  */ \
_LINE3( 0x0F,0x28,0xD1 )           /* movaps      xmm2,xmm1  */ \
_LINE4( 0x0F,0xC6,0xD1,0x0E )      /* shufps      xmm2,xmm1,0Eh  */ \
_LINE3( 0x0F,0x28,0xC2 )           /* movaps      xmm0,xmm2  */ \
_LINE4( 0x0F,0xC6,0xC2,0x01 )      /* shufps      xmm0,xmm2,1  */ \
_LINE3( 0x0F,0x58,0xD1 )           /* addps       xmm2,xmm1  */ \
_LINE4( 0xF3,0x0F,0x58,0xD0 )      /* addss       xmm2,xmm0  */ \
_LINE4( 0xF3,0x0F,0x51,0xD2 )      /* sqrtss      xmm2,xmm2  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )      /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x5E,0xDA )           /* divps       xmm3,xmm2  */ \
_LINE3( 0x0F,0x17,0x1A )           /* movhps      qword ptr [rdx],xmm3  */ \
_LINE5( 0xF3,0x0F,0x11,0x5A,0x08 ) /* movss       dword ptr [rdx+8],xmm3  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Нормализация четырехмерного вектора одинарной точности, команды SSE
#define VECTORP4DNORMALSSE_MC \
_BEGIN_ASM \
_LINE4( 0x0F,0x12,0x59,0x08 )        /* movlps      xmm3,qword ptr [rcx+8]  */ \
_LINE3( 0x0F,0x16,0x19 )             /* movhps      xmm3,qword ptr [rcx]  */ \
_LINE3( 0x0F,0x28,0xD3 )             /* movaps      xmm2,xmm3  */ \
_LINE3( 0x0F,0x59,0xD3 )             /* mulps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x28,0xCA )             /* movaps      xmm1,xmm2  */ \
_LINE3( 0x0F,0x12,0xCA )             /* movhlps     xmm1,xmm2  */ \
_LINE3( 0x0F,0x28,0xC1 )             /* movaps      xmm0,xmm1  */ \
_LINE3( 0x0F,0x58,0xD1 )             /* addps       xmm2,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC1,0x01 )        /* shufps      xmm0,xmm1,1  */ \
_LINE4( 0xF3,0x0F,0x58,0xD0 )        /* addss       xmm2,xmm0  */ \
_LINE4( 0xF3,0x0F,0x51,0xD2 )        /* sqrtss      xmm2,xmm2  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )        /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x5E,0xDA )             /* divps       xmm3,xmm2  */ \
_LINE3( 0x0F,0x17,0x1A )             /* movhps      qword ptr [rdx],xmm3  */ \
_LINE4( 0x0F,0x13,0x5A,0x08 )        /* movlps      qword ptr [rdx+8],xmm3  */ \
_LINE1( 0xC3 ) \
_END_ASM

//**************************** NORMAL System V x64 *********************************
// addition vectors rdi-a void *, rsi-b void *

/// Нормализация двухмерного вектора одинарной точности, команды SSE
#define VECTORP2DNORMALSSE_SV \
_BEGIN_ASM \
_LINE3( 0x0F,0x57,0xD2 )           /* xorps       xmm2,xmm2  */ \
_LINE3( 0x0F,0x12,0x17 )           /* movlps      xmm2,qword ptr [rdi]  */ \
_LINE3( 0x0F,0x28,0xCA )           /* movaps      xmm1,xmm2  */ \
_LINE3( 0x0F,0x59,0xCA )           /* mulps       xmm1,xmm2  */ \
_LINE3( 0x0F,0x28,0xC1 )           /* movaps      xmm0,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC1,0x01 )      /* shufps      xmm0,xmm1,1  */ \
_LINE4( 0xF3,0x0F,0x58,0xC8 )      /* addss       xmm1,xmm0  */ \
_LINE4( 0xF3,0x0F,0x51,0xC9 )      /* sqrtss      xmm1,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )      /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x5E,0xD1 )           /* divps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x13,0x16 )           /* movlps      qword ptr [rsi],xmm2  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Нормализация трехмерного вектора одинарной точности, команды SSE
#define VECTORP3DNORMALSSE_SV \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x5F,0x08 ) /* movss       xmm3,dword ptr [rdi+8]  */ \
_LINE3( 0x0F,0x16,0x1F )           /* movhps      xmm3,qword ptr [rdi]  */ \
_LINE3( 0x0F,0x28,0xCB )           /* movaps      xmm1,xmm3  */ \
_LINE3( 0x0F,0x59,0xCB )           /* mulps       xmm1,xmm3  */ \
_LINE3( 0x0F,0x28,0xD1 )           /* movaps      xmm2,xmm1  */ \
_LINE4( 0x0F,0xC6,0xD1,0x0E )      /* shufps      xmm2,xmm1,0Eh  */ \
_LINE3( 0x0F,0x28,0xC2 )           /* movaps      xmm0,xmm2  */ \
_LINE4( 0x0F,0xC6,0xC2,0x01 )      /* shufps      xmm0,xmm2,1  */ \
_LINE3( 0x0F,0x58,0xD1 )           /* addps       xmm2,xmm1  */ \
_LINE4( 0xF3,0x0F,0x58,0xD0 )      /* addss       xmm2,xmm0  */ \
_LINE4( 0xF3,0x0F,0x51,0xD2 )      /* sqrtss      xmm2,xmm2  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )      /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x5E,0xDA )           /* divps       xmm3,xmm2  */ \
_LINE3( 0x0F,0x17,0x1E )           /* movhps      qword ptr [rsi],xmm3  */ \
_LINE5( 0xF3,0x0F,0x11,0x5E,0x08 ) /* movss       dword ptr [rsi+8],xmm3  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Нормализация четырехмерного вектора одинарной точности, команды SSE
#define VECTORP4DNORMALSSE_SV \
_BEGIN_ASM \
_LINE4( 0x0F,0x12,0x5F,0x08 )        /* movlps      xmm3,qword ptr [rdi+8]  */ \
_LINE3( 0x0F,0x16,0x1F )             /* movhps      xmm3,qword ptr [rdi]  */ \
_LINE3( 0x0F,0x28,0xD3 )             /* movaps      xmm2,xmm3  */ \
_LINE3( 0x0F,0x59,0xD3 )             /* mulps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x28,0xCA )             /* movaps      xmm1,xmm2  */ \
_LINE3( 0x0F,0x12,0xCA )             /* movhlps     xmm1,xmm2  */ \
_LINE3( 0x0F,0x28,0xC1 )             /* movaps      xmm0,xmm1  */ \
_LINE3( 0x0F,0x58,0xD1 )             /* addps       xmm2,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC1,0x01 )        /* shufps      xmm0,xmm1,1  */ \
_LINE4( 0xF3,0x0F,0x58,0xD0 )        /* addss       xmm2,xmm0  */ \
_LINE4( 0xF3,0x0F,0x51,0xD2 )        /* sqrtss      xmm2,xmm2  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )        /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x5E,0xDA )             /* divps       xmm3,xmm2  */ \
_LINE3( 0x0F,0x17,0x1E )             /* movhps      qword ptr [rsi],xmm3  */ \
_LINE4( 0x0F,0x13,0x5E,0x08 )        /* movlps      qword ptr [rsi+8],xmm3  */ \
_LINE1( 0xC3 ) \
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
#define VECTORP2DNORMALSSE VECTORP2DNORMALSSE_MC
#define VECTORP3DNORMALSSE VECTORP3DNORMALSSE_MC
#define VECTORP4DNORMALSSE VECTORP4DNORMALSSE_MC
//#define VECTORP2DDLENGTH2SSE4 VECTORP2DDLENGTH2SSE4_MC
//#define VECTORP3DDLENGTH2SSE4 VECTORP3DDLENGTH2SSE4_MC
//#define VECTORP4DDLENGTH2SSE4 VECTORP4DDLENGTH2SSE4_MC
#endif

#ifdef CALLSV
#define VECTORP2DNORMALSSE VECTORP2DNORMALSSE_SV
#define VECTORP3DNORMALSSE VECTORP3DNORMALSSE_SV
#define VECTORP4DNORMALSSE VECTORP4DNORMALSSE_SV
//#define VECTORP2DDLENGTH2SSE4 VECTORP2DDLENGTH2SSE4_SV
//#define VECTORP3DDLENGTH2SSE4 VECTORP3DDLENGTH2SSE4_SV
//#define VECTORP4DDLENGTH2SSE4 VECTORP4DDLENGTH2SSE4_SV
#endif

#endif // GEN3_VECTOR_NORMAL_H
#endif