/*
 * e2k_64math.cpp
 *
 *  Created on: 18.09.2013
 *      Author: Александр
 */

#include "e2k_64math.h"

#ifdef CPU_E2K_64
WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

	float _APICALL _FsqrtE2K(float)
	{
		asm("fsqrts %r0,%r0");
	}

	double _APICALL _DsqrtE2K(double)
	{
		asm("fsqrtid %dr0,%dr1");
		asm("fsqrttd %dr1,%dr0,%dr0");
	}
}

OPTIMIZE_OFF;
WARNING_ENABLE;
#endif