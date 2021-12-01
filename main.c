#include <stdlib.h>
#include <time.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include "SFMl/Window.h"
#include "mapa.h"
#include "menu.h"
#include "tlo.h"
#include "stanGry.h"

sfVector2i ustawienieRozmiaruOkna(int rozmiar, sfRenderWindow* okno, sfView* widok, Menu* menu, Tlo* tlo, StanGry* stan);

int main() {
	HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
	srand(time(NULL));
	sfClock* zegar = sfClock_create();
	sfTime czas = sfTime_Zero;
    sfEvent zdarzenie;
	StanGry stan = Poczatek;
	Mapa mapa;
	sfVector2i rozmiar = (sfVector2i) { 8, 8 };
	if (!tworzenieMapy(&mapa, (sfVector2f) { 32, 32 })) {
		return 1;
	}
	Menu menu;
	if (!tworzenieMenu(&menu, (sfVector2f) { 304, 32 })) {
		return 1;
	}
	Tlo tlo;
	if (!tworzenieTla(&tlo)) {
		return 1;
	}
    sfRenderWindow* okno = sfRenderWindow_create((sfVideoMode) { 800, 600, 32 }, "Saper", sfClose, NULL);
    if (!okno) {
        return 1;
	}
	sfView* widok = sfView_create();
	rozmiar = ustawienieRozmiaruOkna(1, okno, widok, &menu, &tlo, &stan);
	sfRenderWindow_setFramerateLimit(okno, 60);
	sfImage* ikona = sfImage_createFromFile("./grafika/ikona.png");
	if (ikona != NULL) {
		sfRenderWindow_setIcon(okno, 16, 16, sfImage_getPixelsPtr(ikona));
	}
    while (sfRenderWindow_isOpen(okno)) {
		if (stan == Poczatek) {
			losowanieMapy(&mapa, (sfVector2i) { rozmiar.x, rozmiar.y }, 0.15);
			czas = sfTime_Zero;
			sfText_setColor(menu.zegar, sfYellow);
			zmianaTla(&tlo, &stan);
			stan = Gra;
		}
        while (sfRenderWindow_pollEvent(okno, &zdarzenie)) {
            if (zdarzenie.type == sfEvtClosed) {
                sfRenderWindow_close(okno);
			}
			if (zdarzenie.type == sfEvtMouseButtonPressed) {
				if (sfMouse_isButtonPressed(sfMouseLeft)) {
					klikniecieMenu(&menu, okno, &stan);
					if (stan == Gra) {
						klikniecieMapy(&mapa, okno, sfFalse);
						sprawdzenieMapy(&mapa, &stan);
						if (stan == Wygrana) {
							sfText_setColor(menu.zegar, sfGreen);
							zmianaTla(&tlo, &stan);
						}
						else if (stan == Przegrana)  {
							sfText_setColor(menu.zegar, sfRed);
							zmianaTla(&tlo, &stan);
						}
					}
				}
				if (sfMouse_isButtonPressed(sfMouseRight)) {
					if (stan == Gra){
						klikniecieMapy(&mapa, okno, sfTrue);
					}
				}
			}
			if (zdarzenie.type == sfEvtKeyPressed) {
				if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
					if (stan == Gra) {
						stan = Pauza;
					}
					else if (stan == Pauza) {
						stan = Gra;
					}
				}
				if (sfKeyboard_isKeyPressed(sfKeyF1)) {
					rozmiar = ustawienieRozmiaruOkna(1, okno, widok, &menu, &tlo, &stan);
				}
				if (sfKeyboard_isKeyPressed(sfKeyF2)) {
					rozmiar = ustawienieRozmiaruOkna(2, okno, widok, &menu, &tlo, &stan);
				}
				if (sfKeyboard_isKeyPressed(sfKeyF3)) {
					rozmiar = ustawienieRozmiaruOkna(3, okno, widok, &menu, &tlo, &stan);
				}
			}
        }
		if (stan == Gra) {
			sfTime roznica = sfClock_getElapsedTime(zegar);
			czas.microseconds += roznica.microseconds;
			ustawienieCzasu(&menu, czas);
		}
		if (stan == Wyjscie) {
			usuniecieMapy(&mapa);
			sfRenderWindow_destroy(okno);
			return 0;
		}
		sfClock_restart(zegar);
        sfRenderWindow_clear(okno, sfBlack);
		wyswietlenieTla(&tlo, okno);
		wyswietlenieMapy(&mapa, okno);
		wyswietlenieMenu(&menu, okno);
        sfRenderWindow_display(okno);
    }
	usuniecieMapy(&mapa);
    sfRenderWindow_destroy(okno);
	return 0;
}


sfVector2i ustawienieRozmiaruOkna(int rozmiar, sfRenderWindow* okno, sfView* widok, Menu* menu, Tlo* tlo, StanGry* stan) {
	if (rozmiar == 3) {
		(*stan) = Poczatek;
		sfView_setSize(widok, (sfVector2f) { 1024, 448 });
		sfView_setCenter(widok, (sfVector2f) { 512, 224 });
		sfRenderWindow_setSize(okno, (sfVector2u) { 1024, 448 });
		sfRenderWindow_setView(okno, widok);
		ustawienieMenu(menu, (sfVector2f) { 832, 32 });
		zmianaRozmiaruTla(tlo, (sfVector2i) { 1024, 448 });
		return (sfVector2i) { 32, 16 };
	}
	if (rozmiar == 2) {
		(*stan) = Poczatek;
		sfView_setSize(widok, (sfVector2f) { 640, 448 });
		sfView_setCenter(widok, (sfVector2f) { 320, 224 });
		sfRenderWindow_setSize(okno, (sfVector2u) { 640, 448 });
		sfRenderWindow_setView(okno, widok);
		ustawienieMenu(menu, (sfVector2f) { 448, 32 });
		zmianaRozmiaruTla(tlo, (sfVector2i) { 640, 448 });
		return (sfVector2i) { 16, 16 };
	}
	(*stan) = Poczatek;
	sfView_setSize(widok, (sfVector2f) { 448, 256 });
	sfView_setCenter(widok, (sfVector2f) { 224, 128 });
	sfRenderWindow_setSize(okno, (sfVector2u) { 448, 256 });
	sfRenderWindow_setView(okno, widok);
	ustawienieMenu(menu, (sfVector2f) { 256, 32 });
	zmianaRozmiaruTla(tlo, (sfVector2i) { 448, 256 });
	return (sfVector2i) { 8, 8 };
}