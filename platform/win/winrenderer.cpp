/*
 *  winrenderer.cpp
 *
 *  Created on: 15.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>

#if defined (OS_WIN)

#include <platform.h>
#include <bt.h>
#include <scene/transform.h>
#include <scene/scene.h>
#include <scene/camera.h>
#include <scene/light.h>
#include <scene/lightingmodel.h>
#include <scene/meshfilter.h>
#include <scene/mesh.h>
#include <scene/material.h>
#include <scene/shader.h>
#include <core/graph.h>
#include <core/system.h>
#include <core/input.h>
#include "csad/core/csadcore.h"
#include "csad/core/baselocal.h"
#include "csad/platform/glextension.h"

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

using namespace bt;

void _sortZUpNodes(Transform** list,int begin,int end);
void _sortZDownNodes(Transform** list,int begin,int end);
int _sortTreeNodes(Transform** list,int begin,int end);

void Renderer::_bindCamera()
{
	sFunctionsGLContext &functions=p_context->functions();
	p_clear=0;
	if (p_camera->clearColor()) {
		p_clear|=GL_COLOR_BUFFER_BIT;
		vector4f *color = &p_camera->p_clearColor;
		functions.ClearColor(color->x,color->y,color->z,color->w);
	}
	if (p_camera->clearDepth()) {
		p_clear|=GL_DEPTH_BUFFER_BIT;
		functions.ClearDepth(p_camera->p_clearDepth);
	}
	if (p_camera->cullFace()) {
		functions.Enable(GL_CULL_FACE);
		if (p_camera->frontFace()) {
			functions.CullFace(GL_FRONT);
		} else {
			functions.CullFace(GL_BACK);
		}
	} else {
		functions.Disable(GL_CULL_FACE);
	}
	functions.Hint(GL_LINE_SMOOTH_HINT,GL_FASTEST);
	functions.Hint(GL_POINT_SMOOTH_HINT,GL_FASTEST);
	functions.Enable(GL_LINE_SMOOTH);
	functions.Enable(GL_POINT_SMOOTH);
}

bool Renderer::drawRect(vector4i _rect)
{
	if (!p_context || !p_camera) return false;
	Transform *transform=p_camera->getContainer();
	if (!transform) {
#ifdef LOG_CSAD
		Log::console("camera not have target");
#endif
		return false;
	}

	Scene *scene = p_camera->getScene();
	if (!scene) {
#ifdef LOG_CSAD
		Log::console("can not use null scene.");
#endif
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
		if (p_count>0) {
			if ((fmode & 0xf)==ZUP) _sortZUpNodes(p_tempfilter,0,p_count-1);
			if ((fmode & 0xf)==ZDOWN) _sortZDownNodes(p_tempfilter,0,p_count-1);
		}
		p_needUpdate=false;
	}

	_draw();

	//Render::PopAttrib();
	Render::Finish();
	return true;
}

void *Renderer::select(vector4i _rect)
{
	sFunctionsGLContext &functions=p_context->functions();

	if (!p_context || !p_camera) return false;
	Transform *transform=p_camera->getContainer();
	if (!transform) {
#ifdef LOG_CSAD
		Log::console("camera not have target");
#endif
		return 0;
	}

	//p_selected.clear();
	Scene *scene = p_camera->getScene();
	if (!scene) {
#ifdef LOG_CSAD
		Log::console("can not use null scene.");
#endif
		return 0;
	}

	if (!p_context->makeCurrent()) return false;
	functions.PushAttrib(GL_ALL_ATTRIB_BITS);
	p_camera->makeCurrent(_rect);

	scene->_setDefault();
	p_selected.clear();

	_validateUpdate(scene,p_camera);
	if (p_needUpdate) {
		_prepareNodes(p_camera);
		_fillFilter(scene);
		if (p_count>0) {
			if ((fmode & 0xf)==ZUP) _sortZUpNodes(p_tempfilter,0,p_count-1);
			if ((fmode & 0xf)==ZDOWN) _sortZDownNodes(p_tempfilter,0,p_count-1);
		}
		p_needUpdate=false;
	}

	//glClearColor(1,1,1,1);
	//glClear(GL_COLOR_BUFFER_BIT);
	functions.Enable(GL_DEPTH_TEST);
	functions.Clear(GL_DEPTH_BUFFER_BIT);
	functions.Disable(GL_LIGHTING);

	functions.SelectBuffer(32,p_selectBuffer);
	functions.RenderMode(GL_SELECT);
	functions.InitNames();
	functions.PushName(0);

	functions.PushMatrix();
	Transform *mtransform;
	MeshFilter *geom;
	for (unsigned int i=0;i<p_count;i++)
	{
		mtransform=p_tempfilter[i];
		if (!mtransform->isSelected()) continue;
		geom=mtransform->getComponent<MeshFilter>();
		if (geom) {
			functions.LoadName((GLuint)(i));

			matrix4f mMatrix;
			vector3f mpos(mtransform->realPosition());
			quaternionf mrot(mtransform->realRotate());
			vecFunctions.M4FTRS(&mMatrix,&mpos,&mrot,mtransform->realScale());
			functions.LoadMatrixf(mMatrix.m);

			functions.DrawMesh(geom);
		}
	}
	functions.PopMatrix();

	int count=functions.RenderMode(GL_RENDER);
	if (count>0) {
		if (count<0) count=32>>2;
		while (count>0) {
			count--;
			mtransform=p_tempfilter[p_selectBuffer[(count<<2)+3]];
			if (mtransform) {
				p_selected.assign(mtransform);
			}
		}
	}

	functions.PopName();
	Render::UnBindModel();

	functions.Enable(GL_DEPTH_TEST);

	functions.PopAttrib();
	//Render::Finish();
	return &p_selected;
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
	if (!p_context) return false;
	vector4i rect;
	rect.w=1;
	rect.z=1;
	if (p_input->set(BaseObject::TYPE,0)==(void*)Mouse::t()) {
		Mouse *mouse=(Mouse *)p_input;
		if (!mouse->getUpdata()) return true;
		vecFunctions.V2FTo2I(&mouse->getPos(),&rect);
		p_context->getDisplay()->toLocal((vector2i*)&rect,(vector2i*)&rect);
		select(rect);
		//selectSoft(rect);
	}
	if (p_input->set(BaseObject::TYPE,0)==(void*)Input::t()) {
		Input *input=(Input *)p_input;
		vecFunctions.V2FTo2I(&input->getCursorPos(),&rect);
		p_context->getDisplay()->toLocal((vector2i*)&rect,(vector2i*)&rect);
		selectSoft(rect);
	}
	if (p_selected.count()>0) {
		Transform **tr=(Transform **)p_selected.data();
		Transform *t=*tr;
		double z=(*tr)->realPosition()->z;
		if ((fmode & 0xf)==ZUP)
		for (unsigned int i=1;i<p_selected.count();i++) {
			tr++; if ((*tr)->realPosition()->z>z) t=*tr;
		}
		if ((fmode & 0xf)==ZDOWN)
		for (unsigned int i=1;i<p_selected.count();i++) {
			tr++; if ((*tr)->realPosition()->z<z) t=*tr;
		}
		t->setComponents(BaseObject::SELECT,t);
	}

	return true;
}

void Renderer::_draw()
{
	sFunctionsGLContext &functions=p_context->functions();
	MeshFilter *geom;
	Transform *mtransform;
	functions.DepthMask(0x1);
	functions.Clear(p_clear);

	unsigned int glerr=functions.GetError();
	if (glerr>0) {
#ifdef LOG_CSAD
		Log::console("Renderer::_draw glerror: %x",glerr);
#endif
	}

	Render::UnBindAll();
	functions.PushMatrix();

	Scene *scene = p_camera->getScene();
	LightingModel* dlmodel = scene->getDefaultLightingModel();

	void *key=MeshFilter::t();
	for (unsigned int i=0;i<p_count;i++)
	{
		mtransform=p_tempfilter[i];
		geom=(MeshFilter*)mtransform->getComponent(key);
		mtransform->render();
		if (geom) {
			LightingModel*lm=geom->getLightingModel();
			if (!lm) lm=dlmodel;

			Material *mat=geom->getMaterial();
			if (mat) {
				mat->bind();
				if (!mat->isLight()) lm=0;
			} else {
				Render::BindMaterial(0);
			}

			Render::BindLightingModel(lm);

			Shader *shader=geom->getShader();
			if (shader) {
				shader->bind();
			} else {
				p_context->bindShaderProg(0);
			}

			matrix4f mMatrix;
			vector3f mpos(mtransform->realPosition());
			quaternionf mrot(mtransform->realRotate());
			vecFunctions.M4FTRS(&mMatrix,&mpos,&mrot,mtransform->realScale());
			functions.LoadMatrixf(mMatrix.m);

			functions.DrawMesh(geom);
		}
	}
	functions.PopMatrix();
	Render::UnBindAll();
	p_context->bindShaderProg(0);

//	if (p_toTextureId) _copyToTexture();
}

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif
