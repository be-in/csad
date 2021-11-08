/*
* basesampler.h
*
*  @brief core, 2003-2014
*
*  Created on: 12.04.2008
*      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
*/

#include "basesampler.h"
#include "basegen.h"
#include <bt.h>

OPTIMIZE_ON;

// все не правильно
// для всех DEF функций с массивами сделать общую линейную функций с подставлением медода обработчика!

namespace gen {

	unsigned int tgsArrayTypeConvertS[8] = { 1, 2, 4, 4, 8, 8, 8, 8 };
	void* tgsArrayTypeVariantS[16] = { 0, 0, typeInt(), typeFloat(), typeDouble(), 0, 0, 0, 0, 0, bt::vector2i::t(), bt::vector2f::t(), bt::vector2d::t(), 0, 0, 0 };

	float _APICALL _constSample(void*, float) {
		return 1.0f;
	}

	float _APICALL _sinSample(void*, float inv) {
		inv = matFunctions.FScaleMod(inv - PIF, PI2F) + PIF;
		return matFunctions.FSin(inv);
	}

	float _APICALL _abssinSample(void*, float inv) {
		inv = matFunctions.FScaleMod(inv - PIF, PI2F) + PIF;
		float sincos = matFunctions.FSin(inv);
		if (sincos < 0.0f) sincos = -sincos;
		return sincos;
	}

	float _APICALL _squareSample(void*, float inv) {
		if (inv < 0.0f) inv = PIF - inv;
		float ret = 1.0f;
		if ((matFunctions.FTrunc(inv*APIF) & 1) != 0) ret = -ret;
		return ret;
	}

	float _APICALL _trianglSample(void*, float inv)
	{
		if (inv < 0.0f) inv = PIF - inv;
		inv *= APIF;
		float ret = 1.0f;
		int f = matFunctions.FTrunc(inv);
		if ((f & 1) != 0) ret = -ret;
		inv -= f;
		inv *= 2.0f;
		if (inv > 1.0f) inv = 2.0f - inv;
		return inv*ret;
	}

	float _APICALL _sawSample(void* ,float inv)
	{
		if (inv < 0) inv = PIF - inv;
		inv *= API2F;
		int f = matFunctions.FTrunc(inv);
		return 1.0f - (inv-f) * 2.0f;
	}

	float _APICALL _noiseSample(void*, float) {
		return ((extFunctions.NoiseGet() & 0xFFFF) * 0.0000152587890625f - 0.5f);
	}

	float _APICALL _clampSample(void*data, float clamp) {
		float *lda = (float*)data;
		float ret = *lda;
		if (ret > clamp) ret=clamp;
		if (ret < -clamp) ret = -clamp;
		return ret;
	}

	bt::tfSTDCALL_float_FUNC_p_float tgsArrayFormsSample[] = { &_constSample, &_sinSample, &_abssinSample, &_trianglSample, &_sawSample, &_noiseSample, &_clampSample };

	void* CreateSampleDEF( int len,int flagtype)
	{
		int bpp = flagtype >> 4;
		if (bpp>4) return 0;
		Sample *sample = new Sample();
		sample->flagtype = flagtype;
		sample->length = len;
		if (bpp > 7) bpp = 7;
		int step = (flagtype & 0xF) * tgsArrayTypeConvertS[bpp];
		sample->data = extFunctions.CreateMem(len * step, 0);
	}

	struct _InDataSamler {
		char *data;
		int bpp;
		int mode;
		int step;
		int llen;
		float frec;
		float amp;
		float phasepos;
		float k1;
		float k2;
		bt::tfSTDCALL_float_FUNC_p_float fun;
	};

	bool _initSample(_InDataSamler *_s_datac, void *sample, int start, int len)
	{
		extFunctions.CleanMem(_s_datac, sizeof(_InDataSamler));
		Sample *sa = (Sample *)sample;
		_s_datac->bpp = sa->flagtype >> 4;
		if (_s_datac->bpp > 7) return false;
		_s_datac->step = (sa->flagtype & 0xF) * tgsArrayTypeConvertS[_s_datac->bpp];
		_s_datac->data = (char*)sa->data;
		_s_datac->llen = sa->length - start;
		if (_s_datac->llen > len) _s_datac->llen = len;
		return true;
	}

	void _SamplerSampleFloat(_InDataSamler *_s_datac)
	{
		float phasepos = _s_datac->phasepos;
		float frec = _s_datac->frec;
		float k1 = _s_datac->k1;
		float k2 = _s_datac->k2;
		int step = _s_datac->step;
		char *ldata = _s_datac->data;
		int llen = llen;
		while (llen > 0) {
			*(float*)ldata = _s_datac->amp*_s_datac->fun(ldata, (phasepos)*PI2F*frec);
			ldata += step;
			frec += k1;
			k1 += k2;
			phasepos += 1.0f;
			llen--;
		}
	}

	void SamplerSampleDEF(void *sample, int form,int start, int len, float frec, float amp, float phase, float speed, float subspeed)
	{
		_InDataSamler s;
		if (_initSample(&s, sample, start, len)) return;
		s.fun = tgsArrayFormsSample[form];
		s.phasepos = phase;
		s.frec = frec;
		s.k1 = 1.0f / speed;
		s.k2 = 1.0f / subspeed;
		s.amp = amp;
		if (s.bpp == 3) _SamplerSampleFloat(&s);
	}

	void SamplerConstDEF(void *sample, int form, int start, int len, float amp)
	{
		_InDataSamler s;
		if (_initSample(&s, sample, start, len)) return;
		s.fun = &_constSample;
		s.amp = amp;
		if (s.bpp == 3) _SamplerSampleFloat(&s);
	}

	void SamplerDistortionDEF(void *sample, int from, int len, float amp, float grain)
	{
		_InDataSamler s;
		if (_initSample(&s, sample, from, len)) return;
		s.amp = amp;
		//s.grain = grain;
		//arvFunctions.AFClamp(left, sizeof(float), -amp, +amp, llen);
		//arvFunctions.AFMulVal(left, grain, right, sizeof(float), llen);
		//if (right) {
			//arvFunctions.AFClamp(right, sizeof(float), -amp, +amp, llen);
			//arvFunctions.AFMulVal(right, grain, right, sizeof(float), llen);
		//}
	}

	void SamplerClampDEF(void *sample, int from, int len, float amp)
	{
		_InDataSamler s;
		if (_initSample(&s, sample, from, len)) return;
		s.fun = &_clampSample;
		s.amp = amp;
		if (s.bpp == 3) _SamplerSampleFloat(&s);
	}

	void SamplerFadeDEF(void *sample, int from, int len, float amp1, float amp2,float qt)
	{
		Sample *sa = (Sample *)sample;
		int bpp = sa->flagtype >> 4;
		if (bpp != 3) return;
		float *left = (float*)sa->data;
		float *right = 0;
		if (sa->flagtype & 0xF > 0) right = left + sa->length;
		int llen = sa->length - from;
		if (llen > len) llen = len;

	}

}

OPTIMIZE_OFF;