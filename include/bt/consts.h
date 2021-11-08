/*
 * consts.h
 *
 *  Created on: 17.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#pragma once

#ifndef CONSTS_H_
#define CONSTS_H_

#ifndef PI360F
	#define PI360F 0.00872664625997164788461845384244f
#endif

#ifndef PI360
	#define PI360 0.00872664625997164788461845384244
#endif

#ifndef PI180F
	#define PI180F 0.01745329251994329576923690768489f
#endif

#ifndef PI180
	#define PI180 0.01745329251994329576923690768489
#endif

#ifndef PIF
	#define PIF 3.1415926535897932384626433832795f
#endif

#ifndef PI
	#define PI 3.1415926535897932384626433832795
#endif

#ifndef APIF
#define APIF 0.31830988618379067153776752674503f
#endif

#ifndef API
#define API 0.31830988618379067153776752674503
#endif

#ifndef A180PIF
	#define A180PIF 57.295779513082320876798154814105f
#endif

#ifndef A180PI
	#define A180PI 57.295779513082320876798154814105
#endif

#ifndef PI2F
	#define PI2F 6.283185307179586476925286766559f
#endif

#ifndef PI2
	#define PI2 6.283185307179586476925286766559
#endif

#ifndef API2F
	#define API2F 0.15915494309189533576888376337251f
#endif

#ifndef API2
	#define API2 0.15915494309189533576888376337251
#endif

#ifndef LOGEF
	#define LOGEF 0.69314718055994530941723212145818f
#endif

#ifndef LOGE
	#define LOGE 0.69314718055994530941723212145818
#endif

#ifndef LOG8F
	#define LOG8F 0.33333333333333333333333333333333f
#endif

#ifndef LOG8
	#define LOG8 0.33333333333333333333333333333333
#endif

#ifndef LOG10F
	#define LOG10F 0.30102999566398119521373889472449f
#endif

#ifndef LOG10
	#define LOG10 0.30102999566398119521373889472449
#endif

#ifndef LOG16F
	#define LOG16F 0.25f
#endif

#ifndef LOG16
	#define LOG16 0.25
#endif

#ifndef VALIDED_STATE
	#define VALIDED_STATE 0x011F1C01
#endif

#ifndef FREE_STATE
	#define FREE_STATE 0x011F1C01
#endif

// ********************************** bit defines ******************************

#define  BIT_0 0x00000001
#define  BIT_1 0x00000002
#define  BIT_2 0x00000004
#define  BIT_3 0x00000008
#define  BIT_4 0x00000010
#define  BIT_5 0x00000020
#define  BIT_6 0x00000040
#define  BIT_7 0x00000080
#define  BIT_8 0x00000100
#define  BIT_9 0x00000200
#define  BIT_10 0x00000400
#define  BIT_11 0x00000800
#define  BIT_12 0x00001000
#define  BIT_13 0x00002000
#define  BIT_14 0x00004000
#define  BIT_15 0x00008000
#define  BIT_16 0x00010000
#define  BIT_17 0x00020000
#define  BIT_18 0x00040000
#define  BIT_19 0x00080000
#define  BIT_20 0x00100000
#define  BIT_21 0x00200000
#define  BIT_22 0x00400000
#define  BIT_23 0x00800000
#define  BIT_24 0x01000000
#define  BIT_25 0x02000000
#define  BIT_26 0x04000000
#define  BIT_27 0x08000000
#define  BIT_28 0x10000000
#define  BIT_29 0x20000000
#define  BIT_30 0x40000000
#define  BIT_31 0x80000000

// ********************************** x86 defines ******************************

#define  CPU_x86_FPU        0x00001
#define  CPU_x86_MMX        0x00002
#define  CPU_x86_3DNOW      0x00004
#define  CPU_x86_FXSR       0x00008
#define  CPU_x86_CMOV       0x00010
#define  CPU_x86_RDTSC      0x00020
#define  CPU_x86_RDMSR      0x00040
#define  CPU_x86_CMPXCHG8B  0x00080
#define  CPU_x86_SSE        0x00100
#define  CPU_x86_SSE2       0x00200
#define  CPU_x86_SSE3       0x00400
#define  CPU_x86_SSSE3      0x00800
#define  CPU_x86_SSE4       0x01000 // SSE4.1 and SSE4.2
#define  CPU_x86_SSE5       0x02000
#define  CPU_x86_MMXPLUS    0x04000
#define  CPU_x86_3DNOWPLUS  0x08000
#define  CPU_x86_SSE4A      0x10000
#define  CPU_x86_64BIT      0x20000
#define  CPU_x86_128BITFPU  0x40000
#define  CPU_x86_FASTMOVU   0x80000
#define  CPU_x86_AVX       0x100000
#define  CPU_x86_AVX2      0x200000
#define  CPU_x86_AES       0x400000
#define  CPU_x86_FMA       0x800000
#define  CPU_x86_XSAVE    0x1000000
#define  CPU_x86_YMM      0x2000000
#define  CPU_x86_XMM      0x4000000
#define  CPU_x86_OSXSAVE  0x8000000

// ********************************** e2k defines ******************************

#define  CPU_e2k_E2K        0x00001

#endif /* CONSTS_H_ */
