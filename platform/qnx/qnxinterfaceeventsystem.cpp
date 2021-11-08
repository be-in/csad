/*
 * qnxinterfaceeventsystem.cpp
 *
 *  Created on: 09.08.2013
 *      Author: Пантелеймонов Александр
 */

#include <platform/platformapi.h>

#if defined (OS_QNX)

#include <platform/interfaceeventsystem.h>

namespace csad {

InterfaceEventSystem::InterfaceEventSystem()
{
	p_isupdate=false;
}

bool InterfaceEventSystem::registerEvent(int id,BaseObject * obj)
{
	p_handles[(void*)id]=obj;
	p_isupdate=false;
	return true;
}

bool InterfaceEventSystem::unregisterEvent(int id)
{
	//int it=p_handles.find(id);
	//if (it<0) return false;
	if (p_handles.remove((void*)id)==0) return false;
	p_isupdate=false;
	return true;
}

void InterfaceEventSystem::maxUpdata()
{
	InterfaceEventList::iterator it=p_handles.begin();
	InterfaceEventList::iterator end=p_handles.end();
	p_max=0;
	FD_ZERO(&p_mev);
	while (it!=end) {
		int val=(_voidint)it.key();
		if (val>p_max) p_max=val;
		FD_SET(val,&p_mev);
		it++;
	}
}

void InterfaceEventSystem::readEvents()
{
	if (!p_isupdate) maxUpdata();
	p_isupdate=true;
	fd_set mev=p_mev;
	int selectret=1;
	struct timeval twait;

	twait.tv_sec=0;
	twait.tv_usec=0;

	while ((selectret!=0) && (selectret!=-1)) {
		selectret=::select(p_max+1,&mev,0,0,&twait);
		if ((selectret!=0) && (selectret!=-1)) {
			InterfaceEventList::iterator it=p_handles.begin();
			InterfaceEventList::iterator end=p_handles.end();
			while (it!=end) {
				int val=(_voidint)it.key();
				if (FD_ISSET(val,&mev)) {
					it.value()->set(BaseObject::EVENT,0);
				}
				it++;
			}

		}
	}

	//update();
}

}

#endif