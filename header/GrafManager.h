#ifndef GRAFMANAGER_H
#define GRAFMANAGER_H

#include <iostream>
#include <string>
#include "MacierzKosztow.h"
#include "GrafGenerator.h"
#include "CzytnikGrafow.h"
#include "BruteForce.h"
#include "BranchAndBound.h"
#include "SimulatedAnnealing.h"

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

    void wczytajDaneZPliku();

    void wygenerujGrafLosowo();

    void wyswietlGraf();

    void uruchomBruteForce();

    void uruchomBranchAndBound();

    void uruchomSimulatedAnnealing();

    void zapiszDoCSV(const string& nazwaPliku, int liczbaMiast, long long czas);

    void zapiszDoCSV2(const string& nazwaPliku, int liczbaMiast, long long czas, int procent, int czyprzerwany);

    void testForReportBF();

    void testForReportBandB_BFS();

    void testForReportSymetric();
};

#endif // GRAFMANAGER_H