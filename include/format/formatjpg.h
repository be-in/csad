/*
 * formatjpg.h
 *
 *  Created on: 10.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#if defined(CSAD_JPEG) || defined(JPEG_CSAD) || !defined(CSAD_LOCAL)

#ifndef FORMATJPG_H_
#define FORMATJPG_H_

#include <core/baseobject.h>

OPTIMIZE_ON;

namespace csad {

class File;

/**
 * @class FormatJPG
 *
 * @ingroup format
 * @brief FormatJPG - ���� ����������� �����������.
 *
 * @see format
 */

class FormatJPG {
public:
	CSAD_API FormatJPG();
	CSAD_API ~FormatJPG();

	/// ��������� � ���������� ����.
	CSAD_API bool readFromFile(char *name);
	/// ��������� � ���������� ����.
	_FORCEINLINE bool readFromFile(const char *name) { return readFromFile((char*)name); }
	/// ��������� � ���������� ����.
	CSAD_API bool readFromFile(File *file);
	
	CSAD_API bool writeToFile(char *name,int qual);
	_FORCEINLINE bool writeToFile(const char *name,int qual) { return writeToFile((char*)name,qual); }
	CSAD_API bool writeToFile(File *file,int qual);

	/// ������ �������� �������.
	_FORCEINLINE int width() {return fWidth;}
	/// ������ �������� �������.
	_FORCEINLINE int height() {return fHeight;}

	/// ���������� ���������� ���� �� ������
	_FORCEINLINE int bpp() {return fBPP;}
	/// ������ �������� ������� ��� �������� �������
	_FORCEINLINE void setMatrix(void *data) {p_JPGImg=data;}
	/// ������ �������� ������� � �� ������
	CSAD_API void setMatrix(int height,int width,int bpp,void *data);
	/// ���������� ��������� �� ���������� �������� �������
	_FORCEINLINE void *imgMatrix() {return p_JPGImg;}

	/// ������� �� ���� ������
	CSAD_API void clear();
private:
	int fWidth;
	int fHeight;
	int fBPP;
	void *p_JPGImg;
};

}

OPTIMIZE_OFF;

#endif

#endif
