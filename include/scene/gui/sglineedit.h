/*
 * sglineedit.h
 *
 *  Created on: 05.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef SGLINEEDIT_H_
#define SGLINEEDIT_H_

#include <scene/gui/sgbaseelement.h>

namespace csad {

WARNING_DISABLE;
OPTIMIZE_ON;

class Transform;
class Style;

/**
 * @class SGLineEdit
 *
 * @ingroup scenegui
 * @brief SGLineEdit - component
 *
 *
 * For description in the configuration:
 @verbatim
   <Transform name="the name of the scene">
       <SGLineEdit size="0.3 0.1 0.0" text="test text"/>
   </Transform>
 @endverbatim
 *
 * @see Transform, SGLineEditStyle, SGBaseElement, scenegui
 */

class SGLineEdit: public SGBaseElement {
public:
	MEMDEFAULT(SGLineEdit)

	CSAD_API SGLineEdit();
	CSAD_API ~SGLineEdit();

	/// Задать редактируемый текст
	CSAD_API void setText(char *text);
	/// Задать редактируемый текст
	_FORCEINLINE void setText(const char *text) {setText((char*)text);}
	/// Возвращает текст (компоненты Text3D)
	CSAD_API const char *getText();
	/// Задает стиль
	CSAD_API void setStyle(char *name);
	/// Задает стиль
	CSAD_API void setStyle(Style *style);
	///
	CSAD_API bool setUseStyle(void *type);
	///
	CSAD_API bool setUseStyle(char *styleType);
	/// Задать размер поля ввода
	CSAD_API void setSize(vector3f &size);

	/// Задает состояние активности редактирования.
	CSAD_API void setSet(bool val);
	CSAD_API void setState(unsigned int val);
	_FORCEINLINE unsigned int getState() {return p_state & (0xF | SGE_Set);}
	/// Returns true if set status Click
	_FORCEINLINE bool isClick() {return (p_state & (0xF))==Click;}

	/// Задает состояние видимости
	CSAD_API void setVisible(bool val);

	CSAD_API void setReceiver(char *path);
	CSAD_API void setReceiver(BaseObject* obj);

	_FORCEINLINE Transform *back() {return p_back;}
	_FORCEINLINE Transform *text() {return p_text;}

	CSAD_API void start();
	CSAD_API void update();

	virtual void click() {}
	virtual void edit() {}

	//int changes() {return p_changes;}

	CSAD_API void * set(unsigned _int32 ,void *);

	CSAD_API TYPEINFO_H

private:
	//
	vector3f p_size;
	//
	unsigned int p_state;
	unsigned int p_changes;
	BaseObject* p_reciver;
	Style *p_style;
	void *p_useStyle;
	unsigned int feditpos;

	void _init();
	void _initImage();
	void* _select(BaseObject *item);

	Transform *p_back;
	Transform *p_text;
	Transform *p_cursor;

	void _textreset();
	void _textwrite(char);
	void _textremove();
};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* SGLINEEDIT_H_ */
