//=============================================================================
///**
// *  @file quaternion_matrix.h
// *
// *  $Id: quaternion_matrix.h 16.10.2011  $
// *
// *  @brief generator 3, assembler quaternion double/float matrix, MS Visual C++ 2003-2008
// *
// *  @author Pant_eleymonov Alek_sandr Kons_tantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_QUATERNION_MATRIX_H
#define GEN3_QUATERNION_MATRIX_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** MATRIX STDCALL *********************************
// quaternion to matrix eax=[esp+4]-a void *, [esp+8]-b void *

/// Преобразование кватерниона в матрицу одинарной точности, команды SSE
#define QUATERNIONP4DMATRIXSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )          /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )          /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x12,0x00 )               /* movlps      xmm0,qword ptr [eax]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )          /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE3( 0x0F,0x28,0xC8 )               /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x59,0xC9 )               /* mulps       xmm1,xmm1  */ \
_LINE3( 0x0F,0x12,0xD1 )               /* movhlps     xmm2,xmm1  */ \
_LINE3( 0x0F,0x58,0xD1 )               /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x28,0xCA )               /* movaps      xmm1,xmm2  */ \
_LINE4( 0x0F,0xC6,0xC9,0x01 )          /* shufps      xmm1,xmm1,1  */ \
_LINE4( 0xF3,0x0F,0x58,0xD1 )          /* addss       xmm2,xmm1  */ \
_LINE5( 0xB8,0x02,0x00,0x00,0x00 )     /* mov         eax,2  */ \
_LINE3( 0x0F,0x57,0xFF )               /* xorps       xmm7,xmm7  */ \
_LINE4( 0xF3,0x0F,0x2A,0xC8 )          /* cvtsi2ss    xmm1,eax  */ \
_LINE5( 0xB8,0x01,0x00,0x00,0x00 )     /* mov         eax,1  */ \
_LINE4( 0xF3,0x0F,0x2A,0xF8 )          /* cvtsi2ss    xmm7,eax  */ \
_LINE4( 0xF3,0x0F,0x5E,0xCA )          /* divss       xmm1,xmm2  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )          /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x28,0xD8 )               /* movaps      xmm3,xmm0  */ \
_LINE3( 0x0F,0x59,0xD9 )               /* mulps       xmm3,xmm1  */ \
_LINE3( 0x0F,0x28,0xD0 )               /* movaps      xmm2,xmm0  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )          /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x28,0xCB )               /* movaps      xmm1,xmm3  */ \
_LINE3( 0x0F,0x59,0xCA )               /* mulps       xmm1,xmm2  */ \
_LINE3( 0x0F,0x28,0xE3 )               /* movaps      xmm4,xmm3  */ \
_LINE4( 0x0F,0xC6,0xE4,0xE9 )          /* shufps      xmm4,xmm4,0E9h  */ \
_LINE4( 0x0F,0xC6,0xC0,0xE5 )          /* shufps      xmm0,xmm0,0E5h  */ \
_LINE3( 0x0F,0x59,0xE0 )               /* mulps       xmm4,xmm0  */ \
_LINE4( 0x0F,0xC6,0xC0,0xFF )          /* shufps      xmm0,xmm0,0FFh  */ \
_LINE3( 0x0F,0x59,0xC3 )               /* mulps       xmm0,xmm3  */ \
_LINE3( 0x0F,0x28,0xD9 )               /* movaps      xmm3,xmm1  */ \
_LINE4( 0x0F,0xC6,0xDC,0x00 )          /* shufps      xmm3,xmm4,0  */ \
_LINE4( 0x0F,0xC6,0xCC,0x59 )          /* shufps      xmm1,xmm4,59h  */ \
_LINE4( 0x0F,0xC6,0xC0,0x06 )          /* shufps      xmm0,xmm0,6  */ \
_LINE4( 0x0F,0xC6,0xE4,0xA8 )          /* shufps      xmm4,xmm4,0A8h  */ \
_LINE3( 0x0F,0x28,0xD1 )               /* movaps      xmm2,xmm1  */ \
_LINE3( 0x0F,0x58,0xC8 )               /* addps       xmm1,xmm0  */ \
_LINE3( 0x0F,0x5C,0xD0 )               /* subps       xmm2,xmm0  */ \
_LINE3( 0x0F,0x28,0xEF )               /* movaps      xmm5,xmm7  */ \
_LINE4( 0x0F,0xC6,0xED,0x40 )          /* shufps      xmm5,xmm5,40h  */ \
_LINE3( 0x0F,0x58,0xE3 )               /* addps       xmm4,xmm3  */ \
_LINE3( 0x0F,0x5C,0xEC )               /* subps       xmm5,xmm4  */ \
_LINE3( 0x0F,0x28,0xF5 )               /* movaps      xmm6,xmm5  */ \
_LINE4( 0x0F,0xC6,0xF7,0xF2 )          /* shufps      xmm6,xmm7,0F2h  */ \
_LINE4( 0x0F,0xC6,0xE9,0x81 )          /* shufps      xmm5,xmm1,81h  */ \
_LINE3( 0x0F,0x28,0xE2 )               /* movaps      xmm4,xmm2  */ \
_LINE4( 0x0F,0xC6,0xE7,0xF2 )          /* shufps      xmm4,xmm7,0F2h  */ \
_LINE4( 0x0F,0xC6,0xD1,0x91 )          /* shufps      xmm2,xmm1,91h  */ \
_LINE4( 0x0F,0xC6,0xEC,0x82 )          /* shufps      xmm5,xmm4,82h  */ \
_LINE4( 0x0F,0xC6,0xE6,0x85 )          /* shufps      xmm4,xmm6,85h  */ \
_LINE4( 0x0F,0xC6,0xF2,0xC9 )          /* shufps      xmm6,xmm2,0C9h  */ \
_LINE4( 0x0F,0xC6,0xD4,0xFA )          /* shufps      xmm2,xmm4,0FAh  */ \
_LINE4( 0x0F,0xC6,0xE2,0x82 )          /* shufps      xmm4,xmm2,82h  */ \
_LINE4( 0x0F,0xC6,0xF6,0x4E )          /* shufps      xmm6,xmm6,4Eh  */ \
_LINE4( 0x0F,0xC6,0xFF,0x15 )          /* shufps      xmm7,xmm7,15h  */ \
_LINE3( 0x0F,0x13,0x22 )               /* movlps      qword ptr [edx],xmm4  */ \
_LINE4( 0x0F,0x13,0x6A,0x10 )          /* movlps      qword ptr [edx+10h],xmm5  */ \
_LINE4( 0x0F,0x17,0x62,0x08 )          /* movhps      qword ptr [edx+8],xmm4  */ \
_LINE4( 0x0F,0x17,0x6A,0x18 )          /* movhps      qword ptr [edx+18h],xmm5  */ \
_LINE4( 0x0F,0x13,0x72,0x20 )          /* movlps      qword ptr [edx+20h],xmm6  */ \
_LINE4( 0x0F,0x13,0x7A,0x30 )          /* movlps      qword ptr [edx+30h],xmm7  */ \
_LINE4( 0x0F,0x17,0x72,0x28 )          /* movhps      qword ptr [edx+28h],xmm6  */ \
_LINE4( 0x0F,0x17,0x7A,0x38 )          /* movhps      qword ptr [edx+38h],xmm7  */ \
_END_ASM

/// Преобразование кватерниона в матрицу одинарной точности, команды SSE4
#define QUATERNIONP4DMATRIXSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )          /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )          /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )          /* lddqu       xmm0,[eax]  */ \
_LINE3( 0x0F,0x28,0xD0 )               /* movaps      xmm2,xmm0  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xD2,0xF1 )                     /* dpps        xmm2,xmm2,0F1h  */ \
_LINE5( 0xB8,0x02,0x00,0x00,0x00 )     /* mov         eax,2  */ \
_LINE3( 0x0F,0x57,0xFF )               /* xorps       xmm7,xmm7  */ \
_LINE4( 0xF3,0x0F,0x2A,0xC8 )          /* cvtsi2ss    xmm1,eax  */ \
_LINE5( 0xB8,0x01,0x00,0x00,0x00 )     /* mov         eax,1  */ \
_LINE4( 0xF3,0x0F,0x2A,0xF8 )          /* cvtsi2ss    xmm7,eax  */ \
_LINE4( 0xF3,0x0F,0x5E,0xCA )          /* divss       xmm1,xmm2  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )          /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x28,0xD8 )               /* movaps      xmm3,xmm0  */ \
_LINE3( 0x0F,0x59,0xD9 )               /* mulps       xmm3,xmm1  */ \
_LINE3( 0x0F,0x28,0xD0 )               /* movaps      xmm2,xmm0  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )          /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x28,0xCB )               /* movaps      xmm1,xmm3  */ \
_LINE3( 0x0F,0x59,0xCA )               /* mulps       xmm1,xmm2  */ \
_LINE3( 0x0F,0x28,0xE3 )               /* movaps      xmm4,xmm3  */ \
_LINE4( 0x0F,0xC6,0xE4,0xE9 )          /* shufps      xmm4,xmm4,0E9h  */ \
_LINE4( 0x0F,0xC6,0xC0,0xE5 )          /* shufps      xmm0,xmm0,0E5h  */ \
_LINE3( 0x0F,0x59,0xE0 )               /* mulps       xmm4,xmm0  */ \
_LINE4( 0x0F,0xC6,0xC0,0xFF )          /* shufps      xmm0,xmm0,0FFh  */ \
_LINE3( 0x0F,0x59,0xC3 )               /* mulps       xmm0,xmm3  */ \
_LINE3( 0x0F,0x28,0xD9 )               /* movaps      xmm3,xmm1  */ \
_LINE4( 0x0F,0xC6,0xDC,0x00 )          /* shufps      xmm3,xmm4,0  */ \
_LINE4( 0x0F,0xC6,0xCC,0x59 )          /* shufps      xmm1,xmm4,59h  */ \
_LINE4( 0x0F,0xC6,0xC0,0x06 )          /* shufps      xmm0,xmm0,6  */ \
_LINE4( 0x0F,0xC6,0xE4,0xA8 )          /* shufps      xmm4,xmm4,0A8h  */ \
_LINE3( 0x0F,0x28,0xD1 )               /* movaps      xmm2,xmm1  */ \
_LINE3( 0x0F,0x58,0xC8 )               /* addps       xmm1,xmm0  */ \
_LINE3( 0x0F,0x5C,0xD0 )               /* subps       xmm2,xmm0  */ \
_LINE3( 0x0F,0x28,0xEF )               /* movaps      xmm5,xmm7  */ \
_LINE4( 0x0F,0xC6,0xED,0x40 )          /* shufps      xmm5,xmm5,40h  */ \
_LINE3( 0x0F,0x58,0xE3 )               /* addps       xmm4,xmm3  */ \
_LINE3( 0x0F,0x5C,0xEC )               /* subps       xmm5,xmm4  */ \
_LINE3( 0x0F,0x28,0xF5 )               /* movaps      xmm6,xmm5  */ \
_LINE4( 0x0F,0xC6,0xF7,0xF2 )          /* shufps      xmm6,xmm7,0F2h  */ \
_LINE4( 0x0F,0xC6,0xE9,0x81 )          /* shufps      xmm5,xmm1,81h  */ \
_LINE3( 0x0F,0x28,0xE2 )               /* movaps      xmm4,xmm2  */ \
_LINE4( 0x0F,0xC6,0xE7,0xF2 )          /* shufps      xmm4,xmm7,0F2h  */ \
_LINE4( 0x0F,0xC6,0xD1,0x91 )          /* shufps      xmm2,xmm1,91h  */ \
_LINE4( 0x0F,0xC6,0xEC,0x82 )          /* shufps      xmm5,xmm4,82h  */ \
_LINE4( 0x0F,0xC6,0xE6,0x85 )          /* shufps      xmm4,xmm6,85h  */ \
_LINE4( 0x0F,0xC6,0xF2,0xC9 )          /* shufps      xmm6,xmm2,0C9h  */ \
_LINE4( 0x0F,0xC6,0xD4,0xFA )          /* shufps      xmm2,xmm4,0FAh  */ \
_LINE4( 0x0F,0xC6,0xE2,0x82 )          /* shufps      xmm4,xmm2,82h  */ \
_LINE4( 0x0F,0xC6,0xF6,0x4E )          /* shufps      xmm6,xmm6,4Eh  */ \
_LINE4( 0x0F,0xC6,0xFF,0x15 )          /* shufps      xmm7,xmm7,15h  */ \
_LINE3( 0x0F,0x11,0x22 )               /* movups      xmmword ptr [edx],xmm4  */ \
_LINE4( 0x0F,0x11,0x6A,0x10 )          /* movups      xmmword ptr [edx+10h],xmm5  */ \
_LINE4( 0x0F,0x11,0x72,0x20 )          /* movups      xmmword ptr [edx+30h],xmm6  */ \
_LINE4( 0x0F,0x11,0x7A,0x30 )          /* movups      xmmword ptr [edx+30h],xmm7  */ \
_END_ASM

/// Преобразование кватерниона в матрицу двойной точности, команды SSE4
#define QUATERNIONP4DDMATRIXSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE5( 0xF2,0x0F,0xF0,0x50,0x10 )                          /* lddqu       xmm2,xmmword ptr [eax+10h]  */ \
_LINE3( 0x0F,0x28,0xDA )                                    /* movaps      xmm3,xmm2  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC9,0x31 )                     /* dppd        xmm1,xmm1,31h  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xDB,0x31 )                     /* dppd        xmm3,xmm3,31h  */ \
_LINE4( 0xF2,0x0F,0x58,0xCB )                               /* addsd       xmm1,xmm3  */ \
_LINE5( 0xB8,0x02,0x00,0x00,0x00 )                          /* mov         eax,2  */ \
_LINE4( 0xF2,0x0F,0x2A,0xE0 )                               /* cvtsi2sd    xmm4,eax  */ \
_LINE3( 0x0F,0x28,0xF0 )                                    /* movaps      xmm6,xmm0  */ \
_LINE4( 0xF2,0x0F,0x5E,0xE1 )                               /* divsd       xmm4,xmm1  */ \
_LINE3( 0x0F,0x28,0xFA )                                    /* movaps      xmm7,xmm2  */ \
_LINE3( 0x0F,0x16,0xE4 )                                    /* movlhps     xmm4,xmm4  */ \
_LINE3( 0x0F,0x12,0xC8 )                                    /* movhlps     xmm1,xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xF4 )                               /* mulpd       xmm6,xmm4  */ \
_LINE3( 0x0F,0x16,0xCA )                                    /* movlhps     xmm1,xmm2  */ \
_LINE4( 0x66,0x0F,0x59,0xFC )                               /* mulpd       xmm7,xmm4  */ \
_LINE3( 0x0F,0x12,0xDE )                                    /* movhlps     xmm3,xmm6  */ \
_LINE3( 0x0F,0x28,0xE0 )                                    /* movaps      xmm4,xmm0  */ \
_LINE5( 0xB8,0x01,0x00,0x00,0x00 )                          /* mov         eax,1  */ \
_LINE3( 0x0F,0x16,0xDF )                                    /* movlhps     xmm3,xmm7  */ \
_LINE4( 0xF2,0x0F,0x59,0xE6 )                               /* mulsd       xmm4,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xD9 )                               /* mulpd       xmm3,xmm1  */ \
_LINE4( 0xF2,0x0F,0x2A,0xE8 )                               /* cvtsi2sd    xmm5,eax  */ \
_LINE3( 0x0F,0x16,0xE4 )                                    /* movlhps     xmm4,xmm4  */ \
_LINE3( 0x0F,0x16,0xED )                                    /* movlhps     xmm5,xmm5  */ \
_LINE4( 0x66,0x0F,0x58,0xE3 )                               /* addpd       xmm4,xmm3  */ \
_LINE3( 0x0F,0x28,0xC5 )                                    /* movaps      xmm0,xmm5  */ \
_LINE4( 0x66,0x0F,0x5C,0xEC )                               /* subpd       xmm5,xmm4  */ \
_LINE3( 0x0F,0x12,0xFF )                                    /* movhlps     xmm7,xmm7  */ \
_LINE3( 0x0F,0x16,0xE6 )                                    /* movlhps     xmm4,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xF9 )                               /* mulpd       xmm7,xmm1  */ \
_LINE3( 0x0F,0x12,0xE6 )                                    /* movhlps     xmm4,xmm6  */ \
_LINE5( 0xF2,0x0F,0x11,0x6A,0x50 )                          /* movsd       mmword ptr [edx+50h],xmm5  */ \
_LINE4( 0x66,0x0F,0x59,0xE2 )                               /* mulpd       xmm4,xmm2  */ \
_LINE3( 0x0F,0x16,0xF6 )                                    /* movlhps     xmm6,xmm6  */ \
_LINE4( 0x66,0x0F,0x7C,0xDC )                               /* haddpd      xmm3,xmm4  */ \
_LINE4( 0x0F,0x17,0x6A,0x28 )                               /* movhps      qword ptr [edx+28h],xmm5  */ \
_LINE4( 0x66,0x0F,0x7D,0xE4 )                               /* hsubpd      xmm4,xmm4  */ \
_LINE4( 0xF2,0x0F,0x5C,0xC3 )                               /* subsd       xmm0,xmm3  */ \
_LINE4( 0x66,0x0F,0x59,0xF1 )                               /* mulpd       xmm6,xmm1  */ \
_LINE4( 0xF2,0x0F,0x11,0x02 )                               /* movsd       mmword ptr [edx],xmm0  */ \
_LINE3( 0x0F,0x16,0xD6 )                                    /* movlhps     xmm2,xmm6  */ \
_LINE4( 0x0F,0x17,0x42,0x78 )                               /* movhps      qword ptr [edx+78h],xmm0  */ \
_LINE3( 0x0F,0x12,0xD6 )                                    /* movhlps     xmm2,xmm6  */ \
_LINE4( 0x0F,0x17,0x5A,0x48 )                               /* movhps      qword ptr [edx+48h],xmm3  */ \
_LINE3( 0x0F,0x28,0xF2 )                                    /* movaps      xmm6,xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x62,0x30 )                          /* movsd       mmword ptr [edx+30h],xmm4  */ \
_LINE4( 0x66,0x0F,0x5C,0xD7 )                               /* subpd       xmm2,xmm7  */ \
_LINE4( 0x66,0x0F,0x58,0xF7 )                               /* addpd       xmm6,xmm7  */ \
_LINE5( 0xF2,0x0F,0x11,0x52,0x40 )                          /* movsd       mmword ptr [edx+40h],xmm2  */ \
_LINE5( 0xF2,0x0F,0x11,0x72,0x10 )                          /* movsd       mmword ptr [edx+10h],xmm6  */ \
_LINE4( 0x0F,0x17,0x52,0x08 )                               /* movhps      qword ptr [edx+8],xmm2  */ \
_LINE4( 0x0F,0x17,0x72,0x20 )                               /* movhps      qword ptr [edx+20h],xmm6  */ \
_LINE3( 0x0F,0x57,0xFF )                                    /* xorps       xmm7,xmm7  */ \
_LINE5( 0x66,0x0F,0x11,0x7A,0x58 )                          /* movupd      xmmword ptr [edx+58h],xmm7  */ \
_LINE5( 0x66,0x0F,0x11,0x7A,0x68 )                          /* movupd      xmmword ptr [edx+68h],xmm7  */ \
_LINE5( 0xF2,0x0F,0x11,0x7A,0x18 )                          /* movsd       mmword ptr [edx+18h],xmm7  */ \
_LINE5( 0xF2,0x0F,0x11,0x7A,0x38 )                          /* movsd       mmword ptr [edx+38h],xmm7 */ \
_END_ASM

#endif