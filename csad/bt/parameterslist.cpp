/*
 * parameterslist.cpp
 *
 *  Created on: 11.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <bt/parameterslist.h>

namespace bt {

WARNING_DISABLE;
OPTIMIZE_ON;

typedef MapName<void> MapParametersList;

/*class MapParametersIterator:public MapParametersList::iterator {
public:
	_FORCEINLINE MapParametersIterator(void *ptr,void *data) {
		*(void**)&_Ptr=ptr;
#if defined (OS_WIN)
		_Adopt((MapParametersList*)data);
#endif
	}
	_FORCEINLINE ~MapParametersIterator() {}

	_FORCEINLINE value_type &val() {return _Ptr->_Myval;}

	_FORCEINLINE void setPtr( void *ptr) {*(void**)&_Ptr=ptr;}

	_FORCEINLINE void setData(void *ptr) {
#if defined (OS_QNX)
#elif defined (OS_WIN)
		_Adopt((MapParametersList*)ptr);
#endif
	}
};*/

/*ParametersList::ParametersList()
{
	mData=0;
}

ParametersList::~ParametersList()
{
	clear();
}

Variant* ParametersList::find(const char*key)
{
	void**val=(void**)arrFunctions.MSSPFind(&mData,(void*)key);
	return (Variant*)val;
}*/

/*bool ParametersList::contains(const char*key)
{
	void**val=(void**)arrFunctions.MSSPFind(&mData,(void*)key);
	return val!=0;
}*/

/*ParametersList::iterator ParametersList::begin()
{
	//void **data=&mData;
	return ParametersList::iterator(arrFunctions.MPArray(&mData), mData);
}

ParametersList::iterator ParametersList::end()
{
	void **data=&mData;
	return ParametersList::iterator(&(((void**)arrFunctions.MPArray(&mData))[arrFunctions.MPCount(data) << 1]), mData);
}*/

void ParametersList::clear()
{
	if (!mData) {
		void**arr = (void**)arrFunctions.MPArray(&mData);
		unsigned int count=arrFunctions.MPCount(&mData);
		while (count>0) {
			arr++;
			if (*arr) ((Variant*)(arr))->clean();
			arr++;
			count--;
		}
	}
	arrFunctions.MSSPFree(&mData);
}

unsigned int ParametersList::dataSize()
{
	void**arr = (void**)arrFunctions.MPArray(&mData);
	unsigned _int32 count=arrFunctions.MPCount(&mData);
	unsigned int fullsize=sizeof(_int32);
	while (count>0) {
		unsigned char* str=*(unsigned char**)arr;
		fullsize+=(str[0]+1);
		arr++;
		Variant* p=(Variant*)(arr);
		fullsize+=p->size();
		arr++;
		count--;
	}
	return 0;
}

void ParametersList::writeToData(void* data)
{
}

void ParametersList::readFromData(void* data)
{
}

/*Variant &ParametersList::operator[](char*name)
{
	return *(Variant*)(((void**)arrFunctions.MSSPAdd(&mData, name, 0)) + 1);
}

Variant &ParametersList::operator[](const char*name)
{
	return *(Variant*)(((void**)arrFunctions.MSSPAdd(&mData, (char*)name, 0)) + 1);
}*/

OPTIMIZE_OFF;
WARNING_ENABLE;

}
