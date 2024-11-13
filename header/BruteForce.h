#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "MacierzKosztow.h"

// Klasa realizująca algorytm Brute Force.
class BruteForce {
public:
    // Statyczna metoda uruchamiająca algorytm Brute Force na podanej macierzy kosztów, rozpoczynając od wybranego miasta.
    static long long uruchomAlgorytm(const MacierzKosztow& graf);
};

#endif // BRUTEFORCE_H