//=============================================================================
///**
// *  @file   vector_add.h
// *
// *  $Id: vector_add.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float addition, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_MATH_SINCOS_H
#define GEN3_MATH_SINCOS_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** SINCOS STDCALL *********************************
// sin cos [esp+4]-a float, eax=[esp+8]-b void *, edx=[esp+12]-c void *

/// Вычисление синуса и косинуса одинарной точности, команды SSE.
#define MATHPDSINCOSSSE_STD \
_BEGIN_ASM \
ASM( mov eax,-1 ) \
ASM( CVTSI2SS xmm5,eax ) \
ASM( mov edx,1 ) \
ASM( CVTSI2SS xmm0,edx ) \
ASM( lea ecx,[esp-0x48] ) \
ASM( and ecx,0xFFFFFFF0 ) \
ASM( mov eax,0x3f000000 ) \
ASM( mov edx,0x3e2aaaab ) \
ASM( movss xmm1,[esp+4] ) \
ASM( mov [ecx],eax) \
ASM( mov [ecx+0x4],edx) \
ASM( xorps xmm3,xmm3 ) \
ASM( mov eax,0x3d2aaaab ) \
ASM( mov edx,0x3c088889 ) \
ASM( movss xmm3,xmm1 ) \
ASM( mov [ecx+0x8],eax) \
ASM( mov [ecx+0xC],edx) \
ASM( mulss xmm3,xmm3 ) \
ASM( mov eax,0x3ab60b61 ) \
ASM( mov edx,0x39500d01 ) \
ASM( shufps xmm1,xmm3,0x00 ) \
ASM( mov [ecx+0x10],eax) \
ASM( mov [ecx+0x14],edx) \
ASM( movss xmm4,xmm3 ) \
ASM( mov eax,0x37d00d01 ) \
ASM( mov edx,0x3638ef1d ) \
ASM( mulss xmm3,xmm3 ) \
ASM( mov [ecx+0x18],eax) \
ASM( mov [ecx+0x1C],edx) \
ASM( shufps xmm4,xmm3,0x00 ) \
ASM( mov eax,0x3493f27e ) \
ASM( mov edx,0x32d7322b ) \
ASM( shufps xmm4,xmm1,0x08 ) \
ASM( mov [ecx+0x20],eax) \
ASM( mov [ecx+0x24],edx) \
ASM( shufps xmm4,xmm4,0x42 ) \
ASM( mov eax,0x310f76c7 ) \
ASM( mov edx,0x2f309231 ) \
ASM( shufps xmm1,xmm1,0x20 ) \
ASM( mov [ecx+0x28],eax) \
ASM( mov [ecx+0x2C],edx) \
ASM( mulps xmm1,xmm4 ) \
ASM( mov eax,0x2d49cba6 ) \
ASM( mov edx,0x2b573f9f ) \
ASM( shufps xmm5,xmm0,0x00 ) \
ASM( mov [ecx+0x30],eax) \
ASM( mov [ecx+0x34],edx) \
ASM( shufps xmm3,xmm3,0x00 ) \
ASM( mov eax,0x29573f9f ) \
ASM( mov edx,0x274a963c ) \
ASM( movlhps xmm0,xmm4 ) \
ASM( mov [ecx+0x38],eax) \
ASM( mov [ecx+0x3C],edx) \
ASM( mulps xmm1,xmm5 ) \
ASM( shufps xmm0,xmm0,0x88 ) \
ASM( movlps xmm2,[ecx] ) \
ASM( movlps xmm4,[ecx+0x10] ) \
ASM( movhps xmm2,[ecx+0x08] ) \
ASM( movhps xmm4,[ecx+0x18] ) \
ASM( mulps xmm2,xmm1 ) \
ASM( mulps xmm1,xmm3 ) \
ASM( mulps xmm4,xmm1 ) \
ASM( movlps xmm5,[ecx+0x20] ) \
ASM( movlps xmm6,[ecx+0x30] ) \
ASM( addps xmm2,xmm4 ) \
ASM( mulps xmm1,xmm3 ) \
ASM( movhps xmm5,[ecx+0x28] ) \
ASM( movhps xmm6,[ecx+0x38] ) \
ASM( mulps xmm5,xmm1 ) \
ASM( mov eax,[esp+8] ) \
ASM( mulps xmm1,xmm3 ) \
ASM( addps xmm2,xmm5 ) \
ASM( mulps xmm6,xmm1 ) \
ASM( mov edx,[esp+12] ) \
ASM( addps xmm2,xmm6 ) \
ASM( movhlps xmm1,xmm2 ) \
ASM( addps xmm2,xmm1 ) \
ASM( addps xmm2,xmm0 ) \
ASM( movss [eax],xmm2 ) \
ASM( shufps xmm2,xmm2,0x1 ) \
ASM( movss [edx],xmm2 ) \
_END_ASM

/// Вычисление синуса и косинуса одинарной точности, команды SSE2.
#define MATHPDSINCOSSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,-1 ) \
ASM( CVTSI2SS xmm5,eax ) \
ASM( mov edx,1 ) \
ASM( CVTSI2SS xmm0,edx ) \
ASM( lea ecx,[esp-0x48] ) \
ASM( and ecx,0xFFFFFFF0 ) \
ASM( mov eax,0x3f000000 ) \
ASM( mov edx,0x3e2aaaab ) \
ASM( movss xmm1,[esp+4] ) \
ASM( mov [ecx],eax) \
ASM( mov [ecx+0x4],edx) \
ASM( xorps xmm3,xmm3 ) \
ASM( mov eax,0x3d2aaaab ) \
ASM( mov edx,0x3c088889 ) \
ASM( movss xmm3,xmm1 ) \
ASM( mov [ecx+0x8],eax) \
ASM( mov [ecx+0xC],edx) \
ASM( mulss xmm3,xmm3 ) \
ASM( mov eax,0x3ab60b61 ) \
ASM( mov edx,0x39500d01 ) \
ASM( shufps xmm1,xmm3,0x00 ) \
ASM( mov [ecx+0x10],eax) \
ASM( mov [ecx+0x14],edx) \
ASM( movss xmm4,xmm3 ) \
ASM( mov eax,0x37d00d01 ) \
ASM( mov edx,0x3638ef1d ) \
ASM( mulss xmm3,xmm3 ) \
ASM( mov [ecx+0x18],eax) \
ASM( mov [ecx+0x1C],edx) \
ASM( shufps xmm4,xmm3,0x00 ) \
ASM( mov eax,0x3493f27e ) \
ASM( mov edx,0x32d7322b ) \
ASM( shufps xmm4,xmm1,0x08 ) \
ASM( mov [ecx+0x20],eax) \
ASM( mov [ecx+0x24],edx) \
ASM( shufps xmm4,xmm4,0x42 ) \
ASM( mov eax,0x310f76c7 ) \
ASM( mov edx,0x2f309231 ) \
ASM( shufps xmm1,xmm1,0x20 ) \
ASM( mov [ecx+0x28],eax) \
ASM( mov [ecx+0x2C],edx) \
ASM( mulps xmm1,xmm4 ) \
ASM( mov eax,0x2d49cba6 ) \
ASM( mov edx,0x2b573f9f ) \
ASM( shufps xmm5,xmm0,0x00 ) \
ASM( mov [ecx+0x30],eax) \
ASM( mov [ecx+0x34],edx) \
ASM( shufps xmm3,xmm3,0x00 ) \
ASM( mov eax,0x29573f9f ) \
ASM( mov edx,0x274a963c ) \
ASM( movlhps xmm0,xmm4 ) \
ASM( mov [ecx+0x38],eax) \
ASM( mov [ecx+0x3C],edx) \
ASM( mulps xmm1,xmm5 ) \
ASM( shufps xmm0,xmm0,0x88 ) \
ASM( movaps xmm2,[ecx] ) \
ASM( movaps xmm4,[ecx+0x10] ) \
ASM( mulps xmm2,xmm1 ) \
ASM( mulps xmm1,xmm3 ) \
ASM( mulps xmm4,xmm1 ) \
ASM( movaps xmm5,[ecx+0x20] ) \
ASM( addps xmm2,xmm4 ) \
ASM( mulps xmm1,xmm3 ) \
ASM( movaps xmm6,[ecx+0x30] ) \
ASM( mulps xmm5,xmm1 ) \
ASM( mov eax,[esp+8] ) \
ASM( mulps xmm1,xmm3 ) \
ASM( addps xmm2,xmm5 ) \
ASM( mulps xmm6,xmm1 ) \
ASM( mov edx,[esp+12] ) \
ASM( addps xmm2,xmm6 ) \
ASM( movhlps xmm1,xmm2 ) \
ASM( addps xmm2,xmm1 ) \
ASM( addps xmm2,xmm0 ) \
ASM( movss [eax],xmm2 ) \
ASM( shufps xmm2,xmm2,0x1 ) \
ASM( movss [edx],xmm2 ) \
_END_ASM

/// Вычисление синуса и косинуса одинарной точности, команды SSE3.
#define MATHPDSINCOSSSE3_STD \
_BEGIN_ASM \
ASM( mov eax,-1 ) \
ASM( CVTSI2SS xmm5,eax ) \
ASM( movss xmm1,[esp+4] ) \
ASM( lea ecx,bt::fastsindividef ) \
ASM( mov edx,1 ) \
ASM( CVTSI2SS xmm0,edx ) \
ASM( movaps xmm3,xmm1 ) \
ASM( mulss xmm3,xmm3 ) \
ASM( shufps xmm1,xmm3,0x00 ) \
ASM( movss xmm4,xmm3 ) \
ASM( mulss xmm3,xmm3 ) \
ASM( shufps xmm4,xmm3,0x00 ) \
ASM( shufps xmm4,xmm1,0x08 ) \
ASM( shufps xmm4,xmm4,0x42 ) \
ASM( shufps xmm1,xmm1,0x20 ) \
ASM( mulps xmm1,xmm4 ) \
ASM( shufps xmm5,xmm0,0x00 ) \
ASM( shufps xmm3,xmm3,0x00 ) \
ASM( movlhps xmm0,xmm4 ) \
ASM( mulps xmm1,xmm5 ) \
ASM( shufps xmm0,xmm0,0x88 ) \
ASM( lddqu xmm2,[ecx] ) \
ASM( lddqu xmm4,[ecx+0x10] ) \
ASM( mulps xmm2,xmm1 ) \
ASM( mulps xmm1,xmm3 ) \
ASM( mulps xmm4,xmm1 ) \
ASM( lddqu xmm5,[ecx+0x20] ) \
ASM( addps xmm2,xmm4 ) \
ASM( mulps xmm1,xmm3 ) \
ASM( lddqu xmm6,[ecx+0x30] ) \
ASM( mulps xmm5,xmm1 ) \
ASM( mov eax,[esp+0x08] ) \
ASM( mulps xmm1,xmm3 ) \
ASM( addps xmm2,xmm5 ) \
ASM( mulps xmm6,xmm1 ) \
ASM( mov edx,[esp+0x0C] ) \
ASM( addps xmm2,xmm6 ) \
ASM( movhlps xmm1,xmm2 ) \
ASM( addps xmm2,xmm1 ) \
ASM( addps xmm2,xmm0 ) \
ASM( movss [eax],xmm2 ) \
ASM( shufps xmm2,xmm2,0x1 ) \
ASM( movss [edx],xmm2 ) \
_END_ASM

/*
		[0x0]	0x3ff0000000000000	__int64
		[0x1]	0x3fe0000000000000	__int64
		[0x2]	0x3fc5555555555555	__int64
		[0x3]	0x3fa5555555555555	__int64
		[0x4]	0x3f81111111111111	__int64
		[0x5]	0x3f56c16c16c16c17	__int64
		[0x6]	0x3f2a01a01a01a01a	__int64
		[0x7]	0x3efa01a01a01a01a	__int64
		[0x8]	0x3ec71de3a556c734	__int64
		[0x9]	0x3e927e4fb7789f5c	__int64
		[0xa]	0x3e5ae64567f544e4	__int64
		[0xb]	0x3e21eed8eff8d898	__int64
		[0xc]	0x3de6124613a86d09	__int64
		[0xd]	0x3da93974b2d957b5	__int64
		[0xe]	0x3d6ae7f3e733b81f	__int64
		[0xf]	0x3d2ae7f3e733b81f	__int64
		[0x10]	0x3ce952c77030ad4a	__int64
*/

/*ASM( mov eax,0x3fe00000 ) \
ASM( mov edx,0x00000000 ) \
ASM( mov [ecx],edx) \
ASM( mov [ecx+0x4],eax) \
ASM( mov eax,0x3fc55555 ) \
ASM( mov edx,0x55555555 ) \
ASM( mov [ecx+0x8],edx) \
ASM( mov [ecx+0xC],eax) \
ASM( mov eax,0x3fa55555 ) \
ASM( mov edx,0x55555555 ) \
ASM( mov [ecx+0x10],edx) \
ASM( mov [ecx+0x14],eax) \
ASM( mov eax,0x3f811111 ) \
ASM( mov edx,0x11111111 ) \
ASM( mov [ecx+0x18],edx) \
ASM( mov [ecx+0x1C],eax) \
ASM( mov eax,0x3f56c16c ) \
ASM( mov edx,0x16c16c17 ) \
ASM( mov [ecx+0x20],edx) \
ASM( mov [ecx+0x24],eax) \
ASM( mov eax,0x3f2a01a0 ) \
ASM( mov edx,0x1a01a01a ) \
ASM( mov [ecx+0x28],edx) \
ASM( mov [ecx+0x2C],eax) \
ASM( mov eax,0x3efa01a0 ) \
ASM( mov edx,0x1a01a01a ) \
ASM( mov [ecx+0x30],edx) \
ASM( mov [ecx+0x34],eax) \
ASM( mov eax,0x3ec71de3 ) \
ASM( mov edx,0xa556c734 ) \
ASM( mov [ecx+0x38],edx) \
ASM( mov [ecx+0x3C],eax) \
ASM( mov eax,0x3e927e4f ) \
ASM( mov edx,0xb7789f5c ) \
ASM( mov [ecx+0x40],edx) \
ASM( mov [ecx+0x44],eax) \
ASM( mov eax,0x3e5ae645 ) \
ASM( mov edx,0x67f544e4 ) \
ASM( mov [ecx+0x48],edx) \
ASM( mov [ecx+0x4C],eax) \
ASM( mov eax,0x3e21eed8 ) \
ASM( mov edx,0xeff8d898 ) \
ASM( mov [ecx+0x58],edx) \
ASM( mov [ecx+0x5C],eax) \
ASM( mov eax,0x3de61246 ) \
ASM( mov edx,0x13a86d09 ) \
ASM( mov [ecx+0x58],edx) \
ASM( mov [ecx+0x5C],eax) \
ASM( mov eax,0x3da93974 ) \
ASM( mov edx,0xb2d957b5 ) \
ASM( mov [ecx+0x68],edx) \
ASM( mov [ecx+0x6C],eax) \
ASM( mov eax,0x3d6ae7f3 ) \
ASM( mov edx,0xe733b81f ) \
ASM( mov [ecx+0x68],edx) \
ASM( mov [ecx+0x6C],eax) \
ASM( mov eax,0x3d2ae7f3 ) \
ASM( mov edx,0xe733b81f ) \
ASM( mov [ecx+0x78],edx) \
ASM( mov [ecx+0x7C],eax) \
ASM( mov eax,0x3ce952c7 ) \
ASM( mov edx,0x7030ad4a ) \
ASM( mov [ecx+0x78],edx) \
ASM( mov [ecx+0x7C],eax) \*/

/// Вычисление синуса и косинуса двойной точности, команды SSE2.
#define MATHPDDSINCOSSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,-1 ) \
ASM( CVTSI2SD xmm5,eax ) \
ASM( movsd xmm1,[esp+4] ) \
ASM( mov edx,1 ) \
ASM( lea ecx,bt::fastsindivided ) \
ASM( CVTSI2SD xmm0,edx ) \
ASM( xorps xmm3,xmm3 ) \
ASM( movsd xmm3,xmm1 ) \
ASM( mulsd xmm3,xmm3 ) \
ASM( movsd xmm4,xmm1 ) \
ASM( mulsd xmm1,xmm3 ) \
ASM( movlhps xmm1,xmm1 ) \
ASM( movlhps xmm3,xmm3 ) \
ASM( movhlps xmm1,xmm3 ) \
ASM( movlhps xmm4,xmm4 ) \
ASM( movlhps xmm5,xmm5 ) \
ASM( movlhps xmm0,xmm4 ) \
ASM( mulpd xmm3,xmm5 ) \
ASM( mulpd xmm1,xmm5 ) \
ASM( movapd xmm2,[ecx] ) \
ASM( movapd xmm4,[ecx+0x10] ) \
ASM( mulpd xmm2,xmm1 ) \
ASM( mulpd xmm1,xmm3 ) \
ASM( mulpd xmm4,xmm1 ) \
ASM( movapd xmm5,[ecx+0x20] ) \
ASM( movapd xmm6,[ecx+0x30] ) \
ASM( addpd xmm2,xmm4 ) \
ASM( mulpd xmm1,xmm3 ) \
ASM( mulpd xmm5,xmm1 ) \
ASM( mov eax,[esp+12] ) \
ASM( mulpd xmm1,xmm3 ) \
ASM( addpd xmm2,xmm5 ) \
ASM( mulpd xmm6,xmm1 ) \
ASM( mov edx,[esp+16] ) \
ASM( addpd xmm2,xmm6 ) \
ASM( mulpd xmm1,xmm3 ) \
ASM( movapd xmm7,[ecx+0x40] ) \
ASM( movapd xmm4,[ecx+0x50] ) \
ASM( mulpd xmm7,xmm1 ) \
ASM( mulpd xmm1,xmm3 ) \
ASM( mulpd xmm4,xmm1 ) \
ASM( addpd xmm2,xmm7 ) \
ASM( mulpd xmm1,xmm3 ) \
ASM( movapd xmm5,[ecx+0x60] ) \
ASM( movapd xmm6,[ecx+0x70] ) \
ASM( mulpd xmm1,xmm3 ) \
ASM( addpd xmm2,xmm4 ) \
ASM( mulpd xmm5,xmm1 ) \
ASM( mulpd xmm6,xmm1 ) \
ASM( addpd xmm2,xmm6 ) \
ASM( addpd xmm2,xmm0 ) \
ASM( movsd [eax],xmm2 ) \
ASM( movhps [edx],xmm2 ) \
_END_ASM

//**************************** SINCOS TABLE STDCALL *********************************
// sin cos edx=[esp+4]-c void *, [esp+8]-a float, eax=[esp+12]-b void *, ecx=[esp+16]-c void *

/// Вычисление синуса и косинуса одинарной точности, команды SSE.
#define MATHPDSINCOSTABLESSE_STD \
_BEGIN_ASM \
ASM( mov edx,[esp+0x4] ) \
ASM( movss xmm3,dword ptr [esp+8] ) \
ASM( movss xmm4,dword ptr [edx] ) \
ASM( mov eax,dword ptr [esp+0xC] ) \
ASM( mov ecx,dword ptr [esp+0x10] ) \
_LINE3( 0x0F,0x28,0xF3 )                /* movaps      xmm6,xmm3  */ \
_LINE4( 0xF3,0x0F,0x58,0xE4 )           /* addss       xmm4,xmm4  */ \
_LINE4( 0xF3,0x0F,0x59,0xF3 )           /* mulss       xmm6,xmm3  */ \
_LINE3( 0x0F,0x57,0xC0 )                /* xorps       xmm0,xmm0  */ \
_LINE4( 0x0F,0xC6,0xDE,0x00 )           /* shufps      xmm3,xmm6,0  */ \
_LINE4( 0xF3,0x0F,0x10,0xEE )           /* movss       xmm5,xmm6  */ \
_LINE4( 0xF3,0x0F,0x59,0xF6 )           /* mulss       xmm6,xmm6  */ \
_LINE4( 0xF3,0x0F,0x5C,0xC4 )           /* subss       xmm0,xmm4  */ \
_LINE4( 0x0F,0xC6,0xEE,0x00 )           /* shufps      xmm5,xmm6,0  */ \
_LINE4( 0x0F,0xC6,0xEB,0x08 )           /* shufps      xmm5,xmm3,8  */ \
_LINE4( 0x0F,0xC6,0xF6,0x00 )           /* shufps      xmm6,xmm6,0  */ \
_LINE4( 0x0F,0xC6,0xED,0x42 )           /* shufps      xmm5,xmm5,42h  */ \
_LINE4( 0x0F,0xC6,0xDB,0x20 )           /* shufps      xmm3,xmm3,20h  */ \
_LINE4( 0x0F,0xC6,0xC4,0x00 )           /* shufps      xmm0,xmm4,0  */ \
_LINE4( 0x0F,0x28,0x48,0x10 )           /* movaps      xmm1,xmmword ptr [eax+10h]  */ \
_LINE3( 0x0F,0x59,0xDD )                /* mulps       xmm3,xmm5  */ \
_LINE3( 0x0F,0x59,0xD8 )                /* mulps       xmm3,xmm0  */ \
_LINE3( 0x0F,0x28,0xD3 )                /* movaps      xmm2,xmm3  */ \
_LINE3( 0x0F,0x28,0x38 )                /* movaps      xmm7,xmmword ptr [eax]  */ \
_LINE3( 0x0F,0x59,0xD6 )                /* mulps       xmm2,xmm6  */ \
_LINE3( 0x0F,0x16,0xE5 )                /* movlhps     xmm4,xmm5  */ \
_LINE3( 0x0F,0x59,0xCA )                /* mulps       xmm1,xmm2  */ \
_LINE3( 0x0F,0x59,0xFB )                /* mulps       xmm7,xmm3  */ \
_LINE4( 0x0F,0x28,0x68,0x20 )           /* movaps      xmm5,xmmword ptr [eax+20h]  */ \
_LINE3( 0x0F,0x59,0xD6 )                /* mulps       xmm2,xmm6  */ \
_LINE3( 0x0F,0x58,0xCF )                /* addps       xmm1,xmm7  */ \
_LINE3( 0x0F,0x59,0xEA )                /* mulps       xmm5,xmm2  */ \
_LINE4( 0x0F,0x28,0x58,0x30 )           /* movaps      xmm3,xmmword ptr [eax+30h]  */ \
_LINE3( 0x0F,0x59,0xD6 )                /* mulps       xmm2,xmm6  */ \
_LINE4( 0x0F,0xC6,0xE4,0x88 )           /* shufps      xmm4,xmm4,88h  */ \
_LINE3( 0x0F,0x59,0xDA )                /* mulps       xmm3,xmm2  */ \
_LINE3( 0x0F,0x58,0xCD )                /* addps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xCB )                /* addps       xmm1,xmm3  */ \
_LINE3( 0x0F,0x12,0xD1 )                /* movhlps     xmm2,xmm1  */ \
_LINE3( 0x0F,0x58,0xD1 )                /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x58,0xD4 )                /* addps       xmm2,xmm4  */ \
ASM( movss dword ptr [eax],xmm2 ) \
ASM( shufps xmm2,xmm2,1 ) \
ASM( movss dword ptr [ecx],xmm2 ) \
_END_ASM

/// Вычисление синуса и косинуса двойной точности, команды SSE2.
#define MATHPDDSINCOSTABLESSE2_STD \
_BEGIN_ASM \
ASM( mov edx,[esp+0x4] ) \
ASM( movsd       xmm0,mmword ptr [edx]  ) \
ASM( movsd       xmm2,mmword ptr [esp+8]  ) \
ASM( movapd      xmm3,xmmword ptr [edx]  ) \
ASM( addsd       xmm0,xmm0  ) \
ASM( movapd      xmm4,xmmword ptr [edx+0x10]  ) \
ASM( movapd      xmm5,xmmword ptr [edx+0x20]  ) \
ASM( movapd      xmm6,xmmword ptr [edx+0x30]  ) \
ASM( movapd      xmm7,xmmword ptr [edx+0x40]  ) \
ASM( mov eax,dword ptr [esp+0x10]  ) \
ASM( movlhps     xmm0,xmm2  ) \
ASM( mov ecx,dword ptr [esp+0x14]  ) \
ASM( movlhps     xmm2,xmm2  ) \
ASM( movapd      xmm1,xmm2  ) \
ASM( mulpd       xmm1,xmm0  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( mulpd       xmm3,xmm1  ) \
ASM( mulpd       xmm2,xmm2  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( mulpd       xmm4,xmm1  ) \
ASM( subpd       xmm0,xmm3  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( mulpd       xmm5,xmm1  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( addpd       xmm0,xmm4  ) \
ASM( movapd      xmm3,xmmword ptr [edx+0x60]  ) \
ASM( mulpd       xmm6,xmm1  ) \
ASM( subpd       xmm0,xmm5  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( mulpd       xmm7,xmm1  ) \
ASM( addpd       xmm0,xmm6  ) \
ASM( movapd      xmm4,xmmword ptr [edx+0x50]  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( mulpd       xmm4,xmm1  ) \
ASM( subpd       xmm0,xmm7  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( mulpd       xmm3,xmm1  ) \
ASM( addpd       xmm0,xmm4  ) \
ASM( subpd       xmm0,xmm3  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( mulpd       xmm1,xmmword ptr [edx+0x70]  ) \
ASM( addpd       xmm0,xmm1  ) \
ASM( movsd       mmword ptr [eax],xmm0  ) \
ASM( shufpd      xmm0,xmm0,1  ) \
ASM( movsd       mmword ptr [ecx],xmm0  ) \
_END_ASM

//**************************** FAST SINCOS STDCALL *********************************
// sin cos [esp+4]-a float, eax=[esp+8]-b void *, edx=[esp+12]-c void *

/// Вычисление синуса и косинуса одинарной точности, команды SSE. ???
#define MATHPDFASTSINCOSSSE_STD \
_BEGIN_ASM \
ASM( mov eax,-1 ) \
ASM( CVTSI2SS xmm5,eax ) \
ASM( mov edx,1 ) \
ASM( CVTSI2SS xmm0,edx ) \
ASM( lea ecx,bt::fastsindividef ) \
ASM( movss xmm1,[esp+4] ) \
ASM( xorps xmm3,xmm3 ) \
ASM( movss xmm3,xmm1 ) \
ASM( mulss xmm3,xmm3 ) \
ASM( shufps xmm1,xmm3,0x00 ) \
ASM( movss xmm4,xmm3 ) \
ASM( mulss xmm3,xmm3 ) \
ASM( shufps xmm4,xmm3,0x00 ) \
ASM( shufps xmm4,xmm1,0x08 ) \
ASM( shufps xmm4,xmm4,0x42 ) \
ASM( shufps xmm1,xmm1,0x20 ) \
ASM( mulps xmm1,xmm4 ) \
ASM( shufps xmm5,xmm0,0x00 ) \
ASM( shufps xmm3,xmm3,0x00 ) \
ASM( movlhps xmm0,xmm4 ) \
ASM( mulps xmm1,xmm5 ) \
ASM( shufps xmm0,xmm0,0x88 ) \
ASM( movaps xmm6,xmm1 ) \
ASM( movlps xmm2,[ecx] ) \
ASM( movlps xmm4,[ecx+0x10] ) \
ASM( mulps xmm6,xmm3 ) \
ASM( movhps xmm2,[ecx+0x08] ) \
ASM( movhps xmm4,[ecx+0x18] ) \
ASM( mulps xmm2,xmm1 ) \
ASM( mulps xmm3,xmm3 ) \
ASM( mulps xmm4,xmm6 ) \
ASM( movlps xmm5,[ecx+0x20] ) \
ASM( addps xmm2,xmm4 ) \
ASM( mulps xmm1,xmm3 ) \
ASM( movhps xmm5,[ecx+0x28] ) \
ASM( mulps xmm5,xmm1 ) \
ASM( mov eax,[esp+8] ) \
ASM( addps xmm2,xmm5 ) \
ASM( mov edx,[esp+12] ) \
ASM( movhlps xmm1,xmm2 ) \
ASM( addps xmm2,xmm1 ) \
ASM( addps xmm2,xmm0 ) \
ASM( movss [eax],xmm2 ) \
ASM( shufps xmm2,xmm2,0x1 ) \
ASM( movss [edx],xmm2 ) \
_END_ASM

//**************************** SINCOS TABLE FASTCALL *********************************
// sin cos edx=b void *, ecx=c void *,eax=[esp+4]-c void *, [esp+8]-a float,

/// Вычисление синуса и косинуса одинарной точности, команды SSE.
#define MATHPDSINCOSTABLESSE_FAST \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )           /* mov         eax,dword ptr [esp+4]  */ \
_LINE6( 0xF3,0x0F,0x10,0x5C,0x24,0x08 ) /* movss       xmm3,dword ptr [esp+8]  */ \
_LINE4( 0xF3,0x0F,0x10,0x20 )           /* movss       xmm4,dword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xF3 )                /* movaps      xmm6,xmm3  */ \
_LINE4( 0xF3,0x0F,0x58,0xE4 )           /* addss       xmm4,xmm4  */ \
_LINE4( 0xF3,0x0F,0x59,0xF3 )           /* mulss       xmm6,xmm3  */ \
_LINE3( 0x0F,0x57,0xC0 )                /* xorps       xmm0,xmm0  */ \
_LINE4( 0x0F,0xC6,0xDE,0x00 )           /* shufps      xmm3,xmm6,0  */ \
_LINE4( 0xF3,0x0F,0x10,0xEE )           /* movss       xmm5,xmm6  */ \
_LINE4( 0xF3,0x0F,0x59,0xF6 )           /* mulss       xmm6,xmm6  */ \
_LINE4( 0xF3,0x0F,0x5C,0xC4 )           /* subss       xmm0,xmm4  */ \
_LINE4( 0x0F,0xC6,0xEE,0x00 )           /* shufps      xmm5,xmm6,0  */ \
_LINE4( 0x0F,0xC6,0xEB,0x08 )           /* shufps      xmm5,xmm3,8  */ \
_LINE4( 0x0F,0xC6,0xF6,0x00 )           /* shufps      xmm6,xmm6,0  */ \
_LINE4( 0x0F,0xC6,0xED,0x42 )           /* shufps      xmm5,xmm5,42h  */ \
_LINE4( 0x0F,0xC6,0xDB,0x20 )           /* shufps      xmm3,xmm3,20h  */ \
_LINE4( 0x0F,0xC6,0xC4,0x00 )           /* shufps      xmm0,xmm4,0  */ \
_LINE4( 0x0F,0x28,0x48,0x10 )           /* movaps      xmm1,xmmword ptr [eax+10h]  */ \
_LINE3( 0x0F,0x59,0xDD )                /* mulps       xmm3,xmm5  */ \
_LINE3( 0x0F,0x59,0xD8 )                /* mulps       xmm3,xmm0  */ \
_LINE3( 0x0F,0x28,0xD3 )                /* movaps      xmm2,xmm3  */ \
_LINE3( 0x0F,0x28,0x38 )                /* movaps      xmm7,xmmword ptr [eax]  */ \
_LINE3( 0x0F,0x59,0xD6 )                /* mulps       xmm2,xmm6  */ \
_LINE3( 0x0F,0x16,0xE5 )                /* movlhps     xmm4,xmm5  */ \
_LINE3( 0x0F,0x59,0xCA )                /* mulps       xmm1,xmm2  */ \
_LINE3( 0x0F,0x59,0xFB )                /* mulps       xmm7,xmm3  */ \
_LINE4( 0x0F,0x28,0x68,0x20 )           /* movaps      xmm5,xmmword ptr [eax+20h]  */ \
_LINE3( 0x0F,0x59,0xD6 )                /* mulps       xmm2,xmm6  */ \
_LINE3( 0x0F,0x58,0xCF )                /* addps       xmm1,xmm7  */ \
_LINE3( 0x0F,0x59,0xEA )                /* mulps       xmm5,xmm2  */ \
_LINE4( 0x0F,0x28,0x58,0x30 )           /* movaps      xmm3,xmmword ptr [eax+30h]  */ \
_LINE3( 0x0F,0x59,0xD6 )                /* mulps       xmm2,xmm6  */ \
_LINE4( 0x0F,0xC6,0xE4,0x88 )           /* shufps      xmm4,xmm4,88h  */ \
_LINE3( 0x0F,0x59,0xDA )                /* mulps       xmm3,xmm2  */ \
_LINE3( 0x0F,0x58,0xCD )                /* addps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xCB )                /* addps       xmm1,xmm3  */ \
_LINE3( 0x0F,0x12,0xD1 )                /* movhlps     xmm2,xmm1  */ \
_LINE3( 0x0F,0x58,0xD1 )                /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x58,0xD4 )                /* addps       xmm2,xmm4  */ \
_LINE4( 0xF3,0x0F,0x11,0x11 )           /* movss       dword ptr [ecx],xmm2  */ \
_LINE4( 0x0F,0xC6,0xD2,0x01 )           /* shufps      xmm2,xmm2,1  */ \
_LINE4( 0xF3,0x0F,0x11,0x12 )           /* movss       dword ptr [edx],xmm2  */ \
_END_ASM

/// Вычисление синуса и косинуса двойной точности, команды SSE2.
#define MATHPDDSINCOSTABLESSE2_FAST \
_BEGIN_ASM \
ASM( mov eax,[esp+0x4] ) \
ASM( movsd       xmm0,mmword ptr [eax]  ) \
ASM( movsd       xmm2,mmword ptr [esp+8]  ) \
ASM( movapd      xmm3,xmmword ptr [eax]  ) \
ASM( addsd       xmm0,xmm0  ) \
ASM( movapd      xmm4,xmmword ptr [eax+0x10]  ) \
ASM( movapd      xmm5,xmmword ptr [eax+0x20]  ) \
ASM( movapd      xmm6,xmmword ptr [eax+0x30]  ) \
ASM( movapd      xmm7,xmmword ptr [eax+0x40]  ) \
ASM( movlhps     xmm0,xmm2  ) \
ASM( movlhps     xmm2,xmm2  ) \
ASM( movapd      xmm1,xmm2  ) \
ASM( mulpd       xmm1,xmm0  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( mulpd       xmm3,xmm1  ) \
ASM( mulpd       xmm2,xmm2  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( mulpd       xmm4,xmm1  ) \
ASM( subpd       xmm0,xmm3  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( mulpd       xmm5,xmm1  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( addpd       xmm0,xmm4  ) \
ASM( movapd      xmm3,xmmword ptr [eax+0x60]  ) \
ASM( mulpd       xmm6,xmm1  ) \
ASM( subpd       xmm0,xmm5  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( mulpd       xmm7,xmm1  ) \
ASM( addpd       xmm0,xmm6  ) \
ASM( movapd      xmm4,xmmword ptr [eax+0x50]  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( mulpd       xmm4,xmm1  ) \
ASM( subpd       xmm0,xmm7  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( mulpd       xmm3,xmm1  ) \
ASM( addpd       xmm0,xmm4  ) \
ASM( subpd       xmm0,xmm3  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( mulpd       xmm1,xmmword ptr [eax+0x70]  ) \
ASM( addpd       xmm0,xmm1  ) \
ASM( movsd       mmword ptr [ecx],xmm0  ) \
ASM( shufpd      xmm0,xmm0,1  ) \
ASM( movsd       mmword ptr [edx],xmm0  ) \
_END_ASM

/// Вычисление синуса и косинуса одинарной точности, команды SSE.
#define MATHPDFASTSINCOSTABLESSE_FAST \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )           /* mov         eax,dword ptr [esp+4]  */ \
_LINE6( 0xF3,0x0F,0x10,0x5C,0x24,0x08 ) /* movss       xmm3,dword ptr [esp+8]  */ \
_LINE4( 0xF3,0x0F,0x10,0x20 )           /* movss       xmm4,dword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xF3 )                /* movaps      xmm6,xmm3  */ \
_LINE4( 0xF3,0x0F,0x58,0xE4 )           /* addss       xmm4,xmm4  */ \
_LINE4( 0xF3,0x0F,0x59,0xF3 )           /* mulss       xmm6,xmm3  */ \
_LINE3( 0x0F,0x57,0xC0 )                /* xorps       xmm0,xmm0  */ \
_LINE4( 0x0F,0xC6,0xDE,0x00 )           /* shufps      xmm3,xmm6,0  */ \
_LINE4( 0xF3,0x0F,0x10,0xEE )           /* movss       xmm5,xmm6  */ \
_LINE4( 0xF3,0x0F,0x59,0xF6 )           /* mulss       xmm6,xmm6  */ \
_LINE4( 0xF3,0x0F,0x5C,0xC4 )           /* subss       xmm0,xmm4  */ \
_LINE4( 0x0F,0xC6,0xEE,0x00 )           /* shufps      xmm5,xmm6,0  */ \
_LINE4( 0x0F,0xC6,0xEB,0x08 )           /* shufps      xmm5,xmm3,8  */ \
_LINE4( 0x0F,0xC6,0xF6,0x00 )           /* shufps      xmm6,xmm6,0  */ \
_LINE4( 0x0F,0xC6,0xED,0x42 )           /* shufps      xmm5,xmm5,42h  */ \
_LINE4( 0x0F,0xC6,0xDB,0x20 )           /* shufps      xmm3,xmm3,20h  */ \
_LINE4( 0x0F,0xC6,0xC4,0x00 )           /* shufps      xmm0,xmm4,0  */ \
_LINE4( 0x0F,0x28,0x48,0x10 )           /* movaps      xmm1,xmmword ptr [eax+10h]  */ \
_LINE3( 0x0F,0x59,0xDD )                /* mulps       xmm3,xmm5  */ \
_LINE3( 0x0F,0x59,0xD8 )                /* mulps       xmm3,xmm0  */ \
_LINE3( 0x0F,0x28,0xD3 )                /* movaps      xmm2,xmm3  */ \
_LINE3( 0x0F,0x28,0x38 )                /* movaps      xmm7,xmmword ptr [eax]  */ \
_LINE3( 0x0F,0x59,0xD6 )                /* mulps       xmm2,xmm6  */ \
_LINE3( 0x0F,0x16,0xE5 )                /* movlhps     xmm4,xmm5  */ \
_LINE3( 0x0F,0x59,0xCA )                /* mulps       xmm1,xmm2  */ \
_LINE3( 0x0F,0x59,0xFB )                /* mulps       xmm7,xmm3  */ \
_LINE4( 0x0F,0x28,0x68,0x20 )           /* movaps      xmm5,xmmword ptr [eax+20h]  */ \
_LINE3( 0x0F,0x59,0xD6 )                /* mulps       xmm2,xmm6  */ \
_LINE3( 0x0F,0x58,0xCF )                /* addps       xmm1,xmm7  */ \
_LINE3( 0x0F,0x59,0xEA )                /* mulps       xmm5,xmm2  */ \
_LINE4( 0x0F,0xC6,0xE4,0x88 )           /* shufps      xmm4,xmm4,88h  */ \
_LINE3( 0x0F,0x12,0xD1 )                /* movhlps     xmm2,xmm1  */ \
_LINE3( 0x0F,0x58,0xD1 )                /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x58,0xD5 )                /* addps       xmm2,xmm5  */ \
_LINE3( 0x0F,0x58,0xD4 )                /* addps       xmm2,xmm4  */ \
_LINE4( 0xF3,0x0F,0x11,0x11 )           /* movss       dword ptr [ecx],xmm2  */ \
_LINE4( 0x0F,0xC6,0xD2,0x01 )           /* shufps      xmm2,xmm2,1  */ \
_LINE4( 0xF3,0x0F,0x11,0x12 )           /* movss       dword ptr [edx],xmm2  */ \
_END_ASM

/// Вычисление синуса и косинуса двойной точности, команды SSE2.
#define MATHPDDFASTSINCOSTABLESSE2_FAST \
_BEGIN_ASM \
ASM( mov eax,[esp+0x4] ) \
ASM( movsd       xmm0,mmword ptr [eax]  ) \
ASM( movsd       xmm2,mmword ptr [esp+8]  ) \
ASM( movapd      xmm3,xmmword ptr [eax]  ) \
ASM( addsd       xmm0,xmm0  ) \
ASM( movapd      xmm4,xmmword ptr [eax+0x10]  ) \
ASM( movapd      xmm5,xmmword ptr [eax+0x20]  ) \
ASM( movapd      xmm6,xmmword ptr [eax+0x30]  ) \
ASM( movapd      xmm7,xmmword ptr [eax+0x40]  ) \
ASM( movlhps     xmm0,xmm2  ) \
ASM( movlhps     xmm2,xmm2  ) \
ASM( movapd      xmm1,xmm2  ) \
ASM( mulpd       xmm1,xmm0  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( mulpd       xmm3,xmm1  ) \
ASM( mulpd       xmm2,xmm2  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( mulpd       xmm4,xmm1  ) \
ASM( subpd       xmm0,xmm3  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( mulpd       xmm5,xmm1  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( addpd       xmm0,xmm4  ) \
ASM( mulpd       xmm6,xmm1  ) \
ASM( subpd       xmm0,xmm5  ) \
ASM( mulpd       xmm1,xmm2  ) \
ASM( mulpd       xmm7,xmm1  ) \
ASM( addpd       xmm0,xmm6  ) \
ASM( subpd       xmm0,xmm7  ) \
ASM( movsd       mmword ptr [ecx],xmm0  ) \
ASM( shufpd      xmm0,xmm0,1  ) \
ASM( movsd       mmword ptr [edx],xmm0  ) \
_END_ASM

#endif
