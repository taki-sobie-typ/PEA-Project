#include "../header/Menu.h"

using namespace std;

void Menu::wyswietlMenuGlowne() {
    int wybor;
    do {
        cout << "1. Wczytaj dane z pliku" << endl;
        cout << "2. Wygeneruj graf losowo" << endl;
        cout << "3. Wyswietl graf" << endl;
        cout << "4. Wyjscie" << endl;
        cout << "5. Brute Test" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;
        cout << endl;

        switch (wybor) {
            case 1:
                wczytajDaneZPliku();
                break;
            case 2:
                wygenerujGrafLosowo();
                break;
            case 3:
                wyswietlGraf();
                break;
            case 4:
                cout << "Koniec programu." << endl;
                break;
            case 5:
                testBruteForce();
                break;
            default:
                cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
        }
        cout << endl;
    } while (wybor != 6);
}

void Menu::wczytajDaneZPliku() {
    grafManager.wczytajDaneZPliku();
}

void Menu::wygenerujGrafLosowo() {
    grafManager.wygenerujGrafLosowo();
}

void Menu::wyswietlGraf() {
    grafManager.wyswietlGraf();
}

void Menu::testBruteForce() {
    grafManager.uruchomBruteForce(0);
}
