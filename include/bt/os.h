/*
 *  os.h
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef OS_H_
#define OS_H_

#include <bt/macrosos.h>
#include <bt/macroscall.h>

OPTIMIZE_ON;

#ifdef __cplusplus

#if defined (OS_QNX)
#ifdef _int64
#undef _int64
#endif
//#define __PLATFORM_H_INCLUDED
#include <assert.h>
#include <string.h>
#include <typeinfo>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

#define type_info std::type_info

#elif defined (OS_WIN)
#include <assert.h>
#include <stdarg.h>
#include <windows.h>
#include <winbase.h>

#elif defined (OS_LINUX)

#include <cstdlib>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <stddef.h>

#elif defined (OS_OSX)

#include <cstdlib>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <stddef.h>

#else

#include <cstdlib>

#endif

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

#endif

OPTIMIZE_OFF;

#endif /* OS_H_ */
