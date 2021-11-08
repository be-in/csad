/*
 * mesh.cpp
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/mesh.h>
#include <platform.h>
#include "csad/platform/glextension.h"
#include "csad/bt/base/baseapi.h"

OPTIMIZE_ON;

namespace csad {

unsigned int tglArrayTypeConvertT[5]={0,4*1,4*2,4*3,4*4};
unsigned int tglArrayTypeConvertC[3]={0,4*3,4*4};
unsigned int tglArrayTypeConvertN[2]={0,4*3};
unsigned int tglArrayTypeConvertV[7]={0,4*2,4*3,4*4,8*2,8*3,8*4};
unsigned int tglArrayTypeCEConvertT[5]={0,1,2,3,4};
unsigned int tglArrayTypeCEConvertC[3]={0,3,4};
unsigned int tglArrayTypeCEConvertN[2]={0,3};
unsigned int tglArrayTypeCEConvertV[7]={0,2,3,4,2,3,4};
unsigned int tglIndexTypeConvert[7]={0,1,2,2,4,4,4};

Mesh::Mesh(char*)
{
	_init();
}

Mesh::Mesh(const char*)
{
	_init();
}

void Mesh::_init()
{
	p_elementFormat=Mesh::_TGL_0T2F+Mesh::_TGL_N3F+Mesh::_TGL_V3F;
	p_drawFormat=_GL_TRIANGLES;
	if (sizeof(GlIndex)==1) p_drawFormat|=_GL_INDEX_BYTE;
	if (sizeof(GlIndex)==2) p_drawFormat|=_GL_INDEX_WORD;
	if (sizeof(GlIndex)==4) p_drawFormat|=_GL_INDEX_DWORD;
	p_elements=0;
	p_index=0;
	p_indexCount=0;
	p_elementCount=0;
	p_bound.zero();
}

Mesh::~Mesh()
{
	extFunctions.DeleteMem(p_index,0);
	extFunctions.DeleteMem(p_elements, 0);
	p_index=0;
	p_elements=0;
	p_indexCount=0;
	p_elementCount=0;
}

Mesh& Mesh::setFields(unsigned int attr)
{
	p_elementFormat=attr;
	return *this;
}

unsigned int Mesh::getVectorType()
{
	return p_elementFormat&7;
}

unsigned int Mesh::getColorType()
{
	return p_elementFormat &0xF0000000;
}

unsigned int Mesh::getTexType(int id)
{
	return (p_elementFormat>>(id*4)) &0xF0;
}

bool Mesh::isNormal()
{
	return (p_elementFormat&8)!=0;
}

Mesh& Mesh::setVertexCount(unsigned int count)
{
	if (p_elements) extFunctions.DeleteMem(p_elements,0);
	p_elements = (unsigned char *)extFunctions.CreateMem(count*_elementSize(p_elementFormat),0);
	p_elementCount=count;
	p_drawFormat|=_GL_NEED_ELEMENT_UPDATE;
	return *this;
}

Mesh& Mesh::setIndexCount(unsigned int count)
{
	//if (count==p_indexCount) return; //??
	if (p_index) extFunctions.DeleteMem(p_index,0);
	p_index = (unsigned char *)extFunctions.CreateMem(count*sizeof(GlIndex), 0);
	p_indexCount=count;
	p_drawFormat|=_GL_NEED_INDEX_UPDATE;
	return *this;
}

Mesh& Mesh::resizeVertex(unsigned int count)
{
	unsigned int s=_elementSize(p_elementFormat);
	unsigned char *el = (unsigned char *)extFunctions.CreateMem(count*s, 0);
	if (p_elements) {
		int fr=p_elementCount-count;
		if (fr<0) fr=0;
		unsigned char *from=p_elements+fr*s;
		int t=count-p_elementCount;
		if (t<0) t=0;
		unsigned char *to=el+t*s;
		if (p_elementCount>count) p_elementCount=count;
		extFunctions.MoveMem(from,to,p_elementCount*s);
		extFunctions.DeleteMem(p_elements,0);
		if (p_index) {
			GlIndex * ind=(GlIndex *)p_index;
			for (unsigned int i=0;i<p_indexCount;i++) ind[i]+=t;
		}
	}
	p_elements=el;
	p_elementCount=count;
	p_drawFormat|=_GL_NEED_ELEMENT_UPDATE;
	return *this;
}

Mesh& Mesh::resizeIndex(unsigned int count)
{
	unsigned int s=sizeof(GlIndex);
	unsigned char *in = (unsigned char *)extFunctions.CreateMem(count*s, 0);
	if (p_index) {
		int fr=p_indexCount-count;
		if (fr<0) fr=0;
		unsigned char *from=p_index+fr*s;
		int t=count-p_indexCount;
		if (t<0) t=0;
		unsigned char *to=in+t*s;
		if (p_indexCount>count) p_indexCount=count;
		extFunctions.MoveMem(from,to,p_indexCount*s);
		extFunctions.DeleteMem(p_index,0);
	}
	p_index=in;
	p_indexCount=count;
	p_drawFormat|=_GL_NEED_INDEX_UPDATE;
	return *this;
}

Mesh& Mesh::setDrawFormat(stDrawFormat attr)
{
	p_drawFormat=attr+(p_drawFormat & (~_GL_MASK));
	return *this;
}

int Mesh::indexById(unsigned int id)
{
	GlIndex * p = (GlIndex *)p_index;
	return p[id];
}

Mesh& Mesh::setIndex(unsigned int i,int val)
{
	GlIndex * p = (GlIndex *)p_index;
	p[i]=val;
	p_drawFormat|=_GL_NEED_INDEX_UPDATE;
	return *this;
}

Mesh& Mesh::setVector(unsigned int i,float *v)
{
	char *c=_startElement(this,0,_VECTOR);
	c+=_elementSize(p_elementFormat)*i;
	i=tglArrayTypeCEConvertV[p_elementFormat&7];
	unsigned int size=i<<2;
	if (size==_elementSize(p_elementFormat,_VECTOR)) {
		extFunctions.MoveMem(v,c,size);
	} else {
		double *cc=(double *)c;
		cc[0]=(float)v[0];
		cc[1]=(float)v[1];
		if (i>2) cc[2]=(float)v[2];
		if (i>3) cc[3]=(float)v[3];
	}
	p_drawFormat|=_GL_NEED_ELEMENT_UPDATE;
	return *this;
}

Mesh& Mesh::setVector(unsigned int i,double *v)
{
	char *c=_startElement(this,0,_VECTOR);
	c+=_elementSize(p_elementFormat)*i;
	i=tglArrayTypeCEConvertV[p_elementFormat&7];
	unsigned int size=i<<3;
	if (size>_elementSize(p_elementFormat,_VECTOR)) {
		float *cc=(float *)c;
		cc[0]=(float)v[0];
		cc[1]=(float)v[1];
		if (i>2) cc[2]=(float)v[2];
		if (i>3) cc[3]=(float)v[3];
	} else {
		extFunctions.MoveMem(v,c,size);
	}
	p_drawFormat|=_GL_NEED_ELEMENT_UPDATE;
	return *this;
}

Mesh& Mesh::setIndexLine(unsigned int i,unsigned int a,unsigned int b)
{
	GlIndex * p = (GlIndex *)p_index;
	p[i]=a;
	i++;
	p[i]=b;
	p_drawFormat|=_GL_NEED_INDEX_UPDATE;
	return *this;
}

Mesh& Mesh::setIndexTri(unsigned int i,unsigned int a,unsigned int b,unsigned int c)
{
	GlIndex * p = (GlIndex *)p_index;
	p[i]=a;
	i++;
	p[i]=b;
	i++;
	p[i]=c;
	p_drawFormat|=_GL_NEED_INDEX_UPDATE;
	return *this;
}

Mesh& Mesh::setIndexQuad(unsigned int i,unsigned int a,unsigned int b,unsigned int c,unsigned int d)
{
	GlIndex * p = (GlIndex *)p_index;
	p[i]=a;
	i++;
	p[i]=b;
	i++;
	p[i]=c;
	i++;
	p[i]=d;
	p_drawFormat|=_GL_NEED_INDEX_UPDATE;
	return *this;
}

void Mesh::cleanIndex(int from,int count)
{
	GlIndex * p = (GlIndex *)p_index;
	if (sizeof(GlIndex)==4) extFunctions.StocIMem(&p[from],count,0);
	if (sizeof(GlIndex)==2) extFunctions.StocSMem(&p[from],count,0);
}

vector3d Mesh::calculateBound()
{
	int type=p_elementFormat&7;
	vector3f maxf(0.0);
	vector3f minf(0.0);
	vector3d maxd(0.0);
	vector3d mind(0.0);
	if (p_elementCount==0) return mind;
	LinkArray<int>::iterator vectors = vector<int>().begin();
	if (type==Mesh::_TGL_V2F) {
		maxf=vector3f((vector2f*)&vectors.value());
		minf=vector3f((vector2f*)&vectors.value());
		for (unsigned int i = 1; i < p_elementCount; ++i) {
			vectors++;
			vecFunctions.V2FMinMax(&vectors.value(),&minf,&maxf);
		}
		vecFunctions.V3FTo3D(&maxf,&maxd);
		vecFunctions.V3FTo3D(&minf,&mind);
	}
	if (type==Mesh::_TGL_V3F || type==Mesh::_TGL_V4F) {
		maxf=*(vector3f*)&vectors.value();
		minf=*(vector3f*)&vectors.value();
		for (unsigned int i = 1; i < p_elementCount; ++i) {
			vectors++;
			vecFunctions.V3FMinMax(&vectors.value(),&minf,&maxf);
		}
		vecFunctions.V3FTo3D(&maxf,&maxd);
		vecFunctions.V3FTo3D(&minf,&mind);
	}
	if (type==Mesh::_TGL_V2D) {
		maxd=vector3d((vector2d*)&vectors.value());
		mind=vector3d((vector2d*)&vectors.value());
		for (unsigned int i = 1; i < p_elementCount; ++i) {
			vectors++;
			vecFunctions.V2DMinMax(&vectors.value(),&mind,&maxd);
		}
	}
	if (type==Mesh::_TGL_V3D || type==Mesh::_TGL_V4D) {
		maxd=*(vector3d*)&vectors.value();
		mind=*(vector3d*)&vectors.value();
		for (unsigned int i = 1; i < p_elementCount; ++i) {
			vectors++;
			vecFunctions.V3DMinMax(&vectors.value(),&mind,&maxd);
		}
	}
	maxd-=mind;
	mind+=maxd*0.5;
	p_bound=vector4d(mind.x,mind.y,mind.z,maxd.sqrLen()*0.25);
	return maxd;
}

void Mesh::calculateNormals()
{
	if ((p_elementFormat&0x8)==0) return;
	if (p_indexCount==0) return;

	int dformat=p_drawFormat & _GL_MASK;
	int type=p_elementFormat&7;
	LinkArray<vector3f> normals = normal<vector3f>();
	if (type==Mesh::_TGL_V2F || type==Mesh::_TGL_V2D || dformat<_GL_TRIANGLES) {
		for (unsigned int i = 0; i < p_elementCount; i++) normals[i]=vector3f(0.0f,0.0f,1.0f);
	} else {
		for (unsigned int i = 0; i < p_elementCount; i++) normals[i]=vector3f(0.0f);
	}

	GlIndex * p = (GlIndex *)p_index;
	unsigned int indc=p_indexCount;
	int indinc=0;
	if (dformat==_GL_TRIANGLES) {
		indc-=2;
		indinc=3;
	}
	if (dformat==_GL_TRIANGLE_STRIP || dformat==_GL_QUAD_STRIP || dformat==_GL_TRIANGLE_FAN) {
		indc-=2;
		indinc=1;
	}
	if (dformat==_GL_QUADS) {
		indinc=4;
	}
	LinkArray<int> vectors = vector<int>();
	if (dformat==_GL_TRIANGLES || dformat==_GL_TRIANGLE_STRIP || dformat==_GL_QUAD_STRIP) {
		if (type==Mesh::_TGL_V3F || type==Mesh::_TGL_V4F) {
			//LinkArray<vector3f> vectors = vector<vector3f>();
			int off=(int)(normals.getArray()-vectors.getArray());
			for (unsigned int i = 0; i < indc; i+=indinc) {
				vecFunctions.V3FAddTriNorm(&vectors[p[i]],&vectors[p[i+1]],&vectors[p[i+2]],off);
			}
		}
		if (type==Mesh::_TGL_V3D || type==Mesh::_TGL_V4D) {
			//LinkArray<vector3d> vectors = vector<vector3d>();
			int off=(int)(normals.getArray()-vectors.getArray());
			for (unsigned int i = 0; i < indc; i+=indinc) {
				vecFunctions.V3FAdd3DTriNorm(&vectors[p[i]],&vectors[p[i+1]],&vectors[p[i+2]],off);
			}
		}
	}
	if (dformat==_GL_TRIANGLE_FAN) {
		if (type==Mesh::_TGL_V3F || type==Mesh::_TGL_V4F) {
			//LinkArray<vector3f> vectors = vector<vector3f>();
			int off=(int)(normals.getArray()-vectors.getArray());
			void *s=&vectors[p[0]];
			for (unsigned int i = 0; i < indc;) {
				vecFunctions.V3FAddTriNorm(s,&vectors[p[i]],&vectors[p[i]],off);
				i+=indinc;
			}
		}
		if (type==Mesh::_TGL_V3D || type==Mesh::_TGL_V4D) {
			//LinkArray<vector3d> vectors = vector<vector3d>();
			int off=(int)(normals.getArray()-vectors.getArray());
			void *s=&vectors[p[0]];
			for (unsigned int i = 0; i < indc;) {
				vecFunctions.V3FAdd3DTriNorm(s,&vectors[p[i+1]],&vectors[p[i+2]],off);
				i+=indinc;
			}
		}
	}
	if (dformat==_GL_QUADS) {
		if (type==Mesh::_TGL_V3F || type==Mesh::_TGL_V4F) {
			//LinkArray<vector3f> vectors = vector<vector3f>();
			int off=(int)(normals.getArray()-vectors.getArray());
			for (unsigned int i = 0; i < indc;) {
				void *vr[4]={&vectors[p[i]],&vectors[p[i+1]],&vectors[p[i+2]],&vectors[p[i+3]]};
				vecFunctions.V3FAddTriNorm(vr[0],vr[1],vr[2],off);
				vecFunctions.V3FAddTriNorm(vr[1],vr[2],vr[3],off);
				i+=indinc;
			}
		}
		if (type==Mesh::_TGL_V3D || type==Mesh::_TGL_V4D) {
			//LinkArray<vector3d> vectors = vector<vector3d>();
			int off=(int)(normals.getArray()-vectors.getArray());
			for (unsigned int i = 0; i < indc;) {
				void *vr[4]={&vectors[p[i]],&vectors[p[i+1]],&vectors[p[i+2]],&vectors[p[i+3]]};
				vecFunctions.V3FAdd3DTriNorm(vr[0],vr[1],vr[2],off);
				vecFunctions.V3FAdd3DTriNorm(vr[1],vr[2],vr[3],off);
				i+=indinc;
			}
		}
	}
	if (type!=Mesh::_TGL_V2F && type!=Mesh::_TGL_V2D) {
		arvFunctions.A3FNormal(normals.getArray(),normals.getArray(),normals.getStep(),normals.getStep(),normals.count());
	}
	p_drawFormat|=_GL_NEED_ELEMENT_UPDATE;
}

unsigned int Mesh::combineFilds(Mesh * mesha,Mesh * )
{
/*	int sizea=tglArrayTypeConvertV[mesha->p_elementFormat &0x7];
	int counta=tglArrayTypeCEConvertV[mesha->p_elementFormat &0x7];
	sizea=sizea/counta;
	int sizeb=tglArrayTypeConvertV[mesha->p_elementFormat &0x7];
	int countb=tglArrayTypeCEConvertV[mesha->p_elementFormat &0x7];
	sizeb=sizeb/countb;

	if (countb>counta) counta=countb;*/

	return mesha->p_elementFormat;
}

unsigned int Mesh::_indexSize(unsigned int drawformat)
{
	return tglIndexTypeConvert[(drawformat>>24)&7];
}

unsigned int Mesh::_elementSize(unsigned int format)
{
	int size=tglArrayTypeConvertV[format &0x7];
	size+=tglArrayTypeConvertN[(format>>3) &0x1];
	int i=1;
	while (i<7) {
		size+=tglArrayTypeConvertT[(format>>(i<<2)) &0xF];
		i++;
	}
	size+=tglArrayTypeConvertC[(format>>28) &0xF];
	return size;
}

unsigned int Mesh::_elementSize(unsigned int format,unsigned int it)
{
	if (it==_TEXTURE0) return tglArrayTypeConvertT[(format>>4) &0xF];
	if (it==_TEXTURE1) return tglArrayTypeConvertT[(format>>8) &0xF];
	if (it==_TEXTURE2) return tglArrayTypeConvertT[(format>>12) &0xF];
	if (it==_TEXTURE3) return tglArrayTypeConvertT[(format>>16) &0xF];
	if (it==_TEXTURE4) return tglArrayTypeConvertT[(format>>20) &0xF];
	if (it==_TEXTURE5) return tglArrayTypeConvertT[(format>>24) &0xF];
	if (it==_COLOR) return tglArrayTypeConvertC[(format>>28) &0xF];
	if (it==_NORMAL) return tglArrayTypeConvertN[(format>>3) &0x1];
	if (it==_VECTOR) return tglArrayTypeConvertV[format &0x7];
	return 0;
}


unsigned int Mesh::_elementSubCount(unsigned int format, unsigned int it)
{
	if (it==_TEXTURE0) return tglArrayTypeCEConvertT[(format>>4) &0xF];
	if (it==_TEXTURE1) return tglArrayTypeCEConvertT[(format>>8) &0xF];
	if (it==_TEXTURE2) return tglArrayTypeCEConvertT[(format>>12) &0xF];
	if (it==_TEXTURE3) return tglArrayTypeCEConvertT[(format>>16) &0xF];
	if (it==_TEXTURE4) return tglArrayTypeCEConvertT[(format>>20) &0xF];
	if (it==_TEXTURE5) return tglArrayTypeCEConvertT[(format>>24) &0xF];
	if (it==_COLOR) return tglArrayTypeCEConvertC[(format>>28) &0xF];
	if (it==_NORMAL) return tglArrayTypeCEConvertN[(format>>3) &0x1];
	if (it==_VECTOR) return tglArrayTypeCEConvertV[format &0x7];
	return 0;
}

char * Mesh::_startElement(Mesh *mesh,unsigned int offset, unsigned int it)
{
	int i=0;
	char *p=(char *)mesh->p_elements;
	int size=_elementSize(mesh->p_elementFormat);
	while (it>0) {
		p+=_elementSize(mesh->p_elementFormat,i);
		i++;
		it--;
	}
	p+=size*offset;
	return p;
}

TYPEINFO(Mesh::MeshQuad)

TYPEINFO(Mesh::MeshCube)

TYPEINFO(Mesh::MeshSphere)

TYPEINFO(Mesh)

/*void Mesh::Ray(Ray *ray,out array collisions)
{
	proj(matrix) to new array or temp buffer vertex
	for all triangles
		test ray -> point collision
}*/

//******************** StaticMesh **********************************

StaticMesh::StaticMesh(unsigned char * index,unsigned int indexCount,unsigned char*elements,unsigned int elemCount,unsigned int draw,unsigned int format)
{
	initFunc();
	p_elementFormat=format;
	p_drawFormat=draw;
	if ((p_drawFormat&_GL_INDEX_MASK)==0) {
		if (sizeof(GlIndex)==1) p_drawFormat|=_GL_INDEX_BYTE;
		if (sizeof(GlIndex)==2) p_drawFormat|=_GL_INDEX_WORD;
		if (sizeof(GlIndex)==4) p_drawFormat|=_GL_INDEX_DWORD;
	}
	p_elements=elements;
	p_index=index;
	p_indexCount=indexCount;
	p_elementCount=elemCount;
	calculateBound();
	//p_bound.zero();
}

StaticMesh::~StaticMesh()
{
	p_index=0;
	p_elements=0;
}

//******************** VBOMesh **********************************

VBOMesh::VBOMesh(BaseMesh * mesh)
{
	elements=0;
	index=0;
	context=GlContext::getCurrent();
	if (mesh->getMesh()==mesh && context) {
		p_mesh=mesh;
	}
}

VBOMesh::~VBOMesh()
{
	if (context) {
		context->makeCurrent();
		Render::FreeVBO(this);
		//context->freeVBOMesh(this);
	}
	context=0;
	p_mesh=0;
}

//****************** base primitives ***************************

struct baseShape {
	vector2f text;
	vector3f norm;
	vector3f vert;
};

baseShape ShapeQuad[] = {
		// quad
		{vector2f(0,0),vector3f(0,0,1),vector3f(-1,-1,0)},
		{vector2f(1,0),vector3f(0,0,1),vector3f(1,-1,0)},
		{vector2f(1,1),vector3f(0,0,1),vector3f(1,1,0)},
		{vector2f(0,1),vector3f(0,0,1),vector3f(-1,1,0)}
		// box
		// plane
		// sphere
};

baseShape ShapeCube[] = {
		// cube
		{vector2f(0,0),vector3f(0,0,1.0f),vector3f(-1,-1,1)},
		{vector2f(1,0),vector3f(0,0,1.0f),vector3f(1,-1,1)},
		{vector2f(1,1),vector3f(0,0,1.0f),vector3f(1,1,1)},
		{vector2f(0,1),vector3f(0,0,1.0f),vector3f(-1,1,1)},
		{vector2f(0,0),vector3f(0,0,-1.0f),vector3f(1,-1,-1)},
		{vector2f(1,0),vector3f(0,0,-1.0f),vector3f(-1,-1,-1)},
		{vector2f(1,1),vector3f(0,0,-1.0f),vector3f(-1,1,-1)},
		{vector2f(0,1),vector3f(0,0,-1.0f),vector3f(1,1,-1)},
		{vector2f(0,0),vector3f(1.0f,0,0),vector3f(1,-1,-1)},
		{vector2f(1,0),vector3f(1.0f,0,0),vector3f(1,1,-1)},
		{vector2f(1,1),vector3f(1.0f,0,0),vector3f(1,1,1)},
		{vector2f(0,1),vector3f(1.0f,0,0),vector3f(1,-1,1)},
		{vector2f(0,0),vector3f(-1.0f,0,0),vector3f(-1,1,-1)},
		{vector2f(1,0),vector3f(-1.0f,0,0),vector3f(-1,-1,-1)},
		{vector2f(1,1),vector3f(-1.0f,0,0),vector3f(-1,-1,1)},
		{vector2f(0,1),vector3f(-1.0f,0,0),vector3f(-1,1,1)},
		{vector2f(0,0),vector3f(0,1.0f,0),vector3f(1,1,-1)},
		{vector2f(1,0),vector3f(0,1.0f,0),vector3f(-1,1,-1)},
		{vector2f(1,1),vector3f(0,1.0f,0),vector3f(-1,1,1)},
		{vector2f(0,1),vector3f(0,1.0f,0),vector3f(1,1,1)},
		{vector2f(0,0),vector3f(0,-1.0f,0),vector3f(-1,-1,-1)},
		{vector2f(1,0),vector3f(0,-1.0f,0),vector3f(1,-1,-1)},
		{vector2f(1,1),vector3f(0,-1.0f,0),vector3f(1,-1,1)},
		{vector2f(0,1),vector3f(0,-1.0f,0),vector3f(-1,-1,1)}
};

GlIndex IndexQuad[] = {
		0,1,2,0,2,3
};

GlIndex IndexCube[] = {
		0,1,2,0,2,3,
		4,5,6,4,6,7,
		8,9,10,8,10,11,
		12,13,14,12,14,15,
		16,17,18,16,18,19,
		20,21,22,20,22,23,
};

StaticMesh LocalQuad((unsigned char*)IndexQuad,6,(unsigned char*)ShapeQuad,4,Mesh::_GL_TRIANGLES,Mesh::_TGL_0T2F+Mesh::_TGL_N3F+Mesh::_TGL_V3F);
StaticMesh LocalCube((unsigned char*)IndexCube,36,(unsigned char*)ShapeCube,24,Mesh::_GL_TRIANGLES,Mesh::_TGL_0T2F+Mesh::_TGL_N3F+Mesh::_TGL_V3F);

Mesh* Mesh::Quad=&LocalQuad;
Mesh* Mesh::Cube=&LocalCube;

TYPEINFO(VBOMesh)

}

OPTIMIZE_OFF;
