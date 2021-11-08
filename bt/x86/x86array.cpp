/*
 * x86array.cpp
 *
 *  Created on: 25.10.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifdef CPU_BT

#include "x86array.h"

#ifdef CPU_X86_32

#include <math.h>
#include "x86array_add.h"
#include "x86array_sub.h"
#include "x86array_scale.h"
#include "x86array_mul.h"
#include "x86array_normal.h"
#include "x86array_transform.h"
#include "x86array_proj.h"
#include "macrosasm.h"

WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

	void _NAKED _APICALL _A2FNormalFPU(void *,void *,unsigned int ,unsigned int ,unsigned int )
	{
		ARRAYP2DNORMALFPU_STD;
		RET_5;
	}

	void _NAKED _APICALL _A3FNormalFPU(void *,void *,unsigned int ,unsigned int ,unsigned int )
	{
		ARRAYP3DNORMALFPU_STD;
		RET_5;
	}

	void _NAKED _APICALL _A4FNormalFPU(void *,void *,unsigned int ,unsigned int ,unsigned int )
	{
		ARRAYP4DNORMALFPU_STD;
		RET_5;
	}

	void _NAKED _APICALL _A2DNormalFPU(void *,void *,unsigned int ,unsigned int ,unsigned int )
	{
		ARRAYP2DDNORMALFPU_STD;
		RET_5;
	}

	void _NAKED _APICALL _A3DNormalFPU(void *,void *,unsigned int ,unsigned int ,unsigned int )
	{
		ARRAYP3DDNORMALFPU_STD;
		RET_5;
	}

	void _NAKED _APICALL _A4DNormalFPU(void *,void *,unsigned int ,unsigned int ,unsigned int )
	{
		ARRAYP4DDNORMALFPU_STD;
		RET_5;
	}

// ************** array vector Proj FPU function *******************

	void _NAKED _APICALL _A3FProjFPU(float *,void *,float *,float *,float *,unsigned int ,unsigned int ,unsigned int ,unsigned int )
	{

	}

// ************** array vector AddVector SSE function *******************

void _NAKED _APICALL _A2FAddVectorSSE(void *,float *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP2DADDVECTORSSE_STD;
	RET_6;
}

void _NAKED _APICALL _A3FAddVectorSSE(void *,float *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP3DADDVECTORSSE_STD;
	RET_6;
}

void _NAKED _APICALL _A4FAddVectorSSE(void *,float *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP4DADDVECTORSSE_STD;
	RET_6;
}

// ************** array vector Add SSE function *******************

// ************** array vector SubVector SSE function *******************

void _NAKED _APICALL _A2FSubVectorSSE(void *,float *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP2DSUBVECTORSSE_STD;
	RET_6;
}

void _NAKED _APICALL _A3FSubVectorSSE(void *,float *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP3DSUBVECTORSSE_STD;
	RET_6;
}

void _NAKED _APICALL _A4FSubVectorSSE(void *,float *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP4DSUBVECTORSSE_STD;
	RET_6;
}

// ************** array vector MulVector SSE function *******************

void _NAKED _APICALL _A2FMulVectorSSE(void *,float *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP2DMULVECTORSSE_STD;
	RET_6;
}

void _NAKED _APICALL _A3FMulVectorSSE(void *,float *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP3DMULVECTORSSE_STD;
	RET_6;
}

void _NAKED _APICALL _A4FMulVectorSSE(void *,float *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP4DMULVECTORSSE_STD;
	RET_6;
}

// ************** array vector Normal SSE function *******************

void _NAKED _APICALL _A2FNormalSSE(void *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP2DNORMALSSE_STD;
	RET_5;
}

void _NAKED _APICALL _A3FNormalSSE(void *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP3DNORMALSSE_STD;
	RET_5;
}

void _NAKED _APICALL _A4FNormalSSE(void *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP4DNORMALSSE_STD;
	RET_5;
}

// ************** array vector MatrixTransform SSE function *******************

void _NAKED _APICALL _A2FMatrixTransformSSE(void *,void *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP2DTRANSFORMSSE_STD;
	RET_6;
}

void _NAKED _APICALL _A3FMatrixTransformSSE(void *,void *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP3DTRANSFORMSSE_STD;
	RET_6;
}

void _NAKED _APICALL _A4FMatrixTransformSSE(void *,void *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP4DTRANSFORMSSE_STD;
	RET_6;
}

// ************** array vector AddVector SSE2 function *******************

void _NAKED _APICALL _A2DAddVectorSSE2(void *,double *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP2DDADDVECTORSSE2_STD;
	RET_6;
}

void _NAKED _APICALL _A3DAddVectorSSE2(void *,double *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP3DDADDVECTORSSE2_STD;
	RET_6;
}

void _NAKED _APICALL _A4DAddVectorSSE2(void *,double *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP4DDADDVECTORSSE2_STD;
	RET_6;
}

// ************** array vector SubVector SSE2 function *******************

void _NAKED _APICALL _A2DSubVectorSSE2(void *,double *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP2DDSUBVECTORSSE2_STD;
	RET_6;
}

void _NAKED _APICALL _A3DSubVectorSSE2(void *,double *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP3DDSUBVECTORSSE2_STD;
	RET_6;
}

void _NAKED _APICALL _A4DSubVectorSSE2(void *,double *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP4DDSUBVECTORSSE2_STD;
	RET_6;
}

// ************** array vector MulVector SSE2 function *******************

void _NAKED _APICALL _A2DMulVectorSSE2(void *,double *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP2DDMULVECTORSSE2_STD;
	RET_6;
}

void _NAKED _APICALL _A3DMulVectorSSE2(void *,double *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP3DDMULVECTORSSE2_STD;
	RET_6;
}

void _NAKED _APICALL _A4DMulVectorSSE2(void *,double *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP4DDMULVECTORSSE2_STD;
	RET_6;
}

// ************** array vector AddVector SSE3 function *******************

void _APICALL _A4IAddVectorSSE3(void *,int *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP4IADDVECTORSSE3_STD;
	RET_6;
}

void _NAKED _APICALL _A2FAddVectorSSE3(void *,float *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP2DADDVECTORSSE3_STD;
	RET_6;
}

void _NAKED _APICALL _A4FAddVectorSSE3(void *,float *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP4DADDVECTORSSE3_STD;
	RET_6;
}

void _NAKED _APICALL _A2DAddVectorSSE3(void *,double *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP2DDADDVECTORSSE3_STD;
	RET_6;
}

void _NAKED _APICALL _A4DAddVectorSSE3(void *,double *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP4DDADDVECTORSSE3_STD;
	RET_6;
}

// ************** array vector Add SSE3 function *******************

void _NAKED _APICALL _A4IAddSSE3(void *,void *,void *,unsigned int ,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP4IADDSSE3_STD;
	RET_7;
}

void _NAKED _APICALL _A4FAddSSE3(void *,void *,void *,unsigned int ,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP4DADDSSE_STD;
	RET_7;
}

// ************** array vector SubVector SSE3 function *******************

void _NAKED _APICALL _A2FSubVectorSSE3(void *,float *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP2DSUBVECTORSSE3_STD;
	RET_6;
}

void _NAKED _APICALL _A4FSubVectorSSE3(void *,float *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP4DSUBVECTORSSE3_STD;
	RET_6;
}

void _NAKED _APICALL _A2DSubVectorSSE3(void *,double *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP2DDSUBVECTORSSE3_STD;
	RET_6;
}

void _NAKED _APICALL _A4DSubVectorSSE3(void *,double *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP4DDSUBVECTORSSE3_STD;
	RET_6;
}

// ************** array vector Sub SSE3 function *******************

void _NAKED _APICALL _A4ISubSSE3(void *,void *,void *,unsigned int ,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP4ISUBSSE3_STD;
	RET_7;
}

void _NAKED _APICALL _A4FSubSSE3(void *,void *,void *,unsigned int ,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP4DSUBSSE3_STD;
	RET_7;
}

// ************** array vector MulVector SSE3 function *******************

void _NAKED _APICALL _A2FMulVectorSSE3(void *,float *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP2DMULVECTORSSE3_STD;
	RET_6;
}

void _NAKED _APICALL _A4FMulVectorSSE3(void *,float *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP4DMULVECTORSSE3_STD;
	RET_6;
}

void _NAKED _APICALL _A2DMulVectorSSE3(void *,double *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP2DDMULVECTORSSE3_STD;
	RET_6;
}

void _NAKED _APICALL _A4DMulVectorSSE3(void *,double *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP4DDMULVECTORSSE3_STD;
	RET_6;
}

// ************** array vector Normal SSE3 function *******************

void _NAKED _APICALL _A2FNormalSSE3(void *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP2DNORMALSSE3_STD;
	RET_5;
}

// ************** array vector MatrixTransform SSE3 function *******************

void _NAKED _APICALL _A3FMatrixTransformSSE3(void *,void *,void *,int ,int ,unsigned int )
{
	ARRAYP3DTRANSFORMSSE3_STD;
	RET_6;
}

void _NAKED _APICALL _A4FMatrixTransformSSE3(void *,void *,void *,int ,int ,unsigned int )
{
	ARRAYP4DTRANSFORMSSE3_STD;
	RET_6;
}

// ************** array vector Proj SSE3 function *******************

void _NAKED _APICALL _A2FProjSSE3(float *,void *,float *,float *,float *,int ,int ,int ,unsigned int )
{
	ARRAYP2DPROJECTSSE3_STD;
	RET_9;
}

void _NAKED _APICALL _A3FProjSSE3(float *,void *,float *,float *,float *,int ,int ,int ,unsigned int )
{
	ARRAYP3DPROJECTSSE3_STD;
	RET_9;
}

void _NAKED _APICALL _A4FProjSSE3(float *,void *,float *,float *,float *,int ,int ,int ,unsigned int )
{
	ARRAYP4DPROJECTSSE3_STD;
	RET_9;
}

// ************** array vector Normal SSE4 function *******************

void _NAKED _APICALL _A2FNormalSSE4(void *,void *,unsigned int ,unsigned int ,unsigned int )
{
	ARRAYP2DNORMALSSE4_STD;
	RET_5;
}

// ************** array vector MatrixTransform AVX function *******************

void _NAKED _APICALL _A3DMatrixTransformAVX(void *,void *,void *,int ,int ,unsigned int )
{
	ARRAYP3DDTRANSFORMAVX_STD;
	RET_6;
}

void _NAKED _APICALL _A4DMatrixTransformAVX(void *,void *,void *,int ,int ,unsigned int )
{
	ARRAYP4DDTRANSFORMAVX_STD;
	RET_6;
}

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif
#endif