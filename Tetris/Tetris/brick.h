#ifndef BRICK_H
#define BRICK_H
#include "board.h"

//dodanie nowego klocka
void board_addBrick(brickStruct *brick);

//zwolnienie pamiêci zajmowanej przez klocek
void brick_destroy(brickStruct *brick);

//przesuniêcie klocka na osi X
bool brick_moveHorizontaly(fieldStruct field[totalWidth][totalHeight], brickStruct *brick, int delta);

//sprawdzenie, czy pozycja klocka jest dozwolona
bool brick_isPositionValid(fieldStruct field[totalWidth][totalHeight], sfVector2i vec[4]);

//przesuniêcie klocka o jedno pole w dó³
bool brick_moveDown(fieldStruct field[totalWidth][totalHeight], brickStruct *brick);

//ustawienie klocka na planszy
void brick_place(fieldStruct field[totalWidth][totalHeight], brickStruct *brick);

//obrót klocka
bool brick_rotate(fieldStruct field[totalWidth][totalHeight], brickStruct *brick);

//obrót klocka z przesuniêciem
bool brick_rotate2(fieldStruct field[totalWidth][totalHeight], brickStruct *brick, int shift);
#endif