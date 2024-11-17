#include "../header/BranchAndBound.h"
#include <iostream>
#include <climits>
#include <chrono>
#include <vector>
#include <queue>

using namespace std;

long long BranchAndBound::uruchomAlgorytm(const MacierzKosztow& macierz) {
    int** tablicaKosztow = macierz.pobierzMacierzKosztow();
    int liczbaMiast = macierz.pobierzLiczbeMiast();

    auto czasStart = chrono::high_resolution_clock::now();

    int najnizszyKoszt = INT_MAX;
    int* optymalnaSciezka = new int[liczbaMiast + 1];

    // Priority queue for B&B (min-heap based on cost + lower bound)
    auto compare = [](const Node& a, const Node& b) {
        return a.koszt > b.koszt; // Min-heap
    };
    std::priority_queue<Node, std::vector<Node>, decltype(compare)> kolejka(compare);

    // Root node initialization
    Node root;
    root.sciezka = new int[liczbaMiast + 1];
    root.sciezka[0] = 0;
    root.sciezkaCount = 1;
    root.koszt = 0;
    root.poziom = 0;

    // Push the root node into the queue
    kolejka.push(root);

    while (!kolejka.empty()) {
        Node aktualnyNode = kolejka.top();
        kolejka.pop();

        // Check if all cities have been visited
        if (aktualnyNode.poziom == liczbaMiast - 1) {
            int kosztPowrotu = tablicaKosztow[aktualnyNode.sciezka[aktualnyNode.sciezkaCount - 1]][0];
            if (kosztPowrotu != -1) {
                int kosztCalkowity = aktualnyNode.koszt + kosztPowrotu;
                if (kosztCalkowity < najnizszyKoszt) {
                    najnizszyKoszt = kosztCalkowity;

                    // Update optimal path
                    for (int i = 0; i < aktualnyNode.sciezkaCount; ++i) {
                        optymalnaSciezka[i] = aktualnyNode.sciezka[i];
                    }
                    optymalnaSciezka[aktualnyNode.sciezkaCount] = 0;
                }
            }
            delete[] aktualnyNode.sciezka;
            continue;
        }

        // Expand child nodes
        for (int i = 0; i < liczbaMiast; ++i) {
            if (!miastoZawarteSciezka(aktualnyNode.sciezka, aktualnyNode.sciezkaCount, i)) {
                int kosztPrzejscia = tablicaKosztow[aktualnyNode.sciezka[aktualnyNode.sciezkaCount - 1]][i];
                if (kosztPrzejscia != -1) {
                    Node potomek;
                    potomek.sciezka = new int[liczbaMiast + 1];
                    std::copy(aktualnyNode.sciezka, aktualnyNode.sciezka + aktualnyNode.sciezkaCount, potomek.sciezka);
                    potomek.sciezka[aktualnyNode.sciezkaCount] = i;
                    potomek.sciezkaCount = aktualnyNode.sciezkaCount + 1;
                    potomek.poziom = aktualnyNode.poziom + 1;

                    // Calculate cost for the child
                    potomek.koszt = aktualnyNode.koszt + kosztPrzejscia;

                    // Add the child node to the queue only if it's promising
                    if (potomek.koszt < najnizszyKoszt) {
                        kolejka.push(potomek);
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

    // Output the optimal path
    std::cout << "Najkorzystniejsza trasa: ";
    for (int i = 0; i < liczbaMiast; ++i) {
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