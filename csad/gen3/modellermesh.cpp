/*
 * modellermesh.cpp
 *
 *  Created on: 18.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <gen3.h>
#include <scene/mesh.h>
#include <scene/textstyle.h>
#include <scene/fonttext.h>
#include <platform.h>
#include <bt.h>
#include "csad/platform/glextension.h"

OPTIMIZE_ON;

namespace gen {

using namespace csad;

ModellerMesh::ModellerMesh()
{
	p_mode=0;
	p_matrix.identity();
	p_mesh=0;
	p_color=vector4f(1.0f);
}

ModellerMesh::~ModellerMesh()
{
}

void ModellerMesh::setMesh(Mesh* mesh)
{
	p_mesh=mesh;
	if (p_mesh) {
		p_step=Mesh::_elementSize(p_mesh->p_elementFormat);
		//p_vector=Mesh::_startElement(p_mesh,0,Mesh::_VECTOR);
	}
}

void ModellerMesh::setMode(unsigned int mode)
{
	p_mode=mode;
}

void ModellerMesh::TRS(vector3d *pos,quaterniond *rot,vector3f *scale)
{
	vector3d mscale(scale);
	vecFunctions.M4DTRS(&p_matrix,pos,rot,&mscale);
}

void ModellerMesh::addTranslate(vector3d *pos)
{
/*	matrix4d m;
	m.translate(pos);
	p_matrix=p_matrix*m;*/
	p_matrix.addTranslateSelf(pos);
}

void ModellerMesh::addTranslate(double x,double y,double z)
{
/*	matrix4d m;
	m.translate(x,y,z);
	p_matrix=m*p_matrix;*/
	p_matrix.addTranslateSelf(x,y,z);
}

void ModellerMesh::addRotation(quaterniond *rot)
{
	p_matrix.addRotateSelf(*rot);
}

void ModellerMesh::addScale(vector3f *scale)
{
	vector3d mscale(scale);
	/*matrix4d m;
	vector3d mscale(scale);
	Functions::vecFunctions.M4DScale(&m,&mscale);
	p_matrix=m*p_matrix;*/
	p_matrix.addScaleSelf(mscale);
}

void ModellerMesh::resetMatrix()
{
	p_matrix.identity();
}

void ModellerMesh::Translate(vector3d *pos)
{
	genFunctions.MeshTranslate(p_mesh,(float)pos->x,(float)pos->y,(float)pos->z);
}

void ModellerMesh::Rotate(vector3d *rot)
{
	genFunctions.MeshRotate(p_mesh,(float)rot->x,(float)rot->y,(float)rot->z);
}

void ModellerMesh::Scale(vector3f *scale)
{
	genFunctions.MeshScale(p_mesh,scale->x,scale->y,scale->z);
}

void ModellerMesh::Transform(unsigned int from,unsigned int count )
{
	unsigned int type=p_mesh->getVectorType();
	unsigned int size=csad::Mesh::_elementSize(p_mesh->p_elementFormat);
	matrix4f p_matrixf(p_matrix);
	char *p=csad::Mesh::_startElement(p_mesh,from,csad::Mesh::_VECTOR);
	if (type==Mesh::_TGL_V2F) {
		arvFunctions.A2FMatrixTransform(p,&p_matrixf,p,size,size,count);
	}
	if (type==Mesh::_TGL_V3F) {
		arvFunctions.A3FMatrixTransform(p,&p_matrixf,p,size,size,count);
	}
	if (type==Mesh::_TGL_V4F) {
		arvFunctions.A4FMatrixTransform(p,&p_matrixf,p,size,size,count);
	}
	if (type==Mesh::_TGL_V2D) {
		arvFunctions.A2DMatrixTransform(p,&p_matrixf,p,size,size,count);
	}
	if (type==Mesh::_TGL_V3D) {
		arvFunctions.A3DMatrixTransform(p,&p_matrixf,p,size,size,count);
	}
	if (type==Mesh::_TGL_V4D) {
		arvFunctions.A4DMatrixTransform(p,&p_matrixf,p,size,size,count);
	}
}

void ModellerMesh::setColor(unsigned int color)
{
	vecFunctions.V4BTo4F(&color,&p_color);
}

void ModellerMesh::setColor(vector4f *color)
{
	p_color=*color;
}

void ModellerMesh::setColor(float b,float g,float r,float a)
{
	p_color.x=b;
	p_color.y=g;
	p_color.z=r;
	p_color.w=a;
}

/*void ModellerMesh::Colorize(unsigned int from,unsigned int count )
{
}*/

void ModellerMesh::copyIndex(Mesh* mesh,unsigned int at,unsigned int from,unsigned int count,int off)
{
	GlIndex * pd = (GlIndex *)p_mesh->p_index;
	GlIndex * ps = (GlIndex *)mesh->p_index;
	extFunctions.MoveMem(&ps[from],&pd[at],count*sizeof(GlIndex));
	for (unsigned int i=at;i<at+count;i++) pd[i]+=off;
}

void ModellerMesh::copyVertex(Mesh* mesh,unsigned int at,unsigned int from,unsigned int count)
{
	char * pd = (char *)p_mesh->p_elements;
	char * ps = (char *)mesh->p_elements;
	unsigned int size=Mesh::_elementSize(p_mesh->p_elementFormat);
	extFunctions.MoveMem(&ps[from*size],&pd[at*size],count*size);
}

void ModellerMesh::addArray(Vector<vector2i> * arr,unsigned int from,unsigned int count)
{
	if (count<=0) count=arr->count();
	if (arr->count()-from<count) count=arr->count()-from;
	p_mesh->resizeVertex(p_mesh->p_elementCount+count);

	vector2i *v=&(*arr)[from];
	unsigned int st=arr->sizeOfType();
	unsigned int type=p_mesh->getVectorType();
	matrix4f p_matrixf(p_matrix);
	vector4f vr4f(0.0f,0.0f,0.0f,1.0f);
	if (type==Mesh::_TGL_V2F) {
		LinkArray<vector2f> vectors = p_mesh->vector<vector2f>();
		arvFunctions.A2ITo2F(v,vectors.getArray(),st,vectors.getStep(),count);
		arvFunctions.A2FMatrixTransform(vectors.getArray(),p_matrixf.m,vectors.getArray(),vectors.getStep(),vectors.getStep(),count);
	}
	if (type==Mesh::_TGL_V3F) {
		LinkArray<vector3f> vectors = p_mesh->vector<vector3f>();
		arvFunctions.A2IGrowTo3F(v,vectors.getArray(),st,vectors.getStep(),count);
		arvFunctions.A3FMatrixTransform(vectors.getArray(),p_matrixf.m,vectors.getArray(),vectors.getStep(),vectors.getStep(),count);
	}
	if (type==Mesh::_TGL_V4F) {
		LinkArray<vector4f> vectors = p_mesh->vector<vector4f>();
		arvFunctions.A2IGrowTo4F(v,vectors.getArray(),st,vectors.getStep(),count);
		arvFunctions.A4FMatrixTransform(vectors.getArray(),p_matrixf.m,vectors.getArray(),vectors.getStep(),vectors.getStep(),count);
	}
}

void ModellerMesh::addArray(Vector<vector2f> * arr,unsigned int from,unsigned int count)
{
	if (count<=0) count=arr->count();
	if (arr->count()-from<count) count=arr->count()-from;
	p_mesh->resizeVertex(p_mesh->p_elementCount+count);

	vector2f *v=&(*arr)[from];
	unsigned int st=arr->sizeOfType();
	unsigned int type=p_mesh->getVectorType();
	matrix4f p_matrixf(p_matrix);
	vector4f vr4f(0.0f,0.0f,0.0f,1.0f);
	if (type==Mesh::_TGL_V2F) {
		LinkArray<vector2f> vectors = p_mesh->vector<vector2f>();
		arvFunctions.A2FMatrixTransform(v,p_matrixf.m,vectors.getArray(),st,vectors.getStep(),count);
	}
	if (type==Mesh::_TGL_V3F) {
		LinkArray<vector3f> vectors = p_mesh->vector<vector3f>();
		arvFunctions.A2FGrow3F(v,vectors.getArray(),st,vectors.getStep(),count);
		arvFunctions.A3FMatrixTransform(vectors.getArray(),p_matrixf.m,vectors.getArray(),vectors.getStep(),vectors.getStep(),count);
	}
	if (type==Mesh::_TGL_V4F) {
		LinkArray<vector4f> vectors = p_mesh->vector<vector4f>();
		arvFunctions.A2FGrow4F(v,vectors.getArray(),st,vectors.getStep(),count);
		arvFunctions.A4FMatrixTransform(vectors.getArray(),p_matrixf.m,vectors.getArray(),vectors.getStep(),vectors.getStep(),count);
	}
}

void ModellerMesh::addArray(Vector<vector3f> * arr,unsigned int from,unsigned int count)
{
	if (from>arr->count()) from=0;
	if (count<=0) count=arr->count();
	if (arr->count()-from<count) count=arr->count()-from;
	p_mesh->resizeVertex(p_mesh->p_elementCount+count);

	vector3f *v=&(*arr)[from];
	unsigned int st=arr->sizeOfType();
	unsigned int type=p_mesh->getVectorType();
	matrix4f p_matrixf(p_matrix);
	vector4f vr4f(0.0f,0.0f,0.0f,1.0f);
	if (type==Mesh::_TGL_V2F) {
		LinkArray<vector2f> vectors = p_mesh->vector<vector2f>();
		//bt::arrFunctions.A3FPack2F(&(*arr)[from],vectors.getArray(),,vectors.getStep(),count);
		for (unsigned int i = 0; i < count; ++i) {
			vr4f.x=v->x;
			vr4f.y=v->y;
			vr4f.z=v->z;
			vectors[i]=p_matrixf.transform(vr4f);
			v++;
		}
	}
	if (type==Mesh::_TGL_V3F) {
		LinkArray<vector3f> vectors = p_mesh->vector<vector3f>();
		arvFunctions.A3FMatrixTransform(v,p_matrixf.m,vectors.getArray(),st,vectors.getStep(),count);
	}
	if (type==Mesh::_TGL_V4F) {
		LinkArray<vector4f> vectors = p_mesh->vector<vector4f>();
		arvFunctions.A3FGrow4F(v,vectors.getArray(),st,vectors.getStep(),count);
		arvFunctions.A4FMatrixTransform(vectors.getArray(),p_matrixf.m,vectors.getArray(),vectors.getStep(),vectors.getStep(),count);
	}
}

void ModellerMesh::setTextures(Vector<vector2f> * arr,unsigned int from,unsigned int count)
{
	if (from>arr->count()) from=0;
	if (count<=0) count=arr->count();
	if (arr->count()-from<count) count=arr->count()-from;
	unsigned int type=p_mesh->getTexType(0);

	vector2f *v=&(*arr)[from];
	if (type==Mesh::_TGL_0T2F) {
		LinkArray<vector2f> texture = p_mesh->texture0<vector2f>();
		for (unsigned int i = 0; i < count; ++i) {
			texture[i]=*v;
			v++;
		}
	}
	if (type==Mesh::_TGL_0T3F) {
		LinkArray<vector3f> texture = p_mesh->texture0<vector3f>();
		arvFunctions.A2FGrow3F(v,texture.getArray(),sizeof(vector2f),texture.getStep(),count);
	}
	if (type==Mesh::_TGL_0T4F) {
		LinkArray<vector4f> texture = p_mesh->texture0<vector4f>();
		arvFunctions.A2FGrow4F(v,texture.getArray(),sizeof(vector2f),texture.getStep(),count);
	}
}

void ModellerMesh::setColor(unsigned int from,unsigned int count)
{
	unsigned int type=p_mesh->getColorType();

	LinkArray<int>::iterator color = p_mesh->color<int>().begin();
	unsigned int elc=p_mesh->elementsCount();
	if (from>elc) return;
	if (from+count>elc) count=elc-from;
	color+=from;
	if (type==Mesh::_TGL_C3F) {
		for (unsigned int i = 0; i < count; ++i) {
			vecFunctions.V3R32Copy(&p_color,&(color.value()));
			color++;
		}
	}
	if (type==Mesh::_TGL_C4F) {
		for (unsigned int i = 0; i < count; ++i) {
			vecFunctions.V4R32Copy(&p_color,&(color.value()));
			color++;
		}
	}
}

void ModellerMesh::addByTess(void * tess)
{
	TessData *mtess=(TessData *)tess;

	unsigned int countv=mtess->p_vectors.count();

	addArray(&mtess->p_vectors,0,-1);

	unsigned int type;

	setColor(0,countv);

	type=p_mesh->getTexType(0);
	if (type>0) {
		if (type==Mesh::_TGL_0T2F) {
			LinkArray<vector2f> textures = p_mesh->texture0<vector2f>();
			vector2f val(0.75f);
			for (unsigned int i = 0; i < countv; ++i) {
				textures[i]=val;
			}
		}
	}
	
	unsigned int count=mtess->p_result.size();
	p_mesh->resizeIndex(p_mesh->p_indexCount+mtess->p_result.count());
	for (unsigned int i = 0; i < count; ++i) {
		p_mesh->setIndex(i,mtess->p_result[i]);
	}
}

void ModellerMesh::quad(float width,float height,float bsmooth)
{
	width=width*0.5f;
	height=height*0.5f;

	GeometryPath2F pathf;
	GeometryPath<vector2f> *tpathf=(GeometryPath<vector2f> *)&pathf;
	Vector<vector2f> &rez=tpathf->vectors();
	rez.resize(4);
	tpathf->poligonSize().assign(4);
	vector2f *p1=&rez[0];

	*p1=vector2f(width,height);
	p1++;
	*p1=vector2f(-width,height);
	p1++;
	*p1=vector2f(-width,-height);
	p1++;
	*p1=vector2f(width,-height);
	p1++;

	if (bsmooth!=0) {
		stroker(&pathf,bsmooth,bsmooth*0.5f);
	} else {
		addArray(&rez,0,0);

		unsigned int type=p_mesh->getTexType(0);
		if (type>0) {
			if (type==Mesh::_TGL_0T2F) {
				LinkArray<vector2f> textures = p_mesh->texture0<vector2f>();
				vector2f val(0.75f);
				for (unsigned int i = 0; i < 4; ++i) {
					textures[i]=val;
				}
			}
		}

		type=p_mesh->getColorType();
		if (type>0) {
			if (type==Mesh::_TGL_C4F) {
				LinkArray<vector4f> colors = p_mesh->color<vector4f>();
				for (unsigned int i = 0; i < 4; ++i) {
					colors[i]=p_color;
				}
			}
		}
	}

	p_mesh->resizeIndex(p_mesh->p_indexCount+6);
	GlIndex * p = (GlIndex *)p_mesh->p_index;
	p[0]=0;
	p[1]=1;
	p[2]=2;
	p[3]=0;
	p[4]=2;
	p[5]=3;

}

void ModellerMesh::circle(float radius,unsigned int cells,float start,float end)
{
	if (cells<2) return;
	int count=cells+1;

	Vector<vector2f> rez(count);

	bool section=start!=end;

	unsigned int subcells=cells;
	if (section) {
		subcells=cells-1;
		if (end>180) {
			start-=360;
			end-=360;
		}
	} else {
		start=-180;
		end=180;
	}

	float deg=(float)((end-start)*PI180/subcells);
	float grad=(float)(start*PI180);
	vector2f vr2f(0.0f);
	rez[0]=vr2f;
	int id=1;
	for (unsigned int i=0;i<cells;i++) {
		matFunctions.FSinCos(grad,&vr2f.x,&vr2f.y);
		rez[id]=vr2f*radius;
		id++;
		grad+=deg;
	}

	addArray(&rez,0,0);

	p_mesh->resizeIndex(p_mesh->p_indexCount+subcells*6);
	GlIndex * p = (GlIndex *)p_mesh->p_index;
	for (unsigned int i=0;i<subcells;i++) {
		p[i*3]=i;
		p[i*3+1]=i+cells;
		p[i*3+2]=(i+1);
	}
}

void ModellerMesh::sphere(float radius,unsigned int wcells,unsigned int hcells)
{
	//p_mesh->v
}

void ModellerMesh::strokedCircle(float radius,float width,unsigned int cells,float start,float end,float bsmooth)
{
	if (cells<2) return;
	unsigned int count=cells*2;

	GeometryPath2F pathf;
	GeometryPath<vector2f> *tpathf=(GeometryPath<vector2f> *)&pathf;
	Vector<vector2f> &rez=tpathf->vectors();
	rez.resize(count);
	tpathf->poligonSize().assign(count);

	bool section=start!=end;

	unsigned int subcells=cells;
	if (section) {
		subcells=cells-1;
		if (end>180) {
			start-=360;
			end-=360;
		}
	} else {
		start=-180;
		end=180;
	}

	float low=radius-width*0.5f;
	float hi=radius+width*0.5f;
	float deg=(float)((end-start)*PI180/subcells);
	float grad=(float)(start*PI180);
	vector2f vr2f(0.0f);

	int id=0;
	for (unsigned int i=0;i<cells;i++) {
		matFunctions.FSinCos(grad,&vr2f.x,&vr2f.y);
		rez[id]=vr2f*low;
		id++;
		rez[cells*2-id]=vr2f*hi;
		grad+=deg;
	}

	if (bsmooth!=0) {
		stroker(&pathf,bsmooth,bsmooth*0.5f);
	} else {
		addArray(&rez,0,0);

		unsigned int type=p_mesh->getTexType(0);
		if (type>0) {
			if (type==Mesh::_TGL_0T2F) {
				LinkArray<vector2f> textures = p_mesh->texture0<vector2f>();
				vector2f val(0.75f);
				for (unsigned int i = 0; i < count; ++i) {
					textures[i]=val;
				}
			}
		}

		type=p_mesh->getColorType();
		if (type>0) {
			if (type==Mesh::_TGL_C4F) {
				LinkArray<vector4f> colors = p_mesh->color<vector4f>();
				for (unsigned int i = 0; i < count; ++i) {
					colors[i]=p_color;
				}
			}
		}
	}

	p_mesh->resizeIndex(p_mesh->p_indexCount+subcells*6);
	GlIndex * p = (GlIndex *)p_mesh->p_index;
	for (unsigned int i=0;i<subcells;i++) {
		p[i*6]=i;
		p[i*6+1]=cells*2-1-i;
		p[i*6+2]=(i+1);
		if (p[i*6+2]>=cells) p[i*6+2]=0;
		p[i*6+3]=p[i*6+2];
		p[i*6+4]=p[i*6+1];
		p[i*6+5]=cells*2-1-p[i*6+2];
	}

}

void ModellerMesh::stroker(GeometryPath2F *path,float width,float offset)
{
	GeometryPath<vector2f> *tpathf=(GeometryPath<vector2f> *)path;
	unsigned int poligons=tpathf->poligonSize().size();
	vector2f *vectorsp=tpathf->vectors().data();
	int first=0;
	int id=0;

	unsigned int allv=0;
	unsigned int alli=0;

	for (unsigned int i=0; i<poligons;i++) {
		unsigned int vectorc=tpathf->poligonSize()[i];
		bool poligon=vectorsp[vectorc-1]==vectorsp[0];
		if (poligon) vectorc--;
		allv+=vectorc;
		if (!poligon) vectorc--;
		alli+=vectorc;
	}

	vector2f v1;
	vector2f v2;
	vector2f v3;
	vector2f v4;

	width=width*0.5f;

	Vector<vector2f> rez(allv*2);

	for (unsigned int i=0; i<poligons;i++) {
		unsigned int vectorc=tpathf->poligonSize()[i];
		unsigned int s;
		int t;
		bool poligon=vectorsp[vectorc-1]==vectorsp[0];
		if (poligon) vectorc--;
		for (unsigned int j=0; j<vectorc;j++) {
			s=(j+1);
			t=(j-1);
			if (poligon) {
				if (s>=vectorc) s=0;
				if (t<0) t=vectorc-1;
			} else {
				if (s>=vectorc) s=vectorc-1;
				if (t<0) t=0;
			}
			v1=vector2f(vectorsp[first+j]);
			v2=vector2f(vectorsp[first+s]);
			v3=vector2f(vectorsp[first+t]);
			v2=v2-v1;
			v3=v1-v3;
			float qqd=v2.sqrLen();
			if (qqd!=0) {
				qqd=matFunctions.FFastInvSqrt(v2.sqrLen());
			}
			float qqg=v3.sqrLen();
			if (qqg!=0) {
				qqg=matFunctions.FFastInvSqrt(v3.sqrLen());
			}
			v2=v2*qqd;
			v3=v3*qqg;
			if (qqd==0) v2=v3;
			if (qqg==0) v3=v2;
			v4=v2+v3;
			float qqf=v4.sqrLen();
			float f=1.0f;
			if (qqf>0.1) {
				qqf=matFunctions.FFastInvSqrt(qqf);
				v4=v4*qqf;
				f=v2.dot(v4);
				if (f!=0) f=1.0f/f;
				v4=vector2f(-v4.y,v4.x);
			} else {
				v4=vector2f(-v2.y,v2.x);
			}

			v2=v4*((-width+offset)*f);
			v3=v4*((width+offset)*f);

			rez[id]=v1+v2;
			rez[id+allv]=v1+v3;
			id++;
		}
		first+=vectorc;
	}

	addArray(&rez,0,0);

	unsigned int type=p_mesh->getTexType(0);
	if (type>0) {
		if (type==Mesh::_TGL_0T2F) {
			LinkArray<vector2f> textures = p_mesh->texture0<vector2f>();
			vector2f val1(0.75f);
			vector2f val2(0.25f);
			for (unsigned int i = 0; i < allv; ++i) {
				textures[i]=val1;
				textures[i+allv]=val2;
			}
		}
	}

	type=p_mesh->getColorType();
	if (type>0) {
		LinkArray<vector4f> colors = p_mesh->color<vector4f>();
		vector4f alfac=p_color;
		alfac.w=0;
		for (unsigned int i = 0; i < allv; ++i) {
			colors[i]=p_color;
			colors[i+allv]=alfac;
		}
	}

	first=0;
	p_mesh->resizeIndex(p_mesh->p_indexCount+alli*6);
	GlIndex * p = (GlIndex *)p_mesh->p_index;
	for (unsigned int i = 0; i < poligons; ++i) {
		unsigned int vectorc=tpathf->poligonSize()[i];
		bool poligon=vectorsp[vectorc-1]==vectorsp[0];
		vectorc--;
		int id2;
		for (unsigned int j = 0; j < vectorc; ++j) {
			id=first+j;
			id2=first+j+1;
			if (poligon && j==vectorc-1) id2=first;
			p[id*6]=id;
			p[id*6+1]=id2;
			p[id*6+2]=id+allv;
			p[id*6+3]=id2;
			p[id*6+4]=id2+allv;
			p[id*6+5]=id+allv;
		}
		first+=vectorc;
	}
}

void ModellerMesh::fill(GeometryPath2F *path,float bsmooth)
{
	unsigned int df=p_mesh->p_drawFormat & csad::Mesh::_GL_MASK;
	if (df!=csad::Mesh::_GL_TRIANGLES) return;
	GeometryPath<vector2f> *tpathf=(GeometryPath<vector2f> *)path;
	CPUTriangulator triangulator;
	triangulator.initialize(tpathf->vectors().data(),tpathf->poligonSize().data(),tpathf->poligonSize().count());
	triangulator.triangulate();

	addByTess(&triangulator.getTessData()); // possible optimise with stroker

	if (bsmooth!=0) {

		stroker(path,bsmooth,bsmooth*0.5f);

	}
}

void ModellerMesh::textTexture(char *text,TextStyle *style,float z)
{
	if (!style) return;
	if (!style->getFont()) return;
	unsigned int df=p_mesh->p_drawFormat & csad::Mesh::_GL_MASK;
	if (df!=csad::Mesh::_GL_TRIANGLES && df!=csad::Mesh::_GL_QUADS) return;
	csad::Font *font=style->getFont();
	GeometryPath2F path;
	GeometryPath<vector2f> *tpath=(GeometryPath<vector2f> *)&path;
	GeometryPath2F texture;
	GeometryPath<vector2f> *ftexture=(GeometryPath<vector2f> *)&texture;
	float scale=style->getCharSize();
	float pixels=1.0f/font->getSize();
	float pixelsw=(font->getSize()-1)*pixels;
	float pixelss=(font->getSize()-2)*pixels;
	float height=font->height();

	char *c=(char *)text;
	if (!text) c=(char *)"";
	bt::vector2f tx;
	bt::vector2f vx;
	vx.x=0;
	vx.y=0;
	int size = font->getSize();
	while (*c!=0) {
		if (*c!=32) {
			tx.x=(float)((*c&0xf)*0.0625+(pixels*0.0625));
			tx.y=(float)((*c>>4)*0.0625+(pixelsw*0.0625));
			tpath->addVector(vx,true);
			ftexture->addVector(tx,true);
			tx.y-=(pixelss*0.0625f);
			vx.y+=size*pixelss;
			tpath->addVector(vx,false);
			ftexture->addVector(tx,false);
			tx.x+=(pixelss*0.0625f);
			vx.x+=size*pixelss;
			tpath->addVector(vx,false);
			ftexture->addVector(tx,false);
			tx.y+=(pixelss*0.0625f);
			vx.y-=size*pixelss;
			tpath->addVector(vx,false);
			ftexture->addVector(tx,false);
			vx.x-=size*pixelss;
		}
		float wsize=font->width(*(unsigned char*)c);
		vx.x+=matFunctions.FTrunc(wsize*style->getKerning());
		c++;
	}

	vector3d pos(0.0);
	if ((style->getAnchor()==TextStyle::Right_Bottom) ||
			(style->getAnchor()==TextStyle::Right_Center) ||
			(style->getAnchor()==TextStyle::Right_Top)) pos.x=(float)-vx.x;
	if ((style->getAnchor()==TextStyle::Bottom) ||
			(style->getAnchor()==TextStyle::Center) ||
			(style->getAnchor()==TextStyle::Top)) pos.x=-vx.x*0.5f;

	if ((style->getAnchor()==TextStyle::Center) ||
			(style->getAnchor()==TextStyle::Right_Center) ||
			(style->getAnchor()==TextStyle::Left_Center)) pos.y=-height*0.5f;
	if ((style->getAnchor()==TextStyle::Top) ||
			(style->getAnchor()==TextStyle::Right_Top) ||
			(style->getAnchor()==TextStyle::Left_Top)) pos.y=-height;

	pos.z=z;

	matrix4d pm = p_matrix;

	vector3d mscale(scale);
	vecFunctions.M4DAddScale(&p_matrix,&mscale,&p_matrix);
	vecFunctions.M4DAddTranslate(&p_matrix,&pos,&p_matrix);

	addArray(&tpath->vectors(),0,tpath->count());
	setTextures(&ftexture->vectors(),0,ftexture->count());
	setColor(0,tpath->count());

	int count=tpath->count()>>2;
	if (df==csad::Mesh::_GL_TRIANGLES) {
		p_mesh->resizeIndex(p_mesh->p_indexCount+count*6);
		for (int i=0;i<count;i++) {
			int ic=((i<<1)+i)<<1;
			int iv=i<<2;
			p_mesh->setIndexTri(ic,iv,iv+2,iv+1);
			p_mesh->setIndexTri(ic+3,iv+2,iv,iv+3);
		}
	} else {
		p_mesh->resizeIndex(p_mesh->p_indexCount+count*4);
		for (int i=0;i<count;i++) {
			int ic=((i<<1)+i)<<1;
			int iv=i<<2;
			p_mesh->setIndexQuad(ic,iv,iv+1,iv+2,iv+3);
		}
	}

	p_matrix=pm;
}

void ModellerMesh::textFlat(char *text,TextStyle *style,float z,float bsmooth)
{
	if (!style) return;
	if (!style->getFont()) return;
	unsigned int df=p_mesh->p_drawFormat & csad::Mesh::_GL_MASK;
	if (df!=csad::Mesh::_GL_TRIANGLES) return;
	csad::Font *font=style->getFont();
	//GeometryPath2I path;
	//GeometryPath<vector2i> *tpath=(GeometryPath<vector2i> *)&path;
	float scale=style->getCharSize();
	float height=style->getFont()->height();

	GeometryPath2F pathf;
	GeometryPath<vector2f> *tpathf=(GeometryPath<vector2f> *)&pathf;
	int x=genFunctions.FaceText(tpathf,font,text,0,0,style->getKerning(),0);

	/*char *c=(char *)text;
	if (!text) c=(char *)"";
	int x=0;
	while (*c!=0) {
		int size = matFunctions.FTrunc(font->addOutLine(x, 0, *c, &path));
		x += matFunctions.FTrunc(size*style->getKerning());
		c++;
	}*/

	vector3d pos(0.0);
	if ((style->getAnchor()==TextStyle::Right_Bottom) ||
			(style->getAnchor()==TextStyle::Right_Center) ||
			(style->getAnchor()==TextStyle::Right_Top)) pos.x=(float)-x;
	if ((style->getAnchor()==TextStyle::Bottom) ||
			(style->getAnchor()==TextStyle::Center) ||
			(style->getAnchor()==TextStyle::Top)) pos.x=-x*0.5f;

	if ((style->getAnchor()==TextStyle::Center) ||
			(style->getAnchor()==TextStyle::Right_Center) ||
			(style->getAnchor()==TextStyle::Left_Center)) pos.y=-height*0.5f;
	if ((style->getAnchor()==TextStyle::Top) ||
			(style->getAnchor()==TextStyle::Right_Top) ||
			(style->getAnchor()==TextStyle::Left_Top)) pos.y=-height;

	pos.z=z;

	matrix4d pm = p_matrix;

//	matrix4d m;
	vector3d mscale(scale);
	vecFunctions.M4DAddScale(&p_matrix,&mscale,&p_matrix);
//	p_matrix=p_matrix*m;
	vecFunctions.M4DAddTranslate(&p_matrix,&pos,&p_matrix);
	//p_matrix=p_matrix*m;

	/*unsigned int poligons=tpath->poligonSize().size();
	unsigned int vectorsc=0;
	int first=0;
	unsigned int count=0;

	for (unsigned int j=0;j<poligons;j++) {
		vectorsc=tpath->poligonSize()[j];
		count=vectorsc;
		vector2f v=tpath->vectors()[first];
		if (v==tpath->vectors()[count-1]) count--;
		tpathf->addVector(v,true);
		for (unsigned int i=1;i<count;i++) {
			v=tpath->vectors()[i+first];
			tpathf->addVector(v,false);
		}
		first+=vectorsc;
	}*/

	CPUTriangulator triangulator;
	triangulator.initialize(tpathf->vectors().data(),tpathf->poligonSize().data(),tpathf->poligonSize().count());
	triangulator.triangulate();

	addByTess(&triangulator.getTessData()); // possible optimise with stroker

	if (bsmooth!=0) {

		bsmooth=bsmooth/scale;

		stroker(&pathf,bsmooth,bsmooth*0.5f);

	}

	p_matrix=pm;
}

void ModellerMesh::textExtrude(char *text,TextStyle *style,float z,float )
{
	if (!style) return;
	if (!style->getFont()) return;
	csad::Font *font=style->getFont();
	GeometryPath2I path;
	GeometryPath<vector2i> *tpath=(GeometryPath<vector2i> *)&path;
	float scale=style->getCharSize();
	float height=style->getFont()->height();

	GeometryPath2F pathf;
	GeometryPath<vector2f> *tpathf=(GeometryPath<vector2f> *)&pathf;
	int x=genFunctions.FaceText(tpathf,font,text,0,0,style->getKerning(),0);

	/*char *c=(char *)text;
	if (!text) c=(char *)"";
	int x=0;
	while (*c!=0) {
		int size = matFunctions.FTrunc(font->addOutLine(x, 0, *c, &path));
		x += matFunctions.FTrunc(size*style->getKerning());
		c++;
	}*/

	vector3d pos(0.0);
	if ((style->getAnchor()==TextStyle::Right_Bottom) ||
			(style->getAnchor()==TextStyle::Right_Center) ||
			(style->getAnchor()==TextStyle::Right_Top)) pos.x=(float)-x;
	if ((style->getAnchor()==TextStyle::Bottom) ||
			(style->getAnchor()==TextStyle::Center) ||
			(style->getAnchor()==TextStyle::Top)) pos.x=-x*0.5f;

	if ((style->getAnchor()==TextStyle::Center) ||
			(style->getAnchor()==TextStyle::Right_Center) ||
			(style->getAnchor()==TextStyle::Left_Center)) pos.y=-height*0.5f;
	if ((style->getAnchor()==TextStyle::Top) ||
			(style->getAnchor()==TextStyle::Right_Top) ||
			(style->getAnchor()==TextStyle::Left_Top)) pos.y=-height;

	pos.z=z;

	matrix4d pm = p_matrix;

	vector3d mscale(scale);
	vecFunctions.M4DAddScale(&p_matrix,&mscale,&p_matrix);
	vecFunctions.M4DAddTranslate(&p_matrix,&pos,&p_matrix);

	/*GeometryPath2F pathf;
	GeometryPath<vector2f> *tpathf=(GeometryPath<vector2f> *)&pathf;

	unsigned int poligons=tpath->poligonSize().size();
	unsigned int vectorsc=0;
	int first=0;
	unsigned int count=0;

	for (unsigned int j=0;j<poligons;j++) {
		vectorsc=tpath->poligonSize()[j];
		count=vectorsc;
		vector2f v=tpath->vectors()[first];
		if (v==tpath->vectors()[count-1]) count--;
		tpathf->addVector(v,true);
		for (unsigned int i=1;i<count;i++) {
			v=tpath->vectors()[i+first];
			tpathf->addVector(v,false);
		}
		first+=vectorsc;
	}*/

	CPUTriangulator triangulator;
	triangulator.initialize(tpathf->vectors().data(),tpathf->poligonSize().data(),tpathf->poligonSize().count());
	triangulator.triangulate();

	addByTess(&triangulator.getTessData()); // possible optimise with stroker

	p_matrix=pm;
}

}

OPTIMIZE_OFF;
