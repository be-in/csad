//=============================================================================
///**
// *  @file macrosasm.h
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

