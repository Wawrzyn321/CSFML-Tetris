#ifndef IO_H
#define IO_H
#include "define.h"
#include "linkedList.h"

//Dodanie nowego rekordu i zapis wynikow do listy
void IO_saveScore(int score, struct LinkedList **l);

//Wczytanie wynikow do listy
bool IO_loadScores(struct LinkedList **l);

//Wyzerowanie listy wynikow
void IO_clear();

#endif