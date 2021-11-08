/*
 * camera.cpp
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/camera.h>
#include <scene/scene.h>
#include <scene/transform.h>
#include <core/graph.h>
#include <platform.h>
#include <bt.h>
#include "csad/platform/localdisplay.h"
#include "csad/core/base/stringconsts.h"

OPTIMIZE_ON;

namespace csad {

Camera *Camera::p_default=0;

Camera::Camera():
p_clearColor(0,0,0,0)
{
	p_fov = 45.0;
	p_max = 20;
	p_min = 0.1;
	p_clearDepth = 1.0f;
	fflag=UPDATEMATRIX;
	p_mode=0;
	p_proj=0;
}

/*void Camera::setClear(unsigned int clear)
{
	//p_clear=clear;
}*/

Camera& Camera::setViewPort(vector4f *viewport)
{
	if (!viewport) return *this;
	p_viewPort.setRect(*viewport);
	getScene()->p_changes++;
	return *this;
}

vector4f Camera::getViewPort()
{
	return p_viewPort.getRect();
}

vector4i Camera::getViewPort(GlContext * context)
{
	return p_viewPort.getRect(context);
}

vector4i Camera::getViewPort(Display * display)
{
	return p_viewPort.getRect(display);
}

bool Camera::Intersect(vector2i *pos,GlContext * context)
{
	vector4i rect=p_viewPort.getRect(context);
	if (pos->x<rect.x) return false;
	if (pos->x>rect.x+rect.z) return false;
	if (pos->y<rect.y) return false;
	if (pos->y>rect.y+rect.w) return false;
	return true;
}

Camera& Camera::setMaxRange(double max)
{
	if ((fflag&UPDATEMATRIX)==0) if (p_max!=max) fflag^=UPDATEMATRIX;
	p_max=max;
	return *this;
}

Camera& Camera::setMinRange(double min)
{
	if ((fflag&UPDATEMATRIX)==0) if (p_min!=min) fflag^=UPDATEMATRIX;
	p_min=min;
	return *this;
}

Camera& Camera::setFov(double _ov)
{
	if ((fflag&UPDATEMATRIX)==0) if (p_fov!=_ov) fflag^=UPDATEMATRIX;
	p_fov=_ov;
	return *this;
}

Camera& Camera::setProj(unsigned int proj)
{
	if ((fflag&UPDATEMATRIX)==0) if (p_proj!=proj) fflag^=UPDATEMATRIX;
	p_proj=proj;
	return *this;
}

Camera& Camera::setColor(float r,float g,float b,float w)
{
	p_clearColor=vector4f(r,g,b,w);
	if ((fflag&CLEARCOLOR)==0) fflag^=CLEARCOLOR;
	return *this;
}

Camera& Camera::setColor(vector4f &color)
{
	p_clearColor=color;
	if ((fflag&CLEARCOLOR)==0) fflag^=CLEARCOLOR;
	return *this;
}

Camera& Camera::setDepth(double val)
{
	p_clearDepth=(float)val;
	if ((fflag&CLEARDEPTH)==0) fflag^=CLEARDEPTH;
	return *this;
}

void Camera::lookAt(Transform * )
{

}

void Camera::lookAt(vector3d &)
{
/*	vec.norm();
	vector3d xv(vec.x,0,vec.z);
	vector3d x = xv&vector3d(1,0,0);
	quaterniond r;
	if (x.sqrLen()!=0) {
		vector3d z=xv&vector3d(1,0,0);
		r=quaterniond(x,xv|vector3d(1,0,0))*quaterniond(z,vec|vector3d(0,0,1));
	}
	vector3d y=vec&vector3d(0,1,0);
	vector3d z=vec&vector3d(0,0,1);
	if (x.sqrLen()==0) {
		r=quaterniond(y,vec|vector3d(0,1,0))*quaterniond(z,vec|vector3d(0,0,1));
	} else if (y.sqrLen()==0) {
		r=quaterniond(x,vec|vector3d(1,0,0))*quaterniond(z,vec|vector3d(0,0,1));
	} else if (z.sqrLen()==0) {
		r=quaterniond(x,vec|vector3d(1,0,0))*quaterniond(y,vec|vector3d(0,1,0));
	}

	Transform * transform = (Transform *) getContainer();
	transform->setRotate(r);*/
}

void  Camera::pointToNormal(vector3f *local,vector3f *normal)
{
	if (p_proj==Camera::Perspective) {
		matrix4f invproj;
		p_matrix.invert(&invproj);
		local->z=1.0f;
		*normal=p_matrix.transform(*local);
	} else {
		normal->x=0.0f;
		normal->y=0.0f;
		normal->z=1.0f;
	}
}

/*void  Camera::pointToNormal(vector3f *local,vector3f *normal)
{
	if (p_proj==Camera::Perspective) {
		matrix4f invproj;
		p_matrix.invert(&invproj);
		local->z=1.0f;
		//normal->x=normal->x;
		*normal=invproj.transform(*normal);
	} else {
		normal->x=0.0f;
		normal->y=0.0f;
		normal->z=1.0f;
	}
}*/

bool Camera::makeCurrent(unsigned int toTextureId)
{
	if (!p_viewPort.makeCurrent(toTextureId)) return false;
	sFunctionsDisplayRender &dfunctions=((LocalDisplay*)(GlContext::current()->getDisplay()))->functions();
	dfunctions.SetMatrix(this);
	p_default=this;
	return true;
}

bool Camera::makeCurrent(vector4i &rect,unsigned int )
{
	sFunctionsDisplayRender &dfunctions=((LocalDisplay*)(GlContext::current()->getDisplay()))->functions();
	dfunctions.SetViewPort(rect.x,GlContext::getCurrent()->height()-rect.y-rect.w,rect.z,rect.w);

	dfunctions.SetMatrixRect(this,&rect);
	return true;
}

Scene* Camera::getScene()
{
	Transform * transform = (Transform *) getContainer();
	return transform->getScene();
}

matrix4f* Camera::projMatrix()
{
	if ((fflag&UPDATEMATRIX)!=0) {
		vector4i rect=getViewPort(GlContext::getCurrent());
		if (p_proj==Camera::Perspective)
			p_matrix.perspective(rect.z,rect.w,(float)p_max,(float)p_min,(float)p_fov);
		if (p_proj==Camera::Ortographic)
			p_matrix.ortographic(rect.z,rect.w,(float)p_max,(float)p_min,(float)p_fov);
		fflag^=UPDATEMATRIX;
	}
	return &p_matrix;
}

/*Camera *Camera::camera()
{
	return core->
}*/

void *Camera::set(unsigned _int32 id,void *param)
{
	if (id==BaseObject::TYPE) return Camera::t();
	if (id==BaseObject::WRITE) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		if ((p=list.find("fov"))!=0) {
			setProj(0);
			setFov(p->getFloat(45));
		}
		if ((p=list.find("size"))!=0) {
			setProj(1);
			setFov(p->getFloat(45));
		}
		if ((p=list.find("far"))!=0) setMaxRange(p->getFloat(20));
		if ((p=list.find("near"))!=0) setMinRange(p->getFloat(0.01f));
		if ((p=list.find(STR_MAX))!=0) setMaxRange(p->getFloat(20));
		if ((p=list.find(STR_MIN))!=0) setMinRange(p->getFloat(0.01f));
		if ((p=list.find(STR_DEPTH))!=0) setDepth(p->getFloat(1));
		if ((p=list.find(STR_COLOR))!=0) setColor(p->getVector4f());
		if ((p=list.find("viewport"))!=0) setViewPort((vector4f *)&p->getVector4f());
		if ((p=list.find("cullface"))!=0) setCullFace(p->getBool());
	}
	if (id==BaseObject::READ) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		p=&list["proj"];
		p->setInt(p_proj);
		if (p_proj==0) {
			p=&list["fov"];
		} else {
			p=&list["size"];
		}
		p->setDouble(p_fov);
		p=&list["far"];
		p->setDouble(p_max);
		p=&list["near"];
		p->setDouble(p_min);
		p=&list[STR_COLOR];
		p->setVector4f(&p_clearColor);
		p=&list["viewport"];
		p->setVector4f(&p_viewPort.getRect());
		p=&list["cullface"];
		p->setBool(cullFace());
		return param;
	}
	return 0;
}

Camera *Camera::finder(char *path)
{
	ObjectManager::Finder find(path);
	Scene *scene=Graph::graph().getScene(find.getNext());
	if (!scene) {
#ifdef LOG_CSAD
		Log::console("Can`t find scene: %s",find.getNext());
#endif
		return 0;
	}
	find.next();
	Camera *camera=scene->getCamera(find.getNext());
	if (!camera) {
#ifdef LOG_CSAD
		Log::console("Can`t find camera: %s",find.getNext());
#endif
		return 0;
	}
	find.next();
	return camera;
}

TYPEINFO(Camera)

}

OPTIMIZE_OFF;
