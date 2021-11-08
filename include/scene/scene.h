/*
 * scene.h
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <bt.h>
#include <core/objectmanager.h>

OPTIMIZE_ON;

namespace csad {

using namespace bt;

/**
 * @defgroup scene csad: scene
 * @brief classes and architecture environment, objects in space.
 * @see Scene, Transform, Camera, MeshFilter, Material.
 *
 */

/**
 * @defgroup scenegui csad: gui
 * @brief
 * @see scene.
 *
 */

class Transform;
class Camera;
class LightingModel;

typedef Vector<Transform*> SceneTransforms;
typedef SortVoidVector<Transform> ListSceneTransforms;
/**
 * @class Scene
 *
 * @ingroup scene
 * @brief Scene - environment objects that belongs to the Manager Graph.
 *
 * The hierarchical model consisting of objects Transform.
 *
 * For description in the configuration:
 @verbatim
   <Scene name="the name of the scene">
   ... internal objects ...
   </Scene>
 @endverbatim
 *
 * @see Graph, scene.
 */

class Scene: public BaseObject {
public:
	MEMDEFAULT(Scene)

	CSAD_API Scene(char *name);
	CSAD_API Scene(const char *name="");
	CSAD_API ~Scene();

	/// creates the camera object, and returns it to the component.
	CSAD_API Camera *createCamera(char *name,Transform * parent=0);
	/// creates the camera object, and returns it to the component, with out of name.
	CSAD_API Camera *createCamera(const char *name="",Transform * parent=0);
	/// creates the object position.
	CSAD_API Transform *createTransform(char *name,Transform * parent=0);
	/// creates the object position, with out of name.
	CSAD_API Transform *createTransform(const char *name="",Transform * parent=0);

	/// returns the camera component.
	CSAD_API Camera *getCamera(char *name);
	CSAD_API Camera *getCamera(const char *name);

	CSAD_API LightingModel *createLightingModel(char *name);
	_FORCEINLINE LightingModel *getLightingModel(char *name) { return (LightingModel *)p_lightingmodels.getObject(name); }
	_FORCEINLINE LightingModel *getDefaultLightingModel() { if (getMapLightings().count()<=0) return 0; return (LightingModel *)getMapLightings().valueAt(0); }

	/// restores the dependent object by name.
	CSAD_API Transform *getTransform(char *name);
	CSAD_API Transform *getTransform(const char *name);

	/// returns the root object.
	_FORCEINLINE Transform *getRoot() {return p_root;}

	/// detach current object position.
	CSAD_API void detachObject(Transform *transform);

	/// returns a named list of objects.
	_FORCEINLINE ObjectsList &getMapObjects() { return p_transforms.getObjects(); }
	_FORCEINLINE ListSceneTransforms &getObjects() { return *((ListSceneTransforms*)&p_addontransforms); }

	_FORCEINLINE ObjectsList &getMapLightings() { return p_lightingmodels.getObjects(); }

	/// Activate scene in events
	CSAD_API void setActive(bool);
	/// State of action events
	_FORCEINLINE bool active() { return (p_flags & ACTIVE)!=0;}

	_FORCEINLINE unsigned int changes() { return p_changes; }
	_FORCEINLINE void change() { p_changes++; }

	/// return scene name
	CSAD_API const char * getName();

	/// the active scene
	static Scene* getDefault() {return p_default;}

	CSAD_API void *set(unsigned _int32 ,void *);
//	static void actionScene(Scene *scene); //???

	CSAD_API TYPEINFO_H

private:
	enum hideFlags {
		DETACHLOCK = 0x00000001,
		NEEDCLEAN = 0x00000002,
		ACTIVE = 0x00001000,
	};

	CSAD_API static Scene *p_default;
	unsigned int p_changes;
	int p_count;
	int p_flags;
	Transform *p_root;
//	Transform **p_list;
	ObjectManager p_transforms;
	SortVoidVector<Transform> p_addontransforms;

	ObjectManager p_lightingmodels;

	void _regTransform(Transform* transform,char *name);
	void _regTransform(Transform* transform,const char *name = "");

	void _init();
//	void _prepare(Camera *camera); // ??
	void _start();
	void _update();
	void _prepare();
	void _render();
	void _quit();

	void _setDefault();
	void _destroyTransforms();
	void _destroyLightingModels();
	void _checkClean();

friend class LocalTransform;
friend class Camera;
friend class LightingModel;
friend class Graph;
friend class Renderer;
};

}

OPTIMIZE_OFF;

#endif /* SCENE_H_ */
