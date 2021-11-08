/*
 * e2k_64vector.cpp
 *
 *  Created on: 18.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include "e2k_64vector.h"

#ifdef CPU_E2K_64

#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include "macrosasm.h"

WARNING_DISABLE;
OPTIMIZE_ON;

#define NO_NAKED

namespace bt {

// *********************************** matrix Mul E2K function **********************************************

#ifdef NO_NAKED

#endif

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif