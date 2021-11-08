//=============================================================================
///**
// *  @file sqrt.h
// *
// *  $Id: sqrt.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float sqrt, MS Visual C++ 2003-2008
// *
// *  @author Pant_eleymonov Alek_sandr Kons_tantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef CPU_X86_64
#define GEN3_SQRT_H
#endif

#ifndef GEN3_SQRT_H
#define GEN3_SQRT_H

//**************************** Sqrt Microsoft x64 *********************************
// vector dot product ecx=[esp+4]-a void * edx=[esp+8]-b void *

/// Вычисление квадратного корня, команды SSE
#define SQRTDSSE_MC \
_BEGIN_ASM \
_LINE4( 0xF3,0x0F,0x51,0xC0 )        /* sqrtss      xmm0,xmm0  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Вычисление обратного квадратного корня, команды SSE
#define FASTINVERTSQRTDSSE_MC \
_BEGIN_ASM \
_LINE4( 0xF3,0x0F,0x52,0xC0 )        /* rsqrtss     xmm0,xmm0  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Вычисление квадратного корня двойной точности, команды SSE2
#define SQRTDDSSE2_MC \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x51,0xC0 )        /* sqrtsd      xmm0,xmm0  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Вычисление обратного квадратного корня двойной точности, команды SSE2
#define FASTINVERTSQRTDDSSE2_MC \
_BEGIN_ASM \
_LINE4( 0x48,0x83,0xEC,0x18 )      /* sub         rsp,18h  */ \
_LINE4( 0xF2,0x0F,0x5A,0xC8 )      /* cvtsd2ss    xmm1,xmm0  */ \
_LINE4( 0xF3,0x0F,0x52,0xD1 )      /* rsqrtss     xmm2,xmm1  */ \
_LINE4( 0xF3,0x0F,0x5A,0xC2 )      /* cvtss2sd    xmm0,xmm2  */ \
_LINE4( 0x48,0x83,0xC4,0x18 )      /* add         rsp,18h  */ \
_LINE1( 0xC3 ) \
_END_ASM

//**************************** LOG2 System V x64 *********************************
// addition vectors rdi-a void *, rsi-b void *

/// Вычисление квадратного корня, команды SSE
#define SQRTDSSE_SV \
_BEGIN_ASM \
_LINE4( 0xF3,0x0F,0x51,0xC0 )        /* sqrtss      xmm0,xmm0  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Вычисление обратного квадратного корня, команды SSE
#define FASTINVERTSQRTDSSE_SV \
_BEGIN_ASM \
_LINE4( 0xF3,0x0F,0x52,0xC0 )        /* rsqrtss     xmm0,xmm0  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Вычисление квадратного корня двойной точности, команды SSE2
#define SQRTDDSSE2_SV \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x51,0xC0 )        /* sqrtsd      xmm0,xmm0  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Вычисление обратного квадратного корня двойной точности, команды SSE2
#define FASTINVERTSQRTDDSSE2_SV \
_BEGIN_ASM \
_LINE4( 0x48,0x83,0xEC,0x18 )      /* sub         rsp,18h  */ \
_LINE4( 0xF2,0x0F,0x5A,0xC8 )      /* cvtsd2ss    xmm1,xmm0  */ \
_LINE4( 0xF3,0x0F,0x52,0xD1 )      /* rsqrtss     xmm2,xmm1  */ \
_LINE4( 0xF3,0x0F,0x5A,0xC2 )      /* cvtss2sd    xmm0,xmm2  */ \
_LINE4( 0x48,0x83,0xC4,0x18 )      /* add         rsp,18h  */ \
_LINE1( 0xC3 ) \
_END_ASM

//**************************** LOG2 all caling conventions *********************************

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
#define SQRTDSSE SQRTDSSE_MC
#define FASTINVERTSQRTDSSE FASTINVERTSQRTDSSE_MC
#define SQRTDDSSE2 SQRTDDSSE2_MC
#define FASTINVERTSQRTDDSSE2 FASTINVERTSQRTDDSSE2_MC
#endif

#ifdef CALLSV
#define SQRTDSSE SQRTDSSE_SV
#define FASTINVERTSQRTDSSE FASTINVERTSQRTDSSE_SV
#define SQRTDDSSE2 SQRTDDSSE2_SV
#define FASTINVERTSQRTDDSSE2 FASTINVERTSQRTDDSSE2_SV
#endif

#endif // GEN3_SQRT_H

