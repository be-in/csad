/*
 * componentconteiner.cpp
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <core/containercomponents.h>
#include "csadcore.h"
#include <core/component.h>

OPTIMIZE_ON;

/*class OpenContainerComponents: public csad::ContainerComponents {
public:
	_FORCEINLINE void *& list() {return p_list;}
};*/

class OpenComponent: public csad::Component {
public:
	MEMNULL
	_FORCEINLINE void *& parent() {return (void*&)p_parent;}
};

void* newContainerComponentByName(void* container,char * name)
{
	csad::ObjectInfo *tpi=csad::core->classManager()->classInfo(name);
	if (!tpi) return 0;
	OpenComponent **component=(OpenComponent **)arrFunctions.MPAdd(&((csad::ContainerComponents*)container)->list(),tpi->type,0);
	if (*component) return *component;
	bt::tfSTDCALL_p_FUNC_p fun=tpi->fun;
	*component = (OpenComponent*)fun(container); // when return is null - you forgot define MEMDEFAULT(classname)
	(*component)->parent()=container;
	return *component;
}

void* newContainerComponentByInfo(void* container,void *info)
{
	OpenComponent **component=(OpenComponent **)arrFunctions.MPAdd(&((csad::ContainerComponents*)container)->list(),info,0);
	if (*component) return *component;
	csad::ClassManager * classmanager=csad::core->classManager();
	const char *name=classmanager->className(info);
	csad::ObjectInfo *tpi=classmanager->classInfo(name);
	if (!tpi) return 0;
	bt::tfSTDCALL_p_FUNC_p fun=tpi->fun;
	*component = (OpenComponent*)fun(container);
	(*component)->parent()=container;
	return *component;
}

void setContainerComponentParent(void* container,void *component)
{
	OpenComponent *lcomponent=(OpenComponent *)component;
	lcomponent->parent()=container;
}

void **addContainerComponentByInfo(void* container,void *component,void *info)
{
	OpenComponent **lcomponent=(OpenComponent **)arrFunctions.MPAdd(&((csad::ContainerComponents*)container)->list(),info,component);
	if (*lcomponent) (*lcomponent)->parent()=container;
	return (void**)lcomponent;
}

void* getContainerComponent(void* container,char * name)
{
	csad::ClassManager * classmanager=csad::core->classManager();
	if (!classmanager->classInfo(name)) return 0;
	csad::ObjectInfo *tpi=classmanager->classInfo(name);
	if (!tpi) return 0;
	void ** component=(void **)arrFunctions.MPFind(&((csad::ContainerComponents*)container)->list(),tpi->type);
	if (component) return *component;
	return 0;
}

namespace csad {

//void constructInit();

//int p_isConstructVal;

//ConstructorList *p_construct;

ContainerComponents::ContainerComponents()
	:p_list(0)
{
	if ((core!=this) && (core!=0))
		((LocalCore*)core)->p_startC.assign(this);
}

/*ContainerComponents::~ContainerComponents()
{
	if ((core!=this) && (core!=0))
		((LocalCore*)core)->p_startC.del(this);
	freeComponents();
}*/

void ContainerComponents::start()
{
	/*BaseMapVoid::iterator it=p_list.begin();
	BaseMapVoid::iterator itend=p_list.end();
	while (it!=itend)
	{
		Component *component=(Component *)it.value();
		component->start();
		it++;
	}*/
	if ((((LocalCore*)core)->getFlag() &LocalCore::LOCK_UPDATE)==0) {
		void **it=(void **)arrFunctions.MPArray(&p_list);
		void **end = it;
		end += arrFunctions.MPCount(&p_list) << 1;
		it++;
		while (it<end) {
			Component *component=(Component *)*it;
			component->start();
			it += 2;
		}
	}
}

//Component c;

void ContainerComponents::update()
{
	//bt::tfFASTCALL_PROC **vtp=(bt::tfFASTCALL_PROC**)&c;
	//bt::tfFASTCALL_PROC **vtpc;
	void **it=(void **)arrFunctions.MPArray(&p_list);
	void **end=it;
	end+=arrFunctions.MPCount(&p_list)<<1;
	it++;
	while (it<end) {
		Component *component=(Component *)*it;
		//vtpc=(bt::tfFASTCALL_PROC**)component;
		//if ((*vtpc)[4]!=(*vtp)[4])
		component->update();
		it+=2;
	}
}

void ContainerComponents::quit()
{
	void **it=(void **)arrFunctions.MPArray(&p_list);
	void **end = it;
	end += arrFunctions.MPCount(&p_list) << 1;
	it++;
	while (it<end) {
		Component *component=(Component *)*it;
		component->quit();
		it+=2;
	}
}

void *ContainerComponents::setComponents(unsigned int id,void* param)
{
	void **it=(void **)arrFunctions.MPArray(&p_list);
	void **end = it;
	end += arrFunctions.MPCount(&p_list) << 1;
	it++;
	while (it < end) {
		Component *component=(Component *)*it;
		component->set(id,param);
		it += 2;
	}
	return 0;
}

int ContainerComponents::regClass(const char *name,const void *info,tfSTDCALL_p_FUNC_p fun) {
	ObjectInfo *obj=core->classManager()->regClass(name,info,fun);
	obj->flag=ObjectInfo::CONTAINER;
	return 0;
}

/*Component *ContainerComponents::addComponent(char * name)
{
	ObjectInfo *tpi=core->classManager()->classInfo(name);
	if (!tpi) return 0;
	Component **component=(Component **)arrFunctions.MPAdd(&p_list,tpi->type,0);
	if (*component) return *component;
	tfSTDCALL_p_FUNC_p fun=tpi->fun;
	*component = (Component*)fun(this);
	(*component)->p_parent=this;
	return *component;
}*/

/*Component *ContainerComponents::addComponent(const char * name)
{
	if (!p_construct->contains(name)) return 0;
	ObjectInfo *tpi=(*p_construct)[name];
	Component * component=(Component *)p_list._find(tpi->type);
	if (component) return component;
	tfSTDCALL_p_FUNC_p fun=tpi->fun;
	component = (Component*)fun(this);
	void *val=(void*)component;
	void *&p=p_list._findornew(tpi->type);
	p=val;
	component->p_parent=this;
	return component;
}*/

/*Component *ContainerComponents::getComponent(char * name)
{
	if (!core->classManager()->classInfo(name)) return 0;
	ObjectInfo *tpi=core->classManager()->classInfo(name);
	if (!tpi) return 0;
	Component ** component=(Component **)arrFunctions.MPFind(&p_list,tpi->type);
	if (component) return *component;
	return 0;
}*/

/*Component *ContainerComponents::getComponent(const char * name)
{
	if (!p_construct->contains(name)) return 0;
	ObjectInfo *tpi=(*p_construct)[name];
	Component * component=(Component *)p_list.find(tpi->type);
	if (component) return component;
	return 0;
}*/

/*void ContainerComponents::freeComponents()
{
	void **it=(void **)arrFunctions.MPArray(&p_list);
	unsigned int count=arrFunctions.MPCount(&p_list);
	while (count>0) {
		it++;
		Component *component=(Component *)*it;
		component->p_parent=0;
		delete component;
		it++;
		count--;
	}
	arrFunctions.MPFree(&p_list);
	p_list=0;
}*/

bool ContainerComponents::isRegistered(char * name)
{
	return core->classManager()->isRegistered(name);
}

ObjectInfo *ContainerComponents::getInfo(char * name)
{
	return csadCore()->classManager()->classInfo(name);
}

const char *ContainerComponents::getPath()
{
	return 0;
}

void *ContainerComponents::set(unsigned _int32 id,void *)
{
	if (id==BaseObject::CONTAINER) return this;
	return 0;
}

/*Component* *ContainerComponents::addComponent(Component *component,void *info)
{
	OpenComponent **lcomponent=(OpenComponent **)arrFunctions.MPAdd(&p_list,info,component);
	if (*lcomponent) (*lcomponent)->parent()=this;
	return (Component* *)lcomponent;
}*/

/*Component* ContainerComponents::addComponent(void *info)
{
	OpenComponent **component=(OpenComponent **)arrFunctions.MPAdd(&p_list,info,0);
	if (*component) return *component;
	const char *name=core->classManager()->className(info);
	ObjectInfo *tpi=core->classManager()->classInfo(name);
	if (!tpi) return 0;
	tfSTDCALL_p_FUNC_p fun=tpi->fun;
	*component = (OpenComponent*)fun(this);
	(*component)->parent()=this;
	return (Component*)*component;
}*/

void ContainerComponents::removeComponent(void *info)
{
	OpenComponent *component = (OpenComponent *)arrFunctions.MPRemove(&p_list,info);//arrFunctions.MPFind(&p_list,info);
	if (component) {
		component->parent()=0;
	}
}

void ContainerComponents::deleteComponent(void *info)
{
	OpenComponent *component = (OpenComponent *)arrFunctions.MPRemove(&p_list,info);//arrFunctions.MPFind(&p_list,info);
	if (component) {
		component->parent()=0;
		delete component;
	}
}

}

OPTIMIZE_OFF;
