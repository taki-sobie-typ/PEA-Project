#include "../header/GeneticAlgorithm.h"
#include <random>
#include <ctime>
#include <climits>
#include <numeric>

GeneticAlgorithm::GeneticAlgorithm(MacierzKosztow& matrix) : matrix(matrix) {}

// Static function to calculate the cost of a path
int GeneticAlgorithm::calculateTourCost(const std::vector<int>& path, int** matrix, int size) {
    int totalCost = 0;
    for (int i = 0; i < size - 1; ++i) {
        totalCost += matrix[path[i]][path[i + 1]];
    }
    totalCost += matrix[path[size - 1]][path[0]]; // Return to start
    return totalCost;
}

// Generate a random population
std::vector<Individual> GeneticAlgorithm::generateRandomPopulation(int populationSize) {
    int size = matrix.pobierzLiczbeMiast();
    int** costMatrix = matrix.pobierzMacierzKosztow();

    std::vector<Individual> population(populationSize);
    for (int i = 0; i < populationSize; ++i) {
        Individual individual;
        individual.path.resize(size);
        std::iota(individual.path.begin(), individual.path.end(), 0); // Fill path with 0, 1, ..., size-1
        std::shuffle(individual.path.begin() + 1, individual.path.end(), std::mt19937(std::random_device()()));
        individual.cost = calculateTourCost(individual.path, costMatrix, size);
        population[i] = individual;
    }
    return population;
}

// Comparison function for individuals
bool GeneticAlgorithm::compareIndividuals(const Individual& a, const Individual& b) {
    return a.cost < b.cost;
}

// Tournament selection
Individual GeneticAlgorithm::tournamentSelection(std::vector<Individual>& population) {
    Individual a = population[std::rand() % population.size()];
    Individual b = population[std::rand() % population.size()];
    return compareIndividuals(a, b) ? a : b;
}

// Crossover (unchanged)
void GeneticAlgorithm::OXCrossover(const Individual& parent1, const Individual& parent2, Individual& child1, Individual& child2, int startPos, int endPos) {
    // Same as in your original implementation
}

// Swap mutation
void GeneticAlgorithm::swapMutation(Individual& individual) {
    int size = individual.path.size();
    int i = std::rand() % size;
    int j = std::rand() % size;
    std::swap(individual.path[i], individual.path[j]);
    individual.cost = calculateTourCost(individual.path, matrix.pobierzMacierzKosztow(), size);
}

// Inversion mutation
void GeneticAlgorithm::inversionMutation(Individual& individual) {
    int size = individual.path.size();
    int i = std::rand() % size;
    int j = std::rand() % size;
    if (i > j) std::swap(i, j);
    std::reverse(individual.path.begin() + i, individual.path.begin() + j + 1);
    individual.cost = calculateTourCost(individual.path, matrix.pobierzMacierzKosztow(), size);
}

// Run the genetic algorithm
Individual GeneticAlgorithm::run(
    int stopTime,
    int populationSize,
    double mutationRate,
    double crossoverRate,
    Mutation mutationType
) {
    std::vector<Individual> population = generateRandomPopulation(populationSize);
    int bestSolution = INT_MAX;
    const std::clock_t startTime = std::clock();

    double lastTickTime = 0.0; // Ostatni czas zapisu "tick"

    while ((std::clock() - startTime) / CLOCKS_PER_SEC < stopTime) {
        std::sort(population.begin(), population.end(), compareIndividuals);

        double currentTime = (std::clock() - startTime) / (double)CLOCKS_PER_SEC;

        // Aktualizacja dla najlepszego rozwiązania
        if (population[0].cost < bestSolution) {
            bestSolution = population[0].cost;

            // Dodanie danych do wykresów najlepszych rozwiązań
            wykresBestLengths.push_back(bestSolution);
            wykresCzasyOfBestLengths.push_back(currentTime);

            // Zapisanie najlepszej ścieżki w czasie
            bestSolutionFoundInTime.emplace_back(currentTime, bestSolution);
            // TODO Zrobic to aby tikowalo po czasie i zbieralo wyniki zadziej bo co znalezienie lepszego wyniku to za czesto
        }

        // Aktualizacja dla wszystkich długości co "tick"
        if (currentTime - lastTickTime >= 1.0) { // "Tick" co 1 sekundę
            int currentBest = population[0].cost;
            wykresLengths.push_back(currentBest);
            wykresCzasyOfLengths.push_back(currentTime);
            lastTickTime = currentTime; // Zresetuj czas ticku
        }

        // Tworzenie nowej populacji
        std::vector<Individual> newPopulation(populationSize);

        // Elitarność
        std::copy(population.begin(), population.begin() + 10, newPopulation.begin());

        // Krzyżowanie i mutacja
        for (int i = 10; i < populationSize; i += 2) {
            Individual parent1 = tournamentSelection(population);
            Individual parent2 = tournamentSelection(population);
            Individual child1 = parent1, child2 = parent2;

            if ((std::rand() / (double)RAND_MAX) < crossoverRate) {
                int startPos = std::rand() % parent1.path.size();
                int endPos = std::rand() % parent1.path.size();
                if (startPos > endPos) std::swap(startPos, endPos);
                OXCrossover(parent1, parent2, child1, child2, startPos, endPos);
            }

            if ((std::rand() / (double)RAND_MAX) < mutationRate) {
                if (mutationType == swapMut) swapMutation(child1);
                else inversionMutation(child1);
            }

            if ((std::rand() / (double)RAND_MAX) < mutationRate) {
                if (mutationType == swapMut) swapMutation(child2);
                else inversionMutation(child2);
            }

            newPopulation[i] = child1;
            if (i + 1 < populationSize) newPopulation[i + 1] = child2;
        }

        population = newPopulation;
    }

    // Zwrócenie najlepszego osobnika
    return *std::min_element(population.begin(), population.end(), compareIndividuals);
}

const std::list<std::pair<double, int>>& GeneticAlgorithm::getBestSolutionFoundInTime() const {
    return bestSolutionFoundInTime;
}
