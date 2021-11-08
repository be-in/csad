/*
 * x86_64cpu.h
 *
 *  Created on: 18.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifdef CPU_BT
#ifndef X86_64CPU_H_
#define X86_64CPU_H_

#include <bt.h>

#ifdef CPU_X86_64

namespace bt {

	struct x86cpuinfo {
		unsigned _int32 flag;
		char name[17];
	};

	_int64 _TSCDCPU();

	void _APICALL cpuInit(x86cpuinfo *info);

}

#endif

#endif /* X86_64CPU_H_ */
#endif