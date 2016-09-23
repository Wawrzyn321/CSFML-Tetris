#include "LinkedList.h"

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

int LinkedList_getSize(LinkedList *l) {
    int size = 0;
    while (l) {
        size++;
        l = l->pNext;
    }
    return size;
}

void LinkedList_show(LinkedList *l) {
    printf("LinkedList\n");
    printf("%d elements:\n", LinkedList_getSize(l));
    while (l) {
        printf("%d\n", l->val);
        l = l->pNext;
    }
    printf("\n");
}

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

int LinkedList_getVal(LinkedList *l, int index) {
    if (index < 0 || index > LinkedList_getSize(l) - 1)
        return 0;
    while (index > 0) {
        index--;
        l = l->pNext;
    }
    return l->val;
}

LinkedList *LinkedList_getElementRef(LinkedList *l, int index) {
    if (index < 0 || index > LinkedList_getSize(l) - 1)
        return NULL;
    while (index > 0) {
        index--;
        l = l->pNext;
    }
    return l;
}