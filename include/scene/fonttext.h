/*
 * fonttext.h
 *
 *  Created on: 28.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef FONTTEXT_H_
#define FONTTEXT_H_

#include <core/csadapi.h>
#include <platform/font.h>
#include <gen3.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

class Texture2D;

/**
 * @class FontText
 *
 * @ingroup platform
 * @brief FontText - Object bitmap texture font belongs to the font server.
 *
 @verbatim
   <FontText name="name" font="font name" size="size font"/>
 @endverbatim
 * @see Font, FontServer, platform
 *
 */

class FontText: public Font {
public:
	MEMDEFAULT(FontText)

	CSAD_API FontText(FontServer *server, char *name);
	CSAD_API FontText(FontServer *server, const char *name="");
	CSAD_API ~FontText();

	//void setPixels(int size);

	CSAD_API void setSize(int size);
	CSAD_API float width(unsigned _int32 simvol);
	CSAD_API float height();

	CSAD_API float addOutLine(int x,int y,unsigned _int32 simvol, GeometryPath2I *path);

	CSAD_API void *set(unsigned _int32 id,void*param);

	CSAD_API TYPEINFO_H

private:
	Texture2D *ftexture;
	gen::Raster raster;
	//int fpixels;
	char sizes[256];
	bool isBuild;

	void build();
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif