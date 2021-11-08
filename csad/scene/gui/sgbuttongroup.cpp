/*
 * sgbuttongroup.cpp
 *
 *  Created on: 17.12.2013
 *      Author: Пантелеймонов А
 */

#include <scene/gui/sgbuttongroup.h>
#include <scene/gui/sgbutton.h>

namespace csad {

SGButtonGroup::SGButtonGroup()
{

}

void SGButtonGroup::addElement(SGButton *element)
{
	if (p_list.find(element)>=0) return;
	//element->setGroup(this);
	p_list.assign(element);
}

}
