/*
 * sgtabcontroll.cpp
 *
 *  Created on: 16.09.2013
 *      Author: Пантелеймонов Александр
 */

#include <scene/gui/sgtabcontroll.h>
#include <scene/gui/sgelement.h>
#include <scene/transform.h>
#include <core/graph.h>

OPTIMIZE_ON;

namespace csad {

SGTabControll::SGTabControll()
	:mfirst(0)
{
}

CSAD_API SGListElement *SGTabControll::addElement(csad::SGListElement *parent)
{
	return 0;
}

/*void SGTabControll::setAction(csad::SGElement *tr)
{
}

void SGTabControll::setAction(char *tr)
{
}

void SGTabControll::setWidget(csad::Transform *tr)
{
}

void SGTabControll::setWidget(char *tr)
{
}*/

/*void SGTabControll::setActionGroup(csad::Transform *tr)
{
}

void SGTabControll::setActionGroup(char *name)
{
}

void SGTabControll::setWidgetGroup(csad::Transform *tr)
{
}

void SGTabControll::setWidgetGroup(char *name)
{
}*/

void * SGTabControll::set(unsigned _int32 id,void *)
{
	if (id==BaseObject::TYPE) return SGTabControll::t();
	return 0;
}

TYPEINFO(SGTabControll)

}
