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
#ifndef CORE_TYPES_H
#define CORE_TYPES_H

#include <bt/typesproc.h>

#ifdef __cplusplus
namespace csad {
#endif

/**
 * @class sFunctionsCore
 *
 * @ingroup apiinterface
 * @brief sFunctionsCore -
 *
 * @see core, apiinterface
 */
	struct sFunctionsCore {
		int version;
		
		bt::tfSTDCALL_PROC_uint InitCore;
		bt::tfSTDCALL_PROC ResetCore;

		bt::tfSTDCALL_p_FUNC CoreCreaete;
		bt::tfSTDCALL_p_FUNC Core;
		bt::tfSTDCALL_PROC_p SetCore;

		bt::tfSTDCALL_PROC_p ContainerDestructor;
		bt::tfSTDCALL_PROC_p ContainerFree;
		bt::tfSTDCALL_PROC_p ContainerAddComponent;

	};

#ifdef __cplusplus
}
#endif

#endif
