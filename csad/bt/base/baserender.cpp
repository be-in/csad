//=============================================================================
///**
// *  @file baserender.cpp
// *
// *  $Id: baserender.cpp 23.05.2012  $
// *
// *  @brief generator 3, MS Visual C++ 2003-2008
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#include "baserender.h"
#include "baseext.h"
#include <bt.h>

OPTIMIZE_ON;

namespace bt {

union conv4b {
	float valfloat;
	_int32 valint;
	unsigned _int32 valuint;
	char valarray[4];
};

void _TriangleSort(V4AFdata**data) {
	V4AFdata* t;
	if (data[0]->v[1]>data[1]->v[1]) {
		t=data[0];
		data[0]=data[1];
		data[1]=t;
	}
	if (data[1]->v[1]>data[2]->v[1]) {
		t=data[1];
		data[1]=data[2];
		data[2]=t;
	}
	if (data[0]->v[1]>data[1]->v[1]) {
		t=data[0];
		data[0]=data[1];
		data[1]=t;
	}
}

void _APICALL _V3BHalfTexelDEF(void *rez,void *offs,_int32 bwidth)
{
	unsigned char *od=(unsigned char*)offs;
	unsigned char *ort=(unsigned char*)rez;
	ort[0]=(unsigned char)((unsigned _int32)(od[3]+od[0]+od[bwidth+3]+od[bwidth])>>2);
	ort[1]=(unsigned char)((unsigned _int32)(od[4]+od[1]+od[bwidth+4]+od[bwidth+1])>>2);
	ort[2]=(unsigned char)((unsigned _int32)(od[5]+od[2]+od[bwidth+5]+od[bwidth+2])>>2);
}

void _APICALL _V4BHalfTexelDEF(void *rez,void *offs,_int32 bwidth)
{
	unsigned char *od=(unsigned char*)offs;
	unsigned char *ort=(unsigned char*)rez;
	ort[0]=(unsigned char)((unsigned _int32)(od[4]+od[0]+od[bwidth+4]+od[bwidth])>>2);
	ort[1]=(unsigned char)((unsigned _int32)(od[5]+od[1]+od[bwidth+5]+od[bwidth+1])>>2);
	ort[2]=(unsigned char)((unsigned _int32)(od[6]+od[2]+od[bwidth+6]+od[bwidth+2])>>2);
	ort[3]=(unsigned char)((unsigned _int32)(od[7]+od[3]+od[bwidth+7]+od[bwidth+3])>>2);
}

void _APICALL _V3BTexelDEF(void *rez,void *offs,_int32 bwidth,float x,float y)
{
	unsigned char *od=(unsigned char*)offs;
	unsigned char *ort=(unsigned char*)rez;
	float id0=x;
	float id1=y;
	float r1=(od[3]-od[0])*id0+od[0];
	float r2=(od[4]-od[1])*id0+od[1];
	float r3=(od[5]-od[2])*id0+od[2];
	float t1=(od[bwidth+3]-od[bwidth+0])*id0+od[bwidth+0];
	float t2=(od[bwidth+4]-od[bwidth+1])*id0+od[bwidth+1];
	float t3=(od[bwidth+5]-od[bwidth+2])*id0+od[bwidth+2];
	ort[0]=(unsigned char)((t1-r1)*id1+r1);
	ort[1]=(unsigned char)((t2-r2)*id1+r2);
	ort[2]=(unsigned char)((t3-r3)*id1+r3);
}

void _APICALL _V4BTexelDEF(void *rez,void *offs,_int32 bwidth,float x,float y)
{
	unsigned char *od=(unsigned char*)offs;
	unsigned char *ort=(unsigned char*)rez;
	float id0=(1.0f-y);
	float id2=(1.0f-x);
	float id1=id0*x;
	float id3=x*y;
	id0*=id2;
	id2*=y;
	ort[0]=(unsigned char)(od[0]*id0+od[4]*id1+od[bwidth]*id2+od[bwidth+4]*id3);
	ort[1]=(unsigned char)(od[1]*id0+od[5]*id1+od[bwidth+1]*id2+od[bwidth+5]*id3);
	ort[2]=(unsigned char)(od[2]*id0+od[6]*id1+od[bwidth+2]*id2+od[bwidth+6]*id3);
	ort[3]=(unsigned char)(od[3]*id0+od[7]*id1+od[bwidth+3]*id2+od[bwidth+7]*id3);
}

void _APICALL _S4AFdrawDEF(void *data)
{
	_StocIMemDEF(((S4AFdata*)data)->mem,((S4AFdata*)data)->count,((S4AFdata*)data)->color);
}

void _APICALL _S4AFDLdrawDEF(void *data)
{
	while (((S4AFDdata*)data)->count) {
		unsigned short s=(unsigned short)(((S4AFDdata*)data)->z>>15);
		if ((*(unsigned short*)((S4AFDdata*)data)->depth) > s) {
			*(_int32*)((S4AFDdata*)data)->mem=((S4AFDdata*)data)->color;
			*(unsigned short*)((S4AFDdata*)data)->depth=s;
		}
		((S4AFDdata*)data)->z+=((S4AFDdata*)data)->za;
		((S4AFDdata*)data)->mem+=4;
		((S4AFDdata*)data)->depth+=2;
		((S4AFDdata*)data)->count--;
	}
}

void _APICALL _S4AFSdrawDEF(void *data)
{
	if (((S4AFDSdata*)data)->cscale==0.00390625) {
		while (((S4AFDSdata*)data)->count) {
			((S4AFDSdata*)data)->color=0xFFFFFFFF;
			if (((S4AFDSdata*)data)->color3<=65535) ((unsigned char*)&((S4AFDSdata*)data)->color)[3]=(unsigned char)(((S4AFDSdata*)data)->color3>>8);
			if (((S4AFDSdata*)data)->color2<=65535) ((unsigned char*)&((S4AFDSdata*)data)->color)[2]=(unsigned char)(((S4AFDSdata*)data)->color2>>8);
			if (((S4AFDSdata*)data)->color1<=65535) ((unsigned char*)&((S4AFDSdata*)data)->color)[1]=(unsigned char)(((S4AFDSdata*)data)->color1>>8);
			if (((S4AFDSdata*)data)->color0<=65535) ((unsigned char*)&((S4AFDSdata*)data)->color)[0]=(unsigned char)(((S4AFDSdata*)data)->color0>>8);
			*(_int32*)((S4AFDSdata*)data)->mem=((S4AFDSdata*)data)->color;

			((S4AFDSdata*)data)->color3+=((S4AFDSdata*)data)->color3step;
			((S4AFDSdata*)data)->color2+=((S4AFDSdata*)data)->color2step;
			((S4AFDSdata*)data)->color1+=((S4AFDSdata*)data)->color1step;
			((S4AFDSdata*)data)->color0+=((S4AFDSdata*)data)->color0step;
			((S4AFDSdata*)data)->mem+=4;
			((S4AFDSdata*)data)->count--;
		}
		return;
	}
	float max=255.0f/((S4AFDSdata*)data)->cscale;
	float cs=((S4AFDSdata*)data)->cscale;
	while (((S4AFDSdata*)data)->count) {
		((S4AFDSdata*)data)->color=0xFFFFFFFF;
		if (((S4AFDSdata*)data)->color3<=max) ((unsigned char*)&((S4AFDSdata*)data)->color)[3]=(unsigned char)(((S4AFDSdata*)data)->color3*cs);
		if (((S4AFDSdata*)data)->color2<=max) ((unsigned char*)&((S4AFDSdata*)data)->color)[2]=(unsigned char)(((S4AFDSdata*)data)->color2*cs);
		if (((S4AFDSdata*)data)->color1<=max) ((unsigned char*)&((S4AFDSdata*)data)->color)[1]=(unsigned char)(((S4AFDSdata*)data)->color1*cs);
		if (((S4AFDSdata*)data)->color0<=max) ((unsigned char*)&((S4AFDSdata*)data)->color)[0]=(unsigned char)(((S4AFDSdata*)data)->color0*cs);
		*(_int32*)((S4AFDSdata*)data)->mem=((S4AFDSdata*)data)->color;

		((S4AFDSdata*)data)->color3+=((S4AFDSdata*)data)->color3step;
		((S4AFDSdata*)data)->color2+=((S4AFDSdata*)data)->color2step;
		((S4AFDSdata*)data)->color1+=((S4AFDSdata*)data)->color1step;
		((S4AFDSdata*)data)->color0+=((S4AFDSdata*)data)->color0step;
		((S4AFDSdata*)data)->mem+=4;
		((S4AFDSdata*)data)->count--;
	}
}

void _APICALL _S4AFDLSdrawDEF(void *data)
{
	while (((S4AFDSdata*)data)->count) {
		unsigned short s=(unsigned short)(((S4AFDSdata*)data)->z>>15);
		if ((*(unsigned short*)((S4AFDSdata*)data)->depth) > s) {
			((S4AFDSdata*)data)->color=0xFFFFFFFF;
			if (((S4AFDSdata*)data)->color3<=65535) ((unsigned char*)&((S4AFDSdata*)data)->color)[3]=(unsigned char)(((S4AFDSdata*)data)->color3>>8);
			if (((S4AFDSdata*)data)->color2<=65535) ((unsigned char*)&((S4AFDSdata*)data)->color)[2]=(unsigned char)(((S4AFDSdata*)data)->color2>>8);
			if (((S4AFDSdata*)data)->color1<=65535) ((unsigned char*)&((S4AFDSdata*)data)->color)[1]=(unsigned char)(((S4AFDSdata*)data)->color1>>8);
			if (((S4AFDSdata*)data)->color0<=65535) ((unsigned char*)&((S4AFDSdata*)data)->color)[0]=(unsigned char)(((S4AFDSdata*)data)->color0>>8);
			*(_int32*)((S4AFDSdata*)data)->mem=((S4AFDSdata*)data)->color;
			*(unsigned short*)((S4AFDSdata*)data)->depth=s;
		}
		((S4AFDSdata*)data)->color3+=((S4AFDSdata*)data)->color3step;
		((S4AFDSdata*)data)->color2+=((S4AFDSdata*)data)->color2step;
		((S4AFDSdata*)data)->color1+=((S4AFDSdata*)data)->color1step;
		((S4AFDSdata*)data)->color0+=((S4AFDSdata*)data)->color0step;
		((S4AFDSdata*)data)->z+=((S4AFDSdata*)data)->za;
		((S4AFDSdata*)data)->mem+=4;
		((S4AFDSdata*)data)->depth+=2;
		((S4AFDSdata*)data)->count--;
	}
}

struct point_loop {
	float px;
	float py;
	_int32 rect[4];
	char *end;
	char *buff;
	char *startmem;
	char* loopsize;
	_int32 stride;
};

void VTC_pointMemCC(V4AFdata *vertex,point_loop *loop,float radius)
{
	int r=matFunctions.FTrunc(radius);
	loop->px=vertex->v[0];
	loop->py=vertex->v[1];
	float ar[4];
	ar[0] = loop->px;
	ar[1] = loop->py;
	ar[2] = (float)(loop->rect[0] + r + 1);
	ar[3] = (float)(loop->rect[3] + r);
	vecFunctions.V4FTTo4I(ar, loop->rect);
	loop->px=loop->rect[0]-loop->px-r;
	loop->py=loop->rect[1]-loop->py-r;
	loop->rect[0]-=r;
	loop->rect[1]-=r;
}

void _APICALL _P4AFdrawDEF(V4AFdata *vertex,T4AFdata *data,float radius)
{
	point_loop loop;
	VTC_pointMemCC(vertex,&loop,radius);
	loop.stride=data->stride;
	loop.buff=(char*)data->mem;
	loop.end=loop.buff+data->size;
	loop.startmem=loop.buff+loop.rect[1]*loop.stride;
	loop.loopsize=loop.startmem+(((matFunctions.FTrunc(radius))<<1)+2)*loop.stride;
	int t0=data->left>>2;
	if (loop.rect[0]<t0) {
		loop.px+=t0-loop.rect[0];
		loop.rect[0]=t0;
	}
	loop.rect[0]<<=2;
	loop.rect[2]<<=2;
	if (loop.rect[2]>data->right) loop.rect[2]=data->right;
	_int32 color;
	vecFunctions.V4FTo4B(vertex->c,&color);
	int rr = matFunctions.FTrunc(radius*radius);
	float yp=loop.py;
	while (loop.startmem<loop.loopsize) {
		float ry=yp*yp-rr;
		if ((loop.startmem>=loop.buff) && (loop.startmem<loop.end)) {
			char *endpoint=loop.startmem+(loop.rect[2]);
			char *point=loop.startmem+(loop.rect[0]);
			float xp=loop.px;
			while ((_voidint)point<=(_voidint)endpoint) {
				float alpha=(xp*xp+ry);
				if (alpha<=0.0) *(_int32*)point=color;
				point+=4;
				xp+=1.0;
			}
		}
		yp+=1.0;
		loop.startmem+=loop.stride;
	}
}

void _APICALL _P4AFdrawAADEF(V4AFdata *vertex,T4AFdata *data,float radius)
{
	point_loop loop;
	VTC_pointMemCC(vertex,&loop,radius);
	int stride=data->stride;
	char *buff=(char*)data->mem;
	char *end=buff+data->size;
	char *startmem=buff+loop.rect[1]*stride;
	char* loopsize = startmem + (((matFunctions.FTrunc(radius)) << 1) + 2)*stride;
	int t0=data->left>>2;
	if (loop.rect[0]<t0) {
		loop.px+=t0-loop.rect[0];
		loop.rect[0]=t0;
	}
	loop.rect[0]<<=2;
	loop.rect[2]<<=2;
	if (loop.rect[2]>data->right) loop.rect[2]=data->right;
	int color;
	vecFunctions.V4FTo4B(vertex->c,&color);
	int rr = matFunctions.FTrunc(radius*radius);
	int maxrr = matFunctions.FTrunc((radius + 1)*(radius + 1) - rr);
	float invmr=1.0f/maxrr;
	float yp=loop.py;
	while (startmem<loopsize) {
		float ry=yp*yp-rr;
		if ((startmem>=buff) && (startmem<end)) {
			char *endpoint=startmem+(loop.rect[2]);
			char *point=startmem+(loop.rect[0]);
			float xp=loop.px;
			while ((_voidint)point<=(_voidint)endpoint) {
				float alpha=(xp*xp+ry);
				if (alpha<=0) {
					*(int*)point=color;
				} else if (alpha<maxrr) {
					conv4b vb;
					vb.valfloat=alpha*invmr;
					vb.valint=(vb.valint>>1)+0x1fb504f3;
					alpha=vb.valfloat;
					float inval=(1.0f-alpha);
					/*float r=((unsigned char*)point)[0]*alpha+(color&0xFF)*inval;
					float g=((unsigned char*)point)[1]*alpha+((color>>8)&0xFF)*inval;
					float b=((unsigned char*)point)[2]*alpha+((color>>16)&0xFF)*inval;
					((unsigned char*)point)[0]=(unsigned char)r;
					((unsigned char*)point)[1]=(unsigned char)g;
					((unsigned char*)point)[2]=(unsigned char)b;*/
				}
				point+=4;
				xp+=1.0;
			}
		}
		yp+=1.0;
		startmem+=stride;
	}
}

void _APICALL _P4AFAdrawAADEF(V4AFdata *vertex,T4AFdata *data,float radius)
{
	point_loop loop;
	VTC_pointMemCC(vertex,&loop,radius);
	_int32 stride=data->stride;
	char *buff=(char*)data->mem;
	char *end=buff+data->size;
	char *startmem=buff+loop.rect[1]*stride;
	char* loopsize = startmem + (((matFunctions.FTrunc(radius)) << 1) + 2)*stride;
	int t0=data->left>>2;
	if (loop.rect[0]<t0) {
		loop.px+=t0-loop.rect[0];
		loop.rect[0]=t0;
	}
	loop.rect[0]<<=2;
	loop.rect[2]<<=2;
	if (loop.rect[2]>data->right) loop.rect[2]=data->right;
	unsigned int color;
	vecFunctions.V4FTo4B(vertex->c,&color);
	_int32 rr=matFunctions.FTrunc(radius*radius);
	_int32 maxrr = matFunctions.FTrunc((radius + 1)*(radius + 1) - rr);
	float invmr=1.0f/maxrr;
	float yp=loop.py;
	float calpha=(color>>24)*0.0039215686274509803921568627451f;
	while (startmem<loopsize) {
		float ry=yp*yp-rr;
		if ((startmem>=buff) && (startmem<end)) {
			char *endpoint=startmem+(loop.rect[2]);
			char *point=startmem+(loop.rect[0]);
			float xp=loop.px;
			while ((_voidint)point<=(_voidint)endpoint) {
				float alpha=(xp*xp+ry);
				if (alpha<maxrr) {
					if (alpha>0) {
						conv4b vb;
						vb.valfloat=alpha*invmr;
						vb.valint=(vb.valint>>1)+0x1fb504f3;
						alpha=(1.0f-vb.valfloat)*calpha;
					} else alpha=calpha;
					float inval=1.0f-alpha;
					/*float r=((unsigned char*)point)[0]*inval+(color&0xFF)*alpha;
					float g=((unsigned char*)point)[1]*inval+((color>>8)&0xFF)*alpha;
					float b=((unsigned char*)point)[2]*inval+((color>>16)&0xFF)*alpha;
					((unsigned char*)point)[0]=(unsigned char)r;
					((unsigned char*)point)[1]=(unsigned char)g;
					((unsigned char*)point)[2]=(unsigned char)b;*/
				}
				point+=4;
				xp+=1.0;
			}
		}
		yp+=1.0;
		startmem+=stride;
	}
}

struct tri_loop2 {
	_int32 count;
	_int32 color;
	char *mem;
	char *depth;
	_int32 z;
	_int32 za;
	float zscale;
	float cscale;
	_int32 colorr[4];
	_int32 cx[4];
 // add;
	_int32 loopsize;
	_int32 range;
	char *startmem;
	_int32 sad;
	_int32 cstart[4];
	_int32 cy[4];
	float reg1[3];
	float reg2[3];
	float reg3[3];
	float reg4[3];
};

void triangle_MonoColor_8888_loop2_deff(tri_loop2 *inf)
{
	_int32 t[2];
	while (inf->loopsize>0) {
		t[0] = matFunctions.FTrunc(-(inf->reg1[0] * inf->reg2[0]));
		t[1] = matFunctions.FTrunc(-(inf->reg1[1] * inf->reg2[1]));
		float inc1=(t[0]*inf->reg3[0]+inf->reg1[0]);
		float dec2=(t[1]*inf->reg3[1]+inf->reg1[1]);
		if (t[0]>t[1]) {
			_int32 yt=t[0];
			t[0]=t[1];
			t[1]=yt;
			float et=inc1;
			inc1=dec2;
			dec2=et;
		}
		if (t[0]<0) t[0]=0;
		if (t[1]>inf->range) t[1]=inf->range;
		if (inc1>0) t[0]++;
		if (dec2>0) t[1]--;
		inf->count=t[1]-t[0]+1;
		inf->mem=inf->startmem+(t[0]<<2);
		if (inf->count>0) renFunctions.S4AFdraw(inf);
		vecFunctions.V2FAdd(inf->reg1,inf->reg4,inf->reg1);
		inf->startmem+=inf->sad;
		inf->loopsize--;
	}
}

void triangle_MultyColor_8888_loop2_deff(tri_loop2 *inf)
{
	while (inf->loopsize>0) {
		_int32 t1=matFunctions.FTrunc(-(inf->reg1[0]*inf->reg2[0]));
		_int32 t2 = matFunctions.FTrunc(-(inf->reg1[1] * inf->reg2[1]));
		float inc1=(t1*inf->reg3[0]+inf->reg1[0]);
		float dec2=(t2*inf->reg3[1]+inf->reg1[1]);
		if (t1>t2) {
			_int32 yt=t1;
			t1=t2;
			t2=yt;
			float et=inc1;
			inc1=dec2;
			dec2=et;
		}
		if (t1<0) t1=0;
		if (t2>inf->range) t2=inf->range;
		if (inc1>0) t1++;
		if (dec2>0) t2--;
		vecFunctions.V4IScale(inf->cx,inf->colorr,(float)t1);
		vecFunctions.V4IAdd(inf->cstart,inf->colorr,inf->colorr);
		inf->count=t2-t1+1;
		inf->mem=inf->startmem+(t1<<2);
		if (inf->count>0) renFunctions.S4AFSdraw(inf);
		vecFunctions.V4IAdd(inf->cstart,inf->cy,inf->cstart);
		vecFunctions.V2FAdd(inf->reg1,inf->reg4,inf->reg1);
		inf->startmem+=inf->sad;
		inf->loopsize--;
	}
}

void middle_MonoColor_8888_loop2_deff(tri_loop2 *inf)
{
	if (inf->loopsize>0) {
		_int32 tv[3];
		float tvf[3];
		vecFunctions.V3FMul(inf->reg1, inf->reg2, tvf);
		vecFunctions.V3FInv(tvf, tvf);
		vecFunctions.V3FTTo3I(tvf, tv);
		if (tv[0]==tv[1]) tv[1]=tv[2];
		if (tv[0]>tv[1]) {
			_int32 yt=tv[0];
			tv[0]=tv[1];
			tv[1]=yt;
		}
		if (tv[0]<0) tv[0]=0;
		if (tv[1]>inf->range) tv[1]=inf->range;
		if ((tv[0]*inf->reg3[0]>-inf->reg1[0]) || (tv[0]*inf->reg3[1]>-inf->reg1[1]) || (tv[0]*inf->reg3[2]>-inf->reg1[2])) tv[0]++;
		if ((tv[1]*inf->reg3[0]>-inf->reg1[0]) || (tv[1]*inf->reg3[1]>-inf->reg1[1]) || (tv[1]*inf->reg3[2]>-inf->reg1[2])) tv[1]--;
		inf->count=tv[1]-tv[0]+1;
		inf->mem=inf->startmem+(tv[0]<<2);
		if (inf->count>0) renFunctions.S4AFdraw(inf);
		vecFunctions.V3FAdd(inf->reg1,inf->reg4,inf->reg1);
		inf->startmem+=inf->sad;
		inf->loopsize--;
	}
}

void middle_MultyColor_8888_loop2_deff(tri_loop2 *inf)
{
	if (inf->loopsize>0) {
		_int32 tv[3];
		float tvf[3];
		vecFunctions.V3FMul(inf->reg1, inf->reg2, tvf);
		vecFunctions.V3FInv(tvf, tvf);
		vecFunctions.V3FTTo3I(tvf, tv);
		if (tv[0] == tv[1]) tv[1] = tv[2];
		if (tv[0] > tv[1]) {
			_int32 yt = tv[0];
			tv[0] = tv[1];
			tv[1] = yt;
		}
		if (tv[0]<0) tv[0]=0;
		if (tv[1]>inf->range) tv[2]=inf->range;
		if ((tv[0]*inf->reg3[0]>-inf->reg1[0]) || (tv[0]*inf->reg3[1]>-inf->reg1[1]) || (tv[0]*inf->reg3[2]>-inf->reg1[2])) tv[0]++;
		if ((tv[1]*inf->reg3[0]>-inf->reg1[0]) || (tv[1]*inf->reg3[1]>-inf->reg1[1]) || (tv[1]*inf->reg3[2]>-inf->reg1[2])) tv[1]--;
		vecFunctions.V4IScale(inf->cx,inf->colorr,(float)tv[0]);
		vecFunctions.V4IAdd(inf->cstart,inf->colorr,inf->colorr);
		inf->count=tv[1]-tv[0]+1;
		inf->mem=inf->startmem+(tv[0]<<2);
		if (inf->count>0) renFunctions.S4AFSdraw(inf);
		vecFunctions.V4IAdd(inf->cstart,inf->cy,inf->cstart);
		vecFunctions.V3FAdd(inf->reg1,inf->reg4,inf->reg1);
		inf->startmem+=inf->sad;
		inf->loopsize--;
	}
}

void _calcplane(float*a,float*b,float*c)
{
	c[0]=b[1]-a[1];
	c[1]=a[0]-b[0];
	c[2]=-a[1]*c[1]-a[0]*c[0];
}

void _APICALL _L4AFdrawDEF(V4AFdata *vertexs,T4AFdata *data,float w)
{
	V4AFdata *t;
	V4AFdata *v1=vertexs;
	V4AFdata *v2=vertexs+1;

	if (v1->v[1]>v2->v[1]) {
		t=v2;
		v2=v1;
		v1=t;
	}

	V4AFdata v3r=*v1;
	V4AFdata v4r=*v2;
	V4AFdata *v3=&v3r;
	V4AFdata *v4=&v4r;
	vector2f n;
	vecFunctions.V2FSub(v1->v,v2->v,&n);
	float tr=n.x;
	n.x=-n.y;
	n.y=tr;
	n.normalize();
	n.scale(w*0.5f);
	vecFunctions.V2FSub(v1->v,&n,v1->v);
	vecFunctions.V2FAdd(v2->v,&n,v2->v);
	vecFunctions.V2FSub(v4->v,&n,v4->v);
	vecFunctions.V2FAdd(v3->v,&n,v3->v);

	if (n.y<0) {
		t=v1;
		v1=v3;
		v3=t;
		t=v2;
		v2=v4;
		v4=t;
	}

	if (v3->v[1]>v4->v[1]) {
		t=v3;
		v3=v4;
		v4=t;
	}
	tri_loop2 loop;

	int rv[3];
	float rvf[3] = { v1->v[0] + 0.5f, v2->v[0] + 0.5f, v3->v[0] + 0.5f };

	vecFunctions.V3FTTo3I(rvf,rv);
	//int r4=(_int32)(v4->v[0]+0.5f);
	int maxx=rv[0];
	int minx=rv[0];
	if (maxx<rv[1]) maxx=rv[1];
	if (minx>rv[1]) minx=rv[1];
	if (maxx<rv[2]) maxx=rv[2];
	if (minx>rv[2]) minx=rv[2];

	int maxy=matFunctions.FTrunc(v2->v[1]+0.5f);
	int miny = matFunctions.FTrunc(v1->v[1] + 0.5f);
	int midly1 = matFunctions.FTrunc(v3->v[1] + 0.5f);
	int midly2 = matFunctions.FTrunc(v4->v[1] + 0.5f);

	vecFunctions.V4FTo4B(v1->c,&loop.color);
	if (minx<0) minx=0;
	if (maxx>data->width-1) maxx=data->width-1;
	if (maxx<minx) maxx=minx;
	if (minx>maxx) minx=maxx;
	if (miny<0) miny=0;
	if (maxy>data->height-1) maxy=data->height-1;
	if (maxy<miny) maxy=miny;
	if (miny>maxy) miny=maxy;
	if (midly1<miny) midly1=miny;
	if (midly2<miny) midly1=miny;
	if (midly1>maxy) midly1=maxy;
	if (midly2>maxy) midly2=maxy;
	loop.startmem=(char*)data->mem+miny*data->stride+(minx<<2);
	loop.sad=data->stride;

	bool inv=false;
	if (vecFunctions.V2FQDFL(v1->v,v3->v,v4->v)>=0) {
		t=v3;
		v3=v4;
		v4=t;
		inv=true;
	}

	float vr1[3];
	_calcplane(v1->v,v3->v,vr1);
	float vr2[3];
	_calcplane(v3->v,v2->v,vr2);
	float vr3[3];
	_calcplane(v2->v,v4->v,vr3);
	float vr4[3];
	_calcplane(v4->v,v1->v,vr4);

	float v[2]={minx+0.5f,miny+0.5f};
	loop.reg1[0]=(vr1[2]+v[1]*vr1[1]+v[0]*vr1[0]);
	loop.reg1[1]=(vr4[2]+v[1]*vr4[1]+v[0]*vr4[0]);
	loop.reg2[0]=1.0f/vr1[0];
	loop.reg2[1]=1.0f/vr4[0];
	loop.reg3[0]=vr1[0];
	loop.reg3[1]=vr4[0];
	loop.reg4[0]=vr1[1];
	loop.reg4[1]=vr4[1];

	loop.range=maxx-minx;
	loop.loopsize=midly1-miny;
	triangle_MonoColor_8888_loop2_deff(&loop);
	if (!inv) {
		loop.reg1[0]=loop.reg1[1];
		loop.reg2[0]=loop.reg2[1];
		loop.reg3[0]=loop.reg3[1];
		loop.reg4[0]=loop.reg4[1];
		loop.reg1[1]=(vr2[2]+v[1]*vr2[1]+v[0]*vr2[0])+vr2[1]*(midly1-miny);
		loop.reg2[1]=1.0f/vr2[0];
		loop.reg3[1]=vr2[0];
		loop.reg4[1]=vr2[1];
	} else {
		loop.reg1[1]=(vr3[2]+v[1]*vr3[1]+v[0]*vr3[0])+vr3[1]*(midly1-miny);
		loop.reg2[1]=1.0f/vr3[0];
		loop.reg3[1]=vr3[0];
		loop.reg4[1]=vr3[1];
	}
	loop.loopsize=maxy-midly1;
	triangle_MonoColor_8888_loop2_deff(&loop);
	if (!inv) {
		loop.reg1[1]=loop.reg1[0];
		loop.reg2[1]=loop.reg2[0];
		loop.reg3[1]=loop.reg3[0];
		loop.reg4[1]=loop.reg4[0];
		loop.reg1[0]=(vr3[2]+v[1]*vr3[1]+v[0]*vr3[0])+vr3[1]*(midly2-miny);
		loop.reg2[0]=1.0f/vr3[0];
		loop.reg3[0]=vr3[0];
		loop.reg4[0]=vr3[1];
	} else {
		loop.reg1[0]=(vr2[2]+v[1]*vr2[1]+v[0]*vr2[0])+vr2[1]*(midly2-miny);
		loop.reg2[0]=1.0f/vr2[0];
		loop.reg3[0]=vr2[0];
		loop.reg4[0]=vr2[1];
	}

	loop.loopsize=maxy-midly2;
	triangle_MonoColor_8888_loop2_deff(&loop);
}

void _APICALL _T4AFdrawDEF(V4AFdata *vertexs,T4AFdata *data)
{
	V4AFdata *t;
	V4AFdata *vt[3]={vertexs,vertexs+1,vertexs+2};

	_TriangleSort(vt);
	tri_loop2 loop;

	int rv[3];
	float rvf[3] = { (vt[0]->v[0] + 0.5f), (vt[1]->v[0] + 0.5f), (vt[2]->v[0] + 0.5f) };

	vecFunctions.V3FTTo3I(rvf, rv);
	int maxx=rv[0];
	int minx = rv[0];
	if (maxx<rv[1]) maxx = rv[1];
	if (minx>rv[1]) minx = rv[1];
	if (maxx<rv[2]) maxx = rv[2];
	if (minx>rv[2]) minx = rv[2];

	int maxy=matFunctions.FTrunc(vt[2]->v[1]+0.5f);
	int miny = matFunctions.FTrunc(vt[0]->v[1] + 0.5f);
	int midly = matFunctions.FTrunc(vt[1]->v[1] + 0.5f);

	vecFunctions.V4FTo4B(vt[0]->c,&loop.color);
	if (minx<0) minx=0;
	if (maxx>data->width-1) maxx=data->width-1;
	if (maxx<minx) maxx=minx;
	if (minx>maxx) minx=maxx;
	if (miny<0) miny=0;
	if (maxy>data->height-1) maxy=data->height-1;
	if (maxy<miny) maxy=miny;
	if (miny>maxy) miny=maxy;
	if (midly<miny) midly=miny;
	if (midly>maxy) midly=maxy;
	loop.startmem=(char*)data->mem+miny*data->stride+(minx<<2);
	loop.sad=data->stride;

	bool inv=false;
	if (vecFunctions.V2FQDFL(vt[0]->v,vt[1]->v,vt[2]->v)>=0) {
		t=vt[1];
		vt[1]=vt[2];
		vt[2]=t;
		inv=true;
	}

	float vr1[3];
	_calcplane(vt[0]->v,vt[1]->v,vr1);
	float vr2[3];
	_calcplane(vt[1]->v,vt[2]->v,vr2);
	float vr3[3];
	_calcplane(vt[2]->v,vt[0]->v,vr3);

	float v[2]={minx+0.5f,miny+0.5f};
	loop.reg1[0]=(vr1[2]+v[1]*vr1[1]+v[0]*vr1[0]);
	loop.reg1[1]=(vr3[2]+v[1]*vr3[1]+v[0]*vr3[0]);
	loop.reg2[0]=1.0f/vr1[0];
	loop.reg2[1]=1.0f/vr3[0];
	loop.reg3[0]=vr1[0];
	loop.reg3[1]=vr3[0];
	loop.reg4[0]=vr1[1];
	loop.reg4[1]=vr3[1];

	loop.range=maxx-minx;
	loop.loopsize=midly-miny;
	triangle_MonoColor_8888_loop2_deff(&loop);
	if (!inv) {
		loop.reg1[0]=loop.reg1[1];
		loop.reg2[0]=loop.reg2[1];
		loop.reg3[0]=loop.reg3[1];
		loop.reg4[0]=loop.reg4[1];
	}
	loop.reg1[1]=(vr2[2]+v[1]*vr2[1]+v[0]*vr2[0])+vr2[1]*(midly-miny);
	loop.reg2[1]=1.0f/vr2[0];
	loop.reg3[1]=vr2[0];
	loop.reg4[1]=vr2[1];
	loop.loopsize=maxy-midly;
	triangle_MonoColor_8888_loop2_deff(&loop);
}

void _APICALL _T4AFSdrawDEF(V4AFdata *vertexs,T4AFdata *data)
{
	V4AFdata *t;
	V4AFdata *vt[3]={vertexs,vertexs+1,vertexs+2};
	V4AFdata *vx1=vertexs;
	V4AFdata *vx2=vertexs+1;
	V4AFdata *vx3=vertexs+2;

	_TriangleSort(vt);
	tri_loop2 loop;
	loop.cscale=0.0000152587890625;

	int rv[3];
	float rvf[3] = { (vt[0]->v[0] + 0.5f), (vt[1]->v[0] + 0.5f), (vt[2]->v[0] + 0.5f) };

	vecFunctions.V3FTTo3I(rvf, rv);
	int maxx = rv[0];
	int minx = rv[0];
	if (maxx<rv[1]) maxx = rv[1];
	if (minx>rv[1]) minx = rv[1];
	if (maxx<rv[2]) maxx = rv[2];
	if (minx>rv[2]) minx = rv[2];

	int maxy = matFunctions.FTrunc(vt[2]->v[1] + 0.5f);
	int miny = matFunctions.FTrunc(vt[0]->v[1] + 0.5f);
	int midly = matFunctions.FTrunc(vt[1]->v[1] + 0.5f);

	vecFunctions.V4FTo4B(vt[0]->c,&loop.color);
	if (minx<0) minx=0;
	if (maxx>data->width-1) maxx=data->width-1;
	if (maxx<minx) maxx=minx;
	if (minx>maxx) minx=maxx;
	if (miny<0) miny=0;
	if (maxy>data->height-1) maxy=data->height-1;
	if (maxy<miny) maxy=miny;
	if (miny>maxy) miny=maxy;
	if (midly<miny) midly=miny;
	if (midly>maxy) midly=maxy;
	loop.startmem=(char*)data->mem+miny*data->stride+(minx<<2);
	loop.sad=data->stride;

	//color
	float normal0[3];
	float normal1[3];
	float normal2[3];
	float normal3[3];
	bt::vector3f pv1(vx1->v[0],vx1->v[1],vx1->c[0]);
	bt::vector3f pv2(vx2->v[0],vx2->v[1],vx2->c[0]);
	bt::vector3f pv3(vx3->v[0],vx3->v[1],vx3->c[0]);
	
	vecFunctions.V3FSub(&pv2,&pv1,&pv2);
	vecFunctions.V3FSub(&pv3,&pv1,&pv3);
	vecFunctions.V3FCross(&pv2,&pv3,&normal0);
	pv2.z=vx2->c[1]-vx1->c[1];
	pv3.z=vx3->c[1]-vx1->c[1];
	vecFunctions.V3FCross(&pv2,&pv3,&normal1);
	pv2.z=vx2->c[2]-vx1->c[2];
	pv3.z=vx3->c[2]-vx1->c[2];
	vecFunctions.V3FCross(&pv2,&pv3,&normal2);
	pv2.z=vx2->c[3]-vx1->c[3];
	pv3.z=vx3->c[3]-vx1->c[3];
	vecFunctions.V3FCross(&pv2,&pv3,&normal3);

	float cys[4];
	cys[0]=-normal0[1]/normal0[2];
	cys[1]=-normal1[1]/normal1[2];
	cys[2]=-normal2[1]/normal2[2];
	cys[3]=-normal3[1]/normal3[2];

	float cxs[4];
	cxs[0]=-normal0[0]/normal0[2];
	cxs[1]=-normal1[0]/normal1[2];
	cxs[2]=-normal2[0]/normal2[2];
	cxs[3]=-normal3[0]/normal3[2];

	float s=(minx-vt[0]->v[0])*65536.0f;
	vecFunctions.V4FCombine(vt[0]->c,cxs,loop.cstart,65536.0f,s);
	vecFunctions.V4Fmul2NTrunc(cys,loop.cy,16);
	vecFunctions.V4Fmul2NTrunc(cxs,loop.cx,16);
	s=(miny-vt[0]->v[1])*65536.0f;
	vecFunctions.V4FCombine(loop.cstart,cys,loop.cstart,1.0f,s);
	vecFunctions.V4FTTo4I(loop.cstart,loop.cstart);

	loop.cstart[0]-=32768;
	loop.cstart[1]-=32768;
	loop.cstart[2]-=32768;
	loop.cstart[3]-=32768;

	bool inv=false;
	if (vecFunctions.V2FQDFL(vt[0]->v,vt[1]->v,vt[2]->v)>=0) {
		t=vt[1];
		vt[1]=vt[2];
		vt[2]=t;
		inv=true;
	}

	float vr1[3];
	_calcplane(vt[0]->v,vt[1]->v,vr1);
	float vr2[3];
	_calcplane(vt[1]->v,vt[2]->v,vr2);
	float vr3[3];
	_calcplane(vt[2]->v,vt[0]->v,vr3);

	float v[2]={minx+0.4999f,miny+0.5f};
	loop.reg1[0]=(vr1[2]+v[1]*vr1[1]+v[0]*vr1[0]);
	loop.reg1[1]=(vr3[2]+v[1]*vr3[1]+v[0]*vr3[0]);
	loop.reg1[2]=(vr2[2]+v[1]*vr2[1]+v[0]*vr2[0]);
	loop.reg2[0]=1.0f/vr1[0];
	loop.reg2[1]=1.0f/vr3[0];
	loop.reg2[2]=1.0f/vr2[0];
	loop.reg3[0]=vr1[0];
	loop.reg3[1]=vr3[0];
	loop.reg3[2]=vr2[0];
	loop.reg4[0]=vr1[1];
	loop.reg4[1]=vr3[1];
	loop.reg4[2]=vr2[1];

	loop.range=maxx-minx;
	loop.loopsize=midly-miny-1;
	if (loop.loopsize>0) loop.reg1[2]+=loop.reg4[2]*loop.loopsize;
	triangle_MultyColor_8888_loop2_deff(&loop);
	loop.loopsize=1;
	middle_MultyColor_8888_loop2_deff(&loop);
	if (!inv) {
		loop.reg1[0]=loop.reg1[1];
		loop.reg2[0]=loop.reg2[1];
		loop.reg3[0]=loop.reg3[1];
		loop.reg4[0]=loop.reg4[1];
	}
	loop.reg1[1]=loop.reg1[2];
	loop.reg2[1]=loop.reg2[2];
	loop.reg3[1]=loop.reg3[2];
	loop.reg4[1]=loop.reg4[2];
	loop.loopsize=maxy-midly;
	triangle_MultyColor_8888_loop2_deff(&loop);
}

OPTIMIZE_OFF;

}
