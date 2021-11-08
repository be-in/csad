/*
 * sgscroll.cpp
 *
 *  Created on: 11.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/gui/sgscroll.h>
#include <scene/gui/sgstyles.h>
#include <scene/gui/sgbutton.h>
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

OPTIMIZE_ON;

namespace csad {

SGScroll::SGScroll():
	p_size(1,1,1),
	fpos(0),
	fmaxpos(0),
	fpagesize(1),
	p_back(0),
	p_scroll(0),
	p_subkey(0),
	p_addkey(0),
	p_style(0),
	p_reciver(0)
{
	p_state=Active; // need for afto reset to Normal
	p_useStyle=SGButtonStyle::t();
}

SGScroll::~SGScroll()
{
}

void SGScroll::setStyle(char *name)
{
	setStyle(Graph::graph().getStyle(name));
}

void SGScroll::setStyle(Style *style)
{
	p_style=style;
}

SGScroll &SGScroll::setSize(vector3f &size)
{
	p_size=size;
	return *this;
}

SGScroll &SGScroll::setCount(int val)
{
	fmaxpos=val;
	unsigned int realmax=fmaxpos-fpagesize+1;
	if (fpos>=realmax) 
		if (realmax>0) {
			fpos=realmax-1;
		} else fpos=0;
	return *this;
}

SGScroll &SGScroll::setPageSize(int val)
{
	fpagesize=val;
	unsigned int realmax=fmaxpos-fpagesize+1;
	if (fpos>=realmax) 
		if (realmax>0) {
			fpos=realmax-1;
		} else fpos=0;
	return *this;
}

SGScroll &SGScroll::setVal(int val)
{
	int realmax=fmaxpos-fpagesize+1;
	if (val>=realmax) return *this;
	fpos=val;
	return *this;
}

SGScroll &SGScroll::setSubKey(SGButton* val)
{
	p_subkey=val;
	p_subkey->setReceiver(this);
	return *this;
}

SGScroll &SGScroll::setAddKey(SGButton* val)
{
	p_addkey=val;
	p_addkey->setReceiver(this);
	return *this;
}

void SGScroll::setReceiver(char*)
{

}

void SGScroll::setReceiver(BaseObject* obj)
{
	p_reciver=obj;
}

void SGScroll::start()
{
	_calc();
}

void SGScroll::update()
{
	//if ((p_state & isBuild)==0) _init();

	unsigned int change=p_state&(~(SGE_isBack | SGE_isKey));

	if (p_state!=Disable) {
		if ((p_state & (SGE_isBack | SGE_isKey))!=0) {
			p_state=(p_state & (~0xF)) | Active;
		} else {
			p_state=(p_state & (~0xF)) | Normal;
		}
		if (Input::input().getButton(Input::MOUSELEFT)) {
			if ((p_state & SGE_KeyLock)==0) {
				if ((p_state & SGE_isKey)!=0) {
					flastpos=Input::input().getCursorPos();
					p_state|=SGE_Set;
					p_state=(p_state & (~0xF)) | Click;
				} else if ((p_state & SGE_isBack)!=0) {
					p_state|=SGE_Opened;
				}
			}
			p_state|=SGE_KeyLock;
		} else {
			if ((p_state & SGE_KeyLock)!=0) {
				p_state&=~SGE_KeyLock;
				p_state&=~SGE_Set;
			}
		}
		//if (p_state=SGE_Set) p_state|=Click;
		if (Input::input().isCursorUpdata()) {
			p_state&=~(SGE_isBack | SGE_isKey);
		}
	}

	if (change==(p_state&(~(SGE_isBack | SGE_isKey)))) return;

	if (p_style) {
		SGStyle *style=SGStyle::useStyle(p_style,p_useStyle);
		if (style) {
			if ((p_state &0xF)==Normal) {
				_setMaterial(p_back,style->getMaterialKey(0));
				_setMaterial(p_scroll,style->getMaterialBack(0));
			}
			if ((p_state &0xF)==Active) {
				_setMaterial(p_back,style->getMaterialKey(0));
				_setMaterial(p_scroll,style->getMaterialBack(1));
			}
			if ((p_state &0xF)==Click) {
				_setMaterial(p_back,style->getMaterialKey(0));
				_setMaterial(p_scroll,style->getMaterialBack(2));
			}
			if ((p_state &0xF)==Disable) {
				_setMaterial(p_back,style->getMaterialKey(0));
				_setMaterial(p_scroll,style->getMaterialBack(3));
			}
		}
	}
	
	_calc();
}

void SGScroll::prepare()
{
/*	if ((p_state&SGE_Opened)!=0) {
		p_state&=~SGE_Opened;
	}*/

	if ((p_state&SGE_Set)==0) return;

	vector2f curpos=Input::input().getCursorPos();
	GlContext *context=GlContext::getCurrent();
	if (!context) return;
	Transform *tr=getContainer();
	bt::vector3d*pos=tr->realPosition();
	Display *display=context->getDisplay();

	vector4i vp=Camera::camera()->getViewPort(context);
	bt::matrix4f &matr=*Camera::camera()->projMatrix();
	float d=(float)(pos->z*matr.m[11]+matr.m[15]);

	vector3f curposd;
	display->toLocal((vector2f*)&curpos,(vector2f*)&curposd);
	vector3f lastposd;
	display->toLocal((vector2f*)&flastpos,(vector2f*)&lastposd);
	float lscale=2*d/(vp.w*matr.m[5]);
	vector3f dist;
	dist.x=(curposd.x-vp.z*0.5f-vp.x)*lscale;
	dist.y=(vp.y+vp.w*0.5f-curposd.y)*lscale;
	dist.z=-1;
	lastposd.x=(lastposd.x-vp.z*0.5f-vp.x)*lscale;
	lastposd.y=(vp.y+vp.w*0.5f-lastposd.y)*lscale;
	lastposd.z=-1;

	dist=dist-lastposd;

	vector3f &sback=p_back->getScale();
	vector3f &sscroll=p_scroll->getScale();
	float invmax1=1.0f;
	unsigned int realmax=fmaxpos+1-fpagesize;
	if (realmax>1) invmax1=(realmax-1)*0.5f/(sback.y-sscroll.y);

	dist.y=-dist.y*invmax1;
	int ch=matFunctions.FTrunc(dist.y);
	if (ch==0) return;
	dist.y=ch/dist.y;
	flastpos=flastpos+(curpos-flastpos)*(dist.y);
	if ((int)fpos>=-ch) fpos+=ch;

	if (fpos>=realmax) {
		if (realmax>0) {
			fpos=realmax-1;
		} else fpos=0;
	}
	_calc();
}

void * SGScroll::set(unsigned _int32 id,void * param)
{
	if (id==BaseObject::TYPE) return SGScroll::t();
	if (id==BaseObject::SELECT) return _select((BaseObject*)param);
	if (id==BaseObject::WRITE) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		if ((p=list.find("style"))!=0) setStyle(p->getString());
		if ((p=list.find("size"))!=0) setSize(p->getVector3f());
		if ((p=list.find("count"))!=0) setCount(p->getInt());
		if ((p=list.find("page"))!=0) setPageSize(p->getInt());
		if ((p=list.find("val"))!=0) setVal(p->getInt());
		if ((p=list.find("receiver"))!=0) setReceiver(p->getString());
		return 0;
	}
	if (id==BaseObject::READ) {
		ParametersList &list=*(ParametersList *)param;
		Variant &p=list["style"];
		if (p_style) { p.setString(p_style->getPath()); } else { p.setString(""); }
		p=list["size"];
		p.setVector3f(&p_size);
		p=list["max"];
		p.setInt(fmaxpos);
		p=list["page"];
		p.setInt(fpagesize);
		p=list["val"];
		p.setInt(fpos);
		return param;
	}
	return 0;
}

void* SGScroll::_select(BaseObject *item)
{
	SGButton *but=(SGButton *)item;
	if ((item==p_subkey) && (but->isClick())) {
		if (fpos>0) fpos--;
		if (fpos<0) fpos=0;
	}
	if ((item==p_addkey) && (but->isClick())) {
		unsigned int realmax=fmaxpos-fpagesize+1;
		if (fpos<realmax-1) fpos++;
		if (fpos>=realmax) fpos=realmax-1;
	}
	if (item==p_back) p_state |= SGE_isBack;
	if (item==p_scroll) p_state |= SGE_isKey;
	return 0;
}

void SGScroll::_calc()
{
	if (!p_back) p_back=_initBackInput(p_back,0,-p_size.y*0.01f);
	vector3f &sback=p_back->getScale();
	sback.z=0;
	sback.x=p_size.x;
	sback.y=p_size.y;
	if (!p_scroll) p_scroll=_initBackInput(p_scroll,0,0);
	vector3f &sscroll=p_scroll->getScale();
	sscroll.z=0;
	float invmax=1.0f;
	float invmax1=1.0f;
	unsigned int realmax=fmaxpos-fpagesize+1;
	if (fmaxpos>0) invmax=1.0f/fmaxpos;
	if (realmax>1) invmax1=1.0f/(realmax-1);
	if (fpos>=realmax) {
		if (realmax>0) {
			fpos=realmax-1;
		} else fpos=0;
	}
	if (fpos<0) fpos=0;
	vector3d &pos=p_scroll->getPosition();
	if ((p_state & SGE_Horisontal)==0) {
		sscroll.x=p_size.z;
		sscroll.y=fpagesize*p_size.y*invmax;
		float s=sback.y-sscroll.y;
		pos.x=0;
		pos.y=s-s*2*fpos*invmax1;
		pos.z=0;
	} else {
		sscroll.x=fpagesize*p_size.x*invmax;
		sscroll.y=p_size.z;
		float s=sback.x-sscroll.x;
		pos.x=s-s*2*fpos*invmax1;
		pos.y=0;
		pos.z=0;
	}
}

TYPEINFO(SGScroll)

};

OPTIMIZE_OFF;
