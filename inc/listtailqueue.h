/*
 * listtailqueue.h
 *
 *  Created on: 3 août 2020
 *      Author: bruno
 */

#ifndef INC_LISTTAILQUEUE_H_
#define INC_LISTTAILQUEUE_H_


#include <stddef.h>
#include <sys/queue.h> // double list
#include <pthread.h>

#define LQ_ITEMS  items

#define FOR_TQ(pItem,plistID) \
    for (   pItem = plistID->head.tqh_first; \
            pItem != NULL; \
            pItem = pItem->LQ_ITEMS.tqe_next )




struct ListQ
{
    TAILQ_HEAD(s_tailhead, s_item) head;
    //struct s_tailhead *headp;                 /* Tête de liste double */

    struct s_item {
        TAILQ_ENTRY(s_item) LQ_ITEMS;         /* Liste double */
        void *pData;
    } s_item;
    pthread_mutex_t mutex;
    unsigned int sizedata;
};

typedef struct ListQ ListQ_t;
typedef struct s_tailhead s_tailhead_t;
typedef struct s_item  s_item_t;

//***************************************************
// int        tq_init(ListQ_t *a_pList,int a_sizedata)
//             ListQ_t *pList          : pointer to list-
//             int      a_sizedata     : sizeof(userdata) to allocate
//                                        0 = no allocation, need to manual alloc
//                                        do not use pointer null
//
// initialize the list object
//
// return : 0
//***************************************************
int        tq_init(ListQ_t *a_pList,int a_sizedata);

int tq_lock(ListQ_t *a_pList);
int tq_unlock(ListQ_t *a_pList);

//***************************************************
// int tq_createItem()
//
// create a empty item
//
// return : (s_item_t *)item pointer allocated
//          no data allocated
//***************************************************
s_item_t * tq_createItem();

//***************************************************
// int        tq_createItemList(ListQ_t *a_pList)
//             ListQ_t *pList          :
//
// create a item and allocate data pointer with a_pList.sizedate
//
// return : (s_item_t *)item pointer allocated
//***************************************************
s_item_t * tq_createItemList(ListQ_t *a_pList);


//***************************************************
// int tq_destroyItem()
//
// destroy a item create with tq_createItem()
//      tq_destroyItem() do not make detach when is in any list !
//      use tq_removeItemList() before use tq_destroyItem()
//
// return : no
//***************************************************
void tq_destroyItem(s_item_t   *a_pItem);


s_item_t * tq_insertHead(ListQ_t   *a_pList);
s_item_t * tq_insertTail(ListQ_t   *a_pList);
s_item_t * tq_insertAfter( ListQ_t *a_pList,s_item_t   *a_pItem);

s_item_t * tq_insertItemHead(ListQ_t *a_pList, s_item_t   *a_pItem);
s_item_t * tq_insertItemTail(ListQ_t *a_pList, s_item_t   *a_pItem);
s_item_t * tq_insertItemAfter( ListQ_t     *a_pList,
                    s_item_t   *a_pItem,
                    s_item_t   *a_pItemToAdd);
s_item_t * tq_removeHeadList(ListQ_t *a_pList);
s_item_t * tq_removeTailList(ListQ_t *a_pList);
s_item_t * tq_removeItemList(ListQ_t *a_pList,s_item_t *a_pItem );

void tq_eraseHeadList(ListQ_t *a_pList);
void tq_eraseTailList(ListQ_t *a_pList);
void tq_eraseItemList(ListQ_t *a_pList,s_item_t *a_pItem );

void tq_clearList(ListQ_t *a_pList);
void tq_eraseList(ListQ_t *a_pList);





#endif /* INC_LISTTAILQUEUE_H_ */
