#include "linkedList.h"

/*
Funkcja zapisuj¹ca listê wyników, uzupe³nion¹ o nowy rekord.
Parametry:
    score - uzyskany wynik;
    **l - wskaŸnik na listê jednokierunkowa, do której bêdziemy
zapisywaæ wyniki.
Funkcja nie zwraca wartoœci, a jeœli score = 0, do razu koñczy
pracê, poniewa¿ wynik '0' jest domyœlny.
*/
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

/*
Funkcja wczytujaca liste wyników z pliku.
Parametry:
    **l - wskaŸnik na listê jednokierunkowa
Funkcja zwraca wartosc true, gdy udalo sie
otworzyc plik i wczytac wyniki, w przeciwnym
wypadku funkcja zwraca wartosc false.
*/
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

/*
Funkcja usuwaj¹ca historiê wyników.
Parametry, wartoœæ zwracana - brak.
*/
void IO_clear(){
    FILE *file = fopen(fileName, "w");
    fclose(file);
}
