/*
 * texture2d.h
 *
 *  Created on: 19.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef TEXTURE2D_H_
#define TEXTURE2D_H_

#include <core/baseobject.h>
#include <platform.h>
#include <bt.h>
#include <gen3.h>

namespace csad {

class GlContext;

/**
 * @class Texture2D
 *
 * @ingroup scene
 * @brief Texture2D - two-dimensional texture.
 *
 * @see scene
 */

class Texture2D: public BaseObject {
public:
	MEMMANAGERCLEAN(Texture2D)

	CSAD_API Texture2D(char *name);
	CSAD_API Texture2D(const char *name="");
	//Texture2D(unsigned int texture);
	//Texture2D(unsigned int format,int width,int height);
	CSAD_API ~Texture2D();

	/// the texture filter
	enum FILTER {
		/// does not use filtering
		normal = 0x000,
		/// use LINEAR filtering for texture
		bilinear = 0x101,
		bilinear1 = 0x102,
		bilinear2 = 0x103,
		bilinear3 = 0x104,
		/// use LINEAR filtering for texture and mipmap level
		trilinear = 0x105
	};

	/// ID textures for the current context.
	_FORCEINLINE unsigned int texture() {return p_texture;}

	/// returns the number of the texture to the selected context.
	CSAD_API unsigned int setContext(GlContext* context);

	/// the current context, which was used texture.
	_FORCEINLINE GlContext*context() {return p_context;}

	/// return width
	CSAD_API int getWidth(int level);
	/// return height
	CSAD_API int getHeight(int level);

	CSAD_API void setSize(int width,int height);
	CSAD_API void setFormat(unsigned int format);
	/// sets the link in the resource would have been born matix texture image
	CSAD_API void setRaster(Raster *raster);
	/// returns a resource established as a texture image
	CSAD_API gen::Raster * getRaster();
	/// deferred update textures
	CSAD_API void fullUpdate();
	/// upgrade the texture of the current context
	CSAD_API void updateRect(bt::vector4i *r,Raster *raster);
	CSAD_API void setMipMap(int min,int max);
	CSAD_API void setWrapMode(int s,int t);
	CSAD_API void setFilterMode(int mag,int min);
	CSAD_API void setFilter(unsigned int filter);
	/// download raster file.
	CSAD_API void load(char*name);

	/// activation of the texture, if the texture was not created when creating or changing a context is created in a new way.
	CSAD_API void bind();
	/// returns the name of the texture
	CSAD_API const char * getName();

	CSAD_API void *set(unsigned _int32 ,void *);

	CSAD_API TYPEINFO_H

private:
	/// the selected context
	GlContext *p_context;
	/// the image of Textra
	Raster *p_raster;
	/// the current identity texture for the selected device context
	unsigned int p_texture;
	/// a list of IDs for different contexts
	MapVoid<void> p_shared;
	int p_format;
	int p_width;
	int p_height;
	unsigned int p_filter;
	char mm_min;
	char mm_max;

	void _init();
	/// creates a new texture device for the current context.
	void update();

	void half(void *half,void *data,int w, int h,int bpp);

	static unsigned int p_defFilter;

	static unsigned int getFormatByName(char *name);
	static unsigned int getFilterByName(char *name);
	const char * getFilterName(unsigned int val);
	static int magFilter(int filter);
	static int minFilter(int filter);

	friend class Render;
};

}

#endif /* TEXTURE2D_H_ */
