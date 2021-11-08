/*
 * x86_64mem.cpp
 *
 *  Created on: 17.10.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifdef CPU_BT
#include "x86_64mem.h"

#ifdef CPU_X86_64

#include "macrosasm.h"
ARCH_ALL;

#if defined(GCC) || defined(MINGW)
#include "x86_64intrin.h"
#include <x86intrin.h>
#endif

#if defined(MSVC)
#include <intrin.h>
#endif

WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

ARCH_DEFAULT;

void _APICALL _CleanMemCPU(void * _a, unsigned int _c)
{
	char *a=(char *)_a;
	__stosb((unsigned char*)a,0,_c & 7);
	a+=_c & 7;
	__stosq((unsigned _int64*)a,0,_c>>3);
}

// ************** move mem *******************

void _APICALL _MoveMemCPU(void *_a,void *_b, unsigned int _c)
{
	char *a=(char *)_a;
	char *b=(char *)_b;
	unsigned int c=_c & 7;
	_c=_c-c;
	__movsq((unsigned _int64*)b,(unsigned _int64*)a,_c>>3);
	a+=_c;
	b+=_c;
	__movsb((unsigned char*)b,(unsigned char*)a,c);
}

// ************** swap mem *******************

// ************** stot mem short *******************
void _APICALL _StosSMEMCPU(void * _a,unsigned int _b, unsigned int _c)
{
	__stosw((unsigned short*)_a,_c,_b & 3);
	short *a=(short *)_a;
	_int64 c=_c + (_c<<16);
	c+=c<<32;
	a+=_b & 3;
	__stosq((unsigned _int64*)a,c,_b >>2);
}

// ************** stot mem int *******************
void _APICALL _StosIMEMCPU(void *_a,unsigned int _b, unsigned int _c)
{
	__stosd((unsigned _int32*)_a,_c,_b&1);
	int *a=(int *)_a;
	_int64 c=_c;
	c+=c<<32;
	a+=_b & 1;
	__stosq((unsigned _int64*)a,c,_b >>1);
}

// ************************* SSE2 ****************************
ARCH_SSE2;

// ************** move mem SSE2 *******************

void _APICALL _MoveMemSSE2(void *_a,void *_b, unsigned int _c)
{
	char *a=(char *)_a;
	char *b=(char *)_b;
	if (_c<128 || ((_voidint)(a)&0xF)!=0 || ((_voidint)(b)&0xF)!=0) {
		unsigned int c=_c & 7;
		_c=_c-c;
		__movsq((unsigned _int64*)b,(unsigned _int64*)a,_c>>3);
		a+=_c;
		b+=_c;
		__movsb((unsigned char*)b,(unsigned char*)a,c);
		return;
	} else {
		unsigned int c=_c>>7;
		_c&=0x7F;
		while (c>0) {
			__m128 v0=_mm_load_ps((const float *)a);
			__m128 v1=_mm_load_ps((const float *)(a+16));
			__m128 v2=_mm_load_ps((const float *)(a+32));
			__m128 v3=_mm_load_ps((const float *)(a+48));
			__m128 v4=_mm_load_ps((const float *)(a+64));
			__m128 v5=_mm_load_ps((const float *)(a+80));
			__m128 v6=_mm_load_ps((const float *)(a+96));
			__m128 v7=_mm_load_ps((const float *)(a+112));
			_mm_store_ps((float*)b,v0);
			_mm_store_ps((float*)(b+16),v1);
			_mm_store_ps((float*)(b+32),v2);
			_mm_store_ps((float*)(b+48),v3);
			_mm_store_ps((float*)(b+64),v4);
			_mm_store_ps((float*)(b+80),v5);
			_mm_store_ps((float*)(b+96),v6);
			_mm_store_ps((float*)(b+112),v7);
			a+=128;
			b+=128;
			c--;
		}
		c=_c & 7;
		_c=_c-c;
		__movsq((unsigned _int64*)b,(unsigned _int64*)a,_c>>3);
		a+=_c;
		b+=_c;
		__movsb((unsigned char*)b,(unsigned char*)a,c);
	}
}

}

OPTIMIZE_OFF;
WARNING_ENABLE;

ARCH_DEFAULT;

#endif
#endif
