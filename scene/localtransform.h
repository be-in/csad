/*
 * localtransform.h
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef INTERNAL_TRANSFORM_H_
#define INTERNAL_TRANSFORM_H_

#include <scene/transform.h>
#include <bt.h>

namespace csad {

using namespace bt;

class Scene;

/**
 * @class LocalTransform
 *
 * @ingroup scene
 * @brief LocalTransform - a key element of the environment specifies the position of the object.
 *
 * @see Transform, Scene, scene
 */

class LocalTransform: public Transform {
public:
	LocalTransform(char* name,Transform *parent=0);
	LocalTransform(Scene *scene,char* name,Transform *parent=0);
	LocalTransform(Scene *scene,const char* name="",Transform *parent=0);

	~LocalTransform();

	Transform *createTransform(char *name);

	Transform *getTransform(char *name);

	void setParent(Transform *);

	///
	void deleteChilds();

	void detachChilds();

	void detachChild(Transform* child);

	void addChild(Transform*);

	Transform * Child(int id);

	Transform& setPosition(double x,double y,double z);
	Transform& setPosition(vector3d &pos);
	Transform& setPosition(const vector3d &pos);
	Transform& setScale(float x,float y,float z);
	Transform& setScale(const vector3f &_scale);
	Transform& setRotate(quaterniond &_rotate);
	Transform& setRotate(const quaterniond &_rotate);

	void setChildReal(Transform *transform);
	void setParentReal(Transform *transform);

	void setVisible(bool);
	void setSelected(bool);
	void setSprite(bool);
	void setFixScale(bool);

	void prepare();
	void render();

	_FORCEINLINE void setDestroy() {p_flags|=DESTROY;}

//	Component *addComponent(char * name);
	//Known components

//	_FORCEINLINE MeshFilter *getGeometry() {return getComponent<MeshFilter>();}
//	_FORCEINLINE Camera *getCamera() {return getComponent<Camera>();}
	//Geometry *getMaterial();

	void *set(unsigned _int32 ,void *);

	void* operator new(size_t size);
	void operator delete(void* val);

private:

	enum EVENT {
		UPDATE = 0x00010000,
		PREPARE = 0x00020000,
		RENDER = 0x00040000,
	};

	void _init();

};

}

#endif /* TRANSFORM_H_ */
