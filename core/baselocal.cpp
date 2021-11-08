
#include "baselocal.h"
#include <core/containercomponents.h>

OPTIMIZE_ON;

class CP:public csad::ContainerComponents 
{
public:
	void *getlist() {return p_list;}
};

struct Element {
	void *key;
	void *val;
};

_voidint _MPQskey;
Element *_MPQb[4];
unsigned int _MPQcount[4];
_voidint _MPQrkey[4];
void **_MPQrezs[4];

void _FASTCALL _MPTe0FindDEF()
{
	if (_MPQskey>_MPQrkey[0]) {_MPQb[0]+=(_MPQcount[0]>>1)+1;_MPQcount[0]--;}
	_MPQcount[0]=_MPQcount[0]>>1;
	while (_MPQcount[0]>0) {
		void** kt0=(void**)&_MPQb[0][_MPQcount[0]>>1];
		_MPQrkey[0]=(_voidint)kt0[0];
		if (_MPQskey==_MPQrkey[0]) { *_MPQrezs[0]=(void*)kt0[1]; return;}
		if (_MPQskey>_MPQrkey[0]) {_MPQb[0]+=(_MPQcount[0]>>1)+1;_MPQcount[0]--;}
		_MPQcount[0]=_MPQcount[0]>>1;
	}
}

void _FASTCALL _MPTe1FindDEF()
{
	if (_MPQskey>_MPQrkey[1]) {_MPQb[1]+=(_MPQcount[1]>>1)+1;_MPQcount[1]--;}
	_MPQcount[1]=_MPQcount[1]>>1;
	while (_MPQcount[1]>0) {
		void** kt1=(void**)&_MPQb[0][_MPQcount[1]>>1];
		_MPQrkey[1]=(_voidint)kt1[0];
		if (_MPQskey==_MPQrkey[1]) { *_MPQrezs[1]=(void*)kt1[1]; return;}
		if (_MPQskey>_MPQrkey[1]) {_MPQb[1]+=(_MPQcount[1]>>1)+1;_MPQcount[1]--;}
		_MPQcount[1]=_MPQcount[1]>>1;
	}
}

void _FASTCALL _MPTe2FindDEF()
{
	int c=1;
	if (_MPQskey>_MPQrkey[2]) {_MPQb[2]+=(_MPQcount[2]>>1)+1;_MPQcount[2]--;}
	_MPQcount[2]=_MPQcount[2]>>1;
	while (_MPQcount[2]>0) {
		void** kt2=(void**)&_MPQb[2][_MPQcount[2]>>1];
		_MPQrkey[2]=(_voidint)kt2[0];
		if (_MPQskey==_MPQrkey[2]) { *_MPQrezs[2]=(void*)kt2[1]; return;}
		if (_MPQskey>_MPQrkey[2]) {_MPQb[2]+=(_MPQcount[2]>>1)+1;_MPQcount[2]--;}
		_MPQcount[2]=_MPQcount[2]>>1;
	}
}

void _FASTCALL _MPTe3FindDEF()
{
	if (_MPQskey>_MPQrkey[3]) {_MPQb[3]+=(_MPQcount[3]>>1)+1;_MPQcount[3]--;}
	_MPQcount[3]=_MPQcount[3]>>1;
	while (_MPQcount[3]>0) {
		void** kt3=(void**)&_MPQb[3][_MPQcount[3]>>1];
		_MPQrkey[3]=(_voidint)kt3[0];
		if (_MPQskey==_MPQrkey[3]) { *_MPQrezs[3]=(void*)kt3[1]; return;}
		if (_MPQskey>_MPQrkey[3]) {_MPQb[3]+=(_MPQcount[3]>>1)+1;_MPQcount[3]--;}
		_MPQcount[3]=_MPQcount[3]>>1;
	}
}

void _FASTCALL _MPT01FindDEF()
{
	int c=2;
	if (_MPQskey>_MPQrkey[0]) {_MPQb[0]+=(_MPQcount[0]>>1)+1;_MPQcount[0]--;}
	if (_MPQskey>_MPQrkey[1]) {_MPQb[1]+=(_MPQcount[1]>>1)+1;_MPQcount[1]--;}
	_MPQcount[0]=_MPQcount[0]>>1;
	_MPQcount[1]=_MPQcount[1]>>1;
	while (c==2) {
		void** kt0=(void**)&_MPQb[0][_MPQcount[0]>>1];
		void** kt1=(void**)&_MPQb[2][_MPQcount[1]>>1];
		_MPQrkey[0]=(_voidint)kt0[0];
		_MPQrkey[1]=(_voidint)kt1[0];
		if (_MPQskey==_MPQrkey[0]) { *_MPQrezs[0]=(void*)kt0[1]; c--;}
		if (_MPQskey==_MPQrkey[1]) { *_MPQrezs[1]=(void*)kt1[1]; c--;}
		if (c==1) {
			if (*_MPQrezs[0]!=0) {_MPTe1FindDEF(); return;}
			if (*_MPQrezs[1]!=0) {_MPTe0FindDEF(); return;}
		}
		if (c==0) return;
		if (_MPQskey>_MPQrkey[0]) {_MPQb[0]+=(_MPQcount[0]>>1)+1;_MPQcount[0]--;}
		if (_MPQskey>_MPQrkey[1]) {_MPQb[1]+=(_MPQcount[1]>>1)+1;_MPQcount[1]--;}
		_MPQcount[0]=_MPQcount[0]>>1;
		_MPQcount[1]=_MPQcount[1]>>1;
	}
}

void _FASTCALL _MPT02FindDEF()
{
	int c=2;
	if (_MPQskey>_MPQrkey[0]) {_MPQb[0]+=(_MPQcount[0]>>1)+1;_MPQcount[0]--;}
	if (_MPQskey>_MPQrkey[2]) {_MPQb[2]+=(_MPQcount[2]>>1)+1;_MPQcount[2]--;}
	_MPQcount[0]=_MPQcount[0]>>1;
	_MPQcount[2]=_MPQcount[2]>>1;
	while (c==2) {
		void** kt0=(void**)&_MPQb[0][_MPQcount[0]>>1];
		void** kt2=(void**)&_MPQb[2][_MPQcount[2]>>1];
		_MPQrkey[0]=(_voidint)kt0[0];
		_MPQrkey[2]=(_voidint)kt2[0];
		if (_MPQskey==_MPQrkey[0]) { *_MPQrezs[0]=(void*)kt0[1]; c--;}
		if (_MPQskey==_MPQrkey[2]) { *_MPQrezs[2]=(void*)kt2[1]; c--;}
		if (c==1) {
			if (*_MPQrezs[0]!=0) {_MPTe2FindDEF(); return;}
			if (*_MPQrezs[2]!=0) {_MPTe0FindDEF(); return;}
		}
		if (c==0) return;
		if (_MPQskey>_MPQrkey[0]) {_MPQb[0]+=(_MPQcount[0]>>1)+1;_MPQcount[0]--;}
		if (_MPQskey>_MPQrkey[2]) {_MPQb[2]+=(_MPQcount[2]>>1)+1;_MPQcount[2]--;}
		_MPQcount[0]=_MPQcount[0]>>1;
		_MPQcount[2]=_MPQcount[2]>>1;
	}
}

void _FASTCALL _MPT03FindDEF()
{
	int c=2;
	if (_MPQskey>_MPQrkey[0]) {_MPQb[0]+=(_MPQcount[0]>>1)+1;_MPQcount[0]--;}
	if (_MPQskey>_MPQrkey[3]) {_MPQb[3]+=(_MPQcount[3]>>1)+1;_MPQcount[3]--;}
	_MPQcount[0]=_MPQcount[0]>>1;
	_MPQcount[3]=_MPQcount[3]>>1;
	while (c==2) {
		void** kt0=(void**)&_MPQb[0][_MPQcount[0]>>1];
		void** kt3=(void**)&_MPQb[3][_MPQcount[3]>>1];
		_MPQrkey[0]=(_voidint)kt0[0];
		_MPQrkey[3]=(_voidint)kt3[0];
		if (_MPQskey==_MPQrkey[0]) { *_MPQrezs[0]=(void*)kt0[1]; c--;}
		if (_MPQskey==_MPQrkey[3]) { *_MPQrezs[3]=(void*)kt3[1]; c--;}
		if (c==1) {
			if (*_MPQrezs[0]!=0) {_MPTe3FindDEF(); return;}
			if (*_MPQrezs[3]!=0) {_MPTe0FindDEF(); return;}
		}
		if (c==0) return;
		if (_MPQskey>_MPQrkey[0]) {_MPQb[0]+=(_MPQcount[0]>>1)+1;_MPQcount[0]--;}
		if (_MPQskey>_MPQrkey[3]) {_MPQb[3]+=(_MPQcount[3]>>1)+1;_MPQcount[3]--;}
		_MPQcount[0]=_MPQcount[0]>>1;
		_MPQcount[3]=_MPQcount[3]>>1;
	}
}

void _FASTCALL _MPT12FindDEF()
{
	int c=2;
	if (_MPQskey>_MPQrkey[1]) {_MPQb[0]+=(_MPQcount[1]>>1)+1;_MPQcount[1]--;}
	if (_MPQskey>_MPQrkey[2]) {_MPQb[2]+=(_MPQcount[2]>>1)+1;_MPQcount[2]--;}
	_MPQcount[1]=_MPQcount[1]>>1;
	_MPQcount[2]=_MPQcount[2]>>1;
	while (c==2) {
		void** kt1=(void**)&_MPQb[1][_MPQcount[1]>>1];
		void** kt2=(void**)&_MPQb[2][_MPQcount[2]>>1];
		_MPQrkey[1]=(_voidint)kt1[0];
		_MPQrkey[2]=(_voidint)kt2[0];
		if (_MPQskey==_MPQrkey[1]) { *_MPQrezs[1]=(void*)kt1[1]; c--;}
		if (_MPQskey==_MPQrkey[2]) { *_MPQrezs[2]=(void*)kt2[1]; c--;}
		if (c==1) {
			if (*_MPQrezs[1]!=0) {_MPTe2FindDEF(); return;}
			if (*_MPQrezs[2]!=0) {_MPTe1FindDEF(); return;}
		}
		if (c==0) return;
		if (_MPQskey>_MPQrkey[1]) {_MPQb[1]+=(_MPQcount[1]>>1)+1;_MPQcount[1]--;}
		if (_MPQskey>_MPQrkey[2]) {_MPQb[2]+=(_MPQcount[2]>>1)+1;_MPQcount[2]--;}
		_MPQcount[1]=_MPQcount[1]>>1;
		_MPQcount[2]=_MPQcount[2]>>1;
	}
}

void _FASTCALL _MPT13FindDEF()
{
	int c=2;
	if (_MPQskey>_MPQrkey[1]) {_MPQb[0]+=(_MPQcount[1]>>1)+1;_MPQcount[1]--;}
	if (_MPQskey>_MPQrkey[3]) {_MPQb[3]+=(_MPQcount[3]>>1)+1;_MPQcount[3]--;}
	_MPQcount[1]=_MPQcount[1]>>1;
	_MPQcount[3]=_MPQcount[3]>>1;
	while (c==2) {
		void** kt1=(void**)&_MPQb[1][_MPQcount[1]>>1];
		void** kt3=(void**)&_MPQb[3][_MPQcount[3]>>1];
		_MPQrkey[1]=(_voidint)kt1[0];
		_MPQrkey[3]=(_voidint)kt3[0];
		if (_MPQskey==_MPQrkey[1]) { *_MPQrezs[1]=(void*)kt1[1]; c--;}
		if (_MPQskey==_MPQrkey[3]) { *_MPQrezs[3]=(void*)kt3[1]; c--;}
		if (c==1) {
			if (*_MPQrezs[1]!=0) {_MPTe3FindDEF(); return;}
			if (*_MPQrezs[3]!=0) {_MPTe1FindDEF(); return;}
		}
		if (c==0) return;
		if (_MPQskey>_MPQrkey[1]) {_MPQb[1]+=(_MPQcount[1]>>1)+1;_MPQcount[1]--;}
		if (_MPQskey>_MPQrkey[3]) {_MPQb[3]+=(_MPQcount[3]>>1)+1;_MPQcount[3]--;}
		_MPQcount[1]=_MPQcount[1]>>1;
		_MPQcount[3]=_MPQcount[3]>>1;
	}
}

void _FASTCALL _MPT23FindDEF()
{
	int c=2;
	if (_MPQskey>_MPQrkey[2]) {_MPQb[2]+=(_MPQcount[2]>>1)+1;_MPQcount[2]--;}
	if (_MPQskey>_MPQrkey[3]) {_MPQb[3]+=(_MPQcount[3]>>1)+1;_MPQcount[3]--;}
	_MPQcount[2]=_MPQcount[2]>>1;
	_MPQcount[3]=_MPQcount[3]>>1;
	while (c==1) {
		void** kt2=(void**)&_MPQb[2][_MPQcount[2]>>1];
		void** kt3=(void**)&_MPQb[3][_MPQcount[3]>>1];
		_MPQrkey[2]=(_voidint)kt2[0];
		_MPQrkey[3]=(_voidint)kt3[0];
		if (_MPQskey==_MPQrkey[2]) { *_MPQrezs[2]=(void*)kt2[1]; c--;}
		if (_MPQskey==_MPQrkey[3]) { *_MPQrezs[3]=(void*)kt3[1]; c--;}
		if (c==1) {
			if (*_MPQrezs[2]!=0) {_MPTe3FindDEF(); return;}
			if (*_MPQrezs[3]!=0) {_MPTe2FindDEF(); return;}
		}
		if (c==0) return;
		if (_MPQskey>_MPQrkey[2]) {_MPQb[2]+=(_MPQcount[2]>>1)+1;_MPQcount[2]--;}
		if (_MPQskey>_MPQrkey[3]) {_MPQb[3]+=(_MPQcount[3]>>1)+1;_MPQcount[3]--;}
		_MPQcount[2]=_MPQcount[2]>>1;
		_MPQcount[3]=_MPQcount[3]>>1;
	}
}

void _FASTCALL _MPT0FindDEF()
{
	int c=3;
	if (_MPQskey>_MPQrkey[1]) {_MPQb[0]+=(_MPQcount[1]>>1)+1;_MPQcount[1]--;}
	if (_MPQskey>_MPQrkey[2]) {_MPQb[2]+=(_MPQcount[2]>>1)+1;_MPQcount[2]--;}
	if (_MPQskey>_MPQrkey[3]) {_MPQb[3]+=(_MPQcount[3]>>1)+1;_MPQcount[3]--;}
	_MPQcount[1]=_MPQcount[1]>>1;
	_MPQcount[2]=_MPQcount[2]>>1;
	_MPQcount[3]=_MPQcount[3]>>1;
	while (c==3) {
		void** kt1=(void**)&_MPQb[1][_MPQcount[1]>>1];
		void** kt2=(void**)&_MPQb[2][_MPQcount[2]>>1];
		void** kt3=(void**)&_MPQb[3][_MPQcount[3]>>1];
		_MPQrkey[1]=(_voidint)kt1[0];
		_MPQrkey[2]=(_voidint)kt2[0];
		_MPQrkey[3]=(_voidint)kt3[0];
		if (_MPQskey==_MPQrkey[1]) { *_MPQrezs[1]=(void*)kt1[1]; c--;}
		if (_MPQskey==_MPQrkey[2]) { *_MPQrezs[2]=(void*)kt2[1]; c--;}
		if (_MPQskey==_MPQrkey[3]) { *_MPQrezs[3]=(void*)kt3[1]; c--;}
		if (c==2) {
			if (*_MPQrezs[1]!=0) {_MPT23FindDEF(); return;}
			if (*_MPQrezs[2]!=0) {_MPT13FindDEF(); return;}
			if (*_MPQrezs[3]!=0) {_MPT12FindDEF(); return;}
		}
		if (c==1) {
			if (*_MPQrezs[1]==0) {_MPTe1FindDEF(); return;}
			if (*_MPQrezs[2]==0) {_MPTe2FindDEF(); return;}
			if (*_MPQrezs[3]==0) {_MPTe3FindDEF(); return;}
		}
		if (c==0) return;
		if (_MPQskey>_MPQrkey[1]) {_MPQb[1]+=(_MPQcount[1]>>1)+1;_MPQcount[1]--;}
		if (_MPQskey>_MPQrkey[2]) {_MPQb[2]+=(_MPQcount[2]>>1)+1;_MPQcount[2]--;}
		if (_MPQskey>_MPQrkey[3]) {_MPQb[3]+=(_MPQcount[3]>>1)+1;_MPQcount[3]--;}
		_MPQcount[1]=_MPQcount[1]>>1;
		_MPQcount[2]=_MPQcount[2]>>1;
		_MPQcount[3]=_MPQcount[3]>>1;
	}
}

void _FASTCALL _MPT1FindDEF()
{
	int c=3;
	if (_MPQskey>_MPQrkey[0]) {_MPQb[0]+=(_MPQcount[0]>>1)+1;_MPQcount[0]--;}
	if (_MPQskey>_MPQrkey[2]) {_MPQb[2]+=(_MPQcount[2]>>1)+1;_MPQcount[2]--;}
	if (_MPQskey>_MPQrkey[3]) {_MPQb[3]+=(_MPQcount[3]>>1)+1;_MPQcount[3]--;}
	_MPQcount[0]=_MPQcount[0]>>1;
	_MPQcount[2]=_MPQcount[2]>>1;
	_MPQcount[3]=_MPQcount[3]>>1;
	while (c==3) {
		void** kt0=(void**)&_MPQb[0][_MPQcount[0]>>1];
		void** kt2=(void**)&_MPQb[2][_MPQcount[2]>>1];
		void** kt3=(void**)&_MPQb[3][_MPQcount[3]>>1];
		_MPQrkey[0]=(_voidint)kt0[0];
		_MPQrkey[2]=(_voidint)kt2[0];
		_MPQrkey[3]=(_voidint)kt3[0];
		if (_MPQskey==_MPQrkey[0]) { *_MPQrezs[0]=(void*)kt0[1]; c--;}
		if (_MPQskey==_MPQrkey[2]) { *_MPQrezs[2]=(void*)kt2[1]; c--;}
		if (_MPQskey==_MPQrkey[3]) { *_MPQrezs[3]=(void*)kt3[1]; c--;}
		if (c==2) {
			if (*_MPQrezs[0]!=0) {_MPT23FindDEF(); return;}
			if (*_MPQrezs[2]!=0) {_MPT03FindDEF(); return;}
			if (*_MPQrezs[3]!=0) {_MPT02FindDEF(); return;}
		}
		if (c==1) {
			if (*_MPQrezs[0]==0) {_MPTe0FindDEF(); return;}
			if (*_MPQrezs[2]==0) {_MPTe2FindDEF(); return;}
			if (*_MPQrezs[3]==0) {_MPTe3FindDEF(); return;}
		}
		if (c==0) return;
		if (_MPQskey>_MPQrkey[0]) {_MPQb[0]+=(_MPQcount[0]>>1)+1;_MPQcount[0]--;}
		if (_MPQskey>_MPQrkey[2]) {_MPQb[2]+=(_MPQcount[2]>>1)+1;_MPQcount[2]--;}
		if (_MPQskey>_MPQrkey[3]) {_MPQb[3]+=(_MPQcount[3]>>1)+1;_MPQcount[3]--;}
		_MPQcount[0]=_MPQcount[0]>>1;
		_MPQcount[2]=_MPQcount[2]>>1;
		_MPQcount[3]=_MPQcount[3]>>1;
	}
}

void _FASTCALL _MPT2FindDEF()
{
	int c=3;
	if (_MPQskey>_MPQrkey[0]) {_MPQb[0]+=(_MPQcount[0]>>1)+1;_MPQcount[0]--;}
	if (_MPQskey>_MPQrkey[1]) {_MPQb[1]+=(_MPQcount[1]>>1)+1;_MPQcount[1]--;}
	if (_MPQskey>_MPQrkey[3]) {_MPQb[3]+=(_MPQcount[3]>>1)+1;_MPQcount[3]--;}
	_MPQcount[0]=_MPQcount[0]>>1;
	_MPQcount[1]=_MPQcount[1]>>1;
	_MPQcount[3]=_MPQcount[3]>>1;
	while (c==3) {
		void** kt0=(void**)&_MPQb[0][_MPQcount[0]>>1];
		void** kt1=(void**)&_MPQb[1][_MPQcount[1]>>1];
		void** kt3=(void**)&_MPQb[3][_MPQcount[3]>>1];
		_MPQrkey[0]=(_voidint)kt0[0];
		_MPQrkey[1]=(_voidint)kt1[0];
		_MPQrkey[3]=(_voidint)kt3[0];
		if (_MPQskey==_MPQrkey[0]) { *_MPQrezs[0]=(void*)kt0[1]; c--;}
		if (_MPQskey==_MPQrkey[1]) { *_MPQrezs[1]=(void*)kt1[1]; c--;}
		if (_MPQskey==_MPQrkey[3]) { *_MPQrezs[3]=(void*)kt3[1]; c--;}
		if (c==2) {
			if (*_MPQrezs[0]!=0) {_MPT13FindDEF(); return;}
			if (*_MPQrezs[1]!=0) {_MPT03FindDEF(); return;}
			if (*_MPQrezs[3]!=0) {_MPT01FindDEF(); return;}
		}
		if (c==1) {
			if (*_MPQrezs[0]==0) {_MPTe0FindDEF(); return;}
			if (*_MPQrezs[1]==0) {_MPTe1FindDEF(); return;}
			if (*_MPQrezs[3]==0) {_MPTe3FindDEF(); return;}
		}
		if (c==0) return;
		if (_MPQskey>_MPQrkey[0]) {_MPQb[0]+=(_MPQcount[0]>>1)+1;_MPQcount[0]--;}
		if (_MPQskey>_MPQrkey[1]) {_MPQb[1]+=(_MPQcount[1]>>1)+1;_MPQcount[1]--;}
		if (_MPQskey>_MPQrkey[3]) {_MPQb[3]+=(_MPQcount[3]>>1)+1;_MPQcount[3]--;}
		_MPQcount[0]=_MPQcount[0]>>1;
		_MPQcount[1]=_MPQcount[1]>>1;
		_MPQcount[3]=_MPQcount[3]>>1;
	}
}

void _FASTCALL _MPT3FindDEF()
{
	int c=3;
	if (_MPQskey>_MPQrkey[0]) {_MPQb[0]+=(_MPQcount[0]>>1)+1;_MPQcount[0]--;}
	if (_MPQskey>_MPQrkey[1]) {_MPQb[1]+=(_MPQcount[1]>>1)+1;_MPQcount[1]--;}
	if (_MPQskey>_MPQrkey[2]) {_MPQb[2]+=(_MPQcount[2]>>1)+1;_MPQcount[2]--;}
	_MPQcount[0]=_MPQcount[0]>>1;
	_MPQcount[1]=_MPQcount[1]>>1;
	_MPQcount[2]=_MPQcount[2]>>1;
	while (c==3) {
		void** kt0=(void**)&_MPQb[0][_MPQcount[0]>>1];
		void** kt1=(void**)&_MPQb[2][_MPQcount[1]>>1];
		void** kt2=(void**)&_MPQb[2][_MPQcount[2]>>1];
		_MPQrkey[0]=(_voidint)kt0[0];
		_MPQrkey[1]=(_voidint)kt1[0];
		_MPQrkey[2]=(_voidint)kt2[0];
		if (_MPQskey==_MPQrkey[0]) { *_MPQrezs[0]=(void*)kt0[1]; c--;}
		if (_MPQskey==_MPQrkey[1]) { *_MPQrezs[1]=(void*)kt1[1]; c--;}
		if (_MPQskey==_MPQrkey[2]) { *_MPQrezs[2]=(void*)kt2[1]; c--;}
		if (c==2) {
			if (*_MPQrezs[0]!=0) {_MPT12FindDEF(); return;}
			if (*_MPQrezs[1]!=0) {_MPT02FindDEF(); return;}
			if (*_MPQrezs[2]!=0) {_MPT01FindDEF(); return;}
		}
		if (c==1) {
			if (*_MPQrezs[0]==0) {_MPTe0FindDEF(); return;}
			if (*_MPQrezs[1]==0) {_MPTe1FindDEF(); return;}
			if (*_MPQrezs[2]==0) {_MPTe2FindDEF(); return;}
		}
		if (c==0) return;
		if (_MPQskey>_MPQrkey[0]) {_MPQb[0]+=(_MPQcount[0]>>1)+1;_MPQcount[0]--;}
		if (_MPQskey>_MPQrkey[1]) {_MPQb[1]+=(_MPQcount[1]>>1)+1;_MPQcount[1]--;}
		if (_MPQskey>_MPQrkey[2]) {_MPQb[2]+=(_MPQcount[2]>>1)+1;_MPQcount[2]--;}
		_MPQcount[0]=_MPQcount[0]>>1;
		_MPQcount[1]=_MPQcount[1]>>1;
		_MPQcount[2]=_MPQcount[2]>>1;
	}
}

void _STDCALL _MPQFindDEF(void * containers,void *key,void **rez)
{
	if (!containers) return;
	CP **lcontainers=(CP **)containers;
	void *list0=lcontainers[0]->getlist();
	void *list1=lcontainers[1]->getlist();
	void *list2=lcontainers[2]->getlist();
	void *list3=lcontainers[3]->getlist();
	if (!list0 || !list1 || !list2 || !list3) return;
	_MPQcount[0]=*(unsigned int*)list0;
	_MPQcount[1]=*(unsigned int*)list1;
	_MPQcount[2]=*(unsigned int*)list2;
	_MPQcount[3]=*(unsigned int*)list3;
	Element *b[4];
	_MPQb[0]=(Element *)((char*)list0+4);
	_MPQb[1]=(Element *)((char*)list1+4);
	_MPQb[2]=(Element *)((char*)list2+4);
	_MPQb[3]=(Element *)((char*)list3+4);
	_MPQrezs[0]=&rez[0];
	_MPQrezs[1]=&rez[1];
	_MPQrezs[2]=&rez[2];
	_MPQrezs[3]=&rez[3];
	rez[0]=0;
	rez[1]=0;
	rez[2]=0;
	rez[3]=0;

	_MPQskey=(_voidint)key;
	int c=4;

	if (_MPQcount[0]==0) c--;
	if (_MPQcount[1]==0) c--;
	if (_MPQcount[2]==0) c--;
	if (_MPQcount[3]==0) c--;

	while (c==4) {
		void** kt0=(void**)&_MPQb[0][_MPQcount[0]>>1];
		void** kt1=(void**)&_MPQb[1][_MPQcount[1]>>1];
		void** kt2=(void**)&_MPQb[2][_MPQcount[2]>>1];
		void** kt3=(void**)&_MPQb[3][_MPQcount[3]>>1];
		_MPQrkey[0]=(_voidint)kt0[0];
		_MPQrkey[1]=(_voidint)kt1[0];
		_MPQrkey[2]=(_voidint)kt2[0];
		_MPQrkey[3]=(_voidint)kt3[0];
		if (_MPQskey==_MPQrkey[0]) { rez[0]=(void*)kt0[1]; c--;}
		if (_MPQskey==_MPQrkey[1]) { rez[1]=(void*)kt1[1]; c--;}
		if (_MPQskey==_MPQrkey[2]) { rez[2]=(void*)kt2[1]; c--;}
		if (_MPQskey==_MPQrkey[3]) { rez[3]=(void*)kt3[1]; c--;}
		if (c==3) {
			if (rez[0]!=0) {_MPT0FindDEF(); return;}
			if (rez[1]!=0) {_MPT1FindDEF(); return;}
			if (rez[2]!=0) {_MPT2FindDEF(); return;}
			if (rez[3]!=0) {_MPT3FindDEF(); return;}
		}
		if (c==2) {
			if (rez[0]==0 && rez[1]==0) {_MPT23FindDEF(); return;}
			if (rez[0]==0 && rez[2]==0) {_MPT13FindDEF(); return;}
			if (rez[0]==0 && rez[3]==0) {_MPT12FindDEF(); return;}
			if (rez[1]==0 && rez[2]==0) {_MPT03FindDEF(); return;}
			if (rez[1]==0 && rez[3]==0) {_MPT02FindDEF(); return;}
			if (rez[2]==0 && rez[3]==0) {_MPT01FindDEF(); return;}
		}
		if (c==1) {
			if (rez[0]==0) {_MPTe0FindDEF(); return;}
			if (rez[1]==0) {_MPTe1FindDEF(); return;}
			if (rez[2]==0) {_MPTe2FindDEF(); return;}
			if (rez[3]==0) {_MPTe3FindDEF(); return;}
		}
		if (c==0) return;
		if (_MPQskey>_MPQrkey[0]) {_MPQb[0]+=(_MPQcount[0]>>1)+1;_MPQcount[0]--;}
		if (_MPQskey>_MPQrkey[1]) {_MPQb[1]+=(_MPQcount[1]>>1)+1;_MPQcount[1]--;}
		if (_MPQskey>_MPQrkey[2]) {_MPQb[2]+=(_MPQcount[2]>>1)+1;_MPQcount[2]--;}
		if (_MPQskey>_MPQrkey[3]) {_MPQb[3]+=(_MPQcount[3]>>1)+1;_MPQcount[3]--;}
		_MPQcount[0]=_MPQcount[0]>>1;
		_MPQcount[1]=_MPQcount[1]>>1;
		_MPQcount[2]=_MPQcount[2]>>1;
		_MPQcount[3]=_MPQcount[3]>>1;
	}
}

int cs=0;

void _STDCALL _MPDFindDEF(void * containers,void *key,void **rez)
{
	if (!containers) return;
	rez[0]=0;
	rez[1]=0;
	CP **lcontainers=(CP **)containers;
	void *list0=lcontainers[0]->getlist();
	void *list1=lcontainers[1]->getlist();

	_voidint skey=(_voidint)key;
	unsigned int count0=0;
	unsigned int count1=0;
	Element *b0=0;
	Element *b1=0;
	if (list0) {
		count0=*(unsigned int*)list0;
		b0=(Element *)((char*)list0+4);
	}
	if (list1) {
		count1=*(unsigned int*)list1;
		b1=(Element *)((char*)list1+4);
	}

	while (count0>0 && count1>0) {
		void** kt0=(void**)&b0[count0>>1];
		void** kt1=(void**)&b1[count1>>1];
		_voidint rkey0=(_voidint)kt0[0];
		_voidint rkey1=(_voidint)kt1[0];
		if (skey==rkey0) {rez[0]=(void*)kt0[1];}
		if (skey==rkey1) {rez[1]=(void*)kt1[1];}
		if (skey>rkey0) {b0+=(count0>>1)+1;count0--;}
		if (skey>rkey1) {b1+=(count1>>1)+1;count1--;}
		count0=count0>>1;
		count1=count1>>1;
	}

	if (!rez[0]) while (count0>0) {
		void** kt0=(void**)&b0[count0>>1];
		_voidint rkey0=(_voidint)kt0[0];
		if (skey==rkey0) {rez[0]=(void*)kt0[1]; return;}
		if (skey>rkey0) {b0+=(count0>>1)+1;count0--;}
		count0=count0>>1;
	}

	if (!rez[1]) while (count1>0) {
		void** kt1=(void**)&b1[count1>>1];
		_voidint rkey1=(_voidint)kt1[0];
		if (skey==rkey1) {rez[1]=(void*)kt1[1]; return;}
		if (skey>rkey1) {b1+=(count1>>1)+1;count1--;}
		count1=count1>>1;
	}
}

OPTIMIZE_OFF;