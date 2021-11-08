/*
 * sceneresender.cpp
 *
 *  Created on: 14.11.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/sceneresender.h>

OPTIMIZE_ON;

namespace csad {

SceneResender::SceneResender()
{
	p_receiver=0;
}

void SceneResender::setReceiver(char*)
{

}

void SceneResender::setReceiver(BaseObject *obj)
{
	p_receiver=obj;
}

void* SceneResender::set(unsigned _int32 id,void* param)
{
	if (id==BaseObject::TYPE) return SceneResender::t();
	if (id==BaseObject::WRITE) {
		ParametersList *list=(ParametersList *)param;
		if (list->contains("receiver")) setReceiver((*list)["receiver"].getString());
	}
	if (p_receiver) return p_receiver->set(id,param);
	return 0;
}

TYPEINFO(SceneResender)

}

OPTIMIZE_OFF;
