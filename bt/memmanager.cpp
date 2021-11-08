//=============================================================================
///**
// *  @file memmanager.cpp
// *
// *  $Id: memmanager.cpp 23.05.2012  $
// *
// *  @brief generator 3 tool, MS Visual C++ 2003-2008
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#include <bt.h>
#include "base/baseapi.h"

WARNING_DISABLE;
OPTIMIZE_ON;

//#define MEMORYCPP
//#define THREADDEBUG

namespace bt
{
	class SimpleMutex {
		SimpleMutex():lock(0) {}
	private:
		volatile int lock;
	};

	struct MapMemElement {
		void *key;
		void *val;
	};

	#define SEGMENT_ALIGN 16 // выравнивание начального адреса объекта по 16 байт
	#define SEGMENT_SIZE_MIN 8192 // минимальный размер сегмента памяти для объектов
	#define SEGMENT_OBJECTS_MIN 64 // минимальное количество объектов в сегменте - default 32

	struct p_smemManager {
		MEMDEFAULT(p_smemManager)

		_FORCEINLINE p_smemManager():fsegmentsval() {};
		/// max count of pointers
		unsigned int mAllCount;
		/// count of pointers
		unsigned int mCount;
		/// max size of stack for store free pointers
		unsigned int mAllFreeCount;
		/// count of objects pointers not in used
		unsigned int mFreeCount;
		/// segments of memory by objects count
		unsigned int fsegmentscount;
		/// segments of memory by objects
		void** fsegmentsval;  //std::vector<char*>
		/// memory pointer to objects who need to free
		_voidint *fneedFree;
		/// size of object
		unsigned int fsize;
		_voidint fmask;
		/// count objects in segment
		unsigned int ssize;
		/// size of segment
		unsigned int segmentsize;
		/// last segment
		_voidint lastsegment;
		/// segment size mask
		unsigned int smask;
		/// segment size level
		unsigned int slevel;
	};

	struct p_globalMemManager {
		MEMDEFAULT(p_globalMemManager)

		_FORCEINLINE p_globalMemManager() {};
		void* mManagersMapList; //MapVoid<memManager>
		memManager *fManagers[128];
	};

	memManagerExport::memManagerExport(unsigned int size)
	{
		if (fisVal!=VALIDED) {
			fargs=new p_smemManager();
			extFunctions.CleanMem(fargs,sizeof(p_smemManager));
			_calcsize(size);
			fisVal=VALIDED;
		}
	}

	memManagerExport::~memManagerExport() {
		_free();
		if (fisVal==VALIDED) delete fargs;
		fisVal=FREE;
		fargs=NULL;
	}

	void memManagerExport::_free() {
		if (fisVal!=VALIDED) return;
		for (unsigned int i=0;i<fargs->fsegmentscount;i++) extFunctions.DeleteMem((char*)fargs->fsegmentsval[i],0); //delete[] (char*)fargs->fsegmentsval[i];
		//for (unsigned int i=0;i<fargs->fsegmentsval.mCount;i++) std::free(*(char **)fargs->fsegmentsval._point(i));
		extFunctions.DeleteMem(fargs->fsegmentsval,0);
		if (fargs->fneedFree) extFunctions.DeleteMem(fargs->fneedFree,0);
		extFunctions.CleanMem(fargs,sizeof(p_smemManager));
	}

	void *memManagerExport::_addAlloc() {
		if (fargs->mAllCount>fargs->mCount) {
			//unsigned int idat=fargs->mCount;
			fargs->mCount++;
			//unsigned int idseg=_segid(idat);
			//return &(*(char **)fargs->fsegmentsval._point(idseg))[_valid(idat)*fargs->fsize];
			void *ret=(void *)fargs->lastsegment;
			fargs->lastsegment+=fargs->fsize;
			return ret;
		} else {
			fargs->mAllCount+=fargs->ssize;
			//fargs->lastsegment=(_voidint)new char[fargs->segmentsize+fargs->fmask];
			fargs->lastsegment=(_voidint)extFunctions.CreateMem(fargs->segmentsize+fargs->fmask,0);
			//char *vla=(char *)malloc(fargs->ssize*fargs->fsize);
			unsigned int lasts=extFunctions.ILogSize(MULSIZEOFVOID(fargs->fsegmentscount));
			unsigned int news=extFunctions.ILogSize(MULSIZEOFVOID(fargs->fsegmentscount+1));
			if (lasts!=news) {
				void **newsp=(void**)extFunctions.CreateMem(news,0);
				extFunctions.MoveMem(fargs->fsegmentsval,newsp,MULSIZEOFVOID(fargs->fsegmentscount));
				fargs->fsegmentsval=newsp;
			}
			fargs->fsegmentsval[fargs->fsegmentscount]=(void*)fargs->lastsegment;
			fargs->fsegmentscount++;
			if ((fargs->lastsegment & fargs->fmask)!=0)	fargs->lastsegment=(fargs->lastsegment+fargs->fmask+1) & (~fargs->fmask);
			//fargs->lastsegment=(void*)alignPointer((_voidint)fargs->lastsegment);
			return _addAlloc();
		}
	}

	void *memManagerExport::_getFree(unsigned int size) {
		if (fargs->fsize<size) return 0;
		char *p=0;
		if (fargs->mFreeCount>0) {
			unsigned int c=fargs->mFreeCount-1;
			p=(char *)fargs->fneedFree[c];
#ifdef THREADDEBUG
			assert(p!=0);
#endif
			fargs->fneedFree[c]=0;
			fargs->mFreeCount=c;
#ifdef _DEBUG
			extFunctions.StocBMem(p,fargs->fsize,0xCD);
#endif
		} else {
			p=(char*)_addAlloc();
		}
		return (void *)p;
	}

	void memManagerExport::_appendToFree(_voidint ivdat)
	{
#ifdef THREADDEBUG
		for (int i=0;i<fargs->mFreeCount;i++) assert(fargs->fneedFree[i]!=0);
#endif
		bool isfree=false;
		while (!isfree) {
			if (fargs->mAllCount-fargs->mCount<fargs->ssize) {
				_voidint ls=*(_voidint *)fargs->fsegmentsval[fargs->fsegmentscount-1];
				if ((ls & fargs->fmask)!=0)	ls=(ls+fargs->fmask+1) & (~fargs->fmask);
				_voidint d=fargs->lastsegment-fargs->fsize;
				if (d==ivdat && ls<=d) {
					fargs->lastsegment=d;
					fargs->mCount--;
					break;
				} else if (fargs->mFreeCount>0 && d==fargs->fneedFree[fargs->mFreeCount-1]) {
					fargs->mFreeCount--;
					fargs->lastsegment=d;
					fargs->mCount--;
				}
			}

			if (fargs->mAllFreeCount>fargs->mFreeCount) {
				fargs->fneedFree[fargs->mFreeCount]=ivdat;
				fargs->mFreeCount++;
#ifdef THREADDEBUG
				assert(fargs->fneedFree[fargs->mFreeCount-1]!=0);
#endif
				isfree=true;
			} else {
				//unsigned int allsize=fargs->mAllFreeCount;
				if (fargs->mAllFreeCount==0) fargs->mAllFreeCount=16;
				fargs->mAllFreeCount*=2;
				_voidint *nFree = (_voidint *)extFunctions.CreateMem(sizeof(_voidint)*fargs->mAllFreeCount, 0);
				if (fargs->fneedFree) {
					extFunctions.MoveMem(fargs->fneedFree,nFree,MULSIZEOFVOID(fargs->mFreeCount));
					//for (unsigned int i=0;i<fargs->mFreeCount;i++) nFree[i]=fargs->fneedFree[i];
					extFunctions.DeleteMem( fargs->fneedFree,0);
#ifdef THREADDEBUG
					assert(nFree[fargs->mFreeCount-1]!=0);
#endif
				}
				fargs->fneedFree=nFree;
				//_appendToFree(ivdat);
			}
		}
	}

	void memManagerExport::_markFree(void* val) {
		unsigned int validsize=fargs->fsize*fargs->ssize;
		for (unsigned int i=0;i<fargs->fsegmentscount;i++) {
			_voidint ca=(_voidint)*(char**)fargs->fsegmentsval[i];
			_voidint cb=(_voidint)val;
			int ra=cb-ca;
			if ((ra>=0) && ((unsigned int)ra<validsize)) {
				unsigned int idat=ra/fargs->fsize+i*fargs->ssize;
				_appendToFree(idat);
				return;
			}
		}
	}

	unsigned int memManagerExport::_valid(unsigned int id)
	{
		return id & fargs->smask;
	}

	unsigned int memManagerExport::_segid(unsigned int id)
	{
		return id >> fargs->slevel;
	}

	void memManagerExport::_calcsize(unsigned int size)
	{
		unsigned int i=SEGMENT_ALIGN-1;
		//unsigned int olevel=matFunctions.ILog2(i);
		unsigned int olevel=0;
		while (i>0) {
			olevel++;
			i=i>>1;
		}
		if (olevel==0) olevel=1;
		_voidint mascalign=(1<<olevel)-1;
		if ((size & mascalign)!=0) size=(size+mascalign+1) & (~mascalign);
		fargs->fsize=size;
		fargs->fmask=mascalign;
		i=(SEGMENT_SIZE_MIN+(size-1))/size;
		if (i<SEGMENT_OBJECTS_MIN) i=SEGMENT_OBJECTS_MIN;
		//olevel=matFunctions.ILog2(i-1);
		olevel=0;
		i--;
		while (i>0) {
			olevel++;
			i=i>>1;
		}
		if (olevel==0) olevel=1;
		fargs->slevel=olevel;
		fargs->ssize=1<<fargs->slevel;
		fargs->smask=(1<<fargs->slevel)-1;
		fargs->segmentsize=fargs->ssize*fargs->fsize;
	}

	void _APICALL reallocMemManagerSortMap(void ** list,int size)
	{
		initFunc();
		if (!list) return;
		if (size<=0) return;
		unsigned int count=0;
		unsigned int lallok=0;
		unsigned int lsize=0;
		unsigned int nsize=MULSIZEOFVOID(size<<1)+4;
		unsigned int allocSize=extFunctions.ILogSize(nsize);
		if (*list) {
			count=**(unsigned int**)list;
			lsize=MULSIZEOFVOID(count<<1)+4;
			lallok=extFunctions.ILogSize(lsize);
		}
		if (lallok==allocSize) return;

		unsigned int fullsize=allocSize;
		char *l=(char *)extFunctions.CreateMem(fullsize,0);
		if (*list) {
			if (lsize>nsize) lsize=nsize;
			extFunctions.MoveMem(*list,l,lsize);
			if (fullsize-lsize>0) extFunctions.CleanMem(l+lsize,fullsize-lsize);
			extFunctions.DeleteMem(*list,0);
		} else {
			extFunctions.CleanMem(l,fullsize);
		}
		*list=l;
	}

	void ** _APICALL addMemManagerSortMap(void ** list,void *key,void *val)
	{
		if (!list) return 0;
		unsigned int count=0;
		unsigned int pos=0;
		char *p=(char*)*list;
		p+=4;
		MapMemElement *b=(MapMemElement *)p;
		_voidint skey=(_voidint)key;
		_voidint rkey=(_voidint)_voidintmax;
		if (*list) {
			count=**(unsigned int**)list;
			unsigned int a=count;
			unsigned int apos=0;

			while (apos<a) {
				pos=((apos+a)>>1);
				rkey=(_voidint)b[pos].key;
				if (skey==rkey) break;
				if (skey>rkey) {
					apos=pos+1;
				} else {
					a=pos;
				}
			}
			pos=a;
			if (pos<count) rkey=(_voidint)b[pos].key;
		}

		if (skey!=rkey || !*list) {
			count++;
			reallocMemManagerSortMap(list,count);
			**(unsigned int**)list=count;
			p=(char*)*list;
			p+=4;
			b=(MapMemElement *)p;
			while (count>pos+1) {
				count--;
				b[count].key=b[count-1].key;
				b[count].val=b[count-1].val;
			}
			b[pos].key=key;
			b[pos].val=val;
			return (void**)&b[pos].val;
		} else {
			return (void**)&b[pos].val;
		}
	}

	void _APICALL freeMemManagerSortMap(void ** list)
	{
		if (!list) return;
		if (*list) {
			//unsigned int *p=(unsigned int*)*list;
			//unsigned int count=*p;
			extFunctions.DeleteMem(*list, 0);
		}
		*list=0;
	}

	memManager ** _APICALL arrayMemManagerSortMap(void ** list)
	{
		if (!list) return 0;
		if (!*list) return 0;
		char *p=(char*)*list;
		p+=4;
		return (memManager**)p;
	}

	unsigned int _APICALL countMemManagerSortMap(void ** list)
	{
		if (!list) return 0;
		if (!*list) return 0;
		return **(unsigned int**)list;
	}

// ******************************************************************************

	void checklock(globalMemManager *c)
	{
		if (!c->isThread) return;
		_voidint idl=c->isThread();
#ifdef THREADDEBUG
		assert(idl!=0);
#endif
		while (idl==0 && c->lock());
		if (idl!=0) while (true) {
			while (c->lockId()!=idl) {
				c->canLeave()=idl;
			}
			if (c->lock()) break;
		}
		c->lock()=true;
	}

	void unlock(globalMemManager *c)
	{
		if (!c->isThread) return;
		c->lock()=false;
#ifdef THREADDEBUG
		assert(c->lockId()==c->isThread());
#endif
		c->canLeave()=0;
		c->lockId()=0;
	}

// **************************** globalMemManager ********************************

	globalMemManager::globalMemManager()
	{
		init();
	}

	globalMemManager::~globalMemManager()
	{
		if (fisVal==VALIDED) {
			memManager **it=arrayMemManagerSortMap(&fmanagers->mManagersMapList);
			unsigned int count=countMemManagerSortMap(&fmanagers->mManagersMapList);
			while (count>0) {
				it++;
				if (*it) delete *it;
				it++;
				count--;
			}
			freeMemManagerSortMap(&fmanagers->mManagersMapList);
			for (unsigned int i=0;i<128;i++)
				if (fmanagers->fManagers[i]) delete fmanagers->fManagers[i];
			delete fmanagers;
			fisVal=FREE;
		}
	}

	void globalMemManager::manage()
	{
		if (!lock()) if (lockId()==0 && canLeave()!=0) {
			if (!lock()) lock()=true;
			lockId()=canLeave();
		}
	}

	void* globalMemManager::getNew(unsigned int size)
	{
		checklock(this);
#ifdef MEMORYCPP
		return new char[size];
		unlock(this);
#else
		init();
		if (size==0) {
			unlock(this);
			return 0;
		}
		unsigned int fast=alignSize(size)>>olevel;
		memManager* mem;
		if (fast<128) {
			mem=fmanagers->fManagers[fast];
			if (!mem) {
				mem=new memManager(size);
				fmanagers->fManagers[fast]=mem;
			}
		} else {
			memManager**find=(memManager**)arrFunctions.MPFind(&fmanagers->mManagersMapList,(void*)(_voidint)fast);
			if (!find) {
				mem=new memManager(size);
				addMemManagerSortMap(&fmanagers->mManagersMapList,(void*)(_voidint)fast,mem);
			} else mem=*find;
		}
		void *p=mem->getNew(size);
		unlock(this);
		return p;
#endif
	}

	BT_API void* globalMemManager::getNewClean(unsigned int size)
	{
		void *p=getNew(size);
		extFunctions.CleanMem(p,size);
		return p;
	}

	void globalMemManager::freeThis(void*val,unsigned int size)
	{
		checklock(this);
#ifdef MEMORYCPP
		delete[] (char*)val;
		unlock(this);
#else
		init();
		if (size==0) {
			unlock(this);
			return;
		}
		unsigned int fast=alignSize(size)>>olevel;
		memManager* mem=0;
		if (fast<128) {
			mem=fmanagers->fManagers[fast];
		} else {
			memManager**find=(memManager**)arrFunctions.MPFind(&fmanagers->mManagersMapList,(void*)(_voidint)fast);
			if (find) mem=*find;
		}
#ifdef THREADDEBUG
		if (!mem) {
			assert(mem!=0);
			unlock(this);
			return;
		}
#endif
		mem->freeThis(val);
		unlock(this);
#endif
	}

	void* globalMemManager::cashalloc(unsigned int size)
	{
		checklock(this);
#ifdef MEMORYCPP
		return new char[size];
#else
		init();
		if (size==0) {
			unlock(this);
			return 0;
		}
		unsigned int fast=alignSize(size)>>olevel;
		memManager* mem;
		if (fast<128) {
			mem=fmanagers->fManagers[fast];
			if (!mem) {
				mem=new memManager(size);
				fmanagers->fManagers[fast]=mem;
			}
		} else {
			void * p=extFunctions.CreateMem(size,0);
			unlock(this);
			return p;
		}
		void *p=mem->getNew(size);
		unlock(this);
		return p;
#endif
	}

	void globalMemManager::cashfree(void* val,unsigned int size)
	{
		checklock(this);
#ifdef MEMORYCPP
		delete[] (char*)val;
#else
		init();
		if (size==0) {
			unlock(this);
			return;
		}
		unsigned int fast=alignSize(size)>>olevel;
		memManager* mem=0;
		if (fast<128) {
			mem=fmanagers->fManagers[fast];
		} else {
			//delete[] (char*)val;
			extFunctions.DeleteMem((char*)val,0);
			unlock(this);
			return;
		}
#ifdef THREADDEBUG
		if (!mem) {
			assert(mem!=0);
			unlock(this);
			return;
		}
#endif
		mem->freeThis(val);
		unlock(this);
#endif
	}

	unsigned int globalMemManager::alignSize(unsigned int  size)
	{
		unsigned int mascalign=(1<<olevel)-1;
		if ((size & mascalign)!=0) size=(size+mascalign+1) & (~mascalign);
		return size;
	}

	_voidint globalMemManager::alignPointer(_voidint p)
	{
		_voidint mascalign=(1<<olevel)-1;
		if ((p & mascalign)!=0) p=(p+mascalign+1) & (~mascalign);
		return p;
	}

	void globalMemManager::init()
	{
		initFunc();
		if (fisVal!=VALIDED) {
			fisVal=VALIDED;
			flock=false;
			isThread=0;
			flockid=0;
			fmanagers=new p_globalMemManager();
			fmanagers->mManagersMapList=0;
			olevel=0;
			unsigned int i=SEGMENT_ALIGN-1;
			//olevel=matFunctions.ILog2(i);
			while (i>0) {
				olevel++;
				i=i>>1;
			}
			if (olevel==0) olevel=1;
			extFunctions.CleanMem(fmanagers->fManagers,MULSIZEOFVOID(128));
			//for (unsigned int i=0;i<128;i++)
				//fmanagers->fManagers[i]=0;
		}
	}

	void globalMemManager::cleaner()
	{
		/*
		MapVoid<memManager>::iterator it=fmanagers->mManagers.begin();
		MapVoid<memManager>::iterator end=fmanagers->mManagers.end();
		while (it!=end) {
			if (it.value()) it.value()->cleaner();
			it++;
		}
		for (unsigned int i=0;i<128;i++)
			if (fmanagers->fManagers[i]) fmanagers->fManagers[i]->cleaner();
		*/
	}

	enum States {
		VALIDED = 0x011F1C01,
		FREE = 0
	};

	globalMemManager internalmemmanager;

}

OPTIMIZE_OFF;
WARNING_ENABLE;
