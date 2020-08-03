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


#define FOR_TQ(pItem,plistID) \
    for (   pItem = plistID->head.tqh_first; \
            pItem != NULL; \
            pItem = pItem->entries.tqe_next )



#define LQ_ENTRIES  entries

struct ListQ
{
    TAILQ_HEAD(s_tailhead, s_item) head;
    //struct s_tailhead *headp;                 /* Tête de liste double */

    struct s_item {
        TAILQ_ENTRY(s_item) LQ_ENTRIES;         /* Liste double */
        void *pData;
    } s_entry;
};

typedef struct ListQ ListQ_t;
typedef struct s_tailhead s_tailhead_t;
typedef struct s_item  s_item_t;


int tq_Init(ListQ_t *pList);
s_item_t * tq_insertHead(ListQ_t *a_pList, void* a_pData);
s_item_t * tq_insertTail(ListQ_t *a_pList, void* a_pData);
s_item_t * tq_insertAfter( ListQ_t     *a_pList,
                    s_item_t   *a_pItemToAdd,
                    void        *a_pData);

void   tq_clear(ListQ_t *a_pList);
void * tq_RemoveHead(ListQ_t *a_pList);
void * tq_RemoveItem(ListQ_t *a_pList,s_item_t *a_pItem );

void tq_EraseHead(ListQ_t *a_pList);
void tq_EraseItem(ListQ_t *a_pList,s_item_t *a_pItem );






#endif /* INC_LISTTAILQUEUE_H_ */
