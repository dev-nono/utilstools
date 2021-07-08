/*
 * pthreadutils.h
 *
 *  Created on: 7 août 2020
 *      Author: bruno
 */

#ifndef INC_UTILSTOOLS_PTHREADUTILS_H_
#define INC_UTILSTOOLS_PTHREADUTILS_H_

#include <pthread.h>
#include <time.h>


#include "utilstools.h"

typedef struct pcond_s
{
    pthread_cond_t  condition;
    pthread_mutex_t mutex;

}pcond_t;



int pcond_init(  pcond_t *a_pCond);
int pcond_lock(  pcond_t *a_pCond);
int pcond_unlock(pcond_t *a_pCond);
int pcond_signal(pcond_t *a_pCond);
int pcond_wait(  pcond_t *a_pCond);
int pcond_timedwait(  pcond_t *a_pCond, const struct timespec);




#endif /* INC_UTILSTOOLS_PTHREADUTILS_H_ */
