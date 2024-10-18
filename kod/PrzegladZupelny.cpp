#include "PrzegladZupelny.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <chrono>

// Konstruktor
PrzegladZupelny::PrzegladZupelny(const Matrix& m)
    : matrix(m), size(m.getSize()), minCost(std::numeric_limits<int>::max()) {}

// metoda obliczenia najkrotszej sciezki
int PrzegladZupelny::findShortestPath() {
    std::vector<int> cities(size);  // wektor miast
    for (int i = 0; i < size; ++i) {
        cities[i] = i;  // wypełnienie wektora miastami (0, 1, ..., size-1)
    }

    auto start = chrono::high_resolution_clock::now();


    // przetwarzanie wszystkich permutacji
    do {
        int currentCost = 0;  // koszt aktualnej trasy
        bool validPath = true;  // flaga wskazująca, czy trasa jest możliwa

        // koszt ścieżki dla aktualnej permutacji
        for (int i = 0; i < size - 1; ++i) {
            int cost = matrix.getCost(cities[i], cities[i + 1]);
            if (cost == -1) {
                validPath = false;  // brak połączenia
                break;
            }
            currentCost += cost;
/*
            // Przerwij obliczenia, jeśli dotychczasowy koszt jest większy niż minCost
            if (currentCost >= minCost) {
                validPath = false;
                break;
            }
            */
        }

        // dodaj koszt powrotu do pierwszego miasta, jeśli dotychczasowa trasa jest ważna
        if (validPath) {
            int returnCost = matrix.getCost(cities[size - 1], cities[0]);
            if (returnCost != -1) {
                currentCost += returnCost;

                // Aktualizacja minimalnego kosztu i najlepszego rozwiązania
                if (currentCost < minCost) {
                    minCost = currentCost;
                    bestPath = cities;  // Zapisz najlepszą trasę
                }
            }
        }

    } while (std::next_permutation(cities.begin(), cities.end()));  // pełne permutacje miast

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> duration = end - start;
    cout << "Czas wykonania wybranego fragmentu: " << duration.count() << " us" << endl;

    // Zapisz czas wykonania
    executionTime = duration.count();

    return minCost;
}

// Zwraca czas wykonania algorytmu
double PrzegladZupelny::getExecutionTime() const {
    return executionTime;
}

// wyświetlanie najkrótszej ścieżki
void PrzegladZupelny::displayBestPath() const {
    std::cout << "Najkrotsza sciezka: ";
    for (int city : bestPath) {
        std::cout << city << " ";  // wypisz kolejność miast
    }
    std::cout << bestPath[0] << std::endl;  // powrót do początkowego miasta
    std::cout << "Koszt: " << minCost << std::endl;
}

// zwrócenie minimalnego kosztu
int PrzegladZupelny::getMinCost() const {
    return minCost;
}
