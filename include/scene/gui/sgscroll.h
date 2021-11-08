/*
 * sgscroll.h
 *
 *  Created on: 10.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef SGSCROLL_H_
#define SGSCROLL_H_

#include <scene/gui/sgbaseelement.h>

namespace csad {

WARNING_DISABLE;

class Transform;
class Style;
class SGButton;

/**
 * @class SGScroll
 *
 * @ingroup scenegui
 * @brief SGScroll - component, which is the controller of the scrolls, defines the characteristics of the image and manages events.
 *
 * @see scenegui
 */

class SGScroll: public SGBaseElement {
public:
	MEMDEFAULT(SGScroll)

	CSAD_API SGScroll();
	CSAD_API ~SGScroll();

	/// Sets the style named
	CSAD_API void setStyle(char *name);
	/// Задает объект стиля
	CSAD_API void setStyle(Style *style);

	CSAD_API bool setUseStyle(char *styleType);
	/// Задает размер полосы
	CSAD_API SGScroll & setSize(vector3f &size);
	CSAD_API SGScroll & setState(unsigned int val);
	_FORCEINLINE unsigned int getState() {return p_state & (0xF);}

	CSAD_API SGScroll & setCount(int val);
	CSAD_API SGScroll & setPageSize(int val);
	CSAD_API SGScroll & setVal(int val);
	_FORCEINLINE int count() {return fmaxpos;}
	_FORCEINLINE int val() {return fpos;}

	CSAD_API void setVisible(bool val);

	CSAD_API SGScroll & setSubKey(SGButton* val);
	CSAD_API SGScroll & setAddKey(SGButton* val);

	/// Задает получателя событий по его пути
	/// @see BaseObject::SELECT
	CSAD_API void setReceiver(char *path);
	/// Задает объект получателя
	/// @see BaseObject::SELECT
	CSAD_API void setReceiver(BaseObject* obj);

	_FORCEINLINE Transform *back() {return p_back;}
	_FORCEINLINE Transform *scroll() {return p_scroll;}

	CSAD_API void start();
	CSAD_API void update();

	CSAD_API void prepare();

	virtual void change() {}

	//int changes() {return p_changes;}

	CSAD_API void * set(unsigned _int32 ,void *);

	CSAD_API TYPEINFO_H

private:
	// размер кнопки
	vector3f p_size;
	// состояние кнопки
	unsigned int p_state;
	unsigned int p_changes;
	unsigned int fpos;
	unsigned int fmaxpos;
	unsigned int fpagesize;
	//unsigned int p_newState;
	//int p_changes;
	BaseObject* p_reciver;
	Style *p_style;
	void *p_useStyle;
	bt::vector2f flastpos;

	void _init();
	void _initImage();
	void* _select(BaseObject *item);
	void _calc();

	Transform *p_back;
	Transform *p_scroll;
	SGButton *p_subkey;
	SGButton *p_addkey;
};

WARNING_ENABLE;

}

#endif /* SGSCROLL_H_ */
