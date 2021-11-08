/*
 * baseface.h
 *
 *  @brief core, 2003-2014
 *
 *  Created on: 12.04.2008
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#pragma once
#ifndef BASE_FACE_H
#define BASE_FACE_H

#include <gen3/types.h>

OPTIMIZE_ON;

namespace gen {

	void* _APICALL _CreateFaceDEF();

	void _APICALL _FaceAddDEF(void *face,float x,float y,_int32 flag);

	void _APICALL _FreeFaceDEF(void*face);
	
	void _APICALL _FaceLineFilterDEF(void*fase,float smooth);

	void _APICALL _FaceStrokerDEF(void*fase,void*rez,_int32 smooth,float width,float offset);

	_int32 _APICALL _FaceTextDEF(void*face,void*font,void*text,float x,float y,float kerning,float step);

}

OPTIMIZE_OFF;

#endif //BASE_FACE_H


