/*
 * formatpak.h
 *
 *  Created on: 10.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#if defined(CSAD_PAK) || defined(PAK_CSAD) || !defined(CSAD_LOCAL)
#ifndef FORMATPAK_H_
#define FORMATPAK_H_

#include <core/baseobject.h>
#include <core/csadapi.h>

OPTIMIZE_ON;

namespace csad {

class File;

/**
 * @class FormatPAK
 *
 * @ingroup format
 * @brief FormatPAK - файл контейнер.
 *
 * @see format
 */

class CSAD_API FormatPAK {
public:
	FormatPAK();
	~FormatPAK();

	bool readFromFile(char *name);
	bool readFromFile(const char *name) { return readFromFile((char*)name); }

	void beginBuild(char *name);
	void beginBuild(const char *name) { beginBuild((char*)name); }
	bool addFile(char *name);
	bool addFile(const char *name) { return addFile((char*)name); }
	void end();
	
private:
	File*fFile;
	unsigned int headId;
	unsigned int headFlag;
	unsigned int headCount;
	unsigned int headReserv;
	unsigned int *fTableOffset;
	char *fTableNames;
};

}

OPTIMIZE_OFF;

#endif
#endif