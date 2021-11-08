/*
 * qnxfontserver.cpp
 *
 *  Created on: 30.08.2013
 *      Author: Александр
 */

#include <platform/platformapi.h>

#if defined (OS_QNX)

#include <platform.h>
#include <core/graph.h>
#include <scene/fonttext.h>

namespace csad {

FontServer::FontServer(char *name)
{
	p_dll=0;
	p_pf=0;
	p_options="";
	Graph::graph().p_fontserver->addObject(this,name);
}

FontServer::FontServer(const char *name)
{
	p_dll=0;
	p_pf=0;
	p_options="";
	Graph::graph().p_fontserver->addObject(this,name);
}

FontServer::~FontServer()
{
	Graph::graph().p_fontserver->detachObject(this);
}

void FontServer::setOptions(char *options)
{
	p_options=options;
}

Font *FontServer::createFont(char *name)
{
	if (name[0]!=0) {
		Font *font=(Font*)p_font.getObject(name);
		if (font) return font;
	}
	Font *font=new Font(this,name);
	return font;
}

FontText *FontServer::createFontText(char *name)
{
	if (name[0]!=0) {
		FontText *font=(FontText*)p_font.getObject(name);
		if (font) return font;
	}
	FontText *font=new FontText(this,name);
	return font;
}

Font *FontServer::getFont(char *name)
{
	return (Font *)p_font.getObject(name);
}

FontText *FontServer::getFont(char *name)
{
	return (FontText *)p_font.getObject(name);
}

void FontServer::init()
{
	//"-A, -d=/usr/photon/font_repository"
#if _NTO_VERSION < 660
	p_dll = (void*)PfAttachLocalDll(p_options.str(),DLL_FONT_SERVER);//DLL_FONT_SERVER p_options.c_str()
	if (!p_dll) {
		Log::console("Can`t init font server, %s",strerror(errno));
	}
	p_pf = (void*)PfAttachDllCx((fontdll_t)p_dll,0);
#else
#endif
}

void FontServer::close()
{
#if _NTO_VERSION < 660
	PfDetachCx((_Pf_ctrl *)p_pf);
	p_pf=0;
	PfDetachLocalDll((fontdll_t)p_dll);
	p_dll=0;
#else
#endif
}

void * FontServer::set(unsigned int id,void * param)
{
	if (id==BaseObject::TYPE) return FontServer::t();
	if (id==BaseObject::WRITE) {
		ParametersList *list=(ParametersList *)param;
		if (list->contains("options")) setOptions((*list)["options"].getString());
	}
	return 0;
}

TYPEINFO(FontServer)

}

#endif
