/*
 * keyboard.cpp
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>

#include <platform.h>
#include <core/system.h>
#include <core/input.h>
#include <bt.h>

OPTIMIZE_ON;

namespace csad {

using namespace bt;

void *Keyboard::set(unsigned _int32 id,void * data)
{
	if (id==BaseObject::TYPE) return Keyboard::t();
	if ((id==BaseObject::EVENT) && (data)) read(data);
	return 0;
}

TYPEINFO(Keyboard)

}

OPTIMIZE_OFF;

