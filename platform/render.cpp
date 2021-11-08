/*
 * @file render.cpp
 *
 *  Created on: 13.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>

#include <platform.h>
#include <scene/scene.h>
#include <scene/camera.h>
#include <scene/transform.h>
#include <scene/viewport.h>
#include <scene/meshfilter.h>
#include <scene/mesh.h>
#include <scene/material.h>
#include <scene/texture2d.h>
#include <scene/light.h>
#include <scene/lightingmodel.h>
#include <bt.h>
#include "csad/platform/glextension.h"
#include "csad/platform/localdisplay.h"

OPTIMIZE_ON;

namespace csad {

void _APICALL Render::setMatrix(Camera* camera)
{
	sFunctionsGLContext &functions=GlContext::p_current->functions();
	functions.MatrixMode(GL_PROJECTION);
	functions.LoadMatrixf((GLfloat*)camera->projMatrix());
	functions.MatrixMode(GL_MODELVIEW);
}

void Render::setMatrixRect(Camera* camera,vector4i &rect)
{
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	functions.MatrixMode(GL_PROJECTION);
	functions.LoadIdentity();
	vector4i rectV=camera->getViewPort(GlContext::getCurrent());
	int x=rect.x+matFunctions.FTrunc(rect.z*0.5f);
	int y=rectV.w-rect.y-matFunctions.FTrunc(rect.w*0.5f);
    if ((rect.z > 0) && (rect.w > 0)) {
    	functions.Translatef((float)(rectV.z - 2 * (x - rectV.x)) / rect.z,(float)(rectV.w - 2 * (y - rectV.y)) / rect.w, 0);
    	functions.Scalef(rectV.z *1.0f/ rect.z, rectV.w *1.0f/ rect.w, 1.0);
    }

	functions.MultMatrixf((GLfloat*)camera->projMatrix());
	functions.MatrixMode(GL_MODELVIEW);
}

float tmpColorMatrialValues[11] = { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, 1.0f };

void Render::BindMaterial(Material* material)
{
	if (!GlContext::p_current) return;
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	if (GlContext::p_current->p_lastmaterial==material) return;
	if (!material) {
		functions.Enable(GL_COLOR_MATERIAL);
		functions.Enable(GL_DEPTH_TEST);
		functions.DepthFunc(GL_LESS);
		functions.DepthMask(true);
		functions.Disable(GL_LIGHTING);
		functions.Disable(GL_BLEND);
		functions.Disable(GL_ALPHA_TEST);
		functions.ColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		functions.Color4fv(&tmpColorMatrialValues[3]);
		functions.Materialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &tmpColorMatrialValues[0]);
		functions.Materialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &tmpColorMatrialValues[3]);
		functions.Materialfv(GL_FRONT_AND_BACK, GL_EMISSION, &tmpColorMatrialValues[0]);
		functions.Materialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &tmpColorMatrialValues[7]);
		GlContext::p_current->p_lastmaterial=0;
		BindTexture2D((unsigned int)0);
		functions.MatrixMode(GL_TEXTURE);
		functions.LoadIdentity();
		functions.MatrixMode(GL_MODELVIEW);
		GlContext::p_current->p_lastmaterial=material;
		functions.LineWidth(1.0f);
		functions.PointSize(2.0f);
		return;
	}
	functions.Enable(GL_COLOR_MATERIAL);
	functions.ColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	functions.Color4fv(&material->p_diffuse.x);
	functions.Materialfv(GL_FRONT_AND_BACK,GL_AMBIENT,&material->p_ambient);
	functions.Materialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,&material->p_diffuse);
	functions.Materialfv(GL_FRONT_AND_BACK,GL_EMISSION,&material->p_emission);
	functions.Materialfv(GL_FRONT_AND_BACK,GL_SPECULAR,&material->p_specular);
	if (material->flineWidth>=0) functions.LineWidth(material->flineWidth);
	if (material->fpointSize>=0) functions.PointSize(material->fpointSize);
	if ((material->p_blend_src!=-1) && (material->p_blend_dst!=-1)) {
		functions.Enable(GL_BLEND);
		functions.BlendFunc(material->p_blend_src,material->p_blend_dst);
	} else {
		functions.Disable(GL_BLEND);
	}
	if ((material->p_alpha!=-1)) {
		functions.Enable(GL_ALPHA_TEST);
		functions.AlphaFunc(material->p_alpha,material->p_alpha_ref);
	} else {
		functions.Disable(GL_ALPHA_TEST);
	}
	functions.DepthMask((material->fflag & csad::Material::GL_DEPTHWRITE)!=0);
	if ((material->p_depth!=-1)) {
		functions.Enable(GL_DEPTH_TEST);
		functions.DepthFunc(material->p_depth);
	} else {
		functions.Disable(GL_DEPTH_TEST);
	}
	unsigned int textc=material->p_textures.count();
	unsigned int matrixc=material->ftexturesMatrix.Count;
	Texture2D **t=(Texture2D **)material->p_textures.data();
	bt::matrix4f *m=(bt::matrix4f *)material->ftexturesMatrix.Vals;
	functions.MatrixMode(GL_TEXTURE);
	if (textc==0) {
		functions.Disable(GL_TEXTURE_2D);
		functions.LoadIdentity();
		//BindTexture2D((unsigned int)0);
	}
	while (textc>0) {
		functions.Enable(GL_TEXTURE_2D);
		if (matrixc>0) {
			functions.LoadMatrixf(m->m);
		} else {
			functions.LoadIdentity();
		}
		(*t)->bind();
		t++;
		m++;
		textc--;
		matrixc--;
	}
	functions.MatrixMode(GL_MODELVIEW);
	unsigned _int32 glerr=functions.GetError();
	if (glerr>0) {
#ifdef LOG_CSAD
		Log::console("Render::BindMaterial glerror: 0x%x",glerr);
#endif
	}
	GlContext::p_current->p_lastmaterial=material;
}

struct sTmpLightData {
	unsigned int param;
	void *val;
};

sTmpLightData tmpLightData[6] = { GL_AMBIENT, 0, GL_DIFFUSE, 0, GL_SPECULAR, 0, GL_SPOT_CUTOFF, 0, GL_SPOT_DIRECTION, 0, GL_POSITION };

void _APICALL Render::BindLightingModel(LightingModel*lightings)
{
	if (!GlContext::p_current) return;
	sFunctionsGLContext &functions=GlContext::p_current->ffunctions;
	if (GlContext::p_current->p_lastlightings==lightings) return;

	if (lightings) {
		functions.Enable(GL_LIGHTING);
	} else {
		functions.Disable(GL_LIGHTING);
		GlContext::p_current->p_lastlightings=lightings;
		return;
	}

	int c=0;
	int idl=0;
	if (lightings) {
		c=lightings->lights().count();
		Light**lt=lightings->lights().data();

		tfSTDCALL_PROC_uint_uint_p Lightfv = functions.Lightfv;

		while (idl<c) {
			if (*lt) {
				functions.LoadIdentity();
				unsigned int id=GL_LIGHT0+idl;
				functions.Enable(id);
				csad::Transform *tr=(*lt)->getContainer();
				bt::vector4f pos(0.0f);
				unsigned int mode=(*lt)->mode();
				float cutoff=180.0f;
				if (mode==Light::Spot) cutoff=(*lt)->cutoff();
				if (mode==Light::Direct) {
					//pos=bt::vector4f((*lt)->direction()*quaternionf(tr->realRotate()).invert());
					bt::quaternionf q;
					if (tr) vecFunctions.V4DTo4F(tr->realRotate(),&q);
					vecFunctions.QFInv(&q,&q);
					vecFunctions.Q3FInvTransform(&q,&(*lt)->direction(),&pos);
					pos.w=0.0f;
				} else {
					if (tr) vecFunctions.V3DTo3F(tr->realPosition(),&pos);
					pos.w=1.0f;
				}
				tmpLightData[0].val = &(*lt)->ambient();
				tmpLightData[1].val = &(*lt)->diffuse();
				tmpLightData[2].val = &(*lt)->specular();
				tmpLightData[3].val = &cutoff;
				tmpLightData[4].val = &(*lt)->direction();
				tmpLightData[5].val = &pos;
				sTmpLightData *a = tmpLightData;
				sTmpLightData *c = a + 6;
				while (a < c) {
					Lightfv(id, a->param, a->val);
					a++;
				}
			} else {
				functions.Disable(GL_LIGHT0+idl);
			}
			lt++;
			idl++;
		}
	}

	int max=8;
	functions.GetIntegerv(GL_MAX_LIGHTS,&max);
	while (idl<max) {
		functions.Disable(GL_LIGHT0+idl);
		idl++;
	}

	GlContext::p_current->p_lastlightings=lightings;
}

TYPEINFO(Render)

}

OPTIMIZE_OFF;

