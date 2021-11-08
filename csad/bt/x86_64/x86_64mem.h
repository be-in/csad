//=============================================================================
///**
// *  @file   x86_64mem.h
// *
// *  $Id: x86_64mem.h 16.10.2011  $
// *
// *  @brief generator 3, assembler memory operations, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_X86_64_MEM_H_
#define GEN3_X86_64_MEM_H_

#include <bt.h>

#ifdef CPU_X86_64

namespace bt {

	void _APICALL _CleanMemCPU(void *, unsigned int);
	void _APICALL _MoveMemCPU(void *,void *, unsigned int);
	void _APICALL _StosSMEMCPU(void *,unsigned int, unsigned int);
	void _APICALL _StosIMEMCPU(void *,unsigned int, unsigned int);

	void _APICALL _MoveMemSSE2(void *,void *, unsigned int);
}

#endif

#endif /* GEN3_X86_64_MEM_H_ */
