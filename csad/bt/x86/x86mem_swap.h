//=============================================================================
///**
// *  @file   mem_swap.h
// *
// *  $Id: mem_swap.h 16.10.2011  $
// *
// *  @brief generator 3, assembler memory operations, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_MEM_SWAP_H_
#define GEN3_MEM_SWAP_H_

//**************************** SWAPMEM STACK STDCALL *********************************
// vector cross product edi=[esp+8]-a void * esi=[esp+4]-b void * ecx=[esp+12]-c int

/// Копирование памяти.
/// @brief for CPUTYPE1
#define SWAPMEMCPU_STD \
BEGIN_ASM \
ASM( push edi ) \
ASM( push esi ) \
ASM( mov ecx,[esp+0x14] ) \
ASM( mov esi,[esp+0x0C] ) \
ASM( mov edx,ecx ) \
ASM( mov edi,[esp+0x10] ) \
ASM( shr ecx,2 ) \
ASM( and edx,3 ) \
ASM( jecxz ZLSM1 ) \
ASM( ZLSM3: ) \
ASM( mov eax,[edi] ) \
ASM( movs dword ptr es:[edi],dword ptr [esi] ) \
ASM( mov [esi-4],eax ) \
ASM( loop ZLSM3 ) \
ASM( ZLSM1: ) \
ASM( mov ecx,edx ) \
ASM( jecxz ZLSM2 ) \
ASM( ZLSM4: ) \
ASM( mov al,[edi] ) \
ASM( movsb ) \
ASM( mov [esi-1],al ) \
ASM( loop ZLSM4 ) \
ASM( ZLSM2: ) \
ASM( pop esi ) \
ASM( pop edi ) \
END_ASM

#endif /* GEN3_MEM_SWAP_H_ */