//=============================================================================
///**
// *  @file macros.h
// *
// *  $Id: macros.h 23.05.2012  $
// *
// *  @brief macro commands, MS Visual C++ 2008; GNU C/C++ 4.0;
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#pragma once

//******************************************** Microsoft Visual C++ ****************************************

#ifdef _MSC_VER

#if defined(_M_ALPHA)
#define CPU_ALPHA
#endif

#if defined(_M_ARM) || defined(_M_ARMT)
#define CPU_ARM_32
#endif

#if defined(__aarch64__)
#define CPU_ARM_64
#endif

#if defined(_M_I86)
#define CPU_X86_16
#endif

#if defined(_M_X64) || defined(_M_AMD64) || defined(_M_IA64)
#define CPU_X86_64
#endif

#if defined(_M_IX86) && !defined(CPU_X86_64)
#define CPU_X86_32
#endif

#if defined(__e2k__) && defined(__ptr32__)
#define CPU_E2K_32
#endif

#if defined(__e2k__) && defined(__ptr64__)
#define CPU_E2K_64
#endif

#endif /* _MSC_VER */

//******************************************** MinGW **********************************************************

#ifdef __GNUC__
#ifdef __MINGW32__

#if defined(_X86_)
#define CPU_X86_32
#endif

#endif /* __MINGW32__  */
#endif /* __GNUC__ */

//******************************************** GNU C/C++ ***************************************************

#ifdef __GNUC__
#ifndef __MINGW32__

#if defined(__alpha__)
#define CPU_ALPHA
#endif

#if defined(__arm__) || defined(__thumb__)
#define CPU_ARM_32
#endif

#if defined(__aarch64__)
#define CPU_ARM_64
#endif

#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
#define CPU_AMD
#endif

//#if defined(_M_I86)
//#define CPU_X86_16
//#endif

#if (defined(CPU_AMD) && defined(__ILP32__)) || defined(i386) || defined(__i386) || defined(__i386__)
#define CPU_X86_32
#endif

#if (defined(CPU_AMD) && !defined(__ILP32__)) || defined(__ia64__) || defined(__IA64__) || defined(_IA64)
#define CPU_X86_64
#endif

#if defined(CPU_X86_64)
#undef CPU_X86_32
#endif

#if defined(__sparc__) && defined(__ptr32__)
#define CPU_SPARC_32
#endif

#if defined(__sparc__) && defined(__ptr64__)
#define CPU_SPARC_64
#endif

#if defined(__e2k__) && defined(__ptr32__)
#define CPU_E2K_32
#endif

#if defined(__e2k__) && defined(__ptr64__)
#define CPU_E2K_64
#endif

#endif /* __MINGW32__ */
#endif /* __GNUC__ */

//******************************************** Borland C++ ***************************************************

#ifdef __BORLANDC__

#if defined(_M_I86)
#define CPU_X86_16
#endif

#if defined(_M_IX86) || defined(__X86__)
#define CPU_X86_32
#endif

#endif

//******************************************** Intel C++ *****************************************************

#ifdef __INTEL_COMPILER

#if defined(_M_IX86)
#define CPU_X86_32
#endif

#if defined(_M_IA64)
#define CPU_X86_64
#endif

#endif

/*
#ifdef __arm__ || PROCESSOR_ARM || _M_ARM
#define CPU_ARM
#endif

#if defined(__x86_64__) || defined(__x86_64) || defined(__amd64__) || defined(__amd64) || defined(PROCESSOR_INTEL) || defined(PROCESSOR_AMD64) || defined(_M_64) || defined(_M_AMD64) || defined(i386) || defined(_X86_) || defined(__X86__) || defined(_I86_) || defined(_M_I86) || defined(_M_IX86) || defined(_M_IA64)
#define CPU_X86
#endif
*/
