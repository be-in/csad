/*
 * @file function.h
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

///*
// *  Multi-threaded DLL (/MD) - use this mode for exclude jmp call pointer.
// *  Multi-threaded Debug DLL (/MDd) - use this mode for jmp call pointer.
// * 
// *  WARNING - not for use gcc 4.0.0 or older.

#ifndef EXPORT_FUNCTIONS_H_
#define EXPORT_FUNCTIONS_H_

#include <bt/types.h>
#include <bt/btapi.h>

#ifdef __cplusplus
extern "C" {
#endif

/// @ingroup apiinterface
/// Base math functions
#ifdef __cplusplus
extern bt::sFunctionsAPICPU BT_API btFunctions;
#else
extern sFunctionsAPICPU BT_API btFunctions;
#endif

/// @ingroup apiinterface
/// Base math functions
#ifdef __cplusplus
extern bt::sFunctionsMathCPU BT_API matFunctions;
#else
extern sFunctionsMathCPU BT_API matFunctions;
#endif

/// @ingroup apiinterface
/// Base vectors and matrix functions
#ifdef __cplusplus
extern bt::sFunctionsVectorCPU BT_API vecFunctions;
#else
extern sFunctionsVectorCPU BT_API vecFunctions;
#endif

/// @ingroup apiinterface
/// Base numeric array and vectors functions
#ifdef __cplusplus
extern bt::sFunctionsArrayVectorCPU BT_API arvFunctions;
#else
extern sFunctionsArrayVectorCPU BT_API arvFunctions;
#endif

/// @ingroup apiinterface
/// Base extension functions
#ifdef __cplusplus
extern bt::sFunctionsExtensionCPU BT_API extFunctions;
#else
extern sFunctionsExtensionCPU BT_API extFunctions;
#endif

/// @ingroup apiinterface
/// Base array functions
#ifdef __cplusplus
extern bt::sFunctionsArrayCPU BT_API arrFunctions;
#else
extern sFunctionsArrayCPU BT_API arrFunctions;
#endif

/// @ingroup apiinterface
/// Base operator functions
#ifdef __cplusplus
extern bt::sFunctionsObjectCPU BT_API objFunctions;
#else
extern sFunctionsObjectCPU BT_API objFunctions;
#endif

/// @ingroup apiinterface
/// Base render functions
#ifdef __cplusplus
extern bt::sFunctionsRenderCPU BT_API renFunctions;
#else
extern sFunctionsRenderCPU BT_API renFunctions;
#endif

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
namespace bt {
#endif

#define fsqrt(a) matFunctions.FSqrt((a))
#define dsqrt(a) matFunctions.DSqrt((a))
#define ffastinvsqrt(a) matFunctions.FFastInvSqrt((a))
#define dfastinvsqrt(a) matFunctions.DFastInvSqrt((a))
#define fsincos(a,b,c) matFunctions.FSinCos((a),(b),(c))
#define dsincos(a,b,c) matFunctions.DSinCos((a),(b),(c))
#define farctg(b,c) matFunctions.FArcTg((b),(c))
#define darctg(b,c) matFunctions.DArcTg((b),(c))
#define setBit(m,a,b) extFunctions.SetBit((a) & 0xff,b,m)
#define getBit(m,a) extFunctions.GetBit((a) & 0xff,(m))
#define ftrunc(a) matFunctions.FTrunc((a))
#define dtrunc(a) matFunctions.DTrunc((a))
#define fround(a) matFunctions.FRound((a))
#define dround(a) matFunctions.DRound((a))
#define ilog2(a) matFunctions.ILog2((a))
#define flog2(a) matFunctions.FLog2((a))
#define dlog2(a) matFunctions.DLog2((a))

#define fmemcpy(a,b,c) extFunctions.MoveMem((void*)(b),(void*)(a),(c))
#define fmemcmp(a,b,c) extFunctions.CmpMem((void*)(a),(void*)(b),(c))
#define fmemclean(a,c) extFunctions.CleanMem((void*)(a),(c))
#define fmemswap(a,b,c) extFunctions.SwapMem((void*)(b),(void*)(a),(c))

#ifdef __cplusplus
}
#endif

#endif /* FUNCTIONS_H_ */
