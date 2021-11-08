/*
 * meshscript.cpp
 *
 *  Created on: 27.08.2007
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#if defined(SCRIPT_BT) || defined(BT_SCRIPT)
#include <bt.h>
#include <gen3/meshscript.h>
#include <gen3/genfunctions.h>
#include <platform.h>
#include "csad/bt/script.h"

OPTIMIZE_ON;

namespace gen {

	#define MAX_MeshScriptBuff 40

	bt::sScriptItemInfo MeshCodes[]={
		{typePVoid(),0,0,0},
		{typePVoid(),0,0,0},
		{typePVoid(),0,0,0},
		{typePVoid(),0,0,0},
		{typePVoid(),0,0,0},
		{typePVoid(),0,0,0},
		{typePVoid(),0,0,0},
		{typePVoid(),0,0,0},
		{typePVoid(),0,0,0},
		{typeInt(),0,0,0},
		{typeInt(),(void*)1,0,0},
		{typeInt(),(void*)2,0,0},
		{typeInt(),(void*)3,0,0},
		{typeInt(),(void*)4,0,0},
		{typeInt(),(void*)5,0,0},
		{typeInt(),(void*)6,0,0},
		{typeInt(),(void*)7,0,0},
		{typeInt(),(void*)8,0,0},
		{typeInt(),(void*)9,0,0},
		{typeFunction(),genFunctions.GeneratorMode,bt::DeffType,1},
		{typeFunction(),genFunctions.CreateMesh,bt::DeffType,1},
		{typeFunction(),genFunctions.CloneMesh,bt::PIType,1},
		{typeFunction(),genFunctions.FreeMesh,bt::PIType,1},
		{typeFunction(),extFunctions.NoiseStart,bt::DeffType,2},
		{typeFunction(),genFunctions.MeshColor,bt::PIType,2},
		{typeFunction(),genFunctions.MeshGradient,bt::PFFFFFIIIType,8},
		{typeFunction(),genFunctions.RasterNoise,bt::PIType,3},
		{typeFunction(),genFunctions.RasterLine,bt::PIType,6},
		{typeFunction(),genFunctions.RasterParticle,bt::PIIIFIType,6},
		{typeFunction(),genFunctions.RasterLightRay,bt::PIIIFIType,7},
		{typeFunction(),genFunctions.RasterAlpha,bt::PIType,1},
		{typeFunction(),genFunctions.RasterBlur,bt::PIType,2},
		{typeFunction(),genFunctions.RasterDistort,bt::PPIType,4},
		{typeFunction(),genFunctions.RasterClouds,bt::PIType,4},
		{0,0,0,0}
	};

	bt::ConstMapVoid<char*,bt::sScriptItemInfo*,MAX_MeshScriptBuff> _codesMesh;
	char *_codesnameMesh[]={(char *)"\006result",(char *)"\004tmp0",(char *)"\004tmp1",(char *)"\004tmp2",(char *)"\004tmp3",(char *)"\004tmp4",(char *)"\004tmp5",(char *)"\004tmp6",(char *)"\004tmp7",
		(char *)"\006NORMAL",(char *)"\005ALPHA",(char *)"\003ADD",(char *)"\003SUB",(char *)"\003MUL",(char *)"\002OR",(char *)"\003AND",(char *)"\003XOR",(char *)"\003MIX",(char *)"\005COLOR",
		(char *)"\004Mode",(char *)"\012CreateMesh",(char *)"\011CloneMesh",(char *)"\010FreeMesh",(char *)"\012NoiseStart",(char *)"\005Color",(char *)"\010Gradient",
		(char *)"\005Noise",(char *)"\004Line",(char *)"\010Particle",(char *)"\010LightRay",(char *)"\005Alpha",(char *)"\004Blur",(char *)"\007Distort",(char *)"\006Clouds"};

	void _APICALL initMeshScript(void *script)
	{
		MeshCodes[0].var=0;
		MeshCodes[1].var=0;
		MeshCodes[2].var=0;
		MeshCodes[3].var=0;
		MeshCodes[4].var=0;
		MeshCodes[5].var=0;
		MeshCodes[6].var=0;
		MeshCodes[7].var=0;
		MeshCodes[8].var=0;
		MeshCodes[19].var=genFunctions.GeneratorMode;
		MeshCodes[20].var=genFunctions.CreateMesh;
		MeshCodes[21].var=genFunctions.CloneMesh;
		MeshCodes[22].var=genFunctions.FreeMesh;
		MeshCodes[23].var=extFunctions.NoiseStart;
		MeshCodes[24].var=genFunctions.MeshColor;
		MeshCodes[25].var=genFunctions.MeshGradient;
		MeshCodes[26].var=genFunctions.RasterNoise; 
		MeshCodes[27].var=genFunctions.RasterLine; 
		MeshCodes[28].var=genFunctions.RasterParticle; 
		MeshCodes[29].var=genFunctions.RasterLightRay; 
		MeshCodes[30].var=genFunctions.RasterAlpha; 
		MeshCodes[31].var=genFunctions.RasterBlur; 
		MeshCodes[32].var=genFunctions.RasterDistort;
		MeshCodes[33].var=genFunctions.RasterClouds;

		if (_codesMesh.count()>0) return;
		int i=0;
		while (MeshCodes[i].type) {
			arrFunctions.MCSPAdd(&_codesMesh,(void*)_codesnameMesh[i],(void*)&MeshCodes[i],MAX_MeshScriptBuff);
			i++;
		}
		objFunctions.ScriptInit(script,&_codesMesh,MeshCodes);
	}

	MeshScript::~MeshScript()
	{
		if (ftext) extFunctions.DeleteMem(ftext,0);
		ftext=0;
	}

	bool MeshScript::exec()
	{
		if (mesh) genFunctions.FreeMesh(mesh);
		mesh=0;

		sGenerator gen;
		genFunctions.SetGenerator(&gen);
		genFunctions.initMeshScript(&script);
		objFunctions.ScriptParser(&script,ftext);
		bool rez=true;
		if (script.errorCode) {
#ifdef LOG_CSAD
			csad::Log::console("RasterScript: Ln %i error: %i %s",script.strNum,script.errorCode,((bt::ShortString*)&script.errorString)->str());
#endif
			rez=false;
		} else {
			objFunctions.ScriptExe(&script);
			mesh=(csad::Mesh*)MeshCodes[0].var;
		}
		objFunctions.ScriptClear(&script);
		genFunctions.SetGenerator(0);
		return rez;
	}

	bool MeshScript::readFromFile(char *name)
	{
		csad::File file(name,csad::File::READ);
		if (!file.open()) return false;
		readFromFile(&file);
		file.close();

		return true;
	}

	bool MeshScript::readFromFile(csad::File *file)
	{
		_int32 size=file->size();
		if (ftext) extFunctions.DeleteMem(ftext,0);
		ftext = (char*)extFunctions.CreateMem(size + 1,0);
		file->read(ftext,size);
		ftext[size]=0;
		return true;
	}

}

OPTIMIZE_OFF;
#endif