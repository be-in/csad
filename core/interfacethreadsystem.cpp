/*
 * interfacethreadsystem.cpp
 *
 *  Created on: 09.04.2014
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <core/interfacethreadsystem.h>
#include <bt/macroscall.h>
#include <bt.h>
#include <platform/log.h>
#include <platform/thread.h>

OPTIMIZE_ON;

namespace csad {

struct tfunce {
	void *key;
	void *func;
	_voidint par1[7];
	_voidint parcount1;
	_voidint par2[7];
	_voidint parcount2;
	void *onend;
	void *broke;
	_voidint xorhash;
};

class ThreadSheduler;

int _APICALL ThreadRun(ThreadSheduler*thread);

class ThreadSheduler:public Thread {
public:
	MEMDEFAULT(ThreadSheduler)

	ThreadSheduler(InterfaceThreadSystem *ThreadSystem):Thread(false,(tfSTDCALL_p_FUNC_p)&ThreadRun) {mThreadSystem=ThreadSystem;}

	InterfaceThreadSystem *mThreadSystem;
	void run() {mThreadSystem->run();}
};

class ThreadManager:public csad::Thread {
public:
	MEMDEFAULT(ThreadManager)

	ThreadManager():csad::Thread() {isrun=true;}

	bool isrun;
	void run() {while (isrun) {bt::internalmemmanager.manage();}}
};

volatile int threadLock=0;

_voidint threadid=0;

_voidint _APICALL checkThread()
{
	_voidint retid=(_voidint)Thread::id();
	//if (retid==threadid) return 0;
	return retid;
}

int _APICALL ThreadRun(ThreadSheduler*thread)
{
	//while (thread->mThreadSystem->islock());
	thread->mThreadSystem->lock();
	//threadLock++;
	thread->run();
	//threadLock--;
	//while (thread->mThreadSystem->islock());
	//thread->mThreadSystem->unlock();
	//thread->terminate();
	//while (!thread->isTerminated()) {
		//thread->mThreadSystem->updateDisplay();
		//thread->stop();
	//}
	return 0;
}

ThreadManager *trm=0;

InterfaceThreadSystem::InterfaceThreadSystem(int stacksize)
{
	flock=0;
	fstacksize=stacksize;
	fstackcount=0;
	fmode=1;
	fstack=extFunctions.CreateMem(sizeof(tfunce)*(stacksize+3),0);
	ftunner=new ThreadSheduler(this);
	extFunctions.CleanMem(fstack,sizeof(tfunce)*(stacksize+3));
	threadid=(_voidint)Thread::id();
	if (!trm) trm=new ThreadManager();
	trm->play();
	bt::internalmemmanager.isThread=(bt::tfSTDCALL_uint_FUNC)&checkThread;
}

InterfaceThreadSystem::~InterfaceThreadSystem()
{
	bt::internalmemmanager.isThread=0;
	if (trm) {
		trm->isrun=false;
		while (!trm->isTerminated());
		delete trm;
		trm=0;
	}
	while (!ftunner->isTerminated());
	delete ftunner;
	extFunctions.DeleteMem(fstack,0);
	fstack=0;
}

void InterfaceThreadSystem::addProc(void *key,void *_func,void *_par1,int _parcount1,void *_onend,void *_par2,int _parcount2,void *_broke)
{
	int m=-1;
	_voidint xorhash=((_voidint)_onend) ^ ((_voidint)_func) ^ ((_voidint)key);
	for (int i=0;i<_parcount1;i++) if (_par1)
		xorhash^=((_voidint *)_par1)[i];
	for (int i=0;i<_parcount2;i++) if (_par2)
		xorhash^=((_voidint *)_par2)[i];

	tfunce *m_stack=(tfunce *)fstack;
	tfunce &m_isexec=m_stack[fstacksize];
	tfunce &m_lastadd=m_stack[fstacksize+1];

	for (unsigned int i=0;i<fstackcount;i++) if (m<0) {
		//if (m_stack[i].xorhash==xorhash) {
			m=0;
			if ((m_stack[i].func==_func) && (m_stack[i].onend==_onend) && (m_stack[i].key==key)) {
				if (_par1) for (int j=0; j<_parcount1; j++)
					if (((_voidint *)_par1)[j]!=m_stack[i].par1[j]) m=-1;
				if (_par2) for (int j=0; j<_parcount2; j++) 
					if (((_voidint *)_par2)[j]!=m_stack[i].par2[j]) m=-1;
			} else m=-1;
		//}
	}
	if (m<0) {
		if ((m_isexec.func==_func) && (m_isexec.onend==_onend) && (m_isexec.key==key)) {
			m=0;
			if (_par1) for (int j=0; j<_parcount1; j++)
				if (((_voidint *)_par1)[j]!=m_isexec.par1[j]) m=-1;
			if (_par2) for (int j=0; j<_parcount2; j++)
				if (((_voidint *)_par2)[j]!=m_isexec.par2[j]) m=-1;
		}
	}
	if (m>=0) {	
		if ((m_isexec.onend!=0) && (m_isexec.func==0)) endfunction();
		return;
	}

	if (fstackcount>=fstacksize) {
		fstackcount--;
		//skip++;
		for (unsigned int i=0;i<fstackcount;i++) m_stack[i]=m_stack[i+1];
#ifdef LOG_CSAD
		Log::console("-- TLoader: stack overflow --");
#endif
	}
	m_lastadd.key=key;
	m_lastadd.func=_func;
	if (_parcount1>0) {
		for (int i=0;i<_parcount1;i++) {
			m_lastadd.par1[i]=((_voidint *)_par1)[i];
			//printf("%i",((int *)_par1)[i]);
		}
		//printf("\n");
	}
	m_lastadd.parcount1=_parcount1;
	if (_parcount2>0) {
		for (int i=0;i<_parcount2;i++) {
			m_lastadd.par2[i]=((_voidint *)_par2)[i];
		}
	}

	m_lastadd.parcount2=_parcount2;
	m_lastadd.xorhash=xorhash;
	m_lastadd.onend=_onend;
	m_lastadd.broke=_broke;

	m_stack[fstackcount]=m_lastadd;
	extFunctions.CleanMem(&m_lastadd,sizeof(tfunce));
	fstackcount++;
	if ((m_isexec.onend!=0) && (m_isexec.func==0)) endfunction();
	if ((m_isexec.onend!=0) || (m_isexec.func!=0)) return;
	startnew();
}

void InterfaceThreadSystem::removeProcs(void*key)
{
	tfunce *m_stack=(tfunce *)fstack;
	tfunce &m_isexec=m_stack[fstacksize];
	for (unsigned int i=0;i<fstackcount;i++) {
		while (m_stack[fstackcount].key==key) {
			fstackcount--;
			for (unsigned int j=i;i<fstackcount;i++)
				m_stack[j]=m_stack[j+1];
		}
	}
	if (m_isexec.key==key) extFunctions.CleanMem(&m_isexec,sizeof(tfunce));
	ftunner->terminate();
}

void InterfaceThreadSystem::check()
{
	if (fstackcount<=0) return;
	tfunce *m_stack=(tfunce *)fstack;
	tfunce &m_isexec=m_stack[fstacksize];
	if ((m_isexec.onend!=0) && (m_isexec.func==0)) endfunction();
	if ((m_isexec.onend!=0) || (m_isexec.func!=0)) return;
	startnew();
}

void InterfaceThreadSystem::lock()
{
	if (fmode!=1) return;
	while (flock!=0) {
		if (ftunner->isTerminated()) flock=0;
	}
	//while (flock!=0x0);
	//flock++;
	flock=0x1;
}

void InterfaceThreadSystem::unlock()
{
	if (fmode!=1) return;
	//if (flock>0) flock--;
	flock=0;
}

bool InterfaceThreadSystem::islock()
{
	if (fmode!=1) return false;
	return false;//flock!=0x0;
}

_voidint funcexec(void *func,_voidint * params,unsigned int count)
{
	_voidint ret=0;
	if (count==0) ret=((_voidint (_APICALL *)())func)();
	if (count==1) ret=((_voidint (_APICALL *)(_voidint))func)(params[0]);
	if (count==2) ret=((_voidint (_APICALL *)(_voidint,_voidint))func)(params[0],params[1]);
	if (count==3) ret=((_voidint (_APICALL *)(_voidint,_voidint,_voidint))func)(params[0],params[1],params[2]);
	if (count==4) ret=((_voidint (_APICALL *)(_voidint,_voidint,_voidint,_voidint))func)(params[0],params[1],params[2],params[3]);
	if (count==5) ret=((_voidint (_APICALL *)(_voidint,_voidint,_voidint,_voidint,_voidint))func)(params[0],params[1],params[2],params[3],params[4]);
	if (count==6) ret=((_voidint (_APICALL *)(_voidint,_voidint,_voidint,_voidint,_voidint,_voidint))func)(params[0],params[1],params[2],params[3],params[4],params[5]);
	if (count==7) ret=((_voidint (_APICALL *)(_voidint,_voidint,_voidint,_voidint,_voidint,_voidint,_voidint))func)(params[0],params[1],params[2],params[3],params[4],params[5],params[6]);
	return ret;
}

void InterfaceThreadSystem::run() {
//	while (term) {
	tfunce *m_stack=(tfunce *)fstack;
	tfunce &m_isexec=m_stack[fstacksize];
	if (m_isexec.func!=NULL) {
		_voidint ret=funcexec(m_isexec.func,m_isexec.par1,(int)m_isexec.parcount1);
		fret=ret;
	}
	m_isexec.func=0;
}

void InterfaceThreadSystem::endfunction() {
	if (!ftunner->isTerminated()) return;
	if (fmode==1) {
		unlock();
		ftunner->terminate();
	}
	tfunce *m_stack=(tfunce *)fstack;
	tfunce &m_isexec=m_stack[fstacksize];
	if ((m_isexec.onend!=NULL) && (((_voidint)m_isexec.onend)!=_voidintmax)) {
		funcexec(m_isexec.onend,m_isexec.par2,(int)m_isexec.parcount2);
	}
	//furet=0;
	extFunctions.CleanMem(&m_isexec,sizeof(tfunce));
	startnew();
}

void InterfaceThreadSystem::startnew() {
	if (fstackcount<=0) return;
	if (!ftunner->isTerminated()) return;
	tfunce *m_stack=(tfunce *)fstack;
	tfunce &m_isexec=m_stack[fstacksize];
	tfunce &m_lastadd=m_stack[fstacksize+1];
	fstackcount--;
	m_lastadd=m_stack[fstackcount];
	if ((m_lastadd.func!=NULL) && ((m_lastadd.parcount1==0) || (m_lastadd.par1!=NULL)) && ((m_lastadd.parcount2==0) || (m_lastadd.par2!=NULL))) {
		if (m_isexec.onend) endfunction();
		m_isexec=m_lastadd;
		//for (int i=0;i<stackcount;i++) m_stack[i]=m_stack[i+1];
		extFunctions.CleanMem(&m_lastadd,sizeof(tfunce));
		extFunctions.CleanMem(&m_stack[fstackcount],sizeof(tfunce));
		if (fmode==0) {
			run();
			endfunction();
		}
		if (fmode==1) ftunner->play();
	}
}

}

OPTIMIZE_OFF;
