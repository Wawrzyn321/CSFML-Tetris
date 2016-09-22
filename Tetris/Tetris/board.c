#include "board.h"

/*
Funkcja czyszcz¹ca podany wiersz.
Parametry:
    field[totalWidth][totalHeight] - dwuwymiarowa tablica fieldStuct
    j - odciêta wiersza
Watoœæ zwracana: brak.

Podany wiersz jest oznaczany jako pusty,
a kwadraty symbolizuj¹ce go - ustawiane
jako przezroczyste.
*/
void board_clearRow(fieldStruct field[totalWidth][totalHeight], int j){
#if DEBUG
    if (j<1 || j>totalHeight - 1)
        printf("wrong in clearRow: %d", j);
#endif
    for (int i = 1; i < totalWidth - 1; i++){
        sfRectangleShape_setFillColor(field[i][j].rect, sfTransparent);
        field[i][j].taken = false;
    }
}

/*
Funkcja czyszcz¹ca podany wiersz.
Parametry:
    field[totalWidth][totalHeight] - dwuwymiarowa tablica fieldStuct
    j - odciêta wiersza
Watoœæ zwracana: 
    true, jeœli wiersz jest zape³niony,
false - jeœli jest pusty.
*/
bool board_isRowFull(fieldStruct field[totalWidth][totalHeight], int j){
#if DEBUG
    if (j<1 || j>totalHeight - 1)
        printf("wrong in isRowFull: %d", j);
#endif
    for (int i = 1; i < totalWidth - 1; i++)
        if (!field[i][j].taken)
            return false;
    return true;
}


/*
Funkcja inicjalizuj¹ca planszê
Parametry:
    field[totalWidth][totalHeight] - dwuwymiarowa tablica fieldStuct    
Watoœæ zwracana: brak.

Pamiêæ na kwadraty przedstawiaj¹ce pole jest
rezerwowana, kwadraty s¹ odpowiednio
przemieszczane i "formatowane".
*/
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

/*
Funkcja aktualizuj¹ca planszê.
Parametry:
    field[totalWidth][totalHeight] - dwuwymiarowa tablica fieldStuct
    *stepRate - wskaŸnik na liczbê ca³kowit¹,
bêd¹c¹ czêstoœci¹ zegarowego przemieszczania
klocka w dó³.
    *points - wskaŸnik na liczbê ca³kowit¹,
bêd¹c¹ liczb¹ zdobytyh punktów.   
Watoœæ zwracana: brak.

W funkcji ka¿dy wiersz jest sprawdzany. Jeœli
jest ca³kowicie zape³niony, funkcja czyœci go
i przesuwa wszystkie klocki nad ni o jedno pole
w dó³, jednoczeœnie dodaj¹c punkt do puli oraz
przyspieszaj¹c spadanie kolejnych klocków
(o ile nie jest mniejsza lub równa 200ms).
*/
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

/*
Funkcja rysuj¹ca planszê w oknie gry.
Parametry:
    field[totalWidth][totalHeight] - dwuwymiarowa tablica fieldStuct
    *wind - wskaŸnik na okno gry
Watoœæ zwracana: brak.
*/
void board_draw(sfRenderWindow *wind, fieldStruct field[totalWidth][totalHeight]){
    for (int i = 0; i < totalWidth; i++)
        for (int j = 0; j < totalHeight; j++)
            sfRenderWindow_drawRectangleShape(wind, field[i][j].rect, NULL);
}

/*
Funkcja zwalniaj¹ca pamiêæ po planszy.
Parametry:
    field[totalWidth][totalHeight] - dwuwymiarowa tablica fieldStuct
Watoœæ zwracana: brak.
*/
void board_destroy(fieldStruct field[totalWidth][totalHeight]){
    for (int i = 0; i < totalWidth; i++)
        for (int j = 0; j < totalHeight; j++)
            sfRectangleShape_destroy(field[i][j].rect);
}