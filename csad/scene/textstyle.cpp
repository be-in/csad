/*
 * textstyle.cpp
 *
 *  Created on: 03.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/textstyle.h>
#include <scene/style.h>
#include <scene/material.h>
#include <platform.h>
#include <core/graph.h>
#include "csad/core/base/stringconsts.h"

OPTIMIZE_ON;

namespace csad {

TextStyle::TextStyle()
{
	p_anchor=Bottom;
	p_charSize=1;
	p_kerning=1;
	p_font=0;
	p_material=0;
}

TextStyle& TextStyle::setFont(char *fontPath)
{
	setFont(Font::finder(fontPath));
	return *this;
}

TextStyle& TextStyle::setFont(Font *font)
{
	p_font=font;
	return *this;
}

TextStyle& TextStyle::setCharSize(float val)
{
	p_charSize=val;
	return *this;
}

TextStyle& TextStyle::setKerning(float val)
{
	p_kerning=val;
	return *this;
}

TextStyle& TextStyle::setAnchor(int val)
{
	p_anchor=val;
	return *this;
}

ConstMapVoid<char*,int,9> _anchorval;
char *_anchorname[9]={(char *)"\003top",(char *)"\006center",(char *)"\006bottom",(char *)"\010left top",(char *)"\013left center",(char *)"\013left bottom",(char *)"\011right top",(char *)"\014right center",(char *)"\014right bottom"};
void *_anchorvalue[9]={(void*)TextStyle::Top,(void*)TextStyle::Center,(void*)TextStyle::Bottom,(void*)TextStyle::Left_Top,(void*)TextStyle::Left_Center,(void*)TextStyle::Left_Bottom,(void*)TextStyle::Right_Top,(void*)TextStyle::Right_Center,(void*)TextStyle::Right_Bottom};

TextStyle& TextStyle::setAnchor(char *val)
{
	if (_anchorval.count()==0) {
		int i=0;
		while (i<9) {
			arrFunctions.MCSPAdd(&_anchorval,(void*)_anchorname[i],_anchorvalue[i],9);
			i++;
		}
	}
	bt::ShortString km(val);
	int *res=(int*)arrFunctions.MCSPFind(&_anchorval,km.data());
	if (res) p_anchor=*res;
	return *this;
}

TextStyle& TextStyle::setMaterial(char *name)
{
	p_material=Graph::graph().getMaterial(name);
	return *this;
}

TextStyle& TextStyle::setMaterial(Material *mat)
{
	p_material=mat;
	return *this;
}

void * TextStyle::set(unsigned _int32 id,void * param)
{
	if (id==BaseObject::TYPE) return TextStyle::t();
	if (id==BaseObject::WRITE) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		if ((p=list.find("font"))!=0) setFont(p->getString());
		if ((p=list.find("charsize"))!=0) setCharSize(p->getFloat(1));
		if ((p=list.find("kerning"))!=0) setKerning(p->getFloat(1));
		if ((p=list.find("anchor"))!=0) setAnchor(p->getString());
		if ((p=list.find(STR_MATERIAL))!=0) setMaterial(p->getString());
	}
	if (id==BaseObject::READ) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		//p->setDouble(p_fov);
		p=&list["charsize"];
		p->setFloat(p_charSize);
		p=&list["kerning"];
		p->setDouble(p_kerning);
		//p=&list["anchor"];
		//p->setDouble(p_min);
		p=&list[STR_MATERIAL];
		if (p_material) {
			p->setString(p_material->getName());
		}
	}
	return 0;
}

const char *TextStyle::getPath()
{
	ContainerComponents *mstyle=getContainer();
	if (!mstyle) return "";
	return mstyle->getPath();
}

TYPEINFO(TextStyle)

}

OPTIMIZE_OFF;
