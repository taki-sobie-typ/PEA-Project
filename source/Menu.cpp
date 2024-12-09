#include "../header/Menu.h"

using namespace std;

double coolingFactor = 0.99;
int maxTime = 240000;
int coolingType = 1;

// Metoda wyświetlająca główne menu programu, umożliwiająca użytkownikowi wybór opcji.
void Menu::wyswietlMenuGlowne() {

    int wybor;
    do {
        // Wyświetlenie opcji menu.
        cout << "1. Wczytaj dane z pliku" << endl;
        cout << "2. Wygeneruj graf losowo" << endl;
        cout << "3. Wyswietl graf" << endl;
        cout << "4. Ustawienia SA" << endl;
        cout << "5. SimulatedAnnealingStart" << endl;
        cout << "6. testForReportSimulatedAnnealing" << endl;
        cout << "7. pathSetup" << endl;
        cout << "8. miscAlgos" << endl;
        cout << "9. miscTests" << endl;
        cout << "0. Wyjscie" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;
        cout << endl;

        // Obsługa wyboru użytkownika przy użyciu instrukcji switch.
        switch (wybor) {
            case 1:
                wczytajDaneZPliku(); // Wywołanie metody do wczytania danych z pliku.
                break;
            case 2:
                wygenerujGrafLosowo(); // Wywołanie metody do generowania losowego grafu.
                break;
            case 3:
                wyswietlGraf(); // Wywołanie metody do wyświetlenia macierzy kosztów grafu.
                break;
            case 4:
                ustawieniaGlobalne(); // Wywołanie metody do wyświetlenia macierzy kosztów grafu.
                break;
            case 5:
                testSimulatedAnnealing(); // Wywołanie metody do uruchomienia testu algorytmu Branch and Bound.
                break;
            case 6:
                testForReportSimulatedAnnealing(); // Wywołanie metody do uruchomienia testu algorytmu dla raportu symetrycznego.
                break;
            case 7:
                setupPath(); // Wywołanie metody do uruchomienia testu algorytmu Brute Force dla raportu.
                break;
            case 8:
                wyswietlAlgoMisc(); // Wywołanie metody do uruchomienia testu algorytmu Brute Force dla raportu.
                break;
            case 9:
                wyswietlTestyMisc(); // Wywołanie metody do uruchomienia testu algorytmu B&B i BFS dla raportu.
                break;
            case 0:
                cout << "Koniec programu." << endl; // Zakończenie programu.
                break;
            default:
                cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl; // Obsługa nieprawidłowego wyboru.
        }
        cout << endl;
    } while (wybor != 0); // Pętla działa do momentu, gdy użytkownik wybierze opcję zakończenia (0).
}

// Sub-menu do ustawiania globalnych wartości
void Menu::ustawieniaGlobalne() {
    int wybor;
    do {
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
                break; // Powrót do menu głównego
            default:
                cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
        }
        cout << endl;
    } while (wybor != 0);
}

// Sub-menu do testów misc
void Menu::wyswietlTestyMisc() {
    int wybor;
    do {
        cout << "1. Test For Report Symetric" << endl;
        cout << "2. Test For Report (Brute Force)" << endl;
        cout << "3. Test For Report (B&B BFS)" << endl;
        cout << "0. Powrot do menu glownego" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;
        cout << endl;

        switch (wybor) {
            case 1:
                testForReportSymetric(); // Wywołanie metody do uruchomienia testu dla raportu symetrycznego.
                break;
            case 2:
                testForReportBF(); // Wywołanie metody do uruchomienia testu algorytmu Brute Force dla raportu.
                break;
            case 3:
                testForReportBandB_BFS(); // Wywołanie metody do uruchomienia testu algorytmu BrachAndBound i BFS dla raportu.
                break;
            case 0:
                break; // Powrót do menu głównego
            default:
                cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
        }
        cout << endl;
    } while (wybor != 0);
}


// Sub-menu do testów misc
void Menu::wyswietlAlgoMisc() {
    int wybor;
    do {
        cout << "1. Brute Test" << endl;
        cout << "2. B&B" << endl;
        cout << "0. Powrot do menu glownego" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;
        cout << endl;

        switch (wybor) {
            case 1:
                testBruteForce(); // Wywołanie metody do uruchomienia testu algorytmu Brute Force.
                break;
            case 2:
                testBranchAndBound(); // Wywołanie metody do uruchomienia testu algorytmu Branch and Bound.
                break;
            case 0:
                break; // Powrót do menu głównego
            default:
                cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
        }
        cout << endl;
    } while (wybor != 0);
}

// Sub-menu do testów misc
void Menu::setupPath() {
    int wybor;
    do {
        cout << "1. Wczytaj i oblicz sciezke" << endl;
        cout << "2. Zapisz sciezke" << endl;
        cout << "0. Powrot do menu glownego" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;
        cout << endl;

        switch (wybor) {
            case 1:
                getAndCalculatePath(); // Wywołanie metody do uruchomienia testu algorytmu Brute Force.
                break;
            case 2:
                writePath(); // Wywołanie metody do uruchomienia testu algorytmu Branch and Bound.
                break;
            case 0:
                break; // Powrót do menu głównego
            default:
                cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
        }
        cout << endl;
    } while (wybor != 0);
}

// Metoda wywołująca funkcję wczytywania danych z pliku przy użyciu obiektu grafManager.
void Menu::wczytajDaneZPliku() {
    grafManager.wczytajDaneZPliku(); // Wywołanie metody obiektu grafManager do wczytania danych.
}

// Metoda wywołująca funkcję generowania losowego grafu przy użyciu obiektu grafManager.
void Menu::wygenerujGrafLosowo() {
    grafManager.wygenerujGrafLosowo(); // Wywołanie metody obiektu grafManager do generowania grafu.
}

// Metoda wywołująca funkcję wyświetlania macierzy kosztów przy użyciu obiektu grafManager.
void Menu::wyswietlGraf() {
    grafManager.wyswietlGraf(); // Wywołanie metody obiektu grafManager do wyświetlania grafu.
}

// Metoda wywołująca funkcję uruchomienia algorytmu SimulatedAnnealing przy użyciu obiektu grafManager.
void Menu::testBranchAndBound() {
    grafManager.uruchomBranchAndBound(); // Wywołanie metody obiektu grafManager do uruchomienia algorytmu BrachAndBound.
}

// Metoda wywołująca funkcję uruchomienia algorytmu SimulatedAnnealing przy użyciu obiektu grafManager.
void Menu::testSimulatedAnnealing() {
    grafManager.uruchomSimulatedAnnealing(coolingFactor, maxTime, coolingType); // Wywołanie metody obiektu grafManager do uruchomienia algorytmu SimulatedAnnealing.
}

void Menu::writePath() {
    grafManager.zapiszSciezkeDoPlikuTxt("savedPath"); // Wywołanie metody obiektu grafManager do uruchomienia algorytmu SimulatedAnnealing.
}

void Menu::getAndCalculatePath() {
    grafManager.wczytajSciezkeZPlikuTxt("savedPath"); // Wywołanie metody obiektu grafManager do uruchomienia algorytmu SimulatedAnnealing.
}

void Menu::testForReportSimulatedAnnealing() {
    grafManager.testForReportSimulatedAnnealing(); // Wywołanie metody obiektu grafManager do uruchomienia testu dla raportu symetrycznego.
}

void Menu::testForReportSymetric() {
    grafManager.testForReportSymetric(); // Wywołanie metody obiektu grafManager do uruchomienia testu dla raportu symetrycznego.
}

// Metoda wywołująca funkcję uruchomienia algorytmu Brute Force przy użyciu obiektu grafManager.
void Menu::testBruteForce() {
    grafManager.uruchomBruteForce(); // Wywołanie metody obiektu grafManager do uruchomienia algorytmu Brute Force.
}

void Menu::testForReportBF() {
    grafManager.testForReportBF(); // Wywołanie metody obiektu grafManager do uruchomienia testu algorytmu Brute Force dla raportu.
}

void Menu::testForReportBandB_BFS() {
    grafManager.testForReportBandB_BFS(); // Wywołanie metody obiektu grafManager do uruchomienia testu algorytmu BrachAndBound i BFS dla raportu.
}
