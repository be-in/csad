/*
 * sgbutton.cpp
 *
 *  Created on: 11.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/gui/sgbutton.h>
#include <scene/gui/sgstyles.h>
#include <scene/gui/sgbuttongroup.h>
#include <scene/transform.h>
#include <scene/text3d.h>
#include <scene/meshfilter.h>
#include <scene/mesh.h>
#include <scene/style.h>
#include <scene/textstyle.h>
#include <scene/camera.h>
#include <core/graph.h>
#include <core/system.h>
#include <core/input.h>
#include <components/resender.h>
#include <platform.h>

OPTIMIZE_ON;

namespace csad {

SGButton::SGButton()
{
	setMode(SGE_SetButton);
	setUseStyle(SGButtonStyle::t());
}

SGButton::~SGButton()
{
}

void * SGButton::set(unsigned _int32 id,void * param)
{
	if (id==BaseObject::TYPE) return SGButton::t();
	void *ret=SGElement::set(id,param);
	if (id==BaseObject::SELECT) return ret;
	if (id==BaseObject::WRITE) {
		return ret;
	}
	if (id==BaseObject::READ) {
		return ret;
	}
	return ret;
}

TYPEINFO(SGButton)

}

OPTIMIZE_OFF;
