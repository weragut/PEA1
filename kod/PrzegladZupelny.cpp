#include "PrzegladZupelny.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <chrono>
using namespace std;

// konstruktor inicjalizujacy referencje do obiektu macierzy kosztow
// pobiera rozmiar i ustawia minimalny koszt na maksymalna liczbe
PrzegladZupelny::PrzegladZupelny(const Matrix& m): matrix(m), size(m.getSize()), minCost(numeric_limits<int>::max()) {}

// metoda obliczenia najkrotszej sciezki
int PrzegladZupelny::findShortestPath() {
    vector<int> vertex(size);  // wektor wierzcholkow
    for (int i = 0; i < size; ++i) {
        vertex[i] = i;  // wypelniamy wektor wierzcholkami
    }

    // poczatek pomiaru czasu
    auto start = chrono::high_resolution_clock::now();


    // przetwarzanie wszystkich permutacji
    do {
        int currentCost = 0;  // koszt aktualnej trasy
        bool validPath = true;  // oznaczzenie czy trasa jest mozliwa

        // koszt ścieżki dla aktualnej permutacji
        for (int i = 0; i < size - 1; ++i) {
            int cost = matrix.getCost(vertex[i], vertex[i + 1]); // pobranie kosztu miedzy wierzcholkami
            if (cost == -1) {
                validPath = false;  // brak polaczenia
                break;
            }
            currentCost += cost;

            // przerwij obliczenia, jesli dotychczasowy koszt jest wiekszy niż minCost
            if (currentCost >= minCost) {
                validPath = false;
                break;
            }

        }

        // dodaj koszt powrotu do pierwszego miasta
        if (validPath) {
            int returnCost = matrix.getCost(vertex[size - 1], vertex[0]);
            if (returnCost != -1) {
                currentCost += returnCost;

                // aktualizacja minimalnego kosztu
                if (currentCost < minCost) {
                    minCost = currentCost;
                    bestPath = vertex;  // najlepsza trasa
                }
            }
        }

    } while (next_permutation(vertex.begin(), vertex.end()));  // pełne permutacje miast

    // koniec pomiaru czasu
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    //cout << "Czas wykonania wybranego fragmentu: " << duration.count() << " ms" << endl;

    // zapisz czas wykonania
    executionTime = duration.count();

    return minCost;
}

// zwraca czas wykonania algorytmu
double PrzegladZupelny::getExecutionTime() const {
    return executionTime;
}

// wyswietlenie najkrotszej sciezki (funkcja pomocnicza)
void PrzegladZupelny::displayBestPath() const {
    cout << "Najkrotsza sciezka: ";
    for (int city : bestPath) {
        cout << city << " ";  // wypisuje kolejnosc miast
    }
    cout << bestPath[0] << endl;  // powrot do pierwszego miasta
    cout << "Koszt: " << minCost << endl;
}

