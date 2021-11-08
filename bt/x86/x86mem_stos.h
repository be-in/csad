//=============================================================================
///**
// *  @file   mem_stos.h
// *
// *  $Id: mem_stos.h 16.10.2011  $
// *
// *  @brief generator 3, assembler memory operations, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_MEM_STOS_H_
#define GEN3_MEM_STOS_H_

//**************************** STOSMEM REGISTER FASTCALL *********************************
// vector cross product edi=[esp+4]-a void * ecx=[esp+8]-b int eax=[esp+12]-c int

/// Заполнение памяти беззнаковым словом.
/// @brief for CPUTYPE1
#define STOSSMEMCPU_STD \
_BEGIN_ASM \
_LINE1( 0x57 )                                              /* push        edi */ \
_LINE4( 0x8B,0x7C,0x24,0x08 )                               /* mov         edi,dword ptr [esp+8]  */ \
_LINE5( 0x66,0x8B,0x44,0x24,0x10 )                          /* mov         ax,word ptr [esp+10h] */ \
_LINE3( 0x66,0x8B,0xC8 )                                    /* mov         cx,ax */ \
_LINE3( 0xC1,0xE0,0x10 )                                    /* shl         eax,10h */ \
_LINE3( 0x66,0x8B,0xC1 )                                    /* mov         ax,cx */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE6( 0xF7,0xC1,0x01,0x00,0x00,0x00 )                     /* test        ecx,1 */ \
_LINE2( 0x74,0x06 )                                         /* je          eee (0FB1235h) */ \
_LINE3( 0x66,0x89,0x07 )                                    /* mov         word ptr [edi],ax */ \
_LINE3( 0x83,0xC7,0x02 )                                    /* add         edi,2 */ \
_LINE2( 0xD1,0xE9 )                                         /* shr         ecx,1 */ \
_LINE2( 0xF3,0xAB )                                         /* rep stos    dword ptr es:[edi] */ \
_LINE1( 0x5F )                                              /* pop         edi */ \
_END_ASM

/// Заполнение памяти беззнаковым двойным словом.
/// @brief for CPUTYPE1
#define STOSIMEMCPU_STD \
_BEGIN_ASM \
_LINE1( 0x57 )                                              /* push        edi */ \
_LINE4( 0x8B,0x7C,0x24,0x08 )                               /* mov         edi,dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE4( 0x8B,0x44,0x24,0x10 )                               /* mov         eax,dword ptr [esp+010h]  */ \
_LINE2( 0xF3,0xAB )                                         /* rep stos    dword ptr es:[edi] */ \
_LINE1( 0x5F )                                              /* pop         edi */ \
_END_ASM

#define _STOSMEM128_MOVEUPS \
_LINE3( 0x0F,0x11,0x00 )                                    /* movups      xmmword ptr [eax],xmm0 */ \
_LINE4( 0x0F,0x11,0x48,0x10 )                               /* movups      xmmword ptr [eax+10h],xmm1 */ \
_LINE4( 0x0F,0x11,0x50,0x20 )                               /* movups      xmmword ptr [eax+20h],xmm2 */ \
_LINE4( 0x0F,0x11,0x58,0x30 )                               /* movups      xmmword ptr [eax+30h],xmm3 */ \
_LINE4( 0x0F,0x11,0x60,0x40 )                               /* movups      xmmword ptr [eax+40h],xmm4 */ \
_LINE4( 0x0F,0x11,0x68,0x50 )                               /* movups      xmmword ptr [eax+50h],xmm5 */ \
_LINE4( 0x0F,0x11,0x70,0x60 )                               /* movups      xmmword ptr [eax+60h],xmm6 */ \
_LINE4( 0x0F,0x11,0x78,0x70 )                               /* movups      xmmword ptr [eax+70h],xmm7 */

#define _STOSMEM128_MOVEAPS \
_LINE3( 0x0F,0x29,0x00 )                                    /* movaps      xmmword ptr [eax],xmm0 */ \
_LINE4( 0x0F,0x29,0x48,0x10 )                               /* movaps      xmmword ptr [eax+10h],xmm1 */ \
_LINE4( 0x0F,0x29,0x50,0x20 )                               /* movaps      xmmword ptr [eax+20h],xmm2 */ \
_LINE4( 0x0F,0x29,0x58,0x30 )                               /* movaps      xmmword ptr [eax+30h],xmm3 */ \
_LINE4( 0x0F,0x29,0x60,0x40 )                               /* movaps      xmmword ptr [eax+40h],xmm4 */ \
_LINE4( 0x0F,0x29,0x68,0x50 )                               /* movaps      xmmword ptr [eax+50h],xmm5 */ \
_LINE4( 0x0F,0x29,0x70,0x60 )                               /* movaps      xmmword ptr [eax+60h],xmm6 */ \
_LINE4( 0x0F,0x29,0x78,0x70 )                               /* movaps      xmmword ptr [eax+70h],xmm7 */

#define _STOSMEM128_MOVNTDQ \
_LINE4( 0x66,0x0F,0xE7,0x00 )                               /* movapd      xmmword ptr [eax],xmm0 */ \
_LINE5( 0x66,0x0F,0xE7,0x48,0x10 )                          /* movapd      xmmword ptr [eax+10h],xmm1 */ \
_LINE5( 0x66,0x0F,0xE7,0x50,0x20 )                          /* movapd      xmmword ptr [eax+20h],xmm2 */ \
_LINE5( 0x66,0x0F,0xE7,0x58,0x30 )                          /* movapd      xmmword ptr [eax+30h],xmm3 */ \
_LINE5( 0x66,0x0F,0xE7,0x60,0x40 )                          /* movapd      xmmword ptr [eax+40h],xmm4 */ \
_LINE5( 0x66,0x0F,0xE7,0x68,0x50 )                          /* movapd      xmmword ptr [eax+50h],xmm5 */ \
_LINE5( 0x66,0x0F,0xE7,0x70,0x60 )                          /* movapd      xmmword ptr [eax+60h],xmm6 */ \
_LINE5( 0x66,0x0F,0xE7,0x78,0x70 )                          /* movapd      xmmword ptr [eax+70h],xmm7 */

#define _STOSMEM128_MOVEAPD \
_LINE4( 0x66,0x0F,0x29,0x00 )                               /* movapd      xmmword ptr [eax],xmm0 */ \
_LINE5( 0x66,0x0F,0x29,0x48,0x10 )                          /* movapd      xmmword ptr [eax+10h],xmm1 */ \
_LINE5( 0x66,0x0F,0x29,0x50,0x20 )                          /* movapd      xmmword ptr [eax+20h],xmm2 */ \
_LINE5( 0x66,0x0F,0x29,0x58,0x30 )                          /* movapd      xmmword ptr [eax+30h],xmm3 */ \
_LINE5( 0x66,0x0F,0x29,0x60,0x40 )                          /* movapd      xmmword ptr [eax+40h],xmm4 */ \
_LINE5( 0x66,0x0F,0x29,0x68,0x50 )                          /* movapd      xmmword ptr [eax+50h],xmm5 */ \
_LINE5( 0x66,0x0F,0x29,0x70,0x60 )                          /* movapd      xmmword ptr [eax+60h],xmm6 */ \
_LINE5( 0x66,0x0F,0x29,0x78,0x70 )                          /* movapd      xmmword ptr [eax+70h],xmm7 */

/// Заполнение памяти беззнаковым двойным словом.
/// @brief for CPUTYPE3
#define STOSIMEMSSE_STD \
_BEGIN_ASM \
_LINE6( 0xF3,0x0F,0x10,0x44,0x24,0x0C )                     /* movss       xmm0,dword ptr [esp+0Ch] */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8] */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )                               /* shufps      xmm0,xmm0,0 */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0 */ \
_LINE3( 0x0F,0x28,0xD1 )                                    /* movaps      xmm2,xmm1 */ \
_LINE3( 0x0F,0x28,0xD8 )                                    /* movaps      xmm3,xmm0 */ \
_LINE3( 0x0F,0x28,0xE1 )                                    /* movaps      xmm4,xmm1 */ \
_LINE3( 0x0F,0x28,0xE8 )                                    /* movaps      xmm5,xmm0 */ \
_LINE3( 0x0F,0x28,0xF1 )                                    /* movaps      xmm6,xmm1 */ \
_LINE3( 0x0F,0x28,0xF8 )                                    /* movaps      xmm7,xmm0 */ \
_LINE2( 0xA8,0x03 )                                         /* test        al,3 */ \
_LINE2( 0x74,0x3F )                                         /* je          clean (0CA125Dh) */ \
_LINE2( 0x8B,0xD1 )                                         /* mov         edx,ecx */ \
_LINE3( 0x83,0xE1,0x1F )                                    /* and         ecx,1Fh */ \
_LINE2( 0xE3,0x09 )                                         /* jecxz       beee (0CA1239h) */ \
_LINE4( 0xF3,0x0F,0x11,0x00 )                               /* movss       dword ptr [eax],xmm0 */ \
_LINE3( 0x83,0xC0,0x04 )                                    /* add         eax,4h */ \
_LINE2( 0xE2,0xF7 )                                         /* loop        bbbe (2512A2h) */ \
_LINE2( 0x8B,0xCA )                                         /* mov         ecx,edx */ \
_LINE3( 0xC1,0xE9,0x05 )                                    /* shr         ecx,5 */ \
_LINE2( 0xE3,0x26 )                                         /* jecxz       beee1 (0CA125Bh) */ \
_STOSMEM128_MOVEUPS \
_LINE5( 0x05,0x80,0x00,0x00,0x00 )                          /* add         eax,80h */ \
_LINE2( 0xE2,0xDA )                                         /* loop        bbbe1 (0CA1244h) */ \
_LINE2( 0xEB,0x79 )                                         /* jmp         mmm4 (0CA12CCh) */ \
_LINE2( 0x8B,0xD0 )                                         /* mov         edx,eax */ \
_LINE3( 0xC1,0xEA,0x02 )                                    /* shr         edx,2 */ \
_LINE3( 0x83,0xE2,0x03 )                                    /* and         edx,3 */ \
_LINE2( 0x2B,0xCA )                                         /* sub         ecx,edx */ \
_LINE3( 0xF6,0xC2,0x01 )                                    /* test        dl,1 */ \
_LINE2( 0x74,0x07 )                                         /* je          mmm1 (0CA1273h) */ \
_LINE4( 0xF3,0x0F,0x11,0x00 )                               /* movss       dword ptr [eax],xmm0 */ \
_LINE3( 0x83,0xC0,0x04 )                                    /* add         eax,04h */ \
_LINE3( 0xF6,0xC2,0x02 )                                    /* test        dl,2 */ \
_LINE2( 0x74,0x06 )                                         /* je          mmm2 (0CA127Eh) */ \
_LINE3( 0x0F,0x13,0x00 )                                    /* movlps      qword ptr [eax],xmm0 */ \
_LINE3( 0x83,0xC0,0x08 )                                    /* add         eax,08h */ \
_LINE2( 0x8B,0xD1 )                                         /* mov         edx,ecx */ \
_LINE3( 0x83,0xE1,0x1C )                                    /* and         ecx,1Ch */ \
_LINE2( 0x2B,0xD1 )                                         /* sub         edx,ecx */ \
_LINE3( 0xC1,0xE9,0x02 )                                    /* shr         ecx,2 */ \
_LINE2( 0xE3,0x08 )                                         /* jecxz       eeee (0CA1293h) */ \
_LINE3( 0x0F,0x29,0x00 )                                    /* movaps      xmmword ptr [eax],xmm0 */ \
_LINE3( 0x83,0xC0,0x10 )                                    /* add         eax,10h */ \
_LINE2( 0xE2,0xF8 )                                         /* loop         bbee (0CA1288h) */ \
_LINE2( 0x8B,0xCA )                                         /* mov         ecx,edx */ \
_LINE3( 0xC1,0xE9,0x05 )                                    /* shr         ecx,5 */ \
_LINE2( 0xE3,0x26 )                                         /* jecxz       eeee1 (0CA12B5h) */ \
_STOSMEM128_MOVEAPS \
_LINE5( 0x05,0x80,0x00,0x00,0x00 )                          /* add         eax,80h */ \
_LINE2( 0xE2,0xDA )                                         /* loop        bbee1 (0CA129Eh) */ \
_LINE3( 0xF6,0xC2,0x01 )                                    /* test        dl,1 */ \
_LINE2( 0x74,0x07 )                                         /* je          mmm3 (0CA12C1h) */ \
_LINE4( 0xF3,0x0F,0x11,0x00 )                               /* movss       dword ptr [eax],xmm0 */ \
_LINE3( 0x83,0xC0,0x04 )                                    /* add         eax,4 */ \
_LINE3( 0xF6,0xC2,0x02 )                                    /* test        dl,2 */ \
_LINE2( 0x74,0x06 )                                         /* je          mmm4 (0CA12CCh) */ \
_LINE3( 0x0F,0x13,0x00 )                                    /* movlps      qword ptr [eax],xmm0 */ \
_LINE3( 0x83,0xC0,0x08 )                                    /* add         eax,8 */ \
_END_ASM

/// Заполнение памяти беззнаковым двойным словом.
/// @brief for CPUTYPE3
#define STOSIMEMSSE2_STD \
BEGIN_ASM \
_LINE1( 0x57 )                                              /* push        edi */ \
_LINE4( 0x8B,0x44,0x24,0x10 )                               /* mov         eax,dword ptr [esp+010h]  */ \
ASM( mov edx,[esp+0x0C] ) \
ASM( mov edi,[esp+0x08] ) \
ASM( cmp edx,32 ) \
ASM( jb STOSIMEMDOWNTOSSE2 ) \
ASM( test edi,0xF ) \
ASM( jz STOSIMEMUPTOSSE2 ) \
ASM( STOSIMEMDOWNTOSSE2: ) \
ASM( mov ecx,edx) \
ASM( jecxz FAST1STOSIMEMSSE2 ) \
ASM( rep stos dword ptr es:[edi] ) \
ASM( FAST1STOSIMEMSSE2: ) \
_LINE1( 0x5F )                                              /* pop         edi */ \
_LINE3( 0xC2,0x0C,0x00 ) \
ASM( STOSIMEMUPTOSSE2: ) \
ASM( mov ecx,edx ) \
ASM( shr ecx,5 ) \
ASM( and edx,0x1F ) \
ASM( jecxz FAST3STOSIMEMSSE2 ) \
ASM( movd xmm0,eax ) \
ASM( shufps xmm0,xmm0,00 ) \
ASM( movaps xmm1,xmm0 ) \
ASM( movaps xmm2,xmm0 ) \
ASM( movaps xmm3,xmm1 ) \
ASM( movaps xmm4,xmm2 ) \
ASM( movaps xmm5,xmm3 ) \
ASM( movaps xmm6,xmm4 ) \
ASM( movaps xmm7,xmm5 ) \
ASM( ssell2STOSIMEMSSE2: ) \
ASM( movaps [edi],xmm0 ) \
ASM( movaps [edi+16],xmm1 ) \
ASM( movaps [edi+32],xmm2 ) \
ASM( movaps [edi+48],xmm3 ) \
ASM( movaps [edi+64],xmm4 ) \
ASM( movaps [edi+80],xmm5 ) \
ASM( movaps [edi+96],xmm6 ) \
ASM( movaps [edi+112],xmm7 ) \
ASM( add edi,128 ) \
ASM( loop ssell2STOSIMEMSSE2 ) \
ASM( FAST3STOSIMEMSSE2: ) \
ASM( mov ecx,edx ) \
ASM( jecxz FAST4STOSIMEMSSE2 ) \
ASM( rep stos dword ptr es:[edi] ) \
ASM( FAST4STOSIMEMSSE2: ) \
_LINE1( 0x5F )                                              /* pop         edi */ \
_LINE3( 0xC2,0x0C,0x00 ) \
END_ASM

/// Заполнение памяти беззнаковым двойным словом.
/// @brief for CPUTYPE4
#define STOSIMEMSSE3_STD \
_BEGIN_ASM \
_LINE6( 0xF3,0x0F,0x10,0x44,0x24,0x0C )                     /* movss       xmm0,dword ptr [esp+0Ch] */ \
_LINE4( 0x8B,0x4C,0x24,0x08 )                               /* mov         ecx,dword ptr [esp+8] */ \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4] */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )                               /* shufps      xmm0,xmm0,0 */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0 */ \
_LINE3( 0x0F,0x28,0xD1 )                                    /* movaps      xmm2,xmm1 */ \
_LINE3( 0x0F,0x28,0xD8 )                                    /* movaps      xmm3,xmm0 */ \
_LINE3( 0x0F,0x28,0xE1 )                                    /* movaps      xmm4,xmm1 */ \
_LINE3( 0x0F,0x28,0xE8 )                                    /* movaps      xmm5,xmm0 */ \
_LINE3( 0x0F,0x28,0xF1 )                                    /* movaps      xmm6,xmm1 */ \
_LINE3( 0x0F,0x28,0xF8 )                                    /* movaps      xmm7,xmm0 */ \
_LINE2( 0xA8,0x03 )                                         /* test        al,3 */ \
_LINE2( 0x74,0x4A )                                         /* je          clean (0CA125Dh) */ \
_LINE2( 0x8B,0xD1 )                                         /* mov         edx,ecx */ \
_LINE3( 0x83,0xE1,0x1F )                                    /* and         ecx,1Fh */ \
_LINE2( 0xE3,0x09 )                                         /* jecxz       beee (0CA1239h) */ \
_LINE4( 0xF3,0x0F,0x11,0x00 )                               /* movss       dword ptr [eax],xmm0 */ \
_LINE3( 0x83,0xC0,0x04 )                                    /* add         eax,4h */ \
_LINE2( 0xE2,0xF7 )                                         /* loop        bbbe (2512A2h) */ \
_LINE2( 0x8B,0xCA )                                         /* mov         ecx,edx */ \
_LINE3( 0xC1,0xE9,0x05 )                                    /* shr         ecx,5 */ \
_LINE2( 0xE3,0x2E )                                         /* jecxz       beee1 (0CA125Bh) */ \
_STOSMEM128_MOVNTDQ \
_LINE5( 0x05,0x80,0x00,0x00,0x00 )                          /* add         eax,80h */ \
_LINE2( 0xE2,0xD2 )                                         /* loop        bbbe1 (0CA1244h) */ \
_LINE5( 0xE9,0x81,0x00,0x00,0x00 )                          /* jmp         mmm4 (0CA12CCh) */ \
_LINE2( 0x8B,0xD0 )                                         /* mov         edx,eax */ \
_LINE3( 0xC1,0xEA,0x02 )                                    /* shr         edx,2 */ \
_LINE3( 0x83,0xE2,0x03 )                                    /* and         edx,3 */ \
_LINE2( 0x2B,0xCA )                                         /* sub         ecx,edx */ \
_LINE3( 0xF6,0xC2,0x01 )                                    /* test        dl,1 */ \
_LINE2( 0x74,0x07 )                                         /* je          mmm1 (0CA1273h) */ \
_LINE4( 0xF3,0x0F,0x11,0x00 )                               /* movss       dword ptr [eax],xmm0 */ \
_LINE3( 0x83,0xC0,0x04 )                                    /* add         eax,04h */ \
_LINE3( 0xF6,0xC2,0x02 )                                    /* test        dl,2 */ \
_LINE2( 0x74,0x06 )                                         /* je          mmm2 (0CA127Eh) */ \
_LINE3( 0x0F,0x13,0x00 )                                    /* movlps      qword ptr [eax],xmm0 */ \
_LINE3( 0x83,0xC0,0x08 )                                    /* add         eax,08h */ \
_LINE2( 0x8B,0xD1 )                                         /* mov         edx,ecx */ \
_LINE3( 0x83,0xE1,0x1C )                                    /* and         ecx,1Ch */ \
_LINE2( 0x2B,0xD1 )                                         /* sub         edx,ecx */ \
_LINE3( 0xC1,0xE9,0x02 )                                    /* shr         ecx,2 */ \
_LINE2( 0xE3,0x08 )                                         /* jecxz       eeee (0CA1293h) */ \
_LINE3( 0x0F,0x29,0x00 )                                    /* movaps      xmmword ptr [eax],xmm0 */ \
_LINE3( 0x83,0xC0,0x10 )                                    /* add         eax,10h */ \
_LINE2( 0xE2,0xF8 )                                         /* loop         bbee (0CA1288h) */ \
_LINE2( 0x8B,0xCA )                                         /* mov         ecx,edx */ \
_LINE3( 0xC1,0xE9,0x05 )                                    /* shr         ecx,5 */ \
_LINE2( 0xE3,0x2E )                                         /* jecxz       eeee1 (0CA12B5h) */ \
_STOSMEM128_MOVEAPD \
_LINE5( 0x05,0x80,0x00,0x00,0x00 )                          /* add         eax,80h */ \
_LINE2( 0xE2,0xD2 )                                         /* loop        bbee1 (0CA129Eh) */ \
_LINE3( 0xF6,0xC2,0x01 )                                    /* test        dl,1 */ \
_LINE2( 0x74,0x07 )                                         /* je          mmm3 (0CA12C1h) */ \
_LINE4( 0xF3,0x0F,0x11,0x00 )                               /* movss       dword ptr [eax],xmm0 */ \
_LINE3( 0x83,0xC0,0x04 )                                    /* add         eax,4 */ \
_LINE3( 0xF6,0xC2,0x02 )                                    /* test        dl,2 */ \
_LINE2( 0x74,0x06 )                                         /* je          mmm4 (0CA12CCh) */ \
_LINE3( 0x0F,0x13,0x00 )                                    /* movlps      qword ptr [eax],xmm0 */ \
_LINE3( 0x83,0xC0,0x08 )                                    /* add         eax,8 */ \
_END_ASM

#endif /* GEN3_MEM_STOS_H_ */

