#include <iostream>
#include "Config.h"
#include "Matrix.h"
#include "PrzegladZupelny.h"
using namespace std;

int main() {
    // wczytaj plik konfoguracyjny
    Config config;
    if (!config.loadConfig("C:\\Users\\werag\\Documents\\clionProjekty\\PEA1\\wejscie\\plik_konfiguracyjny.txt")) {
        return 1;
    }

    // deklaracja macierzy
    Matrix matrix;

    // wybieranie sposobu generowania macierzy z pliku lub generowanej losowo
    if (config.matrix_source == "file") {
        if (!matrix.loadFromFile(config.input_file)) {
            return 1;
        }
    } else if (config.matrix_source == "manual") {
        matrix.generateManual(config.matrix_size, config.matrix_type);
    } else {
        cout << "matrix_source wczytano jako: [" << config.matrix_source << "]" << endl;
        cerr << "Niepoprawna wartosc dla matrix_source!" << endl;

        return 1;
    }

    // wyswietlenie macierzy
    matrix.display();


    // Tworzenie obiektu PrzegladZupelny i znajdowanie najkrótszej ścieżki
    PrzegladZupelny przeglad(matrix);
    int minCost = przeglad.findShortestPath();
    przeglad.displayBestPath();

    std::cout << "Minimalny koszt: " << minCost << std::endl;

    // Wyniki można zapisywać do pliku w kolejnych krokach

    return 0;
}
