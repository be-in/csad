/*
 * fontserver.h
 *
 *  Created on: 30.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef FONTSERVER_H_
#define FONTSERVER_H_

#include <platform/platformapi.h>
#include <core/objectmanager.h>
#include <bt.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

/**
 * @class FontServer
 *
 * @ingroup platform
 * @brief FontServer - font Manager.
 *
 @verbatim
   <FontServer name="name" options="">
   ... Fonts ...
   </FontServer>
 @endverbatim
 *
 * @see FontServer, platform
 */

class Font;
class FontText;

class FontServer: public BaseObject {
public:
	MEMDEFAULT(FontServer)

	PLATFORM_API FontServer(char *name);
	PLATFORM_API FontServer(const char *name="");
	PLATFORM_API ~FontServer();

	PLATFORM_API void setOptions(char *options);

	/// Constructs a font by name.
	PLATFORM_API Font *createFont(char *name);
	_FORCEINLINE Font *createFont(const char *name="") {return createFont((char*)name);}
	/// Creates a texture font by name.
	PLATFORM_API FontText *createFontText(char *name);
	_FORCEINLINE FontText *createFontText(const char *name="") {return createFontText((char*)name);}

	/// Returns the font by name.
	PLATFORM_API Font *getFont(char *name);
	_FORCEINLINE Font *getFont(const char *name) {return getFont((char*)name);}
	/// Returns the texture font by name.
	PLATFORM_API FontText *getFontText(char *name);
	_FORCEINLINE FontText *getFontText(const char *name) {return getFontText((char*)name);}

	PLATFORM_API void init();
	PLATFORM_API void close();

	PLATFORM_API void * set(unsigned _int32 ,void * );

	PLATFORM_API TYPEINFO_H

private:
	ObjectManager p_font;
	void* p_dll;
	void* p_pf;
	ShortString p_options;

	friend class Font;
	friend class FontText;
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* FONTSERVER_H_ */
