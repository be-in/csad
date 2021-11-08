//=============================================================================
///**
// *  @file defarray.cpp
// *
// *  $Id: defarray.cpp 23.05.2012  $
// *
// *  @brief generator 3 tool, MS Visual C++ 2003-2008
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#include "basearray.h"
#include "baseapi.h"
#include <bt/functions.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

	struct Element {
		void *key;
		void *val;
	};

	/*void *_allokMem(unsigned _int32 size)
	{
		if ((size>>bt::internalmemmanager._olevel())<64) {
			return bt::internalmemmanager.getNew(size);
		} else return new char[size];
	}

	void _freeMem(void *mem,unsigned _int32 size)
	{
		if ((size>>bt::internalmemmanager._olevel())<64) {
			bt::internalmemmanager.freeThis(mem,size);
		} else delete[] (char*)mem;
	}*/

	void _FASTCALL reallocChar(void ** list,_int32 size)
	{
		initFunc();
		if (!list) return;
		unsigned _int32 count=0;
		unsigned _int32 lallok=0;
		unsigned _int32 allocSize=0;
		if (size>0) allocSize=extFunctions.ILogSize(size+2);
		if (*list) {
			count=**(unsigned char**)list;
			if (count>0) lallok=extFunctions.ILogSize(count+2);
		}
		if (size==0) {
			if (*list) {
				bt::internalmemmanager.cashfree(*list,lallok);
				*list=0;
			}
			return;
		}
		if (lallok==allocSize) return;

		unsigned _int32 fullsize=allocSize;
		char *l=(char *)bt::internalmemmanager.cashalloc(fullsize);
		if (*list) {
			if (count>(unsigned _int32)size) count=size;
			unsigned _int32 lsize=0;
			if (count>0) lsize=count+2;
			extFunctions.MoveMem(*list,l,lsize);
			if (fullsize-lsize>0) extFunctions.CleanMem(l+lsize,fullsize-lsize);
			bt::internalmemmanager.cashfree(*list,lallok);
		} else {
			extFunctions.CleanMem(l,fullsize);
		}
		*list=l;
	}

	void _FASTCALL reallocLChar(void ** list,_int32 size)
	{
		initFunc();
		if (!list) return;
		unsigned _int32 count=0;
		unsigned _int32 lallok=0;
		unsigned _int32 allocSize=0;
		if (size>0) allocSize=extFunctions.ILogSize(size+5);
		if (*list) {
			count=**(unsigned _int32**)list;
			if (count>0) lallok=extFunctions.ILogSize(count+5);
		}
		if (size==0) {
			if (*list) {
				bt::internalmemmanager.cashfree(*list,lallok);
				*list=0;
			}
			return;
		}
		if (lallok==allocSize) return;

		unsigned _int32 fullsize=allocSize;
		char *l=(char *)bt::internalmemmanager.cashalloc(fullsize);
		if (*list) {
			if (count>(unsigned _int32)size) count=size;
			unsigned _int32 lsize=0;
			if (count>0) lsize=count+5;
			extFunctions.MoveMem(*list,l,lsize);
			if (fullsize-lsize>0) extFunctions.CleanMem(l+lsize,fullsize-lsize);
			bt::internalmemmanager.cashfree(*list,lallok);
		} else {
			extFunctions.CleanMem(l,fullsize);
		}
		*list=l;
	}

	void _FASTCALL reallocVoidSort(void ** list,_int32 size)
	{
		initFunc();
		if (!list) return;
		if (size<=0) return;
		unsigned _int32 count=0;
		unsigned _int32 lallok=0;
		unsigned _int32 allocSize=extFunctions.ILogSize(MULSIZEOFVOID(size)+4);
		if (*list) {
			count=**(unsigned _int32**)list;
			lallok=extFunctions.ILogSize(MULSIZEOFVOID(count)+4);
		}
		if (lallok==allocSize) return;

		unsigned _int32 fullsize=allocSize;
		char *l=(char *)bt::internalmemmanager.cashalloc(fullsize);
		if (*list) {
			if (count>(unsigned _int32)size) count=size;
			unsigned _int32 lsize=MULSIZEOFVOID(count)+4;
			extFunctions.MoveMem(*list,l,MULSIZEOFVOID(count)+4);
			if (fullsize-lsize>0) extFunctions.CleanMem(l+lsize,fullsize-lsize);
			bt::internalmemmanager.cashfree(*list,lallok);
		} else {
			extFunctions.CleanMem(l,fullsize);
		}
		*list=l;
	}

	void _FASTCALL _reallocVoidSortMap(void ** list,_int32 size)
	{
		initFunc();
		if (!list) return;
		if (size<=0) return;
		unsigned _int32 count=0;
		unsigned _int32 lallok=0;
		unsigned _int32 lsize=0;
		unsigned _int32 nsize=MULSIZEOFVOID(size<<1)+4;
		unsigned _int32 allocSize=extFunctions.ILogSize(nsize);
		if (*list) {
			count=**(unsigned _int32**)list;
			lsize=MULSIZEOFVOID(count<<1)+4;
			lallok=extFunctions.ILogSize(lsize);
		}
		if (lallok==allocSize) return;

		unsigned _int32 fullsize=allocSize;
		char *l=(char *)bt::internalmemmanager.cashalloc(fullsize);
		if (*list) {
			if (lsize>nsize) lsize=nsize;
			extFunctions.MoveMem(*list,l,lsize);
			if (fullsize-lsize>0) extFunctions.CleanMem(l+lsize,fullsize-lsize);
			bt::internalmemmanager.cashfree(*list,lallok);
		} else {
			extFunctions.CleanMem(l,fullsize);
		}
		*list=l;
	}

// ** string array

	void _APICALL _SSetDEF(void **list,void *str) 
	{
		if (!list) return;
		unsigned char s=0;
		void *astr=str;
		if ((_voidint)astr>255) {
			s=extFunctions.FindCMem(str,0,255);
		} else if (astr) {
			s=1;
			astr=&str;
		}
		reallocChar(list,s);
		if (s>0) {
			unsigned char *p=*(unsigned char**)list;
			*p=s;
			p+=1;
			extFunctions.MoveMem((void*)astr,p,s);
			p+=s;
			*p=0;
		}
	}

	void _APICALL _SAddDEF(void **list,void *str) 
	{
		if (!list) return;
		unsigned char c=0;
		void *astr=str;
		if ((_voidint)astr>255) {
			c=extFunctions.FindCMem((void*)astr,0,255);
		} else if (astr) {
			c=1;
			astr=&str;
		}
		unsigned char s=0;
		if (*list) s=**(unsigned char**)list;
		reallocChar(list,s+c);
		**(unsigned char**)list=s+c;
		unsigned char *p=*(unsigned char**)list;
		p+=s+1;
		extFunctions.MoveMem((void*)astr,p,c);
		p+=c;
		*p=0;
	}

	int _APICALL _SCompareDEF(void **list,void *str)
	{
		if (!list) return 0;
		unsigned char c=0;
		if (*list) c=**(unsigned char**)list;
		if (!c) {
			if (!str || *(char*)str==0) return 0;
			return -1;
		}
		char *p=*(char**)list;
		p++;
		return extFunctions.CmpMem(p,str,c);
	}

// ** long string array

	void _APICALL _LSSetDEF(void **list,void *str)
	{
		if (!list) return;
		unsigned _int32 s=0;
		void *astr=str;
		if ((_voidint)astr>255) {
			s=extFunctions.FindCMem(str,0,1073741824);
		} else if (astr) {
			s=1;
			astr=&str;
		}
		reallocLChar(list,s);
		if (s>0) {
			char *p=*(char**)list;
			**(unsigned _int32**)list=s;
			p+=4;
			extFunctions.MoveMem((void*)astr,p,s);
			p+=s;
			*p=0;
		}
	}

	void _APICALL _LSAddDEF(void **list,void *str)
	{
		if (!list) return;
		unsigned _int32 c=0;
		void *astr=str;
		if ((_voidint)astr>255) {
			c=extFunctions.FindCMem((void*)astr,0,1073741824);
		} else if (astr) {
			c=1;
			astr=&str;
		}
		unsigned _int32 s=0;
		if (*list) s=**(unsigned _int32**)list;
		reallocLChar(list,s+c);
		**(unsigned _int32**)list=s+c;
		char *p=*(char**)list;
		p+=s+4;
		extFunctions.MoveMem((void*)astr,p,c);
		p+=c;
		*p=0;
	}

	void _APICALL _LSInsertDEF(void **list,void *str,unsigned _int32 pos)
	{
		if (!list) return;
		unsigned _int32 c=0;
		void *astr=str;
		if ((_voidint)astr>255) {
			c=extFunctions.FindCMem((void*)astr,0,1073741824);
		} else if (astr) {
			c=1;
			astr=&str;
		}
		unsigned _int32 s=0;
		if (*list) s=**(unsigned _int32**)list;
		reallocLChar(list,s+c);
		**(unsigned _int32**)list=s+c;
		char *p=*(char**)list;
		unsigned _int32 _pos=pos;
		if (_pos<0) _pos=0;
		if (_pos>s) _pos=s;
		p+=_pos+4;
		s-=pos;
		if (s>0) extFunctions.MoveBack(p,p+c,s);
		extFunctions.MoveMem((void*)astr,p,c);
		p+=c;
		*p=0;
	}

	void _APICALL _LSRemoveDEF(void **list,unsigned _int32 pos,unsigned _int32 size)
	{
		if (!list) return;
		if (!*list) return;
		unsigned _int32 s=**(unsigned _int32**)list;
		unsigned _int32 _pos=pos;
		if (_pos<0) _pos=0;
		if (_pos>s) _pos=s;
		char *p=*(char**)list;
		if (size+_pos>s) size=s-_pos;
		s-=(size+_pos);
		p+=_pos+4;
		if (s>0) {
			extFunctions.MoveMem(p+size,p,s+1);
			//p[s]=0;
		}
		s+=_pos;
		reallocLChar(list,s);
		if (*list) **(unsigned _int32**)list=s;
	}

	int _APICALL _LSCompareDEF(void **list,void *str)
	{
		if (!list) return 0;
		unsigned _int32 c=0;
		if (*list) c=**(unsigned _int32**)list;
		if (!c) {
			if (!str || *(char*)str==0) return 0;
			return -1;
		}
		char *p=*(char**)list;
		p+=4;
		return extFunctions.CmpMem(p,str,c);
	}

// ** base array

	void _FASTCALL _ANTReAllocSize(void * list,unsigned int count)
	{
		if (!list) return;
		sArray *arr=(sArray*)list;
		unsigned _int32 AllCount=arr->AllCount;
		if (count>AllCount) {
			if (AllCount==0) AllCount=2;
			AllCount*=2;
			if (AllCount<count) AllCount=count;
			char *nVals=0;
			if (arr->Ths) {
				nVals=(char*)extFunctions.CreateMem(arr->Ths(AllCount),0);
				if (arr->Vals) extFunctions.MoveMem((void*)arr->Vals,(void*)nVals,arr->Ths(arr->Count));
			} else {
				nVals=(char*)extFunctions.CreateMem(AllCount*arr->ItSize,0);
				if (arr->Vals) extFunctions.MoveMem((void*)arr->Vals,(void*)nVals,arr->Count*arr->ItSize);
			}
			if (arr->Vals) extFunctions.DeleteMem(arr->Vals,0);
			arr->Vals=nVals;
		}
		arr->AllCount=AllCount;
	}

	void _FASTCALL _ANTLowAllocSize(void * list,unsigned int count)
	{
		if (!list) return;
		sArray *arr=(sArray*)list;
		unsigned _int32 AllCount=arr->AllCount;
		unsigned int nCount=64;
		while (count>nCount) nCount*=2;
		if (nCount!=AllCount) {
			AllCount=nCount;
			char *nVals=0;
			if (arr->Ths) {
				nVals=(char*)extFunctions.CreateMem(arr->Ths(AllCount),0);
				if (arr->Vals) extFunctions.MoveMem((void*)arr->Vals,(void*)nVals,arr->Ths(count));
			} else {
				nVals=(char*)extFunctions.CreateMem(AllCount*arr->ItSize,0);
				if (arr->Vals) extFunctions.MoveMem((void*)arr->Vals,(void*)nVals,count*arr->ItSize);
			}
			if (arr->Vals) extFunctions.DeleteMem(arr->Vals,0);
			arr->Vals=nVals;
		}
		arr->AllCount=AllCount;
	}

	void _APICALL _ANTInitDEF(void *list,unsigned int size,unsigned int count)
	{
		if (!list) return;
		sArray *arr=(sArray*)list;
		arr->AllCount=0;
		arr->Vals=0;
		arr->Count=0;
		arr->ItSize=size;
		arr->Ths=(tfFASTCALL_int_FUNC_int)extFunctions.GetFastFCMulI(size);
		_ANTResizeDEF(list,count);
	}

	void _APICALL _ANTFreeDEF(void *list)
	{
		if (!list) return;
		sArray *arr=(sArray*)list;
		extFunctions.DeleteMem(arr->Vals,0);
		arr->Vals=0;
		arr->Count=0;
		arr->AllCount=0;
	}

	void _APICALL _ANTResizeDEF(void *list,unsigned int count)
	{
		if (!list) return;
		sArray *arr=(sArray*)list;
		_ANTReservDEF(list,count);
		arr->Count=count;
	}

	void _APICALL _ANTReservDEF(void *list,unsigned int count)
	{
		if (!list) return;
		sArray *arr=(sArray*)list;
		if (count>arr->AllCount) _ANTReAllocSize(list,count);
		if (count<arr->AllCount) _ANTLowAllocSize(list,count);
	}

	void _APICALL _ANTAssignDEF(void *list,void *val)
	{
		if (!list) return;
		sArray *arr=(sArray*)list;
		unsigned int nCount=arr->Count+1;
		_ANTReAllocSize(list,nCount);
		char *itt=arr->Vals;
		if (arr->Ths) {
			itt+=arr->Ths(arr->Count);
		} else {
			itt+=arr->Count*arr->ItSize;
		}
		extFunctions.MoveMem(val,itt,arr->ItSize);
		arr->Count=nCount;
	}

	void _APICALL _ANTDelLastDEF(void *list)
	{
		if (!list) return;
		sArray *arr=(sArray*)list;
		unsigned _int32 count=arr->Count;
		if (count>0) {
			count--;
			_ANTLowAllocSize(list,count);
		}
		arr->Count=count;
	}

	void* _APICALL _ANTPositionDEF(void *list,unsigned int id)
	{
		if (!list) return 0;
		sArray *arr=(sArray*)list;
		bt::tfFASTCALL_int_FUNC_int Ths=arr->Ths;
		if (Ths) return (void*)&arr->Vals[Ths(id)];
		return (void*)&arr->Vals[id*arr->ItSize];
	}

	void* _APICALL _ANTPositionLDEF(void *list)
	{
		if (!list) return 0;
		sArray *arr=(sArray*)list;
		unsigned _int32 count=arr->Count-1;
		if (count<0) return 0;
		bt::tfFASTCALL_int_FUNC_int Ths=arr->Ths;
		if (Ths) return (void*)&arr->Vals[Ths(count)];
		return (void*)&arr->Vals[count*arr->ItSize];
	}

// ** void array

	void _APICALL _DPSetCountDEF(void ** list,unsigned _int32 count)
	{
		if (!list) return;
		reallocVoidSort(list,count);
		**(unsigned _int32**)list=count;
	}

	void ** _APICALL _DPAddLastDEF(void ** list,void *val)
	{
		if (!list) return 0;
		unsigned _int32 count=0;
		if (*list) count=**(unsigned _int32**)list;
		char *p;
		void **b;
		count++;
		reallocVoidSort(list,count);
		**(unsigned _int32**)list=count;
		unsigned _int32 pos=count-1;
		p=(char*)*list;
		p+=4;
		b=(void **)p;
		b[pos]=val;
		return (void**)&b[pos];
	}

	void ** _APICALL _DPInsertDEF(void ** list,void *val,unsigned _int32 pos)
	{
		if (!list) return 0;
		unsigned _int32 count=0;
		if (*list) count=**(unsigned _int32**)list;
		char *p;
		void **b;
		count++;
		reallocVoidSort(list,count);
		**(unsigned _int32**)list=count;
		if (pos>=count) pos=count-1;
		p=(char*)*list;
		p+=4;
		b=(void **)p;
		while (count>pos+1) {
			count--;
			b[count]=b[count-1];
		}
		b[pos]=val;
		return (void**)&b[pos];
	}

	void _APICALL _DPRemoveDEF(void ** list,unsigned _int32 pos)
	{
		if (!list) return;
		if (!*list) return;
		unsigned _int32 count= **(unsigned _int32**)list;
		if (pos>=count) return;
		char *p=(char*)*list;
		p+=4;
		void **b=(void **)p;

		extFunctions.MoveMem(&b[pos+1],&b[pos],MULSIZEOFVOID((count-pos)));
		count--;
		b[count]=0;
		reallocVoidSort(list,count);
		if (*list) **(unsigned _int32**)list=count;
		return;
	}

	_int32 _APICALL _DPRemoveValDEF(void ** list,void *val)
	{
		if (!list) return -1;
		if (!*list) return -1;
		unsigned _int32 count= **(unsigned _int32**)list;
		char *p=(char*)*list;
		p+=4;
		void **b=(void **)p;
		unsigned _int32 pos=0;
		void *sket=val;
		while (pos<count) {
			if (b[pos]==sket) break;
			pos++;
		}
		if (pos>=count) return -1;

		extFunctions.MoveMem(&b[pos+1],&b[pos],MULSIZEOFVOID((count-pos)));
		count--;
		b[count]=0;
		reallocVoidSort(list,count);
		if (*list) **(unsigned _int32**)list=count;
		return pos;
	}

	void _APICALL _DPRemoveLastDEF(void ** list)
	{
		if (!list) return;
		if (!*list) return;
		unsigned _int32 count= **(unsigned _int32**)list;
		count--;
		reallocVoidSort(list,count);
		if (*list) **(unsigned _int32**)list=count;
		return;
	}

// ** short string array

	void ** _APICALL _DSAddLastDEF(void ** list,void *val)
	{
		void **ret=_DPAddLastDEF(list,0);
		_SSetDEF(ret,val);
		return ret;
	}
	
	void _APICALL _DSFreeDEF(void ** list)
	{
		if (!list) return;
		if (*list) {
			char *p=(char*)*list;
			unsigned _int32 count=*(unsigned _int32 *)p;
			p+=4;
			void **buff=(void **)p;
			unsigned _int32 a=count;
			while (a>0) {
				_SSetDEF(buff,0);
				buff++;
				a--;
			}
			unsigned _int32 lallok=extFunctions.ILogSize(MULSIZEOFVOID(count)+4);
			bt::internalmemmanager.cashfree(*list,lallok);
		}
		*list=0;
	}

// ** void sort array

	void * _APICALL _APLastDEF(void ** list)
	{
		if (!list) return 0;
		if (!*list) return 0;
		unsigned _int32 count= **(unsigned _int32**)list;
		char *p=(char*)*list;
		p+=MULSIZEOFVOID(count-1)+4;
		return (void**)p;
	}

	void * _APICALL _APCloneDEF(void ** list)
	{
		if (!list) return 0;
		if (!*list) return 0;
		unsigned _int32 count= **(unsigned _int32**)list;
		void *newList=0;
		reallocVoidSort(&newList,count);
		extFunctions.MoveMem(*list,newList,MULSIZEOFVOID(count)+4);
		return newList;
	}

	void ** _APICALL _APAddDEF(void ** list,void *val)
	{
		if (!list) return 0;
		unsigned _int32 count=0;
		unsigned _int32 pos=0;
		char *p=(char*)*list;
		p+=4;
		void **b=(void **)p;
		_voidint skey=(_voidint)val;
		_voidint rkey=(_voidint)_voidintmax;
		if (*list) {
			count=**(unsigned _int32**)list;
			unsigned _int32 a=count;
			unsigned _int32 apos=0;

			while (apos<a) {
				pos=((apos+a)>>1);
				rkey=(_voidint)b[pos];
				if (skey>rkey) {
					apos=pos+1;
				} else {
					a=pos;
				}
			}
			pos=a;
			if (pos<count) rkey=(_voidint)b[pos];
		}

		if (skey!=rkey) {
			count++;
			reallocVoidSort(list,count);
			**(unsigned _int32**)list=count;
			p=(char*)*list;
			p+=4;
			b=(void **)p;
			while (count>pos+1) {
				count--;
				b[count]=b[count-1];
			}
			b[pos]=val;
			return (void**)&b[pos];
		} else {
			return (void**)&b[pos];
		}
	}

	_int32 _APICALL _APFindDEF(void ** list,void *val)
	{
		if (!list) return -1;
		if (!*list) return -1;
		unsigned _int32 count= **(unsigned _int32**)list;
		char *p=(char*)*list;
		p+=4;
		void **b=(void **)p;

		unsigned _int32 pos=0;
		_voidint skey=(_voidint)val;

		while (count>0) {
			unsigned _int32 hcount=(count>>1);
			_voidint rkey=(_voidint)b[pos+hcount];
			if (skey==rkey) return pos+hcount;
			if (skey>rkey) {pos+=hcount+1;count--;}
			count=count>>1;
			if (count>0) {
				hcount=(count>>1);
				rkey=(_voidint)b[pos+hcount];
				if (skey==rkey) return pos+hcount;
				if (skey>rkey) {pos+=hcount+1;count--;}
				count=count>>1;
			}
		}

		return -1;
	}

	_int32 _APICALL _APRemoveDEF(void ** list,void *val)
	{
		if (!list) return -1;
		if (!*list) return -1;
		unsigned _int32 count= **(unsigned _int32**)list;
		unsigned _int32 a=count;
		char *p=(char*)*list;
		p+=4;
		void **b=(void **)p;

		unsigned _int32 apos=0;
		unsigned _int32 pos=0;
		_voidint skey=(_voidint)val;
		_voidint rkey=_voidintmax;

		while (apos<a) {
			pos=((apos+a)>>1);
			rkey=(_voidint)b[pos];
			if (skey==rkey) break;
			if (skey>rkey) {
				apos=pos+1;
			} else {
				a=pos;
			}
		}
		if (skey!=rkey) return -1;

		extFunctions.MoveMem(&b[pos+1],&b[pos],MULSIZEOFVOID((count-pos)));
		count--;
		b[count]=0;
		reallocVoidSort(list,count);
		if (*list) **(unsigned _int32**)list=count;
		return pos;
	}

	void * _APICALL _APEndDEF(void ** list)
	{
		if (!list) return 0;
		if (!*list) return 0;
		unsigned _int32 count= **(unsigned _int32**)list;
		char *p=(char*)*list;
		p+=MULSIZEOFVOID(count)+4;
		return (void**)p;
	}

	void _APICALL _APFreeDEF(void ** list)
	{
		if (!list) return;
		if (*list) {
			unsigned _int32 *p=(unsigned _int32*)*list;
			unsigned _int32 count=*p;
			unsigned _int32 lallok=extFunctions.ILogSize(MULSIZEOFVOID(count)+4);
			bt::internalmemmanager.cashfree(*list,lallok);
		}
		*list=0;
	}

// ** void map

	void ** _APICALL _MPAddDEF(void ** list,void *key,void *val)
	{
		if (!list) return 0;
		unsigned _int32 count=0;
		unsigned _int32 pos=0;
		char *p=(char*)*list;
		p+=4;
		Element *b=(Element *)p;
		_voidint skey=(_voidint)key;
		_voidint rkey=(_voidint)_voidintmax;
		if (*list) {
			count=**(unsigned _int32**)list;
			unsigned _int32 a=count;
			unsigned _int32 apos=0;

			while (apos<a) {
				pos=((apos+a)>>1);
				rkey=(_voidint)b[pos].key;
				if (skey==rkey) return (void**)&b[pos].val;
				if (skey>rkey) {
					apos=pos+1;
				} else {
					a=pos;
				}
				if (apos<a) {
					pos=((apos+a)>>1);
					rkey=(_voidint)b[pos].key;
					if (skey==rkey) return (void**)&b[pos].val;
					if (skey>rkey) {
						apos=pos+1;
					} else {
						a=pos;
					}
				}
			}
			pos=a;
			if (pos<count) rkey=(_voidint)b[pos].key;
		}

		if (skey!=rkey) {
			count++;
			_reallocVoidSortMap(list,count);
			**(unsigned _int32**)list=count;
			p=(char*)*list;
			p+=4;
			b=(Element *)p;
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

	void ** _APICALL _MPFindDEF(void ** list,void *key)
	{
		if (!list) return 0;
		if (!*list) return 0;
		unsigned _int32 count = **(unsigned _int32**)list;
		char *p=(char*)*list;
		p+=4;
		Element *b=(Element *)p;

		_voidint skey=(_voidint)key;
	
		while (count>0) {
			void** kt=(void**)&b[count>>1];
			_voidint rkey=(_voidint)kt[0];
			if (skey==rkey) return (void**)&kt[1];
			if (skey>rkey) {b+=(count>>1)+1;count--;}
			count=count>>1;
			if (count>0) {
				kt=(void**)&b[count>>1];
				rkey=(_voidint)kt[0];
				if (skey==rkey) return (void**)&kt[1];
				if (skey>rkey) {b+=(count>>1)+1;count--;}
				count=count>>1;
			}
		}

		return 0;
	}

	void * _APICALL _MPFindByValDEF(void ** list, void *val, void *key)
	{
		if (!list) return key;
		if (!*list) return key;
		unsigned _int32 count = **(unsigned _int32**)list;
		char *p = (char*)*list;
		p += 4;
		Element *b = (Element *)p;
		Element *end = b + count;
		while (b<end) {
			if (b->val == val) return b->key;
			b ++;
		}
		return key;
	}

	void* _APICALL _MPRemoveDEF(void ** list,void *key)
	{
		if (!list) return 0;
		if (!*list) return 0;
		unsigned _int32 count= **(unsigned _int32**)list;
		char *p=(char*)*list;
		p+=4;
		Element *b=(Element *)p;

		unsigned _int32 pos=0;
		_voidint skey=(_voidint)key;
		_voidint rkey=_voidintmax;

		unsigned _int32 fcount=count;

		while (fcount>0) {
			unsigned _int32 hcount=fcount>>1;
			rkey=(_voidint)b[pos+hcount].key;
			if (skey==rkey) {
				pos+=hcount;
				break;
			}
			if (skey>rkey) {pos+=hcount+1;fcount--;}
			fcount=fcount>>1;
			if (fcount>0) {
				unsigned _int32 hcount=fcount>>1;
				rkey=(_voidint)b[pos+hcount].key;
				if (skey==rkey) {
					pos+=hcount;
					break;
				}
				if (skey>rkey) {pos+=hcount+1;fcount--;}
				fcount=fcount>>1;
			}
		}
		if (skey!=rkey) return 0;

		b=(Element *)p;
		void *ret=b[pos].val;
		while (count>pos+1) {
			pos++;
			b[pos-1].key=b[pos].key;
			b[pos-1].val=b[pos].val;
		}
		count--;
		b[count].key=0; // ??
		b[count].val=0; // ??
		_reallocVoidSortMap(list,count);
		if (*list) **(unsigned _int32**)list=count;
		return ret;
	}

	void ** _APICALL _MPEndDEF(void ** list)
	{
		if (!list) return 0;
		if (!*list) return 0;
		unsigned _int32 count= **(unsigned _int32**)list;
		char *p=(char*)*list;
		p+=MULSIZEOFVOID(count<<1)+4;
		return (void**)p;
	}

	void _APICALL _MPFreeDEF(void ** list)
	{
		if (!list) return;
		if (*list) {
			unsigned _int32 *p=(unsigned _int32*)*list;
			unsigned _int32 count=*p;
			unsigned _int32 lallok=extFunctions.ILogSize(MULSIZEOFVOID(count<<1)+4);
			bt::internalmemmanager.cashfree(*list,lallok);
		}
		*list=0;
	}

// ** void string map

	void ** _APICALL _MSPAddDEF(void ** list,void *key,void *val)
	{
		if (!list) return 0;
		unsigned _int32 count=0;
		unsigned _int32 pos=0;
		unsigned char *rkey=0;
		unsigned char *skey=(unsigned char*)key;
		char *p=(char*)*list;
		p+=4;
		Element *b=(Element *)p;
		_int32 cmp=-1; 
		if (*list) {
			count=**(unsigned _int32**)list;
			unsigned _int32 a=count;
			unsigned _int32 apos=0;
			while (apos<a) {
				pos=((apos+a)>>1);
				rkey=(unsigned char*)b[pos].key;
				cmp=extFunctions.SubMem(skey,rkey,*skey+1);
				if (cmp==0) return (void**)&b[pos];
				if (cmp<0) {
					apos=pos+1;
				} else {
					a=pos;
				}
			}
			pos=a;
			if (pos<count) rkey=(unsigned char*)b[pos].key;
		}

		if ((!rkey) || (cmp!=0)) {
			count++;
			_reallocVoidSortMap(list,count);
			**(unsigned _int32**)list=count;
			p=(char*)*list;
			p+=4;
			b=(Element *)p;
			while (count>pos+1) {
				count--;
				b[count].key=b[count-1].key;
				b[count].val=b[count-1].val;
			}
			b[pos].key=key;
			b[pos].val=val;
			return (void**)&b[pos];
		} else {
			return (void**)&b[pos];
		}
	}

	void ** _APICALL _MSSPAddDEF(void ** list, void *key, void *val)
	{
		if (!list) return 0;
		unsigned _int32 count = 0;
		unsigned _int32 pos = 0;
		unsigned char **rkey = 0;
		unsigned char *skey = (unsigned char*)key;
		unsigned char c = extFunctions.FindCMem((void*)skey, 0, 255);
		char *p = (char*)*list;
		p += 4;
		Element *b = (Element *)p;
		_int32 cmp = -1;
		if (*list) {
			count = **(unsigned _int32**)list;
			unsigned _int32 a = count;
			unsigned _int32 apos = 0;
			while (apos < a) {
				pos = ((apos + a) >> 1);
				rkey = (unsigned char**)&b[pos];
				_int32 cmp = **rkey - c;
				if (cmp == 0) cmp = extFunctions.SubMem(skey, *rkey + 1, c);
				if (cmp == 0) return (void**)rkey;
				if (cmp < 0) {
					apos = pos + 1;
				}
				else {
					a = pos;
				}
			}
			pos = a;
			if (pos<count) rkey = (unsigned char**)&b[pos];
		}

		if ((!rkey) || (cmp != 0)) {
			count++;
			_reallocVoidSortMap(list, count);
			**(unsigned _int32**)list = count;
			p = (char*)*list;
			p += 4;
			b = (Element *)p;
			while (count>pos + 1) {
				count--;
				b[count].key = b[count - 1].key;
				b[count].val = b[count - 1].val;
			}
			b[pos].key = 0;
			arrFunctions.SSet(&b[pos].key, key);
			b[pos].val = val;
			return (void**)&b[pos];
		}
		else {
			return (void**)&b[pos];
		}
	}

	void ** _APICALL _MSPFindDEF(void **list,void *key)
	{
		if (!list) return 0;
		if (!*list) return 0;
		unsigned _int32 count= **(unsigned _int32**)list;
		char *p=(char*)*list;
		p+=4;
		Element *b=(Element *)p;

		unsigned char *skey=(unsigned char*)key;

		while (count>0) {
			unsigned char** rkey=(unsigned char**)&b[count>>1];
			_int32 cmp=extFunctions.SubMem(skey,*rkey,*skey+1);
			if (cmp==0) return (void**)&rkey[1];
			if (cmp<0) {b+=(count>>1)+1;count--;}
			count=count>>1;
		}

		return 0;
	}

	void ** _APICALL _MSSPFindDEF(void **list,char *key)
	{
		if (!list) return 0;
		if (!*list) return 0;
		unsigned _int32 count= **(unsigned _int32**)list;
		char *p=(char*)*list;
		p+=4;
		Element *b=(Element *)p;

		unsigned char *skey=(unsigned char*)key;
		unsigned char c=extFunctions.FindCMem((void*)skey,0,255);

		while (count>0) {
			unsigned char** rkey=(unsigned char**)&b[count>>1];
			_int32 cmp=**rkey-c;
			if (cmp==0) cmp=extFunctions.SubMem(skey,*rkey+1,c);
			if (cmp==0) return (void**)&rkey[1];
			if (cmp<0) {b+=(count>>1)+1;count--;}
			count=count>>1;
		}

		return 0;
	}

	void* _APICALL _MSPRemoveDEF(void ** list,void *key)
	{
		if (!list) return 0;
		if (!*list) return 0;
		if (!key) return 0;
		unsigned _int32 count= **(unsigned _int32**)list;
		unsigned _int32 a=count;
		char *p=(char*)*list;
		p+=4;
		Element *b=(Element *)p;

		unsigned _int32 apos=0;
		unsigned _int32 pos;
		unsigned char *rkey=0;
		unsigned char *skey=(unsigned char*)key;

		_int32 cmp=-1;
		while (apos<a) {
			pos=((apos+a)>>1);
			rkey=(unsigned char*)b[pos].key;
			cmp=extFunctions.SubMem(skey,rkey,*skey+1);
			if (cmp==0) break;
			if (cmp<0) {
				apos=pos+1;
			} else {
				a=pos;
			}
		}
		if (!rkey || cmp!=0) return 0;

		key=b[pos].key;
		extFunctions.MoveMem(&b[pos+1],&b[pos],MULSIZEOFVOID((count-pos)<<1));
		count--;
		b[count].key=0;
		b[count].val=0;
		_reallocVoidSortMap(list,count);
		**(unsigned _int32**)list=count;
		return key;
	}

	int _APICALL _MSSPRemoveDEF(void ** list,void *key)
	{
		if (!list) return 0;
		if (!*list) return 0;
		if (!key) return 0;
		unsigned _int32 count= **(unsigned _int32**)list;
		unsigned _int32 a=count;
		char *p=(char*)*list;
		p+=4;
		Element *b=(Element *)p;

		unsigned _int32 apos=0;
		unsigned _int32 pos;
		unsigned char *rkey=0;
		unsigned char *skey=(unsigned char*)key;
		unsigned char c=extFunctions.FindCMem((void*)skey,0,255);

		_int32 cmp=-1;
		while (apos<a) {
			pos=((apos+a)>>1);
			rkey=(unsigned char*)b[pos].key;
			cmp=*rkey-c;
			if (cmp==0) cmp=extFunctions.SubMem(skey,rkey+1,c);
			if (cmp==0) break;
			if (cmp<0) {
				apos=pos+1;
			} else {
				a=pos;
			}
		}
		if (!rkey || cmp!=0) return 0;

		_SSetDEF(&(b[pos].key),0);
		extFunctions.MoveMem(&b[pos+1],&b[pos],MULSIZEOFVOID((count-pos)<<1));
		count--;
		b[count].key=0;
		b[count].val=0;
		_reallocVoidSortMap(list,count);
		**(unsigned _int32**)list=count;
		return 1;
	}

	void _APICALL _MSSPFreeDEF(void ** list)
	{
		if (!list) return;
		if (!*list)  return;
		unsigned _int32 *p = (unsigned _int32*)*list;
		unsigned _int32 count = *p;
		unsigned _int32 lallok = extFunctions.ILogSize(MULSIZEOFVOID(count << 1) + 4);
		p += 1;
		Element *b = (Element *)p;
		while (count > 0) {
			_SSetDEF(&(b->key), 0);
			b++;
			count--;
		}
		bt::internalmemmanager.cashfree(*list, lallok);
		*list=0;
	}

// ** const void map

	void ** _APICALL _MCPAddDEF(void * list,void *key,void *val,unsigned _int32 max)
	{
		if (!list) return 0;
		unsigned _int32 count=*(unsigned _int32*)list;
		unsigned _int32 a=count;
		unsigned _int32 pos=0;
		char *p=(char*)list;
		p+=4;
		Element *b=(Element *)p;
		_voidint skey=(_voidint)key;
		_voidint rkey=(_voidint)_voidintmax;

		unsigned _int32 apos=0;
		while (apos<a) {
			pos=((apos+a)>>1);
			rkey=(_voidint)b[pos].key;
			if (skey>rkey) {
				apos=pos+1;
			} else {
				a=pos;
			}
			if (apos<a) {
				pos=((apos+a)>>1);
				rkey=(_voidint)b[pos].key;
				if (skey>rkey) {
					apos=pos+1;
				} else {
					a=pos;
				}
			}
		}
		pos=a;
		if (pos<count) rkey=(_voidint)b[pos].key;

		if (skey!=rkey) {
			if (count>=max) return 0;
			count++;
			*(unsigned _int32*)list=count;
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

	void ** _APICALL _MCPFindDEF(void * list,void *key)
	{
		if (!list) return 0;
		unsigned _int32 count= *(unsigned _int32*)list;
		char *p=(char*)list;
		p+=4;
		Element *b=(Element *)p;

		_voidint skey=(_voidint)key;
	
		while (count>0) {
			void** kt=(void**)&b[count>>1];
			_voidint rkey=(_voidint)kt[0];
			if (skey==rkey) return (void**)&kt[1];
			if (skey>rkey) {b+=(count>>1)+1;count--;}
			count=count>>1;
			if (count>0) {
				kt=(void**)&b[count>>1];
				rkey=(_voidint)kt[0];
				if (skey==rkey) return (void**)&kt[1];
				if (skey>rkey) {b+=(count>>1)+1;count--;}
				count=count>>1;
			}
		}

		return 0;
	}

// ** const void string map

	void ** _APICALL _MCSPAddDEF(void * list,void *key,void *val,unsigned _int32 max)
	{
		if (!list) return 0;
		unsigned _int32 count=*(unsigned _int32*)list;
		if (max<=count) return 0;
		unsigned _int32 pos=0;
		char *rkey=0;
		char *skey=(char*)key;
		char *p=(char*)list;
		p+=4;
		Element *b=(Element *)p;
		unsigned _int32 a=count;
		unsigned _int32 apos=0;
		int cmp=-1; 
		while (apos<a) {
			pos=((apos+a)>>1);
			rkey=(char*)b[pos].key;
			cmp=extFunctions.SubMem(skey,rkey,*skey+1);
			if (cmp==0) break;
			if (cmp<0) {
				apos=pos+1;
			} else {
				a=pos;
			}
		}
		pos=a;
		if (pos<count) rkey=(char*)b[pos].key;

		if ((!rkey) || (cmp!=0)) {
			count++;
			*(unsigned _int32*)list=count;
			while (count>pos+1) {
				count--;
				b[count].key=b[count-1].key;
				b[count].val=b[count-1].val;
			}
			b[pos].key=key;
			b[pos].val=val;
			return (void**)&b[pos].key;
		} else {
			return (void**)&b[pos].key;
		}
	}

	void ** _APICALL _MCSPFindDEF(void * list,void *key)
	{
		if (!list) return 0;
		unsigned _int32 count= *(unsigned _int32*)list;
		char *p=(char*)list;
		p+=4;
		Element *b=(Element *)p;

		char *skey=(char*)key;

		while (count>0) {
			char** rkey=(char**)&b[count>>1];
			int cmp=extFunctions.SubMem(skey,*rkey,*skey+1);
			if (cmp==0) return (void**)&rkey[1];
			if (cmp<0) {b+=(count>>1)+1;count--;}
			count=count>>1;
		}

		return 0;
	}

// ** all arrays

	void * _APICALL _MPArrayDEF(void **list)
	{
		if (!list) return 0;
		if (!*list) return 0;
		char *p=(char*)*list;
		p+=4;
		return (void**)p;
	}

	unsigned _int32 _APICALL _MPCountDEF(void **list)
	{
		if (!list) return 0;
		if (!*list) return 0;
		return **(unsigned _int32**)list;
	}

};

OPTIMIZE_OFF;
WARNING_ENABLE;