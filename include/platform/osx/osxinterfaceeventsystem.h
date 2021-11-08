/*
 * linuxinterfaceeventsystem.h
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr
 */

#ifndef LINUXINTERFACEEVENTSYSTEM_H_
#define LINUXINTERFACEEVENTSYSTEM_H_

#include <platform/base/baseinterfaceeventsystem.h>
#include <platform/platformapi.h>

namespace csad {

class PLATFORM_API InterfaceEventSystem : public BaseInterfaceEventSystem {
public:
	InterfaceEventSystem();

	bool registerEvent(int id,BaseObject * obj);
	bool unregisterEvent(int id);
	void readEvents();

	int newid() {return p_max++;}

private:
	fd_set p_mev;
	int p_max;
	bool p_isupdate;

	void maxUpdata();
};

}

#endif /* LINUXINTERFACEEVENTSYSTEM_H_ */
