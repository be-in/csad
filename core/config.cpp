/*
 * config.cpp
 *
 *  Created on: 23.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include "config.h"
#include <core/containercomponents.h>
#include <core/component.h>
#include <core/graph.h>
#include <core/input.h>
#include <core/module.h>
#include <core/system.h>
#include <format.h>
#include <bt.h>
#include <platform.h>
#include <components/resender.h>
#include <scene/style.h>
#include <scene/scene.h>
#include <scene/sceneresender.h>
#include <scene/material.h>
#include <scene/texture2d.h>
#include <scene/shader.h>
#include <scene/transform.h>
#include <scene/camera.h>
#include <scene/mesh.h>
#include <scene/light.h>
#include <scene/lightingmodel.h>
#include <scene/meshfilter.h>
#include <scene/groupmesh.h>
#include <scene/text3d.h>
#include <scene/textstyle.h>
#include <scene/fonttext.h>
#include <scene/gui/sgbutton.h>
#include <scene/gui/sglineedit.h>
#include <scene/gui/sgscroll.h>
#include <scene/gui/sgelement.h>
#include <scene/gui/sgstyles.h>
#include <scene/gui/sgmouse.h>
#include <scene/gui/sgmenu.h>
#include "csadcore.h"
#include "csad/core/base/stringconsts.h"

OPTIMIZE_ON;

namespace csad {

COMPONENT_CLASS(Resender)
COMPONENT_CLASS(Camera)
COMPONENT_CLASS(Light)
COMPONENT_CLASS(MeshFilter)
COMPONENT_CLASS(GroupMesh)
COMPONENT_CLASS(Text3D)
COMPONENT_CLASS(SGMenu)
COMPONENT_CLASS(SGMouse)
COMPONENT_CLASS(SGMouseMesh)
COMPONENT_CLASS(SGButton)
COMPONENT_CLASS(SGLineEdit)
COMPONENT_CLASS(SGScroll)
COMPONENT_CLASS(SGElement)
COMPONENT_CLASS(SGButtonStyle)
COMPONENT_CLASS(SGElementStyle)
COMPONENT_CLASS(SGLineEditStyle)
COMPONENT_CLASS(SceneResender)
COMPONENT_CLASS(TextStyle)

void *Create_NULL(void *)
{
	return 0;
}

Module * _APICALL Create_Module(ParametersList *param)
{
	char * name=0;
	char * path=0;
	char * lib=0;
	Variant *p;
	if ((p=param->find(STR_NAME))!=0) name=p->getString();
	if ((p=param->find("path"))!=0) path=p->getString();
	if ((p=param->find("lib"))!=0) lib=p->getString();
	ShortString cpath;
	Library::findLib(&cpath,path,lib);
	Module * module=System::system().createModule(cpath.str(),name);
	return module;
}

BaseObject * _APICALL Create_Include(ParametersList *param)
{
	char * path=0;
	Variant *p;
	if ((p=param->find("path"))!=0) path=p->getString();
	FormatXML xml;
	xml.readFromFile(path);
	BaseObject *parent=0;
	Config *config=0;
	if ((p=param->find(STR_PARENT))!=0) parent=(BaseObject*)p->getPointer();
	if ((p=param->find("config"))!=0) config=(Config*)p->getPointer();
	config->prepareNodes(parent,xml.getNode());
	return 0;
}

Mouse * _APICALL Create_Mouse(ParametersList *param)
{
	char * name=0;
	char * driver=0;
	Variant *p;
	if ((p=param->find(STR_NAME))!=0) name=p->getString();
	if ((p=param->find("driver"))!=0) driver=p->getString();
	Mouse * mouse=Input::input().createMouse(driver,name);
	return mouse;
}

Keyboard * _APICALL Create_Keyboard(ParametersList *param)
{
	char * name=0;
	char * driver=0;
	Variant *p;
	if ((p=param->find(STR_NAME))!=0) name=p->getString();
	if ((p=param->find("driver"))!=0) driver=p->getString();
	Keyboard * keyboard=Input::input().createKeyboard(driver,name);
	return keyboard;
}

Display * _APICALL Create_Display(ParametersList *param)
{
	char* name=0;
	//int device=0;
	//int id=0;
	//int mode=0;
	Variant *p;
	if ((p=param->find(STR_NAME))!=0) name=p->getString();
	Display *display=Graph::graph().createDisplay(name);
	display->write(param);
	return display;
}

GlContext * _APICALL Create_Context(ParametersList *param)
{
	Display *display=0;
	char* name=0;
	Variant *p;
	if ((p=param->find(STR_PARENT))!=0) display=(Display*)p->getPointer();
	if (!display) return 0;
	if ((p=param->find(STR_NAME))!=0) name=p->getString();
	if (display->type()!=Display::t()) return 0;
	GlContext * context=display->createContext(name);
	return context;
}

Renderer * _APICALL Create_Renderer(ParametersList *param)
{
	char * name=0;
	int order=0;
	Variant *p;
	if ((p=param->find(STR_NAME))!=0) name=p->getString();
	if ((p=param->find("order"))!=0) order=p->getInt(0);
	Renderer *renderer=Graph::graph().createRenderer(order,name);
	return renderer;
}

Transform * _APICALL Create_Scene(ParametersList *param)
{
	char* name=0;
	Variant *p;
	if ((p=param->find(STR_NAME))!=0) name=p->getString();
	Scene * scene=Graph::graph().createScene(name);
	return scene->getRoot();
}

Transform * _APICALL Create_Transform(ParametersList *param)
{
	Transform *parent=0;
	char* name=0;
	Variant *p;
	if ((p=param->find(STR_PARENT))!=0) parent=(Transform*)p->getPointer();
	if ((p=param->find(STR_NAME))!=0) name=p->getString();
	if (!parent) return 0;
	if (parent->type()!=Transform::t()) return 0;
	Transform *transform=parent->createTransform(name);
	return transform;
}

LightingModel * _APICALL Create_LightingModel(ParametersList *param)
{
	Transform *parent=0;
	char* name=0;
	Variant *p;
	if ((p=param->find(STR_PARENT))!=0) parent=(Transform*)p->getPointer();
	if ((p=param->find(STR_NAME))!=0) name=p->getString();
	if (parent->type()!=Transform::t()) return 0;
	Scene *scene=parent->getScene();
	if (scene->type()!=Scene::t()) return 0;
	LightingModel * lmodel=scene->createLightingModel(name);
	return lmodel;
}

FontServer * _APICALL Create_FontServer(ParametersList *param)
{
	char* name=0;
	Variant *p;
	if ((p=param->find(STR_NAME))!=0) name=p->getString();
	FontServer *fontserver=Graph::graph().createFontServer(name);
	return fontserver;
}

Font * _APICALL Create_Font(ParametersList *param)
{
	FontServer *fontserver=0;
	char* name=0;
	Variant *p;
	if ((p=param->find(STR_PARENT))!=0) fontserver=(FontServer*)p->getPointer();
	if ((p=param->find(STR_NAME))!=0) name=p->getString();
	if (fontserver->set(BaseObject::TYPE,0)!=(void *)FontServer::t()) return 0;
	Font *font=fontserver->createFont(name);
	return font;
}

FontText * _APICALL Create_FontText(ParametersList *param)
{
	FontServer *fontserver=0;
	char* name=0;
	Variant *p;
	if ((p=param->find(STR_PARENT))!=0) fontserver=(FontServer*)p->getPointer();
	if ((p=param->find(STR_NAME))!=0) name=p->getString();
	if (fontserver->set(BaseObject::TYPE,0)!=(void *)FontServer::t()) return 0;
	FontText *font=fontserver->createFontText(name);
	return font;
}

Style * _APICALL Create_Style(ParametersList *param)
{
	char* name=0;
	Variant *p;
	if ((p=param->find(STR_NAME))!=0) name=p->getString();
	Style *style=Graph::graph().createStyle(name);
	return style;
}

Material * _APICALL Create_Material(ParametersList *param)
{
	char* name=0;
	Variant *p;
	if ((p=param->find(STR_NAME))!=0) name=p->getString();
	Material *material=Graph::graph().createMaterial(name);
	return material;
}

/*Material * _STDCALL Create_TextureLayer(ParametersList *param)
{
	Material *parent=0;
	if (param->contains(STR_PARENT))  parent=(Material*)(*param)[STR_PARENT].getPointer();
	if (parent->type()!=Material::t()) return 0;
	return parent;
}*/

Texture2D * _APICALL Create_Texture2D(ParametersList *param)
{
	char* name=0;
	Variant *p;
	if ((p=param->find(STR_NAME))!=0) name=p->getString();
	Texture2D *texture=Graph::graph().createTexture2D(name);
	return texture;
}

Shader * _APICALL Create_Shader(ParametersList *param)
{
	char* name=0;
	Variant *p;
	if ((p=param->find(STR_NAME))!=0) name=p->getString();
	Shader *shader=Graph::graph().createShader(name);
	return shader;
}

Transform * _APICALL Create_Quad(ParametersList *param)
{
	Transform *parent=0;
	char* name=0;
	Variant *p;
	if ((p=param->find(STR_PARENT))!=0) parent=(Transform*)p->getPointer();
	if ((p=param->find(STR_NAME))!=0) name=p->getString();
	if (!parent) return 0;
	if (parent->type()!=Transform::t()) return 0;
	Transform *transform=parent->createTransform(name);
	MeshFilter *mf=transform->addComponent<MeshFilter>();
	mf->setMesh(Mesh::Quad);
	return transform;
}

Transform * _APICALL Create_Cube(ParametersList *param)
{
	Transform *parent=0;
	char* name=0;
	Variant *p;
	if ((p=param->find(STR_PARENT))!=0) parent=(Transform*)p->getPointer();
	if ((p=param->find(STR_NAME))!=0) name=p->getString();
	if (!parent) return 0;
	if (parent->type()!=Transform::t()) return 0;
	Transform *transform=parent->createTransform(name);
	MeshFilter *mf=transform->addComponent<MeshFilter>();
	mf->setMesh(Mesh::Cube);
	return transform;
}

Core * _APICALL Create_Core(ParametersList *)
{
	return core;
}

void InitClass(Core *core)
{
	Core *mcore=core;

	ClassManager *classManager=mcore->classManager();
	// system
	//classManager->regClass("!--",(void*)-2,(tfSTDCALL_p_FUNC_p)&Create_NULL);
	classManager->regClass("Core",Core::t(),(tfSTDCALL_p_FUNC_p)&Create_Core);
	classManager->regClass("ObjectManager",ObjectManager::t(),(tfSTDCALL_p_FUNC_p)0);
	classManager->regClass("Module",Module::t(),(tfSTDCALL_p_FUNC_p)&Create_Module);
	classManager->regClass("Include",FormatXML::t(),(tfSTDCALL_p_FUNC_p)&Create_Include);
	// input
	classManager->regClass("Mouse",Mouse::t(),(tfSTDCALL_p_FUNC_p)&Create_Mouse);
	classManager->regClass("Keyboard",Keyboard::t(),(tfSTDCALL_p_FUNC_p)&Create_Keyboard);
	// graph
	classManager->regClass("FontServer",FontServer::t(),(tfSTDCALL_p_FUNC_p)&Create_FontServer);
	classManager->regClass("Font",Font::t(),(tfSTDCALL_p_FUNC_p)&Create_Font);
	classManager->regClass("FontText",FontText::t(),(tfSTDCALL_p_FUNC_p)&Create_FontText);
	if (!classManager->isRegistered("Display")) classManager->regClass("Display",Display::t(),(tfSTDCALL_p_FUNC_p)&Create_Display);
	if (!classManager->isRegistered("GlContext")) classManager->regClass("GlContext",GlContext::t(),(tfSTDCALL_p_FUNC_p)&Create_Context);
	classManager->regClass("Renderer",Renderer::t(),(tfSTDCALL_p_FUNC_p)&Create_Renderer);
	classManager->regClass("Material",Material::t(),(tfSTDCALL_p_FUNC_p)&Create_Material);
	classManager->regClass("Texture2D",Texture2D::t(),(tfSTDCALL_p_FUNC_p)&Create_Texture2D);
	classManager->regClass("Shader",Shader::t(),(tfSTDCALL_p_FUNC_p)&Create_Shader);
	classManager->regClass("Style",Style::t(),(tfSTDCALL_p_FUNC_p)&Create_Style);
	classManager->regClass("Scene",Scene::t(),(tfSTDCALL_p_FUNC_p)&Create_Scene);
	classManager->regClass("LightingModel",LightingModel::t(),(tfSTDCALL_p_FUNC_p)&Create_LightingModel);
	// scene
	classManager->regClass("Transform",Transform::t(),(tfSTDCALL_p_FUNC_p)&Create_Transform);
	// primitives
	classManager->regClass("Quad",Mesh::MeshQuad::t(),(tfSTDCALL_p_FUNC_p)&Create_Quad);
	classManager->regClass("Cube",Mesh::MeshCube::t(),(tfSTDCALL_p_FUNC_p)&Create_Cube);

/*	csad::Core *score=csad::core;
	if (csad::core!=mcore) {
		core==mcore;
	}*/

	INIT_COMPONENT(Camera)
	INIT_COMPONENT(Light)
	INIT_COMPONENT(MeshFilter)
	INIT_COMPONENT(GroupMesh)
	INIT_COMPONENT(Resender)
	INIT_COMPONENT(SceneResender)
	INIT_COMPONENT(Text3D)
	INIT_COMPONENT(TextStyle)
	INIT_COMPONENT(SGMenu)
	INIT_COMPONENT(SGMouse)
	INIT_COMPONENT(SGMouseMesh)
	INIT_COMPONENT(SGButton)
	INIT_COMPONENT(SGLineEdit)
	INIT_COMPONENT(SGScroll)
	INIT_COMPONENT(SGElement)
	INIT_COMPONENT(SGButtonStyle)
	INIT_COMPONENT(SGElementStyle)
	INIT_COMPONENT(SGLineEditStyle)
	//csad::core=score;
}

Config::Config(Core *core)
{
	mcore=core;
}

Config::~Config()
{
}

void Config::createFromXml(FormatXML * xml)
{
	NodeXML *node=xml->getNode();
	if (!node) return;

	_readModules(node);

	prepareNodes(core,node);

	ConfigParameterList::iterator it=mlistObj.begin();
	ConfigParameterList::iterator end=mlistObj.end();
	while (it!=end) {
		/*bt::ParametersList::iterator ee=it.value().info->begin();
		bt::ParametersList::iterator eee=it.value().info->end();
		Log::console("%s %i %i",core->classManager()->className(it.value().obj->type()),it.value().info,it.value().obj->type());*/
		/*while (eee!=ee) {
			Log::console("%s",ee.key());
			ee++;
		}*/
		it.value().obj->set(BaseObject::WRITE,it.value().info);
		it++;
	}
	mlistObj.clear();
}

void Config::_readModules(NodeXML * node)
{
	ClassManager *classManager=mcore->classManager();
	NodeXMLList::iterator it=node->getNodeList().begin();
	NodeXMLList::iterator end=node->getNodeList().end();
	while (it!=end) {
		const char *name=it.value()->getCharName();
		ObjectInfo *info=classManager->classInfo(name);
		if (info) if (info->type==Module::t())
			classManager->createObject((char*)name,&it.value()->getParameterList());
		_readModules(it.value());
		it++;
	}
}

void Config::prepareNodes(void* parent,NodeXML * node)
{
	NodeXMLList::iterator it=node->getNodeList().begin();
	NodeXMLList::iterator end=node->getNodeList().end();
	while (it!=end) {
		createFromXmlNode(parent,it.value());
		it++;
	}
}

void Config::createFromXmlNode(void* parent,NodeXML * node)
{
	ClassManager *classManager=mcore->classManager();
	ParametersList listp;
	const char *name=node->getCharName();
	typeConfigClassInfo var;
	var.obj=0;

	var.info=&node->getParameterList();
	ParametersList::iterator itp=var.info->begin();
	ParametersList::iterator endp=var.info->end();
	Variant *p;
	while (itp!=endp) {
		p=&listp[itp.key()];
		p->setString(itp.value().getString());
		itp++;
	}

	if (classManager->isRegistered(name)) {
		ObjectInfo *inf=classManager->classInfo(name);
		if (inf->type!=Module::t()) {
			if (inf->flag==ObjectInfo::COMPONENT) {
				if (parent && ((BaseObject*)parent)->isContainer()) {
					var.obj=(BaseObject*)((ContainerComponents*)parent)->addComponent(name);
				} else {
#ifdef LOG_CSAD
					Log::console("Wrong use parent for: %s",name);
#endif
				}
			} else {
				p=&listp[STR_PARENT];
				p->setVoid(parent);
				p=&listp["config"];
				p->setVoid(this);
				var.obj=classManager->createObject((char*)name,&listp);
			}
		}
	} else if ((extFunctions.CmpMem((void*)name,(void*)"!--",3)!=-1) && (extFunctions.CmpMem((void*)name,(void*)"?xml",4)!=-1)) {
#ifdef LOG_CSAD
		Log::console("Unknown class name: %s",name);
#endif
		return;
	}

	if (var.obj) mlistObj.assign(var);
	listp.clear();

	if (var.obj) prepareNodes(var.obj,node);
}

/*void Config::regClassXMLCreator(const char * name,void *info, tfSTDCALL_p_PROC_p_p fun)
{
	typeConfigClassInfo v;
	v.info=info;
	v.fun=fun;
	p_classList[name]=v;
}*/

}

OPTIMIZE_OFF;
