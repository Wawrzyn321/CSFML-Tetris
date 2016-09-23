#ifndef BRICK_H
#define BRICK_H
#include "board.h"

//adding new brick
void board_addBrick(brickStruct *brick);

//releasing memory
void brick_destroy(brickStruct *brick);

//shift on X axis
bool brick_moveHorizontaly(fieldStruct field[totalWidth][totalHeight], brickStruct *brick, int delta);

//checking brick position
bool brick_isPositionValid(fieldStruct field[totalWidth][totalHeight], sfVector2i vec[4]);

//moving the brick to the bottom of board
bool brick_moveDown(fieldStruct field[totalWidth][totalHeight], brickStruct *brick);

//place brick on the board
void brick_place(fieldStruct field[totalWidth][totalHeight], brickStruct *brick);

//brick rotation
bool brick_rotate(fieldStruct field[totalWidth][totalHeight], brickStruct *brick);

//brick rotation with shifting - used when brick touches the wall
bool brick_rotate2(fieldStruct field[totalWidth][totalHeight], brickStruct *brick, int shift);
#endif