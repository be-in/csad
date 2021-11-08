/*
* basesampler.h
*
*  @brief core, 2003-2014
*
*  Created on: 12.04.2008
*      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
*/

#pragma once
#ifndef BASE_SAMPLER_H
#define BASE_SAMPLER_H

#include <gen3/types.h>

OPTIMIZE_ON;

namespace gen {

	void* CreateSampleDEF(int len, int flagtype);

	void SamplerSampleDEF(void *sample, int from, int len, float frec, float amp, float phase, float speed, float subspeed);

	void SamplerNoiseDEF(void *sample, int from, int len, float amp);

	void SamplerDistortionDEF(void *sample, int from, int len, float amp, float grain);

	void SamplerFadeDEF(void *sample, int from, int len, float amp1, float amp2, float qt);

}

OPTIMIZE_OFF;

#endif