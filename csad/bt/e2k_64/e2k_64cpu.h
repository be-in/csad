/*
 * x86cpu.h
 *
 *  Created on: 18.09.2013
 *      Author: Panteleymonov Aleksandr
 */

#ifndef X86_64CPU_H_
#define X86_64CPU_H_

#include <bt.h>

#ifdef CPU_E2K_64

namespace bt {

	struct e2kcpuinfo {
		unsigned _int32 flag;
		char name[17];
	};

	_int64 _TSCDCPU();

	void _APICALL cpuInit(e2kcpuinfo *info);

}

#endif

#endif /* X86CPU_H_ */
