/*
 * x86_64extension.h
 *
 *  Created on: 18.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifdef CPU_BT
#ifndef X86_64EXTENTION_H_
#define X86_64EXTENTION_H_

#include <bt.h>

#ifdef CPU_X86_64

namespace bt {

	int _APICALL _ILogSizeSSE2(unsigned int);

}

#endif

#endif /* X86_64CPU_H_ */
#endif