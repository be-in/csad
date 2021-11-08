//=============================================================================
///**
// *  @file   defrender.h
// *
// *  $Id: defrender.h 23.05.2012  $
// *
// *  @brief generator 3, MS Visual C++ 2003-2008
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#pragma once
#ifndef GEN3TOOL_DEFRENDER_H
#define GEN3TOOL_DEFRENDER_H

#include <bt.h>

namespace bt {

void _APICALL _V3BHalfTexelDEF(void *,void *,_int32);

void _APICALL _V4BHalfTexelDEF(void *,void *,_int32);

void _APICALL _V3BTexelDEF(void *,void *,_int32,float,float);

void _APICALL _V4BTexelDEF(void *,void *,_int32,float,float);

void _APICALL _S4AFdrawDEF(void *);

void _APICALL _S4AFDLdrawDEF(void *);

void _APICALL _S4AFSdrawDEF(void *);

/// отрисовка горизонтальной линии с тестом глубины (меньше) и цветовой интерпол€цией.
void _APICALL _S4AFDLSdrawDEF(void *);

void _APICALL _P4AFdrawDEF(V4AFdata *vertex,T4AFdata *data,float radius);
void _APICALL _P4AFdrawAADEF(V4AFdata *vertex,T4AFdata *data,float radius);
void _APICALL _P4AFAdrawAADEF(V4AFdata *vertex,T4AFdata *data,float radius);

void _APICALL _L4AFdrawDEF(V4AFdata *vertexs,T4AFdata *data,float w);

void _APICALL _T4AFdrawDEF(V4AFdata *vertexs,T4AFdata *data);
void _APICALL _T4AFSdrawDEF(V4AFdata *vertexs,T4AFdata *data);

}

#endif /* GEN3TOOL_DEFRENDER_H */
