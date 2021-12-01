#include "mapa.h"
#include <stdlib.h>
#include <stdio.h>

sfBool tworzenieMapy(Mapa* mapa, sfVector2f odstepOdKrawedzi) {
    sfTexture* tekstura = sfTexture_createFromFile("./grafika/pole.png", NULL);
    if (tekstura == NULL) {
        return sfFalse;
    }
    sfVector2i rozmiarPola = (sfVector2i) { 24, 24 };
    (*mapa).tekstura = tekstura;
    (*mapa).rozmiarPola = rozmiarPola;
    (*mapa).odstepOdKrawedzi = odstepOdKrawedzi;
    (*mapa).rozmiarMapy = (sfVector2i) { 0, 0 };
    return sfTrue;
}

void losowanieMapy(Mapa* mapa, sfVector2i rozmiarMapy, double prawdopodobienstwoMiny) {
    (*mapa).rozmiarMapy = rozmiarMapy;
    (*mapa).pola = (Pole**)malloc(sizeof(Pole*) * rozmiarMapy.y);
    for (int i = 0; i < rozmiarMapy.y; i++) {
        (*mapa).pola[i] = (Pole*)malloc(sizeof(Pole) * rozmiarMapy.x);
        for (int j = 0; j < rozmiarMapy.x; j ++) {
            (*mapa).pola[i][j].mina = ((double)rand() / RAND_MAX <= prawdopodobienstwoMiny) ? sfTrue : sfFalse;
            (*mapa).pola[i][j].flaga = sfFalse;
            (*mapa).pola[i][j].odkryte = sfFalse;
            (*mapa).pola[i][j].grafika = sfSprite_create();
            sfSprite_setTexture((*mapa).pola[i][j].grafika, (*mapa).tekstura, sfFalse);
            sfSprite_setTextureRect((*mapa).pola[i][j].grafika, (sfIntRect) { 0, 0, (*mapa).rozmiarPola.x, (*mapa).rozmiarPola.y });
            sfSprite_setPosition((*mapa).pola[i][j].grafika, (sfVector2f) { (*mapa).rozmiarPola.x * j + (*mapa).odstepOdKrawedzi.x, (*mapa).rozmiarPola.y * i + (*mapa).odstepOdKrawedzi.y});
        }
    }
}

void wyswietlenieMapy(Mapa* mapa, sfRenderWindow* okno) {
    for (int i = 0; i < (*mapa).rozmiarMapy.y; i++) {
        for (int j = 0; j < (*mapa).rozmiarMapy.x; j++) {
            sfRenderWindow_drawSprite(okno, (*mapa).pola[i][j].grafika, NULL);
        }
    }
}

void klikniecieMapy(Mapa* mapa, sfRenderWindow* okno, sfBool prawy) {
    sfFloatRect polozennie;
    for (int i = 0; i < (*mapa).rozmiarMapy.y; i++) {
        for (int j = 0; j < (*mapa).rozmiarMapy.x; j++) {
            polozennie = sfSprite_getGlobalBounds((*mapa).pola[i][j].grafika);
            if (sfFloatRect_contains(&polozennie, sfMouse_getPositionRenderWindow(okno).x, sfMouse_getPositionRenderWindow(okno).y)) {
                if (prawy) { 
                    ustawienieFlagi(mapa, j, i);
                }
                else {
                    odkryciePola(mapa, j, i);
                }
            }
        }
    }
}

void ustawienieFlagi(Mapa* mapa, int x, int y) {
    if (x < 0 || y < 0 || x >= (*mapa).rozmiarMapy.x || y > (*mapa).rozmiarMapy.y) {
        return;
    }
    if ((*mapa).pola[y][x].odkryte) {
        return;
    }
    if ((*mapa).pola[y][x].flaga) {
        (*mapa).pola[y][x].flaga = sfFalse;
        sfSprite_setTextureRect((*mapa).pola[y][x].grafika, (sfIntRect) { 0, 0, (*mapa).rozmiarPola.x, (*mapa).rozmiarPola.x });
    }
    else {
        (*mapa).pola[y][x].flaga = sfTrue;
        sfSprite_setTextureRect((*mapa).pola[y][x].grafika, (sfIntRect) { 24, 0, (*mapa).rozmiarPola.x, (*mapa).rozmiarPola.x });
    }
}

void odkryciePola(Mapa* mapa, int x, int y) {
    if (x < 0 || y < 0 || x >= (*mapa).rozmiarMapy.x || y > (*mapa).rozmiarMapy.y) {
        return;
    }
    if ((*mapa).pola[y][x].odkryte || (*mapa).pola[y][x].flaga) {
        return;
    }
    (*mapa).pola[y][x].odkryte = sfTrue;
    if ((*mapa).pola[y][x].mina) {
        sfSprite_setTextureRect((*mapa).pola[y][x].grafika, (sfIntRect) { 120, 0, (*mapa).rozmiarPola.x, (*mapa).rozmiarPola.y });
        return;
    }
    int sasiednieMiny = 0;
    for (int i = y - 1; i <= y + 1; i++) {
        for (int j = x - 1; j <= x + 1; j++) {
            if (i >= 0 && j >= 0 && i < (*mapa).rozmiarMapy.y && j < (*mapa).rozmiarMapy.x) {
                if ((*mapa).pola[i][j].mina) {
                    sasiednieMiny++;
                }
            }
        }
    }
    sfSprite_setTextureRect((*mapa).pola[y][x].grafika, (sfIntRect) { (*mapa).rozmiarPola.x * (sasiednieMiny + 6), 0, (*mapa).rozmiarPola.x, (*mapa).rozmiarPola.y });
    if (sasiednieMiny == 0) {
        for (int i = y - 1; i <= y + 1; i++) {
            for (int j = x - 1; j <= x + 1; j++) {
                if (i >= 0 && j >= 0 && i < (*mapa).rozmiarMapy.y && j < (*mapa).rozmiarMapy.x) {
                    odkryciePola(mapa, j, i);
                }
            }
        }
    }
}

void sprawdzenieMapy(Mapa* mapa, StanGry* stan) {
    int pusteNieodkrytePola = 0;
    for (int i = 0; i < (*mapa).rozmiarMapy.y; i++) {
        for (int j = 0; j < (*mapa).rozmiarMapy.x; j++) {
            if ((*mapa).pola[i][j].odkryte && (*mapa).pola[i][j].mina) {
                (*stan) = Przegrana;
                odkrycieMapy(mapa, sfFalse);
            }
            if (!(*mapa).pola[i][j].odkryte && !(*mapa).pola[i][j].mina) {
                pusteNieodkrytePola++;
            }
        }
    }
    if (pusteNieodkrytePola == 0) {
        (*stan) = Wygrana;
        odkrycieMapy(mapa, sfTrue);
    }
}

void odkrycieMapy(Mapa* mapa, sfBool wygrana) {
    for (int i = 0; i < (*mapa).rozmiarMapy.y; i++) {
        for (int j = 0; j < (*mapa).rozmiarMapy.x; j++) {
            if ((*mapa).pola[i][j].flaga) {
                if ((*mapa).pola[i][j].mina) {
                    sfSprite_setTextureRect((*mapa).pola[i][j].grafika, (sfIntRect) { 2 * (*mapa).rozmiarPola.x, 0, (*mapa).rozmiarPola.x, (*mapa).rozmiarPola.x });
                }
                else {
                    sfSprite_setTextureRect((*mapa).pola[i][j].grafika, (sfIntRect) { 3 * (*mapa).rozmiarPola.x, 0, (*mapa).rozmiarPola.x, (*mapa).rozmiarPola.x });
                }
            }
            else if ((*mapa).pola[i][j].mina && !(*mapa).pola[i][j].odkryte) {
                if (wygrana) {
                    sfSprite_setTextureRect((*mapa).pola[i][j].grafika, (sfIntRect) { 2 * (*mapa).rozmiarPola.x, 0, (*mapa).rozmiarPola.x, (*mapa).rozmiarPola.x });
                }
                else {
                    sfSprite_setTextureRect((*mapa).pola[i][j].grafika, (sfIntRect) { 4 * (*mapa).rozmiarPola.x, 0, (*mapa).rozmiarPola.x, (*mapa).rozmiarPola.x });
                }
            }
        }
    }
}

void usuniecieMapy(Mapa* mapa) {
    for (int i = 0; i < (*mapa).rozmiarMapy.y; i++) {
        for (int j = 0; j < (*mapa).rozmiarMapy.x; j++) {
            sfSprite_destroy((*mapa).pola[i][j].grafika);
        }
        free((*mapa).pola[i]);
    }
    free((*mapa).pola);
    (*mapa).rozmiarMapy = (sfVector2i) { 0, 0 };
}