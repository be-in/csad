/*
 * baseobject.h
 *
 *  @brief base interface, 2003-2014
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef EXPORT_BASEOBJECT_H_
#define EXPORT_BASEOBJECT_H_

#include <bt.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

using namespace bt;

//class BaseObject;

/*typedef void (_STDCALL BaseObject::*tfSTDCALL_PROC_OBJ_p)(void*);
typedef void* (_STDCALL BaseObject::*tfSTDCALL_p_PROC_OBJ)();

struct ParameterInfo {
	void * offset;
	void * type;
	tfSTDCALL_PROC_OBJ_p set;
	tfSTDCALL_p_PROC_OBJ get;
};

typedef Map<std::string,Variant> ParametersList;
typedef Map<std::string,ParameterInfo> ObjectParameters;
typedef Map<void*,std::string> BaseObjectsName;

struct ObjectInfo {
	tfSTDCALL_p_FUNC_p fun;
	void* type;
	ObjectParameters parameters;
};

typedef Map<std::string,ObjectInfo> BaseObjectsList;*/

/**
 * @class BaseObject
 *
 * @ingroup core
 * @brief BaseObject - the main interface objects.
 *
 *
 * The basic template for description in the header:
 @verbatim
   class SomeClass:public csad::Component {
      public:
	  ...
          void * set(unsinged _int32 id,void * params);

		  TYPEINFO_H
      private:
	  ...
   }
 @endverbatim
 *
 * The basic template for describing the implementation:
 @verbatim
   void * SomeClass::set(unsinged _int32 id,void * params)
   {
      if (id==csad::BaseObject::TYPE) return SomeClassL::t();
      return 0;
   }

   TYPEINFO(SomeClass);
 @endverbatim
 *
 * @see core
 */

class BaseObject {
public:
	MEMNULL

	_FORCEINLINE BaseObject() {}
	_FORCEINLINE virtual ~BaseObject() {}

	/// the basic format of the interface
	enum BASE {
		/// specific identifier
		ANY = 0x00000000,
		/// processing messages
		EVENT = 0x00000001,
		/// the output pointer to the typeid() of the class;
		TYPE = 0x00000002,
		/// returns a pointer to itself if the object is a container.
		CONTAINER = 0x00000003,
		/// returns the number of managers.
		MANAGER_COUNT = 0x00000004,
		/// returns the specified Manager
		MANAGER = 0x00000005,
		/// record attributes of the object, the input is the list of parameters ObjectParameters
		WRITE = 0x00000006,
		/// read attributes object, the input is empty list of parameters ObjectParameters filled and fed to the output
		READ = 0x00000007,
		/// selection event has its peculiarities
		SELECT = 0x00000008,
		/// to execute the method
		RUN = 0x00000009,
		/// returns the list item
		LIST = 0x0000000A,
		/// number of items
		LIST_COUNT = 0x0000000B,
		/// returns the name if it is.
		NAME = 0x0000000C,
		/// returns the name if it is.
		CHILD_NAME = 0x0000000D,
	};

	enum EVENTS {
		ONCAHGE = 0x00000000,
	};

	/// used for any interface commands.
	virtual void *set(unsigned _int32 ,void *) = 0;
	
	/// the output pointer to the typeid() of the class.
	_FORCEINLINE void* type() {return set(TYPE,0);}
	_FORCEINLINE void* run(void* data) {return set(RUN,data);}
	/// record attributes of the object.
	_FORCEINLINE void write(ParametersList* data) {set(WRITE,data);}
	/// read attributes object.
	_FORCEINLINE ParametersList* read(ParametersList* data) {return (ParametersList*)set(READ,data);}
	_FORCEINLINE unsigned _int32 managers() {return (unsigned _int32)(_voidint)set(MANAGER_COUNT,0);}
	/// returns true if the object is a container.
	_FORCEINLINE bool isContainer() {return set(CONTAINER,0)!=0;}

	_FORCEINLINE void setParameter(char *name,Variant &v) {
		ParametersList param;
		param[name]=v;
		set(BaseObject::WRITE,&param);
	}

	_FORCEINLINE Variant getParameter(char *name) {
		ParametersList param;
		param[name].setString("");
		set(BaseObject::READ,&param);
		return param[name];
	}

	struct Event {
		BaseObject *obj;
		unsigned _int32 message;
		unsigned _int32 parama;
		unsigned _int32 paramb;
	};

	_FORCEINLINE void event(BaseObject*obj,unsigned _int32 message,unsigned _int32 parama,unsigned _int32 paramb) {
		Event ev;
		ev.obj=obj;
		ev.message=message;
		ev.parama=parama;
		ev.paramb=paramb;
		set(EVENT,&ev);
	}

	static _FORCEINLINE void* t() {return 0;}
private:

};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* BASEOBJECT_H_ */
