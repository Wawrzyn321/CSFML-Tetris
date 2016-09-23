#include "brick.h"
#include "nextBrickFIeld.h"
#include "IO.h"
#include "gui.h"

/*
return codes:
    0 - no problems
    1 - font could not be loaded
    2 - invalid board size
    3 - scores file could not be loaded
*/


//name is kinda self-explanatory
char getRandomBrickType(const char* characters){
    unsigned int k = rand() % strlen(characters);
    return characters[k];
}

//hiding the console in Release mode
void hideConsole(){
    HWND wind = GetConsoleWindow();
    ShowWindow(wind, SW_HIDE);
}



int main(){

    printf("Loading...");

    //load the font
    sfFont *GUIFont;
    GUIFont = sfFont_createFromFile(fontName);
    if (!GUIFont){
        printf("could not load font %s!\n", fontName);
        system("pause");
        return 1;
    }

    //check the board size
    if (fWidth < 10 || fHeight<12){
        printf("invalid board size! (%dx%d)\n", fWidth, fHeight);
        system("pause");
        return 2;
    }

    //load scores from file
    LinkedList *scoresList = NULL;
    if (!IO_loadScores(&scoresList)){
        printf("could not load scores list! (file: %s)\n", fileName);
        system("pause");
        return 3;
    }

    //Release mode - hide console
#if DEBUG==0
    hideConsole();
#endif


    srand((size_t)time(NULL));
    int stepRate = startingStepRate; 

    //game window
    sfRenderWindow *window = sfRenderWindow_create((sfVideoMode){ windowWidth, windowHeight, 32 }, "Tetris (H - show highscores, P- pause, R - reset)", sfClose, NULL);

    //flags
    bool playin = true;
    bool pause = false;
    bool showingHighscores = false;

    //fixed step-loop variables
    int acc = 0;
    int st = 0;

    int points = 0; //points counter


    //locks for brick's transform
    bool upKeyReleased = true;
    bool downKeyReleased = true;
    bool rightKeyReleased = true;
    bool leftKeyReleased = true;

    //next brick symbol
    char nextBrickType = '\0';

    //GUI components (GUI.h)
    sfRectangleShape* GUIRects[2];
    GUI_initRects(GUIRects);

    sfText *GUITexts[5];
    GUI_initTexts(GUITexts, GUIFont);
    sfText *GUI_HS_texts[6];
    sfRectangleShape *GUI_HS_rec = NULL;
    GUI_initHS(GUI_HS_texts, &GUI_HS_rec, GUIFont);
    int HS_pos = 0;
    //0 - <0,4>, 1 - <1,5>, n - <n,n+4>...
    GUI_fillHS(GUI_HS_texts, scoresList, 0);

    //(board.h)
    fieldStruct field[totalWidth][totalHeight];
    board_init(field);

    //(brick.h and board.h)
    brickStruct *currentBrick = NULL;
    currentBrick = malloc(sizeof(brickStruct));
    currentBrick->type = getRandomBrickType(brickTypes);
    board_addBrick(currentBrick);

    //(nextBrickField.h)
    fieldStruct nextBrickFieldStruct[4][4];
    nextBrickType = getRandomBrickType(brickTypes);
    nbf_init(nextBrickFieldStruct);
    nbf_setBrick(nextBrickFieldStruct, nextBrickType);

    //game timer
    sfClock *timer = sfClock_create();
    sfClock_restart(timer);

    //main loop
    while (sfRenderWindow_isOpen(window)){
        //redraw the screen
        sfRenderWindow_clear(window, backgroundColor);
        GUI_drawRects(window, GUIRects);
        board_draw(window, field);
        GUI_drawTexts(window, GUITexts);
        nbf_draw(window, nextBrickFieldStruct);
        if(showingHighscores)
            GUI_drawHS(window, GUI_HS_texts, GUI_HS_rec);
        sfRenderWindow_display(window);

        //fixed loop
        acc += (long)sfClock_getElapsedTime(timer).microseconds;
        sfClock_restart(timer);
        st += acc;
        if (st >= tetris_refreshRate) {

            //cool smoothly blinking "Pause" text
            if (pause){
                double factor = ((sin(st / 5000.0 / 180.0*3.1415926535)) + 1) / 2.0; // <0,1>
                sfText_setColor(GUITexts[1], (sfColor){ 255, 255, 255, (sfUint8)(63 + 192 * factor) }); // <63,255>
            }
            if (st >= stepRate && !pause){
                if (playin){
                    //try to move brick down
                    if (!brick_moveDown(field, currentBrick)){
                        for (int i = 0; i < 4 && playin; i++)   //check if brick is on the board
                            if (currentBrick->poses[i].y == 2){
                                playin = false;
                                sfText_setColor(GUITexts[4], sfWhite);
                                IO_saveScore(points, &scoresList);
                                GUI_fillHS(GUI_HS_texts, scoresList, 0);
                            }
                        //updating board and GUI (board.h) i napisow (GUI.h)
                        //adding new brick
                        board_update(field, &stepRate, &points);
                        brick_place(field, currentBrick);
                        currentBrick = malloc(sizeof(brickStruct));
                        currentBrick->type = nextBrickType;
                        board_addBrick(currentBrick);
                        nextBrickType = getRandomBrickType(brickTypes);
                        nbf_setBrick(nextBrickFieldStruct, nextBrickType);
                        GUI_updateScore(GUITexts[3], points);
                    }
                }
                st %= stepRate;
            }
            acc %= tetris_refreshRate;
            acc = 0;
        }
        
        //event handling
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)){
            //window is closed - release memory
            if (event.type == sfEvtClosed){
                GUI_destroyRects(GUIRects);
                GUI_destroyTexts(GUITexts);
                GUI_destroyHS(GUI_HS_texts, GUI_HS_rec);
                sfFont_destroy(GUIFont);
                brick_destroy(currentBrick);
                sfClock_destroy(timer);
                board_destroy(field);
                nbf_destroy(nextBrickFieldStruct);
                LinkedList_destroy(&scoresList);
                sfRenderWindow_close(window);
            }
            //if window focus is lost, pause the game
            if (event.type == sfEvtLostFocus && !showingHighscores && playin)
                pause = true;
#if DEBUG
            if (event.type == sfEvtMouseButtonPressed && event.mouseButton.button == sfMouseRight){
                int mX = sfMouse_getPositionRenderWindow(window).x;
                int mY = sfMouse_getPositionRenderWindow(window).y;
                for (int i = 0; i < totalWidth; i++)
                    for (int j = 0; j < totalHeight; j++){
                        sfVector2f pos = sfRectangleShape_getPosition(field[i][j].rect);
                        if ((mX >= pos.x && mX <= pos.x + fSize) && (mY >= pos.y && mY <= pos.y + fSize)){
                            if (field[i][j].taken)
                                sfRectangleShape_setFillColor(field[i][j].rect, sfTransparent);
                            else
                                sfRectangleShape_setFillColor(field[i][j].rect, color_Z);
                            field[i][j].taken = !field[i][j].taken;
                        }
                    }
            }

            if (event.type == sfEvtMouseButtonPressed && event.mouseButton.button == sfMouseLeft){
                int mX = sfMouse_getPositionRenderWindow(window).x;
                int mY = sfMouse_getPositionRenderWindow(window).y;
                for (int i = 0; i < totalWidth; i++)
                    for (int j = 0; j < totalHeight; j++){
                        sfVector2f pos = sfRectangleShape_getPosition(field[i][j].rect);
                        if ((mX >= pos.x && mX <= pos.x + fSize) && (mY >= pos.y && mY <= pos.y + fSize)){
                            printf("%d\n", field[i][j].taken);
                        }
                    }
            }
#endif
            //make brick fall down faster by pressing down arrow
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyDown && !pause && playin){
                if (!brick_moveDown(field, currentBrick)){
                    for (int i = 0; i < 4 && playin; i++)
                        if (currentBrick->poses[i].y == 2){
                            playin = false;
                            sfText_setColor(GUITexts[4], sfWhite);
                            IO_saveScore(points, &scoresList);
                            GUI_fillHS(GUI_HS_texts, scoresList, 0);
                        }
                    board_update(field, &stepRate, &points);
                    brick_place(field, currentBrick);
                    currentBrick = malloc(sizeof(brickStruct));
                    currentBrick->type = nextBrickType;
                    board_addBrick(currentBrick);
                    board_update(field, &stepRate, &points);
                    nextBrickType = getRandomBrickType(brickTypes);
                    nbf_setBrick(nextBrickFieldStruct, nextBrickType);
                    GUI_updateScore(GUITexts[3], points);
                }
                downKeyReleased = false;
            }
            if (event.type == sfEvtKeyReleased && event.key.code == sfKeyDown && downKeyReleased)
                downKeyReleased = true;

            //immedately drop the brick
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyReturn && !pause && playin){
                while (brick_moveDown(field, currentBrick));
                for (int i = 0; i < 4 && playin; i++)
                    if (currentBrick->poses[i].y == 2){
                        playin = false;
                        sfText_setColor(GUITexts[4], sfWhite);
                        IO_saveScore(points, &scoresList);
                        GUI_fillHS(GUI_HS_texts, scoresList, 0);
                    }
                board_update(field, &stepRate, &points);
                brick_place(field, currentBrick);
                currentBrick = malloc(sizeof(brickStruct));
                currentBrick->type = nextBrickType;
                board_addBrick(currentBrick);
                board_update(field, &stepRate, &points);
                nextBrickType = getRandomBrickType(brickTypes);
                nbf_setBrick(nextBrickFieldStruct, nextBrickType);
                GUI_updateScore(GUITexts[3], points);
            }

            //moving brick on X axis
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyRight && playin && !pause){
                brick_moveHorizontal(field, currentBrick, 1);
                rightKeyReleased = false;
            }
            if (event.type == sfEvtKeyReleased && event.key.code == sfKeyRight && rightKeyReleased)
                rightKeyReleased = true;

            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyLeft && playin && !pause){
                brick_moveHorizontal(field, currentBrick, -1);
                leftKeyReleased = false;
            }
            if (event.type == sfEvtKeyReleased && event.key.code == sfKeyLeft && leftKeyReleased)
                leftKeyReleased = true;


            //rotating the brick
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyUp && currentBrick->type != 'O' && playin && !pause){
                if (!brick_rotate(field, currentBrick))
                    if (!brick_rotate2(field, currentBrick, -1))
                        brick_rotate2(field, currentBrick, 1);
            }

            //enabling/disabling pause
            if (event.type == sfEvtKeyPressed && (event.key.code == sfKeyP || (event.key.code == sfKeySpace && !showingHighscores)) && playin){
                if (pause){
                    sfText_setColor(GUITexts[1], sfTransparent);
                    st = 0;
                    if (showingHighscores){
                        sfText_setColor(GUITexts[1], sfTransparent);
                        showingHighscores = false;
                        sfRenderWindow_setTitle(window, "Tetris (H - show highscores, P- pause, R - reset)");
                    }
                }
                pause = !pause;
            }


            //reset game
            if (event.type == sfEvtKeyPressed && (event.key.code == sfKeyR || (!playin && event.key.code == sfKeySpace))){
                board_destroy(field);
                board_init(field);

                brick_destroy(currentBrick);
                currentBrick = malloc(sizeof(brickStruct));
                currentBrick->type = getRandomBrickType(brickTypes);
                board_addBrick(currentBrick);

                nextBrickType = getRandomBrickType(brickTypes);
                nbf_destroy(nextBrickFieldStruct);
                nbf_init(nextBrickFieldStruct);
                nbf_setBrick(nextBrickFieldStruct, nextBrickType);

                playin = true;
                pause = false;
                showingHighscores = false;
                stepRate = startingStepRate;
                acc = st = points = 0;

                sfText_setColor(GUITexts[1], sfTransparent);
                GUI_updateScore(GUITexts[3], points);
                sfText_setColor(GUITexts[4], sfTransparent);

                sfRenderWindow_setTitle(window, "Tetris (H - show highscores, P- pause, R - reset)");
            }

            //hide highscores
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape && showingHighscores){
                sfText_setColor(GUITexts[1], sfTransparent);
                pause = false;
                showingHighscores = false;
                sfRenderWindow_setTitle(window, "Tetris (H - show highscores, P- pause, R - reset)");
            }

            //show highscores
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyH){
                HS_pos = 0;
                if (!showingHighscores){
                    pause = true;
                    sfRenderWindow_setTitle(window, "Showing highscores - use arrow keys to navigate, C to clear the list");
                }
                else{
                    sfText_setColor(GUITexts[1], sfTransparent);
                    pause = false;
                    sfRenderWindow_setTitle(window, "Tetris (H - show highscores, P- pause, R - reset)");
                }
                showingHighscores = !showingHighscores;
            }

            //handle the HS list
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyDown && showingHighscores){
                if (HS_pos + 5 < LinkedList_getSize(scoresList)){
                    HS_pos++;
                    GUI_fillHS(GUI_HS_texts, scoresList, HS_pos);
                }
            }
            else if (event.type == sfEvtKeyPressed && event.key.code == sfKeyUp && showingHighscores){
                if (HS_pos > 0){
                    HS_pos--;
                    GUI_fillHS(GUI_HS_texts, scoresList, HS_pos);
                }
            }
            else if (event.type == sfEvtKeyPressed && event.key.code == sfKeyC && showingHighscores){
                HS_pos = 0;
                LinkedList_destroy(&scoresList);
                GUI_clearHS(GUI_HS_texts);
                IO_clear();
                GUI_fillHS(GUI_HS_texts, scoresList, 0);
            }


        }
    }
    //all's good - return 0
    return 0;
}