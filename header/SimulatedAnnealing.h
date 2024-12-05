#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

#include <iostream>
#include <vector>
#include <algorithm>
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
    vector<int> testPath;

    void greedyAlg();
    void calcLen();
    double calcNewTemperature(double currentTemperature, int eraNumber);
    double calcGeometricTemp(double T);
    double calcLogaritmicTemp(double T, int eraNumber);
    double calcExpotentialTemp(double T, int eraNumber);
    int calcBeginTemperature();
    pair<int, int> generateSwapPoints();
    void swapPoints(pair<int, int> swappedPoints);
public:
    void start();
    Sa(int **matrix, int matrixSize, double coolingFactor, int maxTime, int coolingType);
    ~Sa();

    vector<int> bestPath;
    vector<int> currentPath;
    int beginningTemperature;
    int bestLen;
    int currentLen; //stan w ktorym teraz przebywamy
    int timeOfBestSolution;


    vector<int> wykresCzasy;
    vector<int> wykresBesty;
};

#endif //SIMULATEDANNEALING_H
