/*
 * genfunctions.cpp
 *
 *  Created on: 12.04.2008
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <gen3/genfunctions.h>
#include <bt/macroscall.h>
#include "base/baseraster.h"
#include "base/baseface.h"
#include "base/basemodeller.h"

OPTIMIZE_ON;

gen::sFunctionsGen genFunctions;

enum States {
	VALIDED = 0x011F1C01,
	FREE = 0
};

unsigned int fisGenVal=FREE;

gen::sGenerator *generator=0;

bool _APICALL _SetGeneratorDEF(void *val)
{
	generator=(gen::sGenerator *)val;
	if (generator) {
		generator->mode=0;
	}
	return true;
}

void _APICALL _GeneratorModeDEF(unsigned _int32 mode)
{
	if (!generator) return;
	generator->mode=mode;
}

void _APICALL initGen(unsigned int flagMask)
{
	if (fisGenVal==VALIDED) return;
	fisGenVal=VALIDED;

	gen::sFunctionsGen *as=(gen::sFunctionsGen *)&genFunctions;
	as->version=0;

	as->SetGenerator=(bt::tfSTDCALL_bool_FUNC_p)&_SetGeneratorDEF;
	as->GeneratorMode=(bt::tfSTDCALL_PROC_uint)&_GeneratorModeDEF;

	as->CreateRaster=(bt::tfSTDCALL_p_FUNC_int_int_int)&gen::_CreateRasterDEF;
	as->CloneRaster=(bt::tfSTDCALL_p_FUNC_p)&gen::_CloneRasterDEF;
	as->FreeRaster=(bt::tfSTDCALL_PROC_p)&gen::_FreeRasterDEF;
	as->RasterColor=(bt::tfSTDCALL_PROC_p_uint)&gen::_RasterColorDEF;
	as->RasterColor1B=(bt::tfSTDCALL_PROC_p_uint)&gen::_RasterColor1BDEF;
	as->RasterColor3B=(bt::tfSTDCALL_PROC_p_uint)&gen::_RasterColor3BDEF;
	as->RasterColor4B=(bt::tfSTDCALL_PROC_p_uint)&gen::_RasterColor4BDEF;
	as->RasterGradient=(bt::tfSTDCALL_PROC_p_int_int_int_int_int)&gen::_RasterGradientDEF;
	as->RasterNoise=(bt::tfSTDCALL_PROC_p_uint_uint)&gen::_RasterNoiseDEF;
	as->RasterNoise4B=(bt::tfSTDCALL_PROC_p_uint_uint)&gen::_RasterNoise4BDEF;
	as->RasterLine=(bt::tfSTDCALL_PROC_p_int_int_int_int_uint)&gen::_RasterLineDEF;
	as->RasterParticle=(bt::tfSTDCALL_PROC_p_int_int_int_float_uint)&gen::_RasterParticleDEF;
	as->RasterLightRay=(bt::tfSTDCALL_PROC_p_int_int_int_float_uint_uint)&gen::_RasterLightRayDEF;
	as->RasterDistort4B=(bt::tfSTDCALL_PROC_p_p_int_int)&gen::_RasterDistort4BDEF;
	as->RasterAlpha=(bt::tfSTDCALL_PROC_p)&gen::_RasterAlphaDEF;
	as->RasterBlur=(bt::tfSTDCALL_PROC_p_int)&gen::_RasterBlurDEF;
	as->RasterMix=(bt::tfSTDCALL_PROC_p_p_int_int_int)&gen::_RasterMixDEF;

	as->CreateFace=(bt::tfSTDCALL_p_FUNC)&gen::_CreateFaceDEF;
	as->FreeFace=(bt::tfSTDCALL_PROC_p)&gen::_FreeFaceDEF;
	as->FaceLineFilter=(bt::tfSTDCALL_PROC_p_float)&gen::_FaceLineFilterDEF;
	as->FaceStroker=(bt::tfSTDCALL_PROC_p_p_int_float_float)&gen::_FaceStrokerDEF;
	as->FaceText=(bt::tfSTDCALL_int_FUNC_p_p_p_float_float_float_float)&gen::_FaceTextDEF;

	as->CreateLoft=(bt::tfSTDCALL_p_FUNC)&gen::_CreateLoftDEF;
	as->CloneMesh=(bt::tfSTDCALL_p_FUNC_p)&gen::_CloneMeshDEF;
	as->FreeLoft=(bt::tfSTDCALL_PROC_p)&gen::_FreeLoftDEF;
	as->FreeMesh=(bt::tfSTDCALL_PROC_p)&gen::_FreeMeshDEF;
	as->MeshColor=(bt::tfSTDCALL_PROC_p_uint)&gen::_MeshColorDEF;
	as->MeshGradient=(bt::tfSTDCALL_PROC_p_float_float_float_float_float_uint_uint)&gen::_MeshGradientDEF;
	as->MeshTranslate=(bt::tfSTDCALL_PROC_p_float_float_float)&gen::_MeshTranslateDEF;
	as->MeshRotate=(bt::tfSTDCALL_PROC_p_float_float_float)&gen::_MeshRotateDEF;
	as->MeshScale=(bt::tfSTDCALL_PROC_p_float_float_float)&gen::_MeshScaleDEF;
	as->MeshPlaneScale=(bt::tfSTDCALL_PROC_p_float_float_float_float_float_float_float)&gen::_MeshPlaneScaleDEF;
	as->MeshSphereScale=(bt::tfSTDCALL_PROC_p_float_float_float_float_float_float)&gen::_MeshSphereScaleDEF;
	as->MeshSphereTranslate=(bt::tfSTDCALL_PROC_p_float_float_float_float_float_float_float_float)&gen::_MeshSphereTranslateDEF;
	as->MeshFlip=(bt::tfSTDCALL_PROC_p_float_float)&gen::_MeshFlipDEF;
	as->MeshExtrude=(bt::tfSTDCALL_PROC_p_p_float_int_int)&gen::_MeshExtrudeDEF;
	as->MeshBox=(bt::tfSTDCALL_PROC_p_int_int_int_float_float_float)&gen::_MeshBoxDEF;
	as->MeshSphere=(bt::tfSTDCALL_PROC_p_int_int_float)&gen::_MeshSphereDEF;
	as->MeshLoft=(bt::tfSTDCALL_PROC_p_p_p_int_int_int)&gen::_MeshLoftDEF;
	as->MeshMix=(bt::tfSTDCALL_PROC_p_p)&gen::_MeshMixDEF;

#if defined(SCRIPT_BT) || defined(BT_SCRIPT)
	as->initRasterScript=(bt::tfSTDCALL_PROC_p)&gen::initRasterScript;
	as->initMeshScript=(bt::tfSTDCALL_PROC_p)&gen::initMeshScript;
#endif
}

void _APICALL resetGen() {
	fisGenVal=0;
}

OPTIMIZE_OFF;
