#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "MacierzKosztow.h"

// Klasa realizująca algorytm Brute Force.
class BruteForce {
public:
    // Statyczna metoda uruchamiająca algorytm Brute Force na podanej macierzy kosztów, rozpoczynając od wybranego miasta.
    static void uruchomAlgorytm(const MacierzKosztow& graf, int start);
};

#endif // BRUTEFORCE_H