/*
 * winlog.cpp
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifdef LOG_CSAD
#include <platform/platformapi.h>

#if defined (OS_WIN)

#include <platform/win/winlog.h>
#include <platform/file.h>

OPTIMIZE_ON;

namespace csad {

unsigned int Log::p_isVal;
bool Log::p_console;
void *Log::p_logfile;
void *Log::p_logsteam;

void Log::setLogOut(void* file)
{
	_init();
	p_logsteam=file;
	p_logfile=0;
}

void Log::setFileLogOut(void* file)
{
	_init();
	p_logfile=file;
	p_logsteam=0;
}

void Log::console(const char* format,...)
{
	if (p_isVal!=VALIDED) _init();
	if (!p_console) return;
	if (p_logfile) {
		File*file=(File*)p_logfile;
		char buff[256];
		file->write((void*)"log: ",5);
		va_list args;
		va_start(args,format);
		int r=vsnprintf(buff,255,format,args);
		if (r<0) {
			r=255;
			buff[r-1]='.';
			buff[r-2]='.';
			buff[r-3]='.';
		}
		buff[r]=0;
		va_end(args);
		file->write(buff,r);
		file->write((void*)"\r\n",2);
		return;
	}
	if (p_logsteam) {
		fprintf((FILE*)p_logsteam,"log: ");
		va_list args;
		va_start(args,format);
		vfprintf((FILE*)p_logsteam,format,args);
		va_end(args);
		fprintf((FILE*)p_logsteam,"\n");
	}
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
	return ::strtok(str,(const char*)del);
}

void Log::_init()
{
	if (p_isVal==VALIDED)  return;
	p_console=true;
	p_logsteam=stdout;
	p_logfile=0;
	p_isVal=VALIDED;
}

}

OPTIMIZE_OFF;

#endif
#endif