//=============================================================================
///**
// *  @file basetypes.h
// *
// *  $Id: basetypes.h 23.05.2012  $
// *
// *  @brief generator 3, MS Visual C++ 2003-2008
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#pragma once
#ifndef GEN3_BASE_TYPES_H
#define GEN3_BASE_TYPES_H

#include <bt/typesproc.h>

#ifdef __cplusplus
namespace bt {
#endif

struct sArray {
	unsigned _int32 Count;
	unsigned _int32 AllCount;
	unsigned _int32 ItSize;
	tfFASTCALL_int_FUNC_int Ths;
	char *Vals;
};

struct sScript {
	unsigned _int32 strNum;
	unsigned _int32 errorCode;
	void* errorString;
	void* codesMap;
	void* codesInfo;
	void* build;
};

struct sScriptItemInfo {
	void *type;
	void *var;
	void **attrTypes;
	unsigned _int32 paramCount;
};

struct sScriptParamInfo {
	void *type;
	void *var;
	void *str;
};

#ifdef __cplusplus
}
#endif

#endif
