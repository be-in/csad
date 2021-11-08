/*
 * text3d.cpp
 *
 *  Created on: 28.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/text3d.h>
#include <core/containercomponents.h>
#include <core/graph.h>
#include <scene/transform.h>
#include <scene/mesh.h>
#include <scene/meshfilter.h>
#include <scene/textstyle.h>
#include <scene/style.h>
#include <scene/fonttext.h>
#include <gen3.h>
#include <platform.h>
#include <bt.h>
#include "csad/core/base/stringconsts.h"

OPTIMIZE_ON;

namespace csad {

using namespace gen;

Text3D::Text3D():
	p_meshSize(0.0)
{
	p_isBuild=true;
	p_style=0;
	p_text="";
	p_zoffset=0;
	p_changes=0;
	p_resiver=0;
}

Text3D& Text3D::setStyle(char *name)
{
	Style *style=Graph::graph().getStyle(name);
	if (!style) {
#ifdef LOG_CSAD
		Log::console("Text3D::setStyle can`t find style %s",name);
#endif
		return *this;
	}
	setStyle(style);
	return *this;
}

Text3D& Text3D::setStyle(const char *name)
{
	setStyle((char*)name);
	return *this;
}

Text3D& Text3D::setStyle(Style *style)
{
	if (!style) return *this;
	TextStyle *mstyle=style->getComponent<TextStyle>();
	if (p_isBuild) p_isBuild=p_style==mstyle;
	p_style=mstyle;
	p_changes++;
	return *this;
}

Text3D& Text3D::setText(char *text)
{
	p_text=text;
	p_isBuild=false;
	p_changes++;
	return *this;
}

Text3D& Text3D::setText(const char *text)
{
	p_text=text;
	p_isBuild=false;
	p_changes++;
	return *this;
}

vector3d Text3D::textCenter()
{
	MeshFilter *mf=addComponent<MeshFilter>();
	vector3d vr(0.0);
	if (!mf) return vr;
	if (!mf->getMesh()) return vr;
	return vector3d((double *)&mf->getMesh()->getBoundSphere());
}

void Text3D::setOffset(float offset)
{
	p_zoffset=offset;
}

void Text3D::setResiver(BaseObject *resiver)
{
	p_resiver=resiver;
}

void Text3D::start()
{
	_buildMesh();
}

void Text3D::update()
{
	if (p_isBuild) return;
	_buildMesh();
}

void Text3D::quit()
{
	if (p_isBuild) {
		MeshFilter *mf=addComponent<MeshFilter>();
		Mesh *mesh=mf->getMesh();
		delete mesh;
		mesh=0;
		mf->setMesh(mesh);
	}
}

void * Text3D::set(unsigned _int32 id,void * param)
{
	if (id==BaseObject::TYPE) return Text3D::t();
	if (id==BaseObject::WRITE) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		if ((p=list.find(STR_TEXT))!=0) setText(p->getString());
		if ((p=list.find("style"))!=0) setStyle(p->getString());
		if ((p=list.find("zoffset"))!=0) setOffset(p->getFloat(0));
	}
	if (id==BaseObject::READ) {
		Variant *p;
		ParametersList *list=(ParametersList *)param;
		p=&(*list)[STR_TEXT];
		p->setString(p_text.str());
		p=&(*list)["style"];
		if (p_style) { p->setString(p_style->getPath()); } else { p->setString(""); }
		p=&(*list)["zoffset"];
		p->setFloat(p_zoffset);
		return param;
	}
	return 0;
}

Mesh* Text3D::createMesh(const char *name)
{
	MeshFilter *mf=getComponent<MeshFilter>();
	if (!mf) return 0;
	Mesh* mesh=mf->getMesh();
	if (!mesh) mesh=new Mesh(name);
	return mesh;
}

void Text3D::_buildMesh()
{
	MeshFilter *mf=addComponent<MeshFilter>();
	if (!mf) return;
	Mesh *mesh=mf->getMesh();
	VBOMesh *vbmesh=mf->getVBOMesh();
	if (!mesh) {
		mesh=new Mesh();
		mesh->setFields(Mesh::_TGL_0T2F+Mesh::_TGL_N3F+Mesh::_TGL_V3F);
	}
	if (vbmesh)
		vbmesh->context->freeVBOMesh(vbmesh);
	vbmesh=0;
	if (p_style) if (p_style->p_material) mf->setMaterial(p_style->p_material);
	mf->setMesh(mesh);

	ModellerMesh modeller;

	mesh->setIndexCount(0).setVertexCount(0);
	modeller.setMesh(mesh);
	if (p_style) {
		Font *font=p_style->getFont();
		if (font) {
			if (font->type()==Font::t()) {
				modeller.textFlat((char*)p_text.str(),p_style,p_zoffset,0);
			}
			if (font->type()==FontText::t()) {
				modeller.textTexture((char*)p_text.str(),p_style,p_zoffset);
			}
		}
	}

	mesh->calculateNormals();
	p_meshSize=mesh->calculateBound();
	p_isBuild=true;
	p_changes++;
	mesh->fixed();

	if (p_resiver) p_resiver->event(this,0,0,0);
}

TYPEINFO(Text3D)

}

OPTIMIZE_OFF;
