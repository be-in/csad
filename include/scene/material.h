/*
 * @file material.h
 *
 *  Created on: 19.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <core/baseobject.h>
#include <platform.h>
#include <bt.h>

namespace csad {

WARNING_DISABLE;
OPTIMIZE_ON;

using namespace bt;

class Texture2D;

typedef VoidVector<Texture2D> TextureList;

/**
 * @class Material
 *
 * @ingroup scene
 * @brief Material - the object of material.
 *
 @verbatim
   <Material name="material name" color="0.1 1.0 1.0 1.0" ambient="0.0 0.0 0.0 1.0" src="SRC_ALPHA" dst="DST_COLOR" />
 @endverbatim
 * @see scene
 */

class Material: public BaseObject {
public:
	MEMMANAGERCLEAN(Material)

	CSAD_API Material(char * name);
	CSAD_API Material(const char * name="");
	CSAD_API ~Material();

	/// Blend functions
	enum Blend {
		/// Not use
		NONE=-1,
		/// Use parameter zero
		ZERO=0,
		/// Use parameter one
		ONE=1,
		/// If never
		NEVER=0x0200,
		/// If less
		LESS=0x0201,
		/// If equal
		EQUAL=0x0202,
		///
		LEQUAL=0x0203,
		/// If greater
		GREATER=0x0204,
		///
		NOTEQUAL=0x0205,
		///
		GEQUAL=0x0206,
		/// always
		ALWAYS=0x0207,

		/// Use parameter from source
		SRC_COLOR=0x0300,
		/// Use parameter from one minus source
		ONE_MINUS_SRC_COLOR=0x0301,
		/// Use parameter alpha
		SRC_ALPHA=0x0302,
		/// Use parameter one minus source alpha
		ONE_MINUS_SRC_ALPHA=0x0303,
		/// Use parameter destionation alpha
		DST_ALPHA=0x0304,
		/// Use parameter one minus destionation alpha
		ONE_MINUS_DST_ALPHA=0x0305,
		/// Use parameter destionation
		DST_COLOR=0x0306,
		/// Use parameter one minus destionation
		ONE_MINUS_DST_COLOR=0x0307
	};

	/// 
	enum Flag {
		///
		GL_LIGHT = 0x00001,
		GL_DEPTHWRITE = 0x00002,
	};

	/// set color.
	CSAD_API void setDiffuse(vector4f &color);
	/// set color.
	_FORCEINLINE void setDiffuse(float r,float g,float b,float a) { setDiffuse(bt::vector4f(r,g,b,a)); }
	/// return diffuse color.
	_FORCEINLINE vector4f getDiffuse() {return p_diffuse;}
	/// set ambient color
	CSAD_API void setAmbient(vector4f &color);
	/// set ambient color
	_FORCEINLINE void setAmbient(float r,float g,float b,float a) { setAmbient(bt::vector4f(r,g,b,a)); }
	_FORCEINLINE vector4f getAmbient() {return p_ambient;}
	/// set specular color
	CSAD_API void setSpecular(vector4f &color);
	/// set specular color
	_FORCEINLINE void setSpecular(float r,float g,float b,float a) { setSpecular(bt::vector4f(r,g,b,a)); }
	/// set emission color
	CSAD_API void setEmission(vector4f &color);
	/// set emission color
	_FORCEINLINE void setEmission(float r,float g,float b,float a) { setEmission(bt::vector4f(r,g,b,a)); }

	/// set blend function parameters
	CSAD_API void setBlend(int src=0,int dst=0);
	/// set blend function parameters by name
	CSAD_API void setBlend(char* src=0,char* dst=0);

	/// set alpha function parameters
	CSAD_API void setAlpha(int func,float ref=0.5f);
	/// set alpha function parameters by name
	CSAD_API void setAlpha(char* func=0,float ref=0.5f);

	/// Depth test function
	CSAD_API void setDepth(int func);
	///
	CSAD_API void setDepth(char* func);
	/// Enable or disable depth write
	CSAD_API void setDepthWrite(bool write);

	/// Emit light
	CSAD_API void setLight(bool val);
	/// Is emit light
	_FORCEINLINE bool isLight() { return ((fflag&GL_LIGHT)!=0); }

	/// set line with parameter
	CSAD_API void setLineWith(float val);
	/// set point size parameter
	CSAD_API void setPointSize(float val);

	/// setting the texture, the id number of the layer for multitexturing.
	CSAD_API int setTexture2D(Texture2D* texture,unsigned int id=0);
	/// setting the texture, the id number of the layer for multitexturing.
	CSAD_API int setTexture2D(char* name,unsigned int id=0);
	/// return texture.
	CSAD_API Texture2D *getTexture2D(unsigned int id=0);

	/// sets the matrix to transform texture coordinates as the area of the texture
	CSAD_API void setTextureRect(bt::vector4f &rect,unsigned int id=0);
	//CSAD_API void setTextureTRS(bt::vector3f &pos,bt::quaternionf &rot,bt::vector3f &scale,unsigned int id=0);
	/// sets the matrix to transform texture coordinates
	CSAD_API void setTextureMatrix(bt::matrix4f &matrix,unsigned int id=0);
	/// returns the matrix texture coordinates
	CSAD_API bt::matrix4f* getTextureMatrix(unsigned int id=0);

	_FORCEINLINE void bind() {Render::BindMaterial(this);}

	/// return material name
	CSAD_API const char * getName();
	CSAD_API const char * getPath();

	CSAD_API void *set(unsigned _int32 ,void *);

	CSAD_API static Material *finder(char *path);

	CSAD_API TYPEINFO_H

private:
	VoidVector<Texture2D> p_textures;
	sArray ftexturesMatrix;

	vector4f p_ambient;
	vector4f p_diffuse;
	vector4f p_emission;
	vector4f p_specular;
	unsigned _int32 fflag;
	int p_blend_src;
	int p_blend_dst;
	int p_alpha;
	int p_depth;
	float flineWidth;
	float fpointSize;
	float p_alpha_ref;

	enum States {
		VALIDED = 0x011F1C01,
		FREE = 0
	};

	void init(char *name);

	friend class Render;
};

OPTIMIZE_OFF;
WARNING_ENABLE;

}

#endif /* MATERIAL_H_ */
