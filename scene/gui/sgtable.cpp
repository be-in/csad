/*
 * sgtable.cpp
 *
 *  Created on: 05.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/gui/sgtable.h>
#include <scene/gui/sgstyles.h>
#include <scene/transform.h>
#include <scene/text3d.h>
#include <scene/meshfilter.h>
#include <scene/mesh.h>
#include <scene/style.h>
#include <scene/textstyle.h>
#include <scene/camera.h>
#include <core/graph.h>
#include <core/system.h>
#include <core/input.h>
#include <core/containercomponents.h>
#include <components/resender.h>
#include <platform.h>

OPTIMIZE_ON;

namespace csad {

SGTable::SGTable()
{
	mstate=0;
	mstyle=0;
}

SGTable::~SGTable()
{
}

SGTable &SGTable::setColumns(unsigned int cols)
{
	mcolumns=cols;
	mstate&=~0x1;
	return *this;
}
	
SGTable &SGTable::setRecords(unsigned int recs)
{
	mrecords=recs;
	mstate&=~0x1;
	return *this;
}

/*SGTable& SGTable::setHeaderText(unsigned int id,char*name)
{
	return *this;
}

char *SGTable::getHeaderText(unsigned int id)
{
	return 0;
}

SGListElement *SGTable::getHeader(unsigned int id)
{
	return 0;
}*/

SGListElement *SGTable::getCell(unsigned int record,unsigned int column)
{
	SGListElement *button=SGListElement::anyElement(this);
	if (button) {
		while ( button->prev() ) button=button->prev();
		while ( button->next() && (record>0) ) {
			button=button->next();
			record--;
		}
		if (column>0) {
			column--;
			button=SGListElement::anyElement(button);
			if (button) {
				while ( button->prev() ) button=button->prev();
				while ( button->next() && (column>0) ) {
					button=button->next();
					column--;
				}
			}
		}
	}
	return button;
}

SGTable& SGTable::setSize(vector3f &size)
{
	msize=size;
	return *this;
}

SGTable& SGTable::setColumnWidth(unsigned int id,float width)
{
	SGListElement *button=getCell(0,id);
	if (button) {
		vector3f cs=button->getSize();
		cs.x=width;
		button->setSize(cs);
	}
	mstate&=~0x2;
	return *this;
}

SGTable& SGTable::setRecordHeight(unsigned int id,float height)
{
	SGListElement *button=getCell(id,0);
	if (button) {
		vector3f cs=button->getSize();
		cs.y=height;
		button->setSize(cs);
	}
	mstate&=~0x2;
	return *this;
}

void SGTable::setStyle(char *name)
{
	setStyle(csad::Graph::graph().getStyle(name));
}

void SGTable::setStyle(csad::Style *style)
{
	mstyle=style;
	//_setStyleRecursive(getContainer());
	//mstate&=~0x2;
}

void SGTable::start()
{

}

void SGTable::update()
{
	if ((mstate&0x1)==0) _build();
	if ((mstate&0x2)==0) _recalc();
}

void * SGTable::set(unsigned _int32 id,void * param)
{
	if (id==BaseObject::TYPE) return SGTable::t();
	//if (id==csad::BaseObject::SELECT) _action((csad::SGListElement *)param);
	if (id==csad::BaseObject::WRITE) 
	{
		Variant *p;
		csad::ParametersList *list=(csad::ParametersList *)param;
		if (p=list->find("style")) setStyle(p->getString());
	}
	return 0;
}

SGListElement *SGTable::_addElement(csad::SGListElement *parent)
{
	csad::SceneComponent *fparent=parent;
	if (!fparent) fparent=this;
	SGListElement *button=SGListElement::anyElement(fparent);
	if (button) while ( button->next() ) button=button->next();
	csad::Transform *root=fparent->getContainer();
	csad::Transform *child=root->createTransform();

	csad::SGListElement *component=child->addComponent<csad::SGListElement>();
	component->setReceiver(this);
	component->setMode(csad::SGListElement::SGE_SetButton);
	component->setUseStyle(csad::SGButtonStyle::t());
	component->setStyle(mstyle);

	vector3f elementSize(20,10,0);
	if (mstyle) 
	{
		TextStyle *textStyle=mstyle->getComponent<csad::TextStyle>();
		if (textStyle->getFont()) 
		{
			elementSize.y=(float)(textStyle->getCharSize()*textStyle->getFont()->getSize()*0.9);
		}
	}
	component->setSize(elementSize);

	component->prev()=button;
	if (button) button->next()=component;
	return component;
}

SGListElement *SGTable::_addNext(csad::SGListElement *prev)
{
	if (!prev) return 0;
	csad::Transform *root=prev->getContainer()->parent();
	csad::Transform *child=root->createTransform();

	csad::SGListElement *component=child->addComponent<csad::SGListElement>();
	component->setReceiver(this);
	component->setMode(csad::SGListElement::SGE_SetButton);
	component->setUseStyle(csad::SGButtonStyle::t());
	component->setStyle(mstyle);

	vector3f elementSize(20,10,0);
	if (mstyle) 
	{
		TextStyle *textStyle=mstyle->getComponent<csad::TextStyle>();
		if (textStyle->getFont()) 
		{
			elementSize.y=(float)(textStyle->getCharSize()*textStyle->getFont()->getSize()*0.9);
		}
	}
	component->setSize(elementSize);
	component->prev()=prev;
	prev->next()=component;
	return component;
}

void SGTable::_recalc()
{
	if ((mstate&0x2)!=0) return;
	bt::vector3d cpos(0,0,0);
	SGListElement *button=SGListElement::anyElement(this);
	if (button) {
		while ( button->prev() ) button=button->prev();
		SGListElement *first=button;
		SGListElement *lfirst=0;
		while ( button ) {
			float width=first->getSize().x;
			float height=button->getSize().y;
			if (first!=button) {
				vector3f vl=button->getSize();
				vl.x=width;
				button->setSize(vl);
			}

			cpos.x=0;
			bt::vector3d &pos=button->getContainer()->getPosition();
			cpos.y-=height;
			pos=cpos;

			SGListElement *rbutton=SGListElement::anyElement(button);
			if (rbutton) {
				while ( rbutton->prev() ) rbutton=rbutton->prev();
				if (!lfirst) lfirst=rbutton;
				SGListElement *lbutton=lfirst;
				while (rbutton) {
					cpos.x+=width;
					vector3f vl=rbutton->getSize();
					width=lbutton->getSize().x;
					vl.x=width;
					vl.y=height;
					cpos.x+=width;
					bt::vector3d &pos=rbutton->getContainer()->getPosition();
					pos=cpos;
					pos.y=0;
					rbutton->setSize(vl);
					lbutton=lbutton->next();
					rbutton=rbutton->next();
				}
			}
			cpos.y-=height;
			button=button->next();
		}
	}
	mstate|=0x2;
}

void SGTable::_build()
{
	if ((mstate&0x1)!=0) return;
	SGListElement *button=SGListElement::anyElement(this);
	int frecords=(int)mrecords;
	if (mcolumns==0) frecords=0;
	if (button) {
		while ( button->prev() ) button=button->prev();
		frecords--;
		while ( button->next() ) {
			frecords--;
			_buildRecord(button);
			button=button->next();
		}
	}
	while ( frecords<0 && button->prev() ) {
		SGListElement *sbutton=button->prev();
		delete button;
		button=sbutton;
		frecords++;
	}
	while ( frecords>0 ) {
		SGListElement *sbutton;
		if (button) sbutton=_addNext(button); else sbutton=_addElement();
		_buildRecord(sbutton);
		button=sbutton;
		frecords--;
	}
	mstate|=0x1;
}

void SGTable::_buildRecord(SGListElement *parent)
{
	int fcolumns=(int)mcolumns;
	fcolumns--;
	SGListElement *button=SGListElement::anyElement(parent);
	if (button) {
		while ( button->prev() ) button=button->prev();
		fcolumns--;
		while ( button->next() ) {
			fcolumns--;
			button=button->next();
		}
	}
	while ( fcolumns<0 && button->prev() ) {
		SGListElement *sbutton=button->prev();
		delete button;
		button=sbutton;
		fcolumns++;
	}
	while ( fcolumns>0 ) {
		SGListElement *sbutton;
		if (button) sbutton=_addNext(button); else sbutton=_addElement(parent);
		button=sbutton;
		fcolumns--;
	}
}

TYPEINFO(SGTable)

}

OPTIMIZE_OFF;
