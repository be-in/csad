/*
 * x86matrix.h
 *
 *  Created on: 03.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef X86MATRIX_H_
#define X86MATRIX_H_

#include <bt.h>

namespace bt {

void _APICALL _M4DTranslateCPU(void *,double *);
void _APICALL _M4DScaleCPU(void *,double *);

void _APICALL _M4DTRSFPU(void *,double *,double *,double*);

void _APICALL _M4FMulSSE(void *,void *,void *);

void _APICALL _M4FPerspectiveSSE(void *_m,int _w,int _h,float _aend,float _astart,float _fov);
void _APICALL _M4FOrtographicSSE(void *_m,int _w,int _h,float _aend,float _astart,float _scale);

void _APICALL _M4FIdentitySSE(void *);
void _APICALL _M4DIdentitySSE(void *);

void _APICALL _M4FTranslateSSE(void *,float *);
void _APICALL _M4FScaleSSE(void *,float *);

void _APICALL _M4FAddTranslateSSE(void *,float *,void *);
void _APICALL _M4FAddScaleSSE(void *,float *,void *);
void _APICALL _M4FAddRotateSSE(void *,float *,void *);

void _APICALL _M4FTRSSSE(void *,float *,float *,float*);

void _APICALL _M4DMulSSE2(void *,void *,void *);
void _APICALL _M4DScaleSSE2(void *,double *);

void _APICALL _M4DPerspectiveSSE2(void *_m,int _w,int _h,double _aend,double _astart,double _fov);
void _APICALL _M4DOrtographicSSE2(void *_m,int _w,int _h,double _aend,double _astart,double _scale);

void _APICALL _M4DToM4FSSE2(void *,void *);

void _APICALL _M4FMulSSE3(void *,void *,void *);
void _APICALL _M4FAddRotateSSE3(void *,float *,void *);

void _APICALL _M4FTransposeSSE4(void *,void *);
void _APICALL _M4FMulSSE4(void *,void *,void *);
void _APICALL _M4DMulSSE4(void *,void *,void *);

void _APICALL _M4FPerspectiveSSE4(void *_m,int _w,int _h,float _aend,float _astart,float _fov);
void _APICALL _M4DPerspectiveSSE4(void *_m,int _w,int _h,double _aend,double _astart,double _fov);
void _APICALL _M4FOrtographicSSE4(void *_m,int _w,int _h,float _aend,float _astart,float _scale);
void _APICALL _M4DOrtographicSSE4(void *_m,int _w,int _h,double _aend,double _astart,double _scale);

void _APICALL _M4FIdentitySSE4(void *);
void _APICALL _M4DIdentitySSE4(void *);

void _APICALL _M4DTranslateSSE4(void *,double *);

void _APICALL _M4FAddTranslateSSE4(void *,float *,void *);
void _APICALL _M4DAddTranslateSSE4(void *,double *,void *);
void _APICALL _M4FAddScaleSSE4(void *,float *,void *);
void _APICALL _M4FAddRotateSSE4(void *,float *,void *);
void _APICALL _M4DAddRotateSSE4(void *,double *,void *);

void _APICALL _M4FTRSSSE4(void *,float *,float *,float*);
void _APICALL _M4DTRSSSE4(void *,double *,double *,double*);

void _APICALL _M4FMulAVX(void *,void *,void *);
void _APICALL _M4DMulAVX(void *,void *,void *);

}

#endif /* X86MATRIX_H_ */
