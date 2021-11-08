/*
 * qnxfont.cpp
 *
 *  Created on: 28.08.2013
 *      Author: Александр
 */

#include <platform/platformapi.h>

#if defined (OS_QNX)

#include <platform.h>
#include <gen3.h>

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
	p_chenged=true;
}

void Font::setName(const char *name)
{
	p_name=name;
	p_chenged=true;
}

void Font::setSize(int size)
{
	p_size=size;
	p_chenged=true;
}

int Font::getSize()
{
	return p_size;
}

void Font::setBold(bool val)
{
#if _NTO_VERSION < 660
	if (val) p_style=p_style | PF_STYLE_BOLD;
	if (!val) p_style=p_style & (~PF_STYLE_BOLD);
#else
#endif
	p_chenged=true;
}

bool Font::getBold()
{
#if _NTO_VERSION < 660
	return (p_style & PF_STYLE_BOLD)!=0;
#else
	return 0;
#endif
}

void Font::setItalic(bool val)
{
#if _NTO_VERSION < 660
	if (val) p_style=p_style | PF_STYLE_ITALIC;
	if (!val) p_style=p_style & (~PF_STYLE_ITALIC);
#else
#endif
	p_chenged=true;
}

bool Font::getItalic()
{
#if _NTO_VERSION < 660
	return (p_style & PF_STYLE_ITALIC)!=0;
#else
	return 0;
#endif
}

void Font::setUnderLine(bool val)
{
#if _NTO_VERSION < 660
	if (val) p_style=p_style | PF_STYLE_ULINE;
	if (!val) p_style=p_style & (~PF_STYLE_ULINE);
#else
#endif
	p_chenged=true;
}

bool Font::getUnderLine()
{
#if _NTO_VERSION < 660
	return (p_style & PF_STYLE_ULINE)!=0;
#else
	return 0;
#endif
}

void Font::setStyle(int style)
{
	p_style=0;
#if _NTO_VERSION < 660
	if (style & Font::BOLD) p_style=p_style | PF_STYLE_BOLD;
	if (style & Font::ITALIC) p_style=p_style | PF_STYLE_ITALIC;
	if (style & Font::UNDERLINE) p_style=p_style | PF_STYLE_ULINE;
#else
#endif
	p_chenged=true;
}

int Font::getStyle()
{
	int style=0;
#if _NTO_VERSION < 660
	if (p_style & PF_STYLE_BOLD) style=style | Font::BOLD;
	if (p_style & PF_STYLE_ITALIC) style=style | Font::ITALIC;
	if (p_style & PF_STYLE_ULINE) style=style | Font::UNDERLINE;
#else
#endif
	return p_style;
}

float Font::addOutLine(int x,int y,unsigned long simvol, GeometryPath2I *path)
{
	//if ((simvol<0) || (simvol>255)) return 0;

#if _NTO_VERSION < 660
	char szFont[MAX_FONT_TAG];
	for (int i=0;i<MAX_FONT_TAG;i++) {szFont[i]=0;}

	PfGenerateFontNameCx((_Pf_ctrl *)p_parent->p_pf,p_name.str(),p_style,p_size,szFont);
	if (szFont[0]==0) {
		Log::console("Font %s not found",p_name.str());
		return 0;
	}

	pf_point_t *pnt=0;
	pf_metrics_t metrics;
	metrics.MaxX=0;
	int *loops=0;
	int count=0;
	try {
		count=PfGetOutlineCx((_Pf_ctrl *)p_parent->p_pf,szFont,simvol,&metrics,&pnt,&loops);
	}
	catch (...) {
		Log::console("Font wrong simvol %i",simvol);
		return 0;
	}
	if (simvol!=32) {
		pf_point_t *ppnt=pnt;
		for (int i=0;i<count;i++) {
			for (int j=0;j<loops[i];j++) {
				vector2i v=vector2i(ppnt->x+x,y-ppnt->y);
				if ((j==0) || (path->vectors().last()!=v))
					path->addVector(v,j==0);
				ppnt++;
			}
		}
	}

	return metrics.MaxX*FIXEDFLOAT16x16;
#else

	return 0;
#endif
}

void Font::rasterText(void *raster,int x,int y,unsigned int color,int mode,char*text)
{
#if _NTO_VERSION < 660
#else
#endif
}

float Font::height()
{
	return p_size;
}

float Font::width(char *text)
{
	if (!text) return 0;

	float size=0;

#if _NTO_VERSION < 660
	char szFont[MAX_FONT_TAG];
	for (int i=0;i<MAX_FONT_TAG;i++) {szFont[i]=0;}

	PfGenerateFontNameCx((_Pf_ctrl *)p_parent->p_pf,p_name.str(),p_style,p_size,szFont);
	if (szFont[0]==0) return 0;

	pf_metrics_t metrics;
	metrics.MaxX=0;
	while (*text) {
		PfGetOutlineCx((_Pf_ctrl *)p_parent->p_pf,szFont,*text,&metrics,0,0);
		size+=metrics.MaxX*FIXEDFLOAT16x16;
		text++;
	}

#else
#endif

	return size;
}

void *Font::set(unsigned int id,void *param)
{
	if (id==BaseObject::TYPE) return Font::t();
	if (id==BaseObject::WRITE) {
		ParametersList *list=(ParametersList *)param;
		if (list->contains("font")) setName((*list)["font"].getString());
		if (list->contains("size")) setSize((*list)["size"].getInt(8));
		if (list->contains("bold")) setBold((*list)["bold"].getBool(false));
	}
	return 0;
}

TYPEINFO(Font)

}

#endif
