/*
 * sgmouse.cpp
 *
 *  Created on: 19.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/gui/sgmouse.h>
#include <platform.h>
#include <scene/transform.h>
#include <scene/mesh.h>
#include <scene/camera.h>
#include <scene/meshfilter.h>
#include <scene/material.h>
#include <gen3.h>
#include <core/graph.h>
#include <core/input.h>
#include "csad/core/base/stringconsts.h"

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

SGMouse::SGMouse()
{
	p_XYscale=1.0f;
}

void SGMouse::setZoom(float scale)
{
	p_XYscale=scale;
}

void SGMouse::prepare()
{
	//vector3f pos=Input::input().getCursorPos();
	GlContext *context=GlContext::getCurrent();
	if (!context) return;
	Display *display=context->getDisplay();

	bt::matrix4f &matr=*(Camera::camera()->projMatrix());
	float d=2/matr.m[5];

/*	display->toLocal((vector2f*)&pos,(vector2f*)&pos);
	double lscale=p_XYscale*d/vp.w;
	pos.x=(pos.x-vp.z*0.5-vp.x)*lscale;
	pos.y=(vp.y+vp.w*0.5-pos.y)*lscale;
	pos.z=-1;*/
	vector3f pos=normal(display,Camera::camera());

	Transform *tr=getContainer();
	tr->setVisible(true);
	tr->setPosition(pos+Camera::camera()->getContainer()->getPosition());
	tr->setScale(d,d,d);
}

/*void SGMouse::date() //???
{
	int w=GlContext::getCurrent()->width();
	int h=GlContext::getCurrent()->height();
}*/

void * SGMouse::set(unsigned _int32 id, void * param)
{
	if (id==BaseObject::TYPE) return SGMouse::t();
	if (id==BaseObject::WRITE) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		if ((p=list.find("zoom"))!=0) setZoom(p->getFloat(1.0f));
	}
	if (id==BaseObject::READ) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		p=&list["zoom"];
		p->setFloat(getZoom());
		return param;
	}
	/*if (id==BaseObject::ONRENDER) {    ???
		
	}*/
	return 0;
}

bt::vector3f SGMouse::normal(Display *display,Camera *camera)
{
	vector3f pos=Input::input().getCursorPos();

	//if (!camera)
		//camera = Camera::camera();
	if (!Camera::camera())
		return bt::vector3f(0.0f,0.0f,1.0f);
	vector4i vp=Camera::camera()->getViewPort(display);
	vector4f vpf;
	vecFunctions.V4ITo4F(&vp,&vpf);
	bt::matrix4f &matr=*(camera->projMatrix());
	float d=2/matr.m[5];

	display->toLocal((vector2f*)&pos,(vector2f*)&pos);
	double lscale=d/vp.w;
	vecFunctions.V2FSub(&pos,&vpf,&pos);
	vecFunctions.V2FCombine(&pos,&vpf.z,&pos,lscale,-0.5f*lscale);
	pos.y=-pos.y;
	pos.z=-1;
	return pos;
}

//void SGMouse::onRender()  ???

SGMouseMesh::SGMouseMesh()
{
	p_material=0;
	fline=0;
	p_linematerial=0;
}

void SGMouseMesh::setMaterial(char *name)
{
	p_material=Graph::graph().getMaterial(name);
}

void SGMouseMesh::setLineMaterial(char *name)
{
	p_linematerial=Graph::graph().getMaterial(name);
}

void SGMouseMesh::start()
{
	ftrline=getContainer()->createTransform();
	MeshFilter *lmf=ftrline->addComponent<MeshFilter>();
	MeshFilter *mf=addComponent<MeshFilter>();
	if (!mf || !lmf) return;
	Mesh *mesh=mf->getMesh();
	if (!mesh) {
		mesh=new Mesh();
		mesh->setFields(Mesh::_TGL_0T2F+Mesh::_TGL_V2F);
	}
	fline=lmf->getMesh();
	if (!fline) {
		fline=new Mesh();
		fline->setFields(Mesh::_TGL_0T2F+Mesh::_TGL_V2F);
	}
	_buildMesh(mesh,fline);
	lmf->setMesh(fline);
	lmf->setMaterial(p_linematerial);
	mf->setMesh(mesh);
	mf->setMaterial(p_material);
}

void SGMouseMesh::prepare()
{
	//vector3f pos=Input::input().getCursorPos();
	GlContext *context=GlContext::getCurrent();
	if (!context) return;

	ftrline->setVisible(true);
}

void SGMouseMesh::quit()
{
	delete fline;
	fline=0;
	MeshFilter *mf=getComponent<MeshFilter>();
	if (!mf) return;
	Mesh *mesh=mf->getMesh();
	if (mesh) delete mesh;
	mesh=0;
	mf->setMesh(mesh);
}

void * SGMouseMesh::set(unsigned _int32 id, void * param)
{
	if (id==BaseObject::TYPE) return SGMouseMesh::t();
	if (id==BaseObject::WRITE) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		if ((p=list.find(STR_MATERIAL))!=0) setMaterial(p->getString());
		if ((p=list.find("linematerial"))!=0) setLineMaterial(p->getString());
	}
	if (id==BaseObject::READ) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		p=&list[STR_MATERIAL];
		if (p_material) p->setString(p_material->getName());
		p=&list["linematerial"];
		if (p_linematerial) p->setString(p_linematerial->getName());
		return param;
	}
	/*if (id==BaseObject::ONRENDER) {    ???
		
	}*/
	return 0;
}

bt::vector2f vMousepat[]={bt::vector2f(0.0f,0.0f),bt::vector2f(0.0146f,0.006f),bt::vector2f(0.013f,0.0014f),bt::vector2f(0.018f,0.0014f),bt::vector2f(0.018f,-0.0014f),bt::vector2f(0.013f,-0.0014f),bt::vector2f(0.0146f,-0.006f)};

void SGMouseMesh::_buildMesh(Mesh *mesh,Mesh *linemesh)
{
	ModellerMesh modeller;

	modeller.setMesh(mesh);
	quaterniond r(0.0f,0.0f,1.0f,67.5*PI180);
	quaternionf rf(r);
	modeller.addRotation(&r);
	GeometryPath2F path;
	GeometryPath<vector2f> &tpath=*(GeometryPath<vector2f>*)&path;
	int i=0;
	while (i<7) {
		tpath.addVector(vMousepat[i]);
		i++;
	}
	modeller.fill(&path);

	linemesh->setDrawFormat(Mesh::_GL_LINE_LOOP).setVertexCount(tpath.count()).setIndexCount(tpath.count());
	LinkArray<vector2f> vectors=linemesh->vector<vector2f>();
	for (unsigned int i=0;i<tpath.count();i++) {
		vectors[i]=((tpath.vectors()[i])*rf.invert());
		linemesh->setIndex(i,i);
	}

	mesh->calculateBound();
	linemesh->calculateBound();
	mesh->fixed();
	linemesh->fixed();
	//mesh->calculateNormals();
}

TYPEINFO(SGMouse)
TYPEINFO(SGMouseMesh)

}

OPTIMIZE_OFF;
WARNING_ENABLE;
