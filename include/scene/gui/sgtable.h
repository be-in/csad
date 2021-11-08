/*
 * sgtable.h
 *
 *  Created on: 05.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef SGTABLE_H_
#define SGTABLE_H_

#include <scene/gui/sgelement.h>
#include <bt.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

class Transform;
class Style;

/**
 * @class SGTable
 *
 * @ingroup scenegui
 * @brief SGTable - component
 *
 *
 * For description in the configuration:
 @verbatim
   <Transform name="the name of the scene">
       <SGTable size="0.3 0.1 0.0" columns="3" records="10"/>
   </Transform>
 @endverbatim
 *
 * @see SGBaseElement, scenegui
 */

class SGTable: public SceneComponent {
public:
	MEMDEFAULT(SGTable)

	CSAD_API SGTable();
	CSAD_API ~SGTable();

	CSAD_API SGTable& setColumns(unsigned int);
	
	CSAD_API SGTable& setRecords(unsigned int);

	/*CSAD_API SGTable& setHeaderText(unsigned int id,char*name);
	CSAD_API char *getHeaderText(unsigned int id);
	CSAD_API SGListElement *getHeader(unsigned int id);*/
	CSAD_API SGListElement *getCell(unsigned int record,unsigned int column);

	CSAD_API SGTable& setSize(vector3f &size);
	CSAD_API SGTable& setColumnWidth(unsigned int id,float width);
	CSAD_API SGTable& setRecordHeight(unsigned int id,float height);

	/// Задать редактируемый текст
	/*CSAD_API void setText(char *text);
	_FORCEINLINE void setText(const char *text) {setText((char*)text);}
	/// возвращает текст (компоненты Text3D)
	CSAD_API const char *getText();*/
	///
	CSAD_API void setStyle(char *name);
	CSAD_API void setStyle(Style *style);
	_FORCEINLINE Style *style() {return mstyle;}

	/*CSAD_API bool setUseStyle(char *styleType);
	///
	CSAD_API void setSize(vector3f &size);
	CSAD_API void setSet(bool val);
	CSAD_API void setState(unsigned int val);
	_FORCEINLINE unsigned int getState() {return p_state & (0xF | SGE_Set);}

	CSAD_API void setVisible(bool val);

	CSAD_API void setReceiver(char *path);
	CSAD_API void setReceiver(BaseObject* obj);

	_FORCEINLINE Transform *back() {return p_back;}
	_FORCEINLINE Transform *text() {return p_text;}
	*/
	CSAD_API void start();
	CSAD_API void update();

	/*virtual void click() {}
	virtual void edit() {}*/

	//int changes() {return p_changes;}

	CSAD_API void * set(unsigned _int32 ,void *);

	CSAD_API TYPEINFO_H

private:
	//
	vector3f msize;
	//
	unsigned int mstate;
	Style *mstyle;
	/*unsigned int p_changes;
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
	void _textremove();*/
	unsigned int mcolumns;
	unsigned int mrecords;

	SGListElement *_addElement(csad::SGListElement *parent=0);
	SGListElement *_addNext(csad::SGListElement *prev);
	void _recalc();
	void _build();
	void _buildRecord(SGListElement *parent);
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* SGTABLE_H_ */
