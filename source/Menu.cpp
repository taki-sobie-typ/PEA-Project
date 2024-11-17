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
        cout << "6. Test For Report (Brute Force)" << endl;
        cout << "7. Test For Report (B&B BFS)" << endl;
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
                testBranchAndBound(); // Wywołanie metody do uruchomienia testu algorytmu Brute Force.
                break;
            case 6:
                testForReportBF(); // Wywołanie metody do uruchomienia testu algorytmu Brute Force.
                break;
            case 7:
                testForReportBandB_BFS(); // Wywołanie metody do uruchomienia testu algorytmu Brute Force.
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
    grafManager.wczytajDaneZPliku();
}

// Metoda wywołująca funkcję generowania losowego grafu przy użyciu obiektu grafManager.
void Menu::wygenerujGrafLosowo() {
    grafManager.wygenerujGrafLosowo();
}

// Metoda wywołująca funkcję wyświetlania macierzy kosztów przy użyciu obiektu grafManager.
void Menu::wyswietlGraf() {
    grafManager.wyswietlGraf();
}

// Metoda wywołująca funkcję uruchomienia algorytmu Brute Force przy użyciu obiektu grafManager.
void Menu::testBranchAndBound() {
    grafManager.uruchomBranchAndBound();
}

// Metoda wywołująca funkcję uruchomienia algorytmu Brute Force przy użyciu obiektu grafManager.
void Menu::testBruteForce() {
    grafManager.uruchomBruteForce();
}

void Menu::testForReportBF() {
    grafManager.testForReportBF();
}

void Menu::testForReportBandB_BFS() {
    grafManager.testForReportBandB_BFS();
}
