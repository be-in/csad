/*
 * file.h
 *
 *  Created on: 19.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef FILE_H_
#define FILE_H_

#include <core/baseobject.h>
#include <platform/platformapi.h>
#include <bt.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

/**
 * @class File
 *
 * @ingroup platform
 * @brief File - A file object.
 * @see BaseFile, platform
 *
 * @fn int File(char *name, IOType io=READ);
 * @brief Конструктор файла
 * @param name - имя файла.
 * @param io - режим работы с файлом.
 *
 * @fn bool File::open();
 * @brief Открывает файл
 *
 * @fn bool File::close();
 * @brief Закрывает файл
 *
 * @fn int File::read(void*data,int count);
 * @brief Read byte sequence using cache buffer
 * @param data - buffer to load the data.
 * @param count - the size of the buffer in bytes.
 * @return the number of bytes read.
 *
 * @fn int File::write(void*data,int count);
 * @brief The entry sequence of bytes using cache buffer
 * @param data - buffer data being written.
 * @param count - the size of the buffer in bytes.
 * @return the number of bytes written.
 *
 * @fn void File::setPos(long long pos,PosFrom from);
 * @brief To set the file position
 * @param pos - the offset in bytes.
 * @param from - defines the form of displacement.
  *
 * @fn int File::size();
 * @brief The total file size
 * @return the total file size
 */

using namespace bt;

#define FILE_SIZE_BUFF 1024

class File {
public:
	MEMDEFAULT(File)

	enum IOType {
		///  открыть файл для чтения
		READ,
		///  открыть файл для записи
		WRITE,
		/// открыть файл для записи и чтения
		READWRITE,
		/// cоздать файл для записи
		CREATE,
		/// cоздать файл для записи и чтения
		CREATERW
	};

	enum PosFrom {
		/// since the beginning of the file
		BEGIN,
		/// from the current position
		CURRENT,
		/// with the end of the file
		END,
	};

	/// Конструктор
	PLATFORM_API File(IOType io);
	/// Конструктор
	PLATFORM_API File(char *name, IOType io=READ);
	PLATFORM_API File(const char *name="", IOType io=READ);
	PLATFORM_API virtual ~File();

	/// opens or creates a new file
	PLATFORM_API bool open();
	/// closes the file
	PLATFORM_API bool close();

	/// sets the name of the file
	PLATFORM_API void setFileName(char *);
	_FORCEINLINE void setFileName(const char * name) { setFileName((char*)name); }
	PLATFORM_API const char *getFileName();

	/// read block of data from a file
	PLATFORM_API int read(void*data,int count);
	/// создает буфер разбером в файл и читает из него все содержимое
	PLATFORM_API char* readAll();
	/// writes a block of data to a file
	PLATFORM_API int write(void*data,int count);

	/// setting the position in the file
	PLATFORM_API void setPos(_int64 pos,int from);
	PLATFORM_API _int64 getPos();

	/// Общий размер файла
	/// @return общий размер файла.
	PLATFORM_API int size();

    /// Returns indicator file depends on your operating system
    /// @return the file ID.
	_FORCEINLINE void* getHeader() {return p_header;}

	PLATFORM_API static bool check(const char *name);
	PLATFORM_API static bt::ShortStringList getFileList(char *path,char *name,_int32 mode);

	PLATFORM_API TYPEINFO_H

private:
	IOType p_io;
	ShortString p_filename;
	void* p_header;
	int p_size_use;
	int p_pos;
	bool p_clear;
	char *p_buff;
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* FILE_H_ */
