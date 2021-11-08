/*
 * basecontainer.cpp
 *
 *  @brief core, 2003-2014
 *
 *  Created on: 27.08.2014
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include "basecontainer.h"
#include "csad/core/csadcore.h"
#include <core/containercomponents.h>
#include <core/component.h>
#include <bt/functions.h>

OPTIMIZE_ON;

namespace csad {

/*class OpenContainerComponents: public csad::ContainerComponents {
public:
	_FORCEINLINE void *& list() {return p_list;}
};*/

class OpenComponent: public csad::Component {
public:
	_FORCEINLINE void *& parent() {return (void*&)p_parent;}
};

void _APICALL _ContainerDestructorDEF(void *container)
{
	csad::ContainerComponents *fcontainer=(csad::ContainerComponents *)container;
	if ((core!=fcontainer) && (core!=0))
		((LocalCore*)core)->containers().del(fcontainer);
	_ContainerFreeDEF(container);
}

void _APICALL _ContainerFreeDEF(void *container)
{
	csad::ContainerComponents *fcontainer=(csad::ContainerComponents *)container;
	void **flist=(void **)&fcontainer->list();
	void **it=(void **)arrFunctions.MPArray(flist);
	unsigned int count=arrFunctions.MPCount(flist);
	while (count>0) {
		it++;
		OpenComponent *component=(OpenComponent *)*it;
		component->parent()=0;
		delete component;
		it++;
		count--;
	}
	arrFunctions.MPFree(flist);
}

}

OPTIMIZE_OFF;
