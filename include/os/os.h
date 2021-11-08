/*
 * mouse.h
 *
 *  Created on: 09.08.2013
 *      Author: Пантелеймонов Александр
 */

#ifndef OS_H_
#define OS_H_

/* Operating system recognition (basic) */
#if defined (__unix) || defined (__linux__) || defined (__QNX__) || defined (_AIX) || defined (__NetBSD__) || defined (__OpenBSD__) || defined (__Lynx__) || defined(hpux) || defined(__hpux)
#undef  _UNIX
#define _UNIX 1

#elif defined(macintosh) || defined (_MAC) || defined(__APPLE__)
#undef _MAC
#define _MAC  1

#elif defined (_WIN32) || defined (__WIN32) || defined (WIN32) || defined (__WIN32__)
#undef _WIN32
#define _WIN32

#elif defined (__WIN16) || defined (WIN16) || defined (_WIN16)
#undef _WIN16
#define _WIN16
#error ""
#else
#error ""
#endif /* platforms */

#if defined (__QNX__)
#undef  OS_QNX
#define OS_QNX
#elif defined (_WIN16) || defined (_WIN32)
#undef  OS_WIN
#define OS_WIN
#endif

#if defined (OS_QNX)
#ifdef _int64
#undef _int64
#endif
//#define __PLATFORM_H_INCLUDED
#include <assert.h>
#include <setjmp.h>
#include <typeinfo>
#include <cstdlib>
#include <map>
#include <vector>
#include <string>
#include <font_api.h>

#define type_info std::type_info

#include <errno.h>
#include <stdio.h>
#include <string>
#include <string.h>

#include <stdarg.h>
#include <fcntl.h>

#include <sys/select.h>
#include <sys/dcmd_input.h>

#elif defined (OS_WIN)
#include <assert.h>
#include <map>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <windows.h>
#include <wingdi.h>
#include <GL/gl.h>

#else

#include <cstdlib>

#endif

#endif /* OS_H_ */
