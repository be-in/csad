/*
 * csadapi.h
 *
 *  Created on: 10.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich
 */

#ifndef CSADAPI_H_
#define CSADAPI_H_

#include <bt/os.h>

#if defined(CSAD_LIB) || defined(LIB_CSAD)
#define CSAD_EXPORTS
#endif

#ifdef OS_WIN
#ifdef MSVC
	#define CSAD_EXPORT __declspec(dllexport)
	#define CSAD_IMPORT __declspec(dllimport)
#else
	#define CSAD_EXPORT __attribute__((dllexport))
	#define CSAD_IMPORT __attribute__((dllimport))
#endif
#else /* other */
	#define CSAD_EXPORT __attribute__((visibility("default"))) // use "-fvisibility=hidden" for hide not exports functions
	#define CSAD_IMPORT
#endif

#ifdef CSAD_EXPORTS
	#define CSAD_API CSAD_EXPORT
#else
#ifndef CSAD_LOCAL
	#define CSAD_API CSAD_IMPORT
#else
	#define CSAD_API
#endif
#endif

#endif /* CSADAPI_H_ */
