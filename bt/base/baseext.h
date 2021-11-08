//=============================================================================
///**
// *  @file   defext.h
// *
// *  $Id: defext.h 23.05.2012  $
// *
// *  @brief generator 3, MS Visual C++ 2003-2008
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#pragma once
#ifndef GEN3TOOL_DEFEXT_H
#define GEN3TOOL_DEFEXT_H

#include <bt.h>

OPTIMIZE_ON;

namespace bt {

	extern unsigned _int32 Noigen[];

	_int64 _APICALL _TSCDEFF();

	unsigned _int32 _APICALL _GetFuncFlagDEF();

	void* _APICALL _CreateMemDEF(unsigned _int32 _size,unsigned _int32 _flag);

	bool _APICALL _DeleteMemDEF(void *mem,unsigned _int32 _flag);

	void* _APICALL _ResizeMemDEF(void *mem,unsigned _int32 _size,unsigned _int32 _flag);

	void _APICALL _CleanMemDEF(void *_mem,unsigned _int32 _size);

	/// копирование данных из источника _src в приемник _dst размером _size
	void _APICALL _MoveMemDEF(void *_src,void *_dst,unsigned _int32 _size);

	void _APICALL _MoveBackDEF(void *_src,void *_dst,unsigned _int32 _size);

	void _APICALL _SwapMemDEF(void *_src,void *_dst,unsigned _int32 _size);

	/// заполнение памяти _dst байтом _val
	void _APICALL _StocBMemDEF(void *_dst,unsigned _int32 _count,unsigned _int32 _val);
	/// заполнение памяти _dst словом _val
	void _APICALL _StocSMemDEF(void *_dst,unsigned _int32 _count,unsigned _int32 _val);
	/// заполнение памяти _dst двойным словом _val
	void _APICALL _StocIMemDEF(void *_dst,unsigned _int32 _count,unsigned _int32 _val);

	/// сравнение, возвращает индекс расхождения
	_int32 _APICALL _CmpMemDEF(void *_src,void *_dst,unsigned _int32 _size);

	/// аналог сравнения, возвращает значение расхождения
	_int32 _APICALL _SubMemDEF(void *_src,void *_dst,unsigned _int32 _size);

	/// поиск байта _c по направлению знака _size от начала _src
	_int32 _APICALL _FindCMemDEF(void *_src,unsigned _int32 _c,_int32 _size);
	/// поиск слова _c по направлению знака _size от начала _src
	_int32 _APICALL _FindSMemDEF(void *_src,unsigned _int32 _c,_int32 _size);
	/// поиск двойново слова _c по направлению знака _size от начала _src
	_int32 _APICALL _FindIMemDEF(void *_src,unsigned _int32 _c,_int32 _size);

	void _APICALL _setbit(_int32, _int32, void*);

	_int32 _APICALL _getbit(_int32, void*);

	void* _APICALL _GetFastSTDMulI(_int32);

	void* _APICALL _GetFastFCMulI(_int32);

	void _APICALL _NoiseStartDEF(_int32 _seed,_int32 _cor);
	_int32 _APICALL _NoiseGetDEF();
	void _APICALL _NoiseSaveDEF(unsigned _int32 *buff);
	void _APICALL _NoiseLoadDEF(unsigned _int32 *buff);

	_int32 _APICALL _ILogSizeDEF(_int32);

	char* _APICALL _STRLeftFindDEF(char*,char*);
	char* _APICALL _STRRightFindDEF(char*,char*);
	//char* _STDCALL _STRTokDEF(char*,char*);
	char* _APICALL _STRLeftFindDEF(char*,char*);
	char* _APICALL _STRRightFindDEF(char*,char*);
	_int32 _APICALL _STRToIDEF(char*);
	_int32 _APICALL _STRHexToIDEF(char*);
	float _APICALL _STRToFDEF(char*);
	double _APICALL _STRToDDEF(char*);
	void _APICALL _IToSTRDEF(char*,unsigned _int32,_int32);

	_int32 _APICALL _KeyToUniCharDEF(_int32,_int32);

	bool _APICALL _FMotionPointDEF(float *It, float *SP, float Et, double timer);
	bool _APICALL _DMotionPointDEF(double *It, double* SP, double Et, double timer);
	bool _APICALL _V2FMotionPointDEF(float *It, float *SP, float *Et, double timer);
	bool _APICALL _V2DMotionPointDEF(double *It, double* SP, double *Et, double timer);
	bool _APICALL _V3FMotionPointDEF(float *It, float *SP, float *Et, double timer);
	bool _APICALL _V3DMotionPointDEF(double *It, double* SP, double *Et, double timer);
	bool _APICALL _V4FMotionPointDEF(float *It, float *SP, float *Et, double timer);
	bool _APICALL _V4DMotionPointDEF(double *It, double* SP, double *Et, double timer);

	bool _APICALL _FMotionRadDEF(float *It, float* SP, float Et, double timer);
	bool _APICALL _DMotionRadDEF(double *It, double* SP, double Et, double timer);
	bool _APICALL _V2FMotionRadDEF(float *It, float *SP, float *Et, double timer);
	bool _APICALL _V2DMotionRadDEF(double *It, double* SP, double *Et, double timer);
	bool _APICALL _V3FMotionRadDEF(float *It, float *SP, float *Et, double timer);
	bool _APICALL _V3DMotionRadDEF(double *It, double* SP, double *Et, double timer);
	bool _APICALL _V4FMotionRadDEF(float *It, float *SP, float *Et, double timer);
	bool _APICALL _V4DMotionRadDEF(double *It, double* SP, double *Et, double timer);

	void _APICALL _V2FPCRCCDEF(float **,float *);
	void _APICALL _V3FPCRCCDEF(float **,float *);
	void _APICALL _V4FPCRCCDEF(float **,float *);
	void _APICALL _V2DPCRCCDEF(double **,double *);
	void _APICALL _V3DPCRCCDEF(double **,double *);
	void _APICALL _V4DPCRCCDEF(double **,double *);

	void _APICALL _V2FSplineCRDEF(float *,float *,float ,float);
	void _APICALL _V3FSplineCRDEF(float *,float *,float ,float);
	void _APICALL _V4FSplineCRDEF(float *,float *,float ,float);
	void _APICALL _V2DSplineCRDEF(double *,double *,double ,double);
	void _APICALL _V3DSplineCRDEF(double *,double *,double ,double);
	void _APICALL _V4DSplineCRDEF(double *,double *,double ,double);

	void _APICALL _BLHtoV3FDEF(float*_v1,float*_v2);
	void _APICALL _BLHtoV3DDEF(double*_v1,double*_v2);
	void _APICALL _BLHtoV3FFASTDEF(float*_v1,float*_v2);
	void _APICALL _BLHtoV3DFASTDEF(double* _v1,double* _v2);
	void _APICALL _BLtoV3FDEF(float _b,float _l,float* _v2);
	void _APICALL _BLtoV3DDEF(double _b,double _l,double* _v2);
	void _APICALL _BLtoV3FFASTDEF(float _b,float _l,float* _v2);
	void _APICALL _BLtoV3DFASTDEF(double _b,double _l,double* _v2);
	void _APICALL _V3FtoBLHDEF(float *_blh,float *_pos);
	void _APICALL _V3DtoBLHDEF(double *_blh,double *_pos);
	void _APICALL _V3FtoBLDEF(float *_b,float *_l,float *_pos);
	void _APICALL _V3DtoBLDEF(double *_b,double *_l,double *_pos);

	void _XY2BLGKDEF(double _x,double _y,_int32 zone,double *_br,double *_lr);

	void _TranslateSKDEF(double *_br, double *_lr, double *_hr, _int32 _table, double _b,   double _l,   double _h);

};

OPTIMIZE_OFF;

#endif
