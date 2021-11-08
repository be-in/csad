/*
 * @file platform.h
 *
 *  Created on: 10.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

namespace csad {

/**
 * @defgroup platform csad: platform
 * @brief main platform dependent classes.
 * @see csad.
 */

}

#include <platform/os.h>
#include <platform/types.h>
#include <platform/log.h>
#include <platform/file.h>
#include <platform/library.h>
#include <platform/thread.h>
#include <platform/timer.h>
#include <platform/font.h>
#include <platform/fontserver.h>
#include <platform/keyboard.h>
#include <platform/mouse.h>
#include <platform/netconnection.h>
#include <platform/renderer.h>
#include <platform/render.h>
#include <platform/display.h>
#include <platform/glcontext.h>
#include <platform/interfacerendersystem.h>
#include <platform/interfaceeventsystem.h>

#endif /* PLATFORM_H_ */
