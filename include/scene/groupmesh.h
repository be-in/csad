/*
 * groupmesh.h
 *
 *  Created on: 28.04.2014
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef GROUPMESH_H_
#define GROUPMESH_H_

#include <bt.h>
#include <scene/scenecomponent.h>

OPTIMIZE_ON;

namespace csad {

class Material;
class Transform;

class GroupMesh:public SceneComponent {
public:
	MEMMANAGER(GroupMesh)

	CSAD_API GroupMesh();
	CSAD_API ~GroupMesh();

	CSAD_API void setMaterial(Material *mat);
	CSAD_API bool addTransform(Transform *tr);
	CSAD_API void removeTransform(Transform *tr);

	CSAD_API void update();
	CSAD_API void prepare();

	CSAD_API void *set(unsigned _int32 id,void*);

	CSAD_API TYPEINFO_H

private:
	unsigned int fflags;
	bt::VoidVector<void> ftrMeshList;
	//fmesh;
};

};

OPTIMIZE_OFF;

#endif