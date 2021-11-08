//=============================================================================
///**
// *  @file   array.h
// *
// *  $Id: array.h 23.05.2012  $
// *
// *  @brief sdio, MS Visual C++ 2003-2008
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_ARRAY_H
#define GEN3_ARRAY_H

#include <bt/memmanager.h>
#include <bt/baseclassarray.h>
#include <bt.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

/**
 * @class Vector
 *
 * @brief Vector - continuous array data type T.
 *
 *  ¬ отличии от std::vector скорость выполнени€ операций снижена за счет переходов на реализацию методов, имеет более компактный код.
 *  ѕри доступе к элементу, в некоторых случа€х, производит константное вычисление размера данных.
 *
 * @see bt
 */
template <typename T>

class Vector {
public:

	_FORCEINLINE Vector() {arrFunctions.ANTInit(&mData,sizeof(T),0);}
	_FORCEINLINE Vector(int count) {arrFunctions.ANTInit(&mData,sizeof(T),count);}
	_FORCEINLINE ~Vector() {arrFunctions.ANTFree(&mData);}

	/// The object that abstracts a single interface access to the items in the collection
	class iterator {
	public:
		_FORCEINLINE iterator(T *_val,T *_end) {m_point=_val; m_end=_end;}

		/// The value of the current element.
		_FORCEINLINE T &value() {return (T&)*m_point;}

		_FORCEINLINE T operator ++() {T *it=m_point; m_point++; if (m_end==m_point) m_point=0; return *it;};
		_FORCEINLINE T operator ++(int) {T *it=m_point; m_point++; if (m_end==m_point) m_point=0; return *it;};
		_FORCEINLINE bool operator ==(iterator _a) {return m_point==_a.m_point;}
		_FORCEINLINE bool operator !=(iterator _a) {return m_point!=_a.m_point;}
	private:
		T *m_point;
		T *m_end;
	};

	/// Returns an iterator pointing to the first element in the sequence.
	_FORCEINLINE iterator begin() {return iterator((T*)&mData.Vals[0],(T*)arrFunctions.ANTPosition(&mData,mData.Count));}
	/// Returns an iterator to the conditional end in the sequence
	_FORCEINLINE iterator end() {return iterator(0,(T*)arrFunctions.ANTPosition(&mData,mData.Count));}
	/// Returns true if the array does not contain any element.
	_FORCEINLINE bool isEmpty() {return mData.Count==0;}

	/// Number of array elements.
	_FORCEINLINE unsigned int count() {return mData.Count;}
	_FORCEINLINE unsigned int reservSize() {return mData.AllCount;}
	_FORCEINLINE unsigned int size() {return mData.Count;}
	_FORCEINLINE unsigned int sizeOfType() {return mData.ItSize;}
	/// Frees an array of completely deleting the allocated memory.
	_FORCEINLINE void clear() {mData.Count=0;}
	_FORCEINLINE void resize(unsigned int asize) {arrFunctions.ANTResize(&mData,asize);}
	_FORCEINLINE void reserve(unsigned int asize) {arrFunctions.ANTReserv(&mData,asize);}
	/// Returns an array of data in a continuous sequence of elements.
	_FORCEINLINE T* data() {return (T*)mData.Vals;}
	/// Adds a new element.
	_FORCEINLINE void assign(T _val) {arrFunctions.ANTAssign(&mData,&_val);}
	///
	_FORCEINLINE void push_back(T _val) {arrFunctions.ANTAssign(&mData,&_val);}
	/// Removes the last element.
	_FORCEINLINE void pop_back() {arrFunctions.ANTDelLast(&mData);}
	/// Returns the last element of the array.
	_FORCEINLINE T &last() {return *((T*)arrFunctions.ANTPositionL(&mData));}
	/// Returns the first element of the array.
	_FORCEINLINE T &first() {return *((T*)&mData.Vals[0]);}
	/// Returns the element of the selected position of the array.
	_FORCEINLINE T &at(unsigned int id) {return *((T*)arrFunctions.ANTPosition(&mData,id));}

	_FORCEINLINE void absorb(Vector &vector) {
		clear();
		mData.Vals=vector.mData.Vals;
		mData.Count=vector.mData.Count;
		mData.AllCount=vector.mData.AllCount;
		vector.mData.Vals=0;
		vector.mData.Count=0;
		vector.mData.AllCount=0;
	}

	_FORCEINLINE T &operator[](unsigned int id) const {
		return *((T*)arrFunctions.ANTPosition((void*)&mData,id));
	}

private:
	sArray mData;
};

/**
 * @class VoidVector
 *
 * @brief VoidVector - continuous array of pointers of type T.
 *
 *  ¬ отличии от std::vector скорость выполнени€ операций снижена за счет переходов на реализацию методов, имеет более компактный код.
 *
 * @see BaseVoidVector
 */

template <typename T>

class VoidVector {
public:
	_FORCEINLINE void* operator new(size_t) { return 0; } \
	_FORCEINLINE void operator delete(void*) { }

	_FORCEINLINE VoidVector() : mData(0) {}
	_FORCEINLINE VoidVector(int count) : mData(0) { arrFunctions.DPSetCount(&mData, count); }
	_FORCEINLINE ~VoidVector() {arrFunctions.DPFree(&mData);}

	/// The object that abstracts a single interface access to the items in the collection
	class iterator {
	public:
		_FORCEINLINE iterator(T **_val) {m_point=_val;}

		/// The value of the current element.
		_FORCEINLINE T *value() {return (T*)*m_point;}
		_FORCEINLINE _voidint valueNum() { return (_voidint)*m_point; }

		_FORCEINLINE T *operator ++() {T **it=m_point; m_point++; return *it;};
		_FORCEINLINE T *operator ++(int) {T **it=m_point; m_point++; return *it;};
		_FORCEINLINE bool operator ==(iterator _a) {return m_point==_a.m_point;}
		_FORCEINLINE bool operator !=(iterator _a) {return m_point!=_a.m_point;}
	private:
		T **m_point;
	};

	/// Returns an iterator pointing to the first element in the sequence.
	_FORCEINLINE iterator begin() { return iterator((T**)arrFunctions.MPArray(&mData)); }
	/// Returns an iterator to the conditional end in the sequence.
	_FORCEINLINE iterator end() { return iterator((T**)arrFunctions.APEnd(&mData)); }
	/// Returns true if the array does not contain any element.
	_FORCEINLINE bool isEmpty() { return arrFunctions.MPCount(&mData)==0; }

	/// Number of array elements.
	_FORCEINLINE unsigned int count() {return arrFunctions.MPCount(&mData);}
	/// Number of array elements.
	_FORCEINLINE unsigned int size() {return arrFunctions.MPCount(&mData);}
	/// Frees an array of completely deleting the allocated memory.
	_FORCEINLINE void clear() {arrFunctions.DPFree(&mData);}
	/// Creates an array with the specified number of elements.
	_FORCEINLINE void resize(unsigned int asize) {arrFunctions.DPSetCount(&mData,asize);}
	// Allocates memory for an array with the specified number of elements without changing its size.
	//_FORCEINLINE void reserve(unsigned int asize) {mData._reserv(asize);}
	/// Returns an array of data in a continuous sequence of elements.
	_FORCEINLINE T** data() { return (T**)arrFunctions.MPArray(&mData); }
	_FORCEINLINE T** endData() { return (T**)arrFunctions.APEnd(&mData); }
	/// Adds a new element.
	_FORCEINLINE void assign(T* _val) { arrFunctions.DPAddLast(&mData,_val); }
	/// Removes the element with the specified value and returns its position, otherwise-1.
	_FORCEINLINE int del(T* _val) { return arrFunctions.DPRemoveVal(&mData,_val); }
	///
	_FORCEINLINE void push_back(T *_val) { arrFunctions.DPAddLast(&mData,_val); }
	/// Removes the last element.
	_FORCEINLINE void pop_back() {arrFunctions.DPRemoveLast(&mData);}
	/// Returns the last element of the array.
	_FORCEINLINE T *&last() { return (*(T**)arrFunctions.APLast(&mData)); }
	/// Returns the first element of the array.
	_FORCEINLINE T *&first() { return (*(T**)arrFunctions.MPArray(&mData)); }
	/// Returns the element of the selected position of the array.
	_FORCEINLINE T *&at(unsigned int id) { return (*((T**)arrFunctions.MPArray(&mData)+id)); }

	///
	_FORCEINLINE void absorb(VoidVector &vector) {
		clear();
		mData=vector.mData;
		vector.mData=0;
	}

	_FORCEINLINE T *&operator[](unsigned int id) const { return *((T**)arrFunctions.MPArray((void*)&mData)+id); }

private:
	void *mData;
};

/**
 * @class SortVoidVector
 *
 * @brief SortVoidVector - continuous sorted array of pointers of type T.
 *
 * Unlike VoidVector has a faster search.
 *
 * @see BaseSortVoidVector
 */
template <typename T>

class SortVoidVector {
public:
	MEMNULL

	//_FORCEINLINE SortVoidVector(SortVoidVector &arr) {mData=arrFunctions.APClone(&arr.mData);}
	_FORCEINLINE SortVoidVector():mData(0) {}
	_FORCEINLINE ~SortVoidVector() { arrFunctions.APFree(&mData); }

	/// The object that abstracts a single interface access to the items in the collection.
	class iterator {
	public:
		_FORCEINLINE iterator(T **_val) {m_point=_val;}

		/// The value of the current element.
		_FORCEINLINE T* &value() {return (T*&)(*m_point);}

		_FORCEINLINE T* operator ++() { T **it=m_point; m_point++; return *it; };
		_FORCEINLINE T* operator ++(int) { T **it=m_point; m_point++; return *it; };
		_FORCEINLINE bool operator ==(iterator _a) { return m_point==_a.m_point; }
		_FORCEINLINE bool operator !=(iterator _a) { return m_point!=_a.m_point; }
	private:
		T **m_point;
	};

	/// Returns an iterator pointing to the first element in the sequence.
	_FORCEINLINE iterator begin() { return iterator((T**)arrFunctions.MPArray(&mData)); }
	/// Returns an iterator to the conditional end in the sequence.
	_FORCEINLINE iterator end() { return iterator((T**)arrFunctions.APEnd(&mData)); }
	/// Returns true if the array does not contain any element.
	_FORCEINLINE bool isEmpty() { return arrFunctions.MPCount(&mData)==0; }

	/// Number of array elements.
	_FORCEINLINE unsigned int count() {return arrFunctions.MPCount(&mData);}
	/// Number of array elements.
	_FORCEINLINE unsigned int size() {return arrFunctions.MPCount(&mData);}
	/// Frees an array of completely deleting the allocated memory.
	_FORCEINLINE void clear() {arrFunctions.APFree(&mData);}
	/// Returns an array of data in a continuous sequence of elements.
	_FORCEINLINE T** data() {return (T**)arrFunctions.MPArray(&mData);}
	/// Adds a new element.
	_FORCEINLINE void assign(T *_val) {arrFunctions.APAdd(&mData,_val);}
	/// Returns the position of the element with the specified value, if not -1.
	_FORCEINLINE int find(T* _val) {return arrFunctions.APFind(&mData,_val);}
	/// Removes the element with the specified value and returns its position, otherwise-1.
	_FORCEINLINE int del(T* _val) {return arrFunctions.APRemove(&mData,_val);}
	///
	/// Returns the last element of the array.
	_FORCEINLINE T *&last() {return (*(T**)arrFunctions.APLast(&mData));}
	/// Returns the first element of the array.
	_FORCEINLINE T *&first() {return (*(T**)arrFunctions.MPArray(&mData));}
	/// Returns the element of the selected position of the array.
	_FORCEINLINE T *&at(unsigned int id) { return (*((T**)arrFunctions.MPArray(&mData)+id));}

	_FORCEINLINE T *operator[](unsigned int id) const { return *((T**)arrFunctions.MPArray((void*)&mData)+id);}

	void absorb(SortVoidVector &vector) {
		clear();
		mData=vector.mData;
		vector.mData=0;
	}

	void copy(SortVoidVector &vector) {	clear(); mData=arrFunctions.APClone(&vector.mData);	}

	void add(SortVoidVector &vector) {
		int c=arrFunctions.MPCount(&vector.mData);
		int id=0;
		void **t=(void **)arrFunctions.MPArray(&vector.mData);
		while (id<c) { arrFunctions.APAdd(&mData,t[id]);id++; }
	}

private:
	void* mData;
};

/**
 * @class HashVector
 *
 * @brief HashVector - continuous array data type T.
 *
 * Unlike Vector has a faster search and does not have the last and the first element.
 * Sort this array can cause data loss.
 *
 * @see BaseHashVector
 */
template <typename T>

class HashVector {
public:
	_FORCEINLINE HashVector(BaseHashVector &data):mData(data) {}
	_FORCEINLINE HashVector():mData(sizeof(T)) {}
	_FORCEINLINE ~HashVector() {}

	class iterator {
	public:
		_FORCEINLINE iterator(T *_val,T *_end) {m_point=_val; m_end=_end;}

		/// The value of the current element.
		_FORCEINLINE T &value() {return (T&)(*m_point);}

		_FORCEINLINE T operator ++() {T *it=m_point; m_point++; if (m_end==m_point) m_point=0; return *it;};
		_FORCEINLINE T operator ++(int) {T *it=m_point; m_point++; if (m_end==m_point) m_point=0; return *it;};
		_FORCEINLINE bool operator ==(iterator _a) {return m_point==_a.m_point;}
		_FORCEINLINE bool operator !=(iterator _a) {return m_point!=_a.m_point;}
	private:
		T *m_point;
		T *m_end;
	};

	_FORCEINLINE iterator begin() {return iterator((T*)&mData.mVals[0],(T*)mData._point(mData.mCount));}
	_FORCEINLINE iterator end() {return iterator(0,(T*)mData._point(mData.mCount));}

	_FORCEINLINE bool isEmpty() {return mData.mCount==0;}

	_FORCEINLINE unsigned int count() {return mData.mCount;}
	_FORCEINLINE unsigned int size() {return mData.mCount;}
	_FORCEINLINE void clear() {mData._clear();}
	_FORCEINLINE void reserv(unsigned int count) {mData._realloc(count);}
	_FORCEINLINE T* data() {return (T*)mData.mVals;}
	_FORCEINLINE void assign(T _val) {mData._assign(&_val);}
	_FORCEINLINE int find(T _val) {return mData._find(&_val);}
	_FORCEINLINE int del(T _val) {return mData._del(&_val);}
	_FORCEINLINE bool removeAt(unsigned int id) {return mData._removeAt(id);}
//	_FORCEINLINE T &last() {return *((T*)mData._last());}
//	_FORCEINLINE T &first() {return *((T*)&mData.mVals[0]);}
	_FORCEINLINE T &at(unsigned int id) {return *((T*)mData._point(id));}
	_FORCEINLINE void move(HashVector * v) {mData._moveToNew(&v->mData);}

	_FORCEINLINE void absorb(HashVector &vector) {
		clear();
		mData.mVals=vector.mData.mVals;
		mData.mCount=vector.mData.mCount;
		mData.mAllCount=vector.mData.mAllCount;
		mData.mHashLevel=vector.mData.mHashLevel;
		mData.mHashedC=vector.mData.mHashedC;
		vector.mData.mVals=0;
		vector.mData.mCount=0;
		vector.mData.mAllCount=0;
		vector.mData.mHashLevel=0;
		vector.mData.mHashedC=0;
	}

	_FORCEINLINE void add(HashVector &vector) {
		int c=vector.count();
		int id=0;
		while (id<c) {mData._assign(vector.mData._point(id)); id++;}
	}

	_FORCEINLINE T &operator[](unsigned int id) const {
		return *((T*)mData._point(id));
	}

private:
	BaseHashVector mData;
};

/**
 * @class LinkArray
 *
 * @brief LinkArray - the interface of the segment to the memory of identical elements.
 *
 * Interface for continuous chunk of memory, of identical elements arranged in _from with an initial offset _offset step _step, the Maximum number of elements that is under the pointer *_max.
 *
 * @see
 */
	template <typename T>

	class LinkArray
	{
	public:
		///  онструктор
		/// @param _from - a pointer of array.
		/// @param _offset - additional offset (array=_from+_offset)
		/// @param _step - the number of bytes before the start of the new element.
		/// @param _max - a pointer to the parameter contains the number of elements in the array.
		_FORCEINLINE LinkArray(void *_from,unsigned int _offset,unsigned int _step,unsigned int *_max)
		{	
			m_array=(char*)_from;
			m_array+=_offset;
			m_step=_step;
			m_count=_max;
		}

		_FORCEINLINE ~LinkArray() {}

		/// The object that abstracts a single interface access to the items in the collection.
		class iterator {
		public:
			_FORCEINLINE iterator(char*from,_voidint next) { val=from; fstep=next; }
			_FORCEINLINE ~iterator() {}
			/// The value of the current element.
			_FORCEINLINE T& value() { return *(T*)val; }

			_FORCEINLINE _voidint step() { return fstep; }

			_FORCEINLINE iterator &operator ++(int) { val+=fstep; return (*this); }
			_FORCEINLINE iterator &operator +=(int add) { val+=add*fstep; return (*this); }
			_FORCEINLINE iterator &operator +(int add) { iterator it(val+add*fstep,fstep); return it; }

			_FORCEINLINE iterator& operator =(const T& _Right) { (*(T*)val)=_Right; return (*this);	}

			_FORCEINLINE bool operator ==(const iterator& _Right) { return val==_Right.val;	}

			_FORCEINLINE bool operator !=(const iterator& _Right) { return val!=_Right.val; }
		private:
			char *val;
			_voidint fstep;
		};

		/// Returns an iterator pointing to the first element in the sequence.
		_FORCEINLINE iterator &begin() { return iterator(m_array,m_step); }
		/// Returns an iterator to the conditional end in the sequence.
		_FORCEINLINE iterator &end() { return iterator(m_array+(m_count*m_step),m_step); }

		/// Returns the number of elements of the real array
		_FORCEINLINE unsigned int count() { return *m_count; }

		/// Returns the value of the array element
		_FORCEINLINE T value(unsigned int _id) { char *p=m_array+_id*m_step; return *((T*)p); }

		/// Sets the value of the array element
		_FORCEINLINE void setValue(unsigned int _id,T &_val) { char *p=m_array+_id*m_step; *((T*)p)=_val; }

		_FORCEINLINE T &operator[](unsigned int _id) const { char *p=m_array+_id*m_step; return *((T*)p); }

		/// returns an array (_from+_offset)
		_FORCEINLINE char *getArray() {return m_array;}
		/// returns the step
		_FORCEINLINE unsigned int getStep() {return m_step;}
	private:
		/// A pointer to the actual array
		char *m_array;
		/// Distance in bytes between elements of the array
		unsigned int m_step;
		/// Pointer to count elements of a real array
		unsigned int *m_count;
	};

	/**
	 * @class MapName
	 *
	 * @brief MapName - associative list matches a specific string is the address of the specified data type.
	 *
	 *
	 * @see BaseMapName
	 */

	template <typename T>

	class MapName {
	public:
		MEMNULL

		_FORCEINLINE MapName() :mData(0) {}
		_FORCEINLINE ~MapName() { arrFunctions.MSSPFree(&mData); }

		/// The object that abstracts a single interface access to the items in the collection.
		class iterator {
		public:
			_FORCEINLINE iterator(void *val):m_point((void**)val) {}
			_FORCEINLINE ~iterator() {}

			/// Returns the name of the element.
			_FORCEINLINE const char * key() { return (*(const char**)m_point)+1; }
			/// The value of the current element.
			_FORCEINLINE T* value() { return (*(T**)(m_point+1)); }

			_FORCEINLINE iterator& operator++(int) { m_point+=2; return *this; }
			_FORCEINLINE iterator& operator+=(int count) { m_point+=count<<1; return *this; }
			_FORCEINLINE bool operator==(const iterator& _Right) { return m_point==_Right.m_point; }
			_FORCEINLINE bool operator!=(const iterator& _Right) { return m_point!=_Right.m_point; }

		private:
			void **m_point;
		};

		/// Returns an iterator pointing to the first element in the sequence.
		_FORCEINLINE iterator begin() { return iterator(arrFunctions.MPArray(&mData)); }
		/// Returns an iterator to the conditional end in the sequence.
		_FORCEINLINE iterator end() { return iterator(arrFunctions.MPEnd(&mData)); }

		_FORCEINLINE void clear() { arrFunctions.MSSPFree(&mData); }
		/// Number of array elements.
		_FORCEINLINE unsigned int count() { return arrFunctions.MPCount(&mData); }
		_FORCEINLINE unsigned int count(char* _key) { unsigned int ret = 0; if (arrFunctions.MSSPFind(&mData, (void*)_key)) ret = 1; return ret; }
		_FORCEINLINE void assign(char* _key, T*val) { arrFunctions.MSSPAdd(&mData, (void*)_key, (void*)val); }
		_FORCEINLINE bool contains(char* _key) { return arrFunctions.MSSPFind(&mData,(void*)_key)!=0; }
		_FORCEINLINE bool contains(const char* &_key) { return arrFunctions.MSSPFind(&mData,(void*)_key)!=0; }
		/// Returns a pointer value of a given type, if the value of this key contains, otherwise returns 0.
		_FORCEINLINE T* find(char* _key) { void** val=static_cast<void**>(arrFunctions.MSSPFind(&mData,_key)); if (val) val=static_cast<void**>(*val); return (T*)(val); }
		_FORCEINLINE T* find(const char* &_key) { void** val=static_cast<void**>(arrFunctions.MSSPFind(&mData,_key)); if (val) val=static_cast<void**>(*val); return (T*)(val); }
		_FORCEINLINE T* find(char* _key, T*def) { void** val = static_cast<void**>(arrFunctions.MSSPFind(&mData, _key)); if (val) def=(T*)(*val); return (T*)(def); }
		_FORCEINLINE T* find(const char* &_key, T*def) { void** val = static_cast<void**>(arrFunctions.MSSPFind(&mData, _key)); if (val) def=(T*)(*val); return (T*)(def); }
		_FORCEINLINE int remove(char* _key) { return arrFunctions.MSSPRemove(&mData,_key); }
		_FORCEINLINE int remove(const char* _key) { return arrFunctions.MSSPRemove(&mData,(void*)_key); }
		//_FORCEINLINE const char* key(T *_val,const char* _key) { return mData._key((void*)_val,_key); }
		_FORCEINLINE const char* keyNull(T *_val) { char *k = (char *)arrFunctions.MPFindByVal(&mData, _val, 0); if (k) k += 1; return k; }
		_FORCEINLINE const char* key(T *_val, const char* &_key) { char *k = (char *)arrFunctions.MPFindByVal(&mData, _val, 0); if (!k) k=((char*)_key)-1; return k + 1; }
		/// Returns a pointer value of a given type.
		_FORCEINLINE T* valueAt(unsigned _int32 id) { void** val=static_cast<void**>(arrFunctions.MPArray(&mData)); if (val) return (T*)(val[(id<<1)+1]); return 0;}

		_FORCEINLINE T*& operator[](char * _key) { return *(((T**)arrFunctions.MSSPAdd(&mData, (void*)_key, 0)) + 1); }
		_FORCEINLINE T*& operator[](const char * _key) { return *(((T**)arrFunctions.MSSPAdd(&mData, (void*)_key, 0)) + 1); }

	private:
		void* mData;
	};

	/**
	 * @class MapVoid
	 *
	 * @brief MapVoid - associative list matches a particular address another address of the specified data type.
	 *
	 *
	 * @see bt
	 */

	template <typename T>

	class MapVoid {
	public:
		MEMNULL

		//_FORCEINLINE MapVoid(void*data) {mData=data;}
		_FORCEINLINE MapVoid():mData(0) {}
		_FORCEINLINE MapVoid(int) {}
		_FORCEINLINE ~MapVoid() { arrFunctions.MPFree(&mData); }

		/// The object that abstracts a single interface access to the items in the collection.
		class iterator {
		public:
			_FORCEINLINE iterator(void *val):m_point((void**)val) {}
			_FORCEINLINE ~iterator() {}
			_FORCEINLINE void* key() { return *m_point; }
			/// The value of the current element.
			_FORCEINLINE T* value() { return (T*)m_point[1]; }

			_FORCEINLINE void* &operator ++() { void **it=m_point; m_point+=2; return *it; }
			_FORCEINLINE void* &operator ++(int) { void **it=m_point; m_point+=2; return *it; }

			_FORCEINLINE bool operator ==(const iterator& _a) { return m_point==_a.m_point; }
			_FORCEINLINE bool operator !=(const iterator& _a) { return m_point!=_a.m_point; }
		private:
			void **m_point;
		};

		/// Returns an iterator pointing to the first element in the sequence.
		_FORCEINLINE iterator begin() { return iterator(arrFunctions.MPArray(&mData)); }
		/// Returns an iterator to the conditional end in the sequence.
		_FORCEINLINE iterator end() { return iterator(arrFunctions.MPEnd(&mData)); }

		/// Removes a list of associative records.
		_FORCEINLINE void clear() { arrFunctions.MPFree(&mData); }
		/// The number of associative entries in the list.
		_FORCEINLINE unsigned int count() { return arrFunctions.MPCount(&mData); }
		/// Returns true if the value of this key contains.
		_FORCEINLINE bool contains(void* _key) { return arrFunctions.MPFind(&mData,_key)!=0; }
		/// Returns true if the value of this key contains.
		_FORCEINLINE bool contains(_voidint _key) { return arrFunctions.MPFind(&mData, (void*)_key) != 0; }
		/// Returns a pointer value of a given type, if the value of this key contains, otherwise returns 0.
		_FORCEINLINE T* find(void* _key) { void**c=(void**)arrFunctions.MPFind(&mData,_key); if (c) c=(void**)*c; return (T*)c; }
		/// Returns a pointer value of a given type, if the value of this key contains, otherwise returns 0.
		_FORCEINLINE T* find(_voidint _key) { void**c = (void**)arrFunctions.MPFind(&mData, (void*)_key); if (c) c=(void**)*c; return (T*)c; }
		/// Removes from the list the value of the specified key and returns its position in the list if it is present, otherwise returns -1.
		_FORCEINLINE T* remove(void* _key) { return (T*)arrFunctions.MPRemove(&mData,_key); }
		/// Removes from the list the value of the specified key and returns its position in the list if it is present, otherwise returns -1.
		_FORCEINLINE T* remove(_voidint _key) { return (T*)arrFunctions.MPRemove(&mData, (void*)_key); }
		//_FORCEINLINE void* key(T *_val,void* _key) { return mData._key((void*)_val,_key); };
		/// returns an array of data.
		_FORCEINLINE void* data() { return (void*)mData; }

		_FORCEINLINE T*& operator[](void * _key) { return *((T**)arrFunctions.MPAdd(&mData,_key,0)); }
		_FORCEINLINE T*& operator[](_voidint _key) { return *((T**)arrFunctions.MPAdd(&mData, (void*)_key, 0)); }

	private:
		void *mData;
	};

	/**
	 * @class MapVoidInt
	 *
	 * @brief MapVoidInt - associative list matches a particular address another address of the specified data type.
	 *
	 *
	 * @see bt
	 */

	class MapVoidInt {
	public:
		MEMNULL

		//_FORCEINLINE MapVoid(void*data) {mData=data;}
		_FORCEINLINE MapVoidInt() { mData=0; }
		_FORCEINLINE ~MapVoidInt() { arrFunctions.MPFree(&mData); }

		/// The object that abstracts a single interface access to the items in the collection.
		class iterator {
		public:
			_FORCEINLINE iterator(void *val):m_point((void**)val) {}
			_FORCEINLINE ~iterator() {}
			_FORCEINLINE _voidint key() {return (_voidint)*m_point;}
			/// The value of the current element.
			_FORCEINLINE _voidint value() {return (_voidint)m_point[1];}

			_FORCEINLINE void* &operator ++() {void **it=m_point; m_point+=2; return *it; }
			_FORCEINLINE void* &operator ++(int) {void **it=m_point; m_point+=2; return *it; }

			_FORCEINLINE bool operator ==(const iterator& _a) { return m_point==_a.m_point; }
			_FORCEINLINE bool operator !=(const iterator& _a) { return m_point!=_a.m_point; }
		private:
			void **m_point;
		};

		/// Returns an iterator pointing to the first element in the sequence.
		_FORCEINLINE iterator begin() { return iterator(arrFunctions.MPArray(&mData)); }
		/// Returns an iterator to the conditional end in the sequence.
		_FORCEINLINE iterator end() { return iterator(arrFunctions.MPEnd(&mData)); }

		/// Removes a list of associative records.
		_FORCEINLINE void clear() { arrFunctions.MPFree(&mData); }
		/// The number of associative entries in the list.
		_FORCEINLINE unsigned int count() { return arrFunctions.MPCount(&mData); }
		/// Returns true if the value of this key contains.
		_FORCEINLINE bool contains(void* _key) { return arrFunctions.MPFind(&mData,_key)!=0; }
		/// Returns a pointer value of a given type, if the value of this key contains, otherwise returns 0.
		_FORCEINLINE _voidint find(void* _key) { void**c=(void**)arrFunctions.MPFind(&mData,_key); if (c) c=(void**)*c; return (_voidint)c; }
		/// Removes from the list the value of the specified key and returns its position in the list if it is present, otherwise returns -1.
		_FORCEINLINE _voidint remove(void* _key) { return (_voidint)arrFunctions.MPRemove(&mData,_key); }
		//_FORCEINLINE void* key(T *_val,void* _key) { return mData._key((void*)_val,_key); };
		/// returns an array of data.
		_FORCEINLINE void* data() { return (void*)mData; }

		_FORCEINLINE _voidint& operator[](void * _key) {return *((_voidint*)arrFunctions.MPAdd(&mData,_key,0));}

	private:
		void *mData;
	};

	/**
	 * @class ConstMapVoid
	 *
	 * @brief ConstMapVoid - constant associative list matches a particular address another address of the specified data type.
	 *
	 *
	 * @see bt, arrFunctions.
	 */

	template <typename R,typename T,int max>

	class ConstMapVoid {
	public:
		MEMNULL

		_FORCEINLINE ConstMapVoid() { mData.count=0; }
		_FORCEINLINE ~ConstMapVoid() {}

		/// The number of associative entries in the list.
		_FORCEINLINE unsigned int count() { return mData.count; }
		/// Returns true if the value of this key contains.
		_FORCEINLINE bool contains(void* _key) { return arrFunctions.MPFind(&mData,_key)!=0; }
		/// Returns a pointer value of a given type, if the value of this key contains, otherwise returns 0.
		_FORCEINLINE T* find(R _key) { return (T*)arrFunctions.MCPFind(&mData,(void*)_key); }
		/// 
		_FORCEINLINE void**data() { return mData.data; }

		_FORCEINLINE T& operator[](R _key) {
			T*rez=(T*)arrFunctions.MCPFind(&mData,(void*)_key);
			if (rez) return (T&)*rez;
			rez=(T*)arrFunctions.MCPAdd(&mData,(void*)_key,max);
			if (rez) return (T&)*rez;
			assert(false);
		}

	private:
		struct tConstMapVoidData {
			unsigned int count;
			void*data[2*max];
		};
		tConstMapVoidData mData;
	};

/**
 * @class ShortString
 *
 * @brief ShortString - a short string that can contain no more than 255 8bits characters.
 *
 * For example:
 @verbatim
   ShortString a("list: ");
   a+="1, str 1.";
   printf(a.str());
   char num=a[6];
   printf(num);
 @endverbatim
 *
 * @see bt
 */

	class ShortString {
	public:
		MEMNULL

		_FORCEINLINE ShortString() { mData=0; }
		_FORCEINLINE ShortString(const char *_ch) { mData=0;arrFunctions.SSet(&mData,(void*)_ch); }
		_FORCEINLINE ~ShortString() { arrFunctions.SSet(&mData,0); }

		/// return 0 if equal, see CmpMem
		_FORCEINLINE int compare(char *ch) { return arrFunctions.SCompare(&mData,(void*)ch); }
		/// return 0 if equal, see CmpMem
		_FORCEINLINE int compare(const char *ch) { return arrFunctions.SCompare(&mData,(void*)ch); }

		/// returns a string in the form of an array of characters.
		_FORCEINLINE const char*str() { char *ret = 0; if (mData) ret = &((char*)mData)[1]; return ret; }
		/// returns the number of characters in the string
		_FORCEINLINE unsigned char length() { unsigned char ret = 0;  if (mData) ret = ((unsigned char*)mData)[0]; return ret; }

		/// returns an array of data.
		_FORCEINLINE char* data() { return (char*)mData; }
		/// saves the data array after removal of the object.
		_FORCEINLINE void keep() { mData=0; }

		_FORCEINLINE _int32 toInt() { _int32 ret = 0; if (!mData) ret = extFunctions.STRToI((void*)&((char*)mData)[1]); return ret; }

		_FORCEINLINE ShortString & operator=(char ch) { arrFunctions.SSet(&mData,(void*)(unsigned char)ch); return *this; }
		_FORCEINLINE ShortString & operator=(const char *ch) { arrFunctions.SSet(&mData,(void*)ch); return *this;}

		_FORCEINLINE ShortString & operator+=(char ch) { arrFunctions.SAdd(&mData,(void*)(unsigned char)ch); return *this; }
		_FORCEINLINE ShortString & operator+=(const char *ch) { arrFunctions.SAdd(&mData,(void*)ch); return *this; }
		_FORCEINLINE ShortString & operator=(ShortString & ch) { arrFunctions.SSet(&mData,(void*)ch.str()); return *this; }

		_FORCEINLINE void absorb(ShortString &string) {
			arrFunctions.SSet(&mData,0);
			mData=string.mData;
			string.mData=0;
		}

		_FORCEINLINE char operator[](int id) { return ((char*)mData)[id+1]; }

	private:
		void* mData;
	};

/**
 * @class ShortStringList
 *
 * @brief ShortStringList - array of short string.
 *
 * For example:
 *
 * @see bt
 */

	class ShortStringList {
	public:
		MEMDEFAULT(ShortStringList)

		_FORCEINLINE ShortStringList() { mData=0; }
		_FORCEINLINE ~ShortStringList() { arrFunctions.DSFree(&mData); }

		/// Returns true if the array does not contain any element.
		_FORCEINLINE bool isEmpty() { return arrFunctions.MPCount(&mData)==0; }

		/// Number of array elements.
		_FORCEINLINE unsigned int count() { return arrFunctions.MPCount(&mData); }
		/// Returns an array of data in a continuous sequence of ShortString.
		_FORCEINLINE ShortString* data() { return (ShortString*)arrFunctions.MPArray(&mData); }
		/// Adds a new string.
		_FORCEINLINE void assign(char* _val) { arrFunctions.DSAddLast(&mData,_val); }

		_FORCEINLINE void absorb(ShortStringList &list) {
			arrFunctions.DSFree(&mData);
			mData=list.mData;
			list.mData=0;
		}

		_FORCEINLINE ShortString &operator[](int id) { return *((ShortString*)arrFunctions.MPArray((void*)&mData)+id); }

	private:
		void* mData;
	};

/**
 * @class String
 *
 * @brief String - a long string that can contain 4 milliard 8bits characters.
 *
 * For example:
 @verbatim
   String a("list: ");
   a+="1, str 1.";
   printf(a.str());
   char num=a[6];
   printf(num);
 @endverbatim
 *
 * @see bt
 */

	class String {
	public:
		MEMNULL

		_FORCEINLINE String() { mData=0; }
		_FORCEINLINE String(const char *_ch) { mData=0;arrFunctions.LSSet(&mData,(void*)_ch); }
		_FORCEINLINE ~String() { arrFunctions.LSSet(&mData,0); }

		_FORCEINLINE int compare(char *ch) { return arrFunctions.LSCompare(&mData,(void*)ch); }
		_FORCEINLINE int compare(const char *ch) { return arrFunctions.LSCompare(&mData,(void*)ch); }

		/// returns a string in the form of an array of characters.
		_FORCEINLINE const char*str() { char * ret = 0; if (mData) ret = &((char*)mData)[4]; return ret; }
		/// returns the number of characters in the string
		_FORCEINLINE unsigned _int32 length() { unsigned _int32 ret = 0; if (mData) ret = ((unsigned _int32*)mData)[0]; return ret; }

		_FORCEINLINE void insert(unsigned _int32 pos,char ch) { arrFunctions.LSInsert(&mData,(void*)ch,pos); }
		_FORCEINLINE void insert(unsigned _int32 pos,char *ch) { arrFunctions.LSInsert(&mData,(void*)ch,pos); }
		_FORCEINLINE void insert(unsigned _int32 pos,const char *ch) { arrFunctions.LSInsert(&mData,(void*)ch,pos); }
		_FORCEINLINE void remove(unsigned _int32 pos,const _int32 count) { arrFunctions.LSRemove(&mData,pos,count); }

		/// returns an array of data.
		_FORCEINLINE char* data() { return (char*)mData; }
		/// saves the data array after removal of the object.
		_FORCEINLINE void keep() { mData=0; }

		_FORCEINLINE String & operator=(char ch) { arrFunctions.LSSet(&mData,(void*)(unsigned char)ch); return *this; }
		_FORCEINLINE String & operator=(const char *ch) { arrFunctions.LSSet(&mData,(void*)ch); return *this; }

		_FORCEINLINE String & operator+=(char ch) { arrFunctions.LSAdd(&mData,(void*)(unsigned char)ch); return *this; }
		_FORCEINLINE String & operator+=(const char *ch) { arrFunctions.LSAdd(&mData,(void*)ch); return *this; }
		_FORCEINLINE String & operator=(String & ch) { arrFunctions.LSSet(&mData,(void*)ch.str()); return *this; }

		_FORCEINLINE void absorb(String &string) {
			arrFunctions.LSSet(&mData,0);
			mData=string.mData;
			string.mData=0;
		}

		_FORCEINLINE char operator[](int id) { return ((char*)mData)[id+4]; }

	private:
		void* mData;
	};

};

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif
