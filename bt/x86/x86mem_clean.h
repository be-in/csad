//=============================================================================
///**
// *  @file   mem_clean.h
// *
// *  $Id: mem_clean.h 16.10.2011  $
// *
// *  @brief generator 3, assembler memory operations, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_MEM_CLEAN_H_
#define GEN3_MEM_CLEAN_H_

//**************************** CLEANMEM REGISTER FASTCALL *********************************
// vector cross product edi=[esp+4]-a void * eax=[esp+8]-c int

/// Очистка памяти.
/// @brief for CPUTYPE1
#define CLEANMEMCPU_STD \
_BEGIN_ASM \
_LINE1( 0x57 )                                              /* push        edi */ \
_LINE4( 0x8B,0x7C,0x24,0x08 )                               /* mov         edi,dword ptr [esp+8]  */ \
_LINE2( 0x33,0xC0 )                                         /* xor eax,eax */ \
_LINE4( 0x8B,0x4C,0x24,0x0C )                               /* mov         ecx,dword ptr [esp+0Ch]  */ \
_LINE6( 0xF7,0xC1,0x01,0x00,0x00,0x00 )                     /* test        ecx,1 */ \
_LINE2( 0x74,0x05 )                                         /* je          eee (0FB1235h) */ \
_LINE2( 0x88,0x07 )                                         /* mov         byte ptr [edi],al */ \
_LINE3( 0x83,0xC7,0x01 )                                    /* add         edi,1 */ \
_LINE2( 0xD1,0xE9 )                                         /* shr         ecx,1 */ \
_LINE6( 0xF7,0xC1,0x01,0x00,0x00,0x00 )                     /* test        ecx,1 */ \
_LINE2( 0x74,0x06 )                                         /* je          eee (0FB1235h) */ \
_LINE3( 0x66,0x89,0x07 )                                    /* mov         word ptr [edi],ax */ \
_LINE3( 0x83,0xC7,0x02 )                                    /* add         edi,2 */ \
_LINE2( 0xD1,0xE9 )                                         /* shr         ecx,1 */ \
_LINE2( 0xF3,0xAB )                                         /* rep stos    dword ptr es:[edi] */ \
_LINE1( 0x5F )                                              /* pop         edi */ \
_END_ASM

/// Очистка памяти.
/// @brief for CPUTYPE3
#define CLEANMEMSSE2_STD \
BEGIN_ASM \
_LINE1( 0x57 )                                              /* push        edi */ \
_LINE2( 0x33,0xC0 )                                         /* xor eax,eax */ \
ASM( mov edx,[esp+0x0C] ) \
ASM( mov edi,[esp+0x08] ) \
ASM( cmp edx,128 ) \
ASM( jb CLEANMEMDOWNTOSSE2 ) \
ASM( test edi,0xF ) \
ASM( jz CLEANMEMUPTOSSE2 ) \
ASM( CLEANMEMDOWNTOSSE2: ) \
ASM( mov ecx,edx) \
ASM( and edx,3 ) \
ASM( shr ecx,2 ) \
ASM( jecxz FAST1CLEANMEMSSE2 ) \
ASM( rep stos dword ptr es:[edi] ) \
ASM( FAST1CLEANMEMSSE2: ) \
ASM( mov ecx,edx ) \
ASM( jecxz FAST2CLEANMEMSSE2 ) \
ASM( rep stosb ) \
ASM( FAST2CLEANMEMSSE2: ) \
_LINE1( 0x5F )                                              /* pop         edi */ \
_LINE3( 0xC2,0x08,0x00 ) \
ASM( CLEANMEMUPTOSSE2: ) \
ASM( mov ecx,edx ) \
ASM( shr ecx,7 ) \
ASM( and edx,0x7F ) \
ASM( jecxz FAST3CLEANMEMSSE2 ) \
ASM( xorps xmm0,xmm0 ) \
ASM( xorps xmm1,xmm1 ) \
ASM( xorps xmm2,xmm2 ) \
ASM( xorps xmm3,xmm3 ) \
ASM( xorps xmm4,xmm4 ) \
ASM( xorps xmm5,xmm5 ) \
ASM( xorps xmm6,xmm6 ) \
ASM( xorps xmm7,xmm7 ) \
ASM( ssell2CLEANMEMSSE2: ) \
ASM( movaps [edi],xmm0 ) \
ASM( movaps [edi+16],xmm1 ) \
ASM( movaps [edi+32],xmm2 ) \
ASM( movaps [edi+48],xmm3 ) \
ASM( movaps [edi+64],xmm4 ) \
ASM( movaps [edi+80],xmm5 ) \
ASM( movaps [edi+96],xmm6 ) \
ASM( movaps [edi+112],xmm7 ) \
ASM( add edi,128 ) \
ASM( loop ssell2CLEANMEMSSE2 ) \
ASM( FAST3CLEANMEMSSE2: ) \
ASM( mov ecx,edx ) \
ASM( shr ecx,2 ) \
ASM( and edx,3 ) \
ASM( jecxz FAST4CLEANMEMSSE2 ) \
ASM( rep stos dword ptr es:[edi] ) \
ASM( FAST4CLEANMEMSSE2: ) \
ASM( mov ecx,edx ) \
ASM( jecxz FAST5CLEANMEMSSE2 ) \
ASM( rep stosb ) \
ASM( FAST5CLEANMEMSSE2: ) \
_LINE1( 0x5F )                                              /* pop         edi */ \
_LINE3( 0xC2,0x08,0x00 ) \
END_ASM

/// Очистка памяти.
/// @brief for CPUTYPE5
#define CLEANMEMAVX_STD \
BEGIN_ASM \
_LINE1( 0x57 )                                              /* push        edi */ \
_LINE2( 0x33,0xC0 )                                         /* xor eax,eax */ \
ASM( mov edx,[esp+0x0C] ) \
ASM( mov edi,[esp+0x08] ) \
ASM( cmp edx,128 ) \
ASM( jb CLEANMEMDOWNTOAVX ) \
ASM( test edi,0x1F ) \
ASM( jz CLEANMEMUPTOAVX ) \
ASM( CLEANMEMDOWNTOAVX: ) \
ASM( mov ecx,edx) \
ASM( and edx,3 ) \
ASM( shr ecx,2 ) \
ASM( jecxz FAST1CLEANMEMAVX ) \
ASM( rep stos dword ptr es:[edi] ) \
ASM( FAST1CLEANMEMAVX: ) \
ASM( mov ecx,edx ) \
ASM( jecxz FAST2CLEANMEMAVX ) \
ASM( rep stosb ) \
ASM( FAST2CLEANMEMAVX: ) \
_LINE1( 0x5F )                                              /* pop         edi */ \
_LINE3( 0xC2,0x08,0x00 ) \
ASM( CLEANMEMUPTOAVX: ) \
ASM( mov ecx,edx ) \
ASM( shr ecx,7 ) \
ASM( and edx,0x7F ) \
ASM( jecxz FAST3CLEANMEMAVX ) \
_LINE4( 0xC5,0xFC,0x57,0xC0 )           /* vxorps      ymm0,ymm0,ymm0  */ \
_LINE4( 0xC5,0xF4,0x57,0xC9 )           /* vxorps      ymm1,ymm1,ymm1  */ \
_LINE4( 0xC5,0xEC,0x57,0xD2 )           /* vxorps      ymm2,ymm2,ymm2  */ \
_LINE4( 0xC5,0xE4,0x57,0xDB )           /* vxorps      ymm3,ymm3,ymm3  */ \
ASM( ssell2CLEANMEMAVX: ) \
_LINE4( 0xC5,0xFC,0x29,0x07 )           /* vmovaps     ymmword ptr [edi],ymm0  */ \
_LINE5( 0xC5,0xFC,0x29,0x4F,0x20 )      /* vmovaps     ymmword ptr [edi+20h],ymm1  */ \
_LINE5( 0xC5,0xFC,0x29,0x57,0x40 )      /* vmovaps     ymmword ptr [edi+40h],ymm2  */ \
_LINE5( 0xC5,0xFC,0x29,0x5F,0x60 )      /* vmovaps     ymmword ptr [edi+60h],ymm3  */ \
ASM( add edi,128 ) \
ASM( loop ssell2CLEANMEMAVX ) \
ASM( vzeroupper ) \
ASM( FAST3CLEANMEMAVX: ) \
ASM( mov ecx,edx ) \
ASM( shr ecx,2 ) \
ASM( and edx,3 ) \
ASM( jecxz FAST4CLEANMEMAVX ) \
ASM( rep stos dword ptr es:[edi] ) \
ASM( FAST4CLEANMEMAVX: ) \
ASM( mov ecx,edx ) \
ASM( jecxz FAST5CLEANMEMAVX ) \
ASM( rep stosb ) \
ASM( FAST5CLEANMEMAVX: ) \
_LINE1( 0x5F )                                              /* pop         edi */ \
_LINE3( 0xC2,0x08,0x00 ) \
END_ASM

#endif /* GEN3_MEM_CLEAN_H_ */

