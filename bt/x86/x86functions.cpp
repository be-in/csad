/*
 * x86functions.cpp
 *
 *  Created on: 18.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifdef CPU_BT

#include "x86functions.h"
#include <bt.h>
#include "x86math.h"
#include "x86vector.h"
#include "x86matrix.h"
#include "x86array.h"
#include "x86container.h"
#include "x86quaternion.h"
#include "x86mem.h"
#include "x86extension.h"
#include "x86render.h"

WARNING_DISABLE;
OPTIMIZE_ON;

#ifdef CPU_X86_32

namespace bt {

x86cpuinfo cpuinfo;

void initx86(unsigned _int32 flagMask)
{
	cpuInit(&cpuinfo);
	cpuinfo.flag&=flagMask;
	//cpuinfo.flag&=~(CPU_x86_SSE4 | CPU_x86_AVX);
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

void initx86BT(void*_conteiner)
{
	bt::sFunctionsAPICPU *as=(bt::sFunctionsAPICPU *)_conteiner;
	as->version=0;

	if ((cpuinfo.flag&CPU_x86_RDTSC)!=0) {
		as->TSC=(tfSTDCALL_long_FUNC)&_TSCDCPU;
	}
}

void initx86Math(void* _conteiner)
{
	sFunctionsMathCPU *as=(sFunctionsMathCPU *)_conteiner;

	//as->DLog2=(tfSTDCALL_double_FUNC_double)&_DLog2SSE4;
	as->ILog2=(tfSTDCALL_int_FUNC_int)&_ILog2CPU;

	if ((cpuinfo.flag&CPU_x86_FPU)!=0) {
		as->FSqrt=(tfSTDCALL_float_FUNC_float)_FsqrtFPU;
		as->DSqrt=(tfSTDCALL_double_FUNC_double)_DsqrtFPU;
		as->FFastInvSqrt=(tfSTDCALL_float_FUNC_float)_FFastInvSqrtFPU;
		as->FSinCos=(tfSTDCALL_PROC_float_p_p)_FSinCosFPU;
		as->DSinCos=(tfSTDCALL_PROC_double_p_p)_DSinCosFPU;
		as->FArcTg=(tfSTDCALL_float_FUNC_float_float)_FArcTgFPU;
		as->DArcTg=(tfSTDCALL_double_FUNC_double_double)_DArcTgFPU;
		as->Fmul2N=(tfSTDCALL_float_FUNC_float_int)_Fmul2NFPU;
		as->Dmul2N=(tfSTDCALL_double_FUNC_double_int)_Dmul2NFPU;
		as->FTrunc=(tfSTDCALL_int_FUNC_float)_FTruncFPU;
		as->DTrunc=(tfSTDCALL_int_FUNC_double)_DTruncFPU;
		as->FRound=(tfSTDCALL_int_FUNC_float)_FRoundFPU;
		as->DRound=(tfSTDCALL_int_FUNC_double)_DRoundFPU;
		as->Fmul2NTrunc=(tfSTDCALL_int_FUNC_float_int)_Fmul2NTruncFPU;
		as->Dmul2NTrunc=(tfSTDCALL_int_FUNC_double_int)_Dmul2NTruncFPU;
		as->Fmul2NRound=(tfSTDCALL_int_FUNC_float_int)_Fmul2NRoundFPU;
		as->Dmul2NRound=(tfSTDCALL_int_FUNC_double_int)_Dmul2NRoundFPU;
		as->FLog2=(tfSTDCALL_float_FUNC_float)&_FLog2FPU;
		as->DLog2=(tfSTDCALL_double_FUNC_double)&_DLog2FPU;
		as->ILog2=(tfSTDCALL_int_FUNC_int)&_ILog2FPU;
	}

	if ((cpuinfo.flag&CPU_x86_SSE)!=0) {
		as->FSqrt=(tfSTDCALL_float_FUNC_float)_FsqrtSSE;
		as->FFastInvSqrt=(tfSTDCALL_float_FUNC_float)_FFastInvSqrtSSE;
		as->FSinCos=(tfSTDCALL_PROC_float_p_p)_FSinCosSSE;
		as->FFastSinCos=(tfSTDCALL_PROC_float_p_p)_FFastSinCosSSE;
		as->FArcTg=(tfSTDCALL_float_FUNC_float_float)_FArcTgSSE;
		as->Fmul2N=(tfSTDCALL_float_FUNC_float_int)_Fmul2NSSE;
		as->FTrunc=(tfSTDCALL_int_FUNC_float)_FTruncSSE;
		as->FRound=(tfSTDCALL_int_FUNC_float)_FRoundSSE;
		as->FExp=(tfSTDCALL_float_FUNC_float)_FExpSSE;
	}

	if ((cpuinfo.flag&CPU_x86_SSE2)!=0) {
		as->DSqrt=(tfSTDCALL_double_FUNC_double)_DsqrtSSE2;
		as->DFastInvSqrt=(tfSTDCALL_double_FUNC_double)_DFastInvSqrtSSE2;
		//as->FSinCos=(tfSTDCALL_PROC_float_p_p)_FSinCosSSE2;
		as->DSinCos=(tfSTDCALL_PROC_double_p_p)_DSinCosSSE2;
		as->DFastSinCos=(tfSTDCALL_PROC_double_p_p)_DFastSinCosSSE2;
		as->Fmul2N=(tfSTDCALL_float_FUNC_float_int)_Fmul2NSSE2;
		as->Dmul2N=(tfSTDCALL_double_FUNC_double_int)_Dmul2NSSE2;
		as->DTrunc=(tfSTDCALL_int_FUNC_double)_DTruncSSE2;
		as->DRound=(tfSTDCALL_int_FUNC_double)_DRoundSSE2;
		as->Fmul2NTrunc=(tfSTDCALL_int_FUNC_float_int)_Fmul2NTruncSSE2;
		as->Dmul2NTrunc=(tfSTDCALL_int_FUNC_double_int)_Dmul2NTruncSSE2;
		as->Fmul2NRound=(tfSTDCALL_int_FUNC_float_int)_Fmul2NRoundSSE2;
		as->Dmul2NRound=(tfSTDCALL_int_FUNC_double_int)_Dmul2NRoundSSE2;
		as->DExp=(tfSTDCALL_double_FUNC_double)_DExpSSE2;
		as->ILog2=(tfSTDCALL_int_FUNC_int)&_ILog2SSE2;
	}

	if ((cpuinfo.flag&CPU_x86_SSE3)!=0) {
		//as->FSinCos=(tfSTDCALL_PROC_float_p_p)_FSinCosSSE3;
	}

	if ((cpuinfo.flag&CPU_x86_SSE4)!=0) {
		//as->FExp=(tfSTDCALL_float_FUNC_float)_FExpSSE4;
		//as->DExp=(tfSTDCALL_double_FUNC_double)_DExpSSE4;
		as->FPCRCC=(bt::tfSTDCALL_PROC_p_p)&bt::_FPCRCCSSE4;
		as->DPCRCC=(bt::tfSTDCALL_PROC_p_p)&bt::_DPCRCCSSE4;
		as->FSplineCR=(bt::tfSTDCALL_PROC_p_p_float_float)&bt::_FSplineCRSSE4;
		as->DSplineCR=(bt::tfSTDCALL_PROC_p_p_double_double)&bt::_DSplineCRSSE4;
		//as->DLog2=(tfSTDCALL_double_FUNC_double)&_DLog2SSE4;
	}
}

void initx86Vector(void*_conteiner)
{
	sFunctionsVectorCPU *as=(sFunctionsVectorCPU *)_conteiner;
	as->version=0;

	as->M4DTranslate=(tfSTDCALL_PROC_p_p)&_M4DTranslateCPU;
	as->M4DScale=(tfSTDCALL_PROC_p_p)&_M4DScaleCPU;

	if ((cpuinfo.flag&CPU_x86_FPU)!=0) {
		as->V2FTo2I=(tfSTDCALL_PROC_p_p)&_V2FTo2IFPU;
		as->V3FTo3I=(tfSTDCALL_PROC_p_p)&_V3FTo3IFPU;
		as->V4FTo4I=(tfSTDCALL_PROC_p_p)&_V4FTo4IFPU;
		as->V2DTo2I=(tfSTDCALL_PROC_p_p)&_V2DTo2IFPU;
		as->V3DTo3I=(tfSTDCALL_PROC_p_p)&_V3DTo3IFPU;
		as->V4DTo4I=(tfSTDCALL_PROC_p_p)&_V4DTo4IFPU;

		as->V2FAbs=(tfSTDCALL_PROC_p_p)&_V2FAbsFPU;
		as->V3FAbs=(tfSTDCALL_PROC_p_p)&_V3FAbsFPU;
		as->V4FAbs=(tfSTDCALL_PROC_p_p)&_V4FAbsFPU;
		as->V2DAbs=(tfSTDCALL_PROC_p_p)&_V2DAbsFPU;
		as->V3DAbs=(tfSTDCALL_PROC_p_p)&_V3DAbsFPU;
		as->V4DAbs=(tfSTDCALL_PROC_p_p)&_V4DAbsFPU;

		as->V2FAdd=(tfSTDCALL_PROC_p_p_p)&_V2FAddFPU;
		as->V3FAdd=(tfSTDCALL_PROC_p_p_p)&_V3FAddFPU;
		as->V4FAdd=(tfSTDCALL_PROC_p_p_p)&_V4FAddFPU;
		as->V2DAdd=(tfSTDCALL_PROC_p_p_p)&_V2DAddFPU;
		as->V3DAdd=(tfSTDCALL_PROC_p_p_p)&_V3DAddFPU;
		as->V4DAdd=(tfSTDCALL_PROC_p_p_p)&_V4DAddFPU;

		as->V2FSub=(tfSTDCALL_PROC_p_p_p)&_V2FSubFPU;
		as->V3FSub=(tfSTDCALL_PROC_p_p_p)&_V3FSubFPU;
		as->V4FSub=(tfSTDCALL_PROC_p_p_p)&_V4FSubFPU;
		as->V2DSub=(tfSTDCALL_PROC_p_p_p)&_V2DSubFPU;
		as->V3DSub=(tfSTDCALL_PROC_p_p_p)&_V3DSubFPU;
		as->V4DSub=(tfSTDCALL_PROC_p_p_p)&_V4DSubFPU;

		as->V2FScale=(tfSTDCALL_PROC_p_p_float)&_V2FScaleFPU;
		as->V3FScale=(tfSTDCALL_PROC_p_p_float)&_V3FScaleFPU;
		as->V4FScale=(tfSTDCALL_PROC_p_p_float)&_V4FScaleFPU;
		as->V2DScale=(tfSTDCALL_PROC_p_p_double)&_V2DScaleFPU;
		as->V3DScale=(tfSTDCALL_PROC_p_p_double)&_V3DScaleFPU;
		as->V4DScale=(tfSTDCALL_PROC_p_p_double)&_V4DScaleFPU;

		as->V2FMul=(tfSTDCALL_PROC_p_p_p)&_V2FMulFPU;
		as->V3FMul=(tfSTDCALL_PROC_p_p_p)&_V3FMulFPU;
		as->V4FMul=(tfSTDCALL_PROC_p_p_p)&_V4FMulFPU;
		as->V2DMul=(tfSTDCALL_PROC_p_p_p)&_V2DMulFPU;
		as->V3DMul=(tfSTDCALL_PROC_p_p_p)&_V3DMulFPU;
		as->V4DMul=(tfSTDCALL_PROC_p_p_p)&_V4DMulFPU;

		as->V2Fmul2NTrunc=(tfSTDCALL_PROC_p_p_int)&_V2Fmul2NTruncFPU;
		as->V3Fmul2NTrunc=(tfSTDCALL_PROC_p_p_int)&_V3Fmul2NTruncFPU;
		as->V4Fmul2NTrunc=(tfSTDCALL_PROC_p_p_int)&_V4Fmul2NTruncFPU;
		as->V2Dmul2NTrunc=(tfSTDCALL_PROC_p_p_int)&_V2Dmul2NTruncFPU;
		as->V3Dmul2NTrunc=(tfSTDCALL_PROC_p_p_int)&_V3Dmul2NTruncFPU;
		as->V4Dmul2NTrunc=(tfSTDCALL_PROC_p_p_int)&_V4Dmul2NTruncFPU;

		as->V2Fmul2NRound=(tfSTDCALL_PROC_p_p_int)&_V2Fmul2NRoundFPU;
		as->V3Fmul2NRound=(tfSTDCALL_PROC_p_p_int)&_V3Fmul2NRoundFPU;
		as->V4Fmul2NRound=(tfSTDCALL_PROC_p_p_int)&_V4Fmul2NRoundFPU;
		as->V2Dmul2NRound=(tfSTDCALL_PROC_p_p_int)&_V2Dmul2NRoundFPU;
		as->V3Dmul2NRound=(tfSTDCALL_PROC_p_p_int)&_V3Dmul2NRoundFPU;
		as->V4Dmul2NRound=(tfSTDCALL_PROC_p_p_int)&_V4Dmul2NRoundFPU;

		as->V2Fmul2N=(tfSTDCALL_PROC_p_p_int)&_V2Fmul2NFPU;
		as->V3Fmul2N=(tfSTDCALL_PROC_p_p_int)&_V3Fmul2NFPU;
		as->V4Fmul2N=(tfSTDCALL_PROC_p_p_int)&_V4Fmul2NFPU;
		as->V2Dmul2N=(tfSTDCALL_PROC_p_p_int)&_V2Dmul2NFPU;
		as->V3Dmul2N=(tfSTDCALL_PROC_p_p_int)&_V3Dmul2NFPU;
		as->V4Dmul2N=(tfSTDCALL_PROC_p_p_int)&_V4Dmul2NFPU;

		as->V2FDot=(tfSTDCALL_float_FUNC_p_p)&_V2FDotFPU;
		as->V3FDot=(tfSTDCALL_float_FUNC_p_p)&_V3FDotFPU;
		as->V4FDot=(tfSTDCALL_float_FUNC_p_p)&_V4FDotFPU;
		as->V2DDot=(tfSTDCALL_double_FUNC_p_p)&_V2DDotFPU;
		as->V3DDot=(tfSTDCALL_double_FUNC_p_p)&_V3DDotFPU;
		as->V4DDot=(tfSTDCALL_double_FUNC_p_p)&_V4DDotFPU;

		as->V2FLength2=(tfSTDCALL_float_FUNC_p)&_V2FLength2FPU;
		as->V3FLength2=(tfSTDCALL_float_FUNC_p)&_V3FLength2FPU;
		as->V4FLength2=(tfSTDCALL_float_FUNC_p)&_V4FLength2FPU;
		as->V2DLength2=(tfSTDCALL_double_FUNC_p)&_V2DLength2FPU;
		as->V3DLength2=(tfSTDCALL_double_FUNC_p)&_V3DLength2FPU;

		as->V3FCross=(tfSTDCALL_PROC_p_p_p)&_V3FCrossFPU;
		as->V3DCross=(tfSTDCALL_PROC_p_p_p)&_V3DCrossFPU;

		as->V2FNormal=(tfSTDCALL_PROC_p_p)&_V2FNormalFPU;
		as->V3FNormal=(tfSTDCALL_PROC_p_p)&_V3FNormalFPU;
		as->V4FNormal=(tfSTDCALL_PROC_p_p)&_V4FNormalFPU;
		as->V2DNormal=(tfSTDCALL_PROC_p_p)&_V2DNormalFPU;
		as->V3DNormal=(tfSTDCALL_PROC_p_p)&_V3DNormalFPU;
		as->V4DNormal=(tfSTDCALL_PROC_p_p)&_V4DNormalFPU;

		as->V2FLerp=(tfSTDCALL_PROC_p_p_p_float)&_V2FLerpFPU;
		as->V3FLerp=(tfSTDCALL_PROC_p_p_p_float)&_V3FLerpFPU;
		as->V4FLerp=(tfSTDCALL_PROC_p_p_p_float)&_V4FLerpFPU;
		as->V2DLerp=(tfSTDCALL_PROC_p_p_p_double)&_V2DLerpFPU;
		as->V3DLerp=(tfSTDCALL_PROC_p_p_p_double)&_V3DLerpFPU;
		as->V4DLerp=(tfSTDCALL_PROC_p_p_p_double)&_V4DLerpFPU;

		as->V2FCombine=(tfSTDCALL_PROC_p_p_p_float_float)&_V2FCombineFPU;
		as->V3FCombine=(tfSTDCALL_PROC_p_p_p_float_float)&_V3FCombineFPU;
		as->V4FCombine=(tfSTDCALL_PROC_p_p_p_float_float)&_V4FCombineFPU;
		as->V2DCombine=(tfSTDCALL_PROC_p_p_p_double_double)&_V2DCombineFPU;
		as->V3DCombine=(tfSTDCALL_PROC_p_p_p_double_double)&_V3DCombineFPU;
		as->V4DCombine=(tfSTDCALL_PROC_p_p_p_double_double)&_V4DCombineFPU;

		as->V2FAngle=(bt::tfSTDCALL_float_FUNC_p_p)&bt::_V2FAngleFPU;
		as->V3FAngle=(bt::tfSTDCALL_float_FUNC_p_p)&bt::_V3FAngleFPU;
		as->V2DAngle=(bt::tfSTDCALL_double_FUNC_p_p)&bt::_V2DAngleFPU;
		as->V3DAngle=(bt::tfSTDCALL_double_FUNC_p_p)&bt::_V3DAngleFPU;

		as->V3FAddTriNorm=(bt::tfSTDCALL_PROC_p_p_p_int)&bt::_V3FAddTriNormFPU;
		as->V3FAdd3DTriNorm=(bt::tfSTDCALL_PROC_p_p_p_int)&bt::_V3FAdd3DTriNormFPU;
		as->V3DAddTriNorm=(bt::tfSTDCALL_PROC_p_p_p_int)&bt::_V3DAddTriNormFPU;

		as->V4FQuaternion=(tfSTDCALL_PROC_p_p)&_V4FQuaternionFPU;
		as->V4DQuaternion=(tfSTDCALL_PROC_p_p)&_V4DQuaternionFPU;

		as->V2FTransform=(tfSTDCALL_PROC_p_p_p)&_V2FTransformFPU;
		as->V3FTransform=(tfSTDCALL_PROC_p_p_p)&_V3FTransformFPU;
		as->V4FTransform=(tfSTDCALL_PROC_p_p_p)&_V4FTransformFPU;

		as->V2FMMul=(tfSTDCALL_PROC_p_p_p)&_V2FMMulFPU;

		as->V3FProj=(tfSTDCALL_int_FUNC_p_p_p_p_p)&_V3FProjFPU;

		as->Q4FVector=(tfSTDCALL_PROC_p_p)&_Q4FVectorFPU;
		as->Q4DVector=(tfSTDCALL_PROC_p_p)&_Q4DVectorFPU;

		as->QFInv=(tfSTDCALL_PROC_p_p)&_QFInvFPU;
		as->QDInv=(tfSTDCALL_PROC_p_p)&_QDInvFPU;

		as->QFAdd=(tfSTDCALL_PROC_p_p_p)&_V4FAddFPU;
		as->QDAdd=(tfSTDCALL_PROC_p_p_p)&_V4DAddFPU;

		//as->QFNorm=(tfSTDCALL_double_PROC_p)&_V4FLength2FPU;
		//as->QDNorm=(tfSTDCALL_double_PROC_p)&_V4DLength2FPU;
		as->Q3FInvTransform=(tfSTDCALL_PROC_p_p_p)&_Q3FInvTransformFPU;
		as->Q3DInvTransform=(tfSTDCALL_PROC_p_p_p)&_Q3DInvTransformFPU;

		//as->M4DTRS=(tfSTDCALL_PROC_p_p_p_p)&_M4DTRSFPU;
	}

	if ((cpuinfo.flag&CPU_x86_3DNOW)!=0) {
	}

	if ((cpuinfo.flag&CPU_x86_SSE)!=0) {
		as->V2BTo2F=(tfSTDCALL_PROC_p_p)&_V2BTo2FSSE;
		as->V3BTo3F=(tfSTDCALL_PROC_p_p)&_V3BTo3FSSE;
		as->V4BTo4F=(tfSTDCALL_PROC_p_p)&_V4BTo4FSSE;
		as->V2ITo2F=(tfSTDCALL_PROC_p_p)&_V2ITo2FSSE;
		as->V3ITo3F=(tfSTDCALL_PROC_p_p)&_V3ITo3FSSE;
		as->V4ITo4F=(tfSTDCALL_PROC_p_p)&_V4ITo4FSSE;
		as->V2FTo2B=(tfSTDCALL_PROC_p_p)&_V2FTo2BSSE;
		as->V3FTo3B=(tfSTDCALL_PROC_p_p)&_V3FTo3BSSE;
		as->V4FTo4B=(tfSTDCALL_PROC_p_p)&_V4FTo4BSSE;
		as->V2FTo2I=(tfSTDCALL_PROC_p_p)&_V2FTo2ISSE;
		as->V3FTo3I=(tfSTDCALL_PROC_p_p)&_V3FTo3ISSE;
		as->V4FTo4I=(tfSTDCALL_PROC_p_p)&_V4FTo4ISSE;
		as->V2FTTo2I=(tfSTDCALL_PROC_p_p)&_V2FTTo2ISSE;
		as->V3FTTo3I=(tfSTDCALL_PROC_p_p)&_V3FTTo3ISSE;
		as->V4FTTo4I=(tfSTDCALL_PROC_p_p)&_V4FTTo4ISSE;

		as->V2FInv=(tfSTDCALL_PROC_p_p)&_V2FInvSSE;
		as->V3FInv=(tfSTDCALL_PROC_p_p)&_V3FInvSSE;
		as->V4FInv=(tfSTDCALL_PROC_p_p)&_V4FInvSSE;
		as->V2DInv=(tfSTDCALL_PROC_p_p)&_V2DInvSSE;
		as->V3DInv=(tfSTDCALL_PROC_p_p)&_V3DInvSSE;
		as->V4DInv=(tfSTDCALL_PROC_p_p)&_V4DInvSSE;

		as->V2FAdd=(tfSTDCALL_PROC_p_p_p)&_V2FAddSSE;
		as->V3FAdd=(tfSTDCALL_PROC_p_p_p)&_V3FAddSSE;
		as->V4FAdd=(tfSTDCALL_PROC_p_p_p)&_V4FAddSSE;

		as->V2FSub=(tfSTDCALL_PROC_p_p_p)&_V2FSubSSE;
		as->V3FSub=(tfSTDCALL_PROC_p_p_p)&_V3FSubSSE;
		as->V4FSub=(tfSTDCALL_PROC_p_p_p)&_V4FSubSSE;

		as->V2FScale=(tfSTDCALL_PROC_p_p_float)&_V2FScaleSSE;
		as->V3FScale=(tfSTDCALL_PROC_p_p_float)&_V3FScaleSSE;
		as->V4FScale=(tfSTDCALL_PROC_p_p_float)&_V4FScaleSSE;

		as->V2FMul=(tfSTDCALL_PROC_p_p_p)&_V2FMulSSE;
		as->V3FMul=(tfSTDCALL_PROC_p_p_p)&_V3FMulSSE;
		as->V4FMul=(tfSTDCALL_PROC_p_p_p)&_V4FMulSSE;

		as->V2FDiv=(tfSTDCALL_PROC_p_p_p)&_V2FDivSSE;
		as->V3FDiv=(tfSTDCALL_PROC_p_p_p)&_V3FDivSSE;
		as->V4FDiv=(tfSTDCALL_PROC_p_p_p)&_V4FDivSSE;

//		as->V4FDot=(tfSTDCALL_float_FUNC_p_p)&_V4FDotSSE;

		as->V4FLength2=(tfSTDCALL_float_FUNC_p)&_V4FLength2SSE;

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

		as->V2FCombine=(tfSTDCALL_PROC_p_p_p_float_float)&_V2FCombineSSE;
		as->V3FCombine=(tfSTDCALL_PROC_p_p_p_float_float)&_V3FCombineSSE;
		as->V4FCombine=(tfSTDCALL_PROC_p_p_p_float_float)&_V4FCombineSSE;

		as->V3FAngle=(bt::tfSTDCALL_float_FUNC_p_p)&bt::_V3FAngleSSE;

		as->V3FAddTriNorm=(bt::tfSTDCALL_PROC_p_p_p_int)&bt::_V3FAddTriNormSSE;

		as->V4FQuaternion=(tfSTDCALL_PROC_p_p)&_V4FQuaternionSSE;
		as->V4FFastQuaternion=(tfSTDCALL_PROC_p_p)&_V4FFastQuaternionSSE;

		as->V2FTransform=(tfSTDCALL_PROC_p_p_p)&_V2FTransformSSE;
		as->V3FTransform=(tfSTDCALL_PROC_p_p_p)&_V3FTransformSSE;
		as->V4FTransform=(tfSTDCALL_PROC_p_p_p)&_V4FTransformSSE;

		as->V2FMMul=(tfSTDCALL_PROC_p_p_p)&_V2FMMulSSE;
		as->V3FMMul=(tfSTDCALL_PROC_p_p_p)&_V3FMMulSSE;
		as->V4FMMul=(tfSTDCALL_PROC_p_p_p)&_V4FTransformSSE;

		as->V3FProj=(tfSTDCALL_int_FUNC_p_p_p_p_p)&_V3FProjSSE;

		as->QFAdd=(tfSTDCALL_PROC_p_p_p)&_V4FAddSSE;

		as->QFMul=(tfSTDCALL_PROC_p_p_p)&_QFMulSSE;

		as->Q4FMatrix=(tfSTDCALL_PROC_p_p)&_Q4FMatrixSSE;

		as->Q3FInvTransform=(tfSTDCALL_PROC_p_p_p)&_Q3FInvTransformSSE;

		as->M4FMul=(tfSTDCALL_PROC_p_p_p)&_M4FMulSSE;

		//as->M4FPerspective=(bt::tfSTDCALL_PROC_p_int_int_float_float_float)&bt::_M4FPerspectiveSSE;
		//as->M4FOrtographic=(bt::tfSTDCALL_PROC_p_int_int_float_float_float)&bt::_M4FOrtographicSSE;

		as->M4FIdentity=(bt::tfSTDCALL_PROC_p)&bt::_M4FIdentitySSE;
		as->M4DIdentity=(bt::tfSTDCALL_PROC_p)&bt::_M4DIdentitySSE;

		as->M4FTranslate=(tfSTDCALL_PROC_p_p)&_M4FTranslateSSE;
		as->M4FScale=(tfSTDCALL_PROC_p_p)&_M4FScaleSSE;

		as->M4FAddTranslate=(tfSTDCALL_PROC_p_p_p)&_M4FAddTranslateSSE;
		as->M4FAddScale=(tfSTDCALL_PROC_p_p_p)&_M4FAddScaleSSE;
		as->M4FAddRotate=(tfSTDCALL_PROC_p_p_p)&_M4FAddRotateSSE;

		//as->M4FTRS=(tfSTDCALL_PROC_p_p_p_p)&_M4FTRSSSE;
	}

	if ((cpuinfo.flag&CPU_x86_SSE2)!=0) {
		as->V2BTo2D=(tfSTDCALL_PROC_p_p)&_V2BTo2DSSE2;
		as->V3BTo3D=(tfSTDCALL_PROC_p_p)&_V3BTo3DSSE2;
		as->V4BTo4D=(tfSTDCALL_PROC_p_p)&_V4BTo4DSSE2;
		as->V2FTo2I=(tfSTDCALL_PROC_p_p)&_V2FTo2ISSE2;
		as->V3FTo3I=(tfSTDCALL_PROC_p_p)&_V3FTo3ISSE2;
		as->V4FTo4I=(tfSTDCALL_PROC_p_p)&_V4FTo4ISSE2;
		as->V2FTTo2I=(tfSTDCALL_PROC_p_p)&_V2FTTo2ISSE2;
		as->V3FTTo3I=(tfSTDCALL_PROC_p_p)&_V3FTTo3ISSE2;
		as->V4FTTo4I=(tfSTDCALL_PROC_p_p)&_V4FTTo4ISSE2;
		as->V2FTo2D=(tfSTDCALL_PROC_p_p)&_V2FTo2DSSE2;
		//as->V3FTo3D=(tfSTDCALL_PROC_p_p)&_V3FTo3DSSE2;
		as->V4FTo4D=(tfSTDCALL_PROC_p_p)&_V4FTo4DSSE2;
		as->V2DTo2I=(tfSTDCALL_PROC_p_p)&_V2DTo2ISSE2;
		as->V3DTo3I=(tfSTDCALL_PROC_p_p)&_V3DTo3ISSE2;
		as->V4DTo4I=(tfSTDCALL_PROC_p_p)&_V4DTo4ISSE2;
		as->V2DTTo2I=(tfSTDCALL_PROC_p_p)&_V2DTTo2ISSE2;
		as->V3DTTo3I=(tfSTDCALL_PROC_p_p)&_V3DTTo3ISSE2;
		as->V4DTTo4I=(tfSTDCALL_PROC_p_p)&_V4DTTo4ISSE2;
		as->V2DTo2F=(tfSTDCALL_PROC_p_p)&_V2DTo2FSSE2;
		//as->V3DTo3F=(tfSTDCALL_PROC_p_p)&_V3DTo3FSSE2;
		as->V4DTo4F=(tfSTDCALL_PROC_p_p)&_V4DTo4FSSE2;

		as->V2FAbs=(tfSTDCALL_PROC_p_p)&_V2FAbsSSE2;
		as->V3FAbs=(tfSTDCALL_PROC_p_p)&_V3FAbsSSE2;
		as->V4FAbs=(tfSTDCALL_PROC_p_p)&_V4FAbsSSE2;
		as->V2DAbs=(tfSTDCALL_PROC_p_p)&_V2DAbsSSE2;
		as->V3DAbs=(tfSTDCALL_PROC_p_p)&_V3DAbsSSE2;
		as->V4DAbs=(tfSTDCALL_PROC_p_p)&_V4DAbsSSE2;

		as->V2FMinMax=(tfSTDCALL_PROC_p_p_p)&_V2FMinMaxSSE2;
		as->V3FMinMax=(tfSTDCALL_PROC_p_p_p)&_V3FMinMaxSSE2;
		as->V4FMinMax=(tfSTDCALL_PROC_p_p_p)&_V4FMinMaxSSE2;
		as->V2DMinMax=(tfSTDCALL_PROC_p_p_p)&_V2DMinMaxSSE2;

		as->V2IAdd=(tfSTDCALL_PROC_p_p_p)&_V2IAddSSE2;
		as->V3IAdd=(tfSTDCALL_PROC_p_p_p)&_V3IAddSSE2;
		as->V4IAdd=(tfSTDCALL_PROC_p_p_p)&_V4IAddSSE2;

		as->V2FAdd=(tfSTDCALL_PROC_p_p_p)&_V2FAddSSE2;
		as->V3FAdd=(tfSTDCALL_PROC_p_p_p)&_V3FAddSSE2;

		as->V2FSub=(tfSTDCALL_PROC_p_p_p)&_V2FSubSSE2;
		//as->V4FSub=(tfSTDCALL_PROC_p_p_p)&_V4FSubSSE2;
		as->V3DSub=(tfSTDCALL_PROC_p_p_p)&_V3DSubSSE2;
		as->V4DSub=(tfSTDCALL_PROC_p_p_p)&_V4DSubSSE2;

		as->V2DMul=(tfSTDCALL_PROC_p_p_p)&_V2DMulSSE2;
		as->V3DMul=(tfSTDCALL_PROC_p_p_p)&_V3DMulSSE2;
		as->V4DMul=(tfSTDCALL_PROC_p_p_p)&_V4DMulSSE2;

		as->V2DDiv=(tfSTDCALL_PROC_p_p_p)&_V2DDivSSE2;
		as->V3DDiv=(tfSTDCALL_PROC_p_p_p)&_V3DDivSSE2;
		as->V4DDiv=(tfSTDCALL_PROC_p_p_p)&_V4DDivSSE2;

		as->V2Fmul2NTrunc=(tfSTDCALL_PROC_p_p_int)&_V2Fmul2NTruncSSE2;
		as->V3Fmul2NTrunc=(tfSTDCALL_PROC_p_p_int)&_V3Fmul2NTruncSSE2;
		as->V4Fmul2NTrunc=(tfSTDCALL_PROC_p_p_int)&_V4Fmul2NTruncSSE2;
		as->V2Dmul2NTrunc=(tfSTDCALL_PROC_p_p_int)&_V2Dmul2NTruncSSE2;
		as->V3Dmul2NTrunc=(tfSTDCALL_PROC_p_p_int)&_V3Dmul2NTruncSSE2;
		as->V4Dmul2NTrunc=(tfSTDCALL_PROC_p_p_int)&_V4Dmul2NTruncSSE2;

		as->V2Fmul2NRound=(tfSTDCALL_PROC_p_p_int)&_V2Fmul2NRoundSSE2;
		as->V3Fmul2NRound=(tfSTDCALL_PROC_p_p_int)&_V3Fmul2NRoundSSE2;
		as->V4Fmul2NRound=(tfSTDCALL_PROC_p_p_int)&_V4Fmul2NRoundSSE2;
		as->V2Dmul2NRound=(tfSTDCALL_PROC_p_p_int)&_V2Dmul2NRoundSSE2;
		as->V3Dmul2NRound=(tfSTDCALL_PROC_p_p_int)&_V3Dmul2NRoundSSE2;
		as->V4Dmul2NRound=(tfSTDCALL_PROC_p_p_int)&_V4Dmul2NRoundSSE2;

		as->V2Fmul2N=(tfSTDCALL_PROC_p_p_int)&_V2Fmul2NSSE2;
		as->V3Fmul2N=(tfSTDCALL_PROC_p_p_int)&_V3Fmul2NSSE2;
		as->V4Fmul2N=(tfSTDCALL_PROC_p_p_int)&_V4Fmul2NSSE2;
		as->V2Dmul2N=(tfSTDCALL_PROC_p_p_int)&_V2Dmul2NSSE2;
		as->V3Dmul2N=(tfSTDCALL_PROC_p_p_int)&_V3Dmul2NSSE2;
		as->V4Dmul2N=(tfSTDCALL_PROC_p_p_int)&_V4Dmul2NSSE2;

		as->V4DLength2=(tfSTDCALL_double_FUNC_p)&_V4DLength2SSE2;

		as->V3DCross=(tfSTDCALL_PROC_p_p_p)&_V3DCrossSSE2;

		//as->V2DNormal=(tfSTDCALL_PROC_p_p)&_V2DNormalSSE2;

		as->V2DFastNormal=(tfSTDCALL_PROC_p_p)&_V2DFastNormalSSE2;
		as->V3DFastNormal=(tfSTDCALL_PROC_p_p)&_V3DFastNormalSSE2;
		as->V4DFastNormal=(tfSTDCALL_PROC_p_p)&_V4DFastNormalSSE2;

		as->V2DLerp=(tfSTDCALL_PROC_p_p_p_double)&_V2DLerpSSE2;
		as->V3DLerp=(tfSTDCALL_PROC_p_p_p_double)&_V3DLerpSSE2;
		as->V4DLerp=(tfSTDCALL_PROC_p_p_p_double)&_V4DLerpSSE2;

		as->V2FCombine=(tfSTDCALL_PROC_p_p_p_float_float)&_V2FCombineSSE2;
		as->V4DCombine=(tfSTDCALL_PROC_p_p_p_double_double)&_V4DCombineSSE2;

		as->V3DAddTriNorm=(bt::tfSTDCALL_PROC_p_p_p_int)&bt::_V3DAddTriNormSSE2;

		as->V4DQuaternion=(tfSTDCALL_PROC_p_p)&_V4DQuaternionSSE2;
		as->V4DFastQuaternion=(tfSTDCALL_PROC_p_p)&_V4DFastQuaternionSSE2;

		as->V2FTransform=(tfSTDCALL_PROC_p_p_p)&_V2FTransformSSE2;
		as->V3DTransform=(tfSTDCALL_PROC_p_p_p)&_V3DTransformSSE2;

		as->QDMul=(tfSTDCALL_PROC_p_p_p)&_QDMulSSE2;

		as->Q3DInvTransform=(tfSTDCALL_PROC_p_p_p)&_Q3DInvTransformSSE2;

		as->M4DMul=(tfSTDCALL_PROC_p_p_p)&_M4DMulSSE2;
		
		//as->M4DPerspective=(bt::tfSTDCALL_PROC_p_int_int_double_double_double)&bt::_M4DPerspectiveSSE2;
		//as->M4DOrtographic=(bt::tfSTDCALL_PROC_p_int_int_double_double_double)&bt::_M4DOrtographicSSE2;

		as->M4DScale=(tfSTDCALL_PROC_p_p)&_M4DScaleSSE2;

		as->M4DToM4F=(tfSTDCALL_PROC_p_p)&_M4DToM4FSSE2;
	}

	if ((cpuinfo.flag&CPU_x86_SSE3)!=0) {
		as->V4R32=(bt::tfSTDCALL_PROC_p_p)&bt::_V4R32SSE3;
		as->V4R64=(bt::tfSTDCALL_PROC_p_p)&bt::_V4R64SSE3;

		as->V3R64Copy = (bt::tfSTDCALL_PROC_p_p)&bt::_V3R64CopySSE3;
		as->V4R64Copy = (bt::tfSTDCALL_PROC_p_p)&bt::_V4R64CopySSE3;

		as->V4BTo4F=(tfSTDCALL_PROC_p_p)&_V4BTo4FSSE3;
		as->V2DTo2F=(tfSTDCALL_PROC_p_p)&_V2DTo2FSSE3; 
		as->V3DTo3F=(tfSTDCALL_PROC_p_p)&_V3DTo3FSSE3;
		as->V4DTo4F=(tfSTDCALL_PROC_p_p)&_V4DTo4FSSE3;

		as->V4FAdd=(tfSTDCALL_PROC_p_p_p)&_V4FAddSSE3;
		as->V2DAdd=(tfSTDCALL_PROC_p_p_p)&_V2DAddSSE3;
		as->V3DAdd=(tfSTDCALL_PROC_p_p_p)&_V3DAddSSE3;
		as->V4DAdd=(tfSTDCALL_PROC_p_p_p)&_V4DAddSSE3;

		as->V4FSub=(tfSTDCALL_PROC_p_p_p)&_V4FSubSSE3;
		as->V2DSub=(tfSTDCALL_PROC_p_p_p)&_V2DSubSSE3;
		as->V3DSub=(tfSTDCALL_PROC_p_p_p)&_V3DSubSSE3;
		as->V4DSub=(tfSTDCALL_PROC_p_p_p)&_V4DSubSSE3;

		as->V4FScale=(tfSTDCALL_PROC_p_p_float)&_V4FScaleSSE3;
		as->V2DScale=(tfSTDCALL_PROC_p_p_double)&_V2DScaleSSE3;

		as->V4FLerp=(tfSTDCALL_PROC_p_p_p_float)&_V4FLerpSSE3;
		as->V2DLerp=(tfSTDCALL_PROC_p_p_p_double)&_V2DLerpSSE3;
		as->V3DLerp=(tfSTDCALL_PROC_p_p_p_double)&_V3DLerpSSE3;
		as->V4DLerp=(tfSTDCALL_PROC_p_p_p_double)&_V4DLerpSSE3;

		as->V4FCombine=(tfSTDCALL_PROC_p_p_p_float_float)&_V4FCombineSSE3;

		as->V2FQDFL=(tfSTDCALL_float_FUNC_p_p_p)&_V2FQDFLSSE3;
		as->V2DQDFL=(tfSTDCALL_double_FUNC_p_p_p)&_V2DQDFLSSE3;

		as->V3FTransform=(tfSTDCALL_PROC_p_p_p)&_V3FTransformSSE3;
		as->V4FTransform=(tfSTDCALL_PROC_p_p_p)&_V4FTransformSSE3;

		as->V3FMMul=(tfSTDCALL_PROC_p_p_p)&_V3FMMulSSE3;
		as->V4FMMul=(tfSTDCALL_PROC_p_p_p)&_V4FTransformSSE3;

		as->V2FProj=(tfSTDCALL_int_FUNC_p_p_p_p_p)&_V2FProjSSE3;
		as->V3FProj=(tfSTDCALL_int_FUNC_p_p_p_p_p)&_V3FProjSSE3;
		as->V4FProj=(tfSTDCALL_int_FUNC_p_p_p_p_p)&_V4FProjSSE3;

		as->QFAdd=(tfSTDCALL_PROC_p_p_p)&_V4FAddSSE3;
		as->QDAdd=(tfSTDCALL_PROC_p_p_p)&_V4DAddSSE3;

		//as->QFMul=(tfSTDCALL_PROC_p_p_p)&_QFMulSSE3;
		as->QDMul=(tfSTDCALL_PROC_p_p_p)&_QDMulSSE3;

		as->Q3FInvTransform=(tfSTDCALL_PROC_p_p_p)&_Q3FInvTransformSSE3;

		as->M4FMul=(tfSTDCALL_PROC_p_p_p)&_M4FMulSSE3;
		as->M4FAddRotate=(tfSTDCALL_PROC_p_p_p)&_M4FAddRotateSSE3;
	}

	if ((cpuinfo.flag&CPU_x86_SSE4)!=0) {
		as->V4ITo4F=(tfSTDCALL_PROC_p_p)&_V4ITo4FSSE4;
		as->V4FTo4B=(tfSTDCALL_PROC_p_p)&_V4FTo4BSSE4;
		as->V4FTo4I=(tfSTDCALL_PROC_p_p)&_V4FTo4ISSE4;
		as->V4FTTo4I=(tfSTDCALL_PROC_p_p)&_V4FTTo4ISSE4;
		as->V3FTo3D=(tfSTDCALL_PROC_p_p)&_V3FTo3DSSE4;

		as->V4FAbs=(tfSTDCALL_PROC_p_p)&_V4FAbsSSE4;
		as->V2DAbs=(tfSTDCALL_PROC_p_p)&_V2DAbsSSE4;
		as->V3DAbs=(tfSTDCALL_PROC_p_p)&_V3DAbsSSE4;
		as->V4DAbs=(tfSTDCALL_PROC_p_p)&_V4DAbsSSE4;

		as->V4FMinMax=(tfSTDCALL_PROC_p_p_p)&_V4FMinMaxSSE4;
		as->V2DMinMax=(tfSTDCALL_PROC_p_p_p)&_V2DMinMaxSSE4;
		as->V3DMinMax=(tfSTDCALL_PROC_p_p_p)&_V3DMinMaxSSE4;
		as->V4DMinMax=(tfSTDCALL_PROC_p_p_p)&_V4DMinMaxSSE4;

		as->V4IAdd=(tfSTDCALL_PROC_p_p_p)&_V4IAddSSE4;
		as->V3DAdd=(tfSTDCALL_PROC_p_p_p)&_V3DAddSSE4;
		as->V4DAdd=(tfSTDCALL_PROC_p_p_p)&_V4DAddSSE4;

		as->V4DSub=(tfSTDCALL_PROC_p_p_p)&_V4DSubSSE4;

		as->V4IScale=(tfSTDCALL_PROC_p_p_float)&_V4IScaleSSE3;
		as->V2DScale=(tfSTDCALL_PROC_p_p_double)&_V2DScaleSSE4;
		as->V3DScale=(tfSTDCALL_PROC_p_p_double)&_V3DScaleSSE4;
		as->V4DScale=(tfSTDCALL_PROC_p_p_double)&_V4DScaleSSE4;

		as->V4DMul=(tfSTDCALL_PROC_p_p_p)&_V4DMulSSE4;
		as->V4DDiv=(tfSTDCALL_PROC_p_p_p)&_V4DDivSSE4;

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

		as->V2FNormal=(tfSTDCALL_PROC_p_p)&_V2FNormalSSE4;
		as->V3FNormal=(tfSTDCALL_PROC_p_p)&_V3FNormalSSE4;
		as->V4FNormal=(tfSTDCALL_PROC_p_p)&_V4FNormalSSE4;
		as->V2DNormal=(tfSTDCALL_PROC_p_p)&_V2DNormalSSE4;
		as->V3DNormal=(tfSTDCALL_PROC_p_p)&_V3DNormalSSE4;
		as->V4DNormal=(tfSTDCALL_PROC_p_p)&_V4DNormalSSE4;

		as->V2FFastNormal=(tfSTDCALL_PROC_p_p)&_V2FFastNormalSSE4;
		as->V3FFastNormal=(tfSTDCALL_PROC_p_p)&_V3FFastNormalSSE4;
		as->V4FFastNormal=(tfSTDCALL_PROC_p_p)&_V4FFastNormalSSE4;
		as->V2DFastNormal=(tfSTDCALL_PROC_p_p)&_V2DFastNormalSSE4;
		as->V3DFastNormal=(tfSTDCALL_PROC_p_p)&_V3DFastNormalSSE4;
		as->V4DFastNormal=(tfSTDCALL_PROC_p_p)&_V4DFastNormalSSE4;

		as->V4FLerp=(tfSTDCALL_PROC_p_p_p_float)&_V4FLerpSSE4;
		as->V2DLerp=(tfSTDCALL_PROC_p_p_p_double)&_V2DLerpSSE4;
		as->V4DLerp=(tfSTDCALL_PROC_p_p_p_double)&_V4DLerpSSE4;

		as->V4FCombine=(tfSTDCALL_PROC_p_p_p_float_float)&_V4FCombineSSE4;
		as->V2DCombine=(tfSTDCALL_PROC_p_p_p_double_double)&_V2DCombineSSE4;
		as->V3DCombine=(tfSTDCALL_PROC_p_p_p_double_double)&_V3DCombineSSE4;
		as->V4DCombine=(tfSTDCALL_PROC_p_p_p_double_double)&_V4DCombineSSE4;

		as->V4FQuaternion=(tfSTDCALL_PROC_p_p)&_V4FQuaternionSSE4;
		as->V4DQuaternion=(tfSTDCALL_PROC_p_p)&_V4DQuaternionSSE4;

		//as->V4FFastQuaternion=(tfSTDCALL_PROC_p_p)&_V4FFastQuaternionSSE4;

		as->V2DTransform=(tfSTDCALL_PROC_p_p_p)_V2DTransformSSE4;
		as->V3DTransform=(tfSTDCALL_PROC_p_p_p)_V3DTransformSSE4;
		as->V4DTransform=(tfSTDCALL_PROC_p_p_p)_V4DTransformSSE4;

		as->QFInv=(tfSTDCALL_PROC_p_p)&_QFInvSSE4;
		//as->QDInv=(tfSTDCALL_PROC_p_p)&_QDInvSSE4;

		//as->QFAdd=(tfSTDCALL_PROC_p_p_p)&_V4FAddSSE4;
		as->QDAdd=(tfSTDCALL_PROC_p_p_p)&_V4DAddSSE4;

		as->QFMul=(tfSTDCALL_PROC_p_p_p)&_QFMulSSE4;
		as->QDMul=(tfSTDCALL_PROC_p_p_p)&_QDMulSSE4;

		as->QFNorm=(tfSTDCALL_float_FUNC_p)&_V4FLength2SSE4;
		as->QDNorm=(tfSTDCALL_double_FUNC_p)&_V4DLength2SSE4;
		
		as->Q4FMatrix=(tfSTDCALL_PROC_p_p)&_Q4FMatrixSSE4;
		as->Q4DMatrix=(tfSTDCALL_PROC_p_p)&_Q4DMatrixSSE4;

		as->Q3FInvTransform=(tfSTDCALL_PROC_p_p_p)&_Q3FInvTransformSSE4;
		as->Q3DInvTransform=(tfSTDCALL_PROC_p_p_p)&_Q3DInvTransformSSE4;

		as->M4FTranspose=(tfSTDCALL_PROC_p_p)&_M4FTransposeSSE4;

		as->M4FMul=(tfSTDCALL_PROC_p_p_p)&_M4FMulSSE4;
		as->M4DMul=(tfSTDCALL_PROC_p_p_p)&_M4DMulSSE4;

		//as->M4FPerspective=(bt::tfSTDCALL_PROC_p_int_int_float_float_float)&bt::_M4FPerspectiveSSE4;
		//as->M4DPerspective=(bt::tfSTDCALL_PROC_p_int_int_double_double_double)&bt::_M4DPerspectiveSSE4;
		//as->M4FOrtographic=(bt::tfSTDCALL_PROC_p_int_int_float_float_float)&bt::_M4FOrtographicSSE4;
		//as->M4DOrtographic=(bt::tfSTDCALL_PROC_p_int_int_double_double_double)&bt::_M4DOrtographicSSE4;

		as->M4FIdentity=(bt::tfSTDCALL_PROC_p)&bt::_M4FIdentitySSE4;
		as->M4DIdentity=(bt::tfSTDCALL_PROC_p)&bt::_M4DIdentitySSE4;

		as->M4DTranslate=(tfSTDCALL_PROC_p_p)&_M4DTranslateSSE4;

		as->M4FAddTranslate=(tfSTDCALL_PROC_p_p_p)&_M4FAddTranslateSSE4;
		//as->M4DAddTranslate=(tfSTDCALL_PROC_p_p_p)&_M4DAddTranslateSSE4;
		as->M4FAddScale=(tfSTDCALL_PROC_p_p_p)&_M4FAddScaleSSE4;
		as->M4FAddRotate=(tfSTDCALL_PROC_p_p_p)&_M4FAddRotateSSE4;
		//as->M4DAddRotate=(tfSTDCALL_PROC_p_p_p)&_M4DAddRotateSSE4;

		as->M4FTRS=(tfSTDCALL_PROC_p_p_p_p)&_M4FTRSSSE4;
		as->M4DTRS=(tfSTDCALL_PROC_p_p_p_p)&_M4DTRSSSE4;
	}

	if ((cpuinfo.flag&CPU_x86_AVX)!=0) {
		as->V4DMinMax=(tfSTDCALL_PROC_p_p_p)&_V4DMinMaxAVX;
		as->V3DAdd=(tfSTDCALL_PROC_p_p_p)&_V3DAddAVX;
		as->V4DAdd=(tfSTDCALL_PROC_p_p_p)&_V4DAddAVX;
		as->V4DSub=(tfSTDCALL_PROC_p_p_p)&_V4DSubAVX;
		as->V4DScale=(tfSTDCALL_PROC_p_p_double)&_V4DScaleAVX;
		as->V4DMul=(tfSTDCALL_PROC_p_p_p)&_V4DMulAVX;
		as->V4DDiv=(tfSTDCALL_PROC_p_p_p)&_V4DDivAVX;
		//as->V4DDot=(tfSTDCALL_double_FUNC_p_p)&_V4DDotAVX;
		//as->V4DNormal=(tfSTDCALL_PROC_p_p)&_V4DNormalAVX;
		as->V4DLerp=(tfSTDCALL_PROC_p_p_p_double)&_V4DLerpAVX;
		as->V3DTransform=(tfSTDCALL_PROC_p_p_p)_V3DTransformAVX;
		as->V4DTransform=(tfSTDCALL_PROC_p_p_p)_V4DTransformAVX;
		//as->V4DProj=(tfSTDCALL_int_FUNC_p_p_p_p_p)&_V4DProjAVX;
		//as->M4FMul=(tfSTDCALL_PROC_p_p_p)&_M4FMulAVX;
		as->M4DMul=(tfSTDCALL_PROC_p_p_p)&_M4DMulAVX;
	}
}

void initx86ArrayVector(void*_conteiner)
{
	sFunctionsArrayVectorCPU *as=(sFunctionsArrayVectorCPU *)_conteiner;
	as->version=0;

	if ((cpuinfo.flag&CPU_x86_FPU)!=0) {
		as->A2FNormal=(tfSTDCALL_PROC_p_p_int_int_uint)&_A2FNormalFPU;
		as->A3FNormal=(tfSTDCALL_PROC_p_p_int_int_uint)&_A3FNormalFPU;
		as->A4FNormal=(tfSTDCALL_PROC_p_p_int_int_uint)&_A4FNormalFPU;
		as->A2DNormal=(tfSTDCALL_PROC_p_p_int_int_uint)&_A2DNormalFPU;
		as->A3DNormal=(tfSTDCALL_PROC_p_p_int_int_uint)&_A3DNormalFPU;
		as->A4DNormal=(tfSTDCALL_PROC_p_p_int_int_uint)&_A4DNormalFPU;
	}

	if ((cpuinfo.flag&CPU_x86_SSE)!=0) {
		as->A2FAddVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A2FAddVectorSSE;
		as->A3FAddVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A3FAddVectorSSE;
		as->A4FAddVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A4FAddVectorSSE;

		as->A2FSubVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A2FSubVectorSSE;
		as->A3FSubVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A3FSubVectorSSE;
		as->A4FSubVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A4FSubVectorSSE;

		as->A2FMulVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A2FMulVectorSSE;
		as->A3FMulVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A3FMulVectorSSE;
		as->A4FMulVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A4FMulVectorSSE;

		as->A2FNormal=(tfSTDCALL_PROC_p_p_int_int_uint)&_A2FNormalSSE;
		as->A3FNormal=(tfSTDCALL_PROC_p_p_int_int_uint)&_A3FNormalSSE;
		as->A4FNormal=(tfSTDCALL_PROC_p_p_int_int_uint)&_A4FNormalSSE;

		as->A2FMatrixTransform=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A2FMatrixTransformSSE;
		as->A3FMatrixTransform=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A3FMatrixTransformSSE;
		as->A4FMatrixTransform=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A4FMatrixTransformSSE;
	}

	if ((cpuinfo.flag&CPU_x86_SSE2)!=0) {
		as->A2DAddVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A2DAddVectorSSE2;
		as->A3DAddVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A3DAddVectorSSE2;
		as->A4DAddVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A4DAddVectorSSE2;

		as->A2DSubVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A2DSubVectorSSE2;
		as->A3DSubVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A3DSubVectorSSE2;
		as->A4DSubVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A4DSubVectorSSE2;

		as->A2DMulVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A2DMulVectorSSE2;
		as->A3DMulVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A3DMulVectorSSE2;
		as->A4DMulVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A4DMulVectorSSE2;

		//as->A2FProj=(tfSTDCALL_PROC_p_p_p_p_p_int_int_int_uint)&_A2FProjSSE2;
		//as->A3FProj=(tfSTDCALL_PROC_p_p_p_p_p_int_int_int_uint)&_A3FProjSSE2;
		//as->A4FProj=(tfSTDCALL_PROC_p_p_p_p_p_int_int_int_uint)&_A4FProjSSE2;
	}

	if ((cpuinfo.flag&CPU_x86_SSE3)!=0) {

		as->A2FAddVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A2FAddVectorSSE3;
		as->A4FAddVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A4FAddVectorSSE3;
		as->A2DAddVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A2DAddVectorSSE3;
		as->A4DAddVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A4DAddVectorSSE3;

		as->A4IAdd=(tfSTDCALL_PROC_p_p_p_int_int_int_uint)&_A4IAddSSE3;
		as->A4FAdd=(tfSTDCALL_PROC_p_p_p_int_int_int_uint)&_A4FAddSSE3;

		as->A2FSubVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A2FSubVectorSSE3;
		as->A4FSubVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A4FSubVectorSSE3;
		as->A2DSubVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A2DSubVectorSSE3;
		as->A4DSubVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A4DSubVectorSSE3;

		as->A4ISub=(tfSTDCALL_PROC_p_p_p_int_int_int_uint)&_A4ISubSSE3;
		as->A4FSub=(tfSTDCALL_PROC_p_p_p_int_int_int_uint)&_A4FSubSSE3;

		as->A2FMulVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A2FMulVectorSSE3;
		as->A4FMulVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A4FMulVectorSSE3;
		as->A2DMulVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A2DMulVectorSSE3;
		as->A4DMulVector=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A4DMulVectorSSE3;

		as->A2FNormal=(tfSTDCALL_PROC_p_p_int_int_uint)&_A2FNormalSSE3;

		as->A3FMatrixTransform=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A3FMatrixTransformSSE3;
		as->A4FMatrixTransform=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A4FMatrixTransformSSE3;

		as->A2FProj=(tfSTDCALL_PROC_p_p_p_p_p_int_int_int_uint)&_A2FProjSSE3;
		as->A3FProj=(tfSTDCALL_PROC_p_p_p_p_p_int_int_int_uint)&_A3FProjSSE3;
		as->A4FProj=(tfSTDCALL_PROC_p_p_p_p_p_int_int_int_uint)&_A4FProjSSE3;
	}

	if ((cpuinfo.flag&CPU_x86_SSE4)!=0) {
		as->A2FNormal=(tfSTDCALL_PROC_p_p_int_int_uint)&_A2FNormalSSE4;
	}

	if ((cpuinfo.flag&CPU_x86_AVX)!=0) {
		as->A3DMatrixTransform=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A3DMatrixTransformAVX;
		as->A4DMatrixTransform=(tfSTDCALL_PROC_p_p_p_int_int_uint)&_A4DMatrixTransformAVX;
	}
}

void initx86Extension(void*_conteiner)
{
	sFunctionsExtensionCPU *as=(sFunctionsExtensionCPU *)_conteiner;
	as->version=0;

	as->CleanMem=(tfSTDCALL_PROC_p_uint)&_CleanMemCPU;
	as->MoveMem=(tfSTDCALL_PROC_p_p_uint)&_MoveMemCPU;
	as->MoveBack=(tfSTDCALL_PROC_p_p_uint)&_MoveBackCPU;
	as->SwapMem=(tfSTDCALL_PROC_p_p_uint)&_SwapMemCPU;
	as->StocSMem=(tfSTDCALL_PROC_p_uint_uint)&_StosSMEMCPU;
	as->StocIMem=(tfSTDCALL_PROC_p_uint_uint)&_StosIMEMCPU;

	if ((cpuinfo.flag&CPU_x86_FPU)!=0) {
		as->ILogSize=(tfSTDCALL_int_FUNC_int)&_ILogSizeFPU;

		//as->V3FToBLH=(tfSTDCALL_PROC_p_p)&_V3FToBLHFPU;
		//as->V3DToBLH=(tfSTDCALL_PROC_p_p)&_V3DToBLHFPU;

		//as->V3FToBL=(tfSTDCALL_PROC_p_p_p)&_V3FToBLFPU;
		//as->V3DToBL=(tfSTDCALL_PROC_p_p_p)&_V3DToBLFPU;
	}

	if ((cpuinfo.flag&CPU_x86_SSE)!=0) {
		//as->StocIMem=(tfSTDCALL_PROC_p_uint_uint)&_StosIMEMSSE;
	}

	if ((cpuinfo.flag&CPU_x86_SSE2)!=0) {
		as->CleanMem=(tfSTDCALL_PROC_p_uint)&_CleanMemSSE2;
		as->MoveMem=(tfSTDCALL_PROC_p_p_uint)&_MoveMemSSE2;
		as->MoveBack=(tfSTDCALL_PROC_p_p_uint)&_MoveBackSSE2;
		as->StocIMem=(tfSTDCALL_PROC_p_uint_uint)&_StosIMEMSSE2;
		as->ILogSize=(tfSTDCALL_int_FUNC_int)&_ILogSizeSSE2;
		//as->NoiseGet=(bt::tfSTDCALL_int_FUNC)&_NoiseGetSSE2;
	}

	if ((cpuinfo.flag&CPU_x86_SSE3)!=0) {
		//as->MoveMem=(tfSTDCALL_PROC_p_p_uint)&_MoveMemSSE3;
		//as->StocIMem=(tfSTDCALL_PROC_p_uint_uint)&_StosIMEMSSE3;
	}

	if ((cpuinfo.flag&CPU_x86_SSE4)!=0) {
		//as->StocIMem=(tfSTDCALL_PROC_p_uint_uint)&_StosIMEMSSE4;
	}

	if ((cpuinfo.flag&CPU_x86_AVX)!=0) {
		as->CleanMem=(tfSTDCALL_PROC_p_uint)&_CleanMemAVX;
		as->MoveMem=(tfSTDCALL_PROC_p_p_uint)&_MoveMemAVX;
	}
}

void initx86Array(void*_conteiner)
{
	sFunctionsArrayCPU *as=(sFunctionsArrayCPU *)_conteiner;
	as->version=0;

	//as->MPFind=(bt::tfSTDCALL_p_FUNC_p_p)&bt::_MPFindCPU;

	if ((cpuinfo.flag&CPU_x86_SSE2)!=0) {
		//as->MPFind=(bt::tfSTDCALL_p_FUNC_p_p)&bt::_MPFindSSE2;
	}
}

void initx86Render(void*_conteiner)
{
	sFunctionsRenderCPU *as=(sFunctionsRenderCPU *)_conteiner;
	as->version=0;

	as->S4AFdraw=(tfSTDCALL_PROC_p)_S4AFdrawCPU;
	as->S4AFDLdraw=(tfSTDCALL_PROC_p)_S4AFDLdrawCPU;

	if ((cpuinfo.flag&CPU_x86_SSE)!=0) {
		as->S4AFDLdraw=(tfSTDCALL_PROC_p)_S4AFDLdrawSSE;
	}

	if ((cpuinfo.flag&CPU_x86_SSE2)!=0) {
		as->S4AFSdraw=(tfSTDCALL_PROC_p)_S4AFSdrawSSE2;
		as->S4AFDLSdraw=(tfSTDCALL_PROC_p)_S4AFDLSdrawSSE2;
	}

	if ((cpuinfo.flag&CPU_x86_SSE3)!=0) {
		as->V3BHalfTexel=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V3BHalfTexelSSE3;
		as->V4BHalfTexel=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V4BHalfTexelSSE3;
		as->V3BTexel=(bt::tfSTDCALL_PROC_p_p_int_float_float)&bt::_V3BTexelSSE3;
		as->V4BTexel=(bt::tfSTDCALL_PROC_p_p_int_float_float)&bt::_V4BTexelSSE3;
	}
}

}

#endif

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif