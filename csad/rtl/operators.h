//=============================================================================
///**
// *  @file operators.h
// *
// *  $Id: operators.h 11.02.2015  $
// *
// *  @brief rtl, MS Visual C++ 2008; GNU C/C++ 4.0;
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#pragma once

#ifndef OPERATORS_H
#define OPERATORS_H

#include <bt/macroscall.h>
#include <bt/macrostype.h>

#if (defined(LOCAL_RTL) || defined(RTL_LOCAL))// && !defined(_DLL)

#ifndef __FLTUSED__
#define __FLTUSED__
extern "C" __declspec(selectany) int _fltused = 0;
#endif

#ifdef __cplusplus
extern "C" {
#endif

//void* memset(void * _Dst, int _Val, size_t _Size);

//double _hypot(double x, double y);

#ifdef __cplusplus
}
#endif

#endif
#endif // OPERATORS_H