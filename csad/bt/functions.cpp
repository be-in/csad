/*
 * functions.cpp
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <bt/functions.h>
#include <bt/macroscpu.h>
#include "base/baseapi.h"
#include "base/basemath.h"
#include "base/basevector.h"
#include "base/basearrayvector.h"
#include "base/basearray.h"
#include "base/baseext.h"
#include "base/baserender.h"
#include "script.h"

#ifdef CPU_ARM_32
#endif
#ifdef CPU_X86_32
#include "x86/x86functions.h"
#endif
#ifdef CPU_X86_64
#include "x86_64/x86_64functions.h"
#endif
#ifdef CPU_E2K_64
#include "e2k_64/e2k_64functions.h"
#endif

OPTIMIZE_ON;

char FDiv[131072];

bt::sFunctionsAPICPU btFunctions={0,
	(bt::tfSTDCALL_long_FUNC)&bt::_TSCDEFF,(bt::tfSTDCALL_uint_FUNC)&bt::_GetFuncFlagDEF,(bt::tfSTDCALL_p_FUNC)bt::getCPUstring,
	(bt::tfSTDCALL_PROC_uint)bt::initFunc,(bt::tfSTDCALL_PROC)bt::resetFunc};
bt::sFunctionsMathCPU matFunctions;
bt::sFunctionsVectorCPU vecFunctions;
bt::sFunctionsArrayVectorCPU arvFunctions;
bt::sFunctionsExtensionCPU extFunctions;
bt::sFunctionsArrayCPU arrFunctions;
bt::sFunctionsObjectCPU objFunctions;
bt::sFunctionsRenderCPU renFunctions;

namespace bt {

enum States {
	VALIDED = 0x011F1C01,
	FREE = 0
};

unsigned _int32 fisVal=FREE;
char cpustring[128]={0};

void _APICALL initFunc(unsigned _int32 flagMask)
{
	//flagMask=CPU_x86_FPU | CPU_x86_SSE | CPU_x86_SSE2 | CPU_x86_SSE3;
	if (fisVal==VALIDED) return;

	fisVal=VALIDED;
	initBT(&btFunctions);
	initMath(&matFunctions);
	initVector(&vecFunctions);
	initArrayVector(&arvFunctions);
	initExtension(&extFunctions);
	initArray(&arrFunctions);
	initObject(&objFunctions);
	initRender(&renFunctions);

#ifdef CPU_BT
#ifdef CPU_X86_32
	bt::initx86(flagMask);
	bt::initx86BT(&btFunctions);
	bt::initx86Math(&matFunctions);
	bt::initx86Vector(&vecFunctions);
	bt::initx86ArrayVector(&arvFunctions);
	bt::initx86Extension(&extFunctions);
	bt::initx86Array(&arrFunctions);
	bt::initx86Render(&renFunctions);
#endif
#ifdef CPU_X86_64
	bt::initx86_64(flagMask);
	bt::initx86_64BT(&btFunctions);
	bt::initx86_64Math(&matFunctions);
	bt::initx86_64Vector(&vecFunctions);
	bt::initx86_64ArrayVector(&arvFunctions);
	bt::initx86_64Extension(&extFunctions);
	bt::initx86_64Array(&arrFunctions);
	bt::initx86_64Render(&renFunctions);
#endif
#ifdef CPU_E2K_64
	bt::inite2k_64(flagMask);
	bt::inite2k_64BT(&btFunctions);
	bt::inite2k_64Math(&matFunctions);
	bt::inite2k_64Vector(&vecFunctions);
	bt::inite2k_64ArrayVector(&arvFunctions);
	bt::inite2k_64Extension(&extFunctions);
	bt::inite2k_64Render(&renFunctions);
#endif
#endif
}

void _APICALL resetFunc() {
	fisVal=0;
}

char* _APICALL getCPUstring()
{
#ifdef CPU_BT
#ifdef CPU_X86_32
	bt::cpuinfotostring(cpustring);
#endif
#ifdef CPU_X86_64
	bt::cpuinfotostring(cpustring);
#endif
#endif
	return cpustring;
}

void _APICALL initBT(void*_conteiner)
{
	bt::sFunctionsAPICPU *as=(bt::sFunctionsAPICPU *)_conteiner;
	as->version=0;

	as->TSC=(bt::tfSTDCALL_long_FUNC)&bt::_TSCDEFF;
	as->FlagCPU=(bt::tfSTDCALL_uint_FUNC)&bt::_GetFuncFlagDEF;
	as->StringCPU=(bt::tfSTDCALL_p_FUNC)getCPUstring;
	as->InitFunc=(bt::tfSTDCALL_PROC_uint)initFunc;
	as->ResetFunc=(bt::tfSTDCALL_PROC)resetFunc;
}

void _APICALL initMath(void*_conteiner)
{
	bt::sFunctionsMathCPU *as=(bt::sFunctionsMathCPU *)_conteiner;
	as->version=0;

	as->FSqrt=(bt::tfSTDCALL_float_FUNC_float)&bt::_FsqrtDEF;
	as->DSqrt=(bt::tfSTDCALL_double_FUNC_double)&bt::_DsqrtDEF;
	as->FFastInvSqrt=(bt::tfSTDCALL_float_FUNC_float)&bt::_FFastInvSqrtDEF;
	as->DFastInvSqrt=(bt::tfSTDCALL_double_FUNC_double)&bt::_DFastInvSqrtDEF;
	as->FSin = (bt::tfSTDCALL_float_FUNC_float)&bt::_FSinDEF;
	as->FCos = (bt::tfSTDCALL_float_FUNC_float)&bt::_FCosDEF;
	as->FSinCos=(bt::tfSTDCALL_PROC_float_p_p)&bt::_FSinCosDEF;
	as->DSinCos=(bt::tfSTDCALL_PROC_double_p_p)&bt::_DSinCosDEF;
	as->FFastSinCos=(bt::tfSTDCALL_PROC_float_p_p)&bt::_FSinCosFASTDEF;
	as->DFastSinCos=(bt::tfSTDCALL_PROC_double_p_p)&bt::_DSinCosFASTDEF;
	as->FArcTg=(bt::tfSTDCALL_float_FUNC_float_float)&bt::_FArcTgDEF;
	as->DArcTg=(bt::tfSTDCALL_double_FUNC_double_double)&bt::_DArcTgDEF;
	as->Fmul2N=(bt::tfSTDCALL_float_FUNC_float_int)&bt::_Fmul2NDEF;
	as->Dmul2N=(bt::tfSTDCALL_double_FUNC_double_int)&bt::_Dmul2NDEF;
	as->FLerp=(bt::tfSTDCALL_float_FUNC_float_float_float)&bt::_FLerpDEF;
	as->DLerp=(bt::tfSTDCALL_double_FUNC_double_double_double)&bt::_DLerpDEF;
	as->FTrunc=(bt::tfSTDCALL_int_FUNC_float)&bt::_FTruncDEF;
	as->DTrunc=(bt::tfSTDCALL_int_FUNC_double)&bt::_DTruncDEF;
	as->FRound=(bt::tfSTDCALL_int_FUNC_float)&bt::_FRoundDEF;
	as->DRound=(bt::tfSTDCALL_int_FUNC_double)&bt::_DRoundDEF;
	as->IToF = (bt::tfSTDCALL_float_FUNC_int)&bt::_IToFDEF;
	as->LToD = (bt::tfSTDCALL_double_FUNC_long)&bt::_LToDDEF;
	as->Fmul2NTrunc=(bt::tfSTDCALL_int_FUNC_float_int)&bt::_Fmul2NTruncDEF;
	as->Dmul2NTrunc=(bt::tfSTDCALL_int_FUNC_double_int)&bt::_Dmul2NTruncDEF;
	as->Fmul2NRound=(bt::tfSTDCALL_int_FUNC_float_int)&bt::_Fmul2NRoundDEF;
	as->Dmul2NRound=(bt::tfSTDCALL_int_FUNC_double_int)&bt::_Dmul2NRoundDEF;
	as->FScaleMod = (bt::tfSTDCALL_float_FUNC_float_float)&bt::_FScaleModDEF;
	as->DScaleMod = (bt::tfSTDCALL_double_FUNC_double_double)&bt::_DScaleModDEF;
	as->FCRCC=(bt::tfSTDCALL_PROC_float_float_float_float_p)&bt::_FCRCCDEF;
	as->DCRCC=(bt::tfSTDCALL_PROC_double_double_double_double_p)&bt::_DCRCCDEF;
	as->FPCRCC=(bt::tfSTDCALL_PROC_p_p)&bt::_FPCRCCDEF;
	as->DPCRCC=(bt::tfSTDCALL_PROC_p_p)&bt::_DPCRCCDEF;
	as->FSplineCR=(bt::tfSTDCALL_PROC_p_p_float_float)&bt::_FSplineCRDEF;
	as->DSplineCR=(bt::tfSTDCALL_PROC_p_p_double_double)&bt::_DSplineCRDEF;
	as->FExp=(bt::tfSTDCALL_float_FUNC_float)&bt::_FExpDEF;
	as->DExp=(bt::tfSTDCALL_double_FUNC_double)&bt::_DExpDEF;
	as->FLog2=(bt::tfSTDCALL_float_FUNC_float)&bt::_FLog2DEF;
	as->DLog2=(bt::tfSTDCALL_double_FUNC_double)&bt::_DLog2DEF;
	as->ILog2=(bt::tfSTDCALL_int_FUNC_int)&bt::_ILog2DEF;
	as->LLog2=(bt::tfSTDCALL_int_FUNC_long)&bt::_LLog2DEF;
	as->FPoly1=(bt::tfSTDCALL_float_FUNC_p_uint_float)&bt::_FPoly1DEF;
	as->DPoly1=(bt::tfSTDCALL_double_FUNC_p_uint_double)&bt::_DPoly1DEF;
	as->FPoly2=(bt::tfSTDCALL_float_FUNC_p_uint_uint_float_float)&bt::_FPoly2DEF;
	as->DPoly2=(bt::tfSTDCALL_double_FUNC_p_uint_uint_double_double)&bt::_DPoly2DEF;
	as->FPolyM=(bt::tfSTDCALL_float_FUNC_p_p_p_uint)&bt::_FPolyMDEF;
	as->DPolyM=(bt::tfSTDCALL_double_FUNC_p_p_p_uint)&bt::_DPolyMDEF;

	as->FMinMax=(bt::tfSTDCALL_PROC_p_p_p)&bt::_FMinMaxDEF;
	as->DMinMax=(bt::tfSTDCALL_PROC_p_p_p)&bt::_DMinMaxDEF;
}

void _APICALL initVector(void*_conteiner)
{
	bt::sFunctionsVectorCPU *as=(bt::sFunctionsVectorCPU *)_conteiner;
	as->version=0;

	as->V4R8=(bt::tfSTDCALL_PROC_p_p)&bt::_V4R8DEF;
	as->V4R16=(bt::tfSTDCALL_PROC_p_p)&bt::_V4R16DEF;
	as->V4R32=(bt::tfSTDCALL_PROC_p_p)&bt::_V4R32DEF;
	as->V4R64=(bt::tfSTDCALL_PROC_p_p)&bt::_V4R64DEF;

	as->V2R32Copy=(bt::tfSTDCALL_PROC_p_p)&bt::_V2R32CopyDEF;
	as->V3R32Copy=(bt::tfSTDCALL_PROC_p_p)&bt::_V3R32CopyDEF;
	as->V4R32Copy=(bt::tfSTDCALL_PROC_p_p)&bt::_V4R32CopyDEF;
	as->V2R64Copy=(bt::tfSTDCALL_PROC_p_p)&bt::_V2R64CopyDEF;
	as->V3R64Copy=(bt::tfSTDCALL_PROC_p_p)&bt::_V3R64CopyDEF;
	as->V4R64Copy=(bt::tfSTDCALL_PROC_p_p)&bt::_V4R64CopyDEF;

	as->V2BTo2F=(bt::tfSTDCALL_PROC_p_p)&bt::_V2BTo2FDEF;
	as->V2BTo2D=(bt::tfSTDCALL_PROC_p_p)&bt::_V2BTo2DDEF;
	as->V3BTo3F=(bt::tfSTDCALL_PROC_p_p)&bt::_V3BTo3FDEF;
	as->V3BTo3D=(bt::tfSTDCALL_PROC_p_p)&bt::_V3BTo3DDEF;
	as->V4BTo4F=(bt::tfSTDCALL_PROC_p_p)&bt::_V4BTo4FDEF;
	as->V4BTo4D=(bt::tfSTDCALL_PROC_p_p)&bt::_V4BTo4DDEF;
	as->V2ITo2F=(bt::tfSTDCALL_PROC_p_p)&bt::_V2ITo2FDEF;
	as->V2ITo2D=(bt::tfSTDCALL_PROC_p_p)&bt::_V2ITo2DDEF;
	as->V3ITo3F=(bt::tfSTDCALL_PROC_p_p)&bt::_V3ITo3FDEF;
	as->V3ITo3D=(bt::tfSTDCALL_PROC_p_p)&bt::_V3ITo3DDEF;
	as->V4ITo4B=(bt::tfSTDCALL_PROC_p_p)&bt::_V4ITo4BDEF;
	as->V4ITo4F=(bt::tfSTDCALL_PROC_p_p)&bt::_V4ITo4FDEF;
	as->V4ITo4D=(bt::tfSTDCALL_PROC_p_p)&bt::_V4ITo4DDEF;
	as->V2FTo2B=(bt::tfSTDCALL_PROC_p_p)&bt::_V2FTo2BDEF;
	as->V2FTo2I=(bt::tfSTDCALL_PROC_p_p)&bt::_V2FTo2IDEF;
	as->V2FTTo2I=(bt::tfSTDCALL_PROC_p_p)&bt::_V2FTTo2IDEF;
	as->V2FTo2D=(bt::tfSTDCALL_PROC_p_p)&bt::_V2FTo2DDEF;
	as->V3FTo3B=(bt::tfSTDCALL_PROC_p_p)&bt::_V3FTo3BDEF;
	as->V3FTo3I=(bt::tfSTDCALL_PROC_p_p)&bt::_V3FTo3IDEF;
	as->V3FTTo3I=(bt::tfSTDCALL_PROC_p_p)&bt::_V3FTTo3IDEF;
	as->V3FTo3D=(bt::tfSTDCALL_PROC_p_p)&bt::_V3FTo3DDEF;
	as->V4FTo4B=(bt::tfSTDCALL_PROC_p_p)&bt::_V4FTo4BDEF;
	as->V4FTo4I=(bt::tfSTDCALL_PROC_p_p)&bt::_V4FTo4IDEF;
	as->V4FTTo4I=(bt::tfSTDCALL_PROC_p_p)&bt::_V4FTTo4IDEF;
	as->V4FTo4D=(bt::tfSTDCALL_PROC_p_p)&bt::_V4FTo4DDEF;
	as->V2DTo2B=(bt::tfSTDCALL_PROC_p_p)&bt::_V2DTo2BDEF;
	as->V2DTo2I=(bt::tfSTDCALL_PROC_p_p)&bt::_V2DTo2IDEF;
	as->V2DTTo2I=(bt::tfSTDCALL_PROC_p_p)&bt::_V2DTTo2IDEF;
	as->V2DTo2L=(bt::tfSTDCALL_PROC_p_p)&bt::_V2DTo2LDEF;
	as->V2DTTo2L=(bt::tfSTDCALL_PROC_p_p)&bt::_V2DTTo2LDEF;
	as->V2DTo2F=(bt::tfSTDCALL_PROC_p_p)&bt::_V2DTo2FDEF;
	as->V3DTo3B=(bt::tfSTDCALL_PROC_p_p)&bt::_V3DTo3BDEF;
	as->V3DTo3I=(bt::tfSTDCALL_PROC_p_p)&bt::_V3DTo3IDEF;
	as->V3DTTo3I=(bt::tfSTDCALL_PROC_p_p)&bt::_V3DTTo3IDEF;
	as->V3DTo3F=(bt::tfSTDCALL_PROC_p_p)&bt::_V3DTo3FDEF;
	as->V4DTo4B=(bt::tfSTDCALL_PROC_p_p)&bt::_V4DTo4BDEF;
	as->V4DTo4I=(bt::tfSTDCALL_PROC_p_p)&bt::_V4DTo4IDEF;
	as->V4DTTo4I=(bt::tfSTDCALL_PROC_p_p)&bt::_V4DTTo4IDEF;
	as->V4DTo4F=(bt::tfSTDCALL_PROC_p_p)&bt::_V4DTo4FDEF;

	as->V2FInv=(bt::tfSTDCALL_PROC_p_p)&bt::_V2FInvDEF;
	as->V3FInv=(bt::tfSTDCALL_PROC_p_p)&bt::_V3FInvDEF;
	as->V4FInv=(bt::tfSTDCALL_PROC_p_p)&bt::_V4FInvDEF;
	as->V2DInv=(bt::tfSTDCALL_PROC_p_p)&bt::_V2DInvDEF;
	as->V3DInv=(bt::tfSTDCALL_PROC_p_p)&bt::_V3DInvDEF;
	as->V4DInv=(bt::tfSTDCALL_PROC_p_p)&bt::_V4DInvDEF;

	as->V2FAbs=(bt::tfSTDCALL_PROC_p_p)&bt::_V2FAbsDEF;
	as->V3FAbs=(bt::tfSTDCALL_PROC_p_p)&bt::_V3FAbsDEF;
	as->V4FAbs=(bt::tfSTDCALL_PROC_p_p)&bt::_V4FAbsDEF;
	as->V2DAbs=(bt::tfSTDCALL_PROC_p_p)&bt::_V2DAbsDEF;
	as->V3DAbs=(bt::tfSTDCALL_PROC_p_p)&bt::_V3DAbsDEF;
	as->V4DAbs=(bt::tfSTDCALL_PROC_p_p)&bt::_V4DAbsDEF;

	as->V2FMinMax=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2FMinMaxDEF;
	as->V3FMinMax=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3FMinMaxDEF;
	as->V4FMinMax=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V4FMinMaxDEF;
	as->V2DMinMax=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2DMinMaxDEF;
	as->V3DMinMax=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3DMinMaxDEF;
	as->V4DMinMax=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V4DMinMaxDEF;

	as->V2IAdd=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2IAddDEF;
	as->V3IAdd=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3IAddDEF;
	as->V4IAdd=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V4IAddDEF;
	as->V2FAdd=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2FAddDEF;
	as->V3FAdd=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3FAddDEF;
	as->V4FAdd=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V4FAddDEF;
	as->V2LAdd=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2LAddDEF;
	as->V2DAdd=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2DAddDEF;
	as->V3DAdd=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3DAddDEF;
	as->V4DAdd=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V4DAddDEF;

	as->V2ISub=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2ISubDEF;
	as->V3ISub=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3ISubDEF;
	as->V4ISub=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V4ISubDEF;
	as->V2FSub=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2FSubDEF;
	as->V3FSub=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3FSubDEF;
	as->V4FSub=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V4FSubDEF;
	as->V2LSub=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2LSubDEF;
	as->V2DSub=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2DSubDEF;
	as->V3DSub=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3DSubDEF;
	as->V4DSub=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V4DSubDEF;

	as->V2IScale=(bt::tfSTDCALL_PROC_p_p_float)&bt::_V2IScaleDEF;
	as->V3IScale=(bt::tfSTDCALL_PROC_p_p_float)&bt::_V3IScaleDEF;
	as->V4IScale=(bt::tfSTDCALL_PROC_p_p_float)&bt::_V4IScaleDEF;
	as->V2FScale=(bt::tfSTDCALL_PROC_p_p_float)&bt::_V2FScaleDEF;
	as->V3FScale=(bt::tfSTDCALL_PROC_p_p_float)&bt::_V3FScaleDEF;
	as->V4FScale=(bt::tfSTDCALL_PROC_p_p_float)&bt::_V4FScaleDEF;
	as->V2LScale=(bt::tfSTDCALL_PROC_p_p_double)&bt::_V2LScaleDEF;
	//as->V3LScale=(bt::tfSTDCALL_PROC_p_p_double)&bt::_V3LScaleDEF;
	//as->V4LScale=(bt::tfSTDCALL_PROC_p_p_double)&bt::_V4LScaleDEF;
	as->V2DScale=(bt::tfSTDCALL_PROC_p_p_double)&bt::_V2DScaleDEF;
	as->V3DScale=(bt::tfSTDCALL_PROC_p_p_double)&bt::_V3DScaleDEF;
	as->V4DScale=(bt::tfSTDCALL_PROC_p_p_double)&bt::_V4DScaleDEF;

	as->V2IMul=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2IMulDEF;
	as->V3IMul=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3IMulDEF;
	as->V4IMul=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V4IMulDEF;
	as->V2FMul=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2FMulDEF;
	as->V3FMul=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3FMulDEF;
	as->V4FMul=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V4FMulDEF;
	as->V2DMul=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2DMulDEF;
	as->V3DMul=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3DMulDEF;
	as->V4DMul=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V4DMulDEF;

	as->V2FDiv=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2FDivDEF;
	as->V3FDiv=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3FDivDEF;
	as->V4FDiv=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V4FDivDEF;
	as->V2DDiv=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2DDivDEF;
	as->V3DDiv=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3DDivDEF;
	as->V4DDiv=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V4DDivDEF;

	as->V2Fmul2NTrunc=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V2Fmul2NTruncDEF;
	as->V3Fmul2NTrunc=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V3Fmul2NTruncDEF;
	as->V4Fmul2NTrunc=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V4Fmul2NTruncDEF;
	as->V2Dmul2NTrunc=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V2Dmul2NTruncDEF;
	as->V3Dmul2NTrunc=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V3Dmul2NTruncDEF;
	as->V4Dmul2NTrunc=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V4Dmul2NTruncDEF;

	as->V2Fmul2NRound=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V2Fmul2NRoundDEF;
	as->V3Fmul2NRound=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V3Fmul2NRoundDEF;
	as->V4Fmul2NRound=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V4Fmul2NRoundDEF;
	as->V2Dmul2NRound=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V2Dmul2NRoundDEF;
	as->V3Dmul2NRound=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V3Dmul2NRoundDEF;
	as->V4Dmul2NRound=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V4Dmul2NRoundDEF;

	as->V2Imul2N=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V2Imul2NDEF;
	as->V3Imul2N=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V3Imul2NDEF;
	as->V4Imul2N=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V4Imul2NDEF;
	as->V2Fmul2N=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V2Fmul2NDEF;
	as->V3Fmul2N=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V3Fmul2NDEF;
	as->V4Fmul2N=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V4Fmul2NDEF;
	as->V2Dmul2N=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V2Dmul2NDEF;
	as->V3Dmul2N=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V3Dmul2NDEF;
	as->V4Dmul2N=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V4Dmul2NDEF;

	as->V2FDot=(bt::tfSTDCALL_float_FUNC_p_p)&bt::_V2FDotDEF;
	as->V3FDot=(bt::tfSTDCALL_float_FUNC_p_p)&bt::_V3FDotDEF;
	as->V4FDot=(bt::tfSTDCALL_float_FUNC_p_p)&bt::_V4FDotDEF;
	as->V2DDot=(bt::tfSTDCALL_double_FUNC_p_p)&bt::_V2DDotDEF;
	as->V3DDot=(bt::tfSTDCALL_double_FUNC_p_p)&bt::_V3DDotDEF;
	as->V4DDot=(bt::tfSTDCALL_double_FUNC_p_p)&bt::_V4DDotDEF;

	as->V2ILength2=(bt::tfSTDCALL_int_FUNC_p)&bt::_V2ILength2DEF;
	as->V2FLength2=(bt::tfSTDCALL_float_FUNC_p)&bt::_V2FLength2DEF;
	as->V3FLength2=(bt::tfSTDCALL_float_FUNC_p)&bt::_V3FLength2DEF;
	as->V4FLength2=(bt::tfSTDCALL_float_FUNC_p)&bt::_V4FLength2DEF;
	as->V2LLength2=(bt::tfSTDCALL_long_FUNC_p)&bt::_V2LLength2DEF;
	as->V2DLength2=(bt::tfSTDCALL_double_FUNC_p)&bt::_V2DLength2DEF;
	as->V3DLength2=(bt::tfSTDCALL_double_FUNC_p)&bt::_V3DLength2DEF;
	as->V4DLength2=(bt::tfSTDCALL_double_FUNC_p)&bt::_V4DLength2DEF;

	as->V2INormalMul2N=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V2INormalMul2NDEF;
	as->V3INormalMul2N=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V3INormalMul2NDEF;
	as->V4INormalMul2N=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V4INormalMul2NDEF;

	as->V2FNormal=(bt::tfSTDCALL_PROC_p_p)&bt::_V2FNormalDEF;
	as->V3FNormal=(bt::tfSTDCALL_PROC_p_p)&bt::_V3FNormalDEF;
	as->V4FNormal=(bt::tfSTDCALL_PROC_p_p)&bt::_V4FNormalDEF;
	as->V2DNormal=(bt::tfSTDCALL_PROC_p_p)&bt::_V2DNormalDEF;
	as->V3DNormal=(bt::tfSTDCALL_PROC_p_p)&bt::_V3DNormalDEF;
	as->V4DNormal=(bt::tfSTDCALL_PROC_p_p)&bt::_V4DNormalDEF;

	as->V2FFastNormal=(bt::tfSTDCALL_PROC_p_p)&bt::_V2FFastNormalDEF;
	as->V3FFastNormal=(bt::tfSTDCALL_PROC_p_p)&bt::_V3FFastNormalDEF;
	as->V4FFastNormal=(bt::tfSTDCALL_PROC_p_p)&bt::_V4FFastNormalDEF;
	as->V2DFastNormal=(bt::tfSTDCALL_PROC_p_p)&bt::_V2DFastNormalDEF;
	as->V3DFastNormal=(bt::tfSTDCALL_PROC_p_p)&bt::_V3DFastNormalDEF;
	as->V4DFastNormal=(bt::tfSTDCALL_PROC_p_p)&bt::_V4DFastNormalDEF;

	as->V2ICross=(bt::tfSTDCALL_int_FUNC_p_p)&bt::_V2ICrossDEF;
	as->V2FCross=(bt::tfSTDCALL_float_FUNC_p_p)&bt::_V2FCrossDEF;
	as->V3FCross=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3FCrossDEF;
	as->V2LCross=(bt::tfSTDCALL_long_FUNC_p_p)&bt::_V2LCrossDEF;
	as->V2DCross=(bt::tfSTDCALL_double_FUNC_p_p)&bt::_V2DCrossDEF;
	as->V3DCross=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3DCrossDEF;

	as->V2FLerp=(bt::tfSTDCALL_PROC_p_p_p_float)&bt::_V2FLerpDEF;
	as->V3FLerp=(bt::tfSTDCALL_PROC_p_p_p_float)&bt::_V3FLerpDEF;
	as->V4FLerp=(bt::tfSTDCALL_PROC_p_p_p_float)&bt::_V4FLerpDEF;
	as->V2DLerp=(bt::tfSTDCALL_PROC_p_p_p_double)&bt::_V2DLerpDEF;
	as->V3DLerp=(bt::tfSTDCALL_PROC_p_p_p_double)&bt::_V3DLerpDEF;
	as->V4DLerp=(bt::tfSTDCALL_PROC_p_p_p_double)&bt::_V4DLerpDEF;

	as->V2FCombine=(bt::tfSTDCALL_PROC_p_p_p_float_float)&bt::_V2FCombineDEF;
	as->V3FCombine=(bt::tfSTDCALL_PROC_p_p_p_float_float)&bt::_V3FCombineDEF;
	as->V4FCombine=(bt::tfSTDCALL_PROC_p_p_p_float_float)&bt::_V4FCombineDEF;
	as->V2DCombine=(bt::tfSTDCALL_PROC_p_p_p_double_double)&bt::_V2DCombineDEF;
	as->V3DCombine=(bt::tfSTDCALL_PROC_p_p_p_double_double)&bt::_V3DCombineDEF;
	as->V4DCombine=(bt::tfSTDCALL_PROC_p_p_p_double_double)&bt::_V4DCombineDEF;

	as->V2IQDFL=(bt::tfSTDCALL_int_FUNC_p_p_p)&bt::_V2IQDFLDEF;
	as->V2FQDFL=(bt::tfSTDCALL_float_FUNC_p_p_p)&bt::_V2FQDFLDEF;
	as->V2LQDFL=(bt::tfSTDCALL_long_FUNC_p_p_p)&bt::_V2LQDFLDEF;
	as->V2DQDFL=(bt::tfSTDCALL_double_FUNC_p_p_p)&bt::_V2DQDFLDEF;

	as->V2FReflect=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2FReflectDEF;
	as->V2DReflect=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2DReflectDEF;
	as->V3FReflect=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3FReflectDEF;
	as->V3DReflect=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3DReflectDEF;

	as->V2FAngle=(bt::tfSTDCALL_float_FUNC_p_p)&bt::_V2FAngleDEF;
	as->V3FAngle=(bt::tfSTDCALL_float_FUNC_p_p)&bt::_V3FAngleDEF;
	as->V2DAngle=(bt::tfSTDCALL_double_FUNC_p_p)&bt::_V2DAngleDEF;
	as->V3DAngle=(bt::tfSTDCALL_double_FUNC_p_p)&bt::_V3DAngleDEF;

	as->V3FDPFR=(bt::tfSTDCALL_float_FUNC_p_p)&bt::_V3FDPFRDEF;
	as->V3DDPFR=(bt::tfSTDCALL_double_FUNC_p_p)&bt::_V3DDPFRDEF;

	as->V3FTriNorm=(bt::tfSTDCALL_PROC_p_p_p_p)&bt::_V3FTriNormDEF;
	as->V3DTriNorm=(bt::tfSTDCALL_PROC_p_p_p_p)&bt::_V3DTriNormDEF;
	
	as->V3FAddTriNorm=(bt::tfSTDCALL_PROC_p_p_p_int)&bt::_V3FAddTriNormDEF;
	as->V3FAdd3DTriNorm=(bt::tfSTDCALL_PROC_p_p_p_int)&bt::_V3FAdd3DTriNormDEF;
	as->V3DAddTriNorm=(bt::tfSTDCALL_PROC_p_p_p_int)&bt::_V3DAddTriNormDEF;

	as->V4FQuaternion=(bt::tfSTDCALL_PROC_p_p)&bt::_V4FQuaternionDEF;
	as->V4DQuaternion=(bt::tfSTDCALL_PROC_p_p)&bt::_V4DQuaternionDEF;
	as->V4FFastQuaternion=(bt::tfSTDCALL_PROC_p_p)&bt::_V4FFastQuaternionDEF;
	as->V4DFastQuaternion=(bt::tfSTDCALL_PROC_p_p)&bt::_V4DFastQuaternionDEF;

	as->V2ITransform=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2ITransformDEF; //??
	as->V2FTransform=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2FTransformDEF;
	as->V3FTransform=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3FTransformDEF;
	as->V4FTransform=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V4FTransformDEF;
	as->V2DTransform=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2DTransformDEF;
	as->V3DTransform=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3DTransformDEF;
	as->V4DTransform=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V4DTransformDEF;

	as->V2FMMul=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2FMMulDEF;
	as->V3FMMul=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3FMMulDEF;
	as->V4FMMul=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V4FTransformDEF;
	as->V2DMMul=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2DMMulDEF;
	as->V3DMMul=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3DMMulDEF;
	as->V4DMMul=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V4DTransformDEF;

	as->V2FProj=(bt::tfSTDCALL_int_FUNC_p_p_p_p_p)&bt::_V2FProjDEF;
	as->V3FProj=(bt::tfSTDCALL_int_FUNC_p_p_p_p_p)&bt::_V3FProjDEF;
	as->V4FProj=(bt::tfSTDCALL_int_FUNC_p_p_p_p_p)&bt::_V4FProjDEF;
	as->V2DProj=(bt::tfSTDCALL_int_FUNC_p_p_p_p_p)&bt::_V2DProjDEF;
	as->V3DProj=(bt::tfSTDCALL_int_FUNC_p_p_p_p_p)&bt::_V3DProjDEF;
	as->V4DProj=(bt::tfSTDCALL_int_FUNC_p_p_p_p_p)&bt::_V4DProjDEF;

	as->Q4FVector=(bt::tfSTDCALL_PROC_p_p)&bt::_Q4FVectorDEF;
	as->Q4DVector=(bt::tfSTDCALL_PROC_p_p)&bt::_Q4DVectorDEF;
	as->QFInv=(bt::tfSTDCALL_PROC_p_p)&bt::_QFInvDEF;
	as->QDInv=(bt::tfSTDCALL_PROC_p_p)&bt::_QDInvDEF;
	as->QFAdd=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V4FAddDEF;
	as->QDAdd=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V4DAddDEF;
	as->QFMul=(bt::tfSTDCALL_PROC_p_p_p)&bt::_QFMulDEF;
	as->QDMul=(bt::tfSTDCALL_PROC_p_p_p)&bt::_QDMulDEF;
	as->QFNorm=(bt::tfSTDCALL_float_FUNC_p)&bt::_V4FLength2DEF;
	as->QDNorm=(bt::tfSTDCALL_double_FUNC_p)&bt::_V4DLength2DEF;
	as->QFEuler=(bt::tfSTDCALL_PROC_p_p)&bt::_QFEulerDEF;
	as->QDEuler=(bt::tfSTDCALL_PROC_p_p)&bt::_QDEulerDEF;
	as->Q4FMatrix=(bt::tfSTDCALL_PROC_p_p)&bt::_Q4FMatrixDEF;
	as->Q4DMatrix=(bt::tfSTDCALL_PROC_p_p)&bt::_Q4DMatrixDEF;

	as->V2FAfineTransform=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2FAfineTransformDEF;
	as->V2DAfineTransform=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V2DAfineTransformDEF;
	as->Q2FInvTransform=(bt::tfSTDCALL_PROC_p_p_p)&bt::_Q2FInvTransformDEF;
	as->Q2DInvTransform=(bt::tfSTDCALL_PROC_p_p_p)&bt::_Q2DInvTransformDEF;
	as->Q3FInvTransform=(bt::tfSTDCALL_PROC_p_p_p)&bt::_Q3FInvTransformDEF;
	as->Q3DInvTransform=(bt::tfSTDCALL_PROC_p_p_p)&bt::_Q3DInvTransformDEF;

	as->M4FTranspose=(bt::tfSTDCALL_PROC_p_p)&bt::_M4FTransposeDEF;
	as->M4DTranspose=(bt::tfSTDCALL_PROC_p_p)&bt::_M4DTransposeDEF;
	as->M4FMul=(bt::tfSTDCALL_PROC_p_p_p)&bt::_M4FMulDEF;
	as->M4DMul=(bt::tfSTDCALL_PROC_p_p_p)&bt::_M4DMulDEF;
	as->M4FInv=(bt::tfSTDCALL_int_FUNC_p_p)&bt::_M4FInvDEF;
	as->M4DInv=(bt::tfSTDCALL_int_FUNC_p_p)&bt::_M4DInvDEF;

	as->M4FPerspective=(bt::tfSTDCALL_PROC_p_int_int_float_float_float)&bt::_M4FPerspectiveDEF;
	as->M4DPerspective=(bt::tfSTDCALL_PROC_p_int_int_double_double_double)&bt::_M4DPerspectiveDEF;
	as->M4FOrtographic=(bt::tfSTDCALL_PROC_p_int_int_float_float_float)&bt::_M4FOrtographicDEF;
	as->M4DOrtographic=(bt::tfSTDCALL_PROC_p_int_int_double_double_double)&bt::_M4DOrtographicDEF;

	as->M4FIdentity=(bt::tfSTDCALL_PROC_p)&bt::_M4FIdentityDEF;
	as->M4DIdentity=(bt::tfSTDCALL_PROC_p)&bt::_M4DIdentityDEF;

	as->M4FQuaternion=(bt::tfSTDCALL_PROC_p_p)&bt::_M4FQuaternionDEF;
	as->M4DQuaternion=(bt::tfSTDCALL_PROC_p_p)&bt::_M4DQuaternionDEF;

	as->M4FTranslate=(bt::tfSTDCALL_PROC_p_p)&bt::_M4FTranslateDEF;
	as->M4DTranslate=(bt::tfSTDCALL_PROC_p_p)&bt::_M4DTranslateDEF;

	as->M4FScale=(bt::tfSTDCALL_PROC_p_p)&bt::_M4FScaleDEF;
	as->M4DScale=(bt::tfSTDCALL_PROC_p_p)&bt::_M4DScaleDEF;

	as->M4FAddTranslate=(bt::tfSTDCALL_PROC_p_p_p)&bt::_M4FAddTranslateDEF;
	as->M4DAddTranslate=(bt::tfSTDCALL_PROC_p_p_p)&bt::_M4DAddTranslateDEF;

	as->M4FAddScale=(bt::tfSTDCALL_PROC_p_p_p)&bt::_M4FAddScaleDEF;
	as->M4DAddScale=(bt::tfSTDCALL_PROC_p_p_p)&bt::_M4DAddScaleDEF;

	as->M4FAddRotate=(bt::tfSTDCALL_PROC_p_p_p)&bt::_M4FAddRotateDEF;
	as->M4DAddRotate=(bt::tfSTDCALL_PROC_p_p_p)&bt::_M4DAddRotateDEF;

	as->M4FToM4D=(bt::tfSTDCALL_PROC_p_p)&bt::_M4FTo4DDEF;
	as->M4DToM4F=(bt::tfSTDCALL_PROC_p_p)&bt::_M4DTo4FDEF;

	as->M4FTRS=(bt::tfSTDCALL_PROC_p_p_p_p)&bt::_M4FTRSDEF;
	as->M4DTRS=(bt::tfSTDCALL_PROC_p_p_p_p)&bt::_M4DTRSDEF;
}

void _APICALL initArrayVector(void*_conteiner)
{
	bt::sFunctionsArrayVectorCPU *as=(bt::sFunctionsArrayVectorCPU *)_conteiner;
	as->version=0;

	as->AConvert=(bt::tfSTDCALL_PROC_p_p_uint_uint_p_p_uint)&bt::_AConvertDEF;

	as->A2BMove=(bt::tfSTDCALL_PROC_p_p_uint_uint_uint)&bt::_A2BMoveDEF;
	as->A3BMove=(bt::tfSTDCALL_PROC_p_p_uint_uint_uint)&bt::_A3BMoveDEF;
	as->A4BMove=(bt::tfSTDCALL_PROC_p_p_uint_uint_uint)&bt::_A4BMoveDEF;
	as->A2FMove=(bt::tfSTDCALL_PROC_p_p_uint_uint_uint)&bt::_A2FMoveDEF;
	as->A3FMove=(bt::tfSTDCALL_PROC_p_p_uint_uint_uint)&bt::_A3FMoveDEF;
	as->A4FMove=(bt::tfSTDCALL_PROC_p_p_uint_uint_uint)&bt::_A4FMoveDEF;
	as->A2DMove=(bt::tfSTDCALL_PROC_p_p_uint_uint_uint)&bt::_A2DMoveDEF;
	as->A3DMove=(bt::tfSTDCALL_PROC_p_p_uint_uint_uint)&bt::_A3DMoveDEF;
	as->A4DMove=(bt::tfSTDCALL_PROC_p_p_uint_uint_uint)&bt::_A4DMoveDEF;

	as->A2ITo2F=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A2ITo2FDEF;
	as->A2ITo2D=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A2ITo2DDEF;
	as->A3ITo3F=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A3ITo3FDEF;
	as->A3ITo3D=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A3ITo3DDEF;
	as->A4ITo4W=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A4ITo4WDEF;
	as->A4ITo4F=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A4ITo4FDEF;
	as->A4ITo4D=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A4ITo4DDEF;
	as->A2FTo2I=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A2FTo2IDEF;
	as->A3FTo3I=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A3FTo3IDEF;
	as->A4FTo4I=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A4FTo4IDEF;
	as->A2FTo2D=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A2FTo2DDEF;
	as->A3FTo3D=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A3FTo3DDEF;
	as->A4FTo4D=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A4FTo4DDEF;
	as->A2DTo2F=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A2DTo2FDEF;
	as->A3DTo3F=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A3DTo3FDEF;
	as->A4DTo4F=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A4DTo4FDEF;

	as->A2FGrow3F=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A2FGrow3FDEF;
	as->A2FGrow4F=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A2FGrow4FDEF;
	as->A3FGrow4F=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A3FGrow4FDEF;
	as->A2DGrow3D=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A2DGrow3DDEF;
	as->A2DGrow4D=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A2DGrow4DDEF;
	as->A3DGrow4D=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A3DGrow4DDEF;

	as->A2IGrowTo3F=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A2IGrowTo3FDEF;
	as->A2IGrowTo4F=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A2IGrowTo4FDEF;
	as->A3IGrowTo4F=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A3IGrowTo4FDEF;
	as->A2IGrowTo3D=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A2IGrowTo3DDEF;
	as->A2IGrowTo4D=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A2IGrowTo4DDEF;
	as->A3IGrowTo4D=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A3IGrowTo4DDEF;

	as->A2FSum=(bt::tfSTDCALL_PROC_p_p_int_uint)&bt::_A2FSumDEF;
	as->A3FSum=(bt::tfSTDCALL_PROC_p_p_int_uint)&bt::_A3FSumDEF;
	as->A4FSum=(bt::tfSTDCALL_PROC_p_p_int_uint)&bt::_A4FSumDEF;
	as->A2DSum=(bt::tfSTDCALL_PROC_p_p_int_uint)&bt::_A2DSumDEF;
	as->A3DSum=(bt::tfSTDCALL_PROC_p_p_int_uint)&bt::_A3DSumDEF;
	as->A4DSum=(bt::tfSTDCALL_PROC_p_p_int_uint)&bt::_A4DSumDEF;

	as->A2FAddVector=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A2FAddVectorDEF;
	as->A3FAddVector=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A3FAddVectorDEF;
	as->A4FAddVector=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A4FAddVectorDEF;
	as->A2DAddVector=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A2DAddVectorDEF;
	as->A3DAddVector=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A3DAddVectorDEF;
	as->A4DAddVector=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A4DAddVectorDEF;

	as->A2IAdd=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A2IAddDEF;
	as->A3IAdd=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A3IAddDEF;
	as->A4IAdd=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A4IAddDEF;
	as->A2FAdd=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A2FAddDEF;
	as->A3FAdd=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A3FAddDEF;
	as->A4FAdd=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A4FAddDEF;
	as->A2DAdd=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A2DAddDEF;
	as->A3DAdd=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A3DAddDEF;
	as->A4DAdd=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A4DAddDEF;

	as->A2FSubVector=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A2FSubVectorDEF;
	as->A3FSubVector=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A3FSubVectorDEF;
	as->A4FSubVector=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A4FSubVectorDEF;
	as->A2DSubVector=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A2DSubVectorDEF;
	as->A3DSubVector=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A3DSubVectorDEF;
	as->A4DSubVector=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A4DSubVectorDEF;

	as->A2ISub=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A2ISubDEF;
	as->A3ISub=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A3ISubDEF;
	as->A4ISub=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A4ISubDEF;
	as->A2FSub=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A2FSubDEF;
	as->A3FSub=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A3FSubDEF;
	as->A4FSub=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A4FSubDEF;
	as->A2DSub=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A2DSubDEF;
	as->A3DSub=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A3DSubDEF;
	as->A4DSub=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A4DSubDEF;

	as->A2FScale=(bt::tfSTDCALL_PROC_p_p_float_int_int_uint)&bt::_A2FScaleDEF;
	as->A3FScale=(bt::tfSTDCALL_PROC_p_p_float_int_int_uint)&bt::_A3FScaleDEF;
	as->A4FScale=(bt::tfSTDCALL_PROC_p_p_float_int_int_uint)&bt::_A4FScaleDEF;
	as->A2DScale=(bt::tfSTDCALL_PROC_p_p_double_int_int_uint)&bt::_A2DScaleDEF;
	as->A3DScale=(bt::tfSTDCALL_PROC_p_p_double_int_int_uint)&bt::_A3DScaleDEF;
	as->A4DScale=(bt::tfSTDCALL_PROC_p_p_double_int_int_uint)&bt::_A4DScaleDEF;

	as->A2FMulVector=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A2FMulVectorDEF;
	as->A3FMulVector=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A3FMulVectorDEF;
	as->A4FMulVector=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A4FMulVectorDEF;
	as->A2DMulVector=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A2DMulVectorDEF;
	as->A3DMulVector=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A3DMulVectorDEF;
	as->A4DMulVector=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A4DMulVectorDEF;

	as->A2FMul=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A2FMulDEF;
	as->A3FMul=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A3FMulDEF;
	as->A4FMul=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A4FMulDEF;
	as->A2DMul=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A2DMulDEF;
	as->A3DMul=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A3DMulDEF;
	as->A4DMul=(bt::tfSTDCALL_PROC_p_p_p_int_int_int_uint)&bt::_A4DMulDEF;

	as->A2FNormal=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A2FNormalDEF;
	as->A3FNormal=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A3FNormalDEF;
	as->A4FNormal=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A4FNormalDEF;
	as->A2DNormal=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A2DNormalDEF;
	as->A3DNormal=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A3DNormalDEF;
	as->A4DNormal=(bt::tfSTDCALL_PROC_p_p_int_int_uint)&bt::_A4DNormalDEF;

	as->A2FLerp=(bt::tfSTDCALL_PROC_p_p_p_float_int_int_int_uint)&bt::_A2FLerpDEF;
	as->A3FLerp=(bt::tfSTDCALL_PROC_p_p_p_float_int_int_int_uint)&bt::_A3FLerpDEF;
	as->A4FLerp=(bt::tfSTDCALL_PROC_p_p_p_float_int_int_int_uint)&bt::_A4FLerpDEF;
	as->A2DLerp=(bt::tfSTDCALL_PROC_p_p_p_double_int_int_int_uint)&bt::_A2DLerpDEF;
	as->A3DLerp=(bt::tfSTDCALL_PROC_p_p_p_double_int_int_int_uint)&bt::_A3DLerpDEF;
	as->A4DLerp=(bt::tfSTDCALL_PROC_p_p_p_double_int_int_int_uint)&bt::_A4DLerpDEF;

	as->A2FMatrixTransform=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A2FMatrixTransformDEF;
	as->A3FMatrixTransform=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A3FMatrixTransformDEF;
	as->A4FMatrixTransform=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A4FMatrixTransformDEF;
	as->A2DMatrixTransform=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A2DMatrixTransformDEF;
	as->A3DMatrixTransform=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A3DMatrixTransformDEF;
	as->A4DMatrixTransform=(bt::tfSTDCALL_PROC_p_p_p_int_int_uint)&bt::_A4DMatrixTransformDEF;

	as->A2FProj=(bt::tfSTDCALL_PROC_p_p_p_p_p_int_int_int_uint)&bt::_A2FProjDEF;
	as->A3FProj=(bt::tfSTDCALL_PROC_p_p_p_p_p_int_int_int_uint)&bt::_A3FProjDEF;
	as->A4FProj=(bt::tfSTDCALL_PROC_p_p_p_p_p_int_int_int_uint)&bt::_A4FProjDEF;
	as->A2DProj=(bt::tfSTDCALL_PROC_p_p_p_p_p_int_int_int_uint)&bt::_A2DProjDEF;
	as->A3DProj=(bt::tfSTDCALL_PROC_p_p_p_p_p_int_int_int_uint)&bt::_A3DProjDEF;
	as->A4DProj=(bt::tfSTDCALL_PROC_p_p_p_p_p_int_int_int_uint)&bt::_A4DProjDEF;

	as->AFZoomSplineCR=(bt::tfSTDCALL_PROC_p_p_int_int_double_float_uint_uint_uint)&bt::_AFZoomSplineCRDEF;
	as->A2FZoomSplineCR=(bt::tfSTDCALL_PROC_p_p_int_int_double_float_uint_uint_uint)&bt::_A2FZoomSplineCRDEF;
	as->A3FZoomSplineCR=(bt::tfSTDCALL_PROC_p_p_int_int_double_float_uint_uint_uint)&bt::_A3FZoomSplineCRDEF;
	as->A4FZoomSplineCR=(bt::tfSTDCALL_PROC_p_p_int_int_double_float_uint_uint_uint)&bt::_A4FZoomSplineCRDEF;
	as->ADZoomSplineCR=(bt::tfSTDCALL_PROC_p_p_int_int_double_float_uint_uint_uint)&bt::_ADZoomSplineCRDEF;
	as->A2DZoomSplineCR=(bt::tfSTDCALL_PROC_p_p_int_int_double_float_uint_uint_uint)&bt::_A2DZoomSplineCRDEF;
	as->A3DZoomSplineCR=(bt::tfSTDCALL_PROC_p_p_int_int_double_float_uint_uint_uint)&bt::_A3DZoomSplineCRDEF;
	as->A4DZoomSplineCR=(bt::tfSTDCALL_PROC_p_p_int_int_double_float_uint_uint_uint)&bt::_A4DZoomSplineCRDEF;
}

void _APICALL initExtension(void * _conteiner)
{
	bt::sFunctionsExtensionCPU *as=(bt::sFunctionsExtensionCPU *)_conteiner;
	as->version=0;

	as->CreateMem=(bt::tfSTDCALL_p_FUNC_uint_uint)&bt::_CreateMemDEF;
	as->DeleteMem=(bt::tfSTDCALL_bool_FUNC_p_uint)&bt::_DeleteMemDEF;
	as->ResizeMem=(bt::tfSTDCALL_p_FUNC_p_uint_uint)&bt::_ResizeMemDEF;
	as->CleanMem=(bt::tfSTDCALL_PROC_p_uint)&bt::_CleanMemDEF;
	as->MoveMem=(bt::tfSTDCALL_PROC_p_p_uint)&bt::_MoveMemDEF;
	as->MoveBack=(bt::tfSTDCALL_PROC_p_p_uint)&bt::_MoveBackDEF;
	as->SwapMem=(bt::tfSTDCALL_PROC_p_p_uint)&bt::_SwapMemDEF;
	as->StocBMem=(bt::tfSTDCALL_PROC_p_uint_uint)&bt::_StocBMemDEF;
	as->StocSMem=(bt::tfSTDCALL_PROC_p_uint_uint)&bt::_StocSMemDEF;
	as->StocIMem=(bt::tfSTDCALL_PROC_p_uint_uint)&bt::_StocIMemDEF;
	as->CmpMem=(bt::tfSTDCALL_int_FUNC_p_p_uint)&bt::_CmpMemDEF;
	as->SubMem=(bt::tfSTDCALL_int_FUNC_p_p_uint)&bt::_SubMemDEF;
	as->FindCMem=(bt::tfSTDCALL_int_FUNC_p_uint_int)&bt::_FindCMemDEF;
	as->FindSMem=(bt::tfSTDCALL_int_FUNC_p_uint_int)&bt::_FindSMemDEF;
	as->FindIMem=(bt::tfSTDCALL_int_FUNC_p_uint_int)&bt::_FindIMemDEF;
	as->SetBit=(bt::tfSTDCALL_PROC_int_int_p)&bt::_setbit;
	as->GetBit=(bt::tfSTDCALL_int_FUNC_int_p)&bt::_getbit;
	as->GetFastSTDMulI=(bt::tfSTDCALL_p_FUNC_int)&bt::_GetFastSTDMulI;
	as->GetFastFCMulI=(bt::tfSTDCALL_p_FUNC_int)&bt::_GetFastFCMulI;

	as->NoiseStart=(bt::tfSTDCALL_PROC_int_int)&bt::_NoiseStartDEF;
	as->NoiseGet=(bt::tfSTDCALL_int_FUNC)&bt::_NoiseGetDEF;
	as->NoiseSave=(bt::tfSTDCALL_PROC_p)&bt::_NoiseSaveDEF;
	as->NoiseLoad=(bt::tfSTDCALL_PROC_p)&bt::_NoiseLoadDEF;

	as->ILogSize=(bt::tfSTDCALL_int_FUNC_int)&bt::_ILogSizeDEF;
	as->STRToI=(bt::tfSTDCALL_int_FUNC_p)&bt::_STRToIDEF;
	as->STRToF=(bt::tfSTDCALL_float_FUNC_p)&bt::_STRToFDEF;
	as->STRToD=(bt::tfSTDCALL_double_FUNC_p)&bt::_STRToDDEF;
	as->IToSTR=(bt::tfSTDCALL_PROC_p_uint_int)&bt::_IToSTRDEF;

	//as->STRTok=(bt::tfSTDCALL_p_FUNC_p_p)&bt::_STRTokDEF;
	as->STRLeftFind=(bt::tfSTDCALL_p_FUNC_p_p)&bt::_STRLeftFindDEF;
	as->STRRightFind=(bt::tfSTDCALL_p_FUNC_p_p)&bt::_STRRightFindDEF;

	as->KeyToUniChar=(bt::tfSTDCALL_int_FUNC_int_int)&bt::_KeyToUniCharDEF;

	as->FMotionPoint=(bt::tfSTDCALL_bool_FUNC_p_p_float_double)&bt::_FMotionPointDEF;
	as->DMotionPoint=(bt::tfSTDCALL_bool_FUNC_p_p_double_double)&bt::_DMotionPointDEF;
	as->V2FMotionPoint=(bt::tfSTDCALL_bool_FUNC_p_p_p_double)&bt::_V2FMotionPointDEF;
	as->V2DMotionPoint=(bt::tfSTDCALL_bool_FUNC_p_p_p_double)&bt::_V2DMotionPointDEF;
	as->V3FMotionPoint=(bt::tfSTDCALL_bool_FUNC_p_p_p_double)&bt::_V3FMotionPointDEF;
	as->V3DMotionPoint=(bt::tfSTDCALL_bool_FUNC_p_p_p_double)&bt::_V3DMotionPointDEF;
	as->V4FMotionPoint=(bt::tfSTDCALL_bool_FUNC_p_p_p_double)&bt::_V4FMotionPointDEF;
	as->V4DMotionPoint=(bt::tfSTDCALL_bool_FUNC_p_p_p_double)&bt::_V4DMotionPointDEF;

	as->FMotionRad=(bt::tfSTDCALL_bool_FUNC_p_p_float_double)&bt::_FMotionRadDEF;
	as->DMotionRad=(bt::tfSTDCALL_bool_FUNC_p_p_double_double)&bt::_DMotionRadDEF;
	as->V2FMotionRad=(bt::tfSTDCALL_bool_FUNC_p_p_p_double)&bt::_V2FMotionRadDEF;
	as->V2DMotionRad=(bt::tfSTDCALL_bool_FUNC_p_p_p_double)&bt::_V2DMotionRadDEF;
	as->V3FMotionRad=(bt::tfSTDCALL_bool_FUNC_p_p_p_double)&bt::_V3FMotionRadDEF;
	as->V3DMotionRad=(bt::tfSTDCALL_bool_FUNC_p_p_p_double)&bt::_V3DMotionRadDEF;
	as->V4FMotionRad=(bt::tfSTDCALL_bool_FUNC_p_p_p_double)&bt::_V4FMotionRadDEF;
	as->V4DMotionRad=(bt::tfSTDCALL_bool_FUNC_p_p_p_double)&bt::_V4DMotionRadDEF;

	as->V2FPCRCC=(bt::tfSTDCALL_PROC_p_p)&bt::_V2FPCRCCDEF;
	as->V3FPCRCC=(bt::tfSTDCALL_PROC_p_p)&bt::_V3FPCRCCDEF;
	as->V4FPCRCC=(bt::tfSTDCALL_PROC_p_p)&bt::_V4FPCRCCDEF;
	as->V2DPCRCC=(bt::tfSTDCALL_PROC_p_p)&bt::_V2DPCRCCDEF;
	as->V3DPCRCC=(bt::tfSTDCALL_PROC_p_p)&bt::_V3DPCRCCDEF;
	as->V4DPCRCC=(bt::tfSTDCALL_PROC_p_p)&bt::_V4DPCRCCDEF;

	as->V2FSplineCR=(bt::tfSTDCALL_PROC_p_p_float_float)&bt::_V2FSplineCRDEF;
	as->V3FSplineCR=(bt::tfSTDCALL_PROC_p_p_float_float)&bt::_V3FSplineCRDEF;
	as->V4FSplineCR=(bt::tfSTDCALL_PROC_p_p_float_float)&bt::_V4FSplineCRDEF;
	as->V2DSplineCR=(bt::tfSTDCALL_PROC_p_p_double_double)&bt::_V2DSplineCRDEF;
	as->V3DSplineCR=(bt::tfSTDCALL_PROC_p_p_double_double)&bt::_V3DSplineCRDEF;
	as->V4DSplineCR=(bt::tfSTDCALL_PROC_p_p_double_double)&bt::_V4DSplineCRDEF;

	as->BLHToV3F=(bt::tfSTDCALL_PROC_p_p)&bt::_BLHtoV3FDEF;
	as->BLHToV3D=(bt::tfSTDCALL_PROC_p_p)&bt::_BLHtoV3DDEF;
	as->BLHToV3FFAST=(bt::tfSTDCALL_PROC_p_p)&bt::_BLHtoV3FFASTDEF;
	as->BLHToV3DFAST=(bt::tfSTDCALL_PROC_p_p)&bt::_BLHtoV3DFASTDEF;
	as->BLToV3F=(bt::tfSTDCALL_PROC_float_float_p)&bt::_BLtoV3FDEF;
	as->BLToV3D=(bt::tfSTDCALL_PROC_double_double_p)&bt::_BLtoV3DDEF;
	as->BLToV3FFAST=(bt::tfSTDCALL_PROC_float_float_p)&bt::_BLtoV3FFASTDEF;
	as->BLToV3DFAST=(bt::tfSTDCALL_PROC_double_double_p)&bt::_BLtoV3DFASTDEF;
	as->V3FToBLH=(bt::tfSTDCALL_PROC_p_p)&bt::_V3FtoBLHDEF;
	as->V3DToBLH=(bt::tfSTDCALL_PROC_p_p)&bt::_V3DtoBLHDEF;
	as->V3FToBL=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3FtoBLDEF;
	as->V3DToBL=(bt::tfSTDCALL_PROC_p_p_p)&bt::_V3DtoBLDEF;

	as->FastCharDiv=FDiv;
	as->FastCharDiv=(char*)(((_voidint)as->FastCharDiv+0xFFFF) & (_voidintmax<<16));
	for (int j=0;j<65536;j++)
		as->FastCharDiv[j]=((j&0xFF)*((j>>8)+1))>>8;
}

void _APICALL initArray(void*_conteiner)
{
	bt::sFunctionsArrayCPU *as=(bt::sFunctionsArrayCPU *)_conteiner;
	as->version=0;

	as->SSet=(bt::tfSTDCALL_PROC_p_p)&bt::_SSetDEF;
	as->SAdd=(bt::tfSTDCALL_PROC_p_p)&bt::_SAddDEF;
	as->SCompare=(bt::tfSTDCALL_int_FUNC_p_p)&bt::_SCompareDEF;

	as->LSSet=(bt::tfSTDCALL_PROC_p_p)&bt::_LSSetDEF;
	as->LSAdd=(bt::tfSTDCALL_PROC_p_p)&bt::_LSAddDEF;
	as->LSInsert=(bt::tfSTDCALL_PROC_p_p_uint)&bt::_LSInsertDEF;
	as->LSRemove=(bt::tfSTDCALL_PROC_p_uint_uint)&bt::_LSRemoveDEF;
	as->LSCompare=(bt::tfSTDCALL_int_FUNC_p_p)&bt::_LSCompareDEF;

	as->DPSetCount=(bt::tfSTDCALL_PROC_p_uint)&bt::_DPSetCountDEF;
	as->DPAddLast=(bt::tfSTDCALL_p_FUNC_p_p)&bt::_DPAddLastDEF;
	as->DPInsert=(bt::tfSTDCALL_p_FUNC_p_p_uint)&bt::_DPInsertDEF;
	as->DPRemove=(bt::tfSTDCALL_PROC_p_uint)&bt::_DPRemoveDEF;
	as->DPRemoveVal=(bt::tfSTDCALL_int_FUNC_p_p)&bt::_DPRemoveValDEF;
	as->DPRemoveLast=(bt::tfSTDCALL_PROC_p)&bt::_DPRemoveLastDEF;
	as->DPFree=(bt::tfSTDCALL_PROC_p)&bt::_APFreeDEF;

	as->DSAddLast=(bt::tfSTDCALL_p_FUNC_p_p)&bt::_DSAddLastDEF;
	as->DSFree=(bt::tfSTDCALL_PROC_p)&bt::_DSFreeDEF;

	as->APLast=(bt::tfSTDCALL_p_FUNC_p)&bt::_APLastDEF;
	as->APClone=(bt::tfSTDCALL_p_FUNC_p)&bt::_APCloneDEF;
	as->APAdd=(bt::tfSTDCALL_p_FUNC_p_p)&bt::_APAddDEF;
	as->APFind=(bt::tfSTDCALL_int_FUNC_p_p)&bt::_APFindDEF;
	as->APRemove=(bt::tfSTDCALL_int_FUNC_p_p)&bt::_APRemoveDEF;
	as->APEnd=(bt::tfSTDCALL_p_FUNC_p)&bt::_APEndDEF;
	as->APFree=(bt::tfSTDCALL_PROC_p)&bt::_APFreeDEF;

	as->MPAdd=(bt::tfSTDCALL_p_FUNC_p_p_p)&bt::_MPAddDEF;
	as->MPFind=(bt::tfSTDCALL_p_FUNC_p_p)&bt::_MPFindDEF;
	as->MPFindByVal = (bt::tfSTDCALL_p_FUNC_p_p_p)&bt::_MPFindByValDEF;
	as->MPRemove=(bt::tfSTDCALL_p_FUNC_p_p)&bt::_MPRemoveDEF;
	as->MPEnd=(bt::tfSTDCALL_p_FUNC_p)&bt::_MPEndDEF;
	as->MPFree=(bt::tfSTDCALL_PROC_p)&bt::_MPFreeDEF;

	as->MSPAdd=(bt::tfSTDCALL_p_FUNC_p_p_p)&bt::_MSPAddDEF;
	as->MSSPAdd = (bt::tfSTDCALL_p_FUNC_p_p_p)&bt::_MSSPAddDEF;
	as->MSPFind=(bt::tfSTDCALL_p_FUNC_p_p)&bt::_MSPFindDEF;
	as->MSSPFind=(bt::tfSTDCALL_p_FUNC_p_p)&bt::_MSSPFindDEF;
	as->MSPRemove=(bt::tfSTDCALL_p_FUNC_p_p)&bt::_MSPRemoveDEF;
	as->MSSPRemove=(bt::tfSTDCALL_int_FUNC_p_p)&bt::_MSSPRemoveDEF;
	as->MSSPFree=(bt::tfSTDCALL_PROC_p)&bt::_MSSPFreeDEF;

	as->MCPAdd=(bt::tfSTDCALL_p_FUNC_p_p_p_uint)&bt::_MCPAddDEF;
	as->MCPFind=(bt::tfSTDCALL_p_FUNC_p_p)&bt::_MCPFindDEF;

	as->MCSPAdd=(bt::tfSTDCALL_p_FUNC_p_p_p_uint)&bt::_MCSPAddDEF;
	as->MCSPFind=(bt::tfSTDCALL_p_FUNC_p_p)&bt::_MCSPFindDEF;

	as->MPArray=(bt::tfSTDCALL_p_FUNC_p)&bt::_MPArrayDEF;
	as->MPCount=(bt::tfSTDCALL_uint_FUNC_p)&bt::_MPCountDEF;

	as->ANTInit=(bt::tfSTDCALL_PROC_p_uint_uint)&bt::_ANTInitDEF;
	as->ANTFree=(bt::tfSTDCALL_PROC_p)&bt::_ANTFreeDEF;
	as->ANTResize=(bt::tfSTDCALL_PROC_p_uint)&bt::_ANTResizeDEF;
	as->ANTReserv=(bt::tfSTDCALL_PROC_p_uint)&bt::_ANTReservDEF;
	as->ANTAssign=(bt::tfSTDCALL_PROC_p_p)&bt::_ANTAssignDEF;
	as->ANTDelLast=(bt::tfSTDCALL_PROC_p)&bt::_ANTDelLastDEF;
	as->ANTPosition=(bt::tfSTDCALL_p_FUNC_p_uint)&bt::_ANTPositionDEF;
	as->ANTPositionL=(bt::tfSTDCALL_p_FUNC_p)&bt::_ANTPositionLDEF;
}

void _APICALL initObject(void*_conteiner)
{
	bt::sFunctionsObjectCPU *as=(bt::sFunctionsObjectCPU *)_conteiner;
	as->version=0;

#if defined(SCRIPT_BT) || defined(BT_SCRIPT)
	as->ScriptCreate=(bt::tfSTDCALL_p_FUNC)&bt::scriptCreate;
	as->ScriptInit=(bt::tfSTDCALL_PROC_p_p_p)&bt::scriptInit;
	as->ScriptParser=(bt::tfSTDCALL_PROC_p_p)&bt::scriptParser;
	as->ScriptExe=(bt::tfSTDCALL_PROC_p)&bt::scriptExe;
	as->ScriptClear=(bt::tfSTDCALL_PROC_p)&bt::scriptClear;
#endif
}

void _APICALL initRender(void*_conteiner)
{
	bt::sFunctionsRenderCPU *as=(bt::sFunctionsRenderCPU *)_conteiner;
	as->version=0;

	as->V3BHalfTexel=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V3BHalfTexelDEF;
	as->V4BHalfTexel=(bt::tfSTDCALL_PROC_p_p_int)&bt::_V4BHalfTexelDEF;
	as->V3BTexel=(bt::tfSTDCALL_PROC_p_p_int_float_float)&bt::_V3BTexelDEF;
	as->V4BTexel=(bt::tfSTDCALL_PROC_p_p_int_float_float)&bt::_V4BTexelDEF;

	as->S4AFdraw=(bt::tfSTDCALL_PROC_p)&bt::_S4AFdrawDEF;
	as->S4AFDLdraw=(bt::tfSTDCALL_PROC_p)&bt::_S4AFDLdrawDEF;
	as->S4AFSdraw=(bt::tfSTDCALL_PROC_p)&bt::_S4AFSdrawDEF;
	as->S4AFDLSdraw=(bt::tfSTDCALL_PROC_p)&bt::_S4AFDLSdrawDEF;

	as->P4AFDraw=(bt::tfSTDCALL_PROC_p_p_float)&bt::_P4AFdrawDEF;
	as->P4AFDrawAA=(bt::tfSTDCALL_PROC_p_p_float)&bt::_P4AFdrawAADEF;
	as->P4AFADrawAA=(bt::tfSTDCALL_PROC_p_p_float)&bt::_P4AFAdrawAADEF;

	as->L4AFDraw=(bt::tfSTDCALL_PROC_p_p_float)&bt::_L4AFdrawDEF;

	as->T4AFDraw=(bt::tfSTDCALL_PROC_p_p)&bt::_T4AFdrawDEF;
	as->T4AFSDraw=(bt::tfSTDCALL_PROC_p_p)&bt::_T4AFSdrawDEF;
}

}

OPTIMIZE_OFF;
