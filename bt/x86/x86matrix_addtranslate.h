//=============================================================================
///**
// *  @file   matrix_addtranslate.h
// *
// *  $Id: matrix_addtranslate.h 16.10.2011  $
// *
// *  @brief generator 3, assembler matrix double/float addtranslate, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_MATRIX_ADDTRANSLATE_H_
#define GEN3_MATRIX_ADDTRANSLATE_H_

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

/// Умножение на матрицу переноса одинарной точности, команды SSE
#define MATRIXP4DADDTRANSLATESSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )          /* mov         edx,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )          /* mov         eax,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x12,0x00 )               /* movlps      xmm0,qword ptr [eax]  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x08 )     /* movss       xmm1,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x12,0x22 )               /* movlps      xmm4,qword ptr [edx]  */ \
_LINE4( 0x0F,0x12,0x6A,0x10 )          /* movlps      xmm5,qword ptr [edx+10h]  */ \
_LINE4( 0x0F,0x16,0x62,0x08 )          /* movhps      xmm4,qword ptr [edx+8]  */ \
_LINE4( 0x0F,0x16,0x6A,0x18 )          /* movhps      xmm5,qword ptr [edx+18h]  */ \
_LINE3( 0x0F,0x28,0xD8 )               /* movaps      xmm3,xmm0  */ \
_LINE4( 0x0F,0x12,0x72,0x20 )          /* movlps      xmm6,qword ptr [edx+20h]  */ \
_LINE4( 0x0F,0x12,0x7A,0x30 )          /* movlps      xmm7,qword ptr [edx+30h]  */ \
_LINE4( 0x0F,0x16,0x72,0x28 )          /* movhps      xmm6,qword ptr [edx+28h]  */ \
_LINE4( 0x0F,0x16,0x7A,0x38 )          /* movhps      xmm7,qword ptr [edx+38h]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x0 )           /* shufps      xmm1,xmm1,0h  */ \
_LINE4( 0x0F,0xC6,0xC0,0x0 )           /* shufps      xmm0,xmm0,0h  */ \
_LINE4( 0x0F,0xC6,0xDB,0x55 )          /* shufps      xmm3,xmm3,55h  */ \
_LINE3( 0x0F,0x59,0xC4 )               /* mulps       xmm0,xmm4  */ \
_LINE3( 0x0F,0x59,0xDD )               /* mulps       xmm3,xmm5  */ \
_LINE3( 0x0F,0x59,0xCE )               /* mulps       xmm1,xmm6  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )          /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE3( 0x0F,0x58,0xC3 )               /* addps       xmm0,xmm3  */ \
_LINE3( 0x0F,0x58,0xF9 )               /* addps       xmm7,xmm1  */ \
_LINE3( 0x0F,0x13,0x20 )               /* movlps      qword ptr [eax],xmm4  */ \
_LINE4( 0x0F,0x13,0x68,0x10 )          /* movlps      qword ptr [eax+10h],xmm5  */ \
_LINE4( 0x0F,0x17,0x60,0x08 )          /* movhps      qword ptr [eax+8],xmm4  */ \
_LINE4( 0x0F,0x17,0x68,0x18 )          /* movhps      qword ptr [eax+18h],xmm5  */ \
_LINE3( 0x0F,0x58,0xF8 )               /* addps       xmm7,xmm0  */ \
_LINE4( 0x0F,0x13,0x70,0x20 )          /* movlps      qword ptr [eax+20h],xmm6  */ \
_LINE4( 0x0F,0x13,0x78,0x30 )          /* movlps      qword ptr [eax+30h],xmm7  */ \
_LINE4( 0x0F,0x17,0x70,0x28 )          /* movhps      qword ptr [eax+28h],xmm6  */ \
_LINE4( 0x0F,0x17,0x78,0x38 )          /* movhps      qword ptr [eax+38h],xmm7  */ \
_END_ASM

/// Умножение на матрицу переноса одинарной точности, команды SSE4
#define MATRIXP4DADDTRANSLATESSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )          /* mov         edx,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )          /* mov         eax,dword ptr [esp+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x08 )     /* movss       xmm1,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x12,0x00 )               /* movlps      xmm0,qword ptr [eax]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x22 )          /* lddqu       xmm4,xmmword ptr [edx]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x6A,0x10 )     /* lddqu       xmm5,xmmword ptr [edx+10h]  */ \
_LINE3( 0x0F,0x28,0xD8 )               /* movaps      xmm3,xmm0  */ \
_LINE5( 0xF2,0x0F,0xF0,0x72,0x20 )     /* lddqu       xmm6,xmmword ptr [edx+20h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x7A,0x30 )     /* lddqu       xmm7,xmmword ptr [edx+30h]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x0 )           /* shufps      xmm1,xmm1,0h  */ \
_LINE4( 0x0F,0xC6,0xC0,0x0 )           /* shufps      xmm0,xmm0,0h  */ \
_LINE4( 0x0F,0xC6,0xDB,0x55 )          /* shufps      xmm3,xmm3,55h  */ \
_LINE3( 0x0F,0x59,0xC4 )               /* mulps       xmm0,xmm4  */ \
_LINE3( 0x0F,0x59,0xDD )               /* mulps       xmm3,xmm5  */ \
_LINE3( 0x0F,0x59,0xCE )               /* mulps       xmm1,xmm6  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )          /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE3( 0x0F,0x58,0xC3 )               /* addps       xmm0,xmm3  */ \
_LINE3( 0x0F,0x58,0xF9 )               /* addps       xmm7,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x20 )          /* movupd      xmmword ptr [eax],xmm4  */ \
_LINE5( 0x66,0x0F,0x11,0x68,0x10 )     /* movupd      xmmword ptr [eax+10h],xmm5  */ \
_LINE3( 0x0F,0x58,0xF8 )               /* addps       xmm7,xmm0  */ \
_LINE5( 0x66,0x0F,0x11,0x70,0x20 )     /* movupd      xmmword ptr [eax+20h],xmm6  */ \
_LINE5( 0x66,0x0F,0x11,0x78,0x30 )     /* movupd      xmmword ptr [eax+30h],xmm7  */ \
_END_ASM

/// Перенос матрици одинарной точности, команды SSE4 ??
#define MATRIXP4DDADDTRANSLATESSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )          /* mov         edx,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )          /* mov         eax,dword ptr [esp+8]  */ \
ASM( lddqu xmm0,[eax] ) \
ASM( MOVDDUP xmm1,[eax+16] ) \
_LINE4( 0xF2,0x0F,0xF0,0x22 )          /* lddqu       xmm4,xmmword ptr [edx]  */ \
ASM( MOVDDUP xmm5,[edx+0x18] ) \
_LINE5( 0xF2,0x0F,0xF0,0x72,0x20 )     /* lddqu       xmm6,xmmword ptr [edx+20h]  */ \
ASM( MOVDDUP xmm7,[edx+0x38] ) \
_LINE4( 0x8B,0x44,0x24,0x0C )          /* mov         eax,dword ptr [esp+0Ch]  */ \
ASM( movaps xmm2,xmm5 ) \
ASM( movaps xmm3,xmm7 ) \
ASM( mulpd xmm2,xmm0 ) \
ASM( mulpd xmm3,xmm0 ) \
ASM( addpd xmm4,xmm2 ) \
ASM( addpd xmm6,xmm3 ) \
_LINE4( 0x66,0x0F,0x11,0x20 )          /* movupd      xmmword ptr [eax],xmm4  */ \
_LINE5( 0x66,0x0F,0x11,0x70,0x20 )     /* movupd      xmmword ptr [eax+20h],xmm6  */ \
ASM( movlps xmm3,[edx+0x10] ) \
ASM( movhps xmm3,[edx+0x30] ) \
ASM( movaps xmm2,xmm3 ) \
ASM( mulpd xmm3,xmm1 ) \
ASM( addpd xmm2,xmm3 ) \
ASM( movhlps xmm7,xmm2 ) \
ASM( movlhps xmm2,xmm5 ) \
_LINE5( 0x66,0x0F,0x11,0x50,0x10 )     /* movupd      xmmword ptr [eax+10h],xmm2  */ \
_LINE5( 0x66,0x0F,0x11,0x78,0x30 )     /* movupd      xmmword ptr [eax+30h],xmm7  */ \
_LINE5( 0xF2,0x0F,0xF0,0x62,0x40 )     /* lddqu       xmm4,xmmword ptr [edx+40h]  */ \
ASM( MOVDDUP xmm5,[edx+0x58] ) \
_LINE5( 0xF2,0x0F,0xF0,0x72,0x60 )     /* lddqu       xmm6,xmmword ptr [edx+60h]  */ \
ASM( MOVDDUP xmm7,[edx+0x78] ) \
ASM( movaps xmm2,xmm5 ) \
ASM( movaps xmm3,xmm7 ) \
ASM( mulpd xmm2,xmm0 ) \
ASM( mulpd xmm3,xmm0 ) \
ASM( addpd xmm4,xmm2 ) \
ASM( addpd xmm6,xmm3 ) \
_LINE5( 0x66,0x0F,0x11,0x60,0x40 )     /* movupd      xmmword ptr [eax+40h],xmm4  */ \
_LINE5( 0x66,0x0F,0x11,0x70,0x60 )     /* movupd      xmmword ptr [eax+60h],xmm6  */ \
ASM( movlps xmm3,[edx+0x50] ) \
ASM( movhps xmm3,[edx+0x70] ) \
ASM( movaps xmm2,xmm3 ) \
ASM( mulpd xmm3,xmm1 ) \
ASM( addpd xmm2,xmm3 ) \
ASM( movhlps xmm7,xmm2 ) \
ASM( movlhps xmm2,xmm5 ) \
_LINE5( 0x66,0x0F,0x11,0x50,0x50 )     /* movupd      xmmword ptr [eax+50h],xmm2  */ \
_LINE5( 0x66,0x0F,0x11,0x78,0x70 )     /* movupd      xmmword ptr [eax+70h],xmm7  */ \
_END_ASM

#endif /* X86MATRIX_ADDTRANSLATE_H_ */
