/*
 * renderer.h
 *
 *  Created on: 15.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include <platform/platformapi.h>
#include <bt.h>

namespace csad {

/**
 * @class Renderer
 *
 * @ingroup scene
 * @brief Renderer - class imaging using the active camera selected scene.
 *
 * For description in the configuration:
 @verbatim
   <Renderer name="the name of the scene" order="step of rendering" camera="camera name" context="device context name" input="input device" sort="sort mode"/>
 @endverbatim
 *
 * @see scene
 */

using namespace bt;

class Scene;
class Transform;
class Camera;
class GlContext;

//typedef VoidVector<Transform> SceneTransformsFilter;

class Renderer: public BaseObject {
public:
	MEMDEFAULT(Renderer)

	CSAD_API Renderer(int order,char * name);
	CSAD_API Renderer(int order=0,const char * name="");
	CSAD_API ~Renderer();

	enum MODES {
		/// without sorting
		NOSORT = 0x00000000,
		/// without sorting
		NO = 0x00000000,
		/// sorting objects before drawing the first nearest
		ZUP = 0x00000001,
		/// sorting objects before drawing the first far
		ZDOWN = 0x00000002,
		/// sorting objects before drawing the first parent
		TREE = 0x00000003,
		// отрисовка с учетом двух осей ???
		RENDER_2D = 0x00000020,
		// отрисовка проекции с учетом трех осей ???
		RENDER_3D = 0x00000030,

		NOT_ACTIVE = 0x00000100,
	};

	/// Activate render
	CSAD_API void setActive(bool);
	/// State render action
	_FORCEINLINE bool active() { return (fmode & NOT_ACTIVE)==0;}

	/// To install the active camera
	CSAD_API void setCamera(Camera *camera);
	CSAD_API void setCamera(char *cameraPath);

	CSAD_API Camera* getCamera();

	/// To set the display context
	CSAD_API void setContext(GlContext *context);
	CSAD_API void setContext(char *contextPath);

	CSAD_API GlContext* getContext();

	/// sort mode
	CSAD_API void setSort(unsigned int mode);
	CSAD_API void setSort(char *mode);
	CSAD_API unsigned int getSort();

	/// Sets the active input object.
	CSAD_API void setSelectInput(char*path);
	CSAD_API void setSelectInput(csad::BaseObject*val);

	CSAD_API bool isIntersection(vector2i *global);

	CSAD_API bool draw();
	CSAD_API bool input();
	CSAD_API bool drawRect(vector4i _rect);
	CSAD_API void *select(vector4i _rect);
	CSAD_API void *selectSoft(vector4i _rect);

	CSAD_API void *set(unsigned _int32 ,void *);

	CSAD_API TYPEINFO_H

private:
	bool p_needUpdate;
	unsigned int fmode;
	unsigned int p_sceneChanges;
	unsigned int p_clear;
	Camera *p_camera;
	GlContext *p_context;
	BaseObject *p_input;
	VoidVector<void> p_selected;
	Transform** p_tempfilter;
	// the real number of items to display
	unsigned int p_count;
	// общее количество обьектов в сцене
	unsigned int p_size;
	unsigned int p_selectBuffer[32];

	_int64 cikles_prepare;
	_int64 cikles_nodes;
	_int64 cikles_sort;
	_int64 cikles_fullitem;
	_int64 cikles_inititem;
	_int64 cikles_drawitem;

	void _bindCamera();

	void _draw();
	void _init(int order);
	void _prepareNodes(Camera *camera);
	void _fillFilter(Scene *scene);
	void _validateUpdate(Scene *scene,Camera *camera);

friend class Display;
};

}

#endif /* RENDERER_H_ */
