/*
 * baseclassarray.cpp
 *
 *  Created on: 29.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <bt.h>

#include "base\baseapi.h"

namespace bt {

WARNING_DISABLE;
OPTIMIZE_ON;

//*** BaseVectorArray ***

/*BaseVectorArray::BaseVectorArray(unsigned int size)
{
	mAllCount=0;
	mVals=0;
	mItSize=0;
	mCount=0;
	mItSize=size;
	//initFunc();
	mThs=(tfFASTCALL_int_FUNC_int)extFunctions.GetFastFCMulI(size);
}

BaseVectorArray::~BaseVectorArray()
{
	if (mVals) delete[] mVals;
	mVals=0;
	mItSize=0;
	mThs=0;
	mCount=0;
	mAllCount=0;
}

void BaseVectorArray::_free()
{
	delete[] mVals;
	mVals=0;
	mCount=0;
	mAllCount=0;
}

void BaseVectorArray::_clear()
{
	mCount=0;
}

void BaseVectorArray::_resize(unsigned int count)
{
	if (count>mAllCount) _realloc(count);
	if (count<mAllCount) _lowalloc(count);
	mCount=count;
}

void BaseVectorArray::_reserv(unsigned int count)
{
	if (count>mAllCount) _realloc(count);
	if (count<mAllCount) _lowalloc(count);
}

void BaseVectorArray::_realloc(unsigned int count)
{
	if (count>mAllCount) {
		if (mAllCount==0) mAllCount=2;
		mAllCount*=2;
		if (mAllCount<count) mAllCount=count;
		char *nVals=0;
		if (mThs) {
			nVals=new char[mThs(mAllCount)];
			if (mVals) extFunctions.MoveMem((void*)mVals,(void*)nVals,mThs(mCount));
		} else {
			nVals=new char[mAllCount*mItSize];
			if (mVals) extFunctions.MoveMem((void*)mVals,(void*)nVals,mCount*mItSize);
		}
		if (mVals) delete[] mVals;
		mVals=nVals;
	}
}

void BaseVectorArray::_lowalloc(unsigned int count)
{
	unsigned int nCount=64;
	while (count>nCount) nCount*=2;
	if (nCount!=mAllCount) {
		mAllCount=nCount;
		char *nVals=0;
		if (mThs) {
			nVals=new char[mThs(mAllCount)];
			if (mVals) extFunctions.MoveMem((void*)mVals,(void*)nVals,mThs(count));
		} else {
			nVals=new char[mAllCount*mItSize];
			if (mVals) extFunctions.MoveMem((void*)mVals,(void*)nVals,count*mItSize);
		}
		if (mVals) delete[] mVals;
		mVals=nVals;
	}
}

void BaseVectorArray::_assign(void *val)
{
	unsigned int nCount=mCount+1;
	_realloc(nCount);
	char *itt=mVals;
	if (mThs) {
		itt+=mThs(mCount);
	} else {
		itt+=mCount*mItSize;
	}
	extFunctions.MoveMem(val,itt,mItSize);
	mCount=nCount;
}

void BaseVectorArray::_del_last()
{
	if (mCount>0) {
		mCount--;
		_lowalloc(mCount);
	}
}

void * BaseVectorArray::_point(unsigned int id) const
{
	if (mThs) return (void*)&mVals[mThs(id)];
	return (void*)&mVals[id*mItSize];
}

void * BaseVectorArray::_last()
{
	int id=mCount-1;
	if (mThs) return (void*)&mVals[mThs(id)];
	return (void*)&mVals[id*mItSize];
}*/


//*** BaseVoidVector ***

/*BaseVoidVector::BaseVoidVector()
{
	mAllCount=0;
	mVals=0;
	mCount=0;
}

BaseVoidVector::~BaseVoidVector()
{
	if (mVals) delete[] mVals;
	mVals=0;
	mCount=0;
	mAllCount=0;
}

void BaseVoidVector::_free()
{
	delete[] mVals;
	mVals=0;
	mCount=0;
	mAllCount=0;
}

void BaseVoidVector::_clear()
{
	mCount=0;
}

void BaseVoidVector::_resize(unsigned int count)
{
	if (count>mAllCount) _realloc(count);
	if (count<mAllCount) _lowalloc(count);
	mCount=count;
}

void BaseVoidVector::_reserv(unsigned int count)
{
	if (count>mAllCount) _realloc(count);
	if (count<mAllCount) _lowalloc(count);
}

void BaseVoidVector::_realloc(unsigned int count)
{
	if (count>mAllCount) {
		if (mAllCount==0) mAllCount=2;
		mAllCount*=2;
		if (mAllCount<count) mAllCount=count;
		char *nVals=0;
		nVals=new char[MULSIZEOFVOID(mAllCount)];
		if (mVals) extFunctions.MoveMem((void*)mVals,(void*)nVals,MULSIZEOFVOID(mCount));
		if (mVals) delete[] mVals;
		mVals=(void**)nVals;
	}
}

void BaseVoidVector::_lowalloc(unsigned int count)
{
	unsigned int nCount=64;
	while (count>nCount) nCount*=2;
	if (nCount!=mAllCount) {
		mAllCount=nCount;
		char *nVals=0;
		nVals=new char[MULSIZEOFVOID(mAllCount)];
		if (mVals) extFunctions.MoveMem((void*)mVals,(void*)nVals,MULSIZEOFVOID(count));
		if (mVals) delete[] mVals;
		mVals=(void**)nVals;
	}
}

void BaseVoidVector::_assign(void *val)
{
	unsigned int nCount=mCount+1;
	_realloc(nCount);
	void **itt=mVals;
	itt+=mCount;
	*itt=(*(void**)val);
	mCount=nCount;
}

void BaseVoidVector::_del_last()
{
	if (mCount>0) {
		mCount--;
		_lowalloc(mCount);
	}
}

void * BaseVoidVector::_point(unsigned int id) const
{
	return (void*)&mVals[id];
}

void * BaseVoidVector::_last()
{
	return (void*)&mVals[mCount-1];
}*/

//********************************** BaseHashVector ************************************

BaseHashVector::BaseHashVector(unsigned int size)
{
	mAllCount=0;
	mVals=0;
	mItSize=0;
	mCount=0;
	mItSize=size;
	initFunc();
	mThs=(tfFASTCALL_int_FUNC_int)extFunctions.GetFastFCMulI(size);
	mHashLevel=0;
	mHashedC=0;
	_realloc(0);
}

BaseHashVector::~BaseHashVector()
{
	if (mVals) internalmemmanager.freeThis((char*)mVals,mAllCount*mItSize);
	if (mHashedC) extFunctions.DeleteMem(mHashedC,0);
	mVals=0;
	mItSize=0;
	mThs=0;
	mCount=0;
	mAllCount=0;
	mHashLevel=0;
	mHashedC=0;
}

void BaseHashVector::_assign(void *val)
{
	_realloc(mCount+1);
	_addHash(val);
}

int BaseHashVector::_find(void *val)
{
	if (!mVals) return -1;
	char *itt=(char *)mVals;
	unsigned int hi=_hash(val);
	unsigned int id=0;
	unsigned int i=0;
	while (i<hi) {id+=mHashedC[i];i++;}
	unsigned int count=id+mHashedC[hi];
	if (mThs) {
		while ((extFunctions.CmpMem(&itt[mThs(id)],val,mItSize)!=-1) && (id<count)) id++;
	} else {
		while ((extFunctions.CmpMem(&itt[id*mItSize],val,mItSize)!=-1) && (id<count)) id++;
	}
	if (id>=count) return -1;
	return id;
}

int BaseHashVector::_del(void *val)
{
	if (!mVals) return -1;
	char *itt=(char *)mVals;
	unsigned int hi=_hash(val);
	unsigned int id=0;
	unsigned int i=0;
	while (i<hi) {id+=mHashedC[i];i++;}
	unsigned int count=id+mHashedC[hi];
	if (mThs) {
		while ((extFunctions.CmpMem(&itt[mThs(id)],val,mItSize)!=-1) && (id<count)) id++;
	} else {
		while ((extFunctions.CmpMem(&itt[id*mItSize],val,mItSize)!=-1) && (id<count)) id++;
	}
	if (id>=count) return -1;
	_removeAt(id);
	return id;
}

void * BaseHashVector::_point(unsigned int id) const
{
	if (!mVals) return 0;
	if (mThs)
		return (void*)&mVals[mThs(id)];
	return (void*)&mVals[id*mItSize];
}

bool BaseHashVector::_removeAt(unsigned int _id)
{
	char *itt=(char *)mVals;
	unsigned int hi=_hash(&mVals[_id*mItSize]);
	unsigned int id=0;
	for (unsigned int i=0;i<hi;i++) id+=mHashedC[i];
	unsigned int nid=id;
	unsigned int lid=id;
	if (_id-lid>=mHashedC[hi]) return false;
	nid+=mHashedC[hi]-1;
	if (mThs) {
		extFunctions.MoveMem(&itt[mThs(nid)],&itt[mThs(_id)],mItSize);
		for (unsigned int i=hi+1;i<mHashLevel;i++) {
			lid=nid;
			nid+=mHashedC[i];
			if (lid!=nid) extFunctions.MoveMem(&itt[mThs(nid)],&itt[mThs(lid)],mItSize);
		}
	} else {
		extFunctions.MoveMem(&itt[nid*mItSize],&itt[_id*mItSize],mItSize);
		for (unsigned int i=hi+1;i<mHashLevel;i++) {
			lid=nid;
			nid+=mHashedC[i];
			if (lid!=nid) extFunctions.MoveMem(&itt[nid*mItSize],&itt[lid*mItSize],mItSize);
		}
	}
	mHashedC[hi]--;
	mCount--;
	return true;
}

void BaseHashVector::_clear()
{
	if (mVals) internalmemmanager.freeThis((char*)mVals,mAllCount*mItSize);
	extFunctions.DeleteMem(mHashedC,0);
	mHashedC=0;
	mHashLevel=0;
	mVals=0;
	mCount=0;
	mAllCount=0;
}

void BaseHashVector::_realloc(unsigned int count)
{
	if (count>mAllCount) {
		int lastCount=mAllCount;
		if (mAllCount==0) mAllCount=2;
		mAllCount*=2;
		if (mAllCount<count) mAllCount=count;
		char *nVals;
		if (mThs) {
			nVals=(char*)internalmemmanager.getNew(mThs(mAllCount));
			if (mVals) extFunctions.MoveMem((void*)mVals,(void*)nVals,mThs(mCount));
			if (mVals) internalmemmanager.freeThis((char*)mVals,mThs(lastCount));
		} else {
			nVals=(char*)internalmemmanager.getNew(mAllCount*mItSize);
			if (mVals) extFunctions.MoveMem((void*)mVals,(void*)nVals,mCount*mItSize);
			if (mVals) internalmemmanager.freeThis((char*)mVals,lastCount*mItSize);
		}
		mVals=nVals;
	}
	unsigned int nHL=mHashLevel;
	while (mAllCount>nHL*nHL) {
		if (nHL==0) nHL=1;
		nHL*=2;
	}
	_setHashLevel(nHL);
}

unsigned char BaseHashVector::_hash(void *_val)
{
	unsigned int i=mItSize>>2;
	int *c=(int*)_val;
	int hash=0;
	while (i>0) {hash^=*c;c++;i--;}
	return (hash ^ (hash>>16)) & (mHashLevel-1);
}

void BaseHashVector::_addHash(void * _val)
{
	char *itt=(char *)mVals;
	unsigned int hi=_hash(_val);
	unsigned int lid=mCount;
	unsigned int nid=mCount;
	if (mThs) {
		for (unsigned int i=mHashLevel-1;i>hi;i--) {
			lid=nid;
			nid-=mHashedC[i];
			if (lid!=nid) extFunctions.MoveMem(&itt[mThs(nid)],&itt[mThs(lid)],mItSize);
		}
	} else {
		for (unsigned int i=mHashLevel-1;i>hi;i--) {
			lid=nid;
			nid-=mHashedC[i];
			if (lid!=nid) extFunctions.MoveMem(&itt[nid*mItSize],&itt[lid*mItSize],mItSize);
		}
	}
	mCount++;
	mHashedC[hi]++;
	if (mThs) {
		extFunctions.MoveMem(_val,&itt[mThs(nid)],mItSize);
	} else {
		extFunctions.MoveMem(_val,&itt[nid*mItSize],mItSize);
	}
}

void BaseHashVector::_delHash(void *_val)
{
	char *itt=(char *)mVals;
	unsigned int hi=_hash(_val);
	unsigned int id=0;
	for (unsigned int i=0;i<hi;i++) id+=mHashedC[i];
	unsigned int nid=id;
	unsigned int lid=id;
	if (mThs) {
		while ((extFunctions.CmpMem(&itt[mThs(id)],_val,mItSize)!=-1) && (id-lid<mHashedC[hi])) id++;
	} else {
		while ((extFunctions.CmpMem(&itt[id*mItSize],_val,mItSize)!=-1) && (id-lid<mHashedC[hi])) id++;
	}
	if (id-lid>=mHashedC[hi]) return;
	nid+=mHashedC[hi]-1;
	if (mThs) {
		extFunctions.MoveMem(&itt[mThs(nid)],&itt[mThs(id)],mItSize);
		for (unsigned int i=hi+1;i<mHashLevel;i++) {
			lid=nid;
			nid+=mHashedC[i];
			if (lid!=nid) extFunctions.MoveMem(&itt[mThs(nid)],&itt[mThs(lid)],mItSize);
		}
	} else {
		extFunctions.MoveMem(&itt[nid*mItSize],&itt[id*mItSize],mItSize);
		for (unsigned int i=hi+1;i<mHashLevel;i++) {
			lid=nid;
			nid+=mHashedC[i];
			if (lid!=nid) extFunctions.MoveMem(&itt[nid*mItSize],&itt[lid*mItSize],mItSize);
		}
	}
	mHashedC[hi]--;
	mCount--;
}

void BaseHashVector::_swap(int _aid,int _bid)
{
	char *itt=(char *)mVals;
	//char *a=new char[mItSize];
	int ida=_aid*mItSize;
	int idb=_bid*mItSize;
//	extFunctions.MoveMem(&itt[ida],a,mItSize);
//	extFunctions.MoveMem(&itt[idb],&itt[ida],mItSize);
//	extFunctions.MoveMem(a,&itt[idb],mItSize);
	extFunctions.SwapMem(&itt[ida],&itt[idb],mItSize);
	//delete[] a;
}

void BaseHashVector::_setHashLevel(unsigned int _level)
{
	char *itt=(char *)mVals;
	if (mHashLevel==_level) return;
	if (mHashedC) extFunctions.DeleteMem(mHashedC,0);
	mHashLevel=_level;
	mHashedC = (unsigned int *)extFunctions.CreateMem(mHashLevel*sizeof(int),0);
	for (unsigned int i=0;i<mHashLevel;i++) mHashedC[i]=0;

	if (mCount>0) {
		char *nVals=mVals;
		mVals=(char*)internalmemmanager.getNew(mAllCount*mItSize);
		
		unsigned int nCount=mCount;
		mCount=0;
		for (unsigned int i=0;i<nCount;i++) {
			_addHash(&itt[i*mItSize]);
		}
		if (nVals) internalmemmanager.freeThis((char*)nVals,mAllCount*mItSize);
	}
}

void BaseHashVector::_moveToNew(BaseHashVector* a)
{
	*a=*this;
	mHashedC=0;
	mHashLevel=0;
	mVals=0;
	mCount=0;
	mAllCount=0;
}

//********************************** BaseHashMap ************************************

BaseHashMap::BaseHashMap(unsigned int size,unsigned int vsize)
{
	mAllCount=0;
	mVals=0;
	mItSize=0;
	mCount=0;
	mItSize=size+vsize;
	mKeySize=size;
	initFunc();
	mThs=(tfFASTCALL_int_FUNC_int)extFunctions.GetFastFCMulI(mItSize);
	mHashLevel=0;
	mHashedC=0;
	_realloc(0);
}

BaseHashMap::~BaseHashMap()
{
	if (mVals) extFunctions.DeleteMem(mVals,0);
	if (mHashedC) extFunctions.DeleteMem(mHashedC,0);
	mVals=0;
	mItSize=0;
	mKeySize=0;
	mThs=0;
	mCount=0;
	mAllCount=0;
	mHashLevel=0;
	mHashedC=0;
}

void BaseHashMap::_assign(void *key,void *val)
{
	_realloc(mCount+1);
	_addHash(key,val);
}

int BaseHashMap::_find(void *key)
{
	if (!mVals) return -1;
	char *itt=(char *)mVals;
	unsigned int hi=_hash(key);
	unsigned int id=0;
	unsigned int i=0;
	while (i<hi) {id+=mHashedC[i];i++;}
	unsigned int count=id+mHashedC[hi];
	if (mThs) {
		while ((extFunctions.CmpMem(&itt[mThs(id)],key,mKeySize)!=-1) && (id<count)) id++;
	} else {
		while ((extFunctions.CmpMem(&itt[id*mItSize],key,mKeySize)!=-1) && (id<count)) id++;
	}
	if (id>=count) return -1;
	return id;
}

int BaseHashMap::_del(void *key)
{
	if (!mVals) return -1;
	char *itt=(char *)mVals;
	unsigned int hi=_hash(key);
	unsigned int id=0;
	unsigned int i=0;
	while (i<hi) {id+=mHashedC[i];i++;}
	unsigned int count=id+mHashedC[hi];
	if (mThs) {
		while ((extFunctions.CmpMem(&itt[mThs(id)],key,mKeySize)!=-1) && (id<count)) id++;
	} else {
		while ((extFunctions.CmpMem(&itt[id*mItSize],key,mKeySize)!=-1) && (id<count)) id++;
	}
	if (id>=count) return -1;
	_removeAt(id);
	return id;
}

void * BaseHashMap::_point(unsigned int id) const
{
	if (!mVals) return 0;
	if (mThs)
		return (void*)&mVals[mThs(id)];
	return (void*)&mVals[id*mItSize];
}

void * BaseHashMap::_val(unsigned int id) const
{
	if (!mVals) return 0;
	if (mThs)
		return (void*)&mVals[mThs(id)+mKeySize];
	return (void*)&mVals[id*mItSize+mKeySize];
}

bool BaseHashMap::_removeAt(unsigned int _id)
{
	char *itt=(char *)mVals;
	unsigned int hi=_hash(&mVals[_id*mItSize]);
	unsigned int id=0;
	for (unsigned int i=0;i<hi;i++) id+=mHashedC[i];
	unsigned int nid=id;
	unsigned int lid=id;
	if (_id-lid>=mHashedC[hi]) return false;
	nid+=mHashedC[hi]-1;
	if (mThs) {
		extFunctions.MoveMem(&itt[mThs(nid)],&itt[mThs(_id)],mItSize);
		for (unsigned int i=hi+1;i<mHashLevel;i++) {
			lid=nid;
			nid+=mHashedC[i];
			if (lid!=nid) extFunctions.MoveMem(&itt[mThs(nid)],&itt[mThs(lid)],mItSize);
		}
	} else {
		extFunctions.MoveMem(&itt[nid*mItSize],&itt[_id*mItSize],mItSize);
		for (unsigned int i=hi+1;i<mHashLevel;i++) {
			lid=nid;
			nid+=mHashedC[i];
			if (lid!=nid) extFunctions.MoveMem(&itt[nid*mItSize],&itt[lid*mItSize],mItSize);
		}
	}
	mHashedC[hi]--;
	mCount--;
	return true;
}

void BaseHashMap::_clear()
{
	extFunctions.DeleteMem(mVals,0);
	extFunctions.DeleteMem(mHashedC, 0);
	mHashedC=0;
	mHashLevel=0;
	mVals=0;
	mCount=0;
	mAllCount=0;
}

void BaseHashMap::_realloc(unsigned int count)
{
	if (count>mAllCount) {
		if (mAllCount==0) mAllCount=2;
		mAllCount*=2;
		if (mAllCount<count) mAllCount=count;
		char *nVals = (char*)extFunctions.CreateMem(mAllCount*mItSize,0);
		if (mVals) extFunctions.MoveMem((void*)mVals,(void*)nVals,mCount*mItSize);
		extFunctions.DeleteMem(mVals, 0);
		mVals=nVals;
	}
	unsigned int nHL=mHashLevel;
	while (mAllCount>nHL*nHL) {
		if (nHL==0) nHL=1;
		nHL*=2;
	}
	_setHashLevel(nHL);
}

unsigned char BaseHashMap::_hash(void *_key)
{
	unsigned int i=mKeySize>>2;
	int *c=(int*)_key;
	int hash=0;
	while (i>0) {hash^=*c;c++;i--;}
	return (hash ^ (hash>>16)) & (mHashLevel-1);
}

void BaseHashMap::_addHash(void * _key,void *_val)
{
	char *itt=(char *)mVals;
	unsigned int hi=_hash(_key);
	unsigned int lid=mCount;
	unsigned int nid=mCount;
	if (mThs) {
		for (unsigned int i=mHashLevel-1;i>hi;i--) {
			lid=nid;
			nid-=mHashedC[i];
			if (lid!=nid) extFunctions.MoveMem(&itt[mThs(nid)],&itt[mThs(lid)],mItSize);
		}
	} else {
		for (unsigned int i=mHashLevel-1;i>hi;i--) {
			lid=nid;
			nid-=mHashedC[i];
			if (lid!=nid) extFunctions.MoveMem(&itt[nid*mItSize],&itt[lid*mItSize],mItSize);
		}
	}
	mCount++;
	mHashedC[hi]++;
	if (mThs) {
		extFunctions.MoveMem(_key,&itt[mThs(nid)],mKeySize);
		extFunctions.MoveMem(_val,&itt[mThs(nid)+mKeySize],mItSize-mKeySize);
	} else {
		extFunctions.MoveMem(_key,&itt[nid*mItSize],mKeySize);
		extFunctions.MoveMem(_val,&itt[nid*mItSize+mKeySize],mItSize-mKeySize);
	}
}

void BaseHashMap::_delHash(void *_key)
{
	char *itt=(char *)mVals;
	unsigned int hi=_hash(_key);
	unsigned int id=0;
	for (unsigned int i=0;i<hi;i++) id+=mHashedC[i];
	unsigned int nid=id;
	unsigned int lid=id;
	if (mThs) {
		while ((extFunctions.CmpMem(&itt[mThs(id)],_key,mKeySize)!=-1) && (id-lid<mHashedC[hi])) id++;
	} else {
		while ((extFunctions.CmpMem(&itt[id*mItSize],_key,mKeySize)!=-1) && (id-lid<mHashedC[hi])) id++;
	}
	if (id-lid>=mHashedC[hi]) return;
	nid+=mHashedC[hi]-1;
	if (mThs) {
		extFunctions.MoveMem(&itt[mThs(nid)],&itt[mThs(id)],mItSize);
		for (unsigned int i=hi+1;i<mHashLevel;i++) {
			lid=nid;
			nid+=mHashedC[i];
			if (lid!=nid) extFunctions.MoveMem(&itt[mThs(nid)],&itt[mThs(lid)],mItSize);
		}
	} else {
		extFunctions.MoveMem(&itt[nid*mItSize],&itt[id*mItSize],mItSize);
		for (unsigned int i=hi+1;i<mHashLevel;i++) {
			lid=nid;
			nid+=mHashedC[i];
			if (lid!=nid) extFunctions.MoveMem(&itt[nid*mItSize],&itt[lid*mItSize],mItSize);
		}
	}
	mHashedC[hi]--;
	mCount--;
}

void BaseHashMap::_swap(int _aid,int _bid)
{
	char *itt=(char *)mVals;
	char *a = (char*)extFunctions.CreateMem(mItSize, 0);
	int ida=_aid*mItSize;
	int idb=_bid*mItSize;
	extFunctions.MoveMem(&itt[ida],a,mItSize);
	extFunctions.MoveMem(&itt[idb],&itt[ida],mItSize);
	extFunctions.MoveMem(a,&itt[idb],mItSize);
	extFunctions.DeleteMem( a,0);
}

void BaseHashMap::_setHashLevel(unsigned int _level)
{
	char *itt=(char *)mVals;
	if (mHashLevel==_level) return;
	if (mHashedC) extFunctions.DeleteMem(mHashedC, 0);
	mHashLevel=_level;
	mHashedC = (unsigned int*)extFunctions.CreateMem(mHashLevel*sizeof(int),0);
	for (unsigned int i=0;i<mHashLevel;i++) mHashedC[i]=0;

	if (mCount>0) {
		char *nVals=mVals;
		mVals=(char*)extFunctions.CreateMem(mAllCount*mItSize,0);
		unsigned int nCount=mCount;
		mCount=0;
		for (unsigned int i=0;i<nCount;i++) {
			_addHash(&itt[i*mItSize],&itt[i*mItSize+mKeySize]);
		}
		extFunctions.DeleteMem(nVals,0);
	}
}

void BaseHashMap::_moveToNew(BaseHashMap* a)
{
	*a=*this;
	mHashedC=0;
	mHashLevel=0;
	mVals=0;
	mCount=0;
	mAllCount=0;
}

//********************************** BaseHashVoidMap ************************************

BaseHashVoidMap::BaseHashVoidMap()
{
	mAllCount=0;
	mVals=0;
	mCount=0;
	mHashLevel=0;
	mHashedC=0;
	_realloc(0);
}

BaseHashVoidMap::~BaseHashVoidMap()
{
	if (mVals) extFunctions.DeleteMem( mVals,0);
	if (mHashedC) extFunctions.DeleteMem( mHashedC, 0);
	mVals=0;
	mCount=0;
	mAllCount=0;
	mHashLevel=0;
	mHashedC=0;
}

BaseHashVoidMap::iterator BaseHashVoidMap::begin()
{
	char *itt=(char *)mVals;
	return iterator(itt);
}

BaseHashVoidMap::iterator BaseHashVoidMap::end()
{
	char *itt=(char *)mVals;
	return iterator(&itt[MULSIZEOFVOID(mCount)<<1]);
}

void BaseHashVoidMap::_assign(void *key,void *val)
{
	_realloc(mCount+1);
	_addHash(key,val);
}

int BaseHashVoidMap::_find(void *key)
{
	if (!mVals) return -1;
	char *itt=(char *)mVals;
	unsigned int hi=_hash(key);
	unsigned int id=0;
	unsigned int i=0;
	while (i<hi) {id+=mHashedC[i];i++;}
	unsigned int count=id+mHashedC[hi];
	while (((*(void**)&itt[MULSIZEOFVOID(id)<<1])!=key) && (id<count)) id++;
	if (id>=count) return -1;
	return id;
}

int BaseHashVoidMap::_del(void *key)
{
	if (!mVals) return -1;
	char *itt=(char *)mVals;
	unsigned int hi=_hash(key);
	unsigned int id=0;
	unsigned int i=0;
	while (i<hi) {id+=mHashedC[i];i++;}
	unsigned int count=id+mHashedC[hi];
	while (((*(void**)&itt[MULSIZEOFVOID(id)<<1])!=*((void**)key)) && (id<count)) id++;
	if (id>=count) return -1;
	_removeAt(id);
	return id;
}

void * BaseHashVoidMap::_point(unsigned int id) const
{
	if (!mVals) return 0;
	return (void*)&mVals[id<<3];
}

void * BaseHashVoidMap::_val(unsigned int id) const
{
	if (!mVals) return 0;
	return (void*)&mVals[(id<<3)+4];
}

bool BaseHashVoidMap::_removeAt(unsigned int _id)
{
	char *itt=(char *)mVals;
	unsigned int hi=_hash(&mVals[MULSIZEOFVOID(_id)<<1]);
	unsigned int id=0;
	for (unsigned int i=0;i<hi;i++) id+=mHashedC[i];
	unsigned int nid=id;
	unsigned int lid=id;
	if (_id-lid>=mHashedC[hi]) return false;
	nid+=mHashedC[hi]-1;
	extFunctions.MoveMem(&itt[MULSIZEOFVOID(nid)<<1],&itt[MULSIZEOFVOID(_id)<<1],8);
	for (unsigned int i=hi+1;i<mHashLevel;i++) {
		lid=nid;
		nid+=mHashedC[i];
		if (lid!=nid) {
			(*(void**)&itt[MULSIZEOFVOID(lid)<<1])=*(void**)&itt[MULSIZEOFVOID(nid)<<1];
			(*(void**)&itt[(MULSIZEOFVOID(lid)<<1)+4])=*(void**)&itt[(MULSIZEOFVOID(nid)<<1)+4];
		}
	}
	mHashedC[hi]--;
	mCount--;
	return true;
}

void BaseHashVoidMap::_clear()
{
	extFunctions.DeleteMem( mVals,0);
	extFunctions.DeleteMem( mHashedC,0);
	mHashedC=0;
	mHashLevel=0;
	mVals=0;
	mCount=0;
	mAllCount=0;
}

void BaseHashVoidMap::_realloc(unsigned int count)
{
	if (count>mAllCount) {
		if (mAllCount==0) mAllCount=2;
		mAllCount*=2;
		if (mAllCount<count) mAllCount=count;
		char *nVals = (char*)extFunctions.CreateMem(MULSIZEOFVOID(mAllCount) << 1,0);
		if (mVals) extFunctions.MoveMem((void*)mVals,(void*)nVals,MULSIZEOFVOID(mCount)<<1);
		extFunctions.DeleteMem( mVals,0);
		mVals=nVals;
	}
	unsigned int nHL=mHashLevel;
	while (mAllCount>nHL*nHL) {
		if (nHL==0) nHL=1;
		nHL*=2;
	}
	_setHashLevel(nHL);
}

unsigned char BaseHashVoidMap::_hash(void *_key)
{
	_voidint *c=(_voidint*)_key;
	return (*c ^ (*c>>16)) & (mHashLevel-1);
}

void BaseHashVoidMap::_addHash(void * _key,void *_val)
{
	char *itt=(char *)mVals;
	unsigned int hi=_hash(_key);
	unsigned int lid=mCount;
	unsigned int nid=mCount;
	for (unsigned int i=mHashLevel-1;i>hi;i--) {
		lid=nid;
		nid-=mHashedC[i];
		if (lid!=nid) {
			(*(void**)&itt[MULSIZEOFVOID(lid)<<1])=*(void**)&itt[MULSIZEOFVOID(nid)<<1];
			(*(void**)&itt[(MULSIZEOFVOID(lid)<<1)+4])=*(void**)&itt[(MULSIZEOFVOID(nid)<<1)+4];
		}
	}
	mCount++;
	mHashedC[hi]++;
	(*(void**)&itt[MULSIZEOFVOID(nid)<<1])=*(void**)_key;
	(*(void**)&itt[(MULSIZEOFVOID(nid)<<1)+4])=*(void**)_val;
}

void BaseHashVoidMap::_delHash(void *_key)
{
	char *itt=(char *)mVals;
	unsigned int hi=_hash(_key);
	unsigned int id=0;
	for (unsigned int i=0;i<hi;i++) id+=mHashedC[i];
	unsigned int nid=id;
	unsigned int lid=id;
	while (((*(void**)&itt[id<<3])!=*((void**)_key)) && (id<mHashedC[hi])) id++;
	if (id-lid>=mHashedC[hi]) return;
	nid+=mHashedC[hi]-1;
	extFunctions.MoveMem(&itt[MULSIZEOFVOID(nid)<<1],&itt[MULSIZEOFVOID(id)<<1],8);
	for (unsigned int i=hi+1;i<mHashLevel;i++) {
		lid=nid;
		nid+=mHashedC[i];
		if (lid!=nid) {
			(*(void**)&itt[MULSIZEOFVOID(lid)<<1])=*(void**)&itt[MULSIZEOFVOID(nid)<<1];
			(*(void**)&itt[(MULSIZEOFVOID(lid)<<1)+4])=*(void**)&itt[(MULSIZEOFVOID(id)<<1)+4];
		}
	}
	mHashedC[hi]--;
	mCount--;
}

void BaseHashVoidMap::_swap(int _aid,int _bid)
{
	char *itt=(char *)mVals;
	char a[8];
	int ida=_aid<<3;
	int idb=_bid<<3;
	extFunctions.MoveMem(&itt[ida],a,8);
	extFunctions.MoveMem(&itt[idb],&itt[ida],8);
	extFunctions.MoveMem(a,&itt[idb],8);
}

void BaseHashVoidMap::_setHashLevel(unsigned int _level)
{
	char *itt=(char *)mVals;
	if (mHashLevel==_level) return;
	if (mHashedC) extFunctions.DeleteMem(mHashedC,0);
	mHashLevel=_level;
	mHashedC = (unsigned int*)extFunctions.CreateMem(sizeof(unsigned int)*mHashLevel,0);
	for (unsigned int i=0;i<mHashLevel;i++) mHashedC[i]=0;

	if (mCount>0) {
		char *nVals=mVals;
		mVals = (char*)extFunctions.CreateMem(MULSIZEOFVOID(mAllCount) << 1,0);
		unsigned int nCount=mCount;
		mCount=0;
		for (unsigned int i=0;i<nCount;i++) {
			_addHash(&itt[MULSIZEOFVOID(i)<<1],&itt[(MULSIZEOFVOID(i)<<1)+4]);
		}
		extFunctions.DeleteMem(nVals,0);
	}
}

void BaseHashVoidMap::_moveToNew(BaseHashVoidMap* a)
{
	*a=*this;
	mHashedC=0;
	mHashLevel=0;
	mVals=0;
	mCount=0;
	mAllCount=0;
}

BaseHashVoidMap::iterator::iterator(void*val)
{
	mIterator=val;
}

BaseHashVoidMap::iterator::~iterator()
{
}

void *BaseHashVoidMap::iterator::key()
{
	void **itt=(void **)mIterator;
	return itt[0];
}

void *BaseHashVoidMap::iterator::value()
{
	void **itt=(void **)mIterator;
	return itt[1];
}

BaseHashVoidMap::iterator& BaseHashVoidMap::iterator::operator++(int)
{
	void **itt=(void **)mIterator;
	itt++;
	itt++;
	mIterator=(void *)itt;
	return *this;
}

bool BaseHashVoidMap::iterator::operator==(const BaseHashVoidMap::iterator& _Right)
{
	return mIterator==_Right.mIterator;
}

bool BaseHashVoidMap::iterator::operator!=(const BaseHashVoidMap::iterator& _Right)
{
	return !(mIterator==_Right.mIterator);
}

//************************************************ BaseMapName **********************************

/*typedef std::map<std::string,void*> MapNamePointer;

class MapNameIterator:public MapNamePointer::iterator {
public:
	_FORCEINLINE MapNameIterator(void *ptr,void *data) {
		*(void**)&_Ptr=ptr;
#if defined (OS_WIN)
		_Adopt((MapNamePointer*)data);
#endif
	}
	_FORCEINLINE ~MapNameIterator() {}

	_FORCEINLINE value_type &val() {return _Ptr->_Myval;}

	_FORCEINLINE void setPtr( void *ptr) {*(void**)&_Ptr=ptr;}

	_FORCEINLINE void setData(void *ptr) {
#if defined (OS_QNX)
#elif defined (OS_WIN)
		_Adopt((MapNamePointer*)ptr);
#endif
	}
};

BaseMapName::BaseMapName()
{
	mData=new MapNamePointer();
}

BaseMapName::~BaseMapName()
{
	delete (MapNamePointer*)mData;
}

BaseMapName::iterator BaseMapName::begin()
{
	MapNamePointer::iterator it =((MapNamePointer*)mData)->begin();
	return BaseMapName::iterator(it._Mynode(),mData);
}

BaseMapName::iterator BaseMapName::end()
{
	MapNamePointer::iterator it =((MapNamePointer*)mData)->end();
	return BaseMapName::iterator(it._Mynode(),mData);
}

void BaseMapName::clear()
{
	((MapNamePointer*)mData)->clear();
}

unsigned int BaseMapName::count()
{
	return ((MapNamePointer*)mData)->size();
}

unsigned int BaseMapName::count(char* _key)
{
	return ((MapNamePointer*)mData)->count(_key);
}

unsigned int BaseMapName::count(const char* & _key)
{
	return ((MapNamePointer*)mData)->count(_key);
}

bool BaseMapName::contains(char* _key)
{
	return ((MapNamePointer*)mData)->find(_key)!=((MapNamePointer*)mData)->end();
}

bool BaseMapName::contains(const char* &_key)
{
	return ((MapNamePointer*)mData)->find(_key)!=((MapNamePointer*)mData)->end();
}

int BaseMapName::remove(char* _key)
{
	return ((MapNamePointer*)mData)->erase(_key);
}

int BaseMapName::remove(const char* & _key)
{
	return ((MapNamePointer*)mData)->erase(_key);
}

void *BaseMapName::_find(char* _key)
{
	return _find(_key,0);
}

void *BaseMapName::_find(const char * &_key)
{
	return _find((char*)_key,0);
}

void *BaseMapName::_find(char* _key,void * def)
{
	if (((MapNamePointer*)mData)->size()==0) return def;
	MapNamePointer::iterator it=((MapNamePointer*)mData)->find(_key);
	if (it!=((MapNamePointer*)mData)->end()) return it->second;
	return def;
}

void *BaseMapName::_find(const char * &_key,void * def)
{
	return _find((char*)_key,def);
}

const char * BaseMapName::_key(void *_val,const char * &_key)
{
	MapNamePointer::iterator it=((MapNamePointer*)mData)->begin();
	MapNamePointer::iterator end=((MapNamePointer*)mData)->end();
	while (it!=end) {
		if (it->second==_val) return it->first.c_str();
		it++;
	}
	return _key;
}

void *&BaseMapName::_findornew(char * _key)
{
	return (*((MapNamePointer*)mData))[_key];
}

void *&BaseMapName::_findornew(const char * & _key)
{
	return (*((MapNamePointer*)mData))[_key];
}

void* BaseMapName::_assign(void* _val,char *_key)
{
	(*((MapNamePointer*)mData))[_key]=_val;
	return _val;
}

void* BaseMapName::_assign(void* _val,const char * &_key)
{
	(*((MapNamePointer*)mData))[_key]=_val;
	return _val;
}

BaseMapName::iterator::iterator(void*val,void *v)
{
	mIterator=val;
	d=v;
}

BaseMapName::iterator::~iterator()
{
	//delete (MapNamePointer::iterator*)mIterator;
}

const char* BaseMapName::iterator::key()
{
	MapNameIterator r(mIterator,d);
	return r.val().first.c_str();
}

void* BaseMapName::iterator::value()
{
	MapNameIterator r(mIterator,d);
	return r.val().second;
}

BaseMapName::iterator& BaseMapName::iterator::operator++(int)
{
	MapNameIterator r(mIterator,d);
	r++;
	mIterator=r._Mynode();
	return *this;
}

bool BaseMapName::iterator::operator==(const BaseMapName::iterator& _Right)
{
	MapNameIterator r(_Right.mIterator,_Right.d);
	MapNameIterator l(mIterator,d);
	return l==r;
}

bool BaseMapName::iterator::operator!=(const BaseMapName::iterator& _Right)
{
	MapNameIterator r(_Right.mIterator,_Right.d);
	MapNameIterator l(mIterator,d);
	return !(l==r);
}*/

/*BaseMapName::BaseMapName()
{
	mData=0;
}

BaseMapName::~BaseMapName()
{
	arrFunctions.MSSPFree(&mData);
}

BaseMapName::iterator BaseMapName::begin()
{
	return BaseMapName::iterator((void*)arrFunctions.MPArray(&mData),mData);
}

BaseMapName::iterator BaseMapName::end()
{
	return BaseMapName::iterator((void*)&(((void**)arrFunctions.MPArray(&mData))[arrFunctions.MPCount(&mData)<<1]),mData);
}*/

/*void BaseMapName::clear()
{
	arrFunctions.MSSPFree(&mData);
}

void BaseMapName::free()
{
	arrFunctions.MSSPFree(&mData);
}

unsigned int BaseMapName::count()
{
	return arrFunctions.MPCount(&mData);
}*/

/*unsigned int BaseMapName::count(char* _key)
{
	//BaseShortString ks(_key);
	//if (arrFunctions.MSPFind(&mData,ks.mData)) return 1;
	if (arrFunctions.MSSPFind(&mData,_key)) return 1;
	return 0;
}

unsigned int BaseMapName::count(const char* & _key)
{
	//BaseShortString ks(_key);
	//if (arrFunctions.MSPFind(&mData,ks.mData)) return 1;
	//const char *k=_key;
	if (arrFunctions.MSSPFind(&mData, (void*)_key)) return 1;
	return 0;
}*/

/*bool BaseMapName::contains(char* _key)
{
	//BaseShortString ks(_key);
	//return arrFunctions.MSPFind(&mData,ks.mData)!=0;
	return arrFunctions.MSSPFind(&mData,_key)!=0;
}

bool BaseMapName::contains(const char* &_key)
{
	//BaseShortString ks(_key);
	//return arrFunctions.MSPFind(&mData,ks.mData)!=0;
	const char *k=_key;
	return arrFunctions.MSSPFind(&mData,(void*)k)!=0;
}*/

/*int BaseMapName::remove(char* _key)
{
	void *ks=0;
	arrFunctions.SSet(&ks,(void*)_key);
	void * km=arrFunctions.MSPRemove(&mData,ks);
	//void * km=removeStringSortMap(&mData,ks.mData);
	arrFunctions.SSet(&ks,0);
	if (km) {
		arrFunctions.SSet(&km,0);
		//*((BaseShortString*)&km)="";
		return 1;
	}
	return 0;
}

int BaseMapName::remove(const char* & _key)
{
	void *ks=0;
	arrFunctions.SSet(&ks,(void*)_key);
	void * km=arrFunctions.MSPRemove(&mData,ks);
	//void * km=removeStringSortMap(&mData,ks.mData);
	arrFunctions.SSet(&ks,0);
	if (km) {
		arrFunctions.SSet(&km,0);
		//*((BaseShortString*)&km)="";
		return 1;
	}
	return 0;
}*/

/*void *BaseMapName::_find(char* _key)
{
	//BaseShortString ks(_key);
	//void**val=(void**)arrFunctions.MSPFind(&mData,ks.mData);
	void**val=(void**)arrFunctions.MSSPFind(&mData,_key);
	if (val) return *val;
	return 0;
}

void *BaseMapName::_find(const char * &_key)
{
	//BaseShortString ks(_key);
	//void**val=(void**)arrFunctions.MSPFind(&mData,ks.mData);
	const char *k=_key;
	void**val=(void**)arrFunctions.MSSPFind(&mData,(void*)k);
	if (val) return *val;
	return 0;
}

void *BaseMapName::_find(char* _key,void * def)
{
	BaseShortString ks(_key);
	//void**val=(void**)arrFunctions.MSPFind(&mData,ks.mData);
	void**val=(void**)arrFunctions.MSSPFind(&mData,_key);
	if (val) return *val;
	return def;
}

void *BaseMapName::_find(const char * &_key,void * def)
{
	return _find((char*)_key,def);
}*/

/*const char * BaseMapName::_key(void *_val,const char * &_key)
{
	void** ar=(void**)arrFunctions.MPArray(&mData);
	unsigned int count=arrFunctions.MPCount(&mData);
	while (count>0) {
		if (ar[1]==_val) return ((char*)ar[0])+1;
		ar+=2;
		count--;
	}
	return _key;
}*/

/*void *&BaseMapName::_findornew(char * _key)
{
	//void *ks=0;
	//arrFunctions.SSet(&ks,(void*)_key);
	void **k = (void**)arrFunctions.MSSPAdd(&mData, _key, 0);
	//void **k=addStringSortMap(&mData,ks.mData,0);
	//if (*k!=ks) arrFunctions.SSet(&ks,0);
	return k[1];
}

void *&BaseMapName::_findornew(const char * & _key)
{
	//void *ks=0;
	//arrFunctions.SSet(&ks,(void*)_key);
	void **k=(void**)arrFunctions.MSSPAdd(&mData,(void*)_key,0);
	//void **k=addStringSortMap(&mData,ks.mData,0);
	//if (*k!=ks) arrFunctions.SSet(&ks,0);
	return k[1];
}

void* BaseMapName::_assign(void* _val,char *_key)
{
	//void *ks=0;
	//arrFunctions.SSet(&ks,(void*)_key);
	void **k=(void**)arrFunctions.MSSPAdd(&mData,_key,_val);
	//void **k=addStringSortMap(&mData,ks.mData,_val);
	//if (*k!=ks) arrFunctions.SSet(&ks,0);
	return _val;
}

void* BaseMapName::_assign(void* _val,const char * &_key)
{
	//void *ks=0;
	//arrFunctions.SSet(&ks,(void*)_key);
	void **k = (void**)arrFunctions.MSPAdd(&mData, (void*)_key, _val);
	//void **k=addStringSortMap(&mData,ks.mData,_val);
	//if (*k!=ks) arrFunctions.SSet(&ks,0);
	return _val;
}

BaseMapName::iterator::iterator(void*val,void *v)
{
	mIterator=val;
	d=v;
}

BaseMapName::iterator::iterator(const iterator &it)
{
	mIterator=it.mIterator;
	d=it.d;
}

BaseMapName::iterator::iterator(iterator &it)
{
	mIterator=it.mIterator;
	d=it.d;
}

BaseMapName::iterator::~iterator()
{
	//delete (MapNamePointer::iterator*)mIterator;
}

const char* BaseMapName::iterator::key()
{
	return (*(const char**)mIterator)+1;
}

void* BaseMapName::iterator::value()
{
	return ((void**)mIterator)[1];
}

BaseMapName::iterator& BaseMapName::iterator::operator++(int)
{
	void**r=(void**)mIterator;
	r+=2;
	mIterator=(void**)r;
	return *this;
}

bool BaseMapName::iterator::operator==(const BaseMapName::iterator& _Right)
{
	return mIterator==_Right.mIterator;
}

bool BaseMapName::iterator::operator!=(const BaseMapName::iterator& _Right)
{
	return !(mIterator==_Right.mIterator);
}*/

//******************************************** BaseMapVoid **************************************************

/*typedef std::map<void*,void*> MapVoidPointer;

class MapVoidIterator:public MapVoidPointer::iterator {
public:
	_FORCEINLINE MapVoidIterator(void *ptr,void *data) {
		*(void**)&_Ptr=ptr;
#if defined (OS_WIN)
		_Adopt((MapNamePointer*)data);
#endif
	}

	_FORCEINLINE ~MapVoidIterator() {}

	_FORCEINLINE value_type &val() {return _Ptr->_Myval;}

	_FORCEINLINE void setPtr( void *ptr) {*(void**)&_Ptr=ptr;}

	_FORCEINLINE void setData(void *ptr) {
#if defined (OS_QNX)
#elif defined (OS_WIN)
		_Adopt((MapNamePointer*)ptr);
#endif
	}
};

BaseMapVoid::BaseMapVoid()
{
	mData=new MapVoidPointer();
}

BaseMapVoid::~BaseMapVoid()
{
	delete (MapVoidPointer*)mData;
}

BaseMapVoid::iterator BaseMapVoid::begin()
{
	MapVoidPointer::iterator it =((MapVoidPointer*)mData)->begin();
	return BaseMapVoid::iterator(it._Mynode(),mData);
}

BaseMapVoid::iterator BaseMapVoid::end()
{
	MapVoidPointer::iterator it =((MapVoidPointer*)mData)->end();
	return BaseMapVoid::iterator(it._Mynode(),mData);
}

void BaseMapVoid::clear()
{
	((MapVoidPointer*)mData)->clear();
}

unsigned int BaseMapVoid::count()
{
	return ((MapVoidPointer*)mData)->size();
}

unsigned int BaseMapVoid::count(void* _key)
{
	return ((MapVoidPointer*)mData)->count(_key);
}

bool BaseMapVoid::contains(void* _key)
{
	return ((MapVoidPointer*)mData)->find(_key)!=((MapVoidPointer*)mData)->end();
}

int BaseMapVoid::remove(void* _key)
{
	return ((MapVoidPointer*)mData)->erase(_key);
}

void *BaseMapVoid::_find(void* _key)
{
	MapVoidPointer::iterator it=((MapVoidPointer*)mData)->find(_key);
	if (it!=((MapVoidPointer*)mData)->end()) return it->second;
	return 0;
}

void * BaseMapVoid::_key(void *_val,void * &_key)
{
	MapVoidPointer::iterator it=((MapVoidPointer*)mData)->begin();
	MapVoidPointer::iterator end=((MapVoidPointer*)mData)->end();
	while (it!=end) {
		if (it->second==_val) return it->first;
		it++;
	}
	return _key;
}

void *&BaseMapVoid::_findornew(void * _key)
{
	return (*((MapVoidPointer*)mData))[_key];
}

void* BaseMapVoid::_assign(void* _val,void *_key)
{
	(*((MapVoidPointer*)mData))[_key]=_val;
	return _val;
}

BaseMapVoid::iterator::iterator(void*val,void*v)
{
	mIterator=val;
	d=v;
}

BaseMapVoid::iterator::~iterator()
{
	//delete (BaseMapVoid::iterator*)mIterator;
}

void* BaseMapVoid::iterator::key()
{
	MapVoidIterator r(mIterator,d);
	return r.val().first;
}

void* BaseMapVoid::iterator::value()
{
	MapVoidIterator r(mIterator,d);
	return r.val().second;
}

BaseMapVoid::iterator& BaseMapVoid::iterator::operator++(int)
{
	MapVoidIterator r(mIterator,d);
	r++;
	mIterator=r._Mynode();
	return *this;
}

bool BaseMapVoid::iterator::operator==(const BaseMapVoid::iterator& _Right)
{
	MapVoidIterator r(_Right.mIterator,_Right.d);
	MapVoidIterator l(mIterator,d);
	return l==r;
}

bool BaseMapVoid::iterator::operator!=(const BaseMapVoid::iterator& _Right)
{
	MapVoidIterator r(_Right.mIterator,_Right.d);
	MapVoidIterator l(mIterator,d);
	return !(l==r);
}*/

/*BaseMapVoid::BaseMapVoid()
{
	mData=0;
}

BaseMapVoid::~BaseMapVoid()
{
	arrFunctions.MPFree(&mData);
	mData=0;
}*/

/*BaseMapVoid::iterator BaseMapVoid::begin()
{
	return BaseMapVoid::iterator((void*)arrFunctions.MPArray(&mData),mData);
}

BaseMapVoid::iterator BaseMapVoid::end()
{
	return BaseMapVoid::iterator((void*)&(((void**)arrFunctions.MPArray(&mData))[arrFunctions.MPCount(&mData)<<1]),mData);
}*/

/*void BaseMapVoid::clear()
{
	arrFunctions.MPFree(&mData);
}

unsigned int BaseMapVoid::count()
{
	return arrFunctions.MPCount(&mData);
}

unsigned int BaseMapVoid::count(void* )
{
	return 1;
}

bool BaseMapVoid::contains(void* _key)
{
	return arrFunctions.MPFind(&mData,_key)!=0;
}

void* BaseMapVoid::remove(void* _key)
{
	return arrFunctions.MPRemove(&mData,_key);
}

void *BaseMapVoid::_find(void* _key)
{
	void**c=(void**)arrFunctions.MPFind(&mData,_key);
	if (c) return *c;
	return 0;
}

void * BaseMapVoid::_key(void *_val,void * &_key)
{
	unsigned int count=arrFunctions.MPCount(&mData);
	void **arr=(void**)arrFunctions.MPArray(&mData);
	while (count>0) {
		if (arr[1]==_val) return arr[0];
		arr+=2;
		count--;
	}
	return _key;
}

void *&BaseMapVoid::_findornew(void * _key)
{
	//void **c=(void**)arrFunctions.MPFind(&mData,_key);
	//if (!c) c=(void**)arrFunctions.MPAdd(&mData,_key,0);
	void **c=(void**)arrFunctions.MPAdd(&mData,_key,0);
	return *c;
}

void* BaseMapVoid::_assign(void* _val,void *_key)
{
	arrFunctions.MPAdd(&mData,_key,_val);
	return _val;
}*/

/*BaseMapVoid::iterator::iterator(void*val,void*v)
{
	mIterator=val;
	d=v;
}

BaseMapVoid::iterator::iterator(const iterator &it)
{
	mIterator=it.mIterator;
	d=it.d;
}

BaseMapVoid::iterator::iterator(iterator &it)
{
	mIterator=it.mIterator;
	d=it.d;
}

BaseMapVoid::iterator::~iterator()
{
}

void* BaseMapVoid::iterator::key()
{
	return *(void**)mIterator;
}

void* BaseMapVoid::iterator::value()
{
	return ((void**)mIterator)[1];
}

BaseMapVoid::iterator& BaseMapVoid::iterator::operator++(int)
{
	void **it=(void **)mIterator;
	it+=2;
	mIterator=(void *)it;
	return *this;
}

bool BaseMapVoid::iterator::operator==(const BaseMapVoid::iterator& _Right)
{
	return mIterator==_Right.mIterator;
}

bool BaseMapVoid::iterator::operator!=(const BaseMapVoid::iterator& _Right)
{
	return !(mIterator==_Right.mIterator);
}*/

//*********************************************** BaseShortString ********************************************

/*BaseShortString::BaseShortString()
{
	initFunc();
	mData=0;//new std::string();
}

BaseShortString::BaseShortString(const char *ch)
{
	initFunc();
	unsigned char s=extFunctions.FindCMem((void*)ch,0,255);
	mData=0;
	if (s>0) {
		mData=(char*)_new(s);
		((unsigned char*)mData)[0]=s;
		extFunctions.MoveMem((void*)ch,&((char*)mData)[1],s+1);
	}
}

BaseShortString::~BaseShortString()
{
	if (mData) _del(mData,((unsigned char*)mData)[0]);
}

const char *BaseShortString::str()
{
	if (!mData) return 0;
	return &((char*)mData)[1];
}

char BaseShortString::length()
{
	if (!mData) return 0;
	return mData[0];
}

int BaseShortString::compare(char* ptr)
{
	if (!mData) {
		if (!ptr || *ptr==0) return 0;
		return -1;
	}
	return extFunctions.CmpMem(&((char*)mData)[1],ptr,((unsigned char*)mData)[0]);
}

BaseShortString &BaseShortString::operator=(char _ch)
{
	if (_ch!=0) {
		void *Data=_new(1);
		if (mData!=Data) {
			if (mData) _del(mData,((unsigned char*)mData)[0]);
			mData=(char*)Data;
		}
		((unsigned char*)mData)[0]=1;
		((char*)mData)[1]=_ch;
		((char*)mData)[2]=0;
	} else if (mData) _del(mData,((unsigned char*)mData)[0]);
	return *this;
}

BaseShortString &BaseShortString::operator=(const char *_ch)
{
	unsigned char s=0;
	if (_ch) s=extFunctions.FindCMem((void*)_ch,0,255);
	void *Data=_new(s);
	if (mData!=Data) {
		if (mData) _del(mData,((unsigned char*)mData)[0]);
		mData=(char*)Data;
	}
	if (s>0) {
		((unsigned char*)mData)[0]=s;
		extFunctions.MoveMem((void*)_ch,&((char*)mData)[1],s+1);
	}
	return *this;
}

BaseShortString &BaseShortString::operator=(BaseShortString& str)
{
	unsigned char s=0;
	s=str.length();
	void *Data=_new(s);
	if (mData!=Data) {
		if (mData) _del(mData,((unsigned char*)mData)[0]);
		mData=(char*)Data;
	}
	if (s>0) {
		((unsigned char*)mData)[0]=s;
		extFunctions.MoveMem((void*)str.str(),&((char*)mData)[1],s+1);
	}
	return *this;
}

BaseShortString &BaseShortString::operator+=(char _ch)
{
	unsigned char s=0;
	if (mData) s=((unsigned char*)mData)[0];
	void *Data=_new(s+1);
	if (mData!=Data) {
		if (mData) {
			extFunctions.MoveMem(&((char*)mData)[1],&((char*)Data)[1],s);
			_del(mData,((unsigned char*)mData)[0]);
		}
		mData=(char*)Data;
	}
	((unsigned char*)mData)[0]=s+1;
	((char*)mData)[s+1]=_ch;
	((char*)mData)[s+2]=0;
	return *this;
}

BaseShortString &BaseShortString::operator+=(const char *_ch)
{
	unsigned char p=extFunctions.FindCMem((void*)_ch,0,255);
	unsigned char s=0;
	if (mData) s=((unsigned char*)mData)[0];
	void *Data=_new(s+p);
	if (mData!=Data) {
		if (mData) {
			extFunctions.MoveMem(&((char*)mData)[1],&((char*)Data)[1],s);
			_del(mData,((unsigned char*)mData)[0]);
		}
		mData=(char*)Data;
	}
	((unsigned char*)mData)[0]=s+p;
	extFunctions.MoveMem((void*)_ch,&((char*)mData)[s+1],p);
	((char*)mData)[s+p+1]=0;
	return *this;
}

bool BaseShortString::operator==(BaseShortString & _r)
{
	if (!mData) {
		if (!_r.mData) return false;
		return false;
	}
	return extFunctions.CmpMem(&((char*)mData)[0],&((unsigned char*)_r.mData)[0],((unsigned char*)mData)[0]+1)==-1;
}

bool BaseShortString::operator>(BaseShortString & _r)
{
	if (!mData) {
		if (!_r.mData) return false;
		return false;
	}
	return extFunctions.SubMem(&((char*)mData)[0],&((unsigned char*)_r.mData)[0],((unsigned char*)mData)[0]+1)<0;
}

int BaseShortString::_size(unsigned char size)
{
	if (size<=0) return 0;
	int s = extFunctions.ILogSize(size+2);
	return s;
}

void *BaseShortString::_new(unsigned char size)
{
	int s=_size(size);
	if (mData && (s==_size(((unsigned char*)mData)[0]))) return mData;
	char *r=0;
	//if (s>0) r=new char[s];
	if (s>0) r=(char*)internalmemmanager.getNew(s);
	return r;
}

void BaseShortString::_del(void*mem,unsigned int size)
{
	internalmemmanager.freeThis((char*)mem,_size(size));
	// delete (char*)mem;
}*/

//*********************************************** BaseString ********************************************

/*BaseString::BaseString()
{
	//Functions::init();
	mData=0;//new std::string();
}

BaseString::BaseString(const char *ch)
{
	if (!ch) {
		mData=0;
		return;
	}
	initFunc();
	unsigned int s=extFunctions.FindCMem((void*)ch,0,0xFFFFFF);
	mData=0;
	if (s>0) {
		mData=(char*)_new(s);
		((unsigned int*)mData)[0]=s;
		extFunctions.MoveMem((void*)ch,&((char*)mData)[4],s+1);
	}
}

BaseString::~BaseString()
{
	if (mData) _del(mData,((unsigned int*)mData)[0]);
}

unsigned int BaseString::length()
{
	if (!mData) return 0;
	return *(unsigned int*)mData;
}

void BaseString::insert(unsigned int pos,char _ch)
{
	unsigned int s=0;
	if (mData) s=((unsigned int*)mData)[0];
	void *Data=_new(s+1);
	if (mData!=Data) {
		if (mData) {
			extFunctions.MoveMem(&((char*)mData)[4],&((char*)Data)[4],s);
			_del(mData,((unsigned int*)mData)[0]);
		}
		mData=(char*)Data;
	}
	if (pos>s) pos=s;
	((unsigned int*)mData)[0]=s+1;
	if (s-pos>0) extFunctions.MoveBack(&((char*)mData)[4+pos],&((char*)mData)[4+pos+1],s-pos);
	((char*)mData)[pos+4]=_ch;
	((char*)mData)[s+5]=0;
}

void BaseString::remove(unsigned int pos)
{
	unsigned int s=0;
	if (mData) s=((unsigned int*)mData)[0];
	if (s<=0) return;
	void *Data=_new(s-1);
	s--;
	if (pos>s) pos=s;
	if (mData!=Data) {
		if (mData) {
			if (Data) {
				extFunctions.MoveMem(&((char*)mData)[4],&((char*)Data)[4],pos);
				extFunctions.MoveMem(&((char*)mData)[4+pos+1],&((char*)Data)[4+pos],s-pos);
			}
			_del(mData,((unsigned int*)mData)[0]);
		}
		mData=(char*)Data;
		if (mData) {
			((unsigned int*)mData)[0]=s;
			((char*)mData)[s+4]=0;
		}
		return;
	}
	((unsigned int*)mData)[0]=s;
	if (s-pos>0) extFunctions.MoveMem(&((char*)mData)[4+pos+1],&((char*)mData)[4+pos],s-pos);
	((char*)mData)[s+4]=0;
}

const char *BaseString::str()
{
	if (!mData) return 0;
	return &((char*)mData)[4];
}

int BaseString::compare(char* ptr)
{
	if (!mData) {
		if (!ptr) {
			return 0;
		} else if (*ptr==0) {
			return 0;
		}
		return -1;
	}
	return extFunctions.CmpMem(&((char*)mData)[4],ptr,((unsigned int*)mData)[0]);
}

BaseString &BaseString::operator=(char _ch)
{
	if (_ch!=0) {
		void *Data=_new(1);
		if (mData!=Data) {
			if (mData) _del(mData,((unsigned int*)mData)[0]);
			mData=(char*)Data;
		}
		((unsigned int*)mData)[0]=1;
		((char*)mData)[4]=_ch;
		((char*)mData)[5]=0;
	} else if (mData) _del(mData,((unsigned int*)mData)[0]);
	return *this;
}

BaseString &BaseString::operator=(const char *_ch)
{
	unsigned int s=0;
	if (_ch) s=extFunctions.FindCMem((void*)_ch,0,255);
	void *Data=_new(s);
	if (mData!=Data) {
		if (mData) _del(mData,((unsigned int*)mData)[0]);
		mData=(char*)Data;
	}
	if (s>0) {
		((unsigned int*)mData)[0]=s;
		extFunctions.MoveMem((void*)_ch,&((char*)mData)[4],s+1);
	}
	return *this;
}

BaseString &BaseString::operator+=(char _ch)
{
	unsigned int s=0;
	if (mData) s=((unsigned int*)mData)[0];
	void *Data=_new(s+1);
	if (mData!=Data) {
		if (mData) {
			extFunctions.MoveMem(&((char*)mData)[4],&((char*)Data)[4],s);
			_del(mData,((unsigned int*)mData)[0]);
		}
		mData=(char*)Data;
	}
	((unsigned int*)mData)[0]=s+1;
	((char*)mData)[s+4]=_ch;
	((char*)mData)[s+5]=0;
	return *this;
}

BaseString &BaseString::operator+=(const char *_ch)
{
	unsigned int p=extFunctions.FindCMem((void*)_ch,0,0xFFFFFF);
	unsigned int s=0;
	if (mData) s=((unsigned int*)mData)[0];
	void *Data=_new(s+p);
	if (mData!=Data) {
		if (mData) {
			extFunctions.MoveMem(&((char*)mData)[4],&((char*)Data)[4],s);
			_del(mData,((unsigned int*)mData)[0]);
		}
		mData=(char*)Data;
	}
	((unsigned int*)mData)[0]=s+p;
	extFunctions.MoveMem((void*)_ch,&((char*)mData)[s+4],p);
	((char*)mData)[s+p+4]=0;
	return *this;
}

bool BaseString::operator==(BaseString & _r)
{
	if (!mData) {
		if (!_r.mData) return 0;
		return false;
	}
	return extFunctions.CmpMem(&((char*)mData)[0],&((char*)_r.mData)[0],((unsigned int*)mData)[0]+4)==-1;
}

int BaseString::_size(unsigned int size)
{
	if (size<=0) return 0;
	int s=extFunctions.ILogSize(size+5);
	return s;
}

void *BaseString::_new(unsigned int size)
{
	int s=_size(size);
	if (mData && (s==_size(((unsigned int*)mData)[0]))) return mData;
	char *r=0;
	if (s>0) r=(char*)internalmemmanager.getNew(s);
	//if (s>0) r=new char[s];
	return r;
}

void BaseString::_del(void*mem,unsigned int size)
{
	internalmemmanager.freeThis((char*)mem,_size(size));
	// delete (char*)mem;
}*/

OPTIMIZE_OFF;
WARNING_ENABLE;

}
