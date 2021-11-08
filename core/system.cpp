/*
 * system.cpp
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <core/system.h>
#include <core/module.h>
#include "csadcore.h"

OPTIMIZE_ON;

namespace csad {

System::System()
{
	flibraryes = new ObjectManager("module");
}

System::~System()
{
	if (flibraryes) flibraryes->destroyObjects<Module>();
	delete flibraryes;
	flibraryes=0;
}

Module *System::createModule(char *path,char *name)
{
	if ((name!=0) && (name[0]!=0)) {
		Module* r=(Module*)flibraryes->getObject(name);
		if (r) return r;
	}
	Module * module=new Module(path);
	if (module->isInit()) {
		flibraryes->addObject(module,name);
		return module;
	}
	delete module;
	return 0;
}

Module *System::getModule(char *name)
{
	return (Module*)flibraryes->getObject(name);
}

System & System::system()
{
	return *core->system();
}

/*SystemObject* System::CreateObject()
{
	return new SystemObject();
}*/

}

OPTIMIZE_OFF;