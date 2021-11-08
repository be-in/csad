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
 * @brief FormatJPG - файл двухмерного изображения.
 *
 * @see format
 */

class FormatJPG {
public:
	CSAD_API FormatJPG();
	CSAD_API ~FormatJPG();

	/// Загружает и декодирует файл.
	CSAD_API bool readFromFile(char *name);
	/// Загружает и декодирует файл.
	_FORCEINLINE bool readFromFile(const char *name) { return readFromFile((char*)name); }
	/// Загружает и декодирует файл.
	CSAD_API bool readFromFile(File *file);
	
	CSAD_API bool writeToFile(char *name,int qual);
	_FORCEINLINE bool writeToFile(const char *name,int qual) { return writeToFile((char*)name,qual); }
	CSAD_API bool writeToFile(File *file,int qual);

	/// ширина цветовой матирци.
	_FORCEINLINE int width() {return fWidth;}
	/// высота цветовой матирци.
	_FORCEINLINE int height() {return fHeight;}

	/// возвращает количество байт на пиксей
	_FORCEINLINE int bpp() {return fBPP;}
	/// задает цветовую матрицу для текущего формата
	_FORCEINLINE void setMatrix(void *data) {p_JPGImg=data;}
	/// задает цветовую матрицу и ее формат
	CSAD_API void setMatrix(int height,int width,int bpp,void *data);
	/// возвращает указатель на двухмерную цветовую матрицу
	_FORCEINLINE void *imgMatrix() {return p_JPGImg;}

	/// очистка от всех данных
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
