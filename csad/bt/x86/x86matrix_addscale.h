//=============================================================================
///**
// *  @file   matrix_addscale.h
// *
// *  $Id: matrix_addscale.h 16.10.2011  $
// *
// *  @brief generator 3, assembler matrix double/float addscale, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_MATRIX_ADDSCALE_H_
#define GEN3_MATRIX_ADDSCALE_H_

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

/// Масштабирование матрици одинарной точности, команды SSE
#define MATRIXP4DADDSCALESSE_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )        /* mov         edx,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )        /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0xF3,0x0F,0x10,0x00 )        /* movss       xmm0,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )        /* shufps      xmm0,xmm0,0  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )   /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )        /* shufps      xmm1,xmm1,0  */ \
_LINE5( 0xF3,0x0F,0x10,0x50,0x08 )   /* movss       xmm2,dword ptr [eax+8]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )        /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x12,0x22 )             /* movlps      xmm4,qword ptr [edx]  */ \
_LINE4( 0x0F,0x12,0x6A,0x10 )        /* movlps      xmm5,qword ptr [edx+10h]  */ \
_LINE4( 0x0F,0x16,0x62,0x08 )        /* movhps      xmm4,qword ptr [edx+8]  */ \
_LINE4( 0x0F,0x16,0x6A,0x18 )        /* movhps      xmm5,qword ptr [edx+18h]  */ \
_LINE4( 0x0F,0x12,0x72,0x20 )        /* movlps      xmm6,qword ptr [edx+20h]  */ \
_LINE4( 0x0F,0x12,0x7A,0x30 )        /* movlps      xmm7,qword ptr [edx+30h]  */ \
_LINE4( 0x0F,0x16,0x72,0x28 )        /* movhps      xmm6,qword ptr [edx+28h]  */ \
_LINE4( 0x0F,0x16,0x7A,0x38 )        /* movhps      xmm7,qword ptr [edx+38h]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )        /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE3( 0x0F,0x59,0xE0 )             /* mulps       xmm4,xmm0  */ \
_LINE3( 0x0F,0x59,0xE9 )             /* mulps       xmm5,xmm1  */ \
_LINE3( 0x0F,0x59,0xF2 )             /* mulps       xmm6,xmm2  */ \
_LINE3( 0x0F,0x13,0x20 )             /* movlps      qword ptr [eax],xmm4  */ \
_LINE4( 0x0F,0x13,0x68,0x10 )        /* movlps      qword ptr [eax+10h],xmm5  */ \
_LINE4( 0x0F,0x17,0x60,0x08 )        /* movhps      qword ptr [eax+8],xmm4  */ \
_LINE4( 0x0F,0x17,0x68,0x18 )        /* movhps      qword ptr [eax+18h],xmm5  */ \
_LINE4( 0x0F,0x13,0x70,0x20 )        /* movlps      qword ptr [eax+20h],xmm6  */ \
_LINE4( 0x0F,0x13,0x78,0x30 )        /* movlps      qword ptr [eax+30h],xmm7  */ \
_LINE4( 0x0F,0x17,0x70,0x28 )        /* movhps      qword ptr [eax+28h],xmm6  */ \
_LINE4( 0x0F,0x17,0x78,0x38 )        /* movhps      qword ptr [eax+38h],xmm7  */ \
_END_ASM

/// Масштабирование матрици одинарной точности, команды SSE4
#define MATRIXP4DADDSCALESSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x54,0x24,0x04 )          /* mov         edx,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )          /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0xF3,0x0F,0x10,0x00 )          /* movss       xmm0,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )          /* shufps      xmm0,xmm0,0  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )     /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )          /* shufps      xmm1,xmm1,0  */ \
_LINE5( 0xF3,0x0F,0x10,0x50,0x08 )     /* movss       xmm2,dword ptr [eax+8]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )          /* shufps      xmm2,xmm2,0  */ \
_LINE4( 0xF2,0x0F,0xF0,0x22 )          /* lddqu       xmm4,xmmword ptr [edx]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x6A,0x10 )     /* lddqu       xmm5,xmmword ptr [edx+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x72,0x20 )     /* lddqu       xmm6,xmmword ptr [edx+20h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x7A,0x30 )     /* lddqu       xmm7,xmmword ptr [edx+30h]  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )          /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE3( 0x0F,0x59,0xE0 )               /* mulps       xmm4,xmm0  */ \
_LINE3( 0x0F,0x59,0xE9 )               /* mulps       xmm5,xmm1  */ \
_LINE3( 0x0F,0x59,0xF2 )               /* mulps       xmm6,xmm2  */ \
_LINE4( 0x66,0x0F,0x11,0x20 )          /* movupd      xmmword ptr [eax],xmm4  */ \
_LINE5( 0x66,0x0F,0x11,0x68,0x10 )     /* movupd      xmmword ptr [eax+10h],xmm5  */ \
_LINE5( 0x66,0x0F,0x11,0x70,0x20 )     /* movupd      xmmword ptr [eax+20h],xmm6  */ \
_LINE5( 0x66,0x0F,0x11,0x78,0x30 )     /* movupd      xmmword ptr [eax+30h],xmm7  */ \
_END_ASM

#endif /* X86MATRIX_ADDSCALE_H_ */
