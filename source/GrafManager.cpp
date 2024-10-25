#include "../header/GrafManager.h"
#include <iostream>
#include <string>

using namespace std;

GrafManager::~GrafManager() {
    // Destructor to release memory
    if (macierzKosztow) {
        for (size_t i = 0; i < liczbaMiast; ++i) {
            delete[] macierzKosztow[i];
        }
        delete[] macierzKosztow;
    }
}

void GrafManager::wczytajDaneZPliku() {
    string nazwaPliku;
    cout << "Podaj nazwe pliku: ";
    cin >> nazwaPliku;
    cout << endl;

    // Free existing macierzKosztow if it exists
    if (macierzKosztow) {
        for (size_t i = 0; i < liczbaMiast; ++i) {
            delete[] macierzKosztow[i];
        }
        delete[] macierzKosztow;
        macierzKosztow = nullptr;
    }

    // Read new data
    macierzKosztow = czytnikGrafow.wczytajMacierz(nazwaPliku, liczbaMiast);

    if (macierzKosztow) {
        cout << "Dane zostaly wczytane pomyslnie." << endl;
    } else {
        cout << "Blad wczytywania danych." << endl;
    }
    cout << endl;
}

void GrafManager::wygenerujGrafLosowo() {
    size_t liczbaWierzcholkow;
    float gestosc;
    size_t maxWartosc;

    cout << "Podaj liczbe wierzcholków: ";
    cin >> liczbaWierzcholkow;
    cout << "Podaj gestosc grafu (w %): ";
    cin >> gestosc;
    cout << "Podaj maksymalna wartosc krawedzi: ";
    cin >> maxWartosc;
    cout << endl;

    SuroweDaneGrafu dane = generatorGrafow.generuj(gestosc / 100.0, liczbaWierzcholkow, maxWartosc);

    // Free existing macierzKosztow if it exists
    if (macierzKosztow) {
        for (size_t i = 0; i < liczbaMiast; ++i) {
            delete[] macierzKosztow[i];
        }
        delete[] macierzKosztow;
        macierzKosztow = nullptr;
    }

    // Update the number of cities
    liczbaMiast = dane.liczbaWierzcholkow;

    // Allocate new macierzKosztow and populate it
    macierzKosztow = new int*[liczbaMiast];
    for (size_t i = 0; i < liczbaMiast; ++i) {
        macierzKosztow[i] = new int[liczbaMiast];
        for (size_t j = 0; j < liczbaMiast; ++j) {
            macierzKosztow[i][j] = dane.dane[i * liczbaMiast + j];
        }
    }

    delete[] dane.dane;

    cout << "Graf zostal wygenerowany pomyslnie." << endl;
    cout << endl;
}

void GrafManager::wyswietlGraf() {
    if (macierzKosztow) {
        cout << "Macierz Kosztow:" << endl;
        for (size_t i = 0; i < liczbaMiast; ++i) {
            for (size_t j = 0; j < liczbaMiast; ++j) {
                cout << macierzKosztow[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    } else {
        cout << "Brak danych do wyswietlenia." << endl;
    }
}

// New method to run the Brute Force algorithm
void GrafManager::uruchomBruteForce(int start) {
    if (macierzKosztow) {
        MacierzKosztow macierz(macierzKosztow, liczbaMiast);
        cout << "Uruchamianie algorytmu Brute Force od miasta " << start << "..." << endl;
        BruteForce::uruchomDlaMacierzy(macierz, start);
    } else {
        cout << "Brak zaladowanej macierzy kosztow. Najpierw wczytaj lub wygeneruj graf." << endl;
    }
}
