//=============================================================================
///**
// *  @file defmath.cpp
// *
// *  $Id: defmath.cpp 23.05.2012  $
// *
// *  @brief generator 3 tool, MS Visual C++ 2003-2008
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#include "basemath.h"

WARNING_DISABLE;
OPTIMIZE_ON;

namespace bt {

struct IEE754FLOAT {
	unsigned _int32 mant : 23;
	unsigned _int32 exp : 8;
	unsigned _int32 sign : 1;
};

struct IEE754DOUBLE {
	unsigned _int64 mant : 52;
	unsigned _int64 exp : 11;
	unsigned _int64 sign : 1;
};

union conv4b {
	float valfloat;
	_int32 valint;
	unsigned _int32 valuint;
	char valarray[4];
	IEE754FLOAT varIEE;
};

union conv8b {
	double valdouble;
	char valarray[8];
	_int32 valint[2];
	_int64 vallong;
	unsigned _int64 valulong;
	unsigned _int32 valuint[2];
	unsigned char valuchar[8];
	IEE754DOUBLE varIEE;
};

/*
 * 		double b=_a;
		double m=1;
		*_b=1;
		*_l=0;
		for (int i=1;i<MAX_SINE_ITER;i++) {
			*_l+=b/m;            // sin
			b=(-1.0)*b*_a;
			m*=(i*2);
			*_b+=b/m;            // cos
			b*=_a;
			m*=(i*2+1);
		}
 */

#define MAX_SINE_ITER 8

	_ALIGN float fastsindividef[]={0.5f,1.0f/6.0f,1.0f/24.0f,1.0f/120.0f,1.0f/720.0f,1.0f/5040.0f,1.0f/40320.0f,
			1.0f/362880.0f,1.0f/3628800.0f,1.0f/3.99168E7f,1.0f/4.790016E8f,1.0f/6.2270208E9f,1.0f/8.717828912E10f,1.0f/1.307674368E12f,
			(float)4.7794773323873852974382074911175e-14,(float)2.8114572543455207631989455830103e-15,0,0,0,0};

	_ALIGN double fastsindivided[]={0.5,1.0/6.0,1.0/24.0,1.0/120.0,1.0/720.0,1.0/5040.0,1.0/40320.0,
			1.0/362880.0,1.0/3628800.0,1.0/3.99168E7,1.0/4.790016E8,1.0/6.2270208E9,1.0/8.717828912E10,1.0/1.307674368E12,
			4.7794773323873852974382074911175e-14,2.8114572543455207631989455830103e-15,0,0,0,0};

	_ALIGN float fasttgdividef[]={1.0f/3,1.0f/5,1.0f/7,1.0f/9,1.0f/11,1.0f/13,1.0f/15,1.0f/17,1.0f/19,1.0f/21,1.0f/23,1.0f/25,1.0f/27,1.0f/29,1.0f/31,1.0f/33,1.0f/35};
	_ALIGN double fasttgdivided[]={1.0/3,1.0/5,1.0/7,1.0/9,1.0/11,1.0/13,1.0/15,1.0/17,1.0/19,1.0/21,1.0/23,1.0/25,1.0/27,1.0/29,1.0/31,1.0/33,1.0/35};

	_ALIGN float rotateArcTgf[]={0.92387953251128675612818318939679f,0.92387953251128675612818318939679f,-0.3826834323650897717284599840304f,0.3826834323650897717284599840304f,0.78539816339744830961566084581988f,0.4142135623730950488016887242097f,0.39269908169872415480783042290994f,3.1415926535897932384626433832795f,3.1415926535897932384626433832795f*0.5f};
	_ALIGN double rotateArcTgd[]={0.92387953251128675612818318939679,0.92387953251128675612818318939679,-0.3826834323650897717284599840304,0.3826834323650897717284599840304,0.78539816339744830961566084581988,0.4142135623730950488016887242097,0.39269908169872415480783042290994,3.1415926535897932384626433832795,3.1415926535897932384626433832795f*0.5f};

	_ALIGN float fcmsplinef[]={-1.0f,3.0f,-3.0f,1.0f,2.0f,-5.0f,4.0f,-1.0f};
	_ALIGN double fcmsplined[]={-1.0,3.0,-3.0,1.0,2.0,-5.0,4.0,-1.0};

	float _APICALL _FsqrtDEF(float _a)
	{
		if (_a==0) return 0;
		conv4b c;
		conv4b al;
		c.valfloat=_a;
		al.valuint=0x5f3504f3-(c.valuint>>1);
		float g=al.valfloat;
		//float c05=0.5f;
		float mr=g*(3.0f-c.valfloat*g*g);
		return 1.0/mr+_a*mr*0.25;
	}

	//0x7f000000
	//170141183460469231731687303715884105728.000000

	//0x7effffff
	//170141177636784644266596604262060392448
	//170141173319264429905852091742258462720

	//0x7f03519c
	//174552615061162208610858289854834278400
	//18446744073709551616

	//340282346638528859811704183484516925440

	double _APICALL _DsqrtDEF(double _a)
	{
		if (_a==0) return 0;
		double a=_a;
		conv4b c;
		conv4b al;
		c.valfloat=a;
		al.valuint=0x5f3504f3-(c.valuint>>1);
		float g=al.valfloat;
		float mr=g*(3.0-a*g*g);
		double r=2.0/mr+a*mr*0.5;
		return r*0.25+a/r;

		// Full quality, 40-50 x32, 60-70 x64
		/*double y;
		conv4b z;
		conv4b zn;
		z.valfloat=_a;
		zn.valint=0x5F3504F3-(z.valuint>>1);
		//float g=z.valuint=zn;
		float mg=0.5*zn.valfloat*(3.0-zn.valfloat*zn.valfloat*z.valfloat);
		y=0.5*mg*(3.0-mg*mg*_a);
		y=0.5*y*(3.0-y*y*_a);
		return 0.5*_a*y*(3.0-y*y*_a);*/
	}

	/*float _STDCALL _FsqrtDEF(float _a)
	{
		if (_a==0) return 0;
		_int32v l=(((*((_int32*)&  _a)>>24)&0x7F)-0x3F);
		float r=1<<l;
		if (l<0) r=1.0f/(1<<(-l));
		float c05=0.5f;
		r=(float)((r+_a/r)*c05);
		r=(float)((r+_a/r)*c05);
		r=(float)((r+_a/r)*c05);
		r=(float)((r+_a/r)*c05);
		return r;
	}

	double _STDCALL _DsqrtDEF(double _a)
	{
		if (_a==0) return 0;
		_int32 l=(((*(((_int32*)&_a)+1)>>21)&0x3FF)-0x1FF);
		double r=1<<l;
		if (l<0) r=1.0/(1<<(-l));
		double c05=0.5;
		r=(r+_a/r)*c05;
		r=(r+_a/r)*c05;
		r=(r+_a/r)*c05;
		r=(r+_a/r)*c05;
		return r;
	}*/

	float _APICALL _FFastInvSqrtDEF(float _a)
	{
		conv4b c;
		conv4b al;
		c.valfloat=_a;
		al.valuint=c.valint;
		al.valuint=0x5f3504f3-(al.valuint>>1);  //0x5F3759DF
		float g=al.valfloat;
		return g*(1.5f-0.5f*c.valfloat*g*g);
	}

	double _APICALL _DFastInvSqrtDEF(double _a)
	{
		conv4b c;
		conv4b al;
		c.valfloat=_a;
		al.valuint=c.valint;
		al.valuint=0x5f3504f3-(al.valuint>>1);  //0x5F3759DF
		float g=al.valfloat;
		return g*(1.5f-0.5f*c.valfloat*g*g);
/*		unsigned _int64 al=*(_int64*)&_a;
		unsigned _int64 bl=0x5fe6a09e667f3bcc;
		al=bl-(al>>1);  //0x5FE6EB3BE0000000
		double g=*(double*)&al;
		return g*(1.5-0.5*_a*g*g);*/
	}

	void _APICALL _FSinCosDEF(float _a,float *_b,float *_l)
	{
		float b=_a;
		*_b=1.0f;
		*_l=b;
		//_int32 i=0;
		float *fds=fastsindividef;
		float *fdse=fastsindividef+16;
		while (fds<fdse) {
			b=(float)(b*_a);
			*_b-=(float)(b*fds[0]);            // cos
			b*=_a;
			*_l-=(float)(b*fds[1]);            // sin
			b=(float)(b*_a);
			*_b+=(float)(b*fds[2]);            // cos
			b*=_a;
			*_l+=(float)(b*fds[3]);            // sin
			fds+=4;
		}
	}

	void _APICALL _DSinCosDEF(double _a,double *_b,double *_l)
	{
		double b=_a;
		*_b=1.0f;
		*_l=b;
		double *fds=fastsindivided;
		double *fdse=fastsindivided+16;
		while (fds<fdse) {
			b=(double)(b*_a);
			*_b-=(double)(b*fds[0]);            // cos
			b*=_a;
			*_l-=(double)(b*fds[1]);            // sin
			b=(double)(b*_a);
			*_b+=(double)(b*fds[2]);            // cos
			b*=_a;
			*_l+=(double)(b*fds[3]);            // sin
			fds+=4;
		}
	}

	void _APICALL _FSinCosFASTDEF(float _a,float *_cos,float *_sin)
	{
		/*float b=_a*_a;
		float c=b*b;
		float d=c*b;
		*_b=1-b*0.5+c*0.0416666666666666666667-d*0.0013888888888888889+b*d*0.0000248015873015873015873015873015; // cos
		*_l=_a-_a*b*0.166666666667+_a*c*0.00833333333333333333-_a*d*0.0001984126984126984126+_a*d*b*0.0000027557319223985890652557319223986; // sin*/
		float a2 = _a*_a;
		float a4 = a2*a2;
		float a6 = a2*a4;
		float a8 = a4*a4;
		float a10= a2*a8;
		*_cos = (1 - a2*0.5 + a4*0.04166667 - a6* 0.001388889  + a8* 0.00002480159 - a10* 0.0000002755732);
		*_sin = _a*(1 - a2*0.1666667 + a4*0.008333333 - a6*0.0001984127 + a8* 0.000002755732 - a10*0.00000002505211);
	}

	void _APICALL _DSinCosFASTDEF(double _a,double *_cos,double *_sin)
	{
		/*double b=_a*_a;
		double c=b*b;
		double d=c*b;
		*_b=1-b*0.5+c*0.041666666666666666666667-d*0.0013888888888888889+b*d*0.0000248015873015873015873015873015; // cos
		*_l=_a-_a*b*0.166666666667+_a*c*0.008333333333333333333-_a*d*0.0001984126984126984126; // sin*/
		double a2 = _a*_a;
		double a4 = a2*a2;
		double a6 = a2*a4;
		double a8 = a4*a4;
		double a10= a2*a8;
		*_cos = (1 - a2*0.5 + a4*0.04166667 - a6* 0.001388889  + a8* 0.00002480159 - a10* 0.0000002755732);
		*_sin = _a*(1 - a2*0.1666667 + a4*0.008333333 - a6*0.0001984127 + a8* 0.000002755732 - a10*0.00000002505211);
	}

	float _APICALL _FSinDEF(float _a)
	{
		float b=_a;
		float _s=b;
		for (_int32 i=0;i<MAX_SINE_ITER;i++) {
			b=(float)((-1.0)*b*_a);
			b*=_a;
			_s+=(float)(b*fastsindividef[(i<<1)+1]);            // sin
		}
		return _s;
	}

	float _APICALL _FCosDEF(float _a)
	{
		float b=_a;
		float _c=1.0f;
		for (_int32 i=0;i<MAX_SINE_ITER;i++) {
			b=(float)((-1.0)*b*_a);
			_c+=(float)(b*fastsindividef[(i<<1)]);            // cos
			b*=_a;
		}
		return _c;
	}

	double _APICALL _DSinDEF(double _a)
	{
		double b=_a;
		double _s=b;
		for (_int32 i=0;i<MAX_SINE_ITER;i++) {
			b=(double)((-1.0)*b*_a);
			b*=_a;
			_s+=(double)(b*fastsindividef[(i<<1)+1]);            // sin
		}
		return _s;
	}

	double _APICALL _DCosDEF(double _a)
	{
		double b=_a;
		double _c=1.0f;
		for (_int32 i=0;i<MAX_SINE_ITER;i++) {
			b=(double)((-1.0)*b*_a);
			_c+=(double)(b*fastsindividef[(i<<1)]);            // cos
			b*=_a;
		}
		return _c;
	}

#define M_PI ((float)3.141592653589793)
#define M_PI12 (M_PI/12.F)
#define M_PI6 (M_PI/6.F)
#define M_PI2 (M_PI/2.F)
#define SQRT3 ((float)1.732050807569)

/*float _STDCALL _FArcTgDEF(float _x,float _y) {
	float x=_y/_x;
  _int32 sta=0,sp=0;
  float x2,a;
  // check up the sign change
  if(x<0.F) {x=-x;sta|=1;}
  // check up the invertation
  if(x>1.F) {x=1.F/x;sta|=2;}
  // process shrinking the domain until x<PI/12
  while(x>M_PI12) {
    sp++; a=x+SQRT3; a=1.F/a; x*=SQRT3; x-=1.F; x*=a;
  }
  // calculation core
	x2=x*x; a=x2+1.4087812F; a=0.55913709F/a; a+=0.60310579F;
	a-=0.05160454F*x2; a*=x;
  //x2=x*x; a=x2+1.4087812F; a=0.55913709F/a; a+=0.60310579F;
  //a-=0.05160454F*x2; a*=x;
  // process until sp=0
  while(sp>0) {a+=M_PI6;sp--;}
  // invertation took place
  if(sta&2) a=M_PI2-a;
  // sign change took place
  if(sta&1) a=-a;
  return(a);
}*/

	float _APICALL _FArcTgDEF(float _x,float _y)
	{
		float _b;
		if (_x==0) _b=1;
		if (_y==0) _b=0;
		float b=0;
		float bs=0;
		float absx=_x;
		if (absx<0) absx=-absx;
		float absy=_y;
		if (absy<0) absy=-absy;
		if (absy==absx) {
			_b=0.78539816339744830961566084581988f;
		} else {
			if (absy>absx) bs=absx/absy;
			if (absy<absx) bs=absy/absx;
			if (bs<0) bs=-bs;
			if (bs>0.4142135623730950488016887242097f) {
				if (absy>absx) {
					float bsx=absx*0.92387953251128675612818318939679f-absy*0.3826834323650897717284599840304f;
					absy=absy*0.92387953251128675612818318939679f+absx*0.3826834323650897717284599840304f;
					absx=bsx;
					b=absx/absy;
				}
				if (absy<absx) {
					float bsx=absx*0.92387953251128675612818318939679f+absy*0.3826834323650897717284599840304f;
					absy=absy*0.92387953251128675612818318939679f-absx*0.3826834323650897717284599840304f;
					absx=bsx;
					b=absy/absx;
				}
			} else b=bs;
			float a=b*b;
			_b=b;
			float *fds=fasttgdividef;
			float *fdse=fasttgdividef+8;
			while (fds<fdse) {
				b=b*a;
				_b-=b*fds[0];            // arctg
				b=b*a;
				_b+=b*fds[1];            // arctg
				b=b*a;
				_b-=b*fds[2];            // arctg
				b=b*a;
				_b+=b*fds[3];            // arctg
				fds+=4;
			}

			if (bs>0.4142135623730950488016887242097f) _b+=0.39269908169872415480783042290994f;
		}
		if (_y*_x<0) _b=-_b;
		float fs=0;
		if (absy>absx) {
			_b=-_b;
			fs=3.1415926535897932384626433832795f*0.5f;
		} else if (_x<0) {
			fs=3.1415926535897932384626433832795f;
		}
		if (_y<0) {_b-=fs;} else {_b+=fs;}
		return _b;
	}

	double _APICALL _DArcTgDEF(double _x,double _y)
	{
		double _b;
		if (_x==0) _b=1;
		if (_y==0) _b=0;
		double b;
		double bs;
		double absx=_x;
		if (absx<0) absx=-absx;
		double absy=_y;
		if (absy<0) absy=-absy;
		if (absy==absx) {
			_b=0.78539816339744830961566084581988;
		} else {
			if (absy>absx) bs=absx/absy;
			if (absy<absx) bs=absy/absx;
			if (bs<0) bs=-bs;
			if (bs>0.4142135623730950488016887242097) {
				if (absy>absx) {
					double bsx=absx*0.92387953251128675612818318939679-absy*0.3826834323650897717284599840304;
					absy=absy*0.92387953251128675612818318939679+absx*0.3826834323650897717284599840304;
					absx=bsx;
					b=absx/absy;
				}
				if (absy<absx) {
					double bsx=absx*0.92387953251128675612818318939679+absy*0.3826834323650897717284599840304;
					absy=absy*0.92387953251128675612818318939679-absx*0.3826834323650897717284599840304;
					absx=bsx;
					b=absy/absx;
				}
			} else b=bs;
			double a=b*b;
			_b=b;
			for (_int32 i=0;i<MAX_SINE_ITER;i++) {
				b=b*a;
				_b-=b*fasttgdivided[i<<1];            // arctg
				b=b*a;
				_b+=b*fasttgdivided[(i<<1)+1];            // arctg
			}
			if (bs>0.4142135623730950488016887242097) _b+=0.39269908169872415480783042290994;
		}
		if (_y*_x<0) _b=-_b;
		if (absy>absx) _b=-_b;
		double fs=0;
		if (absy>absx) {
			fs=3.1415926535897932384626433832795*0.5;
		} else if (_x<0) {
			fs=3.1415926535897932384626433832795;
		}
		if (_y<0) _b-=fs;
		if (_y>=0) _b+=fs;
		return _b;
	}

	float _APICALL _Fmul2NDEF(float _a,_int32 _b)
	{
		short* mexp=(short*)&_a;
		mexp[1]+=(_b<<7);
		return _a;
	}

	double _APICALL _Dmul2NDEF(double _a,_int32 _b)
	{
		short* mexp=(short*)&_a;
		mexp[3]+=(_b<<4);
		return _a;
	}

	float _APICALL _FLerpDEF(float _a,float _b,float _d)
	{
		return (_b-_a)*_d+_a;
	}

	double _APICALL _DLerpDEF(double _a,double _b,double _d)
	{
		return (_b-_a)*_d+_a;
	}

	_int32 _APICALL _FTruncDEF(float _a)
	{
		conv4b rd = *(conv4b*)&_a;
		if (rd.valint == 0) return 0;
		return ((rd.varIEE.mant | 0x00800000) >> (127 + 23 - (_int32)rd.varIEE.exp))*(1 - (((_int32)rd.varIEE.sign) << 1));
	}

	_int32 _APICALL _DTruncDEF(double _a)
	{
		conv8b rd = *(conv8b*)&_a;
		if (rd.vallong == 0) return 0;
		_int32 val0 = (1023 + 52 - (_int32)rd.varIEE.exp);
		if (val0 > 128) val0 = 128;
		return ((rd.varIEE.mant | 0x0010000000000000) >> val0)*(1 - (((_int32)rd.varIEE.sign) << 1));
	}

	_int64 _APICALL _DTruncLDEF(double _a)
	{
		conv8b rd = *(conv8b*)&_a;
		if (rd.vallong == 0) return 0;
		_int32 val0 = (1023 + 52 - (_int32)rd.varIEE.exp);
		if (val0 > 128) val0 = 128;
		return ((rd.varIEE.mant | 0x0010000000000000) >> val0)*(1 - (((_int32)rd.varIEE.sign) << 1));
	}

	_int32 _APICALL _FRoundDEF(float _a)
	{
		conv4b rd = *(conv4b*)&_a;
		if (rd.valint == 0) return 0;
		_int32 val0 = (127 + 23 - (_int32)rd.varIEE.exp);
		return ((rd.varIEE.mant + (0x008E38E3 >> (24 - val0)) + 0x800000) >> val0)*(1 - (((_int32)rd.varIEE.sign) << 1));
	}

	_int32 _APICALL _DRoundDEF(double _a)
	{
		conv8b rd = *(conv8b*)&_a;
		if (rd.vallong == 0) return 0;
		_int32 val0 = (1023 + 52 - (_int32)rd.varIEE.exp);
		if (val0 > 128) val0 = 128;
		return ((rd.varIEE.mant + (0x0011C71C71C71C71 >> (53 - val0)) + 0x0010000000000000) >> val0)*(1 - (((_int32)rd.varIEE.sign) << 1));
	}

	_int64 _APICALL _DRoundLDEF(double _a)
	{
		conv8b rd = *(conv8b*)&_a;
		if (rd.vallong == 0) return 0;
		_int32 val0 = (1023 + 52 - (_int32)rd.varIEE.exp);
		if (val0 > 128) val0 = 128;
		return ((rd.varIEE.mant + (0x0011C71C71C71C71 >> (53 - val0)) + 0x0010000000000000) >> val0)*(1 - (((_int32)rd.varIEE.sign) << 1));
	}

	float _APICALL _IToFDEF(_int32 _a)
	{
		if (_a == 0) return 0.0;
		IEE754FLOAT rd;
		if (_a < 0) {
			rd.sign = 1;
			_a = -_a;
		}
		int log = _ILog2DEF(_a);
		rd.exp = 127 + log;
		rd.mant = _a << (23 - log);
		return *((float*)&rd);
	}

	double _APICALL _IToDDEF(_int32 _a)
	{
		if (_a == 0) return 0.0;
		IEE754DOUBLE rd;
		if (_a < 0) {
			rd.sign = 1;
			_a = -_a;
		}
		int log = _ILog2DEF(_a);
		rd.exp = 1023 + log;
		rd.mant = _a << (52 - log);
		return *((double*)&rd);
	}

	double _APICALL _LToDDEF(_int64 _a)
	{
		if (_a == 0) return 0.0;
		IEE754DOUBLE rd;
		if (_a < 0) {
			rd.sign = 1;
			_a = -_a;
		}
		int log = _LLog2DEF(_a);
		rd.exp = 1023 + log;
		rd.mant = _a << (52 - log);
		return *((double*)&rd);
	}

	_int32 _APICALL _Fmul2NTruncDEF(float _a,_int32 _b)
	{
		conv4b rd = *(conv4b*)&_a;
		if (rd.valint == 0) return 0;
		return ((rd.varIEE.mant | 0x00800000) >> (127 + 23 - (_int32)rd.varIEE.exp - _b))*(1 - (((_int32)rd.varIEE.sign) << 1));
	}

	_int32 _APICALL _Dmul2NTruncDEF(double _a,_int32 _b)
	{
		conv8b rd = *(conv8b*)&_a;
		if (rd.vallong == 0) return 0;
		return ((rd.varIEE.mant | 0x0010000000000000) >> (1023 + 52 - (_int32)rd.varIEE.exp - _b))*(1 - (((_int32)rd.varIEE.sign) << 1));
	}

	_int32 _APICALL _Fmul2NRoundDEF(float _a,_int32 _b)
	{
		conv4b rd = *(conv4b*)&_a;
		if (rd.valint == 0) return 0;
		_int32 val0 = (127 + 23 - (_int32)rd.varIEE.exp - _b);
		return ((rd.varIEE.mant + (0x008E38E3 >> (24 - val0)) + 0x800000) >> val0)*(1 - (((_int32)rd.varIEE.sign) << 1));
	}

	_int32 _APICALL _Dmul2NRoundDEF(double _a,_int32 _b)
	{
		conv8b rd = *(conv8b*)&_a;
		if (rd.vallong == 0) return 0;
		_int32 val0 = (1023 + 52 - (_int32)rd.varIEE.exp - _b);
		return ((rd.varIEE.mant + (0x0011C71C71C71C71 >> (53 - val0)) + 0x0010000000000000) >> val0)*(1 - (((_int32)rd.varIEE.sign) << 1));
	}

	float _APICALL _FScaleModDEF(float  _a, float _c)
	{
		float rd = _a;
		float invc = 1.0f / _c;
		rd *= invc;
		_int32 va = _FTruncDEF(rd);
		return (rd - va)*_c;
	}

	double _APICALL _DScaleModDEF(double  _a, double _c)
	{
		double rd = _a;
		double invc = 1.0f / _c;
		rd *= invc;
		_int32 va = _DTruncDEF(rd);
		return (rd - va)*_c;
	}

	void _APICALL _FCRCCDEF(float a,float b,float c,float d,float * cof)
	{
		float r1=a;
		float r2=b;
		float r3=c;
		float r4=d;
		float *fcoef=cof;
		fcoef[0]= - (r1) + fcmsplinef[1] * (r2) + fcmsplinef[2] * (r3) + (r4);
		fcoef[1]= 2.0f * (r1) + fcmsplinef[5] * (r2) + fcmsplinef[6] * (r3) - (r4);
		fcoef[2]= - (r1) + (r3);
		fcoef[3]= 2.0f * (r2);
	}

	void _APICALL _DCRCCDEF(double a,double b,double c,double d,double * cof)
	{
		double r1=a;
		double r2=b;
		double r3=c;
		double r4=d;
		double *fcoef=cof;
		fcoef[0]= - (r1) + fcmsplined[1] * (r2) + fcmsplined[2] * (r3) + (r4);
		fcoef[1]= 2.0 * (r1) + fcmsplined[5] * (r2) + fcmsplinef[6] * (r3) - (r4);
		fcoef[2]= - (r1) + (r3);
		fcoef[3]= 2.0 * (r2);
	}

	void _APICALL _FPCRCCDEF(float **a,float *cof)
	{
		float r1=*a[0];
		float r2=*a[1];
		float r3=*a[2];
		float r4=*a[3];
		float *fcoef=cof;
		fcoef[0]= - (r1) + fcmsplinef[1] * (r2) + fcmsplinef[2] * (r3) + (r4);
		fcoef[1]= 2.0f * (r1) + fcmsplinef[5] * (r2) + fcmsplinef[6] * (r3) - (r4);
		fcoef[2]= - (r1) + (r3);
		fcoef[3]= 2.0f * (r2);
	}

	void _APICALL _DPCRCCDEF(double **a,double *cof)
	{
		double r1=*a[0];
		double r2=*a[1];
		double r3=*a[2];
		double r4=*a[3];
		double *fcoef=cof;
		fcoef[0]= - (r1) + fcmsplined[1] * (r2) + fcmsplined[2] * (r3) + (r4);
		fcoef[1]= 2.0 * (r1) + fcmsplined[5] * (r2) + fcmsplinef[6] * (r3) - (r4);
		fcoef[2]= - (r1) + (r3);
		fcoef[3]= 2.0 * (r2);
	}

	void _APICALL _FSplineCRDEF(float * a,float * b,float c,float d)
	{
		float c1 = c * c;
		float c2 = c1 * c;
		*b = (a[0]*c2+a[1]*c1+a[2]*c+a[3])*d;
	}

	void _APICALL _DSplineCRDEF(double *a,double *b,double c,double d)
	{
		double c1 = c * c;
		double c2 = c1 * c;
		*b = (a[0]*c2+a[1]*c1+a[2]*c+a[3])*d;
	}

	float _APICALL _FExpDEF(float _a)
	{
		float b=_a;
		float r=1+_a;
		float *fds=fastsindividef;
		float *fdse=fastsindividef+16;
		while (fds<fdse) {
			b=(float)(b*_a);
			r+=b*fds[0];
			b=(float)(b*_a);
			r+=b*fds[1];
			fds+=2;
		}
		return r;
	}

	double _APICALL _DExpDEF(double _a)
	{
		double b=_a;
		double r=1+_a;
		for (_int32 i=0;i<MAX_SINE_ITER;i++) {
			b*=_a;
			r+=(double)(b*fastsindivided[i<<1]);
			b*=_a;
			r+=(double)(b*fastsindivided[(i<<1)+1]);
		}
		return r;
	}

	float _APICALL _FLog2DEF(float _a)
	{
		conv4b c;
		c.valfloat=_a;
		c.valfloat=((c.valint & 0x7F800000)>>23)-127;

		conv4b d;
		d.valfloat=_a;
		d.valint=(d.valint&0x007FFFFF) | 0x3F800000;

		float rez=((((((-3.4436006e-2f*d.valfloat)+3.1821337e-1f)*d.valfloat)-1.2315303f)*d.valfloat+2.5988452f)*d.valfloat-3.3241990f)*d.valfloat+3.1157899f;
		return (d.valfloat-1.0f)*rez+c.valfloat;
	}

	double _APICALL _DLog2DEF(double _a)
	{
		if (_a<=0) return 0;
		double a=0.00048828125;
		if (_a<1) {
			_a=1.0/_a;
			a=-0.00048828125;
		}
		unsigned _int32 b=0;
		if (18446744073709551616.0<=_a) {b|=131072;_a*=5.4210108624275221700372640043497E-20;}
		if (4294967296.0<=_a) {b|=65536;_a*=0.00000000023283064365386962890625;}
		if (65536.0<=_a) {b|=32768;_a*=0.0000152587890625;}
		if (256.0<=_a) {b|=16384;_a*=0.00390625;}
		if (16.0<=_a) {b|=8192;_a*=0.0625;}
		if (4.0<=_a) {b|=4096;_a*=0.25;}
		if (2.0<=_a) {b|=2048;_a*=0.5;}
		if (1.4142135623730950488016887242097<=_a) {b|=1024;_a*=0.70710678118654752440084436210485;}
		if (1.1892071150027210667174999705605<=_a) {b|=512;_a*=0.84089641525371454303112547623321;}
		if (1.0905077326652576592070106557607<=_a) {b|=256;_a*=0.91700404320467123174354159479414;}
		if (1.0442737824274138403219664787399<=_a) {b|=128;_a*=0.95760328069857364693630563514792;}
		if (1.0218971486541166782344801347833<=_a) {b|=64;_a*=0.97857206208770013450916112581344;}
		if (1.0108892860517004600204097905619<=_a) {b|=32;_a*=0.98922801319397548412912495906558;}
		if (1.0054299011128028213513839559348<=_a) {b|=16;_a*=0.99459942348363317565247768622217;}
		if (1.0027112750502024854307455884504<=_a) {b|=8;_a*=0.99729605608547012625765991384792;}
		if (1.0013547198921082058808815267841<=_a) {b|=4;_a*=0.99864711289097017358812131808592;}
		if (1.0006771306930663566781727848746<=_a) {b|=2;_a*=0.99932332750265075236028365984374;}
		//if (1.0003385080526823129533054818562f<=_a) {r+=0.00048828125f;_a*=0.99966160649624368394219686876282f;}
		double r=b;
		if (1.0003385080526823129533054818562<=_a) {
			_a=1+(_a-1.0003385080526823129533054818562)*2953.1628373988541728190892445809;
			r+=_a;
		} else {
			_a=(_a-1)*2954.1394719448279842425365870796;
			r+=_a;
		}
		//if (1.0003385080526823129533054818562<=_a) {b|=1;_a*=0.99966160649624368394219686876282;}
		return r*a;

		/*conv8b c;
		c.valdouble=_a;

		c.valdouble=((c.valint[1] & 0x7FF00000)>>20)-1023;

		conv8b d;
		d.valdouble=_a;
		d.valint[1]=(d.valint[1]&0x000FFFFF) | 0x3FF00000;

		double rez=((((((-3.4436006e-2*d.valdouble)+3.1821337e-1)*d.valdouble)-1.2315303)*d.valdouble+2.5988452)*d.valdouble-3.3241990)*d.valdouble+3.1157899;
		return (d.valdouble-1.0f)*rez+c.valdouble;*/
	}

	_int32 _APICALL _ILog2DEF(_int32 _a)
	{
		_int32 r=0;
		_int32 _b=_a & 0xFFFF0000;
		if (_b) {r|=16;_a=_b;}
		_b=_a & 0xFF00FF00;
		if (_b) {r|=8;_a=_b;}
		_b=_a & 0xF0F0F0F0;
		if (_b) {r|=4;_a=_b;}
		_b=_a & 0xCCCCCCCC;
		if (_b) {r|=2;_a=_b;}
		_b=_a & 0xAAAAAAAA;
		if (_b) {r|=1;_a=_b;}
		return r;
	}

	_int32 _APICALL _LLog2DEF(_int64 _a)
	{
		_int32 r=0;
		_int64 _b=_a & 0xFFFFFFFF00000000;
		if (_b) {r|=32;_a=_b;}
		_b=_a & 0xFFFF0000FFFF0000;
		if (_b) {r|=16;_a=_b;}
		_b=_a & 0xFF00FF00FF00FF00;
		if (_b) {r|=8;_a=_b;}
		_b=_a & 0xF0F0F0F0F0F0F0F0;
		if (_b) {r|=4;_a=_b;}
		_b=_a & 0xCCCCCCCCCCCCCCCC;
		if (_b) {r|=2;_a=_b;}
		_b=_a & 0xAAAAAAAAAAAAAAAA;
		if (_b) {r|=1;_a=_b;}
		return r;
	}

	float _APICALL _FPoly1DEF(void* c,unsigned _int32 n,float v)
	{
		float *fc=(float*)c;
		unsigned _int32 fn=n;
		float fv=1;
		float rez=*fc;
		fc++;
		while (fn>1) {
			fv*=v;
			rez+=*fc*fv;
			fc++;
			fn--;
		}
		return rez;
	}

	double _APICALL _DPoly1DEF(void* c,unsigned _int32 n,double v)
	{
		double *fc=(double*)c;
		unsigned _int32 fn=n;
		double fv=1;
		double rez=*fc;
		fc++;
		while (fn>1) {
			fv*=v;
			rez+=*fc*fv;
			fc++;
			fn--;
		}
		return rez;
	}

	float _APICALL _FPoly2DEF(void* c,unsigned _int32 n1,unsigned _int32 n2,float v1,float v2)
	{
		float *fc=(float*)c;
		unsigned _int32 fn1=n1;
		float fv1=1;
		float rez=*fc;
		fc++;
		while (fn1>1) {
			fv1*=v1;
			rez+=*fc*fv1;
			fc++;
			fn1--;
		}
		unsigned _int32 fn2=n2;
		float fv2=1;
		while (fn2>1) {
			fv2*=v2;
			fn1=n1;
			fv1=fv2;
			rez+=*fc*fv1;
			fc++;
			while (fn1>1) {
				fv1*=v1;
				rez+=*fc*fv1;
				fc++;
				fn1--;
			}
			fn2--;
		}
		return rez;
	}

	double _APICALL _DPoly2DEF(void* c,unsigned _int32 n1,unsigned _int32 n2,double v1,double v2)
	{
		double *fc=(double*)c;
		unsigned _int32 fn1=n1;
		double fv1=1;
		double rez=*fc;
		fc++;
		while (fn1>1) {
			fv1*=v1;
			rez+=*fc*fv1;
			fc++;
			fn1--;
		}
		unsigned _int32 fn2=n2;
		double fv2=1;
		while (fn2>1) {
			fv2*=v2;
			fn1=n1;
			fv1=fv2;
			rez+=*fc*fv1;
			fc++;
			while (fn1>1) {
				fv1*=v1;
				rez+=*fc*fv1;
				fc++;
				fn1--;
			}
			fn2--;
		}
		return rez;
	}

	float _APICALL _FPolyMDEF(void* c,unsigned _int32 *n,float *v,unsigned _int32 s)
	{
		float *fc=(float*)c;
		float rez=0;
		unsigned _int32 fs=s--;
		if (fs>0) {
			rez=_FPolyMDEF(fc,n,v,fs);
			unsigned _int32 ffs=0;
			unsigned _int32 d=1;
			while (ffs<fs) {
				d*=n[ffs];
				ffs++;
			}
			fc+=d;
		} else {
			rez=*fc;
			fc++;
		}
		unsigned _int32 fn=n[fs];
		float fv=1;
		while (fn>1) {
			fv*=v[fs];
			if (fs>0) {
				rez+=_FPolyMDEF(fc,n,v,fs)*fv;
				unsigned _int32 ffs=0;
				unsigned _int32 d=1;
				while (ffs<fs) {
					d*=n[ffs];
					ffs++;
				}
				fc+=d;
			} else {
				rez=*fc*fv;
				fc++;
			}
			fn--;
		}
		return rez;
	}

	double _APICALL _DPolyMDEF(void* c,unsigned _int32 *n,double *v,unsigned _int32 s)
	{
		double *fc=(double*)c;
		double rez=0;
		unsigned _int32 fs=s--;
		if (fs>0) {
			rez=_DPolyMDEF(fc,n,v,fs);
			unsigned _int32 ffs=0;
			unsigned _int32 d=1;
			while (ffs<fs) {
				d*=n[ffs];
				ffs++;
			}
			fc+=d;
		} else {
			rez=*fc;
			fc++;
		}
		unsigned _int32 fn=n[fs];
		double fv=1;
		while (fn>1) {
			fv*=v[fs];
			if (fs>0) {
				rez+=_DPolyMDEF(fc,n,v,fs)*fv;
				unsigned _int32 ffs=0;
				unsigned _int32 d=1;
				while (ffs<fs) {
					d*=n[ffs];
					ffs++;
				}
				fc+=d;
			} else {
				rez=*fc*fv;
				fc++;
			}
			fn--;
		}
		return rez;
	}

	void _APICALL _FMinMaxDEF(float *_a,float *_b,float *_c)
	{
		float r0=_c[0];
		if (_a[0]<_b[0]) _b[0]=_a[0];
		if (_a[0]>r0) r0=_a[0];
		_c[0]=r0;
	}

	void _APICALL _DMinMaxDEF(double *_a,double *_b,double *_c)
	{
		double r0=_c[0];
		if (_a[0]<_b[0]) _b[0]=_a[0];
		if (_a[0]>r0) r0=_a[0];
		_c[0]=r0;
	}
}

OPTIMIZE_OFF;
WARNING_ENABLE;
