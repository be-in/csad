/*
 * linuxfontserver.cpp
 *
 *  Created on: 30.08.2013
 *      Author: Panteleymonov Aleksandr
 */

#include <platform/platformapi.h>

#if defined (OS_LINUX)

#include <platform.h>
#include <core/graph.h>
#include <scene/fonttext.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype2/freetype/freetype.h>

OPTIMIZE_ON;

namespace csad {

FontServer::FontServer(char *name)
{
	p_dll=0;
	p_pf=0;
	Graph::graph().p_fontserver->addObject(this,name);
}

FontServer::FontServer(const char *name)
{
	p_dll=0;
	p_pf=0;
	Graph::graph().p_fontserver->addObject(this,name);
}

FontServer::~FontServer()
{
	Graph::graph().p_fontserver->detachObject(this);
	p_font.destroyObjects<Font>();
}

void FontServer::setOptions(char *options)
{
	p_options=options;
}

Font *FontServer::createFont(char *name)
{
	if (name[0]!=0) {
		Font *font=(Font*)p_font.getObject(name);
		if (font) return font;
	}
	Font *font=new Font(this,name);
	return font;
}

FontText *FontServer::createFontText(char *name)
{
	if (name[0]!=0) {
		FontText *font=(FontText*)p_font.getObject(name);
		if (font) return font;
	}
	FontText *font=new FontText(this,name);
	return font;
}

Font *FontServer::getFont(char *name)
{
	return (Font *)p_font.getObject(name);
}

FontText *FontServer::getFontText(char *name)
{
	return (FontText *)p_font.getObject(name);
}

void FontServer::init()
{
	if(FT_Init_FreeType((FT_Library*)&p_dll))
	{
		Log::console("Could not init freetype library");
	    return;
	}
	p_pf=p_dll;
}

void FontServer::close()
{
	FT_Done_FreeType((FT_Library)p_dll);
	p_dll=0;
	p_pf=0;
}

}

OPTIMIZE_OFF;

#endif
