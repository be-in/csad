/*
 * e2k_64vector.cpp
 *
 *  Created on: 18.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include "e2k_64vector.h"

#ifdef CPU_E2K_64

#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include "macrosasm.h"

WARNING_DISABLE;
OPTIMIZE_ON;

#define NO_NAKED

namespace bt {

// *********************************** vector Add E2K function **********************************************

#ifdef NO_NAKED

void _APICALL _V2FAddE2K(float *a,float *b,float *c)
{
	asm( "{ nop 2; ldd,0 [0+%0],%%dr4; ldd,2 [0+%1],%%dr5; return %%ctpr3 }"
		 "{ pfadds,1 %%dr4,%%dr5,%%dr4; std,2 [0+%2],%%dr4; ct %%ctpr3; ipd 2 }"
		:
		:"r"(a), "r"(b), "r"(c) );
}

void _APICALL _V3FAddE2K(float *a,float *b,float *c)
{
	asm( "{ nop 2; ldd,0 [0+%0],%%dr4; ldd,2 [0+%1],%%dr5; ldw,3 [8+%0],%%r6; ldw,5 [8+%1],%%r7; return %%ctpr3 }"
		 "{ pfadds,1 %%dr4,%%dr5,%%dr4; std,2 [0+%2],%%dr4; fadds,4 %%r6,%%r7,%%r6; stw,5 [8+%2],%%r6; ct %%ctpr3; ipd 2 }"
		:
		:"r"(a), "r"(b), "r"(c) );
}

void _APICALL _V4FAddE2K(float *a,float *b,float *c)
{
	asm( "{ ldd,0 [0+%0],%%dr4; ldd,2 [0+%1],%%dr5; ldd,3 [8+%0],%%dr6; ldd,5 [8+%1],%%dr7; setwd wsz = 0x6, nfx = 0x1; setbp psz = 0x0; return %%ctpr3; }"
		 "{ pfadds,1 %%dr4,%%dr5,%%dr4; std,2 [0+%%dr2],%%dr4; pfadds,4 %%dr6,%%dr7,%%dr5; std,5 [8+%2],%%dr5; ct %%ctpr3; ipd 2 }"
		:
		:"r"(a), "r"(b), "r"(c) );
}

void _APICALL _V2DAddE2K(double *a,double *b,double *c)
{
	asm( "{ nop 2; ldd,0 [0+%0],%%dr4; ldd,2 [0+%1],%%dr5; ldd,3 [8+%0],%%dr6; ldd,5 [8+%1],%%dr7; return %%ctpr3 }"
		 "{ faddd,1 %%dr4,%%dr5,%%dr4; std,2 [0+%2],%%dr4; faddd,4 %%dr6,%%dr7,%%dr6; std,5 [4+%2],%%dr6; ct %%ctpr3; ipd 2 }"
		:
		:"r"(a), "r"(b), "r"(c) );
}

void _APICALL _V3DAddE2K(double *a,double *b,double *c)
{
	asm( "{ ldd,0 [0+%0],%%dr3; ldd,2 [0+%1],%%dr4; ldd,3 [8+%0],%%dr5; ldd,5 [8+%1],%%dr6; }"
		 "{ nop 2; ldd,0 [16+%0],%%dr7; ldd,2 [16+%1],%%dr8; return %%ctpr3 }"
		 "{ faddd,0 %%dr3,%%dr4,%%dr3; faddd,1 %%dr5, %%dr6, %%dr4; std,2 [0+%2],%%dr3; faddd,3 %%dr7,%%dr8,%%dr5; std,5 [8+%2],%%dr4 }"
		 "{ std,2 [16+%2],%%dr5; ct %%ctpr3; ipd 2 }"
		:
		:"r"(a), "r"(b), "r"(c) );
}

void _APICALL _V4DAddE2K(double *a,double *b,double *c)
{
	asm( "{ ldd,0 [0+%0],%%dr3; ldd,2 [0+%1],%%dr4; ldd,3 [8+%0],%%dr5; ldd,5 [8+%1],%%dr6; }"
		 "{ nop 2; ldd,0 [16+%0],%%dr7; ldd,2 [16+%1],%%dr8; ldd,3 [24+%0],%%dr9; ldd,5 [24+%1],%%dr10; return %%ctpr3 }"
		 "{ faddd,0 %%dr3,%%dr4,%%dr3; faddd,1 %%dr5, %%dr6, %%dr4; std,2 [0+%2],%%dr3; faddd,3 %%dr7,%%dr8,%%dr5; faddd,4 %%dr9,%%dr10,%%dr6; std,5 [8+%2],%%dr4 }"
		 "{ std,2 [16+%2],%%dr5; std,5 [24+%2],%%dr6; ct %%ctpr3; ipd 2 }"
		:
		:"r"(a), "r"(b), "r"(c) );
}

#endif

/*void _NAKED _STDCALL _V2FAddE2K(float *a,float *b,float *c)
{
	_BEGIN_ASM \
	ASM( { nop 2; ldd,0 [0+%dr0],%dr4; ldd,2 [0+%dr1],%dr5; return %ctpr3 } ) \
	ASM( { pfadds,1 %dr4,%dr5,%dr4; std,2 [0+%dr2],%dr4; ct %ctpr3; ipd 2 } ) \
	_END_ASM
}

void _NAKED _STDCALL _V3FAddE2K(float *a,float *b,float *c)
{
	_BEGIN_ASM \
	ASM( { nop 2; ldd,0 [0+%dr0],%dr4; ldd,2 [0+%dr1],%dr5; ldw,3 [8+%dr0],%r6; ldw,5 [8+%dr1],%r7; return %ctpr3 } ) \
	ASM( { pfadds,1 %dr4,%dr5,%dr4; std,2 [0+%dr2],%dr4; fadds,4 %r6,%r7,%r6; stw,5 [8+%dr2],%r6 } ) \
	ASM( { ct %ctpr3; ipd 2 } ) \
	_END_ASM
}

//	asm("{ ldw,0 [0+%dr0],%r3; ldw,2 [0+%dr1],%r4; ldw,3 [4+%dr0],%r5; ldw,5 [4+%dr1],%r6 }");
//	asm("{ nop 2; ldw,0 [8+%dr0],%r7; ldw,2 [8+%dr1],%r8; ldw,3 [12+%dr0],%r9; ldw,5 [12+%dr1],%r10; return %ctpr3 }");
//	asm("{ nop 3; fadds,0 %r3, %r4, %r3; fadds,1 %r5, %r6, %r4; stw,2 [0+%dr2],%r3; fadds,3 %r7, %r8, %r5; fadds,4 %r9, %r10, %r6; stw,5 [4+%dr2],%r4; }");
//	asm("{ stw,2 [8+%dr2],%r5; stw,5 [12+%dr2],%r6; ct %ctpr3; ipd 2 }");
*/
/*asm (".global _V4FAddE2K\n"
     ".type   _V4FAddE2K, @function\n"
     ".align  8\n"
     "_V4FAddE2K:\n"
     "{ setwd wsz = 0x6, nfx = 0x1; setbp psz = 0x0; }\n"
     "{ nop 2; ldd,0 [0+%dr0],%dr4; ldd,2 [0+%dr1],%dr5; ldd,3 [8+%dr0],%dr6; ldd,5 [8+%dr1],%dr7; return %ctpr3; }\n"
     "{ pfadds,1 %dr4,%dr5,%dr4; std,2 [0+%dr2],%dr4; pfadds,4 %dr6,%dr7,%dr5; std,5 [8+%dr2],%dr5; ct %ctpr3; ipd 2 }\n"
     ".size   _V4FAddE2K, .- :_V4FAddE2K\n");*/

/*
	_BEGIN_ASM \
		ASM( { setwd wsz = 0x6, nfx = 0x1; setbp psz = 0x0; } ) \
		ASM( { nop 2; ldd,0 [0+%dr0],%dr4; ldd,2 [0+%dr1],%dr5; ldd,3 [8+%dr0],%dr6; ldd,5 [8+%dr1],%dr7; return %ctpr3; } ) \
		ASM( { pfadds,1 %dr4,%dr5,%dr4; std,2 [0+%dr2],%dr4; pfadds,4 %dr6,%dr7,%dr5; std,5 [8+%dr2],%dr5; ct %ctpr3; ipd 2 } ) \
	_END_ASM
*/

/*void _NAKED _STDCALL _V4FAddE2K(float *a,float *b,float *c)
{
	_BEGIN_ASM \
		ASM( { ldd,0 [0+%dr0],%dr4; ldd,2 [0+%dr1],%dr5; ldd,3 [8+%dr0],%dr6; ldd,5 [8+%dr1],%dr7; setwd wsz = 0x6, nfx = 0x1; setbp psz = 0x0; return %ctpr3; } ) \
		ASM( { pfadds,1 %dr4,%dr5,%dr4; std,2 [0+%dr2],%dr4; pfadds,4 %dr6,%dr7,%dr5; std,5 [8+%dr2],%dr5; ct %ctpr3; ipd 2 } ) \
	_END_ASM
}

void _NAKED _STDCALL _V2DAddE2K(double *a,double *b,double *c)
{
	_BEGIN_ASM \
	ASM( { nop 2; ldd,0 [0+%dr0],%dr4; ldd,2 [0+%dr1],%dr5; ldd,3 [8+%dr0],%dr6; ldd,5 [8+%dr1],%dr7; return %ctpr3 } ) \
	ASM( { faddd,1 %dr4,%dr5,%dr4; std,2 [0+%dr2],%dr4; faddd,4 %dr6,%dr7,%dr6; std,5 [4+%dr2],%dr6; ct %ctpr3; ipd 2 } ) \
	_END_ASM
}

void _NAKED _STDCALL _V3DAddE2K(double *a,double *b,double *c)
{
	_BEGIN_ASM \
	ASM( { ldd,0 [0+%dr0],%dr4; ldd,2 [0+%dr1],%dr5; ldd,3 [8+%dr0],%dr6; ldd,5 [8+%dr1],%dr7 } ) \
	ASM( { nop 2; faddd,0 %dr4,%dr5,%dr4; std,2 [0+%dr2],%dr4; faddd,4 %dr6,%dr7,%dr6; std,5 [4+%dr2],%dr6; return %ctpr3 } ) \
	ASM( { ldd,0 [16+%dr0],%dr4; ldd,2 [16+%dr1],%dr5; } ) \
	ASM( { faddd,0 %dr4,%dr5,%dr4; std,2 [16+%dr2],%dr4; ct %ctpr3; ipd 2 } ) \
	_END_ASM
}*/

/*	_BEGIN_ASM \
	ASM( { setwd wsz = 0x6, nfx = 0x1; setwd psz = 0x0; } ) \
	ASM( { ldd,0 [%dr1+0],%dr4; ldd,2 [%dr0+0],%dr5; ldd,3,sm [%dr1+8]0x4,%dr6; return %ctpr3 } ) \
	ASM( { ldd,0,sm [%dr1+8]0x4,%dr7; ldd,3,sm [16 + %dr0]0x4,%dr8; } ) \
	ASM( { ldd,0,sm [16 + %dr1]0x4,%dr9; ldd,3,sm [24 + %dr0]0x4,%dr10; } ) \
	ASM( { nop 3; ldd,0,sm [24 + %dr1]0x4,%dr5; faddd,1 %dr5,%dr4,%dr4; } ) \
	_END_ASM*/

/*asm (".global _V4DAddE2K\n"
     ".type   _V4DAddE2K, @function\n"
     ".align  8\n"
     "_V4DAddE2K:\n"
	 "{ setwd wsz = 0x6, nfx = 0x1; setbp psz = 0x0; }\n"
	 "{ ldd,0 [0+%dr0],%dr3; ldd,2 [0+%dr1],%dr4; ldd,3 [8+%dr0],%dr5; ldd,5 [8+%dr1],%dr6 }\n"
     "{ nop 2; ldd,0 [16+%dr0],%dr7; ldd,2 [16+%dr1],%dr8; ldd,3 [24+%dr0],%dr9; ldd,5 [24+%dr1],%dr10; return %ctpr3 }\n"
     "{ faddd,0 %dr3,%dr4,%dr3; faddd,1 %dr5, %dr6, %dr4; std,2 [0+%dr2],%dr3; faddd,3 %dr7,%dr8,%dr5; faddd,4 %dr9, %dr10, %dr6; std,5 [8+%dr2],%dr4 }\n"
     "{ std,2 [16+%dr2],%dr5; std,5 [24+%dr2],%dr6; ct %ctpr3; ipd 2 }\n"
     ".size   _V4DAddE2K, .- _V4DAddE2K\n");*/

/*void _NAKED _STDCALL _V4DAddE2K(double *a,double *b,double *c)
{
	_BEGIN_ASM \
	ASM( { ldd,0 [0+%dr0],%dr3; ldd,2 [0+%dr1],%dr4; ldd,3 [8+%dr0],%dr5; ldd,5 [8+%dr1],%dr6; setwd wsz = 0x6, nfx = 0x1; setbp psz = 0x0; } ) \
	ASM( { nop 2; ldd,0 [16+%dr0],%dr7; ldd,2 [16+%dr1],%dr8; ldd,3 [24+%dr0],%dr9; ldd,5 [24+%dr1],%dr10; return %ctpr3 } ) \
	ASM( { faddd,0 %dr3,%dr4,%dr3; faddd,1 %dr5, %dr6, %dr4; std,2 [0+%dr2],%dr3; faddd,3 %dr7,%dr8,%dr5; faddd,4 %dr9, %dr10, %dr6; std,5 [8+%dr2],%dr4 } ) \
	ASM( { std,2 [16+%dr2],%dr5; std,5 [24+%dr2],%dr6; ct %ctpr3; ipd 2 } ) \
	_END_ASM
}*/

// *********************************** vector Add E2K function **********************************************

#ifdef NO_NAKED

void _APICALL _V2FSubE2K(float *a,float *b,float *c)
{
	asm( "{ nop 2; ldd,0 [0+%0],%%dr4; ldd,2 [0+%1],%%dr5; return %%ctpr3 }"
		 "{ pfsubs,1 %%dr4,%%dr5,%%dr4; std,2 [0+%2],%%dr4; ct %%ctpr3; ipd 2 }"
		:
		:"r"(a), "r"(b), "r"(c) );
}

void _APICALL _V3FSubE2K(float *a,float *b,float *c)
{
	asm( "{ nop 2; ldd,0 [0+%0],%%dr4; ldd,2 [0+%1],%%dr5; ldw,3 [8+%0],%%r6; ldw,5 [8+%1],%%r7; return %%ctpr3 }"
		 "{ pfsubs,1 %%dr4,%%dr5,%%dr4; std,2 [0+%2],%%dr4; fsubs,4 %%r6,%%r7,%%r6; stw,5 [8+%2],%%r6; ct %%ctpr3; ipd 2 }"
		:
		:"r"(a), "r"(b), "r"(c) );
}

void _APICALL _V4FSubE2K(float *a,float *b,float *c)
{
	asm( "{ ldd,0 [0+%0],%%dr4; ldd,2 [0+%1],%%dr5; ldd,3 [8+%0],%%dr6; ldd,5 [8+%1],%%dr7; setwd wsz = 0x6, nfx = 0x1; setbp psz = 0x0; return %%ctpr3; }"
		 "{ pfsubs,1 %%dr4,%%dr5,%%dr4; std,2 [0+%%dr2],%%dr4; pfsubs,4 %%dr6,%%dr7,%%dr5; std,5 [8+%2],%%dr5; ct %%ctpr3; ipd 2 }"
		:
		:"r"(a), "r"(b), "r"(c) );
}

void _APICALL _V2DSubE2K(double *a,double *b,double *c)
{
	asm( "{ nop 2; ldd,0 [0+%0],%%dr4; ldd,2 [0+%1],%%dr5; ldd,3 [8+%0],%%dr6; ldd,5 [8+%1],%%dr7; return %%ctpr3 }"
		 "{ fsubd,1 %%dr4,%%dr5,%%dr4; std,2 [0+%2],%%dr4; fsubd,4 %%dr6,%%dr7,%%dr6; std,5 [4+%2],%%dr6; ct %%ctpr3; ipd 2 }"
		:
		:"r"(a), "r"(b), "r"(c) );
}

void _APICALL _V3DSubE2K(double *a,double *b,double *c)
{
	asm( "{ ldd,0 [0+%0],%%dr3; ldd,2 [0+%1],%%dr4; ldd,3 [8+%0],%%dr5; ldd,5 [8+%1],%%dr6; }"
		 "{ nop 2; ldd,0 [16+%0],%%dr7; ldd,2 [16+%1],%%dr8; return %%ctpr3 }"
		 "{ fsubd,0 %%dr3,%%dr4,%%dr3; fsubd,1 %%dr5, %%dr6, %%dr4; std,2 [0+%2],%%dr3; fsubd,3 %%dr7,%%dr8,%%dr5; std,5 [8+%2],%%dr4 }"
		 "{ std,2 [16+%2],%%dr5; ct %%ctpr3; ipd 2 }"
		:
		:"r"(a), "r"(b), "r"(c) );
}

void _APICALL _V4DSubE2K(double *a,double *b,double *c)
{
	asm( "{ ldd,0 [0+%0],%%dr3; ldd,2 [0+%1],%%dr4; ldd,3 [8+%0],%%dr5; ldd,5 [8+%1],%%dr6; }"
		 "{ nop 2; ldd,0 [16+%0],%%dr7; ldd,2 [16+%1],%%dr8; ldd,3 [24+%0],%%dr9; ldd,5 [24+%1],%%dr10; return %%ctpr3 }"
		 "{ fsubd,0 %%dr3,%%dr4,%%dr3; fsubd,1 %%dr5, %%dr6, %%dr4; std,2 [0+%2],%%dr3; fsubd,3 %%dr7,%%dr8,%%dr5; fsubd,4 %%dr9,%%dr10,%%dr6; std,5 [8+%2],%%dr4 }"
		 "{ std,2 [16+%2],%%dr5; std,5 [24+%2],%%dr6; ct %%ctpr3; ipd 2 }"
		:
		:"r"(a), "r"(b), "r"(c) );
}

#endif

// *********************************** vector Dot E2K function **********************************************

/*float _NAKED _STDCALL _V2FDotE2K(float *a,float *b)
{
	_BEGIN_ASM \
	ASM( { nop 2; ldw,0 [0+%dr0],%r3; ldw,2 [0+%dr1],%r4; ldw,3 [4+%dr0],%r5; ldw,5 [4+%dr1],%r6; setwd wsz = 0x6, nfx = 0x1; setbp psz = 0x0; return %ctpr3 } ) \
	ASM( { ct %ctpr3; ipd 2; fmuls,0 %r3, %r4, %r3; fmuls,1 %r5, %r6, %r4; fadds,4 %r3, %r4, %r0 } ) \
	_END_ASM
}

float _NAKED _STDCALL _V3FDotE2K(float *a,float *b)
{
	_BEGIN_ASM \
	ASM( { nop 2; ldw,0 [0+%dr0],%r3; ldw,2 [0+%dr1],%r4; ldw,3 [4+%dr0],%r5; ldw,5 [4+%dr1],%r6; return %ctpr3 } ) \
	ASM( { ct %ctpr3; ipd 2; fmuls,0 %r3, %r4, %r3; fmuls,1 %r5, %r6, %r4; fadds,4 %r3, %r4, %r0 } ) \
	_END_ASM
}

float _NAKED _STDCALL _V4FDotE2K(float *a,float *b)
{
	_BEGIN_ASM \
	ASM( { ldw,0 [0+%dr0],%r3; ldw,2 [0+%dr1],%r4; ldw,3 [4+%dr0],%r5; ldw,5 [4+%dr1],%r6 } ) \
	ASM( { nop 2; ldw,0 [8+%dr0],%r7; ldw,2 [8+%dr1],%r8; ldw,3 [12+%dr0],%r9; ldw,5 [12+%dr1],%r10; return %ctpr3 } ) \
	ASM( { nop 3; fmuls,0 %r3, %r4, %r3; fmuls,1 %r5, %r6, %r4; fmuls,3 %r7, %r8, %r5; fmuls,4 %r9, %r10, %r6; } ) \
	_END_ASM
//	asm("{ ct %ctpr3; ipd 2; fadds,0 %r3, %r4, %r3; fadds,1 %r5, %r6, %r4; fadds,4 %r3, %r4, %r0 }");
}

double _NAKED _STDCALL _V4DDotE2K(double *a,double *b)
{
///	_BEGIN_ASM \
	_LINE8( 0x25, 0x40, 0x00, 0xB4, 0x83, 0xC8, 0x81, 0x67 ) \
	_LINE8( 0x84, 0xC8, 0x80, 0x67, 0x85, 0xC0, 0x81, 0x67 ) \
	_LINE8( 0x86, 0xC0, 0x80, 0x67, 0x00, 0x00, 0x00, 0xF0 ) \
	_LINE8( 0xA4, 0x00, 0x00, 0xB4, 0x87, 0x81, 0xD0, 0x67 ) \
	_LINE8( 0x88, 0x80, 0xD0, 0x67, 0x81, 0x81, 0xD8, 0x67 ) \
	_LINE8( 0x89, 0x80, 0xD8, 0x67, 0x00, 0x00, 0x00, 0x00 ) \
	_END_ASM

	_BEGIN_ASM \
	ASM( { ldd,0 [%dr1+8],%dr3; ldd,2 [%dr0+8],%dr4; ldd,3 [%dr1+0],%dr5; ldd,5 [%dr0+0],%dr6; return %ctpr3 } ) \
	ASM( { nop 1; ldd,0 [16+%dr1],%dr7; ldd,2 [16+%dr0],%dr8; ldd,3 [24+%dr1],%dr1; ldd,5 [24+%dr0],%dr9; } ) \
	_END_ASM

//	_BEGIN_ASM \
	ASM( { ldd,0 [%dr1+8],%dr3; ldd,2 [%dr0+8],%dr4; ldd,3 [%dr1+0],%dr5; ldd,5 [%dr0+0],%dr6; return %ctpr3 } ) \
	ASM( { nop 1; ldd,0 [16+%dr1],%dr7; ldd,2 [16+%dr0],%dr8; ldd,3 [24+%dr1],%dr1; ldd,5 [24+%dr0],%dr9; } ) \
	ASM( { fmuld,0 %dr4, %dr3, %dr3; fmuld,3 %dr6, %dr5, %dr4; } ) \
	ASM( { nop 4; fmuld,0 %dr8, %dr7, %dr5; fmuld,3 %dr9, %dr1, %dr1; } ) \
	ASM( { nop 3; faddd,0 %dr4, %dr3, %dr3; } ) \
	ASM( { nop 3; faddd,0 %dr3, %dr5, %dr3; } ) \
	ASM( { ct %ctpr3; ipd 2; faddd,0 %dr3, %dr1, %dr0; } ) \
	_END_ASM
}*/

// *********************************** vector Normal E2K function **********************************************

#ifdef NO_NAKED

void _APICALL _V2FNormalE2K(float *a,float *b)
{
	asm( "{ nop 2; ldw,0 [0+%0],%%r4; ldw,2 [4+%0],%%r5; return %%ctpr3 }"
		 "{ fmuls,0 %%r5,%%r5,%%r6; fmuls,3 %%r4,%%r4,%%r7; fadds,4 %%r6,%%r7,%%r7; fsqrts,5 %%r7,%%r7; }"
		 "{ fdivs,5 %2,%%r7,%%r7; }"
		 "{ fmuls,0 %%r5,%%r7,%%r5; fmuls,3 %%r4,%%r7,%%r4; }"
		 "{ stw,2 [0+%1],%%r4; stw,5 [4+%1],%%r5; ct %%ctpr3; ipd 2 }"
		:
		:"r"(a), "r"(b), "r"(1.0f) );
}

void _APICALL _V3FNormalE2K(float *a,float *b)
{
	asm( "{ nop 2; ldw,0 [0+%0],%%r4; ldw,2 [4+%0],%%r5; ldw,3 [8+%0],%%r6; return %%ctpr3 }"
		 "{ fmuls,0 %%r5,%%r5,%%r7; fmuls,3 %%r4,%%r4,%%r8; fmuls,4 %%r6,%%r6,%%r9; }"
		 "{ fadds,0 %%r8,%%r7,%%r7; fadds,1 %%r9,%%r7,%%r7;  fsqrts,5 %%r7,%%r7; }"
		 "{ fdivs,5 %2,%%r7,%%r7; }"
		 "{ fmuls,0 %%r5,%%r7,%%r5; fmuls,3 %%r4,%%r7,%%r4; fmuls,4 %%r6,%%r7,%%r6; }"
		 "{ stw,2 [0+%1],%%r4; stw,5 [4+%1],%%r5; }"
		 "{ stw,2 [8+%1],%%r6; ct %%ctpr3; ipd 2 }"
		:
		:"r"(a), "r"(b), "r"(1.0f) );
}

void _APICALL _V4FNormalE2K(float *a,float *b)
{
	asm( "{ nop 2; ldw,0 [0+%0],%%r4; ldw,2 [4+%0],%%r5; ldw,3 [8+%0],%%r6; ldw,5 [12+%0],%%r7; return %%ctpr3 }"
		 "{ fmuls,3 %%r4,%%r4,%%r8; fmuls,0 %%r5,%%r5,%%r9; fmuls,4 %%r6,%%r6,%%r10; }"
		 "{ fmuls,0 %%r7,%%r7,%%r11; fadds,1 %%r8,%%r9,%%r9; fadds,3 %%r9,%%r10,%%r10; fadds,4 %%r10,%%r11,%%r11; fsqrts,5 %%r11,%%r11; }"
		 "{ fdivs,5 %2,%%r11,%%r11; }"
		 "{ fmuls,0 %%r5,%%r11,%%r5; fmuls,3 %%r4,%%r11,%%r4; fmuls,4 %%r6,%%r11,%%r6; }"
		 "{ fmuls,0 %%r7,%%r11,%%r7; stw,2 [0+%1],%%r4; stw,5 [4+%1],%%r5; }"
		 "{ stw,2 [8+%1],%%r6; stw,5 [12+%1],%%r7; ct %%ctpr3; ipd 2 }"
		:
		:"r"(a), "r"(b), "r"(1.0f) );
}

void _APICALL _V2DNormalE2K(double *a,double *b)
{
	asm( "{ nop 2; ldd,0 [0+%0],%%dr4; ldd,2 [8+%0],%%dr5; return %%ctpr3 }"
		 "{ fmuld,0 %%dr5,%%dr5,%%dr6; fmuld,3 %%dr4,%%dr4,%%dr7; faddd,4 %%dr6,%%dr7,%%dr7; fsqrtid,5 %%dr7,%%dr8 }"
		 "{ fsqrttd %%dr8,%%dr7,%%dr7 } "
		 "{ fdivd,5 %2,%%dr7,%%dr7; }"
		 "{ fmuld,0 %%dr5,%%dr7,%%dr5; fmuld,3 %%dr4,%%dr7,%%dr4; }"
		 "{ std,2 [0+%1],%%dr4; std,5 [8+%1],%%dr5; ct %%ctpr3; ipd 2 }"
		:
		:"r"(a), "r"(b), "r"(1.0) );
}

void _APICALL _V3DNormalE2K(double *a,double *b)
{
	asm( "{ nop 2; ldd,0 [0+%0],%%dr4; ldd,2 [8+%0],%%dr5; ldd,3 [16+%0],%%dr6; return %%ctpr3 }"
		 "{ fmuld,0 %%dr5,%%dr5,%%dr7; fmuld,3 %%dr4,%%dr4,%%dr8; fmuld,4 %%dr6,%%dr6,%%dr9; }"
		 "{ faddd,0 %%dr8,%%dr7,%%dr7; faddd,1 %%dr9,%%dr7,%%dr7; fsqrtid,5 %%dr7,%%dr8 }"
		 "{ fsqrttd %%dr8,%%dr7,%%dr7 } "
		 "{ fdivd,5 %2,%%dr7,%%dr7; }"
		 "{ fmuld,0 %%dr5,%%dr7,%%dr5; fmuld,3 %%dr4,%%dr7,%%dr4; fmuld,4 %%dr6,%%dr7,%%dr6; }"
		 "{ std,2 [0+%1],%%dr4; std,5 [8+%1],%%dr5; }"
		 "{ stw,2 [16+%1],%%r6; ct %%ctpr3; ipd 2 }"
		:
		:"r"(a), "r"(b), "r"(1.0) );
}

void _APICALL _V4DNormalE2K(double *a,double *b)
{
	asm( "{ nop 2; ldd,0 [0+%0],%%dr4; ldd,2 [8+%0],%%dr5; ldd,3 [16+%0],%%dr6; ldd,5 [24+%0],%%dr7; return %%ctpr3 }"
		 "{ fmuld,3 %%dr4,%%dr4,%%dr8; fmuld,0 %%dr5,%%dr5,%%dr9; fmuld,4 %%dr6,%%dr6,%%dr10; }"
		 "{ fmuld,0 %%dr7,%%dr7,%%dr11; faddd,1 %%dr8,%%dr9,%%dr9; faddd,3 %%dr9,%%dr10,%%dr10; faddd,4 %%dr10,%%dr11,%%dr11; fsqrtid,5 %%dr11,%%dr10 }"
		 "{ fsqrttd %%dr10,%%dr11,%%dr11 } "
		 "{ fdivd,5 %2,%%dr11,%%dr11; }"
		 "{ fmuld,0 %%dr5,%%dr11,%%dr5; fmuld,3 %%dr4,%%dr11,%%dr4; fmuld,4 %%dr6,%%dr11,%%dr6; }"
		 "{ fmuld,0 %%dr7,%%dr11,%%dr7; std,2 [0+%1],%%dr4; std,5 [8+%1],%%dr5; }"
		 "{ stw,2 [16+%1],%%r6; stw,5 [24+%1],%%r7; ct %%ctpr3; ipd 2 }"
		:
		:"r"(a), "r"(b), "r"(1.0) );
}

#endif

// ************** add triangle normal default function *******************

#ifdef NO_NAKED

void _APICALL _V3FAddTriNormE2K(float * _a,float * _b,float * _c,int off)
{
/*	asm( "{ nop 2; ldw,0 [0+%0],%%r4; ldw,2 [4+%0],%%r5; ldw,3 [8+%0],%%r6; return %%ctpr3 }"
		 "{ fmuls,0 %%r5,%%r5,%%r7; fmuls,3 %%r4,%%r4,%%r8; fmuls,4 %%r6,%%r6,%%r9; }"
		 "{ fadds,0 %%r8,%%r7,%%r7; fadds,1 %%r9,%%r7,%%r7;  fsqrts,5 %%r7,%%r7; }"
		 "{ fdivs,5 %4,%%r7,%%r7; }"
		 "{ fmuls,0 %%r5,%%r7,%%r5; fmuls,3 %%r4,%%r7,%%r4; fmuls,4 %%r6,%%r7,%%r6; }"
		 "{ stw,2 [0+%1],%%r4; stw,5 [4+%1],%%r5; }"
		 "{ stw,2 [8+%1],%%r6; ct %%ctpr3; ipd 2 }"
		:
		:"r"(a), "r"(b), "r"(c), "r"(off), "r"(1.0f) );*/
}

#endif

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif