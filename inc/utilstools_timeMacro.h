/*
 * utilstools_timeMacro.h
 *
 *  Created on: 18 janv. 2021
 *      Author: bruno
 */

#ifndef INC_UTILSTOOLS_TIMEMACRO_H_
#define INC_UTILSTOOLS_TIMEMACRO_H_

#include <limits.h>
#include <time.h>
#include <sys/time.h>

#include "utilstools.h"



/**
 * \fn          timeradd_ts_macro( a_Time1,a_Time2,a_Time_result )
 *
 * \brief   facility tools struct timespec macro
 *           add a_Time1 + a_Time2 in a_Time_result
 *           use only utilstoos.h do not need link libutilstools.so
 *
 * \param       struct timespec a_Time1     _IN
 *              struct timespec a_Time2     _IN
 *              struct timespec *a_Time_result _OUT);
 *
 * \return      nothing
 */
#define timeradd_ts_macro( a_Time1,a_Time2,a_Time_result )\
do{\
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
}while(0)

#endif /* INC_UTILSTOOLS_TIMEMACRO_H_ */
