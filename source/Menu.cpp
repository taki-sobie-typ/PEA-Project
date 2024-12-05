#include "../header/Menu.h"

using namespace std;

// Metoda wyświetlająca główne menu programu, umożliwiająca użytkownikowi wybór opcji.
void Menu::wyswietlMenuGlowne() {
    int wybor;
    do {
        // Wyświetlenie opcji menu.
        cout << "1. Wczytaj dane z pliku" << endl;
        cout << "2. Wygeneruj graf losowo" << endl;
        cout << "3. Wyswietl graf" << endl;
        cout << "4. Brute Test" << endl;
        cout << "5. B&B" << endl;
        cout << "6. SimulatedAnnealing" << endl;
        cout << "7. Test For Report Symetric" << endl;
        cout << "8. Test For Report (Brute Force)" << endl;
        cout << "9. Test For Report (B&B BFS)" << endl;
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
                testBruteForce(); // Wywołanie metody do uruchomienia testu algorytmu Brute Force.
                break;
            case 5:
                testBranchAndBound(); // Wywołanie metody do uruchomienia testu algorytmu Branch and Bound.
                break;
            case 6:
                testSimulatedAnnealing(); // Wywołanie metody do uruchomienia testu algorytmu Branch and Bound.
                break;
            case 7:
                testForReportSymetric(); // Wywołanie metody do uruchomienia testu algorytmu dla raportu symetrycznego.
                break;
            case 8:
                testForReportBF(); // Wywołanie metody do uruchomienia testu algorytmu Brute Force dla raportu.
                break;
            case 9:
                testForReportBandB_BFS(); // Wywołanie metody do uruchomienia testu algorytmu B&B i BFS dla raportu.
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
    grafManager.uruchomSimulatedAnnealing(); // Wywołanie metody obiektu grafManager do uruchomienia algorytmu SimulatedAnnealing.
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
