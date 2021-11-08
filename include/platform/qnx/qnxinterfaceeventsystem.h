/*
 * qnxinterfaceeventsystem.h
 *
 *  Created on: 09.08.2013
 *      Author: Пантелеймонов Александр
 */

#ifndef QNXINTERFACEEVENTSYSTEM_H_
#define QNXINTERFACEEVENTSYSTEM_H_

#include <platform/base/baseinterfaceeventsystem.h>
#include <platform/platformapi.h>

namespace csad {

class PLATFORM_API InterfaceEventSystem : public BaseInterfaceEventSystem {
public:
	InterfaceEventSystem();

	bool registerEvent(int id,BaseObject * obj);
	bool unregisterEvent(int id);
	void readEvents();

private:
	fd_set p_mev;
	int p_max;
	bool p_isupdate;

	void maxUpdata();
};

}

#endif /* QNXINTERFACEEVENTSYSTEM_H_ */
