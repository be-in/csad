/*
 * formattga.h
 *
 *  Created on: 10.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#if defined(CSAD_TGA) || defined(TGA_CSAD) || !defined(CSAD_LOCAL)
#ifndef FORMATTGA_H_
#define FORMATTGA_H_

#include <core/baseobject.h>
#include <core/csadapi.h>

OPTIMIZE_ON;

namespace csad {

class File;

/**
 * @class FormatTGA
 *
 * @ingroup format
 * @brief FormatTGA - ���� ����������� �����������.
 *
 * @see format
 */

class FormatTGA {
public:
	CSAD_API FormatTGA();
	CSAD_API ~FormatTGA();

	/// ��������� � ���������� ����.
	CSAD_API bool readFromFile(char *name);
	/// ��������� � ���������� ����.
	_FORCEINLINE bool readFromFile(const char *name) { return readFromFile((char*)name); }
	/// ��������� � ���������� ����.
	CSAD_API bool readFromFile(File *file);

	// ������ �������� �������.
	_FORCEINLINE int width() {return p_TGA.Width;}
	/// ������ �������� �������.
	_FORCEINLINE int height() {return p_TGA.Height;}

	/// ���������� ���������� ���� �� ������
	_FORCEINLINE int bpp() {return p_BytePP;}
	/// ������ �������� ������� ��� �������� �������
	_FORCEINLINE void setMatrix(void *data) {p_TGAImg=data;}
	/// ���������� ��������� �� ���������� �������� �������
	_FORCEINLINE void *imgMatrix() {return p_TGAImg;}

	CSAD_API void clear();
private:

	struct TTGAHand {
		char dLeight;
		char ColorMap;
		char DataType;
		char ColorMapInfo[4];
		short X_Origin;
		short Y_Origin;
		short Width;
		short Height;
		char BPP;
		char Description;
	};

	TTGAHand p_TGA;
	void *p_TGAImg;
	int p_ImgSize;
	int p_ImgPixels;
	int p_BytePP;

	bool _create();
};

}

OPTIMIZE_OFF;

#endif /* FORMAT_H_ */
#endif