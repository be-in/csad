/*
 * sgstyles.cpp
 *
 *  Created on: 16.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/gui/sgstyles.h>
#include <scene/material.h>
#include <core/graph.h>

OPTIMIZE_ON;

namespace csad {

SGStyle::SGStyle()
{
	for (int i=0;i<2;i++) {
		materialKey[i]=0;
	}

	for (int i=0;i<4;i++) {
		materialText[i]=0;
	}
	for (int i=0;i<8;i++) {
		materialBack[i]=0;
	}
}

void SGStyle::setMaterialBack(char * name,int state)
{
	Material*mat=Graph::graph().getMaterial(name);
#ifdef LOG_CSAD
	if (!mat) Log::console("Can`t find material: %s",name);
#endif
	setMaterialBack(mat,state);
}

void SGStyle::setMaterialBack(Material * mat,int state)
{
	if (state>7) return;
	materialBack[state]=mat;
	if (state==0 && !materialBack[1]) materialBack[1]=mat;
	if (state==0 && !materialBack[2]) materialBack[2]=mat;
	if (state==0 && !materialBack[3]) materialBack[3]=mat;
	if (state==0 && !materialBack[4]) materialBack[4]=mat;
	if ((state==0 || state==4) && !materialBack[5]) materialBack[5]=mat;
	if ((state==0 || state==4) && !materialBack[6]) materialBack[6]=mat;
	if ((state==0 || state==4) && !materialBack[7]) materialBack[7]=mat;
}

Material *SGStyle::getMaterialBack(int state)
{
	if (state>7) return 0;
	return materialBack[state];
}

void SGStyle::setMaterialText(char * name,int state)
{
	Material*mat=Graph::graph().getMaterial(name);
#ifdef LOG_CSAD
	if (!mat) Log::console("Can`t find material: %s",name);
#endif
	setMaterialText(mat,state);
}

void SGStyle::setMaterialText(Material * mat,int state)
{
	if (state>3) return;
	materialText[state]=mat;
	if (state==0 && !materialText[1]) materialText[1]=mat;
	if (state==0 && !materialText[2]) materialText[2]=mat;
	if (state==0 && !materialText[3]) materialText[3]=mat;
}

Material *SGStyle::getMaterialText(int state)
{
	if (state>3) return 0;
	return materialText[state];
}

void SGStyle::setMaterialKey(char * name,int state)
{
	Material*mat=Graph::graph().getMaterial(name);
#ifdef LOG_CSAD
	if (!mat) Log::console("Can`t find material: %s",name);
#endif
	setMaterialKey(mat,state);
}

void SGStyle::setMaterialKey(Material * mat,int state)
{
	if (state>1) return;
	materialKey[state]=mat;
	if (state==0 && !materialKey[1]) materialKey[1]=mat;
}

Material *SGStyle::getMaterialKey(int state)
{
	if (state>1) return 0;
	return materialKey[state];
}

void * SGStyle::set(unsigned _int32 id,void * param)
{
	if (id==BaseObject::TYPE) return SGStyle::t();
	if (id==BaseObject::WRITE) {
		Variant *p;
		ParametersList *list=(ParametersList *)param;
		if ((p=list->find("normal"))!=0) setMaterialBack(p->getString(),0);
		if ((p=list->find("active"))!=0) setMaterialBack(p->getString(),1);
		if ((p=list->find("click"))!=0) setMaterialBack(p->getString(),2);
		if ((p=list->find("disable"))!=0) setMaterialBack(p->getString(),3);
		if ((p=list->find("set_normal"))!=0) setMaterialBack(p->getString(),4);
		if ((p=list->find("set_active"))!=0) setMaterialBack(p->getString(),5);
		if ((p=list->find("set_click"))!=0) setMaterialBack(p->getString(),6);
		if ((p=list->find("set_disable"))!=0) setMaterialBack(p->getString(),7);
		if ((p=list->find("normal_text"))!=0) setMaterialText(p->getString(),0);
		if ((p=list->find("active_text"))!=0) setMaterialText(p->getString(),1);
		if ((p=list->find("click_text"))!=0) setMaterialText(p->getString(),2);
		if ((p=list->find("disable_text"))!=0) setMaterialText(p->getString(),3);
		if ((p=list->find("normal_key"))!=0) setMaterialKey(p->getString(),0);
		if ((p=list->find("set_key"))!=0) setMaterialKey(p->getString(),1);
	}
	if (id==BaseObject::READ) {
		Variant *p;
		ParametersList *list=(ParametersList *)param;
		p=&(*list)["normal"]; if (materialBack[0]) p->setString(materialBack[0]->getName());
		p=&(*list)["active"]; if (materialBack[1]) p->setString(materialBack[1]->getName());
		p=&(*list)["click"]; if (materialBack[2]) p->setString(materialBack[2]->getName());
		p=&(*list)["disable"]; if (materialBack[3]) p->setString(materialBack[3]->getName());
		p=&(*list)["set_normal"]; if (materialBack[4]) p->setString(materialBack[4]->getName());
		p=&(*list)["set_active"]; if (materialBack[5]) p->setString(materialBack[5]->getName());
		p=&(*list)["set_click"]; if (materialBack[6]) p->setString(materialBack[6]->getName());
		p=&(*list)["set_disable"]; if (materialBack[7]) p->setString(materialBack[7]->getName());
		return param;
	}
	return 0;
}

void * SGButtonStyle::set(unsigned _int32 id,void * param)
{
	if (id==BaseObject::TYPE) return SGButtonStyle::t();
	return SGStyle::set(id,param);
}

void * SGElementStyle::set(unsigned _int32 id,void * param)
{
	if (id==BaseObject::TYPE) return SGElementStyle::t();
	if (id==BaseObject::WRITE) SGStyle::set(id,param);
	return SGStyle::set(id,param);
}

void * SGLineEditStyle::set(unsigned _int32 id,void * param)
{
	if (id==BaseObject::TYPE) return SGLineEditStyle::t();
	if (id==BaseObject::WRITE) SGStyle::set(id,param);
	return SGStyle::set(id,param);
}

TYPEINFO(SGStyle)
TYPEINFO(SGButtonStyle)
TYPEINFO(SGElementStyle)
TYPEINFO(SGLineEditStyle)

}

OPTIMIZE_OFF;
