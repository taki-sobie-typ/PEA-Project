#include "../header/GrafManager.h"
#include <iostream>
#include <string>

using namespace std;

// Destruktor klasy GrafManager
// Zwalnia pamięć zajmowaną przez macierz kosztów, jeśli została załadowana
GrafManager::~GrafManager() {
    if (macierzKosztow) {
        for (size_t i = 0; i < liczbaMiast; ++i) {
            delete[] macierzKosztow[i];
        }
        delete[] macierzKosztow;
    }
}

// Metoda do wczytywania danych z pliku
void GrafManager::wczytajDaneZPliku() {
    string nazwaPliku;
    cout << "Podaj nazwe pliku: ";
    cin >> nazwaPliku;
    cout << endl;

    // Zwolnij istniejącą macierz kosztów, jeśli istnieje
    if (macierzKosztow) {
        for (size_t i = 0; i < liczbaMiast; ++i) {
            delete[] macierzKosztow[i];
        }
        delete[] macierzKosztow;
        macierzKosztow = nullptr;
    }

    // Wczytaj nowe dane z pliku
    macierzKosztow = czytnikGrafow.wczytajMacierz(nazwaPliku, liczbaMiast);

    // Sprawdź, czy dane zostały poprawnie wczytane
    if (macierzKosztow) {
        cout << "Dane zostaly wczytane pomyslnie." << endl;
    } else {
        cout << "Blad wczytywania danych." << endl;
    }
    cout << endl;
}

// Metoda do generowania losowego grafu
void GrafManager::wygenerujGrafLosowo() {
    int liczbaWierzcholkow, minWartosc, maxWartosc;

    cout << "Podaj liczbe wierzcholkow: ";
    cin >> liczbaWierzcholkow;
    cout << "Podaj minimalna wartosc krawedzi: ";
    cin >> minWartosc;
    cout << "Podaj maksymalna wartosc krawedzi: ";
    cin >> maxWartosc;
    cout << endl;

    // Wygeneruj losowy graf używając klasy GrafGenerator
    vector<vector<int>> matrix = GrafGenerator::generujLosowaMacierz(liczbaWierzcholkow, minWartosc, maxWartosc);

    // Zwolnij istniejącą macierz kosztów, jeśli istnieje
    if (macierzKosztow) {
        for (size_t i = 0; i < liczbaMiast; ++i) {
            delete[] macierzKosztow[i];
        }
        delete[] macierzKosztow;
        macierzKosztow = nullptr;
    }

    // Zaktualizuj liczbaMiast i zaalokuj nową macierz kosztów
    liczbaMiast = liczbaWierzcholkow;
    macierzKosztow = new int*[liczbaMiast];
    for (size_t i = 0; i < liczbaMiast; ++i) {
        macierzKosztow[i] = new int[liczbaMiast];
        for (size_t j = 0; j < liczbaMiast; ++j) {
            macierzKosztow[i][j] = matrix[i][j];
        }
    }

    cout << "Graf zostal wygenerowany pomyslnie." << endl;
    cout << endl;
}

// Metoda do wyświetlania macierzy kosztów
void GrafManager::wyswietlGraf() {
    if (macierzKosztow) {
        cout << "Macierz:" << endl;
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

// Metoda do uruchomienia algorytmu Brute Force
void GrafManager::uruchomBruteForce() {
    if (macierzKosztow) {
        int start;

        // Poproś użytkownika o wybór wierzchołka startowego
        cout << "Wybierz wierzcholek startowy (od 0 do " << liczbaMiast - 1 << "): ";
        cin >> start;

        // Upewnij się, że użytkownik podał poprawny numer wierzchołka
        while (start < 0 || start >= liczbaMiast) {
            cout << "Niepoprawny wierzcholek. Wybierz wierzcholek startowy (od 0 do " << liczbaMiast - 1 << "): ";
            cin >> start;
        }

        // Utwórz obiekt macierzy kosztów i uruchom algorytm Brute Force
        MacierzKosztow macierz(macierzKosztow, liczbaMiast);
        cout << "Uruchamianie algorytmu Brute Force od miasta " << start << "..." << endl;
        BruteForce::uruchomAlgorytm(macierz, start);
    } else {
        cout << "Brak zaladowanej macierzy kosztow. Najpierw wczytaj lub wygeneruj graf." << endl;
    }
}
