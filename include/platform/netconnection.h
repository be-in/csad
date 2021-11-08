/*
 * netconnection.h
 *
 *  Created on: 25.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef NETCONNECTION_H_
#define NETCONNECTION_H_

#include <platform/platformapi.h>
#include <platform/platformfunctions.h>
#include <bt.h>

namespace csad {

/**
 * @class NetConnection
 *
 * @ingroup platform
 * @brief NetConnection - network connection.
 *
 * For example UDP:
 @verbatim
   NetConnection connection;
   connection.setMode(NC_UDP);
   connection.setPort(2000);
   connection.setAddr(0,0,0,0);
   connection.open();
   char data[256];
   connection.write(data,256);
   while (connection.read(data,256)==0);
   unsigned _int32 recvAddr=connection.addr();
   connection.setAddr(192,168,102,10);
   while (connection.write(data,256)==0);
   connection.close();
 @endverbatim
 *
 * For example TCP client:
 @verbatim
   NetConnection connection;
   connection.setMode(NC_TCP);
   connection.setPort(2000);
   connection.setAddr(192,168,102,20);
   connection.connect();
   char data[256];
   connection.write(data,256);
   connection.close();
 @endverbatim
 *
 * @see platform
 */

class NetConnection {
public:
	MEMDEFAULT(NetConnection)

	/// socket mode
	enum Mode {
		/// create TCP connection
		NC_TCP,
		/// create UDP connection
		NC_UDP,
		/// create RAW connection
		NC_RAW,
	};

	/// create connection
	_FORCEINLINE NetConnection(char * ) { platformFunctions.NetConnectionCreate(&mdata); }
	/// set connection mode
	_FORCEINLINE void setMode(unsigned int mode) { mdata.mode=mode; }

	/// set port connection, or for open listening
	_FORCEINLINE void setPort(_int32 port) { platformFunctions.NetConnectionSetIP4(&mdata,(void*)mdata.addr.str(),port); }
	/// return connection port.
	_FORCEINLINE _int32 port() { return mdata.port; }
	/// set connection addres.
	_FORCEINLINE void setAddr(char a,char b,char c,char d) { char cd[4]={a,b,c,d}; platformFunctions.NetConnectionSetIP4(&mdata,(void*)cd,mdata.port); }
	/// return connection or last recv data addres.
	_FORCEINLINE unsigned _int32 addr() { return platformFunctions.NetConnectionGetIP4(&mdata); }

	/// Open socket
	_FORCEINLINE bool open() { return platformFunctions.NetConnectionOpen(&mdata); }
	/// Connect
	_FORCEINLINE bool connect() { return platformFunctions.NetConnectionConnect(&mdata); }
	/// Close socket
	_FORCEINLINE bool close() { return platformFunctions.NetConnectionClose(&mdata); }

	/// recive data
	_FORCEINLINE int read(void *data,unsigned int size) {return platformFunctions.NetConnectionRead(&mdata,data,size);}
	/// send data
	_FORCEINLINE int write(void *data,unsigned int size) {return platformFunctions.NetConnectionWrite(&mdata,data,size);}

	/// recive connection and create new NetConnection.
	_FORCEINLINE NetConnection *accept(char * ) {NetConnection *data=(NetConnection *)platformFunctions.NetConnectionAccept(&mdata); return data;}
private:
	sConnectionData mdata;
};

}

#endif /* NETCONNECTION_H_ */
