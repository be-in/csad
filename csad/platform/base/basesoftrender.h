/*
 * basesoftrender.h
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#if defined(CSAD_SOFT_RENDER) || defined(SOFT_RENDER_CSAD)
#ifndef BASE_SOFT_RENDER_H_
#define BASE_SOFT_RENDER_H_

#include <scene/transform.h>
#include <bt.h>

OPTIMIZE_ON;

namespace csad {

struct softDisplay {
	void *obj;
	void *buffer;
	void *colorOffset;
	void *depthOffset;
	int bufferStride;
	int maxx;
	int maxy;
};

struct softGlContextArray {
	unsigned int count;
	unsigned int type;
	int step;
	void *data;
};

struct softGlContext {

	enum softGlContextEnable {
		ALPHA_TEST = 0,
		BLEND = 1,
		LINE_SMOOTH = 2,
		POINT_SMOOTH = 3,
		DEPTH_TEST = 5,
		CULL_FACE = 6,
		COLOR_MATERIAL = 7,
		NORMALIZE = 9,
		SCISSOR_TEST  = 13,
		TEXTURE_1D = 16,
		TEXTURE_2D = 17,
		TEXTURE_3D = 18,
		CLIENT_TEXTURE_COORD_ARRAY = 40,
		CLIENT_COLOR_ARRAY = 41,
		CLIENT_NORMAL_ARRAY = 42,
		CLIENT_VERTEX_ARRAY = 43,
	};

	void *display;
	char enable[8];
	bt::vector4f materialFrontAmbient;
	bt::vector4f materialFrontDiffuse;
	bt::vector4f materialFrontSpecular;
	bt::vector4f materialFrontEmission;
	bt::vector4f materialBackAmbient;
	bt::vector4f materialBackDiffuse;
	bt::vector4f materialBackSpecular;
	bt::vector4f materialBackEmission;
	float materialShininess;
	unsigned int frontface;
	unsigned int cullface;
	bt::vector4b clearColor;
	float clearDepth;
	bt::vector4i scissor;
	bt::vector4i viewPort;
	float depthMin;
	float depthMax;
	unsigned int depthFunc;
	unsigned int depthMask;
	unsigned int alphaFunc;
	unsigned int alphaRef;
	unsigned int blendSrcFactor;
	unsigned int blendDstFactor;
	unsigned int fogMode;
	float pointSize;
	float lineSize;
	bt::vector4f normalDef;
	unsigned int matrixMode;
	unsigned int multyTextId;
	bt::matrix4f model_matrix[16];
	bt::matrix4f proj_matrix[2];
	bt::matrix4f text_matrix[4][2];
	unsigned int modelMatrixStackPos;
	unsigned int projMatrixStackPos;
	unsigned int textMatrixStackPos[4];
	softGlContextArray textArray[4];
	softGlContextArray colorArray;
	softGlContextArray normalArray;
	softGlContextArray vertexArray;
	unsigned int error;
};

using namespace bt;
class GlContext;
class Display;
class Camera;
class MeshFilter;

class SoftRender {
public:
	SoftRender();

	static void _APICALL initialize(GlContext * context);
	static void _APICALL setViewPort(int x,int y,int width,int height);
	static bool _APICALL createContext(Display*,GlContext *);
	static bool _APICALL destroyContext(Display *, GlContext *);
	static void * _APICALL getCurrentContext();
	static bool _APICALL MakeCurrent(Display*,GlContext*);
	static void _APICALL setMatrix(Camera*);
	static void _APICALL setMatrixRect(Camera * camera,bt::vector4i *rect);
	static void _APICALL Buffers(Display * context);

	TYPEINFO_H

private:

	void _APICALL _DrawMesh(MeshFilter *mesh);

};

void _APICALL glAlphaFunc(unsigned int,float);
void _APICALL glBindTexture(unsigned int,unsigned int);
void _APICALL glBlendFunc(unsigned int,unsigned int);
void _APICALL glColor4f(float,float,float,float);
void _APICALL glColor4fv(float*);
void _APICALL glColorPointer(int,unsigned int,int,void*);
void _APICALL glClear(unsigned int);
void _APICALL glClearColor(float,float,float,float);
void _APICALL glClearDepth(double);
void _APICALL glCullFace(unsigned int);
void _APICALL glDeleteTextures(int,void*);
void _APICALL glDepthFunc(unsigned int);
void _APICALL glDisable(unsigned int);
void _APICALL glDisableClientState(unsigned int);
void _APICALL glDrawElements(unsigned int,int,unsigned int,void*);
void _APICALL glEnable(unsigned int);
void _APICALL glEnableClientState(unsigned int);
void _APICALL glFinish();
void _APICALL glFlush();
void _APICALL glGenTextures(int,unsigned int *);
void _APICALL glGetBooleanv(unsigned int,void*);
unsigned int _APICALL glGetError();
void _APICALL glGetFloatv(unsigned int,void*);
void _APICALL glGetIntegerv(unsigned int,void*);
char *_APICALL glGetString(unsigned int id);
void _APICALL glGetTexParameteriv(unsigned int,unsigned int,int *);
void _APICALL glHint(unsigned int,unsigned int);
bool _APICALL glIsEnabled(unsigned int);
void _APICALL glLightModelfv(unsigned int,unsigned int,float*);
void _APICALL glLightfv(unsigned int,unsigned int,float*);
void _APICALL glLineWidth(float);
void _APICALL glLoadIdentity();
void _APICALL glLoadMatrixf(float*);
void _APICALL glMaterialfv(unsigned int,unsigned int,float*);
void _APICALL glMatrixMode(unsigned int);
void _APICALL glMultMatrixf(float*);
void _APICALL glNormalPointer(unsigned int,int,void*);
void _APICALL glPointSize(float);
void _APICALL glPopMatrix();
void _APICALL glPushMatrix();
int _APICALL glRenderMode(unsigned int);
void _APICALL glScalef(float,float,float);
void _APICALL glScissor(int,int,int,int);
void _APICALL glTexCoordPointer(int,unsigned int,int,void*);
void _APICALL glTexImage2D(unsigned int,int,int,int,int,int,unsigned int,unsigned int,void*);
void _APICALL glTexParameteri(unsigned int,unsigned int,unsigned int);
void _APICALL glTexSubImage2D(unsigned int,int,int,int,int,int,unsigned int,unsigned int,void*);
void _APICALL glTranslatef(float,float,float);
void _APICALL glVertexPointer(int,int,int,void*);
void _APICALL glViewport(int,int,int,int);

}

OPTIMIZE_OFF;

#endif /* BASE_SOFT_RENDER_H_ */
#endif
