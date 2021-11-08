/*
 * xml.h
 *
 *  Created on: 19.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef XMLFORMAT_H_
#define XMLFORMAT_H_

#include <bt.h>
#include <platform.h>
#include <core/baseobject.h>
#include <core/csadapi.h>

namespace csad {

using namespace bt;

class File;
class NodeXML;

typedef VoidVector<NodeXML> NodeXMLList;

/**
 * @class NodeXML
 *
 * @ingroup format
 * @brief NodeXML - элемент данных xml файла.
 *
 * @see FormatXML, format
 */

class NodeXML {
public:
	MEMMANAGER(NodeXML);

	CSAD_API NodeXML(NodeXML *parent=0);
	CSAD_API ~NodeXML();

	/// устанавливает родительский элемент
	CSAD_API void setParent(NodeXML *parent);

	_FORCEINLINE NodeXML * getParent() { return p_parent; }

	/// Sets the tag name
	CSAD_API void setName(char *name);
	/// Sets the tag name
	_FORCEINLINE void setName(const char *name) { setName((char*)name); }

	/// Returns the tag name
	_FORCEINLINE ShortString& getName() { return p_name; }
	/// Returns the tag name
	_FORCEINLINE const char* getCharName() { return p_name.str(); }

	CSAD_API void setString(char *name,char *val);
	CSAD_API void setString(const char *name,const char *val);

	CSAD_API char* getString(char *name,char *def);
	CSAD_API const char* getString(const char *name,const char *def="");
	CSAD_API int getInt(const char *name,int def=0);

	CSAD_API float getFloat(char *name,float def=0);
	CSAD_API float getFloat(const char *name,float def=0);

	_FORCEINLINE const char *text() { return p_text.str(); }
	CSAD_API void setText(char *text);

	/// возвращает зависимый нод
	/// @param name - имя ноды "nodeName[3]"
	CSAD_API NodeXML *getChild(char *name);
	_FORCEINLINE NodeXML *getChild(const char *name) { return getChild((char*)name); }

	/// возвращает список дочерних элементов
	_FORCEINLINE NodeXMLList &getNodeList() { return p_child; }
	/// взвращает список параметров тега
	_FORCEINLINE ParametersList &getParameterList() { return p_parameters; }

private:
	NodeXML *p_parent;
	NodeXMLList p_child;
	ParametersList p_parameters;
	ShortString p_name;
	String p_text;
};

/**
 * @class FormatXML
 *
 * @ingroup format
 * @brief FormatXML - the format of the xml data file.
 *
 * The object containing the XML hierarchy Tagoo, starting from the virtual root element with the name of the file.
 *
 * @see format
 */

class FormatXML {
public:
	MEMDEFAULT(FormatXML)

	CSAD_API FormatXML();
	CSAD_API ~FormatXML();

	/// Loading from a file at the specified path
	CSAD_API bool readFromFile(char *name);
	_FORCEINLINE bool readFromFile(const char *name) { return readFromFile((char *)name); }
	/// Загрузка из файла
	CSAD_API bool readFromFile(File *file);
	/// Write to the file at the specified path
	CSAD_API bool saveToFile(char *name);
	_FORCEINLINE bool saveToFile(const char *name) { return saveToFile((char *)name); }
	/// Запись в файл
	CSAD_API bool saveToFile(File *file);

	/// Creates a node from a specified parent or root node
	CSAD_API NodeXML *newNode(NodeXML*parent);
	/// returns the root element
	_FORCEINLINE NodeXML *getNode() { return p_root; }
	/// returns the node for submission
	/// @param path - the path of hierarchie "first/second[3]/param[2]"
	CSAD_API NodeXML *getNodeByPath(char *path);
	_FORCEINLINE NodeXML *getNodeByPath(const char *name) { return getNodeByPath((char*)name); }

	CSAD_API void clear();

	CSAD_API TYPEINFO_H

private:
	enum TAGINFO {
		OPEN,
		CLOSE,
		SELF_CLOSE
	};

	NodeXML *p_root;
	bool p_end;

	//bool _readFromFile(File *file,XMLNode *parent);
	bool _readFromFile(File *file,NodeXML *parent);
	bool _saveToFile(File *file,NodeXML *parent);
	char* _readTagFromFile(File *file);
	char* _readTagName(char *tag,char **name,TAGINFO *info);
	bool _readParams(char *tag, NodeXML *newnode, TAGINFO *info);
	void _writeParams(String *tag, NodeXML *newnode);

};

}

#endif /* XMLFORMAT_H_ */
