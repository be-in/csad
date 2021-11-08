//=============================================================================
///**
// *  @file   vector_quaternion.h
// *
// *  $Id: vector_quaternion.h 17.08.2011  $
// *
// *  @brief generator 3, MS Visual C++ 2003-2008
// *
// *  @author Panteleym_onov Aleks_andr Konstantino_vich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_VECTOR_QUATERNION_H
#define GEN3_VECTOR_QUATERNION_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** QUATERNION STDCALL *********************************
// vector quaternion [eax]-a void * [edx]-b void * rez

/// ѕреобразование четырехмерного вектора в кватернион одинарной точности, команды FPU
#define VECTORP4DQUATERNIONFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE2( 0xD9,0xC2 )                                         /* fld         st(2)  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xD9,0xC2 )                                         /* fld         st(2)  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xC1 )                                         /* fld         st(1)  */ \
_LINE2( 0xDC,0xC8 )                                         /* fmul        st(0),st  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8] */ \
_LINE2( 0xD9,0xFA )                                         /* fsqrt             */ \
_LINE2( 0xD9,0xE8 )                                         /* fld1  */ \
_LINE2( 0xD9,0xE0 )                                         /* fchs  */ \
_LINE3( 0xD9,0x40,0x0C )                                    /* fld         dword ptr [eax+12]  */ \
_LINE2( 0xD9,0xFD )                                         /* fscale */ \
_LINE2( 0xDD,0xD9 )                                         /* fstp        st(1) */ \
_LINE2( 0xD9,0xFB )                                         /* fsincos  */ \
_LINE3( 0xD9,0x5A,0x0C )                                    /* fstp        dword ptr [edx+12]  */ \
_LINE2( 0xD9,0xEE )                                         /* fldz */ \
_LINE2( 0xD8,0xDA )                                         /* fcomp       st(2) */ \
_LINE2( 0xDF,0xE0 )                                         /* fnstsw      ax */ \
_LINE1( 0x9E )                                              /* sahf */ \
_LINE2( 0x74,0x04 )                                         /* je */ \
_LINE2( 0xDE,0xF1 )                                         /* fdivrp      st(1),st  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0) */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xDE,0xCC )                                         /* fmulp       st(4),st  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xDE,0xCB )                                         /* fmulp       st(3),st  */ \
_LINE2( 0xDE,0xC9 )                                         /* fmulp       st(1),st  */ \
_LINE3( 0xD9,0x5A,0x08 )                                    /* fstp        dword ptr [edx+8]  */ \
_LINE3( 0xD9,0x5A,0x04 )                                    /* fstp        dword ptr [edx+4]  */ \
_LINE2( 0xD9,0x1A )                                         /* fstp        dword ptr [edx]  */ \
_END_ASM

/// ѕреобразование четырехмерного вектора в кватернион одинарной точности, команды SSE
#define VECTORP4DQUATERNIONSSE_STD \
_BEGIN_ASM \
ASM( lea ecx,[fastsindividef] ) \
_LINE5( 0xB8,0xFF,0xFF,0xFF,0xFF )         /* mov         eax,0FFFFFFFFh  */ \
_LINE4( 0xF3,0x0F,0x2A,0xE8 )              /* cvtsi2ss    xmm5,eax  */ \
_LINE5( 0xBA,0x01,0x00,0x00,0x00 )         /* mov         edx,1  */ \
_LINE4( 0xF3,0x0F,0x2A,0xC2 )              /* cvtsi2ss    xmm0,edx  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )              /* mov         eax,dword ptr [esp+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x0C )         /* movss       xmm1,dword ptr [eax+0Ch]  */ \
ASM( mulss xmm1,[ecx] ) \
_LINE3( 0x0F,0x57,0xDB )                   /* xorps       xmm3,xmm3  */ \
_LINE4( 0xF3,0x0F,0x10,0xD9 )              /* movss       xmm3,xmm1  */ \
_LINE4( 0xF3,0x0F,0x59,0xDB )              /* mulss       xmm3,xmm3  */ \
_LINE4( 0x0F,0xC6,0xCB,0x00 )              /* shufps      xmm1,xmm3,0  */ \
_LINE4( 0xF3,0x0F,0x10,0xE3 )              /* movss       xmm4,xmm3  */ \
_LINE4( 0xF3,0x0F,0x59,0xDB )              /* mulss       xmm3,xmm3  */ \
_LINE4( 0x0F,0xC6,0xE3,0x00 )              /* shufps      xmm4,xmm3,0  */ \
_LINE4( 0x0F,0xC6,0xE1,0x08 )              /* shufps      xmm4,xmm1,8  */ \
_LINE4( 0x0F,0xC6,0xE4,0x42 )              /* shufps      xmm4,xmm4,42h  */ \
_LINE4( 0x0F,0xC6,0xC9,0x20 )              /* shufps      xmm1,xmm1,20h  */ \
_LINE3( 0x0F,0x59,0xCC )                   /* mulps       xmm1,xmm4  */ \
_LINE4( 0x0F,0xC6,0xE8,0x00 )              /* shufps      xmm5,xmm0,0  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )              /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x16,0xC4 )                   /* movlhps     xmm0,xmm4  */ \
_LINE3( 0x0F,0x59,0xCD )                   /* mulps       xmm1,xmm5  */ \
_LINE4( 0x0F,0xC6,0xC0,0x88 )              /* shufps      xmm0,xmm0,88h  */ \
_LINE4( 0x0F,0x16,0x51,0x08 )              /* movhps      xmm2,qword ptr [ecx+8]  */ \
_LINE3( 0x0F,0x12,0x11 )                   /* movlps      xmm2,qword ptr [ecx]  */ \
_LINE4( 0x0F,0x12,0x61,0x10 )              /* movlps      xmm4,qword ptr [ecx+10h]  */ \
_LINE4( 0x0F,0x16,0x61,0x18 )              /* movhps      xmm4,qword ptr [ecx+18h]  */ \
_LINE3( 0x0F,0x59,0xD1 )                   /* mulps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x59,0xCB )                   /* mulps       xmm1,xmm3  */ \
_LINE3( 0x0F,0x59,0xE1 )                   /* mulps       xmm4,xmm1  */ \
_LINE4( 0x0F,0x16,0x69,0x28 )              /* movhps      xmm5,qword ptr [ecx+28h]  */ \
_LINE4( 0x0F,0x12,0x69,0x20 )              /* movlps      xmm5,qword ptr [ecx+20h]  */ \
_LINE3( 0x0F,0x58,0xD4 )                   /* addps       xmm2,xmm4  */ \
_LINE3( 0x0F,0x59,0xCB )                   /* mulps       xmm1,xmm3  */ \
_LINE4( 0x0F,0x16,0x71,0x38 )              /* movhps      xmm6,qword ptr [ecx+38h]  */ \
_LINE4( 0x0F,0x12,0x71,0x30 )              /* movlps      xmm6,qword ptr [ecx+30h]  */ \
_LINE3( 0x0F,0x59,0xE9 )                   /* mulps       xmm5,xmm1  */ \
_LINE3( 0x0F,0x59,0xCB )                   /* mulps       xmm1,xmm3  */ \
_LINE3( 0x0F,0x58,0xD5 )                   /* addps       xmm2,xmm5  */ \
_LINE3( 0x0F,0x59,0xF1 )                   /* mulps       xmm6,xmm1  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )              /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0x0F,0x58,0xD6 )                   /* addps       xmm2,xmm6  */ \
_LINE3( 0x0F,0x12,0xCA )                   /* movhlps     xmm1,xmm2  */ \
_LINE3( 0x0F,0x58,0xD1 )                   /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x58,0xD0 )                   /* addps       xmm2,xmm0  */ \
_LINE3( 0x0F,0x57,0xDB )                   /* xorps       xmm3,xmm3  */ \
_LINE5( 0xF3,0x0F,0x11,0x52,0x0C )         /* movss       dword ptr [edx+0Ch],xmm2  */ \
_LINE4( 0x0F,0xC6,0xD2,0x01 )              /* shufps      xmm2,xmm2,1  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )         /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x00 )                   /* movhps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xC8 )                   /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x59,0xC9 )                   /* mulps       xmm1,xmm1  */ \
_LINE3( 0x0F,0x12,0xE1 )                   /* movhlps     xmm4,xmm1  */ \
_LINE4( 0xF3,0x0F,0x58,0xCC )              /* addss       xmm1,xmm4  */ \
_LINE4( 0x0F,0xC6,0xE4,0x01 )              /* shufps      xmm4,xmm4,1  */ \
_LINE4( 0xF3,0x0F,0x58,0xCC )              /* addss       xmm1,xmm4  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC9,0xD1 )    /* dpps        xmm1,xmm1,0D1h  */ \
_LINE5( 0xF2,0x0F,0xC2,0xD9,0x00 )         /* cmpeqsd     xmm3,xmm1  */ \
_LINE3( 0x0F,0x50,0xC3 )                   /* movmskps    eax,xmm3  */ \
_LINE2( 0xA8,0x01 )                        /* test        al,1  */ \
_LINE2( 0x75,0x08 )                        /* jne         VTQS (9869C2h)  */ \
_LINE4( 0xF3,0x0F,0x51,0xC9 )              /* sqrtss      xmm1,xmm1  */ \
_LINE4( 0xF3,0x0F,0x5E,0xD1 )              /* divss       xmm2,xmm1  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )              /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xC2 )                   /* mulps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x17,0x02 )                   /* movhps      qword ptr [edx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x42,0x08 )         /* movss       dword ptr [edx+8],xmm0  */ \
_END_ASM

/// ѕреобразование четырехмерного вектора в кватернион одинарной точности, команды SSE4
#define VECTORP4DQUATERNIONSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
ASM( movss xmm1,[eax+0x0C] ) \
ASM( lea ecx,bt::fastsindividef ) \
ASM( mov eax,-1 ) \
ASM( CVTSI2SS xmm5,eax ) \
ASM( mulss xmm1,[ecx] ) \
ASM( mov edx,1 ) \
ASM( CVTSI2SS xmm0,edx ) \
ASM( xorps xmm3,xmm3 ) \
ASM( movss xmm3,xmm1 ) \
ASM( mulss xmm3,xmm3 ) \
ASM( shufps xmm1,xmm3,0x00 ) \
ASM( movss xmm4,xmm3 ) \
ASM( mulss xmm3,xmm3 ) \
ASM( shufps xmm4,xmm3,0x00 ) \
ASM( shufps xmm4,xmm1,0x08 ) \
ASM( shufps xmm4,xmm4,0x42 ) \
ASM( shufps xmm1,xmm1,0x20 ) \
ASM( mulps xmm1,xmm4 ) \
ASM( shufps xmm5,xmm0,0x00 ) \
ASM( shufps xmm3,xmm3,0x00 ) \
ASM( movlhps xmm0,xmm4 ) \
ASM( mulps xmm1,xmm5 ) \
ASM( shufps xmm0,xmm0,0x88 ) \
ASM( lddqu xmm2,[ecx] ) \
ASM( lddqu xmm4,[ecx+0x10] ) \
ASM( mulps xmm2,xmm1 ) \
ASM( mulps xmm1,xmm3 ) \
ASM( mulps xmm4,xmm1 ) \
ASM( lddqu xmm5,[ecx+0x20] ) \
ASM( addps xmm2,xmm4 ) \
ASM( mulps xmm1,xmm3 ) \
ASM( lddqu xmm6,[ecx+0x30] ) \
ASM( mulps xmm5,xmm1 ) \
ASM( mulps xmm1,xmm3 ) \
ASM( addps xmm2,xmm5 ) \
ASM( mulps xmm6,xmm1 ) \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8] */ \
ASM( addps xmm2,xmm6 ) \
ASM( movhlps xmm1,xmm2 ) \
ASM( addps xmm2,xmm1 ) \
ASM( addps xmm2,xmm0 ) \
ASM( xorps xmm3,xmm3 ) \
ASM( movss [edx+0x0C],xmm2 ) \
ASM( shufps xmm2,xmm2,0x1 ) \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x00 )                                    /* movhps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC9,0xD1 )                     /* dpps        xmm1,xmm1,0D1h  */ \
ASM( cmpeqsd xmm3,xmm1 ) \
ASM( movmskps eax,xmm3 ) \
ASM( test        al,1 ) \
ASM( jne VTQS1 ) \
_LINE4( 0xF3,0x0F,0x51,0xC9 )                               /* sqrtss      xmm1,xmm1  */ \
ASM( divss xmm2,xmm1 ) \
ASM( VTQS1: ) \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
ASM( mulps xmm0,xmm2 ) \
_LINE3( 0x0F,0x17,0x02 )                                    /* movhps      qword ptr [edx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x42,0x08 )                          /* movss       dword ptr [edx+8],xmm0  */ \
_END_ASM

/// ѕреобразование четырехмерного вектора в кватернион двойной точности, команды FPU
#define VECTORP4DDQUATERNIONFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
_LINE2( 0xDD,0x00 )                                         /* fld         qword ptr [eax]  */ \
_LINE3( 0xDD,0x40,0x08 )                                    /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDD,0x40,0x10 )                                    /* fld         qword ptr [eax+16]  */ \
_LINE2( 0xD9,0xC2 )                                         /* fld         st(2)  */ \
ASM( fmul st(0),st(0) ) \
_LINE2( 0xD9,0xC2 )                                         /* fld         st(2)  */ \
ASM( fmul st(0),st(0) ) \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xC1 )                                         /* fld         st(1)  */ \
ASM( fmul st(0),st(0) ) \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8] */ \
_LINE2( 0xD9,0xFA )                                         /* fsqrt             */ \
ASM( fld1 ) \
ASM( fchs ) \
_LINE3( 0xDD,0x40,0x18 )                                    /* fld         qword ptr [eax+24]  */ \
_LINE2( 0xD9,0xFD )                                         /* fscale */ \
_LINE2( 0xDD,0xD9 )                                         /* fstp        st(1) */ \
_LINE2( 0xD9,0xFB )                                         /* fsincos  */ \
_LINE3( 0xDD,0x5A,0x18 )                                    /* fstp        qword ptr [edx+24]  */ \
_LINE2( 0xD9,0xEE )                                         /* fldz */ \
_LINE2( 0xD8,0xDA )                                         /* fcomp       st(2) */ \
_LINE2( 0xDF,0xE0 )                                         /* fnstsw      ax */ \
_LINE1( 0x9E )                                              /* sahf */ \
_LINE2( 0x74,0x04 )                                         /* je */ \
_LINE2( 0xDE,0xF1 )                                         /* fdivrp      st(1),st  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0) */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
ASM( fmulp st(4),st(0) ) \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
ASM( fmulp st(3),st(0) ) \
ASM( fmulp st(1),st(0) ) \
_LINE3( 0xDD,0x5A,0x10 )                                    /* fstp        qword ptr [edx+16]  */ \
_LINE3( 0xDD,0x5A,0x08 )                                    /* fstp        qword ptr [edx+8]  */ \
_LINE2( 0xDD,0x1A )                                         /* fstp        qword ptr [edx]  */ \
_END_ASM

/// ѕреобразование четырехмерного вектора в кватернион двойной точности, команды SSE4
#define VECTORP4DDQUATERNIONSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
ASM( movsd xmm1,[eax+0x18] ) \
ASM( mov eax,-1 ) \
ASM( CVTSI2SD xmm5,eax ) \
ASM( mov edx,1 ) \
ASM( CVTSI2SD xmm0,edx ) \
ASM( lea ecx,bt::fastsindivided ) \
ASM( mulsd xmm1,[ecx] ) \
ASM( xorps xmm3,xmm3 ) \
ASM( movsd xmm3,xmm1 ) \
ASM( mulsd xmm3,xmm3 ) \
ASM( movsd xmm4,xmm1 ) \
ASM( mulsd xmm1,xmm3 ) \
ASM( movlhps xmm1,xmm1 ) \
ASM( movlhps xmm3,xmm3 ) \
ASM( movhlps xmm1,xmm3 ) \
ASM( movlhps xmm4,xmm4 ) \
ASM( movlhps xmm5,xmm5 ) \
ASM( movlhps xmm0,xmm4 ) \
ASM( mulpd xmm3,xmm5 ) \
ASM( mulpd xmm1,xmm5 ) \
ASM( movapd xmm2,[ecx] ) \
ASM( movapd xmm4,[ecx+0x10] ) \
ASM( mulpd xmm2,xmm1 ) \
ASM( mulpd xmm1,xmm3 ) \
ASM( mulpd xmm4,xmm1 ) \
ASM( movapd xmm5,[ecx+0x20] ) \
ASM( movapd xmm6,[ecx+0x30] ) \
ASM( addpd xmm2,xmm4 ) \
ASM( mulpd xmm1,xmm3 ) \
ASM( mulpd xmm5,xmm1 ) \
ASM( mov eax,[esp+12] ) \
ASM( mulpd xmm1,xmm3 ) \
ASM( addpd xmm2,xmm5 ) \
ASM( mulpd xmm6,xmm1 ) \
ASM( mov edx,[esp+16] ) \
ASM( addpd xmm2,xmm6 ) \
ASM( mulpd xmm1,xmm3 ) \
ASM( movapd xmm7,[ecx+0x40] ) \
ASM( movapd xmm4,[ecx+0x50] ) \
ASM( mulpd xmm7,xmm1 ) \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
ASM( mulpd xmm1,xmm3 ) \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8] */ \
ASM( mulpd xmm4,xmm1 ) \
ASM( addpd xmm2,xmm7 ) \
ASM( mulpd xmm1,xmm3 ) \
ASM( movapd xmm5,[ecx+0x60] ) \
ASM( movapd xmm6,[ecx+0x70] ) \
ASM( mulpd xmm1,xmm3 ) \
ASM( addpd xmm2,xmm4 ) \
ASM( mulpd xmm5,xmm1 ) \
ASM( mulpd xmm6,xmm1 ) \
ASM( addpd xmm2,xmm6 ) \
ASM( movsd xmm1,[eax+0x10] ) \
ASM( addpd xmm2,xmm0 ) \
ASM( mulsd xmm1,xmm1 ) \
ASM( xorpd xmm3,xmm3 ) \
_LINE4( 0xF2,0x0F,0xF0,0x00 )                               /* lddqu       xmm0,xmmword ptr [eax]  */ \
ASM( movsd [edx+24],xmm2 ) \
ASM( movapd xmm4,xmm0 ) \
ASM( movhlps xmm2,xmm2 ) \
ASM( movapd xmm5,xmm1 ) \
_LINE6( 0x66,0x0F,0x3A,0x41,0xC0,0x31 )                     /* dppd        xmm0,xmm0,31h  */ \
ASM( addsd xmm1,xmm0 ) \
ASM( cmpeqsd xmm3,xmm1 ) \
ASM( movmskps eax,xmm3 ) \
ASM( test        al,1 ) \
ASM( jne VDTQS2 ) \
_LINE4( 0xF2,0x0F,0x51,0xC9 )                               /* sqrtsd      xmm1,xmm1  */ \
ASM( divsd xmm2,xmm1 ) \
ASM( VDTQS2: ) \
ASM( movlhps xmm2,xmm2 ) \
ASM( mulpd xmm4,xmm2 ) \
ASM( mulsd xmm5,xmm2 ) \
ASM( movlps [edx+16],xmm5 ) \
ASM( movupd [edx],xmm4 ) \
_END_ASM

//**************************** FAST QUATERNION STDCALL *********************************
// vector fast quaternion [eax]-a void * [edx]-b void * rez

/// ѕреобразование четырехмерного вектора в кватернион одинарной точности, команды SSE4
#define VECTORP4DFASTQUATERNIONSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
ASM( movss xmm1,[eax+0x0C] ) \
ASM( mov eax,-1 ) \
ASM( CVTSI2SS xmm5,eax ) \
ASM( mov edx,1 ) \
ASM( CVTSI2SS xmm0,edx ) \
ASM( lea ecx,bt::fastsindividef ) \
ASM( mulss xmm1,[ecx] ) \
ASM( xorps xmm3,xmm3 ) \
ASM( movss xmm3,xmm1 ) \
ASM( mulss xmm3,xmm3 ) \
ASM( shufps xmm1,xmm3,0x00 ) \
ASM( movss xmm4,xmm3 ) \
ASM( mulss xmm3,xmm3 ) \
ASM( shufps xmm4,xmm3,0x00 ) \
ASM( shufps xmm4,xmm1,0x08 ) \
ASM( shufps xmm4,xmm4,0x42 ) \
ASM( shufps xmm1,xmm1,0x20 ) \
ASM( mulps xmm1,xmm4 ) \
ASM( shufps xmm5,xmm0,0x00 ) \
ASM( shufps xmm3,xmm3,0x00 ) \
ASM( movlhps xmm0,xmm4 ) \
ASM( mulps xmm1,xmm5 ) \
ASM( shufps xmm0,xmm0,0x88 ) \
ASM( lddqu xmm2,[ecx] ) \
ASM( lddqu xmm4,[ecx+0x10] ) \
ASM( mulps xmm2,xmm1 ) \
ASM( mulps xmm1,xmm3 ) \
ASM( mulps xmm4,xmm1 ) \
ASM( lddqu xmm5,[ecx+0x20] ) \
ASM( addps xmm2,xmm4 ) \
ASM( mulps xmm1,xmm3 ) \
ASM( mulps xmm5,xmm1 ) \
ASM( addps xmm2,xmm5 ) \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8] */ \
ASM( movhlps xmm1,xmm2 ) \
ASM( addps xmm2,xmm1 ) \
ASM( addps xmm2,xmm0 ) \
ASM( xorps xmm3,xmm3 ) \
ASM( movss [edx+0x0C],xmm2 ) \
ASM( shufps xmm2,xmm2,0x1 ) \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x00 )                                    /* movhps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE6( 0x66,0x0F,0x3A,0x40,0xC9,0xD1 )                     /* dpps        xmm1,xmm1,0D1h  */ \
ASM( cmpeqsd xmm3,xmm1 ) \
ASM( movmskps eax,xmm3 ) \
ASM( test        al,1 ) \
ASM( jne VTQS3 ) \
ASM( rsqrtss xmm1,xmm1 ) \
ASM( mulss xmm2,xmm1 ) \
ASM( VTQS3: ) \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
ASM( mulps xmm0,xmm2 ) \
_LINE3( 0x0F,0x17,0x02 )                                    /* movhps      qword ptr [edx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x42,0x08 )                          /* movss       dword ptr [edx+8],xmm0  */ \
_END_ASM

#endif
