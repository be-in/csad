/*
 * manager.cpp
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <core/objectmanager.h>
#include "csadcore.h"

namespace csad {

OPTIMIZE_ON;

String ObjectManager::path;

ObjectManager::ObjectManager(char *name)
{
	if ((name==0) || (name[0]!=0)) {
		if (core->manager()!=this) core->manager()->addObject(this,name);
	}
	p_genObjectName=0;
}

ObjectManager::ObjectManager(const char *name)
{
	if ((name==0) || (name[0]!=0)) {
		if (core->manager()!=this) core->manager()->addObject(this,name);
	}
	p_genObjectName=0;
}

ObjectManager::~ObjectManager()
{
	if (core->manager()!=this)
		core->manager()->detachObject(this);
}

bool ObjectManager::addObject(void * obj,char *name)
{
	if ((name==0) || (name[0]==0)) {
		p_genObjectName++;
		if (p_genObjectName==0xFFFFFFFF) p_genObjectName++;
		name = numName(p_genObjectName);
	}
	if (arrFunctions.MSSPFind(&p_objects,name)==0) {
		//void *&p=((BaseMapName *)&p_objects)->_findornew(name);
		void *&p = p_objects[name];
		p=obj;
		return true;
	}
	return false;
}

void* ObjectManager::getObject(char *name)
{
	void** val=static_cast<void**>(arrFunctions.MSSPFind(&p_objects,name));
	if (val) val=static_cast<void**>(*val);
	return (void*)(val);
}

void* ObjectManager::getObject(const char *name)
{
	void** val=static_cast<void**>(arrFunctions.MSSPFind(&p_objects,(void*)name));
	if (val) val=static_cast<void**>(*val);
	return (void*)(val);
}

bool ObjectManager::removeObject(char *name)
{
	if (p_genObjectName==0xFFFFFFFF) return false;
	return arrFunctions.MSSPRemove(&p_objects,(void*)name)!=0;
}

bool ObjectManager::removeObject(const char *name)
{
	if (p_genObjectName==0xFFFFFFFF) return false;
	return arrFunctions.MSSPRemove(&p_objects,(void*)name)!=0;
}

bool ObjectManager::detachObject(void* obj)
{
	if (p_genObjectName==0xFFFFFFFF) return false;
	const char *key="";
	key=p_objects.key(obj,key);
	return arrFunctions.MSSPRemove(&p_objects,(void*)key)!=0;
}

const char* ObjectManager::getName(void* obj)
{
	const char *key="";
	key=p_objects.key(obj,key);
	return key;
}

void *ObjectManager::set(unsigned _int32 id,void *param)
{
	if (id==BaseObject::TYPE) return ObjectManager::t();
	if (id==BaseObject::MANAGER) {
		void** val=static_cast<void**>(arrFunctions.MSSPFind(&p_objects,param));
		if (val) val=static_cast<void**>(*val);
		return val;
	}
	if (id==BaseObject::MANAGER_COUNT) {
		return (void *)(_voidint)arrFunctions.MPCount(&p_objects);
	}
	if (id==BaseObject::NAME) {
		BaseObject *parent=(BaseObject *)param;
		if (parent) return parent->set(BaseObject::CHILD_NAME,this);
	}
	if (id==BaseObject::READ) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		p=&list["count"];
		p->setInt(arrFunctions.MPCount(&p_objects));
		return param;
	}
	return 0;
}

ObjectManager &ObjectManager::manager()
{
	return *core->manager();
}

void ObjectManager::regFinderObject(void *type,tfSTDCALL_p_FUNC_p func)
{
	if (core->finder()->contains(type)) return;
	(*core->finder())[type]=(void*)func;
}

void *ObjectManager::findObject(char *path)
{
	Finder find(path); 
	BaseObject *obj;

	obj=(BaseObject*)&manager();
	while ((obj!=0) && (find.getNext())) {
		obj=(BaseObject*)obj->set(BaseObject::MANAGER,find.next());
		find.next();
	}
	return obj;
}

void *ObjectManager::findObject(void *type,char *path)
{
	tfSTDCALL_p_FUNC_p func=(tfSTDCALL_p_FUNC_p)core->finder()->find(type);
	if (!func) return 0;
	return func(path);
}

void *ObjectManager::findObject(void *,const char *)
{
	return 0;//findObject(type,path);
}

ObjectManager::Finder::Finder(char *path)
{
	char *c=path;
	while (*c!=0) c++;
	int size=(int)((_voidint)c-(_voidint)path+1);
	p_path=(char*)extFunctions.CreateMem(size,0);
	extFunctions.MoveMem(path,p_path,size);
	p_prevnext=p_path;
	p_next=(char*)extFunctions.STRLeftFind((void*)p_path,(void*)"/");
	if (p_next) {
		*p_next=0;
		p_next++;
	}
}

ObjectManager::Finder::~Finder()
{
	if (p_path) extFunctions.DeleteMem(p_path,0);
	p_path=0;
}

char *ObjectManager::Finder::next()
{
	char* ret=p_prevnext;
	p_prevnext=p_next;
	if (p_next) {
		p_next=(char*)extFunctions.STRLeftFind((void*)ret,(void*)"/");
		if (p_next) {
			*p_next=0;
			p_next++;
		}
	}
	return ret;
}

TYPEINFO(ObjectManager)

OPTIMIZE_OFF;

}
