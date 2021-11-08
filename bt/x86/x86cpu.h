/*
 * x86cpu.h
 *
 *  Created on: 18.09.2013
 *      Author: Пантелеймонов Александр
 */

#ifndef X86CPU_H_
#define X86CPU_H_

#include <bt.h>

#ifdef CPU_X86_32

namespace bt {

	struct x86cpuinfo {
		unsigned _int32 flag;
		char name[17];
	};

	_int64 _TSCDCPU();

	void _APICALL cpuInit(x86cpuinfo *info);

}

#endif

#endif /* X86CPU_H_ */
