//=============================================================================
///**
// *  @file types.h
// *
// *  $Id: types.h 27.08.2014  $
// *
// *  @brief core, 2003-2014
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#pragma once
#ifndef GEN_TYPES_H
#define GEN_TYPES_H

#include <bt/memmanager.h>
#include <bt/typesproc.h>

#ifdef __cplusplus
namespace gen {
#endif

	struct Trgba {
		char b;
		char g;
		char r;
		char a;
	};

	struct Urgba {
		union {
			Trgba rgba;
			unsigned _int32 color;
		};
	};
	
struct sGenerator {
	unsigned _int32 mode;
};

/**
 * @class Raster
 *
 * @ingroup generator
 * @brief Raster - двухмерная цветовая матрица.
 *
 * @see generator
 */

struct Raster {
	MEMMANAGER(Raster)
	int width; /// ширина
	int height; /// высота
	int bpp; /// бит на пиксель
	void *data; /// матрица
};

struct Sample {
	MEMMANAGER(Sample)
	int length; /// длинна
	int flagtype; /// тип
	void *data; /// масcив
};

/**
 * @class sFunctionsGen
 *
 * @ingroup apiinterface
 * @brief sFunctionsGen - 
 *
 * @see gen
 */
	struct sFunctionsGen {
		int version;

		bt::tfSTDCALL_bool_FUNC_p SetGenerator;
		bt::tfSTDCALL_PROC_uint GeneratorMode;

		bt::tfSTDCALL_p_FUNC_int_int_int CreateRaster;
		bt::tfSTDCALL_p_FUNC_p CloneRaster;
		bt::tfSTDCALL_PROC_p FreeRaster;

		/// Fill color
		bt::tfSTDCALL_PROC_p_uint RasterColor;
		/// Fill color
		bt::tfSTDCALL_PROC_p_uint RasterColor1B;
		/// Fill color
		bt::tfSTDCALL_PROC_p_uint RasterColor3B;
		/// Fill color
		bt::tfSTDCALL_PROC_p_uint RasterColor4B;

		bt::tfSTDCALL_PROC_p_int_int_int_int_int RasterGradient;

		bt::tfSTDCALL_PROC_p_uint_uint RasterNoise;
		/// Generate and mix noise color
		bt::tfSTDCALL_PROC_p_uint_uint RasterNoise4B;

		bt::tfSTDCALL_PROC_p_int_int_int_int_uint RasterLine;

		bt::tfSTDCALL_PROC_p_int_int_int_float_uint RasterParticle;

		bt::tfSTDCALL_PROC_p_int_int_int_float_uint_uint RasterLightRay;

		bt::tfSTDCALL_PROC_p RasterAlpha;

		bt::tfSTDCALL_PROC_p_int RasterBlur;

		bt::tfSTDCALL_PROC_p_p_int_int RasterDistort;
		/// Distortion raster
		bt::tfSTDCALL_PROC_p_p_int_int RasterDistort4B;

		bt::tfSTDCALL_PROC_p_int_int_int RasterClouds;

		bt::tfSTDCALL_PROC_p_p_int_int_int RasterMix;

		/// Create plane
		//bt:: TPlaneUI
		/// Begin Loft
		//bt:: TPlaneUI

		bt::tfSTDCALL_p_FUNC CreateFace;

		bt::tfSTDCALL_PROC_p FreeFace;

		bt::tfSTDCALL_PROC_p_float FaceLineFilter;

		bt::tfSTDCALL_PROC_p_p_int_float_float FaceStroker;

		bt::tfSTDCALL_int_FUNC_p_p_p_float_float_float_float FaceText;

		bt::tfSTDCALL_p_FUNC CreateLoft;

		bt::tfSTDCALL_p_FUNC_int CreateMesh;

		bt::tfSTDCALL_p_FUNC_p CloneMesh;

		bt::tfSTDCALL_PROC_p FreeLoft;

		bt::tfSTDCALL_PROC_p FreeMesh;

		bt::tfSTDCALL_PROC_p_uint MeshColor;

		bt::tfSTDCALL_PROC_p_float_float_float_float_float_uint_uint MeshGradient;

		bt::tfSTDCALL_PROC_p_float_float_float MeshTranslate;

		bt::tfSTDCALL_PROC_p_float_float_float MeshRotate;

		bt::tfSTDCALL_PROC_p_float_float_float MeshScale;
		/// Scale
		/// @param arg1 - mesh
		/// @param arg2 - scale center x
		/// @param arg3 - scale center y
		/// @param arg4 - scale center z
		/// @param arg5 - rotate scale plane by x
		/// @param arg6 - rotate scale plane by y
		/// @param arg7 - max size
		/// @param arg8 - scale
		bt::tfSTDCALL_PROC_p_float_float_float_float_float_float_float MeshPlaneScale;
		/// Scale 
		/// @param arg1 - mesh
		/// @param arg2 - sphere center x
		/// @param arg3 - sphere center y
		/// @param arg4 - sphere center z
		/// @param arg5 - sphare radius
		/// @param arg6 - scale
		/// @param arg9 - factor
		bt::tfSTDCALL_PROC_p_float_float_float_float_float_float MeshSphereScale;
		/// Translate
		/// @param arg1 - mesh
		/// @param arg2 - sphere center x
		/// @param arg3 - sphere center y
		/// @param arg4 - sphere center z
		/// @param arg5 - sphare radius
		/// @param arg6 - offset x
		/// @param arg7 - offset y
		/// @param arg8 - offset z
		/// @param arg9 - factor
		bt::tfSTDCALL_PROC_p_float_float_float_float_float_float_float_float MeshSphereTranslate;
		/// Flip
		/// @param arg1 - mesh
		/// @param arg2 - rotate flip plane by x
		/// @param arg3 - rotate flip plane by y
		bt::tfSTDCALL_PROC_p_float_float MeshFlip;
		/// Extrude
		/// @param arg1 - mesh
		/// @param arg2 - fase
		/// @param arg3 - extrude size
		/// @param arg4 - cells
		/// @param arg5 - flags ( 1-extrude, 2-front, 4-back, 8-smooth )
		bt::tfSTDCALL_PROC_p_p_float_int_int MeshExtrude;
		/// Box
		/// @param arg1 - mesh
		/// @param arg2 - xcells
		/// @param arg3 - ycells
		/// @param arg4 - zcells
		bt::tfSTDCALL_PROC_p_int_int_int_float_float_float MeshBox;
		/// Sphere
		/// @param arg1 - mesh
		/// @param arg2 - xcells
		/// @param arg3 - ycells
		/// @param arg4 - radius
		bt::tfSTDCALL_PROC_p_int_int_float MeshSphere;
		/// Loft
		/// @param arg1 - mesh
		/// @param arg2 - loft
		/// @param arg3 - face
		/// @param arg4 - loft cells
		/// @param arg5 - fase cells
		/// @param arg6 - flags
		bt::tfSTDCALL_PROC_p_p_p_int_int_int MeshLoft;

		bt::tfSTDCALL_PROC_p_p MeshMix;

		//bt::tfSTDCALL_PROC_p ContainerDestructor;
		//bt::tfSTDCALL_PROC_p ContainerFree;
		//bt::tfSTDCALL_PROC_p ContainerAddComponent;

		bt::tfSTDCALL_PROC_p initRasterScript;
		bt::tfSTDCALL_PROC_p initMeshScript;
	};

#ifdef __cplusplus
}
#endif

#endif
