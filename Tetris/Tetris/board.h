#ifndef BOARD_H
#define BOARD_H
#include "define.h"

//wyczyszczenie wiersza
void board_clearRow(fieldStruct field[totalWidth][totalHeight], int j);

//sprawdzenie, czy wiersz jest zape³niony
bool board_isRowFull(fieldStruct field[totalWidth][totalHeight], int j);

//inicjalizacja planszy
void board_init(fieldStruct field[totalWidth][totalHeight]);

//aktualizacja planszy
void board_update(fieldStruct field[totalWidth][totalHeight], int *stepRate, int *points);

//rysowanie planszy na ekranie
void board_draw(sfRenderWindow *wind, fieldStruct field[totalWidth][totalHeight]);

//dealokacja pamiêci zarezerwowanej na planszê
void board_destroy(fieldStruct field[totalWidth][totalHeight]);

#endif