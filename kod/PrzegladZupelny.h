#ifndef PRZEGLADZUPELNY_H
#define PRZEGLADZUPELNY_H

#include <vector>
#include "Matrix.h"
using namespace std;

class PrzegladZupelny {
public:
    PrzegladZupelny(const Matrix& matrix); // konstruktor
    int findShortestPath(); // znajdowanie najkrotszej sciezki
    void displayBestPath() const; // wyswietl najlepsza sciezke (funkcja pomocnicza)
    double getExecutionTime() const; // zwraca czas wykonania


private:
    const Matrix& matrix; // referencja do obiektu macierzy
    int size; // rozmiar
    vector<int> bestPath; // najkrotsza znaleziona sciezka
    int minCost; // koszt najkrotszej sciezki
    double executionTime; // czas wykonania algorytmu

   // void calculateAllPermutations(); // oblicza wszystkie permutacje
};

#endif
