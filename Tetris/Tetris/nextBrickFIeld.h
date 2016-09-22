#ifndef NBF_H
#define NBF_H
#include "define.h"

//pnk - pole nastêpnego klocka

//inicjalizacja pnk
void nbf_init(fieldStruct nbf[4][4]);

//ustawienie, który klocek ma byæ wyœwietlany
void nbf_setBrick(fieldStruct nbf[4][4], char type);

//rsowanie pnk
void nbf_draw(sfRenderWindow *wind, fieldStruct nbf[4][4]);

//zwolnienie pamiêci po pnk
void nbf_destroy(fieldStruct nbf[4][4]);

#endif