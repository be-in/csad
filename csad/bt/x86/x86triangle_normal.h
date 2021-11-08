//=============================================================================
///**
// *  @file triangle_normal.h
// *
// *  $Id: triangle_normal.h 17.08.2011  $
// *
// *  @brief generator 3, MS Visual C++ 2003-2008
// *
// *  @author Panteleym_onov Aleks_andr Konstantino_vich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_TRANGLE_NORMAL_H
#define GEN3_TRANGLE_NORMAL_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** TRIANGLE NORMAL STDCALL *********************************
// triangle Normal [eax]-a void * [edx]-b void * rez

/// ¬ычисление нормали дл€ трехмерного вектора одинарной точности, команды FPU
#define TRIANGLEP3DADDNORMALFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x4C,0x24,0x04 )        /* mov         ecx,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )        /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xD9,0x02 )              /* fld         dword ptr [edx]  */ \
_LINE2( 0xD8,0x21 )              /* fsub        dword ptr [ecx]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )        /* mov         eax,dword ptr [esp+Ch]  */ \
_LINE3( 0xD9,0x42,0x04 )           /* fld         dword ptr [edx+4]  */ \
_LINE3( 0xD8,0x61,0x04 )           /* fsub        dword ptr [ecx+4]  */ \
_LINE3( 0xD9,0x42,0x08 )           /* fld         dword ptr [edx+8]  */ \
_LINE3( 0xD8,0x61,0x08 )           /* fsub        dword ptr [ecx+8]  */ \
_LINE2( 0xD9,0x00 )              /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0x21 )              /* fsub        dword ptr [ecx]  */ \
_LINE3( 0xD9,0x40,0x04 )           /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x61,0x04 )           /* fsub        dword ptr [ecx+4]  */ \
_LINE3( 0xD9,0x40,0x08 )           /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD8,0x61,0x08 )           /* fsub        dword ptr [ecx+8]  */ \
_LINE2( 0xD9,0xC0 )              /* fld         st(0)  */ \
_LINE2( 0xD8,0xCD )              /* fmul        st,st(5)  */ \
_LINE2( 0xD9,0xC2 )              /* fld         st(2)  */ \
_LINE2( 0xD8,0xCD )              /* fmul        st,st(5)  */ \
_LINE2( 0xDE,0xE9 )              /* fsubp       st(1),st  */ \
_LINE2( 0xD9,0xC3 )              /* fld         st(3)  */ \
_LINE2( 0xDE,0xCD )              /* fmulp       st(5),st  */ \
_LINE2( 0xD9,0xC9 )              /* fxch        st(1)  */ \
_LINE2( 0xD8,0xCE )              /* fmul        st,st(6)  */ \
_LINE2( 0xDE,0xEC )              /* fsubp       st(4),st  */ \
_LINE2( 0xD9,0xC9 )              /* fxch        st(1)  */ \
_LINE2( 0xDE,0xCD )              /* fmulp       st(5),st  */ \
_LINE2( 0xD9,0xC9 )              /* fxch        st(1)  */ \
_LINE2( 0xDE,0xCB )              /* fmulp       st(3),st  */ \
_LINE2( 0xD9,0xCB )              /* fxch        st(3)  */ \
_LINE2( 0xDE,0xE2 )              /* fsubrp      st(2),st  */ \
_LINE2( 0xD9,0xC0 )              /* fld         st(0)  */ \
_LINE2( 0xD8,0xC9 )              /* fmul        st,st(1)  */ \
_LINE2( 0xD9,0xC3 )              /* fld         st(3)  */ \
_LINE2( 0xD8,0xCC )              /* fmul        st,st(4)  */ \
_LINE2( 0xDE,0xC1 )              /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xC2 )              /* fld         st(2)  */ \
_LINE2( 0xD8,0xCB )              /* fmul        st,st(3)  */ \
_LINE2( 0xDE,0xC1 )              /* faddp       st(1),st  */ \
_LINE4( 0x8B,0x44,0x24,0x10 )        /* mov         eax,dword ptr [esp+10h]  */ \
_LINE2( 0xD9,0xFA )              /* fsqrt  */ \
_LINE2( 0xD9,0xE8 )              /* fld1  */ \
_LINE2( 0xDE,0xF1 )              /* fdivrp      st(1),st  */ \
_LINE2( 0xDC,0xCB )              /* fmul        st(3),st  */ \
_LINE2( 0xDC,0xC9 )              /* fmul        st(1),st  */ \
_LINE2( 0xDE,0xCA )              /* fmulp       st(2),st  */ \
_LINE3( 0xD9,0x04,0x01 )           /* fld         dword ptr [ecx+eax]  */ \
_LINE2( 0xD8,0xC3 )              /* fadd        st,st(3)  */ \
_LINE3( 0xD9,0x1C,0x01 )           /* fstp        dword ptr [ecx+eax]  */ \
_LINE4( 0xD9,0x44,0x01,0x04 )        /* fld         dword ptr [ecx+eax+4]  */ \
_LINE2( 0xD8,0xC1 )              /* fadd        st,st(1)  */ \
_LINE4( 0xD9,0x5C,0x01,0x04 )        /* fstp        dword ptr [ecx+eax+4]  */ \
_LINE4( 0x8D,0x4C,0x01,0x08 )        /* lea         ecx,[ecx+eax+8]  */ \
_LINE2( 0xD9,0x01 )              /* fld         dword ptr [ecx]  */ \
_LINE2( 0xD8,0xC2 )              /* fadd        st,st(2)  */ \
_LINE2( 0xD9,0x19 )              /* fstp        dword ptr [ecx]  */ \
_LINE4( 0x8D,0x4C,0x02,0x08 )        /* lea         ecx,[edx+eax+8]  */ \
_LINE2( 0xD9,0xC2 )              /* fld         st(2)  */ \
_LINE3( 0xD8,0x04,0x02 )           /* fadd        dword ptr [edx+eax]  */ \
_LINE3( 0xD9,0x1C,0x02 )           /* fstp        dword ptr [edx+eax]  */ \
_LINE4( 0xD9,0x44,0x02,0x04 )        /* fld         dword ptr [edx+eax+4]  */ \
_LINE2( 0xD8,0xC1 )              /* fadd        st,st(1)  */ \
_LINE4( 0xD9,0x5C,0x02,0x04 )        /* fstp        dword ptr [edx+eax+4]  */ \
_LINE2( 0xD9,0x01 )              /* fld         dword ptr [ecx]  */ \
_LINE2( 0xD8,0xC2 )              /* fadd        st,st(2)  */ \
ASM( add eax,[esp+12] ) \
_LINE2( 0xD9,0x19 )              /* fstp        dword ptr [ecx]  */ \
_LINE2( 0xD9,0x00 )              /* fld         dword ptr [eax]  */ \
_LINE2( 0xDE,0xC3 )              /* faddp       st(3),st  */ \
_LINE2( 0xD9,0xCA )              /* fxch        st(2)  */ \
_LINE2( 0xD9,0x18 )              /* fstp        dword ptr [eax]  */ \
_LINE3( 0xD9,0x40,0x04 )           /* fld         dword ptr [eax+4]  */ \
_LINE2( 0xDE,0xC2 )              /* faddp       st(2),st  */ \
_LINE2( 0xD9,0xC9 )              /* fxch        st(1)  */ \
_LINE3( 0xD9,0x58,0x04 )              /* fstp        dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x40,0x08 )              /* fadd        dword ptr [eax+8]  */ \
_LINE3( 0xD9,0x58,0x08 )              /* fstp        dword ptr [eax+8]  */ \
_END_ASM

/// ¬ычисление нормали дл€ трехмерного вектора одинарной точности, команды SSE
#define TRIANGLEP3DADDNORMALSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x60,0x08 )                          /* movss       xmm4,dword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x42,0x08 )                          /* movss       xmm0,dword ptr [edx+8]  */ \
_LINE3( 0x0F,0x16,0x20 )                                    /* movhps      xmm4,qword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE5( 0xF3,0x0F,0x10,0x49,0x08 )                          /* movss       xmm1,dword ptr [ecx+8]  */ \
_LINE3( 0x0F,0x16,0x02 )                                    /* movhps      xmm0,qword ptr [edx]  */ \
_LINE3( 0x0F,0x16,0x09 )                                    /* movhps      xmm1,qword ptr [ecx]  */ \
ASM( subps xmm0,xmm4 ) \
ASM( subps xmm1,xmm4 ) \
_LINE3( 0x0F,0x28,0xD0 )                                    /* movaps      xmm2,xmm0  */ \
_LINE3( 0x0F,0x28,0xD9 )                                    /* movaps      xmm3,xmm1  */ \
ASM( mov eax,[esp+16] ) \
_LINE4( 0x0F,0xC6,0xC0,0x32 )                               /* shufps      xmm0,xmm0,32h  */ \
_LINE4( 0x0F,0xC6,0xC9,0x83 )                               /* shufps      xmm1,xmm1,83h  */ \
_LINE4( 0x0F,0xC6,0xD2,0x83 )                               /* shufps      xmm2,xmm2,83h  */ \
_LINE4( 0x0F,0xC6,0xDB,0x32 )                               /* shufps      xmm3,xmm3,32h  */ \
ASM( add ecx,eax ) \
_LINE3( 0x0F,0x59,0xC1 )                                    /* mulps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x59,0xD3 )                                    /* mulps       xmm2,xmm3  */ \
ASM( add edx,eax ) \
_LINE3( 0x0F,0x5C,0xC2 )                                    /* subps       xmm0,xmm2  */ \
ASM( add eax,[esp+4] ) \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x59,0xC9 )                                    /* mulps       xmm1,xmm1  */ \
_LINE3( 0x0F,0x28,0xD1 )                                    /* movaps      xmm2,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC9,0x0E )                               /* shufps      xmm1,xmm1,0Eh  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC9,0x01 )                               /* shufps      xmm1,xmm1,1  */ \
_LINE4( 0xF3,0x0F,0x58,0xD1 )                               /* addss       xmm2,xmm1  */ \
_LINE4( 0xF3,0x0F,0x51,0xD2 )                               /* sqrtss      xmm2,xmm2  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x5E,0xC2 )                                    /* divps       xmm0,xmm2  */ \
_LINE5( 0xF3,0x0F,0x10,0x61,0x08 )                          /* movss       xmm4,dword ptr [ecx+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x6A,0x08 )                          /* movss       xmm5,dword ptr [edx+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x70,0x08 )                          /* movss       xmm6,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x21 )                                    /* movhps      xmm4,qword ptr [ecx]  */ \
_LINE3( 0x0F,0x16,0x2A )                                    /* movhps      xmm5,qword ptr [edx]  */ \
_LINE3( 0x0F,0x16,0x30 )                                    /* movhps      xmm6,qword ptr [eax]  */ \
ASM( addps xmm4,xmm0 ) \
ASM( addps xmm5,xmm0 ) \
ASM( addps xmm6,xmm0 ) \
_LINE3( 0x0F,0x17,0x21 )                                    /* movhps      qword ptr [ecx],xmm4  */ \
_LINE3( 0x0F,0x17,0x2A )                                    /* movhps      qword ptr [edx],xmm5  */ \
_LINE3( 0x0F,0x17,0x30 )                                    /* movhps      qword ptr [eax],xmm6  */ \
_LINE5( 0xF3,0x0F,0x11,0x61,0x08 )                          /* movss       dword ptr [ecx+8],xmm4  */ \
_LINE5( 0xF3,0x0F,0x11,0x6A,0x08 )                          /* movss       dword ptr [edx+8],xmm5  */ \
_LINE5( 0xF3,0x0F,0x11,0x70,0x08 )                          /* movss       dword ptr [eax+8],xmm6  */ \
_END_ASM

/// ¬ычисление нормали дл€ трехмерного вектора двойной точности, команды FPU
#define TRIANGLEP3DADD3DDNORMALFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x0C )                               /* mov         edx,dword ptr [esp+12]  */ \
_LINE3( 0xDD,0x42,0x10 )                                    /* fld         qword ptr [edx+10h]  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
ASM( fsub qword ptr [eax+8] ) \
_LINE3( 0xDD,0x42,0x08 )                                    /* fld         qword ptr [edx+8]  */ \
ASM( fsub qword ptr [eax+4] ) \
_LINE2( 0xDD,0x02 )                                         /* fld         qword ptr [edx]  */ \
ASM( fsub qword ptr [eax] ) \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0xDD,0x42,0x10 )                                    /* fld         qword ptr [edx+10h]  */ \
ASM( fsub qword ptr [eax+8] ) \
_LINE3( 0xDD,0x42,0x08 )                                    /* fld         qword ptr [edx+8]  */ \
ASM( fsub qword ptr [eax+4] ) \
_LINE2( 0xDD,0x02 )                                         /* fld         qword ptr [edx]  */ \
ASM( fsub qword ptr [eax] ) \
_LINE2( 0xD9,0xC1 )                                         /* fld         st(1)  */ \
_LINE2( 0xD8,0xCE )                                         /* fmul        st,st(6)  */ \
_LINE2( 0xD9,0xC3 )                                         /* fld         st(3)  */ \
_LINE2( 0xD8,0xCE )                                         /* fmul        st,st(6)  */ \
_LINE2( 0xDE,0xE9 )                                         /* fsubp       st(1),st  */ \
ASM( fstp qword ptr [esp-28] ) \
_LINE2( 0xD9,0xC2 )                                         /* fld         st(2)  */ \
_LINE2( 0xD8,0xCC )                                         /* fmul        st,st(4)  */ \
_LINE2( 0xD9,0xC1 )                                         /* fld         st(1)  */ \
_LINE2( 0xD8,0xCF )                                         /* fmul        st,st(7)  */ \
_LINE2( 0xDE,0xE9 )                                         /* fsubp       st(1),st  */ \
ASM( fstp qword ptr [esp-20] ) \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xD9,0xC2 )                                         /* fld         st(2)  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xDE,0xE9 )                                         /* fsubp       st(1),st  */ \
ASM( fstp qword ptr [esp-12] ) \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
ASM( fld qword ptr [esp-12] ) \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
ASM( fld qword ptr [esp-20] ) \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
ASM( fld qword ptr [esp-28] ) \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
ASM( mov edx,[esp+16] ) \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xFA )                                         /* fsqrt             */ \
_LINE2( 0xD9,0xE8 )                                         /* fld1              */ \
_LINE2( 0xDE,0xF1 )                                         /* fdivrp      st(1),st  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0x03,0xC2 )                                         /* add         eax,edx  */ \
ASM( fld qword ptr [esp-28] ) \
ASM( fmulp st(1),st(0) ) \
ASM( fld qword ptr [esp-20] ) \
ASM( fmulp st(2),st(0) ) \
ASM( fld qword ptr [esp-12] ) \
_LINE2( 0xDE,0xCB )                                         /* fmulp       st(3),st  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0xC1 )                                         /* fadd        st,st(1)  */ \
_LINE2( 0xD9,0x18 )                                         /* fstp        dword ptr [eax]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE2( 0xD8,0xC2 )                                         /* fadd        st,st(2)  */ \
_LINE3( 0xD9,0x58,0x04 )                                    /* fstp        dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE2( 0xD8,0xC3 )                                         /* fadd        st,st(3)  */ \
_LINE3( 0xD9,0x58,0x08 )                                    /* fstp        dword ptr [eax+8]  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8]  */ \
_LINE2( 0x03,0xC2 )                                         /* add         eax,edx  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0xC1 )                                         /* fadd        st,st(1)  */ \
_LINE2( 0xD9,0x18 )                                         /* fstp        dword ptr [eax]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE2( 0xD8,0xC2 )                                         /* fadd        st,st(2)  */ \
_LINE3( 0xD9,0x58,0x04 )                                    /* fstp        dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE2( 0xD8,0xC3 )                                         /* fadd        st,st(3)  */ \
_LINE3( 0xD9,0x58,0x08 )                                    /* fstp        dword ptr [eax+8]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+12]  */ \
_LINE2( 0x03,0xC2 )                                         /* add         eax,edx  */ \
_LINE2( 0xD8,0x00 )                                         /* fadd        dword ptr [eax]  */ \
_LINE2( 0xD9,0x18 )                                         /* fstp        dword ptr [eax]  */ \
_LINE3( 0xD8,0x40,0x04 )                                    /* fadd        dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x58,0x04 )                                    /* fstp        dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x40,0x08 )                                    /* fadd        dword ptr [eax+8]  */ \
_LINE3( 0xD9,0x58,0x08 )                                    /* fstp        dword ptr [eax+8]  */ \
_END_ASM

/// ¬ычисление нормали дл€ трехмерного вектора двойной точности, команды FPU
#define TRIANGLEP3DDADDNORMALFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x0C )                               /* mov         edx,dword ptr [esp+12]  */ \
_LINE3( 0xDD,0x42,0x10 )                                    /* fld         qword ptr [edx+10h]  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
ASM( fsub qword ptr [eax+8] ) \
_LINE3( 0xDD,0x42,0x08 )                                    /* fld         qword ptr [edx+8]  */ \
ASM( fsub qword ptr [eax+4] ) \
_LINE2( 0xDD,0x02 )                                         /* fld         qword ptr [edx]  */ \
ASM( fsub qword ptr [eax] ) \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0xDD,0x42,0x10 )                                    /* fld         qword ptr [edx+10h]  */ \
ASM( fsub qword ptr [eax+8] ) \
_LINE3( 0xDD,0x42,0x08 )                                    /* fld         qword ptr [edx+8]  */ \
ASM( fsub qword ptr [eax+4] ) \
_LINE2( 0xDD,0x02 )                                         /* fld         qword ptr [edx]  */ \
ASM( fsub qword ptr [eax] ) \
_LINE2( 0xD9,0xC1 )                                         /* fld         st(1)  */ \
_LINE2( 0xD8,0xCE )                                         /* fmul        st,st(6)  */ \
_LINE2( 0xD9,0xC3 )                                         /* fld         st(3)  */ \
_LINE2( 0xD8,0xCE )                                         /* fmul        st,st(6)  */ \
_LINE2( 0xDE,0xE9 )                                         /* fsubp       st(1),st  */ \
ASM( fstp qword ptr [esp-28] ) \
_LINE2( 0xD9,0xC2 )                                         /* fld         st(2)  */ \
_LINE2( 0xD8,0xCC )                                         /* fmul        st,st(4)  */ \
_LINE2( 0xD9,0xC1 )                                         /* fld         st(1)  */ \
_LINE2( 0xD8,0xCF )                                         /* fmul        st,st(7)  */ \
_LINE2( 0xDE,0xE9 )                                         /* fsubp       st(1),st  */ \
ASM( fstp qword ptr [esp-20] ) \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xD9,0xC2 )                                         /* fld         st(2)  */ \
_LINE2( 0xD8,0xCD )                                         /* fmul        st,st(5)  */ \
_LINE2( 0xDE,0xE9 )                                         /* fsubp       st(1),st  */ \
ASM( fstp qword ptr [esp-12] ) \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
ASM( fld qword ptr [esp-12] ) \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
ASM( fld qword ptr [esp-20] ) \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
ASM( fld qword ptr [esp-28] ) \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
ASM( mov edx,[esp+16] ) \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xFA )                                         /* fsqrt             */ \
_LINE2( 0xD9,0xE8 )                                         /* fld1              */ \
_LINE2( 0xDE,0xF1 )                                         /* fdivrp      st(1),st  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0x03,0xC2 )                                         /* add         eax,edx  */ \
ASM( fld qword ptr [esp-28] ) \
ASM( fmulp st(1),st(0) ) \
ASM( fld qword ptr [esp-20] ) \
ASM( fmulp st(2),st(0) ) \
ASM( fld qword ptr [esp-12] ) \
ASM( fmulp st(3),st(0) ) \
ASM( fld qword ptr [eax] ) \
ASM( fadd st(0),st(1) ) \
ASM( fstp qword ptr [eax] ) \
ASM( fld qword ptr [eax+8] ) \
ASM( fadd st(0),st(2) ) \
ASM( fstp qword ptr [eax+8] ) \
ASM( fld qword ptr [eax+16] ) \
ASM( fadd st(0),st(3) ) \
ASM( fstp qword ptr [eax+16] ) \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8]  */ \
_LINE2( 0x03,0xC2 )                                         /* add         eax,edx  */ \
ASM( fld qword ptr [eax] ) \
ASM( fadd st(0),st(1) ) \
ASM( fstp qword ptr [eax] ) \
ASM( fld qword ptr [eax+8] ) \
ASM( fadd st(0),st(2) ) \
ASM( fstp qword ptr [eax+8] ) \
ASM( fld qword ptr [eax+16] ) \
ASM( fadd st(0),st(3) ) \
ASM( fstp qword ptr [eax+16] ) \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+12]  */ \
_LINE2( 0x03,0xC2 )                                         /* add         eax,edx  */ \
ASM( fadd qword ptr [eax] ) \
ASM( fstp qword ptr [eax] ) \
ASM( fadd qword ptr [eax+8] ) \
ASM( fstp qword ptr [eax+8] ) \
ASM( fadd qword ptr [eax+16] ) \
ASM( fstp qword ptr [eax+16] ) \
_END_ASM

/// ¬ычисление нормали дл€ трехмерного вектора двойной точности, команды SSE2
#define TRIANGLEP3DDADDNORMALSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x0F,0x12,0x60,0x10 )                               /* movlps      xmm4,qword ptr [eax+10h]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x12,0x68,0x08 )                               /* movlps      xmm5,qword ptr [eax+8]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+12]  */ \
_LINE3( 0x0F,0x16,0x1A )                                    /* movhps      xmm3,qword ptr [edx]  */ \
_LINE3( 0x0F,0x16,0x28 )                                    /* movhps      xmm5,qword ptr [eax]  */ \
_LINE4( 0x0F,0x12,0x51,0x08 )                               /* movlps      xmm2,qword ptr [ecx+8]  */ \
_LINE4( 0x0F,0x12,0x4A,0x10 )                               /* movlps      xmm1,qword ptr [edx+10h]  */ \
_LINE4( 0x0F,0x12,0x41,0x10 )                               /* movlps      xmm0,qword ptr [ecx+10h]  */ \
_LINE4( 0x0F,0x12,0x5A,0x08 )                               /* movlps      xmm3,qword ptr [edx+8]  */ \
_LINE3( 0x0F,0x16,0x11 )                                    /* movhps      xmm2,qword ptr [ecx]  */ \
ASM( subpd xmm2,xmm5 ) \
ASM( subsd xmm0,xmm4 ) \
ASM( subpd xmm3,xmm5 ) \
ASM( subsd xmm1,xmm4 ) \
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
ASM( movsd xmm1,xmm4 ) \
ASM( movhlps xmm4,xmm4 ) \
_LINE4( 0x66,0x0F,0x14,0xD4 )                               /* unpcklpd    xmm2,xmm4  */ \
_LINE4( 0x66,0x0F,0x28,0xC2 )                               /* movapd      xmm0,xmm2  */ \
_LINE4( 0x66,0x0F,0x28,0xD9 )                               /* movapd      xmm3,xmm1  */ \
_LINE4( 0x66,0x0F,0x59,0xD2 )                               /* mulpd       xmm2,xmm2  */ \
_LINE4( 0xF2,0x0F,0x59,0xDB )                               /* mulsd       xmm3,xmm3  */ \
_LINE4( 0xF2,0x0F,0x58,0xDA )                               /* addsd       xmm3,xmm2  */ \
_LINE4( 0x66,0x0F,0x15,0xD2 )                               /* unpckhpd    xmm2,xmm2  */ \
_LINE4( 0xF2,0x0F,0x58,0xDA )                               /* addsd       xmm3,xmm2  */ \
_LINE4( 0xF2,0x0F,0x51,0xDB )                               /* sqrtsd      xmm3,xmm3  */ \
_LINE5( 0xB8,0x01,0x00,0x00,0x00 )                          /* mov         eax,1  */ \
_LINE4( 0xF2,0x0F,0x2A,0xD0 )                               /* cvtsi2sd    xmm2,eax  */ \
_LINE4( 0xF2,0x0F,0x5E,0xD3 )                               /* divsd       xmm2,xmm3  */ \
ASM( mov eax,[esp+16] ) \
_LINE4( 0x66,0x0F,0x14,0xD2 )                               /* unpcklpd    xmm2,xmm2  */ \
ASM( add edx,eax ) \
_LINE4( 0x66,0x0F,0x59,0xC2 )                               /* mulpd       xmm0,xmm2  */ \
ASM( add ecx,eax ) \
_LINE4( 0xF2,0x0F,0x59,0xCA )                               /* mulsd       xmm1,xmm2  */ \
ASM( add eax,[esp+4] ) \
_LINE4( 0x0F,0x12,0x51,0x10 )                               /* movlps      xmm2,qword ptr [ecx+10h]  */ \
_LINE4( 0x0F,0x12,0x5A,0x10 )                               /* movlps      xmm3,qword ptr [edx+10h]  */ \
_LINE4( 0x0F,0x12,0x60,0x10 )                               /* movlps      xmm4,qword ptr [eax+10h]  */ \
ASM( addsd xmm2,xmm1 ) \
ASM( addsd xmm3,xmm1 ) \
ASM( addsd xmm4,xmm1 ) \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x5A,0x10 )                          /* movsd       mmword ptr [edx+10h],xmm3  */ \
_LINE5( 0xF2,0x0F,0x11,0x60,0x10 )                          /* movsd       mmword ptr [eax+10h],xmm4  */ \
_LINE4( 0x0F,0x16,0x51,0x08 )                               /* movhps      xmm2,qword ptr [ecx+8]  */ \
_LINE4( 0x0F,0x16,0x5A,0x08 )                               /* movhps      xmm3,qword ptr [edx+8]  */ \
_LINE4( 0x0F,0x16,0x60,0x08 )                               /* movhps      xmm4,qword ptr [eax+8]  */ \
_LINE3( 0x0F,0x12,0x11 )                                    /* movlps      xmm2,qword ptr [ecx]  */ \
_LINE3( 0x0F,0x12,0x1A )                                    /* movlps      xmm3,qword ptr [edx]  */ \
_LINE3( 0x0F,0x12,0x20 )                                    /* movlps      xmm4,qword ptr [eax]  */ \
ASM( addpd xmm2,xmm0 ) \
ASM( addpd xmm3,xmm0 ) \
ASM( addpd xmm4,xmm0 ) \
_LINE4( 0xF2,0x0F,0x11,0x11 )                               /* movsd       mmword ptr [ecx],xmm2  */ \
_LINE4( 0xF2,0x0F,0x11,0x1A )                               /* movsd       mmword ptr [edx],xmm3  */ \
_LINE4( 0xF2,0x0F,0x11,0x20 )                               /* movsd       mmword ptr [eax],xmm4  */ \
_LINE4( 0x66,0x0F,0x15,0xD2 )                               /* unpckhpd    xmm2,xmm2  */ \
_LINE4( 0x66,0x0F,0x15,0xDB )                               /* unpckhpd    xmm3,xmm3  */ \
_LINE4( 0x66,0x0F,0x15,0xE4 )                               /* unpckhpd    xmm4,xmm4  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x5A,0x08 )                          /* movsd       mmword ptr [edx+8],xmm3  */ \
_LINE5( 0xF2,0x0F,0x11,0x60,0x08 )                          /* movsd       mmword ptr [eax+8],xmm4  */ \
_END_ASM

#endif
