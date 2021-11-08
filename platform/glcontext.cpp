/*
 * glcontext.h
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform.h>
#include <scene/viewport.h>
#include <scene/texture2d.h>
#include <scene/mesh.h>
#include <core/graph.h>
#include "csad/core/base/stringconsts.h"

namespace csad {

GlContext *GlContext::p_current=0;

unsigned int GlContext::createTexture2D()
{
	if (makeCurrent()) {
		unsigned int texture;
		ffunctions.GenTextures(1,&texture);
		unsigned int err=ffunctions.GetError();
		if (err) {
#ifdef LOG_CSAD
			Log::console("createTexture2D failed: 0x%x", err);
#endif
			return 0;
		}
		return texture;
	} else return 0;
}

void GlContext::bindTexture2D(unsigned _int32 text)
{
	GLboolean isEnable;
	ffunctions.GetBooleanv(GL_TEXTURE_2D,&isEnable);
	if (!isEnable) ffunctions.Enable(GL_TEXTURE_2D);
	if (GlContext::p_current->p_lasttexture2d!=text) ffunctions.BindTexture(GL_TEXTURE_2D,text);
	GlContext::p_current->p_lasttexture2d=text;
}

unsigned int GlContext::createShaderProg()
{
	if (makeCurrent()) {
		unsigned int prog=ffunctions.CreateProgram();
		if (prog==0) {
			unsigned int err = ffunctions.GetError();
#ifdef LOG_CSAD
			Log::console("createTexture2D failed: 0x%x", err);
#endif
			return 0;
		}
		return prog;
	} else return 0;
}

void GlContext::bindShaderProg(unsigned _int32 prog)
{
	if (GlContext::p_current->p_lastshaderprog != prog) ffunctions.UseProgram(prog);
	GlContext::p_current->p_lastshaderprog = prog;
	_int32 err = ffunctions.GetError();
	if (err) {
#ifdef LOG_CSAD
		Log::console("GlContext::bindShaderProg 0x%x", err);
#endif
	}
}

BaseMesh * GlContext::getVBOMesh(BaseMesh *mesh)
{
	if (!mesh) return 0;
	if (mesh->getMesh()!=mesh) return 0;
	VBOMesh *vboMesh=(VBOMesh *)p_vboMesh.find(mesh);
	if (vboMesh) return vboMesh;
	return mesh;
}

void GlContext::freeVBOMesh(BaseMesh *mesh)
{
	if (!mesh) return;
	Mesh*lm=mesh->getMesh();
	VBOMesh*vbo=(VBOMesh*)mesh;
	if (lm!=mesh) {
		if (p_vboMesh.remove(lm)!=0)
			delete vbo;
	}
}

void GlContext::setExtentions(bool val)
{
	if (val) ffunctions.extensionsFlag=0xFFFFFFFF;
	if (!val) ffunctions.extensionsFlag=0x0;
}

void * GlContext::set(unsigned _int32 id,void *param)
{
	if (id==BaseObject::TYPE) return GlContext::t();
	if (id==BaseObject::WRITE) {
		Variant *p;
		ParametersList *list=(ParametersList *)param;
		if ((p=list->find(STR_COLOR))!=0) setColor(p->getVector4f());
		if ((p=list->find("extentions"))!=0) setExtentions(p->getBool());
		//if ((p=list->find("vb"))!=0) setVB(p->getBool());
	}
	return 0;
}

GlContext *GlContext::finder(char *path)
{
	ObjectManager::Finder find(path);
	Display *display=Graph::graph().getDisplay(find.getNext());
	if (!display) {
#ifdef LOG_CSAD
		Log::console("Can`t find display: %s",find.getNext());
#endif
		return 0;
	}
	find.next();
	GlContext *context=display->getContext(find.getNext());
	if (!context) {
#ifdef LOG_CSAD
		Log::console("Can`t find context: %s",find.getNext());
#endif
		return 0;
	}
	find.next();
	return context;
}

TYPEINFO(GlContext)

}

OPTIMIZE_OFF;