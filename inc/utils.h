/*
 * utils.h
 *
 *  Created on: 10 juil. 2020
 *      Author: bruno
 */

#ifndef COMMON_INC_UTILS_H_
#define COMMON_INC_UTILS_H_

#include <limits.h>
#include <time.h>
#include <sys/time.h>



#define _IN_
#define _OUT_
#define HARD_MAX  (8192U)

//*******************************************************************
//*
//*     CONSTANTES
//*
//*********************************************** ********************
#define DOUBLE_MANTIS_SIZE   (30U)
#define NS_PER_SECOND (1000000000LL)


#define FAILURE    1   /* Failing  status.  */
#define SUCCESS    0   /* Successful status.  */

//*******************************************************************
//*
//*             MACRO
//*
//*******************************************************************
#define STRINGIFY(x) #x
#define STRINGIFY_2(aa,bb)      STRINGIFY(aa ## bb)
#define STRINGIFY_3(aa,bb,cc)   STRINGIFY(aa ## bb ## cc)

#define CONCAT_POINT(_a,_b) STRINGIFY( _a._b )          // "." for semaphore filename
#define CONCAT_SEM(aa,bb) STRINGIFY_3( aa , _ , bb )    // "_" for fifo filename



int timeradd_ts(    struct timespec a_Time1,
                    struct timespec a_Time2,
                    struct timespec *a_Time_result );
int timeradd_real (struct timespec a_Time2,struct timespec *a_Time_result );
int timeradd_raw  (struct timespec a_Time2,struct timespec *a_Time_result );
int timeradd_gtofd(struct timeval  a_Time2,struct timeval  *a_Time_result );

int time_cnv_double_to_ts(double a_date,  struct timespec *a_pTime );

//*******************************************************************
//*
//*
//*
//*******************************************************************
const char *    getDateRawStr();
const char *    getDateRaw(char *a_BufferDate);
double          getDateRawDouble();
double          getDateDouble(const struct timespec a_Date);

int getFifoname(char* a_Fifoname);
int getProcessname(char* a_Processname);
int getMqClientname(  const char* a_ID,           // in
                const char *a_Svcname,      // in
                char        a_MqFilename[NAME_MAX]);   // out

int fushMessageQueue(int a_Fd);


#endif /* COMMON_INC_UTILS_H_ */

