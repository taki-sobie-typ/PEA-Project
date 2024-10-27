#ifndef CZYTNIKGRAFOW_H
#define CZYTNIKGRAFOW_H

#include "MacierzKosztow.h"
#include <string>

using namespace std;

// Klasa odpowiedzialna za wczytywanie macierzy kosztów z pliku.
class CzytnikGrafow {
private:
    string sciezkaBazowa; // Ścieżka bazowa do plików z danymi.

public:
    // Konstruktor przyjmujący ścieżkę bazową jako parametr.
    CzytnikGrafow(string sciezkaBazowa);

    // Metoda do wczytywania macierzy kosztów z pliku i zwracająca ją.
    int** wczytajMacierz(string nazwaPliku, size_t& liczbaMiast);
};

#endif // CZYTNIKGRAFOW_H