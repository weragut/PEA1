#ifndef MATRIX_H
#define MATRIX_H

#include <string>

class Matrix {
public:
    Matrix();           // Konstruktor
    ~Matrix();          // Destruktor

    bool loadFromFile(const std::string& filename);   // Wczytuje macierz z pliku
    void generateManual(int size, const std::string& type);  // Generuje macierz ręcznie

    void display() const;  // Wyświetla macierz
    void freeMemory();     // Zwalnia pamięć

private:
    int** matrix;          // Wskaźnik do dynamicznej tablicy 2D
    int size;              // Rozmiar macierzy
};

#endif
