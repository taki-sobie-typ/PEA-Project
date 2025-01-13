#include "../header/Menu.h"

using namespace std;

// Global variables for Simulated Annealing settings
double coolingFactor = 0.99;
int maxTime = 240000;
int coolingType = 1;

// Parametry algorytmu genetycznego
int populationSize = 500;        // Rozmiar populacji
int stopTime = 30;               // Czas trwania algorytmu w sekundach
double mutationRate = 0.01;       // Prawdopodobieństwo mutacji
double crossoverRate = 0.8;     // Prawdopodobieństwo krzyżowania
Mutation mutationType = inverseMut; // Typ mutacji (swap lub inversja)

// Central dispatcher for executing actions
void Menu::executeAction(Action action) {
    switch (action) {
        case LOAD_DATA:
            grafManager.wczytajDaneZPliku();
            break;
        case GENERATE_GRAPH:
            grafManager.wygenerujGrafLosowo();
            break;
        case DISPLAY_GRAPH:
            grafManager.wyswietlGraf();
            break;
        case RUN_BNB:
            grafManager.uruchomBranchAndBound();
            break;
        case RUN_SA:
            grafManager.uruchomSimulatedAnnealing(coolingFactor, maxTime, coolingType);
            break;
        case RUN_GENETIC:
            grafManager.uruchomGeneticAlgorithm(populationSize, stopTime, mutationRate, crossoverRate, mutationType);
            break;
        case WRITE_PATH:
            grafManager.zapiszSciezkeDoPlikuTxt("savedPath");
            break;
        case READ_PATH:
            grafManager.wczytajSciezkeZPlikuTxt("savedPath");
            break;
        case TEST_SA_REPORT:
            grafManager.testForReportSimulatedAnnealing();
            break;
        case TEST_SYMMETRIC_REPORT:
            grafManager.testForReportSymetric();
            break;
        case TEST_BRUTE_FORCE:
            grafManager.uruchomBruteForce();
            break;
        case TEST_BF_REPORT:
            grafManager.testForReportBF();
            break;
        case TEST_BNB_BFS_REPORT:
            grafManager.testForReportBandB_BFS();
            break;
        case TEST_GEN_REPORT:
            grafManager.testForReportGeneticAlgorithm();
            break;
        default:
            cerr << "Nieprawidlowa akcja!" << endl;
            break;
    }
}

// Main menu
void Menu::wyswietlMenuGlowne() {
    int wybor;
    do {
        cout << "\n===== MENU GLOWNE =====" << endl;
        cout << "1. Operacje na grafie" << endl;
        cout << "2. Algorytmy" << endl;
        cout << "3. Ustawienia" << endl;
        cout << "0. Wyjscie" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;
        cout << endl;

        switch (wybor) {
            case 1:
                wyswietlSubmenuGraf();
                break;
            case 2:
                wyswietlSubmenuAlgorytmy();
                break;
            case 3:
                ustawieniaGlobalne();
                break;
            case 0:
                cout << "Zamykanie programu. Do widzenia!" << endl;
                break;
            default:
                cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
        }
    } while (wybor != 0);
}

// Graph operations submenu
void Menu::wyswietlSubmenuGraf() {
    int wybor;
    do {
        cout << "\n===== OPERACJE NA GRAFIE =====" << endl;
        cout << "1. Wczytaj dane z pliku" << endl;
        cout << "2. Wygeneruj losowy graf" << endl;
        cout << "3. Wyswietl graf" << endl;
        cout << "4. Operacje na sciezce" << endl;
        cout << "0. Powrot" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;
        cout << endl;

        switch (wybor) {
            case 1:
                executeAction(LOAD_DATA);
                break;
            case 2:
                executeAction(GENERATE_GRAPH);
                break;
            case 3:
                executeAction(DISPLAY_GRAPH);
                break;
            case 4:
                setupPath();
                break;
            case 0:
                break;
            default:
                cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
        }
    } while (wybor != 0);
}

// Optimization algorithms submenu
void Menu::wyswietlSubmenuAlgorytmy() {
    int wybor;
    do {
        cout << "\n===== ALGORYTMY =====" << endl;
        cout << "1. Algorytm Simulated Annealing" << endl;
        cout << "2. Algorytm Genetyczny" << endl;
        cout << "3. Algorytm Brute Force" << endl;
        cout << "4. Algorytm Branch and Bound" << endl;
        cout << "5. Testy do raportu" << endl;
        cout << "0. Powrot" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;
        cout << endl;

        switch (wybor) {
            case 1:
                executeAction(RUN_SA);
                break;
            case 2:
                executeAction(RUN_GENETIC);
                break;
            case 3:
                executeAction(TEST_BRUTE_FORCE);
                break;
            case 4:
                executeAction(RUN_BNB);
                break;
            case 5:
                wyswietlTestyMisc();
                break;
            case 0:
                break;
            default:
                cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
        }
    } while (wybor != 0);
}

// Path operations submenu
void Menu::setupPath() {
    int wybor;
    do {
        cout << "\n===== OPERACJE NA SCIEZCE =====" << endl;
        cout << "1. Wczytaj i oblicz sciezke" << endl;
        cout << "2. Zapisz sciezke" << endl;
        cout << "0. Powrot" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;
        cout << endl;

        switch (wybor) {
            case 1:
                executeAction(READ_PATH);
                break;
            case 2:
                executeAction(WRITE_PATH);
                break;
            case 0:
                break;
            default:
                cout << "Nieprawidlowy wybur. Sprubuj ponownie." << endl;
        }
    } while (wybor != 0);
}

// Report tests submenu
void Menu::wyswietlTestyMisc() {
    int wybor;
    do {
        cout << "\n===== TESTY DLA RAPORTU =====" << endl;
        cout << "1. Test dla algorytmu Brute Force (symetrycznie)" << endl;
        cout << "2. Test dla algorytmu Brute Force" << endl;
        cout << "3. Test dla algorytmu Branch and Bound (BFS)" << endl;
        cout << "4. Test dla algorytmu Genetcznego" << endl;
        cout << "0. Powrot" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;
        cout << endl;

        switch (wybor) {
            case 1:
                executeAction(TEST_SYMMETRIC_REPORT);
                break;
            case 2:
                executeAction(TEST_BF_REPORT);
                break;
            case 3:
                executeAction(TEST_BNB_BFS_REPORT);
                break;
            case 4:
                executeAction(TEST_GEN_REPORT);
                break;
            case 0:
                break;
            default:
                cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
        }
    } while (wybor != 0);
}

//UstawieniaGlobalne Definicja
// Sub-menu do ustawiania globalnych wartosci
void Menu::ustawieniaGlobalne() {
    int wybor;
    do {
        cout << "\n===== USTAWIENIA GLOBALNE =====" << endl;
        cout << "1. Ustawienia Simulated Annealing" << endl;
        cout << "2. Ustawienia Algorytmu Genetycznego" << endl;
        cout << "0. Powrot" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;
        cout << endl;

        switch (wybor) {
            case 1:
                ustawieniaSimulatedAnnealing();
            break;
            case 2:
                ustawieniaGeneticAlgorithm();
            break;
            case 0:
                break; // Return to the main menu
            default:
                cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
        }
        cout << endl;
    } while (wybor != 0);
}

// Global Settings Menu for Simulated Annealing
void Menu::ustawieniaSimulatedAnnealing() {
    int wybor;
    do {
        cout << "\n===== USTAWIENIA SIMULATED ANNEALING =====" << endl;
        cout << "1. Ustaw Cooling Factor (aktualnie: " << coolingFactor << ")" << endl;
        cout << "2. Ustaw Max Time (aktualnie: " << maxTime << ")" << endl;
        cout << "3. Ustaw Cooling Type (aktualnie: " << coolingType << ")" << endl;
        cout << "0. Powrot" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;
        cout << endl;

        switch (wybor) {
            case 1:
                cout << "Podaj nowy Cooling Factor (np. 0.99): ";
                cin >> coolingFactor;
                break;
            case 2:
                cout << "Podaj nowy Max Time (np. 20000): ";
                cin >> maxTime;
                break;
            case 3:
                cout << "Podaj nowy Cooling Type (np. 1): ";
                cin >> coolingType;
                break;
            case 0:
                break; // Return to the main menu
            default:
                cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
        }
        cout << endl;
    } while (wybor != 0);
}

// Global Settings Menu for Genetic Algorithm
void Menu::ustawieniaGeneticAlgorithm() {
    int wybor;
    do {
        cout << "\n===== USTAWIENIA ALGORYTMU GENETYCZNEGO =====" << endl;
        cout << "1. Ustaw Population Size (aktualnie: " << populationSize << ")" << endl;
        cout << "2. Ustaw Stop Time (aktualnie: " << stopTime << ")" << endl;
        cout << "3. Ustaw Mutation Rate (aktualnie: " << mutationRate << ")" << endl;
        cout << "4. Ustaw Crossover Rate (aktualnie: " << crossoverRate << ")" << endl;
        cout << "5. Ustaw Mutation Type (aktualnie: " << (mutationType == inverseMut ? "inverse" : "swap") << ")" << endl;
        cout << "0. Powrot" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;
        cout << endl;

        switch (wybor) {
            case 1:
                cout << "Podaj nowy Population Size: ";
                cin >> populationSize;
                break;
            case 2:
                cout << "Podaj nowy Stop Time (sekundy): ";
                cin >> stopTime;
                break;
            case 3:
                cout << "Podaj nowy Mutation Rate (np. 0.01): ";
                cin >> mutationRate;
                break;
            case 4:
                cout << "Podaj nowy Crossover Rate (np. 0.8): ";
                cin >> crossoverRate;
                break;
            case 5:
                int mutationChoice;
                cout << "Wybierz Mutation Type (1 = swap, 2 = inverse): ";
                cin >> mutationChoice;
                if (mutationChoice == 1) {
                    mutationType = swapMut;
                } else if (mutationChoice == 2) {
                    mutationType = inverseMut;
                } else {
                    cout << "Nieprawidlowy wybor. Pozostawiono obecny typ mutacji." << endl;
                }
                break;
            case 0:
                break; // Return to the main menu
            default:
                cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
        }
        cout << endl;
    } while (wybor != 0);
}
