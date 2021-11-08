/*
 * winthread.h
 *
 *  Created on: 26.11.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

/*
 if use TerminateThread	and CloseHandle it can be lock - need wait when thread close self
 -- while (!isTerminate); --
*/

#include <platform/platformapi.h>

#if defined (OS_WIN)

#include <platform.h>

OPTIMIZE_ON;

namespace csad {

void* _APICALL ThreadProcExe(Thread*thread)
{
	if (thread) {
		thread->run();
		//thread->terminate();
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
		if (mhandle) CloseHandle((HANDLE)mhandle);
		create();
	}
	if (isSuspended()) {
		if (ResumeThread((HANDLE)mhandle)>=0)
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
			SuspendThread((HANDLE)mhandle);
		}
	}
}

void Thread::create()
{
	if ((mflags&DESTROY)==0) {
		mflags=SUSPEND;
		mhandle=(void*)CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)mproc,this,CREATE_SUSPENDED,(LPDWORD)&mid);
	}
}

void Thread::terminate()
{
	mflags&=~CONFIRM_TERMINATE;
	if (!isTerminated()) {
		_voidint lid=(_voidint)GetCurrentThreadId();
		if (lid!=(_voidint)mid) {
			if (isSuspended()) mflags&=(~SUSPEND);
			mflags|=TERMINATE;
			if (mhandle) {
				TerminateThread((HANDLE)mhandle,0);
				CloseHandle((HANDLE)mhandle);
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
	if (mhandle) return GetThreadPriority((HANDLE)mhandle);
	return -1;
}

void Thread::setPriority(int prior)
{
	if (mhandle) SetThreadPriority((HANDLE)mhandle,prior);
}

bool Thread::isThisThread()
{
	_voidint lid=(_voidint)GetCurrentThreadId();
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
	_voidint code;
	if (!GetExitCodeThread((HANDLE)mhandle,(LPDWORD)&code)) {
		int err=GetLastError();
	} else {
		if (code!=STILL_ACTIVE) mflags|=TERMINATE;
	}
	return (mflags&TERMINATE)!=0;
}

void* Thread::id()
{
	return (void*)GetCurrentThreadId();
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

OPTIMIZE_OFF;

#endif