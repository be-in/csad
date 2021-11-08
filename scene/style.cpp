/*
 * style.cpp
 *
 *  Created on: 13.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/style.h>
#include <core/graph.h>
#include <bt.h>

OPTIMIZE_ON;

namespace csad {

Style::Style(char *name)
{
	_init();
	Graph::graph().p_style->addObject(this,name);
}

Style::Style(const char *name)
{
	_init();
	Graph::graph().p_style->addObject(this,name);
}

Component* Style::getInheritComponent(void * t) {
	if (!finherit) return 0;
	Component* c=finherit->getComponent(t);
	return c;
}

void Style::setInherit(Style *style)
{
	finherit=style;
}

void Style::setInherit(char *name)
{
	Graph::graph().p_style->getObject(name);
}

const char *Style::getPath()
{
	ObjectManager::path="style/";
	ObjectManager::path+=Graph::graph().p_style->getName(this);
	return ObjectManager::path.str();
}

void * Style::set(unsigned _int32 id,void *param)
{
	if (id==BaseObject::TYPE) return Style::t();
	if (id==BaseObject::CONTAINER) return this;
	if (id==BaseObject::WRITE) {
		ParametersList &list=*(ParametersList *)param;
		if (list.contains("inherit")) setInherit(list["inherit"].getString());
	}
	return 0;
}

void Style::_init()
{
	finherit=0;
}

TYPEINFO(Style)

}

OPTIMIZE_OFF;
