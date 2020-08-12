/*
 * network.h
 *
 *  Created on: 9 août 2020
 *      Author: bruno
 */

#ifndef INC_UTILSTOOLS_NETWORK_H_
#define INC_UTILSTOOLS_NETWORK_H_


#include "utilstools.h"

/**
 * \fn      int net_resetConnectSocket(int a_socket)
 * \brief   deconnect a client on socket AF_UNIX server binded
 *          sun_family = AF_UNSPEC;
 *
 * \param       int a_socket                    : socket server binded
 *
 * \return      EINVAL invalid argument
 *              error code for connect(...)
 */
int net_resetConnectSocket(int a_socket);
/**
 * \fn      int net_ConnectSocketUnix(int a_socket,const char* a_clientFilename)
 * \brief   connect a client on socket AF_UNIXserver binded
 *
 * \param       int a_socket                    : socket server binded
 * \param       const char* a_clientFilename    : filname client to connect
 *
 * \return      EINVAL invalid argument
 *              error code for connect(...)
 */
int net_ConnectSocketUnix(int a_socket,const char* a_clientFilename);

/**
 * \fn      int net_openBindConnect( const char  *a_BindFilename,
 *                                      const char  *a_ConnectFilename,
 *                                      int         *a_pSocketdescriptor)
 *
 * \brief   create socket AF_UNIX, SOCK_DGRAM, bind a filename,
 *              and connect client to socked binded
 *
 * \param       const char  *a_BindFilename         : filename to bind
 * \param       const char  *a_ConnectFilename      : file to connect
 * \param       int         *a_pSocketdescriptor    : pointer to new socket create
 *
 * \return      0  no error, a_pSocketdescriptor with new socket
 *              or error for function :
 *              - socket(AF_UNIX, SOCK_DGRAM, 0);
 *              - setsockopt(Socketdescriptor, SOL_SOCKET, SO_REUSEADDR,1,)
 *              - bind(...)
 *              - connect(...)
 */
int net_openBindConnect(    const char  *a_BindFilename,
                            const char  *a_ConnectFilename,
                            int         *a_pSocketdescriptor);

/**
 * \fn      int net_openBind(const char *a_BindFilename,int* a_pSocketdescriptor)
 * \brief   create socket AF_UNIX, SOCK_DGRAM, bind a filename
 *
 * \param       const char  *a_BindFilename       : filename to bind
 * \param       int         *a_pSocketdescriptor    : pointer to new socket create
 *
 * \return      0  no error, a_pSocketdescriptor with new socket
 *              or error for function :
 *              - socket(AF_UNIX, SOCK_DGRAM, 0);
 *              - setsockopt(Socketdescriptor, SOL_SOCKET, SO_REUSEADDR,1,)
 *              - bind(...)
 */
int net_openBind(const char *a_BindFilename,int* a_pSocketdescriptor);

#endif /* INC_UTILSTOOLS_NETWORK_H_ */
