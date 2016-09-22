#ifndef BRICK_H
#define BRICK_H
#include "board.h"

//dodanie nowego klocka
void board_addBrick(brickStruct *brick);

//zwolnienie pami�ci zajmowanej przez klocek
void brick_destroy(brickStruct *brick);

//przesuni�cie klocka na osi X
bool brick_moveHorizontaly(fieldStruct field[totalWidth][totalHeight], brickStruct *brick, int delta);

//sprawdzenie, czy pozycja klocka jest dozwolona
bool brick_isPositionValid(fieldStruct field[totalWidth][totalHeight], sfVector2i vec[4]);

//przesuni�cie klocka o jedno pole w d�
bool brick_moveDown(fieldStruct field[totalWidth][totalHeight], brickStruct *brick);

//ustawienie klocka na planszy
void brick_place(fieldStruct field[totalWidth][totalHeight], brickStruct *brick);

//obr�t klocka
bool brick_rotate(fieldStruct field[totalWidth][totalHeight], brickStruct *brick);

//obr�t klocka z przesuni�ciem
bool brick_rotate2(fieldStruct field[totalWidth][totalHeight], brickStruct *brick, int shift);
#endif