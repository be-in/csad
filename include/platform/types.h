//=============================================================================
///**
// *  @file types.h
// *
// *  $Id: types.h 27.08.2014  $
// *
// *  @brief core, 2003-2014
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#pragma once
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

#include <bt/typesproc.h>
#include <bt/array.h>

#ifdef __cplusplus
namespace csad {
using namespace bt;
#endif

/**
 * @class sFunctionsDisplayRender
 *
 * @ingroup apiinterface
 * @brief sFunctionsDisplayRender - 
 *
 * @see csad
 */

	struct sFunctionsDisplayRender {
		_int32 version;
		unsigned _int32 mode;
		void* soft;
		tfSTDCALL_PROC_p Initialize;
		/// create OpenGl contect
		tfSTDCALL_bool_FUNC_p_p CreateContext;
		tfSTDCALL_bool_FUNC_p_p DestroyContext;
		tfSTDCALL_p_FUNC GetCurrent;
		tfSTDCALL_bool_FUNC_p_p MakeCurrent;
		tfSTDCALL_PROC_p SetMatrix;
		tfSTDCALL_PROC_p_p SetMatrixRect;
		///
		tfSTDCALL_PROC_p Buffers;
		tfSTDCALL_PROC_int_int_int_int SetViewPort;
		tfSTDCALL_uint_FUNC_int_p GenTextures;
	};

/**
 * @class sFunctionsPlatform
 *
 * @ingroup apiinterface
 * @brief sFunctionsPlatform - 
 *
 * @see csad
 */
	struct sFunctionsPlatform {
		_int32 version;
		
		bt::tfSTDCALL_p_FUNC NetConnectionNew;
		bt::tfSTDCALL_PROC_p NetConnectionCreate;
		bt::tfSTDCALL_bool_FUNC_p NetConnectionOpen;
		bt::tfSTDCALL_bool_FUNC_p NetConnectionConnect;
		bt::tfSTDCALL_p_FUNC_p NetConnectionAccept;
		bt::tfSTDCALL_bool_FUNC_p NetConnectionClose;
		bt::tfSTDCALL_PROC_p_p_int NetConnectionSetIP4;
		bt::tfSTDCALL_uint_FUNC_p NetConnectionGetIP4;
		bt::tfSTDCALL_int_FUNC_p_p_uint NetConnectionRead;
		bt::tfSTDCALL_int_FUNC_p_p_uint NetConnectionWrite;

	};

	struct sConnectionData {
		void* handle;
		ShortString addr;
		unsigned _int32 port;
		unsigned _int32 mode;
	};

#ifdef __cplusplus
}
#endif

#endif
