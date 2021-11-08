/*
 * classmanager.h
 *
 *  Created on: 09.08.2013
 *      Author: Пантелеймонов Александр
 */

#ifndef CSADCLASSMANAGER_H_
#define CSADCLASSMANAGER_H_

#include <core/classmanager.h>

namespace csad {

using namespace bt;

/**
 * @defgroup core csad: core - классы архитектуры
 *
 *
 *
 */

class BaseObjectsName: public MapVoid<void> {
public:
	MEMDEFAULT(BaseObjectsName)

	~BaseObjectsName();
	_FORCEINLINE ShortString& operator[](void * _key) {
		return (ShortString&)MapVoid<void>::operator[](_key);
	}
};

/**
 * @class CsadClassManager
 *
 * @ingroup core
 * @brief CsadClassManager - менеджер классов.
 *
 * @see core
 */

class CsadClassManager: public ClassManager {
public:
	MEMDEFAULT(CsadClassManager)

	CsadClassManager();
	virtual ~CsadClassManager();

	ObjectInfo* regClass(char *classNam,void * type,tfSTDCALL_p_FUNC_p creator);

	BaseObject* createObject(char *className,ParametersList *list);
	
	const char *className(void * type);
	BaseObjectsList * ObjectInfoList();
	ObjectInfo *classInfoType(void * type);
	ObjectInfo *classInfo(char * className);

	void addConst(const char*name,int c);
	int getConst(char*name);

	bool isRegistered(char * name);

private:

	BaseObjectsList p_classInfo;
	BaseObjectsName p_className;
	MapName<void> p_constName;

};

}

#endif /* CSADCLASSMANAGER_H_ */
