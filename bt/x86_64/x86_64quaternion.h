/*
 * x86_64quaternion.h
 *
 *  Created on: 24.10.2013
 *      Author: Пантелеймонов А
 */

#ifndef X86_64QUATERNION_H_
#define X86_64QUATERNION_H_

#include <bt.h>

#ifdef CPU_X86_64

namespace bt {
/*
// ************** quaternion SSE function *******************

void _STDCALL _QFMulSSE(float * ,float * ,float * );

void _STDCALL _Q4FMatrixSSE(float * ,float * );

void _STDCALL _Q3FInvTransformSSE(float *,float *,float *);

// ************** quaternion SSE2 function *******************

void _STDCALL _QDMulSSE2(double * ,double * ,double * );

void _STDCALL _Q3DInvTransformSSE2(double * ,double * ,double * );
*/
// ************** quaternion SSE3 function *******************

void _APICALL _QFMulSSE3(float * ,float * ,float * );
void _APICALL _QDMulSSE3(double * ,double * ,double * );
/*
void _STDCALL _Q3FInvTransformSSE3(float *,float *,float *);

// ************** quaternion SSE4 function *******************

void _STDCALL _QFMulSSE4(float * ,float * ,float * );
void _STDCALL _QDMulSSE4(double * ,double * ,double * );

void _STDCALL _Q4FMatrixSSE4(float * ,float * );
void _STDCALL _Q4DMatrixSSE4(double * ,double * );

void _STDCALL _Q3FInvTransformSSE4(float *,float *,float *);
void _STDCALL _Q3DInvTransformSSE4(double *, double *, double *);
*/
}

#endif

#endif /* X86QUATERNION_H_ */
