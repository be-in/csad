/*
 * @file bt.h
 *
 *  Created on: 04.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#pragma once

#ifndef BT_H_
#define BT_H_

/**
 * @page page2 Использование базового функционала
 *
 * Прежде чем использовать методы базового функционала необходимо проинициализировать соответствующюю группу функций определенной для этого функцией.
 * После чего методы группы будут доступны, если базовые инструкции используются в среде CSAD то такая инициализация выполнится при старте приложения или при использовании специфичных классов.
 *
 * Console example for Microsoft Visual Studio:
 @verbatim
   #include <bt.h>

   int main(HINSTANCE hInst, HINSTANCE, LPSTR lpCmdLine, INT)
   {
      initFunc();
      printf("log 2 : %f\n",flog2(100.14f));
      return 0;
   }
 @endverbatim
 *
 * Console example for linux gnu c++ compiler:
 @verbatim
   #include <bt.h>

   int main(int argc, char *argv[]) {
      initFunc();
      printf("log 2 : %f\n",flog2(100.14f));
      return EXIT_SUCCESS;
   }
 @endverbatim
 *
 * @see apiinterface
 */

#ifdef __cplusplus

#include <bt/os.h>
#include <bt/math/math.h>
#include <bt/consts.h>
#include <bt/typesproc.h>
#include <bt/types.h>
#include <bt/array.h>
#include <bt/memmanager.h>
#include <bt/string.h>
#include <bt/variant.h>
#include <bt/parameterslist.h>

#endif

#include <bt/functions.h>

/**
 * @namespace bt
 *
 * @brief Base Tools
 *
 * This is a set of low-level instructions form the basis of software package , they include geometric mathematical functions , functions for handling arrays of data blocks and any other algorithmic framework.
 * The main objective of the basic functionality to provide a set of commonly used algorithms described optimally for your processor architecture , no matter what it means assembling and compiling the application.
 * Group instruction also contains basic mathematical and algorithmic features that do not perform computationally intensive.
 * As the use of methods with minimal functionality makes efficient performance for the most efficient use of the basic functionality you need to know the volume of the tasks assigned to a separate function.
 *
 * Хронология:
 @verbatim

 - 2004 -
 Векторное сложение. (DEF FPU 3DNOW SSE)
 Векторное вычитание. (DEF  FPU 3DNOW SSE)
 Масштабирование вектора (умножение на число).
 Скалярное умножение векторов (Dot product).
 Векторное умножение векторов (Cross product).
 Вычисление нормали вектора. (DEF FPU)
 Поэлементное умножение векторов. (DEF FPU)
 Вычисление квадрата длинны вектора. (DEF FPU 3DNOW)
 Матричное умножение. (DEF FPU)
 Умножение вектора на матрицу. (DEF FPU SSE)
 Умножение вектора на транспонированную матрицу. (DEF FPU SSE)
 Методы вычисление матриц разворота вокруг осей X Y Z. (DEF FPU)

 - 2009 -
 Методы анимации значения параметра с задержкой и ускорением.
 Методы вычисления коэффициентов сплайна Катмулла-Рома.
 Методы вычисления сплайна Катмулла-Рома.
 Вычисление квадрата расстояния между векторами.
 Методы линейной интерполяции векторов.
 Быстрое копирование коротких отрезков памяти. (MMX)

 - 2011 -
 Методы быстрого получения не точного обратного квадратного корня для чисел с плавающей точкой разной точности. (DEF)
 Методы быстрого не точного вычисления нормалей. (DEF FPU SSE)
 Методы масштабирования чисел с плавающей точкой по степени двойки и преобразование их в целые числа с округлением или отсечением дробной части. (DEF FPU)
 Быстрое не точное вычисление синуса косинуса и арктангенса. (DEF)
 Умножение вектора на транспонированную матрицу. (SSE4)
 Методы Комбинирования векторов. (DEF FPU SSE)
 Методы преобразования градусных координат в векторные.  (DEF FPU)
 Методы быстрого не точного преобразования градусных координат в векторные.  (DEF FPU)
 Вычисление квадрата длинны вектора. (SSE4)

 - 2012 -
 Вычисление ортогональной и перспективной матриц проекций.
 Инвертирование знаков векторов.
 Абсолютное значение вектора.
 Умножение кватернионов.
 Вычисление обратного кватерниона.
 Умножение вектора на кватернион.
 Нормализация кватерниона.
 Разложение кватерниона на вектор и угол поворота вокруг него и обратно. (DEF SSE)

 - 2013 -
 Методы вычисление проекции векторов на плоскость экрана и анализ результата (DEF FPU SSE3 SSE4).
 Методы Вычисления квадрата расстояния от точки до отрезка (DEF FPU SSE3).
 Методы Вычисления угла между векторами (DEF FPU SSE).
 Методы Вычисления зеркального вектора (DEF FPU SSE).
 Методы Вычисления нормали плоскости (DEF FPU SSE).
 Умножение матрицы на матрицу масштабирования и формирование матрици маштабирования. (DEF SSE3 SSE4)
 Умножение матрицы на матрицу переноса и формирование матрици переноса. (DEF SSE3)
 Умножение матрицы на кватернион. (DEF SSE3)
 Преобразование кватерниона в матрицу и обратно. (DEF)

 - 2014 -
 
 @endverbatim
 *
 * Принятые формы сокращения:
 @verbatim
   B - 8и битное целое число (условно знаковое).
   S - 16и битное целое число (условно знаковое).
   I - 32х битное целое число (условно знаковое).
   L - 64х битное целое число (условно знаковое).
   F - 32х битное число с плавающей точкой.
   D - 64х битное число с плавающей точкой.
   Vx - вектор размерности х.
   A - массив данных.
   Q - 4 значения обозначающие вектор и угол поворота во круг него.
   Mx - матрица размерности х.
 @endverbatim
 *
 * @see apiinterface, math, array
 */

#ifdef __cplusplus
namespace bt {
#endif

/**
 * @defgroup apiinterface bt: api interface
 * @brief base interface of api functions.
 *
 * The basis of complex software is the base interface provides access to functionality at a low level for different programming languages.
 * The interface consists of a set of individual blocks of pointers, grouped by purpose functions described corresponding structure.
 * Each group can be filled with a set of matching functions corresponding to the execution environment, both by means of an initialization method and external programs.
 *
 * @ref page2
 * @see bt
 */

/**
 * @defgroup math bt: math
 * @brief mathematical operations and classes.
 *
 * @see bt
 */

/**
 * @defgroup array bt: array
 * @brief operations and classes for handling arrays.
 *
 * @see bt
 */

#ifdef __cplusplus
}
#endif

#endif /* BT_H_ */
