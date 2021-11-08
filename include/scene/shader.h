/*
 * shader.h
 *
 *  Created on: 19.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <core/csadapi.h>
#include <core/baseobject.h>

namespace csad {

class GlContext;

CSAD_API bool loadShader(char**text,char *name);

/**
 * @class Shader
 *
 * @ingroup scene
 * @brief Shader - the object of shader programm.
 *
 @verbatim
   <Shader name="shader name" />
 @endverbatim
 * @see scene
 */

class Shader:public BaseObject {
public:
	MEMMANAGERCLEAN(Shader)

	CSAD_API Shader(char * name);
	CSAD_API Shader(const char * name);
	CSAD_API ~Shader();

	unsigned _int32 setContext(GlContext* context);

	CSAD_API Shader& setGeometry(char *text);
	_FORCEINLINE bool loadGeometry(char *file) { return loadShader(&ftextGS,file); }
	CSAD_API Shader& setVertex(char *text);
	_FORCEINLINE bool loadVertex(char *file) { return loadShader(&ftextVS,file); }
	CSAD_API Shader& setFragment(char *text);
	_FORCEINLINE bool loadFragment(char *file) { return loadShader(&ftextPS,file); }

	CSAD_API void setFloat(char *name,float v);
	CSAD_API void setVector2f(char *name,bt::vector2f &v);
	CSAD_API void setVector3f(char *name,bt::vector3f &v);
	CSAD_API void setVector4f(char *name,bt::vector4f &v);
	CSAD_API void setInt(char *name,_int32 v);
	CSAD_API void setVector2i(char *name,bt::vector2i &v);
	CSAD_API void setVector3i(char *name,bt::vector3i &v);
	CSAD_API void setVector4i(char *name,bt::vector4i &v);

	CSAD_API void bind();

	CSAD_API void* set(unsigned _int32,void*);

	CSAD_API TYPEINFO_H

private:
	/// the selected context
	GlContext *fcontext;
	///
	char *ftextGS;
	char *ftextVS;
	char *ftextPS;
	/// the current identity texture for the selected device context
	unsigned int fProg;
	/// a list of IDs for different contexts
	MapVoid<void> fshared;
	ParametersList values;

	void update();
	bool compileSource(unsigned _int32 _id,char *_src);
};

}

#endif /* SHADER_H_ */
