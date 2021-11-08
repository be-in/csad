/*
 * meshfilter.h
 *
 *  Created on: 16.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef MESHFILTER_H_
#define MESHFILTER_H_

#include <scene/scenecomponent.h>

OPTIMIZE_ON;

namespace csad {

class Mesh;
class VBOMesh;
class BaseMesh;
class Material;
class LightingModel;
class Shader;

/**
 * @class MeshFilter
 *
 * @ingroup scene
 * @brief MeshFilter - a component of a graphical object.
 *
 * The mediator unifying component properties and models of geometry, allowing you to link the object's position with his image, performs the functions of a Manager of a geometry for a given object in the scene.
 *
 @verbatim
   csad::Graph::graph().getScene("MyScene")->getRoot()->addComponent<MeshFilter>()->setMesh( csad::Mesh::Quad() );
 @endverbatim
 *
 * @see scene Mesh Material Shader SceneComponent Transform 
 */

class MeshFilter: public SceneComponent {
public:
	MEMMANAGER(MeshFilter)

	CSAD_API MeshFilter();
	CSAD_API ~MeshFilter();

	/// Return view geometry
	CSAD_API Mesh *getMesh();
	/// Return vbo view geometry
	CSAD_API VBOMesh *getVBOMesh();
	/// Specifies the visible geometry by name
	CSAD_API MeshFilter& setMesh(char *);
	/// Set view geometry
	_FORCEINLINE MeshFilter& setMesh(const char *name) { return setMesh((char*)name);}
	/// Specifies the visible geometry
	CSAD_API MeshFilter& setMesh(BaseMesh *);
	//void setMesh(char *path);

	/// Return used shader
	_FORCEINLINE Shader *getShader() { return fshader; }
	/// Set shader for use
	CSAD_API MeshFilter& setShader(char *);
	/// Set shader for use
	_FORCEINLINE MeshFilter& setShader(const char *name) { return setShader((char*)name); }
	/// Set shader for use
	CSAD_API MeshFilter& setShader(Shader *);

	/// Return used material
	_FORCEINLINE Material* getMaterial() { return fmaterial; }
	/// Set material for use
	CSAD_API MeshFilter& setMaterial(char *);
	/// Set material for use
	_FORCEINLINE MeshFilter& setMaterial(const char *name) { return setMaterial((char*)name); }
	/// Set material for use
	CSAD_API MeshFilter& setMaterial(Material *);

	/// Return used LightingModel
	_FORCEINLINE LightingModel* getLightingModel() { return flightmodel; }
	/// Set LightingModel for use
	CSAD_API MeshFilter& setLightingModel(char *);
	/// Set LightingModel for use
	_FORCEINLINE MeshFilter& setLightingModel(const char *name) { return setLightingModel((char*)name); }
	/// Set LightingModel for use
	CSAD_API MeshFilter& setLightingModel(LightingModel *);

	CSAD_API void *set(unsigned _int32 ,void *);

	CSAD_API TYPEINFO_H

private:
	BaseMesh * fmesh;
	Shader * fshader;
	Material *fmaterial;
	LightingModel *flightmodel;
};

}

OPTIMIZE_OFF;

#endif /* MESHFILTER_H_ */
