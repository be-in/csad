/*
 * core.cpp
 *
 *  Created on: 30.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include "csadcore.h"
#include "config.h"
#include "csadclassmanager.h"
#include "base/baseapi.h"
#include <format/formatxml.h>

OPTIMIZE_ON;

namespace csad {

Core* core=0;

csad::Core* _APICALL CoreCreaete()
{
	csad::initCore();
	return new csad::LocalCore();
}

csad::Core* _APICALL csadCore()
{
	return csad::core;
}

void _APICALL SetCore(csad::Core* core)
{
	csad::core=core;
}

LocalCore::LocalCore()
{
	core=this; // mast be first
	p_flag=0;

	p_manager = new ObjectManager();
	p_classManager = new CsadClassManager();
	p_system = new System();
	p_input = new Input();
	p_graph = new Graph();
	//p_finder
}

LocalCore::~LocalCore()
{
	//p_manager->clean();
	freeComponents();
	delete p_graph;
	p_graph=0;
	delete p_input;
	p_input=0;
	delete p_system;
	p_system=0;
	delete p_classManager;
	p_classManager=0;
	delete p_manager;
	p_manager=0;

	if (core==this) core=0;
}

void LocalCore::init()
{
	p_graph->init();
	p_input->init();
}

void LocalCore::start()
{
	p_flag|=LOCK_UPDATE;
	while (p_startC.count()>0) {
		ContainerList startC;
		startC.absorb(p_startC);
		ContainerList::iterator cit=startC.begin();
		ContainerList::iterator citend=startC.end();
		while (cit!=citend)
		{
			ContainerComponents *container=(ContainerComponents *)cit.value();
			container->start();
			cit++;
		}
		startC.clear();
	}
	p_flag^=LOCK_UPDATE;

	while (p_start.count()>0) {
		ComponentsList start;
		start.absorb(p_start);
		ComponentsList::iterator it=start.begin();
		ComponentsList::iterator itend=start.end();
		while (it!=itend)
		{
			Component *component=(Component *)it.value();
			component->start();
			it++;
		}
		start.clear();
	}
}

void LocalCore::quit()
{
	p_graph->quit();
	p_input->close();
	ContainerComponents::quit();
}

bool LocalCore::loadCore(char* name)
{
	Config config(this);
	csad::FormatXML * xml=new FormatXML();
	if (xml->readFromFile(name)) {
		config.createFromXml(xml);
	} else {
#ifdef LOG_CSAD
		csad::Log::console("not found configuration file config.xml");
#endif
	}
	delete xml;

	return true;
}

void *LocalCore::set(unsigned _int32 id,void *param)
{
	if (id==BaseObject::TYPE) return Core::t();
	if (id==BaseObject::CONTAINER) return this;
	if (id==BaseObject::MANAGER) return p_manager->getObjects().valueAt((_int32)(_voidint)param);
	if (id==BaseObject::MANAGER_COUNT) return (void*)(_voidint)p_manager->getObjects().count();
	//if ((id==BaseObject::MANAGER) || (id==BaseObject::MANAGER_COUNT)) return p_manager->set(id,param);
	if (id==BaseObject::NAME) return (void*)"core";
	if (id==BaseObject::CHILD_NAME) return (void*)p_manager->getName(param);
	if (id==BaseObject::WRITE) {
		ParametersList &list=*(ParametersList *)param;
		if (list.contains("cpuflag")) {
			btFunctions.ResetFunc();
			btFunctions.InitFunc(list["cpuflag"].getInt());
		}
	}
	if (id==BaseObject::READ) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		p=&list["count"];
		p->setInt(p_manager->getObjects().count());
		p=&list["cpuflag"];
		p->setInt(btFunctions.FlagCPU());
		return param;
	}
/*	if (id==BaseObject::RUN) {
		unsigned int id=*(unsigned int*)param;
		if (id==Core::FunctionsLoad) {
			Functions::init();
			Core::pLoadFunc *fp=(Core::pLoadFunc *)param;
			//Functions::init()(fp->funcArr);
		}
	}*/
	return 0;
}

TYPEINFO(LocalCore)

}

OPTIMIZE_OFF;
