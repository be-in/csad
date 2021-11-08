/*
 * groupmesh.cpp
 *
 *  Created on: 28.04.2014
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/groupmesh.h>
#include <scene/transform.h>
#include <scene/material.h>
#include <scene/meshfilter.h>
#include <scene/mesh.h>
#include <gen3/modellermesh.h>

OPTIMIZE_ON;

namespace csad {

GroupMesh::GroupMesh()
{
	fflags=0;
}

GroupMesh::~GroupMesh()
{
}

void GroupMesh::setMaterial(Material *mat)
{
	MeshFilter *mf=getComponent<MeshFilter>();
	if (!mf) mf=addComponent<MeshFilter>();
	mf->setMaterial(mat);
}

bool GroupMesh::addTransform(Transform *tr)
{
/*	MeshFilter *mf=tr->getComponent<MeshFilter>();
	if (!mf) return false;
	Mesh *mesh=mf->getMesh();
	if (!mesh) return false;*/
	ftrMeshList.assign(tr);
	return true;
}

void GroupMesh::removeTransform(Transform *)
{
	//ftrMeshList.
}

void GroupMesh::update()
{
	if (fflags) return;

	Transform **trs=(Transform **)ftrMeshList.data();
	unsigned int count=ftrMeshList.count();

	MeshFilter *mf=getComponent<MeshFilter>();
	if (!mf) mf=addComponent<MeshFilter>();

	Mesh *mesh=mf->getMesh();
	if (!mesh) {
		mesh=new Mesh();
		mf->setMesh(mesh);
	}

	unsigned int indexcount=0;
	unsigned int elementscount=0;
	MeshFilter *mfs=(*trs)->getComponent<MeshFilter>();
	if (!mfs) return;
	if (!mf->getMaterial()) mf->setMaterial(mfs->getMaterial());
	Mesh *ss=mfs->getMesh();
	if (!ss) return;
	unsigned int format=ss->getFields();
	Mesh::stDrawFormat drawFormat=ss->getDrawFormat();
	while (count>0) {
		Transform *tr=*trs;
		count--;
		if (tr->isVisible()) {
			mfs=tr->getComponent<MeshFilter>();
			if (!mfs) return;
			ss=mfs->getMesh();
			if (!ss) return;
			if (ss->getFields()!=format) return;
			indexcount+=ss->indexCount();
			elementscount+=ss->elementsCount();
		}
		trs++;
	}
	if (mesh->getFields()==format && mesh->indexCount()==indexcount && mesh->elementsCount()==elementscount) {
		return;
	}
	mesh->setFields(format);
	mesh->setDrawFormat(drawFormat);
	mesh->setIndexCount(indexcount);
	mesh->setVertexCount(elementscount);
	fflags=0;
}

void GroupMesh::prepare()
{
	if (fflags) return;
	MeshFilter *mf=getComponent<MeshFilter>();
	Mesh *mesh=mf->getMesh();
	
	gen::ModellerMesh meshmod;
	meshmod.setMesh(mesh);

	Transform **trs=(Transform **)ftrMeshList.data();
	unsigned int count=ftrMeshList.count();
	unsigned int format=mesh->getFields();
	unsigned int indexcount=0;
	unsigned int elementscount=0;

	Transform *transform=getContainer();
	transform->setChildReal(transform);
	transform->setParentReal(transform);
	while (count>0) {
		Transform *tr=*trs;
		count--;
		if (tr->isVisible()) {
			mf=tr->getComponent<MeshFilter>();
			if (!mf) return;
			Mesh *ss=mf->getMesh();
			if (!ss) return;
			if (ss->getFields()!=format) return;
			meshmod.TRS(tr->realPosition(),tr->realRotate(),tr->realScale());
			meshmod.copyIndex(ss,indexcount,0,ss->indexCount(),elementscount);
			meshmod.copyVertex(ss,elementscount,0,ss->elementsCount());
			meshmod.Transform(elementscount,ss->elementsCount());
			indexcount+=ss->indexCount();
			elementscount+=ss->elementsCount();
		}
		tr->setVisible(false);
		trs++;
	}
	fflags=1;
}

void *GroupMesh::set(unsigned _int32 id,void*)
{
	if (id==BaseObject::TYPE) return GroupMesh::t();
	return 0;
}

TYPEINFO(GroupMesh);

};

OPTIMIZE_OFF;
