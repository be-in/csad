/*
 * script.cpp
 *
 *  Created on: 2007 - 22.06.2008
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#if defined(SCRIPT_BT) || defined(BT_SCRIPT)
#include <bt.h>
#include "script.h"

OPTIMIZE_ON;

namespace bt {

	void* DeffType[15]={typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt()};
	void* PIType[15]={typePVoid(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt()};
	void* PIIIFIType[15]={typePVoid(),typeInt(),typeInt(),typeInt(),typeFloat(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt()};
	void* PFFFFFIIIType[15]={typePVoid(),typeFloat(),typeFloat(),typeFloat(),typeFloat(),typeFloat(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt()};
	void* PPIType[15]={typePVoid(),typePVoid(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt(),typeInt()};

sScript * _APICALL scriptCreate()
{
	sScript *script = (sScript *)extFunctions.CreateMem(sizeof(sScript), 0);
	script->strNum=0;
	script->build=0;
	script->codesInfo=0;
	script->codesMap=0;
	script->errorCode=0;
	script->errorString=0;
	return script;
}

const char *scriptDelimiters=" /(),:;='\r\n""";

bool isDel(char*text)
{
	if (!text) return true;
	if (*text==0) return true;
	char*dels=(char*)scriptDelimiters;
	while (*dels) {
		if (*text==*dels) return true;
		dels++;
	}
	return false;
}

void _APICALL scriptInit(void *script,void *CodeMap,void *CodesInfo) {
	sScript *sscript=(sScript *)script;
	sscript->strNum=0;
	sscript->build=0;
	sscript->codesInfo=CodesInfo;
	sscript->codesMap=CodeMap;
	sscript->errorCode=0;
	sscript->errorString=0;
}

char* getparam(void *script,char*text,int max,void**types,VoidVector<void> * param)
{
	sScript *sscript=(sScript *)script;
	char *c=text;
	bool isstr=false;

	char *s=c;
	char *next=c;
	while (*next && isDel(next)) next++;
	while (s<next && *s!='(') s++;
	if (*s!='(') {
		*(bt::ShortString*)&sscript->errorString="";
		sscript->errorCode=2;
		return 0;
	}
	char *f=s;
	while (s<next && *s!='\'') s++;
	if (*s=='\'') { isstr=true; } else s=f;
	while (s<next && *s!=')') s++;
		c=next;
	void **typei=types;

	if (*s!=')')
	while (*c && max>0) {
		next=c;
		int len=0;
		while (*next && !isDel(next)) {
			next++;
			len++;
		}
		f=next;
		while (*next && isDel(next)) next++;
		s=f;
		while (s<next && *s!='\'') *s++;
		if (isstr) {
			if (*s=='\'') {
			} else {
				*(bt::ShortString*)&sscript->errorString="";
				sscript->errorCode=4;
				return 0;
			}
		} else s=f;
		
		char val[128];
		extFunctions.MoveMem(c,val,len);
		val[len]=0;

		sScriptParamInfo *par=0;
		par = (sScriptParamInfo*)extFunctions.CreateMem(sizeof(sScriptParamInfo), 0);
		if (isstr) {
			//par = (sScriptParamInfo*)extFunctions.CreateMem(sizeof(sScriptParamInfo),0);
			*(bt::ShortString*)&par->str=val;
			par->type=typePChar();
			par->var=val;
			typei++;
		} else {
			//par = (sScriptParamInfo*)extFunctions.CreateMem(sizeof(sScriptParamInfo), 0);
			sScriptItemInfo **info=(sScriptItemInfo **)arrFunctions.MSSPFind(&(sscript->codesMap),val);
			if (info) {
				par->type=0;
				par->str=0;
				par->var=*info;
			} else {
				par->type=(*typei);
				par->str=0;
				bt::Variant bv;
				bv.setString(val);
				if ((*typei)==typeInt()) {
					_int32 valr=bv.getInt();
					par->var=(void*)(_voidint)valr;
				}
				if ((*typei)==typeFloat()) {
					float valr=bv.getFloat();
					_voidint iv=*((_int32*)&valr);
					par->var=(void*)iv;
				}
			}
		}
		if (par) param->assign(par);
		typei++;

		isstr=false;
		f=s;
		while (s<next && *s!=',') s++;
		if (*s==',') { max--; } else s=f;
		while (s<next && *s!=')') {
			s++;
		}
		c=next;
		if (*s!=')') {
			s=f;
			while (s<next && *s!='\'') s++;
			if (*s=='\'') isstr=true;
		} else {
			max--;
			break;
		}
	}

	if (max>0) {
		*(bt::ShortString*)&sscript->errorString="";
		sscript->errorCode=2;
		return 0;
	}
	if (max<0) {
		*(bt::ShortString*)&sscript->errorString="";
		sscript->errorCode=3;
		return 0;
	}
	return c;
}

void _APICALL scriptParser(void *script,char*text)
{
	sScript *sscript=(sScript *)script;
	VoidVector<void> *bs=(VoidVector<void> *)&sscript->build;
	char *p=text;
	char *next;
	sscript->errorCode=0;
	sscript->strNum=0;
	char val[128];
	if (!p) return;
	sScriptItemInfo *returnValue=0;
	while (*p && sscript->errorCode==0) {
		next=p;
		int len=0;
		while (!isDel(next)) {
			len++;
			next++;
		}
		if (len>127) len=127;
		char *sdel=next;
		while (*next && isDel(next)) next++;
		char *s=sdel;
		while (s!=next) {
			if (*s=='\n') sscript->strNum++;
			s++;
		}
		bool isnull=true;
		s=p;
		while (s<sdel) {if (*s!=' ') isnull=false; s++;}
		if (p!=sdel && !isnull) {
			extFunctions.MoveMem(p,val,len);

			val[len]=0;
			sScriptItemInfo **info=(sScriptItemInfo **)arrFunctions.MSSPFind(&(sscript->codesMap),val);
			if (!info) {
				*(bt::ShortString*)&sscript->errorString=val;
				sscript->errorCode=1;
				return;
			}
			sScriptItemInfo *sinfo=*info;
			if (sinfo->type==typeFunction()) {
				bs->assign(0);
				VoidVector<void> *params=(VoidVector<void> *)&bs->last();
				params->assign(returnValue);
				params->assign(sinfo);
				//read params!!!
				next=getparam(script,sdel,sinfo->paramCount,sinfo->attrTypes,params);
				if (!next) return;
				returnValue=0;
			} else {
				returnValue=sinfo;
			}
		}
		p=next;
	}
}

void _APICALL scriptExe(void *script)
{
	sScript *sscript=(sScript *)script;
	VoidVector<void> *bs=(VoidVector<void> *)&sscript->build;
	unsigned int count=bs->count();
	VoidVector<void> *data=(VoidVector<void> *)bs->data();
	while (count>0) {
		void**bf=data->data();
		sScriptItemInfo *rezInfo=(sScriptItemInfo *)bf[0];
		sScriptItemInfo *sinfo=(sScriptItemInfo *)bf[1];
		sScriptParamInfo **params=(sScriptParamInfo **)&(bf[2]);
		int paramcount=data->count()-2;
		void*rez=0;
		if (sinfo->var) {
			for (int i=0;i<paramcount;i++) if (params[i]->type==0) params[i]->var=((sScriptItemInfo*)params[i]->var)->var;
			if (paramcount==0) rez=((bt::tfSTDCALL_p_FUNC)sinfo->var)();
			if (paramcount==1) rez=((bt::tfSTDCALL_p_FUNC_p)sinfo->var)(params[0]->var);
			if (paramcount==2) rez=((bt::tfSTDCALL_p_FUNC_p_p)sinfo->var)(params[0]->var,params[1]->var);
			if (paramcount==3) rez=((bt::tfSTDCALL_p_FUNC_p_p_p)sinfo->var)(params[0]->var,params[1]->var,params[2]->var);
			if (paramcount==4) rez=((bt::tfSTDCALL_p_FUNC_p_p_p_p)sinfo->var)(params[0]->var,params[1]->var,params[2]->var,params[3]->var);
			if (paramcount==5) rez=((bt::tfSTDCALL_p_FUNC_p_p_p_p_p)sinfo->var)(params[0]->var,params[1]->var,params[2]->var,params[3]->var,params[4]->var);
			if (paramcount==6) rez=((bt::tfSTDCALL_p_FUNC_p_p_p_p_p_p)sinfo->var)(params[0]->var,params[1]->var,params[2]->var,params[3]->var,params[4]->var,params[5]->var);
			if (paramcount==7) rez=((bt::tfSTDCALL_p_FUNC_p_p_p_p_p_p_p)sinfo->var)(params[0]->var,params[1]->var,params[2]->var,params[3]->var,params[4]->var,params[5]->var,params[6]->var);
			if (paramcount==8) rez=((bt::tfSTDCALL_p_FUNC_p_p_p_p_p_p_p_p)sinfo->var)(params[0]->var,params[1]->var,params[2]->var,params[3]->var,params[4]->var,params[5]->var,params[6]->var,params[7]->var);
			if (paramcount==9) rez=((bt::tfSTDCALL_p_FUNC_p_p_p_p_p_p_p_p_p)sinfo->var)(params[0]->var,params[1]->var,params[2]->var,params[3]->var,params[4]->var,params[5]->var,params[6]->var,params[7]->var,params[8]->var);
		}
		if (rezInfo) rezInfo->var=rez;
		data++;
		count--;
	}

/*begin
 Subresult:=@UnRez;
 CodeProc.FirstRecord;

 with CodeProc do while RecordIndex<>0 do begin
  with PEnProc(ItemRecord)^ do begin
   Params:=Param;
   if Pro.Proc<>nil then begin
    if (Pro.T=1) then begin
     Subresult^:=_fcall(Pro);
     Subresult:=@UnRez;
    end;
    if (Pro.T=0) then _fcall(Pro);
    if (Pro.T=3) then Subresult:=Pro.Proc;
   end;
  end;
  NextRecord;
 end;*/

}

void _APICALL scriptClear(void *script) {
	sScript *sscript=(sScript *)script;
	VoidVector<void> *bs=(VoidVector<void> *)&sscript->build;
	unsigned int count=bs->count();
	VoidVector<void> *data=(VoidVector<void> *)bs->data();
	while (count>0) {
		unsigned int c=data->count();
		if (c>2) {
			void **df=data->data();
			df++;
			df++;
			while (c>2) {
				extFunctions.DeleteMem(*df,0);
				df++;
				c--;
			}
		}
		data->clear();
		data++;
		count--;
	}
	bs->clear();
	if (sscript->errorString) {
		*(ShortString*)&sscript->errorString="";
	}
}

}

OPTIMIZE_OFF;

#endif