/*
 * material.cpp
 *
 *  Created on: 03.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/material.h>
#include <platform.h>
#include <bt.h>
#include <scene/texture2d.h>
#include <core/graph.h>
#include "csad/core/csadcore.h"
#include "csad/core/base/stringconsts.h"

OPTIMIZE_ON;

namespace csad {

Material::Material(char * name)
{
	init(name);
}

Material::Material(const char * name)
{
	init((char*)name);
}

Material::~Material()
{
	arrFunctions.ANTFree(&ftexturesMatrix);
	Graph::graph().getMaterials()->detachObject(this);
}

void Material::init(char *name)
{
	arrFunctions.ANTInit(&ftexturesMatrix,sizeof(bt::matrix4f),0);
	p_diffuse=vector4f((float)1.0,(float)1.0,(float)1.0,(float)1.0);
	p_ambient=vector4f((float)0.0,(float)0.0,(float)0.0,(float)1.0);
	p_emission=vector4f((float)0.05,(float)0.05,(float)0.05,(float)1.0);
	p_specular=vector4f((float)1.0,(float)1.0,(float)1.0,(float)1.0);
	p_blend_src=NONE;
	p_blend_dst=NONE;
	flineWidth=1.0f;
	fpointSize=2.0f;
	p_alpha=NONE;
	p_alpha_ref=0.5f;
	p_depth=NONE;
	fflag=GL_DEPTHWRITE;
	Graph::graph().getMaterials()->addObject(this,name);
}

void Material::setDiffuse(vector4f &color)
{
	p_diffuse=color;
}

/*void Material::setDiffuse(float r,float g,float b,float a)
{
	p_diffuse.x=r;
	p_diffuse.y=g;
	p_diffuse.z=b;
	p_diffuse.w=a;
}*/

void Material::setAmbient(vector4f &color)
{
	p_ambient=color;
}

void Material::setSpecular(vector4f &color)
{
	p_specular=color;
}

void Material::setEmission(vector4f &color)
{
	p_emission=color;
}

void Material::setBlend(int src,int dst)
{
	p_blend_src=src;
	p_blend_dst=dst;
}

void Material::setBlend(char* src,char* dst)
{
	ClassManager *cm=core->classManager();
	setBlend((int)cm->getConst(src),(int)cm->getConst(dst));
}

void Material::setAlpha(int func,float ref)
{
	p_alpha=func;
	p_alpha_ref=ref;
}

void Material::setAlpha(char* func,float ref)
{
	ClassManager *cm=core->classManager();
	setAlpha((int)cm->getConst(func),ref);
}

void Material::setDepth(int func)
{
	p_depth=func;
}

void Material::setDepth(char* func)
{
	ClassManager *cm=core->classManager();
	setDepth((int)cm->getConst(func));
}

void Material::setDepthWrite(bool write)
{
	if (write!=((fflag&GL_DEPTHWRITE)!=0)) fflag^=GL_DEPTHWRITE;
}

void Material::setLight(bool val)
{
	if (val!=((fflag&GL_LIGHT)!=0)) fflag^=GL_LIGHT;
}

void Material::setLineWith(float val)
{
	flineWidth=val;
}

void Material::setPointSize(float val)
{
	fpointSize=val;
}

int Material::setTexture2D(Texture2D* texture,unsigned int id)
{
	Texture2D *valz=0;
	while (p_textures.count()<=id) p_textures.assign(valz);
	Texture2D *&val=p_textures[id];
	val=texture;
	return id;
}

int Material::setTexture2D(char* name,unsigned int id)
{
	Texture2D *text=Graph::graph().getTexture2D(name);
	if (!text) {
#ifdef LOG_CSAD
		Log::console("Can`t found texture2d: %s",name);
#endif
		return 0;
	}
	return setTexture2D(text,id);
}

Texture2D *Material::getTexture2D(unsigned int id)
{
	if (id>=p_textures.count()) return 0;
	Texture2D *&val=p_textures[id];
	return val;
}

void Material::setTextureRect(bt::vector4f &rect,unsigned int id)
{
	bt::matrix4f valz;
	valz.identity();
	while (ftexturesMatrix.Count<=id) arrFunctions.ANTAssign(&ftexturesMatrix,&valz);
	bt::matrix4f *val=(bt::matrix4f *)arrFunctions.ANTPosition(&ftexturesMatrix,id);
	valz.addTranslateSelf(rect.x,rect.y,0);
	valz.addScaleSelf(rect.z,rect.w,1);
	*val=valz;
}

void Material::setTextureMatrix(bt::matrix4f &matrix,unsigned int id)
{
	if (ftexturesMatrix.Count<=id) {
		bt::matrix4f valz;
		valz.identity();
		while (ftexturesMatrix.Count<=id) arrFunctions.ANTAssign(&ftexturesMatrix,&valz);
	}
	bt::matrix4f **val=(bt::matrix4f **)arrFunctions.ANTPosition(&ftexturesMatrix,id);
	**val=matrix;
}

bt::matrix4f *Material::getTextureMatrix(unsigned int id)
{
	if (id>=ftexturesMatrix.Count) return 0;
	bt::matrix4f **val=(bt::matrix4f **)arrFunctions.ANTPosition(&ftexturesMatrix,id);
	return *val;
}

const char *Material::getName()
{
	return Graph::graph().p_material->getName(this);
}

const char *Material::getPath()
{
	ObjectManager::path="material/";
	ObjectManager::path+=Graph::graph().p_material->getName(this);
	return ObjectManager::path.str();
}

void *Material::set(unsigned _int32 id,void * param)
{
	if (id==BaseObject::TYPE) return Material::t();
	if (id==BaseObject::WRITE) {
		Variant *p;
		Variant *p2;
		ParametersList &list=*(ParametersList *)param;
		if ((p=list.find(STR_COLOR))!=0) setDiffuse(p->getVector4f());
		if ((p=list.find(STR_DIFFUSE))!=0) setDiffuse(p->getVector4f());
		if ((p=list.find(STR_AMBIENT))!=0) setAmbient(p->getVector4f());
		if ((p=list.find(STR_SPECULAR))!=0) setSpecular(p->getVector4f());
		if ((p=list.find("emission"))!=0) setEmission(p->getVector4f());
		if (((p=list.find("src"))!=0) && ((p2=list.find("dst"))!=0)) setBlend(p->getString(),p2->getString());
		if (((p=list.find("alpha"))!=0) && ((p2=list.find("alpharef"))!=0)) setAlpha(p->getString(),p2->getFloat());
		if ((p=list.find(STR_DEPTH))!=0) setDepth(p->getString());
		if ((p=list.find("depthwrite"))!=0) setDepthWrite(p->getBool());
		if ((p=list.find(STR_LIGHT))!=0) setLight(p->getBool());
		if ((p=list.find("linewidth"))!=0) flineWidth=p->getFloat();
		if ((p=list.find("pointsize"))!=0) fpointSize=p->getFloat();
		if ((p=list.find(STR_TEXTURE))!=0) setTexture2D(p->getString());
		if ((p=list.find("rect"))!=0) setTextureRect(p->getVector4f());
		if ((p=list.find("texture1"))!=0) setTexture2D(p->getString(),1);
		if ((p=list.find("rect1"))!=0) setTextureRect(p->getVector4f(),1);
	}
	if (id==BaseObject::READ) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		p=&list[STR_DIFFUSE];
		p->setVector4f(&p_diffuse);
		p=&list[STR_AMBIENT];
		p->setVector4f(&p_ambient);
		p=&list[STR_SPECULAR];
		p->setVector4f(&p_specular);
		p=&list["emission"];
		p->setVector4f(&p_emission);
		if (p_textures.count()>0) {
			p=&list[STR_TEXTURE];
			p->setString((p_textures[0]->getName()));
		}
		if (ftexturesMatrix.Count>0) {
			bt::matrix4f *m=(bt::matrix4f *)arrFunctions.ANTPosition(&ftexturesMatrix,0);
			bt::vector3f *tr=(bt::vector3f *)&m->m[12];
			bt::matrix4f ms;
			bt::vector3f scale;
			bt::quaternionf rot;
			extFunctions.MoveMem(m,&ms,sizeof(bt::matrix4f));
			scale.x=matFunctions.FSqrt(vecFunctions.V3FLength2(&ms));
			scale.y=matFunctions.FSqrt(vecFunctions.V3FLength2(&ms[4]));
			scale.z=matFunctions.FSqrt(vecFunctions.V3FLength2(&ms[8]));
			vecFunctions.V3FScale(&ms,&ms,1/scale.x);
			vecFunctions.V3FScale(&ms[4],&ms[4],1/scale.y);
			vecFunctions.V3FScale(&ms[8],&ms[8],1/scale.z);
			vecFunctions.M4FQuaternion(&ms,&rot);

			if (tr->z==0.0f && scale.z==1.0f) {
				bt::vector4f rect(tr->x,tr->y,scale.x,scale.y);
				p=&list["rect"];
				p->setVector4f(&rect);
			} else {
				p=&list[STR_TRANSLATE];
				p->setVector3f(tr);
				p=&list[STR_SCALE];
				p->setVector3f(&scale);
				p=&list["rotate"];
				p->setVector4f((bt::vector4f *)&rot);
			}

			/*if (m->m[1]==0.0f && m->m[2]==0.0f && m->m[3]==0.0f 
				&& m->m[4]==0.0f && m->m[6]==0.0f && m->m[7]==0.0f 
				&& m->m[8]==0.0f && m->m[9]==0.0f && m->m[10]==1.0f && m->m[11]==0.0f
				&& m->m[14]==0.0f && m->m[15]==1.0f) {
				p=&list["rect"];
				p->setString("");
			} else {
				p=&list["matrix"];
				p->setString("???");
			}*/
			//p->setVector4f((p_textures[0]->getName()));
		}
		//if (list.contains("rect1")) setTextureRect(list["rect1"].getVector4f(),1);
	}
	return 0;
}

Material *Material::finder(char *path)
{
	return (Material *)Graph::graph().p_material->getObject(path);
}

TYPEINFO(Material)

}

OPTIMIZE_OFF;