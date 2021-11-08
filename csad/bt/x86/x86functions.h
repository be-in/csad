/*
 * x86functions.h
 *
 *  Created on: 18.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef X86FUNCTIONS_H_
#define X86FUNCTIONS_H_

#include "x86cpu.h"

#ifdef CPU_X86_32

namespace bt {

extern x86cpuinfo cpuinfo;

void initx86(unsigned _int32 flagMask=0xFFFFFFFF);
void cpuinfotostring(char *string);
void initx86BT(void*_conteiner);
void initx86Math(void*_conteiner);
void initx86Vector(void*_conteiner);
void initx86ArrayVector(void*_conteiner);
void initx86Extension(void*_conteiner);
void initx86Array(void*_conteiner);
void initx86Render(void*_conteiner);

}

#endif

#endif /* X86FUNCTIONS_H_ */
