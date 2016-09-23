#ifndef GUI_H
#define GUI_H
#include "define.h"
#include "LinkedList.h"

//get length of the  number
int numLen(int num);

//init rectangles
void GUI_initRects(sfRectangleShape *GUIRects[2]);

//drawing rectangles in window
void GUI_drawRects(sfRenderWindow *window, sfRectangleShape *GUIRects[2]);

//releasing memory occupied by rectangles
void GUI_destroyRects(sfRectangleShape *GUIRects[2]);


//init game texts
void GUI_initTexts(sfText *GUITexts[5], sfFont *GUIFont);

//draw game texts on screen
void GUI_drawTexts(sfRenderWindow *window, sfText *GUITexts[5]);

//updating score text
void GUI_updateScore(sfText *GUIText, int points);

//releasing memory occupied by texts
void GUI_destroyTexts(sfText *GUITexts[5]);


//init highscores rectangle and texts 
void GUI_initHS(sfText *GUI_HS_Texts[6], sfRectangleShape **GUI_HS_rec, sfFont *GUIFont);

//drawing highscores window on screen
void GUI_drawHS(sfRenderWindow *window, sfText *GUI_HS_Texts[6], sfRectangleShape *GUI_HS_rec);

//coping scores from list to GUI texts
void GUI_fillHS(sfText *GUI_HS_Texts[6], struct LinkedList *l, int pos);

//clearing the highscores
void GUI_clearHS(sfText *GUI_HS_Texts[6]);

//releasing memory occupied by highscores GUI
void GUI_destroyHS(sfText *GUI_HS_Texts[6], sfRectangleShape *GUI_HS_rec);

#endif