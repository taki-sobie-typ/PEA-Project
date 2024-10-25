#ifndef GRAFMANAGER_H
#define GRAFMANAGER_H

#include <iostream>
#include <string>
#include "MacierzKosztow.h"   // Include the cost matrix header
#include "GeneratorGrafow.h"
#include "CzytnikGrafow.h"
#include "BruteForce.h"

using namespace std;

class GrafManager {
private:
    int** macierzKosztow;  // Pointer to the cost matrix
    size_t liczbaMiast;    // Number of cities

    GeneratorGrafow generatorGrafow;
    CzytnikGrafow czytnikGrafow;

public:
    GrafManager() : macierzKosztow(nullptr), liczbaMiast(0), czytnikGrafow("dane/") {}
    ~GrafManager();

    void wczytajDaneZPliku();     // Load data from a file
    void wygenerujGrafLosowo();    // Generate a random graph
    void wyswietlGraf();           // Display the cost matrix
    void uruchomBruteForce(int start); // New method to run Brute Force
};

#endif // GRAFMANAGER_H
