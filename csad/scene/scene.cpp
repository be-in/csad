/*
 * scene.cpp
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/scene.h>
#include "localtransform.h"
#include <scene/camera.h>
#include <scene/lightingmodel.h>
#include <platform.h>
#include <core/graph.h>
#include <core/core.h>

namespace csad {

OPTIMIZE_ON;

Scene *Scene::p_default=0;

Scene::Scene(char *name)
	//:p_addontransforms(sizeof(void*))
	:p_addontransforms()
{
	_init();
	Graph::graph().p_scene->addObject(this,name);
}

Scene::Scene(const char *name)
	//:p_addontransforms(sizeof(void*))
	:p_addontransforms()
{
	_init();
	Graph::graph().p_scene->addObject(this,name);
}

void Scene::_init()
{
	p_flags=ACTIVE;
	p_root=0;
	p_root=new LocalTransform(this);
	p_root->p_scene=this;
	p_count=0;
	//p_list=0;
	p_changes=0;
}

Scene::~Scene()
{
	Graph::graph().p_scene->detachObject(this);
	_destroyTransforms();
	_destroyLightingModels();
	p_root=0;
	//delete p_root;
}

Camera * Scene::createCamera(char *name,Transform * parent) {
	Transform * tr = createTransform(name,parent);
	Camera * cam = tr->addComponent<Camera>();
	return cam;
}

Camera * Scene::createCamera(const char *name,Transform * parent) {
	Transform * tr = createTransform(name,parent);
	Camera * cam = tr->addComponent<Camera>();
	return cam;
}

Transform *Scene::createTransform(char *name,Transform * parent)
{
	if ((name!=0) && (name[0]!=0)) {
		Transform * r=(Transform *)p_transforms.getObject(name);
		if (r) return r;
	}
	return new LocalTransform(this,name,parent);
}

Transform *Scene::createTransform(const char *name,Transform * parent)
{
	if ((name!=0) && (name[0]!=0)) {
		Transform * r=(Transform *)p_transforms.getObject(name);
		if (r) return r;
	}
	return new LocalTransform(this,name,parent);
}

Camera *Scene::getCamera(char *name)
{
	Transform *transform = (Transform *)p_transforms.getObject(name);
	if (!transform) return 0;
	return transform->getComponent<Camera>();
}

Camera *Scene::getCamera(const char *name)
{
	Transform *transform = (Transform *)p_transforms.getObject(name);
	return transform->getComponent<Camera>();
}

LightingModel *Scene::createLightingModel(char *name)
{
	if ((name!=0) && (name[0]!=0)) {
		LightingModel *ret=(LightingModel *)p_lightingmodels.getObject(name);
		if (ret) return ret;
	}
	return new LightingModel(this,name);
}

Transform *Scene::getTransform(char *name)
{
	return (Transform *)p_transforms.getObject(name);
}

Transform *Scene::getTransform(const char *name)
{
	return (Transform *)p_transforms.getObject(name);
}

void Scene::detachObject(Transform *transform)
{
	if ((p_flags&DETACHLOCK)!=0) {
		p_flags|=Scene::NEEDCLEAN;
		return;
	}
	if (!p_transforms.detachObject(transform)) {
		p_addontransforms.del(transform);
	}
}

void Scene::setActive(bool val)
{
	if (val!=active())p_flags^=ACTIVE;
}

const char * Scene::getName()
{
	return Graph::graph().p_scene->getName(this);
}

void *Scene::set(unsigned _int32 id,void *param)
{
	if (id==BaseObject::TYPE) return Scene::t();
	if (id==BaseObject::CONTAINER) return p_root;
	if (id==BaseObject::MANAGER) return &p_transforms;
	if (id==BaseObject::MANAGER_COUNT) return (void*)1;
	if ((id==BaseObject::LIST) ||
		(id==BaseObject::LIST_COUNT) ||
		(id==BaseObject::WRITE) ||
		(id==BaseObject::READ)) return p_root->set(id,param);
	//if (id==BaseObject::)
	//if (id==ListAll)
	return 0;
}

void Scene::_start()
{
	ObjectsList &list=p_transforms.getObjects();
	ObjectsList::iterator it=list.begin();
	ObjectsList::iterator end=list.end();
	while (it!=end) {
		Transform *tr=(Transform *)it.value();
		tr->start();
		it++;
	}

	ListSceneTransforms listadd;
	ListSceneTransforms &listis=getObjects();
	listadd.absorb(listis);

	ListSceneTransforms::iterator ait=listadd.begin();
	ListSceneTransforms::iterator aend=listadd.end();
	while (ait!=aend) {
		Transform *tr=(Transform *)ait.value();
		tr->start();
		ait++;
	}
	if (listis.count()>0) listadd.add(listis);
	listis.absorb(listadd);
}

void Scene::_update()
{
	p_flags|=DETACHLOCK;

	ObjectsList &list=p_transforms.getObjects();
	ObjectsList::iterator it=list.begin();
	ObjectsList::iterator end=list.end();
	while (it!=end) {
		LocalTransform *tr=(LocalTransform *)it.value();
		//if (tr->list().count()>0)
			if (!tr->isDestroy()) tr->update();
		it++;
	}

	ListSceneTransforms listadd;
	ListSceneTransforms &listis=getObjects();
	listadd.copy(listis);

	ListSceneTransforms::iterator ait=listadd.begin();
	ListSceneTransforms::iterator aend=listadd.end();
	while (ait!=aend) {
		LocalTransform *tr=(LocalTransform *)ait.value();
		//if (tr->list().count()>0) 
			if (!tr->isDestroy()) tr->update();
		ait++;
	}
	//if (listis.count()>0) listadd.add(listis);
	//listis.absorb(listadd);

	p_flags^=DETACHLOCK;
	if ((p_flags&NEEDCLEAN)!=0) _checkClean();
}

void Scene::_prepare()
{
	ObjectsList &list=p_transforms.getObjects();
	ObjectsList::iterator it=list.begin();
	ObjectsList::iterator end=list.end();
	while (it!=end) {
		Transform *tr=(Transform *)it.value();
		//if (tr->list().count()>0)
			tr->prepare();
		it++;
	}

	ListSceneTransforms::iterator ait=getObjects().begin();
	ListSceneTransforms::iterator aend=getObjects().end();
	while (ait!=aend) {
		Transform *tr=(Transform *)ait.value();
		//if (tr->list().count()>0)
			tr->prepare();
		ait++;
	}
}

void Scene::_render()
{
	ObjectsList &list=p_transforms.getObjects();
	ObjectsList::iterator it=list.begin();
	ObjectsList::iterator end=list.end();
	while (it!=end) {
		Transform *tr=(Transform *)it.value();
		//if (tr->list().count()>0)
			tr->render();
		it++;
	}

	ListSceneTransforms::iterator ait=getObjects().begin();
	ListSceneTransforms::iterator aend=getObjects().end();
	while (ait!=aend) {
		Transform *tr=(Transform *)ait.value();
		//if (tr->list().count()>0)
			tr->render();
		ait++;
	}
}

/*void Scene::_select()
{
	ObjectsList &list=p_transforms.getObjects();
	ObjectsList::iterator it=list.begin();
	ObjectsList::iterator end=list.end();
	while (it!=end) {
		Transform *tr=(Transform *)it.value();
		tr->render();
		it++;
	}

	ListSceneTransforms::iterator ait=getObjects().begin();
	ListSceneTransforms::iterator aend=getObjects().end();
	while (ait!=aend) {
		Transform *tr=(Transform *)ait.value();
		tr->select();
		ait++;
	}
}*/

void Scene::_quit()
{

	ObjectsList &list=p_transforms.getObjects();
	ObjectsList::iterator it=list.begin();
	ObjectsList::iterator end=list.end();
	while (it!=end) {
		Transform *tr=(Transform *)it.value();
		tr->quit();
		it++;
	}

	ListSceneTransforms::iterator ait=getObjects().begin();
	ListSceneTransforms::iterator aend=getObjects().end();
	while (ait!=aend) {
		Transform *tr=(Transform *)ait.value();
		tr->quit();
		ait++;
	}
}

void Scene::_setDefault()
{
	p_default=this;
}

void Scene::_destroyTransforms()
{
	if ((p_flags&DETACHLOCK)==0) p_flags^=DETACHLOCK;
	ObjectsList &list=p_transforms.getObjects();
	ObjectsList::iterator it=list.begin();
	ObjectsList::iterator end=list.end();
	while (it!=end) {
		Transform *tr=(Transform *)it.value();
		tr->children().clear();
		tr->p_scene=0;
		tr->p_parent=0;
		delete tr;
		it++;
	}
	list.clear();

	ListSceneTransforms::iterator ait=getObjects().begin();
	ListSceneTransforms::iterator aend=getObjects().end();
	while (ait!=aend) {
		Transform *tr=(Transform *)ait.value();
		tr->children().clear();
		tr->p_scene=0;
		tr->p_parent=0;
		delete tr;
		ait++;
	}
	getObjects().clear();
	p_flags^=DETACHLOCK;
}

void Scene::_destroyLightingModels()
{
	if ((p_flags&DETACHLOCK)==0) p_flags^=DETACHLOCK;
	ObjectsList &list=p_transforms.getObjects();
	ObjectsList::iterator it=list.begin();
	ObjectsList::iterator end=list.end();
	while (it!=end) {
		LightingModel *lm=(LightingModel *)it.value();
		lm->fscene=0;
		delete lm;
		it++;
	}
	list.clear();
	p_flags^=DETACHLOCK;
}

void Scene::_checkClean()
{
	VoidVector<Transform> trs;

	ObjectsList &list=p_transforms.getObjects();
	ObjectsList::iterator it=list.begin();
	ObjectsList::iterator end=list.end();
	while (it!=end) {
		Transform *tr=(Transform *)it.value();
		if (tr->p_scene!=this) trs.assign(tr);
		it++;
	}

	int tc=trs.count();
	for (int i=0;i<tc;i++) {
		Transform *tr=trs[i];
		p_transforms.detachObject(tr);
		if ((tr->p_flags&Transform::DESTROY)!=0) {
			tr->p_flags^=Transform::DESTROY;
			LocalTransform::operator delete(tr);
		}
	}
	if (tc>0) trs.clear();

	ListSceneTransforms::iterator ait=getObjects().begin();
	ListSceneTransforms::iterator aend=getObjects().end();
	while (ait!=aend) {
		Transform *tr=(Transform *)ait.value();
		if (tr->p_scene!=this) trs.assign(tr);
		ait++;
	}

	tc=trs.count();
	for (int i=0;i<tc;i++) {
		Transform *tr=trs[i];
		//p_addontransforms._del(&tr);
		p_addontransforms.del(tr);
		if ((tr->p_flags&Transform::DESTROY)!=0) {
			tr->p_flags^=Transform::DESTROY;
			LocalTransform::operator delete(tr);
		}
	}
	if (tc>0) trs.clear();

	if ((p_flags&NEEDCLEAN)==0) p_flags^=NEEDCLEAN;
}

TYPEINFO(Scene)

OPTIMIZE_OFF;

}
