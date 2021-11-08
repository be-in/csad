/*
 * wintimer.cpp
 *
 *  Created on: 15.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>

#if defined (OS_WIN)

#include <platform.h>

OPTIMIZE_ON;

char *createMemory(unsigned int size,unsigned int flag)
{
	void *h;
	void **block=0;
	if ((flag & 0x1)==0) {
		h=(void*)LocalAlloc(LMEM_FIXED,size+sizeof(void*));
		block=(void**)LocalLock(h);
	} else {
		h=(void*)GlobalAlloc(LMEM_FIXED,size+sizeof(void*));
		block=(void**)GlobalLock(h);
	}
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
	if ((flag & 0x1)==0) {
		LocalUnlock((HLOCAL)*h);
		LocalFree((HLOCAL)*h);
	} else {
		GlobalUnlock((HLOCAL)*h);
		GlobalFree((HLOCAL)*h);
	}
	return true;
}

OPTIMIZE_OFF;

#endif