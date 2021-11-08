/*
 * x86container.h
 *
 *  Created on: 25.10.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef X86CONTAINER_H_
#define X86CONTAINER_H_

#include <bt.h>

#ifdef CPU_X86_32

OPTIMIZE_ON;

namespace bt {

void ** _APICALL _MPFindCPU(void ** ,void *);
void ** _APICALL _MPFindSSE2(void ** ,void *);

};

OPTIMIZE_OFF;

#endif

#endif