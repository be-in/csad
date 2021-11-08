/*
 * lightingmodel.cpp
 *
 *  Created on: 06.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/lightingmodel.h>
#include <scene/transform.h>
#include <scene/scene.h>
#include <scene/light.h>
#include <platform/log.h>
#include "csad/core/base/stringconsts.h"

OPTIMIZE_ON;

namespace csad {

LightingModel::LightingModel(Scene *scene,char*name)
{
	fscene=scene;
	if (scene) scene->p_lightingmodels.addObject(this,name);
}

LightingModel::~LightingModel()
{
	if (fscene) fscene->p_lightingmodels.detachObject(this);
	fscene=0;
}

LightingModel& LightingModel::setLight(unsigned int id,char *name)
{
	if (!fscene) return *this;
	csad::Transform *tr=fscene->getTransform(name);
	if (!tr) return *this;
	Light*light=tr->getComponent<Light>();
	if (!light) {
#ifdef LOG_CSAD
		Log::console("LightingModel::setLight can`t find light %s",name);
#endif
		return *this;
	}
	setLight(id,light);
	return *this;
}

LightingModel& LightingModel::setLight(unsigned int id,Light*light)
{
	while (flist.count()<=id) flist.assign(0);
	flist[id]=light;
	return *this;
}

void *LightingModel::set(unsigned _int32 id,void * param)
{
	if (id==BaseObject::TYPE) return LightingModel::t();
	if (id==BaseObject::WRITE) {
		Variant *p;
		ParametersList *list=(ParametersList *)param;
		if ((p=list->find(STR_LIGHT))!=0 || (p=list->find("light0"))!=0) setLight(0,p->getString());
		if ((p=list->find("light1"))!=0) setLight(1,p->getString());
		if ((p=list->find("light2"))!=0) setLight(2,p->getString());
		if ((p=list->find("light3"))!=0) setLight(3,p->getString());
		if ((p=list->find("light4"))!=0) setLight(4,p->getString());
		if ((p=list->find("light5"))!=0) setLight(5,p->getString());
		if ((p=list->find("light6"))!=0) setLight(6,p->getString());
		if ((p=list->find("light7"))!=0) setLight(7,p->getString());
	}
	return 0;
}

TYPEINFO(LightingModel)

}

OPTIMIZE_OFF;
