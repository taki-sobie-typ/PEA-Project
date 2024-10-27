#include "../header/GrafGenerator.h"
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// Funkcja generująca losową macierz kosztów (macierz sąsiedztwa) dla grafu
vector<vector<int>> GrafGenerator::generujLosowaMacierz(int rozmiar, int minWartosc, int maxWartosc) {
    // Tworzenie dwuwymiarowego wektora o rozmiarze `rozmiar x rozmiar`
    vector<vector<int>> macierz(rozmiar, vector<int>(rozmiar));

    // Ustawienie ziarna generatora liczb losowych na aktualny czas
    srand(time(NULL));

    // Wypełnianie macierzy losowymi wartościami
    for (int i = 0; i < rozmiar; ++i) {
        for (int j = 0; j < rozmiar; ++j) {
            if (i == j) {
                // Odległość do samego siebie ustawiamy na -1 (lub można ustawić na 0, jeśli to bardziej pasuje)
                macierz[i][j] = -1;
            } else {
                // Generowanie losowej wartości w zakresie od `minWartosc` do `maxWartosc`
                macierz[i][j] = rand() % (maxWartosc - minWartosc + 1) + minWartosc;
            }
        }
    }
    // Zwrócenie wygenerowanej macierzy
    return macierz;
}
