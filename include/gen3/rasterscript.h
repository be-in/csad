/*
 * rasterscript.h
 *
 *  @brief core, 2003-2014
 *
 *  Created on: 12.04.2008
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#pragma once
#ifndef GEN_RASTER_SCRIPT_H
#define GEN_RASTER_SCRIPT_H

#include <bt.h>
#include <gen3/genfunctions.h>

OPTIMIZE_ON;

namespace csad {
	class File;
}

namespace gen {

class RasterScript {
public:
	MEMDEFAULT(RasterScript)

	_FORCEINLINE RasterScript():raster(0),ftext(0) {}
	GEN_API ~RasterScript();

	_FORCEINLINE Raster *result() {return raster;}

	_FORCEINLINE char *text() {return ftext;}

	GEN_API bool exec();

	GEN_API bool readFromFile(char *name);
	GEN_API bool readFromFile(csad::File *file);

private:
	bt::sScript script;
	Raster *raster;
	char *ftext;
};

}

OPTIMIZE_OFF;

#endif //GEN_RASTER_SCRIPT_H