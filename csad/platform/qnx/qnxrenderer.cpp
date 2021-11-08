/*
 * qnxrenderer.cpp
 *
 *  Created on: 15.08.2013
 *      Author: Пантелеймонов Александр
 */
#include <platform/platformapi.h>

#if defined (OS_QNX)

#include <platform.h>
#include <scene/transform.h>
#include <scene/scene.h>
#include <scene/camera.h>
#include <scene/meshfilter.h>
#include <scene/mesh.h>
#include <scene/material.h>
#include <core/graph.h>
#include <core/system.h>
#include <core/input.h>
#include <bt.h>
#include "csad/core/csadcore.h"
#include "csad/platform/glextention.h"

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

using namespace bt;

void Renderer::_init(int order)
{
	p_camera=0;
	p_context=0;
	p_input=0;
	p_needUpdate=true;
	p_clear=GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
	System::system().getIRS().registerTarget(order,this);
}

void Renderer::setCamera(Camera *camera)
{
	if (p_camera!=camera) p_needUpdate=true;
	p_camera=camera;
}

void Renderer::setCamera(char *cameraPath)
{
	Camera *camera=Camera::finder(cameraPath);
	if (camera) {
		if (p_camera!=camera) p_needUpdate=true;
		p_camera=camera;
	}
}

Camera* Renderer::getCamera()
{
	return p_camera;
}

void Renderer::setContext(GlContext *context)
{
	if (p_context!=context) p_needUpdate=true;
	p_context=context;
}

void Renderer::setContext(char *contextPath)
{
	GlContext *context=GlContext::finder(contextPath);
	if (context) {
		if (p_context!=context) p_needUpdate=true;
		p_context=context;
	}
}

GlContext* Renderer::getContext()
{
	return p_context;
}

void Renderer::_bindCamera()
{
	p_clear=0;
	if (p_camera->clearColor()) {
		p_clear|=GL_COLOR_BUFFER_BIT;
		vector4f *color = &p_camera->p_clearColor;
		glClearColor(color->x,color->y,color->z,color->w);
	}
	if (p_camera->clearDepth()) {
		p_clear|=GL_DEPTH_BUFFER_BIT;
		glClearDepthf(p_camera->p_clearDepth);
	}
	if (p_camera->cullFace()) {
		glEnable(GL_CULL_FACE);
		if (p_camera->frontFace()) {
			glCullFace(GL_FRONT);
		} else {
			glCullFace(GL_BACK);
		}
	} else {
		glDisable(GL_CULL_FACE);
	}
}

#define GL_POLYGON_SMOOTH 0x0B41

bool Renderer::drawRect(vector4i _rect)
{
	if (!p_context || !p_camera) return false;
	Transform *transform=p_camera->getContainer();
	if (!transform) {
		Log::console("camera not have target");
		return false;
	}

	Scene *scene = p_camera->getScene();
	if (!scene) {
		Log::console("can not use null scene.");
		return false;
	}

	if (!p_context->makeCurrent()) return false;
	p_camera->makeCurrent(_rect);
	_bindCamera();

	scene->_setDefault();

	scene->_prepare();
	_validateUpdate(scene,p_camera);
	if (p_needUpdate) {
		_prepareNodes(p_camera);
		_fillFilter(scene);
		_sortZUpNodes(&p_tempfilter[0],0,p_tempfilter.size()-1);
		p_needUpdate=false;
	}

	//glEnable(GL_SCISSOR_TEST);

	_draw();

	//glDisable(GL_SCISSOR_TEST);
	//Render::PopAttrib();
	Render::Finish();
	return true;
}

struct buffSelectMesh4f {
	vector4f v;
	unsigned int flag;
};

struct buffSelectMesh4d {
	vector4d v;
	unsigned int flag;
};

void *Renderer::select(vector4i _rect)
{
	if (!p_context || !p_camera) return false;
	Transform *transform=p_camera->getContainer();
	if (!transform) {
		Log::console("camera not have target");
		return false;
	}

	p_selected.clear();
	Scene *scene = p_camera->getScene();
	if (!scene) {
		Log::console("can not use null scene.");
		return false;
	}
	scene->_setDefault();

	_validateUpdate(scene,p_camera);
	if (p_needUpdate) {
		_prepareNodes(p_camera);
		_fillFilter(scene);
		_sortZUpNodes(&p_tempfilter[0],0,p_tempfilter.size()-1);
		p_needUpdate=false;
	}

	p_context->makeCurrent();
	p_camera->makeCurrent(_rect);

	matrix4f projMatrix;
	vector4i viewport=p_camera->getViewPort(p_context);
	glGetFloatv(GL_PROJECTION_MATRIX,(float*)&projMatrix);

	float vportScale[3]={0.5*viewport.z,0.5*viewport.w,(p_camera->getMaxRange()-p_camera->getMinRange())*0.5};
	float vportAdd[3]={viewport.x,viewport.y,p_camera->getMinRange()};
	vecFunctions.V3FAdd(vportAdd,vportScale,vportAdd);

	char *buff=new char[65536*(sizeof(buffSelectMesh4d))];
	buffSelectMesh4f *buffMesh4f=(buffSelectMesh4f *)buff;
	buffSelectMesh4d *buffMesh4d=(buffSelectMesh4d *)buff;

	Transform *mtransform;
	MeshFilter *geom;
	unsigned int i;
	vector4b *t;
	t=(vector4b*)&i;
	for (i=0;i<p_count;i++)
	{
		mtransform=p_tempfilter[i];
		if (!mtransform->isSelect()) continue;
		geom=mtransform->getComponent<MeshFilter>();
		if (geom) {
			matrix4f mMatrix;
			vector3f mpos(mtransform->realPosition());
			quaternionf mrot(mtransform->realRotate());
			vecFunctions.M4FTRS(&mMatrix,&mpos,&mrot,mtransform->realScale());
			glLoadMatrixf(mMatrix.m);

			/*matrix4f mMatrix;
			vector3f mpos(mtransform->realPosition());
			vecFunctions.M4FTranslate(&mMatrix,&mpos);
			quaternionf mrot(mtransform->realRotate());
			//matrix4f rMatrix(mrot);
			//mMatrix=mMatrix*rMatrix;
			vecFunctions.M4FAddRotate(&mMatrix,&mrot,&mMatrix);
			vecFunctions.M4FAddScale(&mMatrix,mtransform->realScale(),&mMatrix);*/
			mMatrix=projMatrix*mMatrix;

			Mesh *mesh=geom->getMesh();
			unsigned int type=mesh->getVectorType();
			//mesh->index(i);
			int count=0;
			if (type==Mesh::_TGL_V2F) {
				LincArray<vector2f> vectors=mesh->vector<vector2f>();
				count=vectors.count();
				if (vectors.count()>0) arrFunctions.A2FProj(vectors.getArray(),&mMatrix,vportScale,vportAdd,buffMesh4f,vectors.getStep(),sizeof(buffSelectMesh4f),(int)&buffMesh4f->flag-(int)buffMesh4f,vectors.count());
			}
			if (type==Mesh::_TGL_V3F) {
				LincArray<vector3f> vectors=mesh->vector<vector3f>();
				count=vectors.count();
				if (vectors.count()>0) arrFunctions.A3FProj(vectors.getArray(),&mMatrix,vportScale,vportAdd,buffMesh4f,vectors.getStep(),sizeof(buffSelectMesh4f),(int)&buffMesh4f->flag-(int)buffMesh4f,vectors.count());
			}
			if (type==Mesh::_TGL_V4F) {
				LincArray<vector4f> vectors=mesh->vector<vector4f>();
				count=vectors.count();
				//if (vectors.count()>0) csad::Functions::arrFunctions.A4FProj(vectors.getArray(),&mMatrix,vportScale,vportAdd,buffMesh4f,vectors.getStep(),sizeof(buffSelectMesh4f),(int)&buffMesh4f->flag-(int)buffMesh4f,vectors.count());
			}
			bool isselected=false;
			if (type==Mesh::_TGL_V2F || type==Mesh::_TGL_V3F || type==Mesh::_TGL_V4F) {
				for (unsigned int e=0;e<mesh->indexCount();e+=3) {
					int i1=mesh->index(e);
					int i2=mesh->index(e+1);
					int i3=mesh->index(e+2);
					if ((buffMesh4f[i1].flag & buffMesh4f[i2].flag & buffMesh4f[i3].flag & 0xF)!=0) {
						//isselected=false;
					} else {
						isselected=true;
					}
				}
			}
			if (type==Mesh::_TGL_V2D || type==Mesh::_TGL_V3D || type==Mesh::_TGL_V4D) {
				for (unsigned int e=0;e<mesh->indexCount();e+=3) {
					int i1=mesh->index(e);
					int i2=mesh->index(e+1);
					int i3=mesh->index(e+2);
					if ((buffMesh4d[i1].flag & buffMesh4d[i2].flag & buffMesh4d[i3].flag & 0xF)!=0) {
						//isselected=false;
					} else {
						isselected=true;
					}
				}
			}
			if (isselected) p_selected.assign(mtransform);
		}
	}
	delete buff;

	//if (i<p_count) p_selected.assign(p_tempfilter[i]);
	Render::UnBindModel();

	return &p_selected;
}

void Renderer::setSelectInput(char*path)
{
	p_input=Input::input().finder(path);
}

bool Renderer::isIntersection(vector2i *global)
{
	if (!p_context) return false;
	Display *display=p_context->getDisplay();
	if (!display) return false;
	if (!display->isGlobalPoint(global)) return false;
	vector2i local;
	display->toLocal(global,&local);
	vector4i view=p_camera->getViewPort(p_context);
	if (view.x>local.x) return false;
	if (view.x+view.z<local.x) return false;
	if (view.y>local.y) return false;
	if (view.y+view.w<local.y) return false;
	return true;
}

bool Renderer::input()
{
	vector4i rect;
	rect.w=1;
	rect.z=1;
	if (p_input->set(BaseObject::TYPE,0)==Mouse::t()) {
		Mouse *mouse=(Mouse *)p_input;
		if (!mouse->getUpdata()) return true;
		rect.x=mouse->getPos().x;
		rect.y=mouse->getPos().y;
		p_context->getDisplay()->toLocal((vector2i*)&rect,(vector2i*)&rect);
		select(rect);
	}
	if (p_input->set(BaseObject::TYPE,0)==Input::t()) {
		Input *input=(Input *)p_input;
		rect.x=input->getCursorPos().x;
		rect.y=input->getCursorPos().y;
		p_context->getDisplay()->toLocal((vector2i*)&rect,(vector2i*)&rect);
		select(rect);
	}
	for (unsigned int i=0;i<p_selected.size();i++) {
		p_selected[i]->setComponents(BaseObject::SELECT,p_selected[i]);
	}

	return true;
}

void Renderer::_prepareNodes(Camera *camera)
{
	Transform *transform=camera->getContainer();
	transform->setChildReal(transform);
	transform->setParentReal(transform);
}

void Renderer::_draw()
{
	MeshFilter *geom;
	Transform *mtransform;
	glClear(p_clear);

	unsigned int err=glGetError();
	if (err>0) {
		if (err>=0x500 && err<=0x505) {
			Log::console("glerror %s",GLErrorString[err-0x500]);
		} else {
			Log::console("glerror 0x%x",err);
		}
	}

/*	vector4i f=p_camera->getViewPort(p_context);
	if (!texture) {
		eglCreatePbufferSurface(p_context->getDisplay());
		glGenTextures(1,&texture);
		Render::BindTexture2D(texture);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,2048,2048,0,GL_RGBA,GL_UNSIGNED_BYTE,0);
	}
	//eglCreatePbufferSurface
	//eglBindTexImage
	Render::BindTexture2D(texture);
	//glCopyTexSubImage2D(GL_TEXTURE_2D,0,0,0,f.x,f.y,f.z,f.w);
*/

	Render::UnBindAll();
	glPushMatrix();

	for (unsigned int i=0;i<p_count;i++)
	{
		mtransform=p_tempfilter[i];
		geom=mtransform->getComponent<MeshFilter>();
		if (geom) {

			matrix4f mMatrix;
			vector3f mpos(mtransform->realPosition());
			quaternionf mrot(mtransform->realRotate());
			vecFunctions.M4FTRS(&mMatrix,&mpos,&mrot,mtransform->realScale());
			glLoadMatrixf(mMatrix.m);

			/*matrix4f mMatrix;
			vector3f mpos(mtransform->realPosition());
			vecFunctions.M4FTranslate(&mMatrix,&mpos);
			quaternionf mrot(mtransform->realRotate());
			//matrix4f rMatrix(mrot);
			//mMatrix=mMatrix*rMatrix;
			vecFunctions.M4FAddRotate(&mMatrix,&mrot,&mMatrix);
			vecFunctions.M4FAddScale(&mMatrix,mtransform->realScale(),&mMatrix);
			glMultMatrixf(mMatrix.m);*/

			/*vector3f mpos(mtransform->realPosition());
			glTranslatef(mpos.x,mpos.y,mpos.z);
			matrix4f mMatrix(quaternionf(mtransform->realRotate()));
			glMultMatrixf((GLfloat *)&mMatrix);
			vector3f* mscale=mtransform->realScale();
			glScalef(mscale->x,mscale->y,mscale->z);*/

			/*err=glGetError();
			if (err>0) {
				Log::console("glerror %i",err);
			}*/

			Material *mat=geom->getMaterial();
			if (mat) {
				mat->bind();
			} else {
				Render::BindMaterial(0);
			}

			Render::DrawMesh(geom);

		}
	}
	glPopMatrix();

	Render::UnBindAll();

//	if (p_toTextureId) _copyToTexture();
}

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif
