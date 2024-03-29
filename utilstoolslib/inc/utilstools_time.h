/*
 * utilstools_time.h
 *
 *  Created on: 9 août 2020
 *      Author: bruno
 */

#ifndef INC_UTILSTOOLS_TIME_H_
#define INC_UTILSTOOLS_TIME_H_

#include <limits.h>
#include <time.h>
#include <sys/time.h>

#include "utilstools.h"

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
                    struct timespec *a_Time_result );

/**
 * \fn          timeradd_ts_macro( a_Time1,a_Time2,a_Time_result )
 *
 * \brief   facility tools struct timespec macro
 *           add a_Time1 + a_Time2 in a_Time_result
 *           use only utilstoos.h do not need link libutilstools.so
 *
 * \param       struct timespec a_Time1
 *              struct timespec a_Time2
 *              struct timespec *a_Time_result );
 *
 * \return      nothing
 */
#define timeradd_ts_macro( a_Time1,a_Time2,a_Time_result )\
{\
        a_Time_result.tv_nsec = a_Time1.tv_nsec + a_Time2.tv_nsec;\
        a_Time_result.tv_sec  = a_Time1.tv_sec  + a_Time2.tv_sec;\
        if (a_Time_result.tv_nsec >= NS_PER_SECOND)\
        {\
            a_Time_result.tv_nsec -= NS_PER_SECOND;\
            a_Time_result.tv_sec++;\
        }\
        else if (a_Time_result.tv_nsec <= -NS_PER_SECOND)\
        {\
            a_Time_result.tv_nsec += NS_PER_SECOND;\
            a_Time_result.tv_sec--;\
        }\
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
int timeradd_real (struct timespec a_Time2,struct timespec *a_Time_result );

/**
 * \fn      int timeradd_real_macro (struct timespec a_Time2,struct timespec *a_Time_result );
 *
 * \brief   facility tools struct timespec macro
 *          add a_Time2 to current date(CLOCK_REALTIME)
 *          fill a_Time_result to new date
 *           use only utilstoos.h do not need link libutilstools.so
 *
 * \param   struct timespec a_Time2);
 * \param   struct timespec *a_Time_result ); pointer to new date to fill
 *
 * \return  0 to ok
 *          error code of clock_gettime(CLOCK_REALTIME, &Time1);
 */
#define timeradd_real_macro( a_Time2,a_Time_result )\
        {\
            struct timespec vTime1 = {0,0};\
            \
            clock_gettime(CLOCK_REALTIME, &vTime1);\
            timeradd_ts_macro(vTime1,a_Time2,a_Time_result);\
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
int timeradd_raw  (struct timespec a_Time2,struct timespec *a_Time_result );
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
int timeradd_gtofd(struct timeval  a_Time2,struct timeval  *a_Time_result );

/**
 * \fn      int time_cnv_double_to_ts(double a_date,  struct timespec *a_pTime );
 *
 * \brief   convert double to struct timespec
 *
 * \param   double a_date               : date to convert
 * \param   struct timespec *a_pTime    : output struct to fill
 * \return
 */
int time_cnv_double_to_ts(double a_date,  struct timespec *a_pTime );

/**
 * \fn          const char * getDateRawStr(char *a_BufferDate )
 *
 * \brief       return string date from clock_gettime(CLOCK_MONOTONIC_RAW,&vDate);
 *
 * \param       char *a_BufferDate : string to fill
 * \return      pointer to  a_BufferDate
 */
const char * getDateRawStr(char *a_BufferDate );

/**
 * \fn          double          getDateRawDouble();
 *
 * \brief       return date from clock_gettime(CLOCK_MONOTONIC_RAW,&vDate);
 *
 * \param
 * \return      date cast to double
 */
double          getDateRawDouble();
/**
 * \fn          double getDateDouble(const struct timespec a_Date);
 *
 * \brief   convert  struct timespec  to double value
 *
 * \param       const struct timespec a_Date : date to convert
 *
 * \return     date in double format
 */
double          getDateDouble(const struct timespec a_Date);


#endif /* INC_UTILSTOOLS_TIME_H_ */
