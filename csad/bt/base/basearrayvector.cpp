//=============================================================================
///**
// *  @file defarrayvector.cpp
// *
// *  $Id: defarrayvector.cpp 23.05.2012  $
// *
// *  @brief generator 3 tool, MS Visual C++ 2003-2008
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#include "basearrayvector.h"
#include "basemath.h"
#include "basevector.h"
#include "baseext.h"

WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

	void _FASTCALL _FAAAADEF(bt::tfFASTCALL_PROC_p_p_p fun,void*,void *_a, void *_b, void *_c, int _stepa, int _stepb, int _stepc, unsigned int _count)
	{
		char *pa = (char*)_a;
		char *pb = (char*)_b;
		char *pc = (char*)_c;
		for (unsigned int i = 0; i < _count; i++) {
			fun(pa, pb, pc);
			pa += _stepa;
			pb += _stepb;
			pc += _stepc;
		}
	}

	void _FASTCALL _AAAADEF(bt::tfSTDCALL_PROC_p_p_p fun, void*, void *_a, void *_b, void *_c, int _stepa, int _stepb, int _stepc, unsigned int _count)
	{
		char *pa = (char*)_a;
		char *pb = (char*)_b;
		char *pc = (char*)_c;
		for (unsigned int i = 0; i < _count; i++) {
			fun(pa, pb, pc);
			pa += _stepa;
			pb += _stepb;
			pc += _stepc;
		}
	}

	void _FASTCALL _AAADEF(bt::tfSTDCALL_PROC_p_p fun, void*, void *_a, void *_b, int _stepa, int _stepb, unsigned int _count)
	{
		char *pa = (char*)_a;
		char *pb = (char*)_b;
		for (unsigned int i = 0; i < _count; i++) {
			fun(pa, pb);
			pa += _stepa;
			pb += _stepb;
		}
	}

	void _FASTCALL _AAAAFDEF(bt::tfSTDCALL_PROC_p_p_p_float fun, void*, void *_a, void *_b, void *_c, float _d, int _stepa, int _stepb, int _stepc, unsigned int _count)
	{
		char *pa = (char*)_a;
		char *pb = (char*)_b;
		char *pc = (char*)_c;
		for (unsigned int i = 0; i < _count; i++) {
			fun(pa, pb, pc, _d);
			pa += _stepa;
			pb += _stepb;
			pc += _stepc;
		}
	}

	void _FASTCALL _AAPADEF(bt::tfSTDCALL_PROC_p_p_p fun, void*, void *_a, void *_b, void *_c, int _stepa, int _stepc, unsigned int _count)
	{
		char *pa = (char*)_a;
		char *pc = (char*)_c;
		for (unsigned int i = 0; i < _count; i++) {
			fun(pa, _b, pc);
			pa += _stepa;
			pc += _stepc;
		}
	}

	void _APICALL _AConvertDEF(void *_a,void *_b,int _stepa,int _stepb,void *_at,void *_bt,unsigned int _count)
	{
		if (_at==_bt) {
			if (_at==bt::vector2b::t()) arvFunctions.A2BMove(_a,_b,_stepa,_stepb,_count);
			if (_at==bt::vector3b::t()) arvFunctions.A3BMove(_a,_b,_stepa,_stepb,_count);
			if (_at==bt::vector4b::t()) arvFunctions.A4BMove(_a,_b,_stepa,_stepb,_count);
			if (_at==bt::vector2f::t()) arvFunctions.A2FMove(_a,_b,_stepa,_stepb,_count);
			if (_at==bt::vector3f::t()) arvFunctions.A3FMove(_a,_b,_stepa,_stepb,_count);
			if (_at==bt::vector4f::t()) arvFunctions.A4FMove(_a,_b,_stepa,_stepb,_count);
			if (_at==bt::vector2d::t()) arvFunctions.A2DMove(_a,_b,_stepa,_stepb,_count);
			if (_at==bt::vector3d::t()) arvFunctions.A3DMove(_a,_b,_stepa,_stepb,_count);
			if (_at==bt::vector4d::t()) arvFunctions.A4DMove(_a,_b,_stepa,_stepb,_count);
		} else {
			if (_bt==bt::vector2f::t()) {
				if (_at==bt::vector3f::t() || _at==bt::vector4f::t()) arvFunctions.A2FMove(_a,_b,_stepa,_stepb,_count);
				if (_at==bt::vector2d::t() || _at==bt::vector3d::t() || _at==bt::vector4d::t()) arvFunctions.A2DTo2F(_a,_b,_stepa,_stepb,_count);
			}
			if (_bt==bt::vector3f::t()) {
				if (_at==bt::vector2f::t()) arvFunctions.A2FGrow3F(_a,_b,_stepa,_stepb,_count);
				if (_at==bt::vector4f::t()) arvFunctions.A3FMove(_a,_b,_stepa,_stepb,_count);
				if (_at==bt::vector2d::t()) arvFunctions.A2DGrowTo3F(_a,_b,_stepa,_stepb,_count);
				if (_at==bt::vector3d::t() || _at==bt::vector4d::t()) arvFunctions.A3DTo3F(_a,_b,_stepa,_stepb,_count);
			}
			if (_bt==bt::vector4f::t()) {
				if (_at==bt::vector2f::t()) arvFunctions.A2FGrow4F(_a,_b,_stepa,_stepb,_count);
				if (_at==bt::vector3f::t()) arvFunctions.A3FGrow4F(_a,_b,_stepa,_stepb,_count);
				if (_at==bt::vector2d::t()) arvFunctions.A2DGrowTo4F(_a,_b,_stepa,_stepb,_count);
				if (_at==bt::vector3d::t()) arvFunctions.A3DGrowTo4F(_a,_b,_stepa,_stepb,_count);
				if (_at==bt::vector4d::t()) arvFunctions.A4DTo4F(_a,_b,_stepa,_stepb,_count);
			}
			if (_bt==bt::vector2d::t()) {
				if (_at==bt::vector2f::t() || _at==bt::vector3f::t() || _at==bt::vector4f::t()) arvFunctions.A2FTo2D(_a,_b,_stepa,_stepb,_count);
				if (_at==bt::vector3d::t() || _at==bt::vector4d::t()) arvFunctions.A2DMove(_a,_b,_stepa,_stepb,_count);
			}
			if (_bt==bt::vector3d::t()) {
				if (_at==bt::vector2f::t()) arvFunctions.A2FGrowTo3D(_a,_b,_stepa,_stepb,_count);
				if (_at==bt::vector3f::t() || _at==bt::vector4f::t()) arvFunctions.A3FTo3D(_a,_b,_stepa,_stepb,_count);
				if (_at==bt::vector2d::t()) arvFunctions.A2DGrow3D(_a,_b,_stepa,_stepb,_count);
				if (_at==bt::vector4d::t()) arvFunctions.A3DMove(_a,_b,_stepa,_stepb,_count);
			}
			if (_bt==bt::vector4d::t()) {
				if (_at==bt::vector2f::t()) arvFunctions.A2FGrowTo4D(_a,_b,_stepa,_stepb,_count);
				if (_at==bt::vector3f::t()) arvFunctions.A3FGrowTo4D(_a,_b,_stepa,_stepb,_count);
				if (_at==bt::vector4f::t()) arvFunctions.A4FTo4D(_a,_b,_stepa,_stepb,_count);
				if (_at==bt::vector2d::t()) arvFunctions.A2DGrow4D(_a,_b,_stepa,_stepb,_count);
				if (_at==bt::vector3d::t()) arvFunctions.A3DGrow4D(_a,_b,_stepa,_stepb,_count);
			}
		}
	}

// ************** array Move default function *******************

	void _APICALL _A2BMoveDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			char *_da=(char*)pa;
			char *_db=(char*)pb;
			_db[0]=_da[0];
			_db[1]=_da[1];
			pa+=_stepa;
			pb+=_stepb;
		}
	}

	void _APICALL _A3BMoveDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			char *_da=(char*)pa;
			char *_db=(char*)pb;
			_db[0]=_da[0];
			_db[1]=_da[1];
			_db[2]=_da[2];
			pa+=_stepa;
			pb+=_stepb;
		}
	}

	void _APICALL _A4BMoveDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			int *_da=(int*)pa;
			int *_db=(int*)pb;
			_db[0]=_da[0];
			pa+=_stepa;
			pb+=_stepb;
		}
	}

	void _APICALL _A2FMoveDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V2R32CopyDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			_int32 *_da=(_int32*)pa;
			_int32 *_db=(_int32*)pb;
			_db[0]=_da[0];
			_db[1]=_da[1];
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A3FMoveDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V3R32CopyDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			_int32 *_da=(_int32*)pa;
			_int32 *_db=(_int32*)pb;
			_db[0]=_da[0];
			_db[1]=_da[1];
			_db[2]=_da[2];
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A4FMoveDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V4R32CopyDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			_int32 *_da=(_int32*)pa;
			_int32 *_db=(_int32*)pb;
			_db[0]=_da[0];
			_db[1]=_da[1];
			_db[2]=_da[2];
			_db[3]=_da[3];
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A2DMoveDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V2R64CopyDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			_int64 *_da=(_int64*)pa;
			_int64 *_db=(_int64*)pb;
			_db[0]=_da[0];
			_db[1]=_da[1];
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A3DMoveDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V3R64CopyDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			_int64 *_da=(_int64*)pa;
			_int64 *_db=(_int64*)pb;
			_db[0]=_da[0];
			_db[1]=_da[1];
			_db[2]=_da[2];
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A4DMoveDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V4R64CopyDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			_int64 *_da=(_int64*)pa;
			_int64 *_db=(_int64*)pb;
			_db[0]=_da[0];
			_db[1]=_da[1];
			_db[2]=_da[2];
			_db[3]=_da[3];
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

// ************** array to default function *******************

	void _APICALL _A2ITo2FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V2ITo2FDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			_int32 *_da = (_int32*)pa;
			float *_db=(float*)pb;
			_db[0]=_IToFDEF(_da[0]);
			_db[1]=_IToFDEF(_da[1]);
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A2ITo2DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V2ITo2DDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			_int32 *_da = (_int32*)pa;
			double *_db=(double*)pb;
			_db[0]=_IToDDEF(_da[0]);
			_db[1]=_IToDDEF(_da[1]);
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A3ITo3FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V3ITo3FDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			_int32 *_da = (_int32*)pa;
			float *_db=(float*)pb;
			_db[0]=(float)_da[0];
			_db[1]=(float)_da[1];
			_db[2]=(float)_da[2];
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A3ITo3DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V3ITo3DDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			_int32 *_da = (_int32*)pa;
			double *_db=(double*)pb;
			_db[0]=(double)_da[0];
			_db[1]=(double)_da[1];
			_db[2]=(double)_da[2];
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A4ITo4WDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		//_AAADEF((bt::tfSTDCALL_PROC_p_p)_V4ITo4WDEF, 0, _a, _b, _stepa, _stepb, _count);
		char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			_int32 *_da = (_int32*)pa;
			short *_db=(short*)pb;
			_db[0]=(short)_da[0];
			_db[1]=(short)_da[1];
			_db[2]=(short)_da[2];
			_db[3]=(short)_da[3];
			pa+=_stepa;
			pb+=_stepb;
		}
	}

	void _APICALL _A4ITo4FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V4ITo4FDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			_int32 *_da = (_int32*)pa;
			float *_db=(float*)pb;
			_db[0]=(float)_da[0];
			_db[1]=(float)_da[1];
			_db[2]=(float)_da[2];
			_db[3]=(float)_da[3];
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A4ITo4DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V4ITo4DDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			_int32 *_da = (_int32*)pa;
			double *_db=(double*)pb;
			_db[0]=(double)_da[0];
			_db[1]=(double)_da[1];
			_db[2]=(double)_da[2];
			_db[3]=(double)_da[3];
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A2FTo2IDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V2FTo2IDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			_int32 *_db = (_int32*)pb;
			_db[0]=_FRoundDEF(_da[0]);
			_db[1]=_FRoundDEF(_da[1]);
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A3FTo3IDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V3FTo3IDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			_int32 *_db = (_int32*)pb;
			_db[0]=_FRoundDEF(_da[0]);
			_db[1]=_FRoundDEF(_da[1]);
			_db[2]=_FRoundDEF(_da[2]);
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A4FTo4IDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V4FTo4IDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			_int32 *_db = (_int32*)pb;
			_db[0]=_FRoundDEF(_da[0]);
			_db[1]=_FRoundDEF(_da[1]);
			_db[2]=_FRoundDEF(_da[2]);
			_db[3]=_FRoundDEF(_da[3]);
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A2FTo2DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V2FTo2DDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			double *_db=(double*)pb;
			_db[0]=(double)_da[0];
			_db[1]=(double)_da[1];
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A3FTo3DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V3FTo3DDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			double *_db=(double*)pb;
			_db[0]=(double)_da[0];
			_db[1]=(double)_da[1];
			_db[2]=(double)_da[2];
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A4FTo4DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V4FTo4DDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			double *_db=(double*)pb;
			_db[0]=(double)_da[0];
			_db[1]=(double)_da[1];
			_db[2]=(double)_da[2];
			_db[3]=(double)_da[3];
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A2DTo2FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V2DTo2FDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			float *_db=(float*)pb;
			_db[0]=(float)_da[0];
			_db[1]=(float)_da[1];
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A3DTo3FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V3DTo3FDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			float *_db=(float*)pb;
			_db[0]=(float)_da[0];
			_db[1]=(float)_da[1];
			_db[2]=(float)_da[2];
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A4DTo4FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V4DTo4FDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			float *_db=(float*)pb;
			_db[0]=(float)_da[0];
			_db[1]=(float)_da[1];
			_db[2]=(float)_da[2];
			_db[3]=(float)_da[3];
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

// ************** array grow default function *******************

	void _APICALL _A2FGrow3FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_db=(float*)pb;
			_db[0]=_da[0];
			_db[1]=_da[1];
			_db[2]=0.0f;
			pa+=_stepa;
			pb+=_stepb;
		}
	}

	void _APICALL _A2FGrow4FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_db=(float*)pb;
			_db[0]=_da[0];
			_db[1]=_da[1];
			_db[2]=0.f;
			_db[3]=1.0f;
			pa+=_stepa;
			pb+=_stepb;
		}
	}

	void _APICALL _A3FGrow4FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_db=(float*)pb;
			_db[0]=_da[0];
			_db[1]=_da[1];
			_db[2]=_da[2];
			_db[3]=1.0f;
			pa+=_stepa;
			pb+=_stepb;
		}
	}

	void _APICALL _A2DGrow3DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_db=(double*)pb;
			_db[0]=_da[0];
			_db[1]=_da[1];
			_db[2]=0.0;
			pa+=_stepa;
			pb+=_stepb;
		}
	}

	void _APICALL _A2DGrow4DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_db=(double*)pb;
			_db[0]=_da[0];
			_db[1]=_da[1];
			_db[2]=0.0;
			_db[3]=1.0;
			pa+=_stepa;
			pb+=_stepb;
		}
	}

	void _APICALL _A3DGrow4DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_db=(double*)pb;
			_db[0]=_da[0];
			_db[1]=_da[1];
			_db[2]=_da[2];
			_db[3]=1.0;
			pa+=_stepa;
			pb+=_stepb;
		}
	}

// ************** array grow to default function *******************

	void _APICALL _A2IGrowTo3FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			int *_da=(int*)pa;
			float *_db=(float*)pb;
			_db[0]=(float)_da[0];
			_db[1]=(float)_da[1];
			_db[2]=0;
			pa+=_stepa;
			pb+=_stepb;
		}
	}

	void _APICALL _A2IGrowTo4FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			int *_da=(int*)pa;
			float *_db=(float*)pb;
			_db[0]=(float)_da[0];
			_db[1]=(float)_da[1];
			_db[2]=0;
			_db[3]=1;
			pa+=_stepa;
			pb+=_stepb;
		}
	}

	void _APICALL _A3IGrowTo4FDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			int *_da=(int*)pa;
			float *_db=(float*)pb;
			_db[0]=(float)_da[0];
			_db[1]=(float)_da[1];
			_db[2]=(float)_da[1];
			_db[3]=1;
			pa+=_stepa;
			pb+=_stepb;
		}
	}

	void _APICALL _A2IGrowTo3DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			int *_da=(int*)pa;
			double *_db=(double*)pb;
			_db[0]=(double)_da[0];
			_db[1]=(double)_da[1];
			_db[2]=0;
			pa+=_stepa;
			pb+=_stepb;
		}
	}

	void _APICALL _A2IGrowTo4DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			int *_da=(int*)pa;
			double *_db=(double*)pb;
			_db[0]=(double)_da[0];
			_db[1]=(double)_da[1];
			_db[2]=0;
			_db[3]=1;
			pa+=_stepa;
			pb+=_stepb;
		}
	}

	void _APICALL _A3IGrowTo4DDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			int *_da=(int*)pa;
			double *_db=(double*)pb;
			_db[0]=(double)_da[0];
			_db[1]=(double)_da[1];
			_db[2]=(double)_da[1];
			_db[3]=1;
			pa+=_stepa;
			pb+=_stepb;
		}
	}

// ************** array sum default function *******************

	void _APICALL _A2FSumDEF(void *_a,float *_b,int _step,unsigned int _count)
	{
		char *p=(char*)_a;
		_b[0]=0;
		_b[1]=0;
		for (unsigned int i=0;i<_count;i++) {
			float *_d=(float*)p;
			_b[0]+=_d[0];
			_b[1]+=_d[1];
			p+=_step;
		}
	}

	void _APICALL _A3FSumDEF(void *_a,float *_b,int _step,unsigned int _count)
	{
		char *p=(char*)_a;
		_b[0]=0;
		_b[1]=0;
		for (unsigned int i=0;i<_count;i++) {
			float *_d=(float*)p;
			_b[0]+=_d[0];
			_b[1]+=_d[1];
			_b[2]+=_d[2];
			p+=_step;
		}
	}

	void _APICALL _A4FSumDEF(void *_a,float *_b,int _step,unsigned int _count)
	{
		char *p=(char*)_a;
		_b[0]=0;
		_b[1]=0;
		for (unsigned int i=0;i<_count;i++) {
			float *_d=(float*)p;
			_b[0]+=_d[0];
			_b[1]+=_d[1];
			_b[2]+=_d[2];
			_b[3]+=_d[3];
			p+=_step;
		}
	}

	void _APICALL _A2DSumDEF(void *_a,double *_b,int _step,unsigned int _count)
	{
		char *p=(char*)_a;
		_b[0]=0;
		_b[1]=0;
		for (unsigned int i=0;i<_count;i++) {
			double *_d=(double*)p;
			_b[0]+=_d[0];
			_b[1]+=_d[1];
			p+=_step;
		}
	}

	void _APICALL _A3DSumDEF(void *_a,double *_b,int _step,unsigned int _count)
	{
		char *p=(char*)_a;
		_b[0]=0;
		_b[1]=0;
		_b[2]=0;
		for (unsigned int i=0;i<_count;i++) {
			double *_d=(double*)p;
			_b[0]+=_d[0];
			_b[1]+=_d[1];
			_b[2]+=_d[2];
			p+=_step;
		}
	}

	void _APICALL _A4DSumDEF(void *_a,double *_b,int _step,unsigned int _count)
	{
		char *p=(char*)_a;
		_b[0]=0;
		_b[1]=0;
		_b[2]=0;
		_b[3]=0;
		for (unsigned int i=0;i<_count;i++) {
			double *_d=(double*)p;
			_b[0]+=_d[0];
			_b[1]+=_d[1];
			_b[2]+=_d[2];
			_b[3]+=_d[3];
			p+=_step;
		}
	}

// ************** array add vector default function *******************

	void _APICALL _A2FAddVectorDEF(void *_a,float *_b,void *_c,int _stepa,int _stepc,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V2FAddDEF, 0, _a, _b, _c, _stepa, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]+_b[0];
			_dc[1]=_da[1]+_b[1];
			pa+=_stepa;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A3FAddVectorDEF(void *_a,float *_b,void *_c,int _stepa,int _stepc,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V3FAddDEF, 0, _a, _b, _c, _stepa, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]+_b[0];
			_dc[1]=_da[1]+_b[1];
			_dc[2]=_da[2]+_b[2];
			pa+=_stepa;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A4FAddVectorDEF(void *_a,float *_b,void *_c,int _stepa,int _stepc,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V4FAddDEF, 0, _a, _b, _c, _stepa, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]+_b[0];
			_dc[1]=_da[1]+_b[1];
			_dc[2]=_da[2]+_b[2];
			_dc[3]=_da[3]+_b[3];
			pa+=_stepa;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A2DAddVectorDEF(void *_a,double *_b,void *_c,int _stepa,int _stepc,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V2DAddDEF, 0, _a, _b, _c, _stepa, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]+_b[0];
			_dc[1]=_da[1]+_b[1];
			pa+=_stepa;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A3DAddVectorDEF(void *_a,double *_b,void *_c,int _stepa,int _stepc,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V3DAddDEF, 0, _a, _b, _c, _stepa, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]+_b[0];
			_dc[1]=_da[1]+_b[1];
			_dc[2]=_da[2]+_b[2];
			pa+=_stepa;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A4DAddVectorDEF(void *_a,double *_b,void *_c,int _stepa,int _stepc,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V4DAddDEF, 0, _a, _b, _c, _stepa, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]+_b[0];
			_dc[1]=_da[1]+_b[1];
			_dc[2]=_da[2]+_b[2];
			_dc[3]=_da[3]+_b[3];
			pa+=_stepa;
			pc+=_stepc;
		}*/
	}

// ************** array add with array default function *******************

	void _APICALL _A2IAddDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_FAAAADEF((bt::tfFASTCALL_PROC_p_p_p)_V2IAddDEF_CPP, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			int *_da=(int*)pa;
			int *_db=(int*)pb;
			int *_dc=(int*)pc;
			_dc[0]=_da[0]+_db[0];
			_dc[1]=_da[1]+_db[1];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A3IAddDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_FAAAADEF((bt::tfFASTCALL_PROC_p_p_p)_V3IAddDEF_CPP, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			int *_da=(int*)pa;
			int *_db=(int*)pb;
			int *_dc=(int*)pc;
			_dc[0]=_da[0]+_db[0];
			_dc[1]=_da[1]+_db[1];
			_dc[2]=_da[2]+_db[2];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A4IAddDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_FAAAADEF((bt::tfFASTCALL_PROC_p_p_p)_V4IAddDEF_CPP, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			int *_da=(int*)pa;
			int *_db=(int*)pb;
			int *_dc=(int*)pc;
			_dc[0]=_da[0]+_db[0];
			_dc[1]=_da[1]+_db[1];
			_dc[2]=_da[2]+_db[2];
			_dc[3]=_da[3]+_db[3];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A2FAddDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_FAAAADEF((bt::tfFASTCALL_PROC_p_p_p)_V2FAddDEF_CPP, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_db=(float*)pb;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]+_db[0];
			_dc[1]=_da[1]+_db[1];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A3FAddDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_FAAAADEF((bt::tfFASTCALL_PROC_p_p_p)_V3FAddDEF_CPP, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_db=(float*)pb;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]+_db[0];
			_dc[1]=_da[1]+_db[1];
			_dc[2]=_da[2]+_db[2];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A4FAddDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_FAAAADEF((bt::tfFASTCALL_PROC_p_p_p)_V4FAddDEF_CPP, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_db=(float*)pb;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]+_db[0];
			_dc[1]=_da[1]+_db[1];
			_dc[2]=_da[2]+_db[2];
			_dc[3]=_da[3]+_db[3];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A2DAddDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_FAAAADEF((bt::tfFASTCALL_PROC_p_p_p)_V2DAddDEF_CPP, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_db=(double*)pb;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]+_db[0];
			_dc[1]=_da[1]+_db[1];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A3DAddDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_FAAAADEF((bt::tfFASTCALL_PROC_p_p_p)_V3DAddDEF_CPP, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_db=(double*)pb;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]+_db[0];
			_dc[1]=_da[1]+_db[1];
			_dc[2]=_da[2]+_db[2];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A4DAddDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_FAAAADEF((bt::tfFASTCALL_PROC_p_p_p)_V4DAddDEF_CPP, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_db=(double*)pb;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]+_db[0];
			_dc[1]=_da[1]+_db[1];
			_dc[2]=_da[2]+_db[2];
			_dc[3]=_da[3]+_db[3];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

// ************** array sub vector default function *******************

	void _APICALL _A2FSubVectorDEF(void *_a,float *_b,void *_c,int _stepa,int _stepc,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V2FSubDEF, 0, _a, _b, _c, _stepa, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]-_b[0];
			_dc[1]=_da[1]-_b[1];
			pa+=_stepa;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A3FSubVectorDEF(void *_a,float *_b,void *_c,int _stepa,int _stepc,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V3FSubDEF, 0, _a, _b, _c, _stepa, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]-_b[0];
			_dc[1]=_da[1]-_b[1];
			_dc[2]=_da[2]-_b[2];
			pa+=_stepa;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A4FSubVectorDEF(void *_a,float *_b,void *_c,int _stepa,int _stepc,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V4FSubDEF, 0, _a, _b, _c, _stepa, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]-_b[0];
			_dc[1]=_da[1]-_b[1];
			_dc[2]=_da[2]-_b[2];
			_dc[3]=_da[3]-_b[3];
			pa+=_stepa;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A2DSubVectorDEF(void *_a,double *_b,void *_c,int _stepa,int _stepc,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V2DSubDEF, 0, _a, _b, _c, _stepa, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]-_b[0];
			_dc[1]=_da[1]-_b[1];
			pa+=_stepa;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A3DSubVectorDEF(void *_a,double *_b,void *_c,int _stepa,int _stepc,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V3DSubDEF, 0, _a, _b, _c, _stepa, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]-_b[0];
			_dc[1]=_da[1]-_b[1];
			_dc[2]=_da[2]-_b[2];
			pa+=_stepa;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A4DSubVectorDEF(void *_a,double *_b,void *_c,int _stepa,int _stepc,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V4DSubDEF, 0, _a, _b, _c, _stepa, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]-_b[0];
			_dc[1]=_da[1]-_b[1];
			_dc[2]=_da[2]-_b[2];
			_dc[3]=_da[3]-_b[3];
			pa+=_stepa;
			pc+=_stepc;
		}*/
	}

// ************** array sub with array default function *******************

	void _APICALL _A2ISubDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_AAAADEF((bt::tfSTDCALL_PROC_p_p_p)_V2ISubDEF, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			int *_da=(int*)pa;
			int *_db=(int*)pb;
			int *_dc=(int*)pc;
			_dc[0]=_da[0]-_db[0];
			_dc[1]=_da[1]-_db[1];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A3ISubDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_AAAADEF((bt::tfSTDCALL_PROC_p_p_p)_V3ISubDEF, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			int *_da=(int*)pa;
			int *_db=(int*)pb;
			int *_dc=(int*)pc;
			_dc[0]=_da[0]-_db[0];
			_dc[1]=_da[1]-_db[1];
			_dc[2]=_da[2]-_db[2];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A4ISubDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_AAAADEF((bt::tfSTDCALL_PROC_p_p_p)_V4ISubDEF, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			int *_da=(int*)pa;
			int *_db=(int*)pb;
			int *_dc=(int*)pc;
			_dc[0]=_da[0]-_db[0];
			_dc[1]=_da[1]-_db[1];
			_dc[2]=_da[2]-_db[2];
			_dc[3]=_da[3]-_db[3];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A2FSubDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_AAAADEF((bt::tfSTDCALL_PROC_p_p_p)_V2FSubDEF, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_db=(float*)pb;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]-_db[0];
			_dc[1]=_da[1]-_db[1];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A3FSubDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_AAAADEF((bt::tfSTDCALL_PROC_p_p_p)_V3FSubDEF, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_db=(float*)pb;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]-_db[0];
			_dc[1]=_da[1]-_db[1];
			_dc[2]=_da[2]-_db[2];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A4FSubDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_AAAADEF((bt::tfSTDCALL_PROC_p_p_p)_V4FSubDEF, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_db=(float*)pb;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]-_db[0];
			_dc[1]=_da[1]-_db[1];
			_dc[2]=_da[2]-_db[2];
			_dc[3]=_da[3]-_db[3];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A2DSubDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_AAAADEF((bt::tfSTDCALL_PROC_p_p_p)_V2DSubDEF, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_db=(double*)pb;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]-_db[0];
			_dc[1]=_da[1]-_db[1];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A3DSubDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_AAAADEF((bt::tfSTDCALL_PROC_p_p_p)_V3DSubDEF, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_db=(double*)pb;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]-_db[0];
			_dc[1]=_da[1]-_db[1];
			_dc[2]=_da[2]-_db[2];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A4DSubDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_AAAADEF((bt::tfSTDCALL_PROC_p_p_p)_V4DSubDEF, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_db=(double*)pb;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]-_db[0];
			_dc[1]=_da[1]-_db[1];
			_dc[2]=_da[2]-_db[2];
			_dc[3]=_da[3]-_db[3];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

// ************** array scale default function *******************

	void _APICALL _A2FScaleDEF(void *_a,void *_c,float _b,int _stepa,int _stepc,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]*_b;
			_dc[1]=_da[1]*_b;
			pa+=_stepa;
			pc+=_stepc;
		}
	}

	void _APICALL _A3FScaleDEF(void *_a,void *_c,float _b,int _stepa,int _stepc,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]*_b;
			_dc[1]=_da[1]*_b;
			_dc[2]=_da[2]*_b;
			pa+=_stepa;
			pc+=_stepc;
		}
	}

	void _APICALL _A4FScaleDEF(void *_a,void *_c,float _b,int _stepa,int _stepc,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]*_b;
			_dc[1]=_da[1]*_b;
			_dc[2]=_da[2]*_b;
			_dc[3]=_da[3]*_b;
			pa+=_stepa;
			pc+=_stepc;
		}
	}

	void _APICALL _A2DScaleDEF(void *_a,void *_c,double _b,int _stepa,int _stepc,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]*_b;
			_dc[1]=_da[1]*_b;
			pa+=_stepa;
			pc+=_stepc;
		}
	}

	void _APICALL _A3DScaleDEF(void *_a,void *_c,double _b,int _stepa,int _stepc,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]*_b;
			_dc[1]=_da[1]*_b;
			_dc[2]=_da[2]*_b;
			pa+=_stepa;
			pc+=_stepc;
		}
	}

	void _APICALL _A4DScaleDEF(void *_a,void *_c,double _b,int _stepa,int _stepc,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]*_b;
			_dc[1]=_da[1]*_b;
			_dc[2]=_da[2]*_b;
			_dc[3]=_da[3]*_b;
			pa+=_stepa;
			pc+=_stepc;
		}
	}

// ************** array mul vector default function *******************

	void _APICALL _A2FMulVectorDEF(void *_a,float *_b,void *_c,int _stepa,int _stepc,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V2FMulDEF, 0, _a, _b, _c, _stepa, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]*_b[0];
			_dc[1]=_da[1]*_b[1];
			pa+=_stepa;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A3FMulVectorDEF(void *_a,float *_b,void *_c,int _stepa,int _stepc,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V3FMulDEF, 0, _a, _b, _c, _stepa, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]*_b[0];
			_dc[1]=_da[1]*_b[1];
			_dc[2]=_da[2]*_b[2];
			pa+=_stepa;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A4FMulVectorDEF(void *_a,float *_b,void *_c,int _stepa,int _stepc,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V4FMulDEF, 0, _a, _b, _c, _stepa, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]*_b[0];
			_dc[1]=_da[1]*_b[1];
			_dc[2]=_da[2]*_b[2];
			_dc[3]=_da[3]*_b[3];
			pa+=_stepa;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A2DMulVectorDEF(void *_a,double *_b,void *_c,int _stepa,int _stepc,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V2DMulDEF, 0, _a, _b, _c, _stepa, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]*_b[0];
			_dc[1]=_da[1]*_b[1];
			pa+=_stepa;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A3DMulVectorDEF(void *_a,double *_b,void *_c,int _stepa,int _stepc,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V3DMulDEF, 0, _a, _b, _c, _stepa, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]*_b[0];
			_dc[1]=_da[1]*_b[1];
			_dc[2]=_da[2]*_b[2];
			pa+=_stepa;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A4DMulVectorDEF(void *_a,double *_b,void *_c,int _stepa,int _stepc,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V4DMulDEF, 0, _a, _b, _c, _stepa, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]*_b[0];
			_dc[1]=_da[1]*_b[1];
			_dc[2]=_da[2]*_b[2];
			_dc[3]=_da[3]*_b[3];
			pa+=_stepa;
			pc+=_stepc;
		}*/
	}

// ************** array mul with array default function *******************

	void _APICALL _A2FMulDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_AAAADEF((bt::tfSTDCALL_PROC_p_p_p)_V2FMulDEF, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_db=(float*)pb;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]*_db[0];
			_dc[1]=_da[1]*_db[1];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A3FMulDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_AAAADEF((bt::tfSTDCALL_PROC_p_p_p)_V3FMulDEF, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_db=(float*)pb;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]*_db[0];
			_dc[1]=_da[1]*_db[1];
			_dc[2]=_da[2]*_db[2];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A4FMulDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_AAAADEF((bt::tfSTDCALL_PROC_p_p_p)_V4FMulDEF, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_db=(float*)pb;
			float *_dc=(float*)pc;
			_dc[0]=_da[0]*_db[0];
			_dc[1]=_da[1]*_db[1];
			_dc[2]=_da[2]*_db[2];
			_dc[3]=_da[3]*_db[3];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A2DMulDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_AAAADEF((bt::tfSTDCALL_PROC_p_p_p)_V2DMulDEF, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_db=(double*)pb;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]*_db[0];
			_dc[1]=_da[1]*_db[1];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A3DMulDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_AAAADEF((bt::tfSTDCALL_PROC_p_p_p)_V3DMulDEF, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_db=(double*)pb;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]*_db[0];
			_dc[1]=_da[1]*_db[1];
			_dc[2]=_da[2]*_db[2];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A4DMulDEF(void *_a,void *_b,void *_c,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_AAAADEF((bt::tfSTDCALL_PROC_p_p_p)_V4DMulDEF, 0, _a, _b, _c, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_db=(double*)pb;
			double *_dc=(double*)pc;
			_dc[0]=_da[0]*_db[0];
			_dc[1]=_da[1]*_db[1];
			_dc[2]=_da[2]*_db[2];
			_dc[3]=_da[3]*_db[3];
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

// ************** array normal with array default function *******************

	void _APICALL _A2FNormalDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V2FNormalDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_db=(float*)pb;
			double c=1.0/_DsqrtDEF(_da[0]*_da[0]+_da[1]*_da[1]);
			_db[0]=(float)(_da[0]*c);
			_db[1]=(float)(_da[1]*c);
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A3FNormalDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V3FNormalDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_db=(float*)pb;
			double c=1.0/_DsqrtDEF(_da[0]*_da[0]+_da[1]*_da[1]+_da[2]*_da[2]);
			_db[0]=(float)(_da[0]*c);
			_db[1]=(float)(_da[1]*c);
			_db[2]=(float)(_da[2]*c);
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A4FNormalDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V4FNormalDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_db=(float*)pb;
			double c=1.0/_DsqrtDEF(_da[0]*_da[0]+_da[1]*_da[1]+_da[2]*_da[2]+_da[3]*_da[3]);
			_db[0]=(float)(_da[0]*c);
			_db[1]=(float)(_da[1]*c);
			_db[2]=(float)(_da[2]*c);
			_db[3]=(float)(_da[3]*c);
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A2DNormalDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V2DNormalDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_db=(double*)pb;
			double c=1.0/_DsqrtDEF(_da[0]*_da[0]+_da[1]*_da[1]);
			_db[0]=(_da[0]*c);
			_db[1]=(_da[1]*c);
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A3DNormalDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V3DNormalDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_db=(double*)pb;
			double c=1.0/_DsqrtDEF(_da[0]*_da[0]+_da[1]*_da[1]+_da[2]*_da[2]);
			_db[0]=(_da[0]*c);
			_db[1]=(_da[1]*c);
			_db[2]=(_da[2]*c);
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

	void _APICALL _A4DNormalDEF(void *_a,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAADEF((bt::tfSTDCALL_PROC_p_p)_V4DNormalDEF, 0, _a, _b, _stepa, _stepb, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_db=(double*)pb;
			double c=1.0/_DsqrtDEF(_da[0]*_da[0]+_da[1]*_da[1]+_da[2]*_da[2]+_da[3]*_da[3]);
			_db[0]=(_da[0]*c);
			_db[1]=(_da[1]*c);
			_db[2]=(_da[2]*c);
			_db[3]=(_da[3]*c);
			pa+=_stepa;
			pb+=_stepb;
		}*/
	}

// ************** array lerp default function *******************

	void _APICALL _A2FLerpDEF(void *_a,void *_b,void *_c,float _d,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_AAAAFDEF((bt::tfSTDCALL_PROC_p_p_p_float)_V2FLerpDEF, 0, _a, _b, _c, _d, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_db=(float*)pb;
			float *_dc=(float*)pc;
			float r1=_da[0];
			float r2=_da[1];
			float t1=_db[0];
			float t2=_db[1];
			_dc[0]=(t1-r1)*_d+r1;
			_dc[1]=(t2-r2)*_d+r2;
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A3FLerpDEF(void *_a,void *_b,void *_c,float _d,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_AAAAFDEF((bt::tfSTDCALL_PROC_p_p_p_float)_V3FLerpDEF, 0, _a, _b, _c, _d, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_db=(float*)pb;
			float *_dc=(float*)pc;
			float r1=_da[0];
			float r2=_da[1];
			float r3=_da[2];
			float t1=_db[0];
			float t2=_db[1];
			float t3=_db[2];
			_dc[0]=(t1-r1)*_d+r1;
			_dc[1]=(t2-r2)*_d+r2;
			_dc[2]=(t3-r3)*_d+r3;
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A4FLerpDEF(void *_a,void *_b,void *_c,float _d,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		_AAAAFDEF((bt::tfSTDCALL_PROC_p_p_p_float)_V4FLerpDEF, 0, _a, _b, _c, _d, _stepa, _stepb, _stepc, _count);
		/*char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			float *_da=(float*)pa;
			float *_db=(float*)pb;
			float *_dc=(float*)pc;
			float r1=_da[0];
			float r2=_da[1];
			float r3=_da[2];
			float r4=_da[3];
			float t1=_db[0];
			float t2=_db[1];
			float t3=_db[2];
			float t4=_db[3];
			_dc[0]=(t1-r1)*_d+r1;
			_dc[1]=(t2-r2)*_d+r2;
			_dc[2]=(t3-r3)*_d+r3;
			_dc[3]=(t4-r4)*_d+r4;
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}*/
	}

	void _APICALL _A2DLerpDEF(void *_a,void *_b,void *_c,double _d,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_db=(double*)pb;
			double *_dc=(double*)pc;
			double r1=_da[0];
			double r2=_da[1];
			double t1=_db[0];
			double t2=_db[1];
			_dc[0]=(t1-r1)*_d+r1;
			_dc[1]=(t2-r2)*_d+r2;
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}
	}

	void _APICALL _A3DLerpDEF(void *_a,void *_b,void *_c,double _d,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_db=(double*)pb;
			double *_dc=(double*)pc;
			double r1=_da[0];
			double r2=_da[1];
			double r3=_da[2];
			double t1=_db[0];
			double t2=_db[1];
			double t3=_db[2];
			_dc[0]=(t1-r1)*_d+r1;
			_dc[1]=(t2-r2)*_d+r2;
			_dc[2]=(t3-r3)*_d+r3;
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}
	}

	void _APICALL _A4DLerpDEF(void *_a,void *_b,void *_c,double _d,int _stepa,int _stepb,int _stepc,unsigned int _count)
	{
		char *pa=(char*)_a;
		char *pb=(char*)_b;
		char *pc=(char*)_c;
		for (unsigned int i=0;i<_count;i++) {
			double *_da=(double*)pa;
			double *_db=(double*)pb;
			double *_dc=(double*)pc;
			double r1=_da[0];
			double r2=_da[1];
			double r3=_da[2];
			double r4=_da[3];
			double t1=_db[0];
			double t2=_db[1];
			double t3=_db[2];
			double t4=_db[3];
			_dc[0]=(t1-r1)*_d+r1;
			_dc[1]=(t2-r2)*_d+r2;
			_dc[2]=(t3-r3)*_d+r3;
			_dc[3]=(t4-r4)*_d+r4;
			pa+=_stepa;
			pb+=_stepb;
			pc+=_stepc;
		}
	}

// ************** array matrix transform with array default function *******************

	void _APICALL _A2FMatrixTransformDEF(void *_a,void *_matrix,void *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V2FTransformDEF, 0, _a, _matrix, _b, _stepa, _stepb, _count);
		/*float *_matrixa=(float*)_matrix;
		char *s=(char*)_a;
		char *d=(char*)_b;
		while (_count) {
			float *_da=(float*)s;
			float *_db=(float*)d;
			float r1=_da[0]*_matrixa[0]+_da[1]*_matrixa[4]+_matrixa[12];
			float r2=_da[0]*_matrixa[1]+_da[1]*_matrixa[5]+_matrixa[13];
			_db[0]=r1;
			_db[1]=r2;
			s+=_stepa;
			d+=_stepb;
			_count--;
		}*/
	}

	void _APICALL _A3FMatrixTransformDEF(float *_a,void *_matrix,float *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V3FTransformDEF, 0, _a, _matrix, _b, _stepa, _stepb, _count);
		/*float *_matrixa=(float*)_matrix;
		char *s=(char*)_a;
		char *d=(char*)_b;
		while (_count) {
			float r1=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_a[2]*_matrixa[8]+_matrixa[12];
			float r2=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_a[2]*_matrixa[9]+_matrixa[13];
			float r3=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_a[2]*_matrixa[10]+_matrixa[14];
			_b[0]=r1;
			_b[1]=r2;
			_b[2]=r3;
			s+=_stepa;
			d+=_stepb;
			_a=(float*)s;
			_b=(float*)d;
			_count--;
		}*/
	}

	void _APICALL _A4FMatrixTransformDEF(float *_a,void *_matrix,float *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V4FTransformDEF, 0, _a, _matrix, _b, _stepa, _stepb, _count);
		/*float *_matrixa=(float*)_matrix;
		char *s=(char*)_a;
		char *d=(char*)_b;
		while (_count) {
			float r1=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_a[2]*_matrixa[8]+_a[3]*_matrixa[12];
			float r2=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_a[2]*_matrixa[9]+_a[3]*_matrixa[13];
			float r3=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_a[2]*_matrixa[10]+_a[3]*_matrixa[14];
			float r4=_a[0]*_matrixa[3]+_a[1]*_matrixa[7]+_a[2]*_matrixa[11]+_a[3]*_matrixa[15];
			_b[0]=r1;
			_b[1]=r2;
			_b[2]=r3;
			_b[3]=r4;
			s+=_stepa;
			d+=_stepb;
			_a=(float*)s;
			_b=(float*)d;
			_count--;
		}*/
	}

	void _APICALL _A2DMatrixTransformDEF(double *_a,void *_matrix,double *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V2DTransformDEF, 0, _a, _matrix, _b, _stepa, _stepb, _count);
		/*double *_matrixa=(double*)_matrix;
		char *s=(char*)_a;
		char *d=(char*)_b;
		while (_count) {
			double r1=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_matrixa[12];
			double r2=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_matrixa[13];
			_b[0]=r1;
			_b[1]=r2;
			s+=_stepa;
			d+=_stepb;
			_a=(double*)s;
			_b=(double*)d;
			_count--;
		}*/
	}

	void _APICALL _A3DMatrixTransformDEF(double *_a,void *_matrix,double *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V3DTransformDEF, 0, _a, _matrix, _b, _stepa, _stepb, _count);
		/*double *_matrixa=(double*)_matrix;
		char *s=(char*)_a;
		char *d=(char*)_b;
		while (_count) {
			double r1=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_a[2]*_matrixa[8]+_matrixa[12];
			double r2=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_a[2]*_matrixa[9]+_matrixa[13];
			double r3=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_a[2]*_matrixa[10]+_matrixa[14];
			_b[0]=r1;
			_b[1]=r2;
			_b[2]=r3;
			s+=_stepa;
			d+=_stepb;
			_a=(double*)s;
			_b=(double*)d;
			_count--;
		}*/
	}

	void _APICALL _A4DMatrixTransformDEF(double *_a,void *_matrix,double *_b,int _stepa,int _stepb,unsigned int _count)
	{
		_AAPADEF((bt::tfSTDCALL_PROC_p_p_p)_V4DTransformDEF, 0, _a, _matrix, _b, _stepa, _stepb, _count);
		/*double *_matrixa=(double*)_matrix;
		char *s=(char*)_a;
		char *d=(char*)_b;
		while (_count) {
			double r1=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_a[2]*_matrixa[8]+_a[3]*_matrixa[12];
			double r2=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_a[2]*_matrixa[9]+_a[3]*_matrixa[13];
			double r3=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_a[2]*_matrixa[10]+_a[3]*_matrixa[14];
			double r4=_a[0]*_matrixa[3]+_a[1]*_matrixa[7]+_a[2]*_matrixa[11]+_a[3]*_matrixa[15];
			_b[0]=r1;
			_b[1]=r2;
			_b[2]=r3;
			_b[3]=r4;
			s+=_stepa;
			d+=_stepb;
			_a=(double*)s;
			_b=(double*)d;
			_count--;
		}*/
	}

// ************** array proj with array default function *******************

	void _APICALL _A2FProjDEF(float *_a,void *_b,float *_c,float *_d,float *_e,int _stepa,int _stepe,int _flagoff,unsigned int _count)
	{
		float *_matrixa=(float*)_b;
		char *s=(char*)_a;
		char *d=(char*)_e;
		int *pflag=(int*)(((char*)_e)+(int)_flagoff);
//		float r[5];
		while (_count) {
			*pflag = _V2FProjDEF(_a, _matrixa, _c, _d, _e);
			/*r[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_matrixa[12];
			r[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_matrixa[13];
			r[2]=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_matrixa[14];
			r[3]=_a[0]*_matrixa[3]+_a[1]*_matrixa[7]+_matrixa[15];
			r[4]=-r[3];
			int flag=0;
			if (r[0]>r[3]) flag|=0x01;
			if (r[1]>r[3]) flag|=0x02;
			if (r[2]>r[3]) flag|=0x04;
			if (r[0]<r[4]) flag|=0x10;
			if (r[1]<r[4]) flag|=0x20;
			if (r[2]<r[4]) flag|=0x40;
			if ((r[3]!=0) && (r[3]!=1.0)) {
				r[3]=1.0f/r[3];
				r[0]=r[0]*r[3];
				r[1]=r[1]*r[3];
				r[2]=r[2]*r[3];
			}
			_e[0]=r[0]*_c[0]+_d[0];
			_e[1]=r[1]*_c[1]+_d[1];
			_e[2]=r[2]*_c[2]+_d[2];
			_e[3]=r[3];
			*pflag=flag;*/

			s+=_stepa;
			d+=_stepe;
			pflag=(int*)(((char*)pflag)+_stepe);
			_a=(float*)s;
			_e=(float*)d;
			_count--;
		}
	}

	void _APICALL _A3FProjDEF(float *_a,void *_b,float *_c,float *_d,float *_e,int _stepa,int _stepe,int _flagoff,unsigned int _count)
	{
		float *_matrixa=(float*)_b;
		char *s=(char*)_a;
		char *d=(char*)_e;
		int *pflag=(int*)(((char*)_e)+(int)_flagoff);
//		float r[5];
		while (_count) {
			*pflag = _V3FProjDEF(_a, _matrixa, _c, _d, _e);
			/*r[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_a[2]*_matrixa[8]+_matrixa[12];
			r[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_a[2]*_matrixa[9]+_matrixa[13];
			r[2]=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_a[2]*_matrixa[10]+_matrixa[14];
			r[3]=_a[0]*_matrixa[3]+_a[1]*_matrixa[7]+_a[2]*_matrixa[11]+_matrixa[15];
			r[4]=-r[3];
			int flag=0;
			if (r[0]>r[3]) flag|=0x01;
			if (r[1]>r[3]) flag|=0x02;
			if (r[2]>r[3]) flag|=0x04;
			if (r[0]<r[4]) flag|=0x10;
			if (r[1]<r[4]) flag|=0x20;
			if (r[2]<r[4]) flag|=0x40;
			if ((r[3]!=0) && (r[3]!=1.0)) {
				r[3]=1.0f/r[3];
				r[0]=r[0]*r[3];
				r[1]=r[1]*r[3];
				r[2]=r[2]*r[3];
			}
			_e[0]=r[0]*_c[0]+_d[0];
			_e[1]=r[1]*_c[1]+_d[1];
			_e[2]=r[2]*_c[2]+_d[2];
			_e[3]=r[3];
			*pflag=flag;*/

			s+=_stepa;
			d+=_stepe;
			pflag=(int*)(((char*)pflag)+_stepe);
			_a=(float*)s;
			_e=(float*)d;
			_count--;
		}
	}

	void _APICALL _A4FProjDEF(float *_a,void *_b,float *_c,float *_d,float *_e,int _stepa,int _stepe,int _flagoff,unsigned int _count)
	{
		float *_matrixa=(float*)_b;
		char *s=(char*)_a;
		char *d=(char*)_e;
		int *pflag=(int*)(((char*)_e)+(int)_flagoff);
//		float r[5];
		while (_count) {
			*pflag = _V4FProjDEF(_a, _matrixa, _c, _d, _e);
			/*r[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_a[2]*_matrixa[8]+_a[3]*_matrixa[12];
			r[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_a[2]*_matrixa[9]+_a[3]*_matrixa[13];
			r[2]=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_a[2]*_matrixa[10]+_a[3]*_matrixa[14];
			r[3]=_a[0]*_matrixa[3]+_a[1]*_matrixa[7]+_a[2]*_matrixa[11]+_a[3]*_matrixa[15];
			r[4]=-r[3];
			int flag=0;
			if (r[0]>r[3]) flag|=0x01;
			if (r[1]>r[3]) flag|=0x02;
			if (r[2]>r[3]) flag|=0x04;
			if (r[0]<r[4]) flag|=0x10;
			if (r[1]<r[4]) flag|=0x20;
			if (r[2]<r[4]) flag|=0x40;
			if ((r[3]!=0) && (r[3]!=1.0)) {
				r[3]=1.0f/r[3];
				r[0]=r[0]*r[3];
				r[1]=r[1]*r[3];
				r[2]=r[2]*r[3];
			}
			_e[0]=r[0]*_c[0]+_d[0];
			_e[1]=r[1]*_c[1]+_d[1];
			_e[2]=r[2]*_c[2]+_d[2];
			_e[3]=r[3];
			*pflag=flag;*/

			s+=_stepa;
			d+=_stepe;
			pflag=(int*)(((char*)pflag)+_stepe);
			_a=(float*)s;
			_e=(float*)d;
			_count--;
		}
	}

	void _APICALL _A2DProjDEF(double *_a,void *_b,double *_c,double *_d,double *_e,int _stepa,int _stepe,int _flagoff,unsigned int _count)
	{
		double *_matrixa=(double*)_b;
		char *s=(char*)_a;
		char *d=(char*)_e;
		int *pflag=(int*)(((char*)_e)+(int)_flagoff);
//		double r[5];
		while (_count) {
			*pflag = _V2DProjDEF(_a, _matrixa, _c, _d, _e);
			/*r[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_matrixa[12];
			r[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_matrixa[13];
			r[2]=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_matrixa[14];
			r[3]=_a[0]*_matrixa[3]+_a[1]*_matrixa[7]+_matrixa[15];
			r[4]=-r[3];
			int flag=0;
			if (r[0]>r[3]) flag|=0x01;
			if (r[1]>r[3]) flag|=0x02;
			if (r[2]>r[3]) flag|=0x04;
			if (r[0]<r[4]) flag|=0x10;
			if (r[1]<r[4]) flag|=0x20;
			if (r[2]<r[4]) flag|=0x40;
			if ((r[3]!=0) && (r[3]!=1.0)) {
				r[3]=1.0f/r[3];
				r[0]=r[0]*r[3];
				r[1]=r[1]*r[3];
				r[2]=r[2]*r[3];
			}
			_e[0]=r[0]*_c[0]+_d[0];
			_e[1]=r[1]*_c[1]+_d[1];
			_e[2]=r[2]*_c[2]+_d[2];
			_e[3]=r[3];
			*pflag=flag;*/

			s+=_stepa;
			d+=_stepe;
			pflag=(int*)(((char*)pflag)+_stepe);
			_a=(double*)s;
			_e=(double*)d;
			_count--;
		}
	}

	void _APICALL _A3DProjDEF(double *_a,void *_b,double *_c,double *_d,double *_e,int _stepa,int _stepe,int _flagoff,unsigned int _count)
	{
		double *_matrixa=(double*)_b;
		char *s=(char*)_a;
		char *d=(char*)_e;
		int *pflag=(int*)(((char*)_e)+(int)_flagoff);
//		double r[5];
		while (_count) {
			*pflag = _V3DProjDEF(_a, _matrixa, _c, _d, _e);
			/*r[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_a[2]*_matrixa[8]+_matrixa[12];
			r[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_a[2]*_matrixa[9]+_matrixa[13];
			r[2]=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_a[2]*_matrixa[10]+_matrixa[14];
			r[3]=_a[0]*_matrixa[3]+_a[1]*_matrixa[7]+_a[2]*_matrixa[11]+_matrixa[15];
			r[4]=-r[3];
			int flag=0;
			if (r[0]>r[3]) flag|=0x01;
			if (r[1]>r[3]) flag|=0x02;
			if (r[2]>r[3]) flag|=0x04;
			if (r[0]<r[4]) flag|=0x10;
			if (r[1]<r[4]) flag|=0x20;
			if (r[2]<r[4]) flag|=0x40;
			if ((r[3]!=0) && (r[3]!=1.0)) {
				r[3]=1.0f/r[3];
				r[0]=r[0]*r[3];
				r[1]=r[1]*r[3];
				r[2]=r[2]*r[3];
			}
			_e[0]=r[0]*_c[0]+_d[0];
			_e[1]=r[1]*_c[1]+_d[1];
			_e[2]=r[2]*_c[2]+_d[2];
			_e[3]=r[3];
			*pflag=flag;*/

			s+=_stepa;
			d+=_stepe;
			pflag=(int*)(((char*)pflag)+_stepe);
			_a=(double*)s;
			_e=(double*)d;
			_count--;
		}
	}

	void _APICALL _A4DProjDEF(double *_a,void *_b,double *_c,double *_d,double *_e,int _stepa,int _stepe,int _flagoff,unsigned int _count)
	{
		double *_matrixa=(double*)_b;
		char *s=(char*)_a;
		char *d=(char*)_e;
		int *pflag=(int*)(((char*)_e)+(int)_flagoff);
//		double r[5];
		while (_count) {
			*pflag = _V4DProjDEF(_a, _matrixa, _c, _d, _e);
			/*r[0]=_a[0]*_matrixa[0]+_a[1]*_matrixa[4]+_a[2]*_matrixa[8]+_a[3]*_matrixa[12];
			r[1]=_a[0]*_matrixa[1]+_a[1]*_matrixa[5]+_a[2]*_matrixa[9]+_a[3]*_matrixa[13];
			r[2]=_a[0]*_matrixa[2]+_a[1]*_matrixa[6]+_a[2]*_matrixa[10]+_a[3]*_matrixa[14];
			r[3]=_a[0]*_matrixa[3]+_a[1]*_matrixa[7]+_a[2]*_matrixa[11]+_a[3]*_matrixa[15];
			r[4]=-r[3];
			int flag=0;
			if (r[0]>r[3]) flag|=0x01;
			if (r[1]>r[3]) flag|=0x02;
			if (r[2]>r[3]) flag|=0x04;
			if (r[0]<r[4]) flag|=0x10;
			if (r[1]<r[4]) flag|=0x20;
			if (r[2]<r[4]) flag|=0x40;
			if ((r[3]!=0) && (r[3]!=1.0)) {
				r[3]=1.0f/r[3];
				r[0]=r[0]*r[3];
				r[1]=r[1]*r[3];
				r[2]=r[2]*r[3];
			}
			_e[0]=r[0]*_c[0]+_d[0];
			_e[1]=r[1]*_c[1]+_d[1];
			_e[2]=r[2]*_c[2]+_d[2];
			_e[3]=r[3];
			*pflag=flag;*/

			s+=_stepa;
			d+=_stepe;
			pflag=(int*)(((char*)pflag)+_stepe);
			_a=(double*)s;
			_e=(double*)d;
			_count--;
		}
	}

	// ************** array Zooming by Spline Catmul Rome default function *******************

	unsigned int _FASTCALL _startvaluesLoopCR(void **vals,void *first,char *b,int step,unsigned int index,unsigned int max)
	{
		vals[0]=(void*)(b-step);
		if (index<=0) vals[0]=(void*)(b+step*(max-1));
		vals[1]=(void*)b;
		b+=step;
		index++;
		if (index>=max) {
			b=(char*)first;
			index=0;
		}
		vals[2]=(void*)b;
		b+=step;
		index++;
		if (index>=max) {
			b=(char*)first;
			index=0;
		}
		vals[3]=(void*)b;
		return index;
	}

	void _FASTCALL _AFZoomSplineCRLoopANY(float *_a,float *_b,int _stepa,int _stepb,double spstart,float spStep,unsigned int _counta,unsigned int _count,bt::tfSTDCALL_PROC_p_p cc,bt::tfSTDCALL_PROC_p_p_float_float rc)
	{
		unsigned int index = matFunctions.FTrunc(spstart);
		spstart-=index;
		index=(index%_counta);
		char *s=(char*)_a;
		char *d=(char*)_b;
		s+=index*_stepa;
		void *val[4];
		index=_startvaluesLoopCR(val,_a,s,_stepa,index,_counta);
		s=(char*)_a;
		s+=index*_stepa;
		float c[16];
		while (_count) {
			cc(val,c);
			while (_count && spstart<1.0) {
				rc(c,_b,spstart,0.5f);
				spstart+=spStep;
				d+=_stepb;
				_b=(float*)d;
				_count--;
			}
			spstart-=1.0;
			val[0]=val[1];
			val[1]=val[2];
			val[2]=val[3];
			index++;
			s+=_stepa;
			if (index>=_counta) {
				s=(char*)_a;
				index=0;
			}
			val[3]=(void*)s;
		}
	}

	void _FASTCALL _ADZoomSplineCRLoopANY(double *_a,double *_b,int _stepa,int _stepb,double spstart,float spStep,unsigned int _counta,unsigned int _count,bt::tfSTDCALL_PROC_p_p cc,bt::tfSTDCALL_PROC_p_p_double_double rc)
	{
		unsigned int index=matFunctions.DTrunc(spstart);
		spstart-=index;
		index=(index%_counta);
		char *s=(char*)_a;
		char *d=(char*)_b;
		s+=index*_stepa;
		void *val[4];
		index=_startvaluesLoopCR(val,_a,s,_stepa,index,_counta);
		s=(char*)_a;
		s+=index*_stepa;
		double c[16];
		while (_count) {
			cc(val,c);
			while (_count && spstart<1.0) {
				rc(c,_b,spstart,0.5);
				spstart+=spStep;
				d+=_stepb;
				_b=(double*)d;
				_count--;
			}
			spstart-=1.0;
			val[0]=val[1];
			val[1]=val[2];
			val[2]=val[3];
			index++;
			s+=_stepa;
			if (index>=_counta) {
				s=(char*)_a;
				index=0;
			}
			val[3]=(void*)s;
		}
	}

	unsigned int _FASTCALL _startvaluesCR(void **vals,void *,char *b,int step,unsigned int index,unsigned int max)
	{
		vals[0]=(void*)(b-step);
		if (index<=0) vals[0]=(void*)b;
		vals[1]=(void*)b;
		b+=step;
		index++;
		if (index>=max) {
			b-=step;
			index=max-1;
		}
		vals[2]=(void*)b;
		b+=step;
		index++;
		if (index>=max) {
			b-=step;
			index=max-1;
		}
		vals[3]=(void*)b;
		return index;
	}

	void _FASTCALL _AFZoomSplineCRTrucANY(void *_a, void *_b, int _stepa, int _stepb, double spstart, float spStep, unsigned int _counta, unsigned int _count, bt::tfSTDCALL_PROC_p_p cc, bt::tfSTDCALL_PROC_p_p_float_float rc)
	{
		unsigned int index = matFunctions.FTrunc(spstart);
		spstart-=index;
		index=(index%_counta);
		char *s=(char*)_a;
		char *d=(char*)_b;
		s+=index*_stepa;
		void *val[4];
		index=_startvaluesCR(val,_a,s,_stepa,index,_counta);
		s=(char*)_a;
		s+=index*_stepa;
		float c[16];
		while (_count) {
			cc(val,c);
			while (_count && spstart<1.0) {
				rc(c,_b,spstart,0.5f);
				spstart+=spStep;
				d+=_stepb;
				_b = (void*)d;
				_count--;
			}
			spstart-=1.0;
			val[0]=val[1];
			val[1]=val[2];
			val[2]=val[3];
			index++;
			s+=_stepa;
			if (index>=_counta) {
				s-=_stepa;
				index=_counta-1;
			}
			val[3]=(void*)s;
		}
	}

	void _FASTCALL _ADZoomSplineCRTrucANY(void *_a, void *_b, int _stepa, int _stepb, double spstart, float spStep, unsigned int _counta, unsigned int _count, bt::tfSTDCALL_PROC_p_p cc, bt::tfSTDCALL_PROC_p_p_double_double rc)
	{
		unsigned int index = matFunctions.DTrunc(spstart);
		spstart-=index;
		index=(index%_counta);
		char *s=(char*)_a;
		char *d=(char*)_b;
		s+=index*_stepa;
		void *val[4];
		index=_startvaluesCR(val,_a,s,_stepa,index,_counta);
		s=(char*)_a;
		s+=index*_stepa;
		double c[16];
		while (_count) {
			cc(val,c);
			while (_count && spstart<1.0) {
				rc(c,_b,spstart,0.5);
				spstart+=spStep;
				d+=_stepb;
				_b=(void*)d;
				_count--;
			}
			spstart-=1.0;
			val[0]=val[1];
			val[1]=val[2];
			val[2]=val[3];
			index++;
			s+=_stepa;
			if (index>=_counta) {
				s-=_stepa;
				index=_counta-1;
			}
			val[3]=(void*)s;
		}
	}

	void _APICALL _AFZoomSplineCRDEF(float *_a,float *_b,int _stepa,int _stepb,double spstart,float spStep,unsigned int flag,unsigned int _counta,unsigned int _count)
	{
		if (flag) {
			_AFZoomSplineCRLoopANY(_a,_b,_stepa,_stepb,spstart,spStep,_counta,_count,matFunctions.FPCRCC,matFunctions.FSplineCR);
		} else {
			_AFZoomSplineCRTrucANY(_a,_b,_stepa,_stepb,spstart,spStep,_counta,_count,matFunctions.FPCRCC,matFunctions.FSplineCR);
		}
	}

	void _APICALL _A2FZoomSplineCRDEF(float *_a,float *_b,int _stepa,int _stepb,double spstart,float spStep,unsigned int flag,unsigned int _counta,unsigned int _count)
	{
		if (flag) {
			_AFZoomSplineCRLoopANY(_a,_b,_stepa,_stepb,spstart,spStep,_counta,_count,extFunctions.V2FPCRCC,extFunctions.V2FSplineCR);
		} else {
			_AFZoomSplineCRTrucANY(_a,_b,_stepa,_stepb,spstart,spStep,_counta,_count,extFunctions.V2FPCRCC,extFunctions.V2FSplineCR);
		}
	}

	void _APICALL _A3FZoomSplineCRDEF(float *_a,float *_b,int _stepa,int _stepb,double spstart,float spStep,unsigned int flag,unsigned int _counta,unsigned int _count)
	{
		if (flag) {
			_AFZoomSplineCRLoopANY(_a,_b,_stepa,_stepb,spstart,spStep,_counta,_count,extFunctions.V3FPCRCC,extFunctions.V3FSplineCR);
		} else {
			_AFZoomSplineCRTrucANY(_a,_b,_stepa,_stepb,spstart,spStep,_counta,_count,extFunctions.V3FPCRCC,extFunctions.V3FSplineCR);
		}
	}

	void _APICALL _A4FZoomSplineCRDEF(float *_a,float *_b,int _stepa,int _stepb,double spstart,float spStep,unsigned int flag,unsigned int _counta,unsigned int _count)
	{
		if (flag) {
			_AFZoomSplineCRLoopANY(_a,_b,_stepa,_stepb,spstart,spStep,_counta,_count,extFunctions.V4FPCRCC,extFunctions.V4FSplineCR);
		} else {
			_AFZoomSplineCRTrucANY(_a,_b,_stepa,_stepb,spstart,spStep,_counta,_count,extFunctions.V4FPCRCC,extFunctions.V4FSplineCR);
		}
	}

	void _APICALL _ADZoomSplineCRDEF(double *_a,double *_b,int _stepa,int _stepb,double spstart,float spStep,unsigned int flag,unsigned int _counta,unsigned int _count)
	{
		if (flag) {
			_ADZoomSplineCRLoopANY(_a,_b,_stepa,_stepb,spstart,spStep,_counta,_count,matFunctions.DPCRCC,matFunctions.DSplineCR);
		} else {
			_ADZoomSplineCRTrucANY(_a,_b,_stepa,_stepb,spstart,spStep,_counta,_count,matFunctions.DPCRCC,matFunctions.DSplineCR);
		}
	}

	void _APICALL _A2DZoomSplineCRDEF(double *_a,double *_b,int _stepa,int _stepb,double spstart,float spStep,unsigned int flag,unsigned int _counta,unsigned int _count)
	{
		if (flag) {
			_ADZoomSplineCRLoopANY(_a,_b,_stepa,_stepb,spstart,spStep,_counta,_count,extFunctions.V2DPCRCC,extFunctions.V2DSplineCR);
		} else {
			_ADZoomSplineCRTrucANY(_a,_b,_stepa,_stepb,spstart,spStep,_counta,_count,extFunctions.V2DPCRCC,extFunctions.V2DSplineCR);
		}
	}

	void _APICALL _A3DZoomSplineCRDEF(double *_a,double *_b,int _stepa,int _stepb,double spstart,float spStep,unsigned int flag,unsigned int _counta,unsigned int _count)
	{
		if (flag) {
			_ADZoomSplineCRLoopANY(_a,_b,_stepa,_stepb,spstart,spStep,_counta,_count,extFunctions.V3DPCRCC,extFunctions.V3DSplineCR);
		} else {
			_ADZoomSplineCRTrucANY(_a,_b,_stepa,_stepb,spstart,spStep,_counta,_count,extFunctions.V3DPCRCC,extFunctions.V3DSplineCR);
		}
	}

	void _APICALL _A4DZoomSplineCRDEF(double *_a,double *_b,int _stepa,int _stepb,double spstart,float spStep,unsigned int flag,unsigned int _counta,unsigned int _count)
	{
		if (flag) {
			_ADZoomSplineCRLoopANY(_a,_b,_stepa,_stepb,spstart,spStep,_counta,_count,extFunctions.V4DPCRCC,extFunctions.V4DSplineCR);
		} else {
			_ADZoomSplineCRTrucANY(_a,_b,_stepa,_stepb,spstart,spStep,_counta,_count,extFunctions.V4DPCRCC,extFunctions.V4DSplineCR);
		}
	}

};

OPTIMIZE_OFF;
WARNING_ENABLE;
