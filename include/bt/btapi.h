/*
 * btapi.h
 *
 *  Created on: 10.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef BTAPI_H_
#define BTAPI_H_

#include <bt/os.h>

#if defined(BT_LIB) || defined(LIB_BT)
#define BT_EXPORTS
#endif

#define TYPEINFO_H static void * t_data; static _FORCEINLINE void* t() { return &t_data; }
#define TYPEINFO(classname) void* classname::t_data=(void*)&#classname;

#ifdef OS_WIN
#ifdef MSVC
#define BT_EXPORT __declspec(dllexport)
#define BT_IMPORT __declspec(dllimport)
#else
#define BT_EXPORT __attribute__((dllexport))
#define BT_IMPORT __attribute__((dllimport))
#endif
#else /* other */
#define BT_EXPORT __attribute__((visibility("default"))) // use "-fvisibility=hidden" for hide not exports functions
#define BT_IMPORT
#endif

#ifdef BT_EXPORTS
#define BT_API BT_EXPORT
#else
#ifndef BT_LOCAL
#define BT_API BT_IMPORT
#else
#define BT_API
#endif
#endif

#endif /* BTAPI_H_ */
