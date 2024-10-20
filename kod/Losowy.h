#ifndef LOSOWY_H
#define LOSOWY_H

#include "Matrix.h"
using namespace std;
#include <vector>

class Losowy {
public:
    Losowy(const Matrix& matrix, int instances); // konstruktor
    int findShortestPath(); // znajdowanie najkrotszej sciezki
    void displayBestPath() const; // wyswietl najlepsza sciezke (funkcja pomocnicza)
    int getMinCost() const;// zwraca minimalny koszt
    double getExecutionTime() const; // zwraca czas wykonania


private:
    const Matrix& matrix; // referencja do obiektu macierzy
    int size; // rozmiar
    int instances; // liczba instancji (ile losowych tras zostanie wygenerowanych)
    vector<int> bestPath; // najkrotsza znaleziona sciezka
    int minCost; // koszt najkrotszej sciezki
    double executionTime; // czas wykonania algorytmu


    vector<int> generateRandomPath(); // generowanie losowej sciezki
};

#endif
