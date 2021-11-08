/*
 * sgbutton.cpp
 *
 *  Created on: 11.09.2013
 *      Author: Пантелеймонов Александр
 */

/*#include <scene/gui/sgbutton.h>
#include <scene/gui/sgstyles.h>
#include <scene/gui/sgbuttongroup.h>
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
#include <components/resender.h>
#include <platform.h>

namespace csad {

SGButton::SGButton()
{
	p_back=0;
	p_image=0;
	p_key=0;
	p_text=0;
	p_state=0;
	p_style=0;
	p_state=Active; // need for afto reset to Normal
	p_size=vector3f(1,1,0);
	p_reciver=0;
	p_useStyle=SGButtonStyle::t();
	p_changes=0;
}

void SGButton::setText(char *text)
{
	if (!text && p_text) {
		delete p_text;
	} else {
		p_text=_initText(p_text,text,p_style);
	}
}

const char *SGButton::getText()
{
	if (!p_text) return 0;
	Text3D *mtext = _initText(&p_text);
	if (!mtext) return 0;
	return mtext->text();
}

void SGButton::setStyle(char *name)
{
	setStyle(Graph::graph().getStyle(name));
}

void SGButton::setStyle(Style *style)
{
	p_style=style;
	if (p_text) p_text=_initText(p_text,0,p_style);
}

bool SGButton::setUseStyle(char *styleType)
{
	ObjectInfo *info=ConteinerComponents::getInfo(styleType);
	if (!info) return false;
	if ((info->type==SGButtonStyle::t())
			|| (info->type==SGElementStyle::t())
			|| (info->type==SGStyle::t())) {
		p_useStyle=info->type;
		return true;
	}
	return false;
}

void SGButton::setSize(vector3f &size)
{
	p_size=size;
	p_back=_initBackInput(p_back,&p_size,-p_size.y*0.01);
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
}

void SGButton::setSet(bool val)
{
	if (val) p_state|=Set;
	if (!val) p_state=p_state & (~Set);
	p_state|=needUpdate;
}

void SGButton::setState(unsigned int val)
{
	p_state=val &0xF;
	p_state|=needUpdate;
}

void SGButton::setVisible(bool val)
{
	Transform *tr=getContainer();
	if (tr) tr->setVisible(val);
	if (p_back) p_back->setVisible(val);
	if (p_text) p_text->setVisible(val);
}

void SGButton::setReceiver(char*path)
{

}

void SGButton::setReceiver(BaseObject* obj)
{
	p_reciver=obj;
}

void SGButton::start()
{
}

void SGButton::update()
{
	if (p_text) {
		Text3D *text= p_text->getComponent<Text3D>();
		if (text->changes()!=p_changes) setSize(p_size);
	}
	if ((p_state & isBild)==0) _init();

	unsigned int change=p_state&(~isSelect);
	if (p_state!=Disable) {
		if ((p_state & isSelect)!=0) {
			p_state=(p_state & (~0xF)) | Active;
		} else {
			p_state=(p_state & (~0xF)) | Normal;
		}
		if (((p_state &0xF)==Active) && (Input::input().getButton(Input::MOUSELEFT))) {
			p_state=(p_state & (~0xF)) | Click;
			if ((p_state & 0xF000)==SetSelect) p_state|=Set;
			if ((p_state & 0xF000)==SetSwitch) p_state^=Set;
		}
		if (Input::input().isCursorUpdata()) p_state&=~isSelect;
		p_state&=~needUpdate;
	}

	if (change==(p_state&(~isSelect))) return;

	if (p_style) {
		SGStyle *style=0;
		if (p_useStyle==SGStyle::t()) style=p_style->getComponent<SGStyle>();
		if (p_useStyle==SGButtonStyle::t()) style=(SGStyle *)p_style->getComponent<SGButtonStyle>();
		if (p_useStyle==SGElementStyle::t()) style=(SGStyle *)p_style->getComponent<SGElementStyle>();
		if (style) {
			if ((p_state & Set)==0) {
				if (p_key) _setMaterial(p_key,style->getMaterialKey(0));
				if ((p_state &0xF)==Normal) _setMaterial(p_back,style->getMaterialBack(0));
				if ((p_state &0xF)==Active) _setMaterial(p_back,style->getMaterialBack(1));
				if ((p_state &0xF)==Click) _setMaterial(p_back,style->getMaterialBack(2));
				if ((p_state &0xF)==Disable) _setMaterial(p_back,style->getMaterialBack(3));
			} else {
				if (p_key) _setMaterial(p_key,style->getMaterialKey(1));
				if ((p_state &0xF)==Normal) _setMaterial(p_back,style->getMaterialBack(4));
				if ((p_state &0xF)==Active) _setMaterial(p_back,style->getMaterialBack(5));
				if ((p_state &0xF)==Click) _setMaterial(p_back,style->getMaterialBack(6));
				if ((p_state &0xF)==Disable) _setMaterial(p_back,style->getMaterialBack(7));
			}
			if (p_text) {
				if ((p_state &0xF)==Normal) _setMaterial(p_text,style->getMaterialText(0));
				if ((p_state &0xF)==Active) _setMaterial(p_text,style->getMaterialText(1));
				if ((p_state &0xF)==Click) _setMaterial(p_text,style->getMaterialText(2));
				if ((p_state &0xF)==Disable) _setMaterial(p_text,style->getMaterialText(3));
			}
		}
	}

	if (p_reciver) p_reciver->set(BaseObject::SELECT,this);
	if ((p_state &0xF)==Click) click();
}

void* SGButton::_select(BaseObject *item)
{
	if (item==p_back) p_state |= isSelect;
	return 0;
}

void * SGButton::set(unsigned int id,void * param)
{
	if (id==BaseObject::TYPE) return SGButton::t();
	if (id==BaseObject::SELECT) return _select((BaseObject*)param); // ???
	if (id==BaseObject::WRITE) {
		ParametersList *list=(ParametersList *)param;
		if (list->contains("text")) setText((*list)["text"].getString());
		if (list->contains("style")) setStyle((*list)["style"].getString());
		if (list->contains("size")) setSize((*list)["size"].getVector3f());
		if (list->contains("receiver")) setReceiver((*list)["receiver"].getString());
		return 0;
	}
	if (id==BaseObject::READ) {
		Variant *p;
		ParametersList *list=(ParametersList *)param;
		p=&(*list)["style"];
		if (p_style) { p->setString(p_style->getPath()); } else {p->setString("");}
		p=&(*list)["size"];
		p->setVector3f(&p_size);
		return param;
	}
	return 0;
}

void SGButton::_init()
{
	p_back=_initBackInput(p_back,&p_size,-p_size.y*0.01);
	//p_text=_initText(p_text,0,0);
	//p_isBuild=true;
	p_state|=isBild;
}

void SGButton::_initImage()
{
	if (!p_image) {
		Transform *tr=getContainer();
		p_image=tr->createTransform();
	}
}

TYPEINFO(SGButton)

}
*/