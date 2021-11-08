//=============================================================================
///**
// *  @file macros.h
// *
// *  $Id: macros.h 23.05.2012  $
// *
// *  @brief macro commands, MS Visual C++ 2008; GNU C/C++;
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#pragma once

#include "macroscpu.h"

///*
// *  **************  Общие директивы **************
// *  http://predef.sourceforge.net/precomp.html - макросы определения компилятора
// *  MSVC - компилятор Microsoft Visual C++
// *  INTEL - компилятор Intel C++
// *  BORLAND - компилятор Borland C++
// *  GCC - компилятор GNU C/C++
// *  MINGW - компилятор MinGW
// *
// *  _NOINLINE - instruction of shutdown of replacement of a call of function by her body.
// *              example: void _NOINLINE test(int i);
// *
// *  _FORCELINE - instruction of obligatory replacement of a call of function by her body.
// *               example: void _NOINLINE test(int i);
// *
// *  _STDCALL - standard of transfer of parameters through a stack, in the following sequence:
// *             [esp+4], [esp+8] ...
// *             parameters in the int64 or double size are transferred by dimension through a stack.
// *             example: void _STDCALL Scale(void* a,void* b,double c,double d)
// *             [esp+4] - a, [esp+8] - b, [esp+12] - c, [esp+20] - d
// *
// *  _FASTCALL - standard C ++ transfers of parameters through registers, in the following sequence:
// *              ecx, edx, [esp+4], [esp+8] ...
// *              parameters in the int64 or double size are transferred by dimension through a stack.
// *              example: void _FASTCALL Scale(void* a,void* b,double c,double d)
// *              ecx - a, edx - b, [esp+4] - c, [esp+12] - d
// *
// *  _NAKED - the instruction disconnects automatic formation of the beginning and the function end.
// *           it is applied to independent writing of processing of input parameters of a stack and return from function.
// *           example: int _NAKED not(int i)
// *                   {
// *				       BEGIN_ASM
// *					     _ASM mov eax,[esp+4];
// *						 _ASM not eax;
// *						 _ASM ret 0x4;
// *                       END_ASM
// *                   }
// *
// *  _ALIGN - the instruction of alignment of variables on border of 16 bytes
// *           increases productivity of any calculations and operations using memory for 20 %-50 %.
// *           исключением являются случаи с копированием данных - требуется дополнительное выравнивание по границе кеша.
// *           example: _ALIGN int t;
// *                    _ALIGN double t[3];
// *
// */

#if defined(CPU_X86_32) || defined(CPU_E2K_32)
#define _X32
#endif

#if defined(CPU_X86_64) || defined(CPU_E2K_64)
#define _X64
#endif

//******************************************** Microsoft Visual C++ ****************************************

#ifdef _MSC_VER

#ifndef MSVC
#define MSVC
#endif

#define WARNING_DISABLE __pragma(warning(disable:4251)) __pragma(warning(disable:4521)) __pragma(warning(disable:4244)) __pragma(warning(disable:4172))
#define WARNING_ENABLE __pragma(warning(default:4251)) __pragma(warning(default:4521)) __pragma(warning(default:4244)) __pragma(warning(default:4172))
#define OPTIMIZE_ON __pragma(optimize( "gtpyb", on ))
#define OPTIMIZE_OFF __pragma(optimize( "gtpyb", off ))

#ifdef _X64
#define _APICALL
#define _FASTCALL
#define _CDECL
#endif

#ifndef _APICALL
#define _APICALL __stdcall
#endif

#ifndef _FASTCALL
#define _FASTCALL __fastcall
#endif

#ifndef _CDECL
#define _CDECL __cdecl
#endif

#ifndef _NOINLINE
#define _NOINLINE __declspec(noinline)
#endif

#ifndef _HIDE
#define _HIDE
#endif

#ifndef _NORETURN
#define _NORETURN
#endif

#ifndef _FORCEINLINE
#define _FORCEINLINE __forceinline
#endif

#ifndef _NAKED
#ifdef CPU_X86_32
#define _NAKED __declspec(naked)
#else
#define _NAKED
#endif
#endif

#ifndef _ALIGN
#define _ALIGN __declspec(align(16))
#endif

#ifndef _VPTROFFSET
#define _VPTROFFSET 0
#endif

#ifdef _DEBUG
#undef _DEBUG
#endif

#ifdef NDEBUG
#define _RELEASE
#else
#define _DEBUG
#endif

#endif

//******************************************** MinGW **********************************************************

#if defined(__GNUC__) && defined(__WIN32__) || defined(__MINGW32__)

#ifndef MINGW
#define MINGW
#endif

#ifdef __GNUC_PATCHLEVEL__
#define COMPILER_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__ )
#else
#define COMPILER_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100)
#endif

#if COMPILER_VERSION >= 40400
#define WARNING_DISABLE _Pragma("GCC diagnostic ignored \"-Wall\"")
#define WARNING_ENABLE _Pragma("GCC diagnostic warning \"-Wall\"")
#define OPTIMIZE_ON _Pragma("GCC optimize(\"O2\")")
#define OPTIMIZE_OFF _Pragma("GCC optimize(\"O0\")")
#else
#define WARNING_DISABLE
#define WARNING_ENABLE
#define OPTIMIZE_ON
#define OPTIMIZE_OFF

#define _APICALL __attribute__((__stdcall__))
#define _FASTCALL __attribute__((__fastcall__))
#define _CDECL __attribute__((__cdecl__))
#define _NOINLINE __attribute__((__noinline__))
#define _NAKED __attribute__((__naked__))
#endif

#ifdef WFP3
#undef WFP3
#endif
#define WFP3(a) (((char*)a)+3)

#ifndef _APICALL
#define _APICALL __attribute__((stdcall))
#endif

#ifndef _FASTCALL
#define _FASTCALL __attribute__((fastcall))
#endif

#ifndef _CDECL
#define _CDECL __attribute__((cdecl))
#endif

#ifndef _NOINLINE
#define _NOINLINE __attribute__((noinline))
#endif

#ifndef _HIDE
#define _HIDE __attribute__((visibility("hidden")))
#endif

#ifndef _NORETURN
#define _NORETURN __attribute__((noreturn))
#endif

#ifndef _HIDE
#define _HIDE __attribute__((visibility("hidden")))
#endif

#ifndef _NORETURN
#define _NORETURN __attribute__((noreturn))
#endif

#ifndef _FORCEINLINE
#define _FORCEINLINE __inline__ __attribute__((always_inline))
#endif //__attribute__((inline))

#ifndef _NAKED
#define _NAKED __declspec(naked) __attribute__((optimize(3)))
#endif //__attribute__((naked))

#ifndef _ALIGN
#define _ALIGN __attribute__((aligned (16)))
#endif

#ifndef _VPTROFFSET
#define _VPTROFFSET 0
#endif

#endif /* __GNUC__  __MINGW32__*/

//******************************************** GNU C/C++ ***************************************************

#ifdef __GNUC__
#ifndef __MINGW32__

#ifndef GCC
#define GCC
#endif

#ifdef __GNUC_PATCHLEVEL__
#define COMPILER_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__ )
#else
#define COMPILER_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100)
#endif

#if COMPILER_VERSION >= 40400
		#define WARNING_DISABLE _Pragma("GCC diagnostic ignored \"-Wall\"")
		#define WARNING_ENABLE _Pragma("GCC diagnostic warning \"-Wall\"")
#define OPTIMIZE_ON _Pragma("GCC optimize(\"O2\")") \
			_Pragma("GCC optimize(\"no-caller-saves\")")
#define OPTIMIZE_OFF _Pragma("GCC optimize(\"O0\")")
#else
#define WARNING_DISABLE
#define WARNING_ENABLE
#define OPTIMIZE_ON
#define OPTIMIZE_OFF

// specially for gcc < 4.4, because we need to skip prolog (push ebp; mov ebp,esp).
#ifdef WFP3
#undef WFP3
#endif
#define WFP3(a) (((char*)a)+3)

#define _APICALL __attribute__((__stdcall__))
#define _FASTCALL __attribute__((__fastcall__))
#define _CDECL __attribute__((__cdecl__))
#define _NOINLINE __attribute__((__noinline__))
#define _NAKED __attribute__((__naked__))

#endif

#ifdef _X64
#undef _APICALL
#undef _FASTCALL
#undef _CDECL
#define _APICALL
#define _FASTCALL
#define _CDECL
#endif

#ifndef _APICALL
#define _APICALL __attribute__((stdcall))
#endif

#ifndef _FASTCALL
#define _FASTCALL __attribute__((fastcall))
#endif

#ifndef _CDECL
#define _CDECL __attribute__((cdecl))
#endif

#ifndef _NOINLINE
#define _NOINLINE __attribute__((noinline))
#endif

#ifndef _HIDE
#define _HIDE __attribute__((visibility("hidden")))
#endif

#ifndef _NORETURN
#define _NORETURN __attribute__((noreturn))
#endif

#ifndef _FORCEINLINE
#define _FORCEINLINE __inline__ __attribute__((always_inline))
#endif //__inline__ __attribute__((always_inline))

#ifndef _NAKED
#define _NAKED __attribute__((naked))
#endif

#ifndef _ALIGN
#define _ALIGN __attribute__((aligned (16)))
#endif

#ifndef _VPTROFFSET
#define _VPTROFFSET 1
#endif

#endif /* __MINGW32__ */
#endif /* __GNUC__ */

//******************************************** Borland C++ ***************************************************

#ifdef __BORLANDC__
#ifndef BORLAND
#define BORLAND
#endif

#ifndef _FORCEINLINE
#define _FORCEINLINE
#endif

#ifndef _NAKED
#define _NAKED
#endif

#ifndef _ALIGN
#define _ALIGN
#endif

#ifndef _VPTROFFSET
#define _VPTROFFSET 0
#endif

#endif

//******************************************** Intel C++ *****************************************************

#ifdef __INTEL_COMPILER
#ifndef INTEL
#define INTEL
#endif

#ifndef _VPTROFFSET
#define _VPTROFFSET 0
#endif

#endif

