/*
 * baseface.h
 *
 *  @brief core, 2003-2014
 *
 *  Created on: 12.04.2008
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include "baseface.h"
#include "basegen.h"
#include <bt.h>
#include <gen3.h>
#include <platform/font.h>

OPTIMIZE_ON;

namespace gen {

	void* _APICALL _CreateFaceDEF()
	{
		return new gen::GeometryPath<bt::vector2f>();
	}

	void _APICALL _FaceAddDEF(void *face,float x,float y,_int32 flag)
	{
		gen::GeometryPath<bt::vector2f>* aface=(gen::GeometryPath<bt::vector2f>*)face;
		aface->addVector(bt::vector2f(x,y),(flag&1)!=0);
	}

	void _APICALL _FreeFaceDEF(void*fase)
	{
		delete (gen::GeometryPath<bt::vector3f>*)fase;
	}

	void _APICALL _FaceLineFilterDEF(void*fase,float smooth)
	{
		GeometryPath<vector2f> *tfasef=(GeometryPath<vector2f> *)fase;
		GeometryPath<vector2f> rfasef;
		unsigned int poligons=tfasef->poligonSize().size();
		vector2f *vectorsp=tfasef->vectors().data();

		vector3f v1(0.0f);
		vector3f v2(0.0f);
		for (unsigned int i=0; i<poligons;i++) {
			unsigned int vectorc=tfasef->poligonSize()[i];
			rfasef.addVector(vectorsp[0],true);
			for (unsigned int i=0;i<vectorc-2;i++) {
				vecFunctions.V2FSub(&(vectorsp[i]),&(vectorsp[i+1]),&v1);
				vecFunctions.V2FNormal(&v1,&v1);
				vecFunctions.V2FSub(&(vectorsp[i+1]),&(vectorsp[i+2]),&v2);
				vecFunctions.V2FNormal(&v2,&v2);
				vecFunctions.V3FCross(&v1,&v2,&v1);
				if (v1.z<0) v1.z=-v1.z;
				if (v1.z>smooth) {
					rfasef.addVector(vectorsp[i+1]);
				}
				v1.z=0.0f;
			}
			rfasef.addVector(vectorsp[vectorc-1]);
			vectorsp+=vectorc;
		}
		tfasef->clear();
		tfasef->vectors().absorb(rfasef.vectors());
		tfasef->poligonSize().absorb(rfasef.poligonSize());
	}

	void _APICALL _FaceStrokerDEF(void*fase,void*rez,_int32 smooth,float width,float offset)
	{
		GeometryPath<vector2f> *tpathf=(GeometryPath<vector2f> *)fase;
		GeometryPath<vector2f> *rpathf=(GeometryPath<vector2f> *)rez;
		unsigned int poligons=tpathf->poligonSize().size();
		vector2f *vectorsp=tpathf->vectors().data();
		int first=0;
		int id=0;

		unsigned int allv=0;//tpathf->vectors().count();

		/*for (unsigned int i=0; i<poligons;i++) {
			unsigned int vectorc=tpathf->poligonSize()[i];
			bool poligon=vectorsp[vectorc-1]==vectorsp[0];
			if (poligon) vectorc--;
			allv+=vectorc;
		}*/

		vector2f v1;
		vector2f v2;
		vector2f v3;
		vector2f v4;

		width=width*0.5f;

		//rpathf->vectors().resize(allv*2);

		//Vector<vector2f> rezv(allv*2);

		for (unsigned int i=0; i<poligons;i++) {
			unsigned int vectorc=tpathf->poligonSize()[i];
			unsigned int s;
			int t;
			bool poligon=vectorsp[vectorc-1]==vectorsp[0];
			unsigned int loopc=vectorc;
			if (poligon) loopc--;
			int from=rpathf->vectors().count();
			rpathf->vectors().resize(from+vectorc*2);
			bt::vector2f *vec=rpathf->vectors().data();
			if (poligon) {
				rpathf->poligonSize().assign(vectorc);
				rpathf->poligonSize().assign(vectorc);
			} else {
				rpathf->poligonSize().assign(vectorc*2);
			}
			vec+=from;
			for (unsigned int j=0; j<loopc;j++) {
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

				vec[j]=v1+v2;
				vec[vectorc*2-j-1]=v1+v3;
				id++;
			}
			if (poligon) {
				vec[vectorc-1]=vec[0];
				vec[vectorc]=vec[vectorc*2-1];
			} else {
				bt::vector2f v=vec[0];
				rpathf->addVector(v);
			}
			first+=vectorc;
		}
	}

	_int32 _APICALL _FaceTextDEF(void*face,void*font,void*text,float x,float y,float kerning,float step)
	{
		GeometryPath2I* aface=(GeometryPath2I*)face;
		csad::Font *afont=(csad::Font *)font;
		char *c=(char *)text;
		int from=aface->geometry().vectors().count();
		int xd=0;
		while (*c!=0) {
			float size=afont->addOutLine(xd,0,*c,aface);
			xd+=matFunctions.FTrunc(size*kerning+step);
			c++;
		}
		int to=aface->geometry().vectors().count()-from;
		bt::vector2i *v=aface->geometry().vectors().data();
		v+=from;
		arvFunctions.A2ITo2F(v,v,sizeof(bt::vector2i),sizeof(bt::vector2f),to);
		bt::vector2f pos(x,y);
		arvFunctions.A2FAddVector(v,&pos,v,sizeof(bt::vector2i),sizeof(bt::vector2f),to);
		return xd;
	}

}

OPTIMIZE_OFF;
