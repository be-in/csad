/*
 * x86_64extension.cpp
 *
 *  Created on: 18.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifdef CPU_BT
#include "x86_64extension.h"

#ifdef CPU_X86_64

#include <bt/os.h>
#include "macrosasm.h"
ARCH_ALL;

#if defined(GCC) || defined(MINGW)
#include "x86_64intrin.h"
#include <x86intrin.h>
#include "../x86/macrosasm.h"
#endif

#if defined(MSVC)
#include <intrin.h>
#endif

#include "x86_64log2.h"

WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

ARCH_SSE2;

#ifdef MSVC
int _APICALL _ILogSizeSSE2(unsigned int _a)
{
	int val=1;
	_a-=val;
	if (_a>0) {
		__m128i v1;
		*(__m128d*)&v1 = _mm_cvtsi32_sd(*(__m128d*)&v1,_a);
		v1 = _mm_slli_epi64(v1,1);
		v1 = _mm_srli_epi64(v1,53);
		val = _mm_cvtsi128_si32(v1);
		val-=0x3FF;
		val=2<<val;
	}
	return val;
}
#else
_NORETURN int _APICALL _ILogSizeSSE2(unsigned int)
{
	EXTLOG2ISIZESSE2;
}
#endif

}

OPTIMIZE_OFF;
WARNING_ENABLE;

ARCH_DEFAULT;

#endif /* CPU_X86_64 */
#endif
