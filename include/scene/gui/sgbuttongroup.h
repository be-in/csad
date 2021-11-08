/*
 * sgbuttongroup.h
 *
 *  Created on: 17.12.2013
 *      Author: Пантелеймонов А
 */

#ifndef SGBUTTONGROUP_H_
#define SGBUTTONGROUP_H_

#include <scene/scenecomponent.h>

namespace csad {

class SGButton;

class SGButtonGroup: public SceneComponent {
public:
	CSAD_API SGButtonGroup();

	CSAD_API void addElement(SGButton *element);

private:
	HashVector<SGButton *> p_list;
};

}

#endif /* SGBUTTONGROUP_H_ */
