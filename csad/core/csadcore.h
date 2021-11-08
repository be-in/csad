/*
 * csadcore.h
 *
 *  Created on: 13.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef LOCAL_CORE_H_
#define LOCAL_CORE_H_

#include <bt.h>
#include <core/core.h>
#include <core/input.h>
#include <core/graph.h>
#include <core/system.h>
#include <core/containercomponents.h>
#include <core/component.h>

WARNING_DISABLE;

namespace csad {

csad::Core* _APICALL CoreCreaete();
csad::Core* _APICALL csadCore();
void _APICALL SetCore(csad::Core* core);

typedef SortVoidVector<ContainerComponents> ContainerList;
typedef SortVoidVector<Component> ComponentsList;

/**
 * @class CsadCore
 *
 * @ingroup core
 * @brief CsadCore - менеджер приложения.
 *
 * @see core
 */

class LocalCore:public Core {
public:
	MEMDEFAULT(LocalCore)

	LocalCore();
	~LocalCore();

	enum Flag {
		LOCK_UPDATE = 0x00000001,
	};

	void init();
	void start();
	void quit();

	_FORCEINLINE unsigned int getFlag() {return p_flag;}

	bool loadCore(char* config);

	_FORCEINLINE ContainerList &containers() { return p_startC; }
	_FORCEINLINE ComponentsList &components() { return p_start; }

	void *set(unsigned _int32 ,void*);

	TYPEINFO_H

private:

	unsigned int p_flag;

	ContainerList p_startC;
	ComponentsList p_start;

	friend class ContainerComponents;
	friend class Component;
};

extern Core* core;

}

WARNING_ENABLE;

#endif /* LOCAL_CORE_H_ */
