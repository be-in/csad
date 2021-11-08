//=============================================================================
///**
// *  @file vector_crossproduct.h
// *
// *  $Id: vector_crossproduct.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float cross product, MS Visual C++ 2003-2008
// *
// *  @author Pant_eleymonov Alek_sandr Kons_tantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_VECTOR_CROSS_PRODUCT_H
#define GEN3_VECTOR_CROSS_PRODUCT_H

//**************************** CROSS PRODUCT STDCALL *********************************
// vector cross product eax=[esp+4]-a void * edx=[esp+8]-b void * ecx=[esp+12]-rez void *

/// ¬екторное умножение трехмерных векторов одинарной точности, команды FPU
#define VECTORP3DCROSSPRODUCTFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )        /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0x00 )                  /* fld         dword ptr [eax]  */ \
_LINE3( 0xD9,0x40,0x04 )             /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x40,0x08 )             /* fld         dword ptr [eax+8]  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )        /* mov         eax,dword ptr [esp+8]  */ \
_LINE2( 0xD9,0x00 )                  /* fld         dword ptr [eax]  */ \
_LINE3( 0xD9,0x40,0x04 )             /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x40,0x08 )             /* fld         dword ptr [eax+8]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )        /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE2( 0xD9,0xC0 )                  /* fld         st(0)  */ \
_LINE2( 0xD8,0xCD )                  /* fmul        st,st(5)  */ \
_LINE2( 0xD9,0xC2 )                  /* fld         st(2)  */ \
_LINE2( 0xD8,0xCD )                  /* fmul        st,st(5)  */ \
_LINE2( 0xDE,0xE9 )                  /* fsubp       st(1),st  */ \
_LINE2( 0xD9,0x18 )                  /* fstp        dword ptr [eax]  */ \
_LINE2( 0xD9,0xC2 )                  /* fld         st(2)  */ \
_LINE2( 0xDE,0xCC )                  /* fmulp       st(4),st  */ \
_LINE2( 0xD8,0xCD )                  /* fmul        st,st(5)  */ \
_LINE2( 0xDE,0xEB )                  /* fsubp       st(3),st  */ \
_LINE2( 0xD9,0xCA )                  /* fxch        st(2)  */ \
_LINE3( 0xD9,0x58,0x04 )             /* fstp        dword ptr [eax+4]  */ \
_LINE2( 0xD9,0xC9 )                  /* fxch        st(1)  */ \
_LINE2( 0xDE,0xCB )                  /* fmulp       st(3),st  */ \
_LINE2( 0xDE,0xC9 )                  /* fmulp       st(1),st  */ \
_LINE2( 0xDE,0xE9 )                  /* fsubp       st(1),st  */ \
_LINE3( 0xD9,0x58,0x08 )             /* fstp        dword ptr [eax+8]  */ \
_END_ASM

//_LINE4( 0xD9,0x6C,0x24,0xF4 )                               /* fldcw       word ptr [esp-12]  */ \

/// ¬екторное умножение трехмерных векторов одинарной точности, команды SSE
#define VECTORP3DCROSSPRODUCTSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE3( 0x0F,0x16,0x00 )                                    /* movhps      xmm0,qword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE3( 0x0F,0x16,0x0A )                                    /* movhps      xmm1,qword ptr [edx]  */ \
_LINE3( 0x0F,0x28,0xD0 )                                    /* movaps      xmm2,xmm0  */ \
_LINE3( 0x0F,0x28,0xD9 )                                    /* movaps      xmm3,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC0,0x32 )                               /* shufps      xmm0,xmm0,32h  */ \
_LINE4( 0x0F,0xC6,0xC9,0x83 )                               /* shufps      xmm1,xmm1,83h  */ \
_LINE4( 0x0F,0xC6,0xD2,0x83 )                               /* shufps      xmm2,xmm2,83h  */ \
_LINE4( 0x0F,0xC6,0xDB,0x32 )                               /* shufps      xmm3,xmm3,32h  */ \
_LINE3( 0x0F,0x59,0xC1 )                                    /* mulps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x59,0xD3 )                                    /* mulps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x5C,0xC2 )                                    /* subps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x17,0x01 )                                    /* movhps      qword ptr [ecx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x41,0x08 )                          /* movss       dword ptr [ecx+8],xmm0  */ \
_END_ASM

/// ¬екторное умножение трехмерных векторов двойной точности, команды FPU
#define VECTORP3DDCROSSPRODUCTFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )        /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xDD,0x00 )                  /* fld         dword ptr [eax]  */ \
_LINE3( 0xDD,0x40,0x08 )             /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xDD,0x40,0x10 )             /* fld         dword ptr [eax+16]  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )        /* mov         eax,dword ptr [esp+8]  */ \
_LINE2( 0xDD,0x00 )                  /* fld         dword ptr [eax]  */ \
_LINE3( 0xDD,0x40,0x08 )             /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xDD,0x40,0x10 )             /* fld         dword ptr [eax+16]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )        /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE2( 0xD9,0xC0 )                  /* fld         st(0)  */ \
_LINE2( 0xD8,0xCD )                  /* fmul        st,st(5)  */ \
_LINE2( 0xD9,0xC2 )                  /* fld         st(2)  */ \
_LINE2( 0xD8,0xCD )                  /* fmul        st,st(5)  */ \
_LINE2( 0xDE,0xE9 )                  /* fsubp       st(1),st  */ \
_LINE2( 0xDD,0x18 )                  /* fstp        dword ptr [eax]  */ \
_LINE2( 0xD9,0xC2 )                  /* fld         st(2)  */ \
_LINE2( 0xDE,0xCC )                  /* fmulp       st(4),st  */ \
_LINE2( 0xD8,0xCD )                  /* fmul        st,st(5)  */ \
_LINE2( 0xDE,0xEB )                  /* fsubp       st(3),st  */ \
_LINE2( 0xD9,0xCA )                  /* fxch        st(2)  */ \
_LINE3( 0xDD,0x58,0x08 )             /* fstp        dword ptr [eax+8]  */ \
_LINE2( 0xD9,0xC9 )                  /* fxch        st(1)  */ \
_LINE2( 0xDE,0xCB )                  /* fmulp       st(3),st  */ \
_LINE2( 0xDE,0xC9 )                  /* fmulp       st(1),st  */ \
_LINE2( 0xDE,0xE9 )                  /* fsubp       st(1),st  */ \
_LINE3( 0xDD,0x58,0x10 )             /* fstp        dword ptr [eax+16]  */ \
_END_ASM

/// ¬екторное умножение трехмерных векторов двойной точности, команды SSE2
#define VECTORP3DDCROSSPRODUCTSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x0F,0x12,0x40,0x10 )                               /* movlps      xmm0,qword ptr [eax+10h]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x12,0x50,0x08 )                               /* movlps      xmm2,qword ptr [eax+8]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x16,0x1A )                                    /* movhps      xmm3,qword ptr [edx]  */ \
_LINE3( 0x0F,0x16,0x10 )                                    /* movhps      xmm2,qword ptr [eax]  */ \
_LINE4( 0x0F,0x12,0x4A,0x10 )                               /* movlps      xmm1,qword ptr [edx+10h]  */ \
_LINE4( 0x0F,0x12,0x5A,0x08 )                               /* movlps      xmm3,qword ptr [edx+8]  */ \
_LINE3( 0x0F,0x12,0xE2 )                                    /* movhlps     xmm4,xmm2  */ \
_LINE3( 0x0F,0x12,0xEB )                                    /* movhlps     xmm5,xmm3  */ \
_LINE3( 0x0F,0x16,0xE0 )                                    /* movlhps     xmm4,xmm0  */ \
_LINE3( 0x0F,0x16,0xE9 )                                    /* movlhps     xmm5,xmm1  */ \
_LINE4( 0x66,0x0F,0x59,0xE3 )                               /* mulpd       xmm4,xmm3  */ \
_LINE4( 0x66,0x0F,0x59,0xEA )                               /* mulpd       xmm5,xmm2  */ \
_LINE4( 0xF2,0x0F,0x59,0xD8 )                               /* mulsd       xmm3,xmm0  */ \
_LINE4( 0xF2,0x0F,0x59,0xD1 )                               /* mulsd       xmm2,xmm1  */ \
_LINE4( 0x66,0x0F,0x5C,0xE5 )                               /* subpd       xmm4,xmm5  */ \
_LINE4( 0xF2,0x0F,0x5C,0xD3 )                               /* subsd       xmm2,xmm3  */ \
_LINE4( 0x0F,0x17,0x61,0x08 )                               /* movhps      qword ptr [ecx+8],xmm4  */ \
_LINE3( 0x0F,0x13,0x11 )                                    /* movlps      qword ptr [ecx],xmm2  */ \
_LINE4( 0x0F,0x13,0x61,0x10 )                               /* movlps      qword ptr [ecx+10h],xmm4  */ \
_END_ASM

//**************************** CROSS PRODUCT REGISTER FASTCALL *********************************
// vector cross product eax-a void * edx-b void * ecx-b void *

/// ¬екторное умножение трехмерных векторов одинарной точности, команды FPU
#define VECTORP3DCROSSPRODUCTFPU \
_BEGIN_ASM \
_LINE3( 0xD9,0x42,0x08 )                                    /* fld         dword ptr [edx+8]  */ \
_LINE3( 0xD9,0x42,0x04 )                                    /* fld         dword ptr [edx+4]  */ \
_LINE2( 0xD9,0x02 )                                         /* fld         dword ptr [edx]  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE2( 0xD9,0xC1 )                                         /* fld         st(1)  */ \
_LINE2( 0xD8,0xCE )                                         /* fmul        st,st(6)  */ \
_LINE2( 0xD9,0xC3 )                                         /* fld         st(3)  */ \
_LINE2( 0xD8,0xCE )                                         /* fmul        st,st(6)  */ \
_LINE2( 0xDE,0xE9 )                                         /* fsubp       st(1),st  */ \
_LINE2( 0xD9,0x19 )                                         /* fstp        dword ptr [ecx]  */ \
_LINE2( 0xD9,0xC2 )                                         /* fld         st(2)  */ \
_LINE2( 0xD8,0xCC )                                         /* fmul        st,st(4)  */ \
_LINE2( 0xD9,0xC1 )                                         /* fld         st(1)  */ \
_LINE2( 0xD8,0xCF )                                         /* fmul        st,st(7)  */ \
_LINE2( 0xDE,0xE9 )                                         /* fsubp       st(1),st  */ \
_LINE3( 0xD9,0x59,0x04 )                                    /* fstp        dword ptr [ecx+4]  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xD9,0xC2 )                                         /* fld         st(2)  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xDE,0xE9 )                                         /* fsubp       st(1),st  */ \
_LINE3( 0xD9,0x59,0x08 )                                    /* fstp        dword ptr [ecx+8]  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

/// ¬екторное умножение трехмерных векторов одинарной точности, команды SSE
#define VECTORP3DCROSSPRODUCTSSE \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE3( 0x0F,0x16,0x00 )                                    /* movhps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x16,0x0A )                                    /* movhps      xmm1,qword ptr [edx]  */ \
_LINE3( 0x0F,0x28,0xD0 )                                    /* movaps      xmm2,xmm0  */ \
_LINE3( 0x0F,0x28,0xD9 )                                    /* movaps      xmm3,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC0,0x32 )                               /* shufps      xmm0,xmm0,32h  */ \
_LINE4( 0x0F,0xC6,0xC9,0x83 )                               /* shufps      xmm1,xmm1,83h  */ \
_LINE4( 0x0F,0xC6,0xD2,0x83 )                               /* shufps      xmm2,xmm2,83h  */ \
_LINE4( 0x0F,0xC6,0xDB,0x32 )                               /* shufps      xmm3,xmm3,32h  */ \
_LINE3( 0x0F,0x59,0xC1 )                                    /* mulps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x59,0xD3 )                                    /* mulps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x5C,0xC2 )                                    /* subps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x17,0x01 )                                    /* movhps      qword ptr [ecx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x41,0x08 )                          /* movss       dword ptr [ecx+8],xmm0  */ \
_END_ASM

/// ¬екторное умножение трехмерных векторов двойной точности, команды FPU
#define VECTORP3DDCROSSPRODUCTFPU \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0xDD,0x42,0x10 )                                    /* fld         qword ptr [edx+10h]  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE3( 0xDD,0x42,0x08 )                                    /* fld         qword ptr [edx+8]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE2( 0xDD,0x02 )                                         /* fld         qword ptr [edx]  */ \
_LINE3( 0xDD,0x40,0x10 )                                    /* fld         qword ptr [eax+10h]  */ \
_LINE3( 0xDD,0x40,0x08 )                                    /* fld         qword ptr [eax+8]  */ \
_LINE2( 0xDD,0x00 )                                         /* fld         qword ptr [eax]  */ \
_LINE2( 0xD9,0xC1 )                                         /* fld         st(1)  */ \
_LINE2( 0xD8,0xCE )                                         /* fmul        st,st(6)  */ \
_LINE2( 0xD9,0xC3 )                                         /* fld         st(3)  */ \
_LINE2( 0xD8,0xCE )                                         /* fmul        st,st(6)  */ \
_LINE2( 0xDE,0xE9 )                                         /* fsubp       st(1),st  */ \
_LINE2( 0xDD,0x19 )                                         /* fstp        qword ptr [ecx]  */ \
_LINE2( 0xD9,0xC2 )                                         /* fld         st(2)  */ \
_LINE2( 0xD8,0xCC )                                         /* fmul        st,st(4)  */ \
_LINE2( 0xD9,0xC1 )                                         /* fld         st(1)  */ \
_LINE2( 0xD8,0xCF )                                         /* fmul        st,st(7)  */ \
_LINE2( 0xDE,0xE9 )                                         /* fsubp       st(1),st  */ \
_LINE3( 0xDD,0x59,0x08 )                                    /* fstp        qword ptr [ecx+8]  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xD9,0xC2 )                                         /* fld         st(2)  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xDE,0xE9 )                                         /* fsubp       st(1),st  */ \
_LINE3( 0xDD,0x59,0x10 )                                    /* fstp        qword ptr [ecx+10h]  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

/// ¬екторное умножение трехмерных векторов одинарной точности, команды SSE2
#define VECTORP3DDCROSSPRODUCTSSE2 \
BEGIN_ASM \
END_ASM

//**************************** CROSS PRODUCT CPP FASTCALL *********************************
// vector cross product ecx-a void * edx-b void * eax-b void *

/// ¬екторное умножение трехмерных векторов одинарной точности, команды FPU
#define VECTORP3DCROSSPRODUCTFPU_CPP \
_BEGIN_ASM \
_LINE3( 0xD9,0x42,0x08 )                                    /* fld         dword ptr [edx+8]  */ \
_LINE3( 0xD9,0x42,0x04 )                                    /* fld         dword ptr [edx+4]  */ \
_LINE2( 0xD9,0x02 )                                         /* fld         dword ptr [edx]  */ \
_LINE3( 0xD9,0x41,0x08 )                                    /* fld         dword ptr [ecx+8]  */ \
_LINE3( 0xD9,0x41,0x04 )                                    /* fld         dword ptr [ecx+4]  */ \
_LINE2( 0xD9,0x01 )                                         /* fld         dword ptr [ecx]  */ \
_LINE2( 0xD9,0xC1 )                                         /* fld         st(1)  */ \
_LINE2( 0xD8,0xCE )                                         /* fmul        st,st(6)  */ \
_LINE2( 0xD9,0xC3 )                                         /* fld         st(3)  */ \
_LINE2( 0xD8,0xCE )                                         /* fmul        st,st(6)  */ \
_LINE2( 0xDE,0xE9 )                                         /* fsubp       st(1),st  */ \
_LINE2( 0xD9,0x18 )                                         /* fstp        dword ptr [eax]  */ \
_LINE2( 0xD9,0xC2 )                                         /* fld         st(2)  */ \
_LINE2( 0xD8,0xCC )                                         /* fmul        st,st(4)  */ \
_LINE2( 0xD9,0xC1 )                                         /* fld         st(1)  */ \
_LINE2( 0xD8,0xCF )                                         /* fmul        st,st(7)  */ \
_LINE2( 0xDE,0xE9 )                                         /* fsubp       st(1),st  */ \
_LINE3( 0xD9,0x58,0x04 )                                    /* fstp        dword ptr [eax+4]  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xD9,0xC2 )                                         /* fld         st(2)  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xDE,0xE9 )                                         /* fsubp       st(1),st  */ \
_LINE3( 0xD9,0x58,0x08 )                                    /* fstp        dword ptr [eax+8]  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

/// ¬екторное умножение трехмерных векторов одинарной точности, команды SSE
#define VECTORP3DCROSSPRODUCTSSE_CPP \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x41,0x08 )                          /* movss       xmm0,dword ptr [ecx+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE3( 0x0F,0x16,0x01 )                                    /* movhps      xmm0,qword ptr [ecx]  */ \
_LINE3( 0x0F,0x16,0x0A )                                    /* movhps      xmm1,qword ptr [edx]  */ \
_LINE3( 0x0F,0x28,0xD0 )                                    /* movaps      xmm2,xmm0  */ \
_LINE3( 0x0F,0x28,0xD9 )                                    /* movaps      xmm3,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC0,0x32 )                               /* shufps      xmm0,xmm0,32h  */ \
_LINE4( 0x0F,0xC6,0xC9,0x83 )                               /* shufps      xmm1,xmm1,83h  */ \
_LINE4( 0x0F,0xC6,0xD2,0x83 )                               /* shufps      xmm2,xmm2,83h  */ \
_LINE4( 0x0F,0xC6,0xDB,0x32 )                               /* shufps      xmm3,xmm3,32h  */ \
_LINE3( 0x0F,0x59,0xC1 )                                    /* mulps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x59,0xD3 )                                    /* mulps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x5C,0xC2 )                                    /* subps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x17,0x00 )                                    /* movhps      qword ptr [eax],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x40,0x08 )                          /* movss       dword ptr [eax+8],xmm0  */ \
_END_ASM

/// ¬екторное умножение трехмерных векторов двойной точности, команды FPU
#define VECTORP3DDCROSSPRODUCTFPU_CPP \
_BEGIN_ASM \
_LINE3( 0xDD,0x42,0x10 )                                    /* fld         qword ptr [edx+10h]  */ \
_LINE3( 0xDD,0x42,0x08 )                                    /* fld         qword ptr [edx+8]  */ \
_LINE2( 0xDD,0x02 )                                         /* fld         qword ptr [edx]  */ \
_LINE3( 0xDD,0x41,0x10 )                                    /* fld         qword ptr [ecx+10h]  */ \
_LINE3( 0xDD,0x41,0x08 )                                    /* fld         qword ptr [ecx+8]  */ \
_LINE2( 0xDD,0x01 )                                         /* fld         qword ptr [ecx]  */ \
_LINE2( 0xD9,0xC1 )                                         /* fld         st(1)  */ \
_LINE2( 0xD8,0xCE )                                         /* fmul        st,st(6)  */ \
_LINE2( 0xD9,0xC3 )                                         /* fld         st(3)  */ \
_LINE2( 0xD8,0xCE )                                         /* fmul        st,st(6)  */ \
_LINE2( 0xDE,0xE9 )                                         /* fsubp       st(1),st  */ \
_LINE2( 0xDD,0x18 )                                         /* fstp        qword ptr [eax]  */ \
_LINE2( 0xD9,0xC2 )                                         /* fld         st(2)  */ \
_LINE2( 0xD8,0xCC )                                         /* fmul        st,st(4)  */ \
_LINE2( 0xD9,0xC1 )                                         /* fld         st(1)  */ \
_LINE2( 0xD8,0xCF )                                         /* fmul        st,st(7)  */ \
_LINE2( 0xDE,0xE9 )                                         /* fsubp       st(1),st  */ \
_LINE3( 0xDD,0x58,0x08 )                                    /* fstp        qword ptr [eax+8]  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xD9,0xC2 )                                         /* fld         st(2)  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xDE,0xE9 )                                         /* fsubp       st(1),st  */ \
_LINE3( 0xDD,0x58,0x10 )                                    /* fstp        qword ptr [eax+10h]  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0) */ \
_END_ASM

/// ¬екторное умножение трехмерных векторов двойной точности, команды SSE2
#define VECTORP3DDCROSSPRODUCTSSE2_CPP \
BEGIN_ASM \
END_ASM

#endif
