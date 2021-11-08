/*
 * resender.cpp
 *
 *  Created on: 14.11.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <components/resender.h>
#include <bt.h>

OPTIMIZE_ON;

namespace csad {

Resender::Resender()
{
	p_receiver=0;
}

void Resender::setReceiver(char*path)
{

}

void Resender::setReceiver(BaseObject *obj)
{
	p_receiver=obj;
}

void* Resender::set(unsigned _int32 id,void* param)
{
	if (id==BaseObject::TYPE) return Resender::t();
	if (id==BaseObject::WRITE) {
		ParametersList *list=(ParametersList *)param;
		if (list->contains("receiver")) setReceiver((*list)["receiver"].getString());
	}
	if (p_receiver) return p_receiver->set(id,param);
	return 0;
}

TYPEINFO(Resender)

}

OPTIMIZE_OFF;
