#include "../header/SimulatedAnnealing.h"

Sa::Sa(int** matrix, int matrixSize, double coolingFactor, int maxTime, int coolingType)
    : matrix(matrix), matrixSize(matrixSize), coolingFactor(coolingFactor), maxTime(maxTime), coolingType(coolingType) {
    testPath = new int[matrixSize + 1];
    bestPath = new int[matrixSize + 1];
    currentPath = new int[matrixSize + 1];
    wykresSize = 0;
    wykresCapacity = 100; // Initial capacity
    wykresCzasy = new int[wykresCapacity];
    wykresBesty = new int[wykresCapacity];
}

Sa::~Sa() {
    delete[] testPath;
    delete[] bestPath;
    delete[] currentPath;
    delete[] wykresCzasy;
    delete[] wykresBesty;
}

void Sa::start() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1);

    pair<int, int> swappedPoints;
    greedyAlg();
    beginningTemperature = calcBeginTemperature();
    eraLen = matrixSize * (matrixSize - 1) / 2;

    std::copy(bestPath, bestPath + matrixSize + 1, currentPath);
    currentLen = bestLen;

    appendWykres(0, bestLen);

    double currentTemperature = beginningTemperature;
    int eraNumber = 0;

    auto startTime = std::chrono::high_resolution_clock::now();
    timeOfBestSolution = 0;

    do {
        for (int era = 0; era < eraLen; ++era) {
            std::copy(currentPath, currentPath + matrixSize + 1, testPath);
            swappedPoints = generateSwapPoints();
            swapPoints(swappedPoints);
            calcLen();

            int delta = testLen - currentLen;
            if (delta <= 0) {
                currentLen = testLen;
                std::copy(testPath, testPath + matrixSize + 1, currentPath);
                if (currentLen < bestLen) {
                    bestLen = currentLen;
                    std::copy(currentPath, currentPath + matrixSize + 1, bestPath);

                    auto currentTime = std::chrono::high_resolution_clock::now();
                    timeOfBestSolution = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
                    appendWykres(timeOfBestSolution, bestLen);
                }
            } else {
                double randomValue = dis(gen);
                if (randomValue < exp(-delta / currentTemperature)) {
                    currentLen = testLen;
                    std::copy(testPath, testPath + matrixSize + 1, currentPath);
                }
            }
        }
        ++eraNumber;
        currentTemperature = calcNewTemperature(currentTemperature, eraNumber);
    } while (currentTemperature >= 0.01 &&
             std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - startTime).count() <= maxTime);
}

void Sa::greedyAlg() {
    int currentCity = 0;
    bestPath[0] = currentCity;
    bestLen = 0;
    int pathSize = 1;

    while (pathSize < matrixSize) {
        int minLen = INT_MAX;
        int nextCity = -1;

        for (int i = 0; i < matrixSize; ++i) {
            bool visited = false;
            for (int j = 0; j < pathSize; ++j) {
                if (bestPath[j] == i) {
                    visited = true;
                    break;
                }
            }
            if (!visited && matrix[currentCity][i] < minLen) {
                nextCity = i;
                minLen = matrix[currentCity][i];
            }
        }
        bestPath[pathSize++] = nextCity;
        bestLen += minLen;
        currentCity = nextCity;
    }
    bestPath[pathSize] = bestPath[0];
    bestLen += matrix[currentCity][0];
}

double Sa::calcNewTemperature(double T, int eraNumber) {
    switch (coolingType) {
        case 1: return calcGeometricTemp(T);
        case 2: return calcLogaritmicTemp(T, eraNumber);
        case 3: return calcExpotentialTemp(T, eraNumber);
    }
    return 0;
}

double Sa::calcGeometricTemp(double T) {
    return T * coolingFactor;
}

double Sa::calcLogaritmicTemp(double T, int eraNumber) {
    return T / (1 + coolingFactor * log(eraNumber + 1));
}

double Sa::calcExpotentialTemp(double T, int eraNumber) {
    return pow(coolingFactor, eraNumber) * T;
}

pair<int, int> Sa::generateSwapPoints() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, matrixSize - 1);

    int indexI = dis(gen);
    int indexJ = dis(gen);
    while (indexI == indexJ) indexJ = dis(gen);
    return {indexI, indexJ};
}

void Sa::swapPoints(pair<int, int> swappedPoints) {
    swap(testPath[swappedPoints.first], testPath[swappedPoints.second]);
    if (swappedPoints.first == 0 || swappedPoints.second == 0) {
        testPath[matrixSize] = testPath[0];
    }
}

void Sa::calcLen() {
    testLen = 0;
    for (int i = 0; i < matrixSize; ++i) {
        testLen += matrix[testPath[i]][testPath[i + 1]];
    }
}

int Sa::calcBeginTemperature() {
    std::copy(bestPath, bestPath + matrixSize + 1, testPath);
    testLen = bestLen;

    int minLen = INT_MAX;
    int maxLen = 0;

    for (int i = 0; i < 100; ++i) {
        swapPoints(generateSwapPoints());
        calcLen();
        minLen = min(minLen, testLen);
        maxLen = max(maxLen, testLen);
    }
    return (maxLen - minLen) * 1.5;
}

void Sa::appendWykres(int czas, int best) {
    if (wykresSize == wykresCapacity) {
        wykresCapacity *= 2;
        int* newWykresCzasy = new int[wykresCapacity];
        int* newWykresBesty = new int[wykresCapacity];
        std::copy(wykresCzasy, wykresCzasy + wykresSize, newWykresCzasy);
        std::copy(wykresBesty, wykresBesty + wykresSize, newWykresBesty);
        delete[] wykresCzasy;
        delete[] wykresBesty;
        wykresCzasy = newWykresCzasy;
        wykresBesty = newWykresBesty;
    }
    wykresCzasy[wykresSize] = czas;
    wykresBesty[wykresSize] = best;
    ++wykresSize;
}
