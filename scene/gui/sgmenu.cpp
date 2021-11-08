/*
 * sgmenu.cpp
 *
 *  Created on: 26.11.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/gui/sgmenu.h>
#include <core/graph.h>
#include <scene/gui/sgelement.h>
#include <scene/gui/sgstyles.h>
#include <scene/transform.h>
#include <scene/text3d.h>
#include <scene/style.h>
#include <scene/textstyle.h>
#include <platform/font.h>
#include <core/input.h>

OPTIMIZE_ON;

namespace csad {

SGMenu::SGMenu()
	:p_pos(0.0f)
{
	p_isBuild=false;
	p_state=0;
	p_back=0;
	p_style=0;
	p_changes=0;
	mfirst=0;
}

SGMenu::~SGMenu()
{
}

void SGMenu::setPosition(float x,float y)
{
	p_pos.x=x;
	p_pos.y=y;
}

void SGMenu::setStyle(char *name)
{
	setStyle(csad::Graph::graph().getStyle(name));
}

void SGMenu::setStyle(csad::Style *style)
{
	p_style=style;
	_setStyleRecursive(getContainer());
	_recalc();
}

CSAD_API SGListElement *SGMenu::firstElement(csad::SGListElement *parent)
{
	csad::SceneComponent *fparent=parent;
	if (!fparent) fparent=this;
	SGListElement *button=SGListElement::anyElement(fparent);
	if (button) while ( button->prev() ) button=button->prev();
	return button;
}

CSAD_API SGListElement *SGMenu::lastElement(csad::SGListElement *parent)
{
	csad::SceneComponent *fparent=parent;
	if (!fparent) fparent=this;
	SGListElement *button=SGListElement::anyElement(fparent);
	if (button) while ( button->next() ) button=button->next();
	return button;
}

csad::SGListElement *SGMenu::addElement(csad::SGListElement *parent)
{
	csad::Transform *root;
	bool isRoot=!parent;
	if (!parent) {
		root=getContainer();
	} else {
		root=parent->getContainer();
	}
	if (!root) return 0;
	csad::SGListElement *button=lastElement(parent);

	csad::Transform *child=root->createTransform();

	csad::SGListElement *component=child->addComponent<csad::SGListElement>();
	//component->setMode(csad::SGListElement::SGE_SetSelect);
	if (!isRoot) component->setVisible(false);
	component->setReceiver(this);
	component->setMode(csad::SGListElement::SGE_SetButton);
	component->setUseStyle(csad::SGButtonStyle::t());
	component->setStyle(p_style);

	if (mfirst==0) mfirst=component;
	component->prev()=button;
	if (button) button->next()=component;
	return component;
}

csad::SGListElement *SGMenu::findElement(char *name,csad::SGListElement *parent)
{
	csad::Transform *root;
	bool isRoot=!parent;
	if (isRoot) {
		root=getContainer();
	} else {
		root=parent->getContainer();
	}
	if (!root) return 0;

	csad::TransformList::iterator it=root->children().begin();
	csad::TransformList::iterator end=root->children().end();

	int size=extFunctions.FindCMem(name,0,255);
	while ( it!=end ) 
	{
		csad::Transform *tr=it.value();
		it++;
		csad::SGListElement *button=tr->getComponent<csad::SGListElement>();
		if (!button || !button->text()) continue;
		const char *c=button->getText();
		int cmp=extFunctions.SubMem(name,(void*)c,size);
		if (cmp==0) return button;
	}
	return 0;
}

void SGMenu::removeElement(csad::SGListElement *element)
{
	if (mfirst==element) mfirst=element->next();
	if (element->prev()) element->prev()->next()=element->next();
	if (element->next()) element->next()->prev()=element->prev();
	delete element->getContainer();
}

/*void SGMenu::setCamera(csad::Camera * camera)
{
	p_camera=camera;
}*/

void SGMenu::start()
{
	_recalc();
}

void SGMenu::update()
{
	if (Input::input().getButton(Input::MOUSELEFT)) {
		p_state|=0x10;
	} else {
		if ((p_state&0x10)!=0) {
			p_state^=0x10;
			if ((p_state&0xC)==0x4) {
				if (isActive()) {
					p_state^=1;
					setVisibleAll(getContainer(),false);
				}
			}
			p_state&=~0xC;
		}
	}
	if (isAction()) {
		p_state^=2;
		if ((p_state&0xC)!=0x4) p_state&=~0xC;
	}
	if (p_isBuild) return;
	_recalc();
	p_isBuild=true;
}

void SGMenu::render()
{
	/*csad::GlContext* context=csad::GlContext::getCurrent();
	csad::Camera *camera=csad::Camera::camera();
	bt::vector4i view=camera->getViewPort(context);

	bt::vector3d &pos=getContainer()->getPosition();
	pos.x=(p_pos.x*view.z)/view.w;
	pos.y=p_pos.y;*/
	//view
}

void SGMenu::_action(csad::SGListElement * button)
{
	p_state|=2;
	csad::Transform *cont=getContainer();
	csad::Transform *parent=button->getContainer()->parent();
	if (button->getState()==csad::SGBaseElement::Click) {
		p_state|=8;
		if (parent==cont) {
			p_state^=1;
			if (isActive()) {
				setVisibleChilds(button,true);
			} else {
				setVisibleAll(cont,false);
			}
		} else {
			csad::Transform *root=button->getContainer();
			csad::TransformList::iterator it=root->children().begin();
			csad::TransformList::iterator end=root->children().end();
			bool ischildb=true;
			while ( ischildb && it!=end ) {
				if (it.value()->getComponent<csad::SGListElement>()) ischildb=false;
				it++;
			}
			if (ischildb) {
				setVisibleAll(cont,false);
				if (isActive()) p_state^=1;
				action(button);
				// action menu
			}
		}
	}
	if (button->getState()==csad::SGBaseElement::Normal) {
		p_state|=4;
	}
	if (button->getState()==csad::SGBaseElement::Active) {
		p_state|=8;
		//if (parent==cont) {
			if (isActive()) {
				setVisibleAll(parent,false);
				setVisibleChilds(button,true);
			}
		//}
	}
}

void SGMenu::action(csad::SGListElement * button)
{
}

void SGMenu::setVisibleChilds(csad::SGListElement * button,bool val)
{
	csad::Transform *root;
	root=button->getContainer();
	csad::TransformList::iterator it=root->children().begin();
	csad::TransformList::iterator end=root->children().end();

	while ( it!=end ) {
		csad::Transform *tr=it.value();
		it++;
		csad::SGListElement *button=tr->getComponent<csad::SGListElement>();
		if (!button) continue;
		button->setVisible(val);
		if (!val) setVisibleChilds(button,val);
	}
}

void SGMenu::setVisibleAll(csad::Transform * root,bool val)
{
	csad::TransformList::iterator it=root->children().begin();
	csad::TransformList::iterator end=root->children().end();

	while ( it!=end ) {
		csad::Transform *tr=it.value();
		it++;
		csad::SGListElement *button=tr->getComponent<csad::SGListElement>();
		if (!button) continue;
		setVisibleChilds(button,val);
	}
}

void *SGMenu::set(unsigned _int32 id,void * param)
{
	if (id==csad::BaseObject::TYPE) return SGMenu::t();
	if (id==csad::BaseObject::SELECT) _action((csad::SGListElement *)param);
	if (id==csad::BaseObject::WRITE) 
	{
		Variant *p;
		csad::ParametersList *list=(csad::ParametersList *)param;
		if (p=list->find("style")) setStyle(p->getString());
	}
	if (id==csad::BaseObject::READ) 
	{
		//csad::ParametersList *list=(csad::ParametersList *)param;
		return param;
	}
	return 0;
}

int SGMenu::_changes(csad::Transform *root)
{
	if (!root) return 0;

	csad::TransformList::iterator it=root->children().begin();
	csad::TransformList::iterator end=root->children().end();

	int c=0;

	while ( it!=end ) 
	{
		csad::Transform *tr=it.value();
		it++;
		csad::SGListElement *button=tr->getComponent<csad::SGListElement>();
		if (!button || !button->text()) continue;
		csad::Text3D *text=button->text()->getComponent<csad::Text3D>();
		//button->setStyle(p_style);
		c+=text->changes();
		//c+=button->changes();
		c+=_changes(tr);
	}
	return c;
}

void SGMenu::_setStyleRecursive(csad::Transform *root)
{
	if (!root) return;

	csad::TransformList::iterator it=root->children().begin();
	csad::TransformList::iterator end=root->children().end();

	while ( it!=end ) 
	{
		csad::Transform *tr=it.value();
		it++;
		csad::SGListElement *button=tr->getComponent<csad::SGListElement>();
		if (!button) continue;
		button->setStyle(p_style);
		_setStyleRecursive(tr);
	}
}

void SGMenu::_recalc()
{
	csad::Transform *root;
	root=getContainer();
	if (!root) return;

	//csad::TransformList::iterator it=root->children().begin();
	//csad::TransformList::iterator end=root->children().end();

	csad::vector3d pos(0.0);
	p_elementSize.x=0;
	p_elementSize.y=10.0;
	p_elementSize.z=0;
	if (p_style) 
	{
		TextStyle *textStyle=p_style->getComponent<csad::TextStyle>();
		if (textStyle->getFont()) 
		{
			p_elementSize.y=(float)(textStyle->getCharSize()*textStyle->getFont()->getSize()*0.9);
		}
	}

	csad::SGListElement *first=firstElement();

	while ( first ) 
	{
		csad::Transform *tr=first->getContainer();//it.value();
		//it++;
		csad::SGListElement *button=first;//tr->getComponent<csad::SGMenuElement>();
		csad::Text3D *text=button->text()->getComponent<csad::Text3D>();
		//csad::vector3d center=text->textCenter();
		csad::vector3d tsize=text->textSize();
		p_elementSize.x=(float)(tsize.x*0.5+p_elementSize.y*0.7);
		button->setSize(p_elementSize);
		pos.x+=p_elementSize.x;
		pos.y=-p_elementSize.y;
		tr->setPosition(pos);
		pos.x+=p_elementSize.x;
		_recalc(tr,-p_elementSize.x,-p_elementSize.y*2);
		first=first->next();
	}
}

void SGMenu::_recalc(csad::Transform *root,float x, float y)
{
	if (!root) return;

	csad::TransformList::iterator it=root->children().begin();
	csad::TransformList::iterator end=root->children().end();

	float xs=0;
	csad::SGListElement *first=0;
	while ( it!=end ) 
	{
		csad::Transform *tr=it.value();
		it++;
		csad::SGListElement *button=tr->getComponent<csad::SGListElement>();
		if (!button || !button->text()) continue;
		if (!first || first->prev()) first=button;
		csad::Text3D *text=button->text()->getComponent<csad::Text3D>();
		csad::vector3d tsize=text->textSize();
		if (xs<tsize.x) xs=(float)tsize.x;
	}
	xs=xs*0.5f+p_elementSize.y*0.7f;

	//it=root->children().begin();
	csad::vector3d pos(x+xs,y,0);
	while ( first ) 
	{
		csad::Transform *tr=first->getContainer();//it.value();
		//it++;
		csad::SGListElement *button=first;//tr->getComponent<csad::SGListElement>();
		csad::Text3D *text=button->text()->getComponent<csad::Text3D>();
		//csad::vector3d center=text->textCenter();
		csad::vector3d tsize=text->textSize();
		p_elementSize.x=xs;
		button->setSize(p_elementSize);
		tr->setPosition(pos);
		pos.y-=p_elementSize.y*2;
		_recalc(tr,xs,0);
		first=first->next();
	}
}

TYPEINFO(SGMenu)

};

OPTIMIZE_OFF;
