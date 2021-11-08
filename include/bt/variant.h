/*
 * variant.h
 *
 *  Created on: 19.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef VARIANT_H_
#define VARIANT_H_

#include <bt/btapi.h>
#include <bt/array.h>
#include <bt/math/math.h>

OPTIMIZE_ON;

extern "C" {

	extern bt::sBaseTypesData BT_API t_data_base;

/// @ingroup bt
/// Индентификатор типа функции
	_FORCEINLINE void * typeFunction() { return t_data_base.Function; }
/// @ingroup bt
/// Индентификатор типа указатель
	_FORCEINLINE void * typePVoid() { return t_data_base.PVoid; }
/// @ingroup bt
/// Индентификатор типа bool
	_FORCEINLINE void * typeBool() { return t_data_base.Bool; }
/// @ingroup bt
/// Индентификатор типа char*
	_FORCEINLINE void * typePChar() { return t_data_base.PChar; }
/// @ingroup bt
/// Индентификатор типа _int32
	_FORCEINLINE void * typeInt() { return t_data_base.Int; }
/// Индентификатор типа _int64
	_FORCEINLINE void * typeLong() { return t_data_base.Long; }
/// @ingroup bt
/// Индентификатор типа float
	_FORCEINLINE void * typeFloat() { return t_data_base.Float; }
/// @ingroup bt
/// Индентификатор типа double
	_FORCEINLINE void * typeDouble() { return t_data_base.Double; }

}

namespace bt {

/**
 * @class Variant
 *
 * @ingroup bt
 * @brief Variant - variational data type enables you to store, transmit and convert different types.
 *
 * Example:
 @verbatim
   Variant a;
   a.setString("123.5");
   float b=a.getFloat();
 @endverbatim
 *
 * @see bt
 */

class Variant {
public:
	MEMDEFAULT(Variant)

	BT_API Variant();
	BT_API Variant(void *data);
	BT_API ~Variant();

	/// set the pointer
	BT_API void setVoid(void * val);
	/// to specify a Boolean value
	BT_API void setBool(bool val);
	/// to specify integer signed a number of
	BT_API void setInt(_int32 val);
	/// to specify integer signed a number of
	BT_API void setLong(_int64 val);
	/// задать строковое значение
	BT_API void setString(char * val);
	/// задать строковое значение
	BT_API void setString(const char* val);
	/// to specify a floating-point value
	BT_API void setFloat(float val);
	/// задать значение с плавающей точкой
	BT_API void setDouble(double val);
	/// to specify integer signed a two-dimensional vector
	BT_API void setVector2i(vector2i *v);
	/// to set a two-dimensional vector floating point single-precision
	BT_API void setVector2f(vector2f *v);
	/// to set a two-dimensional vector floating point double precision
	BT_API void setVector2d(vector2d *v);
	/// to specify integer signed a three-dimensional vector
	BT_API void setVector3i(vector3i *v);
	/// to set a three-dimensional vector floating point single-precision
	BT_API void setVector3f(vector3f *v);
	/// to set a three-dimensional vector floating point double precision
	BT_API void setVector3d(vector3d *v);
	/// to specify integer signed a four-dimensional vector
	BT_API void setVector4i(vector4i *v);
	/// to set a four-dimensional vector floating point single-precision
	BT_API void setVector4f(vector4f *v);
	/// to set a four-dimensional vector floating-point double precision
	BT_API void setVector4d(vector4d *v);
	/// to read the data as Boolean
	BT_API bool getBool(bool def = false);
	/// to read the data as an integer signed number
	BT_API _int32 getInt(_int32 def = 0);
	// to read the data as an integer signed number
	//BT_API _int64 getLong(int def=0);
	/// to read the data as a string value
	BT_API char* getString();
	/// to read the data as a string value
	BT_API const char * getString(const char* def);
	/// прочитать данные как значение одинарной точности
	BT_API float getFloat(float def = 0);
	/// прочитать данные как значение двойной точности
	BT_API double getDouble(double def = 0);
	/// прочитать данные как указатель
	BT_API void *getPointer();
	/// прочитать данные как целочисленный знаковый двухмерный вектор
	BT_API vector2i &getVector2i();
	/// прочитать данные как двухмерный вектор с плавающей точкой одинарной точности
	BT_API vector2f &getVector2f();
	/// прочитать данные как двухмерный вектор с плавающей точкой двойной точности
	BT_API vector2d &getVector2d();
	/// прочитать данные как целочисленный знаковый трехмерный вектор
	BT_API vector3i &getVector3i();
	/// прочитать данные как трехмерный вектор с плавающей точкой одинарной точности
	BT_API vector3f &getVector3f();
	/// прочитать данные как трехмерный вектор с плавающей точкой двойной точности
	BT_API vector3d &getVector3d();
	/// прочитать данные как целочисленный знаковый четырехмерный вектор
	BT_API vector4i &getVector4i();
	/// прочитать данные как четырехмерный вектор с плавающей точкой одинарной точности
	BT_API vector4f &getVector4f();
	/// прочитать данные как четырехмерный вектор с плавающей точкой двойной точности
	BT_API vector4d &getVector4d();

	BT_API bool setType(void*);
	/// Возвращает идентификатор типа данных
	_FORCEINLINE void* getType() { return *(void**)p_data; }

	_FORCEINLINE void* getData() { return (void*)(((void**)p_data) + 1); }

	BT_API unsigned int size();

/*	_FORCEINLINE Variant &operator=(const Variant &b) {
		p_data=(char*)b._copyData();
		return *this;
	}

	_FORCEINLINE Variant &operator=(Variant &b) {
		p_data=b.p_data;
		b.p_data=0;
		return *this;
	}

	_FORCEINLINE Variant &operator=(const int b) {
		setInt(b);
		return *this;
	}

	_FORCEINLINE Variant &operator=(const float b) {
		setFloat(b);
		return *this;
	}

	_FORCEINLINE Variant &operator=(const bool b) {
		setBool(b);
		return *this;
	}*/

	BT_API void clean();

//	_FORCEINLINE Variant operator=()

private:
	char *p_data;

	void *_getNew(void *type);
	char *_copyData() const ;

	BT_API static void _init();
};

}

OPTIMIZE_OFF;

#endif /* VARIANT_H_ */
