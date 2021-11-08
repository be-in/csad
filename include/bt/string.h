/*
 * string.h
 *
 *  Created on: 10.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef STRING_H_
#define STRING_H_

#include <bt/btapi.h>

namespace bt {

BT_API char *numName(unsigned int i);
BT_API void tochar(char* ,int ,const char *,...);
BT_API void todata(char* ,const char *,...);
BT_API bool tobool(char*data);

}

#endif /* STRING_H_ */
