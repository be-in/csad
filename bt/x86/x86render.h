/*
 * x86render.h
 *
 *  Created on: 01.11.2013
 *      Author: Пантелеймонов А
 */

#ifndef X86RENDER_H_
#define X86RENDER_H_

#include <bt.h>

namespace bt {

void _APICALL _S4AFdrawCPU(void *);

void _APICALL _S4AFDLdrawCPU(void *);

void _APICALL _S4AFDLdrawSSE(void *);

void _APICALL _S4AFSdrawSSE2(void *);

void _APICALL _S4AFDLSdrawSSE2(void *);

void _APICALL _V3BHalfTexelSSE3(void *,void *,int);
void _APICALL _V4BHalfTexelSSE3(void *,void *,int);
void _APICALL _V3BTexelSSE3(void *,void *,int,float,float);
void _APICALL _V4BTexelSSE3(void *,void *,int,float,float);

}

#endif /* X86RENDER_H_ */
