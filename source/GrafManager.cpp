#include "../header/GrafManager.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

vector<int> sciezka;  // Przechowuje ścieżkę rozwiązania (np. wynik algorytmu)
string nazwaPliku;  // Nazwa pliku do wczytania/zapisu
string folderRozw;  // Folder, do którego będą zapisywane wyniki

// Destruktor klasy GrafManager
// Zwalnia pamięć zajmowaną przez macierz kosztów, jeśli została załadowana
GrafManager::~GrafManager() {
    if (macierzKosztow) {
        for (size_t i = 0; i < liczbaMiast; ++i) {
            delete[] macierzKosztow[i];  // Usuwamy wiersze macierzy
        }
        delete[] macierzKosztow;  // Usuwamy całą macierz
    }
}

// Metoda do wczytywania danych z pliku
void GrafManager::wczytajDaneZPliku() {
    nazwaPliku;  // Zmienna do przechowania nazwy pliku
    cout << "Podaj nazwe pliku: ";
    cin >> nazwaPliku;  // Użytkownik podaje nazwę pliku
    cout << endl;

    // Zwolnij istniejącą macierz kosztów, jeśli istnieje
    if (macierzKosztow) {
        for (size_t i = 0; i < liczbaMiast; ++i) {
            delete[] macierzKosztow[i];  // Usuwamy wiersze macierzy
        }
        delete[] macierzKosztow;  // Usuwamy całą macierz
        macierzKosztow = nullptr;  // Ustawiamy wskaźnik na NULL
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
    cin >> liczbaWierzcholkow;  // Użytkownik podaje liczbę wierzchołków
    cout << "Podaj minimalna wartosc krawedzi: ";
    cin >> minWartosc;  // Minimalna wartość krawędzi
    cout << "Podaj maksymalna wartosc krawedzi: ";
    cin >> maxWartosc;  // Maksymalna wartość krawędzi
    cout << endl;

    // Wygeneruj losowy graf używając klasy GrafGenerator
    vector<vector<int>> matrix = GrafGenerator::generujLosowaMacierz(liczbaWierzcholkow, minWartosc, maxWartosc, false);

    // Zwolnij istniejącą macierz kosztów, jeśli istnieje
    if (macierzKosztow) {
        for (size_t i = 0; i < liczbaMiast; ++i) {
            delete[] macierzKosztow[i];  // Usuwamy wiersze macierzy
        }
        delete[] macierzKosztow;  // Usuwamy całą macierz
        macierzKosztow = nullptr;  // Ustawiamy wskaźnik na NULL
    }

    // Zaktualizuj liczbaMiast i zaalokuj nową macierz kosztów
    liczbaMiast = liczbaWierzcholkow;  // Aktualizujemy liczbę miast
    macierzKosztow = new int*[liczbaMiast];  // Alokujemy pamięć na nową macierz
    for (size_t i = 0; i < liczbaMiast; ++i) {
        macierzKosztow[i] = new int[liczbaMiast];  // Alokujemy pamięć na wiersze macierzy
        for (size_t j = 0; j < liczbaMiast; ++j) {
            macierzKosztow[i][j] = matrix[i][j];  // Kopiujemy wartości do nowej macierzy
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
                cout << macierzKosztow[i][j] << " ";  // Wyświetlamy wartości macierzy
            }
            cout << endl;
        }
        cout << endl;
    } else {
        cout << "Brak danych do wyswietlenia." << endl;  // Jeśli brak macierzy, wyświetlamy komunikat
    }
}

// Metoda do uruchomienia algorytmu Brute Force
void GrafManager::uruchomBruteForce() {
    if (macierzKosztow) {
        // Utwórz obiekt macierzy kosztów i uruchom algorytm Brute Force
        MacierzKosztow macierz(macierzKosztow, liczbaMiast);
        BruteForce::uruchomAlgorytm(macierz);  // Uruchamiamy algorytm Brute Force
    } else {
        cout << "Brak zaladowanej macierzy kosztow. Najpierw wczytaj lub wygeneruj graf." << endl;
    }
}

// Metoda do uruchomienia algorytmu Branch and Bound
void GrafManager::uruchomBranchAndBound() {
    if (macierzKosztow) {
        // Utwórz obiekt macierzy kosztów i uruchom algorytm
        MacierzKosztow macierz(macierzKosztow, liczbaMiast);
        BranchAndBound::uruchomAlgorytm(macierz, 300000);  // Uruchamiamy algorytm Branch and Bound
    } else {
        cout << "Brak zaladowanej macierzy kosztow. Najpierw wczytaj lub wygeneruj graf." << endl;
    }
}

// Metoda do uruchomienia algorytmu Simulated Annealing
void GrafManager::uruchomSimulatedAnnealing(double coolingFactor, int maxTime, int coolingType) {
    if (macierzKosztow) {
        MacierzKosztow macierz(macierzKosztow, liczbaMiast);

        // Uruchamiamy algorytm Simulated Annealing
        SimulatedAnnealing::start(macierz, coolingFactor, maxTime, coolingType, false);
        sciezka = SimulatedAnnealing::finalPath;  // Zapisujemy wynikową ścieżkę
    } else {
        cout << "Brak zaladowanej macierzy kosztow. Najpierw wczytaj lub wygeneruj graf." << endl;
    }
}

// Metoda do uruchomienia algorytmu genetycznego
void GrafManager::uruchomGeneticAlgorithm(int populationSize, int stopTime, double mutationRate, double crossoverRate, TypMutacji mutationType) {
    if (macierzKosztow) {
        cout << "TO JEST GENETYCZNY" << endl;
        // Utwórz obiekt macierzy kosztów
        MacierzKosztow macierz(macierzKosztow, liczbaMiast);

        /* Parametry algorytmu genetycznego
        populationSize = 600;        // Rozmiar populacji
        stopTime = 500;               // Czas trwania algorytmu w sekundach
        mutationRate = 0.01;       // Prawdopodobieństwo mutacji
        crossoverRate = 0.8;     // Prawdopodobieństwo krzyżowania
        mutationType = inverseMut; // Typ mutacji (swap lub inversja)
        */

        // Utwórz obiekt algorytmu genetycznego
        GeneticAlgorithm geneticAlgorithm(macierz);

        // Uruchom algorytm
        Osobnik bestIndividual = geneticAlgorithm.uruchom(stopTime, populationSize, mutationRate, crossoverRate, mutationType);

        // Wyświetl najlepsze znalezione rozwiązanie
        cout << "Najlepsza znaleziona sciezka: ";
        for (int city : bestIndividual.sciezka) {
            cout << city << " ";
        }
        cout << bestIndividual.sciezka[0] << " ";
        cout << endl;

        cout << "Koszt najlepszej sciezki: " << bestIndividual.koszt << endl;
    } else {
        cout << "Brak zaladowanej macierzy kosztow. Najpierw wczytaj lub wygeneruj graf." << endl;
    }
}

void GrafManager::testForReportGeneticAlgorithm() {
    // Lista rozmiarów populacji do przetestowania
    std::vector<int> populationSizes = {200, 400, 800};

    // Lista typów mutacji
    std::vector<TypMutacji> mutationTypes = {zamiana, inwersja};

    // Liczba powtórzeń dla każdego przypadku
    const int repetitions = 10;

    // Plik z wynikami ogólnymi (najkrótsza ścieżka dla każdego przypadku)
    const std::string mainGeneticCsvFile = "genetic_algorithm_report_main.csv";

    // Nagłówki dla plików CSV
    std::ofstream resultsCsv(mainGeneticCsvFile);

    // Wczytaj plik grafu ftv170.atsp
    const std::string fileName = "ftv170.atsp";

    // Wczytanie macierzy kosztów z pliku
    if (macierzKosztow) {
        for (size_t i = 0; i < liczbaMiast; ++i) {
            delete[] macierzKosztow[i];
        }
        delete[] macierzKosztow;
        macierzKosztow = nullptr;
    }
    macierzKosztow = czytnikGrafow.wczytajMacierz(fileName, liczbaMiast);

    if (!macierzKosztow) {
        std::cerr << "Nie można załadować pliku grafu: " << fileName << std::endl;
        return;
    }

    for (int populationSize : populationSizes) {

                if (resultsCsv.is_open()) {
                    resultsCsv << populationSize << "\n";
                }

        for (TypMutacji mutationType : mutationTypes) {

                if (resultsCsv.is_open()) {
                    resultsCsv << (mutationType == zamiana ? "zamiana" : "inwersja") << "\n";
                }

                // Przechowywanie poprzedniego najlepszego wyniku (dla porównania w detailedCsv)
                int previousBestLength = INT_MAX;

            for (int i = 0; i < repetitions; ++i) {

                cout << "GENETYCZNY TRWA ;" << i << ";" << mutationType << ";" << populationSize << ";" << endl;

                // Parametry algorytmu
                int stopTime = 240;               // Czas trwania algorytmu w sekundach
                double mutationRate = 0.01;       // Prawdopodobieństwo mutacji
                double crossoverRate = 0.8;      // Prawdopodobieństwo krzyżowania

                // Utwórz obiekt macierzy kosztów
                MacierzKosztow macierz(macierzKosztow, liczbaMiast);

                // Utwórz obiekt algorytmu genetycznego
                GeneticAlgorithm geneticAlgorithm(macierz);

                // Uruchom algorytm genetyczny
                Osobnik bestIndividual = geneticAlgorithm.uruchom(
                    stopTime, populationSize, mutationRate, crossoverRate, mutationType
                );

                // Zapisz wynik do pliku CSV
                if (resultsCsv.is_open()) {
                    resultsCsv << bestIndividual.koszt << "\n";
                }

                // Jeśli znaleziono lepsze rozwiązanie niż poprzednie, zapisz dane do szczegółowego CSV
                if (bestIndividual.koszt < previousBestLength) {
                    previousBestLength = bestIndividual.koszt;
                    // Plik z danymi do wykresów (znalezienie lepszego rozwiązania w czasie)
                    string mutationTypeNow = mutationType == zamiana ? "zamian" : "inwersja";

                    std::string detailedGeneticCsvFileActual = "genetic_algorithm_report_detailed_" + string(mutationTypeNow) + "_" + to_string(populationSize) + string(".csv");

                    std::ofstream detailedCsvNow(detailedGeneticCsvFileActual);

                    const auto& bestSolutions = geneticAlgorithm.pobierzNajlepszeRozwiazaniaWCzasie();
                    if (detailedCsvNow.is_open()) {
                            detailedCsvNow << "Time" << "," << "BestLength" << "\n";
                        for (const auto& solution : bestSolutions) {
                            double time = solution.first;      // Extract time (double)
                            int bestLength = solution.second;  // Extract best length (int)

                            // Write to CSV in format: double, int, \n
                            detailedCsvNow << time << "," << bestLength << "\n";
                        }
                    }
                    detailedCsvNow.close();
                }
            }
        }
    }

    resultsCsv.close();

    std::cout << "Testowanie algorytmu genetycznego zakonczone. Wyniki zapisano do plikow CSV." << std::endl;
}



// Metoda do zapisu wyników do pliku CSV
void GrafManager::zapiszDoCSV(const string& nazwaPliku, int liczbaMiast, long long czas) {
    ofstream plik(folderRozw + nazwaPliku, ios::app);  // Otwieramy plik w trybie dopisywania
    if (plik.is_open()) {
        plik << liczbaMiast << "," << czas << endl;  // Zapisujemy dane do pliku
        plik.close();  // Zamykamy plik
    } else {
        cerr << "Blad otwierania pliku do zapisu." << endl;
    }
}

// Metoda do zapisu szczegółowych wyników do pliku CSV
void GrafManager::zapiszDoCSV2(const string& nazwaPliku, int liczbaMiast, long long czas, int procent, int czyprzerwany) {
    ofstream plik(folderRozw + nazwaPliku, ios::app);  // Otwieramy plik w trybie dopisywania
    if (plik.is_open()) {
        plik << liczbaMiast << "," << czas << "," << procent << "," << czyprzerwany << endl;  // Zapisujemy dane do pliku
        plik.close();  // Zamykamy plik
    } else {
        cerr << "Blad otwierania pliku do zapisu." << endl;
    }
}

// Funkcja zapisująca wyniki algorytmu do pliku CSV
void GrafManager::zapiszDoCSV3(const string& csvFileName,
                              int size,
                              long long duration,
                              int coolingType,
                              double beginningTemperature,
                              long long timeOfBestSolution,
                              int bestLen,
                              int maxRunTime) {
    ofstream plik(csvFileName, ios::app); // Otwieranie pliku CSV w trybie dopisywania
    if (plik.is_open()) {
        // Zapisuje wyniki do pliku w odpowiednich kolumnach
        plik << size << "," // Rozmiar macierzy
             << duration << "," // Czas trwania obliczeń
             << coolingType << "," // Typ schładzania (np. geometryczne, logarytmiczne, wykładnicze)
             << beginningTemperature << "," // Początkowa temperatura
             << timeOfBestSolution << "," // Czas, w którym znaleziono najlepsze rozwiązanie
             << bestLen << "," // Długość najlepszego rozwiązania (najkrótsza ścieżka)
             << maxRunTime << "\n"; // Maksymalny czas wykonania algorytmu

        plik.close(); // Zamknięcie pliku po zapisaniu
        cout << "Detailed data appended to CSV file: " << csvFileName << endl;
    } else {
        cerr << "Error opening CSV file for writing." << endl; // Błąd otwarcia pliku
    }
}

// Funkcja zapisująca ścieżkę rozwiązania do pliku txt
void GrafManager::zapiszSciezkeDoPlikuTxt(string txtFileName) {
    ofstream plik(folderRozw + "sw_" + txtFileName, std::ios::trunc);  // Otwieranie pliku do zapisu, w trybie nadpisywania
    if (plik.is_open()) {
        int liczbaMiast = sciezka.size();  // Liczba miast w rozwiązaniu
        plik << liczbaMiast << endl;  // Zapisuje liczbę miast na pierwszej linii

        // Zapisuje każdą miasto w ścieżce (w tym pierwsze miasto na końcu, aby utworzyć cykl)
        for (size_t i = 0; i < sciezka.size(); ++i) {
            plik << sciezka[i] << endl;  // Zapisuje miasto w każdej linii
        }

        cout << "Sciezka zostala zapisana do pliku: " << txtFileName << endl; // Potwierdzenie zapisu
        plik.close(); // Zamknięcie pliku
    } else {
        cerr << "Blad otwierania pliku do zapisu." << endl; // Błąd otwarcia pliku
    }
}

// Funkcja wczytująca ścieżkę rozwiązania z pliku txt i obliczająca koszt
int GrafManager::wczytajSciezkeZPlikuTxt(const string& nazwaPliku) {
    ifstream plik(folderRozw + "sw_" + nazwaPliku);  // Otwieranie pliku do odczytu
    vector<int> sciezka;
    int miasto;

    if (plik.is_open()) {
        int liczbaMiast;
        plik >> liczbaMiast;  // Wczytanie liczby miast z pierwszej linii

        // Wczytuje kolejne miasta w ścieżce
        while (plik >> miasto) {
            sciezka.push_back(miasto); // Dodaje miasto do wektora
        }
        plik.close();

        // Sprawdza, czy ścieżka jest cykliczna (pierwsze miasto musi być takie samo jak ostatnie)
        if (!sciezka.empty() && sciezka.front() != sciezka.back()) {
            sciezka.push_back(sciezka.front());  // Uzupełnia cykl, dodając pierwsze miasto na koniec
        }

        // Oblicza całkowity koszt ścieżki na podstawie macierzy kosztów
        int totalCost = 0;
        for (size_t i = 0; i < sciezka.size() - 1; ++i) {
            int start = sciezka[i];
            int end = sciezka[i + 1];
            if (start < liczbaMiast && end < liczbaMiast) {
                totalCost += macierzKosztow[start][end];  // Sumuje koszty między miastami
            }
        }

        cout << "Koszt sciezki: " << totalCost << endl; // Wyświetla koszt ścieżki
        return totalCost;
    } else {
        cerr << "Blad otwierania pliku do odczytu." << endl; // Błąd otwarcia pliku
        return -1;  // Zwraca -1, jeśli plik nie został otwarty
    }
}

// Funkcja testująca dla raportu, algorytm brute force
void GrafManager::testForReportBF() {
    string nazwaPlikuCSV = "bruteforce_report.csv";

    for (int rozmiar = 5; rozmiar <= 15; ++rozmiar) {
        for (int i = 0; i < 50; ++i) {
            // Generuje nowy losowy graf o rozmiarze "rozmiar"
            vector<vector<int>> matrix = GrafGenerator::generujLosowaMacierz(rozmiar, 1, 100, false);  // Zakres wartości krawędzi: 1-100

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
                    macierzKosztow[j][k] = matrix[j][k];  // Kopiuje dane z macierzy do macierzy kosztów
                }
            }

            // Uruchomienie algorytmu brute force i zmierzenie czasu wykonania
            MacierzKosztow macierz(macierzKosztow, liczbaMiast);
            long long czasTrwania = BruteForce::uruchomAlgorytm(macierz);

            // Zapisanie wyniku do pliku CSV
            zapiszDoCSV(nazwaPlikuCSV, liczbaMiast, czasTrwania);
        }
    }
}

// Funkcja testująca algorytm Branch and Bound dla losowych grafów nieliniowych
void GrafManager::testForReportBandB_BFS() {
    string nazwaPlikuCSV = "b&b_BFS_report_p.csv";  // Nazwa pliku, do którego będą zapisywane wyniki

    // Pętla po różnych rozmiarach grafów (od 4 do 30)
    for (int rozmiar = 4; rozmiar <= 30; ++rozmiar) {
        int rozmiarInner = 20;  // Ustawienie liczby prób dla danego rozmiaru grafu
        if (rozmiar > 12) {
            rozmiarInner = 20;
        }
        if (rozmiar > 14) {
            rozmiarInner = 20;
        }
        if (rozmiar > 16) {
            rozmiarInner = 5;  // Zmniejszenie liczby prób dla większych rozmiarów
        }

        // Pętla wykonująca testy dla danego rozmiaru grafu
        for (int i = 0; i < rozmiarInner; ++i) {
            // Generowanie losowego grafu o rozmiarze "rozmiar"
            vector<vector<int>> matrix = GrafGenerator::generujLosowaMacierz(rozmiar, 1, 100, false);

            // Zwolnienie pamięci zajmowanej przez poprzednią macierz kosztów (jeśli istnieje)
            if (macierzKosztow) {
                for (size_t i = 0; i < liczbaMiast; ++i) {
                    delete[] macierzKosztow[i];
                }
                delete[] macierzKosztow;
            }

            liczbaMiast = rozmiar;  // Ustawienie liczby miast na rozmiar grafu
            macierzKosztow = new int*[liczbaMiast];  // Alokacja pamięci dla nowej macierzy kosztów
            for (size_t j = 0; j < liczbaMiast; ++j) {
                macierzKosztow[j] = new int[liczbaMiast];
                for (size_t k = 0; k < liczbaMiast; ++k) {
                    macierzKosztow[j][k] = matrix[j][k];  // Kopiowanie wartości z wygenerowanego grafu
                }
            }

            // Uruchomienie algorytmu Branch and Bound i zmierzenie czasu wykonania
            MacierzKosztow macierz(macierzKosztow, liczbaMiast);
            auto [result, czyPrzerwany] = BranchAndBound::uruchomAlgorytm(macierz, 300000);
            auto [czasTrwania, liczbaPrzetworzonychWezlow] = result;

            // Zapisanie wyników do pliku CSV
            zapiszDoCSV2(nazwaPlikuCSV, liczbaMiast, czasTrwania, liczbaPrzetworzonychWezlow, czyPrzerwany);
        }
    }
}

// Funkcja testująca algorytm Branch and Bound dla losowych grafów symetrycznych
void GrafManager::testForReportSymetric() {
    string nazwaPlikuCSV = "b&b_BFS_report_s_p.csv";  // Nazwa pliku do zapisu wyników

    // Pętla po różnych rozmiarach grafów (od 4 do 30)
    for (int rozmiar = 4; rozmiar <= 30; ++rozmiar) {
        int rozmiarInner = 20;  // Ustawienie liczby prób dla danego rozmiaru grafu
        if (rozmiar > 12) {
            rozmiarInner = 20;
        }
        if (rozmiar > 14) {
            rozmiarInner = 20;
        }
        if (rozmiar > 16) {
            rozmiarInner = 5;  // Zmniejszenie liczby prób dla większych rozmiarów
        }

        // Pętla wykonująca testy dla danego rozmiaru grafu
        for (int i = 0; i < rozmiarInner; ++i) {
            // Generowanie losowego grafu symetrycznego
            vector<vector<int>> matrix = GrafGenerator::generujLosowaMacierz(rozmiar, 1, 99, true);  // Generowanie symetrycznej macierzy kosztów

            // Zwolnienie pamięci zajmowanej przez poprzednią macierz kosztów (jeśli istnieje)
            if (macierzKosztow) {
                for (size_t i = 0; i < liczbaMiast; ++i) {
                    delete[] macierzKosztow[i];
                }
                delete[] macierzKosztow;
            }

            liczbaMiast = rozmiar;  // Ustawienie liczby miast na rozmiar grafu
            macierzKosztow = new int*[liczbaMiast];  // Alokacja pamięci dla nowej macierzy kosztów
            for (size_t j = 0; j < liczbaMiast; ++j) {
                macierzKosztow[j] = new int[liczbaMiast];
                for (size_t k = 0; k < liczbaMiast; ++k) {
                    macierzKosztow[j][k] = matrix[j][k];  // Kopiowanie wartości z wygenerowanego grafu
                }
            }

            // Uruchomienie algorytmu Branch and Bound i zmierzenie czasu wykonania
            MacierzKosztow macierz(macierzKosztow, liczbaMiast);
            auto [result, czyPrzerwany] = BranchAndBound::uruchomAlgorytm(macierz, 300000);
            auto [czasTrwania, liczbaPrzetworzonychWezlow] = result;

            // Zapisanie wyników do pliku CSV
            zapiszDoCSV2(nazwaPlikuCSV, liczbaMiast, czasTrwania, liczbaPrzetworzonychWezlow, czyPrzerwany);
        }
    }
}

// Funkcja testująca algorytm symulowanego wyżarzania dla różnych plików grafów
void GrafManager::testForReportSimulatedAnnealing() {
    // Lista nazw plików wejściowych, które będą testowane
    vector<string> fileNames = {
        "ftv55", "ftv170", "rbg358"
    };

    // Rozszerzenie plików wejściowych (np. .atsp)
    const string fileExtension = ".atsp";

    // Nazwa pliku CSV, do którego będą zapisywane wszystkie wyniki
    const string csvFileName = "simulated_annealing_report.csv";

    // Flaga do dodania nagłówka tylko raz na początku
    bool headerAdded = false;

    // Zmienna do przechowywania poprzedniej najlepszej długości ścieżki
    int previousBestLen = INT_MAX;

    // Pętla po wszystkich plikach z listy
    for (const auto& fileName : fileNames) {
        // Tworzenie pełnej nazwy pliku do odczytu
        string fullFileName = fileName + fileExtension;
        nazwaPliku = fullFileName;

        // Dodanie nagłówka do pliku CSV (tylko raz na początku)
        if (!headerAdded) {
            ofstream csvFile(csvFileName, ios::app);
            if (csvFile.is_open()) {
                csvFile << "Matrix Size,Duration,Cooling Type,Final Temperature,"
                           "Time Of Best Solution,Best Path Length,Max Time\n";
                csvFile.close();
                headerAdded = true;
            }
        }

        // Zapisanie nazwy pliku do CSV (przed rozpoczęciem testów)
        cout << "Testing file: " << fullFileName << endl;
        ofstream csvFile(csvFileName, ios::app);
        if (csvFile.is_open()) {
            csvFile << fullFileName << "\n";
            csvFile.close();
        }

        // Wczytanie macierzy kosztów z pliku
        if (macierzKosztow) {
            for (size_t i = 0; i < liczbaMiast; ++i) {
                delete[] macierzKosztow[i];
            }
            delete[] macierzKosztow;
            macierzKosztow = nullptr;
        }
        macierzKosztow = czytnikGrafow.wczytajMacierz(fullFileName, liczbaMiast);

        if (!macierzKosztow) {
            cerr << "Error loading file: " << fullFileName << endl;
            continue;
        }

        // Określenie maksymalnego czasu trwania algorytmu w zależności od liczby miast
        int maxTime = 0;
        if (liczbaMiast <= 100) {
            maxTime = 2 * 60 * 1000; // 2 minuty
        } else if (liczbaMiast <= 200) {
            maxTime = 4 * 60 * 1000; // 4 minuty
        } else {
            maxTime = 6 * 60 * 1000; // 6 minut
        }

        // Pętla po różnych typach schładzania
        for (int coolingType = 1; coolingType <= 3; ++coolingType) {
            // Określenie współczynnika schładzania w zależności od typu
            double coolingFactor = 0.0;
            if (coolingType == 1) {
                coolingFactor = 0.99; // Geometric cooling
            } else if (coolingType == 2) {
                coolingFactor = 0.001; // Logarithmic cooling
            } else if (coolingType == 3) {
                coolingFactor = 0.9999; // Exponential cooling
            }

            previousBestLen = INT_MAX; // Resetowanie poprzedniej najlepszej długości

            cout << "Cooling type: " << coolingType << ", Cooling factor: " << coolingFactor << endl;

            // Wykonywanie 10 iteracji dla danego typu schładzania
            for (int i = 0; i < 10; ++i) {
                cout << "Iteration: " << (i + 1) << endl;

                // Przygotowanie macierzy dla algorytmu
                MacierzKosztow macierz(macierzKosztow, liczbaMiast);

                // Uruchomienie algorytmu Simulated Annealing
                auto result = SimulatedAnnealing::start(macierz, coolingFactor, maxTime, coolingType, true);

                // Wyciąganie wyników z algorytmu
                long long timeOfBestSolution = result.first.first.first;
                long long duration = result.first.first.second;
                int bestLen = result.first.second;
                double initialTemperature = result.second.first;
                int matrixSize = result.second.second;

                // Zapis wyników do pliku CSV
                zapiszDoCSV3(csvFileName, matrixSize, duration, coolingType, initialTemperature,
                             timeOfBestSolution, bestLen, maxTime);

                // Zapisanie wyników do osobnego pliku dla najlepszej ścieżki
                if (bestLen < previousBestLen) {
                    previousBestLen = bestLen;

                    // Generowanie nazwy pliku do zapisania wektorów
                    string baseFileName = fileName + "c_type_" + to_string(coolingType) + "_best_path";

                    // Zapisuje wektory najlepszego rozwiązania do pliku
                    ofstream bestVectorsFile("rozw/" + baseFileName + "__vectors.txt", ios::trunc);

                    if (bestVectorsFile.is_open()) {
                        // Zapis wykresów najlepszych długości
                        for (size_t i = 0; i < SimulatedAnnealing::wykresBestLengths.size(); ++i) {
                            bestVectorsFile << SimulatedAnnealing::wykresBestLengths[i];
                            if (i != SimulatedAnnealing::wykresBestLengths.size() - 1) {
                                bestVectorsFile << ",";
                            }
                        }
                        bestVectorsFile << "\n";  // Nowa linia po wykresBestLengths
                    }

                    if (bestVectorsFile.is_open()) {
                        // Zapis wykresów aktualnej temperatury
                        for (size_t i = 0; i < SimulatedAnnealing::wykresCurrentTemperature.size(); ++i) {
                            bestVectorsFile << SimulatedAnnealing::wykresCurrentTemperature[i];
                            if (i != SimulatedAnnealing::wykresCurrentTemperature.size() - 1) {
                                bestVectorsFile << ",";
                            }
                        }
                        bestVectorsFile << "\n";  // Nowa linia po wykresCurrentTemperature
                    }

                    if (bestVectorsFile.is_open()) {
                        // Zapis wykresów czasów najlepszych długości
                        for (size_t i = 0; i < SimulatedAnnealing::wykresCzasyOfBestLengths.size(); ++i) {
                            bestVectorsFile << SimulatedAnnealing::wykresCzasyOfBestLengths[i];
                            if (i != SimulatedAnnealing::wykresCzasyOfBestLengths.size() - 1) {
                                bestVectorsFile << ",";
                            }
                        }
                        bestVectorsFile << "\n";  // Nowa linia po wykresCzasyOfBestLengths
                    }

                    bestVectorsFile.close();

                    // Zapisanie najlepszej ścieżki do pliku TXT
                    sciezka = SimulatedAnnealing::finalPath; // Aktualizacja ścieżki z wektora statycznego
                    string txtFileName = baseFileName;
                    zapiszSciezkeDoPlikuTxt(txtFileName); // Zapisanie ścieżki do pliku TXT
                }
            }
        }
    }
}
