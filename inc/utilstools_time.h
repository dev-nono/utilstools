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

int timeradd_ts(    struct timespec a_Time1,
                    struct timespec a_Time2,
                    struct timespec *a_Time_result );

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

int timeradd_real (struct timespec a_Time2,struct timespec *a_Time_result );

#define timeradd_real_macro( a_Time2,a_Time_result )\
        {\
            struct timespec vTime1 = {0,0};\
            \
            clock_gettime(CLOCK_REALTIME, &vTime1);\
            timeradd_ts_macro(vTime1,a_Time2,a_Time_result);\
        }

int timeradd_raw  (struct timespec a_Time2,struct timespec *a_Time_result );
int timeradd_gtofd(struct timeval  a_Time2,struct timeval  *a_Time_result );

int time_cnv_double_to_ts(double a_date,  struct timespec *a_pTime );



const char *    getDateRawStr();
const char *    getDateRaw(char *a_BufferDate);
double          getDateRawDouble();
double          getDateDouble(const struct timespec a_Date);


#endif /* INC_UTILSTOOLS_TIME_H_ */
