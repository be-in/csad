/*
 * basenet.h
 *
 *  Created on: 16.09.2013
 *      Author: Александр
 */

#ifndef BASENET_H_
#define BASENET_H_

namespace csad {

class NetConnection;

class BaseNetConnection {
public:
	BaseNetConnection(char *,unsigned int,char*) {}
	// bool connected();
	// int write(char*,int);
	// int read(char*,int);
	// char* data();
	// NetConnection *getConnection();
};

}

#endif /* BASENET_H_ */
