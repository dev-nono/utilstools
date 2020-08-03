/*
 * tailq.c
 *
 *  Created on: 3 août 2020
 *      Author: bruno
 */

#include <stdlib.h>

#include "listtailqueue.h"



//**********************************************************
//*
//**********************************************************
int tq_Init(ListQ_t *a_pList)
{
    int result = 0;

    TAILQ_INIT(&a_pList->head);                      /* Initialisation de liste */

    return result;
}
//**********************************************************
//*
//**********************************************************
s_item_t * tq_insertHead(ListQ_t *a_pList, void* a_pData)
{
    s_item_t *pItem = malloc(sizeof( s_item_t));

    TAILQ_INSERT_HEAD(&a_pList->head, pItem, LQ_ENTRIES);

    pItem->pData = a_pData;

    return pItem;
}
//**********************************************************
//*
//**********************************************************
s_item_t * tq_insertTail(ListQ_t *a_pList,  void* a_pData)
{
    s_item_t *pItem = malloc(sizeof( s_item_t));

    TAILQ_INSERT_TAIL(&a_pList->head, pItem, LQ_ENTRIES);

    pItem->pData = a_pData;

    return pItem;
}
//**********************************************************
//*
//**********************************************************
s_item_t * tq_insertAfter( ListQ_t     *a_pList,
                    s_item_t   *a_pItem,
                    void        *a_pData)
{
    s_item_t *pItemToAdd = malloc(sizeof( s_item_t));

    TAILQ_INSERT_AFTER( &a_pList->head,
                        a_pItem,
                        pItemToAdd,
                        LQ_ENTRIES);

    pItemToAdd->pData = a_pData;

    return pItemToAdd;
}

//**********************************************************
//*
//**********************************************************
void tq_EraseHead(ListQ_t *a_pList)
{
    s_item_t *pItem = a_pList->head.tqh_first;

    tq_EraseItem(a_pList,pItem );
}
//**********************************************************
//*
//**********************************************************
 void tq_EraseItem(ListQ_t *a_pList,s_item_t *a_pItem )
{
    if( a_pItem->pData)
        free(a_pItem->pData);

   a_pItem->pData = 0;

    TAILQ_REMOVE(&a_pList->head, a_pItem, LQ_ENTRIES);

    free(a_pItem);
    a_pItem = 0;

}
 void   tq_clear(ListQ_t *a_pList)
 {
     while (a_pList->head.tqh_first != NULL)
     {
         tq_EraseHead(a_pList);
     }
 }

//**********************************************************
//*
//**********************************************************
void * tq_RemoveHead(ListQ_t *a_pList)
{

    s_item_t *pItem = a_pList->head.tqh_first;

    tq_RemoveItem(a_pList, pItem);

    return (void*)pItem->pData;
}
//**********************************************************
//*
//**********************************************************
void * tq_RemoveItem(ListQ_t *a_pList,s_item_t *a_pItem )
{
    TAILQ_REMOVE(&a_pList->head, a_pItem, LQ_ENTRIES);

    return (void*)a_pItem->pData;
}
