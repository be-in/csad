/*
 * component.cpp
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <core/component.h>
#include <core/containercomponents.h>
#include "csadcore.h"

//bool GlobalComponentDefaultValueChecker;

namespace csad {

OPTIMIZE_ON;

Component::Component()
{
	p_parent=0;
	if (core) ((LocalCore*)core)->p_start.assign(this);
}

Component::~Component() {
	if (p_parent) {
//		void *key=0;
		p_parent->removeComponent(((BaseObject*)this)->set(TYPE,0));
		/*key=p_parent->p_list._key(this,key);
		if (key) p_parent->p_list.remove(key);*/
	}
	if (core) ((LocalCore*)core)->p_start.del(this);
}

void Component::start()
{
	//GlobalComponentDefaultValueChecker = true;
}

void Component::update()
{
	//GlobalComponentDefaultValueChecker = true;
}

void Component::quit()
{
	//GlobalComponentDefaultValueChecker = true;
}

void *Component::set(unsigned _int32,void*)
{
	return 0;
}

int Component::regClass(const char *name,const void *info,tfSTDCALL_p_FUNC_p fun)
{
	ObjectInfo *obj=core->classManager()->regClass(name,info,fun);
	obj->flag=ObjectInfo::COMPONENT;
	return 0;
}

ContainerComponents *Component::getContainer(void * info)
{
	if (!p_parent) return 0;
	if (p_parent->type()!=info) return 0;
	return p_parent;
}

Component *Component::addComponent(Component * component,void * info)
{
	//ContainerComponents *lparent=(ContainerComponents *)p_parent;
	return (Component *)*addContainerComponentByInfo(p_parent,component,info);
}

Component *Component::getComponent(void * info)
{
	void**c=(void**)arrFunctions.MPFind(&p_parent->p_list,info);
	if (!c) return 0;
	return (Component *)*c;
	//return (Component *)p_parent->p_list._find(info);
}

TYPEINFO(Component)

OPTIMIZE_OFF;

}
