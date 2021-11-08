//=============================================================================
///**
// *  @file   typesproc.h
// *
// *  $Id: typesproc.h 23.05.2012  $
// *
// *  @brief generator 3, MS Visual C++ 2003-2008
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#pragma once
#ifndef GEN3_TYPESPROC_H
#define GEN3_TYPESPROC_H

#include <bt/macroscall.h>
#include <bt/macrostype.h>

#ifdef __cplusplus
namespace bt {
#endif

// **************** FAST call types ********************

	typedef _int32 (_FASTCALL *tfFASTCALL_int_FUNC)();
	typedef _int32 (_FASTCALL *tfFASTCALL_int_FUNC_p)(void *);
	typedef _int32 (_FASTCALL *tfFASTCALL_int_FUNC_p_p)(void *,void *);
	typedef _int32 (_FASTCALL *tfFASTCALL_int_FUNC_p_p_p)(void *,void *,void *);
	typedef _int32 (_FASTCALL *tfFASTCALL_int_FUNC_int)(_int32);
	typedef _int32 (_FASTCALL *tfFASTCALL_int_FUNC_int_int)(_int32,_int32);
	typedef _int32 (_FASTCALL *tfFASTCALL_int_FUNC_int_int_int)(_int32,_int32,_int32);

	typedef unsigned _int32 (_FASTCALL *tfFASTCALL_uint_FUNC_p)(void *);
	typedef bool (_FASTCALL *tfFASTCALL_bool_FUNC_p_p)(void *,void *);

	typedef void (_FASTCALL *tfFASTCALL_PROC)();
	typedef void (_FASTCALL *tfFASTCALL_PROC_p)(void *);
	typedef void (_FASTCALL *tfFASTCALL_PROC_p_p_p)(void*, void*, void*);
	typedef void (_FASTCALL *tfFASTCALL_PROC_p_int)(void *,_int32);
	typedef void (_FASTCALL *tfFASTCALL_PROC_p_p_int)(void *,void *,_int32);
	typedef void (_FASTCALL *tfFASTCALL_PROC_p_p_int_int)(void *,void *,_int32,_int32);

// **************** STD call types ********************


	typedef void* (_APICALL *tfSTDCALL_p_FUNC)();
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_p)(void*);
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_p_p)(void*,void*);
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_p_p_p)(void*,void*,void*);
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_p_p_p_p)(void*,void*,void*,void*);
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_p_p_p_p_p)(void*,void*,void*,void*,void*);
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_p_p_p_p_p_p)(void*,void*,void*,void*,void*,void*);
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_p_p_p_p_p_p_p)(void*,void*,void*,void*,void*,void*,void*);
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_p_p_p_p_p_p_p_p)(void*,void*,void*,void*,void*,void*,void*,void*);
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_p_p_p_p_p_p_p_p_p)(void*,void*,void*,void*,void*,void*,void*,void*,void*);
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_p_p_p_int)(void*,void*,void*,_int32);
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_p_p_p_uint)(void*,void*,void*,unsigned _int32);
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_p_p_uint)(void*,void*,unsigned _int32);
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_p_int_p)(void*,_int32,void*);
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_p_uint)(void*,unsigned _int32);
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_p_uint_uint)(void*,unsigned _int32,unsigned _int32);
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_p_bool)(void*,bool);
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_int)(_int32);
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_int_int)(_int32,_int32);
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_int_int_int)(_int32,_int32,_int32);
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_uint)(unsigned int);
	typedef void* (_APICALL *tfSTDCALL_p_FUNC_uint_uint)(unsigned _int32,unsigned _int32);

	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC)();
	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_p)(void*);
	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_p_p)(void*,void*);
	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_p_p_p)(void*,void*,void*);
	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_p_p_p_p_p)(void*,void*,void*,void*,void*);
	
	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_p_p_p_float_float_float_float)(void*,void*,void*,float,float,float,float);

	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_p_p_int)(void*,void*,int);
	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_p_p_int_int)(void*,void*,_int32,_int32);
	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_p_p_int_int_p_p)(void*,void*,_int32,_int32,void*,void*);
	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_p_p_uint)(void*,void*,unsigned _int32);

	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_p_int)(void*,_int32);
	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_p_uint_int)(void*,unsigned _int32,_int32);

	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_int)(_int32);
	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_int_p)(_int32,void*);
	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_int_p_p_p_p)(_int32,void*,void*,void*,void*);
	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_int_int)(_int32,_int32);
	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_int_int_int)(_int32,_int32,_int32);
	
	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_uint)(unsigned _int32);
	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_long)(_int64);

	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_float)(float);
	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_double)(double);

	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_float_int)(float,_int32);
	typedef _int32 (_APICALL *tfSTDCALL_int_FUNC_double_int)(double,_int32);

	typedef unsigned _int32 (_APICALL *tfSTDCALL_uint_FUNC)();
	typedef unsigned _int32 (_APICALL *tfSTDCALL_uint_FUNC_p)(void *);
	typedef unsigned _int32 (_APICALL *tfSTDCALL_uint_FUNC_int_p)(_int32,void *);
	typedef unsigned _int32 (_APICALL *tfSTDCALL_uint_FUNC_uint)(unsigned _int32);
	typedef unsigned _int32 (_APICALL *tfSTDCALL_uint_FUNC_uint_p)(unsigned _int32,void *);

	typedef _int64 (_APICALL *tfSTDCALL_long_FUNC)();
	typedef _int64 (_APICALL *tfSTDCALL_long_FUNC_p)(void*);
	typedef _int64 (_APICALL *tfSTDCALL_long_FUNC_p_p)(void*,void*);
	typedef _int64 (_APICALL *tfSTDCALL_long_FUNC_p_p_p)(void*,void*,void*);

	typedef float (_APICALL *tfSTDCALL_float_FUNC)();
	typedef float (_APICALL *tfSTDCALL_float_FUNC_p)(void*);
	typedef float (_APICALL *tfSTDCALL_float_FUNC_p_p)(void*,void*);
	typedef float (_APICALL *tfSTDCALL_float_FUNC_p_p_p)(void*,void*,void*);
	typedef float (_APICALL *tfSTDCALL_float_FUNC_p_p_p_uint)(void*,void*,void*,unsigned _int32);
	typedef float (_APICALL *tfSTDCALL_float_FUNC_p_uint_float)(void*,unsigned _int32,float);
	typedef float (_APICALL *tfSTDCALL_float_FUNC_p_uint_uint_float_float)(void*,unsigned _int32,float,float);
	typedef float (_APICALL *tfSTDCALL_float_FUNC_p_uint_float_float)(void*,unsigned _int32,float,float);
	typedef float (_APICALL *tfSTDCALL_float_FUNC_p_float)(void*, float);

	typedef float (_APICALL *tfSTDCALL_float_FUNC_int)(_int32);

	typedef float (_APICALL *tfSTDCALL_float_FUNC_float)(float);
	typedef float (_APICALL *tfSTDCALL_float_FUNC_float_int)(float,_int32);
	typedef float (_APICALL *tfSTDCALL_float_FUNC_float_float)(float,float);
	typedef float (_APICALL *tfSTDCALL_float_FUNC_float_float_float)(float,float,float);

	typedef double (_APICALL *tfSTDCALL_double_FUNC)();
	typedef double (_APICALL *tfSTDCALL_double_FUNC_p)(void*);
	typedef double (_APICALL *tfSTDCALL_double_FUNC_p_p)(void*,void*);
	typedef double (_APICALL *tfSTDCALL_double_FUNC_p_p_p)(void*,void*,void*);
	typedef double (_APICALL *tfSTDCALL_double_FUNC_p_p_p_uint)(void*,void*,void*,unsigned _int32);
	typedef double (_APICALL *tfSTDCALL_double_FUNC_p_uint_double)(void*,unsigned _int32,double);
	typedef double (_APICALL *tfSTDCALL_double_FUNC_p_uint_uint_double_double)(void*,unsigned _int32,unsigned _int32,double,double);
	typedef double (_APICALL *tfSTDCALL_double_FUNC_p_uint_double_double)(void*,unsigned _int32,double,double);
	
	typedef double (_APICALL *tfSTDCALL_double_FUNC_long)(_int64);

	typedef double (_APICALL *tfSTDCALL_double_FUNC_double)(double);
	typedef double (_APICALL *tfSTDCALL_double_FUNC_double_int)(double,int);
	typedef double (_APICALL *tfSTDCALL_double_FUNC_double_double)(double,double);
	typedef double (_APICALL *tfSTDCALL_double_FUNC_double_double_double)(double,double,double);

	typedef bool (_APICALL *tfSTDCALL_bool_FUNC)();
	typedef bool (_APICALL *tfSTDCALL_bool_FUNC_p)(void*);
	typedef bool (_APICALL *tfSTDCALL_bool_FUNC_p_p)(void*,void*);
	typedef bool (_APICALL *tfSTDCALL_bool_FUNC_p_p_uint)(void*,void*,unsigned _int32);
	typedef bool (_APICALL *tfSTDCALL_bool_FUNC_p_p_float_double)(void*,void*,float,double);
	typedef bool (_APICALL *tfSTDCALL_bool_FUNC_p_p_double_double)(void*,void*,double,double);
	typedef bool (_APICALL *tfSTDCALL_bool_FUNC_p_p_p_float)(void*,void*,void*,float);
	typedef bool (_APICALL *tfSTDCALL_bool_FUNC_p_p_p_double)(void*,void*,void*,double);
	typedef bool (_APICALL *tfSTDCALL_bool_FUNC_p_uint)(void*,unsigned _int32);
	typedef bool (_APICALL *tfSTDCALL_bool_FUNC_int)(_int32);
	typedef bool (_APICALL *tfSTDCALL_bool_FUNC_uint)(unsigned _int32);

	typedef void (_APICALL *tfSTDCALL_PROC)();
	typedef void (_APICALL *tfSTDCALL_PROC_p)(void*);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p)(void*,void*);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p)(void*,void*,void*);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p_p)(void*,void*,void*,void*);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p_p_p)(void*,void*,void*,void*,void*);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p_p_p_int_int_int_uint)(void*,void*,void*,void*,void*,_int32,_int32,_int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p_p_p_int_int_uint_uint)(void*,void*,void*,void*,void*,_int32,_int32,unsigned _int32,unsigned _int32);

	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p_p_p_uint_uint_uint_uint)(void*,void*,void*,void*,void*,unsigned _int32,unsigned _int32,unsigned _int32,unsigned _int32);

	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p_int)(void*,void*,void*,_int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p_int_int_int)(void*,void*,void*,_int32,_int32,_int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p_int_int_int_uint)(void*,void*,void*,_int32,_int32,_int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p_int_int_uint)(void*,void*,void*,_int32,_int32,unsigned _int32);

	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p_uint_uint_uint)(void*,void*,void*,unsigned _int32,unsigned _int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p_uint_uint_uint_uint)(void*,void*,void*,unsigned _int32,unsigned _int32,unsigned _int32,unsigned _int32);

	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p_float)(void*,void*,void*,float);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p_float_int_int_int_uint)(void*,void*,void*,float,_int32,_int32,_int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p_float_uint_uint_uint_uint)(void*,void*,void*,float,unsigned _int32,unsigned _int32,unsigned _int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p_float_float)(void*,void*,void*,float,float);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p_float_float_float_float)(void*,void*,void*,float,float,float,float);

	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p_double)(void*,void*,void*,double);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p_double_int_int_int_uint)(void*,void*,void*,double,_int32,_int32,_int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p_double_uint_uint_uint_uint)(void*,void*,void*,double,unsigned _int32,unsigned _int32,unsigned _int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_p_double_double)(void*,void*,void*,double,double);

	typedef void (_APICALL *tfSTDCALL_PROC_p_p_int)(void*,void*,_int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_int_int)(void*,void*,_int32,_int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_int_int_int)(void*,void*,_int32,_int32,_int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_int_int_uint)(void*,void*,_int32,_int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_int_int_float_float_uint_uint_uint)(void*,void*,_int32,_int32,float,float,unsigned _int32,unsigned _int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_int_int_double_float_uint_uint_uint)(void*,void*,_int32,_int32,double,float,unsigned _int32,unsigned _int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_int_uint)(void*,void*,_int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_int_float_float)(void*,void*,_int32,float,float);

	typedef void (_APICALL *tfSTDCALL_PROC_p_p_uint)(void*,void*,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_uint_uint)(void*,void*,unsigned _int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_uint_uint_p_p_uint)(void*,void*,unsigned _int32,unsigned _int32,void*,void*,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_uint_uint_uint)(void*,void*,unsigned _int32,unsigned _int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_uint_uint_uint_uint_uint)(void*,void*,unsigned _int32,unsigned _int32,unsigned _int32,unsigned _int32,unsigned _int32);

	typedef void (_APICALL *tfSTDCALL_PROC_p_p_float)(void*,void*,float);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_float_int)(void*,void*,float,_int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_float_int_int)(void*,void*,float,_int32,_int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_float_int_int_uint)(void*,void*,float,_int32,_int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_float_uint_uint_uint)(void*,void*,float,unsigned _int32,unsigned _int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_float_float)(void*,void*,float,float);

	typedef void (_APICALL *tfSTDCALL_PROC_p_p_double)(void*,void*,double);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_double_int_int_uint)(void*,void*,double,_int32,_int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_double_uint_uint_uint)(void*,void*,double,unsigned _int32,unsigned _int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_p_double_double)(void*,void*,double,double);
	
	typedef void (_APICALL *tfSTDCALL_PROC_p_int)(void*,_int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_int_int)(void*,_int32,_int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_int_int_int)(void*,_int32,_int32,_int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_int_int_int_int_int)(void*,_int32,_int32,_int32,_int32,_int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_int_int_int_int_uint)(void*,_int32,_int32,_int32,_int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_int_int_int_float_uint)(void*,_int32,_int32,_int32,float,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_int_int_int_float_uint_uint)(void*,_int32,_int32,_int32,float,unsigned _int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_int_int_int_float_float_float)(void*,_int32,_int32,_int32,float,float,float);
	typedef void (_APICALL *tfSTDCALL_PROC_p_int_int_float)(void*,_int32,_int32,float);
	typedef void (_APICALL *tfSTDCALL_PROC_p_int_int_float_float_float)(void*,_int32,_int32,float,float,float);
	typedef void (_APICALL *tfSTDCALL_PROC_p_int_int_double_double_double)(void*,_int32,_int32,double,double,double);
	typedef void (_APICALL *tfSTDCALL_PROC_p_uint_int)(void*,unsigned _int32,_int32);

	typedef void (_APICALL *tfSTDCALL_PROC_p_uint)(void*,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_uint_uint)(void*,unsigned _int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_uint_uint_uint)(void*,unsigned _int32,unsigned _int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_uint_uint_uint_uint_uint)(void*,unsigned _int32,unsigned _int32,unsigned _int32,unsigned _int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_float)(void*,float);
	typedef void (_APICALL *tfSTDCALL_PROC_p_float_float)(void*,float,float);
	typedef void (_APICALL *tfSTDCALL_PROC_p_float_float_float)(void*,float,float,float);
	typedef void (_APICALL *tfSTDCALL_PROC_p_float_float_float_float_float_uint_uint)(void*,float,float,float,float,float,unsigned _int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_p_float_float_float_float_float_float)(void*,float,float,float,float,float,float);
	typedef void (_APICALL *tfSTDCALL_PROC_p_float_float_float_float_float_float_float)(void*,float,float,float,float,float,float,float);
	typedef void (_APICALL *tfSTDCALL_PROC_p_float_float_float_float_float_float_float_float)(void*,float,float,float,float,float,float,float,float);

	typedef void (_APICALL *tfSTDCALL_PROC_int_p)(_int32,void*);
	typedef void (_APICALL *tfSTDCALL_PROC_int_int)(_int32,_int32);
	typedef void (_APICALL *tfSTDCALL_PROC_int_int_p)(_int32,_int32,void*);
	typedef void (_APICALL *tfSTDCALL_PROC_int_int_int_int)(_int32,_int32,_int32,_int32);
	typedef void (_APICALL *tfSTDCALL_PROC_int_int_int_int_uint_uint_p)(_int32,_int32,_int32,_int32,unsigned _int32,unsigned _int32,void*);
	typedef void (_APICALL *tfSTDCALL_PROC_int_uint)(_int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_int_uint_int_p)(_int32,unsigned _int32,_int32,void*);

	typedef void (_APICALL *tfSTDCALL_PROC_uint)(unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_uint_p)(unsigned _int32,void*);
	typedef void (_APICALL *tfSTDCALL_PROC_uint_p_p_p)(unsigned _int32,void*,void*,void*);
	typedef void (_APICALL *tfSTDCALL_PROC_uint_int_p)(unsigned _int32,_int32,void*);
	typedef void (_APICALL *tfSTDCALL_PROC_uint_int_p_p)(unsigned _int32,_int32,void*,void*);
	typedef void (_APICALL *tfSTDCALL_PROC_uint_int_p_uint)(unsigned _int32,_int32,void*,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_uint_int_int_p)(unsigned _int32,_int32,_int32,void*);
	typedef void (_APICALL *tfSTDCALL_PROC_uint_int_int_int_int_int_uint_uint_p)(unsigned _int32,_int32,_int32,_int32,_int32,_int32,unsigned _int32,unsigned _int32,void*);
	typedef void (_APICALL *tfSTDCALL_PROC_uint_int_uint_p)(unsigned _int32,_int32,unsigned _int32,void*);
	typedef void (_APICALL *tfSTDCALL_PROC_uint_uint)(unsigned _int32,unsigned _int32);
	typedef void (_APICALL *tfSTDCALL_PROC_uint_uint_p)(unsigned _int32,unsigned _int32,void*);
	typedef void (_APICALL *tfSTDCALL_PROC_uint_uint_int)(unsigned _int32,unsigned _int32,_int32);
	typedef void (_APICALL *tfSTDCALL_PROC_uint_float)(unsigned _int32,float);
	typedef void (_APICALL *tfSTDCALL_PROC_uint_float_float)(unsigned _int32,float,float);
	typedef void (_APICALL *tfSTDCALL_PROC_uint_float_float_float)(unsigned _int32,float,float,float);
	typedef void (_APICALL *tfSTDCALL_PROC_uint_float_float_float_float)(unsigned _int32,float,float,float,float);
	typedef void (_APICALL *tfSTDCALL_PROC_uint_double)(unsigned _int32,double);

	typedef void (_APICALL *tfSTDCALL_PROC_float)(float);
	typedef void (_APICALL *tfSTDCALL_PROC_float_p_p)(float,void*,void*);
	typedef void (_APICALL *tfSTDCALL_PROC_float_float_p)(float,float,void*);
	typedef void (_APICALL *tfSTDCALL_PROC_float_float_float)(float,float,float);
	typedef void (_APICALL *tfSTDCALL_PROC_float_float_float_float)(float,float,float,float);
	typedef void (_APICALL *tfSTDCALL_PROC_float_float_float_float_p)(float,float,float,float,void*);
	typedef void (_APICALL *tfSTDCALL_PROC_double)(double);
	typedef void (_APICALL *tfSTDCALL_PROC_double_p_p)(double,void*,void*);
	typedef void (_APICALL *tfSTDCALL_PROC_double_double_p)(double,double,void*);
	typedef void (_APICALL *tfSTDCALL_PROC_double_double_double_double_p)(double,double,double,double,void*);

	typedef void (_APICALL *tfSTDCALL_PROC_bool)(bool);
	
#ifdef __cplusplus
}
#endif

#endif
