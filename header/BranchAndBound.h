#ifndef BRANCHANDBOUND_H
#define BRANCHANDBOUND_H

#include "MacierzKosztow.h"
#include "vector"

// Klasa realizująca algorytm Branch And Bound.
class BranchAndBound {
public:
    static long long uruchomAlgorytm(const MacierzKosztow& graf);

private:
    struct Node {
        int* sciezka; // Aktualna ścieżka
        int sciezkaCount;
        int koszt;              // Koszt aktualnej ścieżki
        int poziom;             // Poziom w drzewie (liczba odwiedzonych miast)
    };

    static bool miastoZawarteSciezka(int* sciezka, int scieckaCount, int miasto);

};

#endif //BRANCHANDBOUND_H
