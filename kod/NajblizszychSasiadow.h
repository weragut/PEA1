#ifndef NAJBLIZSZYCHSASIADOW_H
#define NAJBLIZSZYCHSASIADOW_H

#include "Matrix.h"
#include <vector>

class NajblizszychSasiadow {
public:
    NajblizszychSasiadow(const Matrix& matrix);  // Konstruktor
    int findShortestPath();  // Znajdź ścieżkę algorytmem najbliższych sąsiadów
    void displayBestPath() const;  // Wyświetl ścieżkę
    int getMinCost() const;  // Zwraca minimalny koszt

private:
    const Matrix& matrix;  // Referencja do obiektu macierzy
    int size;  // Rozmiar macierzy (liczba miast)
    std::vector<int> bestPath;  // Najkrótsza ścieżka (kolejność miast)
    int minCost;  // Koszt znalezionej ścieżki
};

#endif
