//=============================================================================
///**
// *  @file quaternion_mul.h
// *
// *  $Id: quaternion_mul.h 16.10.2011  $
// *
// *  @brief generator 3, assembler quaternion double/float mul, MS Visual C++ 2003-2008
// *
// *  @author Pant_eleymonov Alek_sandr Kons_tantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_QUATERNION_MUL_H
#define GEN3_QUATERNION_MUL_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** MUL STDCALL *********************************
// mul quaternion eax=[esp+4]-a void *, [esp+8]-b void *  [esp+12]-c void *

/// Умножение кватернионa на кватернион одинарной точности, команды SSE
#define QUATERNIONPDMULSSE_STD \
_BEGIN_ASM \
ASM( mov edx,[esp+8] ) \
ASM( movlps xmm0,[edx] ) \
ASM( mov eax,[esp+4] ) \
ASM( movss xmm6,[eax] ) \
ASM( movhps xmm0,[edx+8] ) \
ASM( shufps xmm6,xmm6,0 ) \
ASM( movss xmm7,[eax+4] ) \
ASM( xorps xmm1,xmm1 ) \
ASM( movss xmm5,[eax+12] ) \
ASM( shufps xmm7,xmm7,0 ) \
ASM( subps xmm1,xmm0 ) \
ASM( shufps xmm5,xmm5,0 ) \
ASM( movaps xmm2,xmm0 ) \
ASM( movaps xmm3,xmm1 ) \
ASM( movss xmm4,[eax+8] ) \
ASM( shufps xmm3,xmm0,0xC9 ) \
ASM( shufps xmm2,xmm1,0x27 ) \
ASM( mulps xmm5,xmm0 ) \
ASM( shufps xmm2,xmm2,0xD8 ) \
ASM( shufps xmm0,xmm1,0x4E ) \
ASM( shufps xmm4,xmm4,0 ) \
ASM( mulps xmm7,xmm0 ) \
ASM( shufps xmm3,xmm3,0x78 ) \
ASM( mulps xmm6,xmm2 ) \
ASM( shufps xmm0,xmm1,0x4E ) \
ASM( mulps xmm4,xmm3 ) \
ASM( addps xmm6,xmm7 ) \
ASM( addps xmm4,xmm5 ) \
ASM( mov eax,[esp+12] ) \
ASM( addps xmm6,xmm4 ) \
ASM( movlps [eax],xmm6 ) \
ASM( movhps [eax+8],xmm6 ) \
_END_ASM

/// Умножение кватернионa на кватернион одинарной точности, команды SSE3
#define QUATERNIONPDMULSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x08 )        /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )        /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x02 )        /* lddqu       xmm0,xmmword ptr [edx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x38 )        /* lddqu       xmm7,xmmword ptr [eax]  */ \
_LINE3( 0x0F,0x57,0xC9 )             /* xorps       xmm1,xmm1  */ \
_LINE3( 0x0F,0x12,0xD0 )             /* movhlps     xmm2,xmm0  */ \
_LINE4( 0xF3,0x0F,0x12,0xF7 )        /* movsldup    xmm6,xmm7  */ \
_LINE3( 0x0F,0x5C,0xC8 )             /* subps       xmm1,xmm0  */ \
_LINE4( 0xF3,0x0F,0x16,0xFF )        /* movshdup    xmm7,xmm7  */ \
_LINE4( 0x0F,0xC6,0xC1,0x44 )        /* shufps      xmm0,xmm1,44h  */ \
_LINE3( 0x0F,0x16,0xD2 )             /* movlhps     xmm2,xmm2  */ \
_LINE3( 0x0F,0x28,0xD8 )             /* movaps      xmm3,xmm0  */ \
_LINE4( 0x0F,0xC6,0xCA,0x5A )        /* shufps      xmm1,xmm2,5Ah  */ \
_LINE4( 0x0F,0xC6,0xDB,0x93 )        /* shufps      xmm3,xmm3,93h  */ \
_LINE4( 0x0F,0xC6,0xC9,0x22 )        /* shufps      xmm1,xmm1,22h  */ \
_LINE3( 0x0F,0x59,0xD7 )             /* mulps       xmm2,xmm7  */ \
_LINE3( 0x0F,0x59,0xCE )             /* mulps       xmm1,xmm6  */ \
_LINE4( 0x0F,0xC6,0xFF,0x4E )        /* shufps      xmm7,xmm7,4Eh  */ \
_LINE4( 0x0F,0xC6,0xF6,0x4E )        /* shufps      xmm6,xmm6,4Eh  */ \
_LINE3( 0x0F,0x59,0xC7 )             /* mulps       xmm0,xmm7  */ \
_LINE3( 0x0F,0x59,0xDE )             /* mulps       xmm3,xmm6  */ \
_LINE3( 0x0F,0x58,0xD0 )             /* addps       xmm2,xmm0  */ \
_LINE3( 0x0F,0x58,0xCB )             /* addps       xmm1,xmm3  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )        /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE3( 0x0F,0x58,0xD1 )             /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x13,0x10 )             /* movlps      qword ptr [eax],xmm2  */ \
_LINE4( 0x0F,0x17,0x50,0x08 )        /* movhps      qword ptr [eax+8],xmm2  */ \
_END_ASM

/// Умножение кватернионa на кватернион одинарной точности, команды SSE4 ???
#define QUATERNIONPDMULSSE4_STD \
_BEGIN_ASM \
ASM( mov edx,[esp+8] ) \
ASM( mov eax,[esp+4] ) \
ASM( lddqu xmm0,[edx] ) \
ASM( lddqu xmm7,[eax] ) \
ASM( xorps xmm1,xmm1 ) \
ASM( movhlps xmm2,xmm0 ) \
ASM( movsldup xmm6,xmm7 ) \
ASM( subps xmm1,xmm0 ) \
ASM( movshdup xmm7,xmm7 ) \
ASM( shufps xmm0,xmm1,0x44 ) \
ASM( movlhps xmm2,xmm2 ) \
ASM( movaps xmm3,xmm0 ) \
ASM( shufps xmm1,xmm2,0x5A ) \
ASM( shufps xmm3,xmm3,0x93 ) \
ASM( shufps xmm1,xmm1,0x22 ) \
ASM( mulps xmm2,xmm7 ) \
ASM( mulps xmm1,xmm6 ) \
ASM( shufps xmm7,xmm7,0x4E ) \
ASM( shufps xmm6,xmm6,0x4E ) \
ASM( mulps xmm0,xmm7 ) \
ASM( mulps xmm3,xmm6 ) \
ASM( addps xmm2,xmm0 ) \
ASM( addps xmm1,xmm3 ) \
ASM( mov eax,[esp+12] ) \
ASM( addps xmm2,xmm1 ) \
ASM( movupd [eax],xmm2 ) \
_END_ASM

/// Умножение кватернионa на кватернион двойной точности, команды SSE2
#define QUATERNIONPDDMULSSE2_STD \
_BEGIN_ASM \
ASM( mov edx,[esp+8] ) \
ASM( movlps xmm0,[edx] ) \
ASM( mov eax,[esp+4] ) \
ASM( movlps xmm6,[eax] ) \
ASM( movhps xmm0,[edx+8] ) \
ASM( unpcklpd xmm6,xmm6 ) \
ASM( xorps xmm2,xmm2 ) \
ASM( movlps xmm7,[eax+8] ) \
ASM( movlps xmm1,[edx+16] ) \
ASM( unpcklpd xmm7,xmm7 ) \
ASM( xorps xmm3,xmm3 ) \
ASM( movhps xmm1,[edx+24] ) \
ASM( subpd xmm2,xmm0 ) \
ASM( subpd xmm3,xmm1 ) \
ASM( movlhps xmm3,xmm3 ) \
ASM( movhlps xmm4,xmm0 ) \
ASM( movhlps xmm3,xmm1 ) \
ASM( movlhps xmm5,xmm0 ) \
ASM( movlhps xmm4,xmm2 ) \
ASM( movhlps xmm5,xmm2 ) \
ASM( mulpd xmm4,xmm6 ) \
ASM( mulpd xmm2,xmm7 ) \
ASM( mulpd xmm6,xmm3 ) \
ASM( mulpd xmm7,xmm1 ) \
ASM( addpd xmm2,xmm4 ) \
ASM( addpd xmm6,xmm7 ) \
ASM( movlps xmm4,[eax+16] ) \
ASM( movlps xmm7,[eax+24] ) \
ASM( unpcklpd xmm4,xmm4 ) \
ASM( unpcklpd xmm7,xmm7 ) \
ASM( mulpd xmm5,xmm4 ) \
ASM( mulpd xmm0,xmm7 ) \
ASM( mulpd xmm4,xmm3 ) \
ASM( mulpd xmm7,xmm1 ) \
ASM( addpd xmm0,xmm5 ) \
ASM( addpd xmm7,xmm4 ) \
ASM( addpd xmm6,xmm0 ) \
ASM( mov eax,[esp+12] ) \
ASM( addpd xmm2,xmm7 ) \
ASM( movlps [eax],xmm6 ) \
ASM( movlps [eax+16],xmm2 ) \
ASM( movhps [eax+8],xmm6 ) \
ASM( movhps [eax+24],xmm2 ) \
_END_ASM

/// Умножение кватернионa на кватернион двойной точности, команды SSE3
#define QUATERNIONPDDMULSSE3_STD \
_BEGIN_ASM \
ASM( mov edx,[esp+8] ) \
ASM( lddqu xmm0,[edx] ) \
ASM( mov eax,[esp+4] ) \
ASM( movddup xmm6,[eax] ) \
ASM( xorps xmm2,xmm2 ) \
ASM( movddup xmm7,[eax+8] ) \
ASM( lddqu xmm1,[edx+16] ) \
ASM( xorps xmm3,xmm3 ) \
ASM( subpd xmm2,xmm0 ) \
ASM( subpd xmm3,xmm1 ) \
ASM( movlhps xmm3,xmm3 ) \
ASM( movhlps xmm4,xmm0 ) \
ASM( movhlps xmm3,xmm1 ) \
ASM( movlhps xmm5,xmm0 ) \
ASM( movlhps xmm4,xmm2 ) \
ASM( movhlps xmm5,xmm2 ) \
ASM( mulpd xmm4,xmm6 ) \
ASM( mulpd xmm2,xmm7 ) \
ASM( mulpd xmm6,xmm3 ) \
ASM( mulpd xmm7,xmm1 ) \
ASM( addpd xmm2,xmm4 ) \
ASM( addpd xmm6,xmm7 ) \
ASM( movddup xmm4,[eax+16] ) \
ASM( movddup xmm7,[eax+24] ) \
ASM( mulpd xmm5,xmm4 ) \
ASM( mulpd xmm0,xmm7 ) \
ASM( mulpd xmm4,xmm3 ) \
ASM( mulpd xmm7,xmm1 ) \
ASM( addpd xmm0,xmm5 ) \
ASM( addpd xmm7,xmm4 ) \
ASM( addpd xmm6,xmm0 ) \
ASM( mov eax,[esp+12] ) \
ASM( addpd xmm2,xmm7 ) \
ASM( movlps [eax],xmm6 ) \
ASM( movlps [eax+16],xmm2 ) \
ASM( movhps [eax+8],xmm6 ) \
ASM( movhps [eax+24],xmm2 ) \
_END_ASM

/// Умножение кватернионa на кватернион двойной точности, команды SSE4
#define QUATERNIONPDDMULSSE4_STD \
_BEGIN_ASM \
ASM( mov edx,[esp+8] ) \
ASM( lddqu xmm0,[edx] ) \
ASM( mov eax,[esp+4] ) \
ASM( movddup xmm6,[eax] ) \
ASM( xorps xmm2,xmm2 ) \
ASM( movddup xmm7,[eax+8] ) \
ASM( lddqu xmm1,[edx+16] ) \
ASM( xorps xmm3,xmm3 ) \
ASM( subpd xmm2,xmm0 ) \
ASM( subpd xmm3,xmm1 ) \
ASM( movlhps xmm3,xmm3 ) \
ASM( movhlps xmm4,xmm0 ) \
ASM( movhlps xmm3,xmm1 ) \
ASM( movlhps xmm5,xmm0 ) \
ASM( movlhps xmm4,xmm2 ) \
ASM( movhlps xmm5,xmm2 ) \
ASM( mulpd xmm4,xmm6 ) \
ASM( mulpd xmm2,xmm7 ) \
ASM( mulpd xmm6,xmm3 ) \
ASM( mulpd xmm7,xmm1 ) \
ASM( addpd xmm2,xmm4 ) \
ASM( addpd xmm6,xmm7 ) \
ASM( movddup xmm4,[eax+16] ) \
ASM( movddup xmm7,[eax+24] ) \
ASM( mulpd xmm5,xmm4 ) \
ASM( mulpd xmm0,xmm7 ) \
ASM( mulpd xmm4,xmm3 ) \
ASM( mulpd xmm7,xmm1 ) \
ASM( addpd xmm0,xmm5 ) \
ASM( addpd xmm7,xmm4 ) \
ASM( addpd xmm6,xmm0 ) \
ASM( mov eax,[esp+12] ) \
ASM( addpd xmm2,xmm7 ) \
ASM( movupd [eax],xmm6 ) \
ASM( movupd [eax+16],xmm2 ) \
_END_ASM

#endif
