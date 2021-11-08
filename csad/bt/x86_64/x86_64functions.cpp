/*
 * x86_64functions.cpp
 *
 *  Created on: 18.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifdef CPU_BT
#include "x86_64functions.h"
#include <bt.h>
#include "x86_64mem.h"
#include "x86_64math.h"
#include "x86_64vector.h"
#include "x86_64matrix.h"
#include "x86_64extension.h"
#include "x86_64quaternion.h"

#ifdef CPU_X86_64

WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

x86cpuinfo cpuinfo;

void initx86_64(unsigned int flagMask)
{
	cpuInit(&cpuinfo);
	cpuinfo.flag&=flagMask;
}

void cpuinfotostring(char *string)
{
	char *s=string;
	if ((cpuinfo.flag&CPU_x86_FPU)!=0) {
		extFunctions.MoveMem((void*)"FPU/",s,4);
		s+=4;
	}
	if ((cpuinfo.flag&CPU_x86_MMX)!=0) {
		extFunctions.MoveMem((void*)"MMX/",s,4);
		s+=4;
	}
	if ((cpuinfo.flag&CPU_x86_MMXPLUS)!=0) {
		extFunctions.MoveMem((void*)"MMXPLUS/",s,8);
		s+=8;
	}
	if ((cpuinfo.flag&CPU_x86_3DNOW)!=0) {
		extFunctions.MoveMem((void*)"3DNOW/",s,6);
		s+=6;
	}
	if ((cpuinfo.flag&CPU_x86_3DNOWPLUS)!=0) {
		extFunctions.MoveMem((void*)"3DNOWPLUS/",s,10);
		s+=10;
	}
	if ((cpuinfo.flag&CPU_x86_SSE)!=0) {
		extFunctions.MoveMem((void*)"SSE/",s,4);
		s+=4;
	}
	if ((cpuinfo.flag&CPU_x86_SSE2)!=0) {
		extFunctions.MoveMem((void*)"SSE2/",s,5);
		s+=5;
	}
	if ((cpuinfo.flag&CPU_x86_SSSE3)!=0) {
		extFunctions.MoveMem((void*)"SSSE3/",s,6);
		s+=6;
	}
	if ((cpuinfo.flag&CPU_x86_SSE3)!=0) {
		extFunctions.MoveMem((void*)"SSE3/",s,5);
		s+=5;
	}
	if ((cpuinfo.flag&CPU_x86_SSE4)!=0) {
		extFunctions.MoveMem((void*)"SSE4/",s,5);
		s+=5;
	}
	if ((cpuinfo.flag&CPU_x86_SSE4A)!=0) {
		extFunctions.MoveMem((void*)"SSE4A/",s,6);
		s+=6;
	}
	if ((cpuinfo.flag&CPU_x86_SSE5)!=0) {
		extFunctions.MoveMem((void*)"SSE5/",s,5);
		s+=5;
	}
	if ((cpuinfo.flag&CPU_x86_AVX)!=0) {
		extFunctions.MoveMem((void*)"AVX/",s,4);
		s+=4;
	}
	if ((cpuinfo.flag&CPU_x86_FMA)!=0) {
		extFunctions.MoveMem((void*)"FMA/",s,4);
		s+=4;
	}
	if ((cpuinfo.flag&CPU_x86_AVX2)!=0) {
		extFunctions.MoveMem((void*)"AVX2/",s,5);
		s+=5;
	}
	if ((cpuinfo.flag&CPU_x86_AES)!=0) {
		extFunctions.MoveMem((void*)"AES/",s,4);
		s+=5;
	}
	if ((cpuinfo.flag&CPU_x86_64BIT)==0) {
		extFunctions.MoveMem((void*)"32BIT/",s,6);
		s+=6;
	}
	if ((cpuinfo.flag&CPU_x86_64BIT)!=0) {
		extFunctions.MoveMem((void*)"64BIT/",s,6);
		s+=6;
	}
	if ((cpuinfo.flag&CPU_x86_128BITFPU)!=0) {
		extFunctions.MoveMem((void*)"128BITFPU/",s,10);
		s+=10;
	}
	*s=0;
}

void initx86_64BT(void* _conteiner)
{
	bt::sFunctionsAPICPU *as=(bt::sFunctionsAPICPU *)_conteiner;
	as->version=0;

	if ((cpuinfo.flag&CPU_x86_RDTSC)!=0) {
		as->TSC=(tfSTDCALL_long_FUNC)&_TSCDCPU;
	}
}

void initx86_64Math(void* _conteiner)
{
	sFunctionsMathCPU *as=(sFunctionsMathCPU *)_conteiner;
	as->version=0;
	
	if ((cpuinfo.flag&CPU_x86_SSE)!=0) {
		as->FSqrt=(tfSTDCALL_float_FUNC_float)&_FsqrtSSE;
		as->FFastInvSqrt=(tfSTDCALL_float_FUNC_float)&_FFastInvSqrtSSE;
		as->FSinCos=(tfSTDCALL_PROC_float_p_p)&_FSinCosSSE;
		as->FArcTg=(tfSTDCALL_float_FUNC_float_float)&_FArcTgSSE;
		as->FExp=(tfSTDCALL_float_FUNC_float)_FExpSSE;
	}

	if ((cpuinfo.flag&CPU_x86_SSE2)!=0) {
		as->DSqrt=(tfSTDCALL_double_FUNC_double)&_DsqrtSSE2;
		as->DFastInvSqrt=(tfSTDCALL_double_FUNC_double)&_DFastInvSqrtSSE2;
		as->DExp=(tfSTDCALL_double_FUNC_double)_DExpSSE2;
		as->ILog2=(bt::tfSTDCALL_int_FUNC_int)&bt::_ILog2SSE2;
	}

	if ((cpuinfo.flag&CPU_x86_SSE3)!=0) {
		as->FSinCos=(tfSTDCALL_PROC_float_p_p)&_FSinCosSSE3;
		as->FArcTg=(tfSTDCALL_float_FUNC_float_float)&_FArcTgSSE3;
		//as->DArcTg=(tfSTDCALL_double_FUNC_double_double)&_DArcTgSSE3;
	}
}

void initx86_64Vector(void*_conteiner)
{
	sFunctionsVectorCPU *as=(sFunctionsVectorCPU *)_conteiner;
	as->version=0;
	
	if ((cpuinfo.flag&CPU_x86_SSE)!=0) {
		as->V2FAdd=(tfSTDCALL_PROC_p_p_p)&_V2FAddSSE;
		as->V3FAdd=(tfSTDCALL_PROC_p_p_p)&_V3FAddSSE;
		as->V4FAdd=(tfSTDCALL_PROC_p_p_p)&_V4FAddSSE;
		
		as->V2FSub=(tfSTDCALL_PROC_p_p_p)&_V2FSubSSE;
		as->V3FSub=(tfSTDCALL_PROC_p_p_p)&_V3FSubSSE;

		as->V2FScale=(tfSTDCALL_PROC_p_p_float)&_V2FScaleSSE;
		as->V3FScale=(tfSTDCALL_PROC_p_p_float)&_V3FScaleSSE;
		as->V4FScale=(tfSTDCALL_PROC_p_p_float)&_V4FScaleSSE;

		as->V2FMul=(tfSTDCALL_PROC_p_p_p)&_V2FMulSSE;
		as->V3FMul=(tfSTDCALL_PROC_p_p_p)&_V3FMulSSE;

		as->V2FDiv=(tfSTDCALL_PROC_p_p_p)&_V2FDivSSE;
		as->V3FDiv=(tfSTDCALL_PROC_p_p_p)&_V3FDivSSE;

		as->V3FCross=(tfSTDCALL_PROC_p_p_p)&_V3FCrossSSE;

		as->V2FNormal=(tfSTDCALL_PROC_p_p)&_V2FNormalSSE;
		as->V3FNormal=(tfSTDCALL_PROC_p_p)&_V3FNormalSSE;
		as->V4FNormal=(tfSTDCALL_PROC_p_p)&_V4FNormalSSE;

		as->V2FFastNormal=(tfSTDCALL_PROC_p_p)&_V2FFastNormalSSE;
		as->V3FFastNormal=(tfSTDCALL_PROC_p_p)&_V3FFastNormalSSE;
		as->V4FFastNormal=(tfSTDCALL_PROC_p_p)&_V4FFastNormalSSE;

		as->V2FLerp=(tfSTDCALL_PROC_p_p_p_float)&_V2FLerpSSE;
		as->V3FLerp=(tfSTDCALL_PROC_p_p_p_float)&_V3FLerpSSE;
		as->V4FLerp=(tfSTDCALL_PROC_p_p_p_float)&_V4FLerpSSE;

		as->V3FAngle=(tfSTDCALL_float_FUNC_p_p)&_V3FAngleSSE;

		as->V2FTransform=(tfSTDCALL_PROC_p_p_p)&_V2FTransformSSE;
		as->V3FTransform=(tfSTDCALL_PROC_p_p_p)&_V3FTransformSSE;
		as->V4FTransform=(tfSTDCALL_PROC_p_p_p)&_V4FTransformSSE;

		as->V2FMMul=(tfSTDCALL_PROC_p_p_p)&_V2FMMulSSE;
		as->V3FMMul=(tfSTDCALL_PROC_p_p_p)&_V3FMMulSSE;
		as->V4FMMul=(tfSTDCALL_PROC_p_p_p)&_V4FTransformSSE;

		as->QFAdd=(tfSTDCALL_PROC_p_p_p)&_V4FAddSSE;

		as->M4FTranslate=(tfSTDCALL_PROC_p_p)&_M4FTranslateSSE;
		as->M4FScale=(tfSTDCALL_PROC_p_p)&_M4FScaleSSE;

		//as->M4FTRS=(tfSTDCALL_PROC_p_p_p_p)&_M4FTRSSSE;
	}

	if ((cpuinfo.flag&CPU_x86_SSE2)!=0) {
		as->V4R32=(tfSTDCALL_PROC_p_p)&_V4R32SSE3;
		as->V4R64=(tfSTDCALL_PROC_p_p)&_V4R64SSE3;

		as->V2FAdd=(tfSTDCALL_PROC_p_p_p)&_V2FAddSSE2;
		as->V4FAdd=(tfSTDCALL_PROC_p_p_p)&_V4FAddSSE2;
		as->V2DAdd=(tfSTDCALL_PROC_p_p_p)&_V2DAddSSE2;
		as->V3DAdd=(tfSTDCALL_PROC_p_p_p)&_V3DAddSSE2;
		as->V4DAdd=(tfSTDCALL_PROC_p_p_p)&_V4DAddSSE2;

		as->V2FSub=(tfSTDCALL_PROC_p_p_p)&_V2FSubSSE2;
		as->V4FSub=(tfSTDCALL_PROC_p_p_p)&_V4FSubSSE2;
		as->V2DSub=(tfSTDCALL_PROC_p_p_p)&_V2DSubSSE2;
		as->V3DSub=(tfSTDCALL_PROC_p_p_p)&_V3DSubSSE2;
		as->V4DSub=(tfSTDCALL_PROC_p_p_p)&_V4DSubSSE2;

		as->V2DScale=(tfSTDCALL_PROC_p_p_double)&_V2DScaleSSE2;
		as->V3DScale=(tfSTDCALL_PROC_p_p_double)&_V3DScaleSSE2;
		as->V4DScale=(tfSTDCALL_PROC_p_p_double)&_V4DScaleSSE2;

		as->V2FMul=(tfSTDCALL_PROC_p_p_p)&_V2FMulSSE2;
		as->V4FMul=(tfSTDCALL_PROC_p_p_p)&_V4FMulSSE2;
		as->V2DMul=(tfSTDCALL_PROC_p_p_p)&_V2DMulSSE2;
		as->V3DMul=(tfSTDCALL_PROC_p_p_p)&_V3DMulSSE2;
		as->V4DMul=(tfSTDCALL_PROC_p_p_p)&_V4DMulSSE2;

		as->V2FDiv=(tfSTDCALL_PROC_p_p_p)&_V2FDivSSE2;
		as->V4FDiv=(tfSTDCALL_PROC_p_p_p)&_V4FDivSSE2;
		as->V2DDiv=(tfSTDCALL_PROC_p_p_p)&_V2DDivSSE2;
		as->V3DDiv=(tfSTDCALL_PROC_p_p_p)&_V3DDivSSE2;
		as->V4DDiv=(tfSTDCALL_PROC_p_p_p)&_V4DDivSSE2;

		as->V2DNormal=(tfSTDCALL_PROC_p_p)&_V2DNormalSSE2;
		as->V3DNormal=(tfSTDCALL_PROC_p_p)&_V3DNormalSSE2;
		as->V4DNormal=(tfSTDCALL_PROC_p_p)&_V4DNormalSSE2;

		as->V2DFastNormal=(tfSTDCALL_PROC_p_p)&_V2DFastNormalSSE2;
		as->V3DFastNormal=(tfSTDCALL_PROC_p_p)&_V3DFastNormalSSE2;
		as->V4DFastNormal=(tfSTDCALL_PROC_p_p)&_V4DFastNormalSSE2;

		as->V2DLerp=(tfSTDCALL_PROC_p_p_p_double)&_V2DLerpSSE2;
		as->V3DLerp=(tfSTDCALL_PROC_p_p_p_double)&_V3DLerpSSE2;
		as->V4DLerp=(tfSTDCALL_PROC_p_p_p_double)&_V4DLerpSSE2;

		//as->V2DReflect=(tfSTDCALL_PROC_p_p_p)&_V2DReflectSSE2;
		//as->V3DReflect=(tfSTDCALL_PROC_p_p_p)&_V3DReflectSSE2;

		as->V2FTransform=(tfSTDCALL_PROC_p_p_p)&_V2FTransformSSE2;
		as->V2DTransform=(tfSTDCALL_PROC_p_p_p)&_V2DTransformSSE2;

		as->QFAdd=(tfSTDCALL_PROC_p_p_p)&_V4FAddSSE2;

		as->M4DTranslate=(tfSTDCALL_PROC_p_p)&_M4DTranslateSSE2;
		as->M4DScale=(tfSTDCALL_PROC_p_p)&_M4DScaleSSE2;
	}

	if ((cpuinfo.flag&CPU_x86_SSE3)!=0) {
		as->V4FAdd=(tfSTDCALL_PROC_p_p_p)&_V4FAddSSE3;

		as->V3FAngle=(tfSTDCALL_float_FUNC_p_p)&_V3FAngleSSE3;

		as->QFAdd=(tfSTDCALL_PROC_p_p_p)&_V4FAddSSE3;

		as->QDMul=(tfSTDCALL_PROC_p_p_p)&_QDMulSSE3;

		as->M4FMul=(tfSTDCALL_PROC_p_p_p)&_M4FMulSSE3;
	}

	if ((cpuinfo.flag&CPU_x86_SSE4)!=0) {
		as->V4FAdd=(tfSTDCALL_PROC_p_p_p)&_V4FAddSSE4;

		as->V4FScale=(tfSTDCALL_PROC_p_p_float)&_V4FScaleSSE4;
		as->V2DScale=(tfSTDCALL_PROC_p_p_double)&_V2DScaleSSE4;
		as->V4DScale=(tfSTDCALL_PROC_p_p_double)&_V4DScaleSSE4;

		as->V2Fmul2NRound=(tfSTDCALL_PROC_p_p_int)&_V2Fmul2NRoundSSE4;
		as->V3Fmul2NRound=(tfSTDCALL_PROC_p_p_int)&_V3Fmul2NRoundSSE4;
		as->V4Fmul2NRound=(tfSTDCALL_PROC_p_p_int)&_V4Fmul2NRoundSSE4;

		as->V2FDot=(tfSTDCALL_float_FUNC_p_p)&_V2FDotSSE4;
		as->V3FDot=(tfSTDCALL_float_FUNC_p_p)&_V3FDotSSE4;
		as->V4FDot=(tfSTDCALL_float_FUNC_p_p)&_V4FDotSSE4;
		as->V2DDot=(tfSTDCALL_double_FUNC_p_p)&_V2DDotSSE4;
		as->V3DDot=(tfSTDCALL_double_FUNC_p_p)&_V3DDotSSE4;
		as->V4DDot=(tfSTDCALL_double_FUNC_p_p)&_V4DDotSSE4;

		as->V2FLength2=(tfSTDCALL_float_FUNC_p)&_V2FLength2SSE4;
		as->V3FLength2=(tfSTDCALL_float_FUNC_p)&_V3FLength2SSE4;
		as->V4FLength2=(tfSTDCALL_float_FUNC_p)&_V4FLength2SSE4;
		as->V2DLength2=(tfSTDCALL_double_FUNC_p)&_V2DLength2SSE4;
		as->V3DLength2=(tfSTDCALL_double_FUNC_p)&_V3DLength2SSE4;
		as->V4DLength2=(tfSTDCALL_double_FUNC_p)&_V4DLength2SSE4;
		
		as->V2FLerp=(tfSTDCALL_PROC_p_p_p_float)&_V2FLerpSSE4;
		as->V3FLerp=(tfSTDCALL_PROC_p_p_p_float)&_V3FLerpSSE4;
		as->V4FLerp=(tfSTDCALL_PROC_p_p_p_float)&_V4FLerpSSE4;
		as->V2DLerp=(tfSTDCALL_PROC_p_p_p_double)&_V2DLerpSSE4;
		as->V3DLerp=(tfSTDCALL_PROC_p_p_p_double)&_V3DLerpSSE4;
		as->V4DLerp=(tfSTDCALL_PROC_p_p_p_double)&_V4DLerpSSE4;

		as->V2FCombine=(tfSTDCALL_PROC_p_p_p_float_float)&_V2FCombineSSE4;
		as->V3FCombine=(tfSTDCALL_PROC_p_p_p_float_float)&_V3FCombineSSE4;
		as->V4FCombine=(tfSTDCALL_PROC_p_p_p_float_float)&_V4FCombineSSE4;
		as->V2DCombine=(tfSTDCALL_PROC_p_p_p_double_double)&_V2DCombineSSE4;
		as->V3DCombine=(tfSTDCALL_PROC_p_p_p_double_double)&_V3DCombineSSE4;
		as->V4DCombine=(tfSTDCALL_PROC_p_p_p_double_double)&_V4DCombineSSE4;

		as->V4FTransform=(tfSTDCALL_PROC_p_p_p)&_V4FTransformSSE4;
		as->V2DTransform=(tfSTDCALL_PROC_p_p_p)&_V2DTransformSSE4;
		as->V3DTransform=(tfSTDCALL_PROC_p_p_p)&_V3DTransformSSE4;
		as->V4DTransform=(tfSTDCALL_PROC_p_p_p)&_V4DTransformSSE4;

		as->V4FMMul=(tfSTDCALL_PROC_p_p_p)&_V4FTransformSSE4;

		as->M4DMul=(tfSTDCALL_PROC_p_p_p)&_M4DMulSSE4;

		as->M4FAddScale=(tfSTDCALL_PROC_p_p_p)&_M4FAddScaleSSE4;
		as->M4FAddTranslate=(tfSTDCALL_PROC_p_p_p)&_M4FAddTranslateSSE4;
	}

	if ((cpuinfo.flag&CPU_x86_AVX)!=0) {
		as->V4DAdd=(tfSTDCALL_PROC_p_p_p)&_V4DAddAVX;
		as->V4DSub=(tfSTDCALL_PROC_p_p_p)&_V4DSubAVX;
		//as->V4DScale=(tfSTDCALL_PROC_p_p_double)&_V4DScaleAVX;
		as->V4DMul=(tfSTDCALL_PROC_p_p_p)&_V4DMulAVX;
		as->V4DDiv=(tfSTDCALL_PROC_p_p_p)&_V4DDivAVX;
		//as->V4DLerp=(tfSTDCALL_PROC_p_p_p_double)&_V4DLerpAVX;
		//as->V4DCombine=(tfSTDCALL_PROC_p_p_p_double_double)&_V4DCombineAVX;

		as->QDAdd=(tfSTDCALL_PROC_p_p_p)&_V4DAddAVX;
	}
}

void initx86_64ArrayVector(void*_conteiner)
{
	sFunctionsArrayVectorCPU *as=(sFunctionsArrayVectorCPU *)_conteiner;
	as->version=0;
}

void initx86_64Extension(void*_conteiner)
{
	sFunctionsExtensionCPU *as=(sFunctionsExtensionCPU *)_conteiner;
	as->version=0;
	
	as->CleanMem=(tfSTDCALL_PROC_p_uint)&_CleanMemCPU;
	as->MoveMem=(tfSTDCALL_PROC_p_p_uint)&_MoveMemCPU;
	as->StocSMem=(tfSTDCALL_PROC_p_uint_uint)&_StosSMEMCPU;
	as->StocIMem=(tfSTDCALL_PROC_p_uint_uint)&_StosIMEMCPU;

	if ((cpuinfo.flag&CPU_x86_SSE2)!=0) {
		as->MoveMem=(tfSTDCALL_PROC_p_p_uint)&_MoveMemSSE2;
		as->ILogSize=(tfSTDCALL_int_FUNC_int)&_ILogSizeSSE2;
	}
}

void initx86_64Array(void*_conteiner)
{
	sFunctionsArrayCPU *as=(sFunctionsArrayCPU *)_conteiner;
	as->version=0;
}

void initx86_64Render(void*_conteiner)
{
	sFunctionsRenderCPU *as=(sFunctionsRenderCPU *)_conteiner;
	as->version=0;

}

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif
#endif
