/*
 * winfont.cpp
 *
 *  Created on: 28.08.2013
 *      Author: Panteleymonov Aleksandr
 */

#include <platform/platformapi.h>

#if defined (OS_WIN)

#include <platform.h>
#include <gen3.h>

OPTIMIZE_ON;

namespace csad {

using namespace bt;

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
	p_chenged=true;
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

HGDIOBJ initFont(void *parent,Font*font,HFONT *hf)
{
	int style=font->getStyle();
	int size=font->getSize();
	int bold=0;
	if ((style&Font::BOLD)!=0) bold=FW_BOLD;
	bool underline=(style&Font::UNDERLINE)!=0;
	bool italic=(style&Font::ITALIC)!=0;
	*hf=CreateFontA(size,0,0,0,bold,italic,underline,0,RUSSIAN_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,DEFAULT_PITCH,font->getName());
	return SelectObject((HDC)parent,*hf);
}

float Font::width(unsigned _int32 simvol)
{
	HFONT hf;
	HGDIOBJ hbold=initFont(p_parent->p_pf,this,&hf);

	//char *pnt=0;
	GLYPHMETRICS metrics;
	MAT2 mt;
	extFunctions.CleanMem(&mt,sizeof(MAT2));
	mt.eM11.value=1;
	mt.eM22.value=1;
	int size=GetGlyphOutlineA((HDC)p_parent->p_pf,simvol,GGO_NATIVE | GGO_UNHINTED,&metrics,0,0,&mt);
	if (size==GDI_ERROR) {
		return 0;
	}

	SelectObject((HDC)p_parent->p_pf, hbold);
	DeleteObject(hf);
	return metrics.gmCellIncX;
}

float Font::addOutLine(int x,int y,char simvol, GeometryPath2I *path)
{
	HFONT hf;
	HGDIOBJ hbold=initFont(p_parent->p_pf,this,&hf);

	char *pnt=0;
	GLYPHMETRICS metrics;
	MAT2 mt;
	extFunctions.CleanMem(&mt,sizeof(MAT2));
	mt.eM11.value=1;
	mt.eM22.value=1;
	int size=GetGlyphOutlineA((HDC)p_parent->p_pf,simvol,GGO_NATIVE | GGO_UNHINTED,&metrics,0,0,&mt);
	if (size==GDI_ERROR) {
		return 0;
	}
	if (size<=0)
		return metrics.gmCellIncX;
	pnt=(char*)extFunctions.CreateMem(size,0);

	int ret=GetGlyphOutlineA((HDC)p_parent->p_pf,simvol,GGO_NATIVE | GGO_UNHINTED,&metrics,size,pnt,&mt);
	if (ret==GDI_ERROR) 
		return 0;

	LPTTPOLYGONHEADER lpHeader = (LPTTPOLYGONHEADER)pnt;
	LPTTPOLYGONHEADER lpStart=lpHeader;
	LPTTPOLYCURVE lpCurve;
	POINTFX ptStart;
	int cTotal;

	GeometryPath<vector2i> *tpath=(GeometryPath<vector2i> *)path;

	int cb=tpath->vectors().count();
    while ((DWORD)lpHeader < (DWORD)(((LPSTR)lpStart) + size))
    {
        if (lpHeader->dwType == TT_POLYGON_TYPE)
        {
            cTotal = 1;
			vector2i v;
			v.x=lpHeader->pfxStart.x.value+x;
			v.y=lpHeader->pfxStart.y.value+y;
			tpath->addVector(v,true);
            lpCurve = (LPTTPOLYCURVE) (lpHeader + 1);

            while ((DWORD)lpCurve < (DWORD)(((LPSTR)lpHeader) + lpHeader->cb))
            {
				//if (lpCurve->wType!=TT_PRIM_LINE)

                ptStart = *(LPPOINTFX)((LPSTR)lpCurve - sizeof(POINTFX));
				for (int i=0;i< lpCurve->cpfx;i++) {
					int xr=lpCurve->apfx[i].x.value+x;
					int yr=lpCurve->apfx[i].y.value+y;
					if (v.x!=xr || v.y!=yr) {
						v.x=xr;
						v.y=yr;
						tpath->addVector(v);
					}
				}
				lpCurve = (LPTTPOLYCURVE)&(lpCurve->apfx[lpCurve->cpfx]);
			}
			bt::vector2i *vc=tpath->vectors().data();
			if (vc[cb]!=v) tpath->addVector(vc[cb]);
			cb=tpath->vectors().count();
        }
        else
            break;
        lpHeader = (LPTTPOLYGONHEADER)(((LPSTR)lpHeader) + lpHeader->cb);
    }

	SelectObject((HDC)p_parent->p_pf, hbold);

	extFunctions.DeleteMem(pnt,0);
	DeleteObject(hf);
	return (float)metrics.gmCellIncX;
}

void Font::rasterText(void *raster,int x,int y,unsigned int color,int mode,char*text)
{
	gen::Raster *lraster=(gen::Raster *)raster;
	gen::Raster rasterb;
	BITMAPINFO BmpI;
	extFunctions.CleanMem(&BmpI,sizeof(BmpI));
	BmpI.bmiHeader.biSize=sizeof(BmpI.bmiHeader);
	BmpI.bmiHeader.biWidth=lraster->width;
	BmpI.bmiHeader.biHeight=lraster->height;
	rasterb.width=BmpI.bmiHeader.biWidth;
	rasterb.height=BmpI.bmiHeader.biHeight;
	rasterb.bpp=3;
	BmpI.bmiHeader.biPlanes=1;
	BmpI.bmiHeader.biBitCount=24;
	BmpI.bmiHeader.biCompression=BI_RGB;
	BmpI.bmiHeader.biSizeImage=0;
	BmpI.bmiHeader.biClrUsed=0;
	BmpI.bmiHeader.biClrImportant=0;

	char *buffimg;
	HBITMAP hb=CreateDIBSection((HDC)p_parent->p_pf,&BmpI,DIB_RGB_COLORS,(void**)&buffimg,0,0);
	HGDIOBJ hbold2=SelectObject((HDC)p_parent->p_pf,hb);

	HFONT hf;
	HGDIOBJ hbold=initFont(p_parent->p_pf,this,&hf);

	SetBkMode((HDC)p_parent->p_pf, TRANSPARENT);
	unsigned char ca=color>>24;

	SetTextColor((HDC)p_parent->p_pf, _RGB(ca,ca,ca));
	int size=extFunctions.FindCMem(text,0,255);
	if (!TextOutA((HDC)p_parent->p_pf, x, y, text, size))
	{
#ifdef LOG_CSAD
		Log::console("Font::rasterText error %i",GetLastError());
#endif
	}

	//bt::extFunctions.StocBMem(buffimg+x*3+lraster->width*3*(y+6),16*3,0xFF);
	//bt::extFunctions.StocBMem(buffimg+x*3+lraster->width*3*(y+8),16*3,0xFF);

	//buffimg+=lraster->width*(lraster->height-1)*3;

	//tfFASTCALL_PROC_p_int setR=gen::ModellerRaster::getBPPset(bpp);
	//tfFASTCALL_int_FUNC_p getR=gen::ModellerRaster::getBPPget(bpp);

	gen::ModellerRaster::revers(buffimg,lraster->width*3,lraster->height);
	rasterb.data=buffimg;
	gen::sGenerator gen;
	gen.mode=mode;
	genFunctions.SetGenerator(&gen);
	genFunctions.RasterMix(lraster,&rasterb,0,0,0);

	/*Trgba c;

	if (setR) {
		c.color=color;
		for (int y=0;y<lraster->height;y++) {
			for (int x=0;x<lraster->width;x++) {
				c.rgba.a=*buffimg;
				int cr=getR(p);
				if (c.rgba.a>0) {
					cr=0;
				}
				cr=gen::ModellerRaster::mixColor(cr,c.color,mode);
				setR(p,cr);
				p+=bpp;
				buffimg+=3;
			}
		}
	}*/

	SelectObject((HDC)p_parent->p_pf, hbold);
	SelectObject((HDC)p_parent->p_pf, hbold2);
	DeleteObject(hb);
	DeleteObject(hf);
}

float Font::height()
{
	HFONT hf;
	HGDIOBJ hbold=initFont(p_parent->p_pf,this,&hf);

	OUTLINETEXTMETRIC textm;
	GetOutlineTextMetrics((HDC)p_parent->p_pf,sizeof(OUTLINETEXTMETRIC),&textm);

	SelectObject((HDC)p_parent->p_pf, hbold);
	DeleteObject(hf);

	return (float)textm.otmAscent;
}

float Font::width(char *text)
{
	if (!text) return 0;
	HFONT hf;
	HGDIOBJ hbold=initFont(p_parent->p_pf,this,&hf);

	//char *pnt=0;
	GLYPHMETRICS metrics;
	MAT2 mt;
	extFunctions.CleanMem(&mt,sizeof(MAT2));
	mt.eM11.value=1;
	mt.eM22.value=1;
	float size=0;
	while (*text) {
		int size=GetGlyphOutlineA((HDC)p_parent->p_pf,*text,GGO_NATIVE | GGO_UNHINTED,&metrics,0,0,&mt);
		if (size==GDI_ERROR) {
			return 0;
		}
		if (size>0)
			size+=metrics.gmCellIncX;
		text++;
	}

	SelectObject((HDC)p_parent->p_pf, hbold);
	DeleteObject(hf);

	return size;
}

}

OPTIMIZE_OFF;

#endif
