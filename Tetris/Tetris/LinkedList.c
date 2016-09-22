#include "LinkedList.h"


/*
Funkcja dodaj�ca element na pocz�tek listy.
Parametry:
    *l - wska�nik na element
    val - liczba ca�kowita (warto�� nowego elementu)
Warto�� zwracana:
    wska�nik na element
*/
LinkedList *LinkedList_push_front(LinkedList *l, int val) {
    size_t LinkedList_size = sizeof(LinkedList);
    if (!l) {
        l = malloc(LinkedList_size);
        l->val = val;
        l->pNext = NULL;
        return l;
    }
    else {
        LinkedList *element = malloc(LinkedList_size);
        element->val = val;
        element->pNext = l;
        return element;
    }
}

/*
Funkcja dodaj�ca element na koniec listy.
Parametry:
    *l - wska�nik na element
    val - liczba ca�kowita (warto�� nowego elementu)
Warto�� zwracana:
    wska�nik na element
*/
LinkedList *LinkedList_push_back(LinkedList *l, int val) {
    size_t LinkedList_size = sizeof(LinkedList);
    if (!l) {
        l = malloc(LinkedList_size);
        l->val = val;
        l->pNext = NULL;
        return l;
    }
    LinkedList *LinkedList_temp = l;
    while (LinkedList_temp->pNext)
        LinkedList_temp = LinkedList_temp->pNext;

    LinkedList *element = malloc(LinkedList_size);
    element->pNext = NULL;
    element->val = val;
    LinkedList_temp->pNext = element;
    return l;
}

/*
Funkcja wstawiaj�ca element do listy, zachowuj�c kolejno�� rosn�c�.
Parametry:
    *l - wska�nik na element listy jednokierunkowej
    val - liczba ca�kowita (warto�� nowego elementu)
Warto�� zwracana:
    wska�nik na element
*/
LinkedList *LinkedList_insert_in_order(LinkedList *l, int val){
    size_t LinkedList_size = sizeof(LinkedList);
    if (!l){
        l = malloc(LinkedList_size);
        l->pNext = NULL;
        l->val = val;
        return l;
    }
    if (l->val >= val){
        LinkedList *element = malloc(LinkedList_size);
        element->pNext = l;
        element->val = val;
        return element;
    }
    LinkedList *LinkedList_temp = l;
    while (LinkedList_temp->pNext){
        if (LinkedList_temp->pNext->val >= val){
            LinkedList *element = malloc(LinkedList_size);
            element->pNext = LinkedList_temp->pNext;
            element->val = val;
            LinkedList_temp->pNext = element;
            return l;
        }
        LinkedList_temp = LinkedList_temp->pNext;
    }
    LinkedList *element = malloc(LinkedList_size);
    element->pNext = NULL;
    element->val = val;
    LinkedList_temp->pNext = element;
    return l;
}

/*
Funkcja wstawiaj�ca element do listy, zachowuj�c kolejno�� malej�c�.
Parametry:
    *l - wska�nik na element listy jednokierunkowej
    val - liczba ca�kowita(warto�� nowego elementu)
Warto�� zwracana :
    wska�nik na element
*/
LinkedList *LinkedList_insert_in_order_reverse(LinkedList *l, int val){
    size_t LinkedList_size = sizeof(LinkedList);
    if (!l){
        l = malloc(LinkedList_size);
        l->pNext = NULL;
        l->val = val;
        return l;
    }
    if (l->val <= val){
        LinkedList *element = malloc(LinkedList_size);
        element->pNext = l;
        element->val = val;
        return element;
    }
    LinkedList *LinkedList_temp = l;
    while (LinkedList_temp->pNext){
        if (LinkedList_temp->pNext->val <= val){
            LinkedList *element = malloc(LinkedList_size);
            element->pNext = LinkedList_temp->pNext;
            element->val = val;
            LinkedList_temp->pNext = element;
            return l;
        }
        LinkedList_temp = LinkedList_temp->pNext;
    }
    LinkedList *element = malloc(LinkedList_size);
    element->pNext = NULL;
    element->val = val;
    LinkedList_temp->pNext = element;
    return l;
}

/*
Funkcja zwracaj�ca d�ugo�� listy.
Parametry:
    *l - wska�nik na element listy jednokierunkowej
Warto�� zwracana:
    size - liczba ca�kowita okre�laj�ca d�ugo�� listy.
*/
int LinkedList_getSize(LinkedList *l) {
    int size = 0;
    while (l) {
        size++;
        l = l->pNext;
    }
    return size;
}

/*
Funkcja wypisuj�ca zawarto�� listy na standardowe wyj�cie.
Parametry:
    *l - wska�nik na element listy jednokierunkowej
Warto�� zwracana: brak.
*/
void LinkedList_show(LinkedList *l) {
    printf("LinkedList\n");
    printf("%d elements:\n", LinkedList_getSize(l));
    while (l) {
        printf("%d\n", l->val);
        l = l->pNext;
    }
    printf("\n");
}

/*
Funkcja dealokuj�ca list�.
Parametry:
    **l - wska�nik na wska�nik na element listy jednokierunkowej
Warto�� zwracana: brak.
*/
void LinkedList_destroy(LinkedList **l) {
    LinkedList* temp = *l;
    LinkedList* next;
    while (temp) {
        next = temp->pNext;
        free(temp);
        temp = next;
    }
    *l = NULL;
}

/*
Funkcja zwracaj�ca z listy warto�� elementu o podanym indeksie.
Parametry:
    *l - wska�nik na element listy jednokierunkowej
    index - liczba ca�kowita b�d�ca indeksem
Warto�� zwraca:
    warto�� index-ego elementu

Je�li indexx wykracza poza zakres <0, d�ugo�� listy-1>,
funkcja zwraca warto�� 0.
*/
int LinkedList_getVal(LinkedList *l, int index) {
    if (index < 0 || index > LinkedList_getSize(l) - 1)
        return 0;
    while (index > 0) {
        index--;
        l = l->pNext;
    }
    return l->val;
}

/*
Funkcja zwracaj�ca z listy wska�nik na element o podanym indeksie
Parametry:
    *l - wska�nik na element listy jednokierunkowej
    index - liczba ca�kowita b�d�ca indeksem
Warto�� zwracana:
    wska�nik na ��dany element

Je�li indexx wykracza poza zakres <0, d�ugo�� listy - 1>,
funkcja zwraca warto�� NULL.
*/
LinkedList *LinkedList_getElementRef(LinkedList *l, int index) {
    if (index < 0 || index > LinkedList_getSize(l) - 1)
        return NULL;
    while (index > 0) {
        index--;
        l = l->pNext;
    }
    return l;
}