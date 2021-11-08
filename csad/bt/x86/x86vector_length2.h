//=============================================================================
///**
// *  @file vector_length2.h
// *
// *  $Id: vector_length2.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float length2, MS Visual C++ 2003-2008
// *
// *  @author Pan_teleymonov Ale_ksandr Kon_stantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_VECTOR_LENGTH2_H
#define GEN3_VECTOR_LENGTH2_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** LENGTH2 STDCALL *********************************
// length vectors eax=[esp+4]-a void *, st(0)-rez double/float

/// Квадрат длинны двухмерного вектора одинарной точности, команды FPU
#define VECTORP2DLENGTH2FPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// Квадрат длинны двухмерного вектора одинарной точности, команды SSE4
#define VECTORP2DLENGTH2SSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC0,0x31 )                     /* dpps        xmm0,xmm0,31h  */ \
_LINE6( 0xF3,0x0F,0x11,0x44,0x24,0xDC )                     /* movss       dword ptr [esp-24h],xmm0  */ \
_LINE4( 0xD9,0x44,0x24,0xDC )                               /* fld         dword ptr [esp-24h]  */ \
_END_ASM

/// Квадрат длинны двухмерного вектора одинарной точности, команды FPU
#define VECTORP3DLENGTH2FPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD8,0x48,0x08 )                                    /* fmul        dword ptr [eax+8]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// Квадрат длинны двухмерного вектора одинарной точности, команды SSE4
#define VECTORP3DLENGTH2SSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x00 )                                    /* movhps      xmm0,qword ptr [eax]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC0,0xD1 )                     /* dpps        xmm0,xmm0,0D1h  */ \
_LINE6( 0xF3,0x0F,0x11,0x44,0x24,0xDC )                     /* movss       dword ptr [esp-24h],xmm0  */ \
_LINE4( 0xD9,0x44,0x24,0xDC )                               /* fld         dword ptr [esp-24h]  */ \
_END_ASM

/// Квадрат длинны четырехмерного вектора одинарной точности, команды FPU
#define VECTORP4DLENGTH2FPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD8,0x48,0x08 )                                    /* fmul        dword ptr [eax+8]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x40,0x0C )                                    /* fld         dword ptr [eax+12]  */ \
_LINE3( 0xD8,0x48,0x0C )                                    /* fmul        dword ptr [eax+12]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// Квадрат длинны четырехмерного вектора одинарной точности, команды SSE
#define VECTORP4DLENGTH2SSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
ASM( movss   xmm1, dword ptr [eax+0x4] ) \
ASM( movss   xmm0, dword ptr [eax] ) \
_LINE5( 0xF3,0x0F,0x10,0x50,0x08 )                          /* movss       xmm2,dword ptr [eax+8]  */ \
ASM( mulss   xmm0, xmm0 ) \
ASM( mulss   xmm1, xmm1 ) \
ASM( mulss   xmm2, xmm2 ) \
_LINE5( 0xF3,0x0F,0x10,0x58,0x0C )                          /* movss       xmm3,dword ptr [eax+C]  */ \
ASM( addss   xmm0, xmm1 ) \
ASM( mulss   xmm3, xmm3 ) \
ASM( addss   xmm0, xmm2 ) \
ASM( addss   xmm0, xmm3 ) \
_LINE6( 0xF3,0x0F,0x11,0x44,0x24,0xDC )                     /* movss       dword ptr [esp-24h],xmm0  */ \
_LINE4( 0xD9,0x44,0x24,0xDC )                               /* fld         dword ptr [esp-24h]  */ \
_END_ASM

/// Квадрат длинны четырехмерного вектора одинарной точности, команды SSE4.
/// @brief for CPUTYPE4
#define VECTORP4DLENGTH2SSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC0,0xF1 )                     /* dpps        xmm0,xmm0,0F1h  */ \
_LINE6( 0xF3,0x0F,0x11,0x44,0x24,0xDC )                     /* movss       dword ptr [esp-24h],xmm0  */ \
_LINE4( 0xD9,0x44,0x24,0xDC )                               /* fld         dword ptr [esp-24h]  */ \
_END_ASM

/// Квадрат длинны двухмерного вектора двойной точности, команды FPU
#define VECTORP2DDLENGTH2FPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xDD,0x00 )                                         /* fld         qword ptr [eax]  */ \
_LINE2( 0xDC,0x08 )                                         /* fmul        qword ptr [eax]  */ \
_LINE3( 0xDD,0x40,0x08 )                                    /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDC,0x48,0x08 )                                    /* fmul        qword ptr [eax+8]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// Квадрат длинны двухмерного вектора двойной точности, команды SSE4
#define VECTORP2DDLENGTH2SSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC0,0x31 )                     /* dppd        xmm0,xmm0,31h  */ \
_LINE6( 0xF2,0x0F,0x11,0x44,0x24,0xDC )                     /* movsd       mmword ptr [esp-24h],xmm0  */ \
_LINE4( 0xDD,0x44,0x24,0xDC )                               /* fld         qword ptr [esp-24h]  */ \
_END_ASM

/// Квадрат длинны трехмерного вектора двойной точности, команды FPU
#define VECTORP3DDLENGTH2FPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xDD,0x00 )                                         /* fld         qword ptr [eax]  */ \
_LINE2( 0xDC,0x08 )                                         /* fmul        qword ptr [eax]  */ \
_LINE3( 0xDD,0x40,0x08 )                                    /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDC,0x48,0x08 )                                    /* fmul        qword ptr [eax+8]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x40,0x10 )                                    /* fld         qword ptr [eax+10h]  */ \
_LINE3( 0xDC,0x48,0x10 )                                    /* fmul        qword ptr [eax+10h]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// Квадрат длинны трехмерного вектора двойной точности, команды SSE4
#define VECTORP3DDLENGTH2SSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC0,0x31 )                     /* dppd        xmm0,xmm0,31h  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE4( 0xF2,0x0F,0x59,0xD2 )                               /* mulsd       xmm2,xmm2  */ \
_LINE4( 0xF2,0x0F,0x58,0xC2 )                               /* addsd       xmm0,xmm2  */ \
_LINE6( 0xF2,0x0F,0x11,0x44,0x24,0xDC )                     /* movsd       mmword ptr [esp-24h],xmm0  */ \
_LINE4( 0xDD,0x44,0x24,0xDC )                               /* fld         qword ptr [esp-24h]  */ \
_END_ASM

/// Квадрат длинны четырехмерного вектора двойной точности, команды SSE2
#define VECTORP4DDLENGTH2SSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x08 )                          /* movsd       xmm1,mmword ptr [eax+8h]  */ \
ASM( movsd   xmm0, qword ptr [eax] ) \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE4( 0xF2,0x0F,0x59,0xC0 )                               /* mulsd       xmm0,xmm0  */ \
_LINE4( 0xF2,0x0F,0x59,0xC9 )                               /* mulsd       xmm1,xmm1  */ \
_LINE4( 0xF2,0x0F,0x59,0xD2 )                               /* mulsd       xmm2,xmm2  */ \
_LINE5( 0xF2,0x0F,0x10,0x58,0x18 )                          /* movsd       xmm3,mmword ptr [eax+18h]  */ \
_LINE4( 0xF2,0x0F,0x58,0xC1 )                               /* addsd       xmm0,xmm1  */ \
_LINE4( 0xF2,0x0F,0x59,0xDB )                               /* mulsd       xmm3,xmm3  */ \
_LINE4( 0xF2,0x0F,0x58,0xC2 )                               /* addsd       xmm0,xmm2  */ \
_LINE6( 0xF2,0x0F,0x11,0x44,0x24,0xDC )                     /* movsd       mmword ptr [esp-24h],xmm0  */ \
_LINE4( 0xDD,0x44,0x24,0xDC )                               /* fld         qword ptr [esp-24h]  */ \
_END_ASM

/// Квадрат длинны четырехмерного вектора двойной точности, команды SSE4
#define VECTORP4DDLENGTH2SSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC0,0x31 )                     /* dppd        xmm0,xmm0,31h  */ \
_LINE5( 0xF2,0x0F,0xF0,0x50,0x10 )                          /* lddqu       xmm2,xmmword ptr [eax+10h]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xD2,0x31 )                     /* dppd        xmm2,xmm2,31h  */ \
_LINE4( 0xF2,0x0F,0x58,0xC2 )                               /* addsd       xmm0,xmm2  */ \
_LINE6( 0xF2,0x0F,0x11,0x44,0x24,0xDC )                     /* movsd       mmword ptr [esp-24h],xmm0  */ \
_LINE4( 0xDD,0x44,0x24,0xDC )                               /* fld         qword ptr [esp-24h]  */ \
_END_ASM

//**************************** LENGTH2 REGISTER FASTCALL *********************************
// length vectors eax-a void *, st(0)-rez double/float

/// Квадрат длинны двухмерного вектора одинарной точности, команды FPU
#define VECTORP2DLENGTH2FPU \
_BEGIN_ASM \
 _STR(_DB(0xD9) _DB(0x00)) \
 _STR(_DB(0xD8) _DB(0x08)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
 _STR(_DB(0xD8) _DB(0x48) _DB(0x04)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
_END_ASM

/// Квадрат длинны двухмерного вектора одинарной точности, команды SSE4
#define VECTORP2DLENGTH2SSE4 \
BEGIN_ASM \
_ASM movsd xmm0,[eax] \
_ASM dpps xmm0, xmm0, 0x31 \
_ASM movss [esp-_STACKFREE], xmm0 \
_ASM fld dword ptr [esp-_STACKFREE] \
END_ASM

/// Квадрат длинны двухмерного вектора одинарной точности, команды FPU
#define VECTORP3DLENGTH2FPU \
_BEGIN_ASM \
 _STR(_DB(0xD9) _DB(0x00)) \
 _STR(_DB(0xD8) _DB(0x08)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x04)) \
 _STR(_DB(0xD8) _DB(0x48) _DB(0x04)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xD9) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xD8) _DB(0x48) _DB(0x08)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
_END_ASM

/// Квадрат длинны двухмерного вектора одинарной точности, команды SSE4
#define VECTORP3DLENGTH2SSE4 \
BEGIN_ASM \
_ASM movss xmm0,[eax+8] \
_ASM movhps xmm0,[eax] \
_ASM dpps xmm0, xmm0, 0xD1 \
_ASM movss [esp-_STACKFREE], xmm0 \
_ASM fld dword ptr [esp-_STACKFREE] \
END_ASM

/// Квадрат длинны двухмерного вектора двойной точности, команды FPU
#define VECTORP2DDLENGTH2FPU \
_BEGIN_ASM \
 _STR(_DB(0xDD) _DB(0x00)) \
 _STR(_DB(0xDC) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x48) _DB(0x08)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
_END_ASM

/// Квадрат длинны двухмерного вектора двойной точности, команды SSE4
#define VECTORP2DDLENGTH2SSE4 \
BEGIN_ASM \
_ASM lddqu xmm0, [eax] \
_ASM dppd xmm0, xmm0, 0x31 \
_ASM movsd [esp-_STACKFREE], xmm0 \
_ASM fld qword ptr [esp-_STACKFREE] \
END_ASM

/// Квадрат длинны трехмерного вектора двойной точности, команды FPU
#define VECTORP3DDLENGTH2FPU \
_BEGIN_ASM \
 _STR(_DB(0xDD) _DB(0x00)) \
 _STR(_DB(0xDC) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x48) _DB(0x08)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x10)) \
 _STR(_DB(0xDC) _DB(0x48) _DB(0x10)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
_END_ASM

/// Квадрат длинны трехмерного вектора двойной точности, команды SSE4
#define VECTORP3DDLENGTH2SSE4 \
BEGIN_ASM \
_ASM lddqu xmm0, [eax] \
_ASM dppd xmm0, xmm0, 0x31 \
_ASM movsd xmm2, [eax+16] \
_ASM mulsd xmm2, xmm2 \
_ASM addsd xmm0,xmm2 \
_ASM movsd [esp-_STACKFREE], xmm0 \
_ASM fld qword ptr [esp-_STACKFREE] \
END_ASM

//**************************** LENGTH2 CPP FASTCALL *********************************
// length vectors ecx-a void *, st(0)-rez double/float

/// Квадрат длинны двухмерного вектора одинарной точности, команды FPU
#define VECTORP2DLENGTH2FPU_CPP \
_BEGIN_ASM \
_LINE2( 0xD9,0x01 )                                         /* fld         dword ptr [ecx]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE3( 0xD9,0x41,0x04 )                                    /* fld         dword ptr [ecx+4]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// Квадрат длинны двухмерного вектора одинарной точности, команды SSE4
#define VECTORP2DLENGTH2SSE4_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x01 )                               /* movsd       xmm0,mmword ptr [ecx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC0,0x31 )                     /* dpps        xmm0,xmm0,31h  */ \
_LINE6( 0xF3,0x0F,0x11,0x44,0x24,0xDC )                     /* movss       dword ptr [esp-24h],xmm0  */ \
_LINE4( 0xD9,0x44,0x24,0xDC )                               /* fld         dword ptr [esp-24h]  */ \
_END_ASM

/// Квадрат длинны двухмерного вектора одинарной точности, команды FPU
#define VECTORP3DLENGTH2FPU_CPP \
_BEGIN_ASM \
_LINE2( 0xD9,0x01 )                                         /* fld         dword ptr [ecx]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE3( 0xD9,0x41,0x04 )                                    /* fld         dword ptr [ecx+4]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x41,0x08 )                                    /* fld         dword ptr [ecx+8]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// Квадрат длинны двухмерного вектора одинарной точности, команды SSE4
#define VECTORP3DLENGTH2SSE4_CPP \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x41,0x08 )                          /* movss       xmm0,dword ptr [ecx+8]  */ \
_LINE3( 0x0F,0x16,0x01 )                                    /* movhps      xmm0,qword ptr [ecx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC0,0xD1 )                     /* dpps        xmm0,xmm0,0D1h  */ \
_LINE6( 0xF3,0x0F,0x11,0x44,0x24,0xDC )                     /* movss       dword ptr [esp-24h],xmm0  */ \
_LINE4( 0xD9,0x44,0x24,0xDC )                               /* fld         dword ptr [esp-24h] */ \
_END_ASM

/// Квадрат длинны двухмерного вектора двойной точности, команды FPU
#define VECTORP2DDLENGTH2FPU_CPP \
_BEGIN_ASM \
_LINE2( 0xDD,0x01 )                                         /* fld         qword ptr [ecx]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE3( 0xDD,0x41,0x08 )                                    /* fld         qword ptr [ecx+8]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// Квадрат длинны двухмерного вектора двойной точности, команды SSE4
#define VECTORP2DDLENGTH2SSE4_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC0,0x31 )                     /* dppd        xmm0,xmm0,31h  */ \
_LINE6( 0xF2,0x0F,0x11,0x44,0x24,0xDC )                     /* movsd       mmword ptr [esp-24h],xmm0  */ \
_LINE4( 0xDD,0x44,0x24,0xDC )                               /* fld         qword ptr [esp-24h]  */ \
_END_ASM

/// Квадрат длинны трехмерного вектора двойной точности, команды FPU
#define VECTORP3DDLENGTH2FPU_CPP \
_BEGIN_ASM \
_LINE2( 0xDD,0x01 )                                         /* fld         qword ptr [ecx]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE3( 0xDD,0x41,0x08 )                                    /* fld         qword ptr [ecx+8]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x41,0x10 )                                    /* fld         qword ptr [ecx+10h]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// Квадрат длинны трехмерного вектора двойной точности, команды SSE4
#define VECTORP3DDLENGTH2SSE4_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC0,0x31 )                     /* dppd        xmm0,xmm0,31h  */ \
_LINE5( 0xF2,0x0F,0x10,0x51,0x10 )                          /* movsd       xmm2,mmword ptr [ecx+10h]  */ \
_LINE4( 0xF2,0x0F,0x59,0xD2 )                               /* mulsd       xmm2,xmm2  */ \
_LINE4( 0xF2,0x0F,0x58,0xC2 )                               /* addsd       xmm0,xmm2  */ \
_LINE6( 0xF2,0x0F,0x11,0x44,0x24,0xDC )                     /* movsd       mmword ptr [esp-24h],xmm0  */ \
_LINE4( 0xDD,0x44,0x24,0xDC )                               /* fld         qword ptr [esp-24h]  */ \
_END_ASM

#endif

