//=============================================================================
///**
// *  @file vector_dotproduct.h
// *
// *  $Id: vector_dotproduct.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float dot product, MS Visual C++ 2003-2008
// *
// *  @author Pant_eleymonov Alek_sandr Kons_tantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef CPU_X86_64
#define GEN3_VECTOR_DOT_H
#endif

#ifndef GEN3_VECTOR_DOT_H
#define GEN3_VECTOR_DOT_H

//**************************** DOT PRODUCT Microsoft x64 *********************************
// vector dot product ecx=[esp+4]-a void * edx=[esp+8]-b void *

/// —кал€рное произведение двухмерных векторов одинарной точности, команды SSE4
#define VECTORP2DDOTPRODUCTSSE4_MC \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x01 )           /* movsd       xmm0,mmword ptr [rcx]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )           /* movsd       xmm1,mmword ptr [rdx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC1,0x31 ) /* dpps        xmm0,xmm1,31h  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// —кал€рное произведение трехмерных векторов одинарной точности, команды SSE4
#define VECTORP3DDOTPRODUCTSSE4_MC \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )      /* movss       xmm1,dword ptr [rdx+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x41,0x08 )      /* movss       xmm0,dword ptr [rcx+8]  */ \
_LINE3( 0x0F,0x16,0x0A )                /* movhps      xmm1,qword ptr [rdx]  */ \
_LINE3( 0x0F,0x16,0x01 )                /* movhps      xmm0,qword ptr [rcx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC1,0xD1 ) /* dpps        xmm0,xmm1,0D1h  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// —кал€рное произведение четырехмерных векторов одинарной точности, команды SSE4
#define VECTORP4DDOTPRODUCTSSE4_MC \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )            /* lddqu       xmm0,xmmword ptr [rcx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )            /* lddqu       xmm1,xmmword ptr [rdx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC1,0xF1 )  /* dpps        xmm0,xmm1,0F1h  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// —кал€рное произведение двухмерных векторов двойной точности, команды SSE4
#define VECTORP2DDDOTPRODUCTSSE4_MC \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )           /* lddqu       xmm0,xmmword ptr [rcx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )           /* lddqu       xmm1,xmmword ptr [rdx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC1,0x31 ) /* dppd        xmm0,xmm1,31h  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// —кал€рное произведение трехмерных векторов двойной точности, команды SSE4
#define VECTORP3DDDOTPRODUCTSSE4_MC \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x0A )           /* lddqu       xmm1,xmmword ptr [rdx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x01 )           /* lddqu       xmm0,xmmword ptr [rcx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x51,0x10 )      /* movsd       xmm2,mmword ptr [rcx+10h]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC1,0x31 ) /* dppd        xmm0,xmm1,31h  */ \
_LINE5( 0xF2,0x0F,0x10,0x4A,0x10 )      /* movsd       xmm1,mmword ptr [rdx+10h]  */ \
_LINE4( 0xF2,0x0F,0x59,0xD1 )           /* mulsd       xmm2,xmm1  */ \
_LINE4( 0xF2,0x0F,0x58,0xC2 )           /* addsd       xmm0,xmm2  */ \
_LINE1( 0xC3 )                          /* ret  */ \
_END_ASM

/// —кал€рное произведение четырехмерных векторов двойной точности, команды SSE4
#define VECTORP4DDDOTPRODUCTSSE4_MC \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )           /* lddqu       xmm0,xmmword ptr [rcx]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x59,0x10 )      /* lddqu       xmm3,xmmword ptr [rcx+10h]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )           /* lddqu       xmm1,xmmword ptr [rdx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC1,0x31 ) /* dppd        xmm0,xmm1,31h  */ \
_LINE5( 0xF2,0x0F,0xF0,0x52,0x10 )      /* lddqu       xmm2,xmmword ptr [rdx+10h]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xDA,0x31 ) /* dppd        xmm3,xmm2,31h  */ \
_LINE4( 0xF2,0x0F,0x58,0xC3 )           /* addsd       xmm0,xmm3  */ \
_LINE1( 0xC3 ) \
_END_ASM

//**************************** DOT PRODUCT System V x64 *********************************
// addition vectors rdi-a void *, rsi-b void *

/// —кал€рное произведение двухмерных векторов одинарной точности, команды SSE4
#define VECTORP2DDOTPRODUCTSSE4_SV \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x07 )           /* movsd       xmm0,mmword ptr [rdi]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0E )           /* movsd       xmm1,mmword ptr [rsi]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC1,0x31 ) /* dpps        xmm0,xmm1,31h  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// —кал€рное произведение трехмерных векторов одинарной точности, команды SSE4
#define VECTORP3DDOTPRODUCTSSE4_SV \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x4E,0x08 )      /* movss       xmm1,dword ptr [rsi+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x47,0x08 )      /* movss       xmm0,dword ptr [rdi+8]  */ \
_LINE3( 0x0F,0x16,0x0E )                /* movhps      xmm1,qword ptr [rsi]  */ \
_LINE3( 0x0F,0x16,0x07 )                /* movhps      xmm0,qword ptr [rdi]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC1,0xD1 ) /* dpps        xmm0,xmm1,0D1h  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// —кал€рное произведение четырехмерных векторов одинарной точности, команды SSE4
#define VECTORP4DDOTPRODUCTSSE4_SV \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x07 )            /* lddqu       xmm0,xmmword ptr [rdi]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0E )            /* lddqu       xmm1,xmmword ptr [rsi]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC1,0xF1 )  /* dpps        xmm0,xmm1,0F1h  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// —кал€рное произведение двухмерных векторов двойной точности, команды SSE4
#define VECTORP2DDDOTPRODUCTSSE4_SV \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x07 )           /* lddqu       xmm0,xmmword ptr [rdi]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0E )           /* lddqu       xmm1,xmmword ptr [rsi]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC1,0x31 ) /* dppd        xmm0,xmm1,31h  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// —кал€рное произведение трехмерных векторов двойной точности, команды SSE4
#define VECTORP3DDDOTPRODUCTSSE4_SV \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x0E )           /* lddqu       xmm1,xmmword ptr [rsi]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x07 )           /* lddqu       xmm0,xmmword ptr [rdi]  */ \
_LINE5( 0xF2,0x0F,0x10,0x57,0x10 )      /* movsd       xmm2,mmword ptr [rdi+10h]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC1,0x31 ) /* dppd        xmm0,xmm1,31h  */ \
_LINE5( 0xF2,0x0F,0x10,0x4E,0x10 )      /* movsd       xmm1,mmword ptr [rsi+10h]  */ \
_LINE4( 0xF2,0x0F,0x59,0xD1 )           /* mulsd       xmm2,xmm1  */ \
_LINE4( 0xF2,0x0F,0x58,0xC2 )           /* addsd       xmm0,xmm2  */ \
_LINE1( 0xC3 )                          /* ret  */ \
_END_ASM

/// —кал€рное произведение четырехмерных векторов двойной точности, команды SSE4
#define VECTORP4DDDOTPRODUCTSSE4_SV \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x07 )           /* lddqu       xmm0,xmmword ptr [rdi]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x5F,0x10 )      /* lddqu       xmm3,xmmword ptr [rdi+10h]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0E )           /* lddqu       xmm1,xmmword ptr [rsi]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC1,0x31 ) /* dppd        xmm0,xmm1,31h  */ \
_LINE5( 0xF2,0x0F,0xF0,0x56,0x10 )      /* lddqu       xmm2,xmmword ptr [rsi+10h]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xDA,0x31 ) /* dppd        xmm3,xmm2,31h  */ \
_LINE4( 0xF2,0x0F,0x58,0xC3 )           /* addsd       xmm0,xmm3  */ \
_LINE1( 0xC3 ) \
_END_ASM

//**************************** DOT all caling conventions *********************************

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
#define VECTORP2DDOTPRODUCTSSE4 VECTORP2DDOTPRODUCTSSE4_MC
#define VECTORP3DDOTPRODUCTSSE4 VECTORP3DDOTPRODUCTSSE4_MC
#define VECTORP4DDOTPRODUCTSSE4 VECTORP4DDOTPRODUCTSSE4_MC
#define VECTORP2DDDOTPRODUCTSSE4 VECTORP2DDDOTPRODUCTSSE4_MC
#define VECTORP3DDDOTPRODUCTSSE4 VECTORP3DDDOTPRODUCTSSE4_MC
#define VECTORP4DDDOTPRODUCTSSE4 VECTORP4DDDOTPRODUCTSSE4_MC
#endif

#ifdef CALLSV
#define VECTORP2DDOTPRODUCTSSE4 VECTORP2DDOTPRODUCTSSE4_SV
#define VECTORP3DDOTPRODUCTSSE4 VECTORP3DDOTPRODUCTSSE4_SV
#define VECTORP4DDOTPRODUCTSSE4 VECTORP4DDOTPRODUCTSSE4_SV
#define VECTORP2DDDOTPRODUCTSSE4 VECTORP2DDDOTPRODUCTSSE4_SV
#define VECTORP3DDDOTPRODUCTSSE4 VECTORP3DDDOTPRODUCTSSE4_SV
#define VECTORP4DDDOTPRODUCTSSE4 VECTORP4DDDOTPRODUCTSSE4_SV
#endif

#endif