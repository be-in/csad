/*
 * interfacethreadsystem.h
 *
 *  Created on: 09.04.2014
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef INTERFACETHREADSYSTEM_H_
#define INTERFACETHREADSYSTEM_H_

#include <core/csadapi.h>
#include <bt.h>

OPTIMIZE_ON;

namespace csad {

class Thread;

class CSAD_API InterfaceThreadSystem
{
public:
	MEMDEFAULT(InterfaceThreadSystem)

	InterfaceThreadSystem(int stacksize = 256);
	~InterfaceThreadSystem();

	/// the addition of a task handler
	// _func - the handler function _par1 - list of parameters _parcount1 - the number of parameters
	// _onend - завершающий обработчик _par2 - список параметров _parcount2 - количество параметров
	void addProc(void*key,void *_func,void *_par1,int _parcount1,void *_onend,void *_par2,int _parcount2,void *_broke=0);
	void removeProcs(void*key);

	void check();

	void lock(); //??
	void unlock(); //??
	bool islock(); //??

private:
	unsigned int fstacksize;
	unsigned int fstackcount;
	unsigned int fmode;
	volatile unsigned int flock;
	void *fstack;
	Thread *ftunner;
	_voidint fret;

	//start();
	void startnew();
	void run();
	void endfunction();

	friend class ThreadSheduler;
};

}

OPTIMIZE_OFF;

#endif /* INTERFACEDATASYSTEM_H_ */