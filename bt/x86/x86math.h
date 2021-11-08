//=============================================================================
///**
// *  @file  math.h
// *
// *  $Id: math.h 16.10.2011  $
// *
// *  @brief generator 3, assembler memory operations, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_MATH_H_
#define GEN3_MATH_H_

#include <bt.h>

#ifdef CPU_X86_32

OPTIMIZE_ON;

namespace bt {

// ******************************* CPU ********************************

	int _APICALL _ILog2CPU(unsigned int);

// ******************************* FPU ********************************

	float _APICALL _FsqrtFPU(float);

	double _APICALL _DsqrtFPU(double);

	float _APICALL _FFastInvSqrtFPU(float);

	void _APICALL _FSinCosFPU(float,float*,float*);

	void _APICALL _DSinCosFPU(double,double*,double*);

	float _APICALL _FArcTgFPU(float,float);

	double _APICALL _DArcTgFPU(double,double);

	float _APICALL _Fmul2NFPU(float,int);

	double _APICALL _Dmul2NFPU(double,int);

	int _APICALL _FTruncFPU(float);

	int _APICALL _DTruncFPU(double);

	int _APICALL _FRoundFPU(float);

	int _APICALL _DRoundFPU(double);

	int _APICALL _Fmul2NTruncFPU(float,int);

	int _APICALL _Dmul2NTruncFPU(double,int);

	int _APICALL _Fmul2NRoundFPU(float,int);

	int _APICALL _Dmul2NRoundFPU(double,int);

	float _APICALL _FLog2FPU(float);

	double _APICALL _DLog2FPU(double);

	_int32 _APICALL _ILog2FPU(unsigned _int32);

	_int32 _APICALL _LLog2FPU(_int64);

// ******************************* SSE ********************************
	float _APICALL _FsqrtSSE(float);

	float _APICALL _FFastInvSqrtSSE(float _a);

	void _APICALL _FSinCosSSE(float,float*,float*);
	
	void _APICALL _FFastSinCosSSE(float ,float *,float *);

	float _APICALL _FArcTgSSE(float _x,float _y);

	float _APICALL _Fmul2NSSE(float,int);

	int _APICALL _FTruncSSE(float);

	int _APICALL _FRoundSSE(float);

	float _APICALL _FExpSSE(float _a);

// ******************************* SSE2 *******************************

	double _APICALL _DsqrtSSE2(double);

	double _APICALL _DFastInvSqrtSSE2(double );

	void _APICALL _FSinCosSSE2(float,float*,float*);

	void _APICALL _DSinCosSSE2(double,double*,double*);

	void _APICALL _DFastSinCosSSE2(double,double*,double*);

	float _APICALL _Fmul2NSSE2(float,int);

	double _APICALL _Dmul2NSSE2(double,int);

	int _APICALL _DTruncSSE2(double);

	int _APICALL _DRoundSSE2(double);

	int _APICALL _Fmul2NTruncSSE2(float _a,int _b);

	int _APICALL _Dmul2NTruncSSE2(double _a,int _b);

	int _APICALL _Fmul2NRoundSSE2(float _a,int _b);

	int _APICALL _Dmul2NRoundSSE2(double _a,int _b);

	double _APICALL _DExpSSE2(double _a);

	int _APICALL _ILog2SSE2(unsigned int);

// ******************************* SSE3 *******************************

	void _APICALL _FSinCosSSE3(float,float*,float*);

// ******************************* SSE4 *******************************

	void _APICALL _FPCRCCSSE4(float **,float *);
	void _APICALL _DPCRCCSSE4(double **,double *);

	void _APICALL _FSplineCRSSE4(float *,float *,float ,float);
	void _APICALL _DSplineCRSSE4(double *,double *,double ,double);

	//float _STDCALL _FExpSSE4(float _a);

	//double _STDCALL _DExpSSE4(double _a);

	double _APICALL _DLog2SSE4(double _a);

}

OPTIMIZE_OFF;

#endif

#endif /* GEN3_MATH_H_ */
