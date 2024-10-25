#ifndef MACIERZ_KOSZTOW_H
#define MACIERZ_KOSZTOW_H

#include <iostream>
using namespace std;

class MacierzKosztow {
private:
    size_t liczbaMiast;
    int** macierzKosztow;

public:
    MacierzKosztow(int** koszty, size_t liczbaMiast);
    ~MacierzKosztow();

    // Print the cost matrix
    void drukuj(ostream& wyjscie) const;

    // Retrieve the cost between city u and city v
    int pobierzKoszt(size_t u, size_t v) const;

    // Get the number of cities
    size_t pobierzLiczbeMiast() const;

    // Get Macierz Kosztow
    int** pobierzMacierzKosztow() const;
};

#endif // MACIERZ_KOSZTOW_H
