/*
 * sgbaseelement.h
 *
 *  Created on: 06.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef SGBASEELEMENT_H_
#define SGBASEELEMENT_H_

#include <scene/scenecomponent.h>
#include <bt.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

using namespace bt;

class Transform;
class Text3D;
class Material;
class Style;

/**
 * @class SGBaseElement
 *
 * @ingroup scenegui
 * @brief SGBaseElement - base class for gui elements.
 *
 * @see SGElement, SGListElement, scenegui
 */

class SGBaseElement:public SceneComponent {
public:
	MEMDEFAULT(SGBaseElement)

	CSAD_API SGBaseElement();
	CSAD_API ~SGBaseElement();

	enum State {
		/// not active state
		Normal = 0x0,
		/// key active
		Active = 0x1,
		/// a key is pressed
		Click = 0x2,
		/// the item is disabled
		Disable = 0x3,
		/// the item is selected (for a group of buttons)
		SGE_Set = 0x100,
		///
		SGE_isBuild = 0x200,
		///
		SGE_isBack = 0x400,
		///
		SGE_needUpdate = 0x800,
		/// button mode
		SGE_SetButton = 0x0000,
		/// mode
		SGE_SetSelect = 0x1000,
		/// inversion mode
		SGE_SetSwitch = 0x2000,
		/// inversion key mode
		SGE_SetOpen = 0x3000,
		/// indicate state
		SGE_Opened = 0x10000,
		///
		SGE_isKey = 0x20000,
		///
		SGE_KeyLock = 0x40000,
		/// режим ориентации вертикальный
		SGE_Vertical = 0x00000,
		/// режим ориентации горизонтальный
		SGE_Horisontal = 0x80000,
		/// is event end
		SGE_End = 0x100000,
	};

protected:
	void _setMaterial(Transform *tr,Material*mat);
	Transform* _initBack(Transform *tr,vector3f *size,float back);
	Transform* _initBackInput(Transform *tr,vector3f *size,float back);
	Transform* _initKeyInput(Transform *tr,vector3f *size,BaseObject *res,float back);
	Transform* _initText(Transform *tr,char *text,Style *style);
	Text3D* _initText(Transform **tr);
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* SGBASEELEMENT_H_ */
