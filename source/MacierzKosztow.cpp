#include "../header/MacierzKosztow.h"
#include <iomanip>

MacierzKosztow::MacierzKosztow(int** koszty, size_t liczbaMiast) : liczbaMiast(liczbaMiast) {
    // Copy the matrix
    macierzKosztow = new int*[liczbaMiast];
    for (size_t i = 0; i < liczbaMiast; ++i) {
        macierzKosztow[i] = new int[liczbaMiast];
        for (size_t j = 0; j < liczbaMiast; ++j) {
            macierzKosztow[i][j] = koszty[i][j];
        }
    }
}

MacierzKosztow::~MacierzKosztow() {
    for (size_t i = 0; i < liczbaMiast; ++i) {
        delete[] macierzKosztow[i];
    }
    delete[] macierzKosztow;
}

void MacierzKosztow::drukuj(ostream& wyjscie) const {
    const int cellWidth = 5; // Set cell width for alignment

    wyjscie << "    "; // Initial space before city numbers
    for (size_t i = 0; i < liczbaMiast; ++i) {
        wyjscie << setw(cellWidth) << i << " ";
    }
    wyjscie << endl;

    for (size_t i = 0; i < liczbaMiast; ++i) {
        wyjscie << setw(3) << i << " "; // City number
        for (size_t j = 0; j < liczbaMiast; ++j) {
            if (macierzKosztow[i][j] == -1) {
                wyjscie << setw(cellWidth) << "inf" << " "; // Replace -1 with 'inf' for readability
            } else {
                wyjscie << setw(cellWidth) << macierzKosztow[i][j] << " ";
            }
        }
        wyjscie << endl;
    }
}

int MacierzKosztow::pobierzKoszt(size_t u, size_t v) const {
    return macierzKosztow[u][v];
}

size_t MacierzKosztow::pobierzLiczbeMiast() const {
    return liczbaMiast;
}

int** MacierzKosztow::pobierzMacierzKosztow() const {
    return macierzKosztow; // Return the internal cost matrix
}
