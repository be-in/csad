/*
 * osxglcontext.h
 *
 *  Created on: 14.08.2013
 *      Author: Пантелеймонов Александр
 */

#include <platform/platformapi.h>

#if defined (OS_OSX)

#include <platform.h>
#include <scene/viewport.h>
#include <scene/texture2d.h>
#include <scene/mesh.h>
#include <core/graph.h>
#include "linuxglextention.h"
#include "csad/platform/localdisplay.h"

OPTIMIZE_ON;

namespace csad {

	GlContext::GlContext(Display * parent,char *name)
	{
		p_lastmaterial=0;
		p_context=new Context_P();
		p_parent=(Display *)parent;
		((LocalDisplay*)p_parent)->p_context.addObject(this,name);
	}

	GlContext::GlContext(Display *parent,const char *name)
	{
		p_lastmaterial=0;
		p_context=new Context_P();
		p_parent=(Display * )parent;
		((LocalDisplay*)p_parent)->p_context.addObject(this,name);
	}

	GlContext::~GlContext()
	{
		BaseMapVoid::iterator it = p_vboMesh.begin();
		BaseMapVoid::iterator end = p_vboMesh.end();

		while (it!=end) {
			delete (VBOMesh*)it.value();
			it++;
		}
		p_vboMesh.clear();

		((LocalDisplay*)p_parent)->p_context.detachObject(this);
		if (p_context) delete p_context;
		p_context=0;
	}

	unsigned int GlContext::createTexture2D()
	{
		makeCurrent();
		unsigned int texture;
		Render::GenTextures(1,&texture);
		return texture;
	}

	BaseMesh * GlContext::createVBOMesh(BaseMesh *mesh)
	{
		if (!mesh) return 0;
		if (mesh->getMesh()!=mesh) return 0;
		VBOMesh *vboMesh=(VBOMesh *)p_vboMesh._find(mesh);
		if (vboMesh) return vboMesh;
		vboMesh=new VBOMesh(mesh);
		void *&p=p_vboMesh._findornew(mesh);
		p=vboMesh;
		return vboMesh;
	}

	BaseMesh * GlContext::getVBOMesh(BaseMesh *mesh)
	{
		if (!mesh) return 0;
		if (mesh->getMesh()!=mesh) return 0;
		VBOMesh *vboMesh=(VBOMesh *)p_vboMesh._find(mesh);
		if (vboMesh) return vboMesh;
		return mesh;
	}

	void GlContext::freeVBOMesh(BaseMesh *mesh)
	{
		if (!mesh) return;
		if (mesh->getMesh()!=mesh) {
			if (p_vboMesh.remove(mesh)>=0) delete mesh;
		}
	}

	void GlContext::setColor(vector4f &color)
	{
		makeCurrent();
		glClearColor(color.x,color.y,color.z,color.w);
		/*glClear(GL_COLOR_BUFFER_BIT);
		p_parent->swapBuffers();
		glClear(GL_COLOR_BUFFER_BIT);
		p_parent->swapBuffers();*/
	}

	Display * GlContext::getDisplay()
	{
		return p_parent;
	}

	int GlContext::width()
	{
		return ((LocalDisplay*)p_parent)->p_display.xres;
	}

	int GlContext::height()
	{
		return ((LocalDisplay*)p_parent)->p_display.yres;
	}

	bool GlContext::makeCurrent()
	{
		/* connect the context to the surface */
		//if (p_current==this) return true;
		if (!Render::MakeCurrent((Display*)p_parent,this))
		{
			//Log::console("Make current failed: 0x%x", GetLastError());
			return false;
		}
		p_current = this;
		return true;
	}

	GlContext *GlContext::getCurrent()
	{
		if (p_current) {
			void* d=Render::getCurrentContex();
			void* c=(void*)((Context_P*)p_current->p_context)->context;
			if (d!=c) p_current->makeCurrent();
		}
		return p_current;
	}

	void * GlContext::set(unsigned int id,void *param)
	{
		if (id==BaseObject::TYPE) return GlContext::t();
		if (id==BaseObject::WRITE) {
			ParametersList *list=(ParametersList *)param;
			if (list->contains(STR_COLOR)) setColor((*list)[STR_COLOR].getVector4f());
		}
		return 0;
	}

	GlContext *GlContext::finder(char *path)
	{
		ObjectManager::Finder find(path);
		Display *display=Graph::graph().getDisplay(find.getNext());
		if (!display) {
			Log::console("Can`t find display: %s",find.getNext());
			return 0;
		}
		find.next();
		GlContext *context=display->getContext(find.getNext());
		if (!context) {
			Log::console("Can`t find context: %s",find.getNext());
			return 0;
		}
		find.next();
		return context;
	}

	TYPEINFO(GlContext)

}

OPTIMIZE_OFF;

#endif