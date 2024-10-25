#ifndef CZYTNIKGRAFOW_H
#define CZYTNIKGRAFOW_H

#include "MacierzKosztow.h"
#include <string>

using namespace std;

class CzytnikGrafow {
private:
    string sciezkaBazowa;

public:
    CzytnikGrafow(string sciezkaBazowa);

    // Method to read and return the cost matrix
    int** wczytajMacierz(string nazwaPliku, size_t& liczbaMiast);
};

#endif // CZYTNIK_GRAFOW_H
