#include "linkedList.h"

void IO_saveScore(int score, LinkedList **l){
    if (score == 0)
        return;
    *l = LinkedList_insert_in_order_reverse(*l, score);
    int LLSize = LinkedList_getSize(*l);
    FILE *file = fopen(fileName, "w+");
    for (LinkedList *temp = *l; temp; temp = temp->pNext)
        fwrite(&(temp->val), sizeof(int), 1, file);
    fclose(file);
}

bool IO_loadScores(LinkedList **l){
    FILE *file = fopen(fileName, "rb");
    if (!file)
        return false;

    LinkedList_destroy(l);

    int val;
    while (fread(&val, sizeof(int), 1, file))
        *l = LinkedList_push_back(*l, val);

    fclose(file);
    return true;
}

void IO_clear(){
    FILE *file = fopen(fileName, "w");
    fclose(file);
}
