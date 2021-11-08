/*
 * wintimer.cpp
 *
 *  Created on: 15.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>

#if defined (OS_WIN)

#include <platform.h>

OPTIMIZE_ON;

namespace csad {

Timer::Timer()
{
	p_rate=1.0f;
	LARGE_INTEGER rt;
	LARGE_INTEGER ft;
	QueryPerformanceCounter(&rt);
	QueryPerformanceFrequency(&ft);
	double td2 = matFunctions.LToD(rt.QuadPart) / (2147.483648 * matFunctions.LToD(ft.QuadPart));
	unsigned int t2 = (unsigned int)matFunctions.DTrunc((td2 - matFunctions.LToD(matFunctions.DTrunc(td2))) * 2147483648.0);
	//unsigned int t2 = (unsigned int)matFunctions.DTrunc(matFunctions.LToD(rt.QuadPart)*1000000.0 / matFunctions.LToD(ft.QuadPart));
	p_t1=t2;
	p_t2=t2;
	p_avgfps=0;
	p_lps=0;
	p_fps=0;
	p_avgfps=0;
	p_avglps=0;
	for (int i=0;i<End;i++)
		p_tics[i]=0;
}

double Timer::getDelta(TicType tic)
{
	return p_tics[tic]*p_rate;
}

long long Timer::getTime()
{
	return 0;
}

void Timer::setRate(double rate)
{
	p_rate=rate;
}

void Timer::tic(TicType tic)
{
	if (tic>=End) return;
	LARGE_INTEGER rt;
	LARGE_INTEGER ft;
	QueryPerformanceCounter(&rt);
	QueryPerformanceFrequency(&ft);
	double td2 = matFunctions.LToD(rt.QuadPart) / (2147.483648 * matFunctions.LToD(ft.QuadPart));
	unsigned int t2 = (unsigned int)matFunctions.DTrunc((td2 - matFunctions.LToD(matFunctions.DTrunc(td2))) * 2147483648.0);
	//unsigned int t2 = (unsigned int)matFunctions.DTrunc(matFunctions.LToD(rt.QuadPart)*1000000.0 / matFunctions.LToD(ft.QuadPart));
	long r=t2-p_t2;
	//if (r<0) r+=100;
	double delta = (r)*0.000001;
	p_t2=t2;
	if ((tic!=Begin) && (tic<End)) p_tics[tic]=delta;
}

void Timer::updateLoop()
{
	LARGE_INTEGER rt;
	LARGE_INTEGER ft;
	QueryPerformanceCounter(&rt);
	QueryPerformanceFrequency(&ft);
	double td2 = matFunctions.LToD(rt.QuadPart) / (2147.483648 * matFunctions.LToD(ft.QuadPart));
	unsigned int t2 = (unsigned int)matFunctions.DTrunc((td2 - matFunctions.LToD(matFunctions.DTrunc(td2))) * 2147483648.0);
	//unsigned int t2 = (unsigned int)matFunctions.DTrunc(matFunctions.LToD(rt.QuadPart)*1000000.0 / matFunctions.LToD(ft.QuadPart));
	double delta = (t2-p_t1)*0.000001;
	p_t1 = t2;
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