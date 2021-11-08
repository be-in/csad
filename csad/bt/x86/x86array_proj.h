//=============================================================================
///**
// *  @file x86array_proj.h
// *
// *  $Id: x86array_proj.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float project, MS Visual C++ 2003-2008
// *
// *  @author Pant_eleymonov Alek_sandr Kons_tantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef X86ARRAY_PROJ_H_
#define X86ARRAY_PROJ_H_

//**************************** PROJECT STDCALL *********************************
// project vectors eax=[esp+4]-v void *, [esp+8]-matrix void *  [esp+12]-viewScale void *  [esp+16]-viewOffset void *  [esp+20]-v rez void *
// [esp+24] - _stepa unsigned int  [esp+28] - _stepe unsigned int  [esp+32] - _flagoff unsigned int  [esp+36] - _count unsigned int
//  additional eax - return clip flag

///  вычисление проекции двухмерного вектора на плоскость экрана, команды SSE3
#define ARRAYP2DPROJECTSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8] */ \
_LINE4( 0xF2,0x0F,0xF0,0x20 )                               /* lddqu       xmm4,[eax]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x68,0x10 )                          /* lddqu       xmm5,[eax+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x78,0x30 )                          /* lddqu       xmm7,[eax+30h]  */ \
_LINE4( 0x89,0x7C,0x24,0x08 )                               /* mov         dword ptr [esp+8],edi  */ \
_LINE4( 0x8B,0x7C,0x24,0x04 )                               /* mov         edi,dword ptr [esp+4]  */ \
_LINE4( 0x89,0x74,0x24,0x04 )                               /* mov         dword ptr [esp+4],esi  */ \
_LINE4( 0x8B,0x74,0x24,0x14 )                               /* mov         esi,dword ptr [esp+14h]  */ \
_LINE4( 0x89,0x5C,0x24,0x14 )                               /* mov         dword ptr [esp+14h],ebx  */ \
_LINE4( 0x8B,0x5C,0x24,0x0C )                               /* mov         ebx,dword ptr [esp+0Ch]  */ \
_LINE4( 0x8B,0x4C,0x24,0x24 )                               /* mov         ecx,dword ptr [esp+24h]  */ \
_LINE4( 0xF3,0x0F,0x10,0x17 )                               /* movss       xmm2,dword ptr [edi]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x4F,0x04 )                          /* movss       xmm1,dword ptr [edi+4]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
_LINE3( 0x0F,0x28,0xCA )                                    /* movaps      xmm1,xmm2  */ \
_LINE4( 0x0F,0xC6,0xC9,0xFF )                               /* shufps      xmm1,xmm1,0FFh  */ \
_LINE4( 0xF3,0x0F,0x10,0xD9 )                               /* movss       xmm3,xmm1  */ \
_LINE3( 0x0F,0x57,0xC0 )                                    /* xorps       xmm0,xmm0  */ \
_LINE3( 0x0F,0x5C,0xC1 )                                    /* subps       xmm0,xmm1  */ \
_LINE4( 0x0F,0xC2,0xCA,0x01 )                               /* cmpltps     xmm1,xmm2  */ \
_LINE4( 0x0F,0xC2,0xC2,0x06 )                               /* cmpnleps    xmm0,xmm2  */ \
_LINE3( 0x0F,0x50,0xC1 )                                    /* movmskps    eax,xmm1  */ \
_LINE3( 0x0F,0x50,0xD0 )                                    /* movmskps    edx,xmm0  */ \
_LINE3( 0xC1,0xE2,0x04 )                                    /* shl         edx,4  */ \
_LINE2( 0x0B,0xC2 )                                         /* or          eax,edx  */ \
_LINE3( 0x83,0xE0,0x77 )                                    /* and         eax,77h  */ \
_LINE4( 0x8B,0x54,0x24,0x20 )                               /* mov         edx,dword ptr [esp+20h]  */ \
_LINE3( 0x89,0x04,0x16 )                                    /* mov         dword ptr [esi+edx],eax  */ \
_LINE3( 0x0F,0x57,0xC0 )                                    /* xorps       xmm0,xmm0  */ \
_LINE5( 0xF3,0x0F,0xC2,0xC3,0x00 )                          /* cmpeqss     xmm0,xmm3  */ \
_LINE3( 0x0F,0x50,0xC0 )                                    /* movmskps    eax,xmm0  */ \
_LINE2( 0xA8,0x01 )                                         /* test        al,1  */ \
_LINE2( 0x75,0x24 )                                         /* jne         ddd (11B14D0h)  */ \
_LINE5( 0xB8,0x00,0x00,0x80,0x3F )                          /* mov         eax,3F800000h  */ \
_LINE4( 0x66,0x0F,0x6E,0xC8 )                               /* movd        xmm1,eax  */ \
_LINE4( 0xF3,0x0F,0x5E,0xCB )                               /* divss       xmm1,xmm3  */ \
_LINE5( 0xF3,0x0F,0xC2,0xD9,0x00 )                          /* cmpeqss     xmm3,xmm1  */ \
_LINE3( 0x0F,0x50,0xC3 )                                    /* movmskps    eax,xmm3  */ \
_LINE4( 0xF3,0x0F,0x10,0xD9 )                               /* movss       xmm3,xmm1  */ \
_LINE2( 0xA8,0x01 )                                         /* test        al,1  */ \
_LINE2( 0x75,0x07 )                                         /* jne         ddd (11B14D0h)  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xD3 )                                    /* mulps       xmm2,xmm3  */ \
_LINE4( 0x0F,0xC6,0xD2,0x4E )                               /* shufps      xmm2,xmm2,4Eh  */ \
_LINE5( 0xF3,0x0F,0x10,0x43,0x08 )                          /* movss       xmm0,dword ptr [ebx+8]  */ \
_LINE3( 0x0F,0x16,0x03 )                                    /* movhps      xmm0,qword ptr [ebx]  */ \
_LINE3( 0x0F,0x59,0xD0 )                                    /* mulps       xmm2,xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x5E,0x0C )                          /* movss       dword ptr [esi+0xC],xmm3  */ \
_LINE4( 0x8B,0x44,0x24,0x10 )                               /* mov         eax,dword ptr [esp+10h]  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x08 )                          /* movss       xmm1,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x08 )                                    /* movhps      xmm1,qword ptr [eax]  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x17,0x16 )                                    /* movhps      qword ptr [esi],xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x56,0x08 )                          /* movss       dword ptr [esi+8],xmm2  */ \
_LINE4( 0x03,0x7C,0x24,0x18 )                               /* add         edi,dword ptr [esp+18h]  */ \
_LINE4( 0x03,0x74,0x24,0x1C )                               /* add         esi,dword ptr [esp+1Ch]  */ \
_LINE1( 0x49 )                                              /* dec         ecx  */ \
_LINE2( 0xE3,0x05 )                                         /* jecxz       end (1D119Ch)  */ \
_LINE5( 0xE9,0x47,0xFF,0xFF,0xFF )                          /* jmp         begin (1D10CEh)*/ \
_LINE4( 0x8B,0x7C,0x24,0x08 )                               /* mov         edi,dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x74,0x24,0x04 )                               /* mov         esi,dword ptr [esp+4h]  */ \
_LINE4( 0x8B,0x5C,0x24,0x14 )                               /* mov         ebx,dword ptr [esp+14h]  */ \
_END_ASM

///  вычисление проекции трехмерного вектора на плоскость экрана, команды SSE3
#define ARRAYP3DPROJECTSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8] */ \
_LINE4( 0xF2,0x0F,0xF0,0x20 )                               /* lddqu       xmm4,[eax]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x68,0x10 )                          /* lddqu       xmm5,[eax+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x70,0x20 )                          /* lddqu       xmm6,[eax+20h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x78,0x30 )                          /* lddqu       xmm7,[eax+30h]  */ \
_LINE4( 0x89,0x7C,0x24,0x08 )                               /* mov         dword ptr [esp+8],edi  */ \
_LINE4( 0x8B,0x7C,0x24,0x04 )                               /* mov         edi,dword ptr [esp+4]  */ \
_LINE4( 0x89,0x74,0x24,0x04 )                               /* mov         dword ptr [esp+4],esi  */ \
_LINE4( 0x8B,0x74,0x24,0x14 )                               /* mov         esi,dword ptr [esp+14h]  */ \
_LINE4( 0x89,0x5C,0x24,0x14 )                               /* mov         dword ptr [esp+14h],ebx  */ \
_LINE4( 0x8B,0x5C,0x24,0x0C )                               /* mov         ebx,dword ptr [esp+0Ch]  */ \
_LINE4( 0x8B,0x4C,0x24,0x24 )                               /* mov         ecx,dword ptr [esp+24h]  */ \
_LINE4( 0xF3,0x0F,0x10,0x17 )                               /* movss       xmm2,dword ptr [edi]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x4F,0x04 )                          /* movss       xmm1,dword ptr [edi+4]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x5F,0x08 )                          /* movss       xmm3,dword ptr [edi+8]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
_LINE3( 0x0F,0x28,0xCA )                                    /* movaps      xmm1,xmm2  */ \
_LINE4( 0x0F,0xC6,0xC9,0xFF )                               /* shufps      xmm1,xmm1,0FFh  */ \
_LINE4( 0xF3,0x0F,0x10,0xD9 )                               /* movss       xmm3,xmm1  */ \
_LINE3( 0x0F,0x57,0xC0 )                                    /* xorps       xmm0,xmm0  */ \
_LINE3( 0x0F,0x5C,0xC1 )                                    /* subps       xmm0,xmm1  */ \
_LINE4( 0x0F,0xC2,0xCA,0x01 )                               /* cmpltps     xmm1,xmm2  */ \
_LINE4( 0x0F,0xC2,0xC2,0x06 )                               /* cmpnleps    xmm0,xmm2  */ \
_LINE3( 0x0F,0x50,0xC1 )                                    /* movmskps    eax,xmm1  */ \
_LINE3( 0x0F,0x50,0xD0 )                                    /* movmskps    edx,xmm0  */ \
_LINE3( 0xC1,0xE2,0x04 )                                    /* shl         edx,4  */ \
_LINE2( 0x0B,0xC2 )                                         /* or          eax,edx  */ \
_LINE3( 0x83,0xE0,0x77 )                                    /* and         eax,77h  */ \
_LINE4( 0x8B,0x54,0x24,0x20 )                               /* mov         edx,dword ptr [esp+20h]  */ \
_LINE3( 0x89,0x04,0x16 )                                    /* mov         dword ptr [esi+edx],eax  */ \
_LINE3( 0x0F,0x57,0xC0 )                                    /* xorps       xmm0,xmm0  */ \
_LINE5( 0xF3,0x0F,0xC2,0xC3,0x00 )                          /* cmpeqss     xmm0,xmm3  */ \
_LINE3( 0x0F,0x50,0xC0 )                                    /* movmskps    eax,xmm0  */ \
_LINE2( 0xA8,0x01 )                                         /* test        al,1  */ \
_LINE2( 0x75,0x24 )                                         /* jne         ddd (11B14D0h)  */ \
_LINE5( 0xB8,0x00,0x00,0x80,0x3F )                          /* mov         eax,3F800000h  */ \
_LINE4( 0x66,0x0F,0x6E,0xC8 )                               /* movd        xmm1,eax  */ \
_LINE4( 0xF3,0x0F,0x5E,0xCB )                               /* divss       xmm1,xmm3  */ \
_LINE5( 0xF3,0x0F,0xC2,0xD9,0x00 )                          /* cmpeqss     xmm3,xmm1  */ \
_LINE3( 0x0F,0x50,0xC3 )                                    /* movmskps    eax,xmm3  */ \
_LINE4( 0xF3,0x0F,0x10,0xD9 )                               /* movss       xmm3,xmm1  */ \
_LINE2( 0xA8,0x01 )                                         /* test        al,1  */ \
_LINE2( 0x75,0x07 )                                         /* jne         ddd (11B14D0h)  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xD3 )                                    /* mulps       xmm2,xmm3  */ \
_LINE4( 0x0F,0xC6,0xD2,0x4E )                               /* shufps      xmm2,xmm2,4Eh  */ \
_LINE5( 0xF3,0x0F,0x10,0x43,0x08 )                          /* movss       xmm0,dword ptr [ebx+8]  */ \
_LINE3( 0x0F,0x16,0x03 )                                    /* movhps      xmm0,qword ptr [ebx]  */ \
_LINE3( 0x0F,0x59,0xD0 )                                    /* mulps       xmm2,xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x5E,0x0C )                          /* movss       dword ptr [esi+0xC],xmm3  */ \
_LINE4( 0x8B,0x44,0x24,0x10 )                               /* mov         eax,dword ptr [esp+10h]  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x08 )                          /* movss       xmm1,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x08 )                                    /* movhps      xmm1,qword ptr [eax]  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x17,0x16 )                                    /* movhps      qword ptr [esi],xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x56,0x08 )                          /* movss       dword ptr [esi+8],xmm2  */ \
_LINE4( 0x03,0x7C,0x24,0x18 )                               /* add         edi,dword ptr [esp+18h]  */ \
_LINE4( 0x03,0x74,0x24,0x1C )                               /* add         esi,dword ptr [esp+1Ch]  */ \
_LINE1( 0x49 )                                              /* dec         ecx  */ \
_LINE2( 0xE3,0x05 )                                         /* jecxz       end (1D119Ch)  */ \
_LINE5( 0xE9,0x38,0xFF,0xFF,0xFF )                          /* jmp         begin (1D10CEh)*/ \
_LINE4( 0x8B,0x7C,0x24,0x08 )                               /* mov         edi,dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x74,0x24,0x04 )                               /* mov         esi,dword ptr [esp+4h]  */ \
_LINE4( 0x8B,0x5C,0x24,0x14 )                               /* mov         ebx,dword ptr [esp+14h]  */ \
_END_ASM

///  вычисление проекции четырехмерного вектора на плоскость экрана, команды SSE3
#define ARRAYP4DPROJECTSSE3_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x08 )                               /* mov         eax,dword ptr [esp+8] */ \
_LINE4( 0xF2,0x0F,0xF0,0x20 )                               /* lddqu       xmm4,[eax]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x68,0x10 )                          /* lddqu       xmm5,[eax+10h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x70,0x20 )                          /* lddqu       xmm6,[eax+20h]  */ \
_LINE5( 0xF2,0x0F,0xF0,0x78,0x30 )                          /* lddqu       xmm7,[eax+30h]  */ \
_LINE4( 0x89,0x7C,0x24,0x08 )                               /* mov         dword ptr [esp+8],edi  */ \
_LINE4( 0x8B,0x7C,0x24,0x04 )                               /* mov         edi,dword ptr [esp+4]  */ \
_LINE4( 0x89,0x74,0x24,0x04 )                               /* mov         dword ptr [esp+4],esi  */ \
_LINE4( 0x8B,0x74,0x24,0x14 )                               /* mov         esi,dword ptr [esp+14h]  */ \
_LINE4( 0x89,0x5C,0x24,0x14 )                               /* mov         dword ptr [esp+14h],ebx  */ \
_LINE4( 0x8B,0x5C,0x24,0x0C )                               /* mov         ebx,dword ptr [esp+0Ch]  */ \
_LINE4( 0x8B,0x4C,0x24,0x24 )                               /* mov         ecx,dword ptr [esp+24h]  */ \
_LINE4( 0xF3,0x0F,0x10,0x17 )                               /* movss       xmm2,dword ptr [edi]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x4F,0x04 )                          /* movss       xmm1,dword ptr [edi+4]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x5F,0x08 )                          /* movss       xmm3,dword ptr [edi+8]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE5( 0xF3,0x0F,0x10,0x47,0x0C )                          /* movss       xmm0,dword ptr [edi+Ch]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )                               /* shufps      xmm0,xmm0,0  */ \
_LINE3( 0x0F,0x59,0xC7 )                                    /* mulps       xmm0,xmm7  */ \
_LINE3( 0x0F,0x58,0xD0 )                                    /* addps       xmm2,xmm0  */ \
_LINE3( 0x0F,0x28,0xCA )                                    /* movaps      xmm1,xmm2  */ \
_LINE4( 0x0F,0xC6,0xC9,0xFF )                               /* shufps      xmm1,xmm1,0FFh  */ \
_LINE4( 0xF3,0x0F,0x10,0xD9 )                               /* movss       xmm3,xmm1  */ \
_LINE3( 0x0F,0x57,0xC0 )                                    /* xorps       xmm0,xmm0  */ \
_LINE3( 0x0F,0x5C,0xC1 )                                    /* subps       xmm0,xmm1  */ \
_LINE4( 0x0F,0xC2,0xCA,0x01 )                               /* cmpltps     xmm1,xmm2  */ \
_LINE4( 0x0F,0xC2,0xC2,0x06 )                               /* cmpnleps    xmm0,xmm2  */ \
_LINE3( 0x0F,0x50,0xC1 )                                    /* movmskps    eax,xmm1  */ \
_LINE3( 0x0F,0x50,0xD0 )                                    /* movmskps    edx,xmm0  */ \
_LINE3( 0xC1,0xE2,0x04 )                                    /* shl         edx,4  */ \
_LINE2( 0x0B,0xC2 )                                         /* or          eax,edx  */ \
_LINE3( 0x83,0xE0,0x77 )                                    /* and         eax,77h  */ \
_LINE4( 0x8B,0x54,0x24,0x20 )                               /* mov         edx,dword ptr [esp+20h]  */ \
_LINE3( 0x89,0x04,0x16 )                                    /* mov         dword ptr [esi+edx],eax  */ \
_LINE3( 0x0F,0x57,0xC0 )                                    /* xorps       xmm0,xmm0  */ \
_LINE5( 0xF3,0x0F,0xC2,0xC3,0x00 )                          /* cmpeqss     xmm0,xmm3  */ \
_LINE3( 0x0F,0x50,0xC0 )                                    /* movmskps    eax,xmm0  */ \
_LINE2( 0xA8,0x01 )                                         /* test        al,1  */ \
_LINE2( 0x75,0x24 )                                         /* jne         ddd (11B14D0h)  */ \
_LINE5( 0xB8,0x00,0x00,0x80,0x3F )                          /* mov         eax,3F800000h  */ \
_LINE4( 0x66,0x0F,0x6E,0xC8 )                               /* movd        xmm1,eax  */ \
_LINE4( 0xF3,0x0F,0x5E,0xCB )                               /* divss       xmm1,xmm3  */ \
_LINE5( 0xF3,0x0F,0xC2,0xD9,0x00 )                          /* cmpeqss     xmm3,xmm1  */ \
_LINE3( 0x0F,0x50,0xC3 )                                    /* movmskps    eax,xmm3  */ \
_LINE4( 0xF3,0x0F,0x10,0xD9 )                               /* movss       xmm3,xmm1  */ \
_LINE2( 0xA8,0x01 )                                         /* test        al,1  */ \
_LINE2( 0x75,0x07 )                                         /* jne         ddd (11B14D0h)  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xD3 )                                    /* mulps       xmm2,xmm3  */ \
_LINE4( 0x0F,0xC6,0xD2,0x4E )                               /* shufps      xmm2,xmm2,4Eh  */ \
_LINE5( 0xF3,0x0F,0x10,0x43,0x08 )                          /* movss       xmm0,dword ptr [ebx+8]  */ \
_LINE3( 0x0F,0x16,0x03 )                                    /* movhps      xmm0,qword ptr [ebx]  */ \
_LINE3( 0x0F,0x59,0xD0 )                                    /* mulps       xmm2,xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x5E,0x0C )                          /* movss       dword ptr [esi+0xC],xmm3  */ \
_LINE4( 0x8B,0x44,0x24,0x10 )                               /* mov         eax,dword ptr [esp+10h]  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x08 )                          /* movss       xmm1,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x08 )                                    /* movhps      xmm1,qword ptr [eax]  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x17,0x16 )                                    /* movhps      qword ptr [esi],xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x56,0x08 )                          /* movss       dword ptr [esi+8],xmm2  */ \
_LINE4( 0x03,0x7C,0x24,0x18 )                               /* add         edi,dword ptr [esp+18h]  */ \
_LINE4( 0x03,0x74,0x24,0x1C )                               /* add         esi,dword ptr [esp+1Ch]  */ \
_LINE1( 0x49 )                                              /* dec         ecx  */ \
_LINE2( 0xE3,0x05 )                                         /* jecxz       end (1D119Ch)  */ \
_LINE5( 0xE9,0x2C,0xFF,0xFF,0xFF )                          /* jmp         begin (1D10CEh)*/ \
_LINE4( 0x8B,0x7C,0x24,0x08 )                               /* mov         edi,dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x74,0x24,0x04 )                               /* mov         esi,dword ptr [esp+4h]  */ \
_LINE4( 0x8B,0x5C,0x24,0x14 )                               /* mov         ebx,dword ptr [esp+14h]  */ \
_END_ASM

#endif /* X86ARRAY_PROJ_H_ */
