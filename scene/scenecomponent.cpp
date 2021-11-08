/*
 * scenecomponent.cpp
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/scenecomponent.h>
#include <scene/transform.h>

namespace csad {

SceneComponent::SceneComponent()
{
}

SceneComponent::~SceneComponent()
{
}

void SceneComponent::prepare()
{

}

void SceneComponent::render()
{

}

void SceneComponent::select()
{

}

Transform * SceneComponent::getContainer()
{
	if (!p_parent) return 0;
	if (p_parent->type()!=Transform::t()) return 0;
	return (Transform *)p_parent;
}

TYPEINFO(SceneComponent);

}

