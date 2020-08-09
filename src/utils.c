 /*
 * utils.c
 *
 *  Created on: 10 juil. 2020
 *      Author: bruno
 */

#include <fcntl.h> /* Définition des constantes AT_* */
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <libgen.h>
#include <stdint.h>

#include <fcntl.h>           /* Pour les constantes O_* */
#include <sys/stat.h>        /* Pour les constantes des modes */
#include <mqueue.h>
#include <errno.h>

#include <utilstools.h>

//          1         2         3
// 1234567890123456789012345678901234567890
//


//****************************************************
//*
//*
//****************************************************
const char * getDateRawStr(char *a_BufferDate )
//const char * getDateRawStr()
{
    int             result = 0;
    char            vBuffer[DOUBLE_MANTIS_SIZE] = {0};
    struct timespec vDate= {0,0};

    if ( a_BufferDate)
    {
        result = clock_gettime(CLOCK_MONOTONIC_RAW,&vDate);
        result = DOUBLE_MANTIS_SIZE - 3;

        snprintf(vBuffer,result, "%4ld.%09ld",vDate.tv_sec,vDate.tv_nsec);

       strncpy(a_BufferDate,vBuffer,DOUBLE_MANTIS_SIZE-1);

       a_BufferDate[DOUBLE_MANTIS_SIZE-1] = 0;
    }

    return a_BufferDate;
}
//****************************************************
//*
//*
//****************************************************
double getDateRawDouble()
{
    double             result = 0;
    struct timespec vDate= {0,0};

    result = clock_gettime(CLOCK_MONOTONIC_RAW,&vDate);

//    result = vDate.tv_sec;
//    result += (vDate.tv_nsec*1.0) * (double)(1e-9 * 1.0);
//
    result = getDateDouble(vDate);

    return result;
}
//****************************************************
//*
//*
//****************************************************
double  getDateDouble(const struct timespec a_Date)
{
    double      result      = 0;
    u_int64_t    secnano    = 0;
    u_int64_t    vtime      = 0;

    secnano = a_Date.tv_sec * 1e9;
    vtime   = a_Date.tv_nsec + secnano;

    result = (double)(vtime / 1e9);

    return result;
}

//****************************************************
//*
//*
//****************************************************
int getFifoname(char* a_Fifoname)
{
    int             result = 0;
    char vProcessname[NAME_MAX];

    result = getProcessname(vProcessname);

    int long vTID  = syscall(SYS_gettid);

    snprintf(a_Fifoname,PATH_MAX-1,"/tmp/%s.%ld",vProcessname,vTID);

    return result;
}
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
//****************************************************
//* /tmp/process1.srv1.12345
//*
//****************************************************
int getUniqname(    const char* a_Path,           // in
                    const char *a_Svcname,          // in
                    char       a_ClientFilename[NAME_MAX])   // out
{
    int         result                  = 0;
    char        vProcessname[NAME_MAX]  = {0};
    int long    vTID  = syscall(SYS_gettid);

    result = getProcessname(vProcessname);

    snprintf(a_ClientFilename,NAME_MAX-1,
            "%.100s/%.50s.%.50s.%ld",a_Path,vProcessname,a_Svcname,vTID);

    return result;
}
//****************************************************
//*
//*
//****************************************************
int getProcessname(char* a_Processname)
{
    int             result = 0;
    char vLinkname[PATH_MAX];
    char *pBasename = 0;


    result = readlink("/proc/self/exe", vLinkname, PATH_MAX-1);

    pBasename = basename(vLinkname);

    strncpy(a_Processname,pBasename,NAME_MAX-1);

    return (result > 0) ? 0 : -1;
}


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


int timeradd_ts(    struct timespec a_Time1,
                    struct timespec a_Time2,
                    struct timespec *a_Time_result )
{
    int result = 0;

    if( !a_Time_result )
    {
        result = EINVAL;
    }
    else
    {
        a_Time_result->tv_nsec = a_Time1.tv_nsec + a_Time2.tv_nsec;
        a_Time_result->tv_sec  = a_Time1.tv_sec  + a_Time2.tv_sec;
        if (a_Time_result->tv_nsec >= NS_PER_SECOND)
        {
            a_Time_result->tv_nsec -= NS_PER_SECOND;
            a_Time_result->tv_sec++;
        }
        else if (a_Time_result->tv_nsec <= -NS_PER_SECOND)
        {
            a_Time_result->tv_nsec += NS_PER_SECOND;
            a_Time_result->tv_sec--;
        }
    }

    return result;
}

int time_cnv_double_to_ts(double a_date,  struct timespec *a_pTime )
{
    int result = 0;

    uint64_t intdatenano    = (uint64_t)a_date * 1e9;
    uint64_t datenano       = a_date * 1e9;
    uint64_t diffnano       = datenano - intdatenano;

    a_pTime->tv_sec  = intdatenano / 1e9;
    a_pTime->tv_nsec = diffnano ;

    return result;
}
int timeradd_real(struct timespec a_Time2,struct timespec *a_Time_result )
{
    int result = 0;
    struct timespec a_Time1 = {0,0};

    result = clock_gettime(CLOCK_REALTIME, &a_Time1);

    timeradd_ts(a_Time1,a_Time2,a_Time_result);

    return result;
}

int timeradd_raw(struct timespec a_Time2,struct timespec *a_Time_result )
{
    int result = 0;
    struct timespec Time1 = {0,0};

    result = clock_gettime(CLOCK_MONOTONIC_RAW, &Time1);

    timeradd_ts(Time1,a_Time2,a_Time_result);

    return result;
}

int timeradd_gtofd(struct timeval a_Time2,struct timeval *a_Time_result )
{
    int result = 0;
    struct timeval Time1 = {0};

    result =  gettimeofday(&Time1,0);

    timeradd(&Time1,&a_Time2,a_Time_result);

    return result;
}

