/*
 * config.h
 *
 *  Created on: 23.08.2013
 *      Author: Пантелеймонов Александр
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <core/baseobject.h>
#include <core/classmanager.h>

namespace csad {

using namespace bt;

class FormatXML;
class NodeXML;

/**
 * @class Config
 *
 * @ingroup core
 * @brief Config - набор статических методов для формирования архитектуры приложения.
 *
 * @see core
 */

class Config {
public:
	Config();

	/// инициализация
	static void init();

	/// формирование обьектов по конфигурации описанной в xml.
	static void createFromXml(FormatXML *xml);
	//static void * createObject(void *parent,ObjectParameters *); //??
	//static void * setObjectParameter(void *object,void *value); //??

	//static void regClassXMLCreator(const char * name,void *info, tfSTDCALL_p_PROC_p_p fun); //???

private:

	//static void _createObject(char *className,void parent,char *name);
	//static void _createFromXmlNode(void *,NodeXML *);
};

}

#endif /* CONFIG_H_ */
