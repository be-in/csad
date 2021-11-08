//=============================================================================
///**
// *  @file   macrosasm.h
// *
// *  $Id: macrosasm.h 04.05.2011  $
// *
// *  @brief macro commands, MS Visual C++ 2008-2010; GNU C/C++;
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#pragma once

#include <bt/macroscpu.h>

///*
// *  **************  Конструктор ассемблера **************
// *
// *  BEGIN_ASM - начало ассеблерной вставки
// *
// *  END_ASM - конец ассеблерной вставки
// *
// *  _ASM - комманда на ассемблере, используется синтаксис Intel
// *         пример: _ASM add eax,ecx;
// *
// *  _LINE(0xCOD, ... ) - директива ввода строки в машинных кодах
// *
// *  SAVE_X_PARAMETERS - сохраняет в неиспользуемой области стека регистры последовательностью:
// *                      eax, edx, ecx, edi, esi, ebx, ebp.
// *                      не изменяет значение ESP.
// *
// *  LOAD_X_PARAMETERS - востанавливает из неиспользуемой области стека регистры последовательностью:
// *                      eax, edx, ecx, edi, esi, ebx, ebp.
// *                      в случае использования вложенных вызывов call или push/pop может привести к неопределенным результатам.
// *                      используется только после SAVE_X_PARAMETERS.
// *
// *  PARAMETERS_?? - директива загрузки парамтров из стека в регистры последовательностью:
// *                  eax, edx, ecx, edi, esi, ebx, ebp.
// *
// *  PARAMETERS_FASTCALL_CPP_?? - директива загрузки парамтров для быстрого вызова из стека в регистры последовательностью:
// *                   ecx, edx, eax, edi, esi, ebx, ebp.
// *
// *
// *
// */

//******************************************** Microsoft Visual C++ ****************************************
#ifdef _MSC_VER
#ifndef MSVC
#define MSVC
#endif

#ifdef CPU_X86_32
#define _BEGIN_ASM
#define _END_ASM
#define BEGIN_ASM __asm {
#define END_ASM }
#define _DB(a) __asm _emit a
#define _STR(a) a
#define _ASM __asm
#define ASM(...) __asm __VA_ARGS__

//----------
#define START_ASM __asm {
#define LINE_ASM(a) a
#define LINE_ASM2(a,b) a,b
#define FINISH_ASM }
#else
#define _BEGIN_ASM
#define _END_ASM
#define BEGIN_ASM
#define END_ASM
#define _DB(a)
#define _STR(a)
#define _ASM
#define ASM(...)
#endif

#endif

//******************************************** GNU C/C++ ***************************************************
#ifdef __GNUC__
#ifndef GCC
#define GCC
#endif

#define _BEGIN_ASM asm ( ".intel_syntax noprefix \n\t"
#define _END_ASM ".att_syntax prefix\n\t" );
#define BEGIN_ASM asm ( ".intel_syntax noprefix \n\t"
#define END_ASM ".att_syntax prefix\n\t" ::: );
#define _DB(a) ".byte "#a"; "
#define _STR(a) a" \n\t"
#define _ASM \n\t
#define ASM(...) #__VA_ARGS__"; \n\t"

//----------
#define START_ASM asm (".intel_syntax noprefix \n"
#define LINE_ASM(a) #a" \n"
#define LINE_ASM2(a,b) #a","#b" \n"
#define FINISH_ASM ".att_syntax prefix");

#endif

//******************************************** Borland C++ ***************************************************
#ifdef __BORLANDC__
#ifndef BORLAND
#define BORLAND
#endif

#endif

//******************************************** Intel C++ *****************************************************
#ifdef __INTEL_COMPILER
#ifndef INTEL
#define INTEL
#endif

#endif

//******************************************** MinGW **********************************************************
#ifdef __MINGW32__
#ifndef MINGW
#define MINGW
#endif

#endif

#ifndef NULL
#define NULL 0
#endif

#define _STACKFREE 36

#define EXEC_ASM(a)  START_ASM LINE_ASM(a)   FINISH_ASM
#define EXEC_ASM2(a,b) START_ASM LINE_ASM2(a,b) FINISH_ASM

#define _LINE1(a1) _STR( _DB(a1) )
#define _LINE2(a1,a2) _STR( _DB(a1) _DB(a2) )
#define _LINE3(a1,a2,a3) _STR( _DB(a1) _DB(a2) _DB(a3) )
#define _LINE4(a1,a2,a3,a4) _STR( _DB(a1) _DB(a2) _DB(a3) _DB(a4) )
#define _LINE5(a1,a2,a3,a4,a5) _STR( _DB(a1) _DB(a2) _DB(a3) _DB(a4) _DB(a5) )
#define _LINE6(a1,a2,a3,a4,a5,a6) _STR( _DB(a1) _DB(a2) _DB(a3) _DB(a4) _DB(a5) _DB(a6) )
#define _LINE7(a1,a2,a3,a4,a5,a6,a7) _STR( _DB(a1) _DB(a2) _DB(a3) _DB(a4) _DB(a5) _DB(a6) _DB(a7) )
#define _LINE8(a1,a2,a3,a4,a5,a6,a7,a8) _STR( _DB(a1) _DB(a2) _DB(a3) _DB(a4) _DB(a5) _DB(a6) _DB(a7) _DB(a8) )

#define PARAMETERS_ESP_2_EDI BEGIN_ASM _LINE4(0x8B,0x7C,0x24,0x08) END_ASM

// преобразования параметров для быстрого вызова
#define PARAMETERS_FASTCALL_ESP_VOID _BEGIN_ASM _LINE2(0x8B,0xC2) _END_ASM
#define PARAMETERS_FASTCALL_ESP_VOID_VOID _BEGIN_ASM _LINE2(0x8B,0xC2) _LINE2(0x8B,0xD1) _END_ASM
#define PARAMETERS_FASTCALL_ESP_VOID_VOID_VOID _BEGIN_ASM _LINE2(0x8B,0xC1) _LINE4(0x8B,0x4C,0x24,0x04) _END_ASM

#define PARAMETERS_FASTCALL_ESP_VOID_VOID_DATA32 _BEGIN_ASM _LINE2(0x8B,0xC1) _LINE4(0x8D,0x4C,0x24,0x04) _END_ASM
#define PARAMETERS_FASTCALL_ESP_VOID_VOID_DATA64 _BEGIN_ASM _LINE2(0x8B,0xC1) _LINE4(0x8D,0x4C,0x24,0x04) _END_ASM

// заметка: для быстрого вызова по стандарту, без преобразования, увеличение производительности на 50%
#define PARAMETERS_FASTCALL_CPP_ESP_VOID
#define PARAMETERS_FASTCALL_CPP_ESP_VOID_VOID
#define PARAMETERS_FASTCALL_CPP_ESP_VOID_VOID_VOID _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0x04) _END_ASM

#define PARAMETERS_FASTCALL_CPP_ESP_VOID_VOID_DATA32 _BEGIN_ASM _LINE4(0x8D,0x44,0x24,0x04) _END_ASM
#define PARAMETERS_FASTCALL_CPP_ESP_VOID_VOID_DATA64 _BEGIN_ASM _LINE4(0x8D,0x44,0x24,0x04) _END_ASM

/// по стандарту STDCALL параметры передаются через стек с использованием регистра ESP, загружаются в регистры EAX EDX ECX EDI ESI EBX, оптимизация передачи параметров должна быть включена, рекомендуется #pragma optimize( "gtp", on )
#define PARAMETERS_ESP_VOID_VOID_VOID_VOID_VOID_VOID _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0x04) _LINE4(0x8B,0x54,0x24,0x08) _LINE4(0x8B,0x4C,0x24,0x0C) _LINE4(0x8B,0x7C,0x24,0x10) _LINE4(0x8B,0x74,0x24,0x14) _LINE4(0x8B,0x5C,0x24,0x18) _END_ASM
/// по стандарту STDCALL параметры передаются через стек с использованием регистра ESP, загружаются в регистры EAX EDX ECX, оптимизация передачи параметров должна быть включена, рекомендуется #pragma optimize( "gtp", on )
#define PARAMETERS_ESP_VOID_VOID_VOID _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0x04) _LINE4(0x8B,0x54,0x24,0x08) _LINE4(0x8B,0x4C,0x24,0x0C) _END_ASM
/// по стандарту STDCALL параметры передаются через стек с использованием регистра ESP, загружаются в регистры EDX EAX ECX, оптимизация передачи параметров должна быть включена, рекомендуется #pragma optimize( "gtp", on )
#define PARAMETERS_ESP_EDX_EAX_ECX _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0x08) _LINE4(0x8B,0x54,0x24,0x04) _LINE4(0x8B,0x4C,0x24,0x0C) _END_ASM
/// по стандарту STDCALL параметры передаются через стек с использованием регистра ESP, загружаются в регистры EAX EDX, оптимизация передачи параметров должна быть включена, рекомендуется #pragma optimize( "gtp", on )
#define PARAMETERS_ESP_VOID_VOID _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0x04) _LINE4(0x8B,0x54,0x24,0x08) _END_ASM
/// по стандарту STDCALL параметры передаются через стек с использованием регистра ESP, загружаются в регистры EAX, оптимизация передачи параметров должна быть включена, рекомендуется #pragma optimize( "gtp", on )
#define PARAMETERS_ESP_VOID _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0x04) _END_ASM
///
#define PARAMETERS_ESP_VOID_VOID_DATA32 _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0x04) _LINE4(0x8B,0x54,0x24,0x08) _LINE4(0x8D,0x4C,0x24,0x0C) _END_ASM
///
#define PARAMETERS_ESP_VOID_VOID_VOID_DATA32 _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0x04) _LINE4(0x8B,0x54,0x24,0x08) _LINE4(0x8B,0x4C,0x24,0x0C) _LINE4(0x8D,0x7C,0x24,0x10) _END_ASM
///
#define PARAMETERS_ESP_VOID_VOID_DATA32_VOID_VOID_VOID _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0x04) _STR(_DB(0x8B) _DB(0x54) _DB(0x24) _DB(0x08)) _STR(_DB(0x8D) _DB(0x4C) _DB(0x24) _DB(0x0C)) _STR(_DB(0x8B) _DB(0x7C) _DB(0x24) _DB(0x10)) _STR(_DB(0x8B) _DB(0x74) _DB(0x24) _DB(0x14)) _STR(_DB(0x8B) _DB(0x5C) _DB(0x24) _DB(0x18)) _END_ASM
///
#define PARAMETERS_ESP_VOID_VOID_VOID_DATA32_DATA32 _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0x04) _LINE4(0x8B,0x54,0x24,0x08) _LINE4(0x8B,0x4C,0x24,0x0C) _LINE4(0x8D,0x7C,0x24,0x10) _LINE4(0x8D,0x74,0x24,0x14) _END_ASM
///
#define PARAMETERS_ESP_VOID_VOID_DATA64 _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0x04) _STR(_DB(0x8B) _DB(0x54) _DB(0x24) _DB(0x08)) _STR(_DB(0x8D) _DB(0x4C) _DB(0x24) _DB(0x0C)) _END_ASM
///
#define PARAMETERS_ESP_VOID_VOID_VOID_DATA64 _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0x04) _LINE4(0x8B,0x54,0x24,0x08) _LINE4(0x8B,0x4C,0x24,0x0C) _LINE4(0x8D,0x7C,0x24,0x10) _END_ASM
///
#define PARAMETERS_ESP_VOID_VOID_DATA64_VOID_VOID_VOID _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0x04) _STR(_DB(0x8B) _DB(0x54) _DB(0x24) _DB(0x08)) _LINE4(0x8D,0x4C,0x24,0x0C) _STR(_DB(0x8B) _DB(0x7C) _DB(0x24) _DB(0x14)) _STR(_DB(0x8B) _DB(0x74) _DB(0x24) _DB(0x18)) _STR(_DB(0x8B) _DB(0x5C) _DB(0x24) _DB(0x1C)) _END_ASM
///
#define PARAMETERS_ESP_VOID_VOID_VOID_DATA64_DATA64 _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0x04) _LINE4(0x8B,0x54,0x24,0x08) _LINE4(0x8B,0x4C,0x24,0x0C) _LINE4(0x8D,0x7C,0x24,0x10) _LINE4(0x8D,0x74,0x24,0x18) _END_ASM

/// по стандарту STDCALL параметры передаются через стек с использованием регистра EBP, загружаются в регистры EAX EDX ECX, необходимо учитывать директивы компиляции с отключенной оптимизацией, рекомендуется #pragma optimize( "gtpy", off ) или #pragma optimize( "", off )
#define PARAMETERS_VOID_VOID_VOID _BEGIN_ASM _STR(_DB(0x8B) _DB(0x4D) _DB(0x10)) _STR(_DB(0x8B) _DB(0x55) _DB(0x0C)) _STR(_DB(0x8B) _DB(0x45) _DB(0x08)) _END_ASM
/// по стандарту STDCALL параметры передаются через стек с использованием регистра EBP, загружаются в регистры EAX EDX, необходимо учитывать директивы компиляции с отключенной оптимизацией, рекомендуется #pragma optimize( "gtpy", off ) или #pragma optimize( "", off )
#define PARAMETERS_VOID_VOID _BEGIN_ASM _STR(_DB(0x8B) _DB(0x55) _DB(0x0C)) _STR(_DB(0x8B) _DB(0x45) _DB(0x08)) _END_ASM
/// по стандарту STDCALL параметры передаются через стек с использованием регистра EBP, загружаются в регистры EAX, необходимо учитывать директивы компиляции с отключенной оптимизацией, рекомендуется #pragma optimize( "gtpy", off ) или #pragma optimize( "", off )
#define PARAMETERS_VOID _BEGIN_ASM _LINE3(0x8B,0x45,0x08) _END_ASM
/// по стандарту STDCALL параметры передаются через стек с использованием регистра EBP, загружаются в регистры EAX EDX, адрес последнего параметра вычисляется ECX, необходимо учитывать директивы компиляции с отключенной оптимизацией, рекомендуется #pragma optimize( "gtpy", off ) или #pragma optimize( "", off )
#define PARAMETERS_VOID_VOID_DATA32 _BEGIN_ASM _LINE3(0x8D,0x4D,0x10) _STR(_DB(0x8B) _DB(0x55) _DB(0x0C)) _STR(_DB(0x8B) _DB(0x45) _DB(0x08)) _END_ASM
/// по стандарту STDCALL параметры передаются через стек с использованием регистра EBP, необходимо учитывать директивы компиляции с отключенной оптимизацией, рекомендуется #pragma optimize( "gtpy", off ) или #pragma optimize( "", off )
#define PARAMETERS_VOID_VOID_DATA64 _BEGIN_ASM _LINE3(0x8D,0x4D,0x10) _STR(_DB(0x8B) _DB(0x55) _DB(0x0C)) _STR(_DB(0x8B) _DB(0x45) _DB(0x08)) _END_ASM

/// Сохранение в стек регистра EAX
#define PUSH_EAX _BEGIN_ASM _LINE1(0x50) _END_ASM
/// Сохранение в стек регистра ECX
#define PUSH_ECX _BEGIN_ASM _LINE1(0x51) _END_ASM
/// Сохранение в стек регистра EDX
#define PUSH_EDX _BEGIN_ASM _LINE1(0x52) _END_ASM
/// Сохранение в стек регистра EBX
#define PUSH_EBX _BEGIN_ASM _LINE1(0x53) _END_ASM
/// Сохранение в стек регистра EBP
#define PUSH_EBP _BEGIN_ASM _LINE1(0x55) _END_ASM
/// Сохранение в стек регистра ESI
#define PUSH_ESI _BEGIN_ASM _LINE1(0x56) _END_ASM
/// Сохранение в стек регистра EDI
#define PUSH_EDI _BEGIN_ASM _LINE1(0x57) _END_ASM
/// Востановление регистра EAX из стека
#define POP_EAX _BEGIN_ASM _LINE1(0x58) _END_ASM
/// Востановление регистра ECX из стека
#define POP_ECX _BEGIN_ASM _LINE1(0x59) _END_ASM
/// Востановление регистра EDX из стека
#define POP_EDX _BEGIN_ASM _LINE1(0x5A) _END_ASM
/// Востановление регистра EBX из стека
#define POP_EBX _BEGIN_ASM _LINE1(0x5B) _END_ASM
/// Востановление регистра EBP из стека
#define POP_EBP _BEGIN_ASM _LINE1(0x5D) _END_ASM
/// Востановление регистра ESI из стека
#define POP_ESI _BEGIN_ASM _LINE1(0x5E) _END_ASM
/// Востановление регистра EDI из стека
#define POP_EDI _BEGIN_ASM _LINE1(0x5F) _END_ASM

#define PUSH_ESP_EAX _BEGIN_ASM _LINE4(0x89,0x44,0x24,0xE4) _END_ASM
#define PUSH_ESP_ECX _BEGIN_ASM _LINE4(0x89,0x4C,0x24,0xE8) _END_ASM
#define PUSH_ESP_EDX _BEGIN_ASM _LINE4(0x89,0x54,0x24,0xEC) _END_ASM
#define PUSH_ESP_EBX _BEGIN_ASM _LINE4(0x89,0x5C,0x24,0xF0) _END_ASM
#define PUSH_ESP_EBP _BEGIN_ASM _LINE4(0x89,0x6C,0x24,0xF4) _END_ASM
#define PUSH_ESP_ESI _BEGIN_ASM _LINE4(0x89,0x74,0x24,0xF8) _END_ASM
#define PUSH_ESP_EDI _BEGIN_ASM _LINE4(0x89,0x7C,0x24,0xFC) _END_ASM
#define POP_ESP_EAX _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0xE4) _END_ASM
#define POP_ESP_ECX _BEGIN_ASM _LINE4(0x8B,0x4C,0x24,0xE8) _END_ASM
#define POP_ESP_EDX _BEGIN_ASM _LINE4(0x8B,0x54,0x24,0xEC) _END_ASM
#define POP_ESP_EBX _BEGIN_ASM _LINE4(0x8B,0x5C,0x24,0xF0) _END_ASM
#define POP_ESP_EBP _BEGIN_ASM _LINE4(0x8B,0x6C,0x24,0xF4) _END_ASM
#define POP_ESP_ESI _BEGIN_ASM _LINE4(0x8B,0x74,0x24,0xF8) _END_ASM
#define POP_ESP_EDI _BEGIN_ASM _LINE4(0x8B,0x7C,0x24,0xFC) _END_ASM

#define SAVE_FUNC_1_PARAMETERS
#define SAVE_FUNC_2_PARAMETERS _BEGIN_ASM _LINE4(0x89,0x54,0x24,0xEC) _END_ASM
#define LOAD_FUNC_1_PARAMETERS
#define LOAD_FUNC_2_PARAMETERS _BEGIN_ASM _LINE4(0x8B,0x54,0x24,0xEC) _END_ASM

#define SAVE_1_PARAMETERS _BEGIN_ASM _LINE4(0x89,0x44,0x24,0xE4) _END_ASM
#define SAVE_2_PARAMETERS _BEGIN_ASM _LINE4(0x89,0x44,0x24,0xE4) _LINE4(0x89,0x54,0x24,0xEC) _END_ASM
#define SAVE_3_PARAMETERS _BEGIN_ASM _LINE4(0x89,0x44,0x24,0xE4) _LINE4(0x89,0x54,0x24,0xEC) _LINE4(0x89,0x4C,0x24,0xE8) _END_ASM
#define SAVE_4_PARAMETERS _BEGIN_ASM _LINE4(0x89,0x44,0x24,0xE4) _LINE4(0x89,0x54,0x24,0xEC) _LINE4(0x89,0x4C,0x24,0xE8) _LINE4(0x89,0x7C,0x24,0xF0) _END_ASM
#define SAVE_5_PARAMETERS _BEGIN_ASM _LINE4(0x89,0x44,0x24,0xE4) _LINE4(0x89,0x54,0x24,0xEC) _LINE4(0x89,0x4C,0x24,0xE8) _LINE4(0x89,0x7C,0x24,0xF0) _LINE4(0x89,0x74,0x24,0xF4) _END_ASM
#define SAVE_6_PARAMETERS _BEGIN_ASM _LINE4(0x89,0x44,0x24,0xE4) _LINE4(0x89,0x54,0x24,0xEC) _LINE4(0x89,0x4C,0x24,0xE8) _LINE4(0x89,0x7C,0x24,0xF0) _LINE4(0x89,0x74,0x24,0xF4) _LINE4(0x89,0x5C,0x24,0xF8) _END_ASM
#define SAVE_7_PARAMETERS _BEGIN_ASM _LINE4(0x89,0x44,0x24,0xE4) _LINE4(0x89,0x54,0x24,0xEC) _LINE4(0x89,0x4C,0x24,0xE8) _LINE4(0x89,0x7C,0x24,0xF0) _LINE4(0x89,0x74,0x24,0xF4) _LINE4(0x89,0x5C,0x24,0xF8) _LINE4(0x89,0x6C,0x24,0xFC) _END_ASM
#define LOAD_1_PARAMETERS _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0xE4) _END_ASM
#define LOAD_2_PARAMETERS _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0xE4) _LINE4(0x8B,0x54,0x24,0xEC) _END_ASM
#define LOAD_3_PARAMETERS _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0xE4) _LINE4(0x8B,0x54,0x24,0xEC) _LINE4(0x8B,0x4C,0x24,0xE8) _END_ASM
#define LOAD_4_PARAMETERS _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0xE4) _LINE4(0x8B,0x54,0x24,0xEC) _LINE4(0x8B,0x4C,0x24,0xE8) _LINE4(0x8B,0x7C,0x24,0xF0) _END_ASM
#define LOAD_5_PARAMETERS _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0xE4) _LINE4(0x8B,0x54,0x24,0xEC) _LINE4(0x8B,0x4C,0x24,0xE8) _LINE4(0x8B,0x7C,0x24,0xF0) _LINE4(0x8B,0x74,0x24,0xF4) _END_ASM
#define LOAD_6_PARAMETERS _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0xE4) _LINE4(0x8B,0x54,0x24,0xEC) _LINE4(0x8B,0x4C,0x24,0xE8) _LINE4(0x8B,0x7C,0x24,0xF0) _LINE4(0x8B,0x74,0x24,0xF4) _LINE4(0x8B,0x5C,0x24,0xF8) _END_ASM
#define LOAD_7_PARAMETERS _BEGIN_ASM _LINE4(0x8B,0x44,0x24,0xE4) _LINE4(0x8B,0x54,0x24,0xEC) _LINE4(0x8B,0x4C,0x24,0xE8) _LINE4(0x8B,0x7C,0x24,0xF0) _LINE4(0x8B,0x74,0x24,0xF4) _LINE4(0x8B,0x5C,0x24,0xF8) _LINE4(0x8B,0x6C,0x24,0xFC) _END_ASM

#define RET _BEGIN_ASM _LINE1( 0xC3 ) _END_ASM
#define RET_0 _BEGIN_ASM _LINE1( 0xC3 ) _END_ASM
#define RET_1 _BEGIN_ASM _LINE3( 0xC2,0x04,0x00 ) _END_ASM
#define RET_2 _BEGIN_ASM _LINE3( 0xC2,0x08,0x00 ) _END_ASM
#define RET_3 _BEGIN_ASM _LINE3( 0xC2,0x0C,0x00 ) _END_ASM
#define RET_4 _BEGIN_ASM _LINE3( 0xC2,0x10,0x00 ) _END_ASM
#define RET_5 _BEGIN_ASM _LINE3( 0xC2,0x14,0x00 ) _END_ASM
#define RET_6 _BEGIN_ASM _LINE3( 0xC2,0x18,0x00 ) _END_ASM
#define RET_7 _BEGIN_ASM _LINE3( 0xC2,0x1C,0x00 ) _END_ASM
#define RET_8 _BEGIN_ASM _LINE3( 0xC2,0x20,0x00 ) _END_ASM
#define RET_9 _BEGIN_ASM _LINE3( 0xC2,0x24,0x00 ) _END_ASM

#define ADD_ESP(a) _BEGIN_ASM _ASM _LINE3( 0xC2,0x1C,a ) _END_ASM
#define SUB_ESP(a) _BEGIN_ASM _ASM _LINE3( 0xC2,0x1C,a ) _END_ASM
