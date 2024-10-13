#include <iostream>
#include "Config.h"
#include "Matrix.h"

int main() {
    // Wczytaj konfigurację
    Config config;
    if (!config.loadConfig("C:\\Users\\werag\\Documents\\clionProjekty\\PEA1\\wejscie\\plik_konfiguracyjny.txt")) {
        return 1;
    }

    // Deklaracja macierzy
    Matrix matrix;

    // Wybierz sposób wczytywania/generowania macierzy
    if (config.matrix_source == "file") {
        if (!matrix.loadFromFile(config.input_file)) {
            return 1;
        }
    } else if (config.matrix_source == "manual") {
        matrix.generateManual(config.matrix_size, config.matrix_type);
    } else {
        std::cout << "matrix_source wczytano jako: [" << config.matrix_source << "]" << std::endl;
        std::cerr << "Niepoprawna wartość dla matrix_source!" << std::endl;

        return 1;
    }

    // Wyświetlenie macierzy
    matrix.display();

    // Wyniki można zapisywać do pliku w kolejnych krokach

    return 0;
}
