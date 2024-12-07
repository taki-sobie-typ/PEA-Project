#include "../header/SimulatedAnnealing.h"

// Zdefiniowanie statycznych wektorów
vector<int> SimulatedAnnealing::wykresBestLengths = {};              // Przechowuje najlepsze długości rozwiązania
vector<double> SimulatedAnnealing::wykresCurrentTemperature = {};    // Przechowuje wartości aktualnej temperatury
vector<long long> SimulatedAnnealing::wykresCzasyOfBestLengths = {}; // Przechowuje czasy uzyskania najlepszych rozwiązań
vector<int> SimulatedAnnealing::finalPath = {};

// Funkcja uruchamiająca algorytm symulowanego wyżarzania
std::pair<std::pair<std::pair<long long, long long>, int>,std::pair<double, int>> SimulatedAnnealing::start(const MacierzKosztow& macierz, double coolingFactor, int maxTime, int coolingType) {
    // Inicjalizacja generatora liczb losowych
    srand(static_cast<unsigned>(time(nullptr)));

    // Czyszczenie wektorów przed rozpoczęciem algorytmu
    wykresBestLengths.clear();
    wykresCurrentTemperature.clear();
    wykresCzasyOfBestLengths.clear();
    finalPath.clear();

    // Pobieramy dane z obiektu MacierzKosztow
    int** matrix = macierz.pobierzMacierzKosztow();  // Pobranie macierzy kosztów
    int matrixSize = macierz.pobierzLiczbeMiast();   // Pobranie liczby miast

    // Dynamiczna alokacja pamięci dla różnych ścieżek
    int* bestPath = new int[matrixSize + 1];   // Najlepsza ścieżka
    int* currentPath = new int[matrixSize + 1]; // Ścieżka aktualna
    int* testPath = new int[matrixSize + 1];    // Ścieżka testowa

    int bestLen, currentLen, testLen;  // Zmienne przechowujące długości ścieżek

    // Wykonanie algorytmu zachłannego w celu uzyskania początkowego rozwiązania
    greedyAlg(matrix, matrixSize, bestPath, bestLen);

    // Skopiowanie rozwiązania z algorytmu zachłannego do ścieżki bieżącej
    std::copy(bestPath, bestPath + matrixSize + 1, currentPath);
    currentLen = bestLen;  // Przypisanie długości początkowej ścieżki

    // Obliczenie początkowej temperatury
    double beginningTemperature = calcBeginTemperature(matrix, matrixSize, bestPath, bestLen);
    double currentTemperature = beginningTemperature;

    // Oblicza łączną liczbę możliwych par miast
    int eraLen = matrixSize * (matrixSize - 1) / 2; // Liczba kombinacji par miast
    int eraNumber = 0;  // Liczba epok (kroków w algorytmie)

    // Rozpoczęcie pomiaru czasu
    auto startTime = std::chrono::high_resolution_clock::now();
    long long timeOfBestSolution = 0;

    // Główna pętla algorytmu symulowanego wyżarzania
    do {
        for (int era = 0; era < eraLen; ++era) {
            // Kopiowanie bieżącej ścieżki do testowej
            std::copy(currentPath, currentPath + matrixSize + 1, testPath);

            // Zamiana dwóch punktów w ścieżce (losowo)
            swapPoints(testPath, matrixSize);

            // Obliczenie długości nowej ścieżki
            calcLen(matrix, matrixSize, testPath, testLen);

            // Obliczenie różnicy długości ścieżek
            int delta = testLen - currentLen;

            // Generowanie losowej liczby z przedziału [0, 1]
            double randomValue = static_cast<double>(rand()) / RAND_MAX;

            // Obliczenie prawdopodobieństwa zaakceptowania gorszego rozwiązania
            double probability = exp(-delta / currentTemperature);

            // Akceptowanie nowego rozwiązania, jeśli jest lepsze lub spełnia warunek prawdopodobieństwa
            if(delta <= 0 || randomValue < probability){
                currentLen = testLen;  // Aktualizacja długości ścieżki
                std::copy(testPath, testPath + matrixSize + 1, currentPath);

                // Jeżeli nowe rozwiązanie jest lepsze, zapisujemy je
                if (currentLen < bestLen) {
                    bestLen = currentLen;
                    std::copy(currentPath, currentPath + matrixSize + 1, bestPath);
                    // Zapisanie czasu, w którym uzyskano najlepsze rozwiązanie
                    timeOfBestSolution = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count();

                    // Dodanie wyników do wykresów
                    wykresBestLengths.push_back(bestLen);
                    wykresCurrentTemperature.push_back(currentTemperature);
                    wykresCzasyOfBestLengths.push_back(timeOfBestSolution);
                }
            }
        }

        ++eraNumber;  // Zwiększenie liczby epok
        // Obliczenie nowej temperatury
        currentTemperature = calcNewTemperature(currentTemperature, eraNumber, coolingType, coolingFactor);

    } while (currentTemperature >= 0.01 && std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count() <= maxTime);

    // Zakończenie pomiaru czasu
    auto endTime = std::chrono::high_resolution_clock::now();
    long long duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

    // Wyświetlenie wyników
    std::cout << "Najkorzystniejsza trasa: ";

    for (int i = 0; i < matrixSize; ++i) {
        std::cout << bestPath[i] << " -> ";  // Wyświetlanie kolejnych miast
    }
    std::cout << bestPath[matrixSize] << std::endl;  // Wyświetlanie ostatniego miasta (cykl)

    std::cout << "Najnizszy koszt przejscia: " << bestLen << "\n";  // Koszt najlepszej trasy
    std::cout << "Czas dzialania algorytmu: " << duration << " mikrosekund\n";  // Czas trwania algorytmu
    std::cout << "Liczba Er:" << eraNumber << "\n";  // Liczba epok

    // Obliczenie i wyświetlenie exp(-1/Tk) oraz Tk
    double expValue = exp(-1.0 / currentTemperature);
    std::cout << "Wartosc exp(-1/Tk) = " << expValue << "\n";  // Wyświetlenie wartości exp(-1/Tk)
    std::cout << "Temperatura Tk = " << currentTemperature << "\n";  // Wyświetlenie końcowej temperatury

    // Zapisanie najlepszej ścieżki do finalPath
    finalPath.clear();
    finalPath.reserve(matrixSize + 1);
    for (int i = 0; i < matrixSize + 1; ++i) {
        finalPath.push_back(bestPath[i]);
    }

    // Zwalnianie pamięci
    delete[] bestPath;
    delete[] currentPath;
    delete[] testPath;

    // Zwracamy czas uzyskania najlepszego rozwiązania i liczbę epok
    return {{{timeOfBestSolution, duration}, bestLen}, {beginningTemperature, matrixSize}};
}

// Funkcja realizująca algorytm zachłanny
void SimulatedAnnealing::greedyAlg(int** matrix, int matrixSize, int* bestPath, int& bestLen) {
    int* tmpPath = new int[matrixSize + 1];  // Tymczasowa ścieżka do przechowywania rozwiązania
    bool *visited = new bool[matrixSize];  // Tablica do śledzenia odwiedzonych miast

    bestLen = INT_MAX;  // Inicjalizacja najlepszej długości jako bardzo dużej

    // Sprawdzamy wszystkie możliwe miasta startowe
    for (int startCity = 0; startCity < matrixSize; ++startCity) {
        int currentCity = startCity;
        tmpPath[0] = currentCity;  // Ustawiamy miasto początkowe
        int pathLen = 0;           // Długość ścieżki
        int pathSize = 1;          // Licznik miast w ścieżce

        // Inicjalizacja tablicy odwiedzonych miast
        for (int i = 0; i < matrixSize; ++i) {
            visited[i] = false;
        }

        visited[currentCity] = true;  // Oznaczamy miasto początkowe jako odwiedzone

        // Pętla do wyznaczenia trasy (zachłannie)
        while (pathSize < matrixSize) {
            int minLen = INT_MAX;  // Inicjalizujemy minimalną długość na dużą wartość
            int nextCity = -1;     // Inicjalizujemy zmienną dla następnego miasta

            // Wybieramy miasto, które jest najbliższe (najmniejszy koszt przejścia)
            for (int i = 0; i < matrixSize; ++i) {
                if (!visited[i] && matrix[currentCity][i] < minLen) {
                    nextCity = i;
                    minLen = matrix[currentCity][i];
                }
            }

            tmpPath[pathSize++] = nextCity;  // Dodajemy miasto do ścieżki
            pathLen += minLen;  // Dodajemy koszt przejścia do całkowitej długości
            currentCity = nextCity;
            visited[nextCity] = true;  // Oznaczamy miasto jako odwiedzone
        }

        // Zamykamy cykl, wracając do miasta początkowego
        pathLen += matrix[currentCity][startCity];
        tmpPath[pathSize] = startCity;

        // Jeżeli znaleźliśmy lepsze rozwiązanie, zapisujemy je
        if (pathLen < bestLen) {
            bestLen = pathLen;
            std::copy(tmpPath, tmpPath + matrixSize + 1, bestPath);
        }
    }

    // Zwalnianie pamięci
    delete[] tmpPath;
    delete[] visited;
}

// Funkcja obliczająca długość ścieżki
void SimulatedAnnealing::calcLen(int** matrix, int matrixSize, int* path, int& length) {
    length = 0;
    for (int i = 0; i < matrixSize; ++i) {
        length += matrix[path[i]][path[i + 1]];  // Sumowanie kosztów przejść między kolejnymi miastami
    }
}

// Funkcja obliczająca nową temperaturę na podstawie wybranego typu chłodzenia
double SimulatedAnnealing::calcNewTemperature(double currentTemperature, int eraNumber, int coolingType, double coolingFactor) {
    switch (coolingType) {
        case 1:
            return currentTemperature * coolingFactor;  // Chłodzenie geometryczne
        case 2:
            return currentTemperature / (1 + coolingFactor * log(eraNumber + 1));  // Chłodzenie logarytmiczne
        case 3:
            return pow(coolingFactor, eraNumber) * currentTemperature;  // Chłodzenie wykładnicze
        default:
            return currentTemperature;  // Domyślny przypadek, brak zmiany temperatury
    }
}

// Funkcja obliczająca początkową temperaturę na podstawie prób
int SimulatedAnnealing::calcBeginTemperature(int** matrix, int matrixSize, int* path, int pathLen) {
    int minLen = INT_MAX;
    int maxLen = 0;

    // Liczba prób jest zależna od rozmiaru macierzy
    int samples = std::max(100, matrixSize * 10);
    double scalingFactor = log(matrixSize) / 2.0;  // Skalowanie na podstawie logarytmu rozmiaru macierzy

    for (int i = 0; i < samples; ++i) {
        // Zamiana punktów w ścieżce
        swapPoints(path, matrixSize);
        int testLen;
        calcLen(matrix, matrixSize, path, testLen);
        minLen = min(minLen, testLen);  // Szukamy minimalnej długości
        maxLen = max(maxLen, testLen);  // Szukamy maksymalnej długości
    }

    // Obliczamy początkową temperaturę na podstawie różnicy max i min długości
    return (maxLen - minLen) * scalingFactor;
}

// Funkcja do zamiany dwóch punktów w ścieżce
void SimulatedAnnealing::swapPoints(int* path, int matrixSize) {
    // Wybieramy dwa losowe punkty do zamiany
    int index1 = rand() % matrixSize;
    int index2 = rand() % matrixSize;

    // Zapewniamy, że indeksy są różne
    while (index1 == index2) {
        index2 = rand() % matrixSize;
    }

    // Zamieniamy miejscami punkty w ścieżce
    std::swap(path[index1], path[index2]);

    // Jeśli którykolwiek z zamienionych punktów to miasto 0, ustawiamy odpowiednią wartość
    if (index1 == 0 || index2 == 0) {
        path[matrixSize] = path[0];
    }
}
