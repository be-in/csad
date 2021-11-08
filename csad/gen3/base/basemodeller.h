/*
 * basemdeller.h
 *
 *  @brief core, 2003-2014
 *
 *  Created on: 12.04.2008
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#pragma once
#ifndef BASE_MODELLER_H
#define BASE_MODELLER_H

#include <gen3/types.h>

OPTIMIZE_ON;

namespace gen {

	void* _APICALL _CreateLoftDEF();

	void _APICALL _LoftAddDEF(void *loft,float x,float y,float z,float w,_int32 flag);

	void _APICALL _FreeLoftDEF(void*loft);

	void* _APICALL _CloneMeshDEF(void *mesh);

	void _APICALL _FreeMeshDEF(void *mesh);

	void _APICALL _MeshColorDEF(void *mesh,unsigned _int32 color);

	void _APICALL _MeshGradientDEF(void *mesh,float x,float y,float rx,float ry,float s,unsigned _int32 colora,unsigned _int32 colorb);

	void _APICALL _MeshTranslateDEF(void *mesh,float x,float y,float z);

	void _APICALL _MeshRotateDEF(void *mesh,float x,float y,float z);

	void _APICALL _MeshScaleDEF(void *mesh,float x,float y,float z);

	void _APICALL _MeshPlaneScaleDEF(void *mesh,float x, float y, float z, float rx, float ry, float r, float zoom);

	void _APICALL _MeshSphereScaleDEF(void *mesh,float x, float y, float z, float r, float zoom,float f);

	void _APICALL _MeshSphereTranslateDEF(void *mesh,float x, float y, float z, float r, float addx, float addy, float addz,float f);

	void _APICALL _MeshFlipDEF(void *mesh,float rx,float ry);

	void _APICALL _MeshExtrudeDEF(void *mesh,void *fase,float exturde,_int32 cels,_int32 flag);

	void _APICALL _MeshBoxDEF(void *mesh,_int32 xcels,_int32 ycels,_int32 zcels,float width,float height,float lenght);

	void _APICALL _MeshSphereDEF(void *mesh,_int32 xcels,_int32 ycels,float radius);

	void _APICALL _MeshLoftDEF(void *mesh,void *loft,void *fase,int loftdetail,int facedetail,int flag);

	void _APICALL _MeshMixDEF(void *mesha,void *meshb);

	void _APICALL initMeshScript(void *script);
}

OPTIMIZE_OFF;

#endif //BASE_MODELLER_H