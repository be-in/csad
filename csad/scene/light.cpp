/*
 * light.cpp
 *
 *  Created on: 06.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/light.h>
#include <core/classmanager.h>
#include <platform/log.h>
#include "csad/core/base/stringconsts.h"

OPTIMIZE_ON;

namespace csad {

Light::Light():
	mdirec(0.0f,0.0f,1.0f),
	fambient(0.0f,0.0f,0.0f,1.0f),
	fdiffuse(1.0f),
	fspecular(0.3f,0.3f,0.3f,1.0f),
	fcutoff(180.0f)
{
	p_mode=Point;
}

Light::~Light()
{

}

void Light::setMode(char *mode)
{
	int nmode=-1;
	if (fmemcmp(mode,(void*)"Spot",5)==-1) nmode=Spot;
	if (fmemcmp(mode,(void*)"Point",6)==-1) nmode=Point;
	if (fmemcmp(mode,(void*)"Direct",7)==-1) nmode=Direct;
	if (nmode>=0) {
		setMode(nmode);
	} else {
#ifdef LOG_CSAD
		Log::console("Light::setMode unknow mode %s",mode);
#endif
	}
}

void Light::setMode(unsigned int mode)
{
	p_mode=mode;
}

void Light::setDirection(vector3f *dir)
{
	mdirec=*dir;
}

void Light::setAmbient(vector4f *val)
{
	fambient=*val;
}

void Light::setDiffuse(vector4f *val)
{
	fdiffuse=*val;
}

void Light::setSpecular(vector4f *val)
{
	fspecular=*val;
}

void Light::setCutoff(float val)
{
	fcutoff=val;
}

void *Light::set(unsigned _int32 id,void * param)
{
	if (id==BaseObject::TYPE) return Light::t();
	if (id==BaseObject::WRITE) {
		Variant *p;
		ParametersList *list=(ParametersList *)param;
		if ((p=list->find("mode"))!=0) setMode(p->getString());
		if ((p=list->find("direction"))!=0) setDirection(&p->getVector3f());
		if ((p=list->find(STR_AMBIENT))!=0) setAmbient(&p->getVector4f());
		if ((p=list->find(STR_DIFFUSE))!=0) setDiffuse(&p->getVector4f());
		if ((p=list->find(STR_SPECULAR))!=0) setSpecular(&p->getVector4f());
		if ((p=list->find("cutoff"))!=0) setCutoff(p->getFloat());
	}
	return 0;
}

TYPEINFO(Light)

}

OPTIMIZE_OFF;
