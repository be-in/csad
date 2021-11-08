/*
 * sgmenu.h
 *
 *  Created on: 25.11.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef SGMENU_H_
#define SGMENU_H_

#include <scene/gui/sgelement.h>
#include <core/classmanager.h>
#include <bt.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

class Transform;
class SGButton;

class SGMenu: public SceneComponent 
{
public:
	MEMDEFAULT(SGMenu)

	CSAD_API SGMenu();
	CSAD_API ~SGMenu();

	CSAD_API void setPosition(float x,float y);

	///
	CSAD_API void setStyle(char *name);
	CSAD_API void setStyle(csad::Style *style);
	_FORCEINLINE Style *style() {return p_style;}

	CSAD_API SGListElement *firstElement(csad::SGListElement *parent=0);
	CSAD_API SGListElement *lastElement(csad::SGListElement *parent=0);
	CSAD_API SGListElement *addElement(csad::SGListElement *parent=0);
	CSAD_API SGListElement *findElement(char *name,csad::SGListElement *parent=0);
	CSAD_API void removeElement(csad::SGListElement *element);

	//void setCamera(csad::Camera *camera);
	CSAD_API void start();
	CSAD_API void update();
	CSAD_API void render();

	CSAD_API virtual void action(csad::SGListElement * button);

	CSAD_API void setVisibleChilds(csad::SGListElement *button,bool val);
	CSAD_API void setVisibleAll(csad::Transform * root,bool val);

	_FORCEINLINE int changes() {return p_changes;}

	_FORCEINLINE bool isActive() { return (p_state & 1)!=0; }
	_FORCEINLINE bool isAction() { return (p_state & 2)!=0; }

	CSAD_API void *set(unsigned _int32 ,void *);

	CSAD_API TYPEINFO_H

private:
	bt::vector2f p_pos;
	csad::SGListElement *mfirst;
	csad::Style *p_style;
	csad::Transform *p_back;
	bt::vector3f p_elementSize;
	bool p_isBuild;
	int p_state;
	int p_changes;

	int _changes(csad::Transform *root);

	void _setStyleRecursive(csad::Transform *root);

	void _recalc();
	void _recalc(csad::Transform *root,float x,float y);

	void _action(csad::SGListElement * button);
};

};

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* MENU_H_ */
