/*
 * x86quaternion.h
 *
 *  Created on: 24.10.2013
 *      Author: Пантелеймонов А
 */

#ifndef X86QUATERNION_H_
#define X86QUATERNION_H_

#include <bt.h>

#ifdef CPU_X86_32

namespace bt {

// ************** quaternion FPU function *******************

void _APICALL _Q4FVectorFPU(float *,float *);
void _APICALL _Q4DVectorFPU(double *,double *);
void _APICALL _QFInvFPU(float *,float *);
void _APICALL _QDInvFPU(double *,double *);
void _APICALL _Q3FInvTransformFPU(float *,float *,float *);
void _APICALL _Q3DInvTransformFPU(double *,double *,double *);

// ************** quaternion SSE function *******************

void _APICALL _QFMulSSE(float * ,float * ,float * );

void _APICALL _QFEulerSSE(float * _a,float * _b);

void _APICALL _Q4FMatrixSSE(float * ,float * );

void _APICALL _Q3FInvTransformSSE(float *,float *,float *);

// ************** quaternion SSE2 function *******************

void _APICALL _QDMulSSE2(double * ,double * ,double * );

void _APICALL _Q3DInvTransformSSE2(double * ,double * ,double * );

// ************** quaternion SSE3 function *******************

void _APICALL _QFMulSSE3(float * ,float * ,float * );
void _APICALL _QDMulSSE3(double * ,double * ,double * );

void _APICALL _Q3FInvTransformSSE3(float *,float *,float *);

// ************** quaternion SSE4 function *******************

void _APICALL _QFInvSSE4(float *,float *);
//void _STDCALL _QDInvSSE4(double *,double *);

void _APICALL _QFMulSSE4(float * ,float * ,float * );
void _APICALL _QDMulSSE4(double * ,double * ,double * );

void _APICALL _Q4FMatrixSSE4(float * ,float * );
void _APICALL _Q4DMatrixSSE4(double * ,double * );

void _APICALL _Q3FInvTransformSSE4(float *,float *,float *);
void _APICALL _Q3DInvTransformSSE4(double *, double *, double *);

}

#endif

#endif /* X86QUATERNION_H_ */
