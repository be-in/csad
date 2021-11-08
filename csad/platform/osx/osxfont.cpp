/*
 * osxfont.cpp
 *
 *  Created on: 28.08.2013
 *      Author: Panteleymonov Aleksandr
 */

#include <platform/platformapi.h>

#if defined (OS_OSX)

#include <platform.h>
#include <gen3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype2/freetype/freetype.h>
#include <freetype2/freetype/ftglyph.h>
#include <freetype2/freetype/ftbitmap.h>

OPTIMIZE_ON;

namespace csad {

using namespace gen;

#define FIXEDFLOAT16x16 0.0000152587890625

Font::Font(FontServer *server, char *name)
{
	_init();
	p_parent=server;
	p_parent->p_font.addObject(this,name);
}

Font::Font(FontServer *server, const char *name)
{
	_init();
	p_parent=server;
	p_parent->p_font.addObject(this,name);
}

Font::~Font()
{
	p_parent->p_font.detachObject(this);
}

void Font::_init()
{
	p_style=0;
	p_chenged=false;
	p_size=8;
}

/*Font::Font(char *name,int size,Stile stile)
{
	p_name=name;
	p_size=size;
	setStile(stile);
}*/

void Font::setName(char *name)
{
	p_name=name;
}

void Font::setName(const char *name)
{
	p_name=name;
}

const char *Font::getName()
{
	return p_name.str();
}

void Font::setSize(int size)
{
	p_size=size;
}

int Font::getSize()
{
	return p_size;
}

void Font::setBold(bool val)
{
	if (val) p_style=p_style | Font::BOLD;
	if (!val) p_style=p_style & (~Font::BOLD);
	p_chenged=true;
}

bool Font::getBold()
{
	return (p_style & Font::BOLD)!=0;
}

void Font::setItalic(bool val)
{
	if (val) p_style=p_style | Font::ITALIC;
	if (!val) p_style=p_style & (~Font::ITALIC);
	p_chenged=true;
}

bool Font::getItalic()
{
	return (p_style & Font::ITALIC)!=0;
}

void Font::setUnderLine(bool val)
{
	if (val) p_style=p_style | Font::UNDERLINE;
	if (!val) p_style=p_style & (~Font::UNDERLINE);
	p_chenged=true;
}

bool Font::getUnderLine()
{
	return (p_style & Font::UNDERLINE)!=0;
}

void Font::setStyle(int stile)
{
	p_style=stile;
}

int Font::getStyle()
{
	return p_style;
}

bool initFont(void *parent,Font*font,FT_Face *face)
{
	int style=font->getStyle();
	int size=font->getSize();

	if (FT_New_Face((FT_Library)parent,font->getName(),0,face))
	{
		Log::console("FT_New_Face: Could not load font %s",font->getName());
	    return false;
	}

	//(*face)->style_flags

	//face
	if (FT_Set_Pixel_Sizes( *face, size, size )) {
		Log::console("FT_Set_Pixel_Sizes: setsize %s",size);
		return false;
	}

	if (FT_Set_Char_Size( *face, size*64, size*64, 60, 60 )) {
		Log::console("FT_Set_Char_Size: setsize %s",size);
		return false;
	}


/*	int bold=0;
	if ((style&Font::BOLD)!=0) bold=FW_BOLD;
	bool underline=(style&Font::UNDERLINE)!=0;
	bool italic=(style&Font::ITALIC)!=0;*/
	//*hf=CreateFontA(size,0,0,0,bold,italic,underline,0,RUSSIAN_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,DEFAULT_PITCH,font->getName());
	return true;
}

float Font::width(unsigned _int32 simvol)
{
	FT_Face face;

	if (initFont(p_parent->p_pf,this,&face)) {
		FT_UInt glyph_index = FT_Get_Char_Index( face, simvol );
		FT_Load_Glyph( face,  glyph_index, FT_LOAD_DEFAULT );
		FT_Glyph glyph;
		FT_Get_Glyph( face->glyph, &glyph );
		FT_GlyphSlot slot = face->glyph;
		int size=slot->linearHoriAdvance*FIXEDFLOAT16x16;
		FT_Done_Glyph(glyph);
		FT_Done_Face(face);
		return size;
	} else return 0;
}

float Font::addOutLine(int x,int y,unsigned _int32 simvol, GeometryPath2I *path)
{
	FT_Face face;

	if (initFont(p_parent->p_pf,this,&face)) {
		FT_UInt glyph_index = FT_Get_Char_Index( face, simvol );
		FT_Load_Glyph( face,  glyph_index, FT_LOAD_DEFAULT );
		FT_Glyph glyph;
		FT_Get_Glyph( face->glyph, &glyph );
		FT_GlyphSlot slot = face->glyph;

		if (glyph->format==FT_GLYPH_FORMAT_OUTLINE) {
			FT_OutlineGlyph og=(FT_OutlineGlyph)glyph;
			FT_Vector *ppnt=og->outline.points;
			char *tags=(char *)&og->outline.tags;
			int first=-1;

			GeometryPath<vector2i> *tpath=(GeometryPath<vector2i> *)path;

			for (int i=0;i<og->outline.n_contours;i++) {
				int last=og->outline.contours[i];
				for (int j=0;j<last-first;j++) {
					//if (*tags==FT_CURVE_TAG_CUBIC  || *tags==FT_CURVE_TAG_CUBIC ) {
						bt::vector2i v=bt::vector2i(ppnt->x*0.015625+x,y+ppnt->y*0.015625); //*0.015625
						if ((j==0) || (tpath->vectors().last()!=v))
							tpath->addVector(v,j==0);
					//}
					ppnt++;
					tags++;
				}
				first=last;
			}
		}
		FT_Done_Glyph(glyph);

		float size=slot->linearHoriAdvance*FIXEDFLOAT16x16;

		FT_Done_Face(face);
		return size;
	} else return 0;
}

void Font::rasterText(void *raster,int x,int y,unsigned int color,int mode,char*text)
{
	gen::Raster *lraster=(gen::Raster *)raster;
	FT_Face face;

	if (initFont(p_parent->p_pf,this,&face)) {
		float posx=x;
		float base=p_size+(face->bbox.yMin*p_size*1.0/(face->bbox.yMax-face->bbox.yMin));

		while (*text) {
			FT_UInt glyph_index = FT_Get_Char_Index( face, *text );
			FT_Load_Glyph( face,  glyph_index, FT_LOAD_DEFAULT );
			FT_Glyph glyph;
			FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
			FT_Get_Glyph( face->glyph, &glyph );
			FT_GlyphSlot slot = face->glyph;

			//FT_Glyph_To_Bitmap(&glyph,FT_RENDER_MODE_NORMAL,0,1);

			if (glyph->format==FT_GLYPH_FORMAT_BITMAP) {
				FT_BitmapGlyph bit=(FT_BitmapGlyph)glyph;
				FT_Bitmap *bitmap = &bit->bitmap;
				FT_Bitmap tempbitmap;
				if (bitmap->pixel_mode==FT_PIXEL_MODE_MONO) {
					FT_Bitmap_New(&tempbitmap);
					FT_Bitmap_Convert((FT_Library)p_parent->p_pf,bitmap,&tempbitmap,1);
					bitmap=&tempbitmap;
					unsigned char *buf=tempbitmap.buffer;
					for (int i=0;i<tempbitmap.rows*tempbitmap.pitch;i++) {
						if (*buf>0) *buf=255;
						buf++;
					}
				}

				gen::Raster rasterb;
				rasterb.data=(char*)bitmap->buffer;
				rasterb.width=bitmap->width;
				rasterb.height=bitmap->rows;
				rasterb.bpp=1;//bitmap.pixel_mode; //+p_size-slot->bitmap_top
				gen::ModellerRaster::mix(lraster,&rasterb,posx,y+base-slot->bitmap_top,mode,0);
				if (bitmap==&tempbitmap) {
					FT_Bitmap_Done((FT_Library)p_parent->p_pf,bitmap);
				}
			}

			posx+=slot->linearHoriAdvance*FIXEDFLOAT16x16;
			FT_Done_Glyph(glyph);
			text++;
		}

		FT_Done_Face(face);
	}
}

float Font::height()
{
/*	FT_Face face;

	if (initFont(p_parent->p_pf,this,&face)) {

		FT_Done_Face(face);
	}*/

	return p_size;
}

float Font::width(char *text)
{
	if (!text) return 0;

	FT_Face face;

	if (initFont(p_parent->p_pf,this,&face)) {

		float size=0;
		while (*text) {
			FT_UInt glyph_index = FT_Get_Char_Index( face, *text );
			FT_Load_Glyph( face,  glyph_index, FT_LOAD_DEFAULT );
			FT_Glyph glyph;
			FT_Get_Glyph( face->glyph, &glyph );
			FT_GlyphSlot slot = face->glyph;

			size+=slot->linearHoriAdvance*FIXEDFLOAT16x16;
			text++;
			FT_Done_Glyph(glyph);
		}

		FT_Done_Face(face);
		return size;
	} else return 0;
}

void *Font::set(unsigned int id,void *param)
{
	if (id==BaseObject::TYPE) return Font::t();
	if (id==BaseObject::WRITE) {
		ParametersList *list=(ParametersList *)param;
		if (list->contains("font")) setName((*list)["font"].getString());
		if (list->contains("size")) setSize((*list)["size"].getInt(8));
		if (list->contains("bold")) setBold((*list)["bold"].getBool(false));
		if (list->contains("italic")) setItalic((*list)["italic"].getBool(false));
	}
	return 0;
}

TYPEINFO(Font)

}

OPTIMIZE_OFF;

#endif
