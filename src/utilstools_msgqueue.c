/*
 * tools_msgqueue.c
 *
 *  Created on: 9 août 2020
 *      Author: bruno
 */

#include <mqueue.h>
#include <stdio.h>

#include "utilstools_msgqueue.h"

#define HARD_MAX  (8192U)

int fushMessageQueue(int a_Fd)
{
    int     result = 0;
    char    vBufferOUT[HARD_MAX] = {0};

    int     vLenReceive = 0;
    struct mq_attr oldAttr = {0};
    struct mq_attr newAttr = {0};

    result =  mq_getattr(a_Fd, &oldAttr);

    newAttr = oldAttr;

    newAttr.mq_flags |= O_NONBLOCK;

    result = mq_setattr(a_Fd, &newAttr ,0);

    do{
        vLenReceive =  mq_receive(a_Fd,
                vBufferOUT,
                HARD_MAX,
                0U);

//        printf("%s : vLenReceive=%d \n",__FUNCTION__,vLenReceive);

    }while(0 < vLenReceive);

    result = mq_setattr(a_Fd, &oldAttr ,0);

    return result;
}//int fushMessageQueue(int a_Fd)





//****************************************************
//*
//*
//****************************************************
int getMqClientname(  const char* a_UniqID,           // in
                const char *a_Svcname,          // in
                char       a_MqFilename[NAME_MAX])   // out
{
    int             result = 0;
    char vProcessname[NAME_MAX];

    result = getProcessname(vProcessname);

    snprintf(a_MqFilename,NAME_MAX-1,"/%.100s.%.20s.%.100s",
            vProcessname,a_UniqID,a_Svcname);

    return result;
}
