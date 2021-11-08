/*
 * format3ds.cpp
 *
 *  Created on: 11.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#if defined(CSAD_3DS) || defined(_3DS_CSAD)
#include <format.h>
#include <platform.h>
#include <scene/mesh.h>

OPTIMIZE_ON;

namespace csad {

Format3DS::Format3DS()
{

}

bool Format3DS::readFromFile(char *name)
{
	File file(name,File::READ);
	if (!file.open()) return false;
	readFromFile(&file);
	file.close();

	return true;
}

bool Format3DS::readFromFile(File *)
{
	clear();
	//if (p_root==0) p_root=new XMLNode();
	//p_root->setName(file->getFileName());

	/*if (!_readFromFile(file,p_root)) {

	}*/
	return true;
}

void Format3DS::toMesh(Mesh *mesh)
{

}

void Format3DS::clear()
{

}

}

OPTIMIZE_OFF;

#endif