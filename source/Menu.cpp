#include "../header/Menu.h"

using namespace std;

// Global variables for Simulated Annealing settings
double coolingFactor = 0.99;
int maxTime = 240000;
int coolingType = 1;

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
            grafManager.uruchomGeneticAlgorithm();
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
        cout << "2. Algorytmy optymalizacyjne" << endl;
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
        cout << "0. Powrut do menu gluwnego" << endl;
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
        cout << "1. Simulated Annealing" << endl;
        cout << "2. Algorytm Genetyczny" << endl;
        cout << "3. Algorytm Brute Force" << endl;
        cout << "4. Branch and Bound" << endl;
        cout << "5. Testy dla raportu" << endl;
        cout << "0. Powrut do menu gluwnego" << endl;
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
        cout << "\n===== OPERACJE NA ŚCIEŻCE =====" << endl;
        cout << "1. Wczytaj i oblicz sciezke" << endl;
        cout << "2. Zapisz sciezke" << endl;
        cout << "0. Powrut do menu gluwnego" << endl;
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
        cout << "1. Test dla grafu symetrycznego" << endl;
        cout << "2. Test dla algorytmu Brute Force" << endl;
        cout << "3. Test dla algorytmu Branch and Bound (BFS)" << endl;
        cout << "4. Test dla algorytmu Genetcznego" << endl;
        cout << "0. Powrut do menu gluwnego" << endl;
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
                cout << "Nieprawidlowy wybur. Sprubuj ponownie." << endl;
        }
    } while (wybor != 0);
}

//UstawieniaGlobalne Definicja
// Sub-menu do ustawiania globalnych wartosci
void Menu::ustawieniaGlobalne() {
    int wybor;
    do {
        cout << "\n===== USTAWIENIA GLOBALNE =====" << endl;
        cout << "1. Ustaw Cooling Factor (aktualnie: " << coolingFactor << ")" << endl;
        cout << "2. Ustaw Max Time (aktualnie: " << maxTime << ")" << endl;
        cout << "3. Ustaw Cooling Type (aktualnie: " << coolingType << ")" << endl;
        cout << "0. Powrot do menu glownego" << endl;
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
                break; // Powrut do menu gluwnego
            default:
                cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
        }
        cout << endl;
    } while (wybor != 0);
}
