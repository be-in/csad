/*
 * basenetconnection.cpp
 *
 *  Created on: 25.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include "basenetconnection.h"
#include <core/system.h>
#include <core/module.h>
#include <platform/library.h>

OPTIMIZE_ON;

namespace csad {

	enum States {
		VALIDED = 0x011F1C01,
		FREE = 0
	};

	//#if defined (OS_WIN)
	struct sLibConnectFunctions {
		int version;
		bt::tfSTDCALL_p_FUNC_int_int_int socket;
		bt::tfSTDCALL_p_FUNC_p_p_p accept;
		bt::tfSTDCALL_int_FUNC_p_p_int bind;
		bt::tfSTDCALL_int_FUNC_p_int listen;
		bt::tfSTDCALL_int_FUNC_p_p_int connect;
		bt::tfSTDCALL_int_FUNC_p close;
		bt::tfSTDCALL_int_FUNC_int_p_p_p_p select;
		bt::tfSTDCALL_int_FUNC_p_p_int_int recv;
		bt::tfSTDCALL_int_FUNC_p_p_int_int_p_p recvfrom;
		bt::tfSTDCALL_int_FUNC_p_p_int_int send;
		bt::tfSTDCALL_int_FUNC_p_p_int_int_p_p sendto;
		bt::tfSTDCALL_uint_FUNC_uint ehtonl;
		bt::tfSTDCALL_int_FUNC connectError;
	};
	//#endif

	unsigned int fisNetLibVal=FREE;
	sLibConnectFunctions connectFunctions;
	const char* connectionModuleName="net";

	#if defined (OS_QNX)
	const char* connectionLibName="socket";
	#endif

	#if defined (OS_WIN)
	WSADATA connection_WSADATA;
	const char* connectionLibName="wsock32";
	#endif

	#if defined (OS_LINUX)
	const char* connectionLibName="socket";
	#endif

	#if defined (OS_OSX)
	const char* connectionLibName="socket";
	#endif

	Module * connectLib()
	{
		Module *module=System::system().getModule(connectionModuleName);
		if (!module) {
			ShortString cpath;
			Library::findLib(&cpath,"",connectionLibName);
			module=System::system().createModule(cpath.str(),connectionModuleName);
		}
		if (!module->isInit() || !module) {
#ifdef LOG_CSAD
			Log::console("connectLib: Can't use connection library!");
#endif
			return 0;
		}
		return module;
	}

	#define INITNetPROCS() void *local;
	#define NetProc(name,set,type) local=(void*)(module->getProc(name)); if (local) {set=(type)local;}// else {Log::console("getProc null %s",name);}

	//#if defined (OS_WIN)
	void connectionInitNetFunctions(void *_conteiner)
	{
		if (fisNetLibVal==VALIDED) return;
		fisNetLibVal=VALIDED;
		csad::sLibConnectFunctions *as=(csad::sLibConnectFunctions *)_conteiner;
		as->version=0;

		Module *module=connectLib();
		if (!module) return;

		INITNetPROCS();

		extFunctions.CleanMem(as,sizeof(bt::sFunctionsGLContext));

		NetProc("socket",as->socket,bt::tfSTDCALL_p_FUNC_int_int_int);
		NetProc("accept",as->accept,bt::tfSTDCALL_p_FUNC_p_p_p);
		NetProc("bind",as->bind,bt::tfSTDCALL_int_FUNC_p_p_int);
		NetProc("listen",as->listen,bt::tfSTDCALL_int_FUNC_p_int);
		NetProc("connect",as->connect,bt::tfSTDCALL_int_FUNC_p_p_int);
		NetProc("closesocket",as->close,bt::tfSTDCALL_int_FUNC_p);
		NetProc("select",as->select,bt::tfSTDCALL_int_FUNC_int_p_p_p_p);
		NetProc("recv",as->recv,bt::tfSTDCALL_int_FUNC_p_p_int_int);
		NetProc("recvfrom",as->recvfrom,bt::tfSTDCALL_int_FUNC_p_p_int_int_p_p);
		NetProc("send",as->send,bt::tfSTDCALL_int_FUNC_p_p_int_int);
		NetProc("sendto",as->sendto,bt::tfSTDCALL_int_FUNC_p_p_int_int_p_p);
		NetProc("htonl",as->ehtonl,bt::tfSTDCALL_uint_FUNC_uint);
		#if defined (OS_WIN)
		NetProc("WSAGetLastError",as->connectError,bt::tfSTDCALL_int_FUNC);
		#else
		NetProc("GetLastError",as->connectError,bt::tfSTDCALL_int_FUNC);
		#endif
		
		#if defined (OS_WIN)
		bt::tfSTDCALL_int_FUNC_int_p start;
		NetProc("WSAStartup",start,bt::tfSTDCALL_int_FUNC_int_p);
		start(MAKEWORD(2, 2),&connection_WSADATA);
		#endif
	}

	//#endif

	void _APICALL _NetInit()
	{
		connectionInitNetFunctions(&connectFunctions);
	}

	void _APICALL _NetConnectionCreateDEF(void*connection)
	{
		sConnectionData *cn=(sConnectionData *)connection;
		connectionInitNetFunctions(&connectFunctions);
		cn->mode=csad::NetConnection::NC_TCP;
		cn->handle=(void*)-1;
		cn->port=0;
		char c[sizeof(sockaddr_in)+1];
		extFunctions.StocBMem(c,sizeof(sockaddr_in),'a');
		c[sizeof(sockaddr_in)]=0;
		cn->addr="123";
		sockaddr_in * maddr=(sockaddr_in*)cn->addr.str();
		maddr->sin_family=AF_INET;
		maddr->sin_port=0;
#if defined (OS_WIN)
		maddr->sin_addr.S_un.S_addr=connectFunctions.ehtonl(INADDR_ANY);
#endif
#if defined (OS_LINUX)
		maddr->sin_addr.s_addr=connectFunctions.ehtonl(INADDR_ANY);
#endif
	}

	bool _APICALL _NetConnectionOpenDEF(void*connection)
	{
		sConnectionData *cn=(sConnectionData *)connection;
		if (cn->handle!=(void*)_voidintmax) return false;
		sockaddr_in * maddr=(sockaddr_in*)cn->addr.str();
		if (cn->mode==csad::NetConnection::NC_TCP) cn->handle=(void*)connectFunctions.socket(maddr->sin_family,SOCK_STREAM,IPPROTO_TCP);
		if (cn->mode==csad::NetConnection::NC_UDP) cn->handle=(void*)connectFunctions.socket(maddr->sin_family,SOCK_DGRAM,IPPROTO_UDP);
		if (cn->mode==csad::NetConnection::NC_RAW) cn->handle=(void*)connectFunctions.socket(maddr->sin_family,SOCK_RAW,IPPROTO_RAW);
		if (cn->handle==(void*)(_voidint)0 || cn->handle==(void*)_voidintmax) {
			cn->handle=(void*)_voidintmax;
#ifdef LOG_CSAD
			Log::console("socket function failed with error = %d\n", connectFunctions.connectError() );
#endif
			return false;
		}
		if (connectFunctions.bind(cn->handle,maddr,sizeof(sockaddr_in))==-1) {
#ifdef LOG_CSAD
			Log::console("socket function failed with error = %d\n", connectFunctions.connectError() );
#endif
			connectFunctions.close(cn->handle);
			cn->handle=(void*)_voidintmax;
			return false;
		}
		return true;
	}

	bool _APICALL _NetConnectionConnectDEF(void*connection)
	{
		sConnectionData *cn=(sConnectionData *)connection;
		if (cn->handle!=(void*)_voidintmax) return false;
		sockaddr_in * maddr=(sockaddr_in*)cn->addr.str();
		if (cn->mode==csad::NetConnection::NC_TCP) cn->handle=(void*)connectFunctions.socket(maddr->sin_family,SOCK_STREAM,IPPROTO_TCP);
		if (cn->mode==csad::NetConnection::NC_UDP) cn->handle=(void*)connectFunctions.socket(maddr->sin_family,SOCK_DGRAM,IPPROTO_UDP);
		if (cn->mode==csad::NetConnection::NC_RAW) cn->handle=(void*)connectFunctions.socket(maddr->sin_family,SOCK_RAW,IPPROTO_RAW);
		if (cn->handle==(void*)(_voidint)0) {
			cn->handle=(void*)_voidintmax;
			return false;
		}
		if (connectFunctions.connect(cn->handle,maddr,sizeof(sockaddr_in))==-1) {
			return false;
		}
		return true;
	}

	void* _APICALL _NetConnectionAcceptDEF(void *connect)
	{
		sConnectionData *cn=(sConnectionData *)connect;
		sockaddr maddrs;
		int maddrlen=sizeof(maddrs);
		void* sock=(void*)connectFunctions.accept(cn->handle,&maddrs,&maddrlen);
		sConnectionData *connection = (sConnectionData *)extFunctions.CreateMem(sizeof(sConnectionData), 0);
		sockaddr_in * maddr=(sockaddr_in*)&maddrs;
#if defined (OS_WIN)
		_NetConnectionSetIP4DEF(connection,(char*)&(maddr->sin_addr.S_un.S_un_b),0);
#endif
#if defined (OS_LINUX)
		_NetConnectionSetIP4DEF(connection,(char*)&(maddr->sin_addr.s_addr),0);
#endif
		cn->handle=sock;
		return connection;
	}

	bool _APICALL _NetConnectionCloseDEF(void*connection)
	{
		sConnectionData *cn=(sConnectionData *)connection;
		if (cn->handle==(void*)-1) return false;
		if (connectFunctions.close(cn->handle)==-1)
		{
			return false;
		}
		cn->handle=(void*)-1;
		return true;
	}

	void _APICALL _NetConnectionSetIP4DEF(void *connection,char*addr,int port)
	{
		sConnectionData *cn=(sConnectionData *)connection;
		sockaddr_in * maddr=(sockaddr_in*)cn->addr.str();
#if defined (OS_WIN)
		maddr->sin_addr.S_un.S_un_b.s_b1=addr[0];
		maddr->sin_addr.S_un.S_un_b.s_b2=addr[1];
		maddr->sin_addr.S_un.S_un_b.s_b3=addr[2];
		maddr->sin_addr.S_un.S_un_b.s_b4=addr[3];
#endif
#if defined (OS_LINUX)
		maddr->sin_addr.s_addr=*(unsigned _int32*)addr;
#endif
		cn->port=port;
		maddr->sin_port=((port&0xFF)<<8) + ((port&0xFF00)>>8);
	}

	unsigned _int32 _APICALL _NetConnectionGetIP4DEF(void *connection)
	{
		sConnectionData *cn=(sConnectionData *)connection;
		sockaddr_in * maddr=(sockaddr_in*)cn->addr.str();
		unsigned _int32 ret;
		ret=*(unsigned _int32*)&(maddr->sin_addr);
		return ret;
	}

	int _APICALL _NetConnectionReadDEF(void *connect,void*data,unsigned int size)
	{
		sConnectionData *cn=(sConnectionData *)connect;
		sockaddr_in * maddr=(sockaddr_in*)cn->addr.str();
		int maddrlen=sizeof(sockaddr_in);
		TIMEVAL timer;
		timer.tv_sec=0;
		timer.tv_usec=0;
		fd_set set;
		FD_ZERO(&set);
		FD_SET((SOCKET)cn->handle,&set);
		int count=connectFunctions.select(0,&set,0,0,&timer);
		if (count==0) return 0;
		if (count==-1) {
#ifdef LOG_CSAD
			Log::console("socket function failed with error = %d\n", connectFunctions.connectError() );
#endif
			return 0;
		}
		if (cn->mode==csad::NetConnection::NC_TCP) return connectFunctions.recv(cn->handle,(char*)data,size,0);
		if (cn->mode==csad::NetConnection::NC_RAW || cn->mode==csad::NetConnection::NC_UDP) return connectFunctions.recvfrom(cn->handle,(char*)data,size,0,maddr,&maddrlen);
		return 0;
	}

	int _APICALL _NetConnectionWriteDEF(void *connect,void*data,unsigned int size)
	{
		sConnectionData *cn=(sConnectionData *)connect;
		sockaddr_in * maddr=(sockaddr_in*)cn->addr.str();
		int maddrlen=sizeof(sockaddr_in);
		if (cn->mode==csad::NetConnection::NC_TCP) return connectFunctions.send(cn->handle,(char*)data,size,0);
		if (cn->mode==csad::NetConnection::NC_RAW || cn->mode==csad::NetConnection::NC_UDP) return connectFunctions.sendto(cn->handle,(char*)data,size,0,maddr,&maddrlen);
		return 0;
	}

}

OPTIMIZE_OFF;
