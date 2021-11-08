/*
 * sgelement.cpp
 *
 *  Created on: 06.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/gui/sgelement.h>
#include <scene/gui/sgstyles.h>
#include <core/graph.h>
#include <core/system.h>
#include <core/input.h>
#include <scene/transform.h>
#include <scene/text3d.h>
#include <scene/meshfilter.h>
#include <scene/mesh.h>
#include <scene/style.h>
#include <scene/textstyle.h>
#include <scene/camera.h>
#include "csad/core/base/stringconsts.h"

OPTIMIZE_ON;

namespace csad {

SGElement::SGElement()
{
	p_back=0;
	p_image=0;
	p_key=0;
	p_text=0;
	p_state=0;
	p_style=0;
	p_size=vector3f(1,1,0);
	p_reciver=0;
	p_state=Active | SGE_SetSelect;
	p_useStyle=SGElementStyle::t();
	p_changes=0;
}

SGElement::~SGElement()
{
}

SGElement& SGElement::setText(char *text)
{
	//p_text=_initText(p_text,text,p_style);
	if (!text && p_text) {
		delete p_text;
	} else if (text) {
		p_text=_initText(p_text,text,p_style);
	}
	return *this;
}

const char *SGElement::getText()
{
	if (!p_text) return 0;
	Text3D *mtext = _initText(&p_text);
	if (!mtext) return 0;
	return mtext->text();
}

SGElement& SGElement::setStyle(char *name)
{
	return setStyle(Graph::graph().getStyle(name));
}

SGElement& SGElement::setStyle(Style *style)
{
	p_style=style;
	if (p_text) p_text=_initText(p_text,0,p_style);
	return *this;
}

bool SGElement::setUseStyle(char *styleType)
{
	ObjectInfo *info=ContainerComponents::getInfo(styleType);
	if (!info) return false;
	return setUseStyle(info->type);
}

bool SGElement::setUseStyle(void *type)
{
	if (!type) return false;
	if ((type==SGButtonStyle::t())
			|| (type==SGElementStyle::t())
			|| (type==SGStyle::t())
			|| (type==SGLineEditStyle::t())) {
		p_useStyle=type;
		return true;
	}
	return false;
}

SGElement& SGElement::setSize(vector3f &size)
{
	p_size=size;
	p_back=_initBackInput(p_back,&p_size,-p_size.y*0.01f);
	if (p_text) {
		int anc=csad::TextStyle::Center;
		Text3D *mtext = _initText(&p_text);
		if (mtext->textStyle()) anc=mtext->textStyle()->getAnchor();
		vector3d pos(0.0);
		if ((anc&csad::TextStyle::Left)!=0) {
			pos.x=-p_size.x*0.8;
		} if ((anc&csad::TextStyle::Right)!=0) {
			pos.x=p_size.x*0.8;
		}
		if ((anc&csad::TextStyle::Top)!=0) {
			pos.y=p_size.y*0.8;
		} if ((anc&csad::TextStyle::Bottom)!=0) {
			pos.y=-p_size.y*0.8;
		}
		p_text->setPosition(&pos);
		p_changes=mtext->changes();
	}
	if (p_key) {
		float k=p_size.x;
		if (p_size.x>p_size.y) k=p_size.y;
		vector3f ks(k);
		p_key=_initKeyInput(p_key,&ks,this,0);
		p_key->setPosition(k-p_size.x,0,0);
	}
	return *this;
}

SGElement& SGElement::setSet(bool val)
{
	if (((p_state&SGE_Set)!=0)!=val) p_state^=SGE_Set;
	p_state|=SGE_needUpdate;
	return *this;
}

SGElement& SGElement::setOpen(bool val)
{
	if (isOpen()!=val) p_state^=SGE_Opened;
	p_state|=SGE_needUpdate;
	return *this;
}

SGElement& SGElement::setState(unsigned int val)
{
	p_state=val &0xF;
	p_state|=SGE_needUpdate;
	return *this;
}

SGElement& SGElement::setMode(unsigned int val)
{
	val&=0xF000;
	p_state=(p_state & (~(0xF000|SGE_isBuild))) | val;
	return *this;
}

SGElement& SGElement::setVisible(bool val)
{
	Transform *tr=getContainer();
	if (tr) tr->setVisible(val);
	/*p_back=_initBackInput(p_back,&p_size,-p_size.y*0.01f);
	p_text=_initText(p_text,0,0);
	float k=p_size.x;
	if (p_size.x>p_size.y) k=p_size.y;
	vector3f ks(k);
	p_key=_initKeyInput(p_key,&ks,this,0);
	p_key->setPosition(k-p_size.x,0,0);*/
	if (p_back) p_back->setVisible(val);
	if (p_text) p_text->setVisible(val);
	if (p_key) p_key->setVisible(val);
	return *this;
}

SGElement& SGElement::setReceiver(char*)
{
	return *this;
}

SGElement& SGElement::setReceiver(BaseObject* obj)
{
	p_reciver=obj;
	return *this;
}

void SGElement::start()
{
}

void SGElement::update()
{
	if (p_text) {
		Text3D *text= p_text->getComponent<Text3D>();
		if (text->changes()!=(int)p_changes) setSize(p_size);
	}
	if ((p_state & SGE_isBuild)==0) _init();

	unsigned int change=p_state&(~(SGE_isBack | SGE_isKey));
	if (p_state!=Disable) {
		if ((p_state & (SGE_isBack|SGE_isKey))!=0) {
			p_state=(p_state & (~0xF)) | Active;
		} else {
			p_state=(p_state & (~0xF)) | Normal;
		}
		if (Input::input().getButton(Input::MOUSELEFT)) {
			p_state|=SGE_KeyLock;
		} else {
			if ((p_state & SGE_KeyLock)!=0) {
				if ((p_state &0xF)==Active) {
					p_state=(p_state & (~0xF)) | Click;
					if ((p_state & 0xF000)==SGE_SetSelect) p_state|=SGE_Set;
					if ((p_state & 0xF000)==SGE_SetSwitch) p_state^=SGE_Set;
					if ((p_state & 0xF000)==SGE_SetOpen) p_state|=SGE_Set;
				}
				if (((p_state & 0xF000)==SGE_SetOpen) && ((p_state & SGE_isKey)!=0)) p_state^=SGE_Opened;
				p_state&=~SGE_KeyLock;
			}
		}
		if (Input::input().isCursorUpdata()) {
			p_state&=~(SGE_isBack | SGE_isKey);
		}
		p_state&=~SGE_needUpdate;
	}

	if (change==(p_state&(~(SGE_isBack | SGE_isKey)))) return;

	if (p_style) {
		SGStyle *style=SGStyle::useStyle(p_style,p_useStyle);
		if (style) {
			if (p_key) {
				if (!isOpen()) {
					_setMaterial(p_key,style->getMaterialKey(0));
				} else _setMaterial(p_key,style->getMaterialKey(1));
			}
			if ((p_state & SGE_Set)==0) {
				if ((p_state & 0xF000)!=SGE_SetOpen) if (p_key) _setMaterial(p_key,style->getMaterialKey(0));
				if ((p_state &0xF)==Normal) _setMaterial(p_back,style->getMaterialBack(0));
				if ((p_state &0xF)==Active) _setMaterial(p_back,style->getMaterialBack(1));
				if ((((p_state &0xF)==Active) && ((p_state &SGE_KeyLock)!=0)) || ((p_state &0xF)==Click)) _setMaterial(p_back,style->getMaterialBack(2));
				if ((p_state &0xF)==Disable) _setMaterial(p_back,style->getMaterialBack(3));
			} else {
				if ((p_state & 0xF000)!=SGE_SetOpen) if (p_key) _setMaterial(p_key,style->getMaterialKey(1));
				if ((p_state &0xF)==Normal) _setMaterial(p_back,style->getMaterialBack(4));
				if ((p_state &0xF)==Active) _setMaterial(p_back,style->getMaterialBack(5));
				if ((((p_state &0xF)==Active) && ((p_state &SGE_KeyLock)!=0)) || ((p_state &0xF)==Click)) _setMaterial(p_back,style->getMaterialBack(6));
				if ((p_state &0xF)==Disable) _setMaterial(p_back,style->getMaterialBack(7));
			}
			if (p_text) {
				if ((p_state &0xF)==Normal) _setMaterial(p_text,style->getMaterialText(0));
				if ((p_state &0xF)==Active) _setMaterial(p_text,style->getMaterialText(1));
				if ((((p_state &0xF)==Active) && ((p_state &SGE_KeyLock)!=0)) || ((p_state &0xF)==Click)) _setMaterial(p_text,style->getMaterialText(2));
				if ((p_state &0xF)==Disable) _setMaterial(p_text,style->getMaterialText(3));
			}
		}
	}

	if (p_reciver) p_reciver->set(BaseObject::SELECT,this);
	if ((p_state &0xF)==Click) click();
}

void* SGElement::_select(BaseObject *item)
{
	if (item==p_back) p_state |= SGE_isBack;
	if (item==p_key) p_state |= SGE_isKey;
	return 0;
}

void * SGElement::set(unsigned _int32 id,void * param)
{
	if (id==BaseObject::TYPE) return SGElement::t();
	if (id==BaseObject::SELECT) return _select((BaseObject *)param); // ???
	if (id==BaseObject::WRITE) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		if ((p=list.find(STR_TEXT))!=0) setText(p->getString());
		if ((p=list.find("style"))!=0) setStyle(p->getString());
		if ((p=list.find("size"))!=0) setSize(p->getVector3f());
		if ((p=list.find("receiver"))!=0) setReceiver(p->getString());
		return 0;
	}
	if (id==BaseObject::READ) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		p=&list[STR_TEXT];
		p->setString(getText());
		p=&list["style"];
		if (p_style) { p->setString(p_style->getPath()); } else {p->setString("");}
		p=&list["size"];
		p->setVector3f(&p_size);
		return param;
	}
	return 0;
}

void SGElement::_init()
{
	p_back=_initBackInput(p_back,&p_size,-p_size.y*0.01f);
	//p_text=_initText(p_text,0,0);
	if (getMode()==SGE_SetOpen) {
		float k=p_size.x;
		if (p_size.x>p_size.y) k=p_size.y;
		vector3f ks(k);
		p_key=_initKeyInput(p_key,&ks,this,0);
		p_key->setPosition(k-p_size.x,0,0);
	}
	p_state|=SGE_isBuild;
}

void SGElement::_initImage()
{
	if (!p_image) {
		Transform *tr=getContainer();
		p_image=tr->createTransform();
	}
}

TYPEINFO(SGElement)

void *SGListElement::set(unsigned _int32 id,void * param)
{
	if (id==csad::BaseObject::TYPE) return SGListElement::t();
	return SGElement::set(id,param);
}

csad::SGListElement *SGListElement::anyElement(csad::SceneComponent *base)
{
	if (!base) return 0;
	csad::Transform *root=base->getContainer();
	if (!root) return 0;
	csad::TransformList::iterator it=root->children().begin();
	csad::TransformList::iterator end=root->children().end();
	csad::SGListElement *button=0;
	while ( !button && it!=end ) 
	{
		csad::Transform *tr=it.value();
		it++;
		button=tr->getComponent<csad::SGListElement>();
	}
	return button;
}

TYPEINFO(SGListElement);

}

OPTIMIZE_OFF;
