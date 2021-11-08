/*
 * system.h
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <bt.h>
#include <platform.h>
#include <core/interfacedatasystem.h>
#include <core/interfacethreadsystem.h>
#include <core/systemobject.h>

namespace csad {

OPTIMIZE_ON;

typedef MapName<SystemObject> SystemsObjectList;

class Module;

/**
 * @class System
 *
 * @ingroup core
 * @brief System - .
 *
 * @see core
 */

class System {
public:
	MEMDEFAULT(System)

	CSAD_API System();
	CSAD_API ~System();

	CSAD_API Module *createModule(char *path,char *name);
	_FORCEINLINE Module *createModule(const char *path,const char *name) {return createModule((char *)path,(char *)name);}
	CSAD_API Module *getModule(char *name);
	_FORCEINLINE Module *getModule(const char *name) {return getModule((char *)name);}

	_FORCEINLINE Timer& getTimer() {return timer;}
	_FORCEINLINE InterfaceEventSystem& getIES() {return p_IES;}
	_FORCEINLINE InterfaceRenderSystem& getIRS() {return p_IRS;}
	_FORCEINLINE InterfaceDataSystem& getIDS() {return p_IDS;}
	_FORCEINLINE InterfaceThreadSystem& getITS() {return p_ITS;}
	//SystemObject* CreateObject();

	//void update();

	CSAD_API static System &system();

private:

	Timer timer;

	// система событий устройств на базе сокетов
	InterfaceEventSystem p_IES;
	// система рендеринга
	InterfaceRenderSystem p_IRS;
	// система ресурсов - файлы кртинок обьектов и тд
	InterfaceDataSystem p_IDS;
	// система потоковых затач, для отложенной обработки или загрузки ресурсов
	InterfaceThreadSystem p_ITS;

	ObjectManager *flibraryes;
};

}

OPTIMIZE_OFF;

#endif /* SYSTEM_H_ */
