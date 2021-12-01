#ifndef _TLO_H
#define _TLO_H

#include "SFML/Graphics.h"
#include "stanGry.h"

typedef struct Tlo {
    sfTexture* gra;
    sfTexture* wygrana;
    sfTexture* przegrana;
    sfSprite* grafika;
} Tlo;

sfBool tworzenieTla(Tlo* tlo);
void zmianaTla(Tlo* tlo, StanGry* stan);
void zmianaRozmiaruTla(Tlo* tlo, sfVector2i rozmiar);
void wyswietlenieTla(Tlo* tlo, sfRenderWindow* okno);

#endif