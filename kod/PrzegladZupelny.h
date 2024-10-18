#ifndef PRZEGLADZUPELNY_H
#define PRZEGLADZUPELNY_H

#include <vector>
#include <limits>
#include "Matrix.h"

class PrzegladZupelny {
public:
    PrzegladZupelny(const Matrix& matrix); // konstruktor
    int findShortestPath();  // Znajdź najkrótszą ścieżkę
    void displayBestPath() const;  // Wyświetl najlepszą ścieżkę
    int getMinCost() const;  // Zwraca minimalny koszt
    double getExecutionTime() const;  // Zwraca czas wykonania


private:
    const Matrix& matrix;  // Referencja do obiektu macierzy
    int size;  // Rozmiar macierzy (liczba miast)
    std::vector<int> bestPath;  // Najkrótsza znaleziona ścieżka
    int minCost;  // Koszt najkrótszej ścieżki
    double executionTime;  // Czas wykonania algorytmu

   // void calculateAllPermutations();  // Oblicza wszystkie permutacje miast
};

#endif
