/*
 * library.h
 *
 *  Created on: 26.11.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef LIBRARY_H_
#define LIBRARY_H_

#include <platform/platformapi.h>
#include <core/baseobject.h>
#include <bt.h>

namespace csad {

using namespace bt;

/**
 * @class Library
 *
 * @ingroup platform
 * @brief Library - dynamic linking of libraries.
 *
 * @see platform
 */

class Library {
public:
	MEMDEFAULT(Library)

	PLATFORM_API Library(char* path);
	PLATFORM_API Library(const char* path);
	PLATFORM_API virtual ~Library();

	/// Open library and return if sucsess
	PLATFORM_API virtual bool open();
	/// Close library
	PLATFORM_API virtual bool close();

	/// Return if library opened
	_FORCEINLINE bool isValid() {return ((_voidint)p_header)>0;}

	/// Return library path
	_FORCEINLINE const char *getPath() {return p_libpath.str();}
	/// return pointer to function for call it.
	PLATFORM_API virtual void *getProc(char* name);

	TYPEINFO_H

	/// Create path for open variant name lib.
	PLATFORM_API static void findLib(ShortString* cpath,char* path,char* lib);
	/// Create path for open variant name lib.
	_FORCEINLINE static void findLib(ShortString* cpath,const char* path,const char* lib) {return findLib(cpath,(char*)path,(char*)lib);}

private:
	ShortString p_libpath;
	void* p_header;
};

}

#endif /* LIBRARY_H_ */
