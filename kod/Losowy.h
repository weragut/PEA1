#ifndef LOSOWY_H
#define LOSOWY_H

#include "Matrix.h"
#include <vector>
#include <string>

class Losowy {
public:
    Losowy(const Matrix& matrix, int repetitions, int instances);  // Konstruktor
    int findShortestPath();  // Znajdź losowo najkrótszą ścieżkę
    void displayBestPath() const;  // Wyświetl najlepszą ścieżkę
    int getMinCost() const;  // Zwraca minimalny koszt

private:
    const Matrix& matrix;  // Referencja do obiektu macierzy
    int size;  // Rozmiar macierzy (liczba miast)
    int repetitions;  // Liczba powtórzeń (ile razy algorytm ma próbować znaleźć trasę)
    int instances;  // Liczba instancji problemu (ile losowych tras wygenerować dla każdej próby)
    std::vector<int> bestPath;  // Najkrótsza znaleziona ścieżka
    int minCost;  // Koszt najkrótszej znalezionej ścieżki

    std::vector<int> generateRandomPath();  // Generuje losową ścieżkę
};

#endif
