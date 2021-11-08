/*
 * e2k_64functions.h
 *
 *  Created on: 18.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef E2K_64FUNCTIONS_H_
#define E2K_64FUNCTIONS_H_

#include "e2k_64cpu.h"

#ifdef CPU_E2K_64

namespace bt {

extern e2kcpuinfo cpuinfo;

void inite2k_64(unsigned int flagMask=0xFFFFFFFF);
void cpuinfotostring(char *string);
void inite2k_64Math(void*_conteiner);
void inite2k_64Vector(void*_conteiner);
void inite2k_64ArrayVector(void*_conteiner);
void inite2k_64Extention(void*_conteiner);
void inite2k_64Render(void*_conteiner);

}

#endif

#endif /* E2K_64FUNCTIONS_H_ */
