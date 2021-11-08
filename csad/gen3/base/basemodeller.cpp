/*
 * basemodeller.h
 *
 *  @brief core, 2003-2014
 *
 *  Created on: 12.04.2008
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include "basemodeller.h"
#include "basegen.h"
#include <bt.h>
#include <gen3.h>
#include <scene/mesh.h>

OPTIMIZE_ON;

namespace gen {

	void* _APICALL _CreateLoftDEF()
	{
		return new gen::GeometryPath<bt::vector4f>();
	}

	void _APICALL _LoftAddDEF(void *loft,float x,float y,float z,float w,_int32 flag)
	{
		gen::GeometryPath<bt::vector4f>* aloft=(gen::GeometryPath<bt::vector4f>*)loft;
		aloft->addVector(bt::vector4f(x,y,z,w),(flag&1)!=0);
	}

	void _APICALL _FreeLoftDEF(void*loft)
	{
		delete (gen::GeometryPath<bt::vector3f>*)loft;
	}

	void* _APICALL _CloneMeshDEF(void *mesh)
	{
		csad::Mesh *amesh=(csad::Mesh *)mesh;
		csad::Mesh *newMesh=new csad::Mesh();
		newMesh->setDrawFormat(amesh->getDrawFormat()).setFields(amesh->getFields());
		newMesh->setIndexCount(amesh->indexCount()).setVertexCount(amesh->elementsCount());
		extFunctions.MoveMem(amesh->indexs(),newMesh->indexs(),newMesh->indexCount()*newMesh->getIndexSize());
		extFunctions.MoveMem(amesh->elements(),newMesh->elements(),newMesh->elementsCount()*newMesh->elementSize());
		return newMesh;
	}

	void _APICALL _FreeMeshDEF(void *mesh)
	{
		csad::Mesh *amesh=(csad::Mesh *)mesh;
		delete amesh;
	}

	void _APICALL _MeshColorDEF(void *mesh,unsigned _int32 color)
	{
		csad::Mesh *amesh=(csad::Mesh *)mesh;
		unsigned int type=amesh->getColorType();
		unsigned int count=amesh->elementsCount();
		bt::vector4f acolor;
		vecFunctions.V4BTo4F(&color,&acolor);
		vecFunctions.V4FScale(&acolor,&acolor,0.0039215686274509803921568627451f);

		if (type==Mesh::_TGL_C3F) {
			LinkArray<vector3f>::iterator color = amesh->color<vector3f>().begin();
			for (unsigned int i = 0; i < count; ++i) {
				color=acolor;
				color++;
			}
		}
		if (type==Mesh::_TGL_C4F) {
			LinkArray<vector4f>::iterator color = amesh->color<vector4f>().begin();
			for (unsigned int i = 0; i < count; ++i) {
				color=acolor;
				color++;
			}
		}
	}

	void _APICALL _MeshGradientDEF(void *mesh,float x,float y,float rx,float ry,float s,unsigned _int32 colora,unsigned _int32 colorb)
	{
		csad::Mesh *amesh=(csad::Mesh *)mesh;
		unsigned int type=amesh->getColorType();
		unsigned int typev=amesh->getVectorType();
		unsigned int count=amesh->elementsCount();
		bt::vector4f acolor;
		bt::vector4f bcolor;
		vecFunctions.V4BTo4F(&colora,&acolor);
		vecFunctions.V4BTo4F(&colorb,&bcolor);
		vecFunctions.V4FScale(&acolor,&acolor,0.0039215686274509803921568627451f);
		vecFunctions.V4FScale(&bcolor,&bcolor,0.0039215686274509803921568627451f);

		bt::vector3d vrot(rx,ry,0.0);
		bt::vector2d vtr(x,y);
		bt::vector2f vtrf;
		bt::quaterniond rot;
		bt::quaterniond rotf;
		bt::matrix4d amtr;
		vecFunctions.V2DScale(&vrot,&vrot,PI180);
		vecFunctions.QDEuler(&vrot,&rot);
		vecFunctions.V4DTo4F(&rot,&rotf);
		vecFunctions.V2DTo2F(&vtr,&vtrf);
		//vecFunctions.M4DTRS(&amtr,&vtr,&vrot);

		LinkArray<vector4f>::iterator color = amesh->color<vector4f>().begin();
		float minmax[2]={0.0f,1.0f};

		bt::vector4f vecf;
		LinkArray<int>::iterator vector = amesh->vector<int>().begin();
		if (typev==Mesh::_TGL_V2F) {
			for (unsigned int i = 0; i < count; ++i) {
				vecFunctions.Q2FInvTransform(&rotf,&vector.value(),&vecf);
				vecFunctions.V2FSub(&vecf,&vtrf,&vecf);
				vecf.x=vecf.x*s;
				matFunctions.FMinMax(minmax,minmax,&vecf.x);
				matFunctions.FMinMax(minmax+1,&vecf.x,minmax+1);
				if (type==Mesh::_TGL_C3F) vecFunctions.V3FLerp(&acolor,&bcolor,&(color.value()),vecf.x);
				if (type==Mesh::_TGL_C4F) vecFunctions.V4FLerp(&acolor,&bcolor,&(color.value()),vecf.x);
				color++;
				vector++;
			}
		}
		if (typev==Mesh::_TGL_V3F) {
			for (unsigned int i = 0; i < count; ++i) {
				vecFunctions.Q3FInvTransform(&rotf,&vector.value(),&vecf);
				vecFunctions.V2FSub(&vecf,&vtrf,&vecf);
				vecf.x=vecf.x*s;
				matFunctions.FMinMax(minmax,minmax,&vecf.x);
				matFunctions.FMinMax(minmax+1,&vecf.x,minmax+1);
				if (type==Mesh::_TGL_C3F) vecFunctions.V3FLerp(&acolor,&bcolor,&(color.value()),vecf.x);
				if (type==Mesh::_TGL_C4F) vecFunctions.V4FLerp(&acolor,&bcolor,&(color.value()),vecf.x);
				color++;
				vector++;
			}
		}

		/*LinkArray<vector4f>::iterator color = amesh->color<vector4f>().begin();
		if (typev==Mesh::_TGL_V2F) {
		}
		if (typev==Mesh::_TGL_V3F) {
			LinkArray<vector3f>::iterator vector = amesh->vector<vector3f>().begin();
			for (unsigned int i = 0; i < count; ++i) {
				color=acolor;
				color++;
			}
		}*/
	}

	void _APICALL _MeshTranslateDEF(void *mesh,float x,float y,float z)
	{
		csad::Mesh *amesh=(csad::Mesh *)mesh;
		bt::vector3d tr(x,y,z);
		bt::vector3f trf;

		vecFunctions.V3DTo3F(&tr,&trf);

		int count=amesh->elementsCount();

		unsigned int vtype=amesh->getVectorType();
		if (vtype==csad::Mesh::_TGL_V2F) {
			LinkArray<vector2f>::iterator vector = amesh->vector<vector2f>().begin();
			arvFunctions.A2FAddVector(&vector.value(),&trf,&vector.value(),vector.step(),vector.step(),count);
		}
		if (vtype==csad::Mesh::_TGL_V3F || vtype==csad::Mesh::_TGL_V4F) {
			LinkArray<vector3f>::iterator vector = amesh->vector<vector3f>().begin();
			arvFunctions.A3FAddVector(&vector.value(),&trf,&vector.value(),vector.step(),vector.step(),count);
		}
		if (vtype==csad::Mesh::_TGL_V2D) {
			LinkArray<vector2d>::iterator vector = amesh->vector<vector2d>().begin();
			arvFunctions.A2DAddVector(&vector.value(),&tr,&vector.value(),vector.step(),vector.step(),count);
		}
		if (vtype==csad::Mesh::_TGL_V3D || vtype==csad::Mesh::_TGL_V4D) {
			LinkArray<vector3d>::iterator vector = amesh->vector<vector3d>().begin();
			arvFunctions.A3DAddVector(&vector.value(),&tr,&vector.value(),vector.step(),vector.step(),count);
		}
	}

	void _APICALL _MeshRotateDEF(void *mesh,float x,float y,float z)
	{
		csad::Mesh *amesh=(csad::Mesh *)mesh;
		bt::vector3d euler(x,y,z);
		vecFunctions.V3DScale(&euler,&euler,PI180);
		bt::quaterniond rot;
		vecFunctions.QDEuler(&euler,&rot);

		bt::quaternionf rotf;
		vecFunctions.V4DTo4F(&rot,&rotf);

		int count=amesh->elementsCount();

		unsigned int vtype=amesh->getVectorType();
		LinkArray<int>::iterator vector = amesh->vector<int>().begin();
		if (vtype==csad::Mesh::_TGL_V2F) {
			while (count>0) {
				vecFunctions.Q2FInvTransform(&rotf,&vector.value(),&vector.value());
				vector++;
				count--;
			}
		}
		if (vtype==csad::Mesh::_TGL_V3F || vtype==csad::Mesh::_TGL_V4F) {
			while (count>0) {
				vecFunctions.Q3FInvTransform(&rotf,&(vector.value()),&(vector.value()));
				vector++;
				count--;
			}
		}
		if (vtype==csad::Mesh::_TGL_V2D) {
			while (count>0) {
				vecFunctions.Q2DInvTransform(&rotf,&vector.value(),&vector.value());
				vector++;
				count--;
			}
		}
		if (vtype==csad::Mesh::_TGL_V3D || vtype==csad::Mesh::_TGL_V4D) {
			while (count>0) {
				vecFunctions.Q3DInvTransform(&rotf,&vector.value(),&vector.value());
				vector++;
				count--;
			}
		}
	}

	void _APICALL _MeshScaleDEF(void *mesh,float x,float y,float z)
	{
		csad::Mesh *amesh=(csad::Mesh *)mesh;
		bt::vector3d sc(x,y,z);
		bt::vector3f scf;

		vecFunctions.V3DTo3F(&sc,&scf);

		int count=amesh->elementsCount();

		unsigned int vtype=amesh->getVectorType();
		if (vtype==csad::Mesh::_TGL_V2F) {
			LinkArray<vector2f>::iterator vector = amesh->vector<vector2f>().begin();
			arvFunctions.A2FMulVector(&vector.value(),&scf,&vector.value(),vector.step(),vector.step(),count);
		}
		if (vtype==csad::Mesh::_TGL_V3F || vtype==csad::Mesh::_TGL_V4F) {
			LinkArray<vector3f>::iterator vector = amesh->vector<vector3f>().begin();
			arvFunctions.A3FMulVector(&vector.value(),&scf,&vector.value(),vector.step(),vector.step(),count);
		}
		if (vtype==csad::Mesh::_TGL_V2D) {
			LinkArray<vector2d>::iterator vector = amesh->vector<vector2d>().begin();
			arvFunctions.A2DMulVector(&vector.value(),&sc,&vector.value(),vector.step(),vector.step(),count);
		}
		if (vtype==csad::Mesh::_TGL_V3D || vtype==csad::Mesh::_TGL_V4D) {
			LinkArray<vector3d>::iterator vector = amesh->vector<vector3d>().begin();
			arvFunctions.A3DMulVector(&vector.value(),&sc,&vector.value(),vector.step(),vector.step(),count);
		}
	}

	void SetVector3F(void *mesh,void *vec,int from,int to,int count) {
		csad::Mesh *amesh=(csad::Mesh *)mesh;
		bt::Vector<bt::vector3f> *avec=(bt::Vector<bt::vector3f> *)vec;
		bt::vector3f *v=&(*avec)[from];

		unsigned int type=amesh->getVectorType();
		int ccount=amesh->elementsCount()-to;

		if (count>ccount) count=ccount;
		ccount=avec->count()-from;
		if (count>ccount) count=ccount;

		LinkArray<int>::iterator vector = amesh->vector<int>().begin();
		vector+=to;

		if (type==Mesh::_TGL_V2F) arvFunctions.A2FMove(v,&vector.value(),sizeof(bt::vector3f),vector.step(),count);
		if (type==Mesh::_TGL_V3F) arvFunctions.A3FMove(v,&vector.value(),sizeof(bt::vector3f),vector.step(),count);
		if (type==Mesh::_TGL_V4F) arvFunctions.A3FGrow4F(v,&vector.value(),sizeof(bt::vector3f),vector.step(),count);
		if (type==Mesh::_TGL_V2D) arvFunctions.A2FTo2D(v,&vector.value(),sizeof(bt::vector3f),vector.step(),count);
		if (type==Mesh::_TGL_V3D) arvFunctions.A3FTo3D(v,&vector.value(),sizeof(bt::vector3f),vector.step(),count);
	}

	void SetIndex(void *mesh,void *vec,int from,int to,int count,int flag,int add) {
		csad::Mesh *amesh=(csad::Mesh *)mesh;
		bt::Vector<int> *avec=(bt::Vector<int> *)vec;
		int ccount=amesh->indexCount()-to;

		if (count>ccount) count=ccount;
		ccount=avec->count()-from;
		if (count>ccount) count=ccount;

		int *i=(int*)avec->data();
		int isize=amesh->getIndexSize();

		int inc=1;
		if (flag!=0) inc=-1;
		if (isize==2) {
			short *inx=(short *)amesh->indexs();
			inx+=to;
			if (flag!=0) inx+=count-1;
			while (count>0) {
				*inx=*i+add;
				i++;
				inx+=inc;
				count--;
			}
		}

		if (isize==4) {
			int *inx=(int *)amesh->indexs();
			inx+=to;
			if (flag!=0) inx+=count-1;
			while (count>0) {
				*inx=*i+add;
				i++;
				inx+=inc;
				count--;
			}
		}
	}

	void _APICALL _MeshPlaneScaleDEF(void *mesh,float x, float y, float z, float rx, float ry, float r, float zoom)
	{
		csad::Mesh *amesh=(csad::Mesh *)mesh;
		unsigned int type=amesh->getVectorType();
		unsigned int count=amesh->elementsCount();
		bt::matrix4d matrd;
		bt::matrix4f matrf;
		bt::quaterniond rot1(1,0,0,rx*PI180);
		bt::quaterniond rot2(0,1,0,ry*PI180);
		bt::quaterniond rot;
		bt::vector3d vectd(-x,-y,-z);
		bt::vector3f vectf;
		vecFunctions.V3DTo3F(&vectd,&vectf);
		vecFunctions.QDMul(&rot1,&rot2,&rot);
		vecFunctions.Q4DMatrix(&rot,&matrd);
		vecFunctions.M4DAddTranslate(&matrd,&vectd,&matrd);
		vecFunctions.M4DToM4F(&matrd,&matrf);
		double invr=1.0/r;
		
		char rez[32];
		bt::vector4f checkf;
		bt::vector4d checkd;

		bt::LinkArray<int>::iterator it=amesh->vector<int>().begin();

		if (type==csad::Mesh::_TGL_V2F) {
			while (count>0) {
				void *val=&it.value();
				vecFunctions.V2FTransform(val,&matrf,&checkf);
				vecFunctions.V2FAdd(val,&vectf,&rez);
				vecFunctions.V2FScale(&rez,&rez,zoom);
				vecFunctions.V3FSub(&rez,&vectf,&rez);
				if (checkf.z<0) checkf.z=-checkf.z;
				float m=(float)(1.0f-checkf.y*invr);
				if (m>0.0) vecFunctions.V2FLerp(val,&rez,val,m);
				it++;
				count--;
			}
		}
		if (type==csad::Mesh::_TGL_V3F || type==csad::Mesh::_TGL_V4F) {
			while (count>0) {
				void *val=&it.value();
				vecFunctions.V3FTransform(val,&matrf,&checkf);
				vecFunctions.V3FAdd(val,&vectf,&rez);
				vecFunctions.V3FScale(&rez,&rez,zoom);
				vecFunctions.V3FSub(&rez,&vectf,&rez);
				if (checkf.z<0) checkf.z=-checkf.z;
				float m=(float)(1.0f-checkf.z*invr);
				if (m>0.0) vecFunctions.V3FLerp(val,&rez,val,m);
				it++;
				count--;
			}
		}
		if (type==csad::Mesh::_TGL_V2D) {
			while (count>0) {
				void *val=&it.value();
				vecFunctions.V2DTransform(val,&matrd,&checkd);
				vecFunctions.V2DAdd(val,&vectd,&rez);
				vecFunctions.V2DScale(&rez,&rez,zoom);
				vecFunctions.V2DAdd(&rez,&vectd,&rez);
				if (checkd.z<0) checkd.z=-checkd.z;
				double m=(1.0f-checkd.y*invr);
				if (m>0.0) vecFunctions.V2DLerp(val,&rez,val,m);
				it++;
				count--;
			}
		}
		if (type==csad::Mesh::_TGL_V3D || type==csad::Mesh::_TGL_V4D) {
			while (count>0) {
				void *val=&it.value();
				vecFunctions.V3DTransform(val,&matrd,&checkd);
				vecFunctions.V3DAdd(val,&vectd,&rez);
				vecFunctions.V3DScale(&rez,&rez,zoom);
				vecFunctions.V2DAdd(&rez,&vectd,&rez);
				if (checkd.z<0) checkd.z=-checkd.z;
				double m=1.0-checkd.z*invr;
				if (m>0.0) vecFunctions.V3DLerp(val,&rez,val,m);
				it++;
				count--;
			}
		}
	}

	void _APICALL _MeshSphereScaleDEF(void *mesh,float x, float y, float z, float r, float zoom,float f)
	{
		csad::Mesh *amesh=(csad::Mesh *)mesh;
		unsigned int type=amesh->getVectorType();
		unsigned int count=amesh->elementsCount();

		bt::LinkArray<int>::iterator it=amesh->vector<int>().begin();

		bt::vector3f trf(x,y,z);
		bt::vector3d trd;
		vecFunctions.V3FTo3D(&trf,&trd);

		bt::vector4f checkf;
		bt::vector4d checkd;

		double rs=r*r;
		double invr=1.0/r;

		if (type==csad::Mesh::_TGL_V3F || type==csad::Mesh::_TGL_V4F) {
			while (count>0) {
				void *val=&it.value();
				vecFunctions.V3FSub(val,&trf,&checkf);
				float l=vecFunctions.V3FLength2(&checkf);
				if (l<rs) {
					l=(float)(matFunctions.FSqrt(l)*invr);
					vecFunctions.V3FScale(&checkf,&checkf,zoom);
					vecFunctions.V3FAdd(&checkf,&trf,&checkf);
					vecFunctions.V3FLerp(&checkf,val,val,l);
				}
				it++;
				count--;
			}
		}

		if (type==csad::Mesh::_TGL_V3D || type==csad::Mesh::_TGL_V4D) {
			while (count>0) {
				void *val=&it.value();
				vecFunctions.V3DSub(val,&trd,&checkd);
				double l=vecFunctions.V3DLength2(&checkd);
				if (l<rs) {
					l=matFunctions.DSqrt(l)*invr;
					vecFunctions.V3DScale(&checkd,&checkd,zoom);
					vecFunctions.V3DAdd(&checkd,&trd,&checkd);
					vecFunctions.V3DLerp(&checkd,val,val,l);
				}
				it++;
				count--;
			}
		}
	}

	void _APICALL _MeshSphereTranslateDEF(void *mesh,float x, float y, float z, float r, float addx, float addy, float addz,float f)
	{
		csad::Mesh *amesh=(csad::Mesh *)mesh;
		unsigned int type=amesh->getVectorType();
		unsigned int count=amesh->elementsCount();

		bt::LinkArray<int>::iterator it=amesh->vector<int>().begin();

		bt::vector3f trf(x,y,z);
		bt::vector3f atrf(addx,addy,addz);
		bt::vector3d trd;
		bt::vector3d atrd;
		vecFunctions.V3FTo3D(&trf,&trd);
		vecFunctions.V3FTo3D(&atrf,&atrd);

		bt::vector4f checkf;
		bt::vector4d checkd;

		double rs=r*r;
		double invr=1.0/r;

		if (type==csad::Mesh::_TGL_V3F || type==csad::Mesh::_TGL_V4F) {
			while (count>0) {
				void *val=&it.value();
				vecFunctions.V3FSub(val,&trf,&checkf);
				float l=vecFunctions.V3FLength2(&checkf);
				if (l<rs) {
					l=(float)(matFunctions.FSqrt(l)*invr);
					vecFunctions.V3FAdd(val,&atrf,&checkf);
					vecFunctions.V3FLerp(&checkf,val,val,l);
				}
				it++;
				count--;
			}
		}

		if (type==csad::Mesh::_TGL_V3D || type==csad::Mesh::_TGL_V4D) {
			while (count>0) {
				void *val=&it.value();
				vecFunctions.V3DSub(val,&trd,&checkd);
				double l=vecFunctions.V3DLength2(&checkd);
				if (l<rs) {
					l=matFunctions.DSqrt(l)*invr;
					vecFunctions.V3DAdd(val,&atrd,&checkd);
					vecFunctions.V3DLerp(&checkd,val,val,l);
				}
				it++;
				count--;
			}
		}
	}

	void _APICALL _MeshFlipDEF(void *mesh,float rx,float ry)
	{
		csad::Mesh *amesh=(csad::Mesh *)mesh;
		unsigned int type=amesh->getVectorType();
		unsigned int count=amesh->elementsCount();

		bt::LinkArray<int>::iterator it=amesh->vector<int>().begin();

		bt::quaterniond rot1(1,0,0,rx*PI180);
		bt::quaterniond rot2(0,1,0,ry*PI180);
		bt::quaterniond rot;
		bt::quaterniond roti;
		bt::quaternionf rotf;
		bt::quaternionf rotif;
		vecFunctions.QDMul(&rot1,&rot2,&rot);
		vecFunctions.QDInv(&rot,&roti);
		vecFunctions.V4DTo4F(&rot,&rotf);
		vecFunctions.V4DTo4F(&roti,&rotif);

		bt::vector4f checkf;
		bt::vector4d checkd;

		if (type==csad::Mesh::_TGL_V3F || type==csad::Mesh::_TGL_V4F) {
			while (count>0) {
				void *val=&it.value();
				vecFunctions.Q3FInvTransform(&rotf,val,&checkf);
				checkf.z=-checkf.z;
				vecFunctions.Q3FInvTransform(&rotif,&checkf,val);
				it++;
				count--;
			}
		}

		if (type==csad::Mesh::_TGL_V3D || type==csad::Mesh::_TGL_V4D) {
			while (count>0) {
				void *val=&it.value();
				vecFunctions.Q3DInvTransform(&rot,val,&checkd);
				checkf.z=-checkf.z;
				vecFunctions.Q3DInvTransform(&roti,&checkd,val);
				it++;
				count--;
			}
		}
		int is=amesh->getIndexSize();
		unsigned int counti=amesh->indexCount();
		if (is==4) {
			int *vali=(int *)amesh->indexs();
			int *valb=vali+counti-1;
			while (valb>vali) {
				int id=*valb;
				*valb=*vali;
				*vali=id;
				valb--;
				vali++;
			}
		}
		if (is==2) {
			short *vali=(short *)amesh->indexs();
			short *valb=vali+counti-1;
			while (valb>vali) {
				int id=*valb;
				*valb=*vali;
				*vali=id;
				valb--;
				vali++;
			}
		}
	}

	/*void InternalTeselator(void *mesh,gen::TessData *tess,int fromi,int fromv)
	{
	}*/

	void _APICALL _MeshExtrudeDEF(void *mesh,void *fase,float exturde,_int32 cels,_int32 flag)
	{
		int acells=cels+1;
		csad::Mesh *bmesh=(csad::Mesh *)mesh;
		csad::Mesh amesh;
		amesh.setFields(bmesh->getFields());
		gen::GeometryPath<bt::vector2f> *afase=(gen::GeometryPath<bt::vector2f>*)fase;
		bt::Vector<bt::vector2f> &list=afase->vectors();

		int countv=0;
		int counti=0;
		int count;
		if ((flag&1)!=0) {
			gen::ListPoligonSize::iterator it=afase->poligonSize().begin();
			gen::ListPoligonSize::iterator end=afase->poligonSize().end();
			
			int first=0;
			while (it!=end) {
				int c=it.value();
				bool circle=list[first]==list[first+c-1];
				first+=c;
				if ((flag&8)!=0) {
					if (circle) { countv+=(c-1)*acells; } else countv+=(c*acells);
				} else {
					countv+=((c-1)*(acells-1))<<2;
				}
				counti+=(c-1)*(acells-1)*6;
				it++;
			}
		}

		CPUTriangulator triangulator;
		if ((flag&6)!=0) {
			triangulator.initialize(afase->vectors().data(),afase->poligonSize().data(),afase->poligonSize().count());
			triangulator.triangulate();
			int c=1;
			if ((flag&6)==6) c=2;
			countv+=triangulator.getTessData().p_vectors.count()*c;
			counti+=triangulator.getTessData().p_result.count()*c;
		}

		amesh.setVertexCount(countv).setIndexCount(counti);

		countv=0;
		counti=0;
		if ((flag&2)!=0) {
			count=triangulator.getTessData().p_result.count();
			SetIndex(&amesh,&triangulator.getTessData().p_result,0,0,count,0,0);
			counti+=count;
			count=triangulator.getTessData().p_vectors.count();
			SetVector3F(&amesh,&triangulator.getTessData().p_vectors,0,0,count);
			countv+=count;
		}
		if ((flag&4)!=0) {
			count=triangulator.getTessData().p_result.count();
			SetIndex(&amesh,&triangulator.getTessData().p_result,0,counti,count,1,countv);
			counti+=count;
			count=triangulator.getTessData().p_vectors.count();
			void *data=triangulator.getTessData().p_vectors.data();
			bt::vector3f adde(0.0f,0.0f,exturde);
			arvFunctions.A3FAddVector(data,&adde,data,sizeof(bt::vector3f),sizeof(bt::vector3f),count);
			SetVector3F(&amesh,&triangulator.getTessData().p_vectors,0,countv,count);
			countv+=count;
		}
		bt::Vector<bt::vector3f> vecs;
		count=vecs.count();

		double zextr=exturde*1.0/(acells-1);

		if ((flag&1)!=0) {
			gen::ListPoligonSize::iterator it=afase->poligonSize().begin();
			gen::ListPoligonSize::iterator end=afase->poligonSize().end();
			int cvi=countv;
			int fr=0;
			if ((flag&8)!=0) {
				while (it!=end) {
					int count=it.value();
					bool circle=list[fr]==list[fr+count-1];
					int cvid=cvi;
					if (circle) count--;
					for (int i=0;i<count;i++) {
						for (int j=0;j<acells;j++) {
							vecs.assign(afase->vectors()[fr]);
							vecs.last().z=(float)(j*zextr);
						}
						fr++;
						if (i<count-1) {
							for (int j=0;j<acells-1;j++) {
								amesh.setIndexTri(counti,cvi,cvi+1,cvi+acells);
								counti+=3;
								amesh.setIndexTri(counti,cvi+acells,cvi+1,cvi+acells+1);
								counti+=3;
								cvi++;
							}
							cvi++;
						} else if (circle) {
							/*amesh.setIndexTri(counti,cvi,cvi+1,cvid);
							counti+=3;
							amesh.setIndexTri(counti,cvid,cvi+1,cvid+1);
							counti+=3;*/
							for (int j=0;j<acells-1;j++) {
								amesh.setIndexTri(counti,cvi,cvi+1,cvid);
								counti+=3;
								amesh.setIndexTri(counti,cvid,cvi+1,cvid+1);
								cvid++;
								counti+=3;
								cvi++;
							}
							cvi++;
						}
					}
					//if (!circle) cvi+=2;
					if (circle) fr++;
					it++;
				}
			} else {
				while (it!=end) {
					int count=it.value()-1;
					//bool circle=list[fr]==list[fr+count-1];
					for (int i=0;i<count;i++) {
						for (int j=0;j<acells-1;j++) {
							vecs.assign(afase->vectors()[fr+1]);
							vecs.last().z=(float)(j*zextr);
							vecs.assign(afase->vectors()[fr]);
							vecs.last().z=(float)(j*zextr);
							vecs.assign(afase->vectors()[fr]);
							vecs.last().z=(float)((j+1)*zextr);
							vecs.assign(afase->vectors()[fr+1]);
							vecs.last().z=(float)((j+1)*zextr);
						}
						fr++;
						for (int j=0;j<acells-1;j++) {
							amesh.setIndexTri(counti,cvi,cvi+1,cvi+2);
							counti+=3;
							amesh.setIndexTri(counti,cvi,cvi+2,cvi+3);
							counti+=3;
							cvi+=4;
						}
					}
					fr++;
					it++;
				}
			}

			SetVector3F(&amesh,&vecs,0,countv,cvi-countv);
		}

		_MeshMixDEF(mesh,&amesh);
	}

	void _APICALL _MeshBoxDEF(void *mesh,_int32 xcels,_int32 ycels,_int32 zcels,float width,float height,float lenght)
	{
		if (xcels<0) xcels=1;
		if (ycels<0) ycels=1;
		if (zcels<0) zcels=1;
		float xcdiv=1.0f/xcels;
		float ycdiv=1.0f/ycels;
		float zcdiv=1.0f/zcels;
		xcels++;
		ycels++;
		zcels++;
		csad::Mesh *bmesh=(csad::Mesh *)mesh;
		csad::Mesh amesh;
		amesh.setFields(bmesh->getFields());

		bt::vector3f vec(-0.5f);
		bt::Vector<bt::vector3f> vecs;
		vec.y=-0.5;
		for (int i=0;i<ycels;i++) {
			vec.x=-0.5;
			for (int j=0;j<xcels;j++) {
				vec.z=-0.5f;
				vecs.assign(vec);
				vec.z=0.5f;
				vecs.assign(vec);
				vec.x+=xcdiv;
			}
			vec.y+=ycdiv;
		}
		vec.z=-0.5;
		for (int i=0;i<zcels;i++) {
			vec.x=-0.5;
			for (int j=0;j<xcels;j++) {
				vec.y=-0.5f;
				vecs.assign(vec);
				vec.y=0.5f;
				vecs.assign(vec);
				vec.x+=xcdiv;
			}
			vec.z+=zcdiv;
		}
		vec.z=-0.5;
		for (int i=0;i<zcels;i++) {
			vec.y=-0.5;
			for (int j=0;j<ycels;j++) {
				vec.x=-0.5f;
				vecs.assign(vec);
				vec.x=0.5f;
				vecs.assign(vec);
				vec.y+=ycdiv;
			}
			vec.z+=zcdiv;
		}
		bt::vector3f scale(width,height,lenght);

		xcels--;
		ycels--;
		zcels--;
		amesh.setIndexCount((xcels*ycels+ycels*zcels+zcels*xcels)*12).setVertexCount(vecs.count());
		arvFunctions.A3FMulVector(vecs.data(),&scale,vecs.data(),sizeof(bt::vector3f),sizeof(bt::vector3f),vecs.count());

		int idv1=0;
		int idv2=idv1+((xcels+1)<<1);
		int ind=0;
		for (int i=0;i<ycels;i++) {
			for (int j=0;j<xcels;j++) {
				amesh.setIndexTri(ind,idv1,idv2,idv1+2);
				ind+=3;
				amesh.setIndexTri(ind,idv1+2,idv2,idv2+2);
				ind+=3;
				idv1++;
				idv2++;
				amesh.setIndexTri(ind,idv1,idv1+2,idv2);
				ind+=3;
				amesh.setIndexTri(ind,idv1+2,idv2+2,idv2);
				ind+=3;
				idv1++;
				idv2++;
			}
			idv1+=2;
			idv2+=2;
		}
		idv1+=((xcels+1)<<1);
		idv2=idv1+((xcels+1)<<1);
		for (int i=0;i<zcels;i++) {
			for (int j=0;j<xcels;j++) {
				amesh.setIndexTri(ind,idv1,idv1+2,idv2);
				ind+=3;
				amesh.setIndexTri(ind,idv1+2,idv2+2,idv2);
				ind+=3;
				idv1++;
				idv2++;
				amesh.setIndexTri(ind,idv1,idv2,idv1+2);
				ind+=3;
				amesh.setIndexTri(ind,idv1+2,idv2,idv2+2);
				ind+=3;
				idv1++;
				idv2++;
			}
			idv1+=2;
			idv2+=2;
		}
		idv1+=((xcels+1)<<1);
		idv2=idv1+((ycels+1)<<1);
		for (int i=0;i<zcels;i++) {
			for (int j=0;j<ycels;j++) {
				amesh.setIndexTri(ind,idv1,idv2,idv1+2);
				ind+=3;
				amesh.setIndexTri(ind,idv1+2,idv2,idv2+2);
				ind+=3;
				idv1++;
				idv2++;
				amesh.setIndexTri(ind,idv1,idv1+2,idv2);
				ind+=3;
				amesh.setIndexTri(ind,idv1+2,idv2+2,idv2);
				ind+=3;
				idv1++;
				idv2++;
			}
			idv1+=2;
			idv2+=2;
		}

		SetVector3F(&amesh,&vecs,0,0,vecs.count());
		_MeshMixDEF(mesh,&amesh);
	}

	void _APICALL _MeshSphereDEF(void *mesh,_int32 xcels,_int32 ycels,float radius)
	{
		csad::Mesh *bmesh=(csad::Mesh *)mesh;
		csad::Mesh amesh;
		amesh.setFields(bmesh->getFields());

		bt::vector3f vec(0.0f);
		bt::vector3f vec1(0.0f);
		bt::Vector<bt::vector3f> vecs1;
		bt::Vector<bt::vector3f> vecs;
		matFunctions.FSinCos((float)PI*2.0f/xcels,&vec1.x,&vec1.y);
		vec.z=1.0f;
		vecs.assign(vec);
		vec.z=0.0f;
		vec.x=1.0f;
		for (int i=0;i<xcels;i++) {
			vecs1.assign(vec);
			vecFunctions.V2FAfineTransform(&vec,&vec1,&vec);
		}

		amesh.setIndexCount(xcels*6+(xcels*ycels)*6);

		int iid=0;
		int vid=0;
		ycels+=2;
		bt::vector3f vec2(0.0f);
		vec2.x=1.0f;
		matFunctions.FSinCos((float)PI/ycels,&vec1.x,&vec1.y);
		for (int i=0;i<xcels-1;i++) {
			amesh.setIndexTri(iid,0,i+2,i+1);
			iid+=3;
		}
		amesh.setIndexTri(iid,0,1,xcels);
		iid+=3;
		vid++;
		for (int i=1;i<ycels-1;i++) {
			bt::vector3f *v=vecs1.data();
			vecFunctions.V2FAfineTransform(&vec2,&vec1,&vec2);
			for (int j=0;j<xcels;j++) {
				vecFunctions.V3FScale(v,&vec,vec2.y);
				vec.z=vec2.x;
				vecs.assign(vec);
				v++;
				if (j<xcels-1) {
					amesh.setIndexTri(iid,vid,vid+1,vid+xcels);
					iid+=3;
					amesh.setIndexTri(iid,vid+1,vid+xcels+1,vid+xcels);
					iid+=3;
					vid++;
				}
			}
			amesh.setIndexTri(iid,vid,vid-xcels+1,vid+xcels);
			iid+=3;
			amesh.setIndexTri(iid,vid-xcels+1,vid+1,vid+xcels);
			iid+=3;
			vid++;
		}
		bt::vector3f *v=vecs1.data();
		vecFunctions.V2FAfineTransform(&vec2,&vec1,&vec2);
		for (int i=0;i<xcels-1;i++) {
			vecFunctions.V3FScale(v,&vec,vec2.y);
			vec.z=vec2.x;
			vecs.assign(vec);
			v++;
			amesh.setIndexTri(iid,vid+i,vid+i+1,vid+xcels);
			iid+=3;
		}
		vecFunctions.V3FScale(v,&vec,vec2.y);
		vec.z=vec2.x;
		vecs.assign(vec);
		amesh.setIndexTri(iid,vid+xcels-1,vid,vid+xcels);
		iid+=3;
		vec=bt::vector3f(0.0f,0.0f,-1.0f);
		vecs.assign(vec);

		amesh.setVertexCount(vecs.count());

		arvFunctions.A3FScale(vecs.data(),vecs.data(),radius,sizeof(bt::vector3f),sizeof(bt::vector3f),vecs.count());
		SetVector3F(&amesh,&vecs,0,0,vecs.count());
		_MeshMixDEF(mesh,&amesh);
	}

	void _APICALL _MeshLoftDEF(void *mesh,void *loft,void *fase,int loftdetail,int facedetail,int flag)
	{
		if (loftdetail<1) loftdetail=1;
		if (facedetail<1) facedetail=1;

		GeometryPath<bt::vector4f> *aloft=(GeometryPath<bt::vector4f> *)loft;
		GeometryPath<bt::vector4f> loftc;
		GeometryPath<bt::vector2f> *afase=(GeometryPath<bt::vector2f> *)fase;
		GeometryPath<bt::vector2f> fasec;
		int fullsize=0;
		int *counts=aloft->poligonSize().data();
		unsigned int lofts=aloft->poligonSize().count();
		for (unsigned int i=0;i<lofts;i++) {
			int count=(counts[i]-1)*loftdetail+1;
			loftc.poligonSize().assign(count);
			fullsize+=count;
		}
		loftc.vectors().resize(fullsize);
		bt::vector4f *loftin=aloft->vectors().data();
		bt::vector4f *loftout=loftc.vectors().data();
		int *countsout=loftc.poligonSize().data();
		float ilstep=1.0f/loftdetail;
		float ifstep=1.0f/facedetail;
		int instep=aloft->vectors().sizeOfType();
		
		if ((flag&1)==0) { // loft lineare

		} else { // loft smooth CR
			for (unsigned int i=0;i<lofts;i++) {
				int loop=0;
				if (loftin[0]==loftin[counts[i]-1]) loop=1;
				arvFunctions.A4FZoomSplineCR(loftin,loftout,instep,sizeof(bt::vector4f),0,ilstep,loop,counts[i],countsout[i]);
				char *p=(char *)loftin;
				loftin=(bt::vector4f *)(p+counts[i]*instep);
				loftout+=countsout[i];
			}
		}
		int facesize=0;
		int *countf=afase->poligonSize().data();
		unsigned int fases=afase->poligonSize().count();
		for (unsigned int i=0;i<fases;i++) {
			int count=(countf[i]-1)*facedetail+1;
			fasec.poligonSize().assign(count);
			facesize+=count;
		}
		fasec.vectors().resize(facesize);
		bt::vector2f *fasein=afase->vectors().data();
		bt::vector2f *faseout=fasec.vectors().data();
		int *countfout=fasec.poligonSize().data();
		instep=afase->vectors().sizeOfType();
		int fasecount=0;

		if ((flag&2)==0) { // fase lineare

		} else { // fase smooth CR
			for (unsigned int i=0;i<afase->poligonSize().count();i++) {
				int loop=0;
				fasecount+=countfout[i];
				if (fasein[0]==fasein[countf[i]-1]) {
					loop=1;
					fasecount--;
				}
				arvFunctions.A2FZoomSplineCR(fasein,faseout,instep,sizeof(bt::vector2f),0,ifstep,loop,countf[i],countfout[i]);
				char *p=(char *)fasein;
				fasein=(bt::vector2f *)(p+countf[i]*instep);
				faseout+=countfout[i];
			}
		}

		bt::Vector<bt::vector3f> vecs;
		loftout=loftc.vectors().data();
		int vecid=0;
		int indexc=0;
		bool lastZero=true;
		bt::vector3f loftTo(0.0f);
		bt::vector3f up(0.0f,1.0f,0.0f);
		bt::vector3f left(1.0f,0.0f,0.0f);
		bt::vector3f uleft;
		bt::vector3f uup;
		bt::vector3f bild;
		for (unsigned int i=0;i<lofts;i++) {
			bool loopl=(loftout[0]==loftout[countsout[i]-1]);
			unsigned int countl=countsout[i];
			if (loopl) countl--;

			for (unsigned int j=0;j<countl;j++) {
				bool zero=loftout[j].w==0;
				if (j<countl-1) lastZero=loftout[j+1].w==0;
				int j0=j-1;
				int j2=j+1;
				if (j0<0) if (loopl) { j0=countl-1; } else j0=0;
				if (j2>=countl) if (loopl) { j2=0; } else j2=countl-1;
				vecFunctions.V3FSub(loftout+j0,loftout+j2,&loftTo);
				vecFunctions.V3FCross(&loftTo,&up,&uleft);
				vecFunctions.V3FCross(&uleft,&loftTo,&uup);
				vecFunctions.V3FNormal(&uleft,&uleft);
				vecFunctions.V3FNormal(&uup,&uup);
				if (zero) {
					vecs.assign(loftout[j]);
					vecid++;
					bt::vector2f *faseout=fasec.vectors().data();
					for ( unsigned int fi=0; fi<fases; fi++ ) {
						bool loopf=faseout[0]==faseout[countfout[fi]-1];
						unsigned int countf=countfout[fi];
						if (loopf) countf--;
						if (loopl || j<countl-1) if (!zero || !lastZero) {
							if (!zero && !lastZero) {
								indexc+=(countfout[fi]-1)*6;
							} else indexc+=(countfout[fi]-1)*3;
						}
						faseout+=countfout[fi];
					}
				} else {
					bt::vector2f *faseout=fasec.vectors().data();
					for ( unsigned int fi=0; fi<fases; fi++ ) {
						bool loopf=faseout[0]==faseout[countfout[fi]-1];
						unsigned int countf=countfout[fi];
						if (loopf) countf--;
						for ( unsigned int fj=0; fj<countf; fj++ ) {
							vecFunctions.V3FCombine(&uleft,&uup,&bild,faseout[fj].x,faseout[fj].y);
							vecFunctions.V3FAdd(&bild,&(loftout[j]),&bild);
							vecs.assign(bild);
							//vecid++;
						}
						if (loopl || j<countl-1) if (!zero || !lastZero) {
							if (!zero && !lastZero) {
								indexc+=(countfout[fi]-1)*6;
							} else indexc+=(countfout[fi]-1)*3;
						}
						faseout+=countfout[fi];
					}
				}
			}
			loftout+=countsout[i];
		}
		csad::Mesh *bmesh=(csad::Mesh *)mesh;
		csad::Mesh amesh;
		amesh.setFields(bmesh->getFields());
		amesh.setVertexCount(vecs.count()).setIndexCount(indexc);
		SetVector3F(&amesh,&vecs,0,0,vecs.count());

		vecid=0;
		indexc=0;
		loftout=loftc.vectors().data();
		for (unsigned int i=0;i<lofts;i++) {
			bool loopl=(loftout[0]==loftout[countsout[i]-1]);
			unsigned int countl=countsout[i];
			if (loopl) countl--;
			//countl--;

			int vecidl=vecid;
			for (unsigned int j=0;j<countl;j++) {
				bool idloop=loopl && j==countl-1;
				bool zero=loftout[j].w==0;
				if (j<countl-1) lastZero=loftout[j+1].w==0;
				bt::vector2f *faseout=fasec.vectors().data();
				int vecidi=vecidl;
				for ( unsigned int fi=0; fi<fases; fi++ ) {
					bool loopf=faseout[0]==faseout[countfout[fi]-1];
					unsigned int countf=countfout[fi];
					if (loopf) countf--;
					/*for ( unsigned int fj=0; fj<countf; fj++ ) {

					}*/
					if (loopl || j<countl-1) if (!zero || !lastZero) {
						if (!zero && !lastZero) {
							for ( unsigned int fj=0; fj<countf-1; fj++ ) {
								int loopvecid=vecid+fasecount;
								if (idloop) loopvecid=vecidi;
								amesh.setIndexTri(indexc,vecid,vecid+1,loopvecid);
								indexc+=3;
								amesh.setIndexTri(indexc,vecid+1,loopvecid+1,loopvecid);
								indexc+=3;
								vecid++;
								vecidi++;
							}
							if (loopf) {
								int loopvecid=vecid+fasecount;
								if (idloop) loopvecid=vecidi;
								amesh.setIndexTri(indexc,vecid,vecid-fasecount+1,loopvecid);
								indexc+=3;
								amesh.setIndexTri(indexc,vecid-fasecount+1,loopvecid-fasecount+1,loopvecid);
								indexc+=3;
							}
							vecid++;
							vecidi++;
						} else {
							if (!zero) {
								int end=vecid+fasecount;
								if (idloop) end=vecidi;
								for ( unsigned int fj=0; fj<countf-1; fj++ ) {
									amesh.setIndexTri(indexc,vecid,vecid+1,end);
									indexc+=3;
									vecid++;
								}
								if (loopf) {
									amesh.setIndexTri(indexc,vecid,vecid-fasecount+1,end);
									indexc+=3;
								}
								vecid++;
								vecidi++;
							} else if (!lastZero) {
								int begin=vecid;
								//int loopvecid=vecid+fasecount;
								for ( unsigned int fj=0; fj<countf-1; fj++ ) {
									amesh.setIndexTri(indexc,begin,vecid+1+fj,vecid+2+fj);
									indexc+=3;
								}
								if (loopf) {
									amesh.setIndexTri(indexc,begin,vecid+fasecount,vecid+1);
									indexc+=3;
								}
								vecid++;
								vecidi++;
							}
						}
					}
					faseout+=countfout[fi];
					//if (!zero) vecid+=countf;
				}
				if (zero && lastZero) {
					vecid++;
					vecidi++;
				}
				//lastZero=loftout[j].w==0;
			}
			loftout+=countsout[i];
		}

		_MeshMixDEF(mesh,&amesh);
	}

	void _APICALL _MeshMixDEF(void *mesha,void *meshb)
	{
		csad::Mesh *amesh=(csad::Mesh *)mesha;
		csad::Mesh *bmesh=(csad::Mesh *)meshb;

		int mode=generator->mode;
		unsigned int bcountv=bmesh->elementsCount();
		unsigned int bcounti=bmesh->indexCount();
		unsigned int countv=bcountv;
		unsigned int counti=bcounti;

		if (mode==0) {
			amesh->setVertexCount(countv).setIndexCount(counti);
		}

		if (mode==1) {
			countv+=amesh->elementsCount();
			counti+=amesh->indexCount();
			amesh->resizeVertex(countv).resizeIndex(counti);
		}
		unsigned int avtype=amesh->getVectorType();
		unsigned int bvtype=bmesh->getVectorType();
		int stepa=amesh->elementSize();
		int stepb=bmesh->elementSize();
		bt::LinkArray<int>::iterator itva=amesh->vector<int>().begin();
		bt::LinkArray<int>::iterator itvb=bmesh->vector<int>().begin();

		//bt::LinkArray<int>::iterator itnb=bmesh->normal<int>().begin();
		//bt::LinkArray<int>::iterator itnb=bmesh->normal<int>().begin();

		if (mode==0 || mode==1) {
			if (amesh->getFields()==bmesh->getFields()) {
				extFunctions.MoveMem(bmesh->elements(),amesh->elements(),bcountv*stepb);
			} else {
				if ((avtype!=0) && (bvtype!=0)) {
					void *typea=0;
					void *typeb=0;
					if (avtype==csad::Mesh::_TGL_V2F) typea=bt::vector2f::t();
					if (avtype==csad::Mesh::_TGL_V3F) typea=bt::vector3f::t();
					if (avtype==csad::Mesh::_TGL_V4F) typea=bt::vector4f::t();
					if (avtype==csad::Mesh::_TGL_V2D) typea=bt::vector2d::t();
					if (avtype==csad::Mesh::_TGL_V3D) typea=bt::vector3d::t();
					if (avtype==csad::Mesh::_TGL_V4D) typea=bt::vector4d::t();
					if (bvtype==csad::Mesh::_TGL_V2F) typeb=bt::vector2f::t();
					if (bvtype==csad::Mesh::_TGL_V3F) typeb=bt::vector3f::t();
					if (bvtype==csad::Mesh::_TGL_V4F) typeb=bt::vector4f::t();
					if (bvtype==csad::Mesh::_TGL_V2D) typeb=bt::vector2d::t();
					if (bvtype==csad::Mesh::_TGL_V3D) typeb=bt::vector3d::t();
					if (bvtype==csad::Mesh::_TGL_V4D) typeb=bt::vector4d::t();
					arvFunctions.AConvert(&itvb.value(),&itva.value(),stepb,stepa,typeb,typea,bcountv);
				}
				/*if () {

				}*/
			}
			if (amesh->getIndexSize()==bmesh->getIndexSize()) extFunctions.MoveMem(bmesh->indexs(),amesh->indexs(),bmesh->getIndexSize()*bcounti);
		}
	}

};

OPTIMIZE_OFF;