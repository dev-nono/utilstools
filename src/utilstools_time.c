/*
 * utilstools_time.c
 *
 *  Created on: 9 août 2020
 *      Author: bruno
 */

#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>


#include "utilstools_time.h"


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
    __uint64_t    secnano    = 0;
    __uint64_t    vtime      = 0;

    secnano = a_Date.tv_sec * 1e9;
    vtime   = a_Date.tv_nsec + secnano;

    result = (double)(vtime / 1e9);

    return result;
}
