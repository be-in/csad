/*
 * interfacedatasystem.cpp
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <core/interfacedatasystem.h>
#include <scene/texture2d.h>
#include "csad/core/base/stringconsts.h"

OPTIMIZE_ON;

namespace csad {

	InterfaceDataSystem::InterfaceDataSystem()
	{
		list=0;
		maxPriority=0;
		maxSize=512*1024*1024;
		lockSize=0;
	}

	InterfaceDataSystem::~InterfaceDataSystem()
	{
		p_objects.destroyObjects<Raster>();
		arrFunctions.MPFree(&list);
	}

	bool InterfaceDataSystem::registerFormat(BaseObject * )
	{
		return false;
	}

	void InterfaceDataSystem::setAvailSize(int size)
	{
		maxSize=size;
	}

	void InterfaceDataSystem::loadRaster(char *filename,gen::Raster **raster)
	{
//		while (bt::internalmemmanager.isLock());
		*raster=(Raster *)p_objects.getObject(filename);
		if (*raster) {
			//upObjectPriority(filename);
			return;
		}
		bt::ParametersList param;
		bt::Variant *par=&param[STR_MANAGER];
		par->setVoid(&p_objects);
		par=&param[STR_FILE];
		par->setString(filename);
		par=&param["update"];
		par->setVoid(raster);
		_loadRaster(&param);
		_Raster(&param);
		//addRasterAlloc(*raster);
		//upObjectPriority(filename);
	}

	void InterfaceDataSystem::loadRasterToTexture2D(char *filename,Texture2D *text)
	{
		gen::Raster *raster=(gen::Raster *)p_objects.getObject(filename);
		if (raster) {
			text->setRaster(raster);
			//upObjectPriority(filename);
			return;
		}
		bt::ParametersList param;
		bt::Variant *par=&param[STR_MANAGER];
		par->setVoid(&p_objects);
		par=&param[STR_FILE];
		par->setString(filename);
		par=&param[STR_TEXTURE];
		par->setVoid(text);
		_loadRaster(&param);
		_Raster(&param);
		//addRasterAlloc(text->getRaster());
		//upObjectPriority(filename);
	}

	_voidint InterfaceDataSystem::addRasterAlloc(Raster *raster)
	{
		lockSize+=(raster->height*raster->width*raster->bpp);
		if (lockSize>maxSize) {
			void** key=getLowObject();
			p_objects.getObject((char*)*key);
		}
		return lockSize;
	}

	void InterfaceDataSystem::upObjectPriority(void *key)
	{
		_voidint *val=(_voidint*)arrFunctions.MPAdd(&list,key,0);
		maxPriority++;
		*val=maxPriority;
	}

	void** InterfaceDataSystem::getLowObject()
	{
		unsigned int count=arrFunctions.MPCount(&list);
		_voidint *val=(_voidint*)arrFunctions.MPArray(&list);
		_voidint *pval=val;
		while (count>0) {
			if (val[1]<pval[1]) pval=val;
			val+=2;
		}
		return (void**)pval;
	}

	void _APICALL InterfaceDataSystem::_loadRaster(ParametersList *param)
	{
		bt::Variant *par=param->find(STR_FILE);
		gen::Raster *raster=0;

		char *name=par->getString();
		int ss=extFunctions.FindCMem(name,0,256);
		char *dn = name + ss - 1;
		char *ext = dn + extFunctions.FindCMem(dn, '.', -ss) + 1;
#if defined(CSAD_TGA) || defined(TGA_CSAD)
		if (extFunctions.CmpMem(ext,(void*)"tga",4)==-1) {
			raster=gen::ModellerRaster::loadTGA(name);
		}
#endif
#if defined(CSAD_JPEG) || defined(JPEG_CSAD)
		if (extFunctions.CmpMem(ext,(void*)"jpg",4)==-1) {
			raster=gen::ModellerRaster::loadJPG(name);
		}
#endif
#if defined(SCRIPT_BT) || defined(BT_SCRIPT)
		if (extFunctions.CmpMem(ext,(void*)"script",7)==-1) {
			raster=gen::ModellerRaster::loadScript(name);
		}
#endif
		par=&(*param)["raster"];
		par->setVoid(raster);
	}

	void _APICALL InterfaceDataSystem::_Raster(ParametersList *param)
	{
		bt::Variant *par=param->find(STR_MANAGER);
		ObjectManager *manager=(ObjectManager *)par->getPointer();
		par=param->find(STR_FILE);
		char *name=par->getString();
		par=param->find("raster");
		Raster *raster=(Raster *)par->getPointer();
		if (raster) manager->addObject(raster,name);
		par=param->find(STR_TEXTURE);
		if (par) {
			Texture2D *text=(Texture2D *)par->getPointer();
			text->setRaster(raster);
		}
		par=param->find("update");
		if (par) {
			Raster **uraster=(Raster **)par->getPointer();
			*uraster=raster;
		}
	}

}

OPTIMIZE_OFF;
