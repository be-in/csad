//=============================================================================
///**
// *  @file quaternion_transform.h
// *
// *  $Id: quaternion_transform.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float transform, MS Visual C++ 2003-2008
// *
// *  @author Pant_eleymonov Alek_sandr Kons_tantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_QUATERNION_TRANSFORM_H
#define GEN3_QUATERNION_TRANSFORM_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** TRANSFORM STDCALL *********************************
// transform vectors eax=[esp+4]-a void *, [esp+8]-b void *  [esp+12]-c void *

/// Умножение трехмерного вектора на кватернион трансформации одинарной точности, команды FPU
#define QUATERNIONP3DTRANSFORMFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B, 0x54, 0x24, 0x04 )        /* mov         edx,dword ptr [esp+4]  */ \
_LINE2( 0xD9, 0x02 )                    /* fld         dword ptr [edx]  */ \
_LINE3( 0xD9, 0x42, 0x08 )              /* fld         dword ptr [edx+8]  */ \
_LINE3( 0xD9, 0x42, 0x04 )              /* fld         dword ptr [edx+4]  */ \
_LINE3( 0xD9, 0x42, 0x0C )              /* fld         dword ptr [edx+0Ch]  */ \
_LINE4( 0x8B, 0x44, 0x24, 0x08 )        /* mov         eax,dword ptr [esp+8]  */ \
_LINE3( 0xD9, 0x40, 0x08 )              /* fld         dword ptr [eax+8]  */ \
_LINE2( 0xD8, 0xCA )                    /* fmul        st,st(2)  */ \
_LINE3( 0xD9, 0x40, 0x04 )              /* fld         dword ptr [eax+4]  */ \
_LINE2( 0xD8, 0xCC )                    /* fmul        st,st(4)  */ \
_LINE2( 0xDE, 0xE9 )                    /* fsubp       st(1),st  */ \
_LINE2( 0xD9, 0x00 )                    /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8, 0xCA )                    /* fmul        st,st(2)  */ \
_LINE2( 0xDE, 0xC1 )                    /* faddp       st(1),st  */ \
_LINE2( 0xD9, 0x00 )                    /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8, 0xCC )                    /* fmul        st,st(4)  */ \
_LINE3( 0xD9, 0x40, 0x04 )              /* fld         dword ptr [eax+4]  */ \
_LINE2( 0xD8, 0xCB )                    /* fmul        st,st(3)  */ \
_LINE2( 0xDE, 0xC1 )                    /* faddp       st(1),st  */ \
_LINE3( 0xD9, 0x40, 0x08 )              /* fld         dword ptr [eax+8]  */ \
_LINE2( 0xD8, 0xCE )                    /* fmul        st,st(6)  */ \
_LINE2( 0xDE, 0xE9 )                    /* fsubp       st(1),st  */ \
_LINE3( 0xD9, 0x40, 0x04 )              /* fld         dword ptr [eax+4]  */ \
_LINE2( 0xD8, 0xCE )                    /* fmul        st,st(6)  */ \
_LINE2( 0xD9, 0x00 )                    /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8, 0xCD )                    /* fmul        st,st(5)  */ \
_LINE2( 0xDE, 0xE9 )                    /* fsubp       st(1),st  */ \
_LINE3( 0xD9, 0x40, 0x08 )              /* fld         dword ptr [eax+8]  */ \
_LINE2( 0xDE, 0xCC )                    /* fmulp       st(4),st  */ \
_LINE2( 0xDE, 0xC3 )                    /* faddp       st(3),st  */ \
_LINE2( 0xD9, 0x00 )                    /* fld         dword ptr [eax]  */ \
_LINE2( 0xDE, 0xCE )                    /* fmulp       st(6),st  */ \
_LINE3( 0xD9, 0x40, 0x04 )              /* fld         dword ptr [eax+4]  */ \
_LINE2( 0xDE, 0xCC )                    /* fmulp       st(4),st  */ \
_LINE3( 0xD9, 0x40, 0x08 )              /* fld         dword ptr [eax+8]  */ \
_LINE2( 0xD8, 0xCD )                    /* fmul        st,st(5)  */ \
_LINE2( 0xD8, 0xC6 )                    /* fadd        st,st(6)  */ \
_LINE2( 0xDE, 0xC4 )                    /* faddp       st(4),st  */ \
_LINE2( 0xDD, 0xDD )                    /* fstp        st(5)  */ \
_LINE2( 0xDD, 0xDB )                    /* fstp        st(3)  */ \
_LINE4( 0x8B, 0x44, 0x24, 0x0C )        /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE3( 0xD9, 0x42, 0x0C )              /* fld         dword ptr [edx+0Ch]  */ \
_LINE2( 0xD8, 0xCB )                    /* fmul        st,st(3)  */ \
_LINE3( 0xD9, 0x42, 0x04 )              /* fld         dword ptr [edx+4]  */ \
_LINE2( 0xD8, 0xCA )                    /* fmul        st,st(2)  */ \
_LINE2( 0xDE, 0xC1 )                    /* faddp       st(1),st  */ \
_LINE3( 0xD9, 0x42, 0x08 )              /* fld         dword ptr [edx+8]  */ \
_LINE2( 0xD8, 0xCD )                    /* fmul        st,st(5)  */ \
_LINE2( 0xDE, 0xE9 )                    /* fsubp       st(1),st  */ \
_LINE2( 0xD9, 0x02 )                    /* fld         dword ptr [edx]  */ \
_LINE2( 0xD8, 0xCB )                    /* fmul        st,st(3)  */ \
_LINE2( 0xDE, 0xC1 )                    /* faddp       st(1),st  */ \
_LINE2( 0xD9, 0x18 )                    /* fstp        dword ptr [eax]  */ \
_LINE3( 0xD9, 0x42, 0x08 )              /* fld         dword ptr [edx+8]  */ \
_LINE2( 0xD8, 0xCB )                    /* fmul        st,st(3)  */ \
_LINE3( 0xD9, 0x42, 0x0C )              /* fld         dword ptr [edx+0Ch]  */ \
_LINE2( 0xD8, 0xCD )                    /* fmul        st,st(5)  */ \
_LINE2( 0xDE, 0xC1 )                    /* faddp       st(1),st  */ \
_LINE2( 0xD9, 0x02 )                    /* fld         dword ptr [edx]  */ \
_LINE2( 0xD8, 0xCA )                    /* fmul        st,st(2)  */ \
_LINE2( 0xDE, 0xE9 )                    /* fsubp       st(1),st  */ \
_LINE3( 0xD9, 0x42, 0x04 )              /* fld         dword ptr [edx+4]  */ \
_LINE2( 0xD8, 0xCB )                    /* fmul        st,st(3)  */ \
_LINE2( 0xDE, 0xC1 )                    /* faddp       st(1),st  */ \
_LINE3( 0xD9, 0x58, 0x04 )              /* fstp        dword ptr [eax+4]  */ \
_LINE2( 0xD9, 0x02 )                    /* fld         dword ptr [edx]  */ \
_LINE2( 0xDE, 0xCC )                    /* fmulp       st(4),st  */ \
_LINE3( 0xD9, 0x42, 0x0C )              /* fld         dword ptr [edx+0Ch]  */ \
_LINE2( 0xDE, 0xC9 )                    /* fmulp       st(1),st  */ \
_LINE2( 0xDE, 0xC3 )                    /* faddp       st(3),st  */ \
_LINE3( 0xD9, 0x42, 0x04 )              /* fld         dword ptr [edx+4]  */ \
_LINE2( 0xDE, 0xCA )                    /* fmulp       st(2),st  */ \
_LINE3( 0xD9, 0x42, 0x08 )              /* fld         dword ptr [edx+8]  */ \
_LINE2( 0xDE, 0xC9 )                    /* fmulp       st(1),st  */ \
_LINE2( 0xDE, 0xE9 )                    /* fsubp       st(1),st  */ \
_LINE2( 0xDE, 0xE9 )                    /* fsubp       st(1),st  */ \
_LINE3( 0xD9, 0x58, 0x08 )              /* fstp        dword ptr [eax+8]  */ \
_END_ASM

/// Умножение трехмерного вектора на кватернион трансформации одинарной точности, команды SSE
#define QUATERNIONP3DTRANSFORMSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )              /* mov         eax,dword ptr [esp+4]  */ \
_LINE3( 0x0F,0x12,0x08 )                   /* movlps      xmm1,qword ptr [eax]  */ \
_LINE4( 0x0F,0x16,0x48,0x08 )              /* movhps      xmm1,qword ptr [eax+8]  */ \
_LINE3( 0x0F,0x57,0xE4 )                   /* xorps       xmm4,xmm4  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )              /* mov         eax,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x12,0xD1 )                   /* movhlps     xmm2,xmm1  */ \
_LINE4( 0xF3,0x0F,0x10,0x00 )              /* movss       xmm0,dword ptr [eax]  */ \
_LINE5( 0xF3,0x0F,0x10,0x68,0x04 )         /* movss       xmm5,dword ptr [eax+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x70,0x08 )         /* movss       xmm6,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x5C,0xE1 )                   /* subps       xmm4,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )              /* shufps      xmm0,xmm0,0  */ \
_LINE4( 0x0F,0xC6,0xED,0x00 )              /* shufps      xmm5,xmm5,0  */ \
_LINE4( 0x0F,0xC6,0xF6,0x00 )              /* shufps      xmm6,xmm6,0  */ \
_LINE3( 0x0F,0x28,0xD9 )                   /* movaps      xmm3,xmm1  */ \
_LINE4( 0x0F,0xC6,0xD4,0x11 )              /* shufps      xmm2,xmm4,11h */ \
_LINE4( 0x0F,0xC6,0xDC,0x9C )              /* shufps      xmm3,xmm4,9Ch  */ \
_LINE4( 0x0F,0xC6,0xDB,0x87 )              /* shufps      xmm3,xmm3,87h */ \
_LINE4( 0x0F,0xC6,0xCC,0x8D )              /* shufps      xmm1,xmm4,8Dh  */ \
_LINE4( 0x0F,0xC6,0xC9,0xD8 )              /* shufps      xmm1,xmm1,D8h */ \
_LINE3( 0x0F,0x59,0xC2 )                   /* mulps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x59,0xEB )                   /* mulps       xmm5,xmm3  */ \
_LINE3( 0x0F,0x59,0xF1 )                   /* mulps       xmm6,xmm1  */ \
_LINE3( 0x0F,0x58,0xC5 )                   /* addps       xmm0,xmm5  */ \
_LINE3( 0x0F,0x58,0xC6 )                   /* addps       xmm0,xmm6  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )              /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE3( 0x0F,0x28,0xF8 )                   /* movaps      xmm7,xmm0  */ \
_LINE4( 0x0F,0xC6,0xFF,0x00 )              /* shufps      xmm7,xmm7,0  */ \
_LINE3( 0x0F,0x28,0xE8 )                   /* movaps      xmm5,xmm0  */ \
_LINE4( 0x0F,0xC6,0xED,0x55 )              /* shufps      xmm5,xmm5,55h  */ \
_LINE3( 0x0F,0x28,0xF0 )                   /* movaps      xmm6,xmm0  */ \
_LINE4( 0x0F,0xC6,0xF6,0xAA )              /* shufps      xmm6,xmm6,AAh  */ \
_LINE4( 0x0F,0xC6,0xC0,0xFF )              /* shufps      xmm0,xmm0,FFh  */ \
_LINE3( 0x0F,0x59,0xFA )                   /* mulps       xmm7,xmm2  */ \
_LINE3( 0x0F,0x59,0xEB )                   /* mulps       xmm5,xmm3  */ \
_LINE3( 0x0F,0x59,0xF1 )                   /* mulps       xmm6,xmm1  */ \
_LINE3( 0x0F,0x59,0xC4 )                   /* mulps       xmm0,xmm4  */ \
_LINE3( 0x0F,0x58,0xFD )                   /* addps       xmm7,xmm5  */ \
_LINE3( 0x0F,0x58,0xC6 )                   /* addps       xmm0,xmm6  */ \
_LINE3( 0x0F,0x58,0xC7 )                   /* addps       xmm0,xmm7  */ \
_LINE3( 0x0F,0x13,0x00 )                   /* movlps      qword ptr [eax],xmm0  */ \
_LINE3( 0x0F,0x12,0xD8 )                   /* movhlps     xmm3,xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x58,0x08 )         /* movss       dword ptr [eax+8],xmm3  */ \
_END_ASM

/// Умножение трехмерного вектора на кватернион трансформации одинарной точности, команды SSE3
#define QUATERNIONP3DTRANSFORMSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )              /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x08 )              /* lddqu       xmm1,xmmword ptr [eax]  */ \
_LINE3( 0x0F,0x57,0xE4 )                   /* xorps       xmm4,xmm4  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )              /* mov         eax,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x12,0xD1 )                   /* movhlps     xmm2,xmm1  */ \
_LINE4( 0xF3,0x0F,0x10,0x00 )              /* movss       xmm0,dword ptr [eax]  */ \
_LINE5( 0xF3,0x0F,0x10,0x68,0x04 )         /* movss       xmm5,dword ptr [eax+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x70,0x08 )         /* movss       xmm6,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x5C,0xE1 )                   /* subps       xmm4,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )              /* shufps      xmm0,xmm0,0  */ \
_LINE4( 0x0F,0xC6,0xED,0x00 )              /* shufps      xmm5,xmm5,0  */ \
_LINE4( 0x0F,0xC6,0xF6,0x00 )              /* shufps      xmm6,xmm6,0  */ \
_LINE3( 0x0F,0x28,0xD9 )                   /* movaps      xmm3,xmm1  */ \
_LINE4( 0x0F,0xC6,0xD4,0x11 )              /* shufps      xmm2,xmm4,11h */ \
_LINE4( 0x0F,0xC6,0xDC,0x9C )              /* shufps      xmm3,xmm4,9Ch  */ \
_LINE4( 0x0F,0xC6,0xDB,0x87 )              /* shufps      xmm3,xmm3,87h */ \
_LINE4( 0x0F,0xC6,0xCC,0x8D )              /* shufps      xmm1,xmm4,8Dh  */ \
_LINE4( 0x0F,0xC6,0xC9,0xD8 )              /* shufps      xmm1,xmm1,D8h */ \
_LINE3( 0x0F,0x59,0xC2 )                   /* mulps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x59,0xEB )                   /* mulps       xmm5,xmm3  */ \
_LINE3( 0x0F,0x59,0xF1 )                   /* mulps       xmm6,xmm1  */ \
_LINE3( 0x0F,0x58,0xC5 )                   /* addps       xmm0,xmm5  */ \
_LINE3( 0x0F,0x58,0xC6 )                   /* addps       xmm0,xmm6  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )              /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE3( 0x0F,0x28,0xF8 )                   /* movaps      xmm7,xmm0  */ \
_LINE4( 0x0F,0xC6,0xFF,0x00 )              /* shufps      xmm7,xmm7,0  */ \
_LINE3( 0x0F,0x28,0xE8 )                   /* movaps      xmm5,xmm0  */ \
_LINE4( 0x0F,0xC6,0xED,0x55 )              /* shufps      xmm5,xmm5,55h  */ \
_LINE3( 0x0F,0x28,0xF0 )                   /* movaps      xmm6,xmm0  */ \
_LINE4( 0x0F,0xC6,0xF6,0xAA )              /* shufps      xmm6,xmm6,AAh  */ \
_LINE4( 0x0F,0xC6,0xC0,0xFF )              /* shufps      xmm0,xmm0,FFh  */ \
_LINE3( 0x0F,0x59,0xFA )                   /* mulps       xmm7,xmm2  */ \
_LINE3( 0x0F,0x59,0xEB )                   /* mulps       xmm5,xmm3  */ \
_LINE3( 0x0F,0x59,0xF1 )                   /* mulps       xmm6,xmm1  */ \
_LINE3( 0x0F,0x59,0xC4 )                   /* mulps       xmm0,xmm4  */ \
_LINE3( 0x0F,0x58,0xFD )                   /* addps       xmm7,xmm5  */ \
_LINE3( 0x0F,0x58,0xC6 )                   /* addps       xmm0,xmm6  */ \
_LINE3( 0x0F,0x58,0xC7 )                   /* addps       xmm0,xmm7  */ \
_LINE3( 0x0F,0x13,0x00 )                   /* movlps      qword ptr [eax],xmm0  */ \
_LINE3( 0x0F,0x12,0xD8 )                   /* movhlps     xmm3,xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x58,0x08 )         /* movss       dword ptr [eax+8],xmm3  */ \
_END_ASM

/// Умножение трехмерного вектора на кватернион трансформации одинарной точности, команды SSE4
#define QUATERNIONP3DTRANSFORMSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )              /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x08 )              /* lddqu       xmm1,xmmword ptr [eax]  */ \
_LINE3( 0x0F,0x57,0xE4 )                   /* xorps       xmm4,xmm4  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )              /* mov         eax,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x12,0xD1 )                   /* movhlps     xmm2,xmm1  */ \
_LINE4( 0xF3,0x0F,0x10,0x00 )              /* movss       xmm0,dword ptr [eax]  */ \
_LINE5( 0xF3,0x0F,0x10,0x68,0x04 )         /* movss       xmm5,dword ptr [eax+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x70,0x08 )         /* movss       xmm6,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x5C,0xE1 )                   /* subps       xmm4,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )              /* shufps      xmm0,xmm0,0  */ \
_LINE4( 0x0F,0xC6,0xED,0x00 )              /* shufps      xmm5,xmm5,0  */ \
_LINE4( 0x0F,0xC6,0xF6,0x00 )              /* shufps      xmm6,xmm6,0  */ \
_LINE3( 0x0F,0x28,0xD9 )                   /* movaps      xmm3,xmm1  */ \
_LINE4( 0x0F,0xC6,0xD4,0x11 )              /* shufps      xmm2,xmm4,11h */ \
_LINE4( 0x0F,0xC6,0xDC,0x9C )              /* shufps      xmm3,xmm4,9Ch  */ \
_LINE4( 0x0F,0xC6,0xDB,0x87 )              /* shufps      xmm3,xmm3,87h */ \
_LINE4( 0x0F,0xC6,0xCC,0x8D )              /* shufps      xmm1,xmm4,8Dh  */ \
_LINE4( 0x0F,0xC6,0xC9,0xD8 )              /* shufps      xmm1,xmm1,D8h */ \
_LINE3( 0x0F,0x59,0xC2 )                   /* mulps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x59,0xEB )                   /* mulps       xmm5,xmm3  */ \
_LINE3( 0x0F,0x59,0xF1 )                   /* mulps       xmm6,xmm1  */ \
_LINE3( 0x0F,0x58,0xC5 )                   /* addps       xmm0,xmm5  */ \
_LINE3( 0x0F,0x58,0xC6 )                   /* addps       xmm0,xmm6  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )              /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE3( 0x0F,0x28,0xF8 )                   /* movaps      xmm7,xmm0  */ \
_LINE4( 0x0F,0xC6,0xFF,0x00 )              /* shufps      xmm7,xmm7,0  */ \
_LINE3( 0x0F,0x28,0xE8 )                   /* movaps      xmm5,xmm0  */ \
_LINE4( 0x0F,0xC6,0xED,0x55 )              /* shufps      xmm5,xmm5,55h  */ \
_LINE3( 0x0F,0x28,0xF0 )                   /* movaps      xmm6,xmm0  */ \
_LINE4( 0x0F,0xC6,0xF6,0xAA )              /* shufps      xmm6,xmm6,AAh  */ \
_LINE4( 0x0F,0xC6,0xC0,0xFF )              /* shufps      xmm0,xmm0,FFh  */ \
_LINE3( 0x0F,0x59,0xFA )                   /* mulps       xmm7,xmm2  */ \
_LINE3( 0x0F,0x59,0xEB )                   /* mulps       xmm5,xmm3  */ \
_LINE3( 0x0F,0x59,0xF1 )                   /* mulps       xmm6,xmm1  */ \
_LINE3( 0x0F,0x59,0xC4 )                   /* mulps       xmm0,xmm4  */ \
_LINE3( 0x0F,0x58,0xFD )                   /* addps       xmm7,xmm5  */ \
_LINE3( 0x0F,0x58,0xC6 )                   /* addps       xmm0,xmm6  */ \
_LINE3( 0x0F,0x58,0xC7 )                   /* addps       xmm0,xmm7  */ \
_LINE3( 0x0F,0x13,0x00 )                   /* movlps      qword ptr [eax],xmm0  */ \
_LINE3( 0x0F,0x12,0xD8 )                   /* movhlps     xmm3,xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x58,0x08 )         /* movss       dword ptr [eax+8],xmm3  */ \
_END_ASM

/// Умножение трехмерного вектора на кватернион трансформации одинарной точности, команды SSE4
#define QUATERNIONP3DTRANSFORMSSE4_STD1 \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )              /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x08 )              /* lddqu       xmm1,xmmword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x4E )              /* shufps      xmm1,xmm1,4Eh  */ \
_LINE3( 0x0F,0x57,0xE4 )                   /* xorps       xmm4,xmm4  */ \
_LINE3( 0x0F,0x5C,0xE1 )                   /* subps       xmm4,xmm1  */ \
_LINE3( 0x0F,0x16,0xD1 )                   /* movlhps     xmm2,xmm1  */ \
_LINE3( 0x0F,0x12,0xD4 )                   /* movhlps     xmm2,xmm4  */ \
_LINE3( 0x0F,0x28,0xD9 )                   /* movaps      xmm3,xmm1  */ \
_LINE4( 0x0F,0xC6,0xDC,0xC9 )              /* shufps      xmm3,xmm4,0C9h  */ \
_LINE4( 0x0F,0xC6,0xDB,0x78 )              /* shufps      xmm3,xmm3,78h  */ \
_LINE4( 0x0F,0xC6,0xCC,0x8D )              /* shufps      xmm1,xmm4,8Dh  */ \
_LINE4( 0x0F,0xC6,0xC9,0x8D )              /* shufps      xmm1,xmm1,8Dh  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )              /* mov         eax,dword ptr [esp+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )         /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x00 )                   /* movhps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xE8 )                   /* movaps      xmm5,xmm0  */ \
_LINE3( 0x0F,0x28,0xF0 )                   /* movaps      xmm6,xmm0  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xE0,0xD2 )    /* dpps        xmm4,xmm0,0D2h  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC1,0xD4 )    /* dpps        xmm0,xmm1,0D4h  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xEA,0xD8 )    /* dpps        xmm5,xmm2,0D8h  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xF3,0xD1 )    /* dpps        xmm6,xmm3,0D1h  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )              /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE3( 0x0F,0x56,0xE0 )                   /* orps        xmm4,xmm0  */ \
_LINE3( 0x0F,0x56,0xF5 )                   /* orps        xmm6,xmm5  */ \
_LINE3( 0x0F,0x56,0xE6 )                   /* orps        xmm4,xmm6  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xCC,0xF1 )    /* dpps        xmm1,xmm4,0F1h  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xD4,0xF2 )    /* dpps        xmm2,xmm4,0F2h  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xDC,0xF1 )    /* dpps        xmm3,xmm4,0F1h  */ \
_LINE3( 0x0F,0x56,0xD1 )                   /* orps        xmm2,xmm1  */ \
_LINE3( 0x0F,0x13,0x10 )                   /* movlps      qword ptr [eax],xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x58,0x08 )         /* movss       dword ptr [eax+8],xmm3  */ \
_END_ASM

/// Умножение трехмерного вектора на кватернион трансформации двойной точности, команды FPU
#define QUATERNIONP3DDTRANSFORMFPU_STD \
_BEGIN_ASM \
ASM( mov edx,[esp+4] ) \
ASM( fld qword ptr [edx] ) \
ASM( fld qword ptr [edx+16] ) \
ASM( fld qword ptr [edx+8] ) \
ASM( fld qword ptr [edx+24] ) /* a3 a1 a2 a0 */ \
ASM( mov eax,[esp+8] ) \
ASM( fld qword ptr [eax+16] ) /* b2 a3 a1 a2 a0 */ \
ASM( fmul st(0),st(2) ) \
ASM( fld qword ptr [eax+8] ) /* b1 b2*a1 a3 a1 a2 a0 */ \
ASM( fmul st(0),st(4) ) \
ASM( fsubp st(1),st(0) ) \
ASM( fld qword ptr [eax] ) /* b0 b2*a1-b1*a2 a3 a1 a2 a0 */ \
ASM( fmul st(0),st(2) ) \
ASM( faddp st(1),st(0) ) \
ASM( fld qword ptr [eax] ) /* b0 m0 a3 a1 a2 a0 */ \
ASM( fmul st(0),st(4) ) \
ASM( fld qword ptr [eax+8] ) /* b1 b0*a2 m0 a3 a1 a2 a0 */ \
ASM( fmul st(0),st(3) ) \
ASM( faddp st(1),st(0) ) \
ASM( fld qword ptr [eax+16] ) /* b2 b0*a2+b1*a3 m0 a3 a1 a2 a0 */ \
ASM( fmul st(0),st(6) ) \
ASM( fsubp st(1),st(0) ) \
ASM( fld qword ptr [eax+8] ) /* b1 m1 m0 a3 a1 a2 a0 */ \
ASM( fmul st(0),st(6) ) \
ASM( fld qword ptr [eax] ) /* b0 b1*a0 m1 m0 a3 a1 a2 a0 */ \
ASM( fmul st(0),st(5) ) \
ASM( fsubp st(1),st(0) ) \
ASM( fld qword ptr [eax+16] ) /* b2 b1*a0-b0*a1 m1 m0 a3 a1 a2 a0 */ \
ASM( fmulp st(4),st(0) ) /* b1*a0-b0*a1 m1 m0 b2*a3 a1 a2 a0 */ \
ASM( faddp st(3),st(0) ) /* m1 m0 m2 a1 a2 a0 */ \
ASM( fld qword ptr [eax] ) /* b0 m1 m0 m2 a1 a2 a0 */ \
ASM( fmulp st(6),st(0) ) /* m1 m0 m2 a1 a2 b0*a0 */ \
ASM( fld qword ptr [eax+8] ) /* b1 m1 m0 m2 a1 a2 b0*a0 */ \
ASM( fmulp st(4),st(0) ) /* m1 m0 m2 b1*a1 a2 b0*a0 */ \
ASM( fld qword ptr [eax+16] ) /* b2 m1 m0 m2 b1*a1 a2 b0*a0 */ \
ASM( fmul st(0),st(5) ) /* a2*b2 m1 m0 m2 b1*a1 a2 b0*a0 */ \
ASM( fadd st(0),st(6) ) /* a2*b2+b0*a0 m1 m0 m2 b1*a1 a2 b0*a0 */ \
ASM( faddp st(4),st(0) ) /* m1 m0 m2 -m3 a2 b0*a0 */ \
ASM( fstp st(5) ) /* m0 m2 -m3 a2 m1 */ \
ASM( fstp st(3) ) /* m2 -m3 m0 m1 */ \
ASM( mov eax,[esp+12] ) \
ASM( fld qword ptr [edx+24] ) /* a0 m2 -m3 m0 m1 */ \
ASM( fmul st(0),st(3) ) /* a0*m0 m2 -m3 m0 m1 */ \
ASM( fld qword ptr [edx+8] ) /* r1 r0 m2 -m3 m0 m1 */ \
ASM( fmul st(0),st(2) ) \
ASM( faddp st(1),st(0) ) \
ASM( fld qword ptr [edx+16] ) /* r2 r0 m2 -m3 m0 m1 */ \
ASM( fmul st(0),st(5) ) \
ASM( fsubp st(1),st(0) ) \
ASM( fld qword ptr [edx] ) /* r3 r0 m2 -m3 m0 m1 */ \
ASM( fmul st(0),st(3) ) \
ASM( faddp st(1),st(0) ) \
ASM( fstp qword ptr [eax] ) \
ASM( fld qword ptr [edx+16] ) /* r0 m2 -m3 m0 m1 */ \
ASM( fmul st(0),st(3) ) \
ASM( fld qword ptr [edx+24] ) /* r1 r0 m2 -m3 m0 m1 */ \
ASM( fmul st(0),st(5) ) \
ASM( faddp st(1),st(0) ) \
ASM( fld qword ptr [edx] ) /* r2 r0 m2 -m3 m0 m1 */ \
ASM( fmul st(0),st(2) ) \
ASM( fsubp st(1),st(0) ) \
ASM( fld qword ptr [edx+8] ) /* r3 r0 m2 -m3 m0 m1 */ \
ASM( fmul st(0),st(3) ) \
ASM( faddp st(1),st(0) ) \
ASM( fstp qword ptr [eax+8] ) \
ASM( fld qword ptr [edx] ) /* r0 m2 -m3 m0 m1 */ \
ASM( fmulp st(4),st(0) ) \
ASM( fld qword ptr [edx+24] ) /* r1 m2 -m3 m0 r0 */ \
ASM( fmulp st(1),st(0) ) /* r1 -m3 m0 r0 */ \
ASM( faddp st(3),st(0) ) /* -m3 m0 r0 */ \
ASM( fld qword ptr [edx+8] ) /* r2 -m3 m0 r0 */ \
ASM( fmulp st(2),st(0) ) /* -m3 r2 r0 */ \
ASM( fld qword ptr [edx+16] ) /* r3 -m3 r2 r0 */ \
ASM( fmulp st(1),st(0) ) /* a2*-m3 a1*m0 a0*m1+a3*m2 */ \
ASM( fsubp st(1),st(0) ) \
ASM( fsubp st(1),st(0) ) \
ASM( fstp qword ptr [eax+16] ) \
_END_ASM

/// Умножение трехмерного вектора на кватернион трансформации двойной точности, команды SSE2
#define QUATERNIONP3DDTRANSFORMSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                 /* mov         eax,dword ptr [esp+4]  */ \
_LINE3( 0x0F,0x16,0x10 )                      /* movhps      xmm2,qword ptr [eax]  */ \
_LINE4( 0x0F,0x12,0x58,0x10 )                 /* movlps      xmm3,qword ptr [eax+10h]  */ \
_LINE4( 0x0F,0x12,0x50,0x08 )                 /* movlps      xmm2,qword ptr [eax+8]  */ \
_LINE4( 0x0F,0x16,0x58,0x18 )                 /* movhps      xmm3,qword ptr [eax+18h]  */ \
_LINE3( 0x0F,0x12,0xE2 )                      /* movhlps     xmm4,xmm2  */ \
_LINE3( 0x0F,0x57,0xC9 )                      /* xorps       xmm1,xmm1  */ \
_LINE3( 0x0F,0x16,0xE3 )                      /* movlhps     xmm4,xmm3  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                 /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0x66,0x0F,0x5C,0xCC )                 /* subpd       xmm1,xmm4  */ \
_LINE3( 0x0F,0x28,0xC1 )                      /* movaps      xmm0,xmm1  */ \
_LINE3( 0x0F,0x12,0xCB )                      /* movhlps     xmm1,xmm3  */ \
_LINE3( 0x0F,0x16,0xC2 )                      /* movlhps     xmm0,xmm2  */ \
_LINE4( 0xF2,0x0F,0x10,0x28 )                 /* movsd       xmm5,mmword ptr [eax]  */ \
_LINE3( 0x0F,0x16,0xED )                      /* movlhps     xmm5,xmm5  */ \
_LINE3( 0x0F,0x28,0xE2 )                      /* movaps      xmm4,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xE5 )                 /* mulpd       xmm4,xmm5  */ \
_LINE5( 0xF2,0x0F,0x10,0x78,0x10 )            /* movsd       xmm7,mmword ptr [eax+10h]  */ \
_LINE3( 0x0F,0x16,0xFF )                      /* movlhps     xmm7,xmm7  */ \
_LINE4( 0x66,0x0F,0x59,0xEB )                 /* mulpd       xmm5,xmm3  */ \
_LINE3( 0x0F,0x28,0xF7 )                      /* movaps      xmm6,xmm7  */ \
_LINE4( 0x66,0x0F,0x59,0xF0 )                 /* mulpd       xmm6,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xF9 )                 /* mulpd       xmm7,xmm1  */ \
_LINE4( 0x66,0x0F,0x58,0xF5 )                 /* addpd       xmm6,xmm5  */ \
_LINE4( 0x66,0x0F,0x5C,0xFC )                 /* subpd       xmm7,xmm4  */ \
_LINE5( 0xF2,0x0F,0x10,0x68,0x08 )            /* movsd       xmm5,mmword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0xED )                      /* movlhps     xmm5,xmm5  */ \
_LINE3( 0x0F,0x28,0xE5 )                      /* movaps      xmm4,xmm5  */ \
_LINE4( 0x66,0x0F,0x59,0xE0 )                 /* mulpd       xmm4,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xE9 )                 /* mulpd       xmm5,xmm1  */ \
_LINE4( 0x66,0x0F,0x5C,0xFC )                 /* subpd       xmm7,xmm4  */ \
_LINE4( 0x66,0x0F,0x58,0xF5 )                 /* addpd       xmm6,xmm5  */ \
_LINE3( 0x0F,0x28,0xE6 )                      /* movaps      xmm4,xmm6  */ \
_LINE3( 0x0F,0x12,0xE4 )                      /* movhlps     xmm4,xmm4  */ \
_LINE3( 0x0F,0x16,0xF6 )                      /* movlhps     xmm6,xmm6  */ \
_LINE4( 0xF2,0x0F,0x10,0xE8 )                 /* movsd       xmm5,xmm0  */ \
_LINE4( 0xF2,0x0F,0x59,0xEE )                 /* mulsd       xmm5,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xF1 )                 /* mulpd       xmm6,xmm1  */ \
_LINE4( 0xF2,0x0F,0x59,0xCF )                 /* mulsd       xmm1,xmm7  */ \
_LINE4( 0xF2,0x0F,0x5C,0xCD )                 /* subsd       xmm1,xmm5  */ \
_LINE3( 0x0F,0x28,0xEF )                      /* movaps      xmm5,xmm7  */ \
_LINE3( 0x0F,0x12,0xED )                      /* movhlps     xmm5,xmm5  */ \
_LINE3( 0x0F,0x16,0xFF )                      /* movlhps     xmm7,xmm7  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                 /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE4( 0x66,0x0F,0x59,0xF8 )                 /* mulpd       xmm7,xmm0  */ \
_LINE4( 0x66,0x0F,0x58,0xFE )                 /* addpd       xmm7,xmm6  */ \
_LINE4( 0xF2,0x0F,0x10,0xC4 )                 /* movsd       xmm0,xmm4  */ \
_LINE4( 0xF2,0x0F,0x59,0xC2 )                 /* mulsd       xmm0,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xE3 )                 /* mulpd       xmm4,xmm3  */ \
_LINE4( 0xF2,0x0F,0x59,0xDD )                 /* mulsd       xmm3,xmm5  */ \
_LINE4( 0xF2,0x0F,0x58,0xC3 )                 /* addsd       xmm0,xmm3  */ \
_LINE4( 0x66,0x0F,0x59,0xEA )                 /* mulpd       xmm5,xmm2  */ \
_LINE4( 0x66,0x0F,0x5C,0xE5 )                 /* subpd       xmm4,xmm5  */ \
_LINE4( 0xF2,0x0F,0x5C,0xC8 )                 /* subsd       xmm1,xmm0  */ \
_LINE4( 0x66,0x0F,0x58,0xFC )                 /* addpd       xmm7,xmm4  */ \
_LINE5( 0xF2,0x0F,0x11,0x78,0x08 )            /* movsd       mmword ptr [eax+8],xmm7  */ \
_LINE5( 0xF2,0x0F,0x11,0x48,0x10 )            /* movsd       mmword ptr [eax+10h],xmm1  */ \
_LINE3( 0x0F,0x17,0x38 )                      /* movhps      qword ptr [eax],xmm7  */ \
_END_ASM

/// Умножение трехмерного вектора на кватернион трансформации двойной точности, команды SSE4
#define QUATERNIONP3DDTRANSFORMSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                 /* mov         eax,dword ptr [esp+4]  */ \
_LINE3( 0x0F,0x16,0x10 )                      /* movhps      xmm2,qword ptr [eax]  */ \
_LINE4( 0x0F,0x12,0x50,0x08 )                 /* movlps      xmm2,qword ptr [eax+8]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x58,0x10 )            /* lddqu       xmm3,xmmword ptr [eax+10h]  */ \
_LINE3( 0x0F,0x12,0xE2 )                      /* movhlps     xmm4,xmm2  */ \
_LINE3( 0x0F,0x57,0xC9 )                      /* xorps       xmm1,xmm1  */ \
_LINE3( 0x0F,0x16,0xE3 )                      /* movlhps     xmm4,xmm3  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                 /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0x66,0x0F,0x5C,0xCC )                 /* subpd       xmm1,xmm4  */ \
_LINE3( 0x0F,0x28,0xC1 )                      /* movaps      xmm0,xmm1  */ \
_LINE3( 0x0F,0x12,0xCB )                      /* movhlps     xmm1,xmm3  */ \
_LINE3( 0x0F,0x16,0xC2 )                      /* movlhps     xmm0,xmm2  */ \
_LINE4( 0xF2,0x0F,0x12,0x28 )                 /* movddup     xmm5,mmword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xE2 )                      /* movaps      xmm4,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xE5 )                 /* mulpd       xmm4,xmm5  */ \
_LINE5( 0xF2,0x0F,0x12,0x78,0x10 )            /* movddup     xmm7,mmword ptr [eax+10h]  */ \
_LINE4( 0x66,0x0F,0x59,0xEB )                 /* mulpd       xmm5,xmm3  */ \
_LINE3( 0x0F,0x28,0xF7 )                      /* movaps      xmm6,xmm7  */ \
_LINE4( 0x66,0x0F,0x59,0xF0 )                 /* mulpd       xmm6,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xF9 )                 /* mulpd       xmm7,xmm1  */ \
_LINE4( 0x66,0x0F,0x58,0xF5 )                 /* addpd       xmm6,xmm5  */ \
_LINE4( 0x66,0x0F,0x5C,0xFC )                 /* subpd       xmm7,xmm4  */ \
_LINE5( 0xF2,0x0F,0x12,0x68,0x08 )            /* movddup     xmm5,mmword ptr [eax+8]  */ \
_LINE3( 0x0F,0x28,0xE5 )                      /* movaps      xmm4,xmm5  */ \
_LINE4( 0x66,0x0F,0x59,0xE0 )                 /* mulpd       xmm4,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xE9 )                 /* mulpd       xmm5,xmm1  */ \
_LINE4( 0x66,0x0F,0x5C,0xFC )                 /* subpd       xmm7,xmm4  */ \
_LINE4( 0x66,0x0F,0x58,0xF5 )                 /* addpd       xmm6,xmm5  */ \
_LINE3( 0x0F,0x28,0xE6 )                      /* movaps      xmm4,xmm6  */ \
_LINE3( 0x0F,0x12,0xE4 )                      /* movhlps     xmm4,xmm4  */ \
_LINE3( 0x0F,0x16,0xF6 )                      /* movlhps     xmm6,xmm6  */ \
_LINE4( 0xF2,0x0F,0x10,0xE8 )                 /* movsd       xmm5,xmm0  */ \
_LINE4( 0xF2,0x0F,0x59,0xEE )                 /* mulsd       xmm5,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xF1 )                 /* mulpd       xmm6,xmm1  */ \
_LINE4( 0xF2,0x0F,0x59,0xCF )                 /* mulsd       xmm1,xmm7  */ \
_LINE4( 0xF2,0x0F,0x5C,0xCD )                 /* subsd       xmm1,xmm5  */ \
_LINE3( 0x0F,0x28,0xEF )                      /* movaps      xmm5,xmm7  */ \
_LINE3( 0x0F,0x12,0xED )                      /* movhlps     xmm5,xmm5  */ \
_LINE3( 0x0F,0x16,0xFF )                      /* movlhps     xmm7,xmm7  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                 /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE4( 0x66,0x0F,0x59,0xF8 )                 /* mulpd       xmm7,xmm0  */ \
_LINE4( 0x66,0x0F,0x58,0xFE )                 /* addpd       xmm7,xmm6  */ \
_LINE4( 0xF2,0x0F,0x10,0xC4 )                 /* movsd       xmm0,xmm4  */ \
_LINE4( 0xF2,0x0F,0x59,0xC2 )                 /* mulsd       xmm0,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xE3 )                 /* mulpd       xmm4,xmm3  */ \
_LINE4( 0xF2,0x0F,0x59,0xDD )                 /* mulsd       xmm3,xmm5  */ \
_LINE4( 0xF2,0x0F,0x58,0xC3 )                 /* addsd       xmm0,xmm3  */ \
_LINE4( 0x66,0x0F,0x59,0xEA )                 /* mulpd       xmm5,xmm2  */ \
_LINE4( 0x66,0x0F,0x5C,0xE5 )                 /* subpd       xmm4,xmm5  */ \
_LINE4( 0xF2,0x0F,0x5C,0xC8 )                 /* subsd       xmm1,xmm0  */ \
_LINE4( 0x66,0x0F,0x58,0xFC )                 /* addpd       xmm7,xmm4  */ \
_LINE5( 0xF2,0x0F,0x11,0x78,0x08 )            /* movsd       mmword ptr [eax+8],xmm7  */ \
_LINE5( 0xF2,0x0F,0x11,0x48,0x10 )            /* movsd       mmword ptr [eax+10h],xmm1  */ \
_LINE3( 0x0F,0x17,0x38 )                      /* movhps      qword ptr [eax],xmm7  */ \
_END_ASM

/// Умножение трехмерного вектора на кватернион трансформации двойной точности, команды SSE4
#define QUATERNIONP3DDTRANSFORMSSE4_STD1 \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                 /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x10 )                 /* lddqu       xmm2,xmmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x58,0x10 )            /* lddqu       xmm3,xmmword ptr [eax+10h]  */ \
_LINE4( 0xF2,0x0F,0x10,0xE2 )                 /* movsd       xmm4,xmm2  */ \
_LINE3( 0x0F,0x16,0xE3 )                      /* movlhps     xmm4,xmm3  */ \
_LINE3( 0x0F,0x57,0xC0 )                      /* xorps       xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x5C,0xC4 )                 /* subpd       xmm0,xmm4  */ \
_LINE3( 0x0F,0x28,0xE8 )                      /* movaps      xmm5,xmm0  */ \
_LINE3( 0x0F,0x12,0xEB )                      /* movhlps     xmm5,xmm3  */ \
_LINE3( 0x0F,0x16,0xE0 )                      /* movlhps     xmm4,xmm0  */ \
_LINE3( 0x0F,0x12,0xE2 )                      /* movhlps     xmm4,xmm2  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                 /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                 /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0x12,0x48,0x10 )            /* movddup     xmm1,mmword ptr [eax+10h]  */ \
_LINE3( 0x0F,0x28,0xF0 )                      /* movaps      xmm6,xmm0  */ \
_LINE3( 0x0F,0x28,0xF8 )                      /* movaps      xmm7,xmm0  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xF5,0x31 )       /* dppd        xmm6,xmm5,31h  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xFB,0x32 )       /* dppd        xmm7,xmm3,32h  */ \
_LINE3( 0x0F,0x56,0xF7 )                      /* orps        xmm6,xmm7  */ \
_LINE3( 0x0F,0x28,0xF9 )                      /* movaps      xmm7,xmm1  */ \
_LINE4( 0x66,0x0F,0x59,0xFC )                 /* mulpd       xmm7,xmm4  */ \
_LINE4( 0x66,0x0F,0x58,0xF7 )                 /* addpd       xmm6,xmm7  */ \
_LINE3( 0x0F,0x28,0xF8 )                      /* movaps      xmm7,xmm0  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC4,0x31 )       /* dppd        xmm0,xmm4,31h  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xFA,0x32 )       /* dppd        xmm7,xmm2,32h  */ \
_LINE3( 0x0F,0x56,0xC7 )                      /* orps        xmm0,xmm7  */ \
_LINE4( 0x66,0x0F,0x59,0xCD )                 /* mulpd       xmm1,xmm5  */ \
_LINE4( 0x66,0x0F,0x5C,0xC8 )                 /* subpd       xmm1,xmm0  */ \
_LINE3( 0x0F,0x28,0xFE )                      /* movaps      xmm7,xmm6  */ \
_LINE3( 0x0F,0x28,0xC1 )                      /* movaps      xmm0,xmm1  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                 /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xFD,0x31 )       /* dppd        xmm7,xmm5,31h  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC4,0x31 )       /* dppd        xmm0,xmm4,31h  */ \
_LINE4( 0xF2,0x0F,0x58,0xF8 )                 /* addsd       xmm7,xmm0  */ \
_LINE4( 0xF2,0x0F,0x11,0x38 )                 /* movsd       mmword ptr [eax],xmm7  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xDE,0x31 )       /* dppd        xmm3,xmm6,31h  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xF4,0x32 )       /* dppd        xmm6,xmm4,32h  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xD1,0x31 )       /* dppd        xmm2,xmm1,31h  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xCD,0x32 )       /* dppd        xmm1,xmm5,32h  */ \
_LINE3( 0x0F,0x56,0xD9 )                      /* orps        xmm3,xmm1  */ \
_LINE3( 0x0F,0x56,0xD6 )                      /* orps        xmm2,xmm6  */ \
_LINE4( 0x66,0x0F,0x5C,0xDA )                 /* subpd       xmm3,xmm2  */ \
_LINE5( 0x66,0x0F,0x11,0x58,0x08 )            /* movupd      xmmword ptr [eax+8],xmm3  */ \
_END_ASM

#endif
