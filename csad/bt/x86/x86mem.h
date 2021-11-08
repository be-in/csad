//=============================================================================
///**
// *  @file   mem.h
// *
// *  $Id: mem.h 16.10.2011  $
// *
// *  @brief generator 3, assembler memory operations, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_MEM_H_
#define GEN3_MEM_H_

#include <bt.h>

#ifdef CPU_X86_32

namespace bt {

	void _APICALL _CleanMemCPU(void *, unsigned int);
	void _APICALL _MoveMemCPU(void *,void *, unsigned int);
	void _APICALL _MoveBackCPU(void *,void *, unsigned int);
	void _APICALL _SwapMemCPU(void *,void *, unsigned int);
	void _APICALL _StosSMEMCPU(void *,unsigned int, unsigned int);
	void _APICALL _StosIMEMCPU(void *,unsigned int, unsigned int);

	void _APICALL _StosIMEMSSE(void *,unsigned int, unsigned int);

	void _APICALL _CleanMemSSE2(void *, unsigned int);
	void _APICALL _MoveMemSSE2(void *,void *,unsigned int);
	void _APICALL _MoveBackSSE2(void *,void *,unsigned int);
	void _APICALL _StosSMEMSSE2(void *,unsigned int, unsigned int);
	void _APICALL _StosIMEMSSE2(void *,unsigned int, unsigned int);

	void _APICALL _MoveMemSSE3(void *,void *, unsigned int);
	void _APICALL _MoveBackSSE3(void *,void *, unsigned int);
	void _APICALL _StosIMEMSSE3(void *,unsigned int, unsigned int);

	void _APICALL _CleanMemAVX(void *, unsigned int);
	void _APICALL _MoveMemAVX(void *,void *,unsigned int);
}

#endif

#endif /* GEN3_MEM_H_ */
