#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include "GrafManager.h"

using namespace std;

// Klasa odpowiedzialna za wyświetlanie menu aplikacji i obsługę interakcji z użytkownikiem.
class Menu {
private:
    GrafManager grafManager; // Obiekt do zarządzania operacjami na grafach.

    // Metoda do wczytywania danych z pliku.
    void wczytajDaneZPliku();

    // Metoda do generowania losowego grafu.
    void wygenerujGrafLosowo();

    // Metoda do wyświetlania macierzy kosztów.
    void wyswietlGraf();

    // Metoda do uruchamiania testu algorytmu Brute Force.
    void testBruteForce();

public:
    Menu() {}

    // Metoda do wyświetlania głównego menu aplikacji.
    void wyswietlMenuGlowne();
};

#endif // MENU_H