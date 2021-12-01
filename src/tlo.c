#include "tlo.h"

sfBool tworzenieTla(Tlo* tlo) {
    (*tlo).gra = sfTexture_createFromFile("./grafika/tloGra.png", NULL);
    if ((*tlo).gra == NULL) {
        return sfFalse;
    }
    sfTexture_setRepeated((*tlo).gra, sfTrue);
    (*tlo).wygrana = sfTexture_createFromFile("./grafika/tloWygrana.png", NULL);
    if ((*tlo).wygrana == NULL) {
        return sfFalse;
    }
    sfTexture_setRepeated((*tlo).wygrana, sfTrue);
    (*tlo).przegrana = sfTexture_createFromFile("./grafika/tloPrzegrana.png", NULL);
    if ((*tlo).przegrana == NULL) {
        return sfFalse;
    }
    sfTexture_setRepeated((*tlo).przegrana, sfTrue);
    (*tlo).grafika = sfSprite_create();
    sfSprite_setTextureRect((*tlo).grafika, (sfIntRect) { 0, 0, 1200, 600 });
    return sfTrue;
}

void zmianaTla(Tlo* tlo, StanGry* stan) {
    if ((*stan) == Przegrana) {
        sfSprite_setTexture((*tlo).grafika, (*tlo).przegrana, sfFalse);
    }
    else if ((*stan) == Wygrana) {
        sfSprite_setTexture((*tlo).grafika, (*tlo).wygrana, sfFalse);
    }
    else {
        sfSprite_setTexture((*tlo).grafika, (*tlo).gra, sfFalse);
    }
}

void zmianaRozmiaruTla(Tlo* tlo, sfVector2i rozmiar) {
    sfSprite_setTextureRect((*tlo).grafika, (sfIntRect) { 0, 0, rozmiar.x, rozmiar.y });
}

void wyswietlenieTla(Tlo* tlo, sfRenderWindow* okno) {
    sfRenderWindow_drawSprite(okno, (*tlo).grafika, NULL);
}
