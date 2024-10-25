#include "../header/BruteForce.h"
#include <iostream>
#include <limits>
#include <chrono>
#include <algorithm> // For std::next_permutation

using namespace std;

void BruteForce::uruchomDlaMacierzy(const MacierzKosztow& graf, int start) {
    int** drogi = graf.pobierzMacierzKosztow();
    int liczba_miast = graf.pobierzLiczbeMiast();

    auto start_time = chrono::high_resolution_clock::now(); // Start timing

    int suma_drog = INT_MAX;
    int suma_obecna;
    int* miasta = new int[liczba_miast];
    int* najlepsza_trasa = new int[liczba_miast];
    najlepsza_trasa[0] = start; // Assuming 'start' is the starting city

    for (int i = 0; i < liczba_miast; i++) {
        miasta[i] = i;
    }

    do {
        suma_obecna = 0;
        for (int i = 0; i < liczba_miast - 1; i++) {
            suma_obecna += drogi[miasta[i]][miasta[i + 1]];

            if (suma_obecna >= suma_drog) {
                break;
            }
        }
        suma_obecna += drogi[miasta[liczba_miast - 1]][miasta[0]]; // Return to start city

        if (suma_obecna < suma_drog) {
            suma_drog = suma_obecna;
            for (int i = 0; i < liczba_miast; i++) {
                najlepsza_trasa[i] = miasta[i];
            }
        }

    } while (std::next_permutation(miasta + 1, miasta + liczba_miast));

    auto stop_time = chrono::high_resolution_clock::now(); // End timing
    auto duration = chrono::duration_cast<chrono::microseconds>(stop_time - start_time);

    // Output results
    cout << "Najlepsza trasa: " << start << " -> ";
    for (int i = 1; i < liczba_miast; i++) {
        cout << najlepsza_trasa[i] << " -> ";
    }
    cout << start << endl; // Closing the loop back to the start

    cout << "Minimalny koszt: " << suma_drog << endl;
    cout << "Czas działania Przegląd zupelnego: " << duration.count() << " mikrosekund" << endl;

    delete[] miasta;
    delete[] najlepsza_trasa;
}
