#ifndef ALGORYTM_GENETYCZNY_H
#define ALGORYTM_GENETYCZNY_H

// Biblioteki standardowe
#include <vector>  // Do przechowywania wektorów (np. ścieżek osobników).
#include <list>  // Do przechowywania listy najlepszych rozwiązań w czasie.
#include <algorithm>  // Do funkcji pomocniczych jak sortowanie.
#include "MacierzKosztow.h"  // Nagłówek zawierający definicję klasy MacierzKosztow.

struct Osobnik {
    // Reprezentacja osobnika w populacji
    std::vector<int> sciezka;  // Wektor reprezentujący ścieżkę (porządek odwiedzanych miast).
    int koszt;  // Całkowity koszt tej ścieżki (np. suma odległości pomiędzy miastami w ścieżce).
};

// Typ wyliczeniowy dla rodzajów mutacji
enum TypMutacji {
    zamiana,  // Mutacja zamiany dwóch miast w ścieżce.
    inwersja  // Mutacja inwersji (odwrócenie fragmentu ścieżki).
};

// Klasa implementująca algorytm genetyczny
class GeneticAlgorithm{
private:
    MacierzKosztow& macierz;  // Referencja do macierzy kosztów (przechowuje odległości między miastami).
    std::list<std::pair<double, int>> najlepszeRozwiazaniaWCzasie;  // Lista najlepszych rozwiązań w trakcie działania algorytmu (para: koszt, czas).

    // Funkcja pomocnicza do obliczania kosztu ścieżki
    static int obliczKosztSciezki(const std::vector<int>& sciezka, int** macierz, int rozmiar);

    // Funkcja porównująca dwóch osobników na podstawie ich kosztów
    static bool porownajOsobniki(const Osobnik& a, const Osobnik& b);

    // Funkcja realizująca krzyżowanie OX (Order Crossover)
    void krzyzowanieOX(const Osobnik& rodzic1, const Osobnik& rodzic2, Osobnik& dziecko1, Osobnik& dziecko2, int poczatek, int koniec);

    // Funkcja realizująca mutację typu zamiana
    void mutacjaZamiany(Osobnik& osobnik);

    // Funkcja realizująca mutację typu inwersja
    void mutacjaInwersji(Osobnik& osobnik);

    // Funkcja realizująca wybór osobnika przez turniej
    Osobnik turniejWyboru(const std::vector<Osobnik>& populacja);

public:
    // Konstruktor, który inicjalizuje algorytm genetyczny
    GeneticAlgorithm(MacierzKosztow& macierz);

    // Funkcja do tworzenia początkowej, losowej populacji
    std::vector<Osobnik> stworzLosowaPopulacje(int rozmiarPopulacji);

    // Funkcja uruchamiająca główny algorytm genetyczny
    Osobnik uruchom(int czasZatrzymania, int rozmiarPopulacji, double wspolczynnikMutacji, double wspolczynnikKrzyzowania, TypMutacji typMutacji);

    // Funkcja zwracająca listę najlepszych rozwiązań w trakcie działania algorytmu
    const std::list<std::pair<double, int>>& pobierzNajlepszeRozwiazaniaWCzasie() const;

};

#endif // ALGORYTM_GENETYCZNY_H
