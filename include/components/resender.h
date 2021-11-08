/*
 * resender.h
 *
 *  Created on: 14.11.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef RESENDER_H_
#define RESENDER_H_

#include <core/component.h>
#include <core/containercomponents.h>

OPTIMIZE_ON;

namespace csad {

/**
 * @class Resender
 *
 * @ingroup core
 * @brief Resender - the component that redirects all events of the specified object.
 *
 * @see core
 */

class Resender: public Component {
public:
	MEMMANAGER(Resender)

	Resender();

	void setReceiver(char*path);
	void setReceiver(BaseObject *obj);

	void* set(unsigned _int32,void*);

	TYPEINFO_H
private:
	BaseObject *p_receiver;
};

}

OPTIMIZE_OFF;

#endif /* RESENDER_H_ */
