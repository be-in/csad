/*
 * transform.h
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <core/containercomponents.h>
#include <bt.h>

namespace csad {

using namespace bt;

class Transform;

typedef SortVoidVector<Transform> TransformList;

class Scene;
class SceneComponent;

/**
 * @class Transform
 *
 * @ingroup scene
 * @brief Transform - a key element of the environment specifies the position of the object.
 *
 * Object allows you to organize position and recalculation of coordinates for building orientation of the object relative to the calculation point.
 * This allows to minimize, and in some cases eliminate, the loss of accuracy.
 *
 * For description in the configuration:
 * @verbatim
   <Scene name="myScene">
     <Transform name="the name of the transform" pos="x y z of position" rot="x y z and angle rotation" scale="x y z of scale">
	   ... internal objects or components ...
     </Transform>
   </Scene>
 * @endverbatim
 *
 * @see scene Scene ContainerComponents
 */

class Transform: public ContainerComponents {
public:
	MEMNULL

	/// Adds the component of the specified type in the container if this component already exists, returns available.
	template <typename T>
	_FORCEINLINE T* addComponent() {
		void * tp=T::t();
		SceneComponent **c=(SceneComponent **)arrFunctions.MPFind(&p_list,tp);
		if (!c) c = (SceneComponent **)addContainerComponentByInfo(this, new T(), tp);
		return static_cast<T*>(*c);
	}

	/// creates a dependent object.
	virtual Transform *createTransform(char *name) = 0;
	_FORCEINLINE Transform *createTransform(const char *name="") {return createTransform((char*)name);}

	/// restores the dependent object by name.
	virtual Transform *getTransform(char *name) = 0;
	_FORCEINLINE Transform *getTransform(const char *name) {return getTransform((char*)name);}

	/// returns the parent object.
	_FORCEINLINE Transform *parent() {return p_parent;}
	virtual void setParent(Transform *) = 0;

	/// delete all childs.
	virtual void deleteChilds() = 0;

	virtual void detachChilds() = 0;

	/// remove transform from child list.
	virtual void detachChild(Transform* child) = 0;

	/// insert transform to child list.
	virtual void addChild(Transform*) = 0;

	/// the list of dependent objects.
	TransformList &children() {return p_childs;}
	/// returns number of dependent objects.
	_FORCEINLINE unsigned int ChildCount() {return p_childs.count();}
	/// returns child objects by id.
	/// @param id - is a position object in child list;
	virtual Transform * Child(int id) = 0;

	/// sets the position of the object
	/// @param x,y,z - coordinates relative to the coordinate system of the parent object
	virtual Transform& setPosition(double x,double y,double z) = 0;
	/// sets the position of the object
	/// @param pos - coordinates relative to the coordinate system of the parent object
	virtual Transform& setPosition(vector3d &pos) = 0;
	/// sets the position of the object
	/// @param pos - coordinates relative to the coordinate system of the parent object
	virtual Transform& setPosition(const vector3d &pos) = 0;
	_FORCEINLINE vector3d &getPosition() {return p_position;}
	/// sets the scale of the object
	/// @param x,y,z - the scale of the axes relative to the scale of the parent object
	virtual Transform& setScale(float x,float y,float z) = 0;
	/// sets the scale of the object
	/// @param pos - the scale relative to the scale of the parent object
	virtual Transform& setScale(const vector3f &_scale) = 0;
	_FORCEINLINE vector3f &getScale() {return p_scale;}
	virtual Transform& setRotate(quaterniond &_rotate) = 0;
	/// sets the reversal of the object
	/// @param _rotate - quaternion razvorot relation to the position of the parent object
	virtual Transform& setRotate(const quaterniond &_rotate) = 0;
	_FORCEINLINE quaterniond &getRotate() {return p_rotate;}

	/// returns the actual position of the object
	_FORCEINLINE vector3d *realPosition() {return &p_realPos;}
	/// returns the real scale
	_FORCEINLINE vector3f *realScale() {return &p_realScale;}
	/// returns the real razvorot object
	_FORCEINLINE quaterniond *realRotate() {return &p_realRotate;}

	/// recalculation of the actual point down the hierarchy of objects
	/// @param transform - the object on which is made recalculation.
	virtual void setChildReal(Transform *transform) = 0;
	/// recalculation real coordinates up and down the hierarchy of objects
	/// @param transform - the object on which is made recalculation.
	virtual void setParentReal(Transform *transform) = 0;

	/// sets the object visible.
	virtual void setVisible(bool) = 0;
	_FORCEINLINE bool isVisible() {return (p_flags&VISIBLE)!=0;}
	/// specifies a choice object.
	virtual void setSelected(bool) = 0;
	_FORCEINLINE bool isSelected() {return (p_flags&SELECTED)!=0;}
	/// the reversal of the object relative to the camera.
	virtual void setSprite(bool) = 0;
	_FORCEINLINE bool isSprite() {return (p_flags&SPRITE)!=0;}
	virtual void setFixScale(bool) = 0;
	_FORCEINLINE bool isFixScale() {return (p_flags&FIXSCALE)!=0;}
	_FORCEINLINE bool isDestroy() {return (p_flags&DESTROY)!=0;}

	//unsigned int flags

	virtual void prepare() = 0;
	virtual void render() = 0;
	/// returns the scene to which an object belongs.
	_FORCEINLINE Scene *getScene() {return p_scene;}

	CSAD_API const char * getName();

	CSAD_API static Transform *finder(char *path);

	CSAD_API TYPEINFO_H

protected:
	enum hideFlags {
		VISIBLE = 0x00000001,
		SELECTED = 0x00000002,
		SPRITE = 0x00000004,
		FIXSCALE = 0x00000008,
		DESTROY = 0x00000010,
		DISABLE = 0x00000020
	};

	unsigned int p_flags;
	vector3d p_position;
	quaterniond p_rotate;
	vector3f p_scale;

	vector3d p_realPos;
	quaterniond p_realRotate;
	vector3f p_realScale;

	Scene *p_scene;
	Transform *p_parent;
	TransformList p_childs;

friend class Scene;
};

}

#endif /* TRANSFORM_H_ */
