#include "linkedList.h"

/*
Funkcja zapisuj�ca list� wynik�w, uzupe�nion� o nowy rekord.
Parametry:
    score - uzyskany wynik;
    **l - wska�nik na list� jednokierunkowa, do kt�rej b�dziemy
zapisywa� wyniki.
Funkcja nie zwraca warto�ci, a je�li score = 0, do razu ko�czy
prac�, poniewa� wynik '0' jest domy�lny.
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
Funkcja wczytujaca liste wynik�w z pliku.
Parametry:
    **l - wska�nik na list� jednokierunkowa
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
Funkcja usuwaj�ca histori� wynik�w.
Parametry, warto�� zwracana - brak.
*/
void IO_clear(){
    FILE *file = fopen(fileName, "w");
    fclose(file);
}
