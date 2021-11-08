/*
 * config.h
 *
 *  Created on: 23.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <bt.h>
#include <core/baseobject.h>
#include <core/core.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

void InitClass(Core *core);

using namespace bt;

class FormatXML;
class NodeXML;

struct typeConfigClassInfo {
	BaseObject *obj;
	ParametersList *info;
};

typedef Vector<typeConfigClassInfo> ConfigParameterList;

/**
 * @class Config
 *
 * @ingroup core
 * @brief Config - a set of methods for forming the architecture of the application.
 *
 * @see core
 */

class Config {
public:
	Config(Core *core);
	~Config();

	/// the formation of objects in the configuration described in xml.
	void createFromXml(FormatXML *xml);
	//static void * createObject(void *parent,ObjectParameters *); //??
	//static void * setObjectParameter(void *object,void *value); //??

	//static void regClassXMLCreator(const char * name,void *info, tfSTDCALL_p_PROC_p_p fun); //???
	void createFromXmlNode(void* parent,NodeXML * node);
	void prepareNodes(void* parent,NodeXML * node);

private:
	ConfigParameterList mlistObj;
	Core *mcore;

	//static void _createObject(char *className,void parent,char *name);
	
	void _readModules(NodeXML * node);
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* CONFIG_H_ */
