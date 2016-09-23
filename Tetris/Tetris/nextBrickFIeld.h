#ifndef NBF_H
#define NBF_H
#include "define.h"

//init nbf
void nbf_init(fieldStruct nbf[4][4]);

//set next brick
void nbf_setBrick(fieldStruct nbf[4][4], char type);

//drawin nbf on window
void nbf_draw(sfRenderWindow *wind, fieldStruct nbf[4][4]);

//releasing memory
void nbf_destroy(fieldStruct nbf[4][4]);

#endif