/*
 * parameterslist.h
 *
 *  Created on: 11.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef PARAMETERSLLIST_H_
#define PARAMETERSLLIST_H_

#include <bt/array.h>
#include <bt/variant.h>

namespace bt {

OPTIMIZE_ON;

/**
 * @class ParametersList
 *
 * @brief ParametersList - a named parameter list.
 *
 * @see bt
 */

class ParametersList {
public:
	_FORCEINLINE ParametersList():mData(0) {}
	_FORCEINLINE ParametersList(int) {}
	_FORCEINLINE ~ParametersList() { clear(); }

	class iterator {
	public:
		_FORCEINLINE iterator(void *it) { mIterator=(void**)it; }
		_FORCEINLINE ~iterator() {}

		/// returns the name of the parameter
		_FORCEINLINE const char * key() { return ((const char*)*mIterator)+1; }
		/// returns the value of the parameter
		_FORCEINLINE Variant &value() {return (*(Variant*)(mIterator+1)); }

		_FORCEINLINE iterator& operator++(int) { mIterator+=2; return *this;}
		_FORCEINLINE bool operator==(const iterator& _Right) {return mIterator==_Right.mIterator;}
		_FORCEINLINE bool operator!=(const iterator& _Right) {return mIterator!=_Right.mIterator;}

	private:
		void **mIterator;
	};

	/// returns the parameter value by its name
	_FORCEINLINE Variant* find(const char* key) { void**val=(void**)arrFunctions.MSSPFind(&mData,(void*)key); return (Variant*)val; }
	/// checks for the existence of a parameter
	_FORCEINLINE bool contains(const char* key) { void**val=(void**)arrFunctions.MSSPFind(&mData,(void*)key); return val!=0; }

	/// the first element of the list of parameters
	_FORCEINLINE iterator begin() { return iterator(arrFunctions.MPArray(&mData)); }
	/// the final element of the list of parameters
	_FORCEINLINE iterator end() { return iterator(arrFunctions.MPEnd(&mData)); }
	/// remove all values.
	BT_API void clear();

	/// calculate full size data.
	BT_API unsigned int dataSize();
	/// write data to memory.
	BT_API void writeToData(void* data);
	/// read data from memory.
	BT_API void readFromData(void* data);

	///
	_FORCEINLINE Variant &operator[](char* name) { return *(Variant*)(((void**)arrFunctions.MSSPAdd(&mData, (void*)name, 0)) + 1); }
	_FORCEINLINE Variant &operator[](const char* name) { return *(Variant*)(((void**)arrFunctions.MSSPAdd(&mData, (void*)name, 0)) + 1); }

private:
	void *mData;
};

OPTIMIZE_OFF;

}

#endif /* PARAMETERSLLIST_H_ */
