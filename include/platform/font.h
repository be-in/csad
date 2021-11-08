/*
 * font.h
 *
 *  Created on: 28.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef FONT_H_
#define FONT_H_

#include <core/baseobject.h>
#include <platform/platformapi.h>
#include <bt.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace gen {

class GeometryPath2I;

}

namespace csad {

using namespace bt;
using namespace gen;

class FontServer;

/**
 * @class Font
 *
 * @ingroup platform
 * @brief Font - The font object belongs to font server.
 *
 @verbatim
   <Font name="name" font="font name" size="size font"/>
 @endverbatim
 * @see FontServer, platform
 *
 *
 */

class Font: public BaseObject {
public:
	MEMMANAGERCLEAN(Font)

	/// font style, can mix
	enum Style {
		/// default
		NONE=0,
		/// bold style
		BOLD = 1,
		/// italic style
		ITALIC = 2,
		/// underline style
		UNDERLINE = 4
	};

	PLATFORM_API Font(FontServer *server, char *name);
	PLATFORM_API Font(FontServer *server, const char *name="");
	PLATFORM_API ~Font();

	/// Specifies the name of the font, for some platforms, you set the font file name
	PLATFORM_API void setName(char *name);
	PLATFORM_API void setName(const char *name);
	/// return font name.
	PLATFORM_API const char *getName();

	/// specifies the font size
	PLATFORM_API virtual void setSize(int size);
	PLATFORM_API virtual int getSize();

	/// Sets the font style bold
	PLATFORM_API void setBold(bool val);
	PLATFORM_API bool getBold();
	/// Sets the font style inclined
	PLATFORM_API void setItalic(bool val);
	PLATFORM_API bool getItalic();
	/// Sets the font style underlined
	PLATFORM_API void setUnderLine(bool val);
	PLATFORM_API bool getUnderLine();

	/// Sets the style of the font
	PLATFORM_API virtual void setStyle(int style);
	///
	PLATFORM_API virtual int getStyle();

	PLATFORM_API virtual float width(unsigned _int32 simvol);

	/// Supplements geometry glyph of the specified character
	PLATFORM_API virtual float addOutLine(int x,int y,char simvol, GeometryPath2I *path);

	/// Creates a raster of the text
	PLATFORM_API virtual void rasterText(void *raster,int x,int y,unsigned int color,int mode,char*text);

	/// Long labels
	PLATFORM_API virtual float width(char *text);
	/// font height
	PLATFORM_API virtual float height();

	PLATFORM_API void *set(unsigned _int32 id,void *param);

	PLATFORM_API static Font *finder(char *path);

	PLATFORM_API TYPEINFO_H

private:
	FontServer *p_parent;
	ShortString p_name;
	int p_size;
	int p_style;
	bool p_chenged;

	void _init();
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* FONT_H_ */
