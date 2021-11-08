/*
 * winlog.h
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#if defined(LOG_CSAD) || !defined(CSAD_LOCAL)
#ifndef WINLOG_H_
#define WINLOG_H_

#include <platform/base/baselog.h>
#include <platform/platformapi.h>

namespace csad {

class Log: public BaseLog {

public:
	PLATFORM_API static void setLogOut(void*);
	PLATFORM_API static void setFileLogOut(void*);
	PLATFORM_API static void console(const char* format, ...);
	PLATFORM_API static void log(const char* message);
	PLATFORM_API static void setConsole(bool is);
	PLATFORM_API static char *strtok(char*str, char*del);

private:
	enum States {
		VALIDED = 0x011F1C01,
		FREE = 0
	};

	static unsigned int p_isVal;
	static void *p_logsteam;
	static void *p_logfile;
	static bool p_console;

	static void _init();
};

}

#endif /* WINLOG_H_ */
#endif