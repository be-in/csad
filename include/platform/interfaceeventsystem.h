/*
 * interfaceeventsystem.h
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef INTERFACEEVENTSYSTEM_H_
#define INTERFACEEVENTSYSTEM_H_

#include <platform/platformapi.h>

namespace csad {

}

#if defined (OS_QNX)
#include "qnx/qnxinterfaceeventsystem.h"
#elif defined (OS_WIN)
#include "win/wininterfaceeventsystem.h"
#elif defined (OS_LINUX)
#include "linux/linuxinterfaceeventsystem.h"
#elif defined (OS_OSX)
#include "osx/osxinterfaceeventsystem.h"
#else
#include "unknow/unknowinterfaceeventsystem.h"
#endif

#endif /* INTERFACEEVENTSYSTEM_H_ */
