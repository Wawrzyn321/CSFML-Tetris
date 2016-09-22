#ifndef GUI_H
#define GUI_H
#include "define.h"
#include "LinkedList.h"

//Funkcja zwracaj�ca dlugosc liczby
int numLen(int num);


//Inicjalizacja prostok�t�w
void GUI_initRects(sfRectangleShape *GUIRects[2]);

//Rysowanie prostok�t�w w oknie
void GUI_drawRects(sfRenderWindow *window, sfRectangleShape *GUIRects[2]);

//Dealokacja pami�ci po prostok�tach
void GUI_destroyRects(sfRectangleShape *GUIRects[2]);


//Inicjalizacja napis�w gry
void GUI_initTexts(sfText *GUITexts[5], sfFont *GUIFont);

//Rysowanie napis�w gry w oknie
void GUI_drawTexts(sfRenderWindow *window, sfText *GUITexts[5]);

//Aktualizacja napisu wy�wietlaj�cego wynik
void GUI_updateScore(sfText *GUIText, int points);

//Dealokaja pami�ci po napisach
void GUI_destroyTexts(sfText *GUITexts[5]);

//Inicjalizacja komponent�w wynik�w
void GUI_initHS(sfText *GUI_HS_Texts[6], sfRectangleShape **GUI_HS_rec, sfFont *GUIFont);

//Rysowanie komponent�w wynik�w w oknie
void GUI_drawHS(sfRenderWindow *window, sfText *GUI_HS_Texts[6], sfRectangleShape *GUI_HS_rec);

//Przepisanie listy wynikow do GUI
void GUI_fillHS(sfText *GUI_HS_Texts[6], struct LinkedList *l, int pos);

//Wyczyszczenie listy wynikow
void GUI_clearHS(sfText *GUI_HS_Texts[6]);

//Dealokacja pami�ci po komponentach wynik�w
void GUI_destroyHS(sfText *GUI_HS_Texts[6], sfRectangleShape *GUI_HS_rec);

#endif