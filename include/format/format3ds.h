/*
 * format3ds.h
 *
 *  Created on: 21.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#if defined(CSAD_3DS) || defined(_3DS_CSAD) || !defined(CSAD_LOCAL)
#ifndef FORMAT3DS_H_
#define FORMAT3DS_H_

OPTIMIZE_ON;

namespace csad {

class File;
class Mesh;

/**
 * @class Format3DS
 *
 * @ingroup format
 * @brief Format3DS - файл экспортируемого формата 3D Studio Max.
 *
 * @see format
 */

class Format3DS {
public:
	Format3DS();

	bool readFromFile(char *name);
	bool readFromFile(const char *name) { return readFromFile((char*)name); }
	bool readFromFile(File *file);

	void toMesh(Mesh *mesh);

	void clear();
private:

};

}

OPTIMIZE_OFF;

#endif /* FORMAT3DS_H_ */

#endif