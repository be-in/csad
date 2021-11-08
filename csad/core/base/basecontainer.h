/*
 * basecontainer.h
 *
 *  @brief core, 2003-2014
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef BASECONTAINER_H_
#define BASECONTAINER_H_

#include <bt/types.h>

OPTIMIZE_ON;

namespace csad {

	void _APICALL _ContainerDestructorDEF(void *);
	void _APICALL _ContainerFreeDEF(void *);
	void _APICALL _ContainerGetComponentByName(void *,char*);

}

OPTIMIZE_OFF;

#endif