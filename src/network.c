/*
 * network.c
 *
 *  Created on: 9 août 2020
 *      Author: bruno
 */

#include <stdio.h>
#include <string.h>

#include "utilstools_network.h"


int net_resetConnectSocket(int a_socket)
{
    int result = 0;

    struct sockaddr_un sockaddr = {0};

    if( 0 > a_socket)
    {
        result = EINVAL;
    }
    else
    {
        memset(&sockaddr, 0, sizeof(struct sockaddr_un));
        sockaddr.sun_family = AF_UNSPEC;

        result = connect(a_socket, (struct sockaddr *) &sockaddr,
                sizeof(struct sockaddr_un)) ;

        if( -1 == result  )
        {
            fprintf(stderr,"%s : connect(%d,%s)=%d errn=%d %s ",
                    __FUNCTION__,a_socket,"AF_UNSPEC",
                    result,errno,strerror(errno) );
            result = errno;
        }
    }

    return result;
}

int net_ConnectSocketUnix(int a_socket,const char* a_clientFilename)
{
    int result = 0;

    struct sockaddr_un sockaddr = {0};

    if( ( 0 > a_socket) || (! *a_clientFilename) )
    {
        result = EINVAL;
    }
    else
    {
        memset(&sockaddr, 0, sizeof(struct sockaddr_un));

        sockaddr.sun_family = AF_UNIX;

        strncpy(sockaddr.sun_path, a_clientFilename,sizeof(sockaddr.sun_path) - 1);

        result = connect(a_socket, (struct sockaddr *) &sockaddr,sizeof(struct sockaddr_un)) ;

        if( -1 == result  )
        {
            fprintf(stderr,"%s : connect(%d,%s)=%d errn=%d %s ",
                    __FUNCTION__,a_socket,a_clientFilename,result,errno,strerror(errno) );
            result = errno;
        }
    }

    return result;
}
