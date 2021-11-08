//=============================================================================
///**
// *  @file defvector.cpp
// *
// *  $Id: defvector.cpp 23.05.2012  $
// *
// *  @brief generator 3, MS Visual C++ 2003-2008
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#include "basevector.h"
#include "basemath.h"
#include "baseext.h"
#include <bt.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

	struct IEE754FLOAT {
		unsigned _int32 mant : 23;
		unsigned _int32 exp : 8;
		unsigned _int32 sign : 1;
	};

	struct IEE754DOUBLE {
		unsigned _int64 mant : 52;
		unsigned _int64 exp : 11;
		unsigned _int64 sign : 1;
	};

	union conv4b {
		float valfloat;
		_int32 valint;
		unsigned _int32 valuint;
		char valarray[4];
		IEE754FLOAT valIEE;
	};

	union conv8b {
		double valdouble;
		_int64 valint64;
		unsigned _int64 valuint64;
		_int32 valint[2];
		unsigned _int32 valuint[2];
		char valarray[8];
		IEE754DOUBLE valIEE;
	};

	// ************** vector revers default function *******************

	void _APICALL _V4R8DEF(char *a,char *b) {
		char c3=a[0];
		a[0]=b[3];
		b[3]=c3;
		char c2=a[1];
		a[1]=b[2];
		b[2]=c2;
	}

	void _APICALL _V4R16DEF(short *a,short *b) {
		short c3=a[0];
		a[0]=b[3];
		b[3]=c3;
		short c2=a[1];
		a[1]=b[2];
		b[2]=c2;
	}

	void _APICALL _V4R32DEF(_int32 *a,_int32 *b) {
		_int32 c3=a[0];
		b[0]=a[3];
		b[3]=c3;
		_int32 c2=a[1];
		b[1]=a[2];
		b[2]=c2;
	}

	void _APICALL _V4R64DEF(_int64 *a,_int64 *b) {
		_int64 c3=a[0];
		b[0]=a[3];
		b[3]=c3;
		_int64 c2=a[1];
		b[1]=a[2];
		b[2]=c2;
	}

	// ************** vector copy default function *******************

	void _APICALL _V2R32CopyDEF(void *a,void *b)
	{
		_int32 *aa=(_int32 *)a;
		_int32 *ab=(_int32 *)b;
		ab[0]=aa[0];
		ab[1]=aa[1];
	}

	void _APICALL _V3R32CopyDEF(void *a,void *b)
	{
		_int32 *aa=(_int32 *)a;
		_int32 *ab=(_int32 *)b;
		ab[0]=aa[0];
		ab[1]=aa[1];
		ab[2]=aa[2];
	}

	void _APICALL _V4R32CopyDEF(void *a,void *b)
	{
		_int32 *aa=(_int32 *)a;
		_int32 *ab=(_int32 *)b;
		ab[0]=aa[0];
		ab[1]=aa[1];
		ab[2]=aa[2];
		ab[3]=aa[3];
	}

	void _APICALL _V2R64CopyDEF(void *a,void *b)
	{
		_int64 *aa=(_int64 *)a;
		_int64 *ab=(_int64 *)b;
		ab[0]=aa[0];
		ab[1]=aa[1];
	}

	void _APICALL _V3R64CopyDEF(void *a,void *b)
	{
		_int64 *aa=(_int64 *)a;
		_int64 *ab=(_int64 *)b;
		ab[0]=aa[0];
		ab[1]=aa[1];
		ab[2]=aa[2];
	}

	void _APICALL _V4R64CopyDEF(void *a,void *b)
	{
		_int64 *aa=(_int64 *)a;
		_int64 *ab=(_int64 *)b;
		ab[0]=aa[0];
		ab[1]=aa[1];
		ab[2]=aa[2];
		ab[3]=aa[3];
	}

	// ************** vector to default function *******************

	void _APICALL _V2BTo2FDEF(char *a, float *b) {
		b[0] = _IToFDEF((unsigned char)a[0]);
		b[1] = _IToFDEF((unsigned char)a[1]);
	}

	void _APICALL _V2BTo2DDEF(char *a, double *b) {
		b[0] = _IToDDEF((unsigned char)a[0]);
		b[1] = _IToDDEF((unsigned char)a[1]);
	}

	void _APICALL _V3BTo3FDEF(char *a, float *b) {
		b[0] = _IToFDEF((unsigned char)a[0]);
		b[1] = _IToFDEF((unsigned char)a[1]);
		b[2] = _IToFDEF((unsigned char)a[2]);
	}

	void _APICALL _V3BTo3DDEF(char *a, double *b) {
		b[0] = _IToDDEF((unsigned char)a[0]);
		b[1] = _IToDDEF((unsigned char)a[1]);
		b[2] = _IToDDEF((unsigned char)a[2]);
	}

	void _APICALL _V4BTo4FDEF(char *a, float *b) {
		b[0] = _IToFDEF((unsigned char)a[0]);
		b[1] = _IToFDEF((unsigned char)a[1]);
		b[2] = _IToFDEF((unsigned char)a[2]);
		b[3] = _IToFDEF((unsigned char)a[3]);
	}

	void _APICALL _V4BTo4DDEF(char *a,double *b) {
		double r[4];
		r[0]=_IToDDEF((unsigned char)a[0]);
		r[1]=_IToDDEF((unsigned char)a[1]);
		r[2]=_IToDDEF((unsigned char)a[2]);
		r[3]=_IToDDEF((unsigned char)a[3]);
		b[0]=r[0];
		b[1]=r[1];
		b[2]=r[2];
		b[3]=r[3];
	}

	void _APICALL _V2ITo2FDEF(_int32 *a,float *b) {
		b[0] = _IToFDEF(a[0]);
		b[1] = _IToFDEF(a[1]);
	}

	void _APICALL _V2ITo2DDEF(_int32 *a,double *b) {
		double r1=_IToDDEF(a[0]);
		double r2=_IToDDEF(a[1]);
		b[0]=r1;
		b[1]=r2;
	}

	void _APICALL _V3ITo3FDEF(_int32 *a,float *b) {
		b[0] = _IToFDEF(a[0]);
		b[1] = _IToFDEF(a[1]);
		b[2] = _IToFDEF(a[2]);
	}

	void _APICALL _V3ITo3DDEF(_int32 *a,double *b) {
		double r1=_IToDDEF(a[0]);
		double r2=_IToDDEF(a[1]);
		double r3=_IToDDEF(a[2]);
		b[0]=r1;
		b[1]=r2;
		b[2]=r3;
	}

	void _APICALL _V4ITo4BDEF(_int32 *a,char *b)
	{
		char r[4];
		r[0]=(char)a[0];
		r[1]=(char)a[1];
		r[2]=(char)a[2];
		r[3]=(char)a[3];
		b[0]=r[0];
		b[1]=r[1];
		b[2]=r[2];
		b[3]=r[3];
	}

	void _APICALL _V4ITo4FDEF(_int32 *a,float *b) {
		b[0] = _IToFDEF(a[0]);
		b[1] = _IToFDEF(a[1]);
		b[2] = _IToFDEF(a[2]);
		b[3] = _IToFDEF(a[3]);
	}

	void _APICALL _V4ITo4DDEF(_int32 *a,double *b) {
		double r[4];
		r[0]=_IToDDEF(a[0]);
		r[1]=_IToDDEF(a[1]);
		r[2]=_IToDDEF(a[2]);
		r[3]=_IToDDEF(a[3]);
		b[0]=r[0];
		b[1]=r[1];
		b[2]=r[2];
		b[3]=r[3];
	}

	void _APICALL _V2FTo2BDEF(float *a,char *b) {
		char *lb = b;
		float *la = a;
		lb[0] = _FRoundDEF(la[0]);
		lb[1] = _FRoundDEF(la[1]);
	}

	void _APICALL _V2FTo2IDEF(float *a,_int32 *b) {
		_int32 *lb = b;
		float *la = a;
		lb[0] = _FRoundDEF(la[0]);
		lb[1] = _FRoundDEF(la[1]);
	}

	void _APICALL _V2FTTo2IDEF(float *a,_int32 *b) {
		_int32 *lb = b;
		float *la = a;
		lb[0] = _FTruncDEF(la[0]);
		lb[1] = _FTruncDEF(la[1]);
	}

	void _APICALL _V2FTo2DDEF(float *a,double *b) {
		double r1=a[0];
		double r2=a[1];
		b[0]=r1;
		b[1]=r2;
	}

	void _APICALL _V3FTo3BDEF(float *a,char *b) {
		char *lb = b;
		float *la = a;
		lb[0] = _FRoundDEF(la[0]);
		lb[1] = _FRoundDEF(la[1]);
		lb[2] = _FRoundDEF(la[2]);
	}

	void _APICALL _V3FTo3IDEF(float *a,_int32 *b) {
		_int32 *lb = b;
		float *la = a;
		lb[0] = _FRoundDEF(la[0]);
		lb[1] = _FRoundDEF(la[1]);
		lb[2] = _FRoundDEF(la[2]);
	}

	void _APICALL _V3FTTo3IDEF(float *a,_int32 *b) {
		_int32 *lb = b;
		float *la = a;
		lb[0] = _FTruncDEF(la[0]);
		lb[1] = _FTruncDEF(la[1]);
		lb[2] = _FTruncDEF(la[2]);
	}

	void _APICALL _V3FTo3DDEF(float *a,double *b) {
		double r[4];
		r[0]=(double)a[0];
		r[1]=(double)a[1];
		r[2]=(double)a[2];
		b[0]=r[0];
		b[1]=r[1];
		b[2]=r[2];
	}

	void _APICALL _V4FTo4BDEF(float *a,char *b) {
		char *lb = b;
		float *la = a;
		lb[0] = _FRoundDEF(la[0]);
		lb[1] = _FRoundDEF(la[1]);
		lb[2] = _FRoundDEF(la[2]);
		lb[3] = _FRoundDEF(la[3]);
	}

	void _APICALL _V4FTo4IDEF(float *a,_int32 *b) {
		_int32 *lb = b;
		float *la = a;
		lb[0] = _FRoundDEF(la[0]);
		lb[1] = _FRoundDEF(la[1]);
		lb[2] = _FRoundDEF(la[2]);
		lb[3] = _FRoundDEF(la[3]);
	}

	void _APICALL _V4FTTo4IDEF(float *a,_int32 *b) {
		_int32 *lb = b;
		float *la = a;
		lb[0] = _FTruncDEF(la[0]);
		lb[1] = _FTruncDEF(la[1]);
		lb[2] = _FTruncDEF(la[2]);
		lb[3] = _FTruncDEF(la[3]);
	}

	void _APICALL _V4FTo4DDEF(float *a,double *b) {
		double r[4];
		r[0]=(double)a[0];
		r[1]=(double)a[1];
		r[2]=(double)a[2];
		r[3]=(double)a[3];
		b[0]=r[0];
		b[1]=r[1];
		b[2]=r[2];
		b[3]=r[3];
	}

	void _APICALL _V2DTo2BDEF(double *a,char *b) {
		b[0]=_FTruncDEF(a[0]);
		b[1] = _FTruncDEF(a[1]);
	}

	void _APICALL _V2DTo2IDEF(double *a,_int32 *b) {
		_int32 *lb = b;
		double *la = a;
		lb[0] = _DRoundDEF(la[0]);
		lb[1] = _DRoundDEF(la[1]);
	}

	void _APICALL _V2DTTo2IDEF(double *a,_int32 *b) {
		_int32 *lb = b;
		double *la = a;
		lb[0] = _DTruncDEF(la[0]);
		lb[1] = _DTruncDEF(la[1]);
	}

	void _APICALL _V2DTo2LDEF(double *a,_int64 *b) {
		_int64 *lb = b;
		double *la = a;
		lb[0] = _DRoundLDEF(la[0]);
		lb[1] = _DRoundLDEF(la[1]);
	}

	void _APICALL _V2DTTo2LDEF(double *a,_int64 *b) {
		_int64 *lb = b;
		double *la = a;
		lb[0] = _DTruncLDEF(la[0]);
		lb[1] = _DTruncLDEF(la[1]);
	}

	void _APICALL _V2DTo2FDEF(double *a,float *b) {
		b[0]=(float)a[0];
		b[1]=(float)a[1];
	}

	void _APICALL _V3DTo3BDEF(double *a,char *b) {
		b[0] = _FTruncDEF(a[0]);
		b[1] = _FTruncDEF(a[1]);
		b[2] = _FTruncDEF(a[2]);
	}

	void _APICALL _V3DTo3IDEF(double *a,_int32 *b) {
		_int32 *lb = b;
		double *la = a;
		lb[0] = _DRoundDEF(la[0]);
		lb[1] = _DRoundDEF(la[1]);
		lb[2] = _DRoundDEF(la[2]);
	}

	void _APICALL _V3DTTo3IDEF(double *a,_int32 *b) {
		_int32 *lb = b;
		double *la = a;
		lb[0] = _DTruncDEF(la[0]);
		lb[1] = _DTruncDEF(la[1]);
		lb[2] = _DTruncDEF(la[2]);
	}

	void _APICALL _V3DTo3FDEF(double *a,float *b) {
		float r[4];
		r[0]=(float)a[0];
		r[1]=(float)a[1];
		r[2]=(float)a[2];
		b[0]=r[0];
		b[1]=r[1];
		b[2]=r[2];
	}

	void _APICALL _V4DTo4BDEF(double *a,char *b) {
		char r[4];
		r[0]=(char)_DRoundDEF(a[0]);
		r[1]=(char)_DRoundDEF(a[1]);
		r[2]=(char)_DRoundDEF(a[2]);
		r[3]=(char)_DRoundDEF(a[3]);
		b[0]=r[0];
		b[1]=r[1];
		b[2]=r[2];
		b[3]=r[3];
	}

	void _APICALL _V4DTo4IDEF(double *a,_int32 *b) {
		_int32 *lb = b;
		double *la = a;
		lb[0] = _DRoundDEF(la[0]);
		lb[1] = _DRoundDEF(la[1]);
		lb[2] = _DRoundDEF(la[2]);
		lb[3] = _DRoundDEF(la[3]);
	}

	void _APICALL _V4DTTo4IDEF(double *a,_int32 *b) {
		_int32 *lb = b;
		double *la = a;
		lb[0] = _DTruncDEF(la[0]);
		lb[1] = _DTruncDEF(la[1]);
		lb[2] = _DTruncDEF(la[2]);
		lb[3] = _DTruncDEF(la[3]);
	}

	void _APICALL _V4DTo4FDEF(double *a,float *b) {
		float r[4];
		r[0]=(float)a[0];
		r[1]=(float)a[1];
		r[2]=(float)a[2];
		r[3]=(float)a[3];
		b[0]=r[0];
		b[1]=r[1];
		b[2]=r[2];
		b[3]=r[3];
	}

	// ************** vector inv default function *******************

	void _APICALL _V2FInvDEF(float * _a,float * _b)
	{
		_b[0]=-_a[0];
		_b[1]=-_a[1];
	}

	void _APICALL _V3FInvDEF(float * _a,float * _b)
	{
		_b[0]=-_a[0];
		_b[1]=-_a[1];
		_b[2]=-_a[2];
	}

	void _APICALL _V4FInvDEF(float * _a,float * _b)
	{
		float r[4];
		r[0]=-_a[0];
		r[1]=-_a[1];
		r[2]=-_a[2];
		r[3]=-_a[3];
		_b[0]=r[0];
		_b[1]=r[1];
		_b[2]=r[2];
		_b[3]=r[3];
	}

	void _APICALL _V2DInvDEF(double * _a,double * _b)
	{
		_b[0]=-_a[0];
		_b[1]=-_a[1];
	}

	void _APICALL _V3DInvDEF(double * _a,double * _b)
	{
		_b[0]=-_a[0];
		_b[1]=-_a[1];
		_b[2]=-_a[2];
	}

	void _APICALL _V4DInvDEF(double * _a,double * _b)
	{
		double r[4];
		r[0]=-_a[0];
		r[1]=-_a[1];
		r[2]=-_a[2];
		r[3]=-_a[3];
		_b[0]=r[0];
		_b[1]=r[1];
		_b[2]=r[2];
		_b[3]=r[3];
	}

	void _FASTCALL _V2FInvDEF_CPP(float * _a,float * _b)
	{
		_b[0]=-_a[0];
		_b[1]=-_a[1];
	}

	void _FASTCALL _V3FInvDEF_CPP(float * _a,float * _b)
	{
		_b[0]=-_a[0];
		_b[1]=-_a[1];
		_b[2]=-_a[2];
	}

	void _FASTCALL _V4FInvDEF_CPP(float * _a,float * _b)
	{
		float r[4];
		r[0]=-_a[0];
		r[1]=-_a[1];
		r[2]=-_a[2];
		r[3]=-_a[3];
		_b[0]=r[0];
		_b[1]=r[1];
		_b[2]=r[2];
		_b[3]=r[3];
	}

	void _FASTCALL _V2DInvDEF_CPP(double * _a,double * _b)
	{
		_b[0]=-_a[0];
		_b[1]=-_a[1];
	}

	void _FASTCALL _V3DInvDEF_CPP(double * _a,double * _b)
	{
		_b[0]=-_a[0];
		_b[1]=-_a[1];
		_b[2]=-_a[2];
	}

	void _FASTCALL _V4DInvDEF_CPP(double * _a,double * _b)
	{
		double r[4];
		r[0]=-_a[0];
		r[1]=-_a[1];
		r[2]=-_a[2];
		r[3]=-_a[3];
		_b[0]=r[0];
		_b[1]=r[1];
		_b[2]=r[2];
		_b[3]=r[3];
	}

	// ************** vector abs default function *******************

	#define _gen3toolabs(a) (a<0?-a:a)

	void _APICALL _V2FAbsDEF(float * _a,float * _b)
	{
		conv4b r1;
		conv4b r2;
		r1.valfloat=_a[0];
		r1.valint&=0x7FFFFFFF;
		r2.valfloat=_a[1];
		r2.valint&=0x7FFFFFFF;
		_b[0]=r1.valfloat;
		_b[1]=r2.valfloat;
	}

	void _APICALL _V3FAbsDEF(float * _a,float * _b)
	{
		conv4b r1;
		conv4b r2;
		conv4b r3;
		r1.valfloat=_a[0];
		r1.valint&=0x7FFFFFFF;
		r2.valfloat=_a[1];
		r2.valint&=0x7FFFFFFF;
		r3.valfloat=_a[2];
		r3.valint&=0x7FFFFFFF;
		_b[0]=r1.valfloat;
		_b[1]=r2.valfloat;
		_b[2]=r3.valfloat;
	}

	void _APICALL _V4FAbsDEF(float * _a,float * _b)
	{
		conv4b r1;
		conv4b r2;
		conv4b r3;
		conv4b r4;
		r1.valfloat = _a[0];
		r1.valint &= 0x7FFFFFFF;
		r2.valfloat = _a[1];
		r2.valint &= 0x7FFFFFFF;
		r3.valfloat = _a[2];
		r3.valint &= 0x7FFFFFFF;
		r4.valfloat = _a[3];
		r4.valint &= 0x7FFFFFFF;
		_b[0] = r1.valfloat;
		_b[1] = r2.valfloat;
		_b[2] = r3.valfloat;
		_b[3] = r4.valfloat;
	}

	void _APICALL _V2DAbsDEF(double * _a,double * _b)
	{
		_b[0]=_gen3toolabs(_a[0]);
		_b[1]=_gen3toolabs(_a[1]);
	}

	void _APICALL _V3DAbsDEF(double * _a,double * _b)
	{
		_b[0]=_gen3toolabs(_a[0]);
		_b[1]=_gen3toolabs(_a[1]);
		_b[2]=_gen3toolabs(_a[2]);
	}

	void _APICALL _V4DAbsDEF(double * _a,double * _b)
	{
		_b[0]=_gen3toolabs(_a[0]);
		_b[1]=_gen3toolabs(_a[1]);
		_b[2]=_gen3toolabs(_a[2]);
		_b[3]=_gen3toolabs(_a[3]);
	}

	void _FASTCALL _V2FAbsDEF_CPP(float * _a,float * _b)
	{
		_b[0]=_gen3toolabs(_a[0]);
		_b[1]=_gen3toolabs(_a[1]);
	}

	void _FASTCALL _V3FAbsDEF_CPP(float * _a,float * _b)
	{
		_b[0]=_gen3toolabs(_a[0]);
		_b[1]=_gen3toolabs(_a[1]);
		_b[2]=_gen3toolabs(_a[2]);
	}

	void _FASTCALL _V4FAbsDEF_CPP(float * _a,float * _b)
	{
		_b[0]=_gen3toolabs(_a[0]);
		_b[1]=_gen3toolabs(_a[1]);
		_b[2]=_gen3toolabs(_a[2]);
		_b[3]=_gen3toolabs(_a[3]);
	}

	void _FASTCALL _V2DAbsDEF_CPP(double * _a,double * _b)
	{
		_b[0]=_gen3toolabs(_a[0]);
		_b[1]=_gen3toolabs(_a[1]);
	}

	void _FASTCALL _V3DAbsDEF_CPP(double * _a,double * _b)
	{
		_b[0]=_gen3toolabs(_a[0]);
		_b[1]=_gen3toolabs(_a[1]);
		_b[2]=_gen3toolabs(_a[2]);
	}

	void _FASTCALL _V4DAbsDEF_CPP(double * _a,double * _b)
	{
		_b[0]=_gen3toolabs(_a[0]);
		_b[1]=_gen3toolabs(_a[1]);
		_b[2]=_gen3toolabs(_a[2]);
		_b[3]=_gen3toolabs(_a[3]);
	}

	// ************** vector min max default function *******************

	void _APICALL _V2FMinMaxDEF(float *_a,float *_b,float *_c)
	{
		float r0=_c[0];
		float r1=_c[1];
		if (_a[0]<_b[0]) _b[0]=_a[0];
		if (_a[0]>r0) r0=_a[0];
		if (_a[1]<_b[1]) _b[1]=_a[1];
		if (_a[1]>r1) r1=_a[1];
		_c[0]=r0;
		_c[1]=r1;
	}

	void _APICALL _V3FMinMaxDEF(float *_a,float *_b,float *_c)
	{
		float r0=_c[0];
		float r1=_c[1];
		float r2=_c[2];
		if (_a[0]<_b[0]) _b[0]=_a[0];
		if (_a[0]>r0) r0=_a[0];
		if (_a[1]<_b[1]) _b[1]=_a[1];
		if (_a[1]>r1) r1=_a[1];
		if (_a[2]<_b[2]) _b[2]=_a[2];
		if (_a[2]>r2) r2=_a[2];
		_c[0]=r0;
		_c[1]=r1;
		_c[2]=r2;
	}

	void _APICALL _V4FMinMaxDEF(float *_a,float *_b,float *_c)
	{
		float r0=_c[0];
		float r1=_c[1];
		float r2=_c[2];
		float r3=_c[3];
		if (_a[0]<_b[0]) _b[0]=_a[0];
		if (_a[0]>r0) r0=_a[0];
		if (_a[1]<_b[1]) _b[1]=_a[1];
		if (_a[1]>r1) r1=_a[1];
		if (_a[2]<_b[2]) _b[2]=_a[2];
		if (_a[2]>r2) r2=_a[2];
		if (_a[3]<_b[3]) _b[3]=_a[3];
		if (_a[3]>r3) r3=_a[3];
		_c[0]=r0;
		_c[1]=r1;
		_c[2]=r2;
		_c[3]=r3;
	}

	void _APICALL _V2DMinMaxDEF(double *_a,double *_b,double *_c)
	{
		double r0=_c[0];
		double r1=_c[1];
		if (_a[0]<_b[0]) _b[0]=_a[0];
		if (_a[0]>r0) r0=_a[0];
		if (_a[1]<_b[1]) _b[1]=_a[1];
		if (_a[1]>r1) r1=_a[1];
		_c[0]=r0;
		_c[1]=r1;
	}

	void _APICALL _V3DMinMaxDEF(double *_a,double *_b,double *_c)
	{
		double r0=_c[0];
		double r1=_c[1];
		double r2=_c[2];
		if (_a[0]<_b[0]) _b[0]=_a[0];
		if (_a[0]>r0) r0=_a[0];
		if (_a[1]<_b[1]) _b[1]=_a[1];
		if (_a[1]>r1) r1=_a[1];
		if (_a[2]<_b[2]) _b[2]=_a[2];
		if (_a[2]>r2) r2=_a[2];
		_c[0]=r0;
		_c[1]=r1;
		_c[2]=r2;
	}

	void _APICALL _V4DMinMaxDEF(double *_a,double *_b,double *_c)
	{
		double r0=_c[0];
		double r1=_c[1];
		double r2=_c[2];
		double r3=_c[3];
		if (_a[0]<_b[0]) _b[0]=_a[0];
		if (_a[0]>r0) r0=_a[0];
		if (_a[1]<_b[1]) _b[1]=_a[1];
		if (_a[1]>r1) r1=_a[1];
		if (_a[2]<_b[2]) _b[2]=_a[2];
		if (_a[2]>r2) r2=_a[2];
		if (_a[3]<_b[3]) _b[3]=_a[3];
		if (_a[3]>r3) r3=_a[3];
		_c[0]=r0;
		_c[1]=r1;
		_c[2]=r2;
		_c[3]=r3;
	}

	// ************** vector add default function *******************

	void _APICALL _V2IAddDEF(_int32 * _a,_int32 * _b,_int32 * _c)
	{
		_int32 r1=_a[0];
		_int32 r2=_a[1];
		_int32 t1=_b[0];
		_int32 t2=_b[1];
		_c[0]=r1+t1;
		_c[1]=r2+t2;
	}

	void _APICALL _V3IAddDEF(_int32 * _a,_int32 * _b,_int32 * _c) {
		_int32 r1=_a[0];
		_int32 r2=_a[1];
		_int32 r3=_a[2];
		_int32 t1=_b[0];
		_int32 t2=_b[1];
		_int32 t3=_b[2];
		_c[0]=r1+t1;
		_c[1]=r2+t2;
		_c[2]=r3+t3;
	}

	void _APICALL _V4IAddDEF(_int32 * _a,_int32 * _b,_int32 * _c) {
		_int32 r1=_a[0];
		_int32 r2=_a[1];
		_int32 r3=_a[2];
		_int32 r4=_a[3];
		_int32 t1=_b[0];
		_int32 t2=_b[1];
		_int32 t3=_b[2];
		_int32 t4=_b[3];
		_c[0]=r1+t1;
		_c[1]=r2+t2;
		_c[2]=r3+t3;
		_c[3]=r4+t4;
	}

	void _APICALL _V2FAddDEF(float * _a,float * _b,float * _c) {
		float r1=_a[0];
		float r2=_a[1];
		float t1=_b[0];
		float t2=_b[1];
		_c[0]=r1+t1;
		_c[1]=r2+t2;
	}

	void _APICALL _V3FAddDEF(float * _a,float * _b,float * _c) {
		float r1=_a[0];
		float r2=_a[1];
		float r3=_a[2];
		float t1=_b[0];
		float t2=_b[1];
		float t3=_b[2];
		_c[0]=r1+t1;
		_c[1]=r2+t2;
		_c[2]=r3+t3;
	}

	void _APICALL _V4FAddDEF(float * _a,float * _b,float * _c) {
		float r1=_a[0];
		float r2=_a[1];
		float r3=_a[2];
		float r4=_a[3];
		float t1=_b[0];
		float t2=_b[1];
		float t3=_b[2];
		float t4=_b[3];
		_c[0]=r1+t1;
		_c[1]=r2+t2;
		_c[2]=r3+t3;
		_c[3]=r4+t4;
	}

	void _APICALL _V2LAddDEF(_int64 * _a,_int64 * _b,_int64 * _c)
	{
		_int64 r1=_a[0];
		_int64 r2=_a[1];
		_int64 t1=_b[0];
		_int64 t2=_b[1];
		_c[0]=r1+t1;
		_c[1]=r2+t2;
	}

	void _APICALL _V2DAddDEF(double * _a,double * _b,double * _c) {
		double r1=_a[0];
		double r2=_a[1];
		double t1=_b[0];
		double t2=_b[1];
		_c[0]=r1+t1;
		_c[1]=r2+t2;
	}

	void _APICALL _V3DAddDEF(double * _a,double * _b,double * _c) {
		double r1=_a[0];
		double r2=_a[1];
		double r3=_a[2];
		double t1=_b[0];
		double t2=_b[1];
		double t3=_b[2];
		_c[0]=r1+t1;
		_c[1]=r2+t2;
		_c[2]=r3+t3;
	}

	void _APICALL _V4DAddDEF(double * _a,double * _b,double * _c) {
		double r1=_a[0];
		double r2=_a[1];
		double r3=_a[2];
		double r4=_a[3];
		double t1=_b[0];
		double t2=_b[1];
		double t3=_b[2];
		double t4=_b[3];
		_c[0]=r1+t1;
		_c[1]=r2+t2;
		_c[2]=r3+t3;
		_c[3]=r4+t4;
	}

	void _FASTCALL _V2IAddDEF_CPP(_int32 * _a,_int32 * _b,_int32 * _c)
	{
		_c[0]=_a[0]+_b[0];
		_c[1]=_a[1]+_b[1];
	}

	void _FASTCALL _V3IAddDEF_CPP(_int32 * _a, _int32 * _b, _int32 * _c)
	{
		_c[0] = _a[0] + _b[0];
		_c[1] = _a[1] + _b[1];
		_c[2] = _a[2] + _b[2];
	}

	void _FASTCALL _V4IAddDEF_CPP(_int32 * _a, _int32 * _b, _int32 * _c)
	{
		_c[0] = _a[0] + _b[0];
		_c[1] = _a[1] + _b[1];
		_c[2] = _a[2] + _b[2];
		_c[3] = _a[3] + _b[3];
	}

	void _FASTCALL _V2FAddDEF_CPP(float * _a, float * _b, float * _c)
	{
		_c[0] = _a[0] + _b[0];
		_c[1] = _a[1] + _b[1];
	}

	void _FASTCALL _V3FAddDEF_CPP(float * _a,float * _b,float * _c) {
		_c[0]=_a[0]+_b[0];
		_c[1]=_a[1]+_b[1];
		_c[2]=_a[2]+_b[2];
	}

	void _FASTCALL _V4FAddDEF_CPP(float * _a,float * _b,float * _c) {
		float r1=_a[0];
		float r2=_a[1];
		float r3=_a[2];
		float r4=_a[3];
		float t1=_b[0];
		float t2=_b[1];
		float t3=_b[2];
		float t4=_b[3];
		_c[0]=r1+t1;
		_c[1]=r2+t2;
		_c[2]=r3+t3;
		_c[3]=r4+t4;
	}

	void _FASTCALL _V2LAddDEF_CPP(_int64 * _a,_int64 * _b,_int64 * _c)
	{
		_c[0]=_a[0]+_b[0];
		_c[1]=_a[1]+_b[1];
	}

	void _FASTCALL _V2DAddDEF_CPP(double * _a,double * _b,double * _c) {
		_c[0]=_a[0]+_b[0];
		_c[1]=_a[1]+_b[1];
	}

	void _FASTCALL _V3DAddDEF_CPP(double * _a,double * _b,double * _c) {
		_c[0]=_a[0]+_b[0];
		_c[1]=_a[1]+_b[1];
		_c[2]=_a[2]+_b[2];
	}

	void _FASTCALL _V4DAddDEF_CPP(double * _a,double * _b,double * _c) {
		double r1=_a[0];
		double r2=_a[1];
		double r3=_a[2];
		double r4=_a[3];
		double t1=_b[0];
		double t2=_b[1];
		double t3=_b[2];
		double t4=_b[3];
		_c[0]=r1+t1;
		_c[1]=r2+t2;
		_c[2]=r3+t3;
		_c[3]=r4+t4;
	}

	// ************** vector sub default function *******************

	void _APICALL _V2ISubDEF(_int32 * _a,_int32 * _b,_int32 * _c) {
		_int32 r1=_a[0];
		_int32 r2=_a[1];
		_int32 t1=_b[0];
		_int32 t2=_b[1];
		_c[0]=r1-t1;
		_c[1]=r2-t2;
	}

	void _APICALL _V3ISubDEF(_int32 * _a,_int32 * _b,_int32 * _c) {
		_int32 r1=_a[0];
		_int32 r2=_a[1];
		_int32 r3=_a[2];
		_int32 t1=_b[0];
		_int32 t2=_b[1];
		_int32 t3=_b[2];
		_c[0]=r1-t1;
		_c[1]=r2-t2;
		_c[2]=r3-t3;
	}

	void _APICALL _V4ISubDEF(_int32 * _a,_int32 * _b,_int32 * _c) {
		_int32 r1=_a[0];
		_int32 r2=_a[1];
		_int32 r3=_a[2];
		_int32 r4=_a[3];
		_int32 t1=_b[0];
		_int32 t2=_b[1];
		_int32 t3=_b[2];
		_int32 t4=_b[3];
		_c[0]=r1-t1;
		_c[1]=r2-t2;
		_c[2]=r3-t3;
		_c[3]=r4-t4;
	}

	void _APICALL _V2FSubDEF(float * _a,float * _b,float * _c) {
		float r1=_a[0];
		float r2=_a[1];
		float t1=_b[0];
		float t2=_b[1];
		_c[0]=r1-t1;
		_c[1]=r2-t2;
	}

	void _APICALL _V3FSubDEF(float * _a,float * _b,float * _c) {
		float r1=_a[0];
		float r2=_a[1];
		float r3=_a[2];
		float t1=_b[0];
		float t2=_b[1];
		float t3=_b[2];
		_c[0]=r1-t1;
		_c[1]=r2-t2;
		_c[2]=r3-t3;
	}

	void _APICALL _V4FSubDEF(float * _a,float * _b,float * _c) {
		float r1=_a[0];
		float r2=_a[1];
		float r3=_a[2];
		float r4=_a[3];
		float t1=_b[0];
		float t2=_b[1];
		float t3=_b[2];
		float t4=_b[3];
		_c[0]=r1-t1;
		_c[1]=r2-t2;
		_c[2]=r3-t3;
		_c[3]=r4-t4;
	}

	void _APICALL _V2LSubDEF(_int64 * _a,_int64 * _b,_int64 * _c)
	{
		_int64 r1=_a[0];
		_int64 r2=_a[1];
		_int64 t1=_b[0];
		_int64 t2=_b[1];
		_c[0]=r1-t1;
		_c[1]=r2-t2;
	}

	void _APICALL _V2DSubDEF(double * _a,double * _b,double * _c) {
		_c[0]=_a[0]-_b[0];
		_c[1]=_a[1]-_b[1];
	}

	void _APICALL _V3DSubDEF(double * _a,double * _b,double * _c) {
		double r1=_a[0];
		double r2=_a[1];
		double r3=_a[2];
		double t1=_b[0];
		double t2=_b[1];
		double t3=_b[2];
		_c[0]=r1-t1;
		_c[1]=r2-t2;
		_c[2]=r3-t3;
	}

	void _APICALL _V4DSubDEF(double * _a,double * _b,double * _c) {
		double r1=_a[0];
		double r2=_a[1];
		double r3=_a[2];
		double r4=_a[3];
		double t1=_b[0];
		double t2=_b[1];
		double t3=_b[2];
		double t4=_b[3];
		_c[0]=r1-t1;
		_c[1]=r2-t2;
		_c[2]=r3-t3;
		_c[3]=r4-t4;
	}

	void _FASTCALL _V2FSubDEF_CPP(float * _a,float * _b,float * _c) {
		_c[0]=_a[0]-_b[0];
		_c[1]=_a[1]-_b[1];
	}

	void _FASTCALL _V3FSubDEF_CPP(float * _a,float * _b,float * _c) {
		_c[0]=_a[0]-_b[0];
		_c[1]=_a[1]-_b[1];
		_c[2]=_a[2]-_b[2];
	}

	void _FASTCALL _V4FSubDEF_CPP(float * _a,float * _b,float * _c) {
		double r1=_a[0];
		double r2=_a[1];
		double r3=_a[2];
		double r4=_a[3];
		double t1=_b[0];
		double t2=_b[1];
		double t3=_b[2];
		double t4=_b[3];
		_c[0]=r1-t1;
		_c[1]=r2-t2;
		_c[2]=r3-t3;
		_c[3]=r4-t4;
	}

	void _FASTCALL _V2DSubDEF_CPP(double * _a,double * _b,double * _c) {
		_c[0]=_a[0]-_b[0];
		_c[1]=_a[1]-_b[1];
	}

	void _FASTCALL _V3DSubDEF_CPP(double * _a,double * _b,double * _c) {
		_c[0]=_a[0]-_b[0];
		_c[1]=_a[1]-_b[1];
		_c[2]=_a[2]-_b[2];
	}

	void _FASTCALL _V4DSubDEF_CPP(double * _a,double * _b,double * _c) {
		double r[4];
		r[0]=_a[0]-_b[0];
		r[1]=_a[1]-_b[1];
		r[2]=_a[2]-_b[2];
		r[3]=_a[3]-_b[3];
		_c[0]=r[0];
		_c[1]=r[1];
		_c[2]=r[2];
		_c[3]=r[3];
	}

	// ************** vector scale default function *******************

	void _APICALL _V2IScaleDEF(_int32 * _a,_int32 * _b,float _c)
	{
		_b[0] = _FTruncDEF(_a[0] * _c);
		_b[1] = _FTruncDEF(_a[1] * _c);
	}

	void _APICALL _V3IScaleDEF(_int32 * _a,_int32 * _b,float _c)
	{
		_b[0] = _FTruncDEF(_a[0] * _c);
		_b[1] = _FTruncDEF(_a[1] * _c);
		_b[2] = _FTruncDEF(_a[2] * _c);
	}

	void _APICALL _V4IScaleDEF(_int32 * _a,_int32 * _b,float _c)
	{
		_int32 r[4];
		r[0]=_a[0];
		r[1]=_a[1];
		r[2]=_a[2];
		r[3]=_a[3];
		_b[0] = _FTruncDEF(r[0] * _c);
		_b[1] = _FTruncDEF(r[1] * _c);
		_b[2] = _FTruncDEF(r[2] * _c);
		_b[3] = _FTruncDEF(r[3] * _c);
	}

	void _APICALL _V2FScaleDEF(float * _a,float * _b,float _c) {
		_b[0]=_a[0]*_c;
		_b[1]=_a[1]*_c;
	}

	void _APICALL _V3FScaleDEF(float * _a,float * _b,float _c) {
		_b[0]=_a[0]*_c;
		_b[1]=_a[1]*_c;
		_b[2]=_a[2]*_c;
	}

	void _APICALL _V4FScaleDEF(float * _a,float * _b,float _c) {
		float r[4];
		r[0]=_a[0];
		r[1]=_a[1];
		r[2]=_a[2];
		r[3]=_a[3];
		_b[0]=r[0]*_c;
		_b[1]=r[1]*_c;
		_b[2]=r[2]*_c;
		_b[3]=r[3]*_c;
	}

	void _APICALL _V2LScaleDEF(_int64 * _a,_int64 * _b,double _c)
	{
		_b[0] = _DTruncLDEF(_LToDDEF(_a[0]) * _c);
		_b[1] = _DTruncLDEF(_LToDDEF(_a[1]) * _c);
	}

	void _APICALL _V2DScaleDEF(double * _a,double * _b,double _c) {
		_b[0]=_a[0]*_c;
		_b[1]=_a[1]*_c;
	}

	void _APICALL _V3DScaleDEF(double * _a,double * _b,double _c) {
		_b[0]=_a[0]*_c;
		_b[1]=_a[1]*_c;
		_b[2]=_a[2]*_c;
	}

	void _APICALL _V4DScaleDEF(double * _a,double * _b,double _c) {
		double r[4];
		r[0]=_a[0];
		r[1]=_a[1];
		r[2]=_a[2];
		r[3]=_a[3];
		_b[0]=r[0]*_c;
		_b[1]=r[1]*_c;
		_b[2]=r[2]*_c;
		_b[3]=r[3]*_c;
	}

	void _FASTCALL _V2FScaleDEF_CPP(float * _a,float * _b,float _c) {
		_b[0]=_a[0]*_c;
		_b[1]=_a[1]*_c;
	}

	void _FASTCALL _V3FScaleDEF_CPP(float * _a,float * _b,float _c) {
		_b[0]=_a[0]*_c;
		_b[1]=_a[1]*_c;
		_b[2]=_a[2]*_c;
	}

	void _FASTCALL _V4FScaleDEF_CPP(float * _a,float * _b,float _c) {
		float r[4];
		r[0]=_a[0];
		r[1]=_a[1];
		r[2]=_a[2];
		r[3]=_a[3];
		_b[0]=r[0]*_c;
		_b[1]=r[1]*_c;
		_b[2]=r[2]*_c;
		_b[3]=r[3]*_c;
	}

	void _FASTCALL _V2DScaleDEF_CPP(double * _a,double * _b,double _c) {
		_b[0]=_a[0]*_c;
		_b[1]=_a[1]*_c;
	}

	void _FASTCALL _V3DScaleDEF_CPP(double * _a,double * _b,double _c) {
		_b[0]=_a[0]*_c;
		_b[1]=_a[1]*_c;
		_b[2]=_a[2]*_c;
	}

	void _FASTCALL _V4DScaleDEF_CPP(double * _a,double * _b,double _c) {
		double r[4];
		r[0]=_a[0];
		r[1]=_a[1];
		r[2]=_a[2];
		r[3]=_a[3];
		_b[0]=r[0]*_c;
		_b[1]=r[1]*_c;
		_b[2]=r[2]*_c;
		_b[3]=r[3]*_c;
	}

	// ************** mul default function *******************

	void _APICALL _V2IMulDEF(_int32 * _a,_int32 * _b,_int32 * _c)
	{
		_c[0]=_a[0]*_b[0];
		_c[1]=_a[1]*_b[1];
	}

	void _APICALL _V3IMulDEF(_int32 * _a,_int32 * _b,_int32 * _c)
	{
		_c[0]=_a[0]*_b[0];
		_c[1]=_a[1]*_b[1];
		_c[2]=_a[2]*_b[2];
	}

	void _APICALL _V4IMulDEF(_int32 * _a,_int32 * _b,_int32 * _c)
	{
		_c[0]=_a[0]*_b[0];
		_c[1]=_a[1]*_b[1];
		_c[2]=_a[2]*_b[2];
		_c[3]=_a[3]*_b[3];
	}

	void _APICALL _V2FMulDEF(float * _a,float * _b,float * _c) {
		_c[0]=_a[0]*_b[0];
		_c[1]=_a[1]*_b[1];
	}

	void _APICALL _V3FMulDEF(float * _a,float * _b,float * _c) {
		_c[0]=_a[0]*_b[0];
		_c[1]=_a[1]*_b[1];
		_c[2]=_a[2]*_b[2];
	}

	void _APICALL _V4FMulDEF(float * _a,float * _b,float * _c) {
		_c[0]=_a[0]*_b[0];
		_c[1]=_a[1]*_b[1];
		_c[2]=_a[2]*_b[2];
		_c[3]=_a[3]*_b[3];
	}

	void _APICALL _V2DMulDEF(double * _a,double * _b,double * _c) {
		_c[0]=_a[0]*_b[0];
		_c[1]=_a[1]*_b[1];
	}

	void _APICALL _V3DMulDEF(double * _a,double * _b,double * _c) {
		_c[0]=_a[0]*_b[0];
		_c[1]=_a[1]*_b[1];
		_c[2]=_a[2]*_b[2];
	}

	void _APICALL _V4DMulDEF(double * _a,double * _b,double * _c) {
		_c[0]=_a[0]*_b[0];
		_c[1]=_a[1]*_b[1];
		_c[2]=_a[2]*_b[2];
		_c[3]=_a[3]*_b[3];
	}

	void _FASTCALL _V2FMulDEF_CPP(float * _a,float * _b,float * _c) {
		_c[0]=_a[0]*_b[0];
		_c[1]=_a[1]*_b[1];
	}

	void _FASTCALL _V3FMulDEF_CPP(float * _a,float * _b,float * _c) {
		_c[0]=_a[0]*_b[0];
		_c[1]=_a[1]*_b[1];
		_c[2]=_a[2]*_b[2];
	}

	void _FASTCALL _V4FMulDEF_CPP(float * _a,float * _b,float * _c) {
		_c[0]=_a[0]*_b[0];
		_c[1]=_a[1]*_b[1];
		_c[2]=_a[2]*_b[2];
		_c[3]=_a[3]*_b[3];
	}

	void _FASTCALL _V2DMulDEF_CPP(double * _a,double * _b,double * _c) {
		_c[0]=_a[0]*_b[0];
		_c[1]=_a[1]*_b[1];
	}

	void _FASTCALL _V3DMulDEF_CPP(double * _a,double * _b,double * _c) {
		_c[0]=_a[0]*_b[0];
		_c[1]=_a[1]*_b[1];
		_c[2]=_a[2]*_b[2];
	}

	void _FASTCALL _V4DMulDEF_CPP(double * _a,double * _b,double * _c) {
		_c[0]=_a[0]*_b[0];
		_c[1]=_a[1]*_b[1];
		_c[2]=_a[2]*_b[2];
		_c[3]=_a[3]*_b[3];
	}

	// ************** div default function *******************

	void _APICALL _V2FDivDEF(float * _a,float * _b,float * _c) {
		_c[0]=_a[0]/_b[0];
		_c[1]=_a[1]/_b[1];
	}

	void _APICALL _V3FDivDEF(float * _a,float * _b,float * _c) {
		_c[0]=_a[0]/_b[0];
		_c[1]=_a[1]/_b[1];
		_c[2]=_a[2]/_b[2];
	}

	void _APICALL _V4FDivDEF(float * _a,float * _b,float * _c) {
		_c[0]=_a[0]/_b[0];
		_c[1]=_a[1]/_b[1];
		_c[2]=_a[2]/_b[2];
		_c[3]=_a[3]/_b[3];
	}

	void _APICALL _V2DDivDEF(double * _a,double * _b,double * _c) {
		_c[0]=_a[0]/_b[0];
		_c[1]=_a[1]/_b[1];
	}

	void _APICALL _V3DDivDEF(double * _a,double * _b,double * _c) {
		_c[0]=_a[0]/_b[0];
		_c[1]=_a[1]/_b[1];
		_c[2]=_a[2]/_b[2];
	}

	void _APICALL _V4DDivDEF(double * _a,double * _b,double * _c) {
		_c[0]=_a[0]/_b[0];
		_c[1]=_a[1]/_b[1];
		_c[2]=_a[2]/_b[2];
		_c[3]=_a[3]/_b[3];
	}

	// ************** vector mul2NTrunc default function *******************

	void _APICALL _V2Fmul2NTruncDEF(float * _a,_int32 * _b,_int32 _c) {
		_int32 lc = _c;
		float *la = _a;
		_int32 *lb = _b;
		lb[0] = _Fmul2NTruncDEF(la[0], lc);
		lb[1] = _Fmul2NTruncDEF(la[1], lc);
	}

	void _APICALL _V3Fmul2NTruncDEF(float * _a,_int32 * _b,_int32 _c) {
		_int32 lc = _c;
		float *la = _a;
		_int32 *lb = _b;
		lb[0] = _Fmul2NTruncDEF(la[0], lc);
		lb[1] = _Fmul2NTruncDEF(la[1], lc);
		lb[2] = _Fmul2NTruncDEF(la[2], lc);
	}

	void _APICALL _V4Fmul2NTruncDEF(float * _a,_int32 * _b,_int32 _c) {
		_int32 lc = _c;
		float *la = _a;
		_int32 *lb = _b;
		lb[0] = _Fmul2NTruncDEF(la[0], lc);
		lb[1] = _Fmul2NTruncDEF(la[1], lc);
		lb[2] = _Fmul2NTruncDEF(la[2], lc);
		lb[3] = _Fmul2NTruncDEF(la[3], lc);
	}

	void _APICALL _V2Dmul2NTruncDEF(double * _a,_int32 * _b,_int32 _c) {
		_int32 lc = _c;
		double *la = _a;
		_int32 *lb = _b;
		lb[0] = _Dmul2NTruncDEF(la[0], lc);
		lb[1] = _Dmul2NTruncDEF(la[1], lc);
	}

	void _APICALL _V3Dmul2NTruncDEF(double * _a,_int32 * _b,_int32 _c) {
		_int32 lc = _c;
		double *la = _a;
		_int32 *lb = _b;
		lb[0] = _Dmul2NTruncDEF(la[0], lc);
		lb[1] = _Dmul2NTruncDEF(la[1], lc);
		lb[2] = _Dmul2NTruncDEF(la[2], lc);
	}

	void _APICALL _V4Dmul2NTruncDEF(double * _a,_int32 * _b,_int32 _c) {
		_int32 lc = _c;
		double *la = _a;
		_int32 *lb = _b;
		lb[0] = _Dmul2NTruncDEF(la[0], lc);
		lb[1] = _Dmul2NTruncDEF(la[1], lc);
		lb[2] = _Dmul2NTruncDEF(la[2], lc);
		lb[3] = _Dmul2NTruncDEF(la[3], lc);
	}

	// ************** vector mul2NRound default function *******************

	void _APICALL _V2Fmul2NRoundDEF(float * _a,_int32 * _b,_int32 _c) {
		_int32 lc = _c;
		float *la = _a;
		_int32 *lb = _b;
		lb[0] = _Fmul2NRoundDEF(la[0], lc);
		lb[1] = _Fmul2NRoundDEF(la[1], lc);
	}

	void _APICALL _V3Fmul2NRoundDEF(float * _a,_int32 * _b,_int32 _c) {
		_int32 lc = _c;
		float *la = _a;
		_int32 *lb = _b;
		lb[0] = _Fmul2NRoundDEF(la[0], lc);
		lb[1] = _Fmul2NRoundDEF(la[1], lc);
		lb[2] = _Fmul2NRoundDEF(la[2], lc);
	}

	void _APICALL _V4Fmul2NRoundDEF(float * _a,_int32 * _b,_int32 _c) {
		_int32 lc = _c;
		float *la = _a;
		_int32 *lb = _b;
		lb[0] = _Fmul2NRoundDEF(la[0], lc);
		lb[1] = _Fmul2NRoundDEF(la[1], lc);
		lb[2] = _Fmul2NRoundDEF(la[2], lc);
		lb[3] = _Fmul2NRoundDEF(la[3], lc);
	}

	void _APICALL _V2Dmul2NRoundDEF(double * _a,_int32 * _b,_int32 _c) {
		_int32 lc = _c;
		double *la = _a;
		_int32 *lb = _b;
		lb[0] = _Dmul2NRoundDEF(la[0], lc);
		lb[1] = _Dmul2NRoundDEF(la[1], lc);
	}

	void _APICALL _V3Dmul2NRoundDEF(double * _a,_int32 * _b,_int32 _c) {
		_int32 lc = _c;
		double *la = _a;
		_int32 *lb = _b;
		lb[0] = _Dmul2NRoundDEF(la[0], lc);
		lb[1] = _Dmul2NRoundDEF(la[1], lc);
		lb[2] = _Dmul2NRoundDEF(la[2], lc);
	}

	void _APICALL _V4Dmul2NRoundDEF(double * _a,_int32 * _b,_int32 _c) {
		_int32 lc = _c;
		double *la = _a;
		_int32 *lb = _b;
		lb[0] = _Dmul2NRoundDEF(la[0], lc);
		lb[1] = _Dmul2NRoundDEF(la[1], lc);
		lb[2] = _Dmul2NRoundDEF(la[2], lc);
		lb[3] = _Dmul2NRoundDEF(la[3], lc);
	}

	// ************** vector mul2N default function *******************

	void _APICALL _V2Imul2NDEF(_int32 * _a,_int32 * _b,_int32 _c)
	{
		_int32 c=_c;
		if (c<0) {
			c=-c;
			_b[0]=_a[0]>>c;
			_b[1]=_a[1]>>c;
		} else {
			_b[0]=_a[0]<<c;
			_b[1]=_a[1]<<c;
		}
	}

	void _APICALL _V3Imul2NDEF(_int32 * _a,_int32 * _b,_int32 _c)
	{
		_int32 c=_c;
		if (c<0) {
			c=-c;
			_b[0]=_a[0]>>c;
			_b[1]=_a[1]>>c;
			_b[2]=_a[2]>>c;
		} else {
			_b[0]=_a[0]<<c;
			_b[1]=_a[1]<<c;
			_b[2]=_a[2]<<c;
		}
	}

	void _APICALL _V4Imul2NDEF(_int32 * _a,_int32 * _b,_int32 _c)
	{
		_int32 c=_c;
		if (c<0) {
			c=-c;
			_b[0]=_a[0]>>c;
			_b[1]=_a[1]>>c;
			_b[2]=_a[2]>>c;
			_b[3]=_a[3]>>c;
		} else {
			_b[0]=_a[0]<<c;
			_b[1]=_a[1]<<c;
			_b[2]=_a[2]<<c;
			_b[3]=_a[3]<<c;
		}
	}

	void _APICALL _V2Fmul2NDEF(float * _a,float * _b,_int32 _c) {
		float b=0;
		_int32* mexp=(_int32*)&b;
		*mexp=(((_c+0x7f) &0xFF)<<23);
		_b[0]=_a[0]*b;
		_b[1]=_a[1]*b;
	}

	void _APICALL _V3Fmul2NDEF(float * _a,float * _b,_int32 _c) {
		float b=0;
		_int32* mexp=(_int32*)&b;
		*mexp=(((_c+0x7f) &0xFF)<<23);
		_b[0]=_a[0]*b;
		_b[1]=_a[1]*b;
		_b[2]=_a[2]*b;
	}

	void _APICALL _V4Fmul2NDEF(float * _a,float * _b,_int32 _c) {
		float b=0;
		_int32* mexp=(_int32*)&b;
		*mexp=(((_c+0x7f) &0xFF)<<23);
		float r[4];
		r[0]=_a[0]*b;
		r[1]=_a[1]*b;
		r[2]=_a[2]*b;
		r[3]=_a[3]*b;
		_b[0]=r[0];
		_b[1]=r[1];
		_b[2]=r[2];
		_b[3]=r[3];
	}

	void _APICALL _V2Dmul2NDEF(double * _a,double * _b,_int32 _c) {
		double c=(1<<_c);
		if (_c<0) c=1.0/(1<<(-_c));
		_b[0]=_a[0]*c;
		_b[1]=_a[1]*c;
	}

	void _APICALL _V3Dmul2NDEF(double * _a,double * _b,_int32 _c) {
		double c=(1<<_c);
		if (_c<0) c=1.0/(1<<(-_c));
		_b[0]=_a[0]*c;
		_b[1]=_a[1]*c;
		_b[2]=_a[2]*c;
	}

	void _APICALL _V4Dmul2NDEF(double * _a,double * _b,_int32 _c) {
		double c=(1<<_c);
		if (_c<0) c=1.0/(1<<(-_c));
		double r[4];
		r[0]=_a[0]*c;
		r[1]=_a[1]*c;
		r[2]=_a[2]*c;
		r[3]=_a[3]*c;
		_b[0]=r[0];
		_b[1]=r[1];
		_b[2]=r[2];
		_b[3]=r[3];
	}

	// ************** vector scale and mode default function *******************

	void _APICALL _V2FScaleModDEF(float * _a,float * _b,float _c)
	{
		float rd[2];
		rd[0]=*_a;
		rd[1]=*(_a+1);
		float invc=1.0f/_c;
		rd[0]*=invc;
		rd[1]*=invc;
		_int32 va[3];
		_V2FTTo2IDEF(rd,va);
		_b[0]=(rd[0]-va[0])*_c;
		_b[1]=(rd[1]-va[1])*_c;
	}

	void _APICALL _V3FScaleModDEF(float * _a,float * _b,float _c)
	{
		float rd[3];
		rd[0]=*_a;
		rd[1]=*(_a+1);
		rd[2]=*(_a+2);
		float invc=1.0f/_c;
		rd[0]*=invc;
		rd[1]*=invc;
		rd[2]*=invc;
		_int32 va[3];
		_V3FTTo3IDEF(rd,va);
		_b[0]=(rd[0]-va[0])*_c;
		_b[1]=(rd[1]-va[1])*_c;
		_b[2]=(rd[2]-va[2])*_c;
	}

	void _APICALL _V4FScaleModDEF(float * _a,float * _b,float _c)
	{
		float rd[4];
		rd[0]=*_a;
		rd[1]=*(_a+1);
		rd[2]=*(_a+2);
		rd[3]=*(_a+3);
		float invc=1.0f/_c;
		rd[0]*=invc;
		rd[1]*=invc;
		rd[2]*=invc;
		rd[3]*=invc;
		_int32 va[4];
		_V4FTTo4IDEF(rd,va);
		_b[0]=(rd[0]-va[0])*_c;
		_b[1]=(rd[1]-va[1])*_c;
		_b[2]=(rd[2]-va[2])*_c;
		_b[3]=(rd[3]-va[3])*_c;
	}

	void _APICALL _V3DScaleModDEF(double * _a,double * _b,double _c)
	{
		double rd[3];
		rd[0]=*_a;
		rd[1]=*(_a+1);
		rd[2]=*(_a+2);
		double invc=1.0/_c;
		rd[0]*=invc;
		rd[1]*=invc;
		rd[2]*=invc;
		_int32 va[3];
		_V3DTTo3IDEF(rd,va);
		_b[0]=(rd[0]-va[0])*_c;
		_b[1]=(rd[1]-va[1])*_c;
		_b[2]=(rd[2]-va[2])*_c;
	}

	void _APICALL _V4DScaleModDEF(double * _a,double * _b,double _c)
	{
		double rd[4];
		rd[0]=*_a;
		rd[1]=*(_a+1);
		rd[2]=*(_a+2);
		rd[3]=*(_a+3);
		double invc=1.0/_c;
		rd[0]*=invc;
		rd[1]*=invc;
		rd[2]*=invc;
		rd[3]*=invc;
		_int32 va[4];
		_V4DTTo4IDEF(rd,va);
		_b[0]=(rd[0]-va[0])*_c;
		_b[1]=(rd[1]-va[1])*_c;
		_b[2]=(rd[2]-va[2])*_c;
		_b[3]=(rd[3]-va[3])*_c;
	}

	// ************** vector dot product default function *******************

	float _APICALL _V2FDotDEF(float * _a,float * _b) {
		return _a[0]*_b[0]+_a[1]*_b[1];
	}

	float _APICALL _V3FDotDEF(float * _a,float * _b) {
		return _a[0]*_b[0]+_a[1]*_b[1]+_a[2]*_b[2];
	}

	float _APICALL _V4FDotDEF(float * _a,float * _b) {
		return _a[0]*_b[0]+_a[1]*_b[1]+_a[2]*_b[2]+_a[3]*_b[3];
	}

	double _APICALL _V2DDotDEF(double * _a,double * _b) {
		return _a[0]*_b[0]+_a[1]*_b[1];
	}

	double _APICALL _V3DDotDEF(double * _a,double * _b) {
		return _a[0]*_b[0]+_a[1]*_b[1]+_a[2]*_b[2];
	}

	double _APICALL _V4DDotDEF(double * _a,double * _b) {
		return _a[0]*_b[0]+_a[1]*_b[1]+_a[2]*_b[2]+_a[3]*_b[3];
	}

	float _FASTCALL _V2FDotDEF_CPP(float * _a,float * _b) {
		return _a[0]*_b[0]+_a[1]*_b[1];
	}

	float _FASTCALL _V3FDotDEF_CPP(float * _a,float * _b) {
		return _a[0]*_b[0]+_a[1]*_b[1]+_a[2]*_b[2];
	}

	float _FASTCALL _V4FDotDEF_CPP(float * _a,float * _b) {
		return _a[0]*_b[0]+_a[1]*_b[1]+_a[2]*_b[2]+_a[3]*_b[3];
	}

	double _FASTCALL _V2DDotDEF_CPP(double * _a,double * _b) {
		return _a[0]*_b[0]+_a[1]*_b[1];
	}

	double _FASTCALL _V3DDotDEF_CPP(double * _a,double * _b) {
		return _a[0]*_b[0]+_a[1]*_b[1]+_a[2]*_b[2];
	}

	double _FASTCALL _V4DDotDEF_CPP(double * _a,double * _b) {
		return _a[0]*_b[0]+_a[1]*_b[1]+_a[2]*_b[2]+_a[3]*_b[3];
	}

	// ************** vector Length2 default function *******************

	_int32 _APICALL _V2ILength2DEF(_int32 *_a)
	{
		return _a[0]*_a[0]+_a[1]*_a[1];
	}

	float _APICALL _V2FLength2DEF(float * _a) {
		return _a[0]*_a[0]+_a[1]*_a[1];
	}

	float _APICALL _V3FLength2DEF(float * _a) {
		return _a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2];
	}

	float _APICALL _V4FLength2DEF(float * _a) {
		return _a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2]+_a[3]*_a[3];
	}

	_int64 _APICALL _V2LLength2DEF(_int64 *_a)
	{
		return _a[0]*_a[0]+_a[1]*_a[1];
	}

	double _APICALL _V2DLength2DEF(double * _a) {
		return _a[0]*_a[0]+_a[1]*_a[1];
	}

	double _APICALL _V3DLength2DEF(double * _a) {
		return _a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2];
	}

	double _APICALL _V4DLength2DEF(double * _a) {
		return _a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2]+_a[3]*_a[3];
	}

	float _FASTCALL _V2FLength2DEF_CPP(float * _a) {
		return _a[0]*_a[0]+_a[1]*_a[1];
	}

	float _FASTCALL _V3FLength2DEF_CPP(float * _a) {
		return _a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2];
	}

	float _FASTCALL _V4FLength2DEF_CPP(float * _a) {
		return _a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2]+_a[3]*_a[3];
	}

	double _FASTCALL _V2DLength2DEF_CPP(double * _a) {
		return _a[0]*_a[0]+_a[1]*_a[1];
	}

	double _FASTCALL _V3DLength2DEF_CPP(double * _a) {
		return _a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2];
	}

	double _FASTCALL _V4DLength2DEF_CPP(double * _a) {
		return _a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2]+_a[3]*_a[3];
	}

	// ************** normal default function *******************

	void _APICALL _V2INormalMul2NDEF(_int32 *_a,_int32 *_b,_int32 _c)
	{
		double b=0;
		_int32* mexp=(_int32*)&b;
		mexp[1]=(((_c+0x3ff) &0x7FF)<<20);
		double r1=_a[0];
		double r2=_a[1];
		double c=b/_DsqrtDEF(r1*r1+r2*r2);
		_b[0] = _FTruncDEF(r1*c);
		_b[1] = _FTruncDEF(r2*c);
	}

	void _APICALL _V3INormalMul2NDEF(_int32 *_a,_int32 *_b,_int32 _c)
	{
		double b=0;
		_int32* mexp=(_int32*)&b;
		mexp[1]=(((_c+0x3ff) &0x7FF)<<20);
		double r1=_a[0];
		double r2=_a[1];
		double r3=_a[2];
		double c=b/_DsqrtDEF(r1*r1+r2*r2+r3*r3);
		_b[0] = _FTruncDEF(r1*c);
		_b[1] = _FTruncDEF(r2*c);
		_b[2] = _FTruncDEF(r3*c);
	}

	void _APICALL _V4INormalMul2NDEF(_int32 *_a,_int32 *_b,_int32 _c)
	{
		double b=0;
		_int32* mexp=(_int32*)&b;
		mexp[1]=(((_c+0x3ff) &0x7FF)<<20);
		double r1=_a[0];
		double r2=_a[1];
		double r3=_a[2];
		double r4=_a[3];
		double c=b/_DsqrtDEF(r1*r1+r2*r2+r3*r3+r4*r4);
		_b[0] = _FTruncDEF(r1*c);
		_b[1] = _FTruncDEF(r2*c);
		_b[2] = _FTruncDEF(r3*c);
		_b[3] = _FTruncDEF(r4*c);
	}

	// ************** normal default function *******************

	void _APICALL _V2FNormalDEF(float * _a,float * _b) {
		double c=1.0/_DsqrtDEF(_a[0]*_a[0]+_a[1]*_a[1]);
		float r[2];
		r[0]=(float)(_a[0]*c);
		r[1]=(float)(_a[1]*c);
		_b[0]=r[0];
		_b[1]=r[1];
	}

	void _APICALL _V3FNormalDEF(float * _a,float * _b) {
		double c=1.0/_DsqrtDEF(_a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2]);
		float r[3];
		r[0]=(float)(_a[0]*c);
		r[1]=(float)(_a[1]*c);
		r[2]=(float)(_a[2]*c);
		_b[0]=r[0];
		_b[1]=r[1];
		_b[2]=r[2];
	}

	void _APICALL _V4FNormalDEF(float * _a,float * _b) {
		double c=1.0/_DsqrtDEF(_a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2]+_a[3]*_a[3]);
		float r[4];
		r[0]=(float)(_a[0]*c);
		r[1]=(float)(_a[1]*c);
		r[2]=(float)(_a[2]*c);
		r[3]=(float)(_a[3]*c);
		_b[0]=r[0];
		_b[1]=r[1];
		_b[2]=r[2];
		_b[3]=r[3];
	}

	void _APICALL _V2DNormalDEF(double * _a,double * _b) {
		double c=1.0/_DsqrtDEF(_a[0]*_a[0]+_a[1]*_a[1]);
		double r[2];
		r[0]=(double)(_a[0]*c);
		r[1]=(double)(_a[1]*c);
		_b[0]=r[0];
		_b[1]=r[1];
	}

	void _APICALL _V3DNormalDEF(double * _a,double * _b) {
		double c=1.0/_DsqrtDEF(_a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2]);
		double r[3];
		r[0]=(double)(_a[0]*c);
		r[1]=(double)(_a[1]*c);
		r[2]=(double)(_a[2]*c);
		_b[0]=r[0];
		_b[1]=r[1];
		_b[2]=r[2];
	}

	void _APICALL _V4DNormalDEF(double * _a,double * _b) {
		double c=1.0/_DsqrtDEF(_a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2]+_a[3]*_a[3]);
		double r[4];
		r[0]=(double)(_a[0]*c);
		r[1]=(double)(_a[1]*c);
		r[2]=(double)(_a[2]*c);
		r[3]=(double)(_a[3]*c);
		_b[0]=r[0];
		_b[1]=r[1];
		_b[2]=r[2];
		_b[3]=r[3];
	}

	void _FASTCALL _V2FNormalDEF_CPP(float * _a,float * _b) {
		double c=1.0/_FsqrtDEF(_a[0]*_a[0]+_a[1]*_a[1]);
		_b[0]=(float)(_a[0]*c);
		_b[1]=(float)(_a[1]*c);
	}

	void _FASTCALL _V3FNormalDEF_CPP(float * _a,float * _b) {
		double c=1.0/_FsqrtDEF(_a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2]);
		float r[3];
		r[0]=(float)(_a[0]*c);
		r[1]=(float)(_a[1]*c);
		r[2]=(float)(_a[2]*c);
		_b[0]=r[0];
		_b[1]=r[1];
		_b[2]=r[2];
	}

	void _FASTCALL _V4FNormalDEF_CPP(float * _a,float * _b) {
		double c=1.0/_FsqrtDEF(_a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2]+_a[3]*_a[3]);
		float r[4];
		r[0]=(float)(_a[0]*c);
		r[1]=(float)(_a[1]*c);
		r[2]=(float)(_a[2]*c);
		r[3]=(float)(_a[3]*c);
		_b[0]=r[0];
		_b[1]=r[1];
		_b[2]=r[2];
		_b[3]=r[3];
	}

	void _FASTCALL _V2DNormalDEF_CPP(double * _a,double * _b) {
		double c=1.0/_DsqrtDEF(_a[0]*_a[0]+_a[1]*_a[1]);
		double r[2];
		r[0]=(double)(_a[0]*c);
		r[1]=(double)(_a[1]*c);
		_b[0]=r[0];
		_b[1]=r[1];
	}

	void _FASTCALL _V3DNormalDEF_CPP(double * _a,double * _b) {
		double c=1.0/_DsqrtDEF(_a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2]);
		double r[3];
		r[0]=(double)(_a[0]*c);
		r[1]=(double)(_a[1]*c);
		r[2]=(double)(_a[2]*c);
		_b[0]=r[0];
		_b[1]=r[1];
		_b[2]=r[2];
	}

	void _FASTCALL _V4DNormalDEF_CPP(double * _a,double * _b) {
		double c=1.0/_DsqrtDEF(_a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2]+_a[3]*_a[3]);
		double r[4];
		r[0]=(double)(_a[0]*c);
		r[1]=(double)(_a[1]*c);
		r[2]=(double)(_a[2]*c);
		r[3]=(double)(_a[3]*c);
		_b[0]=r[0];
		_b[1]=r[1];
		_b[2]=r[2];
		_b[3]=r[3];
	}

	// ************** fast normal default function *******************

	void _APICALL _V2FFastNormalDEF(float * _a,float * _b) {
		conv4b c;
		conv4b al;
		c.valfloat=_a[0]*_a[0]+_a[1]*_a[1];
		al.valuint=c.valint;
		al.valuint=0x5f3504f3-(al.valuint>>1);
		float g=al.valfloat;
		c.valfloat=g*(1.5f-0.5f*c.valfloat*g*g);
		_b[0]=(float)(_a[0]*c.valfloat);
		_b[1]=(float)(_a[1]*c.valfloat);
	}

	void _APICALL _V3FFastNormalDEF(float * _a,float * _b) {
		conv4b c;
		conv4b al;
		c.valfloat=_a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2];
		al.valuint=c.valint;
		al.valuint=0x5f3504f3-(al.valuint>>1);
		float g=al.valfloat;
		c.valfloat=g*(1.5f-0.5f*c.valfloat*g*g);
		_b[0]=(float)(_a[0]*c.valfloat);
		_b[1]=(float)(_a[1]*c.valfloat);
		_b[2]=(float)(_a[2]*c.valfloat);
	}

	void _APICALL _V4FFastNormalDEF(float * _a,float * _b) {
		conv4b c;
		conv4b al;
		c.valfloat=_a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2]+_a[3]*_a[3];
		al.valuint=c.valint;
		al.valuint=0x5f3504f3-(al.valuint>>1);
		float g=al.valfloat;
		c.valfloat=g*(1.5f-0.5f*c.valfloat*g*g);
		float r[4];
		r[0]=(float)(_a[0]*c.valfloat);
		r[1]=(float)(_a[1]*c.valfloat);
		r[2]=(float)(_a[2]*c.valfloat);
		r[3]=(float)(_a[3]*c.valfloat);
		_b[0]=r[0];
		_b[1]=r[1];
		_b[2]=r[2];
		_b[3]=r[3];
	}

	void _APICALL _V2DFastNormalDEF(double * _a,double * _b) {
		conv4b c;
		conv4b al;
		c.valfloat=(float)(_a[0]*_a[0]+_a[1]*_a[1]);
		al.valuint=c.valint;
		al.valuint=0x5f3504f3-(al.valuint>>1);
		float g=al.valfloat;
		c.valfloat=g*(1.5f-0.5f*c.valfloat*g*g);
		_b[0]=_a[0]*c.valfloat;
		_b[1]=_a[1]*c.valfloat;
	}

	void _APICALL _V3DFastNormalDEF(double * _a,double * _b) {
		conv4b c;
		conv4b al;
		c.valfloat=(float)(_a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2]);
		al.valuint=c.valint;
		al.valuint=0x5f3504f3-(al.valuint>>1);
		float g=al.valfloat;
		c.valfloat=g*(1.5f-0.5f*c.valfloat*g*g);
		_b[0]=_a[0]*c.valfloat;
		_b[1]=_a[1]*c.valfloat;
		_b[2]=_a[2]*c.valfloat;
	}

	void _APICALL _V4DFastNormalDEF(double * _a,double * _b) {
		conv4b c;
		conv4b al;
		double r1=_a[0];
		double r2=_a[1];
		double r3=_a[2];
		double r4=_a[3];
		c.valfloat=(float)(r1*r1+r2*r2+r3*r3+r4*r4);
		al.valuint=c.valint;
		al.valuint=0x5f3504f3-(al.valuint>>1);
		float g=al.valfloat;
		c.valfloat=g*(1.5f-0.5f*c.valfloat*g*g);
		_b[0]=r1*c.valfloat;
		_b[1]=r2*c.valfloat;
		_b[2]=r3*c.valfloat;
		_b[3]=r4*c.valfloat;
	}

	// ************** CrossProduct default function *******************

	_int32 _APICALL _V2ICrossDEF(_int32 * _a,_int32 * _b) {
		return _a[0]*_b[1]-_a[1]*_b[0];
	}

	float _APICALL _V2FCrossDEF(float * _a,float * _b) {
		return _a[0]*_b[1]-_a[1]*_b[0];
	}

	void _APICALL _V3FCrossDEF(float * _a,float * _b,float * _c) {
		float r1=_a[0];
		float r2=_a[1];
		float r3=_a[2];
		float t1=_b[0];
		float t2=_b[1];
		float t3=_b[2];
		_c[0]=r2*t3-r3*t2;
		_c[1]=r3*t1-r1*t3;
		_c[2]=r1*t2-r2*t1;
	}

	_int64 _APICALL _V2LCrossDEF(_int64 * _a,_int64 * _b) {
		return _a[0]*_b[1]-_a[1]*_b[0];
	}

	double _APICALL _V2DCrossDEF(double * _a,double * _b) {
		return _a[0]*_b[1]-_a[1]*_b[0];
	}

	void _APICALL _V3DCrossDEF(double * _a,double * _b,double * _c) {
		double r1=_a[0];
		double r2=_a[1];
		double r3=_a[2];
		double t1=_b[0];
		double t2=_b[1];
		double t3=_b[2];
		_c[0]=r2*t3-r3*t2;
		_c[1]=r3*t1-r1*t3;
		_c[2]=r1*t2-r2*t1;
	}

	_int32 _FASTCALL _V2ICrossDEF_CPP(_int32 * _a,_int32 * _b) {
		return _a[0]*_b[1]-_a[1]*_b[0];
	}

	float _FASTCALL _V2FCrossDEF_CPP(float * _a,float * _b) {
		return _a[0]*_b[1]-_a[1]*_b[0];
	}

	void _FASTCALL _V3FCrossDEF_CPP(float * _a,float * _b,float * _c) {
		_c[0]=_a[1]*_b[2]-_a[2]*_b[1];
		_c[1]=_a[2]*_b[0]-_a[0]*_b[2];
		_c[2]=_a[0]*_b[1]-_a[1]*_b[0];
	}

	_int64 _FASTCALL _V2LCrossDEF_CPP(_int64 * _a,_int64 * _b) {
		return _a[0]*_b[1]-_a[1]*_b[0];
	}

	double _FASTCALL _V2DCrossDEF_CPP(double * _a,double * _b) {
		return _a[0]*_b[1]-_a[1]*_b[0];
	}

	void _FASTCALL _V3DCrossDEF_CPP(double * _a,double * _b,double * _c) {
		_c[0]=_a[1]*_b[2]-_a[2]*_b[1];
		_c[1]=_a[2]*_b[0]-_a[0]*_b[2];
		_c[2]=_a[0]*_b[1]-_a[1]*_b[0];
	}

	// ************** Lerp default function *******************

	void _APICALL _V2FLerpDEF(float * _a,float * _b,float * _c,float _d)
	{
		float r1=_a[0];
		float r2=_a[1];
		float t1=_b[0];
		float t2=_b[1];
		_c[0]=(t1-r1)*_d+r1;
		_c[1]=(t2-r2)*_d+r2;
	}

	void _APICALL _V3FLerpDEF(float * _a,float * _b,float * _c,float _d)
	{
		float r1=_a[0];
		float r2=_a[1];
		float r3=_a[2];
		float t1=_b[0];
		float t2=_b[1];
		float t3=_b[2];
		_c[0]=(t1-r1)*_d+r1;
		_c[1]=(t2-r2)*_d+r2;
		_c[2]=(t3-r3)*_d+r3;
	}

	void _APICALL _V4FLerpDEF(float * _a,float * _b,float * _c,float _d)
	{
		float r1=_a[0];
		float r2=_a[1];
		float r3=_a[2];
		float r4=_a[3];
		float t1=_b[0];
		float t2=_b[1];
		float t3=_b[2];
		float t4=_b[3];
		_c[0]=(t1-r1)*_d+r1;
		_c[1]=(t2-r2)*_d+r2;
		_c[2]=(t3-r3)*_d+r3;
		_c[3]=(t4-r4)*_d+r4;
	}

	void _APICALL _V2DLerpDEF(double * _a,double * _b,double * _c,double _d)
	{
		double r1=_a[0];
		double r2=_a[1];
		double t1=_b[0];
		double t2=_b[1];
		_c[0]=(t1-r1)*_d+r1;
		_c[1]=(t2-r2)*_d+r2;
	}

	void _APICALL _V3DLerpDEF(double * _a,double * _b,double * _c,double _d)
	{
		double r1=_a[0];
		double r2=_a[1];
		double r3=_a[2];
		double t1=_b[0];
		double t2=_b[1];
		double t3=_b[2];
		_c[0]=(t1-r1)*_d+r1;
		_c[1]=(t2-r2)*_d+r2;
		_c[2]=(t3-r3)*_d+r3;
	}

	void _APICALL _V4DLerpDEF(double * _a,double * _b,double * _c,double _d)
	{
		double r1=_a[0];
		double r2=_a[1];
		double r3=_a[2];
		double r4=_a[3];
		double t1=_b[0];
		double t2=_b[1];
		double t3=_b[2];
		double t4=_b[3];
		_c[0]=(t1-r1)*_d+r1;
		_c[1]=(t2-r2)*_d+r2;
		_c[2]=(t3-r3)*_d+r3;
		_c[3]=(t4-r4)*_d+r4;
	}

	// ************** vector combine *******************

	void _APICALL _V2FCombineDEF(float *a,float *b,float *c,float d,float e)
	{
		float r1=a[0];
		float r2=a[1];
		float t1=b[0];
		float t2=b[1];
		c[0]=r1*d+t1*e;
		c[1]=r2*d+t2*e;
	}

	void _APICALL _V3FCombineDEF(float *a,float *b,float *c,float d,float e)
	{
		float r1=a[0];
		float r2=a[1];
		float r3=a[2];
		float t1=b[0];
		float t2=b[1];
		float t3=b[2];
		c[0]=r1*d+t1*e;
		c[1]=r2*d+t2*e;
		c[2]=r3*d+t3*e;
	}

	void _APICALL _V4FCombineDEF(float *a,float *b,float *c,float d,float e)
	{
		float r1=a[0];
		float r2=a[1];
		float r3=a[2];
		float r4=a[3];
		float t1=b[0];
		float t2=b[1];
		float t3=b[2];
		float t4=b[3];
		c[0]=r1*d+t1*e;
		c[1]=r2*d+t2*e;
		c[2]=r3*d+t3*e;
		c[3]=r4*d+t4*e;
	}

	void _APICALL _V2DCombineDEF(double *a,double *b,double *c,double d,double e)
	{
		double r1=a[0];
		double r2=a[1];
		double t1=b[0];
		double t2=b[1];
		c[0]=r1*d+t1*e;
		c[1]=r2*d+t2*e;
	}

	void _APICALL _V3DCombineDEF(double *a,double *b,double *c,double d,double e)
	{
		double r1=a[0];
		double r2=a[1];
		double r3=a[2];
		double t1=b[0];
		double t2=b[1];
		double t3=b[2];
		c[0]=r1*d+t1*e;
		c[1]=r2*d+t2*e;
		c[2]=r3*d+t3*e;
	}

	void _APICALL _V4DCombineDEF(double *a,double *b,double *c,double d,double e)
	{
		double r1=a[0];
		double r2=a[1];
		double r3=a[2];
		double r4=a[3];
		double t1=b[0];
		double t2=b[1];
		double t3=b[2];
		double t4=b[3];
		c[0]=r1*d+t1*e;
		c[1]=r2*d+t2*e;
		c[2]=r3*d+t3*e;
		c[3]=r4*d+t4*e;
	}

	// ************** vector quad distance from line *******************

	_int32 _APICALL _V2IQDFLDEF(_int32 * _a,_int32 * _b,_int32 * _c)
	{
		return (_a[0]-_b[0])*(_c[1]-_b[1])-(_a[1]-_b[1])*(_c[0]-_b[0]);
	}

	float _APICALL _V2FQDFLDEF(float * _a,float * _b,float * _c)
	{
		return (_a[0]-_b[0])*(_c[1]-_b[1])-(_a[1]-_b[1])*(_c[0]-_b[0]);
	}

/*	float _STDCALL _V3FQDFL(float * _a,float * _b,float * _c)
	{
		_d[0]=_a[0]-_b[0];
		_d[1]=_a[1]-_b[1];
		_d[2]=_a[2]-_b[2];
		_f[0]=_c[0]-_b[0];
		_f[1]=_c[1]-_b[1];
		_f[2]=_c[2]-_b[2];

		_e[0]=_d[1]*_f[2]-_d[2]*_f[1];
		_e[1]=_d[2]*_f[0]-_d[0]*_f[2];
		_e[2]=_d[0]*_f[1]-_d[1]*_f[0];

		_g[0]=_d[1]*(_d[0]*_f[1]-_d[1]*_f[0])-_d[2]*(_d[2]*_f[0]-_d[0]*_f[2]);
		_g[1]=_d[2]*(_d[1]*_f[2]-_d[2]*_f[1])-_d[0]*(_d[0]*_f[1]-_d[1]*_f[0]);
		_g[2]=_d[0]*(_d[2]*_f[0]-_d[0]*_f[2])-_d[1]*(_d[1]*_f[2]-_d[2]*_f[1]);

		_g[0]=(_d[0]*(_d[1]*_f[1]+_d[2]*_f[2])-_f[0]*(_d[1]*_d[1]+_d[2]*_d[2]))*_f[0];
		_g[1]=(_d[1]*(_d[2]*_f[2]+_d[0]*_f[0])-_f[1]*(_d[2]*_d[2]+_d[0]*_d[0]))*_f[1];
		_g[2]=(_d[2]*(_d[0]*_f[0]+_d[1]*_f[1])-_f[2]*(_d[0]*_d[0]+_d[1]*_d[1]))*_f[2];


		d*f*(d1*f1+d2*f2)-f*f*(d1*d1+d2*d2)

		(d*f*d1*f1+d1*f1*d*f)-(f*f*d1*d1+f1*f1*d*d)

		(_a[0]-_b[0])*(_c[1]-_b[1])-(_a[1]-_b[1])*(_c[0]-_b[0]);
		_a[1];
		_a[0]*_c[1]-_a[0]*_b[1]-_a[1]*_c[0]+_a[1]*_b[0]+_b[1]*_c[0]-_b[0]*_c[1];
		-_b[1];
		_a[0]*_c[1]-_a[0]*_b[1]-_a[1]*_c[0]+_a[1]*_b[0]+_b[1]*_c[0]-_b[0]*_c[1];


		_a[1]*_a[1]*(_b[0]-_c[0])+_a[1]*_a[0]*(_c[1]-_b[1])
													+2*_a[1]*_b[1]*_c[0]-(_a[1]*_b[0]+_a[0]*_b[1])*_c[1]
		+_b[1]*_b[1]*(_a[0]-_c[0])+_b[1]*_b[0]*(_c[1]-_a[1])



		_g[0]=(_a[1]-_b[1])*((_a[0]-_b[0])*(_c[1]-_b[1])-(_a[1]-_b[1])*(_c[0]-_b[0]))-(_a[2]-_b[2])*((_a[2]-_b[2])*(_c[0]-_b[0])-(_a[0]-_b[0])*(_c[2]-_b[2]));
		_g[1]=(_a[2]-_b[2])*((_a[1]-_b[1])*(_c[2]-_b[2])-(_a[2]-_b[2])*(_c[1]-_b[1]))-(_a[0]-_b[0])*((_a[0]-_b[0])*(_c[1]-_b[1])-(_a[1]-_b[1])*(_c[0]-_b[0]));
		_g[2]=(_a[0]-_b[0])*((_a[2]-_b[2])*(_c[0]-_b[0])-(_a[0]-_b[0])*(_c[2]-_b[2]))-(_a[1]-_b[1])*((_a[1]-_b[1])*(_c[2]-_b[2])-(_a[2]-_b[2])*(_c[1]-_b[1]));

		return _f[0]*_g[0]+_f[1]*_g[1]+_f[2]*_g[2];
	}*/

	_int64 _APICALL _V2LQDFLDEF(_int64 * _a,_int64 * _b,_int64 * _c)
	{
		return (_a[0]-_b[0])*(_c[1]-_b[1])-(_a[1]-_b[1])*(_c[0]-_b[0]);
	}

	double _APICALL _V2DQDFLDEF(double * _a,double * _b,double * _c)
	{
		return (_a[0]-_b[0])*(_c[1]-_b[1])-(_a[1]-_b[1])*(_c[0]-_b[0]);
	}

	// ************** reflect default function *******************

	void _APICALL _V2FReflectDEF(float * _a,float * _b,float * _c)
	{
		float d=-((_a[0]*_b[0])-(_a[1]*_b[1]))*2;
		float r1=_b[0]*d+_a[0];
		float r2=_b[1]*d+_a[1];
		_c[0]=r1;
		_c[1]=r2;
	}

	void _APICALL _V3FReflectDEF(float * _a,float * _b,float * _c)
	{
		float d=-((_a[0]*_b[0])-(_a[1]*_b[1])-(_a[2]*_b[2]))*2;
		float r1=_b[0]*d+_a[0];
		float r2=_b[1]*d+_a[1];
		float r3=_b[2]*d+_a[2];
		_c[0]=r1;
		_c[1]=r2;
		_c[2]=r3;
	}

	void _APICALL _V4FReflectDEF(float * _a,float * _b,float * _c)
	{
		float d=-((_a[0]*_b[0])-(_a[1]*_b[1])-(_a[2]*_b[2])-(_a[3]*_b[3]))*2;
		float r1=_b[0]*d+_a[0];
		float r2=_b[1]*d+_a[1];
		float r3=_b[2]*d+_a[2];
		float r4=_b[3]*d+_a[3];
		_c[0]=r1;
		_c[1]=r2;
		_c[2]=r3;
		_c[3]=r4;
	}

	void _APICALL _V2DReflectDEF(double * _a,double * _b,double * _c)
	{
		double d=-((_a[0]*_b[0])-(_a[1]*_b[1]))*2;
		double r1=_b[0]*d+_a[0];
		double r2=_b[1]*d+_a[1];
		_c[0]=r1;
		_c[1]=r2;
	}

	void _APICALL _V3DReflectDEF(double * _a,double * _b,double * _c)
	{
		double d=-((_a[0]*_b[0])-(_a[1]*_b[1])-(_a[2]*_b[2]))*2;
		double r1=_b[0]*d+_a[0];
		double r2=_b[1]*d+_a[1];
		double r3=_b[2]*d+_a[2];
		_c[0]=r1;
		_c[1]=r2;
		_c[2]=r3;
	}

	void _APICALL _V4DReflectDEF(double * _a,double * _b,double * _c)
	{
		double d=-((_a[0]*_b[0])-(_a[1]*_b[1])-(_a[2]*_b[2])-(_a[3]*_b[3]))*2;
		double r1=_b[0]*d+_a[0];
		double r2=_b[1]*d+_a[1];
		double r3=_b[2]*d+_a[2];
		double r4=_b[3]*d+_a[3];
		_c[0]=r1;
		_c[1]=r2;
		_c[2]=r3;
		_c[3]=r4;
	}

	// ************** angle default function *******************

	float _APICALL _V2FAngleDEF(float * _a,float * _b)
	{
		float r3=_a[0]*_b[1]-_a[1]*_b[0];
		return _FArcTgDEF(_a[0]*_b[0]+_a[1]*_b[1],r3);
	}

	float _APICALL _V3FAngleDEF(float * _a,float * _b)
	{
		float r1=_a[1]*_b[2]-_a[2]*_b[1];
		float r2=_a[2]*_b[0]-_a[0]*_b[2];
		float r3=_a[0]*_b[1]-_a[1]*_b[0];
		return _FArcTgDEF(_a[0]*_b[0]+_a[1]*_b[1]+_a[2]*_b[2],_FsqrtDEF(r1*r1+r2*r2+r3*r3));
	}

	double _APICALL _V2DAngleDEF(double * _a,double * _b)
	{
		double r3=_a[0]*_b[1]-_a[1]*_b[0];
		return _DArcTgDEF(_a[0]*_b[0]+_a[1]*_b[1],r3);
	}

	double _APICALL _V3DAngleDEF(double * _a,double * _b)
	{
		double r1=_a[1]*_b[2]-_a[2]*_b[1];
		double r2=_a[2]*_b[0]-_a[0]*_b[2];
		double r3=_a[0]*_b[1]-_a[1]*_b[0];
		return _DArcTgDEF(_a[0]*_b[0]+_a[1]*_b[1]+_a[2]*_b[2],_DsqrtDEF(r1*r1+r2*r2+r3*r3));
	}

	// ************** distance plane from ray default function *******************

	float _APICALL _V3FDPFRDEF(float * _a,float * _b,float * _c,float * _d)
	{
		float d=_d[0]*_b[0]+_d[1]*_b[1]+_d[2]*_b[2];
		if (d==0) return 0;
		return ((_a[0]-_c[0])*_b[0]+(_a[1]-_c[1])*_b[1]+(_a[2]-_c[2])*_b[2])/d;
	} // _c+_d*rez

	double _APICALL _V3DDPFRDEF(double * _a,double * _b,double * _c,double * _d)
	{
		double d=_d[0]*_b[0]+_d[1]*_b[1]+_d[2]*_b[2];
		if (d==0) return 0;
		return ((_a[0]-_c[0])*_b[0]+(_a[1]-_c[1])*_b[1]+(_a[2]-_c[2])*_b[2])/d;
	} // _c+_d*rez

	// ************** triangle normal default function *******************

	void _APICALL _V3FTriNormDEF(float * _a,float * _b,float * _c,float * _d)
	{
		float a0=(_b[0]-_a[0]);
		float a1=(_b[1]-_a[1]);
		float a2=(_b[2]-_a[2]);
		float b0=(_c[0]-_a[0]);
		float b1=(_c[1]-_a[1]);
		float b2=(_c[2]-_a[2]);

		float r0=(a1)*(b2)-(a2)*(b1);
		float r1=(a2)*(b0)-(a0)*(b2);
		float r2=(a0)*(b1)-(a1)*(b0);

		double c=1.0/_DsqrtDEF(r0*r0+r1*r1+r2*r2);
		_d[0]=(float)(r0*c);
		_d[1]=(float)(r1*c);
		_d[2]=(float)(r2*c);
	}

	void _APICALL _V3DTriNormDEF(double * _a,double * _b,double * _c,double * _d)
	{
		double a0=(_b[0]-_a[0]);
		double a1=(_b[1]-_a[1]);
		double a2=(_b[2]-_a[2]);
		double b0=(_c[0]-_a[0]);
		double b1=(_c[1]-_a[1]);
		double b2=(_c[2]-_a[2]);

		double r0=(a1)*(b2)-(a2)*(b1);
		double r1=(a2)*(b0)-(a0)*(b2);
		double r2=(a0)*(b1)-(a1)*(b0);

		double c=1.0/_DsqrtDEF(r0*r0+r1*r1+r2*r2);
		_d[0]=r0*c;
		_d[1]=r1*c;
		_d[2]=r2*c;
	}

	// ************** add triangle normal default function *******************

	void _APICALL _V3FAddTriNormDEF(float * _a,float * _b,float * _c,_int32 off)
	{
		float a0=(_b[0]-_a[0]);
		float a1=(_b[1]-_a[1]);
		float a2=(_b[2]-_a[2]);
		float b0=(_c[0]-_a[0]);
		float b1=(_c[1]-_a[1]);
		float b2=(_c[2]-_a[2]);

		float r0=(a1)*(b2)-(a2)*(b1);
		float r1=(a2)*(b0)-(a0)*(b2);
		float r2=(a0)*(b1)-(a1)*(b0);

		double c=1.0/_DsqrtDEF(r0*r0+r1*r1+r2*r2);
		float *an=(float *)((char*)_a+off);
		float *bn=(float *)((char*)_b+off);
		float *cn=(float *)((char*)_c+off);
		r0=(float)(r0*c);
		r1=(float)(r1*c);
		r2=(float)(r2*c);
		a0=an[0];
		a1=an[1];
		a2=an[2];
		b0=bn[0];
		b1=bn[1];
		b2=bn[2];
		an[0]=a0+r0;
		an[1]=a1+r1;
		an[2]=a2+r2;
		bn[0]=b0+r0;
		bn[1]=b1+r1;
		bn[2]=b2+r2;
		r0=r0+cn[0];
		r1=r1+cn[1];
		r2=r2+cn[2];
		cn[0]=r0;
		cn[1]=r1;
		cn[2]=r2;
	}

	void _APICALL _V3FAdd3DTriNormDEF(double * _a,double * _b,double * _c,_int32 off)
	{
		double a0=(_b[0]-_a[0]);
		double a1=(_b[1]-_a[1]);
		double a2=(_b[2]-_a[2]);
		double b0=(_c[0]-_a[0]);
		double b1=(_c[1]-_a[1]);
		double b2=(_c[2]-_a[2]);

		double r0=(a1)*(b2)-(a2)*(b1);
		double r1=(a2)*(b0)-(a0)*(b2);
		double r2=(a0)*(b1)-(a1)*(b0);

		double c=1.0/_DsqrtDEF(r0*r0+r1*r1+r2*r2);
		float *an=(float *)((char*)_a+off);
		float *bn=(float *)((char*)_b+off);
		float *cn=(float *)((char*)_c+off);
		r0=(r0*c);
		r1=(r1*c);
		r2=(r2*c);
		an[0]+=(float)r0;
		an[1]+=(float)r1;
		an[2]+=(float)r2;
		bn[0]+=(float)r0;
		bn[1]+=(float)r1;
		bn[2]+=(float)r2;
		cn[0]+=(float)r0;
		cn[1]+=(float)r1;
		cn[2]+=(float)r2;
	}

	void _APICALL _V3DAddTriNormDEF(double * _a,double * _b,double * _c,_int32 off)
	{
		double a0=(_b[0]-_a[0]);
		double a1=(_b[1]-_a[1]);
		double a2=(_b[2]-_a[2]);
		double b0=(_c[0]-_a[0]);
		double b1=(_c[1]-_a[1]);
		double b2=(_c[2]-_a[2]);

		double r0=(a1)*(b2)-(a2)*(b1);
		double r1=(a2)*(b0)-(a0)*(b2);
		double r2=(a0)*(b1)-(a1)*(b0);

		double c=1.0/_DsqrtDEF(r0*r0+r1*r1+r2*r2);
		double *an=(double *)((char*)_a+off);
		double *bn=(double *)((char*)_b+off);
		double *cn=(double *)((char*)_c+off);
		r0=(r0*c);
		r1=(r1*c);
		r2=(r2*c);
		an[0]+=r0;
		an[1]+=r1;
		an[2]+=r2;
		bn[0]+=r0;
		bn[1]+=r1;
		bn[2]+=r2;
		cn[0]+=r0;
		cn[1]+=r1;
		cn[2]+=r2;
	}

	// ************** vector to quaternion default function *******************

	void _APICALL _V4FQuaternionDEF(float * _a,float * _b) {
		float sc[2];
		_FSinCosDEF((float)(_a[3]*0.5),sc,&sc[1]);
		float alen=_V3FLength2DEF(_a);
		if ((alen!=1) && (alen!=0)) {
			sc[1]=sc[1]/_FsqrtDEF(alen);
		}
		_V3FScaleDEF(_a,_b,sc[1]);
		_b[3]=sc[0];
	}

	void _APICALL _V4DQuaternionDEF(double * _a,double * _b) {
		double sc[2];
		_DSinCosDEF(_a[3]*0.5,sc,&sc[1]);
		double alen=_V3DLength2DEF(_a);
		if ((alen!=1) && (alen!=0)) {
			sc[1]=sc[1]/_DsqrtDEF(alen);
		}
		_V3DScaleDEF(_a,_b,sc[1]);
		_b[3]=sc[0];
	}

	void _FASTCALL _V4FQuaternionDEF_CPP(float * _a,float * _b) {
		float sc[2];
		_FSinCosDEF((float)(_a[3]*0.5),sc,&sc[1]);
		float alen=_V3FLength2DEF(_a);
		if ((alen!=1) && (alen!=0)) {
			sc[1]=sc[1]/_FsqrtDEF(alen);
		}
		_V3FScaleDEF(_a,_b,sc[1]);
		_b[3]=sc[0];
	}

	void _FASTCALL _V4DQuaternionDEF_CPP(double * _a,double * _b) {
		double sc[2];
		_DSinCosDEF(_a[3]*0.5,sc,&sc[1]);
		double alen=_V3DLength2DEF(_a);
		if ((alen!=1) && (alen!=0)) {
			sc[1]=sc[1]/_DsqrtDEF(alen);
		}
		_V3DScaleDEF(_a,_b,sc[1]);
		_b[3]=sc[0];
	}

	// ************** fast vector to quaternion default function *******************

	void _APICALL _V4FFastQuaternionDEF(float * _a,float * _b) {
		float sc[2];
		_FSinCosFASTDEF((float)(_a[3]*0.5),sc,&sc[1]);
		float alen=_V3FLength2DEF(_a);
		if ((alen!=1) && (alen!=0)) {
			sc[1]=sc[1]*_FFastInvSqrtDEF(alen);
		}
		_V3FScaleDEF(_a,_b,sc[1]);
		_b[3]=sc[0];
	}

	void _APICALL _V4DFastQuaternionDEF(double * _a,double * _b) {
		double sc[2];
		_DSinCosFASTDEF(_a[3]*0.5,sc,&sc[1]);
		double alen=_V3DLength2DEF(_a);
		if ((alen!=1) && (alen!=0)) {
			sc[1]=sc[1]*_DFastInvSqrtDEF(alen);
		}
		_V3DScaleDEF(_a,_b,sc[1]);
		_b[3]=sc[0];
	}

	// ************** vector transform default function *******************

	void _APICALL _V2ITransformDEF(_int32 *_a,void *_b,_int32 *_c) {
		float *_matrixa=(float *)_b;
		float r[2];
		r[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_matrixa[12];
		r[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_matrixa[13];
		_c[0] = _FTruncDEF(r[0]);
		_c[1] = _FTruncDEF(r[1]);
	}

	void _APICALL _V2FTransformDEF(float *_a,void *_b,float *_c) {
		float *_matrixa=(float *)_b;
		float r[2];
		r[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_matrixa[12];
		r[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_matrixa[13];
		_c[0]=r[0];
		_c[1]=r[1];
	}

	void _APICALL _V3FTransformDEF(float *_a,void *_b,float *_c) {
		float *_matrixa=(float *)_b;
		float r[3];
		r[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_a[2]*_matrixa[8]+_matrixa[12];
		r[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_a[2]*_matrixa[9]+_matrixa[13];
		r[2]=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_a[2]*_matrixa[10]+_matrixa[14];
		_c[0]=r[0];
		_c[1]=r[1];
		_c[2]=r[2];
	}

	void _APICALL _V4FTransformDEF(float *_a,void *_b,float *_c) {
		float *_matrixa=(float *)_b;
		float r[4];
		r[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_a[2]*_matrixa[8]+_a[3]*_matrixa[12];
		r[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_a[2]*_matrixa[9]+_a[3]*_matrixa[13];
		r[2]=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_a[2]*_matrixa[10]+_a[3]*_matrixa[14];
		r[3]=_a[0]*_matrixa[3]+_a[1]*_matrixa[7]+_a[2]*_matrixa[11]+_a[3]*_matrixa[15];
		_c[0]=r[0];
		_c[1]=r[1];
		_c[2]=r[2];
		_c[3]=r[3];
	}

	void _APICALL _V2DTransformDEF(double *_a,void *_b,double *_c) {
		double *_matrixa=(double *)_b;
		double r1=_a[0];
		double r2=_a[1];
		double r[2];
		r[0]=r1*_matrixa[0]+r2*_matrixa[4]+_matrixa[12];
		r[1]=r1*_matrixa[1]+r2*_matrixa[5]+_matrixa[13];
		_c[0]=r[0];
		_c[1]=r[1];
	}

	void _APICALL _V3DTransformDEF(double *_a,void *_b,double *_c) {
		double *_matrixa=(double *)_b;
		double r1=_a[0];
		double r2=_a[1];
		double r3=_a[2];
		double r[3];
		r[0]=r1*_matrixa[0]+r2*_matrixa[4]+r3*_matrixa[8]+_matrixa[12];
		r[1]=r1*_matrixa[1]+r2*_matrixa[5]+r3*_matrixa[9]+_matrixa[13];
		r[2]=r1*_matrixa[2]+r2*_matrixa[6]+r3*_matrixa[10]+_matrixa[14];
		_c[0]=r[0];
		_c[1]=r[1];
		_c[2]=r[2];
	}

	void _APICALL _V4DTransformDEF(double *_a,void *_b,double *_c) {
		double *_matrixa=(double *)_b;
		double r1=_a[0];
		double r2=_a[1];
		double r3=_a[2];
		double r4=_a[3];
		double r[4];
		r[0]=r1*_matrixa[0]+r2*_matrixa[4]+r3*_matrixa[8]+r4*_matrixa[12];
		r[1]=r1*_matrixa[1]+r2*_matrixa[5]+r3*_matrixa[9]+r4*_matrixa[13];
		r[2]=r1*_matrixa[2]+r2*_matrixa[6]+r3*_matrixa[10]+r4*_matrixa[14];
		r[3]=r1*_matrixa[3]+r2*_matrixa[7]+r3*_matrixa[11]+r4*_matrixa[15];
		_c[0]=r[0];
		_c[1]=r[1];
		_c[2]=r[2];
		_c[3]=r[3];
	}

	// ************** vector mul matrix default function *******************

	void _APICALL _V2FMMulDEF(float *_a,void *_b,float *_c) {
		float *_matrixa=(float *)_b;
		_c[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4];
		_c[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5];
	}

	void _APICALL _V3FMMulDEF(float *_a,void *_b,float *_c) {
		float *_matrixa=(float *)_b;
		_c[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_a[2]*_matrixa[8];
		_c[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_a[2]*_matrixa[9];
		_c[2]=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_a[2]*_matrixa[10];
	}

	void _APICALL _V2DMMulDEF(double *_a,void *_b,double *_c) {
		double *_matrixa=(double *)_b;
		_c[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4];
		_c[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5];
	}

	void _APICALL _V3DMMulDEF(double *_a,void *_b,double *_c) {
		double *_matrixa=(double *)_b;
		_c[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_a[2]*_matrixa[8];
		_c[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_a[2]*_matrixa[9];
		_c[2]=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_a[2]*_matrixa[10];
	}

	// ************** vector projection default function *******************

	_int32 _APICALL _V2FProjDEF(float *_a,void *_b,float *_c,float *_d,float *_e) {
		float *_matrixa=(float *)_b;
		float r[5];
		r[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_matrixa[12];
		r[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_matrixa[13];
		r[2]=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_matrixa[14];
		r[3]=_a[0]*_matrixa[3]+_a[1]*_matrixa[7]+_matrixa[15];
		r[4]=-r[3];
		_int32 flag=0;
		if (r[0]>r[3]) flag|=0x01; //right
		if (r[1]>r[3]) flag|=0x02; //down
		if (r[2]>r[3]) flag|=0x04;
		if (r[0]<r[4]) flag|=0x10; //left
		if (r[1]<r[4]) flag|=0x20; //up
		if (r[2]<r[4]) flag|=0x40;
		if ((r[3]!=0) && (r[3]!=1.0)) {
			r[3]=1.0f/r[3];
			r[0]=r[0]*r[3];
			r[1]=r[1]*r[3];
			r[2]=r[2]*r[3];
		}
		_e[0]=r[0]*_c[0]+_d[0];
		_e[1]=r[1]*_c[1]+_d[1];
		_e[2]=r[2]*_c[2]+_d[2];
		_e[3]=r[3];
		return flag;
	}

	_int32 _APICALL _V3FProjDEF(float *_a,void *_b,float *_c,float *_d,float *_e) {
		float *_matrixa=(float *)_b;
		float r[5];
		r[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_a[2]*_matrixa[8]+_matrixa[12];
		r[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_a[2]*_matrixa[9]+_matrixa[13];
		r[2]=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_a[2]*_matrixa[10]+_matrixa[14];
		r[3]=_a[0]*_matrixa[3]+_a[1]*_matrixa[7]+_a[2]*_matrixa[11]+_matrixa[15];
		r[4]=-r[3];
		_int32 flag=0;
		if (r[0]>r[3]) flag|=0x01;
		if (r[1]>r[3]) flag|=0x02;
		if (r[2]>r[3]) flag|=0x04;
		if (r[0]<r[4]) flag|=0x10;
		if (r[1]<r[4]) flag|=0x20;
		if (r[2]<r[4]) flag|=0x40;
		if ((r[3]!=0) && (r[3]!=1.0)) {
			r[3]=1.0f/r[3];
			r[0]=r[0]*r[3];
			r[1]=r[1]*r[3];
			r[2]=r[2]*r[3];
		}
		_e[0]=r[0]*_c[0]+_d[0];
		_e[1]=r[1]*_c[1]+_d[1];
		_e[2]=r[2]*_c[2]+_d[2];
		_e[3]=r[3];
		return flag;
	}

	_int32 _APICALL _V4FProjDEF(float *_a,void *_b,float *_c,float *_d,float *_e) {
		float *_matrixa=(float *)_b;
		float r[5];
		r[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_a[2]*_matrixa[8]+_a[3]*_matrixa[12];
		r[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_a[2]*_matrixa[9]+_a[3]*_matrixa[13];
		r[2]=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_a[2]*_matrixa[10]+_a[3]*_matrixa[14];
		r[3]=_a[0]*_matrixa[3]+_a[1]*_matrixa[7]+_a[2]*_matrixa[11]+_a[3]*_matrixa[15];
		r[4]=-r[3];
		_int32 flag=0;
		if (r[0]>r[3]) flag|=0x01;
		if (r[1]>r[3]) flag|=0x02;
		if (r[2]>r[3]) flag|=0x04;
		if (r[0]<r[4]) flag|=0x10;
		if (r[1]<r[4]) flag|=0x20;
		if (r[2]<r[4]) flag|=0x40;
		if ((r[3]!=0) && (r[3]!=1.0)) {
			r[3]=1.0f/r[3];
			r[0]=r[0]*r[3];
			r[1]=r[1]*r[3];
			r[2]=r[2]*r[3];
		}
		_e[0]=r[0]*_c[0]+_d[0];
		_e[1]=r[1]*_c[1]+_d[1];
		_e[2]=r[2]*_c[2]+_d[2];
		_e[3]=r[3];
		return flag;
	}

	_int32 _APICALL _V2DProjDEF(double *_a,void *_b,double *_c,double *_d,double *_e) {
		double *_matrixa=(double *)_b;
		double r[5];
		r[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_matrixa[12];
		r[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_matrixa[13];
		r[2]=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_matrixa[14];
		r[3]=_a[0]*_matrixa[3]+_a[1]*_matrixa[7]+_matrixa[15];
		r[4]=-r[3];
		_int32 flag=0;
		if (r[0]>r[3]) flag|=0x01;
		if (r[1]>r[3]) flag|=0x02;
		if (r[2]>r[3]) flag|=0x04;
		if (r[0]<r[4]) flag|=0x10;
		if (r[1]<r[4]) flag|=0x20;
		if (r[2]<r[4]) flag|=0x40;
		if ((r[3]!=0) && (r[3]!=1.0)) {
			r[3]=1.0f/r[3];
			r[0]=r[0]*r[3];
			r[1]=r[1]*r[3];
			r[2]=r[2]*r[3];
		}
		_e[0]=r[0]*_c[0]+_d[0];
		_e[1]=r[1]*_c[1]+_d[1];
		_e[2]=r[2]*_c[2]+_d[2];
		_e[3]=r[3];
		return flag;
	}

	_int32 _APICALL _V3DProjDEF(double *_a,void *_b,double *_c,double *_d,double *_e) {
		double *_matrixa=(double *)_b;
		double r[5];
		r[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_a[2]*_matrixa[8]+_matrixa[12];
		r[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_a[2]*_matrixa[9]+_matrixa[13];
		r[2]=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_a[2]*_matrixa[10]+_matrixa[14];
		r[3]=_a[0]*_matrixa[3]+_a[1]*_matrixa[7]+_a[2]*_matrixa[11]+_matrixa[15];
		r[4]=-r[3];
		_int32 flag=0;
		if (r[0]>r[3]) flag|=0x01;
		if (r[1]>r[3]) flag|=0x02;
		if (r[2]>r[3]) flag|=0x04;
		if (r[0]<r[4]) flag|=0x10;
		if (r[1]<r[4]) flag|=0x20;
		if (r[2]<r[4]) flag|=0x40;
		if ((r[3]!=0) && (r[3]!=1.0)) {
			r[3]=1.0f/r[3];
			r[0]=r[0]*r[3];
			r[1]=r[1]*r[3];
			r[2]=r[2]*r[3];
		}
		_e[0]=r[0]*_c[0]+_d[0];
		_e[1]=r[1]*_c[1]+_d[1];
		_e[2]=r[2]*_c[2]+_d[2];
		_e[3]=r[3];
		return flag;
	}

	_int32 _APICALL _V4DProjDEF(double *_a,void *_b,double *_c,double *_d,double *_e) {
		double *_matrixa=(double *)_b;
		double r[5];
		r[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_a[2]*_matrixa[8]+_a[3]*_matrixa[12];
		r[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_a[2]*_matrixa[9]+_a[3]*_matrixa[13];
		r[2]=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_a[2]*_matrixa[10]+_a[3]*_matrixa[14];
		r[3]=_a[0]*_matrixa[3]+_a[1]*_matrixa[7]+_a[2]*_matrixa[11]+_a[3]*_matrixa[15];
		r[4]=-r[3];
		_int32 flag=0;
		if (r[0]>r[3]) flag|=0x01;
		if (r[1]>r[3]) flag|=0x02;
		if (r[2]>r[3]) flag|=0x04;
		if (r[0]<r[4]) flag|=0x10;
		if (r[1]<r[4]) flag|=0x20;
		if (r[2]<r[4]) flag|=0x40;
		if ((r[3]!=0) && (r[3]!=1.0)) {
			r[3]=1.0f/r[3];
			r[0]=r[0]*r[3];
			r[1]=r[1]*r[3];
			r[2]=r[2]*r[3];
		}
		_e[0]=r[0]*_c[0]+_d[0];
		_e[1]=r[1]*_c[1]+_d[1];
		_e[2]=r[2]*_c[2]+_d[2];
		_e[3]=r[3];
		return flag;
	}

	// ************** vector unprojection default function ??? *******************

	_int32 _APICALL _V2FUnProjDEF(float *_a,void *_b,float *_c,float *_d,float *) {
		float *_matrixa=(float *)_b;
		float r[5];
		r[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_matrixa[12];
		r[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_matrixa[13];
		r[2]=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_matrixa[14];
		r[3]=_a[0]*_matrixa[3]+_a[1]*_matrixa[7]+_matrixa[15];
		r[4]=-r[3];
		_int32 flag=0;

		r[0]=(_a[0]-_d[0])/_c[0];
		r[1]=(_a[1]-_d[1])/_c[1];
		return flag;
	}

	// ************** quaternion to vector default function *******************

	void _APICALL _Q4FVectorDEF(float * _a,float * _b) {
		float alen=_V3FLength2DEF(_a);
		if (alen!=0.0f) {
			alen=_FsqrtDEF(alen);
			_V3FScaleDEF(_a,_b,1.0f/alen);
			_b[3]=_FArcTgDEF(_a[3],alen)*2.0f;
		} else {
			_b[0]=0.0f;
			_b[1]=0.0f;
			_b[2]=0.0f;
			_b[3]=0.0f;
		}
	}

	void _APICALL _Q4DVectorDEF(double * _a,double * _b) {
		double alen=_V3DLength2DEF(_a);
		if (alen!=0.0f) {
			alen=_DsqrtDEF(alen);
			_V3DScaleDEF(_a,_b,1.0/alen);
			_b[3]=_DArcTgDEF(_a[3],alen)*2.0f;
		} else {
			_b[0]=0.0;
			_b[1]=0.0;
			_b[2]=0.0;
			_b[3]=0.0;
		}
	}

	// ************** quaternion inv default function *******************
	
	void _APICALL _QFInvDEF(float * _a,float * _b) {
		_V3FInvDEF(_a,_b);
		_b[3]=_a[3];
		_V4FScaleDEF(_b,_b,1.0f/_V4FLength2DEF(_a));
	}

	void _APICALL _QDInvDEF(double * _a,double * _b) {
		_V3DInvDEF(_a,_b);
		_b[3]=_a[3];
		_V4DScaleDEF(_b,_b,1.0/_V4DLength2DEF(_a));
	}

	void _FASTCALL _QFInvDEF_CPP(float * _a,float * _b) {
		_V3FInvDEF_CPP(_a,_b);
		_b[3]=_a[3];
		_V4FScaleDEF_CPP(_b,_b,1.0f/_V4FLength2DEF_CPP(_a));
	}

	void _FASTCALL _QDInvDEF_CPP(double * _a,double * _b) {
		_V3DInvDEF_CPP(_a,_b);
		_b[3]=_a[3];
		_V4DScaleDEF_CPP(_b,_b,1.0/_V4DLength2DEF_CPP(_a));
	}

	// ************** quaternion mul default function *******************

	void _APICALL _QFMulDEF(float * _a,float * _b,float * _c) {
		float r1=_a[0]*_b[3]+_b[0]*_a[3]+_a[1]*_b[2]-_a[2]*_b[1];
		float r2=_a[1]*_b[3]+_b[1]*_a[3]-_a[0]*_b[2]+_a[2]*_b[0];
		float r3=_a[2]*_b[3]+_b[2]*_a[3]+_a[0]*_b[1]-_a[1]*_b[0];
		float r4=_a[3]*_b[3]-_a[0]*_b[0]-_a[1]*_b[1]-_a[2]*_b[2];
		_c[0]=r1;
		_c[1]=r2;
		_c[2]=r3;
		_c[3]=r4;
	}

	void _APICALL _QDMulDEF(double * _a,double * _b,double * _c) {
		double r1=_a[0]*_b[3]+_b[0]*_a[3]+_a[1]*_b[2]-_a[2]*_b[1];
		double r2=_a[1]*_b[3]+_b[1]*_a[3]-_a[0]*_b[2]+_a[2]*_b[0];
		double r3=_a[2]*_b[3]+_b[2]*_a[3]+_a[0]*_b[1]-_a[1]*_b[0];
		double r4=_a[3]*_b[3]-_a[0]*_b[0]-_a[1]*_b[1]-_a[2]*_b[2];
		_c[0]=r1;
		_c[1]=r2;
		_c[2]=r3;
		_c[3]=r4;
	}

	void _FASTCALL _QFMulDEF_CPP(float * _a,float * _b,float * _c) {
		float r1=_a[0]*_b[3]+_b[0]*_a[3]+_a[1]*_b[2]-_a[2]*_b[1];
		float r2=_a[1]*_b[3]+_b[1]*_a[3]-_a[0]*_b[2]+_a[2]*_b[0];
		float r3=_a[2]*_b[3]+_b[2]*_a[3]+_a[0]*_b[1]-_a[1]*_b[0];
		float r4=_a[3]*_b[3]-_a[0]*_b[0]-_a[1]*_b[1]-_a[2]*_b[2];
		_c[0]=r1;
		_c[1]=r2;
		_c[2]=r3;
		_c[3]=r4;
	}

	void _FASTCALL _QDMulDEF_CPP(double * _a,double * _b,double * _c) {
		double r1=_a[0]*_b[3]+_b[0]*_a[3]+_a[1]*_b[2]-_a[2]*_b[1];
		double r2=_a[1]*_b[3]+_b[1]*_a[3]-_a[0]*_b[2]+_a[2]*_b[0];
		double r3=_a[2]*_b[3]+_b[2]*_a[3]+_a[0]*_b[1]-_a[1]*_b[0];
		double r4=_a[3]*_b[3]-_a[0]*_b[0]-_a[1]*_b[1]-_a[2]*_b[2];
		_c[0]=r1;
		_c[1]=r2;
		_c[2]=r3;
		_c[3]=r4;
	}

	// ************** quaternion euler default function *******************

	void _APICALL _QFEulerDEF(float * _a,float * _b) {
		float lsin[3];
		float lcos[3];
		_FSinCosDEF(_a[0]*0.5f,&lsin[0],&lcos[0]);
		_FSinCosDEF(_a[1]*0.5f,&lsin[1],&lcos[1]);
		_FSinCosDEF(_a[2]*0.5f,&lsin[2],&lcos[2]);

		_b[0]=lcos[0]*lsin[1]*lsin[2]+lcos[1]*lsin[0]*lcos[2];
		_b[1]=lcos[1]*lsin[0]*lsin[2]-lcos[0]*lsin[1]*lcos[2];
		_b[2]=lcos[0]*lcos[1]*lsin[2]+lsin[0]*lsin[1]*lcos[2];
		_b[3]=lsin[0]*lsin[1]*lsin[2]-lcos[0]*lcos[1]*lcos[2];
	}

	void _APICALL _QDEulerDEF(double * _a,double * _b) {
		double lsin[3];
		double lcos[3];
		_DSinCosDEF(_a[0]*0.5,&lsin[0],&lcos[0]);
		_DSinCosDEF(_a[1]*0.5,&lsin[1],&lcos[1]);
		_DSinCosDEF(_a[2]*0.5,&lsin[2],&lcos[2]);

		_b[0]=lcos[0]*lsin[1]*lsin[2]+lcos[1]*lsin[0]*lcos[2];
		_b[1]=lcos[1]*lsin[0]*lsin[2]-lcos[0]*lsin[1]*lcos[2];
		_b[2]=lcos[0]*lcos[1]*lsin[2]+lsin[0]*lsin[1]*lcos[2];
		_b[3]=lsin[0]*lsin[1]*lsin[2]-lcos[0]*lcos[1]*lcos[2];
	}

	// ************** quaternion to matrix default function *******************

	void _APICALL _Q4FMatrixDEF(float * _a,float * _b) {
		float f[12];
		float s=2.0f/(_a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2]+_a[3]*_a[3]); // если кватернион нормализоват, то квадрат его длинны равен 1.0, возможно просто 2.0f
		f[0]=_a[0]*s;
		f[1]=_a[1]*s;
		f[2]=_a[2]*s;
		f[3]=f[0]*_a[0];
		f[4]=f[1]*_a[0];
		f[5]=f[2]*_a[0];
		f[6]=_a[1]*f[1];
		f[7]=_a[1]*f[2];
		f[8]=_a[2]*f[2];
		f[9]=f[0]*_a[3];
		f[10]=f[1]*_a[3];
		f[11]=f[2]*_a[3];

		_b[0]=1.0f-(f[6]+f[8]);
		_b[1]=f[4]-f[11];
		_b[2]=f[5]+f[10];
		_b[3]=0;
		_b[4]=f[4]+f[11];
		_b[5]=1.0f-(f[3]+f[8]);
		_b[6]=f[7]-f[9];
		_b[7]=0;
		_b[8]=f[5]-f[10];
		_b[9]=f[7]+f[9];
		_b[10]=1.0f-(f[3]+f[6]);
		_b[11]=0;
		_b[12]=0;
		_b[13]=0;
		_b[14]=0;
		_b[15]=1;
	}

	void _APICALL _Q4DMatrixDEF(double * _a,double * _b) {
		double f[12];
		double s=2.0f/(_a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2]+_a[3]*_a[3]);
		f[0]=_a[0]*s;
		f[1]=_a[1]*s;
		f[2]=_a[2]*s;
		f[3]=f[0]*_a[0];
		f[4]=f[1]*_a[0];
		f[5]=f[2]*_a[0];
		f[6]=_a[1]*f[1];
		f[7]=_a[1]*f[2];
		f[8]=_a[2]*f[2];
		f[9]=f[0]*_a[3];
		f[10]=f[1]*_a[3];
		f[11]=f[2]*_a[3];

		_b[0]=1.0f-(f[6]+f[8]);
		_b[1]=f[4]-f[11];
		_b[2]=f[5]+f[10];
		_b[3]=0;
		_b[4]=f[4]+f[11];
		_b[5]=1.0f-(f[3]+f[8]);
		_b[6]=f[7]-f[9];
		_b[7]=0;
		_b[8]=f[5]-f[10];
		_b[9]=f[7]+f[9];
		_b[10]=1.0f-(f[3]+f[6]);
		_b[11]=0;
		_b[12]=0;
		_b[13]=0;
		_b[14]=0;
		_b[15]=1;
	}

	void _FASTCALL _Q4FMatrixDEF_CPP(float * _a,float * _b) {
		float f[12];
		float s=2.0f/(_a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2]+_a[3]*_a[3]);
		f[0]=_a[0]*s;
		f[1]=_a[1]*s;
		f[2]=_a[2]*s;
		f[3]=f[0]*_a[0];
		f[4]=f[1]*_a[0];
		f[5]=f[2]*_a[0];
		f[6]=_a[1]*f[1];
		f[7]=_a[1]*f[2];
		f[8]=_a[2]*f[2];
		f[9]=f[0]*_a[3];
		f[10]=f[1]*_a[3];
		f[11]=f[2]*_a[3];

		_b[0]=1.0f-(f[6]+f[8]);
		_b[1]=f[4]-f[11];
		_b[2]=f[5]+f[10];
		_b[3]=0;
		_b[4]=f[4]+f[11];
		_b[5]=1.0f-(f[3]+f[8]);
		_b[6]=f[7]-f[9];
		_b[7]=0;
		_b[8]=f[5]-f[10];
		_b[9]=f[7]+f[9];
		_b[10]=1.0f-(f[3]+f[6]);
		_b[11]=0;
		_b[12]=0;
		_b[13]=0;
		_b[14]=0;
		_b[15]=1;
	}

	void _FASTCALL _Q4DMatrixDEF_CPP(double * _a,double * _b) {
		double f[12];
		double s=2.0f/(_a[0]*_a[0]+_a[1]*_a[1]+_a[2]*_a[2]+_a[3]*_a[3]);
		f[0]=_a[0]*s;
		f[1]=_a[1]*s;
		f[2]=_a[2]*s;
		f[3]=f[0]*_a[0];
		f[4]=f[1]*_a[0];
		f[5]=f[2]*_a[0];
		f[6]=_a[1]*f[1];
		f[7]=_a[1]*f[2];
		f[8]=_a[2]*f[2];
		f[9]=f[0]*_a[3];
		f[10]=f[1]*_a[3];
		f[11]=f[2]*_a[3];

		_b[0]=1.0f-(f[6]+f[8]);
		_b[1]=f[4]-f[11];
		_b[2]=f[5]+f[10];
		_b[3]=0;
		_b[4]=f[4]+f[11];
		_b[5]=1.0f-(f[3]+f[8]);
		_b[6]=f[7]-f[9];
		_b[7]=0;
		_b[8]=f[5]-f[10];
		_b[9]=f[7]+f[9];
		_b[10]=1.0f-(f[3]+f[6]);
		_b[11]=0;
		_b[12]=0;
		_b[13]=0;
		_b[14]=0;
		_b[15]=1;
	}

// ************** afine transform default function *******************

	void _APICALL _V2FAfineTransformDEF(float * _a,float * _b,float * _c) {
		float r1=_a[0];
		float r2=_a[1];
		float t1=_b[0];
		float t2=_b[1];
		_c[0]=r1*t1-r2*t2;
		_c[1]=r2*t1+r1*t2;
	}

	void _APICALL _V2DAfineTransformDEF(double * _a,double * _b,double * _c) {
		double r1=_a[0];
		double r2=_a[1];
		double t1=_b[0];
		double t2=_b[1];
		_c[0]=r1*t1-r2*t2;
		_c[1]=r2*t1+r1*t2;
	}

// ************** quaternion transform default function *******************

	void _APICALL _Q2FInvTransformDEF(float * _a,float * _b,float * _c) {
		float mv[4];
		mv[0]=-_a[2]*_b[1]+_a[3]*_b[0];
		mv[1]=+_a[3]*_b[1]+_a[2]*_b[0];
		mv[2]=+_a[0]*_b[1]-_a[1]*_b[0];
		mv[3]=-_a[1]*_b[1]-_a[0]*_b[0];

		_c[0]=mv[0]*_a[3]+mv[2]*_a[1]-mv[1]*_a[2]-mv[3]*_a[0];
		_c[1]=mv[1]*_a[3]+mv[0]*_a[2]-mv[2]*_a[0]-mv[3]*_a[1];
	}

	void _APICALL _Q3FInvTransformDEF(float * _a,float * _b,float * _c) {
		float mv[4];
		mv[0]=(+_a[1]*_b[2]-_a[2]*_b[1]+_a[3]*_b[0]);
		mv[1]=(-_a[0]*_b[2]+_a[3]*_b[1]+_a[2]*_b[0]);
		mv[2]=(+_a[3]*_b[2]+_a[0]*_b[1]-_a[1]*_b[0]);
		mv[3]=(-_a[2]*_b[2]-_a[1]*_b[1]-_a[0]*_b[0]);

		_c[0]=(+mv[0]*_a[3]+mv[2]*_a[1]-mv[1]*_a[2]-mv[3]*_a[0]);
		_c[1]=(+mv[0]*_a[2]-mv[2]*_a[0]+mv[1]*_a[3]-mv[3]*_a[1]);
		_c[2]=(-mv[0]*_a[1]+mv[2]*_a[3]+mv[1]*_a[0]-mv[3]*_a[2]);
	}

	void _APICALL _Q2DInvTransformDEF(double * _a,double * _b,double * _c) {
		double mv[4];
		mv[0]=-_a[2]*_b[1]+_a[3]*_b[0];
		mv[1]=+_a[3]*_b[1]+_a[2]*_b[0];
		mv[2]=+_a[0]*_b[1]-_a[1]*_b[0];
		mv[3]=-_a[1]*_b[1]-_a[0]*_b[0];

		_c[0]=mv[0]*_a[3]+mv[2]*_a[1]-mv[1]*_a[2]-mv[3]*_a[0];
		_c[1]=mv[1]*_a[3]+mv[0]*_a[2]-mv[2]*_a[0]-mv[3]*_a[1];
	}

	void _APICALL _Q3DInvTransformDEF(double * _a,double * _b,double * _c) {
		double mv[4];
		mv[0]=(+_a[1]*_b[2]-_a[2]*_b[1]+_a[3]*_b[0]);
		mv[1]=(-_a[0]*_b[2]+_a[3]*_b[1]+_a[2]*_b[0]);
		mv[2]=(+_a[3]*_b[2]+_a[0]*_b[1]-_a[1]*_b[0]);
		mv[3]=(-_a[2]*_b[2]-_a[1]*_b[1]-_a[0]*_b[0]);

		_c[0]=(+mv[0]*_a[3]+mv[2]*_a[1]-mv[1]*_a[2]-mv[3]*_a[0]);
		_c[1]=(+mv[0]*_a[2]-mv[2]*_a[0]+mv[1]*_a[3]-mv[3]*_a[1]);
		_c[2]=(-mv[0]*_a[1]+mv[2]*_a[3]+mv[1]*_a[0]-mv[3]*_a[2]);
	}

	void _FASTCALL _Q3FInvTransformDEF_CPP(float * _a,float * _b,float * _c) {
		float mv[4];
		mv[0]=+_a[1]*_b[2]-_a[2]*_b[1]+_a[3]*_b[0];
		mv[1]=-_a[0]*_b[2]+_a[2]*_b[0]+_a[3]*_b[1];
		mv[2]=_a[0]*_b[1]-_a[1]*_b[0]+_a[3]*_b[2];
		mv[3]=-_a[0]*_b[0]-_a[1]*_b[1]-_a[2]*_b[2];

		_c[0]=mv[0]*_a[3]-mv[1]*_a[2]+mv[2]*_a[1]-mv[3]*_a[0];
		_c[1]=mv[0]*_a[2]+mv[1]*_a[3]-mv[2]*_a[0]-mv[3]*_a[1];
		_c[2]=-mv[0]*_a[1]+mv[1]*_a[0]+mv[2]*_a[3]-mv[3]*_a[2];
	}

	void _FASTCALL _Q3DInvTransformDEF_CPP(double * _a,double * _b,double * _c) {
		double mv[4];
		mv[0]=+_a[1]*_b[2]-_a[2]*_b[1]+_a[3]*_b[0];
		mv[1]=-_a[0]*_b[2]+_a[2]*_b[0]+_a[3]*_b[1];
		mv[2]=_a[0]*_b[1]-_a[1]*_b[0]+_a[3]*_b[2];
		mv[3]=-_a[0]*_b[0]-_a[1]*_b[1]-_a[2]*_b[2];

		_c[0]=mv[0]*_a[3]-mv[1]*_a[2]+mv[2]*_a[1]-mv[3]*_a[0];
		_c[1]=mv[0]*_a[2]+mv[1]*_a[3]-mv[2]*_a[0]-mv[3]*_a[1];
		_c[2]=-mv[0]*_a[1]+mv[1]*_a[0]+mv[2]*_a[3]-mv[3]*_a[2];
	}

	// ************** matrix transpose default function *******************

	void _APICALL _M4FTransposeDEF(void * _a,void * _b)
	{
		float *_matrixa=(float *)_a;
		float _matrixt[11];
		float *_matrixb=(float *)_b;

		_matrixb[0]=_matrixa[0];
		_matrixb[5]=_matrixa[5];
		_matrixb[10]=_matrixa[10];
		_matrixb[15]=_matrixa[15];

		_matrixt[1]=_matrixa[4];
		_matrixb[4]=_matrixa[1];
		_matrixb[1]=_matrixt[1];
		_matrixt[2]=_matrixa[8];
		_matrixb[8]=_matrixa[2];
		_matrixb[2]=_matrixt[2];
		_matrixt[3]=_matrixa[12];
		_matrixb[12]=_matrixa[3];
		_matrixb[3]=_matrixt[3];
		_matrixt[6]=_matrixa[9];
		_matrixb[9]=_matrixa[6];
		_matrixb[6]=_matrixt[6];
		_matrixt[7]=_matrixa[13];
		_matrixb[13]=_matrixa[7];
		_matrixb[7]=_matrixt[7];
		_matrixt[10]=_matrixa[14];
		_matrixb[14]=_matrixa[11];
		_matrixb[11]=_matrixt[10];
	}

	void _APICALL _M4DTransposeDEF(void * _a,void * _b)
	{
		double *_matrixa=(double *)_a;
		double _matrixt[11];
		double *_matrixb=(double *)_b;

		_matrixb[0]=_matrixa[0];
		_matrixb[5]=_matrixa[5];
		_matrixb[10]=_matrixa[10];
		_matrixb[15]=_matrixa[15];

		_matrixt[1]=_matrixa[4];
		_matrixb[4]=_matrixa[1];
		_matrixb[1]=_matrixt[1];
		_matrixt[2]=_matrixa[8];
		_matrixb[8]=_matrixa[2];
		_matrixb[2]=_matrixt[2];
		_matrixt[3]=_matrixa[12];
		_matrixb[12]=_matrixa[3];
		_matrixb[3]=_matrixt[3];
		_matrixt[6]=_matrixa[9];
		_matrixb[9]=_matrixa[6];
		_matrixb[6]=_matrixt[6];
		_matrixt[7]=_matrixa[13];
		_matrixb[13]=_matrixa[7];
		_matrixb[7]=_matrixt[7];
		_matrixt[10]=_matrixa[14];
		_matrixb[14]=_matrixa[11];
		_matrixb[11]=_matrixt[10];
	}

	// ************** matrix mul default function *******************

	void _APICALL _M4FMulDEF(void *_a,void *_b,void *_c)
	{
		float *_matrixa=(float *)_b;
		float *_matrixb=(float *)_a;
		float *_matrixc=(float *)_c;
		float r[12];
		r[0]=_matrixb[0];
		r[1]=_matrixb[1];
		_matrixc[0]=_matrixa[0]*_matrixb[0]+_matrixa[1]*_matrixb[4]+_matrixa[2]*_matrixb[8]+_matrixa[3]*_matrixb[12];
		_matrixc[1]=_matrixa[0]*_matrixb[1]+_matrixa[1]*_matrixb[5]+_matrixa[2]*_matrixb[9]+_matrixa[3]*_matrixb[13];
		r[2]=_matrixb[2];
		r[3]=_matrixb[3];
		_matrixc[2]=_matrixa[0]*_matrixb[2]+_matrixa[1]*_matrixb[6]+_matrixa[2]*_matrixb[10]+_matrixa[3]*_matrixb[14];
		_matrixc[3]=_matrixa[0]*_matrixb[3]+_matrixa[1]*_matrixb[7]+_matrixa[2]*_matrixb[11]+_matrixa[3]*_matrixb[15];
		r[4]=_matrixb[4];
		r[5]=_matrixb[5];
		_matrixc[4]=_matrixa[4]*r[0]+_matrixa[5]*r[4]+_matrixa[6]*_matrixb[8]+_matrixa[7]*_matrixb[12];
		_matrixc[5]=_matrixa[4]*r[1]+_matrixa[5]*r[5]+_matrixa[6]*_matrixb[9]+_matrixa[7]*_matrixb[13];
		r[6]=_matrixb[6];
		r[7]=_matrixb[7];
		_matrixc[6]=_matrixa[4]*r[2]+_matrixa[5]*r[6]+_matrixa[6]*_matrixb[10]+_matrixa[7]*_matrixb[14];
		_matrixc[7]=_matrixa[4]*r[3]+_matrixa[5]*r[7]+_matrixa[6]*_matrixb[11]+_matrixa[7]*_matrixb[15];
		r[8]=_matrixb[8];
		r[9]=_matrixb[9];
		_matrixc[8]=_matrixa[8]*r[0]+_matrixa[9]*r[4]+_matrixa[10]*_matrixb[8]+_matrixa[11]*_matrixb[12];
		_matrixc[9]=_matrixa[8]*r[1]+_matrixa[9]*r[5]+_matrixa[10]*_matrixb[9]+_matrixa[11]*_matrixb[13];
		r[10]=_matrixb[10];
		r[11]=_matrixb[11];
		_matrixc[10]=_matrixa[8]*r[2]+_matrixa[9]*r[6]+_matrixa[10]*_matrixb[10]+_matrixa[11]*_matrixb[14];
		_matrixc[11]=_matrixa[8]*r[3]+_matrixa[9]*r[7]+_matrixa[10]*_matrixb[11]+_matrixa[11]*_matrixb[15];
		_matrixc[12]=_matrixa[12]*r[0]+_matrixa[13]*r[4]+_matrixa[14]*r[8]+_matrixa[15]*_matrixb[12];
		_matrixc[13]=_matrixa[12]*r[1]+_matrixa[13]*r[5]+_matrixa[14]*r[9]+_matrixa[15]*_matrixb[13];
		_matrixc[14]=_matrixa[12]*r[2]+_matrixa[13]*r[6]+_matrixa[14]*r[10]+_matrixa[15]*_matrixb[14];
		_matrixc[15]=_matrixa[12]*r[3]+_matrixa[13]*r[7]+_matrixa[14]*r[11]+_matrixa[15]*_matrixb[15];
	}

	void _APICALL _M4DMulDEF(void *_a,void *_b,void *_c)
	{
		double *_matrixa=(double *)_b;
		double *_matrixb=(double *)_a;
		double *_matrixc=(double *)_c;
		double r[12];
		r[0]=_matrixb[0];
		r[1]=_matrixb[1];
		_matrixc[0]=_matrixa[0]*_matrixb[0]+_matrixa[1]*_matrixb[4]+_matrixa[2]*_matrixb[8]+_matrixa[3]*_matrixb[12];
		_matrixc[1]=_matrixa[0]*_matrixb[1]+_matrixa[1]*_matrixb[5]+_matrixa[2]*_matrixb[9]+_matrixa[3]*_matrixb[13];
		r[4]=_matrixb[4];
		r[5]=_matrixb[5];
		_matrixc[4]=_matrixa[4]*r[0]+_matrixa[5]*r[4]+_matrixa[6]*_matrixb[8]+_matrixa[7]*_matrixb[12];
		_matrixc[5]=_matrixa[4]*r[1]+_matrixa[5]*r[5]+_matrixa[6]*_matrixb[9]+_matrixa[7]*_matrixb[13];
		r[8]=_matrixb[8];
		r[9]=_matrixb[9];
		_matrixc[8]=_matrixa[8]*r[0]+_matrixa[9]*r[4]+_matrixa[10]*_matrixb[8]+_matrixa[11]*_matrixb[12];
		_matrixc[9]=_matrixa[8]*r[1]+_matrixa[9]*r[5]+_matrixa[10]*_matrixb[9]+_matrixa[11]*_matrixb[13];
		_matrixc[12]=_matrixa[12]*r[0]+_matrixa[13]*r[4]+_matrixa[14]*r[8]+_matrixa[15]*_matrixb[12];
		_matrixc[13]=_matrixa[12]*r[1]+_matrixa[13]*r[5]+_matrixa[14]*r[9]+_matrixa[15]*_matrixb[13];
		r[2]=_matrixb[2];
		r[3]=_matrixb[3];
		_matrixc[2]=_matrixa[0]*_matrixb[2]+_matrixa[1]*_matrixb[6]+_matrixa[2]*_matrixb[10]+_matrixa[3]*_matrixb[14];
		_matrixc[3]=_matrixa[0]*_matrixb[3]+_matrixa[1]*_matrixb[7]+_matrixa[2]*_matrixb[11]+_matrixa[3]*_matrixb[15];
		r[6]=_matrixb[6];
		r[7]=_matrixb[7];
		_matrixc[6]=_matrixa[4]*r[2]+_matrixa[5]*r[6]+_matrixa[6]*_matrixb[10]+_matrixa[7]*_matrixb[14];
		_matrixc[7]=_matrixa[4]*r[3]+_matrixa[5]*r[7]+_matrixa[6]*_matrixb[11]+_matrixa[7]*_matrixb[15];
		r[10]=_matrixb[10];
		r[11]=_matrixb[11];
		_matrixc[10]=_matrixa[8]*r[2]+_matrixa[9]*r[6]+_matrixa[10]*_matrixb[10]+_matrixa[11]*_matrixb[14];
		_matrixc[11]=_matrixa[8]*r[3]+_matrixa[9]*r[7]+_matrixa[10]*_matrixb[11]+_matrixa[11]*_matrixb[15];
		_matrixc[14]=_matrixa[12]*r[2]+_matrixa[13]*r[6]+_matrixa[14]*r[10]+_matrixa[15]*_matrixb[14];
		_matrixc[15]=_matrixa[12]*r[3]+_matrixa[13]*r[7]+_matrixa[14]*r[11]+_matrixa[15]*_matrixb[15];
	}

	// ************** matrix invert default function *******************

	_int32 _APICALL _M4FInvDEF(void *_a,void *_b)
	{
		float *_ma=(float *)_a;
		float *_mb=(float *)_b;
		_int32 i; 
		_mb[0] =   _ma[5]*_ma[10]*_ma[15] - _ma[5]*_ma[11]*_ma[14] - _ma[9]*_ma[6]*_ma[15] + _ma[9]*_ma[7]*_ma[14] + _ma[13]*_ma[6]*_ma[11] - _ma[13]*_ma[7]*_ma[10];
		_mb[1] =   _ma[9]*_ma[2]*_ma[15]  - _ma[9]*_ma[3]*_ma[14] - _ma[1]*_ma[10]*_ma[15] + _ma[1]*_ma[11]*_ma[14] + _ma[13]*_ma[3]*_ma[10] - _ma[13]*_ma[2]*_ma[11];
		_mb[2] =   _ma[1]*_ma[6]*_ma[15]  - _ma[1]*_ma[7]*_ma[14]  - _ma[5]*_ma[2]*_ma[15] + _ma[5]*_ma[3]*_ma[14] + _ma[13]*_ma[2]*_ma[7]  - _ma[13]*_ma[3]*_ma[6];
		_mb[3] =  -_ma[1]*_ma[6]*_ma[11]  + _ma[1]*_ma[7]*_ma[10]  + _ma[5]*_ma[2]*_ma[11] - _ma[5]*_ma[3]*_ma[10] - _ma[9]*_ma[2]*_ma[7]   + _ma[9]*_ma[3]*_ma[6];
		_mb[4] =  -_ma[4]*_ma[10]*_ma[15] + _ma[4]*_ma[11]*_ma[14] + _ma[8]*_ma[6]*_ma[15] - _ma[8]*_ma[7]*_ma[14] - _ma[12]*_ma[6]*_ma[11] + _ma[12]*_ma[7]*_ma[10];
		_mb[5] =   _ma[0]*_ma[10]*_ma[15] - _ma[0]*_ma[11]*_ma[14] - _ma[8]*_ma[2]*_ma[15] + _ma[8]*_ma[3]*_ma[14] + _ma[12]*_ma[2]*_ma[11] - _ma[12]*_ma[3]*_ma[10];
		_mb[6] =  -_ma[0]*_ma[6]*_ma[15]  + _ma[0]*_ma[7]*_ma[14]  + _ma[4]*_ma[2]*_ma[15] - _ma[4]*_ma[3]*_ma[14] - _ma[12]*_ma[2]*_ma[7]  + _ma[12]*_ma[3]*_ma[6];
		_mb[7] =   _ma[0]*_ma[6]*_ma[11]  - _ma[0]*_ma[7]*_ma[10]  - _ma[4]*_ma[2]*_ma[11] + _ma[4]*_ma[3]*_ma[10] + _ma[8]*_ma[2]*_ma[7]   - _ma[8]*_ma[3]*_ma[6];
		_mb[8] =   _ma[4]*_ma[9]*_ma[15]  - _ma[4]*_ma[11]*_ma[13] - _ma[8]*_ma[5]*_ma[15] + _ma[8]*_ma[7]*_ma[13] + _ma[12]*_ma[5]*_ma[11] - _ma[12]*_ma[7]*_ma[9];
		_mb[9] =  -_ma[0]*_ma[9]*_ma[15]  + _ma[0]*_ma[11]*_ma[13] + _ma[8]*_ma[1]*_ma[15] - _ma[8]*_ma[3]*_ma[13] - _ma[12]*_ma[1]*_ma[11] + _ma[12]*_ma[3]*_ma[9];
		_mb[10] =  _ma[0]*_ma[5]*_ma[15]  - _ma[0]*_ma[7]*_ma[13]  - _ma[4]*_ma[1]*_ma[15] + _ma[4]*_ma[3]*_ma[13] + _ma[12]*_ma[1]*_ma[7]  - _ma[12]*_ma[3]*_ma[5];
		_mb[11] = -_ma[0]*_ma[5]*_ma[11]  + _ma[0]*_ma[7]*_ma[9]   + _ma[4]*_ma[1]*_ma[11] - _ma[4]*_ma[3]*_ma[9]  - _ma[8]*_ma[1]*_ma[7]   + _ma[8]*_ma[3]*_ma[5];
		_mb[12] = -_ma[4]*_ma[9]*_ma[14]  + _ma[4]*_ma[10]*_ma[13] + _ma[8]*_ma[5]*_ma[14] - _ma[8]*_ma[6]*_ma[13] - _ma[12]*_ma[5]*_ma[10] + _ma[12]*_ma[6]*_ma[9];
		_mb[13] =  _ma[0]*_ma[9]*_ma[14]  - _ma[0]*_ma[10]*_ma[13] - _ma[8]*_ma[1]*_ma[14] + _ma[8]*_ma[2]*_ma[13] + _ma[12]*_ma[1]*_ma[10] - _ma[12]*_ma[2]*_ma[9];
		_mb[14] = -_ma[0]*_ma[5]*_ma[14]  + _ma[0]*_ma[6]*_ma[13]  + _ma[4]*_ma[1]*_ma[14] - _ma[4]*_ma[2]*_ma[13] - _ma[12]*_ma[1]*_ma[6]  + _ma[12]*_ma[2]*_ma[5];
		_mb[15] =  _ma[0]*_ma[5]*_ma[10]  - _ma[0]*_ma[6]*_ma[9]   - _ma[4]*_ma[1]*_ma[10] + _ma[4]*_ma[2]*_ma[9]  + _ma[8]*_ma[1]*_ma[6]   - _ma[8]*_ma[2]*_ma[5];

		float det = _ma[0]*_mb[0] + _ma[1]*_mb[4] + _ma[2]*_mb[8] + _ma[3]*_mb[12];
		if (det == 0)
			return 0;

		det=1.0f/det;

		for (i = 0; i < 16; i++)
			_mb[i] = _mb[i] * det;

	    return 1;
	}

	_int32 _APICALL _M4DInvDEF(void *_a,void *_b)
	{
		double *_ma=(double *)_a;
		double *_mb=(double *)_b;
		_int32 i;
		_mb[0] = _ma[5]*_ma[10]*_ma[15] - _ma[5]*_ma[11]*_ma[14] - _ma[9]*_ma[6]*_ma[15]
             + _ma[9]*_ma[7]*_ma[14] + _ma[13]*_ma[6]*_ma[11] - _ma[13]*_ma[7]*_ma[10];
		_mb[4] =  -_ma[4]*_ma[10]*_ma[15] + _ma[4]*_ma[11]*_ma[14] + _ma[8]*_ma[6]*_ma[15]
             - _ma[8]*_ma[7]*_ma[14] - _ma[12]*_ma[6]*_ma[11] + _ma[12]*_ma[7]*_ma[10];
		_mb[8] =   _ma[4]*_ma[9]*_ma[15] - _ma[4]*_ma[11]*_ma[13] - _ma[8]*_ma[5]*_ma[15]
             + _ma[8]*_ma[7]*_ma[13] + _ma[12]*_ma[5]*_ma[11] - _ma[12]*_ma[7]*_ma[9];
		_mb[12] = -_ma[4]*_ma[9]*_ma[14] + _ma[4]*_ma[10]*_ma[13] + _ma[8]*_ma[5]*_ma[14]
             - _ma[8]*_ma[6]*_ma[13] - _ma[12]*_ma[5]*_ma[10] + _ma[12]*_ma[6]*_ma[9];
		_mb[1] =  -_ma[1]*_ma[10]*_ma[15] + _ma[1]*_ma[11]*_ma[14] + _ma[9]*_ma[2]*_ma[15]
             - _ma[9]*_ma[3]*_ma[14] - _ma[13]*_ma[2]*_ma[11] + _ma[13]*_ma[3]*_ma[10];
		_mb[5] =   _ma[0]*_ma[10]*_ma[15] - _ma[0]*_ma[11]*_ma[14] - _ma[8]*_ma[2]*_ma[15]
             + _ma[8]*_ma[3]*_ma[14] + _ma[12]*_ma[2]*_ma[11] - _ma[12]*_ma[3]*_ma[10];
		_mb[9] =  -_ma[0]*_ma[9]*_ma[15] + _ma[0]*_ma[11]*_ma[13] + _ma[8]*_ma[1]*_ma[15]
             - _ma[8]*_ma[3]*_ma[13] - _ma[12]*_ma[1]*_ma[11] + _ma[12]*_ma[3]*_ma[9];
		_mb[13] =  _ma[0]*_ma[9]*_ma[14] - _ma[0]*_ma[10]*_ma[13] - _ma[8]*_ma[1]*_ma[14]
             + _ma[8]*_ma[2]*_ma[13] + _ma[12]*_ma[1]*_ma[10] - _ma[12]*_ma[2]*_ma[9];
		_mb[2] =   _ma[1]*_ma[6]*_ma[15] - _ma[1]*_ma[7]*_ma[14] - _ma[5]*_ma[2]*_ma[15]
             + _ma[5]*_ma[3]*_ma[14] + _ma[13]*_ma[2]*_ma[7] - _ma[13]*_ma[3]*_ma[6];
		_mb[6] =  -_ma[0]*_ma[6]*_ma[15] + _ma[0]*_ma[7]*_ma[14] + _ma[4]*_ma[2]*_ma[15]
             - _ma[4]*_ma[3]*_ma[14] - _ma[12]*_ma[2]*_ma[7] + _ma[12]*_ma[3]*_ma[6];
		_mb[10] =  _ma[0]*_ma[5]*_ma[15] - _ma[0]*_ma[7]*_ma[13] - _ma[4]*_ma[1]*_ma[15]
             + _ma[4]*_ma[3]*_ma[13] + _ma[12]*_ma[1]*_ma[7] - _ma[12]*_ma[3]*_ma[5];
		_mb[14] = -_ma[0]*_ma[5]*_ma[14] + _ma[0]*_ma[6]*_ma[13] + _ma[4]*_ma[1]*_ma[14]
             - _ma[4]*_ma[2]*_ma[13] - _ma[12]*_ma[1]*_ma[6] + _ma[12]*_ma[2]*_ma[5];
		_mb[3] =  -_ma[1]*_ma[6]*_ma[11] + _ma[1]*_ma[7]*_ma[10] + _ma[5]*_ma[2]*_ma[11]
             - _ma[5]*_ma[3]*_ma[10] - _ma[9]*_ma[2]*_ma[7] + _ma[9]*_ma[3]*_ma[6];
		_mb[7] =   _ma[0]*_ma[6]*_ma[11] - _ma[0]*_ma[7]*_ma[10] - _ma[4]*_ma[2]*_ma[11]
             + _ma[4]*_ma[3]*_ma[10] + _ma[8]*_ma[2]*_ma[7] - _ma[8]*_ma[3]*_ma[6];
		_mb[11] = -_ma[0]*_ma[5]*_ma[11] + _ma[0]*_ma[7]*_ma[9] + _ma[4]*_ma[1]*_ma[11]
             - _ma[4]*_ma[3]*_ma[9] - _ma[8]*_ma[1]*_ma[7] + _ma[8]*_ma[3]*_ma[5];
		_mb[15] =  _ma[0]*_ma[5]*_ma[10] - _ma[0]*_ma[6]*_ma[9] - _ma[4]*_ma[1]*_ma[10]
             + _ma[4]*_ma[2]*_ma[9] + _ma[8]*_ma[1]*_ma[6] - _ma[8]*_ma[2]*_ma[5];

		double det = _ma[0]*_mb[0] + _ma[1]*_mb[4] + _ma[2]*_mb[8] + _ma[3]*_mb[12];
		if (det == 0)
			return 0;

		det=1.0f/det;

		for (i = 0; i < 16; i++)
			_mb[i] = _mb[i] * det;

	    return 1;
	}

	// ************** matrix projection default function *******************

	void _APICALL _M4FPerspectiveDEF(void *_m,_int32 _w,_int32 _h,float _aend,float _astart,float _fov)
	{
		float tbrl[2];

		float f=(float)(_fov*PI360);
		_FSinCosDEF(f,&tbrl[0],&tbrl[1]);
		f=tbrl[1]/tbrl[0];
		if (_h>0) { tbrl[1]=(float)(_w*1.0/_h); } else tbrl[1]=(float)(_w);
		tbrl[0]=f;
		tbrl[1]=f*tbrl[1];

		float *_matrix=(float *)_m;
		_CleanMemDEF(_m,4*16);
		_matrix[0]=1.0f/tbrl[1];
		_matrix[5]=1.0f/tbrl[0];
		_matrix[10]=-(_aend+_astart)/(_aend-_astart);
		_matrix[11]=-1.0f;
		_matrix[14]=-2.0f*_aend*_astart/(_aend-_astart);
	}

	void _APICALL _M4DPerspectiveDEF(void *_m,_int32 _w,_int32 _h,double _aend,double _astart,double _fov)
	{
		double tbrl[2];

		double f=_fov*PI360;
		_DSinCosDEF(f,&tbrl[0],&tbrl[1]);
		f=tbrl[1]/tbrl[0];
		if (_h>0) { tbrl[1]=_w*1.0/_h; } else tbrl[1]=_w;
		tbrl[0]=f;
		tbrl[1]=f*tbrl[1];

		double *_matrix=(double *)_m;
		_CleanMemDEF(_m,8*16);
		_matrix[0]=1.0/tbrl[1];
		_matrix[5]=1.0/tbrl[0];
		_matrix[10]=-(_aend+_astart)/(_aend-_astart);
		_matrix[11]=-1.0;
		_matrix[14]=-2.0*_aend*_astart/(_aend-_astart);
	}

	void _APICALL _M4FOrtographicDEF(void *_m,_int32 _w,_int32 _h,float _aend,float _astart,float _scale)
	{
		float tbrl[2];

		if (_h>0) { tbrl[1]=(float)(_w*1.0/_h); } else tbrl[1]=(float)(_w);
		tbrl[0]=_scale;
		tbrl[1]=_scale*tbrl[1];

		float *_matrix=(float *)_m;
		_CleanMemDEF(_m,4*16);
		_matrix[0]=2.0f/tbrl[1];
		_matrix[5]=2.0f/tbrl[0];
		_matrix[10]=-2.0f/(_aend-_astart);
		_matrix[14]=-(_aend+_astart)/(_aend-_astart);
		_matrix[15]=1.0f;
	}

	void _APICALL _M4DOrtographicDEF(void *_m,_int32 _w,_int32 _h,double _aend,double _astart,double _scale)
	{
		double tbrl[2];

		if (_h>0) { tbrl[1]=(float)(_w*1.0/_h); } else tbrl[1]=(float)(_w);
		tbrl[0]=_scale;
		tbrl[1]=_scale*tbrl[1];

		double *_matrix=(double *)_m;
		_CleanMemDEF(_m,8*16);
		_matrix[0]=2.0/tbrl[1];
		_matrix[5]=2.0/tbrl[0];
		_matrix[10]=-2.0/(_aend-_astart);
		_matrix[14]=-(_aend+_astart)/(_aend-_astart);
		_matrix[15]=1.0;
	}

	// ************** matrix ed default function *******************

	void _APICALL _M4FIdentityDEF(void *_m)
	{
		float *_matrix=(float *)_m;
		_CleanMemDEF(_m,4*16);
		_matrix[0]=1;
		_matrix[5]=1;
		_matrix[10]=1;
		_matrix[15]=1;
	}

	void _APICALL _M4DIdentityDEF(void *_m)
	{
		double *_matrix=(double *)_m;
		_CleanMemDEF(_m,8*16);
		_matrix[0]=1;
		_matrix[5]=1;
		_matrix[10]=1;
		_matrix[15]=1;
	}

	// ************** matrix to quaternion default function *******************

	void _APICALL _M4FQuaternionDEF(float * _a,float * _b) {
		float *_matrix=(float *)_a;
		float tr=_matrix[0]+_matrix[5]+_matrix[10];
		if (tr>0) {
			float s = _FsqrtDEF(tr+1.0f);
			_b[3]=s*0.5;
			s=0.5/s;
			_b[0]=(_matrix[6]-_matrix[9])*s;
			_b[1]=(_matrix[8]-_matrix[2])*s;
			_b[2]=(_matrix[1]-_matrix[4])*s;
		} else {
			_int32 i=0;
			if (_matrix[5]>_matrix[0]) i=1;
			if (_matrix[10]>_matrix[(i<<2)+i]) i=2;
			_int32 j=i+1;
			if (j>2) j=0;
			_int32 k=j+1;
			if (k>2) k=0;
			float s = _FsqrtDEF(_matrix[(i<<2)+i]-_matrix[(j<<2)+j]+_matrix[(k<<2)+k]+1.0f);
			_b[i]=s*0.5;
			if (s!=0.0) s=0.5/s;

			_b[3]=(_matrix[(j<<2)+k]-_matrix[(k<<2)+j])*s;
			_b[j]=(_matrix[(i<<2)+j]-_matrix[(j<<2)+i])*s;
			_b[k]=(_matrix[(i<<2)+k]-_matrix[(k<<2)+i])*s;
		}
	}

	void _APICALL _M4DQuaternionDEF(double * _a,double * _b) {
		double *_matrix=(double *)_a;
		double tr=_matrix[0]+_matrix[5]+_matrix[10];
		if (tr>0) {
			double s = _DsqrtDEF(tr+1.0f);
			_b[3]=s*0.5;
			s=0.5/s;
			_b[0]=(_matrix[6]-_matrix[9])*s;
			_b[1]=(_matrix[8]-_matrix[2])*s;
			_b[2]=(_matrix[1]-_matrix[4])*s;
		} else {
			_int32 i=0;
			if (_matrix[5]>_matrix[0]) i=1;
			if (_matrix[10]>_matrix[(i<<2)+i]) i=2;
			_int32 j=i+1;
			if (j>2) j=0;
			_int32 k=j+1;
			if (k>2) k=0;
			double s = _DsqrtDEF(_matrix[(i<<2)+i]-_matrix[(j<<2)+j]+_matrix[(k<<2)+k]+1.0f);
			_b[i]=s*0.5;
			if (s!=0.0) s=0.5/s;

			_b[3]=(_matrix[(j<<2)+k]-_matrix[(k<<2)+j])*s;
			_b[j]=(_matrix[(i<<2)+j]-_matrix[(j<<2)+i])*s;
			_b[k]=(_matrix[(i<<2)+k]-_matrix[(k<<2)+i])*s;
		}
	}

	// ************** vector to translate matrix default function *******************

	void _APICALL _M4FTranslateDEF(void *_m,float *v)
	{
		float *_matrix=(float *)_m;
		_CleanMemDEF(_m,4*16);
		_matrix[0]=1;
		_matrix[5]=1;
		_matrix[10]=1;
		_matrix[15]=1;
		_matrix[12]=v[0];
		_matrix[13]=v[1];
		_matrix[14]=v[2];
	}

	void _APICALL _M4DTranslateDEF(void *_m,double *v)
	{
		double *_matrix=(double *)_m;
		_CleanMemDEF(_m,8*16);
		_matrix[0]=1;
		_matrix[5]=1;
		_matrix[10]=1;
		_matrix[15]=1;
		_matrix[12]=v[0];
		_matrix[13]=v[1];
		_matrix[14]=v[2];
	}

	// ************** vector to scale matrix default function *******************

	void _APICALL _M4FScaleDEF(void *_m,float *v)
	{
		float *_matrix=(float *)_m;
		_CleanMemDEF(_m,4*16);
		_matrix[0]=v[0];
		_matrix[5]=v[1];
		_matrix[10]=v[2];
		_matrix[15]=1;
	}

	void _APICALL _M4DScaleDEF(void *_m,double *v)
	{
		double *_matrix=(double *)_m;
		_CleanMemDEF(_m,8*16);
		_matrix[0]=v[0];
		_matrix[5]=v[1];
		_matrix[10]=v[2];
		_matrix[15]=1;
	}

	// ************** create Translate Rotate Scale matrix function *******************

	void _APICALL _M4FTRSDEF(void * _m,float * _a,float * _b,float * _c)
	{
		float *_matrixb=(float *)_m;
		float f[12];
		float d[9];
		float s=2.0f/(_b[0]*_b[0]+_b[1]*_b[1]+_b[2]*_b[2]+_b[3]*_b[3]);
		f[0]=_b[0]*s;
		f[1]=_b[1]*s;
		f[2]=_b[2]*s;
		f[3]=f[0]*_b[0];
		f[4]=f[1]*_b[0];
		f[5]=f[2]*_b[0];
		f[6]=_b[1]*f[1];
		f[7]=_b[1]*f[2];
		f[8]=_b[2]*f[2];
		f[9]=f[0]*_b[3];
		f[10]=f[1]*_b[3];
		f[11]=f[2]*_b[3];

		d[0]=1.0f-(f[6]+f[8]);
		d[1]=1.0f-(f[3]+f[8]);
		d[2]=1.0f-(f[3]+f[6]);
		d[3]=f[4]+f[11];
		d[5]=f[5]+f[10];
		d[7]=f[7]+f[9];
		d[4]=f[4]-f[11];
		d[6]=f[5]-f[10];
		d[8]=f[7]-f[9];

		_matrixb[0]=d[0]*_c[0];
		_matrixb[1]=d[4]*_c[0];
		_matrixb[2]=d[5]*_c[0];
		_matrixb[3]=0;
		_matrixb[4]=d[3]*_c[1];
		_matrixb[5]=d[1]*_c[1];
		_matrixb[6]=d[8]*_c[1];
		_matrixb[7]=0;
		_matrixb[8]=d[6]*_c[2];
		_matrixb[9]=d[7]*_c[2];
		_matrixb[10]=d[2]*_c[2];
		_matrixb[11]=0;
		_matrixb[12]=_a[0];
		_matrixb[13]=_a[1];
		_matrixb[14]=_a[2];
		_matrixb[15]=1;
	}

	void _APICALL _M4DTRSDEF(void * _m,double * _a,double * _b,double * _c)
	{
		double *_matrixb=(double *)_m;
		double f[12];
		double d[9];
		double s=2.0f/(_b[0]*_b[0]+_b[1]*_b[1]+_b[2]*_b[2]+_b[3]*_b[3]);
		f[0]=_b[0]*s;
		f[1]=_b[1]*s;
		f[2]=_b[2]*s;
		f[3]=f[0]*_b[0];
		f[4]=f[1]*_b[0];
		f[5]=f[2]*_b[0];
		f[6]=_b[1]*f[1];
		f[7]=_b[1]*f[2];
		f[8]=_b[2]*f[2];
		f[9]=f[0]*_b[3];
		f[10]=f[1]*_b[3];
		f[11]=f[2]*_b[3];

		d[0]=1.0f-(f[6]+f[8]);
		d[1]=1.0f-(f[3]+f[8]);
		d[2]=1.0f-(f[3]+f[6]);
		d[3]=f[4]+f[11];
		d[5]=f[5]+f[10];
		d[7]=f[7]+f[9];
		d[4]=f[4]-f[11];
		d[6]=f[5]-f[10];
		d[8]=f[7]-f[9];

		_matrixb[0]=d[0]*_c[0];
		_matrixb[1]=d[4]*_c[0];
		_matrixb[2]=d[5]*_c[0];
		_matrixb[3]=0;
		_matrixb[4]=d[3]*_c[1];
		_matrixb[5]=d[1]*_c[1];
		_matrixb[6]=d[8]*_c[1];
		_matrixb[7]=0;
		_matrixb[8]=d[6]*_c[2];
		_matrixb[9]=d[7]*_c[2];
		_matrixb[10]=d[2]*_c[2];
		_matrixb[11]=0;
		_matrixb[12]=_a[0];
		_matrixb[13]=_a[1];
		_matrixb[14]=_a[2];
		_matrixb[15]=1;
	}

	// ************** matrix to default function *******************

	void _APICALL _M4FTo4DDEF(void *_mf,void *_md)
	{
		float *_matrixf=(float *)_mf;
		double *_matrixd=(double *)_md;
		_matrixd[0]=_matrixf[0];
		_matrixd[1]=_matrixf[1];
		_matrixd[2]=_matrixf[2];
		_matrixd[3]=_matrixf[3];
		_matrixd[4]=_matrixf[4];
		_matrixd[5]=_matrixf[5];
		_matrixd[6]=_matrixf[6];
		_matrixd[7]=_matrixf[7];
		_matrixd[8]=_matrixf[8];
		_matrixd[9]=_matrixf[9];
		_matrixd[10]=_matrixf[10];
		_matrixd[11]=_matrixf[11];
		_matrixd[12]=_matrixf[12];
		_matrixd[13]=_matrixf[13];
		_matrixd[14]=_matrixf[14];
		_matrixd[15]=_matrixf[15];
	}

	void _APICALL _M4DTo4FDEF(void *_md,void *_mf)
	{
		double *_matrixd=(double *)_md;
		float *_matrixf=(float *)_mf;
		_matrixf[0]=(float)_matrixd[0];
		_matrixf[1]=(float)_matrixd[1];
		_matrixf[2]=(float)_matrixd[2];
		_matrixf[3]=(float)_matrixd[3];
		_matrixf[4]=(float)_matrixd[4];
		_matrixf[5]=(float)_matrixd[5];
		_matrixf[6]=(float)_matrixd[6];
		_matrixf[7]=(float)_matrixd[7];
		_matrixf[8]=(float)_matrixd[8];
		_matrixf[9]=(float)_matrixd[9];
		_matrixf[10]=(float)_matrixd[10];
		_matrixf[11]=(float)_matrixd[11];
		_matrixf[12]=(float)_matrixd[12];
		_matrixf[13]=(float)_matrixd[13];
		_matrixf[14]=(float)_matrixd[14];
		_matrixf[15]=(float)_matrixd[15];
	}

	// ************** matrix mul translate vector default function *******************

	void _APICALL _M4FAddTranslateDEF(void *_ma,float *v,void *_mb)
	{
		float *_matrixa=(float *)_ma;
		float *_matrixb=(float *)_mb;
		_matrixb[0]=_matrixa[0];
		_matrixb[1]=_matrixa[1];
		_matrixb[2]=_matrixa[2];
		_matrixb[3]=_matrixa[3];
		_matrixb[4]=_matrixa[4];
		_matrixb[5]=_matrixa[5];
		_matrixb[6]=_matrixa[6];
		_matrixb[7]=_matrixa[7];
		_matrixb[8]=_matrixa[8];
		_matrixb[9]=_matrixa[9];
		_matrixb[10]=_matrixa[10];
		_matrixb[11]=_matrixa[11];
		_matrixb[12]=_matrixa[0]*v[0]+_matrixa[4]*v[1]+_matrixa[8]*v[2]+_matrixa[12];
		_matrixb[13]=_matrixa[1]*v[0]+_matrixa[5]*v[1]+_matrixa[9]*v[2]+_matrixa[13];
		_matrixb[14]=_matrixa[2]*v[0]+_matrixa[6]*v[1]+_matrixa[10]*v[2]+_matrixa[14];
		_matrixb[15]=_matrixa[3]*v[0]+_matrixa[7]*v[1]+_matrixa[11]*v[2]+_matrixa[15];
	}

	void _APICALL _M4DAddTranslateDEF(void *_ma,double *v,void *_mb)
	{
		double *_matrixa=(double *)_ma;
		double *_matrixb=(double *)_mb;
		_matrixb[0]=_matrixa[0];
		_matrixb[1]=_matrixa[1];
		_matrixb[2]=_matrixa[2];
		_matrixb[3]=_matrixa[3];
		_matrixb[4]=_matrixa[4];
		_matrixb[5]=_matrixa[5];
		_matrixb[6]=_matrixa[6];
		_matrixb[7]=_matrixa[7];
		_matrixb[8]=_matrixa[8];
		_matrixb[9]=_matrixa[9];
		_matrixb[10]=_matrixa[10];
		_matrixb[11]=_matrixa[11];
		_matrixb[12]=_matrixa[0]*v[0]+_matrixa[4]*v[1]+_matrixa[8]*v[2]+_matrixa[12];
		_matrixb[13]=_matrixa[1]*v[0]+_matrixa[5]*v[1]+_matrixa[9]*v[2]+_matrixa[13];
		_matrixb[14]=_matrixa[2]*v[0]+_matrixa[6]*v[1]+_matrixa[10]*v[2]+_matrixa[14];
		_matrixb[15]=_matrixa[3]*v[0]+_matrixa[7]*v[1]+_matrixa[11]*v[2]+_matrixa[15];
	}

	// ************** matrix mul scale vector default function *******************

	void _APICALL _M4FAddScaleDEF(void *_ma,float *v,void *_mb)
	{
		float *_matrixa=(float *)_ma;
		float *_matrixb=(float *)_mb;
		_matrixb[0]=_matrixa[0]*v[0];
		_matrixb[1]=_matrixa[1]*v[0];
		_matrixb[2]=_matrixa[2]*v[0];
		_matrixb[3]=_matrixa[3]*v[0];
		_matrixb[4]=_matrixa[4]*v[1];
		_matrixb[5]=_matrixa[5]*v[1];
		_matrixb[6]=_matrixa[6]*v[1];
		_matrixb[7]=_matrixa[7]*v[1];
		_matrixb[8]=_matrixa[8]*v[2];
		_matrixb[9]=_matrixa[9]*v[2];
		_matrixb[10]=_matrixa[10]*v[2];
		_matrixb[11]=_matrixa[11]*v[2];
		_matrixb[12]=_matrixa[12];
		_matrixb[13]=_matrixa[13];
		_matrixb[14]=_matrixa[14];
		_matrixb[15]=_matrixa[15];
	}

	void _APICALL _M4DAddScaleDEF(void *_ma,double *v,void *_mb)
	{
		double *_matrixa=(double *)_ma;
		double *_matrixb=(double *)_mb;
		_matrixb[0]=_matrixa[0]*v[0];
		_matrixb[1]=_matrixa[1]*v[0];
		_matrixb[2]=_matrixa[2]*v[0];
		_matrixb[3]=_matrixa[3]*v[0];
		_matrixb[4]=_matrixa[4]*v[1];
		_matrixb[5]=_matrixa[5]*v[1];
		_matrixb[6]=_matrixa[6]*v[1];
		_matrixb[7]=_matrixa[7]*v[1];
		_matrixb[8]=_matrixa[8]*v[2];
		_matrixb[9]=_matrixa[9]*v[2];
		_matrixb[10]=_matrixa[10]*v[2];
		_matrixb[11]=_matrixa[11]*v[2];
		_matrixb[12]=_matrixa[12];
		_matrixb[13]=_matrixa[13];
		_matrixb[14]=_matrixa[14];
		_matrixb[15]=_matrixa[15];
	}

	// ************** matrix mul rotation quaternion default function *******************

	void _APICALL _M4FAddRotateDEF(void * _a,float * _b,void * _c) {
		float *_matrixa=(float *)_a;
		float *_matrixb=(float *)_c;
		float f[12];
		float d[9];
		float s=2.0f/(_b[0]*_b[0]+_b[1]*_b[1]+_b[2]*_b[2]+_b[3]*_b[3]);
		f[0]=_b[0]*s;
		f[1]=_b[1]*s;
		f[2]=_b[2]*s;
		f[3]=f[0]*_b[0];
		f[4]=f[1]*_b[0];
		f[5]=f[2]*_b[0];
		f[6]=_b[1]*f[1];
		f[7]=_b[1]*f[2];
		f[8]=_b[2]*f[2];
		f[9]=f[0]*_b[3];
		f[10]=f[1]*_b[3];
		f[11]=f[2]*_b[3];

		d[0]=1.0f-(f[6]+f[8]);
		d[1]=1.0f-(f[3]+f[8]);
		d[2]=1.0f-(f[3]+f[6]);
		d[3]=f[4]+f[11];
		d[5]=f[5]+f[10];
		d[7]=f[7]+f[9];
		d[4]=f[4]-f[11];
		d[6]=f[5]-f[10];
		d[8]=f[7]-f[9];

		float r[12];

		r[0]=_matrixa[0]*d[0]+_matrixa[4]*d[4]+_matrixa[8]*d[5];
		r[1]=_matrixa[1]*d[0]+_matrixa[5]*d[4]+_matrixa[9]*d[5];
		r[2]=_matrixa[2]*d[0]+_matrixa[6]*d[4]+_matrixa[10]*d[5];
		r[3]=_matrixa[3]*d[0]+_matrixa[7]*d[4]+_matrixa[11]*d[5];
		r[4]=_matrixa[0]*d[3]+_matrixa[4]*d[1]+_matrixa[8]*d[8];
		r[5]=_matrixa[1]*d[3]+_matrixa[5]*d[1]+_matrixa[9]*d[8];
		r[6]=_matrixa[2]*d[3]+_matrixa[6]*d[1]+_matrixa[10]*d[8];
		r[7]=_matrixa[3]*d[3]+_matrixa[7]*d[1]+_matrixa[11]*d[8];
		r[8]=_matrixa[0]*d[6]+_matrixa[4]*d[7]+_matrixa[8]*d[2];
		r[9]=_matrixa[1]*d[6]+_matrixa[5]*d[7]+_matrixa[9]*d[2];
		r[10]=_matrixa[2]*d[6]+_matrixa[6]*d[7]+_matrixa[10]*d[2];
		r[11]=_matrixa[3]*d[6]+_matrixa[7]*d[7]+_matrixa[11]*d[2];
		_matrixb[0]=r[0];
		_matrixb[1]=r[1];
		_matrixb[2]=r[2];
		_matrixb[3]=r[3];
		_matrixb[4]=r[4];
		_matrixb[5]=r[5];
		_matrixb[6]=r[6];
		_matrixb[7]=r[7];
		_matrixb[8]=r[8];
		_matrixb[9]=r[9];
		_matrixb[10]=r[10];
		_matrixb[11]=r[11];
		_matrixb[12]=_matrixa[12];
		_matrixb[13]=_matrixa[13];
		_matrixb[14]=_matrixa[14];
		_matrixb[15]=_matrixa[15];
	}

	void _APICALL _M4DAddRotateDEF(void * _a,double * _b,void * _c) {
		double *_matrixa=(double *)_a;
		double *_matrixb=(double *)_c;
		double f[12];
		double d[9];
		double s=2.0f/(_b[0]*_b[0]+_b[1]*_b[1]+_b[2]*_b[2]+_b[3]*_b[3]);
		f[0]=_b[0]*s;
		f[1]=_b[1]*s;
		f[2]=_b[2]*s;
		f[3]=f[0]*_b[0];
		f[4]=f[1]*_b[0];
		f[5]=f[2]*_b[0];
		f[6]=_b[1]*f[1];
		f[7]=_b[1]*f[2];
		f[8]=_b[2]*f[2];
		f[9]=f[0]*_b[3];
		f[10]=f[1]*_b[3];
		f[11]=f[2]*_b[3];

		d[0]=1.0f-(f[6]+f[8]);
		d[1]=1.0f-(f[3]+f[8]);
		d[2]=1.0f-(f[3]+f[6]);
		d[3]=f[4]+f[11];
		d[5]=f[5]+f[10];
		d[7]=f[7]+f[9];
		d[4]=f[4]-f[11];
		d[6]=f[5]-f[10];
		d[8]=f[7]-f[9];

		double r[12];

		r[0]=_matrixa[0]*d[0]+_matrixa[4]*d[4]+_matrixa[8]*d[5];
		r[1]=_matrixa[1]*d[0]+_matrixa[5]*d[4]+_matrixa[9]*d[5];
		r[2]=_matrixa[2]*d[0]+_matrixa[6]*d[4]+_matrixa[10]*d[5];
		r[3]=_matrixa[3]*d[0]+_matrixa[7]*d[4]+_matrixa[11]*d[5];
		r[4]=_matrixa[0]*d[3]+_matrixa[4]*d[1]+_matrixa[8]*d[8];
		r[5]=_matrixa[1]*d[3]+_matrixa[5]*d[1]+_matrixa[9]*d[8];
		r[6]=_matrixa[2]*d[3]+_matrixa[6]*d[1]+_matrixa[10]*d[8];
		r[7]=_matrixa[3]*d[3]+_matrixa[7]*d[1]+_matrixa[11]*d[8];
		r[8]=_matrixa[0]*d[6]+_matrixa[4]*d[7]+_matrixa[8]*d[2];
		r[9]=_matrixa[1]*d[6]+_matrixa[5]*d[7]+_matrixa[9]*d[2];
		r[10]=_matrixa[2]*d[6]+_matrixa[6]*d[7]+_matrixa[10]*d[2];
		r[11]=_matrixa[3]*d[6]+_matrixa[7]*d[7]+_matrixa[11]*d[2];
		_matrixb[0]=r[0];
		_matrixb[1]=r[1];
		_matrixb[2]=r[2];
		_matrixb[3]=r[3];
		_matrixb[4]=r[4];
		_matrixb[5]=r[5];
		_matrixb[6]=r[6];
		_matrixb[7]=r[7];
		_matrixb[8]=r[8];
		_matrixb[9]=r[9];
		_matrixb[10]=r[10];
		_matrixb[11]=r[11];
		_matrixb[12]=_matrixa[12];
		_matrixb[13]=_matrixa[13];
		_matrixb[14]=_matrixa[14];
		_matrixb[15]=_matrixa[15];
	}

}

OPTIMIZE_OFF;
WARNING_ENABLE;
