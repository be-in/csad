/*
 * linuxthread.h
 *
 *  Created on: 26.11.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>

#if defined (OS_LINUX)

#include <platform.h>

OPTIMIZE_ON;

namespace csad {

void* _APICALL ThreadProcExe(Thread*thread)
{
	if (thread) {
		thread->run();
		thread->terminate();
	}
	return 0;
}

Thread::Thread(bool created,tfSTDCALL_p_FUNC_p proc)
{
	mproc=(tfSTDCALL_p_FUNC_p)&ThreadProcExe;
	if (proc) mproc=(tfSTDCALL_p_FUNC_p)proc;
	if (created) {
		create();
	} else {
		mid=0;
		mhandle=0;
		mflags=TERMINATE;
	}
}

Thread::~Thread()
{
	mflags|=DESTROY;
	terminate();
}

void Thread::play()
{
	if (isTerminated()) {
		if (mhandle) int error=pthread_cancel((pthread_t )mhandle);
		create();
	}
	if (isSuspended()) {
		setPriority(mpriority);
		//if (ResumeThread((HANDLE)mhandle)>=0)
			mflags&=(~SUSPEND);
	}
}

void Thread::run()
{
}

void Thread::stop()
{
	if (isThisThread()) {
		mflags|=CONFIRM_SUSPEND;
		while ((!isSuspended()) && ((mflags&CONFIRM_SUSPEND)!=0)) {
		}
	} else {
		if ((mflags&TERMINATE)!=0) {
			create();
		}
		if ((mflags&SUSPEND)==0) {
			mflags|=SUSPEND;
			mflags&=~CONFIRM_SUSPEND;
			setPriority(0);
		}
	}
}

void Thread::create()
{
	if ((mflags&DESTROY)==0) {
		mflags=SUSPEND;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		pthread_attr_setdetachstate(&attr, PTHREAD_INHERIT_SCHED);
		
		//pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
		int error=pthread_create((pthread_t *)&mhandle,&attr,(void *(*)(void *))mproc,this);
		if (error == EPERM) {
			pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED);
			error=pthread_create((pthread_t *)&mhandle,&attr,(void *(*)(void *))mproc,this);
		}
		pthread_attr_destroy(&attr);
		if (error) mhandle=0;
		mid=mhandle;
	}
}

void Thread::terminate()
{
	mflags&=~CONFIRM_TERMINATE;
	if (!isTerminated()) {
		_voidint lid=(_voidint)pthread_self();
		if (lid!=(_voidint)mid) {
			if (isSuspended()) mflags&=(~SUSPEND);
			mflags|=TERMINATE;
			if (mhandle) {
				int error=pthread_cancel((pthread_t)mhandle);
			}
			mhandle=0;
			mid=0;
			mflags&=~CONFIRM_TERMINATE;
		} else {
			mflags|=CONFIRM_TERMINATE;
		}
	}
}

int Thread::priority()
{
	//if (mhandle) return GetThreadPriority((HANDLE)mhandle);
	return mpriority;
}

void Thread::setPriority(int prior)
{
	mpriority=prior;
	if (!mhandle) return;

	int sched_policy;
    sched_param param;
	if (pthread_getschedparam((_voidint)mhandle, &sched_policy, &param) != 0) return;
	
	int prio;
    int prio_min = sched_get_priority_min(sched_policy);
    int prio_max = sched_get_priority_max(sched_policy);
	prio=prio_min+(prior*(prio_max-prio_min)/100);
	
	param.sched_priority = prio;
	int error = pthread_setschedparam((pthread_t)mhandle, sched_policy, &param);
}

bool Thread::isThisThread()
{
	_voidint lid=(_voidint)pthread_self();
	return lid==(_voidint)mid;
}

bool Thread::isSuspended()
{
	confirm();
	return (mflags&SUSPEND)!=0;
}

bool Thread::isTerminated()
{
	confirm();
	_voidint ret;
	if (!mhandle) return true;
	if (pthread_tryjoin_np((pthread_t)mhandle,(void**)&ret)) {
	} else {
		mflags|=TERMINATE;
	}
	return (mflags&TERMINATE)!=0;
}

void* Thread::id()
{
	return (void*)pthread_self();
}

Thread* Thread::runProc(tfSTDCALL_p_FUNC_p proc,Thread *thread)
{
	if (!thread) {
		thread=new Thread(true,proc);
	} else {
		thread->terminate();
		thread->mproc=(tfSTDCALL_p_FUNC_p)proc;
		thread->create();
	}
	thread->play();
	
	return thread;
}

void Thread::confirm()
{
	if (!isThisThread()) {
		if ((mflags&CONFIRM_TERMINATE)!=0) terminate();
		if ((mflags&CONFIRM_SUSPEND)!=0) stop();
		mflags&=~(CONFIRM_TERMINATE | CONFIRM_SUSPEND);
	}
}

TYPEINFO(Thread)

}

#endif
