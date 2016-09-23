#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "define.h"

//list element
typedef struct LinkedList {
    int val;
    struct LinkedList *pNext;
}LinkedList;

//adding element at the beginning
LinkedList *LinkedList_push_front(LinkedList *l, int val);

//adding element at the end
LinkedList *LinkedList_push_back(LinkedList *l, int val);

//adding element in increasing order
LinkedList *LinkedList_insert_in_order(LinkedList *l, int val);

//adding element in decreasing order
LinkedList *LinkedList_insert_in_order_reverse(LinkedList *l, int val);

//getting the count of the list
int LinkedList_getSize(LinkedList *l);

//DEBUG - showing the list
void LinkedList_show(LinkedList *l);

//releasing memory
void LinkedList_destroy(LinkedList **l);

//getting value from list's element
int LinkedList_getVal(LinkedList *l, int index);

//getting reference to list's element
LinkedList *LinkedList_getElementRef(LinkedList *l, int index);

#endif