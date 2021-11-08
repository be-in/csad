//=============================================================================
///**
// *  @file vector_length2.h
// *
// *  $Id: vector_length2.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float length2, MS Visual C++ 2003-2008
// *
// *  @author Pant_eleymonov Alek_sandr Kons_tantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef CPU_X86_64
#define GEN3_VECTOR_LENGTH2_H
#endif

#ifndef GEN3_VECTOR_LENGTH2_H
#define GEN3_VECTOR_LENGTH2_H

//**************************** LENGTH2 Microsoft x64 *********************************
// vector dot product ecx=[esp+4]-a void * edx=[esp+8]-b void *

///  вадрат длинны двухмерного вектора одинарной точности, команды SSE4
#define VECTORP2DLENGTH2SSE4_MC \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x01 )           /* movsd       xmm0,mmword ptr [rcx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC0,0x31 ) /* dpps        xmm0,xmm0,31h  */ \
_LINE1( 0xC3 ) \
_END_ASM

///  вадрат длинны трехмерного вектора одинарной точности, команды SSE4
#define VECTORP3DLENGTH2SSE4_MC \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x41,0x08 )      /* movss       xmm0,dword ptr [rcx+8]  */ \
_LINE3( 0x0F,0x16,0x01 )                /* movhps      xmm0,qword ptr [rcx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC0,0xD1 ) /* dpps        xmm0,xmm0,0D1h  */ \
_LINE1( 0xC3 ) \
_END_ASM

///  вадрат длинны четырехмерного вектора одинарной точности, команды SSE4
#define VECTORP4DLENGTH2SSE4_MC \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )            /* lddqu       xmm0,xmmword ptr [rcx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC0,0xF1 )  /* dpps        xmm0,xmm0,0F1h  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// —кал€рное произведение двухмерных векторов двойной точности, команды SSE4
#define VECTORP2DDLENGTH2SSE4_MC \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )           /* lddqu       xmm0,xmmword ptr [rcx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC0,0x31 ) /* dppd        xmm0,xmm0,31h  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// —кал€рное произведение трехмерных векторов двойной точности, команды SSE4
#define VECTORP3DDLENGTH2SSE4_MC \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )           /* lddqu       xmm0,xmmword ptr [rcx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x51,0x10 )      /* movsd       xmm2,mmword ptr [rcx+10h]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC0,0x31 ) /* dppd        xmm0,xmm0,31h  */ \
_LINE4( 0xF2,0x0F,0x59,0xD2 )           /* mulsd       xmm2,xmm2  */ \
_LINE4( 0xF2,0x0F,0x58,0xC2 )           /* addsd       xmm0,xmm2  */ \
_LINE1( 0xC3 )                          /* ret  */ \
_END_ASM

/// —кал€рное произведение четырехмерных векторов двойной точности, команды SSE4
#define VECTORP4DDLENGTH2SSE4_MC \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )           /* lddqu       xmm0,xmmword ptr [rcx]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x59,0x10 )      /* lddqu       xmm3,xmmword ptr [rcx+10h]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC0,0x31 ) /* dppd        xmm0,xmm0,31h  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xDB,0x31 ) /* dppd        xmm3,xmm3,31h  */ \
_LINE4( 0xF2,0x0F,0x58,0xC3 )           /* addsd       xmm0,xmm3  */ \
_LINE1( 0xC3 ) \
_END_ASM

//**************************** LENGTH2 System V x64 *********************************
// addition vectors rdi-a void *, rsi-b void *

///  вадрат длинны двухмерного вектора одинарной точности, команды SSE4
#define VECTORP2DLENGTH2SSE4_SV \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x07 )           /* movsd       xmm0,mmword ptr [rdi]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC0,0x31 ) /* dpps        xmm0,xmm0,31h  */ \
_LINE1( 0xC3 ) \
_END_ASM

///  вадрат длинны трехмерного вектора одинарной точности, команды SSE4
#define VECTORP3DLENGTH2SSE4_SV \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x47,0x08 )      /* movss       xmm0,dword ptr [rdi+8]  */ \
_LINE3( 0x0F,0x16,0x07 )                /* movhps      xmm0,qword ptr [rdi]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC0,0xD1 ) /* dpps        xmm0,xmm0,0D1h  */ \
_LINE1( 0xC3 ) \
_END_ASM

///  вадрат длинны четырехмерного вектора одинарной точности, команды SSE4
#define VECTORP4DLENGTH2SSE4_SV \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x07 )            /* lddqu       xmm0,xmmword ptr [rdi]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC0,0xF1 )  /* dpps        xmm0,xmm0,0F1h  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// —кал€рное произведение двухмерных векторов двойной точности, команды SSE4
#define VECTORP2DDLENGTH2SSE4_SV \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x07 )           /* lddqu       xmm0,xmmword ptr [rdi]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC0,0x31 ) /* dppd        xmm0,xmm0,31h  */ \
_LINE1( 0xC3 ) \
_END_ASM

/// —кал€рное произведение трехмерных векторов двойной точности, команды SSE4
#define VECTORP3DDLENGTH2SSE4_SV \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x07 )           /* lddqu       xmm0,xmmword ptr [rdi]  */ \
_LINE5( 0xF2,0x0F,0x10,0x57,0x10 )      /* movsd       xmm2,mmword ptr [rdi+10h]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC0,0x31 ) /* dppd        xmm0,xmm0,31h  */ \
_LINE4( 0xF2,0x0F,0x59,0xD2 )           /* mulsd       xmm2,xmm2  */ \
_LINE4( 0xF2,0x0F,0x58,0xC2 )           /* addsd       xmm0,xmm2  */ \
_LINE1( 0xC3 )                          /* ret  */ \
_END_ASM

/// —кал€рное произведение четырехмерных векторов двойной точности, команды SSE4
#define VECTORP4DDLENGTH2SSE4_SV \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x07 )           /* lddqu       xmm0,xmmword ptr [rdi]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x5F,0x10 )      /* lddqu       xmm3,xmmword ptr [rdi+10h]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC0,0x31 ) /* dppd        xmm0,xmm0,31h  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xDB,0x31 ) /* dppd        xmm3,xmm3,31h  */ \
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
#define VECTORP2DLENGTH2SSE4 VECTORP2DLENGTH2SSE4_MC
#define VECTORP3DLENGTH2SSE4 VECTORP3DLENGTH2SSE4_MC
#define VECTORP4DLENGTH2SSE4 VECTORP4DLENGTH2SSE4_MC
#define VECTORP2DDLENGTH2SSE4 VECTORP2DDLENGTH2SSE4_MC
#define VECTORP3DDLENGTH2SSE4 VECTORP3DDLENGTH2SSE4_MC
#define VECTORP4DDLENGTH2SSE4 VECTORP4DDLENGTH2SSE4_MC
#endif

#ifdef CALLSV
#define VECTORP2DLENGTH2SSE4 VECTORP2DLENGTH2SSE4_SV
#define VECTORP3DLENGTH2SSE4 VECTORP3DLENGTH2SSE4_SV
#define VECTORP4DLENGTH2SSE4 VECTORP4DLENGTH2SSE4_SV
#define VECTORP2DDLENGTH2SSE4 VECTORP2DDLENGTH2SSE4_SV
#define VECTORP3DDLENGTH2SSE4 VECTORP3DDLENGTH2SSE4_SV
#define VECTORP4DDLENGTH2SSE4 VECTORP4DDLENGTH2SSE4_SV
#endif

#endif // GEN3_VECTOR_LENGTH2_H