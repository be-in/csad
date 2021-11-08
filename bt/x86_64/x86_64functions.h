/*
 * x86_64functions.h
 *
 *  Created on: 18.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifdef CPU_BT
#ifndef X86_64FUNCTIONS_H_
#define X86_64FUNCTIONS_H_

#include "x86_64cpu.h"

#ifdef CPU_X86_64

namespace bt {

extern x86cpuinfo cpuinfo;

void initx86_64(unsigned int flagMask=0xFFFFFFFF);
void cpuinfotostring(char *string);
void initx86_64BT(void*_conteiner);
void initx86_64Math(void*_conteiner);
void initx86_64Vector(void*_conteiner);
void initx86_64ArrayVector(void*_conteiner);
void initx86_64Extension(void*_conteiner);
void initx86_64Array(void*_conteiner);
void initx86_64Render(void*_conteiner);

}

#endif

#endif /* X86_64FUNCTIONS_H_ */
#endif