/*
 * style.h
 *
 *  Created on: 13.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef STYLE_H_
#define STYLE_H_

#include <core/containercomponents.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

class Font;

/**
 * @class Style
 *
 * @ingroup core
 * @brief Style - container styles.
 *
 * Necessary to create the model of the parameter list.
 * Not tied to a particular environment, allows you to store various components and their parameters for future use.
 * Unlike the base of the container tied to the Manager graphics.
 * You can use any set of components, which contains the necessary settings, which can be the same for a large number of objects.
 * Changing the style settings after you install it in your object, may not always lead to a change of an object that requires a re-install of the style object.
 *
 * For description in the configuration:
 @verbatim
   <Style name="the name of the style">
   ... components ...
   </Style>
 @endverbatim
 *
 * @see core, TextStyle, SGButtonStyle, SGElementStyle
 */

class Style: public ContainerComponents {
public:
	MEMMANAGER(Style)

	CSAD_API Style(char *name);
	CSAD_API Style(const char *name="");

	CSAD_API Component* getInheritComponent(void * t);

	/// Returns the component of the given type, if it is not in a container returns 0.
	template <typename T>
	_FORCEINLINE T* getComponent() { 
		Component **c=(Component **)arrFunctions.MPFind(&p_list,T::t());
		if (c) return static_cast<T*>(*c);
		return static_cast<T*>(getInheritComponent(T::t()));
	}

	/// Returns the component of the given type, if it is not in a container returns 0.
	_FORCEINLINE Component* getComponent(void * t) {
		Component **c=(Component **)arrFunctions.MPFind(&p_list,t);
		if (c) return *c;
		return getInheritComponent(t);
	}

	CSAD_API void setInherit(Style *style);
	CSAD_API void setInherit(char *name);

	CSAD_API const char *getPath();

	CSAD_API void *set(unsigned _int32 id,void * param);

	CSAD_API TYPEINFO_H
private:
	Style *finherit;

	void _init();
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* STYLE_H_ */
