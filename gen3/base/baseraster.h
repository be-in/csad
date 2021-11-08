/*
 * baseraster.h
 *
 *  @brief core, 2003-2014
 *
 *  Created on: 12.04.2008
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#pragma once
#ifndef BASE_RASTER_H
#define BASE_RASTER_H

#include <gen3/types.h>

OPTIMIZE_ON;

namespace gen {

	void* _APICALL _CreateRasterDEF(_int32 width,_int32 height,_int32 bpp);
	void* _APICALL _CloneRasterDEF(void *raster);
	void _APICALL _FreeRasterDEF(void *raster);

	void _APICALL _RasterColorDEF(void *raster,unsigned _int32 color);
	void _APICALL _RasterColor1BDEF(void *raster,unsigned _int32 color);
	void _APICALL _RasterColor3BDEF(void *raster,unsigned _int32 color);
	void _APICALL _RasterColor4BDEF(void *raster,unsigned _int32 color);

	void _APICALL _RasterGradientDEF(void *raster,int centerx,int centery,float rotate,float scale,unsigned _int32 color);
	void _APICALL _RasterGradient4BDEF(void *raster,int centerx,int centery,float rotate,float scale,unsigned _int32 color);

	void _APICALL _RasterNoiseDEF(void *raster,unsigned _int32 colorAmp,unsigned int mode);
	void _APICALL _RasterNoise4BDEF(void *raster,unsigned _int32 colorAmp,unsigned int mode);

	void _APICALL _RasterLineDEF(void *raster,int x1,int y1,int x2,int y2,int color);
	void _APICALL _RasterLine4BDEF(void *raster,int x1,int y1,int x2,int y2,int color);

	void _APICALL _RasterParticleDEF(void *raster,int centerx,int centery,int radius,float curve,unsigned _int32 color);
	void _APICALL _RasterParticle4BDEF(void *raster,int centerx,int centery,int radius,float curve,unsigned _int32 color);

	void _APICALL _RasterLightRayDEF(void *raster,int centerx,int centery,int radius,float step,unsigned _int32 mode,unsigned _int32 color);

	void _APICALL _RasterAlphaDEF(void *raster);
	void _APICALL _RasterAlpha4BDEF(void *raster);

	void _APICALL _RasterBlurDEF(void *raster,int scale);
	void _APICALL _RasterBlur4BDEF(void *raster,int scale);

	void _APICALL _RasterEmboss4BDEF(void *raster,int scalex,int scaley);
	void _APICALL _RasterDistort4BDEF(void *rastera,void *rasterb,int scalex,int scaley);
	void _APICALL _RasterSpherizer4BDEF(void *raster,int centerx,int centery,int radius);

	void _APICALL _RasterMixDEF(void *rastera,void *rasterb,_int32 offx,_int32 offy,_int32 fill);

	void _APICALL initRasterScript(void *script);
}

OPTIMIZE_OFF;

#endif //BASE_RASTER_H