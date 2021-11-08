/*
 * mesh.h
 *
 *  Created on: 13.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef Mesh_H_
#define Mesh_H_

#include <bt.h>
#include <core/csadapi.h>
#include <core/baseobject.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace gen {

class ModellerMesh;

}

namespace csad {

using namespace bt;
using namespace gen;

class Mesh;
class VBOMesh;
class GlContext;

/**
 * @class BaseMesh
 *
 * @ingroup scene
 * @brief BaseMesh - abstract class geometry
 *
 * @see scene
 *
 */

class BaseMesh {
public:
	MEMNULL

	virtual ~BaseMesh() {}

	virtual Mesh * getMesh() = 0;
	virtual VBOMesh * getVBOMesh() = 0;
};

/**
 * @class Mesh
 *
 * @ingroup scene
 * @brief Mesh - geometric container sets vertex model object. Tops in its composition can have the following characteristics: position, color, vector front, texture coordinates.
 *
 * @see scene MeshFilter StaticMesh VBOMesh
 *
 *
 */

class Mesh: public BaseMesh {
public:
	MEMMANAGER(Mesh)

	CSAD_API Mesh(char* name);
	CSAD_API Mesh(const char* name="");
	CSAD_API ~Mesh();

	/// to install the vertex format
	CSAD_API Mesh& setFields(unsigned int attr);
	_FORCEINLINE unsigned int getIndexSize() { return _indexSize(p_drawFormat); }
	/// The type of the field of coordinate geometry, if the field is missing returns 0.
	/// @return _TGL_V2F, _TGL_V3F, _TGL_V4F, _TGL_V2D, _TGL_V3D, _TGL_V4D.
	CSAD_API unsigned int getVectorType();
	/// returns the color format of vertices: float[3] float[4]
	CSAD_API unsigned int getColorType();
	/// The field type of texture coordinates, if the field is missing returns 0.
	/// @param id - индекс слоя текстурных координат.
    /// @return _TGL_0T1F, _TGL_0T2F, _TGL_0T3F, _TGL_0T4F.
	CSAD_API unsigned int getTexType(int id);
	/// returns true if the vertices contains the vector of the front
	CSAD_API bool isNormal();
	_FORCEINLINE unsigned int getFields() {return p_elementFormat;}

	/// Sets the number of elements vertex buffer, the previous value of vertices is not saved
	CSAD_API Mesh& setVertexCount(unsigned int count);
	/// Sets the number of indexes, the previous value of the index is not saved
	CSAD_API Mesh& setIndexCount(unsigned int count);

	/// Changes the number of elements, preserving the values at the end of the array
	CSAD_API Mesh& resizeVertex(unsigned int count);
	/// Changes the number of indexes, preserving the values at the end of the array
	CSAD_API Mesh& resizeIndex(unsigned int count);

	/*enum AtributeType
	{
		AT_NONE,
		AT_VECTOR2F,
		AT_VECTOR2D,
		AT_VECTOR3F,
		AT_VECTOR3D,
		AT_VECTOR4F,
		AT_VECTOR4D,
		AT_TEXTURE1F,
		AT_TEXTURE2F,
		AT_TEXTURE3F,
		AT_TEXTURE4F,
		AT_NORMAL3F,
		AT_COLOR3F,
		AT_COLOR4F,
	};*/

	/// the types of fields of geometry
	enum stFormat {
		/// two-dimensional coordinates single-precision
		_TGL_V2F = 0x00000001,
		/// three-dimensional coordinates of single-precision
		_TGL_V3F = 0x00000002,
		_TGL_V4F = 0x00000003,
		/// two-dimensional double-precision coordinates
		_TGL_V2D = 0x00000004,
		/// three-dimensional double-precision coordinates
		_TGL_V3D = 0x00000005,
		_TGL_V4D = 0x00000006,
		/// three-dimensional normal single-precision
		_TGL_N3F = 0x00000008,
		/// coordinate single precision first layer by odnomernoi textures
		_TGL_0T1F = 0x00000010,
		/// coordinate single precision first layer of two-dimensional texture
		_TGL_0T2F = 0x00000020,
		_TGL_0T3F = 0x00000030,
		_TGL_0T4F = 0x00000040,
		_TGL_1T1F = 0x00000100,
		_TGL_1T2F = 0x00000200,
		_TGL_1T3F = 0x00000300,
		_TGL_1T4F = 0x00000400,
		_TGL_2T1F = 0x00001000,
		_TGL_2T2F = 0x00002000,
		_TGL_2T3F = 0x00003000,
		_TGL_2T4F = 0x00004000,
		_TGL_3T1F = 0x00010000,
		_TGL_3T2F = 0x00020000,
		_TGL_3T3F = 0x00030000,
		_TGL_3T4F = 0x00040000,
		_TGL_4T1F = 0x00100000,
		_TGL_4T2F = 0x00200000,
		_TGL_4T3F = 0x00300000,
		_TGL_4T4F = 0x00400000,
		_TGL_5T1F = 0x01000000,
		_TGL_5T2F = 0x02000000,
		_TGL_5T3F = 0x03000000,
		_TGL_5T4F = 0x04000000,
		/// цвет RGB
		_TGL_C3F = 0x10000000,
		/// цвет RGBA
		_TGL_C4F = 0x20000000
	};

	/// field vertex geometry.
	enum stItem {
		/// field texture coordinates of the first layer
		_TEXTURE0 = 0,
		/// field texture coordinates of the second layer
		_TEXTURE1 = 1,
		/// field texture coordinates of the third layer
		_TEXTURE2 = 2,
		///
		_TEXTURE3 = 3,
		///
		_TEXTURE4 = 4,
		///
		_TEXTURE5 = 5,
		/// color box
		_COLOR = 6,
		/// field surface
		_NORMAL = 7,
		/// field of coordinatearea
		_VECTOR = 8
	};

	/// the format of building geometry.
	enum stDrawFormat {
		/// вершина интерпретируется как отдельная точка.
		_GL_POINTS = 0x000,
		/// пара вершин интерпретируются как линия.
		_GL_LINES = 0x001,
		/// каждая вершина участвует в построении замкнутой линейной фигуры.
		_GL_LINE_LOOP = 0x002,
		/// каждая вершина участвует в построении не замкнутой линейной фигуры.
		_GL_LINE_STRIP = 0x003,
		/// каждые три вершины задают треугольник.
		_GL_TRIANGLES = 0x004,
		/// треугольник производится из двух предыдущий вершин и текущей.
		_GL_TRIANGLE_STRIP = 0x005,
		/// каждая вершина строит треугольник к предыдущей грани треугольника или первой пары вершин, все треугольники имеют общую первую вершину.
		_GL_TRIANGLE_FAN = 0x006,
		/// каждые четыре вершины задают пару смежных треугольников.
		_GL_QUADS = 0x007,
		/// 
		_GL_QUAD_STRIP = 0x008,
		/// замкнутый полигон разделяется индексами -1
		_GL_POLYGON = 0x009,
		/// glIndexSize
		_GL_INDEX_BYTE = 0x01000000,
		_GL_INDEX_WORD = 0x02000000,
		_GL_INDEX_DWORD = 0x04000000,
		/// буфер индекса требует обновления на устройстве
		_GL_NEED_INDEX_UPDATE = 0x10000000,
		/// буфер вершин требует обновления на устройстве
		_GL_NEED_ELEMENT_UPDATE = 0x20000000,
		_GL_MASK = 0x0000FFFF,
		_GL_INDEX_MASK = 0x0F000000
	};

	/// задает тип геометри
	CSAD_API Mesh& setDrawFormat(stDrawFormat attr);
	/// former rendering
	_FORCEINLINE stDrawFormat getDrawFormat() {return (stDrawFormat)(p_drawFormat&_GL_MASK);}
	/// елементы геометрии
	_FORCEINLINE unsigned char* &elements() {return p_elements;}
	_FORCEINLINE unsigned char* &indexs() {return p_index;}

	template <typename T>
	/// An array of texture coordinates
	_FORCEINLINE LinkArray<T> texture0() {return LinkArray<T>((void*)_startElement(this,0,_TEXTURE0),0,_elementSize(p_elementFormat),&p_elementCount);}
	template <typename T>
	/// An array of texture coordinates
	_FORCEINLINE LinkArray<T> texture1() {return LinkArray<T>((void*)_startElement(this,0,_TEXTURE1),0,_elementSize(p_elementFormat),&p_elementCount);}
	template <typename T>
	/// Array normals
	_FORCEINLINE LinkArray<T> normal() {return LinkArray<T>((void*)_startElement(this,0,_NORMAL),0,_elementSize(p_elementFormat),&p_elementCount);}
	template <typename T>
	/// The array of vertices color
	_FORCEINLINE LinkArray<T> color() {return LinkArray<T>((void*)_startElement(this,0,_COLOR),0,_elementSize(p_elementFormat),&p_elementCount);}
	template <typename T>
	/// The array of vertices positions
	_FORCEINLINE LinkArray<T> vector() {return LinkArray<T>((void*)_startElement(this,0,_VECTOR),0,_elementSize(p_elementFormat),&p_elementCount);}
	template <typename T>
	/// The array of vertices
	_FORCEINLINE LinkArray<T> vertex() {return LinkArray<T>((void*)p_elements,0,_elementSize(p_elementFormat),&p_elementCount);}
	template <typename T>
	/// Array indexes
	_FORCEINLINE LinkArray<T> index() {return LinkArray<T>((void*)p_index,0,_indexSize(p_drawFormat),&p_indexCount);}

	/// The size element
	_FORCEINLINE unsigned int elementSize() {return _elementSize(p_elementFormat);}

	/// value of index
	CSAD_API int indexById(unsigned int id);

	/// installing index
	CSAD_API Mesh& setIndex(unsigned int i,int val);
	/// slow installation vertix
	CSAD_API Mesh& setVector(unsigned int i,float *v);
	/// slow installation vertix
	CSAD_API Mesh& setVector(unsigned int i,double *v);

	/// installation of two indexess in a row
	CSAD_API Mesh& setIndexLine(unsigned int i,unsigned int a,unsigned int b);
	/// installation of three indexes in a row
	CSAD_API Mesh& setIndexTri(unsigned int i,unsigned int a,unsigned int b,unsigned int c);
	/// installation of four indexes in a row
	CSAD_API Mesh& setIndexQuad(unsigned int i,unsigned int a,unsigned int b,unsigned int c,unsigned int d);

	/// returns the number of indexes
	_FORCEINLINE unsigned int indexCount() {return p_indexCount;}
	/// returns the number of vertices
	_FORCEINLINE unsigned int elementsCount() {return p_elementCount;}

	/// specifies the zero index elements
	CSAD_API void cleanIndex(int from,int count);

	/// returns a sector describing the cube in which pomeshaetsa geometry
	_FORCEINLINE vector4d &getBoundSphere() {return p_bound;}
	/// preset sphere describing cube
	CSAD_API vector3d calculateBound();
	/// recalculate normals
	CSAD_API void calculateNormals();

	//_FORCEINLINE LincArray<T> index() {return LincArray<T>((void*)_startElement(this,0,_VECTOR),0,_elementSize(p_elementFormat),&p_elementCount);}

	_FORCEINLINE Mesh * getMesh() {return this;}
	_FORCEINLINE VBOMesh * getVBOMesh() {return 0;}

	_FORCEINLINE void fixed() {p_drawFormat&=_GL_MASK+_GL_INDEX_MASK;}
	/// the next drawing geometry updated on the device
	_FORCEINLINE void update() {p_drawFormat|=_GL_NEED_INDEX_UPDATE|_GL_NEED_ELEMENT_UPDATE;}
	/// the next drawing vertex geometry updated on the device
	_FORCEINLINE void updateVertex() {p_drawFormat|=_GL_NEED_ELEMENT_UPDATE;}

	/// Геометрия квадрата
	CSAD_API static Mesh* Quad;
	/// Геометрия куба
	CSAD_API static Mesh* Cube;

	CSAD_API static unsigned int combineFilds(Mesh *,Mesh *);

	class CSAD_API MeshQuad {
	public:
		TYPEINFO_H
	};
	class CSAD_API MeshCube {
	public:
		TYPEINFO_H
	};
	class CSAD_API MeshSphere {
	public:
		TYPEINFO_H
	};

	TYPEINFO_H

protected:
	unsigned int p_drawFormat;
	unsigned int p_elementFormat;
	unsigned int p_indexCount;
	unsigned int p_elementCount;
	unsigned char *p_index;
	unsigned char *p_elements;
	vector4d p_bound;

	void _init();

	CSAD_API static unsigned int _indexSize(unsigned int drawformat);
	CSAD_API static unsigned int _elementSize(unsigned int format);
	CSAD_API static unsigned int _elementSize(unsigned int format,unsigned int i);
	CSAD_API static unsigned int _elementSubCount(unsigned int format, unsigned int it);
	CSAD_API static char * _startElement(Mesh *mesh,unsigned int offset, unsigned int it);

friend class Render;
friend class gen::ModellerMesh;
};

/**
 * @class StaticMesh
 *
 * @ingroup scene
 * @brief StaticMesh - the class is static geometry.
 *
 * @see scene
 *
 */

class StaticMesh: public Mesh {
public:
	MEMNULL

	CSAD_API StaticMesh(unsigned char * index,unsigned int indexCount,unsigned char*elements,unsigned int elemCount,unsigned int draw,unsigned int format);
	CSAD_API ~StaticMesh();
};

/**
 * @class VBOMesh
 *
 * @ingroup scene
 * @brief VBOMesh - class geometry of the device.
 *
 * Provides support for virtual buffer to store the geometry on the graphics device.
 *
 * @see scene
 *
 */

class VBOMesh: public BaseMesh {
public:
	MEMMANAGER(VBOMesh)

	VBOMesh(BaseMesh * mesh);
	~VBOMesh();

	Mesh * getMesh() {return (Mesh *)p_mesh;}
	VBOMesh * getVBOMesh() {return this;}

	/// identifier indexes
	unsigned int index;
	/// identifier array elements
	unsigned int elements;
	GlContext *context;

	TYPEINFO_H

private:
	BaseMesh * p_mesh;

};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* Mesh_H_ */
