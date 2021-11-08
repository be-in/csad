/*
 * transform.cpp
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include "localtransform.h"
#include <scene/scene.h>
#include <scene/scenecomponent.h>
#include <core/graph.h>
#include <core/core.h>
#include <platform.h>
#include "csad/bt/base/basevector.h"
#include "csad/core/base/stringconsts.h"

OPTIMIZE_ON;

namespace csad {

LocalTransform::LocalTransform(char* name,Transform *parent)
{
	p_parent=parent;
	p_scene=0;
	_init();
	if (p_scene!=0) {
		if (name && name[0]) {
			p_scene->p_transforms.addObject(this,name);
		} else {
			p_scene->getObjects().assign(this);
		}
		p_scene->change();
	}
}

LocalTransform::LocalTransform(Scene *scene,char* name,Transform *parent)
{
	p_parent=parent;
	p_scene=scene;
	_init();
	if (p_scene!=0) {
		if (name && name[0]) {
			p_scene->p_transforms.addObject(this,name);
		} else {
			p_scene->getObjects().assign(this);
		}
		p_scene->change();
	}
}

LocalTransform::LocalTransform(Scene *scene,const char* name,Transform *parent)
{
	p_parent=parent;
	p_scene=scene;
	_init();
	if (p_scene!=0) {
		if (name && name[0]) {
			p_scene->p_transforms.addObject(this,name);
		} else {
			p_scene->getObjects().assign(this);
		}
		p_scene->change();
	}
}

void LocalTransform::_init()
{
	p_flags=VISIBLE;
	p_position=vector3d(0.0);
	p_rotate.reset(); //=quaterniond(0,0,0,0);
	p_scale=vector3f(1.0f);
	if ((p_parent!=0) && (p_scene==0)) p_scene=((LocalTransform*)p_parent)->p_scene;
	if (p_scene==0) p_scene=Scene::p_default;
	if (p_scene!=0) {
		if (p_parent==0) p_parent=p_scene->p_root;
	}
	if (p_parent!=0) {
		p_parent->addChild(this);
		if (!p_parent->isVisible()) p_flags^=VISIBLE;
	}
}

LocalTransform::~LocalTransform()
{
	if (p_parent) {
		((LocalTransform*)p_parent)->p_childs.del(this);
		p_parent=0;
	}
	if (p_scene) {
		p_scene->detachObject(this);
		p_scene->change();
	}
	deleteChilds();
}

Transform *LocalTransform::createTransform(char *name)
{
	return p_scene->createTransform(name,this);
}

Transform *LocalTransform::getTransform(char *name)
{
	return p_scene->getTransform(name);
}

void LocalTransform::setParent(Transform *parent)
{
	if (p_parent!=0) {
		p_parent->detachChild(this);
	}
	parent->addChild(this);
	p_scene->p_changes++;
}

void LocalTransform::deleteChilds()
{
	if (p_childs.count()==0) return;
	TransformList::iterator it=p_childs.begin();
	TransformList::iterator end=p_childs.end();
	while (it!=end) {
		LocalTransform* tr=(LocalTransform*)it.value();
		tr->p_parent=0;
/*		if (tr->p_scene) if ((tr->p_scene->p_flags&Scene::DETACHLOCK)!=0) {
			tr->p_scene->p_changes++;
			tr->p_scene->p_flags|=Scene::NEEDCLEAN;
			tr->p_scene=0;
			tr->deleteChilds();
		} else*/
		delete tr;
		it++;
	}
	p_childs.clear();
}

void LocalTransform::detachChilds()
{
	if (p_childs.count()==0) return;
	TransformList::iterator it=p_childs.begin();
	TransformList::iterator end=p_childs.end();
	while (it!=end) {
		((LocalTransform*)it.value())->p_parent=0;
		it++;
	}
	p_childs.clear();
}

Transform * LocalTransform::Child(int id)
{
	return p_childs[id];
}

Transform& LocalTransform::setPosition(double x,double y,double z)
{
	bool b=p_position.x==x; //???
	if (b) b=p_position.y==y;
	if (b) b=p_position.z==z;
	if (!b) {
		p_position.x=x;
		p_position.y=y;
		p_position.z=z;
		p_scene->p_changes++;
	}
	return *this;
}

Transform& LocalTransform::setPosition(vector3d &pos)
{
	p_position=pos;
	p_scene->p_changes++;
	return *this;
}

Transform& LocalTransform::setPosition(const vector3d &pos)
{
	p_position=pos;
	p_scene->p_changes++;
	return *this;
}

/*void Transform::setPosition(const vector3d pos)
{
	p_position=pos;
	p_scene->p_changes++;
}*/

Transform& LocalTransform::setScale(float x,float y,float z)
{
	p_scale.x=x;
	p_scale.y=y;
	p_scale.z=z;
	p_scene->p_changes++;
	return *this;
}

Transform& LocalTransform::setScale(const vector3f &_scale)
{
	p_scale=_scale;
	p_scene->p_changes++;
	return *this;
}

Transform& LocalTransform::setRotate(quaterniond &_rotate)
{
	p_rotate=_rotate;
	p_scene->p_changes++;
	return *this;
}

Transform& LocalTransform::setRotate(const quaterniond &_rotate)
{
	p_rotate=_rotate;
	p_scene->p_changes++;
	return *this;
}

void LocalTransform::setChildReal(Transform *transform)
{
	Transform *mtransform;
	TransformList &mlist=children();
	if (mlist.count()==0) return;
	if (transform!=this) {
		vector3d lscale=vector3d(&p_realScale);
		matrix4d mTr;
//		bt::_M4DTRSDEF(&mTr, (double*)&p_realPos, (double*)&p_realRotate, (double*)&lscale);
		vecFunctions.M4DTRS(&mTr,&p_realPos,&p_realRotate,&lscale);
		TransformList::iterator it=mlist.begin();
		TransformList::iterator end=mlist.end();
		while (it!=end) {
			mtransform=it.value();
			if (mtransform!=transform) {
				vecFunctions.V3DTransform(&mtransform->getPosition(),&mTr,mtransform->realPosition());
				//*mtransform->realPosition()=mTr.transform(mtransform->getPosition());
				if (!mtransform->isSprite()) {
					vecFunctions.QDMul(&mtransform->getRotate(),&p_realRotate,mtransform->realRotate());
					//*mtransform->realRotate()=mtransform->getRotate() * p_realRotate;
				} else {
					*mtransform->realRotate()=mtransform->getRotate();
				}
				if (!mtransform->isFixScale()) {
					vecFunctions.V3FMul(&(mtransform->getScale()),&p_realScale,mtransform->realScale());
				} else {
					*mtransform->realScale() = mtransform->getScale();
				}
				mtransform->setChildReal(0);
			}
			it++;
		}
	} else {
		TransformList::iterator it=mlist.begin();
		TransformList::iterator end=mlist.end();
		while (it!=end) {
			mtransform=it.value();
			*mtransform->realPosition()=mtransform->getPosition();
			*mtransform->realRotate()=mtransform->getRotate();
			*mtransform->realScale()=mtransform->getScale();
			mtransform->setChildReal(0);
			it++;
		}
	}
}

void LocalTransform::setParentReal(Transform *transform)
{
	Transform* mtransform=parent();
	if (transform==this) {
		p_realPos=vector3d(0.0,0.0,0.0);
		p_realRotate.reset();//=p_rotate;
		p_realScale=vector3d(1.0,1.0,1.0);
	} else {
		if (!isSprite()) {
			vecFunctions.QDInv(&(transform->getRotate()),&p_realRotate);
			vecFunctions.QDMul(&p_realRotate,transform->realRotate(),&p_realRotate);
			//p_realRotate=transform->getRotate().invert()*(*transform->realRotate());
		} else {
			p_realRotate=p_rotate;
		}
		vector3f frealScale=transform->getScale();
		if (frealScale.x!=0) frealScale.x=1/frealScale.x;
		if (frealScale.y!=0) frealScale.y=1/frealScale.y;
		if (frealScale.z!=0) frealScale.z=1/frealScale.z;
		frealScale=(*transform->realScale())*frealScale;
		p_realScale=frealScale;
		if (frealScale.x==0) frealScale.x=1;
		if (frealScale.y==0) frealScale.y=1;
		if (frealScale.z==0) frealScale.z=1;
		p_realPos=(*transform->realPosition())-(transform->getPosition()*frealScale)*p_realRotate.invert();
	}
	setChildReal(transform);
	if (mtransform) mtransform->setParentReal(this);
}

void LocalTransform::setVisible(bool visible)
{
	if (((p_flags & VISIBLE)!=0)!=visible) {
		p_scene->p_changes++;
		p_flags^=VISIBLE;
	}
}

void LocalTransform::setSelected(bool select)
{
	if (((p_flags & SELECTED)!=0)!=select) {
		p_scene->p_changes++;
		p_flags^=SELECTED;
	}
}

void LocalTransform::setSprite(bool sprite)
{
	if (((p_flags & SPRITE)!=0)!=sprite) {
		p_scene->p_changes++;
		p_flags^=SPRITE;
	}
}

void LocalTransform::setFixScale(bool sprite)
{
	if (((p_flags & FIXSCALE)!=0)!=sprite) {
		p_scene->p_changes++;
		p_flags^=FIXSCALE;
	}
}

SceneComponent sc;

void LocalTransform::prepare()
{
	//bt::tfFASTCALL_PROC **vtp=(bt::tfFASTCALL_PROC**)&sc;
	//bt::tfFASTCALL_PROC **vtpc;
	void **it=(void **)arrFunctions.MPArray(&p_list);
	void **end=it;
	end+=arrFunctions.MPCount(&p_list)<<1;
	it++;
	while (it<end) {
		SceneComponent *component=(SceneComponent *)*it;
		//vtpc=(bt::tfFASTCALL_PROC**)component;
		//if ((*vtpc)[6]!=(*vtp)[6])
			component->prepare();
		it+=2;
	}
}

void LocalTransform::render()
{
	void **it=(void **)arrFunctions.MPArray(&p_list);
	void **end=it;
	end+=arrFunctions.MPCount(&p_list)<<1;
	it++;
	while (it<end) {
		SceneComponent *component=(SceneComponent *)*it;
		component->render();
		it+=2;
	}
}

void *LocalTransform::set(unsigned _int32 id,void *param)
{
	if (id==BaseObject::TYPE) return Transform::t();
	if (id==BaseObject::CONTAINER) return this;
	if (id==BaseObject::SELECT) {
		setComponents(id,param);
		return 0;
	}
	if (id==BaseObject::WRITE) {
		Variant *p;
		ParametersList *list=(ParametersList *)param;
		if ((p=list->find("pos"))!=0) setPosition(p->getVector3d());
		if ((p=list->find("rotate"))!=0) setRotate(quaterniond(p->getVector4d()));
		if ((p=list->find(STR_SCALE))!=0) setScale(p->getVector3f());
		if ((p=list->find("visible"))!=0) setVisible(p->getBool());
		if ((p=list->find("selected"))!=0) setSelected(p->getBool());
		if ((p=list->find("sprite"))!=0) setSprite(p->getBool());
		return 0;
	}
	if (id==BaseObject::READ) {
		Variant *p;
		ParametersList *list=(ParametersList *)param;
		p=&(*list)["pos"];
		p->setVector3d(&p_position);
		p=&(*list)["rotate"];
		bt::vector4d rtvector(&p_rotate);
		p->setVector4d((vector4d*)&rtvector);
		p=&(*list)[STR_SCALE];
		p->setVector3f(&p_scale);
		p=&(*list)["visible"];
		p->setBool(isVisible());
		p=&(*list)["selected"];
		p->setBool(isSelected());
		p=&(*list)["sprite"];
		p->setBool(isSprite());
		p=&(*list)["childs"];
		p->setInt(p_childs.count());
		return param;
	}
	if (id==BaseObject::MANAGER) return 0;
	if (id==BaseObject::MANAGER_COUNT) return 0;
	if (id==BaseObject::LIST) {
		unsigned int idt=(unsigned int)(_voidint)param;
		if (idt<p_childs.count()) return p_childs.at(idt);
		return 0;
	}
	if (id==BaseObject::LIST_COUNT) return (void*)(_voidint)p_childs.count();
	if (id==BaseObject::NAME) return (void*)getName();
	return 0;
}

void* LocalTransform::operator new(size_t size)
{
	return internalmemmanager.getNew((unsigned int)size);
}

void LocalTransform::operator delete(void* val)
{
	LocalTransform *tr=(LocalTransform *)val;
	if (!tr->isDestroy()) {
		if ((tr->getScene()!=0) && ((tr->getScene()->p_flags&Scene::DETACHLOCK)!=0)) {
			tr->getScene()->p_flags|=Scene::NEEDCLEAN;
			tr->p_scene=0;
			tr->setDestroy();
		} else internalmemmanager.freeThis(val,sizeof(Transform));
	}
}

const char * Transform::getName()
{
	const char *key=0;
	key=p_scene->getMapObjects().key((void*)this,key);
	if (key==0) {
		int pos=p_scene->getObjects().find(this);
		return numName(pos);
	}
	return key;
}

Transform *Transform::finder(char *path)
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
	Transform *transform=scene->getTransform(find.getNext());
	if (!transform) {
#ifdef LOG_CSAD
		Log::console("Can`t find transform: %s",find.getNext());
#endif
		return 0;
	}
	find.next();
	return transform;
}

void LocalTransform::addChild(Transform* child)
{
	p_childs.assign((Transform*)child);
	((LocalTransform*)child)->p_parent=this;
}

void LocalTransform::detachChild(Transform* child)
{
	p_childs.del((Transform*)child);
	((LocalTransform*)child)->p_parent=0;
}

TYPEINFO(Transform)

}

OPTIMIZE_OFF;
