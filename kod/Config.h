#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
using namespace std;

class Config {
public:
    // Publiczne pola konfiguracyjne
    string matrix_source;
    string output_file;
    int repetitions;
    int instances;

    // Parametry specyficzne dla opcji "file"
    string input_file;     // Używane, gdy matrix_source = "file"

    // Parametry specyficzne dla opcji "manual"
    int matrix_size;            // Rozmiar macierzy (tylko jeśli manual)
    string matrix_type;    // Typ macierzy: "synchronous" lub "asynchronous" (tylko jeśli manual)

    // Funkcja do wczytania pliku konfiguracyjnego
    bool loadConfig(const std::string& filename);
};

#endif
