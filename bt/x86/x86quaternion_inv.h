//=============================================================================
///**
// *  @file   quaternion_inv.h
// *
// *  $Id: quaternion_inv.h 16.10.2011  $
// *
// *  @brief generator 3, assembler quaternion double/float invertor, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_QUATERNION_INV_H
#define GEN3_QUATERNION_INV_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** INV SDTCALL *********************************
// addition vectors eax=[esp+4]-a void *, edx=[esp+8]-b void *

/// Вычисление обратного кватерниона, команды FPU.
/// @brief for CPUTYPE1
#define QUATERNIONPDINVFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )        /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0x00 )                  /* fld         dword ptr [eax]  */ \
_LINE2( 0xD9,0xE0 )                  /* fchs  */ \
_LINE3( 0xD9,0x40,0x04 )             /* fld         dword ptr [eax+4]  */ \
_LINE2( 0xD9,0xE0 )                  /* fchs  */ \
_LINE3( 0xD9,0x40,0x08 )             /* fld         dword ptr [eax+8]  */ \
_LINE2( 0xD9,0xE0 )                  /* fchs  */ \
_LINE3( 0xD9,0x40,0x0C )             /* fld         dword ptr [eax+0Ch]  */ \
_LINE2( 0xD9,0xC3 )                  /* fld         st(3)  */ \
_LINE2( 0xDC,0xC8 )                  /* fmul        st(0),st  */ \
_LINE2( 0xD9,0xC3 )                  /* fld         st(3)  */ \
_LINE2( 0xDC,0xC8 )                  /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                  /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xC2 )                  /* fld         st(2)  */ \
_LINE2( 0xDC,0xC8 )                  /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                  /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xC1 )                  /* fld         st(1)  */ \
_LINE2( 0xDC,0xC8 )                  /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                  /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xE8 )                  /* fld1  */ \
_LINE2( 0xDE,0xF1 )                  /* fdivrp      st(1),st  */ \
_LINE2( 0xDC,0xC9 )                  /* fmul        st(1),st  */ \
_LINE2( 0xDC,0xCA )                  /* fmul        st(2),st  */ \
_LINE2( 0xDC,0xCB )                  /* fmul        st(3),st  */ \
_LINE2( 0xDE,0xCC )                  /* fmulp       st(4),st  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )        /* mov         eax,dword ptr [esp+8]  */ \
_LINE3( 0xD9,0x58,0x0C )             /* fstp        dword ptr [eax+0Ch]  */ \
_LINE3( 0xD9,0x58,0x08 )             /* fstp        dword ptr [eax+8]  */ \
_LINE3( 0xD9,0x58,0x04 )             /* fstp        dword ptr [eax+4]  */ \
_LINE2( 0xD9,0x18 )                  /* fstp        dword ptr [eax]  */ \
_END_ASM

/// Вычисление обратного кватерниона, команды SSE4.
/// @brief for CPUTYPE4
#define QUATERNIONPDINVSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )             /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )             /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE3( 0x0F,0x57,0xD2 )                  /* xorps       xmm2,xmm2  */ \
_LINE3( 0x0F,0x28,0xC8 )                  /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x5C,0xD0 )                  /* subps       xmm2,xmm0  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC9,0xFF )   /* dpps        xmm1,xmm1,0FFh  */ \
_LINE4( 0x0F,0xC6,0xC2,0xAF )             /* shufps      xmm0,xmm2,0AFh  */ \
_LINE4( 0x0F,0xC6,0xD0,0x24 )             /* shufps      xmm2,xmm0,24h  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )             /* mov         eax,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x5E,0xD1 )                  /* divps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x11,0x10 )                  /* movups      xmmword ptr [eax],xmm2  */ \
_END_ASM

/// Вычисление обратного кватерниона двойной точности, команды FPU.
/// @brief for CPUTYPE1
#define QUATERNIONPDDINVFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )        /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xDD,0x00 )                  /* fld         qword ptr [eax]  */ \
_LINE2( 0xD9,0xE0 )                  /* fchs  */ \
_LINE3( 0xDD,0x40,0x08 )             /* fld         qword ptr [eax+8]  */ \
_LINE2( 0xD9,0xE0 )                  /* fchs  */ \
_LINE3( 0xDD,0x40,0x10 )             /* fld         qword ptr [eax+10h]  */ \
_LINE2( 0xD9,0xE0 )                  /* fchs  */ \
_LINE3( 0xDD,0x40,0x18 )             /* fld         qword ptr [eax+18h]  */ \
_LINE2( 0xD9,0xC3 )                  /* fld         st(3)  */ \
_LINE2( 0xDC,0xC8 )                  /* fmul        st(0),st  */ \
_LINE2( 0xD9,0xC3 )                  /* fld         st(3)  */ \
_LINE2( 0xDC,0xC8 )                  /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                  /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xC2 )                  /* fld         st(2)  */ \
_LINE2( 0xDC,0xC8 )                  /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                  /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xC1 )                  /* fld         st(1)  */ \
_LINE2( 0xDC,0xC8 )                  /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                  /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xE8 )                  /* fld1  */ \
_LINE2( 0xDE,0xF1 )                  /* fdivrp      st(1),st  */ \
_LINE2( 0xDC,0xC9 )                  /* fmul        st(1),st  */ \
_LINE2( 0xDC,0xCA )                  /* fmul        st(2),st  */ \
_LINE2( 0xDC,0xCB )                  /* fmul        st(3),st  */ \
_LINE2( 0xDE,0xCC )                  /* fmulp       st(4),st  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )        /* mov         eax,dword ptr [esp+8]  */ \
_LINE3( 0xDD,0x58,0x18 )             /* fstp        qword ptr [eax+18h]  */ \
_LINE3( 0xDD,0x58,0x10 )             /* fstp        qword ptr [eax+10h]  */ \
_LINE3( 0xDD,0x58,0x08 )             /* fstp        qword ptr [eax+8]  */ \
_LINE2( 0xDD,0x18 )                  /* fstp        qword ptr [eax]  */ \
_END_ASM

/// Вычисление обратного кватерниона двойной точности, команды SSE4.
/// @brief for CPUTYPE4
#define QUATERNIONPDDINVSSE4_STD1 \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )            /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x00 )            /* lddqu       xmm0,xmmword ptr [eax]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x48,0x10 )       /* lddqu       xmm1,xmmword ptr [eax+10h]  */ \
_LINE3( 0x0F,0x28,0xD0 )                 /* movaps      xmm2,xmm0  */ \
_LINE3( 0x0F,0x57,0xE4 )                 /* xorps       xmm4,xmm4  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xD2,0x31 )  /* dppd        xmm2,xmm2,31h  */ \
_LINE3( 0x0F,0x28,0xD9 )                 /* movaps      xmm3,xmm1  */ \
_LINE4( 0xF2,0x0F,0x10,0xEC )            /* movsd       xmm5,xmm4  */ \
_LINE5( 0xB8,0x01,0x00,0x00,0x00 )       /* mov         eax,1  */ \
_LINE6( 0x66,0x0F,0x3A,0x41,0xDB,0x31 )  /* dppd        xmm3,xmm3,31h  */ \
_LINE4( 0xF2,0x0F,0x2A,0xF0 )            /* cvtsi2sd    xmm6,eax  */ \
_LINE4( 0xF2,0x0F,0x58,0xDA )            /* addsd       xmm3,xmm2  */ \
_LINE5( 0x66,0x0F,0xC6,0xE9,0x02 )       /* shufpd      xmm5,xmm1,2  */ \
_LINE4( 0xF2,0x0F,0x5E,0xF3 )            /* divsd       xmm6,xmm3  */ \
_LINE4( 0x66,0x0F,0x5C,0xE0 )            /* subpd       xmm4,xmm0  */ \
_LINE3( 0x0F,0x16,0xF6 )                 /* movlhps     xmm6,xmm6  */ \
_LINE4( 0xF2,0x0F,0x5C,0xE9 )            /* subsd       xmm5,xmm1  */ \
_LINE4( 0x66,0x0F,0x59,0xE6 )            /* mulpd       xmm4,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xEE )            /* mulpd       xmm5,xmm6  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )            /* mov         eax,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x11,0x20 )                 /* movups      xmmword ptr [eax],xmm4  */ \
_LINE4( 0x0F,0x11,0x68,0x10 )            /* movups      xmmword ptr [eax+10h],xmm5  */ \
_END_ASM

#define QUATERNIONPDDINVSSE4_STD2 \
_BEGIN_ASM \
ASM( xor eax,eax ) \
_LINE4( 0x8B,0x54,0x24,0x04 )            /* mov         edx,dword ptr [esp+4]  */ \
ASM( mov [esp-12],eax ) \
_LINE4( 0xF2,0x0F,0xF0,0x02 )            /* lddqu       xmm0,xmmword ptr [edx]  */ \
ASM( mov [esp-8],eax ) \
_LINE5( 0xF2,0x0F,0xF0,0x4A,0x10 )       /* lddqu       xmm1,xmmword ptr [edx+10h]  */ \
ASM( mov byte ptr [esp-5],0x80 ) \
_LINE3( 0x0F,0x28,0xD0 )                 /* movaps      xmm2,xmm0  */ \
ASM( movsd xmm5,[esp-12] ) \
_LINE3( 0x0F,0x28,0xD9 )                 /* movaps      xmm3,xmm1  */ \
ASM( movddup xmm7,xmm5 ) \
_LINE6( 0x66,0x0F,0x3A,0x41,0xD2,0x31 )  /* dppd        xmm2,xmm2,31h  */ \
ASM( mov word ptr [esp-6],0x3FF0 ) \
ASM( xorps xmm0,xmm7 ) \
_LINE6( 0x66,0x0F,0x3A,0x41,0xDB,0x31 )  /* dppd        xmm3,xmm3,31h  */ \
_LINE4( 0xF2,0x0F,0x58,0xDA )            /* addsd       xmm3,xmm2  */ \
ASM( movsd xmm6,[esp-12] ) \
ASM( xorps xmm1,xmm5 ) \
_LINE4( 0xF2,0x0F,0x5E,0xF3 )            /* divsd       xmm6,xmm3  */ \
_LINE3( 0x0F,0x16,0xF6 )                 /* movlhps     xmm6,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xC6 )            /* mulpd       xmm0,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xCE )            /* mulpd       xmm1,xmm6  */ \
_LINE4( 0x8B,0x44,0x24,0x08 )            /* mov         eax,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x11,0x00 )                 /* movups      xmmword ptr [eax],xmm0  */ \
_LINE4( 0x0F,0x11,0x48,0x10 )            /* movups      xmmword ptr [eax+10h],xmm1  */ \
_END_ASM

#define QUATERNIONPDDINVSSE4_STD3 \
_BEGIN_ASM \
ASM( mov eax,-1  ) \
ASM( xorps       xmm2,xmm2  ) \
_LINE4( 0xF2,0x0F,0x2A,0xC0 )            /* cvtsi2sd    xmm0,eax  */ \
ASM( mov edx,[esp+8]  ) \
ASM( mov ecx,[esp+4]  ) \
ASM( mulsd xmm0,xmm2 ) \
ASM( mov eax,1  ) \
ASM( movsd       xmm7,mmword ptr [ecx]  ) \
ASM( xorps       xmm7,xmm0  ) \
ASM( movsd       mmword ptr [edx],xmm7  ) \
ASM( movsd       xmm6,mmword ptr [ecx+8]  ) \
ASM( xorps       xmm6,xmm0  ) \
ASM( movsd       mmword ptr [edx+8],xmm6  ) \
ASM( movsd       xmm5,mmword ptr [ecx+10h]  ) \
ASM( xorps       xmm5,xmm0  ) \
_LINE4( 0xF2,0x0F,0x2A,0xD8 )            /* cvtsi2sd    xmm3,eax  */ \
ASM( movsd       mmword ptr [edx+10h],xmm5  ) \
ASM( movsd       xmm4,mmword ptr [ecx+8]  ) \
ASM( movsd       xmm0,mmword ptr [ecx]  ) \
ASM( movsd       xmm1,mmword ptr [ecx+10h]  ) \
ASM( mulsd       xmm0,xmm0  ) \
ASM( mulsd       xmm4,xmm4  ) \
ASM( mulsd       xmm1,xmm1  ) \
ASM( movsd       xmm2,mmword ptr [ecx+18h]  ) \
ASM( addsd       xmm4,xmm0  ) \
ASM( mulsd       xmm2,xmm2  ) \
ASM( addsd       xmm4,xmm1  ) \
ASM( addsd       xmm4,xmm2  ) \
ASM( divsd       xmm3,xmm4  ) \
ASM( movapd      xmm0,xmm3  ) \
ASM( movapd      xmm1,xmm3  ) \
ASM( mulsd       xmm0,xmm7  ) \
ASM( mulsd       xmm1,xmm6  ) \
ASM( movsd       mmword ptr [edx],xmm0  ) \
ASM( movapd      xmm0,xmm3  ) \
ASM( movsd       mmword ptr [edx+8],xmm1  ) \
ASM( mulsd       xmm3,mmword ptr [ecx+18h]  ) \
ASM( mulsd       xmm0,xmm5  ) \
ASM( movsd       mmword ptr [edx+10h],xmm0  ) \
ASM( movsd       mmword ptr [edx+18h],xmm3  ) \
_END_ASM

#define QUATERNIONPDDINVSSE4_STD5 \
_BEGIN_ASM \
ASM( mov eax,-1  ) \
_LINE4( 0x8B,0x54,0x24,0x04 )            /* mov         edx,dword ptr [esp+4]  */ \
ASM( xorps       xmm7,xmm7  ) \
_LINE4( 0xF2,0x0F,0xF0,0x02 )            /* lddqu       xmm0,xmmword ptr [edx]  */ \
_LINE4( 0xF2,0x0F,0x2A,0xE8 )            /* cvtsi2sd    xmm5,eax  */ \
_LINE5( 0xF2,0x0F,0xF0,0x4A,0x10 )       /* lddqu       xmm1,xmmword ptr [edx+10h]  */ \
ASM( mulsd xmm5,xmm7 ) \
_LINE3( 0x0F,0x28,0xD0 )                 /* movaps      xmm2,xmm0  */ \
_LINE3( 0x0F,0x28,0xD9 )                 /* movaps      xmm3,xmm1  */ \
ASM( movddup xmm7,xmm5 ) \
_LINE6( 0x66,0x0F,0x3A,0x41,0xD2,0x31 )  /* dppd        xmm2,xmm2,31h  */ \
ASM( mov eax,1  ) \
ASM( xorps xmm0,xmm7 ) \
_LINE6( 0x66,0x0F,0x3A,0x41,0xDB,0x31 )  /* dppd        xmm3,xmm3,31h  */ \
_LINE4( 0xF2,0x0F,0x58,0xDA )            /* addsd       xmm3,xmm2  */ \
_LINE4( 0xF2,0x0F,0x2A,0xF0 )            /* cvtsi2sd    xmm6,eax  */ \
ASM( xorps xmm1,xmm5 ) \
_LINE4( 0x8B,0x44,0x24,0x08 )            /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0xF2,0x0F,0x5E,0xF3 )            /* divsd       xmm6,xmm3  */ \
_LINE3( 0x0F,0x16,0xF6 )                 /* movlhps     xmm6,xmm6  */ \
_LINE4( 0x66,0x0F,0x59,0xC6 )            /* mulpd       xmm0,xmm6  */ \
_LINE3( 0x0F,0x11,0x00 )                 /* movups      xmmword ptr [eax],xmm0  */ \
_LINE4( 0x66,0x0F,0x59,0xCE )            /* mulpd       xmm1,xmm6  */ \
_LINE4( 0x0F,0x11,0x48,0x10 )            /* movups      xmmword ptr [eax+10h],xmm1  */ \
_END_ASM

#endif /* GEN3_QUATERNION_INV_H */
