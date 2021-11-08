/*
 * x86render.cpp
 *
 *  Created on: 01.11.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifdef CPU_BT

#include "x86render.h"
#include "x86render_span.h"
#include "x86render_texel.h"
#include "macrosasm.h"

WARNING_DISABLE;
OPTIMIZE_ON;

#ifdef CPU_X86_32

namespace bt {

// ************** vector span draw CPU function *******************

	void _NAKED _APICALL _S4AFdrawCPU(void *)
	{
		RENDERPSPAN4AFCPU_STD
		RET_1;
	}

	void _NAKED _APICALL _S4AFDLdrawCPU(void *)
	{
		RENDERPSPAN4AFDCPU_STD;
		RET_1;
	}

	// ************** vector span draw SSE function *******************

	void _NAKED _APICALL _S4AFDLdrawSSE(void *)
	{
		RENDERPSPAN4AFDSSE_STD;
		RET_1;
	}

	void _NAKED _APICALL _S4AFSdrawSSE2(void *)
	{
		RENDERPSPAN4AFSSSE2_STD;
		RET_1;
	}

	void _NAKED _APICALL _S4AFDLSdrawSSE2(void *)
	{
		RENDERPSPAN4AFDSSSE2_STD;
		RET_1;
	}

	// ************** vector Texel SSE3 function *******************

	void _NAKED _APICALL _V3BHalfTexelSSE3(void *,void *,int)
	{
		RENDERPV3BHALFTEXELSSE3_STD;
		RET_3;
	}

	void _NAKED _APICALL _V4BHalfTexelSSE3(void *,void *,int)
	{
		RENDERPV4BHALFTEXELSSE3_STD;
		RET_3;
	}

	void _NAKED _APICALL _V3BTexelSSE3(void *,void *,int,float,float)
	{
		RENDERPV3BTEXELSSE3_STD;
		RET_5;
	}

	void _NAKED _APICALL _V4BTexelSSE3(void *,void *,int,float,float)
	{
		RENDERPV4BTEXELSSE3_STD;
		RET_5;
	}
}

#endif

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif