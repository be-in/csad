/*
 *  manager.h
 *
 *  @brief Complex software application developer, MS Visual C++ 2003-2010, QNX Momentics IDEб, gcc 4.4.2
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include <core/containercomponents.h>
#include <core/baseobject.h>
#include <bt.h>

namespace csad {

WARNING_DISABLE;
OPTIMIZE_ON;

using namespace bt;

class ObjectManager;

typedef MapName<void> ObjectsList;
typedef MapVoid<void> ObjectsFinder;
typedef MapName<ObjectManager> ManagerList;

/**
 * @class ObjectManager
 *
 * @ingroup core
 * @brief ObjectManager - tool organize objects. Is intended for storage of objects or containers components.
 *
 * @see core
 */

class ObjectManager: public BaseObject {
public:
	MEMMANAGER(ObjectManager)

	CSAD_API ObjectManager(char *name);
	CSAD_API ObjectManager(const char *name="");
	CSAD_API ~ObjectManager();

	/// Adds the object and sets it a name.
	CSAD_API bool addObject(void* obj,char *name);
	/// Adds the object and sets it a name.
	_FORCEINLINE bool addObject(void* obj,const char *name="") {return addObject(obj,(char*)name);}
	/// Returns the object by name.
	CSAD_API void * getObject(char *name);
	/// Returns the object by name.
	CSAD_API void * getObject(const char *name="");
	/// Returns the object by name, and leads to the specified type.
	template <typename T>
	_FORCEINLINE T* getObject(char *name) {return (T*)getObject(name);}
	/// Returns the object by name, and leads to the specified type.
	template <typename T>
	_FORCEINLINE T* getObject(const char *name="") {return (T*)getObject(name);}
	/// Removes the connection object named.
	CSAD_API bool removeObject(char *name);
	/// Removes the connection object named.
	CSAD_API bool removeObject(const char *name="");
	/// Removes the object
	CSAD_API bool detachObject(void* obj);
	/// Returns the name of the object if it is in the list
	CSAD_API const char* getName(void* obj);

	/// Returns a list of objects.
	_FORCEINLINE ObjectsList &getObjects() {return *((ObjectsList*)&p_objects);}

	template <typename T>
	_FORCEINLINE void destroyObjects() {
		p_genObjectName=0-1;
		ObjectsList::iterator it = p_objects.begin();
		ObjectsList::iterator end = p_objects.end();
		while (it!=end) {
			delete (T*)it.value();
			it++;
		}
		p_objects.clear();
		p_genObjectName=0;
	}

	_FORCEINLINE void clean() {p_objects.clear();}

	CSAD_API void *set(unsigned _int32 ,void *);

	/// root Manager objects
	CSAD_API static ObjectManager &manager();

	class Finder {
	public:
		Finder(char *path);
		~Finder();
		char *next();
		char *getNext() {return p_prevnext;}
	private:
		char *p_path;
		char *p_next;
		char *p_prevnext;
	};

	template <typename T>
	static T* find(char *path) {return (T*)findObject(T::t(),path);}
	template <typename T>
	static T* find(const char *path) {return (T*)findObject(T::t(),path);}

	CSAD_API static void regFinderObject(void *type,tfSTDCALL_p_FUNC_p func);

	CSAD_API static String path;

	CSAD_API TYPEINFO_H

private:
	ObjectsList p_objects;

	unsigned _int32 p_genObjectName;

	CSAD_API static void *findObject(char *path);
	CSAD_API static void *findObject(void *type,char *path);
	CSAD_API static void *findObject(void *type,const char *path);

	friend class Config;
};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* MANAGER_H_ */
