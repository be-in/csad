/*
 * x86service.cpp
 *
 *  Created on: 18.09.2014
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include "x86service.h"

#ifdef CPU_X86_32

#include "macrosasm.h"

WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

	void _NAKED _STDCALL __writeAddr(void*,void*)
	{
		BEGIN_ASM
		ASM( mov eax,[esp+12] )
		ASM( cmp word ptr [eax-3],0x50FF )
		ASM( jz writeAddrskip )
		ASM( cmp word ptr [eax-6],0x90FF )
		ASM( jz writeAddrwrite )
		ASM( cmp word ptr [eax-6],0x15FF )
		ASM( jnz writeAddrskip )
		ASM( writeAddrwrite: )
		ASM( mov [esp-12],0x90 )
		ASM( mov [esp-11],0xE8 )
		ASM( mov eax,[esp+8] )
		ASM( sub eax,[esp+12] )
		ASM( mov [esp-10],eax )
		ASM( mov eax,[esp+12] )
		ASM( sub eax,6 )
		ASM( lea edx,[esp-12] )
		ASM( sub esp,12 )
		ASM( push 6 )
		ASM( push edx )
		ASM( push eax )
		ASM( mov eax,[esp+28] )
		ASM( call eax )
		ASM( add esp,12 )
		ASM( mov eax,[esp+8] )
		ASM( writeAddrskip: )
		ASM( add esp,12 )
		ASM( jmp eax )
		END_ASM
	}

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif