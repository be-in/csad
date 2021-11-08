/*
 * log.h
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#if defined(LOG_CSAD) | !defined(CSAD_LOCAL)
#ifndef LOG_H_
#define LOG_H_

#include <platform/platformapi.h>

namespace csad {

}

#if defined (OS_QNX)
#include "qnx/qnxlog.h"
#elif defined (OS_WIN)
#include "win/winlog.h"
#elif defined (OS_LINUX)
#include "linux/linuxlog.h"
#elif defined (OS_OSX)
#include "osx/osxlog.h"
#else
#include "unknow/unknowlog.h"
#endif

#endif /* LOG_H_ */
#endif