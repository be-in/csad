/*
 * sglayout.cpp
 *
 *  Created on: 03.12.2013
 *      Author: Пантелеймонов А
 */

#include <scene/gui/sglayout.h>

namespace csad {

SGLayout::SGLayout()
{

}

void SGLayout::setSize(double x,double y,double z)
{
	p_size.x=x;
	p_size.y=y;
	p_size.z=z;
}


}
