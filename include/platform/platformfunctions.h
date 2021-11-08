/*
 * @file platformfunction.h
 *
 *  Created on: 27.04.2008
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef PLATFORM_FUNCTIONS_H_
#define PLATFORM_FUNCTIONS_H_

#include <platform/types.h>
#include <platform/platformapi.h>

#ifdef __cplusplus
extern "C" {
#endif

/// @ingroup apiinterface
/// Initialisation platform functions
PLATFORM_API void _APICALL initPlatform(unsigned _int32 flagMask = 0xFFFFFFFF);
/// @ingroup apiinterface
/// Reset for reinitialization functions
PLATFORM_API void _APICALL resetPlatform();
/// @ingroup apiinterface
/// Set functions for display.
PLATFORM_API void _APICALL initDisplayRender(void *content, unsigned _int32 mode = 0);

/// @ingroup apiinterface
/// Genetator functions
#ifdef __cplusplus
extern csad::sFunctionsPlatform PLATFORM_API platformFunctions;
#else
extern sFunctionsPlatform PLATFORM_API platformFunctions;
#endif

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_FUNCTIONS_H_ */
