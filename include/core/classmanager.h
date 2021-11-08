/*
 * classmanager.h
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich
 */

#ifndef CLASSMANAGER_H_
#define CLASSMANAGER_H_

#include <bt.h>
#include <core/baseobject.h>
#include <core/csadapi.h>

WARNING_DISABLE;

namespace csad {

using namespace bt;

struct ObjectInfo {
	MEMMANAGER(ObjectInfo)

	enum Flag {
		COMPONENT = 0x00000001,
		CONTAINER = 0x00000002,
	};

	tfSTDCALL_p_FUNC_p fun;
	void* type;
	unsigned int flag;
};

typedef MapName<ObjectInfo> BaseObjectsList;

/**
 * @class ClassManager
 *
 * @ingroup core
 * @brief ClassManager - the Manager interface classes.
 *
 * @see core
 */

class ClassManager {
public:
	MEMNULL

	virtual ~ClassManager() {}

	/// register class
	/// @param classNam - the class name
	/// @param type - type of class
	/// @param creator - the method contains the algorithm object creation
	virtual ObjectInfo* regClass(char *classNam,void * type,tfSTDCALL_p_FUNC_p creator)=0;
	///
	_FORCEINLINE ObjectInfo* regClass(const char *classNam,void * type,tfSTDCALL_p_FUNC_p creator) {return regClass((char*)classNam,type,creator);}
	///
	_FORCEINLINE ObjectInfo* regClass(const char *classNam,const void * type,tfSTDCALL_p_FUNC_p creator) {return regClass((char*)classNam,(void *) type,creator);}

	/// Creates object of the specified class and passes the parameter list
	virtual BaseObject* createObject(char *className,ParametersList *list)=0;
	/// Creates object of the specified class and passes the parameter list
	_FORCEINLINE BaseObject* createObject(const char *className,ParametersList *list) {return createObject((char*)className,list);}
	
	/// Returns the name of the specified type
	virtual const char *className(void * type)=0;
	///
	virtual BaseObjectsList * ObjectInfoList()=0;
	///
	virtual ObjectInfo *classInfoType(void * type)=0;
	virtual ObjectInfo *classInfo(char * className)=0;
	_FORCEINLINE ObjectInfo* classInfo(const char * className) {return classInfo((char*)className);}

	/// Assigns the name of the constant value
	virtual void addConst(const char*name,int c)=0;
	/// Returns a constant value of its name
	virtual int getConst(char*name)=0;
	/// Returns a constant value of its name
	_FORCEINLINE int getConst(const char*name) {return getConst(name);}

	//virtual BaseObjectsList *ObjectInfoList()=0;

	virtual bool isRegistered(char * name)=0;
	_FORCEINLINE bool isRegistered(const char * name) {return isRegistered((char*)name);}
};

}

WARNING_ENABLE;

#endif /* CLASSMANAGER_H_ */
