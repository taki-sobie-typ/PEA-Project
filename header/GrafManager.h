#ifndef GRAFMANAGER_H
#define GRAFMANAGER_H

#include <iostream>
#include <string>
#include "MacierzIncydencji.h"
#include "ListaSasiedztwa.h"
#include "GeneratorGrafow.h"
#include "CzytnikGrafow.h"
#include "Prim.h"
#include "Dijkstra.h"

using namespace std;

class GrafManager {
private:
    MacierzIncydencji* macierzIncydencji;
    ListaSasiedztwa* listaSasiedztwa;
    GeneratorGrafow generatorGrafow;
    CzytnikGrafow czytnikGrafow;

public:
    GrafManager() : macierzIncydencji(nullptr), listaSasiedztwa(nullptr), czytnikGrafow("") {}
    ~GrafManager() {
        delete macierzIncydencji;
        delete listaSasiedztwa;
    }

    void wczytajDaneZPliku();
    void wygenerujGrafLosowo();
    void wyswietlGraf();
    void uruchomAlgorytmMST();
    void uruchomAlgorytmNajkrotszejSciezki();
    void uruchomTestyDoSprawozdania();
};

#endif // GRAFMANAGER_H
