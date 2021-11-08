/*
 * wininterfaceeventsystem.h
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef WININTERFACEEVENTSYSTEM_H_
#define WININTERFACEEVENTSYSTEM_H_

#include <platform/base/baseinterfaceeventsystem.h>
#include <platform/platformapi.h>

namespace csad {

class InterfaceEventSystem : public BaseInterfaceEventSystem {
public:
	PLATFORM_API InterfaceEventSystem();
	PLATFORM_API ~InterfaceEventSystem();

	PLATFORM_API bool registerEvent(int id,BaseObject * obj);
	PLATFORM_API bool unregisterEvent(int id);
	PLATFORM_API void readEvents();

	_FORCEINLINE int newid() {return p_max++;}

private:
	int p_max;
	bool p_isupdate;
};

}

#endif /* WININTERFACEEVENTSYSTEM_H_ */
