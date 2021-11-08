/*
 * wininterfaceeventsystem.cpp
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>

#if defined (OS_WIN)

#include <platform/win/wininterfaceeventsystem.h>

OPTIMIZE_ON;

namespace csad {

InterfaceEventSystem::InterfaceEventSystem()
{
	p_max=0;
	p_isupdate=false;
}

InterfaceEventSystem::~InterfaceEventSystem()
{
}

bool InterfaceEventSystem::registerEvent(int id,BaseObject * obj)
{
	p_handles[(void*)id]=obj;
	p_isupdate=false;
	return true;
}

bool InterfaceEventSystem::unregisterEvent(int id)
{
	if (p_handles.remove((void*)id)==0) return false;
	p_isupdate=false;
	return true;
}

void InterfaceEventSystem::readEvents()
{
	MSG msg;
	while ((PeekMessage(&msg,0,0,0,PM_REMOVE)) && (msg.message!=WM_PAINT))
	{
		Event eventdata;
		eventdata.id=(void*)msg.hwnd;
		eventdata.message=msg.message;
		eventdata.wparam=msg.wParam;
		eventdata.lparam=msg.lParam;
		p_isupdate=true;
		InterfaceEventList::iterator it=p_handles.begin();
		InterfaceEventList::iterator end=p_handles.end();
		while (it!=end) {
			//int val=(int)it.key();
			it.value()->set(BaseObject::EVENT,&eventdata);
			it++;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

}

OPTIMIZE_OFF;

#endif