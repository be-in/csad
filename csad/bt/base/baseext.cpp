//=============================================================================
///**
// *  @file defext.cpp
// *
// *  $Id: defext.cpp 23.05.2012  $
// *
// *  @brief generator 3 tool, MS Visual C++ 2003-2008
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#include "baseext.h"
#include "basevector.h"
#include "basemath.h"
#include <bt.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

	_int64 _APICALL _TSCDEFF()
	{
		return 0;
	}

	unsigned _int32 _APICALL _GetFuncFlagDEF()
	{
		return 0;
	}

	void* _APICALL _CreateMemDEF(unsigned _int32 _size,unsigned _int32)
	{
		if (_size==0) return 0;
		void *h;
		void **block=0;
		h=(void*)LocalAlloc(LMEM_FIXED,_size+sizeof(void*));
		block=(void**)LocalLock(h);
		if (block) {
			*block=h;
			block++;
		}
		return (char*)block;
		//return new char[_size];
	}

	bool _APICALL _DeleteMemDEF(void *mem,unsigned _int32)
	{
		if (!mem) return false;
		void **h=(void **)mem;
		h--;
		LocalUnlock((HLOCAL)*h);
		LocalFree((HLOCAL)*h);
		//delete[] (char*)mem;
		return true;
	}

	void* _APICALL _ResizeMemDEF(void *mem,unsigned _int32 _size,unsigned _int32)
	{
		unsigned _int32 _lsize=0;
		void **lh=(void **)mem;
		if (lh) {
			lh--;
			_lsize=LocalSize((HLOCAL)*lh);
		}

		if (_size==0) return 0;
		void *h;
		void **block=0;
		h=(void*)LocalAlloc(LMEM_FIXED,_size+sizeof(void*));
		block=(void**)LocalLock(h);
		if (block) {
			*block=h;
			block++;
		}
		if (mem) {
			if (_lsize>_size) _lsize=_size;
			extFunctions.MoveMem(mem,block,_lsize);
			LocalUnlock((HLOCAL)*lh);
			LocalFree((HLOCAL)*lh);
		}
		return (char*)block;
		//return new char[_size];
	} 

	void _APICALL _CleanMemDEF(void *_mem,unsigned _int32 _size)
	{
		char *e1=((char *)_mem)+_size;
		_size=_size>>2;
		_int32 *e4=((_int32 *)_mem)+_size;
		_int32 *p4=(_int32 *)_mem;
		while (p4<e4) {
			*p4=0;
			p4++;
		}
		char *p1=(char *)p4;
		while (p1<e1) {
			*p1=0;
			p1++;
		}
	}

	void _APICALL _MoveMemDEF(void *_src,void *_dst,unsigned _int32 _size)
	{
		_int32 *d4=(_int32 *)_dst;
		_int32 *s4=(_int32 *)_src;
		unsigned _int32 s=_size & 0x3;
		_size=_size>>2;
		for (unsigned _int32 i=0;i<_size;i++) {
			*d4=*s4;
			d4++;
			s4++;
		}
		char *d1=(char *)d4;
		char *s1=(char *)s4;
		for (unsigned _int32 i=0;i<s;i++) {
			d1[i]=s1[i];
		}
	}

	void _APICALL _MoveBackDEF(void *_src,void *_dst,unsigned _int32 _size)
	{
		_int32 *d4=(_int32 *)((char*)_dst+_size);
		_int32 *s4=(_int32 *)((char*)_src+_size);
		unsigned _int32 s=_size & 0x3;
		_size=_size>>2;
		for (unsigned _int32 i=0;i<_size;i++) {
			d4--;
			s4--;
			*d4=*s4;
		}
		char *d1=(char *)d4;
		char *s1=(char *)s4;
		for (unsigned _int32 i=0;i<s;i++) {
			s1--;
			d1--;
			*d1=*s1;
		}
	}


	void _APICALL _SwapMemDEF(void *_src,void *_dst,unsigned _int32 _size)
	{
		_int32 *d4=(_int32 *)_dst;
		_int32 *s4=(_int32 *)_src;
		_int32 a;
		unsigned _int32 s=_size & 0x3;
		_size=_size>>2;
		for (unsigned _int32 i=0;i<_size;i++) {
			a=*d4;
			*d4=*s4;
			*s4=a;
			d4++;
			s4++;
		}
		char *d1=(char *)d4;
		char *s1=(char *)s4;
		char b;
		for (unsigned _int32 i=0;i<s;i++) {
			b=d1[i];
			d1[i]=s1[i];
			s1[i]=b;
		}
	}

	void _APICALL _StocBMemDEF(void *_dst,unsigned _int32 _count,unsigned _int32 _val)
	{
		unsigned char *d41=(unsigned char *)_dst;
		_val=(_val<<8)+(_val & 0xFF);
		_val=(_val<<16)+_val;
		if (_count & 1) {
			*d41=_val;
			d41++;
		}
		unsigned short *d42=(unsigned short *)d41;
		if (_count & 2) {
			*d42=_val;
			d42++;
		}
		unsigned _int32 *d4=(unsigned _int32 *)d42;
		unsigned _int32 *e4=d4+(_count>>2);
		while (d4<e4) {
			*d4=_val;
			d4++;
		}
	}

	void _APICALL _StocSMemDEF(void *_dst,unsigned _int32 _count,unsigned _int32 _val)
	{
		unsigned short *d41=(unsigned short *)_dst;
		_val=(_val<<16)+(_val & 0xFFFF);
		if (_count & 1) {
			*d41=_val;
			d41++;
		}
		unsigned _int32 *d4=(unsigned _int32 *)d41;
		unsigned _int32 *e4=d4+(_count>>1);
		while (d4<e4) {
			*d4=_val;
			d4++;
		}
	}

	void _APICALL _StocIMemDEF(void *_dst,unsigned _int32 _count,unsigned _int32 _val)
	{
		unsigned _int32 *d4=(unsigned _int32 *)_dst;
		unsigned _int32 *e4=d4+_count;
		while (d4<e4) {
			*d4=_val;
			d4++;
		}
	}

	_int32 _APICALL _CmpMemDEF(void *_src,void *_dst,unsigned _int32 _size)
	{
		_int32 *d4=(_int32 *)_dst;
		_int32 *s4=(_int32 *)_src;
		unsigned _int32 s=_size & 0x3;
		_size=_size>>2;
		for (unsigned _int32 i=0;i<_size;i++) {
			if (*d4!=*s4) return i;
			d4++;
			s4++;
		}
		char *d1=(char *)d4;
		char *s1=(char *)s4;
		for (unsigned _int32 i=0;i<s;i++) {
			if (d1[i]!=s1[i]) return i;
		}
		return -1;
	}

	_int32 _APICALL _SubMemDEF(void *_src,void *_dst,unsigned _int32 _size)
	{
		_int32 *d4=(_int32 *)_dst;
		_int32 *s4=(_int32 *)_src;
		unsigned _int32 s=_size & 0x3;
		char *d1=(char *)d4;
		char *s1=(char *)s4;
		_size=_size>>2;
		for (unsigned _int32 i=0;i<_size;i++) {
			if (*d4!=*s4) {
				d1=(char *)d4;
				s1=(char *)s4;
				if (d1[0]!=s1[0]) return d1[0]-s1[0];
				if (d1[1]!=s1[1]) return d1[1]-s1[1];
				if (d1[2]!=s1[2]) return d1[2]-s1[2];
				if (d1[3]!=s1[3]) return d1[3]-s1[3];
			}
			d4++;
			s4++;
		}
		d1=(char *)d4;
		s1=(char *)s4;
		for (unsigned _int32 i=0;i<s;i++) {
			if (d1[i]!=s1[i]) return d1[i]-s1[i];
		}
		return 0;
	}

	_int32 _APICALL _CmpMoveMemDEF(void *_src,void *_dst,unsigned _int32 _size)
	{
		_int32 *d4=(_int32 *)_dst;
		_int32 *s4=(_int32 *)_src;
		unsigned _int32 s=_size & 0x3;
		_size=_size>>2;
		_int32 ret=0;
		for (unsigned _int32 i=0;i<_size;i++) {
			if (*d4!=*s4) ret=i;
			*d4=*s4;
			d4++;
			s4++;
		}
		char *d1=(char *)d4;
		char *s1=(char *)s4;
		for (unsigned _int32 i=0;i<s;i++) {
			if (d1[i]!=s1[i]) ret=i;
			d1[i]=s1[i];
		}
		return ret;
	}

// ************** FindMem default function *******************

	_int32 _APICALL _FindCMemDEF(void *_src,unsigned _int32 _c,_int32 _size)
	{
		unsigned char *p=(unsigned char *)_src;
		_int32 size=_size;
		if (_size>0) {
			while (_size!=0 && (_c!=*p)) {
				_size--;
				p++;
			}
		} else {
			while (_size!=0 && (_c!=*p)) {
				_size++;
				p--;
			}
		}
		return size-_size;
	}

	_int32 _APICALL _FindSMemDEF(void *_src,unsigned _int32 _c,_int32 _size)
	{
		unsigned short *p=(unsigned short *)_src;
		_int32 size=_size;
		if (_size>0) {
			while (_size!=0 && _c!=*p) {
				_size--;
				p++;
			}
		} else {
			while (_size!=0 && _c!=*p) {
				_size++;
				p--;
			}
		}
		return size-_size;
	}

	_int32 _APICALL _FindIMemDEF(void *_src,unsigned _int32 _c,_int32 _size)
	{
		unsigned _int32 *p=(unsigned _int32 *)_src;
		_int32 size=_size;
		if (_size>0) {
			while ((_size!=0) && (_c!=*p)) {
				_size--;
				p++;
			}
		} else {
			while ((_size!=0) && (_c!=*p)) {
				_size++;
				p--;
			}
		}
		return size-_size;
	}

// ************** bits operations default function *******************

	void _APICALL _setbit(_int32 id, _int32 b, void* var)
	{
		unsigned _int32 *p=(unsigned _int32 *)var;
		p+=(id>>5);
		*p=(*p & (~(1<<(id & 0x1F)))) | (b<<(id & 0x1F));
	}

	_int32 _APICALL _getbit(_int32 id, void* var)
	{
		unsigned _int32 *p=(unsigned _int32 *)var;
		p+=(id>>5);
		return (*p>>(id & 0x1F)) & 1;
	}

// ************** FastMul default function *******************

	_int32 _APICALL _FastSTDMulI0(_int32 )
	{
		return 0;
	}

	_int32 _APICALL _FastSTDMulI1(_int32 _val)
	{
		return _val;
	}

	_int32 _APICALL _FastSTDMulI2(_int32 _val)
	{
		return (_val<<1);
	}

	_int32 _APICALL _FastSTDMulI3(_int32 _val)
	{
		return (_val<<1)+_val;
	}

	_int32 _APICALL _FastSTDMulI4(_int32 _val)
	{
		return (_val<<2);
	}

	_int32 _APICALL _FastSTDMulI5(_int32 _val)
	{
		return (_val<<2)+_val;
	}

	_int32 _APICALL _FastSTDMulI6(_int32 _val)
	{
		return ((_val<<1)+_val)<<1;
	}

	_int32 _APICALL _FastSTDMulI7(_int32 _val)
	{
		return (_val<<3)-_val;
	}

	_int32 _APICALL _FastSTDMulI8(_int32 _val)
	{
		return (_val<<3);
	}

	_int32 _APICALL _FastSTDMulI9(_int32 _val)
	{
		return (_val<<3)+_val;
	}

	_int32 _APICALL _FastSTDMulI10(_int32 _val)
	{
		return ((_val<<2)+_val)<<1;
	}

	_int32 _APICALL _FastSTDMulI16(_int32 _val)
	{
		return (_val<<4);
	}

	_int32 _APICALL _FastSTDMulI24(_int32 _val)
	{
		return ((_val<<1)+_val)<<3;
	}

	_int32 _APICALL _FastSTDMulI32(_int32 _val)
	{
		return (_val<<5);
	}

	tfSTDCALL_int_FUNC_int mulprocSTD[]={&_FastSTDMulI0,&_FastSTDMulI1,&_FastSTDMulI2,&_FastSTDMulI3,
			&_FastSTDMulI4,&_FastSTDMulI5,&_FastSTDMulI6,&_FastSTDMulI7,&_FastSTDMulI8,&_FastSTDMulI9,&_FastSTDMulI10};

	void* _APICALL _GetFastSTDMulI(_int32 _val)
	{
		if (_val<11) return (void*)mulprocSTD[_val];
		if (_val==16) return (void*)&_FastSTDMulI16;
		if (_val==24) return (void*)&_FastSTDMulI24;
		if (_val==32) return (void*)&_FastSTDMulI32;
		return 0;
	}

	_int32 _FASTCALL _FastFCMulI0(_int32)
	{
		return 0;
	}

	_int32 _FASTCALL _FastFCMulI1(_int32 _val)
	{
		return _val;
	}

	_int32 _FASTCALL _FastFCMulI2(_int32 _val)
	{
		return (_val<<1);
	}

	_int32 _FASTCALL _FastFCMulI3(_int32 _val)
	{
		return (_val<<1)+_val;
	}

	_int32 _FASTCALL _FastFCMulI4(_int32 _val)
	{
		return (_val<<2);
	}

	_int32 _FASTCALL _FastFCMulI5(_int32 _val)
	{
		return (_val<<2)+_val;
	}

	_int32 _FASTCALL _FastFCMulI6(_int32 _val)
	{
		return ((_val<<1)+_val)<<1;
	}

	_int32 _FASTCALL _FastFCMulI7(_int32 _val)
	{
		return (_val<<3)-_val;
	}

	_int32 _FASTCALL _FastFCMulI8(_int32 _val)
	{
		return (_val<<3);
	}

	_int32 _FASTCALL _FastFCMulI9(_int32 _val)
	{
		return (_val<<3)+_val;
	}

	_int32 _FASTCALL _FastFCMulI10(_int32 _val)
	{
		return ((_val<<2)+_val)<<1;
	}

	_int32 _FASTCALL _FastFCMulI16(_int32 _val)
	{
		return (_val<<4);
	}

	_int32 _FASTCALL _FastFCMulI24(_int32 _val)
	{
		return ((_val<<1)+_val)<<3;
	}

	_int32 _FASTCALL _FastFCMulI32(_int32 _val)
	{
		return (_val<<5);
	}

	_int32 _FASTCALL _FastFCMulI64(_int32 _val)
	{
		return (_val<<6);
	}

	tfFASTCALL_int_FUNC_int mulprocFC[]={&_FastFCMulI0,&_FastFCMulI1,&_FastFCMulI2,&_FastFCMulI3,
			&_FastFCMulI4,&_FastFCMulI5,&_FastFCMulI6,&_FastFCMulI7,&_FastFCMulI8,&_FastFCMulI9,&_FastFCMulI10};

	void* _APICALL _GetFastFCMulI(_int32 _val)
	{
		if (_val<11) return (void*)mulprocFC[_val];
		if (_val==16) return (void*)&_FastFCMulI16;
		if (_val==24) return (void*)&_FastFCMulI24;
		if (_val==32) return (void*)&_FastFCMulI32;
		if (_val==64) return (void*)&_FastFCMulI64;
		return 0;
	}

	// ************** vector MotionPoint default function *******************

#define _gen3toolabs(a) (a<0?-a:a)

	bool _NOINLINE _APICALL _FMotionPointDEF(float *It, float *SP, float Et, double timer)
	{
		float S = Et-It[0];
		if (timer>1.0) timer=1.0;
		float sSP=SP[0];
		float abS1=_gen3toolabs(S);
		float abSP1=_gen3toolabs(sSP);
		if (abSP1<abS1) sSP+=(float)((S-sSP)*timer);
		if (abSP1>abS1) sSP=S;
		SP[0]=sSP;
		sSP = It[0]+(float)(sSP*timer);
		S=Et-sSP;
		if (S<0) S=-S;
		It[0]=sSP;
		return S<0.0001;
	}

	bool _NOINLINE _APICALL _DMotionPointDEF(double *It, double *SP, double Et, double timer)
	{
		double S1 = Et-It[0];
		if (timer>1.0) timer=1.0;
		double SP1=SP[0];
		double abS1=_gen3toolabs(S1);
		double abSP1=_gen3toolabs(SP1);
		if (abSP1<abS1) SP1+=(S1-SP1)*timer;
		if (abSP1>abS1) SP1=S1;
		SP[0]=SP1;
		SP1 = It[0]+SP1*timer;
		S1=_gen3toolabs(Et-SP1);
		It[0]=SP1;
		return S1<0.0001;
	}

	bool _NOINLINE _APICALL _V2FMotionPointDEF(float *It, float *SP, float *Et, double timer)
	{
		float S[2];
		float sSP[2]={SP[0],SP[1]};
		float abS[2];
		float abSP[2];
		_V2FSubDEF(Et,It,S);
		if (timer>1.0) timer=1.0;
		_V2FAbsDEF(S,abS);
		_V2FAbsDEF(sSP,abSP);
		if (abSP[0]<abS[0]) sSP[0]+=(float)((S[0]-sSP[0])*timer);
		if (abSP[0]>abS[0]) sSP[0]=S[0];
		if (abSP[1]<abS[1]) sSP[1]+=(float)((S[1]-sSP[1])*timer);
		if (abSP[1]>abS[1]) sSP[1]=S[1];
		SP[0]=sSP[0];
		SP[1]=sSP[1];
		_V2FScaleDEF(sSP,sSP,timer);
		_V2FAddDEF(It,sSP,sSP);
		_V2FSubDEF(Et,It,S);
		_V2FAbsDEF(S,S);
		It[0]=sSP[0];
		It[1]=sSP[1];
		return S[0]<0.0001 && S[1]<0.0001;
	}

	bool _NOINLINE _APICALL _V2DMotionPointDEF(double *It, double *SP, double *Et, double timer)
	{
		double S[2];
		_V2DSubDEF(Et,It,S);
		if (timer>1.0) timer=1.0;
		double sSP[2]={SP[0],SP[1]};
		double abS[2];
		double abSP[2];
		_V2DAbsDEF(S,abS);
		_V2DAbsDEF(sSP,abSP);
		if (abSP[0]<abS[0]) sSP[0]+=(S[0]-sSP[0])*timer;
		if (abSP[0]>abS[0]) sSP[0]=S[0];
		if (abSP[1]<abS[1]) sSP[1]+=(S[1]-sSP[1])*timer;
		if (abSP[1]>abS[1]) sSP[1]=S[1];
		SP[0]=sSP[0];
		SP[1]=sSP[1];
		_V2DScaleDEF(sSP,sSP,timer);
		_V2DAddDEF(It,sSP,sSP);
		_V2DSubDEF(Et,It,S);
		_V2DAbsDEF(S,S);
		It[0]=sSP[0];
		It[1]=sSP[1];
		return S[0]<0.0001 && S[1]<0.0001;
	}

	bool _NOINLINE _APICALL _V3FMotionPointDEF(float *It, float *SP, float *Et, double timer)
	{
		float S[3];
		_V3FSubDEF(Et,It,S);
		if (timer>1.0) timer=1.0;
		float sSP[]={SP[0],SP[1],SP[2]};
		float abS[3];
		float abSP[3];
		_V3FAbsDEF(S,abS);
		_V3FAbsDEF(sSP,abSP);
		if (abSP[0]<abS[0]) sSP[0]+=(S[0]-sSP[0])*timer;
		if (abSP[0]>abS[0]) sSP[0]=S[0];
		if (abSP[1]<abS[1]) sSP[1]+=(S[1]-sSP[1])*timer;
		if (abSP[1]>abS[1]) sSP[1]=S[1];
		if (abSP[2]<abS[2]) sSP[2]+=(S[2]-sSP[2])*timer;
		if (abSP[2]>abS[2]) sSP[2]=S[2];
		_V3R32CopyDEF(sSP,SP);
		_V3FScaleDEF(sSP,sSP,timer);
		_V3FAddDEF(It,sSP,sSP);
		_V3FSubDEF(Et,sSP,S);
		_V3FAbsDEF(S,S);
		_V3R32CopyDEF(sSP,It);
		return S[0]<0.0001 && S[1]<0.0001 && S[2]<0.0001;
	}

	bool _NOINLINE _APICALL _V3DMotionPointDEF(double *It, double *SP, double *Et, double timer)
	{
		double S[3];
		_V3DSubDEF(Et,It,S);
		if (timer>1.0) timer=1.0;
		double sSP[3];
		_V3R64CopyDEF(SP,sSP);
		double abS[3];
		double abSP[3];
		_V3DAbsDEF(S,abS);
		_V3DAbsDEF(sSP,abSP);
		if (abSP[0]<abS[0]) sSP[0]+=(S[0]-sSP[0])*timer;
		if (abSP[0]>abS[0]) sSP[0]=S[0];
		if (abSP[1]<abS[1]) sSP[1]+=(S[1]-sSP[1])*timer;
		if (abSP[1]>abS[1]) sSP[1]=S[1];
		if (abSP[2]<abS[2]) sSP[2]+=(S[2]-sSP[2])*timer;
		if (abSP[2]>abS[2]) sSP[2]=S[2];
		_V3R64CopyDEF(sSP,SP);
		_V3DScaleDEF(sSP,sSP,timer);
		_V3DAddDEF(It,sSP,sSP);
		_V3DSubDEF(Et,sSP,S);
		_V3DAbsDEF(S,S);
		_V3R64CopyDEF(sSP,It);
		return S[0]<0.0001 && S[1]<0.0001 && S[2]<0.0001;
	}

	bool _NOINLINE _APICALL _V4FMotionPointDEF(float *It, float *SP, float *Et, double timer)
	{
		float S[4];
		_V4FSubDEF(Et,It,S);
		if (timer>1.0) timer=1.0;
		float sSP[4]={SP[0],SP[1],SP[2],SP[3]};
		float abS[4];
		float abSP[4];
		_V4FAbsDEF(S,abS);
		_V4FAbsDEF(sSP,abSP);
		if (abSP[0]<abS[0]) sSP[0]+=(S[0]-sSP[0])*timer;
		if (abSP[0]>abS[0]) sSP[0]=S[0];
		if (abSP[1]<abS[1]) sSP[1]+=(S[1]-sSP[1])*timer;
		if (abSP[1]>abS[1]) sSP[1]=S[1];
		if (abSP[2]<abS[2]) sSP[2]+=(S[2]-sSP[2])*timer;
		if (abSP[2]>abS[2]) sSP[2]=S[2];
		if (abSP[3]<abS[3]) sSP[3]+=(S[3]-sSP[3])*timer;
		if (abSP[3]>abS[3]) sSP[3]=S[3];
		_V4R32CopyDEF(sSP,SP);
		_V4FScaleDEF(sSP,sSP,timer);
		_V4FAddDEF(It,sSP,sSP);
		_V4FSubDEF(Et,sSP,S);
		_V4FAbsDEF(S,S);
		_V4R32CopyDEF(sSP,It);
		return S[0]<0.0001 && S[1]<0.0001 && S[2]<0.0001 && S[3]<0.0001;
	}

	bool _NOINLINE _APICALL _V4DMotionPointDEF(double *It, double *SP, double *Et, double timer)
	{
		double S[4];
		_V4DSubDEF(Et,It,S);
		if (timer>1.0) timer=1.0;
		double sSP[4];
		_V4R64CopyDEF(SP,sSP);
		double abS[4];
		double abSP[4];
		_V4DAbsDEF(S,abS);
		_V4DAbsDEF(sSP,abSP);
		if (abSP[0]<abS[0]) sSP[0]+=(S[0]-sSP[0])*timer;
		if (abSP[0]>abS[0]) sSP[0]=S[0];
		if (abSP[1]<abS[1]) sSP[1]+=(S[1]-sSP[1])*timer;
		if (abSP[1]>abS[1]) sSP[1]=S[1];
		if (abSP[2]<abS[2]) sSP[2]+=(S[2]-sSP[2])*timer;
		if (abSP[2]>abS[2]) sSP[2]=S[2];
		if (abSP[3]<abS[3]) sSP[3]+=(S[3]-sSP[3])*timer;
		if (abSP[3]>abS[3]) sSP[3]=S[3];
		_V4R64CopyDEF(sSP,SP);
		_V4DScaleDEF(sSP,sSP,timer);
		_V4DAddDEF(It,sSP,sSP);
		_V4DSubDEF(Et,sSP,S);
		_V4DAbsDEF(S,S);
		_V4R64CopyDEF(sSP,It);
		return S[0]<0.0001 && S[1]<0.0001 && S[2]<0.0001 && S[3]<0.0001;
	}

	// ************** vector MotionRad default function *******************

	bool _NOINLINE _APICALL _FMotionRadDEF(float *It, float* SP, float Et, double timer)
	{
		float S1 = Et-It[0];
		S1-=(_FTruncDEF(S1*API2))*PI*2.0f;
		if (S1>PI) S1-=(float)(PI*2.0f);
		if (S1<-PI) S1+=(float)(PI*2.0f);
		if (timer>1.0) timer=1.0;
		float SP1=SP[0];
		float abS1=_gen3toolabs(S1);
		float abSP1=_gen3toolabs(SP1);
		if (abSP1<abS1) SP1+=(float)((S1-SP1)*timer);
		if (abSP1>abS1) SP1=S1;
		SP[0]=SP1;
		SP1 = It[0]+(float)(SP1*timer);
		S1=Et-SP1;
		S1-=(_FTruncDEF(S1*API2))*PI*2.0f;
		if (S1>PI) S1-=(float)(PI*2.0f);
		if (S1<-PI) S1+=(float)(PI*2.0f);
		if (S1<0) S1=-S1;
		It[0]=SP1;
		return S1<0.0001f;
	}

	bool _NOINLINE _APICALL _DMotionRadDEF(double *It, double* SP, double Et, double timer)
	{
		double S1 = Et-It[0];
		S1-=(_DTruncDEF(S1*API2))*PI*2.0;
		if (S1>PI) S1-=PI*2.0;
		if (S1<-PI) S1+=PI*2.0;
		if (timer>1.0) timer=1.0;
		double SP1=SP[0];
		double abS1=_gen3toolabs(S1);
		double abSP1=_gen3toolabs(SP1);
		if (abSP1<abS1) SP1+=(double)((S1-SP1)*timer);
		if (abSP1>abS1) SP1=S1;
		SP[0]=SP1;
		SP1 = It[0]+(double)(SP1*timer);
		S1=Et-SP1;
		S1-=(_DTruncDEF(S1*API2))*PI*2.0;
		if (S1>PI) S1-=PI*2.0;
		if (S1<-PI) S1+=PI*2.0;
		if (S1<0) S1=-S1;
		It[0]=SP1;
		return S1<0.0001;
	}

	bool _NOINLINE _APICALL _V2FMotionRadDEF(float *It, float* SP, float *Et, double timer)
	{
		float S[2];
		float sSP[2];
		_V2FSubDEF(Et,It,S);
		_V2FScaleModDEF(S,S,PI2F);
		if (S[0]>PI) S[0]-=PI2F;
		if (S[1]>PI) S[1]-=PI2F;
		if (S[0]<-PI) S[0]+=PI2F;
		if (S[1]<-PI) S[1]+=PI2F;
		if (timer>1.0) timer=1.0;
		_V2R32CopyDEF(SP,sSP);
		float abS[2];
		float abSP[2];
		_V2FAbsDEF(S,abS);
		_V2FAbsDEF(SP,abSP);
		if (abSP[0]<abS[0]) sSP[0]+=(float)((S[0]-sSP[0])*timer);
		if (abSP[1]<abS[1]) sSP[1]+=(float)((S[1]-sSP[1])*timer);
		if (abSP[0]>abS[0]) sSP[0]=S[0];
		if (abSP[1]>abS[1]) sSP[1]=S[1];
		_V2R32CopyDEF(sSP,SP);
		_V2FScaleDEF(sSP,sSP,timer);
		_V2FAddDEF(It,sSP,sSP);
		_V2FSubDEF(Et,sSP,S);
		S[0]-=(_FTruncDEF(S[0]*API2))*PI*2.0;
		S[1]-=(_FTruncDEF(S[1]*API2))*PI*2.0;
		if (S[0]>PI) S[0]-=(float)PI*2.0;
		if (S[1]>PI) S[1]-=(float)PI*2.0;
		if (S[0]<-PI) S[0]+=(float)PI*2.0;
		if (S[1]<-PI) S[1]+=(float)PI*2.0;
		_V2FAbsDEF(S,S);
		_V2R32CopyDEF(sSP,It);
		return S[0]<0.0001 && S[1]<0.0001;
	}

	bool _NOINLINE _APICALL _V2DMotionRadDEF(double *It, double* SP, double *Et, double timer)
	{
		double S[2];
		double sSP[2];
		_V2DSubDEF(Et,It,S);
		S[0]-=(_DTruncDEF(S[0]*API2))*PI2;
		S[1]-=(_DTruncDEF(S[1]*API2))*PI*2.0;
		if (S[0]>PI) S[0]-=PI2;
		if (S[1]>PI) S[1]-=PI*2.0;
		if (S[0]<-PI) S[0]+=PI*2.0;
		if (S[1]<-PI) S[1]+=PI*2.0;
		if (timer>1.0) timer=1.0;
		_V2R64CopyDEF(SP,sSP);
		double abS[2];
		double abSP[2];
		_V2DAbsDEF(S,abS);
		_V2DAbsDEF(SP,abSP);
		if (abSP[0]<abS[0]) sSP[0]+=(double)((S[0]-sSP[0])*timer);
		if (abSP[1]<abS[1]) sSP[1]+=(double)((S[1]-sSP[1])*timer);
		if (abSP[0]>abS[0]) sSP[0]=S[0];
		if (abSP[1]>abS[1]) sSP[1]=S[1];
		_V2R64CopyDEF(sSP,SP);
		_V2DScaleDEF(sSP,sSP,timer);
		_V2DAddDEF(It,sSP,sSP);
		_V2DSubDEF(Et,sSP,S);
		S[0]-=(_DTruncDEF(S[0]*API2))*PI*2.0;
		S[1]-=(_DTruncDEF(S[1]*API2))*PI*2.0;
		if (S[0]>PI) S[0]-=PI*2.0;
		if (S[1]>PI) S[1]-=PI*2.0;
		if (S[0]<-PI) S[0]+=PI*2.0;
		if (S[1]<-PI) S[1]+=PI*2.0;
		_V2DAbsDEF(S,S);
		_V2R64CopyDEF(sSP,It);
		return S[0]<0.0001 && S[1]<0.0001;
	}

	bool _NOINLINE _APICALL _V3FMotionRadDEF(float *It, float* SP, float *Et, double timer)
	{
		float S[3];
		float sSP[3];
		_V3FSubDEF(Et,It,S);
		_V3FScaleModDEF(S,S,PI2F);
		//_V3FRadLimitDEF(S,S,PIF);
		if (S[0]>PI) S[0]-=PI2F;
		if (S[1]>PI) S[1]-=PI2F;
		if (S[2]>PI) S[2]-=PI2F;
		if (S[0]<-PI) S[0]+=PI2F;
		if (S[1]<-PI) S[1]+=PI2F;
		if (S[2]<-PI) S[2]+=PI2F;
		if (timer>1.0) timer=1.0;
		_V3R32CopyDEF(SP,sSP);
		float abS[3];
		float abSP[3];
		_V3FAbsDEF(S,abS);
		_V3FAbsDEF(SP,abSP);
		if (abSP[0]<abS[0]) sSP[0]+=((S[0]-sSP[0])*timer);
		if (abSP[1]<abS[1]) sSP[1]+=((S[1]-sSP[1])*timer);
		if (abSP[2]<abS[2]) sSP[2]+=((S[2]-sSP[2])*timer);
		if (abSP[0]>abS[0]) sSP[0]=S[0];
		if (abSP[1]>abS[1]) sSP[1]=S[1];
		if (abSP[2]>abS[2]) sSP[2]=S[2];
		_V3R32CopyDEF(sSP,SP);
		_V3FCombineDEF(sSP,It,sSP,timer,1);
		_V3FSubDEF(Et,sSP,S);
		_V3FScaleModDEF(S,S,PI2F);
		//_V3DRadLimitDEF(S,S,PIF);
		if (S[0]>PI) S[0]-=PI2F;
		if (S[1]>PI) S[1]-=PI2F;
		if (S[2]>PI) S[2]-=PI2F;
		if (S[0]<-PI) S[0]+=PI2F;
		if (S[1]<-PI) S[1]+=PI2F;
		if (S[2]<-PI) S[2]+=PI2F;
		_V3FAbsDEF(S,S);
		_V3R32CopyDEF(sSP,It);
		return S[0]<0.0001f && S[1]<0.0001f && S[2]<0.0001f;
	}

	bool _NOINLINE _APICALL _V3DMotionRadDEF(double *It, double* SP, double *Et, double timer)
	{
		double S[3];
		double sSP[3];
		_V3DSubDEF(Et,It,S);
		_V3DScaleModDEF(S,S,PI2);
		//_V3DRadLimitDEF(S,S,PI);
		if (S[0]>PI) S[0]-=PI2;
		if (S[1]>PI) S[1]-=PI2;
		if (S[2]>PI) S[2]-=PI2;
		if (S[0]<-PI) S[0]+=PI2;
		if (S[1]<-PI) S[1]+=PI2;
		if (S[2]<-PI) S[2]+=PI2;
		if (timer>1.0) timer=1.0;
		_V3R64CopyDEF(SP,sSP);
		double abS[3];
		double abSP[3];
		_V3DAbsDEF(S,abS);
		_V3DAbsDEF(SP,abSP);
		if (abSP[0]<abS[0]) sSP[0]+=((S[0]-sSP[0])*timer);
		if (abSP[1]<abS[1]) sSP[1]+=((S[1]-sSP[1])*timer);
		if (abSP[2]<abS[2]) sSP[2]+=((S[2]-sSP[2])*timer);
		if (abSP[0]>abS[0]) sSP[0]=S[0];
		if (abSP[1]>abS[1]) sSP[1]=S[1];
		if (abSP[2]>abS[2]) sSP[2]=S[2];
		_V3R64CopyDEF(sSP,SP);
		_V3DCombineDEF(sSP,It,sSP,timer,1);
		_V3DSubDEF(Et,sSP,S);
		_V3DScaleModDEF(S,S,PI2);
		//_V3DRadLimitDEF(S,S,PI);
		if (S[0]>PI) S[0]-=PI2;
		if (S[1]>PI) S[1]-=PI2;
		if (S[2]>PI) S[2]-=PI2;
		if (S[0]<-PI) S[0]+=PI2;
		if (S[1]<-PI) S[1]+=PI2;
		if (S[2]<-PI) S[2]+=PI2;
		_V3DAbsDEF(S,S);
		_V3R64CopyDEF(sSP,It);
		return S[0]<0.0001 && S[1]<0.0001 && S[2]<0.0001;
	}

	bool _NOINLINE _APICALL _V4FMotionRadDEF(float *It, float* SP, float *Et, double timer)
	{
		float S[4];
		float sSP[4];
		_V4FSubDEF(Et,It,S);
		_V4FScaleModDEF(S,S,PI2F);
		//_V3FRadLimitDEF(S,S,PIF);
		if (S[0]>PI) S[0]-=PI2F;
		if (S[1]>PI) S[1]-=PI2F;
		if (S[2]>PI) S[2]-=PI2F;
		if (S[3]>PI) S[3]-=PI2F;
		if (S[0]<-PI) S[0]+=PI2F;
		if (S[1]<-PI) S[1]+=PI2F;
		if (S[2]<-PI) S[2]+=PI2F;
		if (S[3]<-PI) S[3]+=PI2F;
		if (timer>1.0) timer=1.0;
		_V4R32CopyDEF(SP,sSP);
		float abS[4];
		float abSP[4];
		_V4FAbsDEF(S,abS);
		_V4FAbsDEF(SP,abSP);
		if (abSP[0]<abS[0]) sSP[0]+=((S[0]-sSP[0])*timer);
		if (abSP[1]<abS[1]) sSP[1]+=((S[1]-sSP[1])*timer);
		if (abSP[2]<abS[2]) sSP[2]+=((S[2]-sSP[2])*timer);
		if (abSP[3]<abS[3]) sSP[3]+=((S[3]-sSP[3])*timer);
		if (abSP[0]>abS[0]) sSP[0]=S[0];
		if (abSP[1]>abS[1]) sSP[1]=S[1];
		if (abSP[2]>abS[2]) sSP[2]=S[2];
		if (abSP[3]>abS[3]) sSP[3]=S[3];
		_V4R32CopyDEF(sSP,SP);
		_V4FCombineDEF(sSP,It,sSP,timer,1);
		_V4FSubDEF(Et,sSP,S);
		_V4FScaleModDEF(S,S,PI2F);
		//_V3DRadLimitDEF(S,S,PIF);
		if (S[0]>PI) S[0]-=PI2F;
		if (S[1]>PI) S[1]-=PI2F;
		if (S[2]>PI) S[2]-=PI2F;
		if (S[3]>PI) S[3]-=PI2F;
		if (S[0]<-PI) S[0]+=PI2F;
		if (S[1]<-PI) S[1]+=PI2F;
		if (S[2]<-PI) S[2]+=PI2F;
		if (S[3]<-PI) S[3]+=PI2F;
		_V4FAbsDEF(S,S);
		_V4R32CopyDEF(sSP,It);
		return S[0]<0.0001f && S[1]<0.0001f && S[2]<0.0001f && S[3]<0.0001f;
	}

	bool _NOINLINE _APICALL _V4DMotionRadDEF(double *It, double* SP, double *Et, double timer)
	{
		double S[4];
		double sSP[4];
		_V4DSubDEF(Et,It,S);
		_V4DScaleModDEF(S,S,PI2);
		//_V4DRadLimitDEF(S,S,PI);
		if (S[0]>PI) S[0]-=PI2;
		if (S[1]>PI) S[1]-=PI2;
		if (S[2]>PI) S[2]-=PI2;
		if (S[3]>PI) S[3]-=PI2;
		if (S[0]<-PI) S[0]+=PI2;
		if (S[1]<-PI) S[1]+=PI2;
		if (S[2]<-PI) S[2]+=PI2;
		if (S[3]<-PI) S[3]+=PI2;
		if (timer>1.0) timer=1.0;
		_V4R64CopyDEF(SP,sSP);
		double abS[4];
		double abSP[4];
		_V4DAbsDEF(S,abS);
		_V4DAbsDEF(SP,abSP);
		if (abSP[0]<abS[0]) sSP[0]+=((S[0]-sSP[0])*timer);
		if (abSP[1]<abS[1]) sSP[1]+=((S[1]-sSP[1])*timer);
		if (abSP[2]<abS[2]) sSP[2]+=((S[2]-sSP[2])*timer);
		if (abSP[3]<abS[2]) sSP[3]+=((S[3]-sSP[3])*timer);
		if (abSP[0]>abS[0]) sSP[0]=S[0];
		if (abSP[1]>abS[1]) sSP[1]=S[1];
		if (abSP[2]>abS[2]) sSP[2]=S[2];
		if (abSP[3]>abS[3]) sSP[3]=S[3];
		_V4R64CopyDEF(sSP,SP);
		_V4DCombineDEF(sSP,It,sSP,timer,1);
		_V4DSubDEF(Et,sSP,S);
		_V4DScaleModDEF(S,S,PI2);
		//_V4DRadLimitDEF(S,S,PI);
		if (S[0]>PI) S[0]-=PI2;
		if (S[1]>PI) S[1]-=PI2;
		if (S[2]>PI) S[2]-=PI2;
		if (S[3]>PI) S[3]-=PI2;
		if (S[0]<-PI) S[0]+=PI2;
		if (S[1]<-PI) S[1]+=PI2;
		if (S[2]<-PI) S[2]+=PI2;
		if (S[3]<-PI) S[3]+=PI2;
		_V4DAbsDEF(S,S);
		_V4R64CopyDEF(sSP,It);
		return S[0]<0.0001 && S[1]<0.0001 && S[2]<0.0001 && S[3]<0.0001;
	}

	// ************** Spline Catmule Rome Vector default function *******************

	void _APICALL _V2FPCRCCDEF(float **a,float *cof)
	{
		int i=0;
		float *fcoef=cof;
		while (i<2) {
			float r1=a[0][i];
			float r2=a[1][i];
			float r3=a[2][i];
			float r4=a[3][i];
			fcoef[0]= - (r1) + fcmsplinef[1] * (r2) + fcmsplinef[2] * (r3) + (r4);
			fcoef[1]= 2.0f * (r1) + fcmsplinef[5] * (r2) + fcmsplinef[6] * (r3) - (r4);
			fcoef[2]= - (r1) + (r3);
			fcoef[3]= 2.0f * (r2);
			fcoef+=4;
			i++;
		}
	}

	void _APICALL _V3FPCRCCDEF(float **a,float *cof)
	{
		int i=0;
		float *fcoef=cof;
		while (i<3) {
			float r1=a[0][i];
			float r2=a[1][i];
			float r3=a[2][i];
			float r4=a[3][i];
			fcoef[0]= - (r1) + fcmsplinef[1] * (r2) + fcmsplinef[2] * (r3) + (r4);
			fcoef[1]= 2.0f * (r1) + fcmsplinef[5] * (r2) + fcmsplinef[6] * (r3) - (r4);
			fcoef[2]= - (r1) + (r3);
			fcoef[3]= 2.0f * (r2);
			fcoef+=4;
			i++;
		}
	}

	void _APICALL _V4FPCRCCDEF(float **a,float *cof)
	{
		int i=0;
		float *fcoef=cof;
		while (i<4) {
			float r1=a[0][i];
			float r2=a[1][i];
			float r3=a[2][i];
			float r4=a[3][i];
			fcoef[0]= - (r1) + fcmsplinef[1] * (r2) + fcmsplinef[2] * (r3) + (r4);
			fcoef[1]= 2.0f * (r1) + fcmsplinef[5] * (r2) + fcmsplinef[6] * (r3) - (r4);
			fcoef[2]= - (r1) + (r3);
			fcoef[3]= 2.0f * (r2);
			fcoef+=4;
			i++;
		}
	}

	void _APICALL _V2DPCRCCDEF(double **a,double *cof)
	{
		int i=0;
		double *fcoef=cof;
		while (i<2) {
			double r1=a[0][i];
			double r2=a[1][i];
			double r3=a[2][i];
			double r4=a[3][i];
			fcoef[0]= - (r1) + fcmsplined[1] * (r2) + fcmsplined[2] * (r3) + (r4);
			fcoef[1]= 2.0f * (r1) + fcmsplined[5] * (r2) + fcmsplined[6] * (r3) - (r4);
			fcoef[2]= - (r1) + (r3);
			fcoef[3]= 2.0f * (r2);
			fcoef+=4;
			i++;
		}
	}

	void _APICALL _V3DPCRCCDEF(double **a,double *cof)
	{
		int i=0;
		double *fcoef=cof;
		while (i<3) {
			double r1=a[0][i];
			double r2=a[1][i];
			double r3=a[2][i];
			double r4=a[3][i];
			fcoef[0]= - (r1) + fcmsplined[1] * (r2) + fcmsplined[2] * (r3) + (r4);
			fcoef[1]= 2.0f * (r1) + fcmsplined[5] * (r2) + fcmsplined[6] * (r3) - (r4);
			fcoef[2]= - (r1) + (r3);
			fcoef[3]= 2.0f * (r2);
			fcoef+=4;
			i++;
		}
	}

	void _APICALL _V4DPCRCCDEF(double **a,double *cof)
	{
		int i=0;
		double *fcoef=cof;
		while (i<4) {
			double r1=a[0][i];
			double r2=a[1][i];
			double r3=a[2][i];
			double r4=a[3][i];
			fcoef[0]= - (r1) + fcmsplined[1] * (r2) + fcmsplined[2] * (r3) + (r4);
			fcoef[1]= 2.0f * (r1) + fcmsplined[5] * (r2) + fcmsplined[6] * (r3) - (r4);
			fcoef[2]= - (r1) + (r3);
			fcoef[3]= 2.0f * (r2);
			fcoef+=4;
			i++;
		}
	}

	void _APICALL _V2FSplineCRDEF(float *a,float *b,float c,float d)
	{
		float c1 = c * c;
		float c2 = c1 * c;
		b[0] = (a[0]*c2+a[1]*c1+a[2]*c+a[3])*d;
		b[1] = (a[4]*c2+a[5]*c1+a[6]*c+a[7])*d;
	}

	void _APICALL _V3FSplineCRDEF(float *a,float *b,float c,float d)
	{
		float c1 = c * c;
		float c2 = c1 * c;
		b[0] = (a[0]*c2+a[1]*c1+a[2]*c+a[3])*d;
		b[1] = (a[4]*c2+a[5]*c1+a[6]*c+a[7])*d;
		b[2] = (a[8]*c2+a[9]*c1+a[10]*c+a[11])*d;
	}

	void _APICALL _V4FSplineCRDEF(float *a,float *b,float c,float d)
	{
		float c1 = c * c;
		float c2 = c1 * c;
		b[0] = (a[0]*c2+a[1]*c1+a[2]*c+a[3])*d;
		b[1] = (a[4]*c2+a[5]*c1+a[6]*c+a[7])*d;
		b[2] = (a[8]*c2+a[9]*c1+a[10]*c+a[11])*d;
		b[3] = (a[12]*c2+a[13]*c1+a[14]*c+a[15])*d;
	}

	void _APICALL _V2DSplineCRDEF(double *a,double *b,double c,double d)
	{
		double c1 = c * c;
		double c2 = c1 * c;
		b[0] = (a[0]*c2+a[1]*c1+a[2]*c+a[3])*d;
		b[1] = (a[4]*c2+a[5]*c1+a[6]*c+a[7])*d;
	}

	void _APICALL _V3DSplineCRDEF(double *a,double *b,double c,double d)
	{
		double c1 = c * c;
		double c2 = c1 * c;
		b[0] = (a[0]*c2+a[1]*c1+a[2]*c+a[3])*d;
		b[1] = (a[4]*c2+a[5]*c1+a[6]*c+a[7])*d;
		b[2] = (a[8]*c2+a[9]*c1+a[10]*c+a[11])*d;
	}

	void _APICALL _V4DSplineCRDEF(double *a,double *b,double c,double d)
	{
		double c1 = c * c;
		double c2 = c1 * c;
		b[0] = (a[0]*c2+a[1]*c1+a[2]*c+a[3])*d;
		b[1] = (a[4]*c2+a[5]*c1+a[6]*c+a[7])*d;
		b[2] = (a[8]*c2+a[9]*c1+a[10]*c+a[11])*d;
		b[3] = (a[12]*c2+a[13]*c1+a[14]*c+a[15])*d;
	}

	// ************** Noise default function *******************

	unsigned _int32 Noigen[22]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x41A7,0xBC8F,0x10FF5};

	void _APICALL _NoiseStartDEF(_int32 _seed,_int32 _cor)
	{
		Noigen[16]=_cor;
		Noigen[17]=_seed;
		_int32 id=0;
		for (_int32 i=0;i<16;i++) {
			Noigen[17]=(Noigen[17]*Noigen[18+id]+Noigen[16])%0x7FFFFFFF;
			Noigen[i]=Noigen[17];
			if (id>2) id=0;
			id++;
		}
	}

	_int32 _APICALL _NoiseGetDEF()
	{
		_int32 k;
		k=Noigen[17]&0xF;
		_int32 result=Noigen[k];
		_int32 id=(Noigen[17] >> 6);
		_int32 tr=matFunctions.DTrunc((id*0.33333333333333333333333333333333));
		_int32 fs=(result*Noigen[18+id-tr*3]+Noigen[16]);
		_int32 ds=matFunctions.DTrunc((fs*4.656612875245796924105750827168e-10));
		Noigen[k]=fs-ds*2147483647;
		Noigen[17]=result;
		return result;
	}

	void _APICALL _NoiseSaveDEF(unsigned _int32 *buff)
	{
		unsigned _int32 *b=(unsigned _int32 *)buff;
		extFunctions.MoveMem(Noigen,b,18*4);
	}

	void _APICALL _NoiseLoadDEF(unsigned _int32 *buff)
	{
		unsigned _int32 *b=(unsigned _int32 *)buff;
		extFunctions.MoveMem(b,Noigen,18*4);
	}

	// ************** Log default function *******************

	_int32 _APICALL _ILogSizeDEF(_int32 _a)
	{
		_int32 r=0;
		if (_a<2) return 1;
		_a--;
		_int32 _b=_a & 0xFFFF0000;
		if (_b) {r|=16;_a=_b;}
		_b=_a & 0xFF00FF00;
		if (_b) {r|=8;_a=_b;}
		_b=_a & 0xF0F0F0F0;
		if (_b) {r|=4;_a=_b;}
		_b=_a & 0xCCCCCCCC;
		if (_b) {r|=2;_a=_b;}
		_b=_a & 0xAAAAAAAA;
		if (_b) {r|=1;_a=_b;}
		return 2<<r;
	}

	// ************** str default function *******************

	/*char* _STDCALL _STRTokDEF(char*str,char*del)
	{
		char *c=str;
		_int32 dels=_FindCMemDEF(del,0,255);
		bool end=false;
		while ((*c!=0) && (!end)) {
			char *dc=del;
			char *cc=c;
			while ((*dc!=0) && (*cc==*dc) && (*cc!=0)) {
				dc++;
				cc++;
			}
			end=(dc-del==dels);
			if (!end) c++;
		}
		if (!end) return 0;
		return c;
	}*/

	char* _APICALL _STRLeftFindDEF(char*str,char*find)
	{
		char *c=str;
		_int32 finds=_FindCMemDEF(find,0,255);
		bool end=false;
		while ((*c!=0) && (!end)) {
			char *dc=find;
			char *cc=c;
			while ((*dc!=0) && (*cc==*dc) && (*cc!=0)) {
				dc++;
				cc++;
			}
			end=(dc-find==finds);
			if (!end) c++;
		}
		if (!end) return 0;
		return c;
	}

	char* _APICALL _STRRightFindDEF(char*str,char*find)
	{
		_int32 finds=_FindCMemDEF(find,0,255);
		_int32 strs=_FindCMemDEF(str,0,255);
		if (strs-finds<0) return 0;
		char *c=str+strs-finds;
		bool end=false;
		while ((c>str) && (!end)) {
			char *dc=find;
			char *cc=c;
			while ((*dc!=0) && (*cc==*dc) && (*cc!=0)) {
				dc++;
				cc++;
			}
			end=(dc-find==finds);
			if (!end) c--;
		}
		if (!end) return 0;
		return c;
	}

	_int32 _APICALL _STRBinToIDEF(char* s) //??
	{
		_int32 rez=0;
		_int32 wal=16;
		char *c=s;
		if (!c) return rez;
		if (*c=='-') c++;
		if (*(c+1)=='x') c+=2;
		while ((*c!=0) && (*c>='0') && (*c<='1')) {
			rez=(*c-'0')+(rez*wal);
			c++;
		}
		if (*s=='-') rez=-rez;
		return rez;
	}

	_int32 _APICALL _STRToIDEF(char* s)
	{
		_int32 rez=0;
		_int32 wal=10;
		char *c=s;
		if (!s) return rez;
		if (*s=='-') c++;
		if (c[0]=='0' && c[1]=='x') {
			rez=_STRHexToIDEF(s);
			return rez;
		}
		while ((*c!=0) && (*c>='0') && (*c<='9')) {
			rez=(*c-'0')+(rez*wal);
			c++;
		}
		if (*s=='-') rez=-rez;
		return rez;
	}

	_int32 _APICALL _STRHexToIDEF(char* s)
	{
		_int32 rez=0;
		_int32 wal=16;
		char *c=s;
		if (!c) return rez;
		if (*c=='-') c++;
		if (*(c+1)=='x') c+=2;
		_int32 r=0;
		while ((*c!=0) && (r>=0) && (r<=15)) {
			_int32 r=(*c-'0');
			if (!((r>=0) && (r<=9))) r=(*c-'A')+10;
			if (!((r>=0) && (r<=15))) r=(*c-'a')+10;
			if ((r>=0) && (r<=15)) rez=r+(rez*wal);
			c++;
		}
		if (*s=='-') rez=-rez;
		return rez;
	}

	float _APICALL _STRToFDEF(char* s)
	{
		float rez=0.0f;
		float wal=10.0f;
		char *c=s;
		if (!s) return rez;
		if (*s=='-') c++;
		while ((*c!=0) && (*c>='0') && (*c<='9')) {
			rez=(*c-'0')+(rez*wal);
			c++;
		}
		wal=1.0;
		if (*c!=0) c++;
		while ((*c!=0) && (*c>='0') && (*c<='9')) {
			wal*=0.1f;
			rez+=(*c-'0')*wal;
			c++;
		}
		if (*s=='-') rez=-rez;
		return rez;
	}

	double _APICALL _STRToDDEF(char* s)
	{
		double rez=0.0;
		double wal=10.0;
		char *c=s;
		if (!s) return rez;
		if (*s=='-') c++;
		while ((*c!=0) && (*c>='0') && (*c<='9')) {
			rez=(*c-'0')+(rez*wal);
			c++;
		}
		wal=1.0;
		if (*c!=0) c++;
		while ((*c!=0) && (*c>='0') && (*c<='9')) {
			wal*=0.1;
			rez+=(*c-'0')*wal;
			c++;
		}
		if (*s=='-') rez=-rez;
		return rez;
	}

	void _APICALL _IToSTRDEF(char* s,unsigned _int32 len,_int32 t)
	{
		_int32 rez=t;
		char *c=s;
		if (!s) return;
		if (rez<0 && len>0) {
			*c='-';
			c++;
			len--;
			rez=-rez;
		}
		if (rez==0 && len>0) {
			*c='0';
			c++;
			len--;
		}
		char *l=c;
		while (len>0 && rez>0) {
			_int32 fr=rez/10;
			char cs=rez-((fr<<3)+(fr<<1));
			*c=cs+'0';
			rez=fr;
			c++;
			len--;
		}
		if (len>0) *c=0;
		c--;
		while (l<c) {
			char cd=*l;
			*l=*c;
			*c=cd;
			l++;
			c--;
		}
	}

	char keytable[]={0};

	_int32 _APICALL _KeyToUniCharDEF(_int32 key,_int32 flag)
	{
		_int32 val=key;
		_int32 lang=(flag >> 16);
		if (key<32) val=0;
		if ((key>=33) && (key<=46)) val=0;
		if (lang==0) {
			if ((key==186)) val=';';
			if ((key==187)) val='=';
			if ((key==188)) val=',';
			if ((key==189)) val='-';
			if ((key==190)) val='.';
			if ((key==191)) val='/';
			if ((key==192)) val='`';
			if ((key==219)) val='[';
			if ((key==220)) val='\\';
			if ((key==221)) val=']';
			if ((key==222)) val='\'';
			if ((flag & 1)==0) {
				if ((key>=65) && (key<=90)) val+=32;
			}
			if ((flag & 2)!=0) {
				if ((key==48)) val=')';
				if ((key==49)) val='!';
				if ((key==50)) val='@';
				if ((key==51)) val='#';
				if ((key==52)) val='$';
				if ((key==53)) val='%';
				if ((key==54)) val='^';
				if ((key==55)) val='&';
				if ((key==56)) val='*';
				if ((key==57)) val='(';
				if ((key==186)) val=':';
				if ((key==187)) val='+';
				if ((key==188)) val='<';
				if ((key==189)) val='_';
				if ((key==190)) val='>';
				if ((key==191)) val='?';
				if ((key==192)) val='~';
				if ((key==219)) val='{';
				if ((key==220)) val='|';
				if ((key==221)) val='}';
				if ((key==222)) val='"';
			}
			return val;
		}
		if (lang==1) {
			if ((flag & 1)==0) {
				if ((key==186)) val=230;
				if ((key==188)) val=225;
				if ((key==190)) val=254;
				if ((key==192)) val=184;
				if ((key==219)) val=245;
				if ((key==221)) val=250;
				if ((key==222)) val=253;
				if ((key>=65) && (key<=90)) val+=159;
			} else {
				if ((key==186)) val=230;
				if ((key==188)) val=225;
				if ((key==190)) val=254;
				if ((key==192)) val=184;
				if ((key==219)) val=245;
				if ((key==221)) val=250;
				if ((key==222)) val=253;
				if ((key>=65) && (key<=90)) val+=127;
			}
			if ((flag & 2)!=0) {
				if ((key==48)) val=')';
				if ((key==49)) val='!';
				if ((key==50)) val='"';
				if ((key==51)) val='¹';
				if ((key==52)) val=';';
				if ((key==53)) val='%';
				if ((key==54)) val=':';
				if ((key==55)) val='?';
				if ((key==56)) val='*';
				if ((key==57)) val='(';
			}
			return val;
		}
		return val;
	}

	// ************** vector BLH default function *******************

	void _NOINLINE _APICALL _BLHtoV3FDEF(float*_v1,float*_v2)
	{
		float l=(float)(_v1[1]*PI180);
		float b=(float)(_v1[0]*PI180);
		float s;
		_FSinCosDEF(b,&s,&_v2[1]);
		_FSinCosDEF(l,&b,&l);
		_v2[0]=s*b;
		_v2[2]=s*l;
		_V3FScaleDEF_CPP(_v2,_v2,_v1[2]);
	}

	void _NOINLINE _APICALL _BLHtoV3DDEF(double* _v1,double* _v2)
	{
		double l=_v1[1]*PI180;
		double b=_v1[0]*PI180;
		double s;
		_DSinCosDEF(b,&s,&_v2[1]);
		_DSinCosDEF(l,&b,&l);
		_v2[0]=s*b;
		_v2[2]=s*l;
		_V3DScaleDEF_CPP(_v2,_v2,_v1[2]);
	}

	void _NOINLINE _APICALL _BLHtoV3FFASTDEF(float*_v1,float*_v2)
	{
		float l=(float)(_v1[1]*PI180);
		float b=(float)(_v1[0]*PI180);
		float s;
		_FSinCosFASTDEF(b,&s,&_v2[1]);
		_FSinCosFASTDEF(l,&b,&l);
		_v2[0]=s*b;
		_v2[2]=s*l;
		_V3FScaleDEF_CPP(_v2,_v2,_v1[2]);
	}

	void _NOINLINE _APICALL _BLHtoV3DFASTDEF(double* _v1,double* _v2)
	{
		double l=_v1[1]*PI180;
		double b=_v1[0]*PI180;
		double s;
		_DSinCosFASTDEF(b,&s,&_v2[1]);
		_DSinCosFASTDEF(l,&b,&l);
		_v2[0]=s*b;
		_v2[2]=s*l;
		_V3DScaleDEF_CPP(_v2,_v2,_v1[2]);
	}

	void _NOINLINE _APICALL _BLtoV3FDEF(float _b,float _l,float* _v2)
	{
		_l=(float)(_l*PI180);
		_b=(float)(_b*PI180);
		float s;
		_FSinCosDEF(_b,&s,&_v2[1]);
		_FSinCosDEF(_l,&_b,&_l);
		_v2[0]=s*_b;
		_v2[2]=s*_l;
	}

	void _NOINLINE _APICALL _BLtoV3DDEF(double _b,double _l,double* _v2)
	{
		_l=_l*PI180;
		_b=_b*PI180;
		double s;
		_DSinCosDEF(_b,&s,&_v2[1]);
		_DSinCosDEF(_l,&_b,&_l);
		_v2[0]=s*_b;
		_v2[2]=s*_l;
	}

	void _NOINLINE _APICALL _BLtoV3FFASTDEF(float _b,float _l,float* _v2)
	{
		_l=(float)(_l*PI180);
		_b=(float)(_b*PI180);
		float s;
		_FSinCosFASTDEF(_b,&s,&_v2[1]);
		_FSinCosFASTDEF(_l,&_b,&_l);
		_v2[0]=s*_b;
		_v2[2]=s*_l;
	}

	void _NOINLINE _APICALL _BLtoV3DFASTDEF(double _b,double _l,double* _v2)
	{
		_l=_l*PI180;
		_b=_b*PI180;
		double s;
		_DSinCosFASTDEF(_b,&s,&_v2[1]);
		_DSinCosFASTDEF(_l,&_b,&_l);
		_v2[0]=s*_b;
		_v2[2]=s*_l;
	}

	void _NOINLINE _APICALL _V3FtoBLHDEF(float *_blh,float *_pos)
	{
		_blh[1]=(float)(_FArcTgDEF(_pos[0],_pos[2])*A180PI);
		if (_blh[1]>180) _blh[1]=_blh[1]-360.0f;
		float ll=_pos[0]*_pos[0]+_pos[2]*_pos[2];
		if (ll>0) ll=_FsqrtDEF(ll);
		_blh[0]=(float)(_FArcTgDEF(ll,_pos[1])*A180PI);
		ll=_V3FLength2DEF(_pos);
		if (ll>0) ll=_FsqrtDEF(ll);
		_blh[3]=ll;
	}

	void _NOINLINE _APICALL _V3DtoBLHDEF(double *_blh,double *_pos)
	{
		_blh[1]=_DArcTgDEF(_pos[0],_pos[2])*A180PI;
		if (_blh[1]>180) _blh[1]-=360;
		double ll=_pos[0]*_pos[0]+_pos[2]*_pos[2];
		if (ll>0) ll=_DsqrtDEF(ll);
		_blh[0]=_DArcTgDEF(ll,_pos[1])*A180PI;
		ll=_V3DLength2DEF(_pos);
		if (ll>0) ll=_DsqrtDEF(ll);
		_blh[2]=ll;
	}

	void _NOINLINE _APICALL _V3FtoBLDEF(float *_b,float *_l,float *_pos)
	{
		*_l=(float)(_FArcTgDEF(_pos[0],_pos[2])*A180PI);
		if (*_l>180) *_l-=360.0f;
		float ll=_pos[0]*_pos[0]+_pos[2]*_pos[2];
		if (ll>0) ll=_FsqrtDEF(ll);
		*_b=(float)(_FArcTgDEF(ll,_pos[1])*A180PI);
	}

	void _NOINLINE _APICALL _V3DtoBLDEF(double *_b,double *_l,double *_pos)
	{
		*_l=_DArcTgDEF(_pos[0],_pos[2])*A180PI;
		if (*_l>180) *_l-=360.0;
		double ll=_pos[0]*_pos[0]+_pos[2]*_pos[2];
		if (ll>0) ll=_DsqrtDEF(ll);
		*_b=_DArcTgDEF(ll,_pos[1])*A180PI;
	}

	_int32 _ZoneNumberDEF(double _l)
	{
		return matFunctions.DTrunc(_l*(180.0/3.1415926535897932384626433832795)/6.0+1);
	}

	void _XY2BLGKDEF(double _x,double _y,_int32 zone,double *_br,double *_lr)
	{
		double x=_x*(1.570460641237214268e-7);
		double v24=_DSinDEF(x*2.0);
		double v30=_DSinDEF(x);
		v30=v30*v30;
		double v3C=v30*v30;
		double v48=((2.5258868499999998294e-3)-(1.491868999999999929e-5)*v30+(1.1903999999999999921e-7)*v3C)*v24+x;
		double v54=_DCosDEF(v48);
		v24=_DSinDEF(2.0*v48);
		v30=_DSinDEF(x);
		v30=v30*v30;
		v3C=v30*v30;
		double v60=v3C*v30;
		double z0=(_y-1.0e6*zone-5.0e5)*(1.5678293950765453152e-7)/v54;
		double v78=z0*z0;
		double v80=(1.6719999999999998752e-2)-v30*(6.3000000000000000444e-3)+(1.1879999999999999935e-2*v3C)-v60*(3.2799999999999999295e-3);
		v80=(4.2858000000000000262e-2)-v30*(2.5318000000000000227e-2)+v3C*(1.4345999999999999377e-2)-v60*(1.2639999999999999326e-3)-v80*v78;
		v80=(1.0500613999999999781e-1)-v30*(4.5599159999999999693e-2)+v3C*(2.2890100000000001765e-3)-(2.9870000000000000311e-5)*v60-v80*v78;
		v80=(2.51684630999999992e-1)-v30*(3.3692629999999999454e-3)+v3C*(1.1276000000000000121e-5)-(v78*v80);
		v80=v24*(-v78)*v80;
		*_br=v48+v80;
		v80=v30*(5.2400000000000002132e-2)+(3.7999999999999999924e-3)+(4.8199999999999999789e-2)*v3C+(3.2000000000000001533e-3)*v60;
		v80=(9.4769999999999993134e-2)*v30+(1.2250000000000000472e-2)+(3.282000000000000195e-2)*v3C-(3.4000000000000002442e-4)*v60-v78*v80;
		v80=(1.4874070000000000347e-1)*v30+(4.200249999999999817e-2)+(5.942000000000000233e-3)*v3C-(1.500000000000000038e-5)*v60-v78*v80;
		v80=(1.6273586000000000995e-1)*v30+(1.6778974999999998752e-1)-(5.2490000000000001934e-4)*v3C-(8.460000000000000316e-6)*v60-v78*v80;
		v80=1.0-(3.3467107999999999753e-3)*v30-(5.6002000000000001851e-6)*v3C-(1.8699999999999998704e-8)*v60-v78*v80;
		v80=v80*z0;
		*_lr=v80+(zone*6.0-3.0)/(5.7295779513082322e+1);
	}

	void _TranslateSKDEF(double *_br, double *_lr, double *_hr, _int32 _table, double _b,   double _l,   double _h)
	{
		/*double ra; //C
		double rb; //14
		double rc; //1C
		double fa; //24
		double fb; //2C
		double fc; //34
		double fd; //3C
		double fm; //44
		double kl; //4C
		double kb; //54

		if (_table>8) return;
		if (_table==0) {
			ra=6378245.0000000000;
			rb=6378136.0000000000;
			kl=0.0033523298692591350;
			kb=0.0033528037351842955;
			rc=25.000000000000000;
			fa=-141.00000000000000;
			fb=-80.000000000000000;
			fc=0;
			fd=0.34999999999999998;
			fm=0.66000000000000003;
		}
		if (_table==1) {
			ra=6378136.0000000000;
			rb=6378137.0000000000;
			kl=0.0033528037351842955;
			kb=0.0033528106647474805;
			rc=0;
			fa=0.29999999999999999;
			fb=1.5000000000000000;
			fc=0;
			fd=0;
			fm=0.075999999999999998;
		}
		if (_table==2) {
			ra=6378137.0000000000;
			rb=-rb;
			kl=0.0033528106647474805;
			kb=-rb;
			rc=-rb;
			fa=-rb;
			fb=-rb;
			fc=0;
			fd=0;
			fm=0;
		}
		if (_table==3) {
			ra=6378245.0000000000;
			rb=6378136.0000000000;
			kl=0.0033528037351842955;
			kb=0.0033523298692591350;
			rc=-rb;
			fa=-rb;
			fb=-rb;
			fc=-rb;
			fd=-rb;
			fm=-rb;
		}
		if (_table==4) {
			ra=6378245.0000000000;
			rb=6378136.0000000000;
			kl=0.0033523298692591350;
			kb=0.0033528037351842955;
			rc=25.000000000000000;
			fa=-141.00000000000000;
			fb=-80.000000000000000;
			fc=0;
			fd=0.34999999999999998;
			fm=0.66000000000000003;
		}
		if (_table==5) {
			ra=6378245.0000000000;
			rb=6378136.0000000000;
			kl=0.0033523298692591350;
			kb=0.0033528037351842955;
			rc=25.000000000000000;
			fa=-141.00000000000000;
			fb=-80.000000000000000;
			fc=0;
			fd=0.34999999999999998;
			fm=0.66000000000000003;
		}
		if (_table==6) {
			ra=6378245.0000000000;
			rb=6378136.0000000000;
			kl=0.0033523298692591350;
			kb=0.0033528037351842955;
			rc=25.000000000000000;
			fa=-141.00000000000000;
			fb=-80.000000000000000;
			fc=0;
			fd=0.34999999999999998;
			fm=0.66000000000000003;
		}
		if (_table==7) {
			ra=6378245.0000000000;
			rb=6378136.0000000000;
			kl=0.0033523298692591350;
			kb=0.0033528037351842955;
			rc=25.000000000000000;
			fa=-141.00000000000000;
			fb=-80.000000000000000;
			fc=0;
			fd=0.34999999999999998;
			fm=0.66000000000000003;
		}
		if (_table==8) {
			ra=6378245.0000000000;
			rb=6378136.0000000000;
			kl=0.0033523298692591350;
			kb=0.0033528037351842955;
			rc=25.000000000000000;
			fa=-141.00000000000000;
			fb=-80.000000000000000;
			fc=0;
			fd=0.34999999999999998;
			fm=0.66000000000000003;
		}

		_int32 at=ra*1.5915494309189534561e-1;
		ra-=at*6.283185307179586;
		if (ra<0) {
			ra+=6.283185307179586;
		} else if (ra>6.283185307179586) {
			ra-=6.283185307179586;
		}

		double cc=2.0*kl-kl*kl; //5C
		double cd=2.0*kb-kb*kb; //6C
		//double ca=rb-ra; //6A
		double cg=cd-cc; //74
		double cf=1.0-cc; //7C

		double sinb; //8C
		double cosb; //94
		_DSinCosDEF(_b,&sinb,&cosb);
		double sinl; //9C
		double cosl; //A4
		_DSinCosDEF(_l,&sinl,&cosl);
		double ss=(1.0-sinb*sinb*cc); //84
	
		//double m=pow(ss,-0.75))*cf*ra; //AC
		double m=ss*ss*ss/_DsqrtDEF(_DsqrtDEF(ss))*cf*ra; //AC
		double n=1.0/_DsqrtDEF(ss)*ra; //B4

		double Sb=(cd*cc*sinb*cosb-rc*sinb*cosl-fa*sinb*sinl+fb*cosb)*2.06265e5/(m+_h)+
			cg*sinb*cosb*2.06265e5+fc*sinl-fd*cosl; //BC
		*_br=Sb*(3.141592653589793)*(1.5432098765432097858e-6)+_b;

		double Sl=sinb/cosb*(cosl*fc+sinl*fd)-(cosl*fa-sinl*rc)*2.06265e5/(n+_h)+fm; //C4
		*_lr=Sl*(3.141592653589793)*(1.5432098765432097858e-6)+_l;

		double Sh=0.0000001*(_h+n)+
			(cosl*rc+sinl*fa)*cosb+fa*sinb+ra*cg*sinb*sinb*(5.0e-1)-
			(1.0-cc*sinb*sinb*(5.0e-1))*cd; //CC
		*_hr=_h+Sh;*/
	}

};

OPTIMIZE_OFF;
WARNING_ENABLE;