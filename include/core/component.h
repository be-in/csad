/*
 * component.h
 *
 *  @brief Complex software application developer, MS Visual C++ 2003-2010, QNX Momentics IDE
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <core/csadapi.h>
#include <core/baseobject.h>
#include <bt.h>

OPTIMIZE_ON;

//CSAD_API extern bool GlobalComponentDefaultValueChecker;

namespace csad {

using namespace bt;

#define COMPONENT_CLASS(classname) \
	csad::Component * _APICALL creator_##classname(void *) { return (csad::Component *)new classname(); }
#define INIT_COMPONENT(classname) \
	csad::Component::regClass(#classname,classname::t(),(bt::tfSTDCALL_p_FUNC_p)&creator_##classname);

/// Registers the class as the components of the object.
#ifndef CSAD_EXPORTS
#define REG_COMPONENT(classname) \
	COMPONENT_CLASS(classname) \
	int reg_##classname=INIT_COMPONENT(classname);
#else
#define REG_COMPONENT(classname)	
#endif

class ContainerComponents;

/**
 * @class Component
 *
 * @ingroup core
 * @brief Component - a component is a unique part of the object may not have a name, and to exist independently.
 *
 * The component has a pointer to the container to which it belongs.
 *
 * To register the component class there are two ways.
 * To register in the module:
 @verbatim
   REG_COMPONENT(SomeClass)
 @endverbatim
 *
 * To register the application:
 @verbatim
   COMPONENT_CLASS(SomeClass)

   void InitClass()
   {
      INIT_COMPONENT(SomeClass)
   }

   void main()
   {
      ...
      csadStart();
      InitClass();
	  ...
   }
 @endverbatim
 *
 * @see core
 */

class Component: public BaseObject {
public:
	MEMNULL

	CSAD_API Component();
	CSAD_API virtual ~Component();

	/// This event is fired after the program start
	CSAD_API virtual void start();

	/// This event is fired before rendering environment container component
	CSAD_API virtual void update();

	/// The event is called before the program exits
	CSAD_API virtual void quit();

	/// Returns the container in which the component.
	_FORCEINLINE ContainerComponents * getContainer() { return p_parent; }

	/// Returns the container in which the component, if the container does not match the given type 0 is returned.
	template <typename T>
	_FORCEINLINE T * getContainer() { return (T*)getContainer(T::t()); }

	/// Add component of the specified type in the container if this component already exists, returns available.
	template <typename T>
	_FORCEINLINE T* addComponent() {
		void *tp=T::t();
		Component *c=getComponent(tp);
		T* ret = static_cast<T*>(c);
		if (!c) ret=static_cast<T*>(addComponent(new T(),tp));
		return ret;
	}

	/// Returns the component of the given type, if it is not in a container returns 0.
	template <typename T>
	_FORCEINLINE T* getComponent() {
		return static_cast<T*>(getComponent(T::t()));
	}

	CSAD_API void *set(unsigned _int32,void*);

	/// Registers the component class
	/// @param name - the class name of the component
	/// @param info - the class identifier
	/// @param fun - the class constructor
	CSAD_API static int regClass(const char *name,const void *info, tfSTDCALL_p_FUNC_p fun);

	_FORCEINLINE static int dataIn() { return ((int)&reinterpret_cast<const volatile char&>((((csad::Component *)0)->p_parent))) + MULSIZEOFVOID(1); }

	CSAD_API TYPEINFO_H

protected:
	// ???
	void addManager(Component *) {}
	ContainerComponents *p_parent;

	CSAD_API ContainerComponents *getContainer(void *);
	CSAD_API Component *addComponent(Component *,void *);
	CSAD_API Component *getComponent(void *);

friend class ContainerComponents;
};

}

OPTIMIZE_OFF;

#endif /* COMPONENT_H_ */
