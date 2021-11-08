/*
 * x86extension.h
 *
 *  Created on: 18.09.2013
 *      Author: Пантелеймонов Александр
 */

#ifndef X86EXTENSION_H_
#define X86EXTENSION_H_

#include <bt.h>

#ifdef CPU_X86_32

namespace bt {

int _APICALL _ILogSizeCPU(unsigned int);

int _APICALL _ILogSizeFPU(unsigned int);

void _APICALL _V3FToBLHFPU(float *,float *);
void _APICALL _V3DToBLHFPU(double *,double *);

void _APICALL _V3FToBLFPU(float *,float *,float *);
void _APICALL _V3DToBLFPU(double *,double *,double *);

int _APICALL _ILogSizeSSE2(unsigned int);

_int32 _APICALL _NoiseGetSSE2();

}

#endif

#endif /* X86EXTENSION_H_ */
