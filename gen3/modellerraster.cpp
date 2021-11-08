/*
 * modellerraster.cpp
 *
 *  Created on: 18.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <gen3.h>
#include <format.h>
#include <platform/font.h>
#include "csad/gen3/base/baseraster.h"
#include <bt.h>

OPTIMIZE_ON;

namespace gen {

	//char FDiv[65536*2];

	ModellerRaster::ModellerRaster()
	{
		fraster=0;
		ffont=0;
		fmode=0;
	}

	void ModellerRaster::setRaster(Raster* raster)
	{
		if (fraster==raster) return;
		fraster=raster;
		if (fraster) {
		}
	}

	void ModellerRaster::setFont(csad::Font *font)
	{
		ffont=font;
	}

	void ModellerRaster::setMode(_int32 mode)
	{
		fmode=mode;
	}

	void ModellerRaster::rastertext(_int32 x,_int32 y,_int32 color,char *str)
	{
		ffont->rasterText(fraster,x,y,color,fmode,str);
	}

	/*void _FASTCALL _set32(void *data,_int32 color)
	{
		*(_int32 *)data=color;
	}

	void _FASTCALL _set24(void *data,_int32 color)
	{
		char*r=(char*)data;
		*(unsigned short*)data=(unsigned short)color;
		r[2]=color>>16;
	}

	void _FASTCALL _set16(void *data,_int32 color)
	{
		((unsigned char*)&color)[1]>>=2;
		color>>=3;
		((unsigned short*)&color)[0]<<=5;
		color>>=5;
		*(unsigned short *)data=(unsigned short)color;
	}

	void _FASTCALL _set8(void *data,unsigned _int32 color)
	{
		*(char *)data=((color &0xff)+((((color>>8) &0xff)+((color>>16) &0xff))>>1))>>1;
	}

	_int32 _FASTCALL _get32(void *data)
	{
		return *(_int32*)data;
	}

	_int32 _FASTCALL _get24(void *data)
	{
		unsigned char*r=(unsigned char*)data;
		return (r[2]<<16)+*(unsigned short*)data | 0xFF000000;
	}

	_int32 _FASTCALL _get16(void *data)
	{
		_int32 color=*(unsigned short*)data;
		color<<=5;
		((unsigned short*)&color)[0]>>=5;
		color<<=3;
		((unsigned char*)&color)[1]<<=2;
		return color | 0x70307;
	}

	_int32 _FASTCALL _get8(void *data)
	{
		unsigned char c=*(unsigned char*)data;
		return 0xFF000000+(c<<16)+(c<<8)+(c);
	}

	tfFASTCALL_PROC_p_int getBPPset(_int32 bpp)
	{
		if (bpp==4) return (tfFASTCALL_PROC_p_int)&_set32;
		if (bpp==3) return (tfFASTCALL_PROC_p_int)&_set24;
		if (bpp==2) return (tfFASTCALL_PROC_p_int)&_set16;
		if (bpp==1) return (tfFASTCALL_PROC_p_int)&_set8;
		return (tfFASTCALL_PROC_p_int)0;
	}

	tfFASTCALL_int_FUNC_p getBPPget(_int32 bpp)
	{
		if (bpp==4) return (tfFASTCALL_int_FUNC_p)&_get32;
		if (bpp==3) return (tfFASTCALL_int_FUNC_p)&_get24;
		if (bpp==2) return (tfFASTCALL_int_FUNC_p)&_get16;
		if (bpp==1) return (tfFASTCALL_int_FUNC_p)&_get8;
		return (tfFASTCALL_int_FUNC_p)0;
	}*/

	void _FASTCALL _get8set8NORMAL(void *a,void *b,_int32 c)
	{
		unsigned char *ap=(unsigned char*)a;
		unsigned char *bp=(unsigned char*)b;
		while (c>0) {
			*bp=*ap;
			bp++;
			ap++;
			c--;
		}
	}

	void _FASTCALL _get16set16NORMAL(void *a,void *b,_int32 c)
	{
		unsigned short *ap=(unsigned short*)a;
		unsigned short *bp=(unsigned short*)b;
		while (c>0) {
			*bp=*ap;
			bp++;
			ap++;
			c--;
		}
	}

	void _FASTCALL _get24set24NORMAL(void *a,void *b,_int32 c)
	{
		unsigned char *ap=(unsigned char*)a;
		unsigned char *bp=(unsigned char*)b;
		while (c>0) {
			*(unsigned short*)bp=*(unsigned short*)ap;
			bp+=2;
			ap+=2;
			*bp=*ap;
			bp+=1;
			ap+=1;
			c--;
		}
	}

	void _FASTCALL _get24set32NORMAL(void *a,void *b,_int32 c)
	{
		unsigned char *ap=(unsigned char*)a;
		unsigned char *bp=(unsigned char*)b;
		while (c>0) {
			*(unsigned short*)bp=*(unsigned short*)ap;
			bp+=2;
			ap+=2;
			*(unsigned short*)bp=*ap | 0xFF00;
			bp+=2;
			ap+=1;
			c--;
		}
	}

	void _FASTCALL _get32set24NORMAL(void *a,void *b,_int32 c)
	{
		unsigned char *ap=(unsigned char*)a;
		unsigned char *bp=(unsigned char*)b;
		while (c>0) {
			*(unsigned short*)bp=*(unsigned short*)ap;
			bp+=2;
			ap+=2;
			*bp=*ap;
			bp+=1;
			ap+=2;
			c--;
		}
	}

	void _FASTCALL _get32set32NORMAL(void *a,void *b,_int32 c)
	{
		unsigned _int32 *ap=(unsigned _int32*)a;
		unsigned _int32 *bp=(unsigned _int32*)b;
		while (c>0) {
			*bp=*ap;
			bp++;
			ap++;
			c--;
		}
	}

	tfFASTCALL_PROC_p_p_int normalmix[16]={_get8set8NORMAL,0,0,0,0,&_get16set16NORMAL,0,0,0,0,&_get24set24NORMAL,&_get24set32NORMAL,0,0,&_get32set24NORMAL,&_get32set32NORMAL};

	struct sWordLowHi {
		char Low;
		char Hi;
	};

	struct sDivvoid {
		union {
			void*ptr;
			char*rez;
			sWordLowHi div;
		};
	};

/*	void ModellerRaster::colorRaster(Raster *raster,_int32 color,_int32 mode)
	{
		tfFASTCALL_PROC_p_int setD=getBPPset(raster->bpp);
		tfFASTCALL_int_FUNC_p getD=getBPPget(raster->bpp);
		char*p = (char*)raster->data;
		_int32 bpp=raster->bpp;
		_int32 l=raster->width*raster->height;
		while (l>0) {
			_int32 c=getD(p);
			_int32 cr=gen::ModellerRaster::mixColor(color,c,mode);
			setD(p,cr);
			l--;
			p+=bpp;
		}
	}*/

	_int32 ModellerRaster::mixColor(_int32 a,_int32 b,_int32 mode)
	{
		sDivvoid data;
		Urgba rb;
		rb.color=b;
		Urgba ra;
		ra.color=a;
		data.ptr=extFunctions.FastCharDiv;
		if (mode==MIX) {
			mode=ALPHA;
		}
		data.div.Hi=rb.rgba.a;
		data.div.Low=rb.rgba.b;
		rb.rgba.b=*data.rez;
		data.div.Low=rb.rgba.g;
		rb.rgba.g=*data.rez;
		data.div.Low=rb.rgba.r;
		rb.rgba.r=*data.rez;

		if (mode==OR) {
			rb.color=rb.color | ra.color;
		}

		if (mode==XOR) {
			rb.color=rb.color^ra.color;
		}

		if (mode==ALPHA) {	
			data.div.Hi=~data.div.Hi;
			data.div.Low=ra.rgba.b;
			ra.rgba.b=*data.rez;
			data.div.Low=ra.rgba.g;
			ra.rgba.g=*data.rez;
			data.div.Low=ra.rgba.r;
			ra.rgba.r=*data.rez;
			rb.color+=ra.color;
		}
		return rb.color;
	}

	/*void ModellerRaster::mix(Raster *rastera,Raster *rasterb,_int32 x,_int32 y,_int32 mode,_int32 fill)
	{
		tfFASTCALL_PROC_p_int setD=getBPPset(rastera->bpp);
		tfFASTCALL_int_FUNC_p getD=getBPPget(rastera->bpp);
		tfFASTCALL_int_FUNC_p getS=getBPPget(rasterb->bpp);

		char *pa=(char *)rastera->data;
		char *pb=(char *)rasterb->data;
		_int32 w=rastera->width;
		_int32 h=rastera->height;
		_int32 bpp=rastera->bpp;
		_int32 bpp2=rasterb->bpp;
		_int32 w2=rasterb->width;
		_int32 h2=rasterb->height;
		_int32 mw=w2;
		_int32 mh=h2;
		if (mw<w) mw=w;
		if (mh<h) mh=h;
		if (mw==w2) w2=w;
		if (mh==h2) h2=h;
		w2+=x;
		h2+=y;

		if (y<0) {
			h2-=y;
			if (h==mh) pa-=mw*bpp*y;
			if (h!=mh) pb-=mw*bpp2*y;
			y=0;
		}
		if (x<0) {
			w2-=x;
			if (w==mw) pa-=bpp*x;
			if (w!=mw) pb-=bpp2*x;
			x=0;
		}

		if (mode==NORMAL) {
			tfFASTCALL_PROC_p_p_int n=normalmix[(bpp-1)+(bpp2-1)*4];
			if (n) {
				for (_int32 ya=0; ya<mh; ya++) {
					if ((ya<y) || (ya>=h2)) {
						if (h==mh) pa+=mw*bpp;
						if (h!=mh) pb+=mw*bpp2;
					} else {
						if (x>0) {
							if (w==mw) pa+=bpp*x;
							if (w!=mw) pb+=bpp2*x;
						}
						_int32 ce=w2-x;
						if (ce>0) n(pb,pa,ce);
						pa+=bpp*ce;
						pb+=bpp2*ce;
						if (mw>w2) {
							if (w==mw) pa+=bpp*(mw-w2);
							if (w!=mw) pb+=bpp2*(mw-w2);
						}
					}
				}
				return;
			}
		}

		for (_int32 ya=0; ya<mh; ya++) {
			if ((ya<y) || (ya>=h2)) {
				if (h==mh) pa+=mw*bpp;
				if (h!=mh) pb+=mw*bpp2;
			} else {
				if (x>0) {
					if (w==mw) pa+=bpp*x;
					if (w!=mw) pb+=bpp2*x;
				}
				for (_int32 xa=x;xa<w2;xa++) {
					_int32 c=getS(pb);
					_int32 cr=getD(pa);
					cr=gen::ModellerRaster::mixColor(cr,c,mode);
					setD(pa,cr);
					pa+=bpp;
					pb+=bpp2;
				}
				if (mw>w2) {
					if (w==mw) pa+=bpp*(mw-w2);
					if (w!=mw) pb+=bpp2*(mw-w2);
				}
			}
		}
	}*/

	/*void ModellerRaster::mixRect(Raster *rastera,Raster *rasterb,_int32 x,_int32 y,_int32 fromx,_int32 fromy,_int32 rw,_int32 rh,_int32 mode,_int32 fill)
	{
		tfFASTCALL_PROC_p_int setD=getBPPset(rastera->bpp);
		tfFASTCALL_int_FUNC_p getD=getBPPget(rastera->bpp);
		tfFASTCALL_int_FUNC_p getS=getBPPget(rasterb->bpp);

		char *pa=(char *)rastera->data;
		char *pb=(char *)rasterb->data;
		_int32 w=rastera->width;
		_int32 h=rastera->height;
		_int32 bpp=rastera->bpp;
		_int32 bpp2=rasterb->bpp;
		_int32 w2=rasterb->width;
		_int32 h2=rasterb->height;
		_int32 mw=w2;
		_int32 mh=h2;
		//if (mw>rw) mw=rw;
		//if (mh>rh) mh=rh;
		if (mw<w) mw=w;
		if (mh<h) mh=h;
		w2+=x;
		h2+=y;

		for (_int32 ya=0; ya<h; ya++) {
			if ((ya<y) || (ya>=h2)) {
				if (h==mh) pa+=mw*bpp;
				if (h!=mh) pb+=mw*bpp2;
			} else for (_int32 xa=0; xa<w; xa++) if ((xa>=x) && (xa<w2)) {
				_int32 c=getS(pb);
				_int32 cr=getD(pa);
				cr=gen::ModellerRaster::mixColor(cr,c,mode);
				setD(pa,cr);
				pa+=bpp;
				pb+=bpp2;
			} else {
				if (w==mw) pa+=bpp;
				if (w!=mw) pb+=bpp2;
			}
		}
	}*/

	void ModellerRaster::revers(void *data,_int32 widthBpp,_int32 height)
	{
		char *d=(char *)data;
		char *s=d;
		s+=widthBpp*height-widthBpp;
		height=height>>1;
		while (height>0) {
			fmemswap(d,s,widthBpp);
			s-=widthBpp;
			d+=widthBpp;
			height--;
		}
	}

#if defined(CSAD_TGA) || defined(TGA_CSAD)
	Raster *ModellerRaster::loadTGA(char *name)
	{
		FormatTGA tga;
		Raster *raster=0;
		if (tga.readFromFile(name)) {
			//bt::internalmemmanager.freeThis
			raster=new Raster();
			raster->data=tga.imgMatrix();
			raster->height=tga.height();
			raster->width=tga.width();
			raster->bpp=tga.bpp();
			tga.setMatrix(0);
		}
		return raster;
	}
#endif

#if defined(CSAD_JPEG) || defined(JPEG_CSAD)
	Raster *ModellerRaster::loadJPG(char *name)
	{
		FormatJPG jpg;
		Raster *raster=0;
		if (jpg.readFromFile(name)) {
			raster=new Raster();
			raster->data=jpg.imgMatrix();
			raster->height=jpg.height();
			raster->width=jpg.width();
			raster->bpp=jpg.bpp();
			jpg.setMatrix(0);
		}
		return raster;
	}
#endif

#if defined(SCRIPT_BT) || defined(BT_SCRIPT)
	Raster *ModellerRaster::loadScript(char *name)
	{
		RasterScript script;
		Raster *raster=0;
		if (script.readFromFile(name)) {
			script.exec();
			raster=script.result();
		}
		return raster;
	}
#endif

#if defined(CSAD_JPEG) || defined(JPEG_CSAD)
	bool ModellerRaster::saveJPG(Raster *rast,char *name,_int32 qual)
	{
		FormatJPG jpg;
		jpg.setMatrix(rast->width,rast->height,rast->bpp,rast->data);
		bool ret=jpg.writeToFile(name,qual);
		jpg.setMatrix(0);
		return ret;
	}
#endif
}

OPTIMIZE_OFF;