#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <cstdlib>  // do funkcji rand()
using namespace std;

Matrix::Matrix() : matrix(nullptr), size(0) {}

Matrix::~Matrix() {
    freeMemory();
}

bool Matrix::loadFromFile(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Proba otwarcia pliku: " << filename << endl;

        cerr << "Nie można otworzyc pliku: " << filename << endl;
        return false;
    }

    // Dealokacja pamięci przed wczytaniem nowej macierzy
    freeMemory();

    inputFile >> size; // nadpisanie poprawnego rozmiaru

    // dynamiczna alokacja pamieci dla macierzy
    matrix = new int*[size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            inputFile >> matrix[i][j];
        }
    }

    inputFile.close();
    return true;
}

void Matrix::generateManual(int size, const string& type) {
    // Dealokacja pamięci przed wczytaniem nowej macierzy
    freeMemory();
    this->size = size;
    matrix = new int*[size]; // alokacja pamięci tablicy wskaźników int*, która ma size elementów

    if(type == "asynchronous") {
        for (int i = 0; i < size; ++i) {
            matrix[i] = new int[size];
            for (int j = 0; j < size; ++j) {
                if (i == j) {
                    matrix[i][j] = -1;  // Przekątna
                } else {
                    matrix[i][j] = rand() % 100 + 1;  // Asynchroniczna macierz
                }
            }
        }
    }else{
        for (int i = 0; i < size; ++i) {
            matrix[i] = new int[size];
            for (int j = 0; j < size; ++j) {
                if (i == j) {
                    matrix[i][j] = -1;  // Przekątna
                } else if(i<j){
                    matrix[i][j] = rand() % 100 + 1;  // Asynchroniczna macierz
                }else if(i>j) {
                    matrix[i][j] = matrix[j][i];
                }
            }
        }

    }

}

void Matrix::display() const {
    if (matrix == nullptr) return;

    cout << "Macierz (" << size << "x" << size << "):" << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Matrix::freeMemory() {
    if (matrix != nullptr) {
        for (int i = 0; i < size; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
    }
}
int Matrix::getSize() const {
    return size;  // Zwraca rozmiar macierzy
}

int Matrix::getCost(int i, int j) const {
    if (i >= 0 && i < size && j >= 0 && j < size) {
        return matrix[i][j];
    } else {
        return -1;  // Zwróć -1, jeśli indeksy są poza zakresem
    }
}