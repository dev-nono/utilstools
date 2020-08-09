/*
 * pthreadutils.c
 *
 *  Created on: 7 août 2020
 *      Author: bruno
 */

#include <errno.h>

#include <utilstools_pthreadutils.h>

//**********************************************
// return : 0 if ok
//          EINVAL invalid arg
//          error code
//**********************************************
int pcond_init(pcond_t *a_pCond)
{
    int result = 0;
//  pthread_ condattr_t  cond_attrib  = {0};
    pthread_mutexattr_t mutex_attrib = {0};

    if( ! a_pCond )
    {
        result = EINVAL;
    }
    else
    {
        //**************************************************************
        //                      mutex
        //**************************************************************

        //**********************
        // mutex attrib

        result = pthread_mutexattr_init(&mutex_attrib);
        result = pthread_mutexattr_settype(&mutex_attrib, PTHREAD_MUTEX_DEFAULT);

        //**********************
        // mutex
        result = pthread_mutex_init(& a_pCond->mutex,&mutex_attrib);

        result = pthread_mutexattr_destroy(&mutex_attrib);

        //**************************************************************
        //                      condition
        //**************************************************************
        result = pthread_cond_init(&a_pCond->condition ,0);
    }

    return result;
}
//**********************************************
// return : 0 if ok
//          EINVAL invalid arg
//**********************************************
int pcond_lock(pcond_t *a_pCond)
{
    int result = 0;

    if( ! a_pCond )
    {
        result = EINVAL;
    }
    else
    {
        result = pthread_mutex_lock(&a_pCond->mutex);
    }

    return result;
}
//**********************************************
// return : 0 if ok
//          EINVAL invalid arg
//**********************************************
int pcond_unlock(pcond_t *a_pCond)
{
    int result = 0;

    if( ! a_pCond )
    {
        result = EINVAL;
    }
    else
    {
        result = pthread_mutex_unlock(&a_pCond->mutex);

    }

    return result;
}
//**********************************************
// return : 0 if ok
//          EINVAL invalid arg
//**********************************************

int pcond_signal( pcond_t *a_pCond)
{
    int result = 0;

    if( ! a_pCond )
    {
        result = EINVAL;
    }
    else
    {
        result = pthread_cond_signal(&a_pCond->condition);
    }

    return result;
}
//**********************************************
// return : 0 if ok
//          EINVAL invalid arg
//**********************************************
int pcond_wait(  pcond_t *a_pCond)
{
    int result = 0;

    if( ! a_pCond )
    {
        result = EINVAL;
    }
    else
    {
        result = pthread_cond_wait(&a_pCond->condition, &a_pCond->mutex);

    }

    return result;
}

//**********************************************
// return : 0 if ok
//          EINVAL invalid arg
//**********************************************
int pcond_timedwait(  pcond_t *a_pCond, const struct timespec a_absTime)
{
    int result = 0;

    if( ! a_pCond )
    {
        result = EINVAL;
    }
    else
    {
        result = pthread_cond_timedwait(&a_pCond->condition ,
                &a_pCond->mutex,
                &a_absTime);

    }

    return result;
}



