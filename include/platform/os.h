/*
 * os.h
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef PLATFORM_OS_H_
#define PLATFORM_OS_H_

#include <platform/platformapi.h>

PLATFORM_API char* createMemory(unsigned int size,unsigned int flag=0);
PLATFORM_API bool deleteMemory(char *block,unsigned int flag=0);

#endif /* PLATFORM_OS_H_ */
