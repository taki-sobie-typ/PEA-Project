#include "../header/GrafManager.h"

#include <fstream>
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
    vector<vector<int>> matrix = GrafGenerator::generujLosowaMacierz(liczbaWierzcholkow, minWartosc, maxWartosc, false);

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
        // Utwórz obiekt macierzy kosztów i uruchom algorytm Brute Force
        MacierzKosztow macierz(macierzKosztow, liczbaMiast);
        BruteForce::uruchomAlgorytm(macierz);
    } else {
        cout << "Brak zaladowanej macierzy kosztow. Najpierw wczytaj lub wygeneruj graf." << endl;
    }
}

// Metoda do uruchomienia algorytmue
void GrafManager::uruchomBranchAndBound() {
    if (macierzKosztow) {
        // Utwórz obiekt macierzy kosztów i uruchom algorytm
        MacierzKosztow macierz(macierzKosztow, liczbaMiast);
        BranchAndBound::uruchomAlgorytm(macierz, 300000);
    } else {
        cout << "Brak zaladowanej macierzy kosztow. Najpierw wczytaj lub wygeneruj graf." << endl;
    }
}

// Metoda do zapisu wyników do pliku CSV
void GrafManager::zapiszDoCSV(const string& nazwaPliku, int liczbaMiast, long long czas) {
    ofstream plik(nazwaPliku, ios::app);  // Open in append mode
    if (plik.is_open()) {
        plik << liczbaMiast << "," << czas << endl;
        plik.close();
    } else {
        cerr << "Blad otwierania pliku do zapisu." << endl;
    }
}

// Metoda do zapisu wyników do pliku CSV
void GrafManager::zapiszDoCSV2(const string& nazwaPliku, int liczbaMiast, long long czas, int procent, int czyprzerwany) {
    ofstream plik(nazwaPliku, ios::app);  // Open in append mode
    if (plik.is_open()) {
        plik << liczbaMiast << "," << czas << "," << procent << "," << czyprzerwany << endl;
        plik.close();
    } else {
        cerr << "Blad otwierania pliku do zapisu." << endl;
    }
}

// Metoda testująca dla raportu
void GrafManager::testForReportBF() {
    string nazwaPlikuCSV = "bruteforce_report.csv";

    for (int rozmiar = 5; rozmiar <= 15; ++rozmiar) {
        for (int i = 0; i < 50; ++i) {
            // Generuj nowy losowy graf o rozmiarze "rozmiar"
            vector<vector<int>> matrix = GrafGenerator::generujLosowaMacierz(rozmiar, 1, 100, false);  // Edge values from 1 to 100

            // Zwolnij istniejącą macierz kosztów, jeśli istnieje
            if (macierzKosztow) {
                for (size_t i = 0; i < liczbaMiast; ++i) {
                    delete[] macierzKosztow[i];
                }
                delete[] macierzKosztow;
            }

            liczbaMiast = rozmiar;
            macierzKosztow = new int*[liczbaMiast];
            for (size_t j = 0; j < liczbaMiast; ++j) {
                macierzKosztow[j] = new int[liczbaMiast];
                for (size_t k = 0; k < liczbaMiast; ++k) {
                    macierzKosztow[j][k] = matrix[j][k];
                }
            }

            // Uruchom algorytm i zmierz czas wykonania
            MacierzKosztow macierz(macierzKosztow, liczbaMiast);
            long long czasTrwania = BruteForce::uruchomAlgorytm(macierz);

            // Zapisz wynik do pliku CSV
            zapiszDoCSV(nazwaPlikuCSV, liczbaMiast, czasTrwania);
        }
    }
}

void GrafManager::testForReportBandB_BFS() {
    string nazwaPlikuCSV = "b&b_BFS_report_p.csv";

    for (int rozmiar = 4; rozmiar <= 30; ++rozmiar) {
        int rozmiarInner = 20;
        if (rozmiar > 12) {
            rozmiarInner = 20;
        }
        if (rozmiar > 14) {
            rozmiarInner = 20;
        }
        if (rozmiar > 16) {
            rozmiarInner = 5;
        }
        for (int i = 0; i < rozmiarInner; ++i) {
            // Generuj nowy losowy graf o rozmiarze "rozmiar"
            vector<vector<int>> matrix = GrafGenerator::generujLosowaMacierz(rozmiar, 1, 100, false);

            // Zwolnij istniejącą macierz kosztów, jeśli istnieje
            if (macierzKosztow) {
                for (size_t i = 0; i < liczbaMiast; ++i) {
                    delete[] macierzKosztow[i];
                }
                delete[] macierzKosztow;
            }

            liczbaMiast = rozmiar;
            macierzKosztow = new int*[liczbaMiast];
            for (size_t j = 0; j < liczbaMiast; ++j) {
                macierzKosztow[j] = new int[liczbaMiast];
                for (size_t k = 0; k < liczbaMiast; ++k) {
                    macierzKosztow[j][k] = matrix[j][k];
                }
            }

            // Uruchom algorytm i zmierz czas wykonania
            MacierzKosztow macierz(macierzKosztow, liczbaMiast);
            auto [result, czyPrzerwany] = BranchAndBound::uruchomAlgorytm(macierz, 300000);
            auto [czasTrwania, liczbaPrzetworzonychWezlow] = result;

            // Zapisz wynik do pliku CSV
            zapiszDoCSV2(nazwaPlikuCSV, liczbaMiast, czasTrwania, liczbaPrzetworzonychWezlow, czyPrzerwany);
        }
    }
}

void GrafManager::testForReportSymetric() {

    string nazwaPlikuCSV = "b&b_BFS_report_s_p.csv";

    for (int rozmiar = 4; rozmiar <= 30; ++rozmiar) {
        int rozmiarInner = 20;
        if (rozmiar > 12) {
            rozmiarInner = 20;
        }
        if (rozmiar > 14) {
            rozmiarInner = 20;
        }
        if (rozmiar > 16) {
            rozmiarInner = 5;
        }
        for (int i = 0; i < rozmiarInner; ++i) {
            // Generuj nowy losowy graf o rozmiarze "rozmiar"
            vector<vector<int>> matrix = GrafGenerator::generujLosowaMacierz(rozmiar, 1, 99, true);  // Edge values from 1 to 100

            // Zwolnij istniejącą macierz kosztów, jeśli istnieje
            if (macierzKosztow) {
                for (size_t i = 0; i < liczbaMiast; ++i) {
                    delete[] macierzKosztow[i];
                }
                delete[] macierzKosztow;
            }

            liczbaMiast = rozmiar;
            macierzKosztow = new int*[liczbaMiast];
            for (size_t j = 0; j < liczbaMiast; ++j) {
                macierzKosztow[j] = new int[liczbaMiast];
                for (size_t k = 0; k < liczbaMiast; ++k) {
                    macierzKosztow[j][k] = matrix[j][k];
                }
            }

            // Uruchom algorytm i zmierz czas wykonania
            MacierzKosztow macierz(macierzKosztow, liczbaMiast);
            auto [result, czyPrzerwany] = BranchAndBound::uruchomAlgorytm(macierz, 300000);
            auto [czasTrwania, liczbaPrzetworzonychWezlow] = result;

            // Zapisz wynik do pliku CSV
            zapiszDoCSV2(nazwaPlikuCSV, liczbaMiast, czasTrwania, liczbaPrzetworzonychWezlow, czyPrzerwany);
        }
    }
}
