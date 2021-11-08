/*
 * sgelement.h
 *
 *  Created on: 06.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef SGELEMENT_H_
#define SGELEMENT_H_

#include <scene/gui/sgbaseelement.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

class Transform;

/**
 * @class SGElement
 *
 * @ingroup scenegui
 * @brief SGElement - component, which is the action controller, defines the characteristics of the image and manages events.
 *
 * To handle events keys, you must install a handler recipient using the SGElement::setReceiver.
 * Event processing is performed in the method BaseObject::set when the parameter id==BaseObject::SELECT, and the second parameter contains a pointer to the component type SGButton.
 * This can be any object of a class inherited from the BaseObject class or his descendants.
 *
 * For description in the configuration:
 @verbatim
   <Scene name="myKeyScene">
     <Transform name="name of the button" pos="0 0 0" scale="0.1 0.1 0.1">
	   <SGElement size="0.1 0.05 0" text="key text" style="buttonstyle"/>
     </Transform>
   </Scene>
 @endverbatim
 *
 * @see scenegui, Style, TextStyle, SGButtonStyle, BaseObject
 */

class SGElement: public SGBaseElement {
public:
	MEMMANAGER(SGElement)

	CSAD_API SGElement();
	CSAD_API ~SGElement();

	/// Specifies the text of the button
	CSAD_API SGElement& setText(char *text);
	_FORCEINLINE SGElement& setText(const char *text) { return setText((char*)text); }
	/// returns the text of the element (components Text3D)
	CSAD_API const char *getText();
	/// Sets the style named
	CSAD_API SGElement& setStyle(char *name);
	/// Specifies the style object
	CSAD_API SGElement& setStyle(Style *style);
	/// Тип стиля, может быть выбран SGStyle, SGButtonStyle, SGElementStyle.
	CSAD_API bool setUseStyle(char *styleType);
	CSAD_API bool setUseStyle(void *type);
	/// Specifies the size of the button
	CSAD_API SGElement& setSize(vector3f &size);
	_FORCEINLINE vector3f getSize() {return p_size;}

	CSAD_API SGElement& setSet(bool val);
	/// Returns true if set check button
	_FORCEINLINE bool isSet() {return (p_state&SGE_Set)!=0;}

	CSAD_API SGElement& setOpen(bool val);
	_FORCEINLINE bool isOpen() {return (p_state&SGE_Opened)!=0;}

	CSAD_API SGElement& setState(unsigned int val);
	_FORCEINLINE unsigned int getState() {return p_state & (0xF | SGE_Set);}
	/// Returns true if set status Click
	_FORCEINLINE bool isClick() {return (p_state & (0xF))==Click;}
	/// Returns true if the installed state of the Active
	_FORCEINLINE bool isActive() {return (p_state & (0xF))==Active;}
	/// Returns true if installed, the Normal state
	_FORCEINLINE bool isNormal() {return (p_state & (0xF))==Normal;}
	/// Returns true if the installed condition Disable
	_FORCEINLINE bool isDisable() {return (p_state & (0xF))==Disable;}

	CSAD_API SGElement& setMode(unsigned int val);
	_FORCEINLINE unsigned int getMode() {return (p_state & (0xF000));}
	/// Sets the visibility of all the elements of a button
	CSAD_API SGElement& setVisible(bool val);
	/// Specifies the recipient's events on his way
	/// @see BaseObject::SELECT
	CSAD_API SGElement& setReceiver(char *path);
	/// Specifies the recipient object
	/// @see BaseObject::SELECT
	CSAD_API SGElement& setReceiver(BaseObject* obj);

	_FORCEINLINE Transform *back() {return p_back;}
	_FORCEINLINE Transform *image() {return p_image;}
	_FORCEINLINE Transform *key() {return p_key;}
	_FORCEINLINE Transform *text() {return p_text;}

	CSAD_API void start();
	CSAD_API void update();

	virtual void click() {}

	_FORCEINLINE int changes() {return p_changes;}

	CSAD_API void * set(unsigned _int32 ,void *);

	CSAD_API TYPEINFO_H

private:
	// the size of the element
	vector3f p_size;
	// the state of the element
	unsigned int p_state;
	unsigned int p_changes;
	//unsigned int p_newState;
	BaseObject* p_reciver;
	Style *p_style;
	void *p_useStyle;

	void _init();
	void _initImage();
	void* _select(BaseObject*);

	Transform *p_back;
	Transform *p_image;
	Transform *p_key;
	Transform *p_text;
};

class SGListElement: public SGElement
{
public:
	MEMMANAGER(SGListElement)

	_FORCEINLINE SGListElement():p_prev(0),p_next(0) {}
	_FORCEINLINE ~SGListElement() {}

	_FORCEINLINE csad::SGListElement *&prev() {return p_prev;}
	_FORCEINLINE csad::SGListElement *&next() {return p_next;}

	CSAD_API void *set(unsigned _int32 ,void *);

	CSAD_API static csad::SGListElement *anyElement(csad::SceneComponent *base);

	CSAD_API TYPEINFO_H

private:
	csad::SGListElement *p_prev;
	csad::SGListElement *p_next;
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* SGELEMENT_H_ */
