/*
 * sgbutton.h
 *
 *  Created on: 10.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef SGBUTTON_H_
#define SGBUTTON_H_

#include <scene/gui/sgelement.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

class Transform;
class Style;
class Text3D;

/**
 * @class SGButton
 *
 * @ingroup scenegui
 * @brief SGButton - component, which is the controller buttons, defines the characteristics of the image and manages events.
 *
 * To handle events keys, you must install a handler recipient using the SGButton::setReceiver.
 * Event processing is performed in the method BaseObject::set when the parameter id==BaseObject::SELECT, and the second parameter contains a pointer to the component type SGButton.
 * This can be any object of a class inherited from the BaseObject class or his descendants.
 *
 * For description in the configuration:
 @verbatim
   <Scene name="myKeyScene">
     <Transform name="name of the button" pos="0 0 0" scale="0.1 0.1 0.1">
	   <SGButton size="0.1 0.05 0" text="key text" style="buttonstyle"/>
     </Transform>
   </Scene>
 @endverbatim
 *
 * @see scenegui, Style, TextStyle, SGButtonStyle, BaseObject
 */

class SGButton: public SGElement {
public:
	MEMMANAGER(SGButton)

	CSAD_API SGButton();
	CSAD_API ~SGButton();

	CSAD_API void * set(unsigned _int32 ,void *);

	CSAD_API TYPEINFO_H

private:
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* SGBUTTON_H_ */
