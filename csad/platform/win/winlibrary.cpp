/*
 * winlibrary.cpp
 *
 *  Created on: 11.12.2013
 *      Author: Пантелеймонов А
 */

#include <platform/platformapi.h>

#if defined (OS_WIN)

#include <platform/library.h>
#include <platform/win/winlog.h>
#include <WinBase.h>

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
	p_header=(void*)LoadLibraryA(p_libpath.str());
	if (p_header == 0) {
		int err=GetLastError();
#ifdef LOG_CSAD
		Log::console("Library::open() error open file: %s err: %s",p_libpath.str(),strerror(err));
#endif
		return false;
	}
	return true;
}

bool Library::close()
{
	FreeLibrary((HMODULE)p_header);
	p_header=0;
	return true;
}

void *Library::getProc(char* name)
{
	if (p_header == 0) {
		return 0;
	}
	void *func=(void*)GetProcAddress((HMODULE)p_header,name);
	return func;
}

void Library::findLib(ShortString* cpath,char* path,char* lib)
{
	*cpath=path;
	if (lib) {
		*cpath+=lib;
		*cpath+=".dll";
	}
	//p_header=(void*)LoadLibraryA(str.str());
}

TYPEINFO(Library)

}

OPTIMIZE_OFF;

#endif