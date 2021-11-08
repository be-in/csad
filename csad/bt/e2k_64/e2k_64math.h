/*
 * e2k_64math.h
 *
 *  Created on: 18.09.2013
 *      Author: Александр
 */

#ifndef E2K_64MATH_H_
#define E2K_64MATH_H_

#include <bt.h>

#ifdef CPU_E2K_64

namespace bt {

	float _APICALL _FsqrtE2K(float);

	double _APICALL _DsqrtE2K(double);

}

#endif

#endif /* E2K_64MATH_H_ */
