#include "../header/CzytnikGrafow.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Konstruktor klasy CzytnikGrafow
// Inicjalizuje obiekt klasy, ustawiając ścieżkę bazową dla plików z danymi
CzytnikGrafow::CzytnikGrafow(string sciezkaBazowa) : sciezkaBazowa(sciezkaBazowa) {}

// Funkcja do wczytania macierzy kosztów z pliku (obsługuje różne formaty plików)
// - Parametry:
//   - nazwaPliku: nazwa pliku z danymi
//   - liczbaMiast: liczba miast (wierzchołków), która zostanie zaktualizowana
// - Zwraca wskaźnik do macierzy kosztów lub nullptr w przypadku błędu
int** CzytnikGrafow::wczytajMacierz(string nazwaPliku, size_t& liczbaMiast) {
    // Wyodrębnienie rozszerzenia pliku
    string extension = nazwaPliku.substr(nazwaPliku.find_last_of('.') + 1);

    // Wybór odpowiedniej metody wczytywania w zależności od rozszerzenia
    if (extension == "txt") {
        return wczytajZTxt(nazwaPliku, liczbaMiast);
    } else if (extension == "atsp") {
        return wczytajZAtsp(nazwaPliku, liczbaMiast);
    } else {
        // Komunikat w przypadku nieobsługiwanego formatu pliku
        cerr << "Nieobslugiwany format pliku: " << extension << endl;
        return nullptr;
    }
}

// Funkcja do wczytywania macierzy z pliku TXT
// - Parametry:
//   - nazwaPliku: nazwa pliku z danymi
//   - liczbaMiast: liczba miast, która zostanie zaktualizowana
// - Zwraca wskaźnik do macierzy kosztów lub nullptr w przypadku błędu
int** CzytnikGrafow::wczytajZTxt(string nazwaPliku, size_t& liczbaMiast) {
    // Otwieranie pliku TXT
    ifstream plik(this->sciezkaBazowa + nazwaPliku);

    // Sprawdzenie, czy plik został poprawnie otwarty
    if (plik.fail()) {
        cerr << "Nie mozna otworzyc pliku TXT!" << endl;
        return nullptr;
    }

    // Wczytanie liczby miast
    plik >> liczbaMiast;

    // Alokacja pamięci dla macierzy kosztów
    int** macierz = new int*[liczbaMiast];
    for (size_t i = 0; i < liczbaMiast; ++i) {
        macierz[i] = new int[liczbaMiast];
        for (size_t j = 0; j < liczbaMiast; ++j) {
            // Wczytanie wartości do macierzy
            plik >> macierz[i][j];
        }
    }

    // Zamknięcie pliku
    plik.close();
    return macierz;
}

// Funkcja do wczytywania macierzy z pliku ATSP
// - Parametry:
//   - nazwaPliku: nazwa pliku z danymi
//   - liczbaMiast: liczba miast, która zostanie zaktualizowana
// - Zwraca wskaźnik do macierzy kosztów lub nullptr w przypadku błędu
int** CzytnikGrafow::wczytajZAtsp(string nazwaPliku, size_t& liczbaMiast) {
    // Otwieranie pliku ATSP
    ifstream plik(this->sciezkaBazowa + nazwaPliku);

    // Sprawdzenie, czy plik został poprawnie otwarty
    if (plik.fail()) {
        cerr << "Nie mozna otworzyc pliku ATSP!" << endl;
        return nullptr;
    }

    string line;
    // Odczytanie danych nagłówkowych pliku ATSP (np. DIMENSION)
    while (getline(plik, line)) {
        if (line.find("DIMENSION:") != string::npos) {
            liczbaMiast = stoi(line.substr(line.find(":") + 1));
        } else if (line.find("EDGE_WEIGHT_SECTION") != string::npos) {
            break; // Przerwanie pętli po znalezieniu sekcji z wagami
        }
    }

    // Sprawdzenie, czy liczba miast została poprawnie wczytana
    if (liczbaMiast == 0) {
        cerr << "Nie udalo sie odczytac liczby miast z pliku ATSP!" << endl;
        return nullptr;
    }

    // Alokacja pamięci dla macierzy kosztów
    int** macierz = new int*[liczbaMiast];
    for (size_t i = 0; i < liczbaMiast; ++i) {
        macierz[i] = new int[liczbaMiast];
    }

    // Wczytywanie wartości do macierzy kosztów
    for (size_t i = 0; i < liczbaMiast; ++i) {
        for (size_t j = 0; j < liczbaMiast; ++j) {
            if (!(plik >> macierz[i][j])) {
                // Obsługa błędu wczytywania danych
                cerr << "Blad odczytu danych z sekcji macierzy w pliku ATSP!" << endl;
                return nullptr;
            }
        }
    }

    // Zamknięcie pliku
    plik.close();
    return macierz;
}
