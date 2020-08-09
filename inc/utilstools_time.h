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
int timeradd_real (struct timespec a_Time2,struct timespec *a_Time_result );
int timeradd_raw  (struct timespec a_Time2,struct timespec *a_Time_result );
int timeradd_gtofd(struct timeval  a_Time2,struct timeval  *a_Time_result );

int time_cnv_double_to_ts(double a_date,  struct timespec *a_pTime );



const char *    getDateRawStr();
const char *    getDateRaw(char *a_BufferDate);
double          getDateRawDouble();
double          getDateDouble(const struct timespec a_Date);


#endif /* INC_UTILSTOOLS_TIME_H_ */
