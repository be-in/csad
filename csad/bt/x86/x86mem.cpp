/*
 * x86mem.cpp
 *
 *  Created on: 17.10.2013
 *      Author: Пантелеймонов А
 */

#ifdef CPU_BT

#include "x86mem.h"
#include "x86mem_clean.h"
#include "x86mem_move.h"
#include "x86mem_swap.h"
#include "x86mem_stos.h"
#include "macrosasm.h"

WARNING_DISABLE;
OPTIMIZE_ON;

#ifdef CPU_X86_32

namespace bt {

// ************** mem CPU *******************

void _NAKED _APICALL _CleanMemCPU(void *, unsigned int)
{
	CLEANMEMCPU_STD;
	RET_2;
}

void _NAKED _APICALL _MoveMemCPU(void *,void *, unsigned int)
{
	MOVEMEMCPU_STD;
	RET_3;
}

void _NAKED _APICALL _MoveBackCPU(void *,void *, unsigned int)
{
	MOVEBACKCPU_STD;
	RET_3;
}

void _NAKED _APICALL _SwapMemCPU(void *,void *, unsigned int)
{
	SWAPMEMCPU_STD;
	RET_3;
}

void _NAKED _APICALL _StosSMEMCPU(void *,unsigned int, unsigned int)
{
	STOSSMEMCPU_STD;
	RET_3;
}

void _NAKED _APICALL _StosIMEMCPU(void *,unsigned int, unsigned int)
{
	STOSIMEMCPU_STD;
	RET_3;
}

// ************** mem SSE *******************

void _NAKED _APICALL _StosIMEMSSE(void *,unsigned int, unsigned int)
{
	STOSIMEMSSE_STD;
	RET_3;
}

// ************** mem SSE2 *******************

void _NAKED _APICALL _CleanMemSSE2(void *, unsigned int)
{
	CLEANMEMSSE2_STD;
}

void _NAKED _APICALL _MoveMemSSE2(void *,void *,unsigned int)
{
	MOVEMEMSSE2_STD;
}

void _NAKED _APICALL _MoveBackSSE2(void *,void *,unsigned int)
{
	MOVEBACKSSE2_STD;
}

void _NAKED _APICALL _StosSMEMSSE2(void *,unsigned int, unsigned int)
{
	//STOSSMEMSSE2_STD;
}

void _NAKED _APICALL _StosIMEMSSE2(void *,unsigned int, unsigned int)
{
	STOSIMEMSSE2_STD;
}

// ************** mem SSE3 *******************

void _NAKED _APICALL _MoveMemSSE3(void *,void *,unsigned int)
{
	SAVE_5_PARAMETERS;
	PARAMETERS_ESP_EDX_EAX_ECX;
	MOVEMEMSSE3;
	LOAD_5_PARAMETERS;
	RET_3;
}

/*void _NAKED _STDCALL _MoveMemSSE3(void *,void *,unsigned int)
{
	SAVE_5_PARAMETERS;
	PARAMETERS_ESP_EDX_EAX_ECX;
	MOVEMEMSSE3;
	LOAD_5_PARAMETERS;
	RET_3;
}*/

void _NAKED _APICALL _StosIMEMSSE3(void *,unsigned int, unsigned int)
{
	STOSIMEMSSE3_STD;
	RET_3;
}

// ************** mem AVX *******************

void _NAKED _APICALL _CleanMemAVX(void *, unsigned int)
{
	CLEANMEMAVX_STD;
}

void _NAKED _APICALL _MoveMemAVX(void *,void *,unsigned int)
{
	MOVEMEMAVX_STD;
}

}

#endif

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif