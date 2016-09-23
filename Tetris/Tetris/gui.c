#include "gui.h"

int numLen(int num){
    num = abs(num);
    int len = 1;
    while (num > 10){
        len++;
        num = num / 10;
    }
    return len;
}

void GUI_initRects(sfRectangleShape *GUIRects[2]){
    GUIRects[0] = sfRectangleShape_create();
    sfRectangleShape_setSize(GUIRects[0], (sfVector2f){ fSize * fWidth, fSize * (fHeight + 1) });
    sfRectangleShape_setPosition(GUIRects[0], (sfVector2f){ fSize / 2, -fSize / 2 });
    sfRectangleShape_setFillColor(GUIRects[0], sfBlack);

    GUIRects[1] = sfRectangleShape_create();
    sfRectangleShape_setSize(GUIRects[1], (sfVector2f){ fSize * 4, fSize * 4 });
    sfRectangleShape_setPosition(GUIRects[1], (sfVector2f){ fSize * (fWidth + 1), fSize * 4 });
    sfRectangleShape_setFillColor(GUIRects[1], sfBlack);
}

void GUI_drawRects(sfRenderWindow *window, sfRectangleShape *GUIRects[2]){
    sfRenderWindow_drawRectangleShape(window, GUIRects[0], NULL);
    sfRenderWindow_drawRectangleShape(window, GUIRects[1], NULL);
}

void GUI_destroyRects(sfRectangleShape *GUIRects[2]){
    sfRectangleShape_destroy(GUIRects[0]);
    sfRectangleShape_destroy(GUIRects[1]);
}

void GUI_initTexts(sfText *GUITexts[5], sfFont *GUIFont){
    for (int i = 0; i < 5; i++){
        GUITexts[i] = sfText_create();
        sfText_setFont(GUITexts[i], GUIFont);
    }
    sfText_setString(GUITexts[0], "Next\nbrick");
    sfText_setCharacterSize(GUITexts[0], (unsigned int)(fSize * 0.8));
    sfText_setPosition(GUITexts[0], (sfVector2f){ fSize*(fWidth + 1.75), fSize * 2 });

    sfText_setString(GUITexts[1], "Paused");
    sfText_setStyle(GUITexts[1], sfTextBold);
    sfText_setCharacterSize(GUITexts[1], (unsigned int)(fSize *1.5));
    sfText_setOrigin(GUITexts[1], (sfVector2f){ sfText_getLocalBounds(GUITexts[1]).width / 2, fSize });
    sfText_setPosition(GUITexts[1], (sfVector2f){ (float)(fSize * fWidth / 2.0), (float)(fSize * (fHeight + 1) / 2.0) });
    sfText_setColor(GUITexts[1], sfTransparent);

    sfText_setString(GUITexts[2], "Points:");
    sfText_setCharacterSize(GUITexts[2], (unsigned int)(fSize *0.75));
    sfText_setPosition(GUITexts[2], (sfVector2f){ fSize*(fWidth + 1.5), fSize * 10 });
    sfText_setCharacterSize(GUITexts[3], (unsigned int)(fSize *1.5));
    sfText_setString(GUITexts[3], "0");
    sfText_setPosition(GUITexts[3], (sfVector2f){ fSize*(fWidth + 3) - sfText_getLocalBounds(GUITexts[3]).width / 2.0f, fSize * 11 });

    sfText_setString(GUITexts[4], "You lost!");
    sfText_setCharacterSize(GUITexts[4], (unsigned int)(fSize *1.5));
    sfText_setPosition(GUITexts[4], (sfVector2f){ ((float)fSize*fWidth - sfText_getLocalBounds(GUITexts[4]).width) / 2, (float)windowHeight / 2 - sfText_getCharacterSize(GUITexts[4]) });
    sfText_setColor(GUITexts[4], sfTransparent);
}

void GUI_drawTexts(sfRenderWindow *window, sfText *GUITexts[5]){
    for (int i = 0; i < 5; i++)
        sfRenderWindow_drawText(window, GUITexts[i], NULL);
}

void GUI_updateScore(sfText *GUIText, int points){
    char score[10];
    sprintf(score, "%d", points); //convert score to string
    sfText_setString(GUIText, score);
    sfText_setPosition(GUIText, (sfVector2f){ fSize*(fWidth + 3) - sfText_getLocalBounds(GUIText).width / 2.0f, fSize * 11 });
}

void GUI_destroyTexts(sfText *GUITexts[5]){
    for (int i = 0; i < 5; i++)
        sfText_destroy(GUITexts[i]);
}

void GUI_initHS(sfText *GUI_HS_Texts[6], sfRectangleShape **GUI_HS_rec, sfFont *GUIFont){
    *GUI_HS_rec = sfRectangleShape_create();
    sfRectangleShape_setSize(*GUI_HS_rec, (sfVector2f){ windowWidth / 2, windowHeight / 2 });
    sfRectangleShape_setOrigin(*GUI_HS_rec, (sfVector2f){ sfRectangleShape_getSize(*GUI_HS_rec).x / 2, sfRectangleShape_getSize(*GUI_HS_rec).y / 2 });
    sfRectangleShape_setPosition(*GUI_HS_rec, (sfVector2f){ windowWidth / 2, windowHeight / 2 });
    sfRectangleShape_setFillColor(*GUI_HS_rec, sfBlack);
    sfRectangleShape_setOutlineColor(*GUI_HS_rec, sfWhite);
    sfRectangleShape_setOutlineThickness(*GUI_HS_rec, 4);

    for (int i = 0; i < 6; i++){
        GUI_HS_Texts[i] = sfText_create();
        sfText_setFont(GUI_HS_Texts[i], GUIFont);
    }

    sfText_setString(GUI_HS_Texts[0], "Highscores");
    sfText_setStyle(GUI_HS_Texts[0], sfTextBold);
    sfText_setCharacterSize(GUI_HS_Texts[0], fSize*9/8);
    sfText_setOrigin(GUI_HS_Texts[0], (sfVector2f){ sfText_getLocalBounds(GUI_HS_Texts[0]).width / 2, sfText_getLocalBounds(GUI_HS_Texts[0]).height / 2 }); sfText_setPosition(GUI_HS_Texts[0], (sfVector2f){ windowWidth / 2, 100 });
    sfText_setPosition(GUI_HS_Texts[0], (sfVector2f){ (float)windowWidth / 2, sfRectangleShape_getPosition(*GUI_HS_rec).y - (float)(fSize *3.75) });

    for (int i = 1; i < 6; i++){ //operujemy na tekstach o indeksach 1..5
        //wymagamy 11 znakow na rekord
        char score[11];
        sprintf(score, "%d", i);
        sfText_setString(GUI_HS_Texts[i], strcat(score, ". .......0"));
        sfText_setCharacterSize(GUI_HS_Texts[i], fSize);
        sfText_setOrigin(GUI_HS_Texts[i], (sfVector2f){ sfText_getLocalBounds(GUI_HS_Texts[i]).width / 2, sfText_getLocalBounds(GUI_HS_Texts[i]).height / 2 });
        sfText_setPosition(GUI_HS_Texts[i], (sfVector2f){ (float)windowWidth / 2, sfRectangleShape_getPosition(*GUI_HS_rec).y / 2 + fSize * 2 + (float)(fSize*1.25) * i });
    }
}

void GUI_drawHS(sfRenderWindow *window, sfText *GUI_HS_Texts[6], sfRectangleShape *GUI_HS_rec){
    sfRenderWindow_drawRectangleShape(window, GUI_HS_rec, NULL);
    for (int i = 0; i < 6; i++)
        sfRenderWindow_drawText(window, GUI_HS_Texts[i], NULL);
}

void GUI_fillHS(sfText *GUI_HS_Texts[6], LinkedList *l, int pos){
    int LLSize = LinkedList_getSize(l);
    if (LLSize > 5)
        LLSize = 5;
    for (int i = 0; i < pos; i++)
        l = l->pNext;
    for (int i = 1; i <= LLSize; i++){
        char res[11];
        sprintf(res, "%d", i+pos);
        sfText_setString(GUI_HS_Texts[i], strcat(res, ". .......0"));

        char num[8];
        sprintf(num, "%d", l->val);

        memcpy(res + 11 -  numLen(l->val), num, sizeof(char)*strlen(num));

        sfText_setString(GUI_HS_Texts[i], res);
        l = l->pNext;
    }
}

void GUI_clearHS(sfText *GUI_HS_Texts[6]){
    for (int i = 1; i <= 5; i++){
        char res[11];  //we need 11 char for highscore
        sprintf(res, "%d", i); //convert i to text
        sfText_setString(GUI_HS_Texts[i], strcat(res, ". .......0"));

        sfText_setString(GUI_HS_Texts[i], res);
    }
}

void GUI_destroyHS(sfText *GUI_HS_Texts[6], sfRectangleShape *GUI_HS_rec){
    sfRectangleShape_destroy(GUI_HS_rec);
    for (int i = 0; i < 6; i++)
        sfText_destroy(GUI_HS_Texts[i]);
}