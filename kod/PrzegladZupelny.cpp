#include "PrzegladZupelny.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

PrzegladZupelny::PrzegladZupelny(const Matrix& m)
    : matrix(m), size(m.getSize()), minCost(numeric_limits<int>::max()) {}

// Metoda, która oblicza najkrótszą ścieżkę
int PrzegladZupelny::findShortestPath() {
    vector<int> cities(size);
    for (int i = 0; i < size; ++i) {
        cities[i] = i;
    }

    // Przetwarzanie wszystkich permutacji
    do {
        int currentCost = 0;
        bool validPath = true;

        // Oblicz koszt ścieżki dla aktualnej permutacji
        for (int i = 0; i < size - 1; ++i) {
            int cost = matrix.getCost(cities[i], cities[i + 1]);
            if (cost == -1) {
                validPath = false;
                break;
            }
            currentCost += cost;
        }

        // Dodaj koszt powrotu do pierwszego miasta
        int returnCost = matrix.getCost(cities[size - 1], cities[0]);
        if (validPath && returnCost != -1) {
            currentCost += returnCost;

            // Aktualizacja minimalnego kosztu i najlepszego rozwiązania
            if (currentCost < minCost) {
                minCost = currentCost;
                bestPath = cities;
            }
        }

    } while (std::next_permutation(cities.begin() + 1, cities.end()));

    return minCost;
}

// Wyświetlanie najkrótszej ścieżki
void PrzegladZupelny::displayBestPath() const {
    cout << "Najkrotsza sciezka: ";
    for (int city : bestPath) {
        std::cout << city << " ";
    }
    cout << bestPath[0] << endl;  // Powrót do początkowego miasta
    cout << "Koszt: " << minCost << endl;
}

// Zwraca minimalny koszt
int PrzegladZupelny::getMinCost() const {
    return minCost;
}
