/*
 * basenetconnection.h
 *
 *  Created on: 25.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <bt/os.h>
#include <bt/macrostype.h>

OPTIMIZE_ON;

namespace csad {

	void _APICALL _NetInit();
	void* _APICALL _NetConnectionNewDEF(char *name);
	void _APICALL _NetConnectionCreateDEF(void *connect);
	bool _APICALL _NetConnectionOpenDEF(void *connect);
	bool _APICALL _NetConnectionConnectDEF(void *connect);
	void* _APICALL _NetConnectionAcceptDEF(void *connect);
	bool _APICALL _NetConnectionCloseDEF(void *connect);
	void _APICALL _NetConnectionSetIP4DEF(void *connect,char*addr,int port);
	unsigned _int32 _APICALL _NetConnectionGetIP4DEF(void *connect);
	int _APICALL _NetConnectionReadDEF(void *connect,void*data,unsigned int size);
	int _APICALL _NetConnectionWriteDEF(void *connect,void*data,unsigned int size);

}

OPTIMIZE_OFF;
