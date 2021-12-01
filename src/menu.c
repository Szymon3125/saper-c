#include "menu.h"

sfBool tworzenieMenu(Menu* menu, sfVector2f odstepOdKrawedzi) {
    sfTexture* tekstura = sfTexture_createFromFile("./grafika/menu.png", NULL);
    if (tekstura == NULL) {
        return sfFalse;
    }
    sfFont* czcionka = sfFont_createFromFile("./czcionki/courierNew.ttf");
    if (czcionka == NULL) {
        return sfFalse;
    }
    sfVector2i rozmiarPrzycisku = (sfVector2i) { 160, 32 };
    int odstepMiedzyPrzyciskami = 16;
    (*menu).tekstura = tekstura;
    (*menu).zegar = sfText_create();
    sfText_setFont((*menu).zegar, czcionka);
    sfText_setString((*menu).zegar, "00:00:00");
    sfText_setCharacterSize((*menu).zegar, rozmiarPrzycisku.y - 4);
    sfText_setPosition((*menu).zegar, (sfVector2f) { odstepOdKrawedzi.x + 12, odstepOdKrawedzi.y - 4 });
    (*menu).grafikaZegar = sfSprite_create();
    sfSprite_setTexture((*menu).grafikaZegar, tekstura, sfFalse);
    sfSprite_setTextureRect((*menu).grafikaZegar, (sfIntRect) { 0, 0, rozmiarPrzycisku.x, rozmiarPrzycisku.y });
    sfSprite_setPosition((*menu).grafikaZegar, (sfVector2f) { odstepOdKrawedzi.x, odstepOdKrawedzi.y });
    (*menu).grafikaPauza = sfSprite_create();
    sfSprite_setTexture((*menu).grafikaPauza, tekstura, sfFalse);
    sfSprite_setTextureRect((*menu).grafikaPauza, (sfIntRect) { 0, rozmiarPrzycisku.y, rozmiarPrzycisku.x, rozmiarPrzycisku.y });
    sfSprite_setPosition((*menu).grafikaPauza, (sfVector2f) { odstepOdKrawedzi.x, odstepOdKrawedzi.y + odstepMiedzyPrzyciskami + rozmiarPrzycisku.y });
    (*menu).grafikaNowaGra = sfSprite_create();
    sfSprite_setTexture((*menu).grafikaNowaGra, tekstura, sfFalse);
    sfSprite_setTextureRect((*menu).grafikaNowaGra, (sfIntRect) { 0, 2 * rozmiarPrzycisku.y, rozmiarPrzycisku.x, rozmiarPrzycisku.y });
    sfSprite_setPosition((*menu).grafikaNowaGra, (sfVector2f) { odstepOdKrawedzi.x, odstepOdKrawedzi.y + 2 * (odstepMiedzyPrzyciskami + rozmiarPrzycisku.y) });
    (*menu).grafikaWyjscie = sfSprite_create();
    sfSprite_setTexture((*menu).grafikaWyjscie, tekstura, sfFalse);
    sfSprite_setTextureRect((*menu).grafikaWyjscie, (sfIntRect) { 0, 3 * + rozmiarPrzycisku.y, rozmiarPrzycisku.x, rozmiarPrzycisku.y });
    sfSprite_setPosition((*menu).grafikaWyjscie, (sfVector2f) { odstepOdKrawedzi.x, odstepOdKrawedzi.y + 3 * (odstepMiedzyPrzyciskami + rozmiarPrzycisku.y) });
    return sfTrue;
}

void ustawienieMenu(Menu* menu, sfVector2f odstepOdKrawedzi) {
    sfVector2i rozmiarPrzycisku = (sfVector2i) { 160, 32 };
    int odstepMiedzyPrzyciskami = 16;
    sfText_setPosition((*menu).zegar, (sfVector2f) { odstepOdKrawedzi.x + 12, odstepOdKrawedzi.y - 4 });
    sfSprite_setPosition((*menu).grafikaZegar, (sfVector2f) { odstepOdKrawedzi.x, odstepOdKrawedzi.y });
    sfSprite_setPosition((*menu).grafikaPauza, (sfVector2f) { odstepOdKrawedzi.x, odstepOdKrawedzi.y + odstepMiedzyPrzyciskami + rozmiarPrzycisku.y });
    sfSprite_setPosition((*menu).grafikaNowaGra, (sfVector2f) { odstepOdKrawedzi.x, odstepOdKrawedzi.y + 2 * (odstepMiedzyPrzyciskami + rozmiarPrzycisku.y) });
    sfSprite_setPosition((*menu).grafikaWyjscie, (sfVector2f) { odstepOdKrawedzi.x, odstepOdKrawedzi.y + 3 * (odstepMiedzyPrzyciskami + rozmiarPrzycisku.y) });
}

void ustawienieCzasu(Menu* menu, sfTime czas) {
    int milisekundy = czas.microseconds / 1000;
    int sekundy = czas.microseconds / 1000000;
    int minuty = czas.microseconds / 60000000;
    char napis[9] = "";
    napis[0] = (sekundy % 10000) / 1000 + 48;
    napis[1] = (sekundy % 1000) / 100 + 48;
    napis[2] = ':';
    napis[3] = (sekundy % 100) / 10 + 48;
    napis[4] = sekundy % 10 + 48;
    napis[5] = ':';
    napis[6] = (milisekundy % 1000) / 100 + 48;
    napis[7] = (milisekundy % 100) / 10 + 48;
    napis[8] = '\0';
    sfText_setString((*menu).zegar, napis);
}

void wyswietlenieMenu(Menu* menu, sfRenderWindow* okno) {
    sfRenderWindow_drawSprite(okno, (*menu).grafikaZegar, NULL);
    sfRenderWindow_drawSprite(okno, (*menu).grafikaPauza, NULL);
    sfRenderWindow_drawSprite(okno, (*menu).grafikaNowaGra, NULL);
    sfRenderWindow_drawSprite(okno, (*menu).grafikaWyjscie, NULL);
    sfRenderWindow_drawText(okno, (*menu).zegar, NULL);
}

void klikniecieMenu(Menu* menu, sfRenderWindow* okno, StanGry* stan) {
    sfFloatRect polozennie = sfSprite_getGlobalBounds((*menu).grafikaPauza);
    if (sfFloatRect_contains(&polozennie, sfMouse_getPositionRenderWindow(okno).x, sfMouse_getPositionRenderWindow(okno).y)) {
        if ((*stan) == Gra) {
            (*stan) = Pauza;
        }
        else if ((*stan) == Pauza) {
            (*stan) = Gra;
        }
    }
    polozennie = sfSprite_getGlobalBounds((*menu).grafikaNowaGra);
    if (sfFloatRect_contains(&polozennie, sfMouse_getPositionRenderWindow(okno).x, sfMouse_getPositionRenderWindow(okno).y)) {
        (*stan) = Poczatek;
    }
    polozennie = sfSprite_getGlobalBounds((*menu).grafikaWyjscie);
    if (sfFloatRect_contains(&polozennie, sfMouse_getPositionRenderWindow(okno).x, sfMouse_getPositionRenderWindow(okno).y)) {
        (*stan) = Wyjscie;
    }
}
