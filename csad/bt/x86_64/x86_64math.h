//=============================================================================
///**
// *  @file   x86_64math.h
// *
// *  $Id: x86_64math.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector operations, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef X86_64MATH_H_
#define X86_64MATH_H_

#include <bt.h>

#ifdef CPU_X86_64

namespace bt {

	_ALIGN extern float rotateArcTg[];

	float _APICALL _FsqrtSSE(float);
	float _APICALL _FFastInvSqrtSSE(float _a);
	void _APICALL _FSinCosSSE(float a, float *__formala, float *a3);
	float _APICALL _FArcTgSSE(float _x,float _y);
	float _APICALL _FExpSSE(float _a);

	double _APICALL _DsqrtSSE2(double);
	double _APICALL _DFastInvSqrtSSE2(double _a);
	double _APICALL _DExpSSE2(double _a);
	int _APICALL _ILog2SSE2(unsigned int);

	void _APICALL _FSinCosSSE3(float a, float *b, float *c);
	
	float _APICALL _FArcTgSSE3(float _x,float _y);
	double _APICALL _DArcTgSSE3(double _x,double _y);
}

#endif

#endif /* X86_64MATH_H_ */