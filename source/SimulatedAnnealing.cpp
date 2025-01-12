#include "../header/SimulatedAnnealing.h"

// Zdefiniowanie statycznych wektorów
// Przechowują dane potrzebne do generowania wykresów i finalnego rozwiązania
vector<int> SimulatedAnnealing::wykresBestLengths = {};              // Przechowuje najlepsze długości rozwiązania
vector<double> SimulatedAnnealing::wykresCurrentTemperature = {};    // Przechowuje wartości aktualnej temperatury
vector<long long> SimulatedAnnealing::wykresCzasyOfBestLengths = {}; // Przechowuje czasy uzyskania najlepszych rozwiązań
vector<int> SimulatedAnnealing::finalPath = {};                      // Przechowuje końcową najlepszą ścieżkę

// Funkcja uruchamiająca algorytm symulowanego wyżarzania
// Parametry:
// - macierz: obiekt MacierzKosztow zawierający dane o kosztach przejść między miastami
// - coolingFactor: współczynnik chłodzenia
// - maxTime: maksymalny czas działania algorytmu (w milisekundach)
// - coolingType: typ funkcji chłodzenia (1, 2, 3)
// - testing: flaga, czy algorytm jest uruchamiany w trybie testowym
// Zwraca: struktura zawierająca czas znalezienia najlepszego rozwiązania, jego długość, temperaturę końcową oraz liczbę miast
std::pair<std::pair<std::pair<long long, long long>, int>, std::pair<double, int>> SimulatedAnnealing::start(
    const MacierzKosztow& macierz, double coolingFactor, int maxTime, int coolingType, bool testing) {

    // Inicjalizacja generatora liczb losowych
    srand(static_cast<unsigned>(time(nullptr)));  // Ustawienie ziarna dla rand()
    random_device rd;                             // Urządzenie do generowania losowości
    mt19937 gen(rd());                            // Generator liczb pseudolosowych
    uniform_real_distribution<> dis(0, 1);        // Rozkład równomierny w przedziale [0, 1]

    // Czyszczenie wektorów przed rozpoczęciem algorytmu
    wykresBestLengths.clear();
    wykresCurrentTemperature.clear();
    wykresCzasyOfBestLengths.clear();
    finalPath.clear();

    // Pobranie danych z obiektu MacierzKosztow
    int** matrix = macierz.pobierzMacierzKosztow();  // Pobranie macierzy kosztów
    int matrixSize = macierz.pobierzLiczbeMiast();   // Pobranie liczby miast

    // Dynamiczna alokacja pamięci dla ścieżek
    int* bestPath = new int[matrixSize + 1];   // Najlepsza ścieżka
    int* currentPath = new int[matrixSize + 1]; // Bieżąca ścieżka
    int* testPath = new int[matrixSize + 1];    // Ścieżka testowa

    int bestLen, currentLen, testLen;  // Długości ścieżek

    // Uzyskanie początkowego rozwiązania za pomocą algorytmu zachłannego
    greedyAlg(matrix, matrixSize, bestPath, bestLen);

    // Skopiowanie początkowego rozwiązania do bieżącej ścieżki
    std::copy(bestPath, bestPath + matrixSize + 1, currentPath);
    currentLen = bestLen;  // Przypisanie długości początkowej

    // Obliczenie początkowej temperatury
    double beginningTemperature = calcBeginTemperature(matrix, matrixSize, bestPath, bestLen, gen, dis);
    double currentTemperature = beginningTemperature;

    // Liczba iteracji (kombinacji par miast)
    int eraLen = matrixSize * (matrixSize - 1) / 2;
    //eraLen = eraLen * 2;
    int eraNumber = 0;  // Licznik epok

    // Rozpoczęcie pomiaru czasu
    auto startTime = std::chrono::high_resolution_clock::now();
    long long timeOfBestSolution = 0;  // Czas uzyskania najlepszego rozwiązania

    // Główna pętla algorytmu symulowanego wyżarzania
    do {
        for (int era = 0; era < eraLen; ++era) {
            // Skopiowanie bieżącej ścieżki do testowej
            std::copy(currentPath, currentPath + matrixSize + 1, testPath);

            // Zamiana dwóch losowych punktów w ścieżce
            swapPoints(testPath, matrixSize, gen, dis);

            // Obliczenie długości nowej ścieżki
            calcLen(matrix, matrixSize, testPath, testLen);

            // Obliczenie różnicy kosztu ścieżki
            int delta = testLen - currentLen;

            // Generowanie losowej wartości z zakresu [0, 1]
            double randomValue = dis(gen);

            // Obliczenie prawdopodobieństwa zaakceptowania gorszego rozwiązania
            double probability = exp(-delta / currentTemperature);

            // Aktualizacja rozwiązania, jeśli jest lepsze lub spełnia warunek probabilistyczny
            if (delta <= 0 || randomValue < probability) {
                currentLen = testLen;
                std::copy(testPath, testPath + matrixSize + 1, currentPath);

                // Aktualizacja najlepszego rozwiązania, jeśli jest lepsze
                if (currentLen < bestLen) {
                    bestLen = currentLen;
                    std::copy(currentPath, currentPath + matrixSize + 1, bestPath);

                    // Zapisanie czasu najlepszego rozwiązania
                    timeOfBestSolution = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::high_resolution_clock::now() - startTime).count();

                    // Dodanie danych do wykresów
                    wykresBestLengths.push_back(bestLen);
                    wykresCurrentTemperature.push_back(currentTemperature);
                    wykresCzasyOfBestLengths.push_back(timeOfBestSolution);
                }
            }
        }

        // Aktualizacja liczby epok
        ++eraNumber;

        // Obliczenie nowej temperatury w zależności od typu chłodzenia
        currentTemperature = calcNewTemperature(currentTemperature, eraNumber, coolingType, coolingFactor);

    } while (currentTemperature >= 0.01 &&
             std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count() <= maxTime);

    // Zakończenie pomiaru czasu
    auto endTime = std::chrono::high_resolution_clock::now();
    long long duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

    // Obliczenie wartości exp(-1/Tk)
    double expValue = exp(-1.0 / currentTemperature);

    if (!testing) {
        // Wyświetlenie wyników w trybie normalnym
        std::cout << "Najkorzystniejsza trasa: ";
        for (int i = 0; i < matrixSize; ++i) {
            std::cout << bestPath[i] << " -> ";
        }
        std::cout << bestPath[matrixSize] << std::endl;

        std::cout << "Najnizszy koszt przejscia: " << bestLen << "\n";
        std::cout << "Czas dzialania algorytmu: " << duration << " mikrosekund\n";
        std::cout << "Liczba Er: " << eraNumber << "\n";
        std::cout << "Wartosc exp(-1/Tk) = " << expValue << "\n";
        std::cout << "Temperatura Tk = " << currentTemperature << "\n";
    }

    // Zapisanie najlepszego rozwiązania do finalPath
    finalPath.clear();
    finalPath.reserve(matrixSize + 1);
    for (int i = 0; i < matrixSize + 1; ++i) {
        finalPath.push_back(bestPath[i]);
    }

    // Zwolnienie pamięci dynamicznej
    delete[] bestPath;
    delete[] currentPath;
    delete[] testPath;

    // Zwrócenie danych o czasie rozwiązania, długości trasy i temperaturze końcowej
    return {{{timeOfBestSolution, duration}, bestLen}, {currentTemperature, matrixSize}};
}

// Funkcja realizująca algorytm zachłanny.
// Algorytm ten służy do znalezienia wstępnego rozwiązania problemu TSP (problem komiwojażera).
void SimulatedAnnealing::greedyAlg(int **matrix, int matrixSize, int *bestPath, int &bestLen) {
    // Tablica do przechowywania tymczasowej ścieżki
    int *tmpPath = new int[matrixSize + 1];
    // Tablica do śledzenia odwiedzonych miast
    bool *visited = new bool[matrixSize];

    // Inicjalizacja najlepszej długości jako bardzo dużej wartości
    bestLen = INT_MAX;

    // Sprawdzamy każde miasto jako możliwe miasto startowe
    for (int startCity = 0; startCity < matrixSize; ++startCity) {
        int currentCity = startCity; // Aktualne miasto
        tmpPath[0] = currentCity; // Ustawienie pierwszego miasta w ścieżce
        int pathLen = 0; // Aktualna długość ścieżki
        int pathSize = 1; // Liczba miast w bieżącej ścieżce

        // Inicjalizacja tablicy odwiedzonych miast
        std::fill(visited, visited + matrixSize, false);
        visited[currentCity] = true; // Oznaczenie miasta startowego jako odwiedzonego

        // Algorytm zachłanny: wybieramy najbliższe nieodwiedzone miasto
        while (pathSize < matrixSize) {
            int minLen = INT_MAX; // Minimalny koszt przejścia
            int nextCity = -1; // Kolejne miasto do odwiedzenia

            // Szukamy najbliższego miasta
            for (int i = 0; i < matrixSize; ++i) {
                if (!visited[i] && matrix[currentCity][i] < minLen) {
                    nextCity = i;
                    minLen = matrix[currentCity][i];
                }
            }

            // Aktualizujemy ścieżkę i oznaczamy miasto jako odwiedzone
            tmpPath[pathSize++] = nextCity;
            pathLen += minLen;
            currentCity = nextCity;
            visited[nextCity] = true;
        }

        // Zamykamy cykl, dodając koszt powrotu do miasta startowego
        pathLen += matrix[currentCity][startCity];
        tmpPath[pathSize] = startCity;

        // Jeśli znalezione rozwiązanie jest lepsze, zapisujemy je jako najlepsze
        if (pathLen < bestLen) {
            bestLen = pathLen;
            std::copy(tmpPath, tmpPath + matrixSize + 1, bestPath);
        }
    }

    // Zwolnienie pamięci
    delete[] tmpPath;
    delete[] visited;
}

// Funkcja obliczająca długość podanej ścieżki.
void SimulatedAnnealing::calcLen(int** matrix, int matrixSize, int* path, int& length) {
    length = 0;  // Inicjalizacja długości ścieżki
    for (int i = 0; i < matrixSize; ++i) {
        length += matrix[path[i]][path[i + 1]];  // Sumowanie kosztów przejść między miastami
    }
}

// Funkcja obliczająca nową temperaturę w algorytmie symulowanego wyżarzania.
// Parametry:
// - currentTemperature: aktualna temperatura,
// - eraNumber: numer iteracji,
// - coolingType: typ chłodzenia (1: geometryczne, 2: logarytmiczne, 3: wykładnicze),
// - coolingFactor: współczynnik chłodzenia.
double SimulatedAnnealing::calcNewTemperature(double currentTemperature, int eraNumber, int coolingType, double coolingFactor) {
    switch (coolingType) {
        case 1:
            return currentTemperature * coolingFactor;  // Chłodzenie geometryczne
        case 2:
            return currentTemperature / (1 + coolingFactor * log(eraNumber + 1));  // Chłodzenie logarytmiczne
        case 3:
            return pow(coolingFactor, eraNumber) * currentTemperature;  // Chłodzenie wykładnicze
        default:
            return currentTemperature;  // Domyślny przypadek: brak zmiany temperatury
    }
}

// Funkcja obliczająca początkową temperaturę algorytmu na podstawie prób.
// Wykorzystuje losowe zamiany w ścieżce, aby oszacować różnicę między minimalnym i maksymalnym kosztem.
int SimulatedAnnealing::calcBeginTemperature(int **matrix, int matrixSize, int *path, int pathLen, std::mt19937 &gen,
                         std::uniform_real_distribution<> &dis) {
    int minLen = INT_MAX;
    int maxLen = 0;
    int testLen = pathLen;

    // Liczba prób zależy od rozmiaru macierzy
    int samples = std::max(100, matrixSize * 10);
    //double scalingFactor = log(matrixSize) / 2.0; // Skalowanie na podstawie rozmiaru macierzy
    double scalingFactor = log(matrixSize) * 2.0; // Skalowanie na podstawie rozmiaru macierzy

    // Wykonujemy określoną liczbę prób
    for (int i = 0; i < samples; ++i) {
        swapPoints(path, matrixSize, gen, dis); // Losowa zamiana punktów w ścieżce
        calcLen(matrix, matrixSize, path, testLen);
        minLen = std::min(minLen, testLen); // Aktualizacja minimalnej długości
        maxLen = std::max(maxLen, testLen); // Aktualizacja maksymalnej długości
    }

    // Obliczamy temperaturę początkową jako różnicę kosztów skalowaną współczynnikiem
    return (maxLen - minLen) * scalingFactor;
}

// Funkcja do zamiany dwóch losowych punktów w ścieżce.
void SimulatedAnnealing::swapPoints(int* path, int matrixSize, std::mt19937& gen, std::uniform_real_distribution<>& dis) {
    // Generujemy dwa różne indeksy
    int index1 = static_cast<int>(dis(gen) * matrixSize);
    int index2 = static_cast<int>(dis(gen) * matrixSize);

    // Upewniamy się, że indeksy są różne
    while (index1 == index2) {
        index2 = static_cast<int>(dis(gen) * matrixSize);
    }

    // Zamieniamy miejscami dwa punkty
    std::swap(path[index1], path[index2]);

    // Jeśli zamiana dotyczy miasta startowego, aktualizujemy cykl
    if (index1 == 0 || index2 == 0) {
        path[matrixSize] = path[0];  // Cykl zamknięty
    }
}