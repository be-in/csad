//=============================================================================
///**
// *  @file   vector_add.h
// *
// *  $Id: vector_distance.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float distance, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

// *********************************** DISTANCE REGISTER FASTCALL **************************************
// vector distance eax-a void *, edx-b void *; return double/float

/// ¬ычисление рассто€ни€ между двухмерными векторами одинарной точности, команды FPU
#define VECTORP2DDISTANCE2FPU \
_BEGIN_ASM \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0x22 )                                         /* fsub        dword ptr [edx]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x62,0x04 )                                    /* fsub        dword ptr [edx+4]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st */ \
_END_ASM

/// ¬ычисление рассто€ни€ между двухмерными векторами одинарной точности, команды SSE4
#define VECTORP2DDISTANCE2SSE4 \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,mmword ptr [edx]  */ \
_LINE3( 0x0F,0x5C,0xC1 )                                    /* subps       xmm0,xmm1  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC0,0x31 )                     /* dpps        xmm0,xmm0,31h  */ \
_LINE6( 0xF3,0x0F,0x11,0x44,0x24,0xDC )                     /* movss       dword ptr [esp-24h],xmm0  */ \
_LINE4( 0xD9,0x44,0x24,0xDC )                               /* fld         dword ptr [esp-24h]  */ \
_END_ASM

/// ¬ычисление рассто€ни€ между трехмерными векторами одинарной точности, команды FPU
#define VECTORP3DDISTANCE2FPU \
_BEGIN_ASM \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0x22 )                                         /* fsub        dword ptr [edx]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x62,0x04 )                                    /* fsub        dword ptr [edx+4]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD8,0x62,0x08 )                                    /* fsub        dword ptr [edx+8]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// ¬ычисление рассто€ни€ между трехмерными векторами одинарной точности, команды SSE4
#define VECTORP3DDISTANCE2SSE4 \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE3( 0x0F,0x16,0x00 )                                    /* movhps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x16,0x0A )                                    /* movhps      xmm1,qword ptr [edx]  */ \
_LINE3( 0x0F,0x5C,0xC1 )                                    /* subps       xmm0,xmm1  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC0,0xD1 )                     /* dpps        xmm0,xmm0,0D1h  */ \
_LINE6( 0xF3,0x0F,0x11,0x44,0x24,0xDC )                     /* movss       dword ptr [esp-24h],xmm0  */ \
_LINE4( 0xD9,0x44,0x24,0xDC )                               /* fld         dword ptr [esp-24h]  */ \
_END_ASM

/// ¬ычисление рассто€ни€ между двухмерными векторами двойной точности, команды FPU
#define VECTORP2DDDISTANCE2FPU \
_BEGIN_ASM \
_LINE2( 0xDD,0x00 )                                         /* fld         qword ptr [eax]  */ \
_LINE2( 0xDC,0x22 )                                         /* fsub        qword ptr [edx]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE3( 0xDD,0x40,0x08 )                                    /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDC,0x62,0x08 )                                    /* fsub        qword ptr [edx+8]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// ¬ычисление рассто€ни€ между двухмерными векторами двойной точности, команды SSE4
#define VECTORP2DDDISTANCE2SSE4 \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x66,0x0F,0x5C,0xC1 )                               /* subpd       xmm0,xmm1  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC0,0x31 )                     /* dppd        xmm0,xmm0,31h  */ \
_LINE6( 0xF2,0x0F,0x11,0x44,0x24,0xDC )                     /* movsd       mmword ptr [esp-24h],xmm0  */ \
_LINE4( 0xDD,0x44,0x24,0xDC )                               /* fld         qword ptr [esp-24h] */ \
_END_ASM

/// ¬ычисление рассто€ни€ между трехмерными векторами двойной точности, команды FPU
#define VECTORP3DDDISTANCE2FPU \
_BEGIN_ASM \
_LINE2( 0xDD,0x00 )                                         /* fld         qword ptr [eax]  */ \
_LINE2( 0xDC,0x22 )                                         /* fsub        qword ptr [edx]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE3( 0xDD,0x40,0x08 )                                    /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDC,0x62,0x08 )                                    /* fsub        qword ptr [edx+8]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x40,0x10 )                                    /* fld         qword ptr [eax+10h]  */ \
_LINE3( 0xDC,0x62,0x10 )                                    /* fsub        qword ptr [edx+10h]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// ¬ычисление рассто€ни€ между трехмерными векторами двойной точности, команды SSE4
#define VECTORP3DDDISTANCE2SSE4 \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x66,0x0F,0x5C,0xC1 )                               /* subpd       xmm0,xmm1  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC0,0x31 )                     /* dppd        xmm0,xmm0,31h  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x10 )                          /* movsd       xmm2,mmword ptr [eax+10h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x5A,0x10 )                          /* movsd       xmm3,mmword ptr [edx+10h]  */ \
_LINE4( 0x66,0x0F,0x5C,0xD3 )                               /* subpd       xmm2,xmm3  */ \
_LINE4( 0xF2,0x0F,0x59,0xD2 )                               /* mulsd       xmm2,xmm2  */ \
_LINE4( 0xF2,0x0F,0x58,0xC2 )                               /* addsd       xmm0,xmm2  */ \
_LINE6( 0xF2,0x0F,0x11,0x44,0x24,0xDC )                     /* movsd       mmword ptr [esp-24h],xmm0  */ \
_LINE4( 0xDD,0x44,0x24,0xDC )                               /* fld         qword ptr [esp-24h]  */ \
_END_ASM

// *********************************** DISTANCE CPP FASTCALL **************************************
// vector distance ecx-a void *, edx-b void *; return double/float

/// ¬ычисление рассто€ни€ между двухмерными векторами одинарной точности, команды FPU
#define VECTORP2DDISTANCE2FPU_CPP \
_BEGIN_ASM \
_LINE2( 0xD9,0x01 )                                         /* fld         dword ptr [ecx]  */ \
_LINE2( 0xD8,0x22 )                                         /* fsub        dword ptr [edx]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE3( 0xD9,0x41,0x04 )                                    /* fld         dword ptr [ecx+4]  */ \
_LINE3( 0xD8,0x62,0x04 )                                    /* fsub        dword ptr [edx+4]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// ¬ычисление рассто€ни€ между двухмерными векторами одинарной точности, команды SSE4
#define VECTORP2DDISTANCE2SSE4_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0x10,0x01 )                               /* movsd       xmm0,mmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0x10,0x0A )                               /* movsd       xmm1,mmword ptr [edx]  */ \
_LINE3( 0x0F,0x5C,0xC1 )                                    /* subps       xmm0,xmm1  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC0,0x31 )                     /* dpps        xmm0,xmm0,31h  */ \
_LINE6( 0xF3,0x0F,0x11,0x44,0x24,0xDC )                     /* movss       dword ptr [esp-24h],xmm0  */ \
_LINE4( 0xD9,0x44,0x24,0xDC )                               /* fld         dword ptr [esp-24h]  */ \
_END_ASM

/// ¬ычисление рассто€ни€ между трехмерными векторами одинарной точности, команды FPU
#define VECTORP3DDISTANCE2FPU_CPP \
_BEGIN_ASM \
_LINE2( 0xD9,0x01 )                                         /* fld         dword ptr [ecx]  */ \
_LINE2( 0xD8,0x22 )                                         /* fsub        dword ptr [edx]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE3( 0xD9,0x41,0x04 )                                    /* fld         dword ptr [ecx+4]  */ \
_LINE3( 0xD8,0x62,0x04 )                                    /* fsub        dword ptr [edx+4]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x41,0x08 )                                    /* fld         dword ptr [ecx+8]  */ \
_LINE3( 0xD8,0x62,0x08 )                                    /* fsub        dword ptr [edx+8]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// ¬ычисление рассто€ни€ между трехмерными векторами одинарной точности, команды SSE4
#define VECTORP3DDISTANCE2SSE4_CPP \
_BEGIN_ASM \
_LINE5( 0xF3,0x0F,0x10,0x41,0x08 )                          /* movss       xmm0,dword ptr [ecx+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x4A,0x08 )                          /* movss       xmm1,dword ptr [edx+8]  */ \
_LINE3( 0x0F,0x16,0x01 )                                    /* movhps      xmm0,qword ptr [ecx]  */ \
_LINE3( 0x0F,0x16,0x0A )                                    /* movhps      xmm1,qword ptr [edx]  */ \
_LINE3( 0x0F,0x5C,0xC1 )                                    /* subps       xmm0,xmm1  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC0,0xD1 )                     /* dpps        xmm0,xmm0,0D1h  */ \
_LINE6( 0xF3,0x0F,0x11,0x44,0x24,0xDC )                     /* movss       dword ptr [esp-24h],xmm0  */ \
_LINE4( 0xD9,0x44,0x24,0xDC )                               /* fld         dword ptr [esp-24h]  */ \
_END_ASM

/// ¬ычисление рассто€ни€ между двухмерными векторами двойной точности, команды FPU
#define VECTORP2DDDISTANCE2FPU_CPP \
_BEGIN_ASM \
_LINE2( 0xDD,0x01 )                                         /* fld         qword ptr [ecx]  */ \
_LINE2( 0xDC,0x22 )                                         /* fsub        qword ptr [edx]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE3( 0xDD,0x41,0x08 )                                    /* fld         qword ptr [ecx+8]  */ \
_LINE3( 0xDC,0x62,0x08 )                                    /* fsub        qword ptr [edx+8]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// ¬ычисление рассто€ни€ между двухмерными векторами двойной точности, команды SSE4
#define VECTORP2DDDISTANCE2SSE4_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x66,0x0F,0x5C,0xC1 )                               /* subpd       xmm0,xmm1  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC0,0x31 )                     /* dppd        xmm0,xmm0,31h  */ \
_LINE6( 0xF2,0x0F,0x11,0x44,0x24,0xDC )                     /* movsd       mmword ptr [esp-24h],xmm0  */ \
_LINE4( 0xDD,0x44,0x24,0xDC )                               /* fld         qword ptr [esp-24h]  */ \
_END_ASM

/// ¬ычисление рассто€ни€ между трехмерными векторами двойной точности, команды FPU
#define VECTORP3DDDISTANCE2FPU_CPP \
_BEGIN_ASM \
_LINE2( 0xDD,0x01 )                                         /* fld         qword ptr [ecx]  */ \
_LINE2( 0xDC,0x22 )                                         /* fsub        qword ptr [edx]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE3( 0xDD,0x41,0x08 )                                    /* fld         qword ptr [ecx+8]  */ \
_LINE3( 0xDC,0x62,0x08 )                                    /* fsub        qword ptr [edx+8]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x41,0x10 )                                    /* fld         qword ptr [ecx+10h]  */ \
_LINE3( 0xDC,0x62,0x10 )                                    /* fsub        qword ptr [edx+10h]  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_END_ASM

/// ¬ычисление рассто€ни€ между трехмерными векторами двойной точности, команды SSE4
#define VECTORP3DDDISTANCE2SSE4_CPP \
_BEGIN_ASM \
_LINE4( 0xF2,0x0F,0xF0,0x01 )                               /* lddqu       xmm0,xmmword ptr [ecx]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x0A )                               /* lddqu       xmm1,xmmword ptr [edx]  */ \
_LINE4( 0x66,0x0F,0x5C,0xC1 )                               /* subpd       xmm0,xmm1  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC0,0x31 )                     /* dppd        xmm0,xmm0,31h  */ \
_LINE5( 0xF2,0x0F,0x10,0x51,0x10 )                          /* movsd       xmm2,mmword ptr [ecx+10h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x5A,0x10 )                          /* movsd       xmm3,mmword ptr [edx+10h]  */ \
_LINE4( 0x66,0x0F,0x5C,0xD3 )                               /* subpd       xmm2,xmm3  */ \
_LINE4( 0xF2,0x0F,0x59,0xD2 )                               /* mulsd       xmm2,xmm2  */ \
_LINE4( 0xF2,0x0F,0x58,0xC2 )                               /* addsd       xmm0,xmm2  */ \
_LINE6( 0xF2,0x0F,0x11,0x44,0x24,0xDC )                     /* movsd       mmword ptr [esp-24h],xmm0  */ \
_LINE4( 0xDD,0x44,0x24,0xDC )                               /* fld         qword ptr [esp-24h]  */ \
_END_ASM