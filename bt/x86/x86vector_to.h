//=============================================================================
///**
// *  @file vector_to.h
// *
// *  $Id: vector_to.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector and matrix double/float conversion, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_VECTOR_TO_H
#define GEN3_VECTOR_TO_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium M, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** COPY STDCALL *********************************

/// Копирование трехмерного вектора двойной точности, команды SSE3.
/// @brief for CPUTYPE4
#define VECTORP3DDCOPYSSE3_STD \
_BEGIN_ASM \
_LINE4(0x8B, 0x44, 0x24, 0x04)                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4(0xF2, 0x0F, 0xF0, 0x00)                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4(0x8B, 0x54, 0x24, 0x08)                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5(0xF2, 0x0F, 0x10, 0x48, 0x10)                         /* movsd       xmm1,mmword ptr [eax+10h]  */ \
_LINE4(0x66, 0x0F, 0x11, 0x02)                               /* movupd      xmmword ptr [edx],xmm0  */ \
_LINE5(0xF2, 0x0F, 0x11, 0x4A, 0x10)                         /* movsd       mmword ptr [edx+10h],xmm1  */ \
_END_ASM

/// Копирование четырехмерного вектора двойной точности, команды SSE3.
/// @brief for CPUTYPE4
#define VECTORP4DDCOPYSSE3_STD \
_BEGIN_ASM \
_LINE4(0x8B, 0x44, 0x24, 0x04)                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4(0xF2, 0x0F, 0xF0, 0x00)                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4(0x8B, 0x54, 0x24, 0x08)                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5(0xF2, 0x0F, 0xF0, 0x48, 0x10)                         /* lddqu       xmm1,[eax+10h]  */ \
_LINE4(0x66, 0x0F, 0x11, 0x02)                               /* movupd      xmmword ptr [edx],xmm0  */ \
_LINE5(0x66, 0x0F, 0x11, 0x4A, 0x10)                         /* movupd      xmmword ptr [edx+10h],xmm0  */ \
_END_ASM

//**************************** TO STDCALL *********************************
// to vectors eax=[esp+4]-a void *, edx=[esp+8]-b void *

/// Преобразование двухмерного вектора байт в вектор одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP2BTO2DSSE_STD \
_BEGIN_ASM \
_LINE2( 0x33,0xC0 )                   /* xor         eax,eax  */ \
_LINE2( 0x33,0xC9 )                   /* xor         ecx,ecx  */ \
_LINE4( 0x8B,0x54,0x24,0x04 )         /* mov         edx,dword ptr [esp+4]  */ \
_LINE2( 0x8A,0x02 )                   /* mov         al,byte ptr [edx]  */ \
_LINE4( 0xF3,0x0F,0x2A,0xC0 )         /* cvtsi2ss    xmm0,eax  */ \
_LINE3( 0x8A,0x4A,0x01 )              /* mov         cl,byte ptr [edx+1]  */ \
_LINE4( 0xF3,0x0F,0x2A,0xC9 )         /* cvtsi2ss    xmm1,ecx  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )         /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0xF3,0x0F,0x11,0x00 )         /* movss       dword ptr [eax],xmm0 */ \
_LINE5( 0xF3,0x0F,0x11,0x48,0x04 )    /* movss       dword ptr [eax+4],xmm1 */ \
_END_ASM

/// Преобразование трехмерного вектора байт в вектор одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP3BTO3DSSE_STD \
_BEGIN_ASM \
_LINE2( 0x33,0xC0 )                   /* xor         eax,eax  */ \
_LINE2( 0x33,0xC9 )                   /* xor         ecx,ecx  */ \
_LINE4( 0x8B,0x54,0x24,0x04 )         /* mov         edx,dword ptr [esp+4]  */ \
_LINE2( 0x8A,0x0A )                   /* mov         cl,byte ptr [edx]  */ \
_LINE4( 0xF3,0x0F,0x2A,0xC1 )         /* cvtsi2ss    xmm0,ecx  */ \
_LINE3( 0x8A,0x42,0x01 )              /* mov         al,byte ptr [edx+1]  */ \
_LINE4( 0xF3,0x0F,0x2A,0xC8 )         /* cvtsi2ss    xmm1,eax  */ \
_LINE3( 0x8A,0x4A,0x02 )              /* mov         cl,byte ptr [edx+2]  */ \
_LINE4( 0xF3,0x0F,0x2A,0xD1 )         /* cvtsi2ss    xmm2,ecx  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )         /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0xF3,0x0F,0x11,0x00 )         /* movss       dword ptr [eax],xmm0 */ \
_LINE5( 0xF3,0x0F,0x11,0x48,0x04 )    /* movss       dword ptr [eax+4],xmm1 */ \
_LINE5( 0xF3,0x0F,0x11,0x50,0x08 )    /* movss       dword ptr [eax+8],xmm2 */ \
_END_ASM

/// Преобразование четырехмерного вектора байт в вектор одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP4BTO4DSSE_STD \
_BEGIN_ASM \
_LINE2( 0x33,0xC0 )                   /* xor         eax,eax  */ \
_LINE2( 0x33,0xC9 )                   /* xor         ecx,ecx  */ \
_LINE4( 0x8B,0x54,0x24,0x04 )         /* mov         edx,dword ptr [esp+4]  */ \
_LINE2( 0x8A,0x02 )                   /* mov         al,byte ptr [edx]  */ \
_LINE4( 0xF3,0x0F,0x2A,0xC0 )         /* cvtsi2ss    xmm0,eax  */ \
_LINE3( 0x8A,0x4A,0x01 )              /* mov         cl,byte ptr [edx+1]  */ \
_LINE4( 0xF3,0x0F,0x2A,0xC9 )         /* cvtsi2ss    xmm1,ecx  */ \
_LINE3( 0x8A,0x42,0x02 )              /* mov         al,byte ptr [edx+2]  */ \
_LINE4( 0xF3,0x0F,0x2A,0xC8 )         /* cvtsi2ss    xmm1,eax  */ \
_LINE3( 0x8A,0x4A,0x03 )              /* mov         cl,byte ptr [edx+3]  */ \
_LINE4( 0xF3,0x0F,0x2A,0xD1 )         /* cvtsi2ss    xmm2,ecx  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )         /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0xF3,0x0F,0x11,0x00 )         /* movss       dword ptr [eax],xmm0 */ \
_LINE5( 0xF3,0x0F,0x11,0x48,0x04 )    /* movss       dword ptr [eax+4],xmm1 */ \
_LINE5( 0xF3,0x0F,0x11,0x50,0x08 )    /* movss       dword ptr [eax+8],xmm2 */ \
_LINE5( 0xF3,0x0F,0x11,0x58,0x0C )    /* movss       dword ptr [eax+12],xmm3 */ \
_END_ASM

/// Преобразование двухмерного вектора байт в вектор двойной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP2BTO2DDSSE2_STD \
_BEGIN_ASM \
_LINE2( 0x33,0xC0 )                  /* xor         eax,eax  */ \
_LINE2( 0x33,0xC9 )                  /* xor         ecx,ecx  */ \
_LINE4( 0x8B,0x54,0x24,0x04 )        /* mov         edx,dword ptr [esp+4]  */ \
_LINE2( 0x8A,0x02 )                  /* mov         al,byte ptr [edx]  */ \
_LINE4( 0xF2,0x0F,0x2A,0xC0 )        /* cvtsi2sd    xmm0,eax  */ \
_LINE3( 0x8A,0x4A,0x01 )             /* mov         cl,byte ptr [edx+1]  */ \
_LINE4( 0xF2,0x0F,0x2A,0xC9 )        /* cvtsi2sd    xmm1,ecx  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )        /* mov         eax,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x13,0x00 )             /* movlps      qword ptr [eax],xmm0  */ \
_LINE4( 0x0F,0x13,0x48,0x08 )        /* movlps      qword ptr [eax+8],xmm1  */ \
_END_ASM

/// Преобразование трехмерного вектора байт в вектор двойной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP3BTO3DDSSE2_STD \
_BEGIN_ASM \
_LINE2( 0x33,0xC0 )                  /* xor         eax,eax  */ \
_LINE2( 0x33,0xC9 )                  /* xor         ecx,ecx  */ \
_LINE4( 0x8B,0x54,0x24,0x04 )        /* mov         edx,dword ptr [esp+4]  */ \
ASM( mov cl,byte ptr [edx] ) \
ASM( cvtsi2sd    xmm0,ecx )                    /* cvtsi2ss    xmm0,eax */ \
ASM( mov al,byte ptr [edx+1] ) \
ASM( cvtsi2sd    xmm1,eax )                    /* cvtsi2ss    xmm1,eax */ \
ASM( mov cl,byte ptr [edx+2] ) \
ASM( cvtsi2sd    xmm2,ecx )                    /* cvtsi2ss    xmm2,eax */ \
_LINE4( 0x8B,0x44,0x24,0x08 )        /* mov         eax,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x13,0x00 )             /* movlps      qword ptr [eax],xmm0  */ \
_LINE4( 0x0F,0x13,0x48,0x08 )        /* movlps      qword ptr [eax+8],xmm1  */ \
_LINE4( 0x0F,0x13,0x50,0x10 )        /* movlps      qword ptr [eax+0x10],xmm2  */ \
_END_ASM

/// Преобразование четырехмерного вектора байт в вектор двойной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP4BTO4DDSSE2_STD \
_BEGIN_ASM \
_LINE2( 0x33,0xC0 )                  /* xor         eax,eax  */ \
_LINE2( 0x33,0xC9 )                  /* xor         ecx,ecx  */ \
_LINE4( 0x8B,0x54,0x24,0x04 )        /* mov         edx,dword ptr [esp+4]  */ \
_LINE2( 0x8A,0x02 )                  /* mov         al,byte ptr [edx]  */ \
_LINE4( 0xF2,0x0F,0x2A,0xC0 )        /* cvtsi2sd    xmm0,eax  */ \
_LINE3( 0x8A,0x4A,0x01 )             /* mov         cl,byte ptr [edx+1]  */ \
_LINE4( 0xF2,0x0F,0x2A,0xC9 )        /* cvtsi2sd    xmm1,ecx  */ \
_LINE3( 0x8A,0x42,0x02 )             /* mov         al,byte ptr [edx+2]  */ \
_LINE4( 0xF2,0x0F,0x2A,0xD0 )        /* cvtsi2sd    xmm2,eax  */ \
_LINE3( 0x8A,0x4A,0x03 )             /* mov         cl,byte ptr [edx+3]  */ \
_LINE4( 0xF2,0x0F,0x2A,0xD9 )        /* cvtsi2sd    xmm3,ecx  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )        /* mov         eax,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x13,0x00 )             /* movlps      qword ptr [eax],xmm0  */ \
_LINE4( 0x0F,0x13,0x48,0x08 )        /* movlps      qword ptr [eax+8],xmm1  */ \
_LINE4( 0x0F,0x13,0x50,0x10 )        /* movlps      qword ptr [eax+0x10],xmm2  */ \
_LINE4( 0x0F,0x13,0x58,0x18 )        /* movlps      qword ptr [eax+0x18],xmm3  */ \
_END_ASM


/// Преобразование четырехмерного вектора байт в вектор двойной точности, команды SSE3.
/// @brief for CPUTYPE4
#define VECTORP4BTO4DSSE3_STD \
_BEGIN_ASM \
ASM( xorps xmm1,xmm1 ) \
_LINE4( 0x8B,0x44,0x24,0x04 )                        /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                        /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF3,0x0F,0x10,0x00 )                        /* movss       xmm0,dword ptr [eax]  */ \
_LINE4( 0x66,0x0F,0x60,0xC1 )                        /* punpcklbw   xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x61,0xC1 )                        /* punpcklwd   xmm0,xmm1  */ \
_LINE3( 0x0F,0x5B,0xC8 )                             /* cvtdq2ps    xmm1,xmm0  */ \
_LINE3( 0x0F,0x13,0x0A )                             /* movlps      qword ptr [edx],xmm1  */ \
_LINE4( 0x0F,0x17,0x4A,0x08 )                        /* movhps      qword ptr [edx+8],xmm1  */ \
_END_ASM

/// Преобразование четырехмерного вектора байт в вектор одинарной точности, команды FPU. ???
/// @brief for CPUTYPE1
#define VECTORP4BTO4DFPU_STD \
_BEGIN_ASM \
_END_ASM

/// Преобразование двухмерного целочисленный вектор в вектор одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP2ITO2DSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                         /* mov         eax,dword ptr [esp+4] */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                         /* mov         edx,dword ptr [esp+8] */ \
_LINE4( 0xF3,0x0F,0x2A,0x00 )                         /* cvtsi2ss    xmm0,dword ptr [eax] */ \
_LINE5( 0xF3,0x0F,0x2A,0x48,0x04 )                    /* cvtsi2ss    xmm1,dword ptr [eax+4] */ \
_LINE4( 0xF3,0x0F,0x11,0x02 )                         /* movss       dword ptr [edx],xmm0 */ \
_LINE5( 0xF3,0x0F,0x11,0x4A,0x04 )                    /* movss       dword ptr [edx+4],xmm1 */ \
_END_ASM

/// Преобразование трехмерного целочисленного вектора в вектор одинарной точности, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP3ITO3DSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                         /* mov         eax,dword ptr [esp+4] */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                         /* mov         edx,dword ptr [esp+8] */ \
_LINE4( 0xF3,0x0F,0x2A,0x00 )                         /* cvtsi2ss    xmm0,dword ptr [eax] */ \
_LINE5( 0xF3,0x0F,0x2A,0x48,0x04 )                    /* cvtsi2ss    xmm1,dword ptr [eax+4] */ \
_LINE5( 0xF3,0x0F,0x2A,0x50,0x08 )                    /* cvtsi2ss    xmm2,dword ptr [eax+8] */ \
_LINE4( 0xF3,0x0F,0x11,0x02 )                         /* movss       dword ptr [edx],xmm0 */ \
_LINE5( 0xF3,0x0F,0x11,0x4A,0x04 )                    /* movss       dword ptr [edx+4],xmm1 */ \
_LINE5( 0xF3,0x0F,0x11,0x52,0x08 )                    /* movss       dword ptr [edx+8],xmm2 */ \
_END_ASM

/// Преобразование четырехмерного целочисленного вектора в вектор одинарной точности, команды FPU. ???
/// @brief for CPUTYPE1
#define VECTORP4ITO4DFPU_STD \
_BEGIN_ASM \
_END_ASM

/// Преобразование четырехмерного целочисленного вектора в вектор одинарной точности, команды SSE.
/// @brief for CPUTYPE1
#define VECTORP4ITO4DSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                         /* mov         eax,dword ptr [esp+4] */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                         /* mov         edx,dword ptr [esp+8] */ \
_LINE4( 0xF3,0x0F,0x2A,0x00 )                         /* cvtsi2ss    xmm0,dword ptr [eax] */ \
_LINE5( 0xF3,0x0F,0x2A,0x48,0x04 )                    /* cvtsi2ss    xmm1,dword ptr [eax+4] */ \
_LINE5( 0xF3,0x0F,0x2A,0x50,0x08 )                    /* cvtsi2ss    xmm2,dword ptr [eax+8] */ \
_LINE5( 0xF3,0x0F,0x2A,0x58,0x0C )                    /* cvtsi2ss    xmm3,dword ptr [eax+12] */ \
_LINE4( 0xF3,0x0F,0x11,0x02 )                         /* movss       dword ptr [edx],xmm0 */ \
_LINE5( 0xF3,0x0F,0x11,0x4A,0x04 )                    /* movss       dword ptr [edx+4],xmm1 */ \
_LINE5( 0xF3,0x0F,0x11,0x52,0x08 )                    /* movss       dword ptr [edx+8],xmm2 */ \
_LINE5( 0xF3,0x0F,0x11,0x5A,0x0C )                    /* movss       dword ptr [edx+12],xmm3 */ \
_END_ASM

/// Преобразование четырехмерного целочисленного вектора в вектор одинарной точности, команды SSE2. ???
/// @brief for CPUTYPE1
#define VECTORP4ITO4DSSE2_STD \
_BEGIN_ASM \
_END_ASM

/// Преобразование четырехмерного целочисленного вектора в вектор одинарной точности, команды SSE4.
/// @brief for CPUTYPE1
#define VECTORP4ITO4DSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x08 )                               /* lddqu       xmm1,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
ASM( cvtdq2ps       xmm0,xmm1 )                                    /* cvtdq2ps       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x02 )                               /* movupd      xmmword ptr [edx],xmm0  */ \
_END_ASM

/// Преобразование двухмерного вектора одинарной точности в вектор байт, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP2DTO2BSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                                /* mov         edx,dword ptr [esp+4]  */ \
_LINE4( 0xF3,0x0F,0x2D,0x02 )                                /* cvtss2si   eax,dword ptr [edx]  */ \
_LINE2( 0x8A,0xC8 )                                          /* mov         cl,al  */ \
_LINE5( 0xF3,0x0F,0x2D,0x42,0x04 )                           /* cvtss2si   eax,dword ptr [edx+4]  */ \
_LINE2( 0x8A,0xE8 )                                          /* mov         ch,al  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                                /* mov         eax,dword ptr [esp+8]  */ \
ASM( mov         word ptr [eax],cx ) \
_END_ASM

/// Преобразование трехмерного вектора одинарной точности в вектор байт, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP3DTO3BSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                                /* mov         edx,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x2D,0x42,0x08 )                           /* cvtss2si   eax,dword ptr [edx+8]  */ \
_LINE2( 0x8A,0xC8 )                                          /* mov         cl,al  */ \
_LINE3( 0xC1,0xE1,0x10 )                                     /* shl         ecx,10h  */ \
_LINE4( 0xF3,0x0F,0x2D,0x02 )                                /* cvtss2si   eax,dword ptr [edx]  */ \
_LINE2( 0x8A,0xC8 )                                          /* mov         cl,al  */ \
_LINE5( 0xF3,0x0F,0x2D,0x42,0x04 )                           /* cvtss2si   eax,dword ptr [edx+4]  */ \
_LINE2( 0x8A,0xE8 )                                          /* mov         ch,al  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                                /* mov         eax,dword ptr [esp+8]  */ \
ASM( mov         word ptr [eax],cx ) \
ASM( shr         ecx,0x10 ) \
ASM( mov         byte ptr [eax+2],cl ) \
_END_ASM

/// Преобразование четырехмерного вектора одинарной точности в вектор байт, команды FPU. ???
/// @brief for CPUTYPE1
#define VECTORP4DTO4BFPU_STD \
_BEGIN_ASM \
_END_ASM

/// Преобразование четырехмерного вектора одинарной точности в вектор байт, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP4DTO4BSSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                                /* mov         edx,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x2D,0x42,0x08 )                           /* cvtss2si   eax,dword ptr [edx+8]  */ \
_LINE2( 0x8A,0xC8 )                                          /* mov         cl,al  */ \
_LINE5( 0xF3,0x0F,0x2D,0x42,0x0C )                           /* cvtss2si   eax,dword ptr [edx+0Ch]  */ \
_LINE2( 0x8A,0xE8 )                                          /* mov         ch,al  */ \
_LINE3( 0xC1,0xE1,0x10 )                                     /* shl         ecx,10h  */ \
_LINE4( 0xF3,0x0F,0x2D,0x02 )                                /* cvtss2si   eax,dword ptr [edx]  */ \
_LINE2( 0x8A,0xC8 )                                          /* mov         cl,al  */ \
_LINE5( 0xF3,0x0F,0x2D,0x42,0x04 )                           /* cvtss2si   eax,dword ptr [edx+4]  */ \
_LINE2( 0x8A,0xE8 )                                          /* mov         ch,al  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                                /* mov         eax,dword ptr [esp+8]  */ \
_LINE2( 0x89,0x08 )                                          /* mov         dword ptr [eax],ecx  */ \
_END_ASM

/// Преобразование четырехмерного вектора одинарной точности в вектор байт, команды SSE4.
/// @brief for CPUTYPE4
#define VECTORP4DTO4BSSE4_STD \
_BEGIN_ASM \
ASM( mov eax,0xFF ) \
_LINE4( 0x8B,0x54,0x24,0x04 )                                /* mov         edx,dword ptr [esp+4]  */ \
ASM( movd xmm2,eax ) \
_LINE4( 0xF2,0x0F,0xF0,0x02 )                                /* lddqu       xmm0,xmmword ptr [edx]  */ \
ASM( shufps xmm2,xmm2,0 ) \
_LINE4( 0x66,0x0F,0x5B,0xC8 )                                /* cvtps2dq    xmm1,xmm0  */ \
ASM( andps xmm1,xmm2 ) \
_LINE5( 0x66,0x0F,0x38,0x2B,0xC9 )                           /* packusdw    xmm1,xmm1  */ \
_LINE4( 0x66,0x0F,0x67,0xC9 )                                /* packuswb    xmm1,xmm1  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )                                /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0xF3,0x0F,0x11,0x08 )                                /* movss       dword ptr [eax],xmm1  */ \
_END_ASM

/// Округление двухмерного вектора одинарной точности в целочисленный вектор, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP2DTO2IFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                         /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                         /* mov         edx,dword ptr [esp+8] */ \
ASM( fld dword ptr [eax] ) \
ASM( fistp dword ptr [edx]  ) \
ASM( fld dword ptr [eax+4] ) \
ASM( fistp dword ptr [edx+4]  ) \
_END_ASM

/// Округление двухмерного вектора одинарной точности в целочисленный вектор, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP2DTO2ISSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                         /* mov         edx,dword ptr [esp+4] */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                         /* mov         ecx,dword ptr [esp+8] */ \
_LINE4( 0xF3,0x0F,0x2D,0x02 )                         /* cvtss2si    eax,dword ptr [edx] */ \
_LINE5( 0xF3,0x0F,0x2D,0x52,0x04 )                    /* cvtss2si    edx,dword ptr [edx+4] */ \
_LINE2( 0x89,0x01 )                                   /* mov         dword ptr [ecx],eax */ \
_LINE3( 0x89,0x51,0x04 )                              /* mov         dword ptr [ecx+4],edx */ \
_END_ASM

/// Округление двухмерного вектора одинарной точности в целочисленный вектор, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP2DTO2ISSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                                /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                                /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                                /* movsd       xmm0,mmword ptr [eax]  */ \
ASM( cvtps2dq    xmm0,xmm0 )                                 /* cvtps2dq    xmm0,xmm0  */ \
_LINE3( 0x0F,0x13,0x02 )                                     /* movlps      qword ptr [edx],xmm0  */ \
_END_ASM

/// Округление трехмерного вектора одинарной точности в целочисленный вектор, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP3DTO3IFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                         /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                         /* mov         edx,dword ptr [esp+8] */ \
ASM( fld dword ptr [eax] ) \
ASM( fistp dword ptr [edx]  ) \
ASM( fld dword ptr [eax+4] ) \
ASM( fistp dword ptr [edx+4]  ) \
ASM( fld dword ptr [eax+8] ) \
ASM( fistp dword ptr [edx+8]  ) \
_END_ASM

/// Округление трехмерного вектора одинарной точности в целочисленный вектор, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP3DTO3ISSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                         /* mov         edx,dword ptr [esp+4] */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                         /* mov         ecx,dword ptr [esp+8] */ \
_LINE4( 0xF3,0x0F,0x2D,0x02 )                         /* cvtss2si    eax,dword ptr [edx] */ \
_LINE2( 0x89,0x01 )                                   /* mov         dword ptr [ecx],eax */ \
_LINE5( 0xF3,0x0F,0x2D,0x42,0x04 )                    /* cvtss2si    eax,dword ptr [edx+4] */ \
_LINE5( 0xF3,0x0F,0x2D,0x52,0x08 )                    /* cvtss2si    edx,dword ptr [edx+8] */ \
_LINE3( 0x89,0x41,0x04 )                              /* mov         dword ptr [ecx+4],eax */ \
_LINE3( 0x89,0x51,0x08 )                              /* mov         dword ptr [ecx+8],edx */ \
_END_ASM

/// Округление двухмерного вектора одинарной точности в целочисленный вектор, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP3DTO3ISSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                         /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                    /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                         /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x66,0x0F,0x16,0x00 )                         /* movhpd      xmm0,qword ptr [eax]  */ \
_LINE4( 0x66,0x0F,0x5B,0xC0 )                         /* cvtps2dq    xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x17,0x02 )                         /* movhpd      qword ptr [edx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x42,0x08 )                    /* movss       dword ptr [edx+8],xmm0  */ \
_END_ASM

/// Округление четырехмерного вектора одинарной точности в целочисленный вектор, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP4DTO4IFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                         /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                         /* mov         edx,dword ptr [esp+8] */ \
ASM( fld dword ptr [eax] ) \
ASM( fistp dword ptr [edx]  ) \
ASM( fld dword ptr [eax+4] ) \
ASM( fistp dword ptr [edx+4]  ) \
ASM( fld dword ptr [eax+8] ) \
ASM( fistp dword ptr [edx+8]  ) \
ASM( fld dword ptr [eax+12] ) \
ASM( fistp dword ptr [edx+12]  ) \
_END_ASM

/// Округление четырехмерного вектора одинарной точности в целочисленный вектор, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP4DTO4ISSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                         /* mov         edx,dword ptr [esp+4] */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                         /* mov         ecx,dword ptr [esp+8] */ \
_LINE4( 0xF3,0x0F,0x2D,0x02 )                         /* cvtss2si    eax,dword ptr [edx] */ \
_LINE2( 0x89,0x01 )                                   /* mov         dword ptr [ecx],eax */ \
_LINE5( 0xF3,0x0F,0x2D,0x42,0x04 )                    /* cvtss2si    eax,dword ptr [edx+4] */ \
_LINE3( 0x89,0x41,0x04 )                              /* mov         dword ptr [ecx+4],eax */ \
_LINE5( 0xF3,0x0F,0x2D,0x42,0x08 )                    /* cvtss2si    eax,dword ptr [edx+8] */ \
_LINE5( 0xF3,0x0F,0x2D,0x52,0x0C )                    /* cvtss2si    edx,dword ptr [edx+12] */ \
_LINE3( 0x89,0x41,0x08 )                              /* mov         dword ptr [ecx+8],eax */ \
_LINE3( 0x89,0x51,0x0C )                              /* mov         dword ptr [ecx+12],edx */ \
_END_ASM

/// Округление четырехмерного вектора одинарной точности в целочисленный вектор, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP4DTO4ISSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                                /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                                /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )                                /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE3( 0x0F,0x12,0x00 )                                     /* movlps      xmm0,qword ptr [eax]  */ \
_LINE4( 0x66,0x0F,0x5B,0xC0 )                                /* cvtps2dq    xmm0,xmm0  */ \
_LINE3( 0x0F,0x13,0x02 )                                     /* movlps      qword ptr [edx],xmm0  */ \
_LINE4( 0x0F,0x17,0x42,0x08 )                                /* movhps      qword ptr [edx+8],xmm0  */ \
_END_ASM

/// Округление четырехмерного вектора одинарной точности в целочисленный вектор, команды SSE4.
/// @brief for CPUTYPE3
#define VECTORP4DTO4ISSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x08 )                               /* lddqu       xmm1,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
ASM( cvtps2dq       xmm0,xmm1 )                                    /* cvtps2dq       xmm0,xmm1  */ \
_LINE4( 0x66,0x0F,0x11,0x02 )                               /* movupd      xmmword ptr [edx],xmm0  */ \
_END_ASM

/// Отсечение двухмерного вектора одинарной точности в целочисленный вектор, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP2DTTO2ISSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                         /* mov         edx,dword ptr [esp+4] */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                         /* mov         ecx,dword ptr [esp+8] */ \
_LINE4( 0xF3,0x0F,0x2C,0x02 )                         /* cvttss2si    eax,dword ptr [edx] */ \
_LINE5( 0xF3,0x0F,0x2C,0x52,0x04 )                    /* cvttss2si    edx,dword ptr [edx+4] */ \
_LINE2( 0x89,0x01 )                                   /* mov         dword ptr [ecx],eax */ \
_LINE3( 0x89,0x51,0x04 )                              /* mov         dword ptr [ecx+4],edx */ \
_END_ASM

/// Отсечение двухмерного вектора одинарной точности в целочисленный вектор, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP2DTTO2ISSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                                /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                                /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                                /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE4( 0xF3,0x0F,0x5B,0xC0 )                                /* cvttps2dq    xmm0,xmm0  */ \
_LINE3( 0x0F,0x13,0x02 )                                     /* movlps      qword ptr [edx],xmm0  */ \
_END_ASM

/// Отсечение трехмерного вектора одинарной точности в целочисленный вектор, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP3DTTO3ISSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                         /* mov         edx,dword ptr [esp+4] */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                         /* mov         ecx,dword ptr [esp+8] */ \
_LINE4( 0xF3,0x0F,0x2C,0x02 )                         /* cvttss2si    eax,dword ptr [edx] */ \
_LINE2( 0x89,0x01 )                                   /* mov         dword ptr [ecx],eax */ \
_LINE5( 0xF3,0x0F,0x2C,0x42,0x04 )                    /* cvttss2si    eax,dword ptr [edx+4] */ \
_LINE5( 0xF3,0x0F,0x2C,0x52,0x08 )                    /* cvttss2si    edx,dword ptr [edx+8] */ \
_LINE3( 0x89,0x41,0x04 )                              /* mov         dword ptr [ecx+4],edx */ \
_LINE3( 0x89,0x51,0x08 )                              /* mov         dword ptr [ecx+8],edx */ \
_END_ASM

/// Преобразование двухмерного вектора одинарной точности в целочисленный вектор, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP3DTTO3ISSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                         /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                    /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                         /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x66,0x0F,0x16,0x00 )                         /* movhpd      xmm0,qword ptr [eax]  */ \
_LINE4( 0xF3,0x0F,0x5B,0xC0 )                         /* cvttps2dq    xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x17,0x02 )                         /* movhpd      qword ptr [edx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x42,0x08 )                    /* movss       dword ptr [edx+8],xmm0  */ \
_END_ASM

/// Отсечение четырехмерного вектора одинарной точности в целочисленный вектор, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP4DTTO4ISSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                         /* mov         edx,dword ptr [esp+4] */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                         /* mov         ecx,dword ptr [esp+8] */ \
_LINE4( 0xF3,0x0F,0x2C,0x02 )                         /* cvttss2si   eax,dword ptr [edx] */ \
_LINE2( 0x89,0x01 )                                   /* mov         dword ptr [ecx],eax */ \
_LINE5( 0xF3,0x0F,0x2C,0x42,0x04 )                    /* cvttss2si   eax,dword ptr [edx+4] */ \
_LINE3( 0x89,0x41,0x04 )                              /* mov         dword ptr [ecx+4],eax */ \
_LINE5( 0xF3,0x0F,0x2C,0x42,0x08 )                    /* cvttss2si   eax,dword ptr [edx+8] */ \
_LINE5( 0xF3,0x0F,0x2C,0x52,0x0C )                    /* cvttss2si   edx,dword ptr [edx+12] */ \
_LINE3( 0x89,0x41,0x08 )                              /* mov         dword ptr [ecx+8],eax */ \
_LINE3( 0x89,0x51,0x0C )                              /* mov         dword ptr [ecx+12],edx */ \
_END_ASM

/// Отсечение четырехмерного вектора одинарной точности в целочисленный вектор, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP4DTTO4ISSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                                /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                                /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )                                /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE3( 0x0F,0x12,0x00 )                                     /* movlps      xmm0,qword ptr [eax]  */ \
_LINE4( 0xF3,0x0F,0x5B,0xC0 )                                /* cvttps2dq   xmm0,xmm0   */ \
_LINE3( 0x0F,0x13,0x02 )                                     /* movlps      qword ptr [edx],xmm0  */ \
_LINE4( 0x0F,0x17,0x42,0x08 )                                /* movhps      qword ptr [edx+8],xmm0  */ \
_END_ASM

/// Отсечение четырехмерного вектора одинарной точности в целочисленный вектор, команды SSE4.
/// @brief for CPUTYPE3
#define VECTORP4DTTO4ISSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x08 )                               /* lddqu       xmm1,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF3,0x0F,0x5B,0xC1 )                               /* cvttps2dq   xmm0,xmm1   */ \
_LINE4( 0x66,0x0F,0x11,0x02 )                               /* movupd      xmmword ptr [edx],xmm0  */ \
_END_ASM

/// Преобразование двухмерного вектора одинарной точности в вектор двойной точности, команды FPU. ???
/// @brief for CPUTYPE1
#define VECTORP2DTO2DDFPU_STD \
_BEGIN_ASM \
_END_ASM

/// Преобразование двухмерного вектора одинарной точности в вектор двойной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP2DTO2DDSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x5A,0x00 )                                    /* cvtps2pd    xmm0,mmword ptr [eax]  */ \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
_LINE4( 0x0F,0x17,0x42,0x08 )                               /* movhps      qword ptr [edx+8],xmm0  */ \
_END_ASM

/// Преобразование трехмерного вектора одинарной точности в вектор двойной точности, команды SSE2. low speed
/// @brief for CPUTYPE3
#define VECTORP3DTO3DDSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x5A,0x00 )                                    /* cvtps2pd    xmm0,mmword ptr [eax]  */ \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
_LINE4( 0x0F,0x17,0x42,0x08 )                               /* movhps      qword ptr [edx+8],xmm0  */ \
ASM( CVTSS2SD xmm1,dword ptr [eax+8] ) \
_LINE4( 0x0F,0x13,0x4A,0x10 )                               /* movlps      qword ptr [edx+16],xmm1  */ \
_END_ASM

/// Преобразование трехмерного вектора одинарной точности в вектор двойной точности, команды SSE4. low speed
/// @brief for CPUTYPE3
#define VECTORP3DTO3DDSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x5A,0x00 )                                    /* cvtps2pd    xmm0,mmword ptr [eax]  */ \
ASM( CVTSS2SD xmm1,dword ptr [eax+8] ) \
_LINE4( 0x66,0x0F,0x11,0x02 )                               /* movupd      xmmword ptr [edx],xmm0  */ \
_LINE4( 0x0F,0x13,0x4A,0x10 )                               /* movlps      qword ptr [edx+16],xmm1  */ \
_END_ASM

/// Преобразование четырехмерного вектора одинарной точности в вектор двойной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP4DTO4DDSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x5A,0x00 )                                    /* cvtps2pd    xmm0,mmword ptr [eax]  */ \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
_LINE4( 0x0F,0x17,0x42,0x08 )                               /* movhps      qword ptr [edx+8],xmm0  */ \
_LINE4( 0x0F,0x5A,0x48,0x08 )                               /* cvtps2pd    xmm1,mmword ptr [eax+8]  */ \
_LINE4( 0x0F,0x13,0x4A,0x10 )                               /* movlps      qword ptr [edx+10h],xmm1  */ \
_LINE4( 0x0F,0x17,0x4A,0x18 )                               /* movhps      qword ptr [edx+18h],xmm1  */ \
_END_ASM

/// Округление двухмерного вектора двойной точности в целочисленный вектор, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP2DDTO2IFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                         /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                         /* mov         edx,dword ptr [esp+8] */ \
ASM( fld qword ptr [eax] ) \
ASM( fistp dword ptr [edx]  ) \
ASM( fld qword ptr [eax+8] ) \
ASM( fistp dword ptr [edx+4]  ) \
_END_ASM

/// Округление двухмерного вектора двойной точности в целочисленный вектор, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP2DDTO2ISSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                         /* mov         edx,dword ptr [esp+4] */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                         /* mov         ecx,dword ptr [esp+8] */ \
_LINE4( 0xF2,0x0F,0x2D,0x02 )                         /* cvtsd2si    eax,mmword ptr [edx] */ \
_LINE5( 0xF2,0x0F,0x2D,0x52,0x08 )                    /* cvtsd2si    edx,mmword ptr [edx+8] */ \
_LINE2( 0x89,0x01 )                                   /* mov         dword ptr [ecx],eax */ \
_LINE3( 0x89,0x51,0x04 )                              /* mov         dword ptr [ecx+4],edx */ \
_END_ASM

/// Округление трехмерного вектора двойной точности в целочисленный вектор, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP3DDTO3IFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                         /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                         /* mov         edx,dword ptr [esp+8] */ \
ASM( fld qword ptr [eax] ) \
ASM( fistp dword ptr [edx]  ) \
ASM( fld qword ptr [eax+8] ) \
ASM( fistp dword ptr [edx+4]  ) \
ASM( fld qword ptr [eax+16] ) \
ASM( fistp dword ptr [edx+8]  ) \
_END_ASM

/// Округление трехмерного вектора двойной точности в целочисленный вектор, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP3DDTO3ISSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                         /* mov         edx,dword ptr [esp+4] */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                         /* mov         ecx,dword ptr [esp+8] */ \
_LINE4( 0xF2,0x0F,0x2D,0x02 )                         /* cvtsd2si    eax,mmword ptr [edx] */ \
_LINE2( 0x89,0x01 )                                   /* mov         dword ptr [ecx],eax */ \
_LINE5( 0xF2,0x0F,0x2D,0x42,0x08 )                    /* cvtsd2si    eax,mmword ptr [edx+8] */ \
_LINE5( 0xF2,0x0F,0x2D,0x52,0x10 )                    /* cvtsd2si    edx,mmword ptr [edx+16] */ \
_LINE3( 0x89,0x41,0x04 )                              /* mov         dword ptr [ecx+4],eax */ \
_LINE3( 0x89,0x51,0x08 )                              /* mov         dword ptr [ecx+8],edx */ \
_END_ASM

/// Округление четырехмерного вектора двойной точности в целочисленный вектор, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP4DDTO4IFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                         /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                         /* mov         edx,dword ptr [esp+8] */ \
ASM( fld qword ptr [eax] ) \
ASM( fistp dword ptr [edx]  ) \
ASM( fld qword ptr [eax+8] ) \
ASM( fistp dword ptr [edx+4]  ) \
ASM( fld qword ptr [eax+16] ) \
ASM( fistp dword ptr [edx+8]  ) \
ASM( fld qword ptr [eax+24] ) \
ASM( fistp dword ptr [edx+12]  ) \
_END_ASM

/// Округление четырехмерного вектора двойной точности в целочисленный вектор, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP4DDTO4ISSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                         /* mov         edx,dword ptr [esp+4] */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                         /* mov         ecx,dword ptr [esp+8] */ \
_LINE4( 0xF2,0x0F,0x2D,0x02 )                         /* cvtsd2si    eax,mmword ptr [edx] */ \
_LINE2( 0x89,0x01 )                                   /* mov         dword ptr [ecx],eax */ \
_LINE5( 0xF2,0x0F,0x2D,0x42,0x08 )                    /* cvtsd2si    eax,mmword ptr [edx+8] */ \
_LINE3( 0x89,0x41,0x04 )                              /* mov         dword ptr [ecx+4],eax */ \
_LINE5( 0xF2,0x0F,0x2D,0x42,0x10 )                    /* cvtsd2si    eax,mmword ptr [edx+16] */ \
_LINE5( 0xF2,0x0F,0x2D,0x52,0x18 )                    /* cvtsd2si    edx,mmword ptr [edx+24] */ \
_LINE3( 0x89,0x41,0x08 )                              /* mov         dword ptr [ecx+8],eax */ \
_LINE3( 0x89,0x51,0x0C )                              /* mov         dword ptr [ecx+12],edx */ \
_END_ASM

/// Отсечение двухмерного вектора двойной точности в целочисленный вектор, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP2DDTTO2ISSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                         /* mov         edx,dword ptr [esp+4] */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                         /* mov         ecx,dword ptr [esp+8] */ \
_LINE4( 0xF2,0x0F,0x2C,0x02 )                         /* cvttsd2si   eax,mmword ptr [edx] */ \
_LINE5( 0xF2,0x0F,0x2C,0x52,0x08 )                    /* cvttsd2si   edx,mmword ptr [edx+8] */ \
_LINE2( 0x89,0x01 )                                   /* mov         dword ptr [ecx],eax */ \
_LINE3( 0x89,0x51,0x04 )                              /* mov         dword ptr [ecx+4],edx */ \
_END_ASM

/// Отсечение трехмерного вектора двойной точности в целочисленный вектор, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP3DDTTO3ISSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                         /* mov         edx,dword ptr [esp+4] */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                         /* mov         ecx,dword ptr [esp+8] */ \
_LINE4( 0xF2,0x0F,0x2C,0x02 )                         /* cvttsd2si   eax,mmword ptr [edx] */ \
_LINE2( 0x89,0x01 )                                   /* mov         dword ptr [ecx],eax */ \
_LINE5( 0xF2,0x0F,0x2C,0x42,0x08 )                    /* cvttsd2si   eax,mmword ptr [edx+8] */ \
_LINE5( 0xF2,0x0F,0x2C,0x52,0x10 )                    /* cvttsd2si   edx,mmword ptr [edx+16] */ \
_LINE3( 0x89,0x41,0x04 )                              /* mov         dword ptr [ecx+4],eax */ \
_LINE3( 0x89,0x51,0x08 )                              /* mov         dword ptr [ecx+8],edx */ \
_END_ASM

/// Отсечение четырехмерного вектора двойной точности в целочисленный вектор, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP4DDTTO4ISSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )                         /* mov         edx,dword ptr [esp+4] */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                         /* mov         ecx,dword ptr [esp+8] */ \
_LINE4( 0xF2,0x0F,0x2C,0x02 )                         /* cvttsd2si   eax,mmword ptr [edx] */ \
_LINE2( 0x89,0x01 )                                   /* mov         dword ptr [ecx],eax */ \
_LINE5( 0xF2,0x0F,0x2C,0x42,0x08 )                    /* cvttsd2si   eax,mmword ptr [edx+8] */ \
_LINE3( 0x89,0x41,0x04 )                              /* mov         dword ptr [ecx+4],eax */ \
_LINE5( 0xF2,0x0F,0x2C,0x42,0x10 )                    /* cvttsd2si   eax,mmword ptr [edx+16] */ \
_LINE5( 0xF2,0x0F,0x2C,0x52,0x18 )                    /* cvttsd2si   edx,mmword ptr [edx+24] */ \
_LINE3( 0x89,0x41,0x08 )                              /* mov         dword ptr [ecx+8],eax */ \
_LINE3( 0x89,0x51,0x0C )                              /* mov         dword ptr [ecx+12],edx */ \
_END_ASM

/// Преобразование двухмерного вектора двойной точности в вектор одинарной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP2DDTO2DSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF2,0x0F,0x5A,0x48,0x08 )                          /* cvtsd2ss    eax,mmword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x5A,0x00 )                               /* cvtsd2ss    eax,mmword ptr [eax]  */ \
_LINE4( 0xF3,0x0F,0x11,0x02 )                               /* movss       dword ptr [edx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x4A,0x04 )                          /* movss       dword ptr [edx+4],xmm1  */ \
_END_ASM

/// Преобразование двухмерного вектора двойной точности в вектор одинарной точности, команды SSE3.
/// @brief for CPUTYPE4
#define VECTORP2DDTO2DSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x66,0x0F,0x5A,0xC0 )                               /* cvtpd2ps    xmm0,xmm0  */ \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
_END_ASM

/// Преобразование трехмерного вектора двойной точности в вектор одинарной точности, команды SSE2. // low
/// @brief for CPUTYPE3
#define VECTORP3DDTO3DSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF2,0x0F,0x5A,0x48,0x08 )                          /* cvtsd2ss    xmm1,mmword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x5A,0x00 )                               /* cvtsd2ss    xmm0,mmword ptr [eax]  */ \
_LINE4( 0xF3,0x0F,0x11,0x02 )                               /* movss       dword ptr [edx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x5A,0x50,0x10 )                          /* cvtsd2ss    xmm2,mmword ptr [eax+16]  */ \
_LINE5( 0xF3,0x0F,0x11,0x4A,0x04 )                          /* movss       dword ptr [edx+4],xmm1  */ \
_LINE5( 0xF3,0x0F,0x11,0x52,0x08 )                          /* movss       dword ptr [edx+8],xmm2  */ \
_END_ASM

/// Преобразование трехмерного вектора двойной точности в вектор одинарной точности, команды SSE3.
/// @brief for CPUTYPE3
#define VECTORP3DDTO3DSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x66,0x0F,0x5A,0xC0 )                               /* cvtpd2ps    xmm0,xmm0  */ \
_LINE5( 0xF2,0x0F,0x5A,0x50,0x10 )                          /* cvtsd2ss    xmm2,mmword ptr [eax+16]  */ \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x52,0x08 )                          /* movss       dword ptr [edx+8],xmm2  */ \
_END_ASM

/// Преобразование четырехмерного вектора двойной точности в вектор одинарной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP4DDTO4DSSE2_STD1 \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF2,0x0F,0x5A,0x48,0x08 )                          /* cvtsd2ss    xmm1,mmword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x5A,0x00 )                               /* cvtsd2ss    xmm0,mmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0x5A,0x50,0x10 )                          /* cvtsd2ss    xmm2,mmword ptr [eax+16]  */ \
_LINE5( 0xF3,0x0F,0x11,0x4A,0x04 )                          /* movss       dword ptr [edx+4],xmm1  */ \
_LINE4( 0xF3,0x0F,0x11,0x02 )                               /* movss       dword ptr [edx],xmm0  */ \
_LINE5( 0xF2,0x0F,0x5A,0x58,0x18 )                          /* cvtsd2ss    xmm3,mmword ptr [eax+24]  */ \
_LINE5( 0xF3,0x0F,0x11,0x52,0x08 )                          /* movss       dword ptr [edx+8],xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x5A,0x0C )                          /* movss       dword ptr [edx+12],xmm3  */ \
_END_ASM

/// Преобразование четырехмерного вектора двойной точности в вектор одинарной точности, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP4DDTO4DSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x10 )                          /* movsd       xmm1,mmword ptr [eax+10h]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )                               /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x16,0x48,0x18 )                               /* movhps      xmm1,qword ptr [eax+18h]  */ \
_LINE4( 0x66,0x0F,0x5A,0xC0 )                               /* cvtpd2ps    xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x5A,0xC9 )                               /* cvtpd2ps    xmm1,xmm1  */ \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
_LINE4( 0x0F,0x13,0x4A,0x08 )                               /* movlps      qword ptr [edx+8],xmm1  */ \
_END_ASM

/// Преобразование четырехмерного вектора двойной точности в вектор одинарной точности, команды SSE3.
/// @brief for CPUTYPE4
#define VECTORP4DDTO4DSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x48,0x10 )                          /* lddqu       xmm1,[eax+10h]  */ \
_LINE4( 0x66,0x0F,0x5A,0xC0 )                               /* cvtpd2ps    xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x5A,0xC9 )                               /* cvtpd2ps    xmm1,xmm1  */ \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
_LINE4( 0x0F,0x13,0x4A,0x08 )                               /* movlps      qword ptr [edx+8],xmm1  */ \
_END_ASM

//**************************** MATRIX TO STDCALL *********************************
// to matrix eax=[esp+4]-a void *, edx=[esp+8]-b void *

/// Преобразование матрицы двойной точности в матрицу одинарной точности, команды SSE2.
/// @brief for CPUTYPE3
#define MATRIXP4DDTO4DSSE2_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0x10,0x00 )                               /* movsd       xmm0,mmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0x10,0x48,0x10 )                          /* movsd       xmm1,mmword ptr [eax+10h]  */ \
_LINE4( 0x0F,0x16,0x40,0x08 )                               /* movhps      xmm0,qword ptr [eax+8]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x0F,0x16,0x48,0x18 )                               /* movhps      xmm1,qword ptr [eax+18h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x50,0x20 )                          /* movsd       xmm2,mmword ptr [eax+20h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x58,0x30 )                          /* movsd       xmm3,mmword ptr [eax+30h]  */ \
_LINE4( 0x0F,0x16,0x50,0x28 )                               /* movhps      xmm2,qword ptr [eax+28]  */ \
_LINE4( 0x0F,0x16,0x58,0x38 )                               /* movhps      xmm3,qword ptr [eax+38h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x60,0x40 )                          /* movsd       xmm4,mmword ptr [eax+40h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x68,0x50 )                          /* movsd       xmm5,mmword ptr [eax+50h]  */ \
_LINE4( 0x0F,0x16,0x60,0x48 )                               /* movhps      xmm4,qword ptr [eax+48]  */ \
_LINE4( 0x0F,0x16,0x68,0x58 )                               /* movhps      xmm5,qword ptr [eax+58h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x70,0x60 )                          /* movsd       xmm6,mmword ptr [eax+60h]  */ \
_LINE5( 0xF2,0x0F,0x10,0x78,0x70 )                          /* movsd       xmm7,mmword ptr [eax+70h]  */ \
_LINE4( 0x0F,0x16,0x70,0x68 )                               /* movhps      xmm6,qword ptr [eax+68]  */ \
_LINE4( 0x0F,0x16,0x78,0x78 )                               /* movhps      xmm7,qword ptr [eax+78h]  */ \
_LINE4( 0x66,0x0F,0x5A,0xC0 )                               /* cvtpd2ps    xmm0,xmm0  */ \
_LINE4( 0x66,0x0F,0x5A,0xC9 )                               /* cvtpd2ps    xmm1,xmm1  */ \
_LINE4( 0x66,0x0F,0x5A,0xD2 )                               /* cvtpd2ps    xmm2,xmm2  */ \
_LINE4( 0x66,0x0F,0x5A,0xDB )                               /* cvtpd2ps    xmm3,xmm3  */ \
_LINE4( 0x66,0x0F,0x5A,0xE4 )                               /* cvtpd2ps    xmm4,xmm4  */ \
_LINE4( 0x66,0x0F,0x5A,0xED )                               /* cvtpd2ps    xmm5,xmm5  */ \
_LINE4( 0x66,0x0F,0x5A,0xF6 )                               /* cvtpd2ps    xmm6,xmm6  */ \
_LINE4( 0x66,0x0F,0x5A,0xFF )                               /* cvtpd2ps    xmm7,xmm7  */ \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
_LINE4( 0x0F,0x13,0x4A,0x08 )                               /* movlps      qword ptr [edx+8],xmm1  */ \
_LINE4( 0x0F,0x13,0x52,0x10 )                               /* movlps      qword ptr [edx+0x10],xmm2  */ \
_LINE4( 0x0F,0x13,0x5A,0x18 )                               /* movlps      qword ptr [edx+0x18],xmm3  */ \
_LINE4( 0x0F,0x13,0x62,0x20 )                               /* movlps      qword ptr [edx+0x20],xmm4  */ \
_LINE4( 0x0F,0x13,0x6A,0x28 )                               /* movlps      qword ptr [edx+0x28],xmm5  */ \
_LINE4( 0x0F,0x13,0x72,0x30 )                               /* movlps      qword ptr [edx+0x30],xmm6  */ \
_LINE4( 0x0F,0x13,0x7A,0x38 )                               /* movlps      qword ptr [edx+0x38],xmm7  */ \
_END_ASM

#endif
