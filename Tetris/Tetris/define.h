//really cool file with definitions

#ifndef DEFINE_H
#define DEFINE_H
#define bool int    //bool, true, false - just as in C++
#define true 1
#define false 0
#define DEBUG false     //debug mode

//board size
//fWidth>9 && fHeight <12
//you can change it's values only in code
#define fWidth 10
#define fHeight 19
//reference for scaling
#define fSize 40

//http://www.sfml-dev.org/
#include <SFML\Graphics.h>
#include <SFML\Window.h>
#include <SFML\System.h>

#include <stdio.h>
#include <time.h>
#include <windows.h>


//window and board data
#define totalWidth fWidth+2
#define totalHeight fHeight +2 +2
#define windowWidth (unsigned int)(fSize*(totalWidth+3.5))
#define windowHeight fSize*(totalHeight-3)
#define startingStepRate 1000*1000 //brick's inital falling speed
#define minStepRate 200 * 1000  //brick's maximal falling speed

#define tetris_refreshRate 30   //fps
#define brickTypes "OTILJSZ"    //brick types
#define fileName "scores.dat"   //file with scores
#define fontName "cour.ttf"     //file with font

//color definitions
#define backgroundColor (sfColor){ 110, 110, 110 }
#define sfTransparent sfTransparent
#define color_O sfYellow
#define color_T sfMagenta
#define color_I sfCyan
#define color_L (sfColor){ 255, 132, 0, 255 }
#define color_J sfBlue
#define color_S sfGreen
#define color_Z sfRed

//structure for field on board
typedef struct{
    sfVector2i pos;
    bool taken;
    sfRectangleShape *rect;
}fieldStruct;

//structure for brick on the board
typedef struct{
    char type;
    sfVector2i poses[4];
    sfRectangleShape *elements[4];
    sfVector2i pivot;
    sfColor col;
}brickStruct;

#endif