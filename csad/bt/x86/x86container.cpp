/*
 * x86container.cpp
 *
 *  Created on: 25.10.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifdef CPU_BT

#include "x86container.h"

#ifdef CPU_X86_32

#include "macrosasm.h"

WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

typedef void** voidpp;

voidpp _NAKED _APICALL _MPFindCPU(void ** ,void *)
{
	_BEGIN_ASM \
 ASM( mov         eax,dword ptr [esp+4] ) \
 ASM( test        eax,eax ) \
 ASM( je         _MPFindCPU02 ) \
 ASM( mov         ecx,dword ptr [eax] ) \
 ASM( test        ecx,ecx ) \
 ASM( jne          _MPFindCPU01 ) \
 ASM( _MPFindCPU02: xor         eax,eax ) \
 ASM( ret         8 ) \
 ASM( _MPFindCPU01: mov         eax,dword ptr [ecx] ) \
 ASM( add         ecx,4 ) \
 ASM( push        edi ) \
 ASM( test        eax,eax ) \
 ASM( je          _MPFindCPU03 ) \
 ASM( mov         edx,dword ptr [esp+0x0C] ) \
 ASM( mov         edi,eax ) \
 ASM( _MPFindCPU07: shr         eax,1 ) \
 ASM( cmp         edx,[ecx+eax*8] ) \
 ASM( je          _MPFindCPU04 ) \
 ASM( jbe         _MPFindCPU05 ) \
 ASM( lea         ecx,[ecx+eax*8+8] ) \
 ASM( dec         edi ) \
 ASM( _MPFindCPU05: shr         edi,1 ) \
 ASM( je          _MPFindCPU03 ) \
 ASM( mov         eax,edi ) \
 ASM( shr         eax,1 ) \
 ASM( cmp         edx,[ecx+eax*8] ) \
 ASM( je          _MPFindCPU04 ) \
 ASM( jbe         _MPFindCPU06 ) \
 ASM( lea         ecx,[ecx+eax*8+8] ) \
 ASM( dec         edi ) \
 ASM( _MPFindCPU06: shr         edi,1 ) \
 ASM( mov         eax,edi ) \
 ASM( jne         _MPFindCPU07 ) \
 ASM( _MPFindCPU03: pop         edi ) \
 ASM( xor         eax,eax ) \
 ASM( ret         8 ) \
 ASM( _MPFindCPU04: pop         edi ) \
 ASM( lea         eax,[ecx+eax*8+4] ) \
 ASM( ret         8 ) \
	_END_ASM
	RET_2;
}

voidpp _NAKED _APICALL _MPFindSSE2(void ** ,void *)
{
	_BEGIN_ASM \
 ASM( mov         eax,dword ptr [esp+4] ) \
 ASM( test        eax,eax ) \
 ASM( je         _MPFindSSE202 ) \
 ASM( mov         ecx,dword ptr [eax] ) \
 ASM( test        ecx,ecx ) \
 ASM( jne         _MPFindSSE201 ) \
 ASM( _MPFindSSE202: xor         eax,eax ) \
 ASM( ret         8 ) \
 ASM( _MPFindSSE201: mov         eax,dword ptr [ecx] ) \
 ASM( add         ecx,4 ) \
 ASM( movd        xmm0,edi ) \
 ASM( test        eax,eax ) \
 ASM( je          _MPFindSSE203 ) \
 ASM( mov         edx,dword ptr [esp+0x08] ) \
 ASM( mov         edi,eax ) \
 ASM( _MPFindSSE207: shr         eax,1 ) \
 ASM( cmp         edx,[ecx+eax*8] ) \
 ASM( je          _MPFindSSE204 ) \
 ASM( jbe         _MPFindSSE205 ) \
 ASM( lea         ecx,[ecx+eax*8+8] ) \
 ASM( dec         edi ) \
 ASM( _MPFindSSE205: shr         edi,1 ) \
 ASM( je          _MPFindSSE203 ) \
 ASM( mov         eax,edi ) \
 ASM( shr         eax,1 ) \
 ASM( cmp         edx,[ecx+eax*8] ) \
 ASM( je          _MPFindSSE204 ) \
 ASM( jbe         _MPFindSSE206 ) \
 ASM( lea         ecx,[ecx+eax*8+8] ) \
 ASM( dec         edi ) \
 ASM( _MPFindSSE206: shr         edi,1 ) \
 ASM( mov         eax,edi ) \
 ASM( jne         _MPFindSSE207 ) \
 ASM( _MPFindSSE203: movd        edi,xmm0 ) \
 ASM( xor         eax,eax ) \
 ASM( ret         8 ) \
 ASM( _MPFindSSE204: movd        edi,xmm0 ) \
 ASM( lea         eax,[ecx+eax*8+4] ) \
 ASM( ret         8 ) \
	_END_ASM
	RET_2;
}

};

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif
#endif