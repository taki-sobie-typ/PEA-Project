#ifndef GRAFMANAGER_H
#define GRAFMANAGER_H

#include <iostream>
#include <string>
#include "MacierzKosztow.h"
#include "GrafGenerator.h"
#include "CzytnikGrafow.h"
#include "BruteForce.h"

using namespace std;

// Klasa zarządzająca operacjami na grafach, takimi jak wczytywanie, generowanie, wyświetlanie oraz uruchamianie algorytmów.
class GrafManager {
private:
    int** macierzKosztow;  // Wskaźnik do macierzy kosztów.
    size_t liczbaMiast;    // Liczba miast (wierzchołków) w grafie.

    CzytnikGrafow czytnikGrafow;     // Obiekt do wczytywania grafów z plików.

public:
    GrafManager() : macierzKosztow(nullptr), liczbaMiast(0), czytnikGrafow("dane/") {}
    ~GrafManager();

    // Metoda do wczytywania danych z pliku.
    void wczytajDaneZPliku();

    // Metoda do generowania losowego grafu.
    void wygenerujGrafLosowo();

    // Metoda do wyświetlania macierzy kosztów.
    void wyswietlGraf();

    // Metoda do uruchamiania algorytmu Brute Force.
    void uruchomBruteForce();
};

#endif // GRAFMANAGER_H