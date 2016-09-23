#ifndef BOARD_H
#define BOARD_H
#include "define.h"

//init board
void board_init(fieldStruct field[totalWidth][totalHeight]);

//clearing single row
void board_clearRow(fieldStruct field[totalWidth][totalHeight], int j);

//checking if row is full
bool board_isRowFull(fieldStruct field[totalWidth][totalHeight], int j);

//updating the board (stepRate and points can be modified)
void board_update(fieldStruct field[totalWidth][totalHeight], int *stepRate, int *points);

//drawing board on screen
void board_draw(sfRenderWindow *wind, fieldStruct field[totalWidth][totalHeight]);

//releasing memory
void board_destroy(fieldStruct field[totalWidth][totalHeight]);

#endif