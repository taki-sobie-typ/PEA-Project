#include "../header/CzytnikGrafow.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Konstruktor klasy CzytnikGrafow, który ustawia ścieżkę bazową dla plików z danymi
CzytnikGrafow::CzytnikGrafow(string sciezkaBazowa) : sciezkaBazowa(sciezkaBazowa) {}

// Funkcja do wczytania macierzy kosztów z pliku (TXT, XML, ATSP)
int** CzytnikGrafow::wczytajMacierz(string nazwaPliku, size_t& liczbaMiast) {
    string extension = nazwaPliku.substr(nazwaPliku.find_last_of('.') + 1);

    if (extension == "txt") {
        return wczytajZTxt(nazwaPliku, liczbaMiast);
    } else if (extension == "atsp") {
        return wczytajZAtsp(nazwaPliku, liczbaMiast);
    } else {
        cerr << "Nieobslugiwany format pliku: " << extension << endl;
        return nullptr;
    }
}

// Funkcja do wczytywania macierzy z pliku TXT
int** CzytnikGrafow::wczytajZTxt(string nazwaPliku, size_t& liczbaMiast) {
    ifstream plik(this->sciezkaBazowa + nazwaPliku);

    if (plik.fail()) {
        cerr << "Nie mozna otworzyc pliku TXT!" << endl;
        return nullptr;
    }

    plik >> liczbaMiast;

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

// Funkcja do wczytywania macierzy z pliku ATSP
int** CzytnikGrafow::wczytajZAtsp(string nazwaPliku, size_t& liczbaMiast) {
    ifstream plik(this->sciezkaBazowa + nazwaPliku);

    if (plik.fail()) {
        cerr << "Nie mozna otworzyc pliku ATSP!" << endl;
        return nullptr;
    }

    string line;
    while (getline(plik, line)) {
        if (line.find("DIMENSION:") != string::npos) {
            liczbaMiast = stoi(line.substr(line.find(":") + 1));
        } else if (line.find("EDGE_WEIGHT_SECTION") != string::npos) {
            break;
        }
    }

    if (liczbaMiast == 0) {
        cerr << "Nie udalo sie odczytac liczby miast z pliku ATSP!" << endl;
        return nullptr;
    }

    int** macierz = new int*[liczbaMiast];
    for (size_t i = 0; i < liczbaMiast; ++i) {
        macierz[i] = new int[liczbaMiast];
    }

    for (size_t i = 0; i < liczbaMiast; ++i) {
        for (size_t j = 0; j < liczbaMiast; ++j) {
            if (!(plik >> macierz[i][j])) {
                cerr << "Blad odczytu danych z sekcji macierzy w pliku ATSP!" << endl;
                return nullptr;
            }
        }
    }

    plik.close();
    return macierz;
}
