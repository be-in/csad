//=============================================================================
///**
// *  @file vector_scale.h
// *
// *  $Id: vector_scale.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float scale, MS Visual C++ 2003-2008
// *
// *  @author Pant_eleymonov Alek_sandr Kons_tantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

//**************************** SCALE STDCALL *********************************
// vector scale eax=[esp+4]-in void * edx=[esp+8]-out void * [esp+12]-float* (double*)

/// Умножает четырехмерный целочисленный вектор на число, команды SSE3.
#define VECTORP4ISCALESSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE6( 0xF3,0x0F,0x10,0x4C,0x24,0x0C )                     /* movss       xmm1,dword ptr [esp+0Ch]  */ \
_LINE3( 0x0F,0x5B,0xD0 )                                    /* cvtdq2ps       xmm2,xmm0  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xD1 )                                    /* mulps       xmm2,xmm1  */ \
_LINE4( 0xF3,0x0F,0x5B,0xC2 )                                /* cvttps2dq   xmm0,xmm2   */ \
_LINE3( 0x0F,0x13,0x01 )                                    /* movlps      qword ptr [ecx],xmm0  */ \
_LINE4( 0x0F,0x17,0x41,0x08 )                               /* movhps      qword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Умножает двухмерный вектор одинарной точности на число, команды FPU.
#define VECTORP2DSCALEFPU_STD \
_BEGIN_ASM \
_LINE4( 0xD9,0x44,0x24,0x0C )                               /* fld         dword ptr [esp+0Ch]  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE2( 0xD9,0x19 )                                         /* fstp        dword ptr [ecx]  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x59,0x04 )                                    /* fstp        dword ptr [ecx+4]  */ \
_END_ASM

/// Умножает двухмерный вектор одинарной точности на число, команды SSE.
#define VECTORP2DSCALESSE_STD \
_BEGIN_ASM \
_LINE6( 0xF3,0x0F,0x10,0x4C,0x24,0x0C )                     /* movss       xmm1,dword ptr [esp+0Ch]  */ \
_LINE4( 0xF3,0x0F,0x10,0xC1 )                               /* movss       xmm0,xmm1  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF3,0x0F,0x59,0x00 )                               /* mulss       xmm0,dword ptr [eax]  */ \
_LINE5( 0xF3,0x0F,0x59,0x48,0x04 )                          /* mulss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE4( 0xF3,0x0F,0x11,0x01 )                               /* movss       dword ptr [ecx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x49,0x04 )                          /* movss       dword ptr [ecx+4],xmm1  */ \
_END_ASM

/// Умножает двухмерный вектор одинарной точности на число, команды SSE2.
#define VECTORP2DSCALESSE2_STD \
_BEGIN_ASM \
_LINE6( 0xF3,0x0F,0x10,0x4C,0x24,0x0C )                     /* movss       xmm1,dword ptr [esp+0Ch]  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xC1 )                                    /* mulps       xmm0,xmm1  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_END_ASM

/// Умножает трехмерный вектор одинарной точности на число, команды FPU.
#define VECTORP3DSCALEFPU_STD \
_BEGIN_ASM \
_LINE4( 0xD9,0x44,0x24,0x0C )                               /* fld         dword ptr [esp+0Ch]  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE2( 0xD9,0x19 )                                         /* fstp        dword ptr [ecx]  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x59,0x04 )                                    /* fstp        dword ptr [ecx+4]  */ \
_LINE3( 0xD8,0x48,0x08 )                                    /* fmul        dword ptr [eax+8]  */ \
_LINE3( 0xD9,0x59,0x08 )                                    /* fstp        dword ptr [ecx+8]  */ \
_END_ASM

/// Умножает трехмерный вектор одинарной точности на число, команды SSE.
#define VECTORP3DSCALESSE_STD \
_BEGIN_ASM \
_LINE6( 0xF3,0x0F,0x10,0x4C,0x24,0x0C )                     /* movss       xmm1,dword ptr [esp+0Ch]  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x00 )                                    /* movhps      xmm0,qword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xC1 )                                    /* mulps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x17,0x01 )                                    /* movhps      qword ptr [ecx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x41,0x08 )                          /* movss       dword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Умножает четырехмерный вектор одинарной точности на число, команды FPU.
#define VECTORP4DSCALEFPU_STD \
_BEGIN_ASM \
_LINE4( 0xD9,0x44,0x24,0x0C )                               /* fld         dword ptr [esp+0Ch]  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE2( 0xD9,0x19 )                                         /* fstp        dword ptr [ecx]  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x59,0x04 )                                    /* fstp        dword ptr [ecx+4]  */ \
_LINE3( 0xD8,0x48,0x08 )                                    /* fmul        dword ptr [eax+8]  */ \
_LINE3( 0xD9,0x59,0x08 )                                    /* fstp        dword ptr [ecx+8]  */ \
_LINE3( 0xD8,0x48,0x0C )                                    /* fmul        dword ptr [eax+12]  */ \
_LINE3( 0xD9,0x59,0x0C )                                    /* fstp        dword ptr [ecx+12]  */ \
_END_ASM

/// Умножает четырехмерный вектор одинарной точности на число, команды SSE.
#define VECTORP4DSCALESSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE3( 0x0F,0x12,0x00 )                                    /* movlps      xmm0,qword ptr [eax]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )                               /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE6( 0xF3,0x0F,0x10,0x4C,0x24,0x0C )                     /* movss       xmm1,dword ptr [esp+0Ch]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xC1 )                                    /* mulps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x01 )                                    /* movlps      qword ptr [ecx],xmm0  */ \
_LINE4( 0x0F,0x17,0x41,0x08 )                               /* movhps      qword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Умножает четырехмерный вектор одинарной точности на число, команды SSE3.
#define VECTORP4DSCALESSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE6( 0xF3,0x0F,0x10,0x4C,0x24,0x0C )                     /* movss       xmm1,dword ptr [esp+0Ch]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xC1 )                                    /* mulps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x01 )                                    /* movlps      qword ptr [ecx],xmm0  */ \
_LINE4( 0x0F,0x17,0x41,0x08 )                               /* movhps      qword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Умножает двухмерный вектор двойной точности на число, команды FPU.
#define VECTORP2DDSCALEFPU_STD \
_BEGIN_ASM \
_LINE4( 0xDD,0x44,0x24,0x0C )                               /* fld         qword ptr [esp+0Ch]  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xDC,0x08 )                                         /* fmul        qword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE2( 0xDD,0x19 )                                         /* fstp        qword ptr [ecx]  */ \
_LINE3( 0xDC,0x48,0x08 )                                    /* fmul        qword ptr [eax+8]  */ \
_LINE3( 0xDD,0x59,0x08 )                                    /* fstp        qword ptr [ecx+8]  */ \
_END_ASM

/// Умножает двухмерный вектор двойной точности на число, команды SSE2.
#define VECTORP2DDSCALESSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x08 )                          /* movsd       xmm1,mmword ptr [eax+8]  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE4( 0x66,0x0F,0x14,0xC1 )                               /* unpcklpd    xmm0,xmm1  */ \
_LINE6( 0xF2,0x0F,0x10,0x54,0x24,0x0C )                     /* movsd       xmm2,mmword ptr [esp+0Ch]  */ \
_LINE4( 0x66,0x0F,0x14,0xD2 )                               /* unpcklpd    xmm2,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xC2 )                               /* mulpd       xmm0,xmm2  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Умножает двухмерный вектор двойной точности на число, команды SSE3.
#define VECTORP2DDSCALESSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE6( 0xF2,0x0F,0x12,0x4C,0x24,0x0C )                     /* movddup     xmm1,mmword ptr [esp+0Ch]  */ \
_LINE4( 0x66,0x0F,0x59,0xC1 )                               /* mulpd       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Умножает двухмерный вектор двойной точности на число, команды SSE4.
#define VECTORP2DDSCALESSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE6( 0xF2,0x0F,0x12,0x4C,0x24,0x0C )                     /* movddup     xmm1,mmword ptr [esp+0Ch]  */ \
_LINE4( 0x66,0x0F,0x59,0xC1 )                               /* mulpd       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_END_ASM

/// Умножает трехмерный вектор двойной точности на число, команды FPU.
#define VECTORP3DDSCALEFPU_STD \
_BEGIN_ASM \
_LINE4( 0xDD,0x44,0x24,0x0C )                               /* fld         qword ptr [esp+0Ch]  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xDC,0x08 )                                         /* fmul        qword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE2( 0xDD,0x19 )                                         /* fstp        qword ptr [ecx]  */ \
_LINE3( 0xDC,0x48,0x08 )                                    /* fmul        qword ptr [eax+8]  */ \
_LINE3( 0xDD,0x59,0x08 )                                    /* fstp        qword ptr [ecx+8]  */ \
_LINE3( 0xDC,0x48,0x10 )                                    /* fmul        qword ptr [eax+16]  */ \
_LINE3( 0xDD,0x59,0x10 )                                    /* fstp        qword ptr [ecx+16]  */ \
_END_ASM

/// Умножает трехмерный вектор двойной точности на число, команды SSE2.
#define VECTORP3DDSCALESSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x08 )                          /* movsd       xmm1,mmword ptr [eax+8]  */ \
_LINE6( 0xF2,0x0F,0x10,0x64,0x24,0x0C )                     /* movsd       xmm4,mmword ptr [esp+0Ch]  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE4( 0x66,0x0F,0x14,0xC1 )                               /* unpcklpd    xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x14,0xE4 )                               /* unpcklpd    xmm4,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xC4 )                               /* mulpd       xmm0,xmm4  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE4( 0xF2,0x0F,0x59,0xD4 )                               /* mulsd       xmm2,xmm4  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Умножает трехмерный вектор двойной точности на число, команды SSE3.
#define VECTORP3DDSCALESSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE6( 0xF2,0x0F,0x12,0x64,0x24,0x0C )                     /* movddup     xmm4,mmword ptr [esp+0Ch]  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE4( 0x66,0x0F,0x59,0xC4 )                               /* mulpd       xmm0,xmm4  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE4( 0xF2,0x0F,0x59,0xD4 )                               /* mulsd       xmm2,xmm4  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm0  */ \
_END_ASM

/// Умножает трехмерный вектор двойной точности на число, команды SSE4.
#define VECTORP3DDSCALESSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE6( 0xF2,0x0F,0x12,0x64,0x24,0x0C )                     /* movddup     xmm4,mmword ptr [esp+0Ch]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE4( 0x66,0x0F,0x59,0xC4 )                               /* mulpd       xmm0,xmm4  */ \
_LINE4( 0xF2,0x0F,0x59,0xD4 )                               /* mulsd       xmm2,xmm4  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_END_ASM

/// Умножает четырехмерный вектор двойной точности на число, команды FPU.
#define VECTORP4DDSCALEFPU_STD \
_BEGIN_ASM \
_LINE4( 0xDD,0x44,0x24,0x0C )                               /* fld         qword ptr [esp+0Ch]  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xDC,0x08 )                                         /* fmul        qword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE2( 0xDD,0x19 )                                         /* fstp        qword ptr [ecx]  */ \
_LINE3( 0xDC,0x48,0x08 )                                    /* fmul        qword ptr [eax+8]  */ \
_LINE3( 0xDD,0x59,0x08 )                                    /* fstp        qword ptr [ecx+8]  */ \
_LINE3( 0xDC,0x48,0x10 )                                    /* fmul        qword ptr [eax+16]  */ \
_LINE3( 0xDD,0x59,0x10 )                                    /* fstp        qword ptr [ecx+16]  */ \
_LINE3( 0xDC,0x48,0x18 )                                    /* fmul        qword ptr [eax+24]  */ \
_LINE3( 0xDD,0x59,0x18 )                                    /* fstp        qword ptr [ecx+24]  */ \
_END_ASM

/// Умножает четырехмерный вектор двойной точности на число, команды SSE2.
#define VECTORP4DDSCALESSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x08 )                          /* movsd       xmm1,mmword ptr [eax+8]  */ \
_LINE6( 0xF2,0x0F,0x10,0x64,0x24,0x0C )                     /* movsd       xmm4,mmword ptr [esp+0Ch]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x58,0x18 )                          /* movsd       xmm3,mmword ptr [eax+18h]  */ \
_LINE4( 0x66,0x0F,0x14,0xE4 )                               /* unpcklpd    xmm4,xmm4  */ \
_LINE4( 0x66,0x0F,0x14,0xC1 )                               /* unpcklpd    xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x14,0xD3 )                               /* unpcklpd    xmm2,xmm3  */ \
_LINE4( 0x66,0x0F,0x59,0xC4 )                               /* mulpd       xmm0,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xD2 )                               /* unpckhpd    xmm2,xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x18 )                          /* movsd       mmword ptr [ecx+18h],xmm2  */ \
_END_ASM

/// Умножает четырехмерный вектор двойной точности на число, команды SSE3.
#define VECTORP4DDSCALESSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE6( 0xF2,0x0F,0x12,0x64,0x24,0x0C )                     /* movddup     xmm4,mmword ptr [esp+0Ch]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x50,0x10 )                          /* lddqu       xmm2,xmmword ptr [eax+10h]  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE4( 0x66,0x0F,0x59,0xC4 )                               /* mulpd       xmm0,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE4( 0xF2,0x0F,0x11,0x01 )                               /* movsd       mmword ptr [ecx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x10 )                          /* movsd       mmword ptr [ecx+10h],xmm2  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xD2 )                               /* unpckhpd    xmm2,xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x41,0x08 )                          /* movsd       mmword ptr [ecx+8],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x51,0x18 )                          /* movsd       mmword ptr [ecx+18h],xmm2  */ \
_END_ASM

/// Умножает четырехмерный вектор двойной точности на число, команды SSE4.
#define VECTORP4DDSCALESSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE6( 0xF2,0x0F,0x12,0x64,0x24,0x0C )                     /* movddup     xmm4,mmword ptr [esp+0Ch]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x50,0x10 )                          /* lddqu       xmm2,xmmword ptr [eax+10h]  */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8]  */ \
_LINE4( 0x66,0x0F,0x59,0xC4 )                               /* mulpd       xmm0,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE4( 0x66,0x0F,0x11,0x01 )                               /* movupd      xmmword ptr [ecx],xmm0  */ \
_LINE5( 0x66,0x0F,0x11,0x51,0x10 )                          /* movupd      xmmword ptr [ecx+10h],xmm2  */ \
_END_ASM

/// Умножает четырехмерный вектор двойной точности на число, команды AVX.
#define VECTORP4DDSCALEAVX_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                 /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xC5,0xFD,0x10,0x08 )                 /* vmovupd     ymm1,ymmword ptr [eax]  */ \
_LINE7( 0xC4,0xE2,0x7D,0x19,0x44,0x24,0x0C )  /* vbroadcastsd ymm0,qword ptr [esp+0Ch]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                 /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xC5,0xFD,0x59,0xD9 )                 /* vmulpd      ymm3,ymm0,ymm1  */ \
_LINE4( 0xC5,0xFD,0x11,0x1A )                 /* vmovupd     ymmword ptr [edx],ymm3  */ \
_LINE3( 0xC5,0xF8,0x77 )                      /* vzeroupper  */ \
_END_ASM

//**************************** SCALE REGISTER FASTCALL *********************************
// vector scale eax-in void * edx-out void * ecx-float* (double*)

/// Умножает двухмерный вектор одинарной точности на число, команды FPU.
#define VECTORP2DSCALEFPU \
_BEGIN_ASM \
 _STR(_DB(0xD9) _DB(0x00)) \
 _STR(_DB(0xD8) _DB(0x09)) \
 _STR(_DB(0xD9) _DB(0x1A)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
 _STR(_DB(0xD8) _DB(0x09)) \
 _STR(_DB(0xD9) _DB(0x5A) _DB(0x04)) \
_END_ASM

/// Умножает двухмерный вектор одинарной точности на число, команды SSE.
#define VECTORP2DSCALESSE \
BEGIN_ASM \
_ASM movss xmm1,[ecx] \
_ASM movss xmm0,xmm1 \
_ASM mulss xmm0,[eax] \
_ASM mulss xmm1,[eax+4] \
_ASM movss [edx],xmm0 \
_ASM movss [edx+4],xmm1 \
END_ASM

/// Умножает двухмерный вектор одинарной точности на число, команды SSE2.
#define VECTORP2DSCALESSE2 \
BEGIN_ASM \
_ASM movss xmm1,[ecx] \
_ASM movsd xmm0,[eax] \
_ASM shufps xmm1,xmm1,0 \
_ASM mulss xmm0,xmm1 \
_ASM movsd [edx],xmm0 \
END_ASM

/// Умножает трехмерный вектор одинарной точности на число, команды FPU.
#define VECTORP3DSCALEFPU \
_BEGIN_ASM \
 _STR(_DB(0xD9) _DB(0x00)) \
 _STR(_DB(0xD8) _DB(0x09)) \
 _STR(_DB(0xD9) _DB(0x1A)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
 _STR(_DB(0xD8) _DB(0x09)) \
 _STR(_DB(0xD9) _DB(0x5A) _DB(0x04)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xD8) _DB(0x09)) \
 _STR(_DB(0xD9) _DB(0x5A) _DB(0x08)) \
_END_ASM

/// Умножает трехмерный вектор одинарной точности на число, команды SSE.
#define VECTORP3DSCALESSE \
BEGIN_ASM \
_ASM movss xmm0,[eax+8] \
_ASM movhps xmm0,[eax] \
_ASM movss xmm1,[ecx] \
_ASM shufps xmm1,xmm1,0 \
_ASM mulps xmm0,xmm1 \
_ASM movhps [edx],xmm0 \
_ASM movss [edx+8],xmm0 \
END_ASM

/// Умножает четырехмерный вектор одинарной точности на число, команды FPU.
#define VECTORP4DSCALEFPU \
_BEGIN_ASM \
 _STR(_DB(0xD9) _DB(0x00)) \
 _STR(_DB(0xD8) _DB(0x09)) \
 _STR(_DB(0xD9) _DB(0x1A)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
 _STR(_DB(0xD8) _DB(0x09)) \
 _STR(_DB(0xD9) _DB(0x5A) _DB(0x04)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xD8) _DB(0x09)) \
 _STR(_DB(0xD9) _DB(0x5A) _DB(0x08)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x0C)) \
 _STR(_DB(0xD8) _DB(0x09)) \
 _STR(_DB(0xD9) _DB(0x5A) _DB(0x0C)) \
_END_ASM

/// Умножает четырехмерный вектор одинарной точности на число, команды SSE.
#define VECTORP4DSCALESSE \
BEGIN_ASM \
_ASM movlps xmm0,[eax] \
_ASM movhps xmm0,[eax+8] \
_ASM movss xmm1,[ecx] \
_ASM shufps xmm1,xmm1,0 \
_ASM mulps xmm0,xmm1 \
_ASM movlps [edx],xmm0 \
_ASM movhps [edx+8],xmm0 \
END_ASM

/// Умножает четырехмерный вектор одинарной точности на число, команды SSE3.
#define VECTORP4DSCALESSE3 \
BEGIN_ASM \
_ASM lddqu xmm0,[eax] \
_ASM movss xmm1,[ecx] \
_ASM shufps xmm1,xmm1,0 \
_ASM mulps xmm0,xmm1 \
_ASM movups [edx],xmm0 \
END_ASM

/// Умножает двухмерный вектор двойной точности на число, команды FPU.
#define VECTORP2DDSCALEFPU \
_BEGIN_ASM \
 _STR(_DB(0xDD) _DB(0x00)) \
 _STR(_DB(0xDC) _DB(0x09)) \
 _STR(_DB(0xDD) _DB(0x1A)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x09)) \
 _STR(_DB(0xDD) _DB(0x5A) _DB(0x08)) \
_END_ASM

/// Умножает двухмерный вектор двойной точности на число, команды SSE2.
#define VECTORP2DDSCALESSE2 \
BEGIN_ASM \
_ASM movsd xmm0,[eax] \
_ASM movsd xmm1,[eax+8] \
_ASM unpcklpd xmm0,xmm1 \
_ASM movsd xmm2,[ecx] \
_ASM unpcklpd xmm2,xmm2 \
_ASM mulpd xmm0,xmm2 \
_ASM movsd [edx],xmm0 \
_ASM unpckhpd xmm0,xmm0 \
_ASM movsd [edx+8],xmm0 \
END_ASM

/// Умножает двухмерный вектор двойной точности на число, команды SSE3.
#define VECTORP2DDSCALESSE3 \
BEGIN_ASM \
_ASM lddqu xmm0,[eax] \
_ASM movddup xmm1,[ecx] \
_ASM mulpd xmm0,xmm1 \
_ASM movsd [edx],xmm0 \
_ASM unpckhpd xmm0,xmm0 \
_ASM movsd [edx+8],xmm0 \
END_ASM

/// Умножает трехмерный вектор двойной точности на число, команды FPU.
#define VECTORP3DDSCALEFPU \
_BEGIN_ASM \
 _STR(_DB(0xDD) _DB(0x00)) \
 _STR(_DB(0xDC) _DB(0x09)) \
 _STR(_DB(0xDD) _DB(0x1A)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x09)) \
 _STR(_DB(0xDD) _DB(0x5A) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x10)) \
 _STR(_DB(0xDC) _DB(0x09)) \
 _STR(_DB(0xDD) _DB(0x5A) _DB(0x10)) \
_END_ASM

/// Умножает трехмерный вектор двойной точности на число, команды SSE2.
#define VECTORP3DDSCALESSE2 \
BEGIN_ASM \
_ASM movsd xmm0,[eax] \
_ASM movsd xmm1,[eax+8] \
_ASM movsd xmm4,[ecx] \
_ASM unpcklpd xmm0,xmm1 \
_ASM unpcklpd xmm4,xmm4 \
_ASM mulpd xmm0,xmm4 \
_ASM movsd xmm2,[eax+16] \
_ASM movsd [edx],xmm0 \
_ASM mulsd xmm2,xmm4 \
_ASM unpckhpd xmm0,xmm0 \
_ASM movsd [edx+16],xmm2 \
_ASM movsd [edx+8],xmm0 \
END_ASM

/*
_BEGIN_ASM \
_LINE3(0x0F,0x10,0x00) \
_LINE4(0xF2,0x0F,0x10,0x09) \
_LINE5(0xF2,0x0F,0x10,0x50,0x10) \
_LINE4(0x0F,0xC6,0xC9,0x44) \
_LINE4(0x66,0x0F,0x59,0xC1) \
_LINE4(0x66,0x0F,0x59,0xD1) \
_LINE3(0x0F,0x11,0x02) \
_LINE5(0xF2,0x0F,0x11,0x52,0x10) \
_END_ASM
*/

/// Умножает трехмерный вектор двойной точности на число, команды SSE2.
#define VECTORP3DDSCALESSE3 \
BEGIN_ASM \
_ASM lddqu xmm0,[eax] \
_ASM movddup xmm4,[ecx] \
_ASM movsd xmm2,[eax+16] \
_ASM mulpd xmm0,xmm4 \
_ASM movsd [edx],xmm0 \
_ASM mulsd xmm2,xmm4 \
_ASM unpckhpd xmm0,xmm0 \
_ASM movsd [edx+16],xmm2 \
_ASM movsd [edx+8],xmm0 \
END_ASM

/// Умножает трехмерный вектор двойной точности на число, команды SSE4.
#define VECTORP3DDSCALESSE4 \
BEGIN_ASM \
_ASM lddqu xmm0,[eax] \
_ASM movddup xmm4,[ecx] \
_ASM movsd xmm2,[eax+16] \
_ASM mulpd xmm0,xmm4 \
_ASM mulsd xmm2,xmm4 \
_ASM movupd [edx],xmm0 \
_ASM movsd [edx+16],xmm2 \
END_ASM

/// Умножает четырехмерный вектор двойной точности на число, команды FPU.
#define VECTORP4DDSCALEFPU \
_BEGIN_ASM \
 _LINE2(0xDD,0x00) \
 _LINE2(0xDC,0x09) \
 _LINE2(0xDD,0x1A) \
 _LINE3(0xDD,0x40,0x08) \
 _LINE2(0xDC,0x09) \
 _LINE3(0xDD,0x5A,0x08) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x10)) \
 _STR(_DB(0xDC) _DB(0x09)) \
 _STR(_DB(0xDD) _DB(0x5A) _DB(0x10)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x18)) \
 _STR(_DB(0xDC) _DB(0x09)) \
 _STR(_DB(0xDD) _DB(0x5A) _DB(0x18)) \
_END_ASM

/// Умножает четырехмерный вектор двойной точности на число, команды SSE2.
#define VECTORP4DDSCALESSE2 \
BEGIN_ASM \
_ASM movsd xmm0,[eax] \
_ASM movsd xmm1,[eax+8] \
_ASM movsd xmm4,[ecx] \
_ASM movsd xmm2,[eax+16] \
_ASM movsd xmm3,[eax+24] \
_ASM unpcklpd xmm4,xmm4 \
_ASM unpcklpd xmm0,xmm1 \
_ASM unpcklpd xmm2,xmm3 \
_ASM mulpd xmm0,xmm4 \
_ASM mulpd xmm2,xmm4 \
_ASM movsd [edx],xmm0 \
_ASM movsd [edx+16],xmm2 \
_ASM unpckhpd xmm0,xmm0 \
_ASM unpckhpd xmm2,xmm2 \
_ASM movsd [edx+8],xmm0 \
_ASM movsd [edx+24],xmm2 \
END_ASM

/*
_LINE3(0x0F,0x10,0x00) \
_LINE4(0xF2,0x0F,0x10,0x09) \
_LINE4(0x0F,0x10,0x50,0x10) \
_LINE4(0x0F,0xC6,0xC9,0x44) \
_LINE4(0x66,0x0F,0x59,0xC1) \
_LINE4(0x66,0x0F,0x59,0xD1) \
_LINE3(0x0F,0x11,0x02) \
_LINE4(0x0F,0x11,0x52,0x10) \
*/

/*BEGIN_ASM \
_ASM movsd xmm0,[eax] \
_ASM movsd xmm1,[eax+8] \
_ASM movsd xmm2,[eax+16] \
_ASM movsd xmm3,[eax+24] \
_ASM movsd xmm4,[edx] \
_ASM movsd xmm5,[edx+8] \
_ASM movsd xmm6,[edx+16] \
_ASM movsd xmm7,[edx+24] \
_ASM unpcklpd xmm0,xmm1 \
_ASM unpcklpd xmm2,xmm3 \
_ASM unpcklpd xmm4,xmm5 \
_ASM unpcklpd xmm6,xmm7 \
_ASM addpd xmm0,xmm4 \
_ASM addpd xmm2,xmm6 \
_ASM movsd [ecx],xmm0 \
_ASM movsd [ecx+16],xmm2 \
_ASM unpckhpd xmm0,xmm0 \
_ASM unpckhpd xmm2,xmm2 \
_ASM movsd [ecx+8],xmm0 \
_ASM movsd [ecx+24],xmm2 \
END_ASM*/

/// Умножает четырехмерный вектор двойной точности на число, команды SSE3.
#define VECTORP4DDSCALESSE3 \
BEGIN_ASM \
_ASM lddqu xmm0,[eax] \
_ASM movddup xmm4,[ecx] \
_ASM lddqu xmm2,[eax+16] \
_ASM mulpd xmm0,xmm4 \
_ASM mulpd xmm2,xmm4 \
_ASM movsd [edx],xmm0 \
_ASM movsd [edx+16],xmm2 \
_ASM unpckhpd xmm0,xmm0 \
_ASM unpckhpd xmm2,xmm2 \
_ASM movsd [edx+8],xmm0 \
_ASM movsd [edx+24],xmm2 \
END_ASM

/// Умножает четырехмерный вектор двойной точности на число, команды SSE4.
#define VECTORP4DDSCALESSE4 \
BEGIN_ASM \
_ASM lddqu xmm0,[eax] \
_ASM movddup xmm4,[ecx] \
_ASM lddqu xmm2,[eax+16] \
_ASM mulpd xmm0,xmm4 \
_ASM mulpd xmm2,xmm4 \
_ASM movupd [edx],xmm0 \
_ASM movupd [edx+16],xmm2 \
END_ASM

//**************************** SCALE C++ FASTCALL *********************************
// vector scale ecx-in void * edx-out void * eax-float* (double*)

/// Умножает двухмерный вектор одинарной точности на число, команды FPU.
#define VECTORP2DSCALEFPU_CPP \
_BEGIN_ASM \
 _STR(_DB(0xD9) _DB(0x01)) \
 _STR(_DB(0xD8) _DB(0x08)) \
 _STR(_DB(0xD9) _DB(0x1A)) \
 _STR(_DB(0xD9) _DB(0x41) _DB(0x04)) \
 _STR(_DB(0xD8) _DB(0x08)) \
 _STR(_DB(0xD9) _DB(0x5A) _DB(0x04)) \
_END_ASM

/// Умножает двухмерный вектор одинарной точности на число, команды SSE.
#define VECTORP2DSCALESSE_CPP \
_BEGIN_ASM \
_LINE3( 0x0F,0x16,0x01 )                                    /* movhps      xmm0,qword ptr [ecx]  */ \
_LINE4( 0xF3,0x0F,0x10,0x08 )                               /* movss       xmm1,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xC1 )                                    /* mulps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x17,0x02 )                                    /* movhps      qword ptr [edx],xmm0  */ \
_END_ASM

/// Умножает трехмерный вектор одинарной точности на число, команды FPU.
#define VECTORP3DSCALEFPU_CPP \
_BEGIN_ASM \
 _STR(_DB(0xD9) _DB(0x01)) \
 _STR(_DB(0xD8) _DB(0x08)) \
 _STR(_DB(0xD9) _DB(0x1A)) \
 _STR(_DB(0xD9) _DB(0x41) _DB(0x04)) \
 _STR(_DB(0xD8) _DB(0x08)) \
 _STR(_DB(0xD9) _DB(0x5A) _DB(0x04)) \
 _STR(_DB(0xD9) _DB(0x41) _DB(0x08)) \
 _STR(_DB(0xD8) _DB(0x08)) \
 _STR(_DB(0xD9) _DB(0x5A) _DB(0x08)) \
_END_ASM

/// Умножает трехмерный вектор одинарной точности на число, команды SSE.
#define VECTORP3DSCALESSE_CPP \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x41,0x08 )                          /* movss       xmm0,dword ptr [ecx+8]  */ \
_LINE3( 0x0F,0x16,0x01 )                                    /* movhps      xmm0,qword ptr [ecx]  */ \
_LINE4( 0xF3,0x0F,0x10,0x08 )                               /* movss       xmm1,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xC1 )                                    /* mulps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x17,0x02 )                                    /* movhps      qword ptr [edx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x42,0x08 )                          /* movss       dword ptr [edx+8],xmm0  */ \
_END_ASM

/// Умножает четырехмерный вектор одинарной точности на число, команды FPU.
#define VECTORP4DSCALEFPU_CPP \
_BEGIN_ASM \
 _STR(_DB(0xD9) _DB(0x01)) \
 _STR(_DB(0xD8) _DB(0x08)) \
 _STR(_DB(0xD9) _DB(0x1A)) \
 _STR(_DB(0xD9) _DB(0x41) _DB(0x04)) \
 _STR(_DB(0xD8) _DB(0x08)) \
 _STR(_DB(0xD9) _DB(0x5A) _DB(0x04)) \
 _STR(_DB(0xD9) _DB(0x41) _DB(0x08)) \
 _STR(_DB(0xD8) _DB(0x08)) \
 _STR(_DB(0xD9) _DB(0x5A) _DB(0x08)) \
 _STR(_DB(0xD9) _DB(0x41) _DB(0x0C)) \
 _STR(_DB(0xD8) _DB(0x08)) \
 _STR(_DB(0xD9) _DB(0x5A) _DB(0x0C)) \
_END_ASM

/// Умножает четырехмерный вектор одинарной точности на число, команды SSE.
#define VECTORP4DSCALESSE_CPP \
_BEGIN_ASM \
_LINE3( 0x0F,0x12,0x01 )                                    /* movlps      xmm0,qword ptr [ecx]  */ \
_LINE4( 0x0F,0x16,0x41,0x08 )                               /* movhps      xmm0,qword ptr [ecx+8]  */ \
_LINE4( 0xF3,0x0F,0x10,0x08 )                               /* movss       xmm1,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xC1 )                                    /* mulps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
_LINE4( 0x0F,0x17,0x42,0x08 )                               /* movhps      qword ptr [edx+8],xmm0 */ \
_END_ASM

/// Умножает четырехмерный вектор одинарной точности на число, команды SSE3.
#define VECTORP4DSCALESSE3_CPP \
BEGIN_ASM \
_ASM lddqu xmm0,[ecx] \
_ASM movss xmm1,[eax] \
_ASM shufps xmm1,xmm1,0 \
_ASM mulps xmm0,xmm1 \
_ASM movups [edx],xmm0 \
END_ASM

/// Умножает двухмерный вектор двойной точности на число, команды FPU.
#define VECTORP2DDSCALEFPU_CPP \
_BEGIN_ASM \
 _STR(_DB(0xDD) _DB(0x01)) \
 _STR(_DB(0xDC) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x1A)) \
 _STR(_DB(0xDD) _DB(0x41) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x5A) _DB(0x08)) \
_END_ASM

/// Умножает двухмерный вектор двойной точности на число, команды SSE2.
#define VECTORP2DDSCALESSE2_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x01 )                               /* movsd       xmm0,mmword ptr [ecx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x49,0x08 )                          /* movsd       xmm1,mmword ptr [ecx+8]  */ \
_LINE4( 0x66,0x0F,0x14,0xC1 )                               /* unpcklpd    xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x10,0x10 )                               /* movsd       xmm2,mmword ptr [eax]  */ \
_LINE4( 0x66,0x0F,0x14,0xD2 )                               /* unpcklpd    xmm2,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xC2 )                               /* mulpd       xmm0,xmm2  */ \
_LINE4( 0xF2,0x0F,0x11,0x02 )                               /* movsd       mmword ptr [edx],xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x42,0x08 )                          /* movsd       mmword ptr [edx+8],xmm0  */ \
_END_ASM

/// Умножает двухмерный вектор двойной точности на число, команды SSE3.
#define VECTORP2DDSCALESSE3_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0x12,0x08 )                               /* movddup     xmm1,mmword ptr [eax]  */ \
_LINE4( 0x66,0x0F,0x59,0xC1 )                               /* mulpd       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x02 )                               /* movsd       mmword ptr [edx],xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x42,0x08 )                          /* movsd       mmword ptr [edx+8],xmm0  */ \
_END_ASM

/// Умножает трехмерный вектор двойной точности на число, команды FPU.
#define VECTORP3DDSCALEFPU_CPP \
_BEGIN_ASM \
 _STR(_DB(0xDD) _DB(0x01)) \
 _STR(_DB(0xDC) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x1A)) \
 _STR(_DB(0xDD) _DB(0x41) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x5A) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x41) _DB(0x10)) \
 _STR(_DB(0xDC) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x5A) _DB(0x10)) \
_END_ASM

/// Умножает трехмерный вектор двойной точности на число, команды SSE2.
#define VECTORP3DDSCALESSE2_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x01 )                               /* movsd       xmm0,mmword ptr [ecx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x49,0x08 )                          /* movsd       xmm1,mmword ptr [ecx+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x20 )                               /* movsd       xmm4,mmword ptr [eax]  */ \
_LINE4( 0x66,0x0F,0x14,0xC1 )                               /* unpcklpd    xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x14,0xE4 )                               /* unpcklpd    xmm4,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xC4 )                               /* mulpd       xmm0,xmm4  */ \
_LINE5( 0xF2,0x0F,0x10,0x51,0x10 )                          /* movsd       xmm2,mmword ptr [ecx+10h]  */ \
_LINE4( 0xF2,0x0F,0x11,0x02 )                               /* movsd       mmword ptr [edx],xmm0  */ \
_LINE4( 0xF2,0x0F,0x59,0xD4 )                               /* mulsd       xmm2,xmm4  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x52,0x10 )                          /* movsd       mmword ptr [edx+10h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x42,0x08 )                          /* movsd       mmword ptr [edx+8],xmm0  */ \
_END_ASM

/// Умножает трехмерный вектор двойной точности на число, команды SSE2.
#define VECTORP3DDSCALESSE3_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0x12,0x20 )                               /* movddup     xmm4,mmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0x10,0x51,0x10 )                          /* movsd       xmm2,mmword ptr [ecx+10h]  */ \
_LINE4( 0x66,0x0F,0x59,0xC4 )                               /* mulpd       xmm0,xmm4  */ \
_LINE4( 0xF2,0x0F,0x11,0x02 )                               /* movsd       mmword ptr [edx],xmm0  */ \
_LINE4( 0xF2,0x0F,0x59,0xD4 )                               /* mulsd       xmm2,xmm4  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x52,0x10 )                          /* movsd       mmword ptr [edx+10h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x42,0x08 )                          /* movsd       mmword ptr [edx+8],xmm0  */ \
_END_ASM

/// Умножает трехмерный вектор двойной точности на число, команды SSE4.
#define VECTORP3DDSCALESSE4_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0x12,0x20 )                               /* movddup     xmm4,mmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0x10,0x51,0x10 )                          /* movsd       xmm2,mmword ptr [ecx+10h]  */ \
_LINE4( 0x66,0x0F,0x59,0xC4 )                               /* mulpd       xmm0,xmm4  */ \
_LINE4( 0xF2,0x0F,0x59,0xD4 )                               /* mulsd       xmm2,xmm4  */ \
_LINE4( 0x66,0x0F,0x11,0x02 )                               /* movupd      xmmword ptr [edx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x52,0x10 )                          /* movsd       mmword ptr [edx+10h],xmm2  */ \
_END_ASM

/// Умножает четырехмерный вектор двойной точности на число, команды FPU.
#define VECTORP4DDSCALEFPU_CPP \
_BEGIN_ASM \
 _LINE2(0xDD,0x01) \
 _LINE2(0xDC,0x08) \
 _LINE2(0xDD,0x1A) \
 _LINE3(0xDD,0x41,0x08) \
 _LINE2(0xDC,0x08) \
 _LINE3(0xDD,0x5A,0x08) \
 _STR(_DB(0xDD) _DB(0x41) _DB(0x10)) \
 _STR(_DB(0xDC) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x5A) _DB(0x10)) \
 _STR(_DB(0xDD) _DB(0x41) _DB(0x18)) \
 _STR(_DB(0xDC) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x5A) _DB(0x18)) \
_END_ASM

/// Умножает четырехмерный вектор двойной точности на число, команды SSE2.
#define VECTORP4DDSCALESSE2_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x01 )                               /* movsd       xmm0,mmword ptr [ecx]  */ \
_LINE5( 0xF2,0x0F,0x10,0x49,0x08 )                          /* movsd       xmm1,mmword ptr [ecx+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x20 )                               /* movsd       xmm4,mmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0x10,0x51,0x10 )                          /* movsd       xmm2,mmword ptr [ecx+10h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x59,0x18 )                          /* movsd       xmm3,mmword ptr [ecx+18h]  */ \
_LINE4( 0x66,0x0F,0x14,0xE4 )                               /* unpcklpd    xmm4,xmm4  */ \
_LINE4( 0x66,0x0F,0x14,0xC1 )                               /* unpcklpd    xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x14,0xD3 )                               /* unpcklpd    xmm2,xmm3  */ \
_LINE4( 0x66,0x0F,0x59,0xC4 )                               /* mulpd       xmm0,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE4( 0xF2,0x0F,0x11,0x02 )                               /* movsd       mmword ptr [edx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x52,0x10 )                          /* movsd       mmword ptr [edx+10h],xmm2  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xD2 )                               /* unpckhpd    xmm2,xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x42,0x08 )                          /* movsd       mmword ptr [edx+8],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x52,0x18 )                          /* movsd       mmword ptr [edx+18h],xmm2  */ \
_END_ASM

/// Умножает четырехмерный вектор двойной точности на число, команды SSE3.
#define VECTORP4DDSCALESSE3_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0x12,0x20 )                               /* movddup     xmm4,mmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x51,0x10 )                          /* lddqu       xmm2,xmmword ptr [ecx+10h]  */ \
_LINE4( 0x66,0x0F,0x59,0xC4 )                               /* mulpd       xmm0,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE4( 0xF2,0x0F,0x11,0x02 )                               /* movsd       mmword ptr [edx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x52,0x10 )                          /* movsd       mmword ptr [edx+10h],xmm2  */ \
_LINE4( 0x66,0x0F,0x15,0xC0 )                               /* unpckhpd    xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x15,0xD2 )                               /* unpckhpd    xmm2,xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x42,0x08 )                          /* movsd       mmword ptr [edx+8],xmm0  */ \
_LINE5( 0xF2,0x0F,0x11,0x52,0x18 )                          /* movsd       mmword ptr [edx+18h],xmm2  */ \
_END_ASM

/// Умножает четырехмерный вектор двойной точности на число, команды SSE4.
#define VECTORP4DDSCALESSE4_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0x12,0x20 )                               /* movddup     xmm4,mmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x51,0x10 )                          /* lddqu       xmm2,xmmword ptr [ecx+10h]  */ \
_LINE4( 0x66,0x0F,0x59,0xC4 )                               /* mulpd       xmm0,xmm4  */ \
_LINE4( 0x66,0x0F,0x59,0xD4 )                               /* mulpd       xmm2,xmm4  */ \
_LINE4( 0x66,0x0F,0x11,0x02 )                               /* movupd      xmmword ptr [edx],xmm0  */ \
_LINE5( 0x66,0x0F,0x11,0x52,0x10 )                          /* movupd      xmmword ptr [edx+10h],xmm2 */ \
_END_ASM
