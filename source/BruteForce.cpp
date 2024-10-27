#include "../header/BruteForce.h"
#include <iostream>
#include <climits> // Dla INT_MAX
#include <chrono>  // Dla pomiaru czasu
#include <algorithm> // Do generowania permutacji

using namespace std;

// Funkcja uruchamiająca algorytm pełnego przeglądu (brute force) na podanej macierzy kosztów
void BruteForce::uruchomAlgorytm(const MacierzKosztow& macierz, int miastoPoczatkowe) {
    // Pobieranie tablicy kosztów oraz liczby miast z przekazanego obiektu grafu
    int** tablicaKosztow = macierz.pobierzMacierzKosztow();
    int liczbaMiast = macierz.pobierzLiczbeMiast();

    // Rozpocznij mierzenie czasu działania algorytmu
    auto czasStart = chrono::high_resolution_clock::now();

    int najnizszyKoszt = INT_MAX; // Przechowuje minimalny znaleziony koszt
    int aktualnyKoszt; // Zmienna do obliczania bieżącego kosztu trasy
    int* indeksyMiast = new int[liczbaMiast]; // Tablica do przechowywania indeksów miast
    int* optymalnaSciezka = new int[liczbaMiast]; // Tablica do przechowywania najlepszej trasy
    optymalnaSciezka[0] = miastoPoczatkowe; // Ustaw pierwszy punkt na miasto początkowe

    // Przygotuj tablicę indeksów miast do generowania permutacji
    for (int k = 0; k < liczbaMiast; k++) {
        indeksyMiast[k] = k;
    }

    // Przeglądaj wszystkie możliwe permutacje miast, z wyłączeniem punktu startowego
    do {
        aktualnyKoszt = 0; // Zresetuj koszt dla bieżącej permutacji
        // Oblicz koszt przejścia między miastami w danej kolejności
        for (int x = 0; x < liczbaMiast - 1; x++) {
            aktualnyKoszt += tablicaKosztow[indeksyMiast[x]][indeksyMiast[x + 1]];

            // Jeżeli aktualny koszt przewyższa najniższy znaleziony koszt, zakończ pętlę
            if (aktualnyKoszt >= najnizszyKoszt) {
                break;
            }
        }
        // Uwzględnij koszt powrotu do miasta początkowego
        aktualnyKoszt += tablicaKosztow[indeksyMiast[liczbaMiast - 1]][indeksyMiast[0]];

        // Jeżeli bieżący koszt jest mniejszy od najmniejszego zapisanego, zapisz nowy minimalny koszt
        if (aktualnyKoszt < najnizszyKoszt) {
            najnizszyKoszt = aktualnyKoszt;
            for (int y = 0; y < liczbaMiast; y++) {
                optymalnaSciezka[y] = indeksyMiast[y];
            }
        }

    } while (std::next_permutation(indeksyMiast + 1, indeksyMiast + liczbaMiast)); // Generowanie następnych permutacji

    // Zakończ mierzenie czasu działania algorytmu
    auto czasStop = chrono::high_resolution_clock::now();
    auto czasTrwania = chrono::duration_cast<chrono::microseconds>(czasStop - czasStart);

    // Wyświetlanie wyników
    cout << "Najkorzystniejsza trasa: " << miastoPoczatkowe << " -> ";
    for (int z = 1; z < liczbaMiast; z++) {
        cout << optymalnaSciezka[z] << " -> ";
    }
    cout << miastoPoczatkowe << endl; // Zamyka cykl, wracając do miasta początkowego

    cout << "Najnizszy koszt przejscia: " << najnizszyKoszt << endl;
    cout << "Czas dzialania algorytmu pelnego przegladu: " << czasTrwania.count() << " mikrosekund" << endl;

    // Zwolnij pamięć zajmowaną przez dynamiczne tablice
    delete[] indeksyMiast;
    delete[] optymalnaSciezka;
}
