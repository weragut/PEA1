#include "Config.h"
#include <iostream>
#include <fstream>

bool Config::loadConfig(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku konfiguracyjnego: " << filename << std::endl;
        return false;
    }

    std::string key;
    while (file >> key) {
        if (key == "matrix_source") {
            file >> matrix_source;
        } else if (key == "output_file") {
            file >> output_file;
        } else if (key == "repetitions") {
            file >> repetitions;
        } else if (key == "instances") {
            file >> instances;
        } else if (key == "input_file") {
            file >> input_file;
        } else if (key == "matrix_size") {
            file >> matrix_size;
        } else if (key == "matrix_type") {
            file >> matrix_type;
        }
    }

    file.close();
    return true;
}
