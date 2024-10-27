#ifndef MACIERZ_KOSZTOW_H
#define MACIERZ_KOSZTOW_H

#include <iostream>
using namespace std;

// Klasa reprezentująca macierz kosztów dla problemu komiwojażera.
class MacierzKosztow {
private:
    size_t liczbaMiast;   // Liczba miast w grafie.
    int** macierzKosztow; // Wskaźnik do macierzy kosztów.

public:
    // Konstruktor przyjmujący wskaźnik do macierzy kosztów i liczbę miast.
    MacierzKosztow(int** koszty, size_t liczbaMiast);

    // Destruktor zwalniający pamięć.
    ~MacierzKosztow();

    // Metoda do drukowania macierzy kosztów.
    void drukuj(ostream& wyjscie) const;

    // Metoda do pobierania kosztu przejścia między miastami u i v.
    int pobierzKoszt(size_t u, size_t v) const;

    // Metoda do pobierania liczby miast.
    size_t pobierzLiczbeMiast() const;

    // Metoda do pobierania wskaźnika do macierzy kosztów.
    int** pobierzMacierzKosztow() const;
};

#endif // MACIERZ_KOSZTOW_H