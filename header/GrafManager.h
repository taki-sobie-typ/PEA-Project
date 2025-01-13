#ifndef GRAFMANAGER_H
#define GRAFMANAGER_H

#include <iostream>
#include <string>
#include "MacierzKosztow.h"
#include "GrafGenerator.h"
#include "CzytnikGrafow.h"
#include "BruteForce.h"
#include "GeneticAlgorithm.h"
#include "BranchAndBound.h"
#include "SimulatedAnnealing.h"

using namespace std;

// Klasa zarządzająca operacjami na grafach, takimi jak wczytywanie danych, generowanie grafów,
// uruchamianie algorytmów oraz zapisywanie wyników.
class GrafManager {
private:
    int** macierzKosztow;   // Wskaźnik do macierzy kosztów.
    size_t liczbaMiast;     // Liczba miast (wierzchołków) w grafie.

    vector<int> sciezka;    // Wektor przechowujący wyznaczoną ścieżkę.

    string nazwaPliku;      // Nazwa pliku używanego do wczytywania danych.
    string folderRozw = "rozw/"; // Domyślny folder dla plików z wynikami.

    CzytnikGrafow czytnikGrafow; // Obiekt do wczytywania grafów z plików.

public:
    // Konstruktor inicjalizujący zmienne.
    GrafManager() : macierzKosztow(nullptr), liczbaMiast(0), czytnikGrafow("atsp/") {}

    // Destruktor do zwalniania pamięci.
    ~GrafManager();

    // Zapisuje wyznaczoną ścieżkę do pliku tekstowego.
    void zapiszSciezkeDoPlikuTxt(string txtFileName);

    // Wczytuje ścieżkę z pliku tekstowego.
    int wczytajSciezkeZPlikuTxt(const string& nazwaPliku);

    // Wczytuje dane grafu z pliku.
    void wczytajDaneZPliku();

    // Generuje losowy graf.
    void wygenerujGrafLosowo();

    // Wyświetla graf w formie macierzy kosztów.
    void wyswietlGraf();

    // Uruchamia algorytm brute force dla problemu TSP.
    void uruchomBruteForce();

    // Uruchamia algorytm Branch and Bound dla problemu TSP.
    void uruchomBranchAndBound();

    // Uruchamia algorytm Genetyczny z parametrami dla problemu TSP.
    void uruchomGeneticAlgorithm(int populationSize, int stopTime, double mutationRate, double crossoverRate, Mutation mutationType);

    // Uruchamia algorytm symulowanego wyżarzania.
    void uruchomSimulatedAnnealing(double coolingFactor, int maxTime, int coolingType);

    // Zapisuje podstawowe wyniki do pliku CSV.
    void zapiszDoCSV(const string& nazwaPliku, int liczbaMiast, long long czas);

    // Zapisuje wyniki do pliku CSV z dodatkowymi informacjami, takimi jak procent ukończenia czy przerwanie.
    void zapiszDoCSV2(const string& nazwaPliku, int liczbaMiast, long long czas, int procent, int czyprzerwany);

    // Zapisuje szczegółowe wyniki symulowanego wyżarzania do pliku CSV.
    void zapiszDoCSV3(const string& writeFileName, int size, long long duration, int coolingType,
                      double beginningTemperature, long long timeOfBestSolution, int bestLen, int maxRunTime);

    // Przeprowadza testy symulowanego wyżarzania do raportu.
    void testForReportSimulatedAnnealing();

    // Przeprowadza testy brute force do raportu.
    void testForReportBF();

    // Przeprowadza testy algorytmu Branch and Bound dla raportu.
    void testForReportBandB_BFS();

    // Testuje rozwiązania symetryczne dla raportu.
    void testForReportSymetric();

    // Testuje algorytm genetyczny dla raportu.
    void testForReportGeneticAlgorithm();
};

#endif // GRAFMANAGER_H
