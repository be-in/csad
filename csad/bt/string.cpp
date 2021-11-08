/*
 * string.cpp
 *
 *  Created on: 10.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <bt.h>
#include <vector>
#include <string.h>
#include <stdio.h>

OPTIMIZE_ON;

namespace bt {

char tempNumNameGenerator[20] = { '#', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

char *numName(unsigned int i)
{
	extFunctions.IToSTR(&tempNumNameGenerator[1], 18, i);
	return tempNumNameGenerator;
}

void tochar(char* buff,int size,const char * format,...)
{
	va_list args;
	va_start(args,format);
	vsnprintf(buff,size,format,args);
	va_end(args);
}

void todata(char* buff,const char *format,...)
{
#if defined (OS_QNX) || defined (OS_LINUX)
	va_list args;
	va_start(args,format);
	vsscanf(buff,format,args);
	va_end(args);
#elif defined (OS_WIN)
	va_list args;
	va_start(args,format);
	void* a[16];
	for (int i=0;i<16;i++) a[i]=va_arg(args,void*);
	sscanf(buff,format,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10]);
#else
#endif
}

bool tobool(char*data)
{
	if ((*((int *)data)==0x736c6166) && (*((short *)data+2)==0x0065)) return false;
	if ((*((int *)data)==0x65757274) && (*(data+4)==0x00)) return true;
	return false;
}

}

OPTIMIZE_OFF;
