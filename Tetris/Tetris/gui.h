#ifndef GUI_H
#define GUI_H
#include "define.h"
#include "LinkedList.h"

//Funkcja zwracaj¹ca dlugosc liczby
int numLen(int num);


//Inicjalizacja prostok¹tów
void GUI_initRects(sfRectangleShape *GUIRects[2]);

//Rysowanie prostok¹tów w oknie
void GUI_drawRects(sfRenderWindow *window, sfRectangleShape *GUIRects[2]);

//Dealokacja pamiêci po prostok¹tach
void GUI_destroyRects(sfRectangleShape *GUIRects[2]);


//Inicjalizacja napisów gry
void GUI_initTexts(sfText *GUITexts[5], sfFont *GUIFont);

//Rysowanie napisów gry w oknie
void GUI_drawTexts(sfRenderWindow *window, sfText *GUITexts[5]);

//Aktualizacja napisu wyœwietlaj¹cego wynik
void GUI_updateScore(sfText *GUIText, int points);

//Dealokaja pamiêci po napisach
void GUI_destroyTexts(sfText *GUITexts[5]);

//Inicjalizacja komponentów wyników
void GUI_initHS(sfText *GUI_HS_Texts[6], sfRectangleShape **GUI_HS_rec, sfFont *GUIFont);

//Rysowanie komponentów wyników w oknie
void GUI_drawHS(sfRenderWindow *window, sfText *GUI_HS_Texts[6], sfRectangleShape *GUI_HS_rec);

//Przepisanie listy wynikow do GUI
void GUI_fillHS(sfText *GUI_HS_Texts[6], struct LinkedList *l, int pos);

//Wyczyszczenie listy wynikow
void GUI_clearHS(sfText *GUI_HS_Texts[6]);

//Dealokacja pamiêci po komponentach wyników
void GUI_destroyHS(sfText *GUI_HS_Texts[6], sfRectangleShape *GUI_HS_rec);

#endif