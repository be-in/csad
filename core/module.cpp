/*
 * module.cpp
 *
 *  Created on: 16.12.2013
 *      Author: Пантелеймонов А
 */

#include <core/module.h>

namespace csad {

Module::Module(char *path)
:lib(path)
{
	lib.open();
}

Module::~Module()
{
	lib.close();
}

void *Module::set(unsigned _int32 id,void* param)
{
	if (id==BaseObject::TYPE) return Module::t();
	if (id==BaseObject::READ) {
		Variant *p;
		ParametersList *list=(ParametersList *)param;
		p=&(*list)["path"];
		p->setString(lib.getPath());
	}
	return 0;
}

TYPEINFO(Module)

}
