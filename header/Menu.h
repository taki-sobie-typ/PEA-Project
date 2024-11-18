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

    // Metoda do uruchamiania testu algorytmu BrachAndBound.
    void testBranchAndBound();

    // Metoda do uruchamiania testu algorytmu BrachAndBound.
    void testForReportSymetric();

    // Metoda uruchamiająca procedurę testowania algorytmów Brute Force dla raportu.
    void testForReportBF();

    // Metoda uruchamiająca procedurę testowania algorytmów BrachAndBound i BFS dla raportu.
    void testForReportBandB_BFS();

public:
    Menu() {}

    // Metoda do wyświetlania głównego menu aplikacji.
    void wyswietlMenuGlowne();
};

#endif // MENU_H
