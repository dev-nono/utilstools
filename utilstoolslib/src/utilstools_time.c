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

/**
 * \fn          int timeradd_ts(    struct timespec a_Time1,
 *                                  struct timespec a_Time2,
 *                                  struct timespec *a_Time_result );
 *
 * \brief   facility tools struct timespec
 *          add a_Time1 + a_Time2 in a_Time_result
 *
 * \param       struct timespec a_Time1
 *              struct timespec a_Time2
 *              struct timespec *a_Time_result );
 *
 * \return      nothing
 */
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
/**
 * \fn      int time_cnv_double_to_ts(double a_date,  struct timespec *a_pTime );
 *
 * \brief   convert double to struct timespec
 *
 * \param   double a_date               : date to convert
 * \param   struct timespec *a_pTime    : output struct to fill
 * \return
 */
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
/**
 * \fn      int timeradd_real (struct timespec a_Time2,struct timespec *a_Time_result );
 *
 * \brief   facility tools struct timespec macro
 *          add a_Time2 to current date(CLOCK_REALTIME)
 *          fill a_Time_result to new date
 *
 * \param   struct timespec a_Time2);
 * \param   struct timespec *a_Time_result ); pointer to new date to fill
 *
 * \return  0 to ok
 *          error code of clock_gettime(CLOCK_REALTIME, &Time1);
 */
int timeradd_real(struct timespec a_Time2,struct timespec *a_Time_result )
{
    int result = 0;
    struct timespec a_Time1 = {0,0};

    result = clock_gettime(CLOCK_REALTIME, &a_Time1);

    timeradd_ts(a_Time1,a_Time2,a_Time_result);

    return result;
}
/**
 * \fn      int timeradd_raw (struct timespec a_Time2,struct timespec *a_Time_result );
 *
 * \brief   facility tools struct timespec macro
 *          add a_Time2 to current date(CLOCK_MONOTONIC_RAW)
 *          fill a_Time_result to new date
 *
 * \param   struct timespec a_Time2);
 * \param   struct timespec *a_Time_result ); pointer to new date to fill
 *
 * \return  0 to ok
 *          error code of clock_gettime(CLOCK_MONOTONIC_RAW, &Time1);
 */
int timeradd_raw(struct timespec a_Time2,struct timespec *a_Time_result )
{
    int result = 0;
    struct timespec Time1 = {0,0};

    result = clock_gettime(CLOCK_MONOTONIC_RAW, &Time1);

    timeradd_ts(Time1,a_Time2,a_Time_result);

    return result;
}
/**
 * \fn      int timeradd_gtofd(struct timeval  a_Time2,struct timeval  *a_Time_result );
 *
 * \brief   facility tools struct timeval
 *          add a_Time2 to current date gettimeofday(...)
 *          fill a_Time_result to new date
 *
 * \param   struct timeval a_Time2;
 * \param   struct timeval *a_Time_result ; pointer to new date to fill
 *
 * \return  0 to ok
 *          error code of gettimeofday(&Time1,0)
 */
int timeradd_gtofd(struct timeval a_Time2,struct timeval *a_Time_result )
{
    int result = 0;
    struct timeval Time1 = {0};

    result =  gettimeofday(&Time1,0);

    timeradd(&Time1,&a_Time2,a_Time_result);

    return result;
}
/**
 * \fn          const char * getDateRawStr(char *a_BufferDate )
 *
 * \brief       return string date from clock_gettime(CLOCK_MONOTONIC_RAW,&vDate);
 *
 * \param       char *a_BufferDate : string to fill
 * \return      pointer to  a_BufferDate
 *
 */
const char * getDateRawStr(char *a_BufferDate )
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
/**
 * \fn          double          getDateRawDouble();
 *
 * \brief       return date from clock_gettime(CLOCK_MONOTONIC_RAW,&vDate);
 *
 * \param
 * \return      date cast to double
 */
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
/**
 * \fn          double getDateDouble(const struct timespec a_Date);
 *
 * \brief   convert  struct timespec  to double value
 *
 * \param       const struct timespec a_Date : date to convert
 *
 * \return     date in double format
 */
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
