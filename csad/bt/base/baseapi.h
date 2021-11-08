//=============================================================================
///**
// *  @file defapi.h
// *
// *  $Id: defapi.h 23.05.2012  $
// *
// *  @brief generator 3 tool, MS Visual C++ 2003-2008
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#pragma once
#ifndef GEN3TOOL_BASEAPI_H
#define GEN3TOOL_BASEAPI_H

#include <bt.h>

namespace bt {

char* _APICALL getCPUstring();
void _APICALL resetFunc();
void _APICALL initFunc(unsigned _int32 flagMask=0xFFFFFFFF);

void _APICALL initBT(void*_conteiner);
void _APICALL initMath(void*_conteiner);
void _APICALL initVector(void*_conteiner);
void _APICALL initArrayVector(void*_conteiner);
void _APICALL initExtension(void*_conteiner);
void _APICALL initArray(void*_conteiner);
void _APICALL initObject(void*_conteiner);
void _APICALL initRender(void*_conteiner);

}

#endif