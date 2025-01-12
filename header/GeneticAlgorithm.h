#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <vector>
#include <list>
#include <algorithm>
#include "MacierzKosztow.h"

struct Individual {
    std::vector<int> path;
    int cost;
};

enum Mutation {
    swapMut,
    inverseMut
};

class GeneticAlgorithm {
private:
    MacierzKosztow &matrix; // Reference to cost matrix
    std::list<std::pair<double, int>> bestSolutionFoundInTime;

    static int calculateTourCost(const std::vector<int>& path, int** matrix, int size);
    static bool compareIndividuals(const Individual& a, const Individual& b);

    void OXCrossover(const Individual& parent1, const Individual& parent2, Individual& child1, Individual& child2, int startPos, int endPos);
    void swapMutation(Individual& individual);
    void inversionMutation(Individual& individual);
    Individual tournamentSelection(std::vector<Individual>& population);

public:
    GeneticAlgorithm(MacierzKosztow& matrix);
    std::vector<Individual> generateRandomPopulation(int populationSize);
    Individual run(int stopTime, int populationSize, double mutationRate, double crossoverRate, Mutation mutationType);
    const std::list<std::pair<double, int>>& getBestSolutionFoundInTime() const;

    std::vector<int> wykresBestLengths;
    std::vector<double> wykresCzasyOfBestLengths;
    std::vector<int> wykresLengths;
    std::vector<double> wykresCzasyOfLengths;
};

#endif // GENETIC_ALGORITHM_H
