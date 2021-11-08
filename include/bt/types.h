//=============================================================================
///**
// *  @file types.h
// *
// *  $Id: types.h 23.05.2012  $
// *
// *  @brief generator 3, MS Visual C++ 2003-2008
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#pragma once
#ifndef GEN3_TYPES_H
#define GEN3_TYPES_H

#include <bt/typesproc.h>
#include <bt/basetypes.h>

#ifdef __cplusplus
namespace bt {
#endif

	struct sBaseTypesData {
		void * Procedure;
		void * Function;
		void * PVoid;
		void * Bool;
		void * PChar;
		void * Int;
		void * Long;
		void * Float;
		void * Double;
	};

/**
 * @class sFunctionsAPICPU
 *
 * @ingroup apiinterface
 * @brief sFunctionsAPICPU -
 *
 * @see math, apiinterface
 */

	struct sFunctionsAPICPU {
		_int32 version;

		/// Time Stamp Counter
		/// @return tacts.
		tfSTDCALL_long_FUNC TSC;
		/// CPU flag
		/// @return system CPU flag
		tfSTDCALL_uint_FUNC FlagCPU;

		tfSTDCALL_p_FUNC StringCPU;

		tfSTDCALL_PROC_uint InitFunc;

		tfSTDCALL_PROC ResetFunc;
	};

/**
 * @class sFunctionsMathCPU
 *
 * @ingroup apiinterface
 * @brief sFunctionsMathCPU - numerical mathematical functions
 *
 * @see math, apiinterface
 */
	struct sFunctionsMathCPU {
		_int32 version;
		/// Square root (fsqrt).
		/// @param arg - the number.
		/// @return the Square root.
		tfSTDCALL_float_FUNC_float FSqrt;
		/// The square root of a double precision (dsqrt).
		/// @param arg - the number.
		/// @return the Square root.
		tfSTDCALL_double_FUNC_double DSqrt;

		/// Fast inverse square root with loss of precision
		/// @param arg the number.
		/// @return the inverse square root.
		tfSTDCALL_float_FUNC_float FFastInvSqrt;
		/// Fast inverse square root double precision precision will be lost
		/// @param arg - the number.
		/// @return the inverse square root.
		tfSTDCALL_double_FUNC_double DFastInvSqrt;

		tfSTDCALL_float_FUNC_float FSin;
		tfSTDCALL_float_FUNC_float FCos;

		/// Calculate sine and cosine (fsincos).
		/// @param arg1 - the angle in radians.
		/// @param arg2 - is a pointer to the result of the cosine.
		/// @param arg3 - pointer to the sine.
		tfSTDCALL_PROC_float_p_p FSinCos;
		/// Calculate sine and cosine double-precision (dsincos).
		/// @param arg1 - the angle in radians.
		/// @param arg2 - is a pointer to the result of the cosine.
		/// @param arg3 - pointer to the sine.
		tfSTDCALL_PROC_double_p_p DSinCos;

		/// Calculate sine and cosine with loss of precision
		/// @param arg1 - the angle in radians.
		/// @param arg2 - is a pointer to the result of the cosine.
		/// @param arg3 - pointer to the sine.
		tfSTDCALL_PROC_float_p_p FFastSinCos;
		/// Calculate sine and cosine double-precision precision loss
		/// @param arg1 - the angle in radians.
		/// @param arg2 - is a pointer to the result of the cosine.
		/// @param arg3 - pointer to the sine.
		tfSTDCALL_PROC_double_p_p DFastSinCos;

		/// Arc tangent of a/b (farctg).
		/// @param arg1 - the sinus.
		/// @param arg2 - cosine.
		/// @return the arc tangent.
		tfSTDCALL_float_FUNC_float_float FArcTg;
		/// Arc tangent of a/b double-precision (darctg).
		/// @param arg1 - the sinus.
		/// @param arg2 - cosine.
		/// @return the arc tangent.
		tfSTDCALL_double_FUNC_double_double DArcTg;

		/// multiply the number by 2 to the power N
		/// @param arg1 - number.
		/// @param arg2 - �������.
		/// @return arg1*(2^arg2).
		tfSTDCALL_float_FUNC_float_int Fmul2N;
		/// multiply the number by 2 to the power N double precision
		/// @param arg1 - �����.
		/// @param arg2 - �������.
		/// @return arg1*(2^arg2).
		tfSTDCALL_double_FUNC_double_int Dmul2N;

		/// interpolation
		/// @param arg1 - number.
		/// @param arg2 - number.
		/// @param arg3 - factor.
		/// @return (arg2-arg1)*arg3+arg1.
		tfSTDCALL_float_FUNC_float_float_float FLerp;
		/// Interpolation double precision
		/// @param arg1 - number.
		/// @param arg2 - number.
		/// @param arg3 - factor.
		/// @return (arg2-arg1)*arg3+arg1.
		tfSTDCALL_double_FUNC_double_double_double DLerp;

		/// Transfer to an integer, truncation of the fractional part
		/// @param arg1 - the number format in floating point.
		/// @return integer number.
		tfSTDCALL_int_FUNC_float FTrunc;
		/// Transfer to an integer, truncation of the fractional part
		/// @param arg1 - the number format in floating point double precision.
		/// @return integer number.
		tfSTDCALL_int_FUNC_double DTrunc;

		/// ������� � �����, ���������� �������� ���������� ���������� (MXCSR)
		/// @return ����� �����.
		tfSTDCALL_int_FUNC_float FRound;
		/// ������� � �����, ���������� �������� ���������� ���������� (MXCSR)
		/// @return ����� �����.
		tfSTDCALL_int_FUNC_double DRound;

		tfSTDCALL_float_FUNC_int IToF;
		tfSTDCALL_double_FUNC_long LToD;

		/// �������������� ����� � ��������� ������ � ��������� ���������� ������� �����
		tfSTDCALL_int_FUNC_float_int Fmul2NTrunc;
		/// �������������� ����� � ��������� ������ ������� �������� � ��������� ���������� ������� �����
		tfSTDCALL_int_FUNC_double_int Dmul2NTrunc;

		/// �������������� ����� � ��������� ������ � ��������� �������� ���������� ���������� (MXCSR)
		tfSTDCALL_int_FUNC_float_int Fmul2NRound;
		/// �������������� ����� � ��������� ������ ������� �������� � ��������� �������� ���������� ���������� (MXCSR)
		tfSTDCALL_int_FUNC_double_int Dmul2NRound;

		tfSTDCALL_float_FUNC_float_float FScaleMod;
		tfSTDCALL_double_FUNC_double_double DScaleMod;

		/// Calculation of coefficientof spline Catala Roma (x1 x2 x3 x4 rez[4]).
		tfSTDCALL_PROC_float_float_float_float_p FCRCC;
		/// Calculation of coefficientof spline Catala Roma (x1 x2 x3 x4 rez[4]).
		tfSTDCALL_PROC_double_double_double_double_p DCRCC;
		/// Calculation of coefficientof spline Catala Roma (x1 x2 x3 x4 rez[4]).
		tfSTDCALL_PROC_p_p FPCRCC;
		/// Calculation of coefficientof spline Catala Roma (x1 x2 x3 x4 rez[4]).
		tfSTDCALL_PROC_p_p DPCRCC;

		/// ���������� �������� ������� ������� ���� (c[4] x frac force).
		tfSTDCALL_PROC_p_p_float_float FSplineCR;
		/// ���������� �������� ������� ������� ���� (c[4] x frac force).
		tfSTDCALL_PROC_p_p_double_double DSplineCR;

		/// exponent
		tfSTDCALL_float_FUNC_float FExp;
		/// exponent
		tfSTDCALL_double_FUNC_double DExp;

		/// �������� �� ��������� 2, ���������� flog2
		tfSTDCALL_float_FUNC_float FLog2;
		/// �������� �� ��������� 2 ������� ��������, ���������� dlog2
		tfSTDCALL_double_FUNC_double DLog2;
		/// ������������� �������� �� ��������� 2, ���������� ilog2
		tfSTDCALL_int_FUNC_int ILog2;
		/// ������������� �������� �� ��������� 2
		tfSTDCALL_int_FUNC_long LLog2;

		/// �������
		tfSTDCALL_float_FUNC_p_uint_float FPoly1;
		/// ������� ������� ��������
		tfSTDCALL_double_FUNC_p_uint_double DPoly1;
		/// ������� ���� ���������� (const1, maxpow2, maxpow3, val4, val5)
		tfSTDCALL_float_FUNC_p_uint_uint_float_float FPoly2;
		/// ������� ������� �������� ���� ���������� (const1,maxpow2,maxpow3,val4,val5)
		tfSTDCALL_double_FUNC_p_uint_uint_double_double DPoly2;
		/// ������� ��������� ����������
		tfSTDCALL_float_FUNC_p_p_p_uint FPolyM;
		/// ������� ������� �������� ��������� ����������
		tfSTDCALL_double_FUNC_p_p_p_uint DPolyM;

		tfSTDCALL_PROC_p_p_p FMinMax;
		tfSTDCALL_PROC_p_p_p DMinMax;
	};

	/**
	 * @class sFunctionsVectorCPU
	 *
	 * @ingroup apiinterface
	 * @brief sFunctionsVectorCPU - vector mathematical functions
	 *
	 * @see math, apiinterface
	 */

	struct sFunctionsVectorCPU {
		_int32 version;
		/// Reverse byte order
		/// @param arg1 - the source pointer of 4 bytes.
		/// @param arg2 - is a pointer receiver 4 bytes.
		tfSTDCALL_PROC_p_p V4R8;
		/// Reverse the sequence of words
		/// @param arg1 - ��������� ��������� 8 ����.
		/// @param arg2 - ��������� ��������� 8 ����.
		tfSTDCALL_PROC_p_p V4R16;
		/// Reverse sequence of double words
		/// @param arg1 - ��������� ��������� 16 ����.
		/// @param arg2 - ��������� ��������� 16 ����.
		tfSTDCALL_PROC_p_p V4R32;
		/// The reverse sequence Quad words
		/// @param arg1 - ��������� ��������� 32 �����.
		/// @param arg2 - ��������� ��������� 32 �����.
		tfSTDCALL_PROC_p_p V4R64;

		tfSTDCALL_PROC_p_p V2R32Copy;
		tfSTDCALL_PROC_p_p V3R32Copy;
		tfSTDCALL_PROC_p_p V4R32Copy;
		tfSTDCALL_PROC_p_p V2R64Copy;
		tfSTDCALL_PROC_p_p V3R64Copy;
		tfSTDCALL_PROC_p_p V4R64Copy;

		/// ��������������� char �� float
		/// @param arg1 - ��������� ��������� 2 �����.
		/// @param arg2 - ��������� ��������� 8 ����.
		tfSTDCALL_PROC_p_p V2BTo2F;
		/// ��������������� char �� double
		/// @param arg1 - ��������� ��������� 2 �����.
		/// @param arg2 - ��������� ��������� 16 ����.
		tfSTDCALL_PROC_p_p V2BTo2D;
		/// ��������������� char �� float
		/// @param arg1 - ��������� ��������� 3 �����.
		/// @param arg2 - ��������� ��������� 12 ����.
		tfSTDCALL_PROC_p_p V3BTo3F;
		/// ��������������� char �� double
		/// @param arg1 - ��������� ��������� 3 �����.
		/// @param arg2 - ��������� ��������� 24 �����.
		tfSTDCALL_PROC_p_p V3BTo3D;
		/// ��������������� char �� float
		/// @param arg1 - ��������� ��������� 4 �����.
		/// @param arg2 - ��������� ��������� 16 ����.
		tfSTDCALL_PROC_p_p V4BTo4F;
		/// ��������������� char �� double
		/// @param arg1 - ��������� ��������� 4 �����.
		/// @param arg2 - ��������� ��������� 32 �����.
		tfSTDCALL_PROC_p_p V4BTo4D;
		/// ��������������� int �� char
		tfSTDCALL_PROC_p_p V4ITo4B;
		/// ��������������� int �� float
		tfSTDCALL_PROC_p_p V2ITo2F;
		/// ��������������� int �� double
		tfSTDCALL_PROC_p_p V2ITo2D;
		/// ��������������� int �� float
		tfSTDCALL_PROC_p_p V3ITo3F;
		/// ��������������� int �� double
		tfSTDCALL_PROC_p_p V3ITo3D;
		/// ��������������� int �� float
		tfSTDCALL_PROC_p_p V4ITo4F;
		/// ��������������� int �� double
		tfSTDCALL_PROC_p_p V4ITo4D;
		/// ���������� double � char
		tfSTDCALL_PROC_p_p V2FTo2B;
		/// ���������� float � int
		tfSTDCALL_PROC_p_p V2FTo2I;
		/// ��������� float � int
		tfSTDCALL_PROC_p_p V2FTTo2I;
		/// ��������������� float � double
		tfSTDCALL_PROC_p_p V2FTo2D;
		/// ���������� double � char
		tfSTDCALL_PROC_p_p V3FTo3B;
		/// ���������� float � int
		tfSTDCALL_PROC_p_p V3FTo3I;
		/// ��������� float � int
		tfSTDCALL_PROC_p_p V3FTTo3I;
		/// ��������������� float � double
		tfSTDCALL_PROC_p_p V3FTo3D;
		/// ���������� float � char
		tfSTDCALL_PROC_p_p V4FTo4B;
		/// ���������� float � int
		tfSTDCALL_PROC_p_p V4FTo4I;
		/// ��������� float � int
		tfSTDCALL_PROC_p_p V4FTTo4I;
		/// ��������������� float � double
		tfSTDCALL_PROC_p_p V4FTo4D;
		/// ���������� double � char
		tfSTDCALL_PROC_p_p V2DTo2B;
		/// ���������� double � int
		tfSTDCALL_PROC_p_p V2DTo2I;
		/// ��������� double � int
		tfSTDCALL_PROC_p_p V2DTTo2I;
		tfSTDCALL_PROC_p_p V2DTo2L;
		tfSTDCALL_PROC_p_p V2DTTo2L;
		/// ��������������� double �� float
		tfSTDCALL_PROC_p_p V2DTo2F;
		/// ���������� double � char
		tfSTDCALL_PROC_p_p V3DTo3B;
		/// ���������� double � int
		tfSTDCALL_PROC_p_p V3DTo3I;
		/// ��������� double � int
		tfSTDCALL_PROC_p_p V3DTTo3I;
		/// ��������������� double �� float
		tfSTDCALL_PROC_p_p V3DTo3F;
		/// ���������� double � char
		tfSTDCALL_PROC_p_p V4DTo4B;
		/// ���������� double � int
		tfSTDCALL_PROC_p_p V4DTo4I;
		/// ��������� double � int
		tfSTDCALL_PROC_p_p V4DTTo4I;
		/// ��������������� double �� float
		tfSTDCALL_PROC_p_p V4DTo4F;

		//V2FSinCos;
		//V3FSinCos;
		//V4FSinCos;
		//V2DSinCos;
		//V3DSinCos;
		//V4DSinCos;
		/// �������� �� ����� ������
		tfSTDCALL_PROC_p_p V2FInv;
		/// �������� �� ����� ������
		tfSTDCALL_PROC_p_p V3FInv;
		/// �������� �� ����� ������
		tfSTDCALL_PROC_p_p V4FInv;
		/// �������� �� ����� ������
		tfSTDCALL_PROC_p_p V2DInv;
		/// �������� �� ����� ������
		tfSTDCALL_PROC_p_p V3DInv;
		/// �������� �� ����� ������
		tfSTDCALL_PROC_p_p V4DInv;

		/// Absolute value of a vector
		tfSTDCALL_PROC_p_p V2FAbs;
		/// Absolute value of a vector
		tfSTDCALL_PROC_p_p V3FAbs;
		/// Absolute value of a vector
		tfSTDCALL_PROC_p_p V4FAbs;
		/// Absolute value of a vector
		tfSTDCALL_PROC_p_p V2DAbs;
		/// Absolute value of a vector
		tfSTDCALL_PROC_p_p V3DAbs;
		/// Absolute value of a vector
		tfSTDCALL_PROC_p_p V4DAbs;

		tfSTDCALL_PROC_p_p_p V2FMinMax;
		tfSTDCALL_PROC_p_p_p V3FMinMax;
		tfSTDCALL_PROC_p_p_p V4FMinMax;
		tfSTDCALL_PROC_p_p_p V2DMinMax;
		tfSTDCALL_PROC_p_p_p V3DMinMax;
		tfSTDCALL_PROC_p_p_p V4DMinMax;

		/// ��������� �������� (vec1+vec2=vec3)
		tfSTDCALL_PROC_p_p_p V2IAdd;
		/// ��������� �������� (vec1+vec2=vec3)
		tfSTDCALL_PROC_p_p_p V3IAdd;
		/// ��������� �������� (vec1+vec2=vec3)
		tfSTDCALL_PROC_p_p_p V4IAdd;
		/// ��������� �������� (vec1+vec2=vec3)
		tfSTDCALL_PROC_p_p_p V2FAdd;
		/// ��������� �������� (vec1+vec2=vec3)
		tfSTDCALL_PROC_p_p_p V3FAdd;
		/// ��������� �������� (vec1+vec2=vec3)
		tfSTDCALL_PROC_p_p_p V4FAdd;
		/// ��������� �������� (vec1+vec2=vec3)
		tfSTDCALL_PROC_p_p_p V2LAdd;
		/// ��������� �������� (vec1+vec2=vec3)
		tfSTDCALL_PROC_p_p_p V2DAdd;
		/// ��������� �������� (vec1+vec2=vec3)
		tfSTDCALL_PROC_p_p_p V3DAdd;
		/// ��������� �������� (vec1+vec2=vec3)
		tfSTDCALL_PROC_p_p_p V4DAdd;
		
		/// ��������� ��������� (vec1-vec2=vec3)
		tfSTDCALL_PROC_p_p_p V2ISub;
		/// ��������� ��������� (vec1-vec2=vec3)
		tfSTDCALL_PROC_p_p_p V3ISub;
		/// ��������� ��������� (vec1-vec2=vec3)
		tfSTDCALL_PROC_p_p_p V4ISub;
		/// ��������� ��������� (vec1-vec2=vec3)
		tfSTDCALL_PROC_p_p_p V2FSub;
		/// ��������� ��������� (vec1-vec2=vec3)
		tfSTDCALL_PROC_p_p_p V3FSub;
		/// ��������� ��������� (vec1-vec2=vec3)
		tfSTDCALL_PROC_p_p_p V4FSub;
		/// ��������� ��������� (vec1-vec2=vec3)
		tfSTDCALL_PROC_p_p_p V2LSub;
		/// ��������� ��������� (vec1-vec2=vec3)
		tfSTDCALL_PROC_p_p_p V2DSub;
		/// ��������� ��������� (vec1-vec2=vec3)
		tfSTDCALL_PROC_p_p_p V3DSub;
		/// ��������� ��������� (vec1-vec2=vec3)
		tfSTDCALL_PROC_p_p_p V4DSub;

		/// ��������� ������� �� ����� (vec1*a=vec2)
		tfSTDCALL_PROC_p_p_float V2IScale;
		/// ��������� ������� �� ����� (vec1*a=vec2)
		tfSTDCALL_PROC_p_p_float V3IScale;
		/// ��������� ������� �� ����� (vec1*a=vec2)
		tfSTDCALL_PROC_p_p_float V4IScale;
		/// ��������� ������� �� ����� (vec1*a=vec2)
		tfSTDCALL_PROC_p_p_float V2FScale;
		/// ��������� ������� �� ����� (vec1*a=vec2)
		tfSTDCALL_PROC_p_p_float V3FScale;
		/// ��������� ������� �� ����� (vec1*a=vec2)
		tfSTDCALL_PROC_p_p_float V4FScale;
		/// ��������� ������� �� ����� (vec1*a=vec2)
		tfSTDCALL_PROC_p_p_double V2LScale;
		/// ��������� ������� �� ����� (vec1*a=vec2)
		tfSTDCALL_PROC_p_p_double V2DScale;
		/// ��������� ������� �� ����� (vec1*a=vec2)
		tfSTDCALL_PROC_p_p_double V3DScale;
		/// ��������� ������� �� ����� (vec1*a=vec2)
		tfSTDCALL_PROC_p_p_double V4DScale;

		/// ������������ ������������ ��������
		tfSTDCALL_PROC_p_p_p V2IMul;
		/// ������������ ������������ ��������
		tfSTDCALL_PROC_p_p_p V3IMul;
		/// ������������ ������������ ��������
		tfSTDCALL_PROC_p_p_p V4IMul;
		/// ������������ ������������ ��������
		tfSTDCALL_PROC_p_p_p V2FMul;
		/// ������������ ������������ ��������
		tfSTDCALL_PROC_p_p_p V3FMul;
		/// ������������ ������������ ��������
		tfSTDCALL_PROC_p_p_p V4FMul;
		/// ������������ ������������ ��������
		tfSTDCALL_PROC_p_p_p V2DMul;
		/// ������������ ������������ ��������
		tfSTDCALL_PROC_p_p_p V3DMul;
		/// ������������ ������������ ��������
		tfSTDCALL_PROC_p_p_p V4DMul;

		/// ������������ ������� ��������
		tfSTDCALL_PROC_p_p_p V2FDiv;
		/// ������������ ������� ��������
		tfSTDCALL_PROC_p_p_p V3FDiv;
		/// ������������ ������� ��������
		tfSTDCALL_PROC_p_p_p V4FDiv;
		/// ������������ ������� ��������
		tfSTDCALL_PROC_p_p_p V2DDiv;
		/// ������������ ������� ��������
		tfSTDCALL_PROC_p_p_p V3DDiv;
		/// ������������ ������� ��������
		tfSTDCALL_PROC_p_p_p V4DDiv;

		/// ��������� �� 2 � ������� N � ��������� float � int
		tfSTDCALL_PROC_p_p_int V2Fmul2NTrunc;
		/// ��������� �� 2 � ������� N � ��������� float � int
		tfSTDCALL_PROC_p_p_int V3Fmul2NTrunc;
		/// ��������� �� 2 � ������� N � ��������� float � int
		tfSTDCALL_PROC_p_p_int V4Fmul2NTrunc;
		/// ��������� �� 2 � ������� N � ��������� double � int
		tfSTDCALL_PROC_p_p_int V2Dmul2NTrunc;
		/// ��������� �� 2 � ������� N � ��������� double � int
		tfSTDCALL_PROC_p_p_int V3Dmul2NTrunc;
		/// ��������� �� 2 � ������� N � ��������� double � int
		tfSTDCALL_PROC_p_p_int V4Dmul2NTrunc;
		/// ��������� �� 2 � ������� N � ���������� float � int
		tfSTDCALL_PROC_p_p_int V2Fmul2NRound;
		/// ��������� �� 2 � ������� N � ���������� float � int
		tfSTDCALL_PROC_p_p_int V3Fmul2NRound;
		/// ��������� �� 2 � ������� N � ���������� float � int
		tfSTDCALL_PROC_p_p_int V4Fmul2NRound;
		/// ��������� �� 2 � ������� N � ���������� double � int
		tfSTDCALL_PROC_p_p_int V2Dmul2NRound;
		/// ��������� �� 2 � ������� N � ���������� double � int
		tfSTDCALL_PROC_p_p_int V3Dmul2NRound;
		/// ��������� �� 2 � ������� N � ���������� double � int
		tfSTDCALL_PROC_p_p_int V4Dmul2NRound;
		/// multiplication by 2 to the power N
		/// @param arg1 - two-dimensional single precision vector
		/// @param arg2 - the result is a two-dimensional single precision vector
		tfSTDCALL_PROC_p_p_int V2Imul2N;
		/// multiplication by 2 to the power N
		/// @param arg1 - ���������� ������ ��������� ��������
		/// @param arg2 - ��������� ���������� ������ ��������� ��������
		tfSTDCALL_PROC_p_p_int V3Imul2N;
		/// multiplication by 2 to the power N
		/// @param arg1 - ������������� ������ ��������� ��������
		/// @param arg2 - ��������� ������������� ������ ��������� ��������
		tfSTDCALL_PROC_p_p_int V4Imul2N;
		/// multiplication by 2 to the power N
		/// @param arg1 - two-dimensional single precision vector
		/// @param arg2 - the result is a two-dimensional single precision vector
		tfSTDCALL_PROC_p_p_int V2Fmul2N;
		/// multiplication by 2 to the power N
		/// @param arg1 - ���������� ������ ��������� ��������
		/// @param arg2 - ��������� ���������� ������ ��������� ��������
		tfSTDCALL_PROC_p_p_int V3Fmul2N;
		/// multiplication by 2 to the power N
		/// @param arg1 - ������������� ������ ��������� ��������
		/// @param arg2 - ��������� ������������� ������ ��������� ��������
		tfSTDCALL_PROC_p_p_int V4Fmul2N;
		/// ��������� �� 2 � ������� N
		/// @param arg1 - two-dimensional double precision vector
		/// @param arg2 - ��������� ���������� ������ ������� ��������
		tfSTDCALL_PROC_p_p_int V2Dmul2N;
		/// ��������� �� 2 � ������� N
		/// @param arg1 - ���������� ������ ������� ��������
		/// @param arg2 - ��������� ���������� ������ ������� ��������
		tfSTDCALL_PROC_p_p_int V3Dmul2N;
		/// ��������� �� 2 � ������� N
		/// @param arg1 - ������������� ������ ������� ��������
		/// @param arg2 - ��������� ������������� ������ ������� ��������
		tfSTDCALL_PROC_p_p_int V4Dmul2N;

		/// ��������� ��������� ��������
		tfSTDCALL_float_FUNC_p_p V2FDot;
		/// ��������� ��������� ��������
		tfSTDCALL_float_FUNC_p_p V3FDot;
		/// ��������� ��������� ��������
		tfSTDCALL_float_FUNC_p_p V4FDot;
		/// ��������� ��������� ��������
		tfSTDCALL_double_FUNC_p_p V2DDot;
		/// ��������� ��������� ��������
		tfSTDCALL_double_FUNC_p_p V3DDot;
		/// ��������� ��������� ��������
		tfSTDCALL_double_FUNC_p_p V4DDot;

		/// The length of the vector squared
		/// @return vector length.
		tfSTDCALL_int_FUNC_p V2ILength2;
		/// The length of the vector squared
		/// @return vector length.
		tfSTDCALL_float_FUNC_p V2FLength2;
		/// The length of the vector squared
		/// @param arg1 - two-dimensional single precision vector
		/// @return vector length.
		tfSTDCALL_float_FUNC_p V3FLength2;
		/// The length of the vector squared
		/// @return vector length.
		tfSTDCALL_float_FUNC_p V4FLength2;
		/// The length of the vector squared
		/// @param arg1 - ���������� ������ ������������� 64
		/// @return vector length.
		tfSTDCALL_long_FUNC_p V2LLength2;
		/// The length of the vector squared
		/// @param arg1 - two-dimensional double precision vector
		/// @return vector length.
		tfSTDCALL_double_FUNC_p V2DLength2;
		/// The length of the vector squared
		/// @return vector length.
		tfSTDCALL_double_FUNC_p V3DLength2;
		/// The length of the vector squared
		/// @return vector length.
		tfSTDCALL_double_FUNC_p V4DLength2;

		/// ��������� ���������
		tfSTDCALL_int_FUNC_p_p V2ICross;
		/// ��������� ���������
		tfSTDCALL_float_FUNC_p_p V2FCross;
		/// ��������� ���������
		tfSTDCALL_PROC_p_p_p V3FCross;
		/// ��������� ���������
		tfSTDCALL_long_FUNC_p_p V2LCross;
		/// ��������� ���������
		tfSTDCALL_double_FUNC_p_p V2DCross;
		/// ��������� ���������
		/// @param arg1 - ������ �
		/// @param arg2 - ������ �
		/// @param arg3 - ���������
		tfSTDCALL_PROC_p_p_p V3DCross;

		/// ������ ��������� ������ � ���������� �� 2 � �������
		/// @param arg1 - vector
		/// @param arg2 - normalized vector
		/// @param arg3 - pow
		tfSTDCALL_PROC_p_p_int V2INormalMul2N;
		/// ������ ��������� ������ � ���������� �� 2 � �������
		/// @param arg1 - vector
		/// @param arg2 - normalized vector
		/// @param arg3 - pow
		tfSTDCALL_PROC_p_p_int V3INormalMul2N;
		/// ������ ��������� ������ � ���������� �� 2 � �������
		/// @param arg1 - vector
		/// @param arg2 - normalized vector
		/// @param arg3 - pow
		tfSTDCALL_PROC_p_p_int V4INormalMul2N;
		/// ������ ��������� ������ (vec2=vec1*(1/length(vec1)))
		/// @param arg1 - vector
		/// @param arg2 - normalized vector
		tfSTDCALL_PROC_p_p V2FNormal;
		/// ������ ��������� ������ (vec2=vec1*(1/length(vec1)))
		/// @param arg1 - vector
		/// @param arg2 - normalized vector
		tfSTDCALL_PROC_p_p V3FNormal;
		/// ������ ��������� ������ (vec2=vec1*(1/length(vec1)))
		/// @param arg1 - vector
		/// @param arg2 - normalized vector
		tfSTDCALL_PROC_p_p V4FNormal;
		/// ������ ��������� ������ (vec2=vec1*(1/length(vec1)))
		/// @param arg1 - two-dimensional double precision vector
		/// @param arg2 - normalized vector
		tfSTDCALL_PROC_p_p V2DNormal;
		/// ������ ��������� ������ (vec2=vec1*(1/length(vec1)))
		/// @param arg1 - vector
		/// @param arg2 - normalized vector
		tfSTDCALL_PROC_p_p V3DNormal;
		/// ������ ��������� ������ (vec2=vec1*(1/length(vec1)))
		/// @param arg1 - vector
		/// @param arg2 - normalized vector
		tfSTDCALL_PROC_p_p V4DNormal;

		/// Vector single long, algorithm for fast computation of the approximate inverse root
		tfSTDCALL_PROC_p_p V2FFastNormal;
		/// Vector single long, algorithm for fast computation of the approximate inverse root
		tfSTDCALL_PROC_p_p V3FFastNormal;
		/// Vector single long, algorithm for fast computation of the approximate inverse root
		tfSTDCALL_PROC_p_p V4FFastNormal;
		/// Vector single long, algorithm for fast computation of the approximate inverse root
		tfSTDCALL_PROC_p_p V2DFastNormal;
		/// Vector single long, algorithm for fast computation of the approximate inverse root
		tfSTDCALL_PROC_p_p V3DFastNormal;
		/// Vector single long, algorithm for fast computation of the approximate inverse root
		tfSTDCALL_PROC_p_p V4DFastNormal;

		/// ������������ ������� (vec1+(vec2-vec1)*a=vec3)
		tfSTDCALL_PROC_p_p_p_float V2FLerp;
		/// ������������ ������� (vec1+(vec2-vec1)*a=vec3)
		tfSTDCALL_PROC_p_p_p_float V3FLerp;
		/// ������������ ������� (vec1+(vec2-vec1)*a=vec3)
		tfSTDCALL_PROC_p_p_p_float V4FLerp;
		/// ������������ ������� (vec1+(vec2-vec1)*a=vec3)
		tfSTDCALL_PROC_p_p_p_double V2DLerp;
		/// ������������ ������� (vec1+(vec2-vec1)*a=vec3)
		tfSTDCALL_PROC_p_p_p_double V3DLerp;
		/// ������������ ������� (vec1+(vec2-vec1)*a=vec3)
		tfSTDCALL_PROC_p_p_p_double V4DLerp;

		/// ��������������� � �������� ���� �������� - ������� (vec1*a+vec2*b=vec3)
		/// @param arg1 - vector a
		/// @param arg2 - vector b
		/// @param arg3 - result vector
		/// @param arg4 - scale vector a
		/// @param arg5 - scale vector b
		tfSTDCALL_PROC_p_p_p_float_float V2FCombine;
		/// ������� (vec1*a+vec2*b=vec3)
		/// @param arg1 - vector a
		/// @param arg2 - vector b
		/// @param arg3 - result vector
		/// @param arg4 - scale vector a
		/// @param arg5 - scale vector b
		tfSTDCALL_PROC_p_p_p_float_float V3FCombine;
		/// ������� (vec1*a+vec2*b=vec3)
		/// @param arg1 - vector a
		/// @param arg2 - vector b
		/// @param arg3 - result vector
		/// @param arg4 - scale vector a
		/// @param arg5 - scale vector b
		tfSTDCALL_PROC_p_p_p_float_float V4FCombine;
		/// ������� (vec1*a+vec2*b=vec3)
		/// @param arg1 - vector a
		/// @param arg2 - vector b
		/// @param arg3 - result vector
		/// @param arg4 - scale vector a
		/// @param arg5 - scale vector b
		tfSTDCALL_PROC_p_p_p_double_double V2DCombine;
		/// ������� (vec1*a+vec2*b=vec3)
		/// @param arg1 - vector a
		/// @param arg2 - vector b
		/// @param arg3 - result vector
		/// @param arg4 - scale vector a
		/// @param arg5 - scale vector b
		tfSTDCALL_PROC_p_p_p_double_double V3DCombine;
		/// ������� (vec1*a+vec2*b=vec3)
		/// @param arg1 - vector a
		/// @param arg2 - vector b
		/// @param arg3 - result vector
		/// @param arg4 - scale vector a
		/// @param arg5 - scale vector b
		tfSTDCALL_PROC_p_p_p_double_double V4DCombine;

		/// The distance from a point to a straight line in the square
		tfSTDCALL_int_FUNC_p_p_p V2IQDFL;
		/// The distance from a point to a straight line in the square
		tfSTDCALL_float_FUNC_p_p_p V2FQDFL;
		/// The distance from a point to a straight line in the square
		tfSTDCALL_long_FUNC_p_p_p V2LQDFL;
		/// The distance from a point to a straight line in the square
		tfSTDCALL_double_FUNC_p_p_p V2DQDFL;

		/// ��������� ������� ������������ ������� (vec1, nor2, rez3)
		tfSTDCALL_PROC_p_p_p V2FReflect;
		/// ��������� ������� ������������ ������� (vec1, nor2, rez3)
		tfSTDCALL_PROC_p_p_p V2DReflect;
		/// ��������� ������� ������������ ������� (vec1, nor2, rez3)
		tfSTDCALL_PROC_p_p_p V3FReflect;
		/// ��������� ������� ������������ ������� (vec1, nor2, rez3)
		tfSTDCALL_PROC_p_p_p V3DReflect;

		/// ���� ����� ���������
		/// @param arg1 - vector a
		/// @param arg2 - vector b
		/// @return angle.
		tfSTDCALL_float_FUNC_p_p V2FAngle;
		/// ���� ����� ���������
		/// @param arg1 - vector a
		/// @param arg2 - vector b
		/// @return angle.
		tfSTDCALL_float_FUNC_p_p V3FAngle;
		/// ���� ����� ���������
		/// @param arg1 - vector a
		/// @param arg2 - vector b
		/// @return angle.
		tfSTDCALL_double_FUNC_p_p V2DAngle;
		/// ���� ����� ���������
		/// @param arg1 - vector a
		/// @param arg2 - vector b
		/// @return angle.
		tfSTDCALL_double_FUNC_p_p V3DAngle;

		/// ���������� ����� ���������� � ������ �� ����������� ���� (plane1, normal2, point3, ray4)
		/// @param arg1 - plane point
		/// @param arg2 - plane normal
		/// @param arg3 - point
		/// @param arg4 - normalized ray
		/// @return distance.
		tfSTDCALL_float_FUNC_p_p V3FDPFR;
		/// ���������� ����� ���������� � ������ �� ����������� ���� (plane1, normal2, point3, ray4)
		/// @param arg1 - plane point
		/// @param arg2 - plane normal
		/// @param arg3 - point
		/// @param arg4 - normalized ray
		/// @return distance.
		tfSTDCALL_double_FUNC_p_p V3DDPFR;

		/// ��������� ������� ��� ��������� �������� ������� vec1, vec2, vec3
		/// @param arg1 - plane point vec1
		/// @param arg2 - plane point vec2
		/// @param arg3 - plane point vec3
		/// @param arg4 - rezult plane normal
		tfSTDCALL_PROC_p_p_p_p V3FTriNorm;
		/// ��������� ������� ������� �������� ��� ��������� �������� ������� vec1, vec2, vec3
		/// @param arg1 - plane point vec1
		/// @param arg2 - plane point vec2
		/// @param arg3 - plane point vec3
		/// @param arg4 - rezult plane normal
		tfSTDCALL_PROC_p_p_p_p V3DTriNorm;

		/// ��������� ����������� ������� ������������ NORM(CROSS(vec1-vec2,vec1-vec3)) � ��������� �� ��������� vec1+off4, vec2+off4, vec3+off4
		/// @param arg1 - plane point vec1
		/// @param arg2 - plane point vec2
		/// @param arg3 - plane point vec3
		/// @param arg4 - normal offset from vec1 to normal1
		tfSTDCALL_PROC_p_p_p_int V3FAddTriNorm;
		/// ��������� ����������� ������� ������������ NORM(CROSS(vec1-vec2,vec1-vec3)) � ��������� �� ��������� vec1+off4, vec2+off4, vec3+off4
		/// @param arg1 - plane point vec1
		/// @param arg2 - plane point vec2
		/// @param arg3 - plane point vec3
		/// @param arg4 - normal offset from vec1 to normal1
		tfSTDCALL_PROC_p_p_p_int V3FAdd3DTriNorm;
		/// ��������� ����������� ������� ������������ NORM(CROSS(vec1-vec2,vec1-vec3)) � ��������� �� ��������� vec1+off4, vec2+off4, vec3+off4
		/// @param arg1 - plane point vec1
		/// @param arg2 - plane point vec2
		/// @param arg3 - plane point vec3
		/// @param arg4 - normal offset from vec1 to normal1
		tfSTDCALL_PROC_p_p_p_int V3DAddTriNorm;

/*		tfSTDCALL_PROC_p_p V2FAdds;
		tfSTDCALL_PROC_p_p V3FAdds;
		tfSTDCALL_PROC_p_p V4FAdds;
		tfSTDCALL_PROC_p_p V2DAdds;
		tfSTDCALL_PROC_p_p V3DAdds;
		tfSTDCALL_PROC_p_p V4DAdds;*/

		/// The calculation of the quaternion from the vector and rotation angle around it
		tfSTDCALL_PROC_p_p V4FQuaternion;
		/// The calculation of the quaternion from the vector and rotation angle around it
		tfSTDCALL_PROC_p_p V4DQuaternion;

		/// The calculation of the quaternion from the vector and rotation angle around it, fast computation of approximate sine and cosine
		tfSTDCALL_PROC_p_p V4FFastQuaternion;
		/// The calculation of the quaternion from the vector and rotation angle around it, fast computation of approximate sine and cosine
		tfSTDCALL_PROC_p_p V4DFastQuaternion;

		/// ��������� �������������� �������
		tfSTDCALL_PROC_p_p_p V2ITransform;
		/// ��������� �������������� �������
		tfSTDCALL_PROC_p_p_p V3ITransform;
		/// ��������� �������������� �������
		tfSTDCALL_PROC_p_p_p V4ITransform;
		/// ��������� �������������� �������
		tfSTDCALL_PROC_p_p_p V2FTransform;
		/// ��������� �������������� �������
		tfSTDCALL_PROC_p_p_p V3FTransform;
		/// ��������� �������������� �������
		tfSTDCALL_PROC_p_p_p V4FTransform;
		/// ��������� �������������� �������
		tfSTDCALL_PROC_p_p_p V2DTransform;
		/// ��������� �������������� �������
		tfSTDCALL_PROC_p_p_p V3DTransform;
		/// ��������� �������������� �������
		tfSTDCALL_PROC_p_p_p V4DTransform;

		/// The multiplication of a vector by a matrix
		/// arg1 - two-dimensional single precision vector
		/// arg2 - four-dimensional matrix, use the first two rows and column
		/// arg3 - the result is a two-dimensional single precision vector
		tfSTDCALL_PROC_p_p_p V2FMMul;
		/// The multiplication of a vector by a matrix
		tfSTDCALL_PROC_p_p_p V3FMMul;
		/// ��������� ������� �� �������
		tfSTDCALL_PROC_p_p_p V4FMMul;
		/// ��������� ������� �� �������
		tfSTDCALL_PROC_p_p_p V2DMMul;
		/// ��������� ������� �� �������
		tfSTDCALL_PROC_p_p_p V3DMMul;
		/// ��������� ������� �� �������
		tfSTDCALL_PROC_p_p_p V4DMMul;

		/// Calculation of the projection of the vector in the cubic area of the screen (vec, matrix, scale, offset, rez)
		/// @param arg1 - vector.
		/// @param arg2 - matrix.
		/// @param arg3 - scree scale (width, height, depth).
		/// @param arg4 - scree center (x, y, z).
		/// @param arg5 - result vector.
		tfSTDCALL_int_FUNC_p_p_p_p_p V2FProj;
		/// Calculation of the projection of the vector in the cubic area of the screen (vec, matrix, scale, offset, rez)
		/// @param arg1 - vector.
		/// @param arg2 - matrix.
		/// @param arg3 - scree scale (width, height, depth).
		/// @param arg4 - scree center (x, y, z).
		/// @param arg5 - result vector.
		tfSTDCALL_int_FUNC_p_p_p_p_p V3FProj;
		/// Calculation of the projection of the vector in the cubic area of the screen (vec, matrix, scale, offset, rez)
		/// @param arg1 - vector.
		/// @param arg2 - matrix.
		/// @param arg3 - scree scale (width, height, depth).
		/// @param arg4 - scree center (x, y, z).
		/// @param arg5 - result vector.
		tfSTDCALL_int_FUNC_p_p_p_p_p V4FProj;
		/// Calculation of the projection of the vector in the cubic area of the screen (vec, matrix, scale, offset, rez)
		/// @param arg1 - vector.
		/// @param arg2 - matrix.
		/// @param arg3 - scree scale (width, height, depth).
		/// @param arg4 - scree center (x, y, z).
		/// @param arg5 - result vector.
		tfSTDCALL_int_FUNC_p_p_p_p_p V2DProj;
		/// Calculation of the projection of the vector in the cubic area of the screen (vec, matrix, scale, offset, rez)
		/// @param arg1 - vector.
		/// @param arg2 - matrix.
		/// @param arg3 - scree scale (width, height, depth).
		/// @param arg4 - scree center (x, y, z).
		/// @param arg5 - result vector.
		tfSTDCALL_int_FUNC_p_p_p_p_p V3DProj;
		/// Calculation of the projection of the vector in the cubic area of the screen (vec, matrix, scale, offset, rez)
		/// @param arg1 - vector.
		/// @param arg2 - matrix.
		/// @param arg3 - scree scale (width, height, depth).
		/// @param arg4 - scree center (x, y, z).
		/// @param arg5 - result vector.
		tfSTDCALL_int_FUNC_p_p_p_p_p V4DProj;

		/// ���������� �� ����������
		/// @param arg1 - quaternion.
		/// @param arg2 - result vector.
		tfSTDCALL_PROC_p_p Q4FVector;
		/// ���������� �� ����������
		/// @param arg1 - quaternion.
		/// @param arg2 - result vector.
		tfSTDCALL_PROC_p_p Q4DVector;

		/// �������� �����������
		/// @param arg1 - quaternion.
		/// @param arg2 - result invert quaternion.
		tfSTDCALL_PROC_p_p QFInv;
		/// �������� �����������
		/// @param arg1 - quaternion.
		/// @param arg2 - result invert quaternion.
		tfSTDCALL_PROC_p_p QDInv;

		/// �������� ������������ - ������� �������
		/// @param arg1 - quaternion a.
		/// @param arg2 - quaternion b.
		/// @param arg3 - result quaternion.
		tfSTDCALL_PROC_p_p_p QFAdd;
		/// �������� ������������ - ������� �������
		/// @param arg1 - quaternion a.
		/// @param arg2 - quaternion b.
		/// @param arg3 - result quaternion.
		tfSTDCALL_PROC_p_p_p QDAdd;

		/// ������������ ������������
		/// @param arg1 - quaternion a.
		/// @param arg2 - quaternion b.
		/// @param arg3 - result quaternion.
		tfSTDCALL_PROC_p_p_p QFMul;
		/// ������������ ������������
		/// @param arg1 - quaternion a.
		/// @param arg2 - quaternion b.
		/// @param arg3 - result quaternion.
		tfSTDCALL_PROC_p_p_p QDMul;

		/// ???
		tfSTDCALL_float_FUNC_p QFNorm;
		/// ???
		tfSTDCALL_double_FUNC_p QDNorm;

		/// ��������� ����������� ����� ���� ������
		/// @param arg1 - euler angles (x, y, z).
		/// @param arg2 - result quaternion.
		tfSTDCALL_PROC_p_p QFEuler;
		/// ��������� ����������� ����� ���� ������
		/// @param arg1 - euler angles (x, y, z).
		/// @param arg2 - result quaternion.
		tfSTDCALL_PROC_p_p QDEuler;

		/// �������������� ����������� � �������
		/// @param arg1 - quaternion
		/// @param arg2 - rezult matrix
		tfSTDCALL_PROC_p_p Q4FMatrix;
		/// �������������� ����������� � �������
		/// @param arg1 - quaternion
		/// @param arg2 - rezult matrix
		tfSTDCALL_PROC_p_p Q4DMatrix;

		/// ������� ��������������
		/// @param arg1 - vector
		/// @param arg2 - transform vector
		/// @param arg3 - rezult vector
		tfSTDCALL_PROC_p_p_p V2FAfineTransform;
		/// ������� ��������������
		/// @param arg1 - vector
		/// @param arg2 - transform vector
		/// @param arg3 - rezult vector
		tfSTDCALL_PROC_p_p_p V2DAfineTransform;

		/// ��������� ������� �� �������� ���������� (vec2*quat1=vec3)
		/// @param quat1 - quaternion.
		/// @param vec2 - vector.
		/// @param vec3 - result vector.
		tfSTDCALL_PROC_p_p_p Q2FInvTransform;
		/// ��������� ������� �� �������� ���������� (vec2*quat1=vec3)
		/// @param quat1 - quaternion.
		/// @param vec2 - vector.
		/// @param vec3 - result vector.
		tfSTDCALL_PROC_p_p_p Q2DInvTransform;
		/// ��������� ������� �� �������� ���������� (vec2*quat1=vec3)
		/// @param quat1 - quaternion.
		/// @param vec2 - vector.
		/// @param vec3 - result vector.
		tfSTDCALL_PROC_p_p_p Q3FInvTransform;
		/// ��������� ������� �� �������� ���������� (vec2*quat1=vec3)
		/// @param quat1 - quaternion.
		/// @param vec2 - vector.
		/// @param vec3 - result vector.
		tfSTDCALL_PROC_p_p_p Q3DInvTransform;

		/// ���������������� �������
		tfSTDCALL_PROC_p_p M4FTranspose;
		/// ���������������� �������
		tfSTDCALL_PROC_p_p M4DTranspose;
		/// ��������� ���������
		tfSTDCALL_PROC_p_p_p M4FMul;
		/// ��������� ���������
		tfSTDCALL_PROC_p_p_p M4DMul;
		/// �������� �������
		tfSTDCALL_int_FUNC_p_p M4FInv;
		/// �������� �������
		tfSTDCALL_int_FUNC_p_p M4DInv;
		/// The perspective projection matrix
		/// @param arg1 - �������.
		/// @param arg2 - ������.
		/// @param arg3 - ������.
		/// @param arg4 - ��������� ������� ���������.
		/// @param arg5 - ��������� �������.
		/// @param arg6 - ���� ������.
		tfSTDCALL_PROC_p_int_int_float_float_float M4FPerspective;
		/// The perspective projection matrix
		/// @param arg1 - ��������� �� ������� ������� ��������.
		/// @param arg2 - ������.
		/// @param arg3 - ������.
		/// @param arg4 - ��������� ������� ���������.
		/// @param arg5 - ��������� �������.
		/// @param arg6 - ���� ������.
		tfSTDCALL_PROC_p_int_int_double_double_double M4DPerspective;
		/// The ortographic projection matrix
		/// @param arg1 - �������.
		/// @param arg2 - ������.
		/// @param arg3 - ������.
		/// @param arg4 - ��������� ������� ���������.
		/// @param arg5 - ��������� �������.
		/// @param arg6 - ������ ��������.
		tfSTDCALL_PROC_p_int_int_float_float_float M4FOrtographic;
		/// The ortographic projection matrix
		/// @param arg1 - ��������� �� ������� ������� ��������.
		/// @param arg2 - ������.
		/// @param arg3 - ������.
		/// @param arg4 - ��������� ������� ���������.
		/// @param arg5 - ��������� �������.
		/// @param arg6 - ������ ��������.
		tfSTDCALL_PROC_p_int_int_double_double_double M4DOrtographic;
		/// ��������� �������
		tfSTDCALL_PROC_p M4FIdentity;
		/// ��������� �������
		tfSTDCALL_PROC_p M4DIdentity;
		/// Extract quaternion from matrix
		/// @param arg1 - matrix
		/// @param arg2 - rezult quaternion
		tfSTDCALL_PROC_p_p M4FQuaternion;
		/// Extract quaternion from matrix
		/// @param arg1 - matrix
		/// @param arg2 - rezult quaternion
		tfSTDCALL_PROC_p_p M4DQuaternion;
		/// ������� ��������
		tfSTDCALL_PROC_p_p M4FTranslate;
		/// ������� ��������
		tfSTDCALL_PROC_p_p M4DTranslate;
		/// ������� ��������������
		tfSTDCALL_PROC_p_p M4FScale;
		/// ������� ��������������
		tfSTDCALL_PROC_p_p M4DScale;
		/// ��������� �� ������� ��������
		/// @param arg1 - matrix
		/// @param arg2 - translate vector
		/// @param arg3 - result matrix
		tfSTDCALL_PROC_p_p_p M4FAddTranslate;
		/// ��������� �� ������� ��������
		/// @param arg1 - matrix
		/// @param arg2 - translate vector
		/// @param arg3 - result matrix
		tfSTDCALL_PROC_p_p_p M4DAddTranslate;
		/// ��������� �� ������� ��������������
		/// @param arg1 - matrix
		/// @param arg2 - scale vector
		/// @param arg3 - result matrix
		tfSTDCALL_PROC_p_p_p M4FAddScale;
		/// ��������� �� ������� ��������������
		/// @param arg1 - matrix
		/// @param arg2 - scale vector
		/// @param arg3 - result matrix
		tfSTDCALL_PROC_p_p_p M4DAddScale;
		/// ��������� ������� �� ����������
		/// @param arg1 - matrix
		/// @param arg2 - quaternion
		/// @param arg3 - result matrix
		tfSTDCALL_PROC_p_p_p M4FAddRotate;
		/// ��������� ������� �� ����������
		/// @param arg1 - matrix
		/// @param arg2 - quaternion
		/// @param arg3 - result matrix
		tfSTDCALL_PROC_p_p_p M4DAddRotate;

		/// ������������� ������� ������� �������� � ���������
		tfSTDCALL_PROC_p_p M4DToM4F;
		/// ������������� ������� ��������� �������� � �������
		tfSTDCALL_PROC_p_p M4FToM4D;

		/// ������������ ������� ������������� �� ���� ����� ��������� ��������� � �������� �������, � ������ ������� ������
		/// @param arg1 - result matrix
		/// @param arg2 - position
		/// @param arg3 - rotation
		/// @param arg4 - scale
		tfSTDCALL_PROC_p_p_p_p M4FTRSDDF;
		/// ������������ ������� ������������� �� ���� ����� ��������� ��������� � �������� �������, � ������ ������� ������
		/// @param arg1 - result matrix
		/// @param arg2 - position
		/// @param arg3 - rotation
		/// @param arg4 - scale
		tfSTDCALL_PROC_p_p_p_p M4DTRSDDF;
		/// ������������ ������� ������������� �� ���� ����� ��������� ��������� � �������� �������
		/// @param arg1 - result matrix
		/// @param arg2 - position
		/// @param arg3 - rotation
		/// @param arg4 - scale
		tfSTDCALL_PROC_p_p_p_p M4FTRS;
		/// ������������ ������� ������������� �� ���� ����� ��������� ��������� � �������� �������
		/// @param arg1 - result matrix
		/// @param arg2 - position
		/// @param arg3 - rotation
		/// @param arg4 - scale
		tfSTDCALL_PROC_p_p_p_p M4DTRS;
	};

	/**
	 * @class sFunctionsArrayVectorCPU
	 *
	 * @ingroup apiinterface
	 * @brief sFunctionsArrayVectorCPU - mathematical functions for handling arrays of numbers.
	 *
	 * @see math, apiinterface
	 */

	struct sFunctionsArrayVectorCPU {
		_int32 version;
		//AFSinCos;
		//ADSinCos;
		//APFSinCos;
		//APDSinCos;

		tfSTDCALL_PROC_p_p_uint_uint_p_p_uint AConvert;

		tfSTDCALL_PROC_p_p_uint_uint_uint A2BMove;
		tfSTDCALL_PROC_p_p_uint_uint_uint A3BMove;
		tfSTDCALL_PROC_p_p_uint_uint_uint A4BMove;
		tfSTDCALL_PROC_p_p_uint_uint_uint A2FMove;
		tfSTDCALL_PROC_p_p_uint_uint_uint A3FMove;
		tfSTDCALL_PROC_p_p_uint_uint_uint A4FMove;
		tfSTDCALL_PROC_p_p_uint_uint_uint A2DMove;
		tfSTDCALL_PROC_p_p_uint_uint_uint A3DMove;
		tfSTDCALL_PROC_p_p_uint_uint_uint A4DMove;

		tfSTDCALL_PROC_p_p_int_int_uint A2ITo2F;
		tfSTDCALL_PROC_p_p_int_int_uint A2ITo2D;
		tfSTDCALL_PROC_p_p_int_int_uint A3ITo3F;
		tfSTDCALL_PROC_p_p_int_int_uint A3ITo3D;
		tfSTDCALL_PROC_p_p_int_int_uint A4ITo4W;
		tfSTDCALL_PROC_p_p_int_int_uint A4ITo4F;
		tfSTDCALL_PROC_p_p_int_int_uint A4ITo4D;
		tfSTDCALL_PROC_p_p_int_int_uint A2FTo2I;
		tfSTDCALL_PROC_p_p_int_int_uint A3FTo3I;
		tfSTDCALL_PROC_p_p_int_int_uint A4FTo4I;
		tfSTDCALL_PROC_p_p_int_int_uint A2FTo2D;
		tfSTDCALL_PROC_p_p_int_int_uint A3FTo3D;
		tfSTDCALL_PROC_p_p_int_int_uint A4FTo4D;
		tfSTDCALL_PROC_p_p_int_int_uint A2DTo2F;
		tfSTDCALL_PROC_p_p_int_int_uint A3DTo3F;
		tfSTDCALL_PROC_p_p_int_int_uint A4DTo4F;

		/// ��������� ������ �������� �� �����������
		tfSTDCALL_PROC_p_p_int_int_uint A2FGrow3F;
		/// ��������� ������ �������� �� ��������������
		tfSTDCALL_PROC_p_p_int_int_uint A2FGrow4F;
		/// ��������� ������ �������� �� ��������������
		tfSTDCALL_PROC_p_p_int_int_uint A3FGrow4F;
		/// ��������� ������ �������� �� �����������
		tfSTDCALL_PROC_p_p_int_int_uint A2DGrow3D;
		/// ��������� ������ �������� �� ��������������
		tfSTDCALL_PROC_p_p_int_int_uint A2DGrow4D;
		/// ��������� ������ �������� �� ��������������
		tfSTDCALL_PROC_p_p_int_int_uint A3DGrow4D;

		/// ��������� ������ �������� �� ����������� � �������� ������
		tfSTDCALL_PROC_p_p_int_int_uint A2IGrowTo3F;
		/// ��������� ������ �������� �� �������������� � �������� ������
		tfSTDCALL_PROC_p_p_int_int_uint A2IGrowTo4F;
		/// ��������� ������ �������� �� �������������� � �������� ������
		tfSTDCALL_PROC_p_p_int_int_uint A3IGrowTo4F;
		/// ��������� ������ �������� �� ����������� � �������� ������
		tfSTDCALL_PROC_p_p_int_int_uint A2IGrowTo3D;
		/// ��������� ������ �������� �� �������������� � �������� ������
		tfSTDCALL_PROC_p_p_int_int_uint A2IGrowTo4D;
		/// ��������� ������ �������� �� �������������� � �������� ������
		tfSTDCALL_PROC_p_p_int_int_uint A3IGrowTo4D;

		///
		tfSTDCALL_PROC_p_p_int_int_uint A2FGrowTo3D;
		///
		tfSTDCALL_PROC_p_p_int_int_uint A2FGrowTo4D;
		///
		tfSTDCALL_PROC_p_p_int_int_uint A3FGrowTo4D;
		///
		tfSTDCALL_PROC_p_p_int_int_uint A2DGrowTo3F;
		///
		tfSTDCALL_PROC_p_p_int_int_uint A2DGrowTo4F;
		///
		tfSTDCALL_PROC_p_p_int_int_uint A3DGrowTo4F;

		/// ������� ��� ������� �������� (arr1/rez arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_int_uint A2FSum;
		/// ������� ��� ������� �������� (arr1/rez arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_int_uint A3FSum;
		/// ������� ��� ������� �������� (arr1/rez arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_int_uint A4FSum;
		/// ������� ��� ������� �������� (arr1/rez arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_int_uint A2DSum;
		/// ������� ��� ������� �������� (arr1/rez arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_int_uint A3DSum;
		/// ������� ��� ������� �������� (arr1/rez arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_int_uint A4DSum;

		/// �������� �� ���� ��������� ������ (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A2FAddVector;
		/// �������� �� ���� ��������� ������ (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A3FAddVector;
		/// �������� �� ���� ��������� ������ (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A4FAddVector;
		/// �������� �� ���� ��������� ������ (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A2DAddVector;
		/// �������� �� ���� ��������� ������ (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A3DAddVector;
		/// �������� �� ���� ��������� ������ (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A4DAddVector;

		/// ������� ��� ������� �������� (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A2IAdd;
		/// ������� ��� ������� �������� (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A3IAdd;
		/// ������� ��� ������� �������� (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A4IAdd;
		/// ������� ��� ������� �������� (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A2FAdd;
		/// ������� ��� ������� �������� (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A3FAdd;
		/// ������� ��� ������� �������� (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A4FAdd;
		/// ������� ��� ������� �������� (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A2DAdd;
		/// ������� ��� ������� �������� (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A3DAdd;
		/// ������� ��� ������� �������� (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A4DAdd;

		/// ������� �� ���� ��������� ������ (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A2FSubVector;
		/// ������� �� ���� ��������� ������ (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A3FSubVector;
		/// ������� �� ���� ��������� ������ (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A4FSubVector;
		/// ������� �� ���� ��������� ������ (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A2DSubVector;
		/// ������� �� ���� ��������� ������ (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A3DSubVector;
		/// ������� �� ���� ��������� ������ (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A4DSubVector;

		/// ������� ��� ������� �������� (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A2ISub;
		/// ������� ��� ������� �������� (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A3ISub;
		/// ������� ��� ������� �������� (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A4ISub;
		/// ������� ��� ������� �������� (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A2FSub;
		/// ������� ��� ������� �������� (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A3FSub;
		/// ������� ��� ������� �������� (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A4FSub;
		/// ������� ��� ������� �������� (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A2DSub;
		/// ������� ��� ������� �������� (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A3DSub;
		/// ������� ��� ������� �������� (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A4DSub;

		/// ��������������� ������� ��������
		tfSTDCALL_PROC_p_p_float_int_int_uint A2FScale;
		/// ��������������� ������� ��������
		tfSTDCALL_PROC_p_p_float_int_int_uint A3FScale;
		/// ��������������� ������� ��������
		tfSTDCALL_PROC_p_p_float_int_int_uint A4FScale;
		/// ��������������� ������� ��������
		tfSTDCALL_PROC_p_p_double_int_int_uint A2DScale;
		/// ��������������� ������� ��������
		tfSTDCALL_PROC_p_p_double_int_int_uint A3DScale;
		/// ��������������� ������� ��������
		tfSTDCALL_PROC_p_p_double_int_int_uint A4DScale;

		/// �������� ������ �������� �� ������
		tfSTDCALL_PROC_p_p_p_int_int_uint A2FMulVector;
		/// �������� ������ �������� �� ������
		tfSTDCALL_PROC_p_p_p_int_int_uint A3FMulVector;
		/// �������� ������ �������� �� ������
		tfSTDCALL_PROC_p_p_p_int_int_uint A4FMulVector;
		/// �������� ������ �������� �� ������
		tfSTDCALL_PROC_p_p_p_int_int_uint A2DMulVector;
		/// �������� ������ �������� �� ������
		tfSTDCALL_PROC_p_p_p_int_int_uint A3DMulVector;
		/// �������� ������ �������� �� ������
		tfSTDCALL_PROC_p_p_p_int_int_uint A4DMulVector;

		/// To multiply two arrays of vectors
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A2FMul;
		/// To multiply two arrays of vectors
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A3FMul;
		/// To multiply two arrays of vectors
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A4FMul;
		/// To multiply two arrays of vectors
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A2DMul;
		/// To multiply two arrays of vectors
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A3DMul;
		/// To multiply two arrays of vectors
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A4DMul;

		/// Normalization array of vectors
		/// @param a��1 - ������ a
		/// @param a��2 - ������ ����������
		/// @param a��3 - ��� ��������� ������� a
		/// @param a��4 - ��� ��������� ������� ����������
		/// @param a��5 - ���������� ��������� � �������
		tfSTDCALL_PROC_p_p_int_int_uint A2FNormal;
		/// Normalization array of vectors
		tfSTDCALL_PROC_p_p_int_int_uint A3FNormal;
		/// Normalization array of vectors
		tfSTDCALL_PROC_p_p_int_int_uint A4FNormal;
		/// Normalization array of vectors
		tfSTDCALL_PROC_p_p_int_int_uint A2DNormal;
		/// Normalization array of vectors
		tfSTDCALL_PROC_p_p_int_int_uint A3DNormal;
		/// Normalization array of vectors
		tfSTDCALL_PROC_p_p_int_int_uint A4DNormal;

		/// ������������ ������� ��������
		/// @param a��1 - ������ a
		/// @param a��2 - ������ b
		/// @param a��3 - ������ ����������
		/// @param a��4 - �����������
		/// @param a��5 - ��� ��������� ������� a
		/// @param a��6 - ��� ��������� ������� b
		/// @param a��7 - ��� ��������� ������� ����������
		/// @param a��8 - ���������� ��������� � �������
		tfSTDCALL_PROC_p_p_p_float_int_int_int_uint A2FLerp;
		/// ������������ ������� ��������
		tfSTDCALL_PROC_p_p_p_float_int_int_int_uint A3FLerp;
		/// ������������ ������� ��������
		tfSTDCALL_PROC_p_p_p_float_int_int_int_uint A4FLerp;
		/// ������������ ������� ��������
		tfSTDCALL_PROC_p_p_p_double_int_int_int_uint A2DLerp;
		/// ������������ ������� ��������
		tfSTDCALL_PROC_p_p_p_double_int_int_int_uint A3DLerp;
		/// ������������ ������� ��������
		tfSTDCALL_PROC_p_p_p_double_int_int_int_uint A4DLerp;

		/// Transforming a two-dimensional array of vectors (vec, matrix, vecr, stepvec, stepvecr, count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A2FMatrixTransform;
		/// Transforming a three-dimensional array of vectors (vec, matrix, vecr, stepvec, stepvecr, count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A3FMatrixTransform;
		/// The transformation of four-dimensional array of vectors (vec, matrix, vecr, stepvec, stepvecr, count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A4FMatrixTransform;
		/// Transforming a two-dimensional array of vectors (vec, matrix, vecr, stepvec, stepvecr, count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A2DMatrixTransform;
		/// Transforming a three-dimensional array of vectors (vec, matrix, vecr, stepvec, stepvecr, count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A3DMatrixTransform;
		/// The transformation of four-dimensional array of vectors (vec, matrix, vecr, stepvec, stepvecr, count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A4DMatrixTransform;

		/// Calculation of the projection of the vector in the cubic area of the screen (vec, matrix, scale, offset, rez, stepvec, steprez, flagoffset, count)
		tfSTDCALL_PROC_p_p_p_p_p_int_int_int_uint A2FProj;
		/// Calculation of the projection of the vector in the cubic area of the screen (vec, matrix, scale, offset, rez, stepvec, steprez, flagoffset, count)
		tfSTDCALL_PROC_p_p_p_p_p_int_int_int_uint A3FProj;
		/// Calculation of the projection of the vector in the cubic area of the screen (vec, matrix, scale, offset, rez, stepvec, steprez, flagoffset, count)
		tfSTDCALL_PROC_p_p_p_p_p_int_int_int_uint A4FProj;
		/// Calculation of the projection of the vector in the cubic area of the screen (vec, matrix, scale, offset, rez, stepvec, steprez, flagoffset, count)
		tfSTDCALL_PROC_p_p_p_p_p_int_int_int_uint A2DProj;
		/// Calculation of the projection of the vector in the cubic area of the screen (vec, matrix, scale, offset, rez, stepvec, steprez, flagoffset, count)
		tfSTDCALL_PROC_p_p_p_p_p_int_int_int_uint A3DProj;
		/// Calculation of the projection of the vector in the cubic area of the screen (vec, matrix, scale, offset, rez, stepvec, steprez, flagoffset, count)
		tfSTDCALL_PROC_p_p_p_p_p_int_int_int_uint A4DProj;

		/// Scaling the data and filtering the lerp.
		tfSTDCALL_PROC_p_p_int_int_double_float_uint_uint_uint A2FZoomLerp;
		/// Scaling the data and filtering the lerp.
		tfSTDCALL_PROC_p_p_int_int_double_float_uint_uint_uint A4FZoomLerp;

		/// Scaling the data and filtering the spline Catmull-Roma.
		tfSTDCALL_PROC_p_p_int_int_double_float_uint_uint_uint AFZoomSplineCR;
		/// Scaling the data and filtering the spline Catmull-Roma.
		tfSTDCALL_PROC_p_p_int_int_double_float_uint_uint_uint A2FZoomSplineCR;
		/// Scaling the data and filtering the spline Catmull-Roma.
		tfSTDCALL_PROC_p_p_int_int_double_float_uint_uint_uint A3FZoomSplineCR;
		/// Scaling the data and filtering the spline Catmull-Roma.
		/// @param arg1 - array in
		/// @param arg2 - array out
		/// @param arg3 - size of step element array in
		/// @param arg4 - size of step element array out
		/// @param arg5 - first element offset
		/// @param arg6 - interpolation step
		/// @param flag - if flag is not null interpolation looping.
		/// @param arg8 - count of elements array in
		/// @param arg9 - count of elements array out
		tfSTDCALL_PROC_p_p_int_int_double_float_uint_uint_uint A4FZoomSplineCR;
		/// Scaling the data and filtering the spline Catmull-Roma.
		tfSTDCALL_PROC_p_p_int_int_double_float_uint_uint_uint ADZoomSplineCR;
		/// Scaling the data and filtering the spline Catmull-Roma.
		tfSTDCALL_PROC_p_p_int_int_double_float_uint_uint_uint A2DZoomSplineCR;
		/// Scaling the data and filtering the spline Catmull-Roma.
		tfSTDCALL_PROC_p_p_int_int_double_float_uint_uint_uint A3DZoomSplineCR;
		/// Scaling the data and filtering the spline Catmull-Roma.
		tfSTDCALL_PROC_p_p_int_int_double_float_uint_uint_uint A4DZoomSplineCR;

	};

	/**
	 * @class sFunctionsArrayCPU
	 *
	 * @ingroup apiinterface
	 * @brief sFunctionsArrayCPU - ������� ��������� ��������
	 *
	 * A - ������������� ������
	 * D - ������
	 * M - ������������� ������
	 *
	 * P - �������� ������� ���������
	 * S - �������� ������� �������� ������ �� 127 ����.
	 *
	 * @see apiinterface
	 */

	struct sFunctionsArrayCPU {
		_int32 version;

		/// ������������� ������
		tfSTDCALL_p_FUNC_p SCreate;
		/// ������������� ������� ������ ??
		tfSTDCALL_p_FUNC_p LSCreate;
		/// ������������� �������
		tfSTDCALL_PROC_p_uint_uint ANTInit;
		/// ������������� ������� ����� ??
		tfSTDCALL_PROC_p ASInit;
		/// ������������� ������� ���������� ??
		tfSTDCALL_PROC_p APInit;
		/// ������������� ����� ??
		tfSTDCALL_PROC_p MNTInit;
		/// ������������� ����� ����� - ���������, �������� - ������ ??
		tfSTDCALL_PROC_p MPSInit;
		/// ������������� ����� ����� - ������, �������� - ��������� ??
		tfSTDCALL_PROC_p MSPInit;
		/// ������������� ����� ����� - ���������, �������� - ��������� ??
		tfSTDCALL_PROC_p MPInit;

		/// ��������� �������� ������.
		tfSTDCALL_PROC_p_p SSet;
		/// ���������� �������� � ����� ������.
		tfSTDCALL_PROC_p_p SAdd;
		/// Comparison with the sequence of lines of characters. Return 0 if equal, see CmpMem
		tfSTDCALL_int_FUNC_p_p SCompare;

		/// ��������� �������� ������� ������.
		tfSTDCALL_PROC_p_p LSSet;
		/// ���������� �������� � ����� ������� ������.
		tfSTDCALL_PROC_p_p LSAdd;
		/// ��������� �������� � ������� ������.
		tfSTDCALL_PROC_p_p_uint LSInsert;
		/// �������� �������� �� ������� ������.
		tfSTDCALL_PROC_p_uint_uint LSRemove;
		/// ��������� ������� ������ � ������������������� ��������.
		tfSTDCALL_int_FUNC_p_p LSCompare;

		/// �������� �������� � ����� �������
		tfSTDCALL_p_FUNC_p_p DPAddLast;
		/// �������� �������� � ������
		tfSTDCALL_p_FUNC_p_p_uint DPInsert;
		/// ������ ������� � ������� �� �������
		tfSTDCALL_PROC_p_uint DPRemove;
		/// ������ �������� �� �������
		tfSTDCALL_int_FUNC_p_p DPRemoveVal;
		///
		tfSTDCALL_PROC_p DPRemoveLast;
		/// 
		tfSTDCALL_PROC_p_uint DPSetCount;
		/// ����������� ������
		tfSTDCALL_PROC_p DPFree;

		/// �������� ������ � ����� �������
		tfSTDCALL_p_FUNC_p_p DSAddLast;
		/// ����������� ������ �������� �����
		tfSTDCALL_PROC_p DSFree;

		///
		tfSTDCALL_p_FUNC_p APLast;
		///
		tfSTDCALL_p_FUNC_p APClone;
		/// ���������� � ������� ����� - ��������� (list,key)
		tfSTDCALL_p_FUNC_p_p APAdd;
		/// ����� � ������e ����� - ��������� (list,key)
		tfSTDCALL_int_FUNC_p_p APFind;
		/// ������� �������� �� ������� �� �����. (list,key)
		tfSTDCALL_int_FUNC_p_p APRemove;
		///
		tfSTDCALL_p_FUNC_p APEnd;
		/// ����������� ������
		tfSTDCALL_PROC_p APFree;

		/// ���������� � ����� ����� - ���������, �������� - ��������� (list,key,val)
		tfSTDCALL_p_FUNC_p_p_p MPAdd;
		/// ����� ����� � ����� ����� - ��������� (list,key)
		tfSTDCALL_p_FUNC_p_p MPFind;
		/// ���������� ����� �������� � ����� - void* (list,val,def key)
		tfSTDCALL_p_FUNC_p_p_p MPFindByVal;
		/// ������� ������� �� ����� �� �����. (list,key)
		tfSTDCALL_p_FUNC_p_p MPRemove;
		///
		tfSTDCALL_p_FUNC_p MPEnd;
		/// ����������� �����
		tfSTDCALL_PROC_p MPFree;

		/// ���������� � ����� ����� - ������, �������� - ��������� (list,key,val)
		tfSTDCALL_p_FUNC_p_p_p MSPAdd;
		/// ���������� ���������� � �����, � ��������� ����� ������, ����� - char*, �������� - ��������� (list,key,val)
		tfSTDCALL_p_FUNC_p_p_p MSSPAdd;
		/// ����� ����� � ����� ����� - ������ (list,key)
		tfSTDCALL_p_FUNC_p_p MSPFind;
		/// ���������� ����� ����� � ����� ����� - char* (list,key)
		tfSTDCALL_p_FUNC_p_p MSSPFind;
		/// ������� ������� �� ����� �� �����. (list,key) �� ������� ������.
		tfSTDCALL_p_FUNC_p_p MSPRemove;
		/// ���������� �������� �������� �� ����� �� ����� - char* (list,key)
		tfSTDCALL_int_FUNC_p_p MSSPRemove;
		/// ������� ������ � ����������� �����.
		tfSTDCALL_PROC_p MSSPFree;

		/// ���������� � ����������� ����� ����� - ���������, �������� - ��������� (list,key,val,max)
		tfSTDCALL_p_FUNC_p_p_p_uint MCPAdd;
		/// ����� ����� � ����������� ����� ����� - ��������� (list,key)
		tfSTDCALL_p_FUNC_p_p MCPFind;

		/// ���������� � ����������� ����� ����� - ������, �������� - ��������� (list,key,val,max)
		tfSTDCALL_p_FUNC_p_p_p_uint MCSPAdd;
		/// ����� ����� � ����������� ����� ����� - ������ (list,key)
		tfSTDCALL_p_FUNC_p_p MCSPFind;

		/// ���������� ����� ���������
		tfSTDCALL_p_FUNC_p MPArray;
		/// ���������� ���������� ���������
		tfSTDCALL_uint_FUNC_p MPCount;

		tfSTDCALL_PROC_p ANTFree;
		tfSTDCALL_PROC_p_uint ANTResize;
		tfSTDCALL_PROC_p_uint ANTReserv;
		tfSTDCALL_PROC_p_p ANTAssign;
		tfSTDCALL_PROC_p ANTDelLast;
		tfSTDCALL_p_FUNC_p_uint ANTPosition;
		tfSTDCALL_p_FUNC_p ANTPositionL;
	};

	/**
	 * @class sFunctionsExtensionCPU
	 *
	 * @ingroup apiinterface
	 * @brief sFunctionsExtensionCPU - �������������� �������
	 *
	 * @see math, apiinterface
	 */

	struct sFunctionsExtensionCPU {
		_int32 version;

		/// Allocate and return a memory pointer. You must define this method.
		/// @param size - num bytes.
		/// @param flag - .
		/// @return memory pointer.
		tfSTDCALL_p_FUNC_uint_uint CreateMem;
		/// To destroy the memory pointer. You must define this method.
		/// @param pointer - memory pointer
		/// @param flag - .
		/// @return successful operation.
		tfSTDCALL_bool_FUNC_p_uint DeleteMem;

		tfSTDCALL_p_FUNC_p_uint_uint ResizeMem;

		/// Set zero bytes to memory (fmemclean)
		/// @param src - source
		/// @param count - num bytes for set to zero.
		tfSTDCALL_PROC_p_uint CleanMem;
		/// Copy memory from src to dst (fmemcpy)
		/// @param src - source
		/// @param dst - destionation
		/// @param count - num bytes for copy.
		tfSTDCALL_PROC_p_p_uint MoveMem;
		/// The memory copy backwards
		/// @param src - source
		/// @param dst - destionation
		/// @param count - num bytes for copy.
		tfSTDCALL_PROC_p_p_uint MoveBack;
		/// ����� ������
		tfSTDCALL_PROC_p_p_uint SwapMem;
		/// Filling the array value format unsigned char (dst, count, val)
		tfSTDCALL_PROC_p_uint_uint StocBMem;
		/// Filling the array value format short int (dst, count, val)
		tfSTDCALL_PROC_p_uint_uint StocSMem;
		/// Filling the array value format int (dst, count, val)
		tfSTDCALL_PROC_p_uint_uint StocIMem;
		/// Returns the index of the difference, if equal to -1 then
		tfSTDCALL_int_FUNC_p_p_uint CmpMem;
		/// Returns the value of the first difference, if equal to 0 then
		tfSTDCALL_int_FUNC_p_p_uint SubMem;
		///
		tfSTDCALL_int_FUNC_p_p_uint CmpMoveMem;
		/// Returns the position unsigned char from array to array+size (array val size)
		tfSTDCALL_int_FUNC_p_uint_int FindCMem;
		/// Returns the position of a short int from array to array+size (array val size)
		tfSTDCALL_int_FUNC_p_uint_int FindSMem;
		/// Returns the position of the int from array to array+size (array val size)
		tfSTDCALL_int_FUNC_p_uint_int FindIMem;
		/// Setting a bit value b
		tfSTDCALL_PROC_int_int_p SetBit;
		/// Returns the value of the bits a
		tfSTDCALL_int_FUNC_int_p GetBit;
		tfSTDCALL_p_FUNC_int GetFastSTDMulI; ///
		tfSTDCALL_p_FUNC_int GetFastFCMulI; ///

		/// Specifying the initial settings of the noise
		tfSTDCALL_PROC_int_int NoiseStart;
		/// The value of the noise sequence
		tfSTDCALL_int_FUNC NoiseGet;
		/// Saves the state of the noise generator 84 bytes
		tfSTDCALL_PROC_p NoiseSave;
		/// Loads the state of the noise generator 84 bytes
		tfSTDCALL_PROC_p NoiseLoad;

		/// ���������� ��������������� ������ rez=pow(2,trunc(log2(val-1)+1))
		tfSTDCALL_int_FUNC_int ILogSize;

		/// Converts the sequence of characters in the number
		tfSTDCALL_int_FUNC_p STRToI;
		/// ����������� ������������������ �������� � ����� � ��������� ������
		tfSTDCALL_float_FUNC_p STRToF;
		/// ����������� ������������������ �������� � ����� � ��������� ������ ������� ��������
		tfSTDCALL_double_FUNC_p STRToD;

		tfSTDCALL_PROC_p_uint_int IToSTR;

		///
		//tfSTDCALL_p_FUNC_p_p STRTok;
		/// ����� ������������ � ������ val1 ��������� val2 � ���� �� �����, ���������� ������
		tfSTDCALL_p_FUNC_p_p STRLeftFind;
		/// ����� ������������ � ������ val1 ��������� val2 � ����� �� ����, ���������� ������
		tfSTDCALL_p_FUNC_p_p STRRightFind;

		/// ����������� ��� ������� � ������
		tfSTDCALL_int_FUNC_int_int KeyToUniChar;

		/// Animation option (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_float_double FMotionPoint;
		/// Animation option (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_double_double DMotionPoint;
		/// Animation option (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_p_double V2FMotionPoint;
		/// Animation option (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_p_double V2DMotionPoint;
		/// Animation option (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_p_double V3FMotionPoint;
		/// Animation option (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_p_double V3DMotionPoint;
		/// Animation option (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_p_double V4FMotionPoint;
		/// Animation option (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_p_double V4DMotionPoint;

		/// �������� ��������� � �������� (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_float_double FMotionRad;
		/// �������� ��������� � �������� (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_double_double DMotionRad;
		/// �������� ��������� � �������� (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_p_double V2FMotionRad;
		/// �������� ��������� � �������� (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_p_double V2DMotionRad;
		/// �������� ��������� � �������� (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_p_double V3FMotionRad;
		/// �������� ��������� � �������� (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_p_double V3DMotionRad;
		/// �������� ��������� � �������� (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_p_double V4FMotionRad;
		/// �������� ��������� � �������� (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_p_double V4DMotionRad;

		tfSTDCALL_PROC_p_p V2FPCRCC;
		tfSTDCALL_PROC_p_p V3FPCRCC;
		tfSTDCALL_PROC_p_p V4FPCRCC;
		tfSTDCALL_PROC_p_p V2DPCRCC;
		tfSTDCALL_PROC_p_p V3DPCRCC;
		tfSTDCALL_PROC_p_p V4DPCRCC;

		tfSTDCALL_PROC_p_p_float_float V2FSplineCR;
		tfSTDCALL_PROC_p_p_float_float V3FSplineCR;
		tfSTDCALL_PROC_p_p_float_float V4FSplineCR;
		tfSTDCALL_PROC_p_p_double_double V2DSplineCR;
		tfSTDCALL_PROC_p_p_double_double V3DSplineCR;
		tfSTDCALL_PROC_p_p_double_double V4DSplineCR;

		/// �������������� ������ ������� � ������ � ������
		tfSTDCALL_PROC_p_p BLHToV3F;
		/// �������������� ������ ������� � ������ � ������ ������� ��������
		tfSTDCALL_PROC_p_p BLHToV3D;
		/// ������� �������������� ������ ������� � ������ � ������
		tfSTDCALL_PROC_p_p BLHToV3FFAST;
		/// ������� �������������� ������ ������� � ������ � ������ ������� ��������
		tfSTDCALL_PROC_p_p BLHToV3DFAST;
		/// �������������� ������ ������� � ��������� ������
		tfSTDCALL_PROC_float_float_p BLToV3F;
		/// �������������� ������ ������� � ��������� ������ ������� ��������
		tfSTDCALL_PROC_double_double_p BLToV3D;
		/// ������� �������������� ������ ������� � ��������� ������
		tfSTDCALL_PROC_float_float_p BLToV3FFAST;
		/// ������� �������������� ������ ������� � ��������� ������ ������� ��������
		tfSTDCALL_PROC_double_double_p BLToV3DFAST;
		/// �������������� ������� � ������ ������� � ������ (blh vec)
		tfSTDCALL_PROC_p_p V3FToBLH;
		/// �������������� ������� � ������ ������� � ������ ������� �������� (blh vec)
		tfSTDCALL_PROC_p_p V3DToBLH;
		/// �������������� ������� � ������ ������� (b l vec)
		tfSTDCALL_PROC_p_p_p V3FToBL;
		/// �������������� ������� � ������ ������� ������� �������� (b l vec)
		tfSTDCALL_PROC_p_p_p V3DToBL;

		char *FastCharDiv;
	};

	/**
	 * @class sFunctionsObjectCPU
	 *
	 * @ingroup apiinterface
	 * @brief sFunctionsObjectCPU - operators
	 *
	 * @see math, apiinterface
	 */

	struct sFunctionsObjectCPU {
		_int32 version;

		tfSTDCALL_p_FUNC ScriptCreate;
		tfSTDCALL_PROC_p_p_p ScriptInit;
		tfSTDCALL_PROC_p_p ScriptParser;
		tfSTDCALL_PROC_p ScriptExe;
		tfSTDCALL_PROC_p ScriptClear;
	};

	// draw:
	// S - span draw
	// T - triangle draw
	// bit per pixel:
	// 4A 4B - all 8888
	// 4E - RGBA8888 3,2,1,0
	// 4I - ARGB8888 2,1,0,3
	// type:
	// F - data in int and float
	// mode:
	// D - depth test (E - equal, L - low, G - not low equal)
	// S - shade color
	// A - alpha test
	// B - blend test
	// F - fog
	// T - texture

	/**
	 * @class sFunctionsRenderCPU
	 *
	 * @ingroup apiinterface
	 * @brief sFunctionsRenderCPU - ������� ����������� ����������
	 *
	 * @see math, apiinterface
	 */

	struct sFunctionsRenderCPU {
		int version;

		/// ���������� �������� ����� ��������� (void *rez,void*data,byte width)
		tfSTDCALL_PROC_p_p_int V3BHalfTexel;
		/// ���������� �������� ����� ��������� (void *rez,void*data,byte width)
		tfSTDCALL_PROC_p_p_int V4BHalfTexel;
		/// ����������������� ���������� ����� ��������� (void *rez,void*data,byte width,x,y)
		tfSTDCALL_PROC_p_p_int_float_float V3BTexel;
		/// ����������������� ���������� ����� ��������� (void *rez,void*data,byte width,x,y)
		tfSTDCALL_PROC_p_p_int_float_float V4BTexel;

		/// ������� ������������������ �������� ����� ������ � ������� RGBA 4 ����
		tfSTDCALL_PROC_p S4AFdraw;
		/// ������� ������������������ �������� ����� ������ � ������� RGBA 4 ����, � ������ ������� LESS
		tfSTDCALL_PROC_p S4AFDLdraw;
		/// ������� ������������������ �������� ����������������� ������ � ������� RGBA 4 ����
		tfSTDCALL_PROC_p S4AFSdraw;
		/// ������� ������������������ �������� ����������������� ������ � ������� RGBA 4 ����, � ������ ������� LESS
		tfSTDCALL_PROC_p S4AFDLSdraw;

		/// ������������ �����
		tfSTDCALL_PROC_p_p_float P4AFDraw;
		/// ������������ ����� � ����������� �����
		tfSTDCALL_PROC_p_p_float P4AFDrawAA;
		/// ������������ ����� � ����������� ����� BLEND ALPHA
		tfSTDCALL_PROC_p_p_float P4AFADrawAA;

		/// ������������ �����
		tfSTDCALL_PROC_p_p_float L4AFDraw;

		/// ��������� ������������ ������������
		tfSTDCALL_PROC_p_p T4AFDraw;
		/// ��������� ������������ ������������ � ������ ������ ������ �������
		tfSTDCALL_PROC_p_p T4AFSDraw;
	};

	struct S4AFdata {
		_int32 count;
		_int32 color;
		char *mem;
	};

	struct S4AFDdata {
		_int32 count;
		_int32 color;
		char *mem;
		char *depth;
		_int32 z;
		_int32 za;
		float zscale;
	};

	struct S4AFDSdata {
		_int32 count;
		_int32 color;
		char *mem;
		char *depth;
		_int32 z;
		_int32 za;
		float zscale;
		float cscale;
		_int32 color0;
		_int32 color1;
		_int32 color2;
		_int32 color3;
		_int32 color0step;
		_int32 color1step;
		_int32 color2step;
		_int32 color3step;
	};

	struct V4AFdata {
		float v[4];
		float c[4];
		float text[4][2];
		unsigned _int32 flag;
	};

	struct T4AFdata {
		char *mem;
		char *depth;
		_int32 stride;
		_int32 size;
		_int32 width;
		_int32 height;
		_int32 left;
		_int32 right;
	};

	/**
	 * @class sFunctionsGLContext
	 *
	 * @ingroup apiinterface
	 * @brief sFunctionsGLContext - function OpenGL interface standard for SOFT/GL/GLES imaging.
	 *
	 * @see GlContext, apiinterface.
	 */

	struct sFunctionsGLContext {
		_int32 version;
		unsigned _int32 extensionsFlag;
		tfSTDCALL_PROC_p BeginDraw;
		tfSTDCALL_PROC EndDraw;
		tfSTDCALL_PROC_p DrawMesh;
		
		tfSTDCALL_PROC_uint_float AlphaFunc;
		tfSTDCALL_PROC_uint_uint AttachShader;
		tfSTDCALL_PROC_uint_uint BindBuffer;
		tfSTDCALL_PROC_uint_uint BindTexture;
		tfSTDCALL_PROC_uint_uint BlendFunc;
		tfSTDCALL_PROC_uint_int_p_uint BufferData;
		tfSTDCALL_PROC_uint_int_int_p BufferSubData;
		tfSTDCALL_PROC_float_float_float_float Color4f;
		tfSTDCALL_PROC_p Color4fv;
		tfSTDCALL_PROC_uint_uint ColorMaterial;
		tfSTDCALL_PROC_int_uint_int_p ColorPointer;
		tfSTDCALL_PROC_uint CompileShader;
		tfSTDCALL_PROC_uint Clear;
		tfSTDCALL_PROC_float_float_float_float ClearAccum;
		tfSTDCALL_PROC_float_float_float_float ClearColor;
		tfSTDCALL_PROC_double ClearDepth;
		tfSTDCALL_uint_FUNC CreateProgram;
		tfSTDCALL_uint_FUNC_uint CreateShader;
		tfSTDCALL_PROC_uint CullFace;
		tfSTDCALL_PROC_int_p DeleteBuffers;
		tfSTDCALL_PROC_uint DeleteProgram;
		tfSTDCALL_PROC_uint DeleteShader;
		tfSTDCALL_PROC_int_p DeleteTextures;
		tfSTDCALL_PROC_uint DepthFunc;
		tfSTDCALL_PROC_bool DepthMask;
		tfSTDCALL_PROC_uint Disable;
		tfSTDCALL_PROC_uint DisableClientState;
		tfSTDCALL_PROC_uint_int_uint_p DrawElements; 
		tfSTDCALL_PROC_uint Enable;
		tfSTDCALL_PROC_uint EnableClientState;
		tfSTDCALL_PROC Finish;
		tfSTDCALL_PROC Flush;
		tfSTDCALL_PROC_int_p GenBuffers;
		tfSTDCALL_PROC_int_p GenTextures;
		tfSTDCALL_PROC_uint_int_p_p GetAttachedShaders;
		tfSTDCALL_PROC_uint_p GetBooleanv;
		tfSTDCALL_PROC_uint_uint_p GetBufferParameteriv;
		tfSTDCALL_PROC_uint_uint_p GetBufferPointerv;
		tfSTDCALL_PROC_uint_p_p_p GetBufferSubData;
		tfSTDCALL_PROC_uint_p GetDoublev;
		tfSTDCALL_uint_FUNC GetError;
		tfSTDCALL_PROC_uint_p GetFloatv;
		tfSTDCALL_PROC_uint_p GetIntegerv;
		tfSTDCALL_PROC_uint_uint_p GetProgramiv;
		tfSTDCALL_PROC_uint_int_p_p GetProgramInfoLog;
		tfSTDCALL_PROC_uint_uint_p GetShaderiv;
		tfSTDCALL_p_FUNC_uint GetString;
		tfSTDCALL_PROC_uint_uint_p GetTexParameteriv;
		tfSTDCALL_uint_FUNC_uint_p GetUniformLocation;
		tfSTDCALL_PROC_uint_uint Hint;
		tfSTDCALL_PROC InitNames;
		tfSTDCALL_bool_FUNC_uint IsBuffer;
		tfSTDCALL_bool_FUNC_uint IsEnabled;
		tfSTDCALL_PROC_uint_uint_p LightModelfv;
		tfSTDCALL_PROC_uint_uint_p Lightfv;
		tfSTDCALL_PROC_float LineWidth;
		tfSTDCALL_PROC_uint LinkProgram;
		tfSTDCALL_PROC LoadIdentity;
		tfSTDCALL_PROC_p LoadMatrixf;
		tfSTDCALL_PROC_p LoadMatrixd;
		tfSTDCALL_PROC_uint LoadName;
		tfSTDCALL_p_FUNC_uint_uint MapBuffer;
		tfSTDCALL_PROC_uint_uint_p Materialfv;
		tfSTDCALL_PROC_uint MatrixMode;
		tfSTDCALL_PROC_p MultMatrixd;
		tfSTDCALL_PROC_p MultMatrixf;
		tfSTDCALL_PROC_uint_int_p NormalPointer;
		tfSTDCALL_PROC_float PointSize;
		tfSTDCALL_PROC PopAttrib;
		tfSTDCALL_PROC PopMatrix;
		tfSTDCALL_PROC PopName;
		tfSTDCALL_PROC_uint PushAttrib;
		tfSTDCALL_PROC PushMatrix;
		tfSTDCALL_PROC_uint PushName;
		tfSTDCALL_PROC_int_int_int_int_uint_uint_p ReadPixels;
		tfSTDCALL_int_FUNC_uint RenderMode;
		tfSTDCALL_PROC_float_float_float Scalef;
		tfSTDCALL_PROC_int_int_int_int Scissor;
		tfSTDCALL_PROC_int_p SelectBuffer;
		tfSTDCALL_PROC_uint_int_p_p ShaderSource;
		tfSTDCALL_bool_FUNC_int SwapInterval;
		tfSTDCALL_PROC_int_uint_int_p TexCoordPointer;
		tfSTDCALL_PROC_uint_int_int_int_int_int_uint_uint_p TexImage2D;
		tfSTDCALL_PROC_uint_uint_int TexParameteri;
		tfSTDCALL_PROC_uint_int_int_int_int_int_uint_uint_p TexSubImage2D;
		tfSTDCALL_PROC_float_float_float Translatef;
		tfSTDCALL_PROC_uint_float Uniform1f;
		tfSTDCALL_PROC_uint_float_float Uniform2f;
		tfSTDCALL_PROC_uint_float_float_float Uniform3f;
		tfSTDCALL_PROC_uint_float_float_float_float Uniform4f;
		tfSTDCALL_PROC_uint_int_p Uniformiv;
		tfSTDCALL_PROC_uint_int_p Uniformfv;
		tfSTDCALL_PROC_uint_int_p Uniform2iv;
		tfSTDCALL_PROC_uint_int_p Uniform2fv;
		tfSTDCALL_PROC_uint_int_p Uniform3iv;
		tfSTDCALL_PROC_uint_int_p Uniform3fv;
		tfSTDCALL_PROC_uint_int_p Uniform4iv;
		tfSTDCALL_PROC_uint_int_p Uniform4fv;
		tfSTDCALL_bool_FUNC_uint UnmapBuffer;
		tfSTDCALL_PROC_uint UseProgram;
		tfSTDCALL_PROC_int_uint_int_p VertexPointer;
		tfSTDCALL_PROC_int_int_int_int Viewport;

	};

#ifdef __cplusplus
}
#endif

#endif
