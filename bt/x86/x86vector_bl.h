//=============================================================================
///**
// *  @file vector_bl.h
// *
// *  $Id: vector_bl.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector bl conversion, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_MATH_BLVECTOR_H
#define GEN3_MATH_BLVECTOR_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** VECTORBL STDCALL *********************************
// [esp+4]-a void*, eax=[esp+8]-b void *, edx=[esp+12]-c void *

/// Вычисление поворота вектора и длинны одинарной точности, команды FPU.
#define VECTORP3DTOBLHFPU_STD \
BEGIN_ASM \
ASM( mov dword ptr [esp-8],0x42652ee1 ) \
ASM( mov eax,[esp+8] ) \
ASM( mov edx,[esp+4] ) \
ASM( fld dword ptr [eax+8] ) \
ASM( fld dword ptr [eax] ) \
_LINE2(0xD9,0xF3) \
ASM( fmul dword ptr [esp-8] ) \
ASM( fstp dword ptr [edx+4] ) \
ASM( fld dword ptr [eax+4] ) \
ASM( fld dword ptr [eax] ) \
ASM( fmul st(0),st(0) ) \
ASM( fld dword ptr [eax+8] ) \
ASM( fmul st(0),st(0) ) \
ASM( faddp st(1),st(0) ) \
ASM( fld st(0) ) \
ASM( fld st(2) ) \
ASM( fmul st(0),st(0) ) \
ASM( faddp st(1),st(0) ) \
ASM( fsqrt ) \
ASM( fstp qword ptr [edx+8] ) \
ASM( fsqrt ) \
_LINE2(0xD9,0xF3) \
ASM( fmul dword ptr [esp-8] ) \
ASM( fstp dword ptr [edx] ) \
END_ASM

/// Вычисление поворота вектора и длинны двойной точности, команды FPU.
#define VECTORP3DDTOBLHFPU_STD \
BEGIN_ASM \
ASM( mov dword ptr [esp-12],0x1a63c1f8 ) \
ASM( mov dword ptr [esp-8],0x404ca5dc ) \
ASM( mov eax,[esp+8] ) \
ASM( mov edx,[esp+4] ) \
ASM( fld qword ptr [eax+16] ) \
ASM( fld qword ptr [eax] ) \
_LINE2(0xD9,0xF3) \
ASM( fmul qword ptr [esp-12] ) \
ASM( fstp qword ptr [edx+8] ) \
ASM( fld qword ptr [eax+8] ) \
ASM( fld qword ptr [eax] ) \
ASM( fmul st(0),st(0) ) \
ASM( fld qword ptr [eax+16] ) \
ASM( fmul st(0),st(0) ) \
ASM( faddp st(1),st(0) ) \
ASM( fld st(0) ) \
ASM( fld st(2) ) \
ASM( fmul st(0),st(0) ) \
ASM( faddp st(1),st(0) ) \
ASM( fsqrt ) \
ASM( fstp qword ptr [edx+16] ) \
ASM( fsqrt ) \
_LINE2(0xD9,0xF3) \
ASM( fmul qword ptr [esp-12] ) \
ASM( fstp qword ptr [edx] ) \
END_ASM

/// Вычисление поворота вектора одинарной точности, команды FPU.
#define VECTORP3DTOBLFPU_STD \
BEGIN_ASM \
ASM( mov dword ptr [esp-8],0x42652ee1 ) \
ASM( mov eax,[esp+12] ) \
ASM( mov edx,[esp+8] ) \
ASM( fld dword ptr [eax+8] ) \
ASM( fld dword ptr [eax] ) \
_LINE2(0xD9,0xF3) \
ASM( fmul dword ptr [esp-8] ) \
ASM( fstp dword ptr [edx] ) \
ASM( fld dword ptr [eax+4] ) \
ASM( fld dword ptr [eax] ) \
ASM( fmul st(0),st(0) ) \
ASM( fld dword ptr [eax+8] ) \
ASM( fmul st(0),st(0) ) \
ASM( faddp st(1),st(0) ) \
ASM( mov edx,[esp+4] ) \
ASM( fsqrt ) \
_LINE2(0xD9,0xF3) \
ASM( fmul dword ptr [esp-8] ) \
ASM( fstp dword ptr [edx] ) \
END_ASM

/// Вычисление поворота вектора двойной точности, команды FPU.
#define VECTORP3DDTOBLFPU_STD \
BEGIN_ASM \
ASM( mov dword ptr [esp-12],0x1a63c1f8 ) \
ASM( mov dword ptr [esp-8],0x404ca5dc ) \
ASM( mov eax,[esp+12] ) \
ASM( mov edx,[esp+8] ) \
ASM( fld qword ptr [eax+16] ) \
ASM( fld qword ptr [eax] ) \
_LINE2(0xD9,0xF3) \
ASM( fmul qword ptr [esp-12] ) \
ASM( fstp qword ptr [edx] ) \
ASM( fld qword ptr [eax+8] ) \
ASM( fld qword ptr [eax] ) \
ASM( fmul st(0),st(0) ) \
ASM( fld qword ptr [eax+16] ) \
ASM( fmul st(0),st(0) ) \
ASM( faddp st(1),st(0) ) \
ASM( mov edx,[esp+4] ) \
ASM( fsqrt ) \
_LINE2(0xD9,0xF3) \
ASM( fmul qword ptr [esp-12] ) \
ASM( fstp qword ptr [edx] ) \
END_ASM

#endif
