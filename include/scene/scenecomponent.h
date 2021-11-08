/*
 * scenecomponent.h
 *
 *  @brief Complex software application developer, MS Visual C++ 2003-2010, QNX Momentics IDE
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef SCENECOMPONENT_H_
#define SCENECOMPONENT_H_

#include <core/component.h>

namespace csad {

using namespace bt;

class Transform;

/**
 * @class SceneComponent
 *
 * @ingroup scene
 * @brief SceneComponent - a component is a unique part of the object may not have a name, and to exist independently.
 *
 * The component has a pointer to the container to which he belongs.
 *
 *
 * @see scene
 */

class SceneComponent: public Component {
public:
	MEMNULL

	CSAD_API SceneComponent();
	CSAD_API virtual ~SceneComponent();

	/// The event is called during the preparation stage.
	CSAD_API virtual void prepare();

	/// The event is called during the rendering of the model.
	CSAD_API virtual void render();

	/// The event is called during handling of a choice of object - crossing with ray.
	CSAD_API virtual void select();

	/// Returns the container in which the component
	CSAD_API Transform * getContainer();

	/// Add component of the specified type in the container if this component already exists, returns available.
	template <typename T>
	_FORCEINLINE T* addComponent() {
		void *tp=T::t();
		Component *c=Component::getComponent(tp);
		T* ret = static_cast<T*>(c);
		if (!c) ret=static_cast<T*>(Component::addComponent(new T(), tp));
		return ret;
	}

	/// Returns the component of the given type, if it is not in a container returns 0.
	template <typename T>
	_FORCEINLINE T* getComponent() {
		return static_cast<T*>(Component::getComponent(T::t()));
	}

	//_FORCEINLINE Scene *scene() { return getContainer()->getScene(); }

	CSAD_API TYPEINFO_H

friend class Transform;
};

}

#endif /* COMPONENT_H_ */
