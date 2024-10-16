#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <cstdlib>  // do funkcji rand()

Matrix::Matrix() : matrix(nullptr), size(0) {}

Matrix::~Matrix() {
    freeMemory();
}

bool Matrix::loadFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cout << "Proba otwarcia pliku: " << filename << std::endl;

        std::cerr << "Nie można otworzyc pliku: " << filename << std::endl;
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

void Matrix::generateManual(int size, const std::string& type) {
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

    std::cout << "Macierz (" << size << "x" << size << "):" << std::endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
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
