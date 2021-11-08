//=============================================================================
///**
// *  @file defarray.h
// *
// *  $Id: defarray.h 23.05.2012  $
// *
// *  @brief generator 3 tool, MS Visual C++ 2003-2008
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#pragma once
#ifndef GEN3TOOL_DEFARRAY_H
#define GEN3TOOL_DEFARRAY_H

#include <bt.h>

namespace bt {

	void _APICALL _SSetDEF(void **list,void *str);
	void _APICALL _SAddDEF(void **list,void *str);
	int _APICALL _SCompareDEF(void **list,void *str);

	void _APICALL _LSSetDEF(void **list,void *str);
	void _APICALL _LSAddDEF(void **list,void *str);
	void _APICALL _LSInsertDEF(void **list,void *str,unsigned _int32 pos);
	void _APICALL _LSRemoveDEF(void **list,unsigned _int32 pos,unsigned _int32 size);
	int _APICALL _LSCompareDEF(void **list,void *str);

	void _APICALL _ANTInitDEF(void *list,unsigned int size,unsigned int count);
	void _APICALL _ANTFreeDEF(void *list);
	void _APICALL _ANTResizeDEF(void *list,unsigned int count);
	void _APICALL _ANTReservDEF(void *list,unsigned int count);
	void _APICALL _ANTAssignDEF(void *list,void *val);
	void _APICALL _ANTDelLastDEF(void *list);
	void* _APICALL _ANTPositionDEF(void *list,unsigned int id);
	void* _APICALL _ANTPositionLDEF(void *list);

	void _APICALL _DPSetCountDEF(void ** list,unsigned _int32 count);
	void ** _APICALL _DPAddLastDEF(void ** list,void *val);
	void ** _APICALL _DPInsertDEF(void ** list,void *val,unsigned _int32 pos);
	void _APICALL _DPRemoveDEF(void ** list,unsigned _int32 pos);
	_int32 _APICALL _DPRemoveValDEF(void ** list,void *val);
	void _APICALL _DPRemoveLastDEF(void ** list);

	void ** _APICALL _DSAddLastDEF(void ** list,void *val);
	void _APICALL _DSFreeDEF(void ** list);

	void * _APICALL _APLastDEF(void ** list);
	void * _APICALL _APCloneDEF(void ** list);
	void ** _APICALL _APAddDEF(void ** list,void *val);
	_int32 _APICALL _APFindDEF(void ** list,void *val);
	_int32 _APICALL _APRemoveDEF(void ** list,void *val);
	void * _APICALL _APEndDEF(void ** list);
	void _APICALL _APFreeDEF(void ** list);

	void ** _APICALL _MPAddDEF(void ** list,void *key,void *val);
	void ** _APICALL _MPFindDEF(void ** list,void *key);
	void * _APICALL _MPFindByValDEF(void ** list, void *val, void *key);
	void * _APICALL _MPRemoveDEF(void ** list,void *key);
	void ** _APICALL _MPEndDEF(void ** list);
	void _APICALL _MPFreeDEF(void ** list);

	void ** _APICALL _MSPAddDEF(void ** list,void *key,void *val);
	void ** _APICALL _MSSPAddDEF(void ** list, void *key, void *val);
	void ** _APICALL _MSPFindDEF(void ** list,void *key);
	void ** _APICALL _MSSPFindDEF(void ** list,char *key);
	void * _APICALL _MSPRemoveDEF(void ** list,void *key);
	int _APICALL _MSSPRemoveDEF(void ** list,void *key);
	void _APICALL _MSSPFreeDEF(void ** list);

	void ** _APICALL _MCPAddDEF(void * list,void *key,void *val,unsigned _int32 max);
	void ** _APICALL _MCPFindDEF(void * list,void *key);

	void ** _APICALL _MCSPAddDEF(void * list,void *key,void *val,unsigned _int32 max);
	void ** _APICALL _MCSPFindDEF(void * list,void *key);

	void * _APICALL _MPArrayDEF(void **list);
	unsigned _int32 _APICALL _MPCountDEF(void **list);
};

#endif
