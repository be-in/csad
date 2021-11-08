/*
 * core.h
 *
 *  Created on: 13.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef CORE_H_
#define CORE_H_

#include <bt.h>
#include <core/input.h>
#include <core/graph.h>
#include <core/system.h>
#include <platform/timer.h>
#include <core/containercomponents.h>
#include <core/corefunctions.h>
#include <core/component.h>
#include <core/classmanager.h>
#include <core/objectmanager.h>
#include <scene/scene.h>

namespace csad {

WARNING_DISABLE;

/// Registers the class as the baseobject of the object.
#ifndef CSAD_EXPORTS
#define REG_OBJECT(classname) \
	csad::BaseObject * _STDCALL creator_##classname (void *) {return (csad::BaseObject *)new classname();} \
	int reg_##classname=csadCore()->classManager()->regClass(#classname,classname::t(),(bt::tfSTDCALL_p_FUNC_p)&creator_##classname);
#else
#define OBJECT_CLASS(classname) \
	csad::BaseObject * _STDCALL creator_##classname (void *) {return (csad::BaseObject *)new classname();}
#define INIT_OBJECT(classname) \
	csadCore()->classManager()->regClass(#classname,classname::t(),(bt::tfSTDCALL_p_FUNC_p)&creator_##classname);
#define REG_OBJECT(classname)	
#endif

/**
 * @class Core
 *
 * @ingroup core
 * @brief Core - the Manager interface of the application.
 *
 * @see core
 */

class Core:public ContainerComponents {
public:
	MEMNULL

	/// the root object Manager
	_FORCEINLINE ObjectManager *manager() {return p_manager;}
	/// the Manager of system objects
	_FORCEINLINE System *system() {return p_system;}
	/// timer
	_FORCEINLINE Timer &timer() {return p_system->getTimer();}
	/// Manager graphical elements
	_FORCEINLINE Graph *graph() {return p_graph;}
	/// The Manager of the input systems
	_FORCEINLINE Input *input() {return p_input;}
	/// Manager classes
	_FORCEINLINE ClassManager *classManager() {return p_classManager;}
	///
	_FORCEINLINE ObjectsFinder *finder() {return &p_finder;}

	virtual bool loadCore(char* name)=0;

	virtual void init()=0;
	virtual void start()=0;
	virtual void quit()=0;

	/// creates the environment
	static _FORCEINLINE Core *Create() { return (Core *)coreFunctions.CoreCreaete(); }

	/// returns the current environment
	static _FORCEINLINE Core &current() { return *(Core *)coreFunctions.Core(); }
	/// sets the active environment
	static _FORCEINLINE void set(Core *core) { coreFunctions.SetCore(core); }

protected:

	ObjectManager * p_manager;
	System *p_system;
	Graph *p_graph;
	Input *p_input;
	ClassManager *p_classManager;
	ObjectsFinder p_finder;
/*	Scene * p_scene;   ???
	Camera * p_camera;*/
};

WARNING_ENABLE;

}

#endif /* CORE_H_ */
