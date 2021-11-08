//=============================================================================
///**
// *  @file   render_span.h
// *
// *  $Id: render_span.h 16.10.2011  $
// *
// *  @brief generator 3, assembler render span, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_RENDER_SPAN_H
#define GEN3_RENDER_SPAN_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** SPAN DRAW STDCALL *********************************
// span draw ecx=[esp+4]-void *data

/// ќтрисовка горизонтальной линии, команды CPU
/// @brief for CPUTYPE1
#define RENDERPSPAN4AFCPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x4C,0x24,0x04 )                               /* mov         ecx,dword ptr [esp+4] */ \
_LINE1( 0x57 )                                              /* push        edi */ \
_LINE3( 0x8B,0x79,0x08 )                                    /* mov         edi,dword ptr [ecx+4] */ \
_LINE3( 0x8B,0x41,0x04 )                                    /* mov         eax,dword ptr [ecx+4] */ \
_LINE2( 0x8B,0x09 )                                         /* mov         ecx,dword ptr [ecx] */ \
_LINE2( 0xE3,0x2  )                                         /* jecxz       DPNSHEND (0A11A0Ah) */ \
_LINE2( 0xF3,0xAB )                                         /* rep stos    dword ptr es:[edi] */ \
_LINE1( 0x5F )                                              /* pop         edi */ \
_END_ASM

// count , mem , depth , z_start, z_step , color
/// ќтрисовка горизонтальной линии с тестом глубины, команды CPU
/// @brief for CPUTYPE1
#define RENDERPSPAN4AFDCPU_STD \
BEGIN_ASM \
_LINE4( 0x8B,0x4C,0x24,0x04 )                     /* mov         ecx,dword ptr [esp+4] */ \
_LINE1( 0x57 )                                    /* push        edi */ \
_LINE1( 0x56 )                                    /* push        esi */ \
_LINE1( 0x53 )                                    /* push        ebx */ \
_LINE3( 0x8B,0x79,0x08 )                          /* mov         edi,dword ptr [ecx+8] */ \
_LINE3( 0x8B,0x71,0x0C )                          /* mov         esi,dword ptr [ecx+12] */ \
_LINE3( 0x8B,0x51,0x10 )                          /* mov         edx,dword ptr [ecx+16] */ \
_LINE3( 0x8B,0x59,0x14 )                          /* mov         ebx,dword ptr [ecx+20] */ \
_LINE3( 0x8B,0x41,0x04 )                          /* mov         eax,dword ptr [ecx+4] */ \
_LINE2( 0x8B,0x09 )                               /* mov         ecx,dword ptr [ecx] */ \
_LINE2( 0xE3,0x1A  )                              /* jecxz       DPNSHEND (0A11A0Ah) */ \
_LINE3( 0xC1,0xCA,0x0F )                          /* ror         edx,0Fh */ \
_LINE3( 0x66,0x3B,0x16 )                          /* cmp         dx,word ptr [esi] */ \
_LINE2( 0x73,0x05 )                               /* jae         DPNSHNOTS (0A119FDh) */ \
_LINE2( 0x89,0x07 )                               /* mov         dword ptr [edi],eax */ \
_LINE3( 0x66,0x89,0x16 )                          /* mov         word ptr [esi],dx */ \
_LINE3( 0xC1,0xCA,0x11 )                          /* ror         edx,11h */ \
_LINE2( 0x03,0xD3 )                               /* add         edx,ebx */ \
_LINE3( 0x83,0xC7,0x04 )                          /* add         edi,4 */ \
_LINE3( 0x83,0xC6,0x02 )                          /* add         esi,2 */ \
_LINE2( 0xE2,0xE6 )                               /* loop DPNSHEEEE ) */ \
_LINE1( 0x5B )                                    /* pop         ebx */ \
_LINE1( 0x5E )                                    /* pop         esi */ \
_LINE1( 0x5F )                                    /* pop         edi */ \
END_ASM

/// ќтрисовка горизонтальной линии с тестом глубины, команды SSE
/// @brief for CPUTYPE3
#define RENDERPSPAN4AFDSSE_STD \
BEGIN_ASM \
_LINE4( 0x8B,0x4C,0x24,0x04 )                     /* mov         ecx,dword ptr [esp+4] */ \
ASM( push edi ) \
ASM( push esi ) \
ASM( push ebx ) \
ASM( mov edi,[ecx+8] ) \
ASM( mov esi,[ecx+12] ) \
ASM( movss xmm3,[ecx+24] ) \
ASM( cvtsi2ss xmm0,[ecx+16] ) \
ASM( mulss xmm0,xmm3 ) \
ASM( cvtsi2ss xmm1,[ecx+20] ) \
ASM( mulss xmm1,xmm3 ) \
ASM( shufps xmm0,xmm0,0x00 ) \
ASM( shufps xmm1,xmm1,0x00 ) \
ASM( addss xmm0,xmm1 ) \
ASM( shufps xmm0,xmm0,0xE0 ) \
ASM( addss xmm0,xmm1 ) \
ASM( shufps xmm0,xmm0,0xC4 ) \
ASM( addss xmm0,xmm1 ) \
ASM( shufps xmm0,xmm0,0x27 ) \
ASM( mov eax,[ecx+4] ) \
ASM( mov ecx,[ecx] ) \
ASM( test cl,1 ) \
ASM( jz DPNSHNOTSs1a11 ) \
ASM( cvttss2si edx,xmm0 ) \
ASM( cmp dx,[esi] ) \
ASM( jae DPNSHNOTSs1a1 ) \
ASM( mov [edi],eax ) \
ASM( mov [esi],dx ) \
ASM( DPNSHNOTSs1a1: ) \
ASM( add edi,4 ) \
ASM( add esi,2 ) \
ASM( addps xmm0,xmm1 ) \
ASM( DPNSHNOTSs1a11: ) \
ASM( addps xmm1,xmm1 ) \
ASM( test cl,2 ) \
ASM( jz DPNSHNOTSs1a21 ) \
ASM( movaps xmm2,xmm0 ) \
ASM( cvttss2si edx,xmm0 ) \
ASM( cmp dx,[esi] ) \
ASM( jae DPNSHNOTSs1a2 ) \
ASM( mov [edi],eax ) \
ASM( mov [esi],dx ) \
ASM( DPNSHNOTSs1a2: ) \
ASM( shufps xmm2,xmm2,0xE5 ) \
ASM( cvttss2si edx,xmm2 ) \
ASM( cmp dx,[esi+2] ) \
ASM( jae DPNSHNOTSs2a3 ) \
ASM( mov [edi+4],eax ) \
ASM( mov [esi+2],dx ) \
ASM( DPNSHNOTSs2a3: ) \
ASM( add edi,8 ) \
ASM( add esi,4 ) \
ASM( addps xmm0,xmm1 ) \
ASM( DPNSHNOTSs1a21: ) \
ASM( addps xmm1,xmm1 ) \
ASM( shr ecx,2 ) \
ASM( jecxz DPNSHendss ) \
ASM( DPNSHEEEEs: ) \
ASM( movaps xmm2,xmm0 ) \
ASM( cvttss2si edx,xmm0 ) \
ASM( cmp dx,[esi] ) \
ASM( jae DPNSHNOTSs1 ) \
ASM( mov [edi],eax ) \
ASM( mov [esi],dx ) \
ASM( DPNSHNOTSs1: ) \
ASM( movhlps xmm3,xmm0 ) \
ASM( shufps xmm2,xmm2,0xE5 ) \
ASM( cvttss2si edx,xmm2 ) \
ASM( cmp dx,[esi+2] ) \
ASM( jae DPNSHNOTSs2 ) \
ASM( mov [edi+4],eax ) \
ASM( mov [esi+2],dx ) \
ASM( DPNSHNOTSs2: ) \
ASM( cvttss2si edx,xmm3 ) \
ASM( cmp dx,[esi+4] ) \
ASM( jae DPNSHNOTSs3 ) \
ASM( mov [edi+8],eax ) \
ASM( mov [esi+4],dx ) \
ASM( DPNSHNOTSs3: ) \
ASM( shufps xmm3,xmm3,0xE5) \
ASM( cvttss2si edx,xmm2 ) \
ASM( cmp dx,[esi+6] ) \
ASM( jae DPNSHNOTSs4 ) \
ASM( mov [edi+12],eax ) \
ASM( mov [esi+6],dx ) \
ASM( DPNSHNOTSs4: ) \
ASM( add edi,16 ) \
ASM( add esi,8 ) \
ASM( addps xmm0,xmm1 ) \
ASM( loop DPNSHEEEEs ) \
ASM( DPNSHendss: ) \
ASM( pop ebx ) \
ASM( pop esi ) \
ASM( pop edi ) \
END_ASM

// count , mem , depth , z_start, z_step , color
/// ќтрисовка горизонтальной линии с цветовой интерпол€цией, команды SSE2
/// @brief for CPUTYPE4
#define RENDERPSPAN4AFSSSE2_STD \
BEGIN_ASM \
_LINE4( 0x8B,0x4C,0x24,0x04 )                     /* mov         ecx,dword ptr [esp+4] */ \
_LINE1( 0x57 )                                    /* push        edi */ \
_LINE3( 0x8B,0x79,0x08 )                          /* mov         edi,dword ptr [ecx+8] */ \
ASM( movss xmm5,[ecx+28] ) \
ASM( movups xmm6,[ecx+32] ) \
ASM( movups xmm7,[ecx+48] ) \
ASM( shufps xmm5,xmm5,0x00 ) \
ASM( cvtdq2ps xmm6,xmm6 ) \
ASM( cvtdq2ps xmm7,xmm7 ) \
ASM( mulps xmm6,xmm5 ) \
ASM( mulps xmm7,xmm5 ) \
_LINE5( 0xB8,0xFF,0x00,0x00,0x00 )                /* mov         eax,FFh */ \
_LINE4( 0xF3,0x0F,0x2A,0xD8 )                     /* cvtsi2ss    xmm3,eax */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                     /* shufps      xmm3,xmm3,0 */ \
_LINE2( 0x8B,0x09 )                               /* mov         ecx,dword ptr [ecx] */ \
ASM( test ecx,1 ) \
ASM( jz DPNSHEND43 ) \
_LINE3( 0x0F,0x28,0xEE )                          /* movaps      xmm5,xmm6 */ \
_LINE3( 0x0F,0x28,0xE3 )                          /* movaps      xmm4,xmm3 */ \
_LINE4( 0x0F,0xC2,0xE6,0x01 )                     /* cmpltps     xmm4,xmm6 */ \
_LINE4( 0xF3,0x0F,0x5B,0xED )                     /* cvttps2dq   xmm5,xmm5 */ \
ASM( psrld xmm4,24 ) \
_LINE3( 0x0F,0x56,0xEC )                          /* orps        xmm5,xmm4 */ \
_LINE4( 0x66,0x0F,0x6B,0xED )                     /* packssdw    xmm5,xmm5 */ \
_LINE4( 0x66,0x0F,0x67,0xED )                     /* packuswb    xmm5,xmm5 */ \
_LINE4( 0xF3,0x0F,0x11,0x2F )                     /* movss       dword ptr [edi],xmm5 */ \
_LINE3( 0x83,0xC7,0x04 )                          /* add         edi,4 */ \
ASM( addps xmm6,xmm7 )                            /* addps       xmm6,xmm7 */ \
ASM( DPNSHEND43: ) \
ASM( shr ecx,1 ) \
ASM( test ecx,1 ) \
ASM( jz DPNSHEND42 ) \
_LINE3( 0x0F,0x28,0xEE )                          /* movaps      xmm5,xmm6 */ \
_LINE3( 0x0F,0x28,0xE3 )                          /* movaps      xmm4,xmm3 */ \
ASM( addps xmm6,xmm7 )                            /* addps       xmm6,xmm7 */ \
_LINE3( 0x0F,0x28,0xC3 )                          /* movaps      xmm0,xmm3 */ \
_LINE3( 0x0F,0x28,0xCE )                          /* movaps      xmm1,xmm6 */ \
_LINE4( 0x0F,0xC2,0xE5,0x01 )                     /* cmpltps     xmm4,xmm5 */ \
_LINE4( 0x0F,0xC2,0xC6,0x01 )                     /* cmpltps     xmm0,xmm6 */ \
_LINE4( 0xF3,0x0F,0x5B,0xED )                     /* cvttps2dq   xmm5,xmm5 */ \
_LINE4( 0xF3,0x0F,0x5B,0xC9 )                     /* cvttps2dq   xmm1,xmm1 */ \
ASM( psrld xmm4,24 ) \
ASM( psrld xmm0,24 ) \
_LINE3( 0x0F,0x56,0xEC )                          /* orps        xmm5,xmm4 */ \
_LINE3( 0x0F,0x56,0xC8 )                          /* orps        xmm1,xmm0 */ \
_LINE4( 0x66,0x0F,0x6B,0xE9 )                     /* packssdw    xmm5,xmm1 */ \
_LINE4( 0x66,0x0F,0x67,0xED )                     /* packuswb    xmm5,xmm5 */ \
ASM( movlps qword ptr [edi],xmm5 ) \
_LINE3( 0x83,0xC7,0x08 )                          /* add         edi,8 */ \
ASM( addps xmm6,xmm7 )                            /* addps       xmm6,xmm7 */ \
ASM( DPNSHEND42: ) \
ASM( shr ecx,1 ) \
ASM( jecxz DPNSHEND41 )                              /* jecxz       DPNSHEND (0A11A0Ah) */ \
ASM( DPNSHEEEE41: ) \
_LINE3( 0x0F,0x28,0xEE )                          /* movaps      xmm5,xmm6 */ \
_LINE3( 0x0F,0x28,0xE3 )                          /* movaps      xmm4,xmm3 */ \
ASM( addps xmm6,xmm7 )                            /* addps       xmm6,xmm7 */ \
_LINE3( 0x0F,0x28,0xC3 )                          /* movaps      xmm0,xmm3 */ \
_LINE4( 0xF3,0x0F,0x5B,0xCE )                     /* cvttps2dq   xmm1,xmm6 */ \
_LINE4( 0x0F,0xC2,0xE5,0x01 )                     /* cmpltps     xmm4,xmm5 */ \
_LINE3( 0x0F,0x28,0xD3 )                          /* movaps      xmm2,xmm3 */ \
_LINE4( 0x0F,0xC2,0xC6,0x01 )                     /* cmpltps     xmm0,xmm6 */ \
_LINE4( 0xF3,0x0F,0x5B,0xED )                     /* cvttps2dq   xmm5,xmm5 */ \
ASM( addps xmm6,xmm7 )                            /* addps       xmm6,xmm7 */ \
ASM( psrld xmm4,24 ) \
ASM( psrld xmm0,24 ) \
_LINE4( 0x0F,0xC2,0xD6,0x01 )                     /* cmpltps     xmm2,xmm6 */ \
_LINE3( 0x0F,0x56,0xEC )                          /* orps        xmm5,xmm4 */ \
_LINE3( 0x0F,0x56,0xC8 )                          /* orps        xmm1,xmm0 */ \
ASM( psrld xmm2,24 ) \
_LINE4( 0xF3,0x0F,0x5B,0xE6 )                     /* cvttps2dq   xmm4,xmm6 */ \
_LINE4( 0x66,0x0F,0x6B,0xE9 )                     /* packssdw    xmm5,xmm1 */ \
_LINE3( 0x0F,0x28,0xC3 )                          /* movaps      xmm0,xmm3 */ \
ASM( addps xmm6,xmm7 )                            /* addps       xmm6,xmm7 */ \
_LINE3( 0x0F,0x56,0xE2 )                          /* orps        xmm4,xmm2 */ \
_LINE4( 0x0F,0xC2,0xC6,0x01 )                     /* cmpltps     xmm0,xmm6 */ \
_LINE4( 0xF3,0x0F,0x5B,0xCE )                     /* cvttps2dq   xmm1,xmm6 */ \
ASM( psrld xmm0,24 ) \
_LINE3( 0x0F,0x56,0xC9 )                          /* orps        xmm1,xmm0 */ \
_LINE4( 0x66,0x0F,0x6B,0xE1 )                     /* packssdw    xmm4,xmm1 */ \
_LINE4( 0x66,0x0F,0x67,0xEC )                     /* packuswb    xmm5,xmm4 */ \
ASM( movups [edi],xmm5 ) \
_LINE3( 0x83,0xC7,0x10 )                          /* add         edi,16 */ \
ASM( addps xmm6,xmm7 )                            /* addps       xmm6,xmm7 */ \
ASM( loop DPNSHEEEE41 )                           /* loop DPNSHEEEE41 */ \
ASM( DPNSHEND41: ) \
_LINE1( 0x5F )                                    /* pop         edi */ \
END_ASM

// count , mem , depth , z_start, z_step , color
/// ќтрисовка горизонтальной линии с тестом глубины и цветовой интерпол€цией, команды SSE2
/// @brief for CPUTYPE4
#define RENDERPSPAN4AFDSSSE2_STD \
BEGIN_ASM \
_LINE4( 0x8B,0x4C,0x24,0x04 )                     /* mov         ecx,dword ptr [esp+4] */ \
_LINE1( 0x57 )                                    /* push        edi */ \
_LINE1( 0x56 )                                    /* push        esi */ \
_LINE1( 0x53 )                                    /* push        ebx */ \
_LINE3( 0x8B,0x79,0x08 )                          /* mov         edi,dword ptr [ecx+8] */ \
_LINE3( 0x8B,0x71,0x0C )                          /* mov         esi,dword ptr [ecx+12] */ \
_LINE3( 0x8B,0x51,0x10 )                          /* mov         edx,dword ptr [esp+16] */ \
_LINE3( 0x8B,0x59,0x14 )                          /* mov         ebx,dword ptr [esp+20] */ \
_LINE5( 0xF3,0x0F,0x10,0x69,0x1C )                /* movss       xmm5,dword ptr [ecx+1Ch] */ \
_LINE4( 0x0F,0x10,0x71,0x20 )                     /* movups      xmm6,xmmword ptr [ecx+20h] */ \
_LINE4( 0x0F,0x10,0x79,0x30 )                     /* movups      xmm7,xmmword ptr [ecx+30h] */ \
_LINE4( 0x0F,0xC6,0xED,0x00 )                     /* shufps      xmm5,xmm5,0 */ \
_LINE3( 0x0F,0x5B,0xF6 )                          /* cvtdq2ps    xmm6,xmm6 */ \
_LINE3( 0x0F,0x5B,0xFF )                          /* cvtdq2ps    xmm7,xmm7 */ \
_LINE3( 0x0F,0x59,0xF5 )                          /* mulps       xmm6,xmm5 */ \
_LINE3( 0x0F,0x59,0xFD )                          /* mulps       xmm7,xmm5 */ \
_LINE5( 0xB8,0xFF,0x00,0x00,0x00 )                /* mov         eax,FFh */ \
_LINE4( 0xF3,0x0F,0x2A,0xD8 )                     /* cvtsi2ss    xmm3,eax */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                     /* shufps      xmm3,xmm3,0 */ \
_LINE2( 0x8B,0x09 )                               /* mov         ecx,dword ptr [ecx] */ \
_LINE2( 0xE3,0x38 )                               /* jecxz       DPNSHEND (0A11A0Ah) */ \
_LINE3( 0xC1,0xCA,0x0F )                          /* ror         edx,0Fh */ \
_LINE3( 0x66,0x3B,0x16 )                          /* cmp         dx,word ptr [esi] */ \
_LINE2( 0x73,0x20 )                               /* jae         DPNSHNOTSs41 (131A49h) */ \
_LINE3( 0x0F,0x28,0xE3 )                          /* movaps      xmm4,xmm3 */ \
_LINE4( 0x0F,0xC2,0xE6,0x01 )                     /* cmpltps     xmm4,xmm6 */ \
_LINE3( 0x0F,0x54,0xE3 )                          /* andps       xmm4,xmm3 */ \
_LINE3( 0x0F,0x56,0xEC )                          /* orps        xmm5,xmm4 */ \
_LINE4( 0xF3,0x0F,0x5B,0xEE )                     /* cvttps2dq   xmm5,xmm6 */ \
_LINE4( 0x66,0x0F,0x6B,0xED )                     /* packssdw    xmm5,xmm5 */ \
_LINE4( 0x66,0x0F,0x67,0xED )                     /* packuswb    xmm5,xmm5 */ \
_LINE4( 0xF3,0x0F,0x11,0x2F )                     /* movss       dword ptr [edi],xmm5 */ \
_LINE3( 0x66,0x89,0x16 )                          /* mov         word ptr [esi],dx */ \
_LINE3( 0xC1,0xCA,0x11 )                          /* ror         edx,11h */ \
_LINE2( 0x03,0xD3 )                               /* add         edx,ebx */ \
_LINE3( 0x83,0xC7,0x04 )                          /* add         edi,4 */ \
_LINE3( 0x83,0xC6,0x02 )                          /* add         esi,2 */ \
_LINE3( 0x0F,0x58,0xF7 )                          /* addps       xmm6,xmm7 */ \
_LINE2( 0xE2,0xC8 )                               /* loop DPNSHEEEE41 */ \
_LINE1( 0x5B )                                    /* pop         ebx */ \
_LINE1( 0x5E )                                    /* pop         esi */ \
_LINE1( 0x5F )                                    /* pop         edi */ \
END_ASM

//**************************** SPAN DRAW FASTCALL *********************************

/// @brief for CPUTYPE1
#define RENDERPSPAN4AFCPU_CPP \
_BEGIN_ASM \
_LINE1( 0x57 )                                              /* push        edi */ \
ASM( mov edi,[ecx+8] ) \
ASM( mov eax,[ecx+4] ) \
ASM( mov ecx,[ecx] ) \
_LINE2( 0xF3,0xAB )                                         /* rep stos    dword ptr es:[edi] */ \
_LINE1( 0x5F )                                              /* pop         edi */ \
_END_ASM

// count , mem , depth , z_start, z_step , color
/// @brief for CPUTYPE1
#define RENDERPSPAN4AFDCPU_CPP \
BEGIN_ASM \
ASM( push edi ) \
ASM( push esi ) \
ASM( push ebx ) \
ASM( mov edi,[ecx+8] ) \
ASM( mov esi,[ecx+12] ) \
ASM( mov edx,[ecx+16] ) \
ASM( mov ebx,[ecx+20] ) \
ASM( mov eax,[ecx+4] ) \
ASM( mov ecx,[ecx] ) \
ASM( jecxz DPNSHEND ) \
ASM( DPNSHEEEE: ) \
ASM( ror edx,15 ) \
ASM( cmp dx,[esi] ) \
ASM( jae DPNSHNOTS ) \
ASM( mov [edi],eax ) \
ASM( mov [esi],dx ) \
ASM( DPNSHNOTS: ) \
ASM( ror edx,17 ) \
ASM( add edx,ebx ) \
ASM( add edi,4 ) \
ASM( add esi,2 ) \
ASM( loop DPNSHEEEE ) \
ASM( DPNSHEND: ) \
ASM( pop ebx ) \
ASM( pop esi ) \
ASM( pop edi ) \
END_ASM

#endif /* GEN3_RENDER_SPAN_H */
