#ifndef GRAFGENERATOR_H
#define GRAFGENERATOR_H

#include <vector>

// Klasa do generowania losowej macierzy kosztów dla grafu.
class GrafGenerator {
public:
    // Funkcja statyczna do generowania losowej macierzy kosztów o zadanym rozmiarze, minimalnej i maksymalnej wartości kosztu.
    static std::vector<std::vector<int>> generujLosowaMacierz(int rozmiar, int minWartosc, int maxWartosc, bool symetryczna);
};

#endif // GRAFGENERATOR_H
