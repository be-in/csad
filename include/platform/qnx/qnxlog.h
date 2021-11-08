/*
 * qnxlog.h
 *
 *  Created on: 12.08.2013
 *      Author: Пантелеймонов Александр
 */

#ifndef QNXLOG_H_
#define QNXLOG_H_

#include <platform/base/baselog.h>
#include <platform/platformapi.h>

namespace csad {

class PLATFORM_API Log: public BaseLog {

public:
	static void setLogOut(void*);
	static void console(const char* format,...);
	static void log(const char* message);
	static void tocahr(char* buff,int size,const char *format,...);
	static void todata(char* buff,const char *format,...);
	static void setConsole(bool is);
	static int toint(char*);
	static float tofloat(char*);
	static double todouble(char*);
	static char *strtok(char*str,char* del);
	static char *strtok(char*str,const char*del) {return strtok(str,(char*)del);}
	static char *getExt(char *path);

private:
	enum States {
		VALIDED = 0x011F1C01,
		FREE = 0
	};

	static unsigned int p_isVal;
	static void *p_logfile;
	static bool p_console;

	static void _init();
};

}

#endif /* QNXLOG_H_ */
