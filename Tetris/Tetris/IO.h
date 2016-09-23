#ifndef IO_H
#define IO_H
#include "define.h"
#include "linkedList.h"

//adding new score to list and saving it
void IO_saveScore(int score, struct LinkedList **l);

//loading scores to linked list
bool IO_loadScores(struct LinkedList **l);

//clearing the file
void IO_clear();

#endif