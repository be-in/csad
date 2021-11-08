/*
 * camera.h
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <bt.h>
#include <scene/scenecomponent.h>
#include <scene/viewport.h>

namespace csad {

WARNING_DISABLE;
OPTIMIZE_ON;

class Scene;
class Transform;
class ViewPort;
class GlContext;

/**
 * @class Camera
 *
 * @ingroup scene
 * @brief Camera - component defines the projection matrix of points Transform into a point Target
 *
 *
 * For description in the configuration:
 @verbatim
   <Transform name="the name of the scene">
       <Camera fov="45" min="near plane" max="far plane" color="back color clean" depth="value for clean" cullface="" viewport="view rect"/>
   </Transform>
 @endverbatim
 *
 * @see Transform, scene
 */

class Camera: public SceneComponent {
public:
	MEMDEFAULT(Camera)

	CSAD_API Camera();

	enum Projection {
		Perspective = 0,
		Ortographic = 1
	};

	//_FORCEINLINE Transform * getTransform() {return getContainer<Transform>();}

	/// Sets the aspect ratio and position of the window in% from the actual size of the context.
	CSAD_API Camera& setViewPort(vector4f *viewport);
	/// Returns the position and dimensions of the window display, in percent.
	CSAD_API vector4f getViewPort();
	/// Returns the position and dimensions of the display window, in pixels.
	CSAD_API vector4i getViewPort(GlContext * context);
	/// Returns the position and dimensions of the display window, in pixels.
	CSAD_API vector4i getViewPort(Display * display);

	CSAD_API bool Intersect(vector2i *pos,GlContext * context);

	/// Specifies the far clipping plane.
	CSAD_API Camera& setMaxRange(double max);
	/// Return distance of far clipping plane.
	_FORCEINLINE double getMaxRange() {return p_max;}

	/// Specifies near clipping.
	CSAD_API Camera& setMinRange(double min);
	/// Return distance of near clipping plane.
	_FORCEINLINE double getMinRange() {return p_min;}

	/// Depending on the model projection sets the angle of view or the frame size.
	CSAD_API Camera& setFov(double _ov);
	/// Return the angle of view or the frame size.
	_FORCEINLINE double getFov() {return p_fov;}

	/// Sets the model projection of this promising (Camera::Perspective) or orthogonal (Camera::Ortographic)
	CSAD_API Camera& setProj(unsigned int proj);
	/// Return model projection.
	_FORCEINLINE unsigned int getProj() {return p_proj;}

	_FORCEINLINE vector4f &getColor() {return p_clearColor;}
	/// Sets the color of the background, automatically includes the background.
	CSAD_API Camera& setColor(float r,float g,float b,float w);
	/// Sets the color of the background, automatically includes the background.
	CSAD_API Camera& setColor(vector4f &color);
	/// Specifies whether frame to have the background, the performance is better off.
	_FORCEINLINE void setClearColor(bool is) {if (((fflag & CLEARCOLOR)!=0)!=is) fflag^=CLEARCOLOR;}
	/// Return true if color frame have the background.
	_FORCEINLINE bool clearColor() {return (fflag & CLEARCOLOR)!=0;}

	/// Sets the value of the depth.
	CSAD_API Camera& setDepth(double val);
	/// Return true if depth frame cleanning before render.
	_FORCEINLINE bool clearDepth() {return (fflag & CLEARDEPTH)!=0;}

	/// set true if need back of front face hide
	_FORCEINLINE void setCullFace(bool is) {if (((fflag & CULLFACE)!=0)!=is) fflag^=CULLFACE;}
	/// return state
	_FORCEINLINE bool cullFace() {return (fflag & CULLFACE)!=0;}

	/// set true if need front face show
	_FORCEINLINE void setFrontFace(bool is) {if (((fflag & FRONTFACE)!=0)!=is) fflag^=FRONTFACE;}
	/// return state
	_FORCEINLINE bool frontFace() {return (fflag & FRONTFACE)!=0;}

	CSAD_API void lookAt(Transform * );
	CSAD_API void lookAt(vector3d & );
	//void lookAt(vector3f & );

	CSAD_API void pointToNormal(vector3f *local,vector3f *normal);

	/// Setting projection matrix.
	CSAD_API bool makeCurrent(unsigned int toTextureId = 0);
	/// Setting projection matrices, and the region's display.
	CSAD_API bool makeCurrent(vector4i &rect,unsigned int toTextureId = 0);

	/// The environment belongs to the camera.
	CSAD_API Scene * getScene();

	/// returns the projection matrix.
	CSAD_API matrix4f *projMatrix();

	_FORCEINLINE static Camera *camera() {return p_default;}

	CSAD_API void *set(unsigned _int32 ,void *);

	/// returns the camera in the specified path.
	CSAD_API static Camera *finder(char *path);

	CSAD_API TYPEINFO_H

private:
	enum Flags{
		CLEARCOLOR = 0x00000001,
		CLEARDEPTH = 0x00000002,
		CULLFACE = 0x00000004,
		FRONTFACE = 0x00000008,
		UPDATEMATRIX = 0x10000000,
	};

	unsigned int fflag;
	/*bool p_isClearColor;
	bool p_isClearDepth;
	bool p_needUpdateMatrix;*/
	ViewPort p_viewPort;
	double p_fov;
	double p_max;
	double p_min;
	unsigned int p_mode;
	float p_clearDepth;
	vector4f p_clearColor;
	unsigned int p_proj;
	matrix4f p_matrix;

	CSAD_API static Camera*p_default;

friend class Scene;
friend class Renderer;
};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* CAMERA_H_ */
