/*
 * baseinterfaceeventsystem.h
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef BASEINTERFACEEVENTSYSTEM_H_
#define BASEINTERFACEEVENTSYSTEM_H_

#include <core/baseobject.h>
#include <core/systemobject.h>
#include <bt.h>

namespace csad {

typedef MapVoid<BaseObject> InterfaceEventList;

class BaseInterfaceEventSystem: public SystemObject {
public:
	MEMDEFAULT(BaseInterfaceEventSystem)

	enum EventType {
		Intersection = 0xFFFF0001
	};

	struct Event {
		void* id;
		unsigned int message;
		unsigned int wparam;
		unsigned int lparam;
	};

	virtual bool registerEvent(int ,BaseObject * ) {return false;}
	virtual bool unregisterEvent(int ) {return false;}
	virtual	void readEvents() {}
private:
	InterfaceEventList p_handles;

friend class InterfaceEventSystem;
};

}

#endif /* BASEINTERFACEEVENTSYSTEM_H_ */
