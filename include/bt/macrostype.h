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

#include "macroscall.h"
#include "macrosos.h"

///*
// *
// * _int32 - 32 bit signed int, for unsigned use: unsigned _int32.
// *
// * _int64 - 64 bit signed int, for unsigned use: unsigned _int64.
// *
// * _voidint - unsigned int with pointer bits count.
// *
// * _voidintmax - max value in _voidint.
// *
// */

//******************************************** Microsoft Visual C++ ****************************************

#ifdef MSVC

#ifdef OS_WIN
#ifndef _int32
#define _int32 long
//#define _int32 __int32
#endif

#ifndef _int64
#define _int64 __int64
#endif
#endif

#if !defined (_W64)
#if !defined (__midl) && (defined (_X86_) || defined (_M_IX86))
#define _W64 __w64
#else  /* !defined (__midl) && (defined (_X86_) || defined (_M_IX86)) */
#define _W64
#endif  /* !defined (__midl) && (defined (_X86_) || defined (_M_IX86)) */
#endif  /* !defined (_W64) */

#ifndef _SIZE_T_DEFINED
#ifdef _WIN64
typedef unsigned __int64    size_t;
#else  /* _WIN64 */
typedef _W64 unsigned int   size_t;
#endif  /* _WIN64 */
#define _SIZE_T_DEFINED
#endif  /* _SIZE_T_DEFINED */

#endif

//******************************************** MinGW **********************************************************

#ifdef MINGW

#if UINT_MAX == 0xFFFF
#ifndef _int32
#define _int32 long
#endif
#endif

#ifndef _int32
#define _int32 int
#endif

#if ULONG_MAX == 0xFFFFFFFFFFFFFFFF
#ifndef _int64
#define _int64 long
#endif
#else
#ifndef _int64
#define _int64 long long
#endif
#endif

#endif /* __GNUC__  __MINGW32__*/

//******************************************** GNU C/C++ ***************************************************

#ifdef GCC

#if UINT_MAX == 0xFFFF
#ifndef _int32
#define _int32 long
#endif
#endif

#ifndef _int32
#define _int32 int
#endif

#if ULONG_MAX == 0xFFFFFFFFFFFFFFFF
#ifndef _int64
#define _int64 long
#endif
#else
#ifndef _int64
#define _int64 long long
#endif
#endif

#ifndef _VPTROFFSET
#define _VPTROFFSET 1
#endif

#endif

//******************************************** addition macros ***********************************************

typedef void * pointer;

#if defined(_X32)
#define MULSIZEOFVOID( a ) ((a)<<2)
#define DIVSIZEOFVOID( a ) ((a)>>2)
#define _voidint unsigned _int32
#define _voidintmax 0xFFFFFFFF
#endif

#if defined(_X64)
#define MULSIZEOFVOID( a ) ((a)<<3)
#define DIVSIZEOFVOID( a ) ((a)>>3)
#define _voidint unsigned _int64
#define _voidintmax 0xFFFFFFFFFFFFFFFF
#endif
