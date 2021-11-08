/*
 * baselog.h
 *
 *  Created on: 12.08.2013
 *      Author: Пантелеймонов Александр
 */

#ifndef BASE_LOG_H_
#define BASE_LOG_H_

#include <bt/memmanager.h>

namespace csad {

class BaseLog {

public:
	MEMNULL

	static void setLogOut(void*) {}
	static void console(const char* ,...) {}
	static void log(const char* ) {}
	static void todata(char* ,const char *,...) {}
	static void setConsole(bool ) {}
	static char *strtok(char*,char*) {return 0;}
	static char *strtok(char*,const char*) {return 0;}
};

}

#endif /* BASELOG_H_ */
