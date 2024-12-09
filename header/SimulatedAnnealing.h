#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
#include <random>
#include <chrono>
#include <utility>
#include "MacierzKosztow.h" // Nagłówek klasy MacierzKosztow

using namespace std;

// Klasa implementująca algorytm symulowanego wyżarzania dla problemu komiwojażera (TSP)
class SimulatedAnnealing {
public:
    // Główna metoda uruchamiająca algorytm symulowanego wyżarzania
    static std::pair<std::pair<std::pair<long long, long long>, int>, std::pair<double, int>> start(
        const MacierzKosztow& macierz,
        double coolingFactor,
        int maxTime,
        int coolingType,
        bool testing
    );

    // Wektory do przechowywania danych wynikowych
    static vector<int> wykresBestLengths;          // Najlepsze długości ścieżek
    static vector<double> wykresCurrentTemperature; // Aktualne temperatury
    static vector<long long> wykresCzasyOfBestLengths; // Czasy najlepszych wyników
    static vector<int> finalPath;                  // Ostateczna ścieżka

private:
    // Algorytm zachłanny do znalezienia początkowego rozwiązania
    static void greedyAlg(int** matrix, int matrixSize, int* bestPath, int& bestLen);

    // Funkcja obliczająca długość ścieżki
    static void calcLen(int** matrix, int matrixSize, int* path, int& length);

    // Funkcja obliczająca nową temperaturę w zależności od typu chłodzenia
    static double calcNewTemperature(double currentTemperature, int eraNumber, int coolingType, double coolingFactor);

    // Funkcja obliczająca początkową temperaturę na podstawie próbek
    static int calcBeginTemperature(int** matrix, int matrixSize, int* path, int pathLen, std::mt19937& gen, std::uniform_real_distribution<>& dis);

    // Funkcja zamieniająca dwa punkty w ścieżce
    static void swapPoints(int* path, int matrixSize, std::mt19937& gen, std::uniform_real_distribution<>& dis);
};

#endif // SIMULATEDANNEALING_H
