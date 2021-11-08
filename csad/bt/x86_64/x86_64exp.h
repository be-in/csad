//=============================================================================
///**
// *  @file exp.h
// *
// *  $Id: exp.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float exp, MS Visual C++ 2003-2008
// *
// *  @author Pant_eleymonov Alek_sandr Kons_tantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef CPU_X86_64
#define GEN3_LOG2_H
#endif

#ifndef GEN3_LOG2_H
#define GEN3_LOG2_H

//**************************** Exp Microsoft x64 *********************************
// vector dot product ecx=[esp+4]-a void * edx=[esp+8]-b void *

/// Вычисление целочисленного логарифмического размера, команды SSE2
#define EXTLOG2ISIZESSE2_MC \
_BEGIN_ASM \
_LINE5( 0xB8,0x01,0x00,0x00,0x00 )          /* mov         eax,1  */ \
_LINE2( 0xFF,0xC9 )                         /* dec         ecx  */ \
_LINE2( 0x7F,0x01 )                         /* jg          eee  */ \
_LINE1( 0xC3 )                              /* ret         */ \
_LINE4( 0xF2,0x0F,0x2A,0xC1 )               /* cvtsi2sd    xmm0,ecx  */ \
_LINE5( 0xB8,0x02,0x00,0x00,0x00 )          /* mov         eax,2  */ \
_LINE5( 0x66,0x0F,0x73,0xF0,0x01 )          /* psllq       xmm0,1  */ \
_LINE5( 0x66,0x0F,0x73,0xD0,0x35 )          /* psrlq       xmm0,35h  */ \
_LINE4( 0x66,0x0F,0x7E,0xC1 )               /* movd        ecx,xmm0  */ \
_LINE6( 0x81,0xE9,0xFF,0x03,0x00,0x00 )     /* sub         ecx,3FFh  */ \
_LINE2( 0xD3,0xE0 )                         /* shl         eax,cl  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Вычисление целочисленного логарифма, команды SSE2
#define MATHLOG2ISS2_MC \
_BEGIN_ASM \
_LINE2( 0x33,0xC0 )                         /* xor         eax,eax  */ \
_LINE2( 0x85,0xC9 )                         /* test        ecx,ecx  */ \
_LINE2( 0x7F,0x01 )                         /* jg          eee  */ \
_LINE1( 0xC3 )                              /* ret         */ \
_LINE4( 0xF2,0x0F,0x2A,0xC1 )               /* cvtsi2sd    xmm0,ecx  */ \
_LINE5( 0x66,0x0F,0x73,0xF0,0x01 )          /* psllq       xmm0,1  */ \
_LINE5( 0x66,0x0F,0x73,0xD0,0x35 )          /* psrlq       xmm0,35h  */ \
_LINE4( 0x66,0x0F,0x7E,0xC0 )               /* movd        eax,xmm0  */ \
_LINE5( 0x2D,0xFF,0x03,0x00,0x00 )          /* sub         eax,3FFh  */ \
_LINE1( 0xC3 ) \
_END_ASM

//**************************** LOG2 System V x64 *********************************
// addition vectors rdi-a void *, rsi-b void *

/// Вычисление целочисленного логарифмического размера, команды SSE2
#define EXTLOG2ISIZESSE2_SV \
_BEGIN_ASM \
_LINE5( 0xB8,0x01,0x00,0x00,0x00 )          /* mov         eax,1  */ \
_LINE2( 0xFF,0xCF )                         /* dec         edi  */ \
_LINE2( 0x7F,0x01 )                         /* jg          eee  */ \
_LINE1( 0xC3 )                              /* ret         */ \
_LINE4( 0xF2,0x0F,0x2A,0xC7 )               /* cvtsi2sd    xmm0,edi  */ \
_LINE5( 0xB8,0x02,0x00,0x00,0x00 )          /* mov         eax,2  */ \
_LINE5( 0x66,0x0F,0x73,0xF0,0x01 )          /* psllq       xmm0,1  */ \
_LINE5( 0x66,0x0F,0x73,0xD0,0x35 )          /* psrlq       xmm0,35h  */ \
_LINE4( 0x66,0x0F,0x7E,0xC1 )               /* movd        ecx,xmm0  */ \
_LINE6( 0x81,0xE9,0xFF,0x03,0x00,0x00 )     /* sub         ecx,3FFh  */ \
_LINE2( 0xD3,0xE0 )                         /* shl         eax,cl  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// Вычисление целочисленного логарифма, команды SSE2
#define MATHLOG2ISS2_SV \
_BEGIN_ASM \
_LINE2( 0x33,0xC0 )                         /* xor         eax,eax  */ \
_LINE2( 0x85,0xFF )                         /* test        edi,edi  */ \
_LINE2( 0x7F,0x01 )                         /* jg          eee  */ \
_LINE1( 0xC3 )                              /* ret         */ \
_LINE4( 0xF2,0x0F,0x2A,0xC7 )               /* cvtsi2sd    xmm0,edi  */ \
_LINE5( 0x66,0x0F,0x73,0xF0,0x01 )          /* psllq       xmm0,1  */ \
_LINE5( 0x66,0x0F,0x73,0xD0,0x35 )          /* psrlq       xmm0,35h  */ \
_LINE4( 0x66,0x0F,0x7E,0xC0 )               /* movd        eax,xmm0  */ \
_LINE5( 0x2D,0xFF,0x03,0x00,0x00 )          /* sub         eax,3FFh  */ \
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
#define EXTLOG2ISIZESSE2 EXTLOG2ISIZESSE2_MC
#define MATHLOG2ISS2 MATHLOG2ISS2_MC
#endif

#ifdef CALLSV
#define EXTLOG2ISIZESSE2 EXTLOG2ISIZESSE2_SV
#define MATHLOG2ISS2 MATHLOG2ISS2_SV
#endif

#endif // GEN3_LOG2_H