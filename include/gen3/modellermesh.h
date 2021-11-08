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
 * @brief ModellerMesh - ������ ������������� ���������� ������������� ������.
 *
 * @see generator
 */

class ModellerMesh {
public:
	GEN_API ModellerMesh();
	GEN_API ~ModellerMesh();

	/// ��������� ������ ������
	/// @param mesh - ��������� ������.
	GEN_API void setMesh(Mesh* mesh);
	/// ������ ����� ����������
	/// @param mode - �����.
	GEN_API void setMode(unsigned int mode);
	/// ������ ������� ������������� �� �������� ��������� � ��������.
	GEN_API void TRS(vector3d *pos,quaterniond *rot,vector3f *scale);
	/// ��������� �������� � ������� �������������.
	GEN_API void addTranslate(vector3d *pos);
	/// ��������� �������� � ������� �������������.
	GEN_API void addTranslate(double x,double y,double z);
	/// ��������� �������� � ������� �������������.
	GEN_API void addRotation(quaterniond *rot);
	/// ��������� ������� � ������� �������������.
	GEN_API void addScale(vector3f *scale);
	/// ������������� ��������� ������� �������������.
	GEN_API void resetMatrix();
	/// ������� ��������� �������
	GEN_API void Translate(vector3d *pos);
	/// ������������� ��������� �������
	GEN_API void Rotate(vector3d *rot);
	/// ������������ ��������� �������
	GEN_API void Scale(vector3f *scale);
	/// �������������� ������� �������� ������� �������������.
	/// @param from - ������ �������.
	/// @param from - ���������� �������������� ������.
	GEN_API void Transform(unsigned int from,unsigned int count );

	/// ������ ����������� ����� ������
	GEN_API void setColor(unsigned int color);
	/// ������ ����������� ����� ������
	GEN_API void setColor(vector4f *color);
	/// ������ ����������� ����� ������
	GEN_API void setColor(float b,float g,float r,float a);

	/// ���������� ����������� ��������
	GEN_API void copyIndex(Mesh* mesh,unsigned int at,unsigned int from,unsigned int count,int off);
	/// ���������� ����������� ������
	GEN_API void copyVertex(Mesh* mesh,unsigned int at,unsigned int from,unsigned int count);

	/// ��������� ������ ������
	/// @param arr - ������ ������.
	/// @param from - ������ ������� �������.
	/// @param count - ���������� ���������� ���������.
	GEN_API void addArray(Vector<vector2i> * arr,unsigned int from=0,unsigned int count=0);
	/// ��������� ������ ������
	/// @param arr - ������ ������.
	/// @param from - ������ ������� �������.
	/// @param count - ���������� ���������� ���������.
	GEN_API void addArray(Vector<vector2f> * arr,unsigned int from=0,unsigned int count=0);
	/// ��������� ������ ������
	/// @param arr - ������ ������.
	/// @param from - ������ ������� �������.
	/// @param count - ���������� ���������� ���������.
	GEN_API void addArray(Vector<vector3f> * arr,unsigned int from=0,unsigned int count=0);

	GEN_API void setTextures(Vector<vector2f> * arr,unsigned int from=0,unsigned int count=0);

	GEN_API void setColor(unsigned int from,unsigned int count);

	/// ��������� ��������� ����������
	GEN_API void addByTess(void * tess);

	//void triangle(float width,float height,float bsmooth=0);
	/// ���������� �������.
	/// @param width - ������.
	/// @param height - ������.
	/// @param bsmooth - ������ ������� ��� ����������� (antialiasing).
	GEN_API void quad(float width,float height,float bsmooth=0);
	/// ���������� ���� ��� ������ �����.
	/// @param radius - ������.
	/// @param cells - ���������� ����� �� ����������.
	/// @param start - ��������� �����.
	/// @param end - �������� �����.
	GEN_API void circle(float radius,unsigned int cells,float start=0,float end=0);
	/// ���������� �����.
	GEN_API void sphere(float radius,unsigned int wcells,unsigned int hcells);
	/// ���������� ������� ����� ��� ������� ����������.
	/// @param radius - ������.
	/// @param width - ������ �������.
	/// @param cells - ���������� ����� �� ����������.
	/// @param start - ��������� �����.
	/// @param end - �������� �����.
	/// @param bsmooth - ������ ������� ��� ����������� (antialiasing).
	GEN_API void strokedCircle(float radius,float width,unsigned int cells,float start=0.0f,float end=0.0f,float bsmooth=0);
	/// ���������� ����� �������� ������� �������� ����.
	/// @param path - ����.
	/// @param width - ������� �����.
	/// @param offset - �������� ����� �� ������.
	GEN_API void stroker(GeometryPath2F *path,float width,float offset);
	/// ������� �� �����.
	/// @param path - ����� �������.
	/// @param bsmooth - ������ ������� ��� ����������� (antialiasing).
	GEN_API void fill(GeometryPath2F *path,float bsmooth=0);
	/// ���������� �����.
	GEN_API void textTexture(char *text,TextStyle *style,float z);
	/// ������� �����.
	GEN_API void textFlat(char *text,TextStyle *style,float z,float bsmooth=0);
	/// ��������� �������� �����.
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
