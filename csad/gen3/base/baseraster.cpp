/*
 * baseraster.h
 *
 *  @brief core, 2003-2014
 *
 *  Created on: 12.04.2008
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include "baseraster.h"
#include "basegen.h"
#include <bt.h>

OPTIMIZE_ON;

namespace gen {

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

	_FORCEINLINE _int32 abs(_int32 x) {
		_int32 a=(x>>31);
		return (x^a)+a;
	}
	
	_int32 _FASTCALL color32ByAlpha(_int32 color,_int32 alpha) {
		Urgba ra;
		ra.color=color;
		sDivvoid data;
		data.ptr=extFunctions.FastCharDiv;
		data.div.Hi=(char)alpha;
		data.div.Low=ra.rgba.b;
		ra.rgba.b=*data.rez;
		data.div.Low=ra.rgba.g;
		ra.rgba.g=*data.rez;
		data.div.Low=ra.rgba.r;
		ra.rgba.r=*data.rez;
		data.div.Low=ra.rgba.a;
		ra.rgba.a=*data.rez;
		//__ftol2_sse(1);
		//__purecall

		return ra.color;
	}

	_int32 _FASTCALL mixColor32Normal(_int32 colora,_int32,_int32 alpha) {
		Urgba ra;
		ra.color=colora;
		sDivvoid data;
		data.ptr=extFunctions.FastCharDiv;
		data.div.Hi=(char)alpha;
		data.div.Low=ra.rgba.b;
		ra.rgba.b=*data.rez;
		data.div.Low=ra.rgba.g;
		ra.rgba.g=*data.rez;
		data.div.Low=ra.rgba.r;
		ra.rgba.r=*data.rez;
		data.div.Low=ra.rgba.a;
		ra.rgba.a=*data.rez;
		return ra.color;
	}

	_int32 _FASTCALL mixColor32ByAlpha(_int32 colora,_int32 colorb,_int32 alpha) {
		Urgba ra;
		Urgba rb;
		ra.color=colora;
		rb.color=colorb;
		sDivvoid data;
		data.ptr=extFunctions.FastCharDiv;
		data.div.Hi=(char)alpha;
		data.div.Low=ra.rgba.b;
		ra.rgba.b=*data.rez;
		data.div.Low=ra.rgba.g;
		ra.rgba.g=*data.rez;
		data.div.Low=ra.rgba.r;
		ra.rgba.r=*data.rez;
		ra.rgba.a=(char)0xFF;
		data.div.Hi=(char)(alpha ^ 0xFF);
		data.div.Low=rb.rgba.b;
		rb.rgba.b=*data.rez;
		data.div.Low=rb.rgba.g;
		rb.rgba.g=*data.rez;
		data.div.Low=rb.rgba.r;
		rb.rgba.r=*data.rez;
		rb.rgba.a=0;
		return ra.color+rb.color;
	}

	_int32 _FASTCALL mixColor32Add(_int32 colora,_int32 colorb,_int32 alpha) {
		Urgba ra;
		Urgba rb;
		ra.color=colora;
		rb.color=colorb;
		sDivvoid data;
		data.ptr=extFunctions.FastCharDiv;
		_int32 a;
		data.div.Hi=(char)alpha;
		data.div.Low=ra.rgba.b;
		a=(unsigned char)*data.rez+(unsigned char)rb.rgba.b;
		if (a>255) a=255;
		ra.rgba.b=(char)a;
		data.div.Low=ra.rgba.g;
		a=(unsigned char)*data.rez+(unsigned char)rb.rgba.g;
		if (a>255) a=255;
		ra.rgba.g=(char)a;
		data.div.Low=ra.rgba.r;
		a=(unsigned char)*data.rez+(unsigned char)rb.rgba.r;
		if (a>255) a=255;
		ra.rgba.r=(char)a;
		a=alpha+(unsigned char)rb.rgba.a;
		if (a>255) a=255;
		ra.rgba.a=(char)a;
		return ra.color;
	}

	_int32 _FASTCALL mixColor32Sub(_int32 colora,_int32 colorb,_int32 alpha) {
		Urgba ra;
		Urgba rb;
		ra.color=colora;
		rb.color=colorb;
		sDivvoid data;
		data.ptr=extFunctions.FastCharDiv;
		_int32 a;
		data.div.Hi=(char)alpha;
		data.div.Low=ra.rgba.b;
		a=(unsigned char)*data.rez-(unsigned char)rb.rgba.b;
		if (a<0) a=0;
		ra.rgba.b=(char)a;
		data.div.Low=ra.rgba.g;
		a=(unsigned char)*data.rez-(unsigned char)rb.rgba.g;
		if (a<0) a=0;
		ra.rgba.g=(char)a;
		data.div.Low=ra.rgba.r;
		a=(unsigned char)*data.rez-(unsigned char)rb.rgba.r;
		if (a<0) a=0;
		ra.rgba.r=(char)a;
		a=alpha-(unsigned char)rb.rgba.a;
		if (a<0) a=0;
		ra.rgba.a=(char)a;
		return ra.color;
	}

	_int32 _FASTCALL mixColor32Mul(_int32 colora,_int32 colorb,_int32 alpha) {
		Urgba ra;
		Urgba rb;
		ra.color=colora;
		rb.color=colorb;
		sDivvoid data;
		sDivvoid data2;
		data.ptr=extFunctions.FastCharDiv;
		data2.ptr=extFunctions.FastCharDiv;
		data2.div.Hi=(char)alpha;
		data2.div.Low=ra.rgba.b;
		data.div.Hi=rb.rgba.b;
		data.div.Low=*data2.rez;
		ra.rgba.b=*data.rez;
		data2.div.Low=ra.rgba.g;
		data.div.Hi=rb.rgba.g;
		data.div.Low=*data2.rez;
		ra.rgba.g=*data.rez;
		data2.div.Low=ra.rgba.r;
		data.div.Hi=rb.rgba.r;
		data.div.Low=*data2.rez;
		ra.rgba.r=*data.rez;
		data2.div.Low=rb.rgba.a;
		ra.rgba.a=*data.rez;
		return ra.color;
	}

	_int32 _FASTCALL mixColor32Or(_int32 colora,_int32 colorb,_int32 alpha) {
		Urgba ra;
		ra.color=colora;
		sDivvoid data;
		data.ptr=extFunctions.FastCharDiv;
		data.div.Hi=(char)alpha;
		data.div.Low=ra.rgba.b;
		ra.rgba.b=*data.rez;
		data.div.Low=ra.rgba.g;
		ra.rgba.g=*data.rez;
		data.div.Low=ra.rgba.r;
		ra.rgba.r=*data.rez;
		data.div.Low=ra.rgba.a;
		ra.rgba.a=*data.rez;
		return ra.color | colorb;
	}

	_int32 _FASTCALL mixColor32And(_int32 colora,_int32 colorb,_int32 alpha) {
		Urgba ra;
		ra.color=colora;
		sDivvoid data;
		data.ptr=extFunctions.FastCharDiv;
		data.div.Hi=(char)alpha;
		data.div.Low=ra.rgba.b;
		ra.rgba.b=*data.rez;
		data.div.Low=ra.rgba.g;
		ra.rgba.g=*data.rez;
		data.div.Low=ra.rgba.r;
		ra.rgba.r=*data.rez;
		data.div.Low=ra.rgba.a;
		ra.rgba.a=*data.rez;
		return ra.color & colorb;
	}

	_int32 _FASTCALL mixColor32Xor(_int32 colora,_int32 colorb,_int32 alpha) {
		Urgba ra;
		ra.color=colora;
		sDivvoid data;
		data.ptr=extFunctions.FastCharDiv;
		data.div.Hi=(char)alpha;
		data.div.Low=ra.rgba.b;
		ra.rgba.b=*data.rez;
		data.div.Low=ra.rgba.g;
		ra.rgba.g=*data.rez;
		data.div.Low=ra.rgba.r;
		ra.rgba.r=*data.rez;
		data.div.Low=ra.rgba.a;
		ra.rgba.a=*data.rez;
		return ra.color ^ colorb;
	}

	_int32 _FASTCALL mixColor32Mix(_int32 colora,_int32 colorb,_int32 alpha) {
		Urgba ra;
		ra.color=colora;
		sDivvoid data;
		data.ptr=extFunctions.FastCharDiv;
		data.div.Hi=(char)alpha;
		data.div.Low=ra.rgba.b;
		ra.rgba.b=*data.rez;
		data.div.Low=ra.rgba.g;
		ra.rgba.g=*data.rez;
		data.div.Low=ra.rgba.r;
		ra.rgba.r=*data.rez;
		data.div.Low=ra.rgba.a;
		ra.rgba.a=*data.rez;
		return ra.color ^ colorb;
	}

	_int32 _FASTCALL mixColor32Color(_int32 colora,_int32 colorb,_int32 alpha) {
		Urgba ra;
		ra.color=colora;
		sDivvoid data;
		data.ptr=extFunctions.FastCharDiv;
		data.div.Hi=(char)alpha;
		data.div.Low=ra.rgba.b;
		ra.rgba.b=*data.rez;
		data.div.Low=ra.rgba.g;
		ra.rgba.g=*data.rez;
		data.div.Low=ra.rgba.r;
		ra.rgba.r=*data.rez;
		data.div.Low=ra.rgba.a;
		ra.rgba.a=*data.rez;
		return ra.color ^ colorb;
	}

	void _FASTCALL _set32(void *data,_int32 color)
	{
		*(_int32 *)data=color;
	}

	void _FASTCALL _set24(void *data,_int32 color)
	{
		char*r=(char*)data;
		*(unsigned short*)data=(unsigned short)color;
		r[2]=(char)(color>>16);
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

	void * setByBPP[4]={_set8,_set16,_set24,_set32};
	void * getByBPP[4]={_get8,_get16,_get24,_get32};
	void *mixColor32[10]={mixColor32Normal,mixColor32ByAlpha,mixColor32Add,mixColor32Sub,mixColor32Mul,mixColor32Or,mixColor32And,mixColor32Xor,mixColor32Mix,mixColor32Color};

	void* _APICALL _CreateRasterDEF(_int32 width, _int32 height,_int32 bpp)
	{
		if (bpp<1 || bpp>4) return 0;
		if (width<=0) return 0;
		if (height<=0) return 0;
		Raster *rast=new Raster();
		rast->bpp=bpp;
		rast->width=width;
		rast->height=height;
		rast->data=extFunctions.CreateMem(width*height*bpp,0);
		return rast;
	}

	void* _APICALL _CloneRasterDEF(void* raster)
	{
		Raster *rast=(Raster *)raster;
		Raster *rast2=(Raster *)_CreateRasterDEF(rast->bpp,rast2->width,rast2->height);
		extFunctions.MoveMem(rast->data,rast2->data,rast->width*rast->height*rast->bpp);
		return rast2;
	}

	void _APICALL _FreeRasterDEF(void* raster)
	{
		Raster *rast=(Raster *)raster;
		if (rast) {
			if (rast->data) extFunctions.DeleteMem(rast->data,0);
			delete rast;
		}
	}

	void _APICALL _RasterColorDEF(void *raster,unsigned _int32 color)
	{
		Raster *rast=(Raster *)raster;
		int bpp=rast->bpp;
		if (bpp==1) _RasterColor1BDEF(raster,color);
		if (bpp==3) _RasterColor3BDEF(raster,color);
		if (bpp==4) _RasterColor4BDEF(raster,color);
		return;
	}

	void _APICALL _RasterColor1BDEF(void *raster,unsigned _int32 color)
	{
		Raster *rast=(Raster *)raster;
		int bpp=rast->bpp;
		if (bpp!=1) return;
		char *buff=(char*)rast->data;
		int size=rast->height*rast->width;
		char *end=buff+size;
		unsigned char c=(char)color;
		while (buff<end) {
			*(unsigned char*)buff=c;
			buff+=1;
		}
	}

	void _APICALL _RasterColor3BDEF(void *raster,unsigned _int32 color)
	{
		Raster *rast=(Raster *)raster;
		int bpp=rast->bpp;
		if (bpp!=3) return;
		char *buff=(char*)rast->data;
		int size=rast->height*rast->width;
		size=(size<<1)+size;
		char *end=buff+size;
		unsigned short c=(unsigned short)color;
		unsigned char c1=color>>16;
		while (buff<end) {
			*(unsigned short*)buff=c;
			((unsigned char*)buff)[2]=c1;
			buff+=3;
		}
	}

	void _APICALL _RasterColor4BDEF(void *raster,unsigned _int32 color)
	{
		Raster *rast=(Raster *)raster;
		int bpp=rast->bpp;
		if (bpp!=4) return;
		char *buff=(char*)rast->data;
		int size=rast->height*rast->width;
		size=(size<<2);
		char *end=buff+size;
		unsigned _int32 c=color;
		while (buff<end) {
			*(unsigned _int32*)buff=c;
			buff+=4;
		}
	}

	void _APICALL _RasterGradientDEF(void *raster,int centerx,int centery,float rotate,float scale,unsigned _int32 color)
	{
		Raster *rast=(Raster *)raster;
		int bpp=rast->bpp;
		if (bpp==4) _RasterGradient4BDEF(raster,centerx,centery,rotate,scale,color);
	}

	void _APICALL _RasterGradient4BDEF(void *raster,int centerx,int centery,float rotate,float scale,unsigned _int32 color)
	{
		Raster *rast=(Raster *)raster;
		int bpp=rast->bpp;
		if (bpp!=4) return;
		char *buff=(char*)rast->data;
		int size=rast->height*rast->width;
		size=(size<<2);
		char *end=buff+size;
		float s;
		float c;
		matFunctions.FSinCos((float)(rotate*PI180),&c,&s);
		float ya=-centerx*c-centery*s;
		float sc=1.0f/scale;
		unsigned _int32 cl=color;
		while (buff<end) {
			float xa=ya;
			ya=ya+s;
			int w=rast->width;
			while (w>0) {
				xa=xa+c;
				float k=(xa*sc*256+256)*0.5f;
				if (k>255) k=255;
				if (k<0) k=0;
				*(unsigned _int32*)buff=color32ByAlpha(cl,matFunctions.FTrunc(k));
				buff+=4;
				w--;
			}
		}
	}

	void _APICALL _RasterNoiseDEF(void *raster,unsigned _int32 colorAmp,unsigned int mode)
	{
		Raster *rast=(Raster *)raster;
		int bpp=rast->bpp;
		if (bpp==4) _RasterNoise4BDEF(raster,colorAmp,mode);
	}

	void _APICALL _RasterNoise4BDEF(void *raster,unsigned _int32 colorAmp,unsigned int mode)
	{
		Raster *rast=(Raster *)raster;
		int bpp=rast->bpp;
		if (bpp!=4) return;
		char *buff=(char*)rast->data;
		int size=rast->height*rast->width;
		size=(size<<2);
		char *end=buff+size;
		if (mode==0) {
			while (buff<end) {
				unsigned _int32 c=(extFunctions.NoiseGet() & 0xFF) + ((extFunctions.NoiseGet() & 0xFF)<<8) + ((extFunctions.NoiseGet() & 0xFF)<<16) +0xFF000000;
				*(unsigned _int32*)buff=c;
				buff+=4;
			}
		} else if (mode==1) {
			while (buff<end) {
				unsigned _int32 c=(extFunctions.NoiseGet() & 0xFF);
				c=c+(c<<8)+(c<<16)+0xFF000000;
				*(unsigned _int32*)buff=c;
				buff+=4;
			}
		} else {
			unsigned _int32 c=colorAmp;
			while (buff<end) {
				*(unsigned _int32*)buff=c;
				buff+=4;
			}
		}
	}

	void _APICALL _RasterLineDEF(void *raster,int x1,int y1,int x2,int y2,int color)
	{
		Raster *rast=(Raster *)raster;
		int bpp=rast->bpp;
		if (bpp==4) _RasterLine4BDEF(raster,x1,y1,x2,y2,color);
	}

	void _APICALL _RasterLine4BDEF(void *raster,int x1,int y1,int x2,int y2,int color)
	{
		Raster *rast=(Raster *)raster;
		int bpp=rast->bpp;
		if (bpp!=4) return;
		_int32 x=x2-x1;
		_int32 y=y2-y1;
		_int32 *buff=(_int32 *)rast->data;

		float rc=(((unsigned _int32)color)>>24)*0.0039215686274509803921568627451f;
		_int32 cc=color & 0xFFFFFF;
		bool v=abs(x)>abs(y);
		_int32 m;
		_int32 d;
		if (v) {
			m=abs(x);
			d=abs(y);
		} else {
			m=abs(y);
			d=abs(x);
		}
		m=m<<1;
		_int32 r=m-d;
		d=d<<1;

		if (x>0) { x=1; } else if (x<0) { x=-1; }
		if (y>0) { y=1; } else if (y<0) { y=-1; }

		bt::tfFASTCALL_int_FUNC_int_int_int fun=(bt::tfFASTCALL_int_FUNC_int_int_int)mixColor32[generator->mode];

		_int32 i=(m>>1)-1;
		buff+=y1*rast->width;
		buff+=x1;
		float g=255.0f/m;
		_int32 yb=rast->width*y;
		if (v) while (i>0) {
			_int32 ds = matFunctions.FTrunc((matFunctions.FTrunc(r*g) & 0xFF)*rc);
			_int32 df = matFunctions.FTrunc((ds ^ 0xFF)*rc);
			*buff=fun(cc,*buff,ds);
			buff+=yb;
			*buff=fun(cc,*buff,df);
			buff-=yb;
			r-=d;
			if (r<0) {
				r+=m;
				buff+=yb;
			}
			buff+=x;
			i--;
		}
		if (!v) while (i>0) {
			_int32 ds = matFunctions.FTrunc((matFunctions.FTrunc(r*g) & 0xFF)*rc);
			_int32 df = matFunctions.FTrunc((ds ^ 0xFF)*rc);
			*buff=fun(cc,*buff,ds);
			buff+=x;
			*buff=fun(cc,*buff,df);
			buff-=x;
			r-=d;
			if (r<0) {
				r+=m;
				buff+=x;
			}
			buff+=yb;
			i--;
		}
	}

	void _APICALL _RasterParticleDEF(void *raster,int centerx,int centery,int radius,float curve,unsigned _int32 color)
	{
		Raster *rast=(Raster *)raster;
		int bpp=rast->bpp;
		if (bpp==4) _RasterParticle4BDEF(raster,centerx,centery,radius,curve,color);
	}

	void _APICALL _RasterParticle4BDEF(void *raster,int centerx,int centery,int radius,float curve,unsigned _int32 color)
	{
		Raster *rast=(Raster *)raster;
		int bpp=rast->bpp;
		if (bpp!=4) return;
		_int32 *buff=(_int32 *)rast->data;

		float f=curve*1024.0f;
		float a=f/(radius*radius);
		float xa=(float)(centerx*centerx);
		centerx--;
		float b=(float)(centerx*centerx-xa);
		float y=(float)(centery*centery);
		centery--;
		float b2=(float)(centery*centery-y);

		float rc=(((unsigned _int32)color)>>24)*0.0039215686274509803921568627451f;
		_int32 cc=color & 0xFFFFFF;

		bt::tfFASTCALL_int_FUNC_int_int_int fun=(bt::tfFASTCALL_int_FUNC_int_int_int)mixColor32[generator->mode];

		for (int i=0;i<rast->height;i++) {
			float x=xa;
			float b1=b;
			for (int j=0;j<rast->width;j++) {
				_int32 k = matFunctions.FTrunc(f - matFunctions.FTrunc((x + y)*a));
				if (k>0) { k=k>>8; } else k=0;
				if (k>255) k=0xFF;
				x+=b1;
				b1+=2.0f;
				*buff = fun(cc, *buff, matFunctions.FTrunc(k*rc));
				buff++;
			}
			y+=b2;
			b2+=2.0f;
		}
	}

	void _APICALL _RasterLightRayDEF(void *raster,int centerx,int centery,int radius,float step,unsigned _int32 mode,unsigned _int32 color)
	{
		bt::vector2f bs;
		float x2=(float)radius;
		float y2=0;
		matFunctions.FSinCos((float)(step*PI180),&bs.x,&bs.y);
		float r=0;
		while (r<360) {
			float rf=1.0;
			if ((mode&1)!=0) rf=0.0000152587890625f*(extFunctions.NoiseGet() & 0xFFFF);
			if ((mode&2)!=0) {
				bs.x=(float)((extFunctions.NoiseGet() & 0xFFFF)-0x7FFF);
				bs.y=(float)((extFunctions.NoiseGet() & 0xFFFF)-0x7FFF);
				bs.normalize();
			}
			float xs2=x2*bs.x-y2*bs.y;
			float ys2=y2*bs.x+x2*bs.y;
			_RasterLineDEF(raster, centerx, centery, centerx + matFunctions.FTrunc(xs2*rf), centery + matFunctions.FTrunc(ys2*rf), color);
			x2=xs2;
			y2=ys2;
			r+=step;
		}
 	}

	void _APICALL _RasterAlphaDEF(void *raster)
	{
		Raster *rast=(Raster *)raster;
		int bpp=rast->bpp;
		if (bpp==4) _RasterAlpha4BDEF(raster);
	}

	void _APICALL _RasterAlpha4BDEF(void *raster)
	{
		Raster *rast=(Raster *)raster;
		int bpp=rast->bpp;
		if (bpp!=4) return;
		_int32 *buff=(_int32 *)rast->data;

		_int32 size=rast->width*rast->height;
		while (size>0) {
			Urgba ra;
			ra.color=*buff;
			ra.rgba.b=ra.rgba.a;
			ra.rgba.g=ra.rgba.a;
			ra.rgba.r=ra.rgba.a;
			*buff=ra.color;
			buff++;
			size--;
		}
	}

	void _APICALL _RasterBlurDEF(void *raster,int scale)
	{
		Raster *rast=(Raster *)raster;
		int bpp=rast->bpp;
		if (bpp==4) _RasterBlur4BDEF(raster,scale);
	}

	void _APICALL _RasterBlur4BDEF(void *raster,int scale)
	{
		Raster *rast=(Raster *)raster;
		int bpp=rast->bpp;
		if (bpp!=4) return;
		_int32 size=rast->width*rast->height;
		char *tmp = (char*)extFunctions.CreateMem(size << 2,0);
		while (scale>0) {
			_int32 *buff=(_int32 *)rast->data;
			_int32 *buff1=buff+size-1;
			_int32 *buff2=buff+size-rast->width;
			_int32 *buff3=buff+rast->width;
			_int32 *buff4=buff+1;
			_int32 *r=(_int32 *)tmp;
			_int32 asize=0;
			while (asize<size) {
				*r=color32ByAlpha(*buff1,48)+color32ByAlpha(*buff2,48)+color32ByAlpha(*buff3,48)+color32ByAlpha(*buff4,48)+color32ByAlpha(*buff,63);
				buff++;
				buff1++;
				buff2++;
				buff3++;
				buff4++;
				r++;
				asize++;
				if (asize==1) buff1=buff;
				if (asize==rast->width) buff2=buff;
				if (asize==size-rast->width) buff3=buff;
				if (asize==size-1) buff4=buff;
			}
			extFunctions.MoveMem(tmp,rast->data,size<<2);
			scale--;
		}
		extFunctions.DeleteMem(tmp,0);
	}

	void _APICALL _RasterEmboss4BDEF(void *raster,int scalex,int scaley)
	{

	}

	void _APICALL _RasterDistort4BDEF(void *rastera,void *rasterb,int scalex,int scaley)
	{

	}

	void _APICALL _RasterSpherizer4BDEF(void *raster,int centerx,int centery,int radius)
	{

	}

	void _APICALL _RasterMixDEF(void *rastera,void *rasterb,_int32 offx,_int32 offy,_int32 fill)
	{
		Raster *ra=(Raster *)rastera;
		Raster *rb=(Raster *)rasterb;
		int bppa=ra->bpp;
		int bppb=rb->bpp;

		bt::tfFASTCALL_PROC_p_int setD=(bt::tfFASTCALL_PROC_p_int)setByBPP[bppa-1];
		bt::tfFASTCALL_int_FUNC_p getD=(bt::tfFASTCALL_int_FUNC_p)getByBPP[bppa-1];
		bt::tfFASTCALL_int_FUNC_p getS=(bt::tfFASTCALL_int_FUNC_p)getByBPP[bppb-1];

		_int32 fromb=0;
		_int32 nextb=0;
		_int32 nexta=ra->width-rb->width;
		_int32 countx=rb->width;
		_int32 tox=offx+countx;
		_int32 county=rb->height;
		_int32 toy=offy+county;
		if (tox>ra->width) {
			tox=(tox-ra->width);
			nextb+=tox;
			countx-=tox;
			nexta+=tox;
			tox=ra->width;
		}
		_int32 fromx=offx;
		if (fromx<0) {
			countx+=fromx;
			nextb-=fromx;
			fromb-=fromx;
			nexta-=fromx;
			fromx=0;
		}
		if (toy>ra->height) {
			toy=(toy-ra->height);
			county-=toy;
			toy=ra->height;
		}
		_int32 fromy=offy;
		if (fromy<0) {
			county+=fromy;
			fromb-=fromy*rb->width;
			fromy=0;
		}

		nexta*=bppa;
		nextb*=bppb;

		char*a=(char*)ra->data;
		char*b=(char*)rb->data;
		a+=((fromx+fromy*ra->width)*bppa);
		b+=(fromb*bppb);
		bt::tfFASTCALL_int_FUNC_int_int_int fun=(bt::tfFASTCALL_int_FUNC_int_int_int)mixColor32[generator->mode];
		for (int j=0;j<county;j++) {
			for (int i=0;i<countx;i++) {
				setD(a,fun(getS(b),mixColor32Normal(getD(a),0,fill),0xFF));
				a+=bppa;
				b+=bppb;	
			}
			a+=nexta;
			b+=nextb;
		}
	}
}

OPTIMIZE_OFF;


