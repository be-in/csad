/*
 * modelermesh.h
 *
 *  Created on: 17.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef MODELLERMESH_H_
#define MODELLERMESH_H_

#include <bt.h>
#include <gen3/genapi.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

class Mesh;
class TextStyle;

}

namespace gen {

using namespace csad;
using namespace bt;

/*
struct glMesh {
	unsigned int p_drawFormat;
	unsigned int p_elementFormat;
	unsigned int p_indexCount;
	unsigned int p_elementCount;
	unsigned char *p_index;
	unsigned char *p_elements;
};*/

class GeometryPath2F;

/**
 * @class ModellerMesh
 *
 * @ingroup generator
 * @brief ModellerMesh - методы моделирования трехмерной полигональной модели.
 *
 * @see generator
 */

class ModellerMesh {
public:
	GEN_API ModellerMesh();
	GEN_API ~ModellerMesh();

	/// Добавляет массив вершин
	/// @param mesh - контейнер модели.
	GEN_API void setMesh(Mesh* mesh);
	/// Задает режим смешивания
	/// @param mode - режим.
	GEN_API void setMode(unsigned int mode);
	/// Задает матрицу трансформации по смещению развороту и масштабу.
	GEN_API void TRS(vector3d *pos,quaterniond *rot,vector3f *scale);
	/// Добавляет смещение к матрице трансформации.
	GEN_API void addTranslate(vector3d *pos);
	/// Добавляет смещение к матрице трансформации.
	GEN_API void addTranslate(double x,double y,double z);
	/// Добавляет разворок к матрице трансформации.
	GEN_API void addRotation(quaterniond *rot);
	/// Добавляет масштаб к матрице трансформации.
	GEN_API void addScale(vector3f *scale);
	/// устанавливает единичную матрицу трансформации.
	GEN_API void resetMatrix();
	/// смещает имеющиеся вершины
	GEN_API void Translate(vector3d *pos);
	/// разварачивает имеющиеся вершины
	GEN_API void Rotate(vector3d *rot);
	/// масштабирует имеющиеся вершины
	GEN_API void Scale(vector3f *scale);
	/// трансформирует вершины согласно матрице трансформации.
	/// @param from - первая вершина.
	/// @param from - количество модифицируемых вершин.
	GEN_API void Transform(unsigned int from,unsigned int count );

	/// Задает модификатор цвета вершин
	GEN_API void setColor(unsigned int color);
	/// Задает модификатор цвета вершин
	GEN_API void setColor(vector4f *color);
	/// Задает модификатор цвета вершин
	GEN_API void setColor(float b,float g,float r,float a);

	/// Внутреннее копирование индексов
	GEN_API void copyIndex(Mesh* mesh,unsigned int at,unsigned int from,unsigned int count,int off);
	/// Внутреннее копирование вершин
	GEN_API void copyVertex(Mesh* mesh,unsigned int at,unsigned int from,unsigned int count);

	/// Добавляет массив вершин
	/// @param arr - масивв вершин.
	/// @param from - первый элемент массива.
	/// @param count - количество добвляемых элементов.
	GEN_API void addArray(Vector<vector2i> * arr,unsigned int from=0,unsigned int count=0);
	/// Добавляет массив вершин
	/// @param arr - масивв вершин.
	/// @param from - первый элемент массива.
	/// @param count - количество добвляемых элементов.
	GEN_API void addArray(Vector<vector2f> * arr,unsigned int from=0,unsigned int count=0);
	/// Добавляет массив вершин
	/// @param arr - масивв вершин.
	/// @param from - первый элемент массива.
	/// @param count - количество добвляемых элементов.
	GEN_API void addArray(Vector<vector3f> * arr,unsigned int from=0,unsigned int count=0);

	GEN_API void setTextures(Vector<vector2f> * arr,unsigned int from=0,unsigned int count=0);

	GEN_API void setColor(unsigned int from,unsigned int count);

	/// Добавляет результат тесселяции
	GEN_API void addByTess(void * tess);

	//void triangle(float width,float height,float bsmooth=0);
	/// Моделирует квадрат.
	/// @param width - ширина.
	/// @param height - высота.
	/// @param bsmooth - размер обводки для сглаживания (antialiasing).
	GEN_API void quad(float width,float height,float bsmooth=0);
	/// Моделирует круг или секцию круга.
	/// @param radius - радиус.
	/// @param cells - количество шагов по окружности.
	/// @param start - начальный граус.
	/// @param end - конечный граус.
	GEN_API void circle(float radius,unsigned int cells,float start=0,float end=0);
	/// Моделирует сферу.
	GEN_API void sphere(float radius,unsigned int wcells,unsigned int hcells);
	/// Моделирует обводку круга или отрезок окружности.
	/// @param radius - радиус.
	/// @param width - ширина обводки.
	/// @param cells - количество шагов по окружности.
	/// @param start - начальный граус.
	/// @param end - конечный граус.
	/// @param bsmooth - размер обводки для сглаживания (antialiasing).
	GEN_API void strokedCircle(float radius,float width,unsigned int cells,float start=0.0f,float end=0.0f,float bsmooth=0);
	/// Моделирует линию заданной толщины согласно пути.
	/// @param path - путь.
	/// @param width - толщина линии.
	/// @param offset - смещение линии от центра.
	GEN_API void stroker(GeometryPath2F *path,float width,float offset);
	/// Заливка по форме.
	/// @param path - форма заливки.
	/// @param bsmooth - размер обводки для сглаживания (antialiasing).
	GEN_API void fill(GeometryPath2F *path,float bsmooth=0);
	/// Текстурный текст.
	GEN_API void textTexture(char *text,TextStyle *style,float z);
	/// Плоский текст.
	GEN_API void textFlat(char *text,TextStyle *style,float z,float bsmooth=0);
	/// Вытянутый объемный текст.
	GEN_API void textExtrude(char *text,TextStyle *style,float z,float extrude=0);
	//void strokedSection(float radius,float width,unsigned int cells,float start,float end);
private:
	unsigned int p_mode;
	matrix4d p_matrix;
	Mesh *p_mesh;
	char *p_vector;
	vector4f p_color;
	unsigned int p_step;
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* MODELERMESH_H_ */
