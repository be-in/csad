/*
 *  osxnetconnection.cpp
 *
 *  Created on: 25.09.2013
 *      Author: Пантелеймонов Александр
 */

#include <platform/platformapi.h>

#if defined (OS_OSX)

#include <platform/netconnection.h>

namespace csad {

NetConnection::NetConnection(char * name)
{
	*((_voidint*)&p_handle)=-1;
}

bool NetConnection::connect()
{
	return false;
}

bool NetConnection::open()
{
	//p_handle=socket(0,0,0);
	if ((_voidint)p_handle==-1) {
		return false;
	}
	return true;
}

bool NetConnection::close()
{
	if ((_voidint)p_handle==-1) return false;
	if (::close((_voidint)p_handle)!=0) {
		return false;
	}
	*((_voidint*)&p_handle)=-1;
	return true;
}

int NetConnection::read(void *data,char size)
{
	return 0;
}

int NetConnection::write(void *data,char size)
{
	return 0;
}

NetConnection *NetConnection::accept(char * name)
{
	return 0;
}

}

#endif