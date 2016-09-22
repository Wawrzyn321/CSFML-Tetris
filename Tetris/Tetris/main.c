#include "brick.h"
#include "nextBrickFIeld.h"
#include "IO.h"
#include "gui.h"


/*
jak z diagramem klas
"Wykorzystanie zmiennych lokalnych statycznych "
ewentualna poprawka
"kilka plików po³¹czonych w projekcie (nie przez #include!), "
jak szczegó³owy ma byæ opis plików
*/

/*
Funkcja zwracajaca losowy typ klocka.
Parametry:
    characters - ³añcuch znaków, z³o¿ony z liter
odpowiadaj¹cych typom klocków.
Wartosc zwracana - znak z losowej pozycji ciagu
podanego w argumencie.
*/
char getRandomBrickType(const char* characters){
    unsigned int k = rand() % strlen(characters);
    return characters[k];
}

/*
Funkcja ukrywajaca konsolê.
Parametry, wartoœæ zwracana - brak.
*/
void hideConsole(){
    HWND wind = GetConsoleWindow();
    ShowWindow(wind, SW_HIDE);
}

int main(){
    //stworzenie czcionki i wczytanie jej z pliku
    //jeœli nie udalo sie otworzyc wybranej czcionki
    //program zasygnalizuje to komunikatem i zakonczy
    //prace, zwracajac wartosc 1
    sfFont *GUIFont;
    GUIFont = sfFont_createFromFile(fontName);
    if (!GUIFont){
        printf("could not load font %s!\n", fontName);
        system("pause");
        return 1;
    }

    //jesli wymiary planszy sa z niewlasciwego zakresu
    //gra moze nie dzialac wlasciwie. W tym wypadku
    //program wyswietla komunikat, zwraca wartosc 2
    //i konczy prace
    if (fWidth < 10 || fHeight<12){
        printf("invalid field size! (%dx%d)\n", fWidth, fHeight);
        system("pause");
        return 2;
    }

    //utworzenie listy wynikow, zaladowanie jej z pliku
    //jestli nie uda sie otworzyc plik to program wyswietla stosowny
    //komunikat i konczy prace zwracajac wartosc 3
    LinkedList *scoresList = NULL;
    if (!IO_loadScores(&scoresList)){
        printf("could not load scores list! (file: %s)\n", fileName);
        system("pause");
        return 3;
    }

    //jestli jestesmy w trybie Release, okno konsoli
    //jest niepotrzebne
#if DEBUG==0
    hideConsole();
#endif


    srand((size_t)time(NULL));
    
    //czas, co jaki aktywny klocek bedzie poruszal sie w dol
    //pozostaje w zakresie <200, 1000> ms
    //(lub <200 000, 1000 000> qs
    int stepRate = startingStepRate; 

    //okno gry
    sfRenderWindow *window = sfRenderWindow_create((sfVideoMode){ windowWidth, windowHeight, 32 }, "Tetris (H - show highscores, P- pause, R - reset)", sfClose, NULL);

    bool playin = true;                //czy gra trwa nadal?
    bool pause = false;                //czy pauza jest aktywna?
    bool showingHighscores = false;    //czy wyswietlanie wynikow jest wlaczone?

    //zmienne uzywane w petli stalokrokowej
    int acc = 0;
    int st = 0;

    int points = 0; //licznik punktow


    //zmienne umozliwiajace plynne przesuwanie klockami
    //oraz obracanie ich
    bool upKeyReleased = true;
    bool downKeyReleased = true;
    bool rightKeyReleased = true;
    bool leftKeyReleased = true;

    //symbol kolejnego klocka
    char nextBrickType = '\0';

    //komponenty interfejstu (plik GUI.h)
    sfRectangleShape* GUIRects[2];
    GUI_initRects(GUIRects);

    //(plik GUI.h)
    sfText *GUITexts[5];
    GUI_initTexts(GUITexts, GUIFont);
    sfText *GUI_HS_texts[6];
    sfRectangleShape *GUI_HS_rec = NULL;
    GUI_initHS(GUI_HS_texts, &GUI_HS_rec, GUIFont);
    int HS_pos = 0;//pozycja w wyœwietlaniu wyników
    //0 - <0,4>, 1 - <1,5>, n - <n,n+4>...
    GUI_fillHS(GUI_HS_texts, scoresList, 0);

    //stworzenie i inicjalizacja siatki gry (plik board.h)
    fieldStruct field[totalWidth][totalHeight];
    board_init(field);

    //stworzenie nowego klocka, dodanie go jako aktywnego na plansze (pliki brick.h oraz board.h)
    brickStruct *currentBrick = NULL;
    currentBrick = malloc(sizeof(brickStruct));
    currentBrick->type = getRandomBrickType(brickTypes);
    board_addBrick(currentBrick);

    //inicjalizacja pola pokazujacego nastepny typ klocka (plik nextBrickField.h)
    fieldStruct nextBrickFieldStruct[4][4];
    nextBrickType = getRandomBrickType(brickTypes);
    nbf_init(nextBrickFieldStruct);
    nbf_setBrick(nextBrickFieldStruct, nextBrickType);

    //zegar gry
    sfClock *timer = sfClock_create();
    sfClock_restart(timer);
    

    //petla glowna
    while (sfRenderWindow_isOpen(window)){
        //przerysowywanie ekranu
        sfRenderWindow_clear(window, backgroundColor);
        GUI_drawRects(window, GUIRects);
        board_draw(window, field);
        GUI_drawTexts(window, GUITexts);
        nbf_draw(window, nextBrickFieldStruct);
        if(showingHighscores)
            GUI_drawHS(window, GUI_HS_texts, GUI_HS_rec);
        sfRenderWindow_display(window);

        //obsluga petli stalokrokowej
        acc += (long)sfClock_getElapsedTime(timer).microseconds;
        sfClock_restart(timer);
        st += acc;
        if (st >= tetris_refreshRate) {

            //ekran pauzy jest wyposazony w migajacy tekst "Paused"
            if (pause){
                double factor = ((sin(st / 5000.0 / 180.0*3.1415926535)) + 1) / 2.0; //wartosci z przedzialu <0,1>
                sfText_setColor(GUITexts[1], (sfColor){ 255, 255, 255, (sfUint8)(63 + 192 * factor) }); //<63,255>
            }
            if (st >= stepRate && !pause){
                if (playin){
                    //probujemy przemiescic klocek o jedno pole w dol
                    if (!brick_moveDown(field, currentBrick)){
                        for (int i = 0; i < 4 && playin; i++)   //sprawdzenie, czy klocek nie wychodzi poza planszê
                            if (currentBrick->poses[i].y == 2){
                                playin = false;
                                sfText_setColor(GUITexts[4], sfWhite);
                                IO_saveScore(points, &scoresList);
                                GUI_fillHS(GUI_HS_texts, scoresList, 0);
                            }
                        //aktualizacja pola (board.h) i napisow (GUI.h)
                        //dodanie nowego klocka (brick.h)
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
        
        //obsluga zdarzen
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)){
            //okno zostalo zamkniete - zwalniamy zarezerwowana pamiec
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
            //jesli uzytkownik przelaczy widok na inne okno, automatycznie wlacza sie pauza
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
            //przyspieszenie spuszczania klocka w dol i aktualizacja planszy (strzalka w dol)
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyDown && !pause && playin){
                if (!brick_moveDown(field, currentBrick)){
                    for (int i = 0; i < 4 && playin; i++)   //sprawdzenie, czy klocek nie wychodzi poza planszê
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

            //szybkie spuszczenie klocka na pierwsza mozliwo pozycje pod nim    (enter)
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyReturn && !pause && playin){
                while (brick_moveDown(field, currentBrick));
                for (int i = 0; i < 4 && playin; i++)   //sprawdzenie, czy klocek nie wychodzi poza planszê
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

            //obsluga przesuwania aktywnego klocka w prawo i lewo na zyczenie gracza (strzalki w prawo i w lewo)
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyRight && playin && !pause){
                brick_moveHorizontaly(field, currentBrick, 1);
                rightKeyReleased = false;
            }
            if (event.type == sfEvtKeyReleased && event.key.code == sfKeyRight && rightKeyReleased)
                rightKeyReleased = true;

            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyLeft && playin && !pause){
                brick_moveHorizontaly(field, currentBrick, -1);
                leftKeyReleased = false;
            }
            if (event.type == sfEvtKeyReleased && event.key.code == sfKeyLeft && leftKeyReleased)
                leftKeyReleased = true;


            //obrot klocka (strzalka w gore)
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyUp && currentBrick->type != 'O' && playin && !pause){
                if (!brick_rotate(field, currentBrick))
                    if (!brick_rotate2(field, currentBrick, -1))
                        brick_rotate2(field, currentBrick, 1);
            }

            //wlaczenie/wylaczenie pauzy   ('P' lub spacja)
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


            //reset gry ('R' lub dodatkowo spacja w razie przegranej)
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

            //wyjscie z trybu wyswietlania wynikow (escape)
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape && showingHighscores){
                sfText_setColor(GUITexts[1], sfTransparent);
                pause = false;
                showingHighscores = false;
                sfRenderWindow_setTitle(window, "Tetris (H - show highscores, P- pause, R - reset)");
            }

            //wyswietlenie wynikow (H)
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

            //obsluga wyswietlanej listy wyników
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyDown && showingHighscores){ //przesuwanie w dó³ (strza³ka w dó³)
                if (HS_pos + 5 < LinkedList_getSize(scoresList)){
                    HS_pos++;
                    GUI_fillHS(GUI_HS_texts, scoresList, HS_pos);
                }
            }
            else if (event.type == sfEvtKeyPressed && event.key.code == sfKeyUp && showingHighscores){ //przesuwanie w górê (strza³ka w górê)
                if (HS_pos > 0){
                    HS_pos--;
                    GUI_fillHS(GUI_HS_texts, scoresList, HS_pos);
                }
            }
            else if (event.type == sfEvtKeyPressed && event.key.code == sfKeyC && showingHighscores){ //czyszczenie (C)
                HS_pos = 0;
                LinkedList_destroy(&scoresList);
                GUI_clearHS(GUI_HS_texts);
                IO_clear();
                GUI_fillHS(GUI_HS_texts, scoresList, 0);
            }


        }
    }
    //wszystko poszlo zgodnie z planem - zwracamy 0
    return 0;
}