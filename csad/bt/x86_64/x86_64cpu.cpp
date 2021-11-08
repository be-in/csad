/*
 * x86_64cpu.cpp
 *
 *  Created on: 18.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifdef CPU_BT
#include "x86_64cpu.h"

#ifdef CPU_X86_64

#include "macrosasm.h"
ARCH_ALL;

#if defined(GCC) || defined(MINGW)
#include <x86intrin.h>
#include <cpuid.h>
#include "../x86/macrosasm.h"
#endif

#if defined(MSVC)
#include <intrin.h>
#endif

WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

ARCH_DEFAULT;

#ifdef MSVC
	_int64 _NOINLINE _TSCDCPU()
	{
		return __rdtsc();
	}
#else
	_int64 _NOINLINE _TSCDCPU()
	{
		_BEGIN_ASM \
		_LINE2( 0x0F,0x31 )           /* rdtsc  */ \
		_LINE4( 0x48,0xC1,0xE2,0x20 ) /* shl         rdx,20h  */ \
		_LINE3( 0x48,0x0B,0xC2 )      /* or          rax,rdx  */ \
		_LINE1( 0xC3 )                /* ret  */ \
		_END_ASM
	}
#endif

	unsigned _int32 _NOINLINE _APICALL cpuid(_int32 id,_int32 *data)
	{
		#ifdef GCC
		__cpuid(id,data[0],data[1],data[2],data[3]);
		#endif
		#ifdef MSVC
		__cpuid((int*)data,id);
		#endif
		return data[0];
	}

	unsigned int _NOINLINE _APICALL cpuidex(_int32 id,_int32 ex,_int32 *data)
	{
		#ifdef GCC
		__cpuid_count(id,ex,data[0],data[1],data[2],data[3]);
		#endif
		#ifdef MSVC
		__cpuidex((int*)data,id,ex);
		#endif
		return data[0];
	}

	void _APICALL cpuInit(x86cpuinfo * info)
	{
		unsigned _int32 flag;
		_int32 _f[4];
		cpuid(1,_f);
		flag=0;
		if ((_f[3] & 0x0000001)!=0) flag|=CPU_x86_FPU;
		if ((_f[3] & 0x0000010)!=0) flag|=CPU_x86_RDTSC;
		if ((_f[3] & 0x0000020)!=0) flag|=CPU_x86_RDMSR;
		if ((_f[3] & 0x0000100)!=0) flag|=CPU_x86_CMPXCHG8B;
		if ((_f[3] & 0x0008000)!=0) flag|=CPU_x86_CMOV;
		if ((_f[3] & 0x0800000)!=0) flag|=CPU_x86_MMX;
		if ((_f[3] & 0x1000000)!=0) flag|=CPU_x86_FXSR;
		if ((_f[3] & 0x2000000)!=0) flag|=CPU_x86_SSE;
		if ((_f[3] & 0x4000000)!=0) flag|=CPU_x86_SSE2;
		if ((_f[2] & 0x0000001)!=0) flag|=CPU_x86_SSE3;
		if ((_f[2] & 0x0000200)!=0) flag|=CPU_x86_SSSE3;
		if ((_f[2] & 0x0001000)!=0) flag|=CPU_x86_FMA;
		if ((_f[2] & 0x0180000)==0x0180000) flag|=CPU_x86_SSE4;
		if ((_f[2] & 0x2000000)!=0) flag|=CPU_x86_AES;
		if ((_f[2] & 0x4000000)!=0) flag|=CPU_x86_XSAVE;
		if ((_f[2] & 0x8000000)!=0) flag|=CPU_x86_OSXSAVE;
		if ((_f[2] & 0x10000000)!=0) flag|=CPU_x86_AVX;

		cpuidex(7,0,_f);
		if ((_f[1] & 0x0000020)!=0) flag|=CPU_x86_AVX2;

		unsigned _int32 ext=cpuid(0x80000000,_f);
		if (ext>0x80000000) {
			_int32 _a[4];
			cpuid(0x80000001,_a);
			if ((_a[3] & 0x20000000)!=0) flag|=CPU_x86_64BIT;
			if ((_a[3] & 0x00800000)!=0) flag|=CPU_x86_MMXPLUS;
			if ((_a[3] & 0x40000000)!=0) flag|=CPU_x86_3DNOWPLUS;
			if ((_a[3] & 0x80000000)!=0) flag|=CPU_x86_3DNOW;
			if ((_a[2] & 0x00000040)!=0) flag|=CPU_x86_SSE4A;
			if ((_a[2] & 0x00000800)!=0) flag|=CPU_x86_SSE5;
		}

		if (ext>0x80000019) {
			_int32 _a1a[4];
			cpuid(0x8000001A,_a1a);
			if ((_a1a[0] & 0x00000001)!=0) flag|=CPU_x86_128BITFPU;
			if ((_a1a[0] & 0x00000002)!=0) flag|=CPU_x86_FASTMOVU;
		}

		info->flag=flag;
		cpuid(0,(_int32 *)info->name);
	}

}

OPTIMIZE_OFF;
WARNING_ENABLE;

ARCH_DEFAULT;

#endif /* CPU_X86_64 */
#endif
