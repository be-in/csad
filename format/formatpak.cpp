/*
 * format3ds.cpp
 *
 *  Created on: 11.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#if defined(CSAD_PAK) || defined(PAK_CSAD)
#include <format.h>
#include <platform.h>
#include <scene/mesh.h>

OPTIMIZE_ON;

namespace csad {

	FormatPAK::FormatPAK()
	{
		fFile=0;
		headId=0;
		headFlag=0;
		fTableOffset=0;
		fTableNames=0;
	}

	FormatPAK::~FormatPAK()
	{
	}

	bool FormatPAK::readFromFile(char *name)
	{
		return true;
	}

	void FormatPAK::beginBuild(char *name)
	{
	}

	bool FormatPAK::addFile(char *name)
	{
		return true;
	}

	void FormatPAK::end()
	{
	}

};

OPTIMIZE_OFF;

#endif