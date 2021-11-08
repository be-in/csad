/*
 * wininternalfunctions.cpp
 *
 *  Created on: 14.08.2014
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include "csad/platform/internalfunctions.h"

#if defined (OS_WIN)

OPTIMIZE_ON;

namespace bt {

int _STDCALL WriteMe(void *addr, char* wb,int size)
{
	HANDLE h=OpenProcess(PROCESS_VM_OPERATION |PROCESS_VM_WRITE,true,GetCurrentProcessId());
	return WriteProcessMemory(h, addr,wb,size,NULL);
}

}

OPTIMIZE_OFF;

#endif