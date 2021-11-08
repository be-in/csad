/*
 * module.h
 *
 *  Created on: 16.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich
 */

#ifndef MODULE_H_
#define MODULE_H_

#include <core/baseobject.h>
#include <core/csadapi.h>
#include <platform/library.h>

namespace csad {

/**
 * @class Module
 *
 * @ingroup core
 * @brief Module - dynamic module contains system components.
 *
 * Allows you to connect additional components in the form of libraries, extending the basic features.
 *
 * @verbatim
 * <Module path="/mycomponents/app.so.1" />
 * <Module path="/mycomponents/app.dll" />
 *
 * <Module path="/mycomponents/" lib="app" />
 * @endverbatim
 *
 * @see core
 */

class Module:public BaseObject {
public:
	MEMDEFAULT(Module)

	CSAD_API Module(char *path);
	CSAD_API ~Module();

	/// returns true if the module is active
	_FORCEINLINE bool isInit() {return lib.isValid();}
	/// returns the method by name
	_FORCEINLINE void *getProc(char* name) {return lib.getProc(name);}
	_FORCEINLINE void *getProc(const char* name) {return lib.getProc((char*)name);}

	CSAD_API void *set(unsigned _int32,void*);

	CSAD_API TYPEINFO_H
private:
	Library lib;
};

}

#endif /* MODULE_H_ */
