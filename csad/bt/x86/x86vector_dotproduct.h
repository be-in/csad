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

#ifndef GEN3_VECTOR_DOT_H
#define GEN3_VECTOR_DOT_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

// для DOT PRODUCT
// не дает прирост производительности оптиизация на инсрукциях SSE, SSE2, SSE3
// падение производительности из за использования памяти для возврата результата

//**************************** DOT PRODUCT STDCALL *********************************
// vector dot product eax=[esp+4]-a void * edx=[esp+8]-b void *

/// Скалярное произведение двухмерных векторов одинарной точности, команды FPU
#define VECTORP2DDOTPRODUCTFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xD8,0x0A )                                         /* fmul        dword ptr [edx]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x4A,0x04 )                                    /* fmul        dword ptr [edx+4]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st */ \
_END_ASM

/// Скалярное произведение двухмерных векторов одинарной точности, команды SSE4
#define VECTORP2DDOTPRODUCTSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,mmword ptr [edx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC1,0x31 )                     /* dpps        xmm0,xmm1,31h  */ \
_LINE6( 0xF3,0x0F,0x11,0x44,0x24,0xDC )                     /* movss       dword ptr [esp-24h],xmm0  */ \
_LINE4( 0xD9,0x44,0x24,0xDC )                               /* fld         dword ptr [esp-24h]  */ \
_END_ASM

/// Скалярное произведение трехмерных векторов одинарной точности, команды FPU
#define VECTORP3DDOTPRODUCTFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xD8,0x0A )                                         /* fmul        dword ptr [edx]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x4A,0x04 )                                    /* fmul        dword ptr [edx+4]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD8,0x4A,0x08 )                                    /* fmul        dword ptr [edx+8]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// Скалярное произведение трехмерных векторов одинарной точности, команды SSE4
#define VECTORP3DDOTPRODUCTSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE3( 0x0F,0x16,0x00 )                                    /* movhps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x16,0x0A )                                    /* movhps      xmm1,qword ptr [edx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC1,0xD1 )                     /* dpps        xmm0,xmm1,0D1h  */ \
_LINE6( 0xF3,0x0F,0x11,0x44,0x24,0xDC )                     /* movss       dword ptr [esp-24h],xmm0  */ \
_LINE4( 0xD9,0x44,0x24,0xDC )                               /* fld         dword ptr [esp-24h]  */ \
_END_ASM

/// Скалярное произведение четырехмерных векторов одинарной точности, команды FPU
#define VECTORP4DDOTPRODUCTFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xD8,0x0A )                                         /* fmul        dword ptr [edx]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x4A,0x04 )                                    /* fmul        dword ptr [edx+4]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD8,0x4A,0x08 )                                    /* fmul        dword ptr [edx+8]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x40,0x0C )                                    /* fld         dword ptr [eax+0Ch]  */ \
_LINE3( 0xD8,0x4A,0x0C )                                    /* fmul        dword ptr [edx+0Ch]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// Скалярное произведение четырехмерных векторов одинарной точности, команды SSE ???
#define VECTORP4DDOTPRODUCTSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
ASM( movss   xmm0, dword ptr [eax+4] ) \
ASM( movss   xmm1, dword ptr [eax] ) \
ASM( movss   xmm2, dword ptr [eax+8] ) \
ASM( mulss   xmm0, dword ptr [edx+4] ) \
ASM( mulss   xmm1, dword ptr [edx] ) \
ASM( mulss   xmm2, dword ptr [edx+8] ) \
ASM( addss   xmm0, xmm1 ) \
ASM( movss   xmm3, dword ptr [eax+0x0C] ) \
ASM( addss   xmm0, xmm2 ) \
ASM( mulss   xmm3, dword ptr [edx+0x0C] ) \
ASM( addss   xmm0, xmm3 ) \
_LINE6( 0xF3,0x0F,0x11,0x44,0x24,0xDC )                     /* movss       dword ptr [esp-24h],xmm0  */ \
_LINE4( 0xD9,0x44,0x24,0xDC )                               /* fld         dword ptr [esp-24h]  */ \
_END_ASM

/// Скалярное произведение четырехмерных векторов одинарной точности, команды SSE4
#define VECTORP4DDOTPRODUCTSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC1,0xF1 )                     /* dpps        xmm0,xmm1,0F1h  */ \
_LINE6( 0xF3,0x0F,0x11,0x44,0x24,0xDC )                     /* movss       dword ptr [esp-24h],xmm0  */ \
_LINE4( 0xD9,0x44,0x24,0xDC )                               /* fld         dword ptr [esp-24h]  */ \
_END_ASM

/// Скалярное произведение двухмерных векторов двойной точности, команды FPU
#define VECTORP2DDDOTPRODUCTFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xDD,0x00 )                                         /* fld         qword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xDC,0x0A )                                         /* fmul        qword ptr [edx]  */ \
_LINE3( 0xDD,0x40,0x08 )                                    /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDC,0x4A,0x08 )                                    /* fmul        qword ptr [edx+8]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// Скалярное произведение двухмерных векторов двойной точности, команды SSE4
#define VECTORP2DDDOTPRODUCTSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC1,0x31 )                     /* dppd        xmm0,xmm1,31h  */ \
_LINE6( 0xF2,0x0F,0x11,0x44,0x24,0xDC )                     /* movsd       mmword ptr [esp-24h],xmm0  */ \
_LINE4( 0xDD,0x44,0x24,0xDC )                               /* fld         qword ptr [esp-24h]  */ \
_END_ASM

/// Скалярное произведение трехмерных векторов двойной точности, команды FPU
#define VECTORP3DDDOTPRODUCTFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xDD,0x00 )                                         /* fld         qword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xDC,0x0A )                                         /* fmul        qword ptr [edx]  */ \
_LINE3( 0xDD,0x40,0x08 )                                    /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDC,0x4A,0x08 )                                    /* fmul        qword ptr [edx+8]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x40,0x10 )                                    /* fld         qword ptr [eax+10h]  */ \
_LINE3( 0xDC,0x4A,0x10 )                                    /* fmul        qword ptr [edx+10h]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// Скалярное произведение трехмерных векторов двойной точности, команды SSE4
#define VECTORP3DDDOTPRODUCTSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC1,0x31 )                     /* dppd        xmm0,xmm1,31h  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x5A,0x10 )                          /* movsd       xmm3,mmword ptr [edx+10h]  */ \
_LINE4( 0xF2,0x0F,0x59,0xD3 )                               /* mulsd       xmm2,xmm3  */ \
_LINE4( 0xF2,0x0F,0x58,0xC2 )                               /* addsd       xmm0,xmm2  */ \
_LINE6( 0xF2,0x0F,0x11,0x44,0x24,0xDC )                     /* movsd       mmword ptr [esp-24h],xmm0  */ \
_LINE4( 0xDD,0x44,0x24,0xDC )                               /* fld         qword ptr [esp-24h]  */ \
_END_ASM

/// Скалярное произведение четырехмерных векторов двойной точности, команды FPU
#define VECTORP4DDDOTPRODUCTFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xDD,0x00 )                                         /* fld         qword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xDC,0x0A )                                         /* fmul        qword ptr [edx]  */ \
_LINE3( 0xDD,0x40,0x08 )                                    /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDC,0x4A,0x08 )                                    /* fmul        qword ptr [edx+8]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x40,0x10 )                                    /* fld         qword ptr [eax+10h]  */ \
_LINE3( 0xDC,0x4A,0x10 )                                    /* fmul        qword ptr [edx+10h]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x40,0x18 )                                    /* fld         qword ptr [eax+18h]  */ \
_LINE3( 0xDC,0x4A,0x18 )                                    /* fmul        qword ptr [edx+18h]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// Скалярное произведение четырехмерных векторов двойной точности, команды SSE4
#define VECTORP4DDDOTPRODUCTSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC1,0x31 )                     /* dppd        xmm0,xmm1,31h  */ \
_LINE5( 0xF2,0x0F,0xF0,0x50,0x10 )                          /* lddqu       xmm2,xmmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x5A,0x10 )                          /* lddqu       xmm3,xmmword ptr [edx+10h]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xD3,0x31 )                     /* dppd        xmm2,xmm3,31h  */ \
_LINE4( 0xF2,0x0F,0x58,0xC2 )                               /* addsd       xmm0,xmm2  */ \
_LINE6( 0xF2,0x0F,0x11,0x44,0x24,0xDC )                     /* movsd       mmword ptr [esp-24h],xmm0  */ \
_LINE4( 0xDD,0x44,0x24,0xDC )                               /* fld         qword ptr [esp-24h]  */ \
_END_ASM

/// Скалярное произведение четырехмерных векторов двойной точности, команды AVX ???
#define VECTORP4DDDOTPRODUCTAVX_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xC5,0xFD,0x10,0x00 )                /* vmovupd     ymm0,ymmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xC5,0xFD,0x10,0x0A )                /* vmovupd     ymm1,ymmword ptr [edx]  */ \
ASM( vdppd       xmm2,xmm1,xmm0,0xF1 )       /* vdppd       ymm2,ymm1,ymm0,F1h  */ \
ASM( vmovsd   [esp-0x24],xmm2 )    /* vmovsd       mmword ptr [esp-24h],ymm0  */ \
_LINE4( 0xDD,0x44,0x24,0xDC )                /* fld         qword ptr [esp-24h]  */ \
_LINE3( 0xC5,0xF8,0x77 )                /* vzeroupper  */ \
_END_ASM

//**************************** DOT PRODUCT REGISTER FASTCALL *********************************
// vector dot product eax-a void * edx-b void *

/// Скалярное произведение двухмерных векторов одинарной точности, команды FPU
#define VECTORP2DDOTPRODUCTFPU \
BEGIN_ASM \
_ASM FLD  DWORD PTR [EAX] \
_ASM FMUL DWORD PTR [EDX] \
_ASM FLD  DWORD PTR [EAX+4] \
_ASM FMUL DWORD PTR [EDX+4] \
_ASM FADDP ST(1),ST(0) \
END_ASM

/// Скалярное произведение двухмерных векторов одинарной точности, команды SSE3
#define VECTORP2DDOTPRODUCTSSE3 \
BEGIN_ASM \
_ASM movlps xmm0,[eax] \
_ASM movlps xmm1,[edx] \
_ASM mulps xmm0,xmm1 \
_ASM haddps xmm0,xmm0 \
_ASM lea eax,[esp-_STACKFREE] \
_ASM movss dword ptr [eax],xmm0 \
_ASM fld dword ptr [eax] \
END_ASM

/*
_ASM movss xmm0,[eax] \
_ASM mulss xmm0,[edx] \
_ASM movss xmm1,[eax+4] \
_ASM mulss xmm1,[edx+4] \
*/

/// Скалярное произведение двухмерных векторов одинарной точности, команды SSE4
#define VECTORP2DDOTPRODUCTSSE4 \
BEGIN_ASM \
_ASM movsd xmm0,[eax] \
_ASM movsd xmm1,[edx] \
_ASM dpps xmm0, xmm1, 0x31 \
_ASM movss [esp-_STACKFREE], xmm0 \
_ASM fld dword ptr [esp-_STACKFREE] \
END_ASM

/// Скалярное произведение трехмерных векторов одинарной точности, команды FPU
#define VECTORP3DDOTPRODUCTFPU \
_BEGIN_ASM \
 _STR(_DB(0xD9) _DB(0x00)) \
 _STR(_DB(0xD8) _DB(0x0A)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
 _STR(_DB(0xD8) _DB(0x4A) _DB(0x04)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xD8) _DB(0x4A) _DB(0x08)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
_END_ASM

/// Скалярное произведение трехмерных векторов одинарной точности, команды SSE4
#define VECTORP3DDOTPRODUCTSSE4 \
BEGIN_ASM \
_ASM movss xmm0,[eax+8] \
_ASM movss xmm1,[edx+8] \
_ASM movhps xmm0,[eax] \
_ASM movhps xmm1,[edx] \
_ASM dpps xmm0, xmm1, 0xD1 \
_ASM movss [esp-_STACKFREE], xmm0 \
_ASM fld dword ptr [esp-_STACKFREE] \
END_ASM

/// Скалярное произведение четырехмерных векторов одинарной точности, команды FPU
#define VECTORP4DDOTPRODUCTFPU \
_BEGIN_ASM \
 _STR(_DB(0xD9) _DB(0x00)) \
 _STR(_DB(0xD8) _DB(0x0A)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
 _STR(_DB(0xD8) _DB(0x4A) _DB(0x04)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xD8) _DB(0x4A) _DB(0x08)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x0C)) \
 _STR(_DB(0xD8) _DB(0x4A) _DB(0x0C)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
_END_ASM

/// Скалярное произведение четырехмерных векторов одинарной точности, команды SSE3
#define VECTORP4DDOTPRODUCTSSE3 \
BEGIN_ASM \
_ASM lddqu xmm0,[eax] \
_ASM lddqu xmm1,[edx] \
_ASM mulps xmm0, xmm1 \
_ASM haddps xmm0, xmm0 \
_ASM movss xmm3, xmm0 \
_ASM psrlq xmm0, 32 \
_ASM addss xmm0, xmm3 \
_ASM movss [esp-_STACKFREE], xmm0 \
_ASM fld dword ptr [esp-_STACKFREE] \
END_ASM

/// Скалярное произведение четырехмерных векторов одинарной точности, команды SSE4
#define VECTORP4DDOTPRODUCTSSE4 \
BEGIN_ASM \
_ASM lddqu xmm0, [eax] \
_ASM lddqu xmm1, [edx] \
_ASM dpps xmm0, xmm1, 0xf1 \
_ASM movss [esp-_STACKFREE], xmm0 \
_ASM fld dword ptr [esp-_STACKFREE] \
END_ASM

/// Скалярное произведение двухмерных векторов двойной точности, команды FPU
#define VECTORP2DDDOTPRODUCTFPU \
_BEGIN_ASM \
 _STR(_DB(0xDD) _DB(0x00)) \
 _STR(_DB(0xDC) _DB(0x0A)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x4A) _DB(0x08)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
_END_ASM

/// Скалярное произведение двухмерных векторов двойной точности, команды SSE4
#define VECTORP2DDDOTPRODUCTSSE4 \
BEGIN_ASM \
_ASM lddqu xmm0, [eax] \
_ASM lddqu xmm1, [edx] \
_ASM dppd xmm0, xmm1, 0x31 \
_ASM movsd [esp-_STACKFREE], xmm0 \
_ASM fld qword ptr [esp-_STACKFREE] \
END_ASM

/// Скалярное произведение трехмерных векторов двойной точности, команды FPU
#define VECTORP3DDDOTPRODUCTFPU \
_BEGIN_ASM \
 _STR(_DB(0xDD) _DB(0x00)) \
 _STR(_DB(0xDC) _DB(0x0A)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x4A) _DB(0x08)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x10)) \
 _STR(_DB(0xDC) _DB(0x4A) _DB(0x10)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
_END_ASM

/// Скалярное произведение трехмерных векторов двойной точности, команды SSE4
#define VECTORP3DDDOTPRODUCTSSE4 \
BEGIN_ASM \
_ASM lddqu xmm0, [eax] \
_ASM lddqu xmm1, [edx] \
_ASM dppd xmm0, xmm1, 0x31 \
_ASM movsd xmm2, [eax+16] \
_ASM movsd xmm3, [edx+16] \
_ASM mulsd xmm2, xmm3 \
_ASM addsd xmm0,xmm2 \
_ASM movsd [esp-_STACKFREE], xmm0 \
_ASM fld qword ptr [esp-_STACKFREE] \
END_ASM

/// Скалярное произведение четырехмерных векторов двойной точности, команды FPU
#define VECTORP4DDDOTPRODUCTFPU \
_BEGIN_ASM \
 _STR(_DB(0xDD) _DB(0x00)) \
 _STR(_DB(0xDC) _DB(0x0A)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x4A) _DB(0x08)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x10)) \
 _STR(_DB(0xDC) _DB(0x4A) _DB(0x10)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x18)) \
 _STR(_DB(0xDC) _DB(0x4A) _DB(0x18)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
_END_ASM

/// Скалярное произведение четырехмерных векторов двойной точности, команды SSE3
#define VECTORP4DDDOTPRODUCTSSE3 \
BEGIN_ASM \
_ASM lddqu xmm0,[eax] \
_ASM lddqu xmm1,[edx] \
_ASM lddqu xmm2,[eax+16] \
_ASM lddqu xmm3,[edx+16] \
_ASM mulpd xmm0,xmm1 \
_ASM mulpd xmm2,xmm3 \
_ASM addpd xmm0,xmm2 \
_ASM haddpd xmm0,xmm0 \
_ASM movsd qword ptr [esp-_STACKFREE],xmm0 \
_ASM fld qword ptr [esp-_STACKFREE] \
END_ASM

/*_LINE3(0x0F,0x10,0x00) \
_LINE3(0x0F,0x10,0x0A) \
_LINE4(0x0F,0x10,0x50,0x10) \
_LINE4(0x0F,0x10,0x5A,0x10) \
_LINE4(0x66,0x0F,0x59,0xC1) \
_LINE4(0x66,0x0F,0x59,0xCB) \
_LINE4(0x66,0x0F,0x58,0xC2) \
_LINE4(0x66,0x0F,0x7C,0xC0) \
_LINE6(0xF2,0x0F,0x11,0x44,0x24,0xE0) \
_LINE4(0xDD,0x44,0x24,0xE0) \*/

/// Скалярное произведение четырехмерных векторов двойной точности, команды SSE4
#define VECTORP4DDDOTPRODUCTSSE4 \
BEGIN_ASM \
_ASM lddqu xmm0, [eax] \
_ASM lddqu xmm1, [edx] \
_ASM dppd xmm0, xmm1, 0x31 \
_ASM lddqu xmm2, [eax+16] \
_ASM lddqu xmm3, [edx+16] \
_ASM dppd xmm2, xmm3, 0x31 \
_ASM addsd xmm0,xmm2 \
_ASM movsd [esp-_STACKFREE], xmm0 \
_ASM fld qword ptr [esp-_STACKFREE] \
END_ASM

//**************************** DOT PRODUCT CPP FASTCALL *********************************
// vector dot product eax-a void * edx-b void *

/// Скалярное произведение двухмерных векторов одинарной точности, команды FPU
#define VECTORP2DDOTPRODUCTFPU_CPP \
_BEGIN_ASM \
_LINE2( 0xD9,0x01 )                                         /* fld         dword ptr [ecx]  */ \
_LINE2( 0xD8,0x0A )                                         /* fmul        dword ptr [edx]  */ \
_LINE3( 0xD9,0x41,0x04 )                                    /* fld         dword ptr [ecx+4]  */ \
_LINE3( 0xD8,0x4A,0x04 )                                    /* fmul        dword ptr [edx+4]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// Скалярное произведение двухмерных векторов одинарной точности, команды SSE4
#define VECTORP2DDOTPRODUCTSSE4_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x01 )                               /* movsd       xmm0,mmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,mmword ptr [edx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC1,0x31 )                     /* dpps        xmm0,xmm1,31h  */ \
_LINE6( 0xF3,0x0F,0x11,0x44,0x24,0xDC )                     /* movss       dword ptr [esp-24h],xmm0  */ \
_LINE4( 0xD9,0x44,0x24,0xDC )                               /* fld         dword ptr [esp-24h]  */ \
_END_ASM

/// Скалярное произведение трехмерных векторов одинарной точности, команды FPU
#define VECTORP3DDOTPRODUCTFPU_CPP \
_BEGIN_ASM \
_LINE2( 0xD9,0x01 )                                         /* fld         dword ptr [ecx]  */ \
_LINE2( 0xD8,0x0A )                                         /* fmul        dword ptr [edx]  */ \
_LINE3( 0xD9,0x41,0x04 )                                    /* fld         dword ptr [ecx+4]  */ \
_LINE3( 0xD8,0x4A,0x04 )                                    /* fmul        dword ptr [edx+4]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x41,0x08 )                                    /* fld         dword ptr [ecx+8]  */ \
_LINE3( 0xD8,0x4A,0x08 )                                    /* fmul        dword ptr [edx+8]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// Скалярное произведение трехмерных векторов одинарной точности, команды SSE4
#define VECTORP3DDOTPRODUCTSSE4_CPP \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x41,0x08 )                          /* movss       xmm0,dword ptr [ecx+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE3( 0x0F,0x16,0x01 )                                    /* movhps      xmm0,qword ptr [ecx]  */ \
_LINE3( 0x0F,0x16,0x0A )                                    /* movhps      xmm1,qword ptr [edx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC1,0xD1 )                     /* dpps        xmm0,xmm1,0D1h  */ \
_LINE6( 0xF3,0x0F,0x11,0x44,0x24,0xDC )                     /* movss       dword ptr [esp-24h],xmm0  */ \
_LINE4( 0xD9,0x44,0x24,0xDC )                               /* fld         dword ptr [esp-24h]  */ \
_END_ASM

/// Скалярное произведение четырехмерных векторов одинарной точности, команды FPU
#define VECTORP4DDOTPRODUCTFPU_CPP \
_BEGIN_ASM \
_LINE2( 0xD9,0x01 )                                         /* fld         dword ptr [ecx]  */ \
_LINE2( 0xD8,0x0A )                                         /* fmul        dword ptr [edx]  */ \
_LINE3( 0xD9,0x41,0x04 )                                    /* fld         dword ptr [ecx+4]  */ \
_LINE3( 0xD8,0x4A,0x04 )                                    /* fmul        dword ptr [edx+4]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x41,0x08 )                                    /* fld         dword ptr [ecx+8]  */ \
_LINE3( 0xD8,0x4A,0x08 )                                    /* fmul        dword ptr [edx+8]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x41,0x0C )                                    /* fld         dword ptr [ecx+0Ch]  */ \
_LINE3( 0xD8,0x4A,0x0C )                                    /* fmul        dword ptr [edx+0Ch]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// Скалярное произведение четырехмерных векторов одинарной точности, команды SSE4
#define VECTORP4DDOTPRODUCTSSE4_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC1,0xF1 )                     /* dpps        xmm0,xmm1,0F1h  */ \
_LINE6( 0xF3,0x0F,0x11,0x44,0x24,0xDC )                     /* movss       dword ptr [esp-24h],xmm0  */ \
_LINE4( 0xD9,0x44,0x24,0xDC )                               /* fld         dword ptr [esp-24h]  */ \
_END_ASM

/// Скалярное произведение двухмерных векторов одинарной точности, команды FPU
#define VECTORP2DDDOTPRODUCTFPU_CPP \
_BEGIN_ASM \
_LINE2( 0xDD,0x01 )                                         /* fld         qword ptr [ecx]  */ \
_LINE2( 0xDC,0x0A )                                         /* fmul        qword ptr [edx]  */ \
_LINE3( 0xDD,0x41,0x08 )                                    /* fld         qword ptr [ecx+8]  */ \
_LINE3( 0xDC,0x4A,0x08 )                                    /* fmul        qword ptr [edx+8]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// Скалярное произведение двухмерных векторов двойной точности, команды SSE4
#define VECTORP2DDDOTPRODUCTSSE4_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC1,0x31 )                     /* dppd        xmm0,xmm1,31h  */ \
_LINE6( 0xF2,0x0F,0x11,0x44,0x24,0xDC )                     /* movsd       mmword ptr [esp-24h],xmm0  */ \
_LINE4( 0xDD,0x44,0x24,0xDC )                               /* fld         qword ptr [esp-24h]  */ \
_END_ASM

/// Скалярное произведение трехмерных векторов двойной точности, команды FPU
#define VECTORP3DDDOTPRODUCTFPU_CPP \
_BEGIN_ASM \
_LINE2( 0xDD,0x01 )                                         /* fld         qword ptr [ecx]  */ \
_LINE2( 0xDC,0x0A )                                         /* fmul        qword ptr [edx]  */ \
_LINE3( 0xDD,0x41,0x08 )                                    /* fld         qword ptr [ecx+8]  */ \
_LINE3( 0xDC,0x4A,0x08 )                                    /* fmul        qword ptr [edx+8]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x41,0x10 )                                    /* fld         qword ptr [ecx+10h]  */ \
_LINE3( 0xDC,0x4A,0x10 )                                    /* fmul        qword ptr [edx+10h]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// Скалярное произведение трехмерных векторов двойной точности, команды SSE4
#define VECTORP3DDDOTPRODUCTSSE4_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC1,0x31 )                     /* dppd        xmm0,xmm1,31h  */ \
_LINE5( 0xF2,0x0F,0x10,0x51,0x10 )                          /* movsd       xmm2,mmword ptr [ecx+10h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x5A,0x10 )                          /* movsd       xmm3,mmword ptr [edx+10h]  */ \
_LINE4( 0xF2,0x0F,0x59,0xD3 )                               /* mulsd       xmm2,xmm3  */ \
_LINE4( 0xF2,0x0F,0x58,0xC2 )                               /* addsd       xmm0,xmm2  */ \
_LINE6( 0xF2,0x0F,0x11,0x44,0x24,0xDC )                     /* movsd       mmword ptr [esp-24h],xmm0  */ \
_LINE4( 0xDD,0x44,0x24,0xDC )                               /* fld         qword ptr [esp-24h]  */ \
_END_ASM

/// Скалярное произведение четырехмерных векторов двойной точности, команды FPU
#define VECTORP4DDDOTPRODUCTFPU_CPP \
_BEGIN_ASM \
_LINE2( 0xDD,0x01 )                                         /* fld         qword ptr [ecx]  */ \
_LINE2( 0xDC,0x0A )                                         /* fmul        qword ptr [edx]  */ \
_LINE3( 0xDD,0x41,0x08 )                                    /* fld         qword ptr [ecx+8]  */ \
_LINE3( 0xDC,0x4A,0x08 )                                    /* fmul        qword ptr [edx+8]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x41,0x10 )                                    /* fld         qword ptr [ecx+10h]  */ \
_LINE3( 0xDC,0x4A,0x10 )                                    /* fmul        qword ptr [edx+10h]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x41,0x18 )                                    /* fld         qword ptr [ecx+18h]  */ \
_LINE3( 0xDC,0x4A,0x18 )                                    /* fmul        qword ptr [edx+18h]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// Скалярное произведение четырехмерных векторов двойной точности, команды SSE4
#define VECTORP4DDDOTPRODUCTSSE4_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC1,0x31 )                     /* dppd        xmm0,xmm1,31h  */ \
_LINE5( 0xF2,0x0F,0xF0,0x51,0x10 )                          /* lddqu       xmm2,xmmword ptr [ecx+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x5A,0x10 )                          /* lddqu       xmm3,xmmword ptr [edx+10h]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xD3,0x31 )                     /* dppd        xmm2,xmm3,31h  */ \
_LINE4( 0xF2,0x0F,0x58,0xC2 )                               /* addsd       xmm0,xmm2  */ \
_LINE6( 0xF2,0x0F,0x11,0x44,0x24,0xDC )                     /* movsd       mmword ptr [esp-24h],xmm0  */ \
_LINE4( 0xDD,0x44,0x24,0xDC )                               /* fld         qword ptr [esp-24h]  */ \
_END_ASM

#endif