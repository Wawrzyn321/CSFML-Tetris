#include "brick.h"

void board_addBrick(brickStruct *brick){
#if DEBUG
    if (brick->type != 'O' && brick->type != 'T' && brick->type != 'S' && brick->type != 'Z' && brick->type != 'I' && brick->type != 'L' && brick->type != 'J'){
        printf("Unknown brick type in board_addBrick!: %c", brick->type);
        system("pause");
        return;
    }
#endif
    if (brick->type == 'O'){
        brick->poses[0] = (sfVector2i){ fWidth / 2, 1 };
        brick->poses[1] = (sfVector2i){ fWidth / 2 + 1, 1 };
        brick->poses[2] = (sfVector2i){ fWidth / 2, 2 };
        brick->poses[3] = (sfVector2i){ fWidth / 2 + 1, 2 };
        brick->col = color_O;
        brick->pivot = (sfVector2i){ fWidth / 2, 1 };
    }
    else if (brick->type == 'T'){
        brick->poses[0] = (sfVector2i){ fWidth / 2, 1 };
        brick->poses[1] = (sfVector2i){ fWidth / 2 - 1, 2 };
        brick->poses[2] = (sfVector2i){ fWidth / 2, 2 };
        brick->poses[3] = (sfVector2i){ fWidth / 2 + 1, 2 };
        brick->pivot = (sfVector2i){ fWidth / 2, 2 };
        brick->col = color_T;
    }
    else if (brick->type == 'I'){
        brick->poses[0] = (sfVector2i){ fWidth / 2, 0 };
        brick->poses[1] = (sfVector2i){ fWidth / 2, 1 };
        brick->poses[2] = (sfVector2i){ fWidth / 2, 2 };
        brick->poses[3] = (sfVector2i){ fWidth / 2, 3 };
        brick->pivot = (sfVector2i){ fWidth / 2, 2 };
        brick->col = color_I;
    }
    else if (brick->type == 'L'){
        brick->poses[0] = (sfVector2i){ fWidth / 2, 1 };
        brick->poses[1] = (sfVector2i){ fWidth / 2, 2 };
        brick->poses[2] = (sfVector2i){ fWidth / 2, 3 };
        brick->poses[3] = (sfVector2i){ fWidth / 2 + 1, 3 };
        brick->pivot = (sfVector2i){ fWidth / 2, 2 };
        brick->col = color_L;
    }
    else if (brick->type == 'J'){
        brick->poses[0] = (sfVector2i){ fWidth / 2 + 1, 1 };
        brick->poses[1] = (sfVector2i){ fWidth / 2 + 1, 2 };
        brick->poses[2] = (sfVector2i){ fWidth / 2 + 1, 3 };
        brick->poses[3] = (sfVector2i){ fWidth / 2, 3 };
        brick->pivot = (sfVector2i){ fWidth / 2, 2 };
        brick->col = color_J;
    }
    else if (brick->type == 'S'){
        brick->poses[0] = (sfVector2i){ fWidth / 2, 1 };
        brick->poses[1] = (sfVector2i){ fWidth / 2, 2 };
        brick->poses[2] = (sfVector2i){ fWidth / 2 + 1, 2 };
        brick->poses[3] = (sfVector2i){ fWidth / 2 + 1, 3 };
        brick->pivot = (sfVector2i){ fWidth / 2, 2 };
        brick->col = color_S;
    }
    else if (brick->type == 'Z'){
        brick->poses[0] = (sfVector2i){ fWidth / 2 + 1, 1 };
        brick->poses[1] = (sfVector2i){ fWidth / 2 + 1, 2 };
        brick->poses[2] = (sfVector2i){ fWidth / 2, 2 };
        brick->poses[3] = (sfVector2i){ fWidth / 2, 3 };
        brick->pivot = (sfVector2i){ fWidth / 2, 2 };
        brick->col = color_Z;
    }

    for (int i = 0; i < 4; i++){
        brick->elements[i] = sfRectangleShape_create();
        sfRectangleShape_setSize(brick->elements[i], (sfVector2f){ fSize, fSize });
        sfRectangleShape_setPosition(brick->elements[i], (sfVector2f){ fSize*brick->poses[i].x - fSize / 2.0f, fSize*brick->poses[i].y - fSize / 2.0f });
        sfRectangleShape_setOutlineThickness(brick->elements[i], 1);
        sfRectangleShape_setOutlineColor(brick->elements[i], sfWhite);
        sfRectangleShape_setFillColor(brick->elements[i], brick->col);
    }

}

void brick_destroy(brickStruct *brick){
    if (brick == NULL)
        return;
    for (int i = 0; i < 4 && brick->elements[i] != NULL; i++)
        sfRectangleShape_destroy(brick->elements[i]);
    free(brick);
}

bool brick_moveHorizontal(fieldStruct field[totalWidth][totalHeight], brickStruct *brick, int delta){
    for (int i = 0; i < 4; i++)
        if (field[brick->poses[i].x + delta][brick->poses[i].y].taken)
            return false;
    for (int i = 0; i < 4; i++){
        sfRectangleShape_setFillColor(field[brick->poses[i].x][brick->poses[i].y].rect, sfTransparent);
        brick->poses[i].x += delta;
    }
    brick->pivot.x += delta;
    for (int i = 0; i < 4; i++)
        sfRectangleShape_setFillColor(field[brick->poses[i].x][brick->poses[i].y].rect, brick->col);
    return true;
}

bool brick_isPositionValid(fieldStruct field[totalWidth][totalHeight], sfVector2i vec[4]){
    for (int i = 0; i < 4; i++)
        if (field[vec[i].x][vec[i].y].taken == true)
            return false;
    return true;
}

bool brick_moveDown(fieldStruct field[totalWidth][totalHeight], brickStruct *brick){
    for (int i = 0; i < 4; i++)
        if (field[brick->poses[i].x][brick->poses[i].y + 1].taken)
            return false;
    for (int i = 0; i < 4; i++){
        sfRectangleShape_setFillColor(field[brick->poses[i].x][brick->poses[i].y].rect, sfTransparent);
        brick->poses[i].y += 1;
    }
    brick->pivot.y++;
    for (int i = 0; i < 4; i++)
        sfRectangleShape_setFillColor(field[brick->poses[i].x][brick->poses[i].y].rect, brick->col);
    return true;
}

void brick_place(fieldStruct field[totalWidth][totalHeight], brickStruct *brick){
    for (int i = 0; i < 4; i++){
        sfRectangleShape_setFillColor(field[brick->poses[i].x][brick->poses[i].y].rect, brick->col);
        field[brick->poses[i].x][brick->poses[i].y].taken = true;
    }
    brick_destroy(brick);
}

bool brick_rotate(fieldStruct field[totalWidth][totalHeight], brickStruct *brick){
    sfVector2i possiblePos[4];
    sfVector2i pivot = brick->pivot;
    for (int i = 0; i < 4; i++){
        int x = brick->poses[i].x - pivot.x;
        int y = brick->poses[i].y - pivot.y;
        int newXBrickCenter = pivot.x - y;
        int newYBrickCenter = pivot.y + x;
        possiblePos[i] = (sfVector2i){ newXBrickCenter, newYBrickCenter };
    }
    if (!brick_isPositionValid(field, possiblePos))
        return false;
    else
    {
        for (int i = 0; i < 4; i++){
            sfRectangleShape_setFillColor(brick->elements[i], sfTransparent);
            sfRectangleShape_setFillColor(field[brick->poses[i].x][brick->poses[i].y].rect, sfTransparent);
        }
        for (int i = 0; i < 4; i++){
            brick->poses[i] = possiblePos[i];
            sfRectangleShape_setFillColor(field[brick->poses[i].x][brick->poses[i].y].rect, brick->col);
        }
    }
    return true;
}

bool brick_rotate2(fieldStruct field[totalWidth][totalHeight], brickStruct *brick, int shift){
    if (!brick_moveHorizontaly(field, brick, shift))
        return false;
    if (brick_rotate(field, brick))
        return true;
    else
        brick_moveHorizontaly(field, brick, -shift);
    return false;
}