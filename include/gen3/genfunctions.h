/*
 * getfunction.h
 *
 *  Created on: 27.04.2008
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef GEN_FUNCTIONS_H_
#define GEN_FUNCTIONS_H_

#include <gen3/types.h>
#include <gen3/genapi.h>

#ifdef __cplusplus
extern "C" {
#endif

/// @ingroup apiinterface
/// Initialisation generator functions
GEN_API void _APICALL initGen(unsigned int flagMask=0xFFFFFFFF);
/// @ingroup apiinterface
/// Reset for reinitialization functions
GEN_API void _APICALL resetGen();

/// @ingroup apiinterface
/// Genetator functions
#ifdef __cplusplus
extern gen::sFunctionsGen GEN_API genFunctions;
#else
extern sFunctionsGen GEN_API genFunctions;
#endif

#ifdef __cplusplus
}
#endif

#endif /* GEN_FUNCTIONS_H_ */
