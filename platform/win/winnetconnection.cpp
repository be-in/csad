/*
 * winnetconnection.cpp
 *
 *  Created on: 25.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>

#if defined (OS_WIN)

#include <platform/netconnection.h>
#include <winsock.h>

OPTIMIZE_ON;

namespace csad {

/*NetConnection::NetConnection(char * name)
{
	p_handle=(void*)-1;
	p_port=0;
	char c[sizeof(sockaddr_in)+1];
	extFunctions.StocBMem(c,sizeof(sockaddr_in),'a');
	c[sizeof(sockaddr_in)]=0;
	p_addr=c;
	sockaddr_in * maddr=(sockaddr_in*)p_addr.str();
	maddr->sin_family=AF_INET;
	maddr->sin_port=0;
	maddr->sin_addr.S_un.S_addr=htonl(INADDR_ANY);
}

void NetConnection::setPort(int port)
{
	sockaddr_in * maddr=(sockaddr_in*)p_addr.str();
	maddr->sin_port=port;
}

void NetConnection::setAddr(char a,char b,char c,char d)
{
	sockaddr_in * maddr=(sockaddr_in*)&p_addr;
	maddr->sin_addr.S_un.S_un_b.s_b1=a;
	maddr->sin_addr.S_un.S_un_b.s_b2=b;
	maddr->sin_addr.S_un.S_un_b.s_b3=c;
	maddr->sin_addr.S_un.S_un_b.s_b4=d;
}

bool NetConnection::open()
{
	if (p_handle!=(void*)-1) return false;
	sockaddr_in * maddr=(sockaddr_in*)p_addr.str();
	p_handle=(void*)::socket(maddr->sin_family,SOCK_STREAM,0);
	if (::bind((SOCKET)p_handle,(sockaddr *)maddr,sizeof(maddr))==-1) {
		return false;
	}
	return true;
}

bool NetConnection::connect()
{
	if (p_handle!=(void*)-1) return false;
	sockaddr_in * maddr=(sockaddr_in*)p_addr.str();
	p_handle=(void*)::socket(maddr->sin_family,SOCK_STREAM,0);
	if (::connect((SOCKET)p_handle,(sockaddr *)maddr,sizeof(p_addr))==-1) {
		return false;
	}
	return true;
}

bool NetConnection::close()
{
	if (p_handle==(void*)-1) return false;
	if (::closesocket((SOCKET)p_handle)==-1)
	{
		return false;
	}
	p_handle=(void*)-1;
	return true;
}

NetConnection *NetConnection::accept(char * name)
{
	sockaddr maddrs;
	int maddrlen=sizeof(maddrs);
	void* sock=(void*)::accept((SOCKET)p_handle,&maddrs,&maddrlen);
	NetConnection *connection=new NetConnection(name);
	sockaddr_in * maddr=(sockaddr_in*)&maddrs;
	connection->setAddr(maddr->sin_addr.S_un.S_un_b.s_b1,maddr->sin_addr.S_un.S_un_b.s_b2,maddr->sin_addr.S_un.S_un_b.s_b3,maddr->sin_addr.S_un.S_un_b.s_b4);
	connection->p_handle=sock;
	return connection;
	return 0;
}

int NetConnection::read(void *data,char size)
{
	//::recv();
	return 0;
}

int NetConnection::write(void *data,char size)
{
	return ::send((SOCKET)p_handle,(char*)data,size,0);
}*/

}

OPTIMIZE_OFF;

#endif