/*
 * sglineedit.cpp
 *
 *  Created on: 05.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/gui/sglineedit.h>
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
#include "csad/core/base/stringconsts.h"

OPTIMIZE_ON;

namespace csad {

SGLineEdit::SGLineEdit()
{
	p_back=0;
	p_text=0;
	p_cursor=0;
	p_state=0;
	p_style=0;
	p_state=Active; // need for afto reset to Normal
	p_size=vector3f(1,1,0);
	p_reciver=0;
	p_useStyle=SGLineEditStyle::t();
	p_changes=0;
	feditpos=0;
}

SGLineEdit::~SGLineEdit()
{
}

void SGLineEdit::setText(char *text)
{
	if (!text && p_text) {
		delete p_text;
		p_text=0;
	} else if (text) {
		p_text=_initText(p_text,text,p_style);
	}
}

const char *SGLineEdit::getText()
{
	if (!p_text) return 0;
	Text3D *mtext = _initText(&p_text);
	if (!mtext) return 0;
	return mtext->text();
}

void SGLineEdit::setStyle(char *name)
{
	setStyle(Graph::graph().getStyle(name));
}

void SGLineEdit::setStyle(Style *style)
{
	p_style=style;
	if (p_text) p_text=_initText(p_text,0,p_style);
}

bool SGLineEdit::setUseStyle(void *type)
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

bool SGLineEdit::setUseStyle(char *styleType)
{
	ObjectInfo *info=ContainerComponents::getInfo(styleType);
	if (!info) return false;
	if ((info->type==SGButtonStyle::t())
			|| (info->type==SGElementStyle::t())
			|| (info->type==SGStyle::t())) {
		p_useStyle=info->type;
		return true;
	}
	return false;
}

void SGLineEdit::setSize(vector3f &size)
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
}

void SGLineEdit::setSet(bool val)
{
	if (val) p_state|=SGE_isBack;
	if (!val) p_state=p_state & (~SGE_isBack);
	p_state|=SGE_needUpdate;
}

void SGLineEdit::setState(unsigned int val)
{
	p_state=val &0xF;
	p_state|=SGE_needUpdate;
}

void SGLineEdit::setVisible(bool val)
{
	Transform *tr=getContainer();
	if (tr) tr->setVisible(val);
	if (p_back) p_back->setVisible(val);
	if (p_text) p_text->setVisible(val);
}

void SGLineEdit::setReceiver(char*)
{

}

void SGLineEdit::setReceiver(BaseObject* obj)
{
	p_reciver=obj;
}

void SGLineEdit::start()
{
}

void SGLineEdit::update()
{
	if (p_text) {
		Text3D *text= p_text->getComponent<Text3D>();
		if (text->changes()!=p_changes) setSize(p_size);
	}
	
	if ((p_state & SGE_Set)!=0) {
		bool edited=false;
		char key=Input::input().readKey();
		if (key>31) {
			_textwrite(key);
			feditpos++;
			edited=true;
		}
		if (Input::input().isKeyboardUpdata()) {
			if (Input::input().getButton(Keyboard::KEY_BAKCSPACE) && (feditpos>0)) {
				feditpos--;
				_textremove();
				edited=true;
			}
			if (Input::input().getButton(Keyboard::KEY_DEL)) {
				_textremove();
				edited=true;
			}
			if (Input::input().getButton(Keyboard::KEY_LEFT)) {
				if (feditpos>0) feditpos--;
				if ((p_state & SGE_End)!=0) p_state^=SGE_End;
			}
			if (Input::input().getButton(Keyboard::KEY_RIGHT)) {
				String istr(getText());
				if (feditpos<istr.length()) feditpos++;
				if ((p_state & SGE_End)!=0) p_state^=SGE_End;
			}
		}
		if (edited) if ((p_state & SGE_End)!=0) p_state^=SGE_End;
		if (Input::input().isKeyboardUpdata()) {
			if (Input::input().getButton(Keyboard::KEY_ENTER)) {
				p_state|=SGE_End;
				edited=true;
			}
		}
		if (edited) if (p_reciver) p_reciver->set(BaseObject::SELECT,this);
	}

	if ((p_state & SGE_isBuild)==0) _init();

	unsigned int change=p_state&(~SGE_isBack);
	if (p_state!=Disable) {
		if ((p_state & SGE_isBack)!=0) {
			p_state=(p_state & (~0xF)) | Active;
		} else {
			p_state=(p_state & (~0xF)) | Normal;
		}
		if (Input::input().getButton(Input::MOUSELEFT)) {
			if ((p_state &0xF)==Active) {
				p_state=(p_state & (~0xF)) | Click | SGE_Set;
			} else {
				p_state&=~(SGE_Set | SGE_End);
			}
		}
		if (Input::input().isCursorUpdata()) p_state&=~SGE_isBack;
		p_state&=~SGE_needUpdate;
	}

	if (change==(p_state&(~SGE_isBack))) return;

	if (p_style) {
		SGStyle *style=SGStyle::useStyle(p_style,p_useStyle);
		if (style) {
			if ((p_state & SGE_Set)==0) {
				if ((p_state &0xF)==Normal) _setMaterial(p_back,style->getMaterialBack(0));
				if ((p_state &0xF)==Active) _setMaterial(p_back,style->getMaterialBack(1));
				if ((p_state &0xF)==Click) _setMaterial(p_back,style->getMaterialBack(2));
				if ((p_state &0xF)==Disable) _setMaterial(p_back,style->getMaterialBack(3));
			} else {
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

void* SGLineEdit::_select(BaseObject *item)
{
	if (item==p_back) p_state |= SGE_isBack;
	return 0;
}

void * SGLineEdit::set(unsigned _int32 id,void * param)
{
	if (id==BaseObject::TYPE) return SGLineEdit::t();
	if (id==BaseObject::SELECT) return _select((BaseObject*)param); // ???
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
		p=&list["style"];
		if (p_style) { p->setString(p_style->getPath()); } else {p->setString("");}
		p=&list["size"];
		p->setVector3f(&p_size);
		return param;
	}
	return 0;
}

void SGLineEdit::_init()
{
	p_back=_initBackInput(p_back,&p_size,-p_size.y*0.01f);
	//p_text=_initText(p_text,0,0);
	//p_isBuild=true;
	p_state|=SGE_isBuild;
}

void SGLineEdit::_textreset()
{
	setText("");
	feditpos=0;
}

void SGLineEdit::_textwrite(char key)
{
	String istr(getText());
	if ((p_state & SGE_End)!=0) {
		istr="";
		feditpos=0;
	}
	istr.insert(feditpos,key);
	setText(istr.str());
}

void SGLineEdit::_textremove()
{
	String istr(getText());
	if ((p_state & SGE_End)!=0) {
		istr="";
		feditpos=0;
	}
	if (istr.length()>feditpos) istr.remove(feditpos,1);
	setText(istr.str());
}

TYPEINFO(SGLineEdit)

}

OPTIMIZE_OFF;
