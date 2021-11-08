/*
 * xmlformat.cpp
 *
 *  Created on: 19.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <format.h>
#include <platform.h>
#include <bt.h>

OPTIMIZE_ON;

namespace csad {

using namespace bt;

NodeXML::NodeXML(NodeXML *parent)
{
	p_parent=parent;
	if (p_parent != 0) p_parent->p_child.assign(this);
}

NodeXML::~NodeXML()
{
	NodeXML**it=(NodeXML**)p_child.data();
	NodeXML**end=(NodeXML**)p_child.endData();
	while (it!=end) {
		(*it)->p_parent=0;
		delete *it;
		it++;
	}
	if (p_parent) {
		int it = p_parent->p_child.del(this);
	}
	p_child.clear();
	p_parameters.clear();
}

void NodeXML::setParent(NodeXML *parent)
{
	if (p_parent!=0) {
		int it = p_parent->p_child.del(this);
	}
	p_parent=parent;
	if (p_parent != 0) p_parent->p_child.assign(this);
}

void NodeXML::setName(char *name)
{
	p_name=name;
}

void NodeXML::setString(char *name,char *val)
{
	Variant *var=&p_parameters[name];
	var->setString((char*)val);
}

void NodeXML::setString(const char *name,const char *val)
{
	Variant *var=&p_parameters[name];
	var->setString((char*)val);
}

const char* NodeXML::getString(const char *name,const char *def)
{
	Variant *var=&p_parameters[name];
	return var->getString(def);
}

int NodeXML::getInt(const char *name,int def)
{
	Variant *var=&p_parameters[name];
	return var->getInt(def);
}

void NodeXML::setText(char *text)
{
	p_text=text;
}

NodeXML * NodeXML::getChild(char *name)
{
	NodeXML**it = (NodeXML**)p_child.data();
	NodeXML**end = (NodeXML**)p_child.endData();
	int id=0;
	char bname[64];
	String sname;
	int s=extFunctions.FindCMem(name,0,256);
	s=extFunctions.FindCMem(name,'[',s);
	if (s>=0) {
		todata(name,"%s[%i]",bname,&id);
		sname=bname;
	} else sname=name;
	while (it!=end) {
		if (sname.compare((*it)->getCharName())==-1) {
			if (id==0) return *it;
			id--;
		}
		it++;
	}
	return 0;
}

FormatXML::FormatXML()
{
	p_root=0;
}

FormatXML::~FormatXML()
{
	if (p_root) delete p_root;
	p_root=0;
}

bool FormatXML::readFromFile(char *name)
{
	File file(name,File::READ);
	if (!file.open()) return false;
	readFromFile(&file);
	file.close();

	return true;
}

bool FormatXML::readFromFile(File *file)
{
	clear();
	if (p_root==0) p_root=new NodeXML();
	p_root->setName(file->getFileName());

	if (!_readFromFile(file,p_root)) {
		return false;
	}
	return true;
}

bool FormatXML::saveToFile(char *name)
{
	File file(name,File::WRITE);
	if (!file.open()) return false;
	saveToFile(&file);
	file.close();

	return true;
}

bool FormatXML::saveToFile(File *file)
{
	if (p_root) p_root->setName(file->getFileName());

	if (!_saveToFile(file,p_root)) {
		return false;
	}
	return true;
}

NodeXML *FormatXML::newNode(NodeXML*parent)
{
	if (!parent) {
		if (p_root) return p_root;
		p_root=new NodeXML();
		return p_root;
	}
	return new NodeXML(parent);
}

NodeXML *FormatXML::getNodeByPath(char *path)
{
	int size=extFunctions.FindCMem(path,0,256);
	char ppath[256];
	extFunctions.MoveMem(path,ppath,size+1);
	char*name=ppath;
	char*namenext=ppath;
	NodeXML *r=p_root;
	while (name && r) {
		namenext=(char*)extFunctions.STRLeftFind((char*)namenext,(char*)"/");
		if (namenext) {
			*namenext=0;
			namenext++;
		}
		r=r->getChild(name);
		name=namenext;
	}
	return r;
}

void FormatXML::clear()
{
	delete p_root;
	p_root=0;
}

char xmlcode[]={' ','/','<','>','"','=',0};

bool FormatXML::_readFromFile(File *file,NodeXML *parent)
{
	TAGINFO info=OPEN;
	p_end=false;

	while (!p_end) {
		//NodeXML *node=new NodeXML();
		char *tag=_readTagFromFile(file);
		if (p_end) return true;
		if (!tag) return false;
		char *next;
		info=OPEN;
		char *c=_readTagName(tag,&next,&info);
		if (!c) {
			if (tag) extFunctions.DeleteMem(tag,0);
			return false;
		}
		int s=extFunctions.FindCMem(c,0,256);
		NodeXML *newnode;
		if ((info==CLOSE) && (extFunctions.CmpMem((void*)parent->getCharName(),c,s)==-1)) {
			if (tag) extFunctions.DeleteMem(tag,0);
			return true;
		} else {
			newnode=new NodeXML(parent);
			newnode->setName(c);
			if (info!=SELF_CLOSE) {
				_readParams(next,newnode,&info);
				if (info==OPEN) {
					_readFromFile(file,newnode);
				}
			}
		}
		if (tag) extFunctions.DeleteMem(tag, 0);
		tag=0;
	}
	return true;
}

char nulStr[]="";

bool FormatXML::_saveToFile(File *file,NodeXML *parent)
{
	if (!parent) return false;
	unsigned int ss;
	NodeXMLList *childs = (NodeXMLList *)&parent->getNodeList();
	NodeXML**it=(NodeXML**)childs->data();
	NodeXML**end=(NodeXML**)childs->endData();
	TAGINFO info=OPEN;

	char str[256];
	String params;
	ShortString *sname;
	char c[2];
	c[1]=0;

	bool ret=true;
	while (it!=end) {
		NodeXML *child=*it;
		c[0]=0;
		if (child->getNodeList().count()==0) {
			info=SELF_CLOSE;
			c[0]='/';
		} else info=OPEN;
		sname = &child->getName();
		_writeParams(&params,child);

		char *strparams=(char *)params.str();
		if (!strparams) strparams=nulStr;
		str[0] = '<';
		ss = sname->length();
		extFunctions.MoveMem((void*)sname->str(), &str[1], ss);
		ss++;
		str[ss] = ' ';
		ss++;
		unsigned int ss2 = params.length();
		extFunctions.MoveMem((void*)params.str(), &str[ss], ss2);
		ss += ss2;
		if (c[0]) {
			str[ss] = c[0];
			ss++;
		}
		str[ss] = '>';
		ss++;
		str[ss] = '\n';
		ss++;
		str[ss] = 0;
		file->write(str,ss);

		if (info==OPEN) {
			if (!_saveToFile(file,child)) ret=false;
			str[0] = '<';
			str[1] = '/';
			ss = sname->length();
			extFunctions.MoveMem((void*)sname->str(), &str[2],ss);
			ss += 2;
			str[ss] = '>';
			ss++;
			str[ss] = '\n';
			ss++;
			str[ss] = 0;
			file->write(str, ss);
		}
		it++;
	}
	return ret;
}

bool _isCode(char c)
{
	char *f=xmlcode;
	while (*f!=0) {
		if (*f==c) return true;
		f++;
	}
	return false;
}

char* FormatXML::_readTagFromFile(File *file)
{
	String tag="";
	bool endsim=false;
	bool openparam=false;
	bool coment=false;
	int comentind=0;
	bool opentag=false;
	char dt;
	while ((!endsim) && (!p_end)) {
		if (file->read(&dt,1)==0) {
			p_end=true;
		}
		if ((!coment) && (!openparam) && (dt=='<')) {
			opentag=true;
			tag+=dt;
		} else if ((!coment) && (!openparam) && (dt=='>')) {
			endsim=true;
			opentag=false;
			tag+=dt;
		} else if ((!coment) && (opentag) && (dt=='"')) {
			tag+=dt;
			openparam=!openparam;
		} else if ((opentag) && (dt=='!')) {
			if (!coment) comentind++;
			tag+=dt;
		} else if ((opentag) && (comentind>0) && (dt=='-')) {
			tag+=dt;
			if (!coment) {
				comentind++;
				if (comentind==3) {
					coment=true;
					tag+=' ';
				}
			} else {
				comentind--;
				if (comentind==1) {
					//coment=false;
					comentind=0;
				}
			}
		} else if (coment) {
			if ((dt=='>') && comentind==0) {
				coment=false;
				endsim=true;
				opentag=false;
				tag+=dt;
			} else comentind=3;
		} else if ((!coment) && (opentag)) {
			tag+=dt;
		} 
	}
	if ((!endsim) || (openparam) || (opentag)) return 0;
	int size=tag.length();
	char * ret=(char*)extFunctions.CreateMem(size+1,0);
	extFunctions.MoveMem((void*)tag.str(),ret,tag.length());
	ret[size]=0;
	return ret;
}

char* FormatXML::_readTagName(char *tag,char **last,TAGINFO *info)
{
	char *c=tag;
	bool begin=false;
	char *sname=c;
	*last=0;
	while (*c!=0) {
		if (_isCode(*c)) {
			if (*c=='/') {
				if ((!begin) && (info)) *info=CLOSE;
				if ((begin) && (info)) *info=SELF_CLOSE;
			}
			*c=0;
			if (begin) {
				*last=c+1;
				if ((c-sname>2) && (sname[0]=='!') && (sname[1]=='-') && (sname[2]=='-')) *info=SELF_CLOSE;
				if ((c-sname>3) && (sname[0]=='?') && (sname[1]=='x') && (sname[2]=='m') && (sname[3]=='l')) *info=SELF_CLOSE;
				return sname;
			}
		} else {
			if (!begin) {
				begin=true;
				sname=c;
			}
		}
		c++;
	}
	return 0;
}

bool FormatXML::_readParams(char *tag, NodeXML *newnode, TAGINFO *info)
{
	char *c=tag;
	bool paramvalue=false;
	ShortString read="";
	ShortString name="";

	while (*c!=0) {
		if (_isCode(*c)) {
			if (*c=='"') {
				paramvalue=!paramvalue;
			} else {
				if (paramvalue) read+=*c;
			}
			if (!paramvalue) {
				if (*c=='/') {
					if (info) *info=SELF_CLOSE;
				} else if (*c=='>') {
					return true;
				} else if (*c=='=') {
					name=read;
					read="";
				}
				if (*c!='=') {
					if ((name.length()>0) && (read.length()>0)) {
						if (newnode) newnode->setString(name.str(),read.str());
					}
					read="";
				}
			}
		} else {
			read+=*c;
		}
		c++;
	}
	return false;
}

void FormatXML::_writeParams(String *tag, NodeXML *newnode)
{
	ParametersList::iterator it=newnode->getParameterList().begin();
	ParametersList::iterator end=newnode->getParameterList().end();

	*tag="";

	while (it!=end) {

		*tag+=it.key();
		*tag+="=\"";
		*tag+=it.value().getString();
		*tag+="\" ";
		it++;
	}
}

TYPEINFO(FormatXML)

}

OPTIMIZE_OFF;
