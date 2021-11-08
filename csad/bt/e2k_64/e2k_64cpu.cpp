/*
 * e2k_64cpu.cpp
 *
 *  Created on: 18.09.2013
 *      Author: Пантелеймонов Александр
 */

#include "e2k_64cpu.h"

WARNING_DISABLE;
OPTIMIZE_ON;

#ifdef CPU_E2K_64

#include <time.h>

namespace bt {

	long long _NOINLINE _TSCDCPU()
	{
		asm ("rrd %clkr, %dr0");
//		long long x;
//		asm ("rrd %%clkr, %0" : "=r" (x));
//		return x;
/*		long long nsec_count, nsec_per_tick;
		struct timespec ts1, ts2;

		if (clock_gettime(CLOCK_MONOTONIC, &ts1) != 0) return -1;
		nsec_count = ts1.tv_nsec + ts1.tv_sec * 1000000000;
		if (clock_getres(CLOCK_MONOTONIC, &ts2) != 0) return -1;
		nsec_per_tick = ts2.tv_nsec + ts2.tv_sec * 1000000000;

		return (nsec_count / nsec_per_tick);*/
	}

	unsigned int _NOINLINE _APICALL cpuid(int id,int *data)
	{
		//__cpuid(data,id);
		return data[0];
	}

	void _APICALL cpuInit(e2kcpuinfo * info)
	{
		unsigned int flag;
		int _f[4];
		cpuid(1,_f);
		flag=CPU_e2k_E2K;

		info->flag=flag;
		cpuid(0,(int *)info->name);
	}

}

#endif

OPTIMIZE_OFF;
WARNING_ENABLE;
