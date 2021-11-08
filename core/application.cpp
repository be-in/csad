/*
 * application.cpp
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef LIB_CSAD
#ifndef CSAD_LOCAL
#include <cstdlib>
#include <iostream>
#endif
#endif

#include <core/application.h>
#include <core/corefunctions.h>
#include "base/baseapi.h"
#include "csadcore.h"
#include "config.h"
#include <core/component.h>

bool p_loop;

OPTIMIZE_ON;

void _APICALL csadStart()
{
	// base initialization
	btFunctions.InitFunc(0xFFFFFFFF);
	initPlatform();
	csad::initCore();
	initGen();
	csad::SetCore(new csad::LocalCore());
	InitClass(csad::core);
#ifdef LOG_CSAD
	csad::Log::console((char*)btFunctions.StringCPU());
#endif
	//Modules::init(); ??? a possible implementation of the description of the modules through the config
}

void _APICALL csadInit(char *config)
{
	// read configuration
	//Core
	csad::core->loadCore(config);

	// objects initialization
	csad::core->init();

	//Log::console("%i",ConteinerComponents::p_construct->count());

	//System::allSystemsStart();
}

/*void _STDCALL csadInit(const char *config)
{
	csadInit((char *)config);
}*/

void _APICALL csadRun()
{
	csad::System *system=csad::core->system();
	csad::Graph *graph=csad::core->graph();
	csad::Input *input=csad::core->input();

	p_loop=true;
	double t=0;

	csad::Timer &timer=system->getTimer();
#ifdef LOG_CSAD
	csad::Log::console("LPS FPS DELTA EVENTS RENDER SCENE BUFFER");
#endif
	while (p_loop) {
		timer.tic(csad::Timer::Begin);
		csad::core->start();
		input->updateReset();
		system->getIES().readEvents();
		input->update();

		timer.tic(csad::Timer::Events);
		graph->updateScene();
		timer.tic(csad::Timer::Scene);
		//if (!graph->isDisplayLocked())
		system->getIRS().renderTargets();
		timer.tic(csad::Timer::Render);
		graph->updateDisplay();
		timer.tic(csad::Timer::Buffer);

		csad::core->system()->getITS().check();
		csad::core->update();
		timer.tic(csad::Timer::End);
		timer.updateLoop();
		if (t>1) {
#ifdef LOG_CSAD
			csad::Log::console("%lf %lf %lf %lf %lf %lf %lf",timer.getLPS(),timer.getFPS(),timer.getDelta(),timer.getDelta(csad::Timer::Events),timer.getDelta(csad::Timer::Render),timer.getDelta(csad::Timer::Scene),timer.getDelta(csad::Timer::Buffer));
#endif
			t -= 1;
		}
		t+=timer.getDelta();
	}
	csad::core->quit();
}

OPTIMIZE_OFF;

void _APICALL csadQuit()
{
	p_loop=false;
}

void _APICALL csadDone()
{
	delete csad::core;
	coreFunctions.SetCore(0);
}

#ifndef LIB_CSAD
#ifndef CSAD_LOCAL

#if defined (OS_QNX)
int main(int argc, char *argv[]) {
	csadStart();

	const char * config="config.xml";
	if (argc==2) config=argv[1];
	csadInit((char*)config);

	csadRun();

	csadDone();
	return EXIT_SUCCESS;
}
#elif defined (OS_LINUX)
int main(int argc, char *argv[]) {
	csadStart();

	const char * config="config.xml";
	if (argc==2) config=argv[1];
	csadInit((char*)config);

	csadRun();

	csadDone();
	return EXIT_SUCCESS;
}
#elif defined (OS_WIN)
int main(HINSTANCE hInst, HINSTANCE , LPSTR lpCmdLine, INT ) {
	csadStart();
	csad::Render::hInst=hInst;
	csad::Log::setLogOut(stderr);
	const char * config="config.xml";
	if (lpCmdLine[0]!=0) config=lpCmdLine;
	csadInit((char*)config);
	csadRun();
	csadDone();
	return 0;
}

int _APICALL WinMain(HINSTANCE hInst, HINSTANCE, LPSTR lpCmdLine, INT) {
	csadStart();
	csad::Render::hInst=hInst;
	csad::File flog("log.txt",csad::File::CREATE);
	if (!flog.open()) return -1;
	csad::Log::setLogOut(&flog);
	const char * config="config.xml";
	if (lpCmdLine[0]!=0) config=lpCmdLine;
	csadInit((char*)config);
	csadRun();
	csadDone();
	flog.close();
	return 0;
}
#endif

#endif
#endif


