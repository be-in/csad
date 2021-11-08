/*
 * sglineedit.cpp
 *
 *  Created on: 05.12.2013
 *      Author: ������������� ���������
 */
/*
#include <scene/gui/sglineedit.h>
#include <scene/transform.h>
#include <scene/text3d.h>
#include <scene/meshfilter.h>
#include <scene/mesh.h>
#include <scene/style.h>
#include <core/graph.h>
#include <core/system.h>
#include <core/input.h>

namespace csad {

SGLineEdit::SGLineEdit()
{

}

void SGLineEdit::setText(char *text)
{
	Text3D *mtext = addComponent<Text3D>();
	if (!mtext) return;
	mtext->setText(text);
	mtext->setStyle(p_style);
}

const char *SGLineEdit::getText()
{
	Text3D *mtext = addComponent<Text3D>();
	if (!mtext) return 0;
	return mtext->text();
}

void SGLineEdit::setStyle(char *name)
{
	setStyle(Graph::graph().getStyle(name));
}

void SGLineEdit::setStyle(Style *style)
{
	p_style=style;
	Text3D *mtext = getComponent<Text3D>();
	if (!mtext) return;
	mtext->setStyle(style);
}

void SGLineEdit::setSize(vector3f &size)
{
	p_size=size;
	if (!p_back) _initBack();
	p_back->setScale(p_size);
	p_back->setPosition(0,0,-p_size.y*0.01);
}

void SGLineEdit::update()
{

}

void * SGLineEdit::set(unsigned int id,void * param)
{
	if (id==BaseObject::TYPE) return SGLineEdit::t();
	//if (id==BaseObject::SELECT) return _select(); // ???
	if (id==BaseObject::WRITE) {
		ParametersList *list=(ParametersList *)param;
		if (list->contains("text")) setText((*list)["text"].getString());
		if (list->contains("style")) setStyle((*list)["style"].getString());
		if (list->contains("size")) setSize((*list)["size"].getVector3f());
		//if (list->contains("receiver")) setReceiver((*list)["receiver"].getString());
	}
	if (id==BaseObject::READ) {
		Variant *p;
		ParametersList *list=(ParametersList *)param;
		p=&(*list)["style"];
		if (p_style) { p->setString(p_style->getPath()); } else {p->setString("");}
		p=&(*list)["size"];
		p->setVector3f(&p_size);
		return param;
	}
	return 0;
}

void SGLineEdit::_init()
{
	if (!p_back) _initBack();
	//p_isBuild=true;
}

void SGLineEdit::_initBack()
{
	if (!p_back) {
		Transform *tr=getContainer();
		p_back=tr->createTransform();
		p_back->setPosition(0,0,-p_size.y*0.01);
		p_back->setSelected(true);
		//Resender *rs=p_back->addComponent<Resender>();
		//rs->setReceiver(this);
		MeshFilter *mf=p_back->addComponent<MeshFilter>();
		Mesh *mesh=mf->getMesh();
		if (!mesh) mesh=Mesh::Quad;
		mf->setMesh(mesh);
	}
}

TYPEINFO(SGLineEdit)

}*/
