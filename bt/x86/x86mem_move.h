//=============================================================================
///**
// *  @file   mem_move.h
// *
// *  $Id: mem_move.h 16.10.2011  $
// *
// *  @brief generator 3, assembler memory operations, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_MEM_MOVE_H_
#define GEN3_MEM_MOVE_H_

//**************************** MOVEMEM STACK STDCALL *********************************
// vector cross product edi=[esp+8]-a void * esi=[esp+4]-b void * ecx=[esp+12]-c int

/// Копирование памяти.
/// @brief for CPUTYPE1
#define MOVEMEMCPU_STD \
BEGIN_ASM \
ASM( push edi ) \
ASM( push esi ) \
ASM( mov ecx,[esp+0x14] ) \
ASM( mov esi,[esp+0x0C] ) \
ASM( mov edx,ecx ) \
ASM( mov edi,[esp+0x10] ) \
ASM( shr ecx,2 ) \
ASM( and edx,3 ) \
ASM( jecxz ZLMM1 ) \
ASM( rep movs dword ptr es:[edi],dword ptr [esi] ) \
ASM( ZLMM1: ) \
ASM( mov ecx,edx ) \
ASM( jecxz ZLMM2 ) \
ASM( rep movsb ) \
ASM( ZLMM2: ) \
ASM( pop esi ) \
ASM( pop edi ) \
END_ASM

/// Копирование памяти.
/// @brief for CPUTYPE3
#define MOVEMEMSSE2_STD \
BEGIN_ASM \
ASM( push edi ) \
ASM( push esi ) \
ASM( mov edx,[esp+0x14] ) \
ASM( mov esi,[esp+0x0C] ) \
ASM( mov edi,[esp+0x10] ) \
ASM( cmp edx,128 ) \
ASM( jb DOWNTOSSE2 ) \
ASM( test esi,0xF ) \
ASM( jnz DOWNTOSSE2 ) \
ASM( test edi,0xF ) \
ASM( jnz DOWNTOSSE2 ) \
ASM( jmp UPTOSSE2 ) \
ASM( DOWNTOSSE2: ) \
ASM( mov ecx,edx) \
ASM( and edx,3 ) \
ASM( shr ecx,2 ) \
ASM( jecxz FAST1MOVEMEMSSE2 ) \
ASM( rep movs dword ptr es:[edi],dword ptr [esi] ) \
ASM( FAST1MOVEMEMSSE2: ) \
ASM( mov ecx,edx ) \
ASM( jecxz FAST2MOVEMEMSSE2 ) \
ASM( rep movsb ) \
ASM( FAST2MOVEMEMSSE2: ) \
ASM( pop esi ) \
ASM( pop edi ) \
_LINE3( 0xC2,0x0C,0x00 ) \
ASM( UPTOSSE2: ) \
ASM( mov ecx,edx ) \
ASM( shr ecx,7 ) \
ASM( and edx,0x7F ) \
ASM( jecxz FAST3MOVEMEMSSE2 ) \
ASM( ssell2MOVEMEMSSE2: ) \
ASM( movaps xmm0,[esi] ) \
ASM( movaps xmm1,[esi+16] ) \
ASM( movaps xmm2,[esi+32] ) \
ASM( movaps xmm3,[esi+48] ) \
ASM( movaps xmm4,[esi+64] ) \
ASM( movaps xmm5,[esi+80] ) \
ASM( movaps xmm6,[esi+96] ) \
ASM( movaps xmm7,[esi+112] ) \
ASM( movaps [edi],xmm0 ) \
ASM( movaps [edi+16],xmm1 ) \
ASM( movaps [edi+32],xmm2 ) \
ASM( movaps [edi+48],xmm3 ) \
ASM( movaps [edi+64],xmm4 ) \
ASM( movaps [edi+80],xmm5 ) \
ASM( movaps [edi+96],xmm6 ) \
ASM( movaps [edi+112],xmm7 ) \
ASM( add esi,128 ) \
ASM( add edi,128 ) \
ASM( loop ssell2MOVEMEMSSE2 ) \
ASM( FAST3MOVEMEMSSE2: ) \
ASM( mov ecx,edx ) \
ASM( shr ecx,2 ) \
ASM( and edx,3 ) \
ASM( jecxz FAST4MOVEMEMSSE2 ) \
ASM( rep movs dword ptr es:[edi],dword ptr [esi] ) \
ASM( FAST4MOVEMEMSSE2: ) \
ASM( mov ecx,edx ) \
ASM( jecxz FAST5MOVEMEMSSE2 ) \
ASM( rep movsb ) \
ASM( FAST5MOVEMEMSSE2: ) \
ASM( pop esi ) \
ASM( pop edi ) \
_LINE3( 0xC2,0x0C,0x00 ) \
END_ASM

/// Копирование памяти.
/// @brief for CPUTYPE4
#define MOVEMEMAVX_STD \
BEGIN_ASM \
ASM( push edi ) \
ASM( push esi ) \
ASM( mov edx,[esp+0x14] ) \
ASM( mov esi,[esp+0x0C] ) \
ASM( mov edi,[esp+0x10] ) \
ASM( cmp edx,128 ) \
ASM( jb DOWNTOAVX ) \
ASM( test esi,0xF ) \
ASM( jnz DOWNTOAVX ) \
ASM( test edi,0xF ) \
ASM( jnz DOWNTOAVX ) \
ASM( test esi,0x1F ) \
ASM( jnz UPTOSSEAVX ) \
ASM( test edi,0x1F ) \
ASM( jnz UPTOSSEAVX ) \
ASM( jmp UPTOAVX ) \
ASM( DOWNTOAVX: ) \
ASM( mov ecx,edx) \
ASM( and edx,3 ) \
ASM( shr ecx,2 ) \
ASM( jecxz FAST1MOVEMEMAVX ) \
ASM( rep movs dword ptr es:[edi],dword ptr [esi] ) \
ASM( FAST1MOVEMEMAVX: ) \
ASM( mov ecx,edx ) \
ASM( jecxz FAST2MOVEMEMAVX ) \
ASM( rep movsb ) \
ASM( FAST2MOVEMEMAVX: ) \
ASM( pop esi ) \
ASM( pop edi ) \
_LINE3( 0xC2,0x0C,0x00 ) \
ASM( UPTOSSEAVX: ) \
ASM( mov ecx,edx ) \
ASM( shr ecx,7 ) \
ASM( and edx,0x7F ) \
ASM( jecxz FAST8MOVEMEMAVX ) \
ASM( ssell2MOVEMEMAVX: ) \
ASM( movaps xmm0,[esi] ) \
ASM( movaps xmm1,[esi+16] ) \
ASM( movaps xmm2,[esi+32] ) \
ASM( movaps xmm3,[esi+48] ) \
ASM( movaps xmm4,[esi+64] ) \
ASM( movaps xmm5,[esi+80] ) \
ASM( movaps xmm6,[esi+96] ) \
ASM( movaps xmm7,[esi+112] ) \
ASM( movaps [edi],xmm0 ) \
ASM( movaps [edi+16],xmm1 ) \
ASM( movaps [edi+32],xmm2 ) \
ASM( movaps [edi+48],xmm3 ) \
ASM( movaps [edi+64],xmm4 ) \
ASM( movaps [edi+80],xmm5 ) \
ASM( movaps [edi+96],xmm6 ) \
ASM( movaps [edi+112],xmm7 ) \
ASM( add esi,128 ) \
ASM( add edi,128 ) \
ASM( loop ssell2MOVEMEMAVX ) \
ASM( FAST8MOVEMEMAVX: ) \
ASM( jmp FAST3MOVEMEMAVX ) \
ASM( UPTOAVX: ) \
ASM( mov ecx,edx ) \
ASM( shr ecx,7 ) \
ASM( and edx,0x7F ) \
ASM( jecxz FAST3MOVEMEMAVX ) \
ASM( avxll2MOVEMEMAVX: ) \
_LINE4( 0xC5,0xFC,0x28,0x06 )           /* vmovaps     ymm0,ymmword ptr [esi]  */ \
_LINE5( 0xC5,0xFC,0x28,0x4E,0x20 )      /* vmovaps     ymm1,ymmword ptr [esi+20h]  */ \
_LINE5( 0xC5,0xFC,0x28,0x56,0x40 )      /* vmovaps     ymm2,ymmword ptr [esi+40h]  */ \
_LINE5( 0xC5,0xFC,0x28,0x5E,0x60 )      /* vmovaps     ymm3,ymmword ptr [esi+60h]  */ \
_LINE4( 0xC5,0xFC,0x29,0x07 )           /* vmovaps     ymmword ptr [edi],ymm0  */ \
_LINE5( 0xC5,0xFC,0x29,0x4F,0x20 )      /* vmovaps     ymmword ptr [edi+20h],ymm1  */ \
_LINE5( 0xC5,0xFC,0x29,0x57,0x40 )      /* vmovaps     ymmword ptr [edi+40h],ymm2  */ \
_LINE5( 0xC5,0xFC,0x29,0x5F,0x60 )      /* vmovaps     ymmword ptr [edi+60h],ymm3  */ \
ASM( add esi,128 ) \
ASM( add edi,128 ) \
ASM( loop avxll2MOVEMEMAVX ) \
ASM( vzeroupper ) \
ASM( FAST3MOVEMEMAVX: ) \
ASM( mov ecx,edx ) \
ASM( shr ecx,2 ) \
ASM( and edx,3 ) \
ASM( jecxz FAST4MOVEMEMAVX ) \
ASM( rep movs dword ptr es:[edi],dword ptr [esi] ) \
ASM( FAST4MOVEMEMAVX: ) \
ASM( mov ecx,edx ) \
ASM( jecxz FAST5MOVEMEMAVX ) \
ASM( rep movsb ) \
ASM( FAST5MOVEMEMAVX: ) \
ASM( pop esi ) \
ASM( pop edi ) \
_LINE3( 0xC2,0x0C,0x00 ) \
END_ASM

/// Копирование памяти задом на перед.
/// @brief for CPUTYPE1
#define MOVEBACKCPU_STD \
BEGIN_ASM \
ASM( push edi ) \
ASM( push esi ) \
ASM( mov ecx,[esp+0x14] ) \
ASM( mov esi,[esp+0x0C] ) \
ASM( mov edx,ecx ) \
ASM( mov edi,[esp+0x10] ) \
ASM( add esi,ecx ) \
ASM( add edi,edx ) \
ASM( std ) \
ASM( shr ecx,2 ) \
ASM( and edx,3 ) \
ASM( jecxz ZLMB1 ) \
ASM( sub esi,4 ) \
ASM( sub edi,4 ) \
ASM( rep movs dword ptr es:[edi],dword ptr [esi] ) \
ASM( add esi,4 ) \
ASM( add edi,4 ) \
ASM( ZLMB1: ) \
ASM( mov ecx,edx ) \
ASM( jecxz ZLMB2 ) \
ASM( dec esi ) \
ASM( dec edi ) \
ASM( rep movsb ) \
ASM( ZLMB2: ) \
ASM( cld ) \
ASM( pop esi ) \
ASM( pop edi ) \
END_ASM

/// Копирование памяти задом на перед.
/// @brief for CPUTYPE3
#define MOVEBACKSSE2_STD \
BEGIN_ASM \
ASM( push edi ) \
ASM( push esi ) \
ASM( mov edx,[esp+0x14] ) \
ASM( mov esi,[esp+0x0C] ) \
ASM( mov edi,[esp+0x10] ) \
ASM( cmp edx,128 ) \
ASM( jb DOWNTOBACKSSE2 ) \
ASM( test esi,0xF ) \
ASM( jnz DOWNTOBACKSSE2 ) \
ASM( test edi,0xF ) \
ASM( jnz DOWNTOBACKSSE2 ) \
ASM( jmp UPTOBACKSSE2 ) \
ASM( DOWNTOBACKSSE2: ) \
ASM( mov ecx,edx) \
ASM( add esi,ecx ) \
ASM( add edi,edx ) \
ASM( std ) \
ASM( and edx,3 ) \
ASM( shr ecx,2 ) \
ASM( jecxz FAST1MOVEBACKSSE2 ) \
ASM( sub esi,4 ) \
ASM( sub edi,4 ) \
ASM( rep movs dword ptr es:[edi],dword ptr [esi] ) \
ASM( add esi,4 ) \
ASM( add edi,4 ) \
ASM( FAST1MOVEBACKSSE2: ) \
ASM( mov ecx,edx ) \
ASM( jecxz FAST2MOVEBACKSSE2 ) \
ASM( dec esi ) \
ASM( dec edi ) \
ASM( rep movsb ) \
ASM( FAST2MOVEBACKSSE2: ) \
ASM( cld ) \
ASM( pop esi ) \
ASM( pop edi ) \
_LINE3( 0xC2,0x0C,0x00 ) \
ASM( UPTOBACKSSE2: ) \
ASM( mov ecx,edx ) \
ASM( shr ecx,7 ) \
ASM( mov eax,ecx ) \
ASM( shl eax,7 ) \
ASM( add esi,eax ) \
ASM( add edi,eax ) \
ASM( and edx,0x7F ) \
ASM( jecxz FAST3MOVEBACKSSE2 ) \
ASM( ssell2MOVEBACKSSE2: ) \
ASM( sub esi,128 ) \
ASM( sub edi,128 ) \
ASM( movapd xmm0,[esi] ) \
ASM( movapd xmm1,[esi+16] ) \
ASM( movapd xmm2,[esi+32] ) \
ASM( movapd xmm3,[esi+48] ) \
ASM( movapd xmm4,[esi+64] ) \
ASM( movapd xmm5,[esi+80] ) \
ASM( movapd xmm6,[esi+96] ) \
ASM( movapd xmm7,[esi+112] ) \
ASM( movapd [edi],xmm0 ) \
ASM( movapd [edi+16],xmm1 ) \
ASM( movapd [edi+32],xmm2 ) \
ASM( movapd [edi+48],xmm3 ) \
ASM( movapd [edi+64],xmm4 ) \
ASM( movapd [edi+80],xmm5 ) \
ASM( movapd [edi+96],xmm6 ) \
ASM( movapd [edi+112],xmm7 ) \
ASM( loop ssell2MOVEBACKSSE2 ) \
ASM( FAST3MOVEBACKSSE2: ) \
ASM( mov ecx,edx ) \
ASM( shr ecx,2 ) \
ASM( and edx,3 ) \
ASM( std ) \
ASM( jecxz FAST4MOVEBACKSSE2 ) \
ASM( sub esi,4 ) \
ASM( sub edi,4 ) \
ASM( rep movs dword ptr es:[edi],dword ptr [esi] ) \
ASM( add esi,4 ) \
ASM( add edi,4 ) \
ASM( FAST4MOVEBACKSSE2: ) \
ASM( mov ecx,edx ) \
ASM( jecxz FAST5MOVEBACKSSE2 ) \
ASM( dec esi ) \
ASM( dec edi ) \
ASM( rep movsb ) \
ASM( FAST5MOVEBACKSSE2: ) \
ASM( cld ) \
ASM( pop esi ) \
ASM( pop edi ) \
_LINE3( 0xC2,0x0C,0x00 ) \
END_ASM

//**************************** MOVEMEM REGISTER FASTCALL *********************************
// addition vectors eax-a void *, edx-b void *, ecx-c int

#define MOVEMEMCORRECTBYEDI(spec_id) \
ASM( mov edi,eax) \
ASM( mov esi,edx) \
ASM( shl eax,8) \
ASM( sub al,ah) \
ASM( mov edx,ecx) \
ASM( and eax,0xF) \
ASM( sub edx,eax) \
ASM( jae spec_id##ZLMM3A1) \
ASM( add edx,eax) \
ASM( jmp spec_id##ZLMM3) \
ASM( spec_id##ZLMM3A1:) \
ASM( mov ecx,eax) \
ASM( jecxz spec_id##ZLMM3) \
ASM( rep movsb) \
ASM( spec_id##ZLMM3:) \
ASM( mov ecx,edx)

#define MOVEME128MOVUPD_MOVAPD  \
ASM( movupd xmm0,[esi]) \
ASM( movupd xmm1,[esi+16]) \
ASM( movupd xmm2,[esi+32]) \
ASM( movupd xmm3,[esi+48]) \
ASM( movupd xmm4,[esi+64]) \
ASM( movupd xmm5,[esi+80]) \
ASM( movupd xmm6,[esi+96]) \
ASM( movupd xmm7,[esi+112]) \
ASM( movapd [edi],xmm0) \
ASM( movapd [edi+16],xmm1) \
ASM( movapd [edi+32],xmm2) \
ASM( movapd [edi+48],xmm3) \
ASM( movapd [edi+64],xmm4) \
ASM( movapd [edi+80],xmm5) \
ASM( movapd [edi+96],xmm6) \
ASM( movapd [edi+112],xmm7)

#define MOVEME128LDDQU_MOVAPD  \
ASM( lddqu xmm0,[esi]) \
ASM( lddqu xmm1,[esi+16]) \
ASM( lddqu xmm2,[esi+32]) \
ASM( lddqu xmm3,[esi+48]) \
ASM( lddqu xmm4,[esi+64]) \
ASM( lddqu xmm5,[esi+80]) \
ASM( lddqu xmm6,[esi+96]) \
ASM( lddqu xmm7,[esi+112]) \
ASM( movapd [edi],xmm0) \
ASM( movapd [edi+16],xmm1) \
ASM( movapd [edi+32],xmm2) \
ASM( movapd [edi+48],xmm3) \
ASM( movapd [edi+64],xmm4) \
ASM( movapd [edi+80],xmm5) \
ASM( movapd [edi+96],xmm6) \
ASM( movapd [edi+112],xmm7)

#define MOVEME128MOVLHPS_MOVAPD  \
ASM( movsd xmm0,[esi]) \
ASM( movhps xmm0,[esi+8]) \
ASM( movsd xmm1,[esi+0x10]) \
ASM( movhps xmm1,[esi+0x18]) \
ASM( movsd xmm2,[esi+0x20]) \
ASM( movhps xmm2,[esi+0x28]) \
ASM( movsd xmm3,[esi+0x30]) \
ASM( movhps xmm3,[esi+0x38]) \
ASM( movsd xmm4,[esi+0x40]) \
ASM( movhps xmm4,[esi+0x48]) \
ASM( movsd xmm5,[esi+0x50]) \
ASM( movhps xmm5,[esi+0x58]) \
ASM( movsd xmm6,[esi+0x60]) \
ASM( movhps xmm6,[esi+0x68]) \
ASM( movsd xmm7,[esi+0x70]) \
ASM( movhps xmm7,[esi+0x78]) \
ASM( movapd [edi],xmm0) \
ASM( movapd [edi+16],xmm1) \
ASM( movapd [edi+32],xmm2) \
ASM( movapd [edi+48],xmm3) \
ASM( movapd [edi+64],xmm4) \
ASM( movapd [edi+80],xmm5) \
ASM( movapd [edi+96],xmm6) \
ASM( movapd [edi+112],xmm7)

#define MOVEME128MOVDQU_MOVNTDQ  \
ASM( movdqu xmm0,[esi]) \
ASM( movdqu xmm1,[esi+16]) \
ASM( movdqu xmm2,[esi+32]) \
ASM( movdqu xmm3,[esi+48]) \
ASM( movdqu xmm4,[esi+64]) \
ASM( movdqu xmm5,[esi+80]) \
ASM( movdqu xmm6,[esi+96]) \
ASM( movdqu xmm7,[esi+112]) \
ASM( movntdq [edi],xmm0) \
ASM( movntdq [edi+16],xmm1) \
ASM( movntdq [edi+32],xmm2) \
ASM( movntdq [edi+48],xmm3) \
ASM( movntdq [edi+64],xmm4) \
ASM( movntdq [edi+80],xmm5) \
ASM( movntdq [edi+96],xmm6) \
ASM( movntdq [edi+112],xmm7)

#define MOVEME128MOVAPD_MOVAPD  \
ASM( movapd xmm0,[esi]) \
ASM( movapd xmm1,[esi+16]) \
ASM( movapd xmm2,[esi+32]) \
ASM( movapd xmm3,[esi+48]) \
ASM( movapd xmm4,[esi+64]) \
ASM( movapd xmm5,[esi+80]) \
ASM( movapd xmm6,[esi+96]) \
ASM( movapd xmm7,[esi+112]) \
ASM( movapd [edi],xmm0) \
ASM( movapd [edi+16],xmm1) \
ASM( movapd [edi+32],xmm2) \
ASM( movapd [edi+48],xmm3) \
ASM( movapd [edi+64],xmm4) \
ASM( movapd [edi+80],xmm5) \
ASM( movapd [edi+96],xmm6) \
ASM( movapd [edi+112],xmm7)

/// Копирование памяти.
/// @brief for CPUTYPE4
#define MOVEMEMSSE3 \
BEGIN_ASM \
MOVEMEMCORRECTBYEDI(MOVEMEMSSE3) \
ASM( shr ecx,7) \
ASM( prefetchnta [esi]) \
ASM( test esi,0x0F) \
ASM( jz FAST1MOVEMEMSSE3) \
ASM( jecxz ZLMM1MOVEMEMSSE3) \
ASM( ssell1MOVEMEMSSE3:) \
MOVEME128LDDQU_MOVAPD \
ASM( add esi,128) \
ASM( add edi,128) \
ASM( loop ssell1MOVEMEMSSE3) \
ASM( ZLMM1MOVEMEMSSE3:) \
ASM( jmp FAST2MOVEMEMSSE3) \
ASM( FAST1MOVEMEMSSE3:) \
ASM( jecxz ZLMM4MOVEMEMSSE3) \
ASM( ssell2MOVEMEMSSE3:) \
MOVEME128MOVAPD_MOVAPD \
ASM( add esi,128) \
ASM( add edi,128) \
ASM( loop ssell2MOVEMEMSSE3) \
ASM( ZLMM4MOVEMEMSSE3:) \
ASM( FAST2MOVEMEMSSE3:) \
ASM( and edx,0x7F) \
ASM( mov ecx,edx) \
ASM( jecxz ZLMM2MOVEMEMSSE3) \
ASM( rep movsb) \
ASM( ZLMM2MOVEMEMSSE3:) \
END_ASM

#endif /* GEN3_MEM_MOVE_H_ */
