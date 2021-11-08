/*
 * modelerraster.h
 *
 *  Created on: 17.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef MODELLERRASTER_H_
#define MODELLERRASTER_H_

#include <bt.h>
#include <gen3/genapi.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {
class Font;
}

namespace gen {

using namespace csad;
using namespace bt;

/**
 * @class ModellerRaster
 *
 * @ingroup generator
 * @brief ModellerRaster - методы моделирования изображения.
 *
 * @see generator
 */

#define _RGB(r,g,b) (b)+((g)<<8)+((r)<<16)

class ModellerRaster {
public:
	MEMDEFAULT(ModellerRaster)

	GEN_API ModellerRaster();

	enum Mode {
		NORMAL = 0x0,
		ALPHA = 0x1,
		ADD = 0x2,
		SUB = 0x3,
		MUL = 0x4,
		OR = 0x5,
		AND = 0x6,
		XOR = 0x7,
		MIX = 0x8,
		COLOR = 0x9,
	};

	/// Задает рабочий растр
	GEN_API void setRaster(Raster *raster);
	/// Задает шрифт
	GEN_API void setFont(csad::Font *font);
	/// Задает режим смешивания
	GEN_API void setMode(_int32 mode);

	/// Растеризует текст в цветовую матрицу
	GEN_API void rastertext(_int32 x,_int32 y,_int32 color,char *str);

	_FORCEINLINE static void colorRaster(Raster *raster,_int32 color) { genFunctions.RasterColor(raster,color); }

	//static tfFASTCALL_PROC_p_int getBPPset(int bpp);
	//static tfFASTCALL_int_FUNC_p getBPPget(int bpp);
	GEN_API static _int32 mixColor(_int32 a,_int32 b,_int32 mode);
	/// Смешивает цветовые матрицы
	_FORCEINLINE static void mix(Raster *rastera,Raster *rasterb,_int32 x,_int32 y,_int32 fill) { genFunctions.RasterMix(rastera,rasterb,x,y,fill); }
	// Смешивает цветовые матрицы
	//GEN_API static void mixRect(Raster *rastera,Raster *rasterb,_int32 x,_int32 y,_int32 fromx,_int32 fromy,_int32 rw,_int32 rh,_int32 mode,_int32 fill);
	//static void bmpBuffToRaster(Raster *rastera,void *terb,int x,int y,int fill);
	/// переворачивает по вертикали.
	GEN_API static void revers(void *data,_int32 widthBpp,_int32 height);
#if defined(CSAD_TGA) || defined(TGA_CSAD)
	GEN_API static Raster *loadTGA(char *name);
#endif
#if defined(CSAD_JPEG) || defined(JPEG_CSAD)
	GEN_API static Raster *loadJPG(char *name);
#endif
#if defined(SCRIPT_BT) || defined(BT_SCRIPT)
	GEN_API static Raster *loadScript(char *name);
#endif
	
	//static bool saveTGA(Raster *rast,char *name,int qual);
	GEN_API static bool saveJPG(Raster *rast,char *name,_int32 qual);

private:
	csad::Font *ffont;
	Raster *fraster;
	int fmode;
};



}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* MODELERMESH_H_ */
