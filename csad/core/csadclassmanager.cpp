/*
 * classmanager.cpp
 *
 *  Created on: 27.08.2013
 *      Author: Александр
 */

#include "csadclassmanager.h"
#include <bt.h>
#include <platform.h>
#include <scene/material.h>

OPTIMIZE_ON;

namespace csad {

BaseObjectsName::~BaseObjectsName()
{
	MapVoid<void>::iterator it=MapVoid<void>::begin();
	MapVoid<void>::iterator end=MapVoid<void>::end();
	while (it!=end) {
		void *val=it.value();
		if (val) *((ShortString*)&val)="";
		it++;
	}
}

CsadClassManager::CsadClassManager()
{
	addConst("NONE",-1);
	addConst("ZERO",Material::ZERO);
	addConst("ONE",Material::ONE);
	addConst("SRC_COLOR",Material::SRC_COLOR);
	addConst("ONE_MINUS_SRC_COLOR",Material::ONE_MINUS_SRC_COLOR);
	addConst("SRC_ALPHA",Material::SRC_ALPHA);
	addConst("ONE_MINUS_SRC_ALPHA",Material::ONE_MINUS_SRC_ALPHA);
	addConst("DST_ALPHA",Material::DST_ALPHA);
	addConst("NEVER",Material::NEVER);
	addConst("LESS",Material::LESS);
	addConst("EQUAL",Material::EQUAL);
	addConst("LEQUAL",Material::LEQUAL);
	addConst("GREATER",Material::GREATER);
	addConst("NOTEQUAL",Material::NOTEQUAL);
	addConst("GEQUAL",Material::GEQUAL);
	addConst("ALWAYS",Material::ALWAYS);
}

CsadClassManager::~CsadClassManager()
{
	BaseObjectsList::iterator cit=p_classInfo.begin();
	BaseObjectsList::iterator cend=p_classInfo.end();
	while (cit!=cend) {
		delete cit.value();
		cit++;
	}
}

ObjectInfo* CsadClassManager::regClass(char * className,void * type,tfSTDCALL_p_FUNC_p creator)
{
	ObjectInfo *info=p_classInfo.find(className);
	if (!info) info=new ObjectInfo();
	info->fun=creator;
	info->type=type;
	info->flag=0;
	p_classInfo[className]=info;
	p_className[type]=className;
	return p_classInfo[className];
}

BaseObject* CsadClassManager::createObject(char *className,ParametersList *list)
{
	ObjectInfo *classInfo=p_classInfo.find(className);
	if (!classInfo) return 0;
	tfSTDCALL_p_FUNC_p create=classInfo->fun;
	if (!create) return 0;
	BaseObject* object=(BaseObject*)create((void*)list);

	return object;
}

const char *CsadClassManager::className(void * type)
{
	void *data=p_className.find(type);
	if (!data) return 0;
	ShortString *s=(ShortString *)&data;
	return s->str();
}

BaseObjectsList * CsadClassManager::ObjectInfoList()
{
	return &p_classInfo;
}

ObjectInfo *CsadClassManager::classInfoType(void * type)
{
	void *data=p_className.find(type);
	if (!data) return 0;
	ShortString *s=(ShortString *)&data;
	ObjectInfo *classInfo=p_classInfo.find((char*)s->str());
	if (!classInfo) return 0;
	return classInfo;
}

ObjectInfo *CsadClassManager::classInfo(char * className)
{
	ObjectInfo *classInfo=p_classInfo.find(className);
	if (!classInfo) return 0;
	return classInfo;
}

void CsadClassManager::addConst(const char*name,int c)
{
	p_constName[name]=(void*)(_voidint)c;
}

int CsadClassManager::getConst(char*name)
{
	return (int)(_voidint)p_constName[name];
}

/*BaseObjectsList *CsadClassManager::ObjectInfoList()
{
	return &p_classInfo;
}*/

bool CsadClassManager::isRegistered(char * name)
{
	return p_classInfo.contains(name);
}

}

OPTIMIZE_OFF;
