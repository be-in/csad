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
		/// @param arg2 - степень.
		/// @return arg1*(2^arg2).
		tfSTDCALL_float_FUNC_float_int Fmul2N;
		/// multiply the number by 2 to the power N double precision
		/// @param arg1 - число.
		/// @param arg2 - степень.
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

		/// Перевод в целое, округление согласно настройкам округления (MXCSR)
		/// @return целое число.
		tfSTDCALL_int_FUNC_float FRound;
		/// Перевод в целое, округление согласно настройкам округления (MXCSR)
		/// @return целое число.
		tfSTDCALL_int_FUNC_double DRound;

		tfSTDCALL_float_FUNC_int IToF;
		tfSTDCALL_double_FUNC_long LToD;

		/// Масштабировать число с плавающей точкой и округлить отсечением дробной части
		tfSTDCALL_int_FUNC_float_int Fmul2NTrunc;
		/// Масштабировать число с плавающей точкой двойной точности и округлить отсечением дробной части
		tfSTDCALL_int_FUNC_double_int Dmul2NTrunc;

		/// Масштабировать число с плавающей точкой и округлить согласно настройкам округления (MXCSR)
		tfSTDCALL_int_FUNC_float_int Fmul2NRound;
		/// Масштабировать число с плавающей точкой двойной точности и округлить согласно настройкам округления (MXCSR)
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

		/// Вычисление значения сплайна катмула рома (c[4] x frac force).
		tfSTDCALL_PROC_p_p_float_float FSplineCR;
		/// Вычисление значения сплайна катмула рома (c[4] x frac force).
		tfSTDCALL_PROC_p_p_double_double DSplineCR;

		/// exponent
		tfSTDCALL_float_FUNC_float FExp;
		/// exponent
		tfSTDCALL_double_FUNC_double DExp;

		/// Логарифм по основанию 2, сокращение flog2
		tfSTDCALL_float_FUNC_float FLog2;
		/// Логарифм по основанию 2 двойной точности, сокращение dlog2
		tfSTDCALL_double_FUNC_double DLog2;
		/// Целочисленный логарифм по основанию 2, сокращение ilog2
		tfSTDCALL_int_FUNC_int ILog2;
		/// Целочисленный логарифм по основанию 2
		tfSTDCALL_int_FUNC_long LLog2;

		/// Полином
		tfSTDCALL_float_FUNC_p_uint_float FPoly1;
		/// Полином двойной точности
		tfSTDCALL_double_FUNC_p_uint_double DPoly1;
		/// Полином двух переменных (const1, maxpow2, maxpow3, val4, val5)
		tfSTDCALL_float_FUNC_p_uint_uint_float_float FPoly2;
		/// Полином двойной точности двух переменных (const1,maxpow2,maxpow3,val4,val5)
		tfSTDCALL_double_FUNC_p_uint_uint_double_double DPoly2;
		/// Полином множества переменных
		tfSTDCALL_float_FUNC_p_p_p_uint FPolyM;
		/// Полином двойной точности множества переменных
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
		/// @param arg1 - указатель источника 8 байт.
		/// @param arg2 - указатель приемника 8 байт.
		tfSTDCALL_PROC_p_p V4R16;
		/// Reverse sequence of double words
		/// @param arg1 - указатель источника 16 байт.
		/// @param arg2 - указатель приемника 16 байт.
		tfSTDCALL_PROC_p_p V4R32;
		/// The reverse sequence Quad words
		/// @param arg1 - указатель источника 32 байта.
		/// @param arg2 - указатель приемника 32 байта.
		tfSTDCALL_PROC_p_p V4R64;

		tfSTDCALL_PROC_p_p V2R32Copy;
		tfSTDCALL_PROC_p_p V3R32Copy;
		tfSTDCALL_PROC_p_p V4R32Copy;
		tfSTDCALL_PROC_p_p V2R64Copy;
		tfSTDCALL_PROC_p_p V3R64Copy;
		tfSTDCALL_PROC_p_p V4R64Copy;

		/// Конвертирование char во float
		/// @param arg1 - указатель источника 2 байта.
		/// @param arg2 - указатель приемника 8 байт.
		tfSTDCALL_PROC_p_p V2BTo2F;
		/// Конвертирование char во double
		/// @param arg1 - указатель источника 2 байта.
		/// @param arg2 - указатель приемника 16 байт.
		tfSTDCALL_PROC_p_p V2BTo2D;
		/// Конвертирование char во float
		/// @param arg1 - указатель источника 3 байта.
		/// @param arg2 - указатель приемника 12 байт.
		tfSTDCALL_PROC_p_p V3BTo3F;
		/// Конвертирование char во double
		/// @param arg1 - указатель источника 3 байта.
		/// @param arg2 - указатель приемника 24 байта.
		tfSTDCALL_PROC_p_p V3BTo3D;
		/// Конвертирование char во float
		/// @param arg1 - указатель источника 4 байта.
		/// @param arg2 - указатель приемника 16 байт.
		tfSTDCALL_PROC_p_p V4BTo4F;
		/// Конвертирование char во double
		/// @param arg1 - указатель источника 4 байта.
		/// @param arg2 - указатель приемника 32 байта.
		tfSTDCALL_PROC_p_p V4BTo4D;
		/// Конвертирование int во char
		tfSTDCALL_PROC_p_p V4ITo4B;
		/// Конвертирование int во float
		tfSTDCALL_PROC_p_p V2ITo2F;
		/// Конвертирование int во double
		tfSTDCALL_PROC_p_p V2ITo2D;
		/// Конвертирование int во float
		tfSTDCALL_PROC_p_p V3ITo3F;
		/// Конвертирование int во double
		tfSTDCALL_PROC_p_p V3ITo3D;
		/// Конвертирование int во float
		tfSTDCALL_PROC_p_p V4ITo4F;
		/// Конвертирование int во double
		tfSTDCALL_PROC_p_p V4ITo4D;
		/// Округление double в char
		tfSTDCALL_PROC_p_p V2FTo2B;
		/// Округление float в int
		tfSTDCALL_PROC_p_p V2FTo2I;
		/// Отсечение float в int
		tfSTDCALL_PROC_p_p V2FTTo2I;
		/// Конвертирование float в double
		tfSTDCALL_PROC_p_p V2FTo2D;
		/// Округление double в char
		tfSTDCALL_PROC_p_p V3FTo3B;
		/// Округление float в int
		tfSTDCALL_PROC_p_p V3FTo3I;
		/// Отсечение float в int
		tfSTDCALL_PROC_p_p V3FTTo3I;
		/// Конвертирование float в double
		tfSTDCALL_PROC_p_p V3FTo3D;
		/// Округление float в char
		tfSTDCALL_PROC_p_p V4FTo4B;
		/// Округление float в int
		tfSTDCALL_PROC_p_p V4FTo4I;
		/// Отсечение float в int
		tfSTDCALL_PROC_p_p V4FTTo4I;
		/// Конвертирование float в double
		tfSTDCALL_PROC_p_p V4FTo4D;
		/// Округление double в char
		tfSTDCALL_PROC_p_p V2DTo2B;
		/// Округление double в int
		tfSTDCALL_PROC_p_p V2DTo2I;
		/// Отсечение double в int
		tfSTDCALL_PROC_p_p V2DTTo2I;
		tfSTDCALL_PROC_p_p V2DTo2L;
		tfSTDCALL_PROC_p_p V2DTTo2L;
		/// Конвертирование double во float
		tfSTDCALL_PROC_p_p V2DTo2F;
		/// Округление double в char
		tfSTDCALL_PROC_p_p V3DTo3B;
		/// Округление double в int
		tfSTDCALL_PROC_p_p V3DTo3I;
		/// Отсечение double в int
		tfSTDCALL_PROC_p_p V3DTTo3I;
		/// Конвертирование double во float
		tfSTDCALL_PROC_p_p V3DTo3F;
		/// Округление double в char
		tfSTDCALL_PROC_p_p V4DTo4B;
		/// Округление double в int
		tfSTDCALL_PROC_p_p V4DTo4I;
		/// Отсечение double в int
		tfSTDCALL_PROC_p_p V4DTTo4I;
		/// Конвертирование double во float
		tfSTDCALL_PROC_p_p V4DTo4F;

		//V2FSinCos;
		//V3FSinCos;
		//V4FSinCos;
		//V2DSinCos;
		//V3DSinCos;
		//V4DSinCos;
		/// Обратный по знаку вектор
		tfSTDCALL_PROC_p_p V2FInv;
		/// Обратный по знаку вектор
		tfSTDCALL_PROC_p_p V3FInv;
		/// Обратный по знаку вектор
		tfSTDCALL_PROC_p_p V4FInv;
		/// Обратный по знаку вектор
		tfSTDCALL_PROC_p_p V2DInv;
		/// Обратный по знаку вектор
		tfSTDCALL_PROC_p_p V3DInv;
		/// Обратный по знаку вектор
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

		/// Векторное сложение (vec1+vec2=vec3)
		tfSTDCALL_PROC_p_p_p V2IAdd;
		/// Векторное сложение (vec1+vec2=vec3)
		tfSTDCALL_PROC_p_p_p V3IAdd;
		/// Векторное сложение (vec1+vec2=vec3)
		tfSTDCALL_PROC_p_p_p V4IAdd;
		/// Векторное сложение (vec1+vec2=vec3)
		tfSTDCALL_PROC_p_p_p V2FAdd;
		/// Векторное сложение (vec1+vec2=vec3)
		tfSTDCALL_PROC_p_p_p V3FAdd;
		/// Векторное сложение (vec1+vec2=vec3)
		tfSTDCALL_PROC_p_p_p V4FAdd;
		/// Векторное сложение (vec1+vec2=vec3)
		tfSTDCALL_PROC_p_p_p V2LAdd;
		/// Векторное сложение (vec1+vec2=vec3)
		tfSTDCALL_PROC_p_p_p V2DAdd;
		/// Векторное сложение (vec1+vec2=vec3)
		tfSTDCALL_PROC_p_p_p V3DAdd;
		/// Векторное сложение (vec1+vec2=vec3)
		tfSTDCALL_PROC_p_p_p V4DAdd;
		
		/// Векторное вычетание (vec1-vec2=vec3)
		tfSTDCALL_PROC_p_p_p V2ISub;
		/// Векторное вычетание (vec1-vec2=vec3)
		tfSTDCALL_PROC_p_p_p V3ISub;
		/// Векторное вычетание (vec1-vec2=vec3)
		tfSTDCALL_PROC_p_p_p V4ISub;
		/// Векторное вычетание (vec1-vec2=vec3)
		tfSTDCALL_PROC_p_p_p V2FSub;
		/// Векторное вычетание (vec1-vec2=vec3)
		tfSTDCALL_PROC_p_p_p V3FSub;
		/// Векторное вычетание (vec1-vec2=vec3)
		tfSTDCALL_PROC_p_p_p V4FSub;
		/// Векторное вычетание (vec1-vec2=vec3)
		tfSTDCALL_PROC_p_p_p V2LSub;
		/// Векторное вычетание (vec1-vec2=vec3)
		tfSTDCALL_PROC_p_p_p V2DSub;
		/// Векторное вычетание (vec1-vec2=vec3)
		tfSTDCALL_PROC_p_p_p V3DSub;
		/// Векторное вычетание (vec1-vec2=vec3)
		tfSTDCALL_PROC_p_p_p V4DSub;

		/// Умножение вектора на число (vec1*a=vec2)
		tfSTDCALL_PROC_p_p_float V2IScale;
		/// Умножение вектора на число (vec1*a=vec2)
		tfSTDCALL_PROC_p_p_float V3IScale;
		/// Умножение вектора на число (vec1*a=vec2)
		tfSTDCALL_PROC_p_p_float V4IScale;
		/// Умножение вектора на число (vec1*a=vec2)
		tfSTDCALL_PROC_p_p_float V2FScale;
		/// Умножение вектора на число (vec1*a=vec2)
		tfSTDCALL_PROC_p_p_float V3FScale;
		/// Умножение вектора на число (vec1*a=vec2)
		tfSTDCALL_PROC_p_p_float V4FScale;
		/// Умножение вектора на число (vec1*a=vec2)
		tfSTDCALL_PROC_p_p_double V2LScale;
		/// Умножение вектора на число (vec1*a=vec2)
		tfSTDCALL_PROC_p_p_double V2DScale;
		/// Умножение вектора на число (vec1*a=vec2)
		tfSTDCALL_PROC_p_p_double V3DScale;
		/// Умножение вектора на число (vec1*a=vec2)
		tfSTDCALL_PROC_p_p_double V4DScale;

		/// Поэлементное перемножение векторов
		tfSTDCALL_PROC_p_p_p V2IMul;
		/// Поэлементное перемножение векторов
		tfSTDCALL_PROC_p_p_p V3IMul;
		/// Поэлементное перемножение векторов
		tfSTDCALL_PROC_p_p_p V4IMul;
		/// Поэлементное перемножение векторов
		tfSTDCALL_PROC_p_p_p V2FMul;
		/// Поэлементное перемножение векторов
		tfSTDCALL_PROC_p_p_p V3FMul;
		/// Поэлементное перемножение векторов
		tfSTDCALL_PROC_p_p_p V4FMul;
		/// Поэлементное перемножение векторов
		tfSTDCALL_PROC_p_p_p V2DMul;
		/// Поэлементное перемножение векторов
		tfSTDCALL_PROC_p_p_p V3DMul;
		/// Поэлементное перемножение векторов
		tfSTDCALL_PROC_p_p_p V4DMul;

		/// Поэлементное деление векторов
		tfSTDCALL_PROC_p_p_p V2FDiv;
		/// Поэлементное деление векторов
		tfSTDCALL_PROC_p_p_p V3FDiv;
		/// Поэлементное деление векторов
		tfSTDCALL_PROC_p_p_p V4FDiv;
		/// Поэлементное деление векторов
		tfSTDCALL_PROC_p_p_p V2DDiv;
		/// Поэлементное деление векторов
		tfSTDCALL_PROC_p_p_p V3DDiv;
		/// Поэлементное деление векторов
		tfSTDCALL_PROC_p_p_p V4DDiv;

		/// умножение на 2 в степени N и отсечение float в int
		tfSTDCALL_PROC_p_p_int V2Fmul2NTrunc;
		/// умножение на 2 в степени N и отсечение float в int
		tfSTDCALL_PROC_p_p_int V3Fmul2NTrunc;
		/// умножение на 2 в степени N и отсечение float в int
		tfSTDCALL_PROC_p_p_int V4Fmul2NTrunc;
		/// умножение на 2 в степени N и отсечение double в int
		tfSTDCALL_PROC_p_p_int V2Dmul2NTrunc;
		/// умножение на 2 в степени N и отсечение double в int
		tfSTDCALL_PROC_p_p_int V3Dmul2NTrunc;
		/// умножение на 2 в степени N и отсечение double в int
		tfSTDCALL_PROC_p_p_int V4Dmul2NTrunc;
		/// умножение на 2 в степени N и округление float в int
		tfSTDCALL_PROC_p_p_int V2Fmul2NRound;
		/// умножение на 2 в степени N и округление float в int
		tfSTDCALL_PROC_p_p_int V3Fmul2NRound;
		/// умножение на 2 в степени N и округление float в int
		tfSTDCALL_PROC_p_p_int V4Fmul2NRound;
		/// умножение на 2 в степени N и округление double в int
		tfSTDCALL_PROC_p_p_int V2Dmul2NRound;
		/// умножение на 2 в степени N и округление double в int
		tfSTDCALL_PROC_p_p_int V3Dmul2NRound;
		/// умножение на 2 в степени N и округление double в int
		tfSTDCALL_PROC_p_p_int V4Dmul2NRound;
		/// multiplication by 2 to the power N
		/// @param arg1 - two-dimensional single precision vector
		/// @param arg2 - the result is a two-dimensional single precision vector
		tfSTDCALL_PROC_p_p_int V2Imul2N;
		/// multiplication by 2 to the power N
		/// @param arg1 - трехмерный вектор одинарной точности
		/// @param arg2 - результат трехмерный вектор одинарной точности
		tfSTDCALL_PROC_p_p_int V3Imul2N;
		/// multiplication by 2 to the power N
		/// @param arg1 - четырехмерный вектор одинарной точности
		/// @param arg2 - результат четырехмерный вектор одинарной точности
		tfSTDCALL_PROC_p_p_int V4Imul2N;
		/// multiplication by 2 to the power N
		/// @param arg1 - two-dimensional single precision vector
		/// @param arg2 - the result is a two-dimensional single precision vector
		tfSTDCALL_PROC_p_p_int V2Fmul2N;
		/// multiplication by 2 to the power N
		/// @param arg1 - трехмерный вектор одинарной точности
		/// @param arg2 - результат трехмерный вектор одинарной точности
		tfSTDCALL_PROC_p_p_int V3Fmul2N;
		/// multiplication by 2 to the power N
		/// @param arg1 - четырехмерный вектор одинарной точности
		/// @param arg2 - результат четырехмерный вектор одинарной точности
		tfSTDCALL_PROC_p_p_int V4Fmul2N;
		/// умножение на 2 в степени N
		/// @param arg1 - two-dimensional double precision vector
		/// @param arg2 - результат двухмерный вектор двойной точности
		tfSTDCALL_PROC_p_p_int V2Dmul2N;
		/// умножение на 2 в степени N
		/// @param arg1 - трехмерный вектор двойной точности
		/// @param arg2 - результат трехмерный вектор двойной точности
		tfSTDCALL_PROC_p_p_int V3Dmul2N;
		/// умножение на 2 в степени N
		/// @param arg1 - четырехмерный вектор двойной точности
		/// @param arg2 - результат четырехмерный вектор двойной точности
		tfSTDCALL_PROC_p_p_int V4Dmul2N;

		/// Скалярное умножение векторов
		tfSTDCALL_float_FUNC_p_p V2FDot;
		/// Скалярное умножение векторов
		tfSTDCALL_float_FUNC_p_p V3FDot;
		/// Скалярное умножение векторов
		tfSTDCALL_float_FUNC_p_p V4FDot;
		/// Скалярное умножение векторов
		tfSTDCALL_double_FUNC_p_p V2DDot;
		/// Скалярное умножение векторов
		tfSTDCALL_double_FUNC_p_p V3DDot;
		/// Скалярное умножение векторов
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
		/// @param arg1 - двухмерный вектор целочисленный 64
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

		/// Векторное умножение
		tfSTDCALL_int_FUNC_p_p V2ICross;
		/// Векторное умножение
		tfSTDCALL_float_FUNC_p_p V2FCross;
		/// Векторное умножение
		tfSTDCALL_PROC_p_p_p V3FCross;
		/// Векторное умножение
		tfSTDCALL_long_FUNC_p_p V2LCross;
		/// Векторное умножение
		tfSTDCALL_double_FUNC_p_p V2DCross;
		/// Векторное умножение
		/// @param arg1 - вектор а
		/// @param arg2 - вектор б
		/// @param arg3 - результат
		tfSTDCALL_PROC_p_p_p V3DCross;

		/// Вектор еденичной длинны с умножением на 2 в степени
		/// @param arg1 - vector
		/// @param arg2 - normalized vector
		/// @param arg3 - pow
		tfSTDCALL_PROC_p_p_int V2INormalMul2N;
		/// Вектор еденичной длинны с умножением на 2 в степени
		/// @param arg1 - vector
		/// @param arg2 - normalized vector
		/// @param arg3 - pow
		tfSTDCALL_PROC_p_p_int V3INormalMul2N;
		/// Вектор еденичной длинны с умножением на 2 в степени
		/// @param arg1 - vector
		/// @param arg2 - normalized vector
		/// @param arg3 - pow
		tfSTDCALL_PROC_p_p_int V4INormalMul2N;
		/// Вектор еденичной длинны (vec2=vec1*(1/length(vec1)))
		/// @param arg1 - vector
		/// @param arg2 - normalized vector
		tfSTDCALL_PROC_p_p V2FNormal;
		/// Вектор еденичной длинны (vec2=vec1*(1/length(vec1)))
		/// @param arg1 - vector
		/// @param arg2 - normalized vector
		tfSTDCALL_PROC_p_p V3FNormal;
		/// Вектор еденичной длинны (vec2=vec1*(1/length(vec1)))
		/// @param arg1 - vector
		/// @param arg2 - normalized vector
		tfSTDCALL_PROC_p_p V4FNormal;
		/// Вектор еденичной длинны (vec2=vec1*(1/length(vec1)))
		/// @param arg1 - two-dimensional double precision vector
		/// @param arg2 - normalized vector
		tfSTDCALL_PROC_p_p V2DNormal;
		/// Вектор еденичной длинны (vec2=vec1*(1/length(vec1)))
		/// @param arg1 - vector
		/// @param arg2 - normalized vector
		tfSTDCALL_PROC_p_p V3DNormal;
		/// Вектор еденичной длинны (vec2=vec1*(1/length(vec1)))
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

		/// Интерполяция вектора (vec1+(vec2-vec1)*a=vec3)
		tfSTDCALL_PROC_p_p_p_float V2FLerp;
		/// Интерполяция вектора (vec1+(vec2-vec1)*a=vec3)
		tfSTDCALL_PROC_p_p_p_float V3FLerp;
		/// Интерполяция вектора (vec1+(vec2-vec1)*a=vec3)
		tfSTDCALL_PROC_p_p_p_float V4FLerp;
		/// Интерполяция вектора (vec1+(vec2-vec1)*a=vec3)
		tfSTDCALL_PROC_p_p_p_double V2DLerp;
		/// Интерполяция вектора (vec1+(vec2-vec1)*a=vec3)
		tfSTDCALL_PROC_p_p_p_double V3DLerp;
		/// Интерполяция вектора (vec1+(vec2-vec1)*a=vec3)
		tfSTDCALL_PROC_p_p_p_double V4DLerp;

		/// Масштабирование и сложение двух векторов - формула (vec1*a+vec2*b=vec3)
		/// @param arg1 - vector a
		/// @param arg2 - vector b
		/// @param arg3 - result vector
		/// @param arg4 - scale vector a
		/// @param arg5 - scale vector b
		tfSTDCALL_PROC_p_p_p_float_float V2FCombine;
		/// Формула (vec1*a+vec2*b=vec3)
		/// @param arg1 - vector a
		/// @param arg2 - vector b
		/// @param arg3 - result vector
		/// @param arg4 - scale vector a
		/// @param arg5 - scale vector b
		tfSTDCALL_PROC_p_p_p_float_float V3FCombine;
		/// Формула (vec1*a+vec2*b=vec3)
		/// @param arg1 - vector a
		/// @param arg2 - vector b
		/// @param arg3 - result vector
		/// @param arg4 - scale vector a
		/// @param arg5 - scale vector b
		tfSTDCALL_PROC_p_p_p_float_float V4FCombine;
		/// Формула (vec1*a+vec2*b=vec3)
		/// @param arg1 - vector a
		/// @param arg2 - vector b
		/// @param arg3 - result vector
		/// @param arg4 - scale vector a
		/// @param arg5 - scale vector b
		tfSTDCALL_PROC_p_p_p_double_double V2DCombine;
		/// Формула (vec1*a+vec2*b=vec3)
		/// @param arg1 - vector a
		/// @param arg2 - vector b
		/// @param arg3 - result vector
		/// @param arg4 - scale vector a
		/// @param arg5 - scale vector b
		tfSTDCALL_PROC_p_p_p_double_double V3DCombine;
		/// Формула (vec1*a+vec2*b=vec3)
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

		/// Отражение вектора относительно нормали (vec1, nor2, rez3)
		tfSTDCALL_PROC_p_p_p V2FReflect;
		/// Отражение вектора относительно нормали (vec1, nor2, rez3)
		tfSTDCALL_PROC_p_p_p V2DReflect;
		/// Отражение вектора относительно нормали (vec1, nor2, rez3)
		tfSTDCALL_PROC_p_p_p V3FReflect;
		/// Отражение вектора относительно нормали (vec1, nor2, rez3)
		tfSTDCALL_PROC_p_p_p V3DReflect;

		/// Угол между векторами
		/// @param arg1 - vector a
		/// @param arg2 - vector b
		/// @return angle.
		tfSTDCALL_float_FUNC_p_p V2FAngle;
		/// Угол между векторами
		/// @param arg1 - vector a
		/// @param arg2 - vector b
		/// @return angle.
		tfSTDCALL_float_FUNC_p_p V3FAngle;
		/// Угол между векторами
		/// @param arg1 - vector a
		/// @param arg2 - vector b
		/// @return angle.
		tfSTDCALL_double_FUNC_p_p V2DAngle;
		/// Угол между векторами
		/// @param arg1 - vector a
		/// @param arg2 - vector b
		/// @return angle.
		tfSTDCALL_double_FUNC_p_p V3DAngle;

		/// Расстояние между плоскостью и точкой по направлению луча (plane1, normal2, point3, ray4)
		/// @param arg1 - plane point
		/// @param arg2 - plane normal
		/// @param arg3 - point
		/// @param arg4 - normalized ray
		/// @return distance.
		tfSTDCALL_float_FUNC_p_p V3FDPFR;
		/// Расстояние между плоскостью и точкой по направлению луча (plane1, normal2, point3, ray4)
		/// @param arg1 - plane point
		/// @param arg2 - plane normal
		/// @param arg3 - point
		/// @param arg4 - normalized ray
		/// @return distance.
		tfSTDCALL_double_FUNC_p_p V3DDPFR;

		/// Вычесляет нормаль для плоскости заданной точками vec1, vec2, vec3
		/// @param arg1 - plane point vec1
		/// @param arg2 - plane point vec2
		/// @param arg3 - plane point vec3
		/// @param arg4 - rezult plane normal
		tfSTDCALL_PROC_p_p_p_p V3FTriNorm;
		/// Вычесляет нормаль двойной точности для плоскости заданной точками vec1, vec2, vec3
		/// @param arg1 - plane point vec1
		/// @param arg2 - plane point vec2
		/// @param arg3 - plane point vec3
		/// @param arg4 - rezult plane normal
		tfSTDCALL_PROC_p_p_p_p V3DTriNorm;

		/// Добовляет вычесленную нормаль треугольника NORM(CROSS(vec1-vec2,vec1-vec3)) к элементам со смещением vec1+off4, vec2+off4, vec3+off4
		/// @param arg1 - plane point vec1
		/// @param arg2 - plane point vec2
		/// @param arg3 - plane point vec3
		/// @param arg4 - normal offset from vec1 to normal1
		tfSTDCALL_PROC_p_p_p_int V3FAddTriNorm;
		/// Добовляет вычесленную нормаль треугольника NORM(CROSS(vec1-vec2,vec1-vec3)) к элементам со смещением vec1+off4, vec2+off4, vec3+off4
		/// @param arg1 - plane point vec1
		/// @param arg2 - plane point vec2
		/// @param arg3 - plane point vec3
		/// @param arg4 - normal offset from vec1 to normal1
		tfSTDCALL_PROC_p_p_p_int V3FAdd3DTriNorm;
		/// Добовляет вычесленную нормаль треугольника NORM(CROSS(vec1-vec2,vec1-vec3)) к элементам со смещением vec1+off4, vec2+off4, vec3+off4
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

		/// Матричное преобразование вектора
		tfSTDCALL_PROC_p_p_p V2ITransform;
		/// Матричное преобразование вектора
		tfSTDCALL_PROC_p_p_p V3ITransform;
		/// Матричное преобразование вектора
		tfSTDCALL_PROC_p_p_p V4ITransform;
		/// Матричное преобразование вектора
		tfSTDCALL_PROC_p_p_p V2FTransform;
		/// Матричное преобразование вектора
		tfSTDCALL_PROC_p_p_p V3FTransform;
		/// Матричное преобразование вектора
		tfSTDCALL_PROC_p_p_p V4FTransform;
		/// Матричное преобразование вектора
		tfSTDCALL_PROC_p_p_p V2DTransform;
		/// Матричное преобразование вектора
		tfSTDCALL_PROC_p_p_p V3DTransform;
		/// Матричное преобразование вектора
		tfSTDCALL_PROC_p_p_p V4DTransform;

		/// The multiplication of a vector by a matrix
		/// arg1 - two-dimensional single precision vector
		/// arg2 - four-dimensional matrix, use the first two rows and column
		/// arg3 - the result is a two-dimensional single precision vector
		tfSTDCALL_PROC_p_p_p V2FMMul;
		/// The multiplication of a vector by a matrix
		tfSTDCALL_PROC_p_p_p V3FMMul;
		/// Умножение вектора на матрицу
		tfSTDCALL_PROC_p_p_p V4FMMul;
		/// Умножение вектора на матрицу
		tfSTDCALL_PROC_p_p_p V2DMMul;
		/// Умножение вектора на матрицу
		tfSTDCALL_PROC_p_p_p V3DMMul;
		/// Умножение вектора на матрицу
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

		/// Разложение на компоненты
		/// @param arg1 - quaternion.
		/// @param arg2 - result vector.
		tfSTDCALL_PROC_p_p Q4FVector;
		/// Разложение на компоненты
		/// @param arg1 - quaternion.
		/// @param arg2 - result vector.
		tfSTDCALL_PROC_p_p Q4DVector;

		/// Разворот кватерниона
		/// @param arg1 - quaternion.
		/// @param arg2 - result invert quaternion.
		tfSTDCALL_PROC_p_p QFInv;
		/// Разворот кватерниона
		/// @param arg1 - quaternion.
		/// @param arg2 - result invert quaternion.
		tfSTDCALL_PROC_p_p QDInv;

		/// Сложение кватернионов - средний поворот
		/// @param arg1 - quaternion a.
		/// @param arg2 - quaternion b.
		/// @param arg3 - result quaternion.
		tfSTDCALL_PROC_p_p_p QFAdd;
		/// Сложение кватернионов - средний поворот
		/// @param arg1 - quaternion a.
		/// @param arg2 - quaternion b.
		/// @param arg3 - result quaternion.
		tfSTDCALL_PROC_p_p_p QDAdd;

		/// Перемножение кватернионов
		/// @param arg1 - quaternion a.
		/// @param arg2 - quaternion b.
		/// @param arg3 - result quaternion.
		tfSTDCALL_PROC_p_p_p QFMul;
		/// Перемножение кватернионов
		/// @param arg1 - quaternion a.
		/// @param arg2 - quaternion b.
		/// @param arg3 - result quaternion.
		tfSTDCALL_PROC_p_p_p QDMul;

		/// ???
		tfSTDCALL_float_FUNC_p QFNorm;
		/// ???
		tfSTDCALL_double_FUNC_p QDNorm;

		/// Получение кватерниона через углы эйлера
		/// @param arg1 - euler angles (x, y, z).
		/// @param arg2 - result quaternion.
		tfSTDCALL_PROC_p_p QFEuler;
		/// Получение кватерниона через углы эйлера
		/// @param arg1 - euler angles (x, y, z).
		/// @param arg2 - result quaternion.
		tfSTDCALL_PROC_p_p QDEuler;

		/// Преобразование кватерниона в матрицу
		/// @param arg1 - quaternion
		/// @param arg2 - rezult matrix
		tfSTDCALL_PROC_p_p Q4FMatrix;
		/// Преобразование кватерниона в матрицу
		/// @param arg1 - quaternion
		/// @param arg2 - rezult matrix
		tfSTDCALL_PROC_p_p Q4DMatrix;

		/// Афинное преобразование
		/// @param arg1 - vector
		/// @param arg2 - transform vector
		/// @param arg3 - rezult vector
		tfSTDCALL_PROC_p_p_p V2FAfineTransform;
		/// Афинное преобразование
		/// @param arg1 - vector
		/// @param arg2 - transform vector
		/// @param arg3 - rezult vector
		tfSTDCALL_PROC_p_p_p V2DAfineTransform;

		/// Умножение вектора на обратный кватернион (vec2*quat1=vec3)
		/// @param quat1 - quaternion.
		/// @param vec2 - vector.
		/// @param vec3 - result vector.
		tfSTDCALL_PROC_p_p_p Q2FInvTransform;
		/// Умножение вектора на обратный кватернион (vec2*quat1=vec3)
		/// @param quat1 - quaternion.
		/// @param vec2 - vector.
		/// @param vec3 - result vector.
		tfSTDCALL_PROC_p_p_p Q2DInvTransform;
		/// Умножение вектора на обратный кватернион (vec2*quat1=vec3)
		/// @param quat1 - quaternion.
		/// @param vec2 - vector.
		/// @param vec3 - result vector.
		tfSTDCALL_PROC_p_p_p Q3FInvTransform;
		/// Умножение вектора на обратный кватернион (vec2*quat1=vec3)
		/// @param quat1 - quaternion.
		/// @param vec2 - vector.
		/// @param vec3 - result vector.
		tfSTDCALL_PROC_p_p_p Q3DInvTransform;

		/// Транспанирование матрицы
		tfSTDCALL_PROC_p_p M4FTranspose;
		/// Транспанирование матрицы
		tfSTDCALL_PROC_p_p M4DTranspose;
		/// Матричное умножение
		tfSTDCALL_PROC_p_p_p M4FMul;
		/// Матричное умножение
		tfSTDCALL_PROC_p_p_p M4DMul;
		/// Обратная матрица
		tfSTDCALL_int_FUNC_p_p M4FInv;
		/// Обратная матрица
		tfSTDCALL_int_FUNC_p_p M4DInv;
		/// The perspective projection matrix
		/// @param arg1 - матрица.
		/// @param arg2 - ширина.
		/// @param arg3 - высота.
		/// @param arg4 - положение дальней плоскости.
		/// @param arg5 - положение ближней.
		/// @param arg6 - угол зрения.
		tfSTDCALL_PROC_p_int_int_float_float_float M4FPerspective;
		/// The perspective projection matrix
		/// @param arg1 - указатель на матрицу двойной точности.
		/// @param arg2 - ширина.
		/// @param arg3 - высота.
		/// @param arg4 - положение дальней плоскости.
		/// @param arg5 - положение ближней.
		/// @param arg6 - угол зрения.
		tfSTDCALL_PROC_p_int_int_double_double_double M4DPerspective;
		/// The ortographic projection matrix
		/// @param arg1 - матрица.
		/// @param arg2 - ширина.
		/// @param arg3 - высота.
		/// @param arg4 - положение дальней плоскости.
		/// @param arg5 - положение ближней.
		/// @param arg6 - маштаб проекции.
		tfSTDCALL_PROC_p_int_int_float_float_float M4FOrtographic;
		/// The ortographic projection matrix
		/// @param arg1 - указатель на матрицу двойной точности.
		/// @param arg2 - ширина.
		/// @param arg3 - высота.
		/// @param arg4 - положение дальней плоскости.
		/// @param arg5 - положение ближней.
		/// @param arg6 - маштаб проекции.
		tfSTDCALL_PROC_p_int_int_double_double_double M4DOrtographic;
		/// Еденичная матрица
		tfSTDCALL_PROC_p M4FIdentity;
		/// Еденичная матрица
		tfSTDCALL_PROC_p M4DIdentity;
		/// Extract quaternion from matrix
		/// @param arg1 - matrix
		/// @param arg2 - rezult quaternion
		tfSTDCALL_PROC_p_p M4FQuaternion;
		/// Extract quaternion from matrix
		/// @param arg1 - matrix
		/// @param arg2 - rezult quaternion
		tfSTDCALL_PROC_p_p M4DQuaternion;
		/// Матрица переноса
		tfSTDCALL_PROC_p_p M4FTranslate;
		/// Матрица переноса
		tfSTDCALL_PROC_p_p M4DTranslate;
		/// Матрица маштабирования
		tfSTDCALL_PROC_p_p M4FScale;
		/// Матрица маштабирования
		tfSTDCALL_PROC_p_p M4DScale;
		/// Умножение на матрицу переноса
		/// @param arg1 - matrix
		/// @param arg2 - translate vector
		/// @param arg3 - result matrix
		tfSTDCALL_PROC_p_p_p M4FAddTranslate;
		/// Умножение на матрицу переноса
		/// @param arg1 - matrix
		/// @param arg2 - translate vector
		/// @param arg3 - result matrix
		tfSTDCALL_PROC_p_p_p M4DAddTranslate;
		/// Умножение на матрицу маштабирования
		/// @param arg1 - matrix
		/// @param arg2 - scale vector
		/// @param arg3 - result matrix
		tfSTDCALL_PROC_p_p_p M4FAddScale;
		/// Умножение на матрицу маштабирования
		/// @param arg1 - matrix
		/// @param arg2 - scale vector
		/// @param arg3 - result matrix
		tfSTDCALL_PROC_p_p_p M4DAddScale;
		/// Умножение матрицы на кватернион
		/// @param arg1 - matrix
		/// @param arg2 - quaternion
		/// @param arg3 - result matrix
		tfSTDCALL_PROC_p_p_p M4FAddRotate;
		/// Умножение матрицы на кватернион
		/// @param arg1 - matrix
		/// @param arg2 - quaternion
		/// @param arg3 - result matrix
		tfSTDCALL_PROC_p_p_p M4DAddRotate;

		/// Преобразовани матрицы двойной точности в одинарную
		tfSTDCALL_PROC_p_p M4DToM4F;
		/// Преобразовани матрицы одинарной точности в двойную
		tfSTDCALL_PROC_p_p M4FToM4D;

		/// Формирование матрицы трансформации за счет точки положения разворота и масштаба объекта, в прямом формате данных
		/// @param arg1 - result matrix
		/// @param arg2 - position
		/// @param arg3 - rotation
		/// @param arg4 - scale
		tfSTDCALL_PROC_p_p_p_p M4FTRSDDF;
		/// Формирование матрицы трансформации за счет точки положения разворота и масштаба объекта, в прямом формате данных
		/// @param arg1 - result matrix
		/// @param arg2 - position
		/// @param arg3 - rotation
		/// @param arg4 - scale
		tfSTDCALL_PROC_p_p_p_p M4DTRSDDF;
		/// Формирование матрицы трансформации за счет точки положения разворота и масштаба объекта
		/// @param arg1 - result matrix
		/// @param arg2 - position
		/// @param arg3 - rotation
		/// @param arg4 - scale
		tfSTDCALL_PROC_p_p_p_p M4FTRS;
		/// Формирование матрицы трансформации за счет точки положения разворота и масштаба объекта
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

		/// Расширить массив векторов до трехметрого
		tfSTDCALL_PROC_p_p_int_int_uint A2FGrow3F;
		/// Расширить массив векторов до четырехмерного
		tfSTDCALL_PROC_p_p_int_int_uint A2FGrow4F;
		/// Расширить массив векторов до четырехмерного
		tfSTDCALL_PROC_p_p_int_int_uint A3FGrow4F;
		/// Расширить массив векторов до трехметрого
		tfSTDCALL_PROC_p_p_int_int_uint A2DGrow3D;
		/// Расширить массив векторов до четырехмерного
		tfSTDCALL_PROC_p_p_int_int_uint A2DGrow4D;
		/// Расширить массив векторов до четырехмерного
		tfSTDCALL_PROC_p_p_int_int_uint A3DGrow4D;

		/// Расширить массив векторов до трехметрого с плавающй точкой
		tfSTDCALL_PROC_p_p_int_int_uint A2IGrowTo3F;
		/// Расширить массив векторов до четырехмерного с плавающй точкой
		tfSTDCALL_PROC_p_p_int_int_uint A2IGrowTo4F;
		/// Расширить массив векторов до четырехмерного с плавающй точкой
		tfSTDCALL_PROC_p_p_int_int_uint A3IGrowTo4F;
		/// Расширить массив векторов до трехметрого с плавающй точкой
		tfSTDCALL_PROC_p_p_int_int_uint A2IGrowTo3D;
		/// Расширить массив векторов до четырехмерного с плавающй точкой
		tfSTDCALL_PROC_p_p_int_int_uint A2IGrowTo4D;
		/// Расширить массив векторов до четырехмерного с плавающй точкой
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

		/// Сложить два массива векторов (arr1/rez arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_int_uint A2FSum;
		/// Сложить два массива векторов (arr1/rez arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_int_uint A3FSum;
		/// Сложить два массива векторов (arr1/rez arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_int_uint A4FSum;
		/// Сложить два массива векторов (arr1/rez arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_int_uint A2DSum;
		/// Сложить два массива векторов (arr1/rez arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_int_uint A3DSum;
		/// Сложить два массива векторов (arr1/rez arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_int_uint A4DSum;

		/// Добавить ко всем элементам вектор (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A2FAddVector;
		/// Добавить ко всем элементам вектор (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A3FAddVector;
		/// Добавить ко всем элементам вектор (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A4FAddVector;
		/// Добавить ко всем элементам вектор (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A2DAddVector;
		/// Добавить ко всем элементам вектор (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A3DAddVector;
		/// Добавить ко всем элементам вектор (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A4DAddVector;

		/// Сложить два массива векторов (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A2IAdd;
		/// Сложить два массива векторов (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A3IAdd;
		/// Сложить два массива векторов (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A4IAdd;
		/// Сложить два массива векторов (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A2FAdd;
		/// Сложить два массива векторов (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A3FAdd;
		/// Сложить два массива векторов (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A4FAdd;
		/// Сложить два массива векторов (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A2DAdd;
		/// Сложить два массива векторов (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A3DAdd;
		/// Сложить два массива векторов (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A4DAdd;

		/// Вычесть из всех элементов вектор (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A2FSubVector;
		/// Вычесть из всех элементов вектор (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A3FSubVector;
		/// Вычесть из всех элементов вектор (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A4FSubVector;
		/// Вычесть из всех элементов вектор (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A2DSubVector;
		/// Вычесть из всех элементов вектор (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A3DSubVector;
		/// Вычесть из всех элементов вектор (arr1 vec1 arr2 step1 step2 count)
		tfSTDCALL_PROC_p_p_p_int_int_uint A4DSubVector;

		/// Вычесть два массива векторов (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A2ISub;
		/// Вычесть два массива векторов (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A3ISub;
		/// Вычесть два массива векторов (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A4ISub;
		/// Вычесть два массива векторов (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A2FSub;
		/// Вычесть два массива векторов (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A3FSub;
		/// Вычесть два массива векторов (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A4FSub;
		/// Вычесть два массива векторов (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A2DSub;
		/// Вычесть два массива векторов (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A3DSub;
		/// Вычесть два массива векторов (arr1 arr2 rez3 step1 step2 step3 count)
		tfSTDCALL_PROC_p_p_p_int_int_int_uint A4DSub;

		/// Масштабирование массива векторов
		tfSTDCALL_PROC_p_p_float_int_int_uint A2FScale;
		/// Масштабирование массива векторов
		tfSTDCALL_PROC_p_p_float_int_int_uint A3FScale;
		/// Масштабирование массива векторов
		tfSTDCALL_PROC_p_p_float_int_int_uint A4FScale;
		/// Масштабирование массива векторов
		tfSTDCALL_PROC_p_p_double_int_int_uint A2DScale;
		/// Масштабирование массива векторов
		tfSTDCALL_PROC_p_p_double_int_int_uint A3DScale;
		/// Масштабирование массива векторов
		tfSTDCALL_PROC_p_p_double_int_int_uint A4DScale;

		/// Умножить массив векторов на вектор
		tfSTDCALL_PROC_p_p_p_int_int_uint A2FMulVector;
		/// Умножить массив векторов на вектор
		tfSTDCALL_PROC_p_p_p_int_int_uint A3FMulVector;
		/// Умножить массив векторов на вектор
		tfSTDCALL_PROC_p_p_p_int_int_uint A4FMulVector;
		/// Умножить массив векторов на вектор
		tfSTDCALL_PROC_p_p_p_int_int_uint A2DMulVector;
		/// Умножить массив векторов на вектор
		tfSTDCALL_PROC_p_p_p_int_int_uint A3DMulVector;
		/// Умножить массив векторов на вектор
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
		/// @param aрг1 - массив a
		/// @param aрг2 - массив результата
		/// @param aрг3 - шаг элементов массива a
		/// @param aрг4 - шаг элементов массива результата
		/// @param aрг5 - количество элементов в массиве
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

		/// Интерполяция массива векторов
		/// @param aрг1 - массив a
		/// @param aрг2 - массив b
		/// @param aрг3 - массив результата
		/// @param aрг4 - коэффициент
		/// @param aрг5 - шаг элементов массива a
		/// @param aрг6 - шаг элементов массива b
		/// @param aрг7 - шаг элементов массива результата
		/// @param aрг8 - количество элементов в массиве
		tfSTDCALL_PROC_p_p_p_float_int_int_int_uint A2FLerp;
		/// Интерполяция массива векторов
		tfSTDCALL_PROC_p_p_p_float_int_int_int_uint A3FLerp;
		/// Интерполяция массива векторов
		tfSTDCALL_PROC_p_p_p_float_int_int_int_uint A4FLerp;
		/// Интерполяция массива векторов
		tfSTDCALL_PROC_p_p_p_double_int_int_int_uint A2DLerp;
		/// Интерполяция массива векторов
		tfSTDCALL_PROC_p_p_p_double_int_int_int_uint A3DLerp;
		/// Интерполяция массива векторов
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
	 * @brief sFunctionsArrayCPU - функции обработки массивов
	 *
	 * A - сортированный массив
	 * D - массив
	 * M - ассоциативный массив
	 *
	 * P - елементы массива указатели
	 * S - елементы массива короткие строки до 127 байт.
	 *
	 * @see apiinterface
	 */

	struct sFunctionsArrayCPU {
		_int32 version;

		/// Инициализация строки
		tfSTDCALL_p_FUNC_p SCreate;
		/// Инициализация длинной строки ??
		tfSTDCALL_p_FUNC_p LSCreate;
		/// Инициализация массива
		tfSTDCALL_PROC_p_uint_uint ANTInit;
		/// Инициализация массива строк ??
		tfSTDCALL_PROC_p ASInit;
		/// Инициализация массива указателей ??
		tfSTDCALL_PROC_p APInit;
		/// Инициализация карты ??
		tfSTDCALL_PROC_p MNTInit;
		/// Инициализация карты ключь - указатель, значение - строка ??
		tfSTDCALL_PROC_p MPSInit;
		/// Инициализация карты ключь - строка, значение - указатель ??
		tfSTDCALL_PROC_p MSPInit;
		/// Инициализация карты ключь - указатель, значение - указатель ??
		tfSTDCALL_PROC_p MPInit;

		/// Установка значения строки.
		tfSTDCALL_PROC_p_p SSet;
		/// Добовление значения в конец строки.
		tfSTDCALL_PROC_p_p SAdd;
		/// Comparison with the sequence of lines of characters. Return 0 if equal, see CmpMem
		tfSTDCALL_int_FUNC_p_p SCompare;

		/// Установка значения длинной строки.
		tfSTDCALL_PROC_p_p LSSet;
		/// Добовление значения в конец длинной строки.
		tfSTDCALL_PROC_p_p LSAdd;
		/// Вставляет значения в длинную строку.
		tfSTDCALL_PROC_p_p_uint LSInsert;
		/// Вырезает значения из длинной строки.
		tfSTDCALL_PROC_p_uint_uint LSRemove;
		/// Сравнение длинной строки с последовательностью символов.
		tfSTDCALL_int_FUNC_p_p LSCompare;

		/// Вставить значение в конец массива
		tfSTDCALL_p_FUNC_p_p DPAddLast;
		/// Вставить значение в массив
		tfSTDCALL_p_FUNC_p_p_uint DPInsert;
		/// Убрать элемент с номером из массива
		tfSTDCALL_PROC_p_uint DPRemove;
		/// Убрать значение из массива
		tfSTDCALL_int_FUNC_p_p DPRemoveVal;
		///
		tfSTDCALL_PROC_p DPRemoveLast;
		/// 
		tfSTDCALL_PROC_p_uint DPSetCount;
		/// Освобождает массив
		tfSTDCALL_PROC_p DPFree;

		/// Вставить строку в конец массива
		tfSTDCALL_p_FUNC_p_p DSAddLast;
		/// Освобождает массив коротких строк
		tfSTDCALL_PROC_p DSFree;

		///
		tfSTDCALL_p_FUNC_p APLast;
		///
		tfSTDCALL_p_FUNC_p APClone;
		/// Добовление к массиву ключь - указатель (list,key)
		tfSTDCALL_p_FUNC_p_p APAdd;
		/// Поиск в массивe ключь - указатель (list,key)
		tfSTDCALL_int_FUNC_p_p APFind;
		/// Удаляет елемента из массива по ключу. (list,key)
		tfSTDCALL_int_FUNC_p_p APRemove;
		///
		tfSTDCALL_p_FUNC_p APEnd;
		/// Освобождает массив
		tfSTDCALL_PROC_p APFree;

		/// Добовление к карте ключь - указатель, значение - указатель (list,key,val)
		tfSTDCALL_p_FUNC_p_p_p MPAdd;
		/// Поиск ключа в карте ключь - указатель (list,key)
		tfSTDCALL_p_FUNC_p_p MPFind;
		/// Упрощенный поиск значения в карте - void* (list,val,def key)
		tfSTDCALL_p_FUNC_p_p_p MPFindByVal;
		/// Удаляет елемент из карты по ключу. (list,key)
		tfSTDCALL_p_FUNC_p_p MPRemove;
		///
		tfSTDCALL_p_FUNC_p MPEnd;
		/// Освобождает карту
		tfSTDCALL_PROC_p MPFree;

		/// Добовление к карте ключь - строка, значение - указатель (list,key,val)
		tfSTDCALL_p_FUNC_p_p_p MSPAdd;
		/// Упрощенное добовление к карте, с созданием новой строки, ключь - char*, значение - указатель (list,key,val)
		tfSTDCALL_p_FUNC_p_p_p MSSPAdd;
		/// Поиск ключа в карте ключь - строка (list,key)
		tfSTDCALL_p_FUNC_p_p MSPFind;
		/// Упрощенный поиск ключа в карте ключь - char* (list,key)
		tfSTDCALL_p_FUNC_p_p MSSPFind;
		/// Удаляет елемент из карты по ключу. (list,key) не удаляет строку.
		tfSTDCALL_p_FUNC_p_p MSPRemove;
		/// Упрощенное удаление елемента из карты по ключу - char* (list,key)
		tfSTDCALL_int_FUNC_p_p MSSPRemove;
		/// Удаляет строки и освобождает карту.
		tfSTDCALL_PROC_p MSSPFree;

		/// Добовление к константной карте ключь - указатель, значение - указатель (list,key,val,max)
		tfSTDCALL_p_FUNC_p_p_p_uint MCPAdd;
		/// Поиск ключа в константной карте ключь - указатель (list,key)
		tfSTDCALL_p_FUNC_p_p MCPFind;

		/// Добовление к константной карте ключь - строка, значение - указатель (list,key,val,max)
		tfSTDCALL_p_FUNC_p_p_p_uint MCSPAdd;
		/// Поиск ключа в константной карте ключь - строка (list,key)
		tfSTDCALL_p_FUNC_p_p MCSPFind;

		/// возврашает масив элементов
		tfSTDCALL_p_FUNC_p MPArray;
		/// возвращает количество элементов
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
	 * @brief sFunctionsExtensionCPU - дополнительные функции
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
		/// обмен памяти
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

		/// Возвращает логарифмический размер rez=pow(2,trunc(log2(val-1)+1))
		tfSTDCALL_int_FUNC_int ILogSize;

		/// Converts the sequence of characters in the number
		tfSTDCALL_int_FUNC_p STRToI;
		/// Преобразует последовательность символов в число с плавающей точкой
		tfSTDCALL_float_FUNC_p STRToF;
		/// Преобразует последовательность символов в число с плавающей точкой двойной точности
		tfSTDCALL_double_FUNC_p STRToD;

		tfSTDCALL_PROC_p_uint_int IToSTR;

		///
		//tfSTDCALL_p_FUNC_p_p STRTok;
		/// Поиск соответствия в строке val1 параметру val2 с лева на право, возвращает строку
		tfSTDCALL_p_FUNC_p_p STRLeftFind;
		/// Поиск соответствия в строке val1 параметру val2 с права на лево, возвращает строку
		tfSTDCALL_p_FUNC_p_p STRRightFind;

		/// Преобразует код клавиши в символ
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

		/// Анимация параметра в радианах (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_float_double FMotionRad;
		/// Анимация параметра в радианах (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_double_double DMotionRad;
		/// Анимация параметра в радианах (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_p_double V2FMotionRad;
		/// Анимация параметра в радианах (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_p_double V2DMotionRad;
		/// Анимация параметра в радианах (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_p_double V3FMotionRad;
		/// Анимация параметра в радианах (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_p_double V3DMotionRad;
		/// Анимация параметра в радианах (param, save, real, deltaTime)
		tfSTDCALL_bool_FUNC_p_p_p_double V4FMotionRad;
		/// Анимация параметра в радианах (param, save, real, deltaTime)
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

		/// Преобразование широты долготы и высоты в вектор
		tfSTDCALL_PROC_p_p BLHToV3F;
		/// Преобразование широты долготы и высоты в вектор двойной точночти
		tfSTDCALL_PROC_p_p BLHToV3D;
		/// Быстрое преобразование широты долготы и высоты в вектор
		tfSTDCALL_PROC_p_p BLHToV3FFAST;
		/// Быстрое преобразование широты долготы и высоты в вектор двойной точночти
		tfSTDCALL_PROC_p_p BLHToV3DFAST;
		/// Преобразование широты долготы в единичный вектор
		tfSTDCALL_PROC_float_float_p BLToV3F;
		/// Преобразование широты долготы в единичный вектор двойной точночти
		tfSTDCALL_PROC_double_double_p BLToV3D;
		/// Быстрое преобразование широты долготы в единичный вектор
		tfSTDCALL_PROC_float_float_p BLToV3FFAST;
		/// Быстрое преобразование широты долготы в единичный вектор двойной точночти
		tfSTDCALL_PROC_double_double_p BLToV3DFAST;
		/// Преобразование вектора в широту долготу и высоту (blh vec)
		tfSTDCALL_PROC_p_p V3FToBLH;
		/// Преобразование вектора в широту долготу и высоту двойной точночти (blh vec)
		tfSTDCALL_PROC_p_p V3DToBLH;
		/// Преобразование вектора в широту долготу (b l vec)
		tfSTDCALL_PROC_p_p_p V3FToBL;
		/// Преобразование вектора в широту долготу двойной точночти (b l vec)
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
	 * @brief sFunctionsRenderCPU - функции графических алгоритмов
	 *
	 * @see math, apiinterface
	 */

	struct sFunctionsRenderCPU {
		int version;

		/// вычисление среднего между пикселями (void *rez,void*data,byte width)
		tfSTDCALL_PROC_p_p_int V3BHalfTexel;
		/// вычисление среднего между пикселями (void *rez,void*data,byte width)
		tfSTDCALL_PROC_p_p_int V4BHalfTexel;
		/// интерполированное вычисление между пикселями (void *rez,void*data,byte width,x,y)
		tfSTDCALL_PROC_p_p_int_float_float V3BTexel;
		/// интерполированное вычисление между пикселями (void *rez,void*data,byte width,x,y)
		tfSTDCALL_PROC_p_p_int_float_float V4BTexel;

		/// Заливка последовательности пикселей одним цветом в формате RGBA 4 байт
		tfSTDCALL_PROC_p S4AFdraw;
		/// Заливка последовательности пикселей одним цветом в формате RGBA 4 байт, с тестом глубиты LESS
		tfSTDCALL_PROC_p S4AFDLdraw;
		/// Заливка последовательности пикселей интерполированным цветом в формате RGBA 4 байт
		tfSTDCALL_PROC_p S4AFSdraw;
		/// Заливка последовательности пикселей интерполированным цветом в формате RGBA 4 байт, с тестом глубиты LESS
		tfSTDCALL_PROC_p S4AFDLSdraw;

		/// Формирование точки
		tfSTDCALL_PROC_p_p_float P4AFDraw;
		/// Формирование точки и сглаживание краев
		tfSTDCALL_PROC_p_p_float P4AFDrawAA;
		/// Формирование точки и сглаживание краев BLEND ALPHA
		tfSTDCALL_PROC_p_p_float P4AFADrawAA;

		/// Формирование линии
		tfSTDCALL_PROC_p_p_float L4AFDraw;

		/// Отрисовка одноцветного треугольника
		tfSTDCALL_PROC_p_p T4AFDraw;
		/// Отрисовка одноцветного треугольника с учетом цветов каждой вершины
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
