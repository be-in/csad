/*
 * genapi.h
 *
 *  Created on: 16.12.2013
 *      Author: Пантелеймонов А
 */

#ifndef GENAPI_H_
#define GENAPI_H_

#if defined(CSAD_LIB) || defined(LIB_CSAD)
#define GEN_EXPORTS
#endif

#ifdef OS_WIN
#ifdef MSVC
#define GEN_EXPORT __declspec(dllexport)
#define GEN_IMPORT __declspec(dllimport)
#else
#define GEN_EXPORT __attribute__((dllexport))
#define GEN_IMPORT __attribute__((dllimport))
#endif
#else /* other */
#define GEN_EXPORT __attribute__((visibility("default"))) // use "-fvisibility=hidden" for hide not exports functions
#define GEN_IMPORT
#endif

#ifdef GEN_EXPORTS
#define GEN_API GEN_EXPORT
#else
#ifndef CSAD_LOCAL
#define GEN_API GEN_IMPORT
#else
#define GEN_API
#endif
#endif

#endif /* GENAPI_H_ */
