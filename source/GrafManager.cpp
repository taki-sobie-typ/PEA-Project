#include "../header/GrafManager.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

vector<int> sciezka;
string nazwaPliku;
string folderRozw;

// Destruktor klasy GrafManager
// Zwalnia pamięć zajmowaną przez macierz kosztów, jeśli została załadowana
GrafManager::~GrafManager() {
    if (macierzKosztow) {
        for (size_t i = 0; i < liczbaMiast; ++i) {
            delete[] macierzKosztow[i];
        }
        delete[] macierzKosztow;
    }
}

// Metoda do wczytywania danych z pliku
void GrafManager::wczytajDaneZPliku() {
    nazwaPliku;
    cout << "Podaj nazwe pliku: ";
    cin >> nazwaPliku;
    cout << endl;

    // Zwolnij istniejącą macierz kosztów, jeśli istnieje
    if (macierzKosztow) {
        for (size_t i = 0; i < liczbaMiast; ++i) {
            delete[] macierzKosztow[i];
        }
        delete[] macierzKosztow;
        macierzKosztow = nullptr;
    }

    // Wczytaj nowe dane z pliku
    macierzKosztow = czytnikGrafow.wczytajMacierz(nazwaPliku, liczbaMiast);

    // Sprawdź, czy dane zostały poprawnie wczytane
    if (macierzKosztow) {
        cout << "Dane zostaly wczytane pomyslnie." << endl;
    } else {
        cout << "Blad wczytywania danych." << endl;
    }
    cout << endl;
}

// Metoda do generowania losowego grafu
void GrafManager::wygenerujGrafLosowo() {
    int liczbaWierzcholkow, minWartosc, maxWartosc;

    cout << "Podaj liczbe wierzcholkow: ";
    cin >> liczbaWierzcholkow;
    cout << "Podaj minimalna wartosc krawedzi: ";
    cin >> minWartosc;
    cout << "Podaj maksymalna wartosc krawedzi: ";
    cin >> maxWartosc;
    cout << endl;

    // Wygeneruj losowy graf używając klasy GrafGenerator
    vector<vector<int>> matrix = GrafGenerator::generujLosowaMacierz(liczbaWierzcholkow, minWartosc, maxWartosc, false);

    // Zwolnij istniejącą macierz kosztów, jeśli istnieje
    if (macierzKosztow) {
        for (size_t i = 0; i < liczbaMiast; ++i) {
            delete[] macierzKosztow[i];
        }
        delete[] macierzKosztow;
        macierzKosztow = nullptr;
    }

    // Zaktualizuj liczbaMiast i zaalokuj nową macierz kosztów
    liczbaMiast = liczbaWierzcholkow;
    macierzKosztow = new int*[liczbaMiast];
    for (size_t i = 0; i < liczbaMiast; ++i) {
        macierzKosztow[i] = new int[liczbaMiast];
        for (size_t j = 0; j < liczbaMiast; ++j) {
            macierzKosztow[i][j] = matrix[i][j];
        }
    }

    cout << "Graf zostal wygenerowany pomyslnie." << endl;
    cout << endl;
}

// Metoda do wyświetlania macierzy kosztów
void GrafManager::wyswietlGraf() {
    if (macierzKosztow) {
        cout << "Macierz:" << endl;
        for (size_t i = 0; i < liczbaMiast; ++i) {
            for (size_t j = 0; j < liczbaMiast; ++j) {
                cout << macierzKosztow[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    } else {
        cout << "Brak danych do wyswietlenia." << endl;
    }
}

// Metoda do uruchomienia algorytmu Brute Force
void GrafManager::uruchomBruteForce() {
    if (macierzKosztow) {
        // Utwórz obiekt macierzy kosztów i uruchom algorytm Brute Force
        MacierzKosztow macierz(macierzKosztow, liczbaMiast);
        BruteForce::uruchomAlgorytm(macierz);
    } else {
        cout << "Brak zaladowanej macierzy kosztow. Najpierw wczytaj lub wygeneruj graf." << endl;
    }
}

// Metoda do uruchomienia algorytmue
void GrafManager::uruchomBranchAndBound() {
    if (macierzKosztow) {
        // Utwórz obiekt macierzy kosztów i uruchom algorytm
        MacierzKosztow macierz(macierzKosztow, liczbaMiast);
        BranchAndBound::uruchomAlgorytm(macierz, 300000);
    } else {
        cout << "Brak zaladowanej macierzy kosztow. Najpierw wczytaj lub wygeneruj graf." << endl;
    }
}

// Metoda do uruchomienia algorytmue
void GrafManager::uruchomSimulatedAnnealing(double coolingFactor, int maxTime, int coolingType) {
    if (macierzKosztow) {
        MacierzKosztow macierz(macierzKosztow, liczbaMiast);

        //SA START
        SimulatedAnnealing::start(macierz, coolingFactor, maxTime, coolingType);
        sciezka = SimulatedAnnealing::finalPath;

    } else {
        cout << "Brak zaladowanej macierzy kosztow. Najpierw wczytaj lub wygeneruj graf." << endl;
    }
}

// Metoda do zapisu wyników do pliku CSV
void GrafManager::zapiszDoCSV(const string& nazwaPliku, int liczbaMiast, long long czas) {
    ofstream plik(folderRozw + nazwaPliku, ios::app);  // Open in append mode
    if (plik.is_open()) {
        plik << liczbaMiast << "," << czas << endl;
        plik.close();
    } else {
        cerr << "Blad otwierania pliku do zapisu." << endl;
    }
}

// Metoda do zapisu wyników do pliku CSV
void GrafManager::zapiszDoCSV2(const string& nazwaPliku, int liczbaMiast, long long czas, int procent, int czyprzerwany) {
    ofstream plik(folderRozw + nazwaPliku, ios::app);  // Open in append mode
    if (plik.is_open()) {
        plik << liczbaMiast << "," << czas << "," << procent << "," << czyprzerwany << endl;
        plik.close();
    } else {
        cerr << "Blad otwierania pliku do zapisu." << endl;
    }
}

// Method to save detailed results to a CSV file
void GrafManager::zapiszDoCSV3(const string& writeFileName,
                              int size,
                              long long duration,
                              int coolingType,
                              double beginningTemperature,
                              long long timeOfBestSolution,
                              int bestLen,
                              int maxRunTime) {
    ofstream plik(folderRozw + writeFileName + "_" +nazwaPliku, ios::app);  // Open in append mode
    if (plik.is_open()) {
        // Write the header row if the file is empty (optional, depending on your needs)
        if (plik.tellp() == 0) {
            plik << "theFileNameWhereMatrixCameFrom;size;duration;coolingType;beginningTemperature;"
                 << "timeOfBestSolution;bestLen;maxRunTime\n";
        }

        // Write the first part of the data
        plik << nazwaPliku << ";"
             << size << ";"
             << duration << ";"
             << coolingType << ";"
             << beginningTemperature << ";"
             << timeOfBestSolution << ";"
             << bestLen << ";"
             << maxRunTime << "\n";

        // Write `wykresBestLengths` values separated by `;`
        for (size_t i = 0; i < SimulatedAnnealing::wykresBestLengths.size(); ++i) {
            plik << SimulatedAnnealing::wykresBestLengths[i];
            if (i != SimulatedAnnealing::wykresBestLengths.size() - 1) {
                plik << ";";
            }
        }
        plik << "\n";  // Move to the next row

        // Write `wykresCurrentTemperature` values separated by `;`
        for (size_t i = 0; i < SimulatedAnnealing::wykresCurrentTemperature.size(); ++i) {
            plik << SimulatedAnnealing::wykresCurrentTemperature[i];
            if (i != SimulatedAnnealing::wykresCurrentTemperature.size() - 1) {
                plik << ";";
            }
        }
        plik << "\n";  // Move to the next row

        // Write `wykresCzasyOfBestLengths` values separated by `;`
        for (size_t i = 0; i < SimulatedAnnealing::wykresCzasyOfBestLengths.size(); ++i) {
            plik << SimulatedAnnealing::wykresCzasyOfBestLengths[i];
            if (i != SimulatedAnnealing::wykresCzasyOfBestLengths.size() - 1) {
                plik << ";";
            }
        }
        plik << "\n";  // Final row for this entry

        plik.close();  // Close the file
        cout << "Dane zapisane do pliku: " << folderRozw + nazwaPliku << endl;
    } else {
        cerr << "Blad otwierania pliku do zapisu." << endl;
    }
}


// Metoda do zapisu ścieżki rozwiązania do pliku txt
void GrafManager::zapiszSciezkeDoPlikuTxt() {
    ofstream plik(folderRozw + "sw_" + nazwaPliku);  // Open file for writing
    if (plik.is_open()) {
        int liczbaMiast = sciezka.size();  // Number of cities in the path
        plik << liczbaMiast << endl;  // Write the number of cities in the first line

        // Write each city in the path (including the first city again at the end to form a cycle)
        for (size_t i = 0; i < sciezka.size(); ++i) {
            plik << sciezka[i] << endl;  // Write each city on a new line
        }

        cout << "Sciezka zostala zapisana do pliku: " << nazwaPliku << endl;
        plik.close();
    } else {
        cerr << "Blad otwierania pliku do zapisu." << endl;
    }
}

// Metoda do wczytania ścieżki rozwiązania z pliku txt i obliczenia kosztu
int GrafManager::wczytajSciezkeZPlikuTxt(const string& nazwaPliku) {
    ifstream plik(folderRozw + nazwaPliku);  // Open file for reading
    vector<int> sciezka;
    int miasto;

    if (plik.is_open()) {
        int liczbaMiast;
        plik >> liczbaMiast;  // Read the number of cities (first line)

        // Read each city in the path (one per line)
        while (plik >> miasto) {
            sciezka.push_back(miasto);
        }
        plik.close();

        // Ensure the path is a cycle (the first city should be the same as the last city)
        if (!sciezka.empty() && sciezka.front() != sciezka.back()) {
            sciezka.push_back(sciezka.front());  // Complete the cycle by adding the first city at the end
        }

        // Calculate the total cost of the path based on the loaded cost matrix
        int totalCost = 0;
        for (size_t i = 0; i < sciezka.size() - 1; ++i) {
            int start = sciezka[i];
            int end = sciezka[i + 1];
            if (start < liczbaMiast && end < liczbaMiast) {
                totalCost += macierzKosztow[start][end];  // Sum the costs from the matrix
            }
        }

        cout << "Koszt sciezki: " << totalCost << endl;
        return totalCost;
    } else {
        cerr << "Blad otwierania pliku do odczytu." << endl;
        return -1;  // Return -1 if the file cannot be opened
    }
}

// Metoda testująca dla raportu
void GrafManager::testForReportBF() {
    string nazwaPlikuCSV = "bruteforce_report.csv";

    for (int rozmiar = 5; rozmiar <= 15; ++rozmiar) {
        for (int i = 0; i < 50; ++i) {
            // Generuj nowy losowy graf o rozmiarze "rozmiar"
            vector<vector<int>> matrix = GrafGenerator::generujLosowaMacierz(rozmiar, 1, 100, false);  // Edge values from 1 to 100

            // Zwolnij istniejącą macierz kosztów, jeśli istnieje
            if (macierzKosztow) {
                for (size_t i = 0; i < liczbaMiast; ++i) {
                    delete[] macierzKosztow[i];
                }
                delete[] macierzKosztow;
            }

            liczbaMiast = rozmiar;
            macierzKosztow = new int*[liczbaMiast];
            for (size_t j = 0; j < liczbaMiast; ++j) {
                macierzKosztow[j] = new int[liczbaMiast];
                for (size_t k = 0; k < liczbaMiast; ++k) {
                    macierzKosztow[j][k] = matrix[j][k];
                }
            }

            // Uruchom algorytm i zmierz czas wykonania
            MacierzKosztow macierz(macierzKosztow, liczbaMiast);
            long long czasTrwania = BruteForce::uruchomAlgorytm(macierz);

            // Zapisz wynik do pliku CSV
            zapiszDoCSV(nazwaPlikuCSV, liczbaMiast, czasTrwania);
        }
    }
}

void GrafManager::testForReportBandB_BFS() {
    string nazwaPlikuCSV = "b&b_BFS_report_p.csv";

    for (int rozmiar = 4; rozmiar <= 30; ++rozmiar) {
        int rozmiarInner = 20;
        if (rozmiar > 12) {
            rozmiarInner = 20;
        }
        if (rozmiar > 14) {
            rozmiarInner = 20;
        }
        if (rozmiar > 16) {
            rozmiarInner = 5;
        }
        for (int i = 0; i < rozmiarInner; ++i) {
            // Generuj nowy losowy graf o rozmiarze "rozmiar"
            vector<vector<int>> matrix = GrafGenerator::generujLosowaMacierz(rozmiar, 1, 100, false);

            // Zwolnij istniejącą macierz kosztów, jeśli istnieje
            if (macierzKosztow) {
                for (size_t i = 0; i < liczbaMiast; ++i) {
                    delete[] macierzKosztow[i];
                }
                delete[] macierzKosztow;
            }

            liczbaMiast = rozmiar;
            macierzKosztow = new int*[liczbaMiast];
            for (size_t j = 0; j < liczbaMiast; ++j) {
                macierzKosztow[j] = new int[liczbaMiast];
                for (size_t k = 0; k < liczbaMiast; ++k) {
                    macierzKosztow[j][k] = matrix[j][k];
                }
            }

            // Uruchom algorytm i zmierz czas wykonania
            MacierzKosztow macierz(macierzKosztow, liczbaMiast);
            auto [result, czyPrzerwany] = BranchAndBound::uruchomAlgorytm(macierz, 300000);
            auto [czasTrwania, liczbaPrzetworzonychWezlow] = result;

            // Zapisz wynik do pliku CSV
            zapiszDoCSV2(nazwaPlikuCSV, liczbaMiast, czasTrwania, liczbaPrzetworzonychWezlow, czyPrzerwany);
        }
    }
}

void GrafManager::testForReportSymetric() {

    string nazwaPlikuCSV = "b&b_BFS_report_s_p.csv";

    for (int rozmiar = 4; rozmiar <= 30; ++rozmiar) {
        int rozmiarInner = 20;
        if (rozmiar > 12) {
            rozmiarInner = 20;
        }
        if (rozmiar > 14) {
            rozmiarInner = 20;
        }
        if (rozmiar > 16) {
            rozmiarInner = 5;
        }
        for (int i = 0; i < rozmiarInner; ++i) {
            // Generuj nowy losowy graf o rozmiarze "rozmiar"
            vector<vector<int>> matrix = GrafGenerator::generujLosowaMacierz(rozmiar, 1, 99, true);  // Edge values from 1 to 100

            // Zwolnij istniejącą macierz kosztów, jeśli istnieje
            if (macierzKosztow) {
                for (size_t i = 0; i < liczbaMiast; ++i) {
                    delete[] macierzKosztow[i];
                }
                delete[] macierzKosztow;
            }

            liczbaMiast = rozmiar;
            macierzKosztow = new int*[liczbaMiast];
            for (size_t j = 0; j < liczbaMiast; ++j) {
                macierzKosztow[j] = new int[liczbaMiast];
                for (size_t k = 0; k < liczbaMiast; ++k) {
                    macierzKosztow[j][k] = matrix[j][k];
                }
            }

            // Uruchom algorytm i zmierz czas wykonania
            MacierzKosztow macierz(macierzKosztow, liczbaMiast);
            auto [result, czyPrzerwany] = BranchAndBound::uruchomAlgorytm(macierz, 300000);
            auto [czasTrwania, liczbaPrzetworzonychWezlow] = result;

            // Zapisz wynik do pliku CSV
            zapiszDoCSV2(nazwaPlikuCSV, liczbaMiast, czasTrwania, liczbaPrzetworzonychWezlow, czyPrzerwany);
        }
    }
}

void GrafManager::testForReportSimulatedAnnealing() {
    // List of file names
    vector<string> fileNames = {
        "br17", "ft53", "ft70", "ftv33", "ftv35", "ftv38", "ftv44", "ftv47", "ftv55", "ftv64",
        "ftv70", "ftv90", "ftv100", "ftv110", "ftv120", "ftv130", "ftv140", "ftv150", "ftv160",
        "ftv170", "kro124", "p43", "rbg323", "rbg358", "rbg403", "rbg443", "ry48p"
    };

    // File extension for the input files
    const string fileExtension = ".atsp";

    // CSV file to save results
    const string csvFileName = "simulated_annealing_report.csv";

    // Define constants
    const double coolingFactor = 0.99; // Cooling factor set as 0.99

    for (const auto& fileName : fileNames) {
        // Set the file name for the current graph
        string fullFileName = fileName + fileExtension;
        nazwaPliku = fullFileName;

        cout << "Testing file: " << fullFileName << endl;

        // Load the cost matrix for the current file
        if (macierzKosztow) {
            // Free the existing cost matrix if it exists
            for (size_t i = 0; i < liczbaMiast; ++i) {
                delete[] macierzKosztow[i];
            }
            delete[] macierzKosztow;
            macierzKosztow = nullptr;
        }

        macierzKosztow = czytnikGrafow.wczytajMacierz(folderRozw + fullFileName, liczbaMiast);

        if (!macierzKosztow) {
            cerr << "Blad wczytywania pliku: " << fullFileName << endl;
            continue; // Skip to the next file if loading fails
        }

        // Determine maxTime based on the size of the graph
        int maxTime = 0; // Default value
        if (liczbaMiast <= 20) {
            maxTime = 2 * 60 * 1000; // 2 minutes for small graphs
        } else if (liczbaMiast <= 100) {
            maxTime = 4 * 60 * 1000; // 4 minutes for medium graphs
        } else {
            maxTime = 6 * 60 * 1000; // 6 minutes for large graphs
        }

        // Test for each cooling type
        for (int coolingType = 1; coolingType <= 3; ++coolingType) {
            cout << "Cooling type: " << coolingType << endl;

            // Test 10 times for the given cooling type
            for (int i = 0; i < 10; ++i) {
                cout << "Iteration: " << (i + 1);

                // Prepare matrix for Simulated Annealing
                MacierzKosztow macierz(macierzKosztow, liczbaMiast);

                // Run Simulated Annealing and get results
                auto result = SimulatedAnnealing::start(macierz, coolingFactor, maxTime, coolingType);

                // Extract values from the result
                long long timeOfBestSolution = result.first.first.first;
                long long duration = result.first.first.second;
                int bestLen = result.first.second;
                double initialTemperature = result.second.first;
                int matrixSize = result.second.second;

                // Save results to CSV
                zapiszDoCSV3(csvFileName, matrixSize, duration, coolingType, initialTemperature,
                             timeOfBestSolution, bestLen, maxTime);
            }
            cout << endl;

            // Save the best path to a .txt file
            sciezka = SimulatedAnnealing::finalPath; // Update the path from static vector
            nazwaPliku = fileName + "_sw_" + to_string(coolingType) + ".txt";
            zapiszSciezkeDoPlikuTxt();
        }
    }
}
