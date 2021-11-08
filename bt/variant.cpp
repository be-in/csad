/*
 * variant.cpp
 *
 *  Created on: 27.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <bt.h>
#include "base/baseapi.h"

OPTIMIZE_ON;

bt::sBaseTypesData t_data_base = { (void*)&"procedure", (void*)&"function", (void*)&"void*", (void*)&"bool",
	(void*)&"char*", (void*)&"int", (void*)&"long", (void*)&"float", (void*)&"double" };

namespace bt {

typedef MapVoid<void> ConvertVariants;

unsigned int p_isInit;

#define MAX_buffConstMapVoid 15
#define MAX_buffConstMapVoidSTR 15

struct buffConstMapVoid {
	unsigned int count;
	void *data[2*MAX_buffConstMapVoid];
};

buffConstMapVoid _convert={0,{0}};
ConstMapVoid<void*,tfSTDCALL_p_FUNC_p_bool,MAX_buffConstMapVoidSTR> _convert_str;

/*
#define VARIANT_VOIDTYPE 0x0000000
#define VARIANT_BOOLTYPE 0x0000001
#define VARIANT_CHARTYPE 0x0000002
#define VARIANT_CHARPOINTERTYPE 0x0000003
#define VARIANT_FLOATTYPE 0x0000004
#define VARIANT_DOUBLETYPE 0x0000005
#define VARIANT_INTTYPE 0x0000006
#define VARIANT_FLOATTYPE 0x0000007
#define VARIANT_FLOATTYPE 0x0000008
*/

Variant::Variant() {
	initFunc();
	p_data=0;
	//p_type=typePChar();
}

Variant::Variant(void *data)
{
	p_data=0;
	setVoid(data);
}

/*Variant::Variant(void *data)
{
	p_data=new char[];
	*((void **)p_data)=data;
	p_type=typePChar();
}*/

Variant::~Variant()
{
	if (p_data) extFunctions.DeleteMem(p_data,0);
	p_data=0;
//	p_type=typePChar();
}

void Variant::setVoid(void * val)
{
	//p_data=(char*)bt::internalmemmanager.cashalloc(sizeof(void *)+sizeof(void *));
	if (p_data) extFunctions.DeleteMem(p_data, 0);
	p_data = (char*)extFunctions.CreateMem(sizeof(void *)+sizeof(void *),0);
	*((void **)p_data)=(void*)typePVoid();
	*((void **)(p_data+sizeof(void *)))=val;
}

void Variant::setBool(bool val)
{
	if (p_data) extFunctions.DeleteMem(p_data, 0);
	p_data = (char*)extFunctions.CreateMem(sizeof(char)+sizeof(void *),0);
	*((void **)p_data)=(void*)typeBool();
	*((bool *)(p_data+sizeof(void *)))=val;
}

void Variant::setString(char* val)
{
	if (p_data) extFunctions.DeleteMem(p_data, 0);
	if (!val) {
		p_data=0;
		return;
	}
	char*c=val;
	while (*c!=0) {
		c++;
	}
	int i=(int)((_voidint)c-(_voidint)val+1);
	p_data = (char*)extFunctions.CreateMem(i + sizeof(void *),0);
	extFunctions.MoveMem(val,p_data+sizeof(void *),i);
	*((void **)p_data)=(void*)typePChar();
}

void Variant::setString(const char* val)
{
	setString((char*) val);
}

void Variant::setInt(_int32 val)
{
	if (p_data) extFunctions.DeleteMem(p_data, 0);
	p_data = (char*)extFunctions.CreateMem(sizeof(_int32)+sizeof(void *),0);
	*((_int32*)(p_data+sizeof(void *)))=val;
	*((void **)p_data)=(void*)typeInt();
}

void Variant::setLong(_int64 val)
{
	if (p_data) extFunctions.DeleteMem(p_data, 0);
	p_data = (char*)extFunctions.CreateMem(sizeof(_int64)+sizeof(void *),0);
	*((_int64*)(p_data+sizeof(void *)))=val;
	*((void **)p_data)=(void*)typeLong();
}

void Variant::setFloat(float val)
{
	if (p_data) extFunctions.DeleteMem(p_data, 0);
	p_data = (char*)extFunctions.CreateMem(sizeof(float)+sizeof(void *),0);
	*((float*)(p_data+sizeof(void *)))=val;
	*((void **)p_data)=(void*)typeFloat();
}

void Variant::setDouble(double val)
{
	if (p_data) extFunctions.DeleteMem(p_data, 0);
	p_data = (char*)extFunctions.CreateMem(sizeof(double)+sizeof(void *),0);
	*((double*)(p_data+sizeof(void *)))=val;
	*((void **)p_data)=(void*)typeDouble();
}

void Variant::setVector2i(vector2i *v)
{
	if (p_data) extFunctions.DeleteMem(p_data, 0);
	p_data = (char*)extFunctions.CreateMem(sizeof(vector2i)+sizeof(void *),0);
	*((vector2i*)(p_data+sizeof(void *)))=*v;
	*((void **)p_data)=(void*)vector2i::t();
}

void Variant::setVector2f(vector2f *v)
{
	if (p_data) extFunctions.DeleteMem(p_data, 0);
	p_data = (char*)extFunctions.CreateMem(sizeof(vector2f)+sizeof(void *),0);
	*((vector2f*)(p_data+sizeof(void *)))=*v;
	*((void **)p_data)=(void*)vector2f::t();
}

void Variant::setVector2d(vector2d *v)
{
	if (p_data) extFunctions.DeleteMem(p_data, 0);
	p_data = (char*)extFunctions.CreateMem(sizeof(vector2d)+sizeof(void *),0);
	*((vector2d*)(p_data+sizeof(void *)))=*v;
	*((void **)p_data)=(void*)vector2d::t();
}

void Variant::setVector3i(vector3i *v)
{
	if (p_data) extFunctions.DeleteMem(p_data, 0);
	p_data = (char*)extFunctions.CreateMem(sizeof(vector3i)+sizeof(void *),0);
	*((vector3i*)(p_data+sizeof(void *)))=*v;
	*((void **)p_data)=(void*)vector3i::t();
}

void Variant::setVector3f(vector3f *v)
{
	if (p_data) extFunctions.DeleteMem(p_data, 0);
	p_data = (char*)extFunctions.CreateMem(sizeof(vector3f)+sizeof(void *),0);
	*((vector3f*)(p_data+sizeof(void *)))=*v;
	*((void **)p_data)=(void*)vector3f::t();
}

void Variant::setVector3d(vector3d *v)
{
	if (p_data) extFunctions.DeleteMem(p_data, 0);
	p_data = (char*)extFunctions.CreateMem(sizeof(vector3d)+sizeof(void *),0);
	*((vector3d*)(p_data+sizeof(void *)))=*v;
	*((void **)p_data)=(void*)vector3d::t();
}

void Variant::setVector4i(vector4i *v)
{
	if (p_data) extFunctions.DeleteMem(p_data, 0);
	p_data = (char*)extFunctions.CreateMem(sizeof(vector4i)+sizeof(void *),0);
	*((vector4i*)(p_data+sizeof(void *)))=*v;
	*((void **)p_data)=(void*)vector4i::t();
}

void Variant::setVector4f(vector4f *v)
{
	if (p_data) extFunctions.DeleteMem(p_data, 0);
	p_data = (char*)extFunctions.CreateMem(sizeof(vector4f)+sizeof(void *),0);
	*((vector4f*)(p_data+sizeof(void *)))=*v;
	*((void **)p_data)=(void*)vector4f::t();
}

void Variant::setVector4d(vector4d *v)
{
	if (p_data) extFunctions.DeleteMem(p_data, 0);
	p_data = (char*)extFunctions.CreateMem(sizeof(vector4d)+sizeof(void *),0);
	*((vector4d*)(p_data+sizeof(void *)))=*v;
	*((void **)p_data)=(void*)vector4d::t();
}

bool Variant::getBool(bool def)
{
	if (!_getNew((void*)typeBool())) return def;
	return *((bool*)(p_data+sizeof(void*)));
}

_int32 Variant::getInt(_int32 def)
{
	if (!_getNew((void*)typeInt())) return def;
	return *((int*)(p_data+sizeof(void *)));
}

char* Variant::getString()
{
	if (!_getNew((void*)typePChar())) return 0;
	return (p_data+sizeof(void *));
}

const char * Variant::getString(const char* def)
{
	if (!_getNew((void*)typePChar())) return def;
	return (p_data+sizeof(void *));
}

float Variant::getFloat(float def)
{
	if (!_getNew((void*)typeFloat())) return def;
	return *((float*)(p_data+sizeof(void *)));
}

double Variant::getDouble(double def)
{
	if (!_getNew((void*)typeDouble())) return def;
	return *((double*)(p_data+sizeof(void *)));
}

void * Variant::getPointer()
{
	if (!_getNew((void*)typePVoid())) return 0;
	return *((void**)(p_data+sizeof(void *)));
}

vector2i &Variant::getVector2i()
{
	if (!_getNew((void*)vector2i::t())) return *(vector2i*)0;
	return *((vector2i*)(p_data+sizeof(void *)));
}

vector2f &Variant::getVector2f()
{
	if (!_getNew((void*)vector2f::t())) return *(vector2f*)0;
	return *((vector2f*)(p_data+sizeof(void *)));
}

vector2d &Variant::getVector2d()
{
	if (!_getNew((void*)vector2d::t())) return *(vector2d*)0;
	return *((vector2d*)(p_data+sizeof(void *)));
}

vector3i &Variant::getVector3i()
{
	if (!_getNew((void*)vector3i::t())) return *(vector3i*)0;
	return *((vector3i*)(p_data+sizeof(void *)));
}

vector3f &Variant::getVector3f()
{
	if (!_getNew((void*)vector3f::t())) return *(vector3f*)0;
	return *((vector3f*)(p_data+sizeof(void *)));
}

vector3d &Variant::getVector3d()
{
	if (!_getNew((void*)vector3d::t())) return *(vector3d*)0;
	return *((vector3d*)(p_data+sizeof(void *)));
}

vector4i &Variant::getVector4i()
{
	if (!_getNew((void*)vector4i::t())) return *(vector4i*)0;
	return *((vector4i*)(p_data+sizeof(void *)));
}

vector4f &Variant::getVector4f()
{
	if (!_getNew((void*)vector4f::t())) return *(vector4f*)0;
	return *((vector4f*)(p_data+sizeof(void *)));
}

vector4d &Variant::getVector4d()
{
	if (!_getNew((void*)vector4d::t())) return *(vector4d*)0;
	return *((vector4d*)(p_data+sizeof(void *)));
}

bool Variant::setType(void* type)
{
	if (!_getNew(type)) return false;
	return true;
}

unsigned int Variant::size()
{
	void *type=*((void **)p_data);
	char *data=p_data+sizeof(void *);
	if (type=typePVoid()) return sizeof(void *);
	if (type=typePChar()) return extFunctions.FindCMem(data,0,255)+1;
	if (type=typeInt()) return sizeof(_int32);
	if (type=typeBool()) return sizeof(bool);
	if (type=typeLong()) return sizeof(_int64);
	if (type=typeFloat()) return sizeof(float);
	if (type=typeDouble()) return sizeof(double);
	if (type=vector4b::t()) return sizeof(vector4b);
	if (type=vector2i::t()) return sizeof(vector2i);
	if (type=vector2f::t()) return sizeof(vector2f);
	if (type=vector2d::t()) return sizeof(vector2d);
	if (type=vector3i::t()) return sizeof(vector3i);
	if (type=vector3f::t()) return sizeof(vector3f);
	if (type=vector3d::t()) return sizeof(vector3d);
	if (type=vector4i::t()) return sizeof(vector4i);
	if (type=vector4f::t()) return sizeof(vector4f);
	if (type=vector4d::t()) return sizeof(vector4d);
	return 0;
}

void Variant::clean()
{
	if (p_data) extFunctions.DeleteMem(p_data,0);
	p_data=0;
}

void *Variant::_getNew(void *type)
{
	if (!p_data) return 0;
	void *p_type=*(void**)p_data;
	if (type==p_type) {
		return (void*)p_data;
	}
	tfSTDCALL_p_FUNC_p_bool *func;
	if (p_isInit!=VALIDED_STATE) _init();
	if (p_type!=(void*)typePChar()) {
		if (type!=(void*)typePChar()) {
			return 0;
		} else {
			func=(tfSTDCALL_p_FUNC_p_bool*)arrFunctions.MCPFind(&_convert_str,p_type);
			if (!func) return 0;
		}
	} else {
		func=(tfSTDCALL_p_FUNC_p_bool*)arrFunctions.MCPFind(&_convert,type);
		if (!func) return 0;
	}

	char *data=(char*)(*func)(p_data+sizeof(void*),false);
	if (p_data) extFunctions.DeleteMem(p_data, 0);
	p_data=data;
	*(void**)p_data=type;
	return (void*)p_data;
}

char *Variant::_copyData() const
{
	if (p_isInit!=VALIDED_STATE) _init();
	void *p_type=*(void**)p_data;
	tfSTDCALL_p_FUNC_p_bool *func=(tfSTDCALL_p_FUNC_p_bool*)arrFunctions.MCPFind(&_convert,p_type);
	if (!func) return 0;
	return (char*)(*func)(p_data+sizeof(void*),true);
}

void * _APICALL createPointer(char* data,bool eq)
{
	char *r = (char*)extFunctions.CreateMem(sizeof(void*)+sizeof(void *),0);
	if (eq) *((void **)(r+sizeof(void *)))=*((void **)data);
	return r;
}

void * _APICALL createString(char* data,bool)
{
	char *c=data;
	while (*c!=0) c++;
	int t=(int)((_voidint)c-(_voidint)data);
	char *r = (char*)extFunctions.CreateMem(t + 1 + sizeof(void *),0);
	extFunctions.MoveMem(data,(r+sizeof(void *)),t+1);
	*(void**)r=(void*)typePChar();
	return r;
}

void * _APICALL createBool(char* data,bool eq)
{
	char *r = (char*)extFunctions.CreateMem(sizeof(char)+sizeof(void *),0);
	if (eq)	*((bool*)(r+sizeof(void *)))=*((bool *)data);
	if (!eq) *((bool*)(r+sizeof(void *)))=tobool(data);
	*(void**)r=(void*)typeBool();
	return r;
}

void * _APICALL createInt(char* data,bool eq)
{
	char *r = (char*)extFunctions.CreateMem(sizeof(int)+sizeof(void *),0);
	if (eq)	*((int*)(r+sizeof(void *)))=*((int *)data);
	if (!eq) *((int*)(r+sizeof(void *)))=extFunctions.STRToI(data);
	*(void**)r=(void*)typeInt();
	return r;
}

void * _APICALL createFloat(char* data,bool eq)
{
	char *r = (char*)extFunctions.CreateMem(sizeof(float)+sizeof(void *),0);
	if (eq)	*((float*)(r+sizeof(void *)))=*((float *)data);
	if (!eq) *((float*)(r+sizeof(void *)))=extFunctions.STRToF(data);
	*(void**)r=(void*)typeFloat();
	return r;
}

void * _APICALL createDouble(char* data,bool eq)
{
	char *r = (char*)extFunctions.CreateMem(sizeof(double)+sizeof(void *),0);
	if (eq)	*((double *)(r+sizeof(void *)))=*((double *)data);
	if (!eq) *((double *)(r+sizeof(void *)))=extFunctions.STRToD(data);
	*(void**)r=(void*)typeDouble();
	return (void*)r;
}

void * _APICALL createVector2i(char* data,bool eq)
{
	char *r = (char*)extFunctions.CreateMem(sizeof(vector2i)+sizeof(void *),0);
	vector2i *t=(vector2i *)(r+sizeof(void *));
	if (eq)	*t=*((vector2i *)data);
	if (!eq) {
		todata(data,"%i %i",&t->x,&t->y);
	}
	*(void**)r=(void*)vector2i::t();
	return (void*)r;
}

void * _APICALL createVector2f(char* data,bool eq)
{
	char *r = (char*)extFunctions.CreateMem(sizeof(vector2f)+sizeof(void *),0);
	vector2f *t=(vector2f *)(r+sizeof(void *));
	if (eq)	*t=*((vector2f *)data);
	if (!eq) {
		todata(data,"%f %f",&t->x,&t->y);
	}
	*(void**)r=(void*)vector2f::t();
	return (void*)r;
}

void * _APICALL createVector2d(char* data,bool eq)
{
	char *r = (char*)extFunctions.CreateMem(sizeof(vector2d)+sizeof(void *),0);
	vector2d *t=(vector2d *)(r+sizeof(void *));
	if (eq)	*t=*((vector2d *)data);
	if (!eq) {
		todata(data,"%lf %lf",&t->x,&t->y);
	}
	*(void**)r=(void*)vector2d::t();
	return (void*)r;
}

void * _APICALL createVector3i(char* data,bool eq)
{
	char *r = (char*)extFunctions.CreateMem(sizeof(vector3i)+sizeof(void *),0);
	vector3i *t=(vector3i *)(r+sizeof(void *));
	if (eq)	*t=*((vector3i *)data);
	if (!eq) {
		todata(data,"%i %i %i",&t->x,&t->y,&t->z);
	}
	*(void**)r=(void*)vector3i::t();
	return (void*)r;
}

void * _APICALL createVector3f(char* data,bool eq)
{
	char *r = (char*)extFunctions.CreateMem(sizeof(vector3f)+sizeof(void *),0);
	vector3f *t=(vector3f *)(r+sizeof(void *));
	if (eq)	*t=*((vector3f *)data);
	if (!eq) {
		todata(data,"%f %f %f",&t->x,&t->y,&t->z);
	}
	*(void**)r=(void*)vector3f::t();
	return (void*)r;
}

void * _APICALL createVector3d(char* data,bool eq)
{
	char *r = (char*)extFunctions.CreateMem(sizeof(vector3d)+sizeof(void *),0);
	vector3d *t=(vector3d *)(r+sizeof(void *));
	if (eq)	*t=*((vector3d *)data);
	if (!eq) {
		todata(data,"%lf %lf %lf",&t->x,&t->y,&t->z);
	}
	*(void**)r=(void*)vector3d::t();
	return (void*)r;
}

void * _APICALL createVector4i(char* data,bool eq)
{
	char *r = (char*)extFunctions.CreateMem(sizeof(vector4i)+sizeof(void *),0);
	vector4i *t=(vector4i *)(r+sizeof(void *));
	if (eq)	*t=*((vector4i *)data);
	if (!eq) {
		todata(data,"%i %i %i %i",&t->x,&t->y,&t->z,&t->w);
	}
	*(void**)r=(void*)vector4i::t();
	return (void*)r;
}

void * _APICALL createVector4f(char* data,bool eq)
{
	char *r = (char*)extFunctions.CreateMem(sizeof(vector4f)+sizeof(void *),0);
	vector4f *t=(vector4f *)(r+sizeof(void *));
	if (eq)	*t=*((vector4f *)data);
	if (!eq) {
		todata(data,"%f %f %f %f",&t->x,&t->y,&t->z,&t->w);
	}
	*(void**)r=(void*)vector4f::t();
	return (void*)r;
}

void * _APICALL createVector4d(char* data,bool eq)
{
	char *r = (char*)extFunctions.CreateMem(sizeof(vector4d)+sizeof(void *),0);
	vector4d *t=(vector4d *)(r+sizeof(void *));
	if (eq)	*t=*((vector4d *)data);
	if (!eq) {
		todata(data,"%lf %lf %lf %lf",&t->x,&t->y,&t->z,&t->w);
	}
	*(void**)r=(void*)vector4d::t();
	return (void*)r;
}

void * toPChar(char *data) {
	char *c = data;
	while (*c != 0) c++;
	int ts = (int)((_voidint)c - (_voidint)data);
	char *r = (char*)extFunctions.CreateMem(ts + 1 + sizeof(void *),0);
	extFunctions.MoveMem(data, (r + sizeof(void *)), ts + 1);
	*(void**)r = (void*)typePChar();
	return (void*)r;
}

void * _APICALL readPointer(char* data,bool )
{
	char buff[64];
	void* *t=(void* *)(data);
	tochar(buff,63,"%p",*t);

	return toPChar(buff);
}

char *boolstr[2]={(char *)"false",(char *)"true"};

void * _APICALL readBool(char* data,bool )
{
	bool *t=(bool *)(data);
	char *buff=boolstr[0];
	if (*t) buff=boolstr[1];

	return toPChar(buff);
}

void * _APICALL readInt(char* data,bool )
{
	//char buff[64];
	int *t=(int *)(data);
	int val=*t;
	int len=0;
	if (val<0) {
		val=-val;
		len++;
	}
	if (val>0) len+=matFunctions.DTrunc(matFunctions.DLog2(val)*LOG10);
	len+=2;
	char *r = (char*)extFunctions.CreateMem(len + sizeof(void *),0);
	extFunctions.IToSTR((r+sizeof(void *)),len,*t);
	//tochar((r+sizeof(void *)),len-1,"%i",*t);

	//char *c=buff;
	//while (*c!=0) c++;
	//int ts=(int)((_voidint)c-(_voidint)buff);
	//char *r=new char[ts+1+sizeof(void *)];
	//extFunctions.MoveMem(buff,(r+sizeof(void *)),ts+1);
	*(void**)r=(void*)typePChar();
	return (void*)r;
}

void * _APICALL readFloat(char* data,bool )
{
	char buff[64];
	float *t=(float *)(data);
	tochar(buff,63,"%f",*t);

	return toPChar(buff);
}

void * _APICALL readDouble(char* data,bool )
{
	char buff[64];
	double *t=(double *)(data);
	tochar(buff,63,"%f",*t);

	return toPChar(buff);
}

void * _APICALL readVector2i(char* data, bool)
{
	char buff[128];
	vector2i *t = (vector2i *)(data);
	tochar(buff, 127, "%i %i", t->x, t->y);

	return toPChar(buff);
}

void * _APICALL readVector2f(char* data,bool )
{
	char buff[128];
	vector2f *t=(vector2f *)(data);
	tochar(buff,127,"%f %f",t->x,t->y);

	return toPChar(buff);
}

void * _APICALL readVector2d(char* data,bool )
{
	char buff[128];
	vector3d *t=(vector3d *)(data);
	tochar(buff,127,"%f %f",t->x,t->y);

	return toPChar(buff);
}

void * _APICALL readVector3i(char* data,bool )
{
	char buff[128];
	vector3i *t=(vector3i *)(data);
	//extFunctions.IToSTR()
	tochar(buff,127,"%i %i %i",t->x,t->y,t->z);

	return toPChar(buff);
}

void * _APICALL readVector3f(char* data,bool )
{
	char buff[128];
	vector3f *t=(vector3f *)(data);
	tochar(buff,127,"%f %f %f",t->x,t->y,t->z);

	return toPChar(buff);
}

void * _APICALL readVector3d(char* data,bool )
{
	char buff[128];
	vector3d *t=(vector3d *)(data);
	tochar(buff,127,"%f %f %f",t->x,t->y,t->z);

	return toPChar(buff);
}

void * _APICALL readVector4i(char* data,bool )
{
	char buff[128];
	vector4i *t=(vector4i *)(data);
	tochar(buff,127,"%i %i %i %i",t->x,t->y,t->z,t->w);

	return toPChar(buff);
}

void * _APICALL readVector4f(char* data,bool )
{
	char buff[128];
	vector4f *t=(vector4f *)(data);
	tochar(buff,127,"%f %f %f %f",t->x,t->y,t->z,t->w);

	return toPChar(buff);
}

void * _APICALL readVector4d(char* data,bool )
{
	char buff[128];
	vector4d *t=(vector4d *)(data);
	tochar(buff,127,"%f %f %f %f",t->x,t->y,t->z,t->w);

	return toPChar(buff); //(void*)r;
}

void Variant::_init()
{
	arrFunctions.MCPAdd(&_convert,(void*)typePVoid(),(void*)&createPointer,MAX_buffConstMapVoid);
	arrFunctions.MCPAdd(&_convert,(void*)typeBool(),(void*)&createBool,MAX_buffConstMapVoid);
	arrFunctions.MCPAdd(&_convert,(void*)typePChar(),(void*)&createString,MAX_buffConstMapVoid);
	arrFunctions.MCPAdd(&_convert,(void*)typeInt(),(void*)&createInt,MAX_buffConstMapVoid);
	arrFunctions.MCPAdd(&_convert,(void*)typeFloat(),(void*)&createFloat,MAX_buffConstMapVoid);
	arrFunctions.MCPAdd(&_convert,(void*)typeDouble(),(void*)&createDouble,MAX_buffConstMapVoid);
	arrFunctions.MCPAdd(&_convert,(void*)vector2i::t(),(void*)&createVector2i,MAX_buffConstMapVoid);
	arrFunctions.MCPAdd(&_convert,(void*)vector2f::t(),(void*)&createVector2f,MAX_buffConstMapVoid);
	arrFunctions.MCPAdd(&_convert,(void*)vector2d::t(),(void*)&createVector2d,MAX_buffConstMapVoid);
	arrFunctions.MCPAdd(&_convert,(void*)vector3i::t(),(void*)&createVector3i,MAX_buffConstMapVoid);
	arrFunctions.MCPAdd(&_convert,(void*)vector3f::t(),(void*)&createVector3f,MAX_buffConstMapVoid);
	arrFunctions.MCPAdd(&_convert,(void*)vector3d::t(),(void*)&createVector3d,MAX_buffConstMapVoid);
	arrFunctions.MCPAdd(&_convert,(void*)vector4i::t(),(void*)&createVector4i,MAX_buffConstMapVoid);
	arrFunctions.MCPAdd(&_convert,(void*)vector4f::t(),(void*)&createVector4f,MAX_buffConstMapVoid);
	arrFunctions.MCPAdd(&_convert,(void*)vector4d::t(),(void*)&createVector4d,MAX_buffConstMapVoid);

	arrFunctions.MCPAdd(&_convert_str,(void*)typePVoid(),(void*)&readPointer,MAX_buffConstMapVoidSTR);
	arrFunctions.MCPAdd(&_convert_str,(void*)typeBool(),(void*)&readBool,MAX_buffConstMapVoidSTR);
	//arrFunctions.MCPAdd(&_convert_str,(void*)typePChar(),(void*)&readPointer,9);
	arrFunctions.MCPAdd(&_convert_str,(void*)typeInt(),(void*)&readInt,MAX_buffConstMapVoidSTR);
	arrFunctions.MCPAdd(&_convert_str,(void*)typeFloat(),(void*)&readFloat,MAX_buffConstMapVoidSTR);
	arrFunctions.MCPAdd(&_convert_str,(void*)typeDouble(),(void*)&readDouble,MAX_buffConstMapVoidSTR);
	arrFunctions.MCPAdd(&_convert_str,(void*)vector2i::t(),(void*)&readVector2i,MAX_buffConstMapVoidSTR);
	arrFunctions.MCPAdd(&_convert_str,(void*)vector2f::t(),(void*)&readVector2f,MAX_buffConstMapVoidSTR);
	arrFunctions.MCPAdd(&_convert_str,(void*)vector2d::t(),(void*)&readVector2d,MAX_buffConstMapVoidSTR);
	arrFunctions.MCPAdd(&_convert_str,(void*)vector3i::t(),(void*)&readVector3i,MAX_buffConstMapVoidSTR);
	arrFunctions.MCPAdd(&_convert_str,(void*)vector3f::t(),(void*)&readVector3f,MAX_buffConstMapVoidSTR);
	arrFunctions.MCPAdd(&_convert_str,(void*)vector3d::t(),(void*)&readVector3d,MAX_buffConstMapVoidSTR);
	arrFunctions.MCPAdd(&_convert_str,(void*)vector4i::t(),(void*)&readVector4i,MAX_buffConstMapVoidSTR);
	arrFunctions.MCPAdd(&_convert_str,(void*)vector4f::t(),(void*)&readVector4f,MAX_buffConstMapVoidSTR);
	arrFunctions.MCPAdd(&_convert_str,(void*)vector4d::t(),(void*)&readVector4d,MAX_buffConstMapVoidSTR);
	p_isInit=VALIDED_STATE;
}

};

OPTIMIZE_OFF;
