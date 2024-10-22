#include "../header/GrafManager.h"

void GrafManager::wczytajDaneZPliku() {
    string nazwaPliku;
    cout << "Podaj nazwe pliku: ";
    cin >> nazwaPliku;
    cout << endl;

    macierzIncydencji = czytnikGrafow.wczytajMacierz(nazwaPliku);
    listaSasiedztwa = czytnikGrafow.wczytajListe(nazwaPliku);

    if (macierzIncydencji && listaSasiedztwa) {
        cout << "Dane zostaly wczytane pomyslnie." << endl;
    } else {
        cout << "Blad wczytywania danych." << endl;
    }
    cout << endl;
}

void GrafManager::wygenerujGrafLosowo() {
    size_t liczbaWierzcholkow;
    float gestosc;
    size_t maxWartosc;

    cout << "Podaj liczbe wierzcholkow: ";
    cin >> liczbaWierzcholkow;
    cout << "Podaj gestosc grafu (w %): ";
    cin >> gestosc;
    cout << "Podaj maksymalna wartosc krawedzi: ";
    cin >> maxWartosc;
    cout << endl;

    SuroweDaneGrafu dane = generatorGrafow.generuj(gestosc / 100.0, liczbaWierzcholkow, maxWartosc);

    macierzIncydencji = new MacierzIncydencji(dane.liczbaKrawedzi, dane.liczbaWierzcholkow, dane.dane);
    listaSasiedztwa = new ListaSasiedztwa(dane.liczbaKrawedzi, dane.liczbaWierzcholkow, dane.dane);

    delete[] dane.dane;

    cout << "Graf zostal wygenerowany pomyslnie." << endl;
    cout << endl;
}

void GrafManager::wyswietlGraf() {
    if (macierzIncydencji) {
        cout << "Macierz Incydencji:" << endl;
        macierzIncydencji->drukuj(cout);
        cout << endl;
    }

    if (listaSasiedztwa) {
        cout << "Lista Sasiedztwa:" << endl;
        listaSasiedztwa->drukuj(cout);
        cout << endl;
    }
}

void GrafManager::uruchomAlgorytmMST() {
    if (!macierzIncydencji || !listaSasiedztwa) {
        cout << "Graf nie zostal wczytany ani wygenerowany." << endl;
        cout << endl;
        return;
    }

    Prim prim;
    cout << "Wybierz reprezentacje grafu:" << endl;
    cout << "1. Macierz Incydencji" << endl;
    cout << "2. Lista Sasiedztwa" << endl;
    cout << "Wybierz opcje: ";
    int wybor;
    cin >> wybor;
    cout << endl;

    if (wybor == 1) {
        prim.uruchomDlaMacierzy(*macierzIncydencji);
    } else {
        prim.uruchomDlaListy(*listaSasiedztwa);
    }
}

void GrafManager::uruchomAlgorytmNajkrotszejSciezki() {
    if (!macierzIncydencji || !listaSasiedztwa) {
        cout << "Graf nie zostal wczytany ani wygenerowany." << endl;
        cout << endl;
        return;
    }

    int start, koniec;
    cout << "Podaj wierzcholek startowy: ";
    cin >> start;
    cout << "Podaj wierzcholek koncowy: ";
    cin >> koniec;
    cout << endl;

    Dijkstra dijkstra;
    cout << "Wybierz reprezentacje grafu:" << endl;
    cout << "1. Macierz Incydencji" << endl;
    cout << "2. Lista Sasiedztwa" << endl;
    cout << "Wybierz opcje: ";
    int wybor;
    cin >> wybor;
    cout << endl;

    if (wybor == 1) {
        dijkstra.uruchomDlaMacierzy(*macierzIncydencji, start);
    } else {
        dijkstra.uruchomDlaListy(*listaSasiedztwa, start);
    }
}

void GrafManager::uruchomTestyDoSprawozdania() {

}