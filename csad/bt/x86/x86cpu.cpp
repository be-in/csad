/*
 * x86cpu.cpp
 *
 *  Created on: 18.09.2013
 *      Author: Пантелеймонов Александр
 */

#ifdef CPU_BT

#include "x86cpu.h"
#include "macrosasm.h"

WARNING_DISABLE;
OPTIMIZE_ON;

#ifdef CPU_X86_32

namespace bt {

	_int64 _NAKED _TSCDCPU()
	{
		BEGIN_ASM
		_LINE2( 0x0F, 0x31 )                 /* rdtsc */
		END_ASM
		RET_0;
	}

	unsigned _int32 _NAKED _NOINLINE _APICALL cpuid(_int32 ,_int32 *)
	{
		BEGIN_ASM
		_LINE1( 0x53 )                       /* push        ebx  */
		_LINE1( 0x57 )                       /* push        edi  */
		_LINE1( 0x51 )                       /* push        ecx  */
		_LINE4( 0x8B, 0x44, 0x24, 0x10 )     /* mov         eax,dword ptr [esp+10h]  */
		_LINE2( 0x0F, 0xA2 )                 /* cpuid  */
		_LINE4( 0x8B, 0x7C, 0x24, 0x14 )     /* mov         edi,dword ptr [esp+14h]  */
		_LINE2( 0x89, 0x07 )                 /* mov         dword ptr [edi],eax  */
		_LINE3( 0x89, 0x5F, 0x04 )           /* mov         dword ptr [edi+4],ebx  */
		_LINE3( 0x89, 0x4F, 0x08 )           /* mov         dword ptr [edi+8],ecx  */
		_LINE3( 0x89, 0x57, 0x0C )           /* mov         dword ptr [edi+0Ch],edx  */
		_LINE1( 0x59 )                       /* pop         ecx  */
		_LINE1( 0x5F )                       /* pop         edi  */
		_LINE1( 0x5B )                       /* pop         ebx  */
		END_ASM
		RET_2;
	}

	unsigned _int32 _NAKED _NOINLINE _APICALL cpuidex(_int32 ,_int32 ,_int32 *)
	{
		BEGIN_ASM
		_LINE1( 0x53 )                       /* push        ebx  */
		_LINE1( 0x57 )                       /* push        edi  */
		_LINE1( 0x51 )                       /* push        ecx  */
		_LINE4( 0x8B, 0x44, 0x24, 0x10 )     /* mov         eax,dword ptr [esp+10h]  */
		_LINE4( 0x8B, 0x4C, 0x24, 0x14 )     /* mov         ecx,dword ptr [esp+14h]  */
		_LINE2( 0x0F, 0xA2 )                 /* cpuid  */
		_LINE4( 0x8B, 0x7C, 0x24, 0x18 )     /* mov         edi,dword ptr [esp+18h]  */
		_LINE2( 0x89, 0x07 )                 /* mov         dword ptr [edi],eax  */
		_LINE3( 0x89, 0x5F, 0x04 )           /* mov         dword ptr [edi+4],ebx  */
		_LINE3( 0x89, 0x4F, 0x08 )           /* mov         dword ptr [edi+8],ecx  */
		_LINE3( 0x89, 0x57, 0x0C )           /* mov         dword ptr [edi+0Ch],edx  */
		_LINE1( 0x59 )                       /* pop         ecx  */
		_LINE1( 0x5F )                       /* pop         edi  */
		_LINE1( 0x5B )                       /* pop         ebx  */
		END_ASM
		RET_3;
	}

	void _APICALL cpuInit(x86cpuinfo * info)
	{
		unsigned _int32 flag;
		_int32 _f[4];
		cpuid(1,_f);
		flag=0;
		if ((_f[3] & 0x0000001)!=0) flag|=CPU_x86_FPU;
		if ((_f[3] & 0x0000010)!=0) flag|=CPU_x86_RDTSC;
		if ((_f[3] & 0x0000020)!=0) flag|=CPU_x86_RDMSR;
		if ((_f[3] & 0x0000100)!=0) flag|=CPU_x86_CMPXCHG8B;
		if ((_f[3] & 0x0008000)!=0) flag|=CPU_x86_CMOV;
		if ((_f[3] & 0x0800000)!=0) flag|=CPU_x86_MMX;
		if ((_f[3] & 0x1000000)!=0) flag|=CPU_x86_FXSR;
		if ((_f[3] & 0x2000000)!=0) flag|=CPU_x86_SSE;
		if ((_f[3] & 0x4000000)!=0) flag|=CPU_x86_SSE2;
		if ((_f[2] & 0x0000001)!=0) flag|=CPU_x86_SSE3;
		if ((_f[2] & 0x0000200)!=0) flag|=CPU_x86_SSSE3;
		if ((_f[2] & 0x0001000)!=0) flag|=CPU_x86_FMA;
		if ((_f[2] & 0x0180000)==0x0180000) flag|=CPU_x86_SSE4;
		if ((_f[2] & 0x2000000)!=0) flag|=CPU_x86_AES;
		if ((_f[2] & 0x4000000)!=0) flag|=CPU_x86_XSAVE;
		if ((_f[2] & 0x8000000)!=0) flag|=CPU_x86_OSXSAVE;
		if ((_f[2] & BIT_28)!=0) flag|=CPU_x86_AVX;

		cpuidex(7,0,_f);
		if ((_f[1] & 0x0000020)!=0) flag|=CPU_x86_AVX2;

		unsigned _int32 ext=cpuid(0x80000000,_f);
		if (ext>0x80000000) {
			_int32 _a[4];
			cpuid(0x80000001,_a);
			if ((_a[3] & 0x20000000)!=0) flag|=CPU_x86_64BIT;
			if ((_a[3] & 0x00800000)!=0) flag|=CPU_x86_MMXPLUS;
			if ((_a[3] & 0x40000000)!=0) flag|=CPU_x86_3DNOWPLUS;
			if ((_a[3] & 0x80000000)!=0) flag|=CPU_x86_3DNOW;
			if ((_a[2] & 0x00000040)!=0) flag|=CPU_x86_SSE4A;
			if ((_a[2] & 0x00000800)!=0) flag|=CPU_x86_SSE5;
		}

		if (ext>0x80000019) {
			_int32 _a1a[4];
			cpuid(0x8000001A,_a1a);
			if ((_a1a[0] & 0x00000001)!=0) flag|=CPU_x86_128BITFPU;
			if ((_a1a[0] & 0x00000002)!=0) flag|=CPU_x86_FASTMOVU;
		}

		info->flag=flag;
		cpuid(0,(_int32 *)info->name);
	}

}

#endif

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif