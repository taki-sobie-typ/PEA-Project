#include "../header/CzytnikGrafow.h"
#include <iostream>
#include <fstream>

using namespace std;

CzytnikGrafow::CzytnikGrafow(string sciezkaBazowa) : sciezkaBazowa(sciezkaBazowa) {}

int** CzytnikGrafow::wczytajMacierz(string nazwaPliku, size_t& liczbaMiast) {
    ifstream plik(this->sciezkaBazowa + nazwaPliku);

    if (plik.fail()) {
        cerr << "Nie można otworzyć pliku!" << endl;
        return nullptr;
    }

    // Wczytaj liczbę miast
    plik >> liczbaMiast;

    // Tworzymy macierz kosztów (domyślnie zainicjalizowaną na -1)
    int** macierz = new int*[liczbaMiast];
    for (size_t i = 0; i < liczbaMiast; ++i) {
        macierz[i] = new int[liczbaMiast];
        for (size_t j = 0; j < liczbaMiast; ++j) {
            plik >> macierz[i][j];
        }
    }

    plik.close();
    return macierz;
}
