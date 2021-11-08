/*
 * sceneresender.h
 *
 *  Created on: 14.11.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef SCENERESENDER_H_
#define SCENERESENDER_H_

#include <scene/scenecomponent.h>
#include <scene/transform.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

/**
 * @class SceneResender
 *
 * @ingroup core
 * @brief SceneResender - the component that redirects all events of the specified object.
 *
 * @see core
 */

class SceneResender: public SceneComponent {
public:
	MEMMANAGER(SceneResender)

	CSAD_API SceneResender();

	CSAD_API void setReceiver(char*path);
	CSAD_API void setReceiver(BaseObject *obj);

	CSAD_API void* set(unsigned _int32,void*);

	CSAD_API TYPEINFO_H
private:
	BaseObject *p_receiver;
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* SCENERESENDER_H_ */
