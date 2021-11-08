//=============================================================================
///**
// *  @file vector_lerp.h
// *
// *  $Id: vector_lerp.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float linearly interpolate, MS Visual C++ 2003-2008
// *
// *  @author P_anteleymonov A_leksandr K_onstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

// rez=(b-a)*c+a
// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

// *********************************** LERP STDCALL **************************************
// vector interpolate eax=[esp+4]-a void *, edx=[esp+8]-b void *, eсx=[esp+12]-rez void *, [esp+16]-c double/float

/// Интерполяция между двухмерными векторами одинарной точности, команды FPU
#define VECTORP2DLERPFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xD9,0x44,0x24,0x10 )                               /* fld         dword ptr [esp+10h]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xD9,0x02 )                                         /* fld         dword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE2( 0xD8,0xE1 )                                         /* fsub        st,st(1)  */ \
_LINE2( 0xD8,0xCA )                                         /* fmul        st,st(2)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xD9,0x19 )                                         /* fstp        dword ptr [ecx]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x42,0x04 )                                    /* fld         dword ptr [edx+4]  */ \
_LINE2( 0xD8,0xE1 )                                         /* fsub        st,st(1)  */ \
_LINE2( 0xD8,0xCA )                                         /* fmul        st,st(2)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x59,0x04 )                                    /* fstp        dword ptr [ecx+4]  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0) */ \
_END_ASM

/// Интерполяция между двухмерными векторами одинарной точности, команды SSE
/// @brief for CPUTYPE3
#define VECTORP2DLERPSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x5A,0x04 )                          /* movss       xmm3,dword ptr [edx+4]  */ \
_LINE4( 0xF3,0x0F,0x10,0x00 )                               /* movss       xmm0,dword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE4( 0xF3,0x0F,0x10,0x12 )                               /* movss       xmm2,dword ptr [edx]  */ \
_LINE6( 0xF3,0x0F,0x10,0x64,0x24,0x10 )                     /* movss       xmm4,dword ptr [esp+10h]  */ \
_LINE4( 0xF3,0x0F,0x5C,0xD0 )                               /* subss       xmm2,xmm0  */ \
_LINE4( 0xF3,0x0F,0x5C,0xD9 )                               /* subss       xmm3,xmm1  */ \
_LINE4( 0xF3,0x0F,0x59,0xD4 )                               /* mulss       xmm2,xmm4  */ \
_LINE4( 0xF3,0x0F,0x59,0xDC )                               /* mulss       xmm3,xmm4  */ \
_LINE4( 0xF3,0x0F,0x58,0xC2 )                               /* addss       xmm0,xmm2  */ \
_LINE4( 0xF3,0x0F,0x58,0xCB )                               /* addss       xmm1,xmm3  */ \
_LINE4( 0xF3,0x0F,0x11,0x01 )                               /* movss       dword ptr [ecx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x49,0x04 )                          /* movss       dword ptr [ecx+4],xmm1  */ \
_END_ASM

/// Интерполяция между двухмерными векторами одинарной точности, команды SSE2
/// @brief for CPUTYPE3
#define VECTORP2DLERPSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,mmword ptr [edx]  */ \
_LINE6( 0xF3,0x0F,0x10,0x64,0x24,0x10 )                     /* movss       xmm4,dword ptr [esp+10h]  */ \
_LINE3( 0x0F,0x5C,0xC8 )                                    /* subps       xmm1,xmm0  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE4( 0x0F,0xC6,0xE4,0x00 )                               /* shufps      xmm4,xmm4,0  */ \
_LINE3( 0x0F,0x59,0xCC )                                    /* mulps       xmm1,xmm4  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_END_ASM

/// Интерполяция между трехмерными векторами одинарной точности, команды FPU
#define VECTORP3DLERPFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xD9,0x44,0x24,0x10 )                               /* fld         dword ptr [esp+10h]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xD9,0x02 )                                         /* fld         dword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE2( 0xD8,0xE1 )                                         /* fsub        st,st(1)  */ \
_LINE2( 0xD8,0xCA )                                         /* fmul        st,st(2)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xD9,0x19 )                                         /* fstp        dword ptr [ecx]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x42,0x04 )                                    /* fld         dword ptr [edx+4]  */ \
_LINE2( 0xD8,0xE1 )                                         /* fsub        st,st(1)  */ \
_LINE2( 0xD8,0xCA )                                         /* fmul        st,st(2)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x59,0x04 )                                    /* fstp        dword ptr [ecx+4]  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD9,0x42,0x08 )                                    /* fld         dword ptr [edx+8]  */ \
_LINE2( 0xD8,0xE1 )                                         /* fsub        st,st(1)  */ \
_LINE2( 0xD8,0xCA )                                         /* fmul        st,st(2)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x59,0x08 )                                    /* fstp        dword ptr [ecx+8]  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

/// Интерполяция между трехмерными векторами одинарной точности, команды SSE
/// @brief for CPUTYPE3
#define VECTORP3DLERPSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE3( 0x0F,0x16,0x00 )                                    /* movhps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x16,0x0A )                                    /* movhps      xmm1,qword ptr [edx]  */ \
_LINE6( 0xF3,0x0F,0x10,0x64,0x24,0x10 )                     /* movss       xmm4,dword ptr [esp+10h]  */ \
_LINE3( 0x0F,0x5C,0xC8 )                                    /* subps       xmm1,xmm0  */ \
_LINE4( 0x0F,0xC6,0xE4,0x00 )                               /* shufps      xmm4,xmm4,0  */ \
_LINE3( 0x0F,0x59,0xCC )                                    /* mulps       xmm1,xmm4  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x17,0x01 )                                    /* movhps      qword ptr [ecx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x41,0x08 )                          /* movss       dword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Интерполяция между четырехмерными векторами одинарной точности, команды FPU
/// @brief for CPUTYPE1
#define VECTORP4DLERPFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xD9,0x44,0x24,0x10 )                               /* fld         dword ptr [esp+10h]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xD9,0x02 )                                         /* fld         dword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE2( 0xD8,0xE1 )                                         /* fsub        st,st(1)  */ \
_LINE2( 0xD8,0xCA )                                         /* fmul        st,st(2)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xD9,0x19 )                                         /* fstp        dword ptr [ecx]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x42,0x04 )                                    /* fld         dword ptr [edx+4]  */ \
_LINE2( 0xD8,0xE1 )                                         /* fsub        st,st(1)  */ \
_LINE2( 0xD8,0xCA )                                         /* fmul        st,st(2)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x59,0x04 )                                    /* fstp        dword ptr [ecx+4]  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD9,0x42,0x08 )                                    /* fld         dword ptr [edx+8]  */ \
_LINE2( 0xD8,0xE1 )                                         /* fsub        st,st(1)  */ \
_LINE2( 0xD8,0xCA )                                         /* fmul        st,st(2)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x59,0x08 )                                    /* fstp        dword ptr [ecx+8]  */ \
_LINE3( 0xD9,0x40,0x0C )                                    /* fld         dword ptr [eax+0Ch]  */ \
_LINE3( 0xD9,0x42,0x0C )                                    /* fld         dword ptr [edx+0Ch]  */ \
_LINE2( 0xD8,0xE1 )                                         /* fsub        st,st(1)  */ \
_LINE2( 0xD8,0xCA )                                         /* fmul        st,st(2)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x59,0x0C )                                    /* fstp        dword ptr [ecx+0Ch]  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

/// Интерполяция между четырехмерными векторами одинарной точности, команды 3DNOW
/// @brief for CPUTYPE2
#define VECTORP4DLERP3DNOW_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE3( 0x0F,0x6F,0x00 )                                    /* movq        mm0,mmword ptr [eax]  */ \
_LINE4( 0x0F,0x6F,0x50,0x08 )                               /* movq        mm2,mmword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x6F,0x0A )                                    /* movq        mm1,mmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE4( 0x0F,0x6F,0x5A,0x08 )                               /* movq        mm3,mmword ptr [edx+8]  */ \
_LINE5( 0x0F,0x6E,0x7C,0x24,0x10 )                          /* movd        mm7,dword ptr [esp+10h]  */ \
_LINE3( 0x0F,0x62,0xFF )                                    /* punpckldq   mm7,mm7  */ \
_LINE4( 0x0F,0x0F,0xC8,0xAA )                               /* pfsubr      mm1,mm0  */ \
_LINE4( 0x0F,0x0F,0xDA,0xAA )                               /* pfsubr      mm3,mm2  */ \
_LINE4( 0x0F,0x0F,0xCF,0xB4 )                               /* pfmul       mm1,mm7  */ \
_LINE4( 0x0F,0x0F,0xDF,0xB4 )                               /* pfmul       mm3,mm7  */ \
_LINE4( 0x0F,0x0F,0xC1,0x9E )                               /* pfadd       mm0,mm1  */ \
_LINE4( 0x0F,0x0F,0xD3,0x9E )                               /* pfadd       mm2,mm3  */ \
_LINE3( 0x0F,0x7F,0x01 )                                    /* movq        mmword ptr [ecx],mm0  */ \
_LINE4( 0x0F,0x7F,0x51,0x08 )                               /* movq        mmword ptr [ecx+8],mm2  */ \
_END_ASM

/// Интерполяция между четырехмерными векторами одинарной точности, команды SSE
/// @brief for CPUTYPE3
#define VECTORP4DLERPSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )                               /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x16,0x4A,0x08 )                               /* movhps      xmm1,qword ptr [edx+8]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE3( 0x0F,0x12,0x00 )                                    /* movlps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x12,0x0A )                                    /* movlps      xmm1,qword ptr [edx]  */ \
_LINE6( 0xF3,0x0F,0x10,0x64,0x24,0x10 )                     /* movss       xmm4,dword ptr [esp+10h]  */ \
_LINE3( 0x0F,0x5C,0xC8 )                                    /* subps       xmm1,xmm0  */ \
_LINE4( 0x0F,0xC6,0xE4,0x00 )                               /* shufps      xmm4,xmm4,0  */ \
_LINE3( 0x0F,0x59,0xCC )                                    /* mulps       xmm1,xmm4  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x01 )                                    /* movlps      qword ptr [ecx],xmm0  */ \
_LINE4( 0x0F,0x17,0x41,0x08 )                               /* movhps      qword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Интерполяция между четырехмерными векторами одинарной точности, команды SSE3
/// @brief for CPUTYPE3
#define VECTORP4DLERPSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE6( 0xF3,0x0F,0x10,0x64,0x24,0x10 )                     /* movss       xmm4,dword ptr [esp+10h]  */ \
_LINE3( 0x0F,0x5C,0xC8 )                                    /* subps       xmm1,xmm0  */ \
_LINE4( 0x0F,0xC6,0xE4,0x00 )                               /* shufps      xmm4,xmm4,0  */ \
_LINE3( 0x0F,0x59,0xCC )                                    /* mulps       xmm1,xmm4  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x01 )                                    /* movlps      qword ptr [ecx],xmm0  */ \
_LINE4( 0x0F,0x17,0x41,0x08 )                               /* movhps      qword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Интерполяция между четырехмерными векторами одинарной точности, команды SSE4
/// @brief for CPUTYPE4
#define VECTORP4DLERPSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE6( 0xF3,0x0F,0x10,0x64,0x24,0x10 )                     /* movss       xmm4,dword ptr [esp+10h]  */ \
_LINE3( 0x0F,0x5C,0xC8 )                                    /* subps       xmm1,xmm0  */ \
_LINE4( 0x0F,0xC6,0xE4,0x00 )                               /* shufps      xmm4,xmm4,0  */ \
_LINE3( 0x0F,0x59,0xCC )                                    /* mulps       xmm1,xmm4  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_END_ASM

/// Интерполяция между двухмерными векторами двойной точности, команды FPU
#define VECTORP2DDLERPFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xDD,0x44,0x24,0x10 )                               /* fld         qword ptr [esp+10h]  */ \
_LINE2( 0xDD,0x00 )                                         /* fld         qword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xDD,0x02 )                                         /* fld         qword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE2( 0xD8,0xE1 )                                         /* fsub        st,st(1)  */ \
_LINE2( 0xD8,0xCA )                                         /* fmul        st,st(2)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xDD,0x19 )                                         /* fstp        qword ptr [ecx]  */ \
_LINE3( 0xDD,0x40,0x08 )                                    /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDD,0x42,0x08 )                                    /* fld         qword ptr [edx+8]  */ \
_LINE2( 0xD8,0xE1 )                                         /* fsub        st,st(1)  */ \
_LINE2( 0xD8,0xCA )                                         /* fmul        st,st(2)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x59,0x08 )                                    /* fstp        qword ptr [ecx+8]  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

/// Интерполяция между четырехмерными векторами одинарной точности, команды SSE2
/// @brief for CPUTYPE3
#define VECTORP2DDLERPSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,qword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,qword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE5( 0x66,0x0F,0x16,0x40,0x08 )                          /* movhpd      xmm0,qword ptr [eax+8]  */ \
_LINE5( 0x66,0x0F,0x16,0x4A,0x08 )                          /* movhpd      xmm1,qword ptr [edx+8]  */ \
_LINE6( 0xF2,0x0F,0x10,0x64,0x24,0x10 )                     /* movsd       xmm4,qword ptr [esp+10h]  */ \
_LINE4( 0x66,0x0F,0x5C,0xC8 )                               /* subpd       xmm1,xmm0  */ \
_LINE4( 0x66,0x0F,0x14,0xE4 )                               /* unpcklpd    xmm4,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xCC )                               /* mulpd       xmm1,xmm4  */ \
_LINE4( 0x66,0x0F,0x58,0xC1 )                               /* addpd       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       qword ptr [ecx],xmm0  */ \
_LINE5( 0x66,0x0F,0x17,0x41,0x08 )                          /* movhpd      qword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Интерполяция между четырехмерными векторами одинарной точности, команды SSE3
/// @brief for CPUTYPE3
#define VECTORP2DDLERPSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE6( 0xF2,0x0F,0x12,0x64,0x24,0x10 )                     /* movddup     xmm4,mmword ptr [esp+10h]  */ \
_LINE4( 0x66,0x0F,0x5C,0xC8 )                               /* subpd       xmm1,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xCC )                               /* mulpd       xmm1,xmm4  */ \
_LINE4( 0x66,0x0F,0x58,0xC1 )                               /* addpd       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       qword ptr [ecx],xmm0  */ \
_LINE5( 0x66,0x0F,0x17,0x41,0x08 )                          /* movhpd      qword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Интерполяция между четырехмерными векторами одинарной точности, команды SSE4
/// @brief for CPUTYPE4
#define VECTORP2DDLERPSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE6( 0xF2,0x0F,0x12,0x64,0x24,0x10 )                     /* movddup     xmm4,mmword ptr [esp+10h]  */ \
_LINE4( 0x66,0x0F,0x5C,0xC8 )                               /* subpd       xmm1,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xCC )                               /* mulpd       xmm1,xmm4  */ \
_LINE4( 0x66,0x0F,0x58,0xC1 )                               /* addpd       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_END_ASM

/// Интерполяция между трехмерными векторами двойной точности, команды FPU
#define VECTORP3DDLERPFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xDD,0x44,0x24,0x10 )                               /* fld         qword ptr [esp+10h]  */ \
_LINE2( 0xDD,0x00 )                                         /* fld         qword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xDD,0x02 )                                         /* fld         qword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE2( 0xD8,0xE1 )                                         /* fsub        st,st(1)  */ \
_LINE2( 0xD8,0xCA )                                         /* fmul        st,st(2)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xDD,0x19 )                                         /* fstp        qword ptr [ecx]  */ \
_LINE3( 0xDD,0x40,0x08 )                                    /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDD,0x42,0x08 )                                    /* fld         qword ptr [edx+8]  */ \
_LINE2( 0xD8,0xE1 )                                         /* fsub        st,st(1)  */ \
_LINE2( 0xD8,0xCA )                                         /* fmul        st,st(2)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x59,0x08 )                                    /* fstp        qword ptr [ecx+8]  */ \
_LINE3( 0xDD,0x40,0x10 )                                    /* fld         qword ptr [eax+10h]  */ \
_LINE3( 0xDD,0x42,0x10 )                                    /* fld         qword ptr [edx+10h]  */ \
_LINE2( 0xD8,0xE1 )                                         /* fsub        st,st(1)  */ \
_LINE2( 0xD8,0xCA )                                         /* fmul        st,st(2)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x59,0x10 )                                    /* fstp        qword ptr [ecx+10h]  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

/// Интерполяция между трехмерными векторами одинарной точности, команды SSE2
/// @brief for CPUTYPE3
#define VECTORP3DDLERPSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,mmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x5A,0x10 )                          /* movsd       xmm3,mmword ptr [edx+10h]  */ \
_LINE5( 0x66,0x0F,0x16,0x40,0x08 )                          /* movhpd      xmm0,qword ptr [eax+8]  */ \
_LINE5( 0x66,0x0F,0x16,0x4A,0x08 )                          /* movhpd      xmm1,qword ptr [edx+8]  */ \
_LINE6( 0xF2,0x0F,0x10,0x64,0x24,0x10 )                     /* movsd       xmm4,mmword ptr [esp+10h]  */ \
_LINE4( 0xF2,0x0F,0x5C,0xDA )                               /* subsd       xmm3,xmm2  */ \
_LINE4( 0x66,0x0F,0x5C,0xC8 )                               /* subpd       xmm1,xmm0  */ \
_LINE4( 0x66,0x0F,0x14,0xE4 )                               /* unpcklpd    xmm4,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xCC )                               /* mulpd       xmm1,xmm4  */ \
_LINE4( 0xF2,0x0F,0x59,0xDC )                               /* mulsd       xmm3,xmm4  */ \
_LINE4( 0x66,0x0F,0x58,0xC1 )                               /* addpd       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x58,0xD3 )                               /* addsd       xmm2,xmm3  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0x66,0x0F,0x17,0x41,0x08 )                          /* movhpd      qword ptr [ecx+8],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_END_ASM

/// Интерполяция между трехмерными векторами одинарной точности, команды SSE3
/// @brief for CPUTYPE3
#define VECTORP3DDLERPSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x5A,0x10 )                          /* movsd       xmm3,mmword ptr [edx+10h]  */ \
_LINE6( 0xF2,0x0F,0x12,0x64,0x24,0x10 )                     /* movddup     xmm4,mmword ptr [esp+10h]  */ \
_LINE4( 0x66,0x0F,0x5C,0xC8 )                               /* subpd       xmm1,xmm0  */ \
_LINE4( 0xF2,0x0F,0x5C,0xDA )                               /* subsd       xmm3,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xCC )                               /* mulpd       xmm1,xmm4  */ \
_LINE4( 0xF2,0x0F,0x59,0xDC )                               /* mulsd       xmm3,xmm4  */ \
_LINE4( 0x66,0x0F,0x58,0xC1 )                               /* addpd       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x58,0xD3 )                               /* addsd       xmm2,xmm3  */ \
_LINE4( 0x66,0x0F,0x13,0x01 )                               /* movlpd      qword ptr [ecx],xmm0  */ \
_LINE5( 0x66,0x0F,0x17,0x41,0x08 )                          /* movhpd      qword ptr [ecx+8],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_END_ASM

/// Интерполяция между четырехмерными векторами двойной точности, команды FPU
#define VECTORP4DDLERPFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xDD,0x44,0x24,0x10 )                               /* fld         qword ptr [esp+10h]  */ \
_LINE2( 0xDD,0x00 )                                         /* fld         qword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xDD,0x02 )                                         /* fld         qword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE2( 0xD8,0xE1 )                                         /* fsub        st,st(1)  */ \
_LINE2( 0xD8,0xCA )                                         /* fmul        st,st(2)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xDD,0x19 )                                         /* fstp        qword ptr [ecx]  */ \
_LINE3( 0xDD,0x40,0x08 )                                    /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDD,0x42,0x08 )                                    /* fld         qword ptr [edx+8]  */ \
_LINE2( 0xD8,0xE1 )                                         /* fsub        st,st(1)  */ \
_LINE2( 0xD8,0xCA )                                         /* fmul        st,st(2)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x59,0x08 )                                    /* fstp        qword ptr [ecx+8]  */ \
_LINE3( 0xDD,0x40,0x10 )                                    /* fld         qword ptr [eax+10h]  */ \
_LINE3( 0xDD,0x42,0x10 )                                    /* fld         qword ptr [edx+10h]  */ \
_LINE2( 0xD8,0xE1 )                                         /* fsub        st,st(1)  */ \
_LINE2( 0xD8,0xCA )                                         /* fmul        st,st(2)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x59,0x10 )                                    /* fstp        qword ptr [ecx+10h]  */ \
_LINE3( 0xDD,0x40,0x18 )                                    /* fld         qword ptr [eax+18h]  */ \
_LINE3( 0xDD,0x42,0x18 )                                    /* fld         qword ptr [edx+18h]  */ \
_LINE2( 0xD8,0xE1 )                                         /* fsub        st,st(1)  */ \
_LINE2( 0xD8,0xCA )                                         /* fmul        st,st(2)  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x59,0x18 )                                    /* fstp        qword ptr [ecx+18h]  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0) */ \
_END_ASM

/// Интерполяция между четырехмерными векторами двойной точности, команды SSE2
#define VECTORP4DDLERPSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,mmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x5A,0x10 )                          /* movsd       xmm3,mmword ptr [edx+10h]  */ \
_LINE5( 0x66,0x0F,0x16,0x40,0x08 )                          /* movhpd      xmm0,qword ptr [eax+8]  */ \
_LINE5( 0x66,0x0F,0x16,0x4A,0x08 )                          /* movhpd      xmm1,qword ptr [edx+8]  */ \
_LINE5( 0x66,0x0F,0x16,0x50,0x18 )                          /* movhpd      xmm2,qword ptr [eax+18h]  */ \
_LINE5( 0x66,0x0F,0x16,0x5A,0x18 )                          /* movhpd      xmm3,qword ptr [edx+18h]  */ \
_LINE6( 0xF2,0x0F,0x10,0x64,0x24,0x10 )                     /* movsd       xmm4,mmword ptr [esp+10h]  */ \
_LINE4( 0x66,0x0F,0x14,0xE4 )                               /* unpcklpd    xmm4,xmm4  */ \
_LINE4( 0x66,0x0F,0x5C,0xC8 )                               /* subpd       xmm1,xmm0  */ \
_LINE4( 0x66,0x0F,0x5C,0xDA )                               /* subpd       xmm3,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xCC )                               /* mulpd       xmm1,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xDC )                               /* mulpd       xmm3,xmm4  */ \
_LINE4( 0x66,0x0F,0x58,0xC1 )                               /* addpd       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE4( 0x66,0x0F,0x58,0xD3 )                               /* addpd       xmm2,xmm3  */ \
_LINE5( 0x66,0x0F,0x17,0x41,0x08 )                          /* movhpd      qword ptr [ecx+8],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_LINE5( 0x66,0x0F,0x17,0x51,0x18 )                          /* movhpd      qword ptr [ecx+18h],xmm2  */ \
_END_ASM

/// Интерполяция между четырехмерными векторами двойной точности, команды SSE3
#define VECTORP4DDLERPSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x50,0x10 )                          /* lddqu       xmm2,xmmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x5A,0x10 )                          /* lddqu       xmm3,xmmword ptr [edx+10h]  */ \
_LINE6( 0xF2,0x0F,0x12,0x64,0x24,0x10 )                     /* movddup     xmm4,qword ptr [esp+10h]  */ \
_LINE4( 0x66,0x0F,0x5C,0xC8 )                               /* subpd       xmm1,xmm0  */ \
_LINE4( 0x66,0x0F,0x5C,0xDA )                               /* subpd       xmm3,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xCC )                               /* mulpd       xmm1,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xDC )                               /* mulpd       xmm3,xmm4  */ \
_LINE4( 0x66,0x0F,0x58,0xC1 )                               /* addpd       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE4( 0x66,0x0F,0x58,0xD3 )                               /* addpd       xmm2,xmm3  */ \
_LINE5( 0x66,0x0F,0x17,0x41,0x08 )                          /* movhpd      qword ptr [ecx+8],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_LINE5( 0x66,0x0F,0x17,0x51,0x18 )                          /* movhpd      qword ptr [ecx+18h],xmm2  */ \
_END_ASM

/// Интерполяция между четырехмерными векторами двойной точности, команды SSE4
#define VECTORP4DDLERPSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x50,0x10 )                          /* lddqu       xmm2,xmmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x5A,0x10 )                          /* lddqu       xmm3,xmmword ptr [edx+10h]  */ \
_LINE6( 0xF2,0x0F,0x12,0x64,0x24,0x10 )                     /* movddup     xmm4,qword ptr [esp+10h]  */ \
_LINE4( 0x66,0x0F,0x5C,0xC8 )                               /* subpd       xmm1,xmm0  */ \
_LINE4( 0x66,0x0F,0x5C,0xDA )                               /* subpd       xmm3,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xCC )                               /* mulpd       xmm1,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xDC )                               /* mulpd       xmm3,xmm4  */ \
_LINE4( 0x66,0x0F,0x58,0xC1 )                               /* addpd       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x58,0xD3 )                               /* addpd       xmm2,xmm3  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_LINE5( 0x66,0x0F,0x11,0x51,0x10 )                          /* movupd      xmmword ptr [ecx+10h],xmm2  */ \
_END_ASM

/// Интерполяция между четырехмерными векторами двойной точности, команды AVX ???
#define VECTORP4DDLERPAVX_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xC5,0xFD,0x10,0x00 )                /* vmovupd     ymm0,ymmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xC5,0xFD,0x10,0x0A )                /* vmovupd     ymm1,ymmword ptr [edx]  */ \
_LINE7( 0xC4,0xE2,0x7D,0x19,0x64,0x24,0x10 ) /* vbroadcastsd ymm4,qword ptr [esp+10h]  */ \
_LINE4( 0xC5,0xF5,0x5C,0xD8 )                /* vsubpd      ymm3,ymm1,ymm0  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                /* mov         eax,dword ptr [esp+12]  */ \
_LINE4( 0xC5,0xDD,0x59,0xDB )                /* vmulpd      ymm3,ymm4,ymm3  */ \
_LINE4( 0xC5,0xFD,0x58,0xDB )                /* vaddpd      ymm3,ymm0,ymm3  */ \
_LINE4( 0xC5,0xFD,0x11,0x18 )                /* vmovupd     ymmword ptr [eax],ymm3  */ \
_LINE3( 0xC5,0xF8,0x77 )                /* vzeroupper  */ \
_END_ASM

// *********************************** LERP REGISTERS FASTCALL **************************************
// vector interpolate eax-a void *, edx-b void *, eсx-rez void *, [esp+4]-c double/float

/// Интерполяция между двухмерными векторами одинарной точности, команды FPU
#define VECTORP2DLERPFPU \
BEGIN_ASM \
_ASM fld dword ptr [esp+4] \
_ASM fld dword ptr [eax] \
_ASM fld dword ptr [edx] \
_ASM fsub st(0),st(1) \
_ASM fmul st(0),st(2) \
_ASM faddp st(1),st(0) \
_ASM fstp dword ptr [ecx] \
_ASM fld dword ptr [eax+4] \
_ASM fld dword ptr [edx+4] \
_ASM fsub st(0), st(1) \
_ASM fmul st(0), st(2) \
_ASM faddp st(1),st(0) \
_ASM fstp dword ptr [ecx+4] \
_ASM fstp st(0) \
END_ASM

/// Интерполяция между двухмерными векторами одинарной точности, команды SSE
/// @brief for CPUTYPE3
#define VECTORP2DLERPSSE \
BEGIN_ASM \
_ASM movss xmm1,[eax+4] \
_ASM movss xmm3,[edx+4] \
_ASM movss xmm0,[eax] \
_ASM movss xmm2,[edx] \
_ASM movss xmm4,[esp+4] \
_ASM subss xmm2,xmm0 \
_ASM subss xmm3,xmm1 \
_ASM mulss xmm2,xmm4 \
_ASM mulss xmm3,xmm4 \
_ASM addss xmm0,xmm2 \
_ASM addss xmm1,xmm3 \
_ASM movss [ecx],xmm0 \
_ASM movss [ecx+4],xmm1 \
END_ASM

/// Интерполяция между двухмерными векторами одинарной точности, команды SSE2
/// @brief for CPUTYPE3
#define VECTORP2DLERPSSE2 \
BEGIN_ASM \
_ASM movsd xmm0,[eax] \
_ASM movsd xmm1,[edx] \
_ASM movss xmm4,[esp+4] \
_ASM subps xmm1,xmm0 \
_ASM shufps xmm4,xmm4,0 \
_ASM mulps xmm1,xmm4 \
_ASM addps xmm0,xmm1 \
_ASM movsd [ecx],xmm0 \
END_ASM

/// Интерполяция между трехмерными векторами одинарной точности, команды FPU
#define VECTORP3DLERPFPU \
BEGIN_ASM \
_ASM fld dword ptr [esp+4] \
_ASM fld dword ptr [eax] \
_ASM fld dword ptr [edx] \
_ASM fsub st(0),st(1) \
_ASM fmul st(0),st(2) \
_ASM faddp st(1),st(0) \
_ASM fstp dword ptr [ecx] \
_ASM fld dword ptr [eax+4] \
_ASM fld dword ptr [edx+4] \
_ASM fsub st,st(1) \
_ASM fmul st,st(2) \
_ASM faddp st(1),st(0) \
_ASM fstp dword ptr [ecx+4] \
_ASM fld dword ptr [eax+8] \
_ASM fld dword ptr [edx+8] \
_ASM fsub st,st(1) \
_ASM fmul st,st(2) \
_ASM faddp st(1),st(0) \
_ASM fstp dword ptr [ecx+8] \
_ASM fstp st(0) \
END_ASM

/// Интерполяция между трехмерными векторами одинарной точности, команды SSE
/// @brief for CPUTYPE3
#define VECTORP3DLERPSSE \
BEGIN_ASM \
_ASM movss xmm0,[eax+8] \
_ASM movss xmm1,[edx+8] \
_ASM movhps xmm0,[eax] \
_ASM movhps xmm1,[edx] \
_ASM movss xmm4,[esp+4] \
_ASM subps xmm1,xmm0 \
_ASM shufps xmm4,xmm4,0 \
_ASM mulps xmm1,xmm4 \
_ASM addps xmm0,xmm1 \
_ASM movhps [ecx],xmm0 \
_ASM movss [ecx+8],xmm0 \
END_ASM

/// Интерполяция между четырехмерными векторами одинарной точности, команды FPU
/// @brief for CPUTYPE1
#define VECTORP4DLERPFPU \
BEGIN_ASM \
_ASM fld dword ptr [esp+4] \
_ASM fld dword ptr [eax] \
_ASM fld dword ptr [edx] \
_ASM fsub st, st(1) \
_ASM fmul st, st(2) \
_ASM faddp st(1),st(0) \
_ASM fstp dword ptr [ecx] \
_ASM fld dword ptr [eax+4] \
_ASM fld dword ptr [edx+4] \
_ASM fsub st, st(1) \
_ASM fmul st, st(2) \
_ASM faddp st(1),st(0) \
_ASM fstp dword ptr [ecx+4] \
_ASM fld dword ptr [eax+8] \
_ASM fld dword ptr [edx+8] \
_ASM fsub st, st(1) \
_ASM fmul st, st(2) \
_ASM faddp st(1),st(0) \
_ASM fstp dword ptr [ecx+8] \
_ASM fld dword ptr [eax+12] \
_ASM fld dword ptr [edx+12] \
_ASM fsub st, st(1) \
_ASM fmul st, st(2) \
_ASM faddp st(1),st(0) \
_ASM fstp dword ptr [ecx+12] \
_ASM fstp st(0) \
END_ASM

/// Интерполяция между четырехмерными векторами одинарной точности, команды 3DNOW
/// @brief for CPUTYPE2
#define VECTORP4DLERP3DNOW \
BEGIN_ASM \
_ASM movq mm0, [eax] \
_ASM movq mm2, [eax+8] \
_ASM movq mm1, [edx] \
_ASM movq mm3, [edx+8] \
_ASM movd mm7, [esp+4] \
_ASM punpckldq mm7, mm7 \
_ASM pfsubr mm1, mm0 \
_ASM pfsubr mm3, mm2 \
_ASM pfmul mm1, mm7 \
_ASM pfmul mm3, mm7 \
_ASM pfadd mm0, mm1 \
_ASM pfadd mm2, mm3 \
_ASM movq [ecx], mm0 \
_ASM movq [ecx+8], mm2 \
END_ASM

/// Интерполяция между четырехмерными векторами одинарной точности, команды SSE
/// @brief for CPUTYPE3
#define VECTORP4DLERPSSE \
BEGIN_ASM \
_ASM movhps xmm0,[eax+8] \
_ASM movhps xmm1,[edx+8] \
_ASM movlps xmm0,[eax] \
_ASM movlps xmm1,[edx] \
_ASM movss xmm4,[esp+4] \
_ASM subps xmm1,xmm0 \
_ASM shufps xmm4,xmm4,0 \
_ASM mulps xmm1,xmm4 \
_ASM addps xmm0,xmm1 \
_ASM movlps [ecx],xmm0 \
_ASM movhps [ecx+8],xmm0 \
END_ASM

/// Интерполяция между двухмерными векторами двойной точности, команды FPU
#define VECTORP2DDLERPFPU \
BEGIN_ASM \
_ASM fld   qword ptr [esp+4] \
_ASM fld   qword ptr [eax] \
_ASM fld   qword ptr [edx] \
_ASM fsub  st, st(1) \
_ASM fmul  st, st(2) \
_ASM faddp st(1),st(0) \
_ASM fstp  qword ptr [ecx] \
_ASM fld   qword ptr [eax+4] \
_ASM fld   qword ptr [edx+4] \
_ASM fsub  st, st(1) \
_ASM fmul  st, st(2) \
_ASM faddp st(1),st(0) \
_ASM fstp  qword ptr [ecx+4] \
_ASM fstp st(0) \
END_ASM

/// Интерполяция между четырехмерными векторами одинарной точности, команды SSE2
/// @brief for CPUTYPE3
#define VECTORP2DDLERPSSE2 \
BEGIN_ASM \
_ASM movsd xmm0,[eax] \
_ASM movsd xmm1,[edx] \
_ASM movhpd xmm0,[eax+8] \
_ASM movhpd xmm1,[edx+8] \
_ASM movsd xmm4,[esp+4] \
_ASM subpd xmm1,xmm0 \
_ASM unpcklpd xmm4,xmm4 \
_ASM mulpd xmm1,xmm4 \
_ASM addpd xmm0,xmm1 \
_ASM movsd [ecx],xmm0 \
_ASM movhpd [ecx+8],xmm0 \
END_ASM

/// Интерполяция между трехмерными векторами двойной точности, команды FPU
#define VECTORP3DDLERPFPU \
BEGIN_ASM \
_ASM fld   qword ptr [esp+4] \
_ASM fld   qword ptr [eax] \
_ASM fld   qword ptr [edx] \
_ASM fsub  st, st(1) \
_ASM fmul  st, st(2) \
_ASM faddp st(1),st(0) \
_ASM fstp  qword ptr [ecx] \
_ASM fld   qword ptr [eax+8] \
_ASM fld   qword ptr [edx+8] \
_ASM fsub  st, st(1) \
_ASM fmul  st, st(2) \
_ASM faddp st(1),st(0) \
_ASM fstp  qword ptr [ecx+8] \
_ASM fld   qword ptr [eax+0x10] \
_ASM fld   qword ptr [edx+0x10] \
_ASM fsub  st, st(1) \
_ASM fmul  st, st(2) \
_ASM faddp st(1),st(0) \
_ASM fstp  qword ptr [ecx+0x10] \
_ASM fstp st(0) \
END_ASM

/// Интерполяция между трехмерными векторами одинарной точности, команды SSE2
/// @brief for CPUTYPE3
#define VECTORP3DDLERPSSE2 \
BEGIN_ASM \
_ASM movsd xmm0,[eax] \
_ASM movsd xmm1,[edx] \
_ASM movsd xmm2,[eax+16] \
_ASM movsd xmm3,[edx+16] \
_ASM movhpd xmm0,[eax+8] \
_ASM movhpd xmm1,[edx+8] \
_ASM movsd xmm4,[esp+4] \
_ASM subsd xmm3,xmm2 \
_ASM subpd xmm1,xmm0 \
_ASM unpcklpd xmm4,xmm4 \
_ASM mulpd xmm1,xmm4 \
_ASM mulsd xmm3,xmm4 \
_ASM addpd xmm0,xmm1 \
_ASM addsd xmm2,xmm3 \
_ASM movsd [ecx],xmm0 \
_ASM movhpd [ecx+8],xmm0 \
_ASM movsd [ecx+16],xmm2 \
END_ASM

/// Интерполяция между трехмерными векторами одинарной точности, команды SSE2
/// @brief for CPUTYPE3
#define VECTORP3DDLERPSSE3 \
BEGIN_ASM \
_ASM lddqu xmm0,[eax] \
_ASM lddqu xmm1,[edx] \
_ASM movsd xmm2,[eax+16] \
_ASM movsd xmm3,[edx+16] \
_ASM movddup xmm4,[esp+4] \
_ASM subsd xmm3,xmm2 \
_ASM subpd xmm1,xmm0 \
_ASM mulpd xmm1,xmm4 \
_ASM mulsd xmm3,xmm4 \
_ASM addpd xmm0,xmm1 \
_ASM addsd xmm2,xmm3 \
_ASM movlpd [ecx],xmm0 \
_ASM movhpd [ecx+8],xmm0 \
_ASM movsd [ecx+16],xmm2 \
END_ASM

/// Интерполяция между четырехмерными векторами двойной точности, команды FPU
#define VECTORP4DDLERPFPU \
BEGIN_ASM \
_ASM fld   qword ptr [esp+4] \
_ASM fld   qword ptr [eax] \
_ASM fld   qword ptr [edx] \
_ASM fsub  st, st(1) \
_ASM fmul  st, st(2) \
_ASM faddp st(1),st(0) \
_ASM fstp  qword ptr [ecx] \
_ASM fld   qword ptr [eax+8] \
_ASM fld   qword ptr [edx+8] \
_ASM fsub  st, st(1) \
_ASM fmul  st, st(2) \
_ASM faddp st(1),st(0) \
_ASM fstp  qword ptr [ecx+8] \
_ASM fld   qword ptr [eax+0x10] \
_ASM fld   qword ptr [edx+0x10] \
_ASM fsub  st, st(1) \
_ASM fmul  st, st(2) \
_ASM faddp st(1),st(0) \
_ASM fstp  qword ptr [ecx+0x10] \
_ASM fld   qword ptr [eax+0x18] \
_ASM fld   qword ptr [edx+0x18] \
_ASM fsub  st, st(1) \
_ASM fmul  st, st(2) \
_ASM faddp st(1),st(0) \
_ASM fstp  qword ptr [ecx+0x18] \
_ASM fstp st(0) \
END_ASM

/// Интерполяция между четырехмерными векторами двойной точности, команды SSE2
#define VECTORP4DDLERPSSE2 \
BEGIN_ASM \
_ASM movsd xmm0,[eax] \
_ASM movsd xmm1,[edx] \
_ASM movsd xmm2,[eax+16] \
_ASM movsd xmm3,[edx+16] \
_ASM movhpd xmm0,[eax+8] \
_ASM movhpd xmm1,[edx+8] \
_ASM movhpd xmm2,[eax+24] \
_ASM movhpd xmm3,[edx+24] \
_ASM movsd xmm4,[esp+4] \
_ASM unpcklpd xmm4,xmm4 \
_ASM subpd xmm1,xmm0 \
_ASM subpd xmm3,xmm2 \
_ASM mulpd xmm1,xmm4 \
_ASM mulpd xmm3,xmm4 \
_ASM addpd xmm0,xmm1 \
_ASM movsd [ecx],xmm0 \
_ASM addpd xmm2,xmm3 \
_ASM movhpd [ecx+8],xmm0 \
_ASM movsd [ecx+16],xmm2 \
_ASM movhpd [ecx+24],xmm2 \
END_ASM

