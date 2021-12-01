#ifndef _MENU_H
#define _MENU_H

#include "SFML/Graphics.h"
#include "stanGry.h"

typedef struct Menu {
    sfTexture* tekstura;
    sfText* zegar;
    sfSprite* grafikaZegar;
    sfSprite* grafikaPauza;
    sfSprite* grafikaNowaGra;
    sfSprite* grafikaWyjscie;
} Menu;

sfBool tworzenieMenu(Menu* menu, sfVector2f odstepOdKrawedzi);
void ustawienieMenu(Menu* menu, sfVector2f odstepOdKrawedzi);
void ustawienieCzasu(Menu* menu, sfTime czas);
void wyswietlenieMenu(Menu* menu, sfRenderWindow* okno);
void klikniecieMenu(Menu* menu, sfRenderWindow* okno, StanGry* stan);

#endif