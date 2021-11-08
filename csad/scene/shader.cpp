/*
 * shader.cpp
 *
 *  Created on: 19.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <scene/shader.h>
#include <core/graph.h>
#include <platform.h>
#include "csad/platform/glextension.h"

OPTIMIZE_ON;

namespace csad {

_NOINLINE void _FASTCALL _initShader(Shader *sader,char *name)
{
	Graph::graph().getShaders()->addObject(sader,name);
}

bool loadShader(char**text,char *name)
{
	File file;
	file.setFileName(name);
	if (!file.open()) {
		return false;
	}
	_int32 size=file.size();
	if (size<=0) return 0;
	if (*text) extFunctions.DeleteMem(*text,0);
	(*text)=(char*)extFunctions.CreateMem(size+1,0);
	(*text)[size]=0;
	file.read(*text,size);
	file.close();
	return true;
}

Shader::Shader(char * name):values(0),fshared(0)
{
	_initShader(this,name);
}

Shader::Shader(const char * name):values(0),fshared(0)
{
	_initShader(this,(char*)name);
}

Shader::~Shader()
{
	Graph::graph().getShaders()->detachObject(this);
}

unsigned _int32 Shader::setContext(GlContext* context)
{
	if (context==fcontext) return fProg;
	fProg=(unsigned int)(_voidint)fshared.find(context);
	if (fProg==0) {
		fcontext=context;
		fProg=context->createShaderProg();
		if (fProg) {
			void* &p=fshared[context];
			p=(void*)(_voidint)fProg;
			update();
		}
	} else if (fcontext==0) {
		if (context->makeCurrent()) {
			fcontext=context;
			update();
		}
	}
	return fProg;
}

Shader& Shader::setGeometry(char *text)
{
	if (ftextGS) extFunctions.DeleteMem(ftextPS, 0);
	ftextGS=text;
	return *this;
}

Shader& Shader::setVertex(char *text)
{
	if (ftextVS) extFunctions.DeleteMem(ftextVS, 0);
	ftextVS=text;
	return *this;
}

Shader& Shader::setFragment(char *text)
{
	if (ftextPS) extFunctions.DeleteMem(ftextPS, 0);
	ftextPS=text;
	return *this;
}

void Shader::setFloat(char *name,float v)
{
	Variant *p;
	p = &(values)[name];
	p->setFloat(v);
}

void Shader::setVector2f(char *name,bt::vector2f &v)
{
	Variant *p;
	p = &(values)[name];
	p->setVector2f(&v);
}

void Shader::setVector3f(char *name,bt::vector3f &v)
{
	Variant *p;
	p = &(values)[name];
	p->setVector3f(&v);
}

void Shader::setVector4f(char *name,bt::vector4f &v)
{
	Variant *p;
	p = &(values)[name];
	p->setVector4f(&v);
}

void Shader::setInt(char *name,_int32 v)
{
	Variant *p;
	p = &(values)[name];
	p->setInt(v);
}

void Shader::setVector2i(char *name,bt::vector2i &v)
{
	Variant *p;
	p = &(values)[name];
	p->setVector2i(&v);
}

void Shader::setVector3i(char *name,bt::vector3i &v)
{
	Variant *p;
	p = &(values)[name];
	p->setVector3i(&v);
}

void Shader::setVector4i(char *name,bt::vector4i &v)
{
	Variant *p;
	p = &(values)[name];
	p->setVector4i(&v);
}

void Shader::bind()
{
	GlContext*current=GlContext::getCurrent();
	sFunctionsGLContext &functions = current->functions();
	if (fcontext!=current) fProg = setContext(current);
	unsigned int err = functions.GetError();
	current->bindShaderProg(fProg);

	ParametersList::iterator it = values.begin();
	ParametersList::iterator end = values.end();
	tfSTDCALL_PROC_uint_int_p fun=0;
	while (it != end) {
		unsigned _int32 id = functions.GetUniformLocation(fProg, (void*)it.key());
		if (id != 0xFFFFFFFF) {
			bt::Variant *p = &it.value();
			void *ltype = p->getType();
			if (ltype == typeFloat()) fun=functions.Uniformfv;
			if (ltype == typeInt()) fun=functions.Uniformiv;
			if (ltype == bt::vector2f::t()) fun=functions.Uniform2fv;
			if (ltype == bt::vector3f::t()) fun=functions.Uniform3fv;
			if (ltype == bt::vector4f::t()) fun=functions.Uniform4fv;
			if (ltype == bt::vector2i::t()) fun=functions.Uniform2iv;
			if (ltype == bt::vector3i::t()) fun=functions.Uniform3iv;
			if (ltype == bt::vector4i::t()) fun=functions.Uniform4iv;
			if (fun) fun(id, 1, p->getData());
		} else {
			err = functions.GetError();
#ifdef LOG_CSAD
			if (err)
				Log::console("Shader::Bind GetUniformLocation \"%s\" 0x%x", it.key(),err);
#endif
		}
		it++;
	}
}

void* Shader::set(unsigned _int32 id, void*param)
{
	if (id==BaseObject::TYPE) return Shader::t();
	if (id==BaseObject::WRITE) {
		Variant *p;
		ParametersList *list=(ParametersList *)param;
		if ((p=list->find("geometry"))!=0) loadShader(&ftextGS,p->getString());
		if ((p=list->find("vertex"))!=0) loadShader(&ftextVS,p->getString());
		if ((p=list->find("fragment"))!=0) loadShader(&ftextPS,p->getString());
	}
	return 0;
}

void Shader::update()
{
	GlContext*current=GlContext::getCurrent();
	sFunctionsGLContext &functions=current->functions();

	_int32 status;
	_int32 count;
	functions.GetProgramiv(fProg,GL_ATTACHED_SHADERS,&count);
	unsigned _int32 shaders[3];
	functions.GetAttachedShaders(fProg,3,&count,shaders);
	unsigned _int32 gs=0;
	unsigned _int32 vs=0;
	unsigned _int32 fs=0;
	while (count>0) {
		count--;
		_int32 type;
		functions.GetShaderiv(shaders[count],GL_SHADER_TYPE,&type);
		if (type==GL_GEOMETRY_SHADER) gs=shaders[count];
		if (type==GL_VERTEX_SHADER) vs=shaders[count];
		if (type==GL_FRAGMENT_SHADER) fs=shaders[count];
	}
	if (ftextGS) {
		if (!gs) {
			gs = functions.CreateShader(GL_GEOMETRY_SHADER);
		}
		compileSource(gs,ftextGS);
		functions.AttachShader(fProg, gs);
	}
	if (ftextVS) {
		if (!vs) {
			vs=functions.CreateShader(GL_VERTEX_SHADER);
		}
		compileSource(vs,ftextVS);
		functions.AttachShader(fProg, vs);
	}
	if (ftextPS) {
		if (!fs) {
			fs=functions.CreateShader(GL_FRAGMENT_SHADER);
		}
		compileSource(fs,ftextPS);
		functions.AttachShader(fProg, fs);
	}
	functions.LinkProgram(fProg);
	functions.GetProgramiv(fProg, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
#ifdef LOG_CSAD
		char errorLog[1024] = { 0 };
		functions.GetProgramInfoLog(fProg, 1024, NULL, errorLog);
		Log::console("Shader::LinkProgram %s", errorLog);
#endif
	}
}

bool Shader::compileSource(unsigned _int32 _id,char *_src)
{
	GlContext*current=GlContext::getCurrent();
	sFunctionsGLContext &functions=current->functions();
	_int32 status;
	_int32 len=extFunctions.FindCMem(_src,0,65536);
	functions.ShaderSource(_id,1,&_src,&len);
	functions.CompileShader(_id);
	functions.GetShaderiv(_id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) { //GL_INVALID_OPERATION
#ifdef LOG_CSAD
		char errorLog[1024];
		extFunctions.StocBMem(errorLog, 1024, 0);
		functions.GetProgramInfoLog(_id, 1024, NULL, errorLog);
		_int32 errorPos;
		functions.GetIntegerv ( GL_PROGRAM_ERROR_POSITION_ARB, &errorPos );
		Log::console("Shader::compileSource error at position %d %s", errorPos, errorLog );
#endif
		return false;
	}
	return true;
}

TYPEINFO(Shader)

}

OPTIMIZE_OFF;
