/*
 * interfacerendersystem.h
 *
 *  Created on: 15.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef INTERFACERENDERSYSTEM_H_
#define INTERFACERENDERSYSTEM_H_

#include <platform/platformapi.h>
#include <core/baseobject.h>
#include <core/systemobject.h>
#include <bt.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

typedef MapVoid<BaseObject> InterfaceRenderList;

class InterfaceRenderSystem: public SystemObject {
public:
	MEMDEFAULT(InterfaceRenderSystem)

	PLATFORM_API InterfaceRenderSystem();
	PLATFORM_API ~InterfaceRenderSystem();

	PLATFORM_API bool registerTarget(int order,BaseObject * obj);
	PLATFORM_API bool unregisterTarget(int order);
	PLATFORM_API void renderTargets();
	PLATFORM_API BaseObject* getRenderer(vector2i *global);

private:
	InterfaceRenderList p_targets;
	bool p_isupdate;
	BaseObject** p_temp;

	void Sort();
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* INTERFACERENDERSYSTEM_H_ */
