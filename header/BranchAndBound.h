#ifndef BRANCHANDBOUND_H
#define BRANCHANDBOUND_H

#include "MacierzKosztow.h"
#include "vector"

// Klasa realizująca algorytm Branch And Bound.
class BranchAndBound {
public:
    static std::pair<std::pair<long long, int>, int> uruchomAlgorytm(const MacierzKosztow& macierz, long long limitCzasuMS);

private:
    struct Node {
        int* sciezka; // Aktualna ścieżka
        int sciezkaCount; // Ostatni element w ścieżce
        int koszt; // Koszt aktualnej ścieżki
        int poziom; // Poziom w drzewie (liczba odwiedzonych miast)
    };

    static bool miastoZawarteSciezka(int* sciezka, int scieckaCount, int miasto);

};

#endif //BRANCHANDBOUND_H
