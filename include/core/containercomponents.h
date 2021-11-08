/*
 * @file containercomponents.h
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef CONTAINERCOMPONENTS_H_
#define CONTAINERCOMPONENTS_H_

/**
 * @page page1 Компонентная архитектура объектов
 *
 * В отличии от модели компонентных объектов COM данная архитектура не подразумевает глобальное использование объектов в операционной системе.
 * А предоставляет основу для инструментов позволяющих конструировать объекты из имеющихся компонентов и дополнять их функционал.
 * Основой данной архитектуры является базовый объект среды в которой она применяется.
 * Базовый объект среды это контейнер компонентов, который агрегирует в себе их свойства и обеспечивает коммутацию между ними, являесь их менеджером.
 *
 * Каждый контейнер обеспечивает доступ к своим компонентам благодаря уникальной ассоциации между классом компонента и объектом данного класса.
 * Таким образом каждый контейнер может содержать только один объект своего класса.
 *
 * Для соотнашения нескольких объектов одному классу для контейнера необходимо использовать функции для работы со смешанным ассоциативным списком.
 * Это приводит к дополнительным расходам и не подходит для быстрого получения доступа к компонентам.
 * 
 */

#include <core/csadapi.h>
#include <core/baseobject.h>
#include <core/classmanager.h>
#include <bt.h>
#include <core/corefunctions.h>

WARNING_DISABLE;
OPTIMIZE_ON;

extern "C" {

CSAD_API void* newContainerComponentByName(void* container,char * name); // ненужно так делать смотри Transform (?)
CSAD_API void* newContainerComponentByInfo(void* container,void * info);
CSAD_API void setContainerComponentParent(void* container,void *component);
CSAD_API void **addContainerComponentByInfo(void* container,void *component,void * info);
CSAD_API void* getContainerComponent(void* container,char * name);

}

namespace csad {

using namespace bt;

/// Registers the class as the container of the object.
#ifndef CSAD_EXPORTS
#define REG_CONTAINER(classname) \
	csad::Component * _STDCALL creator_##classname (void *) {return (csad::Component *)new classname();} \
	int reg_##classname=csad::Component::regClass(#classname,classname::t(),(bt::tfSTDCALL_p_FUNC_p)&creator_##classname);
#else
#define CONTAINER_CLASS(classname) \
	csad::ContainerComponents * _STDCALL creator_##classname (void *) {return (csad::ContainerComponents *)new classname();}
#define INIT_CONTAINER(classname) \
	csad::ContainerComponents::regClass(#classname,classname::t(),(bt::tfSTDCALL_p_FUNC_p)&creator_##classname);
#define REG_CONTAINER(classname)	
#endif

class Component;

typedef MapVoid<Component> ComponentsMap;
typedef MapName<ObjectInfo> ConstructorList;

/**
 * @class ContainerComponents
 *
 * @ingroup core
 * @brief ContainerComponents - the container class components.
 *
 * The container has a map of pointers to objects components.
 *
 * @see core
 */

class ContainerComponents: public BaseObject {
public:
	MEMNULL

	CSAD_API ContainerComponents();
	//CSAD_API virtual ~ContainerComponents();
	_FORCEINLINE ~ContainerComponents() {coreFunctions.ContainerDestructor(this);}

	/// Adds the component of the specified type in the container if this component already exists, returns available.
	template <typename T>
	_FORCEINLINE T* addComponent() {
		void * tp=T::t();
		Component **c=(Component **)arrFunctions.MPAdd(&p_list,tp,0);
		if (!*c) {
			*c = new T();
			setContainerComponentParent(this, *c);
		}
		return static_cast<T*>(*c);
	}

	/// Returns the component of the given type, if it is not in a container returns 0.
	template <typename T>
	_FORCEINLINE T* getComponent() {
		void **c = (void **)arrFunctions.MPFind(&p_list, T::t());
		if (c) c = (void **)*c;
		return static_cast<T*>((Component *)c);
	}

	/// Returns the component of the given type, if it is not in a container returns 0.
	_FORCEINLINE Component* getComponent(void * t) {
		void **c = (void **)arrFunctions.MPFind(&p_list, t);
		if (c) c = (void **)*c;
		return static_cast<Component*>((void *)c);
	}

	/// Detaches the component from a container
	template <typename T>
	_FORCEINLINE void removeComponent() {
		removeComponent(T::t());
	}

	/// Detaches the component from the container and remove the component.
	template <typename T>
	_FORCEINLINE void deleteComponent() {
		deleteComponent(T::t());
	}

	class iterator {
	public:
		_FORCEINLINE iterator(void*it):miterator((void**)it) {}
		_FORCEINLINE ~iterator() {}

		/// the component type
		_FORCEINLINE void *type() {return *(void**)miterator;}
		
		/// component
		_FORCEINLINE Component *component() {return *((Component**)miterator+1);}

		_FORCEINLINE iterator &operator ++(int) {
			miterator+=2;
			return (*this);
		}

		_FORCEINLINE bool operator ==(const iterator& _Right) {
			return miterator==_Right.miterator;
		}

		_FORCEINLINE bool operator !=(const iterator& _Right) {
			return miterator!=_Right.miterator;
		}
	private:
		void **miterator;
	};

	/// The first element of the list of components
	_FORCEINLINE iterator begin() { return iterator(arrFunctions.MPArray(&p_list));}
	/// The final element of the list component
	_FORCEINLINE iterator end() { return iterator(arrFunctions.MPEnd(&p_list)); }

	/// Transfers control to the nested components start calling each of them
	CSAD_API virtual void start();

	/// Transfers control to the nested components causing update each of them
	CSAD_API virtual void update();

	/// Transfers control to the nested components quit calling each of them
	CSAD_API virtual void quit();

	/// Passes the components parameters from the BaseObject::set.
	/// @param id - id BaseObject::Base
	/// @param param - a pointer to a structure parameters.
	/// @return depends on id.
	CSAD_API void *setComponents(unsigned int id,void* param);

	/// Registers the component class
	/// @param name - the class name of the component
	/// @param info - the class identifier
	/// @param fun - the class identifier
	CSAD_API static int regClass(const char *name,const void *info,tfSTDCALL_p_FUNC_p fun);

	/// Create a component class name and adds it to the container.
	/// @param name - the name of the component class.
	/// @return a new component, or available in the container
	_FORCEINLINE Component *addComponent(char * name) { return (Component *)newContainerComponentByName(this,name); }

	/// Creates a component class name and add it to the container, if the component is already contained in the container is returned to the available component
	/// @param name - the name of the component class.
	/// @return a new component, or available in the container
	_FORCEINLINE Component *addComponent(const char * name) { return (Component *)newContainerComponentByName(this,(char*)name); }

	/// Returns the component of the specified class.
	/// @param name - the name of the component class.
	/// @return the component is available in a container, or null if it is not.
	_FORCEINLINE Component *getComponent(char * name) {return (Component *)getContainerComponent(this,name);}

	/// Returns the component of the specified class.
	/// @param name - the name of the component class.
	/// @return the component is available in a container, or null if it is not.
	_FORCEINLINE Component *getComponent(const char * name) {return (Component *)getContainerComponent(this,(char*)name);}

	/// detaches and removes components
	_FORCEINLINE void freeComponents() {coreFunctions.ContainerFree(this);}
	/// Returns list of Components
	_FORCEINLINE ComponentsMap& list() {return *((ComponentsMap*)&p_list);}

	///
	CSAD_API static bool isRegistered(char * name);
	static _FORCEINLINE bool isRegistered(const char * name) {return isRegistered((char*)name);}

	///
	CSAD_API static ObjectInfo *getInfo(char * name);

	/// 
	CSAD_API virtual const char *getPath();

	CSAD_API void *set(unsigned _int32,void *);

	static _FORCEINLINE void* t() {return 0;}

protected:
	void* p_list;

	//Component**addComponent(Component*,void *info);
	//Component* addComponent(void *info);
	CSAD_API void removeComponent(void *info);
	CSAD_API void deleteComponent(void *info);

	friend class Component;
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* CONTAINERCOMPONENTS_H_ */
