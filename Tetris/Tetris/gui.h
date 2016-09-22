#ifndef GUI_H
#define GUI_H
#include "define.h"
#include "LinkedList.h"

//Funkcja zwracająca dlugosc liczby
int numLen(int num);


//Inicjalizacja prostokątów
void GUI_initRects(sfRectangleShape *GUIRects[2]);

//Rysowanie prostokątów w oknie
void GUI_drawRects(sfRenderWindow *window, sfRectangleShape *GUIRects[2]);

//Dealokacja pamięci po prostokątach
void GUI_destroyRects(sfRectangleShape *GUIRects[2]);


//Inicjalizacja napisów gry
void GUI_initTexts(sfText *GUITexts[5], sfFont *GUIFont);

//Rysowanie napisów gry w oknie
void GUI_drawTexts(sfRenderWindow *window, sfText *GUITexts[5]);

//Aktualizacja napisu wyświetlającego wynik
void GUI_updateScore(sfText *GUIText, int points);

//Dealokaja pamięci po napisach
void GUI_destroyTexts(sfText *GUITexts[5]);

//Inicjalizacja komponentów wyników
void GUI_initHS(sfText *GUI_HS_Texts[6], sfRectangleShape **GUI_HS_rec, sfFont *GUIFont);

//Rysowanie komponentów wyników w oknie
void GUI_drawHS(sfRenderWindow *window, sfText *GUI_HS_Texts[6], sfRectangleShape *GUI_HS_rec);

//Przepisanie listy wynikow do GUI
void GUI_fillHS(sfText *GUI_HS_Texts[6], struct LinkedList *l, int pos);

//Wyczyszczenie listy wynikow
void GUI_clearHS(sfText *GUI_HS_Texts[6]);

//Dealokacja pamięci po komponentach wyników
void GUI_destroyHS(sfText *GUI_HS_Texts[6], sfRectangleShape *GUI_HS_rec);

#endif