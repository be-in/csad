/*
 *  qnxtimer.cpp
 *
 *  Created on: 15.08.2013
 *      Author: Пантелеймонов Александр
 */

#include <platform/platformapi.h>

#if defined (OS_QNX)

#include <platform.h>

OPTIMIZE_ON;

namespace csad {

Timer::Timer()
{
	p_rate=1.0f;
	p_avgfps=0;
	p_lps=0;
	p_fps=0;
	p_avgfps=0;
	p_avglps=0;
}

double Timer::getDelta(TicType tic)
{
	return p_tics[tic]*p_rate;
}

double Timer::getFPS()
{
	return p_avgfps;
}

double Timer::getLPS()
{
	return p_avgfps;
}

void Timer::setRate(double rate)
{
	p_rate=rate;
}

void Timer::tic(TicType tic)
{
	if (tic>=End) return;
	struct timespec t2;
	clock_gettime(CLOCK_REALTIME,&t2);
	long r=t2.tv_nsec-p_t2;
	if (r<0) r+=1000000000;
	double delta = (r)*0.000000001;
	p_t2=t2.tv_nsec;
	if ((tic!=Begin) && (tic<End)) p_tics[tic]=delta;
}

void Timer::updateLoop()
{
	struct timespec t2;
	clock_gettime(CLOCK_REALTIME,&t2);
	long r=t2.tv_nsec-p_t1;
	if (r<0) r+=1000000000;
	double delta = (r)*0.000000001;
	p_t1 = t2.tv_nsec;
	if (delta>0) {
		p_lps = 1.0/(delta);
		p_avglps += p_lps;
		p_avglps = p_avglps*0.5;
		p_tics[Begin]=delta;
	}
	p_fps+=delta;
}

void Timer::updateFrame()
{
	if (p_fps>0) {
		p_fps=1.0/p_fps;
		p_avgfps += p_fps;
		p_avgfps = p_avgfps*0.5;
		p_fps=0;
	}
}

}

OPTIMIZE_OFF;

#endif