/*
 * linuxlibrary.cpp
 *
 *  Created on: 11.12.2013
 *      Author: Panteleymonov Aleksandr
 */

#include <platform/platformapi.h>

#if defined (OS_LINUX)

#include <platform/library.h>
#include <platform/log.h>

OPTIMIZE_ON;

namespace csad {

Library::Library(char*path)
{
	p_libpath=path;
	p_header=0;
}

Library::Library(const char*path)
{
	p_libpath=path;
	p_header=0;
}

Library::~Library()
{
}

bool Library::open()
{
	p_header=dlopen(p_libpath.str(),RTLD_LAZY );
	if (p_header <= 0) {
		char *e=dlerror();
		if (!e) e=(char*)"";
		Log::console("Library::open() error open %s, %s",p_libpath.str(),e);
		return false;
	}
	return true;
}

bool Library::close()
{
	if (p_header) dlclose((void*)p_header);
	p_header=0;
	return true;
}

void *Library::getProc(char* name)
{
	if (p_header <= 0) {
		return 0;
	}
	void *func=dlsym((void*)p_header,name);
	return func;
}

void Library::findLib(BaseString* cpath,char* path,char* lib)
{
	*cpath=path;
	if (lib) {
		*cpath+="lib";
		*cpath+=lib;
		*cpath+=".so";
		void *header=dlopen(cpath->str(),RTLD_LAZY );
		if (!header) {
			*cpath=path;
			*cpath+="lib";
			*cpath+=lib;
			*cpath+=".so.1";
			header=dlopen(cpath->str(),RTLD_LAZY );
		}
		if (!header) {
			*cpath=path;
			*cpath+="lib";
			*cpath+=lib;
			*cpath+=".so.2";
			header=dlopen(cpath->str(),RTLD_LAZY );
		}
		if (header) {
			dlclose((void*)header);
		} else {
			*cpath=path;
			*cpath+="lib";
			*cpath+=lib;
			*cpath+=".so";
		}
	}
	//p_header=(void*)LoadLibraryA(str.str());
}

TYPEINFO(Library)

}

OPTIMIZE_OFF;

#endif
