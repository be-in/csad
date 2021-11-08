/*
 * fonttext.cpp
 *
 *  Created on: 28.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/fonttext.h>
#include <core/graph.h>
#include <scene/texture2d.h>

OPTIMIZE_ON;

namespace csad {

using namespace bt;

FontText::FontText(FontServer *server, char *name):Font(server,name)
{
	ftexture=csad::Graph::graph().createTexture2D(name);
	isBuild=false;
	raster.data=0;
}

FontText::FontText(FontServer *server, const char *name):Font(server,name)
{
	ftexture=csad::Graph::graph().createTexture2D(name);
	isBuild=false;
	raster.data=0;
}

FontText::~FontText()
{
	if (raster.data) extFunctions.DeleteMem(raster.data,0);
	raster.data=0;
	ftexture=0;
}

/*void FontText::setPixels(int size)
{
	fpixels=size;
}*/

float FontText::width(unsigned _int32 simvol)
{
	if (simvol>255) return 0;
	if (!isBuild) build();
	return (float)sizes[simvol];
}

float FontText::height()
{
	if (!isBuild) build();
	return Font::height();
}

void FontText::setSize(int size)
{
	Font::setSize(size);
	isBuild=false;
}

float FontText::addOutLine(int x,int y,unsigned _int32 simvol, GeometryPath2I *path)
{
	if (!isBuild) build();
	if (simvol>255) return 0;
	if (simvol==32) return sizes[simvol];
	GeometryPath<vector2i> *tpath=(GeometryPath<vector2i> *)path;
	vector2i p;
	int size=getSize();
	p.x=x;
	p.y=y;
	tpath->addVector(p,true);
	p.x=x;
	p.y=y+size;
	tpath->addVector(p,false);
	p.x=x+size;
	p.y=y+size;
	tpath->addVector(p,false);
	p.x=x+size;
	p.y=y;
	tpath->addVector(p,false);
	return sizes[simvol];
}

void *FontText::set(unsigned _int32 id,void*param)
{
	if (id==BaseObject::TYPE) return FontText::t();
	return Font::set(id,param);
}

void FontText::build()
{
	if (isBuild) return;
	int size=Font::getSize();
	gen::ModellerRaster modeller;
	gen::Raster gliph;
	modeller.setRaster(&raster);
	raster.bpp=1;
	raster.width=size*16;
	raster.height=size*16;

	int glbuffsize=size*size*raster.bpp;

	gliph.bpp=raster.bpp;
	gliph.width=size;
	gliph.height=size;
	gliph.data = extFunctions.CreateMem(glbuffsize,0);

	modeller.setMode(gen::ModellerRaster::ALPHA);
	if (raster.data) extFunctions.DeleteMem(raster.data,0);
	raster.data=extFunctions.CreateMem(raster.width*raster.height*raster.bpp,0);
	extFunctions.StocBMem(raster.data,raster.width*raster.height*raster.bpp,0);
	modeller.setFont(this);
	unsigned char c[2];
	c[0]=0;
	c[1]=0;
	gen::sGenerator gen;
	gen.mode=gen::ModellerRaster::NORMAL;
	for (int y=0;y<16;y++) {
		for (int x=0;x<16;x++) {
			//rasterText(&raster,x*size+1,y*size+1,0xFFFFFFFF,gen::ModellerRaster::OR,(char*)c);
			extFunctions.CleanMem(gliph.data,glbuffsize);
			rasterText(&gliph,1,1,0xFFFFFFFF,gen::ModellerRaster::NORMAL,(char*)c);
			genFunctions.SetGenerator(&gen);
			genFunctions.RasterMix(&raster,&gliph,x*size,y*size,0xFF);
			//gen::ModellerRaster::mix(&raster,&gliph,x*size,y*size,gen::ModellerRaster::NORMAL,0xFF);
			sizes[c[0]] = matFunctions.FTrunc(Font::width(c[0]));
			c[0]++;
		}
	}

	ftexture->setFormat(GL_ALPHA); //GL_LUMINANCE
	//ftexture->setFilter(0x001);
	//ftexture->setFilter(0x103);
	//ftexture->setFilter(0x101);
	//ftexture->setMipMap(0,0);
	ftexture->setRaster(&raster);
	isBuild=true;
	extFunctions.DeleteMem(gliph.data,0);
}

TYPEINFO(FontText)

}

OPTIMIZE_OFF;
