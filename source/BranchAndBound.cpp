#include "../header/BranchAndBound.h"
#include <iostream>
#include <climits>
#include <chrono>
#include <vector>
#include <queue>

std::pair<std::pair<long long, int>, int> BranchAndBound::uruchomAlgorytm(const MacierzKosztow& macierz, long long limitCzasuMS) {
    // Pobieramy macierz kosztów i liczbę miast z obiektu MacierzKosztow
    int** tablicaKosztow = macierz.pobierzMacierzKosztow();
    int liczbaMiast = macierz.pobierzLiczbeMiast();

    // Zaczynamy mierzenie czasu wykonania algorytmu
    auto czasStart = std::chrono::high_resolution_clock::now();

    // Inicjalizacja zmiennych
    int najnizszyKoszt = INT_MAX; // Zmienna do przechowywania najniższego kosztu
    int* optymalnaSciezka = new int[liczbaMiast + 1]; // Tablica do przechowywania optymalnej ścieżki
    int liczbaPrzetworzonychWezlow = 0; // Licznik przetworzonych węzłów
    int czyPrzerwany = 0; // Flaga przerwania (0 - nie, 1 - tak)

    // Kolejka priorytetowa (min-heap) dla algorytmu B&B, porównujemy węzły na podstawie kosztu
    auto porownaj = [](const Node& a, const Node& b) {
        return a.koszt > b.koszt; // Min-heap: węzeł o mniejszym koszcie będzie na początku
    };
    std::priority_queue<Node, std::vector<Node>, decltype(porownaj)> kolejka(porownaj);

    // Inicjalizacja węzła początkowego (rozpoczynamy od miasta 0)
    Node root;
    root.sciezka = new int[liczbaMiast + 1]; // Tworzymy tablicę dla ścieżki
    root.sciezka[0] = 0; // Rozpoczynamy od miasta 0
    root.sciezkaCount = 1; // Liczba miast w ścieżce na początku to 1 (miasto 0)
    root.koszt = 0; // Początkowy koszt to 0
    root.poziom = 0; // Początkowy poziom to 0 (jesteśmy w mieście 0)

    // Dodajemy węzeł początkowy do kolejki
    kolejka.push(root);

    // Algorytm przetwarzający węzły w kolejce
    while (!kolejka.empty()) {
        auto czasTeraz = std::chrono::high_resolution_clock::now();
        long long czasPracy = std::chrono::duration_cast<std::chrono::milliseconds>(czasTeraz - czasStart).count();

        // Przerwanie algorytmu, jeśli czas pracy przekroczył limit
        if (czasPracy > limitCzasuMS) {
            std::cout << "Limit czasu (" << limitCzasuMS << " ms) przekroczony. Algorytm zostal przerwany.\n";
            czyPrzerwany = 1; // Ustawiamy flagę przerwania
            break;
        }

        // Pobieramy węzeł z początku kolejki
        Node aktualnyWezel = kolejka.top();
        kolejka.pop();
        liczbaPrzetworzonychWezlow++; // Zwiększamy licznik przetworzonych węzłów

        // Sprawdzamy, czy odwiedziliśmy już wszystkie miasta
        if (aktualnyWezel.poziom == liczbaMiast - 1) {
            // Jeśli tak, obliczamy koszt powrotu do miasta 0
            int kosztPowrotu = tablicaKosztow[aktualnyWezel.sciezka[aktualnyWezel.sciezkaCount - 1]][0];
            if (kosztPowrotu != -1) { // Jeżeli koszt powrotu nie jest -1 (czyli istnieje połączenie)
                int kosztCalkowity = aktualnyWezel.koszt + kosztPowrotu; // Całkowity koszt ścieżki
                if (kosztCalkowity < najnizszyKoszt) { // Jeśli koszt jest mniejszy niż dotychczasowy najniższy koszt
                    najnizszyKoszt = kosztCalkowity; // Zaktualizuj najniższy koszt

                    // Aktualizujemy optymalną ścieżkę
                    for (int i = 0; i < aktualnyWezel.sciezkaCount; ++i) {
                        optymalnaSciezka[i] = aktualnyWezel.sciezka[i];
                    }
                    optymalnaSciezka[aktualnyWezel.sciezkaCount] = 0; // Powrót do miasta 0
                }
            }
            delete[] aktualnyWezel.sciezka; // Usuwamy ścieżkę węzła po jej przetworzeniu
            continue;
        }

        // Rozwój potomnych węzłów
        for (int i = 0; i < liczbaMiast; ++i) {
            // Sprawdzamy, czy dane miasto nie zostało już odwiedzone w ścieżce
            if (!miastoZawarteSciezka(aktualnyWezel.sciezka, aktualnyWezel.sciezkaCount, i)) {
                // Obliczamy koszt przejścia do następnego miasta
                int kosztPrzejscia = tablicaKosztow[aktualnyWezel.sciezka[aktualnyWezel.sciezkaCount - 1]][i];
                if (kosztPrzejscia != -1) { // Jeżeli koszt przejścia nie jest -1 (czyli istnieje połączenie)
                    Node potomek;
                    potomek.sciezka = new int[liczbaMiast + 1]; // Tworzymy tablicę dla ścieżki potomka
                    // Kopiujemy ścieżkę z węzła aktualnego do potomka
                    std::copy(aktualnyWezel.sciezka, aktualnyWezel.sciezka + aktualnyWezel.sciezkaCount, potomek.sciezka);
                    potomek.sciezka[aktualnyWezel.sciezkaCount] = i; // Dodajemy miasto do ścieżki potomka
                    potomek.sciezkaCount = aktualnyWezel.sciezkaCount + 1; // Zwiększamy liczbę miast w ścieżce
                    potomek.poziom = aktualnyWezel.poziom + 1; // Zwiększamy poziom (odwiedziliśmy kolejne miasto)

                    // Obliczamy koszt dla potomka
                    potomek.koszt = aktualnyWezel.koszt + kosztPrzejscia;

                    // Dodajemy potomka do kolejki, tylko jeśli jego koszt jest obiecujący
                    if (potomek.koszt < najnizszyKoszt) {
                        kolejka.push(potomek); // Dodajemy do kolejki
                    } else {
                        delete[] potomek.sciezka; // Usuwamy ścieżkę, jeśli węzeł nie jest obiecujący
                    }
                }
            }
        }

        delete[] aktualnyWezel.sciezka; // Usuwamy ścieżkę węzła po przetworzeniu
    }

    // Zatrzymanie mierzenia czasu
    auto czasStop = std::chrono::high_resolution_clock::now();
    auto czasTrwania = std::chrono::duration_cast<std::chrono::microseconds>(czasStop - czasStart);

    // Wypisanie wyników
    if(liczbaMiast >= 13) {
        std::cout << "Najkorzystniejsza trasa: ";
        std::cout << "0"; // Powrót do miasta początkowego
        for (int i = liczbaMiast - 1; i >= 0; --i) {
            std::cout << " -> " << optymalnaSciezka[i];
        }
        std::cout << "\n"; // Powrót do miasta początkowego
    }
    else {
        std::cout << "Najkorzystniejsza trasa: ";
        for (int i = 0; i < liczbaMiast; ++i) {
            std::cout << optymalnaSciezka[i] << " -> ";
        }
        std::cout << "0\n"; // Powrót do miasta początkowego
    }

    std::cout << "Najnizszy koszt przejscia: " << najnizszyKoszt << "\n";
    std::cout << "Czas dzialania algorytmu: " << czasTrwania.count() << " mikrosekund\n";
    std::cout << "Liczba przetworzonych wezlow: " << liczbaPrzetworzonychWezlow << "\n";

    delete[] optymalnaSciezka; // Usuwamy tablicę optymalnej ścieżki

    return {{czasTrwania.count(), liczbaPrzetworzonychWezlow}, czyPrzerwany};
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
