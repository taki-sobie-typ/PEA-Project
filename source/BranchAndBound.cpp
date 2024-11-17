#include "../header/BranchAndBound.h"
#include <iostream>
#include <climits>
#include <chrono>
#include <vector>
#include <queue>

using namespace std;

long long BranchAndBound::uruchomAlgorytm(const MacierzKosztow& macierz) {
    // Pobierz macierz kosztow i liczbe miast
    int** tablicaKosztow = macierz.pobierzMacierzKosztow();
    int liczbaMiast = macierz.pobierzLiczbeMiast();

    // Zaczynamy mierzenie czasu wykonania algorytmu
    auto czasStart = chrono::high_resolution_clock::now();

    // Inicjalizacja zmiennych
    int najnizszyKoszt = INT_MAX;
    int* optymalnaSciezka = new int[liczbaMiast + 1];

    // Kolejka priorytetowa dla algorytmu B&B (min-heap oparty na koszcie)
    auto porownaj = [](const Node& a, const Node& b) {
        return a.koszt > b.koszt; // Min-heap
    };
    std::priority_queue<Node, std::vector<Node>, decltype(porownaj)> kolejka(porownaj);

    // Inicjalizacja wezla poczatkowego
    Node root;
    root.sciezka = new int[liczbaMiast + 1];
    root.sciezka[0] = 0; // Rozpoczynamy od miasta 0
    root.sciezkaCount = 1;
    root.koszt = 0;
    root.poziom = 0;

    // Dodajemy wezel poczatkowy do kolejki
    kolejka.push(root);

    // Algorytm przetwarzający wezly w kolejce
    while (!kolejka.empty()) {
        Node aktualnyWezel = kolejka.top();
        kolejka.pop();

        // Sprawdzamy, czy odwiedziliśmy już wszystkie miasta
        if (aktualnyWezel.poziom == liczbaMiast - 1) {
            // Obliczamy koszt powrotu do miasta 0
            int kosztPowrotu = tablicaKosztow[aktualnyWezel.sciezka[aktualnyWezel.sciezkaCount - 1]][0];
            if (kosztPowrotu != -1) {
                int kosztCalkowity = aktualnyWezel.koszt + kosztPowrotu;
                if (kosztCalkowity < najnizszyKoszt) {
                    najnizszyKoszt = kosztCalkowity;

                    // Aktualizujemy optymalna sciezke
                    for (int i = 0; i < aktualnyWezel.sciezkaCount; ++i) {
                        optymalnaSciezka[i] = aktualnyWezel.sciezka[i];
                        for (int i = 0; i < aktualnyWezel.sciezkaCount; ++i) {
                            std::cout << optymalnaSciezka[i] << " -> ";
                        }
                        cout << endl;
                    }
                    optymalnaSciezka[aktualnyWezel.sciezkaCount] = 0; // Powrót do miasta 0
                }
            }
            delete[] aktualnyWezel.sciezka; // Usuwamy sciezke wezla
            continue;
        }

        // Rozwój potomnych wezlow
        for (int i = 0; i < liczbaMiast; ++i) {
            if (!miastoZawarteSciezka(aktualnyWezel.sciezka, aktualnyWezel.sciezkaCount, i)) {
                // Obliczamy koszt przejścia do następnego miasta
                int kosztPrzejscia = tablicaKosztow[aktualnyWezel.sciezka[aktualnyWezel.sciezkaCount - 1]][i];
                if (kosztPrzejscia != -1) {
                    Node potomek;
                    potomek.sciezka = new int[liczbaMiast + 1];
                    // Kopiujemy sciezke z wezla aktualnego do potomka
                    std::copy(aktualnyWezel.sciezka, aktualnyWezel.sciezka + aktualnyWezel.sciezkaCount, potomek.sciezka);
                    potomek.sciezka[aktualnyWezel.sciezkaCount] = i; // Dodajemy miasto do sciezki
                    potomek.sciezkaCount = aktualnyWezel.sciezkaCount + 1;
                    potomek.poziom = aktualnyWezel.poziom + 1;

                    // Obliczamy koszt dla potomka
                    potomek.koszt = aktualnyWezel.koszt + kosztPrzejscia;

                    // Dodajemy potomka do kolejki, tylko jeśli jego koszt jest obiecujący
                    if (potomek.koszt < najnizszyKoszt) {
                        kolejka.push(potomek);
                    } else {
                        delete[] potomek.sciezka; // Usuwamy sciezke, jeśli node nie jest obiecujący
                    }
                }
            }
        }

        delete[] aktualnyWezel.sciezka; // Usuwamy sciezke po przetworzeniu wezla
    }

    // Zatrzymanie mierzenia czasu
    auto czasStop = chrono::high_resolution_clock::now();
    auto czasTrwania = chrono::duration_cast<chrono::microseconds>(czasStop - czasStart);

    // Wypisanie optymalnej trasy
    std::cout << "Najkorzystniejsza trasa: ";
    if(liczbaMiast >= 13) {
        std::cout << "0"; // Powrót do miasta początkowego
        for (int i = liczbaMiast - 1; i >= 0; --i) {
            std::cout << " -> " << optymalnaSciezka[i];
        }
        std::cout << "\n"; // Powrót do miasta początkowego
    }
    else {
        for (int i = 0; i < liczbaMiast; ++i) {
            std::cout << optymalnaSciezka[i] << " -> ";
        }
        std::cout << "0\n"; // Powrót do miasta początkowego
    }

    // Wypisanie najniższego kosztu i czasu działania algorytmu
    std::cout << "Najnizszy koszt przejscia: " << najnizszyKoszt << "\n";
    std::cout << "Czas dzialania algorytmu: " << czasTrwania.count() << " mikrosekund\n";

    delete[] optymalnaSciezka; // Usuwamy tablicę optymalnej ścieżki

    return czasTrwania.count();
}

// Funkcja pomocnicza sprawdzająca, czy miasto jest już w ścieżce
bool BranchAndBound::miastoZawarteSciezka(int* sciezka, int sciezkaCount, int miasto) {
    for (int i = 0; i < sciezkaCount; ++i) {
        if (sciezka[i] == miasto) {
            return true; // Miasto już w ścieżce
        }
    }
    return false; // Miasto nie jest w ścieżce
}
