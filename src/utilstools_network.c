/*
 * network.c
 *
 *  Created on: 9 août 2020
 *      Author: bruno
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>          /* Consultez NOTES */
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#include "utilstools_network.h"

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

/**
 * \fn      int net_ConnectSocketUnix(int a_socket,const char* a_clientFilename)
 * \brief   connect a client on socket AF_UNIX server binded
 *
 * \param       int a_socket                    : socket server binded
 * \param       const char* a_clientFilename    : filname client to connect
 *
 * \return      EINVAL invalid argument
 *              error code for connect(...)
 */
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
                            int         *a_pSocketdescriptor)
{
    int result = 0;

    if( (! (*a_BindFilename)) || !(*a_ConnectFilename) || !a_pSocketdescriptor)
    {
        result = EINVAL;
    }

    if( 0 == result)
    {
        result = net_openBind(a_BindFilename,a_pSocketdescriptor);
    }

    if( 0 == result)
    {
        result = net_ConnectSocketUnix(*a_pSocketdescriptor,a_ConnectFilename);

        if( 0 !=  result )
        {
            fprintf(stderr,"%s : net_ConnectSocketUnix(%d,%s)=%d errn=%d %s ",
                    __FUNCTION__,*a_pSocketdescriptor,a_ConnectFilename,
                    result,errno,strerror(errno) );
            *a_pSocketdescriptor = -1;
        }
    }

    return result;
}
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
int net_openBind(const char *a_BindFilename,int* a_pSocketdescriptor)
{
    int result = 0;
    int Socketdescriptor = 0;
    int yes = 1;
    struct sockaddr_un sockaddr = {0};

    unlink(a_BindFilename);

    Socketdescriptor = socket(AF_UNIX, SOCK_DGRAM, 0);

    if( -1 == Socketdescriptor )
    {
        fprintf(stderr,"%s : socket()=%d errno=%d %s ",
                __FUNCTION__,Socketdescriptor,errno,strerror(errno) );
        result = errno;
    }

    if( 0 == result )
    {
        result = setsockopt(Socketdescriptor, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if( 0 != result )
        {
            fprintf(stderr,"%s : setsockopt()=%d errno=%d %s ",
                    __FUNCTION__,result,errno,strerror(errno) );
            result = errno;
            close(Socketdescriptor);
        }
    }

    if( 0 == result)
    {
        /* Efface la structure */
        memset(&sockaddr, 0, sizeof(struct sockaddr_un));

        sockaddr.sun_family = AF_UNIX;
        strncpy(sockaddr.sun_path, a_BindFilename,
                sizeof(sockaddr.sun_path) - 1);

        result = bind(Socketdescriptor, (struct sockaddr *) &sockaddr,
                sizeof(struct sockaddr_un)) ;

        if( -1 == result  )
        {
            fprintf(stderr,"%s : bind(%d)=%d errn=%d %s ",
                    __FUNCTION__,Socketdescriptor,
                    result,errno,strerror(errno) );
            close(Socketdescriptor);
            result = errno;
        }
        else
        {
            *a_pSocketdescriptor = Socketdescriptor;
        }
    }

    return result;
}

/**
 * \fn      int libmsg_openBindConnect( const char  *a_BindFilename,
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
int libmsg_openBindConnect( const char  *a_BindFilename,
                            const char  *a_ConnectFilename,
                            int         *a_pSocketdescriptor)
{
    int result = 0;

    if( (! (*a_BindFilename)) || !(*a_ConnectFilename) || !a_pSocketdescriptor)
    {
        result = EINVAL;
    }

    if( 0 == result)
    {
        result = net_openBind(a_BindFilename,a_pSocketdescriptor);
    }

    if( 0 == result)
    {
        result = net_ConnectSocketUnix(*a_pSocketdescriptor,a_ConnectFilename);

        if( 0 !=  result )
        {
            fprintf(stderr,"%s : net_ConnectSocketUnix(%d,%s)=%d errn=%d %s ",
                    __FUNCTION__,*a_pSocketdescriptor,a_ConnectFilename,
                    result,errno,strerror(errno) );
            *a_pSocketdescriptor = -1;
        }
    }

    return result;
}



