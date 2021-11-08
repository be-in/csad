//=============================================================================
///**
// *  @file   x86_64matrix.h
// *
// *  $Id: x86_64matrix.h 16.10.2011  $
// *
// *  @brief generator 3, assembler matrix operations, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_X86_64_MATRIX_H_
#define GEN3_X86_64_MATRIX_H_

#include <bt.h>

#ifdef CPU_X86_64

namespace bt {

	void _APICALL _M4FTranslateSSE(void *,float *);
	void _APICALL _M4FScaleSSE(void *,float *);

	void _APICALL _M4FTRSSSE(void *,float *,float *,float *);

	void _APICALL _M4DTranslateSSE2(void *,double *);
	void _APICALL _M4DScaleSSE2(void *,double *);

	void _APICALL _M4FMulSSE3(void *a, void *b, void *c);

	void _APICALL _M4DMulSSE4(void *a, void *b, void *c);

	void _APICALL _M4FAddTranslateSSE4(void *a, float *b, void *c);
	void _APICALL _M4FAddScaleSSE4(void *a, float *b, void *c);

}

#endif

#endif /* GEN3_X86_64_MATRIX_H_ */
