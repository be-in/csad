/*
 * thread.h
 *
 *  Created on: 26.11.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <platform/platformapi.h>
#include <core/baseobject.h>
#include <bt.h>

namespace csad {

using namespace bt;

/**
 * @class Thread
 *
 * @ingroup platform
 * @brief Thread - class to create and flow control.
 *
 * @see platform
 */

class Thread {
public:
	MEMDEFAULT(Thread)

	PLATFORM_API Thread(bool created = false, tfSTDCALL_p_FUNC_p proc = 0);
	PLATFORM_API virtual ~Thread();

	/// Starts a thread
	PLATFORM_API void play();
	/// The handler thread
	PLATFORM_API virtual void run();
	/// Stops the flow
	PLATFORM_API void stop();
	/// Creates a thread
	PLATFORM_API void create();
	/// Destroys the flow
	PLATFORM_API void terminate();
	PLATFORM_API int priority();
	PLATFORM_API void setPriority(int);

	/// Check for presence in the stream
	PLATFORM_API bool isThisThread();

	PLATFORM_API bool isSuspended();
	PLATFORM_API bool isTerminated();

	PLATFORM_API static void* id();

	/// Invokes the handler thread
	PLATFORM_API static Thread* runProc(tfSTDCALL_p_FUNC_p proc, Thread*thread = 0);

	TYPEINFO_H
private:
	enum Flag {
		TERMINATE = 0x00000001,
		SUSPEND = 0x00000002,
		DESTROY = 0x00000004,
		CONFIRM_TERMINATE = 0x00000100,
		CONFIRM_SUSPEND = 0x00000200,
	};

	void *mid;
	void *mhandle;
	unsigned int mflags;
	int mpriority;
	tfSTDCALL_p_FUNC_p mproc;

	PLATFORM_API void confirm();
};

}

#endif /* THREAD_H_ */