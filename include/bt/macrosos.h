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

///*
// *
// * OS_WIN - windows
// *
// * OS_QNX - qnx
// * 
// * OS_LYNX - lynx
// * 
// * OS_LINUX - fedora, ubuntu
// * 
// * OS_OSX - mac osx
// *
// */

#pragma once

/* Operating system recognition (basic) */
#if defined (__unix) || defined (__linux__) || defined (__QNX__) || defined (_AIX) || defined (__NetBSD__) || defined (__OpenBSD__) || defined (__Lynx__) || defined(hpux) || defined(__hpux)
#undef  _UNIX
#define _UNIX 1

#elif defined(macintosh) || defined (_MAC) || defined(__APPLE__)
#undef _MAC
#define _MAC

#elif defined (_WIN32) || defined (__WIN32) || defined (WIN32) || defined (__WIN32__)
#undef _WIN32
#define _WIN32
#elif defined (_WIN64) || defined (__WIN64) || defined (WIN64) || defined (__WIN64__)
#undef _WIN64
#define _WIN64
#elif defined (__WIN16) || defined (WIN16) || defined (_WIN16)
#undef _WIN16
#define _WIN16
#error ""
#else
#error ""
#endif /* platforms */

#if defined (__QNX__) || defined (__QNXNTO__)
#undef  OS_QNX
#define OS_QNX
#elif defined (_WIN16) || defined (_WIN32) || defined (_WIN64)
#undef  OS_WIN
#define OS_WIN
#elif defined (_MAC)
#undef  OS_OSX
#define OS_OSX
#elif defined (__linux__) || defined (__linux)
#define OS_LINUX
#elif defined (__Lynx__)
#define OS_LYNX
#endif

