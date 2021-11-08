/*
 * corefunctions.cpp
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <core/corefunctions.h>
#include <bt/macroscall.h>
#include "base/baseapi.h"
#include "csadcore.h"
#include "base/basecontainer.h"

OPTIMIZE_ON;

csad::sFunctionsCore coreFunctions={0,(bt::tfSTDCALL_PROC_uint)csad::initCore,(bt::tfSTDCALL_PROC)csad::resetCore};

enum States {
	VALIDED = 0x011F1C01,
	FREE = 0
};

unsigned int fisCoreVal=FREE;

namespace csad {

void _APICALL initCore(unsigned int flagMask)
{
	if (fisCoreVal==VALIDED) return;
	fisCoreVal=VALIDED;

	csad::sFunctionsCore *as=(csad::sFunctionsCore *)&coreFunctions;
	as->version=0;
	
	as->CoreCreaete=(bt::tfSTDCALL_p_FUNC)&csad::CoreCreaete;
	as->Core=(bt::tfSTDCALL_p_FUNC)&csad::csadCore;
	as->SetCore=(bt::tfSTDCALL_PROC_p)&csad::SetCore;

	as->ContainerDestructor=(bt::tfSTDCALL_PROC_p)&csad::_ContainerDestructorDEF;
	as->ContainerFree=(bt::tfSTDCALL_PROC_p)&csad::_ContainerFreeDEF;

}

void _APICALL resetCore() {
	fisCoreVal=0;
}

}

OPTIMIZE_OFF;
