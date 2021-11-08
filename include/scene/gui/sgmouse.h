/*
 * sgmouse.h
 *
 *  Created on: 19.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef SGMOUSE_H_
#define SGMOUSE_H_

#include <scene/scenecomponent.h>
#include <bt.h>

namespace csad {

class Mesh;
class Material;
class Camera;
class Display;

/**
 * @class SGMouse
 *
 * @ingroup scenegui
 * @brief SGMouse - component, mouse event handlers
 *
 * For description in the configuration:
 @verbatim
   <Scene name="myMouseScene">
     <Transform>
	   <SGMouse speed="1"/>
     </Transform>
   </Scene>
 @endverbatim
 *
 * @see scenegui, SGMouseMesh, Style, TextStyle, SGButtonStyle, BaseObject
 */

class SGMouse: public SceneComponent {
public:
	MEMDEFAULT(SGMouse)

	CSAD_API SGMouse();

	/// Sets the zoom speed.
	/// For the orthogonal projection size camera 1.0, direct correspondence screen coordinates speed reverse the height of the screen in pixels.
	CSAD_API void setZoom(float scale);
	_FORCEINLINE float getZoom() { return p_XYscale; }

	CSAD_API void prepare();

	CSAD_API void * set(unsigned _int32, void *);

	CSAD_API static bt::vector3f normal(Display *display,Camera *camera);

	CSAD_API TYPEINFO_H

private:
	float p_XYscale;

};

/**
 * @class SGMouseMesh
 *
 * @ingroup scenegui
 * @brief SGMouseMesh - component, geometrical model of the pointer
 *
 * For description in the configuration:
 @verbatim
   <Scene name="myMouseScene">
     <Transform>
	   <SGMouse speed="1"/>
	   <SGMouseMesh material="" linematerial=""/>
     </Transform>
   </Scene>
 @endverbatim
 *
 * @see scenegui, SGMouse, Style, TextStyle, SGButtonStyle, BaseObject
 */

class SGMouseMesh: public SceneComponent {
public:
	MEMDEFAULT(SGMouse)

	CSAD_API SGMouseMesh();

	/// Setting material for mouse geometry
	CSAD_API void setMaterial(char *name);
	/// Setting material for mouse line geometry
	CSAD_API void setLineMaterial(char *name);

	CSAD_API void start();
	CSAD_API void prepare();
	CSAD_API void quit();

	CSAD_API void * set(unsigned _int32, void *);

	CSAD_API TYPEINFO_H

private:
	Material *p_material;
	Material *p_linematerial;
	Mesh *fline;
	Transform *ftrline;

	void _buildMesh(Mesh *mesh,Mesh *linemesh);
};

}

#endif /* SGMOUSE_H_ */
