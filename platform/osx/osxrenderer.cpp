/*
 *  osxrenderer.cpp
 *
 *  Created on: 15.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>

#if defined (OS_OSX)

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
	p_count=0;
	p_size=0;
	fmode=SORT_ZUP;
	p_clear=GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
	System::system().getIRS().registerTarget(order,this);

	cikles_inititem=0;
	cikles_prepare=0;
	cikles_fullitem=0;
	cikles_nodes=0;
	cikles_sort=0;
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
		glClearDepth(p_camera->p_clearDepth);
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
		_sortZUpNodes(p_tempfilter,0,p_count-1);
		p_needUpdate=false;
	}

	_draw();

	//Render::PopAttrib();
	Render::Finish();
	return true;
}

void *Renderer::select(vector4i _rect)
{
	if (!p_context || !p_camera) return 0;
	Transform *transform=p_camera->getContainer();
	if (!transform) {
		Log::console("camera not have target");
		return 0;
	}

	//p_selected.clear();
	Scene *scene = p_camera->getScene();
	if (!scene) {
		Log::console("can not use null scene.");
		return 0;
	}

	if (!p_context->makeCurrent()) return 0;
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	p_camera->makeCurrent(_rect);

	scene->_setDefault();
	p_selected._clear();

	_validateUpdate(scene,p_camera);
	if (p_needUpdate) {
		_prepareNodes(p_camera);
		_fillFilter(scene);
		_sortZUpNodes(p_tempfilter,0,p_count-1);
		p_needUpdate=false;
	}

	//glClearColor(1,1,1,1);
	//glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_LIGHTING);

	glSelectBuffer(32,p_selectBuffer);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);

	glPushMatrix();
	Transform *mtransform;
	MeshFilter *geom;
	for (unsigned int i=0;i<p_count;i++)
	{
		mtransform=p_tempfilter[i];
		if (!mtransform->isSelect()) continue;
		geom=mtransform->getComponent<MeshFilter>();
		if (geom) {
			glLoadName((GLuint)(i));

			matrix4f mMatrix;
			vector3f mpos(mtransform->realPosition());
			quaternionf mrot(mtransform->realRotate());
			vecFunctions.M4FTRS(&mMatrix,&mpos,&mrot,mtransform->realScale());
			glLoadMatrixf(mMatrix.m);

			/*matrix4f mMatrix;
			vector3f mpos(mtransform->realPosition());
			vecFunctions.M4FTranslate(&mMatrix,&mpos);
			quaternionf mrot(mtransform->realRotate());
			//mrot=mrot.invert();
			vecFunctions.M4FAddRotate(&mMatrix,&mrot,&mMatrix);
			vecFunctions.M4FAddScale(&mMatrix,mtransform->realScale(),&mMatrix);
			glMultMatrixf(mMatrix.m);*/

			Render::DrawMesh(geom);

		}
	}
	glPopMatrix();

	int count=glRenderMode(GL_RENDER);
	if (count>0) {
		if (count<0) count=32>>2;
		while (count>0) {
			count--;
			mtransform=p_tempfilter[p_selectBuffer[(count<<2)+3]];
			if (mtransform) {
					p_selected._assign(&mtransform);
				}
		}
	}

	glPopName();
	Render::UnBindModel();

	glEnable(GL_DEPTH_TEST);

	glPopAttrib();
	//Render::Finish();
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
		vecFunctions.V2FTo2I(&mouse->getPos(),&rect);
		p_context->getDisplay()->toLocal((vector2i*)&rect,(vector2i*)&rect);
		select(rect);
	}
	if (p_input->set(BaseObject::TYPE,0)==Input::t()) {
		Input *input=(Input *)p_input;
		vecFunctions.V2FTo2I(&input->getCursorPos(),&rect);
		p_context->getDisplay()->toLocal((vector2i*)&rect,(vector2i*)&rect);
		select(rect);
	}
	if (p_selected.mCount>0) {
		Transform **tr=(Transform **)p_selected.mVals;
		Transform *t=*tr;
		double z=(*tr)->realPosition()->z;
		for (unsigned int i=1;i<p_selected.mCount;i++) {
			tr++;
			if ((*tr)->realPosition()->z<z) t=*tr;
		}
		t->setComponents(BaseObject::SELECT,t);
	}

	return true;
}

void Renderer::_draw()
{
	MeshFilter *geom;
//	GLMaterial* mat;
	Transform *mtransform;
	glClear(p_clear);

	unsigned int glerr=glGetError();
	if (glerr>0) {
		Log::console("glerror: %x",glerr);
	}

	Render::UnBindAll();
	glPushMatrix();
	//glLoadIdentity();

	for (unsigned int i=0;i<p_count;i++)
	{
		//_int64 sr2=extFunctions.TSC();

		mtransform=p_tempfilter[i];
		geom=mtransform->getComponent<MeshFilter>();
		mtransform->render();
		if (geom) { 
			
			//_int64 s=extFunctions.TSC();

			//_int64 sr1=extFunctions.TSC();

			matrix4f mMatrix;
			vector3f mpos(mtransform->realPosition());
			quaternionf mrot(mtransform->realRotate());
			vecFunctions.M4FTRS(&mMatrix,&mpos,&mrot,mtransform->realScale());
			glLoadMatrixf(mMatrix.m);

			/*matrix4f mMatrix;
			vector3f mpos(mtransform->realPosition());
			vecFunctions.M4FTranslate(&mMatrix,&mpos);
			quaternionf mrot(mtransform->realRotate());
			//mrot=mrot.invert();
			vecFunctions.M4FAddRotate(&mMatrix,&mrot,&mMatrix);
			vecFunctions.M4FAddScale(&mMatrix,mtransform->realScale(),&mMatrix);
			glMultMatrixf(mMatrix.m);*/

			/*vector3f mpos(mtransform->realPosition());
			glTranslatef(mpos.x,mpos.y,mpos.z);
			matrix4f mMatrix(quaternionf(mtransform->realRotate()));
			glMultMatrixf((GLfloat *)&mMatrix);
			vector3f* mscale=mtransform->realScale();
			glScalef(mscale->x,mscale->y,mscale->z);*/

			//s=extFunctions.TSC()-s;
			//Log::console("matr %i",(int)s);

			/*sr1=(extFunctions.TSC()-sr1);
			if (sr1<=0) sr1=cikles_inititem;
			cikles_inititem=(cikles_inititem+sr1)*0.5;*/

			Material *mat=geom->getMaterial();
			if (mat) {
				mat->bind();
			} else {
				Render::BindMaterial(0);
			}
			Render::DrawMesh(geom);
		}

/*		sr2=(extFunctions.TSC()-sr2);
		if (sr2<=0) sr2=cikles_fullitem;
		cikles_fullitem=(cikles_fullitem+sr2)*0.5;*/
	}
	glPopMatrix();
	Render::UnBindAll();

//	if (p_toTextureId) _copyToTexture();
}

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif
