/*
 * basearray.h
 *
 *  Created on: 29.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef BASEARRAY_H_
#define BASEARRAY_H_

#include <bt/os.h>
#include <bt/btapi.h>
#include <bt/typesproc.h>

namespace bt {

WARNING_DISABLE;
OPTIMIZE_ON;

/*class BT_API BaseVectorArray
{
public:
	BaseVectorArray(unsigned int size);
	~BaseVectorArray();

	unsigned int mCount;
	unsigned int mAllCount;
	unsigned int mItSize;
	tfFASTCALL_int_FUNC_int mThs;
	char *mVals;

	void _free();
	void _clear();
	void _resize(unsigned int count);
	void _reserv(unsigned int count);
	void _realloc(unsigned int count);
	void _lowalloc(unsigned int count);
	void _assign(void *val);
	void _del_last();
	void * _point(unsigned int id) const;
	void * _last();
};*/

/*class BT_API BaseVoidVector
{
public:
	BaseVoidVector();
	~BaseVoidVector();

	unsigned int mCount;
	unsigned int mAllCount;
	void **mVals;

	void _free();
	void _clear();
	void _resize(unsigned int count);
	void _reserv(unsigned int count);
	void _realloc(unsigned int count);
	void _lowalloc(unsigned int count);
	void _assign(void *val);
	void _del_last();
	void * _point(unsigned int id) const;
	void * _last();
};*/

class BT_API BaseHashVector
{
public:
	//MEMDEFAULT(BaseHashVector)

	BaseHashVector(unsigned int size);
	~BaseHashVector();

	unsigned int mCount;
	unsigned int mAllCount;
	unsigned int mItSize;
	tfFASTCALL_int_FUNC_int mThs;
	unsigned int mHashLevel;
	unsigned int *mHashedC;
	char *mVals;

	void _assign(void *val);
	int _find(void *val);
	int _del(void *val);
	void * _point(unsigned int id) const;
	bool _removeAt(unsigned int id);

	void _clear();
	void _realloc(unsigned int count);
	unsigned char _hash(void *_val);
	void _addHash(void * _val);
	void _delHash(void *_val);
	void _swap(int _aid,int _bid);
	void _setHashLevel(unsigned int _level);
	void _moveToNew(BaseHashVector*);
};

class BT_API BaseHashMap {
public:
	//MEMDEFAULT(BaseHashMap)

	BaseHashMap(unsigned int size,unsigned int vsize);
	~BaseHashMap();

	unsigned int mCount;
	unsigned int mAllCount;
	unsigned int mItSize;
	unsigned int mKeySize;
	tfFASTCALL_int_FUNC_int mThs;
	unsigned int mHashLevel;
	unsigned int *mHashedC;
	char *mVals;

	void _assign(void *key,void *val);
	int _find(void *key);
	int _del(void *key);
	void * _point(unsigned int id) const;
	void * _val(unsigned int id) const;
	bool _removeAt(unsigned int id);

	void _clear();
	void _realloc(unsigned int count);
	unsigned char _hash(void *_key);
	void _addHash(void * _key,void *_val);
	void _delHash(void *_key);
	void _swap(int _aid,int _bid);
	void _setHashLevel(unsigned int _level);
	void _moveToNew(BaseHashMap*);
};

class BT_API BaseHashVoidMap {
public:
	//MEMDEFAULT(BaseHashVoidMap)

	BaseHashVoidMap();
	~BaseHashVoidMap();

	class BT_API iterator {
	public:
		iterator(void*val);
		~iterator();

		void* key();
		void* value();
		iterator& operator++(int);
		bool operator ==(const iterator& _Right);
		bool operator !=(const iterator& _Right);

	private:
		void* mIterator;
	};

	iterator begin();
	iterator end();

	unsigned int mCount;
	unsigned int mAllCount;
	unsigned int mHashLevel;
	unsigned int *mHashedC;
	char *mVals;

	void _assign(void *key,void *val);
	int _find(void *key);
	int _del(void *key);
	void * _point(unsigned int id) const;
	void * _val(unsigned int id) const;
	bool _removeAt(unsigned int id);

	void _clear();
	void _realloc(unsigned int count);
	unsigned char _hash(void *_key);
	void _addHash(void * _key,void *_val);
	void _delHash(void *_key);
	void _swap(int _aid,int _bid);
	void _setHashLevel(unsigned int _level);
	void _moveToNew(BaseHashVoidMap*);
};

/*class BT_API BaseMapName {
public:
	BaseMapName();
	~BaseMapName();

	class BT_API iterator {
	public:
		iterator(void*val,void *v);
		iterator(const iterator &it);
		iterator(iterator &it);
		~iterator();

		const char* key();
		void* value();
		iterator& operator++(int);
		bool operator ==(const iterator& _Right);
		bool operator !=(const iterator& _Right);

	private:
		void* mIterator;
		void *d;
	};

	iterator begin();
	iterator end();

	//void clear();
	//void free();

	//unsigned int count();
	//unsigned int count(char*);
	//unsigned int count(const char* &);

	//bool contains(char*);
	//bool contains(const char* &);

	int remove(char*);
	int remove(const char* &);

	void* mData;

	//void *_find(char *);
	//void *_find(const char * &);
	//void *_find(char* ,void * );
	//void *_find(const char* &,void * );
	//const char *_key(void *_val,const char * &_key);
	//void *&_findornew(char *);
	//void *&_findornew(const char * &);
	//void* _assign(void*,char *);
	//void* _assign(void*,const char * &);
};*/

/*class BT_API BaseMapVoid {
public:
	BaseMapVoid();
	~BaseMapVoid();

	class BT_API iterator {
	public:
		iterator(void*val,void*v);
		iterator(const iterator &it);
		iterator(iterator &it);
		~iterator();

		void* key();
		void* value();
		iterator& operator++(int);
		bool operator ==(const iterator& _Right);
		bool operator !=(const iterator& _Right);

	private:
		void* mIterator;
		void* d;
	};

	iterator begin();
	iterator end();

	void clear();

	unsigned int count();
	unsigned int count(void*);

	bool contains(void*);

	void* remove(void*);

	void* mData;

	void *_find(void *);
	void *_key(void *_val,void * &_key);
	void *&_findornew(void *);
	void* _assign(void*,void *);
};*/

// нельзя использовать как возвращаемый параметр

/*class BT_API BaseShortString {
public:
	BaseShortString();
	BaseShortString(const char *ch);
	~BaseShortString();

	char *mData;

	const char *str();

	char length();

	int compare(char*);

	BaseShortString &operator=(char);
	BaseShortString &operator=(const char*);
	BaseShortString &operator=(BaseShortString&);

	BaseShortString &operator+=(char);
	BaseShortString &operator+=(const char*);

	bool operator==(BaseShortString & _r);
	char operator[](int id) {return ((char*)mData)[id+1];}
	bool operator>(BaseShortString & _r);

	int _size(unsigned char size);
	void *_new(unsigned char size);
	void _del(void*mem,unsigned int size);
};*/

// нельзя использовать как возвращаемый параметр

/*class BT_API BaseString {
public:
	BaseString();
	BaseString(const char *ch);
	~BaseString();

	char *mData;

	unsigned int length();
	void insert(unsigned int,char);
	void remove(unsigned int);

	const char *str();

	int compare(char*);

	BaseString &operator=(char);
	BaseString &operator=(const char*);

	BaseString &operator+=(char);
	BaseString &operator+=(const char*);
	char operator[](int id) {return ((char*)mData)[id+4];}
	bool operator==(BaseString & _r);

	int _size(unsigned int size);
	void *_new(unsigned int size);
	void _del(void*mem,unsigned int size);
};*/

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* BASEARRAY_H_ */
