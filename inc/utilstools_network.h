/*
 * network.h
 *
 *  Created on: 9 août 2020
 *      Author: bruno
 */

#ifndef INC_UTILSTOOLS_NETWORK_H_
#define INC_UTILSTOOLS_NETWORK_H_


#include "utilstools.h"

// set sockaddr.sun_family = AF_UNSPEC;
int net_resetConnectSocket(int a_socket);
int net_ConnectSocketUnix(int a_socket,const char* a_clientFilename);

#endif /* INC_UTILSTOOLS_NETWORK_H_ */
