/*
 * qnxlog.cpp
 *
 *  Created on: 12.08.2013
 *      Author: Пантелеймонов Александр
 */

#include <platform/platformapi.h>

#if defined (OS_QNX)

#include <bt.h>
#include <platform.h>

namespace csad {

unsigned int Log::p_isVal;
bool Log::p_console;
void *Log::p_logfile;

void Log::setLogOut(void* file)
{
	_init();
	p_logfile=file;
}

void Log::console(const char* format,...)
{
	if (p_isVal!=VALIDED) _init();
	if (!p_console) return;
	if (!p_logfile) return;
	fprintf((FILE*)p_logfile,"log: ");
	va_list args;
	va_start(args,format);
	vfprintf((FILE*)p_logfile,format,args);
	va_end(args);
	fprintf((FILE*)p_logfile,"\n");
}

void Log::log(const char* message)
{
	console(message);
}

void Log::setConsole(bool is)
{
	p_console=is;
}

char *Log::strtok(char*str,char*del)
{
	return std::strtok(str,(const char*)del);
}

char *Log::getExt(char *path)
{
	char *c=path;
	while (*c) c++;
	while ((c!=path) && (*c!='.')) {
		c--;
	}
	if (*c) c++;
	return c;
}

void Log::_init()
{
	if (p_isVal==VALIDED)  return;
	p_console=true;
	p_logfile=stdout;
	p_isVal=VALIDED;
}

}

#endif