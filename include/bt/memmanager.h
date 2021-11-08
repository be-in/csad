/*
 * memmanager.h
 *
 *  Created on: 13.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef MEMMANAGER_H_
#define MEMMANAGER_H_

#include <bt/functions.h>
#include <bt/macrostype.h>
#include <bt/btapi.h>
#include <bt/typesproc.h>

namespace bt {

OPTIMIZE_ON;

#define MEMNULL \
	_FORCEINLINE void* operator new(size_t) { return 0; } \
	_FORCEINLINE void operator delete(void* ) { }

#define MEMDEFAULT(classname) \
	_FORCEINLINE void* operator new(size_t size) { return extFunctions.CreateMem((unsigned int)size, 0); } \
	_FORCEINLINE void operator delete(void* val) { extFunctions.DeleteMem(val, 0); }

#define MEMMANAGER(classname) \
	_FORCEINLINE void* operator new(size_t size) { return bt::internalmemmanager.getNew((unsigned int)size); } \
	_FORCEINLINE void operator delete(void* val) {bt::internalmemmanager.freeThis(val,sizeof(classname));}

#define MEMMANAGERCLEAN(classname) \
	_FORCEINLINE void* operator new(size_t size) { return bt::internalmemmanager.getNewClean((unsigned int)size); } \
	_FORCEINLINE void operator delete(void* val) { bt::internalmemmanager.freeThis(val,sizeof(classname)); }

/**
 * @class memManager
 *
 * @brief memManager - ��������� ���������� � ������������� ������ ������������� ������ �������� ������� size.
 *
 * ������ ������� ������ ������������ �� ���� ��������� �������� �� ������ ������������ �������� ������ ������ ������������ �����.
 * � ������ ����� ���������������� ���� ������ ������������� ���������� ��������������.
 * ��� ������������ ������ ������� ����������� ��������� � ������������ �������� ��� ������� ���������� ��������.
 * �� ������������ ��������������� �� ����������� ������������������, ������������ ��� ��������� ��������� ������.
 *
 * @see
 */

/**
 * @class globalMemManager
 *
 * @brief globalMemManager - ����� �������� ������ ��� ��������� ������������ ��������� ������.
 *
 * ������������ �� ���� ������������ ���������� ����������� ������� �������� ������.
 * � ������ ������� ����� ������ �� ������������� �������� ���������� ������ ������������ ����������.
 *
 * ��� ������������� � ������������� ������ ���������� ������� ����� isThread ��� ������������� ������.
 * ����� ��������� �������������� ���������� ������ ��������� �������������� ����� � ���������� ������� manage.
 *
 * @see
 */

	class memManagerExport {
	public:
		MEMDEFAULT(memManagerExport)

		BT_API memManagerExport(unsigned int size);

		BT_API virtual ~memManagerExport();

		/// destroy all memory segments and free list of free pointers
		BT_API void _free();
		/// return pointer to new object and create new segment of objects if need.
		BT_API void *_addAlloc();
		/// return pointer to free object
		BT_API void *_getFree(unsigned int size);
		/// add pointer to list of free
		BT_API void _appendToFree(_voidint idat);
		/// mark pointer to free ???
		BT_API void _markFree(void* val);
		/// return number object in segment
		BT_API unsigned int _valid(unsigned int id);
		/// return segment number
		BT_API unsigned int _segid(unsigned int id);
		/// prepare calculation for object size
		BT_API void _calcsize(unsigned int size);

	private:
		enum States {
			VALIDED = 0x011F1C01,
			FREE = 0
		};

		unsigned int fisVal;
		struct p_smemManager *fargs;
	};

	class memManager: public memManagerExport {
	public:
		MEMDEFAULT(memManager)

		_FORCEINLINE memManager(unsigned int size):memManagerExport(size) {}

		_FORCEINLINE ~memManager() {}

		/// create memory for object
		_FORCEINLINE void *getNew(unsigned int size) {return (void*)_getFree(size);}
		/// delete memory for object
		_FORCEINLINE void freeThis(void * val) {_appendToFree((_voidint)val);}
		/// destroy all memory segments and free list of free
		_FORCEINLINE void free() {_free();};
	};

	class globalMemManager {
	public:
		MEMDEFAULT(globalMemManager)

		BT_API globalMemManager();
		BT_API ~globalMemManager();

		/// �������� ������� ������� ������ �� ���������� ������
		BT_API void* getNew(unsigned int size);
		/// �������� ������� ������� ������ �� ���������� ������
		BT_API void* getNewClean(unsigned int size);
		/// ����������� ������� ������� ������ ��� ���������� �������������
		BT_API void freeThis(void*val,unsigned int size);

		/// �������� ������� ������ ������������ ���������� ���� ������� �������������� ������� �� �������������.
		BT_API void* cashalloc(unsigned int size);
		/// ����������� ������� ������ �������� ������ ��� ���������.
		BT_API void cashfree(void* val,unsigned int size);

		/// ���������� ������������� ���������� ������������� ������
		BT_API void manage();
		_FORCEINLINE volatile bool &lock() { return flock; }
		_FORCEINLINE volatile _voidint &lockId() { return flockid; }
		_FORCEINLINE volatile _voidint &canLeave() { return fcanleaveid; }
		tfSTDCALL_uint_FUNC isThread;

		/// ������� ������� ������������ ������
		_FORCEINLINE unsigned int _olevel() {return olevel;}

	private:
		enum States {
			VALIDED = 0x011F1C01,
			FREE = 0
		};

		unsigned int fisVal;
		struct p_globalMemManager *fmanagers;
		unsigned int olevel;
		volatile bool flock;
		volatile _voidint flockid;
		volatile _voidint fcanleaveid;

		unsigned int alignSize(unsigned int  size);
		_voidint alignPointer(_voidint p);
		void init();
		void cleaner();
	};

	extern globalMemManager BT_API internalmemmanager;

OPTIMIZE_OFF;

}

#endif /* MEMMANAGER_H_ */
