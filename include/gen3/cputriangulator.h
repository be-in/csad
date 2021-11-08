/*
 * cputriangulator.h
 *
 *  Created on: 30.08.2013
 *      Author: Пантелеймонов Александр
 */

#ifndef CPUTRIANGULATOR_H_
#define CPUTRIANGULATOR_H_

#include <bt.h>
#include <platform.h>

OPTIMIZE_ON;

struct GLUtesselator;

namespace gen {

using namespace csad;
using namespace bt;

struct TessData {
	Vector<vector3f> p_vectors;
	Vector<int> p_indexes;
	Vector<int> p_result;
	int c;
	int tri[3];
	int mode;
};

class CPUTriangulator {
public:

	void initialize(vector2i* v,int *counts,int count);
	void initialize(vector2f* v,int *counts,int count);
	void triangulate();

	TessData &getTessData() {return p_tessdata;}

private:
	unsigned int p_count;
	void * p_vectors;
	void * p_type;
	TessData p_tessdata;
	int p_poligons;
	int *p_counts;

	void _vector2iTess(GLUtesselator * tob);
	void _vector2fTess(GLUtesselator * tob);

};

}

OPTIMIZE_OFF;

#endif /* CPUTRIANGULATOR_H_ */
