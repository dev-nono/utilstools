/*
 * utils.h
 *
 *  Created on: 10 juil. 2020
 *      Author: bruno
 */

#ifndef COMMON_INC_UTILS_H_
#define COMMON_INC_UTILS_H_

#include <limits.h>

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

#define util_max(a,b) \
  ({ __auto_type _a = (a); \
      __auto_type _b = (b); \
    _a > _b ? _a : _b; })

#define util_min(a,b) \
  ({ __auto_type _a = (a); \
      __auto_type _b = (b); \
    _a < _b ? _a : _b; })


//*******************************************************************
//*
//*
//*
//*******************************************************************

int getFifoname(char* a_Fifoname);
int getProcessname(char* a_Processname);
int getClientname(  const char* a_UniqID,           // in
                const char *a_Svcname,          // in
                char       a_ClientFilename[NAME_MAX]);   // out

int getUniqname(    const char* a_Path,           // in
                    const char *a_Svcname,          // in
                    char       a_ClientFilename[NAME_MAX]);   // out



//#include "utilstools_listtailqueue.h"
//#include "utilstools_pthreadutils.h"
//#include "utilstools_network.h"
//#include "utilstools_msgqueue.h"

#endif /* COMMON_INC_UTILS_H_ */

