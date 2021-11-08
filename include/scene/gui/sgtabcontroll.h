/*
 * sgtabcontroll.h
 *
 *  Created on: 16.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef TABCONTROLL_H_
#define TABCONTROLL_H_

#include <scene/scenecomponent.h>
#include <bt.h>

namespace csad {

using namespace bt;

class Transform;
class SGElement;
class SGListElement;

/**
 * @class SGTabControll
 *
 * @ingroup scenegui
 * @brief SGTabControll - .
 *
 * For description in the configuration:
 @verbatim
   <Transform name="TabList">
      <SGTabControll keys="TabKeys"/>
   </Transform>
 @endverbatim
 *
 * @see scenegui, SGButton
 */

class SGTabControll: public SceneComponent {
public:
	MEMDEFAULT(SGTabControll)

	CSAD_API SGTabControll();

	CSAD_API SGListElement *addElement(csad::SGListElement *parent=0);

	/*void setAction(csad::SGElement *tr);
	void setAction(char *tr);

	void setWidget(csad::Transform *tr);
	void setWidget(char *tr);*/

	/*CSAD_API void addActionGroup(csad::Transform *tr);
	CSAD_API void addActionGroup(char *name);

	CSAD_API void setWidgetGroup(csad::Transform *tr);
	CSAD_API void setWidgetGroup(char *name);*/

	CSAD_API void * set(unsigned _int32 ,void *);

	CSAD_API TYPEINFO_H

private:
	 csad::SGListElement *mfirst;

};

}

#endif /* TABCONTROLL_H_ */
