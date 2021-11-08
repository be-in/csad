/*
 * viewport.h
 *
 *  @brief Complex software application developer, MS Visual C++ 2003-2010, QNX Momentics IDE
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include <bt.h>
#include <core/baseobject.h>
#include <core/csadapi.h>

namespace csad {

WARNING_DISABLE;
OPTIMIZE_ON;

using namespace bt;

class GlContext;
class Display;

/**
 * @class ViewPort
 *
 * @ingroup scene
 * @brief ViewPort - rectangular area of the screen where the image is built.
 *
 * @see scene
 */

class ViewPort {
public:
	MEMDEFAULT(ViewPort)

	CSAD_API ViewPort();
	CSAD_API virtual ~ViewPort();

	/// Returns the coefficients position and size the window display
	CSAD_API vector4f &getRect();

	/// Calculates the size of the window in pixels
	CSAD_API vector4i getRect(GlContext *context);

	/// Calculates the size of the window in pixels
	CSAD_API vector4i getRect(Display *display);

	/// Sets the display window in the context size
	CSAD_API void setFull();

	/// Specifies mastasia dimensions region
	_FORCEINLINE void setRect(vector4f &rect) {p_view=rect;}

	/// returns smashie right from the bottom left corner
	_FORCEINLINE float getX() {return p_view.x;}

	/// Returns mixing up from the bottom left corner
	_FORCEINLINE float getY() {return p_view.y;}

	/// Returns the width ratio
	_FORCEINLINE float getWidth() {return p_view.z;}

	/// Returns the height ratio
	_FORCEINLINE float getHeight() {return p_view.w;}

	CSAD_API bool makeCurrent(unsigned int toTextureId = 0);

	CSAD_API TYPEINFO_H

private:
	vector4f p_view;
};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* VIEWPORT_H_ */
