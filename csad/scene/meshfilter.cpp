/*
 * meshfilter.cpp
 *
 *  Created on: 16.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <bt.h>
#include <scene/meshfilter.h>
#include <scene/mesh.h>
#include <scene/material.h>
#include <scene/transform.h>
#include <scene/scene.h>
#include <scene/lightingmodel.h>
#include <scene/shader.h>
#include <core/graph.h>
#include "csad/core/base/stringconsts.h"

OPTIMIZE_ON;

namespace csad {

using namespace bt;

MeshFilter::MeshFilter()
{
	fmesh=0;
	fshader=0;
	fmaterial=0;
	flightmodel=0;
}

MeshFilter::~MeshFilter()
{
}

Mesh *MeshFilter::getMesh()
{
	if (!fmesh) return 0;
	return fmesh->getMesh();
}

VBOMesh *MeshFilter::getVBOMesh()
{
	if (!fmesh) return 0;
	return fmesh->getVBOMesh();
}

MeshFilter& MeshFilter::setMesh(char * )
{
	return *this;
}

MeshFilter& MeshFilter::setMesh(BaseMesh * mesh)
{
	fmesh=mesh;
	return *this;
}

MeshFilter& MeshFilter::setShader(char * name)
{
	fshader=Graph::graph().getShader(name);
	return *this;
}

MeshFilter& MeshFilter::setShader(Shader * shader)
{
	fshader=shader;
	return *this;
}

MeshFilter& MeshFilter::setMaterial(char * name)
{
	fmaterial=Graph::graph().getMaterial(name);
	return *this;
}

MeshFilter& MeshFilter::setMaterial(Material *material)
{
	fmaterial=material;
	return *this;
}

MeshFilter& MeshFilter::setLightingModel(char * name)
{
	csad::Transform *tr=getContainer();
	if (tr) {
		csad::Scene *scene=tr->getScene();
		if (scene) flightmodel=scene->getLightingModel(name);
	}
	return *this;
}

MeshFilter& MeshFilter::setLightingModel(LightingModel *model)
{
	flightmodel=model;
	return *this;
}

void *MeshFilter::set(unsigned _int32 id,void * param)
{
	if (id==BaseObject::TYPE) return MeshFilter::t();
	if (id==BaseObject::WRITE) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		if ((p=list.find("shader"))!=0) setShader(p->getString());
		if ((p=list.find(STR_MATERIAL))!=0) setMaterial(p->getString());
		if ((p=list.find("mesh"))!=0) setMesh(p->getString());
		if ((p=list.find("lightingmodel"))!=0) setLightingModel(p->getString());
	}
	if (id==BaseObject::READ) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		if (fmaterial) {
			p=&list[STR_MATERIAL];
			p->setString(fmaterial->getName());
		}
		if (fmesh) {
			p=&list["mesh"];
			p->setString("select");
		}
	}
	return 0;
}

TYPEINFO(MeshFilter)

}

OPTIMIZE_OFF;
