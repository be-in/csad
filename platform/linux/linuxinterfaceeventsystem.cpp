/*
 * linuxinterfaceeventsystem.cpp
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr
 */

#include <platform/platformapi.h>

#if defined (OS_LINUX)

#include <platform/interfaceeventsystem.h>
#include <platform/display.h>
#include <core/graph.h>
#include <X11/Xlib.h>
#include <platform/log.h>

OPTIMIZE_ON;

namespace csad {

InterfaceEventSystem::InterfaceEventSystem()
{
	p_isupdate=false;
	p_max=0;
}

bool InterfaceEventSystem::registerEvent(int id,BaseObject * obj)
{
	p_handles[(void*)(_voidint)id]=obj;
	p_isupdate=false;
	return true;
}

bool InterfaceEventSystem::unregisterEvent(int id)
{
	//int it=p_handles.find(id);
	//if (it<0) return false;
	if (p_handles.remove((void*)(_voidint)id)==0) return false;
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

unsigned int KeyCodeConvert(unsigned int keycode)
{
	unsigned int ret=keycode;
	if (ret>255) ret=(ret &0xFF)-44;
	return ret;
}

void InterfaceEventSystem::readEvents()
{
/*	if (!p_isupdate) maxUpdata();
	p_isupdate=true;
	fd_set mev=p_mev;
	int selectret=1;
	struct timeval twait;

	twait.tv_sec=0;
	twait.tv_usec=0;*/

	ObjectsList &displays= Graph::graph().getDisplays()->getObjects();
	ObjectsList::iterator it = displays.begin();
	ObjectsList::iterator end = displays.end();
	XEvent event;

	while (it!=end) {
		Display* d=((Display*)it.value());
		::Display* display=(::Display*)d->getBase();
		while (XPending(display) > 0)
		{
			XNextEvent(display, &event);

			Event eventdata;
			eventdata.id=(void*)d->getHandle();
			eventdata.message=event.type;
			eventdata.wparam=0;
			eventdata.lparam=0;
			if (event.type==KeyPress || event.type==KeyRelease) {
				eventdata.wparam=KeyCodeConvert(XLookupKeysym(&event.xkey, 0));
			}
			if (event.type==ButtonPress || event.type==ButtonRelease) {
				eventdata.wparam=event.xbutton.button;
				eventdata.lparam=event.xbutton.x_root+(event.xbutton.y_root<<16);
			}
			if (event.type==MotionNotify) {
				eventdata.wparam=0;
				eventdata.lparam=(event.xmotion.x_root & 0xFFFF)+(event.xmotion.y_root<<16);
			}
			p_isupdate=true;
			InterfaceEventList::iterator it=p_handles.begin();
			InterfaceEventList::iterator end=p_handles.end();
			while (it!=end) {
				//int val=(int)it.key();
				it.value()->set(BaseObject::EVENT,&eventdata);
				it++;
			}
		}
		it++;
	}

	/*while ((selectret!=0) && (selectret!=-1)) {
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
	}*/

	//update();
}

}

OPTIMIZE_OFF;

#endif
