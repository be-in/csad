/*
 * cputriangulator.cpp
 *
 *  Created on: 17.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <gen3.h>
#include "csad/btext/tesselator/tess.h"

OPTIMIZE_ON;

namespace gen {

void CPUTriangulator::initialize(vector2i* v,int *counts,int count)
{
	p_type=(void*)vector2i::t();
	p_poligons=count;
	p_counts=counts;
	int cg=0;
	for (int i=0;i<p_poligons;i++) cg+=counts[i];
	p_count=cg;
	p_vectors=v;
	p_tessdata.c=0;
}

void CPUTriangulator::initialize(vector2f* v,int *counts,int count)
{
	p_type=(void*)vector2f::t();
	p_poligons=count;
	p_counts=counts;
	int cg=0;
	for (int i=0;i<p_poligons;i++) cg+=counts[i];
	p_count=cg;
	p_vectors=v;
	p_tessdata.c=0;
}

void myVertex(int *id,TessData *tess)
{
	if (!id) return;
	unsigned int sid=(unsigned int)*id;
	//if (sid<0) sid=0;
	if (sid>=tess->p_vectors.count()) sid=0;

	if (tess->mode==GL_TRIANGLES) {
		tess->p_result.assign(sid);
	}

	if (tess->mode==GL_TRIANGLE_STRIP) {
		if (tess->c<2) {
			tess->tri[tess->c]=sid;
			tess->c++;
			tess->tri[2]=0;
		} else {
			//Log::console("%i %i %i",tess->tri[0],tess->tri[1],*id);
			tess->p_result.assign(tess->tri[0]);
			tess->p_result.assign(tess->tri[1]);
			tess->p_result.assign(sid);
			if (((tess->tri[2]) & 1)==0) {
				tess->tri[0]=sid;
			} else {
				tess->tri[1]=sid;
			}
			tess->tri[2]^=1;
		}
	}

	if (tess->mode==GL_TRIANGLE_FAN) {
		if (tess->c<2) {
			tess->tri[tess->c]=sid;
			tess->c++;
		} else {
			tess->p_result.assign(tess->tri[0]);
			tess->p_result.assign(tess->tri[1]);
			tess->p_result.assign(sid);
			tess->tri[1]=sid;
		}
	}
}

void myBeginData(int mode,TessData *tess)
{
	tess->mode=mode;
	tess->c=0;
}

void myEnd(TessData *tess)
{
	tess->c=0;
}

void myCombine(float coor[3], void* [4], float [4] ,int **id,TessData *tess)
{
	if (tess->p_indexes.reservSize()<=tess->p_indexes.count()) {
		*id=0;
		return;
	}
	int iid=tess->p_vectors.size();
	tess->p_indexes.assign(iid);
	*id=&tess->p_indexes.last();
	tess->p_vectors.assign(*(vector3f*)coor);
}

void CPUTriangulator::triangulate()
{
	//int s=bt::extFunctions.TSC();

	GLUtesselator *tobj;
	tobj = gluNewTess();

	gluTessProperty(tobj,GLU_TESS_WINDING_RULE,GLU_TESS_WINDING_POSITIVE);
	gluTessProperty(tobj,GLU_TESS_BOUNDARY_ONLY,GL_FALSE);
	gluTessCallback(tobj,GLU_TESS_VERTEX_DATA,(void (*) ()) &myVertex);
	gluTessCallback(tobj,GLU_TESS_BEGIN_DATA,(void (*) ()) &myBeginData);
	gluTessCallback(tobj,GLU_TESS_END_DATA,(void (*) ()) &myEnd);
	gluTessCallback(tobj,GLU_TESS_COMBINE_DATA,(void (*) ()) &myCombine);

	p_tessdata.p_indexes.clear();
	p_tessdata.p_indexes.reserve(p_count*2);
	p_tessdata.p_vectors.clear();
	p_tessdata.p_vectors.reserve(p_count*2);
	gluTessBeginPolygon(tobj,&p_tessdata);


	if (p_type==(void*)vector2i::t()) {
		_vector2iTess(tobj);
	}

	if (p_type==(void*)vector2f::t()) {
		_vector2fTess(tobj);
	}

	gluTessEndPolygon(tobj);
	gluDeleteTess(tobj);

	//s=bt::extFunctions.TSC()-s;
	//csad::Log::console("tess %i",s);
}

void CPUTriangulator::_vector2iTess(GLUtesselator*tobj)
{
	int cg=0;
	int id=0;
	vector2i *vr=(vector2i*)p_vectors;
	for (int i=0;i<p_poligons;i++) {
		int cd=p_counts[i];
		for (int j=0;j<cd;j++) {
			if ((vr[cg+j]!=vr[cg+((j+1)%cd)])) {
				id=p_tessdata.p_vectors.size();
				p_tessdata.p_indexes.assign(id);
				vector3f c((float)vr[cg+j].x,(float)vr[cg+j].y,0);
				p_tessdata.p_vectors.assign(c);
			}
		}
		cg+=cd;
	}

	cg=0;
	id=0;
	for (int i=0;i<p_poligons;i++) {
		gluTessBeginContour(tobj);
		int cd=p_counts[i];
		for (int j=0;j<cd;j++) {
			if ((vr[cg+j]!=vr[cg+((j+1)%cd)])) {
				gluTessVertex(tobj,(float*)&p_tessdata.p_vectors[id],&p_tessdata.p_indexes[id]);
				id++;
			}
		}
		gluTessEndContour(tobj);
		cg+=cd;
	}
}

void CPUTriangulator::_vector2fTess(GLUtesselator*tobj)
{
	int cg=0;
	int id=0;
	vector2f *vr=(vector2f*)p_vectors;

	for (int i=0;i<p_poligons;i++) {
		int cd=p_counts[i];
		for (int j=0;j<cd;j++) {
			if ((vr[cg+j]!=vr[cg+((j+1)%cd)])) {
				id=p_tessdata.p_vectors.size();
				p_tessdata.p_indexes.assign(id);
				vector3f c(vr[cg+j].x,vr[cg+j].y,0);
				p_tessdata.p_vectors.assign(c);
			}
		}
		cg+=cd;
	}

	cg=0;
	id=0;
	for (int i=0;i<p_poligons;i++) {
		gluTessBeginContour(tobj);
		int cd=p_counts[i];
		for (int j=0;j<cd;j++) {
			if ((vr[cg+j]!=vr[cg+((j+1)%cd)])) {
				gluTessVertex(tobj,(float*)&p_tessdata.p_vectors[id],&p_tessdata.p_indexes[id]);
				id++;
			}
		}
		gluTessEndContour(tobj);
		cg+=cd;
	}
}

}

OPTIMIZE_OFF;
