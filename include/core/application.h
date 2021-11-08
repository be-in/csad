/*
 * application.h
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <core/csadapi.h>
#include <core/core.h>

extern "C" {

CSAD_API void _APICALL csadStart();
CSAD_API void _APICALL csadInit(char* config);
//CSAD_API void _STDCALL csadInit(const char* config);
CSAD_API void _APICALL csadRun();
CSAD_API void _APICALL csadDone();
CSAD_API void _APICALL csadQuit();

}

#endif /* APPLICATION_H_ */
