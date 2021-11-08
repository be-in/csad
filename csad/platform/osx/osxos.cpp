/*
 * wintimer.cpp
 *
 *  Created on: 15.08.2013
 *      Author: Пантелеймонов Александр
 */

#include <platform/platformapi.h>

#if defined (OS_OSX)

#include <platform.h>

OPTIMIZE_ON;

char *createMemory(unsigned int size,unsigned int flag)
{
	void *h;
	void **block=0;
	block=malloc(size+sizeof(void*));
	if (block) {
		*block=h;
		block++;
	}
	return (char*)block;
}

bool deleteMemory(char *block,unsigned int flag)
{
	void **h=(void **)block;
	h--;
	free(h);
	return true;
}

OPTIMIZE_OFF;

#endif