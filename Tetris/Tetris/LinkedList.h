#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "define.h"

//element listy
typedef struct LinkedList {
    int val;
    struct LinkedList *pNext;
}LinkedList;

//dodanie elementu na pocz¹tek
LinkedList *LinkedList_push_front(LinkedList *l, int val);

//dodanie elementu na koniec
LinkedList *LinkedList_push_back(LinkedList *l, int val);

//dodanie elementu w kolejnoœci rosn¹cej
LinkedList *LinkedList_insert_in_order(LinkedList *l, int val);

//dodanie elementu w kolejnoœci malej¹cej
LinkedList *LinkedList_insert_in_order_reverse(LinkedList *l, int val);

//pobranie rozmiaru
int LinkedList_getSize(LinkedList *l);

//wyœwietlenie listy
void LinkedList_show(LinkedList *l);

//zwolnienie pamiêci
void LinkedList_destroy(LinkedList **l);

//pobranie wartoœci spod wybranego indeksu
int LinkedList_getVal(LinkedList *l, int index);

//pobranie wskaŸnika na element o podanym indeksie
LinkedList *LinkedList_getElementRef(LinkedList *l, int index);

#endif