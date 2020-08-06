/*
 * tailq.c
 *
 *  Created on: 3 août 2020
 *      Author: bruno
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <errno.h>


#include "listtailqueue.h"




//**********************************************************
//*
//**********************************************************
int tq_init(ListQ_t *a_pList ,int a_sizedata )
{
    int result = 0;

    memset(a_pList,0,sizeof(ListQ_t));

    TAILQ_INIT(&a_pList->head);                      /* Initialisation de liste */

    a_pList->sizedata = a_sizedata;

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
ListQ_item_t * tq_insertItemHead(ListQ_t *a_pList, ListQ_item_t   *a_pItem)
{
    tq_lock(a_pList);

    TAILQ_INSERT_HEAD(&a_pList->head, a_pItem, LQ_ITEMS);

    tq_unlock(a_pList);

    return a_pItem;
}
//**********************************************************
//*
//**********************************************************
ListQ_item_t * tq_insertItemTail(ListQ_t *a_pList, ListQ_item_t *a_pItem)
{
    tq_lock(a_pList);

    TAILQ_INSERT_TAIL(&a_pList->head, a_pItem, LQ_ITEMS);

    tq_unlock(a_pList);

    return a_pItem;
}
//**********************************************************
//*
//**********************************************************
ListQ_item_t * tq_insertItemAfter( ListQ_t     *a_pList,
        ListQ_item_t   *a_pItem,
        ListQ_item_t   *a_pItemToAdd)
{
    tq_lock(a_pList);

    TAILQ_INSERT_AFTER( &a_pList->head,
            a_pItem,
            a_pItemToAdd,
            LQ_ITEMS);

    tq_unlock(a_pList);

    return a_pItemToAdd;
}

//**********************************************************
//*
//**********************************************************
ListQ_item_t * tq_createItemList(ListQ_t *a_pList)
{
    ListQ_item_t *pItem = 0;

    tq_lock(a_pList);

    pItem = tq_createItem();

    if( a_pList->sizedata )
        pItem->pData = calloc(a_pList->sizedata,sizeof(char));

    tq_unlock(a_pList);

    return pItem;
}
//**********************************************************
//*
//**********************************************************
ListQ_item_t * tq_createItem()
{
    ListQ_item_t *pItem = 0;

    pItem = (ListQ_item_t *)calloc(sizeof( ListQ_item_t),sizeof(char));

    return pItem;
}
//**********************************************************
//*
//**********************************************************
void* tq_destroyItem(ListQ_item_t *a_pItem, unsigned int a_DestroyData)
{
    void* pData = 0;

    if( a_pItem && ( a_pItem->pData) )
    {
        if( 0 !=  a_DestroyData )
            free(a_pItem->pData);
        else
            pData = a_pItem->pData ;
    }

    if( a_pItem )
    {
        free(a_pItem);
    }

    return pData;
}

//**********************************************************
//*
//**********************************************************
ListQ_item_t * tq_insertHead(ListQ_t *a_pList)
{
    tq_lock(a_pList);

    ListQ_item_t *pItem = tq_createItemList(a_pList);

    TAILQ_INSERT_HEAD(&a_pList->head, pItem, LQ_ITEMS);

    tq_unlock(a_pList);

    return pItem;
}
//**********************************************************
//*
//**********************************************************
ListQ_item_t * tq_insertTail(ListQ_t *a_pList)
{
    tq_lock(a_pList);

    ListQ_item_t *pItem = tq_createItemList(a_pList);

    TAILQ_INSERT_TAIL(&a_pList->head, pItem, LQ_ITEMS);

    tq_unlock(a_pList);

    return pItem;
}
//**********************************************************
//*
//**********************************************************
ListQ_item_t * tq_insertAfter( ListQ_t *a_pList, ListQ_item_t *a_pItem)
{
    tq_lock(a_pList);

    ListQ_item_t *pItemToAdd = tq_createItemList(a_pList);

    TAILQ_INSERT_AFTER( &a_pList->head,
            a_pItem,
            pItemToAdd,
            LQ_ITEMS);
    tq_unlock(a_pList);

    return pItemToAdd;
}
//**********************************************************
//*
//**********************************************************
void tq_eraseHeadList(ListQ_t *a_pList)
{
    tq_lock(a_pList);

    ListQ_item_t *pItem = TAILQ_FIRST(&a_pList->head);

    tq_eraseItemList(a_pList,pItem );

    tq_unlock(a_pList);
}
//**********************************************************
//*
//**********************************************************
void tq_eraseTailList(ListQ_t *a_pList)
{
    tq_lock(a_pList);

    ListQ_item_t *pItem = TAILQ_LAST(&a_pList->head,s_ListQ_tailhead);

    tq_eraseItemList(a_pList,pItem );

    tq_unlock(a_pList);
}
//**********************************************************
//*
//**********************************************************
void tq_eraseItemList(ListQ_t *a_pList,ListQ_item_t *a_pItem )
{
    tq_lock(a_pList);

//    TAILQ_REMOVE(&a_pList->head, a_pItem, LQ_ITEMS);
    tq_removeItemList(a_pList, a_pItem);

    tq_destroyItem(a_pItem, 1U );

    a_pItem = 0;

    tq_unlock(a_pList);

}
//**********************************************************
//*
//**********************************************************
void   tq_clearList(ListQ_t *a_pList)
{
    tq_lock(a_pList);

    while(!TAILQ_EMPTY(&a_pList->head))
    {
        tq_removeHeadList(a_pList);
    }

    tq_unlock(a_pList);
}

//**********************************************************
//*
//**********************************************************
void   tq_eraseList(ListQ_t *a_pList)
{
    tq_lock(a_pList);

//    while (a_pList->head.tqh_first != NULL)
    while(!TAILQ_EMPTY(&a_pList->head))
    {
        tq_eraseHeadList(a_pList);
    }

    tq_unlock(a_pList);
}
//**********************************************************
//*
//**********************************************************
ListQ_item_t * tq_removeHeadList(ListQ_t *a_pList)
{
    tq_lock(a_pList);

    ListQ_item_t *pItem = TAILQ_FIRST(&a_pList->head);

    tq_removeItemList(a_pList, pItem);

    tq_unlock(a_pList);

    return (void*)pItem;
}
//**********************************************************
//*
//**********************************************************
ListQ_item_t * tq_removeTailList(ListQ_t *a_pList)
{
    tq_lock(a_pList);

    ListQ_item_t *pItem = TAILQ_LAST(&a_pList->head,s_ListQ_tailhead);

    tq_removeItemList(a_pList, pItem);

    tq_unlock(a_pList);

    return (void*)pItem;
}
//**********************************************************
//*
//**********************************************************
ListQ_item_t * tq_removeItemList(ListQ_t *a_pList,ListQ_item_t *a_pItem )
{
    tq_lock(a_pList);

    TAILQ_REMOVE(&a_pList->head, a_pItem, LQ_ITEMS);

    tq_unlock(a_pList);

    return (void*)a_pItem;
}

//**********************************************************
//*
//**********************************************************
int tq_size(ListQ_t *a_pList)
{
    int             retcode     = -1;
    ListQ_item_t    *pItem      = 0;
    int             ii          = 0;

    tq_lock(a_pList);

    if( !a_pList )
    {
        retcode = -1;
    }
    else
    {
        FOR_TQ(pItem,a_pList)
        {
            ii++;
        }
        retcode = ii;
    }

    tq_unlock(a_pList);
    return retcode;
}
