/*
 * corefunction.h
 *
 *  Created on: 27.08.2014
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef CORE_FUNCTIONS_H_
#define CORE_FUNCTIONS_H_

#include <core/types.h>
#include <core/csadapi.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
extern csad::sFunctionsCore CSAD_API coreFunctions;
#else
extern sFunctionsCore CSAD_API coreFunctions;
#endif

#ifdef __cplusplus
}
#endif

#endif /* CORE_FUNCTIONS_H_ */
