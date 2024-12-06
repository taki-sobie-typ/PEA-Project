#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
#include <random>
#include <chrono>

using namespace std;

class Sa {
private:
    int** matrix;
    int matrixSize;
    int maxTime;
    int testLen;
    int coolingType;
    int eraLen;
    double coolingFactor;

    int* testPath;
    int* bestPath;
    int* currentPath;
    int* wykresCzasy;
    int* wykresBesty;

    int wykresSize;
    int wykresCapacity;

    void greedyAlg();
    void calcLen();
    double calcNewTemperature(double currentTemperature, int eraNumber);
    double calcGeometricTemp(double T);
    double calcLogaritmicTemp(double T, int eraNumber);
    double calcExpotentialTemp(double T, int eraNumber);
    int calcBeginTemperature();
    pair<int, int> generateSwapPoints();
    void swapPoints(pair<int, int> swappedPoints);
    void appendWykres(int czas, int best);

public:
    const int* getBestPath() const { return bestPath; } // Returns a pointer to bestPath
    int getMatrixSize() const { return matrixSize; }   // Returns the size of the matrix

    void start();
    Sa(int** matrix, int matrixSize, double coolingFactor, int maxTime, int coolingType);
    ~Sa();

    int beginningTemperature;
    int bestLen;
    int currentLen;
    int timeOfBestSolution;
};

#endif // SIMULATEDANNEALING_H
