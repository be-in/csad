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

#ifdef OS_WIN
/// Microsoft Calling Convention
#ifndef CALLMC
#define CALLMC
#endif
#else
/// System V Calling Convention
#ifndef CALLSV
#define CALLSV
#endif
#endif

//******************************************** Microsoft Visual C++ ****************************************
#if defined(MSVC)

#define ARCH_ALL
#define ARCH_DEFAULT
#define ARCH_SSE
#define ARCH_SSE2
#define ARCH_SSE3
#define ARCH_SSE4
#define ARCH_AVX
#define ARCH_AVX2

#endif

//******************************************** GNU C/C++ ***************************************************
#if defined(GCC) || defined(MINGW)

#define ARCH_ALL
#define ARCH_DEFAULT
#define ARCH_SSE
#define ARCH_SSE2
#define ARCH_SSE3
#define ARCH_SSE4
#define ARCH_AVX
#define ARCH_AVX2

/*#if defined(CPU_X86_32) || defined(CPU_X86_64)
#define ARCH_ALL _Pragma("GCC target \"mmx\"") \
	_Pragma("GCC target \"3dnow\"") \
	_Pragma("GCC target \"sse\"") \
	_Pragma("GCC target \"sse2\"") \
	_Pragma("GCC target \"sse3\"") \
	_Pragma("GCC target \"ssse3\"") \
	_Pragma("GCC target \"sse4\"") \
	_Pragma("GCC target \"sse4a\"") \
	_Pragma("GCC target \"sse4.1\"") \
	_Pragma("GCC target \"sse4.2\"") \
	_Pragma("GCC target \"avx\"") \
	_Pragma("GCC target \"avx2\"")

#if defined(CPU_X86_32)
#define ARCH_DEFAULT _Pragma("GCC target \"no-avx2\"") \
	_Pragma("GCC target \"no-avx\"") \
	_Pragma("GCC target \"no-sse4.2\"") \
	_Pragma("GCC target \"no-sse4.1\"") \
	_Pragma("GCC target \"no-sse4a\"") \
	_Pragma("GCC target \"no-sse4\"") \
	_Pragma("GCC target \"no-ssse3\"") \
	_Pragma("GCC target \"no-sse3\"") \
	_Pragma("GCC target \"no-sse2\"") \
	_Pragma("GCC target \"no-sse\"") \
	_Pragma("GCC target \"no-3dnow\"") \
	_Pragma("GCC target \"no-mmx\"")

#endif
#if defined(CPU_X86_64)
#define ARCH_DEFAULT _Pragma("GCC target \"no-avx2\"") \
	_Pragma("GCC target \"no-avx\"") \
	_Pragma("GCC target \"no-sse4.2\"") \
	_Pragma("GCC target \"no-sse4.1\"") \
	_Pragma("GCC target \"no-sse4a\"") \
	_Pragma("GCC target \"no-sse4\"") \
	_Pragma("GCC target \"no-ssse3\"") \
	_Pragma("GCC target \"no-sse3\"") \
	_Pragma("GCC target \"no-3dnow\"") \
	_Pragma("GCC target \"mmx\"") \
	_Pragma("GCC target \"sse\"") \
	_Pragma("GCC target \"sse2\"")

#endif

#define ARCH_SSE _Pragma("GCC target \"no-avx2\"") \
	_Pragma("GCC target \"no-avx\"") \
	_Pragma("GCC target \"no-sse4.2\"") \
	_Pragma("GCC target \"no-sse4.1\"") \
	_Pragma("GCC target \"no-sse4a\"") \
	_Pragma("GCC target \"no-sse4\"") \
	_Pragma("GCC target \"no-ssse3\"") \
	_Pragma("GCC target \"no-sse3\"") \
	_Pragma("GCC target \"no-sse2\"") \
	_Pragma("GCC target \"no-3dnow\"") \
	_Pragma("GCC target \"mmx\"") \
	_Pragma("GCC target \"sse\"")

#define ARCH_SSE2 _Pragma("GCC target \"no-avx2\"") \
	_Pragma("GCC target \"no-avx\"") \
	_Pragma("GCC target \"no-sse4.2\"") \
	_Pragma("GCC target \"no-sse4.1\"") \
	_Pragma("GCC target \"no-sse4a\"") \
	_Pragma("GCC target \"no-sse4\"") \
	_Pragma("GCC target \"no-ssse3\"") \
	_Pragma("GCC target \"no-sse3\"") \
	_Pragma("GCC target \"no-3dnow\"") \
	_Pragma("GCC target \"mmx\"") \
	_Pragma("GCC target \"sse\"") \
	_Pragma("GCC target \"sse2\"")

#define ARCH_SSE3 _Pragma("GCC target \"no-avx2\"") \
	_Pragma("GCC target \"no-avx\"") \
	_Pragma("GCC target \"no-sse4.2\"") \
	_Pragma("GCC target \"no-sse4.1\"") \
	_Pragma("GCC target \"no-sse4a\"") \
	_Pragma("GCC target \"no-sse4\"") \
	_Pragma("GCC target \"no-3dnow\"") \
	_Pragma("GCC target \"mmx\"") \
	_Pragma("GCC target \"sse\"") \
	_Pragma("GCC target \"sse2\"") \
	_Pragma("GCC target \"sse3\"") \
	_Pragma("GCC target \"ssse3\"")

#define ARCH_SSE4 _Pragma("GCC target \"no-avx2\"") \
	_Pragma("GCC target \"no-avx\"") \
	_Pragma("GCC target \"no-3dnow\"") \
	_Pragma("GCC target \"mmx\"") \
	_Pragma("GCC target \"sse\"") \
	_Pragma("GCC target \"sse2\"") \
	_Pragma("GCC target \"sse3\"") \
	_Pragma("GCC target \"ssse3\"") \
	_Pragma("GCC target \"sse4\"") \
	_Pragma("GCC target \"sse4a\"") \
	_Pragma("GCC target \"sse4.1\"") \
	_Pragma("GCC target \"sse4.2\"")

#define ARCH_AVX _Pragma("GCC target \"no-avx2\"") \
	_Pragma("GCC target \"no-3dnow\"") \
	_Pragma("GCC target \"mmx\"") \
	_Pragma("GCC target \"sse\"") \
	_Pragma("GCC target \"sse2\"") \
	_Pragma("GCC target \"sse3\"") \
	_Pragma("GCC target \"ssse3\"") \
	_Pragma("GCC target \"sse4\"") \
	_Pragma("GCC target \"sse4a\"") \
	_Pragma("GCC target \"sse4.1\"") \
	_Pragma("GCC target \"sse4.2\"") \
	_Pragma("GCC target \"avx\"")

#define ARCH_AVX2 _Pragma("GCC target \"no-3dnow\"") \
	_Pragma("GCC target \"mmx\"") \
	_Pragma("GCC target \"sse\"") \
	_Pragma("GCC target \"sse2\"") \
	_Pragma("GCC target \"sse3\"") \
	_Pragma("GCC target \"ssse3\"") \
	_Pragma("GCC target \"sse4\"") \
	_Pragma("GCC target \"sse4a\"") \
	_Pragma("GCC target \"sse4.1\"") \
	_Pragma("GCC target \"sse4.2\"") \
	_Pragma("GCC target \"avx\"") \
	_Pragma("GCC target \"avx2\"")

#else

#endif*/

#endif


