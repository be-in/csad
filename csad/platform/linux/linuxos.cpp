/*
 * linuxos.cpp
 *
 *  Created on: 15.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>

#if defined (OS_LINUX)

#include <platform.h>

OPTIMIZE_ON;

char *createMemory(unsigned int size,unsigned int)
{
	void *h;
	void **block=0;
	block=(void **)malloc(size+sizeof(void*));
	if (block) {
		*block=h;
		block++;
	}
	return (char*)block;
}

bool deleteMemory(char *block,unsigned int)
{
	void **h=(void **)block;
	h--;
	free((void *)h);
	return true;
}

OPTIMIZE_OFF;

#endif