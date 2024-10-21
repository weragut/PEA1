#ifndef NAJBLIZSZYCHSASIADOW_H
#define NAJBLIZSZYCHSASIADOW_H

#include "Matrix.h"
#include <vector>
using namespace std;

class NajblizszychSasiadow {
public:
    NajblizszychSasiadow(const Matrix& matrix); // konstruktor
    int findShortestPath(); // znajdowanie najkrotszej sciezki
    void displayBestPath() const; // wyswietl najlepsza sciezke (funkcja pomocnicza)
    double getExecutionTime() const; // zwraca czas wykonania

private:
    const Matrix& matrix; // referencja do obiektu macierzy
    int size; // rozmiar
    vector<int> bestPath;// najkrotsza znaleziona sciezka
    int minCost; // koszt najkrotszej sciezki
    double executionTime;// czas wykonania algorytmu

};

#endif
