/*
 * modellerpath.h
 *
 *  Created on: 17.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef MODELLERPATH_H_
#define MODELLERPATH_H_

#include <gen3/genapi.h>
#include <bt.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace gen {

using namespace csad;
using namespace bt;

template <typename T>

struct sGeometryPath {
	Vector<T> p_pointers;
	Vector<unsigned _int32> p_count;
};

typedef Vector<vector2i> ListVector2I;
typedef Vector<vector2f> ListVector2F;
typedef Vector<int> ListPoligonSize;

template <typename T>

/**
 * @class GeometryPath
 *
 * @ingroup generator
 * @brief GeometryPath - Список групп.
 *
 * @see generator
 */

class GeometryPath {
public:
	MEMDEFAULT(GeometryPath)

	_FORCEINLINE GeometryPath() {}
	_FORCEINLINE ~GeometryPath() {}

	/// returns the total number of vertices
	_FORCEINLINE unsigned int count() {return p_pointers.count();}
	/// добавить вершину
	_FORCEINLINE void addVector(const T &vec,bool isNew=false) {
		p_pointers.assign(vec);
		if (isNew || (p_count.count()==0)) {
			p_count.assign(1);
		} else {
			p_count.last()++;
		}
	}

	/// очистка
	_FORCEINLINE void clear() {p_pointers.clear();p_count.clear();}
	/// returns a list of all vertices.
	_FORCEINLINE Vector<T> &vectors() {return p_pointers;}
	/// returns the number of vertices in groups.
	_FORCEINLINE ListPoligonSize &poligonSize() {return p_count;}

private:
	Vector<T> p_pointers;
	ListPoligonSize p_count;
};

class GeometryPath2F;

class GeometryPath2I {
public:
	MEMDEFAULT(GeometryPath)

	GEN_API GeometryPath2I();
	GEN_API GeometryPath2I(GeometryPath2F &path);
	GEN_API ~GeometryPath2I();

	GEN_API void absorb(sArray *pointers,sArray *counts);

	_FORCEINLINE gen::GeometryPath<bt::vector2i>& geometry() { return *((gen::GeometryPath<bt::vector2i>*)this); }

private:
	sArray p_pointers;
	sArray p_count;
};

class GeometryPath2F {
public:
	MEMDEFAULT(GeometryPath)

	GEN_API GeometryPath2F();
	GEN_API GeometryPath2F(GeometryPath2I &path);
	GEN_API ~GeometryPath2F();

	_FORCEINLINE void addVector(float x,float y,bool iNew=false) { geometry().addVector(bt::vector2f(x,y),iNew); }
	GEN_API void addBox(float width,float height,vector2f &offset,float deg);
	GEN_API void addCircle(float radius,int cells,float from,float to,vector2f &offset);
	GEN_API void addStrokedCircle(float radius,float width,int cells,float from,float to,vector2f &offset);

	GEN_API void absorb(sArray *pointers,sArray *counts);

	_FORCEINLINE gen::GeometryPath<bt::vector2f>& geometry() { return *((gen::GeometryPath<bt::vector2f>*)this); }

private:
	sArray p_pointers;
	sArray p_count;
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* MODELLERPATH_H_ */
