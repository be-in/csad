/*
 * font.cpp
 *
 *  Created on: 28.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>

#include <platform.h>
#include <core/graph.h>
#include <gen3.h>

OPTIMIZE_ON;

namespace csad {

using namespace bt;

void *Font::set(unsigned _int32 id,void *param)
{
	if (id==BaseObject::TYPE) return Font::t();
	if (id==BaseObject::WRITE) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		if ((p=list.find("font"))!=0) setName(p->getString());
		if ((p=list.find("size"))!=0) setSize(p->getInt(8));
		if ((p=list.find("bold"))!=0) setBold(p->getBool(false));
		if ((p=list.find("italic"))!=0) setItalic(p->getBool(false));
	}
	if (id==BaseObject::READ) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		p=&list["font"];
		p->setString(p_name.str());
		p=&list["size"];
		p->setInt(p_size);
		p=&list["bold"];
		p->setBool(getBold());
		p=&list["italic"];
		p->setBool(getItalic());
	}
	return 0;
}

Font *Font::finder(char *path)
{
	ObjectManager::Finder find(path);
	FontServer *fontserver=Graph::graph().getFontServer(find.getNext());
	if (!fontserver) {
#ifdef LOG_CSAD
		Log::console("Can`t find font server: %s",find.getNext());
#endif
		return 0;
	}
	find.next();
	Font *font=fontserver->getFont(find.getNext());
	if (!font) {
#ifdef LOG_CSAD
		Log::console("Can`t find font: %s",find.getNext());
#endif
		return 0;
	}
	find.next();
	return font;
}

TYPEINFO(Font)

}

OPTIMIZE_OFF;
