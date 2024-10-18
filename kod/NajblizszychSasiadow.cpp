#include "NajblizszychSasiadow.h"
#include <iostream>
#include <limits>
using namespace std;
// Konstruktor
NajblizszychSasiadow::NajblizszychSasiadow(const Matrix& m)
    : matrix(m), size(m.getSize()), minCost(std::numeric_limits<int>::max()) {}

// Algorytm najbliższych sąsiadów
int NajblizszychSasiadow::findShortestPath() {
    std::vector<int> visited(size, 0);  // Tablica odwiedzonych miast (0 - nieodwiedzone, 1 - odwiedzone)
    bestPath.clear();  // Wyczyszczenie poprzednich danych
    int currentCity = 0;  // Zaczynamy od miasta 0 (można to zmienić na losowe miasto)
    visited[currentCity] = 1;  // Oznaczamy pierwsze miasto jako odwiedzone
    bestPath.push_back(currentCity);  // Zapisz startowe miasto do ścieżki
    minCost = 0;  // Zresetuj minimalny koszt

    // Pętla odwiedzająca wszystkie miasta
    for (int i = 1; i < size; ++i) {
        int nearestCity = -1;
        int nearestCost = std::numeric_limits<int>::max();  // Najbliższe miasto, początkowo maksymalna wartość

        // Znajdź najbliższe nieodwiedzone miasto
        for (int j = 0; j < size; ++j) {
            if (!visited[j]) {  // Jeśli miasto j nie jest odwiedzone
                int cost = matrix.getCost(currentCity, j);
                if (cost != -1 && cost < nearestCost) {  // Znajdź najniższy koszt
                    nearestCity = j;
                    nearestCost = cost;
                }
            }
        }

        // Aktualizacja ścieżki
        if (nearestCity != -1) {
            visited[nearestCity] = 1;  // Oznacz najbliższe miasto jako odwiedzone
            bestPath.push_back(nearestCity);  // Dodaj miasto do ścieżki
            minCost += nearestCost;  // Dodaj koszt do całkowitego kosztu
            currentCity = nearestCity;  // Przejdź do kolejnego miasta
        } else {
            std::cerr << "Błąd: Nie znaleziono połączenia." << std::endl;
            return -1;
        }
    }

    // Powrót do początkowego miasta
    int returnCost = matrix.getCost(currentCity, bestPath[0]);
    if (returnCost != -1) {
        minCost += returnCost;
        bestPath.push_back(bestPath[0]);  // Zamknij cykl, dodając powrót do pierwszego miasta
    } else {
        std::cerr << "Błąd: Brak połączenia powrotnego do miasta startowego." << std::endl;
        return -1;
    }

    return minCost;
}

// Wyświetlanie ścieżki
void NajblizszychSasiadow::displayBestPath() const {
    std::cout << "Najkrotsza sciezka (algorytm najblizszych sasiadow): ";
    for (int city : bestPath) {
        std::cout << city << " ";
    }
    std::cout << std::endl;
    std::cout << "Koszt: " << minCost << std::endl;
}

// Zwraca minimalny koszt
int NajblizszychSasiadow::getMinCost() const {
    return minCost;
}
