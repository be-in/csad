/*
 * mouse.h
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef MOUSE_H_
#define MOUSE_H_

#include <platform/base/basemouse.h>
#include <platform/platformapi.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

/**
 * @class Mouse
 *
 * @ingroup input
 * @brief Mouse - the object input system, platform dependent.
 *
 *
 * For description in the configuration:
 @verbatim
   <Mouse name="טלÿ ג סטסעולו" driver="ןאנאלוענû הנאיגונא" />
 @endverbatim
 * @see input
 */

using namespace bt;

class Mouse : public BaseMouse {
public:
	MEMDEFAULT(Mouse)

	PLATFORM_API Mouse(char* driver,char* name);
	PLATFORM_API Mouse(const char* driver,const char* name="");

	PLATFORM_API void setDriver(char *param);

	PLATFORM_API void *set(unsigned _int32 ,void *);

	PLATFORM_API static void setCursorPos(float x,float y);

	PLATFORM_API TYPEINFO_H

private:
	ShortString p_driver;
	int p_handle;

	bool init();
	bool close();
	void read(void *msg);
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* MOUSE_H_ */
