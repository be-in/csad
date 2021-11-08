/*
 * osxinterfacerendersystem.cpp
 *
 *  Created on: 15.08.2013
 *      Author: Пантелеймонов Александр
 */

#include <platform/platformapi.h>

#if defined (OS_OSX)

#include <platform/interfacerendersystem.h>

namespace csad {

InterfaceRenderSystem::InterfaceRenderSystem()
{
	p_isupdate=false;
	p_temp=0;
}

InterfaceRenderSystem::~InterfaceRenderSystem()
{
	if (p_temp) delete p_temp;
}

bool InterfaceRenderSystem::registerTarget(int order,BaseObject * obj)
{
	p_targets[(void*)order]=obj;
	p_isupdate=false;
	return true;
}

bool InterfaceRenderSystem::unregisterTarget(int order)
{
	//int it=p_targets.find(order);
	//if (it<0) return false;
	if (p_targets.remove((void*)order)==0) return false;
	p_isupdate=false;
	return true;
}

void InterfaceRenderSystem::renderTargets()
{
	if (!p_isupdate) Sort();
	if (!p_temp) return;

	int count=p_targets.count();
	for (int i=0;i<count;i++) {
		p_temp[i]->set(BaseObject::EVENT,0);
	}
}

BaseObject* InterfaceRenderSystem::getRenderer(vector2i *global)
{
	BaseObject* rend=0;
	if (!p_temp) return rend;
	int count=p_targets.count();
//	BaseInterfaceEventSystem::Event msg; //=(BaseInterfaceEventSystem::Event *)param
	//msg->
	for (int i=0;i<count;i++) {
		
//		rend=(BaseObject*)p_temp[i]->set(BaseObject::EVENT,msg);
		if (rend) return rend;
	}
	return 0;
}

void InterfaceRenderSystem::Sort()
{
	if (p_temp) delete p_temp;
	p_temp=(BaseObject**) new void*[p_targets.count()];
	InterfaceRenderList::iterator it= p_targets.begin();
	InterfaceRenderList::iterator end= p_targets.end();
	int i=0;
	while (it!=end) {
		p_temp[i]=it.value();
		i++;
		it++;
	}
}

}

#endif