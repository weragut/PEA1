#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
using namespace std;


class Matrix {
public:
    Matrix();           // konstruktor
    ~Matrix();          // dekonstruktor

    bool loadFromFile(const string& filename);   // wczytywanie macierzy z pliku
    void generateManual(int size, const string& type);  // generowanie losowej macierzy

    void display() const;  // wyswietlenie macierzy
    void freeMemory();     // zwolnienie pamieci

    int getSize() const;  // Metoda zwracająca rozmiar macierzy
    int getCost(int i, int j) const;  // Metoda zwracająca koszt przejścia z miasta i do miasta j

private:
    int** matrix;          // wskaznik do dwuwymiarowej tablicy dynamicznej
    int size;              // rozmiar macierzy
};

#endif
