#include "../header/CzytnikGrafow.h"
#include <iostream>
#include <fstream>

using namespace std;

// Konstruktor klasy CzytnikGrafow, który ustawia ścieżkę bazową dla plików z danymi
CzytnikGrafow::CzytnikGrafow(string sciezkaBazowa) : sciezkaBazowa(sciezkaBazowa) {}

// Funkcja do wczytania macierzy kosztów z pliku
int** CzytnikGrafow::wczytajMacierz(string nazwaPliku, size_t& liczbaMiast) {
    // Otwórz plik do odczytu, łącząc ścieżkę bazową i nazwę pliku
    ifstream plik(this->sciezkaBazowa + nazwaPliku);

    // Sprawdzenie, czy plik został poprawnie otwarty
    if (plik.fail()) {
        cerr << "Nie można otworzyć pliku!" << endl;
        return nullptr;
    }

    // Wczytaj liczbę miast z pliku (pierwsza wartość w pliku)
    plik >> liczbaMiast;

    // Tworzenie dynamicznej macierzy kosztów (domyślnie zainicjalizowanej)
    int** macierz = new int*[liczbaMiast];
    for (size_t i = 0; i < liczbaMiast; ++i) {
        macierz[i] = new int[liczbaMiast];
        for (size_t j = 0; j < liczbaMiast; ++j) {
            // Wczytaj wartość kosztu z pliku do macierzy
            plik >> macierz[i][j];
        }
    }

    // Zamknij plik po zakończeniu odczytu
    plik.close();

    // Zwróć wskaźnik do wczytanej macierzy
    return macierz;
}
