#include "../header/BranchAndBound.h"
#include <iostream>
#include <climits>
#include <chrono>
#include <vector>

using namespace std;

long long BranchAndBound::uruchomAlgorytm(const MacierzKosztow& macierz) {
    int** tablicaKosztow = macierz.pobierzMacierzKosztow();
    int liczbaMiast = macierz.pobierzLiczbeMiast();

    auto czasStart = chrono::high_resolution_clock::now();

    int najnizszyKoszt = INT_MAX;
    int aktualnyKoszt;
    int* optymalnaSciezka = new int[liczbaMiast];
    optymalnaSciezka[0] = 0;

    vector<Node> kolejka;
    Node root;
    root.sciezka = new int[6];
    root.sciezka[0] = 0;
    root.sciezkaCount = 0;
    root.koszt = 0;
    root.poziom = 0;

    kolejka.push_back(root);

    while (!kolejka.empty()) {
        Node aktualnyNode = kolejka.front();
        kolejka.erase(kolejka.begin());

        // Przycinamy gałęzie, jeśli aktualny koszt jest większy lub równy minimalnemu kosztowi
        if (aktualnyNode.koszt >= najnizszyKoszt) {
            continue;
        }

        if (aktualnyNode.poziom == liczbaMiast - 1) {
            int kosztPowrotu = tablicaKosztow[aktualnyNode.sciezka[aktualnyNode.sciezkaCount]][0];
            if (kosztPowrotu != -1) {
                int kosztCalkowity = aktualnyNode.koszt + kosztPowrotu;
                if (kosztCalkowity < najnizszyKoszt) {
                    najnizszyKoszt = kosztCalkowity;
                    optymalnaSciezka = aktualnyNode.sciezka;
                    optymalnaSciezka[aktualnyNode.sciezkaCount + 1] = 0;
                }
            }
            continue;
        }

        for (int i = 0; i < liczbaMiast; ++i) {
            if (!miastoZawarteSciezka(aktualnyNode.sciezka, aktualnyNode.sciezkaCount, i)) {
                int aktualnyKoszt = tablicaKosztow[aktualnyNode.sciezka[aktualnyNode.sciezkaCount]][i];
                if (aktualnyKoszt != -1) {
                    Node potomek;
                    potomek.sciezka = aktualnyNode.sciezka;
                    potomek.sciezkaCount = aktualnyNode.sciezkaCount + 1;
                    potomek.sciezka[potomek.sciezkaCount] = i;
                    potomek.poziom = aktualnyNode.poziom + 1;
                    potomek.koszt = aktualnyNode.koszt + aktualnyKoszt;

                    if (potomek.koszt < najnizszyKoszt) {
                        kolejka.push_back(potomek);
                    }
                }
            }
        }
    }


    auto czasStop = chrono::high_resolution_clock::now();
    auto czasTrwania = chrono::duration_cast<chrono::microseconds>(czasStop - czasStart);

    cout << "Najkorzystniejsza trasa: 0 -> ";
    for (int z = 1; z < liczbaMiast; z++) {
        cout << optymalnaSciezka[z] << " -> ";
    }
    cout << "0" << endl;

    cout << "Najnizszy koszt przejscia: " << najnizszyKoszt << endl;
    cout << "Czas dzialania algorytmu pelnego przegladu: " << czasTrwania.count() << " mikrosekund" << endl;

    delete[] optymalnaSciezka;

    return czasTrwania.count();
}


bool BranchAndBound::miastoZawarteSciezka(int* sciezka, int sciezkaCount, int miasto) {
    for (int i = 0; i < sciezkaCount; ++i) {
        if (sciezka[i] == miasto) {
            return true;
        }
    }
    return false;
}