/*
 * graph.h
 *
 *  @brief Complex software application developer, MS Visual C++ 2003-2010, QNX Momentics IDE
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <core/objectmanager.h>
#include <core/containercomponents.h>

namespace csad {

class Display;
class GlContext;
class Scene;
class Renderer;
class FontServer;
class Style;
class Material;
class Texture2D;
class Shader;
class Thread;

/**
 * @class Graph
 *
 * @ingroup core
 * @brief Graph - Manager graphics.
 *
 * @see core
 */

class Graph: public BaseObject {
public:
	MEMDEFAULT(Graph)

	CSAD_API Graph();
	CSAD_API ~Graph();

	/// Creates the object of the screen with the specified name, or returns available if the object of the screen with the same name already been created.
	CSAD_API Display* createDisplay(char * name);
	_FORCEINLINE Display* createDisplay(const char * name="") {return createDisplay((char*)name);}
	/// Creates the environment of the scene with the specified name, or returns available if the environment of the scene with the same name already been created.
	CSAD_API Scene* createScene(char * name);
	/// Creates the environment of the scene with the specified name, or returns available if the environment of the scene with the same name already been created.
	_FORCEINLINE Scene* createScene(const char * name="") {return createScene((char*)name);}
	CSAD_API Renderer* createRenderer(int order,char * name);
	_FORCEINLINE Renderer* createRenderer(int order=0,const char * name="") {return createRenderer(order,(char*)name);}
	CSAD_API FontServer* createFontServer(char * name);
	_FORCEINLINE FontServer* createFontServer(const char * name="") {return createFontServer((char*)name);}
	/// Creates a container styles, or returns available if the container styles with the same name already been created.
	CSAD_API Style* createStyle(char * name);
	/// Creates a container styles, or returns available if the container styles with the same name already been created.
	_FORCEINLINE Style* createStyle(const char * name="") {return createStyle((char*)name);}
	/// Creates material
	CSAD_API Material* createMaterial(char * name);
	/// Creates material
	_FORCEINLINE Material* createMaterial(const char * name="") {return createMaterial((char*)name);}
	/// Creates texture
	CSAD_API Texture2D* createTexture2D(char * name);
	_FORCEINLINE Texture2D* createTexture2D(const char * name="") {return createTexture2D((char*)name);}
	/// Creates Shader
	CSAD_API Shader* createShader(char * name);
	/// Creates Shader
	_FORCEINLINE Shader* createShader(const char * name="") {return createShader((char*)name);}

	/// Restores a screen object at the specified name
	CSAD_API Display* getDisplay(char *name);
	/// Restores a screen object associated with the specified ID image
	CSAD_API Display* getDisplayByHandle(void *handle);
	/// Restores a screen object associated with the specified point
	CSAD_API Display* getDisplayIntersect(vector3f *pos);
	_FORCEINLINE Display* getDisplay(const char *name) {return getDisplay((char*)name);}
	/// returns the object context in his way
	CSAD_API GlContext* getContext(char *path);
	_FORCEINLINE GlContext* getContext(const char *path) {return getContext((char*)path);}
	/// Returns the scene with the specified name
	CSAD_API Scene* getScene(char *name);
	_FORCEINLINE Scene* getScene(const char *name) {return getScene((char*)name);}
	CSAD_API Renderer* getRenderer(char *name);
	CSAD_API Renderer* getRendererIntersect(vector3f *pos,Display* display=0);
	_FORCEINLINE Renderer* getRenderer(const char *name) {return getRenderer((char*)name);}
	CSAD_API FontServer* getFontServer(char * name);
	_FORCEINLINE FontServer* getFontServer(const char * name) {return getFontServer((char*)name);}
	/// returns the container style object by its name
	CSAD_API Style* getStyle(char * name);
	/// returns the container style object by its name
	_FORCEINLINE Style* getStyle(const char * name) {return getStyle((char*)name);}
	/// returns the ìaterial object by its name
	CSAD_API Material* getMaterial(char * name);
	/// returns the ìaterial object by its name
	_FORCEINLINE Material* getMaterial(const char * name) {return getMaterial((char*)name);}
	/// returns the texture object by its name
	CSAD_API Texture2D* getTexture2D(char * name);
	/// returns the texture object by its name
	_FORCEINLINE Texture2D* getTexture2D(const char * name) {return getTexture2D((char*)name);}
	/// returns the texture object by its name
	CSAD_API Shader* getShader(char * name);
	/// returns the texture object by its name
	_FORCEINLINE Shader* getShader(const char * name) { return getShader((char*)name); }

	CSAD_API bool isDisplayLocked();

	_FORCEINLINE ObjectManager *getDisplays() { return p_display; }
	_FORCEINLINE ObjectManager *getRenderers() { return p_renderer; }
	_FORCEINLINE ObjectManager *getScenes() { return p_scene; }
	_FORCEINLINE ObjectManager *getShaders() { return p_shader; }
	_FORCEINLINE ObjectManager *getMaterials() { return p_material; }

	CSAD_API void init();
	CSAD_API void start();
	CSAD_API void updateScene();
	CSAD_API void updateDisplay();
	CSAD_API void quit();

	/// Active Manager graphical elements
	CSAD_API static Graph &graph();
	/// active scene, the scene becomes active during the build its projection using Renderer
	CSAD_API static Scene *scene();

	/// returns true if the object type belongs to the graphics Manager
	CSAD_API static bool type(void * type);

	CSAD_API void *set(unsigned _int32,void*);

	CSAD_API TYPEINFO_H

private:

	enum Flag {
		DISPLAY_LOCKED = 0x00000001,
		CONFIRM_DISPLAY_UNLOCK = 0x00000100,
	};

	ObjectManager *p_display;
	ObjectManager *p_scene;
	ObjectManager *p_renderer;
	ObjectManager *p_fontserver;
	ObjectManager *p_style;
	ObjectManager *p_material;
	ObjectManager *p_texture;
	ObjectManager *p_shader;

	unsigned int mflags;
	Thread *mbuffersRender;

	//Scene *p_scene;  //??

friend class Application;
friend class LocalDisplay;
friend class Scene;
friend class Renderer;
friend class FontServer;
friend class Style;
friend class Material;
friend class Texture2D;
friend class Shader;
friend class InterfaceRenderSystem;
};

}

#endif /* GRAPH_H_ */
