#include "brick.h"

/*
Funkcja dodaj�ca klocek na g�r� planszy.
Parametry:
   *brick - wska�nik na brickStruct
Warto�� zwracana: brak.

Funkcja rezerwuje pami�� na struktur� oraz
okre�la jego parametry.
*/
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

/*
Funkcja zwalniaj�ca pami�� zajmowan� przez klocek.
Parametry:
    *brick - wska�nik na brickStruct
Warto�� zwracana: brak.
*/
void brick_destroy(brickStruct *brick){
    if (brick == NULL)
        return;
    for (int i = 0; i < 4 && brick->elements[i] != NULL; i++)
        sfRectangleShape_destroy(brick->elements[i]);
    free(brick);
}

/*
Funkcja przemieszczaj�ca klocek na osi horyzontalnej.
Parametry:
    field[totalWidth][totalHeight] - dwuwymiarowa tablica fieldStruct
    *brick - wska�nik na brickStruct
    delta - przesuni�cie
Warto�� zwracana:
    true, je�li uda si� przemie�ci� klocek,
w przeciwnym wypadku false

Funkcja przemieszca klocek, a nast�pnie sprawdza,
czy jego poycja jest dozwolona. Je�li nie,
przywraca jego oryginalne po�o�enie.
*/
bool brick_moveHorizontaly(fieldStruct field[totalWidth][totalHeight], brickStruct *brick, int delta){
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

/*
Funkcja sprawdzaj�ca, czy pola podane w parametrach s� zaj�te.
Parametry:
    fieldStruct[totalWidth][totalHeight] - dwuwymiarowa tablica fieldStruct
    vec[4] - tablica dwuwymiarowych wektor�w liczb ca�kowitych
Warto�� zwracana:
    true, je�li pozycja jest dozwolona,
false, je�li pozycja nie jest dozwolona.
*/
bool brick_isPositionValid(fieldStruct field[totalWidth][totalHeight], sfVector2i vec[4]){
    for (int i = 0; i < 4; i++)
        if (field[vec[i].x][vec[i].y].taken == true)
            return false;
    return true;
}

/*
Funkcja przesuwaj�ca klocek o jedno pole w d�.
Parametry:
    field[totalWidth][totalHeight] - dwuwymiarowa tablica fieldStruct
    *brick - wska�nik na brickStruct
Warto�� zwracana:
    true - uda�o si� przesun�� klocek
    false - nie uda�o si� przesun�� klocka

Zmiana pozycji klocka jest sygnalizowana poprzez
zmian� kolor�w kwadrat�w na planszy.
*/
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

/*
Funkcja umieszczaj�ca aktywny klocek na planszy.
Parametry:
    field[totalWidht][totalHeight] - dwuwymiarowa tablica fieldStruct
    *brick - wska�nik na fieldStruct
Warto�� zwracana: brak.

Funkcja informuje plansze o przybyciu nowego klocka
poprzez ustawienie zajmowanych przeze� kom�rek jako
"zaj�tych" i ustawienie kolor�w odpowiadajacych im
kwadrat�w na kolor ustawianego klocka. Po ustawieniu
pami�� zajmowana przez klocek jest zwalniana.
*/
void brick_place(fieldStruct field[totalWidth][totalHeight], brickStruct *brick){
    for (int i = 0; i < 4; i++){
        sfRectangleShape_setFillColor(field[brick->poses[i].x][brick->poses[i].y].rect, brick->col);
        field[brick->poses[i].x][brick->poses[i].y].taken = true;
    }
    brick_destroy(brick);
}

/*
Funkcja umo�lwiaj�ca rotacj� klocka w prawo.
Parametry:
    field[totalWidth][totalHeight] - dwuwymiarowa tablica fieldStruct
    *brick - wska�nik na brickStruct
Warto�� zwracana:
    true - je�li obr�t si� powi�d�,
w przeciwnym razie false.

Funkcja jest r�wnowa�na z wywo�aniem funkcji brick_rotate z parametrem shift = 0.
*/
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

/*
Funkcja umo�lwiaj�ca rotacj� klocka w prawo.
Parametry:
    field[totalWidth][totalHeight] - dwuwymiarowa
tablica fieldStruct
    *brick - wska�nik na brickStruct
    shift - przesuni�cie na osi X
Warto�� zwracana:
true - je�li obr�t si� powi�d�,
w przeciwnym razie false.

Funkcja przemieszcza klocek o podane przesuni�cie,
nast�pnie sprawdza, czy jego obr�t jest mo�liwy.
Jesli obr�t powiedzie si�, funkcja ko�czy si�,
je�li nie - przywraca klocek na jego pierwotn�
pozycj� i zwraca wrto�� false.
*/
bool brick_rotate2(fieldStruct field[totalWidth][totalHeight], brickStruct *brick, int shift){
    if (!brick_moveHorizontaly(field, brick, shift))
        return false;
    if (brick_rotate(field, brick))
        return true;
    else
        brick_moveHorizontaly(field, brick, -shift);
    return false;
}