#ifndef _MAPA_H
#define _MAPA_H

#include "SFML/Graphics.h"
#include "stanGry.h"

typedef struct Pole {
    sfBool mina;
    sfBool flaga;
    sfBool odkryte;
    sfSprite* grafika;
} Pole;

typedef struct Mapa {
    Pole** pola;
    sfVector2i rozmiarPola;
    sfVector2i rozmiarMapy;
    sfTexture* tekstura;
    sfVector2f odstepOdKrawedzi;
} Mapa;

sfBool tworzenieMapy(Mapa* mapa, sfVector2f odstepOdKrawedzi);
void losowanieMapy(Mapa* mapa, sfVector2i rozmiarMapy, double prawdopodobienstwoMiny);
void wyswietlenieMapy(Mapa* mapa, sfRenderWindow* okno);
void klikniecieMapy(Mapa* mapa, sfRenderWindow* okno, sfBool prawy);
void ustawienieFlagi(Mapa* mapa, int x, int y);
void odkryciePola(Mapa* mapa, int x, int y);
void sprawdzenieMapy(Mapa* mapa, StanGry* stan);
void odkrycieMapy(Mapa* mapa, sfBool wygrana);
void usuniecieMapy(Mapa* mapa);

#endif