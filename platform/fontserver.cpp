/*
 * fontserver.cpp
 *
 *  Created on: 30.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform.h>

OPTIMIZE_ON;

namespace csad {

void * FontServer::set(unsigned _int32 id,void * param)
{
	if (id==BaseObject::TYPE) return FontServer::t();
	if (id==BaseObject::MANAGER) return &p_font;
	if (id==BaseObject::MANAGER_COUNT) return (void*)1;
	if (id==BaseObject::WRITE) {
		Variant *p;
		ParametersList *list=(ParametersList *)param;
		if ((p=list->find("options"))!=0) setOptions(p->getString());
	}
	return 0;
}

TYPEINFO(FontServer)

}

OPTIMIZE_OFF;

