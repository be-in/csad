/*
 * keyboard.h
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <platform/platformapi.h>
#include <platform/base/basekeyboard.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

/**
 * @class Keyboard
 *
 * @ingroup input
 * @brief Keyboard - the object input system, platform dependent.
 *
 *
 *
 * For description in the configuration:
 @verbatim
   <Keyboard name="the name of the system" driver="driver settings" />
 @endverbatim
 *
 * @see input
 */

class Keyboard: public BaseKeyboard {
public:
	MEMDEFAULT(Keyboard)

	CSAD_API Keyboard(char* driver,char* name);
	CSAD_API Keyboard(const char* driver,const char* name="");

	/// Return if key pressed;
	CSAD_API bool getKey(int id);
	/// Return array of bits keys;
	CSAD_API char *getMap();

	CSAD_API void *set(unsigned _int32 ,void *);

	CSAD_API TYPEINFO_H

private:
	ShortString p_driver;
	int p_handle;
	char p_map[32];

	bool init();
	bool close();
	void read(void *msg);

};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* KEYBOARD_H_ */
