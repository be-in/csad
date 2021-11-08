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
 * @page page2 ������������� �������� �����������
 *
 * ������ ��� ������������ ������ �������� ����������� ���������� ������������������� ��������������� ������ ������� ������������ ��� ����� ��������.
 * ����� ���� ������ ������ ����� ��������, ���� ������� ���������� ������������ � ����� CSAD �� ����� ������������� ���������� ��� ������ ���������� ��� ��� ������������� ����������� �������.
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
 * ����������:
 @verbatim

 - 2004 -
 ��������� ��������. (DEF FPU 3DNOW SSE)
 ��������� ���������. (DEF  FPU 3DNOW SSE)
 ��������������� ������� (��������� �� �����).
 ��������� ��������� �������� (Dot product).
 ��������� ��������� �������� (Cross product).
 ���������� ������� �������. (DEF FPU)
 ������������ ��������� ��������. (DEF FPU)
 ���������� �������� ������ �������. (DEF FPU 3DNOW)
 ��������� ���������. (DEF FPU)
 ��������� ������� �� �������. (DEF FPU SSE)
 ��������� ������� �� ����������������� �������. (DEF FPU SSE)
 ������ ���������� ������ ��������� ������ ���� X Y Z. (DEF FPU)

 - 2009 -
 ������ �������� �������� ��������� � ��������� � ����������.
 ������ ���������� ������������� ������� ��������-����.
 ������ ���������� ������� ��������-����.
 ���������� �������� ���������� ����� ���������.
 ������ �������� ������������ ��������.
 ������� ����������� �������� �������� ������. (MMX)

 - 2011 -
 ������ �������� ��������� �� ������� ��������� ����������� ����� ��� ����� � ��������� ������ ������ ��������. (DEF)
 ������ �������� �� ������� ���������� ��������. (DEF FPU SSE)
 ������ ��������������� ����� � ��������� ������ �� ������� ������ � �������������� �� � ����� ����� � ����������� ��� ���������� ������� �����. (DEF FPU)
 ������� �� ������ ���������� ������ �������� � �����������. (DEF)
 ��������� ������� �� ����������������� �������. (SSE4)
 ������ �������������� ��������. (DEF FPU SSE)
 ������ �������������� ��������� ��������� � ���������.  (DEF FPU)
 ������ �������� �� ������� �������������� ��������� ��������� � ���������.  (DEF FPU)
 ���������� �������� ������ �������. (SSE4)

 - 2012 -
 ���������� ������������� � ������������� ������ ��������.
 �������������� ������ ��������.
 ���������� �������� �������.
 ��������� ������������.
 ���������� ��������� �����������.
 ��������� ������� �� ����������.
 ������������ �����������.
 ���������� ����������� �� ������ � ���� �������� ������ ���� � �������. (DEF SSE)

 - 2013 -
 ������ ���������� �������� �������� �� ��������� ������ � ������ ���������� (DEF FPU SSE3 SSE4).
 ������ ���������� �������� ���������� �� ����� �� ������� (DEF FPU SSE3).
 ������ ���������� ���� ����� ��������� (DEF FPU SSE).
 ������ ���������� ����������� ������� (DEF FPU SSE).
 ������ ���������� ������� ��������� (DEF FPU SSE).
 ��������� ������� �� ������� ��������������� � ������������ ������� ��������������. (DEF SSE3 SSE4)
 ��������� ������� �� ������� �������� � ������������ ������� ��������. (DEF SSE3)
 ��������� ������� �� ����������. (DEF SSE3)
 �������������� ����������� � ������� � �������. (DEF)

 - 2014 -
 
 @endverbatim
 *
 * �������� ����� ����������:
 @verbatim
   B - 8� ������ ����� ����� (������� ��������).
   S - 16� ������ ����� ����� (������� ��������).
   I - 32� ������ ����� ����� (������� ��������).
   L - 64� ������ ����� ����� (������� ��������).
   F - 32� ������ ����� � ��������� ������.
   D - 64� ������ ����� � ��������� ������.
   Vx - ������ ����������� �.
   A - ������ ������.
   Q - 4 �������� ������������ ������ � ���� �������� �� ���� ����.
   Mx - ������� ����������� �.
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
