/*
 * meshscript.h
 *
 *  @brief core, 2003-2014
 *
 *  Created on: 12.04.2008
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#pragma once
#ifndef GEN_MESH_SCRIPT_H
#define GEN_MESH_SCRIPT_H

#include <bt.h>
#include <gen3/genfunctions.h>
#include <scene/mesh.h>

OPTIMIZE_ON;

namespace csad {
	class File;
}

namespace gen {

class MeshScript {
public:
	MEMDEFAULT(MeshScript)

	_FORCEINLINE MeshScript():mesh(0),ftext(0) {}
	GEN_API ~MeshScript();

	_FORCEINLINE csad::Mesh *result() {return mesh;}

	_FORCEINLINE char *text() {return ftext;}

	GEN_API bool exec();

	GEN_API bool readFromFile(char *name);
	GEN_API bool readFromFile(csad::File *file);

private:
	bt::sScript script;
	csad::Mesh *mesh;
	char *ftext;
};

}

OPTIMIZE_OFF;

#endif //GEN_RASTER_SCRIPT_H