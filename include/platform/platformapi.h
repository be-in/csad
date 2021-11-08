/*
 * platformapi.h
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef PLATFORMAPI_H_
#define PLATFORMAPI_H_

#include <bt/os.h>

#ifdef LIB_CSAD
#define PLATFORM_EXPORTS
#endif

#if defined (OS_QNX) // QNX
#ifdef _int64
#undef _int64
#endif

#include <setjmp.h>
#include <cstdlib>
#include <pthread.h>

#include <errno.h>
#include <stdio.h>

#include <fcntl.h>
#include <dlfcn.h>

#include <sys/select.h>
#include <sys/neutrino.h>
#include <pthread.h>
#include <sys/dcmd_input.h>

#if _NTO_VERSION < 660
#include <font_api.h>
#include <gf/gf.h>
#include <gf/gf3d.h>
#else
#include <screen/screen.h>
#include <ft2build.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#endif

#define PLATFORM_API

#elif defined (OS_WIN) // WINDOWS
#include <stdio.h>
#include <wingdi.h>
#include <GL/gl.h>

#ifdef PLATFORM_EXPORTS
	#define PLATFORM_API __declspec(dllexport)
#else
#ifndef CSAD_LOCAL
	#define PLATFORM_API __declspec(dllimport)
#else
	#define PLATFORM_API
#endif
#endif

#elif defined (OS_LINUX) // LINUX
#include <setjmp.h>
#include <cstdlib>
#include <pthread.h>

#include <errno.h>
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <dlfcn.h>

#include <sys/types.h>
#include <limits.h>
#include <sys/select.h>
#include <GL/gl.h>

#include <sys/socket.h>
#include <netinet/in.h>

#ifdef PLATFORM_EXPORTS
	#define PLATFORM_API __attribute__((visibility("default")))
#else
	#define PLATFORM_API
#endif

#elif defined (OS_OSX) // OSX
#include <setjmp.h>
#include <cstdlib>
#include <pthread.h>

#include <errno.h>
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <dlfcn.h>

#include <sys/types.h> 
#include <sys/select.h>
#include <OpenGL/gl.h>

#include <sys/socket.h>
#include <netinet/in.h>

#ifdef PLATFORM_EXPORTS
#define PLATFORM_API __attribute__((visibility("default")))
#else
#define PLATFORM_API
#endif

#else

#include <cstdlib>

#endif

#endif /* PLATFORMAPI_H_ */
