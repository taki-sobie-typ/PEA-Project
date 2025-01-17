#include "../header/GeneticAlgorithm.h"
#include <random>
#include <ctime>
#include <climits>
#include <numeric>
#include <unordered_set>
#include <algorithm>

// Konstruktor klasy GeneticAlgorithm, który przyjmuje jako argument referencję do macierzy kosztów.
GeneticAlgorithm::GeneticAlgorithm(MacierzKosztow& macierzKosztow) : macierz(macierzKosztow) {}

// Funkcja statyczna, która oblicza koszt danej ścieżki na podstawie macierzy kosztów.
// Argumenty:
// - sciezka: wektor reprezentujący kolejność odwiedzania miast,
// - macierz: wskaźnik na macierz kosztów,
// - rozmiar: liczba miast.
// Funkcja sumuje koszty przejścia pomiędzy kolejnymi miastami w ścieżce.
int GeneticAlgorithm::obliczKosztSciezki(const std::vector<int>& sciezka, int** macierz, int rozmiar) {
    int calkowityKoszt = 0;
    for (int i = 0; i < rozmiar - 1; ++i) {
        calkowityKoszt += macierz[sciezka[i]][sciezka[i + 1]]; // Dodanie kosztu przejścia między kolejnymi miastami.
    }
    calkowityKoszt += macierz[sciezka[rozmiar - 1]][sciezka[0]]; // Dodanie kosztu powrotu do pierwszego miasta.
    return calkowityKoszt; // Zwrócenie całkowitego kosztu ścieżki.
}

// Funkcja generująca początkową populację losowych osobników.
// Argument:
// - rozmiarPopulacji: liczba osobników do wygenerowania.
// Funkcja tworzy losowe ścieżki, oblicza ich koszt i zwraca populację osobników.
std::vector<Osobnik> GeneticAlgorithm::stworzLosowaPopulacje(int rozmiarPopulacji) {
    int liczbaMiast = macierz.pobierzLiczbeMiast(); // Pobranie liczby miast.
    int** tablicaKosztow = macierz.pobierzMacierzKosztow(); // Pobranie wskaźnika na macierz kosztów.

    std::vector<Osobnik> populacja(rozmiarPopulacji); // Wektor przechowujący populację.
    std::vector<int> bazaSciezki(liczbaMiast); // Wektor bazowy dla losowych ścieżek.
    std::iota(bazaSciezki.begin(), bazaSciezki.end(), 0); // Wypełnienie wektora wartościami od 0 do liczbaMiast-1.

    std::mt19937 generator(std::random_device{}()); // Inicjalizacja generatora liczb losowych.

    // Tworzenie każdego osobnika w populacji.
    for (int i = 0; i < rozmiarPopulacji; ++i) {
        std::shuffle(bazaSciezki.begin() + 1, bazaSciezki.end(), generator); // Losowe przetasowanie miast (pomijając pierwsze).
        populacja[i].sciezka = bazaSciezki; // Przypisanie losowej ścieżki do osobnika.
        populacja[i].koszt = obliczKosztSciezki(populacja[i].sciezka, tablicaKosztow, liczbaMiast); // Obliczenie kosztu ścieżki.
    }

    return populacja; // Zwrócenie populacji.
}

// Funkcja porównująca dwa osobniki na podstawie ich kosztów.
// Zwraca true, jeśli koszt pierwszego osobnika jest mniejszy od drugiego.
bool GeneticAlgorithm::porownajOsobniki(const Osobnik& a, const Osobnik& b) {
    return a.koszt < b.koszt;
}

// Funkcja selekcji turniejowej, która wybiera najlepszego osobnika spośród dwóch losowo wybranych.
// Argumenty:
// - populacja: referencja do wektora osobników.
// Funkcja losuje dwóch osobników, porównuje ich koszty i zwraca lepszego.
Osobnik GeneticAlgorithm::turniejWyboru(const std::vector<Osobnik>& populacja) {
    static std::mt19937 generator(std::random_device{}()); // Generator liczb losowych.
    std::uniform_int_distribution<int> dystrybucja(0, populacja.size() - 1); // Zakres losowania indeksów.

    const Osobnik& pierwszy = populacja[dystrybucja(generator)]; // Pierwszy losowy osobnik.
    const Osobnik& drugi = populacja[dystrybucja(generator)]; // Drugi losowy osobnik.
    return porownajOsobniki(pierwszy, drugi) ? pierwszy : drugi; // Zwrócenie lepszego osobnika.
}

// Funkcja implementująca krzyżowanie OX (Order Crossover).
// Argumenty:
// - rodzic1, rodzic2: rodzice do krzyżowania,
// - dziecko1, dziecko2: osobniki potomne,
// - poczatek, koniec: indeksy wycinka do przekopiowania z rodziców do dzieci.
void GeneticAlgorithm::krzyzowanieOX(const Osobnik& rodzic1, const Osobnik& rodzic2, Osobnik& dziecko1, Osobnik& dziecko2, int poczatek, int koniec) {
    constexpr int PUSTY = -1; // Wartość oznaczająca pustą pozycję.
    int rozmiar = rodzic1.sciezka.size(); // Rozmiar ścieżki (liczba miast).

    dziecko1.sciezka.assign(rozmiar, PUSTY); // Inicjalizacja pustego dziecka1.
    dziecko2.sciezka.assign(rozmiar, PUSTY); // Inicjalizacja pustego dziecka2.

    // Kopiowanie wycinka z rodziców do dzieci.
    for (int i = poczatek; i <= koniec; ++i) {
        dziecko1.sciezka[i] = rodzic1.sciezka[i];
        dziecko2.sciezka[i] = rodzic2.sciezka[i];
    }

    // Lambda uzupełniająca pozostałe geny w ścieżkach dzieci.
    auto uzupelnijDziecko = [&](Osobnik& dziecko, const Osobnik& rodzic, const std::unordered_set<int>& uzyteGeny, int pozycja) {
        int indeks = pozycja;
        for (int gen : rodzic.sciezka) { // Iteracja przez geny rodzica.
            if (uzyteGeny.find(gen) == uzyteGeny.end()) { // Jeśli gen nie jest użyty.
                while (dziecko.sciezka[indeks] != PUSTY) { // Znajdź pierwszą pustą pozycję.
                    indeks = (indeks + 1) % rozmiar;
                }
                dziecko.sciezka[indeks] = gen; // Przypisz gen do pustej pozycji.
            }
        }
    };

    // Tworzenie zbiorów użytych genów.
    std::unordered_set<int> uzyteGeny1(dziecko1.sciezka.begin() + poczatek, dziecko1.sciezka.begin() + koniec + 1);
    std::unordered_set<int> uzyteGeny2(dziecko2.sciezka.begin() + poczatek, dziecko2.sciezka.begin() + koniec + 1);

    // Uzupełnienie brakujących genów w dzieciach.
    uzupelnijDziecko(dziecko1, rodzic2, uzyteGeny1, (koniec + 1) % rozmiar);
    uzupelnijDziecko(dziecko2, rodzic1, uzyteGeny2, (koniec + 1) % rozmiar);

    // Obliczenie kosztów dzieci.
    dziecko1.koszt = obliczKosztSciezki(dziecko1.sciezka, macierz.pobierzMacierzKosztow(), rozmiar);
    dziecko2.koszt = obliczKosztSciezki(dziecko2.sciezka, macierz.pobierzMacierzKosztow(), rozmiar);
}

// Funkcja mutacji zamiany. Losowo wybiera dwa miasta i zamienia je miejscami w ścieżce osobnika.
void GeneticAlgorithm::mutacjaZamiany(Osobnik& osobnik) {
    static std::mt19937 generator(std::random_device{}());  // Tworzymy generator liczb losowych.
    std::uniform_int_distribution<int> dystrybucja(0, osobnik.sciezka.size() - 1);  // Zakres dla indeksów miast w ścieżce.

    // Losujemy dwa różne indeksy miast
    int i = dystrybucja(generator);
    int j = dystrybucja(generator);

    // Zamieniamy miejscami miasta o tych indeksach w ścieżce
    std::swap(osobnik.sciezka[i], osobnik.sciezka[j]);

    // Po wykonaniu mutacji, przeliczamy koszt ścieżki
    osobnik.koszt = obliczKosztSciezki(osobnik.sciezka, macierz.pobierzMacierzKosztow(), osobnik.sciezka.size());
}

// Funkcja mutacji inwersji. Losowo wybiera dwa indeksy i odwraca kolejność miast między tymi indeksami.
void GeneticAlgorithm::mutacjaInwersji(Osobnik& osobnik) {
    static std::mt19937 generator(std::random_device{}());  // Tworzymy generator liczb losowych.
    std::uniform_int_distribution<int> dystrybucja(0, osobnik.sciezka.size() - 1);  // Zakres dla indeksów miast.

    // Losujemy dwa różne indeksy w ścieżce
    int i = dystrybucja(generator);
    int j = dystrybucja(generator);

    // Upewniamy się, że i < j, aby nie zamienić miejscami tych samych indeksów
    if (i > j) std::swap(i, j);

    // Odwracamy fragment ścieżki pomiędzy tymi dwoma indeksami
    std::reverse(osobnik.sciezka.begin() + i, osobnik.sciezka.begin() + j + 1);

    // Po wykonaniu mutacji, przeliczamy koszt ścieżki
    osobnik.koszt = obliczKosztSciezki(osobnik.sciezka, macierz.pobierzMacierzKosztow(), osobnik.sciezka.size());
}

// Główna funkcja uruchamiająca algorytm genetyczny.
Osobnik GeneticAlgorithm::uruchom(
    int czasZatrzymania,  // Czas trwania działania algorytmu (w sekundach).
    int rozmiarPopulacji, // Rozmiar populacji (liczba osobników).
    double wspolczynnikMutacji,  // Prawdopodobieństwo mutacji.
    double wspolczynnikKrzyzowania,  // Prawdopodobieństwo krzyżowania.
    TypMutacji typMutacji  // Typ mutacji (zamiana lub inwersja).
) {
    constexpr int ELITA = 10;  // Liczba najlepszych osobników, które zostaną zachowane w każdej iteracji.

    // Tworzymy początkową, losową populację
    std::vector<Osobnik> populacja = stworzLosowaPopulacje(rozmiarPopulacji);
    int najlepszeRozwiazanie = INT_MAX;  // Najlepsze rozwiązanie (koszt) w trakcie działania algorytmu.
    const std::clock_t czasStartu = std::clock();  // Czas rozpoczęcia działania algorytmu.

    // Generator do losowania prawdopodobieństw i wyboru osobników
    std::mt19937 generator(std::random_device{}());
    std::uniform_real_distribution<double> prawdopodobienstwo(0.0, 1.0);

    // Pętla główna algorytmu (wykonuje się przez zadany czas)
    while ((std::clock() - czasStartu) / CLOCKS_PER_SEC < czasZatrzymania) {
        // Sortowanie populacji, aby najlepsze osobniki były na początku
        std::sort(populacja.begin(), populacja.end(), porownajOsobniki);

        double obecnyCzas = (std::clock() - czasStartu) / (double)CLOCKS_PER_SEC;  // Czas od rozpoczęcia

        // Jeśli znaleźliśmy lepsze rozwiązanie, zapisz je
        if (populacja[0].koszt < najlepszeRozwiazanie) {
            najlepszeRozwiazanie = populacja[0].koszt;

            najlepszeRozwiazaniaWCzasie.emplace_back(obecnyCzas, najlepszeRozwiazanie);
        }

        // Tworzymy nową populację
        std::vector<Osobnik> nowaPopulacja(rozmiarPopulacji);

        // Zachowanie najlepszych osobników (elitarnych) w nowej populacji
        std::copy(populacja.begin(), populacja.begin() + ELITA, nowaPopulacja.begin());

        // Krzyżowanie i mutacja reszty populacji
        for (int i = ELITA; i < rozmiarPopulacji; i += 2) {
            // Wybór dwóch rodziców (turniej)
            Osobnik rodzic1 = turniejWyboru(populacja);
            Osobnik rodzic2 = turniejWyboru(populacja);
            Osobnik dziecko1 = rodzic1, dziecko2 = rodzic2;

            // Krzyżowanie, jeśli prawdopodobieństwo jest spełnione
            if (prawdopodobienstwo(generator) < wspolczynnikKrzyzowania) {
                int poczatek = generator() % rodzic1.sciezka.size();
                int koniec = generator() % rodzic1.sciezka.size();
                if (poczatek > koniec) std::swap(poczatek, koniec);
                krzyzowanieOX(rodzic1, rodzic2, dziecko1, dziecko2, poczatek, koniec);
            }

            // Mutacja, jeśli prawdopodobieństwo jest spełnione
            if (prawdopodobienstwo(generator) < wspolczynnikMutacji) {
                typMutacji == TypMutacji::zamiana ? mutacjaZamiany(dziecko1) : mutacjaInwersji(dziecko1);
            }

            if (prawdopodobienstwo(generator) < wspolczynnikMutacji) {
                typMutacji == TypMutacji::zamiana ? mutacjaZamiany(dziecko2) : mutacjaInwersji(dziecko2);
            }

            // Umieszczamy dzieci w nowej populacji
            nowaPopulacja[i] = dziecko1;
            if (i + 1 < rozmiarPopulacji) nowaPopulacja[i + 1] = dziecko2;
        }

        // Aktualizujemy populację na nową
        populacja = nowaPopulacja;
    }

    // Zwracamy najlepszy osobnik z populacji po zakończeniu algorytmu
    return *std::min_element(populacja.begin(), populacja.end(), porownajOsobniki);
}

// Funkcja zwracająca listę najlepszych rozwiązań w czasie.
const std::list<std::pair<double, int>>& GeneticAlgorithm::pobierzNajlepszeRozwiazaniaWCzasie() const {
    return najlepszeRozwiazaniaWCzasie;
}
