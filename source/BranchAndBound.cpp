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
    int* optymalnaSciezka = new int[liczbaMiast + 1];

    std::vector<Node> kolejka;

    Node root;
    root.sciezka = new int[liczbaMiast + 1];
    root.sciezka[0] = 0;
    root.sciezkaCount = 1;
    root.koszt = 0;
    root.poziom = 0;

    kolejka.push_back(root);

    while (!kolejka.empty()) {
        Node aktualnyNode = kolejka.front();
        kolejka.erase(kolejka.begin());

        if (aktualnyNode.koszt >= najnizszyKoszt) {
            delete[] aktualnyNode.sciezka;
            continue;
        }

        if (aktualnyNode.poziom == liczbaMiast - 1) {
            int kosztPowrotu = tablicaKosztow[aktualnyNode.sciezka[aktualnyNode.sciezkaCount - 1]][0];
            if (kosztPowrotu != -1) {
                int kosztCalkowity = aktualnyNode.koszt + kosztPowrotu;
                if (kosztCalkowity < najnizszyKoszt) {
                    najnizszyKoszt = kosztCalkowity;
                    for (int i = 0; i < aktualnyNode.sciezkaCount; ++i) {
                        optymalnaSciezka[i] = aktualnyNode.sciezka[i];
                    }
                    optymalnaSciezka[aktualnyNode.sciezkaCount] = 0;
                }
            }
            delete[] aktualnyNode.sciezka;
            continue;
        }

        for (int i = 0; i < liczbaMiast; ++i) {

            if (!miastoZawarteSciezka(aktualnyNode.sciezka, aktualnyNode.sciezkaCount, i)) {
                int kosztPrzejscia = tablicaKosztow[aktualnyNode.sciezka[aktualnyNode.sciezkaCount - 1]][i];
                if (kosztPrzejscia != -1) {
                    Node potomek;
                    potomek.sciezka = new int[liczbaMiast + 1];
                    std::copy(aktualnyNode.sciezka, aktualnyNode.sciezka + aktualnyNode.sciezkaCount, potomek.sciezka);
                    potomek.sciezka[aktualnyNode.sciezkaCount] = i;
                    potomek.sciezkaCount = aktualnyNode.sciezkaCount + 1;
                    potomek.koszt = aktualnyNode.koszt + kosztPrzejscia;
                    potomek.poziom = aktualnyNode.poziom + 1;

                    if (potomek.koszt < najnizszyKoszt) {
                        kolejka.push_back(potomek);
                    } else {
                        delete[] potomek.sciezka;
                    }
                }
            }
        }

        delete[] aktualnyNode.sciezka;
    }

    auto czasStop = chrono::high_resolution_clock::now();
    auto czasTrwania = chrono::duration_cast<chrono::microseconds>(czasStop - czasStart);

    std::cout << "Najkorzystniejsza trasa: 0 -> ";
    for (int i = 1; i < liczbaMiast; ++i) {
        std::cout << optymalnaSciezka[i] << " -> ";
    }
    std::cout << "0\n";

    std::cout << "Najnizszy koszt przejscia: " << najnizszyKoszt << "\n";
    std::cout << "Czas dzialania algorytmu: " << czasTrwania.count() << " mikrosekund\n";

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