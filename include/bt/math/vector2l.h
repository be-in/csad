/*
 * vector2l.h
 *
 *  Created on: 29.08.2013
 *      Author: Пантелеймонов Александр
 */

#ifndef VECTOR2L_H_
#define VECTOR2L_H_

#include <bt/functions.h>

namespace bt {

class vector2i;

class vector2l {
public:
	long long x;
	long long y;

	_FORCEINLINE vector2l() {}
	_FORCEINLINE vector2l(long long _x,long long _y) {x=_x;y=_y;}
	_FORCEINLINE vector2l(vector2i &_a) {int *c=(int*)&_a;x=c[0];y=c[1];}
	_FORCEINLINE vector2l(const vector2i &_a) {int *c=(int*)&_a;x=c[0];y=c[1];}
	_FORCEINLINE vector2l(vector2i *_a) {int *c=(int*)_a;x=c[0];y=c[1];}
	_FORCEINLINE ~vector2l() {}

	_FORCEINLINE bool less(const vector2l &b) {if (y!=b.y) return y<b.y; return x<b.x;}
	_FORCEINLINE bool leftOfLine(const vector2l &a,const vector2l &b) {return quadDistanceFromLine(a,b)<0;}
	_FORCEINLINE long long quadDistanceFromLine(const vector2l &a,const vector2l &b) {return vecFunctions.V2LQDFL(this,(void*)&a,(void*)&b);}
	_FORCEINLINE void zero() {x=y=0;}

	_FORCEINLINE const vector2l operator+(const vector2l &a) const {vector2l c; vecFunctions.V2LAdd((void*)this,(void*)&a,&c); return c;}
	_FORCEINLINE friend const vector2l operator+(vector2l &a, vector2l &b) {vector2l c; vecFunctions.V2LAdd(&a,&b,&c); return c;}
	_FORCEINLINE bool operator==(vector2l b) {if (x!=b.x) return false; return y==b.y;}
	_FORCEINLINE bool operator!=(vector2l b) {if (x!=b.x) return true; return y!=b.y;}

	BT_API TYPEINFO_H;
};

}

#endif /* VECTOR2L_H_ */
