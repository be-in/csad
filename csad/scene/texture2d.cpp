/*
 * texture2d.cpp
 *
 *  Created on: 19.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/texture2d.h>
#include <core/graph.h>
#include <core/system.h>
#include <platform.h>
#include <format.h>
#include "csad/platform/glextension.h"
#include "csad/core/base/stringconsts.h"

OPTIMIZE_ON;

namespace csad {

unsigned int Texture2D::p_defFilter=0x105;

const char *textureFilterNameList[]={"\007normal","\011bilinear","\012bilinear2","\012bilinear3","\012trilinear",0};
unsigned int textureFilterValList[]={0x000,0x101,0x102,0x103,0x105};
int textureFilterMinList[]={GL_NEAREST,GL_LINEAR,GL_NEAREST_MIPMAP_NEAREST,GL_LINEAR_MIPMAP_NEAREST,GL_NEAREST_MIPMAP_LINEAR,GL_LINEAR_MIPMAP_LINEAR};

Texture2D::Texture2D(char *name):p_shared(0)
{
	_init();
	Graph::graph().p_texture->addObject(this,name);
}

Texture2D::Texture2D(const char *name):p_shared(0)
{
	_init();
	Graph::graph().p_texture->addObject(this,name);
}

void Texture2D::_init()
{
	p_filter=p_defFilter;
	mm_max=127;
}

/*Texture2D::Texture2D(unsigned int texture)
{
	if (texture==0)
	{
		Render::GenTextures(1,&p_texture);
	} else {
		p_texture=texture;
	}
}

Texture2D::Texture2D(unsigned int format,int width,int height)
{
	Render::GenTextures(1,&p_texture);
	setSize(format,width,height);
}*/

Texture2D::~Texture2D()
{
}

unsigned int Texture2D::setContext(GlContext* context)
{
	if (context==p_context) return p_texture;
	p_texture=(unsigned int)(_voidint)p_shared.find(context);
	if (p_texture==0) {
		p_context=context;
		p_texture=context->createTexture2D();
		setSize(p_width,p_height);
		if (p_texture) {
			void* &p=p_shared[context];
			p=(void*)(_voidint)p_texture;
			update();
		}
	} else if (p_context==0) {
		if (context->makeCurrent()) {
			p_context=context;
			update();
		}
	}
	return p_texture;
}

int Texture2D::getWidth(int level)
{
	//Render::BindTexture2D(p_texture);
	return p_width>>level;//Render::GetTexure2DWidth();
}

int Texture2D::getHeight(int level)
{
	//Render::BindTexture2D(p_texture);
	return p_height>>level;//Render::GetTexure2DHeight();
}

void Texture2D::setSize(int width,int height)
{
	p_width=width;
	p_height=height;
	if (p_texture==0) return;
	GlContext *context = GlContext::getCurrent();
	bt::sFunctionsGLContext& functions=context->functions();
	Render::BindTexture2D(p_texture);
	Render::setMipMap(mm_min,mm_max);

	int i=0;
	int internalformat=p_format;
	if (internalformat==GL_BGRA) internalformat=GL_RGBA;
	if (internalformat==GL_BGR) internalformat=GL_RGB;
	while ((width>1) || (height>1)) {
		functions.TexImage2D(GL_TEXTURE_2D,i,internalformat,width,height,0,p_format,GL_UNSIGNED_BYTE,0);
		width=width>>1;
		height=height>>1;
		if (width<1) width=1;
		if (height<1) height=1;
		i++;
	}
	functions.TexImage2D(GL_TEXTURE_2D,i,internalformat,width,height,0,p_format,GL_UNSIGNED_BYTE,0);
}

void Texture2D::setFormat(unsigned int format)
{
	p_format=format;
}

void Texture2D::setRaster(Raster *raster)
{
	if ((raster==0) || p_raster==raster) return;
	//p_width=raster->width;
	//p_height=raster->height;
	p_raster=raster;
	p_format=Render::formatFromBPP(raster->bpp,p_format);
	setSize(raster->width,raster->height);
}

gen::Raster *Texture2D::getRaster()
{
	return p_raster;
}

void Texture2D::fullUpdate()
{
	p_context=0;
}

void Texture2D::updateRect(bt::vector4i *r,Raster *raster)
{
	sFunctionsGLContext &functions=GlContext::getCurrent()->functions();
	bind();
	Render::setFilterMode(magFilter(p_filter),minFilter(p_filter));
	Render::setMipMap(mm_min,mm_max);
	void *data=0;
	if (raster) data=raster->data;
	int x=r->x;
	int y=r->y;
	int width=raster->width;
	int height=raster->height;

	int i=0;
	void *dhalf=0;
	if (data) dhalf = extFunctions.CreateMem(r->z*r->w*raster->bpp,0);
	int max=mm_max;
	int min=mm_min;
	unsigned int format=Render::formatFromBPP(raster->bpp,p_format);
	while ((width>1) || (height>1)) {
		if ((min<=i) && (i<=max)) {
			functions.TexSubImage2D(GL_TEXTURE_2D,i,x,y,width,height,format,GL_UNSIGNED_BYTE,data);
		}
		if ((data) && (i<max)) half(dhalf,data,width,height,raster->bpp);
		width=width>>1;
		height=height>>1;
		x=x>>1;
		y=y>>1;
		if (width<1) width=1;
		if (height<1) height=1;
		i++;
		if (data) data=dhalf;
	}
	if ((min<=i) && (i<=max)) {
		functions.TexSubImage2D(GL_TEXTURE_2D,i,0,0,1,1,format,GL_UNSIGNED_BYTE,data);
	}
	if (data) extFunctions.DeleteMem(dhalf,0);
}

void Texture2D::setMipMap(int min,int max)
{
	mm_min=min;
	mm_max=max;
	p_context=0;
	//if (!p_texture) return;
	//Render::BindTexture2D(p_texture);
	//Render::setMipMap(min,max);
}

void Texture2D::setWrapMode(int ,int )
{

}

void Texture2D::setFilterMode(int mag,int min)
{
	//Render::BindTexture2D(p_texture);
	//Render::setFilterMode(mag,min);
	p_filter=(mag<<8)+min;
}

void Texture2D::setFilter(unsigned int filter)
{
	//Render::BindTexture2D(p_texture);
	//Render::setFilterMode(mag,min);
	p_filter=filter;
}

void Texture2D::load(char*name)
{
	System::system().getIDS().loadRasterToTexture2D(name,this);
}

void Texture2D::bind()
{
	GlContext*current=GlContext::getCurrent();
	sFunctionsGLContext &functions=current->functions();
	GLboolean isEnable;
	functions.GetBooleanv(GL_TEXTURE_2D,&isEnable);
	if (!isEnable) functions.Enable(GL_TEXTURE_2D);
	if (p_context!=current) p_texture=setContext(current);
	current->bindTexture2D(p_texture);
}

const char *Texture2D::getName()
{
	return Graph::graph().p_texture->getName(this);
}

void *Texture2D::set(unsigned _int32 id,void * param)
{
	if (id==BaseObject::TYPE) return Texture2D::t();
	if (id==BaseObject::WRITE) {
		Variant *p;
		Variant *pa;
		ParametersList &list=*(ParametersList *)param;
		if ((p=list.find("format"))!=0) setFormat(getFormatByName(p->getString()));
		if ((p=list.find("filter"))!=0) setFilter(getFilterByName(p->getString()));
		if (((p=list.find("width"))!=0) && ((pa=list.find("height"))!=0)) {
			setSize(p->getInt(),pa->getInt()); //resize only after activate context!!!
		}
		if (((p=list.find(STR_MIN))!=0) && ((pa=list.find(STR_MAX))!=0)) {
			setMipMap(p->getInt(),pa->getInt());
		}
		if ((p=list.find(STR_FILE))!=0) {
			load(p->getString());
		}
	}
	if (id==BaseObject::READ) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		p=&list["format"];
		//p->setString(p_format);
		p=&list["filter"];
		p->setString(getFilterName(p_filter));
		p=&list["width"];
		p->setInt(p_width);
		p=&list["height"];
		p->setInt(p_height);
		p=&list[STR_MIN];
		p->setInt(mm_min);
		p=&list[STR_MAX];
		p->setInt(mm_max);
	}
	return 0;
}

void Texture2D::half(void *half,void *data,int w, int h,int bpp)
{
	if (bpp==1) {
		char *d=(char *)data;
		char *r=(char *)half;
		for (int y=0;y<h>>1;y++) {
			for (int x=0;x<w;x+=2) {
				int c=matFunctions.FTrunc((d[x]+d[x+1]+d[x+w]+d[x+w+1])*0.25f);
				*r=c;
				r++;
			}
			d+=w*2;
		}
	}
	if (bpp==3) {
		char *d=(char *)data;
		char *r=(char *)half;
		int wb=(w<<1)+w;
		vector3f v1;
		vector3f v2;
		vector3f v3;
		vector3f v4;
		for (int y=0;y<(h>>1);y++) {
			for (int x=0;x<w;x+=2) {
				int xp=((x<<1)+x);
				renFunctions.V3BHalfTexel(r,&d[xp],wb);
				r+=3;
			}
			d+=w*2*3;
		}
	}
	if (bpp==4) {
		int *d=(int *)data;
		int *r=(int *)half;
		int wb=(w<<2);
		vector4f v1;
		vector4f v2;
		vector4f v3;
		vector4f v4;
		for (int y=0;y<h>>1;y++) {
			for (int x=0;x<w;x+=2) {
				renFunctions.V4BHalfTexel(r,&d[x],wb);
				r++;
			}
			d+=w*2;
		}
	}
}

void Texture2D::update()
{
	GlContext*current=GlContext::getCurrent();
	sFunctionsGLContext &functions=current->functions();

	bind();
	Render::setFilterMode(magFilter(p_filter),minFilter(p_filter));
	Render::setMipMap(mm_min,mm_max);

	void *data=0;
	if (p_raster) data=p_raster->data;
	int width=p_width;
	int height=p_height;

	int i=0;
	void *dhalf=0;
	if (data) dhalf = extFunctions.CreateMem(p_raster->height*p_raster->width*p_raster->bpp,0);
	int max=mm_max;
	int min=mm_min;
	while ((width>1) || (height>1)) {
		if ((min<=i) && (i<=max)) {
			functions.TexSubImage2D(GL_TEXTURE_2D,i,0,0,width,height,p_format,GL_UNSIGNED_BYTE,data);
		}
		if ((data) && (i<max)) half(dhalf,data,width,height,p_raster->bpp);
		width=width>>1;
		height=height>>1;
		if (width<1) width=1;
		if (height<1) height=1;
		i++;
		if (data) data=dhalf;
	}
	if ((min<=i) && (i<=max)) {
		functions.TexSubImage2D(GL_TEXTURE_2D,i,0,0,1,1,p_format,GL_UNSIGNED_BYTE,data);
	}
	if (data) extFunctions.DeleteMem(dhalf,0);

}

unsigned int Texture2D::getFormatByName(char *name)
{
	if (fmemcmp(name,(void*)"RGBA",5)==-1) {
		return GL_RGBA;
	}
	if (fmemcmp(name,(void*)"LUMINANCE",10)==-1) {
		return GL_LUMINANCE;
	}
	if (fmemcmp(name,(void*)"ALPHA",6)==-1) {
		return GL_ALPHA;
	}
	return GL_RGB;
}

unsigned int Texture2D::getFilterByName(char *name)
{
	btFunctions.InitFunc(0xFFFFFFFF);
	int i=0;
	while (i<5) {
		if (fmemcmp(name,textureFilterNameList[i]+1,*textureFilterNameList[i])==-1) return textureFilterValList[i];
		i++;
	}
	return 0;
}

const char * Texture2D::getFilterName(unsigned int val)
{
	int i=0;
	while (i<5) {
		if (val==textureFilterValList[i]) return textureFilterNameList[0]+1;
		i++;
	}
	return 0;
}

int Texture2D::magFilter(int filter)
{
	int mag=filter>>8;
	if (mag==0) {
		mag=GL_NEAREST;
	} else if (mag==1) {
		mag=GL_LINEAR;
	} else mag=0;
	return mag;
}

int Texture2D::minFilter(int filter)
{
	int min=filter & 0xF;
	if (min>5) min=0;
	return textureFilterMinList[min];
}

/*void Texture2D::loadTGA(unsigned int format,char*name)
{
	FormatTGA TGA;
	if (!TGA.readFromFile(name)) return;

	// need convert imageMatrix to format mode

	setTexture(format,TGA.width(),TGA.height(),TGA.imgMatrix());
}*/

TYPEINFO(Texture2D)

}

OPTIMIZE_OFF;
