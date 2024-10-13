#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class Config {
public:
    // Publiczne pola konfiguracyjne
    std::string matrix_source;
    std::string output_file;
    int repetitions;
    int instances;

    // Parametry specyficzne dla opcji "file"
    std::string input_file;     // Używane, gdy matrix_source = "file"

    // Parametry specyficzne dla opcji "manual"
    int matrix_size;            // Rozmiar macierzy (tylko jeśli manual)
    std::string matrix_type;    // Typ macierzy: "synchronous" lub "asynchronous" (tylko jeśli manual)

    // Funkcja do wczytania pliku konfiguracyjnego
    bool loadConfig(const std::string& filename);
};

#endif
