/*
 * linuxglcontext.h
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>

#if defined (OS_LINUX)

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
		extFunctions.CleanMem(p_context,sizeof(Context_P));
		extFunctions.CleanMem(&ffunctions,sizeof(ffunctions));
		p_parent=(Display *)parent;
		p_parent->addContext(this,name);
		ffunctions.extensionsFlag=0xFFFFFFFF;
		//((LocalDisplay*)p_parent)->p_context.addObject(this,name);
	}

	GlContext::GlContext(Display *parent,const char *name)
	{
		p_lastmaterial=0;
		p_context=new Context_P();
		extFunctions.CleanMem(p_context,sizeof(Context_P));
		extFunctions.CleanMem(&ffunctions,sizeof(ffunctions));
		p_parent=(Display * )parent;
		p_parent->addContext(this,name);
		ffunctions.extensionsFlag=0xFFFFFFFF;
		//((LocalDisplay*)p_parent)->p_context.addObject(this,name);
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
		if (p_context) delete (Context_P*)p_context;
		p_context=0;
	}

	unsigned int GlContext::createTexture2D()
	{
		if (makeCurrent()) {
			unsigned int texture;
			unsigned int err=Render::GenTextures(1,&texture);
			if (err) {
				Log::console("createTexture2D failed: 0x%x", err);
				return 0;
			}
			return texture;
		} else return 0;
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

	void GlContext::setColor(vector4f &color)
	{
		if (makeCurrent()) {
			ffunctions.ClearColor(color.x,color.y,color.z,color.w);
		}
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
		sFunctionsDisplayRender &dfunctions=((LocalDisplay*)p_parent)->ffunctions;
		/* connect the context to the surface */
		//if (p_current==this) return true;
		if (!dfunctions.MakeCurrent((Display*)p_parent,this))
		{
			Log::console("Make current failed: 0x%x 0x%x", 0, ffunctions.GetError());//GetLastError()
			return false;
		}
		p_current = this;
		return true;
	}

	GlContext *GlContext::getCurrent()
	{
		if (p_current) {
			sFunctionsDisplayRender &dfunctions=((LocalDisplay*)p_current->p_parent)->ffunctions;
			void* d=dfunctions.GetCurrent();
			void* c=(void*)((Context_P*)p_current->p_context)->context;
			if (d!=c) p_current->makeCurrent();
		}
		return p_current;
	}

}

OPTIMIZE_OFF;

#endif
