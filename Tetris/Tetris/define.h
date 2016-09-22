//naprawde poreczny pliczek ze stalymi

#ifndef DEFINE_H
#define DEFINE_H
#define bool int    //bool, true, false - jak w C++
#define true 1
#define false 0
#define DEBUG false     //tryb debugowania

//wymiary planszy:
//ich zmiana jest mo¿liwa, ale tylko poprzez zmianê kodu.
//fWidth powinno byæ wiêksze od 9, a fHeight wiêksze od 12.
#define fWidth 10
#define fHeight 19
//punkt odniesienia do skalowania interfejsu
#define fSize 40

//http://www.sfml-dev.org/
#include <SFML\Graphics.h>
#include <SFML\Window.h>
#include <SFML\System.h>

#include <stdio.h>
#include <time.h>
#include <windows.h>


//dane o oknie i planszy
#define totalWidth fWidth+2
#define totalHeight fHeight +2 +2
#define windowWidth (unsigned int)(fSize*(totalWidth+3.5))
#define windowHeight fSize*(totalHeight-3)
#define startingStepRate 1000*1000 //pocz¹tkowa prêdkoœæ opadania klocka
#define minStepRate 200 * 1000  //minimalna predkosc opadania klocka

#define tetris_refreshRate 30   //liczba klatek na sekunde
#define brickTypes "OTILJSZ"    //dozwolone typy klockow
#define fileName "scores.dat"   //plik z wynikami
#define fontName "cour.ttf"     //plik z czcionka

//definicje kolorow
#define backgroundColor (sfColor){ 110, 110, 110 }
#define sfTransparent sfTransparent
#define color_O sfYellow
#define color_T sfMagenta
#define color_I sfCyan
#define color_L (sfColor){ 255, 132, 0, 255 }
#define color_J sfBlue
#define color_S sfGreen
#define color_Z sfRed

//struktura reprezentujaca pojedynczy blok na planszy
typedef struct{
    sfVector2i pos;             //pozycja na planszy
    bool taken;                 //czy pole jest zajête?
    sfRectangleShape *rect;     //wskaŸnik na prostok¹t
}fieldStruct;

//struktura reprezentuaca klocek
typedef struct{
    char type;                      //typ klocka
    sfVector2i poses[4];            //pozycje poszczególnych elementów klocka
    sfRectangleShape *elements[4];  //wskaŸniki prostok¹ty, symbolizuj¹ce klocek
    sfVector2i pivot;               //œrodek ciê¿koœci klocka
    sfColor col;                    //kolor klocka
}brickStruct;

#endif