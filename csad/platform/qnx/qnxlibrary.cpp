/*
 * qnxlibrary.cpp
 *
 *  Created on: 26.11.2013
 *      Author: ????????????? ?
 */

#include <platform/platformapi.h>

#if defined (OS_QNX)

#include <platform/library.h>
#include <platform/qnx/qnxlog.h>

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
	p_header=dlopen(p_libpath.str(),RTLD_LAZYLOAD );
	if (p_header <= 0) {
		char *e=dlerror();
		if (!e) e="";
		Log::console("Library::open() error open %s, %s",p_libpath.str(),e);
		return false;
	}
	return true;
}

bool Library::close()
{
	dlclose((void*)p_header);
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
		void *header=dlopen(cpath->str(),RTLD_LAZYLOAD );
		if (!header) {
			*cpath=path;
			*cpath+="lib";
			*cpath+=lib;
			*cpath+=".so.1";
			header=dlopen(cpath->str(),RTLD_LAZYLOAD );
		}
		if (!header) {
			*cpath=path;
			*cpath+="lib";
			*cpath+=lib;
			*cpath+=".so.2";
			header=dlopen(cpath->str(),RTLD_LAZYLOAD );
		}
		if (header) {
			dlclose((void*)header);
		}
	}
	//p_header=(void*)LoadLibraryA(str.str());
}

TYPEINFO(Library)

}

#endif