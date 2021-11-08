/*
 * graph.cpp
 *
 *  @brief Complex software application developer, MS Visual C++ 2003-2010, QNX Momentics IDE
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

// !TO DO попробовать разбить концепцию менеджера на контейнер, и компоненты управлю€ющие подчиненными менеджерами
// - контейнер с посто€нными компонентами.

#include <core/graph.h>
#include "csadcore.h"
#include <platform.h>
#include <scene/scene.h>
#include <scene/camera.h>
#include <scene/style.h>
#include <scene/material.h>
#include <scene/texture2d.h>
#include <scene/shader.h>
#include "csad/platform/localdisplay.h"
#include "csad/core/base/stringconsts.h"

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

	int _APICALL SwapBuffersThread(Thread*thread);

	class GraphThread:public Thread {
	public:
		GraphThread(Graph *graph):Thread(false,(tfSTDCALL_p_FUNC_p)&SwapBuffersThread) {mgraph=graph;}

		Graph *mgraph;
	};

	int _APICALL SwapBuffersThread(Thread*thread)
	{
		while (!thread->isTerminated()) {
			((GraphThread*)thread)->mgraph->updateDisplay();
			thread->stop();
		}
		return 0;
	}

	Graph::Graph()		
	{
		mbuffersRender=0;
		//mbuffersRender = new GraphThread(this);
		p_display = new ObjectManager("display");
		p_scene = new ObjectManager("scene");
		p_renderer = new ObjectManager("renderer");
		p_fontserver = new ObjectManager("fontserver");
		p_style = new ObjectManager("style");
		p_material = new ObjectManager(STR_MATERIAL);
		p_texture = new ObjectManager(STR_TEXTURE);
		p_shader = new ObjectManager("shader");
		mflags=0;
	}

	Graph::~Graph()
	{
		if (mbuffersRender) delete mbuffersRender;
		if (p_texture) p_texture->destroyObjects<Texture2D>();
		if (p_shader) p_shader->destroyObjects<Shader>();
		if (p_display) p_display->destroyObjects<Display>();
		if (p_scene) p_scene->destroyObjects<Scene>();
		if (p_renderer) p_renderer->destroyObjects<Renderer>();
		if (p_material) p_material->destroyObjects<Material>();
		if (p_fontserver) p_fontserver->destroyObjects<FontServer>();
		if (p_style) p_style->destroyObjects<Style>();
		// error wen remove from VoidSortStringMap
		delete p_display;
		delete p_scene; 
		delete p_renderer;
		delete p_fontserver;
		delete p_style;
		delete p_material;
		delete p_texture;
		delete p_shader;
		mbuffersRender=0;
		p_display=0;
		p_scene=0;
		p_renderer=0;
		p_fontserver=0;
		p_style=0;
		p_material=0;
		p_texture=0;
		p_shader=0;
	}

	Display* Graph::createDisplay(char * name)
	{
		if ((name!=0) && (name[0]!=0)) {
			Display* r=(Display*)p_display->getObject(name);
			if (r) return r;
		}
		Display * display=new LocalDisplay(name);
		return display;
	}

	Scene* Graph::createScene(char * name)
	{
		if ((name!=0) && (name[0]!=0)) {
			Scene* r=(Scene*)p_scene->getObject(name);
			if (r) return r;
		}
		return new Scene(name);
	}

	Renderer* Graph::createRenderer(int order,char * name)
	{
		if ((name!=0) && (name[0]!=0)) {
			Renderer* r=(Renderer*)p_renderer->getObject(name);
			if (r) return r;
		}
		return new Renderer(order,name);
	}

	FontServer* Graph::createFontServer(char * name)
	{
		if ((name!=0) && (name[0]!=0)) {
			FontServer* r=(FontServer*)p_fontserver->getObject(name);
			if (r) return r;
		}
		return new FontServer(name);
	}

Style* Graph::createStyle(char * name)
{
	if ((name!=0) && (name[0]!=0)) {
		Style* r=(Style*)p_style->getObject(name);
		if (r) return r;
	}
	return new Style(name);
}

Material* Graph::createMaterial(char * name)
{
	if ((name!=0) && (name[0]!=0)) {
		Material* r=(Material*)p_material->getObject(name);
		if (r) return r;
	}
	return new Material(name);
}

Texture2D *Graph::createTexture2D(char * name)
{
	if ((name!=0) && (name[0]!=0)) {
		Texture2D* r=(Texture2D*)p_texture->getObject(name);
		if (r) return r;
	}
	return new Texture2D(name);
}

Shader *Graph::createShader(char * name)
{
	if ((name!=0) && (name[0]!=0)) {
		Shader* r=(Shader*)p_shader->getObject(name);
		if (r) return r;
	}
	return new Shader(name);
}

Display* Graph::getDisplay(char *name)
{
	return (Display*)p_display->getObject(name);
}

Display* Graph::getDisplayByHandle(void *handle)
{
	ObjectsList& list=p_display->getObjects();
	ObjectsList::iterator it = list.begin();
	ObjectsList::iterator end = list.end();
	Display *display=0;
	while (it!=end) {
		display=(Display*)it.value();
		if (display->getHandle()==handle) return display;
		it++;
	}
	return display;
}

Display* Graph::getDisplayIntersect(vector3f *pos)
{
	ObjectsList& list=p_display->getObjects();
	ObjectsList::iterator it = list.begin();
	ObjectsList::iterator end = list.end();
	Display *display=0;
	vector2i global(pos);
	while (it!=end) {
		display=(Display*)it.value();
		if (display->isGlobalPoint(&global)) return display;
		it++;
	}
	return 0;
}

GlContext* Graph::getContext(char *path)
{
	return GlContext::finder(path);
}

Scene* Graph::getScene(char *name)
{
	return (Scene*)p_scene->getObject(name);
}

Renderer* Graph::getRenderer(char *name)
{
	return (Renderer*)p_renderer->getObject(name);
}

Renderer* Graph::getRendererIntersect(vector3f *pos,Display* display)
{
	ObjectsList& list=p_renderer->getObjects();
	ObjectsList::iterator it = list.begin();
	ObjectsList::iterator end = list.end();
	Renderer *renderer=0;
	GlContext *context=0;
	vector2i global(pos);
	if (display) {
		display->toLocal(&global,&global);
		while (it!=end) {
			renderer=(Renderer*)it.value();
			it++;
			context=renderer->getContext();
			if ((context) && (context->getDisplay()==display)) {
				Camera *camera=renderer->getCamera();
				if ((camera) && (camera->Intersect(&global,context))) return renderer;
			}
		}
	} else {
		while (it!=end) {
			renderer=(Renderer*)it.value();
			if (renderer->isIntersection(&global)) return renderer;
			it++;
		}
	}
	return renderer;
}

FontServer* Graph::getFontServer(char * name)
{
	return (FontServer*)p_fontserver->getObject(name);
}

Style* Graph::getStyle(char * name)
{
	return (Style*)p_style->getObject(name);
}

Material* Graph::getMaterial(char * name)
{
	return (Material*)p_material->getObject(name);
}

Texture2D *Graph::getTexture2D(char * name)
{
	return (Texture2D*)p_texture->getObject(name);
}

Shader* Graph::getShader(char * name)
{
	return (Shader*)p_shader->getObject(name);
}

Graph & Graph::graph()
{
	return *core->graph();
}

Scene *Graph::scene()
{
	return Scene::getDefault();
}

void *graphTypes[7]={(void*)Display::t(),(void*)Style::t(),(void*)Scene::t(),(void*)Renderer::t(),(void*)FontServer::t(),(void*)Material::t(),(void*)Texture2D::t()};

bool Graph::type(void * type)
{
	int i=0;
	while (i<7) {
		if (graphTypes[i]==type) return true;
		i++;
	}
	return false;
}

void *Graph::set(unsigned _int32 id,void*)
{
	if (id==BaseObject::TYPE) return Graph::t();
	return 0;
}

bool Graph::isDisplayLocked()
{
	if ((mflags&CONFIRM_DISPLAY_UNLOCK)!=0) {
		mflags&=~CONFIRM_DISPLAY_UNLOCK;
		mflags&=~DISPLAY_LOCKED;
	}
	return (mflags&DISPLAY_LOCKED)!=0;
}

void Graph::init()
{
	ObjectsList::iterator it = p_fontserver->getObjects().begin();
	ObjectsList::iterator end = p_fontserver->getObjects().end();
	while (it!=end)
	{
		FontServer* fs=(FontServer*)it.value();
		fs->init();
		it++;
	}
}

void Graph::start()
{
	ObjectsList::iterator it = p_scene->getObjects().begin();
	ObjectsList::iterator end = p_scene->getObjects().end();
	while (it!=end)
	{
		Scene* scene=(Scene*)it.value();
		scene->_setDefault();
		scene->_start();
		it++;
	}
}

void Graph::updateScene()
{
	ObjectsList::iterator it = p_scene->getObjects().begin();
	ObjectsList::iterator end = p_scene->getObjects().end();
	while (it!=end)
	{
		Scene* scene=(Scene*)it.value();
		if (scene->active()) {
			scene->_setDefault();
			scene->_update();
		}
		it++;
	}
}

void Graph::updateDisplay()
{
	ObjectsList::iterator it = p_display->getObjects().begin();
	ObjectsList::iterator end = p_display->getObjects().end();
	//if (!mbuffersRender->isThisThread()) {
		if ((mflags&DISPLAY_LOCKED)==0) {
			/*if (mbuffersRender->isTerminated()) mbuffersRender->create();
			if (mbuffersRender->isSuspended()) {
				//mflags|=DISPLAY_LOCKED;
				core->system()->getTimer().updateFrame();
				mbuffersRender->play();
			}*/
		}
		if ((mflags&CONFIRM_DISPLAY_UNLOCK)!=0) {
			mflags&=~CONFIRM_DISPLAY_UNLOCK;
			mflags&=~DISPLAY_LOCKED;
		}
		core->system()->getTimer().updateFrame();
		while (it!=end)
		{
			Display* display=(Display*)it.value();
			display->swapBuffers();
			it++;
		}
	//} else {
		/*while (it!=end)
		{
			Display* display=(Display*)it.value();
			display->swapBuffers();
			it++;
		}*/
		if ((mflags&DISPLAY_LOCKED)!=0) mflags|=CONFIRM_DISPLAY_UNLOCK;
	//}
}

void Graph::quit()
{
	ObjectsList::iterator it = p_scene->getObjects().begin();
	ObjectsList::iterator end = p_scene->getObjects().end();
	while (it!=end)
	{
		Scene* scene=(Scene*)it.value();
		scene->_setDefault();
		scene->_quit();
		it++;
	}
	it = p_fontserver->getObjects().begin();
	end = p_fontserver->getObjects().end();
	while (it!=end)
	{
		FontServer* fs=(FontServer*)it.value();
		fs->close();
		it++;
	}
}

TYPEINFO(Graph)

}

OPTIMIZE_OFF;
WARNING_ENABLE;
