/*
 * script.h
 *
 *  Created on: 2007 - 22.06.2008
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#if defined(SCRIPT_BT) || defined(BT_SCRIPT)
#ifndef SCRIPT_H_
#define SCRIPT_H_

#include <bt.h>

OPTIMIZE_ON;

namespace bt {

	extern void* DeffType[15];
	extern void* PIType[15];
	extern void* PIIIFIType[15];
	extern void* PFFFFFIIIType[15];
	extern void* PPIType[15];

	sScript * _APICALL scriptCreate();
	void _APICALL scriptInit(void *script, void *CodeMap, void *CodesInfo);
	void _APICALL scriptParser(void *script, char*text);
	void _APICALL scriptExe(void *script);
	void _APICALL scriptClear(void *script);

}

OPTIMIZE_OFF;

#endif /* SCRIPT_H_ */
#endif
