//=============================================================================
///**
// *  @file vector_proj.h
// *
// *  $Id: vector_proj.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float project, MS Visual C++ 2003-2008
// *
// *  @author Pant_eleymonov Alek_sandr Kons_tantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

//**************************** PROJECT STDCALL *********************************
// project vectors eax=[esp+4]-v void *, [esp+8]-matrix void *  [esp+12]-viewScale void *  [esp+16]-viewOffset void *  [esp+20]-v rez void *
//  additional eax - return clip flag

///  вычисление проекции двухмерного вектора на плоскость экрана, команды SSE3
#define VECTORP2DPROJECTSSE3_STD \
_BEGIN_ASM \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x08))               /* mov         eax,dword ptr [esp+8] */ \
_LINE4( 0xF2,0x0F,0xF0,0x20 )                               /* lddqu       xmm4,[eax]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x68,0x10 )                          /* lddqu       xmm5,[eax+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x78,0x30 )                          /* lddqu       xmm7,[eax+30h]  */ \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x04))               /* mov         eax,dword ptr [esp+04h] */ \
_LINE4( 0xF3,0x0F,0x10,0x10 )                               /* movss       xmm2,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
_LINE3( 0x0F,0x28,0xDA )                                    /* movaps      xmm3,xmm2  */ \
_LINE4( 0x0F,0xC6,0xDB,0xFF )                               /* shufps      xmm3,xmm3,0FFh  */ \
_LINE3( 0x0F,0x57,0xC0 )                                    /* xorps       xmm0,xmm0  */ \
_LINE4( 0xF3,0x0F,0x10,0xCB )                               /* movss       xmm1,xmm3  */ \
_LINE3( 0x0F,0x57,0xFF )                                    /* xorps       xmm7,xmm7  */ \
_LINE3( 0x0F,0x5C,0xC3 )                                    /* subps       xmm0,xmm3  */ \
_LINE4( 0x0F,0xC2,0xDA,0x01 )                               /* cmpltps     xmm3,xmm2  */ \
_LINE4( 0x0F,0xC2,0xC2,0x06 )                               /* cmpnleps    xmm0,xmm2  */ \
_LINE5( 0xF3,0x0F,0xC2,0xF9,0x00 )                          /* cmpeqss     xmm7,xmm1  */ \
_LINE3( 0x0F,0x50,0xC7 )                                    /* movmskps    eax,xmm7  */ \
_LINE2( 0xA8,0x01 )                                         /* test        al,1  */ \
_LINE2( 0x75,0x24 )                                         /* jne         ddd (11B14D0h)  */ \
_LINE5( 0xB8,0x00,0x00,0x80,0x3F )                          /* mov         eax,3F800000h  */ \
_LINE4( 0x66,0x0F,0x6E,0xF8 )                               /* movd        xmm7,eax  */ \
_LINE4( 0xF3,0x0F,0x5E,0xF9 )                               /* divss       xmm7,xmm1  */ \
_LINE5( 0xF3,0x0F,0xC2,0xCF,0x00 )                          /* cmpeqss     xmm1,xmm7  */ \
_LINE3( 0x0F,0x50,0xC1 )                                    /* movmskps    eax,xmm1  */ \
_LINE4( 0xF3,0x0F,0x10,0xCF )                               /* movss       xmm1,xmm7  */ \
_LINE2( 0xA8,0x01 )                                         /* test        al,1  */ \
_LINE2( 0x75,0x07 )                                         /* jne         ddd (11B14D0h)  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xD1 )                                    /* mulps       xmm2,xmm1  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x4E )                               /* shufps      xmm2,xmm2,4Eh  */ \
_LINE5( 0xF3,0x0F,0x10,0x60,0x08 )                          /* movss       xmm4,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x20 )                                    /* movhps      xmm4,qword ptr [eax]  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE4( 0x8B,0x44,0x24,0x10 )                               /* mov         eax,dword ptr [esp+10h]  */ \
_LINE5( 0xF3,0x0F,0x10,0x68,0x08 )                          /* movss       xmm5,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x28 )                                    /* movhps      xmm5,qword ptr [eax]  */ \
_LINE3( 0x0F,0x58,0xD5 )                                    /* addps       xmm2,xmm5  */ \
_LINE4( 0x8B,0x44,0x24,0x14 )                               /* mov         eax,dword ptr [esp+14h]  */ \
_LINE3( 0x0F,0x17,0x10 )                                    /* movhps      qword ptr [eax],xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x50,0x08 )                          /* movss       dword ptr [eax+8],xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x48,0x0C )                          /* movss       dword ptr [eax+0xC],xmm1  */ \
_LINE3( 0x0F,0x50,0xC3 )                                    /* movmskps    eax,xmm3  */ \
_LINE3( 0x0F,0x50,0xD0 )                                    /* movmskps    edx,xmm0  */ \
_LINE3( 0xC1,0xE2,0x04 )                                    /* shl         edx,4  */ \
_LINE2( 0x0B,0xC2 )                                         /* or          eax,edx  */ \
_LINE3( 0x83,0xE0,0x77 )                /* and         eax,77h  */ \
_END_ASM

/// вычисление проекции трехмерного вектора на плоскость экрана, команды FPU
#define VECTORP3DPROJECTFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B, 0x44, 0x24, 0x04)               /* mov         eax,dword ptr [esp+04h] */ \
_STR(_DB(0xD9) _DB(0x40) _DB(0x08))                         /* fld         dword ptr [eax+8] */ \
_STR(_DB(0xD9) _DB(0x40) _DB(0x04))                         /* fld         dword ptr [eax+4] */ \
_STR(_DB(0xD9) _DB(0x00))                                   /* fld         dword ptr [eax] */ \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x08))               /* mov         eax,dword ptr [esp+8] */ \
_STR(_DB(0xD9) _DB(0x00))                                   /* fld         dword ptr [eax] */ \
_STR(_DB(0xD8) _DB(0xC9))                                   /* fmul        st,st(1) */ \
_STR(_DB(0xD9) _DB(0x40) _DB(0x10))                         /* fld         dword ptr [eax+10h] */ \
_STR(_DB(0xD8) _DB(0xCB))                                   /* fmul        st,st(3) */ \
_STR(_DB(0xDE) _DB(0xC1))                                   /* faddp       st(1),st */ \
_STR(_DB(0xD9) _DB(0x40) _DB(0x20))                         /* fld         dword ptr [eax+20h] */ \
_STR(_DB(0xD8) _DB(0xCC))                                   /* fmul        st,st(4) */ \
_STR(_DB(0xDE) _DB(0xC1))                                   /* faddp       st(1),st */ \
_STR(_DB(0xD8) _DB(0x40) _DB(0x30))                         /* fadd        dword ptr [eax+30h] */ \
_STR(_DB(0xD9) _DB(0x40) _DB(0x04))                         /* fld         dword ptr [eax+4h] */ \
_STR(_DB(0xD8) _DB(0xCA))                                   /* fmul        st,st(2) */ \
_STR(_DB(0xD9) _DB(0x40) _DB(0x14))                         /* fld         dword ptr [eax+14h] */ \
_STR(_DB(0xD8) _DB(0xCC))                                   /* fmul        st,st(4) */ \
_STR(_DB(0xDE) _DB(0xC1))                                   /* faddp       st(1),st */ \
_STR(_DB(0xD9) _DB(0x40) _DB(0x24))                         /* fld         dword ptr [eax+24h] */ \
_STR(_DB(0xD8) _DB(0xCD))                                   /* fmul        st,st(5) */ \
_STR(_DB(0xDE) _DB(0xC1))                                   /* faddp       st(1),st */ \
_STR(_DB(0xD8) _DB(0x40) _DB(0x34))                         /* fadd        dword ptr [eax+34h] */ \
_STR(_DB(0xD9) _DB(0x40) _DB(0x08))                         /* fld         dword ptr [eax+8h] */ \
_STR(_DB(0xD8) _DB(0xCB))                                   /* fmul        st,st(3) */ \
_STR(_DB(0xD9) _DB(0x40) _DB(0x18))                         /* fld         dword ptr [eax+18h] */ \
_STR(_DB(0xD8) _DB(0xCD))                                   /* fmul        st,st(5) */ \
_STR(_DB(0xDE) _DB(0xC1))                                   /* faddp       st(1),st */ \
_STR(_DB(0xD9) _DB(0x40) _DB(0x28))                         /* fld         dword ptr [eax+28h] */ \
_STR(_DB(0xD8) _DB(0xCE))                                   /* fmul        st,st(6) */ \
_STR(_DB(0xDE) _DB(0xC1))                                   /* faddp       st(1),st */ \
_STR(_DB(0xD8) _DB(0x40) _DB(0x38))                         /* fadd        dword ptr [eax+38h] */ \
_STR(_DB(0xD9) _DB(0x40) _DB(0x0C))                         /* fld         dword ptr [eax+0Ch] */ \
_STR(_DB(0xD8) _DB(0xCC))                                   /* fmul        st,st(4) */ \
_STR(_DB(0xD9) _DB(0x40) _DB(0x1C))                         /* fld         dword ptr [eax+1Ch] */ \
_STR(_DB(0xD8) _DB(0xCE))                                   /* fmul        st,st(6) */ \
_STR(_DB(0xDE) _DB(0xC1))                                   /* faddp       st(1),st */ \
_STR(_DB(0xD9) _DB(0x40) _DB(0x2C))                         /* fld         dword ptr [eax+2Ch] */ \
_STR(_DB(0xD8) _DB(0xCF))                                   /* fmul        st,st(7) */ \
_STR(_DB(0xDE) _DB(0xC1))                                   /* faddp       st(1),st */ \
_STR(_DB(0xD8) _DB(0x40) _DB(0x3C))                         /* fadd        dword ptr [eax+3Ch] */ \
_STR(_DB(0x33) _DB(0xD2))                                   /* xor         edx,edx */ \
_STR(_DB(0xD8) _DB(0xD1))                                   /* fcom        st(1) */ \
_STR(_DB(0xDF) _DB(0xE0))                                   /* fnstsw      ax */ \
_STR(_DB(0x9E))                                             /* sahf */ \
_STR(_DB(0x73) _DB(0x03))                                   /* jae         fff1 (12914BDh) */ \
_STR(_DB(0x83) _DB(0xCA) _DB(0x04))                         /* or          edx,04h */ \
_STR(_DB(0xD8) _DB(0xD2))                                   /* fcom        st(2) */ \
_STR(_DB(0xDF) _DB(0xE0))                                   /* fnstsw      ax */ \
_STR(_DB(0x9E))                                             /* sahf */ \
_STR(_DB(0x73) _DB(0x03))                                   /* jae         fff2 (12914C8h) */ \
_STR(_DB(0x83) _DB(0xCA) _DB(0x02))                         /* or          edx,02h */ \
_STR(_DB(0xD8) _DB(0xD3))                                   /* fcom        st(3) */ \
_STR(_DB(0xDF) _DB(0xE0))                                   /* fnstsw      ax */ \
_STR(_DB(0x9E))                                             /* sahf */ \
_STR(_DB(0x73) _DB(0x03))                                   /* jae         fff3 (12914D3h) */ \
_STR(_DB(0x83) _DB(0xCA) _DB(0x01))                         /* or          edx,01h */ \
_STR(_DB(0xD9) _DB(0xE0))                                   /* fchs */ \
_STR(_DB(0xD8) _DB(0xD1))                                   /* fcom        st(1) */ \
_STR(_DB(0xDF) _DB(0xE0))                                   /* fnstsw      ax */ \
_STR(_DB(0x9E))                                             /* sahf */ \
_STR(_DB(0x76) _DB(0x03))                                   /* jbe         fff4 (12914E0h) */ \
_STR(_DB(0x83) _DB(0xCA) _DB(0x40))                         /* or          edx,40h */ \
_STR(_DB(0xD8) _DB(0xD2))                                   /* fcom        st(2) */ \
_STR(_DB(0xDF) _DB(0xE0))                                   /* fnstsw      ax */ \
_STR(_DB(0x9E))                                             /* sahf */ \
_STR(_DB(0x76) _DB(0x03))                                   /* jbe         fff5 (12914EBh) */ \
_STR(_DB(0x83) _DB(0xCA) _DB(0x20))                         /* or          edx,20h */ \
_STR(_DB(0xD8) _DB(0xD3))                                   /* fcom        st(3) */ \
_STR(_DB(0xDF) _DB(0xE0))                                   /* fnstsw      ax */ \
_STR(_DB(0x9E))                                             /* sahf */ \
_STR(_DB(0x76) _DB(0x03))                                   /* jbe         fff6 (12914F6h) */ \
_STR(_DB(0x83) _DB(0xCA) _DB(0x10))                         /* or          edx,10h */ \
_STR(_DB(0xD9) _DB(0xE0))                                   /* fchs */ \
_STR(_DB(0xD9) _DB(0xEE))                                   /* fldz */ \
_STR(_DB(0xD8) _DB(0xD9))                                   /* fcomp       st(1) */ \
_STR(_DB(0xDF) _DB(0xE0))                                   /* fnstsw      ax */ \
_STR(_DB(0x9E))                                             /* sahf */ \
_STR(_DB(0x74) _DB(0x13))                                   /* je          www1 (1291516h) */ \
_STR(_DB(0xD9) _DB(0xE8))                                   /* fld1 */ \
_STR(_DB(0xD8) _DB(0xD9))                                   /* fcomp       st(1) */ \
_STR(_DB(0xDF) _DB(0xE0))                                   /* fnstsw      ax */ \
_STR(_DB(0x9E))                                             /* sahf */ \
_STR(_DB(0x74) _DB(0x0A))                                   /* je          www1 (1291516h) */ \
_STR(_DB(0xD9) _DB(0xE8))                                   /* fld1 */ \
_STR(_DB(0xDE) _DB(0xF1))                                   /* fdivrp      st(1),st */ \
_STR(_DB(0xDC) _DB(0xC9))                                   /* fmul        st(1),st */ \
_STR(_DB(0xDC) _DB(0xCA))                                   /* fmul        st(2),st */ \
_STR(_DB(0xDC) _DB(0xCB))                                   /* fmul        st(3),st */ \
_STR(_DB(0x8B) _DB(0xC2))                                   /* mov         eax,edx */ \
_STR(_DB(0x8B) _DB(0x54) _DB(0x24) _DB(0x14))               /* mov         edx,dword ptr [esp+20h] */ \
_STR(_DB(0xD9) _DB(0x5A) _DB(0x0C))                         /* fstp        dword ptr [edx+0xC] */ \
_STR(_DB(0x8B) _DB(0x54) _DB(0x24) _DB(0x0C))               /* mov         edx,dword ptr [esp+12h] */ \
_STR(_DB(0xD9) _DB(0x42) _DB(0x08))                         /* fld         dword ptr [edx+8] */ \
_STR(_DB(0xDE) _DB(0xC9))                                   /* fmulp       st(1),st */ \
_STR(_DB(0xD9) _DB(0x42) _DB(0x04))                         /* fld         dword ptr [edx+4] */ \
_STR(_DB(0xDE) _DB(0xCA))                                   /* fmulp       st(2),st */ \
_STR(_DB(0xD9) _DB(0x02))                                   /* fld         dword ptr [edx] */ \
_STR(_DB(0xDE) _DB(0xCB))                                   /* fmulp       st(3),st */ \
_STR(_DB(0x8B) _DB(0x54) _DB(0x24) _DB(0x10))               /* mov         edx,dword ptr [esp+16h] */ \
_STR(_DB(0xD9) _DB(0x42) _DB(0x08))                         /* fld         dword ptr [edx+8] */ \
_STR(_DB(0xDE) _DB(0xC1))                                   /*  faddp       st(1),st */ \
_STR(_DB(0xD9) _DB(0x42) _DB(0x04))                         /* fld         dword ptr [edx+4] */ \
_STR(_DB(0xDE) _DB(0xC2))                                   /* faddp       st(2),st */ \
_STR(_DB(0xD9) _DB(0x02))                                   /* fld         dword ptr [edx] */ \
_STR(_DB(0xDE) _DB(0xC3))                                   /* faddp       st(3),st */ \
_STR(_DB(0x8B) _DB(0x54) _DB(0x24) _DB(0x14))               /* mov         edx,dword ptr [esp+20h] */ \
_STR(_DB(0xD9) _DB(0x5A) _DB(0x08))                         /* fstp        dword ptr [edx+8] */ \
_STR(_DB(0xD9) _DB(0x5A) _DB(0x04))                         /* fstp        dword ptr [edx+4] */ \
_STR(_DB(0xD9) _DB(0x1A))                                   /* fstp        dword ptr [edx] */ \
_STR(_DB(0xDD) _DB(0xD8))                                   /* fstp        st(0) */ \
_STR(_DB(0xDD) _DB(0xD8))                                   /* fstp        st(0) */ \
_STR(_DB(0xDD) _DB(0xD8))                                   /* fstp        st(0) */ \
_END_ASM

///  вычисление проекции трехмерного вектора на плоскость экрана, команды SSE
#define VECTORP3DPROJECTSSE_STD \
_BEGIN_ASM \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x08))               /* mov         eax,dword ptr [esp+8] */ \
_LINE3( 0x0F,0x12,0x20 )                                    /* movlps      xmm4,qword ptr [eax]  */ \
_LINE4( 0x0F,0x16,0x60,0x08 )                               /* movhps      xmm4,qword ptr [eax+8]  */ \
_STR(_DB(0x8B) _DB(0x4C) _DB(0x24) _DB(0x04))               /* mov         ecx,dword ptr [esp+04h] */ \
_LINE4( 0x0F,0x12,0x68,0x10 )                               /* movlps      xmm5,qword ptr [eax+10h]  */ \
_LINE4( 0xF3,0x0F,0x10,0x11 )                               /* movss       xmm2,dword ptr [ecx]  */ \
_LINE4( 0x0F,0x16,0x68,0x18 )                               /* movhps      xmm5,qword ptr [eax+18h]  */ \
_LINE5( 0xF3,0x0F,0x10,0x49,0x04 )                          /* movss       xmm1,dword ptr [ecx+4]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE4( 0x0F,0x12,0x70,0x20 )                               /* movlps      xmm6,qword ptr [eax+20h]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE4( 0x0F,0x16,0x70,0x28 )                               /* movhps      xmm6,qword ptr [eax+28h]  */ \
_LINE4( 0x0F,0x12,0x78,0x30 )                               /* movlps      xmm7,qword ptr [eax+30h]  */ \
_LINE4( 0x0F,0x16,0x78,0x38 )                               /* movhps      xmm7,qword ptr [eax+38h]  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x59,0x08 )                          /* movss       xmm3,dword ptr [ecx+8]  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x28,0xDA )                                    /* movaps      xmm3,xmm2  */ \
_LINE3( 0x0F,0x57,0xC0 )                                    /* xorps       xmm0,xmm0  */ \
_LINE4( 0x0F,0xC6,0xDB,0xFF )                               /* shufps      xmm3,xmm3,0FFh  */ \
_LINE4( 0xF3,0x0F,0x10,0xCB )                               /* movss       xmm1,xmm3  */ \
_LINE3( 0x0F,0x57,0xFF )                                    /* xorps       xmm7,xmm7  */ \
_LINE3( 0x0F,0x5C,0xC3 )                                    /* subps       xmm0,xmm3  */ \
_LINE4( 0x0F,0xC2,0xDA,0x01 )                               /* cmpltps     xmm3,xmm2  */ \
_LINE4( 0x0F,0xC2,0xC2,0x06 )                               /* cmpnleps    xmm0,xmm2  */ \
_LINE5( 0xF3,0x0F,0xC2,0xF9,0x00 )                          /* cmpeqss     xmm7,xmm1  */ \
_LINE3( 0x0F,0x50,0xC7 )                                    /* movmskps    eax,xmm7  */ \
_LINE2( 0xA8,0x01 )                                         /* test        al,1  */ \
_LINE2( 0x75,0x24 )                                         /* jne         ddd (11B14D0h)  */ \
_LINE5( 0xB8,0x00,0x00,0x80,0x3F )                          /* mov         eax,3F800000h  */ \
_LINE4( 0x66,0x0F,0x6E,0xF8 )                               /* movd        xmm7,eax  */ \
_LINE4( 0xF3,0x0F,0x5E,0xF9 )                               /* divss       xmm7,xmm1  */ \
_LINE5( 0xF3,0x0F,0xC2,0xCF,0x00 )                          /* cmpeqss     xmm1,xmm7  */ \
_LINE3( 0x0F,0x50,0xC1 )                                    /* movmskps    eax,xmm1  */ \
_LINE4( 0xF3,0x0F,0x10,0xCF )                               /* movss       xmm1,xmm7  */ \
_LINE2( 0xA8,0x01 )                                         /* test        al,1  */ \
_LINE2( 0x75,0x07 )                                         /* jne         ddd (11B14D0h)  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xD1 )                                    /* mulps       xmm2,xmm1  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x4E )                               /* shufps      xmm2,xmm2,4Eh  */ \
_LINE5( 0xF3,0x0F,0x10,0x60,0x08 )                          /* movss       xmm4,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x20 )                                    /* movhps      xmm4,qword ptr [eax]  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE4( 0x8B,0x44,0x24,0x10 )                               /* mov         eax,dword ptr [esp+10h]  */ \
_LINE5( 0xF3,0x0F,0x10,0x68,0x08 )                          /* movss       xmm5,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x28 )                                    /* movhps      xmm5,qword ptr [eax]  */ \
_LINE3( 0x0F,0x58,0xD5 )                                    /* addps       xmm2,xmm5  */ \
_LINE4( 0x8B,0x44,0x24,0x14 )                               /* mov         eax,dword ptr [esp+14h]  */ \
_LINE3( 0x0F,0x17,0x10 )                                    /* movhps      qword ptr [eax],xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x50,0x08 )                          /* movss       dword ptr [eax+8],xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x48,0x0C )                          /* movss       dword ptr [eax+0xC],xmm1  */ \
_LINE3( 0x0F,0x50,0xC3 )                                    /* movmskps    eax,xmm3  */ \
_LINE3( 0x0F,0x50,0xD0 )                                    /* movmskps    edx,xmm0  */ \
_LINE3( 0xC1,0xE2,0x04 )                                    /* shl         edx,4  */ \
_LINE2( 0x0B,0xC2 )                                         /* or          eax,edx  */ \
_LINE3( 0x83,0xE0,0x77 )                /* and         eax,77h  */ \
_END_ASM

///  вычисление проекции трехмерного вектора на плоскость экрана, команды SSE3
#define VECTORP3DPROJECTSSE3_STD \
_BEGIN_ASM \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x08))               /* mov         eax,dword ptr [esp+8] */ \
_LINE4( 0xF2,0x0F,0xF0,0x20 )                               /* lddqu       xmm4,[eax]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x68,0x10 )                          /* lddqu       xmm5,[eax+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x70,0x20 )                          /* lddqu       xmm6,[eax+20h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x78,0x30 )                          /* lddqu       xmm7,[eax+30h]  */ \
_STR(_DB(0x8B) _DB(0x44) _DB(0x24) _DB(0x04))               /* mov         eax,dword ptr [esp+04h] */ \
_LINE4( 0xF3,0x0F,0x10,0x10 )                               /* movss       xmm2,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x08 )                          /* movss       xmm3,dword ptr [eax+8]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
_LINE3( 0x0F,0x28,0xDA )                                    /* movaps      xmm3,xmm2  */ \
_LINE4( 0x0F,0xC6,0xDB,0xFF )                               /* shufps      xmm3,xmm3,0FFh  */ \
_LINE3( 0x0F,0x57,0xC0 )                                    /* xorps       xmm0,xmm0  */ \
_LINE4( 0xF3,0x0F,0x10,0xCB )                               /* movss       xmm1,xmm3  */ \
_LINE3( 0x0F,0x57,0xFF )                                    /* xorps       xmm7,xmm7  */ \
_LINE3( 0x0F,0x5C,0xC3 )                                    /* subps       xmm0,xmm3  */ \
_LINE4( 0x0F,0xC2,0xDA,0x01 )                               /* cmpltps     xmm3,xmm2  */ \
_LINE4( 0x0F,0xC2,0xC2,0x06 )                               /* cmpnleps    xmm0,xmm2  */ \
_LINE5( 0xF3,0x0F,0xC2,0xF9,0x00 )                          /* cmpeqss     xmm7,xmm1  */ \
_LINE3( 0x0F,0x50,0xC7 )                                    /* movmskps    eax,xmm7  */ \
_LINE2( 0xA8,0x01 )                                         /* test        al,1  */ \
_LINE2( 0x75,0x24 )                                         /* jne         ddd (11B14D0h)  */ \
_LINE5( 0xB8,0x00,0x00,0x80,0x3F )                          /* mov         eax,3F800000h  */ \
_LINE4( 0x66,0x0F,0x6E,0xF8 )                               /* movd        xmm7,eax  */ \
_LINE4( 0xF3,0x0F,0x5E,0xF9 )                               /* divss       xmm7,xmm1  */ \
_LINE5( 0xF3,0x0F,0xC2,0xCF,0x00 )                          /* cmpeqss     xmm1,xmm7  */ \
_LINE3( 0x0F,0x50,0xC1 )                                    /* movmskps    eax,xmm1  */ \
_LINE4( 0xF3,0x0F,0x10,0xCF )                               /* movss       xmm1,xmm7  */ \
_LINE2( 0xA8,0x01 )                                         /* test        al,1  */ \
_LINE2( 0x75,0x07 )                                         /* jne         ddd (11B14D0h)  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xD1 )                                    /* mulps       xmm2,xmm1  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )                               /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x4E )                               /* shufps      xmm2,xmm2,4Eh  */ \
_LINE5( 0xF3,0x0F,0x10,0x60,0x08 )                          /* movss       xmm4,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x20 )                                    /* movhps      xmm4,qword ptr [eax]  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE4( 0x8B,0x44,0x24,0x10 )                               /* mov         eax,dword ptr [esp+10h]  */ \
_LINE5( 0xF3,0x0F,0x10,0x68,0x08 )                          /* movss       xmm5,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x28 )                                    /* movhps      xmm5,qword ptr [eax]  */ \
_LINE3( 0x0F,0x58,0xD5 )                                    /* addps       xmm2,xmm5  */ \
_LINE4( 0x8B,0x44,0x24,0x14 )                               /* mov         eax,dword ptr [esp+14h]  */ \
_LINE3( 0x0F,0x17,0x10 )                                    /* movhps      qword ptr [eax],xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x50,0x08 )                          /* movss       dword ptr [eax+8],xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x48,0x0C )                          /* movss       dword ptr [eax+0xC],xmm1  */ \
_LINE3( 0x0F,0x50,0xC3 )                                    /* movmskps    eax,xmm3  */ \
_LINE3( 0x0F,0x50,0xD0 )                                    /* movmskps    edx,xmm0  */ \
_LINE3( 0xC1,0xE2,0x04 )                                    /* shl         edx,4  */ \
_LINE2( 0x0B,0xC2 )                                         /* or          eax,edx  */ \
_LINE3( 0x83,0xE0,0x77 )                /* and         eax,77h  */ \
_END_ASM

///  вычисление проекции четырехмерного вектора на плоскость экрана, команды SSE3
#define VECTORP4DPROJECTSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x08 )           /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x4C,0x24,0x04 )           /* mov         ecx,dword ptr [esp+4]  */ \
_LINE4( 0xF2,0x0F,0xF0,0x20 )           /* lddqu       xmm4,xmmword ptr [eax]  */ \
_LINE4( 0xF3,0x0F,0x10,0x11 )           /* movss       xmm2,dword ptr [ecx]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x68,0x10 )      /* lddqu       xmm5,xmmword ptr [eax+10h]  */ \
_LINE5( 0xF3,0x0F,0x10,0x49,0x04 )      /* movss       xmm1,dword ptr [ecx+4]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x70,0x20 )      /* lddqu       xmm6,xmmword ptr [eax+20h]  */ \
_LINE5( 0xF3,0x0F,0x10,0x59,0x08 )      /* movss       xmm3,dword ptr [ecx+8]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x78,0x30 )      /* lddqu       xmm7,xmmword ptr [eax+30h]  */ \
_LINE5( 0xF3,0x0F,0x10,0x41,0x0C )      /* movss       xmm0,dword ptr [ecx+0Ch]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )           /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                /* mulps       xmm2,xmm4  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )           /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                /* mulps       xmm1,xmm5  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )           /* shufps      xmm0,xmm0,0  */ \
_LINE3( 0x0F,0x59,0xC7 )                /* mulps       xmm0,xmm7  */ \
_LINE3( 0x0F,0x58,0xD1 )                /* addps       xmm2,xmm1  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )           /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xDE )                /* mulps       xmm3,xmm6  */ \
_LINE3( 0x0F,0x58,0xD3 )                /* addps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x58,0xD7 )                /* addps       xmm2,xmm7  */ \
_LINE3( 0x0F,0x28,0xE2 )                /* movaps      xmm4,xmm2  */ \
_LINE3( 0x0F,0x57,0xC0 )                /* xorps       xmm0,xmm0  */ \
_LINE4( 0x0F,0xC6,0xE4,0xFF )           /* shufps      xmm4,xmm4,0FFh  */ \
_LINE3( 0x0F,0x57,0xFF )                /* xorps       xmm7,xmm7  */ \
_LINE4( 0xF3,0x0F,0x10,0xCC )           /* movss       xmm1,xmm4  */ \
_LINE3( 0x0F,0x5C,0xC4 )                /* subps       xmm0,xmm4  */ \
_LINE4( 0x0F,0xC2,0xE2,0x01 )           /* cmpltps     xmm4,xmm2  */ \
_LINE4( 0x0F,0xC2,0xC2,0x06 )           /* cmpnleps    xmm0,xmm2  */ \
_LINE5( 0xF3,0x0F,0xC2,0xF9,0x00 )      /* cmpeqss     xmm7,xmm1  */ \
_LINE3( 0x0F,0x50,0xC7 )                /* movmskps    eax,xmm7  */ \
_LINE2( 0xA8,0x01 )                     /* test        al,1  */ \
_LINE2( 0x75,0x24 )                     /* jne         ddd (11B14D0h)  */ \
_LINE5( 0xB8,0x00,0x00,0x80,0x3F )      /* mov         eax,3F800000h  */ \
_LINE4( 0x66,0x0F,0x6E,0xF8 )           /* movd        xmm7,eax  */ \
_LINE4( 0xF3,0x0F,0x5E,0xF9 )           /* divss       xmm7,xmm1  */ \
_LINE5( 0xF3,0x0F,0xC2,0xCF,0x00 )      /* cmpeqss     xmm1,xmm7  */ \
_LINE3( 0x0F,0x50,0xC1 )                /* movmskps    eax,xmm1  */ \
_LINE4( 0xF3,0x0F,0x10,0xCF )           /* movss       xmm1,xmm7  */ \
_LINE2( 0xA8,0x01 )                     /* test        al,1  */ \
_LINE2( 0x75,0x07 )                     /* jne         ddd (11B14D0h)  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )           /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xD1 )                /* mulps       xmm2,xmm1  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )           /* mov         eax,dword ptr [esp+0Ch]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x4E )           /* shufps      xmm2,xmm2,4Eh  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x08 )      /* movss       xmm3,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x18 )                /* movhps      xmm3,qword ptr [eax]  */ \
_LINE4( 0x8B,0x44,0x24,0x10 )           /* mov         eax,dword ptr [esp+10h]  */ \
_LINE5( 0xF3,0x0F,0x10,0x68,0x08 )      /* movss       xmm5,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x28 )                /* movhps      xmm5,qword ptr [eax]  */ \
_LINE3( 0x0F,0x59,0xD3 )                /* mulps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x58,0xD5 )                /* addps       xmm2,xmm5  */ \
_LINE4( 0x8B,0x44,0x24,0x14 )           /* mov         eax,dword ptr [esp+14h]  */ \
_LINE3( 0x0F,0x17,0x10 )                /* movhps      qword ptr [eax],xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x50,0x08 )      /* movss       dword ptr [eax+8],xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x48,0x0C )      /* movss       dword ptr [eax+0xC],xmm1  */ \
_LINE3( 0x0F,0x50,0xC4 )                /* movmskps    eax,xmm4  */ \
_LINE3( 0x0F,0x50,0xD0 )                /* movmskps    edx,xmm0  */ \
_LINE3( 0xC1,0xE2,0x04 )                /* shl         edx,4  */ \
_LINE2( 0x0B,0xC2 )                     /* or          eax,edx  */ \
_LINE3( 0x83,0xE0,0x77 )                /* and         eax,77h  */ \
_END_ASM

/// вычисление проекции четырехмерного вектора двойной точности на плоскость экрана, команды SSE4
#define VECTORP4DDPROJECTSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x08 )           /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x4C,0x24,0x04 )           /* mov         ecx,dword ptr [esp+4]  */ \
_LINE4( 0xC5,0xFD,0x10,0x20 )           /* vmovupd     ymm4,ymmword ptr [eax]  */ \
_LINE5( 0xC4,0xE2,0x7D,0x19,0x11 )      /* vbroadcastsd ymm2,qword ptr [ecx]  */ \
_LINE5( 0xC5,0xFD,0x10,0x68,0x20 )      /* vmovupd     ymm5,ymmword ptr [eax+20h]  */ \
_LINE6( 0xC4,0xE2,0x7D,0x19,0x49,0x08 ) /* vbroadcastsd ymm1,qword ptr [ecx+08h]  */ \
_LINE5( 0xC5,0xFD,0x10,0x70,0x40 )      /* vmovupd     ymm6,ymmword ptr [eax+40h]  */ \
_LINE6( 0xC4,0xE2,0x7D,0x19,0x59,0x10 ) /* vbroadcastsd ymm3,qword ptr [ecx+10h]  */ \
_LINE5( 0xC5,0xFD,0x10,0x78,0x60 )      /* vmovupd     ymm7,ymmword ptr [eax+60h]  */ \
_LINE6( 0xC4,0xE2,0x7D,0x19,0x41,0x18 ) /* vbroadcastsd ymm0,qword ptr [ecx+18h]  */ \
_LINE4( 0xC5,0xCD,0x59,0xDB )           /* vmulpd      ymm3,ymm6,ymm3  */ \
_LINE4( 0xC5,0xDD,0x59,0xD2 )           /* vmulpd      ymm2,ymm4,ymm2  */ \
_LINE4( 0xC5,0xD5,0x59,0xC9 )           /* vmulpd      ymm1,ymm5,ymm1  */ \
_LINE4( 0xC5,0xC5,0x59,0xC0 )           /* vmulpd      ymm0,ymm7,ymm0  */ \
_LINE4( 0xC5,0xE5,0x58,0xD2 )           /* vaddpd      ymm2,ymm3,ymm2  */ \
_LINE4( 0xC5,0xFD,0x58,0xC9 )           /* vaddpd      ymm1,ymm0,ymm1  */ \
_LINE4( 0xC5,0xED,0x58,0xD1 )           /* vaddpd      ymm2,ymm2,ymm1  */ \
ASM( VEXTRACTF128 xmm3,ymm2,1 ) \
ASM( movhpd [esp-0Ch],xmm3 ) \
_LINE4( 0xC5,0xC5,0x57,0xFF )           /* vxorpd      ymm7,ymm7,ymm7  */ \
_LINE7( 0xC4,0xE2,0x7D,0x19,0x64,0x24,0xF4 ) /* vbroadcastsd ymm4,qword ptr [esp-0Ch]  */ \
_LINE4( 0xC5,0xC5,0x5C,0xC4 )          /* vsubpd      ymm0,ymm7,ymm4  */ \
_LINE5( 0xC5,0xDD,0xC2,0xCA,0x01 )     /* vcmpltpd    ymm1,ymm4,ymm2  */ \
_LINE5( 0xC5,0xFD,0xC2,0xC2,0x06 )     /* vcmpnlepd   ymm0,ymm0,ymm2  */ \
ASM( vcmpeqsd    xmm7,xmm7,xmm4 )     /* vcmpeqpd    ymm7,ymm7,ymm4  */ \
ASM( vmovmskpd eax,ymm7 ) \
_LINE2( 0xA8,0x01 )                    /* test        al,1  */ \
_LINE2( 0x75,0x24 )                    /* jne         ddd (11B14D0h)  */ \
_LINE5( 0xB8,0x00,0x00,0x80,0x3F )     /* mov         eax,3F800000h  */ \
_LINE4( 0x66,0x0F,0x6E,0xF8 )          /* movd        xmm7,eax  */ \
ASM( CVTPS2PD xmm7,xmm7 ) \
ASM( vdivsd xmm4,xmm7,xmm4 ) \
ASM( vcmpeqsd    xmm7,xmm7,xmm4 )     /* vcmpeqpd    ymm7,ymm7,ymm4  */ \
ASM( vmovmskpd eax,ymm7 ) \
_LINE6( 0xF2,0x0F,0x11,0x64,0x24,0xF4 ) /* movsd       mmword ptr [esp-0Ch],xmm4  */ \
_LINE2( 0xA8,0x01 )                     /* test        al,1  */ \
_LINE2( 0x75,0x07 )                     /* jne         ddd (11B14D0h)  */ \
_LINE7( 0xC4,0xE2,0x7D,0x19,0x64,0x24,0xF4 ) /* vbroadcastsd ymm4,qword ptr [esp-0Ch]  */ \
_LINE4( 0xC5,0xDD,0x59,0xD2 )           /* vmulpd      ymm2,ymm4,ymm2  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )           /* mov         eax,dword ptr [esp+0Ch]  */ \
ASM( vblendpd ymm3,ymm3,[eax],0x7 ) \
_LINE4( 0x8B,0x44,0x24,0x10 )           /* mov         eax,dword ptr [esp+10h]  */ \
ASM( vblendpd ymm5,ymm5,[eax],0x7 ) \
_LINE4( 0xC5,0xE5,0x59,0xD2 )           /* vmulpd      ymm2,ymm3,ymm2  */ \
_LINE4( 0xC5,0xED,0x58,0xD5 )           /* vaddpd      ymm2,ymm2,ymm5  */ \
_LINE4( 0x8B,0x44,0x24,0x14 )           /* mov         eax,dword ptr [esp+14h]  */ \
ASM( VEXTRACTF128 xmm3,ymm2,1 ) \
ASM( movupd [eax],xmm2 ) \
ASM( movsd [eax+0x10],xmm3 ) \
ASM( movsd [eax+0x18],xmm4 ) \
ASM( vmovmskpd eax,ymm1 ) \
ASM( vmovmskpd edx,ymm0 ) \
_LINE3( 0xC1,0xE2,0x04 )                /* shl         edx,4  */ \
_LINE2( 0x0B,0xC2 )                     /* or          eax,edx  */ \
_LINE3( 0x83,0xE0,0x77 )                /* and         eax,77h  */ \
_END_ASM

/// вычисление проекции четырехмерного вектора двойной точности на плоскость экрана, команды AVX
#define VECTORP4DDPROJECTAVX_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x08 )           /* mov         eax,dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x4C,0x24,0x04 )           /* mov         ecx,dword ptr [esp+4]  */ \
_LINE4( 0xC5,0xFD,0x10,0x20 )           /* vmovupd     ymm4,ymmword ptr [eax]  */ \
_LINE5( 0xC4,0xE2,0x7D,0x19,0x11 )      /* vbroadcastsd ymm2,qword ptr [ecx]  */ \
_LINE5( 0xC5,0xFD,0x10,0x68,0x20 )      /* vmovupd     ymm5,ymmword ptr [eax+20h]  */ \
_LINE6( 0xC4,0xE2,0x7D,0x19,0x49,0x08 ) /* vbroadcastsd ymm1,qword ptr [ecx+08h]  */ \
_LINE5( 0xC5,0xFD,0x10,0x70,0x40 )      /* vmovupd     ymm6,ymmword ptr [eax+40h]  */ \
_LINE6( 0xC4,0xE2,0x7D,0x19,0x59,0x10 ) /* vbroadcastsd ymm3,qword ptr [ecx+10h]  */ \
_LINE5( 0xC5,0xFD,0x10,0x78,0x60 )      /* vmovupd     ymm7,ymmword ptr [eax+60h]  */ \
_LINE6( 0xC4,0xE2,0x7D,0x19,0x41,0x18 ) /* vbroadcastsd ymm0,qword ptr [ecx+18h]  */ \
_LINE4( 0xC5,0xCD,0x59,0xDB )           /* vmulpd      ymm3,ymm6,ymm3  */ \
_LINE4( 0xC5,0xDD,0x59,0xD2 )           /* vmulpd      ymm2,ymm4,ymm2  */ \
_LINE4( 0xC5,0xD5,0x59,0xC9 )           /* vmulpd      ymm1,ymm5,ymm1  */ \
_LINE4( 0xC5,0xC5,0x59,0xC0 )           /* vmulpd      ymm0,ymm7,ymm0  */ \
_LINE4( 0xC5,0xE5,0x58,0xD2 )           /* vaddpd      ymm2,ymm3,ymm2  */ \
_LINE4( 0xC5,0xFD,0x58,0xC9 )           /* vaddpd      ymm1,ymm0,ymm1  */ \
_LINE4( 0xC5,0xED,0x58,0xD1 )           /* vaddpd      ymm2,ymm2,ymm1  */ \
_LINE6( 0xC4,0xE3,0x7D,0x19,0xD3,0x01 ) /* vextractf128 xmm3, ymm2, 1 */ \
_LINE6( 0x66,0x0F,0x17,0x5C,0x24,0xF4 ) /* movhpd      qword ptr[esp - 0Ch], xmm3  */ \
_LINE4( 0xC5,0xC5,0x57,0xFF )           /* vxorpd      ymm7,ymm7,ymm7  */ \
_LINE7( 0xC4,0xE2,0x7D,0x19,0x64,0x24,0xF4 ) /* vbroadcastsd ymm4,qword ptr [esp-0Ch]  */ \
_LINE4( 0xC5,0xC5,0x5C,0xC4 )          /* vsubpd      ymm0,ymm7,ymm4  */ \
_LINE5( 0xC5,0xDD,0xC2,0xCA,0x01 )     /* vcmpltpd    ymm1,ymm4,ymm2  */ \
_LINE5( 0xC5,0xFD,0xC2,0xC2,0x06 )     /* vcmpnlepd   ymm0,ymm0,ymm2  */ \
ASM( vcmpeqsd    xmm7,xmm7,xmm4 )     /* vcmpeqpd    ymm7,ymm7,ymm4  */ \
ASM( vmovmskpd eax,ymm7 ) \
_LINE2( 0xA8,0x01 )                    /* test        al,1  */ \
_LINE2( 0x75,0x24 )                    /* jne         ddd (11B14D0h)  */ \
_LINE5( 0xB8,0x00,0x00,0x80,0x3F )     /* mov         eax,3F800000h  */ \
_LINE4( 0x66,0x0F,0x6E,0xF8 )          /* movd        xmm7,eax  */ \
ASM( CVTPS2PD xmm7,xmm7 ) \
ASM( vdivsd xmm4,xmm7,xmm4 ) \
ASM( vcmpeqsd    xmm7,xmm7,xmm4 )     /* vcmpeqpd    ymm7,ymm7,ymm4  */ \
ASM( vmovmskpd eax,ymm7 ) \
_LINE6( 0xF2,0x0F,0x11,0x64,0x24,0xF4 ) /* movsd       mmword ptr [esp-0Ch],xmm4  */ \
_LINE2( 0xA8,0x01 )                     /* test        al,1  */ \
_LINE2( 0x75,0x07 )                     /* jne         ddd (11B14D0h)  */ \
_LINE7( 0xC4,0xE2,0x7D,0x19,0x64,0x24,0xF4 ) /* vbroadcastsd ymm4,qword ptr [esp-0Ch]  */ \
_LINE4( 0xC5,0xDD,0x59,0xD2 )           /* vmulpd      ymm2,ymm4,ymm2  */ \
_LINE4( 0x8B,0x44,0x24,0x0C )           /* mov         eax,dword ptr [esp+0Ch]  */ \
ASM( vblendpd ymm3,ymm3,[eax],0x7 ) \
_LINE4( 0x8B,0x44,0x24,0x10 )           /* mov         eax,dword ptr [esp+10h]  */ \
ASM( vblendpd ymm5,ymm5,[eax],0x7 ) \
_LINE4( 0xC5,0xE5,0x59,0xD2 )           /* vmulpd      ymm2,ymm3,ymm2  */ \
_LINE4( 0xC5,0xED,0x58,0xD5 )           /* vaddpd      ymm2,ymm2,ymm5  */ \
_LINE4( 0x8B,0x44,0x24,0x14 )           /* mov         eax,dword ptr [esp+14h]  */ \
_LINE6( 0xC4,0xE3,0x7D,0x19,0xD3,0x01 ) /* vextractf128 xmm3, ymm2, 1 */ \
ASM( movupd [eax],xmm2 ) \
ASM( movsd [eax+0x10],xmm3 ) \
ASM( movsd [eax+0x18],xmm4 ) \
ASM( vmovmskpd eax,ymm1 ) \
ASM( vmovmskpd edx,ymm0 ) \
_LINE3( 0xC1,0xE2,0x04 )                /* shl         edx,4  */ \
_LINE2( 0x0B,0xC2 )                     /* or          eax,edx  */ \
_LINE3( 0x83,0xE0,0x77 )                /* and         eax,77h  */ \
_END_ASM


