/*
 * x86service.h
 *
 *  Created on: 18.09.2014
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef X86SERVICE_H_
#define X86SERVICE_H_

#include <bt.h>

#ifdef CPU_X86_32

namespace bt {

void _APICALL __writeAddr(void*write, void*fun);

}

#endif

#endif /* X86VECTOR_H_ */