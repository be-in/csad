/*
 * rasterscript.cpp
 *
 *  Created on: 27.08.2007
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#if defined(SCRIPT_BT) || defined(BT_SCRIPT)
#include <bt.h>
#include <gen3/rasterscript.h>
#include <gen3/genfunctions.h>
#include <platform.h>
#include "csad/bt/script.h"

OPTIMIZE_ON;

namespace gen {

	#define MAX_RasterScriptBuff 40

	bt::sScriptItemInfo RasterCodes[]={
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
		{typeFunction(),genFunctions.CreateRaster,bt::DeffType,3},
		{typeFunction(),genFunctions.CloneRaster,bt::PIType,1},
		{typeFunction(),genFunctions.FreeRaster,bt::PIType,1},
		{typeFunction(),extFunctions.NoiseStart,bt::DeffType,2},
		{typeFunction(),genFunctions.RasterColor,bt::PIType,2},
		{typeFunction(),genFunctions.RasterGradient,bt::PIType,6},
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

	bt::ConstMapVoid<char*,bt::sScriptItemInfo*,MAX_RasterScriptBuff> _codesRaster;
	char *_codesnameRaster[]={(char *)"\006result",(char *)"\004tmp0",(char *)"\004tmp1",(char *)"\004tmp2",(char *)"\004tmp3",(char *)"\004tmp4",(char *)"\004tmp5",(char *)"\004tmp6",(char *)"\004tmp7",
		(char *)"\006NORMAL",(char *)"\005ALPHA",(char *)"\003ADD",(char *)"\003SUB",(char *)"\003MUL",(char *)"\002OR",(char *)"\003AND",(char *)"\003XOR",(char *)"\003MIX",(char *)"\005COLOR",
		(char *)"\004Mode",(char *)"\014CreateRaster",(char *)"\013CloneRaster",(char *)"\012FreeRaster",(char *)"\012NoiseStart",(char *)"\005Color",(char *)"\010Gradient",
		(char *)"\005Noise",(char *)"\004Line",(char *)"\010Particle",(char *)"\010LightRay",(char *)"\005Alpha",(char *)"\004Blur",(char *)"\007Distort",(char *)"\006Clouds"};

	void _APICALL initRasterScript(void *script)
	{
		RasterCodes[0].var=0;
		RasterCodes[1].var=0;
		RasterCodes[2].var=0;
		RasterCodes[3].var=0;
		RasterCodes[4].var=0;
		RasterCodes[5].var=0;
		RasterCodes[6].var=0;
		RasterCodes[7].var=0;
		RasterCodes[8].var=0;
		RasterCodes[19].var=genFunctions.GeneratorMode;
		RasterCodes[20].var=genFunctions.CreateRaster;
		RasterCodes[21].var=genFunctions.CloneRaster;
		RasterCodes[22].var=genFunctions.FreeRaster;
		RasterCodes[23].var=extFunctions.NoiseStart;
		RasterCodes[24].var=genFunctions.RasterColor;
		RasterCodes[25].var=genFunctions.RasterGradient; 
		RasterCodes[26].var=genFunctions.RasterNoise; 
		RasterCodes[27].var=genFunctions.RasterLine; 
		RasterCodes[28].var=genFunctions.RasterParticle; 
		RasterCodes[29].var=genFunctions.RasterLightRay; 
		RasterCodes[30].var=genFunctions.RasterAlpha; 
		RasterCodes[31].var=genFunctions.RasterBlur; 
		RasterCodes[32].var=genFunctions.RasterDistort;
		RasterCodes[33].var=genFunctions.RasterClouds;

		if (_codesRaster.count()>0) return;
		int i=0;
		while (RasterCodes[i].type) {
			arrFunctions.MCSPAdd(&_codesRaster,(void*)_codesnameRaster[i],(void*)&RasterCodes[i],MAX_RasterScriptBuff);
			i++;
		}
		objFunctions.ScriptInit(script,&_codesRaster,RasterCodes);
	}

	RasterScript::~RasterScript()
	{
		if (ftext) extFunctions.DeleteMem(ftext,0);
		ftext=0;
	}

	bool RasterScript::exec()
	{
		if (raster) genFunctions.FreeRaster(raster);
		raster=0;

		sGenerator gen;
		genFunctions.SetGenerator(&gen);
		genFunctions.initRasterScript(&script);
		objFunctions.ScriptParser(&script,ftext);
		bool rez=true;
		if (script.errorCode) {
#ifdef LOG_CSAD
			csad::Log::console("RasterScript: Ln %i error: %i %s",script.strNum,script.errorCode,((bt::ShortString*)&script.errorString)->str());
#endif
			rez=false;
		} else {
			objFunctions.ScriptExe(&script);
			raster=(Raster*)RasterCodes[0].var;
		}
		objFunctions.ScriptClear(&script);
		genFunctions.SetGenerator(0);
		return rez;
	}

	bool RasterScript::readFromFile(char *name)
	{
		csad::File file(name,csad::File::READ);
		if (!file.open()) return false;
		readFromFile(&file);
		file.close();

		return true;
	}

	bool RasterScript::readFromFile(csad::File *file)
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