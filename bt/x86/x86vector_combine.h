//=============================================================================
///**
// *  @file vector_combine.h
// *
// *  $Id: vector_combine.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float combine, MS Visual C++ 2003-2008
// *
// *  @author P_anteleymonov A_leksandr K_onstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_VECTOR_COMBINE_H
#define GEN3_VECTOR_COMBINE_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//*********************************** COMBINE STDCALL **************************************
// vector combine [esp+4]-a void *, [esp+8]-b void *,[esp+12]-rez void *, [esp+16]-double/float, [esp+24]-double/float

/// Масштабирование и сложение двух духмерных векторов одинарной точности, команды FPU
#define VECTORP2DCOMBINEFPU_STD \
BEGIN_ASM \
_LINE4( 0xD9,0x44,0x24,0x10 )        /* fld         dword ptr [esp+10h]  */ \
_LINE4( 0xD9,0x44,0x24,0x14 )        /* fld         dword ptr [esp+14h]  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )        /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0x00 )                  /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0xCA )                  /* fmul        st,st(2)  */ \
_LINE3( 0xD9,0x40,0x04 )             /* fld         dword ptr [eax+4]  */ \
_LINE2( 0xDE,0xCB )                  /* fmulp       st(3),st  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )        /* mov         eax,dword ptr [esp+8]  */ \
_LINE2( 0xD9,0x00 )                  /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0xCA )                  /* fmul        st,st(2)  */ \
_LINE2( 0xDE,0xC1 )                  /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x40,0x04 )             /* fld         dword ptr [eax+4]  */ \
_LINE2( 0xDE,0xCA )                  /* fmulp       st(2),st  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )        /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE2( 0xD9,0x18 )                  /* fstp        dword ptr [eax]  */ \
_LINE2( 0xDE,0xC1 )                  /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x58,0x04 )             /* fstp        dword ptr [eax+4]  */ \
END_ASM

/// Масштабирование и сложение двух четырехмерных векторов одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP2DCOMBINESSE_STD \
_BEGIN_ASM \
_LINE3( 0x0F,0x57,0xC0 )                                    /* xorps       xmm0,xmm0  */ \
_LINE3( 0x0F,0x57,0xC9 )                                    /* xorps       xmm1,xmm1  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE6( 0xF3,0x0F,0x10,0x54,0x24,0x10 )                     /* movss       xmm2,dword ptr [esp+10h]  */ \
_LINE3( 0x0F,0x12,0x00 )                                    /* movlps      xmm0,qword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE6( 0xF3,0x0F,0x10,0x5C,0x24,0x14 )                     /* movss       xmm3,dword ptr [esp+14h]  */ \
_LINE3( 0x0F,0x12,0x0A )                                    /* movlps      xmm1,qword ptr [edx]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x50 )                               /* shufps      xmm2,xmm2,0x50  */ \
_LINE4( 0x0F,0xC6,0xDB,0x50 )                               /* shufps      xmm3,xmm3,0x50  */ \
_LINE3( 0x0F,0x59,0xC2 )                                    /* mulps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x59,0xCB )                                    /* mulps       xmm1,xmm3  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x00 )                                    /* movlps      qword ptr [eax],xmm0  */ \
_END_ASM

/// Масштабирование и сложение двух духмерных векторов одинарной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP2DCOMBINESSE2_STD \
_BEGIN_ASM \
_LINE6( 0xF3,0x0F,0x10,0x54,0x24,0x10 )                     /* movss       xmm2,dword ptr [esp+10h]  */ \
_LINE6( 0xF3,0x0F,0x10,0x5C,0x24,0x14 )                     /* movss       xmm3,dword ptr [esp+14h]  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,mmword ptr [edx]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x50 )                               /* shufps      xmm2,xmm2,0x50  */ \
_LINE4( 0x0F,0xC6,0xDB,0x50 )                               /* shufps      xmm3,xmm3,0x50  */ \
_LINE3( 0x0F,0x59,0xC2 )                                    /* mulps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x59,0xCB )                                    /* mulps       xmm1,xmm3  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x00 )                               /* movsd       mmword ptr [eax],xmm0  */ \
_END_ASM

/// Масштабирование и сложение двух трехмерных векторов одинарной точности, команды FPU
#define VECTORP3DCOMBINEFPU_STD \
BEGIN_ASM \
_LINE4( 0xD9,0x44,0x24,0x10 )         /* fld         dword ptr [esp+10h]  */ \
_LINE4( 0xD9,0x44,0x24,0x14 )         /* fld         dword ptr [esp+14h]  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )         /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0x00 )                   /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0xCA )                   /* fmul        st,st(2)  */ \
_LINE3( 0xD9,0x40,0x04 )              /* fld         dword ptr [eax+4]  */ \
_LINE2( 0xD8,0xCB )                   /* fmul        st,st(3)  */ \
_LINE3( 0xD9,0x40,0x08 )              /* fld         dword ptr [eax+8]  */ \
_LINE2( 0xDE,0xCC )                   /* fmulp       st(4),st  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )         /* mov         eax,dword ptr [esp+8]  */ \
_LINE2( 0xD9,0x00 )                   /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0xCB )                   /* fmul        st,st(3)  */ \
_LINE2( 0xDE,0xC2 )                   /* faddp       st(2),st  */ \
_LINE3( 0xD9,0x40,0x04 )              /* fld         dword ptr [eax+4]  */ \
_LINE2( 0xD8,0xCB )                   /* fmul        st,st(3)  */ \
_LINE2( 0xDE,0xC1 )                   /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x40,0x08 )              /* fld         dword ptr [eax+8]  */ \
_LINE2( 0xDE,0xCB )                   /* fmulp       st(3),st  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )         /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE3( 0xD9,0x58,0x04 )              /* fstp        dword ptr [eax+4]  */ \
_LINE2( 0xD9,0x18 )                   /* fstp        dword ptr [eax]  */ \
_LINE2( 0xDE,0xC1 )                   /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x58,0x08 )              /* fstp        dword ptr [eax+8]  */ \
END_ASM

/// Масштабирование и сложение двух трехмерных векторов одинарной точности, команды SSE.
/// @brief for CPUTYPE1
#define VECTORP3DCOMBINESSE_STD \
_BEGIN_ASM \
_LINE6( 0xF3,0x0F,0x10,0x54,0x24,0x10 )                     /* movss       xmm2,dword ptr [esp+10h]  */ \
_LINE6( 0xF3,0x0F,0x10,0x5C,0x24,0x14 )                     /* movss       xmm3,dword ptr [esp+14h]  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF3,0x0F,0x10,0x00 )                               /* movss       xmm0,dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x16,0x40,0x04 )                               /* movhps      xmm0,qword ptr [eax+4]  */ \
_LINE4( 0xF3,0x0F,0x10,0x0A )                               /* movss       xmm1,dword ptr [edx]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+12]  */ \
_LINE4( 0x0F,0x16,0x4A,0x04 )                               /* movhps      xmm1,qword ptr [edx+4]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x04 )                               /* shufps      xmm2,xmm2,4  */ \
_LINE4( 0x0F,0xC6,0xDB,0x04 )                               /* shufps      xmm3,xmm3,4  */ \
_LINE3( 0x0F,0x59,0xC2 )                                    /* mulps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x59,0xCB )                                    /* mulps       xmm1,xmm3  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE4( 0xF3,0x0F,0x11,0x00 )                               /* movss       dword ptr [eax],xmm0  */ \
_LINE4( 0x0F,0x17,0x40,0x04 )                               /* movhps      qword ptr [eax+4],xmm0  */ \
_END_ASM

/// Масштабирование и сложение двух четырехмерных векторов одинарной точности, команды FPU
#define VECTORP4DCOMBINEFPU_STD \
BEGIN_ASM \
_LINE4( 0xD9,0x44,0x24,0x10 )        /* fld         dword ptr [esp+10h]  */ \
_LINE4( 0xD9,0x44,0x24,0x14 )        /* fld         dword ptr [esp+14h]  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )        /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0x00 )                  /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0xCA )                  /* fmul        st,st(2)  */ \
_LINE3( 0xD9,0x40,0x04 )             /* fld         dword ptr [eax+4]  */ \
_LINE2( 0xD8,0xCB )                  /* fmul        st,st(3)  */ \
_LINE3( 0xD9,0x40,0x08 )             /* fld         dword ptr [eax+8]  */ \
_LINE2( 0xD8,0xCC )                  /* fmul        st,st(4)  */ \
_LINE3( 0xD9,0x40,0x0C )             /* fld         dword ptr [eax+0Ch]  */ \
_LINE2( 0xDE,0xCD )                  /* fmulp       st(5),st  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )        /* mov         eax,dword ptr [esp+8]  */ \
_LINE2( 0xD9,0x00 )                  /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0xCC )                  /* fmul        st,st(4)  */ \
_LINE2( 0xDE,0xC3 )                  /* faddp       st(3),st  */ \
_LINE3( 0xD9,0x40,0x04 )             /* fld         dword ptr [eax+4]  */ \
_LINE2( 0xD8,0xCC )                  /* fmul        st,st(4)  */ \
_LINE2( 0xDE,0xC2 )                  /* faddp       st(2),st  */ \
_LINE3( 0xD9,0x40,0x08 )             /* fld         dword ptr [eax+8]  */ \
_LINE2( 0xD8,0xCC )                  /* fmul        st,st(4)  */ \
_LINE2( 0xDE,0xC1 )                  /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x40,0x0C )             /* fld         dword ptr [eax+0Ch]  */ \
_LINE2( 0xDE,0xCC )                  /* fmulp       st(4),st  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )        /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE3( 0xD9,0x58,0x08 )             /* fstp        dword ptr [eax+8]  */ \
_LINE3( 0xD9,0x58,0x04 )             /* fstp        dword ptr [eax+4]  */ \
_LINE2( 0xD9,0x18 )                  /* fstp        dword ptr [eax]  */ \
_LINE2( 0xDE,0xC1 )                  /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x58,0x0C )             /* fstp        dword ptr [eax+0Ch]  */ \
END_ASM

/// Масштабирование и сложение двух четырехмерных векторов одинарной точности, команды SSE.
/// @brief for CPUTYPE1
#define VECTORP4DCOMBINESSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE3( 0x0F,0x12,0x00 )                                    /* movlps      xmm0,qword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )                               /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE3( 0x0F,0x12,0x0A )                                    /* movlps      xmm1,qword ptr [edx]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+12]  */ \
_LINE4( 0x0F,0x16,0x4A,0x08 )                               /* movhps      xmm1,qword ptr [edx+8]  */ \
_LINE6( 0xF3,0x0F,0x10,0x54,0x24,0x10 )                     /* movss       xmm2,dword ptr [esp+10h]  */ \
_LINE6( 0xF3,0x0F,0x10,0x5C,0x24,0x14 )                     /* movss       xmm3,dword ptr [esp+14h]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xC2 )                                    /* mulps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x59,0xCB )                                    /* mulps       xmm1,xmm3  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x00 )                                    /* movlps      qword ptr [eax],xmm0  */ \
_LINE4( 0x0F,0x17,0x40,0x08 )                               /* movhps      qword ptr [eax+8],xmm0  */ \
_END_ASM

/// Масштабирование и сложение двух четырехмерных векторов одинарной точности, команды SSE3.
/// @brief for CPUTYPE3
#define VECTORP4DCOMBINESSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE6( 0xF3,0x0F,0x10,0x54,0x24,0x10 )                     /* movss       xmm2,dword ptr [esp+10h]  */ \
_LINE6( 0xF3,0x0F,0x10,0x5C,0x24,0x14 )                     /* movss       xmm3,dword ptr [esp+14h]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xC2 )                                    /* mulps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x59,0xCB )                                    /* mulps       xmm1,xmm3  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0x66,0x0F,0x17,0x41,0x08 )                          /* movhpd      qword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Масштабирование и сложение двух четырехмерных векторов одинарной точности, команды SSE4.
/// @brief for CPUTYPE3
#define VECTORP4DCOMBINESSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+12]  */ \
_LINE6( 0xF3,0x0F,0x10,0x54,0x24,0x10 )                     /* movss       xmm2,dword ptr [esp+10h]  */ \
_LINE6( 0xF3,0x0F,0x10,0x5C,0x24,0x14 )                     /* movss       xmm3,dword ptr [esp+14h]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xC2 )                                    /* mulps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x59,0xCB )                                    /* mulps       xmm1,xmm3  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x11,0x00 )                                    /* movups      xmmword ptr [eax],xmm0  */ \
_END_ASM

/// Масштабирование и сложение двух духмерных векторов двойной точности, команды FPU
#define VECTORP2DDCOMBINEFPU_STD \
BEGIN_ASM \
_LINE4( 0xDD,0x44,0x24,0x10 )    /* fld         qword ptr [esp+10h]  */ \
_LINE4( 0xDD,0x44,0x24,0x18 )    /* fld         qword ptr [esp+18h]  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )    /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xDD,0x00 )              /* fld         qword ptr [eax]  */ \
_LINE2( 0xD8,0xCA )              /* fmul        st,st(2)  */ \
_LINE3( 0xDD,0x40,0x08 )         /* fld         qword ptr [eax+8]  */ \
_LINE2( 0xDE,0xCB )              /* fmulp       st(3),st  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )    /* mov         eax,dword ptr [esp+8]  */ \
_LINE2( 0xDD,0x00 )              /* fld         qword ptr [eax]  */ \
_LINE2( 0xD8,0xCA )              /* fmul        st,st(2)  */ \
_LINE2( 0xDE,0xC1 )              /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x40,0x08 )         /* fld         qword ptr [eax+8]  */ \
_LINE2( 0xDE,0xCA )              /* fmulp       st(2),st  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )    /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE2( 0xDD,0x18 )              /* fstp        qword ptr [eax]  */ \
_LINE2( 0xDE,0xC1 )              /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x58,0x08 )         /* fstp        qword ptr [eax+8]  */ \
END_ASM

/// Масштабирование и сложение двух духмерных векторов двойной точности, команды SSE4.
/// @brief for CPUTYPE3
#define VECTORP2DDCOMBINESSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x12 )                               /* lddqu       xmm2,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE6( 0xF2,0x0F,0x12,0x4C,0x24,0x10 )                     /* movddup     xmm1,mmword ptr [esp+10h]  */ \
_LINE4( 0x66,0x0F,0x59,0xC1 )                               /* mulpd       xmm0,xmm1  */ \
_LINE6( 0xF2,0x0F,0x12,0x5C,0x24,0x18 )                     /* movddup     xmm3,mmword ptr [esp+18h]  */ \
_LINE4( 0x66,0x0F,0x59,0xD3 )                               /* mulpd       xmm2,xmm3  */ \
_LINE4( 0x66,0x0F,0x58,0xC2 )                               /* addpd       xmm0,xmm2  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_END_ASM

/// Масштабирование и сложение двух трехмерных векторов двойной точности, команды FPU
#define VECTORP3DDCOMBINEFPU_STD \
BEGIN_ASM \
_LINE4( 0xDD,0x44,0x24,0x10 )    /* fld         qword ptr [esp+10h]  */ \
_LINE4( 0xDD,0x44,0x24,0x18 )    /* fld         qword ptr [esp+18h]  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )    /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xDD,0x00 )              /* fld         qword ptr [eax]  */ \
_LINE2( 0xD8,0xCA )              /* fmul        st,st(2)  */ \
_LINE3( 0xDD,0x40,0x08 )         /* fld         qword ptr [eax+8]  */ \
_LINE2( 0xD8,0xCB )              /* fmul        st,st(3)  */ \
_LINE3( 0xDD,0x40,0x10 )         /* fld         qword ptr [eax+10h]  */ \
_LINE2( 0xDE,0xCC )              /* fmulp       st(4),st  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )    /* mov         eax,dword ptr [esp+8]  */ \
_LINE2( 0xDD,0x00 )              /* fld         qword ptr [eax]  */ \
_LINE2( 0xD8,0xCB )              /* fmul        st,st(3)  */ \
_LINE2( 0xDE,0xC2 )              /* faddp       st(2),st  */ \
_LINE3( 0xDD,0x40,0x08 )         /* fld         qword ptr [eax+8]  */ \
_LINE2( 0xD8,0xCB )              /* fmul        st,st(3)  */ \
_LINE2( 0xDE,0xC1 )              /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x40,0x10 )         /* fld         qword ptr [eax+10h]  */ \
_LINE2( 0xDE,0xCB )              /* fmulp       st(3),st  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )    /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE3( 0xDD,0x58,0x08 )         /* fstp        qword ptr [eax+8]  */ \
_LINE2( 0xDD,0x18 )              /* fstp        qword ptr [eax]  */ \
_LINE2( 0xDE,0xC1 )              /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x58,0x10 )         /* fstp        qword ptr [eax+10h]  */ \
END_ASM

/// Масштабирование и сложение двух трехмерных векторов двойной точности, команды SSE4.
/// @brief for CPUTYPE3
#define VECTORP3DDCOMBINESSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x12 )                               /* lddqu       xmm2,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE6( 0xF2,0x0F,0x12,0x4C,0x24,0x10 )                     /* movddup     xmm1,mmword ptr [esp+10h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x60,0x10 )                          /* movsd       xmm4,mmword ptr [eax+10h]  */ \
_LINE4( 0x66,0x0F,0x59,0xC1 )                               /* mulpd       xmm0,xmm1  */ \
_LINE6( 0xF2,0x0F,0x12,0x5C,0x24,0x18 )                     /* movddup     xmm3,mmword ptr [esp+18h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x6A,0x10 )                          /* movsd       xmm5,xmmword ptr [edx+10h]  */ \
_LINE4( 0x66,0x0F,0x59,0xD3 )                               /* mulpd       xmm2,xmm3  */ \
_LINE4( 0xF2,0x0F,0x59,0xE1 )                               /* mulsd       xmm4,xmm1  */ \
_LINE4( 0xF2,0x0F,0x59,0xEB )                               /* mulsd       xmm5,xmm3  */ \
_LINE4( 0x66,0x0F,0x58,0xC2 )                               /* addpd       xmm0,xmm2  */ \
ASM( addsd       xmm4,xmm5 )                               /* addsd       xmm4,xmm5  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x61,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm4  */ \
_END_ASM

/// Масштабирование и сложение двух четырехмерных векторов двойной точности, команды FPU
#define VECTORP4DDCOMBINEFPU_STD \
BEGIN_ASM \
_LINE4( 0xDD,0x44,0x24,0x10 )    /* fld         qword ptr [esp+10h]  */ \
_LINE4( 0xDD,0x44,0x24,0x18 )    /* fld         qword ptr [esp+18h]  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )    /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xDD,0x00 )              /* fld         qword ptr [eax]  */ \
_LINE2( 0xD8,0xCA )              /* fmul        st,st(2)  */ \
_LINE3( 0xDD,0x40,0x08 )         /* fld         qword ptr [eax+8]  */ \
_LINE2( 0xD8,0xCB )              /* fmul        st,st(3)  */ \
_LINE3( 0xDD,0x40,0x10 )         /* fld         qword ptr [eax+10h]  */ \
_LINE2( 0xD8,0xCC )              /* fmul        st,st(4)  */ \
_LINE3( 0xDD,0x40,0x18 )         /* fld         qword ptr [eax+18h]  */ \
_LINE2( 0xDE,0xCD )              /* fmulp       st(5),st  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )    /* mov         eax,dword ptr [esp+8]  */ \
_LINE2( 0xDD,0x00 )              /* fld         qword ptr [eax]  */ \
_LINE2( 0xD8,0xCC )              /* fmul        st,st(4)  */ \
_LINE2( 0xDE,0xC3 )              /* faddp       st(3),st  */ \
_LINE3( 0xDD,0x40,0x08 )         /* fld         qword ptr [eax+8]  */ \
_LINE2( 0xD8,0xCC )              /* fmul        st,st(4)  */ \
_LINE2( 0xDE,0xC2 )              /* faddp       st(2),st  */ \
_LINE3( 0xDD,0x40,0x10 )         /* fld         qword ptr [eax+10h]  */ \
_LINE2( 0xD8,0xCC )              /* fmul        st,st(4)  */ \
_LINE2( 0xDE,0xC1 )              /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x40,0x18 )         /* fld         qword ptr [eax+18h]  */ \
_LINE2( 0xDE,0xCC )              /* fmulp       st(4),st  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )    /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE3( 0xDD,0x58,0x10 )         /* fstp        qword ptr [eax+10h]  */ \
_LINE3( 0xDD,0x58,0x08 )         /* fstp        qword ptr [eax+8]  */ \
_LINE2( 0xDD,0x18 )              /* fstp        qword ptr [eax]  */ \
_LINE2( 0xDE,0xC1 )              /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x58,0x18 )         /* fstp        qword ptr [eax+18h]  */ \
END_ASM

/// Масштабирование и сложение двух четырехмерных векторов двойной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP4DDCOMBINESSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )                               /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE5( 0x0F,0x12,0x4C,0x24,0x10 )                          /* movlps      xmm1,qword ptr [esp+10h]  */ \
_LINE3( 0x0F,0x12,0x00 )                                    /* movlps      xmm0,qword ptr [eax]  */ \
_LINE4( 0x0F,0x16,0x52,0x08 )                               /* movhps      xmm2,qword ptr [edx+8]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE5( 0x0F,0x12,0x5C,0x24,0x18 )                          /* movlps      xmm3,qword ptr [esp+18h]  */ \
_LINE4( 0x0F,0x16,0x60,0x18 )                               /* movhps      xmm4,qword ptr [eax+18h]  */ \
_LINE4( 0x66,0x0F,0x14,0xC9 )                               /* unpcklpd    xmm1,xmm1  */ \
_LINE3( 0x0F,0x12,0x12 )                                    /* movlps      xmm2,qword ptr [edx]  */ \
_LINE4( 0x66,0x0F,0x14,0xDB )                               /* unpcklpd    xmm3,xmm3  */ \
_LINE4( 0x0F,0x16,0x6A,0x18 )                               /* movhps      xmm5,qword ptr [edx+18h]  */ \
_LINE4( 0x66,0x0F,0x59,0xC1 )                               /* mulpd       xmm0,xmm1  */ \
_LINE4( 0x0F,0x12,0x60,0x10 )                               /* movlps      xmm4,qword ptr [eax+10h]  */ \
_LINE4( 0x0F,0x12,0x6A,0x10 )                               /* movlps      xmm5,qword ptr [edx+10h]  */ \
_LINE4( 0x66,0x0F,0x59,0xD3 )                               /* mulpd       xmm2,xmm3  */ \
_LINE4( 0x66,0x0F,0x59,0xE1 )                               /* mulpd       xmm4,xmm1  */ \
_LINE4( 0x66,0x0F,0x59,0xEB )                               /* mulpd       xmm5,xmm3  */ \
_LINE4( 0x66,0x0F,0x58,0xC2 )                               /* addpd       xmm0,xmm2  */ \
_LINE4( 0x66,0x0F,0x58,0xE5 )                               /* addpd       xmm4,xmm5  */ \
_LINE3( 0x0F,0x13,0x01 )                                    /* movlps      qword ptr [ecx],xmm0  */ \
_LINE4( 0x0F,0x13,0x61,0x10 )                               /* movlps      qword ptr [ecx+10h],xmm4  */ \
_LINE4( 0x0F,0x17,0x41,0x08 )                               /* movhps      qword ptr [ecx+8],xmm0 */ \
_LINE4( 0x0F,0x17,0x61,0x18 )                               /* movhps      qword ptr [ecx+18h],xmm4  */ \
_END_ASM

/// Масштабирование и сложение двух четырехмерных векторов двойной точности, команды SSE4.
/// @brief for CPUTYPE3
#define VECTORP4DDCOMBINESSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x12 )                               /* lddqu       xmm2,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE6( 0xF2,0x0F,0x12,0x4C,0x24,0x10 )                     /* movddup     xmm1,mmword ptr [esp+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x60,0x10 )                          /* lddqu       xmm4,xmmword ptr [eax+10h]  */ \
_LINE4( 0x66,0x0F,0x59,0xC1 )                               /* mulpd       xmm0,xmm1  */ \
_LINE6( 0xF2,0x0F,0x12,0x5C,0x24,0x18 )                     /* movddup     xmm3,mmword ptr [esp+18h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x6A,0x10 )                          /* lddqu       xmm5,xmmword ptr [edx+10h]  */ \
_LINE4( 0x66,0x0F,0x59,0xD3 )                               /* mulpd       xmm2,xmm3  */ \
_LINE4( 0x66,0x0F,0x59,0xE1 )                               /* mulpd       xmm4,xmm1  */ \
_LINE4( 0x66,0x0F,0x59,0xEB )                               /* mulpd       xmm5,xmm3  */ \
_LINE4( 0x66,0x0F,0x58,0xC2 )                               /* addpd       xmm0,xmm2  */ \
_LINE4( 0x66,0x0F,0x58,0xE5 )                               /* addpd       xmm4,xmm5  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_LINE5( 0x66,0x0F,0x11,0x61,0x10 )                          /* movupd      xmmword ptr [ecx+10h],xmm4  */ \
_END_ASM

//*********************************** COMBINE REGISTERS FASTCALL **************************************
// vector combine eax-a void *, edx-b void *,ecx-rez void *, edi-double/float, esi-double/float

/// Масштабирование и сложение двух духмерных векторов одинарной точности, команды FPU
#define VECTORP2DCOMBINEFPU \
BEGIN_ASM \
ASM( fld   dword ptr [edi]) \
ASM( fld   dword ptr [esi]) \
ASM( fld   dword ptr [eax]) \
ASM( fmul  st, st(2)) \
ASM( fld   dword ptr [edx]) \
ASM( fmul  st, st(2)) \
ASM( faddp st(1), st(0)) \
ASM( fstp  dword ptr [ecx]) \
ASM( fld   dword ptr [eax+4]) \
ASM( fmul  st, st(2)) \
ASM( fld   dword ptr [edx+4]) \
ASM( fmul  st, st(2)) \
ASM( faddp st(1), st(0)) \
ASM( fstp  dword ptr [ecx+4]) \
ASM( fstp st) \
ASM( fstp st) \
END_ASM

/// Масштабирование и сложение двух трехмерных векторов одинарной точности, команды FPU
#define VECTORP3DCOMBINEFPU \
BEGIN_ASM \
ASM( fld   dword ptr [edi]) \
ASM( fld   dword ptr [esi]) \
ASM( fld   dword ptr [eax]) \
ASM( fmul  st, st(2)) \
ASM( fld   dword ptr [edx]) \
ASM( fmul  st, st(2)) \
ASM( faddp st(1), st(0)) \
ASM( fstp  dword ptr [ecx]) \
ASM( fld   dword ptr [eax+4]) \
ASM( fmul  st, st(2)) \
ASM( fld   dword ptr [edx+4]) \
ASM( fmul  st, st(2)) \
ASM( faddp st(1), st(0)) \
ASM( fstp  dword ptr [ecx+4]) \
ASM( fld   dword ptr [eax+8]) \
ASM( fmul  st, st(2)) \
ASM( fld   dword ptr [edx+8]) \
ASM( fmul  st, st(2)) \
ASM( faddp st(1), st(0)) \
ASM( fstp  dword ptr [ecx+8]) \
ASM( fstp st) \
ASM( fstp st) \
END_ASM

/// Масштабирование и сложение двух четырехмерных векторов одинарной точности, команды FPU
#define VECTORP4DCOMBINEFPU \
BEGIN_ASM \
ASM( fld   dword ptr [edi]) \
ASM( fld   dword ptr [esi]) \
ASM( fld   dword ptr [eax]) \
ASM( fmul  st, st(2)) \
ASM( fld   dword ptr [edx]) \
ASM( fmul  st, st(2)) \
ASM( faddp st(1), st(0)) \
ASM( fstp  dword ptr [ecx]) \
ASM( fld   dword ptr [eax+4]) \
ASM( fmul  st, st(2)) \
ASM( fld   dword ptr [edx+4]) \
ASM( fmul  st, st(2)) \
ASM( faddp st(1), st(0)) \
ASM( fstp  dword ptr [ecx+4]) \
ASM( fld   dword ptr [eax+8]) \
ASM( fmul  st, st(2)) \
ASM( fld   dword ptr [edx+8]) \
ASM( fmul  st, st(2)) \
ASM( faddp st(1), st(0)) \
ASM( fstp  dword ptr [ecx+8]) \
ASM( fld   dword ptr [eax+12]) \
ASM( fmul  st, st(2)) \
ASM( fld   dword ptr [edx+12]) \
ASM( fmul  st, st(2)) \
ASM( faddp st(1), st(0)) \
ASM( fstp  dword ptr [ecx+12]) \
ASM( fstp st) \
ASM( fstp st) \
END_ASM

/// Масштабирование и сложение двух духмерных векторов двойной точности, команды FPU
#define VECTORP2DDCOMBINEFPU \
BEGIN_ASM \
ASM( fld   qword ptr [edi]) \
ASM( fld   qword ptr [esi]) \
ASM( fld   qword ptr [eax]) \
ASM( fmul  st, st(2)) \
ASM( fld   qword ptr [edx]) \
ASM( fmul  st, st(2)) \
ASM( faddp st(1), st(0)) \
ASM( fstp  qword ptr [ecx]) \
ASM( fld   qword ptr [eax+8]) \
ASM( fmul  st, st(2)) \
ASM( fld   qword ptr [edx+8]) \
ASM( fmul  st, st(2)) \
ASM( faddp st(1), st(0)) \
ASM( fstp  qword ptr [ecx+8]) \
ASM( fstp st) \
ASM( fstp st) \
END_ASM

/// Масштабирование и сложение двух трехмерных векторов двойной точности, команды FPU
#define VECTORP3DDCOMBINEFPU \
BEGIN_ASM \
ASM( fld   qword ptr [edi]) \
ASM( fld   qword ptr [esi]) \
ASM( fld   qword ptr [eax]) \
ASM( fmul  st, st(2)) \
ASM( fld   qword ptr [edx]) \
ASM( fmul  st, st(2)) \
ASM( faddp st(1), st(0)) \
ASM( fstp  qword ptr [ecx]) \
ASM( fld   qword ptr [eax+8]) \
ASM( fmul  st, st(2)) \
ASM( fld   qword ptr [edx+8]) \
ASM( fmul  st, st(2)) \
ASM( faddp st(1), st(0)) \
ASM( fstp  qword ptr [ecx+8]) \
ASM( fld   qword ptr [eax+16]) \
ASM( fmul  st, st(2)) \
ASM( fld   qword ptr [edx+16]) \
ASM( fmul  st, st(2)) \
ASM( faddp st(1), st(0)) \
ASM( fstp  qword ptr [ecx+16]) \
ASM( fstp st) \
ASM( fstp st) \
END_ASM

/// Масштабирование и сложение двух четырехмерных векторов двойной точности, команды FPU
#define VECTORP4DDCOMBINEFPU \
BEGIN_ASM \
ASM( fld   qword ptr [edi]) \
ASM( fld   qword ptr [esi]) \
ASM( fld   qword ptr [eax]) \
ASM( fmul  st, st(2)) \
ASM( fld   qword ptr [edx]) \
ASM( fmul  st, st(2)) \
ASM( faddp st(1), st(0)) \
ASM( fstp  qword ptr [ecx]) \
ASM( fld   qword ptr [eax+8]) \
ASM( fmul  st, st(2)) \
ASM( fld   qword ptr [edx+8]) \
ASM( fmul  st, st(2)) \
ASM( faddp st(1), st(0)) \
ASM( fstp  qword ptr [ecx+8]) \
ASM( fld   qword ptr [eax+16]) \
ASM( fmul  st, st(2)) \
ASM( fld   qword ptr [edx+16]) \
ASM( fmul  st, st(2)) \
ASM( faddp st(1), st(0)) \
ASM( fstp  qword ptr [ecx+16]) \
ASM( fld   qword ptr [eax+24]) \
ASM( fmul  st, st(2)) \
ASM( fld   qword ptr [edx+24]) \
ASM( fmul  st, st(2)) \
ASM( faddp st(1), st(0)) \
ASM( fstp  qword ptr [ecx+24]) \
ASM( fstp st) \
ASM( fstp st) \
END_ASM

#endif
