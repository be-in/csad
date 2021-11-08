/*
 * x86functions.cpp
 *
 *  Created on: 18.09.2013
 *      Author: Пантелеймонов Александр
 */

#include "e2k_64functions.h"
#include <bt.h>

#ifdef CPU_E2K_64

#include "e2k_64math.h"
#include "e2k_64vector.h"

WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

e2kcpuinfo cpuinfo;

void inite2k_64(unsigned int flagMask)
{
	cpuInit(&cpuinfo);
	cpuinfo.flag&=flagMask;
}

void cpuinfotostring(char *string)
{
	char *s=string;
	if ((cpuinfo.flag&CPU_e2k_E2K)!=0) {
		extFunctions.MoveMem((void*)"E2K/",s,4);
		s+=4;
	}
	*s=0;
}

void inite2k_64Math(void* _conteiner)
{
	sFunctionsMathCPU *as=(sFunctionsMathCPU *)_conteiner;

	if ((cpuinfo.flag&CPU_e2k_E2K)!=0) {
		as->FSqrt=(tfSTDCALL_float_FUNC_float)_FsqrtE2K;
		as->DSqrt=(tfSTDCALL_double_FUNC_double)_DsqrtE2K;
	}
}

void inite2k_64Vector(void*_conteiner)
{
	sFunctionsVectorCPU *as=(sFunctionsVectorCPU *)_conteiner;
	
	if ((cpuinfo.flag&CPU_e2k_E2K)!=0) {
		as->V2FAdd=(tfSTDCALL_PROC_p_p_p)&_V2FAddE2K;
		as->V3FAdd=(tfSTDCALL_PROC_p_p_p)&_V3FAddE2K;
		as->V4FAdd=(tfSTDCALL_PROC_p_p_p)&_V4FAddE2K;
		as->V2DAdd=(tfSTDCALL_PROC_p_p_p)&_V2DAddE2K;
		as->V3DAdd=(tfSTDCALL_PROC_p_p_p)&_V3DAddE2K;
		as->V4DAdd=(tfSTDCALL_PROC_p_p_p)&_V4DAddE2K;

		as->V2FSub=(tfSTDCALL_PROC_p_p_p)&_V2FSubE2K;
		as->V3FSub=(tfSTDCALL_PROC_p_p_p)&_V3FSubE2K;
		as->V4FSub=(tfSTDCALL_PROC_p_p_p)&_V4FSubE2K;
		as->V2DSub=(tfSTDCALL_PROC_p_p_p)&_V2DSubE2K;
		as->V3DSub=(tfSTDCALL_PROC_p_p_p)&_V3DSubE2K;
		as->V4DSub=(tfSTDCALL_PROC_p_p_p)&_V4DSubE2K;

		//as->V2FDot=(tfSTDCALL_float_FUNC_p_p)&_V2FDotE2K;
		//as->V4FDot=(tfSTDCALL_float_FUNC_p_p)&_V4FDotE2K;
		//as->V4DDot=(tfSTDCALL_double_FUNC_p_p)&_V4DDotE2K;

		as->V2FNormal=(tfSTDCALL_PROC_p_p)&_V2FNormalE2K;
		as->V3FNormal=(tfSTDCALL_PROC_p_p)&_V3FNormalE2K;
		as->V4FNormal=(tfSTDCALL_PROC_p_p)&_V4FNormalE2K;
		as->V2DNormal=(tfSTDCALL_PROC_p_p)&_V2DNormalE2K;
		as->V3DNormal=(tfSTDCALL_PROC_p_p)&_V3DNormalE2K;
		as->V4DNormal=(tfSTDCALL_PROC_p_p)&_V4DNormalE2K;
	}
}

void inite2k_64ArrayVector(void*_conteiner)
{
	sFunctionsArrayVectorCPU *as=(sFunctionsArrayVectorCPU *)_conteiner;

}

void inite2k_64Extention(void*_conteiner)
{
	sFunctionsExtentionCPU *as=(sFunctionsExtentionCPU *)_conteiner;
	
	as->TSC=(tfSTDCALL_long_FUNC)&_TSCDCPU;
}

void inite2k_64Render(void*_conteiner)
{
	sFunctionsRenderCPU *as=(sFunctionsRenderCPU *)_conteiner;
	as->version=0;

}

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif

