#include "board.h"


void board_init(fieldStruct field[totalWidth][totalHeight]){
    for (int i = 0; i < totalWidth; i++)
        for (int j = 0; j < totalHeight; j++){
            field[i][j].taken = false;
            field[i][j].pos = (sfVector2i){ i, j };
            field[i][j].rect = sfRectangleShape_create();
            sfRectangleShape_setSize(field[i][j].rect, (sfVector2f){ fSize, fSize });
            sfRectangleShape_setFillColor(field[i][j].rect, sfTransparent);
            sfRectangleShape_setPosition(field[i][j].rect, (sfVector2f){ (float)(-fSize / 2 + fSize*i), (float)(-fSize / 2 + fSize*j - 2 * fSize) });
            sfRectangleShape_setOutlineThickness(field[i][j].rect, 0.5);
            sfRectangleShape_setOutlineColor(field[i][j].rect, (sfColor){ 127, 127, 127, 255 });
        }

    for (int i = 0; i < totalWidth; i++){
        sfRectangleShape_setOutlineThickness(field[i][0].rect, 0);
        sfRectangleShape_setOutlineThickness(field[i][1].rect, 0);
        sfRectangleShape_setOutlineThickness(field[i][totalHeight - 1].rect, 0);
        field[i][0].taken = true;
        field[i][totalHeight - 1].taken = true;
    }
    for (int j = 0; j < totalHeight; j++){
        sfRectangleShape_setOutlineThickness(field[0][j].rect, 0);
        sfRectangleShape_setOutlineThickness(field[totalWidth - 1][j].rect, 0);
        field[0][j].taken = true;
        field[totalWidth - 1][j].taken = true;
    }
}

void board_clearRow(fieldStruct field[totalWidth][totalHeight], int j) {
#if DEBUG
    if (j<1 || j>totalHeight - 1)
        printf("wrong in clearRow: %d", j);
#endif
    for (int i = 1; i < totalWidth - 1; i++) {
        sfRectangleShape_setFillColor(field[i][j].rect, sfTransparent);
        field[i][j].taken = false;
    }
}

bool board_isRowFull(fieldStruct field[totalWidth][totalHeight], int j) {
#if DEBUG
    if (j<1 || j>totalHeight - 1)
        printf("wrong in isRowFull: %d", j);
#endif
    for (int i = 1; i < totalWidth - 1; i++)
        if (!field[i][j].taken)
            return false;
    return true;
}


void board_update(fieldStruct field[totalWidth][totalHeight], int *stepRate, int *points){
    for (int j = 1; j < totalHeight - 1; j++)
        if (board_isRowFull(field, j)){
            if (*stepRate > minStepRate)
                *stepRate -= 50 * 1000;
            *points = *points + 1;
            board_clearRow(field, j);
            for (int k = j; k > 2; k--){
                for (int i = 1; i < totalWidth - 1; i++){
                    field[i][k].taken = field[i][k - 1].taken;
                    sfRectangleShape_setFillColor(field[i][k].rect, sfRectangleShape_getFillColor(field[i][k - 1].rect));
                }
            }
        }
}

void board_draw(sfRenderWindow *wind, fieldStruct field[totalWidth][totalHeight]){
    for (int i = 0; i < totalWidth; i++)
        for (int j = 0; j < totalHeight; j++)
            sfRenderWindow_drawRectangleShape(wind, field[i][j].rect, NULL);
}

void board_destroy(fieldStruct field[totalWidth][totalHeight]){
    for (int i = 0; i < totalWidth; i++)
        for (int j = 0; j < totalHeight; j++)
            sfRectangleShape_destroy(field[i][j].rect);
}