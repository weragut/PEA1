#ifndef MATRIX_H
#define MATRIX_H

#include <string>

class Matrix {
public:
    Matrix();           // konstruktor
    ~Matrix();          // dekonstruktor

    bool loadFromFile(const std::string& filename);   // wczytywanie macierzy z pliku
    void generateManual(int size, const std::string& type);  // generowanie losowej macierzy

    void display() const;  // wyswietlenie macierzy
    void freeMemory();     // zwolnienie pamieci
private:
    int** matrix;          // wskaznik do dwuwymiarowej tablicy dynamicznej
    int size;              // rozmiar macierzy
};

#endif
