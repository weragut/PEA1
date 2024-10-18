#include "Losowy.h"
#include <iostream>
#include <vector>
#include <algorithm>  // std::random_shuffle
#include <cstdlib>  // std::rand, std::srand
#include <ctime>    // std::time
#include <limits>

// Konstruktor
Losowy::Losowy(const Matrix& m, int repetitions, int instances)
    : matrix(m), size(m.getSize()), repetitions(repetitions), instances(instances), minCost(std::numeric_limits<int>::max()) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));  // Inicjalizacja generatora liczb losowych
}

// Generowanie losowej ścieżki
std::vector<int> Losowy::generateRandomPath() {
    std::vector<int> path(size);
    for (int i = 0; i < size; ++i) {
        path[i] = i;  // Wypełnij wektor miastami
    }
    std::random_shuffle(path.begin(), path.end());  // Losowa permutacja miast
    return path;
}

// Algorytm losowy
int Losowy::findShortestPath() {
    // Wykonujemy określoną liczbę powtórzeń (repetitions)
    for (int rep = 0; rep < repetitions; ++rep) {
        for (int inst = 0; inst < instances; ++inst) {
            std::vector<int> randomPath = generateRandomPath();  // Generowanie losowej trasy

            // Obliczanie kosztu trasy
            int currentCost = 0;
            bool validPath = true;

            for (int i = 0; i < size - 1; ++i) {
                int cost = matrix.getCost(randomPath[i], randomPath[i + 1]);
                if (cost == -1) {
                    validPath = false;  // Brak połączenia
                    break;
                }
                currentCost += cost;
            }

            // Dodaj koszt powrotu do początkowego miasta
            if (validPath) {
                int returnCost = matrix.getCost(randomPath[size - 1], randomPath[0]);
                if (returnCost != -1) {
                    currentCost += returnCost;

                    // Aktualizacja najlepszej trasy
                    if (currentCost < minCost) {
                        minCost = currentCost;
                        bestPath = randomPath;
                    }
                }
            }
        }
    }

    return minCost;  // Zwróć minimalny znaleziony koszt
}

// Wyświetlanie ścieżki
void Losowy::displayBestPath() const {
    std::cout << "Najkrótsza ścieżka (algorytm losowy): ";
    for (int city : bestPath) {
        std::cout << city << " ";
    }
    std::cout << bestPath[0] << std::endl;  // Powrót do początkowego miasta
    std::cout << "Koszt: " << minCost << std::endl;
}

// Zwraca minimalny koszt
int Losowy::getMinCost() const {
    return minCost;
}
