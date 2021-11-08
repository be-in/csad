/*
 * qnxthread.h
 *
 *  Created on: 26.11.2013
 *      Author: Пантелеймонов А
 */
#include <platform/platformapi.h>

#if defined (OS_QNX)

#include <platform.h>

namespace csad {

int _APICALL ThreadProcExe(Thread*thread)
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
		if (mhandle) ThreadDestroy((int)mhandle,-1,0);
		create();
	}
	if (isSuspended()) {
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
			//SuspendThread((HANDLE)mhandle);
		}
	}
}

void Thread::create()
{
	if ((mflags&DESTROY)==0) {
		mflags=SUSPEND;
		//_thread_attr attr;
		//pthread_attr_init( &attr );
		//pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED );
		//mhandle=(void*)pthread_create(NULL,&attr,(void *(*)(void *))mproc,this);
		mhandle=(void*)ThreadCreate(0,(void *(*)(void *))mproc,this,0);
		mid=(int)mhandle;
	}
}

void Thread::terminate()
{
	if (!isTerminated()) {
		unsigned int lid=(unsigned int)pthread_self();
		if (lid!=mid) {
			if (isSuspended()) mflags&=(~SUSPEND);
			mflags|=TERMINATE;
			if (mhandle) {
				//TerminateThread((HANDLE)mhandle,0);
				//CloseHandle((HANDLE)mhandle);
				ThreadDestroy((int)mhandle,-1,0);
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
	return -1;
}

void Thread::setPriority(int prior)
{
	if (mhandle) pthread_setschedprio((pthread_t)mhandle,prior);
}

bool Thread::isThisThread()
{
	unsigned int lid=(unsigned int)pthread_self();
	return lid==mid;
}

bool Thread::isSuspended()
{
	confirm();
	return (mflags&SUSPEND)!=0;
}

bool Thread::isTerminated()
{
	confirm();
	return (mflags&TERMINATE)!=0;
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