#include "nextBrickFIeld.h"

/*
Funkcja inicjalizuj¹ca pole pokazuj¹ce kolejny klocek.
Parametry:
    nbf[4][4] - dwuwymiarowa tablica fieldStruct
Wartoœæ zwracana: brak.

Funkcja rezerwuje pamiêæ na prostok¹ty i okreœla ich
parametry.
*/
void nbf_init(fieldStruct nbf[4][4]){
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++){
            nbf[i][j].pos = (sfVector2i){ i, j };
            nbf[i][j].rect = sfRectangleShape_create();
            sfRectangleShape_setSize(nbf[i][j].rect, (sfVector2f){ fSize, fSize });
            sfRectangleShape_setFillColor(nbf[i][j].rect, sfTransparent);
            sfRectangleShape_setPosition(nbf[i][j].rect, (sfVector2f){ (float)(fSize * (fWidth + 1 + i)), (float)(fSize * (4 + j)) });
            sfRectangleShape_setOutlineThickness(nbf[i][j].rect, 0.5);  
            sfRectangleShape_setOutlineColor(nbf[i][j].rect, (sfColor){ 127, 127, 127, 255 });
        }
}

/*
Funkcja pozwalaj¹ca na okreœlenie wyœwietlanego klocka.
Parametry:
    nbf[4][4] - dwuwymiarowa tablica fieldStruct
    type - znak okreœlaj¹cy typ klocka
Wartoœæ zwracana: brak.

Funkcja "zapala" odpowiednie kwadraty w tablicy.
*/
void nbf_setBrick(fieldStruct nbf[4][4], char type){
#if DEBUG
    if (type != 'O' && type != 'T' && type != 'S' && type != 'Z' && type != 'I' && type != 'L' && type != 'J'){
        printf("Unknown brick type in nbf_setBrick!: %c", type);
        system("pause");
        return;
    }
#endif
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            sfRectangleShape_setFillColor(nbf[i][j].rect, sfTransparent);

    if (type == 'O'){
        sfRectangleShape_setFillColor(nbf[1][1].rect, color_O);
        sfRectangleShape_setFillColor(nbf[1][2].rect, color_O);
        sfRectangleShape_setFillColor(nbf[2][1].rect, color_O);
        sfRectangleShape_setFillColor(nbf[2][2].rect, color_O);
    }
    else if (type == 'T'){
        sfRectangleShape_setFillColor(nbf[0][3].rect, color_T);
        sfRectangleShape_setFillColor(nbf[1][3].rect, color_T);
        sfRectangleShape_setFillColor(nbf[1][2].rect, color_T);
        sfRectangleShape_setFillColor(nbf[2][3].rect, color_T);
    }
    else if (type == 'I'){
        sfRectangleShape_setFillColor(nbf[1][0].rect, color_I);
        sfRectangleShape_setFillColor(nbf[1][1].rect, color_I);
        sfRectangleShape_setFillColor(nbf[1][2].rect, color_I);
        sfRectangleShape_setFillColor(nbf[1][3].rect, color_I);
    }
    else if (type == 'L'){
        sfRectangleShape_setFillColor(nbf[1][1].rect, color_L);
        sfRectangleShape_setFillColor(nbf[1][2].rect, color_L);
        sfRectangleShape_setFillColor(nbf[1][3].rect, color_L);
        sfRectangleShape_setFillColor(nbf[2][3].rect, color_L);
    }
    else if (type == 'J'){
        sfRectangleShape_setFillColor(nbf[2][1].rect, color_J);
        sfRectangleShape_setFillColor(nbf[2][2].rect, color_J);
        sfRectangleShape_setFillColor(nbf[2][3].rect, color_J);
        sfRectangleShape_setFillColor(nbf[1][3].rect, color_J);
    }
    else if (type == 'S'){
        sfRectangleShape_setFillColor(nbf[1][1].rect, color_S);
        sfRectangleShape_setFillColor(nbf[1][2].rect, color_S);
        sfRectangleShape_setFillColor(nbf[2][2].rect, color_S);
        sfRectangleShape_setFillColor(nbf[2][3].rect, color_S);
    }
    else if (type == 'Z'){
        sfRectangleShape_setFillColor(nbf[2][1].rect, color_Z);
        sfRectangleShape_setFillColor(nbf[1][2].rect, color_Z);
        sfRectangleShape_setFillColor(nbf[2][2].rect, color_Z);
        sfRectangleShape_setFillColor(nbf[1][3].rect, color_Z);
    }
}

/*
Funkcja rysuj¹ca pole wyœwietlaj¹ca nastêpny klocek.
Parametry:
    *wind - wskaŸnik na okno gry
    nbf[4][4] - dwuwymiarowa tablica fieldStruct
Wartoœæ zwracana: brak.
*/
void nbf_draw(sfRenderWindow *wind, fieldStruct nbf[4][4]){
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            sfRenderWindow_drawRectangleShape(wind, nbf[i][j].rect, NULL);
}

/*
Funkcja dealokuj¹ca pamiêæ przeznaczon¹ na pole.
Parametry:
    nbf[4][4] - dwuwymiarowa tablica fieldStruct
Wartoœæ zwracana: brak.
*/
void nbf_destroy(fieldStruct nbf[4][4]){
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            sfRectangleShape_destroy(nbf[i][j].rect);
}
