/*
 * tailq.c
 *
 *  Created on: 3 août 2020
 *      Author: bruno
 */

#include <stdlib.h>
#include <string.h>

#include "listtailqueue.h"




//**********************************************************
//*
//**********************************************************
int tq_Init(ListQ_t *a_pList)
{
    int result = 0;

    memset(a_pList,0,sizeof(ListQ_t));

    TAILQ_INIT(&a_pList->head);                      /* Initialisation de liste */


    pthread_mutexattr_t attrib;

    pthread_mutexattr_init(&attrib);

    pthread_mutexattr_settype(&attrib, PTHREAD_MUTEX_RECURSIVE_NP);

    pthread_mutex_init(& a_pList->mutex,&attrib);

    pthread_mutexattr_destroy(&attrib);


    return result;
}
//**********************************************************
//*
//**********************************************************
int tq_lock(ListQ_t *a_pList)
{
    int result = 0;

    result = pthread_mutex_lock(&a_pList->mutex);

    return result;
}
//**********************************************************
//*
//**********************************************************
int tq_unlock(ListQ_t *a_pList)
{
    int result = 0;

    result = pthread_mutex_unlock(&a_pList->mutex);

    return result;
}
//**********************************************************
//*
//**********************************************************
s_item_t * tq_insertHead(ListQ_t *a_pList, void* a_pData)
{
    tq_lock(a_pList);

    s_item_t *pItem = malloc(sizeof( s_item_t));

    TAILQ_INSERT_HEAD(&a_pList->head, pItem, LQ_ENTRIES);

    pItem->pData = a_pData;

    tq_unlock(a_pList);

    return pItem;
}
//**********************************************************
//*
//**********************************************************
s_item_t * tq_insertTail(ListQ_t *a_pList,  void* a_pData)
{
    tq_lock(a_pList);

    s_item_t *pItem = malloc(sizeof( s_item_t));

    TAILQ_INSERT_TAIL(&a_pList->head, pItem, LQ_ENTRIES);

    pItem->pData = a_pData;

    tq_unlock(a_pList);

    return pItem;
}
//**********************************************************
//*
//**********************************************************
s_item_t * tq_insertAfter( ListQ_t     *a_pList,
                    s_item_t   *a_pItem,
                    void        *a_pData)
{
    tq_lock(a_pList);

    s_item_t *pItemToAdd = malloc(sizeof( s_item_t));

    TAILQ_INSERT_AFTER( &a_pList->head,
                        a_pItem,
                        pItemToAdd,
                        LQ_ENTRIES);

    pItemToAdd->pData = a_pData;

    tq_unlock(a_pList);

    return pItemToAdd;
}

//**********************************************************
//*
//**********************************************************
void tq_EraseHead(ListQ_t *a_pList)
{
    tq_lock(a_pList);

    s_item_t *pItem = a_pList->head.tqh_first;

    tq_EraseItem(a_pList,pItem );

    tq_unlock(a_pList);

}
//**********************************************************
//*
//**********************************************************
 void tq_EraseItem(ListQ_t *a_pList,s_item_t *a_pItem )
{
     tq_lock(a_pList);

    if( a_pItem->pData)
        free(a_pItem->pData);

   a_pItem->pData = 0;

    TAILQ_REMOVE(&a_pList->head, a_pItem, LQ_ENTRIES);

    free(a_pItem);
    a_pItem = 0;

    tq_unlock(a_pList);

}
 void   tq_clear(ListQ_t *a_pList)
 {
     tq_lock(a_pList);

     while (a_pList->head.tqh_first != NULL)
     {
         tq_EraseHead(a_pList);
     }

     tq_unlock(a_pList);

 }

//**********************************************************
//*
//**********************************************************
void * tq_RemoveHead(ListQ_t *a_pList)
{
    tq_lock(a_pList);

    s_item_t *pItem = a_pList->head.tqh_first;

    tq_RemoveItem(a_pList, pItem);

    tq_unlock(a_pList);

    return (void*)pItem->pData;
}
//**********************************************************
//*
//**********************************************************
void * tq_RemoveItem(ListQ_t *a_pList,s_item_t *a_pItem )
{
    tq_lock(a_pList);

    TAILQ_REMOVE(&a_pList->head, a_pItem, LQ_ENTRIES);

    tq_unlock(a_pList);

    return (void*)a_pItem->pData;

}
