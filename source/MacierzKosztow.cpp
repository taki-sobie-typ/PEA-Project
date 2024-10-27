#include "../header/MacierzKosztow.h"
#include <iomanip>

// Konstruktor klasy MacierzKosztow
// Kopiuje podaną macierz kosztów do wewnętrznej struktury klasy.
// Parametry:
// - koszty: wskaźnik na oryginalną macierz kosztów
// - liczbaMiast: liczba miast (rozmiar macierzy)
MacierzKosztow::MacierzKosztow(int** koszty, size_t liczbaMiast) : liczbaMiast(liczbaMiast) {
    // Kopiowanie macierzy kosztów
    macierzKosztow = new int*[liczbaMiast];
    for (size_t i = 0; i < liczbaMiast; ++i) {
        macierzKosztow[i] = new int[liczbaMiast];
        for (size_t j = 0; j < liczbaMiast; ++j) {
            macierzKosztow[i][j] = koszty[i][j];
        }
    }
}

// Destruktor klasy MacierzKosztow
// Zwalnia pamięć zajmowaną przez wewnętrzną macierz kosztów.
MacierzKosztow::~MacierzKosztow() {
    for (size_t i = 0; i < liczbaMiast; ++i) {
        delete[] macierzKosztow[i];
    }
    delete[] macierzKosztow;
}

// Metoda do drukowania macierzy kosztów na podanym strumieniu wyjściowym.
// Zamiast -1 wyświetla 'inf' dla lepszej czytelności.
void MacierzKosztow::drukuj(ostream& wyjscie) const {
    const int cellWidth = 5; // Ustawienie szerokości komórki dla wyrównania

    wyjscie << "    "; // Początkowa spacja przed numerami miast
    for (size_t i = 0; i < liczbaMiast; ++i) {
        wyjscie << setw(cellWidth) << i << " "; // Wyświetlanie numerów miast w nagłówku
    }
    wyjscie << endl;

    for (size_t i = 0; i < liczbaMiast; ++i) {
        wyjscie << setw(3) << i << " "; // Wyświetlanie numeru miasta w wierszu
        for (size_t j = 0; j < liczbaMiast; ++j) {
            if (macierzKosztow[i][j] == -1) {
                wyjscie << setw(cellWidth) << "inf" << " "; // Zamiana -1 na 'inf'
            } else {
                wyjscie << setw(cellWidth) << macierzKosztow[i][j] << " ";
            }
        }
        wyjscie << endl;
    }
}

// Metoda zwracająca koszt podróży z miasta `u` do miasta `v`.
// Parametry:
// - u: numer miasta początkowego
// - v: numer miasta docelowego
// Zwraca wartość z macierzy kosztów.
int MacierzKosztow::pobierzKoszt(size_t u, size_t v) const {
    return macierzKosztow[u][v];
}

// Metoda zwracająca liczbę miast w grafie.
size_t MacierzKosztow::pobierzLiczbeMiast() const {
    return liczbaMiast;
}

// Metoda zwracająca wewnętrzną macierz kosztów.
// Zwraca wskaźnik do macierzy kosztów.
int** MacierzKosztow::pobierzMacierzKosztow() const {
    return macierzKosztow; // Zwraca wewnętrzną macierz kosztów
}
