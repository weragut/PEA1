#include "Losowy.h"
#include <iostream>
#include <vector>
#include <algorithm>  // std::random_shuffle
#include <cstdlib>  // std::rand, std::srand
#include <ctime>    // std::time
#include <limits>
#include <chrono>
using namespace std;

// konstruktor inicjalizujacy referencje do obiektu macierzy kosztow
// pobiera rozmiar, liczbe instancji i ustawia minimalny koszt na maksymalna liczbe
Losowy::Losowy(const Matrix& m, int instances)
    : matrix(m), size(m.getSize()), instances(instances), minCost(numeric_limits<int>::max()) {}

// generowanie losowej sciezki
vector<int> Losowy::generateRandomPath() {
    vector<int> path(size);
    for (int i = 0; i < size; ++i) {
        path[i] = i;
    }
    random_shuffle(path.begin(), path.end());  //losowe przemieszanie miast
    return path;
}

// algorytm losowy
int Losowy::findShortestPath() {

    // poczatek pomiaru czasu
    auto start = chrono::high_resolution_clock::now();


        for (int inst = 0; inst < instances; ++inst) {
            vector<int> randomPath = generateRandomPath();  // generowanie losowej trasy

            int currentCost = 0; // koszt biezacej sciezki
            bool validPath = true; // czy mozna przejsc ta sciezka

            // obliczenie kosztu dla wygenerowanej sciezki
            for (int i = 0; i < size - 1; ++i) {
                int cost = matrix.getCost(randomPath[i], randomPath[i + 1]);
                if (cost == -1) {
                    validPath = false; // brak przejscia
                    break;
                }
                currentCost += cost;
            }

            // dodajemy koszt powrotu do pierwszego wierzcholka
            if (validPath) {
                int returnCost = matrix.getCost(randomPath[size - 1], randomPath[0]);
                if (returnCost != -1) {
                    currentCost += returnCost;
                    // sprawdzenie czy ta trasa ma mniejszy koszt niz dotychczasowa trasa o najmniejszym koszcie
                    if (currentCost < minCost) {
                        minCost = currentCost;
                        bestPath = randomPath;
                    }
                }
            }
        }

    // koniec pomiaru czasu
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Czas wykonania wybranego fragmentu: " << duration.count() << " ms" << endl;

    // zapisz czas wykonania
    executionTime = duration.count();

    return minCost;  // zwraca minimalny znaleziony koszt
}

// zwraca czas wykonania algorytmu
double Losowy::getExecutionTime() const {
    return executionTime;
}

// wyswietlenie najkrotszej sciezki (funkcja pomocnicza)
void Losowy::displayBestPath() const {
    cout << "Najkrotsza sciezka (algorytm losowy): ";
    for (int city : bestPath) {
        cout << city << " ";
    }
    cout << bestPath[0] << endl;
    cout << "Koszt: " << minCost << endl;
}

// zwrocenie minimalnego kosztu
int Losowy::getMinCost() const {
    return minCost;
}
