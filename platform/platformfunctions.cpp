/*
 * platformfunctions.cpp
 *
 *  Created on: 12.04.2008
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformfunctions.h>
#include <bt/macroscall.h>
#include "base/basenetconnection.h"
#include "base/basesoftrender.h"
#include <platform/render.h>
#include <platform/display.h>

OPTIMIZE_ON;

csad::sFunctionsPlatform platformFunctions;

enum States {
	VALIDED = 0x011F1C01,
	FREE = 0
};

unsigned _int32 fisPlatformVal=FREE;

void _APICALL initPlatform(unsigned _int32 )
{
	if (fisPlatformVal==VALIDED) return;
	fisPlatformVal=VALIDED;

	csad::sFunctionsPlatform *as=(csad::sFunctionsPlatform *)&platformFunctions;
	as->version=0;

	as->NetConnectionCreate=(bt::tfSTDCALL_PROC_p)&csad::_NetConnectionCreateDEF;
	as->NetConnectionOpen=(bt::tfSTDCALL_bool_FUNC_p)&csad::_NetConnectionOpenDEF;
	as->NetConnectionConnect=(bt::tfSTDCALL_bool_FUNC_p)&csad::_NetConnectionConnectDEF;
	as->NetConnectionAccept=(bt::tfSTDCALL_p_FUNC_p)&csad::_NetConnectionAcceptDEF;
	as->NetConnectionClose=(bt::tfSTDCALL_bool_FUNC_p)&csad::_NetConnectionCloseDEF;
	as->NetConnectionSetIP4=(bt::tfSTDCALL_PROC_p_p_int)&csad::_NetConnectionSetIP4DEF;
	as->NetConnectionGetIP4=(bt::tfSTDCALL_uint_FUNC_p)&csad::_NetConnectionGetIP4DEF;
	as->NetConnectionRead=(bt::tfSTDCALL_int_FUNC_p_p_uint)&csad::_NetConnectionReadDEF;
	as->NetConnectionWrite=(bt::tfSTDCALL_int_FUNC_p_p_uint)&csad::_NetConnectionWriteDEF;
	
}

void _APICALL resetPlatform() {
	fisPlatformVal=0;
}

void _APICALL initDisplayRender(void *content,unsigned _int32 mode)
{
	csad::sFunctionsDisplayRender *as=(csad::sFunctionsDisplayRender *)content;
	as->version=0;
	as->mode=mode;
	mode=mode & 0xFF;

#if defined(CSAD_SOFT_RENDER) || defined(SOFT_RENDER_CSAD)
	if (mode==csad::Display::RM_SOFT) {
		as->Initialize=(bt::tfSTDCALL_PROC_p)&csad::SoftRender::initialize;
		as->CreateContext=(bt::tfSTDCALL_bool_FUNC_p_p)&csad::SoftRender::createContext;
		as->DestroyContext=(bt::tfSTDCALL_bool_FUNC_p_p)&csad::SoftRender::destroyContext;
		as->GetCurrent=(bt::tfSTDCALL_p_FUNC)&csad::SoftRender::getCurrentContext;
		as->MakeCurrent=(bt::tfSTDCALL_bool_FUNC_p_p)&csad::SoftRender::MakeCurrent;
		as->SetMatrix=(bt::tfSTDCALL_PROC_p)&csad::Render::setMatrix;
		as->SetMatrixRect=(bt::tfSTDCALL_PROC_p_p)&csad::Render::setMatrixRect;
		as->Buffers=(bt::tfSTDCALL_PROC_p)&csad::SoftRender::Buffers;
		as->SetViewPort=(bt::tfSTDCALL_PROC_int_int_int_int)&csad::SoftRender::setViewPort;
		as->GenTextures=(bt::tfSTDCALL_uint_FUNC_int_p)&csad::Render::GenTextures;
	}
#endif

	if ((mode==csad::Display::RM_GL) || (mode==csad::Display::RM_GLES)) {
		as->Initialize=(bt::tfSTDCALL_PROC_p)&csad::Render::initialize;
		as->CreateContext=(bt::tfSTDCALL_bool_FUNC_p_p)&csad::Render::createContext;
		as->DestroyContext=(bt::tfSTDCALL_bool_FUNC_p_p)&csad::Render::destroyContext;
		as->GetCurrent=(bt::tfSTDCALL_p_FUNC)&csad::Render::getCurrentContext;
		as->MakeCurrent=(bt::tfSTDCALL_bool_FUNC_p_p)&csad::Render::MakeCurrent;
		as->SetMatrix=(bt::tfSTDCALL_PROC_p)&csad::Render::setMatrix;
		as->SetMatrixRect=(bt::tfSTDCALL_PROC_p_p)&csad::Render::setMatrixRect;
		if ((as->mode & (csad::Display::FM_TRANSPARENT<<8))==0) {
			as->Buffers=(bt::tfSTDCALL_PROC_p)&csad::Render::Buffers;
		} else {
			as->Buffers=(bt::tfSTDCALL_PROC_p)&csad::Render::TransparentBuffers;
		}
		as->SetViewPort=(bt::tfSTDCALL_PROC_int_int_int_int)&csad::Render::setViewPort;
		as->GenTextures=(bt::tfSTDCALL_uint_FUNC_int_p)&csad::Render::GenTextures;
	}
}

OPTIMIZE_OFF;
