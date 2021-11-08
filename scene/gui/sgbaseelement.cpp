/*
 * sgbaseelement.cpp
 *
 *  Created on: 06.12.2013
 *      Author: Пантелеймонов Александр
 */

#include <scene/gui/sgbaseelement.h>
#include <scene/transform.h>
#include <scene/text3d.h>
#include <scene/meshfilter.h>
#include <scene/mesh.h>
#include <scene/style.h>
#include <scene/sceneresender.h>

OPTIMIZE_ON;

namespace csad {

SGBaseElement::SGBaseElement()
{

}

SGBaseElement::~SGBaseElement()
{

}

void SGBaseElement::_setMaterial(Transform *tr,Material*mat)
{
	if (!mat) return;
	MeshFilter *mf=tr->addComponent<MeshFilter>();
	if (!mf) return;
	mf->setMaterial(mat);
}

Transform* SGBaseElement::_initBack(Transform *tr,vector3f *size,float back)
{
	bool meshbuild=(tr!=0);
	if (!tr) {
		tr=getContainer();
		tr=tr->createTransform();
	}
	tr->setPosition(0,0,back);
	if (size) tr->setScale(size);
	if (meshbuild) return tr;
	MeshFilter *mf=tr->addComponent<MeshFilter>();
	Mesh *mesh=mf->getMesh();
	if (!mesh) mesh=Mesh::Quad;
	mf->setMesh(mesh);
	return tr;
}

Transform* SGBaseElement::_initBackInput(Transform *tr,vector3f *size,float back)
{
	bool meshbuild=(tr!=0);
	if (!tr) {
		tr=getContainer();
		tr=tr->createTransform();
	}
	tr->setPosition(0,0,back);
	if (size) tr->setScale(size);
	if (meshbuild) return tr;
	tr->setSelected(true);
	SceneResender *rs=tr->addComponent<SceneResender>();
	rs->setReceiver(this);
	MeshFilter *mf=tr->addComponent<MeshFilter>();
	Mesh *mesh=mf->getMesh();
	if (!mesh) mesh=Mesh::Quad;
	mf->setMesh(mesh);
	return tr;
}

Transform* SGBaseElement::_initKeyInput(Transform *tr,vector3f *size,BaseObject *res,float back)
{
	bool meshbuild=(tr!=0);
	if (!tr) {
		tr=getContainer();
		tr=tr->createTransform();
	}
	tr->setPosition(0,0,back);
	if (size) tr->setScale(size);
	if (meshbuild) return tr;
	tr->setSelected(true);
	if (res) {
		SceneResender *rs=tr->addComponent<SceneResender>();
		rs->setReceiver(res);
	}
	MeshFilter *mf=tr->addComponent<MeshFilter>();
	Mesh *mesh=mf->getMesh();
	if (!mesh) mesh=Mesh::Quad;
	mf->setMesh(mesh);
	return tr;
}

Transform* SGBaseElement::_initText(Transform *tr,char *text,Style *style)
{
	if (!tr) {
		tr=getContainer();
		tr=tr->createTransform();
	}
	Text3D *ctext=tr->addComponent<Text3D>();
	ctext->setResiver(this);
	if (text) ctext->setText(text);
	if (style) ctext->setStyle(style);
	//ctext->setResiver(this);
	return tr;
}

Text3D* SGBaseElement::_initText(Transform **tr)
{
	if (!*tr) {
		*tr=getContainer();
		*tr=(*tr)->createTransform();
	}
	Text3D *ctext=(*tr)->addComponent<Text3D>();
	return ctext;
}

}

OPTIMIZE_OFF;
