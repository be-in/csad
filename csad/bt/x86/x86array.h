/*
 * x86array.h
 *
 *  Created on: 25.10.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifdef CPU_BT
#ifndef X86ARRAY_H_
#define X86ARRAY_H_

#include <bt.h>

namespace bt {

	void _APICALL _A2FNormalFPU(void *_a,void *_b,unsigned int _stepa,unsigned int _stepb,unsigned int _count);
	void _APICALL _A3FNormalFPU(void *_a,void *_b,unsigned int _stepa,unsigned int _stepb,unsigned int _count);
	void _APICALL _A4FNormalFPU(void *_a,void *_b,unsigned int _stepa,unsigned int _stepb,unsigned int _count);
	void _APICALL _A2DNormalFPU(void *_a,void *_b,unsigned int _stepa,unsigned int _stepb,unsigned int _count);
	void _APICALL _A3DNormalFPU(void *_a,void *_b,unsigned int _stepa,unsigned int _stepb,unsigned int _count);
	void _APICALL _A4DNormalFPU(void *_a,void *_b,unsigned int _stepa,unsigned int _stepb,unsigned int _count);

	void _APICALL _A3FProjFPU(float *_a,void *_b,float *_c,float *_d,float *_e,unsigned int _stepa,unsigned int _stepe,unsigned int _flagoff,unsigned int _count);

	void _APICALL _A2FAddVectorSSE(void *_a,float *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A3FAddVectorSSE(void *_a,float *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A4FAddVectorSSE(void *_a,float *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);

	void _APICALL _A2FSubVectorSSE(void *_a,float *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A3FSubVectorSSE(void *_a,float *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A4FSubVectorSSE(void *_a,float *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);

	void _APICALL _A2FMulVectorSSE(void *_a,float *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A3FMulVectorSSE(void *_a,float *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A4FMulVectorSSE(void *_a,float *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);

	void _APICALL _A2FNormalSSE(void *_a,void *_b,unsigned int _stepa,unsigned int _stepb,unsigned int _count);
	void _APICALL _A3FNormalSSE(void *_a,void *_b,unsigned int _stepa,unsigned int _stepb,unsigned int _count);
	void _APICALL _A4FNormalSSE(void *_a,void *_b,unsigned int _stepa,unsigned int _stepb,unsigned int _count);

	void _APICALL _A2FMatrixTransformSSE(void *_a,void *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A3FMatrixTransformSSE(void *_a,void *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A4FMatrixTransformSSE(void *_a,void *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);

	void _APICALL _A2DAddVectorSSE2(void *_a,double *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A3DAddVectorSSE2(void *_a,double *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A4DAddVectorSSE2(void *_a,double *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);

	void _APICALL _A2DSubVectorSSE2(void *_a,double *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A3DSubVectorSSE2(void *_a,double *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A4DSubVectorSSE2(void *_a,double *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);

	void _APICALL _A2DMulVectorSSE2(void *_a,double *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A3DMulVectorSSE2(void *_a,double *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A4DMulVectorSSE2(void *_a,double *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);

	void _APICALL _A4IAddVectorSSE3(void *_a,int *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A2FAddVectorSSE3(void *_a,float *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A4FAddVectorSSE3(void *_a,float *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A2DAddVectorSSE3(void *_a,double *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A4DAddVectorSSE3(void *_a,double *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);

	void _APICALL _A4IAddSSE3(void *_a,void *_b,void *_c,unsigned int _stepa,unsigned int _stepb,unsigned int _stepc,unsigned int _count);
	void _APICALL _A4FAddSSE3(void *_a,void *_b,void *_c,unsigned int _stepa,unsigned int _stepb,unsigned int _stepc,unsigned int _count);

	void _APICALL _A2FSubVectorSSE3(void *_a,float *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A4FSubVectorSSE3(void *_a,float *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A2DSubVectorSSE3(void *_a,double *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A4DSubVectorSSE3(void *_a,double *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);

	void _APICALL _A4ISubSSE3(void *_a,void *_b,void *_c,unsigned int _stepa,unsigned int _stepb,unsigned int _stepc,unsigned int _count);
	void _APICALL _A4FSubSSE3(void *_a,void *_b,void *_c,unsigned int _stepa,unsigned int _stepb,unsigned int _stepc,unsigned int _count);

	void _APICALL _A2FMulVectorSSE3(void *_a,float *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A4FMulVectorSSE3(void *_a,float *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A2DMulVectorSSE3(void *_a,double *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);
	void _APICALL _A4DMulVectorSSE3(void *_a,double *_b,void *_c,unsigned int _stepa,unsigned int _stepc,unsigned int _count);

	void _APICALL _A2FNormalSSE3(void *_a,void *_b,unsigned int _stepa,unsigned int _stepb,unsigned int _count);

	void _APICALL _A3FMatrixTransformSSE3(void *_a,void *_b,void *_c,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A4FMatrixTransformSSE3(void *_a,void *_b,void *_c,int _stepa,int _stepc,unsigned int _count);

	void _APICALL _A2FProjSSE3(float *_a,void *_b,float *_c,float *_d,float *_e,int _stepa,int _stepe,int _flagoff,unsigned int _count);
	void _APICALL _A3FProjSSE3(float *_a,void *_b,float *_c,float *_d,float *_e,int _stepa,int _stepe,int _flagoff,unsigned int _count);
	void _APICALL _A4FProjSSE3(float *_a,void *_b,float *_c,float *_d,float *_e,int _stepa,int _stepe,int _flagoff,unsigned int _count);

	void _APICALL _A2FNormalSSE4(void *_a,void *_b,unsigned int _stepa,unsigned int _stepb,unsigned int _count);

	void _APICALL _A3DMatrixTransformAVX(void *_a,void *_b,void *_c,int _stepa,int _stepc,unsigned int _count);
	void _APICALL _A4DMatrixTransformAVX(void *_a,void *_b,void *_c,int _stepa,int _stepc,unsigned int _count);

}

#endif /* X86ARRAY_H_ */
#endif