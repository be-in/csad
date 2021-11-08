/*
 * modellerpath.cpp
 *
 *  Created on: 17.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <gen3.h>
#include <bt.h>

OPTIMIZE_ON;

namespace gen {

GeometryPath2I::GeometryPath2I()
{
	arrFunctions.ANTInit(&p_pointers,sizeof(vector2i),0);
	arrFunctions.ANTInit(&p_count,sizeof(_int32),0);
}

GeometryPath2I::GeometryPath2I(GeometryPath2F &path)
{
	GeometryPath<vector2i> *tpath=(GeometryPath<vector2i> *)&path;
	arrFunctions.ANTInit(&p_pointers,sizeof(vector2i),tpath->poligonSize().count());
	arrFunctions.ANTInit(&p_count,sizeof(_int32),tpath->vectors().count());

	extFunctions.MoveMem(tpath->poligonSize().data(),p_count.Vals,tpath->poligonSize().count());
	arvFunctions.A2FTo2I(tpath->vectors().data(),p_pointers.Vals,tpath->vectors().sizeOfType(),p_pointers.ItSize,tpath->vectors().count());
}

GeometryPath2I::~GeometryPath2I()
{
	arrFunctions.ANTFree(&p_pointers);
	arrFunctions.ANTFree(&p_count);
}

void GeometryPath2I::absorb(sArray *pointers,sArray *counts)
{
	p_pointers.Count=pointers->Count;
	p_count.Count=counts->Count;
	p_pointers.AllCount=pointers->AllCount;
	p_count.AllCount=counts->AllCount;
	p_pointers.Vals=pointers->Vals;
	p_count.Vals=counts->Vals;
}

GeometryPath2F::GeometryPath2F()
{
	arrFunctions.ANTInit(&p_pointers,sizeof(vector2f),0);
	arrFunctions.ANTInit(&p_count,sizeof(_int32),0);
}

GeometryPath2F::GeometryPath2F(GeometryPath2I &path)
{
	GeometryPath<vector2f> *tpath=(GeometryPath<vector2f> *)&path;
	arrFunctions.ANTInit(&p_pointers,sizeof(vector2f),tpath->poligonSize().count());
	arrFunctions.ANTInit(&p_count,sizeof(_int32),tpath->vectors().count());
	extFunctions.MoveMem(tpath->poligonSize().data(),p_count.Vals,tpath->poligonSize().count());
	arvFunctions.A2ITo2F(tpath->vectors().data(),p_pointers.Vals,tpath->vectors().sizeOfType(),p_pointers.ItSize,tpath->vectors().count());
}

GeometryPath2F::~GeometryPath2F()
{
	arrFunctions.ANTFree(&p_pointers);
	arrFunctions.ANTFree(&p_count);
}

void GeometryPath2F::absorb(sArray *pointers,sArray *counts)
{
	p_pointers.Count=pointers->Count;
	p_count.Count=counts->Count;
	p_pointers.AllCount=pointers->AllCount;
	p_count.AllCount=counts->AllCount;
	p_pointers.Vals=pointers->Vals;
	p_count.Vals=counts->Vals;
}

void GeometryPath2F::addBox(float width,float height,vector2f &offset,float deg)
{
	int firstindex=p_pointers.Count;
	arrFunctions.ANTResize(&p_pointers,firstindex+5);
	GeometryPath<vector2f> *tpath=(GeometryPath<vector2f> *)this;
	Vector<vector2f>& vectors=tpath->vectors();
	vector2f vr1;
	vector2f vr2;
	float mdeg1=deg;
	if (mdeg1>PI) mdeg1-=(float)(2*PI);
	float mdeg2=(float)(mdeg1+0.5*PI);
	if (mdeg2>PI) mdeg2-=(float)(2*PI);
	width=width*0.5f;
	height=height*0.5f;
	matFunctions.FSinCos(mdeg1,&vr1.x,&vr1.y);
	matFunctions.FSinCos(mdeg2,&vr2.x,&vr2.y);
	vr1=vr1*width;
	vr2=vr2*height;
	
	vectors[firstindex]=offset+vr1+vr2;
	vectors[firstindex+1]=offset+vr1-vr2;
	vectors[firstindex+2]=offset-vr1-vr2;
	vectors[firstindex+3]=offset-vr1+vr2;
	vectors[firstindex+4]=offset+vr1+vr2;
	tpath->poligonSize().assign(5);
}

void GeometryPath2F::addCircle(float radius,int cells,float from,float to,vector2f &offset)
{
	int count=cells;
	GeometryPath<vector2f> *tpath=(GeometryPath<vector2f> *)this;
	Vector<vector2f>& vectors=tpath->vectors();
	int firstindex=vectors.size();
	vectors.resize(firstindex+count);
	vector2f vr;
	vector2f vfg;
	if (from<0.0) from=0.0f;
	if (to==0.0) to=1.0f;
	if (to>1.0) to=1.0f;
	to-=from;
	float deg=(float)(to*2.0*PI/cells);
	float grad=(float)(from*2.0*PI-PI);
	matFunctions.FSinCos(grad,&vr.x,&vr.y);
	matFunctions.FSinCos(deg,&vfg.x,&vfg.y);
	for (int i=0;i<cells;i++) {	
		vectors[firstindex+i]=offset+vr*radius;
		vecFunctions.V2FAfineTransform(&vr,&vfg,&vr);
	}
	tpath->poligonSize().assign(cells);
}

void GeometryPath2F::addStrokedCircle(float radius,float width,int cells,float from,float to,vector2f &offset)
{
	int count=(cells+1)*2;
	GeometryPath<vector2f> *tpath=(GeometryPath<vector2f> *)this;
	Vector<vector2f>& vectors=tpath->vectors();
	int firstindex=vectors.size();
	vector2f vr;
	vector2f vfg;
	if (from<0.0f) from=0.0f;
	to-=from;
	if ((to<=0.0f) || (to>1.0f)) to=1.0f;
	bool tow=to==1.0f;
	if (tow) {
		vectors.resize(firstindex+count);
	} else {
		vectors.resize(firstindex+count+1);
	}
	float low=radius-width*0.5f;
	float hi=radius+width*0.5f;
	float deg=(float)(to*2.0*PI/cells);
	float grad=(float)(from*2.0*PI-PI);
	matFunctions.FSinCos(grad,&vr.x,&vr.y);
	matFunctions.FSinCos(deg,&vfg.x,&vfg.y);
	if (!tow) {
		vectors[firstindex+count]=offset+vr*low;
		cells++;
	}
	if (tow) {
		vectors[firstindex+cells]=offset+vr*low;
		vectors[firstindex+cells+1]=offset+vr*hi;
	}
	for (int i=0;i<cells;i++) {
		vectors[firstindex+i]=offset+vr*low;
		vectors[firstindex+count-i-1]=offset+vr*hi;
		vecFunctions.V2FAfineTransform(&vr,&vfg,&vr);
	}
	if (!tow) tpath->poligonSize().assign(count+1);
	if (tow) {
		tpath->poligonSize().assign(cells+1);
		tpath->poligonSize().assign(cells+1);
	}
}

}

OPTIMIZE_OFF;