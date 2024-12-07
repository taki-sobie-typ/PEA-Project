#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
#include <random>
#include <chrono>
#include <utility>
#include "MacierzKosztow.h" // Include header for MacierzKosztow class

using namespace std;

class SimulatedAnnealing {

public:
    static std::pair<std::pair<std::pair<long long, long long>, int>,std::pair<double, int>> start(const MacierzKosztow& macierz, double coolingFactor, int maxTime, int coolingType);

    static vector<int> wykresBestLengths;           // Stores best solution lengths
    static vector<double> wykresCurrentTemperature;           // Stores best solution lengths
    static vector<long long> wykresCzasyOfBestLengths; // Stores times of best solutions
    static vector<int> finalPath;

private:
    static void greedyAlg(int** matrix, int matrixSize, int* bestPath, int& bestLen);
    static void calcLen(int** matrix, int matrixSize, int* path, int& length);
    static double calcNewTemperature(double currentTemperature, int eraNumber, int coolingType, double coolingFactor);
    static int calcBeginTemperature(int** matrix, int matrixSize, int* path, int pathLen);
    static void swapPoints(int* path, int matrixSize);
};

#endif // SIMULATEDANNEALING_H
